/*
 * gani : The Realtek RTL816x Gigabit Ethernet Driver for Solaris
 *
 * Copyright (c) 2004-2008 Masayuki Murayama.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the author nor the names of its contributors may be
 *    used to endorse or promote products derived from this software without
 *    specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 * OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH
 * DAMAGE.
 */

#pragma	ident	"%Z%%M% %I%     %E%"

/*
 * TODO
 *	hang/panic at boot time on sparc
 *	offloading seem to cause tx timeout
 *
 *	multicast receive not tested (8168)
 *  BUGS
 */

/* ======================================================= */

/*
 * Solaris system header files and macros
 */
#include <sys/types.h>
#include <sys/conf.h>
#include <sys/debug.h>
#include <sys/kmem.h>
#include <sys/modctl.h>
#include <sys/errno.h>
#include <sys/ddi.h>
#include <sys/sunddi.h>
#include <sys/byteorder.h>
#include <sys/ethernet.h>
#include <sys/pci.h>

#include "gani_mii.h"
#include "gani_util.h"
#include "rtl8169reg.h"

char	ident[] = "rtl816x nic driver v" VERSION;

/*
 * Useful macros
 */
#define	ROUNDUP2(x, y)	(((x)+(y)-1) & ~((y)-1))
#define	PKTSIZE(m) \
		(sizeof (struct ether_header) + 8 + (m) + ETHERFCSL)

#define	ONESEC			(drv_usectohz(1*1000000))

#define	DESC_BASE_ALIGN	256	/* it should be defined in rtl8169reg.h */
#define	DESC_MAX_SIZE	(16*1024)	/* in byte */

#define	TALLY_OFFSET(dp)	\
	(((intptr_t)(dp)->io_area) - ((intptr_t)(dp)->rx_ring))
#define	TALLY_VADDR(dp)		((void *)((dp)->io_area))
#define	TALLY_DMA_ADDR(dp)	((dp)->io_area_dma)

#ifdef MAP_MEM
#define	FLSHB(dp, reg)	(void) INB(dp, reg)
#define	FLSHW(dp, reg)	(void) INW(dp, reg)
#define	FLSHL(dp, reg)	(void) INL(dp, reg)
#else
#define	FLSHB(dp, reg)
#define	FLSHW(dp, reg)
#define	FLSHL(dp, reg)
#endif

#define	TXDESC(p)	((struct tx_desc *)(void *)(p))
#define	RXDESC(p)	((struct rx_desc *)(void *)(p))

#define	CONFIG_EEPROM_IO

/* additional PCI related macros for compatibility */
#ifndef PCI_CAP_ID_PCI_E
#define	PCI_CAP_ID_PCI_E	0x10
#endif

/*
 * Debugging
 */
#ifdef DEBUG_LEVEL
static int gani_debug = DEBUG_LEVEL;
#define	DPRINTF(n, args)	if (gani_debug > (n)) cmn_err args
#else
#define	DPRINTF(n, args)
#endif

#define	DUMP_ETHER(n, dp, m) \
	DPRINTF(n, (CE_CONT, "!%s: %s: mac: %02x:%02x:%02x:%02x:%02x:%02x", \
		(dp)->name, __func__, \
		(m)[0], (m)[1], (m)[2], (m)[3], (m)[4], (m)[5]));
/*
 * Our configration for rtl816x
 */
#ifdef CONFIG_OO
#undef TX_MAX_FRAGS
#define	TX_MAX_FRAGS	1
#undef TX_BUF_SIZE
#define	TX_BUF_SIZE	256
#undef TX_RING_SIZE
#define	TX_RING_SIZE	TX_BUF_SIZE
#endif

#if !defined(TX_MAX_FRAGS)
#define	TX_MAX_FRAGS	GEM_MAXTXFRAGS	/* 8 */
#endif

#ifdef TEST_TXDESC_FULL
#define	TX_RING_SIZE	(DESC_BASE_ALIGN / sizeof (struct tx_desc))
#endif
#ifdef TEST_RX_EMPTY
#define	RX_BUF_SIZE	1
#endif

#ifndef	TX_BUF_SIZE
#define	TX_BUF_SIZE	256
#endif
#ifndef	TX_RING_SIZE
#define	TX_RING_SIZE	(DESC_MAX_SIZE / sizeof (struct tx_desc))
#endif

#ifndef	RX_BUF_SIZE
#define	RX_BUF_SIZE	256
#endif
#ifndef	RX_RING_SIZE
#define	RX_RING_SIZE	RX_BUF_SIZE
#endif

#define	OUR_INTR_MASK	\
	(INTR_PUN | INTR_SERR | INTR_SWInt | INTR_FOVW | INTR_RDU | \
	INTR_TER | INTR_TOK | INTR_RER | INTR_ROK)

#if defined(sun4u) || defined(CONFIG_TX_COPY)
static int	gani_tx_copy_thresh = INT32_MAX;
#else
static int	gani_tx_copy_thresh = 256;
#endif
#if defined(sun4u) || defined(CONFIG_RX_COPY)
static int	gani_rx_copy_thresh = INT32_MAX;
#else
static int	gani_rx_copy_thresh = 256;
#endif

/*
 * Local device definitions
 */
struct chip_info {
	uint32_t	tcr_val; /* from RTL8169/RTL8168 docs */
	int		flags;
	uint32_t	tcr_mask;
	char		*name;
	uint_t		type;
};

#define	GANI_TYPE_MASK		0xf000U
#define	GANI_TYPE_PCI		0x0000U
#define	GANI_TYPE_PCIE_GIGA	0x1000U
#define	GANI_TYPE_PCIE_FAST	0x2000U

#define	MAC_VER_8169		(0 | GANI_TYPE_PCI)
#define	MAC_VER_8169S		(1 | GANI_TYPE_PCI)
#define	MAC_VER_8110S		(2 | GANI_TYPE_PCI)
#define	MAC_VER_8169SB		(3 | GANI_TYPE_PCI)
#define	MAC_VER_8110SC_D	(4 | GANI_TYPE_PCI)
#define	MAC_VER_8110SC_E	(5 | GANI_TYPE_PCI)

#define	MAC_VER_8168B_B		(0 | GANI_TYPE_PCIE_GIGA)
#define	MAC_VER_8168B_E		(1 | GANI_TYPE_PCIE_GIGA)
#define	MAC_VER_8168B_F		(2 | GANI_TYPE_PCIE_GIGA)
#define	MAC_VER_8168C		(3 | GANI_TYPE_PCIE_GIGA)
#define	MAC_VER_8168C_B		(4 | GANI_TYPE_PCIE_GIGA)
#define	MAC_VER_8168CP		(5 | GANI_TYPE_PCIE_GIGA)

#define	MAC_VER_8101E_B		(0 | GANI_TYPE_PCIE_FAST)
#define	MAC_VER_8101E_C		(1 | GANI_TYPE_PCIE_FAST)

#define	GANI_PCI(x)		\
		(((x) & GANI_TYPE_MASK) == GANI_TYPE_PCI)
#define	GANI_PCIE_GIGA(x)	\
		(((x) & GANI_TYPE_MASK) == GANI_TYPE_PCIE_GIGA)
#define	GANI_PCIE_FAST(x)	\
		(((x) & GANI_TYPE_MASK) == GANI_TYPE_PCIE_FAST)
#define	GANI_PCIE(x)	(GANI_PCIE_GIGA(x) || GANI_PCIE_FAST(x))

static struct chip_info chiptbl_8169[] = {
/* pci gigabit ethernet devices */
	{TCR_HWVERID_8169,	GEM_SPD_1000,	0xfc800000,
				"RTL8169",		MAC_VER_8169},
	{TCR_HWVERID_8169S,	GEM_SPD_1000,	0xfc800000,
				"RTL8169S rev.D",	MAC_VER_8169S},
	{TCR_HWVERID_8110S,	GEM_SPD_1000,	0xfc800000,
				"RTL8110S rev.E",	MAC_VER_8110S},
	{TCR_HWVERID_8169SB,	GEM_SPD_1000,	0xfc800000,
				"RTL8169SB/8110SB",	MAC_VER_8169SB},
	{TCR_HWVERID_8110SC_D,	GEM_SPD_1000,	0xfc800000,
				"RTL8110SC rev.D",	MAC_VER_8110SC_D},
	{TCR_HWVERID_8110SC_E,	GEM_SPD_1000,	0xfc800000,
				"RTL8110SC rev.E",	MAC_VER_8110SC_E},

/* pci express gigabit ethernet devices */
	{TCR_HWVERID_8168B_B,	GEM_SPD_1000,	0x7c800000,
				"RTL8168B/8111B rev.B",	MAC_VER_8168B_B},
	{TCR_HWVERID_8168B_E,	GEM_SPD_1000,	0x7cf00000,
				"RTL8168B/8111B rev.E",	MAC_VER_8168B_E},
	{TCR_HWVERID_8168B_F,	GEM_SPD_1000,	0x7c800000, /* all others */
				"RTL8168B/8111B rev.F",	MAC_VER_8168B_F},
	{TCR_HWVERID_8168C,	GEM_SPD_1000,	0x7cf00000,
				"RTL8168C/8111C",	MAC_VER_8168C},
	{TCR_HWVERID_8168C_B,	GEM_SPD_1000,	0x7c800000, /* all others */
				"RTL8168C/8111C rev.B",	MAC_VER_8168C_B},
	{TCR_HWVERID_8168CP,	GEM_SPD_1000,	0x7c800000,
				"RTL8168CP/8111CP",	MAC_VER_8168CP},

/* pci express fast ethernet devices */
	{TCR_HWVERID_8101E_B,	GEM_SPD_100,	0x7cf00000,
				"RTL8101E rev.B",	MAC_VER_8101E_B},
	{TCR_HWVERID_8101E_C,	GEM_SPD_100,	0x7c800000, /* all others */
				"RTL8101E rev.C",	MAC_VER_8101E_C},
};

#define	CHIPTABLESIZE	(sizeof (chiptbl_8169)/sizeof (struct chip_info))

struct gani_dev {
	/*
	 * Misc HW information
	 */
	struct chip_info	*chip;

	uint8_t			mac[ETHERADDRL];
	uint8_t			busclk;
#define	BUSCLK_PCI33	0
#define	BUSCLK_PCI66	1
#define	BUSCLK_PCIE	2

	uint32_t		rcr;
	uint32_t		tcr;
	boolean_t		need_to_reset;
	boolean_t		last_stats_valid;
	uint16_t		imr;
	boolean_t		msi;

	int			rx_pkt_cnt;
#ifdef GEM_CONFIG_POLLING
	int			last_poll_interval; /* polling interval in nS */
#endif
	uint16_t		adv;
	boolean_t		forced_100hdx;

	struct rtl8169_tally_counters	last_stat;

	/* TPQ optimizer */
	seqnum_t		tx_activated;
	seqnum_t		tx_finished;
#ifdef CONFIG_OPT_TPPOLL
	boolean_t		tx_running;
#endif
#ifdef WA_NO_TPPOLL_WRAP
	int			tx_last_frags;
	boolean_t		tx_no_more;
	int			tx_pended;
#endif
	kmutex_t		stat_lock;
	timeout_id_t		stat_to_id;
};

/*
 * private functions
 */

#ifdef DEBUG_LEVEL
/* debugging support */
static void gani_tx_desc_dump(struct gem_dev *dp);
#endif

/* mii operations */
static void  gani_mii_sync(struct gem_dev *);
static uint16_t gani_mii_read(struct gem_dev *, uint_t);
static void gani_mii_write(struct gem_dev *, uint_t, uint16_t);

/* nic operations */
static int gani_attach_chip(struct gem_dev *);
static int gani_reset_chip(struct gem_dev *);
static int gani_init_chip(struct gem_dev *);
static int gani_start_chip(struct gem_dev *);
static int gani_stop_chip(struct gem_dev *);
static int gani_set_media(struct gem_dev *);
static int gani_set_rx_filter(struct gem_dev *);
static int gani_get_stats(struct gem_dev *);

/* descriptor operations */
static int gani_tx_desc_write(struct gem_dev *dp, int slot,
		    ddi_dma_cookie_t *dmacookie, int frags, uint64_t flag);
static void gani_tx_start(struct gem_dev *dp, int slot, int frags);
static void gani_rx_desc_write(struct gem_dev *dp, int slot,
		    ddi_dma_cookie_t *dmacookie, int frags);
