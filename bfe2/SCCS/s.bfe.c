h41298
s 00006/00022/01923
d D 1.7 08/01/19 14:56:18 mrym 7 6
c vlan supported
e
s 00429/00511/01516
d D 1.6 08/01/12 22:44:05 mrym 6 5
c os putback
e
s 00143/00120/01884
d D 1.5 07/09/23 16:30:53 mrym 5 4
c 2.6.0 clean up
e
s 00140/00105/01864
d D 1.4 07/04/15 16:46:20 mrym 4 3
c 2.4.0
e
s 00125/00052/01844
d D 1.3 06/06/12 05:05:44 mrym 3 2
c 2.2.1
e
s 00004/00003/01892
d D 1.2 06/05/28 17:00:57 mrym 2 1
c 2.2.0
e
s 01895/00000/00000
d D 1.1 06/05/21 15:46:02 mrym 1 0
c date and time created 06/05/21 15:46:02 by mrym
e
u
U
f e 0
t
T
I 1
/*
D 6
 *  bfe_gem.c: Broadcom 440x Fast Ethernet MAC driver for Solaris
E 6
I 6
 *  bfe: Broadcom 440x Fast Ethernet MAC driver for Solaris
E 6
 *
D 4
 * Copyright (c) 2003-2006 Masayuki Murayama.  All rights reserved.
E 4
I 4
D 6
 * Copyright (c) 2003-2007 Masayuki Murayama.  All rights reserved.
E 4
 * 
E 6
I 6
 * Copyright (c) 2003-2008 Masayuki Murayama.  All rights reserved.
 *
E 6
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
D 6
 * 
E 6
I 6
 *
E 6
 * 1. Redistributions of source code must retain the above copyright notice,
D 6
 *    this list of conditions and the following disclaimer. 
 * 
E 6
I 6
 *    this list of conditions and the following disclaimer.
 *
E 6
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
D 6
 *    and/or other materials provided with the distribution. 
 * 
E 6
I 6
 *    and/or other materials provided with the distribution.
 *
E 6
 * 3. Neither the name of the author nor the names of its contributors may be
 *    used to endorse or promote products derived from this software without
D 6
 *    specific prior written permission. 
 * 
E 6
I 6
 *    specific prior written permission.
 *
E 6
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
D 6
#pragma	ident	"%W% %E%"
E 6
I 6
#pragma	ident	"%Z%%M% %I%     %E%"
E 6

/*
D 6
 Change log
 0.8.0  09/21/2003
	first release
 0.8.1  09/21/2002
	flow control disabled because of tx performance problem.
	macro definitions are fixed
 0.8.2
 	09/21/2003
	flow control bug fixed.
	Status LED enabled.
	promiscous problem in set_rx_filter fixed
	register operation changed to use load/store directly

 	10/10/2003
	rx_desc_stat: retrying reading receive length.
	flow control disabled as it is still funny.
 0.8.3
	10/12/2003
	licensing changed to the BSD license
	source code clean up.
 0.8.4  05/05/2004
	dd_getlongprop removed for DDI/DKI complience.
	wrong attribute in ddi_dma_alloc_handle() for tx.
 0.8.7  11/20/2004
	hiwat of bfeminfo was changed.
	tx bounce buffer corruption in gem fixed.
 0.8.8  11/23/2004
	MAE bit in command register of pci config space fixed for DELL
	Inspillons.

	behaviour when no rx buffer fixed.

 	07/21/2005
	resume/suspend supported but not tested yet.
	behaviour when physical address exceeds the hardware ability tested
	 (use TEST_SMALL_DMA_RANGE to test)
 0.8.15 07/22/2005

	09/29/2005
	restart autonego iff the phy have been reset on bfe_reset_chip.
	debug reports on cache line size and latency timer in pci cfg added
	[backports from 3.0.13]
	 don't use RXINTDELAY
	 don't clear RXCFG at initialization.
	 use single fragment for tx
 0.8.17t0 09/29/2005
	 don't clear TXCFG at initialization.
	 txmaxbuffer changed to 1518+32
	 rxmaxbuffer changed to 1518+32
	 tx and rx dma engine initialazation was moved to tha end of
		 bfe_init_chip.
	 bfe_reset_chip() fixed
 2.0.1t1 05/04/2006
	renamed as bfe
	dump routines were moved into a separeted file
I 3
 2.2.0t0 06/10/2006
	prepared soft copies of rx head and tx head to avoid errors on
	descriptor status checks while restarting nic.
I 4
D 5
 2.4.0 04/15/2004
E 5
I 5
 2.4.0 04/15/2007
E 5
	release
I 5
 2.6.0 09/13/2007
       09/22/2007 additional clean up 
E 5
E 4
E 3
 */

/*
 TODO:
	mii_read/write might fail.  should retry on timeout error?
 */

/*
E 6
 * System Header files.
 */
D 6
#include <values.h>
E 6
#include <sys/types.h>
#include <sys/conf.h>
#include <sys/debug.h>
D 6
#include <sys/stropts.h>
#include <sys/stream.h>
#include <sys/strlog.h>
E 6
#include <sys/kmem.h>
D 6
#include <sys/stat.h>
#include <sys/kstat.h>
#include <sys/vtrace.h>
#include <sys/dlpi.h>
#include <sys/strsun.h>
#include <sys/ethernet.h>
E 6
#include <sys/modctl.h>
#include <sys/errno.h>
D 6
#include <sys/dditypes.h>
E 6
#include <sys/ddi.h>
#include <sys/sunddi.h>
I 5
#include <sys/byteorder.h>
E 5
D 6

E 6
I 6
#include <sys/ethernet.h>
E 6
#include <sys/pci.h>
D 5
#include "mii.h"
E 5
I 5
D 6
#include "gem_mii.h"
E 5
#include "gem.h"
E 6
I 6

#include "bfe_mii.h"
#include "bfe_util.h"
E 6
#include "bcm4400reg.h"

char	ident[] = "bcm4400 nic driver v" VERSION;

/* Debugging support */
#ifdef DEBUG_LEVEL
static int bfe_debug = DEBUG_LEVEL;
D 6
#define	DPRINTF(n, args)	if (bfe_debug>(n)) cmn_err args
E 6
I 6
#define	DPRINTF(n, args)	if (bfe_debug > (n)) cmn_err args
E 6
#else
#define	DPRINTF(n, args)
#endif

/*
 * Useful macros and typedefs
 */
D 6
#define	ONESEC	drv_usectohz(1000*1000)

E 6
I 6
#define	ONESEC		drv_usectohz(1000*1000)
E 6
#define	RX_HEAD_ROOM	(RX_HEADER_SIZE + 2)
I 6
#define	BFE_DESC(p)	((struct bfe_desc *)(void *)(p))
E 6

D 6
#ifdef NOFLUSH
#define	FLUSH(dp, reg)
#else
#define	FLUSH(dp, reg)	INL(dp, reg)
#endif
E 6
I 6
#define	FLUSH(dp, reg)	(void) INL(dp, reg)
E 6

D 4
#define	STRUCT_COPY(a, b)	bcopy(&(b), &(a), sizeof(a))

E 4
#define	TXSTAT_DESC_INDEX(dp)	\
D 6
	((INL(dp, TXSTAT) & TXSTAT_DESCOFFSET) / sizeof(struct bfe_desc))
E 6
I 6
	((INL(dp, TXSTAT) & TXSTAT_DESCOFFSET) / sizeof (struct bfe_desc))
E 6

#define	RXSTAT_DESC_INDEX(dp)	\
D 6
	((INL(dp, RXSTAT) & RXSTAT_DESCOFFSET) / sizeof(struct bfe_desc))
E 6
I 6
	((INL(dp, RXSTAT) & RXSTAT_DESCOFFSET) / sizeof (struct bfe_desc))
E 6

#ifndef INT32_MAX
D 6
# define INT32_MAX	0x7fffffff
E 6
I 6
#define	INT32_MAX	0x7fffffff
E 6
#endif

I 3
#define	INSIDE(slot, head, tail)	\
	(((head) <= (tail)) ?	\
		((head) <= (slot) && (slot) < (tail)) :	\
D 6
		((slot) < (tail)  || (head) <= (slot)))
E 6
I 6
		((slot) < (tail) || (head) <= (slot)))
E 6

E 3
/*
 * Our configuration
 */
#ifdef TEST_RX_EMPTY
D 6
# define RX_BUF_SIZE	1
E 6
I 6
#define	RX_BUF_SIZE	1
E 6
#endif

#define	OUR_INTR_BITS	\
	(INT_RX | INT_TX | INT_DESCERR | INT_DATAERR | INT_DESCPROT | \
D 4
	 INT_RXDESCEMPTY | INT_RXOF | INT_TXUF)
E 4
I 4
D 6
	 INT_RXDESCEMPTY | INT_RXOF | INT_TXUF | INT_MAC)
E 6
I 6
	INT_RXDESCEMPTY | INT_RXOF | INT_TXUF | INT_MAC)
E 6
E 4

I 4
D 6
#ifndef MAXTXFRAGS
# define MAXTXFRAGS	GEM_MAXTXFRAGS
E 6
I 6

#ifdef GEM_CONFIG_TX_DIRECT
#define	MAXTXFRAGS	GEM_MAXTXFRAGS
#else
#define	MAXTXFRAGS	1
E 6
#endif
E 4
D 3
#define TX_RING_SIZE	(DESC_BASE_ALIGN / 8)
E 3
I 3
D 6
#define	DESC_SIZE	8
D 4
#define TX_RING_SIZE	(DESC_BASE_ALIGN / DESC_SIZE)
E 3
#define TX_BUF_SIZE	64
D 3
#define RX_RING_SIZE	(DESC_BASE_ALIGN / 8)
E 3
I 3
#define RX_RING_SIZE	(DESC_BASE_ALIGN / DESC_SIZE)
E 4
I 4
#ifndef TX_RING_SIZE
# define TX_RING_SIZE	(DESC_BASE_ALIGN / DESC_SIZE)
E 6
I 6
#define	MAXRXFRAGS	1

#ifndef	TX_BUF_SIZE
#define	TX_BUF_SIZE	64
E 6
#endif
D 6
#ifndef TX_BUF_SIZE
D 5
# define TX_BUF_SIZE	256
E 5
I 5
# define TX_BUF_SIZE	128
E 6
I 6
#ifndef	TX_RING_SIZE
#if MAXTXFRAGS == 1
#define	TX_RING_SIZE	TX_BUF_SIZE
#else
#define	TX_RING_SIZE	(TX_BUF_SIZE * 4)
E 6
E 5
#endif
D 6
#ifndef RX_RING_SIZE
# define RX_RING_SIZE	(DESC_BASE_ALIGN / DESC_SIZE)
E 6
#endif
E 4
E 3
D 6
#ifndef RX_BUF_SIZE
D 4
# define RX_BUF_SIZE	64
E 4
I 4
# define RX_BUF_SIZE	256
E 6
I 6

#ifndef	RX_BUF_SIZE
#define	RX_BUF_SIZE	256
E 6
E 4
#endif
I 6
#ifndef	RX_RING_SIZE
#define	RX_RING_SIZE	RX_BUF_SIZE
#endif
E 6

D 4
#if TX_BUF_SIZE >= TX_RING_SIZE
E 4
I 4
D 6
#if TX_BUF_SIZE > TX_RING_SIZE
E 4
# error TX_BUF_SIZE must be less than TX_RING_SIZE
E 6
I 6
#if TX_RING_SIZE > 512
#error TX_RING_SIZE must be less than or equal to 512
E 6
#endif
I 6
#if RX_RING_SIZE > 512
#error RX_RING_SIZE must be less than or equal to 512
#endif
E 6

D 6
#ifdef CONFIG_COPY_PACKET
E 6
I 6
#ifdef DEBUG_COPY_PACKET
E 6
static int	bfe_tx_copy_thresh = INT32_MAX;
static int	bfe_rx_copy_thresh = INT32_MAX;
#else
static int	bfe_tx_copy_thresh = 256;
static int	bfe_rx_copy_thresh = 256;
#endif

D 4
#define	LE32(x)	x
E 4
I 4
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
E 4

E 5
/*
 * bcm440x chip state
 */
struct bfe_dev {
	/* HW/FW revision numbers */
	int		coreunit;
	uint_t		revid;

	/* rx control */
	int		rx_rest;
I 3
	int		rx_head;
E 3
	int		rx_tail;

I 3
	/* tx control */
	int		tx_head;
	int		tx_tail;

E 3
	/* interrupt control */
	uint32_t	intmask;
I 5
D 6
	uint32_t	intmask_hw;
E 6
E 5
D 3
	int		tx_tail;
E 3
#ifdef GEM_CONFIG_POLLING
	int		last_poll_interval;
#endif

	/* reset control */
	boolean_t	need_to_reset;
	boolean_t	init_done;
I 3
	boolean_t	nic_active;
E 3

	/* MIB data */
	boolean_t	mibvalid;
	uint32_t	mib[MIB_SIZE];

	uint32_t	prom_data[EEPROM_SIZE];
};

/*
 * Supported chips
 */
struct chip_info {
	uint16_t	venid;
	uint16_t	devid;
	char		*name;
};

static struct chip_info bfe_chiptbl[] = {
	{0x14e4, 0x4401, "BCM4401"},
	{0x14e4, 0x4402, "BCM4401B0"},
	{0x14e4, 0x170c, "BCM4401B0"},
};
D 6
#define CHIPTABLESIZE   (sizeof(bfe_chiptbl)/sizeof(struct chip_info))
E 6
I 6
#define	CHIPTABLESIZE   (sizeof (bfe_chiptbl)/sizeof (struct chip_info))
E 6

/* ======================================================== */
D 6
 
E 6
I 6

E 6
/* mii operations */
static void  bfe_mii_sync(struct gem_dev *);
static uint16_t  bfe_mii_read(struct gem_dev *, uint_t);
static void bfe_mii_write(struct gem_dev *, uint_t, uint16_t);

/* nic operations */
static int bfe_attach_chip(struct gem_dev *);
static int bfe_reset_chip(struct gem_dev *);
D 4
static void bfe_init_chip(struct gem_dev *);
static void bfe_set_rx_filter(struct gem_dev *);
static void bfe_set_media(struct gem_dev *);
static void bfe_start_chip(struct gem_dev *);
E 4
I 4
static int bfe_init_chip(struct gem_dev *);
static int bfe_set_rx_filter(struct gem_dev *);
static int bfe_set_media(struct gem_dev *);
static int bfe_start_chip(struct gem_dev *);
E 4
static int bfe_stop_chip(struct gem_dev *);
D 4
static void bfe_get_stats(struct gem_dev *);
E 4
I 4
static int bfe_get_stats(struct gem_dev *);
E 4

/* descriptor operations */
static int bfe_tx_desc_write(struct gem_dev *dp, int slot,
D 3
		    ddi_dma_cookie_t *dmacookie, int frags, uint32_t intreq);
E 3
I 3
D 5
		    ddi_dma_cookie_t *dmacookie, int frags, uint32_t flag);
E 5
I 5
		    ddi_dma_cookie_t *dmacookie, int frags, uint64_t flag);
E 5
E 3
static void bfe_tx_start(struct gem_dev *dp, int startslot, int nslot);
static void bfe_rx_desc_write(struct gem_dev *dp, int slot,
		    ddi_dma_cookie_t *dmacookie, int frags);
static void bfe_rx_start(struct gem_dev *dp, int startslot, int nslot);
static uint_t bfe_tx_desc_stat(struct gem_dev *dp, int slot, int ndesc);
static uint64_t bfe_rx_desc_stat(struct gem_dev *dp, int slot, int ndesc);

static void bfe_tx_desc_init(struct gem_dev *dp, int slot);
static void bfe_rx_desc_init(struct gem_dev *dp, int slot);

/* interrupt handler */
D 6
static u_int bfe_interrupt(struct gem_dev *dp);
E 6
I 6
static uint_t bfe_interrupt(struct gem_dev *dp);
E 6

/* ======================================================== */

