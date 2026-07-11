h21971
s 00023/00021/01710
d D 1.13 11/09/19 22:42:44 mrym 13 12
c 2.6.3
e
s 00090/00043/01641
d D 1.12 11/02/20 18:49:15 mrym 12 11
c 2.6.2
e
s 00001/00001/01683
d D 1.11 08/04/23 05:22:04 mrym 11 10
c tx ring size increased 64->128
e
s 00402/00393/01282
d D 1.10 08/04/20 20:46:52 mrym 10 9
c 2.6.1
e
s 00160/00144/01515
d D 1.9 07/09/17 13:36:21 mrym 9 8
c 2.6.0
e
s 00005/00002/01654
d D 1.8 07/04/17 23:15:44 mrym 8 7
c 2.4.2
e
s 00013/00002/01643
d D 1.7 07/02/17 09:30:01 mrym 7 6
c 2.4.1 ae_nomii_read fixed for VMware
e
s 00015/00008/01630
d D 1.6 07/01/13 13:50:05 mrym 6 5
c gld v3 support
e
s 00016/00015/01622
d D 1.5 07/01/13 13:36:23 mrym 5 4
c clean up for 2.4.0
e
s 00000/00000/01637
d D 1.4 06/12/16 20:22:51 mrym 4 3
c 2.4.0
e
s 00024/00014/01613
d D 1.3 06/12/16 20:20:40 mrym 3 2
c 2.4.0, worked on 79C973
e
s 00001/00001/01626
d D 1.2 06/08/28 23:38:39 mrym 2 1
c polling mode fixed
e
s 01627/00000/00000
d D 1.1 06/07/04 23:23:22 mrym 1 0
c date and time created 06/07/04 23:23:22 by mrym
e
u
U
f e 0
t
T
I 1
/*
 * ae_gem.c : The AMD PCNET/PCI/FAST  Ethernet Driver for Solaris
 *
D 5
 * Copyright (c) 2006 Masayuki Murayama.  All rights reserved.
E 5
I 5
D 7
 * Copyright (c) 2006,2007 Masayuki Murayama.  All rights reserved.
E 7
I 7
D 10
 * Copyright (c) 2006-2007 Masayuki Murayama.  All rights reserved.
E 7
E 5
 * 
E 10
I 10
D 12
 * Copyright (c) 2006-2008 Masayuki Murayama.  All rights reserved.
E 12
I 12
 * Copyright (c) 2006-2011 Masayuki Murayama.  All rights reserved.
E 12
 *
E 10
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
D 10
 * 
E 10
I 10
 *
E 10
 * 1. Redistributions of source code must retain the above copyright notice,
D 10
 *    this list of conditions and the following disclaimer. 
 * 
E 10
I 10
 *    this list of conditions and the following disclaimer.
 *
E 10
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
D 10
 *    and/or other materials provided with the distribution. 
 * 
E 10
I 10
 *    and/or other materials provided with the distribution.
 *
E 10
 * 3. Neither the name of the author nor the names of its contributors may be
 *    used to endorse or promote products derived from this software without
D 10
 *    specific prior written permission. 
 * 
E 10
I 10
 *    specific prior written permission.
 *
E 10
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

#pragma	ident	"%W% %E%"

D 10
/*
 *  Changelog:
I 7
 2007/02/17	ae_nomii_read fixed. VMware doesn't rise LEDOUT_LED bit.
		thank to Erast Benson for the report and the test.
I 8
 2007/04/17	set_rx_filter, mii_linkdown_action fixed
 2007/04/17	2.4.2 release
I 9
 2007/09/16	2.6.0
E 9
		
E 8
E 7
 */

/*
 * TODO
 */

E 10
/* ======================================================= */

/*
 * Solaris system header files and macros
 */
#include <sys/types.h>
#include <sys/conf.h>
#include <sys/debug.h>
D 10
#include <sys/stropts.h>
#include <sys/stream.h>
#include <sys/strlog.h>
E 10
#include <sys/kmem.h>
D 10
#include <sys/stat.h>
#include <sys/kstat.h>
#include <sys/vtrace.h>
#include <sys/dlpi.h>
#include <sys/strsun.h>
#include <sys/ethernet.h>
E 10
#include <sys/modctl.h>
#include <sys/errno.h>
D 10
#include <sys/dditypes.h>
E 10
#include <sys/ddi.h>
#include <sys/sunddi.h>
I 9
#include <sys/byteorder.h>
E 9
D 10

E 10
I 10
#include <sys/ethernet.h>
E 10
#include <sys/pci.h>

#include "gem.h"
D 9
#include "mii.h"
E 9
I 9
#include "gem_mii.h"
E 9

#include "pcnet.h"

char	ident[] = "pcnet driver v" VERSION;

/*
 * Useful macros
 */
#define	ROUNDUP2(x, y)	(((x)+(y)-1) & ~((y)-1))
D 9
#define	FALSE	(B_FALSE)
#define	TRUE	(!B_FALSE)
E 9
I 9
#define	ONESEC		(drv_usectohz(1*1000000))
E 9

D 5
#define	STRUCT_COPY(a, b)	bcopy(&(b), &(a), sizeof(a))

E 5
D 9
#define	ONESEC			(drv_usectohz(1*1000000))

E 9
D 10
#define	IBP_VADDR(dp)	((struct init_block *) ((caddr_t)((dp)->io_area)))
E 10
I 10
#define	IBP_VADDR(dp)	((void *)((dp)->io_area))
E 10

D 9
#ifdef sun4u
#define	LE64(x)	ddi_swap64(x)
D 3
#define	LE32(x)	ddi_swap16(x)
E 3
I 3
#define	LE32(x)	ddi_swap32(x)
E 3
#define	LE16(x)	ddi_swap16(x)
D 3
#define	LE8(x)	ddi_swap8(x)
E 3
I 3
#define	LE8(x)	((uint8_t)(x))
E 3
#else
#define	LE64(x)	((uint64_t)(x))
#define	LE32(x)	((uint32_t)(x))
#define	LE16(x)	((uint16_t)(x))
#define	LE8(x)	((uint8_t)(x))
#endif

E 9
D 10
#ifdef MAP_MEM
#define	FLSH(dp)	(void)INL(dp, RDP)
E 10
I 10
#if defined(MAP_MEM) || defined(__sparc)
#define	FLSHL(dp, r)	(void)INL(dp, r)
#define	FLSHW(dp, r)	(void)INW(dp, r)
E 10
#else
D 10
#define	FLSH(dp)
E 10
I 10
#define	FLSHL(dp, r)
#define	FLSHW(dp, r)
E 10
#endif

I 10
#define	RXDESC(t)	((struct rx_desc *)((void *)(t)))
#define	TXDESC(t)	((struct tx_desc *)((void *)(t)))

E 10
/*
 * Debugging
 */
#ifdef DEBUG_LEVEL
static int ae_debug = DEBUG_LEVEL;
D 10
#define DPRINTF(n, args)	if (ae_debug > (n)) cmn_err args
E 10
I 10
#define	DPRINTF(n, args)	if (ae_debug > (n)) cmn_err args
E 10
#else
D 10
#define DPRINTF(n, args)
E 10
I 10
#define	DPRINTF(n, args)
E 10
#endif

/*
 * Our configration for PCNET
 */
D 10
#define	TX_RING_SIZE_P2	7		/* 128 */
E 10
I 10
D 12
#if defined(OS_PUTBACK) || defined(CONFIG_OO)
#define	MAXTXFRAGS	1
#else
#define	MAXTXFRAGS	GEM_MAXTXFRAGS
#endif
E 12
I 12
#define	MAXTXFRAGS	(min(8, GEM_MAXTXFRAGS))
E 12
#define	MAXRXFRAGS	1

D 11
#define	TX_RING_SIZE_P2	6		/* 64 */
E 11
I 11
D 12
#define	TX_RING_SIZE_P2	7		/* 128 */
E 12
I 12
#define	TX_RING_SIZE_P2	6		/* 64 */
E 12
E 11
E 10
#define	RX_RING_SIZE_P2	8		/* 256 */

#define	TX_RING_SIZE	(1 << TX_RING_SIZE_P2)
#define	RX_RING_SIZE	(1 << RX_RING_SIZE_P2)

#ifndef	TX_BUF_SIZE
D 10
# define TX_BUF_SIZE	TX_RING_SIZE
E 10
I 10
#define	TX_BUF_SIZE	TX_RING_SIZE
E 10
#endif

#ifndef	RX_BUF_SIZE
D 10
# define RX_BUF_SIZE	RX_RING_SIZE
E 10
I 10
#define	RX_BUF_SIZE	RX_RING_SIZE
E 10
#endif

#define	OUR_INTR_MASK	\
	(CSR0_BABL | CSR0_MISS | CSR0_MERR | CSR0_RINT | CSR0_TINT)

static int	ae_tx_copy_thresh = 256;
static int	ae_rx_copy_thresh = 256;

/*
 * Local device definitions
 */
struct chip_info {
	uint16_t	partid;
	char		*name;
	uint_t		flags;
#define	CAP_MII		0x0001
#define	CAP_FDX		0x0002
#define	CAP_CSR5	0x0004
#define	CAP_NOUFLO	0x0008
#define	CAP_CSR7	0x0010

} chiptable[] = {
D 10
 {
E 10
I 10
{
E 10
	0x2420, "AMD PCnet/PCI AM79C970",
	0,
D 10
 },
 {
E 10
I 10
},
{
E 10
	0x2430, "AMD PCnet/PCI AM79C970",
	0,
D 10
 },
 {
E 10
I 10
},
{
E 10
	0x2621, "AMD PCnet/PCI II AM79C970A",
D 12
	CAP_FDX,
E 12
I 12
	CAP_FDX | CAP_CSR5,
E 12
D 10
 },
 {
E 10
I 10
},
{
E 10
	0x2623, "AMD PCnet/FAST AM79C971",
	CAP_FDX | CAP_MII | CAP_CSR5 | CAP_CSR7 | CAP_NOUFLO,
D 10
 },
 {
E 10
I 10
},
{
E 10
	0x2624, "AMD PCnet/FAST+ AM79C972",
	CAP_FDX | CAP_MII | CAP_CSR5 | CAP_CSR7 | CAP_NOUFLO,
D 10
 },
 {
E 10
I 10
},
{
E 10
	0x2625, "AMD PCnet/FAST III AM79C973",
	CAP_FDX | CAP_MII | CAP_CSR5 | CAP_CSR7 | CAP_NOUFLO,
D 10
 },
 {
E 10
I 10
},
{
E 10
	0x2626, "AMD PCnet/Home AM79C978",
	CAP_FDX | CAP_MII | CAP_CSR5 | CAP_CSR7 | CAP_NOUFLO,
D 10
 },
 {
E 10
I 10
},
{
E 10
	0x2627, "AMD PCnet/FAST III AM79C975",
	CAP_FDX | CAP_MII | CAP_CSR5 | CAP_CSR7 | CAP_NOUFLO,
D 10
 },
 {
E 10
I 10
},
{
E 10
	0x2628, "AMD PCnet/PRO AM79C976",
	CAP_FDX | CAP_MII | CAP_CSR5 | CAP_CSR7 | CAP_NOUFLO,
D 10
 },
E 10
I 10
},
E 10
};

D 10
#define	CHIPTABLESIZE	(sizeof(chiptable)/sizeof(struct chip_info))
E 10
I 10
#define	CHIPTABLESIZE	(sizeof (chiptable)/sizeof (struct chip_info))
E 10

struct ae_dev {
	struct chip_info	*chip;
	kmutex_t		reglock;

	/* register shadows */
	uint16_t		rap;
	uint16_t		csr0;
	uint16_t		csr3;
D 10
#ifdef GEM_CONFIG_POLLING
E 10
I 10
#ifdef CONFIG_POLLING
E 10
	uint16_t		csr7;
#endif
	/* mii phy emulator state */
	uint16_t		bmcr;
	uint16_t		bmsr;
	uint16_t		adv;
D 10
#ifdef GEM_CONFIG_POLLING
E 10
I 10
#ifdef CONFIG_POLLING
E 10
	clock_t			last_poll_interval;
I 10
	boolean_t		do_polling;
E 10
#endif
I 10
	boolean_t		check_link_state;
E 10
};

/*
 * private functions
 */
D 10
 
E 10
I 10

E 10
/* mii operations */
static void  ae_mii_sync(struct gem_dev *);
static uint16_t ae_mii_read(struct gem_dev *, uint_t);
static void ae_mii_write(struct gem_dev *, uint_t, uint16_t);

/* nic operations */
static int ae_attach_chip(struct gem_dev *);
static int ae_reset_chip(struct gem_dev *);
D 3
static void ae_init_chip(struct gem_dev *);
static void ae_start_chip(struct gem_dev *);
E 3
I 3
static int ae_init_chip(struct gem_dev *);
static int ae_start_chip(struct gem_dev *);
E 3
static int ae_stop_chip(struct gem_dev *);
D 3
static void ae_set_media(struct gem_dev *);
static void ae_set_rx_filter(struct gem_dev *);
static void ae_get_stats(struct gem_dev *);
E 3
I 3
static int ae_set_media(struct gem_dev *);
static int ae_set_rx_filter(struct gem_dev *);
static int ae_get_stats(struct gem_dev *);
E 3

/* descriptor operations */
static int ae_tx_desc_write(struct gem_dev *dp, int slot,
D 9
		    ddi_dma_cookie_t *dmacookie, int frags, uint32_t intreq);
E 9
I 9
D 10
		    ddi_dma_cookie_t *dmacookie, int frags, uint64_t intreq);
