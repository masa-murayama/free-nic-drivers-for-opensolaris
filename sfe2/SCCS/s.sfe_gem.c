h02862
s 00698/00852/01753
d D 1.36 11/10/01 23:14:24 mrym 36 35
c 2.6.1
e
s 00005/00005/02600
d D 1.35 07/10/18 00:23:48 mrym 35 34
c type warning fixed
e
s 00390/00206/02215
d D 1.34 07/09/18 01:11:38 mrym 34 33
c 2.6.0 w/ tx fifo setting fixed
e
s 00011/00007/02410
d D 1.33 07/04/17 02:33:13 mrym 33 32
c 2.4.1 set_rx_filter fixed
e
s 00002/00006/02415
d D 1.32 06/12/30 10:48:17 mrym 32 31
c rx_desc_stat fixed for VLAN
e
s 00136/00082/02285
d D 1.31 06/12/30 10:44:48 mrym 31 30
c 2.4.0
e
s 00002/00001/02365
d D 1.30 06/05/28 16:56:39 mrym 30 29
c 2.2.0 again
e
s 00264/00294/02102
d D 1.29 06/05/28 16:52:08 mrym 29 28
c 2.2.0
e
s 00114/00176/02282
d D 1.28 05/08/31 00:05:17 mrym 28 27
c 1.0.9
e
s 00000/00004/02458
d D 1.27 05/05/01 10:46:05 mrym 27 26
c 1.0.8 sfe_reset_chip_sis900 restored
e
s 00152/00227/02310
d D 1.26 05/05/01 05:38:00 mrym 26 25
c 1.0.8
e
s 00002/00002/02535
d D 1.25 05/01/12 01:18:29 mrym 25 24
c flowcontrol fixed
e
s 00117/00066/02420
d D 1.24 05/01/05 11:48:00 mrym 24 23
c 1.0.7
e
s 00017/00020/02469
d D 1.23 04/11/28 22:42:08 mrym 23 22
c IOCACHE removed
e
s 00024/00003/02465
d D 1.22 04/11/28 21:07:25 mrym 22 21
c ddi_getlongprop removed
e
s 00001/00000/02467
d D 1.21 04/11/20 09:47:14 mrym 21 20
c missing type declaration fixed
e
s 00030/00020/02437
d D 1.20 04/10/29 23:01:10 mrym 20 19
c 1.0.5
e
s 00029/00007/02428
d D 1.19 04/04/11 13:06:41 mrym 19 18
c 
e
s 00022/00025/02413
d D 1.18 04/02/01 18:30:12 mrym 18 17
c 1.0.4
e
s 00003/00001/02435
d D 1.17 04/01/24 09:16:15 mrym 17 16
c 1.0.3 tx_timeout changed for fixed gem_tx_timeout
e
s 00038/00017/02398
d D 1.16 04/01/18 18:54:14 mrym 16 15
c 1.0.2 again, error recovery on HIB error fixed
e
s 00003/00001/02412
d D 1.15 04/01/15 21:42:52 mrym 15 14
c 1.0.2 release
e
s 00004/00004/02409
d D 1.14 04/01/14 22:58:20 mrym 14 13
c tx ring size increased
e
s 00044/00031/02369
d D 1.13 03/12/07 15:44:26 mrym 13 12
c 1.0.1 sis900 mii routines were fixed
e
s 00035/00037/02365
d D 1.12 03/10/19 09:09:42 mrym 12 11
c release 1.0.0
e
s 00059/00035/02343
d D 1.11 03/06/03 00:30:41 mrym 11 10
c final for sparc and 83815
e
s 00031/00084/02347
d D 1.10 03/05/27 22:14:39 mrym 10 9
c release 0.9.12, fixed for sparc
e
s 00021/00050/02410
d D 1.9 03/04/23 05:56:47 mrym 9 8
c release 0.9.10
e
s 00004/00004/02456
d D 1.8 03/04/20 21:54:19 mrym 8 7
c release 0.9.9 (perfect multicast match fixed for 83815)
e
s 00335/00120/02125
d D 1.7 03/04/20 18:36:17 mrym 7 6
c 0.9.8
e
s 00076/00046/02169
d D 1.6 03/02/17 22:13:00 mrym 6 5
c 0.9.5
e
s 00001/00001/02214
d D 1.5 03/02/11 20:35:35 mrym 5 4
c debug messages level fixed
e
s 00155/00004/02060
d D 1.4 03/02/11 20:24:06 mrym 4 3
c 0.9.4
e
s 00050/00013/02014
d D 1.3 03/02/10 21:09:41 mrym 3 2
c 0.9.3
e
s 00001/00001/02026
d D 1.2 02/11/30 17:58:01 mrym 2 1
c 0.9.2
e
s 02027/00000/00000
d D 1.1 02/11/30 12:15:37 mrym 1 0
c date and time created 02/11/30 12:15:37 by mrym
e
u
U
f e 0
t
T
I 1
/*
D 13
 *  sfe_gem.c : DP83815/SiS900 Fast Ethernet MAC driver
E 13
I 13
D 19
 *  sfe_gem.c : DP83815/DP83816/SiS900 Fast Ethernet MAC driver
E 19
I 19
D 36
 *  sfe_gem.c : DP83815/DP83816/SiS900 Fast Ethernet MAC driver for Solaris
E 36
I 36
 *  sfe.c : DP83815/DP83816/SiS900 Fast Ethernet MAC driver for Solaris
E 36
E 19
E 13
 *
D 13
 *  Copyright (C) 2002  Masayuki Murayama (KHF04453@nifty.ne.jp)
E 13
I 13
D 18
 *  Copyright (C) 2002,2003  Masayuki Murayama (KHF04453@nifty.ne.jp)
E 18
I 18
D 19
 *  Copyright (C) 2002-2004  Masayuki Murayama (KHF04453@nifty.ne.jp)
E 18
E 13
 *
 *  CAUTION: NO WARRANTY
 *  This software may be used and distributed according to the terms
 *  of the Lesser GNU Public License, incorporated herein by reference.
E 19
I 19
D 26
 * Copyright (c) 2002-2004 Masayuki Murayama.  All rights reserved.
E 26
I 26
D 31
 * Copyright (c) 2002-2005 Masayuki Murayama.  All rights reserved.
E 31
I 31
D 33
 * Copyright (c) 2002-2006 Masayuki Murayama.  All rights reserved.
E 33
I 33
D 36
 * Copyright (c) 2002-2007 Masayuki Murayama.  All rights reserved.
E 33
E 31
E 26
 * 
E 36
I 36
 * Copyright (c) 2002-2011 Masayuki Murayama.  All rights reserved.
 *
E 36
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
D 36
 * 
E 36
I 36
 *
E 36
 * 1. Redistributions of source code must retain the above copyright notice,
D 36
 *    this list of conditions and the following disclaimer. 
 * 
E 36
I 36
 *    this list of conditions and the following disclaimer.
 *
E 36
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
D 36
 *    and/or other materials provided with the distribution. 
 * 
E 36
I 36
 *    and/or other materials provided with the distribution.
 *
E 36
 * 3. Neither the name of the author nor the names of its contributors may be
 *    used to endorse or promote products derived from this software without
D 36
 *    specific prior written permission. 
 * 
E 36
I 36
 *    specific prior written permission.
 *
E 36
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
E 19
 */
D 19

E 19
D 36
#pragma	ident	"%W% %E%"
E 36

D 36
/*
 Change log
I 4
 02/11/2003	PHY register patch for 83815CVNG.
		NOINTR_WORKAROUND implemented
D 13
 02/11/2003	0.9.4 release
E 13
I 13
 02/11/2003	0.9.4 released
E 13
I 6
 02/16/2003	 trace for hung
D 13
 02/17/2003	0.9.5 release
E 13
I 13
 02/17/2003	0.9.5 released
E 13
I 7
 03/13/2003	fixed for sparc
D 13
 04/05/2003	0.9.6 release
E 13
I 13
 04/05/2003	0.9.6 released
E 13
 04/10/2003	sfe_reset_chip changed for sis96x
 04/20/2003	sfe_set_media: maxdma size fixed for builtin sis900
D 13
 04/20/2003	0.9.8 release
E 13
I 13
 04/20/2003	0.9.8 released
E 13
I 9
 04/20/2003	sfe_set_rx_filter_dp83815: perfect match bug fixed
D 13
 04/20/2003	0.9.9 release
E 13
I 13
 04/20/2003	0.9.9 released
E 13
 04/21/2003	sfe_tx_desc_write: type of intreq fixed for sparc
D 13
 04/22/2003	0.9.10 release
E 13
I 13
 04/22/2003	0.9.10 released
E 13
I 10
 05/26/2003	fixed for sparc
D 13
 05/27/2003	0.9.12 release
E 13
I 13
 05/27/2003	0.9.12 released
E 13
I 11
 05/31/2003	burstsizes in dma_attr fixed for sparc.
I 12
 09/08/2003	gld entries removed
 10/19/2003	get_packet removed
D 13
 10/19/2003	1.0.0 release
E 13
I 13
 10/19/2003	1.0.0 released
 11/18/2003	sfe_set_rx_filter_dp83815: perfect match bug fixed
 12/06/2003	sis900 mii routines were fixed.
 12/06/2003	1.0.1 released
I 15
 01/15/2004	TX_RING_SIZE, rx_copy_thresh changed.
D 16
 01/15/2004	1.0.2 released
E 16
I 16
 01/18/2004	Error recovery on HIB interrupt fixed
 01/18/2004	1.0.2 released
I 17
 01/24/2004	tx_timeout changed for fixed gem_tx_timeout (2sec->5sec) 
 01/24/2004	1.0.3 released
I 30
 05/28/2006	2.2.0 released
I 33
 04/17/2007	2.4.1 released
I 34
 08/31/2007	2.6.0 released
 09/17/2007	tx fifo setting fixed
E 34
E 33
E 30
E 17
E 16
E 15
E 13
E 12
E 11
E 10
E 9
E 7
E 6
E 4
 */
E 36
I 36
#pragma	ident	"%Z%%M% %I%     %E%"
E 36

/*
D 36
 TODO:
D 34
	need to customize mii_link_water and mii_config
	need to eliminate rx suspend/pause frame.
I 4
	100m loop back test
E 34
D 7
	NOINTR workaround
E 7
E 4
 */

/*
E 36
 * System Header files.
 */
#include <sys/types.h>
#include <sys/conf.h>
#include <sys/debug.h>
D 36
#include <sys/stropts.h>
#include <sys/stream.h>
#include <sys/strlog.h>
E 36
#include <sys/kmem.h>
D 36
#include <sys/stat.h>
#include <sys/kstat.h>
#include <sys/vtrace.h>
#include <sys/dlpi.h>
#include <sys/strsun.h>
#include <sys/ethernet.h>
E 36
#include <sys/modctl.h>
#include <sys/errno.h>
I 31
D 36
#include <sys/dditypes.h>
E 36
E 31
#include <sys/ddi.h>
#include <sys/sunddi.h>
D 12
#include <sys/gld.h>
E 12
D 31
#include <sys/ddi_impldefs.h>
E 31
D 34

E 34
I 10
#include <sys/byteorder.h>
D 36

E 36
I 36
#include <sys/ethernet.h>
E 36
E 10
#include <sys/pci.h>
I 36

E 36
D 34
#include "mii.h"
E 34
I 34
#include "gem_mii.h"
E 34
#include "gem.h"
#include "sfereg.h"

I 7
D 26
#ifdef sun4u
# define	IOCACHE
# define	IOMMU
#endif

E 26
E 7
D 9
char	ident[] = "sis900/dp83815 driver v" VERSION;
E 9
I 9
D 36
char	ident[] = "sis900/dp83815 driver " VERSION;
E 36
I 36
char	ident[] = "sis900/dp83815 driver v" VERSION;
E 36
E 9
D 29
char	_depends_on[] = {"misc/gld"};
E 29

/* Debugging support */
#ifdef DEBUG_LEVEL
static int sfe_debug = DEBUG_LEVEL;
I 6
D 36
# if DEBUG_LEVEL > 4
#    define	CONS	"^"
#  else
#    define	CONS	"!"
#  endif
E 6
#define	DPRINTF(n, args)	if (sfe_debug>(n)) cmn_err args
E 36
I 36
#if DEBUG_LEVEL > 4
#define	CONS	"^"
E 36
#else
I 6
#define	CONS	"!"
I 36
#endif
#define	DPRINTF(n, args)	if (sfe_debug > (n)) cmn_err args
#else
#define	CONS	"!"
E 36
E 6
#define	DPRINTF(n, args)
#endif

/*
 * Useful macros and typedefs
 */
D 29
#define	FALSE	(0)
#define	TRUE	(!FALSE)
E 29
I 24
D 36
#define	ONESEC			(drv_usectohz(1*1000000))
E 24

I 24
D 31
#define	STRUCT_COPY(a, b)	bcopy(&(b), &(a), sizeof(a))

E 31
D 26
#if defined(sun4u)
#define	LE64(x)	((((uint64_t)gem_le32(x))<<32) | (uint64_t)gem_le32((x)>>32))
#define	LE32(x)	gem_le32(x)
#define	LE16(x)	gem_le16(x)
#else
#define	LE64(x)	(x)
#define	LE32(x)	(x)
#define	LE16(x)	(x)
#endif

E 26
#ifdef MAP_MEM
D 26
#undef	INB
#undef	INW
#undef	INL
#undef	OUTB
#undef	OUTW
#undef	OUTL

#define	INB(dp, reg)	\
	(*(volatile uint8_t *)(((long)(dp)->base_addr) + (reg)))
#define	INW(dp, reg)	\
	(*(volatile uint16_t *)(((long)(dp)->base_addr) + (reg)))
#define	INL(dp, reg)	\
	(*(volatile uint32_t *)(((long)(dp)->base_addr) + (reg)))

#define	OUTB(dp, reg, val)	\
	((*(volatile uint8_t *)(((long)(dp)->base_addr) + (reg))) = (val))
#define	OUTW(dp, reg, val)	\
	((*(volatile uint16_t *)(((long)(dp)->base_addr) + (reg))) = (val))
#define	OUTL(dp, reg, val)	\
	((*(volatile uint32_t *)(((long)(dp)->base_addr) + (reg))) = (val))

E 26
#define	FLSHB(dp,reg)		INB(dp, reg)
#define	FLSHW(dp,reg)		INW(dp, reg)
#define	FLSHL(dp,reg)		INL(dp, reg)
D 26

#else /* MAP_MEM */

E 26
I 26
#else
E 26
#define	FLSHB(dp,reg)
#define	FLSHW(dp,reg)
#define	FLSHL(dp,reg)
D 26

E 26
#endif /* MAP_MEM */

E 36
I 36
#define	ONESEC		(drv_usectohz(1*1000000))
E 36
I 34
#define	ROUNDUP2(x, a)	(((x) + (a) - 1) & ~((a) - 1))

I 36
uint32_t sfe_rxfilter_delay_sis900 = 10;
#define	OUTL_RXFILTER(dp, reg, val)	{	\
	OUTL(dp, reg, val);	\
	if (((struct sfe_dev *)dp->private)->chip->chip_type	\
	    == CHIPTYPE_SIS900) {	\
		drv_usecwait(sfe_rxfilter_delay_sis900);	\
	}	\
}
E 36
E 34
E 24
/*
 * Our configuration
 */
I 29
#ifdef CONFIG_OO
#define	MAXTXFRAGS	1
#else
D 36
#define	MAXTXFRAGS	GEM_MAXTXFRAGS
E 36
I 36
#define	MAXTXFRAGS	min(8, GEM_MAXTXFRAGS)
E 36
#endif
#define	MAXRXFRAGS	1

E 29
I 20
D 24
#ifndef	TX_RING_SIZE
E 20
D 14
#define	TX_RING_SIZE	128
E 14
I 14
#define	TX_RING_SIZE	256
E 14
D 20
#if 0   /* tx block test */
#define	TX_BUF_SIZE	(TX_RING_SIZE/8)
#else
E 20
I 20
#endif
E 24
#ifndef	TX_BUF_SIZE
E 20
D 14
#define	TX_BUF_SIZE	(TX_RING_SIZE/2)
E 14
I 14
D 24
#define	TX_BUF_SIZE	(TX_RING_SIZE/4)
E 24
I 24
#define	TX_BUF_SIZE	64
E 24
E 14
#endif
I 20
D 24

#ifndef	RX_RING_SIZE
E 20
#define	RX_RING_SIZE	64
E 24
I 24
#ifndef	TX_RING_SIZE
D 29
#define	TX_RING_SIZE	(TX_BUF_SIZE * 4)
E 29
I 29
D 36
# if MAXTXFRAGS == 1
#  define	TX_RING_SIZE	TX_BUF_SIZE
# else
#  define	TX_RING_SIZE	(TX_BUF_SIZE * 4)
# endif
E 36
I 36
#if MAXTXFRAGS == 1
#define	TX_RING_SIZE	TX_BUF_SIZE
#else
#define	TX_RING_SIZE	(TX_BUF_SIZE * 4)
E 36
E 29
E 24
I 20
#endif
I 36
#endif
E 36
I 24

E 24
#ifndef	RX_BUF_SIZE
D 24
#define	RX_BUF_SIZE	(RX_RING_SIZE*2)
E 24
I 24
D 34
#define	RX_BUF_SIZE	64
E 34
I 34
#define	RX_BUF_SIZE	256
E 34
E 24
#endif
I 24
#ifndef	RX_RING_SIZE
#define	RX_RING_SIZE	RX_BUF_SIZE
#endif
E 24
E 20

D 29
#define	MAXTXFRAGS	GEM_MAXTXFRAGS
#define	MAXRXFRAGS	1

E 29
#define	OUR_INTR_BITS	\
D 16
	(ISR_RXSOVR | ISR_HIBERR | ISR_TXURN | ISR_TXDESC | ISR_TXERR |	\
E 16
I 16
	(ISR_DPERR | ISR_SSERR | ISR_RMABT | ISR_RTABT | ISR_RXSOVR |	\
D 36
	 ISR_TXURN | ISR_TXDESC | ISR_TXERR |	\
E 16
D 11
	 ISR_RXORN | ISR_RXOK | ISR_RXERR)
E 11
I 11
	 ISR_RXORN | ISR_RXIDLE | ISR_RXOK | ISR_RXERR)
E 36
I 36
	ISR_TXURN | ISR_TXDESC | ISR_TXERR |	\
	ISR_RXORN | ISR_RXIDLE | ISR_RXOK | ISR_RXERR)
E 36
E 11
D 7
#if 0
#define	OUR_INTR_BITS_SIS900	\
	 (OUR_INTR_BITS | ISR_PAUSE_END | ISR_PAUSE_ST)
#else
#define	OUR_INTR_BITS_SIS900	(OUR_INTR_BITS)
#endif
E 7

I 28
D 36
#define USE_MULTICAST_HASHTBL
E 36
I 36
#define	USE_MULTICAST_HASHTBL
E 36

E 28
D 7

E 7
D 12
#define TX_TIMEOUT		(drv_usectohz(5*1000000))
#define TX_TIMEOUT_INTERVAL	(drv_usectohz(1*1000000))
#define LINK_WATCH_INTERVAL	(drv_usectohz(1*1000000))	/* 1 sec */
E 12
D 24
#define	ONESEC			(drv_usectohz(1*1000000))

E 24
static int	sfe_tx_copy_thresh = 256;
D 15
static int	sfe_rx_copy_thresh = 256;
E 15
I 15
D 18
static int	sfe_rx_copy_thresh = INT_MAX;
E 18
I 18
static int	sfe_rx_copy_thresh = 256;
E 18
E 15

D 24
/* special PHY register for SIS900 */
E 24
I 24
/* special PHY registers for SIS900 */
E 24
#define	MII_CONFIG1	0x0010
#define	MII_CONFIG2	0x0011
#define	MII_MASK	0x0013
#define	MII_RESV	0x0014

D 7
#define	PHY_MASK	0xfffffff0
#define	PHY_INTERNAL	0x001d8000
#define	PHY_ICS1893	0x0015f440
E 7
I 7
#define	PHY_MASK		0xfffffff0
#define	PHY_SIS900_INTERNAL	0x001d8000
#define	PHY_ICS1893		0x0015f440
E 7

D 36
/* IEEE802.3x mac control frame for flow controi */
struct pause_frame {
	struct ether_addr	dest;
	struct ether_addr	src;
	uint16_t	type_len;
	uint16_t	pause_flag;
	uint16_t	pause_time;
};
E 36

D 36
static struct ether_addr	sfe_pause_mac_addr = {
	0x01, 0x80, 0xc2, 0x00, 0x00, 0x01,
};

E 36
I 29
D 34
#define	SFE_DESC_SIZE	16
E 34
I 34
#define	SFE_DESC_SIZE	16	/* including pads rounding up to power of 2 */
E 34

D 31
#define	LE32(x)	x
E 31
I 31
D 34
#if defined(sun4u)
# define LE16(x)	ddi_swap16(x)
# define LE32(x)	ddi_swap32(x)
# define LE64(x)	ddi_swap64(x)
#else
# define LE16(x)	(x)
# define LE32(x)	(x)
# define LE64(x)	(x)
#endif
E 31

E 34
E 29
/*
 * Supported chips
 */
struct chip_info {
	uint16_t	venid;
	uint16_t	devid;
	char		*chip_name;
	int		chip_type;
#define	CHIPTYPE_DP83815	0
#define	CHIPTYPE_SIS900		1
};

/*
D 36
 * Chip dependant MAC state
E 36
I 36
 * Chip dependent MAC state
E 36
 */
struct sfe_dev {
	/* misc HW information */
	struct chip_info	*chip;
	uint32_t		our_intr_bits;
I 36
	uint32_t		isr_pended;
E 36
	uint32_t		cr;
D 36
	int			tx_drain_threshold;
	int			tx_fill_threshold;
	int			rx_drain_threshold;
	int			rx_fill_threshold;
E 36
I 36
	uint_t			tx_drain_threshold;
	uint_t			tx_fill_threshold;
	uint_t			rx_drain_threshold;
	uint_t			rx_fill_threshold;
E 36
	uint8_t			revid;	/* revision from PCI configuration */
	boolean_t		(*get_mac_addr)(struct gem_dev *);
I 34
	uint8_t			mac_addr[ETHERADDRL];
E 34
D 26
	uint32_t		mii_phyid;
E 26
D 36
#ifdef TUNE_PHY_630
E 36
	uint8_t			bridge_revid;
D 36
#endif
E 36
I 4
D 10
#ifdef NOINTR_WORKAROUND
	uint32_t		ier;
	timeout_id_t		intr_watcher_id;
#endif
E 10
I 7
D 18
#ifdef DEBUG_LEVEL
	clock_t			tx_setup_time[TX_RING_SIZE];
#endif
E 18
E 7
E 4
};

/*
 * Hardware information
 */
struct chip_info sfe_chiptbl[] = {
D 36
#ifdef CONFIG_SIS900
 {
	0x1039,	0x0900,	"SiS900", CHIPTYPE_SIS900,
 },
#endif
#ifdef CONFIG_DP83815
 {
D 16
	0x100b,	0x0020,	"DP83815", CHIPTYPE_DP83815,
E 16
I 16
	0x100b,	0x0020,	"DP83815/83816", CHIPTYPE_DP83815,
E 16
 },
#endif
#ifdef CONFIG_SIS7016
 {
	0x1039,	0x7016,	"SiS7016", CHIPTYPE_SIS900,
 },
#endif
E 36
I 36
	{ 0x1039, 0x0900, "SiS900", CHIPTYPE_SIS900, },
	{ 0x100b, 0x0020, "DP83815/83816", CHIPTYPE_DP83815, },
	{ 0x1039, 0x7016, "SiS7016", CHIPTYPE_SIS900, },
E 36
};
D 36
#define	CHIPTABLESIZE	(sizeof(sfe_chiptbl)/sizeof(struct chip_info))
E 36
I 36
#define	CHIPTABLESIZE (sizeof (sfe_chiptbl)/sizeof (struct chip_info))
E 36

/* ======================================================== */
D 36
 
E 36
I 36

E 36
/* mii operations */
static void  sfe_mii_sync_dp83815(struct gem_dev *);
static void  sfe_mii_sync_sis900(struct gem_dev *);
D 28
static uint16_t  sfe_mii_read_dp83815(struct gem_dev *, int);
static uint16_t  sfe_mii_read_sis900(struct gem_dev *, int);
static void sfe_mii_write_dp83815(struct gem_dev *, int, uint16_t);
static void sfe_mii_write_sis900(struct gem_dev *, int, uint16_t);
E 28
I 28
static uint16_t  sfe_mii_read_dp83815(struct gem_dev *, uint_t);
static uint16_t  sfe_mii_read_sis900(struct gem_dev *, uint_t);
static void sfe_mii_write_dp83815(struct gem_dev *, uint_t, uint16_t);
static void sfe_mii_write_sis900(struct gem_dev *, uint_t, uint16_t);
E 28
I 10
D 36
#ifdef i86pc
E 36
E 10
static void sfe_set_eq_sis630(struct gem_dev *dp);
D 10

E 10
I 10
D 36
#endif
E 36
E 10
/* nic operations */
D 7
static int sfe_reset_chip(struct gem_dev *);
E 7
I 7
static int sfe_reset_chip_sis900(struct gem_dev *);
static int sfe_reset_chip_dp83815(struct gem_dev *);
E 7
D 31
static void sfe_init_chip(struct gem_dev *);
static void sfe_start_chip(struct gem_dev *);
E 31
I 31
static int sfe_init_chip(struct gem_dev *);
static int sfe_start_chip(struct gem_dev *);
E 31
D 29
static void sfe_stop_chip(struct gem_dev *);
E 29
I 29
static int sfe_stop_chip(struct gem_dev *);
E 29
D 31
static void sfe_set_media(struct gem_dev *);
static void sfe_set_rx_filter_dp83815(struct gem_dev *);
static void sfe_set_rx_filter_sis900(struct gem_dev *);
static void sfe_get_stats(struct gem_dev *);
E 31
I 31
static int sfe_set_media(struct gem_dev *);
static int sfe_set_rx_filter_dp83815(struct gem_dev *);
static int sfe_set_rx_filter_sis900(struct gem_dev *);
static int sfe_get_stats(struct gem_dev *);
E 31
static int sfe_attach_chip(struct gem_dev *);

/* descriptor operations */
D 29
static int sfe_tx_desc_write(struct gem_dev *dp, uint_t slot,
E 29
I 29
static int sfe_tx_desc_write(struct gem_dev *dp, int slot,
E 29
D 9
		    ddi_dma_cookie_t *dmacookie, int frags, boolean_t intreq);
E 9
I 9
D 34
		    ddi_dma_cookie_t *dmacookie, int frags, uint32_t intreq);
E 34
I 34
		    ddi_dma_cookie_t *dmacookie, int frags, uint64_t flags);
