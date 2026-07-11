h14271
s 00087/00077/01870
d D 1.7 11/09/25 17:15:58 mrym 7 6
c 2.6.3 again
e
s 00001/00001/01946
d D 1.6 11/09/23 07:32:49 mrym 6 5
c 2.6.3
e
s 00006/00000/01941
d D 1.5 11/09/23 07:19:02 mrym 5 4
c 2.6.3
e
s 00001/00002/01940
d D 1.4 08/11/27 21:49:14 mrym 4 3
c 2.6.0
e
s 00410/00396/01532
d D 1.3 08/11/03 13:01:34 mrym 3 2
c 2.6.0
e
s 00050/00043/01878
d D 1.2 07/01/13 19:38:41 mrym 2 1
c 2.4.0
e
s 01921/00000/00000
d D 1.1 06/07/16 23:12:27 mrym 1 0
c date and time created 06/07/16 23:12:27 by mrym
e
u
U
f e 0
t
T
I 1
/*
 * rf_gem.c : Realtek RTL8129/813x/810x Fast Ethernet Driver for Solaris
 *
D 2
 * Copyright (c) 2002-2006 Masayuki Murayama.  All rights reserved.
E 2
I 2
D 3
 * Copyright (c) 2002-2007 Masayuki Murayama.  All rights reserved.
E 2
 * 
E 3
I 3
D 6
 * Copyright (c) 2002-2008 Masayuki Murayama.  All rights reserved.
E 6
I 6
 * Copyright (c) 2002-2011 Masayuki Murayama.  All rights reserved.
E 6
 *
E 3
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
D 3
 * 
E 3
I 3
 *
E 3
 * 1. Redistributions of source code must retain the above copyright notice,
D 3
 *    this list of conditions and the following disclaimer. 
 * 
E 3
I 3
 *    this list of conditions and the following disclaimer.
 *
E 3
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
D 3
 *    and/or other materials provided with the distribution. 
 * 
E 3
I 3
 *    and/or other materials provided with the distribution.
 *
E 3
 * 3. Neither the name of the author nor the names of its contributors may be
 *    used to endorse or promote products derived from this software without
D 3
 *    specific prior written permission. 
 * 
E 3
I 3
 *    specific prior written permission.
 *
E 3
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
#pragma ident "%W% %E%"

/*
 *  Changelog:
 01/05/2003 TX DMA burst size (TCR_MXDMAXXX) was fixed  (16byte->128byte)
 01/22/2003 TX DMA burst size (TCR_MXDMAXXX) was changed  (1024)
	0.9.2t release for michael
 01/24/2003 Inter Frame Gap in TCR is too short (8139c data sheet bug)
 01/24/2003 checking method on tx-done fixed according to realtel manual.
	    tx-timeout gone when loopback heatrun test .
 01/25/2003 interrupt processing manner was modified according to realtek manual
	0.9.3t release for michael
 02/02/2003 NOINTR_WORKAROUND added
 03/10/2003 Endianess problem fixed for sparc platform (gem also updated)
 03/22/2003 0.9.7 release
 04/12/2003 ddi_dma_sync added for sparc
 04/20/2003 0.9.8 release
 04/26/2003 FLSH* removed
 05/20/2003 rf_interrupt fixed for missing interrupt of "tx deffered"
 05/20/2003 NOINTR implemented officially
 05/22/2003 0.9.9 release
 05/31/2003 burstsizes in dma attr fixed for sparc
 10/19/2003 MII timeout parameters fixed, 1.0.0 release
 10/23/2003 chip info table modified, 1.0.0 release again
 05/30/2004 interrupts disabled while rf_interrupt().
 05/30/2005 mac address could not be changed.
 */

/*
 * TODO
D 3
    Rx error test (crc error):  done.
    Ensure D0 mode :
E 3
I 3
 *   Rx error test (crc error):  done.
 *   Ensure D0 mode :
E 3
 */
/* ======================================================= */

/*
 * Solaris system header files and macros
 */
#include <sys/types.h>
#include <sys/conf.h>
#include <sys/debug.h>
D 3
#include <sys/stropts.h>
#include <sys/stream.h>
#include <sys/strlog.h>
E 3
#include <sys/kmem.h>
D 3
#include <sys/stat.h>
#include <sys/kstat.h>
#include <sys/vtrace.h>
#include <sys/dlpi.h>
#include <sys/strsun.h>
#include <sys/ethernet.h>
E 3
#include <sys/modctl.h>
#include <sys/errno.h>
D 3
#include <sys/dditypes.h>
E 3
#include <sys/ddi.h>
#include <sys/sunddi.h>
D 3

E 3
I 3
#include <sys/byteorder.h>
#include <sys/ethernet.h>
E 3
#include <sys/pci.h>

I 3
#include "gem_mii.h"
E 3
#include "gem.h"
D 3
#include "mii.h"
E 3
#include "rtl8139reg.h"

char	ident[] = "rtl8129/39 nic driver v" VERSION;
D 2
char	_depends_on[] = {"misc/gld"};
E 2

/*
 * Useful macros
 */
#define	ROUNDUP2(x, y)	(((x)+(y)-1) & ~((y)-1))
D 3
#define	FALSE	B_FALSE
#define	TRUE	(!FALSE)
E 3

D 2
#define	STRUCT_COPY(a, b)	bcopy(&(b), &(a), sizeof(a))

E 2
/*
 * Debugging
 */
#ifdef DEBUG_LEVEL
static int rf_debug = DEBUG_LEVEL;
D 3
#define DPRINTF(n, args)	if (rf_debug > (n)) cmn_err args
E 3
I 3
#define	DPRINTF(n, args)	if (rf_debug > (n)) cmn_err args
E 3
#else
D 3
#define DPRINTF(n, args)
E 3
I 3
#define	DPRINTF(n, args)
E 3
#endif

/*
 * Our configration for rtl8139
 */
/* timeouts */
#define	ONESEC		(drv_usectohz(1*1000000))
D 7
#define	TIM_1us		33
E 7
I 7
#define	TIM_1uS		33
E 7

/*
 * RX/TX buffer size
 */
#define	OUR_RBLEN	RBLEN_64K
#define	OUR_RBLEN_SHIFT	16
#ifdef RX_BUF_NOWRAP
#define	RX_BUFFER_SIZE	\
D 3
	(min(RBLEN(OUR_RBLEN) + ETHERMAX + ETHERFCSL, 0x10000) + RBLEN_PAD)
E 3
I 3
	(min(RBLEN(OUR_RBLEN) + 2048 + RBLEN_PAD, 0x10000))
E 3
#else
D 3
#define	RX_BUFFER_SIZE	(RBLEN(OUR_RBLEN) + RBLEN_PAD)
E 3
I 3
#define	RX_BUFFER_SIZE	(RBLEN(OUR_RBLEN))
E 3
#endif

#ifndef NTXBUF
D 2
#define NTXBUF	32
E 2
I 2
D 3
#define NTXBUF	64
E 3
I 3
#define	NTXBUF	32
E 3
E 2
#endif
D 3
#define TXBUF_LEN	ROUNDUP2(ETHERMAX, 4)
E 3
I 3
#define	TXBUF_LEN	ROUNDUP2(ETHERMAX, 4)
#define	RX_BUF_SIZE	128
E 3

#define	IFG	(12)

D 7
#ifdef TX_DELAYED_INTR
E 7
#define	OUR_INTR_MASK	\
	(INTR_LenChg | INTR_PUN |	\
D 3
	 INTR_SERR | INTR_TIMEOUT | INTR_FOVF | INTR_RXOVW |	\
	 INTR_TER | INTR_RER | INTR_ROK)
E 3
I 3
D 7
	INTR_SERR | INTR_TIMEOUT | INTR_FOVF | INTR_RXOVW |	\
	INTR_TER | INTR_RER | INTR_ROK)
E 3
#else
#define	OUR_INTR_MASK	\
	(INTR_LenChg | INTR_PUN |	\
D 3
	 INTR_SERR | INTR_TIMEOUT | INTR_FOVF | INTR_RXOVW |	\
	 INTR_TER | INTR_TOK | INTR_RER | INTR_ROK)
E 3
I 3
	INTR_SERR | INTR_TIMEOUT | INTR_FOVF | INTR_RXOVW |	\
E 7
I 7
	INTR_SERR | INTR_FOVF | INTR_RXOVW |	\
E 7
	INTR_TER | INTR_TOK | INTR_RER | INTR_ROK)
E 3
D 7
#endif
E 7

static int	rf_tx_copy_thresh = 256;
static int	rf_rx_copy_thresh = INT_MAX;

/*
 * Local device definitions
 */
struct chip_info {
	uint32_t	tcr_val; /* from RTL8139C docs */
	int		flags;
	char		*name;
	int		type;
#define	CHIP_8129	0
#define	CHIP_8139	1
#define	CHIP_8139K	2
#define	CHIP_8139A	3
#define	CHIP_8139A_G	4
#define	CHIP_8139B	5
#define	CHIP_8130	6
#define	CHIP_8139C	7
#define	CHIP_8139CP	8
#define	CHIP_8100	9
#define	CHIP_8100B	10
#define	CHIP_8101L	11
};

struct chip_info chiptbl_8129[] = {
	{0,		0,	"RTL8129",	CHIP_8129},
};

struct chip_info chiptbl_8139[] = {
	{HWREV_8139,	0,	"RTL8139",	CHIP_8139},
	{HWREV_8139K,	0,	"RTL8139 rev K", CHIP_8139K},
	{HWREV_8139A,	0,	"RTL8139A",	CHIP_8139A},
	{HWREV_8139A_G,	0,	"RTL8139A_G",	CHIP_8139A_G},
	{HWREV_8139B,	0,	"RTL8139B",	CHIP_8139B},
	{HWREV_8130,	0,	"RTL8130",	CHIP_8130},
	{HWREV_8139C,	0,	"RTL8139C",	CHIP_8139C},
D 3
	{HWREV_8100,	0,	"RTL8100",	CHIP_8100},	
	{HWREV_8100B,	0,	"RTL8100B/8100C/8139D", CHIP_8100B},	
	{HWREV_8139CP,	0,	"RTL8139C_Plus", CHIP_8139CP},	
	{HWREV_8101L,	0,	"RTL8101L",	CHIP_8101L},	
E 3
I 3
	{HWREV_8100,	0,	"RTL8100",	CHIP_8100},
	{HWREV_8100B,	0,	"RTL8100B/8100C/8139D", CHIP_8100B},
	{HWREV_8139CP,	0,	"RTL8139C_Plus", CHIP_8139CP},
	{HWREV_8101L,	0,	"RTL8101L",	CHIP_8101L},
E 3
};

D 3
#define	CHIPTABLESIZE	(sizeof(chiptbl_8139)/sizeof(struct chip_info))
E 3
I 3
#define	CHIPTABLESIZE	(sizeof (chiptbl_8139) / sizeof (struct chip_info))
E 3

struct rf_dev {
	/*
	 * Misc HW information
	 */
	struct chip_info	*chip;
	uint32_t		rcr;
	uint16_t		rx_curpos;
	boolean_t		need_to_reset;
	uint32_t		imr;
	uint8_t			mac[ETHERADDRL];
	uint_t			tim_1us;
#define	HAVE_TIMER(lp)	((lp)->tim_1us != 0)

D 7
#ifdef TX_DELAYED_INTR
E 7
I 7
#ifdef CONFIG_TX_POLLING
E 7
	uint_t			tx_pkt_len[NTXDESC];
	uint_t			tx_remain;
#endif
D 3
#ifdef GEM_CONFIG_POLLING
E 3
I 3
D 7
#ifdef CONFIG_POLLING
E 7
I 7
#ifdef CONFIG_RX_POLLING
E 7
E 3
	int			last_poll_interval;
#endif
I 3
	uint32_t		tx_desc_addr[NTXDESC];
	uint32_t		tx_desc_len[NTXDESC];
E 3
};

/*
 * private functions
 */

D 2
 
E 2
/* mii operations */
static void  rf_mii_sync(struct gem_dev *);
static uint16_t  rf_mii_read(struct gem_dev *, uint_t);
static void rf_mii_write(struct gem_dev *, uint_t, uint16_t);

/* nic operations */
static int rf_attach_chip(struct gem_dev *);
static int rf_reset_chip(struct gem_dev *);
D 2
static void rf_init_chip(struct gem_dev *);
static void rf_start_chip(struct gem_dev *);
E 2
I 2
static int rf_init_chip(struct gem_dev *);
static int rf_start_chip(struct gem_dev *);
E 2
static int rf_stop_chip(struct gem_dev *);
D 2
static void rf_set_media(struct gem_dev *);
static void rf_set_rx_filter(struct gem_dev *);
static void rf_get_stats(struct gem_dev *);
E 2
I 2
static int rf_set_media(struct gem_dev *);
static int rf_set_rx_filter(struct gem_dev *);
static int rf_get_stats(struct gem_dev *);
E 2