E 10
I 10
    ddi_dma_cookie_t *dmacookie, int frags, uint64_t intreq);
E 10
E 9
static void ae_rx_desc_write(struct gem_dev *dp, int slot,
D 10
		    ddi_dma_cookie_t *dmacookie, int frags);
E 10
I 10
    ddi_dma_cookie_t *dmacookie, int frags);
E 10
static uint_t ae_tx_desc_stat(struct gem_dev *dp, int slot, int ndesc);
static uint64_t ae_rx_desc_stat(struct gem_dev *dp, int slot, int ndesc);

static void ae_tx_desc_init(struct gem_dev *dp, int slot);
static void ae_rx_desc_init(struct gem_dev *dp, int slot);

/* interrupt handler */
D 10
static u_int ae_interrupt(struct gem_dev *dp);
E 10
I 10
static uint_t ae_interrupt(struct gem_dev *dp);
E 10

/* ======================================================== */

/* mapping attributes */
/* Data access requirements. */
static struct ddi_device_acc_attr ae_dev_attr = {
	DDI_DEVICE_ATTR_V0,
	DDI_STRUCTURE_LE_ACC,
	DDI_STRICTORDER_ACC
};

/* On sparc, the buffers should be native endianness */
static struct ddi_device_acc_attr ae_buf_attr = {
	DDI_DEVICE_ATTR_V0,
	DDI_NEVERSWAP_ACC,	/* native endianness */
	DDI_STRICTORDER_ACC
};

static ddi_dma_attr_t ae_dma_attr_buf = {
	DMA_ATTR_V0,		/* dma_attr_version */
	0,			/* dma_attr_addr_lo */
	0xffffffffull,		/* dma_attr_addr_hi */
D 9
	0xfffull,		/* dma_attr_count_max */
E 9
I 9
	0xffffull,		/* dma_attr_count_max */
E 9
	1,			/* dma_attr_align */
	0xffffffff,		/* dma_attr_burstsizes */
	1,			/* dma_attr_minxfer */
	0xffffffffull,		/* dma_attr_maxxfer */
	0xffffffffull,		/* dma_attr_seg */
	1,			/* dma_attr_sgllen */
	1,			/* dma_attr_granular */
	0			/* dma_attr_flags */
};

static ddi_dma_attr_t ae_dma_attr_desc = {
	DMA_ATTR_V0,		/* dma_attr_version */
	0,			/* dma_attr_addr_lo */
	0xffffffffull,		/* dma_attr_addr_hi */
	0xffffull,		/* dma_attr_count_max */
	16,			/* dma_attr_align */
	0xffffffff,		/* dma_attr_burstsizes */
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

/* =============================================================== */
/*
 * Local IO support
 */
/* =============================================================== */
static uint16_t
D 10
ae_csr_read(struct gem_dev *dp, int reg)
E 10
I 10
ae_csr_read(struct gem_dev *dp, uint16_t reg)
E 10
{
D 10
	struct ae_dev	*lp = (struct ae_dev *) dp->private;
E 10
I 10
	struct ae_dev	*lp = dp->private;
E 10

	ASSERT(mutex_owned(&lp->reglock));
	if (lp->rap != reg) {
		OUTL(dp, RAP, reg);
I 10
		FLSHL(dp, RAP);
E 10
		lp->rap = reg;
	}
D 10
	return (INL(dp, RDP));
E 10
I 10
	return ((uint16_t)INL(dp, RDP));
E 10
}

static void
D 10
ae_csr_write(struct gem_dev *dp, int reg, uint16_t val)
E 10
I 10
ae_csr_write(struct gem_dev *dp, uint16_t reg, uint16_t val)
E 10
{
D 10
	struct ae_dev	*lp = (struct ae_dev *) dp->private;
E 10
I 10
	struct ae_dev	*lp = dp->private;
E 10

	ASSERT(mutex_owned(&lp->reglock));
	if (lp->rap != reg) {
		OUTL(dp, RAP, reg);
I 10
		FLSHL(dp, RAP);
E 10
		lp->rap = reg;
	}
	OUTL(dp, RDP, val);
I 10
	FLSHL(dp, RDP);
E 10
}

static uint16_t
D 10
ae_bcr_read(struct gem_dev *dp, int reg)
E 10
I 10
ae_bcr_read(struct gem_dev *dp, uint16_t reg)
E 10
{
D 10
	struct ae_dev	*lp = (struct ae_dev *) dp->private;
E 10
I 10
	struct ae_dev	*lp = dp->private;
E 10

	ASSERT(mutex_owned(&lp->reglock));
	if (lp->rap != reg) {
		OUTL(dp, RAP, reg);
I 10
		FLSHL(dp, RAP);
E 10
		lp->rap = reg;
	}
D 10
	return (INL(dp, BDP));
E 10
I 10
	return ((uint16_t)INL(dp, BDP));
E 10
}

static void
D 10
ae_bcr_write(struct gem_dev *dp, int reg, uint16_t val)
E 10
I 10
ae_bcr_write(struct gem_dev *dp, uint16_t reg, uint16_t val)
E 10
{
D 10
	struct ae_dev	*lp = (struct ae_dev *) dp->private;
E 10
I 10
	struct ae_dev	*lp = dp->private;
E 10

	ASSERT(mutex_owned(&lp->reglock));
	if (lp->rap != reg) {
		OUTL(dp, RAP, reg);
I 10
		FLSHL(dp, RAP);
E 10
		lp->rap = reg;
	}
	OUTL(dp, BDP, val);
I 10
	FLSHL(dp, BDP);
E 10
}

/* =============================================================== */
/*
 * Hardware manupilation
 */
/* =============================================================== */
static int
ae_reset_chip(struct gem_dev *dp)
{
D 10
	struct ae_dev	*lp = (struct ae_dev *)(dp)->private;
E 10
I 10
	struct ae_dev	*lp = dp->private;
E 10

	DPRINTF(1, (CE_CONT, "!%s: %s: called", dp->name, __func__));

	mutex_enter(&lp->reglock);
	OUTW(dp, RAP_W, CSR88);
I 10
	FLSHW(dp, RAP_W);
E 10
	if (INW(dp, RAP_W) == CSR88) {
		/* reset in word mode */
		DPRINTF(0, (CE_CONT, "!%s: %s: reset in word mode",
D 10
			dp->name, __func__));
		(void)INW(dp, RST_W);
	}
	else {
E 10
I 10
		    dp->name, __func__));
		(void) INW(dp, RST_W);
	} else {
E 10
		/* reset in double word mode */
		DPRINTF(0, (CE_CONT, "!%s: %s: reset in double word mode",
D 10
			dp->name, __func__));
		(void)INL(dp, RST);
E 10
I 10
		    dp->name, __func__));
		(void) INL(dp, RST);
E 10
	}
	lp->rap = CSR0;
	drv_usecwait(10);

	/* ensure that we are in double word mode */
	OUTL(dp, RDP, 0);
I 10
	FLSHL(dp, RDP);
E 10

D 9
	/* move to 32bit software style */
E 9
I 9
D 10
	/* move to 32 bit software style */
E 10
I 10
	/* move to 32bit software style */
E 10
E 9
	ae_csr_write(dp, CSR58, CSR58_SWSTYLE_PCNETPCI);

	mutex_exit(&lp->reglock);

	DPRINTF(1, (CE_CONT, "!%s: %s: done", dp->name, __func__));

	return (GEM_SUCCESS);
}

/*
 * Setup am79c790
 */
D 3
static void
E 3
I 3
static int
E 3
ae_init_chip(struct gem_dev *dp)
{
	uint16_t		val;
	struct init_block	*ibp;
D 10
	struct ae_dev		*lp = (struct ae_dev *)(dp)->private;
E 10
I 10
	struct ae_dev		*lp = dp->private;
E 10

	DPRINTF(1, (CE_CONT, "!%s: %s: called", dp->name, __func__));

	/* setup initialization block */
	ibp = IBP_VADDR(dp);
D 9
	bzero((caddr_t)ibp, sizeof (struct init_block));
	ibp->ib_rdra = LE32(dp->rx_ring_dma);
	ibp->ib_tdra = LE32(dp->tx_ring_dma);
	ibp->ib_rlen = LE8(RX_RING_SIZE_P2 << IB_LEN_SHIFT);
	ibp->ib_tlen = LE8(TX_RING_SIZE_P2 << IB_LEN_SHIFT);
E 9
I 9
D 10
	bzero((caddr_t)ibp, sizeof(struct init_block));
E 10
I 10
	bzero(ibp, sizeof (struct init_block));
E 10
	ibp->ib_rdra = LE_32(dp->rx_ring_dma);
	ibp->ib_tdra = LE_32(dp->tx_ring_dma);
	ibp->ib_rlen = LE_8(RX_RING_SIZE_P2 << IB_LEN_SHIFT);
	ibp->ib_tlen = LE_8(TX_RING_SIZE_P2 << IB_LEN_SHIFT);
E 9

	mutex_enter(&lp->reglock);

	/* CSR1, CSR2: initialize block address */
D 10
	ae_csr_write(dp, CSR1, (uint16_t) dp->io_area_dma);
E 10
I 10
	ae_csr_write(dp, CSR1, (uint16_t)dp->io_area_dma);
E 10
	ae_csr_write(dp, CSR2, (uint16_t)(dp->io_area_dma >> 16));

	/* CSR3: interrupt mask and bus swap */
#if DEBUG_LEVEL
D 9
	cmn_err(CE_CONT, "%s: %s: csr3:0x%b",
E 9
I 9
	cmn_err(CE_CONT, "!%s: %s: csr3:0x%b",
E 9
D 10
		dp->name, __func__, ae_csr_read(dp, CSR3), CSR3_BITS);
E 10
I 10
	    dp->name, __func__, ae_csr_read(dp, CSR3), CSR3_BITS);
E 10
#endif
	lp->csr3 = CSR0_ISR & ~OUR_INTR_MASK;
I 12
	if ((lp->chip->flags & CAP_CSR5) == 0) {
		/*
		 * We need to restart nic
		 * on IDON interrupt after re-initialization
		 * due to change rx filter setting.
		 */
		lp->csr3 &= ~CSR0_IDON;
	}
E 12
D 9
	if ((lp->chip->flags & CAP_NOUFLO) != 0) {
E 9
I 9
	if (lp->chip->flags & CAP_NOUFLO) {
E 9
		lp->csr3 |= CSR3_DXSUFLO;
	}
	ae_csr_write(dp, CSR3, lp->csr3);

	/* CSR4: test and feature control */
#if DEBUG_LEVEL
D 9
	cmn_err(CE_CONT, "%s: %s: csr4:0x%b",
E 9
I 9
	cmn_err(CE_CONT, "!%s: %s: csr4:0x%b",
E 9
D 10
		dp->name, __func__, ae_csr_read(dp, CSR4), CSR4_BITS);
E 10
I 10
	    dp->name, __func__, ae_csr_read(dp, CSR4), CSR4_BITS);
E 10
#endif
	ae_csr_write(dp, CSR4, CSR4_TXDPOLL | CSR4_APAD_XMT | CSR4_TXSTRTM);

	/* CSR5: extended interrupt control 1 */
D 9
	if ((lp->chip->flags & CAP_CSR5) != 0) {
E 9
I 9
	if (lp->chip->flags & CAP_CSR5) {
E 9
		DPRINTF(0, (CE_CONT, "!%s: %s: csr5:0x%b",
D 10
			dp->name, __func__, ae_csr_read(dp, CSR5), CSR5_BITS));
		ae_csr_write(dp, CSR5, CSR5_LTINTEN);
E 10
I 10
		    dp->name, __func__, ae_csr_read(dp, CSR5), CSR5_BITS));
		ae_csr_write(dp, CSR5, CSR5_TOKINTD | CSR5_LTINTEN);
E 10
	}

D 10
#ifdef GEM_CONFIG_POLLING
E 10
I 10
#ifdef CONFIG_POLLING
E 10
	/* CSR7: extended interrupt control 2 */
D 9
	if ((lp->chip->flags & CAP_CSR7) != 0) {
E 9
I 9
	if (lp->chip->flags & CAP_CSR7) {
E 9
		DPRINTF(0, (CE_CONT, "!%s: %s: csr7:0x%b",
D 10
			dp->name, __func__, ae_csr_read(dp, CSR7), CSR7_BITS));
E 10
I 10
		    dp->name, __func__, ae_csr_read(dp, CSR7), CSR7_BITS));
E 10
		lp->csr7 = 0;
	}
#endif
	DPRINTF(0, (CE_CONT, "!%s: %s: csr80:0x%x",
D 10
			dp->name, __func__, ae_csr_read(dp, CSR80)));
E 10
I 10
	    dp->name, __func__, ae_csr_read(dp, CSR80)));
E 10
	val = 0;
	if (dp->rxthr < 16) {
		val |= CSR80_RCVFW_16;
	} else if (dp->rxthr < 64) {
		val |= CSR80_RCVFW_64;
	} else {
		val |= CSR80_RCVFW_112;
	}

	if (dp->txthr <= 20) {
		val |= CSR80_XMTSP_20;
	} else if (dp->txthr <= 64) {
		val |= CSR80_XMTSP_64;
	} else if (dp->txthr <= 128) {
		val |= CSR80_XMTSP_128;
	} else {
		val |= CSR80_XMTSP_248;
	}
	if (dp->txmaxdma <= 16) {
		val |= CSR80_XMTFW_16;
	} else if (dp->txmaxdma <= 64) {
		val |= CSR80_XMTFW_64;
	} else {
		val |= CSR80_XMTFW_108;
	}
	val |= min(max(dp->txmaxdma, dp->rxmaxdma), CSR80_DMATC);
	ae_csr_write(dp, CSR80, val);
	DPRINTF(0, (CE_CONT, "!%s: %s: new csr80:0x%x",
D 10
			dp->name, __func__, ae_csr_read(dp, CSR80)));
