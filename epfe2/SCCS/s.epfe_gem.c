h02174
s 00002/00002/01780
d D 1.7 09/02/11 23:49:10 mrym 7 6
c 2.6.2
e
s 00008/00008/01774
d D 1.6 09/02/11 13:14:28 mrym 6 5
c 2.6.1 don't reset phy in epfe_reset_chip
e
s 00406/00405/01376
d D 1.5 09/02/06 21:28:22 mrym 5 4
c 2.6.0
e
s 00015/00017/01766
d D 1.4 07/01/07 15:23:27 mrym 4 3
c 
e
s 00018/00004/01765
d D 1.3 06/12/24 22:34:20 mrym 3 2
c 2.4.0 multicast hash bit calculation fixed
e
s 00026/00015/01743
d D 1.2 06/12/22 01:10:40 mrym 2 1
c 2.4.0
e
s 01758/00000/00000
d D 1.1 06/10/08 21:54:52 mrym 1 0
c date and time created 06/10/08 21:54:52 by mrym
e
u
U
f e 0
t
T
I 1
/*
 * epfe_gem.c : SMC EPIC II fast ethernet controler driver for Solaris.
 *
D 4
 * Copyright (c) 2002-2006 Masayuki Murayama.  All rights reserved.
E 4
I 4
D 5
 * Copyright (c) 2002-2007 Masayuki Murayama.  All rights reserved.
E 4
 * 
E 5
I 5
 * Copyright (c) 2002-2009 Masayuki Murayama.  All rights reserved.
 *
E 5
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
D 5
 * 
E 5
I 5
 *
E 5
 * 1. Redistributions of source code must retain the above copyright notice,
D 5
 *    this list of conditions and the following disclaimer. 
 * 
E 5
I 5
 *    this list of conditions and the following disclaimer.
 *
E 5
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
D 5
 *    and/or other materials provided with the distribution. 
 * 
E 5
I 5
 *    and/or other materials provided with the distribution.
 *
E 5
 * 3. Neither the name of the author nor the names of its contributors may be
 *    used to endorse or promote products derived from this software without
D 5
 *    specific prior written permission. 
 * 
E 5
I 5
 *    specific prior written permission.
 *
E 5
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
#pragma ident	"%W% %E%"

/*
D 5
 Change log

09/11/2003  0.0.0 starting coding.
I 3
12/24/2006  2.4.0 multicast hash bit calculation fixed
E 5
I 5
 * Change log
 *
 * 09/11/2003  0.0.0 starting coding.
 * 12/24/2006  2.4.0 multicast hash bit calculation fixed
E 5
E 3
 */

/*
D 5
 TODO:
	tx underrun
E 5
I 5
 * TODO:
 *	tx underrun
E 5
 */

/*
 * System Header files.
 */
#include <sys/types.h>
#include <sys/conf.h>
#include <sys/debug.h>
D 5
#include <sys/stropts.h>
#include <sys/stream.h>
#include <sys/strlog.h>
E 5
#include <sys/kmem.h>
D 5
#include <sys/stat.h>
#include <sys/kstat.h>
#include <sys/vtrace.h>
#include <sys/dlpi.h>
#include <sys/strsun.h>
#include <sys/ethernet.h>
E 5
#include <sys/modctl.h>
#include <sys/errno.h>
D 5
#include <sys/dditypes.h>
E 5
#include <sys/ddi.h>
#include <sys/sunddi.h>
D 5

E 5
I 5
#include <sys/byteorder.h>
#include <sys/ethernet.h>
E 5
#include <sys/pci.h>
D 5
#include "mii.h"
E 5
I 5

#include "gem_mii.h"
E 5
#include "gem.h"
#include "epicreg.h"

char	ident[] = "smsc epic driver v" VERSION;

/* Debugging support */
#ifdef DEBUG_LEVEL
static int epfe_debug = DEBUG_LEVEL;
D 5
#define	DPRINTF(n, args)	if (epfe_debug>(n)) cmn_err args
E 5
I 5
#define	DPRINTF(n, args)	if (epfe_debug > (n)) cmn_err args
E 5
#else
#define	DPRINTF(n, args)
#endif

/*
 * Useful macros and typedefs
 */
D 4
#define STRUCT_COPY(a, b)	bcopy(&(b), &(a), sizeof(a))

E 4
D 5
#if defined(sun4u)
# define LE16(x)	ddi_swap16(x)
# define LE32(x)	ddi_swap32(x)
# define LE64(x)	ddi_swap64(x)
#else
# define LE16(x)	(x)
# define LE32(x)	(x)
# define LE64(x)	(x)
#endif

E 5
#ifdef MAP_MEM
#define	FLSHB(dp, reg)		INB(dp, reg)
#define	FLSHW(dp, reg)		INW(dp, reg)
#define	FLSHL(dp, reg)		INL(dp, reg)
#else
#define	FLSHB(dp, reg)
#define	FLSHW(dp, reg)
#define	FLSHL(dp, reg)
#endif

/*
D 5
 * EPIC Tx descriptor and Rx descriptor implementation 
E 5
I 5
 * EPIC Tx descriptor and Rx descriptor implementation
E 5
 */
#define	MAXTXFRAGS	5

struct epic_tfd {
	struct epic_desc	desc;		/* 16 byte */
I 5
#if MAXTXFRAGS > 1
E 5
	uint32_t		:32;		/* 4 byte */
D 7
	uint32_t		nfrags;		/* 4 bytes */
E 7
I 7
	volatile uint32_t	nfrags;		/* 4 bytes */
E 7
	struct epic_frag	frag[MAXTXFRAGS];	/* 8 * MAXTXFRAGS */
I 5
#endif
E 5
};

D 5
#define	MAXRXFRAGS	5
E 5
I 5
#define	MAXRXFRAGS	1	/* 5 */
E 5

struct epic_rfd {
	struct epic_desc	desc;		/* 16 bytes */
#if MAXRXFRAGS > 1
	uint32_t		:32;		/* 4 byte */
D 7
	uint32_t		nfrags;		/* 4 byte */
E 7
I 7
	volatile uint32_t	nfrags;		/* 4 byte */
E 7
	struct epic_frag	frag[MAXRXFRAGS];
#endif
};

/*
 * Our configuration
 */
D 5
#if 0
E 5
I 5
#if 1
E 5
#define	INTR_MASK_COMMON	\
D 5
	(INT_CNT |	\
	 INT_RXE | INT_OVW | INT_RQE | INT_RCC | \
	 INT_TXU | INT_TCC | INT_TXC)
E 5
I 5
	(INT_CNT | INT_HCC |	\
	INT_RXE | INT_OVW | INT_RQE | INT_RCC | \
	INT_TXU | INT_TXC)
E 5
#else
#define	INTR_MASK_COMMON	\
D 5
	(INT_CNT |	\
	 INT_RXE | INT_OVW | INT_RQE | INT_RCC | \
	 INT_TXU | INT_TQE)
E 5
I 5
	(INT_CNT | INT_HCC |	\
	INT_RXE | INT_OVW | INT_RQE | INT_RCC | \
	INT_TXU | INT_TQE)
E 5
#endif
#define	INTR_BUSERR_170	\
D 5
			(INT_DPE_170 | INT_APE_170 | INT_PMA_170 | INT_PTA_170)
E 5
I 5
	(INT_DPE_170 | INT_APE_170 | INT_PMA_170 | INT_PTA_170)
E 5
#define	INTR_BUSERR_171	INT_FATAL_INT

#ifdef TEST_RX_EMPTY
D 5
# define RX_RING_SIZE	4
E 5
I 5
#define	RX_BUF_SIZE	4
E 5
#endif
#ifdef TEST_TXDESC_FULL
D 5
# define TX_RING_SIZE	4
# define TX_BUF_SIZE	64
E 5
I 5
#define	TX_RING_SIZE	4
#define	TX_BUF_SIZE	64
E 5
#endif

#ifndef TX_RING_SIZE
D 5
# define TX_RING_SIZE	64
E 5
I 5
#define	TX_RING_SIZE	64
E 5
#endif
#ifndef TX_BUF_SIZE
D 5
# define TX_BUF_SIZE	TX_RING_SIZE
E 5
I 5
#define	TX_BUF_SIZE	TX_RING_SIZE
E 5
#endif

D 5
#ifndef RX_RING_SIZE
# define RX_RING_SIZE	64
E 5
I 5
#ifndef RX_BUF_SIZE
#define	RX_BUF_SIZE	256
E 5
#endif
D 5
#define RX_BUF_SIZE	RX_RING_SIZE
E 5

#define	ONESEC			(drv_usectohz(1*1000000))
static int	epfe_tx_copy_thresh = 256;
static int	epfe_rx_copy_thresh = 256;

/*
 * Supported chips
 */
struct chip_info {
	uint16_t	venid;
	uint16_t	devid;
	uint8_t		rev_min;
	uint8_t		rev_max;
	uint8_t		chip_type;
	char		*name;
};

#define	EPIC_83C170	0
#define	EPIC_83C171	1
#define	EPIC_83C172	2
#define	EPIC_83C175	3

static struct chip_info epfe_chiptbl[] = {
	{0x10b8, 0x0005, 0x00, 0x05, EPIC_83C170, "SMSC LAN83C170"},
D 5
	{0x10b8, 0x0005, 0x06, 0x08, EPIC_83C171, "SMSC LAN83C171"},
	{0x10b8, 0x0005, 0x09, 0xff, EPIC_83C172, "SMSC LAN83C172"},
E 5
I 5
	{0x10b8, 0x0005, 0x06, 0x07, EPIC_83C171, "SMSC LAN83C171"},
	{0x10b8, 0x0005, 0x08, 0xff, EPIC_83C172, "SMSC LAN83C172"},
E 5
	{0x10b8, 0x0006, 0x00, 0xff, EPIC_83C175, "SMSC LAN83C175"},
};

D 5
#define CHIPTABLESIZE   (sizeof(epfe_chiptbl)/sizeof(struct chip_info))
E 5
I 5
#define	CHIPTABLESIZE	(sizeof (epfe_chiptbl) / sizeof (struct chip_info))
E 5

struct epfe_dev {
	struct chip_info	*chip;

	/* copy of registers */
	uint16_t	genctl;
	uint16_t	rxcon;
	uint8_t		txcon;
D 5
	boolean_t	tx_list_loaded;
E 5
	uint_t		need_to_reset;

	/* interrupt mask */
	uint32_t	our_intr_mask;
	uint32_t	intr_buserr;
	char		*int_bits;

#ifdef DEBUG_LEVEL
	seqnum_t	prev_rx_head;
	seqnum_t	prev_rx_tail;
#endif
};


/* ======================================================== */
D 5
 
E 5
I 5

E 5
/* mii operations */
static void  epfe_mii_sync(struct gem_dev *);
D 5
static uint16_t  epfe_mii_read(struct gem_dev *, uint_t);
E 5
I 5
static uint16_t epfe_mii_read(struct gem_dev *, uint_t);
E 5
static void epfe_mii_write(struct gem_dev *, uint_t, uint16_t);

/* nic operations */
static int epfe_attach_chip(struct gem_dev *);
static int epfe_reset_chip(struct gem_dev *);
D 2
static void epfe_init_chip(struct gem_dev *);
static void epfe_start_chip(struct gem_dev *);
E 2
I 2
static int epfe_init_chip(struct gem_dev *);
static int epfe_start_chip(struct gem_dev *);
E 2
static int epfe_stop_chip(struct gem_dev *);
D 2
static void epfe_set_media(struct gem_dev *);
static void epfe_set_rx_filter(struct gem_dev *);
static void epfe_get_stats(struct gem_dev *);
E 2
I 2
static int epfe_set_media(struct gem_dev *);
static int epfe_set_rx_filter(struct gem_dev *);
static int epfe_get_stats(struct gem_dev *);
E 2

/* descriptor operations */
static int epfe_tx_desc_write(struct gem_dev *dp, int slot,
D 5
		    ddi_dma_cookie_t *dmacookie, int frags, uint32_t flag);