/* descriptor operations */
static int rf_tx_desc_write(struct gem_dev *dp, int slot,
D 3
		    ddi_dma_cookie_t *dmacookie, int frags, uint32_t flags);
E 3
I 3
    ddi_dma_cookie_t *dmacookie, int frags, uint64_t flags);
E 3
static void rf_rx_desc_write(struct gem_dev *dp, int slot,
D 3
		    ddi_dma_cookie_t *dmacookie, int frags);
E 3
I 3
    ddi_dma_cookie_t *dmacookie, int frags);
E 3
static void rf_tx_start(struct gem_dev *dp, int start_slot, int nslot);
static uint_t rf_tx_desc_stat(struct gem_dev *dp, int slot, int ndesc);
static uint64_t rf_rx_desc_stat(struct gem_dev *dp, int slot, int ndesc);

static void rf_tx_desc_init(struct gem_dev *dp, int slot);
static void rf_rx_desc_init(struct gem_dev *dp, int slot);
static void rf_tx_desc_clean(struct gem_dev *dp, int slot);
static void rf_rx_desc_clean(struct gem_dev *dp, int slot);

/* interrupt handler */
D 3
static u_int rf_interrupt(struct gem_dev *dp);
E 3
I 3
static uint_t rf_interrupt(struct gem_dev *dp);
E 3

/* ======================================================== */

/* mapping attributes */
/* Data access requirements. */
static struct ddi_device_acc_attr rf_dev_attr = {
	DDI_DEVICE_ATTR_V0,
	DDI_STRUCTURE_LE_ACC,
	DDI_STRICTORDER_ACC
};

/* On sparc, the buffers should be native endianness */
static struct ddi_device_acc_attr rf_buf_attr = {
	DDI_DEVICE_ATTR_V0,
	DDI_NEVERSWAP_ACC,	/* native endianness */
	DDI_STRICTORDER_ACC
};

static ddi_dma_attr_t rf_dma_attr_txbuf = {
	DMA_ATTR_V0,		/* dma_attr_version */
	0,			/* dma_attr_addr_lo */
	0xffffffffull,		/* dma_attr_addr_hi */
	0xffffffffull,		/* dma_attr_count_max */
	4,			/* dma_attr_align */
	0xffffffff,		/* dma_attr_burstsizes */
	1,			/* dma_attr_minxfer */
	0xffffffffull,		/* dma_attr_maxxfer */
	0xffffffffull,		/* dma_attr_seg */
	1,			/* dma_attr_sgllen */
	1,			/* dma_attr_granular */
	0			/* dma_attr_flags */
};

static ddi_dma_attr_t rf_dma_attr_rxbuf = {
	DMA_ATTR_V0,		/* dma_attr_version */
	0,			/* dma_attr_addr_lo */
	0xffffffffull,		/* dma_attr_addr_hi */
	0xffffffffull,		/* dma_attr_count_max */
	16,			/* dma_attr_align */
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
 * Hardware manupilation
 */
/* =============================================================== */
static int
rf_reset_chip(struct gem_dev *dp)
{
	int		i;
	uint8_t		*m;
	uint32_t	val;
D 3
	struct rf_dev	*lp = (struct rf_dev *)dp->private;
E 3
I 3
	struct rf_dev	*lp = dp->private;
E 3

D 3
#ifdef notdef
E 3
I 3
	DPRINTF(0, (CE_CONT, "!%s: %s: called", dp->name, __func__));
#ifdef notdef /* debug */
E 3
	OUTB(dp, CR9346, CR9346_EEM_WE);
	OUTL(dp, IDR + 0, 0x00888800);
	OUTB(dp, CR9346, CR9346_EEM_NORMAL);

	for (i = 0; i < ETHERADDRL; i++) {
		lp->mac[i] = INB(dp, IDR + i);
	}
#endif
I 3
	OUTW(dp, IMR, 0);

E 3
	OUTB(dp, CR, CR_RST);

D 3
	for (i = 0; (INB(dp, CR) & CR_RST) != 0; i++) {
E 3
I 3
	for (i = 0; (INB(dp, CR) & CR_RST); i++) {
E 3
		if (i > 100) {
			/* time out */
			cmn_err(CE_WARN, "!%s: %s: failed to reset: timeout",
D 3
					dp->name, __func__);
E 3
I 3
			    dp->name, __func__);
E 3
			return (GEM_FAILURE);
		}
		drv_usecwait(10);
	}

	return (GEM_SUCCESS);
}

/*
 * Setup rtl8139
 */
D 2
static void
E 2
I 2
static int
E 2
rf_init_chip(struct gem_dev *dp)
{
	int		i;
	uint32_t	val;
D 3
	struct rf_dev	*lp = (struct rf_dev *)dp->private;
E 3
I 3
	struct rf_dev	*lp = dp->private;
E 3

	DPRINTF(0, (CE_CONT, "!%s: %s: called", dp->name, __func__));

	/* reset rx buffer position */
	lp->rx_curpos = 0;

D 3
	/* ID registers: set later by rf_set_rx_filter */
E 3
I 3
	/* ID registers: set later in rf_set_rx_filter */
E 3

D 3
	/* Multicast registers: set later by rf_set_rx_filter */
E 3
I 3
	/* Multicast registers: set later in rf_set_rx_filter */
E 3

	/* Interrupt status register: do nothing */

	/* Interrupt mask register */
	lp->imr = 0;
	OUTW(dp, IMR, lp->imr);

	/* rx buffer start address */
D 2
	OUTL(dp, RBSTART, dp->rx_ring_dma);
E 2
I 2
	OUTL(dp, RBSTART, dp->io_area_dma);
E 2

	/* Current address of packet read */
	OUTW(dp, CAPR, lp->rx_curpos - RBLEN_PAD);

	/* Current buffer address (RO) */
	ASSERT(INW(dp, CBR) == 0);

	/* Transmit status of descriptors: no need to touch */

	/* Transmit start address of descriptors: no need to touch */

	/* Timer count register: no need to touch */
#ifdef notdef /* moved to rf_attach_chip */
	OUTL(dp, TimInt, 0);
	OUTL(dp, TCTR, 0);
	drv_usecwait(1000);
	lp->tim_1us = INL(dp, TCTR)/1000;
	DPRINTF(1, (CE_CONT, "!%s: tim_1us:%d", dp->name, lp->tim_1us));
#endif
	/* Missed packet counter: clear it */
	OUTL(dp, MPC, 0);

	/* multiple interrupt register: no need to touch */

	/* make BMCR and CONFIG registers writable */
	OUTB(dp, CR9346, CR9346_EEM_WE);

	/* Configuration register 0: no need to change */
	DPRINTF(1, (CE_CONT, "!%s: %s: CONFIG0: 0x%02x",
D 3
			dp->name, __func__, INB(dp, CONFIG0)));
E 3
I 3
	    dp->name, __func__, INB(dp, CONFIG0)));
E 3

D 3
	/* Configuration register 1: enable powermanagement ?*/
E 3
I 3
	/* Configuration register 1: enable powermanagement ? */
E 3
	DPRINTF(1, (CE_CONT, "!%s: %s: CONFIG1: 0x%02x",
D 3
				dp->name, __func__, INB(dp, CONFIG1)));
E 3
I 3
	    dp->name, __func__, INB(dp, CONFIG1)));
E 3

	val = INB(dp, CONFIG1) | CONFIG1_DVRLOAD;
	if (lp->chip->type >= CHIP_8139A) {
		val &= ~CONFIG1_LWACT;
		val |= CONFIG1_PMEn;
		if (lp->chip->type >= CHIP_8139B) {
			val |= CONFIG1_VPD;
		}
D 3
	}
	else {
E 3
I 3
	} else {
E 3
		/* for 8129 / 8139 :  wake the chip up */
		val &= ~(CONFIG1_SLEEP | CONFIG1_PWRDWN);
	}
	OUTB(dp, CONFIG1, val);

	/* Configuration register 3: */
	if (lp->chip->type >= CHIP_8139B) {
		/* Disable Magic packet */
		DPRINTF(1, (CE_CONT, "!%s: %s: CONFIG3: 0x%02x",
D 3
			dp->name, __func__, INB(dp, CONFIG3)));
E 3
I 3
		    dp->name, __func__, INB(dp, CONFIG3)));
E 3
		OUTB(dp, CONFIG3, INB(dp, CONFIG3) & ~CONFIG3_Magic);
	}

	/* Configuration register 4: default:RxFIFOAutoClr=1 */
	if (lp->chip->type >= CHIP_8139) {
		DPRINTF(1, (CE_CONT, "!%s: %s: CONFIG4: 0x%02x",
D 3
			dp->name, __func__, INB(dp, CONFIG4)));
E 3
I 3
		    dp->name, __func__, INB(dp, CONFIG4)));
E 3
		OUTB(dp, CONFIG4, INB(dp, CONFIG4) | CONFIG4_RxFIFOAutoClr);
	}

	/* Configuration register 5: */
	DPRINTF(1, (CE_CONT, "!%s: %s: CONFIG5: 0x%02x",
D 3
			dp->name, __func__, INB(dp, CONFIG5)));
E 3
I 3
	    dp->name, __func__, INB(dp, CONFIG5)));
E 3

	/* make BMCR and config registers read only */
	OUTB(dp, CR9346, CR9346_EEM_NORMAL);
	drv_usecwait(10);

	/* Receive configuration register: don't touch here */
	lp->rcr = 0;

D 7
#ifdef TX_DELAYED_INTR
E 7
I 7
#ifdef CONFIG_TX_POLLING
E 7
D 3
	lp->tx_remain  = 0;
E 3
I 3
	lp->tx_remain = 0;
E 3
#endif
I 3
	/* clear mac address cache */
	bzero(lp->mac, ETHERADDRL);
E 3
I 2

	return (GEM_SUCCESS);
E 2
}

static uint_t
rf_mcast_hash(struct gem_dev *dp, uint8_t *addr)
{
D 3
	return (gem_ether_crc_be(addr, ETHERADDRL));
E 3
I 3
	return (gem_ether_crc_be(addr, ETHERADDRL) >> (32 - 6));
E 3
}