static uint_t gani_tx_desc_stat(struct gem_dev *dp, int slot, int ndesc);
static uint64_t gani_rx_desc_stat(struct gem_dev *dp, int slot, int ndesc);

static void gani_tx_desc_init(struct gem_dev *dp, int slot);
static void gani_rx_desc_init(struct gem_dev *dp, int slot);

/* interrupt handler */
static uint_t gani_interrupt(struct gem_dev *dp);

/* ======================================================== */

/* mapping attributes */
/* Data access requirements. */
static struct ddi_device_acc_attr gani_dev_attr = {
	DDI_DEVICE_ATTR_V0,
	DDI_STRUCTURE_LE_ACC,
	DDI_STRICTORDER_ACC
};

/* On sparc, the buffers should be native endianness */
static struct ddi_device_acc_attr gani_buf_attr = {
	DDI_DEVICE_ATTR_V0,
	DDI_NEVERSWAP_ACC,	/* native endianness */
	DDI_STRICTORDER_ACC
};

static ddi_dma_attr_t gani_dma_attr_buf32 = {
	DMA_ATTR_V0,		/* dma_attr_version */
	0,			/* dma_attr_addr_lo */
	0xffffffffull,		/* dma_attr_addr_hi */
	0x3fffull,		/* dma_attr_count_max */
	1,			/* dma_attr_align */
	0x3fff,			/* dma_attr_burstsizes */
	1,			/* dma_attr_minxfer */
	0x3fffull,		/* dma_attr_maxxfer */
	0xffffffffull,		/* dma_attr_seg */
	0 /* pached later */,	/* dma_attr_sgllen */
	1,			/* dma_attr_granular */
	0			/* dma_attr_flags */
};

static ddi_dma_attr_t gani_dma_attr_buf64 = {
	DMA_ATTR_V0,		/* dma_attr_version */
	0,			/* dma_attr_addr_lo */
	0xffffffffffffull,	/* dma_attr_addr_hi */
	0x3fffull,		/* dma_attr_count_max */
	1,			/* dma_attr_align */
	0x3fff,			/* dma_attr_burstsizes */
	1,			/* dma_attr_minxfer */
	0x3fffull,		/* dma_attr_maxxfer */
	0xffffffffffffull,	/* dma_attr_seg */
	0 /* pached later */,	/* dma_attr_sgllen */
	1,			/* dma_attr_granular */
	0			/* dma_attr_flags */
};

static ddi_dma_attr_t gani_dma_attr_desc = {
	DMA_ATTR_V0,		/* dma_attr_version */
	0,			/* dma_attr_addr_lo */
	0xffffffffull,		/* dma_attr_addr_hi */
	0xffffffffull,		/* dma_attr_count_max */
	DESC_BASE_ALIGN,	/* dma_attr_align */
	0,			/* dma_attr_burstsizes */
	1,			/* dma_attr_minxfer */
	0xffffffffull,		/* dma_attr_maxxfer */
	0xffffffffull,		/* dma_attr_seg */
	1,			/* dma_attr_sgllen */
	1,			/* dma_attr_granular */
	0			/* dma_attr_flags */
};

/* =============================================================== */
/*
 * Debugging support
 */
/* =============================================================== */
#ifdef DEBUG_HANG
static void
gani_dump_regs(struct gem_dev *dp, char *m)
{
	int		i;

	cmn_err(CE_CONT, "!%s: register dump (%s)", dp->name, m);

	for (i = 0; i < 256; i += 8) {
		cmn_err(CE_CONT,
		    "!%02x: %02x %02x %02x %02x %02x %02x %02x %02x",
		    i,
		    INB(dp, i+0), INB(dp, i+1),
		    INB(dp, i+2), INB(dp, i+3),
		    INB(dp, i+4), INB(dp, i+5),
		    INB(dp, i+6), INB(dp, i+7));
	}
}
#endif
/* =============================================================== */
/*
 * Hardware manupilation
 */
/* =============================================================== */
static uint16_t
gani_ephy_read(struct gem_dev *dp, uint_t location)
{
	int	i;

	OUTL(dp, PHYAR, location << PHYAR_REGADDR_SHIFT);

	drv_usecwait(100);

	for (i = 0; (INL(dp, PHYAR) & PHYAR_FLAG) == 0; i++) {
		if (i > 10) {
			cmn_err(CE_CONT, "%s: %s: timeout",
			    dp->name, __func__);
			return (0);
		}
		drv_usecwait(100);
	}

	return (INL(dp, PHYAR_DATA) & 0xffff);
}

static void
gani_ephy_write(struct gem_dev *dp, uint_t location, uint16_t val)
{
	OUTL(dp, PHYAR,
	    PHYAR_FLAG | (location << PHYAR_REGADDR_SHIFT) | val);
}

static int
gani_reset_chip(struct gem_dev *dp)
{
	int		i;
	struct gani_dev	*lp = (struct gani_dev *)dp->private;

	DPRINTF(0, (CE_CONT, "!%s: %s: called", dp->name, __func__));
#ifdef DEBUG_HANG
	gani_dump_regs(dp, "reset_chip 1");
#endif
	/* disable interrupts */
	OUTW(dp, IMR, 0);
	FLSHW(dp, IMR);

	switch (lp->chip->type) {
	case MAC_VER_8168C:
	case MAC_VER_8168CP:
		OUTB(dp, CR, CR_STOP | CR_RE | CR_TE);
		drv_usecwait(100);
		break;
	}

	OUTB(dp, CR, CR_RST);

	for (i = 0; INB(dp, CR) & CR_RST; i++) {
		if (i > 100) {
			/* time out */
			cmn_err(CE_WARN, "!%s: failed to reset: timeout",
			    dp->name);
			return (GEM_FAILURE);
		}
		drv_usecwait(10);
	}

	/* clear bogus interrupts */
	OUTW(dp, ISR, 0xffff);
	FLSHW(dp, ISR);

	switch (lp->chip->type) {
	case MAC_VER_8169S:
		OUTB(dp, 0x82, 0x01);
		break;
	}

#ifdef DEBUG_HANG
	gani_dump_regs(dp, "reset_chip 2");
#endif
	return (GEM_SUCCESS);
}

/*
 * Setup rtl8169
 */
static int
gani_init_chip(struct gem_dev *dp)
{
	uint32_t		val;
	ddi_acc_handle_t	conf_ha;
	struct gani_dev	*lp = (struct gani_dev *)dp->private;

	DPRINTF(0, (CE_CONT, "!%s: %s: called", dp->name, __func__));

	if (pci_config_setup(dp->dip, &conf_ha) != DDI_SUCCESS) {
		cmn_err(CE_WARN, "!%s: pci_config_setup failed", dp->name);
		return (GEM_FAILURE);
	}

	/* XXX - disable interrupts */
	OUTW(dp, IMR, 0);
	FLSHW(dp, IMR);

	/* make configuration registers writable */
	OUTB(dp, CR9346, CR9346_EEM_WE);

	OUTB(dp, ETThR, 0x3f);
	OUTW(dp, RMS, 16383);

	DPRINTF(2, (CE_CONT, "!%s: RMS %d", dp->name, INW(dp, RMS)));

	/* fix pci configuration registers */
	if (GANI_PCI(lp->chip->type)) {
		/* based on r8169-6.003.00 */
		pci_config_put8(conf_ha, PCI_CONF_CACHE_LINESZ, 8);
		pci_config_put8(conf_ha, PCI_CONF_LATENCY_TIMER, 0x40);

		if (lp->busclk == BUSCLK_PCI66) {
			if (lp->chip->type == MAC_VER_8110SC_D) {
				OUTL(dp, 0x7c, 0x000fffff);
			} else if (lp->chip->type == MAC_VER_8110SC_E) {
				OUTL(dp, 0x7c, 0x00ffffff);
			}
		} else {
			if (lp->chip->type == MAC_VER_8110SC_D) {
				OUTL(dp, 0x7c, 0x000fff00);
			} else if (lp->chip->type == MAC_VER_8110SC_E) {
				OUTL(dp, 0x7c, 0x00ffff00);
			}
		}
	}

	/* configure CPlus command register */
	val = INW(dp, CpCR);
	if (GANI_PCI(lp->chip->type)) {
		val |= CpCR_MulRW;	/* CpCR */
	} else if (GANI_PCIE_GIGA(lp->chip->type)) {
		val |= CpCR_StatDis | CpCR_INTT_1;	/* CpCR */
	}

#ifdef GEM_CONFIG_VLAN
	/* common capability for CpCR */
	val |= CpCR_RxVLAN;
#ifdef GEM_CONFIG_CKSUM_OFFLOAD
	val |= CpCR_RxChkSum;
#endif
#endif
	OUTW(dp, CpCR, val);

	switch (lp->chip->type) {
	case MAC_VER_8169S:
	case MAC_VER_8110S:
		val |= 1 << 14;
		break;
	}
	OUTW(dp, CpCR, val);

	/* XXX - undocumented */
#ifdef TEST_REG_E2
	OUTW(dp, 0xe2, GANI_PCIE_GIGA(lp->chip->type) ? 0x5151 : 0x282a);
#else
	OUTW(dp, 0xe2, GANI_PCIE_GIGA(lp->chip->type) ? 0x5151 : 0);
#endif

	/* Transmit Normal Priority Descriptors */
	DPRINTF(4, (CE_CONT, "!%s: TNPDS 0x%llx",
	    dp->name, (unsigned long long)dp->tx_ring_dma));
	OUTL(dp, TNPDSL, (uint32_t)dp->tx_ring_dma);
	OUTL(dp, TNPDSH, (uint32_t)(dp->tx_ring_dma >> 32));

	/* Transmit High Priority Descriptors: Do nothing */
	OUTL(dp, THPDSL, 0);
	OUTL(dp, THPDSH, 0);

	/* Receive Descriptor Start Address register */
	OUTL(dp, RDSARL, (uint32_t)dp->rx_ring_dma);
	OUTL(dp, RDSARH, (uint32_t)(dp->rx_ring_dma >> 32));
	DPRINTF(4, (CE_CONT, "!%s: RDSAR 0x%llx",
	    dp->name, (unsigned long long)dp->rx_ring_dma));


	if (GANI_PCI(lp->chip->type) || GANI_PCIE_GIGA(lp->chip->type)) {
		/* Missed packet counter: clear it */
		OUTL(dp, MPC, 0);
	}

	if (!GANI_PCIE_GIGA(lp->chip->type)) {
		/* need to enable tx and rx before writing rcr and tcr */
		OUTB(dp, CR, CR_RE | CR_TE);
	}

	OUTL(dp, RCR, lp->rcr);
	OUTL(dp, TCR, lp->tcr);

	/* Interrupt status register: clear bogus interrupts */
	OUTW(dp, ISR, 0xffff);
	FLSHW(dp, ISR);

	/* MulInt Register */
	OUTW(dp, MULINT, INW(dp, MULINT) & 0xf000);

	switch (lp->chip->type) {
	case MAC_VER_8168C:
		/* XXX - not implemented yet */
		OUTL(dp, CSIDR, 0x27000000);
		OUTL(dp, CSIAR, 0x8000870C);
		OUTB(dp, DBGREG,
		    (0xe << 4) | DBGREG_FIX_NAK_1 | DBGREG_FIX_NAK_2);

		gani_ephy_write(dp, 2,
		    (gani_ephy_read(dp, 2) & ~0x0800) | 0x1000);
		gani_ephy_write(dp, 3, gani_ephy_read(dp, 3) | 0x0002);
		gani_ephy_write(dp, 6, gani_ephy_read(dp, 6) & ~0x0080);

		pci_config_put8(conf_ha, 0x79,
		    (pci_config_get8(conf_ha, 0x79) & ~0x70) | 0x50);

		OUTB(dp, CFG1,
		    CFG1_LEDS | CFG1_SPEEDDOWN | CFG1_IOMAP | CFG1_MEMMAP |
		    CFG1_VPD | CFG1_PMEn);

		OUTW(dp, RMS, 0x5f3);

		OUTB(dp, CFG3, INB(dp, CFG3) & ~CFG3_BEACON_EN);

		pci_config_put8(conf_ha, 0x81, 0);

		OUTW(dp, CpCR, INW(dp, CpCR) &
		    ~(CpCR_BIST | CpCR_Macdbgo_oe | CpCR_HALPDUP |
		    CpCR_RXFLOW | CpCR_TXFLOW |
		    CpCR_CXPL | CpCR_ASF | CpCR_StatDis |
		    CpCR_Macdbgo_sel));
		break;

	case MAC_VER_8168C_B:
		/* XXX - not implemented yet */
		OUTL(dp, CSIDR, 0x27000000);
		OUTL(dp, CSIAR, 0x8000870C);

		pci_config_put8(conf_ha, 0x79,
		    (pci_config_get8(conf_ha, 0x79) & ~0x70) | 0x50);
		OUTB(dp, CFG1,
		    CFG1_LEDS | CFG1_SPEEDDOWN | CFG1_IOMAP | CFG1_MEMMAP |
		    CFG1_VPD | CFG1_PMEn);

		OUTW(dp, RMS, 0x5f3);

		OUTB(dp, CFG3, INB(dp, CFG3) & ~CFG3_BEACON_EN);

		pci_config_put8(conf_ha, 0x81, 0);

		OUTW(dp, CpCR, INW(dp, CpCR) &
		    ~(CpCR_BIST | CpCR_Macdbgo_oe | CpCR_HALPDUP |
		    CpCR_RXFLOW | CpCR_TXFLOW |
		    CpCR_CXPL | CpCR_ASF | CpCR_StatDis |
		    CpCR_Macdbgo_sel));
		break;

	case MAC_VER_8168CP:
		/* XXX - not implemented yet */
		OUTL(dp, CSIDR, 0x27000000);
		OUTL(dp, CSIAR, 0x8000870C);

		OUTB(dp, DBGREG, 0x23);

		pci_config_put8(conf_ha, 0x79,
		    (pci_config_get8(conf_ha, 0x79) & ~0x70) | 0x50);

		OUTB(dp, CFG1,
		    CFG1_LEDS | CFG1_SPEEDDOWN | CFG1_IOMAP | CFG1_MEMMAP |
		    CFG1_VPD | CFG1_PMEn);

		OUTW(dp, RMS, 0x5f3);

		gani_ephy_write(dp, 1, gani_ephy_read(dp, 1) & 0x0001);
		gani_ephy_write(dp, 2,
		    (gani_ephy_read(dp, 2) & ~0x0800) | 0x1000);
		gani_ephy_write(dp, 3, gani_ephy_read(dp, 3) | 0x0042);
		gani_ephy_write(dp, 6, gani_ephy_read(dp, 6) & ~0x0080);
		gani_ephy_write(dp, 7, gani_ephy_read(dp, 7) | 0x2000);

		OUTB(dp, CFG3, INB(dp, CFG3) & ~CFG3_BEACON_EN);

		pci_config_put8(conf_ha, 0x81, 0);

		OUTW(dp, CpCR, INW(dp, CpCR) &
		    ~(CpCR_BIST | CpCR_Macdbgo_oe | CpCR_HALPDUP |
		    CpCR_RXFLOW | CpCR_TXFLOW |
		    CpCR_CXPL   | CpCR_ASF    | CpCR_StatDis |
		    CpCR_Macdbgo_sel));
		break;

	case MAC_VER_8168B_B:
	case MAC_VER_8168B_E:
	case MAC_VER_8168B_F:
		/* register @69 in pci config space is 0x28 (default) */
		DPRINTF(2, (CE_CONT, "%s: %s: pci_conf69:%x",
		    dp->name, __func__, pci_config_get8(conf_ha, 0x69)));
#ifdef NEVER
		/*
		 * XXX - r8168-8.003.00 use following setteng,
		 * but it caused to hang system.
		 */
		pci_config_put8(conf_ha, 0x69,
		    (pci_config_get8(conf_ha, 0x69) & ~0x70) | 0x50);
#else
		/* set default value 0x20, or 0x30, but 0x40 cause problem */
		pci_config_put8(conf_ha, 0x69,
		    (pci_config_get8(conf_ha, 0x69) & ~0x70) | 0x30);
#endif
		break;
	}

	if (GANI_PCIE_GIGA(lp->chip->type)) {
		/* enable tx and rx */
		OUTB(dp, CR, CR_RE | CR_TE);
	}

	/* make config registers read only */
	OUTB(dp, CR9346, CR9346_EEM_NORMAL);
	drv_usecwait(10);

	/* TimerInt Register */
	OUTL(dp, TimerInt, 0);

	/* Timer count register: test count rate */
	OUTL(dp, TCTR, 0);
#if DEBUG_LEVEL > 3
	drv_usecwait(1000);
	cmn_err(CE_CONT, "!%s: TCTR:%d in 1mS", dp->name, INL(dp, TCTR));
#endif
#ifdef DEBUG_HANG
	gani_dump_regs(dp, "init_chip done");
#endif
#ifdef GEM_CONFIG_POLLING
	lp->last_poll_interval = 0; /* polling interval in nS */
#endif
#ifdef CONFIG_OPT_TPPOLL
	lp->tx_running   = B_FALSE;
#endif
	lp->tx_activated = 0;
	lp->tx_finished  = 0;
#ifdef WA_NO_TPPOLL_WRAP
	lp->tx_no_more   = B_FALSE;
	lp->tx_pended    = 0;
#endif
	lp->last_stats_valid = B_FALSE;

	pci_config_teardown(&conf_ha);

	return (GEM_SUCCESS);
}

