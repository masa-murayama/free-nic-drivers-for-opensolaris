h22174
s 00071/00036/01594
d D 1.22 11/09/04 08:46:33 mrym 22 21
c 2.6.4
e
s 00047/00035/01583
d D 1.21 08/11/09 12:45:15 mrym 21 20
c 2.6.1
e
s 00001/00001/01617
d D 1.20 08/02/03 11:37:16 mrym 20 19
c incorrect arg type
e
s 00341/00371/01277
d D 1.19 08/02/03 11:36:29 mrym 19 18
c 2.6.0
e
s 00036/00022/01612
d D 1.18 07/04/01 22:07:49 mrym 18 17
c IP100 support
e
s 00276/00333/01358
d D 1.17 06/12/31 16:45:46 mrym 17 16
c 2.4.0
e
s 00063/00104/01628
d D 1.16 05/08/31 00:16:06 mrym 16 15
c 1.0.10
e
s 00167/00070/01565
d D 1.15 05/05/09 22:57:34 mrym 15 14
c 0.8.9
e
s 00044/00038/01591
d D 1.14 05/05/01 05:39:13 mrym 14 13
c 1.0.8
e
s 00005/00001/01624
d D 1.13 05/01/13 00:11:38 mrym 13 12
c flow control fixed
e
s 00002/00002/01623
d D 1.12 05/01/12 01:19:36 mrym 12 11
c flow control fixed
e
s 00098/00122/01527
d D 1.11 04/12/30 13:39:36 mrym 11 10
c txthr changed
e
s 00009/00007/01640
d D 1.10 04/12/06 15:12:49 mrym 10 9
c structual copy removed for gcc3.x
e
s 00023/00002/01624
d D 1.9 04/11/28 20:54:35 mrym 9 8
c ddi_getlongprop removed
e
s 00069/00056/01557
d D 1.8 04/11/28 20:25:09 mrym 8 7
c cleanup
e
s 00002/00002/01611
d D 1.7 04/11/02 22:12:28 mrym 7 6
c alta_get_stats fixed
e
s 00030/00007/01583
d D 1.6 04/04/11 13:22:25 mrym 6 5
c license changed
e
s 00172/00162/01418
d D 1.5 04/02/29 13:35:30 mrym 5 4
c 1.0.2
e
s 00052/00042/01528
d D 1.4 03/10/19 17:53:21 mrym 4 3
c 1.0.0
e
s 00175/00034/01395
d D 1.3 03/04/20 21:11:37 mrym 3 2
c release 0.9.4 (for DL10050B)
e
s 00009/00002/01420
d D 1.2 03/02/10 20:31:41 mrym 2 1
c 0.9.1 release
e
s 01422/00000/00000
d D 1.1 03/02/09 21:01:13 mrym 1 0
c date and time created 03/02/09 21:01:13 by mrym
e
u
U
f e 0
t
T
I 1
/*
D 6
 *  alta: Sundance Technology ST201 Fast Ethernet MAC driver
E 6
I 6
 *  alta: Sundance Technology ST201 Fast Ethernet MAC driver for Solaris
E 6
 *  %W% %E%
 *
D 5
 *  Copyright (C) 2002,2003  Masayuki Murayama (KHF04453@nifty.ne.jp)
E 5
I 5
D 6
 *  Copyright (C) 2002-2004  Masayuki Murayama (KHF04453@nifty.ne.jp)
E 5
 *
 *  CAUTION: NO WARRANTY
 *  This software may be used and distributed according to the terms
 *  of the Lesser GNU Public License, incorporated herein by reference.
E 6
I 6
D 16
 * Copyright (c) 2002-2004 Masayuki Murayama.  All rights reserved.
E 16
I 16
D 17
 * Copyright (c) 2002-2005 Masayuki Murayama.  All rights reserved.
E 17
I 17
D 18
 * Copyright (c) 2002-2006 Masayuki Murayama.  All rights reserved.
E 18
I 18
D 19
 * Copyright (c) 2002-2007 Masayuki Murayama.  All rights reserved.
E 18
E 17
E 16
 * 
E 19
I 19
D 22
 * Copyright (c) 2002-2008 Masayuki Murayama.  All rights reserved.
E 22
I 22
 * Copyright (c) 2002-2011 Masayuki Murayama.  All rights reserved.
E 22
 *
E 19
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
D 19
 * 
E 19
I 19
 *
E 19
 * 1. Redistributions of source code must retain the above copyright notice,
D 19
 *    this list of conditions and the following disclaimer. 
 * 
E 19
I 19
 *    this list of conditions and the following disclaimer.
 *
E 19
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
D 19
 *    and/or other materials provided with the distribution. 
 * 
E 19
I 19
 *    and/or other materials provided with the distribution.
 *
E 19
 * 3. Neither the name of the author nor the names of its contributors may be
 *    used to endorse or promote products derived from this software without
D 19
 *    specific prior written permission. 
 * 
E 19
I 19
 *    specific prior written permission.
 *
E 19
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
D 6

E 6
D 19
/*
 Change log
E 19

D 19
02/09/2003  0.9.0 release. tested under s9 and s8 
I 2
02/10/2003  alta_get_stats fixed. count no carrier and late collision
		into totai xmit error.
02/10/2003  0.9.1 release.
E 2
D 3

E 3
I 3
03/13/2003  fixed for sparc
04/10/2003  ddi_dma_sync added when accessing tx/rx descriptors
04/11/2003  alta_mii_init added to scan from location 1 instead of 0
04/20/2003  0.9.4 release (updated for DL10050B)
I 4
10/19/2003  alta_mii_init removed, get_packet removed
	    gld entries removed.
            1.0.0 release
I 5
03/01/2004  1.0.2 release
I 6
04/11/2004  1.0.3 release; license changed
I 11
12/06/2004  tx list was potentially corrupted. Number of tx bufs must be
	    smaller tban number of tx descriptors. fixed.
I 17
03/25/2006  version 2.0.0 worked
12/31/2006  version 2.4.0 worked
I 18
03/25/2007  IP100A supported (thank to Pedro Alejandro Lopez Valencia)
E 18
E 17
E 11
E 6
E 5
E 4
E 3
 */
E 19
I 19
#pragma	ident	"%Z%%M% %I%     %E%"
E 19

/*
D 19
 TODO:
D 17
	separete allocation descriptors and bufferes
	txbuf allocation in attach
	fix rx_desc_write/tx_desc_write interface
I 3
	clear txlistloaded on reset
E 17
E 3
 */

/*
E 19
 * System Header files.
 */
#include <sys/types.h>
#include <sys/conf.h>
#include <sys/debug.h>
D 19
#include <sys/stropts.h>
#include <sys/stream.h>
#include <sys/strlog.h>
E 19
#include <sys/kmem.h>
D 19
#include <sys/stat.h>
#include <sys/kstat.h>
#include <sys/vtrace.h>
#include <sys/dlpi.h>
#include <sys/strsun.h>
#include <sys/ethernet.h>
E 19
#include <sys/modctl.h>
#include <sys/errno.h>
I 17
D 19
#include <sys/dditypes.h>
E 19
E 17
#include <sys/ddi.h>
#include <sys/sunddi.h>
D 4
#include <sys/gld.h>
E 4
D 17
#include <sys/ddi_impldefs.h>
E 17
I 17
#include <sys/byteorder.h>
E 17
D 19

E 19
I 19
#include <sys/ethernet.h>
E 19
#include <sys/pci.h>
D 19
#include "mii.h"
E 19
I 19

#include "gem_mii.h"
E 19
#include "gem.h"
#include "st201reg.h"

I 3
D 17
#ifdef sun4u
# define	IOCACHE
# define	IOMMU
#endif

E 17
E 3
D 4
char	ident[] = "alta_gem driver v" VERSION;
E 4
I 4
D 18
char	ident[] = "st201 nic driver v" VERSION;
E 18
I 18
D 19
char	ident[] = "st201/ip100a nic driver v" VERSION;
E 19
I 19
char	ident[] = "st201/ip100a driver v" VERSION;
E 19
E 18
E 4
D 17
char	_depends_on[] = {"misc/gld"};
E 17

/* Debugging support */
#ifdef DEBUG_LEVEL
static int alta_debug = DEBUG_LEVEL;
D 19
#define	DPRINTF(n, args)	if (alta_debug>(n)) cmn_err args
E 19
I 19
#define	DPRINTF(n, args)	if (alta_debug > (n)) cmn_err args
E 19
#else
#define	DPRINTF(n, args)
#endif

/*
 * Useful macros and typedefs
 */
D 17
#define	FALSE	(0)
#define	TRUE	(!FALSE)
E 17
I 17
D 19
#ifdef i86pc
#define	LE32(x)		((uint32_t)(x))
#else
#define	LE32(x)		ddi_swap32((uint32_t)(x))
#endif
E 19
I 19
#define	ONESEC	(drv_usectohz(1*1000000))
#define	ALTA_TFD(p)	((struct alta_tfd *)(void *)(p))
#define	ALTA_RFD(p)	((struct alta_rfd *)(void *)(p))
E 19
E 17

I 10
D 17
#define	STRUCT_COPY(a, b)	bcopy(&(b), &(a), sizeof(a))

E 17
I 11
D 14
#if defined(sparc) || defined(sparcv9)
#define	LE32(x)	gem_le32(x)
#else
#define	LE32(x)	(x)
#endif

E 14
E 11
E 10
/*
 * ST201 TFD and RFD structure
 */
struct alta_fragment {
D 14
	volatile uint32_t	Addr;
	volatile uint32_t	Len;
E 14
I 14
D 19
	uint32_t	Addr;
	uint32_t	Len;
E 19
I 19
	volatile uint32_t	Addr;
	volatile uint32_t	Len;
E 19
E 14
};

D 4
#define	MAXTXFRAGS	7
E 4
I 4
D 22
#define	MAXTXFRAGS	GEM_MAXTXFRAGS		/* was 7 */
E 22
I 22
#define	MAXTXFRAGS	min(GEM_MAXTXFRAGS, 7)	/* alta_tfd is power of 2 */
E 22
E 4