D 2
static void
E 2
I 2
static int
E 2
rf_set_rx_filter(struct gem_dev *dp)
{
	uint32_t	mode;
D 3
	uint32_t	mhash[2];
E 3
I 3
	uint64_t	mhash;
E 3
	int		i;
	uint8_t		*m;
D 3
	struct rf_dev	*lp = (struct rf_dev *)dp->private;
E 3
I 3
	struct rf_dev	*lp = dp->private;
E 3

D 3
	DPRINTF(1, (CE_CONT, "!%s: %s: called", dp->name, __func__));
E 3
I 3
	DPRINTF(0, (CE_CONT, "!%s: %s: called", dp->name, __func__));
E 3

	mode = RCR_AB	/* accept broadcast */
D 3
	     | RCR_APM;	/* accept physical match  */
E 3
I 3
	    | RCR_APM;	/* accept physical match */
E 3

D 3
	if ((dp->rxmode & RXMODE_ALLMULTI) != 0) {
E 3
I 3
	if ((dp->rxmode & RXMODE_ENABLE) == 0) {
		mode = 0;
	} else if ((dp->rxmode & RXMODE_ALLMULTI) || dp->mc_count > 32) {
E 3
		/* accept all multicast packets */
		mode |= RCR_AM;
D 3
		mhash[0] = 0xffffffff;
		mhash[1] = 0xffffffff;
	}	
	else if ((dp->rxmode & RXMODE_PROMISC) != 0) {
E 3
I 3
		mhash = ~0ULL;
	} else if (dp->rxmode & RXMODE_PROMISC) {
E 3
		/* promiscious mode implies all multicast and all physical */
		mode |= RCR_AM | RCR_AAP;
D 3
		mhash[0] = 0xffffffff;
		mhash[1] = 0xffffffff;
	}
	else if (dp->mc_count > 0) {
E 3
I 3
		mhash = ~0ULL;
	} else if (dp->mc_count > 0) {
		/*
		 * make hash table to select interresting
		 * multicast address only.
		 */
E 3
		mode |= RCR_AM;
D 3
		if (dp->mc_count < 64/2) {
			/*
			 * make hash table to select interresting
			 * multicast address only.
			 */
			mhash[0] = 0;
			mhash[1] = 0;
			for (i = 0; i < dp->mc_count; i++) {
				uint_t	h;
				/* hash table is 64 = 2^6 bit width */
				h = dp->mc_list[i].hash >> (32 - 6);
				mhash[h / 32] |= 1 << (h % 32);
			}
E 3
I 3
		mhash = 0ULL;
		for (i = 0; i < dp->mc_count; i++) {
			/* hash table is 64 = 2^6 bit width */
			mhash |= 1ULL << dp->mc_list[i].hash;
E 3
		}
D 3
		else {
			/* too many multicast addresses */
			mhash[0] = 0xffffffff;
			mhash[1] = 0xffffffff;
		}
	}	
E 3
I 3
	}
E 3

	lp->rcr &= ~(RCR_AB | RCR_APM | RCR_AM | RCR_AAP);
I 3
#ifdef notdef	/* debug */
E 3
	if (dp->mac_active) {
D 3
		/* disable all rx filters before changing */
		OUTL(dp, RCR, lp->rcr);
E 3
I 3
		/* enable all rx filters while changing */
		OUTL(dp, MAR + 0, ~0U);
		OUTL(dp, MAR + 4, ~0U);
		OUTL(dp, RCR, lp->rcr | RCR_AB | RCR_APM | RCR_AM | RCR_AAP);
E 3
	}
D 3

	/* set mac address up */	
E 3
I 3
#endif
	/* setup mac address */
E 3
	m = &dp->cur_addr.ether_addr_octet[0];
	if (bcmp(m, lp->mac, ETHERADDRL) != 0) {
		/* make ID registers writable */
		OUTB(dp, CR9346, CR9346_EEM_WE);

		OUTL(dp, IDR + 0,
D 3
			(m[3] << 24) | (m[2] << 16) | (m[1] << 8) | m[0]);
E 3
I 3
		    (m[3] << 24) | (m[2] << 16) | (m[1] << 8) | m[0]);
E 3
		OUTL(dp, IDR + 4, (m[5] <<  8) | m[4]);

		/* make ID registers read only */
		OUTB(dp, CR9346, CR9346_EEM_NORMAL);
		drv_usecwait(10);
I 3

		bcopy(m, lp->mac, ETHERADDRL);
E 3
	}

D 3
	if ((mode & RCR_AM) != 0) {
E 3
I 3
	if (mode & RCR_AM) {
E 3
		/* need to set up multicast hash table */
D 3
		OUTL(dp, MAR + 0, mhash[0]);
		OUTL(dp, MAR + 4, mhash[1]);
E 3
I 3
		OUTL(dp, MAR + 0, (uint32_t)mhash);
		OUTL(dp, MAR + 4, (uint32_t)(mhash >> 32));
E 3
	}

	lp->rcr |= mode;
	if (dp->mac_active) {
		/* update rcr */
		OUTL(dp, RCR, lp->rcr);
	}

	DPRINTF(2, (CE_CONT, "!%s: %s: returned", dp->name, __func__));
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
rf_set_media(struct gem_dev *dp)
{
	uint32_t	val;
D 3
	struct rf_dev	*lp = (struct rf_dev *)dp->private;
E 3
I 3
	struct rf_dev	*lp = dp->private;
E 3

D 3
	DPRINTF(2, (CE_CONT, "!%s: %s: called", dp->name, __func__));
E 3
I 3
	DPRINTF(0, (CE_CONT, "!%s: %s: called", dp->name, __func__));
E 3

	/* select duplex */

	if (lp->chip->type == CHIP_8129) {
		/* make BMCR and CONFIG registers writable */
		OUTB(dp, CR9346, CR9346_EEM_WE);

		val = INB(dp, CONFIG1) & ~CONFIG1_FULL;
		if (dp->full_duplex) {
			val |= CONFIG1_FULL;
		}
		OUTB(dp, CONFIG1, val);

		OUTB(dp, CR9346, CR9346_EEM_NORMAL);
		drv_usecwait(10);
	}

	/* select speed: do nothing */

	/* flow control */
D 3
	val = INB(dp, MSR) & ~(MSR_TXFCE | MSR_RXFCE); 
E 3
I 3
	val = INB(dp, MSR) & ~(MSR_TXFCE | MSR_RXFCE);
E 3

	switch (dp->flow_control) {
	case FLOW_CONTROL_RX_PAUSE:
		val |= MSR_RXFCE;
		break;

	case FLOW_CONTROL_TX_PAUSE:
		val |= MSR_TXFCE;
		break;

	case FLOW_CONTROL_SYMMETRIC:
D 3
		val |= MSR_TXFCE | MSR_RXFCE; 
E 3
I 3
		val |= MSR_TXFCE | MSR_RXFCE;
E 3
		break;
	}

	OUTB(dp, MSR, val);

	DPRINTF(2, (CE_CONT, "!%s: %s: returned", dp->name, __func__));
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
rf_start_chip(struct gem_dev *dp)
{
	uint32_t	val;
D 3
	struct rf_dev	*lp = (struct rf_dev *)dp->private;
E 3
I 3
	struct rf_dev	*lp = dp->private;
E 3

D 3
	DPRINTF(1, (CE_CONT, "!%s: %s: called", dp->name, __func__));
E 3
I 3
	DPRINTF(0, (CE_CONT, "!%s: %s: called", dp->name, __func__));
E 3

	/* Command register : Enable Tx and Rx before writing TCR and RCR */
	OUTB(dp, CR, CR_RE | CR_TE);

	/* Transmit configration register : */
	if (dp->txmaxdma <= 16) {
		val = TCR_MXDMA_16;
	} else if (dp->txmaxdma <= 32) {
		val = TCR_MXDMA_32;
	} else if (dp->txmaxdma <= 64) {
		val = TCR_MXDMA_64;
	} else if (dp->txmaxdma <= 128) {
		val = TCR_MXDMA_128;
	} else if (dp->txmaxdma <= 256) {
		val = TCR_MXDMA_256;
	} else if (dp->txmaxdma <= 512) {
		val = TCR_MXDMA_512;
	} else if (dp->txmaxdma <= 1024) {
		val = TCR_MXDMA_1024;
	} else {
		val = TCR_MXDMA_2048;
	}
	OUTL(dp, TCR, TCR_IFG_802_3 | TCR_LBK_NORMAL | val);

	/* Receive configuration register : */
	val = 0;
	if (dp->rxmaxdma <= 16) {
		val |= RCR_MXDMA_16;
	} else if (dp->rxmaxdma <= 32) {
		val |= RCR_MXDMA_32;
	} else if (dp->rxmaxdma <= 64) {
		val |= RCR_MXDMA_64;
D 3
	} else if (dp->rxmaxdma<= 128) {
E 3
I 3
	} else if (dp->rxmaxdma <= 128) {
E 3
		val |= RCR_MXDMA_128;
D 3
	} else if (dp->rxmaxdma<= 256) {
E 3
I 3
	} else if (dp->rxmaxdma <= 256) {
E 3
		val |= RCR_MXDMA_256;
D 3
	} else if (dp->rxmaxdma<= 512) {
E 3
I 3
	} else if (dp->rxmaxdma <= 512) {
E 3
		val |= RCR_MXDMA_512;
D 3
	} else if (dp->rxmaxdma<= 1024) {
E 3
I 3
	} else if (dp->rxmaxdma <= 1024) {
E 3
		val |= RCR_MXDMA_1024;
	} else {
		val |= RCR_MXDMA_UNLIMIT;
	}
	if (dp->rxthr <= 16) {
		val |= RCR_RXFTH_16;
	} else if (dp->rxthr <= 32) {
		val |= RCR_RXFTH_32;
	} else if (dp->rxthr <= 64) {
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
		val |= RCR_RXFTH_NONE;
	}

	lp->rcr |= RCR_ERTH_NONE | RCR_RER8 | val
D 3
		| (OUR_RBLEN << RCR_RBLEN_SHIFT)
#ifdef NOWRAP
		| RCR_WRAP
E 3
I 3
	    | (OUR_RBLEN << RCR_RBLEN_SHIFT)
#ifdef RX_BUF_NOWRAP
	    | RCR_WRAP
E 3
#endif
D 3
		| RCR_AER | RCR_AR;
E 3
I 3
	    | RCR_AER | RCR_AR;
E 3

	OUTL(dp, RCR, lp->rcr);

	/* Enable interrupts */
	lp->imr = OUR_INTR_MASK;
D 7
	if (!HAVE_TIMER(lp)) {
		lp->imr |= INTR_TOK;
		lp->imr &= ~INTR_TIMEOUT;
E 7
I 7
#ifdef CONFIG_TX_POLLING
	if (HAVE_TIMER(lp)) {
		lp->imr &= ~INTR_TOK;
		lp->imr |= INTR_TIMEOUT;
E 7
	}
D 7

E 7
I 7
#endif
#ifdef CONFIG_RX_POLLING
	if (HAVE_TIMER(lp)) {
		lp->imr |= INTR_TIMEOUT;
	}
#endif
E 7
	if ((dp->misc_flag & GEM_NOINTR) == 0) {
		OUTW(dp, IMR, lp->imr);
	}
I 2

	return (GEM_SUCCESS);
E 2
}

static int
rf_stop_chip(struct gem_dev *dp)
{
D 3
	struct rf_dev	*lp = (struct rf_dev *)dp->private;
E 3
I 3
	struct rf_dev	*lp = dp->private;
E 3

	DPRINTF(0, (CE_CONT, "!%s: %s: called", dp->name, __func__));

D 3
	/* disable all rx filters */
E 3
I 3
	/* disable the rx filter completely */
E 3
	lp->rcr &= ~(RCR_AB | RCR_APM | RCR_AM | RCR_AAP);
	OUTL(dp, RCR, lp->rcr);

	/* disable interrupts */
I 3
D 7
	/* XXX - don't clear lp->imr to process delayed interrupts */
E 7
I 7
	/*
	 * don't clear lp->imr and the interrupt source to process interrupts
	 * correctly, that we may have now.
	 */
E 7
#ifdef NEVER
E 3
	lp->imr = 0;
D 3
	OUTW(dp, IMR, lp->imr);
E 3
I 3
#endif
	OUTW(dp, IMR, 0);
E 3
D 7

D 3
	/* Clear pended interrupt */
E 3
I 3
	/* XXX - Don't clear interrupt source to process delayed interrupts */
E 7
#ifdef NEVER
E 3
	OUTW(dp, ISR, 0xffff);
I 3
#endif
E 3

	/* disable RX and TX */
	OUTB(dp, CR, 0);
	drv_usecwait(2000);

	return (GEM_SUCCESS);
}

D 2
static void
E 2
I 2
static int
E 2
rf_get_stats(struct gem_dev *dp)
{
	/* read missed count */
	dp->stats.missed += INL(dp, MPC);

	/* clear missed count */
	OUTL(dp, MPC, 0);
I 2

	return (GEM_SUCCESS);
E 2
}


/*
 * discriptor  manupiration
 */
D 7
#define	rf_sched_timer(dp)	\
{	\
	uint32_t	clks;	\
D 3
	struct rf_dev	*lp = (struct rf_dev *)(dp)->private;	\
E 3
I 3
	struct rf_dev	*lp = (dp)->private;	\
E 3
	\
	if (dp->speed == GEM_SPD_100) {	\
		clks = lp->tim_1us * (lp->tx_remain * 8) / 100;	\
	} else {	\
		clks = lp->tim_1us * (lp->tx_remain * 8) / 10;	\
	}	\
	clks = (clks/8) * 7;	\
D 3
	clks += INL(dp, TCTR);	\
E 3
	OUTL(dp, TimInt, clks ? clks : 1); \
I 3
	OUTL(dp, TCTR, 0);	\
E 3
}
E 7
I 7
#ifdef CONFIG_TX_POLLING
__INLINE__ static void
rf_sched_tx_timer(struct gem_dev *dp)
{
	uint32_t	clks;
	struct rf_dev	*lp = (dp)->private;
E 7

I 7
	if (dp->speed == GEM_SPD_100) {
		clks = lp->tim_1us * (lp->tx_remain * 8) / 100;
	} else {
		clks = lp->tim_1us * (lp->tx_remain * 8) / 10;
	}
	clks = (clks/8) * 7;
	OUTL(dp, TimInt, max(clks, 1));
	OUTL(dp, TCTR, 0);
}
#pragma inline(rf_sched_tx_timer)
#endif
E 7
static int
rf_tx_desc_write(struct gem_dev *dp, int slot,
D 3
		ddi_dma_cookie_t *dmacookie, int frags, uint32_t intreq)
E 3
I 3
    ddi_dma_cookie_t *dmacookie, int frags, uint64_t flags)
E 3
{
	int		len;
	int		i;
D 3
	struct rf_dev	*lp = (struct rf_dev *)dp->private;
E 3
I 3
	struct rf_dev	*lp = dp->private;
E 3

#if DEBUG_LEVEL > 2
	cmn_err(CE_CONT,
D 3
    "!%s: time:%d rf_tx_desc_write seqnum: %d, slot %d, frags: %d flags: %d",
		dp->name, ddi_get_lbolt(),
		dp->tx_desc_tail, slot, frags, intreq);
E 3
I 3
	    "!%s: time:%d %s seqnum: %d, slot %d, frags: %d flags: %llx",
	    dp->name, ddi_get_lbolt(), __func__,
	    dp->tx_desc_tail, slot, frags, flags);
E 3
	for (i = 0; i < frags; i++) {
		cmn_err(CE_CONT, "!    %d: addr: 0x%x, len: 0x%x",
D 3
			i, dmacookie[i].dmac_address, dmacookie[i].dmac_size);
E 3
I 3
		    i, dmacookie[i].dmac_address, dmacookie[i].dmac_size);
E 3
	}
#endif
D 3

E 3
	OUTL(dp, TSAD + slot*4, dmacookie->dmac_address);

	/* use early transmission for performance */
	len = dmacookie->dmac_size & TSR_SIZE;

	/* early tx does not seem to work in 10M half mode */
	OUTL(dp, TSD  + slot*4, TSR_ERTXTH(dp->txthr) | len);

D 7
#ifdef TX_DELAYED_INTR
E 7
I 7
#ifdef CONFIG_TX_POLLING
E 7
	if (HAVE_TIMER(lp)) {
		lp->tx_remain += lp->tx_pkt_len[slot] = len + IFG;
D 3
		if (intreq != 0) {
E 3
I 3
		if (flags & GEM_TXFLAG_INTR) {
E 3
D 7
			rf_sched_timer(dp);
E 7
I 7
			rf_sched_tx_timer(dp);
E 7
		}
	}
#endif
	return (1);
}

static void
rf_rx_desc_write(struct gem_dev *dp, int slot,
D 3
		ddi_dma_cookie_t *dmacookie, int frags)
E 3
I 3
	ddi_dma_cookie_t *dmacookie, int frags)
E 3
{
D 3
	/* do nothing */
E 3
I 3
	/* EMPTY */
E 3
}

static void
rf_tx_start(struct gem_dev *dp, int start_slot, int nslot)
{
	/* nothing to do */
}

static uint_t
rf_tx_desc_stat(struct gem_dev *dp, int slot, int ndesc)
{
	uint32_t	tsr;
	uint32_t	val;
	uint32_t	errbits;
D 3
	struct rf_dev	*lp = (struct rf_dev *)dp->private;
E 3
I 3
	struct rf_dev	*lp = dp->private;
E 3

	tsr = INL(dp, TSD + slot*4);

	DPRINTF(3, (CE_CONT,
D 3
	"!%s: time:%d rf_tx_desc_stat: seqnum: %d, slot %d, tsr: %b",
		dp->name, ddi_get_lbolt(),
		dp->tx_desc_head, slot, tsr, TX_STATUS_BITS));
E 3
I 3
	    "!%s: time:%d rf_tx_desc_stat: seqnum: %d, slot %d, tsr: %b",
	    dp->name, ddi_get_lbolt(),
	    dp->tx_desc_head, slot, tsr, TX_STATUS_BITS));