static uint_t
gani_mcast_hash(struct gem_dev *dp, uint8_t *addr)
{
	return (gem_ether_crc_be(addr, ETHERADDRL));
}

static int
gani_set_rx_filter(struct gem_dev *dp)
{
	uint32_t	mode;
	uint32_t	mhash[2];
	int		i;
	uint8_t		*m;
	uint8_t		reg;
	struct gani_dev	*lp = (struct gani_dev *)dp->private;

	DPRINTF(1, (CE_CONT, "!%s: %s: called", dp->name, __func__));

	mode = RCR_AB	/* accept broadcast */
	    | RCR_APM; 	/* accept physical match  */
#ifdef notdef
	mode |= RCR_AER | RCR_AR | RCR_RER8; /* accept error and runt packets */
#endif

	mhash[0] = mhash[1] = 0;

	if ((dp->rxmode & RXMODE_ENABLE) == 0) {
		mode = 0;

	} else if (dp->rxmode & RXMODE_PROMISC) {
		/* promiscious mode implies all multicast and all physical */
		mode |= RCR_AM | RCR_AAP;
		mhash[0] = mhash[1] = 0xffffffff;

	} else if ((dp->rxmode & RXMODE_ALLMULTI) || dp->mc_count > 32) {
		/* accept all multicast packets */
		mode |= RCR_AM;
		mhash[0] = mhash[1] = 0xffffffff;

	} else if (dp->mc_count > 0) {
		mode |= RCR_AM;
		/*
		 * make hash table to select interresting
		 * multicast address only.
		 */
		for (i = 0; i < dp->mc_count; i++) {
			uint_t	h;
			/* hash table is 64 = 2^6 bit width */
			h = dp->mc_list[i].hash >> (32 - 6);
			mhash[h / 32] |= 1 << (h % 32);
		}
	}

#ifdef notdef
	lp->rcr &= ~(RCR_ACCEPT_MODE | RCR_RER8);

	if (dp->mac_active) {
		/*
		 * disable all kind of rx filters to stop rx before
		 * changing mac address and/or multicast hash table.
		 */
		OUTL(dp, RCR, lp->rcr);
		FLSHL(dp, RCR);
	}
#endif
	m = &dp->cur_addr.ether_addr_octet[0];
	if (bcmp(m, lp->mac, ETHERADDRL)) {
		/*
		 * XXX - make config registers writable before
		 * changing IDRs. (undocumented)
		 */
		reg = INB(dp, CR9346);
		OUTB(dp, CR9346, CR9346_EEM_WE);

		/* set mac address */
		OUTL(dp, IDR + 0,
		    (m[3] << 24) | (m[2] << 16) | (m[1] << 8) | m[0]);
#if 0
		if (lp->chip->type == MAC_VER_8110SC /* M5 */) {
			drv_usecwait(1000);
		}
#endif
		OUTL(dp, IDR + 4, (m[5] <<  8) | m[4]);

		OUTB(dp, CR9346, reg);
		drv_usecwait(10);
	}

	if (mode & RCR_AM) {
		/* need to set up multicast hash table */
		OUTL(dp, MAR + 4, mhash[1]);
		OUTL(dp, MAR + 0, mhash[0]);
	}

	/* update rcr */
	OUTL(dp, RCR, lp->rcr | mode);

	DPRINTF(4, (CE_CONT, "!%s: returned", __func__));
#ifdef DEBUG_HANG
	gani_dump_regs(dp, "set_rxfilter done");
#endif

	return (GEM_SUCCESS);
}


#define	MII_ABILITY_SPEED_DUPLEX	\
	(MII_ABILITY_100BASE_T4	|	\
	MII_ABILITY_100BASE_TX_FD |	\
	MII_ABILITY_100BASE_TX |	\
	MII_ABILITY_10BASE_T |	\
	MII_ABILITY_10BASE_T_FD)

static int
gani_set_media(struct gem_dev *dp)
{
	struct gani_dev	*lp = (struct gani_dev *)(dp)->private;

	DPRINTF(0, (CE_CONT, "!%s: %s: phys: %b, mac_active: %d",
	    dp->name, __func__, INB(dp, PHYS), PHYS_BITS, dp->mac_active));


	switch (lp->chip->type) {
	case MAC_VER_8168B_B:
	case MAC_VER_8168B_E:
	case MAC_VER_8168B_F:
		/* select page 1 */
		gani_mii_write(dp, 0x1f, 1);

		if (dp->speed == GEM_SPD_1000 && dp->full_duplex) {
			gani_mii_write(dp, 0x10, 0xf01b);
		} else {
			gani_mii_write(dp, 0x10, 0xf41b);
		}

		/* return to page 0 */
		gani_mii_write(dp, 0x1f, 0);
		break;
	}

	return (GEM_SUCCESS);
}

static int
gani_start_chip(struct gem_dev *dp)
{
	struct gani_dev	*lp = (struct gani_dev *)dp->private;

	DPRINTF(0, (CE_CONT, "!%s: %s: called", dp->name, __func__));

	ASSERT(dp->mii_state == MII_STATE_LINKUP ||
	    dp->mii_state == MII_STATE_LINKDOWN);

	/* prepare to dump Tally Count Register : */
	OUTL(dp, DTCCRH, (uint32_t)(TALLY_DMA_ADDR(dp) >> 32));
#ifdef SANITY
	OUTL(dp, DTCCRL, 0);
#endif
	/* clear tally counter area */
	DPRINTF(2, (CE_CONT, "!%s: tally base: vaddr:0x%p, dma addr:0x%llx",
	    dp->name, TALLY_VADDR(dp),
	    (unsigned long long)TALLY_DMA_ADDR(dp)));
	bzero(TALLY_VADDR(dp), TC_SIZE);


	/* Enable interrupts */
	lp->imr = OUR_INTR_MASK;
#ifdef CONFIG_OPT_TPPOLL
	lp->imr |= INTR_TDU;
#endif
#ifdef GEM_CONFIG_POLLING
	lp->imr |= INTR_TimeOut;
#endif
	if ((dp->misc_flag & GEM_NOINTR) == 0) {
		OUTW(dp, IMR, lp->imr);
		FLSHW(dp, IMR);
	}
#ifdef DEBUG_HANG
	gani_dump_regs(dp, "start_chip done");
#endif
	return (GEM_SUCCESS);
}

/*
 * gani_stop_chip: disable interrupts and ensure rx has stopped.
 */
static int
gani_stop_chip(struct gem_dev *dp)
{
	int		i;

	DPRINTF(0, (CE_CONT, "!%s: %s: called", dp->name, __func__));
#if DEBUG_LEVEL > -1
	if (dp->tx_desc_head != dp->tx_desc_tail) {
		gani_tx_desc_dump(dp);
	}
#endif
	/* wait for dumping tally counters stops. */
	for (i = 0; INL(dp, DTCCRL) & DTCCR_CMD; i++) {
		if (i > 100) {
			cmn_err(CE_WARN, "!%s: timeout: dumping tally counters",
			    dp->name);
			break;
		}
		drv_usecwait(10);
	}

	/* disable interrupts */
	OUTW(dp, IMR, 0);
	FLSHW(dp, IMR);

	/* disable RX and TX */
	OUTB(dp, CR, 0);
	FLSHB(dp, CR);

	if (dp->speed == GEM_SPD_10) {
		drv_usecwait(2000);
	} else {
		drv_usecwait(200);
	}
#ifdef notdef
	/* clear bogus interrupts */
	OUTW(dp, ISR, 0xffff);
	FLSHW(dp, ISR);
#endif
	/* XXX - don't clear pended interrupts */
#ifdef DEBUG_HANG
	gani_dump_regs(dp, "stop_chip done");
#endif
	return (GEM_SUCCESS);
}