E 5
I 5
    ddi_dma_cookie_t *dmacookie, int frags, uint64_t flag);
E 5
static void epfe_tx_start(struct gem_dev *dp, int slot, int frags);
static void epfe_rx_desc_write(struct gem_dev *dp, int slot,
D 5
		    ddi_dma_cookie_t *dmacookie, int frags);
E 5
I 5
    ddi_dma_cookie_t *dmacookie, int frags);
E 5
static uint_t epfe_tx_desc_stat(struct gem_dev *dp, int slot, int ndesc);
static uint64_t epfe_rx_desc_stat(struct gem_dev *dp, int slot, int ndesc);

static void epfe_tx_desc_init(struct gem_dev *dp, int slot);
static void epfe_rx_desc_init(struct gem_dev *dp, int slot);
static void epfe_tx_desc_clean(struct gem_dev *dp, int slot);
static void epfe_rx_desc_clean(struct gem_dev *dp, int slot);

/* interrupt handler */
D 5
static u_int epfe_interrupt(struct gem_dev *dp);
E 5
I 5
static uint_t epfe_interrupt(struct gem_dev *dp);
E 5

/* ======================================================== */

/* mapping attributes */
/* Data access requirements. */
static struct ddi_device_acc_attr epfe_dev_attr = {
	DDI_DEVICE_ATTR_V0,
	DDI_STRUCTURE_LE_ACC,
	DDI_STRICTORDER_ACC
};

/* On sparc, the buffers should be native endianness */
static struct ddi_device_acc_attr epfe_buf_attr = {
	DDI_DEVICE_ATTR_V0,
	DDI_NEVERSWAP_ACC,	/* native endianness */
	DDI_STRICTORDER_ACC
};

static ddi_dma_attr_t epfe_dma_attr_buf = {
	DMA_ATTR_V0,		/* dma_attr_version */
	0,			/* dma_attr_addr_lo */
	0xffffffffull,		/* dma_attr_addr_hi */
	0xffffffffull,		/* dma_attr_count_max */
	0, /* patched later */	/* dma_attr_align */
	0,			/* dma_attr_burstsizes */
	1,			/* dma_attr_minxfer */
	0xffffffffull,		/* dma_attr_maxxfer */
	0xffffffffull,		/* dma_attr_seg */
	0, /* patched later */	/* dma_attr_sgllen */
	1,			/* dma_attr_granular */
	0			/* dma_attr_flags */
};

static ddi_dma_attr_t epfe_dma_attr_desc = {
	DMA_ATTR_V0,		/* dma_attr_version */
	0,			/* dma_attr_addr_lo */
	0xffffffffull,		/* dma_attr_addr_hi */
	0xffffffffull,		/* dma_attr_count_max */
	4,			/* dma_attr_align */
	0,			/* dma_attr_burstsizes */
	1,			/* dma_attr_minxfer */
	0xffffffffull,		/* dma_attr_maxxfer */
	0xffffffffull,		/* dma_attr_seg */
	1,			/* dma_attr_sgllen */
	1,			/* dma_attr_granular */
	0			/* dma_attr_flags */
};

/* ======================================================== */
/*
 * misc runtime routines
 */
/* ======================================================== */
static int
epfe_log2(uint64_t val)
{
	int	i;

	if (val == 0) {
		return (0);
	}

D 5
	for (i = 0; i < sizeof(val)*8; i++) {
E 5
I 5
	for (i = 0; i < sizeof (val)*8; i++) {
E 5
		if ((val & 1) != 0) {
			break;
		}
		val >>= 1;
	}
	return (i);
}

/* ======================================================== */
/*
 * HW manupilation routines
 */
/* ======================================================== */

static int
epfe_reset_chip(struct gem_dev *dp)
{
	int		i;
	uint32_t	val;
D 6
	struct epfe_dev	*lp = (struct epfe_dev *)dp->private;
E 6
I 6
	struct epfe_dev	*lp = dp->private;
E 6

	DPRINTF(1, (CE_CONT, "!%s: %s: called", dp->name, __func__));
	/*
	 * Reset the chip.
D 6
	 * XXX - don't reset PHY
E 6
I 6
	 * XXX - don't reset PHY, otherwise it may not be detected.
E 6
	 */
D 5
	OUTL(dp, GENCTL, GC_SOFTRESET);
E 5
I 5
D 6
	OUTL(dp, GENCTL, GC_RESET_PHY | GC_SOFTRESET);
E 6
I 6
	OUTL(dp, GENCTL, GC_SOFTRESET);
E 6
E 5

	/* it need 15 pci cycle */
	drv_usecwait(10);

D 5
#ifdef notdef
	/* XXX - wait for tx and rx become idle */
	for (i = 0; (INL(dp, INTSTAT) & (INT_TXIDLE | INT_RXIDLE))
					!= (INT_TXIDLE | INT_RXIDLE); i++) {
		if (i > 1000) {
			cmn_err(CE_CONT,
			"!%s: epfe_reset_chip: failed to reset the nic",
			dp->name);
			break;
		}
		drv_usecwait(10);
	}
#endif
E 5
	lp->genctl = 0;
	OUTL(dp, GENCTL, lp->genctl);

	for (i = 0; i < 16; i++) {
		OUTL(dp, TEST1, 0x0008);
	}

	/* enable phy */
	OUTL(dp, MIICFG, MIICFG_EN_SMI);

	/* exit power down mode */
	if (lp->chip->chip_type == EPIC_83C175) {
		val = INL(dp, NVCTL) &
D 5
			~(NVCTL_GPIO2| NVCTL_GPIO1| NVCTL_GPOE2| NVCTL_GPOE1);
		OUTL(dp, NVCTL, val | NVCTL_FETPWRPHY| NVCTL_PHYPWRDOWN_N);
E 5
I 5
		    ~(NVCTL_GPIO2| NVCTL_GPIO1| NVCTL_GPOE2 | NVCTL_GPOE1);
		OUTL(dp, NVCTL, val | NVCTL_FETPWRPHY | NVCTL_PHYPWRDOWN_N);
E 5

	}
	return (GEM_SUCCESS);
}

D 2
static void
E 2
I 2
static int
E 2
epfe_init_chip(struct gem_dev *dp)
{
	uint32_t	val;
D 5
	struct epfe_dev	*lp = (struct epfe_dev *)dp->private;
E 5
I 5
	struct epfe_dev	*lp = dp->private;
E 5

	DPRINTF(1, (CE_CONT, "!%s: %s: called", dp->name, __func__));

	/* 00 COMMAND: do nothing */

	/* 04 INTSTAT STATUS: do nothing */

	/* 08 INTMASK : set OUR_INTR_MASK later */
	OUTL(dp, INTMASK, lp->our_intr_mask);
D 5
	DPRINTF(2, (CE_CONT, "!%s: epfe_init_chip: intmask:%b",
			dp->name, INL(dp, INTMASK), lp->int_bits));
E 5
I 5
	DPRINTF(2, (CE_CONT, "!%s: %s: intmask:%b",
	    dp->name, __func__, INL(dp, INTMASK), lp->int_bits));
E 5

D 5
	/* 0C GENERAL CONTROL */	
	/* XXX - tx underrun happens in case of GC_RXDMAPRI */
E 5
I 5
	/* 0C GENERAL CONTROL */
E 5
	if (dp->rxthr <= 32) {
		val = GC_RXFIFO_32;
	} else if (dp->rxthr <= 64) {
		val = GC_RXFIFO_64;
	} else if (dp->rxthr <= 96) {
		val = GC_RXFIFO_96;
	} else {
		val = GC_RXFIFO_128;
	}
D 5
	lp->genctl = val | GC_ONECOPY | GC_MEMRD_LINE /*| GC_RXDMAPRI */;
E 5
I 5
	/* XXX - tx underrun happens in case of GC_RXDMAPRI */
	lp->genctl = val | GC_ONECOPY | GC_MEMRD_LINE | GC_TXDMAPRI;
E 5
	OUTL(dp, GENCTL, lp->genctl);
D 5
	DPRINTF(2, (CE_CONT, "!%s: epfe_init_chip: genctl:%b",
			dp->name, INL(dp, GENCTL), GENCTL_BITS));
E 5
I 5
	DPRINTF(0, (CE_CONT, "!%s: %s: genctl:%b",
	    dp->name, __func__, INL(dp, GENCTL), GENCTL_BITS));
E 5

	/* 10 NON-VOLATILE CONTROL : dont touch */

	/* 14 EEPROM CTL: release MA bus */
	OUTL(dp, EECTL, 0);
D 5

E 5
I 5
#if 0
E 5
	/* 18 PBLCNT(6bit width): shoud we limit max burst length = 128 byte */
	OUTL(dp, PBLCNT,
D 5
		min(max(dp->txmaxdma, dp->txmaxdma)/sizeof(uint32_t), 0x3f));

E 5
I 5
	    min(max(dp->txmaxdma, dp->rxmaxdma)/sizeof (uint32_t), 0x3f));
#endif
E 5
	/* 20 CRC ERROR COUNTER: clear later in get_stats */
	/* 24 FRAME ALIGNMENT ERROR COUNTER: clear later in get_stats */
	/* 28 MISSED PACKET COUNTER: clear later in get_stats */

	/* 30 MII control: do nothing */
	/* 34 MII data: do nothing */
	/* 38 MII configration: initialize in mii_init */

	/* 3C interpacket gap register : don't touch */
D 5
	DPRINTF(2, (CE_CONT, "!%s: epfe_init_chip: ipg:%x",
			dp->name, INL(dp, IPG)));
E 5
I 5
	DPRINTF(2, (CE_CONT, "!%s: %s: ipg:%x",
	    dp->name, __func__, INL(dp, IPG)));
E 5

	/* 40-4C LAN0-2: don't touch */
	/* 4C ID_CHK: don't touch */
	/* 50-5C MC0-3: don't touch */

	/* 60 RXCON: receive control register */
	lp->rxcon = RXCON_RUNT | RXCON_ERR;
	OUTL(dp, RXCON, lp->rxcon);
D 5
	DPRINTF(2, (CE_CONT, "!%s: rxcon:%b", dp->name,
			INL(dp, RXCON), RXCON_BITS));
E 5
I 5
	DPRINTF(2, (CE_CONT, "!%s: %s: rxcon:%b",
	    dp->name, __func__, INL(dp, RXCON), RXCON_BITS));
E 5

	/* 70 TXCON: transmit control register, we don't use early_tx */
D 5
	lp->txcon = TXCON_SLOT(512);
E 5
I 5
	lp->txcon = TXCON_SLOT(512) /* | TXCON_EARLY */;
E 5
	OUTL(dp, TXCON, lp->txcon);
D 5
	DPRINTF(2, (CE_CONT, "!%s: txcon:%b", dp->name,
			INL(dp, TXCON), TXCON_BITS));
E 5
I 5
	DPRINTF(0, (CE_CONT, "!%s: %s: txcon:%b",
	    dp->name, __func__, INL(dp, TXCON), TXCON_BITS));
E 5

	/* 74 TXTEST: clear tx test register */
	OUTL(dp, TXTEST, 0);

	/* 84 PRCDAR: PCI recieve current descriptor address */
	OUTL(dp, PRCDAR, dp->rx_ring_dma);

	/* A4 PRSTAT: clear PCI receive dma status */
	OUTL(dp, PRSTAT, 0);

	/* B0 PRCPTHR: receive copy threshold */
	OUTL(dp, PRCPTHR, 0);

	/* C4 PTCDAR: PCI transmit current descriptor address */
	OUTL(dp, PTCDAR, dp->tx_ring_dma);

	/* DC ETXTHR: tx threshold */
D 5
#ifdef notdef
E 5
	OUTL(dp, ETXTHR, 0x100);
D 5
#else
	OUTL(dp, ETXTHR, min(dp->txthr, 0x7ff));
#endif
E 5

D 5
	lp->tx_list_loaded = B_FALSE;

E 5
#ifdef DEBUG_LEVEL
	lp->prev_rx_head = -1;
	lp->prev_rx_tail = -1;
#endif
I 2
D 5

E 5
	return (GEM_SUCCESS);
E 2
}