/* mapping attributes */
/* Data access requirements. */
static struct ddi_device_acc_attr bfe_dev_attr = {
	DDI_DEVICE_ATTR_V0,
	DDI_STRUCTURE_LE_ACC,
	DDI_STRICTORDER_ACC
};

D 6
/* On sparc, the buffers should be native endianness */
E 6
I 6
/* On sparc, buffers should be native endianness */
E 6
static struct ddi_device_acc_attr bfe_buf_attr = {
	DDI_DEVICE_ATTR_V0,
	DDI_NEVERSWAP_ACC,	/* native endianness */
	DDI_STRICTORDER_ACC
};

#ifdef TEST_SMALL_DMA_RANGE
D 6
#  undef	SB_PCIDMA_SIZE
#  define	SB_PCIDMA_SIZE	(128*1024*1024)
E 6
I 6
#undef	SB_PCIDMA_SIZE
#define	SB_PCIDMA_SIZE	(128*1024*1024)
E 6
#endif

static ddi_dma_attr_t bfe_dma_attr_buf = {
	DMA_ATTR_V0,		/* dma_attr_version */
	0,			/* dma_attr_addr_lo */
	SB_PCIDMA_SIZE - 1,	/* dma_attr_addr_hi */
D 6
	SB_PCIDMA_SIZE - 1,	/* dma_attr_count_max */
	0,/* patched later */	/* dma_attr_align */
E 6
I 6
	0x1fff,			/* dma_attr_count_max */
	0, /* patched later */	/* dma_attr_align */
E 6
	0,			/* dma_attr_burstsizes */
	1,			/* dma_attr_minxfer */
D 6
	SB_PCIDMA_SIZE - 1,	/* dma_attr_maxxfer */
E 6
I 6
	0x1fff,			/* dma_attr_maxxfer */
E 6
	SB_PCIDMA_SIZE - 1,	/* dma_attr_seg */
D 6
	0,/* patched later */	/* dma_attr_sgllen */
E 6
I 6
	0, /* patched later */	/* dma_attr_sgllen */
E 6
	1,			/* dma_attr_granular */
	0			/* dma_attr_flags */
};

static ddi_dma_attr_t bfe_dma_attr_desc = {
	DMA_ATTR_V0,		/* dma_attr_version */
	0,			/* dma_attr_addr_lo */
	SB_PCIDMA_SIZE - 1, 	/* dma_attr_addr_hi */
	SB_PCIDMA_SIZE - 1,	/* dma_attr_count_max */
	DESC_BASE_ALIGN,	/* dma_attr_align */
	0,			/* dma_attr_burstsizes */
	1,			/* dma_attr_minxfer */
	SB_PCIDMA_SIZE - 1,	/* dma_attr_maxxfer */
	SB_PCIDMA_SIZE - 1,	/* dma_attr_seg */
	1,			/* dma_attr_sgllen */
	1,			/* dma_attr_granular */
	0			/* dma_attr_flags */
};

/* ======================================================== */
/*
 * debug routines
 */
/* ======================================================== */
#ifdef DEBUG_DUMP_REGS
#include "bfe_reg_dump.c"
#endif

/* ======================================================== */
/*
 * HW manupilation routines
 */
/* ======================================================== */
I 3
D 4
#if 0
bfe_start_mac(struct gem_dev *dp)
{
	/* Kick TX and RX */
	OUTL(dp, ENETCTL, INL(dp, ENETCTL) | ENETCTL_ENABLE);
}
E 3

E 4
static int
I 3
D 4
bfe_stop_mac(struct gem_dev *dp)
{
	int	i;

	/* Stop Tx and Rx processes in the chip. */
	OUTL(dp, ENETCTL, ENETCTL_DISABLE);
	for (i = 0; (INL(dp, ENETCTL) & ENETCTL_DISABLE) != 0; i++) {
		if (i > 100) {
			cmn_err(CE_NOTE,
				"!%s: %s: timeout: stopping mac",
				dp->name, __func__);
			return (GEM_FAILURE);
		}
		drv_usecwait(10);
	}
	return (GEM_SUCCESS);
}
#endif
static int
E 4
E 3
bfe_reset_chip(struct gem_dev *dp)
{
D 6
	struct bfe_dev		*lp = (struct bfe_dev *)dp->private;
E 6
I 6
	struct bfe_dev		*lp = dp->private;
E 6
	uint32_t		bar0win;
	uint32_t		tmp;
	ddi_acc_handle_t	conf_handle;
	uint32_t		val;
	uint32_t		phyctl;
	int			i;

	DPRINTF(0, (CE_CONT, "!%s: %s: called", dp->name, __func__));

#ifdef DEBUG_DUMP_REGS
	if (!lp->init_done) {
		bfe_dump_allregs(dp, "before reset");
	}
#endif
D 3

E 3
I 3
	lp->nic_active = B_FALSE;
E 3
	if (lp->init_done) {
D 6
		/* inhibit all interrrupts before resetting nic */
D 5
		OUTL(dp, INTMASK, lp->intmask = 0); FLUSH(dp, INTMASK);
E 5
I 5
		lp->intmask    = 0;
		lp->intmask_hw = 0;
		OUTL(dp, INTMASK, lp->intmask_hw); FLUSH(dp, INTMASK);
E 6
I 6
		/* inhibit all interrupts before resetting nic */
		OUTL(dp, INTMASK, 0); FLUSH(dp, INTMASK);
E 6
E 5
		DPRINTF(2, (CE_CONT, "!%s: %s: sb_intmask:0x%x",
D 6
				dp->name, __func__, INL(dp, SB_INTMASK)));
E 6
I 6
		    dp->name, __func__, INL(dp, SB_INTMASK)));
E 6
	}

#if DEBUG_LEVEL > 4
	if ((INL(dp, SB_TMSTATEL) &
D 6
		(SB_TMSTATEL_RESET | SB_TMSTATEL_REJ | SB_TMSTATEL_CLK)) != SB_TMSTATEL_CLK) {
E 6
I 6
	    (SB_TMSTATEL_RESET | SB_TMSTATEL_REJ | SB_TMSTATEL_CLK))
	    != SB_TMSTATEL_CLK) {
E 6
		/* the core isn't up now */
		cmn_err(CE_CONT, "!%s: %s: core isn't up", dp->name, __func__);
	}
#endif

	if ((INL(dp, SB_TMSTATEL) &
D 6
		(SB_TMSTATEL_RESET | SB_TMSTATEL_REJ | SB_TMSTATEL_CLK)) != SB_TMSTATEL_CLK ||
	     !lp->init_done) {
E 6
I 6
	    (SB_TMSTATEL_RESET | SB_TMSTATEL_REJ |
	    SB_TMSTATEL_CLK)) != SB_TMSTATEL_CLK ||
	    !lp->init_done) {
E 6

		if (pci_config_setup(dp->dip, &conf_handle) != DDI_SUCCESS) {
			cmn_err(CE_WARN, "!%s: %s: pci_config_setup failed",
D 6
				dp->name, __func__);
E 6
I 6
			    dp->name, __func__);
E 6
			return (GEM_FAILURE);
		}

		/*
		 * Change bar0window to map sbtopci registers
		 */
		bar0win = pci_config_get32(conf_handle, PCI_BAR0_WIN);
		DPRINTF(2, (CE_CONT, "!%s: %s: bar0win:0x%x",
D 6
			dp->name, __func__, bar0win));
E 6
I 6
		    dp->name, __func__, bar0win));
E 6
		pci_config_put32(conf_handle, PCI_BAR0_WIN, SB_PCI_BASE);

		/*
		 * Ensure if the map is correct.
		 */
		if (SB_IDH_CORE_PCI != (INL(dp, SB_IDH) & SB_IDH_CORE)) {
			cmn_err(CE_WARN,
D 6
				"!%s: %s: failed to map sbtopci registers",
				dp->name, __func__);
E 6
I 6
			    "!%s: %s: failed to map sbtopci registers",
			    dp->name, __func__);
E 6
			/*
			 * XXX - we must restore bar0window mapping,
			 * otherwise the hardware will be hung.
			 */
			pci_config_put32(conf_handle, PCI_BAR0_WIN, bar0win);

			pci_config_teardown(&conf_handle);

			return (GEM_FAILURE);
		}

		val = INL(dp, SB_INTMASK) | SB_INTMASK_ENET0;
		OUTL(dp, SB_INTMASK, val);
D 6
#ifdef DBG_NOBURST
E 6
I 6
#ifdef DEBUG_NOBURST
E 6
		val = INL(dp, SBTOPCI2) & ~(SBTOPCI_PREF | SBTOPCI_BURST);
#else
		val = INL(dp, SBTOPCI2) | SBTOPCI_PREF | SBTOPCI_BURST;
#endif
		OUTL(dp, SBTOPCI2, val);

		/* restore bar0window mapping */
		pci_config_put32(conf_handle, PCI_BAR0_WIN, bar0win);

		pci_config_teardown(&conf_handle);
D 6
	}
	else {
E 6
I 6
	} else {
E 6
		/*
		 * the core have been up,
		 * we try to stop all activities gracefully.
		 */
		DPRINTF(0, (CE_CONT, "!%s: %s: core is up",
D 6
				dp->name, __func__));
E 6
I 6
		    dp->name, __func__));
E 6

		/* do soft reset */
		OUTL(dp, ENETCTL, ENETCTL_SOFTRESET);
	}

	if ((INL(dp, SB_TMSTATEL) & SB_TMSTATEL_RESET) == 0) {
D 6
		
E 6
I 6

E 6
		DPRINTF(0, (CE_CONT, "!%s: %s: resetting the core",
D 6
				dp->name, __func__));
E 6
I 6
		    dp->name, __func__));
E 6
		OUTL(dp, SB_TMSTATEL, SB_TMSTATEL_CLK | SB_TMSTATEL_REJ);

D 6
		for (i = 0; (INL(dp, SB_TMSTATEL) & SB_TMSTATEL_REJ)==0; i++) {
E 6
I 6
		for (i = 0;
		    (INL(dp, SB_TMSTATEL) & SB_TMSTATEL_REJ) == 0; i++) {
E 6
			if (i > 100) {
D 6
				cmn_err(CE_NOTE,
				"!%s: %s: timeout: waiting for SB_TMSTATE_REJ",
					dp->name, __func__);
E 6
I 6
				cmn_err(CE_NOTE, "!%s: %s: timeout:"
				    " waiting for SB_TMSTATE_REJ",
				    dp->name, __func__);
E 6
				break;
			}
			drv_usecwait(10);
		}

D 5
		for (i = 0; (INL(dp, SB_TMSTATEH) & SB_TMSTATEH_BUSY)!=0; i++) {
E 5
I 5
		for (i = 0; INL(dp, SB_TMSTATEH) & SB_TMSTATEH_BUSY; i++) {
E 5
			if (i > 100) {
D 6
				cmn_err(CE_NOTE,
				"!%s: %s: timeout: waiting for SB_TMSTATH_BUSY",
					dp->name, __func__);
E 6
I 6
				cmn_err(CE_NOTE, "!%s: %s: timeout:"
				    " waiting for SB_TMSTATH_BUSY",
				    dp->name, __func__);
E 6
				break;
			}
			drv_usecwait(10);
		}

D 6
		OUTL(dp, SB_TMSTATEL, 
				SB_TMSTATEL_FGC | SB_TMSTATEL_CLK |
				SB_TMSTATEL_REJ | SB_TMSTATEL_RESET);
E 6
I 6
		OUTL(dp, SB_TMSTATEL,
		    SB_TMSTATEL_FGC | SB_TMSTATEL_CLK |
		    SB_TMSTATEL_REJ | SB_TMSTATEL_RESET);
E 6
		FLUSH(dp, SB_TMSTATEL);
		drv_usecwait(10);

D 6
		OUTL(dp, SB_TMSTATEL, 
				SB_TMSTATEL_REJ | SB_TMSTATEL_RESET);
E 6
I 6
		OUTL(dp, SB_TMSTATEL,
		    SB_TMSTATEL_REJ | SB_TMSTATEL_RESET);
E 6
		FLUSH(dp, SB_TMSTATEL);
		drv_usecwait(1);
I 6
#ifdef DEBUG_LEVEL
	} else {
		DPRINTF(0, (CE_CONT,
		    "!%s: %s: no need to reset the core",
		    dp->name, __func__));
#endif
E 6
	}
D 6
	else {
		DPRINTF(0, (CE_CONT, "!%s: %s: no need to reset the core",
				dp->name, __func__));
	}
E 6

	OUTL(dp, SB_TMSTATEL,
D 6
		SB_TMSTATEL_FGC | SB_TMSTATEL_CLK | SB_TMSTATEL_RESET);
E 6
I 6
	    SB_TMSTATEL_FGC | SB_TMSTATEL_CLK | SB_TMSTATEL_RESET);
E 6
	FLUSH(dp, SB_TMSTATEL);
	drv_usecwait(1);

D 5
	if ((INL(dp, SB_TMSTATEH) & SB_TMSTATEH_SERR) != 0) {
E 5
I 5
	if (INL(dp, SB_TMSTATEH) & SB_TMSTATEH_SERR) {
E 5
		OUTL(dp, SB_TMSTATEH, 0);
		cmn_err(CE_WARN, "!%s: %s: SB_TMSTATEH_SERR still set",
D 6
			dp->name, __func__);
E 6
I 6
		    dp->name, __func__);
E 6
		return (GEM_FAILURE);
	}

	if ((tmp = INL(dp, SB_IMSTATE)) & (SB_IMSTATE_IBE | SB_IMSTATE_TO)) {
		OUTL(dp, SB_IMSTATE, tmp & ~(SB_IMSTATE_IBE | SB_IMSTATE_TO));
		cmn_err(CE_WARN, "!%s: %s: sbimstate is not clear",
D 6
			dp->name, __func__);
E 6
I 6
		    dp->name, __func__);
E 6
		return (GEM_FAILURE);
	}

	/* clear reset and allow it to propagate throughout the core */
	OUTL(dp, SB_TMSTATEL, SB_TMSTATEL_FGC | SB_TMSTATEL_CLK);
	FLUSH(dp, SB_TMSTATEL);
	drv_usecwait(1);

	/* clock must be enabled */
	OUTL(dp, SB_TMSTATEL, SB_TMSTATEL_CLK);
	FLUSH(dp, SB_TMSTATEL);
	drv_usecwait(1);

	/* setup PHY */
	OUTL(dp, MIICTL, MIICTL_PREAMBLE | 13);

	phyctl = INL(dp, PHYCTL);
	if ((phyctl & PHYCTL_INTERNAL) == 0) {
		if ((ENETCTL_EXTERNALPHY & INL(dp, ENETCTL)) == 0) {
			/* synchronize with mii_state */
			dp->mii_state = MII_STATE_RESETTING;
		}

		/* enable external phy */
		OUTL(dp, ENETCTL, ENETCTL_EXTERNALPHY);
D 6
	}
	else {
E 6
I 6
	} else {
E 6
D 5
		if ((phyctl & PHYCTL_RESET) != 0) {
E 5
I 5
		if (phyctl & PHYCTL_RESET) {
E 5
			/* release reset signal for internal PHY */
			OUTL(dp, PHYCTL, phyctl & ~PHYCTL_RESET);
			drv_usecwait(100);

			/* synchronize with mii_state */
			dp->mii_state = MII_STATE_RESETTING;
		}
	}
#ifdef DEBUG_DUMP_REGS
	if (!lp->init_done) {
		bfe_dump_allregs(dp, "after reset");
	}
#endif
	lp->init_done = B_TRUE;

D 6
	/* 1/13/2006 clear and mask unexpected interrupts */
D 5
	OUTL(dp, INTMASK, lp->intmask = 0); FLUSH(dp, INTMASK);
E 5
I 5
	lp->intmask    = 0;
	lp->intmask_hw = 0;
	OUTL(dp, INTMASK, lp->intmask_hw); FLUSH(dp, INTMASK);
E 5
	OUTL(dp, INTSTAT, 0xffffffff); FLUSH(dp, INTSTAT);
E 6
I 6
	/* mask unexpected interrupts */
	OUTL(dp, INTMASK, 0); FLUSH(dp, INTMASK);
	if (lp->intmask == 0) {
		OUTL(dp, INTSTAT, 0xffffffff); FLUSH(dp, INTSTAT);
	}
E 6

I 4
D 6
	/* workaround for reseting nic on reception of long packets */
E 6
I 6
	/* workaround for resetting nic on reception of long packets */
E 6
	lp->rx_rest = 0;

	lp->tx_head = 0;
	lp->tx_tail = 0;
	lp->rx_head = 0;
	lp->rx_tail = 0;
	lp->nic_active = B_FALSE;

E 4
	return (GEM_SUCCESS);
}