/* private function */
static boolean_t
gani_update_stats(struct gem_dev *dp)
{
	uint32_t			x;
	struct rtl8169_tally_counters	*tbp;
	struct rtl8169_tally_counters	*ls;
	struct rtl8169_tally_counters	new;
	struct gani_dev			*lp = dp->private;

	DPRINTF(4, (CE_CONT, "!%s: %s: called", dp->name, __func__));

	ASSERT(mutex_owned(&lp->stat_lock));

	if (!dp->mac_active) {
		/* nic isn't running yet */
		return (B_FALSE);
	}

	if (INL(dp, DTCCRL) & DTCCR_CMD) {
		/* Now dumping tally counters, do nothing */
		return (B_FALSE);
	}

	(void) ddi_dma_sync(dp->desc_dma_handle,
	    (off_t)TALLY_OFFSET(dp), (size_t)TC_SIZE, DDI_DMA_SYNC_FORKERNEL);

	tbp = TALLY_VADDR(dp);

	new.tc_txok = LE_64(tbp->tc_txok);		/* 8byte */
	new.tc_rxok = LE_64(tbp->tc_rxok);		/* 8byte */
	new.tc_txer = LE_64(tbp->tc_txer);		/* 8byte */
	new.tc_rxer = LE_32(tbp->tc_rxer);		/* 4byte */
	new.tc_misspkt = LE_16(tbp->tc_misspkt);	/* 2byte */
	new.tc_fae = LE_16(tbp->tc_fae);		/* 2byte */
	new.tc_tx1col = LE_32(tbp->tc_tx1col);		/* 4byte */
	new.tc_txmcol = LE_32(tbp->tc_txmcol);		/* 4byte */
	new.tc_rxokphy = LE_64(tbp->tc_rxokphy);	/* 8byte */
	new.tc_rxokbrd = LE_64(tbp->tc_rxokbrd);	/* 8byte */
	new.tc_rxokmu = LE_32(tbp->tc_rxokmu);		/* 4byte */
	new.tc_txabt = LE_16(tbp->tc_txabt);		/* 2byte */
	new.tc_txundrn = LE_16(tbp->tc_txundrn);	/* 2byte */

	if (lp->last_stats_valid) {
		ls = &lp->last_stat;
		dp->stats.errxmt += new.tc_txer - ls->tc_txer;
		dp->stats.errrcv += new.tc_rxer - ls->tc_rxer;
		dp->stats.missed += new.tc_misspkt - ls->tc_misspkt;
		dp->stats.frame += new.tc_fae - ls->tc_fae;
		dp->stats.first_coll +=	x = new.tc_tx1col - ls->tc_tx1col;
		dp->stats.collisions +=	x;
		dp->stats.multi_coll +=	x = new.tc_txmcol - ls->tc_txmcol;
		dp->stats.collisions +=	x*2;
		dp->stats.excoll += new.tc_txabt - ls->tc_txabt;
		dp->stats.underflow += new.tc_txundrn - ls->tc_txundrn;
	}
	lp->last_stat = new;
	lp->last_stats_valid = B_TRUE;

	/* issue Dump_Tally_Counters_Cmd for the next call */
	bzero(tbp, sizeof (struct rtl8169_tally_counters));
	OUTL(dp, DTCCRL, DTCCR_CMD | (uint32_t)TALLY_DMA_ADDR(dp));

	return (B_TRUE);
}

/* private function */
static void
gani_stat_timeout(void *arg)
{
	struct gem_dev	*dp = (struct gem_dev *)arg;
	struct gani_dev	*lp = (struct gani_dev *)dp->private;

	mutex_enter(&lp->stat_lock);
	(void) gani_update_stats(dp);
	lp->stat_to_id = timeout(gani_stat_timeout, dp, ONESEC);
	mutex_exit(&lp->stat_lock);
}

static int
gani_get_stats(struct gem_dev *dp)
{
	struct gani_dev	*lp = (struct gani_dev *)dp->private;

	DPRINTF(4, (CE_CONT, "!%s: %s: called", dp->name, __func__));

	mutex_enter(&lp->stat_lock);
	(void) gani_update_stats(dp);
	mutex_exit(&lp->stat_lock);

	return (GEM_SUCCESS);
}

/*
 * discriptor  manupiration
 */
static int
gani_tx_desc_write(struct gem_dev *dp, int slot,
		ddi_dma_cookie_t *dmacookie, int frags, uint64_t flag)
{
	int			i;
	struct tx_desc		*tdp;
	uint32_t		mark;
	uint_t			vlan_tag;
	struct gani_dev		*lp = (struct gani_dev *)dp->private;
	int			curslot;
#if TX_MAX_FRAGS > 1
#ifdef WA_NO_TPPOLL_WRAP
	int			pad = 0;
#endif
#endif
#if DEBUG_LEVEL > 2
	cmn_err(CE_CONT,
	    "!%s: %s: seqnum %d, slot %d, frags %d flag 0x%llx",
	    dp->name, __func__, dp->tx_active_tail, slot, frags,
	    (unsigned long long)flag);
	for (i = 0; i < frags; i++) {
		cmn_err(CE_CONT, "!%d: addr 0x%x, len 0x%x",
		    i, dmacookie[i].dmac_address, dmacookie[i].dmac_size);
	}
#endif
	/*
	 * write tx descriptor(s) in reversed order
	 */
	mark = TXD0_OWN | TXD0_LS;
#ifdef GEM_CONFIG_CKSUM_OFFLOAD
	if (flag & GEM_TXFLAG_IPv4) {
		mark |= TXD0_IPCS;
	}
	if (flag & GEM_TXFLAG_TCP) {
		mark |= TXD0_TCPCS;
	} else if (flag & GEM_TXFLAG_UDP) {
		mark |= TXD0_UDPCS;
	}
#endif
	vlan_tag = 0;
#ifdef GEM_CONFIG_VLAN
	if (flag & GEM_TXFLAG_VTAG) {
		uint32_t	vtag;
		vtag = (flag & GEM_TXFLAG_VTAG) >> GEM_TXFLAG_VTAG_SHIFT;
		vlan_tag |= TXD1_TAGC | TXD1_VID(vtag);
	}
#endif

#if TX_MAX_FRAGS > 1
#ifdef WA_NO_TPPOLL_WRAP
	ASSERT(slot + frags <= TX_RING_SIZE);

	if (TX_RING_SIZE - (slot + frags) <
	    dp->gc.gc_tx_max_descs_per_pkt) {
		/*
		 * Calculate the number of required pad to fake upper
		 * layer that the last descriptor just ends at to the
		 * end of tx ring.
		 */
		pad = TX_RING_SIZE - (slot + frags);

		/*
		 * we also must tell actual end of the descriptors
		 * to the nic hardware.
		 */
		mark |= TXD0_EOR;
	}

	if (slot + frags + pad == TX_RING_SIZE) {
		/* record the number of fragments at the end of tx ring  */
		lp->tx_last_frags = frags;
	}
#endif /* WA_NO_TPPOLL_WRAP */

	for (i = frags - 1; i > 0; i--) {

		curslot = SLOT(slot + i, TX_RING_SIZE);

		/*
		 * specify descriptor control flags
		 */
		if (curslot == TX_RING_SIZE - 1) {
			mark |= TXD0_EOR;
		}
		tdp = &TXDESC(dp->tx_ring)[curslot];
		tdp->txd3 = LE_32(dmacookie[i].dmac_laddress >> 32);
		tdp->txd2 = LE_32(dmacookie[i].dmac_laddress);
		tdp->txd1 = LE_32(vlan_tag);
		tdp->txd0 = LE_32(mark | (uint32_t)dmacookie[i].dmac_size);
		mark &= ~(TXD0_LS | TXD0_EOR);
	}
#endif
	/*
	 * specify descriptor control flags for first fragment.
	 */
	mark |= TXD0_FS;
	if (flag & GEM_TXFLAG_HEAD) {
		mark &= ~TXD0_OWN;
	}
	if (slot == TX_RING_SIZE - 1) {
		mark |= TXD0_EOR;
	}

	tdp = &TXDESC(dp->tx_ring)[slot];
	tdp->txd3 = LE_32(dmacookie->dmac_laddress >> 32);
	tdp->txd2 = LE_32(dmacookie->dmac_laddress);
	tdp->txd1 = LE_32(vlan_tag);
	tdp->txd0 = LE_32(mark | (uint32_t)dmacookie->dmac_size);

#if TX_MAX_FRAGS > 1
#ifdef WA_NO_TPPOLL_WRAP
	DPRINTF(3, (CE_CONT, "\t\t\t frags:%d pad:%d", frags, pad));
	frags += pad;
#endif
#endif
	return (frags);
}

static void
gani_tx_start(struct gem_dev *dp, int start_slot, int nslot)
{
	uint32_t	own;
	struct gani_dev	*lp = (struct gani_dev *)dp->private;

	DPRINTF(3, (CE_CONT, "!%s: %s: start_slot %d, nslot %d",
	    dp->name, __func__, start_slot, nslot));

	ASSERT(nslot > 0);

	own = LE_32(TXD0_OWN);

#ifdef CONFIG_OPT_TPPOLL
#ifdef WA_NO_TPPOLL_WRAP
	if (lp->tx_no_more) {
		/* record pended requests */
		lp->tx_pended += nslot;

		/* merge this to current tx list */
		if (start_slot != 0) {
			TXDESC(dp->tx_ring)[start_slot].txd0 |= own;
		}
		return;
	}

	if (start_slot + nslot >= TX_RING_SIZE) {
		lp->tx_no_more = B_TRUE;
		lp->tx_pended  = start_slot + nslot - TX_RING_SIZE;
		nslot = TX_RING_SIZE - start_slot;

		/* break at the head of the ring to avoid tppoll wrapping */
		if (start_slot + nslot > TX_RING_SIZE) {
			TXDESC(dp->tx_ring)[0].txd0 &= ~own;
		}
	}
#endif /* WA_NO_TPPOLL_WRAP */
#endif /* CONFIG_OPT_TPPOLL */
	lp->tx_activated += nslot;

	if (nslot > 1) {
		gem_tx_desc_dma_sync(dp,
		    SLOT(start_slot + 1, TX_RING_SIZE),
		    nslot - 1, DDI_DMA_SYNC_FORDEV);
	}

	TXDESC(dp->tx_ring)[start_slot].txd0 |= own;
	gem_tx_desc_dma_sync(dp, start_slot, 1, DDI_DMA_SYNC_FORDEV);

	if (dp->mac_active) {
		/* kick Tx engine */
#ifdef CONFIG_OPT_TPPOLL
		if (!lp->tx_running) {
			OUTB(dp, TPPoll, TPPoll_NPQ);
			lp->tx_running = B_TRUE;
		}
#else
		OUTB(dp, TPPoll, TPPoll_NPQ);
#endif
	}
}

static void
gani_rx_desc_write(struct gem_dev *dp, int slot,
		ddi_dma_cookie_t *dmacookie, int frags)
{
	uint32_t		mark;
	struct rx_desc		*rdp;

#if DEBUG_LEVEL > 4
{
	int	i;
	cmn_err(CE_CONT,
	    "!%s: %s: seqnum %d, slot %d, frags %d",
	    dp->name, __func__, dp->rx_desc_tail, slot, frags);
	for (i = 0; i < frags; i++) {
		cmn_err(CE_CONT, "!%d: addr 0x%x, len 0x%x",
		    i, dmacookie[i].dmac_address, dmacookie[i].dmac_size);
	}
}
#endif
	mark = RXD0_OWN;
	if (slot == RX_RING_SIZE - 1) {
		mark = RXD0_OWN | RXD0_EOR;
	}

	rdp = &RXDESC(dp->rx_ring)[slot];

	rdp->rxd3 = LE_32(dmacookie->dmac_laddress >> 32);
	rdp->rxd2 = LE_32(dmacookie->dmac_laddress);
	rdp->rxd1 = 0;
	rdp->rxd0 = LE_32(mark | (uint32_t)dmacookie->dmac_size);
}