static uint32_t
epfe_mcast_hash(struct gem_dev *dp, uint8_t *addr)
{
D 3
	return (gem_ether_crc_be(addr, ETHERADDRL));
E 3
I 3
	/* hash key is 6 bits of MSB in be-crc */
	return (gem_ether_crc_be(addr, ETHERADDRL) >> (32 - 6));
E 3
}

D 2
static void
E 2
I 2
static int
E 2
D 5
epfe_set_rx_filter(struct gem_dev *dp)	
E 5
I 5
epfe_set_rx_filter(struct gem_dev *dp)
E 5
{
	int		i;
	uint8_t		mode;
	uint8_t		*mac;
	uint16_t	mhash[4];
D 5
	struct epfe_dev	*lp = (struct epfe_dev *)dp->private;
E 5
I 5
	struct epfe_dev	*lp = dp->private;
E 5

	DPRINTF(1, (CE_CONT, "!%s: %s: called", dp->name, __func__));

I 3
#if DEBUG_LEVEL > 2
	for (i = 0; i < dp->mc_count; i++) {
		cmn_err(CE_CONT,
D 5
		"!%s: adding mcast(%d) %02x:%02x:%02x:%02x:%02x:%02x",
			dp->name, i,
			dp->mc_list[i].addr.ether_addr_octet[0],
			dp->mc_list[i].addr.ether_addr_octet[1],
			dp->mc_list[i].addr.ether_addr_octet[2],
			dp->mc_list[i].addr.ether_addr_octet[3],
			dp->mc_list[i].addr.ether_addr_octet[4],
			dp->mc_list[i].addr.ether_addr_octet[5]);
E 5
I 5
		    "!%s: adding mcast(%d) %02x:%02x:%02x:%02x:%02x:%02x",
		    dp->name, i,
		    dp->mc_list[i].addr.ether_addr_octet[0],
		    dp->mc_list[i].addr.ether_addr_octet[1],
		    dp->mc_list[i].addr.ether_addr_octet[2],
		    dp->mc_list[i].addr.ether_addr_octet[3],
		    dp->mc_list[i].addr.ether_addr_octet[4],
		    dp->mc_list[i].addr.ether_addr_octet[5]);
E 5
	}
#endif
E 3
	mode = RXCON_BR | RXCON_MULT;

	/* clear multicast hash table */
D 5
	bzero(mhash, sizeof(mhash));
E 5
I 5
	bzero(mhash, sizeof (mhash));
E 5

D 5
	if ((dp->rxmode & RXMODE_PROMISC) != 0) {
E 5
I 5
	if (dp->rxmode & RXMODE_PROMISC) {
E 5
		/* promiscous */
		mode |= RXCON_PROMISC;

		/* need to set all bit in the multcast hash table */
D 5
		for (i =0; i < 4; i++) {
E 5
I 5
		for (i = 0; i < 4; i++) {
E 5
			mhash[i] = 0xffff;
		}
D 5
	}
	else if ((dp->rxmode & RXMODE_ALLMULTI) != 0 || dp->mc_count > 64/2) {
E 5
I 5
	} else if ((dp->rxmode & RXMODE_ALLMULTI) || dp->mc_count > 64/2) {
E 5
		for (i = 0; i < 4; i++) {
			mhash[i] = 0xffff;
		}
D 5
	}
	else if (dp->mc_count > 0) {
E 5
I 5
	} else if (dp->mc_count > 0) {
E 5
		/* Make multicast hash table */
		for (i = 0; i < dp->mc_count; i++) {
			uint_t	k;
D 3
			/* hash key is 6 bits of LSB in be-crc */
			k = dp->mc_list[i].hash & (4*16 - 1);
E 3
I 3
			k = dp->mc_list[i].hash;
E 3
			mhash[k / 16] |= 1 << (k % 16);
		}
	}

	/* set rx mode */
D 3
	DPRINTF(2, (CE_CONT,
E 3
I 3
	DPRINTF(3, (CE_CONT,
E 3
D 5
"!%s: set_rx_filter(%x): setting mode: %b mhash[3-0]: %04x %04x %04x %04x",
		dp->name, dp->rxmode, mode | lp->rxcon, RXCON_BITS, 
		mhash[3], mhash[2], mhash[1], mhash[0]));
E 5
I 5
	    "!%s: %s(%x): "
	    "setting mode: %b mhash[3-0]: %04x %04x %04x %04x",
	    dp->name, __func__, dp->rxmode, mode | lp->rxcon, RXCON_BITS,
	    mhash[3], mhash[2], mhash[1], mhash[0]));
E 5

	/* stop rx temporary */
	if (dp->mac_active) {
		OUTL(dp, COMMAND, CMD_STOP_RX | CMD_STOP_RDMA);

		/* XXX - wait for rx become idle */
D 5
		i = 0;
		while ((INL(dp, INTSTAT) & INT_RXIDLE) == 0) {
			if (i++>1000) {
E 5
I 5
		for (i = 0; (INL(dp, INTSTAT) & INT_RXIDLE) == 0; i++) {
			if (i > 1000) {
E 5
				cmn_err(CE_CONT,
D 5
			"!%s: epfe_set_rx_filter: failed to stop the nic",
				dp->name);
E 5
I 5
				    "!%s: %s: failed to stop the nic",
				    dp->name, __func__);
E 5
				break;
			}
			drv_usecwait(10);
		}
	}

	OUTL(dp, RXCON, lp->rxcon | mode);

	/* set multicast hash table up */
	for (i = 0; i < 4; i++) {
		OUTL(dp, MC0 + i*4, mhash[i]);
	}

	/* set station address */
	mac = dp->cur_addr.ether_addr_octet;
	for (i = 0; i < ETHERADDRL/2; i++) {
		OUTL(dp, LAN0 + i*4, (mac[i*2+1] << 8) | mac[i*2]);
	}

	/* enable rx again */
	if (dp->mac_active) {
		OUTL(dp, COMMAND, CMD_RXQUEUED | CMD_START_RX);
	}
I 2

	return (GEM_SUCCESS);
E 2
}

D 2
static void
E 2
I 2
static int
E 2
epfe_set_media(struct gem_dev *dp)
{
	int		i;
D 5
	struct epfe_dev	*lp;
E 5
	uint8_t		old;
	extern int	gem_speed_value[];
I 5
	struct epfe_dev	*lp = dp->private;
E 5

D 5
	lp = (struct epfe_dev *) dp->private;

E 5
	DPRINTF(1, (CE_CONT,
D 5
		"!%s: %s: setting %dM bps, %s duplex mode",
		dp->name, __func__, gem_speed_value[dp->speed],
		dp->full_duplex ? "full" : "half"));
E 5
I 5
	    "!%s: %s: setting %dM bps, %s duplex mode",
	    dp->name, __func__, gem_speed_value[dp->speed],
	    dp->full_duplex ? "full" : "half"));
E 5

	/*
	 * Notify current duplex mode to MAC
	 */
	old = lp->txcon;
	lp->txcon &= ~TXCON_LPBK;
	if (dp->full_duplex) {
		lp->txcon |= TXCON_LPBK_FDX;
	}

	if (old == lp->txcon) {
		/* no need to change media mode */
D 5
		return;
E 5
I 5
		return (GEM_SUCCESS);
E 5
	}

	/* stop tx and rx temporary */
	if (dp->mac_active) {
D 5
		OUTL(dp, COMMAND, CMD_STOP_RX | CMD_STOP_RDMA | CMD_STOP_TDMA);
E 5
I 5
		OUTL(dp, COMMAND,
		    CMD_STOP_RX | CMD_STOP_RDMA | CMD_STOP_TDMA);
E 5

		/* XXX - wait for rx become idle */
D 5
		for (i = 0; (INL(dp, INTSTAT) & (INT_TXIDLE | INT_RXIDLE))
					!= (INT_TXIDLE | INT_RXIDLE); i++) {
E 5
I 5
		for (i = 0;
		    (INL(dp, INTSTAT) & (INT_TXIDLE | INT_RXIDLE))
		    != (INT_TXIDLE | INT_RXIDLE); i++) {
E 5
			if (i > 1000) {
				cmn_err(CE_CONT,
D 5
				"!%s: epfe_set_media: failed to stop the nic",
				dp->name);
E 5
I 5
				    "!%s: %s: failed to stop the nic",
				    dp->name, __func__);
E 5
				break;
			}
			drv_usecwait(10);
		}
	}

	/* change mode */
	OUTL(dp, TXCON, lp->txcon);
I 5
	DPRINTF(0, (CE_CONT, "!%s: %s: txcon:%b",
	    dp->name, __func__, INL(dp, TXCON), TXCON_BITS));
E 5

	/* enable rx and tx again */
	if (dp->mac_active) {
D 5
		OUTL(dp, COMMAND, CMD_TXQUEUED | CMD_RXQUEUED | CMD_START_RX);
E 5
I 5
		OUTL(dp, COMMAND,
		    CMD_TXQUEUED | CMD_RXQUEUED | CMD_START_RX);
E 5
	}
I 2

	return (GEM_SUCCESS);
E 2
}

D 2
static void
E 2
I 2
static int
E 2
epfe_start_chip(struct gem_dev *dp)
{
D 5
	struct epfe_dev	*lp = (struct epfe_dev *)dp->private;
E 5
I 5
	struct epfe_dev	*lp = dp->private;
E 5

	DPRINTF(1, (CE_CONT, "!%s: %s: called", dp->name, __func__));

	/* Enable receiver */
	OUTL(dp, COMMAND, CMD_START_RX | CMD_RXQUEUED);

	/* Enable interrupt mask */
	lp->genctl |= GC_INTEN;
	OUTL(dp, GENCTL, lp->genctl);
I 2

	return (GEM_SUCCESS);
E 2
}

static int
epfe_stop_chip(struct gem_dev *dp)
{
D 5
	struct epfe_dev	*lp = (struct epfe_dev *)dp->private;
E 5
I 5
	struct epfe_dev	*lp = dp->private;
E 5

	DPRINTF(1, (CE_CONT, "!%s: %s: called", dp->name, __func__));

D 4
	/* inhibit interrupt */
E 4
I 4
	/* inhibit interrupts */
E 4
	lp->genctl &= ~GC_INTEN;
	OUTL(dp, GENCTL, lp->genctl);

	/* stop RxDMA, TxDMA and receiver */
	OUTL(dp, COMMAND, CMD_STOP_RDMA | CMD_STOP_TDMA | CMD_STOP_RX);

	return (GEM_SUCCESS);
}


static uint16_t
epfe_read_eeprom(struct gem_dev *dp, uint_t offset)
{
	int		i;
	uint16_t	ret;
	uint8_t		chip_select;
	uint8_t		di;
	uint8_t		cfga_saved;

D 5
#define	EPC_EEPROM_DELAY(dp)	{INL(dp, EECTL); INL(dp, EECTL);}
E 5
I 5
#define	EPC_EEPROM_DELAY(dp)	{ INL(dp, EECTL); INL(dp, EECTL); }
E 5
#define	EE93C46_READ	6

	/* aquire MA bus and ensure de-assert chip select */
	chip_select = EECTL_EN;
	OUTL(dp, EECTL, chip_select);

	/* assert chip select */
	chip_select |= EECTL_EECS;
	OUTL(dp, EECTL, chip_select);
	EPC_EEPROM_DELAY(dp);

	/* make a read command for eeprom */
	offset = (offset & 0x3f) | (EE93C46_READ << 6);

	for (i = 10; i >= 0; i--) {
		/* send 1 bit */
		di = ((offset >> i) & 1) << EECTL_EEDI_SHIFT;

		OUTL(dp, EECTL, chip_select | di);
		EPC_EEPROM_DELAY(dp);

		OUTL(dp, EECTL, chip_select | di | EECTL_EESK);
		EPC_EEPROM_DELAY(dp);
	}

	OUTL(dp, EECTL, chip_select);
	EPC_EEPROM_DELAY(dp);

	/* get the reply and construct a 16bit value */
	ret = 0;
	for (i = 0; i < 16; i++) {
		/* Get 1 bit */
		OUTL(dp, EECTL, chip_select | EECTL_EESK);
		EPC_EEPROM_DELAY(dp);

		ret = (ret << 1)
		    | ((INL(dp, EECTL) >> EECTL_EEDO_SHIFT) & 1);

		OUTL(dp, EECTL, chip_select);
		EPC_EEPROM_DELAY(dp);
	}

	/* negate chip_select */
	OUTL(dp, EECTL, EECTL_EN);
	EPC_EEPROM_DELAY(dp);

	OUTL(dp, EECTL, 0);

	return (ret);
}