#define	RX_TIMEOUT_10u	625		/* 10uS */
#define	RX_FRAMECNT	2

D 4
static void
E 4
I 4
static int
E 4
bfe_init_chip(struct gem_dev *dp)
{
D 6
	struct bfe_dev	*lp = (struct bfe_dev *)dp->private;
	int		rx_delay;
E 6
I 6
	struct bfe_dev	*lp = dp->private;
E 6

	DPRINTF(0, (CE_CONT, "!%s: %s: called", dp->name, __func__));

	ASSERT((dp->rx_ring_dma & 0xfff) == 0);
	ASSERT((dp->tx_ring_dma & 0xfff) == 0);

	/* 000 PHYCTL: have been configured */

	/* 00c BISTSTAT: ignore */

	/* 010 WAKEUPLEN: ignore */

	/* 020 INTSTAT: ignore */

	/* 024 INTMASK: clear */
	OUTL(dp, INTMASK, 0);
I 6
	lp->intmask = 0;
E 6

	/* 028 GPTIMER: clear */
	OUTL(dp, GPTIMER, 0);
D 6
#if 0
E 6
I 6
#if DEBUG_LEVEL > 10
E 6
{
	clock_t	now;

	OUTL(dp, GPTIMER, 100*1000*1000);
	now = ddi_get_lbolt();
	while ((INL(dp, INTSTAT) & INT_GPTIMER) == 0) {
		drv_usecwait(10);
	}

	cmn_err(CE_CONT, "!%s: %s: %d mS",
D 6
		dp->name, __func__,  (ddi_get_lbolt() - now)*10);
E 6
I 6
	    dp->name, __func__,  (ddi_get_lbolt() - now)*10);
E 6

	OUTL(dp, GPTIMER, 0);
}
#endif

	/* 0a8 MACCTL enable crc generation */
	OUTL(dp, MACCTL, MACCTL_EN_LED | MACCTL_EN_CRC);

	/* 100 RXINTDELAY: */
D 6
	rx_delay = 1;
	OUTL(dp, RXINTDELAY,
		(rx_delay << RXINTDELAY_FRAMECNT_SHIFT) |
		(15*RX_TIMEOUT_10u * (rx_delay - 1)));
E 6
I 6
	OUTL(dp, RXINTDELAY, (1 << RXINTDELAY_FRAMECNT_SHIFT));
E 6

I 6

E 6
	/* 400 RXCFG: don't touch */

D 7
	/* 404 RXMAXLEN: must be 1518+32 */
E 7
I 7
	/* 404 RXMAXLEN: */
E 7
	OUTL(dp, RXMAXLEN, dp->mtu +
D 6
		sizeof(struct ether_header) + ETHERFCSL + RX_HEAD_ROOM + 2);
E 6
I 6
D 7
	    sizeof (struct ether_header) + ETHERFCSL + RX_HEAD_ROOM + 2);
E 6
I 4
#ifdef DEBUG_LEVEL
E 4
D 6
	if (dp->mtu + sizeof(struct ether_header) +
E 6
I 6
	if (dp->mtu + sizeof (struct ether_header) +
E 6
				ETHERFCSL + RX_HEAD_ROOM + 2 != 1518+32) {
		cmn_err(CE_WARN, "!%s: rxmaxlen isn't 1518+32 (%d)",
			dp->name,
D 6
			dp->mtu + sizeof(struct ether_header) +
E 6
I 6
			dp->mtu + sizeof (struct ether_header) +
E 6
				ETHERFCSL + RX_HEAD_ROOM + 2);
	}
D 4

E 4
I 4
#endif
E 4
	/* 408 TXMAXLEN: must be 1518+32 */
D 4
	OUTL(dp, TXMAXLEN, dp->mtu + sizeof(struct ether_header) + ETHERFCSL + 32);
E 4
I 4
	OUTL(dp, TXMAXLEN,
D 6
		dp->mtu + sizeof(struct ether_header) + ETHERFCSL + 32);
E 6
I 6
	    dp->mtu + sizeof (struct ether_header) + ETHERFCSL + 32);
E 6
#ifdef DEBUG_LEVEL
E 4
D 6
	if (dp->mtu + sizeof(struct ether_header) + ETHERFCSL + 32 != 1518+32) {
E 6
I 6
	if (dp->mtu + sizeof (struct ether_header)
	    + ETHERFCSL + 32 != 1518+32) {
E 6
		cmn_err(CE_WARN, "!%s: txmaxlen isn't 1518+32 (%d)",
D 6
			dp->name,
			dp->mtu + sizeof(struct ether_header) + ETHERFCSL + 32);
E 6
I 6
		    dp->name,
		    dp->mtu + sizeof (struct ether_header) + ETHERFCSL + 32);
E 6
	}
D 4

E 4
I 4
#endif
E 7
I 7
	    sizeof (struct ether_header) + ETHERFCSL + RX_HEAD_ROOM + 4);

	/* 408 TXMAXLEN: */
	OUTL(dp, TXMAXLEN, dp->mtu + sizeof (struct ether_header) + 4 + 32);

E 7
E 4
	/* 418 MACINTMASK: don't touch */

	/* 42c ENETCTL: don't touch */

	/* 430 TXCFG: don't touch */

	/* 434 TXHIWAT: must be 56 */
D 4
	OUTL(dp, TXHIWAT, 56);	/* 56 */

E 4
I 4
D 6
#if 0
E 6
I 6
#if DEBUG_LEVEL > 10
E 6
	OUTL(dp, TXHIWAT, 1);
	DPRINTF(0, (CE_CONT, "%s: %s: txhiwat: %x",
D 6
		dp->name, __func__, INL(dp, TXHIWAT)));
E 6
I 6
	    dp->name, __func__, INL(dp, TXHIWAT)));
E 6
#else
	OUTL(dp, TXHIWAT, 56);	/* default 56 */
#endif
E 4
	/* 438 MIBCTL */
	OUTL(dp, MIBCTL, MIBCTL_AUTOCLR);

	/* 500 mibdata: clear by reading all mib counter registers */
	if (!lp->mibvalid) {
D 6
		ddi_rep_get32(dp->regs_handle, lp->mib, 
E 6
I 6
		ddi_rep_get32(dp->regs_handle, lp->mib,
E 6
			(uint32_t *)(((long)dp->base_addr) + MIBDATA),
			MIB_SIZE, DDI_DEV_AUTOINCR);
		/* discard mib data */
D 6
		bzero(lp->mib, sizeof(lp->mib));
E 6
I 6
		bzero(lp->mib, sizeof (lp->mib));
E 6
		lp->mibvalid = B_TRUE;
	}

	/*
	 * finally, we setup dma engine.
	 */
	/* for tx dma channel */
D 4
#ifdef DBG_RXOF
	OUTL(dp, TXMAXBURSTLEN, 0x10); /**/
	OUTL(dp, RXMAXBURSTLEN, 0x10); /**/
E 4
I 4
D 6
#if 0
E 6
I 6
#ifdef TEST_BURST
E 6
	OUTL(dp, TXMAXBURSTLEN, 0xffffffff);
	OUTL(dp, RXMAXBURSTLEN, 0xffffffff);
	DPRINTF(0, (CE_CONT, "%s: %s: txmaxburst:%x, rxmaxburst:%x",
D 6
		dp->name, __func__,
		INL(dp, TXMAXBURSTLEN), INL(dp, RXMAXBURSTLEN)));
E 6
I 6
	    dp->name, __func__,
	    INL(dp, TXMAXBURSTLEN), INL(dp, RXMAXBURSTLEN)));
E 6
#endif
D 6
	OUTL(dp, TXMAXBURSTLEN, dp->txmaxdma/4); /* observed max is 0x80 */
	OUTL(dp, RXMAXBURSTLEN, dp->rxmaxdma/4); /* observed max is 0x80 */
#ifdef DBG_FAIRSCHED
E 6
I 6
#ifdef notdef
	OUTL(dp, TXMAXBURSTLEN, min(0x80, dp->txmaxdma/4));
	OUTL(dp, RXMAXBURSTLEN, min(0x80, dp->rxmaxdma/4));
#endif
	DPRINTF(1, (CE_CONT, "%s: %s: txmaxburst:%x, rxmaxburst:%x",
	    dp->name, __func__,
	    INL(dp, TXMAXBURSTLEN), INL(dp, RXMAXBURSTLEN)));
#ifdef TEST_FAIRSCHED
E 6
E 4
	OUTL(dp, TXCTL, TXCTL_FPRI | TXCTL_EN);
#else
	OUTL(dp, TXCTL, TXCTL_EN);
#endif
	OUTL(dp, TXDESCBASE, dp->tx_ring_dma | SB_PCIDMA_BASE);

	/* for rx dma channel */
	OUTL(dp, RXCTL,
D 6
		(RX_HEAD_ROOM << RXCTL_OFFSET_SHIFT) | RXCTL_EN);
E 6
I 6
	    (RX_HEAD_ROOM << RXCTL_OFFSET_SHIFT) | RXCTL_EN);
E 6
	OUTL(dp, RXDESCBASE, dp->rx_ring_dma | SB_PCIDMA_BASE);

D 4
	/* workaround for reseting nic on reception of long packets */
	lp->rx_rest = 0;

I 3
	lp->tx_head = 0;
E 3
	lp->tx_tail = 0;
I 3
	lp->rx_head = 0;
E 3
	lp->rx_tail = 0;
I 3
	lp->nic_active = B_FALSE;
E 4
I 4
	return (GEM_SUCCESS);
E 4
E 3
}

#ifdef DEBUG_LEVEL
D 3
static boolean_t
E 3
I 3
static int
E 3
bfe_dump_cam(struct gem_dev *dp)
{
	int		i;
	int		ix;
I 5
	uint32_t	hi;
	uint32_t	lo;
E 5

	for (ix = 0; ix < 64; ix++) {
		OUTL(dp, CAMCTL, (ix << CAMCTL_INDEX_SHIFT) | CAMCTL_READ);

D 5
		for (i = 0; (INL(dp, CAMCTL) & CAMCTL_BUSY) != 0; i++) {
E 5
I 5
D 6
		for (i = 0; INL(dp, CAMCTL) & CAMCTL_BUSY ; i++) {
E 6
I 6
		for (i = 0; INL(dp, CAMCTL) & CAMCTL_BUSY; i++) {
E 6
E 5
			if (i > 10) {
				cmn_err(CE_WARN,
D 6
				"!%s: dump_cam: timeout on reading cam",
					dp->name);
E 6
I 6
				    "!%s: dump_cam: timeout on reading cam",
				    dp->name);
E 6
D 3
				return;
E 3
I 3
				return (GEM_FAILURE);
E 3
			}
			drv_usecwait(10);
		}
D 5
		cmn_err(CE_CONT, "!cam[%d]: %08x, %08x",
				ix, INL(dp, CAMHI), INL(dp, CAMLOW));
E 5
I 5
		hi = INL(dp, CAMHI);
		lo = INL(dp, CAMLOW);
		cmn_err(CE_CONT, "!%s: %s: (%d) %02x:%02x:%02x:%02x:%02x:%02x",
D 6
				dp->name, __func__, ix,
				(hi >> 8)  & 0xff, (hi >> 0)  & 0xff,
				(lo >> 24) & 0xff, (lo >> 16) & 0xff,
				(lo >> 8)  & 0xff, (lo >> 0)  & 0xff);
E 6
I 6
		    dp->name, __func__, ix,
		    (hi >> 8)  & 0xff, (hi >> 0)  & 0xff,
		    (lo >> 24) & 0xff, (lo >> 16) & 0xff,
		    (lo >> 8)  & 0xff, (lo >> 0)  & 0xff);
E 6
E 5
	}
I 3
	return (GEM_SUCCESS);
E 3
}
#endif

D 3
static boolean_t
E 3
I 3
static int
E 3
bfe_load_addr_into_cam(struct gem_dev *dp, uint8_t *mac, uint_t ix)
{
	int		i;

D 4
	DPRINTF(0, (CE_CONT, "!%s: %s: called", dp->name, __func__));
E 4
I 4
D 5
	DPRINTF(1, (CE_CONT, "!%s: %s: called", dp->name, __func__));
E 5
I 5
	DPRINTF(3, (CE_CONT,
D 6
	"!%s: %s: (%d) %02x:%02x:%02x:%02x:%02x:%02x",
		dp->name, __func__, ix,
		mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]));
E 6
I 6
	    "!%s: %s: (%d) %02x:%02x:%02x:%02x:%02x:%02x",
	    dp->name, __func__, ix,
	    mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]));
E 6
E 5
E 4

	OUTL(dp, CAMLOW,
D 6
		(mac[2] << 24) | (mac[3] << 16) | (mac[4] << 8) | mac[5]);
E 6
I 6
	    (mac[2] << 24) | (mac[3] << 16) | (mac[4] << 8) | mac[5]);
E 6
	OUTL(dp, CAMHI, CAMHI_VALID | (mac[0] << 8) | mac[1]);

	OUTL(dp, CAMCTL, (ix << CAMCTL_INDEX_SHIFT) | CAMCTL_WRITE);

D 5
	for (i = 0; (INL(dp, CAMCTL) & CAMCTL_BUSY) != 0; i++) {
E 5
I 5
	for (i = 0; INL(dp, CAMCTL) & CAMCTL_BUSY; i++) {
E 5
		if (i > 10) {
			cmn_err(CE_WARN,
D 6
				"!%s: %s: timeout on writing to cam",
				dp->name, __func__);
E 6
I 6
			    "!%s: %s: timeout on writing to cam",
			    dp->name, __func__);
E 6
D 3
			return (B_FALSE);
E 3
I 3
			return (GEM_FAILURE);
E 3
		}
		drv_usecwait(10);
	}
D 3
	return (B_TRUE);
E 3
I 3
	return (GEM_SUCCESS);
E 3
}

D 4
static void
E 4
I 4
static int
E 4
D 6
bfe_set_rx_filter(struct gem_dev *dp)	
E 6
I 6
bfe_set_rx_filter(struct gem_dev *dp)
E 6
{
	uint32_t	rxcfg;
	int		i;
I 5
D 6
	int		j;
E 5
	static uint8_t	mac_invalid[ETHERADDRL] = {0,0,0,0,0,0};
	struct bfe_dev	*lp = (struct bfe_dev *)dp->private;
E 6
I 6
	static uint8_t	mac_invalid[ETHERADDRL] = {0, 0, 0, 0, 0, 0};
E 6

D 5
	DPRINTF(0, (CE_CONT, "!%s: %s: called", dp->name, __func__));

E 5
I 5
	DPRINTF(0, (CE_CONT, "!%s: %s: called, mc_count:%d, mode:0x%b",
D 6
		dp->name, __func__, dp->mc_count, dp->rxmode, RXMODE_BITS));
E 6
I 6
	    dp->name, __func__, dp->mc_count, dp->rxmode, RXMODE_BITS));