E 3

	if ((tsr & (TSR_TOK | TSR_TABT | TSR_TUN)) == 0) {
		/*
		 * The packet is under transmitting. Wait.
		 */
		return (0);
	}

D 3
	if ((tsr & TSR_TUN) != 0) {
E 3
I 3
	if (tsr & TSR_TUN) {
E 3
		/* this may happen when early tx */
		dp->stats.underflow++;
		dp->txthr = min(ETHERMAX, dp->txthr*2);
		DPRINTF(0, (CE_WARN,
D 3
			"!%s: tx fifo underflow happened",
			dp->name));
E 3
I 3
		    "!%s: tx fifo underflow happened",
		    dp->name));
E 3
	}

	errbits = TSR_TABT | TSR_OWC | TSR_CRS;
	if (!dp->full_duplex) {
		/* CRS seems not reliable in 100mbps half duplex mode */
		errbits &= ~TSR_CRS;
	}

D 3
	if ((tsr & errbits) != 0) {
E 3
I 3
	if (tsr & errbits) {
E 3
		dp->stats.errxmt++;
		DPRINTF(4, (CE_CONT, "!%s: tx err: tsr:%b",
D 3
			dp->name, tsr, TX_STATUS_BITS));
E 3
I 3
		    dp->name, tsr, TX_STATUS_BITS));
E 3

D 3
		if ((tsr & TSR_CRS & errbits) != 0) {
E 3
I 3
		if (tsr & TSR_CRS & errbits) {
E 3
			/* carrier lost */
			dp->stats.nocarrier++;
D 3
		} else if ((tsr & TSR_OWC & errbits) != 0) {
E 3
I 3
		}
		if (tsr & TSR_OWC & errbits) {
E 3
			/* late collision */
			dp->stats.xmtlatecoll++;
D 3
		} else {
E 3
I 3
		}
		if (tsr & TSR_TABT & errbits) {
E 3
			/* max collision exceeded */
			dp->stats.excoll++;
			dp->stats.collisions += 16;
D 3
		}

		if ((tsr & TSR_TABT) != 0) {
			DPRINTF(2, (CE_WARN, "!%s: tx aborted", dp->name));
E 3
I 3
			DPRINTF(2, (CE_NOTE, "!%s: tx aborted", dp->name));
E 3
			OUTB(dp, TCR, (INB(dp, TCR) & TCR_TXRR) | TCR_CLRABT);
D 3

E 3
			/*
D 3
			 * Don't advance current tx pointer as we 
E 3
I 3
			 * Don't advance current tx pointer as we
E 3
			 * issued TCR_CLRABT above.
			 */
			return (0);
		}
D 3
	}
	else {
		if ((val = (tsr & TSR_NCC)) != 0) {
E 3
I 3
	} else {
		if (val = (tsr & TSR_NCC)) {
E 3
			val >>= TSR_NCC_SHIFT;
			dp->stats.collisions += val;
			if (val == 1) {
				dp->stats.first_coll++;
			} else {
				dp->stats.multi_coll++;
			}
		}
	}
D 7
#ifdef TX_DELAYED_INTR
E 7
I 7
#ifdef CONFIG_TX_POLLING
E 7
	if (HAVE_TIMER(lp)) {
		lp->tx_remain -= lp->tx_pkt_len[slot];
	}
#endif
	return (GEM_TX_DONE);
}