E 34
E 9
D 29
static int sfe_rx_desc_write(struct gem_dev *dp, uint_t slot,
E 29
I 29
static void sfe_tx_start(struct gem_dev *dp, int startslot, int nslot);
static void sfe_rx_desc_write(struct gem_dev *dp, int slot,
E 29
		    ddi_dma_cookie_t *dmacookie, int frags);
static uint_t sfe_tx_desc_stat(struct gem_dev *dp, int slot, int ndesc);
D 28
static uint_t sfe_rx_desc_stat(struct gem_dev *dp, int slot, int ndesc);
E 28
I 28
static uint64_t sfe_rx_desc_stat(struct gem_dev *dp, int slot, int ndesc);
E 28

static void sfe_tx_desc_init(struct gem_dev *dp, int slot);
static void sfe_rx_desc_init(struct gem_dev *dp, int slot);
static void sfe_tx_desc_clean(struct gem_dev *dp, int slot);
static void sfe_rx_desc_clean(struct gem_dev *dp, int slot);

/* interrupt handler */
D 36
static u_int sfe_interrupt(struct gem_dev *dp);
E 36
I 36
static uint_t sfe_interrupt(struct gem_dev *dp);
E 36

/* ======================================================== */

/* mapping attributes */
/* Data access requirements. */
D 7
static struct ddi_device_acc_attr gem_dev_attr = {
E 7
I 7
static struct ddi_device_acc_attr sfe_dev_attr = {
E 7
	DDI_DEVICE_ATTR_V0,
	DDI_STRUCTURE_LE_ACC,
	DDI_STRICTORDER_ACC
};

D 34
/* On sparc, the buffers should be native endianness */
E 34
I 34
/* On sparc, Buffers should be native endian for speed */
E 34
static struct ddi_device_acc_attr sfe_buf_attr = {
	DDI_DEVICE_ATTR_V0,
	DDI_NEVERSWAP_ACC,	/* native endianness */
	DDI_STRICTORDER_ACC
};

I 34
D 36
/*
 * XXX - Actually dma_attr_count_max is 0xfff for sis900/dp83815.
 * But ddi_dma_addr_setup() causes DDI_DMA_TOOBIG error
 * in previous solaris release, if dma_attr_count_max is lower than
 * pagesize. We use 0x3fff instead of 0xfff.
 */
E 36
E 34
D 26
static ddi_dma_attr_t sfe_dma_attr_txbuf = {
E 26
I 26
static ddi_dma_attr_t sfe_dma_attr_buf = {
E 26
	DMA_ATTR_V0,		/* dma_attr_version */
	0,			/* dma_attr_addr_lo */
	0xffffffffull,		/* dma_attr_addr_hi */
D 34
	0xffffffffull,		/* dma_attr_count_max */
E 34
I 34
D 36
	0x00003fffull,		/* dma_attr_count_max */
E 36
I 36
	0x00000fffull,		/* dma_attr_count_max */
E 36
E 34
D 26
	1,			/* dma_attr_align */
E 26
I 26
	0, /* patched later */	/* dma_attr_align */
E 26
D 11
	0xffffffff,		/* dma_attr_burstsizes */
E 11
I 11
D 34
	0,			/* dma_attr_burstsizes */
E 34
I 34
	0x000003fc,		/* dma_attr_burstsizes */
E 34
E 11
	1,			/* dma_attr_minxfer */
D 34
	0xffffffffull,		/* dma_attr_maxxfer */
E 34
I 34
D 36
	0x00003fffull,		/* dma_attr_maxxfer */
E 36
I 36
	0x00000fffull,		/* dma_attr_maxxfer */
E 36
E 34
	0xffffffffull,		/* dma_attr_seg */
D 26
	MAXTXFRAGS,		/* dma_attr_sgllen */
E 26
I 26
	0, /* patched later */	/* dma_attr_sgllen */
E 26
	1,			/* dma_attr_granular */
	0			/* dma_attr_flags */
};

D 26
static ddi_dma_attr_t sfe_dma_attr_rxbuf = {
	DMA_ATTR_V0,		/* dma_attr_version */
	0,			/* dma_attr_addr_lo */
	0xffffffffull,		/* dma_attr_addr_hi */
	0xffffffffull,		/* dma_attr_count_max */
	1,			/* dma_attr_align */
D 11
	0xffffffff,		/* dma_attr_burstsizes */
E 11
I 11
D 24
	0,			/* dma_attr_burstsizes */
E 24
I 24
	0xffffffff,		/* dma_attr_burstsizes */
E 24
E 11
	1,			/* dma_attr_minxfer */
	0xffffffffull,		/* dma_attr_maxxfer */
	0xffffffffull,		/* dma_attr_seg */
D 11
	MAXRXFRAGS,		/* dma_attr_sgllen */
E 11
I 11
	1,			/* dma_attr_sgllen */
E 11
	1,			/* dma_attr_granular */
	0			/* dma_attr_flags */
};

E 26
D 24
static ddi_dma_attr_t sfe_dma_attr_nosc = {
E 24
I 24
static ddi_dma_attr_t sfe_dma_attr_desc = {
E 24
	DMA_ATTR_V0,		/* dma_attr_version */
I 11
D 18
#ifdef notdef
D 12
	/* when desc addr is 0, it make the nic idle */
E 12
I 12
	/* If desc addr is 0, it make the nic idle */
E 12
E 11
	0,			/* dma_attr_addr_lo */
I 11
#else
E 18
D 14
	0x2000,			/* dma_attr_addr_lo */
E 14
I 14
	16,			/* dma_attr_addr_lo */
E 14
D 18
#endif
E 18
E 11
	0xffffffffull,		/* dma_attr_addr_hi */
	0xffffffffull,		/* dma_attr_count_max */
	16,			/* dma_attr_align */
D 11
	0xffffffff,		/* dma_attr_burstsizes */
E 11
I 11
D 24
	0,			/* dma_attr_burstsizes */
E 24
I 24
D 34
	0xffffffff,		/* dma_attr_burstsizes */
E 34
I 34
	0x000003fc,		/* dma_attr_burstsizes */
E 34
E 24
E 11
	1,			/* dma_attr_minxfer */
	0xffffffffull,		/* dma_attr_maxxfer */
	0xffffffffull,		/* dma_attr_seg */
	1,			/* dma_attr_sgllen */
	1,			/* dma_attr_granular */
	0			/* dma_attr_flags */
};

I 36
uint32_t sfe_use_pcimemspace = 0;
E 36
/* ======================================================== */
/*
D 36
 * HW manupilation routines
E 36
I 36
 * HW manipulation routines
E 36
 */
/* ======================================================== */

D 36
#define	SFE_EEPROM_DELAY(dp)	{INL(dp, EROMAR);INL(dp, EROMAR);}
E 36
I 36
#define	SFE_EEPROM_DELAY(dp)	\
	{ (void) INL(dp, EROMAR); (void) INL(dp, EROMAR); }
E 36
#define	EE_CMD_READ	6
#define	EE_CMD_SHIFT	6

static uint16_t
D 29
sfe_read_eeprom(struct gem_dev *dp, int offset)
E 29
I 29
sfe_read_eeprom(struct gem_dev *dp, uint_t offset)
E 29
{
D 36
	int	eedi;
	int	i;
	int	ret;
E 36
I 36
	int		eedi;
	int		i;
	uint16_t	ret;
E 36

	/* ensure de-assert chip select */
	OUTL(dp, EROMAR, 0);
	SFE_EEPROM_DELAY(dp);
	OUTL(dp, EROMAR, EROMAR_EESK);
	SFE_EEPROM_DELAY(dp);

	/* assert chip select */
	offset |= EE_CMD_READ << EE_CMD_SHIFT;

	for (i = 8; i >= 0; i--) {
		/* make command */
		eedi = ((offset >> i) & 1) << EROMAR_EEDI_SHIFT;

		/* send 1 bit */
		OUTL(dp, EROMAR, EROMAR_EECS | eedi);
		SFE_EEPROM_DELAY(dp);
		OUTL(dp, EROMAR, EROMAR_EECS | eedi | EROMAR_EESK);
		SFE_EEPROM_DELAY(dp);
	}

	OUTL(dp, EROMAR, EROMAR_EECS);

	ret = 0;
	for (i = 0; i < 16; i++) {
		/* Get 1 bit */
		OUTL(dp, EROMAR, EROMAR_EECS);
		SFE_EEPROM_DELAY(dp);
		OUTL(dp, EROMAR, EROMAR_EECS | EROMAR_EESK);
		SFE_EEPROM_DELAY(dp);

		ret = (ret << 1) | ((INL(dp, EROMAR) >> EROMAR_EEDO_SHIFT) & 1);
	}

	OUTL(dp, EROMAR, 0);
	SFE_EEPROM_DELAY(dp);

D 36
	return ret;
E 36
I 36
	return (ret);
E 36
}
#undef SFE_EEPROM_DELAY

static boolean_t
sfe_get_mac_addr_dp83815(struct gem_dev *dp)
{
	uint8_t		*mac;
D 29
	int		val;
E 29
I 29
	uint_t		val;
E 29
	int		i;

#define	BITSET(p, ix, v)	(p)[(ix)/8] |= ((v) ? 1 : 0) << ((ix) & 0x7)
D 36
#define	BITTEST(v, pos)		((v) & (1 << (pos)))
E 36

D 6
	DPRINTF(4, (CE_CONT, "%s: sfe_get_mac_addr_dp83815: called", dp->name));
E 6
I 6
D 34
	DPRINTF(4, (CE_CONT, CONS "%s: sfe_get_mac_addr_dp83815: called",
		dp->name));
E 34
I 34
	DPRINTF(4, (CE_CONT, CONS "%s: %s: called", dp->name, __func__));
E 34
E 6

	mac = dp->dev_addr.ether_addr_octet;

	/* first of all, clear MAC address buffer */
	bzero(mac, ETHERADDRL);

	/* get bit 0 */
	val = sfe_read_eeprom(dp, 0x6);
	BITSET(mac, 0, val & 1);

	/* get bit 1 - 16 */
	val = sfe_read_eeprom(dp, 0x7);
	for (i = 0; i < 16; i++) {
		BITSET(mac, 1 + i, val & (1 << (15 - i)));
	}

	/* get bit 17 -  32 */
	val = sfe_read_eeprom(dp, 0x8);
	for (i = 0; i < 16; i++) {
		BITSET(mac, 17 + i, val & (1 << (15 - i)));
	}

	/* get bit 33 -  47 */
	val = sfe_read_eeprom(dp, 0x9);
	for (i = 0; i < 15; i++) {
		BITSET(mac, 33 + i, val & (1 << (15 - i)));
	}

D 29
	return TRUE;
E 29
I 29
D 31
	return B_TRUE;
E 31
I 31
	return (B_TRUE);
E 31
E 29
#undef BITSET
D 36
#undef BITTEST
E 36
}

static boolean_t
sfe_get_mac_addr_sis900(struct gem_dev *dp)
{
D 29
	int		val;
E 29
I 29
	uint_t		val;
E 29
	int		i;
	uint8_t		*mac;
D 36
	
E 36
I 36

E 36
	mac = dp->dev_addr.ether_addr_octet;

	for (i = 0; i < ETHERADDRL/2; i++) {
		val = sfe_read_eeprom(dp, 0x8 + i);
D 29
		*mac++ = val;
		*mac++ = val >> 8;
E 29
I 29
D 36
		*mac++ = (uint8_t) val;
		*mac++ = (uint8_t) (val >> 8);
E 36
I 36
		*mac++ = (uint8_t)val;
		*mac++ = (uint8_t)(val >> 8);
E 36
E 29
	}

D 29
	return TRUE;
E 29
I 29
D 31
	return B_TRUE;
E 31
I 31
	return (B_TRUE);
E 31
E 29
}

I 3
static dev_info_t *
sfe_search_pci_dev_subr(dev_info_t *cur_node, int vendor_id, int device_id)
{
	dev_info_t	*child_id;
	dev_info_t	*ret;
	int		vid, did;

	if (cur_node == NULL) {
D 31
		return NULL;
E 31
I 31
		return (NULL);
E 31
	}

	/* check brothers */
	do {
D 31
		vid = ddi_getprop(DDI_DEV_T_ANY, cur_node,
E 31
I 31
		vid = ddi_prop_get_int(DDI_DEV_T_ANY, cur_node,
E 31
D 36
					DDI_PROP_DONTPASS, "vendor-id", -1);
E 36
I 36
		    DDI_PROP_DONTPASS, "vendor-id", -1);
E 36
D 31
		did = ddi_getprop(DDI_DEV_T_ANY, cur_node,
E 31
I 31
		did = ddi_prop_get_int(DDI_DEV_T_ANY, cur_node,
E 31
D 36
					DDI_PROP_DONTPASS, "device-id", -1);
E 36
I 36
		    DDI_PROP_DONTPASS, "device-id", -1);
E 36

		if (vid == vendor_id && did == device_id) {
			/* found */
D 31
			return cur_node;
E 31
I 31
			return (cur_node);
E 31
		}

		/* check children */
		if ((child_id = ddi_get_child(cur_node)) != NULL) {
D 36
			if((ret = sfe_search_pci_dev_subr(
				child_id, vendor_id, device_id)) != NULL) {
E 36
I 36
			if ((ret = sfe_search_pci_dev_subr(child_id,
			    vendor_id, device_id)) != NULL) {
E 36
D 31
				return ret;
E 31
I 31
				return (ret);
E 31
			}
		}

D 13
	} while ((cur_node = ddi_get_next(cur_node)) != NULL);
E 13
I 13
	} while ((cur_node = ddi_get_next_sibling(cur_node)) != NULL);
E 13

	/* not found */
D 31
	return NULL;
E 31
I 31
	return (NULL);
E 31
}

static dev_info_t *
sfe_search_pci_dev(int vendor_id, int device_id)
{
D 31
	return sfe_search_pci_dev_subr(ddi_root_node(), vendor_id, device_id);
E 31
I 31
	return (sfe_search_pci_dev_subr(ddi_root_node(), vendor_id, device_id));
E 31
}

I 36
/* Avoid undefined symbol for non IA architectures */
#pragma weak	inb
#pragma weak	outb

E 36
E 3
static boolean_t
sfe_get_mac_addr_sis630e(struct gem_dev *dp)
{
D 10
#ifdef GET_MAC_ADDR_SIS630E
E 10
I 10
D 31
#if defined(i86pc) && defined(GET_MAC_ADDR_SIS630E)
E 31
I 31
D 36
#if defined(i86pc) && defined(CONFIG_MAC_ADDR_SIS630E)
E 31
E 10
	uint32_t	rfcrSave;
E 36
	int		i;
D 36
	uint16_t	v;
        dev_info_t	*isa_bridge;
        ddi_acc_handle_t isa_handle;
        int		reg;
E 36
I 36
	dev_info_t	*isa_bridge;
	ddi_acc_handle_t isa_handle;
	int		reg;
E 36

I 36
	if (inb == NULL || outb == NULL) {
		/* this is not IA architecture */
		return (B_FALSE);
	}

E 36
D 3
	/*
	 * ddi_find_devinfo() is undocumented officially,
	 * but it is described in /usr/include/sys/sunddi.h
	 */
	if ((isa_bridge = ddi_find_devinfo("pci1039,8", -1, 0)) == NULL) {
E 3
I 3
	if ((isa_bridge = sfe_search_pci_dev(0x1039, 0x8)) == NULL) {
E 3
D 13
		cmn_err(CE_WARN, "%s: cannot find isa-bridge (pci1039,8)",
E 13
I 13
		cmn_err(CE_WARN, "%s: failed to find isa-bridge pci1039,8",
E 13
D 36
				dp->name);
E 36
I 36
		    dp->name);
E 36
D 29
		return FALSE;
E 29
I 29
D 31
		return B_FALSE;
E 31
I 31
		return (B_FALSE);
E 31
E 29
	}

	if (pci_config_setup(isa_bridge, &isa_handle) != DDI_SUCCESS) {
		cmn_err(CE_WARN, "%s: ddi_regs_map_setup failed",
D 36
			dp->name);
E 36
I 36
		    dp->name);
E 36
D 29
		return FALSE;
E 29
I 29
D 31
		return B_FALSE;
E 31
I 31
		return (B_FALSE);
E 31
E 29
	}

	/* enable to access CMOS RAM */
	reg = pci_config_get8(isa_handle, 0x48);
	pci_config_put8(isa_handle, 0x48, reg | 0x40);

	for (i = 0; i < ETHERADDRL; i++) {
		outb(0x70, 0x09 + i);
D 36
		dp->dev_addr.ether_addr_octet[i] = inb(0x71); 
E 36
I 36
		dp->dev_addr.ether_addr_octet[i] = inb(0x71);
E 36
	}

D 13
	/* disnable to access CMOS RAM */
E 13
I 13
	/* disable to access CMOS RAM */
E 13
	pci_config_put8(isa_handle, 0x48, reg);
	pci_config_teardown(&isa_handle);
D 36
x:
E 36

D 29
	return TRUE;
E 29
I 29
D 31
	return B_TRUE;
E 31
I 31
	return (B_TRUE);
E 31
E 29
D 36
#else
D 29
	return FALSE;
E 29
I 29
D 31
	return B_FALSE;
E 31
I 31
	return (B_FALSE);
E 31
E 29
#endif
E 36
}

static boolean_t
sfe_get_mac_addr_sis635(struct gem_dev *dp)
{
	int		i;
	uint32_t	rfcr;
	uint16_t	v;
D 36
	struct sfe_dev	*lp = (struct sfe_dev *)dp->private;
E 36
I 36
	struct sfe_dev	*lp = dp->private;
E 36

D 6
	DPRINTF(2, (CE_CONT, "%s: sfe_get_mac_addr_sis635: called", dp->name));

E 6
I 6
D 34
	DPRINTF(2, (CE_CONT, CONS "%s: sfe_get_mac_addr_sis635: called",
		dp->name));
E 34
I 34
	DPRINTF(2, (CE_CONT, CONS "%s: %s: called", dp->name, __func__));
E 34
E 6
	rfcr = INL(dp, RFCR);

	OUTL(dp, CR, lp->cr | CR_RELOAD);
	OUTL(dp, CR, lp->cr);

	/* disable packet filtering before reading filter */
D 36
	OUTL(dp, RFCR, rfcr & ~RFCR_RFEN);
E 36
I 36
	OUTL_RXFILTER(dp, RFCR, rfcr & ~RFCR_RFEN);
E 36

	/* load MAC addr from filter data register */
D 36
	for (i = 0 ; i < ETHERADDRL ; i += 2) {
		OUTL(dp, RFCR,
E 36
I 36
	for (i = 0; i < ETHERADDRL; i += 2) {
		OUTL_RXFILTER(dp, RFCR,
E 36
		    (RFADDR_MAC_SIS900 + (i/2)) << RFCR_RFADDR_SHIFT_SIS900);
		v = INL(dp, RFDR);
D 29
		dp->dev_addr.ether_addr_octet[i]   = v;
		dp->dev_addr.ether_addr_octet[i+1] = v >> 8;
E 29
I 29
D 36
		dp->dev_addr.ether_addr_octet[i]   = (uint8_t) v;
		dp->dev_addr.ether_addr_octet[i+1] = (uint8_t) (v >> 8);
E 36
I 36
		dp->dev_addr.ether_addr_octet[i] = (uint8_t)v;
		dp->dev_addr.ether_addr_octet[i+1] = (uint8_t)(v >> 8);
E 36
E 29
	}

D 36
	/* re-enable packet filitering */
	OUTL(dp, RFCR, rfcr | RFCR_RFEN);
E 36
I 36
	/* re-enable packet filtering */
	OUTL_RXFILTER(dp, RFCR, rfcr | RFCR_RFEN);
E 36

D 29
	return TRUE;
E 29
I 29
D 36
	return B_TRUE;
E 36
I 36
	return (B_TRUE);
E 36
E 29
}

I 10
D 36
#ifdef i86pc
E 36
E 10
static boolean_t
sfe_get_mac_addr_sis962(struct gem_dev *dp)
{
D 29
	int	ret;
	int	i;
E 29
I 29
	boolean_t	ret;
	int		i;
E 29

I 28
D 29
	ret = FALSE;
E 29
I 29
	ret = B_FALSE;
E 29

E 28
D 36
	/* rise request signal */
E 36
I 36
	/* rise request signal to access EEPROM */
E 36
	OUTL(dp, MEAR, EROMAR_EEREQ);
D 28
	i = 200;
	while (--i) {
		if ((INL(dp, MEAR) & EROMAR_EEGNT) != 0) {
			break;
E 28
I 28
	for (i = 0; (INL(dp, MEAR) & EROMAR_EEGNT) == 0; i++) {
		if (i > 200) {
D 36
			/* failed to aquire eeprom */
E 36
I 36
			/* failed to acquire eeprom */
E 36
			cmn_err(CE_NOTE,
D 36
				CONS "%s: failed to access eeprom", dp->name);
E 36
I 36
			    CONS "%s: failed to access eeprom", dp->name);
E 36
			goto x;
E 28
		}
D 36
		drv_usecwait(10);      
E 36
I 36
		drv_usecwait(10);
E 36
	}
D 28

	if (i > 0) {
		ret = sfe_get_mac_addr_sis900(dp);
	} else {
		/* failed to get eeprom */
D 6
		cmn_err(CE_NOTE, "!%s: failed to access eeprom", dp->name);
E 6
I 6
		cmn_err(CE_NOTE, CONS "%s: failed to access eeprom", dp->name);
E 6
		ret = FALSE;
	}

E 28
I 28
	ret = sfe_get_mac_addr_sis900(dp);
x:
E 28
	/* release EEPROM */
	OUTL(dp, MEAR, EROMAR_EEDONE);

D 36
	return ret;
E 36
I 36
	return (ret);
E 36
}
I 10
D 36
#endif /* i86pc */
E 36
E 10

static int
D 7
sfe_reset_chip(struct gem_dev *dp)
E 7
I 7
sfe_reset_chip_sis900(struct gem_dev *dp)
E 7
{
	int		i;
D 7
	int		isr;
E 7
I 7
	uint32_t	done;
	uint32_t	val;
E 7
D 36
	struct sfe_dev	*lp = (struct sfe_dev *)dp->private;
E 36
I 36
	struct sfe_dev	*lp = dp->private;
E 36

I 6
D 7
	DPRINTF(4, (CE_CONT, CONS "%s: sfe_reset_chip called", dp->name));
E 7
I 7
D 34
	DPRINTF(4, (CE_CONT, CONS "%s: sfe_reset_chip_sis900 called",
		dp->name));
E 34
I 34
	DPRINTF(4, (CE_CONT, CONS "%s: %s called", dp->name, __func__));
E 34
E 7

I 34
	/* invalidate mac addr cache */
D 36
	bzero(lp->mac_addr, sizeof(lp->mac_addr));
E 36
I 36
	bzero(lp->mac_addr, sizeof (lp->mac_addr));
E 36

E 34
E 6
	lp->cr = 0;
I 34
D 36
#ifdef SANITY
E 34
	OUTL(dp, IER, 0);
D 34
	OUTL(dp, IMR, 0);
E 34
I 34
#endif
	lp->our_intr_bits = 0;
	OUTL(dp, IMR, lp->our_intr_bits);
E 34
	OUTL(dp, RFCR, 0);
E 36

I 36
	/* inhibit interrupt */
	OUTL(dp, IMR, 0);
	lp->isr_pended |= INL(dp, ISR) & lp->our_intr_bits;

	OUTL_RXFILTER(dp, RFCR, 0);
E 36
I 7
	OUTL(dp, CR, CR_RST | CR_TXR | CR_RXR);
	drv_usecwait(10);

D 28
	i    = 1000;
E 28
	done = 0;
D 28
	while (done != (ISR_TXRCMP | ISR_RXRCMP)) {
		if (--i == 0) {
E 28
I 28
	for (i = 0; done != (ISR_TXRCMP | ISR_RXRCMP); i++) {
		if (i > 1000) {
E 28
			cmn_err(CE_WARN, "%s: chip reset timeout", dp->name);
I 26
D 27
#if 1
			break;
#else
E 27
E 26
D 29
			return 1;	
E 29
I 29
D 36
			return (GEM_FAILURE);	
E 36
I 36
			return (GEM_FAILURE);
E 36
E 29
I 26
D 27
#endif
E 27
E 26
		}
		done |= INL(dp, ISR) & (ISR_TXRCMP | ISR_RXRCMP);
		drv_usecwait(10);
	}
D 10

E 10
I 10
D 36
#ifdef i86pc
E 36
I 36

E 36
E 10
	if (lp->revid == SIS630ET_900_REV) {
		lp->cr |= CR_ACCESSMODE;
		OUTL(dp, CR, lp->cr | INL(dp, CR));
	}
D 10

E 10
I 10
D 36
#endif
E 10
	/* Configration register: PCI parity enable */
E 36
I 36

	/* Configuration register: enable PCI parity */
E 36
	DPRINTF(2, (CE_CONT, CONS "%s: cfg:%b",
D 36
			dp->name, INL(dp, CFG), CFG_BITS_SIS900));
	val = CFG_PESEL;
E 36
I 36
	    dp->name, INL(dp, CFG), CFG_BITS_SIS900));
	val = 0;
E 36
	if (lp->revid >= SIS635A_900_REV ||
	    lp->revid == SIS900B_900_REV) {
		/* what is this ? */
		val |= CFG_RND_CNT;
	}
	OUTL(dp, CFG, val);
	DPRINTF(2, (CE_CONT, CONS "%s: cfg:%b", dp->name,
D 36
		INL(dp, CFG), CFG_BITS_SIS900));
E 36
I 36
	    INL(dp, CFG), CFG_BITS_SIS900));
E 36

D 29
	return 0;
E 29
I 29
	return (GEM_SUCCESS);
E 29
}

I 21
static int
E 21
sfe_reset_chip_dp83815(struct gem_dev *dp)
{
	int		i;
D 36
	struct sfe_dev	*lp = (struct sfe_dev *)dp->private;
E 36
I 36
	uint32_t	val;
	struct sfe_dev	*lp = dp->private;
E 36

D 34
	DPRINTF(4, (CE_CONT, CONS "%s: sfe_reset_chip_dp83815 called",
		dp->name));
E 34
I 34
	DPRINTF(4, (CE_CONT, CONS "%s: %s called", dp->name, __func__));
E 34

I 34
	/* invalidate mac addr cache */
D 36
	bzero(lp->mac_addr, sizeof(lp->mac_addr));
E 36
I 36
	bzero(lp->mac_addr, sizeof (lp->mac_addr));
E 36

E 34
	lp->cr = 0;
I 34
D 36
#ifdef SANITY
E 34
	OUTL(dp, IER, 0);
D 34
	OUTL(dp, IMR, 0);
E 34
I 34
#endif
	lp->our_intr_bits = 0;
	OUTL(dp, IMR, lp->our_intr_bits);
E 34
	OUTL(dp, RFCR, 0);
E 36

I 36
	/* inhibit interrupts */
	OUTL(dp, IMR, 0);
	lp->isr_pended |= INL(dp, ISR) & lp->our_intr_bits;

	OUTL_RXFILTER(dp, RFCR, 0);

E 36
E 7
	OUTL(dp, CR, CR_RST);
	drv_usecwait(10);

D 28
	i   = 100;
	while ((INL(dp, CR) & CR_RST) != 0) {
		if (--i == 0) {
			cmn_err(CE_WARN, "%s: chip reset timeout", dp->name);
E 28
I 28
D 34
	for (i = 0; (INL(dp, CR) & CR_RST) != 0; i++) {
E 34
I 34
	for (i = 0; INL(dp, CR) & CR_RST; i++) {
E 34
		if (i > 100) {
			cmn_err(CE_WARN, "!%s: chip reset timeout", dp->name);
E 28
D 29
			return 1;	
E 29
I 29
D 36
			return (GEM_FAILURE);	
E 36
I 36
			return (GEM_FAILURE);
E 36
E 29
		}
		drv_usecwait(10);
	}
I 36
	DPRINTF(0, (CE_CONT, "!%s: chip reset in %duS", dp->name, i*10));
E 36

D 7
	if (lp->chip->chip_type == CHIPTYPE_SIS900) {
		if (lp->revid == SIS630ET_900_REV) {
			lp->cr |= CR_ACCESSMODE;
			OUTL(dp, CR, lp->cr | INL(dp, CR));
		}
	}
I 6
	else if (lp->chip->chip_type == CHIPTYPE_DP83815) {
		OUTL(dp, CCSR, CCSR_PMESTS);
		OUTL(dp, CCSR, 0);
	}
E 7
I 7
	OUTL(dp, CCSR, CCSR_PMESTS);
	OUTL(dp, CCSR, 0);
E 7
E 6

I 7
D 31
	/* Configration register: PCI parity enable */
E 31
I 31
D 36
	/* Configration register: enable PCI parity */
E 36
I 36
	/* Configuration register: enable PCI parity */
E 36
E 31
	DPRINTF(2, (CE_CONT, CONS "%s: cfg:%b",
D 36
			dp->name, INL(dp, CFG), CFG_BITS_DP83815));
	OUTL(dp, CFG, CFG_PESEL | CFG_PAUSE_ADV);
E 36
I 36
	    dp->name, INL(dp, CFG), CFG_BITS_DP83815));
	val = INL(dp, CFG) & (CFG_ANEG_SEL | CFG_PHY_CFG);
	OUTL(dp, CFG, val | CFG_PAUSE_ADV);
E 36
	DPRINTF(2, (CE_CONT, CONS "%s: cfg:%b", dp->name,
D 36
		INL(dp, CFG), CFG_BITS_DP83815));
E 36
I 36
	    INL(dp, CFG), CFG_BITS_DP83815));
E 36

E 7
D 29
	return 0;
E 29
I 29
	return (GEM_SUCCESS);
E 29
}

D 31
static void
E 31
I 31
static int
E 31
sfe_init_chip(struct gem_dev *dp)
{
D 9
	uint32_t	val;
	int		i;
E 9
D 36
	struct sfe_dev	*lp = (struct sfe_dev *)dp->private;
E 36
I 36
	/* Configuration register: have been set up in sfe_chip_reset */
E 36
D 7

E 7
I 7
D 9
#ifdef notdef
E 7
	/* Configration register: PCI parity enable */
D 6
	DPRINTF(2, (CE_CONT, "?%s: cfg:%b", dp->name, INL(dp, CFG), CFG_BITS));
E 6
I 6
	DPRINTF(2, (CE_CONT, CONS "%s: cfg:%b",
			dp->name, INL(dp, CFG), CFG_BITS));
E 6
	val = CFG_PESEL;
	if (lp->chip->chip_type == CHIPTYPE_DP83815) {
		/* force to advertise pause capability */
		val |= CFG_PAUSE_ADV;
	}
	else if (lp->chip->chip_type == CHIPTYPE_SIS900) {
		if (lp->revid >= SIS635A_900_REV ||
		    lp->revid == SIS900B_900_REV) {
			/* what is this ? */
			val |= CFG_RND_CNT;
		}
	}
	OUTL(dp, CFG, val);
D 6
	DPRINTF(2, (CE_CONT, "?%s: cfg:%b", dp->name, INL(dp, CFG), CFG_BITS));

E 6
I 6
	DPRINTF(2, (CE_CONT, CONS "%s: cfg:%b", dp->name,
		INL(dp, CFG), CFG_BITS));
I 7
#else
E 9
I 9

E 9
D 36
	/* Configration register: have been set up in sfe_chip_reset */
D 9
#endif
E 9
I 9

E 36
E 9
E 7
E 6
	/* PCI test control register: do nothing */

D 36
	/* Interrupt status register : clear pended interrupts */
D 9
	(volatile int)i = INL(dp, ISR);
E 9
I 9
	(void) INL(dp, ISR);
E 9
D 34

	/* Interrupt enable register: enable interrupt */
E 34
I 34
#ifdef SANITY
	/* Interrupt enable register: disable interrupt */
E 34
	OUTL(dp, IER, 0);
D 34

	/* Interrupt mask register: clear */
D 7
	if (lp->chip->chip_type == CHIPTYPE_SIS900) {
		lp->our_intr_bits = OUR_INTR_BITS_SIS900;
	} else {
		lp->our_intr_bits = OUR_INTR_BITS;
	}
E 7
I 7
	lp->our_intr_bits = OUR_INTR_BITS;
I 29
D 31
#if 1
	lp->our_intr_bits |= ISR_TXOK;;
E 31
I 31
#ifdef NEVER
	lp->our_intr_bits |= ISR_TXOK;
E 34
E 31
#endif
I 34
	/* Interrupt mask register: clear */
	lp->our_intr_bits = 0;
E 34
E 29
E 7
	OUTL(dp, IMR, lp->our_intr_bits);
E 36
I 36
	/* Interrupt status register : do nothing */
E 36

I 36
	/* Interrupt mask register: clear, but leave lp->our_intr_bits */
	OUTL(dp, IMR, 0);

E 36
	/* Enhanced PHY Access register (sis900): do nothing */

	/* Transmit Descriptor Pointer register: base addr of TX ring */
	OUTL(dp, TXDP, dp->tx_ring_dma);

	/* Receive descriptor pointer register: base addr of RX ring */
I 11
D 36
	ASSERT(dp->rx_ring_dma != 0);
E 36
E 11
	OUTL(dp, RXDP, dp->rx_ring_dma);
I 31

	return (GEM_SUCCESS);
E 31
D 12

E 12
I 12
D 28
#ifdef notdef
E 12
	/* Tx and Rx configuration registers, flow/pause control register */
	sfe_set_media(dp);
I 12
#endif
E 28
E 12
I 7
}
E 7

D 7
#ifdef notdef
	/* Set Mac address, Rx filter and Rx mode */
	sfe_set_rx_filter(dp);	/* do later */
#endif
E 7
I 7
static uint_t
sfe_mcast_hash(struct gem_dev *dp, uint8_t *addr)
{
D 29
	return gem_ether_crc_be(addr);
E 29
I 29
	return (gem_ether_crc_be(addr, ETHERADDRL));
E 29
E 7
}

I 34
#ifdef DEBUG_LEVEL
static void
sfe_rxfilter_dump(struct gem_dev *dp, int start, int end)
{
	int		i;
	int		j;
	uint16_t	ram[0x10];

	cmn_err(CE_CONT, "!%s: rx filter ram dump:", dp->name);
#define	WORDS_PER_LINE	4
	for (i = start; i < end; i += WORDS_PER_LINE*2) {
		for (j = 0; j < WORDS_PER_LINE; j++) {
D 36
			OUTL(dp, RFCR, RFADDR_MAC_DP83815 + i + j*2);
E 36
I 36
			OUTL_RXFILTER(dp, RFCR, RFADDR_MAC_DP83815 + i + j*2);
E 36
			ram[j] = INL(dp, RFDR);
		}
D 36
		cmn_err(CE_CONT, "!0x%02x: 0x%04x 0x%04x 0x%04x 0x%04x", 
			i, ram[0], ram[1], ram[2], ram[3]);
	}
E 36
I 36

		cmn_err(CE_CONT, "!0x%02x: 0x%04x 0x%04x 0x%04x 0x%04x",
		    i, ram[0], ram[1], ram[2], ram[3]);
		}

E 36
#undef	WORDS_PER_LINE
}
#endif

I 36
static uint_t	sfe_rf_perfect_base_dp83815[] = {
	RFADDR_PMATCH0_DP83815,
	RFADDR_PMATCH1_DP83815,
	RFADDR_PMATCH2_DP83815,
	RFADDR_PMATCH3_DP83815,
};

E 36
E 34
D 31
static void
E 31
I 31
static int
E 31
sfe_set_rx_filter_dp83815(struct gem_dev *dp)
{
	int		i;
I 29
	int		j;
E 29
	uint32_t	mode;
D 34
	int		addr_shift;
	uint8_t		*mac;
E 34
I 34
	uint8_t		*mac = dp->cur_addr.ether_addr_octet;
E 34
D 29
#ifdef USE_MULTICAST_HASHTBL
E 29
D 7
	static uint16_t	hash_tbl[0x200/2];
E 7
I 7
	uint16_t	hash_tbl[32];
I 34
D 36
	struct sfe_dev	*lp = (struct sfe_dev *)dp->private;
E 36
I 36
	struct sfe_dev	*lp = dp->private;
E 36
E 34
E 7
D 29
#endif
E 29

D 6
	DPRINTF(4, (CE_CONT, "%s: sfe_set_rx_filter_dp83815: called",
E 6
I 6
D 29
	DPRINTF(4, (CE_CONT, CONS "%s: sfe_set_rx_filter_dp83815: called",
E 6
		dp->name));
E 29
I 29
D 34
	DPRINTF(4, (CE_CONT, CONS "%s: %s: called", dp->name, __func__));
E 34
I 34
	DPRINTF(1, (CE_CONT, CONS "%s: %s: called, mc_count:%d, mode:0x%b",
D 36
		dp->name, __func__, dp->mc_count, dp->rxmode, RXMODE_BITS));
E 36
I 36
	    dp->name, __func__, dp->mc_count, dp->rxmode, RXMODE_BITS));
E 36
E 34
E 29

I 34
#if DEBUG_LEVEL > 0
	for (i = 0; i < dp->mc_count; i++) {
		cmn_err(CE_CONT,
		"!%s: adding mcast(%d) %02x:%02x:%02x:%02x:%02x:%02x",
D 36
			dp->name, i,
			dp->mc_list[i].addr.ether_addr_octet[0],
			dp->mc_list[i].addr.ether_addr_octet[1],
			dp->mc_list[i].addr.ether_addr_octet[2],
			dp->mc_list[i].addr.ether_addr_octet[3],
			dp->mc_list[i].addr.ether_addr_octet[4],
			dp->mc_list[i].addr.ether_addr_octet[5]);
E 36
I 36
		    dp->name, i,
		    dp->mc_list[i].addr.ether_addr_octet[0],
		    dp->mc_list[i].addr.ether_addr_octet[1],
		    dp->mc_list[i].addr.ether_addr_octet[2],
		    dp->mc_list[i].addr.ether_addr_octet[3],
		    dp->mc_list[i].addr.ether_addr_octet[4],
		    dp->mc_list[i].addr.ether_addr_octet[5]);
E 36
	}
#endif
E 34
I 31
	if ((dp->rxmode & RXMODE_ENABLE) == 0) {
D 36
		/* disalbe rx filter */
		OUTL(dp, RFCR, 0);
E 36
I 36
		/* disable rx filter */
		OUTL_RXFILTER(dp, RFCR, 0);
E 36
D 33
		return;
E 33
I 33
		return (GEM_SUCCESS);
E 33
	}

E 31
D 34
	addr_shift = RFCR_RFADDR_SHIFT_DP83815;
	mac = dp->cur_addr.ether_addr_octet;
E 34
D 36

	/* Set Receive filter control register */
E 36
I 36
	/*
	 * Set Receive filter control register
	 */
E 36
D 31

E 31
D 34
	if ((dp->rxmode & RXMODE_PROMISC) != 0) {
E 34
I 34
	if (dp->rxmode & RXMODE_PROMISC) {
E 34
D 36
		mode = RFCR_AAB		/* all broadcast */
		     | RFCR_AAM		/* all multicast */
		     | RFCR_AAP;	/* all physcal */
	}
D 29
	else if ((dp->rxmode & RXMODE_ALLMULTI) != 0) {
E 29
I 29
D 34
	else if ((dp->rxmode & RXMODE_ALLMULTI) != 0 ||
		  dp->mc_count > 16*32/2) {
E 34
I 34
	else if ((dp->rxmode & RXMODE_ALLMULTI) || dp->mc_count > 16*32/2) {
E 34
E 29
		mode = RFCR_AAB		/* all broadcast */
		     | RFCR_AAM		/* all multicast */
		     | RFCR_APM_DP83815;/* physical for the chip */
	}
I 29
D 31
	else if (dp->mc_count > 4) {
E 31
I 31
D 34
#ifdef TEST_HASH_FILTER
	else if (dp->mc_count > 0)
#else
E 34
I 34
#ifdef CONFIG_PATTERN_MATCH_DP83815
E 34
	else if (dp->mc_count > 4)
I 34
#else
	else if (dp->mc_count > 0)
E 34
#endif
	{
E 31
		/* use multicast hash table */
		mode = RFCR_AAB		/* all broadcast */
		     | RFCR_MHEN_DP83815/* enable mcast hash tble */
		     | RFCR_APM_DP83815;/* physical for the chip */
E 36
I 36
		/* all broadcast, all multicast, all physical */
		mode = RFCR_AAB | RFCR_AAM | RFCR_AAP;
	} else if ((dp->rxmode & RXMODE_ALLMULTI) || dp->mc_count > 16*32/2) {
		/* all broadcast, all multicast, physical for the chip */
		mode = RFCR_AAB | RFCR_AAM | RFCR_APM_DP83815;
	} else if (dp->mc_count > 4) {
		/*
		 * Use multicast hash table,
		 * accept all broadcast and physical for the chip.
		 */
		mode = RFCR_AAB | RFCR_MHEN_DP83815 | RFCR_APM_DP83815;
E 36

D 31
		/* make hash table */
E 31
I 31
D 36
		/* make hash table (passed) */
E 31
		bzero(hash_tbl, sizeof(hash_tbl));
E 36
I 36
		bzero(hash_tbl, sizeof (hash_tbl));
E 36
		for (i = 0; i < dp->mc_count; i++) {
D 31
			j = dp->mc_list[i].hash & (32*16 - 1);
E 31
I 31
			j = dp->mc_list[i].hash >> (32 - 9);
E 31
			hash_tbl[j / 16] |= 1 << (j % 16);
		}
I 36
	} else {
		/*
		 * Use pattern mach filter for multicast address,
		 * accept all broadcast and physical for the chip
		 */
		/* need to enable corresponding pattern registers */
		mode = RFCR_AAB | RFCR_APM_DP83815 |
		    (((1 << dp->mc_count) - 1) << RFCR_APAT_SHIFT);
E 36
	}
E 29
D 36
	else {
I 29
D 34
		/* use perfect mach filter */
E 34
I 34
		ASSERT(dp->mc_count <= 4);
		/* use pattern mach filter for multicast address */
E 34
E 29
		mode = RFCR_AAB		/* all broadcast */
D 34
		     | RFCR_APM_DP83815;/* physical for the chip */
E 34
I 34
		     | RFCR_APM_DP83815	/* physical for the chip */
		     | (((1 << dp->mc_count) - 1) << RFCR_APAT_SHIFT);
				/* enable corresponding pattern registers */
	}
E 36
E 34
D 7
		if (dp->mc_count > 0) {
E 7
I 7

D 29
		if (dp->mc_count == 0) {
			/* no multicast, do nothing */
		} else
#ifdef USE_MULTICAST_PERFECT
		if (dp->mc_count <= 4) {
			for (i = 0; i < dp->mc_count; i++) {
D 8
				mode |= 1 << (RFCR_APAT_SHIFT + 1);
E 8
I 8
				mode |= 1 << (RFCR_APAT_SHIFT + i);
E 8
			}
		} else
#endif
E 7
#ifdef USE_MULTICAST_HASHTBL
D 7
			mode |= RFCR_MHEN_DP83815;	/* ? */
E 7
I 7
D 8
		if (dp->mc_count <= 100) {
E 8
I 8
		if (dp->mc_count <= 16*32/2) {
E 8
			/* use multicast hash table */
			/* enable mcast hash tble */
			mode |= RFCR_MHEN_DP83815;

			/* make hash table */
E 7
			bzero(hash_tbl, sizeof(hash_tbl));
D 7
			/* make hash table; not implemented */
#else
			mode |= RFCR_AAM;
E 7
I 7
			for (i = 0; i < dp->mc_count; i++) {
				uint_t	h;
				h = dp->mc_list[i].hash & (32*16 - 1);
				hash_tbl[h / 16] |= 1 << (h % 16);
			}
		} else
E 7
#endif
I 7
		{
			mode |= RFCR_AAM;
E 29
I 29
D 34
		/* enable multicast address registers */
		for (i = 0; i < dp->mc_count; i++) {
			mode |= 1 << (RFCR_APAT_SHIFT + i);
E 34
I 34
#if DEBUG_LEVEL > 1
	cmn_err(CE_CONT,
D 36
		"!%s: mac %02x:%02x:%02x:%02x:%02x:%02x"
		"  cache %02x:%02x:%02x:%02x:%02x:%02x",
			dp->name,
			mac[0], mac[1], mac[2], mac[3], mac[4], mac[5],
			lp->mac_addr[0], lp->mac_addr[1], lp->mac_addr[2],
			lp->mac_addr[3], lp->mac_addr[4], lp->mac_addr[5]);
E 36
I 36
	    "!%s: mac %02x:%02x:%02x:%02x:%02x:%02x"
	    "  cache %02x:%02x:%02x:%02x:%02x:%02x",
	    dp->name, mac[0], mac[1], mac[2], mac[3], mac[4], mac[5],
	    lp->mac_addr[0], lp->mac_addr[1],
	    lp->mac_addr[2], lp->mac_addr[3],
	    lp->mac_addr[4], lp->mac_addr[5]);
E 36
#endif
	if (bcmp(mac, lp->mac_addr, ETHERADDRL) != 0) {
		/*
		 * XXX - need to *disable* rx filter to load mac address for
D 36
		 * the chip. otherwise, we cannot setup rxfileter correctly.
E 36
I 36
		 * the chip. otherwise, we cannot setup rxfilter correctly.
E 36
		 */
I 36
		/* setup perfect match register for my station address */
E 36
		for (i = 0; i < ETHERADDRL; i += 2) {
D 36
			OUTL(dp, RFCR, RFADDR_MAC_DP83815 + i);
			OUTL(dp, RFDR, (mac[i+1] << 8) | mac[i]);
E 36
I 36
			OUTL_RXFILTER(dp, RFCR, RFADDR_MAC_DP83815 + i);
			OUTL_RXFILTER(dp, RFDR, (mac[i+1] << 8) | mac[i]);
E 36
E 34
E 29
E 7
		}
D 34
	}
E 34

D 31
	/* Disable Rx filter and load mac address for the chip */
E 31
I 31
D 34
	/* need to disable rx filter to load mac address for the chip */
E 31
	for (i = 0; i < ETHERADDRL; i += 2) {
		OUTL(dp, RFCR, RFADDR_MAC_DP83815 + i);
		OUTL(dp, RFDR, (mac[i+1] << 8) | mac[i]);
E 34
I 34
		bcopy(mac, lp->mac_addr, ETHERADDRL);
E 34
	}

I 7
D 29
#ifdef USE_MULTICAST_PERFECT
	if (mode & RFCR_APAT_DP83815) {
D 8
		int		j;
E 8
I 8
		int	j;
E 29
I 29
D 34
	if ((mode & RFCR_APAT_DP83815) != 0) {
E 34
I 34
#if DEBUG_LEVEL > 3
	/* clear pattern ram */
	for (j = 0x200; j < 0x380; j += 2) {
D 36
		OUTL(dp, RFCR, j);
		OUTL(dp, RFDR, 0);
E 36
I 36
		OUTL_RXFILTER(dp, RFCR, j);
		OUTL_RXFILTER(dp, RFDR, 0);
E 36
	}
#endif
	if (mode & RFCR_APAT_DP83815) {
E 34
E 29
E 8
D 36
		static uint_t	rf_perfect_base[]= {
D 34
			RFADDR_PMATCH0_DP83815, RFADDR_PMATCH1_DP83815,
D 8
			RFADDR_PMATCH3_DP83815, RFADDR_PMATCH3_DP83815,}
E 8
I 8
D 13
			RFADDR_PMATCH3_DP83815, RFADDR_PMATCH3_DP83815};
E 13
I 13
			RFADDR_PMATCH2_DP83815, RFADDR_PMATCH3_DP83815};
E 13
E 8

D 31
		/* setup perfect match patterns*/
E 31
I 31
		/* setup perfect match patterns */
E 34
I 34
					RFADDR_PMATCH0_DP83815,
					RFADDR_PMATCH1_DP83815,
					RFADDR_PMATCH2_DP83815,
					RFADDR_PMATCH3_DP83815,
				};
E 36
		/* setup multicast address into pattern match registers */
E 34
E 31
		for (j = 0; j < dp->mc_count; j++) {
			mac = &dp->mc_list[j].addr.ether_addr_octet[0];
			for (i = 0; i < ETHERADDRL; i += 2) {
D 36
				OUTL(dp, RFCR, rf_perfect_base[j] + i*2);
				OUTL(dp, RFDR, (mac[i+1] << 8) | mac[i]);
E 36
I 36
				OUTL_RXFILTER(dp, RFCR,
				    sfe_rf_perfect_base_dp83815[j] + i*2);
				OUTL_RXFILTER(dp, RFDR,
				    (mac[i+1] << 8) | mac[i]);
E 36
			}
		}

D 34
		/* setup pattern count register */
E 34
I 34
		/* setup pattern count registers */
E 34
D 36
		OUTL(dp, RFCR, RFADDR_PCOUNT01_DP83815);
D 29
		OUTL(dp, RFDR, ETHERADDRL<<8 | ETHERADDRL);
E 29
I 29
		OUTL(dp, RFDR, (ETHERADDRL << 8) | ETHERADDRL);
E 29
		OUTL(dp, RFCR, RFADDR_PCOUNT23_DP83815);
D 29
		OUTL(dp, RFDR, ETHERADDRL<<8 | ETHERADDRL);
E 29
I 29
		OUTL(dp, RFDR, (ETHERADDRL << 8) | ETHERADDRL);
E 36
I 36
		OUTL_RXFILTER(dp, RFCR, RFADDR_PCOUNT01_DP83815);
		OUTL_RXFILTER(dp, RFDR, (ETHERADDRL << 8) | ETHERADDRL);
		OUTL_RXFILTER(dp, RFCR, RFADDR_PCOUNT23_DP83815);
		OUTL_RXFILTER(dp, RFDR, (ETHERADDRL << 8) | ETHERADDRL);
E 36
E 29
	}
D 29
#endif
E 7
#ifdef USE_MULTICAST_HASHTBL
	if (mode & RFCR_MHEN_DP83815) {
E 29
I 29

D 34
	if ((mode & RFCR_MHEN_DP83815) != 0) {
E 34
I 34
	if (mode & RFCR_MHEN_DP83815) {
E 34
E 29
		/* Load Multicast hash table */
D 7
		/* Sorry, not yet */
E 7
I 7
D 31
		for (i = 0; i < 32; i++ ) {
E 31
I 31
		for (i = 0; i < 32; i++) {
E 31
D 29
			/* For Dp83815, index is in byte */
E 29
I 29
			/* for DP83815, index is in byte */
E 29
D 36
			OUTL(dp, RFCR, RFADDR_MULTICAST_DP83815 + i*2);
			OUTL(dp, RFDR, hash_tbl[i]);
E 36
I 36
			OUTL_RXFILTER(dp, RFCR, RFADDR_MULTICAST_DP83815 + i*2);
			OUTL_RXFILTER(dp, RFDR, hash_tbl[i]);
E 36
		}
E 7
	}
D 29
#endif
E 29
I 29
D 34

E 34
I 34
#if DEBUG_LEVEL > 2
	sfe_rxfilter_dump(dp, 0, 0x10);
	sfe_rxfilter_dump(dp, 0x200, 0x380);
#endif
E 34
E 29
	/* Set rx filter mode and enable rx filter */
D 36
	OUTL(dp, RFCR, RFCR_RFEN | mode);
E 36
I 36
	OUTL_RXFILTER(dp, RFCR, RFCR_RFEN | mode);
E 36
I 31

	return (GEM_SUCCESS);
E 31
}

D 31
static void
E 31
I 31
static int
E 31
sfe_set_rx_filter_sis900(struct gem_dev *dp)
{
	int		i;
	uint32_t	mode;
D 7
	uint32_t	hash_tbl[8];
E 7
I 7
	uint16_t	hash_tbl[16];
E 7
D 34
	uint8_t		*mac;
E 34
I 34
	uint8_t		*mac = dp->cur_addr.ether_addr_octet;
E 34
D 29
	uint16_t	m[3];
E 29
I 7
	int		hash_size;
	int		hash_shift;
D 36
	struct sfe_dev	*lp = (struct sfe_dev *)dp->private;
E 36
I 36
	struct sfe_dev	*lp = dp->private;
E 36
E 7

D 6
	DPRINTF(4, (CE_CONT, "%s: sfe_set_rx_filter_sis900: called", dp->name));

E 6
I 6
D 29
	DPRINTF(4, (CE_CONT, CONS "%s: sfe_set_rx_filter_sis900: called",
			dp->name));
E 6
	mac = dp->cur_addr.ether_addr_octet;
E 29
I 29
	DPRINTF(4, (CE_CONT, CONS "%s: %s: called", dp->name, __func__));
E 29

I 33
	if ((dp->rxmode & RXMODE_ENABLE) == 0) {
		/* disalbe rx filter */
D 36
		OUTL(dp, RFCR, 0);
E 36
I 36
		OUTL_RXFILTER(dp, RFCR, 0);
E 36
		return (GEM_SUCCESS);
	}

E 33
I 7
	/*
D 36
	 * determin hardware hash table size in word.
E 36
I 36
	 * determine hardware hash table size in word.
E 36
	 */
	hash_shift = 25;
D 29
	if ((lp->revid >= SIS635A_900_REV) ||
	    (lp->revid == SIS900B_900_REV)) {
E 29
I 29
	if (lp->revid >= SIS635A_900_REV || lp->revid == SIS900B_900_REV) {
E 29
		hash_shift = 24;
	}
	hash_size = (1 << (32 - hash_shift)) / 16;
D 36
	bzero(hash_tbl, sizeof(hash_tbl));
E 36
I 36
	bzero(hash_tbl, sizeof (hash_tbl));
E 36

E 7
	/* Set Receive filter control register */

D 34
	if ((dp->rxmode & RXMODE_PROMISC) != 0) {
E 34
I 34
	if (dp->rxmode & RXMODE_PROMISC) {
I 36
		/* all broadcast, all multicast, all physical */
E 36
E 34
		mode = RFCR_AAB | RFCR_AAM | RFCR_AAP;
D 36
	}
D 29
	else if ((dp->rxmode & RXMODE_ALLMULTI) != 0) {
E 29
I 29
D 34
	else if ((dp->rxmode & RXMODE_ALLMULTI) != 0 ||
E 34
I 34
	else if ((dp->rxmode & RXMODE_ALLMULTI) ||
E 34
		  dp->mc_count > hash_size*16/2) {
E 36
I 36
	} else if ((dp->rxmode & RXMODE_ALLMULTI) ||
	    dp->mc_count > hash_size*16/2) {
		/* all broadcast, all multicast, physical for the chip */
E 36
E 29
		mode = RFCR_AAB | RFCR_AAM;
D 36
	}
	else {
E 36
I 36
	} else {
		/* all broadcast, physical for the chip */
E 36
		mode = RFCR_AAB;
D 7
		if (dp->mc_count > 0) {
E 7
I 7
D 29
		if (dp->mc_count == 0) {
			/* no multicast, do nothing */
		} else
E 7
#ifdef USE_MULTICAST_HASHTBL
D 7
			/* make hash table; not implemented */
#else
			mode |= RFCR_AAM;
E 7
I 7
		if (dp->mc_count < 100) {
			/* make hash table */
			for (i = 0; i < dp->mc_count; i++) {
				uint_t	h;
				h = dp->mc_list[i].hash >> hash_shift;
				hash_tbl[h / 16] |= 1 << (h % 16);
			}
		} else
E 7
#endif
D 7
		} else {
			bzero(hash_tbl, sizeof(hash_tbl));
E 7
I 7
		{
			mode |= RFCR_AAM;
E 29
I 29
D 36
		/* make hash table */
		for (i = 0; i < dp->mc_count; i++) {
			uint_t	h;
			h = dp->mc_list[i].hash >> hash_shift;
			hash_tbl[h / 16] |= 1 << (h % 16);
E 29
E 7
		}
E 36
	}

I 36
	/* make hash table */
	for (i = 0; i < dp->mc_count; i++) {
		uint_t	h;
		h = dp->mc_list[i].hash >> hash_shift;
		hash_tbl[h / 16] |= 1 << (h % 16);
	}

E 36
D 34
	/* Disable Rx filter and load mac address */
I 29
	mac = dp->cur_addr.ether_addr_octet;
E 29
D 7
	for (i = 0; i < ETHERADDRL; i += 2) {
E 7
I 7
	for (i = 0; i < ETHERADDRL/2; i++) {
		/* For sis900, index is in word */
E 7
		OUTL(dp, RFCR,
D 7
		    (RFADDR_MAC_SIS900 + (i/2)) << RFCR_RFADDR_SHIFT_SIS900);
		OUTL(dp, RFDR, (mac[i+1] << 8) | mac[i]);
E 7
I 7
		    (RFADDR_MAC_SIS900 + i) << RFCR_RFADDR_SHIFT_SIS900);
		OUTL(dp, RFDR, (mac[i*2+1] << 8) | mac[i*2]);
E 34
I 34
	if (bcmp(mac, lp->mac_addr, ETHERADDRL) != 0) {
		/* Disable Rx filter and load mac address */
		for (i = 0; i < ETHERADDRL/2; i++) {
			/* For sis900, index is in word */
D 36
			OUTL(dp, RFCR,
E 36
I 36
			OUTL_RXFILTER(dp, RFCR,
E 36
			    (RFADDR_MAC_SIS900+i) << RFCR_RFADDR_SHIFT_SIS900);
D 36
			OUTL(dp, RFDR, (mac[i*2+1] << 8) | mac[i*2]);
E 36
I 36
			OUTL_RXFILTER(dp, RFDR, (mac[i*2+1] << 8) | mac[i*2]);
E 36
		}

		bcopy(mac, lp->mac_addr, ETHERADDRL);
E 34
E 7
	}

	/* Load Multicast hash table */
D 7
	for (i = 0; i < 8; i++) {
E 7
I 7
	for (i = 0; i < hash_size; i++) {
		/* For sis900, index is in word */
E 7
D 36
		OUTL(dp, RFCR,
E 36
I 36
		OUTL_RXFILTER(dp, RFCR,
E 36
		    (RFADDR_MULTICAST_SIS900 + i) << RFCR_RFADDR_SHIFT_SIS900);
D 36
		OUTL(dp, RFDR, hash_tbl[i]);
E 36
I 36
		OUTL_RXFILTER(dp, RFDR, hash_tbl[i]);
E 36
	}

	/* Load rx filter mode and enable rx filter */
D 36
	OUTL(dp, RFCR, RFCR_RFEN | mode);
E 36
I 36
	OUTL_RXFILTER(dp, RFCR, RFCR_RFEN | mode);
E 36
I 31

	return (GEM_SUCCESS);
E 31
}

D 31
static void
E 31
I 31
static int
E 31
sfe_start_chip(struct gem_dev *dp)
{
D 36
	struct sfe_dev	*lp = (struct sfe_dev *)dp->private;
E 36
I 36
	struct sfe_dev	*lp = dp->private;
E 36

I 6
D 29
	DPRINTF(4, (CE_CONT, CONS "%s: sfe_start_chip: called", dp->name));
E 29
I 29
	DPRINTF(4, (CE_CONT, CONS "%s: %s: called", dp->name, __func__));
E 29

I 34
D 36
	/* setup interrupt mask */
E 36
I 36
	/*
	 * setup interrupt mask, which shouldn't include ISR_TOK
	 * to improve performance.
	 */
E 36
	lp->our_intr_bits = OUR_INTR_BITS;
D 36
#ifdef NEVER
	lp->our_intr_bits |= ISR_TXOK;
#endif
E 36
I 36

E 36
E 34
I 12
D 29
	/*
	 * Setup Tx and Rx configuration registers and
	 * flow/pause control register.
	 */
	sfe_set_media(dp);

E 29
E 12
E 6
	/* enable interrupt */
I 4
D 10
#ifdef NOINTR_WORKAROUND
	lp->ier = 1;
#else
E 4
	OUTL(dp, IER, IER_IE);
D 4

E 4
I 4
#endif
E 10
I 10
	if ((dp->misc_flag & GEM_NOINTR) == 0) {
I 34
D 36
		OUTL(dp, IMR, lp->our_intr_bits);
E 36
E 34
		OUTL(dp, IER, 1);
I 36
		OUTL(dp, IMR, lp->our_intr_bits);
E 36
	}

E 10
E 4
	/* Kick RX */
	OUTL(dp, CR, lp->cr | CR_RXE);
I 31

	return (GEM_SUCCESS);
E 31
}

I 36
/*
 * Stop nic core gracefully.
 */
E 36
D 29
static void
E 29
I 29
static int
E 29
sfe_stop_chip(struct gem_dev *dp)
{
D 36
	struct sfe_dev	*lp = (struct sfe_dev *)dp->private;
E 36
I 36
	struct sfe_dev	*lp = dp->private;
E 36
I 7
	uint32_t	done;
	int		i;
I 36
	uint32_t	val;
E 36
E 7

I 6
D 34
	DPRINTF(4, (CE_CONT, CONS "%s: sfe_stop_chip: called", dp->name));
E 34
I 34
	DPRINTF(4, (CE_CONT, CONS "%s: %s: called", dp->name, __func__));
E 34
E 6
D 36
        /*
	 * Stop chip core
E 36
I 36

	/*
	 * Although we inhibit interrupt here, we don't clear soft copy of
	 * interrupt mask to avoid bogus interrupts.
E 36
	 */
D 26

E 26
D 36
	/* Inhibit interrupt */
I 34
#ifdef SANITY
E 34
I 4
D 10
#ifdef NOINTR_WORKAROUND
	lp->ier = 0;
#else
E 10
E 4
	OUTL(dp, IER, 0);
I 34
#endif
	lp->our_intr_bits = 0;
	OUTL(dp, IMR, lp->our_intr_bits);
E 36
I 36
	OUTL(dp, IMR, 0);
E 36
E 34
D 4

E 4
I 4
D 10
#endif
E 10
I 10

E 10
E 4
	/* stop TX and RX immediately */
	OUTL(dp, CR, lp->cr | CR_TXR | CR_RXR);
I 7

D 28
	i = 0;
E 28
	done = 0;
D 28
	while (done != (ISR_RXRCMP | ISR_TXRCMP)) {
		i++;
E 28
I 28
	for (i = 0; done != (ISR_RXRCMP | ISR_TXRCMP); i++) {
E 28
		if (i > 1000) {
I 36
			/*
			 * As gem layer will call sfe_reset_chip(),
			 * we don't neet to reset futher
			 */
E 36
D 29
			cmn_err(CE_NOTE,
D 28
				"%s: sfe_stop_chip: Tx/Rx reset timeout",
E 28
I 28
				"!%s: sfe_stop_chip: Tx/Rx reset timeout",
E 28
				dp->name);
			break;
E 29
I 29
			cmn_err(CE_NOTE, "!%s: %s: Tx/Rx reset timeout",
D 36
				dp->name, __func__);
E 36
I 36
			    dp->name, __func__);

E 36
			return (GEM_FAILURE);
E 29
		}
D 36
		done |= INL(dp, ISR) & (ISR_RXRCMP | ISR_TXRCMP);
E 36
I 36
		val = INL(dp, ISR);
		done |= val & (ISR_RXRCMP | ISR_TXRCMP);
		lp->isr_pended |= val & lp->our_intr_bits;
E 36
		drv_usecwait(10);
	}
I 29

	return (GEM_SUCCESS);
E 29
E 7
}

I 36
/*
 * Setup media mode
 */
static uint_t
sfe_mxdma_value[] = { 512, 4, 8, 16, 32, 64, 128, 256, };

static uint_t
sfe_encode_mxdma(uint_t burstsize)
{
	int	i;

	if (burstsize > 256) {
		/* choose 512 */
		return (0);
	}

	for (i = 1; i < 8; i++) {
		if (burstsize <= sfe_mxdma_value[i]) {
			break;
		}
	}
	return (i);
}

E 36
D 31
static void
E 31
I 31
static int
E 31
sfe_set_media(struct gem_dev *dp)
{
	uint32_t	txcfg;
	uint32_t	rxcfg;
	uint32_t	pcr;
I 7
D 34
	uint32_t	edb;
E 34
I 34
	uint32_t	val;
	uint32_t	txmxdma;
	uint32_t	rxmxdma;
E 34
E 7
D 36
	struct sfe_dev	*lp = (struct sfe_dev *)dp->private;
E 36
I 36
	struct sfe_dev	*lp = dp->private;
#ifdef DEBUG_LEVEL
E 36
I 24
D 29
#ifdef DEBUG_LEVEL
E 24
I 20
	static int	speed[3] = {10, 100, 1000};
E 20
D 24

E 24
I 24
#endif
E 24
I 12
	if (!dp->nic_active) {
		return;
	}
E 29
I 29
	extern int	gem_speed_value[];
E 29
D 36

E 36
I 36
#endif
E 36
E 12
D 6
	DPRINTF(2, (CE_CONT, "!%s: sfe_set_media: %s duplex, %d Mbps",
E 6
I 6
D 29
	DPRINTF(2, (CE_CONT, CONS "%s: sfe_set_media: %s duplex, %d Mbps",
E 6
		dp->name,
D 20
		dp->full_duplex?"full":"half", dp->speed100?100:10));
E 20
I 20
		dp->full_duplex?"full":"half", speed[dp->speed]));
E 29
I 29
	DPRINTF(2, (CE_CONT, CONS "%s: %s: %s duplex, %d Mbps",
D 36
		dp->name, __func__,
		dp->full_duplex ? "full" : "half", gem_speed_value[dp->speed]));
E 36
I 36
	    dp->name, __func__,
	    dp->full_duplex ? "full" : "half", gem_speed_value[dp->speed]));
E 36
E 29
E 20

I 7
D 34
	edb = 0;
E 34
I 34
D 36
	/* initialize txcfg and rxcfg*/
E 36
I 36
	/* initialize txcfg and rxcfg */
E 36
	txcfg = TXCFG_ATP;
	if (dp->full_duplex) {
		txcfg |= (TXCFG_CSI | TXCFG_HBI);
	}
D 36

	rxcfg =	RXCFG_AEP | RXCFG_ARP;
E 36
I 36
	rxcfg = RXCFG_AEP | RXCFG_ARP;
E 36
	if (dp->full_duplex) {
		rxcfg |= RXCFG_ATX;
	}

I 36
	/* select txmxdma and rxmxdma, maxmum burst length */
E 36
E 34
	if (lp->chip->chip_type == CHIPTYPE_SIS900) {
D 36
#ifdef SIS_EDB_TEST
E 36
I 36
#ifdef DEBUG_SIS900_EDB
E 36
D 34
		edb = CFG_EDB_MASTER_EN;
E 34
I 34
		val = CFG_EDB_MASTER;
E 34
#else
D 34
		edb = INL(dp, CFG) & CFG_EDB_MASTER_EN;
E 34
I 34
		val = INL(dp, CFG) & CFG_EDB_MASTER;
E 34
#endif
I 34
		if (val) {
I 36
			/*
			 * sis900 built-in cores:
			 * max burst length must be fixed to 64
			 */
E 36
			txmxdma = 64;
			rxmxdma = 64;
		} else {
I 36
			/*
			 * sis900 pci chipset:
			 * the vendor recommended to fix max burst length
			 * to 512
			 */
E 36
			txmxdma = 512;
			rxmxdma = 512;
		}
	} else {
D 36
		/* ns dp83815/816 */
		txmxdma = dp->txmaxdma;
		rxmxdma = dp->rxmaxdma;
E 36
I 36
		/*
		 * NS dp83815/816:
		 * use user defined or default for tx/rx max burst length
		 */
		txmxdma = max(dp->txmaxdma, 256);
		rxmxdma = max(dp->rxmaxdma, 256);
E 36
E 34
	}

I 31
D 34
#if 1
E 31
	/* tx low water mark */
I 31
	lp->tx_fill_threshold = dp->txmaxdma;
E 34
I 34
D 36
	/* encode txmxdma */
	if (txmxdma < 8) {
		txcfg |= TXCFG_MXDMA_4;
		txmxdma = 4;
	}
	else if (txmxdma < 16) {
		txcfg |= TXCFG_MXDMA_8;
		txmxdma = 8;
	}
	else if (txmxdma < 32) {
		txcfg |= TXCFG_MXDMA_16;
		txmxdma = 16;
	}
	else if (txmxdma < 64) {
		txcfg |= TXCFG_MXDMA_32;
		txmxdma = 32;
	}
	else if (txmxdma < 128) {
		txcfg |= TXCFG_MXDMA_64;
		txmxdma = 64;
	}
	else if (txmxdma < 256) {
		txcfg |= TXCFG_MXDMA_128;
		txmxdma = 128;
	}
	else if (txmxdma < 512) {
		txcfg |= TXCFG_MXDMA_256;
		txmxdma = 256;
	}
	else {
		txcfg |= TXCFG_MXDMA_512;
		txmxdma = 512;
	}
E 36
E 34

D 34
	/* high water marks */
	lp->tx_drain_threshold = dp->txthr;
E 34
I 34
D 36
	if (rxmxdma < 8) {
		rxcfg |= RXCFG_MXDMA_4;
		rxmxdma = 4;
	}
	else if (rxmxdma < 16) {
		rxcfg |= RXCFG_MXDMA_8;
		rxmxdma = 8;
	}
	else if (rxmxdma < 32) {
		rxcfg |= RXCFG_MXDMA_16;
		rxmxdma = 16;
	}
	else if (rxmxdma < 64) {
		rxcfg |= RXCFG_MXDMA_32;
		rxmxdma = 32;
	}
	else if (rxmxdma < 128) {
		rxcfg |= RXCFG_MXDMA_64;
		rxmxdma = 64;
	}
	else if (rxmxdma < 256) {
		rxcfg |= RXCFG_MXDMA_128;
		rxmxdma = 128;
	}
	else if (rxmxdma < 512) {
		rxcfg |= RXCFG_MXDMA_256;
		rxmxdma = 256;
	}
	else {
		rxcfg |= RXCFG_MXDMA_512;
		rxmxdma = 512;
	}
E 36
I 36
	/* tx high water mark */
	lp->tx_drain_threshold = ROUNDUP2(dp->txthr, TXCFG_FIFO_UNIT);
E 36
E 34

D 34
	/* receive starting threshold */
	lp->rx_drain_threshold = dp->rxthr;
#else
E 34
D 36
	/* tx low water mark */
E 31
E 7
D 34
	lp->tx_fill_threshold = TXFIFOSIZE / 4;			/* 1/4 FIFO */
E 34
I 34
	lp->tx_fill_threshold = txmxdma + TXCFG_FIFO_UNIT;
E 36
I 36
	/* determine tx_fill_threshold accroding drain threshold */
	lp->tx_fill_threshold =
	    TXFIFOSIZE - lp->tx_drain_threshold - TXCFG_FIFO_UNIT;
E 36
E 34
I 7

D 34
	/* high water marks */
E 7
D 20
	if (dp->speed100) {
E 20
I 20
	if (dp->speed == GEM_SPD_100) {
E 20
		/* transmit starting threshold */
D 7
		lp->tx_drain_threshold = (TXFIFOSIZE/4)*3;	/* 3/4 FIFO */
		lp->rx_drain_threshold = RXFIFOSIZE/2;		/* 2/4 FIFO */
E 7
I 7
		lp->tx_drain_threshold = (TXFIFOSIZE/4)*3;	/* S&F */
D 11
		/* receive starting threshold */
		lp->rx_drain_threshold = 128;
E 11
E 7
	} else {
		/* transmit starting threshold */
D 7
		lp->tx_drain_threshold = (TXFIFOSIZE/4);	/* 1/4 FIFO */
		lp->rx_drain_threshold = (RXFIFOSIZE/4)*3;	/* 3/4 FIFO */
E 7
I 7
		lp->tx_drain_threshold = (TXFIFOSIZE/4)*2;	/* 2/4 FIFO */
D 11
		/* receive starting threshold */
		lp->rx_drain_threshold = 192;
E 11
E 7
	}
E 34
I 34
D 36
	/* tx high water marks */
	lp->tx_drain_threshold = dp->txthr & ~(TXCFG_FIFO_UNIT - 1);
E 36
I 36
	/* tune txmxdma not to exceed tx_fill_threshold */
	for (; ; ) {
		/* normalize txmxdma requested */
		val = sfe_encode_mxdma(txmxdma);
		txmxdma = sfe_mxdma_value[val];
E 36
E 34
I 31

E 31
I 11
D 34
	/* receive starting threshold */
	lp->rx_drain_threshold = 128;
I 31
#endif
E 31
E 11

E 34
D 36
	/* fix tx_drain_theshold */
D 7
	if (lp->tx_drain_threshold >= TXFIFOSIZE - lp->tx_fill_threshold) {
E 7
I 7
D 24
	if (lp->tx_drain_threshold > TXFIFOSIZE - lp->tx_fill_threshold) {
E 7
		lp->tx_drain_threshold = TXFIFOSIZE - lp->tx_fill_threshold;
	}
E 24
I 24
	lp->tx_drain_threshold =
D 34
		min(lp->tx_drain_threshold, TXFIFOSIZE - lp->tx_fill_threshold);
E 34
I 34
		min(lp->tx_drain_threshold,
			TXFIFOSIZE - lp->tx_fill_threshold - TXCFG_FIFO_UNIT);
E 36
I 36
		if (txmxdma <= lp->tx_fill_threshold) {
			break;
		}
		/* select new txmxdma */
		txmxdma = txmxdma / 2;
	}
	txcfg |= val << TXCFG_MXDMA_SHIFT;
E 36
E 34

I 36
	/* encode rxmxdma, maxmum burst length for rx */
	val = sfe_encode_mxdma(rxmxdma);
	rxcfg |= val << RXCFG_MXDMA_SHIFT;
	rxmxdma = sfe_mxdma_value[val];

E 36
E 24
D 34
	/* fix rx_drain_theshold; it have only 5bit-wide field */
E 34
I 34
	/* receive starting threshold - it have only 5bit-wide field */
D 36
	val = ROUNDUP2(dp->rxthr, RXCFG_FIFO_UNIT);
E 36
I 36
	val = ROUNDUP2(max(dp->rxthr, ETHERMIN), RXCFG_FIFO_UNIT);
E 36
E 34
D 24
	if (lp->rx_drain_threshold > 31 * RXCFG_DRTH_UNIT) {
		lp->rx_drain_threshold = 31 * RXCFG_DRTH_UNIT;
	}
E 24
I 24
	lp->rx_drain_threshold =
D 34
		min(lp->rx_drain_threshold, 31 * RXCFG_DRTH_UNIT);
E 34
I 34
D 36
		min(val, (RXCFG_DRTH >> RXCFG_DRTH_SHIFT) * RXCFG_FIFO_UNIT);
E 36
I 36
	    min(val, (RXCFG_DRTH >> RXCFG_DRTH_SHIFT) * RXCFG_FIFO_UNIT);
E 36
E 34

E 24
D 34
	ASSERT(lp->tx_drain_threshold < 64*TXCFG_DRTH_UNIT);
	ASSERT(lp->tx_fill_threshold < 64*TXCFG_FLTH_UNIT);
	ASSERT(lp->rx_drain_threshold < 32*RXCFG_DRTH_UNIT);
E 34
I 34
	DPRINTF(0, (CE_CONT,
D 36
		"%s: %s: tx: drain:%d fill:%d mxdma:%d, rx: drain:%d mxdma:%d",
		dp->name, __func__,
		TXFIFOSIZE - lp->tx_drain_threshold,
		lp->tx_fill_threshold, txmxdma,
		lp->rx_drain_threshold, rxmxdma));
E 36
I 36
	    CONS "%s: %s: tx: drain:%d(rest %d) fill:%d mxdma:%d,"
	    " rx: drain:%d mxdma:%d",
	    dp->name, __func__,
	    lp->tx_drain_threshold, TXFIFOSIZE - lp->tx_drain_threshold,
	    lp->tx_fill_threshold, txmxdma,
	    lp->rx_drain_threshold, rxmxdma));
E 36
E 34

D 34
	txcfg =	TXCFG_ATP |		/* auto padding */
D 7
		TXCFG_MXDMA_512 |	/* MAX DMA burst size */
E 7
I 7
		(edb ? TXCFG_MXDMA_64 : TXCFG_MXDMA_512) |
E 7
		(dp->full_duplex ? (TXCFG_CSI | TXCFG_HBI) : 0) |
		(lp->tx_fill_threshold/TXCFG_FLTH_UNIT) << TXCFG_FLTH_SHIFT |
		lp->tx_drain_threshold/TXCFG_DRTH_UNIT;
E 34
I 34
	ASSERT(lp->tx_drain_threshold < 64*TXCFG_FIFO_UNIT);
	ASSERT(lp->tx_fill_threshold < 64*TXCFG_FIFO_UNIT);
	ASSERT(lp->rx_drain_threshold < 32*RXCFG_FIFO_UNIT);

	txcfg |= ((lp->tx_fill_threshold/TXCFG_FIFO_UNIT) << TXCFG_FLTH_SHIFT)
D 36
	      |  (lp->tx_drain_threshold/TXCFG_FIFO_UNIT);
E 36
I 36
	    | (lp->tx_drain_threshold/TXCFG_FIFO_UNIT);
E 36
E 34
	OUTL(dp, TXCFG, txcfg);

D 34
	rxcfg =	RXCFG_AEP | RXCFG_ARP |
		(dp->full_duplex ? RXCFG_ATX : 0) |
D 7
		RXCFG_MXDMA_512 |
E 7
I 7
		(edb ? RXCFG_MXDMA_64 : RXCFG_MXDMA_512) |
E 7
D 29
		(lp->rx_drain_threshold/RXCFG_DRTH_UNIT) << RXCFG_DRTH_SHIFT;
E 29
I 29
		((lp->rx_drain_threshold/RXCFG_DRTH_UNIT) << RXCFG_DRTH_SHIFT);
E 34
I 34
	rxcfg |= ((lp->rx_drain_threshold/RXCFG_FIFO_UNIT) << RXCFG_DRTH_SHIFT);
E 34
I 31
D 36
#ifdef GEM_CONFIG_VLAN
E 36
	if (lp->chip->chip_type == CHIPTYPE_DP83815) {
		rxcfg |= RXCFG_ALP_DP83815;
	}
D 36
#endif
E 36
E 31
E 29
	OUTL(dp, RXCFG, rxcfg);

D 6
	DPRINTF(2, (CE_CONT, "!%s: sfe_set_media: txcfg:%b rxcfg:%b",
E 6
I 6
D 7
	DPRINTF(2, (CE_CONT, CONS "%s: sfe_set_media: txcfg:%b rxcfg:%b",
E 7
I 7
D 29
	DPRINTF(0, (CE_CONT, CONS "%s: sfe_set_media: txcfg:%b rxcfg:%b",
E 7
E 6
		dp->name,
E 29
I 29
	DPRINTF(0, (CE_CONT, CONS "%s: %s: txcfg:%b rxcfg:%b",
D 36
		dp->name, __func__,
E 29
		txcfg, TXCFG_BITS, rxcfg, RXCFG_BITS));
E 36
I 36
	    dp->name, __func__,
	    txcfg, TXCFG_BITS, rxcfg, RXCFG_BITS));
E 36

	/* Flow control */
	if (lp->chip->chip_type == CHIPTYPE_DP83815) {
		pcr = INL(dp, PCR);
D 34
		if (dp->flow_control) {
E 34
I 34
		switch (dp->flow_control) {
		case FLOW_CONTROL_SYMMETRIC:
		case FLOW_CONTROL_RX_PAUSE:
E 34
			OUTL(dp, PCR, pcr | PCR_PSEN | PCR_PS_MCAST);
D 34
		}
		else {
E 34
I 34
			break;

		default:
E 34
			OUTL(dp, PCR,
D 36
				pcr & ~(PCR_PSEN | PCR_PS_MCAST | PCR_PS_DA));
E 36
I 36
			    pcr & ~(PCR_PSEN | PCR_PS_MCAST | PCR_PS_DA));
E 36
I 34
			break;
E 34
		}
D 6
		DPRINTF(2, (CE_CONT,
			"!%s: PCR: %b", dp->name, INL(dp, PCR), PCR_BITS));
E 6
I 6
		DPRINTF(2, (CE_CONT, CONS "%s: PCR: %b", dp->name,
D 36
				INL(dp, PCR), PCR_BITS));
E 6
	}
	else if (lp->chip->chip_type == CHIPTYPE_SIS900) {
 
E 36
I 36
		    INL(dp, PCR), PCR_BITS));

	} else if (lp->chip->chip_type == CHIPTYPE_SIS900) {
E 36
D 34
		if (dp->flow_control) {
E 34
I 34
		switch (dp->flow_control) {
		case FLOW_CONTROL_SYMMETRIC:
		case FLOW_CONTROL_RX_PAUSE:
E 34
			OUTL(dp, FLOWCTL, FLOWCTL_FLOWEN);
D 34
		}
		else {
E 34
I 34
			break;
D 36

E 36
		default:
E 34
			OUTL(dp, FLOWCTL, 0);
I 34
			break;
E 34
		}
D 6
		DPRINTF(2, (CE_CONT, "!%s: FLOWCTL: %b",
E 6
I 6
		DPRINTF(2, (CE_CONT, CONS "%s: FLOWCTL: %b",
E 6
D 36
			dp->name, INL(dp, FLOWCTL), FLOWCTL_BITS));
E 36
I 36
		    dp->name, INL(dp, FLOWCTL), FLOWCTL_BITS));
E 36
	}
I 31
D 36

E 36
	return (GEM_SUCCESS);
E 31
}

D 31
static void
E 31
I 31
static int
E 31
sfe_get_stats(struct gem_dev *dp)
{
	/* do nothing */
I 31
	return (GEM_SUCCESS);
E 31
}

/*
D 36
 * discriptor  manupiration
E 36
I 36
 * descriptor manipulations
E 36
 */
static int
D 29
sfe_tx_desc_write(struct gem_dev *dp, uint_t slot,
D 9
		ddi_dma_cookie_t *dmacookie, int frags, boolean_t intreq)
E 9
I 9
		ddi_dma_cookie_t *dmacookie, int frags, uint32_t intreq)
E 29
I 29
sfe_tx_desc_write(struct gem_dev *dp, int slot,
D 34
		ddi_dma_cookie_t *dmacookie, int frags, uint32_t flags)
E 34
I 34
		ddi_dma_cookie_t *dmacookie, int frags, uint64_t flags)
E 34
E 29
E 9
{
D 36
	int			n;
E 36
I 9
	uint32_t		mark;
E 9
	struct sfe_desc		*tdp;
	ddi_dma_cookie_t	*dcp;
D 36
	struct sfe_dev		*lp = (struct sfe_dev *)dp->private;
I 26
D 29
	ddi_acc_handle_t	h = dp->desc_acc_handle;
E 29
I 29
	uint32_t		offset;
E 29
E 26
D 34
#if DEBUG_LEVEL > 2
E 34
I 34
#if DEBUG_LEVEL > 1
E 36
I 36
	uint32_t		tmp0;
	int			n;
	int			offset;
#if DEBUG_LEVEL > 2
E 36
E 34
	int			i;

	cmn_err(CE_CONT,
D 6
	"%s: sfe_tx_desc_write seqnum: %d, slot %d, frags: %d intreq: %d",
E 6
I 6
D 7
	CONS "%s: sfe_tx_desc_write seqnum: %d, slot %d, frags: %d intreq: %d",
E 6
		dp->name, dp->tx_desc_tail, slot, frags, intreq);
E 7
I 7
D 29
CONS "%s: time:%d sfe_tx_desc_write seqnum: %d, slot %d, frags: %d intreq: %d",
		dp->name, ddi_get_lbolt(),
		dp->tx_desc_tail, slot, frags, intreq);
E 29
I 29
D 34
		CONS "%s: time:%d %s seqnum: %d, slot %d, frags: %d flags: %d",
E 34
I 34
D 36
	     CONS "%s: time:%d %s seqnum: %d, slot %d, frags: %d flags: %llx",
E 34
		dp->name, ddi_get_lbolt(), __func__,
		dp->tx_desc_tail, slot, frags, flags);
E 36
I 36
	    CONS "%s: time:%d %s seqnum: %d, slot %d, frags: %d flags: %llx",
	    dp->name, ddi_get_lbolt(), __func__,
	    dp->tx_desc_tail, slot, frags, flags);
E 36
E 29
E 7

	for (i = 0; i < frags; i++) {
D 6
		cmn_err(CE_CONT, "%d: addr: 0x%x, len: 0x%x",
E 6
I 6
		cmn_err(CE_CONT, CONS "%d: addr: 0x%x, len: 0x%x",
E 6
D 36
			i, dmacookie[i].dmac_address, dmacookie[i].dmac_size);
E 36
I 36
		    i, dmacookie[i].dmac_address, dmacookie[i].dmac_size);
E 36
	}
#endif
	/*
	 * write tx descriptor in reversed order.
	 */
D 9

	/* make the slot for the last fragment of the packet */
	n = frags - 1;
	tdp = &((struct sfe_desc *)dp->tx_ring)[
			SLOT(slot + n, TX_RING_SIZE)];
	dcp = &dmacookie[n];
E 9
D 7

E 7
I 7
#if DEBUG_LEVEL > 3
D 24
	intreq = TRUE;
E 24
I 24
D 29
	intreq |= GEM_TXFLAG_INTR;
E 29
I 29
	flags |= GEM_TXFLAG_INTR;
E 29
E 24
#endif
E 7
D 9
	tdp->d_bufptr = (uint32_t)dcp->dmac_address;
	tdp->d_cmdsts = ((uint32_t)dcp->dmac_size) | CMDSTS_OWN
			| (intreq ? CMDSTS_INTR : 0);
I 7
#ifdef IOCACHE
	ddi_dma_sync(dp->desc_dma_handle,
		(off_t)(((caddr_t)tdp) - dp->rx_ring),
		sizeof(struct sfe_desc), DDI_DMA_SYNC_FORDEV);
#endif
E 7

E 9
I 9
D 24
	mark = (intreq != 0) ? (CMDSTS_OWN | CMDSTS_INTR) : (CMDSTS_OWN);
E 24
I 24
D 29
	mark = ((intreq & GEM_TXFLAG_INTR) != 0)
E 29
I 29
D 34
	mark = ((flags & GEM_TXFLAG_INTR) != 0)
E 34
I 34
	mark = (flags & GEM_TXFLAG_INTR)
E 34
E 29
D 36
			? (CMDSTS_OWN | CMDSTS_INTR) : CMDSTS_OWN;
E 36
I 36
	    ? (CMDSTS_OWN | CMDSTS_INTR) : CMDSTS_OWN;
E 36
E 24
D 29
	dcp = &dmacookie[frags];
	n = frags;
E 9
	while (n--) {
E 29
I 29

	dcp = &dmacookie[frags - 1];
	for (n = frags - 1; n > 0; n--) {
E 29
D 24
		/* slot for n-th fragment */
E 24
I 24
		/* make a slot for n-th fragment */
I 29
		offset = SFE_DESC_SIZE * SLOT(slot + n, TX_RING_SIZE);
		tdp = (struct sfe_desc *) &dp->tx_ring[offset];
D 34
		tdp->d_bufptr = LE32((uint32_t) dcp->dmac_address);
D 31
		tdp->d_cmdsts = LE32(mark | (uint32_t)dcp->dmac_size);
E 31
I 31
		tdp->d_cmdsts = LE32(mark | (uint32_t) dcp->dmac_size);
E 34
I 34
		tdp->d_bufptr = LE_32((uint32_t) dcp->dmac_address);
		tdp->d_cmdsts = LE_32(mark | (uint32_t) dcp->dmac_size);
E 34
E 31

		mark = CMDSTS_OWN | CMDSTS_MORE;
E 29
E 24
		dcp--;
D 9

E 9
D 29
		tdp = &((struct sfe_desc *)dp->tx_ring)[
				SLOT(slot + n, TX_RING_SIZE)];
E 29
I 29
	}
E 29

D 24
		tdp->d_bufptr = (uint32_t)dcp->dmac_address;
D 9
		tdp->d_cmdsts = ((uint32_t)dcp->dmac_size)
				| CMDSTS_OWN | CMDSTS_MORE;
E 9
I 9
		tdp->d_cmdsts = mark | (uint32_t)dcp->dmac_size;
E 24
I 24
D 26
		tdp->d_bufptr = LE32((uint32_t)dcp->dmac_address);
		tdp->d_cmdsts = LE32(mark | (uint32_t)dcp->dmac_size);
E 26
I 26
D 29
		ddi_put32(h, &tdp->d_bufptr, (uint32_t)dcp->dmac_address);
		ddi_put32(h, &tdp->d_cmdsts, mark | (uint32_t)dcp->dmac_size);
E 29
I 29
D 34
	if ((flags & GEM_TXFLAG_HEAD) != 0) {
E 34
I 34
	if (flags & GEM_TXFLAG_HEAD) {
E 34
		mark &= ~CMDSTS_OWN;
	}
E 29
E 26
E 24
E 9
I 7
D 23
#ifdef IOCACHE
E 23
I 23

E 23
D 29
		ddi_dma_sync(dp->desc_dma_handle,
			(off_t)(((caddr_t)tdp) - dp->rx_ring),
			sizeof(struct sfe_desc), DDI_DMA_SYNC_FORDEV);
E 29
I 29
D 36
	tdp = (struct sfe_desc *) &dp->tx_ring[SFE_DESC_SIZE * slot];
D 34
	tdp->d_bufptr = LE32((uint32_t) dcp->dmac_address);
D 31
	tdp->d_cmdsts = LE32(mark | (uint32_t)dcp->dmac_size);
E 31
I 31
	tdp->d_cmdsts = LE32(mark | (uint32_t) dcp->dmac_size);
E 34
I 34
	tdp->d_bufptr = LE_32((uint32_t) dcp->dmac_address);
	tdp->d_cmdsts = LE_32(mark | (uint32_t) dcp->dmac_size);
E 36
I 36
	tdp = (void *)&dp->tx_ring[SFE_DESC_SIZE * slot];
	tmp0 = (uint32_t)dcp->dmac_address;
	mark |= (uint32_t)dcp->dmac_size;
	tdp->d_bufptr = LE_32(tmp0);
	tdp->d_cmdsts = LE_32(mark);
E 36
E 34
E 31
E 29
D 23
#endif
E 23
I 23

E 23
I 9
D 29
		mark = CMDSTS_OWN | CMDSTS_MORE;
E 29
I 29
D 30
	eturn (frags);
E 30
I 30
	return (frags);
E 30
}

static void
sfe_tx_start(struct gem_dev *dp, int start_slot, int nslot)
{
I 36
	uint_t			tx_ring_size = dp->gc.gc_tx_ring_size;
E 36
	struct sfe_desc		*tdp;
D 36
	struct sfe_dev		*lp = (struct sfe_dev *)dp->private;
E 36
I 36
	struct sfe_dev		*lp = dp->private;
E 36

	if (nslot > 1) {
		gem_tx_desc_dma_sync(dp,
D 36
				SLOT(start_slot + 1, TX_RING_SIZE),
				nslot - 1, DDI_DMA_SYNC_FORDEV);
E 36
I 36
		    SLOT(start_slot + 1, tx_ring_size),
		    nslot - 1, DDI_DMA_SYNC_FORDEV);
E 36
E 29
E 9
E 7
	}

I 29
D 36
	tdp = ((struct sfe_desc *) &dp->tx_ring[SFE_DESC_SIZE * start_slot]);
E 36
I 36
	tdp = (void *)&dp->tx_ring[SFE_DESC_SIZE * start_slot];
E 36
D 34
	tdp->d_cmdsts |= LE32(CMDSTS_OWN);
E 34
I 34
	tdp->d_cmdsts |= LE_32(CMDSTS_OWN);
E 34

	gem_tx_desc_dma_sync(dp, start_slot, 1, DDI_DMA_SYNC_FORDEV);

E 29
	/*
D 24
	 * Let the Transmit Buffer Manager Fill state machine active
E 24
I 24
	 * Let the Transmit Buffer Manager Fill state machine active.
E 24
	 */
I 7
D 18
#ifdef DEBUG_LEVEL
	lp->tx_setup_time[slot] = ddi_get_lbolt();
#endif
E 18
E 7
D 29
	OUTL(dp, CR, lp->cr | CR_TXE);

	return frags;
E 29
I 29
	if (dp->mac_active) {
		OUTL(dp, CR, lp->cr | CR_TXE);
	}
E 29
}

D 29
static int
sfe_rx_desc_write(struct gem_dev *dp, uint_t slot,
E 29
I 29
static void
sfe_rx_desc_write(struct gem_dev *dp, int slot,
E 29
	    ddi_dma_cookie_t *dmacookie, int frags)
{
	struct sfe_desc		*rdp;
D 11
	ddi_dma_cookie_t	*dcp = dmacookie;
E 11
I 4
D 36
	struct sfe_dev		*lp = (struct sfe_dev *)dp->private;
I 26
	ddi_acc_handle_t	h = dp->desc_acc_handle;
E 36
I 36
	uint32_t		tmp0;
	uint32_t		tmp1;
E 36
E 26
E 4
#if DEBUG_LEVEL > 2
	int			i;

	ASSERT(frags == 1);

D 6
	cmn_err(CE_CONT, "%s: sfe_rx_desc_write seqnum: %d, slot %d, frags: %d",
E 6
I 6
	cmn_err(CE_CONT, CONS
D 34
		"%s: sfe_rx_desc_write seqnum: %d, slot %d, frags: %d",
E 6
D 29
		dp->name, dp->rx_desc_tail, slot, frags);
E 29
I 29
		dp->name, dp->rx_active_tail, slot, frags);
E 34
I 34
D 36
		"%s: %s seqnum: %d, slot %d, frags: %d",
		dp->name, __func__, dp->rx_active_tail, slot, frags);
E 36
I 36
	    "%s: %s seqnum: %d, slot %d, frags: %d",
	    dp->name, __func__, dp->rx_active_tail, slot, frags);
E 36
E 34
E 29
	for (i = 0; i < frags; i++) {
D 6
		cmn_err(CE_CONT, "  frag: %d addr: 0x%x, len: 0x%x",
E 6
I 6
D 36
		cmn_err(CE_CONT, CONS "  frag: %d addr: 0x%x, len: 0x%x",
E 6
			i, dmacookie[i].dmac_address, dmacookie[i].dmac_size);
E 36
I 36
		cmn_err(CE_CONT, CONS "  frag: %d addr: 0x%llx, len: 0x%lx",
		    i, dmacookie[i].dmac_address, dmacookie[i].dmac_size);
E 36
	}
#endif
	/* for the last slot of the packet */
D 29
	rdp = &((struct sfe_desc *)dp->rx_ring)[slot];
E 29
I 29
D 36
	rdp = (struct sfe_desc *) &dp->rx_ring[SFE_DESC_SIZE * slot];
E 36
I 36
	rdp = (void *)&dp->rx_ring[SFE_DESC_SIZE * slot];
E 36
E 29

D 11
	rdp->d_bufptr = (uint32_t)dcp->dmac_address;
	rdp->d_cmdsts = (uint32_t)dcp->dmac_size;
E 11
I 11
D 24
	rdp->d_bufptr = (uint32_t)dmacookie->dmac_address;
	rdp->d_cmdsts = CMDSTS_INTR | (uint32_t)dmacookie->dmac_size;
E 24
I 24
D 26
	rdp->d_bufptr = LE32((uint32_t)dmacookie->dmac_address);
	rdp->d_cmdsts = LE32(CMDSTS_INTR | (uint32_t)dmacookie->dmac_size);
E 26
I 26
D 29
	ddi_put32(h, &rdp->d_bufptr, (uint32_t)dmacookie->dmac_address);
	ddi_put32(h, &rdp->d_cmdsts,
				CMDSTS_INTR | (uint32_t)dmacookie->dmac_size);
E 26
E 24
E 11
D 7

I 4
	OUTL(dp, CR, lp->cr | CR_RXE);

E 7
I 7
D 23
#ifdef IOCACHE
E 23
I 23

E 23
	ddi_dma_sync(dp->desc_dma_handle,
		(off_t)(((caddr_t)rdp) - dp->rx_ring),
		sizeof(struct sfe_desc), DDI_DMA_SYNC_FORDEV);
D 23
#endif
E 23
I 23

E 23
I 11
D 16
#ifdef notdef
E 11
	if (dp->nic_active) {
		OUTL(dp, CR, lp->cr | CR_RXE);
	}
I 11
#endif
E 16
E 11
E 7
E 4
	return 1;
E 29
I 29
D 31
	rdp->d_bufptr = LE32((uint32_t)dmacookie->dmac_address);
	rdp->d_cmdsts = LE32(CMDSTS_INTR | (uint32_t)dmacookie->dmac_size);
E 31
I 31
D 34
	rdp->d_bufptr = LE32((uint32_t) dmacookie->dmac_address);
	rdp->d_cmdsts = LE32(CMDSTS_INTR | (uint32_t) dmacookie->dmac_size);
E 34
I 34
D 36
	rdp->d_bufptr = LE_32((uint32_t) dmacookie->dmac_address);
	rdp->d_cmdsts = LE_32(CMDSTS_INTR | (uint32_t) dmacookie->dmac_size);
E 36
I 36
	tmp0 = (uint32_t)dmacookie->dmac_address;
	tmp1 = CMDSTS_INTR | (uint32_t)dmacookie->dmac_size;
	rdp->d_bufptr = LE_32(tmp0);
	rdp->d_cmdsts = LE_32(tmp1);
E 36
E 34
E 31
E 29
}

static uint_t
sfe_tx_desc_stat(struct gem_dev *dp, int slot, int ndesc)
{
I 36
	uint_t			tx_ring_size = dp->gc.gc_tx_ring_size;
E 36
	struct sfe_desc		*tdp;
	uint32_t		status;
D 36
	int			i;
E 36
	int			cols;
I 26
D 36
	ddi_acc_handle_t	h = dp->desc_acc_handle;
E 36
I 36
	struct sfe_dev		*lp = dp->private;
E 36
E 26
D 7

E 7
I 7
#ifdef DEBUG_LEVEL
D 36
	struct sfe_dev		*lp = (struct sfe_dev *)dp->private;
E 36
I 36
	int			i;
E 36
	clock_t			delay;
#endif
E 7
	/* check status of the last descriptor */
D 29
	tdp = &((struct sfe_desc *)dp->tx_ring)[
		SLOT(slot + ndesc - 1, TX_RING_SIZE)];
E 29
I 29
D 36
	tdp = (struct sfe_desc *)
	  &dp->tx_ring[SFE_DESC_SIZE * SLOT(slot + ndesc - 1, TX_RING_SIZE)];
E 36
I 36
	tdp = (void *)
	    &dp->tx_ring[SFE_DESC_SIZE * SLOT(slot + ndesc - 1, tx_ring_size)];
E 36
E 29
D 7

E 7
I 7
D 23
#ifdef IOCACHE
E 23
I 23

E 23
D 29
	ddi_dma_sync(dp->desc_dma_handle,
		(off_t)(((caddr_t)tdp) - dp->rx_ring),
		sizeof(struct sfe_desc), DDI_DMA_SYNC_FORKERNEL);
E 29
I 29
D 34
	status = LE32(tdp->d_cmdsts);
E 34
I 34
D 36
	status = LE_32(tdp->d_cmdsts);
E 36
I 36
	/*
	 * Don't use LE_32() directly to refer tdp->d_cmdsts.
	 * It is not atomic for big endian cpus.
	 */
	status = tdp->d_cmdsts;
	status = LE_32(status);
E 36
E 34
E 29
D 23
#endif
E 23
I 23

E 23
E 7
D 24
	status = tdp->d_cmdsts;
E 24
I 24
D 26
	status = LE32(tdp->d_cmdsts);
E 26
I 26
D 29
	status = ddi_get32(h, &tdp->d_cmdsts);
E 26
E 24

E 29
D 34
	DPRINTF(2, (CE_CONT,
D 6
		"%s: sfe_tx_desc_stat: slot:%d, status:0x%b",
E 6
I 6
D 7
		CONS "%s: sfe_tx_desc_stat: slot:%d, status:0x%b",
E 6
		dp->name, slot, status, TXSTAT_BITS));
E 7
I 7
		CONS "%s: time:%d sfe_tx_desc_stat: slot:%d, status:0x%b",
		dp->name, ddi_get_lbolt(), slot, status, TXSTAT_BITS));
E 34
I 34
D 35
	DPRINTF(2, (CE_CONT, CONS "%s: time:%d %s: slot:%d, status:0x%b",
E 35
I 35
	DPRINTF(2, (CE_CONT, CONS "%s: time:%ld %s: slot:%d, status:0x%b",
E 35
D 36
		dp->name, ddi_get_lbolt(), __func__,
		slot, status, TXSTAT_BITS));
E 36
I 36
	    dp->name, ddi_get_lbolt(), __func__,
	    slot, status, TXSTAT_BITS));
E 36
E 34
E 7

D 34
	if ((status & CMDSTS_OWN) != 0) {
E 34
I 34
	if (status & CMDSTS_OWN) {
E 34
		/*
		 * not yet transmitted
		 */
I 36
		/* workaround for tx hang */
		if (lp->chip->chip_type == CHIPTYPE_DP83815 &&
		    dp->mac_active) {
			OUTL(dp, CR, lp->cr | CR_TXE);
		}
E 36
D 29
		return 0;
E 29
I 29
		return (0);
E 29
	}
D 34
	ASSERT((status & CMDSTS_MORE) == 0);
E 34

I 34
	if (status & CMDSTS_MORE) {
		/* XXX - the hardware problem but don't panic the system */
I 36
		/* avoid lint bug for %b format string including 32nd bit */
E 36
		cmn_err(CE_NOTE, CONS
D 36
			"%s: tx status bits incorrect:  slot:%d, status:0x%b",
			dp->name, slot, status, TXSTAT_BITS);
E 36
I 36
		    "%s: tx status bits incorrect:  slot:%d, status:0x%x",
		    dp->name, slot, status);
E 36
	}

E 34
I 7
#if DEBUG_LEVEL > 3
D 18
	delay = (ddi_get_lbolt() - lp->tx_setup_time[slot]) * 10;
E 18
I 18
	delay = (ddi_get_lbolt() - dp->tx_buf_head->txb_stime) * 10;
E 18
	if (delay >= 50) {
		DPRINTF(0, (CE_NOTE, "%s: tx deferred %d mS: slot %d",
D 36
			dp->name, delay, slot));
E 36
I 36
		    dp->name, delay, slot));
E 36
	}
#endif

E 7
D 24
#if DEBUG_LEVEL > 1
E 24
I 24
#if DEBUG_LEVEL > 3
E 24
D 29
	for (i = 0; i < ndesc-1; i++) {
E 29
I 29
	for (i = 0; i < nfrag-1; i++) {
E 29
		uint32_t	s;
		int		n;

D 36
		n = SLOT(slot + i, TX_RING_SIZE);
E 36
I 36
		n = SLOT(slot + i, tx_ring_size);
E 36
D 26
		s = ((struct sfe_desc *)dp->tx_ring)[n].d_cmdsts;
E 26
I 26
D 29
		s = ddi_get32(h, &((struct sfe_desc *)dp->tx_ring)[n].d_cmdsts);
E 29
I 29
D 34
		s = LE32(
E 34
I 34
		s = LE_32(
E 34
D 36
		((struct sfe_desc *)&dp->tx_ring[SFE_DESC_SIZE * n])->d_cmdsts);
E 29
E 26
		
E 36
I 36
		    ((struct sfe_desc *)((void *)
		    &dp->tx_ring[SFE_DESC_SIZE * n]))->d_cmdsts);

E 36
D 34
		ASSERT((s & CMDSTS_MORE) != 0);
E 34
I 34
		ASSERT(s & CMDSTS_MORE);
E 34
		ASSERT((s & CMDSTS_OWN) == 0);
	}
#endif

	/*
D 36
	 *  collect statictics
E 36
I 36
	 *  collect statistics
E 36
	 */
	if ((status & CMDSTS_OK) == 0) {

		/* failed to transmit the packet */

D 6
		DPRINTF(2, (CE_CONT, "%s: Transmit error, Tx status %b",
E 6
I 6
D 34
		DPRINTF(2, (CE_CONT, CONS "%s: Transmit error, Tx status %b",
E 34
I 34
		DPRINTF(0, (CE_CONT, CONS "%s: Transmit error, Tx status %b",
E 34
E 6
D 36
			       dp->name, status, TXSTAT_BITS));
E 36
I 36
		    dp->name, status, TXSTAT_BITS));
E 36

		dp->stats.errxmt++;

		if (status & CMDSTS_TFU) {
			dp->stats.underflow++;
D 36
		}
D 34
		if (status & CMDSTS_CRS) {
E 34
I 34
		else if (status & CMDSTS_CRS) {
E 36
I 36
		} else if (status & CMDSTS_CRS) {
E 36
E 34
			dp->stats.nocarrier++;
D 36
		}
D 34
		if (status & CMDSTS_OWC) {
E 34
I 34
		else if (status & CMDSTS_OWC) {
E 36
I 36
		} else if (status & CMDSTS_OWC) {
E 36
E 34
			dp->stats.xmtlatecoll++;
D 36
		}
D 34
		if (!dp->full_duplex) {
			if (status & CMDSTS_EC) {
				dp->stats.excoll++;
				dp->stats.collisions += 16;
			}
E 34
I 34
		else if ((!dp->full_duplex) && (status & CMDSTS_EC)) {
E 36
I 36
		} else if ((!dp->full_duplex) && (status & CMDSTS_EC)) {
E 36
			dp->stats.excoll++;
			dp->stats.collisions += 16;
E 34
D 36
		}
I 34
		else {
E 36
I 36
		} else {
E 36
			dp->stats.xmit_internal_err++;
		}
E 34
D 36
	}
	else if (!dp->full_duplex) {

E 36
I 36
	} else if (!dp->full_duplex) {
E 36
		cols = (status >> CMDSTS_CCNT_SHIFT) & CCNT_MASK;

		if (cols > 0) {
			if (cols == 1) {
				dp->stats.first_coll++;
			} else /* (cols > 1) */ {
				dp->stats.multi_coll++;
			}
			dp->stats.collisions += cols;
D 36
		}
D 34
		else if ((status & CMDSTS_TD) != 0) {
E 34
I 34
		else if (status & CMDSTS_TD) {
E 36
I 36
		} else if (status & CMDSTS_TD) {
E 36
E 34
			dp->stats.defer++;
		}
	}
D 36

E 36
D 29
	return GEM_TX_DONE;
E 29
I 29
	return (GEM_TX_DONE);
E 29
}

D 36
static void
sfe_pause_received(struct gem_dev *dp, uint8_t *bp)
{
	uint16_t	type_len;
	uint16_t	pause_flag;
	uint16_t	pause_time;
	uint32_t	val;
	struct sfe_dev	*lp = (struct sfe_dev *)dp->private;

	type_len = ntohs(((struct pause_frame *)bp)->type_len);
	pause_flag = ntohs(((struct pause_frame *)bp)->pause_flag);
	pause_time = ntohs(((struct pause_frame *)bp)->pause_time);

	DPRINTF(2, (CE_CONT,
D 6
		"%s: pause packet received: src:%02x:%02x:%02x:%02x:%02x:%02x "
E 6
I 6
	   CONS "%s: pause packet received: src:%02x:%02x:%02x:%02x:%02x:%02x "
E 6
		"type:0x%04x flag:0x%04x time:0x%04x",
		dp->name, bp[6], bp[7], bp[8], bp[9], bp[10], bp[11],
		type_len, pause_flag, pause_time));

	if (lp->chip->chip_type == CHIPTYPE_DP83815) {
		/*
D 24
		 * It seems that DP83815 does not pause automatically
E 24
I 24
		 * It seems that DP83815 doesn't pause tx automatically
E 24
		 * when it receives a IEEE 802.3x pause frame.
		 * For a workaround, we pause transmition manually.
D 7
		 * Is it right ? But it works.
E 7
I 7
D 31
		 * Is it right? But it seems to work.
E 31
I 31
		 * It seems to work practically, but is it right.
E 31
E 7
		 */
		switch (pause_flag) {
		case 1:
			if (pause_time == 0) {
				/* release HW */
				/* cancel pause */
				val = INL(dp, PCR);
				OUTL(dp, PCR, val & ~PCR_PSEN);
				drv_usecwait(1);
				/* restore PCR */
				OUTL(dp, PCR, val);
			}
			else {
				/* issue pause command */
				val = INL(dp, PCR);
				if ((val & (PCR_PS_RCVD | PCR_PS_ACT)) == 0) {
					val &= ~PCR_PAUSE_CNT;
					val |=  pause_time | PCR_MLD_EN;
					OUTL(dp, PCR, val);
				}
			}
			break;

		default:
D 6
			cmn_err(CE_NOTE,
E 6
I 6
			cmn_err(CE_NOTE, CONS
E 6
				"%s: unknown mac control frame: flag:%d",
				dp->name, pause_flag);
			break;
		}
	}
}

E 36
D 28
static uint_t
E 28
I 28
static uint64_t
E 28
sfe_rx_desc_stat(struct gem_dev *dp, int slot, int ndesc)
{
D 26
	struct sfe_desc	*rdp;
	uint_t		len;
	uint_t		flag;
	uint32_t	status;
E 26
I 26
	struct sfe_desc		*rdp;
	uint_t			len;
	uint_t			flag;
	uint32_t		status;
D 29
	ddi_acc_handle_t	h = dp->desc_acc_handle;
E 29
E 26

	flag = GEM_RX_DONE;

D 7
	/* We cannot ack only to rx interrupt. */
E 7
I 7
	/* Dont read ISR because we cannot ack only to rx interrupt. */
E 7

D 29
	rdp = &((struct sfe_desc *)dp->rx_ring)[slot];
E 29
I 29
D 36
	rdp = (struct sfe_desc *) &dp->rx_ring[SFE_DESC_SIZE * slot];
E 36
I 36
	rdp = (void *)&dp->rx_ring[SFE_DESC_SIZE * slot];
E 36
E 29
I 7
D 23
#ifdef IOCACHE
E 23
I 23

E 23
D 29
	ddi_dma_sync(dp->desc_dma_handle,
		(off_t)(((caddr_t)rdp) - dp->rx_ring),
		sizeof(struct sfe_desc), DDI_DMA_SYNC_FORKERNEL);
E 29
I 29
D 34
	status = LE32(rdp->d_cmdsts);
E 34
I 34
D 36
	status = LE_32(rdp->d_cmdsts);
E 36
I 36
	/*
	 * Don't use LE_32() directly to refer rdp->d_cmdsts.
	 * It is not atomic for big endian cpus.
	 */
	status = rdp->d_cmdsts;
	status = LE_32(status);
E 36
E 34
E 29
D 23
#endif
E 23
I 23

E 23
E 7
D 24
	status = rdp->d_cmdsts;
E 24
I 24
D 26
	status = LE32(rdp->d_cmdsts);
E 26
I 26
D 29
	status = ddi_get32(h, &rdp->d_cmdsts);
E 26
E 24

E 29
D 6
	DPRINTF(2, (CE_CONT, "%s: sfe_rx_desc_stat: slot:%d, status:0x%b",
E 6
I 6
D 7
	DPRINTF(2, (CE_CONT, CONS "%s: sfe_rx_desc_stat: slot:%d, status:0x%b",
E 6
		dp->name, slot, status, RXSTAT_BITS));
E 7
I 7
D 34
	DPRINTF(2, (CE_CONT,
	CONS "%s: time:%d sfe_rx_desc_stat: slot:%d, status:0x%b",
		dp->name, ddi_get_lbolt(), slot, status, RXSTAT_BITS));
E 34
I 34
D 35
	DPRINTF(2, (CE_CONT, CONS "%s: time:%d %s: slot:%d, status:0x%b",
E 35
I 35
	DPRINTF(2, (CE_CONT, CONS "%s: time:%ld %s: slot:%d, status:0x%b",
E 35
D 36
		dp->name, ddi_get_lbolt(), __func__,
		slot, status, RXSTAT_BITS));
E 36
I 36
	    dp->name, ddi_get_lbolt(), __func__,
	    slot, status, RXSTAT_BITS));
E 36
E 34
E 7

	if ((status & CMDSTS_OWN) == 0) {
		/*
		 * No more received packets because
		 * this buffer is owned by NIC.
		 */
D 29
		return 0;
E 29
I 29
		return (0);
E 29
	}
D 31

E 31
I 31
D 32
#ifdef GEM_CONFIG_VLAN
E 32
I 32

E 32
E 31
#define	RX_ERR_BITS \
I 31
D 32
	(CMDSTS_RXA | CMDSTS_RXO | CMDSTS_RUNT | \
	 CMDSTS_ISE | CMDSTS_CRCE | CMDSTS_FAE | CMDSTS_MORE)
#else
#define	RX_ERR_BITS \
E 32
E 31
	(CMDSTS_RXA | CMDSTS_RXO | CMDSTS_LONG | CMDSTS_RUNT | \
D 7
	 CMDSTS_ISE | CMDSTS_CRCE | CMDSTS_FAE)
E 7
I 7
D 36
	 CMDSTS_ISE | CMDSTS_CRCE | CMDSTS_FAE | CMDSTS_MORE)
E 36
I 36
		CMDSTS_ISE | CMDSTS_CRCE | CMDSTS_FAE | CMDSTS_MORE)
E 36
E 7
D 31

E 31
I 31
D 32
#endif
E 32
I 32

E 32
E 31
D 34
	if ((status & RX_ERR_BITS) != 0) {
E 34
I 34
	if (status & RX_ERR_BITS) {
E 34
		/*
		 * Packet with error received
		 */
D 6
		DPRINTF(0, (CE_CONT, "%s: Corrupted packet "
E 6
I 6
		DPRINTF(0, (CE_CONT, CONS "%s: Corrupted packet "
E 6
D 36
			"received, buffer status: %b",
			dp->name, status, RXSTAT_BITS));
E 36
I 36
		    "received, buffer status: %b",
		    dp->name, status, RXSTAT_BITS));
E 36

		/* collect statistics information */
		dp->stats.errrcv++;
D 34
		if ((status & CMDSTS_RXO) != 0) {
E 34
I 34

		if (status & CMDSTS_RXO) {
E 34
			dp->stats.overflow++;
D 36
		}
D 7
		if ((status & CMDSTS_LONG) != 0) {
E 7
I 7
D 34
		if ((status & (CMDSTS_LONG | CMDSTS_MORE)) != 0) {
E 34
I 34
		else if (status & (CMDSTS_LONG | CMDSTS_MORE)) {
E 36
I 36
		} else if (status & (CMDSTS_LONG | CMDSTS_MORE)) {
E 36
E 34
E 7
			dp->stats.frame_too_long++;
D 36
		}
D 34
		if ((status & CMDSTS_RUNT) != 0) {
E 34
I 34
		else if (status & CMDSTS_RUNT) {
E 36
I 36
		} else if (status & CMDSTS_RUNT) {
E 36
E 34
			dp->stats.runt++;
D 36
		}
D 34
		if ((status & (CMDSTS_ISE | CMDSTS_FAE)) != 0) {
E 34
I 34
		else if (status & (CMDSTS_ISE | CMDSTS_FAE)) {
E 36
I 36
		} else if (status & (CMDSTS_ISE | CMDSTS_FAE)) {
E 36
E 34
			dp->stats.frame++;
D 36
		}
D 34
		if ((status & CMDSTS_CRCE) != 0) {
E 34
I 34
		else if (status & CMDSTS_CRCE) {
E 36
I 36
		} else if (status & CMDSTS_CRCE) {
E 36
E 34
			dp->stats.crc++;
D 36
		}
I 34
		else {
E 36
I 36
		} else {
E 36
			dp->stats.rcv_internal_err++;
		}
E 34

D 29
		return flag | GEM_RX_ERR;
E 29
I 29
		return (flag | GEM_RX_ERR);
E 29
	}

	/*
D 36
	 * this packet was received without errors 
E 36
I 36
	 * this packet was received without errors
E 36
	 */
D 12
	len = (status & CMDSTS_SIZE) - ETHERFCSL;

E 12
I 12
D 36
	if ((len = (status & CMDSTS_SIZE) - ETHERFCSL) < 0) {
		len = 0;
E 36
I 36
	if ((len = (status & CMDSTS_SIZE)) >= ETHERFCSL) {
		len -= ETHERFCSL;
E 36
	}
E 12
D 36
#ifdef RX_FLOW_CONTROL
	if (dp->flow_control && len == ETHERMIN &&
		bcmp(dp->rx_buf_head->rxb_buf,
D 2
		  sfe_pause_mac_addr.ether_addr_octet, /*ETHERADDRL*/3) == 0) {
E 2
I 2
		  sfe_pause_mac_addr.ether_addr_octet, ETHERADDRL) == 0) {
E 36
E 2

D 36
		sfe_pause_received(dp, (uint8_t *)dp->rx_buf_head->rxb_buf);
D 7
#ifdef notdef
		/* treat as a psuedo collision */
		dp->stats.collisions++;
#endif
E 7
I 7

E 7
		/*
		 * For performance, we discard this packet
		 * if we are not in promiscous mode
		 */
		len = 0;
	}
#endif /* RX_FLOW_CONTROL */

#ifdef notdef
E 36
I 36
#if DEBUG_LEVEL > 10
E 36
D 31
	if (1) {
		int	i;
		uint8_t	*bp = dp->rx_buf_head->rxb_buf;
E 31
I 31
{
	int	i;
	uint8_t	*bp = dp->rx_buf_head->rxb_buf;
E 31

D 6
		cmn_err(CE_CONT, "%s: len:%d", dp->name, len);
E 6
I 6
D 31
		cmn_err(CE_CONT, CONS "%s: len:%d", dp->name, len);
E 31
I 31
	cmn_err(CE_CONT, CONS "%s: len:%d", dp->name, len);
E 31
E 6

D 31
		for (i = 0; i < 60; i += 10) {
D 6
			cmn_err(CE_CONT,
E 6
I 6
			cmn_err(CE_CONT, CONS
E 6
			"%02x %02x %02x %02x %02x %02x %02x %02x %02x %02x",
			bp[0], bp[1], bp[2], bp[3], bp[4],
			bp[5], bp[6], bp[7], bp[8], bp[9]);
		}
		bp += 10;
E 31
I 31
	for (i = 0; i < 60; i += 10) {
		cmn_err(CE_CONT, CONS
D 36
		"%02x %02x %02x %02x %02x %02x %02x %02x %02x %02x",
		bp[0], bp[1], bp[2], bp[3], bp[4],
		bp[5], bp[6], bp[7], bp[8], bp[9]);
E 36
I 36
		    "%02x %02x %02x %02x %02x %02x %02x %02x %02x %02x",
		    bp[0], bp[1], bp[2], bp[3], bp[4],
		    bp[5], bp[6], bp[7], bp[8], bp[9]);
E 36
E 31
	}
I 31
	bp += 10;
}
E 31
#endif
D 12
	return flag | len;
E 12
I 12
D 29
	return flag | (len & GEM_RX_LEN);
E 29
I 29
	return (flag | (len & GEM_RX_LEN));
E 29
E 12
}

static void
sfe_tx_desc_init(struct gem_dev *dp, int slot)
{
I 36
	uint_t			tx_ring_size = dp->gc.gc_tx_ring_size;
E 36
D 7
	struct sfe_desc		*tdp;
	uint32_t		here;
E 7
I 7
D 26
	struct sfe_desc	*tdp;
	uint32_t	here;
E 26
I 26
	struct sfe_desc		*tdp;
	uint32_t		here;
D 29
	ddi_acc_handle_t	h = dp->desc_acc_handle;
E 29
E 26
E 7

D 29
	tdp = &((struct sfe_desc *)dp->tx_ring)[slot];
E 29
I 29
D 36
	tdp = (struct sfe_desc *) &dp->tx_ring[SFE_DESC_SIZE * slot];
E 36
I 36
	tdp = (void *)&dp->tx_ring[SFE_DESC_SIZE * slot];
E 36
E 29

I 36
	/* don't clear d_link field, which have a valid pointer */
E 36
D 26
	tdp->d_cmdsts = 0;
E 26
I 26
D 29
	ddi_put32(h, &tdp->d_cmdsts, 0);
E 29
I 29
	tdp->d_cmdsts = 0;
E 29
E 26
I 7
D 23
#ifdef IOCACHE
E 23
I 23

E 23
D 29
	ddi_dma_sync(dp->desc_dma_handle,
		(off_t)(((caddr_t)tdp) - dp->rx_ring),
		sizeof(struct sfe_desc), DDI_DMA_SYNC_FORDEV);
D 23
#endif
E 23
E 7

E 29
I 23
D 24

E 23
	/* link this from previous descriptor */
E 24
I 24
	/* make a link to this from the previous descriptor */
E 24
D 29
	here = ((uint32_t)dp->tx_ring_dma) + sizeof(struct sfe_desc)*slot;
E 29
I 29
	here = ((uint32_t)dp->tx_ring_dma) + SFE_DESC_SIZE*slot;
E 29
D 24
	if (slot == 0) {
		tdp = &((struct sfe_desc *)dp->tx_ring)[TX_RING_SIZE];
	}
	tdp--;
	tdp->d_link = here;
E 24
D 7

E 7
I 7
D 23
#ifdef IOCACHE
E 23
I 23

I 24
D 29
	tdp = &((struct sfe_desc *)dp->tx_ring)[SLOT(slot - 1, TX_RING_SIZE)];
D 26
	tdp->d_link = LE32(here);
E 26
I 26
	ddi_put32(h, &tdp->d_link, here);
E 26

E 24
E 23
	ddi_dma_sync(dp->desc_dma_handle,
		(off_t)(((caddr_t)tdp) - dp->rx_ring),
		sizeof(struct sfe_desc), DDI_DMA_SYNC_FORDEV);
D 23
#endif
E 23
I 23

E 23
E 7
	return;
E 29
I 29
D 36
	tdp = (struct sfe_desc *)
		&dp->tx_ring[SFE_DESC_SIZE * SLOT(slot - 1, TX_RING_SIZE)];
E 36
I 36
	tdp = (void *)
	    &dp->tx_ring[SFE_DESC_SIZE * SLOT(slot - 1, tx_ring_size)];
E 36
D 34
	tdp->d_link = LE32(here);
E 34
I 34
	tdp->d_link = LE_32(here);
E 34
E 29
}

static void
sfe_rx_desc_init(struct gem_dev *dp, int slot)
{
I 36
	uint_t			rx_ring_size = dp->gc.gc_rx_ring_size;
E 36
D 7
	struct sfe_desc		*rdp;
	uint32_t		here;
E 7
I 7
D 26
	struct sfe_desc	*rdp;
	uint32_t	here;
E 26
I 26
	struct sfe_desc		*rdp;
	uint32_t		here;
D 29
	ddi_acc_handle_t	h = dp->desc_acc_handle;
E 29
E 26
E 7

D 29
	rdp = &((struct sfe_desc *)dp->rx_ring)[slot];
E 29
I 29
D 36
	rdp = (struct sfe_desc *) &dp->rx_ring[SFE_DESC_SIZE * slot];
D 31
#if 0
E 31
I 31
#ifdef NEVER
	/* XXX - don't corrupt d_link */
E 31
	bzero(rdp, SFE_DESC_SIZE);
#endif
E 36
I 36
	rdp = (void *)&dp->rx_ring[SFE_DESC_SIZE * slot];

	/* don't clear d_link field, which have a valid pointer */
E 36
D 34
	rdp->d_cmdsts = LE32(CMDSTS_OWN);
E 34
I 34
	rdp->d_cmdsts = LE_32(CMDSTS_OWN);
E 34
E 29

D 24
	rdp->d_cmdsts = CMDSTS_OWN;
E 24
I 24
D 26
	rdp->d_cmdsts = LE32(CMDSTS_OWN);
E 26
I 26
D 29
	ddi_put32(h, &rdp->d_cmdsts, CMDSTS_OWN);
E 26
E 24
D 7

E 7
I 7
D 23
#ifdef IOCACHE
E 23
I 23

E 23
	ddi_dma_sync(dp->desc_dma_handle,
		(off_t)(((caddr_t)rdp) - dp->rx_ring),
		sizeof(struct sfe_desc), DDI_DMA_SYNC_FORDEV);
D 23
#endif
E 23
I 23

E 29
E 23
E 7
D 24
	/* link this from previous descriptor */
E 24
I 24
	/* make a link to this from the previous descriptor */
E 24
D 29
	here = ((uint32_t)dp->rx_ring_dma) + sizeof(struct sfe_desc)*slot;
E 29
I 29
	here = ((uint32_t)dp->rx_ring_dma) + SFE_DESC_SIZE*slot;
E 29
D 24
	if (slot == 0) {
		rdp = &((struct sfe_desc *)dp->rx_ring)[RX_RING_SIZE];
	}
	rdp--;
	rdp->d_link = here;
I 11
	ASSERT(here != 0);
E 24
E 11
I 7
D 23
#ifdef IOCACHE
E 23
I 23

I 24
D 29
	rdp = &((struct sfe_desc *)dp->rx_ring)[SLOT(slot - 1, RX_RING_SIZE)];
D 26
	rdp->d_link = LE32(here);
E 26
I 26
	ddi_put32(h, &rdp->d_link, here);
E 26

E 24
E 23
	ddi_dma_sync(dp->desc_dma_handle,
		(off_t)(((caddr_t)rdp) - dp->rx_ring),
		sizeof(struct sfe_desc), DDI_DMA_SYNC_FORDEV);
D 23
#endif
E 23
E 7

	return;
E 29
I 29
D 36
	rdp = (struct sfe_desc *)
		&dp->rx_ring[SFE_DESC_SIZE * SLOT(slot - 1, RX_RING_SIZE)];
E 36
I 36
	rdp = (void *)
	    &dp->rx_ring[SFE_DESC_SIZE * SLOT(slot - 1, rx_ring_size)];
E 36
D 34
	rdp->d_link = LE32(here);
E 34
I 34
	rdp->d_link = LE_32(here);
E 34
E 29
}

static void
sfe_tx_desc_clean(struct gem_dev *dp, int slot)
{
	struct sfe_desc		*tdp;
I 26
D 29
	ddi_acc_handle_t	h = dp->desc_acc_handle;
E 29
E 26

D 29
	tdp = &((struct sfe_desc *)dp->tx_ring)[slot];
D 26
	tdp->d_cmdsts = 0;
E 26
I 26
	ddi_put32(h, &tdp->d_cmdsts, 0);
E 26
I 7
D 23
#ifdef IOCACHE
E 23
I 23

E 23
	ddi_dma_sync(dp->desc_dma_handle,
		(off_t)(((caddr_t)tdp) - dp->rx_ring),
		sizeof(struct sfe_desc), DDI_DMA_SYNC_FORDEV);
E 29
I 29
D 36
	tdp = (struct sfe_desc *) &dp->tx_ring[SFE_DESC_SIZE * slot];
E 36
I 36
	tdp = (void *)&dp->tx_ring[SFE_DESC_SIZE * slot];
E 36
	tdp->d_cmdsts = 0;
E 29
D 23
#endif
E 23
E 7
}

static void
sfe_rx_desc_clean(struct gem_dev *dp, int slot)
{
	struct sfe_desc		*rdp;
I 26
D 29
	ddi_acc_handle_t	h = dp->desc_acc_handle;
E 29
E 26

D 29
	rdp = &((struct sfe_desc *)dp->rx_ring)[slot];
D 24
	rdp->d_cmdsts = CMDSTS_OWN;
E 24
I 24
D 26
	rdp->d_cmdsts = LE32(CMDSTS_OWN);
E 26
I 26
	ddi_put32(h, &rdp->d_cmdsts, CMDSTS_OWN);
E 26
E 24
I 7
D 23
#ifdef IOCACHE
E 23
I 23

E 23
	ddi_dma_sync(dp->desc_dma_handle,
		(off_t)(((caddr_t)rdp) - dp->rx_ring),
		sizeof(struct sfe_desc), DDI_DMA_SYNC_FORDEV);
E 29
I 29
D 36
	rdp = (struct sfe_desc *) &dp->rx_ring[SFE_DESC_SIZE * slot];
E 36
I 36
	rdp = (void *)&dp->rx_ring[SFE_DESC_SIZE * slot];
E 36
D 34
	rdp->d_cmdsts = LE32(CMDSTS_OWN);
E 34
I 34
	rdp->d_cmdsts = LE_32(CMDSTS_OWN);
E 34
E 29
D 23
#endif
E 23
E 7
}

/*
 * Device depend interrupt handler
 */
D 36
static u_int
E 36
I 36
static uint_t
E 36
sfe_interrupt(struct gem_dev *dp)
{
I 34
D 36
	int		i;
E 36
I 36
	uint_t		rx_ring_size = dp->gc.gc_rx_ring_size;
E 36
E 34
	uint32_t	isr;
I 36
	uint32_t	isr_bogus;
E 36
	uint_t		flags = 0;
I 11
D 26
	int		loop;
E 26
I 16
D 29
	boolean_t	need_to_reset = FALSE;
E 29
I 29
	boolean_t	need_to_reset = B_FALSE;
E 29
E 16
E 11
D 36
	struct sfe_dev	*lp = (struct sfe_dev *)dp->private;
D 31

E 31
I 31
#ifndef CONFIG_OPT_IO
E 31
I 20
	/* disable interrupts before clearing isr.*/
	OUTL(dp, IER, 0);
D 31

E 31
I 31
#endif
E 36
I 36
	struct sfe_dev	*lp = dp->private;

E 36
E 31
E 20
	/* read reason and clear interrupt */
	isr = INL(dp, ISR);

D 6
	DPRINTF(3, (CE_CONT, "%s: sfe_interrupt: called: isr:0x%b",
E 6
I 6
D 7
	DPRINTF(3, (CE_CONT, CONS "%s: sfe_interrupt: called: isr:0x%b",
E 6
		dp->name, isr, INTR_BITS));
E 7
I 7
D 11
	DPRINTF(3, (CE_CONT, CONS "%s: time:%d sfe_interrupt:called: isr:0x%b",
		dp->name, ddi_get_lbolt(), isr, INTR_BITS));
E 7

E 11
D 36
	if ((isr & lp->our_intr_bits) == 0) {
I 31
#ifndef CONFIG_OPT_IO
E 31
D 20
		/* not for us */
E 20
I 20
D 26
		/* not for us, enable interrupts again*/
E 26
I 26
		/* not for us, enable interrupts again */
E 26
		OUTL(dp, IER, 1);
I 31
#endif
E 36
I 36
	isr_bogus = lp->isr_pended;
	lp->isr_pended = 0;

	if (((isr | isr_bogus) & lp->our_intr_bits) == 0) {
		/* we are not the interrupt source */
E 36
E 31
E 20
D 29
		return DDI_INTR_UNCLAIMED;
E 29
I 29
		return (DDI_INTR_UNCLAIMED);
E 29
	}

I 11
D 16
	DPRINTF(3, (CE_CONT, CONS "%s: time:%d sfe_interrupt:called: isr:0x%b rx_desc_head: %d",
E 16
I 16
	DPRINTF(3, (CE_CONT,
D 29
		CONS "%s: time:%d sfe_interrupt:called: "
		"isr:0x%b rx_desc_head: %d",
E 16
		dp->name, ddi_get_lbolt(), isr, INTR_BITS, dp->rx_desc_head));
E 29
I 29
D 35
		CONS "%s: time:%d %s:called: isr:0x%b rx_active_head: %d",
E 35
I 35
D 36
		CONS "%s: time:%ld %s:called: isr:0x%b rx_active_head: %d",
E 35
		dp->name, ddi_get_lbolt(), __func__,
		isr, INTR_BITS, dp->rx_active_head));
E 36
I 36
	    CONS "%s: time:%ld %s:called: isr:0x%b rx_active_head: %d",
	    dp->name, ddi_get_lbolt(), __func__,
	    isr, INTR_BITS, dp->rx_active_head));
E 36
E 29

E 11
D 29
	if (!dp->nic_active) {
E 29
I 29
	if (!dp->mac_active) {
E 29
		/* the device is going to stop */
I 36
		lp->our_intr_bits = 0;
E 36
D 29
		return DDI_INTR_CLAIMED;
E 29
I 29
		return (DDI_INTR_CLAIMED);
E 29
	}

D 7
#ifdef notdef
	if (lp->chip->chip_type == CHIPTYPE_SIS900) {
		if (isr & ISR_PAUSE_ST) {
			dp->stats.collisions++;
		}
	}

	if ((isr & ISR_TXRCMP) != 0) {
		if (dp->rx_pause_request) {
			sfe_push_pause_frame(dp, 1);
			dp->rx_pause_request = FALSE;
		}
	}
#endif
E 7
D 11
	if ((isr & (ISR_RXORN | ISR_RXERR | ISR_RXOK)) != 0) {
		/* receive done */
		gem_receive(dp);
	}
E 11
I 11
D 16
	loop = 0;
E 16
I 16
D 26
	loop = 100;
E 16
	do {
I 20
		isr &= lp->our_intr_bits;
E 26
I 26
	isr &= lp->our_intr_bits;
E 26

E 20
D 26
		if ((isr & (ISR_RXORN | ISR_RXIDLE | ISR_RXERR |
			    ISR_RXDESC | ISR_RXOK)) != 0) {
			/* receive done */
			gem_receive(dp);
E 26
I 26
D 34
	if ((isr & (ISR_RXORN | ISR_RXIDLE | ISR_RXERR |
		    ISR_RXDESC | ISR_RXOK)) != 0) {
E 26
E 11

E 34
I 34
	if (isr & (ISR_RXSOVR | ISR_RXORN | ISR_RXIDLE | ISR_RXERR |
D 36
		    ISR_RXDESC | ISR_RXOK)) {
E 36
I 36
	    ISR_RXDESC | ISR_RXOK)) {
E 36
E 34
D 11
	if ((isr & (ISR_TXURN | ISR_TXERR | ISR_TXDESC)) != 0) {
		/* transmit done */
		flags |= (gem_tx_done(dp) ? INTR_RESTART_TX : 0);
	}
E 11
I 11
D 26
			if ((isr & ISR_RXIDLE) != 0) {
D 16
				/* this should not happen */
				cmn_err(CE_NOTE, "%s: interrupt: isr %b.",
E 16
I 16
				cmn_err(CE_NOTE,
					"%s: rx buffer ran out: isr %b.",
E 16
					dp->name, isr, INTR_BITS);
D 16
#ifdef notdef
				/* this may cause the system stuck */
E 16
I 16
				/*
				 * Ensure RXDP points the head of receive
				 * buffer list.
				 */
				OUTL(dp, RXDP, dp->rx_ring_dma +
					sizeof(struct sfe_desc) *
					SLOT(dp->rx_desc_head, RX_RING_SIZE));
E 26
I 26
D 31
		gem_receive(dp);
E 31
I 31
		(void) gem_receive(dp);
E 31
E 26

D 26
				/* Restart the receive engine */
E 16
				OUTL(dp, CR, lp->cr | CR_RXE);
D 16
#endif
E 16
			}
		}
E 26
I 26
D 34
		if ((isr & ISR_RXIDLE) != 0) {
			cmn_err(CE_NOTE,
				"%s: rx buffer ran out: isr %b.",
				dp->name, isr, INTR_BITS);
E 34
I 34
		if (isr & (ISR_RXSOVR | ISR_RXORN)) {
			DPRINTF(0, (CE_CONT,
D 36
				CONS "%s: rx fifo overrun: isr %b",
				dp->name, isr, INTR_BITS));
E 36
I 36
			    CONS "%s: rx fifo overrun: isr %b",
			    dp->name, isr, INTR_BITS));
E 36
			/* no need restart rx */
			dp->stats.overflow++;
		}

		if (isr & ISR_RXIDLE) {
			DPRINTF(0, (CE_CONT,
D 36
				CONS "%s: rx buffer ran out: isr %b",
				dp->name, isr, INTR_BITS));
E 36
I 36
			    CONS "%s: rx buffer ran out: isr %b",
			    dp->name, isr, INTR_BITS));
E 36

			dp->stats.norcvbuf++;

E 34
			/*
D 29
			 * Ensure RXDP points the head of receive
E 29
I 29
			 * Make RXDP points the head of receive
E 29
			 * buffer list.
			 */
			OUTL(dp, RXDP, dp->rx_ring_dma +
D 29
				sizeof(struct sfe_desc) *
				SLOT(dp->rx_desc_head, RX_RING_SIZE));
E 29
I 29
D 36
				SFE_DESC_SIZE *
				SLOT(dp->rx_active_head, RX_RING_SIZE));
E 36
I 36
			    SFE_DESC_SIZE *
			    SLOT(dp->rx_active_head, rx_ring_size));
E 36
E 29
E 26
E 11

D 11
	if ((isr & ISR_HIBERR) != 0) {
		cmn_err(CE_WARN, "%s: ERROR interrupt: isr %b.",
			dp->name, isr, INTR_BITS);
	}
E 11
I 11
D 18
		if ((isr & (ISR_TXURN | ISR_TXERR | ISR_TXDESC |
			    ISR_TXOK)) != 0) {
			/* transmit done */
E 18
I 18
D 20
		if ((isr & (ISR_TXURN | ISR_TXERR | ISR_TXDESC)) != 0) {
E 20
I 20
D 26
		if ((isr & (ISR_TXURN | ISR_TXERR | ISR_TXDESC |
					ISR_TXIDLE | ISR_TXOK)) != 0) {
E 20
			/* need to relaim tx buffers */
E 18
D 20
			flags |= (gem_tx_done(dp) ? INTR_RESTART_TX : 0);
E 20
I 20
D 24
			flags |= gem_tx_done(dp) ? INTR_RESTART_TX : 0;
E 24
I 24
			if (gem_tx_done(dp)) {
				flags |= INTR_RESTART_TX;
			}
E 26
I 26
			/* Restart the receive engine */
			OUTL(dp, CR, lp->cr | CR_RXE);
E 26
E 24
E 20
		}
I 26
	}
E 26
E 11
D 7

E 7
D 9
#ifdef notdef
D 6
	DPRINTF(3, (CE_CONT, "%s: sfe_interrupt: return: isr: %b",
E 6
I 6
	DPRINTF(3, (CE_CONT, CONS "%s: sfe_interrupt: return: isr: %b",
E 6
D 3
	       dp->name, INL(dp, ISR), INTR_BITS));
E 3
I 3
	       dp->name, isr, INTR_BITS);
E 3
#endif
E 9
I 9
D 18

I 11
		if ((isr & ISR_TXIDLE) != 0) {
E 18
I 18
D 20
#ifdef notdef
		if ((isr & (ISR_TXIDLE | ISR_TXOK)) != 0) {
E 18
			/* do nothing */
		}
D 18

E 18
I 18
#endif
E 20
I 20

E 20
E 18
D 16
		if ((isr & ISR_HIBERR) != 0) {
E 16
I 16
D 26
		if ((isr & (ISR_DPERR | ISR_SSERR | ISR_RMABT | ISR_RTABT))
			!= 0) {
E 16
			cmn_err(CE_WARN, "%s: ERROR interrupt: isr %b.",
				dp->name, isr, INTR_BITS);
I 16
			need_to_reset = TRUE;
E 26
I 26
D 34
	if ((isr & (ISR_TXURN | ISR_TXERR | ISR_TXDESC |
				ISR_TXIDLE | ISR_TXOK)) != 0) {
E 34
I 34
	if (isr & (ISR_TXURN | ISR_TXERR | ISR_TXDESC |
D 36
				ISR_TXIDLE | ISR_TXOK)) {
E 34
		/* need to relaim tx buffers */
E 36
I 36
	    ISR_TXIDLE | ISR_TXOK)) {
		/* need to reclaim tx buffers */
E 36
		if (gem_tx_done(dp)) {
			flags |= INTR_RESTART_TX;
E 26
E 16
		}
I 34
D 36

E 36
		/*
		 * XXX - tx error statistics will be counted in
		 * sfe_tx_desc_stat() and no need to restart tx on errors.
		 */
E 34
I 26
	}
E 26

D 26
		isr = INL(dp, ISR);
D 16
	} while ((isr & lp->our_intr_bits) != 0 && loop++ < 100);
E 16
I 16
	} while ((isr & lp->our_intr_bits) != 0 && --loop > 0);
E 16

I 16
	if (loop == 0) {
		cmn_err(CE_WARN, "%s: sfe_interrupt, loop exeeded the limit",
			dp->name);
E 26
I 26
D 34
	if ((isr & (ISR_DPERR | ISR_SSERR | ISR_RMABT | ISR_RTABT)) != 0) {
E 34
I 34
	if (isr & (ISR_DPERR | ISR_SSERR | ISR_RMABT | ISR_RTABT)) {
E 34
		cmn_err(CE_WARN, "%s: ERROR interrupt: isr %b.",
D 36
			dp->name, isr, INTR_BITS);
E 36
I 36
		    dp->name, isr, INTR_BITS);
E 36
E 26
D 29
		need_to_reset = TRUE;
E 29
I 29
		need_to_reset = B_TRUE;
E 29
	}
D 34

E 34
I 34
reset:
E 34
	if (need_to_reset) {
D 29
		mutex_enter(&dp->xmitlock);
D 28
		gem_restart_tx(dp);
E 28
I 28
		gem_restart_nic(dp, TRUE);
E 28
		mutex_exit(&dp->xmitlock);
E 29
I 29
D 36
		gem_restart_nic(dp, B_TRUE);
E 36
I 36
		(void) gem_restart_nic(dp, GEM_RESTART_KEEP_BUF);
E 36
E 29
		flags |= INTR_RESTART_TX;
	}
D 31

E 31
I 31
D 36
#ifndef CONFIG_OPT_IO
E 31
I 20
	/* enable interrupts again */
D 26
	if ((dp->misc_flag & GEM_NOINTR) == 0 && loop > 0) {
E 26
I 26
	if ((dp->misc_flag & GEM_NOINTR) == 0) {
E 26
		OUTL(dp, IER, 1);
	}
D 31

E 31
I 31
#endif
E 36
I 36

E 36
E 31
E 20
E 16
E 11
D 29
	DPRINTF(5, (CE_CONT, CONS "%s: sfe_interrupt: return: isr: %b",
	       dp->name, isr, INTR_BITS));
E 29
I 29
	DPRINTF(5, (CE_CONT, CONS "%s: %s: return: isr: %b",
D 36
	       dp->name, __func__, isr, INTR_BITS));
E 36
I 36
	    dp->name, __func__, isr, INTR_BITS));
E 36
E 29

E 9
D 7

I 6
	/* flags |= INTR_RESTART_TX; */
E 7
E 6
D 29
	return DDI_INTR_CLAIMED | flags;
E 29
I 29
	return (DDI_INTR_CLAIMED | flags);
E 29
}

I 4
D 10
#ifdef NOINTR_WORKAROUND
void
sfe_intr_watcher(dev_info_t *dip)
{
	gld_mac_info_t  *macinfo;
	struct gem_dev	*dp;
	struct sfe_dev	*lp;

	macinfo = (gld_mac_info_t *)ddi_get_driver_private(dip);
	if (macinfo == NULL) {
		goto next;
	}

	dp = (struct gem_dev *)macinfo->gldm_private;
	if (dp == NULL) {
		goto next;
	}

	lp = (struct sfe_dev *)dp->private;
	if (lp->ier != 0) {
		(macinfo->gldm_intr)(macinfo);
	}
next:
	/* schedule next call of sfe_intr_watcher */
	lp->intr_watcher_id =
		timeout((void (*)(void *))sfe_intr_watcher, (void *)dip, 1);
}
#endif

E 10
E 4
/* ======================================================== */
/*
 * HW depend MII routine
 */
/* ======================================================== */

/*
 * MII routines for NS DP83815
 */
static void
sfe_mii_sync_dp83815(struct gem_dev *dp)
{
	/* do nothing */
}

static uint16_t
D 28
sfe_mii_read_dp83815(struct gem_dev *dp, int offset)
E 28
I 28
sfe_mii_read_dp83815(struct gem_dev *dp, uint_t offset)
E 28
{
I 6
D 7
	DPRINTF(4, (CE_CONT, CONS "%s: sfe_mii_read_dp83815: offset 0x%x",
E 7
I 7
D 34
	DPRINTF(4, (CE_CONT, CONS"%s: sfe_mii_read_dp83815: offset 0x%x",
E 7
	       dp->name, offset));
E 34
I 34
	DPRINTF(4, (CE_CONT, CONS"%s: %s: offset 0x%x",
D 36
	       dp->name, __func__, offset));
E 34
E 6
D 29
	return (uint16_t) INL(dp, MII_REGS_BASE + offset*4);
E 29
I 29
	return ((uint16_t) INL(dp, MII_REGS_BASE + offset*4));
E 36
I 36
	    dp->name, __func__, offset));
	return ((uint16_t)INL(dp, MII_REGS_BASE + offset*4));
E 36
E 29
}

static void
D 28
sfe_mii_write_dp83815(struct gem_dev *dp, int offset, uint16_t val)
E 28
I 28
sfe_mii_write_dp83815(struct gem_dev *dp, uint_t offset, uint16_t val)
E 28
{
I 6
D 7
	DPRINTF(4, (CE_CONT, CONS "%s: sfe_mii_write_dp83815: offset 0x%x 0x%x",
E 7
I 7
D 34
	DPRINTF(4, (CE_CONT, CONS"%s: sfe_mii_write_dp83815: offset 0x%x 0x%x",
E 7
	       dp->name, offset, val));
E 34
I 34
	DPRINTF(4, (CE_CONT, CONS"%s: %s: offset 0x%x 0x%x",
D 36
	       dp->name, __func__, offset, val));
E 36
I 36
	    dp->name, __func__, offset, val));
E 36
E 34
E 6
	OUTL(dp, MII_REGS_BASE + offset*4, val);
}

static int
D 34
sfe_mii_init_dp83815(struct gem_dev *dp)
E 34
I 34
D 36
sfe_mii_probe_dp83815(struct gem_dev *dp)
E 34
{
D 12
	int		phy;
	uint16_t	adv;
	uint16_t	status;
E 12
D 26
	uint32_t	phyid;
E 26
D 12
	uint16_t	val;
E 12
	struct sfe_dev	*lp = (struct sfe_dev *)dp->private;

D 6
	DPRINTF(3, (CE_CONT, "%s: sfe_mii_init_dp83815: called", dp->name));
E 6
I 6
D 7
	DPRINTF(3,(CE_CONT, CONS "%s: sfe_mii_init_dp83815: called", dp->name));
E 7
I 7
D 34
	DPRINTF(3,(CE_CONT, CONS"%s: sfe_mii_init_dp83815: called", dp->name));
E 34
I 34
	DPRINTF(3,(CE_CONT, CONS"%s: %s: called", dp->name, __func__));
E 34
E 7
E 6

I 12
	dp->mii_phy_addr = -1;
D 31
	if (gem_mii_init_default(dp) < 0) {
E 31
I 31
D 34
	if (gem_mii_init_default(dp) != GEM_SUCCESS) {
E 34
I 34
	if (gem_mii_probe_default(dp) != GEM_SUCCESS) {
E 34
E 31
D 29
		return -1;
E 29
I 29
		return (GEM_FAILURE);
E 29
	}
D 34

E 34
I 34
#ifdef NEVER
E 34
E 12
D 26
	phyid  = GEM_MII_READ(dp, MII_PHYIDH) << 16;
	phyid |= GEM_MII_READ(dp, MII_PHYIDL);

D 12
	adv = GEM_MII_READ(dp, MII_AN_ADVERT);
	val = GEM_MII_READ(dp, MII_CONTROL);
	status = GEM_MII_READ(dp, MII_STATUS);

D 6
	cmn_err(CE_CONT, "!%s: using internal PHY (0x%08x),"
E 6
I 6
	cmn_err(CE_CONT, CONS "%s: using internal PHY (0x%08x),"
E 6
			"control:%b, status:%b, advert:%b, lpar:%b",
		dp->name, dp->mii_phy_addr,
		val, MII_CONTROL_BITS,
		status, MII_STATUS_BITS,
		adv, MII_ABILITY_BITS,
		GEM_MII_READ(dp, MII_AN_LPABLE),
		MII_ABILITY_BITS);

E 12
	lp->mii_phyid = phyid & PHY_MASK;

E 26
I 24
	/* workaround for 83815 internal PHY */
	dp->gc.gc_mii_linkdown_action = MII_ACTION_NONE;
I 28
	dp->gc.gc_mii_linkdown_timeout_action = MII_ACTION_NONE;
I 34
#endif
E 34
E 28
D 29
	dp->gc.gc_mii_dont_reset      = FALSE;
E 29
I 29
	dp->gc.gc_mii_dont_reset      = B_FALSE;
E 29

E 24
D 29
	return 0;
E 29
I 29
	return (GEM_SUCCESS);
E 29
}

I 4
static int
E 36
sfe_mii_config_dp83815(struct gem_dev *dp)
{
	uint32_t	srr;
D 36
	struct sfe_dev	*lp = (struct sfe_dev *)dp->private;
E 36

	srr = INL(dp, SRR) & SRR_REV;

D 6
	DPRINTF(0, (CE_CONT, "!%s: srr:0x%04x %04x %04x %04x %04x %04x",
E 6
I 6
	DPRINTF(0, (CE_CONT, CONS "%s: srr:0x%04x %04x %04x %04x %04x %04x",
E 6
D 36
		dp->name, srr,
		INW(dp, 0x00cc),	/* PGSEL */
		INW(dp, 0x00e4),	/* PMDCSR */
		INW(dp, 0x00fc),	/* TSTDAT */
		INW(dp, 0x00f4),	/* DSPCFG */
		INW(dp, 0x00f8))	/* SDCFG */
	);
E 36
I 36
	    dp->name, srr,
	    INW(dp, 0x00cc),	/* PGSEL */
	    INW(dp, 0x00e4),	/* PMDCSR */
	    INW(dp, 0x00fc),	/* TSTDAT */
	    INW(dp, 0x00f4),	/* DSPCFG */
	    INW(dp, 0x00f8)));	/* SDCFG */
E 36

D 6
	if (srr == SRR_REV_CVNG || srr == 0x0203) {
E 6
I 6
D 36
	if (srr == SRR_REV_CVNG) {
E 36
I 36
	if (srr == SRR_REV_DP83815CVNG) {
E 36
E 6
		/*
D 7
		 * NS datasheet says that DP83815CVNG needs following
E 7
I 7
D 26
		 * NS data sheet says that DP83815CVNG needs following
E 26
I 26
		 * NS datasheet says that DP83815CVNG needs following
E 26
E 7
D 31
		 * registers to be patched for optimizing performance.
E 31
I 31
		 * registers to be patched for optimizing its performance.
E 31
I 6
D 26
		 * A report says that CRC errors on RX was disappeared.
E 26
I 26
D 36
		 * A report said that CRC errors on RX was disappeared.
E 36
I 36
		 * A report said that CRC errors on RX disappeared
		 * with the patch.
E 36
E 26
E 6
		 */
		OUTW(dp, 0x00cc, 0x0001);	/* PGSEL */
		OUTW(dp, 0x00e4, 0x189c);	/* PMDCSR */
		OUTW(dp, 0x00fc, 0x0000);	/* TSTDAT */
		OUTW(dp, 0x00f4, 0x5040);	/* DSPCFG */
		OUTW(dp, 0x00f8, 0x008c);	/* SDCFG */
I 36
		OUTW(dp, 0x00cc, 0x0000);	/* PGSEL */
E 36

		DPRINTF(0, (CE_CONT,
D 6
			"!%s: PHY patched %04x %04x %04x %04x %04x",
E 6
I 6
D 36
			CONS "%s: PHY patched %04x %04x %04x %04x %04x",
E 6
			dp->name,
			INW(dp, 0x00cc),	/* PGSEL */
			INW(dp, 0x00e4),	/* PMDCSR */
			INW(dp, 0x00fc),	/* TSTDAT */
			INW(dp, 0x00f4),	/* DSPCFG */
			INW(dp, 0x00f8))	/* SDCFG */
		);
E 36
I 36
		    CONS "%s: PHY patched %04x %04x %04x %04x %04x",
		    dp->name,
		    INW(dp, 0x00cc),	/* PGSEL */
		    INW(dp, 0x00e4),	/* PMDCSR */
		    INW(dp, 0x00fc),	/* TSTDAT */
		    INW(dp, 0x00f4),	/* DSPCFG */
		    INW(dp, 0x00f8)));	/* SDCFG */
	} else if (((srr ^ SRR_REV_DP83815DVNG) & 0xff00) == 0 ||
	    ((srr ^ SRR_REV_DP83816AVNG) & 0xff00) == 0) {
		/*
		 * Additional packets for later chipset
		 */
		OUTW(dp, 0x00cc, 0x0001);	/* PGSEL */
		OUTW(dp, 0x00e4, 0x189c);	/* PMDCSR */
		OUTW(dp, 0x00cc, 0x0000);	/* PGSEL */

		DPRINTF(0, (CE_CONT,
		    CONS "%s: PHY patched %04x %04x",
		    dp->name,
		    INW(dp, 0x00cc),	/* PGSEL */
		    INW(dp, 0x00e4)));	/* PMDCSR */
E 36
	}

D 29
	return gem_mii_config_default(dp);
E 29
I 29
	return (gem_mii_config_default(dp));
E 29
}

I 36
static int
sfe_mii_probe_dp83815(struct gem_dev *dp)
{
	uint32_t	val;
E 36

I 36
	/* try external phy first */
	DPRINTF(0, (CE_CONT, CONS "%s: %s: trying external phy",
	    dp->name, __func__));
	dp->mii_phy_addr = 0;
	dp->gc.gc_mii_sync = &sfe_mii_sync_sis900;
	dp->gc.gc_mii_read = &sfe_mii_read_sis900;
	dp->gc.gc_mii_write = &sfe_mii_write_sis900;

	val = INL(dp, CFG) & (CFG_ANEG_SEL | CFG_PHY_CFG);
	OUTL(dp, CFG, val | CFG_EXT_PHY | CFG_PHY_DIS);

	if (gem_mii_probe_default(dp) == GEM_SUCCESS) {
		return (GEM_SUCCESS);
	}

	/* switch to internal phy */
	DPRINTF(0, (CE_CONT, CONS "%s: %s: switching to internal phy",
	    dp->name, __func__));
	dp->mii_phy_addr = -1;
	dp->gc.gc_mii_sync = &sfe_mii_sync_dp83815;
	dp->gc.gc_mii_read = &sfe_mii_read_dp83815;
	dp->gc.gc_mii_write = &sfe_mii_write_dp83815;

	val = INL(dp, CFG) & (CFG_ANEG_SEL | CFG_PHY_CFG);
	OUTL(dp, CFG, val | CFG_PAUSE_ADV | CFG_PHY_RST);
	drv_usecwait(100);	/* keep to assert RST bit for a while */
	OUTL(dp, CFG, val | CFG_PAUSE_ADV);

	/* wait for PHY reset */
	delay(drv_usectohz(10000));

	return (gem_mii_probe_default(dp));
}

static int
sfe_mii_init_dp83815(struct gem_dev *dp)
{
	uint32_t	val;

	val = INL(dp, CFG) & (CFG_ANEG_SEL | CFG_PHY_CFG);

	if (dp->mii_phy_addr == -1) {
		/* select internal phy */
		OUTL(dp, CFG, val | CFG_PAUSE_ADV);
	} else {
		/* select external phy */
		OUTL(dp, CFG, val | CFG_EXT_PHY | CFG_PHY_DIS);
	}

	return (GEM_SUCCESS);
}

E 36
E 4
/*
 * MII routines for SiS900
 */
D 36
#define MDIO_DELAY(dp)    INL(dp, MEAR)
E 36
I 36
#define	MDIO_DELAY(dp)	{(void) INL(dp, MEAR); (void) INL(dp, MEAR); }
E 36
static void
sfe_mii_sync_sis900(struct gem_dev *dp)
{
	int	i;

I 36
	/* send 32 ONE's to make MII line idle */
E 36
	for (i = 0; i < 32; i++) {
		OUTL(dp, MEAR, MEAR_MDDIR | MEAR_MDIO);
		MDIO_DELAY(dp);
		OUTL(dp, MEAR, MEAR_MDDIR | MEAR_MDIO | MEAR_MDC);
		MDIO_DELAY(dp);
	}
D 13
	OUTL(dp, MEAR, MEAR_MDDIR | MEAR_MDIO);
E 13
}

static int
D 34
sfe_mii_init_sis900(struct gem_dev *dp)
E 34
I 34
D 36
sfe_mii_probe_sis900(struct gem_dev *dp)
E 34
{
	struct sfe_dev	*lp = (struct sfe_dev *)dp->private;

D 34
	if (gem_mii_init_default(dp) != 0) {
E 34
I 34
	if (gem_mii_probe_default(dp) != GEM_SUCCESS) {
E 34
D 29
		return -1;
E 29
I 29
		return (GEM_FAILURE);
E 29
	}
D 34

E 34
I 34
#ifdef NEVER
E 34
D 26
	lp->mii_phyid =
	  (GEM_MII_READ(dp, MII_PHYIDL) | GEM_MII_READ(dp, MII_PHYIDH) << 16)
		& PHY_MASK;

D 7
	if (lp->mii_phyid == PHY_INTERNAL) {
E 7
I 7
	if (lp->mii_phyid == PHY_SIS900_INTERNAL) {
E 26
I 26
	if ((dp->mii_phy_id & PHY_MASK) == PHY_SIS900_INTERNAL) {
E 26
E 7
D 24
		/* wordaround for internal PHY */
		dp->gc.gc_mii_linkdown_action  = MII_ACTION_RESET;
		dp->gc.gc_mii_dont_reset       = FALSE;
E 24
I 24
		/* workaround for internal PHY */
D 28
		dp->gc.gc_mii_linkdown_action = MII_ACTION_RESET;
E 28
I 28
		dp->gc.gc_mii_linkdown_action = MII_ACTION_RSA;
		dp->gc.gc_mii_linkdown_timeout_action = MII_ACTION_RESET;
E 28
D 29
		dp->gc.gc_mii_dont_reset      = FALSE;
E 29
I 29
		dp->gc.gc_mii_dont_reset      = B_FALSE;
E 29
E 24
	} 
I 24
	else {
		dp->gc.gc_mii_linkdown_action = MII_ACTION_NONE;
I 28
		dp->gc.gc_mii_linkdown_timeout_action = MII_ACTION_NONE;
E 28
D 29
		dp->gc.gc_mii_dont_reset      = FALSE;
E 29
I 29
		dp->gc.gc_mii_dont_reset      = B_FALSE;
E 29
	}
E 24
D 34

E 34
I 34
#endif
E 34
D 29
	return 0;
E 29
I 29
	return (GEM_SUCCESS);
E 29
}

static int
E 36
sfe_mii_config_sis900(struct gem_dev *dp)
{
D 36
	struct sfe_dev	*lp = (struct sfe_dev *)dp->private;
E 36
I 36
	struct sfe_dev	*lp = dp->private;
E 36

	/* Do chip depend setup */
D 26
	if (lp->mii_phyid == PHY_ICS1893) {
E 26
I 26
	if ((dp->mii_phy_id & PHY_MASK) == PHY_ICS1893) {
E 26
D 36
		/* workaround for ICS1893 PHY */ 
E 36
I 36
		/* workaround for ICS1893 PHY */
E 36
D 29
		GEM_MII_WRITE(dp, 0x0018, 0xD200);
E 29
I 29
		gem_mii_write(dp, 0x0018, 0xD200);
E 29
	}
D 10

E 10
I 10
D 36
#ifdef i86pc
E 36
I 36

E 36
E 10
	if (lp->revid == SIS630E_900_REV) {
		/*
D 31
		 * SiS 630E has some bugs on default value
E 31
I 31
		 * SiS 630E has bugs on default values
E 31
		 * of PHY registers
		 */
D 29
		GEM_MII_WRITE(dp, MII_AN_ADVERT, 0x05e1);
		GEM_MII_WRITE(dp, MII_CONFIG1, 0x0022);
		GEM_MII_WRITE(dp, MII_CONFIG2, 0xff00);
		GEM_MII_WRITE(dp, MII_MASK,    0xffc0);
E 29
I 29
		gem_mii_write(dp, MII_AN_ADVERT, 0x05e1);
		gem_mii_write(dp, MII_CONFIG1, 0x0022);
		gem_mii_write(dp, MII_CONFIG2, 0xff00);
		gem_mii_write(dp, MII_MASK,    0xffc0);
E 29
	}
D 10

E 10
	sfe_set_eq_sis630(dp);
D 10

E 10
I 10
D 36
#endif
E 36
I 36

E 36
E 10
D 29
	return gem_mii_config_default(dp);
E 29
I 29
	return (gem_mii_config_default(dp));
E 29
}

static uint16_t
D 28
sfe_mii_read_sis900_raw(struct gem_dev *dp, int reg)
E 28
I 28
D 36
sfe_mii_read_sis900_raw(struct gem_dev *dp, uint_t reg)
E 36
I 36
sfe_mii_read_sis900(struct gem_dev *dp, uint_t reg)
E 36
E 28
{
	uint32_t	cmd;
	uint16_t	ret;
	int		i;
D 3
	int		data;
E 3
I 3
	uint32_t	data;
E 3

	cmd = MII_READ_CMD(dp->mii_phy_addr, reg);

D 36
	sfe_mii_sync_sis900(dp);

E 36
D 13
	OUTL(dp, MEAR, MEAR_MDDIR | MEAR_MDIO);
	MDIO_DELAY(dp);
	OUTL(dp, MEAR, MEAR_MDDIR | MEAR_MDIO | MEAR_MDC);

	for (i = 31; i >= 16; i--) {
E 13
I 13
	for (i = 31; i >= 18; i--) {
E 13
		data = ((cmd >> i) & 1) <<  MEAR_MDIO_SHIFT;
		OUTL(dp, MEAR, data | MEAR_MDDIR);
		MDIO_DELAY(dp);
		OUTL(dp, MEAR, data | MEAR_MDDIR | MEAR_MDC);
		MDIO_DELAY(dp);
	}

D 13
	ASSERT(i == 15);
E 13
I 13
D 36
	/* tern arould cycle */
	OUTL(dp, MEAR, data | MEAR_MDDIR);
E 36
I 36
	/* turn around cycle */
	OUTL(dp, MEAR, 0);
E 36
	MDIO_DELAY(dp);
E 13

D 13
	for (; i >= 0; i--) {
E 13
I 13
	/* get response from PHY */
	OUTL(dp, MEAR, MEAR_MDC);
	MDIO_DELAY(dp);
I 36

E 36
	OUTL(dp, MEAR, 0);
I 36
#if DEBUG_LEBEL > 0
	(void) INL(dp, MEAR);	/* delay */
E 36
D 34
	if ((INL(dp, MEAR) & MEAR_MDIO) != 0) {
E 34
I 34
	if (INL(dp, MEAR) & MEAR_MDIO) {
E 34
D 36
		DPRINTF(0, (CE_WARN, "%s: PHY@%d not responded",
			dp->name, dp->mii_phy_addr));
E 36
I 36
		cmn_err(CE_WARN, "%s: PHY@%d not responded",
		    dp->name, dp->mii_phy_addr);
E 36
	}
I 36
#else
	MDIO_DELAY(dp);
#endif
E 36
	/* terminate response cycle */
	OUTL(dp, MEAR, MEAR_MDC);
I 36
	MDIO_DELAY(dp);
E 36

I 36
	ret = 0;	/* to avoid lint errors */
E 36
	for (i = 16; i > 0; i--) {
E 13
		OUTL(dp, MEAR, 0);
I 36
		(void) INL(dp, MEAR);	/* delay */
E 36
D 13
		MDIO_DELAY(dp);
E 13
		ret = (ret << 1) | ((INL(dp, MEAR) >> MEAR_MDIO_SHIFT) & 1);
		OUTL(dp, MEAR, MEAR_MDC);
		MDIO_DELAY(dp);
	}

I 13
D 36
	/* terminate data transmition from PHY */
E 13
	OUTL(dp, MEAR, 0);
I 13
	MDIO_DELAY(dp);
	OUTL(dp, MEAR, MEAR_MDC);
	MDIO_DELAY(dp);
E 36
I 36
	/* send two idle(Z) bits to terminate the read cycle */
	for (i = 0; i < 2; i++) {
		OUTL(dp, MEAR, 0);
		MDIO_DELAY(dp);
		OUTL(dp, MEAR, MEAR_MDC);
		MDIO_DELAY(dp);
	}
E 36
E 13

D 29
	return ret;
E 29
I 29
	return (ret);
E 29
}

D 36
static uint16_t
D 28
sfe_mii_read_sis900(struct gem_dev *dp, int reg)
E 28
I 28
sfe_mii_read_sis900(struct gem_dev *dp, uint_t reg)
E 28
{
	if (reg == MII_STATUS) {
		(void) sfe_mii_read_sis900_raw(dp, reg);
	}

D 29
	return sfe_mii_read_sis900_raw(dp, reg);
E 29
I 29
	return (sfe_mii_read_sis900_raw(dp, reg));
E 29
}

E 36
static void
D 28
sfe_mii_write_sis900(struct gem_dev *dp, int reg, uint16_t val)
E 28
I 28
sfe_mii_write_sis900(struct gem_dev *dp, uint_t reg, uint16_t val)
E 28
{
	uint32_t	cmd;
	int		i;
D 3
	int		data;
E 3
I 3
	uint32_t	data;
E 3

	cmd = MII_WRITE_CMD(dp->mii_phy_addr, reg, val);

D 36
	sfe_mii_sync_sis900(dp);

E 36
D 13
	OUTL(dp, MEAR, MEAR_MDDIR | MEAR_MDIO);
	MDIO_DELAY(dp);
	OUTL(dp, MEAR, MEAR_MDDIR | MEAR_MDIO | MEAR_MDC);

E 13
	for (i = 31; i >= 0; i--) {
		data = ((cmd >> i) & 1) << MEAR_MDIO_SHIFT;
		OUTL(dp, MEAR, data | MEAR_MDDIR);
		MDIO_DELAY(dp);
		OUTL(dp, MEAR, data | MEAR_MDDIR | MEAR_MDC);
		MDIO_DELAY(dp);
	}

D 13
	/* Clear out extra bits. */
E 13
I 13
D 36
	/* send two 0s to terminate write cycle. */
E 36
I 36
	/* send two idle(Z) bits to terminate the write cycle. */
E 36
E 13
	for (i = 0; i < 2; i++) {
D 13
		OUTL(dp, MEAR, 0);
E 13
I 13
D 36
		OUTL(dp, MEAR, MEAR_MDDIR);
E 36
I 36
		OUTL(dp, MEAR, 0);
E 36
E 13
		MDIO_DELAY(dp);
D 13
		OUTL(dp, MEAR, MEAR_MDC);
E 13
I 13
D 36
		OUTL(dp, MEAR, MEAR_MDDIR | MEAR_MDC);
E 36
I 36
		OUTL(dp, MEAR, MEAR_MDC);
E 36
E 13
		MDIO_DELAY(dp);
	}
D 13
	OUTL(dp, MEAR, 0);
E 13
I 13
D 36
	OUTL(dp, MEAR, MEAR_MDDIR);
	MDIO_DELAY(dp);
	OUTL(dp, MEAR, MEAR_MDC);
	MDIO_DELAY(dp);
E 36
E 13
}
#undef MDIO_DELAY

I 10
D 36
#ifdef i86pc
E 36
E 10
static void
sfe_set_eq_sis630(struct gem_dev *dp)
{
	uint16_t	reg14h;
	uint16_t	eq_value;
	uint16_t	max_value;
	uint16_t	min_value;
	int		i;
	uint8_t		rev;
D 36
	struct sfe_dev	*lp = (struct sfe_dev *)dp->private;
E 36
I 36
	struct sfe_dev	*lp = dp->private;
E 36

	rev = lp->revid;

	if (!(rev == SIS630E_900_REV || rev == SIS630EA1_900_REV ||
D 36
	      rev == SIS630A_900_REV || rev ==  SIS630ET_900_REV) ) {
E 36
I 36
	    rev == SIS630A_900_REV || rev == SIS630ET_900_REV)) {
E 36
D 29
		/* it dont have a internal PHY */
E 29
I 29
		/* it doesn't have a internal PHY */
E 29
		return;
	}

D 36
#ifdef TUNE_PHY_630
E 36
	if (dp->mii_state == MII_STATE_LINKUP) {
D 29
		reg14h = GEM_MII_READ(dp, MII_RESV);
		GEM_MII_WRITE(dp, MII_RESV, (0x2200 | reg14h) & 0xBFFF);
E 29
I 29
		reg14h = gem_mii_read(dp, MII_RESV);
		gem_mii_write(dp, MII_RESV, (0x2200 | reg14h) & 0xBFFF);
E 29

D 29
		eq_value = (0x00f8 & GEM_MII_READ(dp, MII_RESV)) >> 3;
E 29
I 29
		eq_value = (0x00f8 & gem_mii_read(dp, MII_RESV)) >> 3;
E 29
		max_value = min_value = eq_value;
		for (i = 1; i < 10; i++) {
D 29
			eq_value = (0x00f8 & GEM_MII_READ(dp, MII_RESV)) >> 3;
E 29
I 29
			eq_value = (0x00f8 & gem_mii_read(dp, MII_RESV)) >> 3;
E 29
			max_value = max(eq_value, max_value);
			min_value = min(eq_value, min_value);
		}

D 36
		/* 630E rule to determine the equalizer value */
E 36
I 36
		/* for 630E, rule to determine the equalizer value */
E 36
		if (rev == SIS630E_900_REV || rev == SIS630EA1_900_REV ||
		    rev == SIS630ET_900_REV) {
			if (max_value < 5) {
				eq_value = max_value;
I 36
			} else if (5 <= max_value && max_value < 15) {
				eq_value =
				    max(max_value + 1,
				    min_value + 2);
			} else if (15 <= max_value) {
				eq_value =
				    max(max_value + 5,
				    min_value + 6);
E 36
			}
D 36
			else if (5 <= max_value && max_value < 15) {
				eq_value = max(max_value + 1, min_value + 2);
			}
			else if (15 <= max_value) {
				eq_value = max(max_value + 5, min_value + 6);
			}
E 36
		}
D 36
		/* 630B0&B1 rule to determine the equalizer value */
E 36
I 36
		/* for 630B0&B1, rule to determine the equalizer value */
E 36
		else
D 36
		if (rev == SIS630A_900_REV && 
			(lp->bridge_revid == SIS630B0 ||
			 lp->bridge_revid == SIS630B1)) {
E 36
I 36
		if (rev == SIS630A_900_REV &&
		    (lp->bridge_revid == SIS630B0 ||
		    lp->bridge_revid == SIS630B1)) {
E 36

			if (max_value == 0) {
				eq_value = 3;
D 36
			}
			else {
E 36
I 36
			} else {
E 36
				eq_value = (max_value + min_value + 1)/2;
			}
		}
		/* write equalizer value and setting */
D 29
		reg14h = GEM_MII_READ(dp, MII_RESV);
		reg14h = (reg14h & ~0x00f8) | ((eq_value << 3) & 0x00f8);
		reg14h = (reg14h | 0x6000) & ~0x0200;
		GEM_MII_WRITE(dp, MII_RESV, reg14h);
E 29
I 29
		reg14h = gem_mii_read(dp, MII_RESV) & ~0x02f8;
		reg14h |= 0x6000 | (eq_value << 3);
		gem_mii_write(dp, MII_RESV, reg14h);
E 29
D 36
	}
	else {
E 36
I 36
	} else {
E 36
D 29
		reg14h = GEM_MII_READ(dp, MII_RESV);
E 29
I 29
		reg14h = (gem_mii_read(dp, MII_RESV) & ~0x4000) | 0x2000;
E 29
D 36
		if (rev== SIS630A_900_REV && 
			 (lp->bridge_revid == SIS630B0 ||
			  lp->bridge_revid == SIS630B1)) {
E 36
I 36
		if (rev == SIS630A_900_REV &&
		    (lp->bridge_revid == SIS630B0 ||
		    lp->bridge_revid == SIS630B1)) {
E 36

D 29
			GEM_MII_WRITE(dp, MII_RESV, (reg14h | 0x2200) & ~0x4000);
E 29
I 29
			reg14h |= 0x0200;
E 29
		}
D 29
		else {
			GEM_MII_WRITE(dp, MII_RESV, (reg14h | 0x2000) & ~0x4000);
		}
E 29
I 29
		gem_mii_write(dp, MII_RESV, reg14h);
E 29
	}
D 36
#endif /* TUNE_PHY_630 */
	return;
E 36
}
I 10
D 36
#endif /* i86pc */
E 36
I 36

E 36
E 10
/* ======================================================== */
/*
 * OS depend (device driver) routine
 */
/* ======================================================== */
static void
sfe_chipinfo_init_sis900(struct gem_dev *dp)
{
	int		rev;
	struct sfe_dev	*lp = (struct sfe_dev *)dp->private;

	rev = lp->revid;
D 10

E 10
I 10
D 36
#ifdef i86pc
E 36
I 36

E 36
E 10
	if (rev == SIS630E_900_REV /* 0x81 */) {
		/* sis630E */
		lp->get_mac_addr = &sfe_get_mac_addr_sis630e;
D 36
	}
	else if (rev > 0x81 &&  rev <= 0x90) {
E 36
I 36
	} else if (rev > 0x81 && rev <= 0x90) {
E 36
		/* 630S, 630EA1, 630ET, 635A */
		lp->get_mac_addr = &sfe_get_mac_addr_sis635;
D 36
	}
	else if (rev == SIS962_900_REV /* 0x91 */) {
E 36
I 36
	} else if (rev == SIS962_900_REV /* 0x91 */) {
E 36
D 7
		/* sis962 */
E 7
I 7
		/* sis962 or later */
E 7
		lp->get_mac_addr = &sfe_get_mac_addr_sis962;
D 10
	}
	else {
E 10
I 10
D 36
	} else
#endif
	{
E 36
I 36
	} else {
E 36
E 10
		/* sis900 */
		lp->get_mac_addr = &sfe_get_mac_addr_sis900;
	}

D 10
#ifdef TUNE_PHY_630
E 10
I 10
D 36
#if defined(i86pc) && defined(TUNE_PHY_630)
E 36
E 10
	lp->bridge_revid = 0;

	if (rev == SIS630E_900_REV || rev == SIS630EA1_900_REV ||
	    rev == SIS630A_900_REV || rev ==  SIS630ET_900_REV) {
		/*
		 * read host bridge revision
		 */
		dev_info_t	*bridge;
		ddi_acc_handle_t bridge_handle;
D 36
		int		reg;
E 36

D 3
		/*
		 * ddi_find_devinfo() is undocumented officially,
		 * but it is described in /usr/include/sys/sunddi.h
		 */
		if ((bridge = ddi_find_devinfo("pci1039,630", -1, 0)) == NULL) {
E 3
I 3
D 36
		if ((bridge = sfe_search_pci_dev(0x1039, 0x630) == NULL) {
E 36
I 36
		if ((bridge = sfe_search_pci_dev(0x1039, 0x630)) == NULL) {
E 36
E 3
			cmn_err(CE_WARN,
D 36
				"%s: cannot find host bridge (pci1039,630)",
				dp->name);
			goto x;
E 36
I 36
			    "%s: cannot find host bridge (pci1039,630)",
			    dp->name);
			return;
E 36
		}

		if (pci_config_setup(bridge, &bridge_handle) != DDI_SUCCESS) {
			cmn_err(CE_WARN, "%s: pci_config_setup failed",
D 36
				dp->name);
			goto x;
E 36
I 36
			    dp->name);
			return;
E 36
		}

		lp->bridge_revid =
D 36
			pci_config_get8(bridge_handle, PCI_CONF_REVID);
		pci_config_teardown(bridge_handle);
E 36
I 36
		    pci_config_get8(bridge_handle, PCI_CONF_REVID);
		pci_config_teardown(&bridge_handle);
E 36
	}
D 10
#endif /* TUNE_PHY_630 */
E 10
I 10
D 36
#endif /* i86pc && TUNE_PHY_630 */
E 10
x:
	return;
E 36
}

static int
D 36
sfe_attach_chip(struct gem_dev *dp)	
E 36
I 36
sfe_attach_chip(struct gem_dev *dp)
E 36
{
	struct sfe_dev		*lp = (struct sfe_dev *)dp->private;

I 6
D 34
	DPRINTF(4, (CE_CONT, CONS "%s: sfe_attach_chip called", dp->name));
E 34
I 34
	DPRINTF(4, (CE_CONT, CONS "!%s: %s called", dp->name, __func__));
E 34

E 6
	/* setup chip-depend get_mac_address function */
	if (lp->chip->chip_type == CHIPTYPE_SIS900) {
		sfe_chipinfo_init_sis900(dp);
D 36
	}
	else {
E 36
I 36
	} else {
E 36
		lp->get_mac_addr = &sfe_get_mac_addr_dp83815;
	}

	/* read MAC address */
D 31
	if (!gem_get_mac_addr_conf(dp)) {
		if (!((lp->get_mac_addr)(dp))) {
D 6
			cmn_err(CE_WARN,
E 6
I 6
			cmn_err(CE_WARN, 
E 6
				"%s: sfe_attach_chip: cannot get mac address",
				dp->name);
			gem_generate_macaddr(dp, dp->dev_addr.ether_addr_octet);
		}
E 31
I 31
D 36
	if (!((lp->get_mac_addr)(dp))) {
D 34
		cmn_err(CE_WARN, 
			"%s: sfe_attach_chip: cannot get mac address",
			dp->name);
E 34
I 34
		cmn_err(CE_WARN, "!%s: %s: cannot get mac address",
			dp->name, __func__);
E 34
		gem_generate_macaddr(dp, dp->dev_addr.ether_addr_octet);
E 36
I 36
	if (!(lp->get_mac_addr)(dp)) {
		cmn_err(CE_WARN,
		    "!%s: %s: failed to get factory mac address"
		    " please specify a mac address in sfe.conf",
		    dp->name, __func__);
		return (GEM_FAILURE);
E 36
E 31
	}
I 4
D 10
#ifdef NOINTR_WORKAROUND
	/* schedule first call of sfe_intr_watcher */
	lp->intr_watcher_id =
		timeout((void (*)(void *))sfe_intr_watcher,
			(void *)dp->dip, 3*ONESEC);
E 10

I 31
D 36
#ifdef GEM_CONFIG_VLAN
E 36
I 36
	DPRINTF(-1, (CE_CONT, "!%s: %s: mac:%02x:%02x:%02x:%02x:%02x:%02x",
	    dp->name, __func__,
	    dp->dev_addr.ether_addr_octet[0],
	    dp->dev_addr.ether_addr_octet[1],
	    dp->dev_addr.ether_addr_octet[2],
	    dp->dev_addr.ether_addr_octet[3],
	    dp->dev_addr.ether_addr_octet[4],
	    dp->dev_addr.ether_addr_octet[5]));

E 36
	if (lp->chip->chip_type == CHIPTYPE_DP83815) {
I 36
		dp->mii_phy_addr = -1;	/* no need to scan PHY */
E 36
		dp->misc_flag |= GEM_VLAN_SOFT;
I 36
		dp->txthr += 4; /* VTAG_SIZE */
E 36
	}
D 36
#endif
E 36
I 36
	dp->txthr = min(dp->txthr, TXFIFOSIZE - 2);

E 36
E 31
D 10
#endif
E 10
E 4
D 29
	return 0;
E 29
I 29
	return (GEM_SUCCESS);
E 29
}

static int
sfeattach(dev_info_t *dip, ddi_attach_cmd_t cmd)
{
I 28
	int			unit;
	const char		*drv_name;
E 28
	int			i;
I 22
D 28
	int			n;
E 22
	ddi_iblock_cookie_t	c;
E 28
	ddi_acc_handle_t	conf_handle;
D 28
	uint16_t		comm;
	int			ret;
	int			vid;
	int			did;
D 20
	int			svid;
	int			ssid;
E 20
	int			rev;
	int			unit;
E 28
I 28
	uint16_t		vid;
	uint16_t		did;
	uint8_t			rev;
#ifdef DEBUG_LEVEL
	uint32_t		iline;
	uint8_t			latim;
#endif
E 28
	struct chip_info	*p;
D 28
	int			val;
D 22
	int			len;
E 22
I 22
	u_int			len;
E 22
	struct pci_phys_spec	*regs;
	const char		*drv_name;
E 28
	struct gem_dev		*dp;
	struct sfe_dev		*lp;
D 35
	void			*base;
E 35
I 35
	caddr_t			base;
E 35
D 28
	ddi_acc_handle_t	regs_handle;
E 28
I 28
	ddi_acc_handle_t	regs_ha;
E 28
D 26
	struct gem_conf		gc;
E 26
I 26
	struct gem_conf		*gcp;
E 26
I 4
D 28
	uint8_t			cap_ptr;
	uint32_t		cap;
	uint32_t		ps;
E 28
D 6
	uint32_t		ilr;
E 6
E 4

D 28
	unit =  ddi_get_instance(dip);
E 28
I 28
D 36
	unit     = ddi_get_instance(dip);
E 36
I 36
	unit = ddi_get_instance(dip);
E 36
E 28
	drv_name = ddi_driver_name(dip);

D 6
	DPRINTF(3, (CE_CONT, "%s%d: sfeattach: called", drv_name, unit));
E 6
I 6
	DPRINTF(3, (CE_CONT, CONS "%s%d: sfeattach: called", drv_name, unit));
E 6

D 28
	if (cmd == DDI_ATTACH) {
		/*
		 * Check if chip is supported.
		 */
		if (pci_config_setup(dip, &conf_handle) != DDI_SUCCESS) {
			cmn_err(CE_WARN, "%s%d: ddi_regs_map_setup failed",
				drv_name, unit);
			goto err;
		}
		vid  = pci_config_get16(conf_handle, PCI_CONF_VENID);
		did  = pci_config_get16(conf_handle, PCI_CONF_DEVID);
D 20
		svid = pci_config_get16(conf_handle, PCI_CONF_SUBVENID);
		ssid = pci_config_get16(conf_handle, PCI_CONF_SUBSYSID);
E 20
		rev  = pci_config_get16(conf_handle, PCI_CONF_REVID);
E 28
I 28
	/*
	 * Common codes after power-up
	 */
	if (pci_config_setup(dip, &conf_handle) != DDI_SUCCESS) {
		cmn_err(CE_WARN, "%s%d: ddi_regs_map_setup failed",
D 36
			drv_name, unit);
E 36
I 36
		    drv_name, unit);
E 36
		goto err;
	}

	vid  = pci_config_get16(conf_handle, PCI_CONF_VENID);
	did  = pci_config_get16(conf_handle, PCI_CONF_DEVID);
	rev  = pci_config_get16(conf_handle, PCI_CONF_REVID);
#ifdef DEBUG_LEVEL
D 36
	iline =	pci_config_get32(conf_handle, PCI_CONF_ILINE),
E 36
I 36
	iline = pci_config_get32(conf_handle, PCI_CONF_ILINE);
E 36
	latim = pci_config_get8(conf_handle, PCI_CONF_LATENCY_TIMER);
#endif
E 28
D 10
#ifdef DEBUG_BUILT_IN_SIS900
E 10
I 10
D 36
#if defined(i86pc) && defined(DEBUG_BUILT_IN_SIS900)
E 36
I 36
#ifdef DEBUG_BUILT_IN_SIS900
E 36
E 10
D 28
		rev  = SIS630E_900_REV;
		rev  = SIS630ET_900_REV;
E 28
I 28
	rev  = SIS630E_900_REV;
D 36
	rev  = SIS630ET_900_REV;
E 36
E 28
#endif
D 28
		comm = pci_config_get16(conf_handle, PCI_CONF_COMM);
		comm |= PCI_COMM_IO | PCI_COMM_ME;
		pci_config_put16(conf_handle, PCI_CONF_COMM, comm);
E 28
I 28
	for (i = 0, p = sfe_chiptbl; i < CHIPTABLESIZE; i++, p++) {
		if (p->venid == vid && p->devid == did) {
			/* found */
			goto chip_found;
		}
	}
E 28

I 4
D 28
		/* ensure D0 mode */
		cap_ptr = pci_config_get8(conf_handle, PCI_CONF_CAP_PTR);
		while (cap_ptr != 0) {
			/* read capability header */
			cap = pci_config_get32(conf_handle, cap_ptr);
			if ((cap & 0xff) == PCI_CAP_ID_PM) {
				/*
				 * power management capability found
				 * ensure D0 mode
				 */
D 7
				ps = pci_config_get32(conf_handle, cap_ptr + 4);
E 7
I 7
				ps = pci_config_get32(conf_handle, cap_ptr+4);
E 28
I 28
	/* Not found */
D 36
	cmn_err(CE_WARN, 
		"%s%d: sfe_attach: wrong PCI venid/devid (0x%x, 0x%x)",
		drv_name, unit, vid, did);
E 36
I 36
	cmn_err(CE_WARN,
	    "%s%d: sfe_attach: wrong PCI venid/devid (0x%x, 0x%x)",
	    drv_name, unit, vid, did);
E 36
	pci_config_teardown(&conf_handle);
	goto err;
E 28
E 7

D 28
				DPRINTF(0, (CE_CONT,
D 6
				"!%s%d: pmc found at 0x%x: ps: 0x%08x",
E 6
I 6
				CONS "%s%d: pmc found at 0x%x: ps: 0x%08x",
E 6
				drv_name, unit, cap_ptr, ps));
E 28
I 28
chip_found:
	pci_config_put16(conf_handle, PCI_CONF_COMM,
D 36
		PCI_COMM_IO | PCI_COMM_MAE | PCI_COMM_ME |
			pci_config_get16(conf_handle, PCI_CONF_COMM));
E 36
I 36
	    PCI_COMM_IO | PCI_COMM_MAE | PCI_COMM_ME |
	    pci_config_get16(conf_handle, PCI_CONF_COMM));
E 36
E 28

D 28
				ps &= ~PCI_PMCSR_STATE_MASK;
D 7
				pci_config_put32(conf_handle, cap_ptr + 4, ps);
E 7
I 7
				pci_config_put32(conf_handle, cap_ptr+4, ps);
E 7
				break;
			}
			/* get next_ptr */
			cap_ptr = (cap >> 8) & 0xff;
		}
E 28
I 28
	/* ensure D0 mode */
	(void) gem_pci_set_power_state(dip, conf_handle, PCI_PMCSR_D0);
E 28

D 6
		ilr = pci_config_get32(conf_handle, PCI_CONF_ILINE);
		DPRINTF(0, (CE_CONT, "!%s%d: ilr 0x%08x", drv_name, unit, ilr));
E 6
I 6
D 7
		DPRINTF(0, (CE_CONT, CONS "%s%d: ilr 0x%08x, latency_timer:0x%02x",
E 7
I 7
D 28
		DPRINTF(0, (CE_CONT,
			CONS "%s%d: ilr 0x%08x, latency_timer:0x%02x",
E 7
			drv_name, unit,
			pci_config_get32(conf_handle, PCI_CONF_ILINE),
			pci_config_get8(conf_handle, PCI_CONF_LATENCY_TIMER)));
E 28
I 28
	pci_config_teardown(&conf_handle);
E 28
E 6

E 4
D 28
		pci_config_teardown(&conf_handle);
E 28
I 28
	switch (cmd) {
	case DDI_RESUME:
D 29
		return gem_resume(dip);
E 29
I 29
		return (gem_resume(dip));
E 29
E 28

D 28
		for (i = 0, p = sfe_chiptbl; i < CHIPTABLESIZE; i++, p++) {
D 20
			if ((p->venid == vid && p->devid == did) ||
			    (p->venid == svid && p->devid == ssid)) {
E 20
I 20
			if (p->venid == vid && p->devid == did) {
E 20
				/* found */
				goto chip_found;
			}
		}
E 28
I 28
	case DDI_ATTACH:
E 28

D 28
		/* Not found */
D 6
		cmn_err(CE_WARN,
E 6
I 6
		cmn_err(CE_WARN, 
E 6
			"%s%d: sfe_attach: wrong PCI venid/devid (0x%x, 0x%x)",
			drv_name, unit, vid, did);
		goto err;
chip_found:
E 28
I 28
		DPRINTF(0, (CE_CONT,
D 36
			CONS "%s%d: ilr 0x%08x, latency_timer:0x%02x",
			drv_name, unit, iline, latim));
E 36
I 36
		    CONS "%s%d: ilr 0x%08x, latency_timer:0x%02x",
		    drv_name, unit, iline, latim));

E 36
E 28
		/*
		 * Map in the device registers.
		 */
D 36

E 36
D 28
		/* Search IO-range or memory-range to be mapped */
		regs = NULL;
		len  = 0;
I 22
D 26
#ifdef OBSOLUTE_DDI_GETPROP
E 22
		if (ddi_getlongprop(DDI_DEV_T_ANY, dip, DDI_PROP_DONTPASS,
			"reg", (caddr_t)&regs, &len) != DDI_PROP_SUCCESS) {
			cmn_err(CE_WARN, "%s%d: failed to get reg property",
				drv_name, unit);
			goto err;
		}
I 22
		n = len / sizeof(struct pci_phys_spec);
#else
E 26
		if (ddi_prop_lookup_int_array(
			DDI_DEV_T_ANY, dip, DDI_PROP_DONTPASS,
			"reg", (int **)&regs, &len) != DDI_PROP_SUCCESS) {
E 22

I 22
			cmn_err(CE_WARN,
			"%s%d: failed to get reg property", drv_name, unit);
			goto err;
		}
		n = len / (sizeof(struct pci_phys_spec) / sizeof(int));
D 26
#endif
E 26
I 26

E 26
E 22
		ASSERT(regs != NULL && len > 0);
D 9
#if DEBUG_LEVEL > 0
E 9
I 9
#if DEBUG_LEVEL > 4
E 9
D 22
		for (i = 0; i <len / sizeof(struct pci_phys_spec); i++) {
E 22
I 22
		for (i = 0; i < n; i++) {
E 22
			cmn_err(CE_CONT,
D 6
				"!%s%d: regs[%d]: %08x.%08x.%08x.%08x.%08x",
E 6
I 6
				CONS "%s%d: regs[%d]: %08x.%08x.%08x.%08x.%08x",
E 6
				drv_name, unit, i,
				regs[i].pci_phys_hi,
				regs[i].pci_phys_mid,
				regs[i].pci_phys_low,
				regs[i].pci_size_hi,
				regs[i].pci_size_low);
		}
#endif
D 22
		for (i = 0; i <len / sizeof(struct pci_phys_spec); i++) {
E 22
I 22
		for (i = 0; i < n; i++) {
E 22
			if ((regs[i].pci_phys_hi & PCI_REG_ADDR_M) == 
E 28
I 28
		if (gem_pci_regs_map_setup(dip,
E 28
D 18
			    PCI_ADDR_IO) {
				/* it's I/O space */
E 18
I 18
D 36
#ifdef MAP_MEM
D 28
			    PCI_ADDR_MEM32
E 28
I 28
D 29
			PCI_ADDR_MEM32,
E 29
I 29
			PCI_ADDR_MEM32, PCI_ADDR_MASK,
E 29
E 28
#else
D 28
			    PCI_ADDR_IO
E 28
I 28
D 29
			PCI_ADDR_IO,
E 29
I 29
			PCI_ADDR_IO, PCI_ADDR_MASK,
E 29
E 28
#endif
D 28
			) {
I 22
D 26
#ifdef ONSOLUTE_DDI_GETPROP
E 22
E 18
				kmem_free(regs, len);
I 22
#else
E 26
				ddi_prop_free(regs);
D 26
#endif
E 26
E 22
D 18
				goto io_range_found;
E 18
I 18
				goto map_space_found;
E 18
			}
		}
D 18
		cmn_err(CE_WARN, "%s%d: failed to find IO space",
E 18
I 18
		cmn_err(CE_WARN,
#ifdef MAP_MEM
			"%s%d: failed to find MEM32 space",
#else
			"%s%d: failed to find IO space",
#endif
E 18
			drv_name, unit);
I 22
D 26
#ifdef ONSOLUTE_DDI_GETPROP
E 22
		kmem_free(regs, len);
I 22
#else
E 26
I 26

E 26
		ddi_prop_free(regs);
D 26
#endif
E 26
E 22
		goto err;
D 18
io_range_found:
E 18

I 18
map_space_found:
E 18
		if (ddi_regs_map_setup(dip, i, (caddr_t *)&base,
D 7
			0, 0, &gem_dev_attr, &regs_handle)) {
E 7
I 7
			0, 0, &sfe_dev_attr, &regs_handle)) {
E 28
I 28
D 35
			&sfe_dev_attr, (caddr_t *)&base, &regs_ha) !=
E 35
I 35
			&sfe_dev_attr, &base, &regs_ha) !=
E 35
								DDI_SUCCESS) {
E 28
E 7
			cmn_err(CE_WARN, "%s%d: ddi_regs_map_setup failed",
				drv_name, unit);
E 36
I 36
		    (sfe_use_pcimemspace && p->chip_type == CHIPTYPE_DP83815)
		    ? PCI_ADDR_MEM32 : PCI_ADDR_IO, PCI_ADDR_MASK,
		    &sfe_dev_attr, &base, &regs_ha) != DDI_SUCCESS) {
			cmn_err(CE_WARN,
			    "%s%d: ddi_regs_map_setup failed",
			    drv_name, unit);
E 36
			goto err;
		}
I 28

E 28
		/*
D 36
		 * construct gem configration
E 36
I 36
		 * construct gem configuration
E 36
		 */
I 3
D 26
		bzero(&gc, sizeof(gc));
E 26
I 26
D 36
		gcp = (struct gem_conf *) kmem_zalloc(sizeof(*gcp), KM_SLEEP);
E 36
I 36
		gcp = kmem_zalloc(sizeof (*gcp), KM_SLEEP);
E 36
E 26
E 3

		/* name */
D 26
		sprintf(gc.gc_name, "%s%d", drv_name, unit);
E 26
I 26
D 36
		sprintf(gcp->gc_name, "%s%d", drv_name, unit);
E 36
I 36
		(void) sprintf(gcp->gc_name, "%s%d", drv_name, unit);
E 36
E 26

		/* consistency on tx and rx */
D 26
		gc.gc_tx_buf_align = sizeof(uint8_t) - 1;
		gc.gc_tx_max_frags = MAXTXFRAGS;
		gc.gc_tx_desc_size = sizeof(struct sfe_desc) * TX_RING_SIZE;
		gc.gc_tx_ring_size = TX_RING_SIZE;
		gc.gc_tx_buf_size  = TX_BUF_SIZE;
		gc.gc_tx_max_descs_per_pkt = gc.gc_tx_max_frags;
		gc.gc_tx_auto_pad  = TRUE;
		gc.gc_tx_copy_thresh = sfe_tx_copy_thresh;
E 26
I 26
D 36
		gcp->gc_tx_buf_align = sizeof(uint8_t) - 1;
E 36
I 36
		gcp->gc_tx_buf_align = sizeof (uint8_t) - 1;
E 36
		gcp->gc_tx_max_frags = MAXTXFRAGS;
D 29
		gcp->gc_tx_desc_size = sizeof(struct sfe_desc) * TX_RING_SIZE;
		gcp->gc_tx_ring_size = TX_RING_SIZE;
		gcp->gc_tx_buf_size  = TX_BUF_SIZE;
E 29
		gcp->gc_tx_max_descs_per_pkt = gcp->gc_tx_max_frags;
D 29
		gcp->gc_tx_auto_pad  = TRUE;
E 29
I 29
		gcp->gc_tx_desc_unit_shift = 4;	/* 16 byte */
		gcp->gc_tx_buf_size  = TX_BUF_SIZE;
		gcp->gc_tx_buf_limit = gcp->gc_tx_buf_size;
		gcp->gc_tx_ring_size = TX_RING_SIZE;
D 36
		gcp->gc_tx_ring_limit= gcp->gc_tx_ring_size;
E 36
I 36
		gcp->gc_tx_ring_limit = gcp->gc_tx_ring_size;
E 36
		gcp->gc_tx_auto_pad  = B_TRUE;
E 29
		gcp->gc_tx_copy_thresh = sfe_tx_copy_thresh;
E 26
D 29

E 29
I 29
D 33
#ifdef CONFIG_OO
		gcp->gc_tx_desc_write_oo = B_TRUE;
#else
		gcp->gc_tx_desc_write_oo = B_FALSE;
#endif
E 33
I 33
D 36
		gcp->gc_tx_desc_write_oo = (gcp->gc_tx_max_frags == 1);

E 33
E 29
D 26
		gc.gc_rx_buf_align = sizeof(uint8_t)-1;
D 11
		gc.gc_rx_max_frags = 1;
E 11
I 11
		gc.gc_rx_max_frags = sfe_dma_attr_rxbuf.dma_attr_sgllen;
E 11
		gc.gc_rx_desc_size = sizeof(struct sfe_desc) * RX_RING_SIZE;
		gc.gc_rx_ring_size = RX_RING_SIZE;
D 20
		gc.gc_rx_buf_size  = RX_RING_SIZE;
E 20
I 20
		gc.gc_rx_buf_size  = RX_BUF_SIZE;
E 20
D 11
		gc.gc_rx_max_descs_per_pkt = gc.gc_rx_max_frags;
E 11
I 11
		gc.gc_rx_max_descs_per_pkt = sfe_dma_attr_rxbuf.dma_attr_sgllen;
E 11
		gc.gc_rx_copy_thresh = sfe_rx_copy_thresh;
D 14
		gc.gc_rx_buf_max  = gc.gc_rx_buf_size*10;
E 14
I 14
D 24
		gc.gc_rx_buf_max  = gc.gc_rx_buf_size;
E 24
I 24
		gc.gc_rx_buf_max  = gc.gc_rx_buf_size + 1;
E 26
I 26
D 28
		gcp->gc_rx_buf_align = sizeof(uint8_t)-1;
E 28
I 28
		gcp->gc_rx_buf_align = sizeof(uint8_t) - 1;
E 36
I 36
#ifdef CONFIG_OO
		gcp->gc_tx_desc_write_oo = B_TRUE;
#endif
		gcp->gc_rx_buf_align = sizeof (uint8_t) - 1;
E 36
E 28
		gcp->gc_rx_max_frags = MAXRXFRAGS;
D 29
		gcp->gc_rx_desc_size = sizeof(struct sfe_desc) * RX_RING_SIZE;
E 29
I 29
		gcp->gc_rx_desc_unit_shift = 4;
E 29
		gcp->gc_rx_ring_size = RX_RING_SIZE;
D 29
		gcp->gc_rx_buf_size  = RX_BUF_SIZE;
		gcp->gc_rx_max_descs_per_pkt = gcp->gc_rx_max_frags;
E 29
I 29
		gcp->gc_rx_buf_max   = RX_BUF_SIZE;
E 29
		gcp->gc_rx_copy_thresh = sfe_rx_copy_thresh;
D 29
		gcp->gc_rx_buf_max   = gcp->gc_rx_buf_size + 1;
E 29
E 26
E 24
E 14

		/* map attributes */
D 7
		gc.gc_dev_attr = gem_dev_attr;
		gc.gc_buf_attr = gem_dev_attr;
E 7
I 7
D 24
		gc.gc_dev_attr  = sfe_dev_attr;
		gc.gc_buf_attr  = sfe_buf_attr;
		gc.gc_desc_attr = sfe_dev_attr;
E 24
I 24
D 26
		STRUCT_COPY(gc.gc_dev_attr, sfe_dev_attr);
		STRUCT_COPY(gc.gc_buf_attr, sfe_buf_attr);
		STRUCT_COPY(gc.gc_desc_attr, sfe_buf_attr);
E 26
I 26
D 31
		STRUCT_COPY(gcp->gc_dev_attr, sfe_dev_attr);
		STRUCT_COPY(gcp->gc_buf_attr, sfe_buf_attr);
		STRUCT_COPY(gcp->gc_desc_attr, sfe_dev_attr);
E 31
I 31
		gcp->gc_dev_attr = sfe_dev_attr;
		gcp->gc_buf_attr = sfe_buf_attr;
		gcp->gc_desc_attr = sfe_buf_attr;
E 31
E 26
E 24
E 7

		/* dma attributes */
D 24
		gc.gc_dma_attr_desc  = sfe_dma_attr_nosc;
		gc.gc_dma_attr_txbuf = sfe_dma_attr_txbuf;
D 11
		if (gc.gc_rx_max_frags > 1) {
			gc.gc_dma_attr_rxbuf = sfe_dma_attr_rxbuf;
		} else {
			ASSERT(gc.gc_rx_max_frags == 1);
			gc.gc_dma_attr_rxbuf = sfe_dma_attr_nosc;
		}
E 11
I 11
		gc.gc_dma_attr_rxbuf = sfe_dma_attr_rxbuf;
E 24
I 24
D 26
		STRUCT_COPY(gc.gc_dma_attr_desc, sfe_dma_attr_desc);
		STRUCT_COPY(gc.gc_dma_attr_txbuf, sfe_dma_attr_txbuf);
		STRUCT_COPY(gc.gc_dma_attr_rxbuf, sfe_dma_attr_rxbuf);
E 26
I 26
D 31
		STRUCT_COPY(gcp->gc_dma_attr_desc, sfe_dma_attr_desc);
E 31
I 31
		gcp->gc_dma_attr_desc = sfe_dma_attr_desc;
E 31
E 26
E 24
E 11

I 26
D 31
		STRUCT_COPY(gcp->gc_dma_attr_txbuf, sfe_dma_attr_buf);
E 31
I 31
		gcp->gc_dma_attr_txbuf = sfe_dma_attr_buf;
E 31
		gcp->gc_dma_attr_txbuf.dma_attr_align = gcp->gc_tx_buf_align+1;
		gcp->gc_dma_attr_txbuf.dma_attr_sgllen = gcp->gc_tx_max_frags;

D 31
		STRUCT_COPY(gcp->gc_dma_attr_rxbuf, sfe_dma_attr_buf);
E 31
I 31
		gcp->gc_dma_attr_rxbuf = sfe_dma_attr_buf;
E 31
		gcp->gc_dma_attr_rxbuf.dma_attr_align = gcp->gc_rx_buf_align+1;
		gcp->gc_dma_attr_rxbuf.dma_attr_sgllen = gcp->gc_rx_max_frags;

E 26
		/* time out parameters */
D 12
		gc.gc_tx_timeout = 5*ONESEC;
E 12
I 12
D 17
		gc.gc_tx_timeout = 2*ONESEC;
E 17
I 17
D 26
		gc.gc_tx_timeout = 5*ONESEC;
E 17
E 12
		gc.gc_tx_timeout_interval = ONESEC;
E 26
I 26
D 28
		gcp->gc_tx_timeout = 5*ONESEC;
E 28
I 28
		gcp->gc_tx_timeout = 3*ONESEC;
E 28
		gcp->gc_tx_timeout_interval = ONESEC;
I 36
		if (p->chip_type == CHIPTYPE_DP83815) {
			/* workaround for tx hang */
			gcp->gc_tx_timeout_interval = ONESEC/20; /* 50mS */
		}
E 36
E 26

		/* MII timeout parameters */
D 26
		gc.gc_mii_link_watch_interval = ONESEC;
I 12
		gc.gc_mii_an_watch_interval   = ONESEC/5;
E 12
		gc.gc_mii_reset_timeout = MII_RESET_TIMEOUT;	/* 1 sec */
		gc.gc_mii_an_timeout = MII_AN_TIMEOUT;	/* 5 sec */
		gc.gc_mii_an_wait = 0;	/* 0 for default, 3 for via rhine */
		gc.gc_mii_linkdown_timeout = MII_LINKDOWN_TIMEOUT;
E 26
I 26
		gcp->gc_mii_link_watch_interval = ONESEC;
		gcp->gc_mii_an_watch_interval   = ONESEC/5;
		gcp->gc_mii_reset_timeout = MII_RESET_TIMEOUT;	/* 1 sec */
		gcp->gc_mii_an_timeout = MII_AN_TIMEOUT;	/* 5 sec */
		gcp->gc_mii_an_wait = 0;
		gcp->gc_mii_linkdown_timeout = MII_LINKDOWN_TIMEOUT;
E 26

D 24
		/* workaround for various PHY */
E 24
I 24
		/* setting for general PHY */
E 24
D 12
		gc.gc_mii_need_an_delay   = FALSE;
E 12
I 12
D 26
		gc.gc_mii_an_delay	  =  0;
E 12
D 24
		gc.gc_mii_linkdown_action = MII_ACTION_NONE;
		gc.gc_mii_dont_reset      = TRUE;
E 24
I 24
		gc.gc_mii_linkdown_action = MII_ACTION_RESET;
		gc.gc_mii_dont_reset      = FALSE;
E 26
I 26
D 36
		gcp->gc_mii_an_delay	  =  0;
E 36
I 36
		gcp->gc_mii_an_delay = 0;
E 36
D 28
		gcp->gc_mii_linkdown_action = MII_ACTION_RESET;
E 28
I 28
		gcp->gc_mii_linkdown_action = MII_ACTION_RSA;
		gcp->gc_mii_linkdown_timeout_action = MII_ACTION_RESET;
E 28
D 29
		gcp->gc_mii_dont_reset      = FALSE;
E 29
I 29
D 36
		gcp->gc_mii_dont_reset      = B_FALSE;
E 36
I 36
		gcp->gc_mii_dont_reset = B_FALSE;
E 36
E 29
E 26
E 24


		/* I/O methods */

		/* mac operation */
D 26
		gc.gc_attach_chip = &sfe_attach_chip;
E 26
I 26
		gcp->gc_attach_chip = &sfe_attach_chip;
E 26
D 7
		gc.gc_reset_chip  = &sfe_reset_chip;
E 7
I 7
		if (p->chip_type == CHIPTYPE_DP83815) {
D 26
			gc.gc_reset_chip  = &sfe_reset_chip_dp83815;
E 26
I 26
D 28
			gcp->gc_reset_chip  = &sfe_reset_chip_dp83815;
E 28
I 28
			gcp->gc_reset_chip = &sfe_reset_chip_dp83815;
E 28
E 26
		} else {
D 26
			gc.gc_reset_chip  = &sfe_reset_chip_sis900;
E 26
I 26
D 28
			gcp->gc_reset_chip  = &sfe_reset_chip_sis900;
E 28
I 28
			gcp->gc_reset_chip = &sfe_reset_chip_sis900;
E 28
E 26
		}
E 7
D 26
		gc.gc_init_chip   = &sfe_init_chip;
		gc.gc_start_chip  = &sfe_start_chip;
		gc.gc_stop_chip   = &sfe_stop_chip;
E 26
I 26
D 28
		gcp->gc_init_chip   = &sfe_init_chip;
		gcp->gc_start_chip  = &sfe_start_chip;
		gcp->gc_stop_chip   = &sfe_stop_chip;
E 28
I 28
		gcp->gc_init_chip  = &sfe_init_chip;
		gcp->gc_start_chip = &sfe_start_chip;
		gcp->gc_stop_chip  = &sfe_stop_chip;
E 28
E 26
I 7
#ifdef USE_MULTICAST_HASHTBL
D 26
		gc.gc_multicast_hash = &sfe_mcast_hash;
E 26
I 26
		gcp->gc_multicast_hash = &sfe_mcast_hash;
E 26
#endif
E 7
		if (p->chip_type == CHIPTYPE_DP83815) {
D 26
			gc.gc_set_rx_filter = &sfe_set_rx_filter_dp83815;
E 26
I 26
			gcp->gc_set_rx_filter = &sfe_set_rx_filter_dp83815;
E 26
		} else {
D 26
			gc.gc_set_rx_filter = &sfe_set_rx_filter_sis900;
E 26
I 26
			gcp->gc_set_rx_filter = &sfe_set_rx_filter_sis900;
E 26
		}
D 26
		gc.gc_set_media   = &sfe_set_media;
		gc.gc_get_stats   = &sfe_get_stats;
		gc.gc_interrupt   = &sfe_interrupt;
E 26
I 26
D 28
		gcp->gc_set_media   = &sfe_set_media;
		gcp->gc_get_stats   = &sfe_get_stats;
		gcp->gc_interrupt   = &sfe_interrupt;
E 28
I 28
		gcp->gc_set_media = &sfe_set_media;
		gcp->gc_get_stats = &sfe_get_stats;
		gcp->gc_interrupt = &sfe_interrupt;
E 28
E 26

		/* descriptor operation */
D 26
		gc.gc_tx_desc_write = &sfe_tx_desc_write;
		gc.gc_rx_desc_write = &sfe_rx_desc_write;
E 26
I 26
		gcp->gc_tx_desc_write = &sfe_tx_desc_write;
I 29
D 36
		gcp->gc_tx_start      = &sfe_tx_start;
E 36
I 36
		gcp->gc_tx_start = &sfe_tx_start;
E 36
E 29
		gcp->gc_rx_desc_write = &sfe_rx_desc_write;
I 29
D 36
		gcp->gc_rx_start      = NULL;
E 36
I 36
		gcp->gc_rx_start = NULL;
E 36
E 29
E 26

D 26
		gc.gc_tx_desc_stat = &sfe_tx_desc_stat;
		gc.gc_rx_desc_stat = &sfe_rx_desc_stat;
		gc.gc_tx_desc_init = &sfe_tx_desc_init;
		gc.gc_rx_desc_init = &sfe_rx_desc_init;
		gc.gc_tx_desc_clean = &sfe_tx_desc_clean;
		gc.gc_rx_desc_clean = &sfe_rx_desc_clean;
E 26
I 26
		gcp->gc_tx_desc_stat = &sfe_tx_desc_stat;
		gcp->gc_rx_desc_stat = &sfe_rx_desc_stat;
		gcp->gc_tx_desc_init = &sfe_tx_desc_init;
		gcp->gc_rx_desc_init = &sfe_rx_desc_init;
		gcp->gc_tx_desc_clean = &sfe_tx_desc_clean;
		gcp->gc_rx_desc_clean = &sfe_rx_desc_clean;
E 26
I 3
D 12
		gc.gc_get_packet    = &gem_get_packet_default;
E 12
E 3

		/* mii operations */
		if (p->chip_type == CHIPTYPE_DP83815) {
D 26
			gc.gc_mii_init  = &sfe_mii_init_dp83815;
D 4
			gc.gc_mii_config= &gem_mii_config_default;
E 4
I 4
			gc.gc_mii_config= &sfe_mii_config_dp83815;
E 4
			gc.gc_mii_sync  = &sfe_mii_sync_dp83815;
			gc.gc_mii_read  = &sfe_mii_read_dp83815;
			gc.gc_mii_write = &sfe_mii_write_dp83815;
D 12
			gc.gc_mii_tune_phy = 0;
			gc.gc_flow_control = TRUE;
E 12
I 12
			gc.gc_mii_tune_phy = NULL;
E 12
I 6
D 24
			gc.gc_flow_control = FALSE;
E 24
I 24
			gc.gc_flow_control = FLOW_CONTROL_NONE;
E 26
I 26
D 34
			gcp->gc_mii_init  = &sfe_mii_init_dp83815;
E 34
I 34
			gcp->gc_mii_probe = &sfe_mii_probe_dp83815;
D 36
			gcp->gc_mii_init  = NULL;
E 34
			gcp->gc_mii_config= &sfe_mii_config_dp83815;
			gcp->gc_mii_sync  = &sfe_mii_sync_dp83815;
			gcp->gc_mii_read  = &sfe_mii_read_dp83815;
E 36
I 36
			gcp->gc_mii_init = &sfe_mii_init_dp83815;
			gcp->gc_mii_config = &sfe_mii_config_dp83815;
			gcp->gc_mii_sync = &sfe_mii_sync_dp83815;
			gcp->gc_mii_read = &sfe_mii_read_dp83815;
E 36
			gcp->gc_mii_write = &sfe_mii_write_dp83815;
			gcp->gc_mii_tune_phy = NULL;
			gcp->gc_flow_control = FLOW_CONTROL_NONE;
E 26
E 24
E 6
D 36
		}
		else {
D 26
			gc.gc_mii_init  = &sfe_mii_init_sis900;
			gc.gc_mii_config= &sfe_mii_config_sis900;
			gc.gc_mii_sync  = &sfe_mii_sync_sis900;
			gc.gc_mii_read  = &sfe_mii_read_sis900;
			gc.gc_mii_write = &sfe_mii_write_sis900;
E 26
I 26
D 34
			gcp->gc_mii_init  = &sfe_mii_init_sis900;
E 34
I 34
			gcp->gc_mii_probe = &sfe_mii_probe_sis900;
			gcp->gc_mii_init  = NULL;
E 34
			gcp->gc_mii_config= &sfe_mii_config_sis900;
			gcp->gc_mii_sync  = &sfe_mii_sync_sis900;
			gcp->gc_mii_read  = &sfe_mii_read_sis900;
E 36
I 36
		} else {
			gcp->gc_mii_probe = &gem_mii_probe_default;
			gcp->gc_mii_init = NULL;
			gcp->gc_mii_config = &sfe_mii_config_sis900;
			gcp->gc_mii_sync = &sfe_mii_sync_sis900;
			gcp->gc_mii_read = &sfe_mii_read_sis900;
E 36
			gcp->gc_mii_write = &sfe_mii_write_sis900;
E 26
I 10
D 36
#ifdef i86pc
E 36
E 10
D 26
			gc.gc_mii_tune_phy = &sfe_set_eq_sis630;
E 26
I 26
			gcp->gc_mii_tune_phy = &sfe_set_eq_sis630;
E 26
I 10
D 36
#endif
E 36
E 10
D 24
			gc.gc_flow_control = TRUE;
E 24
I 24
D 25
			gc.gc_flow_control = FLOW_CONTROL_BOTH;
E 25
I 25
D 26
			gc.gc_flow_control = FLOW_CONTROL_SYMMETRIC;
E 26
I 26
D 34
			gcp->gc_flow_control = FLOW_CONTROL_SYMMETRIC;
E 34
I 34
			gcp->gc_flow_control = FLOW_CONTROL_RX_PAUSE;
E 34
E 26
E 25
E 24
		}

D 36
		lp = (struct sfe_dev *)
			kmem_zalloc(sizeof(struct sfe_dev), KM_SLEEP);
E 36
I 36
		gcp->gc_default_mtu = ETHERMTU;
		gcp->gc_min_mtu = ETHERMIN - sizeof (struct ether_header);
		gcp->gc_max_mtu = 0xfff - sizeof (struct ether_header) - 8;
E 36

D 36
		lp->chip  = p;
E 36
I 36
		lp = kmem_zalloc(sizeof (*lp), KM_SLEEP);
		lp->chip = p;
E 36
		lp->revid = rev;
D 36
		lp->cr    = 0;
E 36
I 36
		lp->our_intr_bits = 0;
		lp->isr_pended = 0;
E 36

D 5
		DPRINTF(0, (CE_CONT, "%s%d: chip:%s rev:0x%02x",
E 5
I 5
D 6
		DPRINTF(0, (CE_CONT, "!%s%d: chip:%s rev:0x%02x",
E 6
I 6
D 34
		DPRINTF(0, (CE_CONT, CONS "%s%d: chip:%s rev:0x%02x",
E 6
E 5
			drv_name, unit, p->chip_name, rev));
E 34
I 34
		cmn_err(CE_CONT, CONS "%s%d: chip:%s rev:0x%02x",
D 36
			drv_name, unit, p->chip_name, rev);
E 36
I 36
		    drv_name, unit, p->chip_name, rev);
E 36
E 34
D 4

E 4
I 4
D 10
#ifdef NOINTR_WORKAROUND
E 10
I 10

E 10
D 36
		ddi_set_driver_private(dip, NULL);
D 10
#endif
E 10
I 10

E 36
E 10
E 4
D 26
		dp = gem_do_attach(dip, &gc, base, &regs_handle,
E 26
I 26
D 28
		dp = gem_do_attach(dip, gcp, base, &regs_handle,
E 28
I 28
D 34
		dp = gem_do_attach(dip, gcp, base, &regs_ha,
E 34
I 34
		dp = gem_do_attach(dip, 0, gcp, base, &regs_ha,
E 34
E 28
E 26
D 36
			lp, sizeof(*lp));
I 26
		kmem_free(gcp, sizeof(*gcp));
E 36
I 36
		    lp, sizeof (*lp));
		kmem_free(gcp, sizeof (*gcp));
E 36
E 26

		if (dp == NULL) {
			goto err_freelp;
		}

D 29
		return DDI_SUCCESS;
E 29
I 29
		return (DDI_SUCCESS);
E 29

err_freelp:
D 36
		kmem_free(lp, sizeof(struct sfe_dev));
E 36
I 36
		kmem_free(lp, sizeof (struct sfe_dev));
E 36
err:
D 29
		return DDI_FAILURE;
E 29
I 29
		return (DDI_FAILURE);
E 29
	}
D 29
	return DDI_FAILURE;
E 29
I 29
	return (DDI_FAILURE);
E 29
}

static int
sfedetach(dev_info_t *dip, ddi_detach_cmd_t cmd)
{
I 4
D 10
#ifdef NOINTR_WORKAROUND
	gld_mac_info_t  *macinfo;
	struct gem_dev	*dp;
	struct sfe_dev	*lp;
#endif

E 10
E 4
D 28
	if (cmd == DDI_DETACH) {
E 28
I 28
	switch (cmd) {
	case DDI_SUSPEND:
D 29
		return  gem_suspend(dip);
E 29
I 29
		return (gem_suspend(dip));
E 29

	case DDI_DETACH:
E 28
I 4
D 10
#ifdef NOINTR_WORKAROUND
		timeout_id_t	old_id;

		macinfo = (gld_mac_info_t *)ddi_get_driver_private(dip);
		dp = (struct gem_dev *)macinfo->gldm_private;
		lp = (struct sfe_dev *)dp->private;

		/* stop interrupt watcher */
		if (lp->intr_watcher_id != 0) {
			do {
				untimeout(old_id = lp->intr_watcher_id);
			} while (old_id != lp->intr_watcher_id);
			lp->intr_watcher_id = 0;
		}
#endif
E 10
E 4
D 29
		return  gem_do_detach(dip);
E 29
I 29
		return (gem_do_detach(dip));
E 29
	}
D 29
	return DDI_FAILURE;
E 29
I 29
	return (DDI_FAILURE);
E 29
}

/* ======================================================== */
/*
 * OS depend (loadable streams driver) routine
 */
/* ======================================================== */
I 36
#ifdef GEM_CONFIG_GLDv3
GEM_STREAM_OPS(sfe_ops, sfeattach, sfedetach);
#else
E 36
static	struct module_info sfeminfo = {
	0,			/* mi_idnum */
	"sfe",			/* mi_idname */
	0,			/* mi_minpsz */
	ETHERMTU,		/* mi_maxpsz */
D 6
	32*1024,		/* mi_hiwat */
E 6
I 6
D 24
	64*1024,		/* mi_hiwat */
E 24
I 24
D 25
	INT32_MAX,		/* mi_hiwat */
E 25
I 25
D 31
	TX_BUF_SIZE*ETHERMAX,	/* mi_hiwat */
E 31
I 31
	64*1024,		/* mi_hiwat */
E 31
E 25
E 24
E 6
	1,			/* mi_lowat */
};

static	struct qinit sferinit = {
	(int (*)()) NULL,	/* qi_putp */
D 12
	gld_rsrv,		/* qi_srvp */
	gld_open,		/* qi_qopen */
	gld_close,		/* qi_qclose */
E 12
I 12
	gem_rsrv,		/* qi_srvp */
	gem_open,		/* qi_qopen */
	gem_close,		/* qi_qclose */
E 12
	(int (*)()) NULL,	/* qi_qadmin */
	&sfeminfo,		/* qi_minfo */
	NULL			/* qi_mstat */
};

static	struct qinit sfewinit = {
D 12
	gld_wput,		/* qi_putp */
	gld_wsrv,		/* qi_srvp */
E 12
I 12
	gem_wput,		/* qi_putp */
	gem_wsrv,		/* qi_srvp */
E 12
	(int (*)()) NULL,	/* qi_qopen */
	(int (*)()) NULL,	/* qi_qclose */
	(int (*)()) NULL,	/* qi_qadmin */
	&sfeminfo,		/* qi_minfo */
	NULL			/* qi_mstat */
};

static struct streamtab	sfe_info = {
	&sferinit,	/* st_rdinit */
	&sfewinit,	/* st_wrinit */
	NULL,		/* st_muxrinit */
	NULL		/* st_muxwrinit */
};

static	struct cb_ops cb_sfe_ops = {
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
D 29
	&sfe_info,	/* cb_stream */
	D_NEW|D_MP	/* cb_flag */
E 29
I 29
	&sfe_info,	/* cb_str */
	D_MP,		/* cb_flag */
D 36
#ifdef notdef
	CB_REV,		/* cb_rev */
	nodev,		/* cb_aread */
	nodev,		/* cb_awrite */
#endif
E 36
E 29
};

static	struct dev_ops sfe_ops = {
	DEVO_REV,	/* devo_rev */
	0,		/* devo_refcnt */
D 12
	gld_getinfo,	/* devo_getinfo */
E 12
I 12
	gem_getinfo,	/* devo_getinfo */
E 12
	nulldev,	/* devo_identify */
	nulldev,	/* devo_probe */
	sfeattach,	/* devo_attach */
	sfedetach,	/* devo_detach */
	nodev,		/* devo_reset */
	&cb_sfe_ops,	/* devo_cb_ops */
	NULL,		/* devo_bus_ops */
D 29
	ddi_power	/* devo_power */
E 29
I 29
	gem_power	/* devo_power */
E 29
};
D 36

E 36
I 36
#endif
E 36
static struct modldrv modldrv = {
	&mod_driverops,	/* Type of module.  This one is a driver */
	ident,
	&sfe_ops,	/* driver ops */
};

static struct modlinkage modlinkage = {
	MODREV_1, &modldrv, NULL
};

/* ======================================================== */
/*
 * Loadable module support
 */
/* ======================================================== */
int
_init(void)
{
	int 	status;

D 6
	DPRINTF(2, (CE_CONT, "sfe: _init: called"));
E 6
I 6
	DPRINTF(2, (CE_CONT, CONS "sfe: _init: called"));
I 29
	gem_mod_init(&sfe_ops, "sfe");
E 29
E 6
	status = mod_install(&modlinkage);
I 29
	if (status != DDI_SUCCESS) {
		gem_mod_fini(&sfe_ops);
	}
E 29
D 36

E 36
	return (status);
}

/*
 * _fini : done
 */
int
_fini(void)
{
	int	status;

D 6
	DPRINTF(2, (CE_CONT, "sfe: _fini: called"));
E 6
I 6
	DPRINTF(2, (CE_CONT, CONS "sfe: _fini: called"));
E 6
	status = mod_remove(&modlinkage);
I 29
	if (status == DDI_SUCCESS) {
		gem_mod_fini(&sfe_ops);
	}
E 29
	return (status);
}

int
_info(struct modinfo *modinfop)
{
	return (mod_info(&modlinkage, modinfop));
}
E 1