E 6
#if DEBUG_LEVEL > 0
	for (i = 0; i < dp->mc_count; i++) {
		cmn_err(CE_CONT,
D 6
		"!%s: adding mcast(%d) %02x:%02x:%02x:%02x:%02x:%02x",
			dp->name, i,
			dp->mc_list[i].addr.ether_addr_octet[0],
			dp->mc_list[i].addr.ether_addr_octet[1],
			dp->mc_list[i].addr.ether_addr_octet[2],
			dp->mc_list[i].addr.ether_addr_octet[3],
			dp->mc_list[i].addr.ether_addr_octet[4],
			dp->mc_list[i].addr.ether_addr_octet[5]);
E 6
I 6
		    "!%s: adding mcast(%d) %02x:%02x:%02x:%02x:%02x:%02x",
		    dp->name, i,
		    dp->mc_list[i].addr.ether_addr_octet[0],
		    dp->mc_list[i].addr.ether_addr_octet[1],
		    dp->mc_list[i].addr.ether_addr_octet[2],
		    dp->mc_list[i].addr.ether_addr_octet[3],
		    dp->mc_list[i].addr.ether_addr_octet[4],
		    dp->mc_list[i].addr.ether_addr_octet[5]);
E 6
	}
#endif
E 5
	rxcfg = INL(dp, RXCFG) & ~(RXCFG_PROMISC | RXCFG_ALLMULT);