D 19
struct alta_tfd{
D 14
	volatile uint32_t	TxDMANextPtr;
	volatile uint32_t	TxFrameControl;
E 14
I 14
	uint32_t		TxDMANextPtr;
	uint32_t		TxFrameControl;
E 19
I 19
struct alta_tfd {
	volatile uint32_t	TxDMANextPtr;
	volatile uint32_t	TxFrameControl;
E 19
E 14
	struct alta_fragment	TxDMAFrag[MAXTXFRAGS];
};

I 22
#define	MAXRXFRAGS	1
E 22

D 4
#define	MAXRXFRAGS	3
E 4
I 4
D 22
#define	MAXRXFRAGS	GEM_MAXRXFRAGS		/* was 3 */
E 4

E 22
struct alta_rfd {
D 14
	volatile uint32_t	RxDMANextPtr;
	volatile uint32_t	RxFrameStatus;
E 14
I 14
D 19
	uint32_t		RxDMANextPtr;
	uint32_t		RxFrameStatus;
E 19
I 19
	volatile uint32_t	RxDMANextPtr;
	volatile uint32_t	RxFrameStatus;
E 19
E 14
	struct alta_fragment	RxDMAFrag[MAXRXFRAGS];
};

D 8
struct alta_chip_state {
E 8
I 8
struct alta_dev {
E 8
I 5
	boolean_t	need_to_reset;
E 5
	boolean_t	tx_list_loaded;
I 3
	uint8_t		rev_id;
D 8
	uint8_t		txframeid;
E 8
I 8
	uint32_t	intmask;
I 15
D 19
	int		countdown;
E 19
I 19
	uint32_t	countdown;
E 19
D 17
#ifdef CONFIG_POLLING
E 17
I 17
	uint8_t		mac_addr[ETHERADDRL];
#ifdef GEM_CONFIG_POLLING
E 17
	int		last_poll_interval;
#endif
#ifdef TEST_TXTIMEOUT
	int		send_cnt;
#endif
E 15
E 8
E 3
};

/*
 * Our configuration
 */
D 19
#define	OUR_INTR_BITS \
E 19
I 19
#define	OUR_INTR_BITS	\
E 19
D 15
	(INT_HostError | INT_TxComplete | \
	 INT_UpdateStats | INT_TxDMAComplete | INT_RxDMAComplete)
E 15
I 15
	(INT_HostError | INT_TxComplete | INT_UpdateStats | \
D 19
	 INT_LinkEvent | INT_TxDMAComplete | INT_RxDMAComplete)
E 19
I 19
	INT_LinkEvent | INT_TxDMAComplete | INT_RxDMAComplete)
E 19
E 15

D 4
#define TX_RING_SIZE	256
#define RX_RING_SIZE	256
E 4
I 4
D 5
#define TX_RING_SIZE	128
E 5
I 5
D 15
#define TX_RING_SIZE	64
E 5
#define RX_RING_SIZE	64
E 15
I 15
#ifdef TEST_RX_EMPTY
D 19
# define RX_RING_SIZE	1
E 19
I 19
#define	RX_RING_SIZE	1
E 19
#endif
#ifdef TEST_TXDESC_FULL
D 19
# define TX_RING_SIZE	4
# define TX_BUF_SIZE	64
E 19
I 19
#define	TX_RING_SIZE	4
#define	TX_BUF_SIZE	64
E 19
#endif
E 15
E 4

I 15
D 22
#ifndef TX_RING_SIZE
D 19
# define TX_RING_SIZE	64
E 19
I 19
#define	TX_RING_SIZE	64
E 19
#endif
E 22
#ifndef TX_BUF_SIZE
D 19
# define TX_BUF_SIZE	TX_RING_SIZE
E 19
I 19
D 22
#define	TX_BUF_SIZE	TX_RING_SIZE
E 22
I 22
#define	TX_BUF_SIZE	64
E 22
E 19
#endif

D 22
#ifndef RX_RING_SIZE
D 19
# define RX_RING_SIZE	64
E 19
I 19
#define	RX_RING_SIZE	256
E 22
I 22
#ifndef TX_RING_SIZE
#define	TX_RING_SIZE	TX_BUF_SIZE
E 22
E 19
#endif
I 22

E 22
#ifndef RX_BUF_SIZE
D 19
# define RX_BUF_SIZE	RX_RING_SIZE
E 19
I 19
D 22
#define	RX_BUF_SIZE	RX_RING_SIZE
E 22
I 22
#define	RX_BUF_SIZE	256
E 22
E 19
#endif
I 22
#ifndef RX_RING_SIZE
#define	RX_RING_SIZE	RX_BUF_SIZE
#endif
E 22

E 15
D 4
#define TX_TIMEOUT		(drv_usectohz(5*1000000))
#define TX_TIMEOUT_INTERVAL	(drv_usectohz(1*1000000))
#define LINK_WATCH_INTERVAL	(drv_usectohz(1*1000000))	/* 1 sec */
E 4
D 17
#define	ONESEC			(drv_usectohz(1*1000000))
E 17
I 17
D 19
#define	ONESEC	(drv_usectohz(1*1000000))
E 17

E 19
static int	alta_tx_copy_thresh = 256;
static int	alta_rx_copy_thresh = 256;

/*
 * Supported chips
 */
struct chip_info {
	uint16_t	venid;
	uint16_t	devid;
	char		*name;
};

static struct chip_info alta_chiptbl[] = {
I 18
	{PCI_VID_SUNDANCE,	PCI_DID_ST201,	"ST201/IP100"},
E 18
	{PCI_VID_DLINK,		PCI_DID_DFE550, "DL10050"},
D 18
	{PCI_VID_SUNDANCE,	PCI_DID_ST201,	"ST201"},
E 18
I 18
	{PCI_VID_SUNDANCE,	PCI_DID_IP100A,	"IP100A"},
E 18
};
D 19
#define CHIPTABLESIZE   (sizeof(alta_chiptbl)/sizeof(struct chip_info))
E 19
I 19
#define	CHIPTABLESIZE   (sizeof (alta_chiptbl)/sizeof (struct chip_info))
E 19

/* ======================================================== */
D 19
 
E 19
I 19

E 19
/* mii operations */
static void  alta_mii_sync(struct gem_dev *);
D 15
static uint16_t  alta_mii_read(struct gem_dev *, int);
static void alta_mii_write(struct gem_dev *, int, uint16_t);
E 15
I 15
static uint16_t alta_mii_read(struct gem_dev *, uint_t);
D 17
static void alta_mii_write_raw(struct gem_dev *, uint_t, uint16_t);
E 17
static void alta_mii_write(struct gem_dev *, uint_t, uint16_t);
I 22
static int  alta_mii_probe(struct gem_dev *);
E 22
E 15

/* nic operations */
I 15
static int alta_attach_chip(struct gem_dev *);
E 15
static int alta_reset_chip(struct gem_dev *);
D 17
static void alta_init_chip(struct gem_dev *);
static void alta_start_chip(struct gem_dev *);
static void alta_stop_chip(struct gem_dev *);
static void alta_set_media(struct gem_dev *);
static void alta_set_rx_filter(struct gem_dev *);
static void alta_get_stats(struct gem_dev *);
E 17
I 17
static int alta_init_chip(struct gem_dev *);
static int alta_start_chip(struct gem_dev *);
static int alta_stop_chip(struct gem_dev *);
static int alta_set_media(struct gem_dev *);
static int alta_set_rx_filter(struct gem_dev *);
static int alta_get_stats(struct gem_dev *);
E 17
D 15
static int alta_init_mac_addr(struct gem_dev *);
E 15

/* descriptor operations */
D 17
static int alta_tx_desc_write(struct gem_dev *dp, uint_t slot,
E 17
I 17
static int alta_tx_desc_write(struct gem_dev *dp, int slot,
E 17
D 19
		    ddi_dma_cookie_t *dmacookie, int frags, uint32_t flag);
E 19
I 19
		    ddi_dma_cookie_t *dmacookie, int frags, uint64_t flag);
E 19
D 17
static int alta_rx_desc_write(struct gem_dev *dp, uint_t slot,
E 17
I 17
static void alta_tx_start(struct gem_dev *dp, int slot, int nslot);
static void alta_rx_desc_write(struct gem_dev *dp, int slot,
E 17
		    ddi_dma_cookie_t *dmacookie, int frags);
static uint_t alta_tx_desc_stat(struct gem_dev *dp, int slot, int ndesc);
D 16
static uint_t alta_rx_desc_stat(struct gem_dev *dp, int slot, int ndesc);
E 16
I 16
static uint64_t alta_rx_desc_stat(struct gem_dev *dp, int slot, int ndesc);
E 16

static void alta_tx_desc_init(struct gem_dev *dp, int slot);
static void alta_rx_desc_init(struct gem_dev *dp, int slot);
static void alta_tx_desc_clean(struct gem_dev *dp, int slot);
static void alta_rx_desc_clean(struct gem_dev *dp, int slot);

/* interrupt handler */
D 19
static u_int alta_interrupt(struct gem_dev *dp);
E 19
I 19
static uint_t alta_interrupt(struct gem_dev *dp);
E 19

/* ======================================================== */

/* mapping attributes */
/* Data access requirements. */
D 3
static struct ddi_device_acc_attr alta_chip_state_attr = {
E 3
I 3
static struct ddi_device_acc_attr alta_dev_attr = {
E 3
	DDI_DEVICE_ATTR_V0,
	DDI_STRUCTURE_LE_ACC,
	DDI_STRICTORDER_ACC
};

/* On sparc, the buffers should be native endianness */
static struct ddi_device_acc_attr alta_buf_attr = {
	DDI_DEVICE_ATTR_V0,
	DDI_NEVERSWAP_ACC,	/* native endianness */
	DDI_STRICTORDER_ACC
};

I 22
#define	MAX_FRAG_LEN	0x7ff
#define	ALTA_MAX_PACKET_SIZE	2040
E 22
D 11
static ddi_dma_attr_t alta_dma_attr_txbuf = {
E 11
I 11
static ddi_dma_attr_t alta_dma_attr_buf = {
E 11
	DMA_ATTR_V0,		/* dma_attr_version */
	0,			/* dma_attr_addr_lo */
	0xffffffffull,		/* dma_attr_addr_hi */
D 22
	0xffffffffull,		/* dma_attr_count_max */
E 22
I 22
	MAX_FRAG_LEN,		/* dma_attr_count_max */
E 22
	1,			/* dma_attr_align */
D 4
	0xffffffff,		/* dma_attr_burstsizes */
E 4
I 4
D 11
	0,			/* dma_attr_burstsizes */
E 11
I 11
D 22
	0xffffffff,		/* dma_attr_burstsizes */
E 22
I 22
	MAX_FRAG_LEN,		/* dma_attr_burstsizes */
E 22
E 11
E 4
	1,			/* dma_attr_minxfer */
D 22
	0xffffffffull,		/* dma_attr_maxxfer */
E 22
I 22
	ALTA_MAX_PACKET_SIZE,	/* dma_attr_maxxfer */
E 22
	0xffffffffull,		/* dma_attr_seg */
D 11
	MAXTXFRAGS,		/* dma_attr_sgllen */
E 11
I 11
D 19
	0,/* patched later */	/* dma_attr_sgllen */
E 19
I 19
	0, /* patched later */	/* dma_attr_sgllen */
E 19
E 11
	1,			/* dma_attr_granular */
	0			/* dma_attr_flags */
};

D 11
static ddi_dma_attr_t alta_dma_attr_rxbuf = {
E 11
I 11
static ddi_dma_attr_t alta_dma_attr_desc = {
E 11
	DMA_ATTR_V0,		/* dma_attr_version */
D 11
	0,			/* dma_attr_addr_lo */
	0xffffffffull,		/* dma_attr_addr_hi */
	0xffffffffull,		/* dma_attr_count_max */
	1,			/* dma_attr_align */
D 4
	0xffffffff,		/* dma_attr_burstsizes */
E 4
I 4
	0,			/* dma_attr_burstsizes */
E 4
	1,			/* dma_attr_minxfer */
	0xffffffffull,		/* dma_attr_maxxfer */
	0xffffffffull,		/* dma_attr_seg */
	MAXRXFRAGS,		/* dma_attr_sgllen */
	1,			/* dma_attr_granular */
	0			/* dma_attr_flags */
};

static ddi_dma_attr_t alta_dma_attr_nosc = {
	DMA_ATTR_V0,		/* dma_attr_version */
E 11
I 4
D 5
#ifdef notdef	/* zero means no tx/rx list */
E 4
	0,			/* dma_attr_addr_lo */
I 4
#else
	0x2000,			/* dma_attr_addr_lo */
#endif
E 5
I 5
	8,			/* dma_attr_addr_lo */
E 5
E 4
	0xffffffffull,		/* dma_attr_addr_hi */
	0xffffffffull,		/* dma_attr_count_max */
D 4
	16,			/* dma_attr_align */
	0xffffffff,		/* dma_attr_burstsizes */
E 4
I 4
	8,			/* dma_attr_align */
D 11
	0,			/* dma_attr_burstsizes */
E 11
I 11
	0xffffffff,		/* dma_attr_burstsizes */
E 11
E 4
	1,			/* dma_attr_minxfer */
	0xffffffffull,		/* dma_attr_maxxfer */
	0xffffffffull,		/* dma_attr_seg */
	1,			/* dma_attr_sgllen */
	1,			/* dma_attr_granular */
	0			/* dma_attr_flags */
};

/* ======================================================== */
/*
I 19
 * misc routines
 */
/* ======================================================== */
static int
alta_log2(uint32_t val)
{
	int	i;

	for (i = 0; i < 32; i++) {
		if ((1 << i) >= val) {
			break;
		}
	}

	return (i);
}

/* ======================================================== */
/*
E 19
 * HW manupilation routines
 */
/* ======================================================== */

static int
alta_reset_chip(struct gem_dev *dp)
{
D 8
	int	i;
E 8
I 8
D 17
	int			i;
E 17
I 17
	int		i;
E 17
D 19
	struct alta_dev	*lp = (struct alta_dev *)dp->private;
E 19
I 19
	struct alta_dev	*lp = dp->private;
E 19
E 8

	/* Reset the chip. */
I 17
	bzero(lp->mac_addr, ETHERADDRL);

E 17
I 8
D 19
	lp->intmask = 0;
E 19
E 8
I 4
	OUTW(dp, IntEnable, 0);
I 19

	/* XXX - should not reset AC_AutoInit nor AC_RstOut */
E 19
E 4
	OUTL(dp, AsicCtrl,
D 5
		AC_GlobalReset | AC_DMA | AC_FIFO | AC_Network
		| AC_Host | AC_AutoInit | AC_RstOut);
E 5
I 5
D 19
		AC_GlobalReset | AC_RxReset | AC_TxReset
		| AC_DMA | AC_FIFO | AC_Network
D 15
		/*| AC_Host | AC_AutoInit | AC_RstOut*/);
E 15
I 15
		| AC_Host /* | AC_AutoInit | AC_RstOut*/);
E 19
I 19
	    AC_GlobalReset | AC_RxReset | AC_TxReset
	    | AC_DMA | AC_FIFO | AC_Network | AC_Host);
E 19
E 15
E 5
D 17
	i = 0;
	while ((INL(dp, AsicCtrl) & AC_ResetBusy) != 0) {
E 17
I 17

D 19
	for (i = 0; (INL(dp, AsicCtrl) & AC_ResetBusy) != 0; i++) {
E 19
I 19
	i = 0;
	while (INL(dp, AsicCtrl) & AC_ResetBusy) {
E 19
E 17
		drv_usecwait(10);
D 17
		if (i++ > 200) {
			cmn_err(CE_WARN, "%s: alta_reset_chip: timeout",
				dp->name);
			return -1;
E 17
I 17
D 19
		if (i > 200) {
E 19
I 19
		if (i++ > 200) {
E 19
			cmn_err(CE_WARN,
D 19
				"!%s: %s: timeout", dp->name, __func__);
E 19
I 19
			    "!%s: %s: timeout", dp->name, __func__);
E 19
			return (GEM_FAILURE);
E 17
		}
	}
D 17
	DPRINTF(1, (CE_CONT, "!%s: alta_reset_chip: took %d uS",
				dp->name, i*10));
E 17

D 17
	return 0;
E 17
I 17
	DPRINTF(1, (CE_CONT, "!%s: %s: took %d uS", dp->name, __func__, i*10));

	return (GEM_SUCCESS);
E 17
}

D 17
static void
E 17
I 17
static int
E 17
alta_init_chip(struct gem_dev *dp)
{
D 8
	struct alta_chip_state	*lp = (struct alta_chip_state *)dp->private;
E 8
I 8
D 19
	struct alta_dev	*lp = (struct alta_dev *)dp->private;
E 19
I 19
	struct alta_dev	*lp = dp->private;
E 19
E 8

D 11
	DPRINTF(2, (CE_CONT, "?%s: alta_init_chip: called", dp->name));
E 11
I 11
D 18
	DPRINTF(1, (CE_CONT, "!%s: alta_init_chip: called", dp->name));
E 18
I 18
	DPRINTF(1, (CE_CONT, "!%s: %s: called", dp->name, __func__));
E 18
E 11

	ASSERT(mutex_owned(&dp->intrlock));
I 8
D 19
	ASSERT(lp->intmask == 0);
E 19
E 8

	/* AsicCtrl : assume the chip stopped */

D 3
	DPRINTF(3, (CE_CONT, "!alta_init_chip called, mc0: %b",
		INW(dp, MACCtrl0), MC0_BITS));
	DPRINTF(3, (CE_CONT, "!mc1: %b",
		INW(dp, MACCtrl1), MC1_BITS));
	DPRINTF(3, (CE_CONT, "!ac: %b",
E 3
I 3
D 17
	DPRINTF(3, (CE_CONT, "!%s alta_init_chip called, mc0: %b",
		dp->name, INW(dp, MACCtrl0), MC0_BITS));
	DPRINTF(3, (CE_CONT, "!%s: mc1: %b",
		dp->name, INW(dp, MACCtrl1), MC1_BITS));
	DPRINTF(3, (CE_CONT, "!%s: ac: %b", dp->name,
E 17
I 17
D 18
	DPRINTF(3, (CE_CONT, "!%s %s called, mc0: %b, mc1:%b, ac:%b",
E 18
I 18
	DPRINTF(0, (CE_CONT, "!%s %s called, mc0: %b, mc1:%b, ac:%b, pc:%b",
E 18
D 19
		dp->name, __func__,
		INW(dp, MACCtrl0), MC0_BITS,
		INW(dp, MACCtrl1), MC1_BITS,
E 17
E 3
D 18
		INL(dp, AsicCtrl), AC_BITS));
E 18
I 18
		INL(dp, AsicCtrl), AC_BITS,
		INB(dp, PhyCtrl), PC_BITS));
E 19
I 19
	    dp->name, __func__,
	    INW(dp, MACCtrl0), MC0_BITS,
	    INW(dp, MACCtrl1), MC1_BITS,
	    INL(dp, AsicCtrl), AC_BITS,
	    INB(dp, PhyCtrl), PC_BITS));
E 19
E 18
D 5
	
E 5
I 5
#ifdef notdef
E 5
	/* MACCtrl1: Ensure all functions are disabled */
	OUTW(dp, MACCtrl1,
D 19
		MC1_StatisticsDisable | MC1_TxDisable | MC1_RxDisable);
E 19
I 19
	    MC1_StatisticsDisable | MC1_TxDisable | MC1_RxDisable);
E 19
D 5

E 5
I 5
#endif
E 5
D 19
	/* MACCtrl0: Ensure normal operational mode*/
E 19
I 19
	/* MACCtrl0: Ensure normal operational mode */
E 19
	OUTW(dp, MACCtrl0, MC0_IFSSelect802_3);
D 17

E 17
I 17
D 21
#ifdef GEM_CONFIG_VLAN
E 21
I 21
#ifdef GEM_CONFIG_GLDv3
E 21
D 19
	OUTW(dp, MaxFrameSize, dp->mtu + sizeof(struct ether_header) + 4);
E 19
I 19
	OUTW(dp, MaxFrameSize, dp->mtu + sizeof (struct ether_header) + 4);
E 19
#else
E 17
I 5
D 19
	OUTW(dp, MaxFrameSize, dp->mtu + sizeof(struct ether_header));
E 19
I 19
	OUTW(dp, MaxFrameSize, dp->mtu + sizeof (struct ether_header));
E 19
D 17

E 17
I 17
#endif
E 17
E 5
	/* TxDMA */
	OUTL(dp, TxDMAListPtr, 0);
	OUTB(dp, TxDMAPollPeriod, TxDMAPollPeriodMax);
D 17
	lp->tx_list_loaded = FALSE;
E 17
I 17
	lp->tx_list_loaded = B_FALSE;
E 17

	/* RxDMA */
	OUTL(dp, RxDMAListPtr, 0);
	OUTB(dp, RxDMAPollPeriod, RxDMAPollPeriodMax);
I 5

	OUTB(dp, RxDMABurstThresh, dp->rxthr/RxDMABurstThreshUnit);

	/* TxStartThreash : depends on txthr */
E 5
#ifdef TXUNDERRUNTEST
D 5
	/* TxStartThread : 256 byte */
	OUTW(dp, TxStartThresh, 1);
	OUTW(dp, TxDMABurstThresh, 2047/TxDMABurstThreshUnit);
#else
D 4
	/* TxStartThread : 256 byte */
	OUTW(dp, TxStartThresh, 256/TxStartThreshUnit);
E 4
I 4
	/* TxStartThread : store & forword */
	OUTW(dp, TxStartThresh, TxStartThreshMax &~(TxStartThreshUnit-1));
E 5
I 5
	dp->txmaxdma = min(256, dp->txthr);
E 5
E 4
#endif
D 5
	/* TxDMAUrgentThread : 128 byte */
	OUTB(dp, TxDMAUrgentThresh, 128/TxDMAUrgentThreshUnit);
E 5
I 5
	OUTW(dp, TxStartThresh, dp->txthr & ~(TxStartThreshUnit-1));
D 19
	OUTB(dp, TxDMABurstThresh, max(dp->txmaxdma/TxDMABurstThreshUnit, 1));
E 19
I 19
	OUTB(dp, TxDMABurstThresh,
	    max(dp->txmaxdma / TxDMABurstThreshUnit, 1));
E 19
E 5

D 5
	/* TxReleaseThread : 256 byte */
	OUTB(dp, TxReleaseThresh, 256/TxReleaseThreshUnit);
E 5
I 5
	/* TxDMAUrgentThreash : half of txthr */
D 19
	OUTB(dp, TxDMAUrgentThresh, max((dp->txthr/2)/TxDMAUrgentThreshUnit,1));
E 19
I 19
	OUTB(dp, TxDMAUrgentThresh,
	    max((dp->txthr / 2) / TxDMAUrgentThreshUnit, 1));
E 19
E 5

I 5
	/* TxReleaseThreash : 128 byte */
	OUTB(dp, TxReleaseThresh, 128/TxReleaseThreshUnit);

E 5
	/* RxEarlyThreth: disable Eerly Rx */
	OUTW(dp, RxEarlyThresh, RxEarlyThreshDisable);

D 4
	/* Set InterruptMask */
	OUTW(dp, IntEnable, OUR_INTR_BITS);

E 4
D 3
	DPRINTF(1, (CE_CONT, "!alta_init_chip: mc0: %b, mc1: %b, ac: %b",
E 3
I 3
D 5
	DPRINTF(1, (CE_CONT, "!%s: alta_init_chip: mc0: %b, mc1: %b, ac: %b",
E 5
I 5
D 19
	DPRINTF(2, (CE_CONT, "!%s: alta_init_chip: mc0: %b, mc1: %b, ac: %b",
E 5
			dp->name,
E 3
			INW(dp, MACCtrl0), MC0_BITS,
			INW(dp, MACCtrl1), MC1_BITS,
			INL(dp, AsicCtrl), AC_BITS));
E 19
I 19
	DPRINTF(2, (CE_CONT, "!%s: %s: mc0: %b, mc1: %b, ac: %b",
	    dp->name, __func__,
	    INW(dp, MACCtrl0), MC0_BITS,
	    INW(dp, MACCtrl1), MC1_BITS,
	    INL(dp, AsicCtrl), AC_BITS));
E 19
I 17

	return (GEM_SUCCESS);
E 17
}

D 17
static void
E 17
I 17
static int
E 17
alta_start_chip(struct gem_dev *dp)
{
I 3
D 8
	struct alta_chip_state	*lp = (struct alta_chip_state *)dp->private;
E 8
I 8
D 19
	struct alta_dev	*lp = (struct alta_dev *)dp->private;
E 19
I 19
	struct alta_dev	*lp = dp->private;
E 19
E 8

E 3
	ASSERT(mutex_owned(&dp->intrlock));

	/* Enable statistics */
I 4
D 5
#ifdef notdef
E 4
	alta_get_stats(dp);
	bzero(&dp->stats, sizeof(dp->stats));
I 4
#endif
E 5
E 4
	OUTW(dp, MACCtrl1, MC1_StatisticsEnable);
D 15

E 15
I 15
D 17
#ifndef GEM_DELAYED_START
E 15
D 4
	/* Set media */
E 4
I 4
	/* Set media mode */
E 17
I 17
D 18

E 18
I 18
D 19
#if 0
E 18
	/* Ensure media mode */
E 17
E 4
	alta_set_media(dp);
I 4
D 15

E 15
I 15
D 17
#endif
E 15
E 4
D 3

E 3
I 3
#ifdef CONFIG_DFE580TX
E 17
I 17
D 18

E 18
I 18
#endif
E 19
I 19

E 19
E 18
E 17
	if (lp->rev_id >= 0x14) {
I 19
		/* XXX - undocumented */
E 19
		OUTB(dp, DebugCtrl1, 0x01);
	}
D 17
#endif
E 17
I 17

E 17
E 3
D 5
	/* Enable transmitter and receiver */
	OUTW(dp, MACCtrl1, MC1_TxEnable | MC1_RxEnable);

E 5
	ASSERT((dp->rx_ring_dma & 7) == 0);
	OUTL(dp, RxDMAListPtr, dp->rx_ring_dma);

I 5
	/* Enable transmitter and receiver */
	OUTW(dp, MACCtrl1, MC1_TxEnable | MC1_RxEnable);

E 5
D 3
	DPRINTF(1, (CE_CONT, "!alta_start_chip: mc0: %b, mc1: %b",
		INW(dp, MACCtrl0), MC0_BITS,
E 3
I 3
D 4
	DPRINTF(1, (CE_CONT, "!%s: alta_start_chip: mc0: %b, mc1: %b",
E 4
I 4
	/* Set InterruptMask */
D 19
	if ((dp->misc_flag & GEM_NOINTR) == 0) {
I 8
		lp->intmask = OUR_INTR_BITS;
E 19
I 19
	lp->intmask = OUR_INTR_BITS;
E 19
E 8
D 15
		OUTW(dp, IntEnable, OUR_INTR_BITS);
E 15
I 15
D 17
#ifdef CONFIG_POLLING
E 17
I 17
#ifdef GEM_CONFIG_POLLING
E 17
D 19
		lp->intmask |= INT_IntRequest;
E 19
I 19
	lp->intmask |= INT_IntRequest;
E 19
#endif
I 19
	if ((dp->misc_flag & GEM_NOINTR) == 0) {
E 19
		OUTW(dp, IntEnable, lp->intmask);
E 15
	}
I 5
D 19

E 19
I 19
	/* disable interval timer */
E 19
E 5
D 8
	DPRINTF(2, (CE_CONT, "!%s: alta_start_chip: mc0: %b, mc1: %b",
E 8
I 8
D 15
	DPRINTF(1, (CE_CONT, "!%s: alta_start_chip: mc0: %b, mc1: %b",
E 15
I 15
D 17
	lp->countdown = 5000;
E 17
I 17
	lp->countdown = 0;
E 17
	OUTW(dp, Countdown, lp->countdown);

I 19
	OUTL(dp, DMACtrl, 0);
E 19
D 17
	DPRINTF(0, (CE_CONT, "!%s: alta_start_chip: mc0: %b, mc1: %b",
E 15
E 8
E 4
		dp->name, INW(dp, MACCtrl0), MC0_BITS,
E 3
		INW(dp, MACCtrl1), MC1_BITS));
D 3
	DPRINTF(1, (CE_CONT, "!alta_start_chip: dmactrl: %b",
		INL(dp, DMACtrl), DC_BITS));
E 3
I 3
D 4
	DPRINTF(1, (CE_CONT, "!%s: alta_start_chip: dmactrl: %b",
E 4
I 4
D 8
	DPRINTF(2, (CE_CONT, "!%s: alta_start_chip: dmactrl: %b",
E 8
I 8
D 15
	DPRINTF(1, (CE_CONT, "!%s: alta_start_chip: dmactrl: %b",
E 15
I 15
	DPRINTF(0, (CE_CONT, "!%s: alta_start_chip: dmactrl: %b",
E 15
E 8
E 4
		dp->name, INL(dp, DMACtrl), DC_BITS));
E 17
I 17
	DPRINTF(0, (CE_CONT, "!%s: %s: mc0: %b, mc1: %b, dmactrl: %b",
D 19
		dp->name, __func__,
		INW(dp, MACCtrl0), MC0_BITS,
		INW(dp, MACCtrl1), MC1_BITS,
		INL(dp, DMACtrl), DC_BITS));
E 19
I 19
	    dp->name, __func__,
	    INW(dp, MACCtrl0), MC0_BITS,
	    INW(dp, MACCtrl1), MC1_BITS,
	    INL(dp, DMACtrl), DC_BITS));
E 19

	return (GEM_SUCCESS);
E 17
E 3
}

D 17
static void
E 17
I 17
static int
E 17
alta_stop_chip(struct gem_dev *dp)
{
I 8
D 19
	struct alta_dev	*lp = (struct alta_dev *)dp->private;
E 19
I 19
	struct alta_dev	*lp = dp->private;
E 19

I 11
D 17
	DPRINTF(1, (CE_CONT, "!%s: alta_stop_chip: called", dp->name));
E 17
I 17
	DPRINTF(1, (CE_CONT, "!%s: %s: called", dp->name, __func__));
E 17

E 11
E 8
	/* inhibit interrupt */
I 8
D 15
	lp->intmask = 0;
E 8
	OUTW(dp, IntEnable, 0);
E 15
I 15
D 19
	OUTW(dp, IntEnable, lp->intmask = 0);
E 19
I 19
	/* XXX - don't clear lp->intmask to avoid bogus interrupts */
	OUTW(dp, IntEnable, 0);
E 19
E 15

	/* no more statistics */
	OUTW(dp, MACCtrl1, MC1_StatisticsDisable);

	/* stop receiver and transceiver */
	OUTW(dp, MACCtrl1, MC1_RxDisable | MC1_TxDisable);
I 5
D 19
	drv_usecwait(1000);
E 19
I 19
	if (dp->speed == GEM_SPD_10) {
		drv_usecwait(2000);
	} else {
		drv_usecwait(200);
	}
E 19
I 11

	/* reset DMA pointers */
	OUTL(dp, AsicCtrl, AC_RxReset | AC_TxReset | AC_DMA);
I 17

	return (GEM_SUCCESS);
E 17
E 11
E 5
}


static uint16_t
alta_read_eeprom(struct gem_dev *dp, uint_t offset)
{
	int		i;

	OUTW(dp, EepromCtrl, EEC_OpcodeRd | (offset & EEC_Address));
	drv_usecwait(100);

D 17
	i = 0;
	while (++i<100) {
		if ((INW(dp, EepromCtrl) & EEC_Busy) == 0) {
			/* done */
			DPRINTF(4, (CE_CONT, "%s eeprom_read took %d uS",
				dp->name, i*10));
			return INW(dp, EepromData);
E 17
I 17
D 19
	for (i = 0; (INW(dp, EepromCtrl) & EEC_Busy) != 0; i++) {
E 19
I 19
	for (i = 0; INW(dp, EepromCtrl) & EEC_Busy; i++) {
E 19
		if (i > 100) {
D 19
			cmn_err(CE_WARN, "%s: %s timeout", dp->name, __func__);

E 19
I 19
			cmn_err(CE_WARN, "!%s: %s timeout", dp->name, __func__);
E 19
			return (0xffff);
E 17
		}
		drv_usecwait(10);
	}

D 17
	cmn_err(CE_CONT, "%s eeprom_read timeout", dp->name);
E 17
I 17
D 19
	/* done */
	DPRINTF(4, (CE_CONT, "%s: %s: took %d uS", dp->name, __func__, i*10));
E 19
I 19
	DPRINTF(4, (CE_CONT, "!%s: %s: took %d uS", dp->name, __func__, i*10));
E 19
E 17

D 17
	return 0xffff;
E 17
I 17
	return (INW(dp, EepromData));
E 17
}

#ifdef DEBUG_LEVEL
static void
alta_eeprom_dump(struct gem_dev *dp)
{
	int		i;
	uint16_t	prom[0x14];

	for (i = 0; i < 0x14; i++) {
		prom[i] = alta_read_eeprom(dp, i);
	}

	cmn_err(CE_CONT, "!%s: eeprom dump:", dp->name);
	for (i = 0; i < 0x14; i += 4) {
D 19
		cmn_err(CE_CONT, "!0x%02x: 0x%04x 0x%04x 0x%04x 0x%04x", 
			i, prom[i], prom[i + 1], prom[i + 2], prom[i + 3]);
E 19
I 19
		cmn_err(CE_CONT, "!0x%02x: 0x%04x 0x%04x 0x%04x 0x%04x",
		    i, prom[i], prom[i + 1], prom[i + 2], prom[i + 3]);
E 19
	}
}
#endif /* DEBUG_LEVEL */

static int
D 19
alta_attach_chip(struct gem_dev *dp)	
E 19
I 19
alta_attach_chip(struct gem_dev *dp)
E 19
{
	int			i;
	uint16_t		val;

	for (i = 0; i < ETHERADDRL; i += 2) {
D 19
		val =  alta_read_eeprom(dp, 0x10 + i/2);
E 19
I 19
		val = alta_read_eeprom(dp, 0x10 + i/2);
E 19

D 17
		dp->dev_addr.ether_addr_octet[i    ] = val;
		dp->dev_addr.ether_addr_octet[i + 1] = val >> 8;

		OUTW(dp, StationAddress + i, val);
E 17
I 17
D 19
		dp->dev_addr.ether_addr_octet[i + 0] = (uint8_t) val;
		dp->dev_addr.ether_addr_octet[i + 1] = (uint8_t) (val >> 8);
E 19
I 19
		dp->dev_addr.ether_addr_octet[i + 0] = (uint8_t)val;
		dp->dev_addr.ether_addr_octet[i + 1] = (uint8_t)(val >> 8);
E 19
E 17
	}
I 8
D 11

	dp->txthr = ETHERMAX;

E 11
I 11
D 17
#ifdef notdef
	dp->txthr = ETHERMAX;	/* now 1024 */
#endif
E 17
I 17

E 17
E 11
E 8
#if DEBUG_LEVEL > 4
	alta_eeprom_dump(dp);
#endif
D 17
	return 0;
E 17
I 17
D 21
#ifdef GEM_CONFIG_VLAN
E 21
I 21
#ifdef GEM_CONFIG_GLDv3
E 21
	dp->misc_flag |= GEM_VLAN_SOFT;
#endif
I 21
	dp->misc_flag |= GEM_POLL_RXONLY;

E 21
	return (GEM_SUCCESS);
E 17
}

I 3
static uint32_t
alta_mcast_hash(struct gem_dev *dp, uint8_t *addr)
{
D 17
	return gem_ether_crc_be(addr);
E 17
I 17
D 21
	return (gem_ether_crc_be(addr, ETHERADDRL));
E 21
I 21
	/* hash key is 6 bits of LSB in be-crc */
	return (gem_ether_crc_be(addr, ETHERADDRL) % 64);
E 21
E 17
}

E 3
D 17
static void
E 17
I 17
static int
E 17
D 19
alta_set_rx_filter(struct gem_dev *dp)	
E 19
I 19
alta_set_rx_filter(struct gem_dev *dp)
E 19
{
	uint8_t		mode;
	uint8_t		*newmac;
	int		i;
D 17
	int		chip_state;
	uint16_t	val;
E 17
I 3
D 21
	uint16_t	mhash[4];
E 21
I 21
	uint64_t	mhash;
E 21
I 17
D 19
	struct alta_dev	*lp = (struct alta_dev *)dp->private;
E 19
I 19
	struct alta_dev	*lp = dp->private;
E 19
E 17
E 3

	ASSERT(mutex_owned(&dp->intrlock));
I 3
D 17
	bzero(mhash, sizeof(mhash));
E 17
I 17
D 21
	mhash[0] = mhash[1] = mhash[2] = mhash[3] = 0;
E 21
I 21
	mhash = 0;
E 21
E 17
E 3

I 17
	mode = RM_ReceiveUnicast | RM_ReceiveBroadcast;
E 17
D 18
	if ((dp->rxmode & RXMODE_PROMISC) != 0) {
E 18
I 18
	if ((dp->rxmode & RXMODE_ENABLE) == 0) {
I 19
		/* disabled */
E 19
		mode = 0;
D 19
	}
	else if ((dp->rxmode & RXMODE_PROMISC) != 0) {
E 19
I 19
	} else if (dp->rxmode & RXMODE_PROMISC) {
E 19
E 18
		/* promiscous */
D 17
		mode = RM_ReceiveAllFrames;
E 17
I 17
		mode |= RM_ReceiveAllFrames;
E 17
D 19
	}
D 3
	else if (dp->mc_count > 0 || (dp->rxmode & RXMODE_ALLMULTI) != 0) {
		/* Normal mode with multicast */
E 3
I 3
D 17
	else if ((dp->rxmode & RXMODE_ALLMULTI) != 0) {
E 3
		mode = RM_ReceiveUnicast
		     | RM_ReceiveBroadcast
		     | RM_ReceiveMulticast;
E 17
I 17
	else if ((dp->rxmode & RXMODE_ALLMULTI) != 0 || dp->mc_count > 32) {
E 19
I 19
	} else if ((dp->rxmode & RXMODE_ALLMULTI) || dp->mc_count > 32) {
		/* allmulti */
E 19
		mode |= RM_ReceiveMulticast;
E 17
D 19
	}
D 17
	else {
		/* Normal mode */
		mode = RM_ReceiveUnicast | RM_ReceiveBroadcast;
E 17
I 17
	else if (dp->mc_count > 0) {
E 19
I 19
	} else if (dp->mc_count > 0) {
E 19
		/* Normal mode with multicast */
		mode |= RM_ReceiveMulticastHash;
E 17
I 3

D 17
		/* Make multicast hash table */
		if (dp->mc_count == 0) {
			/* no multicast, do nothing */
E 17
I 17
		/* make hash table */
		for (i = 0; i < dp->mc_count; i++) {
D 21
			uint_t	k;
			/* hash key is 6 bits of LSB in be-crc */
			k = dp->mc_list[i].hash & (64 - 1);
			mhash[k / 16] |= 1 << (k % 16);
E 21
I 21
			mhash |= 1ULL << dp->mc_list[i].hash;
E 21
E 17
D 5
		} else
#ifdef USE_MULTICAST_HASHTBL
		if (dp->mc_count <= 100) {
E 5
I 5
		}
D 17
		else if (dp->mc_count <= 100) {
E 5
			mode |= RM_ReceiveMulticastHash;
			/* make hash table */
			for (i = 0; i < dp->mc_count; i++) {
				uint_t	k;
				/* hash key is 6 bits of LSB in be-crc */
				k = dp->mc_list[i].hash & (4*16 - 1);
				mhash[k / 16] |= 1 << (k % 16);
			}
D 5
		} else
#endif
		{
E 5
I 5
		}
		else {
E 5
			mode |= RM_ReceiveMulticast;
		}
E 17
E 3
	}

	/* set rx mode */
D 5
	DPRINTF(1, (CE_CONT, "!%s: set_rx_filter: setting mode: %b",
E 5
I 5
D 17
	DPRINTF(2, (CE_CONT, "!%s: set_rx_filter: setting mode: %b",
E 5
		dp->name, mode, RM_BITS));
E 17
I 17
	DPRINTF(2, (CE_CONT, "!%s: %s: setting mode: %b",
D 19
		dp->name, __func__, mode, RM_BITS));
E 19
I 19
	    dp->name, __func__, mode, RM_BITS));
E 19
E 17

I 18
D 19
	if (mode != 0) {
E 19
I 19
	if (mode) {
E 19
		OUTB(dp, ReceiveMode, RM_ReceiveAllFrames);
	}

E 18
D 17
	/* stop rx temporary */
	if (dp->nic_active) {
		OUTW(dp, MACCtrl1, MC1_RxDisable);
	}

	OUTB(dp, ReceiveMode, mode);

E 17
D 3
	/* clear multicast hash table */
E 3
I 3
	/* set multicast hash table up */
E 3
	for (i = 0; i < 4; i++) {
D 3
		OUTW(dp, HashTable + i*sizeof(uint16_t), 0);
E 3
I 3
D 19
		OUTW(dp, HashTable + i*sizeof(uint16_t), mhash[i]);
E 19
I 19
D 21
		OUTW(dp, HashTable + i*sizeof (uint16_t), mhash[i]);
E 21
I 21
		OUTW(dp, HashTable + i*2, mhash >> (i*16));
E 21
E 19
E 3
	}

D 17
	/* set station address */
E 17
	newmac = dp->cur_addr.ether_addr_octet;
D 17
	for (i = 0; i < ETHERADDRL; i += 2) {
		OUTW(dp, StationAddress + i, (newmac[i+1] << 8) | newmac[i]);
E 17
I 17
D 19
	if (bcmp(newmac, lp->mac_addr, ETHERADDRL) != 0) {
E 19
I 19
	if (bcmp(newmac, lp->mac_addr, ETHERADDRL)) {
E 19
		/* need to update the station address */
		for (i = 0; i < ETHERADDRL; i += 2) {
			OUTW(dp, StationAddress + i,
D 19
				(newmac[i+1] << 8) | newmac[i]);
E 19
I 19
			    (newmac[i+1] << 8) | newmac[i]);
E 19
		}
		bcopy(newmac, lp->mac_addr, ETHERADDRL);
E 17
	}

D 17
	/* enable rx again */
	if (dp->nic_active) {
		OUTW(dp, MACCtrl1, MC1_RxEnable);
	}
E 17
I 17
	OUTB(dp, ReceiveMode, mode);

	return (GEM_SUCCESS);
E 17
}

D 17
static void
E 17
I 17
static int
E 17
alta_set_media(struct gem_dev *dp)
{
	uint16_t	old;
	uint16_t	new;
	int		i;

	ASSERT(mutex_owned(&dp->intrlock));
D 15

E 15
I 15
D 18
#ifdef GEM_DELAYED_START
	ASSERT(dp->nic_online);
#else
E 15
I 4
D 17
	if (!dp->nic_active) {
		return;
E 17
I 17
	if (!dp->mac_active) {
		return (GEM_SUCCESS);
E 17
	}
D 15

E 15
I 15
#endif
E 18
I 18

	DPRINTF(0, (CE_CONT, "!%s %s called, mac_active;%d, pc:%b",
D 19
		dp->name, __func__,
		dp->mac_active,
		INB(dp, PhyCtrl), PC_BITS));
E 19
I 19
	    dp->name, __func__, dp->mac_active, INB(dp, PhyCtrl), PC_BITS));
E 19

E 18
E 15
E 4
	/*
	 * Notify current duplex mode to MAC
	 */
	old = INW(dp, MACCtrl0);
	new = old & ~(MC0_FullDuplexEnable | MC0_FlowControlEnable);

	if (dp->full_duplex) {
		new |= MC0_FullDuplexEnable;
D 13
		if (dp->flow_control) {
E 13
I 13

		switch (dp->flow_control) {
		case FLOW_CONTROL_SYMMETRIC:
		case FLOW_CONTROL_TX_PAUSE:
E 13
			new |= MC0_FlowControlEnable;
I 13
			break;
E 13
		}
	}

	OUTW(dp, MACCtrl0, new);
D 11
	
E 11
I 11

E 11
	if ((old ^ new) & MC0_FullDuplexEnable) {
		/*
		 * Duplex mode is changed. Need to reset Tx/Rx.
		 */
I 11
		DPRINTF(1, (CE_CONT,
D 19
		"!%s: resetting tx and rx to change duplex mode", dp->name));
E 19
I 19
		    "!%s: resetting tx and rx to change duplex mode",
		    dp->name));
E 19

E 11
		OUTL(dp, AsicCtrl, AC_TxReset | AC_RxReset);
D 17
		i = 200;
		while (INL(dp, AsicCtrl) & AC_ResetBusy) {
			if (i-- == 0) {
E 17
I 17

D 19
		for (i = 0; (INL(dp, AsicCtrl) & AC_ResetBusy) != 0; i++) {
			if (i > 200) {
E 19
I 19
		i = 0;
		while (INL(dp, AsicCtrl) & AC_ResetBusy) {
			if (i++ > 200) {
E 19
E 17
				/* Time out */
D 17
				cmn_err(CE_WARN,
				"%s: alta_set_media: tx/rx reset timeout",
				dp->name);
E 17
I 17
D 19
				cmn_err(CE_NOTE, "%s: %s: tx/rx reset timeout",
					dp->name, __func__);
E 19
I 19
				cmn_err(CE_NOTE, "!%s: %s: tx/rx reset timeout",
				    dp->name, __func__);
E 19
E 17
				break;
			}
			drv_usecwait(10);
		}

D 4
		if (dp->nic_active) {
			OUTW(dp, MACCtrl1, MC1_TxEnable | MC1_RxEnable);
		}
E 4
I 4
		OUTW(dp, MACCtrl1, MC1_TxEnable | MC1_RxEnable);
E 4
	}
I 17

	return (GEM_SUCCESS);
E 17
}

D 17
static void
E 17
I 17
static int
E 17
alta_get_stats(struct gem_dev *dp)
{
	int		first_coll;
	int		multi_coll;
I 2
	int		c;
	int		l;
E 2
	volatile int	x;

D 19
	DPRINTF(4, (CE_CONT, "!%s: alta_get_stats: called", dp->name));
E 19
I 19
	DPRINTF(4, (CE_CONT, "!%s: %s: called", dp->name, __func__));
E 19
D 7

E 7
I 7
#ifdef notdef
E 7
	ASSERT(mutex_owned(&dp->intrlock));
D 7

E 7
I 7
#endif
E 7
	OUTW(dp, MACCtrl1, MC1_StatisticsDisable);

D 19
				x= INL(dp, OctetsRecevedOK);
				x= INL(dp, OctetsTransmittedOK);
E 19
I 19
	x =			INL(dp, OctetsRecevedOK);
	x =			INL(dp, OctetsTransmittedOK);
E 19

D 19
				x= INW(dp, FramesTransmittedOK);
				x= INW(dp, FramesReceivedOK);
E 19
I 19
	x =			INW(dp, FramesTransmittedOK);
	x =			INW(dp, FramesReceivedOK);
E 19

D 2
	dp->stats.nocarrier     += INB(dp, CarrierSenseErrors);
	dp->stats.xmtlatecoll   += INB(dp, LateCollisionss);
E 2
I 2
	dp->stats.nocarrier += c = INB(dp, CarrierSenseErrors);
	dp->stats.xmtlatecoll += l = INB(dp, LateCollisionss);
E 2
D 19
	multi_coll               = INB(dp, MultipleColFrames);
	first_coll               = INB(dp, SingleColFrames);
	dp->stats.defer         += INB(dp, FramesWDeferedXmt);
	dp->stats.missed        += INB(dp, FramesLostRxErrors);
				x= INB(dp, FramesWEXDeferral);
				x= INB(dp, FramesAbortXSClls);
				x= INB(dp, BcstFramesXmtdOK);
				x= INB(dp, BcstFramesRcvdOK);
				x= INB(dp, McstFramesXmtdOK);
				x= INB(dp, McstFramesRcvdOK);
E 19
I 19
	multi_coll =		INB(dp, MultipleColFrames);
	first_coll =		INB(dp, SingleColFrames);
	dp->stats.defer +=	INB(dp, FramesWDeferedXmt);
	dp->stats.missed +=	INB(dp, FramesLostRxErrors);
	x =			INB(dp, FramesWEXDeferral);
	x =			INB(dp, FramesAbortXSClls);
	x =			INB(dp, BcstFramesXmtdOK);
	x =			INB(dp, BcstFramesRcvdOK);
	x =			INB(dp, McstFramesXmtdOK);
	x =			INB(dp, McstFramesRcvdOK);
E 19

D 19
	dp->stats.multi_coll    += multi_coll;
	dp->stats.first_coll    += first_coll;
E 19
I 19
	dp->stats.multi_coll +=	multi_coll;
	dp->stats.first_coll +=	first_coll;
E 19

	/*
	 * Guess total collisions
	 */
D 19
	dp->stats.collisions += first_coll + multi_coll*2;
E 19
I 19
	dp->stats.collisions +=	first_coll + multi_coll*2;
E 19

I 2
	dp->stats.errxmt += c + l;

E 2
	OUTW(dp, MACCtrl1, MC1_StatisticsEnable);
I 17

	return (GEM_SUCCESS);
E 17
}

/*
D 19
 * discriptor  manupiration
E 19
I 19
 * descriptor manipulation
E 19
 */
static int
D 17
alta_tx_desc_write(struct gem_dev *dp, uint_t slot,
E 17
I 17
alta_tx_desc_write(struct gem_dev *dp, int slot,
E 17
D 19
		ddi_dma_cookie_t *dmacookie, int frags, uint32_t flag)
E 19
I 19
		ddi_dma_cookie_t *dmacookie, int frags, uint64_t flag)
E 19
{
	int			i;
	struct alta_tfd		*tfdp;
	struct alta_fragment	*tfp;
D 17
	uint32_t		tfd_dma;
E 17
	ddi_dma_cookie_t	*dcp;
	uint32_t		mark;
I 21
	uint32_t		addr;
E 21
D 8
	struct alta_chip_state	*lp = (struct alta_chip_state *)dp->private;
E 8
I 8
D 17
	struct alta_dev	*lp = (struct alta_dev *)dp->private;
I 14
	ddi_acc_handle_t	h = dp->desc_acc_handle;
E 17
I 17
D 19
	struct alta_dev		*lp = (struct alta_dev *)dp->private;
E 19
I 19
	struct alta_dev		*lp = dp->private;
I 22
	const uint_t		tx_ring_size = dp->gc.gc_tx_ring_size;
E 22
E 19
E 17
E 14
E 8

I 3
D 17
#if DEBUG_LEVEL > 3
E 17
I 17
#if DEBUG_LEVEL > 2
E 17
	/* force to cause interrupt upon tx completion */
D 8
	flag |= 1;
E 8
I 8
	flag |= GEM_TXFLAG_INTR;
E 8
#endif
E 3
D 19
	tfdp = &((struct alta_tfd *)dp->tx_ring)[slot];
E 19
I 19
	tfdp = &ALTA_TFD(dp->tx_ring)[slot];
E 19
D 22
#if DEBUG_LEVEL > 2
E 22
I 22
#if DEBUG_LEVEL > 10
E 22
D 17
	cmn_err(CE_CONT,
D 8
	"%s: alta_tx_desc_write seqnum: %d, slot %d, frags: %d flags: %d",
		dp->name, dp->tx_desc_tail, slot, frags, flags);
E 8
I 8
	"%s: alta_tx_desc_write seqnum: %d, slot %d, frags: %d flag: %d",
		dp->name, dp->tx_desc_tail, slot, frags, flag);
E 17
I 17
D 19
	cmn_err(CE_CONT, "%s: %s seqnum: %d, slot %d, frags: %d flag: %d",
		dp->name, __func__, dp->tx_desc_tail, slot, frags, flag);
E 19
I 19
	cmn_err(CE_CONT, "!%s: %s seqnum: %d, slot %d, frags: %d flag: %llx",
	    dp->name, __func__, dp->tx_desc_tail, slot, frags, flag);
E 19
E 17
E 8
	for (i = 0; i < frags; i++) {
D 19
		cmn_err(CE_CONT, "%d: addr: 0x%x, len: 0x%x",
			i, dmacookie[i].dmac_address, dmacookie[i].dmac_size);
E 19
I 19
		cmn_err(CE_CONT, "!%d: addr: 0x%x, len: 0x%x",
		    i, dmacookie[i].dmac_address, dmacookie[i].dmac_size);
E 19
	}
#endif
I 22
#if 0
E 22
D 14
	tfdp->TxDMANextPtr   = 0;	/* means this is the last descriptor */
D 11
	tfdp->TxFrameControl = 
E 11
I 11
	tfdp->TxFrameControl = LE32(
E 14
I 14
D 17
	ddi_put32(h, &tfdp->TxDMANextPtr, 0);
E 17
I 17
	tfdp->TxDMANextPtr = 0;
E 17
D 22
					/* means this is the last descriptor */
E 22
I 22
#else
	tfdp->TxDMANextPtr = dp->tx_ring_dma +
	    sizeof (struct alta_tfd) * SLOT(slot + 1, tx_ring_size);
#endif

E 22
D 17
	ddi_put32(h, &tfdp->TxFrameControl,
E 17
I 17
	mark = 0;
D 19
	if ((flag & GEM_TXFLAG_INTR) != 0) {
E 19
I 19
	if (flag & GEM_TXFLAG_INTR) {
E 19
E 17
E 14
E 11
I 3
D 4
#if 1
E 4
I 4
#ifdef USE_FRAMEID
E 4
D 8
			((flag & 1) != 0 ? TFC_TxIndicate : 0) |
E 8
I 8
D 17
			((flag & GEM_TXFLAG_INTR) != 0 ? TFC_TxIndicate : 0) |
E 17
I 17
		mark = TFC_TxIndicate;
E 17
E 8
#else
E 3
D 8
			((flag & 1) != 0 ? TFC_TxDMAIndicate : 0) |
E 8
I 8
D 17
			((flag & GEM_TXFLAG_INTR) != 0 ? TFC_TxDMAIndicate : 0)|
E 17
I 17
		mark = TFC_TxDMAIndicate;
E 17
E 8
D 3
#if DEBUG_LEVEL > 3
			TFC_TxIndicate |
E 3
#endif
I 17
	}
D 19
	tfdp->TxFrameControl = LE32(mark |
E 17
D 3
#ifdef DEBUG_LEVEL
E 3
			(TFC_FrameId & (slot << TFC_FrameIdShift)) |
D 3
#endif
E 3
D 11
			TFC_WordAlignDisable;
E 11
I 11
			TFC_WordAlignDisable);
E 19
I 19
D 21
	tfdp->TxFrameControl = LE_32(
	    mark | (TFC_FrameId & (slot << TFC_FrameIdShift)) |
	    TFC_WordAlignDisable);
E 21
I 21
	mark |=
#ifdef USE_FRAMEID
	    (TFC_FrameId & (slot << TFC_FrameIdShift)) |
#endif
	    TFC_WordAlignDisable;
	tfdp->TxFrameControl = LE_32(mark);
E 21
E 19
E 11

	/* copy fragment list */
	mark = TFD_TxDMAFragLast; /* last fragment */
D 19
	for (i = frags-1, dcp = &dmacookie[i], tfp = &tfdp->TxDMAFrag[i];
			i >= 0;
				dcp--, tfp--, i--, mark = 0) {
D 11
		tfp->Len  = dcp->dmac_size | mark;
		tfp->Addr = dcp->dmac_address;
E 11
I 11
D 14
		tfp->Len  = LE32(dcp->dmac_size | mark);
		tfp->Addr = LE32(dcp->dmac_address);
E 14
I 14
D 17
		ddi_put32(h, &tfp->Len, dcp->dmac_size | mark);
		ddi_put32(h, &tfp->Addr, dcp->dmac_address);
E 17
I 17
		tfp->Len  = LE32(dcp->dmac_size | mark);
		tfp->Addr = LE32(dcp->dmac_address);
E 19
I 19
	i = frags - 1;
	dcp = &dmacookie[i];
	tfp = &tfdp->TxDMAFrag[i];
	for (; i >= 0; dcp--, tfp--, i--) {
D 21
		tfp->Len = LE_32(dcp->dmac_size | mark);
		tfp->Addr = LE_32(dcp->dmac_address);
E 21
I 21
		mark |= dcp->dmac_size;
		tfp->Len = LE_32(mark);
		addr = dcp->dmac_address;
		tfp->Addr = LE_32(addr);
E 21
		mark = 0;
E 19
E 17
E 14
E 11
	}
I 3
D 8
#ifdef IOCACHE
E 8
I 8

E 8
D 17
	ddi_dma_sync(dp->desc_dma_handle,
		(off_t)(((caddr_t)tfdp) - dp->rx_ring),
		sizeof(struct alta_tfd), DDI_DMA_SYNC_FORDEV);
E 17
I 17
	return (1);
}
E 17
D 8
#endif
E 8
E 3

D 17
	/* link it into the hardware tx list */
	tfd_dma = dp->tx_ring_dma + ((caddr_t)tfdp - (caddr_t)dp->tx_ring);
E 17
I 17
static void
alta_tx_start(struct gem_dev *dp, int start_slot, int nslot)
{
	int		slot;
	uint32_t	tfd_dma;
D 19
	struct alta_dev	*lp = (struct alta_dev *)dp->private;
E 19
I 19
	struct alta_dev	*lp = dp->private;
I 22
	const uint_t	tx_ring_size = dp->gc.gc_tx_ring_size;
E 22
E 19
E 17

D 4
	ASSERT((tfd_dma & 7 ) == 0);
E 4
I 4
D 17
	ASSERT((tfd_dma & 7) == 0);
E 17
I 17
D 19
	if (lp->tx_list_loaded)  {
		/*
		 * fix the specified tx list due to link it to the tail
		 * of current tx descriptor list.
		 */
		start_slot = SLOT(start_slot - 1, TX_RING_SIZE);
		nslot++;
	}
E 19
I 19
D 22
	slot = SLOT(start_slot + nslot - 1, TX_RING_SIZE);
E 22
I 22
	slot = SLOT(start_slot + nslot - 1, tx_ring_size);
E 22
	tfd_dma = dp->tx_ring_dma + sizeof (struct alta_tfd) * slot;
E 19
E 17
E 4

I 17
D 19
	slot    = SLOT(start_slot + nslot - 1, TX_RING_SIZE);
	tfd_dma = dp->tx_ring_dma + sizeof(struct alta_tfd) * slot;

	/* make tx list */
E 19
I 19
	/* make new tx list */
I 22
#if 0
E 22
E 19
	while (slot != start_slot) {
I 19
		/* get the index of the previous slot */
E 19
D 22
		slot = SLOT(slot - 1, TX_RING_SIZE);
E 22
I 22
		slot = SLOT(slot - 1, tx_ring_size);
E 22
D 19
		((struct alta_tfd *) dp->tx_ring)[slot].TxDMANextPtr
							= LE_32(tfd_dma);
		tfd_dma = dp->tx_ring_dma + sizeof(struct alta_tfd) * slot;
E 19
I 19

		/* link me to the previous */
		ALTA_TFD(dp->tx_ring)[slot].TxDMANextPtr = LE_32(tfd_dma);

		/* update current descriptor address in dma space */
		tfd_dma = dp->tx_ring_dma + sizeof (struct alta_tfd) * slot;
E 19
	}
D 22

E 22
I 22
#else
	/* terminate the tx list */
	slot = SLOT(start_slot + nslot - 1, tx_ring_size);
	ALTA_TFD(dp->tx_ring)[slot].TxDMANextPtr = 0;
#endif
E 22
	/* flush tx descriptors in the tx list we have made */
	gem_tx_desc_dma_sync(dp, start_slot, nslot, DDI_DMA_SYNC_FORDEV);

E 17
D 15
#ifdef TXTIMEOUT_TEST
	alta_send_cnt++;
	if (alta_send_cnt > 100) {
E 15
I 15
#ifdef TEST_TXTIMEOUT
	if ((lp->send_cnt++ % 10000) == 9999) {
E 15
		OUTW(dp, MACCtrl1, MC1_TxDisable);
D 15
	} else
E 15
I 15
	}
E 15
#endif
D 17
	if (lp->tx_list_loaded)  {
E 17
I 17
D 19
	if (!lp->tx_list_loaded)  {
E 19
I 19
	if (lp->tx_list_loaded)  {
E 19
E 17
D 11
		/* Link this to the previous slot and kick Tx engine */
		if (slot == 0) {
			tfdp = &((struct alta_tfd *)dp->tx_ring)[TX_RING_SIZE];
		}
		tfdp--;
		tfdp->TxDMANextPtr = tfd_dma;
E 11
I 11
		/*
I 19
		 * Link the new list to the tail of current tx descriptor.
		 */
D 22
		slot = SLOT(start_slot - 1, TX_RING_SIZE);
E 22
I 22
		slot = SLOT(start_slot - 1, tx_ring_size);
E 22
		ALTA_TFD(dp->tx_ring)[slot].TxDMANextPtr = LE_32(tfd_dma);
		gem_tx_desc_dma_sync(dp, slot, 1, DDI_DMA_SYNC_FORDEV);
	} else {
		/*
E 19
D 17
		 * Link this to the previous slot. The previous isn't in use,
		 * because number of tx buffers is smaller than the number of
		 * tx descriptors.
		 */
		tfdp = &((struct alta_tfd *)dp->tx_ring)[
D 14
						SLOT(slot - 1,TX_RING_SIZE)];
		tfdp->TxDMANextPtr = LE32(tfd_dma);
E 14
I 14
						SLOT(slot - 1, TX_RING_SIZE)];
		ddi_put32(h, &tfdp->TxDMANextPtr, tfd_dma);
E 14
E 11
I 3
D 8
#ifdef IOCACHE
E 8
I 8

E 8
		ddi_dma_sync(dp->desc_dma_handle,
			(off_t)(((caddr_t)tfdp) - dp->rx_ring),
			sizeof(struct alta_tfd), DDI_DMA_SYNC_FORDEV);
D 8
#endif
E 8
I 8
D 11
#ifdef notdef
E 8
E 3
		OUTW(dp, MACCtrl1, MC1_TxEnable);
I 8
#endif
E 11
E 8
	}
	else {
D 11
		/* Treat this as head of new tx list, tell to nic */
E 11
I 11
		/*
E 17
		 * This is first call after initialization.
		 * Need to tell the head of tx list to the nic.
		 */
E 11
		OUTL(dp, TxDMAListPtr, tfd_dma);
D 17
		lp->tx_list_loaded = TRUE;
E 17
I 17
		lp->tx_list_loaded = B_TRUE;
E 17
	}
D 17

	return 1;
E 17
}

D 17
static int
alta_rx_desc_write(struct gem_dev *dp, uint_t slot,
E 17
I 17
static void
alta_rx_desc_write(struct gem_dev *dp, int slot,
E 17
	    ddi_dma_cookie_t *dmacookie, int frags)
{
	int			i;
	struct alta_rfd		*rfdp;
	struct alta_fragment	*rfp;
	ddi_dma_cookie_t	*dcp;
	uint32_t		len;
	uint32_t		n;
I 14
D 17
	ddi_acc_handle_t	h = dp->desc_acc_handle;
E 17
I 17
	uint32_t		mark;
I 21
	uint32_t		addr;
E 21
E 17
E 14

D 19
	rfdp = &((struct alta_rfd *)dp->rx_ring)[slot];
E 19
I 19
	rfdp = &ALTA_RFD(dp->rx_ring)[slot];
E 19

D 22
#if DEBUG_LEVEL > 2
E 22
I 22
#if DEBUG_LEVEL > 10
E 22
D 19
	cmn_err(CE_CONT, "%s: alta_rx_desc_write seqnum: %d, slot %d, frags: %d",
D 17
		dp->name, dp->rx_desc_tail, slot, frags);
E 17
I 17
		dp->name, dp->rx_active_tail, slot, frags);
E 19
I 19
	cmn_err(CE_CONT, "!%s: %s seqnum: %d, slot %d, frags: %d",
	    dp->name, __func__, dp->rx_active_tail, slot, frags);
E 19
E 17
	for (i = 0; i < frags; i++) {
D 19
		cmn_err(CE_CONT, "  frag: %d addr: 0x%x, len: 0x%x",
			i, dmacookie[i].dmac_address, dmacookie[i].dmac_size);
E 19
I 19
		cmn_err(CE_CONT, "!  frag: %d addr: 0x%x, len: 0x%x",
		    i, dmacookie[i].dmac_address, dmacookie[i].dmac_size);
E 19
	}
#endif

D 21
	/* copy fragment list */
E 21
I 21
	/* copy fragment list in reversed order */
E 21
D 17
	for (len = 0, i = frags-1, dcp = dmacookie, rfp = rfdp->RxDMAFrag;
			i--; dcp++, rfp++) {
D 11
		len += rfp->Len = (uint32_t)dcp->dmac_size;
		rfp->Addr = (uint32_t)dcp->dmac_address;
E 11
I 11
		len += n = (uint32_t)dcp->dmac_size;
D 14
		rfp->Len  = LE32(n);
		rfp->Addr = LE32((uint32_t)dcp->dmac_address);
E 14
I 14
		ddi_put32(h, &rfp->Len, n);
		ddi_put32(h, &rfp->Addr, (uint32_t)dcp->dmac_address);
E 14
E 11
	}
D 11
	/* for mark last fragment */
E 11
I 11
	/* for last fragment */
E 11
	len += n = (uint32_t)dcp->dmac_size;
D 11
	rfp->Len = n | RFD_RxDMALastFrag;
	rfp->Addr = (uint32_t)dcp->dmac_address;
E 11
I 11
D 14
	rfp->Len  = LE32(n | RFD_RxDMALastFrag);
	rfp->Addr = LE32((uint32_t)dcp->dmac_address);
E 14
I 14
	ddi_put32(h, &rfp->Len, n | RFD_RxDMALastFrag);
	ddi_put32(h, &rfp->Addr, (uint32_t)dcp->dmac_address);
E 17
I 17
	len = 0;
D 19
	i   = frags-1;
E 19
I 19
	i = frags - 1;
E 19
	dcp = &dmacookie[i];
	rfp = &rfdp->RxDMAFrag[i];
	mark = RFD_RxDMALastFrag;
D 19
	for (;i >= 0; i--, dcp--, rfp--) {
		len += (n = (uint32_t) dcp->dmac_size);
E 19
I 19
	for (; i >= 0; i--, dcp--, rfp--) {
D 21
		len += (n = (uint32_t)dcp->dmac_size);
E 19
		n |= mark;
		rfp->Addr = LE_32(dcp->dmac_address);
D 19
		rfp->Len  = LE_32(n);
E 19
I 19
		rfp->Len = LE_32(n);
E 21
I 21
		n = (uint32_t)dcp->dmac_size;
		len += n;
		mark |= n;
		addr = dcp->dmac_address;
		rfp->Addr = LE_32(addr);
		rfp->Len = LE_32(mark);
E 21
E 19
E 17
E 14
E 11

D 11
	rfdp->RxFrameStatus = len;
E 11
I 11
D 14
	rfdp->RxFrameStatus = LE32(len);
E 14
I 14
D 17
	ddi_put32(h, &rfdp->RxFrameStatus, len);
E 14
E 11
I 3
D 8
#ifdef IOCACHE
E 8
I 8

E 8
	ddi_dma_sync(dp->desc_dma_handle,
		(off_t)(((caddr_t)rfdp) - dp->rx_ring),
		sizeof(struct alta_rfd), DDI_DMA_SYNC_FORDEV);
D 8
#endif
E 8
E 3

	return 1;
E 17
I 17
		mark = 0;
	}
	rfdp->RxFrameStatus = LE_32(len);
E 17
}

static uint_t
alta_tx_desc_stat(struct gem_dev *dp, int slot, int ndesc)
{
	struct alta_tfd		*tfdp;
I 3
D 19
	int			frameid;
E 19
I 19
	uint32_t		frameid;
E 19
I 11
	uint32_t		tfc;
I 14
D 17
	ddi_acc_handle_t	h = dp->desc_acc_handle;
E 17
E 14
E 11
E 3

D 19
	tfdp = &((struct alta_tfd *)dp->tx_ring)[slot];
E 19
I 19
	tfdp = &ALTA_TFD(dp->tx_ring)[slot];
E 19
D 3

E 3
I 3
#ifdef USE_FRAMEID
	frameid = (INW(dp, TxStatus) & TS_TxFrameId) >> TS_TxFrameIdShift;
	if (slot == frameid + 1) {
D 17
		return 0;
E 17
I 17
		return (0);
E 17
	}
	if (slot == frameid) {
D 8
#ifdef IOCACHE
E 8
D 17
		ddi_dma_sync(dp->desc_dma_handle,
			(off_t)(((caddr_t)tfdp) - dp->rx_ring),
			sizeof(struct alta_tfd), DDI_DMA_SYNC_FORKERNEL);
I 11
D 14
		tfc = LE32(tfdp->TxFrameControl);
E 14
I 14
		tfc = ddi_get32(h, &tfdp->TxFrameControl);
E 17
I 17
D 19
		tfc = LE32(tfdp->TxFrameControl);
E 19
I 19
D 21
		tfc = LE_32(tfdp->TxFrameControl);
E 21
I 21
		tfc = tfdp->TxFrameControl;
		tfc = LE_32(tfc);
E 21
E 19
E 17
E 14
E 11
D 8
#endif
E 8
I 8

E 8
D 11
		if ((tfdp->TxFrameControl & TFC_TxDMAComplete) == 0) {
E 11
I 11
		if ((tfc & TFC_TxDMAComplete) == 0) {
E 11
			/* not transmitted */
D 17
			return 0;
E 17
I 17
			return (0);
E 17
		}
	}
#else
D 8
#ifdef IOCACHE
E 8
D 17
	ddi_dma_sync(dp->desc_dma_handle,
		(off_t)(((caddr_t)tfdp) - dp->rx_ring),
		sizeof(struct alta_tfd), DDI_DMA_SYNC_FORKERNEL);
E 17
I 17
D 19
	tfc = LE32(tfdp->TxFrameControl);
E 19
I 19
D 21
	tfc = LE_32(tfdp->TxFrameControl);
E 21
I 21
	tfc = tfdp->TxFrameControl;
	tfc = LE_32(tfc);
E 21
E 19
E 17
D 8
#endif
E 3
	/* Ack to interrupt */
	OUTW(dp, IntStatus, INT_TxDMAComplete);
E 8

I 11
D 14
	tfc = LE32(tfdp->TxFrameControl);
E 14
I 14
D 17
	tfc = ddi_get32(h, &tfdp->TxFrameControl);
E 14

E 17
E 11
D 19
	DPRINTF(2, (CE_CONT,
		"%s: alta_tx_desc_stat: slot:%d, tfs:0x%b",
D 11
		dp->name, slot, tfdp->TxFrameControl, TFC_BITS));
E 11
I 11
		dp->name, slot, tfc, TFC_BITS));
E 19
I 19
	DPRINTF(2, (CE_CONT, "!%s: %s: slot:%d, tfs:0x%b",
	    dp->name, __func__, slot, tfc, TFC_BITS));
E 19
E 11

D 11
	if ((tfdp->TxFrameControl & TFC_TxDMAComplete) == 0) {
E 11
I 11
	if ((tfc & TFC_TxDMAComplete) == 0) {
E 11
		/* not transmitted */
D 17
		return 0;
E 17
I 17
		return (0);
E 17
	}
D 3

E 3
I 3
#endif
E 3
D 17
	return GEM_TX_DONE;
E 17
I 17
	return (GEM_TX_DONE);
E 17
}

D 16
static uint_t
E 16
I 16
static uint64_t
E 16
alta_rx_desc_stat(struct gem_dev *dp, int slot, int ndesc)
{
	struct alta_rfd		*rfdp;
D 14
	uint_t		rfs;
	uint_t		len;
	uint_t		flag;
E 14
I 14
D 19
	uint_t			rfs;
	uint_t			len;
	uint_t			flag;
E 19
I 19
	uint32_t		rfs;
	uint32_t		len;
	uint32_t		flag;
E 19
D 17
	ddi_acc_handle_t	h = dp->desc_acc_handle;
E 17
E 14

D 19
	rfdp = &((struct alta_rfd *)dp->rx_ring)[slot];
E 19
I 19
	rfdp = &ALTA_RFD(dp->rx_ring)[slot];
E 19
I 3
D 8
#ifdef IOCACHE
E 8
I 8

E 8
D 17
	ddi_dma_sync(dp->desc_dma_handle,
		(off_t)(((caddr_t)rfdp) - dp->rx_ring),
		sizeof(struct alta_rfd), DDI_DMA_SYNC_FORKERNEL);
D 8
#endif
E 8
E 3

D 8
	/* Ack to interrupt */
	OUTW(dp, IntStatus, INT_RxDMAComplete | INT_MACControlFrame);

E 8
D 11
	rfs  = rfdp->RxFrameStatus;
E 11
I 11
D 14
	rfs  = LE32(rfdp->RxFrameStatus);
E 14
I 14
	rfs  = ddi_get32(h, &rfdp->RxFrameStatus);
E 17
I 17
D 19
	rfs  = LE32(rfdp->RxFrameStatus);
E 17
E 14
E 11
	len  = rfs & RFS_RxDMAFrameLen;
E 19
I 19
D 21
	rfs = LE_32(rfdp->RxFrameStatus);
E 21
I 21
	rfs = rfdp->RxFrameStatus;
	rfs = LE_32(rfs);
E 21
	len = rfs & RFS_RxDMAFrameLen;
E 19
	flag = GEM_RX_DONE;

D 19
	DPRINTF(2, (CE_CONT,
		"%s: alta_rx_desc_stat: slot:%d, rfs:0x%b",
D 11
		dp->name, slot, rfdp->RxFrameStatus, RFS_BITS));
E 11
I 11
		dp->name, slot, rfs, RFS_BITS));
E 19
I 19
	DPRINTF(2, (CE_CONT, "!%s: %s: slot:%d, rfs:0x%b",
	    dp->name, __func__, slot, rfs, RFS_BITS));
E 19
E 11

	if ((rfs & RFS_RxDMAComplete) == 0) {
		/* not received */
D 17
		return 0;
E 17
I 17
		return (0);
E 17
	}

D 19
	if ((rfs & RFS_ERRORS) != 0) {
E 19
I 19
	if (rfs & RFS_ERRORS) {
E 19
		/* error packet */
		dp->stats.errrcv++;
D 19
		if ((rfs & (RFS_RxAlignmentError
				| RFS_RxFrameError)) != 0) {
E 19
I 19
		if (rfs & (RFS_RxAlignmentError | RFS_RxFrameError)) {
E 19
			dp->stats.frame++;
		}
D 19
		if ((rfs & RFS_RxFIFOOverrun) != 0) {
E 19
I 19
		if (rfs & RFS_RxFIFOOverrun) {
E 19
			dp->stats.overflow++;
		}
D 19
		if ((rfs & RFS_RxRuntFrame) != 0) {
E 19
I 19
		if (rfs & RFS_RxRuntFrame) {
E 19
			dp->stats.runt++;
		}
D 19
		if ((rfs & RFS_RxFCSError) != 0) {
E 19
I 19
		if (rfs & RFS_RxFCSError) {
E 19
			dp->stats.crc++;
		}
D 17
		if ((rfs & (RFS_RxDMAOverflow | RFS_RxOversizedFrame))
								!= 0) {
E 17
I 17
D 19
		if ((rfs & (RFS_RxDMAOverflow | RFS_RxOversizedFrame)) != 0) {
E 19
I 19
		if (rfs & (RFS_RxDMAOverflow | RFS_RxOversizedFrame)) {
E 19
E 17
			dp->stats.frame_too_long++;
		}

		flag = GEM_RX_ERR;
	}

D 17
	return flag | len;
E 17
I 17
	return (flag | len);
E 17
}

static void
alta_tx_desc_init(struct gem_dev *dp, int slot)
{
D 19
	struct alta_tfd		*tfdp;

	tfdp = &((struct alta_tfd *)dp->tx_ring)[slot];
I 17
	tfdp->TxFrameControl = LE32(TFC_TxDMAComplete);
E 19
I 19
	ALTA_TFD(dp->tx_ring)[slot].TxFrameControl = LE_32(TFC_TxDMAComplete);
E 19
E 17
}

static void
alta_rx_desc_init(struct gem_dev *dp, int slot)
{
D 21
	int			i;
E 21
I 21
	int		i;
	uint32_t	ptr;
E 21
	struct alta_rfd		*rfdp;
I 14
D 17
	ddi_acc_handle_t	h = dp->desc_acc_handle;
E 17
E 14

D 19
	rfdp = &((struct alta_rfd *)dp->rx_ring)[slot];
E 19
I 19
	rfdp = &ALTA_RFD(dp->rx_ring)[slot];
E 19

	/* invalidate this rfd */
D 11
	rfdp->RxFrameStatus = RFS_RxDMAComplete;
E 11
I 11
D 14
	rfdp->RxFrameStatus = LE32(RFS_RxDMAComplete);
E 14
I 14
D 17
	ddi_put32(h, &rfdp->RxFrameStatus, RFS_RxDMAComplete);
E 17
I 17
D 19
	rfdp->RxFrameStatus = LE32(RFS_RxDMAComplete);
E 19
I 19
	rfdp->RxFrameStatus = LE_32(RFS_RxDMAComplete);
E 19
E 17
E 14
E 11
I 3
D 8
#ifdef IOCACHE
E 8
I 8

E 8
D 17
	ddi_dma_sync(dp->desc_dma_handle,
		(off_t)(((caddr_t)rfdp) - dp->rx_ring),
		sizeof(struct alta_rfd), DDI_DMA_SYNC_FORDEV);
D 8
#endif
E 8
E 3

E 17
D 11
	/* link to previous rfd */
	if (slot == 0) {
		rfdp = &((struct alta_rfd *)dp->rx_ring)[RX_RING_SIZE];
	}
	(--rfdp)->RxDMANextPtr = 
		((uint32_t)dp->rx_ring_dma) + slot*sizeof(struct alta_rfd);
E 11
I 11
	/* link it to the previous rfd */
D 19
	rfdp = &((struct alta_rfd *)dp->rx_ring)[SLOT(slot - 1, RX_RING_SIZE)];
D 14
	rfdp->RxDMANextPtr = 
		LE32(((uint32_t)dp->rx_ring_dma)+slot*sizeof(struct alta_rfd));
E 14
I 14
D 17
	ddi_put32(h, &rfdp->RxDMANextPtr,
E 17
I 17
	rfdp->RxDMANextPtr = LE32(
E 17
		((uint32_t)dp->rx_ring_dma)+slot*sizeof(struct alta_rfd));
E 19
I 19
D 22
	rfdp = &ALTA_RFD(dp->rx_ring)[SLOT(slot - 1, RX_RING_SIZE)];
E 22
I 22
	rfdp = &ALTA_RFD(dp->rx_ring)[SLOT(slot - 1, dp->gc.gc_rx_ring_size)];
E 22
D 21
	rfdp->RxDMANextPtr =
	    LE_32(((uint32_t)dp->rx_ring_dma) + slot*sizeof (struct alta_rfd));
E 21
I 21
	ptr = ((uint32_t)dp->rx_ring_dma) + slot * sizeof (struct alta_rfd);
	rfdp->RxDMANextPtr = LE_32(ptr);
E 21
E 19
E 14
E 11
I 3
D 8
#ifdef IOCACHE
E 8
I 8
D 17

E 8
	ddi_dma_sync(dp->desc_dma_handle,
		(off_t)(((caddr_t)rfdp) - dp->rx_ring),
		sizeof(struct alta_rfd), DDI_DMA_SYNC_FORDEV);
E 17
D 8
#endif
E 8
E 3
}

static void
alta_tx_desc_clean(struct gem_dev *dp, int slot)
{
I 3
	struct alta_tfd		*tfdp;
I 14
D 17
	ddi_acc_handle_t	h = dp->desc_acc_handle;
E 17
E 14

D 19
	tfdp = &((struct alta_tfd *)dp->tx_ring)[slot];
E 19
I 19
	tfdp = &ALTA_TFD(dp->tx_ring)[slot];

	tfdp->TxDMANextPtr = 0;
	tfdp->TxFrameControl = LE_32(TFC_TxDMAComplete);
E 19
I 8
D 17

E 8
E 3
	/* do nothing */
I 3
D 8
#ifdef IOCACHE
E 8
	ddi_dma_sync(dp->desc_dma_handle,
		(off_t)(((caddr_t)tfdp) - dp->rx_ring),
		sizeof(struct alta_tfd), DDI_DMA_SYNC_FORKERNEL);
E 17
D 8
#endif
E 8
E 3
}

static void
alta_rx_desc_clean(struct gem_dev *dp, int slot)
{
D 19
	struct alta_rfd		*rfdp;
I 14
D 17
	ddi_acc_handle_t	h = dp->desc_acc_handle;
E 17
E 14

	rfdp = &((struct alta_rfd *)dp->rx_ring)[slot];
I 3
D 8
#ifdef IOCACHE
E 8
I 8
D 14

E 14
I 14
D 17
#ifdef notdef
E 14
E 8
	ddi_dma_sync(dp->desc_dma_handle,
		(off_t)(((caddr_t)rfdp) - dp->rx_ring),
		sizeof(struct alta_rfd), DDI_DMA_SYNC_FORKERNEL);
D 8
#endif
E 8
E 3
D 14

E 14
I 14
#endif
E 14
	/* invalidate this rfd */
D 11
	rfdp->RxFrameStatus = RFS_RxDMAComplete;
E 11
I 11
D 14
	rfdp->RxFrameStatus = LE32(RFS_RxDMAComplete);
E 14
I 14
	ddi_put32(h, &rfdp->RxFrameStatus, RFS_RxDMAComplete);
E 17
E 14
E 11
I 3
D 8
#ifdef IOCACHE
E 8
I 8

E 19
E 8
D 17
	ddi_dma_sync(dp->desc_dma_handle,
		(off_t)(((caddr_t)rfdp) - dp->rx_ring),
		sizeof(struct alta_rfd), DDI_DMA_SYNC_FORDEV);
E 17
I 17
	/* invalidate this rfd */
D 19
	rfdp->RxFrameStatus = LE_32(RFS_RxDMAComplete);
E 19
I 19
	ALTA_RFD(dp->rx_ring)[slot].RxFrameStatus = LE_32(RFS_RxDMAComplete);
E 19
E 17
D 8
#endif
E 8
E 3
}

/*
 * Device depend interrupt handler
 */
D 22
static boolean_t
E 22
I 22
static void
E 22
alta_get_tx_status(struct gem_dev  *dp)
{
	int		error = 0;
	int		restart_xmit;
	uint16_t	tx_status;
	int		i;
I 5
D 8
	struct alta_chip_state	*lp = (struct alta_chip_state *)dp->private;
E 8
I 8
D 19
	struct alta_dev	*lp = (struct alta_dev *)dp->private;
E 19
I 19
	struct alta_dev	*lp = dp->private;
E 19
E 8
E 5

D 22
	ASSERT(mutex_owned(&dp->intrlock));

	/* Pop all status from  the Tx status stack. */
E 22
I 22
	/* Pop all status from the Tx status stack. */
E 22
D 19
	while (((tx_status = INW(dp, TxStatus)) & TS_TxComplete) != 0) {
E 19
I 19
	while ((tx_status = INW(dp, TxStatus)) & TS_TxComplete) {
E 19

		/* Discard one */
		OUTW(dp, TxStatus, 0);

D 19
		if ((tx_status & TS_TxReleaseError) != 0) {
E 19
I 19
		if (tx_status & TS_TxReleaseError) {
E 19
			cmn_err(CE_WARN,
D 19
			    "%s: tx release error: tx_status: %b",
E 19
I 19
			    "!%s: tx release error: tx_status: %b",
E 19
			    dp->name, tx_status, TS_BITS);
		}

D 19
		if ((tx_status & TS_TxStatusOverflow) != 0) {
E 19
I 19
		if (tx_status & TS_TxStatusOverflow) {
E 19
			cmn_err(CE_WARN,
D 19
			    "%s: tx status overflow: tx_status: %b",
E 19
I 19
			    "!%s: tx status overflow: tx_status: %b",
E 19
			    dp->name, tx_status, TS_BITS);
		}

		/* update statistics */
D 19
		if ((tx_status & TS_TxUnderrun) != 0) {
E 19
I 19
		if (tx_status & TS_TxUnderrun) {
E 19
			/* fifo underflow. TxReset and TxEnable are required */
			cmn_err(CE_WARN,
D 19
			    "%s: tx underrun error: tx_status: %b",
E 19
I 19
			    "!%s: tx underrun error: tx_status: %b",
E 19
			    dp->name, tx_status, TS_BITS);
			dp->stats.underflow++;
			dp->stats.errxmt++;
		}

D 19
		if ((tx_status & TS_MaxCollisions) != 0) {
E 19
I 19
		if (tx_status & TS_MaxCollisions) {
E 19
			/* exceed maximum collisions */
			dp->stats.excoll++;
			dp->stats.collisions += 16;
			dp->stats.errxmt++;
		}

		/* collect status bits */
		error |= (tx_status &
		    (TS_TxReleaseError | TS_TxUnderrun | TS_MaxCollisions));
	}

	mutex_enter(&dp->xmitlock);

D 19
	if (error != 0) {
		if ((error & (TS_TxReleaseError | TS_TxUnderrun)) != 0) {
E 19
I 19
	if (error) {
		if (error & (TS_TxReleaseError | TS_TxUnderrun)) {
E 19
D 5

			DPRINTF(1, (CE_CONT, "!alta_get_tx_status: dmactrl: %b",
				INL(dp, DMACtrl), DC_BITS));

			/* wait for tx fifo free */
			dp->nic_active = FALSE;
			while (dp->tx_busy) {
				cv_wait(&dp->drain_cv, &dp->xmitlock);
			}

E 5
I 5
			/* FATAL error */
#ifdef notdef
I 8
			/* XXX - the nic has stopped */
E 8
E 5
I 3
			OUTW(dp, MACCtrl1, MC1_TxDisable);
D 5
			drv_usecwait(1000);

E 3
			OUTL(dp, AsicCtrl, AC_TxReset);

			drv_usecwait(10);
			i = 0;
			while ((INL(dp, AsicCtrl) & AC_ResetBusy) != 0) {
D 3
				if (i++>100) {
E 3
I 3
				if (i++>5000) {
E 3
					/* TxReset timeout */
					break;
				}
				drv_usecwait(10);
E 5
I 5
#endif
D 17
			lp->need_to_reset = TRUE;
E 17
I 17
			lp->need_to_reset = B_TRUE;
E 17
D 19
			if ((error & TS_TxUnderrun) != 0) {
E 19
I 19
			if (error & TS_TxUnderrun) {
E 19
D 8
				/* modify tx threashold */
E 8
I 8
				/* increase tx threashold by 64 byte */
E 8
				dp->txthr = min(dp->txthr+64, ETHERMAX);
E 5
			}
D 19
		}
I 5
		else {
			if ((error & TS_MaxCollisions) != 0) {
E 19
I 19
		} else {
			if (error & TS_MaxCollisions) {
E 19
				OUTW(dp, MACCtrl1, MC1_StatisticsEnable);
			}
E 5

D 5
		if ((error & TS_MaxCollisions) != 0) {
			OUTW(dp, MACCtrl1, MC1_StatisticsEnable);
E 5
I 5
D 19
			OUTW(dp, MACCtrl1, MC1_TxEnable); 
E 19
I 19
			OUTW(dp, MACCtrl1, MC1_TxEnable);
E 19
E 5
		}
D 5

		OUTW(dp, MACCtrl1, MC1_TxEnable); 
		dp->nic_active = TRUE;
E 5
	}

D 22
	/*
	 * kick someone who waits for enough space in TX fifo
	 */
	restart_xmit = dp->tx_blocked;
E 22
	mutex_exit(&dp->xmitlock);
D 22

D 17
	return restart_xmit;
E 17
I 17
	return (restart_xmit);
E 22
E 17
}


D 19
static u_int
E 19
I 19
static uint_t
E 19
alta_interrupt(struct gem_dev *dp)
{
	uint16_t	int_status;
D 11
	boolean_t	tx_sched = FALSE;
E 11
I 11
D 19
	u_int		tx_sched = 0;
E 11
I 4
D 15
	int		loop;
E 15
I 5
D 8
	struct alta_chip_state	*lp = (struct alta_chip_state *)dp->private;
E 8
I 8
	struct alta_dev	*lp = (struct alta_dev *)dp->private;
E 19
I 19
	uint_t		tx_sched = 0;
	struct alta_dev	*lp = dp->private;
E 19
E 8
E 5
E 4

I 8
D 11
#ifdef MAP_MEM
E 11
E 8
	/*
I 8
D 11
	 * Acknowledge to the interrupt.
	 * Reading IntStatusAck clears both of IntStatus and IntEnable
	 */
	int_status = INW(dp, IntStatusAck);
#else
	/*
E 11
E 8
	 * Read interrupt status
D 3
	 * Caution: Do not use IntStatusAck. It's funny.
E 3
I 3
	 * Do not use IntStatusAck here. It clears IntEnable too.
E 3
	 */
	int_status = INW(dp, IntStatus);
I 8
D 11
#endif
E 11
I 11

E 11
E 8
D 15
	if ((int_status & OUR_INTR_BITS) == 0) {
E 15
I 15
	if ((int_status & lp->intmask) == 0) {
E 15
		/* Not for us */
I 8
D 11
#ifdef MAP_MEM
		/* recover the interrupt mask */
		OUTL(dp, IntEnable, lp->intmask);
#endif
E 11
E 8
D 17
		return DDI_INTR_UNCLAIMED;
E 17
I 17
		return (DDI_INTR_UNCLAIMED);
E 17
	}

I 8
D 11
#ifndef MAP_MEM
E 11
E 8
I 3
D 5
#ifdef notdef
E 5
E 3
	/*
	 * Acknowledge to the interrupt.
D 5
	 * Mask interrupt signal first, because PCI bus recognize
	 * interrupts by edge-triggered method.
E 5
I 5
	 * Reading IntStatusAck clears both of IntStatus and IntEnable
E 5
	 */
D 5
	OUTW(dp, IntEnable, 0);
	OUTW(dp, IntStatus, int_status);
D 3

E 3
I 3
#else
	/* Reading IntStatusAck clears both of IntStatus and IntEnable */
E 5
	int_status = INW(dp, IntStatusAck);
D 5
#endif
E 5
E 3
D 8
	DPRINTF(2, (CE_CONT, "%s: Interrupt, int_status: %b",
E 8
I 8
D 11
#endif
E 11
D 19
	DPRINTF(2, (CE_CONT, "%s: alta_interrupt, int_status: %b",
E 8
			   dp->name, int_status, INT_BITS));
E 19
I 19
	DPRINTF(3, (CE_CONT, "!%s: %s, int_status: %b",
	    dp->name, __func__, int_status, INT_BITS));
E 19
D 17
	if (!dp->nic_active) {
E 17
I 17
	if (!dp->mac_active) {
E 17
		/*
		 * the device is not active.
		 * side effect: left interrupt masked.
		 */
I 19
		lp->intmask = 0;
E 19
D 17
		return DDI_INTR_CLAIMED;
E 17
I 17
		return (DDI_INTR_CLAIMED);
E 17
	}

I 4
D 15
	loop = 100;
E 4
	do {
		if ((int_status & INT_UpdateStats) != 0) {
			/*
			 * Statistics counter overflow
			 */
			alta_get_stats(dp);
		}
E 15
I 15
D 17
#ifdef CONFIG_POLLING
E 17
I 17
#ifdef GEM_CONFIG_POLLING
E 17
D 19
	if (dp->speed == GEM_SPD_100 &&
	    dp->poll_interval != lp->last_poll_interval) {
		if (dp->poll_interval != 0) {
E 19
I 19
	int_status &= lp->intmask | INT_RxDMAComplete;

	if (dp->poll_interval != lp->last_poll_interval) {
		if (dp->poll_interval) {
E 19
			/* move to polling mode */
			lp->intmask &= ~INT_RxDMAComplete;
D 17
			lp->countdown = (dp->poll_interval *  10) / 32;
			lp->countdown = min(lp->countdown, 0xffff);
E 17
I 17
D 19
#ifdef CONFIG_TX_COALEASCE
			lp->intmask &= ~INT_TxDMAComplete;
			dp->tx_coalesce = B_TRUE;
#endif
			lp->countdown = min(dp->poll_interval, 0xffff);
E 17
E 15

D 11
		if ((int_status & (INT_RxDMAComplete | INT_MACControlFrame)) != 0) {
E 11
I 11
D 15
		if ((int_status &
			(INT_RxDMAComplete | INT_MACControlFrame)) != 0) {
E 11
			/*
			 * packet was received, or receive error happened
			 */
			gem_receive(dp);
E 15
I 15
			if (lp->last_poll_interval == 0) {
				/*
				 * To schedule the next timer interrupt,
				 * we pretend as we were interrupted from
				 * polling timer
				 */
				int_status |= INT_IntRequest;
			}
E 15
		}
I 15
		else {
E 19
I 19
			lp->countdown = min(dp->poll_interval/1250, 0xffff);
		} else {
E 19
			/* move to normal mode */
			lp->intmask |= INT_RxDMAComplete;
E 15
D 17

E 17
I 17
D 19
#ifdef CONFIG_TX_COALEASCE
			lp->intmask |= INT_TxDMAComplete;
			dp->tx_coalesce = B_FASLE;
#endif
E 19
I 19

E 19
E 17
D 15
		if ((int_status & INT_TxComplete) != 0) {
			/*
			 * Pull up TxStatus
			 */
D 11
			if (alta_get_tx_status(dp)) {
				tx_sched = TRUE;
			}
E 11
I 11
			(void) alta_get_tx_status(dp);
E 15
I 15
			/* use countdown timer for tx timeout */
D 17
			lp->countdown = 5000;
E 17
I 17
			lp->countdown = 0;
E 17
E 15
E 11
		}
I 19
		/*
		 * To schedule the next timer interrupt,
		 * we pretend as we were interrupted from
		 * polling timer
		 */
		int_status |= INT_IntRequest;
E 19
I 15
	}
	lp->last_poll_interval = dp->poll_interval;
I 19
#else
	int_status &= lp->intmask;
E 19
D 17
#endif /* CONFIG_POLLING */
E 17
I 17
#endif /* GEM_CONFIG_POLLING */
E 17
E 15

D 3
		if ((int_status & INT_TxDMAComplete) != 0) {
E 3
I 3
D 4
		if ((int_status & (INT_TxComplete | INT_TxDMAComplete)) != 0) {
E 4
I 4
D 15
		if ((int_status & INT_TxDMAComplete) != 0) {
E 4
E 3
			/*
D 11
			 * Packets was transfered into TxFIFO or error happened
E 11
I 11
			 * Packets was transfered into TxFIFO or
			 * an error happened.
E 11
			 */
I 8
D 11
#ifdef notdef
E 11
E 8
			if (gem_tx_done(dp)) {
D 11
				tx_sched = TRUE;
E 11
I 11
				tx_sched |= INTR_RESTART_TX;
E 11
			}
E 15
I 15
D 19
	if ((int_status & INT_IntRequest) != 0) {
E 19
I 19
	if (int_status & INT_IntRequest) {
E 19
		/*
		 * re-load Countdown timer to schedule the next polling
		 * timer interrupt.
		 */
		OUTW(dp, Countdown, lp->countdown);
D 17
#ifdef CONFIG_POLLING
E 17
I 17
D 19
#ifdef GEM_CONFIG_POLLING
E 17
		if (dp->poll_interval > 0) {
			/* force to process rx */
			int_status |= INT_RxDMAComplete;
E 15
I 8
D 11
#else
			mutex_enter(&dp->xmitlock);
			if (dp->tx_blocked) {
				tx_sched = TRUE;
			}
			mutex_exit(&dp->xmitlock);
#endif
E 11
E 8
		}
I 15
D 17
#endif /* CONFIG_POLLING */
E 17
I 17
#endif /* GEM_CONFIG_POLLING */
E 19
E 17
	}
E 15

D 15
		if ((int_status &
			(INT_RxEarly | INT_IntRequest | INT_HostError)) != 0) {
			cmn_err(CE_WARN, "%s: unexpected interrupt: %b",
				dp->name, int_status, INT_BITS);
E 15
I 15
D 19
	if ((int_status & INT_UpdateStats) != 0) {
E 19
I 19
	if (int_status & INT_UpdateStats) {
E 19
		/*
		 * Statistics counter overflow
		 */
		alta_get_stats(dp);
	}

D 19
	if ((int_status & (INT_RxDMAComplete | INT_MACControlFrame)) != 0) {
E 19
I 19
	if (int_status & (INT_RxDMAComplete | INT_MACControlFrame)) {
E 19
		/*
		 * packet was received, or receive error happened
		 */
D 21
		gem_receive(dp);
E 21
I 21
		(void) gem_receive(dp);
E 21
	}

D 19
	if ((int_status & INT_TxComplete) != 0) {
E 19
I 19
	if (int_status & INT_TxComplete) {
E 19
		/*
		 * Pull up TxStatus
		 */
		(void) alta_get_tx_status(dp);
	}

D 19
	if ((int_status &
		(INT_TxComplete | INT_TxDMAComplete | INT_IntRequest)) != 0) {
E 19
I 19
	if (int_status & (INT_TxComplete | INT_TxDMAComplete)) {
E 19
		/*
		 * Packets was transfered into TxFIFO or
		 * an error happened.
		 */
		if (gem_tx_done(dp)) {
			tx_sched |= INTR_RESTART_TX;
E 15
		}
D 8

		int_status = INW(dp, IntStatus);
E 8
I 8
D 15
		int_status = INW(dp, IntStatusAck);
E 8
D 4
	} while ((int_status & OUR_INTR_BITS) != 0);
E 4
I 4
	} while ((int_status & OUR_INTR_BITS) != 0 && --loop > 0);
E 15
I 15
	}
E 15
E 4

I 5
D 15
	if (loop <= 0) {
		DPRINTF(0, (CE_WARN, "%s maximum interrupt loop exceeded",
			dp->name));
E 15
I 15
D 19
	if ((int_status & INT_LinkEvent) != 0) {
		DPRINTF(0, (CE_CONT, "%s: %s link event",
D 16
			dp->name, __FUNCTION__));
E 16
I 16
			dp->name, __func__));
E 19
I 19
	if (int_status & INT_LinkEvent) {
		DPRINTF(0, (CE_CONT, "!%s: %s link event",
		    dp->name, __func__));
E 19
E 16
D 18
		(void) gem_mii_link_check(dp);
E 18
I 18
		if (gem_mii_link_check(dp)) {
			tx_sched |= INTR_RESTART_TX;
		}
E 18
E 15
	}

I 15
D 19
	if ((int_status & (INT_RxEarly |
E 19
I 19
	if (int_status & (INT_RxEarly |
E 19
D 17
#ifndef CONFIG_POLLING
E 17
I 17
#ifndef GEM_CONFIG_POLLING
E 17
D 19
			   INT_IntRequest |
E 19
I 19
	    INT_IntRequest |
E 19
#endif
D 19
			   INT_HostError)) != 0) {
		cmn_err(CE_WARN, "%s: unexpected interrupt: %b",
			dp->name, int_status, INT_BITS);
E 19
I 19
	    INT_HostError)) {
		cmn_err(CE_WARN, "!%s: unexpected interrupt: %b",
		    dp->name, int_status, INT_BITS);
E 19
	}

E 15
	if (lp->need_to_reset) {
D 17
		mutex_enter(&dp->xmitlock);
D 16
		gem_restart_tx(dp);
E 16
I 16
		gem_restart_nic(dp, TRUE);
E 16
		mutex_exit(&dp->xmitlock);
E 17
I 17
D 19
		gem_restart_nic(dp, B_TRUE);
E 19
I 19
		gem_restart_nic(dp, GEM_RESTART_KEEP_BUF);
E 19
E 17
D 11
		tx_sched = TRUE;
E 11
I 11
		tx_sched = INTR_RESTART_TX;
E 11
D 17
		lp->need_to_reset = FALSE;
E 17
I 17
		lp->need_to_reset = B_FALSE;
E 17
	}

E 5
	/*
	 * Recover Interrput Enable register
	 */
D 19
	DPRINTF(4, (CE_CONT, "%s: alta_inter done: int_status: %b",
			   dp->name, INW(dp, IntStatus), INT_BITS));
E 19
I 19
	DPRINTF(4, (CE_CONT, "!%s: %s done: int_status: %b",
	    dp->name, __func__, INW(dp, IntStatus), INT_BITS));
E 19
D 4
	OUTW(dp, IntEnable, OUR_INTR_BITS);

E 4
I 4
D 11
	if ((dp->misc_flag & GEM_NOINTR) == 0) {
E 11
I 11
D 15
	if ((dp->misc_flag & GEM_NOINTR) == 0 && loop > 0) {
E 11
I 8
		lp->intmask = OUR_INTR_BITS;
E 8
		OUTW(dp, IntEnable, OUR_INTR_BITS);
E 15
I 15

	if ((dp->misc_flag & GEM_NOINTR) == 0) {
		OUTW(dp, IntEnable, lp->intmask);
E 15
	}
I 15

E 15
E 4
D 11
	return DDI_INTR_CLAIMED | (tx_sched ? INTR_RESTART_TX : 0);
E 11
I 11
D 17
	return DDI_INTR_CLAIMED | tx_sched;
E 17
I 17
	return (DDI_INTR_CLAIMED | tx_sched);
E 17
E 11
}

/*
 * HW depend MII routine
 */
D 19
#define MDIO_DELAY(dp)    {INB(dp, PhyCtrl);INB(dp, PhyCtrl);}
E 19
I 19
#define	MDIO_DELAY(dp)    {INB(dp, PhyCtrl); INB(dp, PhyCtrl); }
E 19

static void
alta_mii_sync(struct gem_dev *dp)
{
	int	i;

	/* output 32 ones */
	for (i = 0; i < 32; i++) {
		OUTB(dp, PhyCtrl, PC_MgmtDir | PC_MgmtData);
		MDIO_DELAY(dp);
		OUTB(dp, PhyCtrl, PC_MgmtDir | PC_MgmtData | PC_MgmtClk);
		MDIO_DELAY(dp);
	}
D 17
	OUTB(dp, PhyCtrl, PC_MgmtDir | PC_MgmtData);
E 17
}

static uint16_t
D 15
alta_mii_read(struct gem_dev *dp, int reg)
E 15
I 15
alta_mii_read(struct gem_dev *dp, uint_t reg)
E 15
{
	uint32_t	cmd;
	uint16_t	ret;
	int		i;
	uint8_t		data;

I 3
D 5
#ifdef CONFIG_DFE580TX
	alta_mii_sync(dp);
#endif
E 5
E 3
	cmd = MII_READ_CMD(dp->mii_phy_addr, reg);

D 5
	OUTB(dp, PhyCtrl, PC_MgmtDir | PC_MgmtData);
	MDIO_DELAY(dp);
	OUTB(dp, PhyCtrl, PC_MgmtDir | PC_MgmtData | PC_MgmtClk);

E 5
	for (i = 31; i >= 18; i--) {
		data = ((cmd >> i) & 1) <<  PC_MgmtDataShift;
		OUTB(dp, PhyCtrl, data | PC_MgmtDir);
		MDIO_DELAY(dp);
		OUTB(dp, PhyCtrl, data | PC_MgmtDir | PC_MgmtClk);
		MDIO_DELAY(dp);
	}
I 5
	/* turn around */
	OUTB(dp, PhyCtrl, 0);
	MDIO_DELAY(dp);
E 5

D 5
	for (i = 17; i >= 0; i--) {
E 5
I 5
	/* get response from PHY */
	OUTB(dp, PhyCtrl, PC_MgmtClk);
	MDIO_DELAY(dp);
	OUTB(dp, PhyCtrl, 0);
D 19
	if ((INB(dp, PhyCtrl) & PC_MgmtData) != 0) {
		DPRINTF(1, (CE_CONT, "%s: no response from phy@%d",
			dp->name, dp->mii_phy_addr));
E 19
I 19
	if (INB(dp, PhyCtrl) & PC_MgmtData) {
		DPRINTF(1, (CE_CONT, "!%s: no response from phy@%d",
		    dp->name, dp->mii_phy_addr));
E 19
	}

	OUTB(dp, PhyCtrl, PC_MgmtClk);
	MDIO_DELAY(dp);

	for (i = 16; i > 0; i--) {
E 5
		OUTB(dp, PhyCtrl, 0);
D 5
		MDIO_DELAY(dp);
E 5
		ret = (ret << 1) | ((INB(dp, PhyCtrl) >> PC_MgmtDataShift) & 1);
		OUTB(dp, PhyCtrl, PC_MgmtClk);
		MDIO_DELAY(dp);
	}
D 5
	OUTB(dp, PhyCtrl, 0);
E 5

I 5
	/* send two 1s to phy */
	for (i = 0; i < 2; i++) {
		OUTB(dp, PhyCtrl, PC_MgmtDir | PC_MgmtData);
		MDIO_DELAY(dp);
		OUTB(dp, PhyCtrl, PC_MgmtDir | PC_MgmtData | PC_MgmtClk);
		MDIO_DELAY(dp);
	}
D 17
	OUTB(dp, PhyCtrl, PC_MgmtDir | PC_MgmtData);
E 17

E 5
D 17
	return ret;
E 17
I 17
	return (ret);
E 17
}

static void
D 15
alta_mii_write(struct gem_dev *dp, int reg, uint16_t val)
E 15
I 15
D 17
alta_mii_write_raw(struct gem_dev *dp, uint_t reg, uint16_t val)
E 17
I 17
alta_mii_write(struct gem_dev *dp, uint_t reg, uint16_t val)
E 17
E 15
{
	uint32_t	cmd;
	int		i;
	uint8_t		data;

I 3
D 5
#ifdef CONFIG_DFE580TX
	alta_mii_sync(dp);
#endif
E 5
E 3
	cmd = MII_WRITE_CMD(dp->mii_phy_addr, reg, val);

D 5
	OUTB(dp, PhyCtrl, PC_MgmtDir | PC_MgmtData);
	MDIO_DELAY(dp);
	OUTB(dp, PhyCtrl, PC_MgmtDir | PC_MgmtData | PC_MgmtClk);

E 5
	for (i = 31; i >= 0; i--) {
		data = ((cmd >> i) & 1) << PC_MgmtDataShift;
		OUTB(dp, PhyCtrl, data | PC_MgmtDir);
		MDIO_DELAY(dp);
		OUTB(dp, PhyCtrl, data | PC_MgmtDir | PC_MgmtClk);
		MDIO_DELAY(dp);
	}

I 5
	/* send two 1s to phy */
E 5
	for (i = 0; i < 2; i++) {
D 5
		OUTB(dp, PhyCtrl, 0);
E 5
I 5
		OUTB(dp, PhyCtrl, PC_MgmtDir | PC_MgmtData);
E 5
		MDIO_DELAY(dp);
D 5
		OUTB(dp, PhyCtrl, PC_MgmtClk);
E 5
I 5
		OUTB(dp, PhyCtrl, PC_MgmtDir  | PC_MgmtData | PC_MgmtClk);
E 5
		MDIO_DELAY(dp);
	}
D 5
	OUTB(dp, PhyCtrl, 0);
E 5
I 5
D 17
	OUTB(dp, PhyCtrl, PC_MgmtDir | PC_MgmtData);
E 17
E 5
}
I 15
D 17

static void
alta_mii_write(struct gem_dev *dp, uint_t reg, uint16_t val)
{
	alta_mii_write_raw(dp, reg, val);

	if (reg == MII_CONTROL && (val & MII_CONTROL_RESET) != 0) {
		/* emulate write-self-clear on RESET bit */
		drv_usecwait(300000);
		alta_mii_write_raw(dp, reg, val & ~MII_CONTROL_RESET);
	}
}
E 17
E 15
#undef MDIO_DELAY

I 22
static int
alta_mii_probe(struct gem_dev *dp)
{
	int	ret;
	uint32_t	val;

	ret = gem_mii_probe_default(dp);
	if (ret == GEM_SUCCESS) {
		val = INL(dp, AsicCtrl);
		if (val & AC_PhyMedia) {
			/*
			 * workaround for fibre interface.
			 * we need to disable autonego by default.
			 */
			dp->mii_status &= ~MII_STATUS_CANAUTONEG;
			dp->mii_status |= MII_STATUS_100_BASEX_FD;
		}
	}
	return (ret);
}

E 22
/* ======================================================== */
/*
 * OS depend (device driver) routine
 */
/* ======================================================== */
static int
altaattach(dev_info_t *dip, ddi_attach_cmd_t cmd)
{
	int			i;
I 9
	int			n;
E 9
D 16
	ddi_iblock_cookie_t	c;
E 16
	ddi_acc_handle_t	conf_handle;
D 16
	uint16_t		comm;
	int			ret;
E 16
	int			vid;
	int			did;
I 16
	uint8_t			revid;
	uint8_t			lat;
E 16
D 8
	int			svid;
	int			ssid;
E 8
	int			unit;
D 16
	struct chip_info	*p;
	int			val;
	int			len;
	struct pci_phys_spec	*regs;
E 16
	const char		*drv_name;
I 16
	struct chip_info	*p;
E 16
	struct gem_dev		*dp;
D 8
	struct alta_chip_state		*lp;
E 8
I 8
	struct alta_dev		*lp;
E 8
	void			*base;
D 16
	ddi_acc_handle_t	regs_handle;
E 16
I 16
	ddi_acc_handle_t	regs_ha;
E 16
D 5
	struct gem_conf		gc;
E 5
I 5
	struct gem_conf		*gcp;
E 5
I 3
D 16
	uint8_t			revid;
I 11
	uint8_t			lat;
E 16
E 11
E 3

D 19
	unit =  ddi_get_instance(dip);
E 19
I 19
	unit = ddi_get_instance(dip);
E 19
	drv_name = ddi_driver_name(dip);

D 19
	DPRINTF(3, (CE_CONT, "%s%d: altaattach: called", drv_name, unit));
E 19
I 19
	DPRINTF(3, (CE_CONT, "!%s%d: %s: called", drv_name, unit, __func__));
E 19

D 16
	if (cmd == DDI_ATTACH) {
E 16
I 16
	/*
	 * Check if chip is supported.
	 */
	if (pci_config_setup(dip, &conf_handle) != DDI_SUCCESS) {
D 19
		cmn_err(CE_WARN, "%s: ddi_regs_map_setup failed",
			drv_name);
E 19
I 19
		cmn_err(CE_WARN, "!%s: ddi_regs_map_setup failed",
		    drv_name);
E 19
		goto err;
	}
E 16

D 16
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
D 8
		svid = pci_config_get16(conf_handle, PCI_CONF_SUBVENID);
		ssid = pci_config_get16(conf_handle, PCI_CONF_SUBSYSID);
E 8
I 3
		revid= pci_config_get8(conf_handle, PCI_CONF_REVID);
E 3
		comm = pci_config_get16(conf_handle, PCI_CONF_COMM);
I 11
		lat  = pci_config_get8(conf_handle, PCI_CONF_LATENCY_TIMER);
E 11
		comm |= PCI_COMM_IO | PCI_COMM_ME;
		pci_config_put16(conf_handle, PCI_CONF_COMM, comm);
E 16
I 16
D 19
	vid  = pci_config_get16(conf_handle, PCI_CONF_VENID);
	did  = pci_config_get16(conf_handle, PCI_CONF_DEVID);
	revid= pci_config_get8(conf_handle, PCI_CONF_REVID);
	lat  = pci_config_get8(conf_handle, PCI_CONF_LATENCY_TIMER);
E 19
I 19
	vid = pci_config_get16(conf_handle, PCI_CONF_VENID);
	did = pci_config_get16(conf_handle, PCI_CONF_DEVID);
	revid = pci_config_get8(conf_handle, PCI_CONF_REVID);
	lat = pci_config_get8(conf_handle, PCI_CONF_LATENCY_TIMER);
E 19
E 16

D 16
		pci_config_teardown(&conf_handle);

		for (i = 0, p = alta_chiptbl; i < CHIPTABLESIZE; i++, p++) {
D 8
			if ((p->venid == vid && p->devid == did) ||
			    (p->venid == svid && p->devid == ssid)) {
E 8
I 8
			if (p->venid == vid && p->devid == did) {
E 8
				/* found */
I 3
				cmn_err(CE_CONT,
D 11
			"!%s%d: %s (vid: 0x%04x, did: 0x%04x, revid: 0x%02x)",
				drv_name, unit, p->name, vid, did, revid);
E 11
I 11
"!%s%d: %s (vid: 0x%04x, did: 0x%04x, revid: 0x%02x, latency timer: 0x%02x)",
				drv_name, unit, p->name, vid, did, revid, lat);
E 11
E 3
				goto chip_found;
			}
E 16
I 16
	for (i = 0, p = alta_chiptbl; i < CHIPTABLESIZE; i++, p++) {
		if (p->venid == vid && p->devid == did) {
			/* found */
			goto chip_found;
E 16
		}
I 16
	}
E 16

D 16
		/* Not found */
		cmn_err(CE_WARN,
			"%s: alta_attach: wrong PCI venid/devid (0x%x, 0x%x)",
			drv_name, vid, did);
		goto err;
E 16
I 16
	/* Not found */
D 18
	cmn_err(CE_WARN,
		"%s: alta_attach: wrong PCI venid/devid (0x%x, 0x%x)",
		drv_name, vid, did);
	pci_config_teardown(&conf_handle);
	goto err;
E 18
I 18
D 19
	cmn_err(CE_NOTE, "%s%d: %s: unknown PCI venid/devid (0x%x, 0x%x)",
		drv_name, unit, __func__, vid, did);
E 19
I 19
	cmn_err(CE_NOTE, "!%s%d: %s: unknown PCI venid/devid (0x%x, 0x%x)",
	    drv_name, unit, __func__, vid, did);
E 19
	/* assume ST201/IP100 chipset */
	p = &alta_chiptbl[0];
	/* fall down */
E 18

E 16
chip_found:
D 16
		/*
		 * Map in the device registers.
		 */
E 16
I 16
	/* ensure the pmr status is D0 mode */
	(void) gem_pci_set_power_state(dip, conf_handle, PCI_PMCSR_D0);
E 16

D 16
		/* Search IO-range or memory-range to be mapped */
		regs = NULL;
		len  = 0;
I 9
D 11
#ifdef OBSOLUTE_DDI_GETPROP
E 9
		if (ddi_getlongprop(DDI_DEV_T_ANY, dip, DDI_PROP_DONTPASS,
			"reg", (caddr_t)&regs, &len) != DDI_PROP_SUCCESS) {
			cmn_err(CE_WARN,
				"%s: failed to get reg property", drv_name);
			goto err;
		}
I 9
		n = len / sizeof(sizeof(struct pci_phys_spec);
#else
E 11
		if (ddi_prop_lookup_int_array(
			DDI_DEV_T_ANY, dip, DDI_PROP_DONTPASS,
			"reg", (int **)&regs, &len) != DDI_PROP_SUCCESS) {
E 16
I 16
	pci_config_put16(conf_handle, PCI_CONF_COMM,
D 19
		PCI_COMM_IO | PCI_COMM_MAE | PCI_COMM_ME |
			pci_config_get16(conf_handle, PCI_CONF_COMM));
E 19
I 19
	    PCI_COMM_IO | PCI_COMM_MAE | PCI_COMM_ME |
	    pci_config_get16(conf_handle, PCI_CONF_COMM));
E 19
E 16
E 9

I 9
D 16
			cmn_err(CE_WARN,
			"%s%d: failed to get reg property", drv_name, unit);
			goto err;
		}
		n = len / (sizeof(struct pci_phys_spec) / sizeof(int));
E 16
I 16
	pci_config_teardown(&conf_handle);
E 16
D 11
#endif
E 11
I 11

E 11
E 9
D 16
		ASSERT(regs != NULL && len > 0);
#if DEBUG_LEVEL > 0
D 9
		for (i = 0; i <len / sizeof(struct pci_phys_spec); i++) {
E 9
I 9
		for (i = 0; i < n; i++) {
E 9
			cmn_err(CE_CONT,
D 3
				"!%s: regs[%d]: %08x.%08x.%08x.%08x.%08x",
				drv_name, i,
E 3
I 3
				"!%s%d: regs[%d]: %08x.%08x.%08x.%08x.%08x",
				drv_name, unit, i,
E 3
				regs[i].pci_phys_hi,
				regs[i].pci_phys_mid,
				regs[i].pci_phys_low,
				regs[i].pci_size_hi,
				regs[i].pci_size_low);
		}
#endif
D 9
		for (i = 0; i <len / sizeof(struct pci_phys_spec); i++) {
E 9
I 9
		for (i = 0; i < n; i++) {
E 9
			if ((regs[i].pci_phys_hi & PCI_REG_ADDR_M) == 
E 16
I 16
	cmn_err(CE_CONT,
D 19
"!%s%d: %s (vid: 0x%04x, did: 0x%04x, revid: 0x%02x, latency timer: 0x%02x)",
		drv_name, unit, p->name, vid, did, revid, lat);
E 19
I 19
	    "!%s%d: %s (vid: 0x%04x, did: 0x%04x,"
	    " revid: 0x%02x, latency timer: 0x%02x)",
	    drv_name, unit, p->name, vid, did, revid, lat);
E 19

	switch (cmd) {
	case DDI_RESUME:
D 17
		return gem_resume(dip);
E 17
I 17
		return (gem_resume(dip));
E 17

	case DDI_ATTACH:
		if (gem_pci_regs_map_setup(dip,
E 16
D 5
			    PCI_ADDR_IO) {
E 5
I 5
#ifdef MAP_MEM
D 16
			    PCI_ADDR_MEM32
E 16
I 16
D 17
			PCI_ADDR_MEM32,
E 17
I 17
D 19
			PCI_ADDR_MEM32, PCI_ADDR_MASK,
E 19
I 19
		    PCI_ADDR_MEM32, PCI_ADDR_MASK,
E 19
E 17
E 16
#else
D 16
			    PCI_ADDR_IO
E 16
I 16
D 17
			PCI_ADDR_IO,
E 17
I 17
D 19
			PCI_ADDR_IO, PCI_ADDR_MASK,
E 19
I 19
		    PCI_ADDR_IO, PCI_ADDR_MASK,
E 19
E 17
E 16
#endif
D 16
			) {
E 5
				/* it's I/O space */
I 9
D 11
#ifdef OBSOLUTE_DDI_GETPROP
E 9
				kmem_free(regs, len);
I 9
#else
E 11
				ddi_prop_free(regs);
D 11
#endif
E 11
E 9
D 5
				goto io_range_found;
E 5
I 5
				goto map_space_found;
E 5
			}
		}
I 5
#ifdef MAP_MEM
		cmn_err(CE_WARN, "%s: failed to find MEM32 space", drv_name);
#else
E 5
		cmn_err(CE_WARN, "%s: failed to find IO space", drv_name);
I 5
#endif
I 9
D 11
#ifdef OBSOLUTE_DDI_GETPROP
E 9
E 5
		kmem_free(regs, len);
I 9
#else
E 11
		ddi_prop_free(regs);
D 11
#endif
E 11
E 9
		goto err;
D 5
io_range_found:
E 5
I 5
map_space_found:
E 5

		if (ddi_regs_map_setup(dip, i, (caddr_t *)&base,
D 3
			0, 0, &alta_chip_state_attr, &regs_handle)) {
E 3
I 3
			0, 0, &alta_dev_attr, &regs_handle)) {
E 3
			cmn_err(CE_WARN, "%s: ddi_regs_map_setup failed",
				drv_name);
E 16
I 16
D 19
			&alta_dev_attr, (caddr_t *)&base, &regs_ha)
					!= DDI_SUCCESS) {
E 19
I 19
D 20
		    &alta_dev_attr, (caddr_t *)&base, &regs_ha)
E 20
I 20
		    &alta_dev_attr, (void *)&base, &regs_ha)
E 20
		    != DDI_SUCCESS) {
E 19
E 16
			goto err;
		}
I 16

E 16
		/*
I 16
D 17
		/*
E 17
E 16
		 * construct gem configration
		 */
D 5
		bzero(&gc, sizeof(gc));
E 5
I 5
D 19
		gcp = (struct gem_conf *) kmem_zalloc(sizeof(*gcp), KM_SLEEP);
E 19
I 19
		gcp = kmem_zalloc(sizeof (*gcp), KM_SLEEP);
E 19
E 5

		/* name */
D 5
		sprintf(gc.gc_name, "%s%d", drv_name, unit);
E 5
I 5
		sprintf(gcp->gc_name, "%s%d", drv_name, unit);
E 5

		/* consistency on tx and rx */
D 5
		gc.gc_tx_buf_align = 0;
		gc.gc_tx_max_frags = MAXTXFRAGS;
		gc.gc_tx_desc_size = sizeof(struct alta_tfd) * TX_RING_SIZE;
		gc.gc_tx_ring_size = TX_RING_SIZE;
		gc.gc_tx_buf_size  = TX_RING_SIZE;
		gc.gc_tx_max_descs_per_pkt = 1;
		gc.gc_tx_auto_pad  = TRUE;
		gc.gc_tx_copy_thresh = alta_tx_copy_thresh;
E 5
I 5
D 11
		gcp->gc_tx_buf_align = 0;
E 11
I 11
D 19
		gcp->gc_tx_buf_align = sizeof(uint8_t) - 1;
E 19
I 19
		gcp->gc_tx_buf_align = sizeof (uint8_t) - 1;
E 19
E 11
		gcp->gc_tx_max_frags = MAXTXFRAGS;
D 17
		gcp->gc_tx_desc_size = sizeof(struct alta_tfd) * TX_RING_SIZE;
E 17
I 17
D 19
		gcp->gc_tx_desc_unit_shift = 6; /* 64 byte */
E 19
I 19
		gcp->gc_tx_desc_unit_shift =
		    alta_log2(sizeof (struct alta_tfd));
E 19
E 17
		gcp->gc_tx_ring_size = TX_RING_SIZE;
D 11
		gcp->gc_tx_buf_size  = TX_RING_SIZE;
E 11
I 11
D 17

		/* 
		 * XXX - bug fixed 2004/12/06
		 * Number of tx buffers must be less than TX RING SIZE,
		 * aka the number of tx descriptors, because we cannot use all
		 * tx descriptors at the same time.
D 14
		 * We need one to point the head of tx descriptor list.
		 * This is tricky.
E 14
I 14
D 16
		 * We need another descriptor which points the head of tx
E 16
I 16
		 * We must reserve a descriptor which points the head of tx
E 16
		 * descriptor list. This is tricky.
E 14
		 */ 
E 17
I 17
		gcp->gc_tx_ring_limit = gcp->gc_tx_ring_size - 1;
E 17
D 15
		gcp->gc_tx_buf_size  = TX_RING_SIZE - 1;
E 11
		gcp->gc_tx_max_descs_per_pkt = 1;
E 15
I 15
D 19
		gcp->gc_tx_buf_size  = TX_BUF_SIZE;
E 19
I 19
		gcp->gc_tx_buf_size = TX_BUF_SIZE;
E 19
D 17

		/* XXX - reserve one to point the actual head of tx list */
		gcp->gc_tx_max_descs_per_pkt = 2;
E 15
		gcp->gc_tx_auto_pad  = TRUE;
E 17
I 17
D 22
		gcp->gc_tx_buf_limit = gcp->gc_tx_buf_size - 1;
E 22
I 22
		gcp->gc_tx_buf_limit = gcp->gc_tx_buf_size;
E 22
		gcp->gc_tx_max_descs_per_pkt = 1;
D 19
		gcp->gc_tx_auto_pad  = B_TRUE;
E 19
I 19
		gcp->gc_tx_auto_pad = B_TRUE;
E 19
E 17
		gcp->gc_tx_copy_thresh = alta_tx_copy_thresh;
I 17
D 21
		gcp->gc_tx_desc_write_oo = B_TRUE;
E 21
E 17
E 5

D 5
		gc.gc_rx_buf_align = 0;
		gc.gc_rx_max_frags = MAXRXFRAGS;
		gc.gc_rx_desc_size = sizeof(struct alta_rfd) * RX_RING_SIZE;
		gc.gc_rx_ring_size = RX_RING_SIZE;
		gc.gc_rx_buf_size  = RX_RING_SIZE;
		gc.gc_rx_max_descs_per_pkt = 1;
		gc.gc_rx_copy_thresh = alta_rx_copy_thresh;
		gc.gc_rx_buf_max  = 10*RX_RING_SIZE;
E 5
I 5
D 11
		gcp->gc_rx_buf_align = 0;
E 11
I 11
D 19
		gcp->gc_rx_buf_align = sizeof(uint8_t) - 1;
E 19
I 19
		gcp->gc_rx_buf_align = sizeof (uint8_t) - 1;
E 19
E 11
		gcp->gc_rx_max_frags = MAXRXFRAGS;
D 17
		gcp->gc_rx_desc_size = sizeof(struct alta_rfd) * RX_RING_SIZE;
E 17
I 17
D 19
		gcp->gc_rx_desc_unit_shift = 5;		/* 32 byte */
E 19
I 19
		gcp->gc_rx_desc_unit_shift =
		    alta_log2(sizeof (struct alta_rfd));
E 19
E 17
		gcp->gc_rx_ring_size = RX_RING_SIZE;
D 15
		gcp->gc_rx_buf_size  = RX_RING_SIZE;
E 15
I 15
D 17
		gcp->gc_rx_buf_size  = RX_BUF_SIZE;

		/*
		 * XXX - no need to reserve one to point to the head of rx
		 * buffers bacause they can be consist of a ring. 
		 * RxDMAComplete bit in RCF take a role of valid bit.
		 */
E 15
		gcp->gc_rx_max_descs_per_pkt = 1;
E 17
I 17
D 19
		gcp->gc_rx_buf_max   = RX_BUF_SIZE;
E 19
I 19
		gcp->gc_rx_buf_max = RX_BUF_SIZE;
E 19
E 17
		gcp->gc_rx_copy_thresh = alta_rx_copy_thresh;
D 17
		gcp->gc_rx_buf_max  = gcp->gc_rx_buf_size + 1;
E 17
E 5

I 17
		gcp->gc_io_area_size = 0;

E 17
		/* map attributes */
D 3
		gc.gc_dev_attr = alta_chip_state_attr;
		gc.gc_buf_attr = alta_chip_state_attr;
E 3
I 3
D 5
		gc.gc_dev_attr  = alta_dev_attr;
		gc.gc_buf_attr  = alta_buf_attr;
		gc.gc_desc_attr = alta_dev_attr;
E 5
I 5
D 10
		gcp->gc_dev_attr  = alta_dev_attr;
		gcp->gc_buf_attr  = alta_buf_attr;
		gcp->gc_desc_attr = alta_dev_attr;
E 10
I 10
D 17
		STRUCT_COPY(gcp->gc_dev_attr, alta_dev_attr);
		STRUCT_COPY(gcp->gc_buf_attr, alta_buf_attr);
D 11
		STRUCT_COPY(gcp->gc_desc_attr, alta_dev_attr);
E 11
I 11
D 14
		STRUCT_COPY(gcp->gc_desc_attr, alta_buf_attr);
E 14
I 14
		STRUCT_COPY(gcp->gc_desc_attr, alta_dev_attr);
E 17
I 17
		gcp->gc_dev_attr = alta_dev_attr;
		gcp->gc_buf_attr = alta_buf_attr;
		gcp->gc_desc_attr = alta_buf_attr;
E 17
E 14
E 11
E 10
E 5
E 3

		/* dma attributes */
D 5
		gc.gc_dma_attr_desc  = alta_dma_attr_nosc;
		gc.gc_dma_attr_txbuf = alta_dma_attr_txbuf;
		if (gc.gc_rx_max_frags > 1) {
			gc.gc_dma_attr_rxbuf = alta_dma_attr_rxbuf;
E 5
I 5
D 10
		gcp->gc_dma_attr_desc  = alta_dma_attr_nosc;
		gcp->gc_dma_attr_txbuf = alta_dma_attr_txbuf;
E 10
I 10
D 11
		STRUCT_COPY(gcp->gc_dma_attr_desc, alta_dma_attr_nosc);
		STRUCT_COPY(gcp->gc_dma_attr_txbuf, alta_dma_attr_txbuf);
E 10
		if (gcp->gc_rx_max_frags > 1) {
D 10
			gcp->gc_dma_attr_rxbuf = alta_dma_attr_rxbuf;
E 10
I 10
			STRUCT_COPY(gcp->gc_dma_attr_rxbuf,alta_dma_attr_rxbuf);
E 10
E 5
		} else {
D 5
			ASSERT(gc.gc_rx_max_frags == 1);
			gc.gc_dma_attr_rxbuf = alta_dma_attr_nosc;
E 5
I 5
			ASSERT(gcp->gc_rx_max_frags == 1);
D 10
			gcp->gc_dma_attr_rxbuf = alta_dma_attr_nosc;
E 10
I 10
			STRUCT_COPY(gcp->gc_dma_attr_rxbuf, alta_dma_attr_nosc);
E 10
E 5
		}
E 11
I 11
D 17
		STRUCT_COPY(gcp->gc_dma_attr_desc, alta_dma_attr_desc);
I 14

E 14
		STRUCT_COPY(gcp->gc_dma_attr_txbuf, alta_dma_attr_buf);
I 14
		gcp->gc_dma_attr_txbuf.dma_attr_align = gcp->gc_tx_buf_align;
E 17
I 17
		gcp->gc_dma_attr_desc = alta_dma_attr_desc;
		gcp->gc_dma_attr_txbuf = alta_dma_attr_buf;
		gcp->gc_dma_attr_txbuf.dma_attr_align = gcp->gc_tx_buf_align+1;
E 17
E 14
		gcp->gc_dma_attr_txbuf.dma_attr_sgllen = gcp->gc_tx_max_frags;
I 14
D 17

E 14
		STRUCT_COPY(gcp->gc_dma_attr_rxbuf, alta_dma_attr_buf);
I 14
		gcp->gc_dma_attr_rxbuf.dma_attr_align = gcp->gc_rx_buf_align;
E 17
I 17
		gcp->gc_dma_attr_rxbuf = alta_dma_attr_buf;
		gcp->gc_dma_attr_rxbuf.dma_attr_align = gcp->gc_rx_buf_align+1;
E 17
E 14
		gcp->gc_dma_attr_rxbuf.dma_attr_sgllen = gcp->gc_rx_max_frags;
E 11

		/* time out parameters */
D 5
		gc.gc_tx_timeout = 2*ONESEC;
		gc.gc_tx_timeout_interval = ONESEC;
E 5
I 5
D 17
		gcp->gc_tx_timeout = 5*ONESEC;
		gcp->gc_tx_timeout_interval = ONESEC;
E 17
I 17
D 21
		gcp->gc_tx_timeout = GEM_TX_TIMEOUT;
		gcp->gc_tx_timeout_interval = GEM_TX_TIMEOUT_INTERVAL;
E 21
I 21
D 22
		gcp->gc_tx_timeout = 3*ONESEC;
		gcp->gc_tx_timeout_interval = ONESEC;
E 22
I 22
		gcp->gc_tx_timeout = GEM_TX_TIMEOUT;
		gcp->gc_tx_timeout_interval = GEM_TX_TIMEOUT_INTERVAL;
E 22
E 21
E 17
E 5

		/* flow control */
D 5
		gc.gc_flow_control = TRUE;
E 5
I 5
D 12
		gcp->gc_flow_control = TRUE;
E 12
I 12
		gcp->gc_flow_control = FLOW_CONTROL_SYMMETRIC;
E 12
E 5

I 17
D 21
		/* mii mode */
		gcp->gc_mii_mode = GEM_MODE_100BASETX;

E 21
E 17
		/* MII timeout parameters */
D 5
		gc.gc_mii_link_watch_interval = ONESEC;
I 4
		gc.gc_mii_an_watch_interval   = ONESEC/5;
E 4
		gc.gc_mii_reset_timeout = MII_RESET_TIMEOUT;	/* 1 sec */
		gc.gc_mii_an_timeout = MII_AN_TIMEOUT;	/* 5 sec */
		gc.gc_mii_an_wait = 0;	/* 0 for default, 3 for via rhine */
		gc.gc_mii_linkdown_timeout = MII_LINKDOWN_TIMEOUT;
E 5
I 5
D 17
		gcp->gc_mii_link_watch_interval = ONESEC;
E 17
I 17
D 21
		gcp->gc_mii_link_watch_interval = GEM_LINK_WATCH_INTERVAL;
E 21
I 21
		gcp->gc_mii_link_watch_interval = ONESEC;
E 21
E 17
D 19
		gcp->gc_mii_an_watch_interval   = ONESEC/5;
E 19
I 19
		gcp->gc_mii_an_watch_interval = ONESEC/5;
E 19
		gcp->gc_mii_reset_timeout = MII_RESET_TIMEOUT;	/* 1 sec */
D 15
		gcp->gc_mii_an_timeout = MII_AN_TIMEOUT;	/* 5 sec */
		gcp->gc_mii_an_wait = 0;
E 15
I 15
D 19
		gcp->gc_mii_an_timeout    = MII_AN_TIMEOUT;	/* 5 sec */
		gcp->gc_mii_an_wait       = 0;
E 19
I 19
		gcp->gc_mii_an_timeout = MII_AN_TIMEOUT;	/* 5 sec */
		gcp->gc_mii_an_wait = 0;
E 19
E 15
		gcp->gc_mii_linkdown_timeout = MII_LINKDOWN_TIMEOUT;
E 5

I 18
		/* hw link event doesn't work */
		gcp->gc_mii_hw_link_detection = B_FALSE;

E 18
D 3
		/* work arounds */
E 3
I 3
		/* MII work arounds */
D 5
		gc.gc_mii_addr_min = 1;
E 3
D 4
		gc.gc_mii_need_an_delay = FALSE;
E 4
I 4
		gc.gc_mii_an_delay = 0;
E 4
		gc.gc_mii_linkdown_action = MII_ACTION_NONE;
		gc.gc_mii_dont_reset = FALSE;
E 5
I 5
D 17
		gcp->gc_mii_addr_min = 1;
E 17
I 17
		gcp->gc_mii_addr_min = 0;
E 17
		gcp->gc_mii_an_delay = 0;
D 15
		gcp->gc_mii_linkdown_action = MII_ACTION_RSA;
E 15
I 15
D 19
		gcp->gc_mii_linkdown_action = MII_ACTION_NONE;
		gcp->gc_mii_linkdown_timeout_action = MII_ACTION_RSA;
E 19
I 19
		gcp->gc_mii_linkdown_action = MII_ACTION_RSA;
		gcp->gc_mii_linkdown_timeout_action = MII_ACTION_RESET;
E 19
E 15
D 17
		gcp->gc_mii_dont_reset = FALSE;
E 17
I 17
		gcp->gc_mii_dont_reset = B_FALSE;
E 17
E 5

		/* I/O methods */

		/* mac operation */
D 5
		gc.gc_attach_chip = &alta_attach_chip;
		gc.gc_reset_chip  = &alta_reset_chip;
		gc.gc_init_chip   = &alta_init_chip;
		gc.gc_start_chip  = &alta_start_chip;
		gc.gc_stop_chip   = &alta_stop_chip;
D 3
		gc.gc_multicast_hash = NULL;
E 3
I 3
#ifdef USE_MULTICAST_HASHTBL
		gc.gc_multicast_hash = &alta_mcast_hash;
#endif
E 3
		gc.gc_set_rx_filter = &alta_set_rx_filter;
		gc.gc_set_media   = &alta_set_media;
		gc.gc_get_stats   = &alta_get_stats;
		gc.gc_interrupt   = &alta_interrupt;
E 5
I 5
		gcp->gc_attach_chip = &alta_attach_chip;
D 19
		gcp->gc_reset_chip  = &alta_reset_chip;
		gcp->gc_init_chip   = &alta_init_chip;
		gcp->gc_start_chip  = &alta_start_chip;
		gcp->gc_stop_chip   = &alta_stop_chip;
E 19
I 19
		gcp->gc_reset_chip = &alta_reset_chip;
		gcp->gc_init_chip = &alta_init_chip;
		gcp->gc_start_chip = &alta_start_chip;
		gcp->gc_stop_chip = &alta_stop_chip;
E 19
		gcp->gc_multicast_hash = &alta_mcast_hash;
		gcp->gc_set_rx_filter = &alta_set_rx_filter;
D 19
		gcp->gc_set_media   = &alta_set_media;
		gcp->gc_get_stats   = &alta_get_stats;
		gcp->gc_interrupt   = &alta_interrupt;
E 19
I 19
		gcp->gc_set_media = &alta_set_media;
		gcp->gc_get_stats = &alta_get_stats;
		gcp->gc_interrupt = &alta_interrupt;
E 19
E 5

		/* descriptor operation */
D 5
		gc.gc_tx_desc_write = &alta_tx_desc_write;
		gc.gc_rx_desc_write = &alta_rx_desc_write;
E 5
I 5
		gcp->gc_tx_desc_write = &alta_tx_desc_write;
		gcp->gc_rx_desc_write = &alta_rx_desc_write;
I 17
D 19
		gcp->gc_tx_start      = &alta_tx_start;
E 19
I 19
		gcp->gc_tx_start = &alta_tx_start;
E 19
E 17
E 5

D 5
		gc.gc_tx_desc_init = &alta_tx_desc_init;
		gc.gc_rx_desc_init = &alta_rx_desc_init;
		gc.gc_tx_desc_stat = &alta_tx_desc_stat;
		gc.gc_rx_desc_stat = &alta_rx_desc_stat;
		gc.gc_tx_desc_clean = &alta_tx_desc_clean;
		gc.gc_rx_desc_clean = &alta_rx_desc_clean;
E 5
I 5
		gcp->gc_tx_desc_init = &alta_tx_desc_init;
		gcp->gc_rx_desc_init = &alta_rx_desc_init;
		gcp->gc_tx_desc_stat = &alta_tx_desc_stat;
		gcp->gc_rx_desc_stat = &alta_rx_desc_stat;
		gcp->gc_tx_desc_clean = &alta_tx_desc_clean;
		gcp->gc_rx_desc_clean = &alta_rx_desc_clean;
E 5

		/* mii operations */
D 5
		gc.gc_mii_init  = &gem_mii_init_default;
		gc.gc_mii_config = &gem_mii_config_default;
		gc.gc_mii_sync  = &alta_mii_sync;
		gc.gc_mii_read  = &alta_mii_read;
		gc.gc_mii_write = &alta_mii_write;
		gc.gc_mii_tune_phy = NULL;
E 5
I 5
D 19
		gcp->gc_mii_init  = &gem_mii_init_default;
E 19
I 19
D 22
		gcp->gc_mii_probe = &gem_mii_probe_default;
E 22
I 22
		gcp->gc_mii_probe = &alta_mii_probe;
E 22
		gcp->gc_mii_init = NULL;
E 19
		gcp->gc_mii_config = &gem_mii_config_default;
D 19
		gcp->gc_mii_sync  = &alta_mii_sync;
		gcp->gc_mii_read  = &alta_mii_read;
E 19
I 19
		gcp->gc_mii_sync = &alta_mii_sync;
		gcp->gc_mii_read = &alta_mii_read;
E 19
		gcp->gc_mii_write = &alta_mii_write;
		gcp->gc_mii_tune_phy = NULL;
E 5
D 4
		gc.gc_get_packet   = &gem_get_packet_default;
E 4

D 8
		lp = kmem_zalloc(sizeof(struct alta_chip_state), KM_SLEEP);
E 8
I 8
D 19
		lp = kmem_zalloc(sizeof(struct alta_dev), KM_SLEEP);
E 19
I 19
		lp = kmem_zalloc(sizeof (struct alta_dev), KM_SLEEP);
E 19
E 8
I 3
		lp->rev_id = revid;
I 22

		/* offload and jumbo frame */
		gcp->gc_max_lso = 0;
		gcp->gc_max_mtu = 0x7f8 - sizeof (struct ether_header) - 4 - 4;
		gcp->gc_default_mtu = ETHERMTU;
		gcp->gc_min_mtu = ETHERMIN - sizeof (struct ether_header);

E 22
E 3
D 5
		dp = gem_do_attach(dip, &gc, base, &regs_handle,
E 5
I 5
D 16
		dp = gem_do_attach(dip, gcp, base, &regs_handle,
E 16
I 16
D 19
		dp = gem_do_attach(dip, gcp, base, &regs_ha,
E 16
E 5
					lp, sizeof(*lp));
E 19
I 19
		dp = gem_do_attach(dip, 0,
		    gcp, base, &regs_ha, lp, sizeof (*lp));
E 19

I 5
D 19
		kmem_free(gcp, sizeof(*gcp));
E 19
I 19
		kmem_free(gcp, sizeof (*gcp));
E 19

E 5
		if (dp != NULL) {
D 17
			return DDI_SUCCESS;
E 17
I 17
			return (DDI_SUCCESS);
E 17
		}
err_free_mem:
D 8
		kmem_free(lp, sizeof(struct alta_chip_state));
E 8
I 8
D 19
		kmem_free(lp, sizeof(struct alta_dev));
E 19
I 19
		kmem_free(lp, sizeof (struct alta_dev));
E 19
E 8
err:
D 17
		return DDI_FAILURE;
E 17
I 17
		return (DDI_FAILURE);
E 17
	}
D 17
	return DDI_FAILURE;
E 17
I 17
	return (DDI_FAILURE);
E 17
}

static int
altadetach(dev_info_t *dip, ddi_detach_cmd_t cmd)
{
	int	ret;

D 16
	if (cmd == DDI_DETACH) {
		ret = gem_do_detach(dip);
		if (ret != DDI_SUCCESS) {
D 4
			goto err;
E 4
I 4
			return DDI_FAILURE;
E 4
		}
		return DDI_SUCCESS;
E 16
I 16
	switch (cmd) {
	case DDI_SUSPEND:
D 17
		return  gem_suspend(dip);
E 17
I 17
		return (gem_suspend(dip));
E 17

	case DDI_DETACH:
D 17
		return  gem_do_detach(dip);
E 17
I 17
		return (gem_do_detach(dip));
E 17
E 16
D 4
err:
		return DDI_FAILURE;

E 4
	}
D 17
	return DDI_FAILURE;
E 17
I 17
	return (DDI_FAILURE);
E 17
}

/* ======================================================== */
/*
 * OS depend (loadable streams driver) routine
 */
/* ======================================================== */
I 21
#ifdef GEM_CONFIG_GLDv3
GEM_STREAM_OPS(alta_ops, altaattach, altadetach);
#else
E 21
static	struct module_info altaminfo = {
	0,			/* mi_idnum */
	"alta",			/* mi_idname */
	0,			/* mi_minpsz */
D 17
	ETHERMTU,		/* mi_maxpsz */
D 8
	32*1024,		/* mi_hiwat */
E 8
I 8
D 12
	INT32_MAX,		/* mi_hiwat */
E 12
I 12
	TX_RING_SIZE*ETHERMAX,	/* mi_hiwat */
E 17
I 17
	INFPSZ,			/* mi_maxpsz */
	64*1024,		/* mi_hiwat */
E 17
E 12
E 8
	1,			/* mi_lowat */
};

static	struct qinit altarinit = {
	(int (*)()) NULL,	/* qi_putp */
D 4
	gld_rsrv,		/* qi_srvp */
	gld_open,		/* qi_qopen */
	gld_close,		/* qi_qclose */
E 4
I 4
	gem_rsrv,		/* qi_srvp */
	gem_open,		/* qi_qopen */
	gem_close,		/* qi_qclose */
E 4
	(int (*)()) NULL,	/* qi_qadmin */
	&altaminfo,		/* qi_minfo */
	NULL			/* qi_mstat */
};

static	struct qinit altawinit = {
D 4
	gld_wput,		/* qi_putp */
	gld_wsrv,		/* qi_srvp */
E 4
I 4
	gem_wput,		/* qi_putp */
	gem_wsrv,		/* qi_srvp */
E 4
	(int (*)()) NULL,	/* qi_qopen */
	(int (*)()) NULL,	/* qi_qclose */
	(int (*)()) NULL,	/* qi_qadmin */
	&altaminfo,		/* qi_minfo */
	NULL			/* qi_mstat */
};

static struct streamtab	alta_info = {
	&altarinit,	/* st_rdinit */
	&altawinit,	/* st_wrinit */
	NULL,		/* st_muxrinit */
	NULL		/* st_muxwrinit */
};

static	struct cb_ops cb_alta_ops = {
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
	&alta_info,	/* cb_stream */
D 17
	D_NEW|D_MP	/* cb_flag */
E 17
I 17
	D_MP,		/* cb_flag */
#ifdef notdef
	CB_REV,		/* cb_rev */
	nodev,		/* cb_aread */
	nodev,		/* cb_awrite */
#endif
E 17
};

static	struct dev_ops alta_ops = {
	DEVO_REV,	/* devo_rev */
	0,		/* devo_refcnt */
D 4
	gld_getinfo,	/* devo_getinfo */
E 4
I 4
	gem_getinfo,	/* devo_getinfo */
E 4
	nulldev,	/* devo_identify */
	nulldev,	/* devo_probe */
	altaattach,	/* devo_attach */
	altadetach,	/* devo_detach */
	nodev,		/* devo_reset */
	&cb_alta_ops,	/* devo_cb_ops */
	NULL,		/* devo_bus_ops */
D 17
	ddi_power	/* devo_power */
E 17
I 17
	gem_power	/* devo_power */
E 17
};
D 21

E 21
I 21
#endif /* GEM_CONFIG_GLDv3 */
E 21
static struct modldrv modldrv = {
	&mod_driverops,	/* Type of module.  This one is a driver */
	ident,
	&alta_ops,	/* driver ops */
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

D 19
	DPRINTF(2, (CE_CONT, "alta: _init: called"));
E 19
I 19
	DPRINTF(2, (CE_CONT, "!alta: _init: called"));
E 19
I 17
	gem_mod_init(&alta_ops, "alta");
E 17
	status = mod_install(&modlinkage);
I 17
	if (status != DDI_SUCCESS) {
		gem_mod_fini(&alta_ops);
	}
E 17

	return (status);
}

/*
 * _fini : done
 */
int
_fini(void)
{
	int	status;

D 19
	DPRINTF(2, (CE_CONT, "alta: _fini: called"));
E 19
I 19
	DPRINTF(2, (CE_CONT, "!alta: _fini: called"));
E 19
	status = mod_remove(&modlinkage);
I 17
	if (status == DDI_SUCCESS) {
		gem_mod_fini(&alta_ops);
	}
E 17
	return (status);
}

int
_info(struct modinfo *modinfop)
{
	return (mod_info(&modlinkage, modinfop));
}
D 19

E 19
E 1