#ifdef DEBUG_LEVEL
D 5
#define	EPIC_EEPROM_SIZE	8	/* in word */
E 5
I 5
#define	EPIC_EEPROM_SIZE	128	/* in word */
E 5
static void
epfe_eeprom_dump(struct gem_dev *dp)
{
	int		i;
	uint16_t	prom[EPIC_EEPROM_SIZE];

	for (i = 0; i < EPIC_EEPROM_SIZE; i++) {
		prom[i] = epfe_read_eeprom(dp, i);
	}

	cmn_err(CE_CONT, "!%s: eeprom dump:", dp->name);
	for (i = 0; i < EPIC_EEPROM_SIZE; i += 4) {
D 5
		cmn_err(CE_CONT, "!0x%02x: 0x%04x 0x%04x 0x%04x 0x%04x", 
			i, prom[i], prom[i + 1], prom[i + 2], prom[i + 3]);
E 5
I 5
		cmn_err(CE_CONT, "!0x%02x: 0x%04x 0x%04x 0x%04x 0x%04x",
		    i, prom[i], prom[i + 1], prom[i + 2], prom[i + 3]);
E 5
	}
}
#endif /* DEBUG_LEVEL */

static int
D 5
epfe_attach_chip(struct gem_dev *dp)	
E 5
I 5
epfe_attach_chip(struct gem_dev *dp)
E 5
{
	int		i;
	uint8_t		*m;
	uint16_t	val;
D 5
	struct epfe_dev	*lp = (struct epfe_dev *)dp->private;
E 5
I 5
	struct epfe_dev	*lp = dp->private;
E 5

D 5
	DPRINTF(1, (CE_CONT, "!%s: %s: nvctl: %b, miicfg: %b",
			dp->name, __func__, INL(dp, NVCTL), NVCTL_BITS,
			INL(dp, MIICFG), MIICFG_BITS));
E 5
I 5
	DPRINTF(0, (CE_CONT, "!%s: %s: nvctl: %b, miicfg: %b",
	    dp->name, __func__, INL(dp,  NVCTL), NVCTL_BITS,
	    INL(dp, MIICFG), MIICFG_BITS));
E 5
#ifdef notdef
	OUTL(dp, NVCTL,
D 5
		(INL(dp, NVCTL) & NVCTL_IPG_DLY) | NVCTL_GPOE1 | NVCTL_GPIO1);
E 5
I 5
	    (INL(dp, NVCTL) & NVCTL_IPG_DLY) | NVCTL_GPOE1 | NVCTL_GPIO1);
E 5
#endif
I 5
	if (lp->chip->chip_type != EPIC_83C175) {
		OUTL(dp, NVCTL, (INL(dp, NVCTL) & ~0x003C) | 0x4800);
	}
	DPRINTF(0, (CE_CONT, "!%s: %s: nvctl: %b",
	    dp->name, __func__, INL(dp,  NVCTL), NVCTL_BITS));

E 5
	m = &dp->dev_addr.ether_addr_octet[0];
	for (i = 0; i < ETHERADDRL/2; i++) {
		val = epfe_read_eeprom(dp, i);
D 5
		*m++ = (uint8_t) val;
		*m++ = (uint8_t) (val >> 8);
E 5
I 5
		*m++ = (uint8_t)val;
		*m++ = (uint8_t)(val >> 8);
E 5
#ifdef notdef
		OUTL(dp, LAN0 + i*4, val);
#endif
	}
D 5
#if DEBUG_LEVEL > 2
E 5
I 5
#if DEBUG_LEVEL > 0
E 5
	epfe_eeprom_dump(dp);
#endif

	/* clear statistics */
D 4
	epfe_get_stats(dp);
E 4
I 4
	(void) epfe_get_stats(dp);
E 4
D 5
	bzero(&dp->stats, sizeof(dp->stats));
E 5
I 5
	bzero(&dp->stats, sizeof (dp->stats));
E 5

	/* makeintr mask */
	if (lp->chip->chip_type == EPIC_83C170) {
		lp->intr_buserr = INTR_BUSERR_170;
		lp->int_bits = INT_BITS_170;
	} else {
		lp->intr_buserr = INTR_BUSERR_171;
D 5
		lp->int_bits = INT_BITS_170;
E 5
I 5
		lp->int_bits = INT_BITS_171;
E 5
	}
	lp->our_intr_mask = INTR_MASK_COMMON | lp->intr_buserr;

	dp->misc_flag |= GEM_VLAN_SOFT;

I 5
	dp->rxthr = 128;

E 5
	return (GEM_SUCCESS);
}


D 2
static void
E 2
I 2
static int
E 2
epfe_get_stats(struct gem_dev *dp)
{
I 5
	DPRINTF(4, (CE_CONT, "!%s:%s: called", dp->name, __func__));

E 5
	/* 20 CRC ERROR COUNTER: clear on read */
D 5
	(void) INL(dp, CRCCNT);
E 5
I 5
	(void) INB(dp, CRCCNT);
E 5

	/* 24 FRAME ALIGNMENT ERROR COUNTER: clear on read */
D 5
	(void) INL(dp, ALICNT);
E 5
I 5
	(void) INB(dp, ALICNT);
E 5

	/* 28 MISSED PACKET COUNTER: clear on read */
D 5
	dp->stats.missed += INL(dp, MPCNT) & MPCNT_MASK;
E 5
I 5
	dp->stats.missed += INB(dp, MPCNT) & MPCNT_MASK;
E 5
I 2

	return (GEM_SUCCESS);
E 2
}

/*
 * discriptor  manupiration
 */
static int
epfe_tx_desc_write(struct gem_dev *dp, int slot,
D 5
		ddi_dma_cookie_t *dmacookie, int frags, uint32_t flag)
E 5
I 5
    ddi_dma_cookie_t *dmacookie, int frags, uint64_t flag)
E 5
{
	int			i;
	uint_t			len;
I 5
	uint32_t		size;
	uint32_t		addr;
	uint32_t		csr;
	uint32_t		stat;
E 5
	struct epic_tfd		*tfdp;
	struct epic_frag	*tfp;
	ddi_dma_cookie_t	*dcp;
D 5
	struct epfe_dev		*lp = (struct epfe_dev *) dp->private;
E 5
I 5
	struct epfe_dev		*lp = dp->private;
E 5

D 5
#if DEBUG_LEVEL > 3
E 5
I 5
#if DEBUG_LEVEL > 0
E 5
	/* force to cause interrupt upon tx completion */
	flag |= GEM_TXFLAG_INTR;
#endif
	tfdp = &((struct epic_tfd *)dp->tx_ring)[slot];
#if DEBUG_LEVEL > 2
	cmn_err(CE_CONT,
D 5
	"!%s: epfe_tx_desc_write seqnum: %d, slot %d, frags: %d flag: %d",
		dp->name, dp->tx_desc_tail, slot, frags, flag);
E 5
I 5
	    "!%s: %s seqnum: %d, slot %d, frags: %d flag: %lld",
	    dp->name, __func__, dp->tx_desc_tail, slot, frags, flag);
E 5
	for (i = 0; i < frags; i++) {
		cmn_err(CE_CONT, "!%d: addr: 0x%x, len: 0x%x",
D 5
			i, dmacookie[i].dmac_address, dmacookie[i].dmac_size);
E 5
I 5
		    i, dmacookie[i].dmac_address, dmacookie[i].dmac_size);
E 5
	}
#endif
	/*
	 * Make fragment section
	 */
I 5
	if (flag & GEM_TXFLAG_INTR) {
		csr |= TD_CTL_IAF;
	} else {
		csr = 0;
	}
#if MAXTXFRAGS > 1
E 5
	len = 0;
D 5
	tfdp->nfrags = LE32(frags);
E 5
I 5
	tfdp->nfrags = LE_32((uint32_t)frags);
E 5

	for (i = 0, dcp = dmacookie, tfp = &tfdp->frag[0];
D 5
			i < frags;
				dcp++, tfp++, i++) {
		len += dcp->dmac_size;
		tfp->frag_len = LE32(dcp->dmac_size);
		tfp->frag_ptr = LE32(dcp->dmac_address);
E 5
I 5
	    i < frags; dcp++, tfp++, i++) {
		size = dcp->dmac_size;
		addr = dcp->dmac_address;
		len += size;
		tfp->frag_len = LE_32(size);
		tfp->frag_ptr = LE_32(addr);
E 5
	}
D 5
	if (len < ETHERMIN) {
		len = ETHERMIN;
	}

E 5
	/*
	 * Setup descriptor section
	 */
D 5
	tfdp->desc.desc_ctl = LE32(
			((flag & GEM_TXFLAG_INTR) != 0 ? TD_CTL_IAF : 0)
			| TD_CTL_FRAGLIST); /* XXX length field must be zero*/
E 5
I 5
	/* XXX - length field must be zero */
	csr |= TD_CTL_FRAGLIST;
	/* keep tfdp->desc.desc_buf */
E 5
	/* keep tfdp->desc.desc_next */
D 5
	/* keep tfdp->desc.desc_bufaddr */
E 5
I 5
#else
	csr |= TD_CTL_LASTDSCR;
	ASSERT(frags == 1);
	size = dmacookie->dmac_size;
	addr = dmacookie->dmac_address;
	tfdp->desc.desc_buf = LE_32(addr);
	/* keep rfdp->desc.desc_next */
E 5

I 5
	csr |= size;
	len = size;
#endif
	tfdp->desc.desc_ctl = LE_32(csr);

E 5
	/* finally set OWN bit in txstat */
I 5
	if (len < ETHERMIN) {
		len = ETHERMIN;
	}
	stat = len << TD_STAT_LEN_SHIFT;
E 5
	if ((flag & GEM_TXFLAG_HEAD) == 0) {
D 5
		tfdp->desc.desc_stat =
			LE32((len << TD_STAT_LEN_SHIFT) | TD_STAT_OWN);
	} else {
		tfdp->desc.desc_stat = LE32(len << TD_STAT_LEN_SHIFT);
E 5
I 5
		stat |= TD_STAT_OWN;
E 5
	}
I 5
	tfdp->desc.desc_stat = LE_32(stat);
E 5

	DPRINTF(2, (CE_CONT, "  slot[%d]: %08x %08x %08x %08x",
D 5
		slot, tfdp->desc.desc_stat, tfdp->desc.desc_buf,
		tfdp->desc.desc_ctl, tfdp->desc.desc_next));
E 5
I 5
	    slot, tfdp->desc.desc_stat, tfdp->desc.desc_buf,
	    tfdp->desc.desc_ctl, tfdp->desc.desc_next));
E 5

	return (1);
}

static void
epfe_tx_start(struct gem_dev *dp, int start_slot, int nslot)
{
D 5
	struct epfe_dev		*lp = (struct epfe_dev *) dp->private;
E 5
I 5
	struct epfe_dev		*lp = dp->private;
E 5

	if (nslot > 1) {
		gem_tx_desc_dma_sync(dp,
D 5
			start_slot + 1, nslot - 1, DDI_DMA_SYNC_FORDEV);
E 5
I 5
		    start_slot + 1, nslot - 1, DDI_DMA_SYNC_FORDEV);
E 5
	}

D 5
	((struct epic_tfd *) dp->tx_ring)[start_slot].desc.desc_stat |=
							LE32(TD_STAT_OWN);