D 2
	if (dp->nic_active) {
E 2
I 2
D 3
	if (dp->mac_active) {
E 2
		/* XXX - should disable all rx filters for a while ? */
E 3
I 3
	if ((dp->rxmode & RXMODE_ENABLE) == 0) {
		/* disable the cam */
		OUTL(dp, CAMCTL, 0);
E 3
D 6
	}
D 3

	if ((dp->rxmode & RXMODE_PROMISC) != 0) {
E 3
I 3
D 5
	else if ((dp->rxmode & RXMODE_PROMISC) != 0) {
E 5
I 5
	else if (dp->rxmode & RXMODE_PROMISC) {
E 6
I 6
	} else if (dp->rxmode & RXMODE_PROMISC) {
E 6
E 5
E 3
		rxcfg |= RXCFG_PROMISC;
D 6
	}
	else {
E 6
I 6
	} else {
E 6
I 3
		if (dp->mac_active) {
			/*
D 5
			 * XXX - enable all packets for a while
E 5
I 5
			 * XXX - receive all packets for a while
E 5
			 * to avoid dropping packets which must be received.
			 */
			OUTL(dp, RXCFG, rxcfg | RXCFG_PROMISC | RXCFG_ALLMULT);
			FLUSH(dp, RXCFG);
		}

E 3
		/* disable the cam for writing */
D 3
		OUTL(dp, CAMCTL, 0); FLUSH(dp, CAMCTL);
E 3
I 3
		OUTL(dp, CAMCTL, 0);
		FLUSH(dp, CAMCTL);
E 3

I 3
		/* reset cam index counter */
E 3
		i = 0;

D 5
		/* first, we add our station address into the cam */
		bfe_load_addr_into_cam(dp, dp->cur_addr.ether_addr_octet, i++);

E 5
		/* next, append multicast addresses */
D 5
		if ((dp->rxmode & RXMODE_ALLMULTI) != 0 ||
E 5
I 5
		if ((dp->rxmode & RXMODE_ALLMULTI) ||
E 5
D 6
		     /* XXX - we must reserve one for our station address */
		     dp->mc_count > CAM_ENTRY_SIZE - 1) {
E 6
I 6
		    /* XXX - we must reserve one for our station address */
		    dp->mc_count > CAM_ENTRY_SIZE - 1) {
E 6
			rxcfg |= RXCFG_ALLMULT;
D 6
		}
D 5
		else if (dp->mc_count > 0) {
D 3
			for (; i < dp->mc_count; i++) {
E 3
I 3
			while (i < dp->mc_count) {
E 5
I 5
		else {
E 6
I 6
		} else {
E 6
			for (; i < dp->mc_count; i++) {
E 5
E 3
D 6
				bfe_load_addr_into_cam(dp,
E 6
I 6
				(void) bfe_load_addr_into_cam(dp,
E 6
D 3
				    dp->mc_list[i].addr.ether_addr_octet, i);
E 3
I 3
D 5
				    dp->mc_list[i].addr.ether_addr_octet, i++);
E 5
I 5
				    dp->mc_list[i].addr.ether_addr_octet, i);
E 5
E 3
			}
		}

		/* XXX - invalidate unused CAM entries. 2004/12/19 */
D 3
		for (; i < CAM_ENTRY_SIZE; i++) {
			bfe_load_addr_into_cam(dp, mac_invalid, i);
E 3
I 3
D 5
		while (i < CAM_ENTRY_SIZE) {
			bfe_load_addr_into_cam(dp, mac_invalid, i++);
E 5
I 5
D 6
		for (;i < CAM_ENTRY_SIZE - 1; i++) {
			bfe_load_addr_into_cam(dp, mac_invalid, i);
E 6
I 6
		for (; i < CAM_ENTRY_SIZE - 1; i++) {
			(void) bfe_load_addr_into_cam(dp, mac_invalid, i);
E 6
E 5
E 3
		}
D 5
#if DEBUG_LEVEL > 4
E 5
I 5

		/* finally,  we add our station address into the cam */
D 6
		bfe_load_addr_into_cam(dp, dp->cur_addr.ether_addr_octet, i);
E 6
I 6
		(void) bfe_load_addr_into_cam(dp,
		    dp->cur_addr.ether_addr_octet, i);
E 6

#if DEBUG_LEVEL > 3
E 5
		bfe_dump_cam(dp);
#endif
I 3
		/* finally enable the cam */
E 3
		OUTL(dp, CAMCTL, INL(dp, CAMCTL) | CAMCTL_EN);
I 3
		FLUSH(dp, CAMCTL);
E 3
	}
	OUTL(dp, RXCFG, rxcfg);
I 3
	FLUSH(dp, RXCFG);
I 4

	return (GEM_SUCCESS);
E 4
E 3
}

D 4
static void
E 4
I 4
static int
E 4
bfe_set_media(struct gem_dev *dp)
{
	uint32_t	rx;
	uint32_t	tx;
D 6
	struct bfe_dev	*lp = (struct bfe_dev *)dp->private;
E 6

	DPRINTF(0, (CE_CONT, "!%s: %s: called", dp->name, __func__));

D 2
	ASSERT(dp->nic_online);
E 2
I 2
	ASSERT(dp->nic_state == NIC_STATE_INITIALIZED ||
D 6
		dp->nic_state == NIC_STATE_ONLINE);
E 6
I 6
	    dp->nic_state == NIC_STATE_ONLINE);
E 6
E 2

	/*
	 * Notify current duplex mode to mac
	 */
	tx = INL(dp, TXCFG) & ~TXCFG_FULLDPX;
	if (dp->full_duplex) {
		tx |= TXCFG_FULLDPX;
	}
	OUTL(dp, TXCFG, tx);

	/*
	 * set up flow control
	 */
	rx = INL(dp, RXCFG) & ~RXCFG_EN_FLOWCTL;
	tx = INL(dp, FLOWCTL) & ~(FLOWCTL_ENABLE | FLOWCTL_RXHIWAT);
	switch (dp->flow_control) {
	case FLOW_CONTROL_RX_PAUSE:
		rx |= RXCFG_EN_FLOWCTL;
		break;

	case FLOW_CONTROL_TX_PAUSE:
D 4
		tx |= FLOWCTL_ENABLE | (192 & FLOWCTL_RXHIWAT);
E 4
I 4
#define	RXFIFO_HI	((256/8)*6)
		tx |= FLOWCTL_ENABLE | (RXFIFO_HI & FLOWCTL_RXHIWAT);
E 4
		break;

	case FLOW_CONTROL_SYMMETRIC:
		rx |= RXCFG_EN_FLOWCTL;
D 4
		tx |= FLOWCTL_ENABLE | (192 & FLOWCTL_RXHIWAT);
E 4
I 4
		tx |= FLOWCTL_ENABLE | (RXFIFO_HI & FLOWCTL_RXHIWAT);
E 4
		break;
I 4
#undef	RXFIFO_HI
E 4
	}
	OUTL(dp, RXCFG, rx);
	OUTL(dp, FLOWCTL, tx);
I 4

	return (GEM_SUCCESS);
E 4
}

D 4
static void
E 4
I 4
static int
E 4
bfe_start_chip(struct gem_dev *dp)
{
D 6
	struct bfe_dev	*lp = (struct bfe_dev *)dp->private;
E 6
I 6
	struct bfe_dev	*lp = dp->private;
E 6

	DPRINTF(0, (CE_CONT, "!%s: %s: called", dp->name, __func__));

	/* Kick TX and RX */
I 3
	lp->nic_active = B_TRUE;
E 3
	OUTL(dp, ENETCTL, INL(dp, ENETCTL) | ENETCTL_ENABLE);

	/* enable interrupt */
	lp->intmask = OUR_INTR_BITS;
D 6
#ifdef GEM_CONFIG_POLLING
	lp->intmask |= INT_GPTIMER;
#endif
I 5
	lp->intmask_hw = 0;

E 6
E 5
	if ((dp->misc_flag & GEM_NOINTR) == 0) {
D 5
		OUTL(dp, INTMASK, lp->intmask); FLUSH(dp, INTMASK);
E 5
I 5
D 6
		lp->intmask_hw = lp->intmask;
		OUTL(dp, INTMASK, lp->intmask_hw); FLUSH(dp, INTMASK);
E 6
I 6
		OUTL(dp, INTMASK, lp->intmask); FLUSH(dp, INTMASK);
E 6
E 5
I 4
#ifdef DEBUG_FLOW
		OUTL(dp, MACINTMASK, MACINT_FLOW);
#endif
E 4
	}
I 4

	return (GEM_SUCCESS);
E 4
}

static int
bfe_stop_chip(struct gem_dev *dp)
{
	int		i;
D 6
	int		wait_time;
	struct txbuf	*tbp;
	struct bfe_dev	*lp = (struct bfe_dev *)dp->private;
	extern int	gem_speed_value[];
E 6
I 6
	struct bfe_dev	*lp = dp->private;
E 6

	DPRINTF(0, (CE_CONT, "!%s: %s: called", dp->name, __func__));

	/* Disable interrupts by clearing the interrupt mask */
D 6
	lp->intmask = 0;
I 5
	lp->intmask_hw = 0;
E 6
E 5
	if ((dp->misc_flag & GEM_NOINTR) == 0) {
D 5
		OUTL(dp, INTMASK, lp->intmask); FLUSH(dp, INTMASK);
E 5
I 5
D 6
		OUTL(dp, INTMASK, lp->intmask_hw); FLUSH(dp, INTMASK);
E 6
I 6
		OUTL(dp, INTMASK, 0); FLUSH(dp, INTMASK);
E 6
E 5
I 4
		OUTL(dp, MACINTMASK, 0);
E 4
	}

I 6
	/* inhibit rx interrupt */
E 6
	OUTL(dp, RXINTDELAY, 0);

D 6
	if ((INL(dp, TXSTAT) & TXSTAT_ERR) == TXSTAT_ERR_NONE) {
		/* wait until all tx buffer have been transmitted */
		wait_time =
			(TX_BUF_SIZE * dp->mtu) / gem_speed_value[dp->speed];
		for (i = 0; TXSTAT_DESC_INDEX(dp) != lp->tx_tail; i++) {
			if (i > wait_time) {
				cmn_err(CE_NOTE,
					"!%s: %s: timeout: stopping tx dma",
					dp->name, __func__);
				break;
			}
			drv_usecwait(10);
		}
		DPRINTF(4, (CE_CONT, "%s: %s: the nic stopped in %d uS",
				dp->name, __func__, i*10));
	}
D 3

E 3
I 3
D 4
#ifdef NEVER
E 3
	/* tx fifo drain time (guess) */
	drv_usecwait(210);
D 3

E 3
I 3
#endif
E 4
I 4

E 4
E 3
	/* stop tx dma engine */
E 6
I 6
	/* stop tx */
E 6
I 3
	/* XXX - last chance to get correct tx_head */
	lp->tx_head = TXSTAT_DESC_INDEX(dp);
E 3
	OUTL(dp, TXCTL, 0);

D 6
	/* Stop Tx and Rx processes in the chip. */
E 6
I 6
	/* wait until tx and rx finish */
E 6
I 3
	lp->nic_active = B_FALSE;
E 3
	OUTL(dp, ENETCTL, ENETCTL_DISABLE);
D 5
	for (i = 0; (INL(dp, ENETCTL) & ENETCTL_DISABLE) != 0; i++) {
E 5
I 5
	for (i = 0; INL(dp, ENETCTL) & ENETCTL_DISABLE; i++) {
E 5
		if (i > 100) {
			cmn_err(CE_NOTE,
D 6
				"!%s: %s: timeout: stopping mac",
				dp->name, __func__);
E 6
I 6
			    "!%s: %s: timeout: stopping mac",
			    dp->name, __func__);
E 6
			break;
		}
		drv_usecwait(10);
	}

	/* wait until rx dma status become idle */
	if ((INL(dp, RXSTAT) & RXSTAT_ERR) == RXSTAT_ERR_NONE) {
		DPRINTF(0, (CE_CONT, "!%s: %s: rxstat_err_none",
D 6
				dp->name, __func__));
		for (i = 0;
			(INL(dp, RXSTAT) & RXSTAT_STATE) == RXSTAT_STATE_ACTIVE;
				i++) {
			if (i > 20) {
				cmn_err(CE_WARN,
					"!%s: %s: timeout: stopping rx dma",
					dp->name, __func__);
E 6
I 6
		    dp->name, __func__));
		i = 0;
		while ((INL(dp, RXSTAT) & RXSTAT_STATE)
		    == RXSTAT_STATE_ACTIVE) {
			if (i++ > 200) {
				/*
				 * XXX - it seems that the rx state
				 * alway active.
				 */
				DPRINTF(1, (CE_CONT,
				    "!%s: %s: timeout: stopping rx dma",
				    dp->name, __func__));
E 6
				break;
			}
			drv_usecwait(10);
		}
	}

D 6
	/* stop rx dma engine */
E 6
I 6
	DPRINTF(0, (CE_CONT, "%s: %s: rxstat:%x",
	    dp->name, __func__, INL(dp, RXSTAT)));

E 6
I 3
	/* XXX - last chance to get correct rx_head */
	lp->rx_head = RXSTAT_DESC_INDEX(dp);
I 6
	/* stop rx dma engine */
E 6
E 3
	OUTL(dp, RXCTL, 0);

	if (lp->mibvalid) {
D 6
		/* read mib counters before resettting the chip */
		bfe_get_stats(dp);
E 6
I 6
		/* read mib counters before resetting the chip */
		(void) bfe_get_stats(dp);
E 6
	}

	return (GEM_SUCCESS);
}

static void
bfe_eeprom_dump(struct gem_dev *dp, uint32_t *prom)
{
	int		i;

	cmn_err(CE_CONT, "!%s: bfe_eeprom dump:", dp->name);
	for (i = 0; i < EEPROM_SIZE; i += 4) {
D 6
		cmn_err(CE_CONT, "!0x%02x(%d): 0x%08x 0x%08x 0x%08x 0x%08x", 
			i*4, i*4, prom[i], prom[i+1], prom[i+2], prom[i+3]);
E 6
I 6
		cmn_err(CE_CONT, "!0x%02x(%d): 0x%08x 0x%08x 0x%08x 0x%08x",
		    i*4, i*4, prom[i], prom[i+1], prom[i+2], prom[i+3]);
E 6
	}
}

static int
bfe_attach_chip(struct gem_dev *dp)
{
	int		i;
	uint8_t		*mac;
D 6
	struct bfe_dev	*lp = (struct bfe_dev *)dp->private;
E 6
I 6
	struct bfe_dev	*lp = dp->private;
E 6
	uint8_t		*prom = (uint8_t *)lp->prom_data;

	for (i = 0; i < EEPROM_SIZE; i++) {
D 6
		lp->prom_data[i] = INL(dp, EEPROM_BASE + i*sizeof(uint32_t));
E 6
I 6
		lp->prom_data[i] = INL(dp, EEPROM_BASE + i*sizeof (uint32_t));
E 6
	}
#if DEBUG_LEVEL > 0
	bfe_eeprom_dump(dp, lp->prom_data);
#endif
	if (prom[EEPROM_MAGIC] != 0x01 &&
	    prom[EEPROM_MAGIC] != 0x10) {
		cmn_err(CE_WARN,
D 6
		"!%s: %s: contents in eeprom is corrupted", dp->name, __func__);
E 6
I 6
		    "!%s: %s: contents in eeprom is corrupted",
		    dp->name, __func__);
E 6
		bfe_eeprom_dump(dp, lp->prom_data);
		return (GEM_FAILURE);
	}

	mac = dp->dev_addr.ether_addr_octet;
	for (i = 0; i < ETHERADDRL; i += 2) {
		/* XXX - the core is running in big endian */
		*mac++ = prom[EEPROM_NODEADDR + i + 1];
		*mac++ = prom[EEPROM_NODEADDR + i];
	}

	/* get phy address from eeprom */
D 6
	dp->mii_phy_addr =prom[EEPROM_PHYADDR] & 0x1f;
E 6
I 6
	dp->mii_phy_addr = prom[EEPROM_PHYADDR] & 0x1f;
E 6

	/* fix rx buffer length, it must have additional 4 byte and rx_header */
D 6
	dp->rx_buf_len = dp->mtu + sizeof(struct ether_header)
			+ ETHERFCSL + 4 + RX_HEAD_ROOM;
E 6
I 6
	dp->rx_buf_len = dp->mtu + sizeof (struct ether_header)
	    + ETHERFCSL + 4 + RX_HEAD_ROOM;
E 6

	DPRINTF(2, (CE_CONT, "!%s: %s:"
D 6
		" phy_addr:%d, macintmask:0x%x,"
		" txcfg:0x%x, txmaxburst:0x%x,"
		" rxmaxburst:0x%x, txhiwat:0x%x",
			dp->name, __func__,
			dp->mii_phy_addr,
			INL(dp, MACINTMASK), INL(dp, TXCFG),
			INL(dp, TXMAXBURSTLEN), INL(dp, RXMAXBURSTLEN),
			INL(dp, TXHIWAT)));
E 6
I 6
	    " phy_addr:%d, macintmask:0x%x,"
	    " txcfg:0x%x, txmaxburst:0x%x,"
	    " rxmaxburst:0x%x, txhiwat:0x%x",
	    dp->name, __func__,
	    dp->mii_phy_addr,
	    INL(dp, MACINTMASK), INL(dp, TXCFG),
	    INL(dp, TXMAXBURSTLEN), INL(dp, RXMAXBURSTLEN),
	    INL(dp, TXHIWAT)));
E 6

D 3
	/* mib counters are not initialized */
E 3
I 3
	/* mib counters are not initialized yet. */
E 3
	lp->mibvalid = B_FALSE;

I 6
#ifdef GEM_CONFIG_POLLING
	dp->misc_flag |= GEM_POLL_RXONLY;
#endif
E 6
I 4
#ifdef GEM_CONFIG_VLAN
	dp->misc_flag |= GEM_VLAN_SOFT;
#endif
E 4
	return (GEM_SUCCESS);
}


D 4
static void
E 4
I 4
static int
E 4
bfe_get_stats(struct gem_dev *dp)
{
	int	txerr;
	int	rxerr;
I 5
	int	x;
I 6
	struct bfe_dev	*lp = dp->private;
E 6
E 5

D 6
	struct bfe_dev	*lp = (struct bfe_dev *)dp->private;

E 6
	if (!lp->mibvalid) {
D 4
		return;
E 4
I 4
		return (GEM_SUCCESS);
E 4
	}

D 6
	ddi_rep_get32(dp->regs_handle, lp->mib, 
		(uint32_t *)(((caddr_t)dp->base_addr) + MIBDATA),
		MIB_SIZE, DDI_DEV_AUTOINCR);
E 6
I 6
	ddi_rep_get32(dp->regs_handle, lp->mib,
	    (void *)(((caddr_t)dp->base_addr) + MIBDATA),
	    MIB_SIZE, DDI_DEV_AUTOINCR);
E 6

	txerr = 0;
	rxerr = 0;

	dp->stats.collisions	+= lp->mib[0x40/4];
	dp->stats.first_coll	+= lp->mib[0x44/4];
	dp->stats.multi_coll	+= lp->mib[0x48/4];
D 5
	dp->stats.excoll	+= lp->mib[0x4c/4]; txerr += lp->mib[0x4c/4];
E 5
I 5
	dp->stats.excoll	+= x = lp->mib[0x4c/4]; txerr += x;
E 5
I 4
D 6
#ifdef NEVER
	/* XXX - no carrier counter seems to be broken */
E 4
D 5
	dp->stats.nocarrier	+= lp->mib[0x58/4]; txerr += lp->mib[0x58/4];
E 5
I 5
	dp->stats.nocarrier	+= x = lp->mib[0x58/4]; txerr += x;
E 5
I 4
#endif
E 6
I 6
	/*
	 * XXX - no carrier counter seems to be broken
	 * dp->stats.nocarrier	+= x = lp->mib[0x58/4]; txerr += x;
	 */
E 6
E 4
	dp->stats.defer		+= lp->mib[0x54/4];
D 5
	dp->stats.underflow	+= lp->mib[0x3c/4]; txerr += lp->mib[0x3c/4];
	dp->stats.xmtlatecoll	+= lp->mib[0x50/4]; txerr += lp->mib[0x50/4];
E 5
I 5
	dp->stats.underflow	+= x = lp->mib[0x3c/4]; txerr += x;
	dp->stats.xmtlatecoll	+= x = lp->mib[0x50/4]; txerr += x;
E 5

D 5
	dp->stats.frame_too_long += lp->mib[0xb4/4]; rxerr += lp->mib[0xb4/4];
	dp->stats.missed	+= lp->mib[0xbc/4]; rxerr += lp->mib[0xbc/4];
	dp->stats.runt		+= lp->mib[0xc4/4]; rxerr += lp->mib[0xc4/4];
	dp->stats.crc		+= lp->mib[0xc8/4]; rxerr += lp->mib[0xc8/4];
	dp->stats.frame	+= lp->mib[0xcc/4] + lp->mib[0xd0/4];
				rxerr += lp->mib[0xcc/4] + lp->mib[0xd0/4];
E 5
I 5
	dp->stats.frame_too_long += x = lp->mib[0xb4/4]; rxerr += x;
	dp->stats.missed	+= x = lp->mib[0xbc/4]; rxerr += x;
	dp->stats.runt		+= x = lp->mib[0xc4/4]; rxerr += x;
	dp->stats.crc		+= x = lp->mib[0xc8/4]; rxerr += x;
	dp->stats.frame	+= x = lp->mib[0xcc/4] + lp->mib[0xd0/4];
				rxerr += x;
E 5
	dp->stats.errxmt += txerr;
	dp->stats.errrcv += rxerr;
I 4

	return (GEM_SUCCESS);
E 4
}

/*
D 6
 * discriptor manupiration
E 6
I 6
 * descriptor manipulation
E 6
 */
static int
bfe_tx_desc_write(struct gem_dev *dp, int slot,
D 3
		ddi_dma_cookie_t *dmacookie, int frags, uint32_t intreq)
E 3
I 3
D 5
		ddi_dma_cookie_t *dmacookie, int frags, uint32_t flag)
E 5
I 5
		ddi_dma_cookie_t *dmacookie, int frags, uint64_t flag)
E 5
E 3
{
I 6
#ifdef GEM_CONFIG_TX_DIRECT
E 6
	int			i;
	int			ix;
I 6
#endif
E 6
	struct bfe_desc		*tdp;
	ddi_dma_cookie_t	*dcp;
	uint32_t		mark;
D 6
	struct bfe_dev		*lp = (struct bfe_dev *)dp->private;
E 6

#if DEBUG_LEVEL > 2
D 3
	cmn_err(CE_CONT,
	"!%s: bfe_tx_desc_write seqnum: %d, slot %d, frags: %d flags: %d",
		dp->name, dp->tx_desc_tail, slot, frags, intreq);
E 3
I 3
D 6
	cmn_err(CE_CONT, "!%s: %s seqnum: %d, slot %d, frags: %d flags: %d",
		dp->name, __func__, dp->tx_desc_tail, slot, frags, flag);
E 6
I 6
{
	int	i;

	cmn_err(CE_CONT, "!%s: %s seqnum: %d, slot %d, frags: %d flags: %ld",
	    dp->name, __func__, dp->tx_desc_tail, slot, frags, flag);
E 6
E 3
	for (i = 0; i < frags; i++) {
		cmn_err(CE_CONT, "!%d: addr: 0x%llx, len: 0x%x",
D 6
			i, dmacookie[i].dmac_laddress, dmacookie[i].dmac_size);
E 6
I 6
		    i, dmacookie[i].dmac_laddress, dmacookie[i].dmac_size);
E 6
	}
	cmn_err(CE_CONT, "!          isr: %b", INL(dp, INTSTAT), INT_BITS);
I 6
}
E 6
#endif
#if DEBUG_LEVEL > 2
D 3
	intreq |= GEM_TXFLAG_INTR;
E 3
I 3
	flag |= GEM_TXFLAG_INTR;
E 3
#endif
I 4
D 6
#if 0
	ASSERT(frags == 1);
	dmacookie->dmac_size = 1514;
#endif
E 6
E 4
	/*
	 * write tx descriptor(s)
	 */
D 3
	mark = CTL_STARTF;
	dcp = dmacookie;
	ix = slot;
E 3
I 3
	mark = CTL_ENDF;
D 5
	if ((flag & GEM_TXFLAG_INTR) != 0) {
E 5
I 5
	if (flag & GEM_TXFLAG_INTR) {
E 5
		mark |= CTL_INTREQ;
	}
	dcp = &dmacookie[frags - 1];
E 3
D 4
#ifndef CONFIG_TX_SINGLE
E 4
I 4
D 5
#if MAXTXFRAGS > 1
E 5
I 5

I 6
#ifdef GEM_CONFIG_TX_DIRECT
E 6
E 5
E 4
D 3
	for (i = frags; --i > 0; ix = SLOT(ix + 1, TX_RING_SIZE), dcp++) {
E 3
I 3
	for (i = frags - 1; i > 0; i--, dcp--) {
		ix = SLOT(slot + i, TX_RING_SIZE);
E 3
D 6
		tdp = &((struct bfe_desc *)dp->tx_ring)[ix];
E 6
I 6
		tdp = &BFE_DESC(dp->tx_ring)[ix];
E 6
I 3

		if (ix == TX_RING_SIZE - 1) {
			mark |= CTL_ENDTBL;
		}
E 3
D 5
		tdp->desc_addr = LE32(dcp->dmac_address | SB_PCIDMA_BASE);
D 3
		tdp->desc_ctl  = LE32((dcp->dmac_size & CTL_LENGTH) | mark
				 | ((ix == TX_RING_SIZE - 1) ? CTL_ENDTBL : 0));
E 3
I 3
		tdp->desc_ctl  = LE32(dcp->dmac_size | mark);
E 5
I 5
		mark |= dcp->dmac_size;
		tdp->desc_addr = LE_32(dcp->dmac_address | SB_PCIDMA_BASE);
		tdp->desc_ctl  = LE_32(mark);
E 5
E 3
		mark = 0;
D 3

E 3
	}
D 4
#endif /* !TX_SINGLE */
E 4
I 4
D 5
#endif /* MAXTXFRAGS > 1*/
E 5
E 4
D 3
	/* make last fragment */
	tdp = &((struct bfe_desc *)dp->tx_ring)[ix];
E 3
I 3
D 6

E 6
I 6
#endif
E 6
	/* make first fragment */
D 6
	tdp = &((struct bfe_desc *)dp->tx_ring)[slot];
E 6
I 6
	tdp = &BFE_DESC(dp->tx_ring)[slot];
E 6
I 5
	mark |= (dcp->dmac_size | CTL_STARTF);
E 5
	if (slot == TX_RING_SIZE - 1) {
		mark |= CTL_ENDTBL;
	}
E 3
D 5
	tdp->desc_addr = LE32(dcp->dmac_address | SB_PCIDMA_BASE);
D 3
	tdp->desc_ctl  = LE32((dcp->dmac_size & CTL_LENGTH) | mark | CTL_ENDF
			| (intreq ? CTL_INTREQ : 0)
			| ((ix == TX_RING_SIZE - 1) ? CTL_ENDTBL : 0));
E 3
I 3
	tdp->desc_ctl  = LE32(dcp->dmac_size | mark | CTL_STARTF);
E 5
I 5
	tdp->desc_addr = LE_32(dcp->dmac_address | SB_PCIDMA_BASE);
	tdp->desc_ctl  = LE_32(mark);
E 5
E 3

	return (frags);
}

static void
bfe_tx_start(struct gem_dev *dp, int start_slot, int nslot)
{
D 6
	struct bfe_dev		*lp = (struct bfe_dev *)dp->private;
E 6
I 6
	struct bfe_dev	*lp = dp->private;
E 6

	gem_tx_desc_dma_sync(dp, start_slot, nslot, DDI_DMA_SYNC_FORDEV);

	/* set new tail */
	lp->tx_tail = SLOT(start_slot + nslot, TX_RING_SIZE);
D 5

E 5
D 6
	OUTL(dp, TXTAIL, lp->tx_tail * sizeof(struct bfe_desc));
E 6
I 6
	OUTL(dp, TXTAIL, lp->tx_tail * sizeof (struct bfe_desc));
E 6
}

static void
bfe_rx_desc_write(struct gem_dev *dp, int slot,
	    ddi_dma_cookie_t *dmacookie, int frags)
{
D 6
	int			i;
I 5
	uint32_t		ctl;
E 5
	struct bfe_desc		*rdp;
	struct bfe_dev		*lp = (struct bfe_dev *)dp->private;
E 6
I 6
	uint32_t	ctl;
	struct bfe_desc	*rdp;
	struct bfe_dev	*lp = dp->private;
E 6

#if DEBUG_LEVEL > 2
I 6
{
	int		i;

E 6
	cmn_err(CE_CONT,
D 6
		"!%s: bfe_rx_desc_write seqnum: %d, slot %d, frags: %d",
		dp->name, dp->rx_desc_tail, slot, frags);
E 6
I 6
	    "!%s: bfe_rx_desc_write seqnum: %d, slot %d, frags: %d",
	    dp->name, dp->rx_desc_tail, slot, frags);
E 6
	for (i = 0; i < frags; i++) {
		cmn_err(CE_CONT, "!%d: addr: 0x%llx, len: 0x%x(%d)",
D 6
			i, dmacookie[i].dmac_laddress,
			dmacookie[i].dmac_size, dmacookie[i].dmac_size);
E 6
I 6
		    i, dmacookie[i].dmac_laddress,
		    dmacookie[i].dmac_size, dmacookie[i].dmac_size);
E 6
	}
I 6
}
E 6
#endif
	ASSERT(frags == 1);

	/*
	 * write a RX descriptor
	 */
I 5
	ctl = (dmacookie->dmac_size & CTL_LENGTH);
	if (slot == RX_RING_SIZE - 1) {
		ctl |= CTL_ENDTBL;
	}
E 5
D 6
	rdp = &((struct bfe_desc *)dp->rx_ring)[slot];
E 6
I 6
	rdp = &BFE_DESC(dp->rx_ring)[slot];
E 6

D 5
	rdp->desc_addr = LE32(dmacookie->dmac_address | SB_PCIDMA_BASE);
	rdp->desc_ctl  = LE32((dmacookie->dmac_size & CTL_LENGTH)
		        | ((slot == RX_RING_SIZE - 1) ? CTL_ENDTBL : 0));
E 5
I 5
	rdp->desc_addr = LE_32(dmacookie->dmac_address | SB_PCIDMA_BASE);
	rdp->desc_ctl  = LE_32(ctl);
E 5

	/* clear rx header area to check reception of big packets */
D 3
#if 0
E 3
	bzero(dp->rx_buf_tail->rxb_buf, RX_HEAD_ROOM);
D 6
	ddi_dma_sync(dp->rx_buf_tail->rxb_dh,
			0, RX_HEAD_ROOM, DDI_DMA_SYNC_FORDEV);
E 6
I 6
	(void) ddi_dma_sync(dp->rx_buf_tail->rxb_dh,
	    0, RX_HEAD_ROOM, DDI_DMA_SYNC_FORDEV);
E 6
D 3
#else
	bzero(dp->rx_buf_tail->rxb_buf, dp->rx_buf_len);
	ddi_dma_sync(dp->rx_buf_tail->rxb_dh,
			0, dp->rx_buf_len, DDI_DMA_SYNC_FORDEV);
#endif
E 3

	lp->rx_tail = SLOT(slot + frags, RX_RING_SIZE);
}

static void
bfe_rx_start(struct gem_dev *dp, int start_slot, int nslot)
{
D 6
	struct bfe_dev		*lp = (struct bfe_dev *)dp->private;
E 6
I 6
	struct bfe_dev	*lp = dp->private;
E 6

	gem_rx_desc_dma_sync(dp, start_slot, nslot, DDI_DMA_SYNC_FORDEV);

	/* set new tail */
D 6
	OUTL(dp, RXTAIL, lp->rx_tail * sizeof(struct bfe_desc));
E 6
I 6
	OUTL(dp, RXTAIL, lp->rx_tail * sizeof (struct bfe_desc));
E 6
}

I 6
#ifdef DEBUG_LEVEL
E 6
static void
bfe_tx_desc_dump(struct gem_dev *dp, seqnum_t head, int ndesc)
{
D 6
	int			i;
	struct bfe_desc		*tdp;
E 6
I 6
	int		i;
	struct bfe_desc	*tdp;
E 6

	cmn_err(CE_CONT, "!%s: tx_desc_dump:  slot:%d, seqnum:%d",
D 6
		dp->name, SLOT(head, TX_RING_SIZE), head);
E 6
I 6
	    dp->name, SLOT(head, TX_RING_SIZE), head);
E 6

	for (i = 0; i < ndesc; i++) {
D 6
		tdp = &((struct bfe_desc *)dp->tx_ring)[
				SLOT(head + i, TX_RING_SIZE)];
		ddi_dma_sync(dp->desc_dma_handle,
			(off_t)(((caddr_t)tdp) - dp->rx_ring),
			sizeof(struct bfe_desc), DDI_DMA_SYNC_FORKERNEL);

E 6
I 6
		tdp = &BFE_DESC(dp->tx_ring)[SLOT(head + i, TX_RING_SIZE)];
		(void) ddi_dma_sync(dp->desc_dma_handle,
		    (off_t)(((caddr_t)tdp) - dp->rx_ring),
		    sizeof (struct bfe_desc), DDI_DMA_SYNC_FORKERNEL);
E 6
		cmn_err(CE_CONT, "! %d: ctrl:%b, addr:0x%08x",
D 5
			i, LE32(tdp->desc_ctl), CTL_BITS,
			LE32(tdp->desc_addr));
E 5
I 5
D 6
			i, LE_32(tdp->desc_ctl), CTL_BITS,
			LE_32(tdp->desc_addr));
E 6
I 6
		    i, LE_32(tdp->desc_ctl), CTL_BITS,
		    LE_32(tdp->desc_addr));
E 6
E 5
	}
}
D 6