static uint_t
gani_tx_desc_stat(struct gem_dev *dp, int slot, int ndesc)
{
	uint32_t	tsr;
	struct tx_desc	*tdp;
	struct gani_dev	*lp = (struct gani_dev *)dp->private;
	int		frags = ndesc;

#ifdef WA_NO_TPPOLL_WRAP
	ASSERT(lp->tx_finished - lp->tx_activated <= 0);
	if (lp->tx_finished == lp->tx_activated) {
		/* we don't have unfinished tx descriptors now. */
		return (0);
	}
#if TX_MAX_FRAGS > 1
	if (slot + ndesc == TX_RING_SIZE) {
		/* need to get actual number of fragnents for the packet */
		frags = lp->tx_last_frags;
	}
#endif
#endif
	/* XXX - we must check last descripor of the packet. */
	tdp = &TXDESC(dp->tx_ring)[SLOT(slot + frags - 1, TX_RING_SIZE)];

	tsr = LE_32(tdp->txd0);
#ifndef lint
	DPRINTF(2, (CE_CONT,
	    "!%s: %s: slot:%d ndesc:%d isr:%b tsr:%b",
	    dp->name, __func__, slot, ndesc,
	    INW(dp, ISR), INTR_BITS, tsr, TXD0_BITS));
#endif
	if (tsr & TXD0_OWN) {
		/* not transmitted yet */
		return (0);
	}

	lp->tx_finished += ndesc;

#if DEBUG_LEVEL >= 0
	if (slot + ndesc != TX_RING_SIZE && (tsr & TXD0_EOR)) {
		/* the descriptor is corrupted */
#ifndef lint
		cmn_err(CE_WARN,
		    "!%s: %s: tx descriptor corrupted, slot:%d ndesc:%d tsr:%b",
		    dp->name, __func__, slot, ndesc, tsr, TXD0_BITS);
#endif
		return (GEM_TX_DONE | GEM_TX_ERR);
	}
#endif
	return (GEM_TX_DONE);
}

#ifdef DEBUG_LEVEL
static void
gani_tx_desc_dump(struct gem_dev *dp)
{
	int		i;
	struct tx_desc	*tdp;

	cmn_err(CE_CONT,
	    "!%s: tx descriptor dump: current head:%d[%d], tail:%d[%d]",
	    dp->name,
	    dp->tx_desc_head, (int)SLOT(dp->tx_desc_head, TX_RING_SIZE),
	    dp->tx_desc_tail, (int)SLOT(dp->tx_desc_tail, TX_RING_SIZE));

	tdp = &TXDESC(dp->tx_ring)[0];
	for (i = 0; i < TX_RING_SIZE; i++, tdp++) {
#ifdef lint
		cmn_err(CE_CONT, "%d: %x %x %x %x",
		    i,
		    LE_32(tdp->txd0),
		    LE_32(tdp->txd1),
		    LE_32(tdp->txd2),
		    LE_32(tdp->txd3));
#else
		cmn_err(CE_CONT, "%d: %b %x %x %x",
		    i,
		    LE_32(tdp->txd0), TXD0_BITS,
		    LE_32(tdp->txd1),
		    LE_32(tdp->txd2),
		    LE_32(tdp->txd3));
#endif
	}
}
#endif

static uint64_t
gani_rx_desc_stat(struct gem_dev *dp, int slot, int ndesc)
{
	uint_t		len;
	uint32_t	rsr;
	struct rx_desc	*rdp;
	uint64_t	flags = GEM_RX_DONE;
#ifdef GEM_CONFIG_VLAN
	uint64_t	vtag;
#endif
	rdp = &RXDESC(dp->rx_ring)[slot];
	rsr = LE_32(rdp->rxd0);
#ifndef lint
	DPRINTF(2, (CE_CONT, "!%s: %s: slot:%d rxd0:0x%b, rxd1:0x%x",
	    dp->name, __func__, slot, rsr, RXD0_BITS, LE_32(rdp->rxd1)));
#endif
	if (rsr & RXD0_OWN) {
		/* not transmitted yet */
		return (0);
	}
#ifndef lint
	DPRINTF(2, (CE_CONT, "!%s: %s: slot:%d rxd0:0x%b, rxd1:0x%x",
	    dp->name, __func__, slot, rsr, RXD0_BITS, LE_32(rdp->rxd1)));
#endif
	if ((rsr & (RXD0_RES | RXD0_LS | RXD0_FS)) != (RXD0_LS | RXD0_FS)) {
		if (rsr & RXD0_RES) {
			if (rsr & RXD0_CRC) {
				dp->stats.crc++;
			}
			if (rsr & RXD0_RUNT) {
				dp->stats.runt++;
			}
		}

		if ((rsr & (RXD0_LS | RXD0_FS)) != (RXD0_LS | RXD0_FS)) {
			/* received frame is too long */
			if (rsr & RXD0_FS) {
				dp->stats.frame_too_long++;
			}
		}
		return (GEM_RX_ERR);
	}

	/* eliminate fcs */
	if ((len = rsr & RXD0_FRAMELEN) < ETHERFCSL) {
		return (GEM_RX_ERR);
	}
	len -= ETHERFCSL;

#ifdef GEM_CONFIG_VLAN
	if ((vtag = LE_32(rdp->rxd1)) & RXD1_TAVA) {
		/* fix vlan tag format */
		flags |= BSWAP_16(vtag & 0xffff) << GEM_RX_VTAG_SHIFT;
		DPRINTF(2, (CE_CONT, "%s: %s: vtag detected %llx",
		    dp->name, __func__, (unsigned long long)flags));
	}
#endif
#ifdef GEM_CONFIG_CKSUM_OFFLOAD
	if ((rsr & (RXD0_PID | RXD0_TCPF)) == RXD0_PID_TCP) {
		flags |= GEM_RX_CKSUM_TCP;
	} else if ((rsr & (RXD0_PID | RXD0_UDPF)) == RXD0_PID_UDP) {
		flags |= GEM_RX_CKSUM_UDP;
	}
	if ((rsr & RXD0_PID) != RXD0_PID_NONIP && (rsr & RXD0_IPF) == 0) {
		flags |= GEM_RX_CKSUM_IPv4;
	}
#endif
#ifdef notdef
{
	int	i;
	uint8_t	*bp = (uint8_t *)&dp->rx_buf_head->rxb_buf[0];

	cmn_err(CE_CONT, "!%s: len:%d", dp->name, len);

	for (i = 0; i < len; i += 10) {
		cmn_err(CE_CONT,
		    "!%02x %02x %02x %02x %02x"
		    " %02x %02x %02x %02x %02x",
		    bp[0], bp[1], bp[2], bp[3], bp[4],
		    bp[5], bp[6], bp[7], bp[8], bp[9]);
		bp += 10;
	}
}
#endif
	return (flags | GEM_RX_DONE | len);
}

static void
gani_tx_desc_init(struct gem_dev *dp, int slot)
{
	TXDESC(dp->tx_ring)[slot].txd0 = 0;
}

static void
gani_rx_desc_init(struct gem_dev *dp, int slot)
{
	RXDESC(dp->rx_ring)[slot].rxd0 = 0;
}

/*
 * Device depend interrupt handler
 */
static uint_t
gani_interrupt(struct gem_dev *dp)
{
	int		i;
	int		nread;
	uint16_t	isr;
	uint16_t	imr_hw;
	uint_t		restart_tx = 0;
	struct gani_dev	*lp = (struct gani_dev *)dp->private;

	isr = INW(dp, ISR);

	DPRINTF(4, (CE_CONT, "!%s: time:%ld gani_interrupt: isr:%b",
	    dp->name, ddi_get_lbolt(), isr, INTR_BITS));

	imr_hw = lp->imr;
	if ((isr & lp->imr) == 0) {
		/* not for us */
		return (DDI_INTR_UNCLAIMED);
	}

	DPRINTF(2, (CE_CONT, "!%s: time:%ld gani_interrupt: isr:%b imr:%b",
	    dp->name, ddi_get_lbolt(), isr, INTR_BITS,
	    INW(dp, IMR), INTR_BITS));

	if (lp->msi) {
		/* disable interrupts */
		OUTW(dp, IMR, imr_hw = 0);
		FLSHW(dp, IMR);
	}

	if (!dp->mac_active) {
		/* disable further interrupts */
		OUTW(dp, IMR, 0);
		FLSHW(dp, IMR);

		/* ack to all interrupts */
		OUTW(dp, ISR, 0xffff);
		FLSHW(dp, ISR);
		return (DDI_INTR_CLAIMED);
	}

#ifdef CONFIG_OPT_TPPOLL
#define	POLLED_INTRS	(INTR_ROK | INTR_TDU | INTR_TOK)
#else
#define	POLLED_INTRS	(INTR_ROK | INTR_TOK)
#endif
	isr &= lp->imr | POLLED_INTRS;

	/* clear interrupt sources explicitly */
	/* XXX : don't clear RxFIFO Overflow bit for 8168 */
	if (GANI_PCIE_GIGA(lp->chip->type)) {
		OUTW(dp, ISR, isr & ~INTR_FOVW);
	} else {
		OUTW(dp, ISR, isr);
	}

	/* PCI read/write barrier to make interrupt state stable. */
	/* XXX - it costs 5%-10% of cpu utilazation at 1.8GHz AMD athlon */
	FLSHW(dp, ISR);

#ifdef GEM_CONFIG_POLLING
	if (dp->poll_interval != lp->last_poll_interval) {
		if (dp->poll_interval) {
			/* polling mode */
			lp->imr &= ~POLLED_INTRS;

			switch (lp->busclk) {
			case BUSCLK_PCIE:
				i = dp->poll_interval / (1000 / 125);
				break;

			case BUSCLK_PCI66:
			case BUSCLK_PCI33:
			default:
				i = dp->poll_interval / (1000 / 33);
				break;
			}
			OUTL(dp, TimerInt, i);

			/*
			 * To schedule the next timer interrupt correctly,
			 * we pretend as we were interrupted from
			 * polling timer
			 */
			isr |= INTR_TimeOut;

			DPRINTF(3, (CE_CONT,
			    "%s: poll_interval:%d", dp->name, i));
		} else {
			/* normal mode */
			lp->imr |= POLLED_INTRS;

			OUTL(dp, TimerInt, 0);
		}

		lp->last_poll_interval = dp->poll_interval;
	}

	if (isr & INTR_TimeOut) {
		/*
		 * Reset PCI clock counter to schedule the next polling
		 * timer interrupt.
		 */
		OUTL(dp, TCTR, 0);
	}
#endif /* GEM_CONFIG_POLLING */

	if (isr & INTR_PUN) {
		/*
		 * Link or PHY status has changed
		 */
		DPRINTF(2, (CE_CONT, "!%s: isr:%b", dp->name, isr, INTR_BITS));
		if (gem_mii_link_check(dp)) {
			restart_tx |= INTR_RESTART_TX;
		}
	}

rx_again:
	if (isr & INTR_FOVW) {
		if (GANI_PCIE(lp->chip->type)) {
			int		wait_time;
			uint16_t	isr_tmp;

			/*
			 * To recover from rx fifo overflow,
			 * we must reset the nic.
			 */
			lp->need_to_reset = B_TRUE;

			/*
			 * Need to drain rx packets which are still
			 * in rx fifo.
			 */
			nread = 0;
			wait_time = dp->mtu / 128;

			for (i = 2; i > 0; i--) {
				drv_usecwait(wait_time);

				isr_tmp = INW(dp, ISR);
				isr |= isr_tmp & (INTR_ROK | INTR_FOVW);

				nread += gem_receive(dp);

				if ((isr_tmp & INTR_ROK) == 0) {
					DPRINTF(1, (CE_CONT,
					    "!%s: rxfifo overflow:"
					    " %d packets salvaged",
					    dp->name, nread));
					break;
				}
				OUTW(dp, ISR, INTR_ROK);
				FLSHW(dp, ISR);
			}
			if (i == 0) {
				cmn_err(CE_WARN,
				    "!%s: %s: rx fifo overflow,"
				    " rxfifo drain timeout",
				    dp->name, __func__);
			}
			lp->rx_pkt_cnt += nread;
		}

		if ((isr & INTR_RDU) == 0) {
			/*
			 * we should increase rxdma size;
			 */
			dp->rxmaxdma = min(dp->rxmaxdma + 256, 2000);
		}

		dp->stats.overflow++;
		dp->stats.errrcv++;
	}

	if (isr & (INTR_ROK | INTR_RER)) {
		nread = gem_receive(dp);
		lp->rx_pkt_cnt += nread;
#ifdef TEST_FOVW
		if ((lp->rx_pkt_cnt % 100000) == 99999) {
			isr |= INTR_FOVW;
		}
#endif
#ifdef NEVER
		if (isr & INTR_RER) {
			cmn_err(CE_WARN, "!%s: Rx error, isr:%b",
			    dp->name, isr, INTR_BITS);
			lp->need_to_reset = B_TRUE;
		}
#endif
	}

	if (isr & INTR_RDU) {
#ifdef GEM_CONFIG_POLLING
		if (dp->poll_interval && dp->poll_pkt_delay > 1 &&
		    GANI_PCIE(lp->chip->type)) {
			/*
			 * current polling interval is too long.
			 * recompute it.
			 */
			dp->poll_pkt_delay--;
			DPRINTF(1, (CE_CONT,
			    "!%s: pkt-delay decreased to %d",
			    dp->name, dp->poll_pkt_delay));
		}
#endif /* GEM_CONFIG_POLLING */
		dp->stats.errrcv++;
		dp->stats.norcvbuf++;
	}

	if (isr & (INTR_TER | INTR_TOK)) {

		/* Need to kick potentially blocked down stream */
		if (gem_tx_done(dp)) {
			restart_tx |= INTR_RESTART_TX;
		}
		if (isr & INTR_TER) {
			cmn_err(CE_WARN, "!%s: Tx error, isr:%b",
			    dp->name, isr, INTR_BITS);
			lp->need_to_reset = B_TRUE;
		}
	}

	if (isr & INTR_TDU) {
#ifdef CONFIG_OPT_TPPOLL
		mutex_enter(&dp->xmitlock);

		ASSERT(lp->tx_running);
		lp->tx_running = B_FALSE;

		if (lp->tx_finished != lp->tx_activated) {
			/* just kick tx engine again */
			OUTB(dp, TPPoll, TPPoll_NPQ);
			lp->tx_running = B_TRUE;
#ifdef WA_NO_TPPOLL_WRAP
		} else if (SLOT(lp->tx_finished, TX_RING_SIZE) == 0) {
			/* we are at the end of tx ring */
			lp->tx_no_more = B_FALSE;
			if (lp->tx_pended > 0) {
				gani_tx_start(dp, 0, lp->tx_pended);
				lp->tx_pended = 0;
			}
#endif /* WA_NO_TPPOLL_WRAP */
		}
		mutex_exit(&dp->xmitlock);
#else
		if (GANI_PCIE_GIGA(lp->chip->type) &&
		    (isr & INTR_TOK)) {
			OUTB(dp, TPPoll, TPPoll_NPQ);
		}
#endif /* CONFIG_OPT_TPPOLL */
	}

	if (isr & INTR_SERR) {
		cmn_err(CE_WARN, "!%s: unexpected interrupt: isr:%b",
		    dp->name, isr, INTR_BITS);
		lp->need_to_reset = B_TRUE;
	}

	if (lp->need_to_reset) {
		(void) gem_restart_nic(dp, GEM_RESTART_KEEP_BUF);

		restart_tx = INTR_RESTART_TX;
		lp->need_to_reset = B_FALSE;
	}

	if ((dp->misc_flag & GEM_NOINTR) == 0 && lp->imr != imr_hw) {
		/* enable interrupts again */
		OUTW(dp, IMR, lp->imr);
	}

	return (DDI_INTR_CLAIMED | restart_tx);
}