E 5
I 5
	((struct epic_tfd *)dp->tx_ring)[start_slot].desc.desc_stat |=
	    LE_32(TD_STAT_OWN);
E 5
	gem_tx_desc_dma_sync(dp, start_slot, 1, DDI_DMA_SYNC_FORDEV);

D 5
	/* notify to mac that new descriptor is added. */
	if (dp->mac_active && !lp->tx_list_loaded) {
		OUTL(dp, COMMAND, CMD_TXQUEUED);
		lp->tx_list_loaded = B_TRUE;
	}
E 5
I 5
	OUTL(dp, COMMAND, CMD_TXQUEUED);
E 5
}

static void
epfe_rx_desc_write(struct gem_dev *dp, int slot,
D 5
	    ddi_dma_cookie_t *dmacookie, int frags)
E 5
I 5
    ddi_dma_cookie_t *dmacookie, int frags)
E 5
{
	int			i;
I 5
	uint32_t		size;
	uint32_t		addr;
E 5
	struct epic_rfd		*rfdp;
	struct epic_frag	*rfp;
	ddi_dma_cookie_t	*dcp;

	rfdp = &((struct epic_rfd *)dp->rx_ring)[slot];

#if DEBUG_LEVEL > 2
D 5
	cmn_err(CE_CONT, "!%s: rx_desc_write seqnum: %d, slot %d, frags: %d",
		dp->name, dp->rx_desc_tail, slot, frags);
E 5
I 5
	cmn_err(CE_CONT, "!%s: %s seqnum: %d, slot %d, frags: %d",
	    dp->name, __func__, dp->rx_desc_tail, slot, frags);
E 5
	for (i = 0; i < frags; i++) {
		cmn_err(CE_CONT, "!  frag: %d addr: 0x%x, len: 0x%x",
D 5
			i, dmacookie[i].dmac_address, dmacookie[i].dmac_size);
E 5
I 5
		    i, dmacookie[i].dmac_address, dmacookie[i].dmac_size);
E 5
	}
#endif
	/*
	 * Setup fragment section
	 */
#if MAXRXFRAGS > 1
	ASSERT(frags <= MAXRXFRAGS);
D 5
	rfdp->nfrags = LE32(frags);
E 5
I 5
	rfdp->nfrags = LE_32(frags);
E 5
	for (i = 0, dcp = dmacookie, rfp = &rfdp->frag[0];
D 5
			i < frags;
				dcp++, rfp++, i++) {
		rfp->frag_len = LE32(dcp->dmac_size);
		rfp->frag_ptr = LE32(dcp->dmac_address);
E 5
I 5
	    i < frags; dcp++, rfp++, i++) {
		size = dcp->dmac_size;
		addr = dcp->dmac_address;
		rfp->frag_len = LE_32(size);
		rfp->frag_ptr = LE_32(addr);
E 5
	}

	/*
	 * Setup descriptor section
	 */
D 5
	rfdp->desc.desc_ctl = LE32(RD_CTL_FRAGLIST);
					/* XXX - length field must be zero */
E 5
I 5
	rfdp->desc.desc_ctl = LE_32(RD_CTL_FRAGLIST);

	/* XXX - length field must be zero */
E 5
	/* keep rfdp->desc.desc_next */
	/* keep rfdp->desc.desc_buf */
#else
	ASSERT(frags == 1);
D 5
	rfdp->desc.desc_ctl = LE32(dmacookie->dmac_size);
	rfdp->desc.desc_buf = LE32(dmacookie->dmac_address);
E 5
I 5
	size = dmacookie->dmac_size;
	addr = dmacookie->dmac_address;
	rfdp->desc.desc_ctl = LE_32(size);
	rfdp->desc.desc_buf = LE_32(addr);
E 5
	/* keep rfdp->desc.desc_next */
#endif

	/* finally set OWN bit in txstat */
D 5
	rfdp->desc.desc_stat = LE32(RD_STAT_OWN);
E 5
I 5
	rfdp->desc.desc_stat = LE_32(RD_STAT_OWN);
E 5

	DPRINTF(2, (CE_CONT, "  slot[%d]: %08x %08x %08x %08x",
D 5
		slot, rfdp->desc.desc_stat, rfdp->desc.desc_buf,
		rfdp->desc.desc_ctl, rfdp->desc.desc_next));
E 5
I 5
	    slot, rfdp->desc.desc_stat, rfdp->desc.desc_buf,
	    rfdp->desc.desc_ctl, rfdp->desc.desc_next));
E 5
}

static uint_t
epfe_tx_desc_stat(struct gem_dev *dp, int slot, int ndesc)
{
	struct epic_tfd		*tfdp;
	uint32_t		txstat;
	uint32_t		cc;
D 5
	struct epfe_dev		*lp = (struct epfe_dev *) dp->private;
E 5
I 5
	struct epfe_dev		*lp = dp->private;
E 5

	tfdp = &((struct epic_tfd *)dp->tx_ring)[slot];
D 5
	DPRINTF(2, (CE_CONT,
		"%s: epfe_tx_desc_stat: slot:%d, txstat:0x%b intstat:0x%b",
		dp->name, slot, tfdp->desc.desc_stat, TD_STAT_BITS,
		INL(dp, INTSTAT), lp->int_bits));
E 5
I 5
	DPRINTF(4, (CE_CONT,
	    "!%s: %s: slot:%d, txstat:0x%b intstat:0x%b",
	    dp->name, __func__, slot, tfdp->desc.desc_stat, TD_STAT_BITS,
	    INL(dp, INTSTAT), lp->int_bits));
E 5

D 5
	txstat = LE32(tfdp->desc.desc_stat);
	if ((txstat & TD_STAT_OWN) != 0) {
E 5
I 5
	txstat = tfdp->desc.desc_stat;
	txstat = LE_32(txstat);
	if (txstat & TD_STAT_OWN) {
E 5
		/* not transmitted */
		return (0);
	}

	cc = (txstat & TXSTAT_CC) >> TXSTAT_CC_SHIFT;

D 5
	if ((txstat & TXSTAT_PT) != 0) {
E 5
I 5
	if (txstat & TXSTAT_PT) {
E 5
		dp->stats.collisions += cc;
		if (cc == 0) {
			if ((txstat & TXSTAT_ND) == 0) {
				dp->stats.defer++;
			}
		} else if (cc == 1) {
			dp->stats.first_coll++;
		} else {
			dp->stats.multi_coll++;
		}
D 5
	}
	else {
E 5
I 5
	} else {
E 5
		dp->stats.errxmt++;
D 5
		DPRINTF(4, (CE_CONT, "%s: tx err: txstat:%b",
			dp->name, txstat, TD_STAT_BITS));
E 5
I 5
		DPRINTF(4, (CE_CONT, "!%s: %s: tx err: txstat:%b",
		    dp->name, __func__, txstat, TD_STAT_BITS));
E 5

		if ((txstat & TXSTAT_OWC) != 0) {
			/* late collision */
			dp->stats.xmtlatecoll++;
		}

		if ((txstat & TXSTAT_UN) != 0) {
			/* this must not happen here */
			dp->stats.underflow++;
			DPRINTF(1, (CE_WARN,
D 5
				"!%s: unexpected tx fifo underflow happened",
				dp->name));
E 5
I 5
			    "!%s: unexpected tx fifo underflow happened",
			    dp->name));
E 5
		}

D 5
		if ((txstat & TXSTAT_CSL) != 0) {
E 5
I 5
		if (txstat & TXSTAT_CSL) {
E 5
			dp->stats.nocarrier++;
		}

		if (cc >= 16) {
			/* max collision exceeded */
			dp->stats.excoll++;
			dp->stats.collisions += 16;
		}
	}
	return (GEM_TX_DONE);
}

static uint64_t
epfe_rx_desc_stat(struct gem_dev *dp, int slot, int ndesc)
{
D 5
	struct epic_rfd		*rfdp;
	uint_t			rfs;
	uint_t			len;
	uint_t			flag;
	uint_t			rxstat;
E 5
I 5
	struct epic_rfd	*rfdp;
	uint64_t	len;
	uint64_t	flag;
	uint32_t	rxstat;
E 5

I 5
	flag = GEM_RX_DONE;
E 5
	rfdp = &((struct epic_rfd *)dp->rx_ring)[slot];

D 5
	rxstat = LE32(rfdp->desc.desc_stat);
	len    = (rxstat & RD_STAT_LEN) >> RD_STAT_LEN_SHIFT;
	flag   = GEM_RX_DONE;
E 5
I 5
	rxstat = rfdp->desc.desc_stat;
	rxstat = LE_32(rxstat);
E 5

I 5
	len = (rxstat & RD_STAT_LEN) >> RD_STAT_LEN_SHIFT;

E 5
	DPRINTF(2, (CE_CONT,
D 5
		"%s: epfe_rx_desc_stat: slot:%d, rxstat:0x%b",
		dp->name, slot, rxstat, RD_STAT_BITS));
E 5
I 5
	    "!%s: %s: slot:%d, rxstat:0x%b",
	    dp->name, __func__, slot, rxstat, RD_STAT_BITS));
E 5