static mblk_t *
rf_get_packet(struct gem_dev *dp, struct rxbuf *rbp, size_t len)
{
I 3
	uint16_t	rsr;
	uint16_t	*p;
E 3
	size_t		rest;
	uint16_t	offset;
D 3
	mblk_t		*mp;
	struct rf_dev	*lp = (struct rf_dev *)dp->private;
E 3
I 3
	mblk_t		*mp = NULL;
	struct rf_dev	*lp = dp->private;
E 3

I 3
	/* get receive status and packet length */
	offset = lp->rx_curpos & (RBLEN(OUR_RBLEN) - 1);
	p = (uint16_t *)&dp->io_area[offset];

	/* read rx header atomicly */
	rsr = p[0];
	rsr = LE_16(rsr);

	DPRINTF(2, (CE_CONT,
	    "!%s: time:%d %s: status:%b len:%d at offset:0x%04x cur:0x%04x",
	    dp->name, ddi_get_lbolt(), __func__,
	    rsr, RSR_BITS, len, offset, lp->rx_curpos));

E 3
	/* read packet and advance current position */
D 2
	offset = (lp->rx_curpos + 4) & (RBLEN(OUR_RBLEN) - 1);
E 2
I 2
D 3
	offset = (dp->io_area - dp->rx_ring)
	       + (lp->rx_curpos + 4) & (RBLEN(OUR_RBLEN) - 1);
E 3
I 3
	offset = (lp->rx_curpos + 4) & (RBLEN(OUR_RBLEN) - 1);
E 3
E 2

	/* update current position */
D 3
	lp->rx_curpos += ROUNDUP2(4/* header size */ + len + ETHERFCSL, 4);
E 3
I 3
	lp->rx_curpos += ROUNDUP2(4 /* header size */ + len + ETHERFCSL, 4);
E 3

I 3
	/* check if any errors happened */
#ifdef GEM_CONFIG_GLDv3	/* for vlan */
#define	RSR_ERROR	(RSR_ISE | RSR_FAE | RSR_RUNT | RSR_CRC)
	if (rsr & (RSR_ERROR))
#else
	if ((rsr & (RSR_ROK)) == 0)
#endif
	{
		DPRINTF(0, (CE_CONT, "!%s: rsr:%b", dp->name, rsr, RSR_BITS));
		dp->stats.errrcv++;
		if (rsr & (RSR_ISE | RSR_FAE)) {
			dp->stats.frame++;
		} else if (rsr & RSR_RUNT) {
			dp->stats.runt++;
#ifndef GEM_CONFIG_GLDv3	/* for vlan */
		} else if (rsr & RSR_LONG) {
			dp->stats.frame_too_long++;
#endif
		} else if (rsr & RSR_CRC) {
			dp->stats.crc++;
		} else {
			dp->stats.rcv_internal_err++;
		}

		/*
		 * Need to reset the chip to recover from error state
		 */
		lp->need_to_reset = B_TRUE;
		goto done;
	}

E 3
	/* aquire packet buffer */
	if ((mp = allocb(len, BPRI_MED)) == NULL) {
		/*
		 * No receive buffer, OS resource exaust
		 */
		dp->stats.norcvbuf++;
D 3
	}
	else {
E 3
I 3
		dp->stats.errrcv++;
	} else {
E 3
		mp->b_wptr = mp->b_rptr + len;
D 3
#if defined(NOWRAP) && (OUR_RBLEN != RBLEN_64K)
D 2
		ddi_dma_sync(dp->desc_dma_handle, (off_t)offset, len,
E 2
I 2
		ddi_dma_sync(dp->desc_dma_handle, (off_t) offset, len,
E 2
			DDI_DMA_SYNC_FORKERNEL);
E 3
I 3
#if defined(RX_BUF_NOWRAP) && (OUR_RBLEN != RBLEN_64K)
		ddi_dma_sync(dp->desc_dma_handle,
		    (off_t)(offset + (dp->io_area - dp->rx_ring)), len,
		    DDI_DMA_SYNC_FORKERNEL);
E 3

D 2
		bcopy(dp->rx_ring + offset, mp->b_rptr, len);
E 2
I 2
		bcopy(dp->io_area + offset, mp->b_rptr, len);
E 2
#else
		rest = min(RBLEN(OUR_RBLEN) - offset, len);
D 2
		ddi_dma_sync(dp->desc_dma_handle, (off_t)offset, rest,
E 2
I 2
D 3
		ddi_dma_sync(dp->desc_dma_handle, (off_t) offset, rest,
E 2
			DDI_DMA_SYNC_FORKERNEL);
E 3
I 3
		ddi_dma_sync(dp->desc_dma_handle,
		    (off_t)(offset + (dp->io_area - dp->rx_ring)), rest,
		    DDI_DMA_SYNC_FORKERNEL);
E 3

D 2
		bcopy(dp->rx_ring + offset, mp->b_rptr, rest);
E 2
I 2
		bcopy(dp->io_area + offset, mp->b_rptr, rest);
E 2
		if ((len -= rest) > 0) {
D 3
			ddi_dma_sync(dp->desc_dma_handle, (off_t) 0, len,
				DDI_DMA_SYNC_FORKERNEL);
E 3
I 3
			ddi_dma_sync(dp->desc_dma_handle, (off_t)0, len,
			    DDI_DMA_SYNC_FORKERNEL);
E 3

D 2
			bcopy(dp->rx_ring, mp->b_rptr + rest, len);
E 2
I 2
			bcopy(dp->io_area, mp->b_rptr + rest, len);
E 2
		}
#endif
	}
D 3

E 3
I 3
done:
E 3
	/* set new limit */
	OUTW(dp, CAPR, lp->rx_curpos - RBLEN_PAD);
D 3

E 3
	return (mp);
}

static uint64_t
rf_rx_desc_stat(struct gem_dev *dp, int slot, int ndesc)
{
	size_t		len;
	uint16_t	rsr;
	uint16_t	offset;
D 3
	uint8_t		*p;
	struct rf_dev	*lp = (struct rf_dev *)dp->private;
E 3
I 3
	uint16_t	*p;
	struct rf_dev	*lp = dp->private;
E 3

D 3
	/* test receive status */
	if ((INB(dp, CR) & CR_BUFE) != 0) {
E 3
I 3
	if (INB(dp, CR) & CR_BUFE) {
E 3
		/* Rx buffer is empty */
		return (0);
	}

D 2
	offset = lp->rx_curpos & (RBLEN(OUR_RBLEN) - 1);
E 2
I 2
D 3
	offset = (dp->io_area - dp->rx_ring)
	       + (lp->rx_curpos & (RBLEN(OUR_RBLEN) - 1));
E 2
	ddi_dma_sync(dp->desc_dma_handle, (off_t)offset, 4,
		DDI_DMA_SYNC_FORKERNEL);
E 3
I 3
	offset = lp->rx_curpos & (RBLEN(OUR_RBLEN) - 1);
	ddi_dma_sync(dp->desc_dma_handle,
	    (off_t)(offset + (dp->io_area - dp->rx_ring)), 4,
	    DDI_DMA_SYNC_FORKERNEL);
E 3

	/* get receive status and packet length */
D 2
	p = (uint8_t *) &dp->rx_ring[offset];
E 2
I 2
D 3
	p = (uint8_t *) &dp->io_area[offset];
E 3
I 3
	p = (uint16_t *)&dp->io_area[offset];
E 3
E 2

D 3
	/* read Rx header */
	rsr = (p[1] << 8) | p[0];
	len = (p[3] << 8) | p[2];
E 3
I 3
	/* read rx header atomicly */
	rsr = p[0];
	rsr = LE_16(rsr);
	len = p[1];
	len = LE_16(len);
E 3

	DPRINTF(2, (CE_CONT,
D 3
	   "!%s: time:%d %s: status:%b len:%d at offset:0x%04x cur:0x%04x",
		dp->name, ddi_get_lbolt(), __func__,
		rsr, RSR_BITS, len, offset, lp->rx_curpos));
E 3
I 3
	    "!%s: time:%d %s: status:%b len:%d at offset:0x%04x cur:0x%04x",
	    dp->name, ddi_get_lbolt(), __func__,
	    rsr, RSR_BITS, len, offset, lp->rx_curpos));
E 3

	if (len == 0xfff0) {
		/* 8139 is busy to copy a packet into memory */
		return (0);
	}

D 3
	/* check if error happen */
D 2
#ifdef CONFIG_VLAN
E 2
I 2
#ifdef GEM_CONFIG_VLAN
E 2
#define RSR_ERROR	(RSR_ISE | RSR_FAE | RSR_RUNT | RSR_CRC)
	if ((rsr & (RSR_ERROR)) != 0)
#else
	if ((rsr & (RSR_ROK)) == 0)
#endif
	{
		DPRINTF(0, (CE_CONT, "!%s: rsr:%b", dp->name, rsr, RSR_BITS));
		if ((rsr & (RSR_ISE | RSR_FAE)) != 0) {
			dp->stats.frame++;
		}
		if ((rsr & RSR_RUNT) != 0) {
			dp->stats.runt++;
		}
D 2
#ifndef CONFIG_VLAN
E 2
I 2
#ifndef GEM_CONFIG_VLAN
E 2
		if ((rsr & RSR_LONG) != 0) {
			dp->stats.frame_too_long++;
		}
#endif
		if ((rsr & RSR_CRC) != 0) {
			dp->stats.crc++;
		}
		dp->stats.errrcv++;

		/*
		 * Need to reset the chip to recover from error state
		 */
		lp->need_to_reset = TRUE;
		return (GEM_RX_ERR);
E 3
I 3
	if (len > ETHERFCSL) {
		/* remove crc code */
		len -= ETHERFCSL;
E 3
	}
D 2
#ifndef CONFIG_VLAN
E 2
I 2
D 3
#ifndef GEM_CONFIG_VLAN
E 2
	if (len > ETHERMAX + ETHERFCSL || len < ETHERMIN + ETHERFCSL) {
		if (len > ETHERMAX + ETHERFCSL) {
			dp->stats.frame_too_long++;
		} else {
			dp->stats.runt++;
		}
E 3

D 3
		/*
		 * Need to reset the chip to recover from error state
		 */
		lp->need_to_reset = TRUE;
		return (GEM_RX_ERR);
	}
D 2
#endif /* CONFIG_VLAN */
E 2
I 2
#endif /* GEM_CONFIG_VLAN */
E 2
	/* remove crc code */
	len -= ETHERFCSL;

E 3
	return (GEM_RX_DONE | (len & GEM_RX_LEN));
}

static void
rf_tx_desc_init(struct gem_dev *dp, int slot)
{
	OUTL(dp, TSD + slot*4, 0);
}

static void
rf_rx_desc_init(struct gem_dev *dp, int slot) { return; }

static void
rf_tx_desc_clean(struct gem_dev *dp, int slot)
{
	OUTL(dp, TSD + slot*4, 0);
}

static void
rf_rx_desc_clean(struct gem_dev *dp, int slot) { return; }

/*
 * Device depend interrupt handler
 */
D 3
static u_int
E 3
I 3
static uint_t
E 3
rf_interrupt(struct gem_dev *dp)
{
	uint16_t	isr;
I 7
	uint16_t	imr;
E 7
D 3
	u_int		restart_tx = 0;
	struct rf_dev	*lp = (struct rf_dev *)dp->private;
E 3
I 3
	uint_t		restart_tx = 0;
	boolean_t	update_imr = B_FALSE;
	struct rf_dev	*lp = dp->private;
E 3

	/* XXX - reading ISR does not clear interrupt source */
	isr = INW(dp, ISR);
D 7
	if ((isr & lp->imr) == 0) {
E 7
I 7
	imr = lp->imr;
	if ((isr & imr) == 0) {
E 7
		/* not for us */
I 7
#ifdef NEVER
		/*
		 * Don't clear TOK and ROK interrupt source bits,
		 * they may be serviced later, in case of TX/RX polling.
		 */
E 7
D 3
		if (isr != 0) {
E 3
I 3
		if (isr) {
E 3
			OUTW(dp, ISR, isr);
		}
I 7
#endif
E 7
		return (DDI_INTR_UNCLAIMED);
	}

D 3
	DPRINTF(2, (CE_CONT,"!%s: time:%d rf_interrupt: isr:%b imr:%b",
		dp->name, ddi_get_lbolt(), isr, INTR_BITS,
		INW(dp, IMR), INTR_BITS));

	/* disable interrupts */
	OUTW(dp, IMR, 0);

E 3
I 3
	DPRINTF(2, (CE_CONT, "!%s: time:%d %s: isr:%b imr:%b",
	    dp->name, ddi_get_lbolt(), __func__, isr, INTR_BITS,
	    INW(dp, IMR), INTR_BITS));
D 7
#ifndef CONFIG_OPT_IO
	if ((dp->misc_flag & GEM_NOINTR) == 0) {
		/* disable interrupts */
		OUTW(dp, IMR, 0);
		update_imr = B_TRUE;
	}
#endif
E 7
I 7

E 7
E 3
	if (!dp->mac_active) {
D 3
		/* inhibit interrupt for ever */
E 3
I 3
		/* no futher interrupts */
E 3
		lp->imr = 0;
I 3
D 7
#ifdef CONFIG_OPT_IO
E 7
		OUTW(dp, IMR, lp->imr);
D 7
#endif
E 7
I 7

E 7
E 3
		/* ack to all interrupts */
		OUTW(dp, ISR, 0xffff);
		return (DDI_INTR_CLAIMED);
	}

D 3
	OUTW(dp, ISR, isr);
#ifdef notdef
E 3
D 7
	/* clear interrupt sources explicitly */
I 3
	OUTW(dp, ISR, isr);

E 3
	isr &= lp->imr;
D 3
#endif
E 3

D 3
#ifdef GEM_CONFIG_POLLING
E 3
I 3
#ifdef TX_DELAYED_INTR
E 7
I 7
#ifdef CONFIG_TX_POLLING
E 7
	if (isr & INTR_TIMEOUT) {
D 7
		isr |= INTR_TOK;
E 7
I 7
		imr |= INTR_TOK;
E 7
	}
#endif
D 7
#ifdef CONFIG_POLLING
E 7
I 7
#ifdef CONFIG_RX_POLLING
E 7
	if (isr & INTR_TIMEOUT) {
D 7
		isr |= INTR_ROK;
E 7
I 7
		imr |= INTR_ROK;
E 7
	}
E 3
D 7
	if (dp->speed == GEM_SPD_100 &&
E 7
I 7

	if (dp->speed == GEM_SPD_100 && HAVE_TIMER(lp) &&
E 7
	    dp->poll_interval != lp->last_poll_interval) {
D 3
		if (dp->poll_interval != 0) {
			/* polling mode */
			lp->imr = OUR_INTR_MASK & ~(INTR_ROK);

			if (lp->last_poll_interval == 0) {
				/*
				 * To schedule the next timer interrupt,
				 * we pretend as we were interrupted from
				 * polling timer
				 */
				isr |= INTR_TIMEOUT;
			}
E 3
I 3
		if (lp->last_poll_interval == 0) {
			/*
			 * To schedule the next timer interrupt,
			 * we pretend as we were interrupted from
			 * polling timer
			 */
			isr |= INTR_TIMEOUT;
E 3
		}
D 3
		else {
			/* normal mode */
			lp->imr = OUR_INTR_MASK;
		}
E 3
		lp->last_poll_interval = dp->poll_interval;
	}
D 3
#endif /* GEM_CONFIG_POLLING */
E 3
I 3
#endif /* CONFIG_POLLING */
E 3

I 7
	/* clear interrupt sources explicitly */
	isr &= imr;
	OUTW(dp, ISR, isr);

E 7
D 3
	if ((isr & (INTR_LenChg | INTR_PUN)) != 0) {
E 3
I 3
	if (isr & (INTR_LenChg | INTR_PUN)) {
E 3
		/*
		 * Link or PHY status changed
		 */
		DPRINTF(2, (CE_CONT, "!%s: isr:%b",
D 3
			dp->name, isr, INTR_BITS));
E 3
I 3
		    dp->name, isr, INTR_BITS));
E 3
		if (gem_mii_link_check(dp)) {
			restart_tx = INTR_RESTART_TX;
		}
	}

D 3
	if ((isr & (INTR_ROK | INTR_RER | INTR_FOVF | INTR_RXOVW)) != 0) {
		if ((isr & (INTR_FOVF | INTR_RXOVW)) != 0) {
			dp->stats.overflow++;
E 3
I 3
	if (isr & (INTR_ROK | INTR_RER | INTR_FOVF | INTR_RXOVW)) {
		if (isr & (INTR_FOVF | INTR_RXOVW)) {
			if (isr & INTR_RXOVW) {
				dp->stats.norcvbuf++;
			} else {
				dp->stats.overflow++;
			}
E 3
			dp->stats.errrcv++;
D 3
			DPRINTF(0, (CE_CONT, "!%s: isr:%b",
				dp->name, isr, INTR_BITS));
E 3
I 3
			DPRINTF(1, (CE_CONT, "!%s: isr:%b",
			    dp->name, isr, INTR_BITS));
E 3
		}
D 3
		gem_receive(dp);
E 3
I 3
		(void) gem_receive(dp);
E 3
	}

D 3
#if defined(GEM_CONFIG_POLLING) || defined(TX_DELAYED_INTR)
	if ((isr & (INTR_TOK | INTR_TER | INTR_TIMEOUT)) != 0)
#else
	if ((isr & (INTR_TOK | INTR_TER)) != 0)
#endif
	{
E 3
I 3
	if (isr & (INTR_TOK | INTR_TER)) {
E 3
		if (gem_tx_done(dp)) {
			restart_tx = INTR_RESTART_TX;
		}
	}

D 3
	if ((isr & INTR_TIMEOUT) != 0) {
E 3
I 3
	if (isr & INTR_TIMEOUT) {
E 3
		mutex_enter(&dp->xmitlock);
D 7
#ifdef TX_DELAYED_INTR
E 7
I 7
#ifdef CONFIG_TX_POLLING
E 7
		if (dp->tx_desc_intr - dp->tx_desc_head > 0) {
			/* need to reschedule tx-intr again */
D 7
			rf_sched_timer(dp);
E 7
I 7
			rf_sched_tx_timer(dp);
E 7
		} else
#endif
D 3
#ifdef GEM_CONFIG_POLLING
		if (lp->last_poll_interval != 0) {
E 3
I 3
D 7
#ifdef CONFIG_POLLING
E 7
I 7
#ifdef CONFIG_RX_POLLING
E 7
		if (dp->poll_interval) {
E 3
D 7
			/* schedule next polling interrupt */
I 3
			OUTL(dp, TimInt, dp->poll_interval / 30);
E 7
I 7
			uint_t	cnt;
			/* schedule the next rx polling interrupt */
			cnt = dp->poll_interval * lp->tim_1us / 1000;
			OUTL(dp, TimInt, max(cnt, lp->tim_1us));
E 7
E 3
			OUTL(dp, TCTR, 0);
D 3
			OUTL(dp, TimInt, dp->poll_interval * 33);
E 3
I 3

			/* disble rx interrupt */
			if (lp->imr & INTR_ROK) {
				lp->imr &= ~INTR_ROK;
				update_imr = B_TRUE;
			}
E 3
		} else
#endif
		{
			/* disable timer interrupt */
			OUTL(dp, TimInt, 0);
I 3
D 7
			lp->imr |= INTR_ROK;
E 7

			/* enable rx interrupt */
I 7
			lp->imr |= INTR_ROK;
E 7
			update_imr = B_TRUE;

E 3
		}
		mutex_exit(&dp->xmitlock);
	}

D 3
	if ((isr & INTR_SERR) != 0) {
E 3
I 3
	if (isr & INTR_SERR) {
E 3
		cmn_err(CE_WARN, "!%s: unexpected interrupt: isr:%b",
D 3
			dp->name, isr, INTR_BITS);
			lp->need_to_reset = TRUE;
E 3
I 3
		    dp->name, isr, INTR_BITS);
		lp->need_to_reset = B_TRUE;
E 3
	}

	if (lp->need_to_reset) {
D 2
		mutex_enter(&dp->xmitlock);
		gem_restart_nic(dp, TRUE);
		mutex_exit(&dp->xmitlock);
E 2
I 2
		gem_restart_nic(dp, GEM_RESTART_KEEP_BUF);
E 2
		restart_tx = INTR_RESTART_TX;
D 3
		lp->need_to_reset = FALSE;
E 3
I 3
		lp->need_to_reset = B_FALSE;
E 3
	}
D 3
	else if ((dp->misc_flag & GEM_NOINTR) == 0) {
		/* enable interrupts again */
E 3
I 3

	if ((dp->misc_flag & GEM_NOINTR) == 0 && update_imr) {
		/* change or enable imr */
E 3
		OUTW(dp, IMR, lp->imr);
	}

	return (DDI_INTR_CLAIMED | restart_tx);
}

D 3
/* 
E 3
I 3
/*
E 3
 * MII Interfaces
 */
/* for rtl8129 */
D 3
#define	MII_DELAY(dp, r)	INB(dp, r)
E 3
I 3
#define	MII_DELAY(dp, r)	{ INB(dp, r); INB(dp, r); }
E 3

static void
rf_mii_sync_external(struct gem_dev *dp)
{
D 3
	int	i;
	int	reg;
	struct rf_dev	*lp = (struct rf_dev *)dp->private;
E 3
I 3
	int		i;
	int		reg;
	struct rf_dev	*lp = dp->private;
E 3

	reg = (lp->chip->type == CHIP_8129) ? MII8129 : MII8130;

	for (i = 0; i < 32; i++) {
		OUTB(dp, reg, MII_MDM | MII_MDO);
		MII_DELAY(dp, reg);
		OUTB(dp, reg, MII_MDM | MII_MDO | MII_MDC);
		MII_DELAY(dp, reg);
	}
}

static uint16_t
rf_mii_read_external(struct gem_dev *dp, uint_t index)
{
	int		i;
	uint_t		data;
	uint16_t	ret;
	uint_t		cmd;
	int		reg;
D 3
	struct rf_dev	*lp = (struct rf_dev *)dp->private;
E 3
I 3
	struct rf_dev	*lp = dp->private;
E 3

	reg = (lp->chip->type == CHIP_8129) ? MII8129 : MII8130;

	cmd = MII_READ_CMD(dp->mii_phy_addr, index);

	/* send read command */
	for (i = 31; i >= 18; i--) {
		data = ((cmd >> i) & 1) << MII_MDO_SHIFT;
		OUTB(dp, reg, MII_MDM | data);
		MII_DELAY(dp, reg);

		OUTB(dp, reg, MII_MDM | data | MII_MDC);
		MII_DELAY(dp, reg);
	}

	/* turn around */
	OUTB(dp, reg, 0);
	MII_DELAY(dp, reg);

	/* notify the phy to send ack */
	OUTB(dp, reg, MII_MDC);
	MII_DELAY(dp, reg);

D 3
        /* get response from the phy */
E 3
I 3
	/* get response from the phy */
E 3
	OUTB(dp, reg, 0);
D 3
        if ((INB(dp, reg) & MII_MDI) != 0) {
                DPRINTF(2, (CE_CONT, "!%s: phy@%d didn't respond",
                        dp->name, dp->mii_phy_addr));
        }
E 3
I 3
	if (INB(dp, reg) & MII_MDI) {
		DPRINTF(2, (CE_CONT, "!%s: phy@%d didn't respond",
		    dp->name, dp->mii_phy_addr));
	}
E 3

#ifdef SANITY
	ret = 0;
#endif
	for (i = 16; i > 0; i--) {
		OUTB(dp, reg, MII_MDC);
		MII_DELAY(dp, reg);

		OUTB(dp, reg, 0);
		ret = (ret << 1) | ((INB(dp, reg) >> MII_MDI_SHIFT) & 1);
D 3
        }
E 3
I 3
	}
E 3

	/* revert the clock cycle and send idle bits */
	for (i = 0; i < 2; i++) {
		OUTB(dp, reg, MII_MDM | MII_MDO);
		MII_DELAY(dp, reg);
		OUTB(dp, reg, MII_MDM | MII_MDO | MII_MDC);
		MII_DELAY(dp, reg);
	}

D 3
        DPRINTF(5, (CE_CONT, "!%s: rf_mii_read_external: ret: 0x%x",
		dp->name, ret));
E 3
I 3
	DPRINTF(5, (CE_CONT, "!%s: %s: ret: 0x%x",
	    dp->name, __func__, ret));
E 3

D 3
        return (ret);
E 3
I 3
	return (ret);
E 3
}

static void
rf_mii_write_external(struct gem_dev *dp, uint_t index, uint16_t val)
{
D 3
        int		i;
        uint32_t	cmd;
E 3
I 3
	int		i;
	uint32_t	cmd;
E 3
	int		data;
	int		reg;
D 3
	struct rf_dev	*lp = (struct rf_dev *)dp->private;
E 3
I 3
	struct rf_dev	*lp = dp->private;
E 3

	reg = (lp->chip->type == CHIP_8129) ? MII8129 : MII8130;

	cmd = MII_WRITE_CMD(dp->mii_phy_addr, index, val);

	/* send write command and data */
	for (i = 31; i >= 0; i--) {
		data = ((cmd >> i) & 1) << MII_MDO_SHIFT;
		OUTB(dp, reg, data | MII_MDM);
		MII_DELAY(dp, reg);
		OUTB(dp, reg, data | MII_MDM | MII_MDC);
		MII_DELAY(dp, reg);
	}

	/*
	 * Send 2 idle clock cycles to ensure that the transmittion
	 * is terminated.
	 */
	for (i = 0; i < 2; i++) {
		OUTB(dp, reg, MII_MDM | MII_MDO);
		MII_DELAY(dp, reg);
		OUTB(dp, reg, MII_MDM | MII_MDO | MII_MDC);
		MII_DELAY(dp, reg);
	}
}
#undef	MII_DELAY

static void
rf_mii_sync_internal(struct gem_dev *dp)
{
	/* do nothing */
}

static uint16_t
rf_mii_read_internal(struct gem_dev *dp, uint_t index)
{
	int	reg;

D 3
	DPRINTF(5, (CE_CONT, "!%s: mii_read: called", dp->name));
E 3
I 3
	DPRINTF(5, (CE_CONT, "!%s: %s: called", dp->name, __func__));
E 3

	switch (index) {
	case MII_CONTROL:
		reg = BMCR;
		break;

	case MII_STATUS:
		reg = BMSR;
		break;

	case MII_AN_ADVERT:
		reg = ANAR;
		break;

	case MII_AN_LPABLE:
		reg = ANLPAR;
		break;

	case MII_AN_EXPANSION:
		reg = ANER;
		break;

	default:
		return (0);
	}

	return (INW(dp, reg));
}

static void
rf_mii_write_internal(struct gem_dev *dp, uint_t index, uint16_t val)
{
	int	reg;

D 3
	DPRINTF(5, (CE_CONT, "!%s: mii_write called", dp->name));
E 3
I 3
	DPRINTF(5, (CE_CONT, "!%s: %s called, reg:0x%x val:0x%04x",
	    dp->name, __func__, index, val));
E 3

	switch (index) {
	case MII_CONTROL:
		reg = INB(dp, CR9346);
		OUTB(dp, CR9346, CR9346_EEM_WE);
		OUTW(dp, BMCR, val);
		OUTB(dp, CR9346, reg);
		return;

	case MII_STATUS:
		reg = BMSR;
		break;

	case MII_AN_ADVERT:
		reg = ANAR;
		break;

	case MII_AN_LPABLE:
D 3
		reg = ANLPAR;		
E 3
I 3
		reg = ANLPAR;
E 3
		break;

	case MII_AN_EXPANSION:
		reg = ANER;
		break;

	default:
		return;
	}

	OUTW(dp, reg, val);
D 3
	return;
E 3
}

/* ======================================================== */
/*
 * OS depend (device driver DKI) routine
 */
/* ======================================================== */
D 3
#define	rf_eeprom_delay(dp)	{INB(dp, CR9346); INB(dp, CR9346);}
E 3
I 3
#define	rf_eeprom_delay(dp)	{INB(dp, CR9346); INB(dp, CR9346); }
E 3
#ifdef EEPROMIO
#include "rf_eeprom_wr.c"
#endif /* EEPROMIO */
static uint16_t
rf_read_eeprom(struct gem_dev *dp, int addr)
{
	int		i;
	int		addr_bits;
	uint_t		cmd;
	uint8_t		chip_select;
	uint8_t		di;
	uint16_t	ret;
D 3
	struct rf_dev	*lp = (struct rf_dev *)dp->private;
E 3
I 3
	struct rf_dev	*lp = dp->private;
E 3

	if (lp->chip->type == CHIP_8139B || lp->chip->type == CHIP_8139C ||
	    lp->chip->type == CHIP_8139CP) {
		/*
		 * eeprom 93C46 or 93C56: 8139B, 8139C, 8139CP
		 */
D 3
		addr_bits = ((INL(dp, RCR) & RCR_9356SEL) != 0) ? 8 : 6;
	}
	else {
E 3
I 3
		addr_bits = ((INL(dp, RCR) & RCR_9356SEL)) ? 8 : 6;
	} else {
E 3
		/*
		 * eeprom 93C46 : 8129, 8130, 8100, 8100B/8139D, 8101
		 */
		addr_bits = 6;
	}

D 3
	DPRINTF(2, (CE_CONT, "!%s: rf_read_eeprom: called: addr_bits:%d",
			dp->name, addr_bits));
E 3
I 3
	DPRINTF(2, (CE_CONT, "!%s: %s: called: addr_bits:%d",
	    dp->name, __func__, addr_bits));
E 3

	/* make command bits */
	cmd = (6 << addr_bits) | addr;

	/* enable eeprom interface register */
	chip_select = CR9346_EEM_PROGRAM;
	OUTB(dp, CR9346, chip_select);

	chip_select |= CR9346_EECS;
	OUTB(dp, CR9346, chip_select);
	rf_eeprom_delay(dp);

	/* output eeprom command */
	for (i = 4 + addr_bits; i >= 0; i--) {
		di = ((cmd >> i) << CR9346_EEDI_SHIFT) & CR9346_EEDI;
		OUTB(dp, CR9346, chip_select | di);
		rf_eeprom_delay(dp);

		OUTB(dp, CR9346, chip_select | di | CR9346_EESK);
		rf_eeprom_delay(dp);
	}

	/* release clock but keep chip_select asserted */
	OUTB(dp, CR9346, chip_select);
	rf_eeprom_delay(dp);

	/* get returned value */
	ret = 0;
	for (i = 16; i > 0; i--) {
		/* get 1 bit */
		OUTB(dp, CR9346, chip_select | CR9346_EESK);
		rf_eeprom_delay(dp);

		ret = (ret << 1)
		    | ((INB(dp, CR9346) >> CR9346_EEDO_SHIFT) & 1);

		OUTB(dp, CR9346, chip_select);
		rf_eeprom_delay(dp);
	}

	/* Terminate the EEPROM access. */
	OUTB(dp, CR9346, CR9346_EEM_PROGRAM);
	OUTB(dp, CR9346, CR9346_EEM_NORMAL);
	rf_eeprom_delay(dp);

D 3
	DPRINTF(2, (CE_CONT, "!rf_read_eeprom: returned 0x%x", ret));
E 3
I 3
	DPRINTF(2, (CE_CONT, "!%s: %s: returned 0x%x",
	    dp->name, __func__, ret));
E 3

D 3
	return ret;
E 3
I 3
	return (ret);
E 3
}

static void
rf_eeprom_dump(struct gem_dev *dp, int size)
{
	int	i;

	cmn_err(CE_CONT, "!%s: %s dump:", dp->name, __func__);
	for (i = 0; i < size; i += 4) {
D 3
		cmn_err(CE_CONT, "!0x%02x: 0x%04x 0x%04x 0x%04x 0x%04x", 
			i, rf_read_eeprom(dp, i), rf_read_eeprom(dp, i + 1),
			rf_read_eeprom(dp, i + 2), rf_read_eeprom(dp, i + 3));
E 3
I 3
		cmn_err(CE_CONT, "!0x%02x: 0x%04x 0x%04x 0x%04x 0x%04x",
		    i, rf_read_eeprom(dp, i), rf_read_eeprom(dp, i + 1),
		    rf_read_eeprom(dp, i + 2), rf_read_eeprom(dp, i + 3));
E 3
	}
}

static int
rf_attach_chip(struct gem_dev *dp)
{
	int		i;
	uint32_t	val;
	uint8_t		*m;
D 3
	char		propname[32];
	struct rf_dev	*lp = (struct rf_dev *)dp->private;
E 3
I 3
	struct rf_dev	*lp = dp->private;
E 3

	/*
	 * reload default mac address from EEPROM
	 */
	m = dp->dev_addr.ether_addr_octet;
D 3
	for (i = 0; i < ETHERADDRL; i+=2) {
		val = rf_read_eeprom(dp, (EPROM_EthernetID + i)/2);
		m[i  ] = (uint8_t) val;
		m[i+1] = (uint8_t) (val >> 8);
E 3
I 3
	for (i = 0; i < ETHERADDRL; i += 2) {
		val = rf_read_eeprom(dp, (EPROM_EthernetID + i) / 2);
		m[i + 0] = (uint8_t)val;
		m[i + 1] = (uint8_t)(val >> 8);
E 3
	}
	bzero(lp->mac, ETHERADDRL);

#ifdef notdef
	if (lp->chip->type == CHIP_8139C) {
		/* enable flow control */
		rtl8139c_eeprom[0xc/2] &= ~0x0002;
		rf_control_eeprom(dp, WEN);
		for (i = 0; i < 0x30; i++) {
			rf_write_eeprom(dp, i, rtl8139c_eeprom[i]);
		}
		rf_control_eeprom(dp, WDS);
	}
	DPRINTF(0, (CE_CONT, "!%s: reg70:%04x, reg74:%04x",
D 3
		dp->name, INW(dp, 0x70), INW(dp, 0x74)));
E 3
I 3
	    dp->name, INW(dp, 0x70), INW(dp, 0x74)));
E 3
#endif

#ifdef notdef
	if (lp->chip->type == CHIP_8139B) {
		rf_control_eeprom(dp, WEN);
		for (i = 0; i < 0x40; i++) {
			rf_write_eeprom(dp, i, rtl8139b_eeprom[i]);
		}
		rf_control_eeprom(dp, WDS);
	}
	DPRINTF(0, (CE_CONT, "!%s: reg70:%04x, reg74:%04x",
D 3
		dp->name, INW(dp, 0x70), INW(dp, 0x74)));
E 3
I 3
	    dp->name, INW(dp, 0x70), INW(dp, 0x74)));
E 3
#endif
	rf_eeprom_dump(dp, 0x40);

	if (lp->chip->type != CHIP_8129) {
		/* no need to scan PHY */
		dp->mii_phy_addr = -1;
	}

#ifndef TX_UNDERRUN_TEST
	dp->txmaxdma = min(dp->txmaxdma, 256);
	dp->txmaxdma = max(dp->txmaxdma, 1024);
#endif
	dp->txmaxdma = min(dp->txmaxdma, 256);

D 3
	sprintf(propname, "%s-txthr", dp->name);
E 3
	if (ddi_prop_exists(DDI_DEV_T_ANY,
D 3
			dp->dip, DDI_PROP_DONTPASS, propname) == 0) {
E 3
I 3
	    dp->dip, DDI_PROP_DONTPASS, "txthr") == 0) {
E 3
		/* fix default value for txthr */
		dp->txthr = 256;
	}

D 7
	/* check timer function is alive */
	OUTL(dp, IMR, 0);
	OUTL(dp, TimInt, 0);
E 7
I 7
	/* check if we have timer function */
#define	TEST_PERIOD	100
	lp->tim_1us = 0;
	OUTW(dp, IMR, 0);
	OUTL(dp, TimInt, TIM_1uS*TEST_PERIOD/2);
E 7
	OUTL(dp, TCTR, 0);
D 7
	drv_usecwait(1000);
	lp->tim_1us = INL(dp, TCTR)/1000;
	DPRINTF(1, (CE_CONT, "!%s: tim_1us:%d", dp->name, lp->tim_1us));
E 7
I 7
	OUTW(dp, ISR, 0xffffU);
	drv_usecwait(TEST_PERIOD);
	if (INW(dp, ISR) & INTR_TIMEOUT) {
		/* we got interrupted, the timer is alive. */
		OUTW(dp, ISR, 0);
		lp->tim_1us = INL(dp, TCTR)/TEST_PERIOD;
		cmn_err(CE_CONT, "!%s: timer resolution:%duS",
		    dp->name, lp->tim_1us);
E 7

D 7
	if (lp->tim_1us < TIM_1us/2) {
		lp->tim_1us = 0;
E 7
I 7
		/* check the result, expected value is 33 */
		if (lp->tim_1us < TIM_1uS/2 || lp->tim_1us > TIM_1uS*3) {
			lp->tim_1us = 0;
		}
E 7
	}
I 7
	OUTL(dp, TimInt, 0);
#undef	TEST_PERIOD
E 7

D 3
#ifdef GEM_CONFIG_POLLING
E 3
I 3
D 7
#ifdef CONFIG_POLLING
E 3
	if (!HAVE_TIMER(lp)) {
		/* inhibit polling mode */
		dp->poll_pkt_delay = 0;
	}
D 3
#endif /* GEM_CONFIG_POLLING */
E 3
I 3
#endif /* CONFIG_POLLING */
E 3

E 7
D 3
	dp->misc_flag |= GEM_POLL_RXONLY;

D 2
#ifdef CONFIG_VLAN
E 2
I 2
#ifdef GEM_CONFIG_VLAN
E 3
I 3
	dp->misc_flag |= GEM_POLL_RXONLY | GEM_NORXBUF;
#ifdef GEM_CONFIG_GLDv3	/* for vlan */
E 3
E 2
	dp->misc_flag |= GEM_VLAN_SOFT;
#endif
I 3

#if 0 /* DEBUG */
	dp->txmaxdma = 1024;
	dp->rxmaxdma = dp->mtu;
	dp->rxthr = dp->mtu;
#endif
E 3
	return (GEM_SUCCESS);
}

static int
rfattach(dev_info_t *dip, ddi_attach_cmd_t cmd)
{
	int			i;
	ddi_acc_handle_t	conf_handle;
	int			ret;
	int			vid;
	int			did;
	int			revid;
	int			unit;
	struct chip_info	*p;
	uint32_t		tcr;
D 3
	u_int			len;
E 3
I 3
	uint_t			len;
E 3
	const char		*drv_name;
	struct gem_dev		*dp;
D 3
	void			*base;
E 3
I 3
	caddr_t			base;
E 3
	ddi_acc_handle_t	regs_handle;
	struct gem_conf		*gcp;
	struct rf_dev		*lp;
	uint32_t		ilr;

D 3
	unit     =  ddi_get_instance(dip);
E 3
I 3
	unit = ddi_get_instance(dip);
E 3
	drv_name = ddi_driver_name(dip);

D 3
	DPRINTF(3, (CE_CONT, "!%s%d: rfattach: called", drv_name, unit));
E 3
I 3
	DPRINTF(3, (CE_CONT, "!%s%d: %s: called", drv_name, unit, __func__));
E 3

	if (pci_config_setup(dip, &conf_handle) != DDI_SUCCESS) {
D 3
		cmn_err(CE_WARN, "!%s%d: ddi_regs_map_setup failed",
			drv_name, unit);
E 3
I 3
		cmn_err(CE_WARN, "!%s%d: pci_config_setup failed",
		    drv_name, unit);
E 3
		return (DDI_FAILURE);
	}

	/* ensure I/O accesss and bus master */
	pci_config_put16(conf_handle, PCI_CONF_COMM,
D 3
		pci_config_get16(conf_handle, PCI_CONF_COMM)
			| PCI_COMM_IO | PCI_COMM_ME);
E 3
I 3
	    pci_config_get16(conf_handle, PCI_CONF_COMM)
	    | PCI_COMM_IO | PCI_COMM_ME);
E 3

	/* ensure D0 mode */
	(void) gem_pci_set_power_state(dip, conf_handle, PCI_PMCSR_D0);

	/* fix latency timer */
	if (pci_config_get8(conf_handle, PCI_CONF_LATENCY_TIMER) < 16) {
		pci_config_put8(conf_handle, PCI_CONF_LATENCY_TIMER, 16);
	}

	vid = pci_config_get16(conf_handle, PCI_CONF_VENID);
	did = pci_config_get16(conf_handle, PCI_CONF_DEVID);
	revid = pci_config_get8(conf_handle, PCI_CONF_REVID);
	ilr = pci_config_get32(conf_handle, PCI_CONF_ILINE);

	DPRINTF(0, (CE_CONT, "!%s%d: ilr 0x%08x", drv_name, unit, ilr));

#ifdef notdef
	/* 8139 doesn't have cacle_line_size register */
	pci_config_put8(conf_handle, PCI_CONF_CACHE_LINESZ, 64/4);
	DPRINTF(0, (CE_CONT, "!%s%d: cache line size: 0x%02x", drv_name, unit,
D 3
		pci_config_get8(conf_handle, PCI_CONF_CACHE_LINESZ)));
E 3
I 3
	    pci_config_get8(conf_handle, PCI_CONF_CACHE_LINESZ)));
E 3
#endif

	pci_config_teardown(&conf_handle);

	switch (cmd) {
	case DDI_RESUME:
		return (gem_resume(dip));

	case DDI_ATTACH:
		/* Map in the device registers.  */
		if (gem_pci_regs_map_setup(dip,
D 3
			PCI_ADDR_IO, PCI_ADDR_MASK,
			&rf_dev_attr,
			(caddr_t *)&base, &regs_handle) != DDI_SUCCESS) {
E 3
I 3
		    PCI_ADDR_IO, PCI_ADDR_MASK,
		    &rf_dev_attr,
		    &base, &regs_handle) != DDI_SUCCESS) {
E 3
			goto err;
		}

		/* Check the chip if it is really 8129/8139.  */
D 3
		tcr = ddi_get32(regs_handle, (uint32_t *)((caddr_t)base + TCR));
E 3
I 3
		tcr = ddi_get32(regs_handle, (uint32_t *)(base + TCR));
E 3

D 3
		/* Try rtl8129 first*/
E 3
I 3
		/* Try rtl8129 first */
E 3
		if (vid == 0x10ec && did == 0x8129) {
			p = &chiptbl_8129[0];
			goto chip_found;
		}

		/* Try rtl8139 */
		for (i = 0; i < CHIPTABLESIZE; i++) {
			if (chiptbl_8139[i].tcr_val == (tcr & TCR_HWREV)) {
				/* found */
				p = &chiptbl_8139[i];
				goto chip_found;
			}
		}

		cmn_err(CE_WARN,
D 3
			"!%s%d: unknown variant of rtl8139 chip: "
			"venid:0x%04x devid:%04x tcr:0x%08x",
			drv_name, unit, vid, did, tcr);
E 3
I 3
		    "!%s%d: unknown variant of rtl8139 chip: "
		    "venid:0x%04x devid:%04x tcr:0x%08x",
		    drv_name, unit, vid, did, tcr);
E 3

		/* assume latest variant of the 8139 */
		/* XXX - RTL8101L for now */
		p = &chiptbl_8139[CHIPTABLESIZE-1];
chip_found:
		cmn_err(CE_CONT, "!%s%d: %s rev:0x%02x tcr:0x%08x",
D 3
			drv_name, unit, p->name, revid, tcr);
E 3
I 3
		    drv_name, unit, p->name, revid, tcr);
E 3

		/*
		 * construct gem configration
D 3
		 */ 
		gcp = (struct gem_conf *) kmem_zalloc(sizeof(*gcp), KM_SLEEP);
E 3
I 3
		 */
		gcp = kmem_zalloc(sizeof (*gcp), KM_SLEEP);
E 3

		/* name */
		sprintf(gcp->gc_name, "%s%d", drv_name, unit);

D 3
		gcp->gc_tx_buf_align = sizeof(uint32_t) - 1;
E 3
I 3
		gcp->gc_tx_buf_align = sizeof (uint32_t) - 1;
E 3
		gcp->gc_tx_max_frags = 1;
		gcp->gc_tx_max_descs_per_pkt = 1;
D 2
		gcp->gc_tx_desc_unit_shift = 0;
E 2
I 2
		gcp->gc_tx_desc_unit_shift = -1;
E 2
D 3
		gcp->gc_tx_buf_size  = NTXBUF;
E 3
I 3
		gcp->gc_tx_buf_size = NTXBUF;
E 3
		gcp->gc_tx_buf_limit = gcp->gc_tx_buf_size;
		gcp->gc_tx_ring_size = NTXDESC;
D 3
		gcp->gc_tx_ring_limit= gcp->gc_tx_ring_size;
		gcp->gc_tx_auto_pad  = FALSE;
E 3
I 3
		gcp->gc_tx_ring_limit = gcp->gc_tx_ring_size;
		gcp->gc_tx_auto_pad = B_FALSE;
E 3
		gcp->gc_tx_copy_thresh = rf_tx_copy_thresh;
D 3
		gcp->gc_tx_desc_write_oo = FALSE;
E 3
I 3
		gcp->gc_tx_desc_write_oo = B_FALSE;
E 3

D 3
		gcp->gc_rx_buf_align = sizeof(uint32_t) - 1;
E 3
I 3
		gcp->gc_rx_buf_align = sizeof (uint32_t) - 1;
E 3
		gcp->gc_rx_max_frags = 1;
D 3
		gcp->gc_rx_desc_unit_shift = OUR_RBLEN_SHIFT;
E 3
I 2
		gcp->gc_rx_desc_unit_shift = -1;
E 2
D 3
		gcp->gc_rx_ring_size = 1;
		gcp->gc_rx_buf_max   = 64;
E 3
I 3
		gcp->gc_rx_ring_size = RX_BUF_SIZE;
		gcp->gc_rx_buf_max = RX_BUF_SIZE;
E 3
		gcp->gc_rx_copy_thresh = rf_rx_copy_thresh;

D 2
		gcp->gc_io_area_size = 0;
E 2
I 2
		gcp->gc_io_area_size = RX_BUFFER_SIZE;
E 2

		/* map attributes (endianess) */
D 2
		STRUCT_COPY(gcp->gc_dev_attr, rf_dev_attr); /* for registers */
		STRUCT_COPY(gcp->gc_buf_attr, rf_buf_attr); /* for tx */
		STRUCT_COPY(gcp->gc_desc_attr, rf_buf_attr);/* for rx buffers */
E 2
I 2
		gcp->gc_dev_attr = rf_dev_attr;		/* for registers */
		gcp->gc_buf_attr = rf_buf_attr;		/* for tx buffers */
		gcp->gc_desc_attr = rf_buf_attr;	/* for rx buffers */
E 2

		/* dma attributes */
D 2
		STRUCT_COPY(gcp->gc_dma_attr_desc, rf_dma_attr_rxbuf);
		STRUCT_COPY(gcp->gc_dma_attr_txbuf, rf_dma_attr_txbuf);
		STRUCT_COPY(gcp->gc_dma_attr_rxbuf, rf_dma_attr_rxbuf);
E 2
I 2
		gcp->gc_dma_attr_desc = rf_dma_attr_rxbuf;
		gcp->gc_dma_attr_txbuf = rf_dma_attr_txbuf;
		gcp->gc_dma_attr_rxbuf = rf_dma_attr_rxbuf;
E 2
		gcp->gc_dma_attr_rxbuf.dma_attr_align = gcp->gc_rx_buf_align+1;

		/* time out parameters */
		gcp->gc_tx_timeout = 3*ONESEC;
		gcp->gc_tx_timeout_interval = ONESEC;

		/* flow control */
		gcp->gc_flow_control = FLOW_CONTROL_SYMMETRIC;

		/* MII timeout parameters */
		gcp->gc_mii_link_watch_interval = ONESEC;
		gcp->gc_mii_an_watch_interval = ONESEC/5;
		gcp->gc_mii_reset_timeout = MII_RESET_TIMEOUT;	/* 1 sec */
D 3
		gcp->gc_mii_an_timeout    = MII_AN_TIMEOUT;	/* 5 sec */
E 3
I 3
		gcp->gc_mii_an_timeout = MII_AN_TIMEOUT;	/* 5 sec */
E 3
		gcp->gc_mii_an_wait = (25*ONESEC)/10;
		gcp->gc_mii_linkdown_timeout = MII_LINKDOWN_TIMEOUT;

D 3
		gcp->gc_mii_an_delay   = ONESEC/10;
		gcp->gc_mii_linkdown_action         = MII_ACTION_RSA;
E 3
I 3
		gcp->gc_mii_an_delay = ONESEC/10;
		gcp->gc_mii_linkdown_action = MII_ACTION_RSA;
E 3
		gcp->gc_mii_linkdown_timeout_action = MII_ACTION_RESET;
D 3
		gcp->gc_mii_dont_reset = FALSE;
		gcp->gc_mii_hw_link_detection = TRUE;	/* experimental */
		gcp->gc_mii_hw_link_detection = FALSE;
E 3
I 3
		gcp->gc_mii_dont_reset = B_FALSE;
		gcp->gc_mii_hw_link_detection = B_TRUE;
E 3

		/* I/O methods */

		/* mac operation */
		gcp->gc_attach_chip = &rf_attach_chip;
D 3
		gcp->gc_reset_chip  = &rf_reset_chip;
		gcp->gc_init_chip   = &rf_init_chip;
		gcp->gc_start_chip  = &rf_start_chip;
		gcp->gc_stop_chip   = &rf_stop_chip;
E 3
I 3
		gcp->gc_reset_chip = &rf_reset_chip;
		gcp->gc_init_chip = &rf_init_chip;
		gcp->gc_start_chip = &rf_start_chip;
		gcp->gc_stop_chip = &rf_stop_chip;
E 3
		gcp->gc_multicast_hash = &rf_mcast_hash;
		gcp->gc_set_rx_filter = &rf_set_rx_filter;
D 3
		gcp->gc_set_media   = &rf_set_media;
		gcp->gc_get_stats   = &rf_get_stats;
		gcp->gc_interrupt   = &rf_interrupt;
E 3
I 3
		gcp->gc_set_media = &rf_set_media;
		gcp->gc_get_stats = &rf_get_stats;
		gcp->gc_interrupt = &rf_interrupt;
E 3

		/* descriptor operation */
		gcp->gc_tx_desc_write = &rf_tx_desc_write;
		gcp->gc_rx_desc_write = &rf_rx_desc_write;
D 3
		gcp->gc_tx_start      = &rf_tx_start;
		gcp->gc_tx_desc_stat  = &rf_tx_desc_stat;
		gcp->gc_rx_desc_stat  = &rf_rx_desc_stat;
		gcp->gc_tx_desc_init  = &rf_tx_desc_init;
		gcp->gc_rx_desc_init  = &rf_rx_desc_init;
E 3
I 3
		gcp->gc_tx_start = &rf_tx_start;
		gcp->gc_tx_desc_stat = &rf_tx_desc_stat;
		gcp->gc_rx_desc_stat = &rf_rx_desc_stat;
		gcp->gc_tx_desc_init = &rf_tx_desc_init;
		gcp->gc_rx_desc_init = &rf_rx_desc_init;
E 3
		gcp->gc_tx_desc_clean = &rf_tx_desc_clean;
		gcp->gc_rx_desc_clean = &rf_rx_desc_clean;

		/* mii operations */
D 3
		gcp->gc_mii_init   = &gem_mii_init_default;
E 3
I 3
		gcp->gc_mii_probe = &gem_mii_probe_default;
		gcp->gc_mii_init = NULL;
E 3
		gcp->gc_mii_config = &gem_mii_config_default;
		if (p->type == CHIP_8129) {
			/* rtl8129 */
D 3
			gcp->gc_mii_sync  = &rf_mii_sync_external;
			gcp->gc_mii_read  = &rf_mii_read_external;
E 3
I 3
			gcp->gc_mii_sync = &rf_mii_sync_external;
			gcp->gc_mii_read = &rf_mii_read_external;
E 3
			gcp->gc_mii_write = &rf_mii_write_external;
D 3
		}
		else {
E 3
I 3
		} else {
E 3
			/* rtl8139 */
D 3
			gcp->gc_mii_sync  = &rf_mii_sync_internal;
			gcp->gc_mii_read  = &rf_mii_read_internal;
E 3
I 3
			gcp->gc_mii_sync = &rf_mii_sync_internal;
			gcp->gc_mii_read = &rf_mii_read_internal;
E 3
			gcp->gc_mii_write = &rf_mii_write_internal;
		}
		gcp->gc_mii_tune_phy = NULL;
		gcp->gc_get_packet = &rf_get_packet;

I 5
		/* offload and jumbo frame */
		gcp->gc_max_lso = 0;
		gcp->gc_max_mtu = ETHERMTU;
		gcp->gc_default_mtu = ETHERMTU;
		gcp->gc_min_mtu = ETHERMIN - sizeof (struct ether_header);

E 5
D 3
		lp = (struct rf_dev *)
				kmem_zalloc(sizeof(struct rf_dev), KM_SLEEP);
E 3
I 3
		lp = kmem_zalloc(sizeof (struct rf_dev), KM_SLEEP);
E 3
		lp->chip = p;

D 3
		dp = gem_do_attach(dip, gcp, base, &regs_handle,
					lp, sizeof(struct rf_dev));
E 3
I 3
		dp = gem_do_attach(dip, 0, gcp, base, &regs_handle,
		    lp, sizeof (struct rf_dev));
E 3

D 3
		kmem_free(gcp, sizeof(*gcp));
E 3
I 3
		kmem_free(gcp, sizeof (*gcp));
E 3

		if (dp != NULL) {
			return (DDI_SUCCESS);
		}
err_free_mem:
D 3
		kmem_free(lp, sizeof(struct rf_dev));
E 3
I 3
		kmem_free(lp, sizeof (struct rf_dev));
E 3
err:
		return (DDI_FAILURE);
	}
	return (DDI_FAILURE);
}

static int
rfdetach(dev_info_t *dip, ddi_detach_cmd_t cmd)
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
I 3
#ifdef GEM_CONFIG_GLDv3
D 4
DDI_DEFINE_STREAM_OPS(rf_ops, nulldev, nulldev, rfattach, rfdetach,
    nodev, NULL, D_MP, NULL);
E 4
I 4
GEM_STREAM_OPS(rf_ops, rfattach, rfdetach);
E 4
#else
E 3
static	struct module_info rfminfo = {
	0,			/* mi_idnum */
	"rf",			/* mi_idname */
	0,			/* mi_minpsz */
D 2
	ETHERMTU,		/* mi_maxpsz */
	NTXBUF*ETHERMAX,	/* mi_hiwat */
E 2
I 2
	INFPSZ,			/* mi_maxpsz */
	64*1024,		/* mi_hiwat */
E 2
	1,			/* mi_lowat */
};

static	struct qinit rfrinit = {
	(int (*)()) NULL,	/* qi_putp */
	gem_rsrv,		/* qi_srvp */
	gem_open,		/* qi_qopen */
	gem_close,		/* qi_qclose */
	(int (*)()) NULL,	/* qi_qadmin */
	&rfminfo,		/* qi_minfo */
	NULL			/* qi_mstat */
};

static	struct qinit rfwinit = {
	gem_wput,		/* qi_putp */
	gem_wsrv,		/* qi_srvp */
	(int (*)()) NULL,	/* qi_qopen */
	(int (*)()) NULL,	/* qi_qclose */
	(int (*)()) NULL,	/* qi_qadmin */
	&rfminfo,		/* qi_minfo */
	NULL			/* qi_mstat */
};

static struct streamtab	rf_info = {
	&rfrinit,	/* st_rdinit */
	&rfwinit,	/* st_wrinit */
	NULL,		/* st_muxrinit */
	NULL		/* st_muxwrinit */
};

static	struct cb_ops cb_rf_ops = {
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
	&rf_info,	/* cb_stream */
	D_MP,		/* cb_flag */
};

static	struct dev_ops rf_ops = {
	DEVO_REV,	/* devo_rev */
	0,		/* devo_refcnt */
	gem_getinfo,	/* devo_getinfo */
	nulldev,	/* devo_identify */
	nulldev,	/* devo_probe */
	rfattach,	/* devo_attach */
	rfdetach,	/* devo_detach */
	nodev,		/* devo_reset */
	&cb_rf_ops,	/* devo_cb_ops */
	NULL,		/* devo_bus_ops */
	gem_power,	/* devo_power */
};
I 3
#endif /* GEM_CONFIG_GLDv3 */
E 3

static struct modldrv modldrv = {
	&mod_driverops,	/* Type of module.  This one is a driver */
	ident,
	&rf_ops,	/* driver ops */
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

	DPRINTF(0, (CE_CONT, "!rf: _init: called"));

	gem_mod_init(&rf_ops, "rf");
	status = mod_install(&modlinkage);
	if (status != DDI_SUCCESS) {
		gem_mod_fini(&rf_ops);
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

	DPRINTF(0, (CE_CONT, "!rf: _fini: called"));
	status = mod_remove(&modlinkage);
	if (status == DDI_SUCCESS) {
		gem_mod_fini(&rf_ops);
	}
	return (status);
}

int
_info(struct modinfo *modinfop)
{
	return (mod_info(&modlinkage, modinfop));
}
E 1