/*
 * MII Interfaces
 */
#define	MII_DELAY(dp, r) { (void) INL(dp, (r)); (void) INL(dp, (r)); }

static void
gani_mii_sync(struct gem_dev *dp)
{
	/* do nothing */
}

#define	GANI_MII_MAX_RETRY	10

static uint16_t
gani_mii_read(struct gem_dev *dp, uint_t index)
{
	int		i;
	int		retry = 0;
	uint32_t	ret;

again:
	OUTL(dp, PHYAR, index << PHYAR_REGADDR_SHIFT);
	drv_usecwait(20);

	for (i = 0; ((ret = INL(dp, PHYAR)) & PHYAR_FLAG) == 0; i++) {
		if (i > 20) {
			if (retry++ < GANI_MII_MAX_RETRY) {
				goto again;
			}
			cmn_err(CE_WARN, "!%s: %s: timeout, reg:%d",
			    dp->name, __func__, index);
			return (0);
		}
		drv_usecwait(20);
	}
	ret &= PHYAR_DATA;
	return ((uint16_t)ret);
}

static void
gani_mii_write(struct gem_dev *dp, uint_t index, uint16_t val)
{
	int		i;
	int		retry = 0;
again:
	OUTL(dp, PHYAR,
	    PHYAR_FLAG | (index << PHYAR_REGADDR_SHIFT) | val);
	drv_usecwait(20);

	for (i = 0; (INL(dp, PHYAR) & PHYAR_FLAG) != 0; i++) {
		if (i > 20) {
			if (retry++ < GANI_MII_MAX_RETRY) {
				goto again;
			}
			cmn_err(CE_WARN, "!%s: %s: timeout, reg:%d",
			    dp->name, __func__, index);
			break;
		}
		drv_usecwait(20);
	}
}
#undef	MII_DELAY

static int
gani_mii_probe(struct gem_dev *dp)
{
	if (gem_mii_probe_default(dp) != GEM_SUCCESS) {
		return (GEM_FAILURE);
	}

	DPRINTF(0, (CE_CONT, "!%s: %s :reg 14:0x%x",
	    dp->name, __func__, gani_mii_read(dp, 0xe)));

#if 0
	/* rtl816x series doesn't support 1000Mbps half duplex mode */
	dp->mii_xstatus &= ~MII_XSTATUS_1000BASET;
#endif
	return (GEM_SUCCESS);
}

static struct {
	uint8_t		addr;
	uint16_t	val;
} gani_8169s_patch[] = {
	/* based on r8169-6.003.00 */
	0x1f, 0x0001, 0x06, 0x006e, 0x08, 0x0708,
	0x15, 0x4000, 0x18, 0x65c7,

	0x1f, 0x0001, 0x03, 0x00a1, 0x02, 0x0008,
	0x01, 0x0120, 0x00, 0x1000, 0x04, 0x0800,
	0x04, 0x0000,

	0x03, 0xff41, 0x02, 0xdf60, 0x01, 0x0140,
	0x00, 0x0077, 0x04, 0x7800, 0x04, 0x7000,

	0x03, 0x802f, 0x02, 0x4f02, 0x01, 0x0409,
	0x00, 0xf0f9, 0x04, 0x9800, 0x04, 0x9000,

	0x03, 0xdf01, 0x02, 0xdf20, 0x01, 0xff95,
	0x00, 0xba00, 0x04, 0xa800, 0x04, 0xa000,

	0x03, 0xff41, 0x02, 0xdf20, 0x01, 0x0140,
	0x00, 0x00bb, 0x04, 0xb800, 0x04, 0xb000,

	0x03, 0xdf41, 0x02, 0xdc60, 0x01, 0x6340,
	0x00, 0x007d, 0x04, 0xd800, 0x04, 0xd000,

	0x03, 0xdf01, 0x02, 0xdf20, 0x01, 0x100a,
	0x00, 0xa0ff, 0x04, 0xf800, 0x04, 0xf000,

	0x1f, 0x0000, 0x0b, 0x0000, 0x00, 0x9200,
};

static int
gani_mii_init(struct gem_dev *dp)
{
	struct gani_dev		*lp = (struct gani_dev *)dp->private;
	int			i;

	switch (lp->chip->type) {
	case MAC_VER_8169S: /* M2 */
	case MAC_VER_8110S: /* M3 */
		for (i = 0;
		    i < sizeof (gani_8169s_patch)
		    / sizeof (gani_8169s_patch[0]); i++) {
			gani_mii_write(dp,
			    gani_8169s_patch[i].addr,
			    gani_8169s_patch[i].val);
		}
		break;

	case MAC_VER_8169SB:
		gani_mii_write(dp, 0x1f, 0x0002);
		gani_mii_write(dp, 0x01, 0x90d0);
		gani_mii_write(dp, 0x1f, 0x0000);
		break;

	case MAC_VER_8168B_B:
	case MAC_VER_8168B_E:
	case MAC_VER_8168B_F:
		/* based on r8168-8.003.00 */
		gani_mii_write(dp, 0x1f, 0x0001);
		gani_mii_write(dp, 0x10, 0xf41b);
		gani_mii_write(dp, 0x1f, 0x0000);
		break;

	case MAC_VER_8168C:
		/* based on r8168-8.003.00 */
		gani_mii_write(dp, 0x1f, 0x0001);
		gani_mii_write(dp, 0x12, 0x2300);

		gani_mii_write(dp, 0x1f, 0x0002);
		gani_mii_write(dp, 0x00, 0x88d4);
		gani_mii_write(dp, 0x01, 0x82b1);
		gani_mii_write(dp, 0x03, 0x7002);
		gani_mii_write(dp, 0x08, 0x9e30);
		gani_mii_write(dp, 0x09, 0x01f0);
		gani_mii_write(dp, 0x0a, 0x5500);
		gani_mii_write(dp, 0x0c, 0x00c8);
		gani_mii_write(dp, 0x1f, 0x0003);
		gani_mii_write(dp, 0x12, 0xC096);

		gani_mii_write(dp, 0x16, 0x000a);
		gani_mii_write(dp, 0x1f, 0x0000);
		break;

	case MAC_VER_8168C_B:
		/* based on r8168-8.003.00 */
		gani_mii_write(dp, 0x1f, 0x0001);
		gani_mii_write(dp, 0x12, 0x2300);
		gani_mii_write(dp, 0x1f, 0x0003);
		gani_mii_write(dp, 0x16, 0x0f0a);
		gani_mii_write(dp, 0x1f, 0x0000);

		gani_mii_write(dp, 0x1f, 0x0002);
		gani_mii_write(dp, 0x0c, 0x7eb8);
		gani_mii_write(dp, 0x1f, 0x0000);
		break;

	case MAC_VER_8168CP:
		/* based on r8168-8.003.00 */
		gani_mii_write(dp, 0x1f, 0x0000);
		gani_mii_write(dp, 0x1d, 0x0f00);

		gani_mii_write(dp, 0x1f, 0x0002);
		gani_mii_write(dp, 0x0c, 0x1ec8);
		gani_mii_write(dp, 0x1f, 0x0000);
		break;
	}

	return (GEM_SUCCESS);
}

static int
gani_mii_config(struct gem_dev *dp)
{
	int		ret;
	uint16_t	val;
	struct gani_dev	*lp = (struct gani_dev *)dp->private;

	/*
	 * XXX - 816x nics seem to have promblem in fixed mode. The link
	 * never go up again after it once become down from up.
	 */
	if (!dp->anadv_autoneg) {
		cmn_err(CE_NOTE,
		    "!%s: rtl816x series does not support fixed mode."
		    "limited auto negotiation capability is used "
		    "instead of given forced mode.",
		    dp->name);
		dp->anadv_autoneg = B_TRUE;
	}

	/*
	 * XXX - the datasheet says rtl816x doesn't support 1Gbps half
	 * duplex mode, but phys in rtl8168 seem to require 1000hdx bit
	 * set in 1000TC register for 1G bps full duplex negotiation.
	 */
	dp->anadv_1000hdx = dp->anadv_1000fdx;

	if (GANI_PCIE_GIGA(lp->chip->type)) {
		/* power up */
		gani_mii_write(dp, 0x1f, 0);
		gani_mii_write(dp, 0x0e, 0);
	}

	ret = gem_mii_config_default(dp);

	if (lp->forced_100hdx) {
		val = gani_mii_read(dp,	MII_AN_ADVERT);
		val &= ~MII_ABILITY_SPEED_DUPLEX;
		gani_mii_write(dp, MII_AN_ADVERT, val | MII_ABILITY_100BASE_TX);
	}

	return (ret);
}

/* ======================================================== */
/*
 * OS depend (device driver kernel interface) routine
 */
/* ======================================================== */
#ifdef CONFIG_EEPROM_IO
#define	gani_eeprom_delay(dp)	\
	{ (void) INB(dp, CR9346); (void) INB(dp, CR9346); }

