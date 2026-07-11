h00254
s 00100/00085/02114
d D 1.15 11/09/19 22:55:28 mrym 15 14
c 2.6.1
e
s 00523/00339/01676
d D 1.14 09/02/26 21:24:28 mrym 14 13
c 2.6.0
e
s 00456/00341/01559
d D 1.13 06/12/29 21:53:08 mrym 13 12
c 2.4.0
e
s 00009/00012/01891
d D 1.12 05/05/09 22:45:22 mrym 12 11
c 0.8.10 again
e
s 00186/00167/01717
d D 1.11 05/05/09 21:57:12 mrym 11 10
c 0.8.10
e
s 00002/00002/01882
d D 1.10 05/05/03 01:01:52 mrym 10 9
c 0.8.9 RX_BUF_SIZE fixed
e
s 00062/00056/01822
d D 1.9 05/05/02 05:57:58 mrym 9 8
c 0.8.0 polling support, 64bit makefile improvement
e
s 00053/00058/01825
d D 1.8 05/01/11 00:23:00 mrym 8 7
c amd64 support
e
s 00068/00011/01815
d D 1.7 04/06/19 16:38:55 mrym 7 6
c 0.8.6
e
s 00070/00071/01756
d D 1.6 04/05/09 10:15:15 mrym 6 5
c 0.8.5
e
s 00008/00004/01819
d D 1.5 04/02/05 21:57:17 mrym 5 4
c nointr support
e
s 00001/00001/01822
d D 1.4 04/02/01 18:26:08 mrym 4 3
c copyright updated
e
s 00005/00002/01818
d D 1.3 04/01/31 23:01:10 mrym 3 2
c 0.8.2
e
s 00483/00319/01337
d D 1.2 04/01/31 22:08:41 mrym 2 1
c 0.8.2
e
s 01656/00000/00000
d D 1.1 03/12/06 11:41:29 mrym 1 0
c date and time created 03/12/06 11:41:29 by mrym
e
u
U
f e 0
t
T
I 1
/*
D 6
 *  tne_gem.c: TI ThunderLAN TNETE100A Fast Ethernet MAC driver
 *  %W% %E%
E 6
I 6
 * tne_gem.c: TI ThunderLAN TNETE100A Fast Ethernet MAC driver
E 6
 *
D 4
 *  Copyright (C) 2003  Masayuki Murayama (KHF04453@nifty.ne.jp)
E 4
I 4
D 6
 *  Copyright (C) 2003-2004  Masayuki Murayama (KHF04453@nifty.ne.jp)
E 4
 *
 *  CAUTION: NO WARRANTY
 *  This software may be used and distributed according to the terms
 *  of the Lesser GNU Public License, incorporated herein by reference.
E 6
I 6
D 13
 * Copyright (c) 2003-2004 Masayuki Murayama.  All rights reserved.
E 13
I 13
D 14
 * Copyright (c) 2003-2006 Masayuki Murayama.  All rights reserved.
E 13
 * 
E 14
I 14
D 15
 * Copyright (c) 2003-2009 Masayuki Murayama.  All rights reserved.
E 15
I 15
 * Copyright (c) 2003-2011 Masayuki Murayama.  All rights reserved.
E 15
 *
E 14
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
D 14
 * 
E 14
I 14
 *
E 14
 * 1. Redistributions of source code must retain the above copyright notice,
D 14
 *    this list of conditions and the following disclaimer. 
 * 
E 14
I 14
 *    this list of conditions and the following disclaimer.
 *
E 14
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
D 14
 *    and/or other materials provided with the distribution. 
 * 
E 14
I 14
 *    and/or other materials provided with the distribution.
 *
E 14
 * 3. Neither the name of the author nor the names of its contributors may be
 *    used to endorse or promote products derived from this software without
D 14
 *    specific prior written permission. 
 * 
E 14
I 14
 *    specific prior written permission.
 *
E 14
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
E 6
 */

I 6
#pragma ident "%W% %E%"

E 6
/*
 Change log
D 6

E 6
I 6
 0.8.5  05/10/2004
	clean up tne_interrupt().
I 7
        05/29/2004
	disabling interrupts while tne_interrupt()
	supported cards added
 0.8.6  06/19/2004
I 13
 ==============================
 2.4.0  12/29/2006
	reading mac address was fixed for Olicom products.
E 13
E 7
E 6
 */

/*
D 14
 TODO:
E 14
I 14
 * TODO:
E 14
D 13
 mii sync/read/write worked
E 13
 */

/*
 * System Header files.
 */
#include <sys/types.h>
#include <sys/conf.h>
#include <sys/debug.h>
D 14
#include <sys/stropts.h>
#include <sys/stream.h>
#include <sys/strlog.h>
E 14
#include <sys/kmem.h>
D 14
#include <sys/stat.h>
#include <sys/kstat.h>
#include <sys/vtrace.h>
#include <sys/dlpi.h>
#include <sys/strsun.h>
#include <sys/ethernet.h>
E 14
#include <sys/modctl.h>
#include <sys/errno.h>
I 13
D 14
#include <sys/dditypes.h>
E 14
E 13
#include <sys/ddi.h>
#include <sys/sunddi.h>
D 13
#include <sys/ddi_impldefs.h>
E 13
D 14

E 14
I 14
#include <sys/byteorder.h>
#include <sys/ethernet.h>
E 14
#include <sys/pci.h>
D 14
#include "mii.h"
E 14
I 14

#include "gem_mii.h"
E 14
#include "gem.h"
I 13

#define	TNE_MAXTXFRAGS	7
#define	TNE_MAXRXFRAGS	7
I 15

E 15
E 13
#include "tnete100areg.h"

D 13
#if GEM_MAXTXFRAGS > TNE_MAXTXFRAGS
D 6
# error GEM_MAXTXFRAGS must be less than 10
E 6
I 6
# error GEM_MAXTXFRAGS must be less than or equals to 10.
E 6
#endif

#if GEM_MAXRXFRAGS >= TNE_MAXRXFRAGS
D 6
# error GEM_MAXRXFRAGS must be less than 10
E 6
I 6
# error GEM_MAXRXFRAGS must be less than 10.
E 6
#endif

E 13
D 8
#ifdef sun4u
# define	IOCACHE
# define	IOMMU
#endif

E 8
D 9
char	ident[] = "TI ThunderLAN TNETE100A driver v" VERSION;
E 9
I 9
char	ident[] = "TI ThunderLAN driver v" VERSION;
E 9
D 13
char	_depends_on[] = {"misc/gld"};
E 13

/* Debugging support */
#ifdef DEBUG_LEVEL
static int tne_debug = DEBUG_LEVEL;
D 14
#define	DPRINTF(n, args)	if (tne_debug>(n)) cmn_err args
E 14
I 14
#define	DPRINTF(n, args)	if (tne_debug > (n)) cmn_err args
E 14
#else
#define	DPRINTF(n, args)
#endif

/*
 * Useful macros and typedefs
 */
D 13
#define	FALSE	(0)
#define	TRUE	(!FALSE)
E 13
I 13
D 14
#define	UINT8(x)	((uint8_t) (x))
#define	UINT16(x)	((uint16_t) (x))
E 14
I 14
D 15
#define	UINT8(x)	((uint8_t)(x))
#define	UINT16(x)	((uint16_t)(x))
E 14
E 13

E 15
I 8
D 13
#define	STRUCT_COPY(a, b)	bcopy(&(b), &(a), sizeof(a))

E 8
#define	INT8(x)		(0xff & (x))
#define	INT16(x)	(0xffff & (x))

E 13
#define	OUTB_DIO(dp, reg, val)	OUTB(dp, DIO_DATA | ((reg) & 3), val)
#define	OUTW_DIO(dp, reg, val)	OUTW(dp, DIO_DATA | ((reg) & 3), val)
#define	OUTL_DIO(dp, reg, val)	OUTL(dp, DIO_DATA, val)
#define	INB_DIO(dp, reg)	INB(dp, DIO_DATA | ((reg) & 3))
#define	INW_DIO(dp, reg)	INW(dp, DIO_DATA | ((reg) & 3))
#define	INL_DIO(dp, reg)	INL(dp, DIO_DATA)
I 7
#define	FLSHL(dp, reg)		INL(dp, reg)
#define	FLSHW(dp, reg)		INW(dp, reg)
E 7

D 13
struct tne_dev {
I 2
	boolean_t	tx_last_intreq;

E 2
	boolean_t	tx_list_loaded;
I 2
	uint_t		tx_list_done;
	int		tx_list_len;
	int		tx_list_head;

E 2
	boolean_t	rx_list_loaded;
D 2
	seqnum_t	tx_last_ack;
	seqnum_t	rx_last_ack;
	boolean_t	tx_last_intreq;
E 2
I 2
	uint_t		rx_list_done;
	int		rx_list_len;
	int		rx_list_head;

I 7
	boolean_t	which_phy;
#define	PHY_EXTERNAL_MII	0
#define	PHY_INTERNAL_MII	1

I 9
#ifdef CONFIG_POLLING
	int		last_poll_interval;
E 13
I 13
D 14
#if defined(sun4u)
# define LE16(x)	ddi_swap16(x)
# define LE32(x)	ddi_swap32(x)
# define LE64(x)	ddi_swap64(x)
#else
# define LE16(x)	(x)
# define LE32(x)	(x)
# define LE64(x)	(x)
E 13
#endif
I 11
D 13
	uint8_t		netcmd;
E 11
E 9
E 7
E 2
	uint8_t		rev_id;
D 2
	uint16_t	prom[256];
E 2
I 2
	uint8_t		prom[256];
E 2
};
E 13

I 13
#define	FLSHB(dp,reg)	INB(dp, reg)
#define	FLSHW(dp,reg)	INW(dp, reg)
E 14
#define	FLSHB(dp, reg)	INB(dp, reg)
#define	FLSHW(dp, reg)	INW(dp, reg)
I 14
#define	FLSHB(dp, reg)	INB(dp, reg)
#define	FLSHW(dp, reg)	INW(dp, reg)
E 14
#define	FLSHL(dp, reg)	INL(dp, reg)

I 14
#define	DUAL_PHY(lp)	((lp)->is_dual_phy)

I 15
#ifdef GEM3
#define	IS_MAC_ONLINE(dp)	((dp)->mac_state == MAC_STATE_ONLINE)
#else
#define	IS_MAC_ONLINE(dp)	((dp)->mac_active)
#endif

E 15
E 14
E 13
/*
 * Our configuration
 */
I 8
D 11
#define	TNE_MAX_MTU	(64*1024 - 14)
E 11
I 11
D 13
#define	TNE_MAX_MTU	(64*1024 - 14 - 1)
E 11

E 13
I 11
#ifdef TEST_TXDESC_FULL
D 14
# define TX_RING_SIZE	4
# define TX_BUF_SIZE	64
E 14
I 14
#define	TX_RING_SIZE	4
#define	TX_BUF_SIZE	64
E 14
#endif
#ifdef TEST_RX_EMPTY
D 14
# define RX_RING_SIZE	8
E 14
I 14
#define	RX_BUF_SIZE	8
E 14
#endif

E 11
D 15
#ifndef TX_RING_SIZE
E 8
D 2
#define TX_RING_SIZE	128
E 2
I 2
D 11
#define TX_RING_SIZE	64
E 11
I 11
D 14
# define TX_RING_SIZE	64
E 14
I 14
#define	TX_RING_SIZE	64
E 14
E 11
I 8
#endif
E 15
E 8
D 10
#define TX_BUF_SIZE	TX_RING_SIZE
E 10
I 10
D 11
#define TX_BUF_SIZE	(TX_RING_SIZE - 1)
E 11
I 11
#ifndef TX_BUF_SIZE
D 13
# define TX_BUF_SIZE	TX_RING_SIZE
E 13
I 13
D 14
# define TX_BUF_SIZE	(TX_RING_SIZE)
E 14
I 14
D 15
#define	TX_BUF_SIZE	(TX_RING_SIZE)
E 15
I 15
#define	TX_BUF_SIZE	64
E 15
E 14
E 13
#endif
I 15
#ifndef TX_RING_SIZE
#define	TX_RING_SIZE	TX_BUF_SIZE
#endif
E 15
E 11
E 10
I 8

D 14
#ifndef RX_RING_SIZE
E 8
E 2
D 11
#define RX_RING_SIZE	64
E 11
I 11
# define RX_RING_SIZE	64
E 14
I 14
#ifndef RX_BUF_SIZE
#define	RX_BUF_SIZE	256
E 14
E 11
I 8
#endif
E 8
I 2
D 10
#define RX_BUF_SIZE	RX_RING_SIZE
E 10
I 10
D 11
#define RX_BUF_SIZE	(RX_RING_SIZE - 1)
E 11
I 11
D 13
#define RX_BUF_SIZE	RX_RING_SIZE
E 13
I 13
D 14
#define RX_BUF_SIZE	(RX_RING_SIZE)
E 14
E 13
E 11
E 10
E 2

D 13
#define	ONESEC			(drv_usectohz(1*1000000))
E 13
I 13
#define	ONESEC		(drv_usectohz(1*1000000))
E 13

static int	tne_tx_copy_thresh = 256;
static int	tne_rx_copy_thresh = 256;

I 6
#ifndef INTR_DELAY
D 14
#   define	INTR_DELAY	0
E 14
I 14
#define	INTR_DELAY	0
E 14
#endif

I 13
struct tne_dev {
	struct chip_info	*chip;
D 14
	boolean_t	tx_intreq[TX_RING_SIZE];
E 14

	boolean_t	tx_list_loaded;
	uint_t		tx_list_done;
	int		tx_list_len;
	int		tx_list_head;

	boolean_t	rx_list_loaded;
	uint_t		rx_list_done;
	int		rx_list_len;
	int		rx_list_head;

D 14
	boolean_t	which_phy;
#define	PHY_EXTERNAL_MII	0
#define	PHY_INTERNAL_MII	1
E 14
I 14
	boolean_t	is_dual_phy;
	int		curr_phy;
E 14

D 14
#ifdef GEM_CONFIG_POLLING
E 14
I 14
#ifdef CONFIG_POLLING
E 14
	int		last_poll_interval;
#endif
	uint8_t		netcmd;
	uint8_t		rev_id;
	uint8_t		prom[256];
};

E 13
E 6
/*
 * Supported chips
 */
struct chip_info {
	uint16_t	venid;
	uint16_t	devid;
	char		*name;
} tne_chiptbl[] = {
	{0x0e11, 0xae32, "Compaq Netelligent 10/100 TX UTP"},
I 7
	{0x0e11, 0xae34, "Compaq Netelligent 10 T UTP"},
D 14
	{0x0e11, 0xae35, "Compaq Integrated NetFlex-3/P"}, 
E 14
I 14
	{0x0e11, 0xae35, "Compaq Integrated NetFlex-3/P"},
E 14
	{0x0e11, 0xae40, "Compaq Netelligent Dual 10/100 TX UTP"},
	{0x0e11, 0xae43, "Compaq Netelligent Integrated 10/100 TX UTP"},
	{0x0e11, 0xb011, "Compaq Netelligent 10/100 TX Embedded UTP"},
	{0x0e11, 0xb012, "Compaq Netelligent 10 T/2 PCI UTP/Coax"},
	{0x0e11, 0xb030, "Compaq Netelligent 10/100 TX UTP"},
I 13
	{0x108d, 0x0012, "Olicom OC-2325"},
E 13
	{0x108d, 0x0013, "Olicom OC-2183/2185"},
	{0x108d, 0x0014, "Olicom OC-2326"},
E 7
	{0x104c, 0x0500, "TI ThunderLAN TNETE100A"},
};
D 14
#define CHIPTABLESIZE   (sizeof(tne_chiptbl)/sizeof(struct chip_info))
E 14
I 14
#define	CHIPTABLESIZE	(sizeof (tne_chiptbl)/sizeof (struct chip_info))
E 14

/* ======================================================== */
D 14
 
E 14
I 14

E 14
/* mii operations */
I 14
static uint16_t tne_mii_read_raw(struct gem_dev *dp, uint_t phy, uint_t reg);
static void tne_mii_write_raw(struct gem_dev *dp,
    uint_t phy, uint_t reg, uint16_t val);
E 14
static void  tne_mii_sync(struct gem_dev *);
D 11
static uint16_t  tne_mii_read(struct gem_dev *, int);
static void tne_mii_write(struct gem_dev *, int, uint16_t);
E 11
I 11
static uint16_t  tne_mii_read(struct gem_dev *, uint_t);
static void tne_mii_write(struct gem_dev *, uint_t, uint16_t);
E 11

/* nic operations */
I 11
static int tne_attach_chip(struct gem_dev *);
E 11
static int tne_reset_chip(struct gem_dev *);
D 13
static void tne_init_chip(struct gem_dev *);
static void tne_start_chip(struct gem_dev *);
static void tne_stop_chip(struct gem_dev *);
static void tne_set_media(struct gem_dev *);
static void tne_set_rx_filter(struct gem_dev *);
static void tne_get_stats(struct gem_dev *);
E 13
I 13
static int tne_init_chip(struct gem_dev *);
static int tne_start_chip(struct gem_dev *);
static int tne_stop_chip(struct gem_dev *);
static int tne_set_media(struct gem_dev *);
static int tne_set_rx_filter(struct gem_dev *);
static int tne_get_stats(struct gem_dev *);
E 13
D 11
static int tne_init_mac_addr(struct gem_dev *);
E 11

/* descriptor operations */
D 13
static int tne_tx_desc_write(struct gem_dev *dp, uint_t slot,
E 13
I 13
static int tne_tx_desc_write(struct gem_dev *dp, int slot,
E 13
D 14
		    ddi_dma_cookie_t *dmacookie, int frags, uint32_t flag);
E 14
I 14
    ddi_dma_cookie_t *dmacookie, int frags, uint64_t flag);
E 14
D 13
static int tne_rx_desc_write(struct gem_dev *dp, uint_t slot,
E 13
I 13
static void tne_tx_start(struct gem_dev *dp, int start_slot, int nslots);
static void tne_rx_desc_write(struct gem_dev *dp, int slot,
E 13
D 14
		    ddi_dma_cookie_t *dmacookie, int frags);
E 14
I 14
    ddi_dma_cookie_t *dmacookie, int frags);
E 14
I 13
static void tne_rx_start(struct gem_dev *dp, int start_slot, int nslots);
E 13
static uint_t tne_tx_desc_stat(struct gem_dev *dp, int slot, int ndesc);
D 13
static uint_t tne_rx_desc_stat(struct gem_dev *dp, int slot, int ndesc);
E 13
I 13
static uint64_t tne_rx_desc_stat(struct gem_dev *dp, int slot, int ndesc);
E 13

static void tne_tx_desc_init(struct gem_dev *dp, int slot);
static void tne_rx_desc_init(struct gem_dev *dp, int slot);

/* interrupt handler */
D 14
static u_int tne_interrupt(struct gem_dev *dp);
E 14
I 14
static uint_t tne_interrupt(struct gem_dev *dp);
E 14

static void tne_load_tx_list(struct gem_dev *dp);
static void tne_load_rx_list(struct gem_dev *dp);

/* ======================================================== */

/* mapping attributes */
/* Data access requirements. */
static struct ddi_device_acc_attr tne_dev_attr = {
	DDI_DEVICE_ATTR_V0,
	DDI_STRUCTURE_LE_ACC,
	DDI_STRICTORDER_ACC
};

/* On sparc, the buffers should be native endianness */
static struct ddi_device_acc_attr tne_buf_attr = {
	DDI_DEVICE_ATTR_V0,
	DDI_NEVERSWAP_ACC,	/* native endianness */
	DDI_STRICTORDER_ACC
};

