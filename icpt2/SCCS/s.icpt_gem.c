h14864
s 00156/00120/01654
d D 1.5 07/09/22 20:50:56 mrym 5 4
c 2.6.0 cleanup
e
s 00009/00016/01765
d D 1.4 07/02/19 22:26:18 mrym 4 3
c 2.4.1
e
s 00150/00158/01631
d D 1.3 07/02/18 15:47:19 mrym 3 2
c 2.4.0
e
s 00120/00077/01669
d D 1.2 06/11/04 20:24:31 mrym 2 1
c gem 2.4.x framework
e
s 01746/00000/00000
d D 1.1 06/02/08 21:38:50 mrym 1 0
c date and time created 06/02/08 21:38:50 by mrym
e
u
U
f e 0
t
T
I 1
/*
 *  icpt: IC Plus IP1000A GbE MAC driver for Solaris
 *  %W% %E%
 *
D 3
 * Copyright (c) 2005, 2006 Masayuki Murayama.  All rights reserved.
E 3
I 3
 * Copyright (c) 2005-2007 Masayuki Murayama.  All rights reserved.
E 3
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
/*
 Change log
I 2
D 3
	03/20/2006	macro nests releated on USE_FRAMEID fixed
			it caused compile time error with old gcc version.
	11/04/2006	changes for gem 2.4.x framework
2.4.0
E 3
I 3
03/20/2006
	macro nests releated on USE_FRAMEID fixed
	it caused compile time error with old gcc version.
11/04/2006
	changes for gem 2.4.x framework

02/18/2007
	2.4.0 released
I 5
09/05/2007
	2.6.0
09/22/2007
	clean up
E 5
E 3
E 2
 */

/*
 TODO:
 */

/*
 * System Header files.
 */
#include <sys/types.h>
#include <sys/conf.h>
#include <sys/debug.h>
#include <sys/stropts.h>
#include <sys/stream.h>
#include <sys/strlog.h>
#include <sys/kmem.h>
#include <sys/stat.h>
#include <sys/kstat.h>
#include <sys/vtrace.h>
#include <sys/dlpi.h>
#include <sys/strsun.h>
#include <sys/ethernet.h>
#include <sys/modctl.h>
#include <sys/errno.h>
I 2
#include <sys/dditypes.h>
E 2
#include <sys/ddi.h>
#include <sys/sunddi.h>
I 5
#include <sys/byteorder.h>
E 5
D 2
#include <sys/ddi_impldefs.h>
E 2

#include <sys/pci.h>
D 5
#include "mii.h"
E 5
I 5
#include "gem_mii.h"
E 5
#include "gem.h"
#include "ip1000reg.h"

char	ident[] = "ip1000a nic driver v" VERSION;

/* Debugging support */
#ifdef DEBUG_LEVEL
static int icpt_debug = DEBUG_LEVEL;
#define	DPRINTF(n, args)	if (icpt_debug>(n)) cmn_err args
#else
#define	DPRINTF(n, args)
#endif

/*
 * Useful macros and typedefs
 */
D 3
#define	STRUCT_COPY(a, b)	bcopy(&(b), &(a), sizeof(a))
E 3
#define	OUTL_HI(dp, reg, val)	OUTW(dp, ((reg)+2), (((uint32_t)(val)) >> 16))
#define	OUTL_LOW(dp, reg, val)	OUTW(dp, reg, ((uint16_t)(val)))

D 5
#if defined(i86pc)
#define	LE64(x)	(x)
#else
#define	LE64(x)	ddi_swap64(x)
#endif

E 5
/*
D 3
 * IP1000A TFD and RFD structure
E 3
I 3
 * configuration on IP1000A TFD and RFD structures.
E 3
 */

#ifndef IPGE_MAXTXFRAGS
#  define	IPGE_MAXTXFRAGS	6
#endif

struct icpt_tfd {
	volatile uint64_t	TxDMANextPtr;
	volatile uint64_t	TxFrameControl;
#if IPGE_MAXTXFRAGS <= 2
	volatile uint64_t	TxDMAFrag[2];
#elif IPGE_MAXTXFRAGS <= 6
	volatile uint64_t	TxDMAFrag[6];
#else
# error IPGE_MAXTXFRAGS must be less than or equal to 6.
#endif
};

struct icpt_rfd {
	volatile uint64_t	RxDMANextPtr;
	volatile uint64_t	RxFrameStatus;
	volatile uint64_t 	RxDMAFrag;
D 3
	uint64_t	:64;		/* software padding for gem v2 */
E 3
I 3
D 5
	volatile uint64_t	pad;	/* software padding for gem v2 */
E 5
I 5
	uint64_t		pad;	/* for gem v2 */
E 5
E 3
};

struct icpt_dev {
	boolean_t	need_to_reset;
	boolean_t	tx_list_loaded;
	uint32_t	asic_ctrl;
	uint8_t		rev_id;
	uint16_t	intmask;
	uint32_t	countdown;
I 3
	int		rx_tail;
E 3
#ifdef USE_FRAMEID
	uint_t		frameid_tail;
#endif
#ifdef GEM_CONFIG_POLLING
	int		last_poll_interval;
#endif
#ifdef TEST_TXTIMEOUT
	int		send_cnt;
#endif
I 5
	uint8_t		mac_addr[ETHERADDRL];
E 5
};

/*
 * Our configuration
 */
#define	OUR_INTR_BITS \
	(INT_HostError | INT_TxComplete | INT_UpdateStats | \
D 3
	 INT_TxDMAComplete | INT_RxDMAComplete | INT_RFDListEnd)
E 3
I 3
	 INT_TxDMAComplete | INT_RxDMAComplete | INT_RFDListEnd | \
	 INT_LinkEvent)
E 3

#ifndef TX_RING_SIZE
# define TX_RING_SIZE	256
#endif
#ifndef TX_BUF_SIZE
# define TX_BUF_SIZE	TX_RING_SIZE
#endif

#ifndef RX_RING_SIZE
# define RX_RING_SIZE	64
#endif
#ifndef RX_BUF_SIZE
# define RX_BUF_SIZE	RX_RING_SIZE
#endif

#define	ONESEC			(drv_usectohz(1*1000000))

static int	icpt_tx_copy_thresh = 256;
static int	icpt_rx_copy_thresh = 256;

/*
 * Supported chips
 */
struct chip_info {
	uint16_t	venid;
	uint16_t	devid;
	char		*name;
};

static struct chip_info icpt_chiptbl[] = {
	{PCI_VID_DLINK,		0x4020,	"D-Link DL-2000"},
	{PCI_VID_SUNDANCE,	0x1023,	"IC Plus ip1000a"},
};
#define CHIPTABLESIZE   (sizeof(icpt_chiptbl)/sizeof(struct chip_info))

/* ======================================================== */
 
/* mii operations */
static void  icpt_mii_sync(struct gem_dev *);
static uint16_t icpt_mii_read(struct gem_dev *, uint_t);
D 3
static void icpt_mii_write_raw(struct gem_dev *, uint_t, uint16_t);
E 3
static void icpt_mii_write(struct gem_dev *, uint_t, uint16_t);

/* nic operations */
static int icpt_attach_chip(struct gem_dev *);
static int icpt_reset_chip(struct gem_dev *);
D 2
static void icpt_init_chip(struct gem_dev *);
static void icpt_start_chip(struct gem_dev *);
static void icpt_stop_chip(struct gem_dev *);
static void icpt_set_media(struct gem_dev *);
static void icpt_set_rx_filter(struct gem_dev *);
static void icpt_get_stats(struct gem_dev *);
E 2
I 2
static int icpt_init_chip(struct gem_dev *);
static int icpt_start_chip(struct gem_dev *);
static int icpt_stop_chip(struct gem_dev *);
static int icpt_set_media(struct gem_dev *);
static int icpt_set_rx_filter(struct gem_dev *);
static int icpt_get_stats(struct gem_dev *);
E 2

/* descriptor operations */
static int icpt_tx_desc_write(struct gem_dev *dp, int slot,
D 5
		    ddi_dma_cookie_t *dmacookie, int frags, uint32_t flag);
E 5
I 5
		    ddi_dma_cookie_t *dmacookie, int frags, uint64_t flag);
E 5
static void icpt_tx_start(struct gem_dev *dp, int slot, int nslot);
static void icpt_rx_desc_write(struct gem_dev *dp, int slot,
		    ddi_dma_cookie_t *dmacookie, int frags);
static uint_t icpt_tx_desc_stat(struct gem_dev *dp, int slot, int ndesc);
static uint64_t icpt_rx_desc_stat(struct gem_dev *dp, int slot, int ndesc);

static void icpt_tx_desc_init(struct gem_dev *dp, int slot);
static void icpt_rx_desc_init(struct gem_dev *dp, int slot);
static void icpt_tx_desc_clean(struct gem_dev *dp, int slot);
static void icpt_rx_desc_clean(struct gem_dev *dp, int slot);

/* interrupt handler */
static u_int icpt_interrupt(struct gem_dev *dp);

/* ======================================================== */

/* mapping attributes */
/* Data access requirements. */
static struct ddi_device_acc_attr icpt_dev_attr = {
	DDI_DEVICE_ATTR_V0,
	DDI_STRUCTURE_LE_ACC,
	DDI_STRICTORDER_ACC
};

/* On sparc, the buffers should be native endianness */
static struct ddi_device_acc_attr icpt_buf_attr = {
	DDI_DEVICE_ATTR_V0,
	DDI_NEVERSWAP_ACC,	/* native endianness */
	DDI_STRICTORDER_ACC
};

static ddi_dma_attr_t icpt_dma_attr_buf = {
	DMA_ATTR_V0,		/* dma_attr_version */
	0,			/* dma_attr_addr_lo */
	0x000000ffffffffffull,	/* dma_attr_addr_hi */
	0x000000000000ffffull,	/* dma_attr_count_max */
	1,			/* dma_attr_align */
	0x000007fc,		/* dma_attr_burstsizes */
	1,			/* dma_attr_minxfer */
	0x000000000000ffffull,	/* dma_attr_maxxfer */
	0x000000ffffffffffull,	/* dma_attr_seg */
	0,/* patched later */	/* dma_attr_sgllen */
	1,			/* dma_attr_granular */
	0			/* dma_attr_flags */
};

static ddi_dma_attr_t icpt_dma_attr_desc = {
	DMA_ATTR_V0,		/* dma_attr_version */
	64,			/* dma_attr_addr_lo */
	0x000000ffffffffffull,	/* dma_attr_addr_hi */
D 3
	0x000000000000ffffull,	/* dma_attr_count_max */
E 3
I 3
	0x00000000ffffffffull,	/* dma_attr_count_max */
E 3
	64,			/* dma_attr_align */
	0x000007fc,		/* dma_attr_burstsizes */
	1,			/* dma_attr_minxfer */
D 3
	0x000000000000ffffull,	/* dma_attr_maxxfer */
E 3
I 3
	0x00000000ffffffffull,	/* dma_attr_maxxfer */
E 3
	0x000000ffffffffffull,	/* dma_attr_seg */
	1,			/* dma_attr_sgllen */
	1,			/* dma_attr_granular */
	0			/* dma_attr_flags */
};

/* ======================================================== */
/*
 * HW manupilation routines
 */
/* ======================================================== */

