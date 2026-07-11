h16111
s 00017/00005/01917
d D 1.11 08/12/31 23:44:38 mrym 11 10
c 2.6.3
e
s 00002/00003/01920
d D 1.10 08/11/28 19:07:40 mrym 10 9
c 2.6.3
e
s 00252/00246/01671
d D 1.9 08/10/11 10:55:41 mrym 9 8
c 2.6.2
e
s 00422/00461/01495
d D 1.8 08/04/20 21:17:53 mrym 8 7
c cstyled
e
s 00009/00011/01947
d D 1.7 02/01/01 06:08:40 mrym 7 6
c dma burst length tuning
e
s 00213/00199/01745
d D 1.6 06/12/04 02:59:52 mrym 6 5
c 2.4.0t1
e
s 00110/00060/01834
d D 1.5 06/03/24 00:54:11 mrym 5 4
c 2.0.2 again
e
s 00318/00356/01576
d D 1.4 06/03/15 00:41:13 mrym 4 3
c 2.0.1
e
s 00234/00209/01698
d D 1.3 05/08/11 03:11:36 mrym 3 2
c 0.8.2
e
s 00298/00151/01609
d D 1.2 05/04/22 23:58:05 mrym 2 1
c 0.8.1
e
s 01760/00000/00000
d D 1.1 05/02/08 23:14:06 mrym 1 0
c date and time created 05/02/08 23:14:06 by mrym
e
u
U
f e 0
t
T
I 1
/*
D 4
 * vel_gem.c: VIA Technology Velocity seris Giga Ethernet MAC driver
E 4
I 4
D 8
 * vel_gem.c: VIA Technology Velocity series Gigabit Ethernet MAC driver
E 8
I 8
 * vel: VIA Technology Velocity series Gigabit Ethernet MAC driver
E 8
E 4
 *
D 4
 * Copyright (c) 2002-2004 Masayuki Murayama.  All rights reserved.
E 4
I 4
D 8
 * Copyright (c) 2002-2006 Masayuki Murayama.  All rights reserved.
E 4
 * 
E 8
I 8
 * Copyright (c) 2002-2008 Masayuki Murayama.  All rights reserved.
 *
E 8
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
D 8
 * 
E 8
I 8
 *
E 8
 * 1. Redistributions of source code must retain the above copyright notice,
D 8
 *    this list of conditions and the following disclaimer. 
 * 
E 8
I 8
 *    this list of conditions and the following disclaimer.
 *
E 8
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
D 8
 *    and/or other materials provided with the distribution. 
 * 
E 8
I 8
 *    and/or other materials provided with the distribution.
 *
E 8
 * 3. Neither the name of the author nor the names of its contributors may be
 *    used to endorse or promote products derived from this software without
D 8
 *    specific prior written permission. 
 * 
E 8
I 8
 *    specific prior written permission.
 *
E 8
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
D 8
#pragma	ident	"%W% %E%"
E 8

D 8
/*
 Change log
I 4
	03/01/2006	100/10m mode didn't work. thank to toshio kumagai.
	03/14/2006	2.0.1 sccs check-in
I 5
	03/18/2006	wrong multicast hash fixed
	03/20/2006	multicast cam control fixed, now it worked with IPv6
			completely. Thank you to toshio kumagai very much.
	03/21/2006	2.0.2 sccs check-in
	03/22/2006	ISR_FLON removed from OUR_INTR_BITS
	03/23/2006	dditypes.h added, ddi_impldef.h removed.
	03/24/2006	2.0.2 sccs check-in again
I 6
	12/04/2006	fixed: UDP packets caused rx errors
E 6
E 5
E 4
 */
E 8
I 8
#pragma	ident	"%Z%%M% %I%     %E%"
E 8

/*
D 8
 TODO:
	tuning on tx underflow.
	test flow control
 */

I 2
/* ======================================================= */

E 2
/*
E 8
 * System Header files.
 */
#include <sys/types.h>
#include <sys/conf.h>
#include <sys/debug.h>
D 8
#include <sys/stropts.h>
#include <sys/stream.h>
#include <sys/strlog.h>
E 8
#include <sys/kmem.h>
D 8
#include <sys/stat.h>
#include <sys/kstat.h>
#include <sys/vtrace.h>
#include <sys/dlpi.h>
#include <sys/strsun.h>
#include <sys/ethernet.h>
E 8
#include <sys/modctl.h>
#include <sys/errno.h>
I 5
D 8
#include <sys/dditypes.h>
E 8
E 5
#include <sys/ddi.h>
#include <sys/sunddi.h>
D 5
#include <sys/ddi_impldefs.h>
E 5
D 8

#include <sys/pci.h>
E 8
I 6
#include <sys/byteorder.h>
I 8
#include <sys/ethernet.h>
#include <sys/pci.h>
E 8
E 6
D 2
#include "mii.h"
E 2
I 2

I 8
#include "gem_mii.h"
E 8
E 2
#include "gem.h"
I 2
D 8
#include "mii.h"
E 8
E 2
#include "vt612xreg.h"

D 3
static char	ident[] = "via velocity nic driver v" VERSION;
E 3
I 3
D 4
char	ident[] = "via velocity nic driver v" VERSION;
E 3
char	_depends_on[] = {"misc/gld"};
E 4
I 4
char	ident[] = "via vt612x nic driver v" VERSION;
E 4

/* Debugging support */
#ifdef DEBUG_LEVEL
static int vel_debug = DEBUG_LEVEL;
D 8
#define	DPRINTF(n, args)	if (vel_debug>(n)) cmn_err args
E 8
I 8
#define	DPRINTF(n, args)	if (vel_debug > (n)) cmn_err args
E 8
#else
#define	DPRINTF(n, args)
#endif

/*
 * Useful macros and typedefs
 */
D 4
#define	FALSE	(0)
#define	TRUE	(!FALSE)
E 4
#define	ONESEC	drv_usectohz(1*1000000)
D 5

E 5
I 3
#define	ROUNDUP(x, a)	(((x) + (a) - 1) & ~((a) - 1))

E 3
D 2
#ifdef sun4u
#define	LE32(x)	gem_le32(x)
#else
#define	LE32(x)	(x)
#endif

E 2
#ifdef MAP_MEM
I 4
D 6
#if 1
I 5
#   undef INB
#   define INB(dp, reg)	\
	(*((volatile uint8_t *)(((caddr_t)(dp)->base_addr) + (reg))))
#   undef OUTB
#   define OUTB(dp, reg, val)	\
	*((uint8_t *)(((volatile caddr_t)(dp)->base_addr) + (reg))) = (val)
E 5
#   undef INW
#   define INW(dp, reg)	\
	(*((volatile uint16_t *)(((caddr_t)(dp)->base_addr) + (reg))))
#   undef OUTW
#   define OUTW(dp, reg, val)	\
	*((uint16_t *)(((volatile caddr_t)(dp)->base_addr) + (reg))) = (val)
#   undef INL
#   define INL(dp, reg)	\
	(*((volatile uint32_t *)(((caddr_t)(dp)->base_addr) + (reg))))
#   undef OUTL
#   define OUTL(dp, reg, val)	\
	*((uint32_t *)(((volatile caddr_t)(dp)->base_addr) + (reg))) = (val)
#endif
E 6
E 4
D 8
#define	FLSHB(dp,reg)		INB(dp, reg)
#define	FLSHW(dp,reg)		INW(dp, reg)
#define	FLSHL(dp,reg)		INL(dp, reg)
E 8
I 8
#define	FLSHB(dp, reg)		INB(dp, reg)
#define	FLSHW(dp, reg)		INW(dp, reg)
#define	FLSHL(dp, reg)		INL(dp, reg)
E 8
#else /* MAP_MEM */
D 8
#define	FLSHB(dp,reg)
#define	FLSHW(dp,reg)
#define	FLSHL(dp,reg)
E 8
I 8
#define	FLSHB(dp, reg)
#define	FLSHW(dp, reg)
#define	FLSHL(dp, reg)
E 8
#endif /* MAP_MEM */

D 7
#define	STRUCT_COPY(a, b)	bcopy(&(b), &(a), sizeof(a))

E 7
D 4
/*
I 2
 * Experimental: polling mode support
 */
#define VEL_IS_POLLING(lp)	(((lp)->imr & ISR_PRX) == 0)
E 4
I 4
D 8
#if defined(sun4u)
I 5
#  define LE16_CONST(x)	((((x) & 0xff) << 8) | (((x) >> 8) & 0xff))
#  define LE32_CONST(x)	((LE16_CONST((x) & 0xffff) << 16) |	\
			  LE16_CONST(((x) >> 16) & 0xffff))
E 5
#  define LE32(x)	ddi_swap32(x)
I 5
#  define LE64(x)	ddi_swap64(x)
E 5
#else
I 5
#  define LE16_CONST(x)	((uint16_t)(x))
#  define LE32_CONST(x)	((uint32_t)(x))
I 6
#  define LE64_CONST(x)	((uint64_t)(x))
E 6
E 5
#  define LE32(x)	((uint32_t)(x))
I 5
#  define LE64(x)	((uint64_t)(x))
E 5
#endif
E 4

E 8
D 4

E 4
/*
E 2
 * Our configuration
 */
#define	OUR_INTR_BITS	\
D 8
	(ISR_PPTX | ISR_PPRX  | ISR_PTX   | ISR_PRX  | \
D 5
	 ISR_PWE  | ISR_TXWB0 | ISR_TXWB1 | ISR_FLON | \
E 5
I 5
D 6
	 ISR_PWE  | ISR_TXWB0 | ISR_TXWB1 | \
E 6
I 6
	 ISR_PWE  | ISR_TXWB0 | ISR_TXWB1 | ISR_PHY | \
E 6
E 5
	 ISR_OVF  | ISR_LSTE  | ISR_LSTPE | ISR_SRC  | ISR_MIBF | \
	 ISR_SHDN | ISR_TMR1  | ISR_TMR0  | ISR_TXSTL)
E 8
I 8
D 9
	(ISR_PPTX | ISR_PTX   | ISR_PRX  | \
	ISR_PWE  | ISR_TXWB0 | ISR_TXWB1 | ISR_PHY | \
	ISR_OVF  | ISR_LSTE  | ISR_SRC  | ISR_MIBF | \
	ISR_SHDN | ISR_TMR1  | ISR_TMR0  | ISR_TXSTL)
E 9
I 9
	(ISR_TXSTL | ISR_RXSTL | ISR_MIBF | ISR_SHDN | ISR_PHY | \
	ISR_TMR1 | ISR_TMR0 | ISR_SRC | ISR_LSTE | ISR_OVF | \
	ISR_RACE | ISR_TXWB1 | ISR_TXWB0 | ISR_PTX)
E 9
E 8

D 3
#ifdef PTX_TEST
E 3
I 3
#ifdef TEST_TXDESC_FULL
E 3
D 8
#  define TX_RING_SIZE	16
E 8
I 8
D 9
#define	TX_RING_SIZE	16
E 8
#else
D 2
#  define TX_RING_SIZE	64
E 2
I 2
D 6
#  define TX_RING_SIZE	256
E 6
I 6
D 8
#  define TX_RING_SIZE	64
E 8
I 8
#define	TX_RING_SIZE	64
E 9
I 9
#undef	TX_BUF_SIZE
#define	TX_BUF_SIZE	16
E 9
E 8
E 6
E 2
#endif
D 4
#define TX_BUF_SIZE	(TX_RING_SIZE - 1)
E 4
I 4
D 8
#define TX_BUF_SIZE	TX_RING_SIZE
E 8
I 8
D 9
#define	TX_BUF_SIZE	TX_RING_SIZE
E 9
I 9
#ifndef TX_BUF_SIZE
D 11
#define	TX_BUF_SIZE	256		/* hardware max */
E 11
I 11
#define	TX_BUF_SIZE	256		/* hardware max is 256 */
E 11
#endif
E 9
E 8
E 4

D 2
#define RX_BUF_SIZE	64
E 2
I 2
D 3
#define RX_BUF_SIZE	256
E 3
I 3
#ifdef TEST_RX_EMPTY
D 8
# define RX_BUF_SIZE	8
E 8
I 8
D 9
#define	RX_BUF_SIZE	8
E 9
I 9
#undef	RX_BUF_SIZE
#define	RX_BUF_SIZE	32
E 9
E 8
#endif
D 9

E 9
#ifndef RX_BUF_SIZE
D 8
# define RX_BUF_SIZE	256
E 8
I 8
D 9
#define	RX_BUF_SIZE	64
E 9
I 9
D 11
#define	RX_BUF_SIZE	256		/* hardware max */
E 11
I 11
#define	RX_BUF_SIZE	256		/* hardware max is 256 */
E 11
E 9
E 8
#endif
E 3
E 2
D 8
#define RX_RING_SIZE	RX_BUF_SIZE
E 8
I 8
D 9
#define	RX_RING_SIZE	RX_BUF_SIZE
E 9
E 8

I 2
D 4
#define	USE_MCAST_CAM
E 4
I 4
D 5
#undef	USE_MCAST_CAM
E 4

E 5
#define	CONFIG_TX_SINGLE_QUEUE

I 4
D 8
#if defined(sun4u) || defined(CONFIG_TX_COPY)
E 8
I 8
#ifdef CONFIG_TX_COPY
E 8
static int	vel_tx_copy_thresh = INT32_MAX;
#else
E 4
E 2
static int	vel_tx_copy_thresh = 256;
I 4
#endif
D 8
#if defined(sun4u) || defined(CONFIG_RX_COPY)
E 8
I 8
#ifdef CONFIG_RX_COPY
E 8
static int	vel_rx_copy_thresh = INT32_MAX;
#else
E 4
static int	vel_rx_copy_thresh = 256;
I 4
#endif
E 4

/*
 * veline chip state
 */
struct vel_dev {
D 2
	uint8_t		mac_addr[ETHERADDRL];
	uint8_t		revid;	/* chip revision id */
	uint8_t		rft;	/* rx fifo threshold */
	uint8_t		maxdma;
	uint32_t	imr;
	int		rxbuf_added;
E 2
I 2
D 5
	uint8_t			mac_addr[ETHERADDRL];
	uint8_t			revid;	/* chip revision id */
	uint8_t			rft;	/* rx fifo threshold */
	uint8_t			maxdma;
	uint32_t		imr;
D 4
	int			rxbuf_added;
#ifdef CONFIG_POLLING
	int			tx_list_len;
E 4
	int			last_poll_interval;
E 5
I 5
D 6
	uint8_t		mac_addr[ETHERADDRL];
	uint8_t		revid;	/* chip revision id */
	uint8_t		rft;	/* rx fifo threshold */
	uint8_t		maxdma;
	uint32_t	imr;
E 6
I 6
	uint8_t			mac_addr[ETHERADDRL];
	uint8_t			revid;	/* chip revision id */
	uint16_t		rft;	/* rx fifo threshold */
	uint16_t		maxdma;
	volatile uint32_t	imr;
E 6
D 9
#ifdef GEM_CONFIG_POLLING
E 9
I 9
#ifdef CONFIG_POLLING
E 9
D 6
	int		last_poll_interval;
E 6
I 6
	int			last_poll_interval;
E 6
#endif
E 5
D 4
#endif
E 4
E 2
#ifdef RESET_TEST
D 6
	int		reset_test;
E 6
I 6
	int			reset_test;
E 6
#endif
I 6
D 9
	int			tx_list_len;
E 9
I 9
	int			rx_tail;
E 9
I 8

D 9
	int			rx_desc_rest;

E 9
	/* device type */
	boolean_t		pcie;
E 8
E 6
};

/*
 * Supported chips
 */
struct chip_info {
	uint16_t	venid;
	uint16_t	devid;
	char		*name;
};

static struct chip_info vel_chiptbl[] = {
	{VID_VIA, DID_VT6122, "VT6122"},
};
D 8
#define CHIPTABLESIZE   (sizeof(vel_chiptbl)/sizeof(struct chip_info))
E 8
I 8
#define	CHIPTABLESIZE   (sizeof (vel_chiptbl) / sizeof (struct chip_info))
E 8

/*
 * Macros to identify chip generation.
 */

/* ======================================================== */
D 8
 
E 8
I 8

E 8
/* mii operations */
static void  vel_mii_sync(struct gem_dev *);
D 3
static uint16_t  vel_mii_read(struct gem_dev *, int);
static void vel_mii_write(struct gem_dev *, int, uint16_t);
E 3
I 3
static uint16_t  vel_mii_read(struct gem_dev *, uint_t);
static void vel_mii_write(struct gem_dev *, uint_t, uint16_t);
E 3

/* nic operations */
I 3
static int vel_attach_chip(struct gem_dev *);
E 3
static int vel_reset_chip(struct gem_dev *);
D 6
static void vel_init_chip(struct gem_dev *);
static void vel_start_chip(struct gem_dev *);
static void vel_stop_chip(struct gem_dev *);
static void vel_set_media(struct gem_dev *);
static void vel_set_rx_filter(struct gem_dev *);
static void vel_get_stats(struct gem_dev *);
E 6
I 6
static int vel_init_chip(struct gem_dev *);
static int vel_start_chip(struct gem_dev *);
static int vel_stop_chip(struct gem_dev *);
static int vel_set_media(struct gem_dev *);
static int vel_set_rx_filter(struct gem_dev *);
static int vel_get_stats(struct gem_dev *);
E 6
D 3
static int vel_init_mac_addr(struct gem_dev *);
E 3

/* descriptor operations */
D 4
static int vel_tx_desc_write(struct gem_dev *dp, uint_t slot,
E 4
I 4
static int vel_tx_desc_write(struct gem_dev *dp, int slot,
E 4
D 8
		    ddi_dma_cookie_t *dmacookie, int frags, uint32_t intreq);
E 8
I 8
    ddi_dma_cookie_t *dmacookie, int frags, uint64_t intreq);
E 8
D 4
static int vel_rx_desc_write(struct gem_dev *dp, uint_t slot,
E 4
I 4
static void vel_tx_start(struct gem_dev *dp, int slot, int frags);
static void vel_rx_desc_write(struct gem_dev *dp, int slot,
E 4
D 8
		    ddi_dma_cookie_t *dmacookie, int frags);
E 8
I 8
    ddi_dma_cookie_t *dmacookie, int frags);
E 8
static uint_t vel_tx_desc_stat(struct gem_dev *dp, int slot, int ndesc);
I 6
static void vel_rx_start(struct gem_dev *dp, int slot, int frags);
E 6
D 4
static uint_t vel_rx_desc_stat(struct gem_dev *dp, int slot, int ndesc);
E 4
I 4
static uint64_t vel_rx_desc_stat(struct gem_dev *dp, int slot, int ndesc);
E 4

static void vel_tx_desc_init(struct gem_dev *dp, int slot);
static void vel_rx_desc_init(struct gem_dev *dp, int slot);
static void vel_tx_desc_clean(struct gem_dev *dp, int slot);
static void vel_rx_desc_clean(struct gem_dev *dp, int slot);

/* interrupt handler */
D 8
static u_int vel_interrupt(struct gem_dev *dp);
E 8
I 8
static uint_t vel_interrupt(struct gem_dev *dp);
E 8

/* ======================================================== */

/* mapping attributes */
/* Data access requirements. */
static struct ddi_device_acc_attr vel_dev_attr = {
	DDI_DEVICE_ATTR_V0,
	DDI_STRUCTURE_LE_ACC,
	DDI_STRICTORDER_ACC
};

/* On sparc, the buffers should be native endianness */
static struct ddi_device_acc_attr vel_buf_attr = {
	DDI_DEVICE_ATTR_V0,
	DDI_NEVERSWAP_ACC,	/* native endianness */
	DDI_STRICTORDER_ACC
};