D 5
	if ((rxstat & RD_STAT_OWN) != 0) {
		/* still nic owns, not received */
E 5
I 5
	if (rxstat & RD_STAT_OWN) {
		/* the nic still owns the buffer, packets are not received */
E 5
		return (0);
	}

	if (len > ETHERFCSL) {
		len -= ETHERFCSL;
	}

	if ((rxstat & RXSTAT_PRI) == 0) {
		/* error packet */
		dp->stats.errrcv++;
D 5
		if ((rxstat & RXSTAT_FAE) != 0) {
E 5
I 5
		if (rxstat & RXSTAT_FAE) {
E 5
			dp->stats.frame++;
		}
D 5
		if ((rxstat & RXSTAT_CRC) != 0) {
E 5
I 5
		if (rxstat & RXSTAT_CRC) {
E 5
			dp->stats.crc++;
		}
D 5
		if ((rxstat & RD_STAT_FLE) != 0) {
E 5
I 5
		if (rxstat & RD_STAT_FLE) {
E 5
			dp->stats.frame_too_long++;
		}

		flag = GEM_RX_ERR;
	}

	return (flag | len);
}

static void
epfe_tx_desc_init(struct gem_dev *dp, int slot)
{
I 5
	uint32_t	addr;
E 5
	struct epic_tfd		*tfdp;

	tfdp = &((struct epic_tfd *)dp->tx_ring)[slot];

	/* invalidate this tfd */
	/* XXX - don't clear desc_next because it may have been initialized */
	tfdp->desc.desc_stat = 0;
D 5
	tfdp->desc.desc_ctl  = 0;

E 5
I 5
	tfdp->desc.desc_ctl = 0;
#if MAXTXFRAGS > 1
E 5
	/* make a link to the fragment descriptor array */
D 5
	tfdp->desc.desc_buf = LE32(
		((uint32_t) dp->tx_ring_dma) +
		slot * sizeof(struct epic_tfd) +
		((uint32_t) &((struct epic_tfd *) NULL)->nfrags));

E 5
I 5
	addr = ((uint32_t)dp->tx_ring_dma)
	    + slot * sizeof (struct epic_tfd)
	    + ((uint32_t)&((struct epic_tfd *)NULL)->nfrags);
	tfdp->desc.desc_buf = LE_32(addr);
#else
#ifdef SANITY
	tfdp->desc.desc_buf = 0;
#endif
#endif
E 5
	/* link it to the previous tfd */
D 5
	tfdp = &((struct epic_tfd *)dp->tx_ring)[SLOT(slot - 1, TX_RING_SIZE)];
	tfdp->desc.desc_next = LE32(
		((uint32_t)dp->tx_ring_dma) + slot*sizeof(struct epic_tfd));
E 5
I 5
	tfdp = &((struct epic_tfd *)
	    dp->tx_ring)[SLOT(slot - 1, dp->gc.gc_tx_ring_size)];
	addr = ((uint32_t)dp->tx_ring_dma) + slot*sizeof (struct epic_tfd);
	tfdp->desc.desc_next = LE_32(addr);
E 5
}

static void
epfe_rx_desc_init(struct gem_dev *dp, int slot)
{
D 5
	int			i;
E 5
I 5
	int		i;
	uint32_t	addr;
E 5
	struct epic_rfd		*rfdp;

	rfdp = &((struct epic_rfd *)dp->rx_ring)[slot];

	/* invalidate this rfd */
	/* XXX - don't clear desc_next because it may have been initialized */
	rfdp->desc.desc_stat = 0;
D 5
	rfdp->desc.desc_ctl  = 0;
E 5
I 5
	rfdp->desc.desc_ctl = 0;
E 5

#if MAXRXFRAGS > 1
	/* make a link to the fragment descriptor array */
D 5
	rfdp->desc.desc_buf = LE32(
		((uint32_t) dp->rx_ring_dma) +
		slot*sizeof(struct epic_rfd) +
		((uint32_t) &((struct epic_rfd *) NULL)->nfrags));
E 5
I 5
	addr = ((uint32_t)dp->rx_ring_dma)
	    + slot*sizeof (struct epic_rfd)
	    + ((uint32_t)&((struct epic_rfd *)NULL)->nfrags);
	rfdp->desc.desc_buf = LE_32(addr);
E 5
#else
D 5
# ifdef SANITY
E 5
I 5
#ifdef SANITY
E 5
	rfdp->desc.desc_buf = 0;
D 5
# endif
E 5
#endif
I 5
#endif
E 5

	/* link it to the previous rfd */
D 5
	rfdp = &((struct epic_rfd *)dp->rx_ring)[SLOT(slot - 1, RX_RING_SIZE)];
	rfdp->desc.desc_next = LE32(
		((uint32_t)dp->rx_ring_dma) + slot*sizeof(struct epic_rfd));
E 5
I 5
	rfdp = &((struct epic_rfd *)
	    dp->rx_ring)[SLOT(slot - 1, dp->gc.gc_rx_ring_size)];
	addr = ((uint32_t)dp->rx_ring_dma) + slot*sizeof (struct epic_rfd);
	rfdp->desc.desc_next = LE_32(addr);
E 5
}

static void
epfe_tx_desc_clean(struct gem_dev *dp, int slot)
{
	struct epic_tfd		*tfdp;

	tfdp = &((struct epic_tfd *)dp->tx_ring)[slot];

	/* keep desc_addr and desc_next */
	tfdp->desc.desc_stat = 0;

#ifdef SANITY
	tfdp->desc.desc_ctl = 0;

I 5
#if MAXTXFRAGS > 1
E 5
	/* clear fragment list field */
	tfdp->nfrags = 0;
D 5
	bzero(&tfdp->frag[0], sizeof(tfdp->frag));
E 5
I 5
	bzero(&tfdp->frag[0], sizeof (tfdp->frag));
E 5
#endif
I 5
#endif
E 5
}

static void
epfe_rx_desc_clean(struct gem_dev *dp, int slot)
{
	struct epic_rfd		*rfdp;

	rfdp = &((struct epic_rfd *)dp->rx_ring)[slot];

	/* keep desc_addr and desc_next */
	rfdp->desc.desc_stat = 0;

#ifdef SANITY
	rfdp->desc.desc_ctl = 0;

D 5
# if MAXRXFRAGS > 1
E 5
I 5
#if MAXRXFRAGS > 1
E 5
	/* clear fragment list field */
	rfdp->nfrags = 0;
D 5
	bzero(&rfdp->frag[0], sizeof(rfdp->frag));
# endif
E 5
I 5
	bzero(&rfdp->frag[0], sizeof (rfdp->frag));
E 5
#endif
I 5
#endif
E 5
}

/*
 * Device depend interrupt handler
 */
D 5
static u_int
E 5
I 5
static uint_t
E 5
epfe_interrupt(struct gem_dev *dp)
{
	int		i;
	uint32_t	intstat;
	uint_t		restart_tx = 0;
	boolean_t	print_warn = B_FALSE;
D 5
	struct epfe_dev	*lp = (struct epfe_dev *)dp->private;
E 5
I 5
	struct epfe_dev	*lp = dp->private;
E 5

	/*
	 * Read interrupt status
	 * Do not use IntStatusAck here. It clears IntEnable too.
	 */
	intstat = INL(dp, INTSTAT);
D 5
	if ((intstat & lp->our_intr_mask) == 0) {
E 5
I 5

	if ((intstat & INT_INT_ACTV) == 0) {
E 5
		/* Not for us */
D 5
		if (intstat != 0) {
			OUTL(dp, INTSTAT, intstat & 0x7fff);
E 5
I 5
		if (intstat) {
			OUTL(dp, INTSTAT, intstat);
E 5
		}
		return (DDI_INTR_UNCLAIMED);
	}

D 5
	/*
	 * Acknowledge to the interrupt.
	 * Mask interrupt signal first, because PCI bus recognize
	 * interrupts by edge-triggered method.
	 */
	lp->genctl &= ~GC_INTEN;
	OUTL(dp, GENCTL, lp->genctl);

	DPRINTF(2, (CE_CONT, "%s: Interrupt, intstat: %b",
			   dp->name, intstat, lp->int_bits));
E 5
I 5
	DPRINTF(4, (CE_CONT, "%s: Interrupt, intstat: %b",
	    dp->name, intstat, lp->int_bits));
E 5
	if (!dp->mac_active) {
		/*
		 * the device is not active.
		 * side effect: left interrupt masked.
		 */
D 5
		OUTL(dp, INTSTAT, intstat & 0x7fff);
E 5
I 5
		OUTL(dp, INTSTAT, intstat);
E 5

		return (DDI_INTR_CLAIMED);
	}

D 5
	OUTL(dp, INTSTAT, intstat & 0x7fff);
E 5
I 5
	/* don't mask any interrupts reason, otherwise system may hang */
	OUTL(dp, INTSTAT, intstat);
E 5
	FLSHL(dp, INTSTAT);
D 5
#if 0
E 5
I 5

E 5
	intstat &= lp->our_intr_mask;
D 5
#endif
E 5
#ifdef notdef
	/* ignore */
	/* INT_INT_ACTV	 : interrupt active */
	/* RCT: receive copy threshold crossed */
	/* INT_PREI */

	/* not interrupt */
	/* INT_RCTS :	  Receive copy threshold status */
	/* INT_TXIDLE :	 transmit idle */
	/* INT_RXIDLE :	 receive idle */
	/* INT_RSV :	 receive status valid */
	/* INT_TCIP :	 transmit copy in progress */
	/* INT_RCIP :	 receive copy in progress */
	/* INT_RBE : Receive buffer empty : ignore */
#endif
	/* counter overflow */
D 5
	if ((intstat & INT_CNT) != 0) {
E 5
I 5
	if (intstat & INT_CNT) {
E 5
		/*
		 * as statistics counters will overflow soon, collect them.
		 */
D 5
		epfe_get_stats(dp);
E 5
I 5
		(void) epfe_get_stats(dp);
E 5
	}

D 5
	/* RCC : receive copy complete : normal*/
	/* RXE : receive error : normal*/
	if ((intstat & (INT_RCC  | INT_RCT_171 |
			INT_PREI | INT_RQE | INT_OVW)) != 0) {
E 5
I 5
	/* RCC : receive copy complete : normal */
	/* RXE : receive error : normal */
	if (intstat &
	    (INT_RCC  | INT_RCT_171 | INT_PREI | INT_RQE | INT_OVW)) {
E 5
		/*
D 5
		 * packets were received, or receive error happened
E 5
I 5
		 * packets were received, or receive errors happened
E 5
		 */
#ifdef DEBUG_LEVEL
		lp->prev_rx_head = dp->rx_active_head;
		lp->prev_rx_tail = dp->rx_active_tail;
#endif
		(void) gem_receive(dp);
	}

	/* TCC: transmit chain complete : normal */
	/* TXC: transmit complete : normal */
D 5
	if ((intstat & (INT_TCC | INT_TXC)) != 0) {
E 5
I 5
	if (intstat & (INT_TCC | INT_TXC)) {
E 5
		if (gem_tx_done(dp)) {
			restart_tx = INTR_RESTART_TX;
		}
	}

D 5
	/* TQE: transmit queue empty : normal */
	/* XXX use TCC instead of TQE because it cause bogus intr. */
	if ((intstat & INT_TQE) != 0) {
		mutex_enter(&dp->xmitlock);
		if (dp->tx_desc_head != dp->tx_desc_tail) {
			/* kick Tx */
			OUTL(dp, COMMAND, CMD_TXQUEUED);
		} else {
			lp->tx_list_loaded = B_FALSE;
		}
		mutex_exit(&dp->xmitlock);
	}

E 5
	/* RQE : receive queue empty : warning only */
	/* OVW : receive buffer overflow : fatal */
D 5
	if ((intstat & (INT_RQE | INT_OVW)) != 0) {
E 5
I 5
	if (intstat & (INT_RQE | INT_OVW)) {
E 5
#ifdef DEBUG_LEVEL
D 5
		DPRINTF(0, (CE_WARN,
			"%s: %s int:%b rx_desc<%d %d><%d %d>",
			dp->name,
			(intstat & INT_RQE) ? "no rx queue" : "rx overflow",
			intstat, lp->int_bits,
			lp->prev_rx_head, lp->prev_rx_tail,
			dp->rx_active_head, dp->rx_active_tail));
E 5
I 5
		DPRINTF(2, (CE_WARN,
		    "!%s: %s int:%b rx_desc<%d %d><%d %d>",
		    dp->name,
		    (intstat & INT_RQE) ? "no rx queue" : "rx overflow",
		    intstat, lp->int_bits,
		    lp->prev_rx_head, lp->prev_rx_tail,
		    dp->rx_active_head, dp->rx_active_tail));
E 5
#endif
D 5
		if ((intstat & INT_RQE) != 0) {
E 5
I 5
		if (intstat & INT_RQE) {
E 5
			dp->stats.norcvbuf++;
D 5
		}
		if ((intstat & INT_OVW) != 0) {
E 5
I 5
		} else if (intstat & INT_OVW) {
E 5
			dp->stats.overflow++;
		}
		OUTL(dp, COMMAND, CMD_RXQUEUED);
	}

	/* transmit underrun : fatal */
D 5
	if ((intstat & INT_TXU) != 0) {
E 5
I 5
	if (intstat & INT_TXU) {
E 5
		/*
		 * Packets was transfered into TxFIFO or error happened
		 */
		/* recover from tx underrun */
		cmn_err(CE_WARN, "!%s: tx underrun", dp->name);
		OUTL(dp, COMMAND, CMD_TXUGO);
	}

	/* should not happen: unexpected */
	/* GPIO(2) is low */
D 5
	if ((intstat & INT_GP2_INT) != 0) {
E 5
I 5
	if (intstat & INT_GP2_INT) {
E 5
		cmn_err(CE_WARN, "!%s: unexpected interrupt: %b",
D 5
			dp->name, intstat, lp->int_bits);
E 5
I 5
		    dp->name, intstat, lp->int_bits);
E 5
	}

	/* should not happen: bus error */
	/* PCI target abort */
	/* PCI master abort */
	/* PCI address parity error */
	/* PCI data parity error */
	/* INT_FATAL_INT : fatal error (27:24) occured */
	/* PME: power management event */
D 5
	if ((intstat & lp->intr_buserr) != 0) {
E 5
I 5
	if (intstat & lp->intr_buserr) {
E 5
		cmn_err(CE_WARN,
D 5
		"!%s: PCI bus error intstat %b, resetting the chip...",
			dp->name, intstat, lp->int_bits);
E 5
I 5
		    "!%s: PCI bus error intstat %b, resetting the chip...",
		    dp->name, intstat, lp->int_bits);
E 5

		/* restart the chip */
		lp->need_to_reset = B_TRUE;
		print_warn = B_TRUE;
		goto x;
	}

x:
D 5
        if (lp->need_to_reset) {
		DPRINTF(2, (CE_CONT,
			"%s: epfe_interrupt: isr:%b, resetting the chip ...",
			dp->name, intstat, lp->int_bits));
E 5
I 5
	if (lp->need_to_reset) {
		DPRINTF(-1, (CE_CONT,
		    "%s: %s: isr:%b, resetting the chip ...",
		    dp->name, __func__, intstat, lp->int_bits));
E 5

D 2
                gem_restart_nic(dp, B_TRUE);
E 2
I 2
D 5
                gem_restart_nic(dp, GEM_RESTART_KEEP_BUF);
E 5
I 5
		(void) gem_restart_nic(dp, GEM_RESTART_KEEP_BUF);
E 5
E 2

		restart_tx = INTR_RESTART_TX;
		lp->need_to_reset = B_FALSE;
D 5
        }
E 5
I 5
	}
E 5

	/*
	 * Recover Interrput Enable register
	 */
D 5
	DPRINTF(4, (CE_CONT, "%s: epfe_inter done: intstat: %b",
			   dp->name, INL(dp, INTSTAT), lp->int_bits));
E 5
I 5
	DPRINTF(4, (CE_CONT, "%s: %s done: intstat: %b",
	    dp->name, __func__, INL(dp, INTSTAT), lp->int_bits));
E 5

D 5
	if ((dp->misc_flag & GEM_NOINTR) == 0) {
		lp->genctl |= GC_INTEN;
		OUTL(dp, GENCTL, lp->genctl);
	}

E 5
	return (DDI_INTR_CLAIMED | restart_tx);
}

/*
 * HW depend MII routine
 */

static void
epfe_mii_sync(struct gem_dev *dp)
{
	/* do nothing */
}

static uint16_t
epfe_mii_read(struct gem_dev *dp, uint_t reg)
{
	int		i;
	uint32_t	ctl;
	uint32_t	val;

	ctl = (dp->mii_phy_addr << MMCTL_PHYADDR_SHIFT)
	    | (reg << MMCTL_PHYREG_SHIFT)
	    | MMCTL_READ;

D 5
	DPRINTF(4, (CE_CONT, "%s: epfe_mii_read: addr:0x%x reg:0x%x ctl:0x%x",
		dp->name, dp->mii_phy_addr, reg, ctl));
E 5
I 5
	DPRINTF(4, (CE_CONT, "%s: %s: addr:0x%x reg:0x%x ctl:0x%x",
	    dp->name, __func__, dp->mii_phy_addr, reg, ctl));
E 5

	OUTL(dp, MMCTL, ctl);
	drv_usecwait(10);

	for (i = 0; (INL(dp, MMCTL) & MMCTL_READ) != 0; i++) {
		/* wait */
		if (i > 100) {
			/* timeout */
D 4
			cmn_err(CE_WARN, "!%s: epfe_mii_read: timeout",
				dp->name);
			return (0xffff);
E 4
I 4
			cmn_err(CE_WARN, "!%s: %s: timeout",
D 5
				dp->name, __func__);
E 5
I 5
			    dp->name, __func__);
E 5
			return (0);
E 4
		}
		drv_usecwait(10);
	}

	val = INL(dp, MMDATA);
#if DEBUG_LEVEL > 4
	if (val == 0 || val == 0xffff) {
D 4
		cmn_err(CE_CONT, "%s: epfe_mii_read: val:0x%x", dp->name, val);
E 4
I 4
		cmn_err(CE_CONT, "%s: %s: val:0x%x", dp->name, __func__, val);
E 4
	}
#endif
I 5
	if (reg == MII_STATUS && val == 0xffff) {
		val = 0;
	}
#ifdef CONFIG_10M_ONLY
	if (reg == MII_STATUS) {
		val &= ~(MII_STATUS_100_BASEX | MII_STATUS_100_BASEX_FD);
	}
#endif
E 5
	return (val);
}

static void
epfe_mii_write(struct gem_dev *dp, uint_t reg, uint16_t val)
{
	int		i;
	uint32_t	ctl;

	ctl = (dp->mii_phy_addr << MMCTL_PHYADDR_SHIFT)
	    | (reg << MMCTL_PHYREG_SHIFT)
	    | MMCTL_WRITE;

	OUTL(dp, MMDATA, val);
	OUTL(dp, MMCTL, ctl);
	drv_usecwait(10);

	for (i = 0; (INL(dp, MMCTL) & MMCTL_WRITE) != 0; i++) {
		/* wait */
		if (i > 100) {
			/* timeout */
D 4
			cmn_err(CE_WARN, "!%s: epfe_mii_write: timeout",
				dp->name);
E 4
I 4
			cmn_err(CE_WARN, "!%s: %s: timeout",
D 5
				dp->name, __func__);
E 5
I 5
			    dp->name, __func__);
E 5
E 4
			return;
		}
		drv_usecwait(10);
	}
}

/* ======================================================== */
/*
 * OS depend (device driver) routine
 */
/* ======================================================== */
static int
epfeattach(dev_info_t *dip, ddi_attach_cmd_t cmd)
{
	int			i;
	ddi_acc_handle_t	conf_handle;
	int			ret;
	int			vid;
	int			did;
	int			unit;
	struct chip_info	*p;
	int			val;
	const char		*drv_name;
	struct gem_dev		*dp;
	struct epfe_dev		*lp;
	void			*base;
	ddi_acc_handle_t	regs_handle;
	struct gem_conf		*gcp;
	uint8_t			revid;

D 5
	unit     = ddi_get_instance(dip);
E 5
I 5
	unit = ddi_get_instance(dip);
E 5
	drv_name = ddi_driver_name(dip);

	DPRINTF(3, (CE_CONT, "%s%d: %s: called", drv_name, unit, __func__));

	if (pci_config_setup(dip, &conf_handle) != DDI_SUCCESS) {
D 5
		cmn_err(CE_WARN, "!%s: ddi_regs_map_setup failed",
			drv_name);
E 5
I 5
		cmn_err(CE_WARN, "!%s%d: pci_config_setup failed",
		    drv_name, unit);
E 5
		goto err;
	}

	pci_config_put16(conf_handle, PCI_CONF_COMM,
D 5
		PCI_COMM_IO | PCI_COMM_MAE | PCI_COMM_ME |
			pci_config_get16(conf_handle, PCI_CONF_COMM));
E 5
I 5
	    PCI_COMM_IO | PCI_COMM_MAE | PCI_COMM_ME |
	    pci_config_get16(conf_handle, PCI_CONF_COMM));
E 5

I 5
D 6
        DPRINTF(0, (CE_CONT,
            "!%s%d: ilr 0x%08x, latency_timer:0x%02x",
            drv_name, unit,
            pci_config_get32(conf_handle, PCI_CONF_ILINE),
            pci_config_get8(conf_handle, PCI_CONF_LATENCY_TIMER)));
E 6
I 6
	DPRINTF(0, (CE_CONT,
	    "!%s%d: ilr 0x%08x, latency_timer:0x%02x",
	    drv_name, unit,
	    pci_config_get32(conf_handle, PCI_CONF_ILINE),
	    pci_config_get8(conf_handle, PCI_CONF_LATENCY_TIMER)));
E 6

E 5
	/* ensure D0 mode */
	(void) gem_pci_set_power_state(dip, conf_handle, PCI_PMCSR_D0);

D 5
	vid  = pci_config_get16(conf_handle, PCI_CONF_VENID);
	did  = pci_config_get16(conf_handle, PCI_CONF_DEVID);
	revid= pci_config_get8(conf_handle, PCI_CONF_REVID);
E 5
I 5
	vid = pci_config_get16(conf_handle, PCI_CONF_VENID);
	did = pci_config_get16(conf_handle, PCI_CONF_DEVID);
	revid = pci_config_get8(conf_handle, PCI_CONF_REVID);
E 5

	pci_config_teardown(&conf_handle);

	switch (cmd) {
	case DDI_RESUME:
		return (gem_resume(dip));

	case DDI_ATTACH:
		/*
		 * Check if chip is supported.
		 */
		for (i = 0, p = epfe_chiptbl; i < CHIPTABLESIZE; i++, p++) {
			if (p->venid == vid && p->devid == did &&
			    p->rev_min <= revid && revid <= p->rev_max) {
				/* found */
				cmn_err(CE_CONT,
D 5
			"!%s%d: %s (vid: 0x%04x, did: 0x%04x, revid: 0x%02x)",
				drv_name, unit, p->name, vid, did, revid);
E 5
I 5
				    "!%s%d: %s "
				    "(vid:%04x, did:%04x, revid: 0x%02x)",
				    drv_name, unit, p->name, vid, did, revid);
E 5
				break;
			}
		}
		if (i >= CHIPTABLESIZE) {
			/* Not found */
			cmn_err(CE_WARN,
D 5
			"!%s: epfe_attach: wrong PCI venid/devid (0x%x, 0x%x)",
				drv_name, vid, did);
E 5
I 5
			    "!%s: %s: wrong PCI venid/devid (0x%x, 0x%x)",
			    drv_name, __func__, vid, did);
E 5

			/* assuming latest chipset */
			p = &epfe_chiptbl[CHIPTABLESIZE-1];
		}

D 5
                /* Map in the device registers.  */
                if (gem_pci_regs_map_setup(dip,
E 5
I 5
		/* Map in the device registers. */
		if (gem_pci_regs_map_setup(dip,
E 5
#ifdef MAP_MEM
D 5
			PCI_ADDR_MEM32, PCI_ADDR_MASK,
E 5
I 5
		    PCI_ADDR_MEM32, PCI_ADDR_MASK,
E 5
#else
D 5
			PCI_ADDR_IO, PCI_ADDR_MASK,
E 5
I 5
		    PCI_ADDR_IO, PCI_ADDR_MASK,
E 5
#endif
D 5
			&epfe_dev_attr,
                        (caddr_t *)&base, &regs_handle) != DDI_SUCCESS) {
                        goto err;
                }
E 5
I 5
		    &epfe_dev_attr,
		    (void *)&base, &regs_handle) != DDI_SUCCESS) {
			goto err;
		}
E 5

		/* construct gem configration */
D 5
		gcp = (struct gem_conf *) kmem_zalloc(sizeof(*gcp), KM_SLEEP);
E 5
I 5
		gcp = kmem_zalloc(sizeof (*gcp), KM_SLEEP);
E 5

		/* name */
		sprintf(gcp->gc_name, "%s%d", drv_name, unit);

		/* consistency on tx and rx */
D 5
		gcp->gc_tx_buf_align = sizeof(uint8_t) - 1;
E 5
I 5
		gcp->gc_tx_buf_align = sizeof (uint32_t) - 1;
E 5
		gcp->gc_tx_max_frags = MAXTXFRAGS;
		gcp->gc_tx_max_descs_per_pkt = 1;
D 5
		gcp->gc_tx_desc_unit_shift = epfe_log2(sizeof(struct epic_tfd));
		gcp->gc_tx_buf_size  = TX_BUF_SIZE;
E 5
I 5
		gcp->gc_tx_desc_unit_shift =
		    epfe_log2(sizeof (struct epic_tfd));
		gcp->gc_tx_buf_size = TX_BUF_SIZE;
E 5
D 2
		gcp->gc_tx_buf_limit = gcp->gc_tx_buf_size;
E 2
		gcp->gc_tx_ring_size = TX_RING_SIZE;
D 5
		gcp->gc_tx_ring_limit= gcp->gc_tx_ring_size;
I 2
		gcp->gc_tx_buf_limit =
				min(gcp->gc_tx_buf_size, gcp->gc_tx_ring_limit);
E 2
		gcp->gc_tx_auto_pad  = B_TRUE;
E 5
I 5
		gcp->gc_tx_ring_limit = gcp->gc_tx_ring_size - 1;
		gcp->gc_tx_buf_limit = gcp->gc_tx_buf_size;

		/* XXX - autopad doesn't work */
		gcp->gc_tx_auto_pad = B_TRUE;
E 5
		gcp->gc_tx_copy_thresh = epfe_tx_copy_thresh;
D 5
		gcp->gc_tx_desc_write_oo = B_TRUE;
E 5

D 5
		gcp->gc_rx_buf_align = sizeof(uint8_t) - 1;
E 5
I 5
		gcp->gc_rx_buf_align = sizeof (uint32_t) - 1;
E 5
		gcp->gc_rx_max_frags = MAXRXFRAGS;
D 5
		gcp->gc_rx_desc_unit_shift = epfe_log2(sizeof(struct epic_rfd));
		gcp->gc_rx_ring_size = RX_RING_SIZE;
D 2
		gcp->gc_rx_buf_max   = RX_BUF_SIZE;
E 2
I 2
		gcp->gc_rx_buf_max   = min(RX_BUF_SIZE, gcp->gc_rx_ring_size);
E 5
I 5
		gcp->gc_rx_desc_unit_shift =
		    epfe_log2(sizeof (struct epic_rfd));
		gcp->gc_rx_ring_size = RX_BUF_SIZE;
		gcp->gc_rx_buf_max = gcp->gc_rx_ring_size - 1;
E 5
E 2
		gcp->gc_rx_copy_thresh = epfe_rx_copy_thresh;
D 5
		gcp->gc_io_area_size   = 0;
E 5

I 5
		gcp->gc_io_area_size = 0;

E 5
		/* map attributes */
D 4
		STRUCT_COPY(gcp->gc_dev_attr, epfe_dev_attr);
		STRUCT_COPY(gcp->gc_buf_attr, epfe_buf_attr);
		STRUCT_COPY(gcp->gc_desc_attr, epfe_buf_attr);
E 4
I 4
		gcp->gc_dev_attr = epfe_dev_attr;
		gcp->gc_buf_attr = epfe_buf_attr;
		gcp->gc_desc_attr = epfe_buf_attr;
E 4

		/* dma attributes */
D 4
		STRUCT_COPY(gcp->gc_dma_attr_desc, epfe_dma_attr_desc);
E 4
I 4
		gcp->gc_dma_attr_desc = epfe_dma_attr_desc;
E 4

D 4
		STRUCT_COPY(gcp->gc_dma_attr_txbuf, epfe_dma_attr_buf);
E 4
I 4
		gcp->gc_dma_attr_txbuf = epfe_dma_attr_buf;
E 4
D 5
		gcp->gc_dma_attr_txbuf.dma_attr_align  = gcp->gc_tx_buf_align+1;
E 5
I 5
		gcp->gc_dma_attr_txbuf.dma_attr_align =
		    gcp->gc_tx_buf_align + 1;
E 5
		gcp->gc_dma_attr_txbuf.dma_attr_sgllen = gcp->gc_tx_max_frags;

D 4
		STRUCT_COPY(gcp->gc_dma_attr_rxbuf, epfe_dma_attr_buf);
E 4
I 4
		gcp->gc_dma_attr_rxbuf = epfe_dma_attr_buf;
E 4
D 5
		gcp->gc_dma_attr_rxbuf.dma_attr_align  = gcp->gc_rx_buf_align+1;
E 5
I 5
		gcp->gc_dma_attr_rxbuf.dma_attr_align =
		    gcp->gc_rx_buf_align + 1;
E 5
		gcp->gc_dma_attr_rxbuf.dma_attr_sgllen = gcp->gc_rx_max_frags;

		/* time out parameters */
D 5
		gcp->gc_tx_timeout = 5*ONESEC;
E 5
I 5
		gcp->gc_tx_timeout = 3*ONESEC;
E 5
		gcp->gc_tx_timeout_interval = ONESEC;

		/* flow control */
		gcp->gc_flow_control = FLOW_CONTROL_NONE;

D 5
		/* mii mode */
		gcp->gc_mii_mode = GEM_MODE_100BASETX;

E 5
		/* MII timeout parameters */
		gcp->gc_mii_link_watch_interval = ONESEC;
D 5
		gcp->gc_mii_an_watch_interval   = ONESEC/10;
E 5
I 5
		gcp->gc_mii_an_watch_interval = ONESEC/10;
E 5
		gcp->gc_mii_reset_timeout = MII_RESET_TIMEOUT;	/* 1 sec */
		gcp->gc_mii_an_timeout = MII_AN_TIMEOUT;	/* 5 sec */
		gcp->gc_mii_an_wait = 0;
		gcp->gc_mii_linkdown_timeout = MII_LINKDOWN_TIMEOUT;

		/* MII work arounds */
		gcp->gc_mii_addr_min = 0;
		gcp->gc_mii_an_delay = 0;
		gcp->gc_mii_linkdown_action = MII_ACTION_NONE;
		gcp->gc_mii_linkdown_timeout_action = MII_ACTION_RSA;
		gcp->gc_mii_dont_reset = B_FALSE;
		gcp->gc_mii_an_oneshot = B_FALSE;

		/* I/O methods */

		/* mac operation */
		gcp->gc_attach_chip = &epfe_attach_chip;
D 5
		gcp->gc_reset_chip  = &epfe_reset_chip;
		gcp->gc_init_chip   = &epfe_init_chip;
		gcp->gc_start_chip  = &epfe_start_chip;
		gcp->gc_stop_chip   = &epfe_stop_chip;
E 5
I 5
		gcp->gc_reset_chip = &epfe_reset_chip;
		gcp->gc_init_chip = &epfe_init_chip;
		gcp->gc_start_chip = &epfe_start_chip;
		gcp->gc_stop_chip = &epfe_stop_chip;
E 5
		gcp->gc_multicast_hash = &epfe_mcast_hash;
		gcp->gc_set_rx_filter = &epfe_set_rx_filter;
D 5
		gcp->gc_set_media   = &epfe_set_media;
		gcp->gc_get_stats   = &epfe_get_stats;
		gcp->gc_interrupt   = &epfe_interrupt;
E 5
I 5
		gcp->gc_set_media = &epfe_set_media;
		gcp->gc_get_stats = &epfe_get_stats;
		gcp->gc_interrupt = &epfe_interrupt;
E 5

		/* descriptor operation */
		gcp->gc_tx_desc_write = &epfe_tx_desc_write;
		gcp->gc_rx_desc_write = &epfe_rx_desc_write;
D 5
		gcp->gc_tx_start      = &epfe_tx_start;
		gcp->gc_rx_start      = NULL;
E 5
I 5
		gcp->gc_tx_start = &epfe_tx_start;
		gcp->gc_rx_start = NULL;
E 5
		gcp->gc_tx_desc_stat = &epfe_tx_desc_stat;
		gcp->gc_rx_desc_stat = &epfe_rx_desc_stat;
		gcp->gc_tx_desc_init = &epfe_tx_desc_init;
		gcp->gc_rx_desc_init = &epfe_rx_desc_init;
		gcp->gc_tx_desc_clean = &epfe_tx_desc_clean;
		gcp->gc_rx_desc_clean = &epfe_rx_desc_clean;

		/* mii operations */
D 5
		gcp->gc_mii_init  = &gem_mii_init_default;
E 5
I 5
		gcp->gc_mii_probe = &gem_mii_probe_default;
		gcp->gc_mii_init = NULL;
E 5
		gcp->gc_mii_config = &gem_mii_config_default;
D 5
		gcp->gc_mii_sync  = &epfe_mii_sync;
		gcp->gc_mii_read  = &epfe_mii_read;
E 5
I 5
		gcp->gc_mii_sync = &epfe_mii_sync;
		gcp->gc_mii_read = &epfe_mii_read;
E 5
		gcp->gc_mii_write = &epfe_mii_write;
		gcp->gc_mii_tune_phy = NULL;

D 5
		lp = kmem_zalloc(sizeof(struct epfe_dev), KM_SLEEP);
E 5
I 5
		lp = kmem_zalloc(sizeof (struct epfe_dev), KM_SLEEP);
E 5
		lp->chip = p;

D 5
		dp = gem_do_attach(dip, gcp, base, &regs_handle,
					lp, sizeof(*lp));
		kmem_free(gcp, sizeof(*gcp));
E 5
I 5
		dp = gem_do_attach(dip, 0,
		    gcp, base, &regs_handle, lp, sizeof (*lp));
E 5

I 5
		kmem_free(gcp, sizeof (*gcp));

E 5
		if (dp != NULL) {
			return (DDI_SUCCESS);
		}
err:
D 5
		kmem_free(lp, sizeof(struct epfe_dev));
E 5
I 5
		kmem_free(lp, sizeof (struct epfe_dev));
E 5
		return (DDI_FAILURE);
	}
	return (DDI_FAILURE);
}

static int
epfedetach(dev_info_t *dip, ddi_detach_cmd_t cmd)
{
	switch (cmd) {
	case DDI_SUSPEND:
		return (gem_suspend(dip));

	case DDI_DETACH:
		return (gem_do_detach(dip));
	}
	return (DDI_FAILURE);
}

/* ======================================================== */
/*
 * OS depend (loadable streams driver) routine
 */
/* ======================================================== */
I 5
#ifdef GEM_CONFIG_GLDv3
GEM_STREAM_OPS(epfe_ops, epfeattach, epfedetach);
#else
E 5
static	struct module_info epfeminfo = {
	0,			/* mi_idnum */
	"epfe",			/* mi_idname */
	0,			/* mi_minpsz */
D 2
	ETHERMTU,		/* mi_maxpsz */
	32*1024,		/* mi_hiwat */
E 2
I 2
	INFPSZ,			/* mi_maxpsz */
	64*1024,		/* mi_hiwat */
E 2
	1,			/* mi_lowat */
};

static	struct qinit epferinit = {
	(int (*)()) NULL,	/* qi_putp */
	gem_rsrv,		/* qi_srvp */
	gem_open,		/* qi_qopen */
	gem_close,		/* qi_qclose */
	(int (*)()) NULL,	/* qi_qadmin */
	&epfeminfo,		/* qi_minfo */
	NULL			/* qi_mstat */
};

static	struct qinit epfewinit = {
	gem_wput,		/* qi_putp */
	gem_wsrv,		/* qi_srvp */
	(int (*)()) NULL,	/* qi_qopen */
	(int (*)()) NULL,	/* qi_qclose */
	(int (*)()) NULL,	/* qi_qadmin */
	&epfeminfo,		/* qi_minfo */
	NULL			/* qi_mstat */
};

static struct streamtab	epfe_info = {
	&epferinit,	/* st_rdinit */
	&epfewinit,	/* st_wrinit */
	NULL,		/* st_muxrinit */
	NULL		/* st_muxwrinit */
};

static	struct cb_ops cb_epfe_ops = {
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
	&epfe_info,	/* cb_stream */
	D_NEW|D_MP	/* cb_flag */
};

static	struct dev_ops epfe_ops = {
	DEVO_REV,	/* devo_rev */
	0,		/* devo_refcnt */
	gem_getinfo,	/* devo_getinfo */
	nulldev,	/* devo_identify */
	nulldev,	/* devo_probe */
	epfeattach,	/* devo_attach */
	epfedetach,	/* devo_detach */
	nodev,		/* devo_reset */
	&cb_epfe_ops,	/* devo_cb_ops */
	NULL,		/* devo_bus_ops */
	ddi_power	/* devo_power */
};
D 5

E 5
I 5
#endif
E 5
static struct modldrv modldrv = {
	&mod_driverops,	/* Type of module.  This one is a driver */
	ident,
	&epfe_ops,	/* driver ops */
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

	DPRINTF(2, (CE_CONT, "epfe: _init: called"));
	gem_mod_init(&epfe_ops, "epfe");
	status = mod_install(&modlinkage);
	if (status != DDI_SUCCESS) {
		gem_mod_fini(&epfe_ops);
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

	DPRINTF(2, (CE_CONT, "epfe: _fini: called"));
	status = mod_remove(&modlinkage);
	if (status == DDI_SUCCESS) {
		gem_mod_fini(&epfe_ops);
	}
	return (status);
}

int
_info(struct modinfo *modinfop)
{
	return (mod_info(&modlinkage, modinfop));
}
D 5

E 5
E 1