static uint16_t
gani_read_eeprom(struct gem_dev *dp, int addr)
{
	int		i;
	int		addr_bits;
	uint_t		cmd;
	uint8_t		chip_select;
	uint8_t		di;
	uint16_t	ret;

	addr_bits = (INL(dp, RCR) & RCR_9356SEL) ? 8 : 6;

	DPRINTF(2, (CE_CONT, "!%s: gani_read_eeprom: called: addr_bits:%d",
	    dp->name, addr_bits));

	/* make command bits */
	cmd = (6 << addr_bits) | addr;

	/* enable eeprom interface register */
	chip_select = CR9346_EEM_PROGRAM;
	OUTB(dp, CR9346, chip_select);

	chip_select |= CR9346_EECS;
	OUTB(dp, CR9346, chip_select);
	gani_eeprom_delay(dp);

	/* output eeprom command */
	for (i = 4 + addr_bits; i >= 0; i--) {
		di = ((cmd >> i) << CR9346_EEDI_SHIFT) & CR9346_EEDI;
		OUTB(dp, CR9346, chip_select | di);
		gani_eeprom_delay(dp);

		OUTB(dp, CR9346, chip_select | di | CR9346_EESK);
		gani_eeprom_delay(dp);
	}

	/* release clock but keep chip_select asserted */
	OUTB(dp, CR9346, chip_select);
	gani_eeprom_delay(dp);

	/* get returned value */
	ret = 0;
	for (i = 16; i > 0; i--) {
		/* get 1 bit */
		OUTB(dp, CR9346, chip_select | CR9346_EESK);
		gani_eeprom_delay(dp);

		ret = (ret << 1)
		    | ((INB(dp, CR9346) >> CR9346_EEDO_SHIFT) & 1);

		OUTB(dp, CR9346, chip_select);
		gani_eeprom_delay(dp);
	}

	/* Terminate the EEPROM access. */
	OUTB(dp, CR9346, CR9346_EEM_PROGRAM);
	OUTB(dp, CR9346, CR9346_EEM_NORMAL);
	gani_eeprom_delay(dp);

	DPRINTF(2, (CE_CONT, "!gani_read_eeprom: returned 0x%x", ret));

	return (ret);
}

#if DEBUG_LEVEL > 0
static void
gani_eeprom_dump(struct gem_dev *dp, int size)
{
	int		i;
	uint16_t	x0, x1, x2, x3;

	cmn_err(CE_CONT, "!%s: eeprom dump:", dp->name);
	for (i = 0; i < size; i += 4) {
		x0 = gani_read_eeprom(dp, i + 0);
		x1 = gani_read_eeprom(dp, i + 1);
		x2 = gani_read_eeprom(dp, i + 2);
		x3 = gani_read_eeprom(dp, i + 3);
		cmn_err(CE_CONT,
		    "!0x%02x: %02x %02x %02x %02x %02x %02x %02x %02x",
		    i*2,
		    (uint8_t)x0, (uint8_t)(x0 >> 8),
		    (uint8_t)x1, (uint8_t)(x1 >> 8),
		    (uint8_t)x2, (uint8_t)(x2 >> 8),
		    (uint8_t)x3, (uint8_t)(x3 >> 8));
	}
}
#endif
#endif /* CONFIG_EEPROM_IO */

static int
gani_attach_chip(struct gem_dev *dp)
{
	int		i;
	uint32_t	val;
	uint8_t		*m;
	struct gani_dev	*lp = (struct gani_dev *)dp->private;

	DPRINTF(0, (CE_CONT, "!%s: %s: called", dp->name, __func__));

	/*
	 * reload default mac address from EEPROM
	 */
	m = &dp->dev_addr.ether_addr_octet[0];
#ifdef CONFIG_EEPROM_IO
#if DEBUG_LEVEL > 0
	gani_eeprom_dump(dp, 0x40);
#endif
	for (i = 0; i < ETHERADDRL/2; i++) {
		val = gani_read_eeprom(dp, i + 7);
		m[i*2  ] = (uint8_t)val;
		m[i*2+1] = (uint8_t)(val >> 8);
	}
#else
	OUTB(dp, CR9346, CR9346_EEM_AUTOLD);

	/*
	 * XXX - the old datasheet says it takes 2mS typically, but
	 * it still caused bus timeouts for Netgear cardbus products
	 * even if we waited for 10mS. Now we wait for 1000mS.
	 */
	delay(drv_usectohz(1000000));

	for (i = 0; i < ETHERADDRL; i++) {
		m[i] = INB(dp, IDR + i);
	}

	/* initialize soft copy of mac registers */
	bcopy(m, lp->mac, ETHERADDRL);
#endif /* CONFIG_EEPROM_IO */

	/* no need to scan phy */
	dp->mii_phy_addr = -1;

	/*
	 * Fix rx buffer length:
	 * It must have additional 4 byte for vlan and must be multiple
	 * of rx buffer align.
	 */
	dp->rx_buf_len = ROUNDUP2(PKTSIZE(dp->mtu), dp->gc.gc_rx_buf_align + 1);

	/* store & foward for tx */
	/* XXX - RTL8168 series supports only store & forword for tx */
	dp->txthr = INT32_MAX;

	/*
	 * XXX - workaround for SiS965L
	 * txmaxdma and rxmaddma must be unlimited, and rxthr *must* be S&F,
	 * otherwise the system will hang.
	 */
	dp->txmaxdma = INT32_MAX;
	dp->rxmaxdma = INT32_MAX;
	dp->rxthr    = INT32_MAX;

#if defined(GEM_CONFIG_CKSUM_OFFLOAD) && defined(GEM_CONFIG_VLAN)
	/*
	 * XXX - 816x series corrupts vlan-tagged packets on tx
	 * if the hw-cksum is enabled and hw-vlan is deisabled.
	 * Therefore, the both must be enabled at the same time.
	 */
	dp->misc_flag |= GEM_VLAN_HARD;
	dp->misc_flag |= (GEM_CKSUM_FULL_IPv4 | GEM_CKSUM_HEADER_IPv4);
#else
	dp->misc_flag |= GEM_VLAN_SOFT;
#endif

	/* Receive control register: write an initial value */
	val = 0;
	if (dp->rxmaxdma <= 64) {
		val |= RCR_MXDMA_64;
	} else if (dp->rxmaxdma <= 128) {
		val |= RCR_MXDMA_128;
	} else if (dp->rxmaxdma <= 256) {
		val |= RCR_MXDMA_256;
	} else if (dp->rxmaxdma <= 512) {
		val |= RCR_MXDMA_512;
	} else if (dp->rxmaxdma <= 1024) {
		val |= RCR_MXDMA_1024;
	} else {
		val |= RCR_MXDMA_UNLIMITED;
	}
	if (dp->rxthr <= 64) {
		val |= RCR_RXFTH_64;
	} else if (dp->rxthr <= 128) {
		val |= RCR_RXFTH_128;
	} else if (dp->rxthr <= 256) {
		val |= RCR_RXFTH_256;
	} else if (dp->rxthr <= 512) {
		val |= RCR_RXFTH_512;
	} else if (dp->rxthr <= 1024) {
		val |= RCR_RXFTH_1024;
	} else {
		val |= RCR_RXFTH_SF;	/* store and forward */
	}
	/* XXX - Keep undocumented bits.  */
	lp->rcr = (val | (INL(dp, RCR) & ~RCR_MASK));

	/* Transmit configration register : */
	val = 0;
	if (dp->txmaxdma <= 16) {
		val |= TCR_MXDMA_16;
	} else if (dp->txmaxdma <= 32) {
		val |= TCR_MXDMA_32;
	} else if (dp->txmaxdma <= 64) {
		val |= TCR_MXDMA_64;
	} else if (dp->txmaxdma <= 128) {
		val |= TCR_MXDMA_128;
	} else if (dp->txmaxdma <= 256) {
		val |= TCR_MXDMA_256;
	} else if (dp->txmaxdma <= 512) {
		val |= TCR_MXDMA_512;
	} else if (dp->txmaxdma <= 1024) {
		val |= TCR_MXDMA_1024;
	} else {
		val |= TCR_MXDMA_UNLIMITED;
	}
	lp->tcr = (TCR_IFG_802_3 | TCR_LBK_NORMAL | val);

	mutex_init(&lp->stat_lock, NULL, MUTEX_DRIVER, dp->iblock_cookie);
	lp->stat_to_id = (timeout_id_t)0;

	return (GEM_SUCCESS);	/* currently return code is not used. */
}