E 6
I 6
#endif
E 6
static uint_t
bfe_tx_desc_stat(struct gem_dev *dp, int slot, int ndesc)
{
D 3
	if (TXSTAT_DESC_INDEX(dp) == slot) {
E 3
I 3
D 6
	struct bfe_dev		*lp = (struct bfe_dev *)dp->private;
E 6
I 6
	struct bfe_dev	*lp = dp->private;
E 6

	if (lp->nic_active) {
		lp->tx_head = TXSTAT_DESC_INDEX(dp);
	}
	slot = SLOT(slot + ndesc - 1, TX_RING_SIZE);
	if (INSIDE(slot, lp->tx_head, lp->tx_tail)) {
E 3
		/* not yet */
		return (0);
	}
	return (GEM_TX_DONE);
}

I 6
#ifdef DEBUG_LEVEL
E 6
static void
bfe_packet_dump(struct gem_dev *dp, uint8_t *bp)
{
	cmn_err(CE_CONT, "!%s: "
D 6
		"%02x %02x %02x %02x %02x %02x %02x %02x "
		"%02x %02x %02x %02x %02x %02x",
		dp->name,
		bp[0], bp[1], bp[2], bp[3], bp[4], bp[5], bp[6], bp[7],
		bp[8], bp[9], bp[10], bp[11], bp[12], bp[13]);
E 6
I 6
	    "%02x %02x %02x %02x %02x %02x %02x %02x "
	    "%02x %02x %02x %02x %02x %02x",
	    dp->name,
	    bp[0], bp[1], bp[2], bp[3], bp[4], bp[5], bp[6], bp[7],
	    bp[8], bp[9], bp[10], bp[11], bp[12], bp[13]);
E 6
}
D 6

E 6
I 6
#endif
E 6
static uint64_t
bfe_rx_desc_stat(struct gem_dev *dp, int slot, int ndesc)
{
	struct rxbuf		*rbp = dp->rx_buf_head;
	volatile uint8_t	*hdp;
	uint16_t		rxf;
	uint_t			len;
	int			i;
	uint_t			ret;
D 6
	struct bfe_dev		*lp = (struct bfe_dev *)dp->private;
E 6
I 6
	struct bfe_dev		*lp = dp->private;
E 6

	/* compare the slot with current rx slot index */
D 3
	if (RXSTAT_DESC_INDEX(dp) == slot) {
		/* not received yet */
E 3
I 3
	if (lp->nic_active) {
		lp->rx_head = RXSTAT_DESC_INDEX(dp);
	}
	i = SLOT(slot + ndesc - 1, RX_RING_SIZE);
	if (INSIDE(i, lp->rx_head, lp->rx_tail)) {
		/* not yet */
E 3
		return (0);
	}

	if (lp->rx_rest > 0) {
		/*
D 6
		 * Ignore this fragment as it is a part of previous jumbo
		 * packet.
E 6
I 6
		 * Ignore this fragment as it is a part of the previous
		 * jumbo packet.
E 6
		 */
		lp->rx_rest -= min(rbp->rxb_buf_len, lp->rx_rest);
		return (GEM_RX_ERR);
	}

	/*
	 * Get rx header which is leading received data area.
	 */
D 6
	hdp = (volatile uint8_t *) rbp->rxb_buf;
E 6
I 6
	hdp = (volatile uint8_t *)rbp->rxb_buf;
E 6

	/*
D 6
	 * Need to wait until the length field at the begining
	 * of the receive buffer updated in case of received packet
	 * exceeds the buffer.
E 6
I 6
	 * Need to wait until the length field at the beginning
	 * of the receive buffer will have been updated in case of
	 * the received packet exceeds the length of the buffer.
E 6
	 */
	for (i = 0; i < 100; i++) {
		/* sync rx header area in the rx buffer */
D 6
		ddi_dma_sync(rbp->rxb_dh,
			0, RX_HEAD_ROOM, DDI_DMA_SYNC_FORKERNEL);
E 6
I 6
		(void) ddi_dma_sync(rbp->rxb_dh,
		    0, RX_HEAD_ROOM, DDI_DMA_SYNC_FORKERNEL);
E 6

		len = (hdp[RXHD_LEN + 1] << 8) | hdp[RXHD_LEN];
		rxf = (hdp[RXHD_RXF + 1] << 8) | hdp[RXHD_RXF];
D 5
		if (len != 0) {
E 5
I 5
		if (len) {
E 5
			break;
		}
		DPRINTF(3, (CE_CONT,
D 6
			"!%s: %s: length field was not updated yet",
			dp->name, __func__));
E 6
I 6
		    "!%s: %s: length field was not updated yet",
		    dp->name, __func__));
E 6
		drv_usecwait(10);
	}

	if (len < ETHERMIN + ETHERFCSL) {
		dp->stats.errrcv++;
		dp->stats.runt++;
		cmn_err(CE_CONT,
D 6
			"!%s: %s: runt error: slot:%d len:%d rxf 0x%b",
			dp->name, __func__, slot, len, rxf, RXF_BITS);
E 6
I 6
		    "!%s: %s: runt error: slot:%d len:%d rxf 0x%b",
		    dp->name, __func__, slot, len, rxf, RXF_BITS);
E 6
		return (GEM_RX_ERR);
	}

	ret = GEM_RX_DONE;

D 5
	if ((rxf & RXF_ERRORS) != 0) {
E 5
I 5
	if (rxf & RXF_ERRORS) {
E 5
		/* errored packet */
#ifdef notdef
D 5
		if ((rxf & RXF_NIBBLEODD) != 0) {
E 5
I 5
		if (rxf & RXF_NIBBLEODD) {
E 5
			/* The nic seems to stop */
			lp->need_to_reset = B_TRUE;
		}
#endif
		DPRINTF(1, (CE_CONT,
D 6
			"!%s: %s: rx error: slot:%d len:%d rxf 0x%b",
			dp->name, __func__, slot, len, rxf, RXF_BITS));
E 6
I 6
		    "!%s: %s: rx error: slot:%d len:%d rxf 0x%b",
		    dp->name, __func__, slot, len, rxf, RXF_BITS));
E 6
		ret |= GEM_RX_ERR;
	}

	DPRINTF(2, (CE_CONT,
D 6
		"!%s: %s: slot:%d len:%d rxf 0x%b",
		dp->name, __func__, slot, len, rxf, RXF_BITS));
E 6
I 6
	    "!%s: %s: slot:%d len:%d rxf 0x%b",
	    dp->name, __func__, slot, len, rxf, RXF_BITS));
E 6
#if DEBUG_LEVEL > 2
	bfe_packet_dump(dp, (uint8_t *)hdp);
#endif

	/* Is the packet too big ? */
	if (len > rbp->rxb_buf_len - RX_HEAD_ROOM) {
		lp->rx_rest = len - (rbp->rxb_buf_len - RX_HEAD_ROOM);
		dp->stats.errrcv++;
		dp->stats.frame_too_long++;
		cmn_err(CE_CONT,
D 6
			"!%s: %s: too_long error: slot:%d len:%d rxf 0x%b",
			dp->name, __func__, slot, len, rxf, RXF_BITS);
E 6
I 6
		    "!%s: %s: too_long error: slot:%d len:%d rxf 0x%b",
		    dp->name, __func__, slot, len, rxf, RXF_BITS);
E 6
		ret |= GEM_RX_ERR;
	}

	return (ret | ((len - ETHERFCSL) & GEM_RX_LEN));
}

static void
bfe_tx_desc_init(struct gem_dev *dp, int slot)
{
	/* invalidate the descriptor */
D 6
	((struct bfe_desc *) dp->tx_ring)[slot].desc_ctl =
D 5
		LE32((slot == TX_RING_SIZE - 1) ? CTL_ENDTBL : 0);
E 5
I 5
		LE_32((slot == TX_RING_SIZE - 1) ? CTL_ENDTBL : 0);
E 6
I 6
	BFE_DESC(dp->tx_ring)[slot].desc_ctl =
	    LE_32((slot == TX_RING_SIZE - 1) ? CTL_ENDTBL : 0);
E 6
E 5
}

static void
bfe_rx_desc_init(struct gem_dev *dp, int slot)
{
	/* invalidate the descriptor */
D 6
	((struct bfe_desc *) dp->rx_ring)[slot].desc_ctl =
D 5
		LE32((slot == RX_RING_SIZE - 1) ? CTL_ENDTBL : 0);
E 5
I 5
		LE_32((slot == RX_RING_SIZE - 1) ? CTL_ENDTBL : 0);
E 6
I 6
	BFE_DESC(dp->rx_ring)[slot].desc_ctl =
	    LE_32((slot == RX_RING_SIZE - 1) ? CTL_ENDTBL : 0);
E 6
E 5
}

/*
 * Device depend interrupt handler
 */
D 6
static u_int
E 6
I 6
static uint_t
E 6
bfe_interrupt(struct gem_dev *dp)
{
	uint32_t	isr;
	uint_t		flag = 0;
I 5
D 6
	boolean_t	update_intmask = B_FALSE;
E 5
	struct bfe_dev	*lp = (struct bfe_dev *)dp->private;
E 6
I 6
	struct bfe_dev	*lp = dp->private;
E 6

	isr = INL(dp, INTSTAT);

	if ((isr & lp->intmask) == 0) {
		/* Not for us */
D 5
		if (isr != 0) {
E 5
I 5
		if (isr) {
E 5
D 6
			OUTL(dp, INTSTAT, isr);
E 6
I 6
			OUTL(dp, INTSTAT, isr); FLUSH(dp, INTSTAT);
E 6
		}
		return (DDI_INTR_UNCLAIMED);
	}

D 4
	DPRINTF(2, (CE_CONT, "!%s: Interrupt, isr: 0x%b",
			   dp->name, isr, INT_BITS));
E 4
I 4
	DPRINTF(2, (CE_CONT, "!%s: %s, isr: 0x%b",
D 6
			   dp->name, __func__, isr, INT_BITS));
E 6
I 6
	    dp->name, __func__, isr, INT_BITS));
E 6
E 4