E 10
I 10
	    dp->name, __func__, ae_csr_read(dp, CSR80)));
E 10

	DPRINTF(0, (CE_CONT, "!%s: %s: bsbc:0x%b",
D 10
			dp->name, __func__, ae_bcr_read(dp, BSBC), BSBC_BITS));
E 10
I 10
	    dp->name, __func__, ae_bcr_read(dp, BSBC), BSBC_BITS));
E 10
I 9

E 9
	val = ae_bcr_read(dp, BSBC) | BSBC_MEMCMD;
D 9
	if ((lp->chip->flags & CAP_NOUFLO) != 0 && dp->txthr >= dp->mtu) {
E 9
I 9
	if ((lp->chip->flags & CAP_NOUFLO) && dp->txthr >= dp->mtu) {
E 9
		val |= BSBC_NOUFLO;
	}
	ae_bcr_write(dp, BSBC, val);
	DPRINTF(0, (CE_CONT, "!%s: %s: new bsbc:0x%b",
D 10
			dp->name, __func__, ae_bcr_read(dp, BSBC), BSBC_BITS));
E 10
I 10
	    dp->name, __func__, ae_bcr_read(dp, BSBC), BSBC_BITS));
E 10

D 10

E 10
	mutex_exit(&lp->reglock);

D 10
#ifdef GEM_CONFIG_POLLING
E 10
I 10
#ifdef CONFIG_POLLING
E 10
	lp->last_poll_interval = 0;
#endif
	DPRINTF(1, (CE_CONT, "!%s: %s: done", dp->name, __func__));
I 3

	return (GEM_SUCCESS);
E 3
}

static uint_t
ae_mcast_hash(struct gem_dev *dp, uint8_t *addr)
{
	return (gem_ether_crc_le(addr, ETHERADDRL) >> (32 - 6));
}