static int
ganiattach(dev_info_t *dip, ddi_attach_cmd_t cmd)
{
	int			i;
	ddi_acc_handle_t	conf_handle;
	int			revid;
	int			unit;
	struct chip_info	*p;
	uint32_t		tcr;
	const char		*drv_name;
	struct gem_dev		*dp;
	void			*base;
	ddi_acc_handle_t	regs_handle;
	struct gem_conf		*gcp;
	struct gani_dev		*lp;
	uint32_t		ilr;
	boolean_t		is_pcie;

	unit =  ddi_get_instance(dip);
	drv_name = ddi_driver_name(dip);
	DPRINTF(1, (CE_CONT, "!%s%d: ganiattach: called", drv_name, unit));

	/*
	 * Common routine after power-on
	 */

	/* fix config registers */
	if (pci_config_setup(dip, &conf_handle) != DDI_SUCCESS) {
		cmn_err(CE_WARN, "!%s%d: pci_config_setup failed",
		    drv_name, unit);
		goto err;
	}

	pci_config_put16(conf_handle, PCI_CONF_COMM,
	    pci_config_get16(conf_handle, PCI_CONF_COMM)
	    | PCI_COMM_IO | PCI_COMM_MAE | PCI_COMM_ME);

	/* ensure D0 mode */
	(void) gem_pci_set_power_state(dip, conf_handle, PCI_PMCSR_D0);

	/* set pci latency timer to 0x40 */
	if (pci_config_get8(conf_handle, PCI_CONF_LATENCY_TIMER) < 64) {
		pci_config_put8(conf_handle, PCI_CONF_LATENCY_TIMER, 64);
	}
	revid = pci_config_get8(conf_handle, PCI_CONF_REVID);
	ilr = pci_config_get32(conf_handle, PCI_CONF_ILINE);
	DPRINTF(0, (CE_CONT, "!%s%d: ilr 0x%08x", drv_name, unit, ilr));

	is_pcie = gem_search_pci_cap(dip, conf_handle, PCI_CAP_ID_PCI_E);

	pci_config_teardown(&conf_handle);

	switch (cmd) {
	case DDI_RESUME:
		dp = GEM_GET_DEV(dip);

		if ((i = gem_resume(dip)) == DDI_SUCCESS) {
			gani_stat_timeout(dp);
		}
		return (i);

	case DDI_ATTACH:
		/*
		 * Map in the device registers.
		 * XXX - MEM32 for PCI-E cause to hang system.
		 */
		if (gem_pci_regs_map_setup(dip,
#ifdef MAP_MEM
		    (is_pcie ? PCI_ADDR_MEM64 : PCI_ADDR_MEM32),
#else
		    PCI_ADDR_IO,
#endif
		    PCI_ADDR_MASK,
		    &gani_dev_attr,
		    (void *)&base, &regs_handle) != DDI_SUCCESS) {
			goto err;
		}

		/*
		 * Check hardware revision
		 */
		tcr = ddi_get32(regs_handle, (void *)((caddr_t)base + TCR));

		for (p = chiptbl_8169, i = 0; i < CHIPTABLESIZE; p++, i++) {
			if (p->tcr_val == (tcr & p->tcr_mask)) {
				/* found */
				goto chip_found;
			}
		}

		cmn_err(CE_WARN,
		    "!%s%d: attach: unknown mac version: tcr:0x%08x",
		    drv_name, unit, tcr);

		p = &chiptbl_8169[0];	/* choose the oldest 8169 chipset */

chip_found:
		cmn_err(CE_CONT, "!%s%d: chip is %s rev:0x%02x tcr:0x%08x",
		    drv_name, unit, p->name, revid, tcr);

		if ((ddi_get8(regs_handle,
		    (uint8_t *)((caddr_t)base + PHYS)) & PHYS_EnTBI)) {
			cmn_err(CE_CONT,
			    "!%s%d: tbi interfaces isn't supported",
			    drv_name, unit);
			goto err;
		}

		lp = (struct gani_dev *)
		    kmem_zalloc(sizeof (struct gani_dev), KM_SLEEP);
		lp->chip = p;

		/* read config2 register */
		if (GANI_PCIE(p->type)) {
			lp->busclk = BUSCLK_PCIE; /* PCI-E (125MHz) */
		} else {
			lp->busclk = ddi_get8(regs_handle,
			    (uint8_t *)((caddr_t)base + CFG2)) & CFG2_PCICLKF
			    ? BUSCLK_PCI66 : BUSCLK_PCI33;
		}
		DPRINTF(0, (CE_CONT, "!%s%d: busclk:%d, cfg2:0x%x",
		    drv_name, unit, lp->busclk,
		    ddi_get8(regs_handle, (uint8_t *)((caddr_t)base + CFG2))));

		/*
		 * construct gem configration
		 */
		gcp = (struct gem_conf *)kmem_zalloc(sizeof (*gcp), KM_SLEEP);

		/* name */
		(void) sprintf(gcp->gc_name, "%s%d", drv_name, unit);

		gcp->gc_tx_buf_align = sizeof (uint8_t) - 1;
		gcp->gc_tx_max_frags = TX_MAX_FRAGS;
		gcp->gc_tx_max_descs_per_pkt = gcp->gc_tx_max_frags;
		gcp->gc_tx_desc_unit_shift = 4;
		gcp->gc_tx_buf_size = TX_BUF_SIZE;
		gcp->gc_tx_buf_limit = gcp->gc_tx_buf_size;
		gcp->gc_tx_ring_size = TX_RING_SIZE;
		gcp->gc_tx_ring_limit = gcp->gc_tx_ring_size;
		gcp->gc_tx_auto_pad = B_TRUE;
		gcp->gc_tx_copy_thresh = gani_tx_copy_thresh;
		gcp->gc_tx_desc_write_oo = B_FALSE;
#ifdef CONFIG_OO
		gcp->gc_tx_desc_write_oo = (TX_MAX_FRAGS == 1);
#endif
		gcp->gc_rx_buf_align = (GANI_PCIE(p->type) ? 8 : 1) - 1;
		gcp->gc_rx_max_frags = 1;
		gcp->gc_rx_desc_unit_shift = 4;
		gcp->gc_rx_ring_size = RX_RING_SIZE;
		gcp->gc_rx_buf_max   = RX_BUF_SIZE;
		gcp->gc_rx_copy_thresh = gani_rx_copy_thresh;
		gcp->gc_io_area_size = TC_SIZE;

		/* map attributes */
		gcp->gc_dev_attr = gani_dev_attr;
		gcp->gc_buf_attr = gani_buf_attr;
		gcp->gc_desc_attr = gani_buf_attr;

		/* dma attributes */
		gcp->gc_dma_attr_desc = gani_dma_attr_desc;
		if (GANI_PCIE(p->type)) {
			gcp->gc_dma_attr_txbuf = gani_dma_attr_buf64;
		} else {
#ifdef CONFIG_DAC
			gcp->gc_dma_attr_txbuf = gani_dma_attr_buf64;
#else
			gcp->gc_dma_attr_txbuf = gani_dma_attr_buf32;
#endif
		}
		gcp->gc_dma_attr_txbuf.dma_attr_align = gcp->gc_tx_buf_align+1;
		gcp->gc_dma_attr_txbuf.dma_attr_sgllen = gcp->gc_tx_max_frags;

		if (GANI_PCIE(p->type)) {
			gcp->gc_dma_attr_rxbuf = gani_dma_attr_buf64;
		} else {
#ifdef CONFIG_DAC
			gcp->gc_dma_attr_rxbuf = gani_dma_attr_buf64;
#else
			gcp->gc_dma_attr_rxbuf = gani_dma_attr_buf32;
#endif
		}
		gcp->gc_dma_attr_rxbuf.dma_attr_align = gcp->gc_rx_buf_align+1;
		gcp->gc_dma_attr_rxbuf.dma_attr_sgllen = gcp->gc_rx_max_frags;

		/* time out parameters */
		gcp->gc_tx_timeout = 3*ONESEC;
		gcp->gc_tx_timeout_interval = ONESEC;

		/* flow control */
		gcp->gc_flow_control = FLOW_CONTROL_RX_PAUSE;
#ifdef NEVER
		/* XXX - now automatically detected by GMII/MII phy */
		/* mii mode */
		gcp->gc_mii_mode =
		    (p->flags & 0xf) == GEM_SPD_1000 ?
		    GEM_MODE_1000BASET : GEM_MODE_100BASETX;
#endif
		/* MII timeout parameters */
		gcp->gc_mii_link_watch_interval = ONESEC;
		gcp->gc_mii_an_watch_interval = ONESEC/10;
		gcp->gc_mii_reset_timeout = MII_RESET_TIMEOUT; /* 1 sec */
		gcp->gc_mii_an_timeout = MII_AN_TIMEOUT;
		gcp->gc_mii_an_wait = ONESEC;
		gcp->gc_mii_linkdown_timeout = MII_LINKDOWN_TIMEOUT;

		/* rtl8169 seems to delay to recognize PHY status */
		gcp->gc_mii_an_delay = ONESEC/10;	/* 100mS */
		/* we must reset rtl8169 phy to update advert register */
		gcp->gc_mii_linkdown_action = MII_ACTION_RESET;

		/*
		 * XXX - MAC_VER_8169S or later chipset requires reset
		 * on link down timeout for 1Gbps connection
		 */
		gcp->gc_mii_linkdown_timeout_action = MII_ACTION_RESET;
		gcp->gc_mii_dont_reset = B_FALSE;
		gcp->gc_mii_an_oneshot = B_FALSE;
		gcp->gc_mii_hw_link_detection = B_TRUE;

		/* I/O methods */

		/* mac operation */
		gcp->gc_attach_chip = &gani_attach_chip;
		gcp->gc_reset_chip = &gani_reset_chip;
		gcp->gc_init_chip = &gani_init_chip;
		gcp->gc_start_chip = &gani_start_chip;
		gcp->gc_stop_chip = &gani_stop_chip;
		gcp->gc_multicast_hash = &gani_mcast_hash;
		gcp->gc_set_rx_filter = &gani_set_rx_filter;
		gcp->gc_set_media = &gani_set_media;
		gcp->gc_get_stats = &gani_get_stats;
		gcp->gc_interrupt = &gani_interrupt;

		/* descriptor operation */
		gcp->gc_tx_desc_write = &gani_tx_desc_write;
		gcp->gc_rx_desc_write = &gani_rx_desc_write;
		gcp->gc_tx_start = &gani_tx_start;
		gcp->gc_rx_start = NULL;
		gcp->gc_tx_desc_stat = &gani_tx_desc_stat;
		gcp->gc_rx_desc_stat = &gani_rx_desc_stat;
		gcp->gc_tx_desc_init = &gani_tx_desc_init;
		gcp->gc_rx_desc_init = &gani_rx_desc_init;
		gcp->gc_tx_desc_clean = &gani_tx_desc_init;
		gcp->gc_rx_desc_clean = &gani_rx_desc_init;

		/* mii operations */
		gcp->gc_mii_probe = &gani_mii_probe;
		gcp->gc_mii_init = &gani_mii_init;
		gcp->gc_mii_config = &gani_mii_config;
		gcp->gc_mii_sync = &gani_mii_sync;
		gcp->gc_mii_read = &gani_mii_read;
		gcp->gc_mii_write = &gani_mii_write;
		gcp->gc_mii_tune_phy = NULL;

		dp = gem_do_attach(dip, 0, gcp, base, &regs_handle,
		    lp, sizeof (struct gani_dev));
		kmem_free(gcp, sizeof (*gcp));

		if (dp == NULL) {
			goto err_free_mem;
		}

		gani_stat_timeout(dp);

		return (DDI_SUCCESS);

err_free_mem:
		kmem_free(lp, sizeof (struct gani_dev));
err:
		return (DDI_FAILURE);
	}

	return (DDI_FAILURE);
}

static int
ganidetach(dev_info_t *dip, ddi_detach_cmd_t cmd)
{
	struct gem_dev  *dp;
	struct gani_dev	*lp;

	dp = GEM_GET_DEV(dip);
	lp = (struct gani_dev *)dp->private;

	switch (cmd) {
	case DDI_DETACH:
	case DDI_SUSPEND:
		/* Ensure statistics timer routine stopped */
		mutex_enter(&lp->stat_lock);
		if (lp->stat_to_id != 0) {
			timeout_id_t	old_id;

			do {
				old_id = lp->stat_to_id;
				mutex_exit(&lp->stat_lock);
				(void) untimeout(old_id);
				mutex_enter(&lp->stat_lock);
			} while (old_id != lp->stat_to_id);
			lp->stat_to_id = 0;
		}
		mutex_exit(&lp->stat_lock);

		switch (cmd) {
		case DDI_DETACH:
			mutex_destroy(&lp->stat_lock);
			return (gem_do_detach(dip));

		case DDI_SUSPEND:
			return (gem_suspend(dip));
		}
	}

	return (DDI_FAILURE);
}

/* ======================================================== */
/*
 * OS depend (loadable streams driver) routine
 */
/* ======================================================== */
#ifdef GEM_CONFIG_GLDv3
DDI_DEFINE_STREAM_OPS(gani_ops, nulldev, nulldev, ganiattach, ganidetach,
    nodev, NULL, D_MP, NULL);
#else
static	struct module_info ganiminfo = {
	0,			/* mi_idnum */
	"gani",			/* mi_idname */
	0,			/* mi_minpsz */
	INFPSZ,			/* mi_maxpsz */
	64*1024,		/* mi_hiwat */
	1,			/* mi_lowat */
};

static	struct qinit ganirinit = {
	(int (*)()) NULL,	/* qi_putp */
	gem_rsrv,		/* qi_srvp */
	gem_open,		/* qi_qopen */
	gem_close,		/* qi_qclose */
	(int (*)()) NULL,	/* qi_qadmin */
	&ganiminfo,		/* qi_minfo */
	NULL			/* qi_mstat */
};

static	struct qinit ganiwinit = {
	gem_wput,		/* qi_putp */
	gem_wsrv,		/* qi_srvp */
	(int (*)()) NULL,	/* qi_qopen */
	(int (*)()) NULL,	/* qi_qclose */
	(int (*)()) NULL,	/* qi_qadmin */
	&ganiminfo,		/* qi_minfo */
	NULL			/* qi_mstat */
};

static struct streamtab	gani_info = {
	&ganirinit,	/* st_rdinit */
	&ganiwinit,	/* st_wrinit */
	NULL,		/* st_muxrinit */
	NULL		/* st_muxwrinit */
};

static	struct cb_ops cb_gani_ops = {
	nulldev,	/* cb_open */
	nulldev,	/* cb_close */
	nodev,		/* cb_strategy */
	nodev,		/* cb_print */
	nodev,		/* cb_dump */
	nodev,		/* cb_read */
	nodev,		/* cb_write */
	nodev,		/* cb_ioctl */
	nodev,		/* cb_devmap */
	nodev,		/* cb_mmap */
	nodev,		/* cb_segmap */
	nochpoll,	/* cb_chpoll */
	ddi_prop_op,	/* cb_prop_op */
	&gani_info,	/* cb_stream */
	D_MP,		/* cb_flag */
};

static	struct dev_ops gani_ops = {
	DEVO_REV,	/* devo_rev */
	0,		/* devo_refcnt */
	gem_getinfo,	/* devo_getinfo */
	nulldev,	/* devo_identify */
	nulldev,	/* devo_probe */
	ganiattach,	/* devo_attach */
	ganidetach,	/* devo_detach */
	nodev,		/* devo_reset */
	&cb_gani_ops,	/* devo_cb_ops */
	NULL,		/* devo_bus_ops */
	gem_power	/* devo_power */
};
#endif /* GEM_CONFIG_GLDv3 */

static struct modldrv modldrv = {
	&mod_driverops,	/* Type of module.  This one is a driver */
	ident,
	&gani_ops,	/* driver ops */
};

static struct modlinkage modlinkage = {
	MODREV_1, &modldrv, NULL
};

/* ======================================================== */
/*
 * _init : done
 */
/* ======================================================== */
int
_init(void)
{
	int 	status;

	DPRINTF(2, (CE_CONT, "!gani: _init: called"));

	gem_mod_init(&gani_ops, "gani");
	status = mod_install(&modlinkage);
	if (status != DDI_SUCCESS) {
		gem_mod_fini(&gani_ops);
	}
	return (status);
}

/*
 * _fini : done
 */
int
_fini(void)
{
	int	status;

	DPRINTF(2, (CE_CONT, "!gani: _fini: called"));
	status = mod_remove(&modlinkage);
	if (status == DDI_SUCCESS) {
		gem_mod_fini(&gani_ops);
	}
	return (status);
}

int
_info(struct modinfo *modinfop)
{
	return (mod_info(&modlinkage, modinfop));
}