static boolean_t
icpt_reset_asic(struct gem_dev *dp, uint32_t cmd, int timeo)
{
	struct icpt_dev	*lp = (struct icpt_dev *)dp->private;

	/* Reset the chip. */
	OUTL_HI(dp, AsicCtrl, cmd | lp->asic_ctrl);

D 5
	for (; (INL(dp, AsicCtrl) & AC_ResetBusy) != 0; timeo -= 10) {
E 5
I 5
	for (; (INL(dp, AsicCtrl) & AC_ResetBusy); timeo -= 10) {
E 5
		if (timeo < 0) {
D 2
			return B_FALSE;
E 2
I 2
			return (B_FALSE);
E 2
		}
		drv_usecwait(10);
	}

D 2
	return B_TRUE;
E 2
I 2
	return (B_TRUE);
E 2
}

static int
icpt_reset_chip(struct gem_dev *dp)
{
D 3
	struct icpt_dev	*lp = (struct icpt_dev *)dp->private;
E 3
I 3
	struct icpt_dev	*lp = (struct icpt_dev *) dp->private;
E 3
	uint32_t	cmd;

I 5
	bzero(lp->mac_addr, sizeof(lp->mac_addr));

E 5
	/* Disable all interrupts */
	OUTW(dp, IntEnable, lp->intmask = 0);

	/* Reset the chip. */
D 3
	cmd = AC_GlobalReset | AC_RxReset | AC_TxReset
		| AC_DMA | AC_FIFO | AC_Network | AC_Host;
#if 1
	cmd |= AC_AutoInit;
#endif
E 3
I 3
	cmd = AC_GlobalReset | AC_RxReset | AC_TxReset | AC_DMA
	    | AC_FIFO | AC_Network | AC_Host | AC_AutoInit;
E 3

	if (!lp->tx_list_loaded) {
D 3
		 /* This is first call after initialization. */
#if 0
		cmd |= AC_RstOut | AC_AutoInit;
#else
E 3
I 3
		 /* This is first call after initialization. Reset phy too. */
E 3
		cmd |= AC_RstOut;
D 3
#endif
E 3
	}

	if (!icpt_reset_asic(dp, cmd, 2000)) {
D 5
		cmn_err(CE_WARN, "%s: %s: timeout", dp->name, __func__);
E 5
I 5
		cmn_err(CE_WARN, "!%s: %s: timeout", dp->name, __func__);
E 5
D 2
		return -1;
E 2
I 2
		return (GEM_FAILURE);
E 2
	}

D 2
	return 0;
E 2
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
icpt_init_chip(struct gem_dev *dp)
{
	struct icpt_dev	*lp = (struct icpt_dev *)dp->private;

	DPRINTF(1, (CE_CONT, "!%s: %s: called", dp->name, __func__));

	ASSERT(mutex_owned(&dp->intrlock));
	ASSERT(lp->intmask == 0);

	/* tx list ptr */
	OUTL(dp, TFDListPtr + 0, 0);
	OUTL(dp, TFDListPtr + 4, 0);
	lp->tx_list_loaded = B_FALSE;

	/* rx list ptr */
	OUTL(dp, RFDListPtr + 0, 0);
	OUTL(dp, RFDListPtr + 4, 0);

	/* AsicCtrl : assume the chip stopped */
D 3
	DPRINTF(3, (CE_CONT, "!%s: AsicCtrl: %b", dp->name,
E 3
I 3
	DPRINTF(3, (CE_CONT, "!%s: %s: AsicCtrl: %b", dp->name, __func__,
E 3
		INL(dp, AsicCtrl), AC_BITS));

D 3
	/* keep LED control bits and non write-clear bits */
E 3
I 3
	/* keep LED control bits and rd/wr bits */
E 3
	lp->asic_ctrl =
		(lp->asic_ctrl & 0xffff0000) | (INL(dp, AsicCtrl) & 0xffff);
	OUTL(dp, AsicCtrl, lp->asic_ctrl);

	/* MACCtrl: */
	DPRINTF(3, (CE_CONT, "!%s %s called, mc: %b",
		dp->name, __func__, INL(dp, MACCtrl), MC_BITS));

	/* Ensure all functions are disabled */
	OUTL_HI(dp, MACCtrl,
			MC_StatisticsDisable | MC_TxDisable | MC_RxDisable);
#ifdef	CONFIG_RCV_FCS
	OUTL_LOW(dp, MACCtrl, MC_RcvFCS | MC_IFSSelect802_3);
#else
	OUTL_LOW(dp, MACCtrl, MC_IFSSelect802_3);
#endif

#define	RxFIFOSIZE	(32*1024)			/* 32Kbyte */
#define	RxFIFO_HIWAT	(RxFIFOSIZE*16/32)		/* 16Kbyte */
#define	RxFIFO_LOWAT	(RxFIFOSIZE*1/32)		/*  1Kbyte */

	OUTW(dp, MaxFrameSize, dp->mtu + sizeof(struct ether_header));
	OUTW(dp, RxEarlyThresh, RxEarlyThreshMax);
I 4

E 4
	OUTW(dp, TxStartThresh,
D 4
		min(dp->txthr / TxStartThreshUnit, TxStartThreshMax));
E 4
I 4
		min((dp->txthr + 4) / TxStartThreshUnit, TxStartThreshMax));
E 4

D 3
	/* disable rx hardware coaleasing */
	OUTL(dp, RxDMAIntCtrl, RIC_PriorityThresh | 1);
E 3
I 3
	/* disable hardware rx interrupt coaleasing */
	OUTL(dp, RxDMAIntCtrl, RIC_RxDMAWaitTime | RIC_PriorityThreshMax | 1);
E 3

	OUTB(dp, RxDMAPollPeriod, RxDMAPollPeriodMin);
	OUTB(dp, RxDMAUrgentThresh,
		max(min((RxFIFOSIZE - RxFIFO_HIWAT) / RxDMAUrgentThreshUnit,
			RxDMAUrgentThreshMax), RxDMAUrgentThreshMin));
	OUTB(dp, RxDMABurstThresh,
		max(min(dp->rxthr / RxDMABurstThreshUnit,
			RxDMABurstThreshMax), RxDMABurstThreshMin));

D 4
#ifdef TXUNDERRUNTEST
	dp->txmaxdma = min(256, dp->txthr);
#endif
E 4
	OUTB(dp, TxDMAPollPeriod, TxDMAPollPeriodMax); /* 81.6 uS */

D 4
	/* TxDMAUrgentThreash : half of TxStartThresh */
E 4
I 4
	/* TxDMAUrgentThreash : 1/16 of TxStartThresh */
E 4
	OUTB(dp, TxDMAUrgentThresh,
D 4
		max(min((dp->txthr / 2) / TxDMAUrgentThreshUnit,
E 4
I 4
		max(min((dp->txthr / 16) / TxDMAUrgentThreshUnit,
E 4
			TxDMAUrgentThreshMax), TxDMAUrgentThreshMin));
I 4

E 4
	OUTB(dp, TxDMABurstThresh,
		max(min(dp->txmaxdma / TxDMABurstThreshUnit,
			TxDMABurstThreshMax), TxDMABurstThreshMin));

	/* DMACtrl: */
#ifdef USE_FRAMEID
	OUTL_LOW(dp, DMACtrl, DC_TxWriteBackDisable | DC_TxBurstLimitMax);
#else
	OUTL_LOW(dp, DMACtrl, DC_TxBurstLimitMax);
#endif

	/* Tx flow control threshold */
	OUTW(dp, FlowOnThresh, RxFIFO_HIWAT / FlowThreshUnit);
	OUTW(dp, FlowOffThresh, RxFIFO_LOWAT / FlowThreshUnit);

	/* DebugCtrl: workarounds */
	OUTW(dp, DebugCtrl, 0x0200 | INL(dp, DebugCtrl));
	OUTW(dp, DebugCtrl, 0x0010 | INL(dp, DebugCtrl));
	OUTW(dp, DebugCtrl, 0x0020 | INL(dp, DebugCtrl));

	/* XXX - clear Countdown timer */
#if 0
	DPRINTF(0, (CE_CONT, "!%s: Countdown: 0x%x",
		dp->name, INL(dp, Countdown)));
	OUTL(dp, Countdown, 0);
#endif
	/* Setup statistics masks */
	OUTL(dp, RMONStatisticsMask, 0);
	OUTL(dp, StatisticsMask, 0);
#ifdef USE_FRAMEID
	lp->frameid_tail = 0;
#endif
I 3
	lp->rx_tail = 0;
D 5

E 5
I 5
#if 0 /* debug */
	OUTL(dp, ReceiveMode, RM_ReceiveAllFrames);
#endif
E 5
E 3
	DPRINTF(2, (CE_CONT, "!%s: %s: mc: %b, ac: %b",
		dp->name, __func__,
		INL(dp, MACCtrl), MC_BITS, INL(dp, AsicCtrl), AC_BITS));
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
icpt_start_chip(struct gem_dev *dp)
{
	struct icpt_dev	*lp = (struct icpt_dev *)dp->private;

	ASSERT(mutex_owned(&dp->intrlock));

	/* Enable statistics */
	OUTL_HI(dp, MACCtrl, MC_StatisticsEnable);
D 5

E 5
I 5
#if 0
E 5
	/* Set media mode */
	icpt_set_media(dp);
D 5

E 5
I 5
#endif
E 5
	ASSERT((dp->rx_ring_dma & 7) == 0);
	OUTL(dp, RFDListPtr + 0, (uint32_t) dp->rx_ring_dma);
	OUTL(dp, RFDListPtr + 4, (uint32_t) (dp->rx_ring_dma >> 32));

	/* Enable transmitter and receiver */
	OUTL_HI(dp, MACCtrl, MC_TxEnable | MC_RxEnable);

	/* Set InterruptMask */
	lp->intmask = OUR_INTR_BITS;

	if ((dp->misc_flag & GEM_NOINTR) == 0) {
		OUTW(dp, IntEnable, lp->intmask);
	}

	DPRINTF(0, (CE_CONT, "!%s: %s: mc: %b",
		dp->name, __func__, INL(dp, MACCtrl), MC_BITS));
	DPRINTF(0, (CE_CONT, "!%s: %s: dmactrl: %b",
		dp->name, __func__, INL(dp, DMACtrl), DC_BITS));
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
icpt_stop_chip(struct gem_dev *dp)
{
	int		i;
	struct icpt_dev	*lp = (struct icpt_dev *)dp->private;

	DPRINTF(1, (CE_CONT, "!%s: icpt_stop_chip: called", dp->name));

	/* inhibit interrupt */
	OUTW(dp, IntEnable, lp->intmask = 0);

	/* no more statistics */
	OUTL_HI(dp, MACCtrl, MC_StatisticsDisable);

	/* stop receiver and transceiver */
	OUTL_HI(dp, MACCtrl, MC_RxDisable | MC_TxDisable);
D 2
	drv_usecwait(1000);
E 2
I 2
	drv_usecwait(2000);
E 2

	/* reset DMA pointers */
	if (!icpt_reset_asic(dp, AC_RxReset | AC_TxReset | AC_DMA, 2000)) {
D 5
		cmn_err(CE_WARN, "%s: %s: timeout: resetting tx/rx",
E 5
I 5
		cmn_err(CE_WARN, "!%s: %s: timeout: resetting tx/rx",
E 5
			dp->name, __func__);
	}
I 2

	return (GEM_SUCCESS);
E 2
}

static uint16_t
icpt_read_eeprom(struct gem_dev *dp, uint_t offset)
{
	int		i;

	OUTW(dp, EepromCtrl, EEC_OpcodeRd | (offset & EEC_Address));
	drv_usecwait(100);

D 5
	for (i = 0; (INW(dp, EepromCtrl) & EEC_Busy) != 0; i++) {
E 5
I 5
	for (i = 0; (INW(dp, EepromCtrl) & EEC_Busy); i++) {
E 5
		if (i > 30) {
D 3
			cmn_err(CE_WARN, "%s: %s: timeout", dp->name, __func__);
E 3
I 3
			cmn_err(CE_WARN,
D 5
				"%s: %s: timeout", dp->name, __func__);
E 5
I 5
				"!%s: %s: timeout", dp->name, __func__);
E 5
E 3
D 2
			return 0xffff;
E 2
I 2
			return (0xffff);
E 2
		}
		drv_usecwait(10);
	}

D 5
	DPRINTF(4, (CE_CONT, "%s: %s: took %d uS", dp->name, __func__, i*10));
E 5
I 5
	DPRINTF(4, (CE_CONT, "!%s: %s: took %d uS", dp->name, __func__, i*10));
E 5

D 2
	return INW(dp, EepromData);
E 2
I 2
	return (INW(dp, EepromData));
E 2
}

#ifdef DEBUG_LEVEL
static void
icpt_eeprom_dump(struct gem_dev *dp)
{
	int		i;
	uint16_t	prom[0x14];

	for (i = 0; i < 0x14; i++) {
		prom[i] = icpt_read_eeprom(dp, i);
	}

	cmn_err(CE_CONT, "!%s: eeprom dump:", dp->name);
	for (i = 0; i < 0x14; i += 4) {
		cmn_err(CE_CONT, "!0x%02x: 0x%04x 0x%04x 0x%04x 0x%04x", 
			i, prom[i], prom[i + 1], prom[i + 2], prom[i + 3]);
	}
}
#endif /* DEBUG_LEVEL */

static int
icpt_attach_chip(struct gem_dev *dp)	
{
	int		i;
	uint_t		val;
	struct icpt_dev	*lp = (struct icpt_dev *)dp->private;

	for (i = 0; i < ETHERADDRL; i += 2) {
		val = icpt_read_eeprom(dp, 0x10 + i/2);

		dp->dev_addr.ether_addr_octet[i + 0] = (uint8_t) val;
		dp->dev_addr.ether_addr_octet[i + 1] = (uint8_t) (val >> 8);

		OUTW(dp, StationAddress + i, val);
	}

	/* setup LED control bits in offset 6 of AsicCtrl */
	lp->asic_ctrl = 0;
	val = icpt_read_eeprom(dp, 6);
D 5
	if ((val & 0x01) != 0) {
E 5
I 5
	if (val & 0x01) {
E 5
		lp->asic_ctrl |= AC_LEDMode;
	}
D 5
	if ((val & 0x02) != 0) {
E 5
I 5
	if (val & 0x02) {
E 5
		lp->asic_ctrl |= AC_LEDMode1;
	}
D 5
	if ((val & 0x08) != 0) {
E 5
I 5
	if (val & 0x08) {
E 5
		lp->asic_ctrl |= AC_LEDSpeed;
	}

#if DEBUG_LEVEL > 4
	icpt_eeprom_dump(dp);
#endif

	/* Minimum burst size is 256 byte */
	dp->txmaxdma = max(dp->txmaxdma,
				TxDMABurstThreshMin * TxDMABurstThreshUnit);
	dp->rxthr = dp->rxmaxdma =
		max(max(dp->rxmaxdma, dp->rxthr),
				RxDMABurstThreshMin * RxDMABurstThreshUnit);
I 4
#ifdef TXUNDERRUNTEST
	dp->txthr = min(256, dp->txthr);
#endif
E 4
I 2
#ifdef CONFIG_VLAN
        dp->misc_flag |= GEM_VLAN_SOFT;
#endif
E 2
#ifdef GEM_CONFIG_CKSUM_OFFLOAD
D 2
        dp->misc_flag |= GEM_CKSUM_IPv4 | GEM_CKSUM_TCP | GEM_CKSUM_UDP;
E 2
I 2
        dp->misc_flag |= (GEM_CKSUM_FULL_IPv4 | GEM_CKSUM_HEADER_IPv4);
E 2
#endif
D 2
	return 0;
E 2
I 2
	return (GEM_SUCCESS);
E 2
}

static uint32_t
icpt_mcast_hash(struct gem_dev *dp, uint8_t *addr)
{
D 2
	return gem_ether_crc_be(addr, ETHERADDRL);
E 2
I 2
	return (gem_ether_crc_be(addr, ETHERADDRL));
E 2
}

D 2
static void
E 2
I 2
static int
E 2
icpt_set_rx_filter(struct gem_dev *dp)	
{
	int		i;
	uint16_t	mode;
	uint8_t		*mac;
	uint32_t	mhash[2];
I 5
	struct icpt_dev	*lp = (struct icpt_dev *)dp->private;
E 5

	ASSERT(mutex_owned(&dp->intrlock));
	bzero(mhash, sizeof(mhash));

D 3
	if ((dp->rxmode & RXMODE_PROMISC) != 0) {
E 3
I 3
	if ((dp->rxmode & RXMODE_ENABLE) == 0) {
		mode = 0;
	}
D 5
	else if ((dp->rxmode & RXMODE_PROMISC) != 0) {
E 5
I 5
	else if (dp->rxmode & RXMODE_PROMISC) {
E 5
E 3
		/* promiscous */
		mode = RM_ReceiveAllFrames;
	}
D 5
	else if ((dp->rxmode & RXMODE_ALLMULTI) != 0 || dp->mc_count > 32) {
E 5
I 5
	else if ((dp->rxmode & RXMODE_ALLMULTI) || dp->mc_count > 32) {
E 5
		mode = RM_ReceiveUnicast
		     | RM_ReceiveBroadcast
		     | RM_ReceiveMulticast;
	}
	else {
		/* Normal mode */
		mode = RM_ReceiveUnicast | RM_ReceiveBroadcast;
		if (dp->mc_count > 0) {
			mode |= RM_ReceiveMulticastHash;
		}

		/* Make multicast hash table */
		for (i = 0; i < dp->mc_count; i++) {
			uint_t	k;
			/* hash key is 6 bits of LSB in be-crc */
			k = dp->mc_list[i].hash & ((1 << 6) - 1);
			mhash[k / 32] |= 1 << (k % 32);
		}
	}

	/* set rx mode */
	DPRINTF(2, (CE_CONT, "!%s: %s: setting rx mode: 0x%b",
		dp->name, __func__, mode, RM_BITS));

D 5
	/* stop rx temporary */
E 5
D 2
	if (dp->nic_active) {
E 2
I 2
	if (dp->mac_active) {
I 3
D 4
#if 0
E 3
E 2
		OUTL_HI(dp, MACCtrl, MC_RxDisable);
I 3
#else
E 4
D 5
		OUTW(dp, ReceiveMode, (mode != 0) ? RM_ReceiveAllFrames : 0);
E 5
I 5
		OUTW(dp, ReceiveMode, mode ? RM_ReceiveAllFrames : 0);
E 5
D 4
#endif
E 4
E 3
	}

D 3
	OUTW(dp, ReceiveMode, mode);

E 3
D 5
	if ((mode & RM_ReceiveMulticastHash) != 0) {
E 5
I 5
	if (mode & RM_ReceiveMulticastHash) {
E 5
		/* set multicast hash table up */
		for (i = 0; i < sizeof(mhash)/sizeof(uint32_t); i++) {
			OUTL(dp, HashTable + i*sizeof(uint32_t), mhash[i]);
		}
	}

D 5
	/* set station address */
E 5
	mac = dp->cur_addr.ether_addr_octet;
D 5
	for (i = 0; i < ETHERADDRL; i += 2) {
		OUTW(dp, StationAddress + i, (mac[i + 1] << 8) | mac[i]);
E 5
I 5
	if (bcmp(mac, lp->mac_addr, ETHERADDRL)) {
		/* set station address */
		for (i = 0; i < ETHERADDRL; i += 2) {
			OUTW(dp, StationAddress + i,
					(mac[i + 1] << 8) | mac[i]);
		}
		bcopy(mac, lp->mac_addr, ETHERADDRL);
E 5
	}

I 3
	OUTW(dp, ReceiveMode, mode);
D 4
#if 0
E 3
	/* enable rx again */
D 2
	if (dp->nic_active) {
E 2
I 2
	if (dp->mac_active) {
E 2
		OUTL_HI(dp, MACCtrl, MC_RxEnable);
	}
I 2
D 3

E 3
I 3
#endif
E 4
I 4

E 4
E 3
	return (GEM_SUCCESS);
E 2
}

D 2
static void
E 2
I 2
static int
E 2
icpt_set_media(struct gem_dev *dp)
{
	uint16_t	old;
	uint16_t	new;
	int		i;
	struct icpt_dev	*lp = (struct icpt_dev *)dp->private;

	ASSERT(mutex_owned(&dp->intrlock));
D 2
#ifdef notdef
	if (!dp->nic_active) {
		return;
	}
#endif
E 2
I 2

E 2
	/*
	 * Notify current duplex mode to MAC
	 */
	old = INW(dp, MACCtrl);
	new = old & ~(MC_DuplexSelect |
		      MC_TxFlowControlEnable | MC_RxFlowControlEnable);

	if (dp->full_duplex) {
		new |= MC_DuplexSelect;

		switch (dp->flow_control) {
		case FLOW_CONTROL_SYMMETRIC:
			new |= MC_TxFlowControlEnable | MC_RxFlowControlEnable;
			break;

		case FLOW_CONTROL_TX_PAUSE:
			new |= MC_TxFlowControlEnable;
			break;

		case FLOW_CONTROL_RX_PAUSE:
			new |= MC_RxFlowControlEnable;
			break;
		}
	}

	if (old != new) {
		OUTL_LOW(dp, MACCtrl, new);
	}

D 5
	if (((old ^ new) & MC_DuplexSelect) != 0) {
E 5
I 5
	if ((old ^ new) & MC_DuplexSelect) {
E 5
		/*
		 * Duplex mode was changed. Need to reset Tx/Rx.
		 */
		DPRINTF(1, (CE_CONT,
			"!%s: %s: resetting tx and rx to change duplex mode",
			dp->name, __func__));

		if (!icpt_reset_asic(dp, AC_TxReset | AC_RxReset, 2000)) {
			/* Time out */
D 5
			cmn_err(CE_WARN, "%s: %s: timeout: resetting tx/rx",
E 5
I 5
			cmn_err(CE_WARN, "!%s: %s: timeout: resetting tx/rx",
E 5
				dp->name, __func__);
		}

		OUTL_HI(dp, MACCtrl, MC_TxEnable | MC_RxEnable);
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
icpt_get_stats(struct gem_dev *dp)
{
	int		first_coll;
	int		multi_coll;
	int		c;
	int		l;
	volatile int	x;

	DPRINTF(4, (CE_CONT, "!%s: icpt_get_stats: called", dp->name));
D 3
#ifdef notdef
E 3
I 3
#ifdef NEVER
E 3
	ASSERT(mutex_owned(&dp->intrlock));
#endif
	OUTL_HI(dp, MACCtrl, MC_StatisticsDisable);

				x= INL(dp, OctetRcvdOk);
				x= INL(dp, McstOctetRcvdOk);
				x= INL(dp, BcstOctetRcvdOk);
				x= INL(dp, FramesRcvdOk);
				x= INL(dp, McstFramesRcvdOk);

				x= INW(dp, BcstFramesRcvdOk);
				x= INW(dp, MacControlFramesRcvd);
				x= INW(dp, FrameTooLongErrors);
				x= INW(dp, InRangeLengthErrors);
				x= INW(dp, FramesCheckSeqErrors);
	dp->stats.missed        += INW(dp, FramesLostRxErrors);

				x= INL(dp, OctetXmtOk);
				x= INL(dp, McstOctetXmtOk);
				x= INL(dp, BcstOctetXmtOk);
				x= INL(dp, FramesXmtdOk);
				x= INL(dp, McstFramesXmtdOk);
	dp->stats.defer         += INL(dp, FramesWDeferredXmt);
	dp->stats.xmtlatecoll += l = INL(dp, LateCollisions);
	multi_coll               = INL(dp, MultiColFrames);
	first_coll               = INL(dp, SingleColFrames);

				x= INW(dp, BcstFramesXmtdOk);
	dp->stats.nocarrier += c = INW(dp, CarrierSenseErrors);
				x= INW(dp, MacControlFramesXmtd);
				x= INW(dp, FramesAbortXSColls);
				x= INW(dp, FramesWEXDeferral);

	dp->stats.multi_coll    += multi_coll;
	dp->stats.first_coll    += first_coll;

	/*
	 * Guess total collisions
	 */
	dp->stats.collisions += first_coll + multi_coll*2;

	dp->stats.errxmt += c + l;

	OUTL_HI(dp, MACCtrl, MC_StatisticsEnable);
I 2

	return (GEM_SUCCESS);
E 2
}

/*
 * discriptor  manupiration
 */
static int
icpt_tx_desc_write(struct gem_dev *dp, int slot,
D 5
		ddi_dma_cookie_t *dmacookie, int frags, uint32_t flag)
E 5
I 5
		ddi_dma_cookie_t *dmacookie, int frags, uint64_t flag)
E 5
{
	int			i;
I 2
	uint64_t		mark;
	uint64_t		vtag;
E 2
	struct icpt_tfd		*tfdp;
D 2
	uint64_t		tfd_dma;
E 2
	struct icpt_dev	*lp = (struct icpt_dev *)dp->private;

#if DEBUG_LEVEL > 2
	/* force to cause interrupt upon tx completion */
	flag |= GEM_TXFLAG_INTR;
#endif
D 3
	tfdp = &((struct icpt_tfd *)dp->tx_ring)[slot];
E 3
I 3
	tfdp = &((struct icpt_tfd *) dp->tx_ring)[slot];
E 3

#if DEBUG_LEVEL > 2
	cmn_err(CE_CONT,
D 5
		"%s: %s: seqnum: %d, slot %d, frags: %d flag: %d",
E 5
I 5
		"!%s: %s: seqnum: %d, slot %d, frags: %d flag: %llx",
E 5
		dp->name, __func__, dp->tx_desc_tail, slot, frags, flag);

	for (i = 0; i < frags; i++) {
D 5
		cmn_err(CE_CONT, "%d: addr: 0x%x, len: 0x%x",
E 5
I 5
		cmn_err(CE_CONT, "!%d: addr: 0x%x, len: 0x%x",
E 5
			i, dmacookie[i].dmac_address, dmacookie[i].dmac_size);
	}
#endif
D 3
	tfdp->TxDMANextPtr = 0ULL;
					/* means this is the last descriptor */
E 3
I 3
	tfdp->TxDMANextPtr = dp->tx_ring_dma +
			sizeof(struct icpt_tfd) * SLOT(i + 1, TX_RING_SIZE);

E 3
	/* make fragment list */
	for (i = 0; i < frags; i++) {
D 5
		tfdp->TxDMAFrag[i] = LE64(
E 5
I 5
		tfdp->TxDMAFrag[i] = LE_64(
E 5
D 2
		    ((uint64_t) dmacookie[i].dmac_size << TFI_FragLenShift) |
		    dmacookie[i].dmac_address);
E 2
I 2
		    (((uint64_t) dmacookie[i].dmac_size) << TFI_FragLenShift) |
		    dmacookie[i].dmac_laddress);
E 2
	}

D 2
	tfdp->TxFrameControl = LE64(
		(((uint64_t) frags) << TFC_FragCountShift) |
E 2
I 2
	mark = (uint64_t) slot
	     | (((uint64_t) frags) << TFC_FragCountShift)
	     | TFC_WordAlignDisable;

D 5
	if ((flag & GEM_TXFLAG_INTR) != 0) {
E 5
I 5
	if (flag & GEM_TXFLAG_INTR) {
E 5
E 2
#ifdef USE_FRAMEID
D 2
		((flag & GEM_TXFLAG_INTR) != 0 ? TFC_TxIndicate : 0) |
		(uint64_t) slot |
E 2
I 2
		mark |= TFC_TxIndicate;
E 2
#else
D 2
		((flag & GEM_TXFLAG_INTR) != 0 ? TFC_TxDMAIndicate : 0) |
E 2
I 2
		mark |= TFC_TxDMAIndicate;
E 2
#endif
#ifdef TEST_CRCERR
D 2
		((flag & GEM_TXFLAG_INTR) != 0 ? TFC_FcsAppendDisable : 0) |
E 2
I 2
		mark |= TFC_FcsAppendDisable;
E 2
#endif
D 2
		(((flag & GEM_TXFLAG_VTAG) == 0) ? 0 :
			((((uint64_t) (flag & GEM_TXFLAG_VTAG)) <<
				(TFC_VTAGShift - GEM_TXFLAG_VTAG_SHIFT)) |
			 TFC_VLANTagInsert)) |
		((flag & (GEM_TXFLAG_IPv4 | GEM_TXFLAG_UDP | GEM_TXFLAG_TCP))
			<< (TFC_IPCksumEnShift - GEM_TXFLAG_IPv4_SHIFT)) |
		TFC_WordAlignDisable);
E 2
I 2
	}
E 2

D 2
	return 1;
E 2
I 2
#ifdef CONFIG_VLAN
	/* XXX - it's funny */
D 5
	if ((vtag = ((flag & GEM_TXFLAG_VTAG) >> GEM_TXFLAG_VTAG_SHIFT)) != 0) {
E 5
I 5
	if (vtag = ((flag & GEM_TXFLAG_VTAG) >> GEM_TXFLAG_VTAG_SHIFT)) {
E 5
		mark |= TFC_VLANTagInsert | (vtag << 32);
	}
#endif

#ifdef GEM_CONFIG_CKSUM_OFFLOAD
D 5
	if ((flag & GEM_TXFLAG_IPv4) != 0) {
E 5
I 5
	if (flag & GEM_TXFLAG_IPv4) {
E 5
		mark |= TFC_IPCksumEn;
	}
D 5
	if ((flag & GEM_TXFLAG_TCP) != 0) {
E 5
I 5
	if (flag & GEM_TXFLAG_TCP) {
E 5
		mark |= TFC_TCPCksumEn;
	}
D 5
	else if ((flag & GEM_TXFLAG_UDP) != 0) {
E 5
I 5
	else if (flag & GEM_TXFLAG_UDP) {
E 5
		mark |= TFC_UDPCksumEn;
	}
#endif
D 5
	tfdp->TxFrameControl = LE64(mark);
E 5
I 5
	tfdp->TxFrameControl = LE_64(mark);
E 5

	return (1);
E 2
}

static void
icpt_tx_start(struct gem_dev *dp, int start_slot, int nslot)
{
D 3
	int			i;
	int			slot;
	uint64_t		tfd_dma;
	struct icpt_tfd		*tfdp;
E 3
I 3
	int		last;
	uint64_t	tfd_dma;
E 3
	struct icpt_dev	*lp = (struct icpt_dev *)dp->private;

D 3
	for (i = start_slot + nslot - 1 ; i-- != start_slot; ) {
		/* make tx list */
		slot = SLOT(i + 1, TX_RING_SIZE);
		tfd_dma = dp->tx_ring_dma + sizeof(struct icpt_tfd) * slot;
		ASSERT((tfd_dma & 7) == 0);
E 3
I 3
	/* write zero into  NextPtr in the last slot to terminate tx list */
	last = SLOT(start_slot + nslot - 1, TX_RING_SIZE);
	((struct icpt_tfd *) dp->tx_ring) [last].TxDMANextPtr = 0ULL;
E 3

D 3
		tfdp = &((struct icpt_tfd *)dp->tx_ring)[SLOT(i, TX_RING_SIZE)];
		tfdp->TxDMANextPtr = LE64(tfd_dma);
	}

E 3
	/* flush tx descriptors we have made */
	gem_tx_desc_dma_sync(dp, start_slot, nslot, DDI_DMA_SYNC_FORDEV);

#ifdef TEST_TXTIMEOUT
	if ((lp->send_cnt++ % 10000) == 9999) {
		OUTL_HI(dp, MACCtrl, MC_TxDisable);
	}
#endif
	tfd_dma = dp->tx_ring_dma + sizeof(struct icpt_tfd) * start_slot;

	if (lp->tx_list_loaded)  {
		/*
		 * Link this to the previous slot. The previous isn't in use,
D 3
		 * because number of tx buffers is smaller than the number of
		 * tx descriptors.
E 3
I 3
		 * because the number of tx buffers is smaller than the
		 * number of tx descriptors.
E 3
		 */
D 3
		slot = SLOT(start_slot - 1, TX_RING_SIZE);
		tfdp = &((struct icpt_tfd *)dp->tx_ring)[slot];
		tfdp->TxDMANextPtr = LE64(tfd_dma);
E 3
I 3
		last = SLOT(start_slot - 1, TX_RING_SIZE);
		((struct icpt_tfd *)dp->tx_ring)[
D 5
				last].TxDMANextPtr = LE64(tfd_dma);
E 5
I 5
				last].TxDMANextPtr = LE_64(tfd_dma);
E 5
E 3

		/* flush tx descriptors we have made */
D 3
		gem_tx_desc_dma_sync(dp, slot, 1, DDI_DMA_SYNC_FORDEV);
E 3
I 3
		gem_tx_desc_dma_sync(dp, last, 1, DDI_DMA_SYNC_FORDEV);
E 3

		/* Make the nic poll tx immediately */
#ifdef GEM_CONFIG_POLLING
		if (dp->poll_interval == 0)
#endif
		{
			/* kick tx engine right now */
D 2
			OUTL_LOW(dp, DMACtrl,
E 2
#ifdef USE_FRAMEID
I 2
			OUTL_LOW(dp, DMACtrl,
E 2
				DC_TxWriteBackDisable |
D 2
#endif
E 2
				DC_TxBurstLimitMax | DC_TxDMAPollNow);
I 2
#else
			OUTL_LOW(dp, DMACtrl,
				DC_TxBurstLimitMax | DC_TxDMAPollNow);
#endif
E 2
		}
	}
	else {
		/*
		 * This is first call after initialization.
		 * Need to tell the head of tx list to the nic.
		 */
		OUTL_LOW(dp, DMACtrl, DC_TxBurstLimitMax);

		OUTL(dp, TFDListPtr + 0, (uint32_t) tfd_dma);
		OUTL(dp, TFDListPtr + 4, (uint32_t) (tfd_dma >> 32));
		lp->tx_list_loaded = B_TRUE;
	}
}

static void
icpt_rx_desc_write(struct gem_dev *dp, int slot,
	    ddi_dma_cookie_t *dmacookie, int frags)
{
D 3
	int			i;
	struct icpt_rfd		*rfdp;
E 3
I 3
	int		i;
	struct icpt_rfd	*rfdp;
	struct icpt_dev	*lp = (struct icpt_dev *) dp->private;
E 3

	rfdp = &((struct icpt_rfd *)dp->rx_ring)[slot];

#if DEBUG_LEVEL > 2
D 5
	cmn_err(CE_CONT, "%s: %s seqnum: %d, slot %d, frags: %d",
E 5
I 5
	cmn_err(CE_CONT, "!%s: %s seqnum: %d, slot %d, frags: %d",
E 5
		dp->name, __func__, dp->rx_active_tail, slot, frags);
	for (i = 0; i < frags; i++) {
D 5
		cmn_err(CE_CONT, "  frag: %d addr: 0x%x, len: 0x%x",
E 5
I 5
		cmn_err(CE_CONT, "!  frag: %d addr: 0x%x, len: 0x%x",
E 5
			i, dmacookie[i].dmac_address, dmacookie[i].dmac_size);
	}
#endif
	ASSERT(frags == 1);

D 5
	rfdp->RxDMAFrag = LE64(
E 5
I 5
	rfdp->RxDMAFrag = LE_64(
E 5
		(((uint64_t) dmacookie->dmac_size) << RFI_FragLenShift) |
		dmacookie->dmac_address);

D 3
	rfdp->RxFrameStatus = 0ULL;
E 3
I 3
	if (slot != lp->rx_tail) {
		rfdp->RxFrameStatus = 0ULL;
	}
E 3
}

I 3
static void
icpt_rx_start(struct gem_dev *dp, int start_slot, int nslot)
{
	struct icpt_dev	*lp = (struct icpt_dev *) dp->private;

	if (nslot > 1) {
		gem_rx_desc_dma_sync(dp, SLOT(start_slot + 1, RX_RING_SIZE),
				nslot, DDI_DMA_SYNC_FORDEV);
	}

	((struct icpt_rfd *)
		dp->rx_ring)[start_slot].RxFrameStatus = 0ULL;

	gem_rx_desc_dma_sync(dp, start_slot, 1, DDI_DMA_SYNC_FORDEV);

	lp->rx_tail = start_slot + nslot;
}

E 3
static uint_t
icpt_tx_desc_stat(struct gem_dev *dp, int slot, int ndesc)
{
#ifdef USE_FRAMEID
D 3
	uint32_t		tx_status;
	clock_t			now;
	struct icpt_dev		*lp = (struct icpt_dev *) dp->private;
E 3
I 3
	uint32_t	tx_status;
	struct icpt_dev	*lp = (struct icpt_dev *) dp->private;
E 3

D 3
	/* first, we try to compare with last frame id. */
E 3
I 3
	/* first, we try to compare the slot with the last frame id read. */
E 3
	if (slot != lp->frameid_tail) {
D 2
		return GEM_TX_DONE;
E 2
I 2
		return (GEM_TX_DONE);
E 2
	}

	/* update frame id */
	tx_status = INL(dp, TxStatus);
	lp->frameid_tail =
		SLOT(((tx_status & TS_TxFrameId) >> TS_TxFrameIdShift) + 1,
				TX_RING_SIZE);

D 2
	return (slot != lp->frameid_tail) ? GEM_TX_DONE : 0;
E 2
I 2
	return ((slot != lp->frameid_tail) ? GEM_TX_DONE : 0);
E 2
#else
D 3
	struct icpt_tfd		*tfdp;
	uint64_t		tfc;
E 3
I 3
	uint64_t	tfc;
E 3

D 3
	tfdp = &((struct icpt_tfd *)dp->tx_ring)[slot];
E 3
I 3
D 5
	tfc = LE64(((struct icpt_tfd *) dp->tx_ring)[slot].TxFrameControl);
E 5
I 5
	tfc = LE_64(((struct icpt_tfd *) dp->tx_ring)[slot].TxFrameControl);
E 5
E 3

D 3
	tfc = LE64(tfdp->TxFrameControl);
E 3
I 3
D 5
	DPRINTF(2, (CE_CONT, "%s: %s: slot:%d, tfs:0x%b",
E 5
I 5
	DPRINTF(2, (CE_CONT, "!%s: %s: slot:%d, tfs:0x%b",
E 5
		dp->name, __func__, slot, (uint32_t) tfc, TFC_BITS));
E 3

D 3
	DPRINTF(2, (CE_CONT,
		"%s: icpt_tx_desc_stat: slot:%d, tfs:0x%b",
		dp->name, slot, (uint32_t)tfc, TFC_BITS));

E 3
	if ((tfc & TFC_TFDDone) == 0) {
D 3
		/* not transmitted */
E 3
I 3
		/* not transmitted yet */
E 3
D 2
		return 0;
E 2
I 2
		return (0);
E 2
	}
D 2
	return GEM_TX_DONE;
E 2
I 2
	return (GEM_TX_DONE);
E 2
#endif
}

static uint64_t
icpt_rx_desc_stat(struct gem_dev *dp, int slot, int ndesc)
{
D 3
	struct icpt_rfd		*rfdp;
E 3
	uint64_t		rfs;
D 2
	uint_t			len;
E 2
I 2
	uint64_t		len;
E 2
	uint64_t		flag;

D 3
	rfdp = &((struct icpt_rfd *)dp->rx_ring)[slot];

	rfs  = LE64(rfdp->RxFrameStatus);
E 3
I 3
D 5
	rfs  = LE64(((struct icpt_rfd *) dp->rx_ring)[slot].RxFrameStatus);
E 5
I 5
	rfs  = LE_64(((struct icpt_rfd *) dp->rx_ring)[slot].RxFrameStatus);
E 5
E 3
	len  = rfs & RFS_RxFrameLen;
	flag = GEM_RX_DONE;

D 3
	DPRINTF(2, (CE_CONT,
		"%s: icpt_rx_desc_stat: slot:%d, rfs:0x%b",
		dp->name, slot, (uint32_t) rfs, RFS_BITS));
E 3
I 3
D 5
	DPRINTF(2, (CE_CONT, "%s: %s: slot:%d, rfs:0x%b",
E 5
I 5
	DPRINTF(2, (CE_CONT, "!%s: %s: slot:%d, rfs:0x%b",
E 5
		dp->name, __func__, slot, (uint32_t) rfs, RFS_BITS));
E 3

	if ((rfs & RFS_RFDDone) == 0) {
		/* not received */
D 2
		return 0;
E 2
I 2
		return (0);
E 2
	}

	/* XXX - RuntFrame bit unreliable */
#define	RFS_ERROR_BITS	\
	(RFS_RxFIFOOverrun |/*RFS_RxRuntFrame |*/RFS_RxAlignmentError |	\
	 RFS_RxFCSError | RFS_RxOversizedFrame | RFS_RxLengthError |	\
	 RFS_FrameStart | RFS_FrameEnd)

	if ((rfs & RFS_ERROR_BITS) != (RFS_FrameStart | RFS_FrameEnd)) {
		/* error packet */
		dp->stats.errrcv++;
D 5
		if ((rfs & RFS_RxAlignmentError) != 0) {
E 5
I 5
		if (rfs & RFS_RxAlignmentError) {
E 5
			dp->stats.frame++;
		}
D 5
		if ((rfs & RFS_RxFIFOOverrun) != 0) {
E 5
I 5
		else if (rfs & RFS_RxFIFOOverrun) {
E 5
			dp->stats.overflow++;
		}
#ifdef notdef
D 5
		if ((rfs & RFS_RxRuntFrame) != 0) {
E 5
I 5
		else if (rfs & RFS_RxRuntFrame) {
E 5
			dp->stats.runt++;
		}
#endif
D 5
		if ((rfs & RFS_RxFCSError) != 0) {
E 5
I 5
		else if (rfs & RFS_RxFCSError) {
E 5
			dp->stats.crc++;
		}
D 5
		if ((rfs & (RFS_RxLengthError | RFS_RxOversizedFrame)) != 0) {
E 5
I 5
		else if (rfs & (RFS_RxLengthError | RFS_RxOversizedFrame)) {
E 5
			dp->stats.frame_too_long++;
		}
I 5
		else {
			dp->stats.rcv_internal_err++;
		}
E 5

		flag = GEM_RX_ERR;
	}
#ifdef GEM_CONFIG_CKSUM_OFFLOAD
	if ((rfs & (RFS_TCPDetected | RFS_TCPError)) == RFS_TCPDetected) {
		flag |= GEM_RX_CKSUM_TCP;
	}
	if ((rfs & (RFS_UDPDetected | RFS_UDPError)) == RFS_UDPDetected) {
		flag |= GEM_RX_CKSUM_UDP;
	}
	if ((rfs & (RFS_IPDetected | RFS_IPError)) == RFS_IPDetected) {
		flag |= GEM_RX_CKSUM_IPv4;
	}
#endif
D 2
#ifdef GEM_CONFIG_VLAN
E 2
I 2
#ifdef notdef /* CONFIG_VLAN */
	/* the hardware doesn't seem to implement hardware vlan detection */
E 2
D 5
	if ((rfs & RFS_VLANDetected) != 0) {
E 5
I 5
	if (rfs & RFS_VLANDetected) {
E 5
		flag |= (rfs & RFS_TCI) >> (RFS_TCIShift - GEM_RX_VTAG_SHIFT);
	}
#endif
D 2
#ifdef	CONFIG_RCV_FCS
E 2
I 2
#ifdef CONFIG_RCV_FCS
E 2
	len = max(len - ETHERFCSL, 0);
#endif
D 2
	return flag | len;
E 2
I 2
	return (flag | len);
E 2
}

static void
icpt_tx_desc_init(struct gem_dev *dp, int slot)
{
D 3
	struct icpt_tfd		*tfdp;

	tfdp = &((struct icpt_tfd *)dp->tx_ring)[slot];

E 3
	/* invalidate the tfd */
D 3
	tfdp->TxFrameControl = LE64(TFC_TFDDone);
E 3
I 3
	((struct icpt_tfd *)
D 5
		dp->tx_ring)[slot].TxFrameControl = LE64(TFC_TFDDone);
E 5
I 5
		dp->tx_ring)[slot].TxFrameControl = LE_64(TFC_TFDDone);
E 5
E 3
}

static void
icpt_rx_desc_init(struct gem_dev *dp, int slot)
{
	struct icpt_rfd		*rfdp;

D 3
	rfdp = &((struct icpt_rfd *)dp->rx_ring)[slot];

E 3
	/* invalidate this rfd */
D 3
	rfdp->RxFrameStatus = LE64(RFS_RFDDone);
E 3
I 3
	((struct icpt_rfd *)
D 5
		dp->rx_ring)[slot].RxFrameStatus = LE64(RFS_RFDDone);
E 5
I 5
		dp->rx_ring)[slot].RxFrameStatus = LE_64(RFS_RFDDone);
E 5
E 3

	/* link it to the previous rfd */
	rfdp = &((struct icpt_rfd *)dp->rx_ring)[SLOT(slot - 1, RX_RING_SIZE)];
	rfdp->RxDMANextPtr =
D 5
		LE64(dp->rx_ring_dma + slot*sizeof(struct icpt_rfd));
E 5
I 5
		LE_64(dp->rx_ring_dma + slot*sizeof(struct icpt_rfd));
E 5
}

static void
icpt_tx_desc_clean(struct gem_dev *dp, int slot)
{
D 3
	struct icpt_tfd		*tfdp;

	tfdp = &((struct icpt_tfd *)dp->tx_ring)[slot];

E 3
	/* invalidate the tfd */
D 3
	tfdp->TxFrameControl = LE64(TFC_TFDDone);
E 3
I 3
	((struct icpt_tfd *)
D 5
		dp->tx_ring)[slot].TxFrameControl = LE64(TFC_TFDDone);
E 5
I 5
		dp->tx_ring)[slot].TxFrameControl = LE_64(TFC_TFDDone);
E 5
E 3
}

static void
icpt_rx_desc_clean(struct gem_dev *dp, int slot)
{
D 3
	struct icpt_rfd		*rfdp;

	rfdp = &((struct icpt_rfd *)dp->rx_ring)[slot];

E 3
	/* invalidate the rfd */
D 3
	rfdp->RxFrameStatus = LE64(RFS_RFDDone);
E 3
I 3
	((struct icpt_rfd *)
D 5
		dp->rx_ring)[slot].RxFrameStatus = LE64(RFS_RFDDone);
E 5
I 5
		dp->rx_ring)[slot].RxFrameStatus = LE_64(RFS_RFDDone);
E 5
E 3
}

/*
 * Device depend interrupt handler
 */
static void
icpt_get_tx_status(struct gem_dev  *dp)
{
	int		i;
	uint32_t	tx_status;
	struct icpt_dev	*lp = (struct icpt_dev *)dp->private;

	ASSERT(mutex_owned(&dp->intrlock));

D 5
	/* Pop up all status from the Tx status stack. */
E 5
I 5
	/* read tx status */
E 5
	if (((tx_status = INL(dp, TxStatus)) & TS_TxComplete) == 0) {
		/* tx status is invalid */
		return;
	}

	/* update statistics */

D 5
	if ((tx_status & TS_TxError) != 0) {
		dp->stats.errxmt++;
	}

	if ((tx_status & TS_TxUnderrun) != 0) {
E 5
I 5
	if (tx_status & TS_TxUnderrun) {
E 5
		/* fifo underflow. TxReset and TxEnable are required */
		cmn_err(CE_WARN,
D 5
		    "%s: tx underrun error: tx_status: %b",
E 5
I 5
		    "!%s: tx underrun error: tx_status: %b",
E 5
		    dp->name, tx_status, TS_BITS);
		dp->stats.underflow++;
I 5
		dp->stats.errxmt++;
E 5
	}

D 5
	if ((tx_status & TS_MaxCollisions) != 0) {
E 5
I 5
	if (tx_status & TS_MaxCollisions) {
E 5
		/* exceed maximum collisions */
		dp->stats.excoll++;
		dp->stats.collisions += 16;
I 5
		dp->stats.errxmt++;
E 5
	}

D 5
	if ((tx_status & TS_LateCollision) != 0) {
E 5
I 5
	if (tx_status & TS_LateCollision) {
E 5
		/* Out of Window collision detected */
		dp->stats.xmtlatecoll++;
I 5
		dp->stats.errxmt++;
E 5
	}

	mutex_enter(&dp->xmitlock);
#ifdef USE_FRAMEID
	lp->frameid_tail =
		SLOT(((tx_status & TS_TxFrameId) >> TS_TxFrameIdShift) + 1,
			TX_RING_SIZE);
#endif
D 5
	if ((tx_status &
	    (TS_TxUnderrun | TS_MaxCollisions | TS_LateCollision)) != 0) {
		if ((tx_status & TS_TxUnderrun) != 0) {
E 5
I 5
	if (tx_status &
	    (TS_TxUnderrun | TS_MaxCollisions | TS_LateCollision)) {
		if (tx_status & TS_TxUnderrun) {
E 5
			/* a fatal error */
#ifdef notdef
			/* XXX - the nic has stopped */
			OUTL_HI(dp, MACCtrl, MC_TxDisable);
#endif
			lp->need_to_reset = B_TRUE;
			/* increase tx threashold by 128 byte */
			dp->txthr = min(dp->txthr + 128,
					dp->mtu + sizeof(struct ether_header));
I 3
D 5
			cmn_err(CE_NOTE, "%s: tx error, 0x%b",
E 5
I 5
			cmn_err(CE_NOTE, "!%s: tx error, 0x%b",
E 5
				dp->name, tx_status, TS_BITS);
E 3
		}
		else {
			OUTL_HI(dp, MACCtrl, MC_TxEnable); 
		}
	}
	mutex_exit(&dp->xmitlock);
}

static u_int
icpt_interrupt(struct gem_dev *dp)
{
I 5
	u_int		ret;
E 5
	uint16_t	int_status;
D 5
	u_int		tx_sched = 0;
E 5
	struct icpt_dev	*lp = (struct icpt_dev *)dp->private;

I 5
	ret = DDI_INTR_CLAIMED;

E 5
	/*
D 3
	 * Read interrupt status
	 * Do not use IntStatusAck here. It clears IntEnable too.
E 3
I 3
	 * Read and reset interrupt status.
E 3
	 */
I 2
D 3
#ifdef NEW
E 3
	int_status = INW(dp, IntStatusAck);
D 3
#else
E 2
	int_status = INW(dp, IntStatus);
D 2

E 2
I 2
#endif
E 3
I 3

E 3
E 2
	if ((int_status & lp->intmask) == 0) {
D 5
		/* Not for us */
D 2
		return DDI_INTR_UNCLAIMED;
E 2
I 2
D 3
		if ((dp->misc_flag & GEM_NOINTR) == 0) {
E 3
I 3
		if (lp->intmask != 0 && (dp->misc_flag & GEM_NOINTR) == 0) {
			/*
			 * As reading IntStatusAck also reset IntEnable,
			 * we need to enable it again.
			 */
E 3
			OUTW(dp, IntEnable, lp->intmask);
		}
		return (DDI_INTR_UNCLAIMED);
E 5
I 5
		/* not for us */
		ret = DDI_INTR_UNCLAIMED;
		goto x;
E 5
E 2
	}
D 2

E 2
I 2
D 3
#ifndef NEW
E 2
	/*
	 * Acknowledge to the interrupt.
	 * Reading IntStatusAck clears both of IntStatus and IntEnable
	 */
	int_status = INW(dp, IntStatusAck);
I 2
#endif
E 2
	DPRINTF(2, (CE_CONT, "%s: icpt_interrupt, int_status: %b",
			   dp->name, int_status, INT_BITS));
E 3
I 3

D 5
	DPRINTF(2, (CE_CONT, "%s: %s, int_status: %b, intmask: %b",
E 5
I 5
	DPRINTF(2, (CE_CONT, "!%s: %s, int_status: %b, intmask: %b",
E 5
		dp->name, __func__,
		int_status, INT_BITS, lp->intmask, INT_BITS));

E 3
D 2
	if (!dp->nic_active) {
E 2
I 2
	if (!dp->mac_active) {
E 2
		/*
		 * the device is not active.
		 * side effect: left interrupt masked.
		 */
D 2
		return DDI_INTR_CLAIMED;
E 2
I 2
D 5
		return (DDI_INTR_CLAIMED);
E 5
I 5
		return (ret);
E 5
E 2
	}

I 3
	int_status &= lp->intmask;

E 3
#ifdef GEM_CONFIG_POLLING
	if (dp->poll_interval != lp->last_poll_interval) {
I 3
		uint32_t	wait;
		uint32_t	rxcnt;

E 3
D 5
		if (dp->poll_interval != 0) {
D 3
			/* tune rx hardware coaleasing */
			OUTL(dp, RxDMAIntCtrl,
				dp->poll_pkt_delay |
				RIC_PriorityThresh |
				((dp->poll_interval * RxDMAWaitTime_1uS)
						<< RIC_RxDMAWaitTimeShift));
#if 0
			/* It will degrade tx delay */
D 2
			dp->polled_mode = B_TRUE;
E 2
I 2
			dp->tx_coalesce = B_TRUE;
E 2
#endif
E 3
I 3
			rxcnt = dp->poll_pkt_delay;
E 5
I 5
		if (dp->poll_interval) {
			rxcnt = min(dp->poll_pkt_delay, RIC_RxFrameCount);
E 5
			wait = min(dp->poll_interval * RxDMAWaitTime_1uS,
					0xffff) << RIC_RxDMAWaitTimeShift;
E 3
		}
		else {
D 3
			/* disable rx hardware coaleasing */
			OUTL(dp, RxDMAIntCtrl, RIC_PriorityThresh | 1);
D 2
			dp->polled_mode = B_FALSE;
E 2
I 2
			dp->tx_coalesce = B_FALSE;
E 3
I 3
			rxcnt = 1;
			wait = RIC_RxDMAWaitTime;
E 3
E 2
		}

I 3
		OUTL(dp, RxDMAIntCtrl, wait | RIC_PriorityThreshMax | rxcnt);

E 3
		lp->last_poll_interval = dp->poll_interval;
	}
#endif
D 3
	int_status &= lp->intmask;
E 3

D 5
	if ((int_status &
	    (INT_RxDMAComplete | INT_MACControlFrame | INT_RFDListEnd)) != 0) {
E 5
I 5
	if (int_status &
	    (INT_RxDMAComplete | INT_MACControlFrame | INT_RFDListEnd)) {
E 5
		/*
		 * packet was received, or receive error happened
		 */
D 2
		gem_receive(dp);
E 2
I 2
		(void) gem_receive(dp);
E 2
D 5
		if ((int_status & INT_RFDListEnd) != 0) {
E 5
I 5
		if (int_status & INT_RFDListEnd) {
E 5
			/* kick rx dma engine again */
			OUTL_LOW(dp, DMACtrl, DC_RxDMAPollNow);
I 5

			dp->stats.errrcv++;
			dp->stats.norcvbuf++;
E 5
		}
	}

D 5
	if ((int_status &
		(INT_TxComplete | INT_TxDMAComplete | INT_IntRequested)) != 0) {
E 5
I 5
	if (int_status & (INT_TxComplete | INT_TxDMAComplete)) {
E 5

D 5
		if ((int_status & INT_TxComplete) != 0) {
E 5
I 5
		if (int_status & INT_TxComplete) {
E 5
			/*
			 * Need to pull up TxStatus before calling tx_desc_stat
			 */
			icpt_get_tx_status(dp);
		}

		/*
		 * Packets was transfered into TxFIFO or
		 * an error happened.
		 */
		if (gem_tx_done(dp)) {
D 3
			tx_sched |= INTR_RESTART_TX;
E 3
I 3
D 5
			tx_sched = INTR_RESTART_TX;
E 5
I 5
			ret |= INTR_RESTART_TX;
E 5
E 3
		}
	}

D 5
	if ((int_status & (INT_UpdateStats | INT_LinkEvent |
			   INT_IntRequested | INT_HostError)) != 0) {
E 5
I 5
	if (int_status & (INT_UpdateStats | INT_LinkEvent |
			   INT_IntRequested | INT_HostError)) {
E 5

D 5
		if ((int_status & INT_UpdateStats) != 0) {
E 5
I 5
		if (int_status & INT_UpdateStats) {
E 5
			/*
			 * Statistics counter overflow
			 */
			icpt_get_stats(dp);
D 5
			DPRINTF(0, (CE_CONT, "%s: %s UpdateStats",
E 5
I 5
			DPRINTF(1, (CE_CONT, "!%s: %s UpdateStats",
E 5
				dp->name, __func__));
		}

D 5
		if ((int_status & INT_LinkEvent) != 0) {
			DPRINTF(0, (CE_CONT, "%s: %s link event",
E 5
I 5
		if (int_status & INT_LinkEvent) {
			DPRINTF(0, (CE_CONT, "!%s: %s link event",
E 5
				dp->name, __func__));
D 3
			(void) gem_mii_link_check(dp);
E 3
I 3
			if (gem_mii_link_check(dp)) {
D 5
				tx_sched = INTR_RESTART_TX;
E 5
I 5
				ret |= INTR_RESTART_TX;
E 5
			}
E 3
		}

D 5
		if ((int_status & (INT_IntRequested | INT_HostError)) != 0) {
			cmn_err(CE_WARN, "%s: unexpected interrupt: %b",
E 5
I 5
		if (int_status & (INT_IntRequested | INT_HostError)) {
			cmn_err(CE_WARN, "!%s: unexpected interrupt: %b",
E 5
				dp->name, int_status, INT_BITS);
		}
	}

	if (lp->need_to_reset) { 
I 3
D 5
		DPRINTF(0, (CE_CONT, "%s: resetting...", dp->name));
E 3
		gem_restart_nic(dp, B_TRUE);
		tx_sched = INTR_RESTART_TX;
E 5
I 5
		DPRINTF(0, (CE_CONT, "!%s: resetting...", dp->name));
		gem_restart_nic(dp, GEM_RESTART_KEEP_BUF);
		ret |= INTR_RESTART_TX;
E 5
		lp->need_to_reset = B_FALSE;
	}

I 5
x:
E 5
	/*
	 * Recover Interrput Enable register
	 */
D 3
	DPRINTF(4, (CE_CONT, "%s: icpt_inter done: int_status: %b",
			   dp->name, INW(dp, IntStatus), INT_BITS));
E 3
I 3
D 5
	DPRINTF(4, (CE_CONT, "%s: %s done: int_status: %b",
E 5
I 5
	DPRINTF(4, (CE_CONT, "!%s: %s done: int_status: %b",
E 5
		   dp->name, __func__, INW(dp, IntStatus), INT_BITS));
E 3
D 5

E 5
	if ((dp->misc_flag & GEM_NOINTR) == 0) {
		OUTW(dp, IntEnable, lp->intmask);
	}

D 2
	return DDI_INTR_CLAIMED | tx_sched;
E 2
I 2
D 5
	return (DDI_INTR_CLAIMED | tx_sched);
E 5
I 5
	return (ret);
E 5
E 2
}

/*
 * HW depend MII routine
 */
#define MDIO_DELAY(dp)    {INB(dp, PhyCtrl); INB(dp, PhyCtrl);}

static void
icpt_mii_sync(struct gem_dev *dp)
{
	int	i;

	/* output 32 ones */
	for (i = 0; i < 32; i++) {
		OUTB(dp, PhyCtrl, PC_MgmtDir | PC_MgmtData);
		MDIO_DELAY(dp);
		OUTB(dp, PhyCtrl, PC_MgmtDir | PC_MgmtData | PC_MgmtClk);
		MDIO_DELAY(dp);
	}
	OUTB(dp, PhyCtrl, PC_MgmtDir | PC_MgmtData);
}

static uint16_t
icpt_mii_read(struct gem_dev *dp, uint_t reg)
{
	uint32_t	cmd;
	uint16_t	ret;
	int		i;
	uint8_t		data;

	cmd = MII_READ_CMD(dp->mii_phy_addr, reg);

	for (i = 31; i >= 18; i--) {
		data = ((cmd >> i) & 1) <<  PC_MgmtDataShift;
		OUTB(dp, PhyCtrl, data | PC_MgmtDir);
		MDIO_DELAY(dp);
		OUTB(dp, PhyCtrl, data | PC_MgmtDir | PC_MgmtClk);
		MDIO_DELAY(dp);
	}
	/* turn around */
	OUTB(dp, PhyCtrl, 0);
	MDIO_DELAY(dp);

	/* get response from PHY */
	OUTB(dp, PhyCtrl, PC_MgmtClk);
	MDIO_DELAY(dp);
	OUTB(dp, PhyCtrl, 0);
D 5
	if ((INB(dp, PhyCtrl) & PC_MgmtData) != 0) {
		DPRINTF(1, (CE_CONT, "%s: no response from phy@%d",
E 5
I 5
	if (INB(dp, PhyCtrl) & PC_MgmtData) {
		DPRINTF(1, (CE_CONT, "!%s: no response from phy@%d",
E 5
			dp->name, dp->mii_phy_addr));
	}

	OUTB(dp, PhyCtrl, PC_MgmtClk);
	MDIO_DELAY(dp);

	for (i = 16; i > 0; i--) {
		OUTB(dp, PhyCtrl, 0);
		ret = (ret << 1) | ((INB(dp, PhyCtrl) >> PC_MgmtDataShift) & 1);
		OUTB(dp, PhyCtrl, PC_MgmtClk);
		MDIO_DELAY(dp);
	}

	/* send two 1s to phy */
	for (i = 0; i < 2; i++) {
		OUTB(dp, PhyCtrl, PC_MgmtDir | PC_MgmtData);
		MDIO_DELAY(dp);
		OUTB(dp, PhyCtrl, PC_MgmtDir | PC_MgmtData | PC_MgmtClk);
		MDIO_DELAY(dp);
	}
	OUTB(dp, PhyCtrl, PC_MgmtDir | PC_MgmtData);

D 2
	return ret;
E 2
I 2
	return (ret);
E 2
}

static void
D 3
icpt_mii_write_raw(struct gem_dev *dp, uint_t reg, uint16_t val)
E 3
I 3
icpt_mii_write(struct gem_dev *dp, uint_t reg, uint16_t val)
E 3
{
	int		i;
	uint32_t	cmd;
	uint8_t		data;

	cmd = MII_WRITE_CMD(dp->mii_phy_addr, reg, val);

	for (i = 31; i >= 0; i--) {
		data = ((cmd >> i) & 1) << PC_MgmtDataShift;
		OUTB(dp, PhyCtrl, data | PC_MgmtDir);
		MDIO_DELAY(dp);
		OUTB(dp, PhyCtrl, data | PC_MgmtDir | PC_MgmtClk);
		MDIO_DELAY(dp);
	}

	/* send two 1s to phy */
	for (i = 0; i < 2; i++) {
		OUTB(dp, PhyCtrl, PC_MgmtDir | PC_MgmtData);
		MDIO_DELAY(dp);
		OUTB(dp, PhyCtrl, PC_MgmtDir  | PC_MgmtData | PC_MgmtClk);
		MDIO_DELAY(dp);
	}
	OUTB(dp, PhyCtrl, PC_MgmtDir | PC_MgmtData);
}
D 3

static void
icpt_mii_write(struct gem_dev *dp, uint_t reg, uint16_t val)
{
	icpt_mii_write_raw(dp, reg, val);

	if (reg == MII_CONTROL && (val & MII_CONTROL_RESET) != 0) {
		/* emulate write-self-clear on RESET bit */
		drv_usecwait(300000);
		icpt_mii_write_raw(dp, reg, val & ~MII_CONTROL_RESET);
	}
}
E 3
#undef MDIO_DELAY

/* ======================================================== */
/*
 * OS depend (device driver) routine
 */
/* ======================================================== */
static int
icptattach(dev_info_t *dip, ddi_attach_cmd_t cmd)
{
	int			i;
	int			n;
	ddi_acc_handle_t	conf_handle;
	int			vid;
	int			did;
	uint8_t			revid;
	uint8_t			lat;
	int			unit;
	const char		*drv_name;
	struct chip_info	*p;
	struct gem_dev		*dp;
	struct icpt_dev		*lp;
	void			*base;
	ddi_acc_handle_t	regs_ha;
	struct gem_conf		*gcp;

	unit =  ddi_get_instance(dip);
	drv_name = ddi_driver_name(dip);

D 5
	DPRINTF(3, (CE_CONT, "%s%d: icptattach: called %s",
E 5
I 5
	DPRINTF(3, (CE_CONT, "!%s%d: icptattach: called %s",
E 5
		drv_name, unit, ident));

	/*
	 * Check if chip is supported.
	 */
	if (pci_config_setup(dip, &conf_handle) != DDI_SUCCESS) {
D 5
		cmn_err(CE_WARN, "%s: ddi_regs_map_setup failed",
E 5
I 5
		cmn_err(CE_WARN, "!%s: pci_config_setup failed",
E 5
			drv_name);
		goto err;
	}

	vid  = pci_config_get16(conf_handle, PCI_CONF_VENID);
	did  = pci_config_get16(conf_handle, PCI_CONF_DEVID);
	revid= pci_config_get8(conf_handle, PCI_CONF_REVID);
	lat  = pci_config_get8(conf_handle, PCI_CONF_LATENCY_TIMER);

	for (i = 0, p = icpt_chiptbl; i < CHIPTABLESIZE; i++, p++) {
		if (p->venid == vid && p->devid == did) {
			/* found */
			goto chip_found;
		}
	}

	/* Not found */
	cmn_err(CE_WARN,
D 5
		"%s: icpt_attach: wrong PCI venid/devid (0x%x, 0x%x)",
		drv_name, vid, did);
E 5
I 5
		"!%s: %s: wrong PCI venid/devid (0x%x, 0x%x)",
		drv_name, __func__, vid, did);
E 5
	pci_config_teardown(&conf_handle);
	goto err;

chip_found:
I 5
#ifdef NEVER
{
	ddi_acc_handle_t	p_ha;

	if (pci_config_setup(ddi_get_parent(dip), &p_ha) == DDI_SUCCESS) {
		cmn_err(CE_CONT,
		"!%s: cache line: %d, latency timer: %d 2nd latency timer: %d",
			drv_name,
			pci_config_get8(p_ha, PCI_CONF_CACHE_LINESZ),
			pci_config_get8(p_ha, PCI_CONF_LATENCY_TIMER),
			pci_config_get8(p_ha, PCI_BCNF_LATENCY_TIMER));

		pci_config_put8(p_ha, PCI_CONF_CACHE_LINESZ, 0xff);
		pci_config_put8(p_ha, PCI_CONF_LATENCY_TIMER, 0xff);
		pci_config_put8(p_ha, PCI_BCNF_LATENCY_TIMER, 0xff);

		cmn_err(CE_CONT,
		"!%s: cache line: %d, latency timer: %d 2nd latency timer: %d",
			drv_name,
			pci_config_get8(p_ha, PCI_CONF_CACHE_LINESZ),
			pci_config_get8(p_ha, PCI_CONF_LATENCY_TIMER),
			pci_config_get8(p_ha, PCI_BCNF_LATENCY_TIMER));

		pci_config_teardown(&p_ha);
	}
}
#endif
E 5
	/* ensure the pmr status is D0 mode */
	(void) gem_pci_set_power_state(dip, conf_handle, PCI_PMCSR_D0);

	pci_config_put16(conf_handle, PCI_CONF_COMM,
		PCI_COMM_IO | PCI_COMM_MAE | PCI_COMM_ME |
			pci_config_get16(conf_handle, PCI_CONF_COMM));

	pci_config_teardown(&conf_handle);

	cmn_err(CE_CONT,
"!%s%d: %s (vid: 0x%04x, did: 0x%04x, revid: 0x%02x, latency timer: 0x%02x)",
		drv_name, unit, p->name, vid, did, revid, lat);

	switch (cmd) {
	case DDI_RESUME:
D 2
		return gem_resume(dip);
E 2
I 2
		return (gem_resume(dip));
E 2

	case DDI_ATTACH:
		if (gem_pci_regs_map_setup(dip,
#ifdef MAP_MEM
D 2
			PCI_ADDR_MEM32,
E 2
I 2
			PCI_ADDR_MEM32, PCI_ADDR_MASK,
E 2
#else
D 2
			PCI_ADDR_IO,
E 2
I 2
			PCI_ADDR_IO, PCI_ADDR_MASK,
E 2
#endif
			&icpt_dev_attr, (caddr_t *)&base, &regs_ha)
					!= DDI_SUCCESS) {
			goto err;
		}

		/*
		/*
		 * construct gem configration
		 */
		gcp = (struct gem_conf *) kmem_zalloc(sizeof(*gcp), KM_SLEEP);

		/* name */
		sprintf(gcp->gc_name, "%s%d", drv_name, unit);

D 3
		/* consistency on tx and rx */
E 3
I 3
		/* configuration on tx and rx rings and buffers */
E 3
		gcp->gc_tx_buf_align = sizeof(uint8_t) - 1;
		gcp->gc_tx_max_frags = IPGE_MAXTXFRAGS;
I 3
		gcp->gc_tx_max_descs_per_pkt = 1;
E 3
#if IPGE_MAXTXFRAGS <= 2
		gcp->gc_tx_desc_unit_shift = 5; /* 32 byte */
#elif IPGE_MAXTXFRAGS <= 6
		gcp->gc_tx_desc_unit_shift = 6; /* 64 byte */
#else
# error IPGE_MAXTXFRAGS must be 2 or 6
#endif
		gcp->gc_tx_buf_size  = TX_BUF_SIZE;
		gcp->gc_tx_buf_limit = gcp->gc_tx_buf_size - 1;
		gcp->gc_tx_ring_size = TX_RING_SIZE;
		gcp->gc_tx_ring_limit = gcp->gc_tx_ring_size - 1;
		gcp->gc_tx_auto_pad  = B_FALSE;
		gcp->gc_tx_copy_thresh = icpt_tx_copy_thresh;
D 3
		gcp->gc_tx_desc_write_oo = B_TRUE;
E 3
I 3
		gcp->gc_tx_desc_write_oo = TX_RING_SIZE == TX_BUF_SIZE;
E 3

		gcp->gc_rx_buf_align = sizeof(uint8_t) - 1;
		gcp->gc_rx_max_frags = 1;
		gcp->gc_rx_desc_unit_shift = 5;		/* 32 byte */
		gcp->gc_rx_ring_size = RX_RING_SIZE;
D 3
		gcp->gc_rx_buf_max   = RX_BUF_SIZE;
E 3
I 3
		gcp->gc_rx_buf_max   = min(RX_BUF_SIZE, RX_RING_SIZE -1);
E 3
		gcp->gc_rx_copy_thresh = icpt_rx_copy_thresh;

		gcp->gc_io_area_size = 0;

		/* map attributes */
D 3
		STRUCT_COPY(gcp->gc_dev_attr, icpt_dev_attr);
		STRUCT_COPY(gcp->gc_buf_attr, icpt_buf_attr);
		STRUCT_COPY(gcp->gc_desc_attr, icpt_buf_attr);
E 3
I 3
		gcp->gc_dev_attr = icpt_dev_attr;
		gcp->gc_buf_attr = icpt_buf_attr;
		gcp->gc_desc_attr = icpt_buf_attr;
E 3

		/* dma attributes */
D 3
		STRUCT_COPY(gcp->gc_dma_attr_desc, icpt_dma_attr_desc);
E 3
I 3
		gcp->gc_dma_attr_desc = icpt_dma_attr_desc;
E 3

D 3
		STRUCT_COPY(gcp->gc_dma_attr_txbuf, icpt_dma_attr_buf);
E 3
I 3
		gcp->gc_dma_attr_txbuf = icpt_dma_attr_buf;
E 3
		gcp->gc_dma_attr_txbuf.dma_attr_align = gcp->gc_tx_buf_align+1;
		gcp->gc_dma_attr_txbuf.dma_attr_sgllen = gcp->gc_tx_max_frags;

D 3
		STRUCT_COPY(gcp->gc_dma_attr_rxbuf, icpt_dma_attr_buf);
E 3
I 3
		gcp->gc_dma_attr_rxbuf = icpt_dma_attr_buf;
E 3
		gcp->gc_dma_attr_rxbuf.dma_attr_align = gcp->gc_rx_buf_align+1;
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
		gcp->gc_flow_control = FLOW_CONTROL_RX_PAUSE;

		/* mii mode */
		gcp->gc_mii_mode = GEM_MODE_1000BASET;
I 3
		gcp->gc_mii_hw_link_detection = B_TRUE;
E 3

		/* MII timeout parameters */
		gcp->gc_mii_link_watch_interval = ONESEC;
		gcp->gc_mii_an_watch_interval   = ONESEC/5;
		gcp->gc_mii_reset_timeout = MII_RESET_TIMEOUT;	/* 1 sec */
		gcp->gc_mii_an_timeout    = MII_AN_TIMEOUT;	/* 5 sec */
		gcp->gc_mii_an_wait       = 0;
		gcp->gc_mii_linkdown_timeout = MII_LINKDOWN_TIMEOUT;

		/* MII work arounds */
		gcp->gc_mii_addr_min = 0;
		gcp->gc_mii_an_delay = 0;
D 3
		gcp->gc_mii_linkdown_action = MII_ACTION_NONE;
		gcp->gc_mii_linkdown_timeout_action = MII_ACTION_RSA;
E 3
I 3
		gcp->gc_mii_linkdown_action = MII_ACTION_RSA;
		gcp->gc_mii_linkdown_timeout_action = MII_ACTION_RESET;
E 3
		gcp->gc_mii_dont_reset = B_FALSE;

		/* I/O methods */

		/* mac operation */
		gcp->gc_attach_chip = &icpt_attach_chip;
		gcp->gc_reset_chip  = &icpt_reset_chip;
		gcp->gc_init_chip   = &icpt_init_chip;
		gcp->gc_start_chip  = &icpt_start_chip;
		gcp->gc_stop_chip   = &icpt_stop_chip;
		gcp->gc_multicast_hash = &icpt_mcast_hash;
		gcp->gc_set_rx_filter = &icpt_set_rx_filter;
		gcp->gc_set_media   = &icpt_set_media;
		gcp->gc_get_stats   = &icpt_get_stats;
		gcp->gc_interrupt   = &icpt_interrupt;

		/* descriptor operation */
		gcp->gc_tx_desc_write = &icpt_tx_desc_write;
		gcp->gc_rx_desc_write = &icpt_rx_desc_write;
		gcp->gc_tx_start      = &icpt_tx_start;
I 3
		gcp->gc_rx_start      = &icpt_rx_start;
E 3

		gcp->gc_tx_desc_init = &icpt_tx_desc_init;
		gcp->gc_rx_desc_init = &icpt_rx_desc_init;
		gcp->gc_tx_desc_stat = &icpt_tx_desc_stat;
		gcp->gc_rx_desc_stat = &icpt_rx_desc_stat;
		gcp->gc_tx_desc_clean = &icpt_tx_desc_clean;
		gcp->gc_rx_desc_clean = &icpt_rx_desc_clean;

		/* mii operations */
D 5
		gcp->gc_mii_init  = &gem_mii_init_default;
E 5
I 5
		gcp->gc_mii_probe = &gem_mii_probe_default;
		gcp->gc_mii_init  = NULL;
E 5
		gcp->gc_mii_config = &gem_mii_config_default;
		gcp->gc_mii_sync  = &icpt_mii_sync;
		gcp->gc_mii_read  = &icpt_mii_read;
D 3
		gcp->gc_mii_write = &icpt_mii_write_raw;
E 3
I 3
		gcp->gc_mii_write = &icpt_mii_write;
E 3
		gcp->gc_mii_tune_phy = NULL;

		lp = kmem_zalloc(sizeof(struct icpt_dev), KM_SLEEP);
		lp->rev_id = revid;
D 5
		dp = gem_do_attach(dip, gcp, base, &regs_ha,
E 5
I 5
		dp = gem_do_attach(dip, 0, gcp, base, &regs_ha,
E 5
					lp, sizeof(*lp));

		kmem_free(gcp, sizeof(*gcp));

		if (dp != NULL) {
D 2
			return DDI_SUCCESS;
E 2
I 2
			return (DDI_SUCCESS);
E 2
		}
err_free_mem:
		kmem_free(lp, sizeof(struct icpt_dev));
err:
D 2
		return DDI_FAILURE;
E 2
I 2
		return (DDI_FAILURE);
E 2
	}
D 2
	return DDI_FAILURE;
E 2
I 2
	return (DDI_FAILURE);
E 2
}

static int
icptdetach(dev_info_t *dip, ddi_detach_cmd_t cmd)
{
	int	ret;

	switch (cmd) {
	case DDI_SUSPEND:
D 2
		return  gem_suspend(dip);
E 2
I 2
		return  (gem_suspend(dip));
E 2

	case DDI_DETACH:
D 2
		return  gem_do_detach(dip);
E 2
I 2
		return  (gem_do_detach(dip));
E 2
	}
D 2
	return DDI_FAILURE;
E 2
I 2
	return (DDI_FAILURE);
E 2
}

/* ======================================================== */
/*
 * OS depend (loadable streams driver) routine
 */
/* ======================================================== */
static	struct module_info icptminfo = {
	0,			/* mi_idnum */
	"icpt",			/* mi_idname */
	0,			/* mi_minpsz */
D 3
	ETHERMTU,		/* mi_maxpsz */
	TX_RING_SIZE*ETHERMAX,	/* mi_hiwat */
E 3
I 3
	INFPSZ,			/* mi_maxpsz */
	64*1024,		/* mi_hiwat */
E 3
	1,			/* mi_lowat */
};

static	struct qinit icptrinit = {
	(int (*)()) NULL,	/* qi_putp */
	gem_rsrv,		/* qi_srvp */
	gem_open,		/* qi_qopen */
	gem_close,		/* qi_qclose */
	(int (*)()) NULL,	/* qi_qadmin */
	&icptminfo,		/* qi_minfo */
	NULL			/* qi_mstat */
};

static	struct qinit icptwinit = {
	gem_wput,		/* qi_putp */
	gem_wsrv,		/* qi_srvp */
	(int (*)()) NULL,	/* qi_qopen */
	(int (*)()) NULL,	/* qi_qclose */
	(int (*)()) NULL,	/* qi_qadmin */
	&icptminfo,		/* qi_minfo */
	NULL			/* qi_mstat */
};

static struct streamtab	icpt_info = {
	&icptrinit,	/* st_rdinit */
	&icptwinit,	/* st_wrinit */
	NULL,		/* st_muxrinit */
	NULL		/* st_muxwrinit */
};

static	struct cb_ops cb_icpt_ops = {
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
	&icpt_info,	/* cb_str */
	D_MP,		/* cb_flag */
#ifdef notdef
	CB_REV,		/* cb_rev */
	nodev,		/* cb_aread */
	nodev,		/* cb_awrite */
#endif
};

static	struct dev_ops icpt_ops = {
	DEVO_REV,	/* devo_rev */
	0,		/* devo_refcnt */
	gem_getinfo,	/* devo_getinfo */
	nulldev,	/* devo_identify */
	nulldev,	/* devo_probe */
	icptattach,	/* devo_attach */
	icptdetach,	/* devo_detach */
	nodev,		/* devo_reset */
	&cb_icpt_ops,	/* devo_cb_ops */
	NULL,		/* devo_bus_ops */
	gem_power	/* devo_power */
};

static struct modldrv modldrv = {
	&mod_driverops,	/* Type of module.  This one is a driver */
	ident,
	&icpt_ops,	/* driver ops */
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

D 5
	DPRINTF(2, (CE_CONT, "icpt: _init: called"));
E 5
I 5
	DPRINTF(2, (CE_CONT, "!icpt: _init: called"));
E 5
	gem_mod_init(&icpt_ops, "icpt");
	status = mod_install(&modlinkage);
D 3
	if (status == DDI_SUCCESS) {
E 3
I 3
	if (status != DDI_SUCCESS) {
E 3
		gem_mod_fini(&icpt_ops);
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

D 5
	DPRINTF(2, (CE_CONT, "icpt: _fini: called"));
E 5
I 5
	DPRINTF(2, (CE_CONT, "!icpt: _fini: called"));
E 5
	status = mod_remove(&modlinkage);
	if (status == DDI_SUCCESS) {
		gem_mod_fini(&icpt_ops);
	}
	return (status);
}

int
_info(struct modinfo *modinfop)
{
	return (mod_info(&modlinkage, modinfop));
}
E 1