D 2
	if (!dp->nic_active) {
E 2
I 2
	if (!dp->mac_active) {
E 2
		/* the device is not active */
D 5
		if (isr != 0) {
E 5
I 5
		if (isr) {
E 5
D 6
			OUTL(dp, INTSTAT, isr);
E 6
I 6
			OUTL(dp, INTSTAT, isr); FLUSH(dp, INTSTAT);
E 6
		}
I 6
		/* inhibit interrupts gracefully */
		lp->intmask = 0;
		OUTL(dp, INTMASK, lp->intmask); FLUSH(dp, INTMASK);
E 6
		return (DDI_INTR_CLAIMED);
	}
D 5

E 5
I 5
D 6
#ifndef CONFIG_OPT_IO
E 5
	OUTL(dp, INTMASK, 0);
I 5
#endif
E 6
I 6

E 6
E 5
	OUTL(dp, INTSTAT, isr);
D 5

E 5
I 4
D 6
	isr &= lp->intmask;
E 6

E 4
D 5
	/*
	 * No need to flush INTSTAT because bfe_tx_desc_stat() and
	 * bfe_rx_desc_stat() routines imply reading registers in the nic.
	 */
E 5
D 4

E 4
#ifdef GEM_CONFIG_POLLING
I 6
	isr &= lp->intmask | INT_RX;

E 6
	if (dp->poll_interval != lp->last_poll_interval) {
D 5
		if (dp->poll_interval != 0) {
E 5
I 5
		if (dp->poll_interval) {
E 5
			/* polling mode */
D 5
			lp->intmask &= ~(INT_RX | INT_TX);
			OUTL(dp, GPTIMER, dp->poll_interval * 62);

			if (lp->last_poll_interval == 0) {
				/*
				 * To schedule the next timer interrupt,
				 * we pretend as we were interrupted from
				 * polling timer
				 */
				isr |= INT_GPTIMER;
			}
E 5
I 5
D 6
			lp->intmask_hw = lp->intmask & ~(INT_RX | INT_TX);
E 6
I 6
			lp->intmask &= ~INT_RX;
			lp->intmask |= INT_GPTIMER;
E 6
E 5
D 4
		}
		else {
E 4
I 4
		} else {
E 4
			/* normal mode */
D 5
			lp->intmask |= INT_RX | INT_TX;
			OUTL(dp, GPTIMER, 0);
I 4
			dp->tx_coalesce = B_FALSE;
E 5
I 5
D 6
			lp->intmask_hw = lp->intmask;
E 6
I 6
			lp->intmask |= INT_RX;
			lp->intmask &= ~INT_GPTIMER;
E 6
E 5
E 4
		}
D 5

E 5
I 5
D 6
		OUTL(dp, GPTIMER, dp->poll_interval * 62);
		update_intmask = B_TRUE;
E 6
I 6
		OUTL(dp, GPTIMER, dp->poll_interval/(10000 / RX_TIMEOUT_10u));
E 6
E 5
		lp->last_poll_interval = dp->poll_interval;
I 6

		if ((dp->misc_flag & GEM_NOINTR) == 0) {
			OUTL(dp, INTMASK, lp->intmask);
		}
E 6
	}
I 6
#else
	isr &= lp->intmask;
E 6
I 5
#endif /* GEM_CONFIG_POLLING */
E 5

D 5
	if ((isr & INT_GPTIMER) != 0) {
		/* force to process RX and TX */
		isr |= INT_RX | INT_TX;
E 5
I 5
	/*
	 * No need to flush INTSTAT because bfe_tx_desc_stat() and
	 * bfe_rx_desc_stat() routines imply reading registers in the nic.
	 */
	if ((isr & (INT_RX | INT_RXDESCEMPTY | INT_TX)) == 0) {
		FLUSH(dp, INTSTAT);
E 5
	}
D 4
#else
	isr &= lp->intmask;
E 4
D 5
#endif /* GEM_CONFIG_POLLING */
E 5

D 5
	if ((isr & (INT_RX | INT_RXDESCEMPTY)) != 0) {
E 5
I 5
	if (isr & (INT_RX | INT_RXDESCEMPTY)) {
E 5
		(void) gem_receive(dp);

D 5
		if ((isr & INT_RXDESCEMPTY) != 0) {
E 5
I 5
		if (isr & INT_RXDESCEMPTY) {
E 5
			/* RX descriptor is empty */
			DPRINTF(2, (CE_CONT,
D 6
				"!%s: %s: rxctl:%x rxtail:%x rxstat:%x",
				dp->name, __func__,
				INL(dp, RXCTL), INL(dp, RXTAIL),
				INL(dp, RXSTAT)));
E 6
I 6
			    "!%s: %s: rxctl:%x rxtail:%x rxstat:%x",
			    dp->name, __func__,
			    INL(dp, RXCTL), INL(dp, RXTAIL),
			    INL(dp, RXSTAT)));
E 6
			dp->stats.norcvbuf++;
		}
	}

D 5
	if ((isr & INT_TX) != 0) {
E 5
I 5
	if (isr & INT_TX) {
E 5
		if (gem_tx_done(dp)) {
			flag |= INTR_RESTART_TX;
		}
D 5
#ifdef GEM_CONFIG_POLLING
		if ((isr & INT_GPTIMER) != 0) {
			/* force to process RX and TX */
			OUTL(dp, TXTAIL, lp->tx_tail*sizeof(struct bfe_desc));
		}
#endif
E 5
	}

I 4
D 5
	if ((isr & INT_MAC) != 0) {
E 5
I 5
	if (isr & INT_MAC) {
E 5
		uint32_t	macint;

		macint = INL(dp, MACINTSTAT);
		cmn_err(CE_NOTE, "!%s: mac interrupt: macint:0x%b",
D 6
			dp->name, macint, MACINT_BITS);
E 6
I 6
		    dp->name, macint, MACINT_BITS);
E 6
		OUTL(dp, MACINTSTAT, macint);
	}

E 4
D 5
	if ((isr & (INT_DESCERR | INT_DATAERR |
		    INT_DESCPROT | INT_RXOF | INT_TXUF)) != 0) {
		FLUSH(dp, INTSTAT);
E 5
I 5
	if (isr & (INT_DESCERR | INT_DATAERR |
D 6
			INT_DESCPROT | INT_RXOF | INT_TXUF)) {
E 6
I 6
	    INT_DESCPROT | INT_RXOF | INT_TXUF)) {
E 6
E 5
D 3
		cmn_err(CE_WARN, "!%s: unexpected interrupt: isr:%b",
E 3
I 3
		cmn_err(CE_NOTE, "!%s: unexpected interrupt: isr:%b",
E 3
D 6
			dp->name, isr, INT_BITS);
E 6
I 6
		    dp->name, isr, INT_BITS);
E 6

D 5
		if ((isr & INT_RXOF) != 0) {
E 5
I 5
		if (isr & INT_RXOF) {
			dp->stats.errrcv++;
E 5
			dp->stats.overflow++;
		}
D 5
		if ((isr & INT_TXUF) != 0) {
E 5
I 5
		if (isr & INT_TXUF) {
			dp->stats.errxmt++;
E 5
			dp->stats.underflow++;
		}

		lp->need_to_reset = B_TRUE;
	}

D 6
        if (lp->need_to_reset) {
E 6
I 6
	if (lp->need_to_reset) {
E 6
D 3
		cmn_err(CE_WARN, "!%s: %s: isr:%b, resetting the chip ...",
E 3
I 3
		cmn_err(CE_NOTE, "!%s: %s: isr:%b, resetting the chip ...",
E 3
D 6
			dp->name, __func__, isr, INT_BITS);
D 3
#if 0
E 3
I 3
#ifdef NEVER
E 3
		/* XXX - workaround for receiving jumbo packet: reset twice */
		bfe_reset_chip(dp);
#endif
D 4
                gem_restart_nic(dp, B_TRUE);
E 4
I 4
                gem_restart_nic(dp, GEM_RESTART_KEEP_BUF | GEM_RESTART_NOWAIT);
E 6
I 6
		    dp->name, __func__, isr, INT_BITS);
E 6
E 4

I 6
		(void) gem_restart_nic(dp,
		    GEM_RESTART_KEEP_BUF | GEM_RESTART_NOWAIT);

E 6
		flag |= INTR_RESTART_TX;
		lp->need_to_reset = B_FALSE;
D 6
        }
D 5

E 5
I 5
#ifdef CONFIG_OPT_IO
	if ((dp->misc_flag & GEM_NOINTR) == 0 && update_intmask) {
		/* restore interrupt mask */
		OUTL(dp, INTMASK, lp->intmask_hw);
E 6
	}
D 6
#else
E 5
	if ((dp->misc_flag & GEM_NOINTR) == 0) {
		/* restore interrupt mask */
D 5
		OUTL(dp, INTMASK, lp->intmask);
E 5
I 5
		OUTL(dp, INTMASK, lp->intmask_hw);
E 5
	}
D 5

E 5
I 5
#endif
E 6
I 6

E 6
E 5
	return (DDI_INTR_CLAIMED | flag);
}

/*
 * HW depend MII routine
 */
static int
bfe_mii_config(struct gem_dev *dp)
{
	uint16_t	val;

D 3
	if (gem_mii_config_default(dp) < 0) {
E 3
I 3
	if (gem_mii_config_default(dp) != GEM_SUCCESS) {
E 3
		return (GEM_FAILURE);
	}

	/* enable LED */
	val = gem_mii_read(dp, 0x1a);
	gem_mii_write(dp, 0x1a, val & ~0x8000);

	val = gem_mii_read(dp, 0x1b);
	gem_mii_write(dp, 0x1b, val & 0x0040);

	return (GEM_SUCCESS);
}

static void
bfe_mii_sync(struct gem_dev *dp)
{
	/* nothing */
}

static uint16_t
bfe_mii_read(struct gem_dev *dp, uint_t reg)
{
	int		i;
	uint16_t	val;

	OUTL(dp, MACINTSTAT, MACINT_MII);

D 5
	if ((INL(dp, MACINTSTAT) & MACINT_MII) != 0) {
E 5
I 5
	if (INL(dp, MACINTSTAT) & MACINT_MII) {
E 5
		cmn_err(CE_WARN,
D 6
		"!%s: %s: failed to clear MII bit in MACINTSTAT register",
			dp->name, __func__);
E 6
I 6
		    "!%s: %s: failed to clear MII bit in MACINTSTAT register",
		    dp->name, __func__);
E 6
D 4
		return (0xffff);
E 4
I 4
		return (0);
E 4
	}

	OUTL(dp, MIIDATA, MII_READ_CMD(dp->mii_phy_addr, reg));

	/* wait until done */
	for (i = 0; (INL(dp, MACINTSTAT) & MACINT_MII) == 0; i++) {
		if (i > 100) {
			val = INL(dp, MIIDATA);
			cmn_err(CE_WARN, "!%s: %s: timeout: 0x%b",
D 6
				dp->name, __func__, val, MII_STATUS_BITS);
E 6
I 6
			    dp->name, __func__, val, MII_STATUS_BITS);
E 6
D 4
			return (0xffff);
E 4
I 4
			return (0);
E 4
		}
		drv_usecwait(10);
	}
	val = INL(dp, MIIDATA);

	DPRINTF(4, (CE_CONT, "!%s: %s: done: 0x%04x", dp->name, __func__, val));

	return (val);
}

static void
bfe_mii_write(struct gem_dev *dp, uint_t reg, uint16_t val)
{
	int	i;

	OUTL(dp, MACINTSTAT, MACINT_MII);

D 5
	if ((INL(dp, MACINTSTAT) & MACINT_MII) != 0) {
E 5
I 5
	if (INL(dp, MACINTSTAT) & MACINT_MII) {
E 5
		cmn_err(CE_WARN,
D 6
		"!%s: %s: failed to clear MII bit in MACINTSTAT register",
			dp->name, __func__);
E 6
I 6
		    "!%s: %s: failed to clear MII bit in MACINTSTAT register",
		    dp->name, __func__);
E 6
		return;
	}

	OUTL(dp, MIIDATA, MII_WRITE_CMD(dp->mii_phy_addr, reg, val));

	for (i = 0; (INL(dp, MACINTSTAT) & MACINT_MII) == 0; i++) {
		if (i > 100) {
			cmn_err(CE_WARN, "!%s: %s: timeout",
D 6
				dp->name, __func__);
E 6
I 6
			    dp->name, __func__);
E 6
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
bfeattach(dev_info_t *dip, ddi_attach_cmd_t cmd)
{
	int			i;
D 6
	ddi_acc_handle_t	conf_handle;
E 6
	int			ret;
I 6
	ddi_acc_handle_t	conf_handle;
E 6
	uint16_t		vid;
	uint16_t		did;
	uint8_t			revid;
I 6
#ifdef DEBUG_LEVEL
E 6
	uint32_t		ilr;
	uint8_t			cacheline;
	uint8_t			latencytimer;
I 6
#endif
E 6
	int			unit;
	struct chip_info	*p;
	const char		*drv_name;
	struct gem_dev		*dp;
	struct bfe_dev		*lp;
	void			*base;
	ddi_acc_handle_t	regs_ha;
	struct gem_conf		*gcp;

	unit =  ddi_get_instance(dip);
	drv_name = ddi_driver_name(dip);

	DPRINTF(0, (CE_CONT, "!%s%d: bfeattach: called %s",
D 6
		drv_name, unit, ident));
E 6
I 6
	    drv_name, unit, ident));
E 6

	/*
	 * Common codes after power-up
	 */
	if (pci_config_setup(dip, &conf_handle) != DDI_SUCCESS) {
		cmn_err(CE_WARN, "!%s%d: pci_config_setup failed",
D 6
			drv_name, unit);
E 6
I 6
		    drv_name, unit);
E 6
		return (DDI_FAILURE);
	}

	/*
	 * XXX - fix command register in pci config space.
	 * some versions of bios in DELL Inspiron 5160 don't set
	 * MAE bit. Thank to Jamie for reporting and testing.
	 */
	pci_config_put16(conf_handle, PCI_CONF_COMM,
D 6
		PCI_COMM_IO | PCI_COMM_MAE | PCI_COMM_ME |
			pci_config_get16(conf_handle, PCI_CONF_COMM));
E 6
I 6
	    PCI_COMM_IO | PCI_COMM_MAE | PCI_COMM_ME |
	    pci_config_get16(conf_handle, PCI_CONF_COMM));
E 6

	/* ensure the pmr status is D0 mode */
	(void) gem_pci_set_power_state(dip, conf_handle, PCI_PMCSR_D0);

	vid  = pci_config_get16(conf_handle, PCI_CONF_VENID);
	did  = pci_config_get16(conf_handle, PCI_CONF_DEVID);
D 6
	revid= pci_config_get8(conf_handle, PCI_CONF_REVID);
E 6
I 6
	revid = pci_config_get8(conf_handle, PCI_CONF_REVID);

#ifdef DEBUG_LEVEL
E 6
	ilr = pci_config_get32(conf_handle, PCI_CONF_ILINE);
D 6
	DPRINTF(0, (CE_CONT, "!%s%d: ilr 0x%08x", drv_name, unit, ilr));
E 6

D 6
	/* XXX - BCM440x does't have cache line register */
E 6
I 6
	/* XXX - BCM440x doesn't have cache line register */
E 6
	cacheline = pci_config_get8(conf_handle, PCI_CONF_CACHE_LINESZ);
	latencytimer = pci_config_get8(conf_handle, PCI_CONF_LATENCY_TIMER);
D 6
#if 0
	pci_config_put8(conf_handle, PCI_CONF_LATENCY_TIMER, 0x40); /* XXX */
#endif
	DPRINTF(0, (CE_CONT,
	"!%s%d: cache line size: 0x%02x, latency timer: 0x%02x, stat: 0x%04x",
		drv_name, unit, cacheline, latencytimer,
		pci_config_get16(conf_handle, PCI_CONF_STAT)));

E 6
I 6
	if (bfe_debug > 0) {
		cmn_err(CE_CONT,
		    "!%s%d: ilr: 0x%08x, cache line size: 0x%02x,"
		    " latency timer: 0x%02x, stat: 0x%04x",
		    drv_name, unit, ilr, cacheline, latencytimer,
		    pci_config_get16(conf_handle, PCI_CONF_STAT));
	}
#endif /* DEBUG_LEVEL */
E 6
	pci_config_teardown(&conf_handle);

	switch (cmd) {
	case DDI_RESUME:
		return (gem_resume(dip));

	case DDI_ATTACH:
		for (i = 0, p = bfe_chiptbl; i < CHIPTABLESIZE; i++, p++) {
			if (p->venid == vid && p->devid == did) {
				/* found */
				cmn_err(CE_CONT,
D 6
			"!%s%d: %s (vid: 0x%04x, did: 0x%04x, revid: 0x%02x)",
				drv_name, unit, p->name, vid, did, revid);
E 6
I 6
				    "!%s%d: %s (vid: 0x%04x, did: 0x%04x,"
				    " revid: 0x%02x)",
				    drv_name, unit, p->name, vid, did, revid);
E 6
				goto chip_found;
			}
		}
		/* Not found */
		cmn_err(CE_WARN,
D 6
			"!%s%d: %s: unknown PCI venid/devid (0x%x, 0x%x)",
			drv_name, unit, __func__, vid, did);
E 6
I 6
		    "!%s%d: %s: unknown PCI venid/devid (0x%x, 0x%x)",
		    drv_name, unit, __func__, vid, did);
E 6
		/* fall down */
chip_found:
		/*
		 * Map in the device registers.
		 */
D 6
		if (gem_pci_regs_map_setup(dip,
			PCI_ADDR_MEM32, PCI_ADDR_MASK,
			&bfe_dev_attr, (caddr_t *)&base, &regs_ha) !=
								DDI_SUCCESS) {
			cmn_err(CE_WARN, "!%s%d: ddi_regs_map_setup failed",
				drv_name, unit);
E 6
I 6
		ret = gem_pci_regs_map_setup(dip,
		    PCI_ADDR_MEM32, PCI_ADDR_MASK,
		    &bfe_dev_attr, (void *)&base, &regs_ha);
		if (ret != DDI_SUCCESS) {
			cmn_err(CE_WARN,
			    "!%s%d: ddi_regs_map_setup failed",
			    drv_name, unit);
E 6
			goto err;
		}

		/*
D 6
		 * construct gem configration
E 6
I 6
		 * construct gem configuration
E 6
		 */
D 6
		gcp = (struct gem_conf *)
			kmem_zalloc(sizeof(struct gem_conf), KM_SLEEP);
E 6
I 6
		gcp = kmem_zalloc(sizeof (struct gem_conf), KM_SLEEP);
E 6

		/* name */
D 6
		sprintf(gcp->gc_name, "%s%d", drv_name, unit);
E 6
I 6
		(void) sprintf(gcp->gc_name, "%s%d", drv_name, unit);
E 6

D 6
		gcp->gc_tx_buf_align = sizeof(uint8_t) - 1;
E 6
I 6
		gcp->gc_tx_buf_align = sizeof (uint8_t) - 1;
E 6
D 4
#ifdef CONFIG_TX_SINGLE
		gcp->gc_tx_max_frags = 1;
#else
		gcp->gc_tx_max_frags = GEM_MAXTXFRAGS;
#endif
E 4
I 4
		gcp->gc_tx_max_frags = MAXTXFRAGS;
E 4
		gcp->gc_tx_max_descs_per_pkt = gcp->gc_tx_max_frags;

		gcp->gc_tx_desc_unit_shift = 3;	/* 8byte */
D 6
		gcp->gc_tx_buf_size  = TX_BUF_SIZE;
E 6
D 4
		gcp->gc_tx_buf_limit = gcp->gc_tx_buf_size;
E 4
		gcp->gc_tx_ring_size = TX_RING_SIZE;
D 4
		gcp->gc_tx_ring_limit= gcp->gc_tx_ring_size;
E 4
I 4
D 6
		gcp->gc_tx_ring_limit= TX_RING_SIZE - 1;
E 6
I 6
		gcp->gc_tx_ring_limit = TX_RING_SIZE - 1;
		gcp->gc_tx_buf_size = TX_BUF_SIZE;
#ifdef GEM_CONFIG_TX_DIRECT
		gcp->gc_tx_buf_limit = gcp->gc_tx_buf_size;
#else
E 6
		gcp->gc_tx_buf_limit =
D 6
			min(gcp->gc_tx_ring_limit, gcp->gc_tx_buf_size);
E 4
		gcp->gc_tx_auto_pad  = B_FALSE;
E 6
I 6
		    min(gcp->gc_tx_ring_limit, gcp->gc_tx_buf_size);
#endif
		gcp->gc_tx_auto_pad = B_FALSE;
E 6
		gcp->gc_tx_copy_thresh = bfe_tx_copy_thresh;
D 4
#ifdef CONFIG_TX_SINGLE
		gcp->gc_tx_desc_write_oo = B_TRUE;
#else
		gcp->gc_tx_desc_write_oo = B_FALSE;
#endif
E 4
I 4
D 6
		gcp->gc_tx_desc_write_oo =
				MAXTXFRAGS == 1 && TX_BUF_SIZE == TX_RING_SIZE;
E 4
		gcp->gc_rx_buf_align = sizeof(uint8_t) - 1;
E 6
I 6
		gcp->gc_tx_desc_write_oo = B_TRUE;

		gcp->gc_rx_buf_align = sizeof (uint8_t) - 1;
E 6
		gcp->gc_rx_max_frags = 1;
		gcp->gc_rx_desc_unit_shift = 3;
		gcp->gc_rx_ring_size = RX_RING_SIZE;
D 4
		gcp->gc_rx_buf_max   = RX_BUF_SIZE;
E 4
I 4
D 6
		gcp->gc_rx_buf_max   = min(RX_RING_SIZE - 1, RX_BUF_SIZE);
E 4
		gcp->gc_rx_header_len= RX_HEAD_ROOM;
E 6
I 6
		gcp->gc_rx_buf_max = min(RX_RING_SIZE - 1, RX_BUF_SIZE);
		gcp->gc_rx_header_len = RX_HEAD_ROOM;
E 6
		gcp->gc_rx_copy_thresh = bfe_rx_copy_thresh;

		gcp->gc_io_area_size  = 0;

		/* map attributes */
D 4
		STRUCT_COPY(gcp->gc_dev_attr, bfe_dev_attr);
		STRUCT_COPY(gcp->gc_buf_attr, bfe_buf_attr);
		STRUCT_COPY(gcp->gc_desc_attr, bfe_dev_attr);
E 4
I 4
		gcp->gc_dev_attr = bfe_dev_attr;
		gcp->gc_buf_attr = bfe_buf_attr;
		gcp->gc_desc_attr = bfe_buf_attr;
E 4

		/* dma attributes */
D 4
		STRUCT_COPY(gcp->gc_dma_attr_desc, bfe_dma_attr_desc);
E 4
I 4
		gcp->gc_dma_attr_desc = bfe_dma_attr_desc;
E 4

D 4
		STRUCT_COPY(gcp->gc_dma_attr_txbuf, bfe_dma_attr_buf);
E 4
I 4
		gcp->gc_dma_attr_txbuf = bfe_dma_attr_buf;
E 4
D 6
		gcp->gc_dma_attr_txbuf.dma_attr_align  = gcp->gc_tx_buf_align+1;
E 6
I 6
		gcp->gc_dma_attr_txbuf.dma_attr_align = gcp->gc_tx_buf_align+1;
E 6
		gcp->gc_dma_attr_txbuf.dma_attr_sgllen = gcp->gc_tx_max_frags;

D 4
		STRUCT_COPY(gcp->gc_dma_attr_rxbuf, bfe_dma_attr_buf);
E 4
I 4
		gcp->gc_dma_attr_rxbuf = bfe_dma_attr_buf;
E 4
D 6
		gcp->gc_dma_attr_rxbuf.dma_attr_align  = gcp->gc_rx_buf_align+1;
E 6
I 6
		gcp->gc_dma_attr_rxbuf.dma_attr_align = gcp->gc_rx_buf_align+1;
E 6
		gcp->gc_dma_attr_rxbuf.dma_attr_sgllen = gcp->gc_rx_max_frags;

		/* time out parameters */
		gcp->gc_tx_timeout = 5*ONESEC;
		gcp->gc_tx_timeout_interval = ONESEC;

		/* flow control */
I 4
D 6
#ifndef CONFIG_FLOW_CONTROL
E 4
		/* XXX - dont use as it seems to cause tx performance problem */
D 4
		gcp->gc_flow_control = B_FALSE;

E 4
I 4
		gcp->gc_flow_control = FLOW_CONTROL_NONE;
#else
E 6
I 6
#ifdef TEST_RX_OVERFLOW
E 6
		/* XXX - test for rx overflow */
		gcp->gc_flow_control = FLOW_CONTROL_RX_PAUSE;
I 6
#else
		/* XXX - dont use as it seems to cause tx performance problem */
		gcp->gc_flow_control = FLOW_CONTROL_NONE;
E 6
#endif
E 4
		/* MII timeout parameters */
		gcp->gc_mii_link_watch_interval = ONESEC;
D 6
		gcp->gc_mii_an_watch_interval   = ONESEC/10;
		gcp->gc_mii_reset_timeout       = MII_RESET_TIMEOUT;
		gcp->gc_mii_an_timeout          = MII_AN_TIMEOUT;
		gcp->gc_mii_an_wait		= 0;
		gcp->gc_mii_linkdown_timeout    = MII_LINKDOWN_TIMEOUT; 
E 6
I 6
		gcp->gc_mii_an_watch_interval = ONESEC/10;
		gcp->gc_mii_reset_timeout = MII_RESET_TIMEOUT;
		gcp->gc_mii_an_timeout = MII_AN_TIMEOUT;
		gcp->gc_mii_an_wait = 0;
		gcp->gc_mii_linkdown_timeout = MII_LINKDOWN_TIMEOUT;
E 6

		/* workaround for PHY */
D 6
		gcp->gc_mii_an_delay	    = 0;
E 6
I 6
		gcp->gc_mii_an_delay = 0;
E 6
		gcp->gc_mii_linkdown_action = MII_ACTION_RESET;
		gcp->gc_mii_linkdown_timeout_action = MII_ACTION_RESET;
D 6
		gcp->gc_mii_dont_reset      = B_FALSE;
E 6
I 6
		gcp->gc_mii_dont_reset = B_FALSE;
E 6


		/* I/O methods */

		/* mac operation */
		gcp->gc_attach_chip = &bfe_attach_chip;
		gcp->gc_reset_chip = &bfe_reset_chip;
D 6
		gcp->gc_init_chip  = &bfe_init_chip;
E 6
I 6
		gcp->gc_init_chip = &bfe_init_chip;
E 6
		gcp->gc_start_chip = &bfe_start_chip;
D 6
		gcp->gc_stop_chip  = &bfe_stop_chip;
E 6
I 6
		gcp->gc_stop_chip = &bfe_stop_chip;
E 6
		gcp->gc_multicast_hash = NULL;
		gcp->gc_set_rx_filter = &bfe_set_rx_filter;
		gcp->gc_set_media = &bfe_set_media;
		gcp->gc_get_stats = &bfe_get_stats;
		gcp->gc_interrupt = &bfe_interrupt;

		/* descriptor operation */
		gcp->gc_tx_desc_write = &bfe_tx_desc_write;
D 6
		gcp->gc_tx_start      = &bfe_tx_start;
E 6
I 6
		gcp->gc_tx_start = &bfe_tx_start;
E 6
		gcp->gc_rx_desc_write = &bfe_rx_desc_write;
D 6
		gcp->gc_rx_start      = &bfe_rx_start;
E 6
I 6
		gcp->gc_rx_start = &bfe_rx_start;
E 6

D 6
		gcp->gc_tx_desc_stat  = &bfe_tx_desc_stat;
		gcp->gc_rx_desc_stat  = &bfe_rx_desc_stat;
		gcp->gc_tx_desc_init  = &bfe_tx_desc_init;
		gcp->gc_rx_desc_init  = &bfe_rx_desc_init;
E 6
I 6
		gcp->gc_tx_desc_stat = &bfe_tx_desc_stat;
		gcp->gc_rx_desc_stat = &bfe_rx_desc_stat;
		gcp->gc_tx_desc_init = &bfe_tx_desc_init;
		gcp->gc_rx_desc_init = &bfe_rx_desc_init;
E 6
		gcp->gc_tx_desc_clean = &bfe_tx_desc_init;
		gcp->gc_rx_desc_clean = &bfe_rx_desc_init;
D 6
		gcp->gc_get_packet    = &gem_get_packet_default;
E 6
I 6
		gcp->gc_get_packet = &gem_get_packet_default;
E 6

		/* mii operations */
D 5
		gcp->gc_mii_init   = &gem_mii_init_default;
E 5
I 5
D 6
		gcp->gc_mii_probe  = &gem_mii_probe_default;
		gcp->gc_mii_init   = NULL;
E 6
I 6
		gcp->gc_mii_probe = &gem_mii_probe_default;
		gcp->gc_mii_init = NULL;
E 6
E 5
		gcp->gc_mii_config = &bfe_mii_config;
D 6
		gcp->gc_mii_sync   = &bfe_mii_sync;
		gcp->gc_mii_read   = &bfe_mii_read;
		gcp->gc_mii_write  = &bfe_mii_write;
E 6
I 6
		gcp->gc_mii_sync = &bfe_mii_sync;
		gcp->gc_mii_read = &bfe_mii_read;
		gcp->gc_mii_write = &bfe_mii_write;
E 6
		gcp->gc_mii_tune_phy = NULL;

D 6
		lp = (struct bfe_dev *)
			kmem_zalloc(sizeof(struct bfe_dev), KM_SLEEP);
		lp->revid         = revid;
E 6
I 6
		lp = kmem_zalloc(sizeof (struct bfe_dev), KM_SLEEP);
		lp->revid  = revid;
E 6
		lp->need_to_reset = B_FALSE;
D 6
		lp->init_done     = B_FALSE;
E 6
I 6
		lp->init_done = B_FALSE;
E 6

D 5
		dp = gem_do_attach(dip, gcp, base, &regs_ha, lp, sizeof(*lp));
E 5
I 5
		dp = gem_do_attach(dip, 0,
D 6
				gcp, base, &regs_ha, lp, sizeof(*lp));
E 6
I 6
		    gcp, base, &regs_ha, lp, sizeof (*lp));
E 6
E 5

D 6
		kmem_free(gcp, sizeof(struct gem_conf));
E 6
I 6
		kmem_free(gcp, sizeof (struct gem_conf));
E 6

		if (dp != NULL) {
			return (DDI_SUCCESS);
		}
err_free_mem:
D 6
		kmem_free(lp, sizeof(struct bfe_dev));
E 6
I 6
		kmem_free(lp, sizeof (struct bfe_dev));
E 6
err:
		return (DDI_FAILURE);
	}
	return (DDI_FAILURE);
}

static int
bfedetach(dev_info_t *dip, ddi_detach_cmd_t cmd)
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
I 6
#ifdef GEM_CONFIG_GLDv3
DDI_DEFINE_STREAM_OPS(bfe_ops, nulldev, nulldev, bfeattach, bfedetach,
    nodev, NULL, D_MP, NULL);
#else
E 6
static	struct module_info bfeminfo = {
	0,			/* mi_idnum */
	"bfe",			/* mi_idname */
	0,			/* mi_minpsz */
D 4
	ETHERMTU,		/* mi_maxpsz */
	TX_BUF_SIZE*ETHERMAX,	/* mi_hiwat */
E 4
I 4
	INFPSZ,			/* mi_maxpsz */
	64*1024,		/* mi_hiwat */
E 4
	1,			/* mi_lowat */
};

static	struct qinit bferinit = {
	(int (*)()) NULL,	/* qi_putp */
	gem_rsrv,		/* qi_srvp */
	gem_open,		/* qi_qopen */
	gem_close,		/* qi_qclose */
	(int (*)()) NULL,	/* qi_qadmin */
	&bfeminfo,		/* qi_minfo */
	NULL			/* qi_mstat */
};

static	struct qinit bfewinit = {
	gem_wput,		/* qi_putp */
	gem_wsrv,		/* qi_srvp */
	(int (*)()) NULL,	/* qi_qopen */
	(int (*)()) NULL,	/* qi_qclose */
	(int (*)()) NULL,	/* qi_qadmin */
	&bfeminfo,		/* qi_minfo */
	NULL			/* qi_mstat */
};

static struct streamtab	bfe_info = {
	&bferinit,	/* st_rdinit */
	&bfewinit,	/* st_wrinit */
	NULL,		/* st_muxrinit */
	NULL		/* st_muxwrinit */
};

static	struct cb_ops cb_bfe_ops = {
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
	&bfe_info,	/* cb_stream */
	D_MP,		/* cb_flag */
D 6
#ifdef notdef
	CB_REV,		/* cb_rev */
	nodev,		/* cb_aread */
	nodev,		/* cb_awrite */
#endif
E 6
};

static	struct dev_ops bfe_ops = {
	DEVO_REV,	/* devo_rev */
	0,		/* devo_refcnt */
	gem_getinfo,	/* devo_getinfo */
	nulldev,	/* devo_identify */
	nulldev,	/* devo_probe */
	bfeattach,	/* devo_attach */
	bfedetach,	/* devo_detach */
	nodev,		/* devo_reset */
	&cb_bfe_ops,	/* devo_cb_ops */
	NULL,		/* devo_bus_ops */
	gem_power	/* devo_power */
};
I 6
#endif /* GEM_CONFIG_GLDv3 */
E 6

static struct modldrv modldrv = {
	&mod_driverops,	/* Type of module.  This one is a driver */
	ident,
	&bfe_ops,	/* driver ops */
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

	DPRINTF(2, (CE_CONT, "!bfe: _init: called"));
	gem_mod_init(&bfe_ops, "bfe");
	status = mod_install(&modlinkage);
	if (status != DDI_SUCCESS) {
		gem_mod_fini(&bfe_ops);
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

	DPRINTF(2, (CE_CONT, "!bfe: _fini: called"));
	status = mod_remove(&modlinkage);
	if (status == DDI_SUCCESS) {
		gem_mod_fini(&bfe_ops);
	}
	return (status);
}

int
_info(struct modinfo *modinfop)
{
	return (mod_info(&modlinkage, modinfop));
}
E 1