D 3
static void
E 3
I 3
static int
E 3
ae_set_rx_filter(struct gem_dev *dp)
{
	int			i;
	uint16_t		mode;
	uint16_t		val;
	uint64_t		mhash;
	struct init_block	*ibp = IBP_VADDR(dp);
D 10
	struct ae_dev		*lp = (struct ae_dev *) (dp)->private;
E 10
I 10
	struct ae_dev		*lp = dp->private;
E 10

D 12
	DPRINTF(1, (CE_CONT, "!%s: %s: called", dp->name, __func__));
E 12
I 12
	DPRINTF(1, (CE_CONT, "!%s: %s: called, rxmode:%b, mccnt:%d",
	    dp->name, __func__, dp->rxmode, RXMODE_BITS, dp->mc_count));
E 12

	/* clear mode and hash table */
D 9
	mode = ((lp->chip->flags & CAP_MII) != 0)
E 9
I 9
D 10
	mode = (lp->chip->flags & CAP_MII)
E 9
			? CSR15_PORTSEL_MII : CSR15_PORTSEL_10BASET;
E 10
I 10
	mode = (lp->chip->flags & CAP_MII) ?
	    CSR15_PORTSEL_MII : CSR15_PORTSEL_10BASET;
E 10
	mhash = 0;

	if ((dp->rxmode & RXMODE_ENABLE) == 0) {
		/* do nothing otherwise it will case infinit recursive calls. */
D 8
		return;
E 8
I 8
		return (GEM_SUCCESS);
E 8
D 10
	}
D 9
	else if ((dp->rxmode & RXMODE_PROMISC) != 0) {
E 9
I 9
	else if (dp->rxmode & RXMODE_PROMISC) {
E 10
I 10
	} else if (dp->rxmode & RXMODE_PROMISC) {
E 10
E 9
		/* promiscious mode implies all multicast and all physical */
		mode |= CSR15_PROM;
		mhash = ~0ull;
D 10
	}	
D 9
	else if ((dp->rxmode & RXMODE_ALLMULTI) != 0 || dp->mc_count > 32) {
E 9
I 9
	else if ((dp->rxmode & RXMODE_ALLMULTI) || dp->mc_count > 32) {
E 10
I 10
	} else if ((dp->rxmode & RXMODE_ALLMULTI) || dp->mc_count > 32) {
E 10
E 9
		/* accept all multicast packets */
		mhash = ~0ull;
D 10
	}
	else {
E 10
I 10
	} else {
E 10
		/*
D 9
		 * make hash table to select interresting
E 9
I 9
		 * make hash table to select interrested
E 9
		 * multicast address only.
		 */
		for (i = 0; i < dp->mc_count; i++) {
			mhash |= 1ull << dp->mc_list[i].hash;
		}
	}

	/* update mode */
D 9
	ibp->ib_mode = LE16(mode);
E 9
I 9
	ibp->ib_mode = LE_16(mode);
E 9

	/* update hash table */
D 9
	ibp->ib_ladrf[0] = LE32(mhash);
	ibp->ib_ladrf[1] = LE32(mhash >> 32);
E 9
I 9
D 10
	ibp->ib_ladrf[0] = LE_32(mhash);
	ibp->ib_ladrf[1] = LE_32(mhash >> 32);
E 10
I 10
	ibp->ib_ladrf[0] = LE_32((uint32_t)mhash);
	ibp->ib_ladrf[1] = LE_32((uint32_t)(mhash >> 32));
E 10
E 9

	/* set mac address */
D 9
	for (i = 0; i < ETHERADDRL; i++) {
		ibp->ib_padr[i] = dp->cur_addr.ether_addr_octet[i];
	}
E 9
I 9
D 10
	bcopy(dp->cur_addr.ether_addr_octet, (void *) ibp->ib_padr, ETHERADDRL);
E 10
I 10
	bcopy(dp->cur_addr.ether_addr_octet, (void *)ibp->ib_padr, ETHERADDRL);
E 10
E 9

D 10
	if (dp->mac_active) {
D 9
		if ((lp->chip->flags & CAP_CSR5) != 0) {
			mutex_enter(&lp->reglock);
E 9
I 9
		if (lp->chip->flags & CAP_CSR5) {
			/* we can notify the update to the nic gracefully */
E 10
I 10
	if (!dp->mac_active) {
		DPRINTF(4, (CE_CONT, "!%s: returned", __func__));
		return (GEM_SUCCESS);
	}
E 10
E 9

D 9
			/* suspend nic */
E 9
I 9
D 10
			/* suspend the nic */
			mutex_enter(&lp->reglock);
E 9
			val = ae_csr_read(dp, CSR5);
			ae_csr_write(dp, CSR5, val | CSR5_SPND);
D 9
			for (i = 0; (ae_csr_read(dp, CSR5) & CSR5_SPND) == 0;
									i++) {
E 9
I 9
			i = 0;
			while ((ae_csr_read(dp, CSR5) & CSR5_SPND) == 0) {
E 9
				if (i > 1000) {
					cmn_err(CE_NOTE,
D 9
						"%s: %s: failed to suspend nic",
E 9
I 9
					"!%s: %s: failed to suspend nic",
E 9
						dp->name, __func__);
D 9
					break;
E 9
I 9
					mutex_exit(&lp->reglock);
					goto reset_nic;
E 9
				}
				drv_usecwait(10);
I 9
				i++;
E 9
			}
E 10
I 10
	if (lp->chip->flags & CAP_CSR5) {
		/* we can notify the update to the nic gracefully */
E 10

D 10
			/* write new mode and logical filter */
D 9
			ae_csr_write(dp, CSR15, LE16(mode));
E 9
I 9
			ae_csr_write(dp, CSR15, LE_16(mode));
E 9
			for (i = 0; i < 4; i++) {
D 9
				ae_csr_write(dp, CSR8+i, LE16(mhash >> 16*i));
E 9
I 9
				ae_csr_write(dp, CSR8 + i, LE_16(mhash));
				mhash >>= 16;
E 10
I 10
		/* suspend the nic */
		mutex_enter(&lp->reglock);
		val = ae_csr_read(dp, CSR5);
		ae_csr_write(dp, CSR5, val | CSR5_SPND);

D 12
		for (i = 0; !(ae_csr_read(dp, CSR5) & CSR5_SPND); i++) {
E 12
I 12
		for (i = 0; (ae_csr_read(dp, CSR5) & CSR5_SPND) == 0; i++) {
E 12
			if (i > 1000) {
I 12
				mutex_exit(&lp->reglock);
E 12
				cmn_err(CE_NOTE,
				    "!%s: %s: failed to suspend nic",
				    dp->name, __func__);
D 12
				mutex_exit(&lp->reglock);
E 12
				goto reset_nic;
E 10
E 9
			}
I 10
			drv_usecwait(10);
		}
E 10

D 9
			/* resume nic */
E 9
I 9
D 10
			/* resume the nic */
E 9
			ae_csr_write(dp, CSR5, val);
			mutex_exit(&lp->reglock);
		} else {
I 9
reset_nic:
E 9
D 5
			gem_restart_nic(dp, B_TRUE);
E 5
I 5
			gem_restart_nic(dp, GEM_RESTART_KEEP_BUF);
E 10
I 10
		/* write new mode and logical filter */
		ae_csr_write(dp, CSR15, LE_16(mode));
		for (i = 0; i < 4; i++) {
			ae_csr_write(dp, CSR8 + i, LE_16((uint16_t)mhash));
			mhash >>= 16;
E 10
E 5
		}
I 10

		/* resume the nic */
		ae_csr_write(dp, CSR5, val);
		mutex_exit(&lp->reglock);

		DPRINTF(4, (CE_CONT, "!%s: returned", __func__));
		return (GEM_SUCCESS);
E 10
	}

D 10
	DPRINTF(4, (CE_CONT, "!%s: returned", __func__));
E 10
I 10
reset_nic:
D 12
	(void) gem_restart_nic(dp, GEM_RESTART_KEEP_BUF);
E 12
I 12
	/* load initialization block into nic */
	mutex_enter(&lp->reglock);
	ae_csr_write(dp, CSR0, CSR0_STOP | lp->csr0);
	ae_csr_write(dp, CSR0, CSR0_INIT | lp->csr0);
	mutex_exit(&lp->reglock);
E 12
E 10
I 3

I 10
	DPRINTF(4, (CE_CONT, "!%s: returned", __func__));
E 10
	return (GEM_SUCCESS);
E 3
}

D 3
static void
E 3
I 3
static int
E 3
ae_set_media(struct gem_dev *dp)
{
D 12
	/* do nothing */
E 12
I 12
D 13
	/* EMPTY */
E 13
I 13
	struct ae_dev		*lp = dp->private;

	lp->do_polling =
	    (dp->speed == GEM_SPD_100) &&
	    (lp->chip->flags & CAP_CSR7) != 0;

E 13
E 12
I 3
	return (GEM_SUCCESS);
E 3
}

D 3
static void
E 3
I 3
static int
E 3
ae_start_chip(struct gem_dev *dp)
{
	int			i;
D 10
	uint16_t		val;
E 10
	struct init_block	*ibp = IBP_VADDR(dp);
D 10
	struct ae_dev		*lp = (struct ae_dev *)dp->private;
E 10
I 10
	struct ae_dev		*lp = dp->private;
E 10

	DPRINTF(1, (CE_CONT, "!%s: %s: called", dp->name, __func__));

	/* prepare initilization block for DMA. */
D 10
	ddi_dma_sync(dp->desc_dma_handle,
		(off_t) (((caddr_t)ibp) - (caddr_t) dp->rx_ring),
		sizeof(struct init_block), DDI_DMA_SYNC_FORDEV);
E 10
I 10
D 12
	(void) ddi_dma_sync(dp->desc_dma_handle,
	    (off_t)(((intptr_t)ibp) - (intptr_t)dp->rx_ring),
E 12
I 12
	gem_ioarea_dma_sync(dp,
	    (off_t)(((caddr_t)ibp) - dp->io_area),
E 12
	    sizeof (struct init_block), DDI_DMA_SYNC_FORDEV);
E 10

D 12
	/* load initialization block into nic */
E 12
	mutex_enter(&lp->reglock);
I 12

	/* load initialization block into nic */
E 12
	ae_csr_write(dp, CSR0, CSR0_INIT);

D 10
	/* wait for 10 mS to complete initialization.  */
E 10
I 10
	/* wait for 10 mS to complete initialization. */
E 10
	for (i = 0; (ae_csr_read(dp, CSR0) & CSR0_IDON) == 0; i++) {
		if (i > 1000) {
			cmn_err(CE_WARN,
D 10
			"!%s: %s: failed to load initialization block into nic",
				dp->name, __func__);
E 10
I 10
			    "!%s: %s: failed to load initialization block "
			    "into nic",
			    dp->name, __func__);
E 10
D 9
			goto x;
E 9
I 9
			mutex_exit(&lp->reglock);
			return (GEM_FAILURE);
E 9
		}
		drv_usecwait(10);
	}

	/* clear bogus interrupt and status bits */
	ae_csr_write(dp, CSR0, ae_csr_read(dp, CSR0) & CSR0_STAT);

	/* kick rx and tx */
	lp->csr0 = 0;
	if ((dp->misc_flag & GEM_NOINTR) == 0) {
		lp->csr0 |= CSR0_IENA;
	}
	ae_csr_write(dp, CSR0, CSR0_STRT | lp->csr0);
D 9
x:
E 9
I 9

E 9
	mutex_exit(&lp->reglock);
I 3

	return (GEM_SUCCESS);
E 3
}

static int
ae_stop_chip(struct gem_dev *dp)
{
D 10
	struct ae_dev	*lp = (struct ae_dev *)dp->private;
E 10
I 10
	struct ae_dev	*lp = dp->private;
E 10
	DPRINTF(1, (CE_CONT, "!%s: %s: called", dp->name, __func__));

	/* disable interrupts and stop nic */
	mutex_enter(&lp->reglock);
	lp->csr0 &= ~CSR0_IENA;
	ae_csr_write(dp, CSR0, CSR0_STOP | lp->csr0);
	mutex_exit(&lp->reglock);

	return (GEM_SUCCESS);
}

D 3
static void
E 3
I 3
static int
E 3
ae_get_stats(struct gem_dev *dp)
{
D 10
	struct ae_dev	*lp = (struct ae_dev *)dp->private;

E 10
D 9
	DPRINTF(4, (CE_CONT, "!%s: ae_get_stats: called", dp->name));
E 9
I 9
	DPRINTF(4, (CE_CONT, "!%s: %s: called", dp->name, __func__));
E 9
I 3
D 10

E 10
I 10
	/* do nothing */
E 10
	return (GEM_SUCCESS);
E 3
}

/*
 * discriptor  manupiration
 */
static int
ae_tx_desc_write(struct gem_dev *dp, int slot,
D 9
		ddi_dma_cookie_t *dmacookie, int frags, uint32_t flag)
E 9
I 9
D 10
		ddi_dma_cookie_t *dmacookie, int frags, uint64_t flag)
E 10
I 10
    ddi_dma_cookie_t *dmacookie, int frags, uint64_t flag)
E 10
E 9
{
I 10
#ifdef DEBUG_LEVEL
E 10
	int			i;
I 10
#endif
E 10
	struct tx_desc		*tdp;
	ddi_dma_cookie_t	*dcp;
	uint32_t		mark;
D 10
	struct ae_dev		*lp = (struct ae_dev *) dp->private;
E 10
I 10
D 12
#ifndef OS_PUTBACK
E 12
E 10
	int			curslot;
I 10
	int			n;
D 12
#endif
E 12
	struct ae_dev	*lp = dp->private;
E 10

#if DEBUG_LEVEL > 2
	cmn_err(CE_CONT,
D 9
		"!%s: %s: seqnum %d, slot %d, frags %d flag 0x%x",
E 9
I 9
D 10
		"!%s: %s: seqnum %d, slot %d, frags %d flag 0x%llx",
E 9
		dp->name, __func__, dp->tx_desc_tail, slot, frags, flag);
E 10
I 10
	    "!%s: %s: seqnum %d, slot %d, frags %d flag 0x%llx",
	    dp->name, __func__, dp->tx_desc_tail, slot, frags, flag);
E 10
	for (i = 0; i < frags; i++) {
		cmn_err(CE_CONT, "!%d: addr 0x%x, len 0x%x",
D 10
			i, dmacookie[i].dmac_address, dmacookie[i].dmac_size);
E 10
I 10
		    i, dmacookie[i].dmac_address, dmacookie[i].dmac_size);
E 10
	}
#endif
	/*
	 * write tx descriptor(s) in reversed order
	 */
D 9
	mark = TMD1_OWN | TMD1_ENP;
	if ((flag & GEM_TXFLAG_INTR) != 0) {
E 9
I 9
D 10
	mark = (TMD1_OWN | TMD1_ENP);
	if (flag & GEM_TXFLAG_INTR) {
E 10
I 10
	mark = TMD1_OWN | TMD1_ENP;
	if ((flag & GEM_TXFLAG_INTR) && (lp->chip->flags & CAP_CSR5)) {
E 10
E 9
		mark |= TMD1_LTINT;
	}
I 10

D 12
#ifdef OS_PUTBACK
	ASSERT(frags == 1);
	dcp = &dmacookie[0];
#else
E 12
E 10
	dcp = &dmacookie[frags - 1];
D 10
	for (i = frags - 1; i > 0; i--, dcp--) {
		curslot = SLOT(slot + i, TX_RING_SIZE);
E 10
I 10
	for (n = frags - 1; n > 0; n--, dcp--) {
		curslot = SLOT(slot + n, TX_RING_SIZE);
E 10

D 10
		tdp = &((struct tx_desc *)dp->tx_ring)[curslot];
E 10
I 10
		tdp = &TXDESC(dp->tx_ring)[curslot];
E 10
D 9
		tdp->tmd0 = LE32(dcp->dmac_address);
		tdp->tmd1 = LE32(mark | ((-dcp->dmac_size) & TMD1_BCNT));
E 9
I 9
		mark |= (-dcp->dmac_size) & TMD1_BCNT;
		tdp->tmd0 = LE_32(dcp->dmac_address);
D 10
		tdp->tmd1 = LE_32(mark);
E 10
E 9
		tdp->tmd2 = 0;
I 10
		tdp->tmd1 = LE_32(mark);
E 10
		mark = TMD1_OWN;
	}
D 10

E 10
I 10
D 12
#endif
E 12
E 10
	/*
	 * specify descriptor control flags for first fragment.
	 */
D 9
	if ((flag & GEM_TXFLAG_HEAD) != 0) {
E 9
I 9
	if (flag & GEM_TXFLAG_HEAD) {
E 9
		mark &= ~TMD1_OWN;
	}
I 9
	mark |= (TMD1_STP | ((-dcp->dmac_size) & TMD1_BCNT));
E 9
D 10
	tdp = &((struct tx_desc *)dp->tx_ring)[slot];
E 10
I 10

	tdp = &TXDESC(dp->tx_ring)[slot];
E 10
D 9
	tdp->tmd0 = LE32(dcp->dmac_address);
	tdp->tmd1 = LE32(mark | TMD1_STP | ((-dcp->dmac_size) & TMD1_BCNT));
E 9
I 9
	tdp->tmd0 = LE_32(dcp->dmac_address);
D 10
	tdp->tmd1 = LE_32(mark);
E 10
E 9
	tdp->tmd2 = 0;
I 10
	tdp->tmd1 = LE_32(mark);
E 10

	return (frags);
}

static void
ae_tx_start(struct gem_dev *dp, int start_slot, int nslots)
{
D 10
	struct ae_dev	*lp = (struct ae_dev *)dp->private;
E 10
I 10
	struct ae_dev	*lp = dp->private;
E 10

	if (nslots > 1) {
		gem_tx_desc_dma_sync(dp,
D 10
			SLOT(start_slot + 1, TX_RING_SIZE),
			nslots - 1, DDI_DMA_SYNC_FORDEV);
E 10
I 10
		    SLOT(start_slot + 1, TX_RING_SIZE),
		    nslots - 1, DDI_DMA_SYNC_FORDEV);
E 10
	}

D 9
	((struct tx_desc *) dp->tx_ring)[start_slot].tmd1 |= LE32(TMD1_OWN);
E 9
I 9
D 10
	((struct tx_desc *) dp->tx_ring)[start_slot].tmd1 |= LE_32(TMD1_OWN);
E 10
I 10
	TXDESC(dp->tx_ring)[start_slot].tmd1 |= LE_32(TMD1_OWN);
E 10
E 9

	gem_tx_desc_dma_sync(dp, start_slot, 1, DDI_DMA_SYNC_FORDEV);

	if (dp->mac_active) {
		/* kick Tx engine */
		mutex_enter(&lp->reglock);
		ae_csr_write(dp, CSR0, CSR0_TDMD | lp->csr0);
		mutex_exit(&lp->reglock);
	}
}

static void
ae_rx_desc_write(struct gem_dev *dp, int slot,
D 10
		ddi_dma_cookie_t *dmacookie, int frags)
E 10
I 10
	ddi_dma_cookie_t *dmacookie, int frags)
E 10
{
	struct rx_desc		*rdp;

D 10
	rdp = &((struct rx_desc *) dp->rx_ring)[slot];
E 10
I 10
	rdp = &RXDESC(dp->rx_ring)[slot];
E 10

D 9
	rdp->rmd0 = LE32(dmacookie->dmac_address);
	rdp->rmd1 = LE32(RMD1_OWN | ((-dmacookie->dmac_size) & RMD1_BCNT));
E 9
I 9
	rdp->rmd0 = LE_32(dmacookie->dmac_address);
D 10
	rdp->rmd1 = LE_32(RMD1_OWN | ((-dmacookie->dmac_size) & RMD1_BCNT));
E 10
E 9
	rdp->rmd2 = 0;
I 10
	rdp->rmd1 = LE_32(RMD1_OWN | ((-dmacookie->dmac_size) & RMD1_BCNT));
E 10
}

static uint_t
ae_tx_desc_stat(struct gem_dev *dp, int slot, int ndesc)
{
	uint_t		err = GEM_TX_DONE;
	uint32_t	tmd1;
	uint32_t	tmd2;
	struct tx_desc	*tdp;
D 10
	struct ae_dev	*lp = (struct ae_dev *) dp->private;
E 10
I 10
	struct ae_dev	*lp = dp->private;
E 10

	/* XXX - we must check last descripor of the packet. */
D 10
	tdp = &((struct tx_desc *)dp->tx_ring)[
					SLOT(slot + ndesc - 1, TX_RING_SIZE)];
D 9
	tmd1 = LE32(tdp->tmd1);
E 9
I 9
	tmd1 = LE_32(tdp->tmd1);
E 10
I 10
	tdp = &TXDESC(dp->tx_ring)[SLOT(slot + ndesc - 1, TX_RING_SIZE)];
	tmd1 = tdp->tmd1;
	tmd1 = LE_32(tmd1);
E 10
E 9

	DPRINTF(2, (CE_CONT, "!%s: %s: slot:%d ndesc:%d",
D 10
		dp->name, __func__, slot, ndesc));
E 10
I 10
	    dp->name, __func__, slot, ndesc));
E 10

D 9
	if ((tmd1 & TMD1_OWN) != 0) {
E 9
I 9
	if (tmd1 & TMD1_OWN) {
E 9
		/* not transmitted yet */
		return (0);
	}
D 9
	tmd2 = LE32(tdp->tmd2);
E 9
I 9
D 10
	tmd2 = LE_32(tdp->tmd2);
E 10
I 10
	tmd2 = tdp->tmd2;
	tmd2 = LE_32(tmd2);
E 10
E 9

	DPRINTF(2, (CE_CONT, "!%s: %s: tmd1:%b, tmd2:%b",
D 10
		dp->name, __func__, tmd1, TMD1_BITS, tmd2, TMD2_BITS));
E 10
I 10
	    dp->name, __func__, tmd1, TMD1_BITS, tmd2, TMD2_BITS));
E 10

D 9
	if ((tmd2 & TMD2_ANYERROR) != 0) {
E 9
I 9
	if (tmd2 & TMD2_ANYERROR) {
E 9
		dp->stats.errxmt++;
		if ((tmd2 & (TMD2_BUFF | TMD2_RTRY | TMD2_LCOL))
D 10
							== TMD2_BUFF) {
			cmn_err(CE_WARN, "!%s: %s: TMD2_BUFF set, tmd2:%b",
				dp->name, __func__, tmd2, TMD2_BITS);
		}
D 9
		if ((tmd2 & TMD2_UFLO) != 0) {
E 9
I 9
		else if (tmd2 & TMD2_UFLO) {
E 10
I 10
		    == TMD2_BUFF) {
			DPRINTF(1, (CE_WARN, "!%s: %s: TMD2_BUFF set, tmd2:%b",
			    dp->name, __func__, tmd2, TMD2_BITS));
			/* EMPTY */
		} else if (tmd2 & TMD2_UFLO) {
E 10
E 9
			dp->stats.underflow++;
			if ((lp->chip->flags & CAP_NOUFLO) == 0) {
				/* need to restart TX */
				err = GEM_TX_ERR;
			}
			DPRINTF(1, (CE_NOTE,
D 10
				"!%s: %s: UFLO set, tmd2:%b",
				dp->name, __func__, tmd2, TMD2_BITS));
		}
D 9
		if ((tmd2 & TMD2_LCOL) != 0) {
E 9
I 9
		else if (tmd2 & TMD2_LCOL) {
E 10
I 10
			    "!%s: %s: UFLO set, tmd2:%b",
			    dp->name, __func__, tmd2, TMD2_BITS));
		} else if (tmd2 & TMD2_LCOL) {
E 10
E 9
			dp->stats.xmtlatecoll++;
D 10
		}
D 9
		if ((tmd2 & (TMD2_LCAR | TMD2_RTRY)) == TMD2_LCAR) {
E 9
I 9
		else if ((tmd2 & (TMD2_LCAR | TMD2_RTRY)) == TMD2_LCAR) {
E 10
I 10
		} else if ((tmd2 & (TMD2_LCAR | TMD2_RTRY)) == TMD2_LCAR) {
E 10
E 9
			dp->stats.nocarrier++;
D 10
		}
D 9
		if ((tmd2 & TMD2_RTRY) != 0) {
E 9
I 9
		else if (tmd2 & TMD2_RTRY) {
E 10
I 10
		} else if (tmd2 & TMD2_RTRY) {
E 10
E 9
			dp->stats.excoll++;
			dp->stats.collisions += 16;
D 10
		}
I 9
		else {
E 10
I 10
		} else {
E 10
			dp->stats.xmit_internal_err++;
		}
E 9
D 10
	}
	else {
E 10
I 10
	} else {
E 10
D 9
		if ((tmd1 & TMD1_ONE) != 0) {
E 9
I 9
		if (tmd1 & TMD1_ONE) {
E 9
			dp->stats.first_coll++;
			dp->stats.collisions++;
D 10
		}
D 9
		else if ((tmd1 & TMD1_MORE) != 0) {
E 9
I 9
		else if (tmd1 & TMD1_MORE) {
E 10
I 10
		} else if (tmd1 & TMD1_MORE) {
E 10
E 9
			dp->stats.multi_coll++;
			dp->stats.collisions += (tmd2 & TMD2_TRC);
D 10
		}
D 9
		else if ((tmd1 & TMD1_DEF) != 0) {
E 9
I 9
		else if (tmd1 & TMD1_DEF) {
E 10
I 10
		} else if (tmd1 & TMD1_DEF) {
E 10
E 9
			dp->stats.defer++;
		}
	}

	return (err);
}

static uint64_t
ae_rx_desc_stat(struct gem_dev *dp, int slot, int ndesc)
{
	uint32_t	rmd2;
	uint32_t	rmd1;
I 12
	uint_t		len;
E 12
	struct rx_desc	*rdp;
D 10
	struct ae_dev	*lp = (struct ae_dev *)dp->private;
E 10

D 10
	rdp = &((struct rx_desc *)dp->rx_ring)[slot];
E 10
I 10
	rdp = &RXDESC(dp->rx_ring)[slot];
E 10

D 9
	rmd1 = LE32(rdp->rmd1);
	rmd2 = LE32(rdp->rmd2);
E 9
I 9
D 10
	rmd1 = LE_32(rdp->rmd1);
	rmd2 = LE_32(rdp->rmd2);
E 10
I 10
	rmd1 = rdp->rmd1;
	rmd1 = LE_32(rmd1);
E 10
E 9

	DPRINTF(2, (CE_CONT, "!%s: %s: rmd1:%b, rmd2:%x",
D 10
		dp->name, __func__, rmd1, RMD1_BITS, rmd2));
E 10
I 10
	    dp->name, __func__, rmd1, RMD1_BITS, LE_32(rdp->rmd2)));
E 10

D 9
	if ((rmd1 & RMD1_OWN) != 0)  {
E 9
I 9
	if (rmd1 & RMD1_OWN)  {
E 9
		return (0);
	}
I 10
	rmd2 = rdp->rmd2;
	rmd2 = LE_32(rmd2);
E 10
D 9
	if ((rmd1 & RMD1_ERR) != 0) {
E 9
I 9

	if (rmd1 & RMD1_ERR) {
E 9
		dp->stats.errrcv++;

D 9
		if ((rmd1 & RMD1_FRAM) != 0) {
E 9
I 9
		if (rmd1 & RMD1_FRAM) {
E 9
			dp->stats.frame++;
D 10
		}
D 9
		if ((rmd1 & RMD1_OFLO) != 0) {
E 9
I 9
		else if (rmd1 & RMD1_OFLO) {
E 10
I 10
		} else if (rmd1 & RMD1_OFLO) {
E 10
E 9
			dp->stats.overflow++;
D 10
		}
D 9
		if ((rmd1 & RMD1_CRC) != 0) {
E 9
I 9
		else if (rmd1 & RMD1_CRC) {
E 10
I 10
		} else if (rmd1 & RMD1_CRC) {
E 10
E 9
			dp->stats.crc++;
D 10
		}
D 9
#ifdef notdef
		if ((rmd1 & RMD1_BUFF) != 0) {
E 9
I 9
		else {
E 10
I 10
		} else {
E 10
			/* RMD1_BUFF, RMD1_BPE */
			dp->stats.rcv_internal_err++;
E 9
		}
I 12
		DPRINTF(2, (CE_CONT, "!%s: %s: rmd1:%b, rmd2:%x",
		    dp->name, __func__, rmd1, RMD1_BITS, LE_32(rdp->rmd2)));
E 12
D 9
		if ((rmd1 & RMD1_BPE) != 0) {
		}
#endif
E 9
		return (GEM_RX_ERR | GEM_RX_DONE);
	}

D 12
	return (GEM_RX_DONE | ((rmd2 & RMD2_MCNT) - ETHERFCSL));
E 12
I 12
	len = (rmd2 & RMD2_MCNT);

	if (len > ETHERMAX + ETHERFCSL) {
		dp->stats.errrcv++;
		dp->stats.frame_too_long++;
		DPRINTF(2, (CE_CONT, "!%s: %s: rmd1:%b, rmd2:%x",
		    dp->name, __func__, rmd1, RMD1_BITS, LE_32(rdp->rmd2)));
		return (GEM_RX_ERR | GEM_RX_DONE);
	} else if (len < ETHERFCSL) {
		dp->stats.errrcv++;
		dp->stats.runt++;
		DPRINTF(2, (CE_CONT, "!%s: %s: rmd1:%b, rmd2:%x",
		    dp->name, __func__, rmd1, RMD1_BITS, LE_32(rdp->rmd2)));
		return (GEM_RX_ERR | GEM_RX_DONE);
	}


	return (GEM_RX_DONE | (len - ETHERFCSL));
E 12
}

static void
D 10
ae_tx_desc_init(struct gem_dev *dp, int slot)	/* done */
E 10
I 10
ae_tx_desc_init(struct gem_dev *dp, int slot)
E 10
{
D 10
	bzero(&((struct tx_desc *)dp->tx_ring)[slot], sizeof(struct tx_desc));
E 10
I 10
	bzero(&TXDESC(dp->tx_ring)[slot], sizeof (struct tx_desc));
E 10
}

static void
D 10
ae_rx_desc_init(struct gem_dev *dp, int slot)	/* done */
E 10
I 10
ae_rx_desc_init(struct gem_dev *dp, int slot)
E 10
{
D 10
	bzero(&((struct rx_desc *) dp->rx_ring)[slot], sizeof(struct rx_desc));
E 10
I 10
	bzero(&RXDESC(dp->rx_ring)[slot], sizeof (struct rx_desc));
E 10
}

/*
 * Device depend interrupt handler
 */
D 10
static u_int
E 10
I 10
static uint_t
E 10
ae_interrupt(struct gem_dev *dp)
{
	boolean_t	need_to_reset = B_FALSE;
	uint16_t	csr0;
I 9
D 10
	uint16_t	ack;
E 9
	uint16_t	csr7 = 0;
E 10
I 10
	uint16_t	csr7;
	uint_t		restart_tx = 0;
	struct ae_dev	*lp = dp->private;
E 10

D 10
	u_int		restart_tx = 0;
	struct ae_dev	*lp = (struct ae_dev *)dp->private;

E 10
	mutex_enter(&lp->reglock);
D 10
	
E 10
I 10

E 10
	csr0 = ae_csr_read(dp, CSR0);
D 10
#ifdef GEM_CONFIG_POLLING
E 10
I 10

E 10
D 9
	if ((lp->chip->flags & CAP_CSR7) != 0) {
E 9
I 9
	if (lp->chip->flags & CAP_CSR7) {
E 9
		csr7 = ae_csr_read(dp, CSR7);
I 10
	} else {
		csr7 = 0;
E 10
	}
D 10
#endif
	DPRINTF(2, (CE_CONT,"!%s: time:%d %s: csr0:0x%b, csr7:0x%b",
		dp->name, ddi_get_lbolt(), __func__,
		csr0, CSR0_BITS, csr7, CSR7_BITS));
E 10

I 10
	DPRINTF(2, (CE_CONT, "!%s: time:%d %s: csr0:0x%b, csr7:0x%b",
	    dp->name, ddi_get_lbolt(), __func__,
	    csr0, CSR0_BITS, csr7, CSR7_BITS));

E 10
	if (((csr0 & ~lp->csr3) & CSR0_ISR) == 0 &&
D 10
	     (csr7 & (CSR7_STINT | CSR7_STINTE)) !=
				(CSR7_STINT | CSR7_STINTE)) {
E 10
I 10
	    (csr7 & (CSR7_STINT | CSR7_STINTE))
	    != (CSR7_STINT | CSR7_STINTE)) {
E 10
		/* not for us */
		mutex_exit(&lp->reglock);
		return (DDI_INTR_UNCLAIMED);
	}

D 9
	/*
D 3
	 * clear all interrput bits and disable interrupt for a while.
E 3
I 3
	 * clear all interrput bits and disable interrupts for a while.
E 3
	 */
	ae_csr_write(dp, CSR0, csr0 & CSR0_ISR);
E 9
I 9
D 10
	/* extract interrupt status bits in csr0 */
	ack = csr0 & CSR0_ISR;
E 10
I 10
	/* clear all interrputs */
	ae_csr_write(dp, CSR0, csr0);
E 10

D 10
	if (!dp->mac_active) {
		/* clear all interrput bits, and diable interrupts */
		ae_csr_write(dp, CSR0, ack);
		FLSH(dp);
		mutex_exit(&lp->reglock);

		/* ack to all interrupts */
		return (DDI_INTR_CLAIMED);
	}

	/* clear all interrput bits,*/
#ifdef CONFIG_OPT_IO
	if ((dp->misc_flag & GEM_NOINTR) == 0) {
		/* enable interrupts */
		ack |= lp->csr0;
	}
#endif
	ae_csr_write(dp, CSR0, ack);

E 9
#ifdef GEM_CONFIG_POLLING
D 2
	if ((lp->chip->flags && CAP_CSR7) != 0 && (csr7 & CSR7_STINT) != 0) {
E 2
I 2
D 9
	if ((lp->chip->flags & CAP_CSR7) != 0 && (csr7 & CSR7_STINT) != 0) {
E 9
I 9
	if ((lp->chip->flags & CAP_CSR7) && (csr7 & CSR7_STINT)) {
E 10
I 10
	if (csr7 & CSR7_STINT) {
E 10
		/* also clear timer interrupt */
E 9
E 2
		ae_csr_write(dp, CSR7, csr7);
	}
D 10
#endif
	/* flush write buffers  */
E 10
I 10
D 13
#ifdef notdef
	/* flush write buffers */
E 10
	FLSH(dp);
I 10
#endif
E 13
E 10
	mutex_exit(&lp->reglock);

	if (!dp->mac_active) {
D 10
		/* still inhibit interrupt */
I 9
#ifdef CONFIG_OPT_IO
E 10
I 10
D 12
		/* inhibit interrupta */
E 12
I 12
		/* inhibit interrupts */
		mutex_enter(&lp->reglock);
E 12
E 10
		ae_csr_write(dp, CSR0, 0);
I 12
		mutex_exit(&lp->reglock);
E 12
D 10
#endif
E 10
I 10

E 10
E 9
		/* ack to all interrupts */
		return (DDI_INTR_CLAIMED);
	}

D 10
#ifdef GEM_CONFIG_POLLING
	if (dp->poll_interval != lp->last_poll_interval &&
D 9
	   (lp->chip->flags & CAP_CSR7) != 0) {
E 9
I 9
	   (lp->chip->flags & CAP_CSR7)) {
E 10
I 10
#ifdef CONFIG_POLLING
D 13
	if (lp->do_polling && dp->poll_interval != lp->last_poll_interval &&
	    (lp->chip->flags & CAP_CSR7)) {
E 13
I 13
	if (lp->do_polling && dp->poll_interval != lp->last_poll_interval) {
E 13
E 10
E 9
		mutex_enter(&lp->reglock);
		/*
		 * It's time to check tx and rx statistics
		 */
D 9
		if (dp->poll_interval != 0) {
E 9
I 9
		if (dp->poll_interval) {
I 10
			uint32_t	val;
E 10
E 9
			/* polling mode */
I 10

E 10
			/* mask rx and tx interrupts */
D 10
			lp->csr3 |= (CSR3_RINTM | CSR3_TINTM);
E 10
I 10
			lp->csr3 |= CSR3_RINTM | CSR3_TINTM;
E 10
D 9
			ae_csr_write(dp, CSR3, lp->csr3);
E 9

			/* compute and set software timer interval */
D 10
			ae_bcr_write(dp, STVAL, dp->poll_interval/12);
E 10
I 10
			val = dp->poll_interval/12800;
			val = max(val, 1);
			val = min(val, 0xffff);
			ae_bcr_write(dp, STVAL, (uint16_t)val);
E 10

			/* enable software interval timer */
			lp->csr7 |= CSR7_STINTE;
D 9
			ae_csr_write(dp, CSR7, lp->csr7);
E 9

			/* pretend as we were interrupted from polling timer */
			csr7 |= CSR7_STINT;
D 9

		}
		else {
E 9
I 9
		} else {
E 9
			/* normal mode */
			/* enable rx and tx interrupts */
			lp->csr3 &= ~(CSR3_RINTM | CSR3_TINTM);
D 9
			ae_csr_write(dp, CSR3, lp->csr3);
E 9

			/* disable software interval timer interrupt */
			lp->csr7 &= ~CSR7_STINTE;
D 9
			ae_csr_write(dp, CSR7, lp->csr7);
E 9
		}
I 9
		ae_csr_write(dp, CSR3, lp->csr3);
		ae_csr_write(dp, CSR7, lp->csr7);
E 9
		mutex_exit(&lp->reglock);
I 10

		lp->last_poll_interval = dp->poll_interval;
E 10
D 9

E 9
	}
D 10
	lp->last_poll_interval = dp->poll_interval;
E 10

D 9
	if ((csr7 & CSR7_STINT) != 0) {
E 9
I 9
	if (csr7 & CSR7_STINT) {
E 9
		/* force to process ROK and TOK */
		csr0 |= (CSR0_RINT | CSR0_TINT);
	}
D 10
#endif /* GEM_CONFIG_POLLING */
E 10
I 10
#endif /* CONFIG_POLLING */
E 10

D 9
	if ((csr0 & CSR0_RINT) != 0) {
		gem_receive(dp);
E 9
I 9
	if (csr0 & CSR0_RINT) {
		(void) gem_receive(dp);
E 9
	}

D 9
	if ((csr0 & CSR0_TINT) != 0) {
E 9
I 9
	if (csr0 & CSR0_TINT) {
E 9
		if (gem_tx_done(dp)) {
			restart_tx = INTR_RESTART_TX;
		}
	}

I 12
	if (csr0 & CSR0_IDON) {
		need_to_reset = B_TRUE;
		DPRINTF(-2, (CE_CONT, "!%s: time:%d %s: csr0:0x%b, csr7:0x%b",
		    dp->name, ddi_get_lbolt(), __func__,
		    csr0, CSR0_BITS, csr7, CSR7_BITS));
	}

E 12
D 9
	if ((csr0 & (CSR0_BABL | CSR0_MERR | CSR0_MISS | CSR0_TXON | CSR0_RXON))
		!= (CSR0_TXON | CSR0_RXON)) {
E 9
I 9
#define	CSR0_HWERR	(CSR0_BABL | CSR0_MERR | CSR0_MISS)
	if ((csr0 & (CSR0_HWERR | CSR0_TXON | CSR0_RXON))
D 10
					!= (CSR0_TXON | CSR0_RXON)) {
E 10
I 10
	    != (CSR0_TXON | CSR0_RXON)) {
E 10
E 9
D 12
		cmn_err(CE_WARN, "!%s: hardware error: csr0:%b",
D 10
			dp->name, csr0, CSR0_BITS);
E 10
I 10
		    dp->name, csr0, CSR0_BITS);
E 12
I 12
		DPRINTF(-2, (CE_CONT, "!%s: hardware error: csr0:%b",
		    dp->name, csr0, CSR0_BITS));
E 12
E 10
		need_to_reset = B_TRUE;
	}
I 9
#undef CSR0_HWERR
E 9

	if (need_to_reset) {
D 5
		gem_restart_nic(dp, B_TRUE);
E 5
I 5
D 10
		gem_restart_nic(dp, GEM_RESTART_KEEP_BUF);
E 10
I 10
		(void) gem_restart_nic(dp, GEM_RESTART_KEEP_BUF);
E 10
E 5

		restart_tx = INTR_RESTART_TX;
	}
D 9

E 9
I 9
D 10
#ifndef CONFIG_OPT_IO
E 9
	if ((dp->misc_flag & GEM_NOINTR) == 0) {
		/* enable interrupts again */
		mutex_enter(&lp->reglock);
		ae_csr_write(dp, CSR0, lp->csr0);
		mutex_exit(&lp->reglock);
	}
D 9

E 9
I 9
#endif
E 10
I 10

E 10
E 9
	return (DDI_INTR_CLAIMED | restart_tx);
}

D 10
/* 
E 10
I 10
/*
E 10
 * MII Interfaces
 */
static void
ae_mii_sync(struct gem_dev *dp)
{
	/* do nothing */
}

static uint16_t
ae_mii_read(struct gem_dev *dp, uint_t index)
{
	uint16_t	val;
D 10
	struct ae_dev	*lp = (struct ae_dev *)dp->private;
E 10
I 10
	struct ae_dev	*lp = dp->private;
E 10

	mutex_enter(&lp->reglock);
	ae_bcr_write(dp, MIIADDR,
D 10
		(dp->mii_phy_addr << MIIADDR_ADDR_SHIFT) | index);
E 10
I 10
	    (dp->mii_phy_addr << MIIADDR_ADDR_SHIFT) | index);
E 10
	val = ae_bcr_read(dp, MIIMDR);
	mutex_exit(&lp->reglock);

	return (val);
}

static void
ae_mii_write(struct gem_dev *dp, uint_t index, uint16_t val)
{
	uint16_t	reg;
D 10
	struct ae_dev	*lp = (struct ae_dev *) dp->private;
E 10
I 10
	struct ae_dev	*lp = dp->private;
E 10

I 12
	DPRINTF(10, (CE_CONT, "!%s: %s: reg:%d, val:0x%04x",
	    dp->name, __func__, index, val));

E 12
	mutex_enter(&lp->reglock);
	switch (index) {
	default:
		ae_bcr_write(dp, MIIADDR,
D 10
			(dp->mii_phy_addr << MIIADDR_ADDR_SHIFT) | index);
E 10
I 10
		    (dp->mii_phy_addr << MIIADDR_ADDR_SHIFT) | index);
E 10
		ae_bcr_write(dp, MIIMDR, val);
D 12
		break;
E 12

I 12
		DPRINTF(10, (CE_CONT, "!%s: %s: read back: val:0x%04x",
		    dp->name, __func__, ae_bcr_read(dp, MIIMDR)));
		break;
#ifdef CONFIG_ANAS
E 12
	case MII_CONTROL:
I 5
		/*
D 10
		 * We cannot directly modify bits in MII_CONTROL register.
		 * We need to modify bits in MIICAS register, instead of
E 10
I 10
		 * As we cannot directly access MII_CONTROL
		 * register, we use MIICAS register, instead of
E 10
		 * MII_CONTROL register.
		 */
E 5

D 5
		/* We must MII_CONTROL register by using following bits */

E 5
		/* disable AN setup first */
		reg = ae_bcr_read(dp, MIICAS) & ~MIICAS_XPHYRST;
		ae_bcr_write(dp, MIICAS, reg | MIICAS_DANAS);

D 10
		reg &= ~(MIICAS_DANAS |
			 MIICAS_XPHYFD | MIICAS_XPHYSP | MIICAS_XPHYANE);
E 10
I 10
		reg &= ~(MIICAS_DANAS | MIICAS_XPHYFD |
		    MIICAS_XPHYSP | MIICAS_XPHYANE);
E 10

D 9
		if ((val & MII_CONTROL_RESET) != 0) {
E 9
I 9
		if (val & MII_CONTROL_RESET) {
E 9
			reg |= MIICAS_XPHYRST;
		}
D 9
		if ((val & (MII_CONTROL_ANE)) != 0) {
E 9
I 9
		if (val & (MII_CONTROL_ANE)) {
E 9
			reg |= MIICAS_XPHYANE;
		}
D 9
		if ((val & MII_CONTROL_FDUPLEX) != 0) {
E 9
I 9
		if (val & MII_CONTROL_FDUPLEX) {
E 9
			reg |= MIICAS_XPHYFD;
		}
		if ((val & MII_CONTROL_SPEED) == MII_CONTROL_100MB) {
			reg |= MIICAS_XPHYSP;
		}
		ae_bcr_write(dp, MIICAS, reg);
		break;
I 12
D 13
#endif
E 13
I 13
#endif /* CONFIG_ANAS */
E 13
E 12
	}
	mutex_exit(&lp->reglock);
}

static uint16_t
ae_nomii_read(struct gem_dev *dp, uint_t index)
{
	uint16_t	ret;
	uint16_t	val;
D 10
	struct ae_dev	*lp = (struct ae_dev *)dp->private;
E 10
I 10
	struct ae_dev	*lp = dp->private;
E 10

	ret = 0;
	switch (index) {
	case MII_CONTROL:
		ret = lp->bmcr;
		break;
I 3

E 3
	case MII_STATUS:
D 3
		/* TODO: should return proper link status */
E 3
I 3
D 7
		/* TODO: we should return proper current link status */
E 7
I 7
D 10
		/* TODO: we should return proper current link status. */
E 10
E 7
E 3
		ret = lp->bmsr;
I 7
D 10
#ifdef NEVER
E 7
		mutex_enter(&lp->reglock);
		val = ae_bcr_read(dp, LED0);
		if (val != LED0_DEFAULT) {
E 10
I 10

		if (lp->check_link_state) {
			mutex_enter(&lp->reglock);
			val = ae_bcr_read(dp, LED0);
			if (val != LED0_DEFAULT) {
				ret |= MII_STATUS_LINKUP;
			}
			mutex_exit(&lp->reglock);
			DPRINTF(1, (CE_CONT, "!%s: %s: LED0:%b",
			    dp->name, __func__, val, LED_BITS));
		} else {
			/*
D 13
			 * XXX - As VMware seems to have a bug that LED_LEDOUT
			 * bit in LED0 register doesn't emulate current link
			 * status, we have no way to know current link status.
E 13
I 13
			 * XXX - VMware doesn't seem to emulate  LED_LEDOUT
			 * bit in LED0 register, which indicates the  current
			 * link status.
E 13
			 */
E 10
			ret |= MII_STATUS_LINKUP;
		}
D 10
		mutex_exit(&lp->reglock);
		DPRINTF(5, (CE_CONT, "!%s: %s: LED0:%b",
			dp->name, __func__, val, LED_BITS));
I 7
#else
		/*
		 * XXX - As VMware seem to have a bug that LED_LEDOUT bit
		 * in LED0 register doesn't emulate current link status,
		 * we have no way to know current link status.
		 */
		ret |= MII_STATUS_LINKUP;
#endif
E 10
I 10

E 10
E 7
		break;

	case MII_AN_ADVERT:
		ret = lp->adv;
		break;
	}
	return (ret);
}

static void
ae_nomii_write(struct gem_dev *dp, uint_t index, uint16_t val)
{
D 10
	struct ae_dev    *lp = (struct ae_dev *)dp->private;
E 10
I 10
	struct ae_dev	*lp = dp->private;
E 10

	switch (index) {
	case MII_CONTROL:
		lp->bmcr = val & ~MII_CONTROL_RESET;
		break;

	case MII_AN_ADVERT:
		lp->adv = val;
		break;

	default:
		cmn_err(CE_WARN,
D 10
		"!%s: %s: writing to register %d in phy isn't permitted.",
			dp->name, __func__, index);
E 10
I 10
		    "!%s: %s: writing to register %d in phy isn't permitted.",
		    dp->name, __func__, index);
E 10
		break;
	}
}

static int
D 9
ae_mii_init(struct gem_dev *dp)
E 9
I 9
ae_mii_probe(struct gem_dev *dp)
E 9
{
	uint16_t	val;
D 10
	int		ret;
	struct ae_dev	*lp = (struct ae_dev *)dp->private;
E 10
I 10
	struct ae_dev	*lp = dp->private;
E 10

	if ((lp->chip->flags & CAP_MII) == 0) {
I 10
		/*
		 * prepare for MII PHY emulation
		 */

		/* We don't have a MII phy. No need to scan it */
		dp->mii_phy_addr = -1;

E 10
		lp->bmsr = MII_STATUS_10;
D 9
		if ((lp->chip->flags & CAP_FDX) != 0) {
E 9
I 9
		if (lp->chip->flags & CAP_FDX) {
E 9
			lp->bmsr |= MII_STATUS_10_FD;
		}
D 10
		dp->gc.gc_mii_read  = &ae_nomii_read;
E 10
I 10
		dp->gc.gc_mii_read = &ae_nomii_read;
E 10
		dp->gc.gc_mii_write = &ae_nomii_write;
	}

D 9
	if (gem_mii_init_default(dp) != GEM_SUCCESS) {
E 9
I 9
D 10
	if (gem_mii_probe_default(dp) != GEM_SUCCESS) {
E 9
		return (GEM_FAILURE);
	}
E 10
I 10
	return (gem_mii_probe_default(dp));
}
E 10

I 10
static int
ae_mii_init(struct gem_dev *dp)
{
	uint16_t	val;
	struct ae_dev	*lp = dp->private;

E 10
	mutex_enter(&lp->reglock);

D 12
	/* enable automatic media selection */
	ae_bcr_write(dp, MC, ae_bcr_read(dp, MC) | MC_ASEL);

E 12
D 10
	/* reset GPSI bit in test register 1 */
	val = ae_csr_read(dp, 124) & ~0x0010;
	ae_csr_write(dp, 124, val);

E 10
D 9
	if ((lp->chip->flags & CAP_MII) != 0) {
E 9
I 9
	if (lp->chip->flags & CAP_MII) {
I 12
		/* force to select MII port */
		ae_csr_write(dp, CSR15,
		    (ae_csr_read(dp, CSR15) & ~CSR15_PORTSEL)
		    | CSR15_PORTSEL_MII);
		ae_bcr_write(dp, MC, ae_bcr_read(dp, MC) & ~MC_ASEL);
#ifdef CONFIG_ANAS
E 12
E 9
D 10
		/* enable/disable MII auto polling */
E 10
I 10
		/* For MII media, enable MII auto polling */
E 10
		ae_bcr_write(dp, MIICAS,
D 10
				ae_bcr_read(dp, MIICAS) | MIICAS_APEP);
	}
	else {
		/* non-MII media, we must setup duplex mode manually */
E 10
I 10
D 12
		    ae_bcr_read(dp, MIICAS) | MIICAS_APEP);
E 12
I 12
		    (ae_bcr_read(dp, MIICAS) & ~MIICAS_XPHYRST)
		    | MIICAS_APEP);
#else
		/* disable AN auto setup, enable MII auto polling */
		ae_bcr_write(dp, MIICAS, 
		    (ae_bcr_read(dp, MIICAS) & ~MIICAS_XPHYRST)
		    | MIICAS_APEP | MIICAS_DANAS);
#endif
E 12
	} else {
I 12
		/* enable automatic media selection */
		ae_bcr_write(dp, MC, ae_bcr_read(dp, MC) | MC_ASEL);

E 12
		/* For non-MII media, we must setup duplex mode manually */
E 10
D 9
		ASSERT(dp->mii_fixedmode);
E 9
I 9
		ASSERT(!dp->anadv_autoneg);
E 9
		val = ae_bcr_read(dp, FDC) & ~(FDC_AUIFD | FDC_FDEN);
		if (dp->full_duplex) {
D 10
			val |= (FDC_AUIFD | FDC_FDEN);
E 10
I 10
			val |= FDC_AUIFD | FDC_FDEN;
E 10
		}
		ae_bcr_write(dp, FDC, val);
	}

	mutex_exit(&lp->reglock);

	return (GEM_SUCCESS);
}

/* ======================================================== */
/*
 * OS depend (device driver kernel interface) routine
 */
/* ======================================================== */
static int
ae_attach_chip(struct gem_dev *dp)
{
	int			i;
	uint32_t		val;
	uint32_t		rev;
	uint8_t			*mac;
	struct chip_info	*p;
D 10
	static uint8_t		zeros[] = {0,0,0,0,0,0};
	struct ae_dev	*lp = (struct ae_dev *) dp->private;
E 10
I 10
	static uint8_t		zeros[] = {0, 0, 0, 0, 0, 0 };
	struct ae_dev		*lp = dp->private;
E 10

	DPRINTF(1, (CE_CONT, "!%s: %s: called", dp->name, __func__));

	mutex_enter(&lp->reglock);

	/*
	 * read mac address from EEPROM
	 */
	mac = &dp->dev_addr.ether_addr_octet[0];
D 9
	for (i = 0; i < ETHERADDRL; i +=4) {
		val = INL(dp, APROM + i);
		mac[i]     = (uint8_t) val;
		mac[i + 1] = (uint8_t) (val >> (8*1));
		mac[i + 2] = (uint8_t) (val >> (8*2));
		mac[i + 3] = (uint8_t) (val >> (8*3));
	}
E 9

D 9
	if ((mac[0] & 1) != 0 ||
	    bcmp(mac, zeros, ETHERADDRL) == 0) {
E 9
I 9
	val = INL(dp, APROM);
D 10
	mac[0] = (uint8_t) val;
	mac[1] = (uint8_t) (val >> (8*1));
	mac[2] = (uint8_t) (val >> (8*2));
	mac[3] = (uint8_t) (val >> (8*3));
E 10
I 10
	mac[0] = (uint8_t)(val >> (8*0));
	mac[1] = (uint8_t)(val >> (8*1));
	mac[2] = (uint8_t)(val >> (8*2));
	mac[3] = (uint8_t)(val >> (8*3));
E 10

	val = INL(dp, APROM + 4);
D 10
	mac[4] = (uint8_t) val;
	mac[5] = (uint8_t) (val >> (8*1));
E 10
I 10
	mac[4] = (uint8_t)(val >> (8*0));
	mac[5] = (uint8_t)(val >> (8*1));
E 10

	if ((mac[0] & 1) || bcmp(mac, zeros, ETHERADDRL) == 0) {
E 9
		/* factory address in eeprom is corrupted */
I 10
D 12
#ifdef OS_PUTBACK
		return (GEM_FAILURE);
#else
E 12
E 10
		gem_generate_macaddr(dp, mac);
I 10
D 12
#endif
E 12
E 10
	}

D 10
	rev = (((ae_csr_read(dp, 89) << 16) | ae_csr_read(dp, 88))
			>> CSR88_PARTID_SHIFT) & CSR88_PARTID_MASK;
E 10
I 10
	rev = (ae_csr_read(dp, CSR89) << 16) | ae_csr_read(dp, CSR88);
	rev = (rev >> CSR88_PARTID_SHIFT) & CSR88_PARTID_MASK;
E 10

	for (i = 0, p = chiptable; i < CHIPTABLESIZE; i++, p++) {
		if (p->partid == rev) {
			/* found */
			cmn_err(CE_CONT, "!%s: partid: 0x%04x %s",
D 10
				dp->name, p->partid, p->name);
E 10
I 10
			    dp->name, p->partid, p->name);
E 10
			goto chip_found;
		}
	}

	/* Not found */
	cmn_err(CE_WARN, "!%s: %s: wrong partid: 0x%x",
D 10
		dp->name, __func__, rev);
E 10
I 10
	    dp->name, __func__, rev);
E 10
	return (GEM_FAILURE);

chip_found:
	lp->chip = p;

I 12
#if DEBUG_LEVEL > 5
E 12
D 10
	if ((p->flags & CAP_MII) == 0) {
		/* no need to scan phy */
		dp->mii_phy_addr = -1;
	}

E 10
	/* enable LED program */
	ae_bcr_write(dp, MC, ae_bcr_read(dp, MC) | MC_LEDPE);

D 9
	/* dump LED configurations */
E 9
I 9
	/* dump LED configuration */
E 9
D 12
#if DEBUG_LEVEL > 5
E 12
	for (i = 0; i < 4; i++) {
		val = ae_bcr_read(dp, LED0 + i);
		cmn_err(CE_CONT, "!%s: LED%d:%b", dp->name, i, val, LED_BITS);
	}
I 12
	ae_bcr_write(dp, MC, ae_bcr_read(dp, MC) & ~MC_LEDPE);
E 12
#endif
	mutex_exit(&lp->reglock);
D 12

D 9
	if (!(dp->anadv_100fdx && dp->anadv_100hdx &&
	      dp->anadv_10fdx && dp->anadv_10hdx)) {
		cmn_err(CE_NOTE,
		"!%s: pcnet doesn't support changing advertise register",
			dp->name);
		dp->anadv_100fdx = B_TRUE;
		dp->anadv_100hdx = B_TRUE;
		dp->anadv_10fdx  = B_TRUE;
		dp->anadv_10hdx  = B_TRUE;
	}
E 9
I 9
	/* pcnet doesn't support changing advertise register */
E 12
I 12
#ifdef CONFIG_ANAS
D 13
	/* pcnet doesn't support changing advertise register wint ANAS */
E 13
I 13
	/* pcnet doesn't support changing advertise register with ANAS */
E 13
E 12
	dp->mii_advert_ro = B_TRUE;
E 9
D 12

E 12
I 12
#endif
E 12
I 9
D 10
#ifdef GEM_CONFIG_VLAN
E 10
I 10
	lp->check_link_state =
	    gem_prop_get_int(dp, "check-link-state", 0) != 0;
	DPRINTF(1, (CE_CONT, "%s: %s: check-link-state:%d",
	    dp->name, __func__, lp->check_link_state));

D 13
#ifdef CONFIG_POLLING
	lp->do_polling =
	    gem_prop_get_int(dp, "polling", 0) != 0;
#endif

#ifdef NEVER /* GEM_CONFIG_VLAN */
E 13
I 13
#ifdef NEVER /* GEM_CONFIG_GLDv3 */
E 13
	/* VLAN is not supported */
E 10
E 9
	dp->misc_flag |= GEM_VLAN_SOFT;
D 9

E 9
I 9
#endif
I 13
	dp->misc_flag |= GEM_POLL_RXONLY;

E 13
E 9
	DPRINTF(1, (CE_CONT, "!%s: %s: done", dp->name, __func__));

	return (GEM_SUCCESS);	/* currently return code is not used. */
}

static int
aeattach(dev_info_t *dip, ddi_attach_cmd_t cmd)
{
D 10
	int			i;
E 10
	ddi_acc_handle_t	conf_handle;
	int			vid;
	int			did;
	int			revid;
	int			unit;
	const char		*drv_name;
	struct gem_dev		*dp;
	void			*base;
	ddi_acc_handle_t	regs_handle;
	struct gem_conf		*gcp;
	struct ae_dev		*lp;
	uint32_t		ilr;

	unit = ddi_get_instance(dip);
	drv_name = ddi_driver_name(dip);
	DPRINTF(3, (CE_CONT, "!%s%d: %s: called", drv_name, unit, __func__));

	/*
	 * Common routine after power-on
	 */

	/* fix config registers */
	if (pci_config_setup(dip, &conf_handle) != DDI_SUCCESS) {
		cmn_err(CE_WARN, "!%s%d: pci_config_setup failed",
D 10
			drv_name, unit);
E 10
I 10
		    drv_name, unit);
E 10
		goto err;
	}

	pci_config_put16(conf_handle, PCI_CONF_COMM,
D 10
		pci_config_get16(conf_handle, PCI_CONF_COMM)
			| PCI_COMM_IO | PCI_COMM_MAE | PCI_COMM_ME);
E 10
I 10
	    pci_config_get16(conf_handle, PCI_CONF_COMM) |
	    PCI_COMM_IO | PCI_COMM_MAE | PCI_COMM_ME);
E 10

	/* ensure D0 mode */
	(void) gem_pci_set_power_state(dip, conf_handle, PCI_PMCSR_D0);

	vid = pci_config_get16(conf_handle, PCI_CONF_VENID);
	did = pci_config_get16(conf_handle, PCI_CONF_DEVID);
	revid = pci_config_get8(conf_handle, PCI_CONF_REVID);
	ilr = pci_config_get32(conf_handle, PCI_CONF_ILINE);
I 10
#ifdef lint
	vid = vid;
	did = did;
	ilr = ilr;
#endif
E 10
	DPRINTF(0, (CE_CONT, "!%s%d: ilr 0x%08x", drv_name, unit, ilr));

	pci_config_teardown(&conf_handle);

	switch (cmd) {
	case DDI_RESUME:
		return (gem_resume(dip));

	case DDI_ATTACH:
		/*
		 * Map in the device registers.
		 */
		if (gem_pci_regs_map_setup(dip,
I 9
#ifdef MAP_MEM
D 10
			PCI_ADDR_MEM32, PCI_ADDR_MASK,
E 10
I 10
		    PCI_ADDR_MEM32, PCI_ADDR_MASK,
E 10
#else
E 9
D 10
			PCI_ADDR_IO, PCI_ADDR_MASK,
E 10
I 10
		    PCI_ADDR_IO, PCI_ADDR_MASK,
E 10
I 9
#endif
E 9
D 10
			&ae_dev_attr,
			(caddr_t *)&base, &regs_handle) != DDI_SUCCESS) {
E 10
I 10
		    &ae_dev_attr,
		    (void *)&base, &regs_handle) != DDI_SUCCESS) {
E 10
			goto err;
		}

		/*
		 * Check hardware revision
		 */
chip_found:
		cmn_err(CE_CONT, "!%s%d: rev:0x%x", drv_name, unit, revid);

		/*
		 * construct gem configration
		 */
D 10
		gcp = (struct gem_conf *) kmem_zalloc(sizeof(*gcp), KM_SLEEP);
E 10
I 10
		gcp = kmem_zalloc(sizeof (*gcp), KM_SLEEP);
E 10

		/* name */
D 10
		sprintf(gcp->gc_name, "%s%d", drv_name, unit);
E 10
I 10
		(void) sprintf(gcp->gc_name, "%s%d", drv_name, unit);
E 10

D 10
		gcp->gc_tx_buf_align   = sizeof(uint8_t) - 1;
		gcp->gc_tx_max_frags   = GEM_MAXTXFRAGS;
E 10
I 10
		gcp->gc_tx_buf_align = sizeof (uint8_t) - 1;
		gcp->gc_tx_max_frags = MAXTXFRAGS;
E 10
		gcp->gc_tx_max_descs_per_pkt = gcp->gc_tx_max_frags;
		gcp->gc_tx_desc_unit_shift = 4;
D 10
		gcp->gc_tx_buf_size    = TX_BUF_SIZE;
		gcp->gc_tx_buf_limit   = gcp->gc_tx_buf_size;
		gcp->gc_tx_ring_size   = TX_RING_SIZE;
		gcp->gc_tx_ring_limit  = gcp->gc_tx_ring_size;
		gcp->gc_tx_auto_pad    = B_TRUE;
E 10
I 10
		gcp->gc_tx_buf_size = TX_BUF_SIZE;
		gcp->gc_tx_buf_limit = gcp->gc_tx_buf_size;
		gcp->gc_tx_ring_size = TX_RING_SIZE;
		gcp->gc_tx_ring_limit = gcp->gc_tx_ring_size;
		gcp->gc_tx_auto_pad = B_TRUE;
E 10
		gcp->gc_tx_copy_thresh = ae_tx_copy_thresh;
D 12
		gcp->gc_tx_desc_write_oo = B_FALSE;
E 12

D 10
		gcp->gc_rx_buf_align = sizeof(uint32_t) - 1;
		gcp->gc_rx_max_frags = 1;
E 10
I 10
		gcp->gc_rx_buf_align = sizeof (uint32_t) - 1;
		gcp->gc_rx_max_frags = MAXRXFRAGS;
E 10
		gcp->gc_rx_desc_unit_shift = 4;
		gcp->gc_rx_ring_size = RX_RING_SIZE;
D 10
		gcp->gc_rx_buf_max   = RX_BUF_SIZE;
E 10
I 10
		gcp->gc_rx_buf_max = RX_BUF_SIZE;
E 10
		gcp->gc_rx_copy_thresh = ae_rx_copy_thresh;

D 10
		gcp->gc_io_area_size = sizeof(struct init_block);;
E 10
I 10
		gcp->gc_io_area_size = sizeof (struct init_block);
E 10

		/* map attributes */
D 5
		STRUCT_COPY(gcp->gc_dev_attr, ae_dev_attr);
		STRUCT_COPY(gcp->gc_buf_attr, ae_buf_attr);
		STRUCT_COPY(gcp->gc_desc_attr, ae_buf_attr);
E 5
I 5
		gcp->gc_dev_attr = ae_dev_attr;
		gcp->gc_buf_attr = ae_buf_attr;
		gcp->gc_desc_attr = ae_buf_attr;
E 5

		/* dma attributes */
D 5
		STRUCT_COPY(gcp->gc_dma_attr_desc, ae_dma_attr_desc);
		STRUCT_COPY(gcp->gc_dma_attr_txbuf, ae_dma_attr_buf);
E 5
I 5
		gcp->gc_dma_attr_desc = ae_dma_attr_desc;
		gcp->gc_dma_attr_txbuf = ae_dma_attr_buf;
I 10
		gcp->gc_dma_attr_txbuf.dma_attr_align =
		    gcp->gc_tx_buf_align + 1;
E 10
E 5
		gcp->gc_dma_attr_txbuf.dma_attr_sgllen = gcp->gc_tx_max_frags;
I 10

E 10
D 5
		STRUCT_COPY(gcp->gc_dma_attr_rxbuf, ae_dma_attr_buf);
E 5
I 5
		gcp->gc_dma_attr_rxbuf = ae_dma_attr_buf;
E 5
D 10
		gcp->gc_dma_attr_rxbuf.dma_attr_align = gcp->gc_rx_buf_align+1;
E 10
I 10
		gcp->gc_dma_attr_rxbuf.dma_attr_align =
		    gcp->gc_rx_buf_align + 1;
E 10
		gcp->gc_dma_attr_rxbuf.dma_attr_sgllen = gcp->gc_rx_max_frags;

		/* time out parameters */
D 13
		gcp->gc_tx_timeout = 3*ONESEC;
		gcp->gc_tx_timeout_interval = ONESEC;
E 13
I 13
		gcp->gc_tx_timeout = GEM_TX_TIMEOUT;
		gcp->gc_tx_timeout_interval = GEM_TX_TIMEOUT_INTERVAL;
E 13

		/* flow control */
		gcp->gc_flow_control = FLOW_CONTROL_NONE;

		/* mii mode */
		gcp->gc_mii_mode = GEM_MODE_100BASETX;

		/* MII timeout parameters */
D 13
		gcp->gc_mii_link_watch_interval = ONESEC;
E 13
I 13
		gcp->gc_mii_link_watch_interval = GEM_LINK_WATCH_INTERVAL;
E 13
		gcp->gc_mii_an_watch_interval = ONESEC/10;
		gcp->gc_mii_reset_timeout = MII_RESET_TIMEOUT;	/* 1 sec */
D 10
		gcp->gc_mii_an_timeout  = MII_AN_TIMEOUT;
		gcp->gc_mii_an_wait	= 0;
E 10
I 10
		gcp->gc_mii_an_timeout = MII_AN_TIMEOUT;
		gcp->gc_mii_an_wait = 0;
E 10
		gcp->gc_mii_linkdown_timeout = MII_LINKDOWN_TIMEOUT;

D 10
		gcp->gc_mii_an_delay	    = ONESEC/10;	/* 100mS */
D 8
		gcp->gc_mii_linkdown_action = MII_ACTION_RESET;
E 8
I 8
		gcp->gc_mii_linkdown_action = MII_ACTION_RSA;
E 10
I 10
		gcp->gc_mii_an_delay = ONESEC/10;	/* 100mS */
		gcp->gc_mii_linkdown_action = MII_ACTION_RESET;
E 10
E 8
		gcp->gc_mii_linkdown_timeout_action = MII_ACTION_RESET;
D 10
		gcp->gc_mii_dont_reset      = B_FALSE;
		gcp->gc_mii_an_oneshot      = B_FALSE;
E 10
I 10
		gcp->gc_mii_dont_reset = B_FALSE;
		gcp->gc_mii_an_oneshot = B_FALSE;
E 10

		/* I/O methods */

		/* mac operation */
		gcp->gc_attach_chip = &ae_attach_chip;
D 10
		gcp->gc_reset_chip  = &ae_reset_chip;
		gcp->gc_init_chip   = &ae_init_chip;
		gcp->gc_start_chip  = &ae_start_chip;
		gcp->gc_stop_chip   = &ae_stop_chip;
E 10
I 10
		gcp->gc_reset_chip = &ae_reset_chip;
		gcp->gc_init_chip = &ae_init_chip;
		gcp->gc_start_chip = &ae_start_chip;
		gcp->gc_stop_chip = &ae_stop_chip;
E 10
		gcp->gc_multicast_hash = &ae_mcast_hash;
		gcp->gc_set_rx_filter = &ae_set_rx_filter;
D 10
		gcp->gc_set_media   = &ae_set_media;
		gcp->gc_get_stats   = &ae_get_stats;
		gcp->gc_interrupt   = &ae_interrupt;
E 10
I 10
		gcp->gc_set_media = &ae_set_media;
		gcp->gc_get_stats = &ae_get_stats;
		gcp->gc_interrupt = &ae_interrupt;
E 10

		/* descriptor operation */
		gcp->gc_tx_desc_write = &ae_tx_desc_write;
		gcp->gc_rx_desc_write = &ae_rx_desc_write;
		gcp->gc_tx_start = &ae_tx_start;
		gcp->gc_rx_start = NULL;
		gcp->gc_tx_desc_stat = &ae_tx_desc_stat;
		gcp->gc_rx_desc_stat = &ae_rx_desc_stat;
		gcp->gc_tx_desc_init = &ae_tx_desc_init;
		gcp->gc_rx_desc_init = &ae_rx_desc_init;
		gcp->gc_tx_desc_clean = &ae_tx_desc_init;
		gcp->gc_rx_desc_clean = &ae_rx_desc_init;

		/* mii operations */
D 9
		gcp->gc_mii_init   = &ae_mii_init;
E 9
I 9
D 10
		gcp->gc_mii_probe  = &ae_mii_probe;
		gcp->gc_mii_init   = NULL;
E 10
I 10
		gcp->gc_mii_probe = &ae_mii_probe;
		gcp->gc_mii_init = &ae_mii_init;
E 10
E 9
		gcp->gc_mii_config = &gem_mii_config_default;
D 10
		gcp->gc_mii_sync  = &ae_mii_sync;
		gcp->gc_mii_read  = &ae_mii_read;
E 10
I 10
		gcp->gc_mii_sync = &ae_mii_sync;
		gcp->gc_mii_read = &ae_mii_read;
E 10
		gcp->gc_mii_write = &ae_mii_write;
		gcp->gc_mii_tune_phy = NULL;

I 13
		/* jumbo packet is not supported */
		gcp->gc_default_mtu = ETHERMTU;
		gcp->gc_min_mtu = ETHERMIN - sizeof (struct ether_header);
		gcp->gc_max_mtu = ETHERMTU;

E 13
D 10
		lp = (struct ae_dev *)
				kmem_zalloc(sizeof(struct ae_dev), KM_SLEEP);
E 10
I 10
		lp = kmem_zalloc(sizeof (struct ae_dev), KM_SLEEP);
E 10

		mutex_init(&lp->reglock, NULL, MUTEX_DRIVER, NULL);

D 9
		dp = gem_do_attach(dip, gcp, base, &regs_handle,
E 9
I 9
D 10
		dp = gem_do_attach(dip, 0, gcp, base, &regs_handle,
E 9
					lp, sizeof(struct ae_dev));
E 10
I 10
		dp = gem_do_attach(dip, 0,
		    gcp, base, &regs_handle, lp, sizeof (struct ae_dev));
E 10

D 10
		kmem_free(gcp, sizeof(*gcp));
E 10
I 10
		kmem_free(gcp, sizeof (*gcp));
E 10

		if (dp == NULL) {
			mutex_destroy(&lp->reglock);
			goto err_free_mem;
		}

		return (DDI_SUCCESS);

err_free_mem:
D 10
		kmem_free(lp, sizeof(struct ae_dev));
E 10
I 10
		kmem_free(lp, sizeof (struct ae_dev));
E 10
err:
		return (DDI_FAILURE);
	}

	return (DDI_FAILURE);
}

static int
aedetach(dev_info_t *dip, ddi_detach_cmd_t cmd)
{
	volatile int	x;
	struct gem_dev	*dp;
	struct ae_dev	*lp;

	dp = GEM_GET_DEV(dip);
D 10
	lp = (struct ae_dev *) dp->private;
E 10
I 10
	lp = dp->private;
E 10

	switch (cmd) {
	case DDI_DETACH:
		/* stop the chip completely */
		mutex_enter(&lp->reglock);
		x = INL(dp, RST);
I 10
#ifdef lint
		x = x;
#endif
E 10
		mutex_exit(&lp->reglock);

		mutex_destroy(&lp->reglock);
		return (gem_do_detach(dip));

	case DDI_SUSPEND:
		/* stop the chip completely */
		mutex_enter(&lp->reglock);
		x = INL(dp, RST);
		mutex_exit(&lp->reglock);

		return (gem_suspend(dip));
	}

	return (DDI_FAILURE);
}

/* ======================================================== */
/*
 * OS depend (loadable streams driver) routine
 */
/* ======================================================== */
I 10
#ifdef GEM_CONFIG_GLDv3
D 12
DDI_DEFINE_STREAM_OPS(ae_ops, nulldev, nulldev, aeattach, aedetach,
    nodev, NULL, D_MP, NULL);
E 12
I 12
GEM_STREAM_OPS(ae_ops, aeattach, aedetach);
E 12
#else
E 10
static	struct module_info aeminfo = {
	0,			/* mi_idnum */
D 10
	"ae",		/* mi_idname */
E 10
I 10
	"ae",			/* mi_idname */
E 10
	0,			/* mi_minpsz */
D 5
	8192,			/* mi_maxpsz */
	TX_BUF_SIZE*ETHERMAX,	/* mi_hiwat */
E 5
I 5
	INFPSZ,			/* mi_maxpsz */
	64*1024,		/* mi_hiwat */
E 5
	1,			/* mi_lowat */
};

static	struct qinit aerinit = {
	(int (*)()) NULL,	/* qi_putp */
D 6
	gld_rsrv,		/* qi_srvp */
	gld_open,		/* qi_qopen */
	gld_close,		/* qi_qclose */
E 6
I 6
	gem_rsrv,		/* qi_srvp */
	gem_open,		/* qi_qopen */
	gem_close,		/* qi_qclose */
E 6
	(int (*)()) NULL,	/* qi_qadmin */
	&aeminfo,		/* qi_minfo */
	NULL			/* qi_mstat */
};

static	struct qinit aewinit = {
D 6
	gld_wput,		/* qi_putp */
	gld_wsrv,		/* qi_srvp */
E 6
I 6
	gem_wput,		/* qi_putp */
	gem_wsrv,		/* qi_srvp */
E 6
	(int (*)()) NULL,	/* qi_qopen */
	(int (*)()) NULL,	/* qi_qclose */
	(int (*)()) NULL,	/* qi_qadmin */
	&aeminfo,		/* qi_minfo */
	NULL			/* qi_mstat */
};

static struct streamtab	ae_info = {
	&aerinit,	/* st_rdinit */
	&aewinit,	/* st_wrinit */
	NULL,		/* st_muxrinit */
	NULL		/* st_muxwrinit */
};

static	struct cb_ops cb_ae_ops = {
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
	&ae_info,	/* cb_stream */
	D_NEW|D_MP	/* cb_flag */
};

static	struct dev_ops ae_ops = {
	DEVO_REV,	/* devo_rev */
	0,		/* devo_refcnt */
D 6
	gld_getinfo,	/* devo_getinfo */
E 6
I 6
	gem_getinfo,	/* devo_getinfo */
E 6
	nulldev,	/* devo_identify */
	nulldev,	/* devo_probe */
	aeattach,	/* devo_attach */
	aedetach,	/* devo_detach */
	nodev,		/* devo_reset */
	&cb_ae_ops,	/* devo_cb_ops */
	NULL,		/* devo_bus_ops */
D 6
	ddi_power	/* devo_power */
E 6
I 6
	gem_power	/* devo_power */
E 6
};
I 10
#endif /* GEM_CONFIG_GLDv3 */
E 10

static struct modldrv modldrv = {
	&mod_driverops,	/* Type of module.  This one is a driver */
	ident,
	&ae_ops,	/* driver ops */
};

static struct modlinkage modlinkage = {
	MODREV_1, &modldrv, NULL
};

/* ======================================================== */
/*
D 10
 * _init : done
E 10
I 10
 * _init :
E 10
 */
/* ======================================================== */
int
_init(void)
{
D 10
	int 	status;
E 10
I 10
	int	status;
E 10

	DPRINTF(2, (CE_CONT, "!ae: _init: called"));
D 6
	status = mod_install(&modlinkage);
E 6

I 6
	gem_mod_init(&ae_ops, "ae");
	status = mod_install(&modlinkage);
	if (status != DDI_SUCCESS) {
		gem_mod_fini(&ae_ops);
	}
E 6
	return (status);
}

/*
D 10
 * _fini : done
E 10
I 10
 * _fini :
E 10
 */
int
_fini(void)
{
	int	status;

	DPRINTF(2, (CE_CONT, "!ae: _fini: called"));
	status = mod_remove(&modlinkage);
I 6
	if (status == DDI_SUCCESS) {
		gem_mod_fini(&ae_ops);
	}
E 6
	return (status);
}

int
_info(struct modinfo *modinfop)
{
	return (mod_info(&modlinkage, modinfop));
}
E 1