D 9
static ddi_dma_attr_t tne_dma_attr_txbuf = {
E 9
I 9
static ddi_dma_attr_t tne_dma_attr_buf = {
E 9
	DMA_ATTR_V0,		/* dma_attr_version */
	0,			/* dma_attr_addr_lo */
	0xffffffffull,		/* dma_attr_addr_hi */
D 15
	0xffffffffull,		/* dma_attr_count_max */
E 15
I 15
	0xffffull,		/* dma_attr_count_max */
E 15
	1,			/* dma_attr_align */
	0,			/* dma_attr_burstsizes */
	1,			/* dma_attr_minxfer */
	0xffffffffull,		/* dma_attr_maxxfer */
	0xffffffffull,		/* dma_attr_seg */
D 9
	GEM_MAXTXFRAGS,		/* dma_attr_sgllen */
E 9
I 9
	0, /* patched later */	/* dma_attr_sgllen */
E 9
	1,			/* dma_attr_granular */
	0			/* dma_attr_flags */
};

D 9
static ddi_dma_attr_t tne_dma_attr_rxbuf = {
	DMA_ATTR_V0,		/* dma_attr_version */
	0,			/* dma_attr_addr_lo */
	0xffffffffull,		/* dma_attr_addr_hi */
	0xffffffffull,		/* dma_attr_count_max */
	1,			/* dma_attr_align */
	0,			/* dma_attr_burstsizes */
	1,			/* dma_attr_minxfer */
	0xffffffffull,		/* dma_attr_maxxfer */
	0xffffffffull,		/* dma_attr_seg */
I 8
#ifdef RXSINGLE
	1,			/* dma_attr_sgllen */
#else
E 8
	GEM_MAXRXFRAGS,		/* dma_attr_sgllen */
I 8
#endif
E 8
	1,			/* dma_attr_granular */
	0			/* dma_attr_flags */
};

E 9
D 8
static ddi_dma_attr_t tne_dma_attr_nosc = {
E 8
I 8
static ddi_dma_attr_t tne_dma_attr_desc = {
E 8
	DMA_ATTR_V0,		/* dma_attr_version */
D 2
	0x8,			/* dma_attr_addr_lo */
E 2
I 2
	8,			/* dma_attr_addr_lo */
E 2
	0xffffffffull,		/* dma_attr_addr_hi */
	0xffffffffull,		/* dma_attr_count_max */
	8,			/* dma_attr_align */
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
 * HW manupilation routines
 */
/* ======================================================== */

static int
tne_reset_chip(struct gem_dev *dp)
{
	int	i;
	uint8_t	val;
I 2
D 14
	struct tne_dev	*lp = (struct tne_dev *)dp->private;
E 14
I 14
	struct tne_dev	*lp = dp->private;
E 14
E 2

D 2
	/* Clear the statistics by resding the statistic registers */

E 2
	/*
	 * Issue a reset command to ThunderLAN by asserting the AdRst bit
	 * in the HOST_CMD register
	 */
	OUTL(dp, HOST_CMD, HC_AdRst);
D 2
#ifdef notdef
	drv_usecwait(1000);
#endif
E 2

I 11
	OUTW(dp, DIO_ADR, NETCMD);
	lp->netcmd = INB_DIO(dp, NETCMD);

E 11
	/*
	 * unreset MII PHY
	 */
	OUTW(dp, DIO_ADR, NETSIO);
D 2
	val = INB_DIO(dp, NETSIO);
	val |= NSIO_NMRST;
	val &= ~NSIO_MINTEN;
	OUTB_DIO(dp, NETSIO, val);
E 2
I 2
	OUTB_DIO(dp, NETSIO, (INB_DIO(dp, NETSIO) | NSIO_NMRST) & ~NSIO_MINTEN);
E 2

I 11
	/* synchronize with mii_state */
	dp->mii_state = MII_STATE_RESETTING;

E 11
D 2
	DPRINTF(1, (CE_CONT, "!%s: tne_reset_chip", dp->name));
E 2
I 2
D 14
	DPRINTF(2, (CE_CONT, "!%s: tne_reset_chip", dp->name));
E 14
I 14
	DPRINTF(2, (CE_CONT, "!%s: %s", dp->name, __func__));
E 14
E 2

D 13
	return 0;
E 13
I 13
	return (GEM_SUCCESS);
E 13
}

D 13
static void
E 13
I 13
static int
E 13
tne_init_chip(struct gem_dev *dp)
{
I 11
	uint32_t	val;
E 11
D 14
	struct tne_dev	*lp = (struct tne_dev *)dp->private;
E 14
I 14
	struct tne_dev	*lp = dp->private;
E 14

D 14
	DPRINTF(2, (CE_CONT, "!%s: tne_init_chip: called", dp->name));
E 14
I 14
	DPRINTF(2, (CE_CONT, "!%s: %s: called", dp->name, __func__));
E 14

D 11
	ASSERT(mutex_owned(&dp->intrlock));

E 11
	/* Disable interrupts by asserting the Ints_off bit int HOST_CMD */
	OUTL(dp, HOST_CMD, HC_IntsOff);

D 11
	lp->tx_list_loaded = FALSE;
I 2
	lp->tx_list_len    = 0;
	lp->tx_list_done   = 0;
	lp->tx_list_head   = 0;

E 2
	lp->rx_list_loaded = FALSE;
D 2
	lp->tx_last_ack = 0;
	lp->rx_last_ack = 0;
E 2
I 2
	lp->rx_list_len    = 0;
	lp->rx_list_done   = 0;
	lp->rx_list_head   = 0;
E 2
}

static void
tne_start_chip(struct gem_dev *dp)
{
I 2
	uint32_t	val;
E 2
	struct tne_dev	*lp = (struct tne_dev *)dp->private;

	ASSERT(mutex_owned(&dp->intrlock));

E 11
	/* Setup the NetConfig registers for the appropriate options */
I 11
	ASSERT((lp->netcmd & NCMD_NRESET) == 0);
I 14

E 14
E 11
	OUTW(dp, DIO_ADR, NETCFG);
D 2
	OUTW_DIO(dp, NETCFG, NCFG_PEF | NCFG_RxCRC | NCFG_ONEchn);
E 2
I 2
D 7
	OUTW_DIO(dp, NETCFG, NCFG_PEF | NCFG_ONEchn);
E 7
I 7
D 14
	if (lp->which_phy == PHY_INTERNAL_MII) {
		OUTW_DIO(dp, NETCFG, NCFG_PEF | NCFG_ONEchn | NCFG_PHY_En);
	} else {
		OUTW_DIO(dp, NETCFG, NCFG_PEF | NCFG_ONEchn);
	}
E 14
I 14
	OUTW_DIO(dp, NETCFG,
	    (dp->mii_phy_addr == 31 || DUAL_PHY(lp))
	    ? (NCFG_PEF | NCFG_ONEchn | NCFG_PHY_En)
	    : (NCFG_PEF | NCFG_ONEchn));
E 14
E 7
E 2

	/* Setup the BSIZEreg for the correct burst size */
I 2
	val = 0;
	if (dp->txmaxdma <= 32) {
		val |= BS_TX_16;
	} else if (dp->txmaxdma < 64) {
		val |= BS_TX_32;
	} else if (dp->txmaxdma < 128) {
		val |= BS_TX_64;
	} else if (dp->txmaxdma < 256) {
		val |= BS_TX_128;
	} else if (dp->txmaxdma < 512) {
		val |= BS_TX_256;
	} else {
		val |= BS_TX_512;
	}
	if (dp->rxmaxdma <= 32) {
		val |= BS_RX_16;
	} else if (dp->rxmaxdma < 64) {
		val |= BS_RX_32;
	} else if (dp->rxmaxdma < 128) {
		val |= BS_RX_64;
	} else if (dp->rxmaxdma < 256) {
		val |= BS_RX_128;
	} else if (dp->rxmaxdma < 512) {
		val |= BS_RX_256;
	} else {
		val |= BS_RX_512;
	}
E 2
	OUTW(dp, DIO_ADR, BSIZEreg);
D 2
	OUTB_DIO(dp, BSIZEreg, BS_TX_64 | BS_RX_64);
E 2
I 2
	OUTB_DIO(dp, BSIZEreg, val);
E 2

	/* Setup the correct Tx commit level in the Acommit register */
I 2
	if (dp->txthr <= 64) {
		val = AC_TX_64;
	} else if (dp->txthr <= 128) {
		val = AC_TX_128;
	} else if (dp->txthr <= 256) {
		val = AC_TX_256;
	} else if (dp->txthr <= 512) {
		val = AC_TX_512;
	} else if (dp->txthr <= 1024) {
		val = AC_TX_1024;
	} else {
		val = AC_TX_SF;
	}
E 2
	OUTW(dp, DIO_ADR, Acommit);
D 2
	OUTB_DIO(dp, Acommit, AC_TX_SF);
E 2
I 2
	OUTB_DIO(dp, Acommit, val);
E 2
D 13

E 13
I 13
#if 0
E 13
	/* Load the appropriate interrupt pacing timer in Ld_Tmr in HOST_CMD */
D 2
	OUTL(dp, HOST_CMD, HC_LdTmr | 0);
E 2
I 2
D 3
	OUTL(dp, HOST_CMD, HC_LdTmr | ((1*1500*8/100)/4));
E 2

E 3
I 3
D 6
#ifdef INTR_DELAY
E 6
D 11
	OUTL(dp, HOST_CMD, HC_LdTmr | (INTR_DELAY/4));
E 11
I 11
	OUTL(dp, HOST_CMD, HC_LdTmr | 0);
E 11
D 6
#else
	OUTL(dp, HOST_CMD, HC_LdTmr | 0);
#endif
E 6
I 6
D 13

E 13
I 13
#endif
E 13
E 6
E 3
	/* Load the appropriate Tx threshold value in Ld_Thr in HOST_CMD */
I 14
#ifdef CONFIG_POLLING
	OUTL(dp, HOST_CMD, HC_LdThr | 1);
#else
E 14
	OUTL(dp, HOST_CMD, HC_LdThr | 0);
I 14
#endif
E 14
D 11

E 11
I 11
#if 0
E 11
	/* Unreset the MII by asserting NMRDT in NetSio */

	/* Initialize PHY layer */
D 11

	/* Setup the network status mask register, Netmask */
E 11
I 11
#endif
	/* Setup the network status mask register */
E 11
	OUTW(dp, DIO_ADR, NETMASK);
	OUTB_DIO(dp, NETMASK, 0);

	OUTW(dp, DIO_ADR, MaxRx);
D 2
	OUTW_DIO(dp, MaxRx, ETHERMAX+ETHERFCSL);
E 2
I 2
D 11
	val = min(0x10000, dp->mtu + 14);
E 11
I 11
D 13
	val = min(0xffff, dp->mtu + sizeof(struct ether_header));
E 13
I 13
D 14
#ifdef GEM_CONFIG_VLAN
	val = min(0xffff, dp->mtu + sizeof(struct ether_header) + 4);
E 14
I 14
#ifdef GEM_CONFIG_GLDv3
	val = min(0xffff, dp->mtu + sizeof (struct ether_header) + 4);
E 14
#else
D 14
	val = min(0xffff, dp->mtu + sizeof(struct ether_header) );
E 14
I 14
	val = min(0xffff, dp->mtu + sizeof (struct ether_header));
E 14
#endif
E 13
E 11
	OUTW_DIO(dp, MaxRx, (uint16_t)val);
E 2

D 11
	/* set NETCMD register */
E 11
I 11
	/* enable NETCMD register */
	lp->netcmd |= NCMD_NRESET | NCMD_NWRAP;
E 11
	OUTW(dp, DIO_ADR, NETCMD);
D 11
	OUTB_DIO(dp, NETCMD, NCMD_NRESET | NCMD_NWRAP);
	tne_set_media(dp);
E 11
I 11
	OUTB_DIO(dp, NETCMD, lp->netcmd);
E 11

I 11
D 13
	lp->tx_list_loaded = FALSE;
E 13
I 13
	lp->tx_list_loaded = B_FALSE;
E 13
D 14
	lp->tx_list_len    = 0;
	lp->tx_list_done   = 0;
	lp->tx_list_head   = 0;
E 14
I 14
	lp->tx_list_len = 0;
	lp->tx_list_done = 0;
	lp->tx_list_head = 0;
E 14

D 13
	lp->rx_list_loaded = FALSE;
E 13
I 13
	lp->rx_list_loaded = B_FALSE;
E 13
D 14
	lp->rx_list_len    = 0;
	lp->rx_list_done   = 0;
	lp->rx_list_head   = 0;
E 14
I 14
	lp->rx_list_len = 0;
	lp->rx_list_done = 0;
	lp->rx_list_head = 0;
E 14
I 13

	return (GEM_SUCCESS);
E 13
}

static uint32_t
tne_mcast_hash(struct gem_dev *dp, uint8_t *addr)
{
	int		i;
	uint8_t		hash;
	uint32_t	addr0, addr1;

D 13
	addr0 = (addr[3] << 24) | (addr[2] << 16) | (addr[1] << 8) | addr[0];
	addr1 = (addr[5] << 8) | addr[4];
	for (hash = 0, i = 0; i < 8; i++) {
		hash ^= addr0;
E 13
I 13
	/*
D 15
	 * By experience, hash function must return following
D 14
	 * 6 bit-width values:
E 14
I 14
	 * 6 bit-width value:
E 15
I 15
	 * According with my experience, the hash function must return
	 * following 6 bit-width value:
E 15
E 14
	 *   01:00:5e:00:00:01 -> 0x0e (001110)
	 *   01:00:5e:00:00:04 -> 0x0b (001011)
	 */
	hash = 0;
D 15
	addr0 = (addr[0] << 16) | (addr[1] << 8) | addr[2];
	addr1 = (addr[3] << 16) | (addr[4] << 8) | addr[5];
E 15
I 15
	addr0 = addr[0] << 16 | addr[1] << 8 | addr[2];
	addr1 = addr[3] << 16 | addr[4] << 8 | addr[5];
E 15

	for (i = 0; i < 3*8/6; i++) {
		hash ^= addr0 ^ addr1;
E 13
		/* shift 6 bits right */
D 13
		addr0 = (addr1 << (32-6)) | (addr0 >> 6);
E 13
I 13
		addr0 >>= 6;
E 13
		addr1 >>= 6;
	}
I 13
D 14
	return (hash & ((1 << 6) - 1));
E 14
I 14
	return (hash & 0x3f);
E 14
}
E 13

D 13
	return hash & ((1<<6)-1);
E 13
I 13
D 14
static int
tne_load_cam(struct gem_dev *dp, int ix, uint8_t *ether_addr)	
E 14
I 14
static void
tne_load_cam(struct gem_dev *dp, int ix, uint8_t *ether_addr)
E 14
{
D 15
	int	j;
E 15
I 15
	int	i;
E 15
	int	offset;

	offset = Areg_0 + ix * ETHERADDRL;
D 15
	for (j = 0; j < ETHERADDRL; j++) {
		OUTW(dp, DIO_ADR, offset + j);
		OUTB_DIO(dp, offset + j, ether_addr[j]);
E 15
I 15
	for (i = 0; i < ETHERADDRL; i++) {
		OUTW(dp, DIO_ADR, offset + i);
		OUTB_DIO(dp, offset + i, ether_addr[i]);
E 15
	}
E 13
}

D 13
static void
E 13
I 13
static int
E 13
D 14
tne_set_rx_filter(struct gem_dev *dp)	
E 14
I 14
tne_set_rx_filter(struct gem_dev *dp)
E 14
{
D 15
	int		i, j;
E 15
I 15
	int		i;
E 15
I 13
	int		cam_ix;
E 13
	uint8_t		mode;
D 13
	uint8_t		old;
	uint8_t		reg;
E 13
D 14
	uint32_t	hash[2];
E 14
I 14
	uint64_t	hash;
E 14
D 13
	uint8_t		*m;
E 13
	uint16_t	addr;
I 13
D 14
	uint8_t		*filler = "\377\377\377\377\377\377";
E 13
	struct tne_dev	*lp = (struct tne_dev *)dp->private;
E 14
I 14
	static uint8_t	ff6[] = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff};
	static uint8_t	zero6[] = {0, 0, 0, 0, 0, 0};
	uint8_t		*filler = ff6;
	struct tne_dev	*lp = dp->private;
E 14

D 15
	ASSERT(mutex_owned(&dp->intrlock));
D 13
	bzero(hash, sizeof(hash));
E 13

E 15
I 13
#if DEBUG_LEVEL > 3
	for (i = 0; i < dp->mc_count; i++) {
		cmn_err(CE_CONT,
D 14
		"!%s: adding mcast(%d) %02x:%02x:%02x:%02x:%02x:%02x -> %d",
			dp->name, i,
			dp->mc_list[i].addr.ether_addr_octet[0],
			dp->mc_list[i].addr.ether_addr_octet[1],
			dp->mc_list[i].addr.ether_addr_octet[2],
			dp->mc_list[i].addr.ether_addr_octet[3],
			dp->mc_list[i].addr.ether_addr_octet[4],
			dp->mc_list[i].addr.ether_addr_octet[5],
			tne_mcast_hash(dp,
				dp->mc_list[i].addr.ether_addr_octet));
E 14
I 14
		    "!%s: adding mcast(%d) %02x:%02x:%02x:%02x:%02x:%02x -> %d",
		    dp->name, i,
		    dp->mc_list[i].addr.ether_addr_octet[0],
		    dp->mc_list[i].addr.ether_addr_octet[1],
		    dp->mc_list[i].addr.ether_addr_octet[2],
		    dp->mc_list[i].addr.ether_addr_octet[3],
		    dp->mc_list[i].addr.ether_addr_octet[4],
		    dp->mc_list[i].addr.ether_addr_octet[5],
		    tne_mcast_hash(dp, dp->mc_list[i].addr.ether_addr_octet));
E 14
	}
#endif
D 14
	hash[0] = hash[1] = 0;
E 14
I 14
	hash = 0ULL;
E 14
	cam_ix = 0;
E 13
	mode = 0;
I 15
#define	NCAMS	4
E 15
I 13

	if ((dp->rxmode & RXMODE_ENABLE) == 0) {
		/* clear cam */
D 14
		filler = "\0\0\0\0\0\0";
E 14
I 14
		filler = zero6;
E 14
		goto x;
	}

D 15
	/* pass all rx packets while we setup rx filter */
E 15
I 15
	/* accept all rx packets while we are changing rx filter */
E 15
	OUTW(dp, DIO_ADR, NETCMD);
	OUTB_DIO(dp, NETCMD, lp->netcmd | NCMD_CAF);

D 15
	/* setup my address for cam-entry #0 */
E 15
I 15
	/* write my station address into cam-entry #0 */
E 15
	tne_load_cam(dp, cam_ix++, &dp->cur_addr.ether_addr_octet[0]);

E 13
D 14
	if ((dp->rxmode & RXMODE_PROMISC) != 0) {
E 14
I 14
	if (dp->rxmode & RXMODE_PROMISC) {
E 14
		/* promiscous */
		mode = NCMD_CAF;
D 14
	}
	else if ((dp->rxmode & RXMODE_ALLMULTI) != 0 && dp->mc_count > 32) {
E 14
I 14
	} else if ((dp->rxmode & RXMODE_ALLMULTI) && dp->mc_count > 32) {
E 14
		/* allmulti */
D 14
		hash[0] = 0xffffffff;
		hash[1] = 0xffffffff;
	}
I 13
	else if (dp->mc_count > 3) {
E 14
I 14
		hash = ~0ULL;
D 15
	} else if (dp->mc_count > 3) {
E 15
I 15
	} else if (dp->mc_count > NCAMS - 1) {
E 15
E 14
		/* use multicast hash table */
D 15
		for (j = 0; j < dp->mc_count; j++) {
D 14
			uint_t	k;
			k = dp->mc_list[j].hash;
			hash[k / 32] |= 1 << (k % 32);
E 14
I 14
			hash |= 1ULL << dp->mc_list[j].hash;
E 15
I 15
		for (i = 0; i < dp->mc_count; i++) {
			hash |= 1ULL << dp->mc_list[i].hash;
E 15
E 14
		}
D 14
	}
E 13
	else {
E 14
I 14
	} else {
E 14
D 13
		/* Normal mode */
		/* set CAM-based multicast filter */
		i = 0;
		addr = Areg_0;
		if (dp->mc_count <= 3) {
			for (; i < dp->mc_count; i++) {
				m = dp->mc_list[i].addr.ether_addr_octet;
				for (j = 0; j < ETHERADDRL; j++, addr++) {
					OUTW(dp, DIO_ADR, addr);
					OUTB_DIO(dp, addr, m[j]);
				}
			}
E 13
I 13
		/* use CAM-based multicast filter */
D 14
		for (; i < dp->mc_count; i++) {
E 14
I 14
		for (i = 0; i < dp->mc_count; i++) {
E 14
			tne_load_cam(dp, cam_ix++,
D 14
				&dp->mc_list[i].addr.ether_addr_octet[0]);
E 14
I 14
			    &dp->mc_list[i].addr.ether_addr_octet[0]);
E 14
E 13
		}
D 13
		else {
			/* Make multicast hash table */
			for (j = 0; j < dp->mc_count; j++) {
				uint_t	k;
				k = dp->mc_list[j].hash;
				hash[k / 32] |= 1 << (k % 32);
			}
			OUTW(dp, DIO_ADR, HASH1);
			OUTL_DIO(dp, HASH1, hash[0]);
			OUTW(dp, DIO_ADR, HASH2);
			OUTL_DIO(dp, HASH2, hash[1]);
		}
E 13
I 13
	}
x:
D 15
	/* fill rest of perfect match filter entries */
	while (cam_ix < 4) {
		tne_load_cam(dp, cam_ix++, filler);
E 15
I 15
	/* fill rest of perfect match filter entries with ff:ff:ff:ff:ff:ff */
	for (; cam_ix < NCAMS; cam_ix++) {
		tne_load_cam(dp, cam_ix, filler);
E 15
	}
E 13

D 13
		/* Set my addresss */
		for (; i < 4; i++) {
			m = dp->cur_addr.ether_addr_octet;
			for (j = 0; j < ETHERADDRL; j++, addr++) {
				OUTW(dp, DIO_ADR, addr);
				OUTB_DIO(dp, addr, m[j]);
			}
		}
E 13
I 13
	/* update hash table */
D 15
	for (j = 0; j < 2; j++) {
		OUTW(dp, DIO_ADR, HASH1 + 4*j);
D 14
		OUTL_DIO(dp, HASH1, hash[j]);
E 14
I 14
		OUTL_DIO(dp, HASH1, (uint32_t) hash);
		hash >>= 32;
E 14
E 13
	}
E 15
I 15
	OUTW(dp, DIO_ADR, HASH1 + 0);
	OUTL_DIO(dp, HASH1, (uint32_t)hash);
	OUTW(dp, DIO_ADR, HASH1 + 4);
	OUTL_DIO(dp, HASH1, (uint32_t)(hash >> 32));
E 15

D 13
	old = lp->netcmd;
E 13
I 13
	/* update rx filter mode */
E 13
	lp->netcmd = (lp->netcmd & ~NCMD_CAF) | mode;
D 13
	if (old != lp->netcmd) {
		OUTW(dp, DIO_ADR, NETCMD);
		OUTB_DIO(dp, NETCMD, lp->netcmd);
	}
E 13
I 13
	OUTW(dp, DIO_ADR, NETCMD);
	OUTB_DIO(dp, NETCMD, lp->netcmd);

	return (GEM_SUCCESS);
E 13
}

D 13
static void
E 13
I 13
static int
E 13
tne_set_media(struct gem_dev *dp)
{
	uint_t		old;
D 14
	struct tne_dev	*lp = (struct tne_dev *)dp->private;
E 14
I 14
	struct tne_dev	*lp = dp->private;
E 14

D 15
	ASSERT(mutex_owned(&dp->intrlock));

E 15
I 14
	if (DUAL_PHY(lp)) {
		uint_t		right_phy;

		/* check current phy */
		if ((dp->anadv_100fdx || dp->anadv_100hdx) &&
		    (dp->mii_lpable &
		    (MII_ABILITY_100BASE_TX_FD | MII_ABILITY_100BASE_TX))) {
			/* we must use external phy device */
			right_phy = dp->mii_phy_addr;
		} else {
			/* we must use internal phy device */
			right_phy = 31;
		}

		if (lp->curr_phy != right_phy) {
			/* switch PHY */
			cmn_err(CE_NOTE,
			    "!%s: %s switching phy from @%d to @%d",
			    dp->name, __func__, lp->curr_phy, right_phy);

			tne_mii_sync(dp);
			tne_mii_write_raw(dp, lp->curr_phy,
			    MII_CONTROL,
			    MII_CONTROL_ISOLATE);

D 15
			lp->curr_phy= right_phy;
E 15
I 15
			lp->curr_phy = right_phy;
E 15

			tne_mii_sync(dp);
			tne_mii_write_raw(dp, lp->curr_phy,
			    MII_CONTROL,
			    (dp->anadv_autoneg ? MII_CONTROL_ANE : 0) |
			    (dp->full_duplex ? MII_CONTROL_FDUPLEX : 0));

D 15
			/* do autinegotiation again */
E 15
I 15
			/*
			 * Force to start autonegotiation with the right phy.
			 * It will cause link-down.
			 */
E 15
			dp->mii_state = MII_STATE_UNKNOWN;

			return (GEM_SUCCESS);
		}
	}

D 15
	if (dp->mii_phy_addr == 31 || (DUAL_PHY(lp) && lp->curr_phy == 31)) {
		/* now we are using internal phy */
E 15
I 15
	if (dp->mii_phy_addr == 31 ||
	    (DUAL_PHY(lp) && lp->curr_phy == 31)) {
		/* now we are using internal 10M phy */
E 15
		if (dp->anadv_autoneg) {
			/* we must configure current duplex mode explicitly */
			tne_mii_sync(dp);
			tne_mii_write_raw(dp,
			    lp->curr_phy,
			    MII_CONTROL,
			    MII_CONTROL_ANE |
			    (dp->full_duplex ? MII_CONTROL_FDUPLEX : 0));
		}
	}

E 14
	/*
	 * Notify current duplex mode to MAC
	 */
	old = lp->netcmd;
	lp->netcmd &= ~NCMD_DUPLEX;
	if (dp->full_duplex) {
		lp->netcmd |= NCMD_DUPLEX;
	}

	if (old != lp->netcmd) {
		OUTW(dp, DIO_ADR, NETCMD);
		OUTB_DIO(dp, NETCMD, lp->netcmd);
	}
I 13

	/* Load the appropriate interrupt pacing timer in Ld_Tmr in HOST_CMD */
	OUTL(dp, HOST_CMD, HC_LdTmr | 0);

	return (GEM_SUCCESS);
E 13
}

D 13
static void
E 13
I 13
static int
E 13
tne_start_chip(struct gem_dev *dp)
{
	uint32_t	val;
D 14
	struct tne_dev	*lp = (struct tne_dev *)dp->private;
E 14
I 14
	struct tne_dev	*lp = dp->private;
E 14

D 15
	ASSERT(mutex_owned(&dp->intrlock));

E 15
E 11
D 5
	/* Reenable interrupts by asserting the IntsOn bit in HOST_CMD */
	OUTL(dp, HOST_CMD, HC_IntsOn);
E 5
I 5
	if ((dp->misc_flag & GEM_NOINTR) == 0) {
		/* Enable interrupts by asserting the IntsOn bit in HOST_CMD */
		OUTL(dp, HOST_CMD, HC_IntsOn);
	}
E 5

D 13
	tne_load_rx_list(dp);
E 13
I 13
	return (GEM_SUCCESS);
E 13
}

D 13
static void
E 13
I 13
static int
E 13
tne_stop_chip(struct gem_dev *dp)
{
	uint8_t		val;
	uint16_t	stat;
I 14
	struct tne_dev	*lp = dp->private;
E 14

	OUTL(dp, HOST_CMD, HC_IntsOff);

	OUTL(dp, HOST_CMD, HC_TxSTOP(0));
	OUTL(dp, HOST_CMD, HC_RxSTOP(0));
D 13

E 13
I 13
D 14
#ifdef notdef
	/* XXX - hw reset may be required */
E 13
D 2
	OUTL(dp, HOST_CMD, HC_AdRst);
#ifdef notdef
	drv_usecwait(1000);
#endif
	/*
	 * unreset MII PHY
	 */
	OUTW(dp, DIO_ADR, NETSIO);
	val = INB_DIO(dp, NETSIO);
	val |= NSIO_NMRST;
	val &= ~NSIO_MINTEN;
	OUTB_DIO(dp, NETSIO, val);
E 2
I 2
	tne_reset_chip(dp);
I 13
#endif
E 14
I 14

	/* hw reset may be required */
	(void) tne_reset_chip(dp);

E 14
	return (GEM_SUCCESS);
E 13
E 2
}

D 2
#define	set(dp, bit)	OUTB_DIO(dp, NETSIO, INB_DIO(dp, NETSIO) | (bit))
#define	clr(dp, bit)	OUTB_DIO(dp, NETSIO, INB_DIO(dp, NETSIO) & ~(bit))
E 2
I 2
/*
 * IIC EEPROM I/O routines
 */
#define	NETSIO_SET(dp, bit)	\
	OUTB_DIO(dp, NETSIO, INB_DIO(dp, NETSIO) | (bit))
#define	NETSIO_CLR(dp, bit)	\
	OUTB_DIO(dp, NETSIO, INB_DIO(dp, NETSIO) & ~(bit))
E 2

I 2
D 14
#define	TNE_EEPROM_DELAY(dp)	{INB_DIO(dp, NETSIO); INB_DIO(dp, NETSIO);}
E 14
I 14
#define	TNE_EEPROM_DELAY(dp)	{ INB_DIO(dp, NETSIO); INB_DIO(dp, NETSIO); }
E 14

static void
tne_iic_start(struct gem_dev *dp)
{
	NETSIO_SET(dp, NSIO_EDATA);
	TNE_EEPROM_DELAY(dp);
	NETSIO_SET(dp, NSIO_ETXEN);
	TNE_EEPROM_DELAY(dp);
	NETSIO_SET(dp, NSIO_ECLOK);
	TNE_EEPROM_DELAY(dp);
	NETSIO_CLR(dp, NSIO_EDATA);
	TNE_EEPROM_DELAY(dp);
	NETSIO_CLR(dp, NSIO_ECLOK);
	TNE_EEPROM_DELAY(dp);
}

static void
tne_iic_stop(struct gem_dev *dp)
{
	/* send EEPROM stop access sequence */
	NETSIO_CLR(dp, NSIO_EDATA);
	TNE_EEPROM_DELAY(dp);
	NETSIO_SET(dp, NSIO_ETXEN);
	TNE_EEPROM_DELAY(dp);
	NETSIO_SET(dp, NSIO_ECLOK);
	TNE_EEPROM_DELAY(dp);
	NETSIO_SET(dp, NSIO_EDATA);
	TNE_EEPROM_DELAY(dp);
	NETSIO_CLR(dp, NSIO_ETXEN);
	TNE_EEPROM_DELAY(dp);
}

E 2
static boolean_t
D 2
ack(struct gem_dev *dp)
E 2
I 2
tne_iic_ack(struct gem_dev *dp)
E 2
{
	boolean_t	ack;

D 2
	clr(dp, NSIO_ETXEN);
	set(dp, NSIO_ECLOK);
	ack = (~INB_DIO(dp, NETSIO) >> NSIO_EDATA_SHIFT) & 1;
	clr(dp, NSIO_ECLOK);
E 2
I 2
	/* disable tx */
	NETSIO_CLR(dp, NSIO_ETXEN);
	TNE_EEPROM_DELAY(dp);
	NETSIO_SET(dp, NSIO_ECLOK);
	TNE_EEPROM_DELAY(dp);

	/* get ack */
	ack = (INB_DIO(dp, NETSIO) & NSIO_EDATA) == 0;
	NETSIO_CLR(dp, NSIO_ECLOK);
	TNE_EEPROM_DELAY(dp);	/* XX */

E 2
#ifdef notdef
D 2
	set(dp, NSIO_ETXEN);
E 2
I 2
	NETSIO_SET(dp, NSIO_ETXEN);
D 11
		TNE_EEPROM_DELAY(dp);
E 11
I 11
	TNE_EEPROM_DELAY(dp);
E 11
E 2
#endif
D 13
	return ack;
E 13
I 13
	return (ack);
E 13
}

static void
D 2
sendaddr(struct gem_dev *dp, uint8_t addr)
E 2
I 2
tne_iic_send(struct gem_dev *dp, uint8_t data)
E 2
{
	uint_t	i;

D 2
	i = 0x80;
	while (i) {
		if (addr & i) {
			set(dp, NSIO_EDATA);
E 2
I 2
D 14
	for (i = 0x80; i != 0; i >>= 1) {
		if ((data & i) != 0) {
E 14
I 14
	for (i = 0x80; i; i >>= 1) {
		if (data & i) {
E 14
			/* send 1 */
			NETSIO_SET(dp, NSIO_EDATA);
E 2
D 14
		}
		else {
E 14
I 14
		} else {
E 14
D 2
			clr(dp, NSIO_EDATA);
E 2
I 2
			/* send 0 */
			NETSIO_CLR(dp, NSIO_EDATA);
E 2
		}
D 2
		set(dp, NSIO_ECLOK);
		INB_DIO(dp, NETSIO);
		clr(dp, NSIO_ECLOK);
		i >>= 1;
E 2
I 2
		TNE_EEPROM_DELAY(dp);	/* XX */
		NETSIO_SET(dp, NSIO_ECLOK);
		TNE_EEPROM_DELAY(dp);
		NETSIO_CLR(dp, NSIO_ECLOK);
E 2
	}
I 2
	TNE_EEPROM_DELAY(dp);
	/* now clock is in low state */
E 2
}

static uint8_t
I 2
tne_iic_recv(struct gem_dev *dp, boolean_t last)
{
	uint_t	i;
	uint8_t	data;

	/* assume clock is in low state */
	NETSIO_CLR(dp, NSIO_ETXEN);

	/* clock bits in from EDATA and construct data in tmp */
	for (i = 8; i; i--) {
		NETSIO_SET(dp, NSIO_ECLOK);
		TNE_EEPROM_DELAY(dp);
		data = (data << 1)
		    | ((INB_DIO(dp, NETSIO) >> NSIO_EDATA_SHIFT) & 1);
		NETSIO_CLR(dp, NSIO_ECLOK);
		TNE_EEPROM_DELAY(dp);
	}

	/* send EEPROM ack */
	if (last) {
		NETSIO_SET(dp, NSIO_EDATA);
	} else {
		NETSIO_CLR(dp, NSIO_EDATA);
	}
	TNE_EEPROM_DELAY(dp);
	NETSIO_SET(dp, NSIO_ETXEN);
	TNE_EEPROM_DELAY(dp);
	NETSIO_SET(dp, NSIO_ECLOK);
	TNE_EEPROM_DELAY(dp);
	NETSIO_CLR(dp, NSIO_ECLOK);
	TNE_EEPROM_DELAY(dp);
	/* now clock is low */

D 13
	return data;
E 13
I 13
	return (data);
E 13
}

static int8_t
E 2
tne_read_eeprom(struct gem_dev *dp, uint8_t offset)
{
	int	i;
	int	tmp;

	/* select NETSIO register */
	OUTW(dp, DIO_ADR, NETSIO);
D 2
	clr(dp, NSIO_ECLOK);
E 2

I 2
	/* let clock low */
	NETSIO_CLR(dp, NSIO_ECLOK);
	TNE_EEPROM_DELAY(dp);

E 2
	/* send EEPROM start sequence */
D 2
	set(dp, NSIO_EDATA);
	set(dp, NSIO_ETXEN);
	set(dp, NSIO_ECLOK);
	clr(dp, NSIO_EDATA);
	clr(dp, NSIO_ECLOK);
E 2
I 2
	tne_iic_start(dp);
E 2

	/*
D 14
	 * put EEPROM device identifier, address, and write 
E 14
I 14
	 * put EEPROM device identifier, address, and write
E 14
	 * command on bus
	 */
#define	EEPROM_DEVID	0xa
#define	EEPROM_WRITE(a)	(((EEPROM_DEVID << 4) | 0) | ((a) << 1))
#define	EEPROM_READ(a)	(((EEPROM_DEVID << 4) | 1) | ((a) << 1))

D 2
	sendaddr(dp, EEPROM_WRITE(0));
E 2
I 2
	tne_iic_send(dp, EEPROM_WRITE(0));
E 2

	/* EEPROM should have acked */
D 2
	if (!ack(dp)) {
E 2
I 2
	if (!tne_iic_ack(dp)) {
E 2
D 6
		DPRINTF(0, (CE_CONT, "eeprom WRITE ack failed"));
E 6
I 6
		cmn_err(CE_WARN, "eeprom WRITE ack failed");
E 6
D 13
		return 0;
E 13
I 13
		return (0);
E 13
	}
I 2

E 2
	/* send address on EEPROM to read from */
D 2
	set(dp, NSIO_ETXEN);
	sendaddr(dp, offset);
E 2
I 2
	NETSIO_SET(dp, NSIO_ETXEN);
	tne_iic_send(dp, offset);
E 2

	/* EEPROM should have acke'd addres received */
D 2
	if (!ack(dp)) {
E 2
I 2
	if (!tne_iic_ack(dp)) {
E 2
D 6
		DPRINTF(0, (CE_CONT, "eeprom addr ack failed"));
E 6
I 6
		cmn_err(CE_WARN, "eeprom addr ack failed");
E 6
D 13
		return 0;
E 13
I 13
		return (0);
E 13
	}

	/* send EEPROM start access sequence */
D 2
	set(dp, NSIO_EDATA);
	set(dp, NSIO_ETXEN);
	set(dp, NSIO_ECLOK);
	set(dp, NSIO_EDATA);
	clr(dp, NSIO_EDATA);
	clr(dp, NSIO_ECLOK);
E 2
I 2
	tne_iic_start(dp);
E 2

	/*
D 14
	 * put EEPROM device identifier, address, and read 
E 14
I 14
	 * put EEPROM device identifier, address, and read
E 14
	 * command on bus
	 */
D 2
	sendaddr(dp, EEPROM_READ(0));
E 2
I 2
	tne_iic_send(dp, EEPROM_READ(0));
E 2

	/* EEPROM should have acked */
D 2
	if (!ack(dp)) {
E 2
I 2
	if (!tne_iic_ack(dp)) {
E 2
D 6
		DPRINTF(0, (CE_CONT, "eeprom read ack failed"));
E 6
I 6
		cmn_err(CE_WARN, "eeprom read ack failed");
E 6
D 2
		return 0;
E 2
I 2
D 8
		return;
E 8
I 8
D 13
		return 0;
E 13
I 13
		return (0);
E 13
E 8
E 2
	}
I 2
	/* receive a 8bit-date from EEPROM and send EEPROM nack */
D 13
	tmp = tne_iic_recv(dp, FALSE);
E 13
I 13
	tmp = tne_iic_recv(dp, B_FALSE);
E 13
E 2

D 2
	/* clock bits in from EDATA and construct data in tmp */
	for (i = 8, tmp = 0; i; i--) {
		set(dp, NSIO_ECLOK);
		tmp = (tmp << 1) | ((INB_DIO(dp, NETSIO) >> NSIO_EDATA_SHIFT) & 1);
		clr(dp, NSIO_ECLOK);
	}
E 2
I 2
	/* send EEPROM stop access sequence */
	tne_iic_stop(dp);
E 2

D 2
	set(dp, NSIO_ECLOK);
	INB_DIO(dp, NETSIO);
	clr(dp, NSIO_ECLOK);
E 2
I 2
	/* now data is high, clock is high */
E 2

D 2
	/* send EEPROM start access sequence */
	clr(dp, NSIO_EDATA);
	set(dp, NSIO_ETXEN);
	set(dp, NSIO_ECLOK);
	set(dp, NSIO_EDATA);
	clr(dp, NSIO_ETXEN);

E 2
D 6
	DPRINTF(4, (CE_CONT, "eeprom_read: ret:%02x", tmp));
E 6
I 6
D 14
	DPRINTF(4, (CE_CONT, "!%s: tne_eeprom_read: ret:%02x", dp->name, tmp));
E 14
I 14
	DPRINTF(4, (CE_CONT, "!%s: %s: ret:%02x", dp->name, __func__, tmp));
E 14
E 6
I 2

E 2
D 13
	return tmp;
E 13
I 13
	return (tmp);
E 13
}

#ifdef DEBUG_LEVEL
static void
tne_eeprom_dump(struct gem_dev *dp)
{
D 13
	int			i;
E 13
I 13
	int		i;
E 13
D 14
	struct tne_dev	*lp = (struct tne_dev *)dp->private;
E 14
I 14
	struct tne_dev	*lp = dp->private;
E 14

	for (i = 0; i < 256; i++) {
		lp->prom[i] = tne_read_eeprom(dp, i);
	}

	cmn_err(CE_CONT, "!%s: eeprom dump:", dp->name);
	for (i = 0; i < 256; i += 8) {
		cmn_err(CE_CONT,
D 14
			"!0x%02x: 0x%02x 0x%02x 0x%02x 0x%02x " 
				 "0x%02x 0x%02x 0x%02x 0x%02x", 
		i, lp->prom[i  ], lp->prom[i+1], lp->prom[i+2], lp->prom[i+3],
		   lp->prom[i+4], lp->prom[i+5], lp->prom[i+6], lp->prom[i+7]);
E 14
I 14
		    "!0x%02x: 0x%02x 0x%02x 0x%02x 0x%02x "
		    "0x%02x 0x%02x 0x%02x 0x%02x",
		    i,
		    lp->prom[i  ], lp->prom[i+1], lp->prom[i+2], lp->prom[i+3],
		    lp->prom[i+4], lp->prom[i+5], lp->prom[i+6], lp->prom[i+7]);
E 14
	}
}
#endif /* DEBUG_LEVEL */

static int
D 14
tne_attach_chip(struct gem_dev *dp)	
E 14
I 14
tne_attach_chip(struct gem_dev *dp)
E 14
{
D 13
	int			i;
	uint16_t		val;
E 13
I 13
	int		i;
	uint16_t	val;
	int		mac_offset;
D 14
	struct tne_dev	*lp = (struct tne_dev *)dp->private;
E 14
I 14
	struct tne_dev	*lp = dp->private;
E 14
E 13
D 2

E 2
I 2
D 6
#if 0
	static uint8_t tne_mac_test[] = {0x00,0x08,0xc7,0x1e,0x06,0x5c};
#endif
E 6
I 6

E 6
#if DEBUG_LEVEL >= 0
E 2
	OUTW(dp, DIO_ADR, DEFAULT_REV);
	val = INB_DIO(dp, DEFAULT_REV);
D 2
	DPRINTF(0, (CE_CONT, "!%s: rev_id: 0x%02x", dp->name, val));

#ifndef notdef
E 2
I 2
	cmn_err(CE_CONT, "!%s: rev_id: 0x%02x", dp->name, val);
#endif
	/* get factory mac address */
E 2
D 13
	for (i = 0; i < ETHERADDRL; i++) {
D 2
		val =  tne_read_eeprom(dp, 0x83 + i);
		dp->dev_addr.ether_addr_octet[i] = val;
	}
#else
	gem_get_mac_addr_conf(dp);
E 2
I 2
		dp->dev_addr.ether_addr_octet[i] = tne_read_eeprom(dp, 0x83+i);
E 13
I 13
	if (lp->chip->venid == 0x108d) {
		/*
		 * Olicom products have network byte ordered mac
		 * address at non-standard offset in eeprom.
		 */
		for (i = 0; i < ETHERADDRL; i++) {
			dp->dev_addr.ether_addr_octet[i] =
D 14
				tne_read_eeprom(dp, 0xf8 + (i ^ 1));
E 14
I 14
			    tne_read_eeprom(dp, 0xf8 + (i ^ 1));
E 14
		}
E 13
D 6
#if 0
		dp->dev_addr.ether_addr_octet[i] = tne_mac_test[i];
E 2
#endif
E 6
D 2

#if DEBUG_LEVEL > 2
E 2
I 2
D 14
	}
D 13
#if DEBUG_LEVEL > 4
E 13
I 13
	else {
E 14
I 14
	} else {
E 14
		for (i = 0; i < ETHERADDRL; i++) {
			dp->dev_addr.ether_addr_octet[i] =
D 14
				tne_read_eeprom(dp, 0x83 + i);
E 14
I 14
			    tne_read_eeprom(dp, 0x83 + i);
E 14
		}
	}
	/* check if the mac address is valid. */
D 14
	if (dp->dev_addr.ether_addr_octet[0] & 0x1 != 0 ||
E 14
I 14
	if ((dp->dev_addr.ether_addr_octet[0] & 0x1) ||
E 14
	    bcmp(dp->dev_addr.ether_addr_octet,
D 14
				"\0\0\0\0\0\0", ETHERADDRL) == 0) {
E 14
I 14
	    "\0\0\0\0\0\0", ETHERADDRL) == 0) {
E 14
		if (!gem_get_mac_addr_conf(dp)) {
			gem_generate_macaddr(dp, dp->dev_addr.ether_addr_octet);
		}
	}
#if DEBUG_LEVEL > 3
E 13
E 2
	tne_eeprom_dump(dp);
#endif
D 2

E 2
I 2
	/* Clear the statistics by reading the statistic registers */
E 2
D 14
	tne_get_stats(dp);
	bzero(&dp->stats, sizeof(dp->stats));
E 14
I 14
	(void) tne_get_stats(dp);
	bzero(&dp->stats, sizeof (dp->stats));
E 14
D 15

E 15
I 15
#if 0
	/* now jumbo frame is handled by solais kernel */
E 15
I 2
	/* fix mtu */
D 13
	dp->mtu = min(dp->mtu, 64*1024 - 14);
E 13
I 13
D 14
#ifdef GEM_CONFIG_VLAN
	dp->mtu = min(dp->mtu, 64*1024 - sizeof(struct ether_header) - 4);
E 14
I 14
#ifdef GEM_CONFIG_GLDv3
	dp->mtu = min(dp->mtu, 64*1024 - sizeof (struct ether_header) - 4);
E 14
#else
D 14
	dp->mtu = min(dp->mtu, 64*1024 - sizeof(struct ether_header));
E 14
I 14
	dp->mtu = min(dp->mtu, 64*1024 - sizeof (struct ether_header));
E 14
#endif
I 15
#endif
E 15
E 13

E 2
D 13
	return 0;
E 13
I 13
D 14
#ifdef GEM_CONFIG_VLAN
E 14
I 14
#ifdef GEM_CONFIG_GLDv3
E 14
	dp->misc_flag |= GEM_VLAN_SOFT;
#endif
I 14

E 14
	return (GEM_SUCCESS);
E 13
}

D 11
static uint32_t
tne_mcast_hash(struct gem_dev *dp, uint8_t *addr)
{
	int		i;
	uint8_t		hash;
	uint32_t	addr0, addr1;

	addr0 = (addr[3] << 24) | (addr[2] << 16) | (addr[1] << 8) | addr[0];
	addr1 = (addr[5] << 8) | addr[4];
D 2
	hash = 0;
	for (i = 0; i < 8; i++) {
E 2
I 2
	for (hash = 0, i = 0; i < 8; i++) {
E 2
		hash ^= addr0;
D 2
		/* shift 6bit right */
		addr0 >>= 6;
		addr0 |= addr1 << (32-6);
E 2
I 2
		/* shift 6 bits right */
		addr0 = (addr1 << (32-6)) | (addr0 >> 6);
E 2
		addr1 >>= 6;
	}

D 2
	return hash & (64-1);
E 2
I 2
	return hash & ((1<<6)-1);
E 2
}

E 11
D 13
static void
E 13
I 13
static int
E 13
D 11
tne_set_rx_filter(struct gem_dev *dp)	
{
	int		i, j;
	uint8_t		mode;
	uint8_t		reg;
	uint32_t	hash[2];
	uint8_t		*m;
	uint16_t	addr;
	struct tne_dev	*lp = (struct tne_dev *)dp->private;

	ASSERT(mutex_owned(&dp->intrlock));
	bzero(hash, sizeof(hash));

	mode = 0;
	if ((dp->rxmode & RXMODE_PROMISC) != 0) {
		/* promiscous */
		mode = NCMD_CAF;
	}
	else if ((dp->rxmode & RXMODE_ALLMULTI) != 0 && dp->mc_count > 32) {
		/* allmulti */
		hash[0] = 0xffffffff;
		hash[1] = 0xffffffff;
	}
	else {
		/* Normal mode */
		/* set CAM-based multicast filter */
		i = 0;
		addr = Areg_0;
		if (dp->mc_count <= 3) {
			for (; i < dp->mc_count; i++) {
				m = dp->mc_list[i].addr.ether_addr_octet;
				for (j = 0; j < ETHERADDRL; j++, addr++) {
					OUTW(dp, DIO_ADR, addr);
					OUTB_DIO(dp, addr, m[j]);
				}
			}
		}
		else {
			/* Make multicast hash table */
			for (j = 0; j < dp->mc_count; j++) {
				uint_t	k;
D 2
				/* hash key is 6 bits of LSB in be-crc */
E 2
				k = dp->mc_list[j].hash;
				hash[k / 32] |= 1 << (k % 32);
			}
			OUTW(dp, DIO_ADR, HASH1);
			OUTL_DIO(dp, HASH1, hash[0]);
			OUTW(dp, DIO_ADR, HASH2);
			OUTL_DIO(dp, HASH2, hash[1]);
		}

		/* Set my addresss */
		for (; i < 4; i++) {
			m = dp->cur_addr.ether_addr_octet;
			for (j = 0; j < ETHERADDRL; j++, addr++) {
				OUTW(dp, DIO_ADR, addr);
				OUTB_DIO(dp, addr, m[j]);
			}
		}
	}

	OUTW(dp, DIO_ADR, NETCMD);
D 2
	reg = INB_DIO(dp, NETCMD) & ~NCMD_CAF;
	reg |= mode;
	OUTB_DIO(dp, NETCMD, reg);
E 2
I 2
	OUTB_DIO(dp, NETCMD, (INB_DIO(dp, NETCMD) & ~NCMD_CAF) | mode);
E 2
}

static void
tne_set_media(struct gem_dev *dp)
{
	uint_t	old;
	uint_t	new;
	int	i;

	ASSERT(mutex_owned(&dp->intrlock));

	if (dp->nic_active) {
		/* reset the nic to change the content of netcmd register*/
	}

	/*
	 * Notify current duplex mode to MAC
	 */
	OUTW(dp, DIO_ADR, NETCMD);

	old = INB_DIO(dp, NETCMD);
	new = old & ~NCMD_DUPLEX;
	if (dp->full_duplex) {
		new |= NCMD_DUPLEX;
	}
	if (old != new) {
		OUTB_DIO(dp, NETCMD, new);
	}
	if (dp->nic_active) {
		/* restatrt the nic */
	}
}

static void
E 11
tne_get_stats(struct gem_dev *dp)
{
	uint_t	x;
	uint_t	val;

D 14
	DPRINTF(4, (CE_CONT, "!%s: tne_get_stats: called", dp->name));
E 14
I 14
	DPRINTF(4, (CE_CONT, "!%s: %s: called", dp->name, __func__));
E 14
D 2
#ifdef notdef
	ASSERT(mutex_owned(&dp->intrlock));
#endif
E 2
I 2

E 2
	OUTW(dp, DIO_ADR, Tx_UN_GOOD);
	val = INL_DIO(dp, Tx_UN_GOOD);
D 13
	dp->stats.underflow += x = INT8(val >> 24);
E 13
I 13
D 14
	dp->stats.underflow += x = UINT8(val >> 24);
E 14
I 14
	dp->stats.underflow += x = (uint8_t)(val >> 24);
E 14
E 13
	dp->stats.errxmt += x;

	OUTW(dp, DIO_ADR, Rx_OV_GOOD);
	val = INL_DIO(dp, Rx_OV_GOOD);
D 13
	dp->stats.overflow += x = INT8(val >> 24);
E 13
I 13
D 14
	dp->stats.overflow += x = UINT8(val >> 24);
E 14
I 14
	dp->stats.overflow += x = (uint8_t)(val >> 24);
E 14
E 13
	dp->stats.errrcv += x;

	OUTW(dp, DIO_ADR, DeferredTx);
	val = INL_DIO(dp, DeferredTx);
D 13
	dp->stats.defer  += INT16(val);
	dp->stats.crc    += x = INT8(val >> 16);
E 13
I 13
D 15
	dp->stats.defer  += UINT16(val);
E 15
I 15
	dp->stats.defer  += (uint16_t)(val);
E 15
D 14
	dp->stats.crc    += x = UINT8(val >> 16);
E 14
I 14
	dp->stats.crc    += x = (uint8_t)(val >> 16);
E 14
E 13
	dp->stats.errrcv += x;
D 13
	dp->stats.frame  += x = INT8(val >> 24);
E 13
I 13
D 14
	dp->stats.frame  += x = UINT8(val >> 24);
E 14
I 14
	dp->stats.frame  += x = (uint8_t)(val >> 24);
E 14
E 13
	dp->stats.errrcv += x;

	OUTW(dp, DIO_ADR, Multicollisions);
	val = INL_DIO(dp, Multicollisions);
D 13
	dp->stats.multi_coll += x = INT16(val);
E 13
I 13
D 14
	dp->stats.multi_coll += x = UINT16(val);
E 14
I 14
	dp->stats.multi_coll += x = (uint16_t)(val);
E 14
E 13
	dp->stats.collisions += x*2;
D 13
	dp->stats.first_coll += x = INT16(val >> 16);
E 13
I 13
D 14
	dp->stats.first_coll += x = UINT16(val >> 16);
E 14
I 14
	dp->stats.first_coll += x = (uint16_t)(val >> 16);
E 14
E 13
	dp->stats.collisions += x;

	OUTW(dp, DIO_ADR, ExcessiveCollisions);
	val = INL_DIO(dp, ExcessiveCollisions);
D 13
	dp->stats.excoll += x = INT8(val);
E 13
I 13
D 14
	dp->stats.excoll += x = UINT8(val);
E 14
I 14
	dp->stats.excoll += x = (uint8_t)(val);
E 14
E 13
	dp->stats.errxmt += x;
	dp->stats.collisions += x*16;
D 13
	dp->stats.xmtlatecoll += x = INT8(val >> 8);
E 13
I 13
D 14
	dp->stats.xmtlatecoll += x = UINT8(val >> 8);
E 14
I 14
	dp->stats.xmtlatecoll += x = (uint8_t)(val >> 8);
E 14
E 13
	dp->stats.errxmt += x;
D 13
	dp->stats.nocarrier += x = INT8(val >> 16);
E 13
I 13
D 14
	dp->stats.nocarrier += x = UINT8(val >> 16);
E 14
I 14
	dp->stats.nocarrier += x = (uint8_t)(val >> 16);
E 14
E 13
	dp->stats.errxmt += x;
I 13

	return (GEM_SUCCESS);
E 13
}

/*
 * discriptor  manupiration
 */
static void
tne_load_tx_list(struct gem_dev *dp)
{
D 14
	struct tne_dev	*lp = (struct tne_dev *)dp->private;
E 14
I 14
	struct tne_dev	*lp = dp->private;
E 14
D 2
	uint32_t		tlp_dma;
E 2

D 2
	tlp_dma = dp->tx_ring_dma
		+ sizeof(struct tx_list) * SLOT(dp->tx_desc_head, TX_RING_SIZE);
E 2
I 2
	ASSERT(!lp->tx_list_loaded);
E 2

D 2
	OUTL(dp, CH_PARM, tlp_dma);
E 2
I 2
	OUTL(dp, CH_PARM,
D 14
		dp->tx_ring_dma + sizeof(struct tx_list) * lp->tx_list_head);
E 14
I 14
	    dp->tx_ring_dma + sizeof (struct tx_list) * lp->tx_list_head);
E 14

E 2
	OUTL(dp, HOST_CMD, HC_TxGO(0));

D 13
	lp->tx_list_loaded = TRUE;
E 13
I 13
	lp->tx_list_loaded = B_TRUE;
E 13
}

#ifdef TXTIMEOUT_TEST
static int	tne_send_cnt;
#endif
static int
D 13
tne_tx_desc_write(struct gem_dev *dp, uint_t slot,
E 13
I 13
tne_tx_desc_write(struct gem_dev *dp, int slot,
E 13
D 14
		ddi_dma_cookie_t *dmacookie, int frags, uint32_t flag)
E 14
I 14
    ddi_dma_cookie_t *dmacookie, int frags, uint64_t flag)
E 14
{
	int			i;
	struct tx_list		*tlp;
D 2
	struct frag		*tfp;
E 2
I 2
D 9
	volatile struct frag	*tfp;
E 9
I 9
	struct frag		*tfp;
E 9
E 2
	uint32_t		tlp_dma;
I 12
	uint32_t		mark;
I 14
	uint32_t		addr;
E 14
E 12
	ddi_dma_cookie_t	*dcp;
	uint_t			len;
D 2
	struct tne_dev	*lp = (struct tne_dev *)dp->private;
E 2
I 2
D 14
	struct tne_dev		*lp = (struct tne_dev *)dp->private;
E 14
I 14
	struct tne_dev		*lp = dp->private;
I 15
	const uint_t		tx_ring_size = dp->gc.gc_tx_ring_size;
E 15
E 14
I 9
D 13
	ddi_acc_handle_t	h = dp->desc_acc_handle;
E 13
E 9
E 2

D 2
	tlp = &((struct tx_list *)dp->tx_ring)[slot];
E 2
I 2
	tlp = ((struct tx_list *)dp->tx_ring) + slot;
E 2

#if DEBUG_LEVEL > 2
	cmn_err(CE_CONT,
D 14
		"%s: tne_tx_desc_write "
		"seqnum: %d, slot %d, frags: %d flag: %d",
		dp->name, dp->tx_desc_tail, slot, frags, flag);
E 14
I 14
	    "%s: %s seqnum: %d, slot %d, frags: %d flag: %lld",
	    dp->name, __func__, dp->tx_desc_tail, slot, frags, flag);
E 14
	for (i = 0; i < frags; i++) {
		cmn_err(CE_CONT, "%d: addr: 0x%x, len: 0x%x",
D 14
			i, dmacookie[i].dmac_address, dmacookie[i].dmac_size);
E 14
I 14
		    i, dmacookie[i].dmac_address, dmacookie[i].dmac_size);
E 14
	}
D 13
	ASSERT(frags <= TNE_MAXTXFRAGS);
E 13
#endif
D 9
	tlp->forward_ptr = 0;	/* means this is the last descriptor */
E 9
I 9
D 13
	ddi_put32(h, &tlp->forward_ptr, 0);
E 13
I 13
D 15
	tlp->forward_ptr = 0;
E 13
					/* means this is the last descriptor */
E 15
I 15
	tlp->forward_ptr = dp->tx_ring_dma +
	    (sizeof (struct tx_list)) * SLOT(slot + 1, tx_ring_size);
E 15
E 9
D 8
	tlp->tx_cstat    = TC_MBO;
E 8

	/* copy fragment list */
I 12
D 14
	i   = frags - 1;
E 14
I 14
	i = frags - 1;
E 14
E 12
	len = 0;
D 2
	for (i = 0, dcp = dmacookie; i < frags; i++, dcp++) {
		len += tlp->frags[i].DataCount = dcp->dmac_size;
		tlp->frags[i].DataAddress = dcp->dmac_address;
E 2
I 2
D 12
	tfp = tlp->frags;
	dcp = dmacookie;
D 9
	for (i = frags-1; i-- > 0; tfp++, dcp++) {
E 9
I 9
D 11
	for (i = frags - 1; i-- > 0; tfp++, dcp++) {
E 11
I 11
	for (i = frags; --i >= 0; tfp++, dcp++) {
E 12
I 12
	tfp = &tlp->frags[i];
	dcp = &dmacookie[i];
D 14
	mark= DATACOUNT_LAST;
E 14
I 14
	mark = DATACOUNT_LAST;
E 14
	for (; i-- >= 0; tfp--, dcp--) {
E 12
E 11
E 9
		len += dcp->dmac_size;
D 9
		tfp->DataCount   = dcp->dmac_size;
		tfp->DataAddress = dcp->dmac_address;
E 9
I 9
D 11
		ddi_put32(h, &tfp->DataCount, dcp->dmac_size);
E 11
I 11
D 12
		ddi_put32(h, &tfp->DataCount, 
			((i == 0) ? DATACOUNT_LAST : 0) | dcp->dmac_size);
E 12
I 12
D 13
		ddi_put32(h, &tfp->DataCount, mark | dcp->dmac_size);
E 12
E 11
		ddi_put32(h, &tfp->DataAddress, dcp->dmac_address);
E 13
I 13
D 14
		tfp->DataCount = LE32(mark | dcp->dmac_size);
		tfp->DataAddress = LE32(dcp->dmac_address);
E 14
I 14
		mark |= dcp->dmac_size;
		tfp->DataCount = LE_32(mark);
		addr = dcp->dmac_address;
		tfp->DataAddress = LE_32(addr);
E 14
E 13
I 12
		mark = 0;
E 12
E 9
E 2
	}
I 2
D 11

E 11
I 11
D 12
#if 0
E 11
	/* for last fragment, terminate the fragment list */
D 9
	tfp->DataCount   = DATACOUNT_LAST | dcp->dmac_size;
	tfp->DataAddress = dcp->dmac_address;
E 9
I 9
	ddi_put32(h, &tfp->DataCount, DATACOUNT_LAST | dcp->dmac_size);
	ddi_put32(h, &tfp->DataAddress, dcp->dmac_address);
I 11
#endif
E 11
	ddi_put32(h, &tlp->tx_cstat,
		((len + dcp->dmac_size) << TC_FRAMESIZE_SHIFT) | TC_MBO);
E 12
I 12
D 13
	ddi_put32(h, &tlp->tx_cstat, (len << TC_FRAMESIZE_SHIFT) | TC_MBO);
E 13
I 13
D 14
	tlp->tx_cstat = LE32((len << TC_FRAMESIZE_SHIFT) | TC_MBO);
E 14
I 14
	addr = (len << TC_FRAMESIZE_SHIFT) | TC_MBO;
	tlp->tx_cstat = LE_32(addr);
E 14
E 13
E 12
E 9

D 8
	tlp->framesize = len + dcp->dmac_size;
E 8
I 8
D 9
	tlp->tx_cstat    = ((len + dcp->dmac_size) << TC_FRAMESIZE_SHIFT)
			 |  TC_MBO;
E 8

E 9
E 2
D 15
#ifdef notdef
D 13
	if (frags < TNE_MAXTXFRAGS) {
D 2
		/* need to terminate the fragment list */
		tlp->frags[frag].DataCount = 0;
E 2
I 2
D 9
		tlp->frags[frags].DataCount = 0;
E 9
I 9
		ddi_put32(h, &tlp->frags[frags].DataCount, 0);
E 13
I 13
	if (frags < min(TNE_MAXTXFRAGS, 10)) {
		tlp->frags[frags].DataCount = 0;
E 13
E 9
E 2
	}
#endif
E 15
D 2
	tlp->frags[frags-1].DataCount |= DATACOUNT_LAST;
	tlp->framesize = len;

E 2
D 8
#ifdef IOCACHE
E 8
D 13
	ddi_dma_sync(dp->desc_dma_handle,
		(off_t)(((caddr_t)tlp) - dp->rx_ring),
		sizeof(struct tx_list), DDI_DMA_SYNC_FORDEV);
D 8
#endif
E 8

E 13
D 2
	/* link it into the hardware tx list */
	tlp_dma = dp->tx_ring_dma + ((caddr_t)tlp - (caddr_t)dp->tx_ring);
#if DEBUG_LEVEL > 2
	ASSERT((tlp_dma & 7) == 0);
#endif
E 2
#ifdef TXTIMEOUT_TEST
	tne_send_cnt++;
	if (tne_send_cnt > 100) {
		tne_send_cnt = 0;
D 13
		return 1;
E 13
I 13
		return (1);
E 13
	}
#endif
D 2
	if (dp->tx_desc_head != dp->tx_desc_tail && !lp->tx_last_intreq) {
E 2
I 2
D 13
	if (lp->tx_list_len > 0 && !lp->tx_last_intreq) {
		struct tx_list	*tlpp;
E 13
I 13
D 14
	lp->tx_intreq[slot] = (flag & GEM_TXFLAG_INTR) != 0;

E 14
	return (1);
}

static void
tne_tx_start(struct gem_dev *dp, int start_slot, int nslot)
{
D 15
	int			i;
E 15
	int			slot;
I 14
	uint32_t		addr;
E 14
	struct tx_list		*tlp;
	struct tx_list		*tlpp;
D 14
	struct tne_dev		*lp = (struct tne_dev *)dp->private;
E 14
I 14
	struct tne_dev		*lp = dp->private;
I 15
	const uint_t		tx_ring_size = dp->gc.gc_tx_ring_size;
E 15
E 14

D 15
	i = start_slot + nslot - 1;
	slot = SLOT(i, TX_RING_SIZE);
D 14
	tlp = &((struct tx_list *) dp->tx_ring)[slot];
E 14
I 14
	tlp = &((struct tx_list *)dp->tx_ring)[slot];
E 15
I 15
	/* terminate the new tx list */
	slot = SLOT(start_slot + nslot - 1, tx_ring_size);
	((struct tx_list *)dp->tx_ring)[slot].forward_ptr = 0;
E 15
E 14

D 15
	while (i-- != start_slot) {
E 13
E 2
		/* append this descriptor at the end of current tx list */
D 2
		if (slot == 0) {
			tlp = &((struct tx_list *)dp->tx_ring)[TX_RING_SIZE];
		}
		tlp--;
		tlp->forward_ptr = tlp_dma;
E 2
I 2
D 13
		tlpp = ((struct tx_list *) dp->tx_ring) +
					SLOT(slot-1, TX_RING_SIZE);
D 9
		tlpp->forward_ptr =
			dp->tx_ring_dma + (((caddr_t)tlp) - dp->tx_ring);
E 9
I 9
		ddi_put32(h, &tlpp->forward_ptr,
			dp->tx_ring_dma + (((caddr_t)tlp) - dp->tx_ring));
E 13
I 13
		slot = SLOT(i, TX_RING_SIZE);
D 14
		tlpp = &((struct tx_list *) dp->tx_ring)[slot];
		if (!lp->tx_intreq[slot]) {
			tlpp->forward_ptr = LE32(dp->tx_ring_dma +
						(((caddr_t)tlp) - dp->tx_ring));
		}
E 14
I 14
		tlpp = &((struct tx_list *)dp->tx_ring)[slot];
		addr = dp->tx_ring_dma + (((caddr_t)tlp) - dp->tx_ring);
		tlpp->forward_ptr = LE_32(addr);
E 14
		tlp = tlpp;
	}
E 13
E 9
E 2
D 8
#ifdef IOCACHE
E 8
I 8

E 15
E 8
D 13
		ddi_dma_sync(dp->desc_dma_handle,
D 2
			(off_t)(((caddr_t)tlp) - dp->rx_ring),
E 2
I 2
			(off_t)(((caddr_t)tlpp) - dp->rx_ring),
E 2
			sizeof(struct tx_list), DDI_DMA_SYNC_FORDEV);
E 13
I 13
	/* flush tx descriptors we made */
D 14
	gem_tx_desc_dma_sync(dp, start_slot, nslot-1, DDI_DMA_SYNC_FORDEV);
E 14
I 14
D 15
	gem_tx_desc_dma_sync(dp, start_slot, nslot - 1, DDI_DMA_SYNC_FORDEV);
E 15
I 15
	gem_tx_desc_dma_sync(dp, start_slot, nslot, DDI_DMA_SYNC_FORDEV);
E 15
E 14

D 14
	if (lp->tx_list_len > 0 &&
	   !lp->tx_intreq[SLOT(start_slot-1, TX_RING_SIZE)]) {
E 14
I 14
	if (lp->tx_list_len > 0) {
E 14
D 15
		slot = SLOT(start_slot - 1, TX_RING_SIZE);
D 14
		tlpp = &((struct tx_list *) dp->tx_ring)[slot];
		tlpp->forward_ptr = LE32(dp->tx_ring_dma +
					(((caddr_t)tlp) - dp->tx_ring));
E 14
I 14
		tlpp = &((struct tx_list *)dp->tx_ring)[slot];
		addr = dp->tx_ring_dma + (((caddr_t)tlp) - dp->tx_ring);
		tlpp->forward_ptr = LE_32(addr);
E 15
I 15
		/* link the tx list to the previous descriptor */
		slot = SLOT(start_slot - 1, tx_ring_size);
		addr = dp->tx_ring_dma + start_slot * sizeof (struct tx_list);
		((struct tx_list *)dp->tx_ring)[slot].forward_ptr = LE_32(addr);
E 15
E 14

I 15
		/* flush the previous descriptor */
E 15
		gem_tx_desc_dma_sync(dp, slot, 1, DDI_DMA_SYNC_FORDEV);
E 13
D 8
#endif
E 8
	}
I 2
D 13
	lp->tx_list_len++;
E 13
I 13
	lp->tx_list_len += nslot;
E 13
E 2

D 13
	if (!lp->tx_list_loaded && dp->nic_active) {
E 13
I 13
D 15
	if (!lp->tx_list_loaded && dp->mac_active) {
E 15
I 15
	if (!lp->tx_list_loaded && IS_MAC_ONLINE(dp)) {
E 15
E 13
		/* Restart tx list */
		tne_load_tx_list(dp);
	}
D 13
	lp->tx_last_intreq = flag;

	return 1;
E 13
}

static void
tne_load_rx_list(struct gem_dev *dp)
{
D 14
	struct tne_dev	*lp = (struct tne_dev *)dp->private;
E 14
I 14
	struct tne_dev	*lp = dp->private;
E 14
D 2
	uint32_t		rlp_dma;
E 2

D 2
	rlp_dma = dp->rx_ring_dma
		+ sizeof(struct rx_list) * SLOT(dp->rx_desc_head, RX_RING_SIZE);
E 2
I 2
	ASSERT(!lp->rx_list_loaded);
I 11
	ASSERT(lp->rx_list_len > 0);
E 11
	OUTL(dp, CH_PARM,
D 14
		dp->rx_ring_dma + sizeof(struct rx_list) * lp->rx_list_head);
E 14
I 14
	    dp->rx_ring_dma + sizeof (struct rx_list) * lp->rx_list_head);
E 14
E 2

D 2
	OUTL(dp, CH_PARM, rlp_dma);
E 2
	OUTL(dp, HOST_CMD, HC_RxGO(0));
I 2

E 2
D 13
	lp->rx_list_loaded = TRUE;
E 13
I 13
	lp->rx_list_loaded = B_TRUE;
E 13
}

D 13
static int
tne_rx_desc_write(struct gem_dev *dp, uint_t slot,
E 13
I 13
static void
tne_rx_desc_write(struct gem_dev *dp, int slot,
E 13
	    ddi_dma_cookie_t *dmacookie, int frags)
{
	int			i;
I 14
	uint32_t		addr;
	uint32_t		len;
E 14
	struct rx_list		*rlp;
I 2
D 9
	volatile struct frag	*rfp;
E 9
I 9
	struct frag		*rfp;
E 9
E 2
	ddi_dma_cookie_t	*dcp;
D 2
	uint32_t		rlp_dma;
	struct tne_dev	*lp = (struct tne_dev *)dp->private;
E 2
I 2
D 14
	struct tne_dev		*lp = (struct tne_dev *)dp->private;
E 14
I 14
	struct tne_dev		*lp = dp->private;
I 15
	const uint_t		rx_ring_size = dp->gc.gc_rx_ring_size;
E 15
E 14
I 9
D 13
	ddi_acc_handle_t	h = dp->desc_acc_handle;
E 13
E 9
E 2

	rlp = &((struct rx_list *)dp->rx_ring)[slot];

#if DEBUG_LEVEL > 2
	cmn_err(CE_CONT,
D 13
		"%s: tne_rx_desc_write seqnum: %d, slot %d, frags: %d",
		dp->name, dp->rx_desc_tail, slot, frags);
E 13
I 13
D 14
		"%s: %s seqnum: %d, slot %d, frags: %d",
		dp->name, __func__, dp->rx_active_tail, slot, frags);
E 14
I 14
	    "!%s: %s seqnum: %d, slot %d, frags: %d",
	    dp->name, __func__, dp->rx_active_tail, slot, frags);
E 14
E 13
	for (i = 0; i < frags; i++) {
		cmn_err(CE_CONT, "  frag: %d addr: 0x%x, len: 0x%x",
D 14
			i, dmacookie[i].dmac_address, dmacookie[i].dmac_size);
E 14
I 14
		    i, dmacookie[i].dmac_address, dmacookie[i].dmac_size);
E 14
	}
#endif
I 15
#if 0
E 15
D 2
	ASSERT(frags <= 10);
	rlp->forward_ptr = 0;	/* means this is the last descriptor */
E 2
I 2
D 13
	ASSERT(frags < TNE_MAXRXFRAGS);
D 9
	rlp->forward_ptr = 0;	/* means this is last descriptor in rx list */
E 2
	rlp->rx_cstat    = RC_MBO;
E 9
I 9
	ddi_put32(h, &rlp->forward_ptr, 0);
D 11
				/* means this is last descriptor in rx list */
E 11
I 11
			/* means this is the last descriptor in rx list */
E 11
	ddi_put32(h, &rlp->rx_cstat, RC_MBO);
E 13
I 13
	rlp->forward_ptr = 0; /* means this is the last descriptor in rx list */
I 15
#else
	rlp->forward_ptr = dp->rx_ring_dma +
	    SLOT(slot + 1, rx_ring_size) * sizeof (struct rx_list);
#endif
E 15
D 14
	rlp->rx_cstat = LE32(RC_MBO);
E 14
I 14
	rlp->rx_cstat = LE_32(RC_MBO);
E 14
E 13
E 9
D 8
#if defined(SANITY) || DEBUG_LEVEL > 2
	rlp->framesize   = 0;	/* the initial value is not used by the nic */
#endif
E 8
I 8

E 8
	/* copy fragment list */
D 2
	for (i = 0, dcp = dmacookie; i < frags; i++, dcp++) {
		rlp->frags[i].DataCount   = (uint32_t)dcp->dmac_size;
		rlp->frags[i].DataAddress = (uint32_t)dcp->dmac_address;
E 2
I 2
	rfp = rlp->frags;
	dcp = dmacookie;
	for (i = frags; i--; rfp++, dcp++) {
D 9
		rfp->DataCount   = (uint32_t)dcp->dmac_size;
		rfp->DataAddress = (uint32_t)dcp->dmac_address;
E 9
I 9
D 13
		ddi_put32(h, &rfp->DataCount, (uint32_t)dcp->dmac_size);
		ddi_put32(h, &rfp->DataAddress, (uint32_t)dcp->dmac_address);
E 13
I 13
D 14
		rfp->DataCount   = LE32((uint32_t) dcp->dmac_size);
		rfp->DataAddress = LE32((uint32_t) dcp->dmac_address);
E 14
I 14
		len = (uint32_t)dcp->dmac_size;
		rfp->DataCount = LE_32(len);
		addr = (uint32_t)dcp->dmac_address;
		rfp->DataAddress = LE_32(addr);
E 14
E 13
E 9
E 2
	}
D 2
	/* need to terminate the rx fragment list */
	rlp->frags[i].DataCount = 0;
E 2
I 2
D 15
	/* Add a zero length fragment to terminate the rx fragment list */
E 15
I 15

	/*
	 * Add a zero length fragment to terminate
	 * the rx fragment list
	 */
E 15
D 9
	rfp->DataCount = 0;
E 9
I 9
D 13
	ddi_put32(h, &rfp->DataCount, 0);
E 13
I 13
	rfp->DataCount = 0;
}
E 13
E 9
E 2
D 8
#ifdef IOCACHE
E 8
I 8

E 8
D 13
	ddi_dma_sync(dp->desc_dma_handle,
		(off_t)(((caddr_t)rlp) - dp->rx_ring),
		sizeof(struct rx_list), DDI_DMA_SYNC_FORDEV);
E 13
I 13
static void
tne_rx_start(struct gem_dev *dp, int start_slot, int nslots)
{
	int			i;
	int			slot;
I 14
	uint32_t		addr;
D 15
	uint_t			rx_ring_size = dp->gc.gc_rx_ring_size;
E 15
I 15
	const uint_t		rx_ring_size = dp->gc.gc_rx_ring_size;
E 15
E 14
	struct rx_list		*rlp;
	struct rx_list		*rlpp;
D 14
	struct tne_dev		*lp = (struct tne_dev *)dp->private;
E 14
I 14
	struct tne_dev		*lp = dp->private;
E 14
E 13
D 8
#endif
E 8
I 8

E 8
D 2
	/* link it into the hardware rx list */
	rlp_dma = dp->rx_ring_dma + ((caddr_t)rlp - (caddr_t)dp->rx_ring);
#if DEBUG_LEVEL > 2
	ASSERT((rlp_dma & 7) == 0);
#endif
	if (dp->rx_desc_head != dp->rx_desc_tail)  {
		/* Link this to the previous slot and kick Rx engine */
		if (slot == 0) {
			rlp = &((struct rx_list *)dp->rx_ring)[RX_RING_SIZE];
		}
		rlp--;
		rlp->forward_ptr = rlp_dma;
E 2
I 2
D 13
	if (lp->rx_list_len++ > 0)  {
		struct rx_list		*rlpp;
E 13
I 13
#if DEBUG_LEVEL > 2
	cmn_err(CE_CONT,
D 14
		"%s: %s: start_slot %d, nslots: %d",
		dp->name, __func__, start_slot, nslots);
E 14
I 14
	    "!%s: %s: start_slot %d, nslots: %d",
	    dp->name, __func__, start_slot, nslots);
E 14
#endif
	i = start_slot + nslots - 1;
D 14
	slot = SLOT(i, RX_RING_SIZE);
	rlp = &((struct rx_list *) dp->rx_ring)[slot];
E 14
I 14
	slot = SLOT(i, rx_ring_size);
	rlp = &((struct rx_list *)dp->rx_ring)[slot];
E 14
E 13
D 15

E 15
I 15
#if 0
E 15
I 13
	while (i-- != start_slot) {
		/* append this descriptor at the end of current rx list */
D 14
		slot = SLOT(i, RX_RING_SIZE);
		rlpp = &((struct rx_list *) dp->rx_ring)[slot];
		rlpp->forward_ptr = LE32(dp->rx_ring_dma +
						(((caddr_t)rlp) - dp->rx_ring));
E 14
I 14
		slot = SLOT(i, rx_ring_size);
		rlpp = &((struct rx_list *)dp->rx_ring)[slot];
		addr = dp->rx_ring_dma + (((caddr_t)rlp) - dp->rx_ring);
		rlpp->forward_ptr = LE_32(addr);
E 14
		rlp = rlpp;
	}
D 15

E 15
I 15
#else
	/* terminate rx list */
	rlp->forward_ptr = 0;
#endif
E 15
	/* flush rx descriptors we made */
	gem_rx_desc_dma_sync(dp, start_slot, nslots, DDI_DMA_SYNC_FORDEV);

	if (lp->rx_list_len > 0)  {
E 13
		/* Link it to the previous slot */
D 13
		rlpp = &((struct rx_list *)
				dp->rx_ring)[SLOT(slot - 1, RX_RING_SIZE)];
D 9
		rlpp->forward_ptr =
			dp->rx_ring_dma + ((caddr_t)rlp - (caddr_t)dp->rx_ring);
E 9
I 9
		ddi_put32(h, &rlpp->forward_ptr,
			dp->rx_ring_dma+((caddr_t)rlp-(caddr_t)dp->rx_ring));
E 13
I 13
D 14
		slot = SLOT(start_slot - 1, RX_RING_SIZE);
		rlpp = &((struct rx_list *) dp->rx_ring)[slot];
		rlpp->forward_ptr = LE32(dp->rx_ring_dma +
					((caddr_t)rlp-(caddr_t)dp->rx_ring));
E 14
I 14
		slot = SLOT(start_slot - 1, rx_ring_size);
D 15
		rlpp = &((struct rx_list *)dp->rx_ring)[slot];
		addr = dp->rx_ring_dma + ((caddr_t)rlp-(caddr_t)dp->rx_ring);
		rlpp->forward_ptr = LE_32(addr);
E 15
I 15
		addr = dp->rx_ring_dma + start_slot * sizeof (struct rx_list);
		((struct rx_list *)dp->rx_ring)[slot].forward_ptr = LE_32(addr);
E 15
E 14
E 13
E 9
E 2
D 8
#ifdef IOCACHE
E 8
I 8

E 8
D 13
		ddi_dma_sync(dp->desc_dma_handle,
			(off_t)(((caddr_t)rlp) - dp->rx_ring),
			sizeof(struct rx_list), DDI_DMA_SYNC_FORDEV);
E 13
I 13
		gem_rx_desc_dma_sync(dp, slot, 1, DDI_DMA_SYNC_FORDEV);
E 13
D 8
#endif
E 8
	}
I 2
D 11
#ifdef notdef
E 2
	if (!lp->rx_list_loaded && dp->nic_active) {
		/* Treat this as the head of new rx list, tell to nic */
		tne_load_rx_list(dp);
	}
I 2
#endif
E 11
I 11

E 11
E 2
D 13
	return 1;
E 13
I 13
	lp->rx_list_len += nslots;

D 15
	if (!lp->rx_list_loaded && dp->mac_active) {
E 15
I 15
	if (!lp->rx_list_loaded && IS_MAC_ONLINE(dp)) {
E 15
		/* Restart rx list */
		tne_load_rx_list(dp);
	}
E 13
}

static uint_t
tne_tx_desc_stat(struct gem_dev *dp, int slot, int ndesc)
{
D 9
	struct tx_list	*tlp;
	uint16_t	cstat;
I 2
	struct tne_dev	*lp = (struct tne_dev *)dp->private;
E 9
I 9
	struct tx_list		*tlp;
	uint16_t		cstat;
D 14
	struct tne_dev		*lp = (struct tne_dev *)dp->private;
E 14
I 14
	struct tne_dev		*lp = dp->private;
E 14
D 13
	ddi_acc_handle_t	h = dp->desc_acc_handle;
E 13
E 9
E 2

	tlp = &((struct tx_list *)dp->tx_ring)[slot];
D 8
#ifdef IOCACHE
E 8
I 8
D 13

E 13
I 13
D 14
#ifdef notdef
E 13
E 8
	ddi_dma_sync(dp->desc_dma_handle,
		(off_t)(((caddr_t)tlp) - dp->rx_ring),
		sizeof(struct tx_list), DDI_DMA_SYNC_FORKERNEL);
I 13
#endif
	cstat = LE32(tlp->tx_cstat);
E 14
I 14
	cstat = tlp->tx_cstat;
	cstat = LE_32(cstat);
E 14
E 13
D 8
#endif
E 8
I 8

E 8
D 9
	cstat = tlp->tx_cstat;
E 9
I 9
D 13
	cstat = ddi_get32(h, &tlp->tx_cstat);
E 9

E 13
	DPRINTF(2, (CE_CONT,
D 14
		"!%s: tne_tx_desc_stat: slot:%d, tx_cstat:0x%b",
		dp->name, slot, tlp->tx_cstat, TC_BITS));
E 14
I 14
	    "!%s: %s: slot:%d, tx_cstat:0x%b",
	    dp->name, __func__, slot, tlp->tx_cstat, TC_BITS));
E 14

	if ((cstat & TC_FrmCmp) == 0) {
		/* not transmitted */
D 13
		return 0;
E 13
I 13
		return (0);
E 13
	}
I 2

	ASSERT(lp->tx_list_len > 0);
	lp->tx_list_len--;
	lp->tx_list_done++;
D 15
	lp->tx_list_head = SLOT(slot + 1, TX_RING_SIZE);
E 15
I 15
	lp->tx_list_head = SLOT(slot + 1, dp->gc.gc_tx_ring_size);
E 15

E 2
D 13
	return GEM_TX_DONE;
E 13
I 13
	return (GEM_TX_DONE);
E 13
}

#ifdef DEBUG_LEVEL
static void
tne_dump_packet(struct gem_dev *dp, uint8_t *bp, int n)
{
	int	i;

D 14
	for (i=0; i < n; i += 8, bp += 8) {
E 14
I 14
	for (i = 0; i < n; i += 8, bp += 8) {
E 14
		cmn_err(CE_CONT, "%02x %02x %02x %02x %02x %02x %02x %02x",
D 14
		bp[0], bp[1], bp[2], bp[3], bp[4], bp[5], bp[6], bp[7]);
E 14
I 14
		    bp[0], bp[1], bp[2], bp[3], bp[4], bp[5], bp[6], bp[7]);
E 14
	}
}
#endif
D 13
static uint_t
E 13
I 13
static uint64_t
E 13
tne_rx_desc_stat(struct gem_dev *dp, int slot, int ndesc)
{
D 9
	struct rx_list	*rlp;
	uint_t		flag;
	uint_t		len;
D 8
	uint16_t	cstat;
E 8
I 8
	uint32_t	cstat;
E 8
I 2
	struct tne_dev	*lp = (struct tne_dev *)dp->private;
E 9
I 9
	struct rx_list		*rlp;
	uint_t			flag;
	uint_t			len;
	uint32_t		cstat;
D 14
	struct tne_dev		*lp = (struct tne_dev *)dp->private;
E 14
I 14
	struct tne_dev		*lp = dp->private;
E 14
D 13
	ddi_acc_handle_t	h = dp->desc_acc_handle;
E 13
E 9
E 2

	rlp = &((struct rx_list *)dp->rx_ring)[slot];
D 8
#ifdef IOCACHE
E 8
I 8
D 13

E 13
I 13
D 14
#ifdef notdef
E 13
E 8
	ddi_dma_sync(dp->desc_dma_handle,
		(off_t)(((caddr_t)rlp) - dp->rx_ring),
		sizeof(struct rx_list), DDI_DMA_SYNC_FORKERNEL);
I 13
#endif
	cstat = LE32(rlp->rx_cstat);
E 14
I 14
	cstat = rlp->rx_cstat;
	cstat = LE_32(cstat);
E 14
E 13
D 8
#endif
E 8

D 9
	cstat = rlp->rx_cstat;
E 9
I 9
D 13
	cstat = ddi_get32(h, &rlp->rx_cstat);

E 13
E 9
I 2
	if ((cstat & RC_FrmCmp) == 0) {
		/* not received */
D 13
		return 0;
E 13
I 13
		return (0);
E 13
	}

E 2
D 8
	len  = rlp->framesize;
E 8
I 8
D 14
	len  = (cstat >> RC_FRAMESIZE_SHIFT) & RC_FRAMESIZE_MASK;
E 14
I 14
	len = (cstat >> RC_FRAMESIZE_SHIFT) & RC_FRAMESIZE_MASK;
E 14
E 8
	flag = GEM_RX_DONE;

	DPRINTF(2, (CE_CONT,
D 8
		"!%s: tne_rx_desc_stat: slot:%d, rx_cstat:0x%b framesize:0x%x",
		dp->name, slot, cstat, RC_BITS, len));
E 8
I 8
D 14
		"!%s: tne_rx_desc_stat: slot:%d, rx_cstat:0x%b",
		dp->name, slot, cstat, RC_BITS));
E 14
I 14
	    "!%s: %s: slot:%d, rx_cstat:0x%b",
	    dp->name, __func__, slot, cstat, RC_BITS));
E 14
E 8

D 2
	if ((cstat & RC_FrmCmp) == 0) {
		/* not received */
		return 0;
	}
E 2
I 2
	ASSERT(lp->rx_list_len > 0);
	lp->rx_list_len--;
	lp->rx_list_done++;
D 14
	lp->rx_list_head = SLOT(slot + 1, RX_RING_SIZE);
E 14
I 14
	lp->rx_list_head = SLOT(slot + 1, dp->gc.gc_rx_ring_size);
E 14
E 2

D 14
	if ((cstat & RC_RxError) != 0) {
E 14
I 14
	if (cstat & RC_RxError) {
		DPRINTF(0, (CE_WARN,
		    "!%s: %s: slot:%d, rx_cstat:0x%b",
		    dp->name, __func__, slot, cstat, RC_BITS));
E 14
		flag |= GEM_RX_ERR;
	}

D 2
	if (len > ETHERFCSL) {
		len -= ETHERFCSL;
	}

E 2
#if DEBUG_LEVEL > 3
	tne_dump_packet(dp, dp->rx_buf_head->rxb_buf, len);
#endif
D 13
	return flag | len;
E 13
I 13
	return (flag | len);
E 13
}

static void
tne_tx_desc_init(struct gem_dev *dp, int slot)
{
D 2
	struct tx_list	*tlp;

	tlp = &((struct tx_list *)dp->tx_ring)[slot];
E 2
I 2
	/* do nothing */
E 2
}

static void
tne_rx_desc_init(struct gem_dev *dp, int slot)
{
D 2
	struct rx_list	*rlp;

	rlp = &((struct rx_list *)dp->rx_ring)[slot];
E 2
I 2
	/* do nothing */
E 2
}

/*
 * Device depend interrupt handler
 */
static void
tne_adapter_check(struct gem_dev *dp)
{
	uint32_t	check_code;
	uint_t		channel;
	uint8_t		failure_code;
	static char	*failure_name[] = {
		"",
		"Data parity error",
		"Address parity error",
		"Master abort",
		"Target abort",
		"List error",
		"Acknowledge error",
		"Int overflow error",
	};

	check_code = INL(dp, CH_PARM);
	channel = (check_code & AdC_Channel) >> AdC_Channel_SHIFT;
	failure_code = check_code & AdC_FailureCode;

	cmn_err(CE_WARN, "%s: adaptor failure happened. "
D 14
		"failure_code:%x (%s) %s %s %s",
		dp->name,
		failure_code,
		(failure_code >= 1 && failure_code <= 7)
			? failure_name[failure_code] : "unknwon error",
		(check_code & AdC_List) ? "List/EOC" : "Data/EOF",
		(check_code & AdC_Rx) ? "Rx" : "Tx",
		(check_code & AdC_Rd) ? "Read" : "Write");
E 14
I 14
	    "failure_code:%x (%s) %s %s %s",
	    dp->name,
	    failure_code,
	    (failure_code >= 1 && failure_code <= 7)
	    ? failure_name[failure_code] : "unknwon error",
	    (check_code & AdC_List) ? "List/EOC" : "Data/EOF",
	    (check_code & AdC_Rx) ? "Rx" : "Tx",
	    (check_code & AdC_Rd) ? "Read" : "Write");
E 14

D 14
	tne_get_stats(dp);
E 14
I 14
	(void) tne_get_stats(dp);
E 14
}

D 14
static u_int
E 14
I 14
#ifdef DEBUG_LEVEL
static char *tne_inttype_names[] = {
	"NoIntr",
	"TxEOF",
	"StatisticsOvf",
	"RxEOF",
	"Dummy",
	"TxEOC",
	"AdNet",
	"RxEOC",
};
#endif
static uint_t
E 14
tne_interrupt(struct gem_dev *dp)
{
	uint16_t	host_int;
D 2
	uint_t		int_type;
	uint_t		int_vec;
E 2
I 2
	uint8_t		int_type;
	uint16_t	int_vec;
E 2
D 13
	boolean_t	tx_sched = FALSE;
E 13
I 13
	boolean_t	tx_sched = B_FALSE;
E 13
	int		loop;
D 2
	uint8_t		ack_count;
E 2
D 13
	boolean_t	need_to_reset = FALSE;
E 13
I 13
	boolean_t	need_to_reset = B_FALSE;
E 13
I 2
	uint16_t	netsts;
E 2
D 14
	struct tne_dev	*lp = (struct tne_dev *)dp->private;
E 14
I 14
	struct tne_dev	*lp = dp->private;
E 14

D 2
	DPRINTF(2, (CE_CONT, "!%s: tne_interrupt: called", dp->name));
E 2
I 2
D 13
	DPRINTF(3, (CE_CONT, "!%s: tne_interrupt: called", dp->name));
E 13
I 13
D 14
	DPRINTF(2, (CE_CONT, "!%s: tne_interrupt: called", dp->name));
E 14
I 14
	DPRINTF(2, (CE_CONT, "!%s: %s: called", dp->name, __func__));
E 14
E 13
E 2

	host_int = INW(dp, HOST_INT);
	int_type = (host_int & HI_IntType) >> HI_IntType_SHIFT;
D 14
	int_vec  = (host_int & HI_IntVec) >> HI_IntVec_SHIFT;
E 14
I 14
	int_vec = (host_int & HI_IntVec) >> HI_IntVec_SHIFT;
E 14

	if (int_type == IntType_NoIntr) {
		/* not for us */
D 13
		return DDI_INTR_UNCLAIMED;
E 13
I 13
		return (DDI_INTR_UNCLAIMED);
E 13
	}
D 2

	/* Disable all interrupts */
	OUTL(dp, HOST_CMD, HC_IntsOff);

E 2
I 2
D 6
#ifndef OPT_INTR
	if ((dp->misc_flag & GEM_NOINTR) == 0) {
		/* Disable all interrupts */
		OUTL(dp, HOST_CMD, HC_IntsOff);
	}
#endif
E 6
I 6

E 6
E 2
D 7
	if (!dp->nic_active) {
I 2
D 6
#ifdef OPT_INTR
E 6
		/* Disable all interrupts */
		OUTL(dp, HOST_CMD, HC_IntsOff);
E 7
I 7
	/* Disable all interrupts */
	OUTL(dp, HOST_CMD, HC_IntsOff);
D 8
#ifdef MAP_MEM
E 8
I 8
#ifdef MAP_MEMx
E 8
	FLSHL(dp, HOST_CMD);
#endif
E 7
D 6
#endif
E 6
I 6

I 7
D 13
	if (!dp->nic_active) {
E 13
I 13
D 15
	if (!dp->mac_active) {
E 15
I 15
	if (!IS_MAC_ONLINE(dp)) {
E 15
E 13
E 7
E 6
E 2
		/* Ack */
		OUTW(dp, HOST_INT, host_int);
D 13
		return DDI_INTR_CLAIMED;
E 13
I 13
		return (DDI_INTR_CLAIMED);
E 13
	}

I 9
D 13
#ifdef CONFIG_POLLING
E 13
I 13
D 14
#ifdef GEM_CONFIG_POLLING
E 14
I 14
#ifdef CONFIG_POLLING
E 14
E 13
	if (dp->speed == GEM_SPD_100 &&
	    lp->last_poll_interval != dp->poll_interval) {
		/*
		 * update interrupt pacing timer
D 13
		 * we use half polling period expected.
E 13
I 13
		 * we actually poll four times in expected polling interval.
E 13
		 */
D 11
		OUTL(dp, HOST_CMD, HC_LdTmr | min(dp->poll_interval/4/2, 255));
E 11
I 11
D 14
		OUTL(dp, HOST_CMD, HC_LdTmr | min(dp->poll_interval/4, 255));
E 14
I 14
		OUTL(dp, HOST_CMD,
		    HC_LdTmr | min(dp->poll_interval/6000, 255));
E 14
E 11
		lp->last_poll_interval = dp->poll_interval;
	}
D 13
#endif /* CONFIG_POLLING */
E 13
I 13
D 14
#endif /* GEM_CONFIG_POLLING */
E 14
I 14
#endif /* CONFIG_POLLING */
E 14
E 13

E 9
	/*
	 * Read interrupt status
	 */
	loop = 100;
	do {
		/* Ack */
		OUTW(dp, HOST_INT, host_int);
D 7

E 7
I 7
D 8
#ifdef MAP_MEM
E 8
I 8
D 14
#ifdef MAP_MEMx
E 8
		FLSHW(dp, HOST_INT);
#endif
E 7
		DPRINTF(2, (CE_CONT, "!%s: tne_interrupt: type:0x%x vec:0x%x",
			dp->name, int_type, int_vec));
E 14

I 14
		DPRINTF(3, (CE_CONT, "!%s: %s: type:%s(%d) vec:0x%x",
		    dp->name, __func__,
		    tne_inttype_names[int_type], int_type, int_vec));

E 14
D 2
		ack_count = 0;
E 2
		switch (int_type) {
#ifdef DEBUG_LEVEL
		case IntType_NoIntr:
			/* Never happen */
			cmn_err(CE_PANIC, "%s: NoInter happened", dp->name);
			/* NOT REACHED */
			break;
#endif
		case IntType_TxEOF:
I 15
#ifdef GEM3
			gem_reclaim_txbuf(dp);
#endif
E 15
			if (gem_tx_done(dp)) {
D 13
				tx_sched = TRUE;
E 13
I 13
				tx_sched = B_TRUE;
E 13
			}
D 2
			/* ack (dp->tx_desc_head - lp->tx_last_ack) frames */
			ack_count = dp->tx_desc_head - lp->tx_last_ack;
			lp->tx_last_ack = dp->tx_desc_head;
E 2

I 2
D 14
			/* ack number of transmitted frames */
E 14
I 14
			/* ack the number of transmitted frames */
E 14
			mutex_enter(&dp->xmitlock);
E 2
			OUTL(dp, HOST_CMD,
D 2
				HC_Ack | (host_int << 16) | ack_count);
E 2
I 2
D 14
				HC_Ack | (host_int << 16) | lp->tx_list_done);
E 14
I 14
			    HC_Ack | (host_int << 16) | lp->tx_list_done);
E 14
			lp->tx_list_done = 0;
			mutex_exit(&dp->xmitlock);
E 2
			break;

		case IntType_StatisticsOvf:
			/*
			 * Statistics counter overflow
			 */
D 14
			tne_get_stats(dp);
E 14
I 14
			(void) tne_get_stats(dp);
E 14

			OUTL(dp, HOST_CMD, HC_Ack | (host_int << 16));
			break;

		case IntType_RxEOF:
			/*
			 * packet was received, or receive error happened
			 */
D 14
			gem_receive(dp);
E 14
I 14
			(void) gem_receive(dp);
E 14

D 14
			/* notify number of received frames to the nic */
E 14
I 14
			/* notify the number of received frames to nic */
E 14
D 2
			ack_count = dp->rx_desc_head - lp->rx_last_ack;
			lp->rx_last_ack = dp->rx_desc_head;

E 2
			OUTL(dp, HOST_CMD,
D 2
				HC_Ack | (host_int << 16) | ack_count);
E 2
I 2
D 14
				HC_Ack | (host_int << 16) | lp->rx_list_done);
E 14
I 14
			    HC_Ack | (host_int << 16) | lp->rx_list_done);
E 14
			lp->rx_list_done = 0;
E 2
			break;

		case IntType_Dummy:
			OUTL(dp, HOST_CMD, HC_Ack | (host_int << 16));
			break;

		case IntType_TxEOC:
I 14
#ifndef CONFIG_POLLING
E 14
			if (gem_tx_done(dp)) {
D 13
				tx_sched = TRUE;
E 13
I 13
				tx_sched = B_TRUE;
E 13
			}
I 2
D 14

E 14
I 14
#endif
E 14
E 2
			/* ack and start again */
			OUTL(dp, HOST_CMD, HC_Ack | (host_int << 16));
I 2

			mutex_enter(&dp->xmitlock);
E 2
D 13
			lp->tx_list_loaded = FALSE;
E 13
I 13
			lp->tx_list_loaded = B_FALSE;
E 13

D 2
			if (dp->tx_desc_head != dp->tx_desc_tail) {
E 2
I 2
			if (lp->tx_list_len > 0) {
E 2
				/* start tx again */
				tne_load_tx_list(dp);
D 2
				lp->tx_list_loaded = TRUE;
E 2
			}
I 2
			mutex_exit(&dp->xmitlock);
E 2
			break;

		case IntType_AdNet:
D 14
			if (int_vec != 0) {
E 14
I 14
			if (int_vec) {
E 14
				tne_adapter_check(dp);
D 13
				need_to_reset = TRUE;
E 13
I 13
				need_to_reset = B_TRUE;
E 13
				goto x;
			}
D 2
			else {
				/* Never happen */
				uint16_t	netsts;
E 2
I 2
D 14
			/* Never happen */
E 14
I 14
			/* never happen */
E 14
E 2

D 2
				/* clear the NetSTS register */
				netsts = INW_DIO(dp, NETSTS);
				OUTW_DIO(dp, NETSTS, netsts);
				
				OUTL(dp, HOST_CMD, HC_Ack | (host_int << 16));
			}
E 2
I 2
D 14
			/* clear the NetSTS register */
E 14
I 14
			/* clear NetSTS register */
E 14
			netsts = INW_DIO(dp, NETSTS);
			OUTW_DIO(dp, NETSTS, netsts);
			OUTL(dp, HOST_CMD, HC_Ack | (host_int << 16));
E 2
			break;

		case IntType_RxEOC:
D 14
			/*  try to allocate Rx buffer */
E 14
I 14
			/*  try to allocate Rx buffers */
E 14
			/* ack and start again */
			OUTL(dp, HOST_CMD, HC_Ack | (host_int << 16));
D 13
			lp->rx_list_loaded = FALSE;
E 13
I 13
			lp->rx_list_loaded = B_FALSE;
E 13
I 11
			dp->stats.norcvbuf++;

E 11
D 2
			if (dp->rx_desc_head != dp->rx_desc_tail) {
E 2
I 2
			if (lp->rx_list_len > 0) {
E 2
				/* start rx again */
				tne_load_rx_list(dp);
D 14
			}
I 11
			else {
E 14
I 14
			} else {
E 14
D 13
				need_to_reset = TRUE;
E 13
I 13
				need_to_reset = B_TRUE;
E 13
				goto x;
			}
E 11
			break;
		}
D 7

E 7
I 7
D 8
#ifdef MAP_MEM
E 8
I 8
D 14
#ifdef MAP_MEMx
E 8
		FLSHL(dp, HOST_CMD);
#endif
E 14
I 14

E 14
E 7
		host_int = INW(dp, HOST_INT);
		int_type = (host_int & HI_IntType) >> HI_IntType_SHIFT;
D 14
		int_vec  = (host_int & HI_IntVec) >> HI_IntVec_SHIFT;
E 14
I 14
		int_vec = (host_int & HI_IntVec) >> HI_IntVec_SHIFT;
E 14

	} while (int_type != IntType_NoIntr && --loop > 0);

x:
I 6
	if (loop <= 0) {
D 13
		need_to_reset = TRUE;
E 13
I 13
		need_to_reset = B_TRUE;
E 13
D 15
		cmn_err(CE_WARN, "%s: interrupts maxmum exceeded", dp->name);
E 15
I 15
		cmn_err(CE_WARN,
		    "%s: interrupts maxmum exceeded, "
		    "type:%s(%d) vec:0x%x",
		    dp->name,
		    tne_inttype_names[int_type], int_type, int_vec);
E 15
	}

E 6
	if (need_to_reset) {
I 2
		/* Disable all interrupts */
		OUTL(dp, HOST_CMD, HC_IntsOff);

		/* Clear all interrupt */
		OUTW(dp, HOST_INT, INW(dp, HOST_INT));

E 2
D 13
		mutex_enter(&dp->xmitlock);
		gem_restart_tx(dp);
		mutex_exit(&dp->xmitlock);
		tx_sched = TRUE;
I 2
D 6
#ifdef OPT_INTR
E 6
I 6

E 13
I 13
		gem_restart_nic(dp, GEM_RESTART_KEEP_BUF);
		tx_sched = B_TRUE;
E 13
E 6
D 5
		/* Enable all interrupts */
		OUTL(dp, HOST_CMD, HC_IntsOn);
E 5
I 5
D 7
		if ((dp->misc_flag & GEM_NOINTR) == 0 && loop > 0) {
			/* Enable all interrupts */
			OUTL(dp, HOST_CMD, HC_IntsOn);
		}
E 7
E 5
D 6
#endif
E 6
E 2
	}
I 7

	if ((dp->misc_flag & GEM_NOINTR) == 0 && loop > 0) {
		/* Enable all interrupts again */
		OUTL(dp, HOST_CMD, HC_IntsOn);
	}
E 7
D 6

E 6
I 6
#if DEBUG_LEVEL > 2
E 6
I 2
	if (tx_sched) {
D 6
		DPRINTF(0, (CE_CONT, "!%s: rescheding blocked tx", dp->name));
E 6
I 6
		cmn_err(CE_CONT, "!%s: rescheduling blocked tx", dp->name);
E 6
	}
D 6

E 6
I 6
#endif
E 6
E 2
	/*
	 * Recover Interrput Enable register
	 */
D 2
#if DEBUG_LEVEL > 4
E 2
D 14
	DPRINTF(4, (CE_CONT, "!%s: tne_inter done", dp->name));
E 14
I 14
	DPRINTF(4, (CE_CONT, "!%s: %s done", dp->name, __func__));
E 14
D 2
#endif
	if ((dp->misc_flag & GEM_NOINTR) == 0 || loop == 0) {
		/*
		 * Enable interrupts again
		 */
E 2
I 2

D 6
#ifndef OPT_INTR
	if ((dp->misc_flag & GEM_NOINTR) == 0 && loop > 0) {
		/* re-enable all interrupts */
E 2
		OUTL(dp, HOST_CMD, HC_IntsOn);
I 2
	} else
#endif
	if (loop == 0) {
		/* Disable all interrupts */
		OUTL(dp, HOST_CMD, HC_IntsOff);
E 2
	}

E 6
D 13
	return DDI_INTR_CLAIMED | (tx_sched ? INTR_RESTART_TX : 0);
E 13
I 13
	return (DDI_INTR_CLAIMED | (tx_sched ? INTR_RESTART_TX : 0));
E 13
}

/*
 * HW depend MII routine
 */
D 14
#define MDIO_DELAY(dp)    {INB_DIO(dp, NETSIO);}
E 14
I 14
#define	MDIO_DELAY(dp)	{ INB_DIO(dp, NETSIO); INB_DIO(dp, NETSIO); }
E 14

static void
tne_mii_sync(struct gem_dev *dp)
{
	int		i;
	uint8_t		diodata;

	/* output 32 ones */
	OUTW(dp, DIO_ADR, NETSIO);

D 2
	diodata = INB_DIO(dp, NETSIO);
	diodata &= ~NSIO_MTXEN | NSIO_MCLK;
E 2
I 2
D 6
	diodata = INB_DIO(dp, NETSIO) | NSIO_MTXEN;
	diodata &= ~NSIO_MCLK;
E 6
I 6
	diodata = INB_DIO(dp, NETSIO) | NSIO_MDATA | NSIO_MTXEN;
	diodata &= ~(NSIO_MINTEN | NSIO_MCLK);
E 6
E 2
	for (i = 0; i < 32; i++) {
		OUTB_DIO(dp, NETSIO, diodata);
		MDIO_DELAY(dp);
D 2
		OUTB_DIO(dp, NETSIO, diodata| NSIO_MCLK);
E 2
I 2
		OUTB_DIO(dp, NETSIO, diodata | NSIO_MCLK);
E 2
		MDIO_DELAY(dp);
	}
D 2
	OUTB_DIO(dp, NETSIO, diodata);
E 2
}

static uint16_t
D 11
tne_mii_read(struct gem_dev *dp, int reg)
E 11
I 11
D 14
tne_mii_read(struct gem_dev *dp, uint_t reg)
E 14
I 14
tne_mii_read_raw(struct gem_dev *dp, uint_t phy, uint_t reg)
E 14
E 11
{
	uint32_t	cmd;
	uint16_t	ret;
	int		i;
	uint8_t		data;
	uint8_t		diodata;
I 14
	uint32_t	valid_mask = 0xffff;
E 14

D 6
	tne_mii_sync(dp);

E 6
D 14
	cmd = MII_READ_CMD(dp->mii_phy_addr, reg);
E 14
I 14
	cmd = MII_READ_CMD(phy, reg);
E 14

	OUTW(dp, DIO_ADR, NETSIO);

	diodata = INB_DIO(dp, NETSIO);
	DPRINTF(4, (CE_CONT,
D 14
		"!%s: tne_mii_read: diodata: 0x%02x", dp->name, diodata));
E 14
I 14
	    "!%s: %s: diodata: 0x%02x", dp->name, __func__, diodata));
E 14

	diodata &= ~(NSIO_MINTEN | NSIO_MDATA | NSIO_MTXEN | NSIO_MCLK);
	diodata |= NSIO_MTXEN;

D 2
	OUTB_DIO(dp, NETSIO, diodata | NSIO_MDATA);
	MDIO_DELAY(dp);
	OUTB_DIO(dp, NETSIO, diodata | NSIO_MDATA | NSIO_MCLK);
	MDIO_DELAY(dp);

E 2
	for (i = 31; i >= 18; i--) {
I 2
		/* notify the phy to send data */
E 2
		data = (((cmd >> i) & 1) <<  NSIO_MDATA_SHIFT) | diodata;
		OUTB_DIO(dp, NETSIO, data);
		MDIO_DELAY(dp);
I 2

		/* notify to the phy that data is stable */
E 2
		OUTB_DIO(dp, NETSIO, data | NSIO_MCLK);
		MDIO_DELAY(dp);
	}
D 2

E 2
I 2
	/* turn araund */
E 2
	diodata &= ~NSIO_MTXEN;
	OUTB_DIO(dp, NETSIO, diodata);
	MDIO_DELAY(dp);

D 2
	for (i = 17; i > 0; i--) {
		OUTB_DIO(dp, NETSIO, diodata | NSIO_MCLK);
		MDIO_DELAY(dp);
		ret = (ret << 1)
		    | ((INB_DIO(dp, NETSIO) >> NSIO_MDATA_SHIFT) & 1);
		OUTB_DIO(dp, NETSIO, diodata);
		MDIO_DELAY(dp);
E 2
I 2
	/* notify to the phy to send ack */
	OUTB_DIO(dp, NETSIO, diodata | NSIO_MCLK);
	MDIO_DELAY(dp);

	/* get response from the phy */
	OUTB_DIO(dp, NETSIO, diodata);
D 14
	if ((INB_DIO(dp, NETSIO) & NSIO_MDATA) != 0) {
D 6
		DPRINTF(0, (CE_CONT, "!%s: phy@%d didn't respond",
E 6
I 6
		DPRINTF(2, (CE_CONT, "!%s: phy@%d didn't respond",
E 6
			dp->name, dp->mii_phy_addr));
E 14
I 14
	if (INB_DIO(dp, NETSIO) & NSIO_MDATA) {
		DPRINTF(4, (CE_CONT, "!%s: %s: phy@%d didn't respond",
		    dp->name, __func__, phy));
		valid_mask = 0;
E 14
E 2
	}

I 14
	ret = 0;
E 14
D 2
	for (i = 0; i < 2; i++) {
E 2
I 2
	for (i = 16; i > 0; i--) {
		/* notify the phy to send data */
E 2
		OUTB_DIO(dp, NETSIO, diodata | NSIO_MCLK);
		MDIO_DELAY(dp);
I 2

		/* down the clock (actual latch timing) */
E 2
		OUTB_DIO(dp, NETSIO, diodata);
D 2
		MDIO_DELAY(dp);
E 2
I 2

		/* read data before raising the clock */
		ret = (ret << 1)
		    | ((INB_DIO(dp, NETSIO) >> NSIO_MDATA_SHIFT) & 1);
I 6
	}
E 6

I 6
	/* revert the clock cycle and send idle bits */
	diodata |= NSIO_MDATA | NSIO_MTXEN;
	for (i = 0; i < 2; i++) {
		OUTB_DIO(dp, NETSIO, diodata);
		MDIO_DELAY(dp);
		OUTB_DIO(dp, NETSIO, diodata | NSIO_MCLK);
		MDIO_DELAY(dp);
E 6
E 2
	}

I 2
D 6
	/* revert clock cycle */
	OUTB_DIO(dp, NETSIO, diodata | NSIO_MCLK);
	MDIO_DELAY(dp);
	OUTB_DIO(dp, NETSIO, diodata);
	MDIO_DELAY(dp);
	OUTB_DIO(dp, NETSIO, diodata | NSIO_MCLK);
	MDIO_DELAY(dp);

E 6
E 2
D 13
	return ret;
E 13
I 13
D 14
	return (ret);
E 14
I 14
	return (ret & valid_mask);
E 14
E 13
}

I 14
static uint16_t
tne_mii_read(struct gem_dev *dp, uint_t reg)
{
	uint16_t	val;
	uint_t		phy;
	struct tne_dev	*lp = dp->private;

	if (DUAL_PHY(lp)) {
		if ((dp->mii_status & MII_STATUS_MFPRMBLSUPR) &&
		    lp->curr_phy == 31) {
			/* internal phy requires sync bits before each access */
			tne_mii_sync(dp);
		}
		phy = lp->curr_phy;
	} else {
		phy = dp->mii_phy_addr;
	}

	val = tne_mii_read_raw(dp, phy, reg);

	if (DUAL_PHY(lp) && reg == MII_STATUS && (val & MII_STATUS_REMFAULT)) {
		uint16_t	ctrl;

		DPRINTF(0, (CE_CONT,
		    "!%s: %s: switching phy at %d, status:%b",
		    dp->name, __func__,
		    lp->curr_phy, val, MII_ABILITY_BITS));

		/* switch phy */
		tne_mii_sync(dp);
		tne_mii_write_raw(dp, lp->curr_phy,
		    MII_CONTROL,
		    MII_CONTROL_ISOLATE);
		if (lp->curr_phy == dp->mii_phy_addr) {
			lp->curr_phy = 31;
		} else {
			lp->curr_phy = dp->mii_phy_addr;
		}

		/* internal phy requires sync bits before each access */
		tne_mii_sync(dp);

		/* initialize control register */
		tne_mii_write_raw(dp, lp->curr_phy, MII_CONTROL, 0);
		dp->mii_state = MII_STATE_UNKNOWN;
	}

	if (reg == MII_AN_ADVERT) {
		val |= 1;
	}
	return (val);
}

E 14
static void
D 11
tne_mii_write(struct gem_dev *dp, int reg, uint16_t val)
E 11
I 11
D 14
tne_mii_write(struct gem_dev *dp, uint_t reg, uint16_t val)
E 14
I 14
tne_mii_write_raw(struct gem_dev *dp, uint_t phy, uint_t reg, uint16_t val)
E 14
E 11
{
	uint32_t	cmd;
	int		i;
	uint8_t		data;
	uint8_t		diodata;

I 13
D 14
	DPRINTF(2, (CE_CONT,
		"!%s: time:%d %s: reg:%d, val: 0x%04x",
		dp->name, ddi_get_lbolt(), __func__, reg, val));
E 14
I 14
	DPRINTF(4, (CE_CONT,
	    "!%s: %s: time:%d %s: reg:%d, val: 0x%04x",
	    dp->name, __func__, ddi_get_lbolt(), __func__, reg, val));
E 14

E 13
D 6
	tne_mii_sync(dp);

E 6
D 14
	cmd = MII_WRITE_CMD(dp->mii_phy_addr, reg, val);
E 14
I 14
	cmd = MII_WRITE_CMD(phy, reg, val);
E 14

	OUTW(dp, DIO_ADR, NETSIO);
	diodata = INB_DIO(dp, NETSIO);
	diodata &= ~(NSIO_MINTEN | NSIO_MDATA | NSIO_MTXEN | NSIO_MCLK);
	diodata |= NSIO_MTXEN;

D 2
	OUTB_DIO(dp, NETSIO, diodata | NSIO_MDATA);
	MDIO_DELAY(dp);
	OUTB_DIO(dp, NETSIO, diodata | NSIO_MDATA | NSIO_MCLK);
	MDIO_DELAY(dp);

E 2
	for (i = 31; i >= 0; i--) {
I 2
		/* output new data */
E 2
		data = (((cmd >> i) & 1) << NSIO_MDATA_SHIFT) | diodata;
		OUTB_DIO(dp, NETSIO, data);
		MDIO_DELAY(dp);
I 2

		/* notify to the phy that data is stable */
E 2
		OUTB_DIO(dp, NETSIO, data | NSIO_MCLK);
		MDIO_DELAY(dp);
	}

I 2
	/*
D 6
	 * Disable output and send 2 clock cycle to ensure transmittion
E 6
I 6
	 * Send 2 idle clock cycle to ensure that the transmittion
E 6
	 * is terminated.
	 */
D 6
	diodata &= ~NSIO_MTXEN;
E 6
I 6
	diodata |= NSIO_MDATA | NSIO_MTXEN;
E 6
E 2
	for (i = 0; i < 2; i++) {
		OUTB_DIO(dp, NETSIO, diodata);
		MDIO_DELAY(dp);
		OUTB_DIO(dp, NETSIO, diodata | NSIO_MCLK);
		MDIO_DELAY(dp);
	}
D 2

	/* disable output */
	OUTB_DIO(dp, NETSIO, diodata & ~NSIO_MTXEN);
E 2
}
I 14

static void
tne_mii_write(struct gem_dev *dp, uint_t reg, uint16_t val)
{
	uint_t		phy;
	struct tne_dev	*lp = dp->private;

	DPRINTF(2, (CE_CONT,
	    "!%s: %s: time:%d %s: reg:%d, val: 0x%04x",
	    dp->name, __func__, ddi_get_lbolt(), __func__, reg, val));

	if (DUAL_PHY(lp)) {
		if ((dp->mii_status & MII_STATUS_MFPRMBLSUPR) &&
		    lp->curr_phy == 31) {
			/* internal phy requires sync bits for each access */
			tne_mii_sync(dp);
		}
		phy = lp->curr_phy;
	} else {
		phy = dp->mii_phy_addr;
	}

	tne_mii_write_raw(dp, phy, reg, val);
}

E 14
#undef MDIO_DELAY

I 7
static int
D 14
tne_mii_init(struct gem_dev *dp)
E 14
I 14
tne_mii_probe(struct gem_dev *dp)
E 14
{
D 14
	int		ret;
	struct tne_dev	*lp = (struct tne_dev *)dp->private;
E 14
I 14
	int	ret;
	struct tne_dev	*lp = dp->private;
E 14

D 14
	/* First, we try external PHY */
	/* Setup the NetConfig register for external phy */
E 14
I 14
	/* Setup the NetConfig register for external phy and internal phy */
	lp->is_dual_phy = B_FALSE;
E 14
	OUTW(dp, DIO_ADR, NETCFG);
D 14
	OUTW_DIO(dp, NETCFG, NCFG_PEF | NCFG_ONEchn);
	ret = gem_mii_init_default(dp);
E 14
I 14
	OUTW_DIO(dp, NETCFG, NCFG_PEF | NCFG_ONEchn | NCFG_PHY_En);

	/* First, we try external PHY */
	ret = gem_mii_probe_default(dp);
E 14
D 13
	if (ret >= 0) {
E 13
I 13
	if (ret == GEM_SUCCESS) {
E 13
D 14
		lp->which_phy = PHY_EXTERNAL_MII;
E 14
I 14
		DPRINTF(0, (CE_CONT, "!%s: %s: external phy selected",
		    dp->name, __func__));

		if (dp->mii_phy_id == 0 || dp->mii_phy_id == 0xffffffffU) {
			uint16_t	status;

			/* dual phy mode */
			lp->is_dual_phy = B_TRUE;
			lp->curr_phy = (uint_t)dp->mii_phy_addr;

			/* enable internal PHY */
			tne_mii_sync(dp);
			status = tne_mii_read_raw(dp, 31, MII_STATUS);
			DPRINTF(0, (CE_CONT,
			    "!%s: %s: reading internal phy: status:%b",
			    dp->name, __func__, status, MII_STATUS_BITS));
			tne_mii_sync(dp);
			tne_mii_write_raw(dp, 31,
			    MII_CONTROL,
			    MII_CONTROL_ISOLATE);
		} else {
			/* disable internal PHY */
			OUTW(dp, DIO_ADR, NETCFG);
			OUTW_DIO(dp, NETCFG, NCFG_PEF | NCFG_ONEchn);
		}
E 14
D 13
		return ret;
E 13
I 13
		return (ret);
E 13
	}

	/* Next, we try internal PHY */
D 14
	/* Setup the NetConfig register for the internal 10Mbps phy */
E 14
I 14
	/* Setup NetConfig register for the internal 10Mbps phy */
E 14
	dp->mii_phy_addr = 31;
D 14
	lp->which_phy = PHY_INTERNAL_MII;
E 14
	OUTW(dp, DIO_ADR, NETCFG);
	OUTW_DIO(dp, NETCFG, NCFG_PEF | NCFG_ONEchn | NCFG_PHY_En);
D 13
	return gem_mii_init_default(dp);
E 13
I 13
D 14
	return (gem_mii_init_default(dp));
E 14
I 14

	DPRINTF(0, (CE_CONT, "!%s: %s: internal phy selected",
	    dp->name, __func__));

	return (gem_mii_probe_default(dp));
E 14
E 13
}

I 14
static int
tne_mii_init(struct gem_dev *dp)
{
	struct tne_dev	*lp = dp->private;

	if (!DUAL_PHY(lp) && dp->mii_phy_addr != 31) {
		/* Setup NetConfig register only for external phy */
		OUTW(dp, DIO_ADR, NETCFG);
		OUTW_DIO(dp, NETCFG, NCFG_PEF | NCFG_ONEchn);
	} else {
		/* Setup NetConfig register for the internal 10Mbps phy */
		OUTW(dp, DIO_ADR, NETCFG);
		OUTW_DIO(dp, NETCFG, NCFG_PEF | NCFG_ONEchn | NCFG_PHY_En);
		if (DUAL_PHY(lp)) {
			/* isolate and power down unused phy */
			tne_mii_sync(dp);
			tne_mii_write_raw(dp,
			    lp->curr_phy != 31 ? 31 : dp->mii_phy_addr,
			    MII_CONTROL,
			    MII_CONTROL_ISOLATE);
		}
	}
	return (GEM_SUCCESS);
}

E 14
E 7
/* ======================================================== */
/*
 * OS depend (device driver) routine
 */
/* ======================================================== */
static int
tneattach(dev_info_t *dip, ddi_attach_cmd_t cmd)
{
	int			i;
I 8
	int			n;
E 8
	ddi_iblock_cookie_t	c;
	ddi_acc_handle_t	conf_handle;
D 13
	uint16_t		comm;
E 13
	int			ret;
	int			vid;
	int			did;
D 6
	int			svid;
	int			ssid;
E 6
	int			unit;
	struct chip_info	*p;
	int			val;
D 8
	int			len;
E 8
I 8
	uint_t			len;
E 8
	struct pci_phys_spec	*regs;
	const char		*drv_name;
	struct gem_dev		*dp;
	struct tne_dev		*lp;
	void			*base;
D 13
	ddi_acc_handle_t	regs_handle;
E 13
I 13
	ddi_acc_handle_t	regs_ha;
E 13
D 2
	struct gem_conf		gc;
E 2
I 2
	struct gem_conf		*gcp;
E 2
	uint8_t			revid;

D 13
	unit =  ddi_get_instance(dip);
E 13
I 13
	unit = ddi_get_instance(dip);
E 13
	drv_name = ddi_driver_name(dip);

D 14
	DPRINTF(3, (CE_CONT, "!%s%d: tneattach: called", drv_name, unit));
E 14
I 14
	DPRINTF(3, (CE_CONT, "!%s%d: %s: called", drv_name, unit, __func__));
E 14

D 13
	if (cmd == DDI_ATTACH) {
		/*
		 * Check if chip is supported.
		 */
		if (pci_config_setup(dip, &conf_handle) != DDI_SUCCESS) {
			cmn_err(CE_WARN, "%s: ddi_regs_map_setup failed",
				drv_name);
			goto err;
		}
		vid  = pci_config_get16(conf_handle, PCI_CONF_VENID);
		did  = pci_config_get16(conf_handle, PCI_CONF_DEVID);
D 6
		svid = pci_config_get16(conf_handle, PCI_CONF_SUBVENID);
		ssid = pci_config_get16(conf_handle, PCI_CONF_SUBSYSID);
E 6
		revid= pci_config_get8(conf_handle, PCI_CONF_REVID);
		comm = pci_config_get16(conf_handle, PCI_CONF_COMM);
		comm |= PCI_COMM_IO | PCI_COMM_ME;
		pci_config_put16(conf_handle, PCI_CONF_COMM, comm);
E 13
I 13
	/*
	 * Check if chip is supported.
	 */
	if (pci_config_setup(dip, &conf_handle) != DDI_SUCCESS) {
D 14
		cmn_err(CE_WARN, "%s: ddi_regs_map_setup failed",
			drv_name);
E 14
I 14
		cmn_err(CE_WARN, "%s%d: pci_config_setup failed",
		    drv_name, unit);
E 14
		goto err;
	}
E 13

D 13
		pci_config_put8(conf_handle, PCI_CONF_LATENCY_TIMER, 0x20);
E 13
I 13
D 14
	vid  = pci_config_get16(conf_handle, PCI_CONF_VENID);
	did  = pci_config_get16(conf_handle, PCI_CONF_DEVID);
	revid= pci_config_get8(conf_handle, PCI_CONF_REVID);
E 14
I 14
	vid = pci_config_get16(conf_handle, PCI_CONF_VENID);
	did = pci_config_get16(conf_handle, PCI_CONF_DEVID);
	revid = pci_config_get8(conf_handle, PCI_CONF_REVID);
E 14
E 13

D 13
		pci_config_teardown(&conf_handle);
E 13
I 13
D 14
	pci_config_put16(conf_handle, PCI_CONF_COMM, 
		PCI_COMM_IO | PCI_COMM_ME | PCI_COMM_MAE |
			pci_config_get16(conf_handle, PCI_CONF_COMM));
E 14
I 14
	pci_config_put16(conf_handle, PCI_CONF_COMM,
	    PCI_COMM_IO | PCI_COMM_ME | PCI_COMM_MAE |
	    pci_config_get16(conf_handle, PCI_CONF_COMM));
E 14
E 13

I 13
	pci_config_put8(conf_handle, PCI_CONF_LATENCY_TIMER, 0x20);

	/* ensure the pmr status is D0 mode */
	(void) gem_pci_set_power_state(dip, conf_handle, PCI_PMCSR_D0);

	pci_config_teardown(&conf_handle);

	switch (cmd) {
	case DDI_RESUME:
		return (gem_resume(dip));

	case DDI_ATTACH:
E 13
		for (i = 0, p = tne_chiptbl; i < CHIPTABLESIZE; i++, p++) {
D 6
			if ((p->venid == vid && p->devid == did) ||
			    (p->venid == svid && p->devid == ssid)) {
E 6
I 6
			if (p->venid == vid && p->devid == did) {
E 6
				/* found */
				cmn_err(CE_CONT,
			"!%s%d: %s (vid: 0x%04x, did: 0x%04x, revid: 0x%02x)",
D 14
				drv_name, unit, p->name, vid, did, revid);
E 14
I 14
				    drv_name, unit, p->name, vid, did, revid);
E 14
				goto chip_found;
			}
		}

		/* Not found */
		cmn_err(CE_WARN,
D 14
			"%s: tne_attach: wrong PCI venid/devid (0x%x, 0x%x)",
			drv_name, vid, did);
E 14
I 14
		    "!%s%d: %s: wrong PCI venid/devid (0x%x, 0x%x)",
		    drv_name, unit, __func__, vid, did);
E 14
		goto err;
chip_found:
D 13
		/*
		 * Map in the device registers.
		 */

		/* Search IO-range or memory-range to be mapped */
		regs = NULL;
		len  = 0;
D 8
		if (ddi_getlongprop(DDI_DEV_T_ANY, dip, DDI_PROP_DONTPASS,
			"reg", (caddr_t)&regs, &len) != DDI_PROP_SUCCESS) {
E 8
I 8
		if (ddi_prop_lookup_int_array(
			DDI_DEV_T_ANY, dip, DDI_PROP_DONTPASS,
			"reg", (int **)&regs, &len) != DDI_PROP_SUCCESS) {

E 8
			cmn_err(CE_WARN,
D 8
				"%s: failed to get reg property", drv_name);
E 8
I 8
			"%s%d: failed to get reg property", drv_name, unit);
E 8
			goto err;
		}
I 8
		n = len / (sizeof(struct pci_phys_spec) / sizeof(int));
E 8

		ASSERT(regs != NULL && len > 0);
#if DEBUG_LEVEL > 0
D 8
		for (i = 0; i <len / sizeof(struct pci_phys_spec); i++) {
E 8
I 8
		for (i = 0; i < n; i++) {
E 8
			cmn_err(CE_CONT,
				"!%s%d: regs[%d]: %08x.%08x.%08x.%08x.%08x",
				drv_name, unit, i,
				regs[i].pci_phys_hi,
				regs[i].pci_phys_mid,
				regs[i].pci_phys_low,
				regs[i].pci_size_hi,
				regs[i].pci_size_low);
		}
#endif
D 8
		for (i = 0; i <len / sizeof(struct pci_phys_spec); i++) {
E 8
I 8
		for (i = 0; i < n; i++) {
E 8
			if ((regs[i].pci_phys_hi & PCI_REG_ADDR_M) == 
E 13
I 13
		if (gem_pci_regs_map_setup(dip,
E 13
D 2
			    PCI_ADDR_IO) {
				/* it's I/O space */
E 2
I 2
#ifdef MAP_MEM
D 13
				PCI_ADDR_MEM32
E 13
I 13
D 14
			PCI_ADDR_MEM32, PCI_ADDR_MASK,
E 14
I 14
		    PCI_ADDR_MEM32, PCI_ADDR_MASK,
E 14
E 13
#else
D 13
				PCI_ADDR_IO
E 13
I 13
D 14
			PCI_ADDR_IO, PCI_ADDR_MASK,
E 14
I 14
		    PCI_ADDR_IO, PCI_ADDR_MASK,
E 14
E 13
#endif
D 13
			) {
E 2
D 8
				kmem_free(regs, len);
E 8
I 8
				ddi_prop_free(regs);
E 8
D 2
				goto io_range_found;
E 2
I 2
				goto map_space_found;
E 2
			}
		}
D 2
		cmn_err(CE_WARN, "%s: failed to find IO space", drv_name);
E 2
I 2
		cmn_err(CE_WARN,
#ifdef MAP_MEM
			"%s%d: failed to find MEM32 space",
#else
			"%s%d: failed to find IO space",
#endif
			drv_name, unit);
E 2
D 8
		kmem_free(regs, len);
E 8
I 8
		ddi_prop_free(regs);
E 8
		goto err;
D 2
io_range_found:
E 2

I 2
map_space_found:
E 2
		if (ddi_regs_map_setup(dip, i, (caddr_t *)&base,
			0, 0, &tne_dev_attr, &regs_handle)) {
			cmn_err(CE_WARN, "%s: ddi_regs_map_setup failed",
				drv_name);
E 13
I 13
D 14
			&tne_dev_attr, (caddr_t *)&base, &regs_ha)
					!= DDI_SUCCESS) {
E 14
I 14
		    &tne_dev_attr, (void *)&base, &regs_ha)
		    != DDI_SUCCESS) {
E 14
E 13
			goto err;
		}
I 13

E 13
		/*
I 13
D 14
		/*
E 14
E 13
		 * construct gem configration
		 */
D 2
		bzero(&gc, sizeof(gc));
E 2
I 2
D 14
		gcp = (struct gem_conf *) kmem_zalloc(sizeof(*gcp), KM_SLEEP);
E 14
I 14
		gcp = kmem_zalloc(sizeof (*gcp), KM_SLEEP);
E 14
E 2

		/* name */
D 2
		sprintf(gc.gc_name, "%s%d", drv_name, unit);
E 2
I 2
		sprintf(gcp->gc_name, "%s%d", drv_name, unit);
E 2

		/* consistency on tx and rx */
D 2
		gc.gc_tx_buf_align = 0;
		gc.gc_tx_max_frags = GEM_MAXTXFRAGS;
		gc.gc_tx_desc_size = sizeof(struct tx_list) * TX_RING_SIZE;
		gc.gc_tx_ring_size = TX_RING_SIZE;
		gc.gc_tx_buf_size  = TX_RING_SIZE;
		gc.gc_tx_max_descs_per_pkt = 1;
		gc.gc_tx_auto_pad  = FALSE;
		gc.gc_tx_copy_thresh = tne_tx_copy_thresh;
E 2
I 2
D 13
		gcp->gc_tx_buf_align = 0;
		gcp->gc_tx_max_frags = GEM_MAXTXFRAGS;
		gcp->gc_tx_desc_size = sizeof(struct tx_list) * TX_RING_SIZE;
		gcp->gc_tx_ring_size = TX_RING_SIZE;
		gcp->gc_tx_buf_size  = TX_BUF_SIZE;
E 13
I 13
D 14
		gcp->gc_tx_buf_align = sizeof(uint8_t) - 1;
E 14
I 14
		gcp->gc_tx_buf_align = sizeof (uint8_t) - 1;
E 14
D 15
		gcp->gc_tx_max_frags = TNE_MAXTXFRAGS;
E 15
I 15
		gcp->gc_tx_max_frags = min(GEM_MAXTXFRAGS, TNE_MAXTXFRAGS);
E 15
E 13
		gcp->gc_tx_max_descs_per_pkt = 1;
D 13
		gcp->gc_tx_auto_pad  = FALSE;
E 13
I 13
		gcp->gc_tx_desc_unit_shift = 6;	/* 64 byte */
D 14
		gcp->gc_tx_buf_size  = TX_BUF_SIZE;
		gcp->gc_tx_buf_limit  = gcp->gc_tx_buf_size - 1;
E 14
I 14
		gcp->gc_tx_buf_size = TX_BUF_SIZE;
D 15
		gcp->gc_tx_buf_limit = gcp->gc_tx_buf_size - 1;
E 15
I 15
		gcp->gc_tx_buf_limit = gcp->gc_tx_buf_size;
E 15
E 14
		gcp->gc_tx_ring_size = TX_RING_SIZE;
		gcp->gc_tx_ring_limit = gcp->gc_tx_ring_size - 1;
D 15
		gcp->gc_tx_ring_limit = gcp->gc_tx_ring_size;
E 15
D 14
		gcp->gc_tx_auto_pad  = B_FALSE;
E 14
I 14
		gcp->gc_tx_auto_pad = B_FALSE;
E 14
E 13
		gcp->gc_tx_copy_thresh = tne_tx_copy_thresh;
I 13
D 14
		gcp->gc_tx_desc_write_oo = B_FALSE;
		gcp->gc_tx_desc_write_oo = B_TRUE;
E 14
E 13
E 2

D 2
		gc.gc_rx_buf_align = 0;
		gc.gc_rx_max_frags = GEM_MAXRXFRAGS;
		gc.gc_rx_desc_size = sizeof(struct rx_list) * RX_RING_SIZE;
		gc.gc_rx_ring_size = RX_RING_SIZE;
		gc.gc_rx_buf_size  = RX_RING_SIZE;
		gc.gc_rx_max_descs_per_pkt = 1;
		gc.gc_rx_copy_thresh = tne_rx_copy_thresh;
		gc.gc_rx_buf_max  = 10*RX_RING_SIZE;
E 2
I 2
D 13
		gcp->gc_rx_buf_align = 0;
E 13
I 13
D 14
		gcp->gc_rx_buf_align = sizeof(uint8_t) - 1;
E 14
I 14
		gcp->gc_rx_buf_align = sizeof (uint8_t) - 1;
E 14
E 13
#ifdef RXSINGLE
		gcp->gc_rx_max_frags = 1;
#else
D 13
		gcp->gc_rx_max_frags = GEM_MAXRXFRAGS;
E 13
I 13
D 15
		gcp->gc_rx_max_frags = TNE_MAXRXFRAGS;
E 15
I 15
		gcp->gc_rx_max_frags = min(GEM_MAXRXFRAGS, TNE_MAXRXFRAGS - 1);
E 15
E 13
#endif
D 13
		gcp->gc_rx_desc_size = sizeof(struct rx_list) * RX_RING_SIZE;
E 13
I 13
		gcp->gc_rx_desc_unit_shift = 6;	/* 64 byte */
E 13
D 14
		gcp->gc_rx_ring_size = RX_RING_SIZE;
D 13
		gcp->gc_rx_buf_size  = RX_BUF_SIZE;
E 13
I 13
		gcp->gc_rx_buf_max  = RX_BUF_SIZE - 1;
E 14
I 14
		gcp->gc_rx_ring_size = RX_BUF_SIZE;
		gcp->gc_rx_buf_max = RX_BUF_SIZE - 1;
E 14
E 13
		gcp->gc_rx_copy_thresh = tne_rx_copy_thresh;
D 8
		if (gcp->gc_rx_max_frags > 1) {
			gcp->gc_rx_buf_max  = gcp->gc_rx_buf_size + 1;
		} else {
			gcp->gc_rx_buf_max  = gcp->gc_rx_buf_size;
		}
E 8
I 8
D 13
		gcp->gc_rx_buf_max  = gcp->gc_rx_buf_size + 1;
E 13
E 8
E 2

I 13
		gcp->gc_io_area_size = 0;

E 13
D 2
		/* map attributes */
		gc.gc_dev_attr  = tne_dev_attr;
		gc.gc_buf_attr  = tne_buf_attr;
		gc.gc_desc_attr = tne_dev_attr;
E 2
I 2
		/* map attributes (endianness) */
D 8
		gcp->gc_dev_attr  = tne_dev_attr;
		gcp->gc_buf_attr  = tne_buf_attr;
		gcp->gc_desc_attr = tne_dev_attr;
E 8
I 8
D 13
		STRUCT_COPY(gcp->gc_dev_attr, tne_dev_attr);
		STRUCT_COPY(gcp->gc_buf_attr, tne_buf_attr);
		STRUCT_COPY(gcp->gc_desc_attr, tne_dev_attr);
E 13
I 13
		gcp->gc_dev_attr = tne_dev_attr;
		gcp->gc_buf_attr = tne_buf_attr;
		gcp->gc_desc_attr = tne_buf_attr;
E 13
E 8
E 2

D 2
		/* dma attributes */
		gc.gc_dma_attr_desc  = tne_dma_attr_nosc;
		gc.gc_dma_attr_txbuf = tne_dma_attr_txbuf;
		if (gc.gc_rx_max_frags > 1) {
			gc.gc_dma_attr_rxbuf = tne_dma_attr_rxbuf;
E 2
I 2
		/* dma attributes (boundary) */
D 8
		gcp->gc_dma_attr_desc  = tne_dma_attr_nosc;
		gcp->gc_dma_attr_txbuf = tne_dma_attr_txbuf;
		if (gcp->gc_rx_max_frags > 1) {
			gcp->gc_dma_attr_rxbuf = tne_dma_attr_rxbuf;
E 2
		} else {
D 2
			ASSERT(gc.gc_rx_max_frags == 1);
			gc.gc_dma_attr_rxbuf = tne_dma_attr_nosc;
E 2
I 2
			ASSERT(gcp->gc_rx_max_frags == 1);
			gcp->gc_dma_attr_rxbuf = tne_dma_attr_nosc;
E 2
		}
E 8
I 8
D 13
		STRUCT_COPY(gcp->gc_dma_attr_desc, tne_dma_attr_desc);
E 13
I 13
		gcp->gc_dma_attr_desc = tne_dma_attr_desc;
E 13
D 9
		STRUCT_COPY(gcp->gc_dma_attr_txbuf, tne_dma_attr_txbuf);
		STRUCT_COPY(gcp->gc_dma_attr_rxbuf, tne_dma_attr_rxbuf);
E 9
E 8

I 9
D 13
		STRUCT_COPY(gcp->gc_dma_attr_txbuf, tne_dma_attr_buf);
E 13
I 13
		gcp->gc_dma_attr_txbuf = tne_dma_attr_buf;
E 13
		gcp->gc_dma_attr_txbuf.dma_attr_sgllen = gcp->gc_tx_max_frags;

D 13
		STRUCT_COPY(gcp->gc_dma_attr_rxbuf, tne_dma_attr_buf);
E 13
I 13
		gcp->gc_dma_attr_rxbuf = tne_dma_attr_buf;
E 13
		gcp->gc_dma_attr_rxbuf.dma_attr_sgllen = gcp->gc_rx_max_frags;

E 9
		/* time out parameters */
D 2
		gc.gc_tx_timeout = 2*ONESEC;
		gc.gc_tx_timeout_interval = ONESEC;
E 2
I 2
D 9
		gcp->gc_tx_timeout = 2*ONESEC;
E 9
I 9
D 14
		gcp->gc_tx_timeout = 5*ONESEC;
E 14
I 14
		gcp->gc_tx_timeout = 3*ONESEC;
E 14
E 9
		gcp->gc_tx_timeout_interval = ONESEC;
E 2

		/* flow control */
D 2
		gc.gc_flow_control = FALSE;
E 2
I 2
D 8
		gcp->gc_flow_control = FALSE;
E 8
I 8
		gcp->gc_flow_control = FLOW_CONTROL_NONE;
E 8
E 2

		/* MII timeout parameters */
D 2
		gc.gc_mii_link_watch_interval = ONESEC;
		gc.gc_mii_an_watch_interval   = ONESEC/5;
		gc.gc_mii_reset_timeout = MII_RESET_TIMEOUT;	/* 1 sec */
		gc.gc_mii_an_timeout = MII_AN_TIMEOUT;	/* 5 sec */
		gc.gc_mii_an_wait = 0;	/* 0 for default, 3 for via rhine */
		gc.gc_mii_linkdown_timeout = MII_LINKDOWN_TIMEOUT;
E 2
I 2
		gcp->gc_mii_link_watch_interval = ONESEC;
D 14
		gcp->gc_mii_an_watch_interval   = ONESEC/5;
E 14
I 14
		gcp->gc_mii_an_watch_interval = ONESEC/5;
E 14
		gcp->gc_mii_reset_timeout = MII_RESET_TIMEOUT;	/* 1 sec */
		gcp->gc_mii_an_timeout = MII_AN_TIMEOUT;	/* 5 sec */
		gcp->gc_mii_an_wait = 0;
		gcp->gc_mii_linkdown_timeout = MII_LINKDOWN_TIMEOUT;
E 2

		/* MII work arounds */
D 2
		gc.gc_mii_addr_min = 0;
		gc.gc_mii_an_delay = 0;
		gc.gc_mii_linkdown_action = MII_ACTION_RSA;
		gc.gc_mii_dont_reset = FALSE;
E 2
I 2
		gcp->gc_mii_addr_min = 0;
		gcp->gc_mii_an_delay = 0;
D 11
		gcp->gc_mii_linkdown_action = MII_ACTION_RSA;
E 11
I 11
D 14
		gcp->gc_mii_linkdown_action = MII_ACTION_NONE;
		gcp->gc_mii_linkdown_timeout_action = MII_ACTION_RSA;
E 14
I 14
		gcp->gc_mii_linkdown_action = MII_ACTION_RESET;
		gcp->gc_mii_linkdown_timeout_action = MII_ACTION_RESET;
E 14
E 11
D 13
		gcp->gc_mii_dont_reset = FALSE;
E 13
I 13
		gcp->gc_mii_dont_reset = B_FALSE;
E 13
E 2

		/* I/O methods */

		/* mac operation */
D 2
		gc.gc_attach_chip = &tne_attach_chip;
		gc.gc_reset_chip  = &tne_reset_chip;
		gc.gc_init_chip   = &tne_init_chip;
		gc.gc_start_chip  = &tne_start_chip;
		gc.gc_stop_chip   = &tne_stop_chip;
#ifdef USE_MULTICAST_HASHTBL
		gc.gc_multicast_hash = &tne_mcast_hash;
#endif
		gc.gc_set_rx_filter = &tne_set_rx_filter;
		gc.gc_set_media   = &tne_set_media;
		gc.gc_get_stats   = &tne_get_stats;
		gc.gc_interrupt   = &tne_interrupt;
E 2
I 2
		gcp->gc_attach_chip = &tne_attach_chip;
D 14
		gcp->gc_reset_chip  = &tne_reset_chip;
		gcp->gc_init_chip   = &tne_init_chip;
		gcp->gc_start_chip  = &tne_start_chip;
		gcp->gc_stop_chip   = &tne_stop_chip;
E 14
I 14
		gcp->gc_reset_chip = &tne_reset_chip;
		gcp->gc_init_chip = &tne_init_chip;
		gcp->gc_start_chip = &tne_start_chip;
		gcp->gc_stop_chip = &tne_stop_chip;
E 14
		gcp->gc_multicast_hash = &tne_mcast_hash;
		gcp->gc_set_rx_filter = &tne_set_rx_filter;
D 14
		gcp->gc_set_media   = &tne_set_media;
		gcp->gc_get_stats   = &tne_get_stats;
		gcp->gc_interrupt   = &tne_interrupt;
E 14
I 14
		gcp->gc_set_media = &tne_set_media;
		gcp->gc_get_stats = &tne_get_stats;
		gcp->gc_interrupt = &tne_interrupt;
E 14
E 2

		/* descriptor operation */
D 2
		gc.gc_tx_desc_write = &tne_tx_desc_write;
		gc.gc_rx_desc_write = &tne_rx_desc_write;
E 2
I 2
		gcp->gc_tx_desc_write = &tne_tx_desc_write;
I 13
D 14
		gcp->gc_tx_start      = &tne_tx_start;
E 14
I 14
		gcp->gc_tx_start = &tne_tx_start;
E 14
E 13
		gcp->gc_rx_desc_write = &tne_rx_desc_write;
I 13
D 14
		gcp->gc_rx_start      = &tne_rx_start;
E 14
I 14
		gcp->gc_rx_start = &tne_rx_start;
E 14
E 13
E 2

D 2
		gc.gc_tx_desc_init = &tne_tx_desc_init;
		gc.gc_rx_desc_init = &tne_rx_desc_init;
		gc.gc_tx_desc_stat = &tne_tx_desc_stat;
		gc.gc_rx_desc_stat = &tne_rx_desc_stat;
		gc.gc_tx_desc_clean = &tne_tx_desc_init;
		gc.gc_rx_desc_clean = &tne_rx_desc_init;
E 2
I 2
		gcp->gc_tx_desc_init = &tne_tx_desc_init;
		gcp->gc_rx_desc_init = &tne_rx_desc_init;
		gcp->gc_tx_desc_stat = &tne_tx_desc_stat;
		gcp->gc_rx_desc_stat = &tne_rx_desc_stat;
		gcp->gc_tx_desc_clean = &tne_tx_desc_init;
		gcp->gc_rx_desc_clean = &tne_rx_desc_init;
E 2

		/* mii operations */
D 2
		gc.gc_mii_init  = &gem_mii_init_default;
		gc.gc_mii_config = &gem_mii_config_default;
		gc.gc_mii_sync  = &tne_mii_sync;
		gc.gc_mii_read  = &tne_mii_read;
		gc.gc_mii_write = &tne_mii_write;
		gc.gc_mii_tune_phy = NULL;
E 2
I 2
D 14
		gcp->gc_mii_init  = &gem_mii_init_default;
E 14
I 14
		gcp->gc_mii_probe = &tne_mii_probe;
		gcp->gc_mii_init = NULL;
E 14
		gcp->gc_mii_config = &gem_mii_config_default;
D 14
		gcp->gc_mii_sync  = &tne_mii_sync;
		gcp->gc_mii_read  = &tne_mii_read;
E 14
I 14
		gcp->gc_mii_sync = &tne_mii_sync;
		gcp->gc_mii_read = &tne_mii_read;
E 14
		gcp->gc_mii_write = &tne_mii_write;
		gcp->gc_mii_tune_phy = NULL;
E 2
D 15

E 15
I 15
#ifdef GEM_CONFIG_JUMBO_FRAME
		gcp->gc_max_mtu = (gcp->gc_rx_max_frags - 1) * 4096 -
		    sizeof(struct ether_header) - 4;
		gcp->gc_default_mtu = ETHERMTU;
		gcp->gc_min_mtu = ETHERMIN;
#endif
E 15
D 14
		lp = kmem_zalloc(sizeof(struct tne_dev), KM_SLEEP);
I 13
		lp->chip   = p;
E 14
I 14
		lp = kmem_zalloc(sizeof (struct tne_dev), KM_SLEEP);
		lp->chip = p;
E 14
E 13
		lp->rev_id = revid;
D 2
		dp = gem_do_attach(dip, &gc, base, &regs_handle,
E 2
I 2
D 13
		dp = gem_do_attach(dip, gcp, base, &regs_handle,
E 13
I 13
D 14
		dp = gem_do_attach(dip, gcp, base, &regs_ha,
E 13
E 2
					lp, sizeof(*lp));
E 14
I 14
		dp = gem_do_attach(dip, 0,
		    gcp, base, &regs_ha, lp, sizeof (*lp));
E 14

I 2
D 14
		kmem_free(gcp, sizeof(*gcp));
E 14
I 14
		kmem_free(gcp, sizeof (*gcp));
E 14

E 2
		if (dp != NULL) {
D 13
			return DDI_SUCCESS;
E 13
I 13
			return (DDI_SUCCESS);
E 13
		}
err_free_mem:
D 14
		kmem_free(lp, sizeof(struct tne_dev));
E 14
I 14
		kmem_free(lp, sizeof (struct tne_dev));
E 14
err:
D 13
		return DDI_FAILURE;
E 13
I 13
		return (DDI_FAILURE);
E 13
	}
D 13
	return DDI_FAILURE;
E 13
I 13
	return (DDI_FAILURE);
E 13
}

static int
tnedetach(dev_info_t *dip, ddi_detach_cmd_t cmd)
{
	int	ret;

D 13
	if (cmd == DDI_DETACH) {
		ret = gem_do_detach(dip);
		if (ret != DDI_SUCCESS) {
			return DDI_FAILURE;
		}
		return DDI_SUCCESS;
E 13
I 13
	switch (cmd) {
	case DDI_SUSPEND:
		return (gem_suspend(dip));

	case DDI_DETACH:
		return (gem_do_detach(dip));
E 13
	}
D 13
	return DDI_FAILURE;
E 13
I 13
	return (DDI_FAILURE);
E 13
}

/* ======================================================== */
/*
 * OS depend (loadable streams driver) routine
 */
/* ======================================================== */
I 14
#ifdef GEM_CONFIG_GLDv3
GEM_STREAM_OPS(tne_ops, tneattach, tnedetach);
#else
E 14
I 7
D 8
#define	TNE_MAX_MTU	(64*1024 - 14)
E 8
E 7
static	struct module_info tneminfo = {
	0,			/* mi_idnum */
D 2
	"tne",		/* mi_idname */
E 2
I 2
	"tne",			/* mi_idname */
E 2
	0,			/* mi_minpsz */
D 2
	ETHERMTU,		/* mi_maxpsz */
E 2
I 2
D 7
	64*1024 - 14,		/* mi_maxpsz */
E 7
I 7
D 13
	TNE_MAX_MTU,		/* mi_maxpsz */
E 7
E 2
D 8
	32*1024,		/* mi_hiwat */
E 8
I 8
	TX_BUF_SIZE*ETHERMAX,	/* mi_hiwat */
E 13
I 13
	INFPSZ,			/* mi_maxpsz */
	64*1024,		/* mi_hiwat */
E 13
E 8
	1,			/* mi_lowat */
};

static	struct qinit tnerinit = {
	(int (*)()) NULL,	/* qi_putp */
	gem_rsrv,		/* qi_srvp */
	gem_open,		/* qi_qopen */
	gem_close,		/* qi_qclose */
	(int (*)()) NULL,	/* qi_qadmin */
	&tneminfo,		/* qi_minfo */
	NULL,			/* qi_mstat */
};

static	struct qinit tnewinit = {
	gem_wput,		/* qi_putp */
	gem_wsrv,		/* qi_srvp */
	(int (*)()) NULL,	/* qi_qopen */
	(int (*)()) NULL,	/* qi_qclose */
	(int (*)()) NULL,	/* qi_qadmin */
	&tneminfo,		/* qi_minfo */
	NULL,			/* qi_mstat */
};

static struct streamtab	tne_info = {
	&tnerinit,	/* st_rdinit */
	&tnewinit,	/* st_wrinit */
	NULL,		/* st_muxrinit */
	NULL,		/* st_muxwrinit */
};

static	struct cb_ops cb_tne_ops = {
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
	&tne_info,	/* cb_stream */
	D_NEW|D_MP,	/* cb_flag */
};

static	struct dev_ops tne_ops = {
	DEVO_REV,	/* devo_rev */
	0,		/* devo_refcnt */
	gem_getinfo,	/* devo_getinfo */
	nulldev,	/* devo_identify */
	nulldev,	/* devo_probe */
	tneattach,	/* devo_attach */
	tnedetach,	/* devo_detach */
	nodev,		/* devo_reset */
	&cb_tne_ops,	/* devo_cb_ops */
	NULL,		/* devo_bus_ops */
	ddi_power,	/* devo_power */
};
D 14

E 14
I 14
#endif
E 14
static struct modldrv modldrv = {
	&mod_driverops,	/* Type of module.  This one is a driver */
	ident,
	&tne_ops,	/* driver ops */
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

	DPRINTF(2, (CE_CONT, "!tne: _init: called"));
I 13
	gem_mod_init(&tne_ops, "tne");
E 13
	status = mod_install(&modlinkage);
I 13
	if (status != DDI_SUCCESS) {
		gem_mod_fini(&tne_ops);
	}
E 13

	return (status);
}

/*
 * _fini : done
 */
int
_fini(void)
{
	int	status;

	DPRINTF(2, (CE_CONT, "!tne: _fini: called"));
	status = mod_remove(&modlinkage);
I 13
	if (status == DDI_SUCCESS) {
		gem_mod_fini(&tne_ops);
	}
E 13
	return (status);
}

int
_info(struct modinfo *modinfop)
{
	return (mod_info(&modlinkage, modinfop));
}
E 1