D 9
static ddi_dma_attr_t vel_dma_attr_buf32 = {
E 9
I 9
#ifdef CONFIG_DAC
static ddi_dma_attr_t vel_dma_attr_buf = {
E 9
	DMA_ATTR_V0,		/* dma_attr_version */
	0,			/* dma_attr_addr_lo */
D 9
	0xffffffffull,		/* dma_attr_addr_hi */
E 9
I 9
	0x0000ffffffffffffull,	/* dma_attr_addr_hi */
E 9
	0x00003fffull,		/* dma_attr_count_max */
D 8
	0,/* patched later */	/* dma_attr_align */
E 8
I 8
	0, /* patched later */	/* dma_attr_align */
E 8
	0x00003fff,		/* dma_attr_burstsizes */
	1,			/* dma_attr_minxfer */
D 4
	0xffffffffull,		/* dma_attr_maxxfer */
E 4
I 4
D 9
	0x00003fffull,		/* dma_attr_maxxfer */
E 4
	0xffffffffull,		/* dma_attr_seg */
E 9
I 9
	0x0000000000003fffull,	/* dma_attr_maxxfer */
	0x0000ffffffffffffull,	/* dma_attr_seg */
E 9
D 8
	0,/* patched later */	/* dma_attr_sgllen */
E 8
I 8
	0, /* patched later */	/* dma_attr_sgllen */
E 8
	1,			/* dma_attr_granular */
	0			/* dma_attr_flags */
};
D 9
#ifdef CONFIG_DAC
static ddi_dma_attr_t vel_dma_attr_buf64 = {
E 9
I 9
#else
static ddi_dma_attr_t vel_dma_attr_buf = {
E 9
	DMA_ATTR_V0,		/* dma_attr_version */
	0,			/* dma_attr_addr_lo */
D 9
	0x0000ffffffffffffull,	/* dma_attr_addr_hi */
E 9
I 9
	0xffffffffull,		/* dma_attr_addr_hi */
E 9
	0x00003fffull,		/* dma_attr_count_max */
D 8
	0,/* patched later */	/* dma_attr_align */
E 8
I 8
	0, /* patched later */	/* dma_attr_align */
E 8
	0x00003fff,		/* dma_attr_burstsizes */
	1,			/* dma_attr_minxfer */
	0x00003fffull,		/* dma_attr_maxxfer */
D 9
	0x0000ffffffffffffull,	/* dma_attr_seg */
E 9
I 9
	0xffffffffull,		/* dma_attr_seg */
E 9
D 8
	0,/* patched later */	/* dma_attr_sgllen */
E 8
I 8
	0, /* patched later */	/* dma_attr_sgllen */
E 8
	1,			/* dma_attr_granular */
	0			/* dma_attr_flags */
};
#endif
static ddi_dma_attr_t vel_dma_attr_desc = {
	DMA_ATTR_V0,		/* dma_attr_version */
	0,			/* dma_attr_addr_lo */
	0xffffffffull,		/* dma_attr_addr_hi */
	0xffffffffull,		/* dma_attr_count_max */
	64,			/* dma_attr_align */
	0x1f,			/* dma_attr_burstsizes */
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
vel_reset_chip(struct gem_dev *dp)
{
	int		i;
D 8
	struct vel_dev	*lp = (struct vel_dev *)dp->private;
E 8
I 8
	struct vel_dev	*lp = dp->private;
E 8

D 3
	DPRINTF(2, (CE_CONT, "!%s: vel_reset_chip: called, time:%d",
E 3
I 3
D 8
	DPRINTF(1, (CE_CONT, "!%s: vel_reset_chip: called, time:%d",
E 3
		dp->name, ddi_get_lbolt()));
E 8
I 8
	DPRINTF(1, (CE_CONT, "!%s: %s: called, time:%d",
	    dp->name, __func__, ddi_get_lbolt()));
E 8
D 6

D 3
#if DEBUG_LEVEL > 4
	/* white a dummy mac address to ensure eeprom autoloading works */
E 3
I 3
#if DEBUG_LEVEL > 0
E 6
I 6
#ifdef notdef
E 6
	/* white a dummy mac address to check eeprom autoloading works */
E 3
	for (i = 0; i < ETHERADDRL; i++) {
		OUTB(dp, PAR + i, i);
		lp->mac_addr[i] = i;
	}
#endif
I 8
	/* inhibit interrupts */
	OUTL(dp, IMR, 0);
	OUTL(dp, CR_CLR, CR_GINTMSK1);

E 8
	/* Reset the nic. */
I 3
D 8
	/* reset doesn't change mac address */
E 8
I 8
	/* XXX - reset doesn't change mac address */
E 8
E 3
	OUTL(dp, CR_SET, CR_SRST);

D 6
	i = 1;
E 6
	drv_usecwait(10);
D 6
	while ((INL(dp, CR_SET) & CR_SRST) != 0) {
E 6
I 6
D 8
	for (i = 1; (INL(dp, CR_SET) & CR_SRST) != 0; i ++) {
E 8
I 8
	for (i = 0; INL(dp, CR_SET) & CR_SRST; i++) {
E 8
E 6
		drv_usecwait(10);
D 6
		if (i++ > 1000) {
			cmn_err(CE_WARN, "!%s: vel_reset_chip: timeout",
				dp->name);
E 6
I 6
		if (i > 1000) {
			cmn_err(CE_NOTE, "!%s: %s: timeout",
D 8
				dp->name, __func__);
E 8
I 8
			    dp->name, __func__);
E 8
E 6
			/* Use force software reset bit instead of */
			OUTL(dp, CR_SET, CR_FORSRST);
			drv_usecwait(2000);
			break;
		}
	}
D 6

E 6
	drv_usecwait(5000);
D 6

E 6
I 3
D 8
#if 0
	DPRINTF(4, (CE_CONT, "%s: %s: mac[5]:%x",
		dp->name, __func__, INB(dp, PAR+5)));
E 8
I 8

	/* clear ISR */
	OUTL(dp, ISR, 0xffffffffU);

	DPRINTF(4, (CE_CONT, "!%s: %s: mac[5]:%x",
	    dp->name, __func__, INB(dp, PAR+5)));

	/* synchronzie read cache for mac address */
E 8
	for (i = 0; i < ETHERADDRL; i++) {
		lp->mac_addr[i] = INB(dp, PAR + i);
	}
D 8
#endif
E 8
I 8

E 8
E 3
D 6
	return 0;
E 6
I 6
	return (GEM_SUCCESS);
E 6
}

D 6
static void
E 6
I 6
static int
E 6
vel_init_chip(struct gem_dev *dp)
{
	int		i;
	uint32_t	val;
D 8
	struct vel_dev	*lp = (struct vel_dev *)dp->private;
E 8
I 8
	struct vel_dev	*lp = dp->private;
E 8

D 8
	DPRINTF(2, (CE_CONT, "!%s: vel_init_chip: called at time:%d",
		dp->name, ddi_get_lbolt()));
E 8
I 8
	DPRINTF(1, (CE_CONT, "!%s: %s: called at time:%d",
	    dp->name, __func__, ddi_get_lbolt()));
E 8

	/* PAR: call setmedia later */

	/* clear PreACPI bit */
	OUTB(dp, CFGA, INB(dp, CFGA) & ~CFGA_PACPI);

I 9
	/* CFGD */
	DPRINTF(2, (CE_CONT, "!%s: %s: CFGD:0x%02x",
	    dp->name, __func__, INB(dp, CFGD)));
	OUTB(dp, CFGD, INB(dp, CFGD) | CFGD_CFGDACEN | CFGD_PCI64EN);

E 9
	/* TCR */
	val = INB(dp, TCR) & ~TCR_LB;
	OUTB(dp, TCR, val | TCR_LB_NORMAL);

D 9
	/* MCFG: rx threshold */
E 9
I 9
	/* MCFG: rx threshold and tag etc, don't set MCFG_VIDFR */
E 9
D 6
	val = INW(dp, MCFG0) & ~MCFG_RFT;
	OUTW(dp, MCFG0, val | (lp->rft << MCFG_RFT_SHIFT));
E 6
I 6
	val = INW(dp, MCFG0) & ~(MCFG_RFT | MCFG_VTAG);
D 9
	val |= (lp->rft << MCFG_RFT_SHIFT) | MCFG_TXARB | MCFG_TXQNOBK;
#ifdef CONFIG_HW_VLAN
E 9
I 9
	val |= (lp->rft << MCFG_RFT_SHIFT);
#ifdef CONFIG_VLAN_HW
E 9
	val |= (VTAG_OPT2 << MCFG_VTAG_SHIFT);
#endif
	OUTW(dp, MCFG0, val);
D 8
	DPRINTF(0, (CE_CONT, "%s: mcfg:%b", dp->name, val, MCFG_BITS));
E 8
I 8
	DPRINTF(0, (CE_CONT, "!%s: mcfg:%b", dp->name, val, MCFG_BITS));
E 8
E 6

	/* DCFG: dma length */
D 2
	DPRINTF(3, (CE_CONT, "!%s: DCFG:%b",
E 2
I 2
D 3
	DPRINTF(0, (CE_CONT, "!%s: DCFG:%b",
E 3
I 3
D 9
	DPRINTF(2, (CE_CONT, "!%s: DCFG:%b",
E 9
I 9
	val = INW(dp, DCFG) & ~(DCFG_XMRL | DCFG_PERDIS | DCFG_DMA);
#ifdef CONFIG_MRM
	val |= DCFG_XMRL;	/* disable MRL */
#endif
#ifdef CONFIG_LATMEN
	val |= DCFG_LATMEN;
#endif
	val |= lp->maxdma << DCFG_DMA_SHIFT;
	OUTW(dp, DCFG, val);
	DPRINTF(0, (CE_CONT, "!%s: DCFG:%b",
E 9
E 3
E 2
D 8
		dp->name, INW(dp, DCFG), DCFG_BITS));
E 8
I 8
	    dp->name, INW(dp, DCFG), DCFG_BITS));
E 8
D 2
	val = INW(dp, DCFG) & ~DCFG_DMA;
E 2
I 2
D 9
	val = INW(dp, DCFG) & ~(DCFG_DMA | DCFG_PERDIS | DCFG_MRM);
E 2
	OUTW(dp, DCFG, val | (lp->maxdma << DCFG_DMA_SHIFT));
E 9

	/* WOL */
	OUTB(dp, WOLCFG_SET, WOLCFG_SAM | WOLCFG_SAB);

	/* CFGB */
	val = INB(dp, CFGB);
	OUTB(dp, CFGB, val | CFGB_CRANDOM | CFGB_CAP | CFGB_MBA | CFGB_BAKOPT);

	/* Rx Desc Addr */
	OUTL(dp, RDBASE_LO, (uint32_t)dp->rx_ring_dma);
I 8
	OUTW(dp, RDINDEX, 0);
E 8
D 9
	OUTW(dp, RDCSIZE, RX_RING_SIZE - 1);
E 9
I 9
	OUTW(dp, RDCSIZE, dp->gc.gc_rx_ring_size - 1);
E 9
	OUTB(dp, RDCSR_SET, RDCSR_RUN);
I 8
D 9
#if 1
E 8
	OUTB(dp, RDCSR_SET, RDCSR_WAK);
D 8

E 8
I 8
#endif
E 9
I 9
	OUTB(dp, RDCSR_SET, RDCSR_WAK);	/* activate rx dma engine */

E 9
E 8
	/* Tx Desc Addr: it has 4 transmit queues */
D 9
	OUTW(dp, TDCSIZE, TX_RING_SIZE - 1);
E 9
I 9
	OUTW(dp, TDCSIZE, dp->gc.gc_tx_ring_size - 1);
E 9
I 2

#ifdef CONFIG_TX_SINGLE_QUEUE
	OUTL(dp, TDBASE_LO, (uint32_t)dp->tx_ring_dma);
	OUTW(dp, TDCSR_SET, TDCSR_RUN(0));
	for (i = 1; i < NUM_TX_QUEUES; i++) {
D 8
		OUTL(dp, TDBASE_LO + sizeof(uint32_t)*i, 0);
E 8
I 8
		OUTL(dp, TDBASE_LO + sizeof (uint32_t)*i, 0);
E 8
		OUTW(dp, TDCSR_CLR, TDCSR_RUN(i));
	}
#else
I 4
	/* XXX - not implemented */
E 4
E 2
	for (i = 0; i < NUM_TX_QUEUES; i++) {
D 8
		OUTL(dp, TDBASE_LO + sizeof(uint32_t)*i,
			((uint32_t)dp->tx_ring_dma) +
			TX_RING_SIZE*sizeof(struct tx_desc)*i);
E 8
I 8
		OUTL(dp, TDBASE_LO + sizeof (uint32_t)*i,
		    ((uint32_t)dp->tx_ring_dma) +
D 9
		    TX_RING_SIZE * sizeof (struct tx_desc) * i);
E 9
I 9
		    dp->gc.gc_tx_ring_size * sizeof (struct tx_desc) * i);
E 9
E 8
		OUTW(dp, TDCSR_SET, TDCSR_RUN(i));
	}
I 2
#endif
E 2
D 6

E 6
	/* init cam filter: later in set_rx_filter */

	/* initialize vlan cam mask */
	OUTB(dp, CAMCR, CAMCR_SEL_MASK);
	OUTB(dp, CAMADDR, CAMADDR_EN | CAMADDR_VCAMSL);
	for (i = 0; i < 8; i++) {
		OUTB(dp, MAR + i, 0);
	}
	OUTB(dp, CAMADDR, 0);
	OUTB(dp, CAMCR, CAMCR_SEL_MAR);

	/* init flow control */
	OUTL(dp, CR_CLR, CR_TXLOWAT | CR_TXHIWAT);
	OUTL(dp, CR_SET, CR_XONEN | CR_TXLOWAT_24 | CR_TXHIWAT_48);
D 8
	OUTW(dp, PAUSE_TIMER, 0xffff);
E 8
I 8
	OUTW(dp, PAUSE_TIMER, 0xffffU);
E 8
D 4
	lp->rxbuf_added = 0;
E 4

I 2
	/* set software timer resolution to 1uS */
D 9
	val = INB(dp, GMCR) | GMCR_TMR1US | GMCR_TMR1US;
E 9
I 9
	val = INB(dp, GMCR) | GMCR_TMR0US | GMCR_TMR1US;
E 9
	OUTB(dp, GMCR, val);

E 2
D 3
	vel_set_media(dp);

E 3
D 8
	lp->imr = OUR_INTR_BITS;
	OUTL(dp, IMR, lp->imr);
E 8
I 8
	/* init adaptive interrupts */
I 9
	/* Set Tx Interrupt Suppression Threshold */
E 9
	OUTB(dp, CAMCR, CAMCR_SEL_MASK);
D 9
	OUTW(dp, ISRCTL, 31);
E 9
I 9
	OUTW(dp, ISRCTL, 31);	/* originally 31 */

	/* Set Rx Interrupt Suppression Threshold */
	/* XXX - 15 improved rx performance in my experience, but why ? */
E 9
	OUTB(dp, CAMCR, CAMCR_SEL_DATA);
D 9
	OUTW(dp, ISRCTL, 31);
E 9
I 9
	OUTW(dp, ISRCTL, 31);	/* originally 31 */
E 9
	OUTB(dp, CAMCR, 0);
E 8
I 6

D 9
	lp->tx_list_len = 0;
D 8

E 8
I 8
	lp->rx_desc_rest = 0;
E 9
I 9
	lp->rx_tail = 0;

E 9
E 8
	return (GEM_SUCCESS);
E 6
I 2
D 4
#ifdef CONFIG_POLLING
	lp->tx_list_len = 0;
#endif
E 4
E 2
}

I 3
static uint_t
vel_mcast_hash(struct gem_dev *dp, uint8_t *addr)
{
	/* hash key is higher 6 bits of msb in crc */
D 4
	return gem_ether_crc_be(addr) >> (32 - 6);
E 4
I 4
D 6
	return gem_ether_crc_be(addr, ETHERADDRL) >> (32 - 6);
E 6
I 6
	return (gem_ether_crc_be(addr, ETHERADDRL) >> (32 - 6));
E 6
E 4
}

E 3
D 6
static void
E 6
I 6
static int
E 6
I 3
D 8
vel_set_rx_filter(struct gem_dev *dp)	
E 8
I 8
vel_set_rx_filter(struct gem_dev *dp)
E 8
{
	uint8_t		mode;
	int		i, j;
	uint32_t	mhash[2];
	uint8_t		mcmask[MULTICAST_CAM_SIZE/8];
	uint8_t		*mac;
I 6
D 8
	static uint8_t	invalid_mac[ETHERADDRL] = {0,0,0,0,0,0};
E 8
I 8
	static uint8_t	invalid_mac[ETHERADDRL] = {0, 0, 0, 0, 0, 0};
	struct vel_dev	*lp = dp->private;
E 8

E 6
D 8
	struct vel_dev	*lp = (struct vel_dev *)dp->private;
E 8
I 8
	DPRINTF(1, (CE_CONT, "!%s: %s: called at time:%d, "
	    "active:%d, rxmode:%b mc_count:%d",
	    dp->name, __func__, ddi_get_lbolt(),
D 9
	    dp->mac_active, dp->rxmode, "\020\002AllMulti\001Promisc",
E 9
I 9
	    dp->mac_active, dp->rxmode, RXMODE_BITS,
E 9
	    dp->mc_count));
E 8

D 8
	DPRINTF(2, (CE_CONT, "!%s: vel_set_rx_filter: called at time:%d, "
		"active:%d, rxmode:%b mc_count:%d",
		dp->name, ddi_get_lbolt(),
D 6
		dp->nic_active, dp->rxmode, "\020\002AllMulti\001Promisc",
E 6
I 6
		dp->mac_active, dp->rxmode, "\020\002AllMulti\001Promisc",
E 6
		dp->mc_count));

E 8
D 5
	/* temporally disable rx filter before changing it */
	mode = RCR_SEP | RCR_AR;
	OUTB(dp, RCR, mode);
E 5
I 5
	/*
	 * temporally make rx filter promiscious mode not to lose any
	 * packets while changing it.
	 */
D 8
	OUTL(dp, MAR + 0, 0xffffffff);
	OUTL(dp, MAR + 4, 0xffffffff);
E 8
I 8
	OUTL(dp, MAR + 0, 0xffffffffU);
	OUTL(dp, MAR + 4, 0xffffffffU);
E 8
	OUTB(dp, RCR, RCR_SEP | RCR_AR | RCR_AB | RCR_AM | RCR_PRO);
	FLSHB(dp, RCR);
E 5

D 5
	mode |= RCR_AB;	/* broadcast */
E 5
I 5
	mode = RCR_SEP | RCR_AR | RCR_AB;	/* broadcast */
I 6
D 9
#ifdef CONFIG_HW_VLAN
	mode |= RCR_AL;	/* long packet */
#endif
E 9
I 9
	mode |= RCR_AL;	/* for long packets and soft vlan */

E 9
E 6
E 5
	mhash[0] = mhash[1] = 0;
I 5
D 8
	bzero(mcmask, sizeof(mcmask));
E 8
I 8
	bzero(mcmask, sizeof (mcmask));
E 8

E 5
D 6
	if ((dp->rxmode & RXMODE_PROMISC) != 0) {
E 6
I 6
D 8
	if ((dp->rxmode & RXMODE_ENABLE) == 0) {
		mac  = invalid_mac;
		mode = 0;
	}
	else if ((dp->rxmode & RXMODE_PROMISC) != 0) {
E 6
		mode |=RCR_PRO	/* promiscous */
                     | RCR_AM;	/* muticast */
		mhash[0] = mhash[1] = 0xffffffff;
	}
D 4
	else if (/*(dp->rxmode & RXMODE_ALLMULTI) != 0 || */
E 4
I 4
	else if ((dp->rxmode & RXMODE_ALLMULTI) != 0 ||
E 4
				dp->mc_count > MULTICAST_CAM_SIZE) {
E 8
I 8
	if (dp->rxmode & RXMODE_PROMISC) {
		mode |= RCR_PRO	/* promiscous */
		    | RCR_AM;	/* muticast */
		mhash[0] = mhash[1] = 0xffffffffU;
	} else if ((dp->rxmode & RXMODE_ALLMULTI) ||
	    dp->mc_count > MULTICAST_CAM_SIZE) {
E 8
		mode |= RCR_AM;	/* multicast */
D 8
		mhash[0] = mhash[1] = 0xffffffff;
	}
	else if (dp->mc_count > 0) {
E 8
I 8
		mhash[0] = mhash[1] = 0xffffffffU;
	} else if (dp->mc_count > 0) {
E 8
D 5
		/* use multicast cam. I guess multicast hash should be zero */
		mode |= RCR_AM;	/* multicast */
E 5
#ifndef USE_MCAST_CAM
I 5
		mode |= RCR_AM;	/* multicast */

E 5
		for (i = 0; i < dp->mc_count; i++) {
			j = dp->mc_list[i].hash;
D 5
			mhash[j/32] = 1 << (j % 32);
E 5
I 5
D 9
			mhash[j/32] |= 1 << (j % 32);
E 9
I 9
			mhash[j / 32] |= 1 << (j % 32);
E 9
E 5
		}
#else
D 4
		/* XXX - doesn't work */
E 4
I 4
D 5
		/* XXX - it doesn't work */
E 5
E 4
		/*
D 5
		 * VT612x has 64 entry CAMs for multicast address filtering
E 5
I 5
		 * Use multicast cam. I guess multicast hash should be zero.
		 * VT612x has 64 entry CAMs for multicast address filtering.
E 5
		 */
D 5
		bzero(mcmask, sizeof(mcmask));
E 5

D 5
		for (i = 0; i < dp->mc_count; i++) {
			/* enable cam port for writing multicast addresses */
			OUTB(dp, CAMCR, CAMCR_SEL_DATA);
E 5
I 5
		/* RCR_AP bit must be set to enable the CAM filter. */
		mode |= RCR_AP;
E 5

I 5
		/* enable cam port for writing multicast addresses */
		OUTB(dp, CAMCR, CAMCR_SEL_DATA);

		for (i = 0; i < dp->mc_count; i++) {
E 5
			/* write cam index */
			OUTB(dp, CAMADDR, CAMADDR_EN | i);

			/* write a multicast address into cam */
			mac = dp->mc_list[i].addr.ether_addr_octet;
			for (j = 0; j < ETHERADDRL; j++) {
				OUTB(dp, MAR + j, mac[j]);
			}
D 9
			mcmask[i/8] |= 1 << (i % 8);
E 9
I 9
			mcmask[i / 8] |= 1 << (i % 8);
E 9

			/* issue a cam write command */
D 4
			FLSHB(dp, MAR);
			OUTB(dp, CAMCR, CAMCR_SEL_DATA | CAMCR_WR);
			FLSHB(dp, CAMCR);
E 4
I 4
D 5
			OUTB(dp, CAMCR, INB(dp, CAMCR) | CAMCR_WR);
E 4

E 5
I 5
			OUTB(dp, CAMCR, CAMCR_SEL_DATA | CAMCR_WR);
			FLSHB(dp, CAMCR);
E 5
			drv_usecwait(10);
I 5
#if DEBUG_LEVEL > 3
			/* issue a cam read command */
			OUTB(dp, CAMCR, CAMCR_SEL_DATA | CAMCR_RD);
			FLSHB(dp, CAMCR);
			drv_usecwait(10);
E 5

D 5
			OUTB(dp, CAMADDR, 0);
			OUTB(dp, CAMCR, CAMCR_SEL_MAR);

D 4
			DPRINTF(2, (CE_CONT,
E 4
I 4
			DPRINTF(0, (CE_CONT,
E 5
I 5
			cmn_err(CE_CONT,
E 5
E 4
D 8
		"!%s: rx_fitler: mcast: %02x:%02x:%02x:%02x:%02x:%02x added",
D 5
			dp->name,
			mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]));
E 5
I 5
				dp->name,
				INB(dp, MAR + 0), INB(dp, MAR + 1),
				INB(dp, MAR + 2), INB(dp, MAR + 3),
				INB(dp, MAR + 4), INB(dp, MAR + 5));
E 8
I 8
			    "!%s: rx_fitler:"
			    " mcast: %02x:%02x:%02x:%02x:%02x:%02x added",
			    dp->name,
			    INB(dp, MAR + 0), INB(dp, MAR + 1),
			    INB(dp, MAR + 2), INB(dp, MAR + 3),
			    INB(dp, MAR + 4), INB(dp, MAR + 5));
E 8
#endif
E 5
		}
D 5

		/* setup multicast cam mask */
		OUTB(dp, CAMCR, CAMCR_SEL_MASK);
		OUTB(dp, CAMADDR, CAMADDR_EN);
		for (i = 0; i < 8; i++) {
			OUTB(dp, MAR + i, mcmask[i]);
		}
E 5
I 5
		/* close to access multicast CAM */
E 5
		OUTB(dp, CAMADDR, 0);
		OUTB(dp, CAMCR, CAMCR_SEL_MAR);
D 9
#endif
E 9
I 9
#endif /* USE_MCAST_CAM */
E 9
	}

D 9
	if (dp->mtu > 1500) {
		/* accept long packets */
		mode |= RCR_AL;
	}

E 9
	/* set my mac address */
	mac = &dp->cur_addr.ether_addr_octet[0];
D 8
	if (bcmp(lp->mac_addr, mac, ETHERADDRL) != 0) {
E 8
I 8
	if (bcmp(lp->mac_addr, mac, ETHERADDRL)) {
E 8
		for (i = 0; i < ETHERADDRL; i++) {
			OUTB(dp, PAR + i, mac[i]);
			lp->mac_addr[i] = mac[i];
		}
	}

I 5
D 8
	if ((mode & RCR_AP) != 0) {
E 8
I 8
	if (mode & RCR_AP) {
E 8
		/* setup multicast cam mask */
		OUTB(dp, CAMCR, CAMCR_SEL_MASK);
		OUTB(dp, CAMADDR, CAMADDR_EN);
		for (i = 0; i < 8; i++) {
			OUTB(dp, MAR + i, mcmask[i]);
		}
		OUTB(dp, CAMADDR, 0);
		OUTB(dp, CAMCR, CAMCR_SEL_MAR);
	}

E 5
D 8
	if ((mode & RCR_AM) != 0) {
E 8
I 8
	if (mode & RCR_AM) {
E 8
D 5
		/* need to setup the multicast hash table */
E 5
I 5
		/* setup the multicast hash table */
E 5
		for (i = 0; i < 2; i++) {
			OUTL(dp, MAR + i*4, mhash[i]);
		}
	}

	/* install new rx filter mode */
	OUTB(dp, RCR, mode);
I 6

	return (GEM_SUCCESS);
E 6
}

D 6
static void
E 6
I 6
static int
E 6
vel_set_media(struct gem_dev *dp)
{
	uint32_t	val;
	int		speed;
D 8
	struct vel_dev	*lp = (struct vel_dev *)dp->private;
E 8
I 8
	struct vel_dev	*lp = dp->private;
E 8

D 4
	DPRINTF(2, (CE_CONT, "!%s: vel_set_media: called at time:%d, "
		"active:%d, GMCR:%b",
E 4
I 4
D 8
	DPRINTF(0, (CE_CONT, "!%s: vel_set_media: called at time:%d, "
		"active:%d, REVID:%02x, TCR:%02x, GMCR:%b",
E 4
		dp->name, ddi_get_lbolt(),
D 4
		dp->nic_active, INB(dp, GMCR), GMCR_BITS));
E 4
I 4
D 6
		dp->nic_active,
E 6
I 6
		dp->mac_active,
E 6
		INB(dp, REVID), INB(dp, TCR), INB(dp, GMCR), GMCR_BITS));
E 8
I 8
	DPRINTF(1, (CE_CONT, "!%s: %s: called at time:%d, "
	    "active:%d, REVID:%02x, TCR:%02x, GMCR:%b",
	    dp->name, __func__, ddi_get_lbolt(),
	    dp->mac_active,
	    INB(dp, REVID), INB(dp, TCR), INB(dp, GMCR), GMCR_BITS));
E 8
E 4

	val = INB(dp, GMCR) | GMCR_FCMODE;

	/* select PHY, aka, speed */
I 4
	val &= ~GMCR_FCGMII;
E 4
	if (dp->speed == GEM_SPD_1000) {
		val |= GMCR_FCGMII;
	}

	/* select duplex */
I 4
	val &= ~GMCR_FCFDX;
E 4
	if (dp->full_duplex) {
		val |= GMCR_FCFDX;
	}

	OUTB(dp, GMCR, val);

	/* flow control */
D 8
	switch(dp->flow_control) {
E 8
I 8
	switch (dp->flow_control) {
E 8
	case FLOW_CONTROL_SYMMETRIC:
		val = CR_FDXTFCEN | CR_FDXRFCEN;
		break;

	case FLOW_CONTROL_TX_PAUSE:
		val = CR_FDXTFCEN;
		break;

	case FLOW_CONTROL_RX_PAUSE:
		val = CR_FDXRFCEN;
		break;

	case FLOW_CONTROL_NONE:
	default:
		val = 0;
		break;
	}
D 8
	OUTL(dp,CR_CLR, (CR_FDXTFCEN | CR_FDXRFCEN | CR_HDXFCEN) & ~val);
E 8
I 8
D 9
#ifdef notdef	/* test for no flow control */
	val = 0;
#endif
E 9
I 9

E 9
	OUTL(dp, CR_CLR, (CR_FDXTFCEN | CR_FDXRFCEN | CR_HDXFCEN) & ~val);
E 8
D 4
	OUTL(dp,CR_SET, val);
E 4
I 4
	OUTL(dp, CR_SET, val);
E 4

	/* select heartbeat for 10m half */
	val = INB(dp, TESTCFG) | TESTCFG_HBDIS;
D 4
	if (!dp->full_duplex && dp->speed == GEM_SPD_10) {
E 4
I 4
	if ((!dp->full_duplex) && dp->speed == GEM_SPD_10) {
E 4
		val &= ~TESTCFG_HBDIS;
	}
	OUTB(dp, TESTCFG, val);

	/* workaround for older revisions */
	if (INB(dp, REVID) < REVID_VT3216_A0) {
		val = INB(dp, TCR) & ~TCR_TB2BDIS;
		if (dp->full_duplex) {
			val |= TCR_TB2BDIS;
		}
		OUTB(dp, TCR, val);
	}
I 6
D 8

E 8
I 8
D 9
#ifdef notdef
E 9
I 9

E 9
	if (lp->revid >= REVID_VT3216_A0) {
I 9
		/* XXX - adaptive interrupt doesn't seem to work */
#if 0
E 9
		if (dp->speed == GEM_SPD_1000 || dp->speed == GEM_SPD_100) {
			OUTB(dp, TQETMR, 0x59); /* 100us */
			OUTB(dp, TQETMR, 0x14);	/* 20us */
		} else {
			OUTB(dp, TQETMR, 0x00);
			OUTB(dp, TQETMR, 0x00);
		}
D 9
	}
E 9
I 9
#else
		OUTB(dp, TQETMR, 0x00);
		OUTB(dp, TQETMR, 0x00);
E 9
#endif
I 9
	}
E 9
E 8
	return (GEM_SUCCESS);
E 6
}

D 6
static void
E 6
I 6
static int
E 6
E 3
vel_start_chip(struct gem_dev *dp)
{
D 8
	struct vel_dev	*lp = (struct vel_dev *)dp->private;
E 8
I 8
	struct vel_dev	*lp = dp->private;
E 8

D 6
	DPRINTF(2, (CE_CONT, "!%s: vel_start_chip: called at time:%d",
		dp->name, ddi_get_lbolt()));
E 6
I 6
D 8
	DPRINTF(2, (CE_CONT, "!%s: %s: called at time:%d",
		dp->name, __func__, ddi_get_lbolt()));
E 8
I 8
	DPRINTF(1, (CE_CONT, "!%s: %s: called at time:%d",
	    dp->name, __func__, ddi_get_lbolt()));
E 8
E 6

	/* Kick TX and RX */
D 4
	if (lp->rxbuf_added > 0) {
		OUTW(dp, RBRDU, lp->rxbuf_added);
		lp->rxbuf_added = 0;
	}
E 4
I 4
D 6
	OUTW(dp, RBRDU, RX_BUF_SIZE);

E 6
E 4
	OUTL(dp, CR_CLR, CR_STOP);
	OUTL(dp, CR_SET, CR_TXON | CR_RXON | CR_DPOLL | CR_STRT);

D 8
	/* clear ISR */
	OUTL(dp, ISR, 0xffffffff);

E 8
I 8
	/* enable interrupt mask */
	lp->imr = OUR_INTR_BITS;
I 9
#ifdef CONFIG_POLLING
	lp->imr |= ISR_PRX;
#else
	lp->imr |= ISR_PPRX;
#endif
	DPRINTF(0, (CE_CONT, "!%s: %s: imr:%b",
	    dp->name, __func__, lp->imr, ISR_BITS));

E 9
E 8
	if ((dp->misc_flag & GEM_NOINTR) == 0) {
D 8
		/* enable interrupt mask */
E 8
I 8
		OUTL(dp, IMR, lp->imr);
E 8
		OUTL(dp, CR_SET, CR_GINTMSK1);
	}
I 6

	return (GEM_SUCCESS);
E 6
}

D 6
static void
E 6
I 6
static int
E 6
vel_stop_chip(struct gem_dev *dp)
{
D 8
	struct vel_dev	*lp = (struct vel_dev *)dp->private;
E 8
I 8
	struct vel_dev	*lp = dp->private;
E 8

D 6
	DPRINTF(2, (CE_CONT, "!%s: vel_stop_chip: called at time:%d",
		dp->name, ddi_get_lbolt()));
E 6
I 6
D 9
	DPRINTF(2, (CE_CONT, "!%s: %s: called at time:%d",
E 9
I 9
	DPRINTF(1, (CE_CONT, "!%s: %s: called at time:%d",
E 9
D 8
		dp->name, __func__, ddi_get_lbolt()));
E 8
I 8
	    dp->name, __func__, ddi_get_lbolt()));
E 8
E 6

	/* Disable interrupts by clearing the interrupt mask */
	if ((dp->misc_flag & GEM_NOINTR) == 0) {
		OUTL(dp, CR_CLR, CR_GINTMSK1);
D 8
		lp->imr = 0;
		OUTL(dp, IMR, lp->imr);
E 8
I 8
		OUTL(dp, IMR, 0);
E 8
	}

	/* Stop Tx and Rx processes in the chip. */
	OUTL(dp, CR_SET, CR_STOP);
D 8
	OUTW(dp, TDCSR_CLR, 0xffff);
	OUTB(dp, RDCSR_CLR, 0xff);
E 8
I 8
	OUTW(dp, TDCSR_CLR, 0xffffU);
	OUTB(dp, RDCSR_CLR, 0xffU);
E 8
D 6
#ifdef notdef
	OUTL(dp, CR_CLR, CR_TXON | CR_RXON | CR_DPOLL | CR_STRT);
#endif
E 6
I 6

D 8
	/* clear potential bogus interrupts */
E 6
	OUTL(dp, ISR, 0xffffffff);
I 6
	FLSHL(dp, ISR);

E 8
	return (GEM_SUCCESS);
E 6
}

#ifdef DEBUG_LEVEL
static uint16_t
vel_read_eeprom(struct gem_dev *dp, uint_t offset)
{
	int		i;
	uint16_t	ret;
	uint8_t		chip_select;
	uint8_t		di;
	uint8_t		cfgc_saved;

D 4
#define	VEL_EEPROM_DELAY(dp)	{INB(dp, EECSR); INB(dp, EECSR);}
E 4
I 4
D 8
#define	VEL_EEPROM_DELAY(dp)	\
	{volatile uint32_t x; x = INB(dp, EECSR); x = INB(dp, EECSR);}
E 8
I 8
#define	VEL_EEPROM_DELAY(dp)	{ \
	volatile uint32_t x; x = INB(dp, EECSR); x = INB(dp, EECSR); \
}
E 8
E 4
#define	EE93C46_READ	6

	/* enable eeprom direct programing */
	cfgc_saved = INB(dp, CFGC);
	OUTB(dp, CFGC, cfgc_saved | CFGC_EELOAD);
	VEL_EEPROM_DELAY(dp);

	/* ensure de-assert chip select */
	chip_select = EECSR_DPM;
	OUTB(dp, EECSR, chip_select);
	VEL_EEPROM_DELAY(dp);

	/* assert chip select */
	chip_select |= EECSR_ECS;
	OUTB(dp, EECSR, chip_select);
	VEL_EEPROM_DELAY(dp);

	/* make a read command for eeprom */
	offset = (offset & 0x3f) | (EE93C46_READ << 6);

	for (i = 10; i >= 0; i--) {
		/* send 1 bit */
		di = ((offset >> i) & 1) << EECSR_EDI_SHIFT;

		OUTB(dp, EECSR, chip_select | di);
		VEL_EEPROM_DELAY(dp);

		OUTB(dp, EECSR, chip_select | di | EECSR_ECK);
		VEL_EEPROM_DELAY(dp);
	}

	OUTB(dp, EECSR, chip_select);
	VEL_EEPROM_DELAY(dp);

	/* get the reply and construct a 16bit value */
	ret = 0;
	for (i = 0; i < 16; i++) {
		/* Get 1 bit */
		OUTB(dp, EECSR, chip_select | EECSR_ECK);
		VEL_EEPROM_DELAY(dp);

		ret = (ret << 1)
		    | ((INB(dp, EECSR) >> EECSR_EDO_SHIFT) & 1);

		OUTB(dp, EECSR, chip_select);
		VEL_EEPROM_DELAY(dp);
	}

	/* negate chip_select */
	OUTB(dp, EECSR, EECSR_DPM);
	VEL_EEPROM_DELAY(dp);

	OUTB(dp, EECSR, 0);
	VEL_EEPROM_DELAY(dp);

	/* disable eeprom direct programming */
	OUTB(dp, CFGC, cfgc_saved);
	VEL_EEPROM_DELAY(dp);

D 6
	return ret;
E 6
I 6
	return (ret);
E 6
}

static void
vel_eeprom_dump(struct gem_dev *dp)
{
	int		i;
	uint16_t	prom[0x10];

	for (i = 0; i < 0x10; i++) {
		prom[i] = vel_read_eeprom(dp, i);
	}

	cmn_err(CE_CONT, "!%s: eeprom dump:", dp->name);
	for (i = 0; i < 0x10; i += 4) {
D 8
		cmn_err(CE_CONT, "!0x%02x: 0x%04x 0x%04x 0x%04x 0x%04x", 
			i, prom[i], prom[i + 1], prom[i + 2], prom[i + 3]);
E 8
I 8
		cmn_err(CE_CONT, "!0x%02x: 0x%04x 0x%04x 0x%04x 0x%04x",
		    i, prom[i], prom[i + 1], prom[i + 2], prom[i + 3]);
E 8
	}
}
#endif /* DEBUG_LEVEL */

static int
vel_attach_chip(struct gem_dev *dp)
{
I 2
D 9
	ddi_acc_handle_t	conf_handle;
E 9
E 2
	int		i;
	uint_t		val;
D 9
	uint8_t		*mac;
E 9
D 2
	ddi_acc_handle_t	conf_handle;
E 2
D 8
	struct vel_dev	*lp = (struct vel_dev *)dp->private;
E 8
I 8
	struct vel_dev	*lp = dp->private;
E 8

D 8
	DPRINTF(2, (CE_CONT, "!%s: vel_attach_chip: called at time:%d",
		dp->name, ddi_get_lbolt()));
E 8
I 8
	DPRINTF(2, (CE_CONT, "!%s: %s: called at time:%d",
	    dp->name, __func__, ddi_get_lbolt()));
E 8

D 6
#ifdef notdef	/* test for setting mac address */
	if (gem_get_mac_addr_conf(dp)) {
		return 0;
	}
#endif /* notdef */
E 6
D 9
	mac = dp->dev_addr.ether_addr_octet;

E 9
	DPRINTF(4, (CE_CONT, "!%s: %d.%09d",
D 8
		dp->name, hrestime.tv_sec, hrestime.tv_nsec));
E 8
I 8
	    dp->name, hrestime.tv_sec, hrestime.tv_nsec));
E 8

	/* we use eeprom autoload function to get mac address */
	OUTB(dp, EECSR, INB(dp, EECSR) | EECSR_AUTOLD);

	/*
D 9
	 * Don't access velocity for 20mS.
	 * It doesn't respond to any PCI transactions
	 * while it loads eeprom. On sparc, it will cause
	 * a bus error.
E 9
I 9
	 * XXX - Don't access velocity for 20mS.
	 * It doesn't respond to any PCI transactions while it
	 * loads eeprom. On sparc, it may cause bus error.
E 9
	 */
D 9
	drv_usecwait(20000);
E 9
I 9
	delay(drv_usectohz(20000));
E 9

	DPRINTF(4, (CE_CONT, "!%s: %d.%09d",
D 8
		dp->name, hrestime.tv_sec, hrestime.tv_nsec));
E 8
I 8
	    dp->name, hrestime.tv_sec, hrestime.tv_nsec));
E 8

D 6
	i = 0;
	while ((INB(dp, EECSR) & EECSR_AUTOLD) != 0) {
		if (i++ > 4000) {
E 6
I 6
D 8
	for (i = 0; (INB(dp, EECSR) & EECSR_AUTOLD) != 0; i++) {
E 8
I 8
	for (i = 0; INB(dp, EECSR) & EECSR_AUTOLD; i++) {
E 8
		if (i > 4000) {
E 6
D 9
			break;
E 9
I 9
			cmn_err(CE_WARN,
			    "!%s: %s: timeout: initializing the nic",
			    dp->name, __func__);
			return (GEM_FAILURE);
E 9
		}
		drv_usecwait(10);
	}
	DPRINTF(4, (CE_CONT, "!%s: %d.%09d",
D 8
		dp->name, hrestime.tv_sec, hrestime.tv_nsec));
E 8
I 8
	    dp->name, hrestime.tv_sec, hrestime.tv_nsec));
E 8

I 9
	/* get factory mac address */
E 9
	for (i = 0; i < ETHERADDRL; i++) {
D 8
		mac[i]= INB(dp, PAR + i);
E 8
I 8
D 9
		mac[i] = INB(dp, PAR + i);
E 9
I 9
		dp->dev_addr.ether_addr_octet[i] = INB(dp, PAR + i);
E 9
E 8
	}
D 9
	bcopy(mac, lp->mac_addr, ETHERADDRL);
E 9
I 9
	bcopy(dp->dev_addr.ether_addr_octet, lp->mac_addr, ETHERADDRL);
E 9

#if DEBUG_LEVEL > 2
	vel_eeprom_dump(dp);
#endif /* DEBUG_LEVEL */

	/* read default address of PHY in eeprom */
D 9
	/* this should be moved into vel_mii_init for DDI_RESUME */
E 9
	dp->mii_phy_addr = INB(dp, MIIADR) & MIIADR_PHYAD;
D 3
	DPRINTF(0, (CE_CONT, "!%s: default PHY address:%d",
E 3
I 3
	DPRINTF(2, (CE_CONT, "!%s: default PHY address:%d",
E 3
D 8
			dp->name, dp->mii_phy_addr));
E 8
I 8
	    dp->name, dp->mii_phy_addr));
E 8

D 2
	if (dp->rxthr <= 128) {
		lp->rft = RFT_128;
	} else if (dp->rxthr <= 512) {
		lp->rft = RFT_512;
	} else if (dp->rxthr <= 1024) {
		lp->rft = RFT_1024;
	} else {
		lp->rft = RFT_SF;
	}

E 2
D 8
	val = max(dp->txmaxdma, dp->rxmaxdma);
I 2
D 3
	val = max(val, 512);	/* XXX - 256:690Mbps, 512:760Mbps */
E 3
I 3
D 4
	val = max(val, 256);	/* XXX - 256:710Mbps, 512:760Mbps */
E 4
I 4
D 5
	val = max(val, 512);	/* XXX - 256:710Mbps, 512:760Mbps */
E 5
I 5
D 6
	val = max(val, 512);	/* XXX -  512:690Mbps */
E 6
I 6
D 7
	val = max(val, 1024);	/* recommendation: 256 */
E 7
I 7
	val = max(val, 256);	/* recommendation: 256 */
E 8
I 8
D 9
	if (lp->pcie) {
		val = dp->mtu;	/* no limit */
	} else {
		val = max(dp->txmaxdma, dp->rxmaxdma);
		val = max(val, 256);	/* recommendation: 256 */
	}
E 9
I 9
	val = dp->mtu;	/* vendor recommendation: no limit */
E 9
E 8
E 7
E 6
E 5
E 4
E 3
E 2

	if (val <= 32) {
		lp->maxdma = DMA_32;
	} else if (val <= 64) {
		lp->maxdma = DMA_64;
	} else if (val <= 128) {
		lp->maxdma = DMA_128;
	} else if (val <= 256) {
		lp->maxdma = DMA_256;
	} else if (val <= 512) {
		lp->maxdma = DMA_512;
	} else if (val <= 1024) {
		lp->maxdma = DMA_1024;
	} else {
		lp->maxdma = DMA_NOLIMIT;
	}

I 2
D 4
	dp->rxthr = max(dp->rxthr, 3*val/4);
E 4
I 4
D 8
	dp->rxthr = max(dp->rxthr, (3*val)/4);
E 4

E 8
I 8
D 9
	if (lp->pcie) {
		dp->rxthr = 128;
		dp->rxthr = dp->mtu;
	} else {
		dp->rxthr = max(dp->rxthr, (3*val)/4);
	}
E 9
E 8
	if (dp->rxthr <= 128) {
D 9
		lp->rft = RFT_128;
E 9
I 9
		lp->rft = RFT_128;	/* vendor recommendation */
E 9
	} else if (dp->rxthr <= 512) {
		lp->rft = RFT_512;
	} else if (dp->rxthr <= 1024) {
		lp->rft = RFT_1024;
	} else {
		lp->rft = RFT_SF;
	}
D 8

E 8
I 8
D 9
#if 0
E 8
E 2
	/* set pci latency timer to 0x40 */
	if (pci_config_setup(dp->dip, &conf_handle) != DDI_SUCCESS) {
D 8
		cmn_err(CE_WARN,
		"!%s: vel_attach_chip: pci_config_setup failed",
			dp->name);
	}
	else {
E 8
I 8
		cmn_err(CE_WARN, "!%s: %s: pci_config_setup failed",
		    dp->name, __func__);
	} else {
E 8
		pci_config_put8(conf_handle, PCI_CONF_LATENCY_TIMER, 0x40);
		pci_config_teardown(&conf_handle);
	}
D 8

E 8
I 8
#endif
E 8
I 6
#ifdef GEM_CONFIG_CKSUM_OFFLOAD
E 9
I 9

	dp->misc_flag |= GEM_POLL_RXONLY;
#ifdef CONFIG_CKSUM_OFFLOAD
E 9
	dp->misc_flag |= (GEM_CKSUM_FULL_IPv4 | GEM_CKSUM_HEADER_IPv4);
#endif
D 9
#ifdef CONFIG_HW_VLAN
E 9
I 9
#ifdef CONFIG_VLAN_HW
E 9
	dp->misc_flag |= GEM_VLAN_HARD;
#else
	dp->misc_flag |= GEM_VLAN_SOFT;
#endif

E 6
I 2
D 9
#if 0
{
	clock_t	tim;
	int	i;
	i = 100000;
#define	TEST_COUNT	30000
	tim = ddi_get_lbolt();

	OUTB(dp, GMCR, INB(dp, GMCR) | GMCR_TMR1US);

	OUTW(dp, SOFT_TMR1, TEST_COUNT);
	OUTL(dp, CR_SET, CR_TM1EN);
	while ((INL(dp, ISR) & ISR_TMR1) == 0) {
		if (--i == 0) {
D 8
			cmn_err(CE_CONT, "%s: soft_timer0 timeout", dp->name);
E 8
I 8
			cmn_err(CE_CONT, "!%s: soft_timer0 timeout", dp->name);
E 8
			break;
		}
		drv_usecwait(100);
	}
	tim = (ddi_get_lbolt() - tim);

	if (i > 0) {
D 8
		cmn_err(CE_CONT, "%s: soft_timer1 resolution in 10mS: %d",
			dp->name, tim > 0 ? TEST_COUNT/tim: 9999999);
E 8
I 8
		cmn_err(CE_CONT, "!%s: soft_timer1 resolution in 10mS: %d",
		    dp->name, tim > 0 ? TEST_COUNT/tim: 9999999);
E 8
	}
	OUTL(dp, CR_CLR, CR_TM0EN);
D 8
	
E 8
I 8

E 8
}
#endif
E 9
E 2
D 6
	return 0;
E 6
I 6
	return (GEM_SUCCESS);
E 6
}

D 3
static uint_t
vel_mcast_hash(struct gem_dev *dp, uint8_t *addr)
{
	/* hash key is higher 6 bits of msb in crc */
	return gem_ether_crc_be(addr) >> (32 - 6);
}

E 3
D 6
static void
E 6
I 6
static int
E 6
D 3
vel_set_rx_filter(struct gem_dev *dp)	
{
	uint8_t		mode;
	int		i, j;
	uint32_t	mhash[2];
	uint8_t		mcmask[MULTICAST_CAM_SIZE/8];
	uint8_t		*mac;
	struct vel_dev	*lp = (struct vel_dev *)dp->private;

D 2
	DPRINTF(2, (CE_CONT, "!%s: vel_set_rx_filter: called at time:%d, "
		"active:%d, rxmode:%b",
E 2
I 2
	DPRINTF(0, (CE_CONT, "!%s: vel_set_rx_filter: called at time:%d, "
		"active:%d, rxmode:%b mc_count:%d",
E 2
		dp->name, ddi_get_lbolt(),
D 2
		dp->nic_active, dp->rxmode, "\020\002AllMulti\001Promisc"));
E 2
I 2
		dp->nic_active, dp->rxmode, "\020\002AllMulti\001Promisc",
		dp->mc_count));
E 2

	/* temporally disable rx filter before changing it */
	mode = RCR_SEP | RCR_AR;
	OUTB(dp, RCR, mode);

	mode |= RCR_AB;	/* broadcast */
	mhash[0] = mhash[1] = 0;
	if ((dp->rxmode & RXMODE_PROMISC) != 0) {
		mode |=RCR_PRO	/* promiscous */
                     | RCR_AM;	/* muticast */
		mhash[0] = mhash[1] = 0xffffffff;
	}
D 2
	else if ((dp->rxmode & RXMODE_ALLMULTI) != 0 ||
E 2
I 2
	else if (/*(dp->rxmode & RXMODE_ALLMULTI) != 0 || */
E 2
				dp->mc_count > MULTICAST_CAM_SIZE) {
		mode |= RCR_AM;	/* multicast */
		mhash[0] = mhash[1] = 0xffffffff;
	}
	else if (dp->mc_count > 0) {
		/* use multicast cam. I guess multicast hash should be zero */
		mode |= RCR_AM;	/* multicast */
D 2

E 2
I 2
#ifndef USE_MCAST_CAM
		for (i = 0; i < dp->mc_count; i++) {
			j = dp->mc_list[i].hash;
			mhash[j/32] = 1 << (j % 32);
		}
#else
		/* XXX - doesn't work */
E 2
		/*
		 * VT612x has 64 entry CAMs for multicast address filtering
		 */
		bzero(mcmask, sizeof(mcmask));

D 2
		/* enable cam port for writing multicast addresses */
		OUTB(dp, CAMCR, CAMCR_SEL_DATA);

E 2
		for (i = 0; i < dp->mc_count; i++) {
I 2
			/* enable cam port for writing multicast addresses */
			OUTB(dp, CAMCR, CAMCR_SEL_DATA);

E 2
			/* write cam index */
			OUTB(dp, CAMADDR, CAMADDR_EN | i);

			/* write a multicast address into cam */
			mac = dp->mc_list[i].addr.ether_addr_octet;
			for (j = 0; j < ETHERADDRL; j++) {
				OUTB(dp, MAR + j, mac[j]);
			}
			mcmask[i/8] |= 1 << (i % 8);

			/* issue a cam write command */
I 2
			FLSHB(dp, MAR);
E 2
			OUTB(dp, CAMCR, CAMCR_SEL_DATA | CAMCR_WR);
I 2
			FLSHB(dp, CAMCR);

E 2
			drv_usecwait(10);
I 2

			OUTB(dp, CAMADDR, 0);
			OUTB(dp, CAMCR, CAMCR_SEL_MAR);

			DPRINTF(0, (CE_CONT,
		"%s: rx_fitler: mcast: %02x:%02x:%02x:%02x:%02x:%02x added",
			dp->name,
			mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]));
E 2
		}

		/* setup multicast cam mask */
		OUTB(dp, CAMCR, CAMCR_SEL_MASK);
D 2
		OUTB(dp, CAMADDR, CAMADDR_EN | 0);
E 2
I 2
		OUTB(dp, CAMADDR, CAMADDR_EN);
E 2
		for (i = 0; i < 8; i++) {
			OUTB(dp, MAR + i, mcmask[i]);
		}
		OUTB(dp, CAMADDR, 0);
		OUTB(dp, CAMCR, CAMCR_SEL_MAR);
I 2
#endif
E 2
	}

	if (dp->mtu > 1500) {
		/* accept long packets */
		mode |= RCR_AL;
	}

	/* set my mac address */
	mac = &dp->dev_addr.ether_addr_octet[0];
	if (bcmp(lp->mac_addr, mac, ETHERADDRL) != 0) {
		for (i = 0; i < ETHERADDRL; i++) {
			OUTB(dp, PAR + i, mac[i]);
			lp->mac_addr[i] = mac[i];
		}
	}

	if ((mode & RCR_AM) != 0) {
		/* need to setup the multicast hash table */
		for (i = 0; i < 2; i++) {
			OUTL(dp, MAR + i*4, mhash[i]);
		}
	}

	/* install new rx filter mode */
	OUTB(dp, RCR, mode);
}

static void
vel_set_media(struct gem_dev *dp)
{
	uint32_t	val;
I 2
	int		speed;
E 2
	struct vel_dev	*lp = (struct vel_dev *)dp->private;

	DPRINTF(0, (CE_CONT, "!%s: vel_set_media: called at time:%d, "
		"active:%d, GMCR:%b",
		dp->name, ddi_get_lbolt(),
		dp->nic_active, INB(dp, GMCR), GMCR_BITS));

D 2
	val = GMCR_FCMODE;
E 2
I 2
	val = INB(dp, GMCR) | GMCR_FCMODE;
E 2

	/* select PHY, aka, speed */
	if (dp->speed == GEM_SPD_1000) {
		val |= GMCR_FCGMII;
	}

	/* select duplex */
	if (dp->full_duplex) {
		val |= GMCR_FCFDX;
	}

	OUTB(dp, GMCR, val);

	/* flow control */
	switch(dp->flow_control) {
	case FLOW_CONTROL_SYMMETRIC:
		val = CR_FDXTFCEN | CR_FDXRFCEN;
		break;

	case FLOW_CONTROL_TX_PAUSE:
		val = CR_FDXTFCEN;
		break;

	case FLOW_CONTROL_RX_PAUSE:
		val = CR_FDXRFCEN;
		break;

	case FLOW_CONTROL_NONE:
	default:
		val = 0;
		break;
	}
	OUTL(dp,CR_CLR, (CR_FDXTFCEN | CR_FDXRFCEN | CR_HDXFCEN) & ~val);
	OUTL(dp,CR_SET, val);

	/* select heartbeat for 10m half */
	val = INB(dp, TESTCFG) | TESTCFG_HBDIS;
	if (!dp->full_duplex && dp->speed == GEM_SPD_10) {
		val &= ~TESTCFG_HBDIS;
	}
	OUTB(dp, TESTCFG, val);

	/* workaround for older revisions */
	if (INB(dp, REVID) < REVID_VT3216_A0) {
		val = INB(dp, TCR) & ~TCR_TB2BDIS;
		if (dp->full_duplex) {
			val |= TCR_TB2BDIS;
		}
		OUTB(dp, TCR, val);
	}
}

static void
E 3
vel_get_stats(struct gem_dev *dp)
{
D 8
	volatile int	x;
	struct vel_dev	*lp = (struct vel_dev *)dp->private;
I 6

E 8
I 8
	/* not implemented */
E 8
	return (GEM_SUCCESS);
E 6
}

/*
 * discriptor manupiration
 */
static int
D 4
vel_tx_desc_write(struct gem_dev *dp, uint_t slot,
		ddi_dma_cookie_t *dmacookie, int frags, uint32_t intreq)
E 4
I 4
vel_tx_desc_write(struct gem_dev *dp, int slot,
D 8
		ddi_dma_cookie_t *dmacookie, int frags, uint32_t flags)
E 8
I 8
    ddi_dma_cookie_t *dmacookie, int frags, uint64_t flags)
E 8
E 4
{
	int			i;
I 4
D 5
	uint32_t		len;
E 5
	uint32_t		tdes1;
E 4
D 5
	int			total_size;
E 5
I 5
D 6
	int32_t			total_size;
E 6
I 6
	uint64_t		total_size;
E 6
E 5
D 4
	struct td_buf		*tbp;
E 4
	struct tx_desc		*tdp;
D 4
	ddi_dma_cookie_t	*dcp;
E 4
I 4
D 6
	struct td_buf		*tbp;
E 6
I 6
D 9
#ifdef CONFIG_HW_VLAN
E 9
I 9
	uint64_t		tmp;
#ifdef CONFIG_VLAN_HW
E 9
	uint64_t		vtag;
#endif
E 6
D 5
	uint64_t		daddr;
E 5
E 4
D 8
	struct vel_dev		*lp = (struct vel_dev *)dp->private;
E 8
I 8
	struct vel_dev		*lp = dp->private;
E 8
I 2
D 4
	ddi_acc_handle_t	h = dp->desc_acc_handle;
E 4
E 2

#if DEBUG_LEVEL > 2
	cmn_err(CE_CONT,
D 6
	"!%s: vel_tx_desc_write time: %d, seqnum: %d, slot %d, frags: %d flags: %d",
		dp->name, ddi_get_lbolt(),
E 6
I 6
D 8
	"!%s: %s time: %d, seqnum: %d, slot %d, frags: %d flags: 0x%x",
		dp->name, __func__, ddi_get_lbolt(),
E 6
D 4
		dp->tx_desc_tail, slot, frags, intreq);
E 4
I 4
		dp->tx_desc_tail, slot, frags, flags);
E 8
I 8
	    "!%s: %s time: %d, seqnum: %d, slot %d, frags: %d flags: 0x%llx",
	    dp->name, __func__, ddi_get_lbolt(),
	    dp->tx_desc_tail, slot, frags, flags);
E 8
E 4
	for (i = 0; i < frags; i++) {
		cmn_err(CE_CONT, "!%d: addr: 0x%llx, len: 0x%x",
D 8
			i, dmacookie[i].dmac_laddress, dmacookie[i].dmac_size);
E 8
I 8
		    i, dmacookie[i].dmac_laddress, dmacookie[i].dmac_size);
E 8
	}
#endif
D 9
#if DEBUG_LEVEL > 3
E 9
I 9
#if DEBUG_LEVEL > 2
E 9
D 4
	intreq |= GEM_TXFLAG_INTR;
E 4
I 4
	flags |= GEM_TXFLAG_INTR;
E 4
#endif
	tdp = &((struct tx_desc *)dp->tx_ring)[slot];

	/*
	 * write tx descriptor(s)
	 */
D 4
	dcp = dmacookie;
E 4
D 6
	tbp = &tdp->td_bufs[0];
E 6
	total_size = 0;
D 4
	for (i = 0; i < frags; i++, dcp++, tbp++) {
D 2
		tbp->tbdes0 = LE32(dcp->dmac_address);
		tbp->tbdes1 = LE32((dcp->dmac_size << TBDES1_LEN_SHIFT)
E 2
I 2
		ddi_put32(h, &tbp->tbdes0, dcp->dmac_address);
		ddi_put32(h, &tbp->tbdes1, (dcp->dmac_size << TBDES1_LEN_SHIFT)
E 4
I 4
	i = frags - 1;
	do {
D 5
		daddr = dmacookie[i].dmac_address;
		len   = dmacookie[i].dmac_size;
E 5
I 5
		uint64_t	len;
D 6
#ifdef notdef
		uint64_t	daddr;
E 6
E 5

I 5
D 8
		len   = dmacookie[i].dmac_size;
E 8
I 8
		len = dmacookie[i].dmac_size;
E 8
D 6
		daddr = dmacookie[i].dmac_address;
E 5
		tbp[i].tbdes0 = LE32(daddr);
		tbp[i].tbdes1 = LE32((len << TBDES1_LEN_SHIFT)
E 4
E 2
#ifdef CONFIG_DAC
D 4
		|  (((uint32_t)(dcp->dmac_laddress >> 32)) & TBDES1_ADDRHI)
E 4
I 4
				|  (daddr >> 32)
E 4
#endif
				);
E 6
I 6
D 9
		tdp->tbdes[i] =
D 8
		    LE64((len << TBDES_LEN_SHIFT) | dmacookie[i].dmac_address);
E 8
I 8
		    LE_64((len << TBDES_LEN_SHIFT) | dmacookie[i].dmac_address);
E 9
E 8
E 6
D 4
		total_size += dcp->dmac_size;
E 4
I 4
		total_size += len;
I 9
D 10
		tmp = (len << TBDES_LEN_SHIFT) | dmacookie[i].dmac_address;
E 10
I 10
		tmp = (len << TBDES_LEN_SHIFT) | dmacookie[i].dmac_laddress;
E 10
		tdp->tbdes[i] = LE_64(tmp);
E 9
I 5
D 6
#else
		total_size += (len = dmacookie[i].dmac_size);
		* (uint64_t *) &tbp[i] = LE64(
			(len << (TBDES1_LEN_SHIFT + 32)) |
			dmacookie[i].dmac_laddress);
#endif
E 6
E 5
	} while (--i >= 0);
D 6

E 6
I 6
D 9
#ifndef CONFIG_OO
D 8
	if ((flags & GEM_TXFLAG_TAIL) == 0) {
		tdp->tbdes[0] |= LE64(TBDES_QUEUE);
E 8
I 8
	if (!(flags & GEM_TXFLAG_TAIL)) {
		tdp->tbdes[0] |= LE_64(TBDES_QUEUE);
E 8
	}
#endif
E 9
I 9

	tdp->tbdes[0] |= LE_64(TBDES_QUEUE);

E 9
E 6
	tdes1 = TDES1_TCPLS_NORMAL | ((frags + 1) << TDES1_CMDZ_SHIFT);
D 8
	if ((flags & GEM_TXFLAG_INTR) != 0) {
E 8
I 8
	if (flags & GEM_TXFLAG_INTR) {
E 8
		tdes1 |= TDES1_TCR_TIC;
E 4
	}
D 2
	tdp->tdes1 = LE32(((intreq & GEM_TXFLAG_INTR) ? TDES1_TCR_TIC : 0)
E 2
I 2
D 4
	ddi_put32(h, &tdp->tdes1,
			((intreq & GEM_TXFLAG_INTR) ? TDES1_TCR_TIC : 0)
E 2
			| TDES1_TCPLS_NORMAL
			| ((total_size > ETHERMAX) ? TDES1_TCR_JUMBO : 0)
			| ((frags + 1) << TDES1_CMDZ_SHIFT));
D 2
	tdp->tdes0 = LE32(TDES0_OWN | (total_size << TDES0_LEN_SHIFT));
E 2
I 2
	ddi_put32(h, &tdp->tdes0, TDES0_OWN | (total_size << TDES0_LEN_SHIFT));
E 4
I 4
	if (total_size > ETHERMAX) {
		tdes1 |= TDES1_TCR_JUMBO;
	}
E 4
E 2

D 4
	ddi_dma_sync(dp->desc_dma_handle,
		(off_t)(((caddr_t)tdp) - dp->rx_ring),
		sizeof(uint32_t)*2 + sizeof(struct td_buf)*frags,
		DDI_DMA_SYNC_FORDEV);
E 4
I 4
D 6
#ifdef CONFIG_CKSUM_OFFLOAD
E 6
I 6
D 9
#ifdef GEM_CONFIG_CKSUM_OFFLOAD
E 9
I 9
#ifdef CONFIG_CKSUM_OFFLOAD
E 9
E 6
D 8
#  if (TDES1_TXFLAG_IPv4 == (TDES1_TXFLAG_UDP << 1)) && \
      (TDES1_TXFLAG_IPv4 == (TDES1_TXFLAG_TCP << 2))
	tdes1 |= ((flags & (GEM_TXFLAG_IPv4 | GEM_TXFLAG_UDP | GEM_TXFLAG_TCP))
			>> GEM_TXFLAG_TCP_SHIFT) << TDES1_TCR_TCPCK_SHIFT;
#  else
	if ((flags & GEM_TXFLAG_IPv4) != 0) {
E 8
I 8
#if (TDES1_TXFLAG_IPv4 == (TDES1_TXFLAG_UDP << 1)) && \
	(TDES1_TXFLAG_IPv4 == (TDES1_TXFLAG_TCP << 2))
	tdes1 |=
	    ((flags & (GEM_TXFLAG_IPv4 | GEM_TXFLAG_UDP | GEM_TXFLAG_TCP))
	    >> GEM_TXFLAG_TCP_SHIFT) << TDES1_TCR_TCPCK_SHIFT;
#else
	if (flags & GEM_TXFLAG_IPv4) {
E 8
		tdes1 |= TDES1_TCR_IPCK;
	}
D 8
	if ((flags & GEM_TXFLAG_UDP) != 0) {
E 8
I 8
D 9
	if (flags & GEM_TXFLAG_UDP) {
E 8
		tdes1 |= TDES1_TCR_UDPCK;
	}
E 9
D 8
	if ((flags & GEM_TXFLAG_TCP) != 0) {
E 8
I 8
	if (flags & GEM_TXFLAG_TCP) {
E 8
		tdes1 |= TDES1_TCR_TCPCK;
I 9
	} else if (flags & GEM_TXFLAG_UDP) {
		tdes1 |= TDES1_TCR_UDPCK;
E 9
	}
D 8
#  endif
E 8
#endif
I 8
D 9
#endif /* GEM_CONFIG_CKSUM_OFFLOAD */
E 9
I 9
#endif /* CONFIG_CKSUM_OFFLOAD */
E 9

E 8
D 6
#ifdef CONFIG_VLAN
	if ((flags & GEM_TXFLAG_VTAG) != 0) {
		tdes1 |= TDES1_TCR_VETAG |
			 ((flags & GEM_TXFLAG_VTAG) >> GEM_TXFLAG_VTAG_SHIFT);
E 6
I 6
D 9
#ifdef CONFIG_HW_VLAN
D 8
	if ((vtag = ((flags & GEM_TXFLAG_VTAG)>>GEM_TXFLAG_VTAG_SHIFT)) != 0) {
E 8
I 8
	if (vtag = ((flags & GEM_TXFLAG_VTAG)>>GEM_TXFLAG_VTAG_SHIFT)) {
E 9
I 9
#ifdef CONFIG_VLAN_HW
	vtag = (flags & GEM_TXFLAG_VTAG) >> GEM_TXFLAG_VTAG_SHIFT;
	if (vtag) {
E 9
E 8
		tdes1 |= TDES1_TCR_VETAG | vtag;
E 6
	}
#endif
I 5

E 5
D 8
	tdp->tdes1 = LE32(tdes1);
	tdp->tdes0 = LE32(TDES0_OWN | (total_size << TDES0_LEN_SHIFT));
E 8
I 8
	tdp->tdes1 = LE_32(tdes1);
D 9
	tdp->tdes0 = LE_32(TDES0_OWN | (total_size << TDES0_LEN_SHIFT));
E 9
I 9
	tmp = TDES0_OWN | (total_size << TDES0_LEN_SHIFT);
	tdp->tdes0 = LE_32(tmp);
E 9
E 8
E 4

I 4
D 6
	return 1;
E 6
I 6
	return (1);
E 6
}

static void
vel_tx_start(struct gem_dev *dp, int start_slot, int nslot)
{
D 5
	struct tx_desc		*tdp;
	struct td_buf		*tbp;
	ddi_dma_cookie_t	*dcp;
	struct vel_dev		*lp = (struct vel_dev *)dp->private;
E 5
D 6
	int			i;
	int			slot;
D 5
	ddi_acc_handle_t	h = dp->desc_acc_handle;
E 5
I 5
	uint32_t		le32_queue;
E 6
I 6
D 9
	int		i;
E 9
	int		slot;
	uint64_t	le64_queue;
I 9
	uint_t		tx_ring_size = dp->gc.gc_tx_ring_size;
E 9
D 8
	struct vel_dev	*lp = (struct vel_dev *)dp->private;
E 8
I 8
	struct vel_dev	*lp = dp->private;
E 8
E 6
E 5

I 5
D 6
	le32_queue = LE32_CONST(TBDES1_QUEUE);

E 6
I 6
D 8
	le64_queue = LE64(TBDES_QUEUE);
E 8
I 8
	DPRINTF(1, (CE_CONT, "!%s: %s: called, mac_active:%x, imr:%b",
	    dp->name, __func__, dp->mac_active, lp->imr, ISR_BITS));

	le64_queue = LE_64(TBDES_QUEUE);
E 8
D 9
#ifdef CONFIG_OO
E 6
E 5
D 8
	for (i = start_slot + nslot - 1 ; i-- != start_slot; ) {
I 5
		struct tx_desc		*tdp;
E 8
I 8
	for (i = start_slot + nslot - 1; i-- != start_slot; ) {
		struct tx_desc	*tdp;
E 9
E 8

E 5
D 9
		slot = SLOT(i, TX_RING_SIZE);
D 6
		tdp = &((struct tx_desc *)dp->tx_ring)[slot];

D 5
		tdp->td_bufs[0].tbdes1 |= LE32(TBDES1_QUEUE);
E 5
I 5
		tdp->td_bufs[0].tbdes1 |= le32_queue;
E 6
I 6
D 8
		((struct tx_desc *) dp->tx_ring)[slot].tbdes[0] |= le64_queue;
E 8
I 8
		((struct tx_desc *)dp->tx_ring)[slot].tbdes[0] |= le64_queue;
E 8
E 6
E 5
	}
D 6

E 6
I 6
#endif
E 9
I 9
	/* remove QUEUE bit from the last descriptor */
	slot = SLOT(start_slot + nslot - 1, tx_ring_size);
	((struct tx_desc *)dp->tx_ring)[slot].tbdes[0] &= ~le64_queue;

E 9
E 6
	/* flush tx descriptors we made */
	gem_tx_desc_dma_sync(dp, start_slot, nslot, DDI_DMA_SYNC_FORDEV);

E 4
	/*
	 * kick Tx engine
D 9
	 *  (1) set Queue bit in td buffer[0] in the previous descriptor.
E 9
I 9
	 *  (1) set QUEUE bit to td buffer[0] in the previous descriptor.
E 9
	 *  (2) wake up the tx queue.
	 */
#ifdef TXTIMEOUT_TEST
	if ((vel_send_cnt++ % 100) == 99) {
		OUTL(dp, CR_CLR, CR_TXON);
	}
#endif
D 4
	tdp = &((struct tx_desc *)dp->tx_ring)[SLOT(slot - 1, TX_RING_SIZE)];
D 2
	tdp->td_bufs[0].tbdes1 |= LE32(TBDES1_QUEUE);
E 2
I 2
	ddi_put32(h, &tdp->td_bufs[0].tbdes1,
			ddi_get32(h, &tdp->td_bufs[0].tbdes1) | TBDES1_QUEUE);
E 4
I 4
D 9
	slot = SLOT(start_slot - 1, TX_RING_SIZE);
E 9
I 9
	slot = SLOT(start_slot - 1, tx_ring_size);
E 9
D 5
	((struct tx_desc *) dp->tx_ring)[slot].td_bufs[0].tbdes1 |=
							LE32(TBDES1_QUEUE);
E 5
I 5
D 6
	((struct tx_desc *) dp->tx_ring)[slot].td_bufs[0].tbdes1 |= le32_queue;
E 6
I 6
D 8
	((struct tx_desc *) dp->tx_ring)[slot].tbdes[0] |= le64_queue;
E 8
I 8
	((struct tx_desc *)dp->tx_ring)[slot].tbdes[0] |= le64_queue;
E 8
E 6
E 5
	gem_tx_desc_dma_sync(dp, slot, 1, DDI_DMA_SYNC_FORDEV);
E 4
E 2

D 4
	ddi_dma_sync(dp->desc_dma_handle,
		(off_t)(((caddr_t)&tdp->td_bufs[0].tbdes1) - dp->rx_ring),
		sizeof(uint32_t), DDI_DMA_SYNC_FORDEV);

D 2
	OUTW(dp, TDCSR_SET, TDCSR_WAK(0));

E 2
I 2
	if (!VEL_IS_POLLING(lp)) {
		OUTW(dp, TDCSR_SET, TDCSR_WAK(0));
	}
#ifdef CONFIG_POLLING
	lp->tx_list_len++;
#endif
E 2
	return 1;
E 4
I 4
D 6
	OUTW(dp, TDCSR_SET, TDCSR_WAK(0));
E 6
I 6
D 8
	if (dp->mac_active && (lp->imr & ISR_PRX) != 0) {
E 8
I 8
D 9
	if (dp->mac_active) {
E 8
		OUTW(dp, TDCSR_SET, TDCSR_WAK(0));
	}
I 8

E 8
	lp->tx_list_len += nslot;
E 9
I 9
	OUTW(dp, TDCSR_SET, TDCSR_WAK(0));
E 9
E 6
E 4
}

D 4
static int
vel_rx_desc_write(struct gem_dev *dp, uint_t slot,
E 4
I 4
static void
vel_rx_desc_write(struct gem_dev *dp, int slot,
E 4
D 9
	    ddi_dma_cookie_t *dmacookie, int frags)
E 9
I 9
    ddi_dma_cookie_t *dmacookie, int frags)
E 9
{
D 2
	int		i;
	struct rx_desc	*rdp;
	struct vel_dev	*lp = (struct vel_dev *)dp->private;
E 2
I 2
D 4
	int			i;
E 4
	struct rx_desc		*rdp;
D 4
	struct vel_dev		*lp = (struct vel_dev *)dp->private;
	ddi_acc_handle_t	h = dp->desc_acc_handle;
E 2

E 4
I 4
	uint64_t		daddr;
I 9
	uint32_t		tmp;
E 9
E 4
#if DEBUG_LEVEL > 2
I 4
	int			i;

E 4
D 8
	cmn_err(CE_CONT,
		"!%s: vel_rx_desc_write seqnum: %d, slot %d, frags: %d",
		dp->name, dp->rx_desc_tail, slot, frags);
E 8
I 8
	cmn_err(CE_CONT, "!%s: %s seqnum: %d, slot %d, frags: %d",
	    dp->name, __func__, dp->rx_desc_tail, slot, frags);
E 8
	for (i = 0; i < frags; i++) {
		cmn_err(CE_CONT, "!%d: addr: 0x%llx, len: 0x%x",
D 8
			i, dmacookie[i].dmac_laddress, dmacookie[i].dmac_size);
E 8
I 8
		    i, dmacookie[i].dmac_laddress, dmacookie[i].dmac_size);
E 8
	}
#endif

	/*
	 * write a RX descriptor
	 */
	rdp = &((struct rx_desc *)dp->rx_ring)[slot];
I 4
D 5
	daddr = (long) dmacookie->dmac_laddress;
E 5
I 5
	daddr = dmacookie->dmac_laddress;
E 5
E 4

D 2
	rdp->rdes1 = 0;
	rdp->rdes2 = LE32(dmacookie->dmac_address);
	rdp->rdes3 = LE32((dmacookie->dmac_size << RDES3_RBS_SHIFT)
E 2
I 2
D 4
	ddi_put32(h, &rdp->rdes1, 0);
	ddi_put32(h, &rdp->rdes2, dmacookie->dmac_address);
	ddi_put32(h, &rdp->rdes3, (dmacookie->dmac_size << RDES3_RBS_SHIFT)
E 4
I 4
	rdp->rdes1 = 0;
I 5
D 6
#ifdef notdef
E 6
I 6
D 8
#ifndef notdef
E 6
E 5
	rdp->rdes2 = LE32(daddr);
D 5
	rdp->rdes3 = LE32((dmacookie->dmac_size << RDES3_RBS_SHIFT)
E 5
I 5
	rdp->rdes3 = LE32((((uint32_t) dmacookie->dmac_size) << RDES3_RBS_SHIFT)
E 5
E 4
E 2
			|  RDES3_INTR
D 5
#ifdef CONFIG_DAC
D 4
		|(((uint32_t)(dmacookie->dmac_laddress >> 32)) & RDES3_ADDRHI)
E 4
I 4
			|  (daddr >> 32)
E 5
I 5
			|  ((uint32_t) (daddr >> 32)));
#else
	* (uint64_t *) &rdp->rdes2 = LE64(
			(((uint64_t) dmacookie->dmac_size)
					<< (RDES3_RBS_SHIFT + 32)) |
			(((uint64_t) RDES3_INTR) << 32) |
			daddr);
E 5
E 4
#endif
D 5
			);
D 2
	rdp->rdes0 = LE32(RDES0_OWN);
E 2
I 2
D 4
	ddi_put32(h, &rdp->rdes0, RDES0_OWN);
E 2

	ddi_dma_sync(dp->desc_dma_handle,
		(off_t)(((caddr_t)rdp) - dp->rx_ring),
		sizeof(struct rx_desc), DDI_DMA_SYNC_FORDEV);

	lp->rxbuf_added++;

D 2
	return frags;
E 2
I 2
	return 1;
E 4
I 4
	rdp->rdes0 = LE32(RDES0_OWN);
E 5
I 5
	rdp->rdes0 = LE32_CONST(RDES0_OWN);
E 8
I 8
	rdp->rdes2 = LE_32((uint32_t)daddr);
D 9
	rdp->rdes3 = LE_32((((uint32_t)dmacookie->dmac_size) << RDES3_RBS_SHIFT)
E 9
I 9
	tmp = (((uint32_t)dmacookie->dmac_size) << RDES3_RBS_SHIFT)
E 9
	    |  RDES3_INTR
D 9
	    |  ((uint32_t)(daddr >> 32)));

	rdp->rdes0 = LE_32(RDES0_OWN);
E 9
I 9
	    |  ((uint32_t)(daddr >> 32));
	rdp->rdes3 = LE_32(tmp);
#ifdef SANITY
	rdp->rdes0 = 0;
#endif
E 9
E 8
E 5
E 4
E 2
}

static void
D 9
vel_tx_desc_dump(struct gem_dev *dp, seqnum_t head, int ndesc)
E 9
I 9
vel_tx_desc_dump(struct gem_dev *dp, int slot)
E 9
{
D 2
	int		slot;
	int		i;
	int		frags;
	uint32_t	tdes0;
	uint32_t	tdes1;
	struct tx_desc	*tdp;
	struct td_buf	*tbp;
	struct vel_dev	*lp = (struct vel_dev *)dp->private;
E 2
I 2
D 9
	int			slot;
E 9
	int			i;
	int			frags;
	uint32_t		tdes0;
	uint32_t		tdes1;
	struct tx_desc		*tdp;
D 6
	struct td_buf		*tbp;
E 6
D 8
	struct vel_dev		*lp = (struct vel_dev *)dp->private;
E 8
I 8
D 9
	struct vel_dev		*lp = dp->private;
E 8
	ddi_acc_handle_t	h = dp->desc_acc_handle;
E 9
E 2

D 9
	ddi_dma_sync(dp->desc_dma_handle,
D 8
		(off_t)(((caddr_t)tdp) - dp->rx_ring),
		sizeof(struct tx_desc), DDI_DMA_SYNC_FORKERNEL);
E 8
I 8
	    (off_t)(((caddr_t)tdp) - dp->rx_ring),
	    sizeof (struct tx_desc), DDI_DMA_SYNC_FORKERNEL);
E 9
I 9
	gem_tx_desc_dma_sync(dp, slot, 1, DDI_DMA_SYNC_FORDEV);
E 9
E 8

D 2
	tdes0 = LE32(tdp->tdes0);
	tdes1 = LE32(tdp->tdes1);
E 2
I 2
D 4
	ddi_put32(h, &tdes0, tdp->tdes0);
	ddi_put32(h, &tdes1, tdp->tdes1);
E 4
I 4
D 8
	tdes0 = LE32(tdp->tdes0);
	tdes1 = LE32(tdp->tdes1);
E 8
I 8
D 9
	tdes0 = LE_32(tdp->tdes0);
	tdes1 = LE_32(tdp->tdes1);
E 9
I 9
	tdp = &((struct tx_desc *)dp->tx_ring)[slot];

	tdes0 = tdp->tdes0;
	tdes0 = LE_32(tdes0);
	tdes1 = tdp->tdes1;
	tdes1 = LE_32(tdes1);
E 9
E 8
E 4
E 2
	frags = ((tdes1 & TDES1_CMDZ) >> TDES1_CMDZ_SHIFT) - 1;

	cmn_err(CE_CONT,
D 8
	"!%s: tx_desc_dump: time: %d slot:%d frags:%d tsr:%b txdesc1:%b",
		dp->name, ddi_get_lbolt(), slot, frags,
D 2
		    LE32(tdp->tdes0), TDES0_BITS,
		    LE32(tdp->tdes1), TDES1_BITS);
E 2
I 2
D 4
		    ddi_get32(h, &tdp->tdes0), TDES0_BITS,
		    ddi_get32(h, &tdp->tdes1), TDES1_BITS);
E 4
I 4
		    LE32(tdp->tdes0), TDES0_BITS,
		    LE32(tdp->tdes1), TDES1_BITS);
E 8
I 8
	    "!%s: %s: time: %d slot:%d frags:%d tsr:%b txdesc1:%b",
	    dp->name, __func__, ddi_get_lbolt(), slot, frags,
D 9
	    LE_32(tdp->tdes0), TDES0_BITS,
	    LE_32(tdp->tdes1), TDES1_BITS);
E 9
I 9
	    tdes0, TDES0_BITS, tdes1, TDES1_BITS);
E 9
E 8
E 4
E 2

	for (i = 0; i < frags; i++) {
D 6
		tbp = &tdp->td_bufs[i];
		cmn_err(CE_CONT, "!%d: tb0: %x tb1: %b",
D 2
			i, LE32(tbp->tbdes0), LE32(tbp->tbdes1), TBDES1_BITS);
E 2
I 2
			i,
D 4
			ddi_get32(h, &tbp->tbdes0),
			ddi_get32(h, &tbp->tbdes1), TBDES1_BITS);
E 4
I 4
			LE32(tbp->tbdes0),
			LE32(tbp->tbdes1), TBDES1_BITS);
E 6
I 6
		cmn_err(CE_CONT, "!%d: tbdes: %xll", i, tdp->tbdes[i]);
E 6
E 4
E 2
	}
}

static uint_t
vel_tx_desc_stat(struct gem_dev *dp, int slot, int ndesc)
{
D 2
	struct tx_desc	*tdp;
	uint32_t	tsr;
	uint_t		ret;
	int		cols;
	int		i;
	struct vel_dev	*lp = (struct vel_dev *)dp->private;
E 2
I 2
	struct tx_desc		*tdp;
	uint32_t		tsr;
D 4
	uint_t			ret;
	int			cols;
	int			i;
	struct vel_dev		*lp = (struct vel_dev *)dp->private;
	ddi_acc_handle_t	h = dp->desc_acc_handle;
E 4
E 2
#ifdef DEBUG_LEVEL
D 2
	struct td_buf	*tbp;
	int		frags;
	uint32_t	tdes1;
E 2
I 2
D 6
	struct td_buf		*tbp;
E 6
	int			frags;
	uint32_t		tdes1;
E 2
#endif
I 6
D 8
	struct vel_dev	*lp = (struct vel_dev *)dp->private;
E 8
I 8
	struct vel_dev		*lp = dp->private;
E 8
E 6

	/*
	 * check the descriptor
	 */
	tdp = &((struct tx_desc *)dp->tx_ring)[slot];

D 4
	ddi_dma_sync(dp->desc_dma_handle,
		(off_t)(((caddr_t)tdp) - dp->rx_ring),
		sizeof(struct tx_desc), DDI_DMA_SYNC_FORKERNEL);

D 2
	tsr = LE32(tdp->tdes0);
E 2
I 2
	tsr = ddi_get32(h, &tdp->tdes0);
E 4
I 4
D 8
	tsr = LE32(tdp->tdes0);
E 8
I 8
	tsr = tdp->tdes0;
	tsr = LE_32(tsr);
E 8
E 4
E 2
#if DEBUG_LEVEL > 2
D 2
	tdes1 = LE32(tdp->tdes1);
E 2
I 2
D 4
	tdes1 = ddi_get32(h, &tdp->tdes1);
E 4
I 4
D 8
	tdes1 = LE32(tdp->tdes1);
E 8
I 8
	tdes1 = LE_32(tdp->tdes1);
E 8
E 4
E 2
	frags = ((tdes1 & TDES1_CMDZ) >> TDES1_CMDZ_SHIFT) - 1;

	cmn_err(CE_CONT,
D 8
	"!%s: vel_tx_desc_stat: time: %d slot:%d frags:%d tsr:%b txdesc1:%b",
		dp->name, ddi_get_lbolt(), slot, frags,
D 2
		    LE32(tdp->tdes0), TDES0_BITS,
		    LE32(tdp->tdes1), TDES1_BITS);
E 2
I 2
D 4
		    ddi_get32(h, &tdp->tdes0), TDES0_BITS,
		    ddi_get32(h, &tdp->tdes1), TDES1_BITS);
E 4
I 4
		    LE32(tdp->tdes0), TDES0_BITS,
		    LE32(tdp->tdes1), TDES1_BITS);
E 8
I 8
	    "!%s: %s: time: %d slot:%d frags:%d tsr:%b txdesc1:%b",
	    dp->name, __func__, ddi_get_lbolt(), slot, frags,
	    LE_32(tdp->tdes0), TDES0_BITS,
	    LE_32(tdp->tdes1), TDES1_BITS);
E 8
{
	int	i;
E 4
E 2

	for (i = 0; i < frags; i++) {
D 6
		tbp = &tdp->td_bufs[i];
		cmn_err(CE_CONT, "!%d: tb0: %x tb1: %b",
D 2
			i, LE32(tbp->tbdes0), LE32(tbp->tbdes1),TBDES1_BITS);
E 2
I 2
D 4
			i, ddi_get32(h, &tbp->tbdes0),
			ddi_get32(h, &tbp->tbdes1),TBDES1_BITS);
E 4
I 4
			i, LE32(tbp->tbdes0),
			LE32(tbp->tbdes1),TBDES1_BITS);
E 6
I 6
		cmn_err(CE_CONT, "!%d: tb: %xll", i, tdp->tbdes[i]);
E 6
E 4
E 2
	}
I 4
}
E 4
#endif
D 4
	if ((tsr & TDES0_OWN) != 0) {
		/* not transmitted yet */
		return 0;
	}
D 2

E 2
I 2
#ifdef CONFING_POLLING
	lp->tx_list_len--;
#endif
E 2
	ret = GEM_TX_DONE;
E 4
I 4
D 8
	if ((tsr & (TSR_TXERR | TDES0_OWN)) == 0) {
E 8
I 8
	if (!(tsr & (TSR_TXERR | TDES0_OWN))) {
E 8
#ifdef notdef
		int	cols;
E 4

D 4
	if ((tsr & TSR_TXERR) == 0) {
E 4
		if (!dp->full_duplex && (cols = (tsr & TSR_NCR)) > 0) {
			dp->stats.collisions += cols;
			if (cols == 1) {
				dp->stats.first_coll++;
D 8
			}
			else /* if (cols > 1)*/ {
E 8
I 8
			} else /* if (cols > 1) */ {
E 8
				dp->stats.multi_coll++;
			}
		}
I 4
#endif
E 4
		/* short cut for normal case */
D 6
		return GEM_TX_DONE;
E 6
I 6
		return (GEM_TX_DONE);
E 6
	}

I 4
D 8
	if ((tsr & TDES0_OWN) != 0) {
E 8
I 8
	if (tsr & TDES0_OWN) {
E 8
		/* not transmitted yet */
D 6
		return 0;
E 6
I 6
		return (0);
E 6
	}

E 4
	DPRINTF(2, (CE_CONT, "!%s: tx error: tsr: %b  desc:%d",
D 8
		dp->name, tsr, TDES0_BITS, dp->tx_desc_head));
E 8
I 8
	    dp->name, tsr, TDES0_BITS, dp->tx_desc_head));
E 8
D 6

E 6
I 6
D 9
	lp->tx_list_len--;
E 9
E 6
	dp->stats.errxmt++;

D 8
	if ((tsr & TSR_CRS) != 0) {
E 8
I 8
	if (tsr & TSR_CRS) {
E 8
		dp->stats.nocarrier++;
D 9
	}
D 8
	if ((tsr & TSR_OWC) != 0) {
E 8
I 8
	if (tsr & TSR_OWC) {
E 9
I 9
	} else if (tsr & TSR_OWC) {
E 9
E 8
		dp->stats.xmtlatecoll++;
D 9
	}

D 8
	if ((tsr & TSR_ABT) != 0) {
E 8
I 8
	if (tsr & TSR_ABT) {
E 9
I 9
	} else if (tsr & TSR_ABT) {
E 9
E 8
		if (!dp->full_duplex) {
			dp->stats.excoll++;
			dp->stats.collisions += 16;
		}
#ifdef notdef
D 9
		vel_tx_desc_dump(dp, dp->tx_desc_head, ndesc);
E 9
I 9
		vel_tx_desc_dump(dp, slot);
E 9
D 4
		/* drop the packet */
		ret |= GEM_TX_ERR;
E 4
#endif
	}

D 4
	return ret;
E 4
I 4
D 6
	return GEM_TX_DONE;
E 6
I 6
	return (GEM_TX_DONE);
E 6
E 4
}

I 6
static void
vel_rx_start(struct gem_dev *dp, int start_slot, int nslot)
{
I 8
D 9
	struct vel_dev		*lp = dp->private;
E 9
I 9
	int		new_tail;
	int		n;
	int		slot;
	uint32_t	own;
	uint_t		rx_ring_size = dp->gc.gc_rx_ring_size;
	struct vel_dev	*lp = dp->private;
E 9

E 8
D 9
	/* flush rx descriptors we made */
	gem_rx_desc_dma_sync(dp, start_slot, nslot, DDI_DMA_SYNC_FORDEV);
I 8
	nslot += lp->rx_desc_rest;
E 9
I 9
	/*
	 * Rx side of vt612x stops when descriptors exhausted.
	 * To restart rx dma engine correctly, it must stop at 4N
	 * boundary of rx descriptor. So, we add rx descriptors by 4.
	 */
	new_tail = SLOT((start_slot + nslot) & ~3, rx_ring_size);
	n = SLOT(new_tail - lp->rx_tail, rx_ring_size);
	if (n == 0) {
		/* only queue the new rx buffers */
		return;
	}
E 9
E 8

D 8
	OUTW(dp, RBRDU, nslot);
E 8
I 8
D 9
	OUTW(dp, RBRDU, nslot & ~3);
#if 0
	OUTB(dp, RDCSR_SET, RDCSR_WAK);
#endif
	lp->rx_desc_rest = nslot & 3;
E 9
I 9
	own = LE_32(RDES0_OWN);
	if (n > 1) {
		slot = SLOT(lp->rx_tail + 1, rx_ring_size);
		while (slot != new_tail) {
			((struct rx_desc *)dp->rx_ring)[slot].rdes0 = own;
			slot = SLOT(slot + 1, rx_ring_size);
		}
		gem_rx_desc_dma_sync(dp,
		    SLOT(lp->rx_tail + 1, rx_ring_size),
		    n - 1, DDI_DMA_SYNC_FORDEV);
	}

	((struct rx_desc *)dp->rx_ring)[lp->rx_tail].rdes0 = own;
	gem_rx_desc_dma_sync(dp, lp->rx_tail, 1, DDI_DMA_SYNC_FORDEV);

	OUTW(dp, RBRDU, n);

	/* save the new tail */
	lp->rx_tail = new_tail;
E 9
E 8
}

E 6
D 4
static uint_t
E 4
I 4
static uint64_t
E 4
vel_rx_desc_stat(struct gem_dev *dp, int slot, int ndesc)
{
D 2
	struct rx_desc	*rdp;
	uint32_t	rsr;
	uint_t		ret;
	uint_t		len;
	struct vel_dev	*lp = (struct vel_dev *)dp->private;
E 2
I 2
	struct rx_desc		*rdp;
	uint32_t		rsr;
D 4
	uint_t			ret;
	uint_t			len;
	struct vel_dev		*lp = (struct vel_dev *)dp->private;
	ddi_acc_handle_t	h = dp->desc_acc_handle;
E 4
I 4
	uint32_t		rdes1;
E 4
E 2

	rdp = &((struct rx_desc *)dp->rx_ring)[slot];

D 4
	ddi_dma_sync(dp->desc_dma_handle,
		(off_t)(((caddr_t)rdp) - dp->rx_ring),
		sizeof(struct rx_desc), DDI_DMA_SYNC_FORKERNEL);
E 4
I 4
D 8
	rsr = LE32(rdp->rdes0);
E 8
I 8
	rsr = rdp->rdes0;
	rsr = LE_32(rsr);
E 8
E 4

D 2
	rsr = LE32(rdp->rdes0);
E 2
I 2
D 4
	rsr = ddi_get32(h, &rdp->rdes0);
E 2
	len = (rsr >> RDES0_LEN_SHIFT) & RDES0_LEN_MASK;
	ret = GEM_RX_DONE;

E 4
	DPRINTF(2, (CE_CONT,
D 6
		"!%s: vel_rx_desc_stat: slot:%d dma len/addr:0x%x.%x rsr 0x%b",
		dp->name, slot,
E 6
I 6
D 8
		"!%s: %s: slot:%d dma len/addr:0x%x.%x rsr 0x%b, rdes1:%x",
		dp->name, __func__, slot,
E 6
D 2
		LE32(rdp->rdes3), LE32(rdp->rdes2),
		LE32(rdp->rdes0), RSR_BITS));
E 2
I 2
D 4
		ddi_get32(h, &rdp->rdes3), ddi_get32(h, &rdp->rdes2),
		ddi_get32(h, &rdp->rdes0), RSR_BITS));
E 4
I 4
		LE32(rdp->rdes3), LE32(rdp->rdes2),
D 6
		LE32(rdp->rdes0), RSR_BITS));
E 6
I 6
		LE32(rdp->rdes0), RSR_BITS, LE32(rdp->rdes1)));
E 8
I 8
	    "!%s: %s: slot:%d dma len/addr:0x%x.%x rsr 0x%b, rdes1:%x",
	    dp->name, __func__, slot,
	    LE_32(rdp->rdes3), LE_32(rdp->rdes2),
	    LE_32(rdp->rdes0), RSR_BITS, LE_32(rdp->rdes1)));
E 8
E 6
E 4
E 2

I 4
D 6
	if ((rsr & (RDES0_OWN | RSR_STP | RSR_EDP | RSR_RXOK)) == RSR_RXOK) {
#ifdef CONFIG_CKSUM_OFFLOAD
E 6
I 6
#define	RSR_ERRS	(RSR_RXER | RSR_LONG | RSR_FAE | RSR_CRC)
D 8
#ifdef notdef
	if ((rsr & (RDES0_OWN | RSR_STP | RSR_EDP)) == 0 &&
	    (rsr & (RSR_RXOK | RSR_VTAG)) != 0)
#else
	if ((rsr & (RDES0_OWN | RSR_STP | RSR_EDP | RSR_ERRS)) == 0)
#endif
	{
E 8
I 8

	if (!(rsr & (RDES0_OWN | RSR_STP | RSR_EDP | RSR_ERRS))) {
E 8
E 6
		uint64_t	pflags = 0;
I 6
D 9
#ifdef GEM_CONFIG_CKSUM_OFFLOAD
E 9
I 9
#ifdef CONFIG_CKSUM_OFFLOAD
E 9
E 6
		uint32_t	rdes1;

D 8
		rdes1 = LE32(rdp->rdes1);
E 8
I 8
D 9
		rdes1 = LE_32(rdp->rdes1);
E 9
I 9
		rdes1 = rdp->rdes1;
		rdes1 = LE_32(rdes1);
E 9
E 8

		if ((rdes1 & (RDES1_IPKT | RDES1_IPOK)) ==
D 8
				(RDES1_IPKT | RDES1_IPOK)) {
E 8
I 8
		    (RDES1_IPKT | RDES1_IPOK)) {
E 8
			pflags |= GEM_RX_CKSUM_IPv4;
		}

		if ((rdes1 & (RDES1_TCPKT | RDES1_TUPOK)) ==
D 8
				(RDES1_TCPKT | RDES1_TUPOK)) {
E 8
I 8
		    (RDES1_TCPKT | RDES1_TUPOK)) {
E 8
			pflags |= GEM_RX_CKSUM_TCP;
D 8
		}
		else if ((rdes1 & (RDES1_UDPKT | RDES1_TUPOK)) ==
				(RDES1_UDPKT | RDES1_TUPOK)) {
E 8
I 8
		} else if ((rdes1 & (RDES1_UDPKT | RDES1_TUPOK)) ==
		    (RDES1_UDPKT | RDES1_TUPOK)) {
E 8
			pflags |= GEM_RX_CKSUM_UDP;
		}
D 9
#endif
D 6
		return GEM_RX_DONE
E 6
I 6
#ifdef CONFIG_HW_VLAN
E 9
I 9
#endif /* CONFIG_CKSUM_OFFLOAD */
#ifdef CONFIG_VLAN_HW
E 9
D 8
		if ((rsr & RSR_VTAG) != 0) {
E 8
I 8
		if (rsr & RSR_VTAG) {
E 8
			uint64_t	vtag;
			/* extract vtag */
			vtag = BSWAP_16(rdes1 & RDES1_VTAG);
			pflags |= vtag << GEM_RX_VTAG_SHIFT;
		}
D 9
#endif
E 9
I 9
#endif /* CONFIG_VLAN_HW */
E 9
D 8
		return (GEM_RX_DONE
E 6
		    | (((rsr >> RDES0_LEN_SHIFT) - ETHERFCSL) & RDES0_LEN_MASK)
D 6
#ifdef CONFIG_CKSUM_OFFLOAD
E 6
I 6
#if defined(GEM_CONFIG_CKSUM_OFFLOAD) || defined(CONFIG_HW_VLAN)
E 6
		    | pflags
#endif
D 6
			;
E 6
I 6
			);
E 8
I 8
		DPRINTF(2, (CE_CONT,
		    "!%s: %s: slot:%d dma len/addr:0x%x.%x rsr 0x%b, rdes1:%x",
		    dp->name, __func__, slot,
		    LE_32(rdp->rdes3), LE_32(rdp->rdes2),
		    LE_32(rdp->rdes0), RSR_BITS, LE_32(rdp->rdes1)));

		return (GEM_RX_DONE | pflags |
		    (((rsr >> RDES0_LEN_SHIFT) - ETHERFCSL) & RDES0_LEN_MASK));
E 8
E 6
	}

E 4
D 8
	if ((rsr & RDES0_OWN) != 0) {
E 8
I 8
	if (rsr & RDES0_OWN) {
E 8
		/* it isn't received yet */
D 6
		return 0;
E 6
I 6
		return (0);
E 6
	}

D 8
	if ((rsr & (RSR_STP | RSR_EDP)) != 0) {
E 8
I 8
	if (rsr & (RSR_STP | RSR_EDP)) {
E 8
		/* big packet, ignore this fragment */
D 8
		if ((rsr & RSR_STP) != 0) {
E 8
I 8
		if (rsr & RSR_STP) {
E 8
			dp->stats.errrcv++;
			dp->stats.frame_too_long++;
		}
D 6
		return GEM_RX_DONE | GEM_RX_ERR;
E 6
I 6
		return (GEM_RX_DONE | GEM_RX_ERR);
E 6
	}

D 4
	if ((rsr & RSR_RXOK) == 0) {
		/* errored packet */
		dp->stats.errrcv++;
		if ((rsr & RSR_LONG) != 0) {
			dp->stats.frame_too_long++;
		}
E 4
I 4
	/* errored packet */
	dp->stats.errrcv++;
D 8
	if ((rsr & RSR_LONG) != 0) {
E 8
I 8
	if (rsr & RSR_LONG) {
E 8
		dp->stats.frame_too_long++;
D 8
	}
E 4
#ifdef notdef
D 4
		if ((rsr & RSR_RUNT) != 0) {
			dp->stats.runt++;
			DPRINTF(2, (CE_CONT,
		"!%s: vel_rx_desc_stat: slot:%d dma_addr:0x%x len:%d rsr 0x%b",
				dp->name, slot,
D 2
				LE32(rdp->rd_addr),
				LE32(rdp->rd_length),
				LE32(rdp->rd_status), RSR_BITS));
E 2
I 2
				ddi_get32(h, &rdp->rd_addr),
				ddi_get32(h, &rdp->rd_length),
				ddi_get32(h, &rdp->rd_status), RSR_BITS));
E 2
		}
		if ((rsr & (RSR_SERR | RSR_BUFF)) != 0) {
			dp->stats.overflow++;
		}
E 4
I 4
	if ((rsr & RSR_RUNT) != 0) {
		dp->stats.runt++;
		DPRINTF(2, (CE_CONT,
	"!%s: vel_rx_desc_stat: slot:%d dma_addr:0x%x len:%d rsr 0x%b",
			dp->name, slot,
			LE32(rdp->rd_addr),
			LE32(rdp->rd_length),
			LE32(rdp->rd_status), RSR_BITS));
	}
	if ((rsr & (RSR_SERR | RSR_BUFF)) != 0) {
		dp->stats.overflow++;
	}
E 4
#endif
D 4
		if ((rsr & RSR_FAE) != 0) {
			dp->stats.frame++;
		}
		if ((rsr & RSR_CRC) != 0) {
			dp->stats.crc++;
		}

		ret |= GEM_RX_ERR;
E 4
I 4
	if ((rsr & RSR_FAE) != 0) {
E 8
I 8
	} else if (rsr & RSR_FAE) {
E 8
		dp->stats.frame++;
E 4
D 8
	}
D 4

	if (len >= ETHERFCSL) {
		len -= ETHERFCSL;
E 4
I 4
	if ((rsr & RSR_CRC) != 0) {
E 8
I 8
	} else if (rsr & RSR_CRC) {
E 8
		dp->stats.crc++;
E 4
	}

D 4
	return ret | (len & GEM_RX_LEN);
E 4
I 4
D 6
	return GEM_RX_DONE | GEM_RX_ERR;
E 6
I 6
	return (GEM_RX_DONE | GEM_RX_ERR);
E 6
E 4
}

D 8
static void	/* DONE */
E 8
I 8
static void
E 8
vel_tx_desc_init(struct gem_dev *dp, int slot)
{
D 8
	struct tx_desc	*tdp;

	tdp = &((struct tx_desc *)dp->tx_ring)[slot];

E 8
	/* invalidate this descriptor */
D 8
	bzero(tdp, sizeof(struct tx_desc));
E 8
I 8
	bzero(&((struct tx_desc *)dp->tx_ring)[slot],
	    sizeof (struct tx_desc));
E 8
D 4

	ddi_dma_sync(dp->desc_dma_handle,
		(off_t)(((caddr_t)tdp) - dp->rx_ring),
		sizeof(struct tx_desc), DDI_DMA_SYNC_FORDEV);
E 4
}

D 8
static void	/* DONE */
E 8
I 8
static void
E 8
vel_rx_desc_init(struct gem_dev *dp, int slot)
{
D 8
	struct rx_desc	*rdp;

	rdp = &((struct rx_desc *)dp->rx_ring)[slot];

E 8
	/* invalidate this descriptor */
D 8
	bzero(rdp, sizeof(struct rx_desc));
E 8
I 8
	bzero(&((struct rx_desc *)dp->rx_ring)[slot],
	    sizeof (struct rx_desc));
E 8
D 4

	ddi_dma_sync(dp->desc_dma_handle,
		(off_t)(((caddr_t)rdp) - dp->rx_ring),
		sizeof(struct rx_desc), DDI_DMA_SYNC_FORDEV);
E 4
}

/*
 * Device depend interrupt handler
 */
D 8
static u_int
E 8
I 8
static uint_t
E 8
vel_interrupt(struct gem_dev *dp)
{
	uint32_t	isr;
I 8
	uint32_t	isr_org;
E 8
D 2
	int		loop;
E 2
I 2
D 4
	int		n;
E 4
E 2
	uint_t		flag = 0;
D 4
	boolean_t	need_to_reset = FALSE;
E 4
I 4
	boolean_t	need_to_reset = B_FALSE;
E 4
I 2
D 9
	clock_t		now;
E 9
E 2
D 8
	struct vel_dev	*lp = (struct vel_dev *)dp->private;
E 8
I 8
	struct vel_dev	*lp = dp->private;
E 8

D 8
	isr = INL(dp, ISR);
E 8
I 8
	isr_org = isr = INL(dp, ISR);
E 8

	if ((isr & lp->imr) == 0) {
		/* Not for us */
D 6
		return DDI_INTR_UNCLAIMED;
E 6
I 6
D 8
		if (isr != 0) {
			OUTL(dp, ISR, isr);
		}
E 8
		return (DDI_INTR_UNCLAIMED);
E 6
	}

D 8
	DPRINTF(2, (CE_CONT, "!%s: Interrupt, isr: %b",
		dp->name, isr, ISR_BITS));
E 8
I 8
	DPRINTF(2, (CE_CONT, "!%s: Interrupt, isr: %b, active:%x",
	    dp->name, isr, ISR_BITS, dp->mac_active));
E 8

D 8
	/* disable interrupt */
	OUTL(dp, CR_CLR, CR_GINTMSK1);
E 8
I 8
	/* clear interrupts */
	OUTL(dp, ISR, isr);
E 8

D 6
	if (!dp->nic_active) {
E 6
I 6
	if (!dp->mac_active) {
E 6
		/* the device is not active, no more interrupts */
		lp->imr = 0;
D 8
		OUTL(dp, ISR, isr);
E 8
I 8
		/* disable interrupt */
		OUTL(dp, CR_CLR, CR_GINTMSK1);
		FLSHL(dp, CR_CLR);
E 8

D 6
		return DDI_INTR_CLAIMED;
E 6
I 6
		return (DDI_INTR_CLAIMED);
E 6
	}
D 6
#ifdef RESET_TEST
E 6
I 6
#if defined(RESET_TEST) && (RESET_TEST >= 1000)
E 6
	lp->reset_test++;
D 6
	if ((lp->reset_test % 10000) == 9999) {
E 6
I 6
	if ((lp->reset_test % RESET_TEST) == RESET_TEST-1) {
E 6
D 4
		need_to_reset = TRUE;
E 4
I 4
		need_to_reset = B_TRUE;
E 4
	}
#endif
D 2
	loop = 100;
	do {
E 2
I 2
D 8
	/* clear interrupts */
	OUTL(dp, ISR, isr);
E 8
E 2

D 2
		/* clear interrupts */
		OUTL(dp, ISR, isr);
		FLSHL(dp, ISR);
E 2
I 2
D 8
	isr &= lp->imr;
E 2

E 8
D 2
		isr &= lp->imr;
E 2
I 2
D 4
#ifdef CONFIG_POLLING
E 4
I 4
D 9
#ifdef GEM_CONFIG_POLLING
I 8
	isr &= lp->imr | ISR_PPRX | ISR_PRX;
E 9
I 9
#ifdef CONFIG_POLLING
#define	INTR_MASK	ISR_PRX
E 9

I 9
	isr &= lp->imr | INTR_MASK;

E 9
E 8
E 4
	if (dp->poll_interval != lp->last_poll_interval) {
		/*
D 9
		 * It's time to check tx and rx statistics
E 9
I 9
		 * It's time to change polling rate.
E 9
		 */
D 8
		if (dp->poll_interval != 0) {
E 8
I 8
		if (dp->poll_interval) {
E 8
			/* polling mode */
D 6
			mutex_enter(&dp->xmitlock);
E 6
D 9
			lp->imr &= ~(ISR_PPRX | ISR_PRX);
I 4
D 6
#ifdef CONFIG_TX_COALESCE
			dp->tx_coalesce = B_TRUE;
#endif
E 4
			mutex_exit(&dp->xmitlock);
E 6
E 2

E 9
I 9
			lp->imr &= ~INTR_MASK;
E 9
D 2
		if (isr & (ISR_PRX | ISR_PPRX)) {
			/* packet was received, or receive error happened */
			gem_receive(dp);
		}
E 2
I 2
D 8
			OUTW(dp, SOFT_TMR1, dp->poll_interval);
			OUTL(dp, IMR, lp->imr);
E 8
I 8
			OUTW(dp, SOFT_TMR1, dp->poll_interval/1000);
E 8
			OUTL(dp, CR_SET, CR_TMR1EN);
E 2
D 9

D 2
		if ((isr & (ISR_PTX | ISR_PPTX)) != 0) {
			/* packet was transmitted or transmit error happened */
			if (gem_tx_done(dp)) {
				flag |= INTR_RESTART_TX;
			}
E 2
I 2
			/* pretend as we were interrupted from polling timer */
			isr |= ISR_TMR1;
E 9
E 2
D 8
		}
I 2
		else {
E 8
I 8
		} else {
E 8
			/* normal mode */
D 6
			mutex_enter(&dp->xmitlock);
E 6
D 9
			lp->imr |= (ISR_PPRX | ISR_PRX);
I 4
D 6
#ifdef CONFIG_TX_COALESCE
			dp->tx_coalesce = B_FALSE;
#endif
E 4
			mutex_exit(&dp->xmitlock);
E 6
D 8
			OUTL(dp, IMR, lp->imr);
E 8
I 8

E 9
I 9
			lp->imr |= INTR_MASK;
E 9
E 8
			OUTL(dp, CR_CLR, CR_TMR1EN);
		}
I 8
		OUTL(dp, IMR, lp->imr);
E 8
E 2

I 8
		lp->last_poll_interval = dp->poll_interval;
E 8
D 2
		if ((isr &
		~(ISR_SHDN | ISR_PRX | ISR_PPRX | ISR_PTX | ISR_PPTX)) != 0) {
E 2
I 2
	}
D 8
	lp->last_poll_interval = dp->poll_interval;

	if ((isr & ISR_TMR1) != 0) {
		/* force to process ROK and TOK */
		isr |= ISR_PRX | ISR_PTX;
	}
E 8
I 8
#else
	isr &= lp->imr;
E 8
D 4
#endif
E 4
I 4
D 9
#endif /* GEM_CONFIG_POLLING */
E 9
I 9
#endif /* CONFIG_POLLING */
E 9
E 4

I 7
D 8
	/* a barrier make the interrupt status stable */
E 8
I 8
D 9
	/* barrier to make the interrupt status stable */
E 9
I 9
	/* barrier to commit the interrupt status */
E 9
E 8
	FLSHL(dp, ISR);

E 7
D 3
	if ((isr & (ISR_PRX | ISR_PPRX)) != 0) {
E 3
I 3
D 8
	if ((isr & (ISR_PRX | ISR_PPRX | ISR_LSTE)) != 0) {
E 8
I 8
	if (isr & (ISR_PRX | ISR_PPRX | ISR_LSTE)) {
E 8
I 4
D 6
		int	rxcnt;
E 4
E 3

E 6
		/* packet was received, or receive error happened */
D 4
		n = gem_receive(dp);
E 4
I 4
D 6
		rxcnt = gem_receive(dp);
E 6
I 6
		(void) gem_receive(dp);
E 6
E 4

I 3
D 8
		if ((isr & ISR_LSTE) != 0) {
E 8
I 8
		if (isr & ISR_LSTE) {
E 8
D 9
			dp->stats.overflow++;
I 8
#ifdef notdef
E 8
D 4
#ifdef notdef
			OUTB(dp, RDCSR_SET, RDCSR_WAK);
#else
			need_to_reset = TRUE;
#endif
E 4
I 4
			need_to_reset = B_TRUE;
E 9
I 9
#if DEBUG_LEVEL > 3
			if ((INW(dp, RDINDEX) & 3) != 0) {
				cmn_err(CE_CONT,
				    "!%s: no rx desc: isr:%b rdcsr:%x:%x "
				    "rbrdu:%x rdindex:%d slot:%d tail:%d",
				    dp->name, isr_org, ISR_BITS,
				    INB(dp, RDCSR_SET), INB(dp, RDCSR_CLR),
				    INW(dp, RBRDU), INW(dp, RDINDEX),
				    SLOT(dp->rx_active_head, RX_BUF_SIZE),
				    lp->rx_tail);
			}
E 9
I 8
#endif
I 9
			dp->stats.norcvbuf++;
			/* Kick TX and RX */
E 9
			OUTB(dp, RDCSR_SET, RDCSR_WAK);
E 8
E 4
		}
D 6

E 3
D 4
		if (lp->rxbuf_added > 0) {
E 4
I 4
		if (rxcnt > 0) {
E 4
E 2
			/*
D 2
			 * unexpected interrupt
E 2
I 2
D 4
			 * Notify the nic that packts are added into
			 * the rx list.
E 4
I 4
			 * tell nic that packts are added into rx list.
E 4
E 2
			 */
D 2
			cmn_err(CE_WARN,
				"!%s: unexpected interrupt: isr:%b",
				dp->name, isr, ISR_BITS);
E 2
I 2
D 4
			OUTW(dp, RBRDU, lp->rxbuf_added);
			lp->rxbuf_added = 0;
E 4
I 4
			OUTW(dp, RBRDU, rxcnt);
E 4
		}
E 6
	}
E 2

D 2
			if ((isr & ISR_TXSTL) != 0) {
				OUTB(dp, TXESR, INB(dp, TXESR) | TXESR_TDSTR);
				/* stop tx queue */
				OUTW(dp, TDCSR_CLR, TDCSR_RUN(0));
				cmn_err(CE_PANIC,
					"%s: corrupted tx descriptor: index:%d",
					dp->name, INW(dp, TDINDEX));
E 2
I 2
D 8
	if ((isr & (ISR_PTX | ISR_PPTX)) != 0) {
E 8
I 8
	if (isr & (ISR_PTX | ISR_PPTX)) {
E 8
D 9
		/* packet was transmitted or transmit error happened */
E 9
I 9
		/* packets have been transmitted or transmit error happened */
E 9
		if (gem_tx_done(dp)) {
			flag |= INTR_RESTART_TX;
		}
I 9
	}
E 9
I 8
#ifdef notdef
E 8
I 6
D 9
		mutex_enter(&dp->xmitlock);
		if (lp->tx_list_len > 0) {
			OUTW(dp, TDCSR_SET, TDCSR_WAK(0));
		}
		mutex_exit(&dp->xmitlock);
I 8
#endif
E 9
I 9
	if (isr & ISR_RACE) {
		OUTW(dp, TDCSR_SET, TDCSR_WAK(0));
E 9
E 8
E 6
D 4
#ifdef CONFIG_POLLING
		if ((isr & ISR_TMR1) != 0) {
			/* force to load valid tx descriptors to the nic */
			if (lp->tx_list_len != 0) {
				OUTW(dp, TDCSR_SET, TDCSR_WAK(0));
E 2
			}
I 2
		}
#endif
E 4
	}
E 2
D 9

E 9
I 9
#endif
E 9
D 2
			if ((isr & ISR_SRC) != 0) {
E 2
I 2
D 8
	if ((isr &
D 3
    ~(ISR_SHDN | ISR_TMR1 | ISR_PRX | ISR_PPRX | ISR_PTX | ISR_PPTX)) != 0) {
E 3
I 3
    ~(ISR_SHDN | ISR_TMR1 | ISR_PRX | ISR_PPRX | ISR_PTX | ISR_PPTX | ISR_LSTE)) != 0) {
E 8
I 8
	if (isr & ~(ISR_SHDN | ISR_TMR1 | ISR_PRX | ISR_PPRX |
D 9
	    ISR_PTX | ISR_PPTX | ISR_LSTE | ISR_LSTPE)) {
E 9
I 9
	    ISR_PTX | ISR_PPTX | ISR_LSTE | ISR_LSTPE | ISR_RACE)) {
E 9
E 8
E 3
		/*
D 9
		 * unexpected interrupt
E 9
I 9
		 * handle unexpected interrupt
E 9
		 */
		cmn_err(CE_WARN,
D 8
			"!%s: unexpected interrupt: isr:%b",
			dp->name, isr, ISR_BITS);
E 8
I 8
		    "!%s: unexpected interrupt: isr:%b",
		    dp->name, isr_org, ISR_BITS);
E 8

D 8
		if ((isr & ISR_TXSTL) != 0) {
E 8
I 8
		if (isr & ISR_TXSTL) {
I 9
#ifdef notdef
			int	i;
#endif
			/* clear interrupt reason */
E 9
E 8
			OUTB(dp, TXESR, INB(dp, TXESR) | TXESR_TDSTR);
I 9

E 9
			/* stop tx queue */
			OUTW(dp, TDCSR_CLR, TDCSR_RUN(0));
I 9

E 9
D 3
			cmn_err(CE_PANIC,
E 3
I 3
			cmn_err(CE_WARN,
E 3
D 8
				"%s: corrupted tx descriptor: index:%d",
				dp->name, INW(dp, TDINDEX));
E 8
I 8
D 9
			    "!%s: corrupted tx descriptor: index:%d",
E 9
I 9
			    "!%s: tx stopped at descriptor index:%d",
E 9
			    dp->name, INW(dp, TDINDEX));
I 9
#ifdef notdef
			for (i = 0; i < dp->gc.gc_tx_ring_size; i++) {
				vel_tx_desc_dump(dp, i);
			}
#endif
#ifdef notdef
E 9
E 8
I 3
D 4
			need_to_reset = TRUE;
E 4
I 4
			need_to_reset = B_TRUE;
I 9
#else
			OUTW(dp, TDCSR_SET, TDCSR_WAK(0));
#endif
E 9
E 4
E 3
		}
D 9

E 9
I 9
#ifdef notdef
E 9
D 6
		if ((isr & ISR_SRC) != 0) {
E 2
#ifdef notyet
D 2
				/* restart link watcher */
				gem_link_check(dp);
E 2
I 2
			/* restart link watcher */
			gem_link_check(dp);
E 2
#endif
E 6
I 6
D 8
		if ((isr & (ISR_SRC | ISR_PHY)) != 0) {
E 8
I 8
		if (isr & (ISR_SRC | ISR_PHY)) {
E 8
			/* link status changed */
D 9
			/* doen't work */
E 9
I 9
			/* XXX - doesn't work */
E 9
			DPRINTF(0, (CE_CONT,
D 8
				"!%s: isr:%b", dp->name, isr, ISR_BITS));
E 8
I 8
			    "!%s: isr:%b", dp->name, isr, ISR_BITS));
E 8
			if (gem_mii_link_check(dp)) {
				flag |= INTR_RESTART_TX;
			}
E 6
D 2
			}
E 2
I 2
		}
E 2
D 9

E 9
I 9
#endif
E 9
D 2
			if ((isr & ISR_MIBF) != 0) {
				vel_get_stats(dp);
			}
E 2
I 2
D 8
		if ((isr & ISR_MIBF) != 0) {
E 8
I 8
		if (isr & ISR_MIBF) {
E 8
			vel_get_stats(dp);
		}
E 2
D 8

D 2
			if ((isr & ISR_LSTE) != 0) {
E 2
I 2
D 3
		if ((isr & ISR_LSTE) != 0) {
E 3
E 2
#ifdef notdef
I 3
		if ((isr & ISR_LSTE) != 0) {
E 3
D 2
				OUTB(dp, RDCSR_SET, RDCSR_WAK);
E 2
I 2
			OUTB(dp, RDCSR_SET, RDCSR_WAK);
E 2
D 3
#else
E 3
D 2
				need_to_reset = TRUE;
E 2
I 2
D 4
			need_to_reset = TRUE;
E 4
I 4
			need_to_reset = B_TRUE;
E 4
E 2
D 3
#endif
E 3
D 2
			}
E 2
		}
I 3
#endif
E 8
E 3
D 2

		if (lp->rxbuf_added > 0) {
			OUTW(dp, RBRDU, lp->rxbuf_added);
			lp->rxbuf_added = 0;
		}

		isr = INL(dp, ISR);

	} while ((isr & lp->imr) != 0 && --loop > 0);

	if (loop <= 0) {
		need_to_reset = TRUE;
		cmn_err(CE_WARN, "%s: interrupts maxmum exceeded", dp->name);
		lp->imr = 0;
		OUTL(dp, IMR, lp->imr);
E 2
	}

I 2
D 4
	/* barrier for interrupt status */
E 4
I 4
D 7
	/* a barrier make the interrupt status stable */
E 4
	FLSHL(dp, ISR);

E 7
E 2
	if (need_to_reset) {
D 4
		mutex_enter(&dp->xmitlock);
		gem_restart_tx(dp);
		mutex_exit(&dp->xmitlock);
E 4
I 4
D 7
		gem_restart_nic(dp, B_TRUE);
E 7
I 7
D 8
		gem_restart_nic(dp, GEM_RESTART_KEEP_BUF);
E 8
I 8
		(void) gem_restart_nic(dp, GEM_RESTART_KEEP_BUF);
E 8
E 7
E 4
I 2
D 9

E 9
E 2
		flag |= INTR_RESTART_TX;
	}
D 2
	else if ((dp->misc_flag & GEM_NOINTR) == 0 && loop > 0) {
E 2
I 2

D 8
	if ((dp->misc_flag & GEM_NOINTR) == 0) {
E 2
		/* enable interrupts again */
		OUTL(dp, CR_SET, CR_GINTMSK1);
	}

E 8
D 6
	return DDI_INTR_CLAIMED | flag;
E 6
I 6
	return (DDI_INTR_CLAIMED | flag);
E 6
}

/*
 * HW depend MII routines
 */
static void
vel_mii_sync(struct gem_dev *dp)
{
	/* nothing to do */
}

static uint16_t
D 3
vel_mii_read(struct gem_dev *dp, int reg)
E 3
I 3
vel_mii_read(struct gem_dev *dp, uint_t reg)
E 3
{
D 8
	int		n;
E 8
I 8
	int		i;
E 8
	uint16_t	val;

	OUTB(dp, MIIADR, reg);
	OUTB(dp, MIICR, INB(dp, MIICR) | MIICR_RCMD);

D 8
	n = 100;
	while ((INB(dp, MIICR) & MIICR_RCMD) != 0) {
		if  (--n == 0) {
E 8
I 8
	for (i = 0; INB(dp, MIICR) & MIICR_RCMD; i++) {
		if (i > 100) {
E 8
D 6
			cmn_err(CE_WARN, "!%s: mii_read: timeout", dp->name);
			return 0xffff;
E 6
I 6
			cmn_err(CE_WARN, "!%s: %s: timeout",
D 8
				dp->name, __func__);
E 8
I 8
			    dp->name, __func__);
E 8
D 7
			return (0xffff);
E 7
I 7
			return (0);
E 7
E 6
		}
		drv_usecwait(10);
	}
	val = INW(dp, MIIDATA);

D 6
	return val;
E 6
I 6
	return (val);
E 6
}

static void
D 3
vel_mii_write(struct gem_dev *dp, int reg, uint16_t val)
E 3
I 3
vel_mii_write(struct gem_dev *dp, uint_t reg, uint16_t val)
E 3
{
D 8
	int	n;
E 8
I 8
	int	i;
E 8

	OUTB(dp, MIIADR, reg);
	OUTW(dp, MIIDATA, val);
	OUTB(dp, MIICR, INB(dp, MIICR) | MIICR_WCMD);
D 8
	n = 100;
	while ((INB(dp, MIICR) & MIICR_WCMD) != 0) {
		if (--n == 0) {
E 8
I 8

	for (i = 0; INB(dp, MIICR) & MIICR_WCMD; i++) {
		if (i > 100) {
E 8
D 6
			cmn_err(CE_WARN, "!%s: mii_write: timeout", dp->name);
E 6
I 6
			cmn_err(CE_WARN, "!%s: %s: timeout",
D 8
				dp->name, __func__);
E 8
I 8
			    dp->name, __func__);
E 8
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
velattach(dev_info_t *dip, ddi_attach_cmd_t cmd)
{
	int			i;
	ddi_iblock_cookie_t	c;
	ddi_acc_handle_t	conf_handle;
	int			ret;
	uint16_t		vid;
	uint16_t		did;
	uint8_t			revid;
	int			unit;
	struct chip_info	*p;
	int			len;
	struct pci_phys_spec	*regs;
	const char		*drv_name;
	struct gem_dev		*dp;
	struct vel_dev	*lp;
	caddr_t			base;
	ddi_acc_handle_t	regs_ha;
	struct gem_conf		*gcp;
	uint32_t		val;
	uint32_t		cap_ptr;
	uint32_t		cap;
	uint32_t		ps;
	uint32_t		ilr;
I 8
D 9
	boolean_t		is_pcie;
E 9
I 9
	uint32_t		pcie_cap;
E 9
E 8

D 7
	unit =  ddi_get_instance(dip);
E 7
I 7
	unit = ddi_get_instance(dip);
E 7
	drv_name = ddi_driver_name(dip);

D 4
	DPRINTF(2, (CE_CONT, "!%s%d: velattach: called at time:%d",
		drv_name, unit, ddi_get_lbolt()));
E 4
I 4
	DPRINTF(0, (CE_CONT, "!%s%d: velattach: called at time:%d (%s)",
D 8
		drv_name, unit, ddi_get_lbolt(), ident));
E 8
I 8
	    drv_name, unit, ddi_get_lbolt(), ident));
E 8
E 4

I 4
	/*
	 * Common codes after power-up
	 */
	if (pci_config_setup(dip, &conf_handle) != DDI_SUCCESS) {
D 8
		cmn_err(CE_WARN, "%s%d: ddi_regs_map_setup failed",
			drv_name, unit);
E 8
I 8
		cmn_err(CE_WARN, "!%s%d: ddi_regs_map_setup failed",
		    drv_name, unit);
E 8
		goto err;
	}

D 8
	vid  = pci_config_get16(conf_handle, PCI_CONF_VENID);
	did  = pci_config_get16(conf_handle, PCI_CONF_DEVID);
	revid= pci_config_get8(conf_handle, PCI_CONF_REVID);
E 8
I 8
	vid = pci_config_get16(conf_handle, PCI_CONF_VENID);
	did = pci_config_get16(conf_handle, PCI_CONF_DEVID);
	revid = pci_config_get8(conf_handle, PCI_CONF_REVID);
I 9
	ilr = pci_config_get32(conf_handle, PCI_CONF_ILINE);
E 9
E 8

	DPRINTF(0, (CE_CONT,
D 8
		"!%s%d: ilr 0x%08x, latency_timer:0x%02x",
		drv_name, unit,
		pci_config_get32(conf_handle, PCI_CONF_ILINE),
		pci_config_get8(conf_handle, PCI_CONF_LATENCY_TIMER)));
E 8
I 8
	    "!%s%d: ilr 0x%08x, latency_timer:0x%02x",
	    drv_name, unit,
	    pci_config_get32(conf_handle, PCI_CONF_ILINE),
	    pci_config_get8(conf_handle, PCI_CONF_LATENCY_TIMER)));
E 8

	pci_config_put16(conf_handle, PCI_CONF_COMM,
D 8
		PCI_COMM_IO | PCI_COMM_MAE | PCI_COMM_ME |
			pci_config_get16(conf_handle, PCI_CONF_COMM));
E 8
I 8
	    PCI_COMM_IO | PCI_COMM_MAE | PCI_COMM_ME |
	    pci_config_get16(conf_handle, PCI_CONF_COMM));
E 8

	/* ensure D0 mode */
	(void) gem_pci_set_power_state(dip, conf_handle, PCI_PMCSR_D0);

I 8
	/* check bus type */
D 9
	is_pcie = gem_search_pci_cap(dip, conf_handle, PCI_CAP_ID_PCI_E);
E 9
I 9
	pcie_cap = gem_search_pci_cap(dip, conf_handle, PCI_CAP_ID_PCI_E);
	if (pcie_cap) {
I 11
		uint32_t	devcap;
		uint32_t	devcsr;

		devcap = pci_config_get32(conf_handle, pcie_cap + 4);
		devcsr = pci_config_get32(conf_handle, pcie_cap + 8);

E 11
		DPRINTF(0, (CE_CONT,
		    "!%s: pcie cap:%x, dev_cap:%x, dev_csr:%x", 
		    __func__,
		    pci_config_get32(conf_handle, pcie_cap),
D 11
		    pci_config_get32(conf_handle, pcie_cap + 4),
		    pci_config_get32(conf_handle, pcie_cap + 8)));
E 11
I 11
		    devcap, devcsr));
		/*
		 * increase max read request 2:512, 3:1024, 4:2048
		 */
		if ((devcsr & (7 << 12)) < (3 << 12)) {
			devcsr = (devcsr & ~(7 << 12)) | (3 << 12);
			pci_config_put32(conf_handle, pcie_cap + 8, devcsr);
		}
E 11
	}
E 9

E 8
	pci_config_teardown(&conf_handle);

E 4
	switch (cmd) {
I 4
	case DDI_RESUME:
D 6
		return gem_resume(dip);
E 6
I 6
		return (gem_resume(dip));
E 6

E 4
	case DDI_ATTACH:
		/*
D 4
		 * Check if chip is supported.
E 4
I 4
		 * Check if the chip is supported.
E 4
		 */
D 4
		if (pci_config_setup(dip, &conf_handle) != DDI_SUCCESS) {
			cmn_err(CE_WARN, "!%s%d: ddi_regs_map_setup failed",
				drv_name, unit);
			return DDI_FAILURE;
		}
		vid  = pci_config_get16(conf_handle, PCI_CONF_VENID);
		did  = pci_config_get16(conf_handle, PCI_CONF_DEVID);
		revid= pci_config_get8(conf_handle, PCI_CONF_REVID);

E 4
		for (i = 0, p = vel_chiptbl; i < CHIPTABLESIZE; i++, p++) {
			if (p->venid == vid && p->devid == did) {
				/* found */
				cmn_err(CE_CONT,
D 8
			"!%s%d: %s (vid: 0x%04x, did: 0x%04x, revid: 0x%02x)",
				drv_name, unit, p->name, vid, did, revid);
E 8
I 8
				    "!%s%d: %s (vid: 0x%04x, did: 0x%04x,"
				    " revid: 0x%02x)",
				    drv_name, unit, p->name, vid, did, revid);
E 8
				goto chip_found;
			}
		}
		/* Not found */
		cmn_err(CE_WARN,
D 8
			"!%s: vel_attach: wrong PCI venid/devid (0x%x, 0x%x)",
			drv_name, vid, did);
E 8
I 8
		    "!%s: vel_attach: wrong PCI venid/devid (0x%x, 0x%x)",
		    drv_name, vid, did);
E 8
D 4
		goto err;

E 4
chip_found:
D 4
		/* ensure the pmr status is  D0 mode */
		cap_ptr = pci_config_get8(conf_handle, PCI_CONF_CAP_PTR);
		while (cap_ptr != 0) {
			/* read capability header */
			cap = pci_config_get32(conf_handle, cap_ptr);
			if ((cap & 0xff) == PCI_CAP_ID_PM) {
				/*
				 * A power management capability found.
				 * ensure D0 mode
				 */
				ps = pci_config_get32(conf_handle, cap_ptr + 4);

				DPRINTF(0, (CE_CONT,
				"!%s%d: pmc found at 0x%x: ps: 0x%08x",
				drv_name, unit, cap_ptr, ps));

				ps &= ~PCI_PMCSR_STATE_MASK;
				pci_config_put32(conf_handle, cap_ptr + 4, ps);

				/* no need to work more */
				break;
			}
			/* get next_ptr */
			cap_ptr = (cap >> 8) & 0xff;
		}

		ilr = pci_config_get32(conf_handle, PCI_CONF_ILINE);
		DPRINTF(0, (CE_CONT, "!%s%d: ilr 0x%08x", drv_name, unit, ilr));

E 4
		/*
D 4
		 * Map the device registers in the kernel virtual space.
E 4
I 4
		 * Map in the device registers.
E 4
		 */

D 4
		/* Search IO-range or memory-range to be mapped */
		regs = NULL;
		len  = 0;
		if (ddi_getlongprop(DDI_DEV_T_ANY, dip, DDI_PROP_DONTPASS,
			"reg", (caddr_t)&regs, &len) != DDI_PROP_SUCCESS) {
			cmn_err(CE_WARN,
			"!%s%d: failed to get reg property", drv_name, unit);
			goto err;
		}

		ASSERT(regs != NULL && len > 0);
#if DEBUG_LEVEL > 2
		for (i = 0; i <len / sizeof(struct pci_phys_spec); i++) {
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
		for (i = 0; i <len / sizeof(struct pci_phys_spec); i++) {
			if ((regs[i].pci_phys_hi & PCI_REG_ADDR_M) == 
E 4
I 4
		if (gem_pci_regs_map_setup(dip,
E 4
#ifdef MAP_MEM
D 4
			    PCI_ADDR_MEM32
E 4
I 4
D 6
			PCI_ADDR_MEM32,
E 6
I 6
D 8
			PCI_ADDR_MEM32, PCI_ADDR_MASK,
E 8
I 8
		    PCI_CONF_BASE1, 0xff,
E 8
E 6
E 4
#else
D 4
			    PCI_ADDR_IO
E 4
I 4
D 6
			PCI_ADDR_IO,
E 6
I 6
D 8
			PCI_ADDR_IO, PCI_ADDR_MASK,
E 8
I 8
		    PCI_CONF_BASE0, 0xff,
E 8
E 6
E 4
#endif
D 4
			) {
				/* Ok, it's I/O space */
				kmem_free(regs, len);
				goto map_space_found;
			}
		}
		cmn_err(CE_WARN,
#ifdef MAP_MEM
			"!%s%d: failed to find MEM32 space",
#else
			"%s%d: failed to find IO space",
#endif
			drv_name, unit);
		kmem_free(regs, len);
		goto err;

map_space_found:
		/* ensure we can access the registers through IO space. */
		ret = pci_config_get16(conf_handle, PCI_CONF_COMM);
		ret |= PCI_COMM_IO | PCI_COMM_ME | PCI_COMM_MAE;
		pci_config_put16(conf_handle, PCI_CONF_COMM, ret);

		if (ddi_regs_map_setup(dip, i, &base,
			0, 0, &vel_dev_attr, &regs_ha)) {
			cmn_err(CE_WARN, "!%s%d: ddi_regs_map_setup failed",
E 4
I 4
D 8
			&vel_dev_attr, (caddr_t *)&base, &regs_ha) !=
								DDI_SUCCESS) {
			cmn_err(CE_WARN, "%s%d: ddi_regs_map_setup failed",
E 4
				drv_name, unit);
E 8
I 8
		    &vel_dev_attr, (caddr_t *)&base, &regs_ha)
		    != DDI_SUCCESS) {
			cmn_err(CE_WARN, "!%s%d: ddi_regs_map_setup failed",
			    drv_name, unit);
E 8
			goto err;
		}

		/*
		 * construct gem configration
		 */
D 8
		gcp = (struct gem_conf *) kmem_zalloc(sizeof(*gcp), KM_SLEEP);
E 8
I 8
		gcp = kmem_zalloc(sizeof (*gcp), KM_SLEEP);
E 8

		/* name */
		sprintf(gcp->gc_name, "%s%d", drv_name, unit);

D 6
		/* consistency on tx and rx */
E 6
I 6
		/* configuration on tx and rx */
E 6
D 8
		gcp->gc_tx_buf_align = sizeof(uint8_t) - 1;
E 8
I 8
		gcp->gc_tx_buf_align = sizeof (uint8_t) - 1;
E 8
		gcp->gc_tx_max_frags = NTDBUFS;
I 6
		gcp->gc_tx_max_descs_per_pkt = 1;
E 6
I 2
D 4
#ifdef CONFIG_TX_SINGLE_QUEUE
		gcp->gc_tx_desc_size = sizeof(struct tx_desc) * TX_RING_SIZE;
#else
E 2
		gcp->gc_tx_desc_size = sizeof(struct tx_desc) * TX_RING_SIZE
					* NUM_TX_QUEUES;
I 2
#endif
E 2
		gcp->gc_tx_ring_size = TX_RING_SIZE;
		gcp->gc_tx_buf_size  = TX_BUF_SIZE;
E 4
I 4
		gcp->gc_tx_desc_unit_shift = 6; /* 64 byte */
D 8
		gcp->gc_tx_ring_size  = TX_RING_SIZE;
E 8
I 8
D 9
		gcp->gc_tx_ring_size = TX_RING_SIZE;
E 9
I 9
		gcp->gc_tx_ring_size = TX_BUF_SIZE;
E 9
E 8
		gcp->gc_tx_ring_limit = gcp->gc_tx_ring_size - 1;
D 8
		gcp->gc_tx_buf_size   = TX_BUF_SIZE;
		gcp->gc_tx_buf_limit  = gcp->gc_tx_buf_size - 1;
E 4
D 6
		gcp->gc_tx_max_descs_per_pkt = 1;
E 6
D 4
		gcp->gc_tx_auto_pad  = FALSE;
E 4
I 4
		gcp->gc_tx_auto_pad  = B_FALSE;
E 8
I 8
D 9
		gcp->gc_tx_buf_size = TX_BUF_SIZE;
		gcp->gc_tx_buf_limit = gcp->gc_tx_buf_size - 1;
E 9
I 9
		gcp->gc_tx_buf_size = gcp->gc_tx_ring_size;
D 11
		gcp->gc_tx_buf_limit = gcp->gc_tx_buf_size;
E 11
I 11
		gcp->gc_tx_buf_limit = gcp->gc_tx_ring_limit;
E 11
E 9
		gcp->gc_tx_auto_pad = B_FALSE;
E 8
E 4
		gcp->gc_tx_copy_thresh = vel_tx_copy_thresh;
D 2

E 2
I 2
D 4
#if 0
E 2
		gcp->gc_rx_buf_align = sizeof(uint8_t) - 1;
E 4
I 4
D 9
#ifdef CONFIG_OO
D 6
		gcp->gc_tx_desc_write_oo = B_TRUE;
E 6
I 6
		gcp->gc_tx_desc_write_oo = TX_BUF_SIZE == TX_RING_SIZE;
E 6
E 4
I 2
#else
D 4
		gcp->gc_rx_buf_align = 64 - 1;
E 4
I 4
		gcp->gc_tx_desc_write_oo = B_FALSE;
E 4
#endif
E 9
I 9

E 9
I 4
D 8
		gcp->gc_rx_buf_align = sizeof(uint8_t) - 1;
E 8
I 8
		gcp->gc_rx_buf_align = sizeof (uint8_t) - 1;
E 8
E 4
E 2
		gcp->gc_rx_max_frags = 1;
D 3
		gcp->gc_rx_desc_size = sizeof(struct rx_desc) * RX_RING_SIZE;
E 3
I 3
D 4
		gcp->gc_rx_desc_size = 
			ROUNDUP(sizeof(struct rx_desc) * RX_RING_SIZE, 64);
E 4
I 4
		gcp->gc_rx_desc_unit_shift = 4;	/* 16 byte */
E 4
E 3
D 9
		gcp->gc_rx_ring_size = RX_RING_SIZE;
D 4
		gcp->gc_rx_buf_size  = RX_BUF_SIZE;
		gcp->gc_rx_max_descs_per_pkt = gcp->gc_rx_max_frags;
E 4
I 4
D 6
		gcp->gc_rx_buf_max   = RX_BUF_SIZE;
E 6
I 6
D 8
		gcp->gc_rx_buf_max   = min(RX_BUF_SIZE, RX_RING_SIZE - 1);
E 8
I 8
		gcp->gc_rx_buf_max = min(RX_BUF_SIZE, RX_RING_SIZE - 1);
E 9
I 9
		gcp->gc_rx_ring_size = RX_BUF_SIZE;
		gcp->gc_rx_buf_max = gcp->gc_rx_ring_size - 1;
E 9
E 8
E 6
E 4
		gcp->gc_rx_copy_thresh = vel_rx_copy_thresh;
D 4
		gcp->gc_rx_buf_max   = gcp->gc_rx_buf_size + 1;
E 4

		/* map attributes */
D 6
		STRUCT_COPY(gcp->gc_dev_attr, vel_dev_attr);
		STRUCT_COPY(gcp->gc_buf_attr, vel_buf_attr);
D 2
		STRUCT_COPY(gcp->gc_desc_attr, vel_buf_attr);
E 2
I 2
D 4
		STRUCT_COPY(gcp->gc_desc_attr, vel_dev_attr);
E 4
I 4
		STRUCT_COPY(gcp->gc_desc_attr, vel_buf_attr);
E 6
I 6
D 8
		gcp->gc_dev_attr  = vel_dev_attr;
		gcp->gc_buf_attr  = vel_buf_attr;
E 8
I 8
		gcp->gc_dev_attr = vel_dev_attr;
		gcp->gc_buf_attr = vel_buf_attr;
E 8
		gcp->gc_desc_attr = vel_buf_attr;
E 6
E 4
E 2

		/* dma attributes */
D 6
		STRUCT_COPY(gcp->gc_dma_attr_desc, vel_dma_attr_desc);
		STRUCT_COPY(gcp->gc_dma_attr_txbuf, vel_dma_attr_buf32);
		gcp->gc_dma_attr_txbuf.dma_attr_align  = gcp->gc_tx_buf_align+1;
E 6
I 6
D 8
		gcp->gc_dma_attr_desc  = vel_dma_attr_desc;
E 8
I 8
		gcp->gc_dma_attr_desc = vel_dma_attr_desc;
E 8
D 9
		gcp->gc_dma_attr_txbuf = vel_dma_attr_buf32;
E 9
I 9
		gcp->gc_dma_attr_txbuf = vel_dma_attr_buf;
E 9
D 8
		gcp->gc_dma_attr_txbuf.dma_attr_align = gcp->gc_tx_buf_align+1;
E 8
I 8
		gcp->gc_dma_attr_txbuf.dma_attr_align =
		    gcp->gc_tx_buf_align + 1;
E 8
E 6
		gcp->gc_dma_attr_txbuf.dma_attr_sgllen = gcp->gc_tx_max_frags;
I 8

E 8
D 6
		STRUCT_COPY(gcp->gc_dma_attr_rxbuf, vel_dma_attr_buf32);
		gcp->gc_dma_attr_rxbuf.dma_attr_align  = gcp->gc_rx_buf_align+1;
E 6
I 6
D 9
		gcp->gc_dma_attr_rxbuf = vel_dma_attr_buf32;
E 9
I 9
		gcp->gc_dma_attr_rxbuf = vel_dma_attr_buf;
E 9
D 8
		gcp->gc_dma_attr_rxbuf.dma_attr_align = gcp->gc_rx_buf_align+1;
E 8
I 8
		gcp->gc_dma_attr_rxbuf.dma_attr_align =
		    gcp->gc_rx_buf_align + 1;
E 8
E 6
		gcp->gc_dma_attr_rxbuf.dma_attr_sgllen = gcp->gc_rx_max_frags;

D 2

E 2
		/* timeout parameters */
		gcp->gc_tx_timeout = GEM_TX_TIMEOUT;
		gcp->gc_tx_timeout_interval = GEM_TX_TIMEOUT_INTERVAL;

		/* flow control */
		gcp->gc_flow_control = FLOW_CONTROL_RX_PAUSE;

D 8
                /* mii mode */
E 8
I 8
D 9
		/* mii mode */
E 8
		gcp->gc_mii_mode = GEM_MODE_1000BASET;

E 9
		/* MII timeout parameters */
		gcp->gc_mii_link_watch_interval = GEM_LINK_WATCH_INTERVAL;
		gcp->gc_mii_an_watch_interval = ONESEC/5;
D 8
		gcp->gc_mii_reset_timeout    = MII_RESET_TIMEOUT;
		gcp->gc_mii_an_timeout       = MII_AN_TIMEOUT;
		gcp->gc_mii_an_wait          = 0;
		gcp->gc_mii_linkdown_timeout = MII_LINKDOWN_TIMEOUT; 
E 8
I 8
		gcp->gc_mii_reset_timeout = MII_RESET_TIMEOUT;
		gcp->gc_mii_an_timeout = MII_AN_TIMEOUT;
		gcp->gc_mii_an_wait = 0;
		gcp->gc_mii_linkdown_timeout = MII_LINKDOWN_TIMEOUT;
E 8

		/* workaround for PHY */
D 8
		gcp->gc_mii_an_delay        = ONESEC/10;
D 3
		gcp->gc_mii_linkdown_action = MII_ACTION_RSA;
E 3
I 3
		gcp->gc_mii_linkdown_action = MII_ACTION_NONE;
		gcp->gc_mii_linkdown_timeout_action = MII_ACTION_RSA;
E 3
D 4
		gcp->gc_mii_dont_reset      = FALSE;	/* XXX */
E 4
I 4
		gcp->gc_mii_dont_reset      = B_FALSE;	/* XXX */
E 8
I 8
		gcp->gc_mii_an_delay = ONESEC/10;
D 9
		gcp->gc_mii_linkdown_action = MII_ACTION_RSA;
E 9
I 9
		/* need to reset PHY for autonegotiating 1000Mbps connection */
		gcp->gc_mii_linkdown_action = MII_ACTION_RESET;
E 9
		gcp->gc_mii_linkdown_timeout_action = MII_ACTION_RESET;
D 9
		gcp->gc_mii_dont_reset = B_FALSE;	/* XXX */
E 9
I 9
		gcp->gc_mii_dont_reset = B_FALSE;
E 9
E 8
I 6
		gcp->gc_mii_hw_link_detection = B_FALSE;
E 6
E 4

		/* I/O methods */

		/* mac operation */
		gcp->gc_attach_chip = &vel_attach_chip;
		gcp->gc_reset_chip = &vel_reset_chip;
D 8
		gcp->gc_init_chip  = &vel_init_chip;
E 8
I 8
		gcp->gc_init_chip = &vel_init_chip;
E 8
		gcp->gc_start_chip = &vel_start_chip;
D 8
		gcp->gc_stop_chip  = &vel_stop_chip;
E 8
I 8
		gcp->gc_stop_chip = &vel_stop_chip;
E 8
I 2
D 4
#ifndef USE_MCAST_CAM
E 4
E 2
		gcp->gc_multicast_hash = &vel_mcast_hash;
I 2
D 4
#else
		gcp->gc_multicast_hash = NULL;
#endif
E 4
E 2
		gcp->gc_set_rx_filter = &vel_set_rx_filter;
		gcp->gc_set_media = &vel_set_media;
		gcp->gc_get_stats = &vel_get_stats;
		gcp->gc_interrupt = &vel_interrupt;

		/* descriptor operation */
		gcp->gc_tx_desc_write = &vel_tx_desc_write;
		gcp->gc_rx_desc_write = &vel_rx_desc_write;
I 4
D 8
		gcp->gc_tx_start      = &vel_tx_start;
I 6
		gcp->gc_rx_start      = &vel_rx_start;
E 8
I 8
		gcp->gc_tx_start = &vel_tx_start;
		gcp->gc_rx_start = &vel_rx_start;
E 8
E 6
E 4

		gcp->gc_tx_desc_stat = &vel_tx_desc_stat;
		gcp->gc_rx_desc_stat = &vel_rx_desc_stat;
		gcp->gc_tx_desc_init = &vel_tx_desc_init;
		gcp->gc_rx_desc_init = &vel_rx_desc_init;
		gcp->gc_tx_desc_clean = &vel_tx_desc_init;
		gcp->gc_rx_desc_clean = &vel_rx_desc_init;
D 8
		gcp->gc_get_packet    = &gem_get_packet_default;
E 8
I 8
		gcp->gc_get_packet = &gem_get_packet_default;
E 8

		/* mii operations */
D 8
		gcp->gc_mii_init = &gem_mii_init_default;
E 8
I 8
		gcp->gc_mii_probe = &gem_mii_probe_default;
		gcp->gc_mii_init = NULL;
E 8
		gcp->gc_mii_config = &gem_mii_config_default;
		gcp->gc_mii_sync = &vel_mii_sync;
		gcp->gc_mii_read = &vel_mii_read;
		gcp->gc_mii_write = &vel_mii_write;
		gcp->gc_mii_tune_phy = NULL;

D 8
		lp = (struct vel_dev *)
			kmem_zalloc(sizeof(struct vel_dev), KM_SLEEP);
E 8
I 8
		lp = kmem_zalloc(sizeof (struct vel_dev), KM_SLEEP);
E 8
		lp->revid = revid;
I 8
D 9
		lp->pcie = is_pcie;
E 9
I 9
		lp->pcie = pcie_cap != 0;
E 9
E 8

		/* tursn off SWPTAG right after leaving power down mode */
		val = ddi_get8(regs_ha, (uint8_t *)(base + STICKHW));
		ddi_put8(regs_ha, (uint8_t *)(base + STICKHW),
D 8
					val & ~STICKHW_SWPTAG);
E 8
I 8
		    val & ~STICKHW_SWPTAG);
E 8
		/* clear sticky bit */
		val = ddi_get8(regs_ha, (uint8_t *)(base + STICKHW));
		ddi_put8(regs_ha, ((uint8_t *)base) + STICKHW,
D 8
					val & ~(STICKHW_DS1 | STICKHW_DS0));
E 8
I 8
		    val & ~(STICKHW_DS1 | STICKHW_DS0));
E 8

		/* disable force PME-enable */
D 8
		ddi_put8(regs_ha, (uint8_t *)(base + WOLCFG_CLR),WOLCFG_PMEOVR);
E 8
I 8
		ddi_put8(regs_ha,
		    (uint8_t *)(base + WOLCFG_CLR), WOLCFG_PMEOVR);
E 8

		/* disable power-event config bit */
D 8
		ddi_put16(regs_ha, (uint16_t *)(base + WOLCR_CLR), 0xffff);
E 8
I 8
		ddi_put16(regs_ha, (uint16_t *)(base + WOLCR_CLR), 0xffffU);
E 8

		/* clear power status */
D 8
		ddi_put16(regs_ha, (uint16_t *)(base + PWRCSR_CLR), 0xffff);
E 8
I 8
		ddi_put16(regs_ha, (uint16_t *)(base + PWRCSR_CLR), 0xffffU);
E 8

D 8
		dp = gem_do_attach(dip, gcp, base, &regs_ha, lp, sizeof(*lp));
E 8
I 8
		dp = gem_do_attach(dip, 0,
		    gcp, base, &regs_ha, lp, sizeof (*lp));
E 8

D 8
		kmem_free(gcp, sizeof(*gcp));
E 8
I 8
		kmem_free(gcp, sizeof (*gcp));
E 8
		if (dp == NULL) {
			cmn_err(CE_WARN, "!%s%d: gem_do_attach failed",
D 8
				drv_name, unit);
E 8
I 8
			    drv_name, unit);
E 8
I 2
			goto err_free_mem;
E 2
		}

D 6
		return DDI_SUCCESS;
E 6
I 6
		return (DDI_SUCCESS);
E 6

err_free_mem:
D 8
		kmem_free(lp, sizeof(struct vel_dev));
E 8
I 8
		kmem_free(lp, sizeof (struct vel_dev));
E 8
err:
D 8
		pci_config_teardown(&conf_handle);
E 8
D 6
		return DDI_FAILURE;
E 6
I 6
		return (DDI_FAILURE);
E 6
D 4
#ifdef notdef
	case DDI_RESUME:
	case DDI_PM_RESUME:
		/* vel_reset_chip(dp); */
		/* restart auto negotiation and mii status polling */
		gem_mii_start(dp);

		/* restart the nic */
		  /* init chip */
		  /* set rx filter  */
		  /* start chip  */
		return DDI_SUCCESS;
#endif
E 4
	}
D 6
	return DDI_FAILURE;
E 6
I 6
	return (DDI_FAILURE);
E 6
}

static int
veldetach(dev_info_t *dip, ddi_detach_cmd_t cmd)
{
	switch (cmd) {
I 4
	case DDI_SUSPEND:
D 6
		return gem_suspend(dip);
E 6
I 6
		return (gem_suspend(dip));
E 6

E 4
	case DDI_DETACH:
D 6
		return gem_do_detach(dip);
E 6
I 6
		return (gem_do_detach(dip));
E 6
D 4
#ifdef notdef
	case DDI_SUSPEND:
	case DDI_PM_SUSPEND:
		macinfo->gldm_stop();
		gem_mii_stop();
		return DDI_SUCCESS;
#endif
E 4
	}
D 6
	return DDI_FAILURE;
E 6
I 6
	return (DDI_FAILURE);
E 6
}

/* ======================================================== */
/*
 * OS depend (loadable streams driver) routine
 */
/* ======================================================== */
I 8
#ifdef GEM_CONFIG_GLDv3
D 10
DDI_DEFINE_STREAM_OPS(vel_ops, nulldev, nulldev, velattach, veldetach,
    nodev, NULL, D_MP, NULL);
E 10
I 10
GEM_STREAM_OPS(vel_ops, velattach, veldetach);
E 10
#else
E 8
static	struct module_info velminfo = {
	0,			/* mi_idnum */
	"vel",			/* mi_idname */
	0,			/* mi_minpsz */
D 7
	VELOCITY_MAX_MTU,	/* mi_maxpsz */
	TX_BUF_SIZE*ETHERMAX,	/* mi_hiwat */
E 7
I 7
	INFPSZ,			/* mi_maxpsz */
	64*1024,		/* mi_hiwat */
E 7
	1,			/* mi_lowat */
};

static	struct qinit velrinit = {
	(int (*)()) NULL,	/* qi_putp */
	gem_rsrv,		/* qi_srvp */
	gem_open,		/* qi_qopen */
	gem_close,		/* qi_qclose */
	(int (*)()) NULL,	/* qi_qadmin */
	&velminfo,		/* qi_minfo */
	NULL			/* qi_mstat */
};

static	struct qinit velwinit = {
	gem_wput,		/* qi_putp */
	gem_wsrv,		/* qi_srvp */
	(int (*)()) NULL,	/* qi_qopen */
	(int (*)()) NULL,	/* qi_qclose */
	(int (*)()) NULL,	/* qi_qadmin */
	&velminfo,		/* qi_minfo */
	NULL			/* qi_mstat */
};

static struct streamtab	vel_info = {
	&velrinit,	/* st_rdinit */
	&velwinit,	/* st_wrinit */
	NULL,		/* st_muxrinit */
	NULL		/* st_muxwrinit */
};

static	struct cb_ops cb_vel_ops = {
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
	&vel_info,	/* cb_stream */
D 4
	D_NEW|D_MP	/* cb_flag */
E 4
I 4
	D_MP,		/* cb_flag */
E 4
};

static	struct dev_ops vel_ops = {
	DEVO_REV,	/* devo_rev */
	0,		/* devo_refcnt */
	gem_getinfo,	/* devo_getinfo */
	nulldev,	/* devo_identify */
	nulldev,	/* devo_probe */
	velattach,	/* devo_attach */
	veldetach,	/* devo_detach */
	nodev,		/* devo_reset */
	&cb_vel_ops,	/* devo_cb_ops */
	NULL,		/* devo_bus_ops */
D 4
	ddi_power	/* devo_power */
E 4
I 4
	gem_power	/* devo_power */
E 4
};
D 8

E 8
I 8
#endif /* GEM_CONFIG_GLDv3 */
E 8
static struct modldrv modldrv = {
	&mod_driverops,	/* Type of module.  This one is a driver */
	ident,
	&vel_ops,	/* driver ops */
};

static struct modlinkage modlinkage = {
	MODREV_1, &modldrv, NULL
};

/* ======================================================== */
/*
 * _init :
 */
/* ======================================================== */
int
_init(void)
{
	int 	status;

	DPRINTF(2, (CE_CONT, "!vel: _init: called"));
I 4
	gem_mod_init(&vel_ops, "vel");
E 4
	status = mod_install(&modlinkage);
I 4
	if (status != DDI_SUCCESS) {
		gem_mod_fini(&vel_ops);
	}
E 4

	return (status);
}

/*
D 8
 * _fini : 
E 8
I 8
 * _fini :
E 8
 */
int
_fini(void)
{
	int	status;

	DPRINTF(2, (CE_CONT, "!vel: _fini: called"));
	status = mod_remove(&modlinkage);
I 4
	if (status == DDI_SUCCESS) {
		gem_mod_fini(&vel_ops);
	}
E 4
	return (status);
}

int
_info(struct modinfo *modinfop)
{
	return (mod_info(&modlinkage, modinfop));
}
E 1
