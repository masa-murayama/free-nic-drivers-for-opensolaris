h58782
s 00146/00103/04197
d D 1.31 13/05/03 15:28:13 mrym 31 30
c 2.6.9
e
s 00054/00024/04246
d D 1.30 10/06/19 17:30:12 mrym 30 29
c 2.6.7
e
s 00109/00080/04161
d D 1.29 10/04/07 22:31:53 mrym 29 28
c 2.6.6 release
e
s 01178/00421/03063
d D 1.28 10/03/28 13:11:08 mrym 28 27
c 2.6.5
e
s 00033/00023/03451
d D 1.27 09/04/16 23:05:20 mrym 27 26
c 2.6.4
e
s 00028/00031/03446
d D 1.26 09/02/04 20:46:17 mrym 26 25
c 2.6.2 reading factory mac address fixed
e
s 00001/00001/03476
d D 1.25 09/01/31 03:38:31 mrym 25 24
c 2.6.2-1
e
s 00276/00142/03201
d D 1.24 09/01/30 01:31:56 mrym 24 23
c 2.6.2
e
s 00377/00605/02966
d D 1.23 09/01/25 20:31:21 mrym 23 22
c 2.6.1
e
s 02023/00940/01548
d D 1.22 05/01/01 01:32:16 mrym 22 21
c 2.6.0
e
s 00158/00114/02330
d D 1.21 07/05/19 21:07:58 mrym 21 20
c 2.4.4
e
s 00002/00002/02442
d D 1.20 07/04/17 23:31:17 mrym 20 19
c 2.4.3
e
s 00048/00027/02396
d D 1.19 07/04/17 03:17:50 mrym 19 18
c set_rx_filter fixed and others 2.4.2
e
s 00053/00070/02370
d D 1.18 06/12/19 22:39:07 mrym 18 17
c 2.4.1
e
s 00140/00113/02300
d D 1.17 06/12/17 18:58:08 mrym 17 16
c 2.4.0
e
s 01257/00676/01156
d D 1.16 06/06/19 06:38:31 mrym 16 15
c many fixes for 8168
e
s 00012/00021/01820
d D 1.15 05/06/10 22:38:52 mrym 15 14
c 0.8.18
e
s 00033/00012/01808
d D 1.14 05/05/21 12:07:03 mrym 14 13
c changing mac address fixed
e
s 00234/00196/01586
d D 1.13 05/05/09 21:45:05 mrym 13 12
c 0.8.16
e
s 00004/00004/01778
d D 1.12 05/04/26 06:53:01 mrym 12 11
c 0.8.15 - 0.8.14 have a bug in gani_stop_chip on sparc)
e
s 00068/00055/01714
d D 1.11 05/04/25 23:50:11 mrym 11 10
c 0.8.14
e
s 00169/00269/01600
d D 1.10 05/04/24 19:34:07 mrym 10 9
c 0.8.13  rx buffer ring initialization timing fixed
e
s 00328/00266/01541
d D 1.9 05/04/04 01:13:43 mrym 9 8
c polling mode implemented
e
s 00002/00001/01805
d D 1.8 05/01/18 02:34:44 mrym 8 7
c slot number calculation for last fragment in gani_tx_desc_stat fixed
e
s 00004/00005/01802
d D 1.7 05/01/12 23:47:25 mrym 7 6
c optimazation for TDU interrupt fixed
e
s 00115/00172/01692
d D 1.6 05/01/10 23:23:16 mrym 6 5
c flow control fixed
e
s 00436/00216/01428
d D 1.5 04/12/24 01:06:35 mrym 5 4
c sparc supported
e
s 00209/00149/01435
d D 1.4 04/11/28 20:32:00 mrym 4 3
c amd64 support
e
s 00104/00018/01480
d D 1.3 04/10/31 09:35:41 mrym 3 2
c tx threashold fixed
e
s 00001/00001/01497
d D 1.2 04/05/24 22:12:25 mrym 2 1
c copyright changed
e
s 01498/00000/00000
d D 1.1 04/05/24 22:09:57 mrym 1 0
c date and time created 04/05/24 22:09:57 by mrym
e
u
U
f e 0
t
T
I 1
/*
D 16
 * gani_gem.c : The Realtek RTL8169 Gigabit Ethernet Driver for Solaris
E 16
I 16
D 22
 * gani_gem.c : The Realtek RTL816x Gigabit Ethernet Driver for Solaris
E 22
I 22
 * gani : The Realtek RTL816x Gigabit Ethernet Driver for Solaris
E 22
E 16
 *
D 2
 * Copyright (c) 2002-2004 Masayuki Murayama.  All rights reserved.
E 2
I 2
D 6
 * Copyright (c) 2004 Masayuki Murayama.  All rights reserved.
E 6
I 6
D 16
 * Copyright (c) 2004, 2005 Masayuki Murayama.  All rights reserved.
E 16
I 16
D 19
 * Copyright (c) 2004-2006 Masayuki Murayama.  All rights reserved.
E 19
I 19
D 22
 * Copyright (c) 2004-2007 Masayuki Murayama.  All rights reserved.
E 19
E 16
E 6
E 2
 * 
E 22
I 22
D 23
 * Copyright (c) 2004-2008 Masayuki Murayama.  All rights reserved.
E 23
I 23
D 28
 * Copyright (c) 2004-2009 Masayuki Murayama.  All rights reserved.
E 28
I 28
D 31
 * Copyright (c) 2004-2010 Masayuki Murayama.  All rights reserved.
E 31
I 31
 * Copyright (c) 2004-2012 Masayuki Murayama.  All rights reserved.
E 31
E 28
E 23
 *
E 22
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
D 22
 * 
E 22
I 22
 *
E 22
 * 1. Redistributions of source code must retain the above copyright notice,
D 22
 *    this list of conditions and the following disclaimer. 
 * 
E 22
I 22
 *    this list of conditions and the following disclaimer.
 *
E 22
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
D 22
 *    and/or other materials provided with the distribution. 
 * 
E 22
I 22
 *    and/or other materials provided with the distribution.
 *
E 22
 * 3. Neither the name of the author nor the names of its contributors may be
 *    used to endorse or promote products derived from this software without
D 22
 *    specific prior written permission. 
 * 
E 22
I 22
 *    specific prior written permission.
 *
E 22
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

D 22
#pragma	ident	"%W% %E%"
E 22
I 22
#pragma	ident	"%Z%%M% %I%     %E%"
E 22

/*
D 22
 *  Changelog:
I 9

 2005/02/26
	gani_set_rx_filter was fixed to use ALLMULTI mode when the number
	of multicast addresses was greater than or equal to 32, instead of
	promiscious mode.

	the performance of gani_set_rx_filter was improved. 
	ID registers had been updated on every call of it.
I 10
D 13
2005/04/23
E 13
I 13

 2005/04/23
E 13
	rx buffer setup problem in gani_init_chip & gani_start_chip fixed.
I 13

 2005/05/09
	0.8.16

I 14
 2005/05/09
	changing mac address did not work
	compile error on __FUNCTION__ with Sun CC
	0.8.17

I 15
 2005/05/25
	lp->mac updated after loading EEPROM contents
 2005/06/11
	0.8.18

I 16
===== gld_v3 version ====
 2005/12/12
	modified for 8168
 2005/12/18
	2.0.0
I 19
 2007/04/17
	2.4.2
I 21
 2007/05/17
	2.4.4	mii read/write fixed for 8110SC
E 21
E 19
E 16
E 15
E 14
E 13
E 10
E 9
 */

/*
E 22
 * TODO
I 5
D 6
	flow control
	66MHz mode
E 6
I 6
D 16
	flow control: done
E 16
D 10
	66MHz mode: done but not tested.
E 10
I 9
D 13
	hang/panic on sparc
E 13
I 13
D 22
	hang/panic at boot time on sparc
I 16
	offloading seem to cause tx timeout

	multicast receive not tested (8168)
   BUGS
E 22
I 22
D 28
 *	hang/panic at boot time on sparc
E 28
 *	offloading seem to cause tx timeout
I 28
 *	tx hang on 8169
 *	rx hang on 8169
E 28
 *
D 28
 *	multicast receive not tested (8168)
E 28
 *  BUGS
E 22
E 16
E 13
E 9
E 6
E 5
 */
I 5

E 5
/* ======================================================= */

/*
 * Solaris system header files and macros
 */
#include <sys/types.h>
#include <sys/conf.h>
#include <sys/debug.h>
D 22
#include <sys/stropts.h>
#include <sys/stream.h>
#include <sys/strlog.h>
E 22
#include <sys/kmem.h>
D 22
#include <sys/stat.h>
#include <sys/kstat.h>
#include <sys/vtrace.h>
#include <sys/dlpi.h>
#include <sys/strsun.h>
#include <sys/ethernet.h>
E 22
#include <sys/modctl.h>
#include <sys/errno.h>
I 16
D 22
#include <sys/dditypes.h>
E 22
E 16
#include <sys/ddi.h>
#include <sys/sunddi.h>
D 9
#include <sys/gld.h>
E 9
I 9
D 10
/* #include <sys/gld.h> */
/* #include <sys/gldpriv.h> */
E 10
E 9
D 16
#include <sys/ddi_impldefs.h>
E 16
D 22

#include <sys/pci.h>
E 22
I 17
#include <sys/byteorder.h>
I 22
#include <sys/ethernet.h>
#include <sys/pci.h>
E 22
E 17

I 22
#include "gem_mii.h"
E 22
#include "gem.h"
D 22
#include "mii.h"
E 22
#include "rtl8169reg.h"

D 16
char	ident[] = "rtl8169 nic driver v" VERSION;
char	_depends_on[] = {"misc/gld"};
E 16
I 16
char	ident[] = "rtl816x nic driver v" VERSION;
E 16

/*
 * Useful macros
 */
#define	ROUNDUP2(x, y)	(((x)+(y)-1) & ~((y)-1))
D 16
#define	FALSE	(0)
#define	TRUE	(!FALSE)
E 16
I 16
D 22
#define	PKTSIZE(m) \
D 17
		(sizeof(struct ether_header) + 4 + (m) + ETHERFCSL + 100)
E 17
I 17
		(sizeof(struct ether_header) + 8 + (m) + ETHERFCSL)
E 22
I 22
D 31
#define	PKTSIZE(m)	(sizeof (struct ether_header) + 8 + (m) + ETHERFCSL)
E 31
I 31
#define	ETHERHEADERL	(ETHERMAX - ETHERMTU)
#define	VTAG_SIZE	4
#define	RMS_PCI(m)	(ETHERHEADERL + VTAG_SIZE + (m) + ETHERFCSL + 4)
#define	RMS_PCIE(m)	(ETHERHEADERL + VTAG_SIZE + (m) + ETHERFCSL + 1)
E 31
#define	ONESEC		(drv_usectohz(1*1000000))
E 22
E 17
E 16

I 5
D 19
#define	STRUCT_COPY(a, b)	bcopy(&(b), &(a), sizeof(a))

E 19
E 5
D 22
#define	ONESEC			(drv_usectohz(1*1000000))
D 5
#define	TIM_10us	333	/* Is the value right in 66MHz PCI ? */
I 4
#define	TALLY_BASE(dp)	((dp)->tx_ring + sizeof(struct tx_desc)*TX_RING_SIZE)
E 5
I 5
D 13
#define	TIM_10us	333	/* based on 33MHz PCI */
I 6
#define	IFG		12
E 13

E 22
I 13
#define	DESC_BASE_ALIGN	256	/* it should be defined in rtl8169reg.h */
I 16
#define	DESC_MAX_SIZE	(16*1024)	/* in byte */
E 16

E 13
E 6
D 16
#define	TALLY_OFFSET	\
D 13
	((sizeof(struct rx_desc) * RX_RING_SIZE) + \
	 (sizeof(struct tx_desc) * TX_RING_SIZE))
E 13
I 13
	(ROUNDUP2(sizeof(struct rx_desc) * RX_RING_SIZE, DESC_BASE_ALIGN) + \
	 ROUNDUP2(sizeof(struct tx_desc) * TX_RING_SIZE, DESC_BASE_ALIGN))
E 13
#define	TALLY_VADDR(dp)	((dp)->rx_ring + TALLY_OFFSET)
#define	TALLY_DMA(dp)	((dp)->rx_ring_dma + TALLY_OFFSET)
E 16
I 16
D 22
#define	TALLY_OFFSET(dp)	((dp)->io_area - (dp)->rx_ring)
#define	TALLY_VADDR(dp)		((dp)->io_area)
E 22
I 22
#define	TALLY_OFFSET(dp)	\
	(((intptr_t)(dp)->io_area) - ((intptr_t)(dp)->rx_ring))
#define	TALLY_VADDR(dp)		((void *)((dp)->io_area))
E 22
#define	TALLY_DMA_ADDR(dp)	((dp)->io_area_dma)
E 16
E 5
E 4

I 4
D 6
#define	TCR_MACVER_B	0x00000000
#define	TCR_MACVER_D	0x00800000
#define	TCR_MACVER_E	0x04000000
#define	TCR_MACVER_F	0x10000000

E 6
I 5
D 9
#if defined(sun4u)
#define	LE64(x)	((((uint64_t)gem_le32(x))<<32) | (uint64_t)gem_le32((x)>>32))
#define	LE32(x)	gem_le32(x)
#define	LE16(x)	gem_le16(x)
#else
#define	LE64(x)	(x)
#define	LE32(x)	(x)
#define	LE16(x)	(x)
#endif

E 9
D 16
#ifdef MAP_MEM
D 6
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
#endif

#ifdef IO_BARRIER
#define	IO_BARRIER_ENTER(lp)	mutex_enter(&(lp)->reglock)
#define	IO_BARRIER_EXIT(lp)	mutex_exit(&(lp)->reglock)
E 6
D 9
#define	FLSHB(dp,reg)		INB(dp, reg)
#define	FLSHW(dp,reg)		INW(dp, reg)
#define	FLSHL(dp,reg)		INL(dp, reg)
E 9
I 9
#define	FLSHB(dp, reg)		INB(dp, reg)
#define	FLSHW(dp, reg)		INW(dp, reg)
#define	FLSHL(dp, reg)		INL(dp, reg)
E 16
I 16
D 22
#if defined(sun4u)
# define LE16(x)	ddi_swap16(x)
# define LE32(x)	ddi_swap32(x)
# define LE64(x)	ddi_swap64(x)
E 16
E 9
#else
D 6
#define	IO_BARRIER_ENTER(lp)
#define	IO_BARRIER_EXIT(lp)
E 6
D 9
#define	FLSHB(dp,reg)
#define	FLSHW(dp,reg)
#define	FLSHL(dp,reg)
E 9
I 9
D 16
#define	FLSHB(dp, reg)
#define	FLSHW(dp, reg)
#define	FLSHL(dp, reg)
E 16
I 16
# define LE16(x)	(x)
# define LE32(x)	(x)
# define LE64(x)	(x)
E 16
E 9
#endif
E 22
D 17

E 17
I 17
#ifdef MAP_MEM
E 17
E 5
E 4
D 16
/*
I 9
 * Experimental: polling mode support
 */
#define	GANI_IS_POLLING(lp)		(((lp)->imr & INTR_ROK) == 0)
E 16
I 16
D 22
#define	FLSHB(dp, reg)	INB(dp, reg)
#define	FLSHW(dp, reg)	INW(dp, reg)
#define	FLSHL(dp, reg)	INL(dp, reg)
E 22
I 22
#define	FLSHB(dp, reg)	(void) INB(dp, reg)
#define	FLSHW(dp, reg)	(void) INW(dp, reg)
#define	FLSHL(dp, reg)	(void) INL(dp, reg)
E 22
I 17
#else
#define	FLSHB(dp, reg)
#define	FLSHW(dp, reg)
#define	FLSHL(dp, reg)
#endif
E 17
E 16

I 16
D 22
#define CONFIG_EEPROM_IO
E 22
I 22
#define	TXDESC(p)	((struct tx_desc *)(void *)(p))
#define	RXDESC(p)	((struct rx_desc *)(void *)(p))
E 22

I 22
D 26
#define	CONFIG_EEPROM_IO

E 26
/* additional PCI related macros for compatibility */
#ifndef PCI_CAP_ID_PCI_E
#define	PCI_CAP_ID_PCI_E	0x10
#endif

I 28
#ifdef GEM3
#define	IS_MAC_ONLINE(dp)	((dp)->mac_state == MAC_STATE_ONLINE)
#else
#define	IS_MAC_ONLINE(dp)	((dp)->mac_active)
#endif
E 28
E 22
E 16
/*
E 9
 * Debugging
 */
#ifdef DEBUG_LEVEL
static int gani_debug = DEBUG_LEVEL;
D 22
#define DPRINTF(n, args)	if (gani_debug > (n)) cmn_err args
E 22
I 22
#define	DPRINTF(n, args)	if (gani_debug > (n)) cmn_err args
E 22
#else
D 22
#define DPRINTF(n, args)
E 22
I 22
#define	DPRINTF(n, args)
E 22
#endif

I 14
#define	DUMP_ETHER(n, dp, m) \
	DPRINTF(n, (CE_CONT, "!%s: %s: mac: %02x:%02x:%02x:%02x:%02x:%02x", \
		(dp)->name, __func__, \
		(m)[0], (m)[1], (m)[2], (m)[3], (m)[4], (m)[5]));
E 14
/*
D 4
 * Our configration for rtl8139
E 4
I 4
D 16
 * Our configration for rtl8169
E 16
I 16
 * Our configration for rtl816x
E 16
E 4
 */
I 24
static boolean_t gani_64bit_addr = B_FALSE;

E 24
I 16
D 22
#ifdef CONFIG_OO
D 18
#  ifdef WA_NO_DESC_WRAP
D 17
#     error both CONFIG_OO and WA_NO_DESC_WRAP were define, ingoring WA_NO_DESC_WRAP
E 17
I 17
#     error both CONFIG_OO and WA_NO_DESC_WRAP were defined, ingoring WA_NO_DESC_WRAP
E 17
#     undef WA_NO_DESC_WRAP
#  endif
E 18
I 18
#  undef TX_MAX_FRAGS
E 18
#  define TX_MAX_FRAGS	1
I 17
#  undef TX_BUF_SIZE
E 17
#  define TX_BUF_SIZE	256
#  undef TX_RING_SIZE
#  define TX_RING_SIZE	TX_BUF_SIZE
E 22
I 22
#ifndef GEM_CONFIG_TX_DIRECT
#undef TX_MAX_FRAGS
#define	TX_MAX_FRAGS	1
#undef TX_BUF_SIZE
#define	TX_BUF_SIZE	256
#undef TX_RING_SIZE
#define	TX_RING_SIZE	TX_BUF_SIZE
#else
#define	TX_MAX_FRAGS	GEM_MAXTXFRAGS
E 22
#endif

D 18
#define WA_NO_TPPOLL_WRAP

E 18
D 22
#if !defined(TX_MAX_FRAGS)
# define TX_MAX_FRAGS	8
#endif

E 22
E 16
I 13
#ifdef TEST_TXDESC_FULL
D 22
# define TX_RING_SIZE	(DESC_BASE_ALIGN / sizeof(struct tx_desc)) /**/
E 22
I 22
#define	TX_RING_SIZE	(DESC_BASE_ALIGN / sizeof (struct tx_desc))
E 22
D 16
/*# define TX_RING_SIZE	8	/**/
E 16
#endif
#ifdef TEST_RX_EMPTY
D 22
# define RX_BUF_SIZE	1
E 22
I 22
#define	RX_BUF_SIZE	1
E 22
#endif

E 13
I 6
#ifndef	TX_BUF_SIZE
D 13
# ifdef TDU_TEST
D 7
#  define	TX_BUF_SIZE	32
E 7
I 7
#  define	TX_BUF_SIZE	4
E 7
# else
#  define	TX_BUF_SIZE	256
# endif
E 13
I 13
D 22
# define TX_BUF_SIZE	256
E 22
I 22
#define	TX_BUF_SIZE	256
E 22
E 13
#endif
E 6
D 4
#define	TX_BUF_SIZE	64
E 4
D 7
#ifdef TDU_TEST
I 4
D 6
#define	TX_BUF_SIZE	32
E 6
E 4
#define	TX_RING_SIZE	4
#else
E 7
I 4
D 6
#define	TX_BUF_SIZE	64
E 6
E 4
D 13
#define	TX_RING_SIZE	(TX_BUF_SIZE*4)
E 13
I 13
#ifndef	TX_RING_SIZE
D 16
# define TX_RING_SIZE	(TX_BUF_SIZE*4)
E 16
I 16
D 22
# define TX_RING_SIZE	(DESC_MAX_SIZE / sizeof(struct tx_desc))
E 22
I 22
#define	TX_RING_SIZE	(DESC_MAX_SIZE / sizeof (struct tx_desc))
E 22
E 16
#endif
E 13
D 7
#endif
E 7
D 6
#define	RX_BUF_SIZE	64
E 6
I 6

#ifndef	RX_BUF_SIZE
D 13
#define	RX_BUF_SIZE	256
E 13
I 13
D 22
# define RX_BUF_SIZE	256
E 22
I 22
#define	RX_BUF_SIZE	256
E 22
E 13
#endif
E 6
D 17
#define	RX_RING_SIZE	RX_BUF_SIZE
E 17
I 17
#ifndef	RX_RING_SIZE
D 22
# define RX_RING_SIZE	RX_BUF_SIZE
E 22
I 22
#define	RX_RING_SIZE	RX_BUF_SIZE
E 22
#endif
E 17

D 5
#define	IFG		(12)
E 5
I 5
D 6
#define	IFG		12
E 5

E 6
D 4
#ifdef TX_DELAYED_INTR
#define	OUR_INTR_MASK_TX_DELAYED_INTR	\
	(INTR_PUN |	\
	 INTR_SERR | INTR_TimeOut | INTR_FOVW | INTR_RDU |	\
	 INTR_TER | INTR_RER | INTR_ROK)

E 4
#define	OUR_INTR_MASK	\
D 4
	(INTR_PUN |	\
	 INTR_SERR | INTR_FOVW | INTR_RDU |	\
E 4
I 4
D 9
	(INTR_SERR | INTR_TDU | INTR_FOVW | INTR_RDU |	\
E 9
I 9
D 13
	(INTR_SERR | INTR_SWInt | INTR_FOVW | INTR_RDU |	\
E 13
I 13
D 16
	(INTR_SERR | INTR_SWInt | INTR_FOVW | INTR_RDU | \
E 13
E 9
E 4
	 INTR_TER | INTR_RER | INTR_ROK)
E 16
I 16
D 23
	(INTR_PUN | INTR_SERR | INTR_SWInt | INTR_FOVW | INTR_RDU | \
E 23
I 23
	(INTR_SERR | INTR_SWInt | INTR_FOVW | INTR_PUN | INTR_RDU | \
E 23
D 18
	 INTR_TDU | INTR_TER | INTR_TOK | INTR_RER | INTR_ROK)
E 18
I 18
D 22
	 INTR_TER | INTR_TOK | INTR_RER | INTR_ROK)
E 22
I 22
	INTR_TER | INTR_TOK | INTR_RER | INTR_ROK)
E 22
E 18
E 16
D 4
#else
#define	OUR_INTR_MASK	\
	(INTR_SERR | INTR_TimeOut | INTR_TDU | INTR_FOVW | INTR_RDU |	\
	 INTR_TER | INTR_RER | INTR_ROK)
#endif
E 4

I 22
D 28
#define	OUR_INTR_MASK_8168	\
	(INTR_SERR | INTR_TimeOut | INTR_SWInt | INTR_PUN | INTR_RDU | \
	INTR_TER | INTR_TOK | INTR_RER | INTR_ROK)

E 28
E 22
I 16
#if defined(sun4u) || defined(CONFIG_TX_COPY)
D 30
static int	gani_tx_copy_thresh = INT32_MAX;
E 30
I 30
static int	gani_tx_copy_thresh = ETHERMAX + 4;
E 30
#else
E 16
I 9
D 13
#define	RX_DELAY_DEFAULT	6

E 13
E 9
static int	gani_tx_copy_thresh = 256;
I 16
#endif
#if defined(sun4u) || defined(CONFIG_RX_COPY)
D 30
static int	gani_rx_copy_thresh = INT32_MAX;
E 30
I 30
static int	gani_rx_copy_thresh = ETHERMAX + 4;
E 30
#else
E 16
static int	gani_rx_copy_thresh = 256;
I 16
#endif
I 23
D 24
static int gani_pcie_req_max = 3;
E 24
I 24
D 25
static int gani_pcie_req_max = 2;
E 25
I 25
D 31
static int gani_pcie_req_max = 3;
E 31
I 31
static int gani_pcie_req_max = 5;
E 31
E 25
E 24
E 23
E 16

/*
 * Local device definitions
 */
struct chip_info {
D 16
	uint32_t	tcr_val; /* from RTL8169 docs */
E 16
I 16
	uint32_t	tcr_val; /* from RTL8169/RTL8168 docs */
E 16
D 22
	int		flags;
E 22
I 22
	uint32_t	tcr_mask;
I 31
	int		max_mtu;
#define	MTU4K	(4*1024 - (ETHERMAX - ETHERMTU) - ETHERFCSL - 4)
#define	MTU6K	(6*1024 - (ETHERMAX - ETHERMTU) - ETHERFCSL - 4)
#define	MTU7K	(7*1024 - (ETHERMAX - ETHERMTU) - ETHERFCSL - 4)
#define	MTU9K	(9*1024 - (ETHERMAX - ETHERMTU) - ETHERFCSL - 4)
E 31
E 22
D 23
	char		*name;
E 23
D 22
	int		type;
E 22
I 22
	uint_t		type;
I 23
	char		*name;
E 23
E 22
};

D 16
#define	MAC_VER_B	0
#define	MAC_VER_D	1
#define	MAC_VER_E	2
I 4
#define	MAC_VER_F	3
E 16
I 16
D 21
#define	MAC_VER_8169	0
#define	MAC_VER_8169S_D	1
#define	MAC_VER_8169S_E	2
#define	MAC_VER_8169SB	3
E 16
E 4

D 16
struct chip_info chiptbl_8169[] = {
D 10
	/* keep the checking order */
I 4
	{TCR_MACVER_F,	0,	"rtl8169s/8110s ver.F",	MAC_VER_F},
E 4
	{TCR_MACVER_E,	0,	"rtl8169s/8110s ver.E",	MAC_VER_E},
	{TCR_MACVER_D,	0,	"rtl8169s/8110s ver.D",	MAC_VER_D},
E 10
	{TCR_MACVER_B,	0,	"rtl8169 ver.B",	MAC_VER_B},
I 10
	{TCR_MACVER_D,	0,	"rtl8169s/8110s ver.D",	MAC_VER_D},
	{TCR_MACVER_E,	0,	"rtl8169s/8110s ver.E",	MAC_VER_E},
	{TCR_MACVER_F,	0,	"rtl8169s/8110s ver.F",	MAC_VER_F},
E 16
I 16
#define	MAC_VER_8168	5
#define	MAC_VER_8168B	6
#define	MAC_VER_8100E	7
#define	MAC_VER_8101E	8
#define	MAC_VER_8169SC	9
E 21
I 21
D 22
#define	MAC_VER_8169	1
#define	MAC_VER_8169S_D	2
#define	MAC_VER_8169S_E	3
#define	MAC_VER_8169SB	4
#define	MAC_VER_8110SC	5
E 22
I 22
#define	GANI_TYPE_MASK		0xf000U
#define	GANI_TYPE_PCI		0x0000U
#define	GANI_TYPE_PCIE_GIGA	0x1000U
#define	GANI_TYPE_PCIE_FAST	0x2000U
E 22
E 21

D 21
#define	GANI_PCIE(x)	((x) >= MAC_VER_8168 && (x) <= MAC_VER_8101E)
#define	GANI_8168_OR_LATER(x)	((x) >= MAC_VER_8168)
E 21
I 21
D 22
#define	MAC_VER_8168	10
#define	MAC_VER_8168B_B	11
#define	MAC_VER_8168B_C	12
#define	MAC_VER_8101E	13
#define	MAC_VER_8100E_A	14
#define	MAC_VER_8100E_B	15
E 22
I 22
D 23
#define	R8169_CFG_METHOD_1	(0 | GANI_TYPE_PCI)
#define	R8169_CFG_METHOD_2	(1 | GANI_TYPE_PCI)
#define	R8169_CFG_METHOD_3	(2 | GANI_TYPE_PCI)
#define	R8169_CFG_METHOD_4	(3 | GANI_TYPE_PCI)
#define	R8169_CFG_METHOD_5	(4 | GANI_TYPE_PCI)
#define	R8169_CFG_METHOD_6	(5 | GANI_TYPE_PCI)
E 23
I 23
#define	R8169_1	(0 | GANI_TYPE_PCI)
#define	R8169_2	(1 | GANI_TYPE_PCI)
#define	R8169_3	(2 | GANI_TYPE_PCI)
#define	R8169_4	(3 | GANI_TYPE_PCI)
#define	R8169_5	(4 | GANI_TYPE_PCI)
#define	R8169_6	(5 | GANI_TYPE_PCI)
E 23
E 22
E 21

I 21
D 22
#define	GANI_PCIE(x)		((x) >= MAC_VER_8168)
#define	GANI_8168_OR_LATER(x)	((x) >= MAC_VER_8110SC)
E 22
I 22
D 23
#define	R8168_CFG_METHOD_1	(0 | GANI_TYPE_PCIE_GIGA)
#define	R8168_CFG_METHOD_2	(1 | GANI_TYPE_PCIE_GIGA)
#define	R8168_CFG_METHOD_3	(2 | GANI_TYPE_PCIE_GIGA)
#define	R8168_CFG_METHOD_4	(3 | GANI_TYPE_PCIE_GIGA)
#define	R8168_CFG_METHOD_5	(4 | GANI_TYPE_PCIE_GIGA)
#define	R8168_CFG_METHOD_6	(5 | GANI_TYPE_PCIE_GIGA)
#define	R8168_CFG_METHOD_7	(6 | GANI_TYPE_PCIE_GIGA)
#define	R8168_CFG_METHOD_8	(7 | GANI_TYPE_PCIE_GIGA)
#define	R8168_CFG_METHOD_9	(8 | GANI_TYPE_PCIE_GIGA)
#define	R8168_CFG_METHOD_10	(9 | GANI_TYPE_PCIE_GIGA)
#define	R8168_CFG_METHOD_11	(10 | GANI_TYPE_PCIE_GIGA)
E 23
I 23
D 28
#define	R8168_1	(0 | GANI_TYPE_PCIE_GIGA)
#define	R8168_2	(1 | GANI_TYPE_PCIE_GIGA)
#define	R8168_3	(2 | GANI_TYPE_PCIE_GIGA)
#define	R8168_4	(3 | GANI_TYPE_PCIE_GIGA)
#define	R8168_5	(4 | GANI_TYPE_PCIE_GIGA)
#define	R8168_6	(5 | GANI_TYPE_PCIE_GIGA)
#define	R8168_7	(6 | GANI_TYPE_PCIE_GIGA)
#define	R8168_8	(7 | GANI_TYPE_PCIE_GIGA)
#define	R8168_9	(8 | GANI_TYPE_PCIE_GIGA)
#define	R8168_10	(9 | GANI_TYPE_PCIE_GIGA)
#define	R8168_11	(10 | GANI_TYPE_PCIE_GIGA)
E 28
I 28
#define	R8168_1 (0 | GANI_TYPE_PCIE_GIGA)
#define	R8168_2 (1 | GANI_TYPE_PCIE_GIGA)
#define	R8168_3 (2 | GANI_TYPE_PCIE_GIGA)
#define	R8168_4 (3 | GANI_TYPE_PCIE_GIGA)
#define	R8168_5 (4 | GANI_TYPE_PCIE_GIGA)
#define	R8168_6 (5 | GANI_TYPE_PCIE_GIGA)
#define	R8168_7 (6 | GANI_TYPE_PCIE_GIGA)
#define	R8168_8 (7 | GANI_TYPE_PCIE_GIGA)
#define	R8168_9 (8 | GANI_TYPE_PCIE_GIGA)
#define	R8168_10 (9 | GANI_TYPE_PCIE_GIGA)
#define	R8168_11 (10 | GANI_TYPE_PCIE_GIGA)
#define	R8168_12 (11 | GANI_TYPE_PCIE_GIGA)
#define	R8168_13 (12 | GANI_TYPE_PCIE_GIGA)
#define	R8168_14 (13 | GANI_TYPE_PCIE_GIGA)
#define	R8168_15 (14 | GANI_TYPE_PCIE_GIGA)
E 28
E 23
E 22

I 22
D 23
#define	R8101_CFG_METHOD_1	(0 | GANI_TYPE_PCIE_FAST)
#define	R8101_CFG_METHOD_2	(1 | GANI_TYPE_PCIE_FAST)
#define	R8101_CFG_METHOD_3	(2 | GANI_TYPE_PCIE_FAST)
#define	R8101_CFG_METHOD_4	(3 | GANI_TYPE_PCIE_FAST)
#define	R8101_CFG_METHOD_5	(4 | GANI_TYPE_PCIE_FAST)
#define	R8101_CFG_METHOD_6	(5 | GANI_TYPE_PCIE_FAST)
E 23
I 23
#define	R8101_1	(0 | GANI_TYPE_PCIE_FAST)
#define	R8101_2	(1 | GANI_TYPE_PCIE_FAST)
#define	R8101_3	(2 | GANI_TYPE_PCIE_FAST)
#define	R8101_4	(3 | GANI_TYPE_PCIE_FAST)
#define	R8101_5	(4 | GANI_TYPE_PCIE_FAST)
#define	R8101_6	(5 | GANI_TYPE_PCIE_FAST)
I 28
#define	R8101_7	(6 | GANI_TYPE_PCIE_FAST)
#define	R8101_8	(7 | GANI_TYPE_PCIE_FAST)
#define	R8101_9	(8 | GANI_TYPE_PCIE_FAST)
#define	R8101_10 (9 | GANI_TYPE_PCIE_FAST)
#define	R8101_11 (10 | GANI_TYPE_PCIE_FAST)
#define	R8101_X	(11 | GANI_TYPE_PCIE_FAST)
E 28
E 23

D 28
#define	GANI_PCI(x)		\
		(((x) & GANI_TYPE_MASK) == GANI_TYPE_PCI)
E 28
I 28
#define	GANI_PCIE(x)	((x)->tcr & 0x20000000)
#define	GANI_PCI(x)	(!GANI_PCIE(x))

E 28
#define	GANI_PCIE_GIGA(x)	\
D 28
		(((x) & GANI_TYPE_MASK) == GANI_TYPE_PCIE_GIGA)
E 28
I 28
	(GANI_PCIE(x) && (((x)->tcr & 0x0f000000) != 0x04000000))

E 28
#define	GANI_PCIE_FAST(x)	\
D 28
		(((x) & GANI_TYPE_MASK) == GANI_TYPE_PCIE_FAST)
#define	GANI_PCIE(x)	(GANI_PCIE_GIGA(x) || GANI_PCIE_FAST(x))
E 28
I 28
	(GANI_PCIE(x) && (((x)->tcr & 0x0f000000) == 0x04000000))
E 28

E 22
E 21
static struct chip_info chiptbl_8169[] = {
D 22
/* pci devices */
	{TCR_HWVERID_8169,	GEM_SPD_1000,
				"RTL8169",		MAC_VER_8169}, 
	{TCR_HWVERID_8169S_D,	GEM_SPD_1000,
				"RTL8169S/8110S rev.D",	MAC_VER_8169S_D},
	{TCR_HWVERID_8169S_E,	GEM_SPD_1000,
				"RTL8169S/8110S rev.E",	MAC_VER_8169S_E},
	{TCR_HWVERID_8169SB,	GEM_SPD_1000,
				"RTL8169SB/8110SB",	MAC_VER_8169SB},
D 21
	{TCR_HWVERID_8169SC,	GEM_SPD_1000,
				"RTL8169SC/8110SC",	MAC_VER_8169SC},
E 21
I 21
	{TCR_HWVERID_8110SC,	GEM_SPD_1000,
				"RTL8169SC/8110SC",	MAC_VER_8110SC},
E 22
I 22
/* pci gigabit ethernet devices */
I 28
/* 012 */
E 28
D 23
{0x00000000,	0xfc800000, "RTL8169",			R8169_CFG_METHOD_1},
{0x00800000,	0xfc800000, "RTL8169S rev.D",		R8169_CFG_METHOD_2},
{0x04000000,	0xfc800000, "RTL8110S rev.E",		R8169_CFG_METHOD_3},
{0x10000000,	0xfc800000, "RTL8169SB/8110SB",		R8169_CFG_METHOD_4},
{0x18000000,	0xfc800000, "RTL8110SC rev.D",		R8169_CFG_METHOD_5},
{0x98000000,	0xfc800000, "RTL8110SC rev.E",		R8169_CFG_METHOD_6},
E 23
I 23
D 31
{ 0x00000000, 0xfc800000, R8169_1, "RTL8169", },
{ 0x00800000, 0xfc800000, R8169_2, "RTL8169S/8110S rev.D", },
{ 0x04000000, 0xfc800000, R8169_3, "RTL8169S/8110S rev.E", },
{ 0x10000000, 0xfc800000, R8169_4, "RTL8169SB/8110SB", },
{ 0x18000000, 0xfc800000, R8169_5, "RTL8169/8110SC rev.D", },
{ 0x98000000, 0xfc800000, R8169_6, "RTL8169/8110SC rev.E", },
E 31
I 31
{ 0x00000000, 0xfc800000, MTU7K, R8169_1, "RTL8169", },
{ 0x00800000, 0xfc800000, MTU7K, R8169_2, "RTL8169S/8110S rev.D", },
{ 0x04000000, 0xfc800000, MTU7K, R8169_3, "RTL8169S/8110S rev.E", },
{ 0x10000000, 0xfc800000, MTU7K, R8169_4, "RTL8169SB/8110SB", },
{ 0x18000000, 0xfc800000, MTU7K, R8169_5, "RTL8169/8110SC rev.D", },
{ 0x98000000, 0xfc800000, MTU7K, R8169_6, "RTL8169/8110SC rev.E", },
E 31
E 23
E 22
E 21

D 22
/* pci express devices */
	{TCR_HWVERID_8168,	GEM_SPD_1000,
				"RTL8168/8111",		MAC_VER_8168},
	{TCR_HWVERID_8168B_B,	GEM_SPD_1000,
D 21
				"RTL8168B/8111B rev.B",	MAC_VER_8168B},
E 21
I 21
				"RTL8168B/8111B rev.B",	MAC_VER_8168B_B},
E 21
	{TCR_HWVERID_8168B_C,	GEM_SPD_1000,
D 21
				"RTL8168B/8111B rev.C",	MAC_VER_8168B},
	{TCR_HWVERID_8100E,	GEM_SPD_100,
				"RTL8100E",	MAC_VER_8100E},
E 21
I 21
				"RTL8168B/8111B rev.C",	MAC_VER_8168B_C},
E 21
	{TCR_HWVERID_8101E,	GEM_SPD_100,
				"RTL8101E",	MAC_VER_8101E},
I 21
	{TCR_HWVERID_8100E_A,	GEM_SPD_100,
				"RTL8100E",	MAC_VER_8100E_A},
	{TCR_HWVERID_8100E_B,	GEM_SPD_100,
				"RTL8100E",	MAC_VER_8100E_B},
E 22
I 22
/* pci express gigabit ethernet devices */
I 28
/* 012 */
E 28
D 23
{0x30000000,	0x7c800000, "RTL8168B/8111B rev.B",	R8168_CFG_METHOD_1},
E 23
I 23
D 31
{ 0x30000000, 0x7c800000, R8168_1, "RTL8168B/8111B rev.B", },
E 31
I 31
{ 0x30000000, 0x7c800000, MTU4K, R8168_1, "RTL8168B/8111B rev.B", },
E 31
E 23

D 23
{0x38000000,	0x7cf00000, "RTL8168B/8111B rev.E",	R8168_CFG_METHOD_2},
{0x38500000,	0x7cf00000, "RTL8168B/8111B rev.F",	R8168_CFG_METHOD_3},
{0x38000000,	0x7c800000, "RTL8168B/8111B unknown",	R8168_CFG_METHOD_3},
E 23
I 23
D 31
{ 0x38000000, 0x7cf00000, R8168_2, "RTL8168B/8111B rev.E", },
{ 0x38500000, 0x7cf00000, R8168_3, "RTL8168B/8111B rev.F", },
{ 0x38000000, 0x7c800000, R8168_3, "RTL8168B/8111B unknown", },
E 31
I 31
{ 0x38000000, 0x7cf00000, MTU4K, R8168_2, "RTL8168B/8111B rev.E", },
{ 0x38500000, 0x7cf00000, MTU4K, R8168_3, "RTL8168B/8111B rev.F", },
{ 0x38000000, 0x7c800000, MTU4K, R8168_3, "RTL8168B/8111B unknown", },
E 31
E 23

D 23
{0x3c000000,	0x7cf00000, "RTL8168C/8111C",		R8168_CFG_METHOD_4},
{0x3c200000,	0x7cf00000, "RTL8168C/8111C rev.B",	R8168_CFG_METHOD_5},
{0x3c400000,	0x7cf00000, "RTL8168C/8111C rev.C",	R8168_CFG_METHOD_6},
{0x3c000000,	0x7c800000, "RTL8168C/8111C unknown",	R8168_CFG_METHOD_6},
E 23
I 23
D 31
{ 0x3c000000, 0x7cf00000, R8168_4, "RTL8168C/8111C", },
{ 0x3c200000, 0x7cf00000, R8168_5, "RTL8168C/8111C rev.B", },
{ 0x3c400000, 0x7cf00000, R8168_6, "RTL8168C/8111C rev.C", },
{ 0x3c000000, 0x7c800000, R8168_6, "RTL8168C/8111C unknown", },
E 31
I 31
{ 0x3c000000, 0x7cf00000, MTU6K, R8168_4, "RTL8168C/8111C", },
{ 0x3c200000, 0x7cf00000, MTU6K, R8168_5, "RTL8168C/8111C rev.B", },
{ 0x3c400000, 0x7cf00000, MTU6K, R8168_6, "RTL8168C/8111C rev.C", },
{ 0x3c000000, 0x7c800000, MTU6K, R8168_6, "RTL8168C/8111C unknown", },
E 31
E 23

D 23
{0x3c900000,	0x7cf00000, "RTL8168CP/8111CP rev.B",	R8168_CFG_METHOD_7},
{0x3cb00000,	0x7cf00000, "RTL8168CP/8111CP rev.C",	R8168_CFG_METHOD_8},
{0x3c800000,	0x7c800000, "RTL8168CP/8111CP",		R8168_CFG_METHOD_8},
E 23
I 23
D 31
{ 0x3c900000, 0x7cf00000, R8168_7, "RTL8168CP/8111CP rev.B", },
{ 0x3cb00000, 0x7cf00000, R8168_8, "RTL8168CP/8111CP rev.C", },
{ 0x3c800000, 0x7c800000, R8168_8, "RTL8168CP/8111CP", },
E 31
I 31
{ 0x3c900000, 0x7cf00000, MTU6K, R8168_7, "RTL8168CP/8111CP rev.B", },
{ 0x3cb00000, 0x7cf00000, MTU6K, R8168_8, "RTL8168CP/8111CP rev.C", },
{ 0x3c800000, 0x7c800000, MTU6K, R8168_8, "RTL8168CP/8111CP", },
E 31
E 23

D 23
{0x28100000,	0x7cf00000, "RTL8168D/8111D",		R8168_CFG_METHOD_9},
{0x28200000,	0x7cf00000, "RTL8168D/8111D rev.B",	R8168_CFG_METHOD_10},
{0x28000000,	0x7c800000, "RTL8168D/8111D unknown",	R8168_CFG_METHOD_10},
E 23
I 23
D 31
{ 0x28100000, 0x7cf00000, R8168_9, "RTL8168D/8111D", },
D 28
{ 0x28200000, 0x7cf00000, R8168_10, "RTL8168D/8111D rev.B", },
I 24
{ 0x28300000, 0x7cf00000, R8168_11, "RTL8168D/8111D rev.C", },
E 28
I 28
{ 0x28300000, 0x7cf00000, R8168_10, "RTL8168D/8111D rev.C", },
E 28
E 24
{ 0x28000000, 0x7c800000, R8168_10, "RTL8168D/8111D unknown", },
E 31
I 31
{ 0x28100000, 0x7cf00000, MTU9K, R8168_9, "RTL8168D/8111D", },
{ 0x28300000, 0x7cf00000, MTU9K, R8168_10, "RTL8168D/8111D rev.C", },
{ 0x28000000, 0x7c800000, MTU9K, R8168_10, "RTL8168D/8111D unknown", },
E 31
E 23

I 28
D 31
{ 0x28800000, 0x7cf00000, R8168_11, "RTL8168DP/8111DP", },
{ 0x28a00000, 0x7cf00000, R8168_12, "RTL8168DP/8111DP rev.B", },
{ 0x28800000, 0x7c800000, R8168_13, "RTL8168DP/8111DP rev.C", },
E 31
I 31
{ 0x28800000, 0x7cf00000, MTU9K, R8168_11, "RTL8168DP/8111DP", },
{ 0x28a00000, 0x7cf00000, MTU9K, R8168_12, "RTL8168DP/8111DP rev.B", },
{ 0x28800000, 0x7c800000, MTU9K, R8168_13, "RTL8168DP/8111DP rev.C", },
E 31

D 31
{ 0x2c100000, 0x7cf00000, R8168_14, "RTL8168E/8111E", },
{ 0x2c200000, 0x7cf00000, R8168_15, "RTL8168E/8111E rev.B", },
{ 0x2c000000, 0x7c800000, R8168_15, "RTL8168E/8111E unknown", },
E 31
I 31
{ 0x2c100000, 0x7cf00000, MTU9K, R8168_14, "RTL8168E/8111E", },
{ 0x2c200000, 0x7cf00000, MTU9K, R8168_15, "RTL8168E/8111E rev.B", },
{ 0x2c000000, 0x7c800000, MTU9K, R8168_15, "RTL8168E/8111E unknown", },
E 31

E 28
/* pci express fast ethernet devices */
D 23
{0x34000000,	0x7cf00000, "RTL8101E rev.B",		R8101_CFG_METHOD_1},
{0x34200000,	0x7cf00000, "RTL8101E rev.C",		R8101_CFG_METHOD_2},
{0x34300000,	0x7cf00000, "RTL8101E rev.C",		R8101_CFG_METHOD_3},
{0x34000000,	0x7c800000, "RTL8101E unknown",		R8101_CFG_METHOD_3},
E 23
I 23
D 31
{ 0x34000000, 0x7cf00000, R8101_1, "RTL8101E rev.B", },
{ 0x34200000, 0x7cf00000, R8101_2, "RTL8101E rev.E", },
{ 0x34300000, 0x7cf00000, R8101_3, "RTL8101E rev.F", },
{ 0x34000000, 0x7c800000, R8101_3, "RTL8101E unknown", },
E 31
I 31
{ 0x34000000, 0x7cf00000, 1500, R8101_1, "RTL8101E rev.B", },
{ 0x34200000, 0x7cf00000, 1500, R8101_2, "RTL8101E rev.E", },
{ 0x34300000, 0x7cf00000, 1500, R8101_3, "RTL8101E rev.F", },
{ 0x34000000, 0x7c800000, 1500, R8101_3, "RTL8101E unknown", },
E 31
E 23

D 23
{0x34900000,	0x7cf00000, "RTL8102E",			R8101_CFG_METHOD_4},
{0x34a00000,	0x7cf00000, "RTL8102E rev.B",		R8101_CFG_METHOD_5},
{0x34c00000,	0x7cf00000, "RTL8103E",			R8101_CFG_METHOD_6},
{0x34800000,	0x7c800000, "RTL8103E",			R8101_CFG_METHOD_6},
E 23
I 23
D 31
{ 0x34900000, 0x7cf00000, R8101_4, "RTL8102E", },
{ 0x34a00000, 0x7cf00000, R8101_5, "RTL8102E rev.B", },
{ 0x34c00000, 0x7cf00000, R8101_6, "RTL8103E", },
D 28
{ 0x34800000, 0x7c800000, R8101_6, "RTL8103E", },
E 28
I 28
{ 0x34d00000, 0x7cf00000, R8101_7, "RTL8103E", },
{ 0x34e00000, 0x7cf00000, R8101_8, "RTL8103E", },
{ 0x34800000, 0x7c800000, R8101_8, "RTL8103E", },
E 31
I 31
{ 0x34900000, 0x7cf00000, 1500, R8101_4, "RTL8102E", },
{ 0x34a00000, 0x7cf00000, 1500, R8101_5, "RTL8102E rev.B", },
{ 0x34c00000, 0x7cf00000, 1500, R8101_6, "RTL8103E", },
{ 0x34d00000, 0x7cf00000, 1500, R8101_7, "RTL8103E", },
{ 0x34e00000, 0x7cf00000, 1500, R8101_8, "RTL8103E", },
{ 0x34800000, 0x7c800000, 1500, R8101_8, "RTL8103E", },
E 31
E 28
E 23

D 23
{0x24900000,	0x7cf00000, "RTL8102EL",		R8101_CFG_METHOD_4},
{0x24a00000,	0x7cf00000, "RTL8102EL rev.B",		R8101_CFG_METHOD_5},
{0x24c00000,	0x7cf00000, "RTL8103EL",		R8101_CFG_METHOD_6},
{0x24800000,	0x7c800000, "RTL8103EL",		R8101_CFG_METHOD_6},
E 23
I 23
D 31
{ 0x24900000, 0x7cf00000, R8101_4, "RTL8102EL", },
{ 0x24a00000, 0x7cf00000, R8101_5, "RTL8102EL rev.B", },
{ 0x24c00000, 0x7cf00000, R8101_6, "RTL8103EL", },
D 28
{ 0x24800000, 0x7c800000, R8101_6, "RTL8103EL", },
E 28
I 28
{ 0x24d00000, 0x7cf00000, R8101_7, "RTL8103EL", },
{ 0x24e00000, 0x7cf00000, R8101_8, "RTL8103EL", },
{ 0x24800000, 0x7c800000, R8101_8, "RTL8103EL unknown", },
E 31
I 31
{ 0x24900000, 0x7cf00000, 1500, R8101_4, "RTL8102EL", },
{ 0x24a00000, 0x7cf00000, 1500, R8101_5, "RTL8102EL rev.B", },
{ 0x24c00000, 0x7cf00000, 1500, R8101_6, "RTL8103EL", },
{ 0x24d00000, 0x7cf00000, 1500, R8101_7, "RTL8103EL", },
{ 0x24e00000, 0x7cf00000, 1500, R8101_8, "RTL8103EL", },
{ 0x24800000, 0x7c800000, 1500, R8101_8, "RTL8103EL unknown", },
E 31

D 31
{ 0x24100000, 0x7cf00000, R8101_9, "RTL8401EL", },
{ 0x24000000, 0x7c800000, R8101_9, "RTL8401EL unknown", },
E 31
I 31
{ 0x24100000, 0x7cf00000, 1500, R8101_9, "RTL8401EL", },
{ 0x24000000, 0x7c800000, 1500, R8101_9, "RTL8401EL unknown", },
E 31

#ifdef CONFIG_RTL8105 /* not yet, it conflicts 8168 */
D 31
{ 0x2c100000, 0x7cf00000, R8101_10, "RTL8105EL", },
{ 0x2c000000, 0x7c800000, R8101_10, "RTL8105EL unknown", },
E 31
I 31
{ 0x2c100000, 0x7cf00000, 1500, R8101_10, "RTL8105EL", },
{ 0x2c000000, 0x7c800000, 1500, R8101_10, "RTL8105EL unknown", },
E 31

D 31
{ 0x40800000, 0x7c800000, R8101_11, "RTL8105EL unknown", },
E 31
I 31
{ 0x40800000, 0x7c800000, 1500, R8101_11, "RTL8105EL unknown", },
E 31
#endif
E 28
E 23
E 22
E 21
E 16
E 10
};

I 10
D 22
#define	CHIPTABLESIZE	(sizeof(chiptbl_8169)/sizeof(struct chip_info))
E 22
I 22
#define	CHIPTABLESIZE	(sizeof (chiptbl_8169)/sizeof (struct chip_info))
E 22

E 10
D 13
#define	PHY_VER_C	0x3
#define	PHY_VER_D	0x4
#define	PHY_VER_E	0x5
#define	PHY_VER_F	0x6
#define	PHY_VER_G	0x7

E 13
D 10
#define	CHIPTABLESIZE	(sizeof(chiptbl_8169)/sizeof(struct chip_info))

E 10
struct gani_dev {
	/*
	 * Misc HW information
	 */
	struct chip_info	*chip;
D 13
	u_int			phy_rev;
E 13
D 22

E 22
I 22
	uint16_t		svid;
	uint16_t		sdid;
E 22
I 9
	uint8_t			mac[ETHERADDRL];
E 9
I 5
D 16
	uint8_t			cfg2;
E 16
I 16
	uint8_t			busclk;
#define	BUSCLK_PCI33	0
#define	BUSCLK_PCI66	1
#define	BUSCLK_PCIE	2
I 22
	uint8_t			pcie_cap;
E 22
E 16

E 5
	uint32_t		rcr;
I 16
	uint32_t		tcr;
E 16
	boolean_t		need_to_reset;
I 16
D 22
	boolean_t		stats_valid;
E 16
D 6
	volatile uint32_t	imr;
	volatile uint32_t	imr_hw;
E 6
I 6
	uint32_t		imr;
	uint32_t		imr_hw;
I 16
	uint32_t		imr_disabled;	/* for polling */
E 22
I 22
	boolean_t		last_stats_valid;
	uint16_t		imr;
I 23
	uint16_t		isr_pended;
E 23
	boolean_t		msi;
I 23
	boolean_t		initialized;
I 28
#ifdef GEM_CONFIG_VLAN_HW
#ifdef CONFIG_CKSUM_OFFLOAD
E 28
	boolean_t		new_cksum;
I 28
#endif
#endif
E 28
E 23
E 22
E 16
E 6
I 4

I 28
#ifdef TEST_FOVW
E 28
D 21
	clock_t			last_stats_time;
E 21
D 16

I 5
D 9
	uint_t			tx_list_len;
E 5
E 4
#ifdef TX_DELAYED_INTR
D 4
	boolean_t		tx_delayed_intr;
E 4
	uint_t			tx_pkt_len[TX_RING_SIZE];
	uint_t			tx_remain;
E 9
I 9
	int			tx_list_len;
#ifdef CONFIG_POLLING
E 16
I 16
	int			rx_pkt_cnt;
I 28
#endif
E 28
D 22
#ifdef GEM_CONFIG_POLLING
E 16
D 10
	clock_t			rx_last_time;	/**/
	int			rx_intr_cnt;	/* rx intr in tick */
	int			rx_intr_hiwat;	/* max of rx_intr_cnt */
	int			rx_pkt_cnt;	/* rx pkt in tick */

	int			tx_pkt_cnt;	/* rx pkt in tick */

	int			poll_pkt_delay;	/* in number of packets */
	int			poll_pkt_hiwat;	/* max pkt count */
	int			poll_interval; /* polling interval in PCI clk*/
E 10
I 10
	int			last_poll_interval; /* polling interval in uS */
E 22
I 22
#ifdef CONFIG_POLLING
	int			last_poll_interval; /* polling interval in nS */
E 22
E 10
E 9
#endif
I 16
D 28
	uint16_t		adv;
E 28
D 22
	int			media_setup_phase;
E 22
I 22

E 22
E 16
I 5
D 6
#ifdef IO_BARRIER
E 6
I 6
D 9
#ifdef OPT_TDU_INTR
E 6
	kmutex_t		reglock;
#endif
E 9
	struct rtl8169_tally_counters	last_stat;
I 16

D 18
	/* TPQ optimazer */
E 18
I 18
D 28
	/* TPQ optimizer */
I 22
D 23
#if defined(CONFIG_OPT_TPPOLL) || defined(WA_NO_TPPOLL_WRAP)
E 22
E 18
	seqnum_t		tx_activated;
	seqnum_t		tx_finished;
I 22
#endif
E 23
E 22
#ifdef CONFIG_OPT_TPPOLL
	boolean_t		tx_running;
#endif
E 28
D 18
#ifdef WA_NO_DESC_WRAP
	int			tx_last_frags;
#endif
E 18
D 23
#ifdef WA_NO_TPPOLL_WRAP
I 18
	int			tx_last_frags;
E 18
	boolean_t		tx_no_more;
	int			tx_pended;
#endif
E 23
I 21
	kmutex_t		stat_lock;
	timeout_id_t		stat_to_id;
I 30
#ifdef WA_NEW_TX_HANG
	int			tx_last_desc;
#endif
E 30
E 21
E 16
E 5
I 3
D 4
#ifdef OPT_TX_INTR
	ddi_softintr_t		soft_id;
	boolean_t		imr_change_req;
#endif
E 4
E 3
};

/*
 * private functions
 */
D 13

E 13
D 22
 
E 22
I 22

#ifdef DEBUG_LEVEL
/* debugging support */
static void gani_tx_desc_dump(struct gem_dev *dp);
#endif

E 22
/* mii operations */
static void  gani_mii_sync(struct gem_dev *);
I 22
static uint16_t gani_mii_read_raw(struct gem_dev *, uint_t);
static void gani_mii_write_raw(struct gem_dev *, uint_t, uint16_t);
E 22
D 13
static uint16_t  gani_mii_read(struct gem_dev *, int);
I 5
static void gani_mii_write_raw(struct gem_dev *, int, uint16_t);
E 5
static void gani_mii_write(struct gem_dev *, int, uint16_t);
E 13
I 13
static uint16_t gani_mii_read(struct gem_dev *, uint_t);
static void gani_mii_write(struct gem_dev *, uint_t, uint16_t);
E 13

/* nic operations */
I 13
static int gani_attach_chip(struct gem_dev *);
E 13
static int gani_reset_chip(struct gem_dev *);
D 17
static void gani_init_chip(struct gem_dev *);
static void gani_start_chip(struct gem_dev *);
E 17
I 17
D 22
static int gani_init_chip(struct gem_dev *);
E 22
I 22
D 23
static int gani_init_chip_8169(struct gem_dev *);
static int gani_init_chip_8168(struct gem_dev *);
static int gani_init_chip_8101(struct gem_dev *);
E 23
I 23
static int gani_init_chip(struct gem_dev *);
E 23
E 22
static int gani_start_chip(struct gem_dev *);
E 17
D 16
static void gani_stop_chip(struct gem_dev *);
E 16
I 16
static int gani_stop_chip(struct gem_dev *);
E 16
D 17
static void gani_set_media(struct gem_dev *);
static void gani_set_rx_filter(struct gem_dev *);
static void gani_get_stats(struct gem_dev *);
E 17
I 17
static int gani_set_media(struct gem_dev *);
static int gani_set_rx_filter(struct gem_dev *);
static int gani_get_stats(struct gem_dev *);
E 17
D 13
static int gani_init_mac_addr(struct gem_dev *);
E 13

/* descriptor operations */
D 16
static int gani_tx_desc_write(struct gem_dev *dp, uint_t slot,
		    ddi_dma_cookie_t *dmacookie, int frags, uint32_t intreq);
static int gani_rx_desc_write(struct gem_dev *dp, uint_t slot,
E 16
I 16
static int gani_tx_desc_write(struct gem_dev *dp, int slot,
D 22
		    ddi_dma_cookie_t *dmacookie, int frags, uint32_t flag);
E 22
I 22
D 23
		    ddi_dma_cookie_t *dmacookie, int frags, uint64_t flag);
E 23
I 23
    ddi_dma_cookie_t *dmacookie, int frags, uint64_t flag);
E 23
E 22
static void gani_tx_start(struct gem_dev *dp, int slot, int frags);
static void gani_rx_desc_write(struct gem_dev *dp, int slot,
E 16
D 23
		    ddi_dma_cookie_t *dmacookie, int frags);
E 23
I 23
    ddi_dma_cookie_t *dmacookie, int frags);
E 23
static uint_t gani_tx_desc_stat(struct gem_dev *dp, int slot, int ndesc);
D 16
static uint_t gani_rx_desc_stat(struct gem_dev *dp, int slot, int ndesc);
E 16
I 16
static uint64_t gani_rx_desc_stat(struct gem_dev *dp, int slot, int ndesc);
E 16

static void gani_tx_desc_init(struct gem_dev *dp, int slot);
static void gani_rx_desc_init(struct gem_dev *dp, int slot);
D 5
static void gani_tx_desc_clean(struct gem_dev *dp, int slot);
static void gani_rx_desc_clean(struct gem_dev *dp, int slot);
E 5

/* interrupt handler */
D 22
static u_int gani_interrupt(struct gem_dev *dp);
E 22
I 22
static uint_t gani_interrupt(struct gem_dev *dp);
E 22

/* ======================================================== */

/* mapping attributes */
/* Data access requirements. */
static struct ddi_device_acc_attr gani_dev_attr = {
	DDI_DEVICE_ATTR_V0,
	DDI_STRUCTURE_LE_ACC,
	DDI_STRICTORDER_ACC
};

I 16
D 22
static struct ddi_device_acc_attr gani_desc_attr = {
	DDI_DEVICE_ATTR_V0,
	DDI_NEVERSWAP_ACC,
	DDI_STRICTORDER_ACC
};

E 22
E 16
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
I 28
D 29
#if 0
E 29
E 28
D 16
	0xffffffffull,		/* dma_attr_count_max */
E 16
I 16
D 17
	0x00001fffull,		/* dma_attr_count_max */
E 17
I 17
D 22
	0x3fffull,		/* dma_attr_count_max */
E 22
I 22
	0xffffull,		/* dma_attr_count_max */
I 28
D 29
#else
	0x1fffull,		/* dma_attr_count_max */
#endif
E 29
E 28
E 22
E 17
E 16
	1,			/* dma_attr_align */
D 16
	0xffffffff,		/* dma_attr_burstsizes */
E 16
I 16
D 17
	0x00001fff,		/* dma_attr_burstsizes */
E 17
I 17
D 22
	0x3fff,			/* dma_attr_burstsizes */
E 22
I 22
	0xffff,			/* dma_attr_burstsizes */
E 22
E 17
E 16
	1,			/* dma_attr_minxfer */
D 16
	0xffffffffull,		/* dma_attr_maxxfer */
E 16
I 16
D 17
	0x00003fffull,		/* dma_attr_maxxfer */
E 17
I 17
D 22
	0x3fffull,		/* dma_attr_maxxfer */
E 22
I 22
	0x0000ffffull,		/* dma_attr_maxxfer */
E 22
E 17
E 16
	0xffffffffull,		/* dma_attr_seg */
D 16
	1,			/* dma_attr_sgllen */
E 16
I 16
	0 /* pached later */,	/* dma_attr_sgllen */
E 16
	1,			/* dma_attr_granular */
	0			/* dma_attr_flags */
};

static ddi_dma_attr_t gani_dma_attr_buf64 = {
	DMA_ATTR_V0,		/* dma_attr_version */
	0,			/* dma_attr_addr_lo */
	0xffffffffffffull,	/* dma_attr_addr_hi */
D 16
	0xffffffffffffull,	/* dma_attr_count_max */
E 16
I 16
D 17
	0x00001fffull,		/* dma_attr_count_max */
E 17
I 17
D 22
	0x3fffull,		/* dma_attr_count_max */
E 22
I 22
	0xffffull,		/* dma_attr_count_max */
E 22
E 17
E 16
	1,			/* dma_attr_align */
D 16
	0xffffffff,		/* dma_attr_burstsizes */
E 16
I 16
D 17
	0x00001fff,		/* dma_attr_burstsizes */
E 17
I 17
D 22
	0x3fff,			/* dma_attr_burstsizes */
E 22
I 22
	0xffff,			/* dma_attr_burstsizes */
E 22
E 17
E 16
	1,			/* dma_attr_minxfer */
D 16
	0xffffffffull,		/* dma_attr_maxxfer */
	0xffffffffull,		/* dma_attr_seg */
	1,			/* dma_attr_sgllen */
E 16
I 16
D 17
	0x00001fffull,		/* dma_attr_maxxfer */
E 17
I 17
D 22
	0x3fffull,		/* dma_attr_maxxfer */
E 22
I 22
	0x00000000ffffull,	/* dma_attr_maxxfer */
E 22
E 17
	0xffffffffffffull,	/* dma_attr_seg */
	0 /* pached later */,	/* dma_attr_sgllen */
E 16
	1,			/* dma_attr_granular */
	0			/* dma_attr_flags */
};

D 5
static ddi_dma_attr_t gani_dma_attr_nosc32 = {
E 5
I 5
static ddi_dma_attr_t gani_dma_attr_desc = {
E 5
	DMA_ATTR_V0,		/* dma_attr_version */
	0,			/* dma_attr_addr_lo */
	0xffffffffull,		/* dma_attr_addr_hi */
D 16
	0xffffffffull,		/* dma_attr_count_max */
E 16
I 16
D 17
	DESC_MAX_SIZE-1,	/* dma_attr_count_max */
E 17
I 17
	0xffffffffull,		/* dma_attr_count_max */
E 17
E 16
D 13
	256,			/* dma_attr_align */
E 13
I 13
	DESC_BASE_ALIGN,	/* dma_attr_align */
E 13
D 16
	0xffffffff,		/* dma_attr_burstsizes */
	1,			/* dma_attr_minxfer */
	0xffffffffull,		/* dma_attr_maxxfer */
E 16
I 16
D 17
	DESC_MAX_SIZE-1,	/* dma_attr_burstsizes */
	DESC_BASE_ALIGN,	/* dma_attr_minxfer */
	0x0000ffffull,		/* dma_attr_maxxfer */
E 17
I 17
	0,			/* dma_attr_burstsizes */
	1,			/* dma_attr_minxfer */
	0xffffffffull,		/* dma_attr_maxxfer */
E 17
E 16
	0xffffffffull,		/* dma_attr_seg */
	1,			/* dma_attr_sgllen */
	1,			/* dma_attr_granular */
	0			/* dma_attr_flags */
};

/* =============================================================== */
/*
I 13
 * Debugging support
 */
/* =============================================================== */
D 22
#ifdef DEBUG_LEVEL
E 22
I 22
#ifdef DEBUG_HANG
E 22
static void
gani_dump_regs(struct gem_dev *dp, char *m)
{
	int		i;
D 22
	struct gani_dev	*lp = (struct gani_dev *)dp->private;
E 22

	cmn_err(CE_CONT, "!%s: register dump (%s)", dp->name, m);

	for (i = 0; i < 256; i += 8) {
		cmn_err(CE_CONT,
D 22
			"!%02x: %02x %02x %02x %02x %02x %02x %02x %02x",
			i,
			INB(dp, i+0), INB(dp, i+1),
			INB(dp, i+2), INB(dp, i+3),
			INB(dp, i+4), INB(dp, i+5),
			INB(dp, i+6), INB(dp, i+7));
E 22
I 22
		    "!%02x: %02x %02x %02x %02x %02x %02x %02x %02x",
		    i,
		    INB(dp, i+0), INB(dp, i+1),
		    INB(dp, i+2), INB(dp, i+3),
		    INB(dp, i+4), INB(dp, i+5),
		    INB(dp, i+6), INB(dp, i+7));
E 22
D 16

E 16
	}
}
#endif
/* =============================================================== */
/*
E 13
 * Hardware manupilation
 */
/* =============================================================== */
I 22
/* IO routines for PCI-E phy */
static uint16_t
gani_ephy_read(struct gem_dev *dp, uint_t location)
{
	int	i;

	OUTL(dp, EPHYAR, location << EPHYAR_REGADDR_SHIFT);

	drv_usecwait(100);

	for (i = 0; (INL(dp, EPHYAR) & EPHYAR_FLAG) == 0; i++) {
		if (i > 10) {
			cmn_err(CE_CONT, "%s: %s: timeout",
			    dp->name, __func__);
			return (0);
		}
		drv_usecwait(100);
	}

	return ((uint16_t)(INL(dp, EPHYAR) & EPHYAR_DATA));
}

static void
gani_ephy_write(struct gem_dev *dp, uint_t location, uint16_t val)
{
	int	i;

	OUTL(dp, EPHYAR,
	    EPHYAR_FLAG | (location << EPHYAR_REGADDR_SHIFT) | val);

	for (i = 0; INL(dp, EPHYAR) & EPHYAR_FLAG; i++) {
		if (i > 10) {
			cmn_err(CE_CONT, "%s: %s: timeout",
			    dp->name, __func__);
			return;
		}
		drv_usecwait(100);
	}
}

static uint32_t
gani_csi_read(struct gem_dev *dp, uint_t addr)
{
D 28
	int		i;
E 28
I 28
	int	i;
E 28

D 28
	OUTL(dp, CSIAR, (CSIAR_ByteEn << CSIAR_ByteEn_SHIFT) | addr);
E 28
I 28
	OUTL(dp, CSIAR, CSIAR_ByteEn | addr);
E 28

	/* Check if the RTL8101 has completed CSI read */
	for (i = 0; (INL(dp, CSIAR) & CSIAR_FLAG) == 0; i++) {
		if (i > 10) {
			cmn_err(CE_WARN, "%s: %s timeout",
			    dp->name, __func__);
			return (0);
		}
		drv_usecwait(100);
	}

	return (INL(dp, CSIDR));
}

static void
gani_csi_write(struct gem_dev *dp, uint_t addr, uint32_t val)
{
	int	i;

	OUTL(dp, CSIDR, val);
D 28
	OUTL(dp, CSIAR,
	    CSIAR_FLAG | (CSIAR_ByteEn << CSIAR_ByteEn_SHIFT) | addr);
E 28
I 28
	OUTL(dp, CSIAR, CSIAR_FLAG | CSIAR_ByteEn | addr);
E 28

	for (i = 0; INL(dp, CSIAR) & CSIAR_FLAG; i++) {
		if (i > 10) {
			break;
		}
		drv_usecwait(100);
	}
}

I 28
static uint32_t
gani_efuse_read(struct gem_dev *dp, uint_t index)
{
	int	i;
	uint32_t	val;
	struct gani_dev	*lp = dp->private;

	OUTL(dp, EFUSEAR, EFUSE_READ | (index << EFUSE_REG_SHIFT));
	drv_usecwait(100);

	for (i = 0; (INL(dp, EFUSEAR) & EFUSE_READ_OK) == 0; i++) {
		if (i > 300) {
			/* time out */
			val = 0xff;
			cmn_err(CE_WARN, "!%s: %s: timeout",
			    dp->name, __func__);
			goto x;
		}
		drv_usecwait(100);
	}

	val = INL(dp, EFUSEAR) & EFUSE_DATA;
x:
	return (val);
}

E 28
E 22
static int
D 22
gani_reset_chip(struct gem_dev *dp)
E 22
I 22
D 23
gani_reset_chip_8169(struct gem_dev *dp)
E 23
I 23
gani_reset_chip(struct gem_dev *dp)
E 23
E 22
{
D 9
	int	i;
E 9
I 9
	int		i;
I 28
	uint32_t	val;
E 28
D 22
	struct gani_dev	*lp = (struct gani_dev *)dp->private;
E 22
I 22
	struct gani_dev	*lp = dp->private;
E 22
E 9

I 11
D 16
	DPRINTF(1, (CE_CONT, "!%s: gani_reset_chip: called", dp->name));
E 16
I 16
D 22
	DPRINTF(1, (CE_CONT, "!%s: %s: called", dp->name, __func__));
E 22
I 22
	DPRINTF(0, (CE_CONT, "!%s: %s: called", dp->name, __func__));
I 23

E 23
E 22
E 16
D 13

E 13
I 13
#ifdef DEBUG_HANG
	gani_dump_regs(dp, "reset_chip 1");
#endif
E 13
E 11
I 9
D 23
	/* disable interrupts */
D 12
	OUTW(dp, IMR, lp->imr_hw = 0); FLSHW(dp, IMR);
E 12
I 12
D 22
	OUTW(dp, IMR, lp->imr_hw = 0);
E 22
I 22
	OUTW(dp, IMR, 0);
	FLSHW(dp, IMR);
E 23
I 23
D 27
	if (lp->initialized) {
E 27
I 27
	if (!lp->initialized) {
E 27
		OUTB(dp, CR9346, CR9346_EEM_WE);
		OUTB(dp, CFG1, INB(dp, CFG1) | CFG1_PMEn);
		OUTB(dp, CFG5, INB(dp, CFG5) & CFG5_PME_STS);
		OUTB(dp, CR9346, CR9346_EEM_NORMAL);
E 23
E 22
E 12

I 24
		if (lp->busclk == BUSCLK_PCI66) {
			if (lp->chip->type == R8169_5) {
				OUTL(dp, 0x7c, 0x000fffff);
			} else if (lp->chip->type == R8169_6) {
D 28
				OUTL(dp, 0x7c, 0x009fffff);
E 28
I 28
				OUTL(dp, 0x7c, 0x003fffff);
E 28
			}
		} else if (lp->busclk == BUSCLK_PCI33) {
			if (lp->chip->type == R8169_5) {
				OUTL(dp, 0x7c, 0x000fff00);
			} else if (lp->chip->type == R8169_6) {
D 28
				OUTL(dp, 0x7c, 0x009fff00);
E 28
I 28
				OUTL(dp, 0x7c, 0x003fff00);
E 28
			}
		}

E 24
E 9
D 23
	OUTB(dp, CR, CR_RST);
I 11
D 16
	drv_usecwait(1000);
E 16
E 11

I 9
D 10
	/*
	 * XXX - experimental
	 * Don't touch on the nic for 20ms until hardware will have been
	 * completely initialized.
	 */
	drv_usecwait(20000);

E 10
E 9
D 15
	i = 0;
	while ((INB(dp, CR) & CR_RST) != 0) {
		if (++i > 100) {
E 15
I 15
D 22
	for (i = 0; (INB(dp, CR) & CR_RST) != 0; i++) {
E 22
I 22
	for (i = 0; INB(dp, CR) & CR_RST; i++) {
E 22
		if (i > 100) {
E 15
			/* time out */
D 10
			cmn_err(CE_WARN, "%s: failed to reset: timeout",
E 10
I 10
			cmn_err(CE_WARN, "!%s: failed to reset: timeout",
E 10
D 22
					dp->name);
E 22
I 22
			    dp->name);
E 22
I 10
D 13
#ifdef notdef
E 13
E 10
I 9
D 15
			bzero(lp->mac, ETHERADDRL);
E 15
E 9
D 16
			return -1;
E 16
I 16
			return (GEM_FAILURE);
E 16
I 10
D 13
#else
			break;
#endif
E 13
E 10
		}
		drv_usecwait(10);
E 23
I 23
		lp->initialized = B_TRUE;
E 23
	}
I 16

I 22
D 23
#ifdef notdef
	/* clear bogus interrupts */
	OUTW(dp, ISR, 0xffff);
	FLSHW(dp, ISR);
#endif
	OUTB(dp, 0x82, 0x01);
E 23
I 23
D 28
	if (GANI_PCIE(lp->chip->type)) {
E 28
I 28
	val = INL(dp, RCR);
	if (val & RCR_ACCEPT_MODE) {
		OUTL(dp, RCR, val & ~RCR_ACCEPT_MODE);
	}

	if (GANI_PCIE(lp)) {
E 28
		switch (lp->chip->type) {
I 28
		/* 016 */
E 28
		case R8168_1: /* RTL8168B rev.B */
		case R8168_2: /* RTL8168B rev.E */
		case R8168_3: /* RTL8168B rev.F */
I 28

E 28
		case R8101_1: /* RTL8101E rev.B */
		case R8101_2: /* RTL8101E rev.E */
		case R8101_3: /* RTL8101E rev.F */
			/* EMPTY */
			break;
E 23

I 28
		/* 016 */
		case R8168_11: /* RTL8168DP */
		case R8168_12: /* RTL8168DP */
			for (i = 0;
			    (INB(dp, TPPoll) & TPPoll_NPQ) && i < 1000;
			    i++) {
				drv_usecwait(20);
			}
			break;

E 28
D 23
	/* XXX - set latency timer in PCI config to 0x40 */

E 22
	switch (lp->chip->type) {
D 22
	case MAC_VER_8169S_D:
E 22
I 22
	case R8169_CFG_METHOD_2:
E 22
		OUTB(dp, 0x82, 0x01);
		break;
E 23
I 23
		default:
			OUTB(dp, CR, CR_STOP | CR_RE | CR_TE);
			drv_usecwait(100);
			break;
		}
E 23
	}

E 16
D 13

E 13
I 13
D 23
#ifdef DEBUG_HANG
	gani_dump_regs(dp, "reset_chip 2");
#endif
E 13
I 9
D 15
	/*
	 * The mac address in EEPROM has been loaded into the ID registers
	 * after chip reset.
	 */
	for (i = 0; i < ETHERADDRL; i++) {
		lp->mac[i] = INB(dp, IDR + i);
	}

E 15
E 9
D 16
	return 0;
E 16
I 16
	return (GEM_SUCCESS);
E 16
}

I 22
static int
gani_reset_chip_8168(struct gem_dev *dp)
{
	int		i;
	struct gani_dev	*lp = dp->private;

	DPRINTF(0, (CE_CONT, "!%s: %s: called", dp->name, __func__));
#ifdef DEBUG_HANG
	gani_dump_regs(dp, "reset_chip 1");
#endif
E 23
	/* disable interrupts */
	OUTW(dp, IMR, 0);
	FLSHW(dp, IMR);

D 23
	switch (lp->chip->type) {
	case R8168_CFG_METHOD_1: /* MAC_VER_8168B_B */
	case R8168_CFG_METHOD_2: /* MAC_VER_8168B_E */
	case R8168_CFG_METHOD_3: /* MAC_VER_8168B_F */
		/* EMPTY */
		break;
	default:
		OUTB(dp, CR, CR_STOP | CR_RE | CR_TE);
		drv_usecwait(100);
		break;
	}

E 23
	OUTB(dp, CR, CR_RST);

	for (i = 0; INB(dp, CR) & CR_RST; i++) {
D 23
		if (i > 100) {
			/* time out */
E 23
I 23
		if (i > 10000) {
			/* timeout */
E 23
			cmn_err(CE_WARN, "!%s: failed to reset: timeout",
			    dp->name);
			return (GEM_FAILURE);
		}
		drv_usecwait(10);
	}

I 28
	/* 013 */
	if (lp->chip->type == R8168_11) {
		OUTL(dp, OCPDR, 0x00000001U);
		OUTL(dp, OCPAR, 0x80001038U);
		OUTL(dp, OCPDR, 0x00000001U);
		OUTL(dp, OCPAR, 0x00001030U);

		OUTL(dp, OCPAR, 0x00001034U);
		for (i = 0; (INL(dp, OCPDR) & 0xffffU); i++) {
			if (i > 1000) {
				cmn_err(CE_CONT, "!%s: %s: OCP timeout",
				    dp->name, __func__);
				break;
			}
			drv_usecwait(100);
		}
	}

E 28
D 23
#ifdef notdef
E 23
	/* clear bogus interrupts */
I 23
	lp->isr_pended = INW(dp, ISR);
E 23
D 28
	OUTW(dp, ISR, 0xffff);
E 28
I 28
	OUTW(dp, ISR, 0xffffU);
E 28
	FLSHW(dp, ISR);
D 23
#endif
E 23

I 23
D 28
	if (GANI_PCI(lp->chip->type)) {
E 28
I 28
	if (GANI_PCI(lp)) {
E 28
		OUTB(dp, 0x82, 0x01);

		switch (lp->chip->type) {
		case R8169_2: /* RTL8169S rev.D */
			OUTB(dp, 0x82, 0x01);
			break;
		}
	}

E 23
#ifdef DEBUG_HANG
	gani_dump_regs(dp, "reset_chip 2");
#endif
	return (GEM_SUCCESS);
}

D 23
static int
gani_reset_chip_8101(struct gem_dev *dp)
{
	int		i;
	struct gani_dev	*lp = dp->private;

	DPRINTF(0, (CE_CONT, "!%s: %s: called", dp->name, __func__));

	/* disable interrupts */
	OUTW(dp, IMR, 0);
	FLSHW(dp, IMR);

	switch (lp->chip->type) {
	case R8101_CFG_METHOD_1:
	case R8101_CFG_METHOD_2:
	case R8101_CFG_METHOD_3:
		/* EMPTY */
		break;

	default:
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
	return (GEM_SUCCESS);
}

E 23
E 22
/*
 * Setup rtl8169
 */
D 17
static void
E 17
I 17
static int
E 17
D 22
gani_init_chip(struct gem_dev *dp)
E 22
I 22
D 23
gani_init_chip_8169(struct gem_dev *dp)
E 23
I 23
gani_init_8169(struct gem_dev *dp, ddi_acc_handle_t conf_ha)
E 23
E 22
{
I 11
D 16
	uint32_t	val;
E 16
I 16
	uint32_t		val;
I 22
	uint32_t		cpcmd;
E 22
D 23
	ddi_acc_handle_t	conf_ha;
E 23
E 16
E 11
I 10
D 22
	struct gani_dev	*lp = (struct gani_dev *)dp->private;
E 22
I 22
	struct gani_dev		*lp = dp->private;
E 22

D 11
	DPRINTF(2, (CE_CONT, "!%s: gani_init_chip: called", dp->name));
E 11
I 11
D 16
	DPRINTF(1, (CE_CONT, "!%s: gani_init_chip: called", dp->name));
E 16
I 16
D 22
	DPRINTF(1, (CE_CONT, "!%s: %s: called", dp->name, __func__));
E 22
I 22
	DPRINTF(0, (CE_CONT, "!%s: %s: called", dp->name, __func__));
E 22
E 16
E 11

D 22
	/* XXX - disable interrupts */
D 12
	OUTW(dp, IMR, lp->imr_hw = 0); FLSHW(dp, IMR);
E 12
I 12
	OUTW(dp, IMR, lp->imr_hw = 0);
E 12

D 16
	/* ID registers will be set later by gani_set_rx_filter */
E 16
I 16
	if (pci_config_setup(dp->dip, &conf_ha) == DDI_SUCCESS) {
		/* fix config registers */
E 16
I 11
D 21

E 21
I 21
		if (!GANI_PCIE(lp->chip->type)) {
			pci_config_put8(conf_ha, PCI_CONF_CACHE_LINESZ, 8);
		}
E 21
E 11
D 16
	/* Multicast hash registers will be  set later by gani_set_rx_filter */
E 16
I 16
		if (lp->chip->type == MAC_VER_8101E /* M13 */) {
D 21
			pci_config_put16(conf_ha, 0x68, 0x00);
			pci_config_put16(conf_ha, 0x69, 0x08);
E 21
I 21
			pci_config_put8(conf_ha, 0x68, 0x00);
			pci_config_put8(conf_ha, 0x69, 0x08);
E 21
		}
D 21
		if (lp->chip->type == MAC_VER_8169SC /* M5 */) {
E 21
I 21
		if (lp->chip->type == MAC_VER_8110SC /* M5 */) {
E 21
			if (lp->busclk == BUSCLK_PCI66) {
D 21
				OUTL(dp, 0x7c, 0x000700ff);
			} else /* PCI33*/ {
E 21
I 21
				OUTL(dp, 0x7c, 0x0007ffff);
			} else {
E 21
				OUTL(dp, 0x7c, 0x0007ff00);
			}
			pci_config_put16(conf_ha, PCI_CONF_COMM,
				pci_config_get16(conf_ha, PCI_CONF_COMM)
						& ~PCI_COMM_MEMWR_INVAL);
		}
		pci_config_teardown(&conf_ha);
E 16

I 16
	} else {
E 22
I 22
D 23
	if (pci_config_setup(dp->dip, &conf_ha) != DDI_SUCCESS) {
E 22
		cmn_err(CE_WARN, "!%s: pci_config_setup failed", dp->name);
I 22
		return (GEM_FAILURE);
E 22
	}
E 23
I 23
D 31
	OUTW(dp, RMS,
	    sizeof (struct ether_header) + 4 + dp->mtu + ETHERFCSL + 4);
E 31
I 31
	OUTW(dp, RMS, RMS_PCI(dp->mtu));
E 31
	DPRINTF(0, (CE_CONT, "!%s: RMS %d", dp->name, INW(dp, RMS)));
E 23

I 22
D 23
	/* XXX - disable interrupts */
	OUTW(dp, IMR, 0);
	FLSHW(dp, IMR);

E 23
E 22
E 16
I 11
	/* make configuration registers writable */
	OUTB(dp, CR9346, CR9346_EEM_WE);

D 16
	/* CpCR */
E 16
I 16
D 22
	if (!GANI_8168_OR_LATER(lp->chip->type)) {
		/* enable tx and rx */
		OUTB(dp, CR, CR_RE | CR_TE);
	}

E 22
	OUTB(dp, ETThR, 0x3f);
D 22
	OUTW(dp, RMS, dp->rx_buf_len);
	DPRINTF(2 , (CE_CONT, "!%s: RMS %d", dp->name, INW(dp, RMS)));
E 22

D 22
	if (!GANI_8168_OR_LATER(lp->chip->type)) {
		OUTL(dp, RCR, lp->rcr);
		OUTL(dp, TCR, lp->tcr);
E 22
I 22
	/* configure CPlus command register */
	cpcmd = INW(dp, CpCR);
I 27
	cpcmd &= ~(CpCR_RxVLAN | CpCR_RxChkSum);
E 27
	cpcmd |= CpCR_MulRW;
D 24
#ifdef CONFIG_DAC
	cpcmd |= CpCR_DAC;
#endif
E 24
I 24
	if (gani_64bit_addr) {
		cpcmd |= CpCR_DAC;
	}
E 24
#ifdef GEM_CONFIG_VLAN_HW
	cpcmd |= CpCR_RxVLAN;
#ifdef GEM_CONFIG_CKSUM_OFFLOAD
	cpcmd |= CpCR_RxChkSum;
#endif /* GEM_CONFIG_CKSUM_OFFLOAD */
#endif /* GEM_CONFIG_VLAN_HW */
	OUTW(dp, CpCR, cpcmd);

	/* fix pci configuration registers */
	pci_config_put8(conf_ha, PCI_CONF_CACHE_LINESZ, 8);

D 23
	if (lp->chip->type == R8169_CFG_METHOD_2) {
E 23
I 23
	if (lp->chip->type == R8169_2 /* RTL8169S rev.D */) {
E 23
		cpcmd |= CpCR_EnAnaPLL;
	} else {
		cpcmd &= ~CpCR_EnAnaPLL;
E 22
	}
I 22
	OUTW(dp, CpCR, cpcmd);
E 22

D 22
	/* CPlus command register */
	OUTW(dp, CpCR, INW(dp, CpCR));
E 16
	val = INW(dp, CpCR);
D 16
	OUTW(dp, CpCR, val);	/* XXX */
	if (lp->chip->type == MAC_VER_D || lp->chip->type == MAC_VER_E) {
		/* what is this ? */
		val |= 0x4000;
E 16
I 16
#ifdef CONFIG_VLAN
	/* common capability for CpCR */
	val |= CpCR_RxVLAN;
I 17
#  ifdef GEM_CONFIG_CKSUM_OFFLOAD
	val |= CpCR_RxChkSum;
#  endif
E 17
#endif
I 21
	if (!GANI_PCIE(lp->chip->type)) {
		val |= CpCR_MulRW;
E 22
I 22
	pci_config_put8(conf_ha, PCI_CONF_LATENCY_TIMER, 0x40);

D 24
	if (lp->busclk == BUSCLK_PCI66) {
D 23
		if (lp->chip->type == R8169_CFG_METHOD_5) {
E 23
I 23
		if (lp->chip->type == R8169_5 /* RTL8169SC rev.D */) {
E 23
			OUTL(dp, 0x7c, 0x000fffff);
D 23
		} else if (lp->chip->type == R8169_CFG_METHOD_6) {
E 23
I 23
		} else if (lp->chip->type == R8169_6 /* RTL8169SC rev.E */) {
E 23
			OUTL(dp, 0x7c, 0x009fffff);
		}
	} else {
D 23
		if (lp->chip->type == R8169_CFG_METHOD_5) {
E 23
I 23
		if (lp->chip->type == R8169_5 /* RTL8169SC rev.D */) {
E 23
			OUTL(dp, 0x7c, 0x000fff00);
D 23
		} else if (lp->chip->type == R8169_CFG_METHOD_6) {
E 23
I 23
		} else if (lp->chip->type == R8169_6 /* RTL8169SC rev.E */) {
E 23
			OUTL(dp, 0x7c, 0x009fff00);
		}
E 22
	}
E 21
D 22
	switch (lp->chip->type) {
D 21
	case MAC_VER_8169SB: case MAC_VER_8169:
		break;

	case MAC_VER_8169S_D: case MAC_VER_8169S_E:
E 21
I 21
	case MAC_VER_8169S_D: /* M2 */
	case MAC_VER_8169S_E: /* M3 */
E 21
		val |= 1 << 14;
D 21
		/* fall down */
	default:
		val |= CpCR_MulRW;
E 21
		break;
E 16
	}
D 16
	OUTW(dp, CpCR, val | CpCR_MulRW);
E 16
I 16
	OUTW(dp, CpCR, val);
E 22
E 16

E 24
	/* XXX - undocumented */
D 24
	OUTW(dp, 0xe2, 0);
E 24
I 24
D 28
	OUTW(dp, INTRMOD, 0);
E 28
I 28
	OUTW(dp, 0xe2, 0);
E 28
E 24

	/* Transmit Normal Priority Descriptors */
D 14
	DPRINTF(1 , (CE_CONT, "!%s: TNPDS 0x%llx", dp->name, dp->tx_ring_dma));
E 14
I 14
D 22
	DPRINTF(4 , (CE_CONT, "!%s: TNPDS 0x%llx", dp->name, dp->tx_ring_dma));
E 14
D 16
	OUTL(dp, TNPDSL, (uint32_t)dp->tx_ring_dma);
	OUTL(dp, TNPDSH, (uint32_t)(dp->tx_ring_dma >> 32));
E 16
I 16
	OUTL(dp, TNPDSL, (uint32_t) dp->tx_ring_dma);
	OUTL(dp, TNPDSH, (uint32_t) (dp->tx_ring_dma >> 32));
E 22
I 22
	DPRINTF(4, (CE_CONT, "!%s: TNPDS 0x%llx",
	    dp->name, (unsigned long long)dp->tx_ring_dma));
	OUTL(dp, TNPDSL, (uint32_t)dp->tx_ring_dma);
	OUTL(dp, TNPDSH, (uint32_t)(dp->tx_ring_dma >> 32));
E 22
E 16

D 16

E 16
	/* Transmit High Priority Descriptors: Do nothing */
	OUTL(dp, THPDSL, 0);
	OUTL(dp, THPDSH, 0);

	/* Receive Descriptor Start Address register */
D 16
	OUTL(dp, RDSARL, (uint32_t)dp->rx_ring_dma);
	OUTL(dp, RDSARH, (uint32_t)(dp->rx_ring_dma >> 32));
E 16
I 16
D 22
	OUTL(dp, RDSARL, (uint32_t) dp->rx_ring_dma);
	OUTL(dp, RDSARH, (uint32_t) (dp->rx_ring_dma >> 32));
E 16
D 14
	DPRINTF(1 , (CE_CONT, "!%s: RDSAR 0x%llx", dp->name, dp->rx_ring_dma));
E 14
I 14
	DPRINTF(4 , (CE_CONT, "!%s: RDSAR 0x%llx", dp->name, dp->rx_ring_dma));
E 22
I 22
	OUTL(dp, RDSARL, (uint32_t)dp->rx_ring_dma);
	OUTL(dp, RDSARH, (uint32_t)(dp->rx_ring_dma >> 32));
	DPRINTF(4, (CE_CONT, "!%s: RDSAR 0x%llx",
	    dp->name, (unsigned long long)dp->rx_ring_dma));
E 22
E 14

I 16
D 22
	if (GANI_8168_OR_LATER(lp->chip->type)) {
		OUTB(dp, CR, CR_RE | CR_TE);
		OUTL(dp, RCR, lp->rcr);
		OUTL(dp, TCR, lp->tcr);
	}
E 22
I 22
	/* Missed packet counter: clear it */
	OUTL(dp, MPC, 0);
E 22

I 22
	/* MulInt Register */
	OUTW(dp, MULINT, INW(dp, MULINT) & 0xf000);

	/* Interrupt status register: clear bogus interrupts */
D 28
	OUTW(dp, ISR, 0xffff);
E 28
I 28
	OUTW(dp, ISR, 0xffffU);
E 28
	FLSHW(dp, ISR);

	/* enable tx and rx before writing rcr and tcr */
	OUTB(dp, CR, CR_RE | CR_TE);

	OUTL(dp, RCR, lp->rcr);
	OUTL(dp, TCR, lp->tcr);

E 22
E 16
	/* make config registers read only */
	OUTB(dp, CR9346, CR9346_EEM_NORMAL);
	drv_usecwait(10);

E 11
D 16
	/* Dump Tally Count Register : */
	OUTL(dp, DTCCRH, (uint32_t)(TALLY_DMA(dp) >> 32));
#ifdef SANITY
	OUTL(dp, DTCCRL, 0);
#endif
	bzero(&lp->last_stat, sizeof(struct rtl8169_tally_counters));
E 16
I 16
D 22
	/* Missed packet counter: clear it */
	OUTL(dp, MPC, 0);
E 22
I 22
	/* TimerInt Register */
	OUTL(dp, TimerInt, 0);
E 22
E 16

I 22
	/* Timer count register: test count rate */
	OUTL(dp, TCTR, 0);
#if DEBUG_LEVEL > 3
	drv_usecwait(1000);
	cmn_err(CE_CONT, "!%s: TCTR:%d in 1mS", dp->name, INL(dp, TCTR));
#endif
D 23
#ifdef DEBUG_HANG
	gani_dump_regs(dp, "init_chip done");
#endif
#ifdef CONFIG_POLLING
	lp->last_poll_interval = 0; /* polling interval in nS */
#endif
#ifdef CONFIG_OPT_TPPOLL
	lp->tx_running = B_FALSE;
#endif
#if defined(CONFIG_OPT_TPPOLL) || defined(WA_NO_TPPOLL_WRAP)
	lp->tx_activated = 0;
	lp->tx_finished = 0;
#endif
#ifdef WA_NO_TPPOLL_WRAP
	lp->tx_no_more = B_FALSE;
	lp->tx_pended = 0;
#endif
	lp->last_stats_valid = B_FALSE;
E 22
D 16
	/* Flash memory read/wirte register: no need to touch */
E 16

I 22
	pci_config_teardown(&conf_ha);

E 23
	return (GEM_SUCCESS);
}

static int
D 23
gani_init_chip_8168(struct gem_dev *dp)
E 23
I 23
gani_init_8168(struct gem_dev *dp, ddi_acc_handle_t conf_ha)
E 23
{
	uint32_t		val;
	uint32_t		cpcmd;
	uint32_t		devcsr;
D 23
	ddi_acc_handle_t	conf_ha;
E 23
	struct gani_dev		*lp = dp->private;

	DPRINTF(0, (CE_CONT, "!%s: %s: called", dp->name, __func__));

D 23
	if (pci_config_setup(dp->dip, &conf_ha) != DDI_SUCCESS) {
		cmn_err(CE_WARN, "!%s: pci_config_setup failed", dp->name);
		return (GEM_FAILURE);
	}
E 23
I 23
	pci_config_put8(conf_ha, PCI_CONF_LATENCY_TIMER, 0x40);
E 23

D 23
	/* XXX - disable interrupts */
	OUTW(dp, IMR, 0);
	FLSHW(dp, IMR);

E 23
	/* make configuration registers writable */
	OUTB(dp, CR9346, CR9346_EEM_WE);

	/* reserved */
	OUTB(dp, ETThR, 0x3f);

D 23
	DPRINTF(2, (CE_CONT, "!%s: RMS %d", dp->name, INW(dp, RMS)));
E 23
I 23
D 31
	OUTW(dp, RMS, dp->mtu + sizeof (struct ether_header) + 8 + 1);
E 31
I 31
	OUTW(dp, RMS, RMS_PCIE(dp->mtu));
E 31
	DPRINTF(0, (CE_CONT, "!%s: RMS %d", dp->name, INW(dp, RMS)));
E 23

D 23
	/* fix pci configuration registers */

E 23
	/* configure CPlus command register */
	cpcmd = INW(dp, CpCR);
	cpcmd |= CpCR_StatDis | CpCR_INTT_1;
I 27
	cpcmd &= ~(CpCR_RxVLAN | CpCR_RxChkSum);
E 27
D 23
#ifdef CONFIG_DAC
	cpcmd |= CpCR_DAC;
#endif
E 23

#ifdef GEM_CONFIG_VLAN_HW
	/* common capability for CpCR */
	cpcmd |= CpCR_RxVLAN;
#ifdef GEM_CONFIG_CKSUM_OFFLOAD
	if (dp->mtu <= ETHERMTU) {
		cpcmd |= CpCR_RxChkSum;
	} else {
		cpcmd &= ~CpCR_RxChkSum;
	}
#endif /* GEM_CONFIG_CKSUM_OFFLOAD */
#endif /* GEM_CONFIG_VLAN_HW */
	OUTW(dp, CpCR, cpcmd);

	/* XXX - undocumented */
	OUTW(dp, 0xe2, 0x5151);

	/* Transmit Normal Priority Descriptors */
D 27
	DPRINTF(4, (CE_CONT, "!%s: TNPDS 0x%llx",
E 27
I 27
	DPRINTF(2, (CE_CONT, "!%s: TNPDS 0x%llx",
E 27
D 29
	    dp->name, (unsigned long long)dp->tx_ring_dma));
E 29
I 29
	    dp->name, (uint64_t)dp->tx_ring_dma));
E 29
D 27
	OUTL(dp, TNPDSL, (uint32_t)dp->tx_ring_dma);
E 27
	OUTL(dp, TNPDSH, (uint32_t)(dp->tx_ring_dma >> 32));
I 27
	OUTL(dp, TNPDSL, (uint32_t)dp->tx_ring_dma);
E 27
D 23

E 23
I 23
#ifdef SANITY
	/* Transmit High Priority Descriptors: Do nothing */
D 27
	OUTL(dp, THPDSL, 0);
E 27
	OUTL(dp, THPDSH, 0);
I 27
	OUTL(dp, THPDSL, 0);
E 27
#endif
E 23
	/* Receive Descriptor Start Address register */
D 27
	OUTL(dp, RDSARL, (uint32_t)dp->rx_ring_dma);
	OUTL(dp, RDSARH, (uint32_t)(dp->rx_ring_dma >> 32));
	DPRINTF(4, (CE_CONT, "!%s: RDSAR 0x%llx",
E 27
I 27
	DPRINTF(2, (CE_CONT, "!%s: RDSAR 0x%llx",
E 27
D 29
	    dp->name, (unsigned long long)dp->rx_ring_dma));
E 29
I 29
	    dp->name, (uint64_t)dp->rx_ring_dma));
E 29
I 27
	OUTL(dp, RDSARH, (uint32_t)(dp->rx_ring_dma >> 32));
	OUTL(dp, RDSARL, (uint32_t)dp->rx_ring_dma);
E 27

	OUTL(dp, RCR, lp->rcr);
	OUTL(dp, TCR, lp->tcr);
I 27
	DPRINTF(0, (CE_CONT, "!%s: %s: rcr:%b, tcr:%x",
	    dp->name, __func__,
	    INL(dp, RCR), RCR_BITS, INL(dp, TCR)));
E 27

E 22
D 16
	/* Interrupt status register */
E 16
I 16
	/* Interrupt status register: clear bogus interrupts */
E 16
D 28
	OUTW(dp, ISR, 0xffff);
E 28
I 28
	OUTW(dp, ISR, 0xffffU);
E 28
I 22
	FLSHW(dp, ISR);
E 22

I 22
	devcsr = pci_config_get32(conf_ha, lp->pcie_cap + 8);
I 29
	DPRINTF(0, (CE_CONT, "!%s: %s: devcsr:0x%x",
	    dp->name, __func__, devcsr));
E 29
D 23
	if ((devcsr & (7 << 12)) < (3 << 12)) {
		devcsr = (devcsr & ~(7 << 12)) | (3 << 12);
E 23
I 23
D 24
	if (((devcsr >> 12) & 7) < gani_pcie_req_max) {
		devcsr = (devcsr & ~(7 << 12)) | (gani_pcie_req_max << 12);
E 23
		pci_config_put32(conf_ha, lp->pcie_cap + 8, devcsr);
E 24
I 24
	devcsr &= ~(7 << 12);
D 28
	if (dp->mtu > ETHERMTU) {
		devcsr |= 2 << 12;
	} else {
E 28
I 28

	switch (lp->chip->type) {
	case R8168_11:
E 28
		devcsr |= gani_pcie_req_max << 12;
I 28
		break;
	default:
		if (dp->mtu > ETHERMTU) {
			devcsr |= 2 << 12;
		} else {
			devcsr |= gani_pcie_req_max << 12;
		}
		break;
E 28
E 24
	}
I 28

E 28
I 24
	switch (lp->chip->type) {
	case R8168_1:
	case R8168_2:
	case R8168_3:
		devcsr |= 0x800;
		break;
	}
	pci_config_put32(conf_ha, lp->pcie_cap + 8, devcsr);
E 24

	switch (lp->chip->type) {
D 23
	case R8168_CFG_METHOD_4:
E 23
I 23
	case R8168_4: /* RTL8168C */
I 28
		/* 012 */
E 28
E 23
		val = gani_csi_read(dp, 0x70c) & 0x00ffffff;
		gani_csi_write(dp, 0x70c, val | 0x27000000);

		OUTB(dp, DBGREG, 0xe0 | DBGREG_FIX_NAK_1 | DBGREG_FIX_NAK_2);

		gani_ephy_write(dp, 2,
		    (gani_ephy_read(dp, 2) & ~0x0800) | 0x1000);
		gani_ephy_write(dp, 3, gani_ephy_read(dp, 3) | 0x0002);
		gani_ephy_write(dp, 6, gani_ephy_read(dp, 6) & ~0x0080);

		OUTB(dp, CFG3, INB(dp, CFG3) & ~CFG3_BEACON_EN);

		pci_config_put8(conf_ha, 0x81, 0);

		val = cpcmd;
		val &= CpCR_NORMAL | CpCR_RxVLAN | CpCR_RxChkSum | 0x3;
		OUTW(dp, CpCR, val);

		OUTB(dp, ETThR, 0x3f);

		if (dp->mtu > ETHERMTU) {
			OUTB(dp, CFG3, INB(dp, CFG3) | CFG3_JUMBO);
			OUTB(dp, CFG4, INB(dp, CFG4) | CFG4_JUMBO);
			/* don't use cksum offload */
		} else {
			OUTB(dp, CFG3, INB(dp, CFG3) & ~CFG3_JUMBO);
			OUTB(dp, CFG4, INB(dp, CFG4) & ~CFG4_JUMBO);
		}
		break;

D 23
	case R8168_CFG_METHOD_5:
E 23
I 23
	case R8168_5: /* RTL8168C rev.B */
I 28
		/* 012 */
E 28
E 23
		val = gani_csi_read(dp, 0x70c) & 0x00ffffff;
		gani_csi_write(dp, 0x70c, val | 0x27000000);

		gani_ephy_write(dp, 1,
		    gani_ephy_read(dp, 1) | 0x0001);
		gani_ephy_write(dp, 3,
		    (gani_ephy_read(dp, 3) & ~0x0400) | 0x0220);

		OUTB(dp, CFG3, INB(dp, CFG3) & ~CFG3_BEACON_EN);

		/* disable clock request */
		pci_config_put8(conf_ha, 0x81, 0);

		val = cpcmd;
		val &= CpCR_NORMAL | CpCR_RxVLAN | CpCR_RxChkSum | 0x3;
		OUTW(dp, CpCR, val);

		OUTB(dp, ETThR, 0x3f);

		if (dp->mtu > ETHERMTU) {
			OUTB(dp, CFG3, INB(dp, CFG3) | CFG3_JUMBO);
			OUTB(dp, CFG4, INB(dp, CFG4) | CFG4_JUMBO);
		} else {
			OUTB(dp, CFG3, INB(dp, CFG3) & ~CFG3_JUMBO);
			OUTB(dp, CFG4, INB(dp, CFG4) & ~CFG4_JUMBO);
		}
		break;

D 23
	case R8168_CFG_METHOD_6: /* MAC_VER_8168C_D: */
E 23
I 23
	case R8168_6: /* RTL8168C rev.C */
I 28
		/* 013 */
E 28
E 23
		val = gani_csi_read(dp, 0x70c) & 0x00ffffff;
		gani_csi_write(dp, 0x70c, val | 0x27000000);

		OUTB(dp, CFG3, INB(dp, CFG3) & ~CFG3_BEACON_EN);

I 28
		/* disable clock request */
		pci_config_put8(conf_ha, 0x81, 0);

E 28
		val = cpcmd;
		val &= CpCR_NORMAL | CpCR_RxVLAN | CpCR_RxChkSum | 0x3;
		OUTW(dp, CpCR, val);

		OUTB(dp, ETThR, 0x3f);

		if (dp->mtu > ETHERMTU) {
			OUTB(dp, CFG3, INB(dp, CFG3) | CFG3_JUMBO);
			OUTB(dp, CFG4, INB(dp, CFG4) | CFG4_JUMBO);
		} else {
			OUTB(dp, CFG3, INB(dp, CFG3) & ~CFG3_JUMBO);
			OUTB(dp, CFG4, INB(dp, CFG4) & ~CFG4_JUMBO);
		}
		break;

D 23
	case R8168_CFG_METHOD_7: /* MAC_VER_8168CP */
E 23
I 23
	case R8168_7: /* RTL8168CP rev.B */
I 28
		/* 013 */
E 28
E 23
		val = gani_csi_read(dp, 0x70c) & 0x00ffffff;
		gani_csi_write(dp, 0x70c, val | 0x27000000);
I 28
#ifdef notyet
		gani_eri_write(dp, 0x1EC, 1, 0x07, ERIAR_ASF);
#endif
		/* disable clock request */
		pci_config_put8(conf_ha, 0x81, 0);
E 28

		val = cpcmd;
		val &= CpCR_NORMAL | CpCR_RxVLAN | CpCR_RxChkSum | 0x3;
		OUTW(dp, CpCR, val);

		OUTB(dp, CFG3, INB(dp, CFG3) & ~CFG3_BEACON_EN);

		OUTB(dp, ETThR, 0x3f);

		if (dp->mtu > ETHERMTU) {
			OUTB(dp, CFG3, INB(dp, CFG3) | CFG3_JUMBO);
			OUTB(dp, CFG4, INB(dp, CFG4) | CFG4_JUMBO);
		} else {
			OUTB(dp, CFG3, INB(dp, CFG3) & ~CFG3_JUMBO);
			OUTB(dp, CFG4, INB(dp, CFG4) & ~CFG4_JUMBO);
		}
		break;

D 23
	case R8168_CFG_METHOD_8:
E 23
I 23
	case R8168_8: /* RTL8168 rev.C */
I 28
		/* 013 */
E 28
E 23
		val = gani_csi_read(dp, 0x70c) & 0x00ffffff;
		gani_csi_write(dp, 0x70c, val | 0x27000000);
I 28
#ifdef notyet
		gani_eri_write(dp, 0x1EC, 1, 0x07, ERIAR_ASF);
#endif
		/* disable clock request */
		pci_config_put8(conf_ha, 0x81, 0);
E 28

		val = cpcmd;
		val &= CpCR_NORMAL | CpCR_RxVLAN | CpCR_RxChkSum | 0x3;
		OUTW(dp, CpCR, val);

		OUTB(dp, CFG3, INB(dp, CFG3) & ~CFG3_BEACON_EN);
D 28
		OUTB(dp, 0xd1, 0x20);
E 28
I 28
		OUTB(dp, 0xD1, 0x20);
E 28

		OUTB(dp, ETThR, 0x3f);

		if (dp->mtu > ETHERMTU) {
			OUTB(dp, CFG3, INB(dp, CFG3) | CFG3_JUMBO);
			OUTB(dp, CFG4, INB(dp, CFG4) | CFG4_JUMBO);
		} else {
			OUTB(dp, CFG3, INB(dp, CFG3) & ~CFG3_JUMBO);
			OUTB(dp, CFG4, INB(dp, CFG4) & ~CFG4_JUMBO);
		}
		break;

D 23
	case R8168_CFG_METHOD_9:
E 23
I 23
	case R8168_9: /* RTL8168D */
I 28
		/* 016 */
E 28
E 23
		val = gani_csi_read(dp, 0x70c) & 0x00ffffff;
D 28
		gani_csi_write(dp, 0x70c, val | 0x27000000);
E 28
I 28
		gani_csi_write(dp, 0x70c, val | 0x13000000);
E 28

I 28
		/* disable clock request */
E 28
		pci_config_put8(conf_ha, 0x81, 0);

I 24
D 28
		OUTB(dp, CFG1, 0xCF);
		OUTB(dp, CFG2, 0x9C);
		OUTB(dp, CFG3, 0x62);
E 28
I 28
		OUTB(dp, CFG3, INB(dp, CFG3) & ~0x10);
		OUTB(dp, DBGREG, INB(dp, DBGREG) | 0x82);
E 28

E 24
		OUTB(dp, ETThR, 0x3f);

		if (dp->mtu > ETHERMTU) {
			OUTB(dp, CFG3, INB(dp, CFG3) | CFG3_JUMBO);
			OUTB(dp, CFG4, INB(dp, CFG4) | CFG4_JUMBO);
		} else {
			OUTB(dp, CFG3, INB(dp, CFG3) & ~CFG3_JUMBO);
			OUTB(dp, CFG4, INB(dp, CFG4) & ~CFG4_JUMBO);
		}
		gani_ephy_write(dp, 0x01, 0x7c7d);
		gani_ephy_write(dp, 0x02, 0x091f);
		gani_ephy_write(dp, 0x06, 0xb271);
		gani_ephy_write(dp, 0x07, 0xce00);
		break;

D 23
	case R8168_CFG_METHOD_10:
E 23
I 23
D 28
	case R8168_10: /* RTL8168D rev.B */
E 28
I 28
	case R8168_10: /* RTL8168D rev.C */
		/* 016 */
E 28
E 23
		val = gani_csi_read(dp, 0x70c) & 0x00ffffff;
D 28
		gani_csi_write(dp, 0x70c, val | 0x27000000);
E 28
I 28
		gani_csi_write(dp, 0x70c, val | 0x13000000);
E 28

I 28
		OUTB(dp, DBGREG, INB(dp, DBGREG) | 0x82);

E 28
		OUTB(dp, ETThR, 0x3f);

		if (dp->mtu > ETHERMTU) {
			OUTB(dp, CFG3, INB(dp, CFG3) | CFG3_JUMBO);
			OUTB(dp, CFG4, INB(dp, CFG4) | CFG4_JUMBO);
		} else {
			OUTB(dp, CFG3, INB(dp, CFG3) & ~CFG3_JUMBO);
			OUTB(dp, CFG4, INB(dp, CFG4) & ~CFG4_JUMBO);
		}
D 28
		OUTB(dp, CFG1, 0xdf);
E 28
I 28
		OUTB(dp, CFG1, (INB(dp, CFG1) & 0xc0) | 0x1F);
E 28

D 28
		gani_ephy_write(dp, 0x01, 0x7c7d);
		gani_ephy_write(dp, 0x02, 0x091f);
		gani_ephy_write(dp, 0x03, 0xc5ba);
		gani_ephy_write(dp, 0x06, 0xb279);
		gani_ephy_write(dp, 0x07, 0xAf00);
		gani_ephy_write(dp, 0x1e, 0xb8eb);
E 28
I 28
		gani_ephy_write(dp, 0x01, 0x6C7F);
		gani_ephy_write(dp, 0x02, 0x011F);
		gani_ephy_write(dp, 0x03, 0xC1B2);
		gani_ephy_write(dp, 0x1A, 0x0546);
		gani_ephy_write(dp, 0x1C, 0x80C4);
		gani_ephy_write(dp, 0x1D, 0x78E4);
		gani_ephy_write(dp, 0x0A, 0x8100);
E 28

		/* disable clock request */
		pci_config_put8(conf_ha, 0x81, 0);
I 28

		OUTB(dp, 0xf3, INB(dp, 0xf3) | 0x04);
E 28
		break;

I 24
D 28
	case R8168_11: /* RTL8168D rev.C */
E 28
I 28
	case R8168_11: /* RTL8168DP */
		/* 016 */
E 28
		val = gani_csi_read(dp, 0x70c) & 0x00ffffff;
D 28
		gani_csi_write(dp, 0x70c, val | 0x27000000);
E 28
I 28
		gani_csi_write(dp, 0x70c, val | 0x17000000);
E 28

		OUTB(dp, ETThR, 0x3f);

		if (dp->mtu > ETHERMTU) {
			OUTB(dp, CFG3, INB(dp, CFG3) | CFG3_JUMBO);
D 28
			OUTB(dp, CFG4, INB(dp, CFG4) | CFG4_JUMBO);
E 28
		} else {
			OUTB(dp, CFG3, INB(dp, CFG3) & ~CFG3_JUMBO);
D 28
			OUTB(dp, CFG4, INB(dp, CFG4) & ~CFG4_JUMBO);
E 28
		}
D 28
		OUTB(dp, CFG1, 0xdf);

		gani_ephy_write(dp, 0x01, 0x6C7F);
		gani_ephy_write(dp, 0x02, 0x011F);
		gani_ephy_write(dp, 0x03, 0xC1B2);
		gani_ephy_write(dp, 0x06, 0x0546);
		gani_ephy_write(dp, 0x07, 0x80C4);
		gani_ephy_write(dp, 0x1e, 0x78E4);

E 28
		/* disable clock request */
		pci_config_put8(conf_ha, 0x81, 0);

D 28
		OUTB(dp, 0xf3, INB(dp, 0xf3) | 0x04);
E 28
I 28
		OUTB(dp, CFG1, (INB(dp, CFG1) & 0xc0) | 0x1F);
E 28
		break;

I 28
	case R8168_12: /* RTL8168DP */
		/* 016 */
		val = gani_csi_read(dp, 0x70c) & 0x00ffffff;
		gani_csi_write(dp, 0x70c, val | 0x17000000);

		OUTB(dp, ETThR, 0x3f);

		if (dp->mtu > ETHERMTU) {
			OUTB(dp, CFG3, INB(dp, CFG3) | CFG3_JUMBO);
		} else {
			OUTB(dp, CFG3, INB(dp, CFG3) & ~CFG3_JUMBO);
		}
#ifdef notyet
		val = gani_ephy_read(dp, 0x0B);
		gani_ephy_write(dp, 0x03, val | 0x48);

		val = gani_ephy_read(dp, 0x19) & 0x20;
		gani_ephy_write(dp, 0x03, val | 0x50);

		val = gani_ephy_read(dp, 0x0C);
		gani_ephy_write(dp, 0x03, val | 0x20);
#endif
		pci_config_put8(conf_ha, 0x81, 1);

		OUTB(dp, CFG1, (INB(dp, CFG1) & 0xc0) | 0x1F);
		break;

E 28
E 24
D 23
	case R8168_CFG_METHOD_1:
E 23
I 23
	case R8168_1: /* RTL8168B rev.B */
I 28
		/* 012 */
E 28
E 23
		OUTB(dp, CFG3, INB(dp, CFG3) & ~CFG3_BEACON_EN);

		val = cpcmd;
		val &= CpCR_NORMAL | CpCR_RxVLAN | CpCR_RxChkSum | 0x3;
		OUTW(dp, CpCR, val);
		break;

D 23
	case R8168_CFG_METHOD_2:
E 23
I 23
	case R8168_2: /* RTL8168B rev.E */
I 28
		/* 012 */
E 28
E 23
		OUTB(dp, CFG3, INB(dp, CFG3) & ~CFG3_BEACON_EN);

		val = cpcmd;
		val &= CpCR_NORMAL | CpCR_RxVLAN | CpCR_RxChkSum | 0x3;
		OUTW(dp, CpCR, val);

		OUTB(dp, ETThR, 0x3f);

		if (dp->mtu > ETHERMTU) {
			OUTB(dp, CFG4, INB(dp, CFG4) | CFG4_JUMBO);
		} else {
			OUTB(dp, CFG4, INB(dp, CFG4) & ~CFG4_JUMBO);
		}
		break;

D 23
	case R8168_CFG_METHOD_3:
E 23
I 23
	case R8168_3: /* RTL8168B rev.F */
I 28
		/* 012 */
E 28
E 23
		OUTB(dp, CFG3, INB(dp, CFG3) & ~CFG3_BEACON_EN);

		val = cpcmd;
		val &= CpCR_NORMAL | CpCR_RxVLAN | CpCR_RxChkSum | 0x3;
		OUTW(dp, CpCR, val);

		OUTB(dp, ETThR, 0x3f);

		if (dp->mtu > ETHERMTU) {
			OUTB(dp, CFG4, INB(dp, CFG4) | CFG4_JUMBO);
		} else {
			OUTB(dp, CFG4, INB(dp, CFG4) & ~CFG4_JUMBO);
		}
		break;
	}

	OUTB(dp, CR, CR_RE | CR_TE);

	/* make config registers read only */
	OUTB(dp, CR9346, CR9346_EEM_NORMAL);
	drv_usecwait(10);

E 22
	/* TimerInt Register */
	OUTL(dp, TimerInt, 0);

	/* Timer count register: test count rate */
	OUTL(dp, TCTR, 0);
#if DEBUG_LEVEL > 3
	drv_usecwait(1000);
	cmn_err(CE_CONT, "!%s: TCTR:%d in 1mS", dp->name, INL(dp, TCTR));
#endif
I 13
D 16
	/*
	 * Receive control register: don't touch here
	 *
	 * XXX - Keep undocumented bits.
	 * This also implies to disable receiving packets.
	 */
	lp->rcr = INL(dp, RCR) & ~RCR_MASK;
E 13

	lp->tx_list_len = 0;
I 13

E 16
D 23
#ifdef DEBUG_HANG
	gani_dump_regs(dp, "init_chip done");
#endif
I 16
D 22
#ifdef GEM_CONFIG_POLLING
	lp->last_poll_interval = 0; /* polling interval in uS */
E 22
I 22
#ifdef CONFIG_POLLING
	lp->last_poll_interval = 0; /* polling interval in nS */
E 22
#endif
#ifdef CONFIG_OPT_TPPOLL
D 22
	lp->tx_running   = B_FALSE;
E 22
I 22
	lp->tx_running = B_FALSE;
E 22
#endif
I 22
#if defined(CONFIG_OPT_TPPOLL) || defined(WA_NO_TPPOLL_WRAP)
E 22
	lp->tx_activated = 0;
D 22
	lp->tx_finished  = 0;
E 22
I 22
	lp->tx_finished = 0;
#endif
E 22
I 18
#ifdef WA_NO_TPPOLL_WRAP
E 18
D 22
	lp->tx_no_more   = B_FALSE;
D 18
#ifdef SANITY
E 18
	lp->tx_pended    = 0;
E 22
I 22
	lp->tx_no_more = B_FALSE;
	lp->tx_pended = 0;
E 22
#endif
I 22
	lp->last_stats_valid = B_FALSE;

	pci_config_teardown(&conf_ha);

E 23
E 22
I 17
D 18

E 18
	return (GEM_SUCCESS);
E 17
E 16
E 13
}

I 22
static int
D 23
gani_init_chip_8101(struct gem_dev *dp)
E 23
I 23
gani_init_8101(struct gem_dev *dp, ddi_acc_handle_t conf_ha)
E 23
{
	uint32_t		val;
	uint32_t		cpcmd;
D 23
	ddi_acc_handle_t	conf_ha;
E 23
	struct gani_dev		*lp = dp->private;

	DPRINTF(0, (CE_CONT, "!%s: %s: called", dp->name, __func__));

D 23
	if (pci_config_setup(dp->dip, &conf_ha) != DDI_SUCCESS) {
		cmn_err(CE_WARN, "!%s: pci_config_setup failed", dp->name);
		return (GEM_FAILURE);
	}

	/* XXX - disable interrupts */
	OUTW(dp, IMR, 0);
	FLSHW(dp, IMR);

	OUTW(dp, RMS,
	    dp->mtu > ETHERMTU ? dp->mtu + 14 + 8 : 1519 /* 0x5ef */);

E 23
I 23
D 31
	OUTW(dp, RMS, dp->mtu + sizeof (struct ether_header) + 8 + 1);
E 31
I 31
	OUTW(dp, RMS, RMS_PCIE(dp->mtu));
E 31
E 23
	DPRINTF(2, (CE_CONT, "!%s: RMS %d", dp->name, INW(dp, RMS)));

	/* configure CPlus command register */
	cpcmd = INW(dp, CpCR);
I 27
	cpcmd &= ~(CpCR_RxVLAN | CpCR_RxChkSum);
E 27
D 23
#ifdef CONFIG_DAC
	cpcmd |= CpCR_DAC;
#endif
E 23
#ifdef GEM_CONFIG_VLAN_HW
	cpcmd &= ~CpCR_RxVLAN;
#ifdef GEM_CONFIG_CKSUM_OFFLOAD
	cpcmd |= CpCR_RxChkSum;
#endif /* GEM_CONFIG_CKSUM_OFFLOAD */
#endif /* GEM_CONFIG_VLAN_HW */
	OUTW(dp, CpCR, cpcmd);

	switch (lp->chip->type) {
D 23
	case R8101_CFG_METHOD_4:
E 23
I 23
	case R8101_4: /* RTL8102E */
E 23
		/* set PCI configuration space offset 0x70F to 0x17 */
		val = gani_csi_read(dp, 0x70c) & 0x00ffffff;
		gani_csi_write(dp, 0x70c, val | 0x17000000);

I 28
		/* XXX config2/4 upon link_control */

E 28
		OUTB(dp, CFG1, 0x0f);
		OUTB(dp, CFG3, INB(dp, CFG3) & ~CFG3_BEACON_EN);

		val = cpcmd;
		val &= CpCR_NORMAL | CpCR_RxVLAN | CpCR_RxChkSum | 0x7;
		OUTW(dp, CpCR, val);
		gani_ephy_write(dp, 0x03, 0xc2f9);
		break;

D 23
	case R8101_CFG_METHOD_5:
E 23
I 23
	case R8101_5: /* RTL8102E rev.B */
I 28
#ifdef gone
E 28
E 23
		/* set PCI configuration space offset 0x70F to 0x17 */
		val = gani_csi_read(dp, 0x70c) & 0x00ffffff;
		gani_csi_write(dp, 0x70c, val | 0x17000000);
I 28
#endif
		/* XXX config2/4 upon link_control */
E 28

		OUTB(dp, CFG1, 0x0f);
		OUTB(dp, CFG3, INB(dp, CFG3) & ~CFG3_BEACON_EN);

		val = cpcmd;
		val &= CpCR_NORMAL | CpCR_RxVLAN | CpCR_RxChkSum | 0x7;
		OUTW(dp, CpCR, val);
I 28
		gani_ephy_write(dp, 0x01, 0x6FE5);
		gani_ephy_write(dp, 0x03, 0xD7D9);
E 28
		break;

D 23
	case R8101_CFG_METHOD_6:
E 23
I 23
	case R8101_6: /* RTL8103E */
I 28
#ifdef gone
E 28
E 23
		/* set PCI configuration space offset 0x70F to 0x17 */
		val = gani_csi_read(dp, 0x70c) & 0x00ffffff;
		gani_csi_write(dp, 0x70c, val | 0x17000000);

D 28
		OUTB(dp, DBGREG, 0x18);
E 28
I 28
		OUTB(dp, DBGREG, 0x10);
#endif
		/* XXX config2/4 upon link_control */
E 28

		OUTB(dp, CFG1, 0xdf);
		OUTB(dp, 0xf4, 0x01);

		val = cpcmd;
		val &= CpCR_NORMAL | CpCR_RxVLAN | CpCR_RxChkSum | 0x7;
		OUTW(dp, CpCR, val);

		OUTB(dp, CFG3, INB(dp, CFG3) & ~CFG3_BEACON_EN);

		gani_ephy_write(dp, 0x06, 0xaf35);
		break;
I 28

	case R8101_7: /* RTL8103E */
	case R8101_8: /* RTL8103E */
#ifdef gone
		/* set PCI configuration space offset 0x70F to 0x17 */
		val = gani_csi_read(dp, 0x70c) & 0x00ffffff;
		gani_csi_write(dp, 0x70c, val | 0x17000000);

		OUTB(dp, DBGREG, 0x10);
#endif
		OUTB(dp, CFG1, (INB(dp, CFG1) & 0xc0) | 0x1f);
		OUTB(dp, 0xf4, 0x01);

		val = cpcmd;
		val &= CpCR_NORMAL | CpCR_RxVLAN | CpCR_RxChkSum | 0x7;
		OUTW(dp, CpCR, val);

		OUTB(dp, CFG3, INB(dp, CFG3) & ~CFG3_BEACON_EN);

		OUTB(dp, 0xf5, INB(dp, 0xf5) | 0x04);
		gani_ephy_write(dp, 0x19, 0xec90);
		gani_ephy_write(dp, 0x01, 0x6fe5);
		gani_ephy_write(dp, 0x03, 0x05d9);
		gani_ephy_write(dp, 0x06, 0xaf35);
		break;

	case R8101_9: /* RTL8401 */
#ifdef gone
		/* set PCI configuration space offset 0x70F to 0x17 */
		val = gani_csi_read(dp, 0x70c) & 0x00ffffff;
		gani_csi_write(dp, 0x70c, val | 0x17000000);

		OUTB(dp, DBGREG, 0x18);
#endif
		OUTB(dp, CFG1, 0xdf);
		OUTB(dp, 0xf4, 0x01);

		val = cpcmd;
		val &= CpCR_NORMAL | CpCR_RxVLAN | CpCR_RxChkSum | 0x7;
		OUTW(dp, CpCR, val);

		OUTB(dp, CFG3, INB(dp, CFG3) & ~CFG3_BEACON_EN);

		gani_ephy_write(dp, 0x06, 0xaf25);
		gani_ephy_write(dp, 0x07, 0x8e68);
		break;

#ifdef CONFIG_RTL8105
	case R8101_10:
		/* set PCI configuration space offset 0x70F to 0x17 */
		val = gani_csi_read(dp, 0x70c) & 0x00ffffff;
		gani_csi_write(dp, 0x70c, val | 0x27000000);

		OUTB(dp, ETThR, 0x0c);

		val = cpcmd;
		val &= CpCR_NORMAL | CpCR_RxVLAN | CpCR_RxChkSum | 0x3;
		OUTW(dp, CpCR, val);

		OUTB(dp, 0xf3, INB(dp, 0xf3) | 0x20);
		OUTB(dp, 0xf3, INB(dp, 0xf3) & ~0x20);

		OUTB(dp, CFG5, (INB(dp, CFG5) & ~0x08) | 0x01);
		OUTB(dp, CFG2, INB(dp, CFG2) | 0x80);
		OUTB(dp, CFG3, INB(dp, CFG3) & ~CFG3_BEACON_EN);
		break;

	case R8101_11:
		val = cpcmd;
		val &= CpCR_NORMAL | CpCR_RxVLAN | CpCR_RxChkSum | 0x3;
		OUTW(dp, CpCR, val);

		OUTB(dp, 0xf2, INB(dp, 0xf2) & ~0x01);
		OUTB(dp, 0xd0, INB(dp, 0xd0) | 0x40);
		OUTW(dp, 0xe0, INW(dp, 0xe0) & ~0xdf9c);
		break;
#endif
E 28
	}

	/* make configuration registers writable */
	OUTB(dp, CR9346, CR9346_EEM_WE);

	/* reserved */
	OUTB(dp, ETThR /* 0xec */, 0x3f);

	OUTW(dp, CpCR, cpcmd);

	/* XXX - undocumented */
	OUTW(dp, 0xe2, 0);	/* intermitigate */

	/* Transmit Normal Priority Descriptors */
	DPRINTF(4, (CE_CONT, "!%s: TNPDS 0x%llx",
	    dp->name, (unsigned long long)dp->tx_ring_dma));
	OUTL(dp, TNPDSL, (uint32_t)dp->tx_ring_dma);
	OUTL(dp, TNPDSH, (uint32_t)(dp->tx_ring_dma >> 32U));

	/* Receive Descriptor Start Address register */
	OUTL(dp, RDSARL, (uint32_t)dp->rx_ring_dma);
	OUTL(dp, RDSARH, (uint32_t)(dp->rx_ring_dma >> 32U));
	DPRINTF(4, (CE_CONT, "!%s: RDSAR 0x%llx",
	    dp->name, (unsigned long long)dp->rx_ring_dma));

D 28

E 28
	/* need to enable tx and rx before writing rcr and tcr */
	OUTB(dp, CR, CR_RE | CR_TE);

	OUTL(dp, RCR, lp->rcr);
	OUTL(dp, TCR, lp->tcr);

I 23
	/* make config registers read only */
	OUTB(dp, CR9346, CR9346_EEM_NORMAL);
	drv_usecwait(10);

E 23
	/* TimerInt Register */
	OUTL(dp, TimerInt, 0);

	/* Timer count register: test count rate */
	OUTL(dp, TCTR, 0);
#if DEBUG_LEVEL > 3
	drv_usecwait(1000);
	cmn_err(CE_CONT, "!%s: TCTR:%d in 1mS", dp->name, INL(dp, TCTR));
#endif
D 23
	/* make config registers read only */
	OUTB(dp, CR9346, CR9346_EEM_NORMAL);
	drv_usecwait(10);
E 23
I 23
	return (GEM_SUCCESS);
}
E 23

I 23
static int
gani_init_chip(struct gem_dev *dp)
{
	int	ret;
	ddi_acc_handle_t	conf_ha;
	struct gani_dev	*lp = dp->private;

	DPRINTF(0, (CE_CONT, "!%s: %s: called", dp->name, __func__));

	if (pci_config_setup(dp->dip, &conf_ha) != DDI_SUCCESS) {
		cmn_err(CE_WARN, "!%s: pci_config_setup failed", dp->name);
		return (GEM_FAILURE);
	}

D 28
	if (GANI_PCI(lp->chip->type)) {
E 28
I 28
	if (GANI_PCI(lp)) {
E 28
		ret = gani_init_8169(dp, conf_ha);
D 28
	} else if (GANI_PCIE_GIGA(lp->chip->type)) {
E 28
I 28
	} else if (GANI_PCIE_GIGA(lp)) {
E 28
		ret = gani_init_8168(dp, conf_ha);
	} else {
		ret = gani_init_8101(dp, conf_ha);
	}
	pci_config_teardown(&conf_ha);

E 23
#ifdef DEBUG_HANG
	gani_dump_regs(dp, "init_chip done");
#endif
#ifdef CONFIG_POLLING
	lp->last_poll_interval = 0; /* polling interval in nS */
#endif
D 28
#ifdef CONFIG_OPT_TPPOLL
	lp->tx_running = B_FALSE;
#endif
E 28
D 23
#if defined(CONFIG_OPT_TPPOLL) || defined(WA_NO_TPPOLL_WRAP)
	lp->tx_activated = 0;
	lp->tx_finished = 0;
#endif
#ifdef WA_NO_TPPOLL_WRAP
	lp->tx_no_more = B_FALSE;
	lp->tx_pended = 0;
#endif
E 23
	lp->last_stats_valid = B_FALSE;

D 23
	pci_config_teardown(&conf_ha);

	return (GEM_SUCCESS);
E 23
I 23
	return (ret);
E 23
}

E 22
I 13
static uint_t
gani_mcast_hash(struct gem_dev *dp, uint8_t *addr)
{
D 16
	return gem_ether_crc_be(addr);
E 16
I 16
D 17
	return gem_ether_crc_be(addr, ETHERADDRL);
E 17
I 17
D 22
	return (gem_ether_crc_be(addr, ETHERADDRL));
E 22
I 22
D 28
	return (gem_ether_crc_be(addr, ETHERADDRL) >> (32 - 6));
E 28
I 28
	uint_t	h;
	struct gani_dev	*lp = dp->private;

	h = gem_ether_crc_be(addr, ETHERADDRL) >> (32 - 6);

D 29
	return (GANI_PCIE(lp) ? (h ^ 0x3f) : h);
E 29
I 29
	return (GANI_PCIE(lp) ? (h ^ 0x38) : h);
E 29
E 28
E 22
E 17
E 16
}

E 13
D 17
static void
E 17
I 17
static int
E 17
I 13
gani_set_rx_filter(struct gem_dev *dp)
{
	uint32_t	mode;
D 22
	uint32_t	mhash[2];
E 22
I 22
	uint64_t	mhash;
E 22
	int		i;
	uint8_t		*m;
I 14
D 23
	uint8_t		reg;
E 23
E 14
D 22
	struct gani_dev	*lp = (struct gani_dev *)dp->private;
E 22
I 22
	struct gani_dev	*lp = dp->private;
E 22

D 14
	DPRINTF(2, (CE_CONT, "!%s: gani_set_rx_mode: called", dp->name));
E 14
I 14
D 16
	DPRINTF(1, (CE_CONT, "!%s: gani_set_rx_mode: called", dp->name));
E 16
I 16
	DPRINTF(1, (CE_CONT, "!%s: %s: called", dp->name, __func__));
E 16
E 14

	mode = RCR_AB	/* accept broadcast */
D 22
	     | RCR_APM 	/* accept physical match  */
E 22
I 22
D 28
	    | RCR_APM; 	/* accept physical match  */
E 28
I 28
	    | RCR_APM	/* accept physical match  */
	    | RCR_AM;	/* accept multicast */
E 28
E 22
D 17
	     | RCR_AER | RCR_AR | RCR_RER8; /* accept error and runt packets */
E 17
I 17
D 23
#ifdef notdef
D 22
	     | RCR_AER | RCR_AR | RCR_RER8 /* accept error and runt packets */
E 22
I 22
	mode |= RCR_AER | RCR_AR | RCR_RER8; /* accept error and runt packets */
E 22
#endif
E 23
D 22
	     ;
E 22
E 17

D 16
	mhash[0] = 0;
	mhash[1] = 0;
E 16
I 16
D 22
	mhash[0] = mhash[1] = 0;
E 22
I 22
	mhash = 0;
E 22
E 16

D 16
	if ((dp->rxmode & RXMODE_PROMISC) != 0) {
E 16
I 16
	if ((dp->rxmode & RXMODE_ENABLE) == 0) {
		mode = 0;
D 22
	} else if ((dp->rxmode & RXMODE_PROMISC) != 0) {
E 22
I 22

	} else if (dp->rxmode & RXMODE_PROMISC) {
E 22
E 16
		/* promiscious mode implies all multicast and all physical */
D 28
		mode |= RCR_AM | RCR_AAP;
E 28
I 28
		mode |= RCR_AAP;
E 28
D 16
		mhash[0] = 0xffffffff;
		mhash[1] = 0xffffffff;
E 16
I 16
D 22
		mhash[0] = mhash[1] = 0xffffffff;
E 16
	}	
D 16
	else if ((dp->rxmode & RXMODE_ALLMULTI) != 0 || dp->mc_count > 32) {
E 16
I 16
	else if ((dp->rxmode & RXMODE_ALLMULTI) != 0 || dp->mc_count > 32 ||
		  GANI_PCIE(lp->chip->type)) {
E 22
I 22
		mhash = ~0ULL;

	} else if ((dp->rxmode & RXMODE_ALLMULTI) || dp->mc_count > 32) {
E 22
E 16
		/* accept all multicast packets */
D 28
		mode |= RCR_AM;
E 28
D 16
		mhash[0] = 0xffffffff;
		mhash[1] = 0xffffffff;
E 16
I 16
D 22
		mhash[0] = mhash[1] = 0xffffffff;
E 16
	}
	else if (dp->mc_count > 0) {
E 22
I 22
		mhash = ~0ULL;

	} else if (dp->mc_count > 0) {
E 22
D 28
		mode |= RCR_AM;
E 28
		/*
D 23
		 * make hash table to select interresting
E 23
I 23
		 * make the hash table to select the interresting
E 23
		 * multicast address only.
		 */
		for (i = 0; i < dp->mc_count; i++) {
D 22
			uint_t	h;
E 22
			/* hash table is 64 = 2^6 bit width */
D 22
			h = dp->mc_list[i].hash >> (32 - 6);
			mhash[h / 32] |= 1 << (h % 32);
E 22
I 22
			mhash |= 1ULL << dp->mc_list[i].hash;
E 22
		}
I 23
D 28
		if (GANI_PCIE(lp->chip->type)) {
			mhash = BSWAP_64(mhash);
		}
E 28
E 23
D 16
	}	
E 16
I 16
	}
E 16

I 16
D 23
#ifdef notdef
E 16
	lp->rcr &= ~(RCR_ACCEPT_MODE | RCR_RER8);
D 16
	if (dp->nic_active) {
E 16
I 16

	if (dp->mac_active) {
E 16
		/*
		 * disable all kind of rx filters to stop rx before
		 * changing mac address and/or multicast hash table.
		 */
		OUTL(dp, RCR, lp->rcr);
		FLSHL(dp, RCR);
	}
D 16

E 16
I 16
#endif
E 23
I 23
	/*
	 * Don't disable the rx filter not to drop packets
	 * while we are changing rx filer mode.
	 */
I 28

E 28
E 23
E 16
	m = &dp->cur_addr.ether_addr_octet[0];
D 22
	if (bcmp(m, lp->mac, ETHERADDRL) != 0) {
E 22
I 22
	if (bcmp(m, lp->mac, ETHERADDRL)) {
E 22
I 14
		/*
D 27
		 * XXX - make config registers writable before
E 27
I 27
		 * make config registers writable before
E 27
		 * changing IDRs. (undocumented)
		 */
D 23
		reg = INB(dp, CR9346);
E 23
		OUTB(dp, CR9346, CR9346_EEM_WE);

E 14
D 22
		/* set mac address */	
E 22
I 22
		/* set mac address */
E 22
		OUTL(dp, IDR + 0,
D 22
			(m[3] << 24) | (m[2] << 16) | (m[1] << 8) | m[0]);
E 22
I 22
		    (m[3] << 24) | (m[2] << 16) | (m[1] << 8) | m[0]);
D 23
#if 0
E 22
I 16
D 21
		if (lp->chip->type == MAC_VER_8169SC /* M5 */) {
E 21
I 21
		if (lp->chip->type == MAC_VER_8110SC /* M5 */) {
E 21
			drv_usecwait(1000);
		}
I 22
#endif
E 23
E 22
E 16
		OUTL(dp, IDR + 4, (m[5] <<  8) | m[4]);
D 14
		bcopy(m, lp->mac, ETHERADDRL);
E 14
I 14

D 23
		OUTB(dp, CR9346, reg);
E 23
I 23
		OUTB(dp, CR9346, CR9346_EEM_NORMAL);
E 23
		drv_usecwait(10);
E 14
	}

D 22
	if ((mode & RCR_AM) != 0) {
E 22
I 22
	if (mode & RCR_AM) {
E 22
		/* need to set up multicast hash table */
D 16
		OUTL(dp, MAR + 0, mhash[0]);
E 16
D 22
		OUTL(dp, MAR + 4, mhash[1]);
I 16
		OUTL(dp, MAR + 0, mhash[0]);
E 22
I 22
D 28
		OUTL(dp, MAR + 4, mhash >> 32U);
		OUTL(dp, MAR + 0, mhash);
E 28
I 28
		OUTL(dp, MAR + 4, (uint32_t)(mhash >> 32U));
		OUTL(dp, MAR + 0, (uint32_t)mhash);
E 28
E 22
E 16
	}

	/* update rcr */
D 16
	lp->rcr |= mode;
	if (dp->nic_active) {
		OUTL(dp, RCR, lp->rcr);
	}
E 16
I 16
	OUTL(dp, RCR, lp->rcr | mode);
E 16

D 14
	DPRINTF(2, (CE_CONT, "!gani_set_rx_filter: returned"));
E 14
I 14
D 16
	DPRINTF(4, (CE_CONT, "!gani_set_rx_filter: returned"));
E 16
I 16
	DPRINTF(4, (CE_CONT, "!%s: returned", __func__));
E 16
E 14
#ifdef DEBUG_HANG
	gani_dump_regs(dp, "set_rxfilter done");
#endif
I 17

	return (GEM_SUCCESS);
E 17
}

I 16

#define	MII_ABILITY_SPEED_DUPLEX	\
	(MII_ABILITY_100BASE_T4	|	\
D 22
	 MII_ABILITY_100BASE_TX_FD |	\
	 MII_ABILITY_100BASE_TX |	\
	 MII_ABILITY_10BASE_T |	\
	 MII_ABILITY_10BASE_T_FD)
E 22
I 22
	MII_ABILITY_100BASE_TX_FD |	\
	MII_ABILITY_100BASE_TX |	\
	MII_ABILITY_10BASE_T |	\
	MII_ABILITY_10BASE_T_FD)
E 22

E 16
D 17
static void
E 17
I 17
static int
E 17
gani_set_media(struct gem_dev *dp)
{
I 24
	struct gani_dev	*lp = dp->private;
D 28

E 28
I 28
#ifdef GEM3
	DPRINTF(0, (CE_CONT, "!%s: %s: phys: %b, mac_state: %d",
	    dp->name, __func__, INB(dp, PHYS), PHYS_BITS, dp->mac_state));
#else
E 28
E 24
I 19
D 22
	uint16_t	val;
E 19
	struct gani_dev	*lp = (struct gani_dev *)(dp)->private;
E 22
I 22
D 23
	struct gani_dev	*lp = dp->private;
E 22

E 23
D 16
	DPRINTF(4, (CE_CONT,
		"!gani_set_media: phys: %b, nic_active: %d",
		INB(dp, PHYS), PHYS_BITS, dp->nic_active));
E 16
I 16
	DPRINTF(0, (CE_CONT, "!%s: %s: phys: %b, mac_active: %d",
D 22
		dp->name, __func__, INB(dp, PHYS), PHYS_BITS, dp->mac_active));
E 22
I 22
	    dp->name, __func__, INB(dp, PHYS), PHYS_BITS, dp->mac_active));
E 22
E 16
D 28

E 28
I 28
#endif
E 28
D 16
	/* do nothing */
E 16
I 16
D 22
	lp->stats_valid = B_FALSE;
E 22
I 22
D 23
	/* do nothing */
E 23
I 23
D 24
	/* EMPTY */
E 24
I 24
	switch (lp->chip->type) {
I 28
	/* 011 */
	case R8169_5:
	case R8169_6:
		if (dp->full_duplex) {
			lp->tcr = (lp->tcr & ~TCR_IFG) | TCR_IFG_802_3;
		} else {
			lp->tcr = (lp->tcr & ~TCR_IFG) | TCR_IFG_HALF_8169;
		}
		OUTL(dp, TCR, lp->tcr);
		break;

E 28
	case R8101_4:
	case R8101_5:
D 28
        	if (gani_csi_read(dp, 0x70c) != 0x27000000) {
                        gani_csi_write(dp, 0x70c, 0x27000000);
E 28
I 28
		if (gani_csi_read(dp, 0x70c) != 0x27000000) {
			gani_csi_write(dp, 0x70c, 0x27000000);
E 28
		}
		break;
I 28

	case R8168_11:
		if (dp->speed == GEM_SPD_10) {
			gani_mii_write_raw(dp, 0x1f, 0x0000);
			gani_mii_write_raw(dp, 0x10, 0x04ee);
		} else {
			gani_mii_write_raw(dp, 0x1f, 0x0000);
			gani_mii_write_raw(dp, 0x10, 0x01ee);
		}
		break;
E 28
	}
E 24
E 23
E 22

D 22
	if (GANI_PCIE(lp->chip->type) && !dp->mii_fixedmode &&
	    dp->speed == GEM_SPD_100 && !dp->full_duplex) {
		/*
D 17
		 * XXX - rtl816x nics seem not to recognize 100M half duplex
		 * mode correctly when it link up if two or more bits are set
		 * in the advertize register.
		 * For a workaround, we issue autonegotiaion again after
		 * modifying advertizement register to have only one bit
		 * set.
E 17
I 17
		 * XXX - rtl816x nics don't seem to recognize 100M half
		 * duplex mode properly when it link up with two or more
		 * bits in advertize register set.
		 * For a workaround, we restart autonegotiaion again after
		 * modifying the value in the advertising register to have
		 * only one bit set.
E 17
		 */
		if (lp->media_setup_phase == 0) {
D 17
			/* phase0: replase mii advert register */
E 17
I 17
			/* phase0: replace the value in mii advert register */
E 17
			lp->adv = gani_mii_read(dp, MII_AN_ADVERT);
			if ((lp->adv & MII_ABILITY_SPEED_DUPLEX) !=
						MII_ABILITY_100BASE_TX) {
				gani_mii_write(dp, MII_AN_ADVERT,
					MII_ABILITY_100BASE_TX |
					(lp->adv & MII_AN_ADVERT_SELECTOR));
				gani_mii_write(dp, MII_CONTROL,
					MII_CONTROL_ANE | MII_CONTROL_RSAN);
			}
			lp->media_setup_phase = 1;
		}
		else {
D 17
			/* phase1: restore advert register */
E 17
I 17
			/* phase1: restore the value in advert register */
E 17
			gani_mii_write(dp, MII_AN_ADVERT, lp->adv);
			lp->media_setup_phase = 0;
		}
	}
	else {
		lp->media_setup_phase = 0;
	}
I 17

E 22
	return (GEM_SUCCESS);
E 17
E 16
}

D 17
static void
E 17
I 17
static int
E 17
E 13
gani_start_chip(struct gem_dev *dp)
{
E 10
D 16
	int		i;
	uint32_t	val;
E 16
D 22
	struct gani_dev	*lp = (struct gani_dev *)dp->private;
E 22
I 22
	struct gani_dev	*lp = dp->private;
E 22

D 10
	DPRINTF(2, (CE_CONT, "!%s: gani_init_chip: called", dp->name));
E 10
I 10
D 11
	DPRINTF(2, (CE_CONT, "!%s: gani_start_chip: end", dp->name));
E 11
I 11
D 16
	DPRINTF(1, (CE_CONT, "!%s: gani_start_chip: called", dp->name));
E 16
I 16
	DPRINTF(0, (CE_CONT, "!%s: %s: called", dp->name, __func__));
E 16
E 11
E 10

I 13
	ASSERT(dp->mii_state == MII_STATE_LINKUP ||
D 22
	       dp->mii_state == MII_STATE_LINKDOWN);
E 22
I 22
	    dp->mii_state == MII_STATE_LINKDOWN);
E 22

E 13
I 10
D 16
	/*
	 * Kick Rx and Tx
	 */
E 10
D 5
	/* ID registers: set later by gani_set_rx_filter */
	/* Multicast registers: set later by gani_set_rx_filter */

I 4
	/* set tally counter area address */
	OUTL(dp, DTCCRH, (uint32_t)(((uint64_t)((long)TALLY_BASE(dp))) >> 32));
#ifdef SANITY
	OUTL(dp, DTCCRL, (uint32_t)((long)(TALLY_BASE(dp))));
#endif
E 5
E 4
D 9
	/* make writable registers */
	OUTB(dp, CR9346, CR9346_EEM_WE);
E 9
I 9
D 11
	/* make registers writable */
	OUTB(dp, CR9346, CR9346_EEM_WE); FLSHB(dp, CR9346);
E 11
E 9

	/* Command register : Enable Tx and Rx before writing TCR and RCR */
	OUTB(dp, CR, CR_RE | CR_TE);

D 9
	/* Early Tx reg */
I 4
D 5
#ifdef notdef
E 4
D 3
	OUTB(dp, ETThR, ETThR_MASK);
E 3
I 3
	OUTB(dp, ETThR, min(ETThR_MASK, (max(128, dp->txthr)) / ETThR_UNIT));
E 3
D 4

E 4
I 4
#else
E 5
	/* XXX - store and forward */
	OUTB(dp, ETThR, ETThR_MASK);
E 9
I 9
D 11
	/* Early Tx register */
	OUTB(dp, ETThR, min(dp->txthr / ETThR_UNIT, ETThR_MASK));
E 9
D 5
#endif
E 5
I 5

E 11
E 5
E 4
D 10
	/* Rx packet Maxmum size */
D 4
	OUTW(dp, RMS, 0x800 /*dp->mtu + 14 + ETHERFCSL*/);	/* max 16k */
E 4
I 4
D 5
	OUTW(dp, RMS, sizeof(struct ether_header) + dp->mtu + 8); /* max 16k-1 */
E 5
I 5
	OUTW(dp, RMS, sizeof(struct ether_header) + dp->mtu
			+ ETHERFCSL + 4);/* max 16k-1 */
E 10
I 10
	/*
	 * Rx packet Maxmum size:
	 * XXX - I think actual that max packet size will be limited by
	 * tx fifo size, aka  8K-1.
	 */
	OUTW(dp, RMS, sizeof(struct ether_header) + dp->mtu + ETHERFCSL + 4);
I 11
	DPRINTF(2 , (CE_CONT, "!%s: RMS 0x%x", dp->name, INW(dp, RMS)));
E 11
E 10
E 5
E 4

I 5
D 9
	/* ID registers: set later by gani_set_rx_filter */
	/* Multicast registers: set later by gani_set_rx_filter */
E 9
I 9
D 10
	/* ID registers will be set later by gani_set_rx_filter */
	/* Multicast hash registers will be  set later by gani_set_rx_filter */
E 9

E 10
E 5
D 13
	/* Receive configuration register : */
E 13
I 13
	/* Receive control register: write an initial value */
E 13
I 5
	val = 0;
	if (dp->rxmaxdma <= 64) {
		val |= RCR_MXDMA_64;
	} else if (dp->rxmaxdma<= 128) {
		val |= RCR_MXDMA_128;
	} else if (dp->rxmaxdma<= 256) {
		val |= RCR_MXDMA_256;
	} else if (dp->rxmaxdma<= 512) {
		val |= RCR_MXDMA_512;
	} else if (dp->rxmaxdma<= 1024) {
		val |= RCR_MXDMA_1024;
	} else {
		val |= RCR_MXDMA_UNLIMITED;
	}
D 13

E 13
E 5
D 10
	if (dp->rxthr <= RCR_RXFTH_64) {
E 10
I 10
	if (dp->rxthr <= 64) {
E 10
D 5
		lp->rcr = RCR_RXFTH_64;
E 5
I 5
		val |= RCR_RXFTH_64;
E 5
D 10
	} else if (dp->rxthr <= RCR_RXFTH_128) {
E 10
I 10
	} else if (dp->rxthr <= 128) {
E 10
D 5
		lp->rcr = RCR_RXFTH_128;
E 5
I 5
		val |= RCR_RXFTH_128;
E 5
D 10
	} else if (dp->rxthr <= RCR_RXFTH_256) {
E 10
I 10
	} else if (dp->rxthr <= 256) {
E 10
D 5
		lp->rcr = RCR_RXFTH_256;
E 5
I 5
		val |= RCR_RXFTH_256;
E 5
D 10
	} else if (dp->rxthr <= RCR_RXFTH_512) {
E 10
I 10
	} else if (dp->rxthr <= 512) {
E 10
D 5
		lp->rcr = RCR_RXFTH_512;
E 5
I 5
		val |= RCR_RXFTH_512;
E 5
D 10
	} else if (dp->rxthr <= RCR_RXFTH_1024) {
E 10
I 10
	} else if (dp->rxthr <= 1024) {
E 10
D 5
		lp->rcr = RCR_RXFTH_1024;
E 5
I 5
		val |= RCR_RXFTH_1024;
E 5
	} else {
D 5
		lp->rcr = RCR_RXFTH_NONE;
E 5
I 5
		val |= RCR_RXFTH_NONE;	/* store and forward */
E 5
	}
I 13
	lp->rcr |= val;
	OUTL(dp, RCR, lp->rcr);
E 13
D 4
	lp->rcr |= RCR_RER8 | RCR_MXDMA_1024 | RCR_AER | RCR_AR;
E 4
I 4
D 5
	lp->rcr |= RCR_RER8 | RCR_MXDMA_UNLIMIT | RCR_AER | RCR_AR;
E 5
I 5
D 10
	lp->rcr = (INL(dp, RCR) & ~RCR_MASK)
D 9
		| RCR_RER8 | RCR_AER | RCR_AR | val;
E 9
I 9
		| RCR_RER8 | val;
E 10
E 9
E 5
E 4

I 10
D 13
	/*
	 * XXX - Setup dma parameters in rcr, but keep undocumented bits.
	 * This also implies to disable receiving packets.
	 */
	lp->rcr = (INL(dp, RCR) & ~RCR_MASK) | val;
E 10
D 4
	OUTL(dp, RCR, lp->rcr);
E 4
I 4
D 5
	OUTL(dp, RCR, (INL(dp, RCR) & ~RCR_MASK) | lp->rcr);
E 5
I 5
D 11
	OUTL(dp, RCR, lp->rcr);
E 11
E 5
E 4

I 11
	/*
	 * We call set_rx_filter explicitely here, becase rx config register
	 * will not be written while the nic isn't active.
	 */
	gani_set_rx_filter(dp);

E 13
	/* Early Tx register */
	OUTB(dp, ETThR, min(dp->txthr / ETThR_UNIT, ETThR_MASK));
	DPRINTF(2 , (CE_CONT, "!%s: ETThR 0x%x", dp->name, INB(dp, ETThR)));

E 11
	/* Transmit configration register : */
D 4
	OUTL(dp, TCR, TCR_IFG_802_3 | TCR_LBK_NORMAL | TCR_MXDMA_1024);
E 4
I 4
D 5
	OUTL(dp, TCR, TCR_IFG_802_3 | TCR_LBK_NORMAL | TCR_MXDMA_UNLIMIT);
E 5
I 5
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
		val = TCR_MXDMA_UNLIMITED;
	}
D 9
#ifdef notdef
	val = TCR_MXDMA_UNLIMITED;
#endif
E 9
I 9
D 11

E 11
E 9
	OUTL(dp, TCR, TCR_IFG_802_3 | TCR_LBK_NORMAL | val);
E 5
E 4

D 4
	/* reset CpCR */
E 4
I 4
D 11
	/* CpCR */
D 5
#ifdef notdef
E 4
	OUTW(dp, CpCR, INW(dp, CpCR));
	if (lp->chip->type == MAC_VER_D) {
		OUTW(dp, CpCR, INW(dp, CpCR) | 0x4000 | CpCR_MulRW);
E 5
I 5
	val = INW(dp, CpCR);
I 9
	OUTW(dp, CpCR, val);	/* XXX */
E 9
	if (lp->chip->type == MAC_VER_D || lp->chip->type == MAC_VER_E) {
		/* what is this ? */
		val |= 0x4000;
E 5
	}
I 4
D 5
#else
	switch (lp->chip->type) {
	case MAC_VER_D:	/* 23bit M2 */
	case MAC_VER_E:	/* 26bit M3 */
		OUTW(dp, CpCR, INW(dp, CpCR) | 0x4000 | CpCR_MulRW);
		break;
	default:
		OUTW(dp, CpCR, INW(dp, CpCR) | CpCR_MulRW);
		break;
	}
E 5
I 5
	OUTW(dp, CpCR, val | CpCR_MulRW);

E 5
	/* XXX - undocumented */
	OUTW(dp, 0xe2, 0);
D 5
#endif
E 5
E 4

D 5
	/* Dump Tally Count Register : don't touch for the time being */

E 5
	/* Transmit Normal Priority Descriptors */
D 5
	DPRINTF(2 , (CE_CONT, "%s: TNPDS 0x%llx", dp->name, dp->tx_ring_dma));
E 5
I 5
	DPRINTF(2 , (CE_CONT, "!%s: TNPDS 0x%llx", dp->name, dp->tx_ring_dma));
E 5
D 9
	OUTL(dp, TNPDSL,(uint32_t)dp->tx_ring_dma);
	OUTL(dp, TNPDSH,(uint32_t)(dp->tx_ring_dma >> 32));
E 9
I 9
	OUTL(dp, TNPDSL, (uint32_t)dp->tx_ring_dma);
	OUTL(dp, TNPDSH, (uint32_t)(dp->tx_ring_dma >> 32));
E 9

I 5
D 9
	lp->tx_list_len = 0;
E 9

E 5
	/* Transmit High Priority Descriptors: Do nothing */
	OUTL(dp, THPDSL, 0);
	OUTL(dp, THPDSH, 0);

	/* Receive Descriptor Start Address register */
	OUTL(dp, RDSARL, (uint32_t)dp->rx_ring_dma);
	OUTL(dp, RDSARH, (uint32_t)(dp->rx_ring_dma >> 32));
D 5
	DPRINTF(2 , (CE_CONT, "%s: RDSAR 0x%llx", dp->name, dp->rx_ring_dma));
E 5
I 5
	DPRINTF(2 , (CE_CONT, "!%s: RDSAR 0x%llx", dp->name, dp->rx_ring_dma));
E 5

	/* make config registers read only */
	OUTB(dp, CR9346, CR9346_EEM_NORMAL);
	drv_usecwait(10);

E 11
I 5
D 10

	/* Dump Tally Count Register : */
	OUTL(dp, DTCCRH, (uint32_t)(TALLY_DMA(dp) >> 32));
#ifdef SANITY
	OUTL(dp, DTCCRL, 0);
#endif
	bzero(&lp->last_stat, sizeof(struct rtl8169_tally_counters));

E 10
E 5
	/* Missed packet counter: clear it */
	OUTL(dp, MPC, 0);

E 16
I 16
D 23
	/* prepare to dump Tally Count Register : */
E 23
I 23
	/* prepare to dump Tally Count Registers */
E 23
D 22
	OUTL(dp, DTCCRH, (uint32_t) (TALLY_DMA_ADDR(dp) >> 32));
E 22
I 22
	OUTL(dp, DTCCRH, (uint32_t)(TALLY_DMA_ADDR(dp) >> 32));
E 22
#ifdef SANITY
	OUTL(dp, DTCCRL, 0);
#endif
E 16
D 10
	/* Flash memory read/wirte register: no need to touch */
E 10
I 10
D 11
	/*
	 * We call set_rx_filter explicitely here, becase rx config register
	 * will not be written while the nic isn't active.
	 */
	gani_set_rx_filter(dp);
E 10

E 11
D 10
	/* Interrupt mask register */
D 6
	OUTW(dp, IMR, 0);
E 6
I 6
	OUTW(dp, IMR, lp->imr_hw = 0);
E 6

	/* Interrupt status register */
	OUTW(dp, ISR, 0xffff);

	/* TimerInt Register */
	OUTL(dp, TimerInt, 0);

	/* Timer count register: test count rate */
	OUTL(dp, TCTR, 0);
D 5
#if DEBUG_LEVEL > 0
E 5
I 5
#if DEBUG_LEVEL > 3
E 5
	drv_usecwait(1000);
D 5
	DPRINTF(0, (CE_CONT, "%s: TCTR:%d", dp->name, INL(dp, TCTR)));
E 5
I 5
D 6
	DPRINTF(0, (CE_CONT, "!%s: TCTR:%d", dp->name, INL(dp, TCTR)));
E 6
I 6
	cmn_err(CE_CONT, "!%s: TCTR:%d", dp->name, INL(dp, TCTR));
E 6
E 5
#endif

I 9
	lp->tx_list_len = 0;
	lp->tx_pkt_cnt = 0;
	lp->rx_pkt_cnt = 0;

E 9
	DPRINTF(2, (CE_CONT, "!%s: gani_start_chip: end", dp->name));
}

static void
gani_start_chip(struct gem_dev *dp)
{
	struct gani_dev	*lp = (struct gani_dev *)dp->private;

E 10
I 4
	/* clear tally counter area */
D 5
	bzero(TALLY_BASE(dp), TC_SIZE);
E 5
I 5
D 6
	DPRINTF(0, (CE_CONT, "!%s: tally base: vaddr:0x%p, dma addr:0x%p",
E 6
I 6
D 22
	DPRINTF(2, (CE_CONT, "!%s: tally base: vaddr:0x%p, dma addr:0x%p",
E 6
D 16
		dp->name, TALLY_VADDR(dp), TALLY_DMA(dp)));
E 16
I 16
		dp->name, TALLY_VADDR(dp), TALLY_DMA_ADDR(dp)));
E 22
I 22
	DPRINTF(2, (CE_CONT, "!%s: tally base: vaddr:0x%p, dma addr:0x%llx",
	    dp->name, TALLY_VADDR(dp),
	    (unsigned long long)TALLY_DMA_ADDR(dp)));
E 22
E 16
	bzero(TALLY_VADDR(dp), TC_SIZE);
E 5
D 21
	lp->last_stats_time = ddi_get_lbolt();
E 21

E 4
D 5
	/* Media status register */
	gani_set_media(dp);

E 5
D 22
	/* MulInt Register */
	OUTW(dp, MULINT, INW(dp, MULINT) & 0xf000);

E 22
	/* Enable interrupts */
I 4
D 9
	lp->imr = OUR_INTR_MASK
D 6
#ifdef OPT_TDU_INTR
		| INTR_SWInt
#endif
E 6
E 4
#ifdef TX_DELAYED_INTR
D 4
	lp->imr = lp->tx_delayed_intr
			? OUR_INTR_MASK_TX_DELAYED_INTR
			: OUR_INTR_MASK;
#else
	lp->imr = OUR_INTR_MASK;
E 4
I 4
		| INTR_TimeOut
E 9
I 9
D 22
	lp->imr = OUR_INTR_MASK;
I 18
#ifdef CONFIG_OPT_TPPOLL
E 22
I 22
D 28
	if (GANI_PCIE_GIGA(lp->chip->type)) {
		lp->imr = OUR_INTR_MASK_8168;
D 23
		if (lp->chip->type == R8168_CFG_METHOD_1) {
E 23
I 23
		if (lp->chip->type == R8168_1 /* RTL8168B rev.B */) {
E 23
			lp->imr |= INTR_FOVW;
		}
	} else {
		lp->imr = OUR_INTR_MASK;
E 28
I 28
	lp->imr = OUR_INTR_MASK;
	if (GANI_PCIE(lp)) {
		lp->imr |= INTR_TDU;
E 28
	}
D 23
#if defined(CONFIG_OPT_TPPOLL) || defined(WA_NO_TPPOLL_WRAP)
E 23
I 23
D 28
#ifdef CONFIG_OPT_TPPOLL
E 23
E 22
	lp->imr |= INTR_TDU;
#endif
E 28
I 28
D 29
	if (lp->chip->type == R8168_1 /* RTL8168B rev.B */) {
		lp->imr |= INTR_FOVW;
	}
E 29
E 28
E 18
D 16
#ifdef CONFIG_POLLING
E 16
I 16
D 22
#ifdef GEM_CONFIG_POLLING
E 22
I 22
#ifdef CONFIG_POLLING
E 22
E 16
	lp->imr |= INTR_TimeOut;
E 9
E 4
#endif
I 16
D 22
	lp->imr_disabled = 0;

E 22
E 16
I 4
D 9
		;
I 7
#ifdef OPT_TDU_INTR
	lp->imr &= ~INTR_TDU;
#endif
E 9
E 7
E 4
D 6
	lp->imr_hw = lp->imr;
E 6
	if ((dp->misc_flag & GEM_NOINTR) == 0) {
D 6
		OUTW(dp, IMR, lp->imr_hw);
E 6
I 6
D 22
		OUTW(dp, IMR, lp->imr_hw = lp->imr);
E 22
I 22
		OUTW(dp, IMR, lp->imr);
		FLSHW(dp, IMR);
E 22
E 6
	}
I 13
#ifdef DEBUG_HANG
	gani_dump_regs(dp, "start_chip done");
#endif
I 17
	return (GEM_SUCCESS);
E 17
E 13
D 10

	/* Rx and Tx has been kicked */
E 10
}

D 16
static void
E 16
I 16
/*
 * gani_stop_chip: disable interrupts and ensure rx has stopped.
 */
static int
E 16
gani_stop_chip(struct gem_dev *dp)
{
I 4
D 10
	int	i;
E 10
I 10
	int		i;
I 27
	uint8_t		*m;
E 27
I 23
	struct gani_dev	*lp = dp->private;
E 23
E 10
E 4
D 22
	struct gani_dev	*lp = (struct gani_dev *)dp->private;
E 22

I 4
D 10
	/* stop dumping tally counters */
	for (i = 100; i > 0; i--) {
		if ((INL(dp, DTCCRL) & DTCCR_CMD) == 0) {
E 10
I 10
D 11
	/* wait for dumping tally counters stop. */
E 11
I 11
D 16
	DPRINTF(1, (CE_CONT, "!%s: gani_stop_chip: called", dp->name));
E 16
I 16
	DPRINTF(0, (CE_CONT, "!%s: %s: called", dp->name, __func__));
E 16
D 22

E 22
I 22
#if DEBUG_LEVEL > 1
	if (dp->tx_desc_head != dp->tx_desc_tail) {
		gani_tx_desc_dump(dp);
	}
#endif
E 22
D 23
	/* wait for dumping tally counters stops. */
E 23
I 23
	/* wait until dumping tally counters stops. */
E 23
E 11
D 15
	i = 0;
	while ((INL(dp, DTCCRL) & DTCCR_CMD) != 0) {
		if (i++ > 100) {
E 15
I 15
D 22
	for (i = 0; (INL(dp, DTCCRL) & DTCCR_CMD) != 0; i++) {
E 22
I 22
	for (i = 0; INL(dp, DTCCRL) & DTCCR_CMD; i++) {
E 22
		if (i > 100) {
E 15
			cmn_err(CE_WARN, "!%s: timeout: dumping tally counters",
D 22
				dp->name);
E 22
I 22
			    dp->name);
E 22
E 10
			break;
		}
		drv_usecwait(10);
	}
D 10
	if (i == 0) {
		cmn_err(CE_WARN, "%s: timeout: dumping tally counters",
			dp->name);
	}
E 10

I 5
D 6
	IO_BARRIER_ENTER(lp);

E 6
E 5
E 4
	/* disable interrupts */
I 23
	/* XXX - don't clear pended interrupts */
E 23
I 6
D 9
	mutex_enter(&lp->reglock);
E 9
E 6
D 22
	lp->imr = 0;
I 16
	lp->imr_disabled = 0;
E 16
D 11
	OUTW(dp, IMR, lp->imr_hw = lp->imr);
E 11
I 11
D 12
	OUTW(dp, IMR, lp->imr_hw = lp->imr); FLSHW(dp, IMR);
E 12
I 12
	OUTW(dp, IMR, lp->imr_hw = lp->imr);
E 12
E 11
I 6
D 9
	mutex_exit(&lp->reglock);
E 9
E 6
D 16

E 16
I 16
#ifdef notdef
	/* XXX - This control has been moved into gem layer. */
E 16
D 11
	/* Clear pended interrupt */
	OUTW(dp, ISR, 0xffff);
E 11
I 11
	/* disable rx filter for preparing the next gani_start_chip() */
I 13
	lp->rcr &= ~(RCR_ACCEPT_MODE | RCR_RER8);
E 13
	OUTL(dp, RCR, lp->rcr);
E 11
D 16

E 16
I 16
#endif
E 22
I 22
	OUTW(dp, IMR, 0);
	FLSHW(dp, IMR);

I 24
	switch (lp->chip->type) {
	case R8101_4:
	case R8101_5:
D 28
        	if (gani_csi_read(dp, 0x70c) != 0x17000000) {
                        gani_csi_write(dp, 0x70c, 0x17000000);
E 28
I 28
		if (gani_csi_read(dp, 0x70c) != 0x17000000) {
			gani_csi_write(dp, 0x70c, 0x17000000);
E 28
		}
		break;
	}

E 24
E 22
E 16
D 23
	/* disable RX and TX */
D 11
	OUTB(dp, CR, 0);
E 11
I 11
D 12
	OUTB(dp, CR, 0); FLSHW(dp, CR);
E 12
I 12
	OUTB(dp, CR, 0);
I 22
	FLSHB(dp, CR);
E 23
I 23
	/* stop nic core */
	(void) (dp->gc.gc_reset_chip)(dp);
E 23
E 22
E 12

I 26
D 27
	/* restore factory mac addr */
E 27
I 27
	/* restore factory mac address */
E 27
	OUTB(dp, CR9346, CR9346_EEM_WE);
D 27
	for (i = 0; i < ETHERADDRL; i++) {
		OUTB(dp, IDR + i, dp->dev_addr.ether_addr_octet[i]);
	}
E 27
I 27
	m = dp->dev_addr.ether_addr_octet;
	OUTL(dp, IDR + 0,
	    (m[3] << 24) | (m[2] << 16) | (m[1] << 8) | m[0]);
D 28
	OUTL(dp, IDR + 4, (m[5] <<  8) | m[4]);
E 28
I 28
	OUTL(dp, IDR + 4, (m[5] << 8) | m[4]);
E 28
E 27
	OUTB(dp, CR9346, CR9346_EEM_NORMAL);

E 26
D 16
	/* Clear pended interrupt */
E 16
I 16
D 23
	if (dp->speed == GEM_SPD_10) {
		drv_usecwait(2000);
	} else {
		drv_usecwait(200);
	}
D 22

	/* Clear pended interrupts */
E 16
	OUTW(dp, ISR, 0xffff); FLSHW(dp, ISR);
E 22
I 22
#ifdef notdef
	/* clear bogus interrupts */
	OUTW(dp, ISR, 0xffff);
	FLSHW(dp, ISR);
#endif
	/* XXX - don't clear pended interrupts */
E 23
E 22
I 13
#ifdef DEBUG_HANG
	gani_dump_regs(dp, "stop_chip done");
#endif
I 16
	return (GEM_SUCCESS);
E 16
E 13
E 11
I 5
D 6

	IO_BARRIER_EXIT(lp);
E 6
E 5
}

D 17
static void
E 17
I 17
D 21
static int
E 17
gani_get_stats(struct gem_dev *dp)
E 21
I 21
/* private function */
static boolean_t
gani_update_stats(struct gem_dev *dp)
E 21
{
I 4
D 9
	uint32_t	x;
E 9
I 9
	uint32_t			x;
E 9
D 5
	uint8_t		*tbp;
E 5
I 5
	struct rtl8169_tally_counters	*tbp;
	struct rtl8169_tally_counters	*ls;
	struct rtl8169_tally_counters	new;
E 5
D 9
	struct gani_dev	*lp = (struct gani_dev *)dp->private;
E 9
I 9
D 22
	struct gani_dev			*lp = (struct gani_dev *)dp->private;
	ddi_acc_handle_t		h = dp->desc_acc_handle;
E 22
I 22
	struct gani_dev			*lp = dp->private;
E 22
E 9

D 21
	DPRINTF(4, (CE_CONT, "!%s: gani_get_stats: called", dp->name));
E 21
I 21
	DPRINTF(4, (CE_CONT, "!%s: %s: called", dp->name, __func__));
E 21

I 21
	ASSERT(mutex_owned(&lp->stat_lock));

E 21
D 16
	if (!dp->nic_active) {
E 16
I 16
D 28
	if (!dp->mac_active) {
E 28
I 28
	if (!IS_MAC_ONLINE(dp)) {
E 28
E 16
D 13
		/* dump base is not loaded yet */
E 13
I 13
		/* nic isn't running yet */
E 13
D 19
		return;
E 19
I 19
D 21
		return (GEM_SUCCESS);
E 21
I 21
		return (B_FALSE);
E 21
E 19
	}

D 21
	lp->last_stats_time = ddi_get_lbolt();
D 5
#ifdef notdef
	if ((INL(dp, DTCCRL) & DTCCR_CMD) != 0) {
E 5
I 5
D 6
#if 1
	IO_BARRIER_ENTER(lp);
E 6
I 6

E 6
	x = INL(dp, DTCCRL);
D 6
	IO_BARRIER_EXIT(lp);
E 6

	if ((x & DTCCR_CMD) != 0) {
E 21
I 21
D 22
	if ((INL(dp, DTCCRL) & DTCCR_CMD) != 0) {
E 22
I 22
	if (INL(dp, DTCCRL) & DTCCR_CMD) {
E 22
E 21
E 5
		/* Now dumping tally counters, do nothing */
D 19
		return;
E 19
I 19
D 21
		return (GEM_SUCCESS);
E 21
I 21
		return (B_FALSE);
E 21
E 19
	}

D 22
	ddi_dma_sync(dp->desc_dma_handle,
E 22
I 22
	(void) ddi_dma_sync(dp->desc_dma_handle,
E 22
D 5
		(off_t)(TALLY_BASE(dp) - dp->rx_ring),
		(size_t)TC_SIZE,
		DDI_DMA_SYNC_FORKERNEL);
E 5
I 5
D 16
		(off_t)TALLY_OFFSET, (size_t)TC_SIZE, DDI_DMA_SYNC_FORKERNEL);
E 16
I 16
	    (off_t)TALLY_OFFSET(dp), (size_t)TC_SIZE, DDI_DMA_SYNC_FORKERNEL);
E 16
E 5

D 5
	tbp = ((caddr_t)dp->tx_ring) + sizeof(struct tx_desc)*TX_RING_SIZE;
E 5
I 5
D 16
	tbp = (struct rtl8169_tally_counters *)TALLY_VADDR(dp);
E 16
I 16
D 22
	tbp = (struct rtl8169_tally_counters *) TALLY_VADDR(dp);
E 22
I 22
	tbp = TALLY_VADDR(dp);
E 22
E 16
E 5

D 5
			/*TC_TxOK_8	*/
			/*TC_RxOK_8	*/
	dp->stats.errxmt	+= *(uint64_t *)(tbp + TC_TxEr_8);
	dp->stats.errrcv	+= *(uint32_t *)(tbp + TC_RxEr_4);
	dp->stats.missed	+= *(uint16_t *)(tbp + TC_MissPkt_2);
	dp->stats.frame		+= *(uint16_t *)(tbp + TC_FAE_2);
	dp->stats.first_coll	+= x = *(uint32_t *)(tbp + TC_Tx1Col_4);
E 5
I 5
D 9
	new.tc_txok    = LE64(tbp->tc_txok);	/* 8byte */
	new.tc_rxok    = LE64(tbp->tc_rxok);	/* 8byte */
	new.tc_txer    = LE64(tbp->tc_txer);	/* 8byte */
	new.tc_rxer    = LE32(tbp->tc_rxer);	/* 4byte */
	new.tc_misspkt = LE16(tbp->tc_misspkt);	/* 2byte */
	new.tc_fae     = LE16(tbp->tc_fae);	/* 2byte */
	new.tc_tx1col  = LE32(tbp->tc_tx1col);	/* 4byte */
	new.tc_txmcol  = LE32(tbp->tc_txmcol);	/* 4byte */
	new.tc_rxokphy = LE64(tbp->tc_rxokphy);	/* 8byte */
	new.tc_rxokbrd = LE64(tbp->tc_rxokbrd);	/* 8byte */
	new.tc_rxokmu  = LE32(tbp->tc_rxokmu);	/* 4byte */
	new.tc_txabt   = LE16(tbp->tc_txabt);	/* 2byte */
	new.tc_txundrn = LE16(tbp->tc_txundrn);	/* 2byte */
E 9
I 9
D 16
	new.tc_txok    = ddi_get64(h, &tbp->tc_txok);		/* 8byte */
	new.tc_rxok    = ddi_get64(h, &tbp->tc_rxok);		/* 8byte */
	new.tc_txer    = ddi_get64(h, &tbp->tc_txer);		/* 8byte */
	new.tc_rxer    = ddi_get32(h, &tbp->tc_rxer);		/* 4byte */
	new.tc_misspkt = ddi_get16(h, &tbp->tc_misspkt);	/* 2byte */
	new.tc_fae     = ddi_get16(h, &tbp->tc_fae);		/* 2byte */
	new.tc_tx1col  = ddi_get32(h, &tbp->tc_tx1col);		/* 4byte */
	new.tc_txmcol  = ddi_get32(h, &tbp->tc_txmcol);		/* 4byte */
	new.tc_rxokphy = ddi_get64(h, &tbp->tc_rxokphy);	/* 8byte */
	new.tc_rxokbrd = ddi_get64(h, &tbp->tc_rxokbrd);	/* 8byte */
	new.tc_rxokmu  = ddi_get32(h, &tbp->tc_rxokmu);		/* 4byte */
	new.tc_txabt   = ddi_get16(h, &tbp->tc_txabt);		/* 2byte */
	new.tc_txundrn = ddi_get16(h, &tbp->tc_txundrn);	/* 2byte */
E 16
I 16
D 22
	new.tc_txok    = LE64(tbp->tc_txok);	/* 8byte */
	new.tc_rxok    = LE64(tbp->tc_rxok);	/* 8byte */
	new.tc_txer    = LE64(tbp->tc_txer);	/* 8byte */
	new.tc_rxer    = LE32(tbp->tc_rxer);	/* 4byte */
	new.tc_misspkt = LE16(tbp->tc_misspkt);	/* 2byte */
	new.tc_fae     = LE16(tbp->tc_fae);	/* 2byte */
	new.tc_tx1col  = LE32(tbp->tc_tx1col);	/* 4byte */
	new.tc_txmcol  = LE32(tbp->tc_txmcol);	/* 4byte */
	new.tc_rxokphy = LE64(tbp->tc_rxokphy);	/* 8byte */
	new.tc_rxokbrd = LE64(tbp->tc_rxokbrd);	/* 8byte */
	new.tc_rxokmu  = LE32(tbp->tc_rxokmu);	/* 4byte */
	new.tc_txabt   = LE16(tbp->tc_txabt);	/* 2byte */
	new.tc_txundrn = LE16(tbp->tc_txundrn);	/* 2byte */
E 22
I 22
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
E 22
E 16
E 9

D 22
	ls = &lp->last_stat;
	dp->stats.errxmt	+= new.tc_txer       - ls->tc_txer;
	dp->stats.errrcv	+= new.tc_rxer       - ls->tc_rxer;
	dp->stats.missed	+= new.tc_misspkt    - ls->tc_misspkt;
	dp->stats.frame		+= new.tc_fae        - ls->tc_fae;
	dp->stats.first_coll	+= x = new.tc_tx1col - ls->tc_tx1col;
E 5
	dp->stats.collisions += x;
D 5
	dp->stats.multi_coll	+= x = *(uint32_t *)(tbp + TC_TxMCol_4);
E 5
I 5
	dp->stats.multi_coll	+= x = new.tc_txmcol - ls->tc_txmcol;
E 5
	dp->stats.collisions += x*2;
D 5
			/*TC_RxOkPhy_8	*/
			/*TC_RxOkBrd_8	*/
			/*TC_RxOkMu_4	*/
	dp->stats.excoll	+= *(uint16_t *)(tbp + TC_TxAbt_2);
	dp->stats.underflow	+= *(uint16_t *)(tbp + TC_TxUndrn_2);
E 5
I 5
	dp->stats.excoll	+= new.tc_txabt        - ls->tc_txabt;
D 9
	dp->stats.underflow	+= new.tc_txundrn    - ls->tc_txundrn;;
E 9
I 9
	dp->stats.underflow	+= new.tc_txundrn    - ls->tc_txundrn;
E 9
E 5

E 22
I 22
	if (lp->last_stats_valid) {
I 28
		struct gem_stats	*gsp = &dp->stats;
#if 0
E 28
		ls = &lp->last_stat;
D 28
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
E 28
I 28
		gsp->errxmt += new.tc_txer - ls->tc_txer;
		gsp->errrcv += new.tc_rxer - ls->tc_rxer;
		gsp->missed += new.tc_misspkt - ls->tc_misspkt;
		gsp->frame += new.tc_fae - ls->tc_fae;
		gsp->first_coll +=	x = new.tc_tx1col - ls->tc_tx1col;
		gsp->collisions +=	x;
		gsp->multi_coll +=	x = new.tc_txmcol - ls->tc_txmcol;
		gsp->collisions +=	x*2;
		gsp->excoll += new.tc_txabt - ls->tc_txabt;
		gsp->underflow += new.tc_txundrn - ls->tc_txundrn;
#else
		uint64_t	txer;
		uint64_t	txok;
		uint64_t	rxer;
		uint64_t	rxok;

		ls = &lp->last_stat;

		txer = new.tc_txer - ls->tc_txer;
		txok = new.tc_txok - ls->tc_txok;
		rxer = new.tc_rxer - ls->tc_rxer;
		rxok = new.tc_rxok - ls->tc_rxok;

		gsp->errrcv += rxer;
		gsp->frame += new.tc_fae - ls->tc_fae;
		gsp->missed += new.tc_misspkt - ls->tc_misspkt;

		gsp->errxmt += txer;
		gsp->first_coll += x = new.tc_tx1col - ls->tc_tx1col;
		gsp->collisions += x;
		gsp->multi_coll += x = new.tc_txmcol - ls->tc_txmcol;
		gsp->collisions += x*2;
		gsp->excoll += new.tc_txabt - ls->tc_txabt;

		gsp->underflow += new.tc_txundrn - ls->tc_txundrn;
#ifdef NEVER
		gsp->rpackets += rxok + rxer;
		gsp->opackets += txok + txer;
#endif
#endif
E 28
	}
I 28

E 28
E 22
D 5
	/* issue Dump Tally Counters Cmd */
	OUTL(dp, DTCCRL, DTCCR_CMD |
		(uint32_t)((long)(dp->tx_ring_dma +
			sizeof(struct tx_desc)*TX_RING_SIZE)));
E 5
I 5
D 19
	STRUCT_COPY(lp->last_stat, new);
E 19
I 19
	lp->last_stat = new;
I 22
	lp->last_stats_valid = B_TRUE;
E 22
E 19

I 16
D 22
	if (!lp->stats_valid) {
		lp->stats_valid = B_TRUE;
		bzero(&dp->stats, sizeof(dp->stats));
	}

E 22
E 16
D 6
	/* issue Dump Tally Counters Cmd for the next call */
	IO_BARRIER_ENTER(lp);
E 6
I 6
	/* issue Dump_Tally_Counters_Cmd for the next call */
E 6
D 16
	OUTL(dp, DTCCRL, DTCCR_CMD | (uint32_t) TALLY_DMA(dp));
E 16
I 16
D 22
	bzero(&tbp, sizeof(struct rtl8169_tally_counters));
	OUTL(dp, DTCCRL, DTCCR_CMD | (uint32_t) TALLY_DMA_ADDR(dp));
E 22
I 22
	bzero(tbp, sizeof (struct rtl8169_tally_counters));
	OUTL(dp, DTCCRL, DTCCR_CMD | (uint32_t)TALLY_DMA_ADDR(dp));
E 22
I 17

I 21
	return (B_TRUE);
}

/* private function */
static void
gani_stat_timeout(void *arg)
{
D 22
	struct gem_dev	*dp = (struct gem_dev *) arg;
	struct gani_dev	*lp = (struct gani_dev *) dp->private;
E 22
I 22
	struct gem_dev	*dp = arg;
	struct gani_dev	*lp = dp->private;
E 22

	mutex_enter(&lp->stat_lock);
	(void) gani_update_stats(dp);
	lp->stat_to_id = timeout(gani_stat_timeout, dp, ONESEC);
	mutex_exit(&lp->stat_lock);
}

static int
gani_get_stats(struct gem_dev *dp)
{
D 22
	int		ret;
	struct gani_dev	*lp = (struct gani_dev *) dp->private;
E 22
I 22
	struct gani_dev	*lp = dp->private;
E 22

	DPRINTF(4, (CE_CONT, "!%s: %s: called", dp->name, __func__));

	mutex_enter(&lp->stat_lock);
	(void) gani_update_stats(dp);
	mutex_exit(&lp->stat_lock);

E 21
	return (GEM_SUCCESS);
E 17
E 16
D 6
	IO_BARRIER_EXIT(lp);
E 5
#else
I 5
	IO_BARRIER_ENTER(lp);
E 5
E 4
	/* read missed count */
	dp->stats.missed += INL(dp, MPC);

	/* clear missed count */
	OUTL(dp, MPC, 0);
I 5
	IO_BARRIER_EXIT(lp);
E 5
I 4
#endif /* notdef */
E 6
E 4
}

D 13
static uint_t
gani_mcast_hash(struct gem_dev *dp, uint8_t *addr)
{
	return gem_ether_crc_be(addr);
}

static void
gani_set_rx_filter(struct gem_dev *dp)
{
	uint32_t	mode;
	uint32_t	mhash[2];
	int		i;
	uint8_t		*m;
	struct gani_dev	*lp = (struct gani_dev *)dp->private;

	DPRINTF(2, (CE_CONT, "!%s: gani_set_rx_mode: called", dp->name));

I 10
	if (!dp->nic_active) {
		/*
D 11
		 * we cannot write into rx control register
E 11
I 11
		 * we cannot write any value into rx control register
E 11
		 * until rx has be started.
		 */
		return;
	}

E 10
D 9
	/* set mac address up */	
	m = &dp->cur_addr.ether_addr_octet[0];
	OUTL(dp, IDR + 0, (m[3] << 24) | (m[2] << 16) | (m[1] << 8) | m[0]);
	OUTL(dp, IDR + 4, (m[5] <<  8) | m[4]);

E 9
	mode = RCR_AB	/* accept broadcast */
D 9
	     | RCR_APM;	/* accept physical match  */
E 9
I 9
	     | RCR_APM 	/* accept physical match  */
D 10
	     | RCR_AER | RCR_AR; /* accept error and runt packets */
E 10
I 10
	     | RCR_AER | RCR_AR | RCR_RER8; /* accept error and runt packets */
E 10

E 9
I 5
	mhash[0] = 0;
	mhash[1] = 0;
E 5

D 9
	if ((dp->rxmode & RXMODE_ALLMULTI) != 0) {
		/* accept all multicast packets */
		mode |= RCR_AM;
E 9
I 9
	if ((dp->rxmode & RXMODE_PROMISC) != 0) {
		/* promiscious mode implies all multicast and all physical */
		mode |= RCR_AM | RCR_AAP;
E 9
		mhash[0] = 0xffffffff;
		mhash[1] = 0xffffffff;
	}	
D 5
	else if ((dp->rxmode & RXMODE_PROMISC) != 0) {
E 5
I 5
D 9
	else if ((dp->rxmode & RXMODE_PROMISC) != 0 || dp->mc_count > 32) {
E 5
		/* promiscious mode implies all multicast and all physical */
		mode |= RCR_AM | RCR_AAP;
E 9
I 9
	else if ((dp->rxmode & RXMODE_ALLMULTI) != 0 || dp->mc_count > 32) {
		/* accept all multicast packets */
		mode |= RCR_AM;
E 9
		mhash[0] = 0xffffffff;
		mhash[1] = 0xffffffff;
	}
	else if (dp->mc_count > 0) {
		mode |= RCR_AM;
D 5
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
E 5
I 5
		/*
		 * make hash table to select interresting
		 * multicast address only.
		 */
		for (i = 0; i < dp->mc_count; i++) {
			uint_t	h;
			/* hash table is 64 = 2^6 bit width */
			h = dp->mc_list[i].hash >> (32 - 6);
			mhash[h / 32] |= 1 << (h % 32);
E 5
		}
D 5
		else {
			/* too many multicast addresses */
			mhash[0] = 0xffffffff;
			mhash[1] = 0xffffffff;
		}
E 5
	}	

I 9
	if (dp->nic_active) {
D 11
		/* stop rx before changing mac address and/or multicast hash */
E 11
I 11
		/*
		 * disable all kind of rx filters to stop rx before
		 * changing mac address and/or multicast hash table.
		 */
E 11
		OUTL(dp, RCR, lp->rcr);
		FLSHL(dp, RCR);
	}

	m = &dp->cur_addr.ether_addr_octet[0];
	if (bcmp(m, lp->mac, ETHERADDRL) != 0) {
		/* set mac address */	
		OUTL(dp, IDR + 0,
			(m[3] << 24) | (m[2] << 16) | (m[1] << 8) | m[0]);
		OUTL(dp, IDR + 4, (m[5] <<  8) | m[4]);
		bcopy(m, lp->mac, ETHERADDRL);
	}

E 9
	if ((mode & RCR_AM) != 0) {
		/* need to set up multicast hash table */
		OUTL(dp, MAR + 0, mhash[0]);
		OUTL(dp, MAR + 4, mhash[1]);
	}

D 4
	OUTL(dp, RCR, lp->rcr | mode);
E 4
I 4
D 5
	OUTL(dp, RCR, (INL(dp, RCR) & ~RCR_MASK) | lp->rcr | mode);
E 5
I 5
	OUTL(dp, RCR, lp->rcr | mode);
E 5
E 4

	DPRINTF(2, (CE_CONT, "!gani_set_rx_filter: returned"));
}

static void
gani_set_media(struct gem_dev *dp)
{
I 9
D 11
	int		speed;
E 11
E 9
	struct gani_dev	*lp = (struct gani_dev *)(dp)->private;

I 6
	DPRINTF(2, (CE_CONT,
		"!gani_set_media: phys: %b", INB(dp, PHYS), PHYS_BITS));

I 9
D 10
#ifdef CONFIG_POLLING
	/*
	 * Polling mode support
	 */
	/* maximum packets in 1 tick */
	speed = 1000*1000*1000/8;	/* 1Gbps in byte */
	if (dp->speed != GEM_SPD_1000) {
		speed = 100*1000*1000/8;	/* we assume 100Mbps */
	}
	lp->poll_pkt_hiwat = ((speed / dp->mtu) / drv_usectohz(1000000))
				/ lp->poll_pkt_delay;
	lp->rx_intr_hiwat  = ((speed / dp->mtu) / drv_usectohz(1000000))
				/ lp->poll_pkt_delay;

	lp->poll_interval = lp->poll_pkt_delay * dp->mtu / (speed/1000000);
								/* in uS */

	if ((lp->cfg2 & CFG2_PCICLKF) != 0) {
		/* PCI clock rate is 66MHz */
		lp->poll_interval *= 66;
	} else {
		/* PCI clock rate is 33MHz */
		lp->poll_interval *= 33;
	}
	DPRINTF(0, (CE_CONT, "%s: rx inter limiter: hiwat:%d poll:%d\n",
			dp->name, lp->rx_intr_hiwat, lp->poll_interval));
#endif
E 10
E 9
E 6
D 5
	/*
	 * fix linkdown action according to connection mode.
	 */
#ifdef notdef
	if (lp->chip->type > MAC_VER_B && lp->phy_rev < PHY_VER_G &&
	   (dp->speed == GEM_SPD_1000)) {
		dp->gc.gc_mii_linkdown_action = MII_ACTION_RESET;
E 5
I 5
	if (!dp->nic_active) {
		return;
E 5
	}
D 5
	else {
		dp->gc.gc_mii_linkdown_action = MII_ACTION_NONE;
	}
#endif
E 5
I 5

	/* restart nic to change media mode */
	mutex_enter(&dp->xmitlock);
I 6
	gani_stop_chip(dp);
E 6
	gem_restart_tx(dp);
	mutex_exit(&dp->xmitlock);
E 5
}

E 13
/*
 * discriptor  manupiration
 */
D 10
#define	gani_sched_timer(dp)	\
{	\
	uint32_t	clks;	\
	struct gani_dev	*lp = (struct gani_dev *)(dp)->private;	\
	\
	switch(dp->speed) {	\
	case GEM_SPD_1000:	\
		clks = lp->tx_remain * 8 / 30;	\
		break;		\
	case GEM_SPD_100:	\
		clks = lp->tx_remain * 8 / 3;	\
		break;		\
	default:		\
		clks = lp->tx_remain * 80 / 3;	\
		break;		\
	}	\
D 5
	clks += INL(dp, TCTR) + TIM_10us;	\
E 5
I 5
D 6
	clks = (clks + TIM_10us) << (lp->cfg2 & CFG2_PCI_CLKF);	\
E 6
I 6
	clks = (clks + TIM_10us) << (lp->cfg2 & CFG2_PCICLKF);	\
E 6
	INL(dp, TCTR) = 0;	\
E 5
	OUTL(dp, TimerInt, clks ? clks : 1); \
}

E 10
static int
D 16
gani_tx_desc_write(struct gem_dev *dp, uint_t slot,
E 16
I 16
gani_tx_desc_write(struct gem_dev *dp, int slot,
E 16
D 5
		ddi_dma_cookie_t *dmacookie, int frags, uint32_t intreq)
E 5
I 5
D 22
		ddi_dma_cookie_t *dmacookie, int frags, uint32_t flag)
E 22
I 22
D 23
		ddi_dma_cookie_t *dmacookie, int frags, uint64_t flag)
E 23
I 23
    ddi_dma_cookie_t *dmacookie, int frags, uint64_t flag)
E 23
E 22
E 5
{
	int			i;
	struct tx_desc		*tdp;
D 16
	ddi_dma_cookie_t	*dcp;
E 16
	uint32_t		mark;
I 4
D 5
	uint8_t			pollreq = 0;
E 5
I 5
D 6
	uint8_t			tppollreq = 0;
E 6
I 6
D 16
	uint8_t			tppollreq;
E 16
I 16
D 22
	uint_t			vlan_tag;
E 16
E 6
E 5
E 4
	struct gani_dev		*lp = (struct gani_dev *)dp->private;
E 22
I 22
D 23
	uint_t			vlan_tag = 0;
E 23
I 23
	uint32_t		vlan_tag = 0;
E 23
	struct gani_dev		*lp = dp->private;
E 22
I 9
D 16
	ddi_acc_handle_t	h = dp->desc_acc_handle;
E 16
I 13
	int			curslot;
E 13
E 9
D 16

#if DEBUG_LEVEL > 2
E 16
I 16
D 18
#ifdef WA_NO_DESC_WRAP
E 18
I 18
D 22
#if (TX_MAX_FRAGS > 1) && defined(WA_NO_TPPOLL_WRAP)
E 22
I 22
	uint_t			tx_ring_size = dp->gc.gc_tx_ring_size;
D 23
#if defined(GEM_CONFIG_CKSUM_OFFLOAD) && defined(GEM_CONFIG_VLAN_HW)
E 23
I 23
#ifdef GEM_CONFIG_VLAN_HW
#ifdef GEM_CONFIG_CKSUM_OFFLOAD
E 23
	uint32_t		mss;
D 23
#endif
#if TX_MAX_FRAGS > 1
#ifdef WA_NO_TPPOLL_WRAP
E 22
E 18
	int			pad = 0;
I 22
#endif /* WA_NO_TPPOLL_WRAP */
E 22
#endif
E 23
I 23
#endif /* GEM_CONFIG_CKSUM_OFFLOAD */
#endif /* GEM_CONFIG_VLAN_HW */
E 23
I 22
	uint32_t		tmp0;
	uint32_t		tmp1;
	uint32_t		tmp2;

E 22
D 17
#if DEBUG_LEVEL > 3
E 17
I 17
D 28
#if DEBUG_LEVEL > 2
E 17
E 16
	cmn_err(CE_CONT,
D 10
		"%s: gani_tx_desc_write seqnum: %d, slot %d, frags: %d flag: %d",
E 10
I 10
D 16
		"!%s: gani_tx_desc_write: seqnum %d, slot %d, frags %d flag %d",
E 10
D 5
		dp->name, dp->tx_desc_tail, slot, frags, intreq);
E 5
I 5
		dp->name, dp->tx_desc_tail, slot, frags, flag);
E 16
I 16
D 22
		"!%s: %s: seqnum %d, slot %d, frags %d flag 0x%x",
		dp->name, __func__, dp->tx_active_tail, slot, frags, flag);
E 22
I 22
	    "!%s: %s: seqnum %d, slot %d, frags %d flag 0x%llx",
	    dp->name, __func__, dp->tx_active_tail, slot, frags,
	    (unsigned long long)flag);
E 22
E 16
E 5
	for (i = 0; i < frags; i++) {
D 10
		cmn_err(CE_CONT, "%d: addr: 0x%x, len: 0x%x",
E 10
I 10
D 22
		cmn_err(CE_CONT, "!%d: addr 0x%x, len 0x%x",
E 10
			i, dmacookie[i].dmac_address, dmacookie[i].dmac_size);
E 22
I 22
		cmn_err(CE_CONT, "!%d: addr 0x%llx, len 0x%x",
		    i, dmacookie[i].dmac_laddress, dmacookie[i].dmac_size);
E 22
	}
#endif
E 28
D 4
	/*
	 * To avoid condition rase, schedule tx-done interrupt
	 * before making descriptor(s) for the packet
	 */
I 3
#ifdef OPT_TX_INTR
E 4
I 4
D 13

E 13
D 9
#ifdef OPT_TDU_INTR
I 5
D 6
	IO_BARRIER_ENTER(lp);
E 5
E 4
E 3
	if ((dp->misc_flag & GEM_NOINTR) == 0 &&
D 5
	    (intreq & 1) != 0 && (lp->imr & INTR_TDU) == 0) {
E 5
I 5
	    (flag & GEM_TXFLAG_INTR) != 0 && (lp->imr & INTR_TDU) == 0) {
E 5
I 4
		/*
		 * As currently TDU interrupt is disabled, enable it.
		 */
E 4
		lp->imr |= INTR_TDU;
D 3
		OUTW(dp, IMR, lp->imr_hw = lp->imr);
E 3
I 3
D 4
		lp->imr_change_req = TRUE;
		ddi_trigger_softintr(lp->soft_id);
E 4
I 4
D 5
		pollreq = TPPoll_FSWInt;
E 5
I 5
		tppollreq |= TPPoll_FSWInt;
E 6
I 6
	/* we need always to start potentially stoped mac. */
	tppollreq = TPPoll_NPQ;
	if ((flag & GEM_TXFLAG_INTR) != 0) {
		mutex_enter(&lp->reglock);
		if ((lp->imr & INTR_TDU) == 0) {
			/*
			 * Currently TDU interrupt is disabled, enable it.
			 */
			lp->imr |= INTR_TDU;
			if (lp->imr_hw != 0) {
				/* we can add interrupt mask now */
				OUTW(dp, IMR, lp->imr_hw = lp->imr);
				FLSHW(dp, IMR);
			}
		}
		mutex_exit(&lp->reglock);
E 6
E 5
E 4
E 3
	}
I 5
D 6
	IO_BARRIER_EXIT(lp);
	tppollreq |= TPPoll_NPQ;
E 6
#else
I 6
	tppollreq = 0;
E 6
	if (lp->tx_list_len++ == 0) {
E 9
I 9
	/*
D 16
	 * If we are not in rx polling mode, we need to start
	 * potentially stopped tx side of mac
E 16
I 16
	 * write tx descriptor(s) in reversed order
E 16
	 */
D 16
	tppollreq = GANI_IS_POLLING(lp) ? 0 : TPPoll_NPQ;
E 16
I 16
	mark = TXD0_OWN | TXD0_LS;
I 22
#ifdef GEM_CONFIG_VLAN_HW
E 22
D 31
#ifdef GEM_CONFIG_CKSUM_OFFLOAD
E 31
I 31
#ifdef CONFIG_CKSUM_OFFLOAD
E 31
D 22
	if ((flag & GEM_TXFLAG_IPv4) != 0) {
		mark |= TXD0_IPCS;
E 22
I 22
	mss = (GEM_TXFLAG_MSS & flag) >> GEM_TXFLAG_MSS_SHIFT;
	if (mss) {
		mark |= (mss << TXD0_LGSMSS_SHIFT) | TXD0_LGSEN;
D 23
	} else {
E 23
I 23
	} else if (!lp->new_cksum) {
E 23
		if (flag & GEM_TXFLAG_IPv4) {
			mark |= TXD0_IPCS;
		}
		if (flag & GEM_TXFLAG_TCP) {
			mark |= TXD0_TCPCS;
		} else if (flag & GEM_TXFLAG_UDP) {
			mark |= TXD0_UDPCS;
		}
I 23
	} else {
		if (flag & GEM_TXFLAG_IPv4) {
			vlan_tag |= TXD1_IPCS;
		}
		if (flag & GEM_TXFLAG_TCP) {
			vlan_tag |= TXD1_TCPCS;
		} else if (flag & GEM_TXFLAG_UDP) {
			vlan_tag |= TXD1_UDPCS;
		}
E 23
E 22
	}
D 22
	if ((flag & GEM_TXFLAG_TCP) != 0) {
		mark |= TXD0_TCPCS;
	}
	else if ((flag & GEM_TXFLAG_UDP) != 0) {
		mark |= TXD0_UDPCS;
	}
#endif
	vlan_tag = 0;
#ifdef CONFIG_VLAN
	if ((flag & GEM_TXFLAG_VTAG) != 0) {
		uint_t	vtag;
E 22
I 22
#endif /* GEM_CONFIG_CKSUM_OFFLOAD */
	if (flag & GEM_TXFLAG_VTAG) {
		uint32_t	vtag;
E 22
		vtag = (flag & GEM_TXFLAG_VTAG) >> GEM_TXFLAG_VTAG_SHIFT;
		vlan_tag |= TXD1_TAGC | TXD1_VID(vtag);
	}
D 22
#endif
E 22
I 22
#endif /* GEM_CONFIG_VLAN_HW */
E 22
E 16

I 28
#if DEBUG_LEVEL > 100
if (flag & (GEM_TXFLAG_IPv4 | GEM_TXFLAG_UDP | GEM_TXFLAG_TCP)) {
	cmn_err(CE_CONT,
	    "!%s: %s: seqnum %d, slot %d, frags %d flag 0x%llx, mss %d",
	    dp->name, __func__, dp->tx_active_tail, slot, frags,
	    (unsigned long long)flag, mss);
	for (i = 0; i < frags; i++) {
		cmn_err(CE_CONT, "!%d: addr 0x%llx, len 0x%x",
		    i, dmacookie[i].dmac_laddress, dmacookie[i].dmac_size);
	}
}
#endif

E 28
D 16
	if ((flag & GEM_TXFLAG_INTR) != 0 && (lp->imr & INTR_TDU) == 0) {
E 16
I 16
D 18
#ifdef WA_NO_DESC_WRAP
E 18
I 18
#if TX_MAX_FRAGS > 1
D 22
# ifdef WA_NO_TPPOLL_WRAP
E 18
	ASSERT(slot + frags <= TX_RING_SIZE);
E 22
I 22
D 23
#ifdef WA_NO_TPPOLL_WRAP
	ASSERT(slot + frags <= tx_ring_size);
E 22

D 22
	if (TX_RING_SIZE - (slot + frags) <
				dp->gc.gc_tx_max_descs_per_pkt) {
E 22
I 22
	if (tx_ring_size - (slot + frags) < TX_MAX_FRAGS) {
E 22
E 16
E 9
		/*
D 6
		 * As we are at the head of tx list, need to kick the nick
E 6
I 6
D 9
		 * As we are at the head of tx list, need to kick the MAC
E 6
		 * to start transmitting.
E 9
I 9
D 16
		 * As currently TDU interrupt is disabled, enable it.
E 16
I 16
D 18
		 * Calculate pad to fake upper layer that the last
		 * descriptor just ends at to the end of tx ring.
E 18
I 18
		 * Calculate the number of required pad to fake upper
		 * layer that the last descriptor just ends at to the
		 * end of tx ring.
E 18
E 16
E 9
		 */
D 6
		tppollreq |= TPPoll_NPQ;
E 6
I 6
D 9
		tppollreq = TPPoll_NPQ;
E 9
I 9
D 16
		lp->imr |= INTR_TDU;
		tppollreq |= TPPoll_FSWInt;
E 16
I 16
D 22
		pad = TX_RING_SIZE - (slot + frags);
E 22
I 22
		pad = tx_ring_size - (slot + frags);
E 22

		/*
		 * we also must tell actual end of the descriptors
		 * to the nic hardware.
		 */
		mark |= TXD0_EOR;
E 16
E 9
E 6
D 22
	}
E 22
E 5
D 3

E 3
I 3
D 9
#endif
E 9
I 9

E 9
E 3
D 16
	/*
	 * write tx descriptor(s) in reversed order
	 */
D 9
	mark = TXD0_LS;
	for (i = frags - 1, dcp = &dmacookie[i]; i > 0; i--, dcp--) {
E 9
I 9
	mark = TXD0_OWN | TXD0_LS;
	for (i = frags - 1, dcp = &dmacookie[i]; i >= 0; i--, dcp--) {
E 16
I 16
D 22
	if (slot + frags + pad == TX_RING_SIZE) {
		/* record the number of fragments at the tx ring  */
E 22
I 22
		/* record the number of fragments at the end of tx ring  */
E 22
		lp->tx_last_frags = frags;
	}
D 18
#endif /* WA_NO_DESC_WRAP */
E 18
I 18
D 22
# endif /* WA_NO_TPPOLL_WRAP */
E 22
I 22
#endif /* WA_NO_TPPOLL_WRAP */
E 22
E 18
E 16
E 9
D 13
		int	curslot;
E 13
I 9

E 23
I 16
D 18
#if TX_MAX_FRAGS > 1
E 18
	for (i = frags - 1; i > 0; i--) {

E 16
E 9
D 22
		curslot = SLOT(slot + i, TX_RING_SIZE);
E 22
I 22
		curslot = SLOT(slot + i, tx_ring_size);
E 22
I 9

		/*
D 10
		 * specify descriptor controling flags
E 10
I 10
		 * specify descriptor control flags
E 10
		 */
D 16
		if (i == 0) {
			mark |= TXD0_FS;
		}
E 16
D 22
		if (curslot == TX_RING_SIZE - 1) {
E 22
I 22
		if (curslot == tx_ring_size - 1) {
E 22
			mark |= TXD0_EOR;
		}
D 16

E 16
E 9
D 22
		tdp = &((struct tx_desc *)dp->tx_ring)[curslot];
D 5
		tdp->txd3 = (uint32_t)(dcp->dmac_laddress >> 32);
		tdp->txd2 = (uint32_t)(dcp->dmac_laddress);
E 5
I 5
D 9
		tdp->txd3 = LE32((uint32_t)(dcp->dmac_laddress >> 32));
		tdp->txd2 = LE32((uint32_t)(dcp->dmac_laddress));
E 5
		tdp->txd1 = 0;
D 5
		tdp->txd0 = TXD0_OWN | mark | dcp->dmac_size
D 3
			  | tdp->txd0 & TXD0_EOR;
E 3
I 3
			  | (tdp->txd0 & TXD0_EOR);
E 5
I 5
		tdp->txd0 = LE32(TXD0_OWN | mark | dcp->dmac_size
			  | ((curslot == TX_RING_SIZE - 1) ? TXD0_EOR : 0));
E 9
I 9
D 13
		ddi_put32(h, &tdp->txd3, (uint32_t)(dcp->dmac_laddress >> 32));
		ddi_put32(h, &tdp->txd2, (uint32_t)(dcp->dmac_laddress));
E 13
I 13
D 16
		ddi_put32(h, &tdp->txd3, dcp->dmac_laddress >> 32);
		ddi_put32(h, &tdp->txd2, dcp->dmac_laddress);
E 13
		ddi_put32(h, &tdp->txd1, 0);
		ddi_put32(h, &tdp->txd0, mark | dcp->dmac_size);
E 16
I 16
		tdp->txd3 = LE32(dmacookie[i].dmac_laddress >> 32);
		tdp->txd2 = LE32(dmacookie[i].dmac_laddress);
		tdp->txd1 = LE32(vlan_tag);
		tdp->txd0 = LE32(mark | (uint32_t)dmacookie[i].dmac_size);
E 22
I 22
		tdp = &TXDESC(dp->tx_ring)[curslot];
		tmp0 = (uint32_t)(dmacookie[i].dmac_laddress >> 32);
		tmp1 = (uint32_t)dmacookie[i].dmac_laddress;
		tmp2 = mark | (uint32_t)dmacookie[i].dmac_size;

		tdp->txd3 = LE_32(tmp0);
		tdp->txd2 = LE_32(tmp1);
		tdp->txd1 = LE_32(vlan_tag);
		tdp->txd0 = LE_32(tmp2);
E 22
		mark &= ~(TXD0_LS | TXD0_EOR);
	}
D 22
#endif
E 22
I 22
#endif /* TX_MAX_FRAGS > 1 */
E 22
	/*
	 * specify descriptor control flags for first fragment.
	 */
	mark |= TXD0_FS;
D 22
	if ((flag & GEM_TXFLAG_HEAD) != 0) {
E 22
I 22
	if (flag & GEM_TXFLAG_HEAD) {
E 22
		mark &= ~TXD0_OWN;
	}
D 18
#ifdef WA_NO_DESC_WRAP
	if (slot == 0) {
		mark &= ~TXD0_OWN;
	}
	else if (lp->tx_no_more) {
		mark |= TXD0_OWN;
	}
#endif
E 18
D 22
	if (slot == TX_RING_SIZE - 1) {
E 22
I 22
	if (slot == tx_ring_size - 1) {
E 22
		mark |= TXD0_EOR;
	}
E 16
E 9
E 5
E 3
D 4
#ifdef IOCACHE
E 4
I 4

E 4
D 16
		ddi_dma_sync(dp->desc_dma_handle,
			(off_t)(((caddr_t)tdp) - dp->rx_ring),
			sizeof(struct tx_desc), DDI_DMA_SYNC_FORDEV);
E 16
I 16
D 22
	tdp = &((struct tx_desc *)dp->tx_ring)[slot];
	tdp->txd3 = LE32(dmacookie->dmac_laddress >> 32);
	tdp->txd2 = LE32(dmacookie->dmac_laddress);
	tdp->txd1 = LE32(vlan_tag);
	tdp->txd0 = LE32(mark | (uint32_t) dmacookie->dmac_size);
E 22
I 22
	tdp = &TXDESC(dp->tx_ring)[slot];
	tmp0 = (uint32_t)(dmacookie[i].dmac_laddress >> 32);
	tmp1 = (uint32_t)dmacookie[i].dmac_laddress;
	tmp2 = mark | (uint32_t)dmacookie[i].dmac_size;
E 22
E 16
D 4
#endif
E 4
I 4

E 4
D 9
		mark = 0;
#ifdef TX_DELAYED_INTR
		lp->tx_remain += lp->tx_pkt_len[curslot] = dcp->dmac_size;
#endif
E 9
I 9
D 16
		mark = TXD0_OWN;
E 16
I 16
D 18
#ifdef WA_NO_DESC_WRAP
E 18
I 18
D 22
#if (TX_MAX_FRAGS > 1) && defined(WA_NO_TPPOLL_WRAP)
E 22
I 22
	tdp->txd3 = LE_32(tmp0);
	tdp->txd2 = LE_32(tmp1);
	tdp->txd1 = LE_32(vlan_tag);
	tdp->txd0 = LE_32(tmp2);

D 23
#if TX_MAX_FRAGS > 1
#ifdef WA_NO_TPPOLL_WRAP
E 22
E 18
	DPRINTF(3, (CE_CONT, "\t\t\t frags:%d pad:%d", frags, pad));
	frags += pad;
D 22
#else
	DPRINTF(3, (CE_CONT, "\t\t\t frags:%d", frags));
E 22
#endif
I 22
#endif
E 23
E 22
D 17
	return frags;
E 17
I 17
	return (frags);
E 17
}

static void
gani_tx_start(struct gem_dev *dp, int start_slot, int nslot)
{
D 22
	int		i;
	uint8_t		cmd;
E 22
	uint32_t	own;
D 22
	struct gani_dev	*lp = (struct gani_dev *)dp->private;
E 22
I 22
	uint_t		tx_ring_size = dp->gc.gc_tx_ring_size;
	struct gani_dev	*lp = dp->private;
E 22

D 22
	DPRINTF(3, (CE_CONT, "!%s: %s: start_slot %d, nslot %d",
		dp->name, __func__, start_slot, nslot));
E 22
I 22
	DPRINTF(5, (CE_CONT, "!%s: %s: start_slot %d, nslot %d",
	    dp->name, __func__, start_slot, nslot));
E 22

	ASSERT(nslot > 0);

D 18
#ifdef WA_NO_TPPOLL_WRAP
E 18
I 18
D 22
	own = LE32(TXD0_OWN);
E 22
I 22
	own = LE_32(TXD0_OWN);
E 22

D 22
#ifdef CONFIG_OPT_TPPOLL
# ifdef WA_NO_TPPOLL_WRAP
E 22
I 22
D 23
#ifdef WA_NO_TPPOLL_WRAP
	DPRINTF(5, (CE_CONT, "!%s: %s: start_slot %d, nslot %d"
	    ", no_more:%d, tx_actd:%d, tx_fshd:%d",
	    dp->name, __func__, start_slot, nslot,
	    lp->tx_no_more, lp->tx_activated, lp->tx_finished));

E 22
E 18
	if (lp->tx_no_more) {
D 22
		/* record pended requests */
E 22
I 22
		/* record the number of the pended requests */
E 22
		lp->tx_pended += nslot;
I 18

		/* merge this to current tx list */
		if (start_slot != 0) {
D 22
			((struct tx_desc *) dp->tx_ring)[start_slot].txd0
				|= own;
E 22
I 22
			TXDESC(dp->tx_ring)[start_slot].txd0 |= own;
E 22
		}
E 18
		return;
E 16
E 9
	}
I 18

E 18
I 16
D 22
	if (start_slot + nslot >= TX_RING_SIZE) {
E 22
I 22
	if (start_slot + nslot >= tx_ring_size) {
E 22
		lp->tx_no_more = B_TRUE;
D 22
		lp->tx_pended  = start_slot + nslot - TX_RING_SIZE;
		nslot = TX_RING_SIZE - start_slot;
I 18

		/* break at the head of the ring to avoid tppoll wrapping */
		if (start_slot + nslot > TX_RING_SIZE) {
			((struct tx_desc *) dp->tx_ring)[0].txd0 &= ~own;
E 22
I 22
		lp->tx_pended = start_slot + nslot - tx_ring_size;
		if (lp->tx_pended > 0) {
			/*
			 * break at the head of the ring to avoid tppoll
			 * wrapping
			 */
			TXDESC(dp->tx_ring)[0].txd0 &= ~own;
E 22
		}
I 22
		/* truncate the descriptors not to wrap the tx ring */
		nslot = tx_ring_size - start_slot;
E 22
E 18
	}
D 18
#endif
E 18
I 18
D 22
# endif /* WA_NO_TPPOLL_WRAP */
#endif /* CONFIG_OPT_TPPOLL */
E 22
I 22
#endif /* WA_NO_TPPOLL_WRAP */
#if defined(CONFIG_OPT_TPPOLL) || defined(WA_NO_TPPOLL_WRAP)
E 22
E 18
	lp->tx_activated += nslot;
E 16
D 22

E 22
I 22
#endif
E 23
E 22
D 9
	tdp = &((struct tx_desc *)dp->tx_ring)[slot];
D 5
	tdp->txd3 = (uint32_t)(dcp->dmac_laddress >> 32);
	tdp->txd2 = (uint32_t)(dcp->dmac_laddress);
E 5
I 5
	tdp->txd3 = LE32((uint32_t)(dcp->dmac_laddress >> 32));
	tdp->txd2 = LE32((uint32_t)(dcp->dmac_laddress));
E 5
	tdp->txd1 = 0;
D 5
	tdp->txd0 = TXD0_OWN | TXD0_FS | mark | dcp->dmac_size
		  | (tdp->txd0 & TXD0_EOR);
E 5
I 5
	tdp->txd0 = LE32(TXD0_OWN | TXD0_FS | mark | dcp->dmac_size
		  | ((slot == TX_RING_SIZE - 1) ? TXD0_EOR : 0));
E 5
#ifdef TX_DELAYED_INTR
	lp->tx_remain += lp->tx_pkt_len[slot] = dcp->dmac_size + IFG;
#endif
	
D 4
#ifdef IOCACHE
E 4
	ddi_dma_sync(dp->desc_dma_handle,
		(off_t)(((caddr_t)tdp) - dp->rx_ring),
		sizeof(struct tx_desc), DDI_DMA_SYNC_FORDEV);
D 4
#endif
E 4

E 9
D 5
	/* kick Tx engine */
D 4
	OUTB(dp, TPPoll, TPPoll_NPQ);
E 4
I 4
	OUTB(dp, TPPoll, TPPoll_NPQ | pollreq);
E 5
I 5
D 10
	if (tppollreq != 0) {
E 10
I 10
D 16
	if (dp->nic_active && tppollreq != 0) {
E 10
		/* kick Tx engine */
D 6
		IO_BARRIER_ENTER(lp);
E 6
		OUTB(dp, TPPoll, tppollreq);
E 16
I 16
D 18
	own = LE32(TXD0_OWN);

E 18
	if (nslot > 1) {
D 18
#ifdef notdef
		for (i = start_slot + nslot - 1; i != start_slot; i--) {
			if ((((struct tx_desc *) dp->tx_ring)
				[SLOT(i, TX_RING_SIZE)].txd0 & own) == 0) {
				cmn_err(CE_WARN,
					"%s: %s: own isn't set at %d, [%d, %d]",
					dp->name, __func__,
					SLOT(i, TX_RING_SIZE),
					start_slot, start_slot + nslot);
			}
			((struct tx_desc *) dp->tx_ring)
				[SLOT(i, TX_RING_SIZE)].txd0 |= own;
		}
#endif
E 18
		gem_tx_desc_dma_sync(dp,
D 22
				SLOT(start_slot + 1, TX_RING_SIZE),
				nslot - 1, DDI_DMA_SYNC_FORDEV);
E 22
I 22
		    SLOT(start_slot + 1, tx_ring_size),
		    nslot - 1, DDI_DMA_SYNC_FORDEV);
E 22
E 16
D 6
		FLSHB(dp, TPPoll);
		IO_BARRIER_EXIT(lp);
E 6
	}
E 5
E 4

D 9
#ifdef TX_DELAYED_INTR
D 4
	if ((intreq & 1) != 0 && lp->tx_delayed_intr) {
E 4
I 4
D 5
	if ((intreq & 1) != 0) {
E 5
I 5
	if ((flag & GEM_TXFLAG_INTR) != 0) {
E 5
E 4
		gani_sched_timer(dp);
	}
#endif
E 9
I 9
D 16
	lp->tx_list_len++;
E 16
I 16
D 18
	((struct tx_desc *)dp->tx_ring)[start_slot].txd0 |= own;
E 18
I 18
D 22
	((struct tx_desc *) dp->tx_ring)[start_slot].txd0 |= own;
E 22
I 22
	TXDESC(dp->tx_ring)[start_slot].txd0 |= own;
E 22
E 18
	gem_tx_desc_dma_sync(dp, start_slot, 1, DDI_DMA_SYNC_FORDEV);
I 30
#ifdef WA_NEW_TX_HANG
	lp->tx_last_desc = start_slot + nslot - 1;
#endif
E 30
E 16
D 10
	lp->tx_pkt_cnt++;
E 10

E 9
D 4

E 4
D 16
	return frags;
E 16
I 16
D 23
	if (dp->mac_active) {
		/* kick Tx engine */
E 23
I 23
	/* kick Tx engine */
D 28
	ASSERT(dp->mac_active);
E 23
#ifdef CONFIG_OPT_TPPOLL
D 23
		if (!lp->tx_running) {
			OUTB(dp, TPPoll, TPPoll_NPQ);
			lp->tx_running = B_TRUE;
		}
#else
E 23
I 23
	if (!lp->tx_running) {
E 23
		OUTB(dp, TPPoll, TPPoll_NPQ);
D 23
#endif
E 23
I 23
		lp->tx_running = B_TRUE;
E 23
	}
I 23
#else
E 28
I 28
	ASSERT(IS_MAC_ONLINE(dp));
E 28
	OUTB(dp, TPPoll, TPPoll_NPQ);
D 28
#endif
E 28
E 23
E 16
}

D 16
static int
gani_rx_desc_write(struct gem_dev *dp, uint_t slot,
E 16
I 16
static void
gani_rx_desc_write(struct gem_dev *dp, int slot,
E 16
		ddi_dma_cookie_t *dmacookie, int frags)
{
D 9
	struct rx_desc	*rdp;
	struct gani_dev	*lp = (struct gani_dev *)dp->private;
E 9
I 9
	uint32_t		mark;
	struct rx_desc		*rdp;
I 22
	uint32_t		tmp0;
	uint32_t		tmp1;
	uint32_t		tmp2;
E 22
D 16
	ddi_acc_handle_t	h = dp->desc_acc_handle;
E 16
E 9

I 16
#if DEBUG_LEVEL > 4
{
	int	i;
	cmn_err(CE_CONT,
D 22
		"!%s: %s: seqnum %d, slot %d, frags %d",
		dp->name, __func__, dp->rx_desc_tail, slot, frags);
E 22
I 22
	    "!%s: %s: seqnum %d, slot %d, frags %d",
	    dp->name, __func__, dp->rx_desc_tail, slot, frags);
E 22
	for (i = 0; i < frags; i++) {
D 22
		cmn_err(CE_CONT, "!%d: addr 0x%x, len 0x%x",
			i, dmacookie[i].dmac_address, dmacookie[i].dmac_size);
E 22
I 22
		cmn_err(CE_CONT, "!%d: addr 0x%llx, len 0x%x",
		    i, dmacookie[i].dmac_laddress, dmacookie[i].dmac_size);
E 22
	}
}
#endif
E 16
D 9
	ASSERT(frags == 1);
E 9
I 9
	mark = RXD0_OWN;
D 23
	if (slot == RX_RING_SIZE - 1) {
E 23
I 23
	if (slot == dp->gc.gc_rx_ring_size - 1) {
E 23
D 16
		mark |= RXD0_EOR;
E 16
I 16
		mark = RXD0_OWN | RXD0_EOR;
E 16
	}
E 9

D 22
	rdp = &((struct rx_desc *)dp->rx_ring)[slot];
E 22
I 22
	rdp = &RXDESC(dp->rx_ring)[slot];
E 22

I 28
	ASSERT(dmacookie->dmac_size == dp->rx_buf_len);
E 28
D 5
	rdp->rxd3 = (uint32_t)(dmacookie->dmac_laddress >> 32);
	rdp->rxd2 = (uint32_t)(dmacookie->dmac_laddress);
E 5
I 5
D 9
	rdp->rxd3 = LE32((uint32_t)(dmacookie->dmac_laddress >> 32));
	rdp->rxd2 = LE32((uint32_t)(dmacookie->dmac_laddress));
E 5
	rdp->rxd1 = 0;
D 5
	rdp->rxd0 = RXD0_OWN | dmacookie->dmac_size |(rdp->rxd0 & RXD0_EOR);
E 5
I 5
	rdp->rxd0 = LE32(RXD0_OWN | dmacookie->dmac_size |
			((slot == RX_RING_SIZE - 1) ? RXD0_EOR : 0));
E 9
I 9
D 13
	ddi_put32(h, &rdp->rxd3, (uint32_t)(dmacookie->dmac_laddress >> 32));
	ddi_put32(h, &rdp->rxd2, (uint32_t)(dmacookie->dmac_laddress));
E 13
I 13
D 16
	ddi_put32(h, &rdp->rxd3, dmacookie->dmac_laddress >> 32);
	ddi_put32(h, &rdp->rxd2, dmacookie->dmac_laddress);
E 13
	ddi_put32(h, &rdp->rxd1, 0);
	ddi_put32(h, &rdp->rxd0, mark | dmacookie->dmac_size);
E 9
E 5
D 4
#ifdef IOCACHE
E 4
I 4

E 4
	ddi_dma_sync(dp->desc_dma_handle,
		(off_t)(((caddr_t)rdp) - dp->rx_ring),
		sizeof(struct rx_desc), DDI_DMA_SYNC_FORDEV);
D 4
#endif
E 4
I 4

E 4
	return 1;
E 16
I 16
D 22
	rdp->rxd3 = LE32(dmacookie->dmac_laddress >> 32);
	rdp->rxd2 = LE32(dmacookie->dmac_laddress);
E 22
I 22
	tmp0 = (uint32_t)(dmacookie->dmac_laddress >> 32);
	tmp1 = (uint32_t)dmacookie->dmac_laddress;
	tmp2 = mark | (uint32_t)dmacookie->dmac_size;

	rdp->rxd3 = LE_32(tmp0);
	rdp->rxd2 = LE_32(tmp1);
E 22
	rdp->rxd1 = 0;
D 22
	rdp->rxd0 = LE32(mark | (uint32_t) dmacookie->dmac_size);
E 22
I 22
	rdp->rxd0 = LE_32(tmp2);
E 22
E 16
}

static uint_t
gani_tx_desc_stat(struct gem_dev *dp, int slot, int ndesc)
{
D 22
	int		i;
E 22
I 5
	uint32_t	tsr;
E 5
	struct tx_desc	*tdp;
D 22
	struct gani_dev	*lp = (struct gani_dev *)dp->private;
E 22
I 22
	struct gani_dev	*lp = dp->private;
E 22
I 16
	int		frags = ndesc;
I 22
	uint_t		tx_ring_size = dp->gc.gc_tx_ring_size;
E 22
E 16

I 16
D 23
#ifdef WA_NO_TPPOLL_WRAP
	ASSERT(lp->tx_finished - lp->tx_activated <= 0);
	if (lp->tx_finished == lp->tx_activated) {
D 18
		/* no more unfinished tx descriptors */
		ASSERT(lp->tx_pended > 0);
		return 0;
E 18
I 18
D 22
		/* we don't have unfinished tx descriptors now.*/
E 22
I 22
		/*
		 * XXX - avoid to call ddi_dma_sync() for descriptors
		 * which have not been issued.
		 * we don't have unfinished tx descriptors now.
		 */
E 22
		return (0);
E 18
	}
D 18
#endif
#ifdef WA_NO_DESC_WRAP
E 18
I 18
D 22
# if TX_MAX_FRAGS > 1
E 18
	if (slot + ndesc == TX_RING_SIZE) {
E 22
I 22
#if TX_MAX_FRAGS > 1
	if (slot + ndesc == tx_ring_size) {
E 22
		/* need to get actual number of fragnents for the packet */
		frags = lp->tx_last_frags;
	}
I 18
D 22
# endif
E 18
#endif
E 16
I 6
	/* XXX - we must check last descripor of the packet. */
E 6
D 5
	tdp = &((struct tx_desc *)dp->tx_ring)[slot];
E 5
I 5
D 8
	tdp = &((struct tx_desc *)dp->tx_ring)[slot + ndesc - 1];
E 8
I 8
	tdp = &((struct tx_desc *)dp->tx_ring)[
D 16
					SLOT(slot + ndesc - 1, TX_RING_SIZE)];
E 16
I 16
					SLOT(slot + frags - 1, TX_RING_SIZE)];
E 22
I 22
#endif /* TX_MAX_FRAGS > 1 */
#endif /* WA_NO_TPPOLL_WRAP */
E 22
E 16
E 8
E 5
D 4
#ifdef IOCACHE
E 4
I 4

E 23
E 4
D 16
	ddi_dma_sync(dp->desc_dma_handle,
		(off_t)(((caddr_t)tdp) - dp->rx_ring),
		sizeof(struct tx_desc), DDI_DMA_SYNC_FORKERNEL);
E 16
I 16
D 22
	tsr = LE32(tdp->txd0);
E 22
I 22
	/* XXX - we must check the last descripor of the packet. */
	tdp = &TXDESC(dp->tx_ring)[SLOT(slot + frags - 1, tx_ring_size)];
E 22
E 16
D 4
#endif
E 4
I 4

I 22
	tsr = tdp->txd0;
	tsr = LE_32(tsr);
#ifndef lint
E 22
I 5
D 9
	tsr = LE32(tdp->txd0);
E 9
I 9
D 16
	tsr = ddi_get32(dp->desc_acc_handle, &tdp->txd0);
E 9

E 16
E 5
E 4
	DPRINTF(2, (CE_CONT,
D 5
		"%s: gani_tx_desc_stat: slot:%d ndesc:%d isr:%b",
E 5
I 5
D 16
		"!%s: gani_tx_desc_stat: slot:%d ndesc:%d isr:%b",
E 5
		dp->name, slot, ndesc,
E 16
I 16
D 22
		"!%s: %s: slot:%d ndesc:%d isr:%b tsr:%b",
		dp->name, __func__, slot, ndesc,
E 16
D 5
		INW(dp, ISR), INTR_BITS, tdp->txd0, TXD0_BITS));
E 5
I 5
		INW(dp, ISR), INTR_BITS, tsr, TXD0_BITS));
E 5

D 5
	if ((tdp->txd0 & TXD0_OWN) != 0) {
E 5
I 5
	if ((tsr & TXD0_OWN) != 0) {
E 22
I 22
	    "!%s: %s: slot:%d ndesc:%d isr:%b tsr:%b",
	    dp->name, __func__, slot, ndesc,
	    INW(dp, ISR), INTR_BITS, tsr, TXD0_BITS));
#endif
	if (tsr & TXD0_OWN) {
E 22
E 5
		/* not transmitted yet */
I 23
D 28
#ifdef CONFIG_OPT_TPPOLL
		if (!lp->tx_running) {
E 28
I 28
		if (GANI_PCIE(lp)) {
			/* XXX - restart potentially stopped tx engine. */
E 28
			OUTB(dp, TPPoll, TPPoll_NPQ);
D 28
			lp->tx_running = B_TRUE;
E 28
		}
D 28
#else
		OUTB(dp, TPPoll, TPPoll_NPQ);
#endif
E 28
E 23
D 16
		return 0;
E 16
I 16
		return (0);
E 16
	}
D 9

E 9
I 5
D 16
	lp->tx_list_len--;
E 16
D 22

E 22
I 22
D 23
#if defined(CONFIG_OPT_TPPOLL) || defined(WA_NO_TPPOLL_WRAP)
E 22
E 5
D 9
#ifdef TX_DELAYED_INTR
	for (i = 0; i < ndesc; i++) {
		lp->tx_remain -= lp->tx_pkt_len[SLOT(i + slot, TX_RING_SIZE)];
	}
#endif
I 4
#ifdef OPT_TDU_INTR
E 9
I 5
D 6
	IO_BARRIER_ENTER(lp);
E 5
E 4
	if (dp->tx_desc_intr - dp->tx_desc_head - ndesc < 0 &&
	   (lp->imr & INTR_TDU) != 0) {
I 4
		/* No need to schedule any more TDU interrupt. */
E 4
		/* XXX - hardware IMR will be updated later */
		lp->imr &= ~INTR_TDU;
E 6
I 6
D 16
	if (dp->tx_desc_intr == dp->tx_desc_head + ndesc) {
		/* No need to schedule TDU interrupts any more. */
D 9
		mutex_enter(&lp->reglock);
E 9
		if ((lp->imr & INTR_TDU) != 0) {
			/* XXX - hardware IMR will be updated later */
			lp->imr &= ~INTR_TDU;
		}
E 16
I 16
	lp->tx_finished += ndesc;
D 22

#if 0
	if (dp->tx_desc_intr - (dp->tx_desc_head + ndesc) <= 0) {
		/* no need for further TOK interrupts */
		lp->imr_disabled |= INTR_TOK;
E 16
D 9
		mutex_exit(&lp->reglock);
E 9
E 6
	}
E 22
I 5
D 6
	IO_BARRIER_EXIT(lp);
E 6
E 5
I 4
D 9
#endif
E 9
E 4
D 16
	return GEM_TX_DONE;
E 16
I 16
#endif
E 23

D 22
#if DEBUG_LEVEL >= 0
	if (slot + ndesc != TX_RING_SIZE && (tsr & TXD0_EOR) != 0) {
E 22
I 22
#ifdef DEBUG_LEVEL
	if (slot + ndesc != tx_ring_size && (tsr & TXD0_EOR)) {
E 22
		/* the descriptor is corrupted */
I 22
#ifndef lint
E 22
		cmn_err(CE_WARN,
D 22
		"%s: %s: tx descriptor corrupted, slot:%d ndesc:%d tsr:%b",
			dp->name, __func__, slot, ndesc, tsr, TXD0_BITS);
E 22
I 22
		    "!%s: %s: tx descriptor corrupted, slot:%d ndesc:%d tsr:%b",
		    dp->name, __func__, slot, ndesc, tsr, TXD0_BITS);
#endif
I 23
		gani_tx_desc_dump(dp);
E 23
E 22
		return (GEM_TX_DONE | GEM_TX_ERR);
	}
D 22
#endif
E 22
I 22
#endif /* DEBUG_LEVEL */
E 22
	return (GEM_TX_DONE);
E 16
}

I 22
#ifdef DEBUG_LEVEL
E 22
D 16
static uint_t
E 16
I 16
static void
gani_tx_desc_dump(struct gem_dev *dp)
{
	int		i;
I 22
	uint_t		tx_ring_size = dp->gc.gc_tx_ring_size;
E 22
	struct tx_desc	*tdp;
D 22
	struct gani_dev	*lp = (struct gani_dev *)dp->private;
#if DEBUG_LEVEL > 2
E 22
I 22

E 22
	cmn_err(CE_CONT,
D 22
		"%s: tx descriptor dump: current head:%d[%d], tail:%d[%d]",
		dp->name,
		dp->tx_desc_head, SLOT(dp->tx_desc_head, TX_RING_SIZE),
		dp->tx_desc_tail, SLOT(dp->tx_desc_tail, TX_RING_SIZE));
E 22
I 22
	    "!%s: tx descriptor dump: current head:%d[%d], tail:%d[%d]",
	    dp->name,
	    dp->tx_desc_head, (int)SLOT(dp->tx_desc_head, tx_ring_size),
	    dp->tx_desc_tail, (int)SLOT(dp->tx_desc_tail, tx_ring_size));
E 22

D 22
	tdp = &((struct tx_desc *)dp->tx_ring)[0];
	for (i = 0; i < TX_RING_SIZE; i++, tdp++) {
E 22
I 22
	tdp = &TXDESC(dp->tx_ring)[0];
	for (i = 0; i < tx_ring_size; i++, tdp++) {
#ifdef lint
		cmn_err(CE_CONT, "%d: %x %x %x %x",
		    i,
		    LE_32(tdp->txd0),
		    LE_32(tdp->txd1),
		    LE_32(tdp->txd2),
		    LE_32(tdp->txd3));
#else
E 22
		cmn_err(CE_CONT, "%d: %b %x %x %x",
D 22
			i, 
			LE32(tdp->txd0), TXD0_BITS,
			LE32(tdp->txd1),
			LE32(tdp->txd2),
			LE32(tdp->txd3));
	}
E 22
I 22
		    i,
		    LE_32(tdp->txd0), TXD0_BITS,
		    LE_32(tdp->txd1),
		    LE_32(tdp->txd2),
		    LE_32(tdp->txd3));
E 22
D 23
#endif
E 23
I 23
#endif /* lint */
E 23
I 22
	}
E 22
}
I 22
D 23
#endif
E 23
I 23
#endif /* DEBUG_LEVEL */
E 23
E 22

static uint64_t
E 16
gani_rx_desc_stat(struct gem_dev *dp, int slot, int ndesc)
{
	uint_t		len;
	uint32_t	rsr;
	struct rx_desc	*rdp;
D 22
	struct gani_dev	*lp = (struct gani_dev *)dp->private;
E 22
D 16

E 16
I 16
	uint64_t	flags = GEM_RX_DONE;
D 22
#ifdef CONFIG_VLAN
E 22
I 22
#ifdef GEM_CONFIG_VLAN_HW
E 22
	uint64_t	vtag;
#endif
I 31
	struct gani_dev	*lp = dp->private;

E 31
E 16
D 22
	rdp = &((struct rx_desc *)dp->rx_ring)[slot];
I 16
	rsr = LE32(rdp->rxd0);
E 16
D 4
#ifdef IOCACHE
E 4
I 4

E 22
I 22
	rdp = &RXDESC(dp->rx_ring)[slot];
	rsr = rdp->rxd0;
	rsr = LE_32(rsr);
#ifndef lint
E 22
E 4
D 16
	ddi_dma_sync(dp->desc_dma_handle,
		(off_t)(((caddr_t)rdp) - dp->rx_ring),
		sizeof(struct rx_desc), DDI_DMA_SYNC_FORKERNEL);
E 16
I 16
D 17
	DPRINTF(2, (CE_CONT, "!%s: %s: slot:%d rxd0:0x%b",
		dp->name, __func__, slot, rsr, RXD0_BITS));
E 17
I 17
	DPRINTF(2, (CE_CONT, "!%s: %s: slot:%d rxd0:0x%b, rxd1:0x%x",
D 22
		dp->name, __func__, slot, rsr, RXD0_BITS, LE32(rdp->rxd1)));
E 17
E 16
D 4
#endif
E 4
I 4

E 4
D 5
	rsr = rdp->rxd0;
E 5
I 5
D 9
	rsr = LE32(rdp->rxd0);
E 9
I 9
D 16
	rsr = ddi_get32(dp->desc_acc_handle, &rdp->rxd0);
E 9
E 5

	DPRINTF(2, (CE_CONT,
D 5
		"%s: gani_rx_desc_stat: slot:%d rxd0:0x%b",
E 5
I 5
		"!%s: gani_rx_desc_stat: slot:%d rxd0:0x%b",
E 5
		dp->name, slot, rsr, RXD0_BITS));

E 16
	if ((rsr & RXD0_OWN) != 0) {
E 22
I 22
	    dp->name, __func__, slot, rsr, RXD0_BITS, LE_32(rdp->rxd1)));
#endif
	if (rsr & RXD0_OWN) {
E 22
		/* not transmitted yet */
D 16
		return 0;
E 16
I 16
		return (0);
E 16
	}
D 22

E 22
I 22
#ifndef lint
E 22
I 17
	DPRINTF(2, (CE_CONT, "!%s: %s: slot:%d rxd0:0x%b, rxd1:0x%x",
D 22
		dp->name, __func__, slot, rsr, RXD0_BITS, LE32(rdp->rxd1)));

E 22
I 22
	    dp->name, __func__, slot, rsr, RXD0_BITS, LE_32(rdp->rxd1)));
#endif
E 22
E 17
D 16
	if ((rsr & RXD0_RES) != 0) {
		return GEM_RX_ERR;
	}
E 16
I 16
	if ((rsr & (RXD0_RES | RXD0_LS | RXD0_FS)) != (RXD0_LS | RXD0_FS)) {
D 22
		if ((rsr & RXD0_RES) != 0) {
			if ((rsr & RXD0_CRC) != 0) {
E 22
I 22
		if (rsr & RXD0_RES) {
			if (rsr & RXD0_CRC) {
E 22
				dp->stats.crc++;
			}
D 22
			if ((rsr & RXD0_RUNT) != 0) {
E 22
I 22
			if (rsr & RXD0_RUNT) {
E 22
				dp->stats.runt++;
			}
I 23
			dp->stats.errrcv++;
E 23
		}
E 16

D 16
	if ((rsr & (RXD0_LS | RXD0_FS)) != (RXD0_LS | RXD0_FS)) {
		/* received frame is too long */
		if ((rsr & RXD0_FS) != 0) {
			dp->stats.frame_too_long++;
E 16
I 16
		if ((rsr & (RXD0_LS | RXD0_FS)) != (RXD0_LS | RXD0_FS)) {
			/* received frame is too long */
D 22
			if ((rsr & RXD0_FS) != 0) {
E 22
I 22
			if (rsr & RXD0_FS) {
E 22
				dp->stats.frame_too_long++;
I 23
				dp->stats.errrcv++;
E 23
			}
E 16
		}
D 16
		return GEM_RX_ERR;
E 16
I 16
		return (GEM_RX_ERR);
E 16
	}

D 16
	len = rsr & RXD0_FRAMELEN;

	if (len < ETHERFCSL) {
		return GEM_RX_ERR;
E 16
I 16
	/* eliminate fcs */
	if ((len = rsr & RXD0_FRAMELEN) < ETHERFCSL) {
		return (GEM_RX_ERR);
E 16
	}
	len -= ETHERFCSL;

D 16
	return GEM_RX_DONE | len;
E 16
I 16
D 22
#ifdef CONFIG_VLAN
	if (((vtag = LE32(rdp->rxd1)) & RXD1_TAVA) != 0) {
E 22
I 22
#ifdef GEM_CONFIG_VLAN_HW
	if ((vtag = LE_32(rdp->rxd1)) & RXD1_TAVA) {
E 22
		/* fix vlan tag format */
D 17
		flags |= ((vtag & 0x00ff) << (GEM_RX_VTAG_SHIFT + 8))
		       | ((vtag & 0xff00) << (GEM_RX_VTAG_SHIFT - 8));
E 17
I 17
D 28
		flags |= BSWAP_16(vtag & 0xffff) << GEM_RX_VTAG_SHIFT;
E 28
I 28
		flags |= ((uint64_t)BSWAP_16(vtag & 0xffff))
		    << GEM_RX_VTAG_SHIFT;
E 28
		DPRINTF(2, (CE_CONT, "%s: %s: vtag detected %llx",
D 22
			dp->name, __func__, flags));
E 22
I 22
		    dp->name, __func__, (unsigned long long)flags));
E 22
E 17
	}
D 22
#endif
E 22
#ifdef GEM_CONFIG_CKSUM_OFFLOAD
	if ((rsr & (RXD0_PID | RXD0_TCPF)) == RXD0_PID_TCP) {
		flags |= GEM_RX_CKSUM_TCP;
D 22
	}
	else if ((rsr & (RXD0_PID | RXD0_UDPF)) == RXD0_PID_UDP) {
E 22
I 22
	} else if ((rsr & (RXD0_PID | RXD0_UDPF)) == RXD0_PID_UDP) {
E 22
		flags |= GEM_RX_CKSUM_UDP;
	}
D 31
	if ((rsr & RXD0_PID) != RXD0_PID_NONIP && (rsr & RXD0_IPF) == 0) {
		flags |= GEM_RX_CKSUM_IPv4;
E 31
I 31
	if (lp->new_cksum) {
		uint32_t	rsr1;
		rsr1 = rdp->rxd1;
		rsr1 = LE_32(rsr1);

		if ((rsr & (RXD0_PID | RXD0_IPF)) == RXD0_PID_IP_NEW &&
		    (rsr1 & RXD1_IPv4)) {
			flags |= GEM_RX_CKSUM_IPv4;
		}
	} else {
		if ((rsr & (RXD0_PID | RXD0_IPF)) == RXD0_PID_IP) {
			flags |= GEM_RX_CKSUM_IPv4;
		}
E 31
	}
D 22
#endif
E 22
I 22
#endif /* GEM_CONFIG_CKSUM_OFFLOAD */
#endif /* GEM_CONFIG_VLAN_HW */
#ifdef notdef
{
	int	i;
	uint8_t	*bp = (uint8_t *)&dp->rx_buf_head->rxb_buf[0];
E 22
I 17

D 22
	if (0) {
		int	i;
D 19
		uint8_t	*bp = &dp->rx_buf_head->rxb_buf[0];
E 19
I 19
		uint8_t	*bp = (uint8_t *) &dp->rx_buf_head->rxb_buf[0];
E 22
I 22
	cmn_err(CE_CONT, "!%s: len:%d", dp->name, len);
E 22
E 19

D 22
		cmn_err(CE_CONT, "!%s: len:%d", dp->name, len);

		for (i = 0; i < len; i += 10) {
			cmn_err(CE_CONT,
			"!%02x %02x %02x %02x %02x %02x %02x %02x %02x %02x",
			bp[0], bp[1], bp[2], bp[3], bp[4],
			bp[5], bp[6], bp[7], bp[8], bp[9]);
			bp += 10;
		}
E 22
I 22
	for (i = 0; i < len; i += 10) {
		cmn_err(CE_CONT,
		    "!%02x %02x %02x %02x %02x"
		    " %02x %02x %02x %02x %02x",
		    bp[0], bp[1], bp[2], bp[3], bp[4],
		    bp[5], bp[6], bp[7], bp[8], bp[9]);
		bp += 10;
E 22
	}
D 22

E 22
I 22
}
#endif
E 22
E 17
	return (flags | GEM_RX_DONE | len);
E 16
}

static void
gani_tx_desc_init(struct gem_dev *dp, int slot)
{
D 16
	struct tx_desc	*tdp;
	struct gani_dev	*lp = (struct gani_dev *)dp->private;

	tdp = &((struct tx_desc *)dp->tx_ring)[slot];

D 5
	tdp->txd0 = (slot == TX_RING_SIZE - 1) ? TXD0_EOR : 0;
E 5
I 5
D 9
	tdp->txd0 = LE32((slot == TX_RING_SIZE - 1) ? TXD0_EOR : 0);
E 9
I 9
	ddi_put32(dp->desc_acc_handle,
		&tdp->txd0, (slot == TX_RING_SIZE - 1) ? TXD0_EOR : 0);
E 9
E 5
D 4
#ifdef IOCACHE
E 4
I 4

E 4
	ddi_dma_sync(dp->desc_dma_handle,
		(off_t)(((caddr_t)tdp) - dp->rx_ring),
		sizeof(struct tx_desc), DDI_DMA_SYNC_FORDEV);
E 16
I 16
D 22
	((struct tx_desc *) dp->tx_ring)[slot].txd0 = 0;
E 22
I 22
	TXDESC(dp->tx_ring)[slot].txd0 = 0;
E 22
E 16
D 4
#endif
E 4
}

static void
gani_rx_desc_init(struct gem_dev *dp, int slot)
{
D 16
	struct rx_desc	*rdp;
	struct gani_dev	*lp = (struct gani_dev *)dp->private;

	rdp = &((struct rx_desc *)dp->rx_ring)[slot];

D 5
	rdp->rxd0 = (slot == RX_RING_SIZE - 1) ? RXD0_EOR : 0;
E 5
I 5
D 9
	rdp->rxd0 = LE32((slot == RX_RING_SIZE - 1) ? RXD0_EOR : 0);
E 9
I 9
	ddi_put32(dp->desc_acc_handle,
		&rdp->rxd0, (slot == RX_RING_SIZE - 1) ? RXD0_EOR : 0);
E 9
E 5
D 4
#ifdef IOCACHE
E 4
I 4

E 4
	ddi_dma_sync(dp->desc_dma_handle,
		(off_t)(((caddr_t)rdp) - dp->rx_ring),
		sizeof(struct rx_desc), DDI_DMA_SYNC_FORDEV);
E 16
I 16
D 22
	((struct rx_desc *) dp->rx_ring)[slot].rxd0 = 0;
E 22
I 22
	RXDESC(dp->rx_ring)[slot].rxd0 = 0;
E 22
E 16
D 4
#endif
E 4
}

D 5
static void
gani_tx_desc_clean(struct gem_dev *dp, int slot)
{
	struct tx_desc	*tdp;
	struct gani_dev	*lp = (struct gani_dev *)dp->private;

	tdp = &((struct tx_desc *)dp->tx_ring)[slot];

	tdp->txd0 &= TXD0_EOR;
D 4
#ifdef IOCACHE
E 4
I 4

E 4
	ddi_dma_sync(dp->desc_dma_handle,
		(off_t)(((caddr_t)tdp) - dp->rx_ring),
		sizeof(struct tx_desc), DDI_DMA_SYNC_FORDEV);
D 4
#endif
E 4
}

static void
gani_rx_desc_clean(struct gem_dev *dp, int slot)
{
	struct rx_desc	*rdp;
	struct gani_dev	*lp = (struct gani_dev *)dp->private;

	rdp = &((struct rx_desc *)dp->rx_ring)[slot];

	rdp->rxd0 &= RXD0_EOR;
D 4
#ifdef IOCACHE
E 4
I 4

E 4
	ddi_dma_sync(dp->desc_dma_handle,
		(off_t)(((caddr_t)rdp) - dp->rx_ring),
		sizeof(struct rx_desc), DDI_DMA_SYNC_FORDEV);
D 4
#endif
E 4
}

E 5
/*
 * Device depend interrupt handler
 */
I 3
D 4
#ifdef OPT_TX_INTR
static
uint_t gani_update_imr(struct gem_dev *dp)
{
	uint_t		ret;
	struct gani_dev	*lp = (struct gani_dev *)dp->private;

	ret = DDI_INTR_UNCLAIMED;

	mutex_enter(&dp->intrlock);
	mutex_enter(&dp->xmitlock);

	if (lp->imr_change_req) {
		if ((dp->misc_flag & GEM_NOINTR) == 0 && lp->imr_hw != 0 &&
		     lp->imr_hw != lp->imr) {
			lp->imr_hw = lp->imr;
			OUTW(dp, IMR, lp->imr_hw);
		}
		lp->imr_change_req = FALSE;
		ret = DDI_INTR_CLAIMED;
	}

	mutex_exit(&dp->xmitlock);
	mutex_exit(&dp->intrlock);

	return ret;
}
#endif /* OPT_TX_INTR */

E 4
E 3
D 22
static u_int
E 22
I 22
static uint_t
E 22
gani_interrupt(struct gem_dev *dp)
{
I 16
	int		i;
	int		nread;
D 22
	boolean_t	rdu;
E 22
E 16
	uint16_t	isr;
I 23
	uint16_t	bogus_isr;
E 23
I 5
D 6
	uint16_t	reg;
E 6
I 6
D 16
	uint16_t	isr_raw;
E 16
I 16
D 22
	uint16_t	isr_org;
E 16
E 6
E 5
D 9
	int		loop;
E 9
I 9
D 10
	uint16_t	new_rok;
	clock_t		now;
	int		n;
E 10
E 9
	u_int		restart_tx = 0;
	struct gani_dev	*lp = (struct gani_dev *)dp->private;
E 22
I 22
	uint16_t	imr_hw;
	uint_t		restart_tx = 0;
	struct gani_dev	*lp = dp->private;
	uint_t		tx_ring_size = dp->gc.gc_tx_ring_size;
E 22

I 5
D 6
	IO_BARRIER_ENTER(lp);
E 5
	isr = INW(dp, ISR);
I 5
	IO_BARRIER_EXIT(lp);
E 6
I 6
D 16
	isr_raw = INW(dp, ISR);
I 10
	isr = isr_raw & lp->imr_hw;
E 16
I 16
D 22
	isr_org = isr = INW(dp, ISR);
E 22
I 22
	isr = INW(dp, ISR);
I 23
	bogus_isr = lp->isr_pended;
	lp->isr_pended = 0;
E 23
E 22
E 16
E 10
E 6
E 5

D 14
	DPRINTF(10, (CE_CONT,"!%s: time:%d gani_interrupt: isr:%b",
E 14
I 14
D 22
	DPRINTF(4, (CE_CONT,"!%s: time:%d gani_interrupt: isr:%b",
E 14
		dp->name, ddi_get_lbolt(), isr, INTR_BITS));
E 22
I 22
D 23
	DPRINTF(2, (CE_CONT, "!%s: time:%ld gani_interrupt: isr:%b",
E 23
I 23
D 28
	DPRINTF(4, (CE_CONT, "!%s: time:%ld gani_interrupt: isr:%b",
E 23
	    dp->name, ddi_get_lbolt(), isr, INTR_BITS));
E 28
I 28
	DPRINTF(4, (CE_CONT, "!%s: time:%ld %s: isr:%b",
	    dp->name, ddi_get_lbolt(), __func__, isr, INTR_BITS));
E 28
E 22

I 22
	imr_hw = lp->imr;
E 22
D 6
	if ((isr & lp->imr_hw) == 0) {
E 6
I 6
D 9
	mutex_enter(&lp->reglock);
E 9
D 10
	isr = isr_raw & lp->imr_hw;
E 10
D 16
	if (isr == 0) {
E 16
I 16
D 17
	if ((isr & lp->imr_hw) == 0) {
E 17
I 17
D 23
	if ((isr & lp->imr) == 0) {
E 23
I 23
	if (((isr | bogus_isr) & lp->imr) == 0) {
E 23
E 17
E 16
E 6
		/* not for us */
I 6
D 9
		mutex_exit(&lp->reglock);
E 9
E 6
D 17
		return DDI_INTR_UNCLAIMED;
E 17
I 17
		return (DDI_INTR_UNCLAIMED);
E 17
	}

D 22
	DPRINTF(2, (CE_CONT,"!%s: time:%d gani_interrupt: isr:%b imr:%b",
		dp->name, ddi_get_lbolt(), isr, INTR_BITS,
		INW(dp, IMR), INTR_BITS));
D 17

E 17
I 17
#ifdef CONFIG_MSI
E 17
I 3
	/* disable interrupts */
I 5
D 6
	IO_BARRIER_ENTER(lp);
E 5
	OUTW(dp, IMR, 0);
D 4

E 4
I 4
D 5
#ifdef MAP_MEM
	INW(dp, IMR);	/* flush write buffer */
#endif
E 5
I 5
	IO_BARRIER_EXIT(lp);
E 6
I 6
	OUTW(dp, IMR, lp->imr_hw = 0);
D 9
	mutex_exit(&lp->reglock);
E 9
E 6
D 17

E 17
I 17
#endif
E 22
I 22
D 28
	DPRINTF(2, (CE_CONT, "!%s: time:%ld gani_interrupt: isr:%b imr:%b",
	    dp->name, ddi_get_lbolt(), isr, INTR_BITS,
E 28
I 28
	DPRINTF(2, (CE_CONT, "!%s: time:%ld %s: isr:%b imr:%b",
	    dp->name, ddi_get_lbolt(), __func__, isr, INTR_BITS,
E 28
	    INW(dp, IMR), INTR_BITS));

D 28
	if (lp->msi) {
E 28
I 28
D 29
	if (lp->pcie_cap) {
E 28
		/* disable interrupts */
		OUTW(dp, IMR, imr_hw = 0);
		FLSHW(dp, IMR);
	}

E 29
E 22
E 17
E 5
E 4
E 3
D 16
	if (!dp->nic_active) {
E 16
I 16
D 28
	if (!dp->mac_active) {
E 28
I 28
	if (!IS_MAC_ONLINE(dp)) {
E 28
E 16
D 22
		/* inhibit interrupt */
		lp->imr = 0;
E 22
I 22
		/* disable further interrupts */
		OUTW(dp, IMR, 0);
		FLSHW(dp, IMR);
E 22
D 3
		OUTW(dp, IMR, lp->imr_hw = lp->imr);
E 3
I 3
D 6
		lp->imr_hw = 0;
E 6

E 3
		/* ack to all interrupts */
I 5
D 6
		IO_BARRIER_ENTER(lp);
E 6
E 5
		OUTW(dp, ISR, 0xffff);
I 5
		FLSHW(dp, ISR);
D 6
		IO_BARRIER_EXIT(lp);
E 6
E 5
D 17
		return DDI_INTR_CLAIMED;
E 17
I 17
		return (DDI_INTR_CLAIMED);
E 17
	}

I 22
D 28
#ifdef CONFIG_OPT_TPPOLL
#define	POLLED_INTRS	(INTR_ROK | INTR_TDU | INTR_TOK)
#else
#define	POLLED_INTRS	(INTR_ROK | INTR_TOK)
#endif
	isr &= lp->imr | POLLED_INTRS;

E 28
E 22
D 9
	loop = 100;
E 9
I 9
	/* clear interrupt sources explicitly */
D 16
	OUTW(dp, ISR, isr_raw);
E 16
I 16
D 23
	/* XXX : don't clear RxFIFO Overflow bit for 8168 */
E 23
D 22
	OUTW(dp, ISR, isr & ~INTR_FOVW);
E 22
I 22
D 28
	if (GANI_PCIE_GIGA(lp->chip->type)) {
E 28
I 28
D 29
	if (GANI_PCIE_GIGA(lp)) {
E 28
I 23
		/* don't clear RxFIFO Overflow bit for 8168 */
E 23
		OUTW(dp, ISR, lp->imr & ~INTR_FOVW);
I 23
D 28
	} else if (GANI_PCI(lp->chip->type) && (isr & INTR_FOVW)) {
		OUTW(dp, ISR, isr | INTR_RDU);
E 28
E 23
	} else {
		OUTW(dp, ISR, isr);
E 29
I 29
	if (lp->pcie_cap) {
		/* disable interrupts */
		OUTW(dp, IMR, imr_hw = 0);
E 29
	}
I 29
	OUTW(dp, ISR, isr);

E 29
E 22
E 16
E 9
I 4
D 28

E 4
D 9
	do {
I 4
D 6
		if (isr == 0xffff) {
E 6
I 6
		if (isr_raw == 0xffff) {
E 6
			break;
		}
E 9
I 9
D 16
#ifdef CONFIG_POLLING
E 16
I 16
D 22
	isr &= lp->imr;

E 22
I 17
	/* PCI read/write barrier to make interrupt state stable. */
	/* XXX - it costs 5%-10% of cpu utilazation at 1.8GHz AMD athlon */
	FLSHW(dp, ISR);

E 28
E 17
D 22
#ifdef GEM_CONFIG_POLLING
E 22
I 22
#ifdef CONFIG_POLLING
E 22
E 16
D 10
	now = ddi_get_lbolt();
	if (now != lp->rx_last_time) {
		/*
		 * It's time to check tx and rx statistics
		 */
		mutex_enter(&dp->xmitlock);
		if (now == lp->rx_last_time + 1 &&
		    lp->tx_pkt_cnt + lp->rx_pkt_cnt > lp->poll_pkt_hiwat) {
			/* go to the polling mode */
			if (!GANI_IS_POLLING(lp)) {
				lp->imr &= ~INTR_ROK;
				OUTL(dp, TimerInt, lp->poll_interval);
			}
E 10
I 10
	if (dp->poll_interval != lp->last_poll_interval) {
D 22
		if (dp->poll_interval != 0) {
E 22
I 22
		if (dp->poll_interval) {
E 22
			/* polling mode */
D 16
			mutex_enter(&dp->xmitlock);
D 13
			lp->imr &= ~(INTR_ROK | INTR_FOVW | INTR_RDU);
E 13
I 13
			lp->imr &= ~INTR_ROK;
E 13
			mutex_exit(&dp->xmitlock);
E 16
I 16
D 22
			lp->imr_disabled |= INTR_ROK | INTR_TOK | INTR_TDU;
#  ifdef CONFIG_TX_COALESCE
			dp->tx_coalesce = B_TRUE;
#  endif
E 16
			OUTL(dp, TimerInt,
D 16
				((lp->cfg2 & CFG2_PCICLKF) != 0)
E 16
I 16
				lp->busclk == BUSCLK_PCIE
					? dp->poll_interval * 125
				: lp->busclk == BUSCLK_PCI66
E 16
					? dp->poll_interval * 66
D 16
					: dp->poll_interval * 33);
E 16
I 16
				: dp->poll_interval * 33);
E 22
I 22
D 28
			lp->imr &= ~POLLED_INTRS;
E 28
I 28
			lp->imr &= ~(INTR_ROK | INTR_TDU | INTR_TOK);
E 28

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
D 28
			OUTL(dp, TimerInt, i);
E 28

E 22
E 16
E 10
E 9
D 17

E 4
D 3
		if ((dp->misc_flag & GEM_NOINTR) == 0 &&
		    (lp->imr_hw & ~lp->imr) != 0) {
			mutex_enter(&dp->xmitlock);
			if ((lp->imr_hw & ~lp->imr) != 0) {
				/* need to downgrade interrput mask */
				OUTW(dp, IMR, lp->imr_hw = lp->imr);
			}
			mutex_exit(&dp->xmitlock);
		}
E 3
D 9
		/* clear interrupt sources explicitly */
I 5
D 6
		IO_BARRIER_ENTER(lp);
E 5
		OUTW(dp, ISR, isr);
E 6
I 6
		OUTW(dp, ISR, isr_raw);
E 6
I 5
		FLSHW(dp, ISR);
D 6
		IO_BARRIER_EXIT(lp);
E 6

E 5
D 6
		isr &= lp->imr_hw;

E 6
		if ((isr & INTR_PUN) != 0) {
			/*
			 * Link or PHY status has changed
			 */
			DPRINTF(2, (CE_CONT, "!%s: isr:%b",
				dp->name, isr, INTR_BITS));
E 9
I 9
D 10
			/* pretend as we were interrupted from polling timer */
			isr |= INTR_TimeOut;
E 10
I 10
			if (lp->last_poll_interval == 0) {
				/*
				 * To schedule the next timer interrupt,
				 * we pretend as we were interrupted from
				 * polling timer
				 */
				isr |= INTR_TimeOut;
			}
E 17
I 17
			/*
			 * To schedule the next timer interrupt correctly,
D 31
			 * we pretend as we were interrupted from
			 * polling timer
E 31
I 31
			 * we need to reset PCI clock counter. So, we pretend
			 * as we were interrupted from polling timer.
E 31
			 */
			isr |= INTR_TimeOut;
E 17
E 10
E 9
D 22
		}
D 9

		if ((isr & (INTR_ROK | INTR_RER | INTR_FOVW | INTR_RDU)) != 0) {
			if ((isr & (INTR_FOVW | INTR_RDU)) != 0) {
				dp->stats.overflow++;
				dp->stats.errrcv++;
E 9
I 9
		else {
E 22
I 22

			DPRINTF(3, (CE_CONT,
			    "%s: poll_interval:%d", dp->name, i));
		} else {
E 22
D 10
			/* go to the normal mode */
			if (GANI_IS_POLLING(lp)) {
				lp->imr |= INTR_ROK;
				OUTL(dp, TimerInt, 0);
E 9
			}
E 10
I 10
D 28
			/* normal mode */
D 16
			mutex_enter(&dp->xmitlock);
D 13
			lp->imr |= INTR_ROK | INTR_FOVW | INTR_RDU;
E 13
I 13
			lp->imr |= INTR_ROK;
E 13
			mutex_exit(&dp->xmitlock);
E 16
I 16
D 22
			lp->imr_disabled &= ~(INTR_ROK | INTR_TOK | INTR_TDU);
#  ifdef CONFIG_TX_COALESCE
			dp->tx_coalesce = B_FALSE;
#  endif
E 22
I 22
			lp->imr |= POLLED_INTRS;

E 22
E 16
			OUTL(dp, TimerInt, 0);
E 28
I 28
			/* normal mode, restore interrupt mask */
			lp->imr |= INTR_ROK | INTR_TOK;
			if (GANI_PCIE(lp)) {
				lp->imr |= INTR_TDU;
			}
			i = 0;
E 28
E 10
D 9
			gem_receive(dp);
E 9
		}
I 28
		OUTL(dp, TimerInt, i);
E 28
I 13

		lp->last_poll_interval = dp->poll_interval;
E 13
D 10

D 4
#if defined(TX_DELAYED_INTR) && DEBUG_LEVEL > 0
		if (lp->tx_delayed_intr) {
			if ((isr & INTR_TimeOut) != 0) {
				if (gem_tx_done(dp)) {
					restart_tx = INTR_RESTART_TX;
				}
				mutex_enter(&dp->xmitlock);
				if (dp->tx_desc_intr - dp->tx_desc_head >= 0) {
					gani_sched_timer(dp);
				}
				mutex_exit(&dp->xmitlock);
E 4
I 4
D 6
		if ((isr &
		    (INTR_TDU | INTR_TER | INTR_TimeOut | INTR_SWInt)) != 0) {
E 6
I 6
D 9
		if ((isr & (INTR_TDU | INTR_TER | INTR_TOK
#ifdef TX_DELAYED_INTR
				| INTR_TimeOut
#endif
				)) != 0) {
E 9
I 9
		/* reset tx and rx packet counter */
		lp->rx_pkt_cnt  = 0;
		lp->rx_intr_cnt = 0;
		lp->tx_pkt_cnt  = 0;
		mutex_exit(&dp->xmitlock);
E 10
	}
D 10
	lp->rx_last_time = now;
E 10
I 10
D 13
	lp->last_poll_interval = dp->poll_interval;
E 13
E 10
E 9

E 6
D 9
			/* Need to kick potentially blocked down stream */
I 6
			if (gem_tx_done(dp)) {
				restart_tx |= INTR_RESTART_TX;
			}
E 6
I 5
#ifndef OPT_TDU_INTR
			if ((isr & INTR_TDU) != 0) {
D 6
				/* ensure there is no garbage in tx queue */
				restart_tx = gem_tx_done(dp);
E 6
				mutex_enter(&dp->xmitlock);
				if (lp->tx_list_len > 0) {
					/* tx queue may hang, restart tx here */
					OUTB(dp, TPPoll, TPPoll_NPQ);
				}
				mutex_exit(&dp->xmitlock);
			}
E 9
I 9
D 22
	if ((isr & INTR_TimeOut) != 0) {
E 22
I 22
	if (isr & INTR_TimeOut) {
E 22
		/*
		 * Reset PCI clock counter to schedule the next polling
		 * timer interrupt.
		 */
		OUTL(dp, TCTR, 0);
D 22

D 16
		/* force to process ROK and TDU */
		isr |= INTR_ROK | INTR_TDU;
E 16
I 16
		/* force to process ROK and TOK */
		isr |= INTR_ROK | INTR_TOK;
E 22
E 16
	}
E 9
D 6
			else
E 6
D 10
#endif
E 10
I 10
D 16
#endif /* CONFIG_POLLING */
E 16
I 16
D 22
#endif /* GEM_CONFIG_POLLING */
E 22
I 22
#endif /* CONFIG_POLLING */
E 22
E 16
E 10
E 5
D 6
			if (dp->tx_blocked) {
D 5
				restart_tx = INTR_RESTART_TX;
E 5
I 5
				restart_tx = gem_tx_done(dp);
E 5
E 4
			}
I 5

E 6
E 5
D 4
		} else
#endif
		if ((isr & (INTR_TDU | INTR_TOK | INTR_TER)) != 0) {
			if (gem_tx_done(dp)) {
				restart_tx = INTR_RESTART_TX;;
			}
E 4
I 3
D 9
			if ((isr & INTR_TER) != 0) {
				cmn_err(CE_WARN, "%s: Tx error, isr:%b",
					dp->name, isr, INTR_BITS);
			}
E 9
I 9

I 28
	/* PCI read/write barrier to ensure the interrupt is ack'ed. */
	/* XXX - it costs 5%-10% of cpu utilazation on 1.8GHz AMD athlon */
	FLSHW(dp, ISR);

E 28
I 16
D 17
	/* load/store barrier for interrupt state */
	FLSHW(dp, ISR);

E 17
E 16
D 22
	if ((isr & INTR_PUN) != 0) {
E 22
I 22
	if (isr & INTR_PUN) {
E 22
		/*
		 * Link or PHY status has changed
		 */
D 10
		DPRINTF(0, (CE_CONT, "!%s: isr:%b",
			dp->name, isr, INTR_BITS));
E 10
I 10
D 14
		DPRINTF(0, (CE_CONT, "!%s: isr:%b", dp->name, isr, INTR_BITS));
E 14
I 14
D 16
		DPRINTF(4, (CE_CONT, "!%s: isr:%b", dp->name, isr, INTR_BITS));
E 16
I 16
D 17
		DPRINTF(0, (CE_CONT, "!%s: isr:%b", dp->name, isr, INTR_BITS));
E 17
I 17
D 22
		DPRINTF(2, (CE_CONT, "!%s: isr:%b", dp->name, isr, INTR_BITS));
E 22
I 22
D 28
		DPRINTF(0, (CE_CONT, "!%s: isr:%b", dp->name, isr, INTR_BITS));
E 28
I 28
		DPRINTF(1, (CE_CONT, "!%s: isr:%b", dp->name, isr, INTR_BITS));
#ifdef GEM3
		gem_mii_link_check(dp);
#else
E 28
E 22
E 17
		if (gem_mii_link_check(dp)) {
			restart_tx |= INTR_RESTART_TX;
		}
I 28
#endif
E 28
E 16
E 14
E 10
	}

D 16
	if ((isr & (INTR_ROK | INTR_RER | INTR_FOVW | INTR_RDU)) != 0) {
I 10
		(void) gem_receive(dp);
		if ((isr & INTR_FOVW) != 0) {
E 16
I 16
D 22
rx_again:
	if ((isr & INTR_FOVW) != 0) {
		int		wait_time;
		uint16_t	isr_tmp;
		extern int	gem_speed_value[];

		/*
		 * Need to drain rx packets which still are in rx fifo
		 */
		wait_time = dp->mtu / 128;

		for (i = 0; i < 100; i++) {
			drv_usecwait(wait_time);

			isr_tmp = INW(dp, ISR);
			isr |= isr_tmp & (INTR_ROK | INTR_FOVW);

			if ((isr_tmp & INTR_ROK) == 0) {
				DPRINTF(0, (CE_CONT,
				"!%s: rxfifo overflow: %d packets salvaged",
					dp->name, i));
				break;
			}
			OUTW(dp, ISR, INTR_ROK);
			FLSHW(dp, ISR);
E 22
I 22
D 29
	if (isr & INTR_FOVW) {
D 23
		if (lp->chip->type == R8168_CFG_METHOD_1) {
E 23
I 23
		if (lp->chip->type == R8168_1 /* RTL8168B rev.B */) {
E 23
			lp->need_to_reset = B_TRUE;
E 22
		}
D 22
		if (i == 100) {
E 16
			cmn_err(CE_WARN,
D 16
				"!%s: gani_interrupt: rx fifo overflow, isr %b",
				dp->name, isr, INTR_BITS);
E 16
I 16
			"!%s: %s: rx fifo overflow, rxfifo drain timeout",
				dp->name, __func__);
		}
E 22
I 22
		dp->stats.overflow++;
		dp->stats.errrcv++;
E 22
	}

E 29
I 28
#ifdef GEM3
	if (isr & INTR_TER) {
I 29
		cmn_err(CE_WARN, "!%s: Tx error, isr:%b",
		    dp->name, isr, INTR_BITS);
E 29
		lp->need_to_reset = B_TRUE;
	} else if ((GANI_PCIE(lp) && (isr & INTR_TDU)) ||
D 29
	    (isr & INTR_TOK) &&  dp->tx_free_bufs < dp->gc.gc_tx_buf_size / 8) {
E 29
I 29
D 30
	    (isr & INTR_TOK) && dp->tx_free_bufs < dp->gc.gc_tx_buf_size / 8) {
E 30
I 30
D 31
	    (isr & INTR_TOK) && dp->tx_free_bufs < dp->gc.gc_tx_buf_size / 1) {
E 30
E 29
		/* Need to kick potentially blocked down stream */
E 31
I 31
	    (isr & INTR_TOK) && dp->tx_free_bufs < dp->gc.gc_tx_buf_size / 8) {
		/* Need to kick potentially blocked downstream */
E 31
		gem_tx_done(dp);
D 29
		if (isr & INTR_TER) {
			cmn_err(CE_WARN, "!%s: Tx error, isr:%b",
			    dp->name, isr, INTR_BITS);
			lp->need_to_reset = B_TRUE;
		}
E 29
	}
#endif /* !GEM3 */

E 28
D 22
	if ((isr & (INTR_ROK | INTR_RER)) != 0) {
E 22
I 22
D 23
	if (isr & (INTR_ROK | INTR_RER | INTR_FOVW)) {
E 23
I 23
	if (isr & (INTR_ROK | INTR_RER | INTR_RDU | INTR_FOVW)) {
I 29
		if (isr & INTR_FOVW) {
			if (lp->chip->type == R8168_1 /* RTL8168B rev.B */) {
				lp->need_to_reset = B_TRUE;
				lp->imr &= ~INTR_FOVW;
			}
			dp->stats.overflow++;
			dp->stats.errrcv++;
		}
E 29
E 23
E 22
		nread = gem_receive(dp);
D 28
		lp->rx_pkt_cnt += nread;
E 28
D 22
		rdu = B_FALSE;
E 22
#ifdef TEST_FOVW
I 28
		lp->rx_pkt_cnt += nread;
E 28
		if ((lp->rx_pkt_cnt % 100000) == 99999) {
			isr |= INTR_FOVW;
		}
#endif
D 22
		if ((isr & (INTR_FOVW | INTR_RDU)) == (INTR_FOVW | INTR_RDU)) {
			if (nread > 0) {
				goto rx_again;
			}
E 22
I 22
D 29
#ifdef NEVER
		if (isr & INTR_RER) {
			cmn_err(CE_WARN, "!%s: Rx error, isr:%b",
			    dp->name, isr, INTR_BITS);
			lp->need_to_reset = B_TRUE;
E 22
		}
I 22
#endif
E 22
	}

D 22
	if ((isr & INTR_RDU) != 0) {
		if (dp->poll_interval != 0 && dp->poll_pkt_delay > 1 &&
		    lp->busclk >= BUSCLK_PCI66) {
E 22
I 22
	if (isr & INTR_RDU) {
E 29
#ifdef CONFIG_POLLING
D 29
		if (dp->poll_interval && dp->poll_pkt_delay > 1 &&
D 28
		    GANI_PCIE(lp->chip->type)) {
E 28
I 28
		    GANI_PCIE(lp)) {
E 28
E 22
E 16
E 10
D 11

E 11
D 10
		if ((isr & (INTR_FOVW | INTR_RDU)) != 0) {
			dp->stats.overflow++;
			dp->stats.errrcv++;
E 10
I 10
			/*
D 16
			 * we should clear rx fifo
			 * and increase rxdma size;
E 16
I 16
			 * current polling interval is too long.
			 * recompute it.
E 16
			 */
D 16
			dp->rxmaxdma = min(dp->rxmaxdma + 256, 1024);
			lp->need_to_reset = TRUE;
I 13
			dp->stats.overflow++;
E 16
I 16
			dp->poll_pkt_delay--;
D 22
			DPRINTF(0, (CE_CONT,
				"!%s: pkt-delay decreased to %d",
				dp->name, dp->poll_pkt_delay));
E 22
I 22
			DPRINTF(1, (CE_CONT,
			    "!%s: pkt-delay decreased to %d",
			    dp->name, dp->poll_pkt_delay));
E 29
I 29
		if (isr & INTR_RDU) {
			if (dp->poll_interval && dp->poll_pkt_delay > 1 &&
			    GANI_PCIE(lp)) {
				/*
				 * current polling interval is too long.
				 * recompute it.
				 */
				dp->poll_pkt_delay--;
				DPRINTF(-1, (CE_CONT,
				    "!%s: pkt-delay decreased to %d",
				    dp->name, dp->poll_pkt_delay));
			}
			dp->stats.errrcv++;
			dp->stats.norcvbuf++;
E 29
E 22
E 16
E 13
E 10
E 9
E 3
		}
I 22
#endif /* CONFIG_POLLING */
D 29
		dp->stats.errrcv++;
E 22
I 16
		dp->stats.norcvbuf++;
E 29
	}
I 29

E 29
E 16
D 10

D 9
		if ((isr & INTR_SERR) != 0) {
D 5
			cmn_err(CE_WARN, "%s: unexpected interrupt: isr:%b",
E 5
I 5
			cmn_err(
#ifdef notef /* DEBUG_LEVEL */
				CE_PANIC,
#else
				CE_WARN,
#endif
				"%s: unexpected interrupt: isr:%b",
E 5
				dp->name, isr, INTR_BITS);
			lp->need_to_reset = TRUE;
E 9
I 9
		n = gem_receive(dp);

#ifdef CONFIG_POLLING
		/* update rx statistics for polling */
		lp->rx_pkt_cnt += n;
		if (n > 0) {
			/* count number of valid rx interrupts */
			lp->rx_intr_cnt++;
E 10
I 10
D 13
#ifdef notdef
		if ((isr & INTR_RDU) != 0) {
			if (dp->poll_interval != 0 && dp->poll_pkt_delay > 0) {
E 13
I 13
D 28

D 16
		if ((isr & INTR_RDU) != 0 && dp->poll_interval != 0) {
E 16
I 16
D 22
	if ((isr & INTR_FOVW) != 0) {
		DPRINTF(2, (CE_WARN, "!%s: %s: rx fifo overflow, isr %b",
			dp->name, __func__, isr, INTR_BITS));
E 22
I 22
	if (isr & (INTR_TER | INTR_TOK | INTR_TDU)) {
I 23
#ifdef CONFIG_OPT_TPPOLL
		if (isr & INTR_TDU) {
			mutex_enter(&dp->xmitlock);
			if (lp->tx_running) {
				lp->tx_running = B_FALSE;
			} else {
				/* hardware error */
				lp->need_to_reset = B_TRUE;
			}
			mutex_exit(&dp->xmitlock);
		}
#endif /* CONFIG_OPT_TPPOLL */
E 23
E 22

E 28
I 28
#ifndef GEM3
	if (isr & INTR_TER) {
I 29
		cmn_err(CE_WARN, "!%s: Tx error, isr:%b",
		    dp->name, isr, INTR_BITS);
E 29
		lp->need_to_reset = B_TRUE;
	} else if ((GANI_PCIE(lp) && (isr & INTR_TDU)) ||
	    (isr & INTR_TOK)) {
E 28
D 22
		dp->stats.overflow++;

		if ((isr & INTR_RDU) == 0) {
E 16
			/*
D 16
			 * current polling interval is too long. recompute it.
E 16
I 16
			 * we should increase rxdma size;
E 16
			 */
D 16
			if (dp->poll_pkt_delay > 0) {
E 13
				dp->poll_pkt_delay--;
				DPRINTF(0, (CE_CONT,
					"!%s: pkt-delay decreased to %d",
					dp->name, dp->poll_pkt_delay));
			}
I 13
			dp->stats.norcvbuf++;
E 16
I 16
			dp->rxmaxdma = min(dp->rxmaxdma + 256, 2000);
E 16
E 13
E 10
E 9
		}
I 16

		/* To recover from rx fifo overflow, we must reset the nic  */
		lp->need_to_reset = B_TRUE;
E 16
I 9
D 13
#endif
E 13
	}
E 9

D 9
		loop--;
E 9
I 9
D 16
	if ((isr & (INTR_TDU | INTR_TER | INTR_TOK)) != 0) {
E 16
I 16
	if ((isr & (INTR_TER | INTR_TOK)) != 0) {
E 16
E 9
I 4

E 22
I 5
D 6
		IO_BARRIER_ENTER(lp);
E 5
E 4
		isr = INW(dp, ISR);
I 5
		IO_BARRIER_EXIT(lp);
E 5
	 } while ((isr & lp->imr_hw) != 0 && loop > 0);
E 6
I 6
D 9
		isr_raw = INW(dp, ISR);
E 9
I 9
		/* Need to kick potentially blocked down stream */
		if (gem_tx_done(dp)) {
			restart_tx |= INTR_RESTART_TX;
		}
E 9
E 6
D 10

I 6
D 9
		mutex_enter(&lp->reglock);
	 	isr = isr_raw & lp->imr;
		mutex_exit(&lp->reglock);
	 } while (isr != 0 && loop > 0);
E 9
I 9
		if ((isr & INTR_TDU) != 0) {
E 10
I 10
D 16
#ifdef CONFIG_POLLING
		if ((isr & INTR_TimeOut) != 0 && lp->tx_list_len != 0) {
E 10
			/* force to load valid tx descriptors to the nic */
D 10
			if (lp->tx_list_len != 0) {
				OUTB(dp, TPPoll, TPPoll_NPQ);
			}
E 10
I 10
			OUTB(dp, TPPoll, TPPoll_NPQ);
E 10
		}
E 9
D 10

E 10
I 10
#endif
E 16
I 16
D 22
#if DEBUG_LEVEL > 0
E 16
E 10
E 6
D 9
	if (loop <= 0) {
		cmn_err(CE_WARN, "%s: maxmum interrupt loop exceeded isr:%b",
E 9
I 9
		if ((isr & INTR_TER) != 0) {
E 22
I 22
D 29
		if (isr & INTR_TER) {
E 22
D 10
			cmn_err(CE_WARN, "%s: Tx error, isr:%b",
E 10
I 10
			cmn_err(CE_WARN, "!%s: Tx error, isr:%b",
E 10
D 22
				dp->name, isr, INTR_BITS);
E 22
I 22
			    dp->name, isr, INTR_BITS);
			lp->need_to_reset = B_TRUE;
E 22
		}
E 29
I 16
D 22
#endif
E 22
D 17
#if 0
		/* XXX: workaround for PCI-E nics */
		if (GANI_PCIE(lp->chip->type) &&
		   ((isr_org & (INTR_TOK | INTR_TDU)) == INTR_TOK | INTR_TDU)) {
			OUTB(dp, TPPoll, TPPoll_NPQ);
		}
#endif
E 17
E 16
	}
I 28
#endif /* !GEM3 */
E 28
I 16
D 17
#if 0
	if ((isr & INTR_SWInt) != 0) {
		lp->imr_disabled |= INTR_TOK;
	}
#endif
E 17
I 17

E 17
D 18
#if defined(WA_NO_TPPOLL_WRAP) || defined(CONFIG_OPT_TPPOLL)
E 18
I 18
D 22
#ifdef CONFIG_OPT_TPPOLL
E 18
	if ((isr & INTR_TDU) != 0) {
E 22
I 22
D 23
#if defined(CONFIG_OPT_TPPOLL) || defined(WA_NO_TPPOLL_WRAP)
	if (isr & INTR_TDU) {
E 22
		mutex_enter(&dp->xmitlock);
E 16
D 22

D 16
	if ((isr & INTR_SERR) != 0) {
		cmn_err(
D 10
#ifdef notef /* DEBUG_LEVEL */
E 10
I 10
#ifdef NEVER /* DEBUG_LEVEL */
E 10
			CE_PANIC,
#else
			CE_WARN,
E 16
I 16
D 18
#ifdef CONFIG_OPT_TPPOLL
E 18
		ASSERT(lp->tx_running == B_TRUE);
		lp->tx_running = B_FALSE;
I 18

E 18
		if (lp->tx_finished != lp->tx_activated) {
			/* just kick tx engine again */
			OUTB(dp, TPPoll, TPPoll_NPQ);
			lp->tx_running = B_TRUE;
E 22
I 22
#ifdef CONFIG_OPT_TPPOLL
		if (!lp->tx_running) {
			/* hardware error */
			lp->need_to_reset = B_TRUE;
			goto tdu_done;
E 22
		}
E 16
D 18
#endif
D 10
			"%s: unexpected interrupt: isr:%b",
E 10
I 10
D 16
			"!%s: unexpected interrupt: isr:%b",
E 16
I 16
#ifdef WA_NO_TPPOLL_WRAP
		if (SLOT(lp->tx_finished, TX_RING_SIZE) == 0) {
E 18
I 18
D 22
# ifdef WA_NO_TPPOLL_WRAP
		else if (SLOT(lp->tx_finished, TX_RING_SIZE) == 0) {
E 22
I 22
#endif
#ifdef WA_NO_TPPOLL_WRAP
		/*
		 * check if the pended requests can be released
		 */
		if (lp->tx_no_more &&
		    lp->tx_finished == lp->tx_activated &&
		    SLOT(lp->tx_finished, tx_ring_size) == 0) {
E 22
E 18
			/* we are at the end of tx ring */
D 18
			ASSERT(lp->tx_finished == lp->tx_activated); 

			/* tx_pended is vaild only if tx_no_more is true */
			ASSERT(lp->tx_no_more);
E 18
			lp->tx_no_more = B_FALSE;
			if (lp->tx_pended > 0) {
				gani_tx_start(dp, 0, lp->tx_pended);
I 18
				lp->tx_pended = 0;
E 18
			}
		}
D 18
#endif
E 18
I 18
D 22
# endif
E 22
I 22
#endif /* WA_NO_TPPOLL_WRAP */

		if (lp->tx_finished != lp->tx_activated) {
			/* just kick tx engine again */
			OUTB(dp, TPPoll, TPPoll_NPQ);
#ifdef CONFIG_OPT_TPPOLL
			lp->tx_running = B_TRUE;
		} else {
			lp->tx_running = B_FALSE;
#endif
		}
tdu_done:
E 22
E 18
		mutex_exit(&dp->xmitlock);
	}
D 18
#endif /* WA_NO_TPPOLL_WRAP || CONFIG_OPT_TPPOLL */
E 18
I 18
D 22
#endif /* CONFIG_OPT_TPPOLL */
E 22
I 22
#endif /* CONFIG_OPT_TPPOLL || WA_NO_TPPOLL_WRAP */
E 22
E 18

E 23
D 22
	if ((isr & INTR_SERR) != 0) {
E 22
I 22
	if (isr & INTR_SERR) {
E 22
		cmn_err(CE_WARN, "!%s: unexpected interrupt: isr:%b",
E 16
E 10
E 9
D 22
			dp->name, isr, INTR_BITS);
E 22
I 22
		    dp->name, isr, INTR_BITS);
E 22
D 16
		lp->need_to_reset = TRUE;
E 16
I 16
		lp->need_to_reset = B_TRUE;
E 16
I 5
D 9

D 6
		IO_BARRIER_ENTER(lp);
E 6
I 6
		mutex_enter(&lp->reglock);
E 6
E 5
		lp->imr = 0;
D 6
		OUTW(dp, IMR, lp->imr_hw = lp->imr);
I 5
		IO_BARRIER_EXIT(lp);
E 6
I 6
		mutex_exit(&lp->reglock);
E 9
E 6
E 5
	}

I 9
D 16
	/* barrier for interrupt state */
	FLSHW(dp, ISR);

E 16
E 9
	if (lp->need_to_reset) {
D 16
		mutex_enter(&dp->xmitlock);
I 11
		gani_stop_chip(dp);
E 11
D 14
		gem_restart_tx(dp);
E 14
I 14
		gem_restart_nic(dp, TRUE);
E 14
		mutex_exit(&dp->xmitlock);
E 16
I 16
D 17
		gem_restart_nic(dp, B_TRUE);
E 17
I 17
D 22
		gem_restart_nic(dp, GEM_RESTART_KEEP_BUF);
E 22
I 22
		(void) gem_restart_nic(dp, GEM_RESTART_KEEP_BUF);
E 22
E 17
E 16
I 6

E 6
		restart_tx = INTR_RESTART_TX;
D 16
		lp->need_to_reset = FALSE;
E 16
I 16
		lp->need_to_reset = B_FALSE;
E 16
	}

I 5
D 6
	IO_BARRIER_ENTER(lp);

E 5
I 3
	if ((dp->misc_flag & GEM_NOINTR) == 0 && lp->imr_hw != 0 &&
	    lp->imr_hw != lp->imr) {
D 5
		mutex_enter(&dp->xmitlock);
		if (lp->imr_hw != lp->imr) {
			lp->imr_hw = lp->imr;
		}
		mutex_exit(&dp->xmitlock);
E 5
I 5
		/* update imr */
		lp->imr_hw = lp->imr;
E 6
I 6
D 22
	if ((dp->misc_flag & GEM_NOINTR) == 0) {
I 17
#ifdef CONFIG_MSI
E 22
I 22
	if ((dp->misc_flag & GEM_NOINTR) == 0 && lp->imr != imr_hw) {
E 22
E 17
		/* enable interrupts again */
D 9
		mutex_enter(&lp->reglock);
E 9
D 16
		OUTW(dp, IMR, lp->imr_hw = lp->imr);
E 16
I 16
D 22
		OUTW(dp, IMR, lp->imr_hw = lp->imr & ~lp->imr_disabled);
I 17
#else
		/* change interrupt mask */
		if (lp->imr_hw != (lp->imr & ~lp->imr_disabled)) {
			OUTW(dp, IMR, lp->imr_hw = lp->imr & ~lp->imr_disabled);
		}
#endif
E 22
I 22
		OUTW(dp, IMR, lp->imr);
E 22
E 17
E 16
D 9
		mutex_exit(&lp->reglock);
E 9
E 6
E 5
	}

D 5
	/* enablle interrupts again */
E 5
I 5
D 6
	/* enable interrupts again */
E 5
	OUTW(dp, IMR, lp->imr_hw);
I 5
	FLSHW(dp, IMR);
E 5

I 5
	IO_BARRIER_EXIT(lp);

E 6
E 5
E 3
D 16
	return DDI_INTR_CLAIMED | restart_tx;
E 16
I 16
	return (DDI_INTR_CLAIMED | restart_tx);
E 16
}

D 22
/* 
E 22
I 22
/*
E 22
 * MII Interfaces
 */
D 6
#define	MII_DELAY(dp, r)	INL(dp, (r))
E 6
I 6
D 16
#define	MII_DELAY(dp, r)	{INL(dp, (r)); INL(dp, (r))}
E 16
I 16
D 22
#define	MII_DELAY(dp, r) {INL(dp, (r)); INL(dp, (r));}
E 22
I 22
#define	MII_DELAY(dp, r) { (void) INL(dp, (r)); (void) INL(dp, (r)); }
E 22
E 16
E 6

static void
gani_mii_sync(struct gem_dev *dp)
{
	/* do nothing */
}

I 21
#define	GANI_MII_MAX_RETRY	10

E 21
static uint16_t
D 13
gani_mii_read(struct gem_dev *dp, int index)
E 13
I 13
D 22
gani_mii_read(struct gem_dev *dp, uint_t index)
E 22
I 22
gani_mii_read_raw(struct gem_dev *dp, uint_t index)
E 22
E 13
{
D 28
	int		i;
I 21
	int		retry = 0;
E 21
	uint32_t	ret;
E 28
I 28
	int	i;
	int	retry = 0;
	uint_t	ret;
	struct gani_dev	*lp = dp->private;
E 28
I 4
D 22
	struct gani_dev	*lp = (struct gani_dev *)dp->private;
E 22
E 4

I 28
	if (lp->chip->type == R8168_12 /* RTL8168DP */) {
		OUTL(dp, 0xD0, INL(dp, 0xD0) & ~0x00020000);
	}
E 28
I 4
D 16
	if (dp->nic_active &&
E 16
I 16
D 21
	if (dp->mac_active &&
E 16
	   (ddi_get_lbolt() - lp->last_stats_time) >= ONESEC) {
		gani_get_stats(dp);
	}

E 21
I 21
again:
E 21
I 5
D 6
	IO_BARRIER_ENTER(lp);
E 6
E 5
E 4
D 13
	OUTL(dp, PHYAR, ((uint32_t)index) << PHYAR_REGADDR_SHIFT);
E 13
I 13
	OUTL(dp, PHYAR, index << PHYAR_REGADDR_SHIFT);
E 13
	drv_usecwait(20);

D 15
	i = 0;
	while (((ret = INL(dp, PHYAR)) & PHYAR_FLAG) == 0) {
		i++;
E 15
I 15
	for (i = 0; ((ret = INL(dp, PHYAR)) & PHYAR_FLAG) == 0; i++) {
E 15
D 22
		if (i > 1000) {
E 22
I 22
D 30
		if (i > 20) {
E 30
I 30
		if (i > 50) {
E 30
E 22
I 13
D 21
			cmn_err(CE_WARN, "%s: %s: timeout",
D 14
				dp->name, __FUNCTION__);
E 14
I 14
				dp->name, __func__);
E 21
I 21
			if (retry++ < GANI_MII_MAX_RETRY) {
				goto again;
			}
			cmn_err(CE_WARN, "!%s: %s: timeout, reg:%d",
D 22
				dp->name, __func__, index);
E 22
I 22
			    dp->name, __func__, index);
E 22
E 21
E 14
E 13
D 18
			return 0xffff;
E 18
I 18
D 28
			return (0);
E 28
I 28
			ret = 0;
			goto x;
E 28
E 18
		}
D 5
		drv_usecwait(10);
E 5
I 5
D 6
		IO_BARRIER_EXIT(lp);
E 6
		drv_usecwait(20);
D 6
		IO_BARRIER_ENTER(lp);
E 6
E 5
	}
I 5
D 6
	IO_BARRIER_EXIT(lp);
E 6
E 5
D 16
	return ret & PHYAR_DATA;
E 16
I 16
	ret &= PHYAR_DATA;
I 28
x:
I 30
	drv_usecwait(100);
E 30
	if (lp->chip->type == R8168_12 /* RTL8168DP */) {
		OUTL(dp, 0xD0, INL(dp, 0xD0) | 0x00020000);
	}

E 28
D 22
	return (ret);
E 22
I 22
	return ((uint16_t)ret);
E 22
E 16
}

I 28
static uint16_t
gani_phyio_read(struct gem_dev *dp, uint_t index)
{
	int	i;
	uint_t	ret;

	OUTL(dp, PHYIO, PHYIO_READ | (index << PHYIO_REG_SHIFT));
	drv_usecwait(100);

	for (i = 0; (INL(dp, PHYIO) & PHYIO_FLAG) == 0; i++) {
		if (i > 10) {
			cmn_err(CE_WARN, "!%s: %s: timeout, reg:%d",
			    dp->name, __func__, index);
			return (0);
		}
		drv_usecwait(100);
	}
	ret = INL(dp, PHYIO) & PHYIO_DATA;
	return ((uint16_t)ret);
}

E 28
static void
D 5
gani_mii_write(struct gem_dev *dp, int index, uint16_t val)
E 5
I 5
D 13
gani_mii_write_raw(struct gem_dev *dp, int index, uint16_t val)
E 13
I 13
D 22
gani_mii_write(struct gem_dev *dp, uint_t index, uint16_t val)
E 22
I 22
gani_mii_write_raw(struct gem_dev *dp, uint_t index, uint16_t val)
E 22
E 13
E 5
{
D 28
	int		i;
I 21
	int		retry = 0;
E 28
I 28
	int	i;
	int	retry = 0;
	struct gani_dev	*lp = dp->private;

	if (lp->chip->type == R8168_12 /* RTL8168DP */) {
		OUTL(dp, 0xD0, INL(dp, 0xD0) & ~0x00020000);
	}
E 28
E 21
I 5
D 22
	struct gani_dev	*lp = (struct gani_dev *)dp->private;
E 22
E 5
D 21

E 21
I 21
again:
E 21
I 5
D 6
	IO_BARRIER_ENTER(lp);
E 6
E 5
	OUTL(dp, PHYAR,
D 13
		PHYAR_FLAG | (((uint32_t)index) << PHYAR_REGADDR_SHIFT) | val);
E 13
I 13
D 22
		PHYAR_FLAG | (index << PHYAR_REGADDR_SHIFT) | val);
E 22
I 22
	    PHYAR_FLAG | (index << PHYAR_REGADDR_SHIFT) | val);
E 22
E 13
	drv_usecwait(20);

D 15
	i = 0;
	while ((INL(dp, PHYAR) & PHYAR_FLAG) != 0) {
		i++;
E 15
I 15
	for (i = 0; (INL(dp, PHYAR) & PHYAR_FLAG) != 0; i++) {
E 15
D 22
		if (i > 1000) {
E 22
I 22
D 30
		if (i > 20) {
E 30
I 30
		if (i > 50) {
E 30
E 22
I 13
D 21
			cmn_err(CE_WARN, "%s: %s: timeout",
D 14
				dp->name, __FUNCTION__);
E 14
I 14
				dp->name, __func__);
E 21
I 21
			if (retry++ < GANI_MII_MAX_RETRY) {
				goto again;
			}
			cmn_err(CE_WARN, "!%s: %s: timeout, reg:%d",
D 22
				dp->name, __func__, index);
E 22
I 22
			    dp->name, __func__, index);
E 22
E 21
E 14
E 13
			break;
		}
D 5
		drv_usecwait(10);
E 5
I 5
D 6
		IO_BARRIER_EXIT(lp);
E 6
		drv_usecwait(20);
D 6
		IO_BARRIER_ENTER(lp);
E 6
E 5
	}
I 30
	drv_usecwait(100);
E 30
I 28

	if (lp->chip->type == R8168_12 /* RTL8168DP */) {
		OUTL(dp, 0xD0, INL(dp, 0xD0) | 0x00020000);
	}
E 28
I 5
D 6
	IO_BARRIER_EXIT(lp);
E 6
E 5
}
I 5
D 13

static void
gani_mii_write(struct gem_dev *dp, int index, uint16_t val)
{
	gani_mii_write_raw(dp, index, val);
	if (index == MII_CONTROL_RESET && (val & MII_CONTROL_RESET) != 0) {
D 6
		/* emulate auto clear function of RESET bit */
E 6
I 6
		/* emulate auto-clear on RESET bit in MII_CONTROL register */
E 6
		gani_mii_write(dp, index, val & ~MII_CONTROL_RESET);
	}
}

E 13
E 5
#undef	MII_DELAY

I 28
static void
gani_phyio_write(struct gem_dev *dp, uint_t index, uint16_t val)
{
	int	i;

	OUTL(dp, PHYIO,
	    PHYIO_WRITE | (index << PHYIO_REG_SHIFT) | val);
	drv_usecwait(20);

	for (i = 0; INL(dp, PHYIO) & PHYIO_FLAG; i++) {
		if (i > 10) {
			cmn_err(CE_WARN, "!%s: %s: timeout, reg:%d",
			    dp->name, __func__, index);
			break;
		}
		drv_usecwait(200);
	}
	drv_usecwait(100);
}

static void
gani_mii_write_ocp(struct gem_dev *dp, uint_t index, uint16_t val)
{
	int	i;

	OUTL(dp, OCPDR, OCPDR_WRITE | (index << OCPDR_GPHY_REG_SHIFT) | val);
	OUTL(dp, OCPAR, OCPAR_GPHY_WRITE);
	OUTL(dp, EPHY_RXER_NUM, 0);

	for (i = 0; INL(dp, OCPAR) & OCPAR_FLAG; i++) {
		if (i > 100) {
			/* timeout */
			cmn_err(CE_WARN,
			    "!%s:%s: timeout", dp->name, __func__);
			break;
		}
		drv_usecwait(2000);
	}
}

E 28
D 10
#define GANI_MII_WRITE_BIT(dp, reg, bit, val)	\
	gani_mii_write(dp, reg,			\
	(gani_mii_read(dp, reg) & ~(1 << (bit))) | (val) << (bit))

#define	PATCH_PHY_PARAM(dp, blk, a, b, c, d) {	\
	gani_mii_write(dp, 4, (gani_mii_read(dp, 4) & 0x0fff) | (blk) << 12); \
	gani_mii_write(dp, 3, (a));	\
	gani_mii_write(dp, 2, (b));	\
	gani_mii_write(dp, 1, (c));	\
	gani_mii_write(dp, 0, (d));	\
	GANI_MII_WRITE_BIT(dp, 4, 11, 1 );	\
	GANI_MII_WRITE_BIT(dp, 4, 11, 0 );	\
}

E 10
D 22
static int
D 16
gani_mii_init(struct gem_dev *dp)
E 16
I 16
gani_mii_patch(struct gem_dev *dp)
E 22
I 22
static uint16_t
I 28
gani_mii_read_ocp(struct gem_dev *dp, uint_t index)
{
	int	i;
	uint16_t	val;

	OUTL(dp, OCPDR, OCPDR_READ | (index << OCPDR_GPHY_REG_SHIFT));
	OUTL(dp, OCPAR, OCPAR_GPHY_WRITE);
	OUTL(dp, EPHY_RXER_NUM, 0);

	for (i = 0; (INL(dp, OCPAR) & OCPAR_FLAG); i++) {
		if (i > 100) {
			/* timeout */
			cmn_err(CE_WARN,
			    "!%s:%s: timeout", dp->name, __func__);
			break;
		}
		drv_usecwait(2000);
	}

	OUTL(dp, OCPAR, OCPAR_GPHY_READ);
	val = INL(dp, OCPDR) & OCPDR_DATA;

	return (val);
}

static uint16_t
E 28
gani_mii_read(struct gem_dev *dp, uint_t index)
E 22
E 16
{
D 10
	int		ret;
	uint16_t	val;
	struct gani_dev	*lp = (struct gani_dev *)dp->private;
E 10
I 10
D 16
	int			ret;
	uint16_t		val;
E 16
D 13
	ddi_acc_handle_t	conf_handle;
E 13
D 22
	struct gani_dev		*lp = (struct gani_dev *)dp->private;
E 22
I 22
D 23
	struct gani_dev	*lp = dp->private;
#ifdef notdef
	if (GANI_PCI(lp->chip->type)) {
		/* prepare for reading phy */
		gani_mii_write_raw(dp, 0x1f, 0x0000);
	}
#endif
E 23
	return (gani_mii_read_raw(dp, index));
}
E 22
E 10

D 13
	lp->phy_rev = GEM_MII_READ(dp, MII_PHYIDL) & 0xf;
D 4

E 4
I 4
D 6
#ifdef notdef
E 6
I 6
D 10
#ifdef OBSOLUTE
E 6
E 4
	if (lp->chip->type >= MAC_VER_D && lp->phy_rev <= PHY_VER_E) {
E 10

E 13
D 10
		DPRINTF(3, (CE_CONT, "!%s: patching PHY", dp->name));

		gani_mii_write(dp, 31, 0x0001);

		gani_mii_write(dp, 21, 0x1000);
		gani_mii_write(dp, 24, 0x65c7);

		GANI_MII_WRITE_BIT(dp, 4, 11, 0);

		PATCH_PHY_PARAM(dp, 0x0, 0x00a1, 0x0008, 0x1020, 0x1000);
		PATCH_PHY_PARAM(dp, 0x7, 0xff41, 0xde60, 0x0140, 0x0077);
		PATCH_PHY_PARAM(dp, 0xa, 0xdf01, 0xdf20, 0xff95, 0xfa00);
		PATCH_PHY_PARAM(dp, 0xb, 0xff41, 0xde20, 0x0140, 0x00bb);
		PATCH_PHY_PARAM(dp, 0xf, 0xdf01, 0xdf20, 0xff95, 0xbf00);

		gani_mii_write(dp, 31, 0x0000);
	}
I 4
#endif
E 10
D 16
	if (lp->chip->type == MAC_VER_F /* M4 */) {
		gani_mii_write(dp, 0x1F, 0x0001);
		gani_mii_write(dp, 0x09, 0x273a);
		gani_mii_write(dp, 0x0e, 0x7bfb);
E 16
I 16
D 22
	switch (lp->chip->type) {
	case MAC_VER_8169S_D: /* M2 */
	case MAC_VER_8169S_E: /* M3 */
	{
		int	i;
		static struct {
			uint8_t		addr;
			uint16_t	val;
		} patch[] = {
D 21
		0x1f, 0x0001, 0x15, 0x1000, 0x18, 0x65c7, 0x04, 0x0000,
		0x03, 0x00a1, 0x02, 0x0008, 0x01, 0x1020, 0x00, 0x1000,
		0x04, 0x0800, 0x04, 0x0000, 0x04, 0x7000, 0x03, 0xff41,
		0x02, 0xde60, 0x01, 0x0140, 0x00, 0x0077, 0x04, 0x7800,
		0x04, 0x7000, 0x04, 0xa000, 0x03, 0xdf01, 0x02, 0xdf20,
		0x01, 0xff95, 0x00, 0xfa00, 0x04, 0xa800, 0x04, 0xa000,
		0x04, 0xb000, 0x03, 0xff41, 0x02, 0xde20, 0x01, 0x0140,
		0x00, 0x00bb, 0x04, 0xb800, 0x04, 0xb000, 0x04, 0xf000,
		0x03, 0xdf01, 0x02, 0xdf20, 0x01, 0xff95, 0x00, 0xbf00,
		0x04, 0xf800, 0x04, 0xf000, 0x04, 0x0000, 0x1f, 0x0000,
		0x0b, 0x0000,
E 21
I 21
			0x1f, 0x0001, 0x06, 0x006e, 0x08, 0x0708,
			0x15, 0x4000, 0x18, 0x65c7,
E 22
I 22
static void
gani_mii_write(struct gem_dev *dp, uint_t index, uint16_t val)
{
I 24
	struct gani_dev	*lp = dp->private;

I 30
	if (index == MII_CONTROL && val == MII_CONTROL_RESET) {
		val |= gani_mii_read(dp, index) & MII_CONTROL_ANE;
	}
E 30
D 28
	if ((GANI_PCIE_GIGA(lp->chip->type)) &&
E 28
I 28
D 29
	if ((GANI_PCIE_GIGA(lp) || lp->chip->type== R8101_10) &&
E 29
I 29
	if ((GANI_PCIE_GIGA(lp) || lp->chip->type == R8101_10) &&
E 29
E 28
	    index == MII_CONTROL && (val & MII_CONTROL_RSAN)) {
		val |= MII_CONTROL_RESET;
	}
E 24
D 23
	struct gani_dev	*lp = dp->private;
#ifdef notdef
	if (GANI_PCI(lp->chip->type) || GANI_PCIE_FAST(lp->chip->type)) {
		/* prepare for writing phy */
		gani_mii_write_raw(dp, 0x1f, 0x0000);
	}
#endif
E 23
	gani_mii_write_raw(dp, index, val);
}
E 22

D 22
			0x1f, 0x0001, 0x03, 0x00a1, 0x02, 0x0008,
			0x01, 0x0120, 0x00, 0x1000, 0x04, 0x0800,
			0x04, 0x0000,
E 22
I 22
struct gani_patch {
	uint_t	addr:8;
	uint_t	val:16;
};
E 22

D 22
			0x03, 0xff41, 0x02, 0xdf60, 0x01, 0x0140,
			0x00, 0x0077, 0x04, 0x7800, 0x04, 0x7000,
E 22
I 22
static struct gani_patch gani_8169_m2_patch[] = {
I 24
D 28
	/* 009 */
E 28
I 28
	/* 012 */
E 28
E 24
	0x1f, 0x0001, 0x06, 0x006e, 0x08, 0x0708,
	0x15, 0x4000, 0x18, 0x65c7,
E 22

D 22
			0x03, 0x802f, 0x02, 0x4f02, 0x01, 0x0409,
			0x00, 0xf0f9, 0x04, 0x9800, 0x04, 0x9000,
E 22
I 22
	0x1f, 0x0001, 0x03, 0x00a1, 0x02, 0x0008,
	0x01, 0x0120, 0x00, 0x1000, 0x04, 0x0800,
	0x04, 0x0000,
E 22

D 22
			0x03, 0xdf01, 0x02, 0xdf20, 0x01, 0xff95,
			0x00, 0xba00, 0x04, 0xa800, 0x04, 0xa000,
E 22
I 22
	0x03, 0xff41, 0x02, 0xdf60, 0x01, 0x0140,
	0x00, 0x0077, 0x04, 0x7800, 0x04, 0x7000,
E 22

D 22
			0x03, 0xff41, 0x02, 0xdf20, 0x01, 0x0140,
			0x00, 0x00bb, 0x04, 0xb800, 0x04, 0xb000,
E 22
I 22
	0x03, 0x802f, 0x02, 0x4f02, 0x01, 0x0409,
	0x00, 0xf0f9, 0x04, 0x9800, 0x04, 0x9000,
E 22

D 22
			0x03, 0xdf41, 0x02, 0xdc60, 0x01, 0x6340,
			0x00, 0x007d, 0x04, 0xd800, 0x04, 0xd000,
E 22
I 22
	0x03, 0xdf01, 0x02, 0xdf20, 0x01, 0xff95,
	0x00, 0xba00, 0x04, 0xa800, 0x04, 0xa000,
I 28

E 28
E 22
D 24

E 24
D 22
			0x03, 0xdf01, 0x02, 0xdf20, 0x01, 0x100a,
			0x00, 0xa0ff, 0x04, 0xf800, 0x04, 0xf000,
E 22
I 22
	0x03, 0xff41, 0x02, 0xdf20, 0x01, 0x0140,
	0x00, 0x00bb, 0x04, 0xb800, 0x04, 0xb000,
E 22

D 22
			0x1f, 0x0000, 0x0b, 0x0000, 0x00, 0x9200,
E 21
		};
		for (i = 0; i < sizeof(patch)/sizeof(patch[0]); i++) {
			gani_mii_write(dp, patch[i].addr, patch[i].val);
E 22
I 22
	0x03, 0xdf41, 0x02, 0xdc60, 0x01, 0x6340,
	0x00, 0x007d, 0x04, 0xd800, 0x04, 0xd000,

	0x03, 0xdf01, 0x02, 0xdf20, 0x01, 0x100a,
	0x00, 0xa0ff, 0x04, 0xf800, 0x04, 0xf000,

	0x1f, 0x0000, 0x0b, 0x0000, 0x00, 0x9200,
I 23
D 24

	0x1f, 0x0000,
E 24
E 23
};

static struct gani_patch gani_8169_m4_patch[] = {
I 24
D 28
	/* 009 */
E 28
I 28
	/* 012 */
E 28
E 24
	0x1f, 0x0002, 0x01, 0x90d0, 0x1f, 0x0000,
};

D 24
static struct gani_patch gani_8169_m5_patch[] = {
	0x1f, 0x0000, 0x01, 0xf890, 0x1f, 0x0000,

E 24
I 24
static struct gani_patch gani_8169_m5_patch0[] = {
D 28
	/* 009 */
E 24
	0x1f, 0x0001, 0x04, 0x0000, 0x03, 0x00a1,
	0x02, 0x0008, 0x01, 0x0120, 0x00, 0x1000,
	0x04, 0x0800, 0x04, 0x9000, 0x03, 0x802f,
	0x02, 0x4f02, 0x01, 0x0409, 0x00, 0xf099,
	0x04, 0x9800, 0x04, 0xa000, 0x03, 0xdf01,
	0x02, 0xdf20, 0x01, 0xff95, 0x00, 0xba00,
	0x04, 0xa800, 0x04, 0xf000, 0x03, 0xdf01,
	0x02, 0xdf20, 0x01, 0x101a, 0x00, 0xa0ff,
E 28
I 28
	/* 012 */
	0x1f, 0x0001, 0x04, 0x0000, 0x03, 0x00a1, 0x02, 0x0008,
	0x01, 0x0120, 0x00, 0x1000, 0x04, 0x0800, 0x04, 0x9000,
	0x03, 0x802f, 0x02, 0x4f02, 0x01, 0x0409, 0x00, 0xf099,
	0x04, 0x9800, 0x04, 0xa000, 0x03, 0xdf01, 0x02, 0xdf20,
	0x01, 0xff95, 0x00, 0xba00, 0x04, 0xa800, 0x04, 0xf000,
	0x03, 0xdf01, 0x02, 0xdf20, 0x01, 0x101a, 0x00, 0xa0ff,
E 28
	0x04, 0xf800, 0x04, 0x0000, 0x1f, 0x0000,

D 28
	0x1f, 0x0001, 0x10, 0xf41b, 0x14, 0xfb54,
	0x18, 0xf5c7, 0x1f, 0x0000,
E 28
I 28
	0x1f, 0x0001, 0x10, 0xf41b, 0x14, 0xfb54, 0x18, 0xf5c7,
	0x1f, 0x0000,
E 28

D 24
	0x1f, 0x0001, 0x17, 0x0CC0, 0x1F, 0x0000,
E 24
I 24
	0x1f, 0x0001, 0x17, 0x0cc0, 0x1f, 0x0000,
E 24
};

D 24
static struct gani_patch gani_8169_m6_patch0[] = {
E 24
I 24
static struct gani_patch gani_8169_m5_patch1[] = {
D 28
	/* 009 */
E 28
I 28
	/* 012 */
E 28
	0x1f, 0x0001, 0x10, 0xf01b, 0x1f, 0x0000,
};

static struct gani_patch gani_8169_m6_patch[] = {
	/* 009 */
E 24
	0x1f, 0x0001, 0x04, 0x0000, 0x03, 0x00a1,
	0x02, 0x0008, 0x01, 0x0120, 0x00, 0x1000,
	0x04, 0x0800, 0x04, 0x9000, 0x03, 0x802f,
	0x02, 0x4f02, 0x01, 0x0409, 0x00, 0xf099,
	0x04, 0x9800, 0x04, 0xa000, 0x03, 0xdf01,
	0x02, 0xdf20, 0x01, 0xff95, 0x00, 0xba00,
	0x04, 0xa800, 0x04, 0xf000, 0x03, 0xdf01,
	0x02, 0xdf20, 0x01, 0x101a, 0x00, 0xa0ff,
	0x04, 0xf800, 0x04, 0x0000, 0x1f, 0x0000,
I 28

E 28
D 24

E 24
	0x1f, 0x0001, 0x0b, 0x8480, 0x1f, 0x0000,

	0x1f, 0x0001, 0x18, 0x67c7, 0x04, 0x2000,
	0x03, 0x002f, 0x02, 0x4360, 0x01, 0x0109,
	0x00, 0x3022, 0x04, 0x2800, 0x1f, 0x0000,
I 28

E 28
I 24
	0x1f, 0x0001, 0x17, 0x0cc0, 0x1f, 0x0000,
E 24
};
D 24
static struct gani_patch gani_8169_m6_patch1[] = {
	0x1f, 0x0001, 0x10, 0xf01b, 0x1f, 0x0000,
E 24
I 24

static struct gani_patch gani_8168_m1_patch[] = {
D 28
	/* 010 */
E 28
I 28
	/* 013 */
E 28
	0x1F, 0x0001, 0x0B, 0x94B0,
D 28
	0x1F, 0x0003, 0x12, 0x6096,
	0x1F, 0x0000,
E 28
I 28

	0x1F, 0x0003, 0x12, 0x6096, 0x1F, 0x0000,

E 28
	0x0D, 0xF8A0,
	0x1F, 0x0000,
E 24
};
D 24
static struct gani_patch gani_8169_m6_patch2[] = {
	0x1f, 0x0001, 0x17, 0x0CC0, 0x1F, 0x0000,
};
E 24

static struct gani_patch gani_8168_m2_patch[] = {
D 24
	0x1f, 0x0001, 0x10, 0xF41B, 0x1f, 0x0000,
E 24
I 24
D 28
	/* 010 */
E 28
I 28
	/* 013 */
E 28
	0x1F, 0x0001, 0x0B, 0x94B0,
I 28

E 28
	0x1F, 0x0003, 0x12, 0x6096,
I 28

E 28
	0x1F, 0x0000,
E 24
};

I 24
static struct gani_patch gani_8168_m3_patch[] = {
D 28
	/* 010 */
E 28
I 28
	/* 013 */
E 28
	0x1F, 0x0001, 0x0B, 0x94B0,
I 28

E 28
	0x1F, 0x0003, 0x12, 0x6096,
I 28

E 28
	0x1F, 0x0000,
};

E 24
static struct gani_patch gani_8168_m4_patch[] = {
I 24
D 28
	/* 010 */
	0x1F, 0x0001, 0x12, 0x2300, 0x1F, 0x0000,
	0x1F, 0x0003, 0x16, 0x000A, 0x1F, 0x0000,
E 28
I 28
	/* 013 */
	0x1F, 0x0001, 0x12, 0x2300, 0x1F, 0x0000, 0x1F, 0x0003,
	0x16, 0x000A, 0x1F, 0x0000,
E 28

	0x1F, 0x0003, 0x12, 0xC096, 0x1F, 0x0000,

E 24
D 28
	0x1F, 0x0002, 0x00, 0x88DE, 0x01, 0x82B1,
D 24
	0x03, 0x7002, 0x08, 0x9E30, 0x09, 0x01F0,
	0x0A, 0x5500, 0x0C, 0x00C8,
E 24
I 24
	0x1F, 0x0000,
E 28
I 28
	0x1F, 0x0002, 0x00, 0x88DE, 0x01, 0x82B1, 0x1F, 0x0000,
E 28
E 24

D 24
	0x1F, 0x0003, 0x12, 0xC096, 0x16, 0x000A,
};
E 24
I 24
D 28
	0x1F, 0x0002, 0x08, 0x9E30, 0x09, 0x01F0,
	0x1F, 0x0000,
E 28
I 28
	0x1F, 0x0002, 0x08, 0x9E30, 0x09, 0x01F0, 0x1F, 0x0000,
E 28
E 24

D 24
static struct gani_patch gani_8168_m5_patch0[] = {
	0x1F, 0x0001, 0x12, 0x2300, 0x03, 0x802F,
	0x02, 0x4F02, 0x01, 0x0409, 0x00, 0xF099,
	0x04, 0x9800, 0x04, 0x9000, 0x1D, 0x3D98,
E 24
I 24
	0x1F, 0x0002, 0x0A, 0x5500, 0x1F, 0x0000,
E 24

D 24
	0x1F, 0x0002, 0x00, 0x88DE, 0x01, 0x82B1,
	0x06, 0x0761, 0x0C, 0x7EB8,
E 24
I 24
	0x1F, 0x0002, 0x03, 0x7002, 0x1F, 0x0000,
E 24

D 24
	0x1F, 0x0003, 0x16, 0x0F0A,
E 24
I 24
	0x1F, 0x0002, 0x0C, 0x00C8, 0x1F, 0x0000,

	0x1F, 0x0000,
E 24
};

D 24
static struct gani_patch gani_8168_m5_patch1[] = {
	0x1F, 0x0001, 0x14, 0xCAA3, 0x1C, 0x000A,
	0x18, 0x65D0,
E 24
I 24
static struct gani_patch gani_8168_m5_patch0[] = {
D 28
	/* 010 */
	0x1F, 0x0001, 0x12, 0x2300, 0x1F, 0x0003,
	0x16, 0x0F0A, 0x1F, 0x0000,
E 24

D 24
	0x1F, 0x0003, 0x17, 0xB580, 0x18, 0xFF54,
	0x19, 0x3954,
E 24
I 24
	0x1F, 0x0002, 0x00, 0x88DE, 0x01, 0x82B1,
E 28
I 28
	/* 013 */
	0x1F, 0x0001, 0x12, 0x2300, 0x1F, 0x0003, 0x16, 0x0F0A,
E 28
	0x1F, 0x0000,
E 24

I 28
	0x1F, 0x0002, 0x00, 0x88DE, 0x01, 0x82B1, 0x1F, 0x0000,

E 28
D 24
	0x1F, 0x0002, 0x0D, 0x310C, 0x0E, 0x310C,
	0x0F, 0x311C, 0x06, 0x0761,
E 24
I 24
	0x1F, 0x0002, 0x0C, 0x7EB8, 0x1F, 0x0000,
E 24

D 24
	0x1F, 0x0003, 0x18, 0xFF55, 0x19, 0x3955,
	0x18, 0xFF54, 0x19, 0x3954,
E 24
I 24
	0x1F, 0x0002, 0x06, 0x0761, 0x1F, 0x0000,
E 24

D 24
	0x1f, 0x0001, 0x17, 0x0CC0,
E 24
I 24
D 28
	0x1F, 0x0001, 0x03, 0x802F, 0x02, 0x4F02,
	0x01, 0x0409, 0x00, 0xF099, 0x04, 0x9800,
	0x04, 0x9000, 0x1F, 0x0000,
E 28
I 28
	0x1F, 0x0001, 0x03, 0x802F, 0x02, 0x4F02, 0x01, 0x0409,
	0x00, 0xF099, 0x04, 0x9800, 0x04, 0x9000, 0x1F, 0x0000,
E 28
E 24

	0x1F, 0x0000,
};

I 24
static struct gani_patch gani_8168_m5_patch1[] = {
D 28
	/* 010 */
E 28
I 28
	/* 013 */
E 28
	0x1F, 0x0001, 0x1D, 0x3D98, 0x1F, 0x0000,
D 28
	0x1F, 0x0001, 0x17, 0x0CC0,
	0x1F, 0x0000,
E 28
I 28

	0x1F, 0x0001, 0x17, 0x0CC0, 0x1F, 0x0000,
E 28
};

E 24
static struct gani_patch gani_8168_m6_patch0[] = {
D 24
	0x1F, 0x0001, 0x12, 0x2300, 0x1D, 0x3D98,
E 24
I 24
D 28
	/* 010 */
	0x1F, 0x0001, 0x12, 0x2300, 0x1F, 0x0003,
	0x16, 0x0F0A, 0x1F, 0x0000,
E 24

	0x1F, 0x0002, 0x00, 0x88DE, 0x01, 0x82B1,
E 28
I 28
	/* 013 */
	0x1F, 0x0001, 0x12, 0x2300, 0x1F, 0x0003, 0x16, 0x0F0A,
E 28
D 24
	0x06, 0x0761, 0x0C, 0x7EB8,
E 24
I 24
	0x1F, 0x0000,
E 24

I 28
	0x1F, 0x0002, 0x00, 0x88DE, 0x01, 0x82B1, 0x1F, 0x0000,

E 28
D 24
	0x1F, 0x0003, 0x16, 0x0F0A,
E 24
I 24
	0x1F, 0x0002, 0x0C, 0x7EB8, 0x1F, 0x0000,

	0x1F, 0x0002, 0x06, 0x0761, 0x1F, 0x0000,

I 28
	0x1F, 0x0002, 0x06, 0x5461, 0x1F, 0x0000,

E 28
	0x1F, 0x0000,
E 24
};

static struct gani_patch gani_8168_m6_patch1[] = {
D 24
	0x1F, 0x0001, 0x14, 0xCAA3, 0x1C, 0x000A,
	0x18, 0x65D0,
E 24
I 24
D 28
	/* 010 */
E 28
I 28
	/* 013 */
E 28
	0x1F, 0x0001, 0x1D, 0x3D98, 0x1F, 0x0000,
E 24

D 24
	0x1F, 0x0003, 0x17, 0xB580, 0x18, 0xFF54,
	0x19, 0x3954,

	0x1F, 0x0002, 0x0D, 0x310C, 0x0E, 0x310C,
	0x0F, 0x311C, 0x06, 0x0761,

	0x1F, 0x0003, 0x18, 0xFF55, 0x19, 0x3955,
	0x18, 0xFF54, 0x19, 0x3954,

E 24
D 28
	0x1f, 0x0001, 0x17, 0x0CC0,

	0x1F, 0x0000,
E 28
I 28
	0x1f, 0x0001, 0x17, 0x0CC0, 0x1F, 0x0000,
E 28
};

static struct gani_patch gani_8168_m7_patch[] = {
I 24
D 28
	/* 010 */
E 28
I 28
	/* 013 */
E 28
E 24
	0x1F, 0x0001, 0x1D, 0x3D98,

D 28
	0x1F, 0x0001, 0x14, 0xCAA3, 0x1C, 0x000A,
	0x18, 0x65D0,
E 28
I 28
	0x1F, 0x0001, 0x14, 0xCAA3, 0x1C, 0x000A, 0x18, 0x65D0,
E 28

D 28
	0x1F, 0x0003, 0x17, 0xB580, 0x18, 0xFF54,
	0x19, 0x3954,
E 28
I 28
	0x1F, 0x0003, 0x17, 0xB580, 0x18, 0xFF54, 0x19, 0x3954,
E 28

D 28
	0x1F, 0x0002, 0x0D, 0x310C, 0x0E, 0x310C,
	0x0F, 0x311C, 0x06, 0x0761,
E 28
I 28
	0x1F, 0x0002, 0x0D, 0x310C, 0x0E, 0x310C, 0x0F, 0x311C,
	0x06, 0x0761,
E 28

D 28
	0x1F, 0x0003, 0x18, 0xFF55, 0x19, 0x3955,
	0x18, 0xFF54, 0x19, 0x3954,
E 28
I 28
	0x1F, 0x0003, 0x18, 0xFF55, 0x19, 0x3955, 0x18, 0xFF54,
	0x19, 0x3954,
E 28

D 28
	0x1f, 0x0001, 0x17, 0x0CC0,
E 28
I 28
	0x1F, 0x0001, 0x17, 0x0CC0,
E 28

	0x1F, 0x0000,
};

static struct gani_patch gani_8168_m8_patch[] = {
D 28
	0x1F, 0x0001, 0x14, 0xCAA3, 0x1C, 0x000A,
	0x18, 0x65D0,
E 28
I 28
	/* 013 */
	0x1F, 0x0001, 0x14, 0xCAA3, 0x1C, 0x000A, 0x18, 0x65D0,
E 28

D 28
	0x1F, 0x0003, 0x17, 0xB580, 0x18, 0xFF54,
	0x19, 0x3954,
E 28
I 28
	0x1F, 0x0003, 0x17, 0xB580, 0x18, 0xFF54, 0x19, 0x3954,
E 28

D 28
	0x1F, 0x0002, 0x0D, 0x310C, 0x0E, 0x310C,
	0x0F, 0x311C, 0x06, 0x0761,
E 28
I 28
	0x1F, 0x0002, 0x0D, 0x310C, 0x0E, 0x310C, 0x0F, 0x311C,
	0x06, 0x0761,
E 28

D 28
	0x1F, 0x0003, 0x18, 0xFF55, 0x19, 0x3955,
	0x18, 0xFF54, 0x19, 0x3954,
E 28
I 28
	0x1F, 0x0003, 0x18, 0xFF55, 0x19, 0x3955, 0x18, 0xFF54,
	0x19, 0x3954,
E 28

D 28
	0x1f, 0x0001, 0x17, 0x0CC0,
E 28
I 28
	0x1F, 0x0001, 0x17, 0x0CC0,
E 28

	0x1F, 0x0000,
};

D 24
static struct gani_patch gani_8168_m9_patch0[] = {
E 24
I 24
D 28
static struct gani_patch gani_8168_m9_patch[] = {
	/* 010 */
	0x1F, 0x0001, 0x06, 0x4064, 0x07, 0x2863,
	0x08, 0x059C, 0x09, 0x26B4, 0x0A, 0x6A19,
	0x0B, 0xACC0, 0x10, 0xF06D, 0x14, 0x7F68,
	0x18, 0x7FD9, 0x1C, 0xF0FF, 0x1D, 0x3D9C,
	0x1F, 0x0003, 0x12, 0xF49F, 0x13, 0x070B,
	0x1A, 0x05AD, 0x14, 0x94C0,
E 28
I 28
static struct gani_patch gani_8168_m9_patch0[] = {
	/* 013 */
	0x1F, 0x0001, 0x06, 0x4064, 0x07, 0x2863, 0x08, 0x059C,
	0x09, 0x26B4, 0x0A, 0x6A19, 0x0B, 0xDCC8, 0x10, 0xF06D,
	0x14, 0x7F68, 0x18, 0x7FD9, 0x1C, 0xF0FF, 0x1D, 0x3D9C,
	0x1F, 0x0003, 0x12, 0xF49F, 0x13, 0x070B, 0x1A, 0x05AD,
	0x14, 0x94C0,
};
E 28

E 24
D 28
	0x1F, 0x0002, 0x0B, 0x0B10, 0x0C, 0xA2F7,
E 28
I 28
static struct gani_patch gani_8168_m9_patch1[] = {
	/* 012 */
	0x1F, 0x0001, 0x17, 0x0CC0,
E 28

D 24
	0x1F, 0x0002, 0x06, 0x5561,
};
E 24
I 24
D 28
	0x1F, 0x0002, 0x06, 0x5571,
E 28
I 28
	0x1F, 0x0005, 0x05, 0xFFF6, 0x06, 0x0080, 0x05, 0x8000,
E 28
E 24

D 24
static struct gani_patch gani_8168_m9_patch1[] = {
	0x1F, 0x0002, 0x15, 0x3628, 0x16, 0x7670,
	0x17, 0x7670,

	0x1F, 0x0003, 0x17, 0x7BC0, 0x18, 0xFF46,
	0x19, 0x3247,

E 24
D 28
	0x1F, 0x0002, 0x02, 0xC107, 0x03, 0x1002,
E 28
I 28
	0x06, 0xF8F9, 0x06, 0xFAEF, 0x06, 0x59EE, 0x06, 0xF8EA,
	0x06, 0x00EE, 0x06, 0xF8EB, 0x06, 0x00E0, 0x06, 0xF87C,
	0x06, 0xE1F8, 0x06, 0x7D59, 0x06, 0x0FEF, 0x06, 0x0139,
	0x06, 0x029E, 0x06, 0x06EF, 0x06, 0x1039, 0x06, 0x089F,
	0x06, 0x2AEE, 0x06, 0xF8EA, 0x06, 0x00EE, 0x06, 0xF8EB,
	0x06, 0x01E0, 0x06, 0xF87C,
E 28

D 24
	0x1F, 0x0002, 0x15, 0x3628, 0x16, 0x7670,
	0x17, 0x7670, 0x1F, 0x0003, 0x17, 0x7BC0,
	0x18, 0xFF46, 0x19, 0x3247,
E 24
I 24
D 28
	0x1F, 0x0001, 0x17, 0x0CC0,
E 28
I 28
	0x06, 0xE1F8, 0x06, 0x7D58, 0x06, 0x409E, 0x06, 0x0F39,
	0x06, 0x46AA, 0x06, 0x0BBF, 0x06, 0x8290, 0x06, 0xD682,
	0x06, 0x9802, 0x06, 0x014F, 0x06, 0xAE09, 0x06, 0xBF82,
	0x06, 0x98D6, 0x06, 0x82A0, 0x06, 0x0201, 0x06, 0x4FEF,
	0x06, 0x95FE, 0x06, 0xFDFC, 0x06, 0x05F8, 0x06, 0xF9FA,
	0x06, 0xEEF8, 0x06, 0xEA00,
E 28
E 24

D 24
	0x1F, 0x0002, 0x02, 0xC107, 0x03, 0x1002,
E 24
I 24
D 28
	0x1F, 0x0005, 0x05, 0x8200, 0x06, 0xF8F9,
	0x06, 0xFAEF, 0x06, 0x59EE, 0x06, 0xF8EA,
	0x06, 0x00EE, 0x06, 0xF8EB, 0x06, 0x00E0,
	0x06, 0xF87C, 0x06, 0xE1F8, 0x06, 0x7D59,
	0x06, 0x0FEF, 0x06, 0x0139, 0x06, 0x029E,
	0x06, 0x06EF, 0x06, 0x1039, 0x06, 0x089F,
	0x06, 0x2AEE, 0x06, 0xF8EA, 0x06, 0x00EE,
	0x06, 0xF8EB, 0x06, 0x01E0, 0x06, 0xF87C,
	0x06, 0xE1F8, 0x06, 0x7D58, 0x06, 0x409E,
	0x06, 0x0F39, 0x06, 0x46AA, 0x06, 0x0BBF,
	0x06, 0x8251, 0x06, 0xD682, 0x06, 0x5902,
	0x06, 0x014F, 0x06, 0xAE09, 0x06, 0xBF82,
	0x06, 0x59D6, 0x06, 0x8261, 0x06, 0x0201,
	0x06, 0x4FEF, 0x06, 0x95FE, 0x06, 0xFDFC,
	0x06, 0x054D, 0x06, 0x2000, 0x06, 0x024E,
	0x06, 0x2200, 0x06, 0x024D, 0x06, 0xDFFF,
	0x06, 0x014E, 0x06, 0xDDFF, 0x06, 0x0100,
	0x06, 0x6010, 0x05, 0xFFF6, 0x06, 0x00EC,
	0x05, 0x83D4, 0x06, 0x8200,
E 28
I 28
	0x06, 0xEEF8, 0x06, 0xEB00, 0x06, 0xE2F8, 0x06, 0x7CE3,
	0x06, 0xF87D, 0x06, 0xA511, 0x06, 0x1112, 0x06, 0xD240,
	0x06, 0xD644, 0x06, 0x4402, 0x06, 0x8217, 0x06, 0xD2A0,
	0x06, 0xD6AA, 0x06, 0xAA02, 0x06, 0x8217, 0x06, 0xAE0F,
	0x06, 0xA544, 0x06, 0x4402, 0x06, 0xAE4D, 0x06, 0xA5AA,
	0x06, 0xAA02, 0x06, 0xAE47, 0x06, 0xAF82, 0x06, 0x13EE,
	0x06, 0x834E, 0x06, 0x00EE, 0x06, 0x834D, 0x06, 0x0FEE,
	0x06, 0x834C, 0x06, 0x0FEE, 0x06, 0x834F, 0x06, 0x00EE,
	0x06, 0x8351, 0x06, 0x00EE, 0x06, 0x834A, 0x06, 0xFFEE,
	0x06, 0x834B, 0x06, 0xFFE0, 0x06, 0x8330, 0x06, 0xE183,
	0x06, 0x3158, 0x06, 0xFEE4, 0x06, 0xF88A, 0x06, 0xE5F8,
E 28
E 24

D 24
	0x1f, 0x0001, 0x17, 0x0CC0,

E 24
D 28
	0x1F, 0x0000,
};
E 28
I 28
	0x06, 0x8BE0, 0x06, 0x8332, 0x06, 0xE183, 0x06, 0x3359,
	0x06, 0x0FE2, 0x06, 0x834D, 0x06, 0x0C24, 0x06, 0x5AF0,
	0x06, 0x1E12, 0x06, 0xE4F8, 0x06, 0x8CE5, 0x06, 0xF88D,
	0x06, 0xAF82, 0x06, 0x13E0, 0x06, 0x834F, 0x06, 0x10E4,
	0x06, 0x834F, 0x06, 0xE083, 0x06, 0x4E78, 0x06, 0x009F,
	0x06, 0x0AE0, 0x06, 0x834F,
E 28

D 28
static struct gani_patch gani_8168_m10_patch[] = {
I 24
	/* 010 */
	0x1F, 0x0001, 0x06, 0x4064, 0x07, 0x2863,
	0x08, 0x059C, 0x09, 0x26B4, 0x0A, 0x6A19,
	0x0B, 0xACC0, 0x10, 0xF06D, 0x14, 0x7F68,
	0x18, 0x7FD9, 0x1C, 0xF0FF, 0x1D, 0x3D9C,
	0x1F, 0x0003, 0x12, 0xF49F, 0x13, 0x070B,
	0x1A, 0x05AD, 0x14, 0x94C0,
E 28
I 28
	0x06, 0xA010, 0x06, 0xA5EE, 0x06, 0x834E, 0x06, 0x01E0,
	0x06, 0x834E, 0x06, 0x7805, 0x06, 0x9E9A, 0x06, 0xE083,
	0x06, 0x4E78, 0x06, 0x049E, 0x06, 0x10E0, 0x06, 0x834E,
	0x06, 0x7803, 0x06, 0x9E0F, 0x06, 0xE083, 0x06, 0x4E78,
	0x06, 0x019E, 0x06, 0x05AE, 0x06, 0x0CAF, 0x06, 0x81F8,
	0x06, 0xAF81, 0x06, 0xA3AF,
E 28

E 24
D 28
	0x1F, 0x0002, 0x06, 0x5571,
E 28
I 28
	0x06, 0x81DC, 0x06, 0xAF82, 0x06, 0x13EE, 0x06, 0x8348,
	0x06, 0x00EE, 0x06, 0x8349, 0x06, 0x00E0, 0x06, 0x8351,
	0x06, 0x10E4, 0x06, 0x8351, 0x06, 0x5801, 0x06, 0x9FEA,
	0x06, 0xD000, 0x06, 0xD180, 0x06, 0x1F66, 0x06, 0xE2F8,
	0x06, 0xEAE3, 0x06, 0xF8EB, 0x06, 0x5AF8, 0x06, 0x1E20,
	0x06, 0xE6F8, 0x06, 0xEAE5,
E 28

D 24
	0x1F, 0x0002, 0x05, 0x1042,
E 24
I 24
D 28
	0x1F, 0x0002, 0x05, 0x2642,
E 28
I 28
	0x06, 0xF8EB, 0x06, 0xD302, 0x06, 0xB3FE, 0x06, 0xE2F8,
	0x06, 0x7CEF, 0x06, 0x325B, 0x06, 0x80E3, 0x06, 0xF87D,
	0x06, 0x9E03, 0x06, 0x7DFF, 0x06, 0xFF0D, 0x06, 0x581C,
	0x06, 0x551A, 0x06, 0x6511, 0x06, 0xA190, 0x06, 0xD3E2,
	0x06, 0x8348, 0x06, 0xE383, 0x06, 0x491B, 0x06, 0x56AB,
	0x06, 0x08EF, 0x06, 0x56E6,
E 28
E 24

D 24
	0x1F, 0x0000, 0x16, 0x5101,

	0x1F, 0x0002, 0x15, 0x3628, 0x16, 0x764C,
	0x17, 0x76B4,
	0x1F, 0x0003, 0x17, 0x7BC0, 0x18, 0xFF46,
	0x19, 0x3247,

E 24
D 28
	0x1F, 0x0002, 0x02, 0xC107, 0x03, 0x1002,
E 28
I 28
	0x06, 0x8348, 0x06, 0xE783, 0x06, 0x4910, 0x06, 0xD180,
	0x06, 0x1F66, 0x06, 0xA004, 0x06, 0xB9E2, 0x06, 0x8348,
	0x06, 0xE383, 0x06, 0x49EF, 0x06, 0x65E2, 0x06, 0x834A,
	0x06, 0xE383, 0x06, 0x4B1B, 0x06, 0x56AA, 0x06, 0x0EEF,
	0x06, 0x56E6, 0x06, 0x834A, 0x06, 0xE783, 0x06, 0x4BE2,
	0x06, 0x834D, 0x06, 0xE683,
E 28

D 28
	0x1F, 0x0001, 0x17, 0x0CC0,
E 28
I 28
	0x06, 0x4CE0, 0x06, 0x834D, 0x06, 0xA000, 0x06, 0x0CAF,
	0x06, 0x81DC, 0x06, 0xE083, 0x06, 0x4D10, 0x06, 0xE483,
	0x06, 0x4DAE, 0x06, 0x0480, 0x06, 0xE483, 0x06, 0x4DE0,
	0x06, 0x834E, 0x06, 0x7803, 0x06, 0x9E0B, 0x06, 0xE083,
	0x06, 0x4E78, 0x06, 0x049E, 0x06, 0x04EE, 0x06, 0x834E,
	0x06, 0x02E0, 0x06, 0x8332,
E 28

D 28
	0x1F, 0x0002, 0x0F, 0x0017,
E 28
I 28
	0x06, 0xE183, 0x06, 0x3359, 0x06, 0x0FE2, 0x06, 0x834D,
	0x06, 0x0C24, 0x06, 0x5AF0, 0x06, 0x1E12, 0x06, 0xE4F8,
	0x06, 0x8CE5, 0x06, 0xF88D, 0x06, 0xE083, 0x06, 0x30E1,
	0x06, 0x8331, 0x06, 0x6801, 0x06, 0xE4F8, 0x06, 0x8AE5,
	0x06, 0xF88B, 0x06, 0xAE37, 0x06, 0xEE83, 0x06, 0x4E03,
	0x06, 0xE083, 0x06, 0x4CE1,
E 28

D 28
	0x1F, 0x0005, 0x05, 0x8200, 0x06, 0xF8F9,
	0x06, 0xFAEF, 0x06, 0x59EE, 0x06, 0xF8EA,
	0x06, 0x00EE, 0x06, 0xF8EB, 0x06, 0x00E0,
	0x06, 0xF87C, 0x06, 0xE1F8, 0x06, 0x7D59,
	0x06, 0x0FEF, 0x06, 0x0139, 0x06, 0x029E,
	0x06, 0x06EF, 0x06, 0x1039, 0x06, 0x089F,
	0x06, 0x2AEE, 0x06, 0xF8EA, 0x06, 0x00EE,
	0x06, 0xF8EB, 0x06, 0x01E0, 0x06, 0xF87C,
	0x06, 0xE1F8, 0x06, 0x7D58, 0x06, 0x409E,
	0x06, 0x0F39, 0x06, 0x46AA, 0x06, 0x0BBF,
	0x06, 0x8251, 0x06, 0xD682, 0x06, 0x5902,
	0x06, 0x014F, 0x06, 0xAE09, 0x06, 0xBF82,
	0x06, 0x59D6, 0x06, 0x8261, 0x06, 0x0201,
	0x06, 0x4FEF, 0x06, 0x95FE, 0x06, 0xFDFC,
	0x06, 0x054D, 0x06, 0x2000, 0x06, 0x024E,
	0x06, 0x2200, 0x06, 0x024D, 0x06, 0xDFFF,
	0x06, 0x014E, 0x06, 0xDDFF, 0x06, 0x0100,
	0x02, 0x6010, 0x05, 0xFFF6, 0x06, 0x00EC,
	0x05, 0x83D4, 0x06, 0x8200,
E 28
I 28
	0x06, 0x834D, 0x06, 0x1B01, 0x06, 0x9E04, 0x06, 0xAAA1,
	0x06, 0xAEA8, 0x06, 0xEE83, 0x06, 0x4E04, 0x06, 0xEE83,
	0x06, 0x4F00, 0x06, 0xAEAB, 0x06, 0xE083, 0x06, 0x4F78,
	0x06, 0x039F, 0x06, 0x14EE, 0x06, 0x834E, 0x06, 0x05D2,
	0x06, 0x40D6, 0x06, 0x5554, 0x06, 0x0282, 0x06, 0x17D2,
	0x06, 0xA0D6, 0x06, 0xBA00,
E 28

I 28
	0x06, 0x0282, 0x06, 0x17FE, 0x06, 0xFDFC, 0x06, 0x05F8,
	0x06, 0xE0F8, 0x06, 0x60E1, 0x06, 0xF861, 0x06, 0x6802,
	0x06, 0xE4F8, 0x06, 0x60E5, 0x06, 0xF861, 0x06, 0xE0F8,
	0x06, 0x48E1, 0x06, 0xF849, 0x06, 0x580F, 0x06, 0x1E02,
	0x06, 0xE4F8, 0x06, 0x48E5, 0x06, 0xF849, 0x06, 0xD000,
	0x06, 0x0282, 0x06, 0x5BBF,

	0x06, 0x8350, 0x06, 0xEF46, 0x06, 0xDC19, 0x06, 0xDDD0,
	0x06, 0x0102, 0x06, 0x825B, 0x06, 0x0282, 0x06, 0x77E0,
	0x06, 0xF860, 0x06, 0xE1F8, 0x06, 0x6158, 0x06, 0xFDE4,
	0x06, 0xF860, 0x06, 0xE5F8, 0x06, 0x61FC, 0x06, 0x04F9,
	0x06, 0xFAFB, 0x06, 0xC6BF, 0x06, 0xF840, 0x06, 0xBE83,
	0x06, 0x50A0, 0x06, 0x0101,

	0x06, 0x071B, 0x06, 0x89CF, 0x06, 0xD208, 0x06, 0xEBDB,
	0x06, 0x19B2, 0x06, 0xFBFF, 0x06, 0xFEFD, 0x06, 0x04F8,
	0x06, 0xE0F8, 0x06, 0x48E1, 0x06, 0xF849, 0x06, 0x6808,
	0x06, 0xE4F8, 0x06, 0x48E5, 0x06, 0xF849, 0x06, 0x58F7,
	0x06, 0xE4F8, 0x06, 0x48E5, 0x06, 0xF849, 0x06, 0xFC04,
	0x06, 0x4D20, 0x06, 0x0002,

	0x06, 0x4E22, 0x06, 0x0002, 0x06, 0x4DDF, 0x06, 0xFF01,
	0x06, 0x4EDD, 0x06, 0xFF01, 0x06, 0xF8FA, 0x06, 0xFBEF,
	0x06, 0x79BF, 0x06, 0xF822, 0x06, 0xD819, 0x06, 0xD958,
	0x06, 0x849F, 0x06, 0x09BF, 0x06, 0x82BE, 0x06, 0xD682,
	0x06, 0xC602, 0x06, 0x014F, 0x06, 0xEF97, 0x06, 0xFFFE,
	0x06, 0xFC05, 0x06, 0x17FF,

	0x06, 0xFE01, 0x06, 0x1700, 0x06, 0x0102, 0x05, 0x83D8,
	0x06, 0x8051, 0x05, 0x83D6, 0x06, 0x82A0, 0x05, 0x83D4,
	0x06, 0x8000, 0x02, 0x2010, 0x03, 0xDC00, 0x1F, 0x0000,
	0x0B, 0x0600, 0x1F, 0x0005, 0x05, 0xFFF6, 0x06, 0x00FC,
E 28
	0x1F, 0x0000,
I 28

	0x1F, 0x0000, 0x0D, 0xF880, 0x1F, 0x0000,
E 28
};

I 24
D 28
static struct gani_patch gani_8168_m11_patch[] = {
	/* 010 */
	0x1F, 0x0001, 0x06, 0x4064, 0x07, 0x2863,
	0x08, 0x059C, 0x09, 0x26B4, 0x0A, 0x6A19,
	0x0B, 0xACC0, 0x10, 0xF06D, 0x14, 0x7F68,
	0x18, 0x7FD9, 0x1C, 0xF0FF, 0x1D, 0x3D9C,
	0x1F, 0x0003, 0x12, 0xF49F, 0x13, 0x070B,
	0x1A, 0x05AD, 0x14, 0x94C0,
E 28
I 28
static struct gani_patch gani_8168_m10_patch0[] = {
	/* 013 */
	0x1F, 0x0001, 0x06, 0x4064, 0x07, 0x2863, 0x08, 0x059C,
	0x09, 0x26B4, 0x0A, 0x6A19, 0x0B, 0xDCC8, 0x10, 0xF06D,
	0x14, 0x7F68, 0x18, 0x7FD9, 0x1C, 0xF0FF, 0x1D, 0x3D9C,
	0x1F, 0x0003, 0x12, 0xF49F, 0x13, 0x070B, 0x1A, 0x05AD,
	0x14, 0x94C0,
E 28

D 28
	0x1F, 0x0002, 0x06, 0x5571,
E 28
I 28
	0x1F, 0x0002, 0x06, 0x5561, 0x1F, 0x0005, 0x05, 0x8332,
	0x06, 0x5561,
E 28

D 28
	0x1F, 0x0002, 0x05, 0x2642,
E 28
I 28
	0x1F, 0x0000,
};
E 28

D 28
	0x1F, 0x0002, 0x02, 0xC107, 0x03, 0x1002,
E 28
I 28
static struct gani_patch gani_8168_m10_patch1[] = {
	/* 013 */
	0x1F, 0x0005, 0x05, 0xFFC2, 0x1F, 0x0005, 0x05, 0x8000,
	0x06, 0xF8F9, 0x06, 0xFAEE, 0x06, 0xF8EA, 0x06, 0x00EE,
	0x06, 0xF8EB, 0x06, 0x00E2, 0x06, 0xF87C, 0x06, 0xE3F8,
	0x06, 0x7DA5, 0x06, 0x1111, 0x06, 0x12D2, 0x06, 0x40D6,
	0x06, 0x4444, 0x06, 0x0281, 0x06, 0xC6D2, 0x06, 0xA0D6,
	0x06, 0xAAAA, 0x06, 0x0281, 0x06, 0xC6AE, 0x06, 0x0FA5,
	0x06, 0x4444, 0x06, 0x02AE, 0x06, 0x4DA5, 0x06, 0xAAAA,
	0x06, 0x02AE, 0x06, 0x47AF, 0x06, 0x81C2, 0x06, 0xEE83,
	0x06, 0x4E00, 0x06, 0xEE83, 0x06, 0x4D0F, 0x06, 0xEE83,
	0x06, 0x4C0F, 0x06, 0xEE83, 0x06, 0x4F00, 0x06, 0xEE83,
	0x06, 0x5100, 0x06, 0xEE83, 0x06, 0x4AFF, 0x06, 0xEE83,
	0x06, 0x4BFF, 0x06, 0xE083, 0x06, 0x30E1, 0x06, 0x8331,
	0x06, 0x58FE, 0x06, 0xE4F8, 0x06, 0x8AE5, 0x06, 0xF88B,
	0x06, 0xE083, 0x06, 0x32E1, 0x06, 0x8333, 0x06, 0x590F,
	0x06, 0xE283, 0x06, 0x4D0C, 0x06, 0x245A, 0x06, 0xF01E,
	0x06, 0x12E4, 0x06, 0xF88C, 0x06, 0xE5F8, 0x06, 0x8DAF,
	0x06, 0x81C2, 0x06, 0xE083, 0x06, 0x4F10, 0x06, 0xE483,
	0x06, 0x4FE0, 0x06, 0x834E, 0x06, 0x7800, 0x06, 0x9F0A,
	0x06, 0xE083, 0x06, 0x4FA0, 0x06, 0x10A5, 0x06, 0xEE83,
	0x06, 0x4E01, 0x06, 0xE083, 0x06, 0x4E78, 0x06, 0x059E,
	0x06, 0x9AE0, 0x06, 0x834E, 0x06, 0x7804, 0x06, 0x9E10,
	0x06, 0xE083, 0x06, 0x4E78, 0x06, 0x039E, 0x06, 0x0FE0,
	0x06, 0x834E, 0x06, 0x7801, 0x06, 0x9E05, 0x06, 0xAE0C,
	0x06, 0xAF81, 0x06, 0xA7AF, 0x06, 0x8152, 0x06, 0xAF81,
	0x06, 0x8BAF, 0x06, 0x81C2, 0x06, 0xEE83, 0x06, 0x4800,
	0x06, 0xEE83, 0x06, 0x4900, 0x06, 0xE083, 0x06, 0x5110,
	0x06, 0xE483, 0x06, 0x5158, 0x06, 0x019F, 0x06, 0xEAD0,
	0x06, 0x00D1, 0x06, 0x801F, 0x06, 0x66E2, 0x06, 0xF8EA,
	0x06, 0xE3F8, 0x06, 0xEB5A, 0x06, 0xF81E, 0x06, 0x20E6,
	0x06, 0xF8EA, 0x06, 0xE5F8, 0x06, 0xEBD3, 0x06, 0x02B3,
	0x06, 0xFEE2, 0x06, 0xF87C, 0x06, 0xEF32, 0x06, 0x5B80,
	0x06, 0xE3F8, 0x06, 0x7D9E, 0x06, 0x037D, 0x06, 0xFFFF,
	0x06, 0x0D58, 0x06, 0x1C55, 0x06, 0x1A65, 0x06, 0x11A1,
	0x06, 0x90D3, 0x06, 0xE283, 0x06, 0x48E3, 0x06, 0x8349,
	0x06, 0x1B56, 0x06, 0xAB08, 0x06, 0xEF56, 0x06, 0xE683,
	0x06, 0x48E7, 0x06, 0x8349, 0x06, 0x10D1, 0x06, 0x801F,
	0x06, 0x66A0, 0x06, 0x04B9, 0x06, 0xE283, 0x06, 0x48E3,
	0x06, 0x8349, 0x06, 0xEF65, 0x06, 0xE283, 0x06, 0x4AE3,
	0x06, 0x834B, 0x06, 0x1B56, 0x06, 0xAA0E, 0x06, 0xEF56,
	0x06, 0xE683, 0x06, 0x4AE7, 0x06, 0x834B, 0x06, 0xE283,
	0x06, 0x4DE6, 0x06, 0x834C, 0x06, 0xE083, 0x06, 0x4DA0,
	0x06, 0x000C, 0x06, 0xAF81, 0x06, 0x8BE0, 0x06, 0x834D,
	0x06, 0x10E4, 0x06, 0x834D, 0x06, 0xAE04, 0x06, 0x80E4,
	0x06, 0x834D, 0x06, 0xE083, 0x06, 0x4E78, 0x06, 0x039E,
	0x06, 0x0BE0, 0x06, 0x834E, 0x06, 0x7804, 0x06, 0x9E04,
	0x06, 0xEE83, 0x06, 0x4E02, 0x06, 0xE083, 0x06, 0x32E1,
	0x06, 0x8333, 0x06, 0x590F, 0x06, 0xE283, 0x06, 0x4D0C,
	0x06, 0x245A, 0x06, 0xF01E, 0x06, 0x12E4, 0x06, 0xF88C,
	0x06, 0xE5F8, 0x06, 0x8DE0, 0x06, 0x8330, 0x06, 0xE183,
	0x06, 0x3168, 0x06, 0x01E4, 0x06, 0xF88A, 0x06, 0xE5F8,
	0x06, 0x8BAE, 0x06, 0x37EE, 0x06, 0x834E, 0x06, 0x03E0,
	0x06, 0x834C, 0x06, 0xE183, 0x06, 0x4D1B, 0x06, 0x019E,
	0x06, 0x04AA, 0x06, 0xA1AE, 0x06, 0xA8EE, 0x06, 0x834E,
	0x06, 0x04EE, 0x06, 0x834F, 0x06, 0x00AE, 0x06, 0xABE0,
	0x06, 0x834F, 0x06, 0x7803, 0x06, 0x9F14, 0x06, 0xEE83,
	0x06, 0x4E05, 0x06, 0xD240, 0x06, 0xD655, 0x06, 0x5402,
	0x06, 0x81C6, 0x06, 0xD2A0, 0x06, 0xD6BA, 0x06, 0x0002,
	0x06, 0x81C6, 0x06, 0xFEFD, 0x06, 0xFC05, 0x06, 0xF8E0,
	0x06, 0xF860, 0x06, 0xE1F8, 0x06, 0x6168, 0x06, 0x02E4,
	0x06, 0xF860, 0x06, 0xE5F8, 0x06, 0x61E0, 0x06, 0xF848,
	0x06, 0xE1F8, 0x06, 0x4958, 0x06, 0x0F1E, 0x06, 0x02E4,
	0x06, 0xF848, 0x06, 0xE5F8, 0x06, 0x49D0, 0x06, 0x0002,
	0x06, 0x820A, 0x06, 0xBF83, 0x06, 0x50EF, 0x06, 0x46DC,
	0x06, 0x19DD, 0x06, 0xD001, 0x06, 0x0282, 0x06, 0x0A02,
	0x06, 0x8226, 0x06, 0xE0F8, 0x06, 0x60E1, 0x06, 0xF861,
	0x06, 0x58FD, 0x06, 0xE4F8, 0x06, 0x60E5, 0x06, 0xF861,
	0x06, 0xFC04, 0x06, 0xF9FA, 0x06, 0xFBC6, 0x06, 0xBFF8,
	0x06, 0x40BE, 0x06, 0x8350, 0x06, 0xA001, 0x06, 0x0107,
	0x06, 0x1B89, 0x06, 0xCFD2, 0x06, 0x08EB, 0x06, 0xDB19,
	0x06, 0xB2FB, 0x06, 0xFFFE, 0x06, 0xFD04, 0x06, 0xF8E0,
	0x06, 0xF848, 0x06, 0xE1F8, 0x06, 0x4968, 0x06, 0x08E4,
	0x06, 0xF848, 0x06, 0xE5F8, 0x06, 0x4958, 0x06, 0xF7E4,
	0x06, 0xF848, 0x06, 0xE5F8, 0x06, 0x49FC, 0x06, 0x044D,
	0x06, 0x2000, 0x06, 0x024E, 0x06, 0x2200, 0x06, 0x024D,
	0x06, 0xDFFF, 0x06, 0x014E, 0x06, 0xDDFF, 0x06, 0x0100,
	0x05, 0x83D8, 0x06, 0x8000, 0x03, 0xDC00, 0x05, 0xFFF6,
	0x06, 0x00FC, 0x1F, 0x0000,
E 28

I 28
	0x1F, 0x0000, 0x0D, 0xF880, 0x1F, 0x0000,
};

static struct gani_patch gani_8168_m11_patch[] = {
	/* 013 */
	0x1F, 0x0002, 0x10, 0x0008, 0x0D, 0x006C,

	0x1F, 0x0000, 0x0D, 0xF880,

E 28
	0x1F, 0x0001, 0x17, 0x0CC0,

D 28
	0x1F, 0x0002, 0x0F, 0x0017,
E 28
I 28
	0x1F, 0x0001, 0x0B, 0xA4D8, 0x09, 0x281C, 0x07, 0x2883,
	0x0A, 0x6B35, 0x1D, 0x3DA4, 0x1C, 0xEFFD, 0x14, 0x7F52,
	0x18, 0x7FC6, 0x08, 0x0601, 0x06, 0x4063, 0x10, 0xF074,
	0x1F, 0x0003, 0x13, 0x0789, 0x12, 0xF4BD, 0x1A, 0x04FD,
	0x14, 0x84B0, 0x1F, 0x0000, 0x00, 0x9200,
E 28

D 28
	0x1F, 0x0000,
E 28
I 28
	0x1F, 0x0005, 0x01, 0x0340, 0x1F, 0x0001, 0x04, 0x4000,
	0x03, 0x1D21, 0x02, 0x0C32, 0x01, 0x0200, 0x00, 0x5554,
	0x04, 0x4800, 0x04, 0x4000, 0x04, 0xF000, 0x03, 0xDF01,
	0x02, 0xDF20, 0x01, 0x101A, 0x00, 0xA0FF, 0x04, 0xF800,
	0x04, 0xF000, 0x1F, 0x0000,

	0x1F, 0x0007, 0x1E, 0x0023, 0x16, 0x0000, 0x1F, 0x0000,
E 28
};

E 24
#define	GANI_PHY_PATCH(t)	{ \
	int	i;	\
	for (i = 0; i < sizeof (t) / sizeof ((t)[0]); i++) {	\
		gani_mii_write_raw(dp, (t)[i].addr, (t)[i].val);	\
	}	\
}

I 28
#define	GANI_PHY_PATCH_OCP(t)	{ \
	int	i;	\
	for (i = 0; i < sizeof (t) / sizeof ((t)[0]); i++) {	\
		gani_mii_write_ocp(dp, (t)[i].addr, (t)[i].val);	\
	}	\
}

E 28
static void
gani_patch_phy(struct gem_dev *dp)
{
	int		i;
	uint32_t	val;
	struct gani_dev	*lp = dp->private;

	switch (lp->chip->type) {
D 23
	case R8169_CFG_METHOD_2:
	case R8169_CFG_METHOD_3:
E 23
I 23
	case R8169_2: /* RTL8169S rev.D */
	case R8169_3: /* RTL8169S rev.E */
E 23
		GANI_PHY_PATCH(gani_8169_m2_patch);
		break;

D 23
	case R8169_CFG_METHOD_4:
E 23
I 23
	case R8169_4: /* RTL8169SB */
E 23
		GANI_PHY_PATCH(gani_8169_m4_patch);
		break;

D 23
	case R8169_CFG_METHOD_5:
E 23
I 23
	case R8169_5: /* RTL8169SC rev.D */
E 23
D 24
		GANI_PHY_PATCH(gani_8169_m5_patch);
E 24
I 24
		GANI_PHY_PATCH(gani_8169_m5_patch0);
		if (lp->svid == 0x1458 && lp->sdid == 0xe000) {
			GANI_PHY_PATCH(gani_8169_m5_patch1);
		}
E 24
		break;

D 23
	case R8169_CFG_METHOD_6:
E 23
I 23
	case R8169_6: /* RTL8169SC rev.E */
E 23
D 24
		GANI_PHY_PATCH(gani_8169_m6_patch0);
		if (lp->svid == 0x1458 && lp->sdid == 0xe000) {
			GANI_PHY_PATCH(gani_8169_m6_patch1);
E 22
		}
I 22
		GANI_PHY_PATCH(gani_8169_m6_patch2);
E 24
I 24
		GANI_PHY_PATCH(gani_8169_m6_patch);
E 24
E 22
		break;
D 22
	}
	case MAC_VER_8169SB: /* M4 */
D 21
#if 0
		gani_mii_write(dp, 0x1f, 0x0001);
E 16
		gani_mii_write(dp, 0x1b, 0x841e);
I 16
		gani_mii_write(dp, 0x0e, 0x7bfb);
		gani_mii_write(dp, 0x09, 0x273a);
#endif
E 21
		gani_mii_write(dp, 0x1f, 0x0002);
		gani_mii_write(dp, 0x01, 0x90d0);
		gani_mii_write(dp, 0x1f, 0x0000);
E 22
I 22

D 23
	case R8168_CFG_METHOD_1: /* MAC_VER_8168B_B */
E 23
I 23
	case R8168_1: /* RTL8168B rev.B */
E 23
D 24
		gani_mii_write_raw(dp, 0x1f, 0x0001);
		gani_mii_write_raw(dp, 0x16, gani_mii_read_raw(dp, 0x16) | 1);
		gani_mii_write_raw(dp, 0x10, 0xf41b);
		gani_mii_write_raw(dp, 0x1f, 0x0000);
E 24
I 24
		GANI_PHY_PATCH(gani_8168_m1_patch);
E 24
E 22
		break;
I 22

D 23
	case R8168_CFG_METHOD_2: /* MAC_VER_8168B_E */
	case R8168_CFG_METHOD_3: /* MAC_VER_8168B_F */
E 23
I 23
	case R8168_2: /* RTL8168B rev.E */
D 24
	case R8168_3: /* RTL8168B rev.F */
E 24
E 23
		GANI_PHY_PATCH(gani_8168_m2_patch);
		break;

I 24
	case R8168_3: /* RTL8168B rev.F */
		GANI_PHY_PATCH(gani_8168_m3_patch);
		break;

E 24
D 23
	case R8168_CFG_METHOD_4: /* MAC_VER_8168C */
E 23
I 23
	case R8168_4: /* RTL8168C */
I 28
		/* 013 */
E 28
E 23
		GANI_PHY_PATCH(gani_8168_m4_patch);

D 24
		gani_mii_write_raw(dp, 0x1f, 0x0000);
E 24
		gani_mii_write_raw(dp, 0x14,
		    gani_mii_read_raw(dp, 0x14) | 0x0020);
D 24
		gani_mii_write_raw(dp, 0x0d,
		    gani_mii_read_raw(dp, 0x0d) | 0x0020);
E 24
I 24
D 28
		gani_mii_write_raw(dp, 0x0D,
		    gani_mii_read_raw(dp, 0x0D) | 0x0020);
E 24
		gani_mii_write_raw(dp, 0x1f, 0x0000);
E 28
I 28
		gani_mii_write_raw(dp, 0x0d,
		    gani_mii_read_raw(dp, 0x0d) & ~0x0020);
E 28
		break;

D 23
	case R8168_CFG_METHOD_5: /* MAC_VER_8168C_B */
E 23
I 23
	case R8168_5: /* RTL8168C rev.B */
E 23
		GANI_PHY_PATCH(gani_8168_m5_patch0);

D 24
		gani_mii_write_raw(dp, 0x1f, 0x0000);
E 24
		gani_mii_write_raw(dp, 0x16,
		    gani_mii_read_raw(dp, 0x16) | 0x0001);
I 28

		gani_mii_write_raw(dp, 0x1F, 0x0000);
E 28
		gani_mii_write_raw(dp, 0x14,
		    gani_mii_read_raw(dp, 0x14) | 0x0020);
D 24
		gani_mii_write_raw(dp, 0x0d,
		    gani_mii_read_raw(dp, 0x0d) | 0x0020);
E 24
I 24
		gani_mii_write_raw(dp, 0x0D,
D 28
		    gani_mii_read_raw(dp, 0x0D) | 0x0020);
E 28
I 28
		    gani_mii_read_raw(dp, 0x0D) & ~0x0020);
E 28
E 24

		GANI_PHY_PATCH(gani_8168_m5_patch1);
		break;

D 23
	case R8168_CFG_METHOD_6: /* MAC_VER_8168C_C */
E 23
I 23
	case R8168_6: /* RTL8168C rev.C */
E 23
		GANI_PHY_PATCH(gani_8168_m6_patch0);

D 24
		gani_mii_write_raw(dp, 0x1f, 0x0000);
E 24
		gani_mii_write_raw(dp, 0x16,
		    gani_mii_read_raw(dp, 0x16) | 0x0001);
I 28

		gani_mii_write_raw(dp, 0x1F, 0x0000);
E 28
		gani_mii_write_raw(dp, 0x14,
		    gani_mii_read_raw(dp, 0x14) | 0x0020);
D 28
		gani_mii_write_raw(dp, 0x0d,
		    gani_mii_read_raw(dp, 0x0d) | 0x0020);
E 28
I 28
		gani_mii_write_raw(dp, 0x0D,
		    gani_mii_read_raw(dp, 0x0D) & ~0x0020);
E 28

		GANI_PHY_PATCH(gani_8168_m6_patch1);
		break;

D 23
	case R8168_CFG_METHOD_7: /* MAC_VER_8168CP */
E 23
I 23
	case R8168_7: /* RTL8168CP rev.B */
E 23
D 28
		gani_mii_write_raw(dp, 0x1f, 0x0000);
E 28
I 28
		gani_mii_write_raw(dp, 0x1F, 0x0000);
E 28
		gani_mii_write_raw(dp, 0x14,
		    gani_mii_read_raw(dp, 0x14) | 0x0020);
D 24
		gani_mii_write_raw(dp, 0x0d,
		    gani_mii_read_raw(dp, 0x0d) | 0x0020);
E 24
I 24
		gani_mii_write_raw(dp, 0x0D,
D 28
		    gani_mii_read_raw(dp, 0x0D) | 0x0020);
E 28
I 28
		    gani_mii_read_raw(dp, 0x0D) & ~0x0020);
E 28

E 24
		GANI_PHY_PATCH(gani_8168_m7_patch);
		break;

D 23
	case R8168_CFG_METHOD_8: /* MAC_VER_8168CP_B */
E 23
I 23
	case R8168_8: /* RTL8168CP rev.C */
E 23
D 24
		gani_mii_write_raw(dp, 0x1f, 0x0000);
		gani_mii_write_raw(dp, 0x0d,
		    gani_mii_read_raw(dp, 0x0d) | 0x0020);
E 24
I 24
		gani_mii_write_raw(dp, 0x1F, 0x0000);
I 28
		gani_mii_write_raw(dp, 0x14,
		    gani_mii_read_raw(dp, 0x14) | 0x0020);
E 28
		gani_mii_write_raw(dp, 0x0D,
D 28
		    gani_mii_read_raw(dp, 0x0D) | 0x0020);
E 28
I 28
		    gani_mii_read_raw(dp, 0x0D) & ~0x0020);
E 28

E 24
		GANI_PHY_PATCH(gani_8168_m8_patch);
I 28

		gani_mii_write_raw(dp, 0x16,
		    gani_mii_read_raw(dp, 0x16) | 0x0001);
		gani_mii_write_raw(dp, 0x1F, 0x0000);
E 28
		break;

D 23
	case R8168_CFG_METHOD_9:
E 23
I 23
	case R8168_9: /* RTL8168D */
E 23
D 24
		GANI_PHY_PATCH(gani_8168_m9_patch0);

		gani_mii_write_raw(dp, 0x1F, 0x0002);
		gani_mii_write_raw(dp, 0x0C,
		    0x0300 | (gani_mii_read_raw(dp, 0x0D) & 0x00FF));

		GANI_PHY_PATCH(gani_8168_m9_patch1);
E 24
I 24
D 28
		GANI_PHY_PATCH(gani_8168_m9_patch);
E 28
I 28
D 31
#ifdef CONFIG_PATCH_8168D
E 31
I 31
#if 1 /* defined(CONFIG_PATCH_8168D) tested */
E 31
		GANI_PHY_PATCH(gani_8168_m9_patch0);

		gani_mii_write_raw(dp, 0x1F, 0x0002);
		val = gani_mii_read_raw(dp, 0x0B) & 0xFF00;
		val |= 0x10;
		gani_mii_write_raw(dp, 0x0B, val);
		val = gani_mii_read_raw(dp, 0x0C) & 0x00FF;
		val |= 0xA200;
		gani_mii_write_raw(dp, 0x0C, val);

		/* 013 */
		gani_mii_write_raw(dp, 0x1F, 0x0002);
		gani_mii_write_raw(dp, 0x06, 0x5561);
		gani_mii_write_raw(dp, 0x1F, 0x0005);
		gani_mii_write_raw(dp, 0x05, 0x8332);
		gani_mii_write_raw(dp, 0x06, 0x5561);

		if (gani_efuse_read(dp, 0x01) == 0xb1) {
			/* 013 */
			gani_mii_write_raw(dp, 0x1F, 0x0002);
			gani_mii_write_raw(dp, 0x05, 0x669A);
			gani_mii_write_raw(dp, 0x1F, 0x0005);
			gani_mii_write_raw(dp, 0x05, 0x8330);
			gani_mii_write_raw(dp, 0x06, 0x669A);

			gani_mii_write_raw(dp, 0x1F, 0x0002);
			val = gani_mii_read_raw(dp, 0x0D);
			if ((val & 0x00FF) != 0x006C) {
				/* 013 */
				val &= 0xFF00;
				gani_mii_write_raw(dp, 0x1F, 0x0002);
				gani_mii_write_raw(dp, 0x0D, val | 0x0065);
				gani_mii_write_raw(dp, 0x0D, val | 0x0066);
				gani_mii_write_raw(dp, 0x0D, val | 0x0067);
				gani_mii_write_raw(dp, 0x0D, val | 0x0068);
				gani_mii_write_raw(dp, 0x0D, val | 0x0069);
				gani_mii_write_raw(dp, 0x0D, val | 0x006A);
				gani_mii_write_raw(dp, 0x0D, val | 0x006B);
				gani_mii_write_raw(dp, 0x0D, val | 0x006C);
			}
		} else {
			/* 013 */
			gani_mii_write_raw(dp, 0x1F, 0x0002);
			gani_mii_write_raw(dp, 0x05, 0x6662);
			gani_mii_write_raw(dp, 0x1F, 0x0005);
			gani_mii_write_raw(dp, 0x05, 0x8330);
			gani_mii_write_raw(dp, 0x06, 0x6662);
		}

		gani_mii_write_raw(dp, 0x1F, 0x0002);
		val = gani_mii_read_raw(dp, 0x0D);
		val |= 0x0300;
		gani_mii_write_raw(dp, 0x0D, val);
		val = gani_mii_read_raw(dp, 0x0F);
		val |= 0x0010;
		gani_mii_write_raw(dp, 0x0F, val);

		gani_mii_write_raw(dp, 0x1F, 0x0002);
		val = gani_mii_read_raw(dp, 0x02);
		val &= ~0x0600;
		val |= 0x0100;
		gani_mii_write_raw(dp, 0x02, val);
		val = gani_mii_read_raw(dp, 0x03);
		val &= ~0xe000;
		gani_mii_write_raw(dp, 0x03, val);

		GANI_PHY_PATCH(gani_8168_m9_patch1);
#endif /* CONFIG_PATCH_8168D */
E 28
E 24
		break;

D 23
	case R8168_CFG_METHOD_10:
E 23
I 23
D 28
	case R8168_10: /* RTL8168D rev.B */
E 23
		GANI_PHY_PATCH(gani_8168_m10_patch);
E 28
I 28
	case R8168_10: /* RTL8168D rev.C */
#ifdef CONFIG_PATCH_8168D_C
		GANI_PHY_PATCH(gani_8168_m10_patch0);

		if (gani_efuse_read(dp, 0x01) == 0xb1) {
			/* 013 */
			gani_mii_write_raw(dp, 0x1F, 0x0002);
			gani_mii_write_raw(dp, 0x05, 0x669A);
			gani_mii_write_raw(dp, 0x1F, 0x0005);
			gani_mii_write_raw(dp, 0x05, 0x8330);
			gani_mii_write_raw(dp, 0x06, 0x669A);

			gani_mii_write_raw(dp, 0x1F, 0x0002);
			val = gani_mii_read_raw(dp, 0x0D);
			if ((val & 0x00FF) != 0x006C) {
				/* 013 */
				val &= 0xFF00;
				gani_mii_write_raw(dp, 0x1F, 0x0002);
				gani_mii_write_raw(dp, 0x0D, val | 0x0065);
				gani_mii_write_raw(dp, 0x0D, val | 0x0066);
				gani_mii_write_raw(dp, 0x0D, val | 0x0067);
				gani_mii_write_raw(dp, 0x0D, val | 0x0068);
				gani_mii_write_raw(dp, 0x0D, val | 0x0069);
				gani_mii_write_raw(dp, 0x0D, val | 0x006A);
				gani_mii_write_raw(dp, 0x0D, val | 0x006B);
				gani_mii_write_raw(dp, 0x0D, val | 0x006C);
			}
		} else {
			/* 013 */
			gani_mii_write_raw(dp, 0x1F, 0x0002);
			gani_mii_write_raw(dp, 0x05, 0x2642);
			gani_mii_write_raw(dp, 0x1F, 0x0005);
			gani_mii_write_raw(dp, 0x05, 0x8330);
			gani_mii_write_raw(dp, 0x06, 0x2642);
		}

		/* 013 */
		gani_mii_write_raw(dp, 0x1F, 0x0002);
		val = gani_mii_read_raw(dp, 0x02);
		val &= ~0x0600;
		val |= 0x0100;
		gani_mii_write_raw(dp, 0x02, val);
		val = gani_mii_read_raw(dp, 0x03);
		val &= ~0xe000;
		gani_mii_write_raw(dp, 0x03, val);

		gani_mii_write_raw(dp, 0x1F, 0x0001);
		gani_mii_write_raw(dp, 0x17, 0x0CC0);

		gani_mii_write_raw(dp, 0x1F, 0x0002);
		val = gani_mii_read_raw(dp, 0x0F);
		val |= 0x0017;
		gani_mii_write_raw(dp, 0x0F, val);

		GANI_PHY_PATCH(gani_8168_m10_patch1);
#endif /* CONFIG_PATCH_8168D_C */
E 28
		break;

I 24
D 28
	case R8168_11: /* RTL8168D rev.C */
		GANI_PHY_PATCH(gani_8168_m11_patch);
E 28
I 28
	case R8168_11: /* RTL8168DP */
#ifdef CONFIG_PATCH_8168DP
		/* 013 */
		GANI_PHY_PATCH_OCP(gani_8168_m11_patch);
#endif
E 28
		break;

I 28
	case R8168_12:
		break;

	case R8168_13:
		break;

	case R8168_14:
		break;

E 28
E 24
D 23
	case R8101_CFG_METHOD_4:
	case R8101_CFG_METHOD_5:
	case R8101_CFG_METHOD_6:
E 23
I 23
	case R8101_4: /* RTL8102E */
	case R8101_5: /* RTL8102E rev.B */
I 28
		/* 015 */
E 28
D 24
	case R8101_6: /* RTL8103E */
E 24
E 23
		gani_mii_write_raw(dp, 0x1f, 0x0000);
		gani_mii_write_raw(dp, 0x11,
		    gani_mii_read_raw(dp, 0x11) | 0x1000);
		gani_mii_write_raw(dp, 0x19,
		    gani_mii_read_raw(dp, 0x19) | 0x2000);
		gani_mii_write_raw(dp, 0x10,
		    gani_mii_read_raw(dp, 0x10) | 0x8000);

		gani_mii_write_raw(dp, 0x1f, 0x0003);
		gani_mii_write_raw(dp, 0x08, 0x441D);
		gani_mii_write_raw(dp, 0x01, 0x9100);

		gani_mii_write_raw(dp, 0x1f, 0x0000);
		break;
I 24

	case R8101_6: /* RTL8103E */
I 28
		/* 015 */
E 28
		gani_mii_write_raw(dp, 0x1f, 0x0000);
		gani_mii_write_raw(dp, 0x11,
		    gani_mii_read_raw(dp, 0x11) | 0x1000);
		gani_mii_write_raw(dp, 0x19,
		    gani_mii_read_raw(dp, 0x19) | 0x2000);
		gani_mii_write_raw(dp, 0x10,
		    gani_mii_read_raw(dp, 0x10) | 0x8000);

		gani_mii_write_raw(dp, 0x1f, 0x0003);
		gani_mii_write_raw(dp, 0x08, 0x441D);

		gani_mii_write_raw(dp, 0x1f, 0x0000);
		break;
I 28

	case R8101_8: /* RTL8401E */
		gani_phyio_write(dp, 0x0e, 0x0068);
		gani_phyio_write(dp, 0x0e, 0x0069);
		gani_phyio_write(dp, 0x0e, 0x006a);
		gani_phyio_write(dp, 0x0e, 0x006b);
		gani_phyio_write(dp, 0x0e, 0x000c);
		break;
E 28
E 24
E 22
E 16
E 4
D 21

I 4
D 16
		gani_mii_write(dp, 0x1F, 0x0002);
		gani_mii_write(dp, 0x01, 0x90D0);
		gani_mii_write(dp, 0x1F, 0x0000);
	}
E 16
I 16
	case MAC_VER_8168: /* M5 */
		gani_mii_write(dp, 0x1f, 0x0001);
		gani_mii_write(dp, 0x06, 0x00aa);
		gani_mii_write(dp, 0x07, 0x3173);
		gani_mii_write(dp, 0x08, 0x08fc);
		gani_mii_write(dp, 0x09, 0xe2d0);
		gani_mii_write(dp, 0x0b, 0x941a);
		gani_mii_write(dp, 0x18, 0x65fe);
		gani_mii_write(dp, 0x1c, 0x1e02);
		gani_mii_write(dp, 0x1f, 0x0000);
		break;
E 16

E 4
D 10
	if (lp->chip->type == MAC_VER_D) {
E 10
I 10
D 16
	if (lp->chip->type == MAC_VER_D /* M2 */) {
E 16
I 16
	case MAC_VER_8168B: /* M6 */
		gani_mii_write(dp, 0x1f, 0x0001);
		gani_mii_write(dp, 0x0b, 0x94b0);
		gani_mii_write(dp, 0x1b, 0xc416);
		gani_mii_write(dp, 0x1f, 0x0003);
		gani_mii_write(dp, 0x12, 0x6096);
		gani_mii_write(dp, 0x1f, 0x0000);
		break;

	case MAC_VER_8100E: /* M7 */
	case MAC_VER_8101E: /* M7 */
		/* do nothing */
		break;
E 21
	}
D 21
#if 0
	if (lp->chip->type == MAC_VER_8169S_D /* M2 */) {
E 16
E 10
		OUTB(dp, 0x82, 0x01);
D 4
		gani_mii_write(dp, 12, 0x0000);
E 4
I 4
		gani_mii_write(dp, 0xb, 0x0000);
E 4
	}
I 16
#endif
E 21
}
E 16

I 16
static int
I 22
gani_mii_probe(struct gem_dev *dp)
{
I 30
	uint_t	val;
	int	ret = GEM_SUCCESS;

E 30
	/* select page 0 */
D 29
	gani_mii_write_raw(dp, 0x1f, 0x0000);
E 29
I 29
D 30
	gem_mii_write(dp, 0x1f, 0x0000);
E 30
I 30
	sema_p(&dp->hal_op_lock);
	gani_mii_write_raw(dp, 0x1f, 0x0000);
E 30
E 29

D 29
	return (gem_mii_probe_default(dp));
E 29
I 29
D 30
	dp->mii_status = gem_mii_read(dp, MII_STATUS);
E 30
I 30
	dp->mii_status = gani_mii_read_raw(dp, MII_STATUS);
E 30
	if (dp->mii_status == 0xffff || dp->mii_status == 0) {
		cmn_err(CE_NOTE,
		    "!%s: failed to probe default internal and/or non-MII PHY",
		    dp->name);
D 30
		return (GEM_FAILURE);
E 30
I 30
		ret = GEM_FAILURE;
		goto x;
E 30
	}

I 30
	/* ensure phy is powered up */
	val = gani_mii_read_raw(dp, MII_CONTROL);
	gani_mii_write_raw(dp, MII_CONTROL,
	    val & (MII_CONTROL_SPEED | MII_CONTROL_ANE));

E 30
	dp->mii_status_ro = ~dp->mii_status;
D 30
	dp->mii_phy_id  = (gem_mii_read(dp, MII_PHYIDH) << 16) |
	    gem_mii_read(dp, MII_PHYIDL);
E 30
I 30
	dp->mii_phy_id  = (gani_mii_read_raw(dp, MII_PHYIDH) << 16) |
	    gani_mii_read_raw(dp, MII_PHYIDL);
E 30

	cmn_err(CE_CONT, "!%s: using internal/non-MII PHY(0x%08x)",
	    dp->name, dp->mii_phy_id);

	cmn_err(CE_CONT,
	    "!%s: PHY control:%b, status:%b, advert:%b, lpar:%b, exp:%b",
	    dp->name,
D 30
	    gem_mii_read(dp, MII_CONTROL), MII_CONTROL_BITS,
E 30
I 30
	    gani_mii_read_raw(dp, MII_CONTROL), MII_CONTROL_BITS,
E 30
	    dp->mii_status, MII_STATUS_BITS,
D 30
	    gem_mii_read(dp, MII_AN_ADVERT), MII_ABILITY_BITS,
	    gem_mii_read(dp, MII_AN_LPABLE), MII_ABILITY_BITS,
	    gem_mii_read(dp, MII_AN_EXPANSION), MII_AN_EXP_BITS);
E 30
I 30
	    gani_mii_read_raw(dp, MII_AN_ADVERT), MII_ABILITY_BITS,
	    gani_mii_read_raw(dp, MII_AN_LPABLE), MII_ABILITY_BITS,
	    gani_mii_read_raw(dp, MII_AN_EXPANSION), MII_AN_EXP_BITS);
E 30

	dp->mii_xstatus = 0;
	if (dp->mii_status & MII_STATUS_XSTATUS) {
D 30
		dp->mii_xstatus = gem_mii_read(dp, MII_XSTATUS);
E 30
I 30
		dp->mii_xstatus = gani_mii_read_raw(dp, MII_XSTATUS);
E 30

		cmn_err(CE_CONT, "!%s: xstatus:%b",
		    dp->name, dp->mii_xstatus, MII_XSTATUS_BITS);

		dp->mii_xstatus &=
		    ~ (MII_XSTATUS_1000BASET | MII_XSTATUS_1000BASEX);
	}
	dp->mii_xstatus_ro = ~dp->mii_xstatus;
D 30

E 30
I 30
x:
	sema_v(&dp->hal_op_lock);
E 30
	return (GEM_SUCCESS);
E 29
}

static int
E 22
gani_mii_init(struct gem_dev *dp)
{
D 22
	int			ret;
	struct gani_dev		*lp = (struct gani_dev *)dp->private;
E 22
I 22
	struct gani_dev		*lp = dp->private;
E 22

E 16
D 13
	return gem_mii_init_default(dp);
E 13
I 13
D 22
	ret = gem_mii_init_default(dp);
E 22
I 22
D 29
	/* select page 0 */
	gani_mii_write_raw(dp, 0x1f, 0x0000);
E 22

E 29
I 23
	/* install latest patch for phy */
I 30
	sema_p(&dp->hal_op_lock);
E 30
E 23
D 16
	if (lp->chip->type >= MAC_VER_D/*M2*/ && (dp->mii_phy_id & 0xf) <= 1) {
E 16
I 16
D 22
	gani_mii_patch(dp);
E 22
I 22
	gani_patch_phy(dp);
I 23

I 29
	/* select page 0 */
	gani_mii_write_raw(dp, 0x1f, 0x0000);

E 29
E 23
D 28
	if (GANI_PCI(lp->chip->type)) {
E 28
I 28
	if (GANI_PCI(lp)) {
E 28
		OUTB(dp, 0x82, 1);
		/* XXX - set pci latency timer to 0x40 */
D 23
		if (lp->chip->type == R8169_CFG_METHOD_2) {
E 23
I 23
		if (lp->chip->type == R8169_2 /* RTL8169S rev.D */) {
E 23
			OUTB(dp, 0x82, 1);
			gani_mii_write_raw(dp, 0x0b, 0x0000);
		}
D 23
	}
E 23
E 22

D 22
	if (lp->chip->type >= MAC_VER_8169S_D &&
	    (dp->mii_phy_id & 0xf) <= 1 &&
	    dp->anadv_1000fdx) {
E 16
		/* fix linkdown timeout action */
		dp->gc.gc_mii_linkdown_timeout_action = MII_ACTION_RESET;
E 22
I 22
D 23
	/* power up */
	if (GANI_PCI(lp->chip->type) || GANI_PCIE_GIGA(lp->chip->type)) {
		gani_mii_write_raw(dp, 0x1f, 0x0000);
E 23
I 23
		/* power up */
E 23
		gani_mii_write_raw(dp, 0x0e, 0x0000);
E 22
	}

I 28
	if (GANI_PCIE_GIGA(lp)) {
		switch (lp->chip->type) {
		case R8168_9:
		case R8168_10:
		case R8168_12:
		case R8168_14:
		case R8168_15:
			OUTB(dp, PMCH, INB(dp, PMCH) | 0x80);
		}

D 30
		if (lp->chip->type != R8168_11) {
			/* power up */
E 30
I 30
		/* power up */
		switch (lp->chip->type) {
		case R8168_14:
		case R8168_15:
			break;
		default:
E 30
			gani_mii_write_raw(dp, 0x0e, 0x0000);
I 30
			break;
E 30
		}
I 30
		gani_mii_write_raw(dp, MII_CONTROL, MII_CONTROL_ANE);
E 30
	}
I 30
	sema_v(&dp->hal_op_lock);
E 30

E 28
I 22
	return (GEM_SUCCESS);
}

static int
gani_mii_config(struct gem_dev *dp)
{
	int		ret;
	uint16_t	val;
I 29
	uint_t		anadv_1000hdx_org;
E 29
	struct gani_dev	*lp = dp->private;

	/*
	 * rtl816x nics seem to have a problem in forced mode. The link
	 * never go up again after once it become down from up.
	 */
D 23
	if (!dp->anadv_autoneg && dp->speed == GEM_SPD_1000) {
E 23
I 23
	if ((!dp->anadv_autoneg) && dp->speed == GEM_SPD_1000) {
E 23
		cmn_err(CE_NOTE,
		    "!%s: rtl816x series does not support fixed mode for "
		    "1Gbps connection. "
		    "limited auto negotiation capability is used "
		    "instead of given forced mode.",
		    dp->name);
		dp->anadv_1000fdx = B_TRUE;
		dp->anadv_1000hdx = B_FALSE;
D 23
		dp->anadv_100fdx = B_FALSE;
		dp->anadv_100hdx = B_FALSE;
		dp->anadv_10fdx = B_FALSE;
		dp->anadv_10hdx = B_FALSE;

E 23
I 23
		dp->anadv_100fdx = B_TRUE;
		dp->anadv_100hdx = B_TRUE;
		dp->anadv_10fdx = B_TRUE;
		dp->anadv_10hdx = B_TRUE;
#ifdef SANITY
E 23
		dp->full_duplex = B_TRUE;
I 23
#endif
E 23
		dp->anadv_autoneg = B_TRUE;
	}

	/*
	 * the datasheet says rtl816x doesn't support 1Gbps half duplex
D 29
	 * mode, but phys in rtl8168 seem to require 1000hdx bit
	 * set in 1000TC register for 1G bps negotiation.
E 29
I 29
	 * mode, but the phy unit in rtl8168 seem to require 1000hdx bit
	 * in 1000TC register set for 1G bps negotiation.
E 29
	 */
I 29
	anadv_1000hdx_org = dp->anadv_1000hdx;
E 29
	dp->anadv_1000hdx = dp->anadv_1000fdx;

I 23
D 28
	if (GANI_PCI(lp->chip->type) &&
E 28
I 28
	if (GANI_PCI(lp) &&
E 28
	    dp->anadv_autoneg && dp->anadv_1000fdx &&
	    (dp->anadv_100fdx | dp->anadv_100hdx |
	    dp->anadv_10fdx | dp->anadv_10hdx) == B_FALSE) {
		/*
		 * At least one capability in 100Mbps or 10Mbps should be
		 * enabled. Otherwise autonegotion will timeout.
		 */
		dp->anadv_100fdx = B_TRUE;
		dp->anadv_100hdx = B_TRUE;
		dp->anadv_10fdx = B_TRUE;
		dp->anadv_10hdx = B_TRUE;
	}

E 23
	/* select page 0 */
I 30
	sema_p(&dp->hal_op_lock);
E 30
	gani_mii_write_raw(dp, 0x1f, 0x0000);

I 23
D 28
	if (GANI_PCIE_GIGA(lp->chip->type) && dp->anadv_autoneg) {
E 28
I 28
D 29
#ifdef notdef
E 29
	if (GANI_PCIE_GIGA(lp) && dp->anadv_autoneg) {
E 28
		/* power up phy */
D 29
		gani_mii_write_raw(dp, 0x0e, 0x0000);
E 29
I 29
		switch (lp->chip->type) {
		case R8168_14:
		case R8168_15:
			break;
		default:
			gani_mii_write_raw(dp, 0x0e, 0x0000);
			break;
		}
		gani_mii_write_raw(dp, MII_CONTROL, MII_CONTROL_ANE);
E 29

D 28
	} else if (GANI_PCIE_FAST(lp->chip->type)) {
E 28
I 28
	} else if (GANI_PCIE_FAST(lp) && dp->anadv_autoneg) {
E 28
		switch (lp->chip->type) {
		case R8101_1: /* RTL8101E rev.B */
		case R8101_2: /* RTL8101E rev.E */
		case R8101_3: /* RTL8101E rev.F */
D 28
			if (dp->anadv_autoneg || dp->speed != GEM_SPD_10) {
E 28
I 28
			if (dp->anadv_100fdx || dp->anadv_100hdx) {
E 28
				break;
			}
			/* FALL THROU */

		case R8101_4: /* RTL8102E */
I 28
		case R8101_5: /* RTL8102E rev.B */
E 28
D 24
		case R8101_5: /* RTL8102E rev.B */
E 24
D 29
			gani_mii_write_raw(dp, MII_CONTROL, MII_CONTROL_RESET);
E 29
I 29
			gani_mii_write_raw(dp,
			    MII_CONTROL, MII_CONTROL_RESET);
E 29
			drv_usecwait(100);
I 29
			gani_patch_phy(dp);

			/* select page 0 */
			gani_mii_write_raw(dp, 0x1f, 0x0000);
E 29
			break;
		}
	}
I 30
	sema_v(&dp->hal_op_lock);
E 30
D 28

E 28
I 28
D 29
#endif
E 29
E 28
E 23
	ret = gem_mii_config_default(dp);
I 30
	sema_p(&dp->hal_op_lock);
E 30

D 28
	if (GANI_PCIE_FAST(lp->chip->type)) {
E 28
I 28
D 29
	if (GANI_PCIE_FAST(lp)) {
E 28
		if (dp->anadv_autoneg) {
			gani_patch_phy(dp);
		}
D 28
	} else if (GANI_PCI(lp->chip->type)) {
D 23
		if (lp->chip->type == R8169_CFG_METHOD_2 ||
		    lp->chip->type == R8169_CFG_METHOD_3) {
E 23
I 23
		if (lp->chip->type == R8169_2 /* RTL8169S rev.D */ ||
		    lp->chip->type == R8169_3 /* RTL8169S rev.E */) {
E 23
			if (!dp->anadv_autoneg && dp->speed == GEM_SPD_100) {
				gani_mii_write_raw(dp, 0x17, 0x2138);
				gani_mii_write_raw(dp, 0x0e, 0x0260);
			} else {
				gani_mii_write_raw(dp, 0x17, 0x2108);
				gani_mii_write_raw(dp, 0x0e, 0x0000);
			}
E 28
I 28
	} else if (lp->chip->type == R8169_2 /* RTL8169S rev.D */ ||
E 29
I 29
	dp->anadv_1000hdx = anadv_1000hdx_org;

	if (lp->chip->type == R8169_2 /* RTL8169S rev.D */ ||
E 29
	    lp->chip->type == R8169_3 /* RTL8169S rev.E */) {
D 29
		if (!dp->anadv_autoneg && dp->speed == GEM_SPD_100) {
E 29
I 29
		if ((!dp->anadv_autoneg) && dp->speed == GEM_SPD_100) {
E 29
			gani_mii_write_raw(dp, 0x17, 0x2138);
			gani_mii_write_raw(dp, 0x0e, 0x0260);
		} else {
			gani_mii_write_raw(dp, 0x17, 0x2108);
			gani_mii_write_raw(dp, 0x0e, 0x0000);
E 28
		}
	}
I 30
	sema_v(&dp->hal_op_lock);
E 30
E 22
D 16
	return ret;
E 16
I 16
	return (ret);
E 16
E 13
}

/* ======================================================== */
/*
 * OS depend (device driver kernel interface) routine
 */
/* ======================================================== */
I 16
D 26
#ifdef CONFIG_EEPROM_IO
E 26
D 22
#define	gani_eeprom_delay(dp)	{INB(dp, CR9346); INB(dp, CR9346);}
E 22
I 22
#define	gani_eeprom_delay(dp)	\
D 28
	{ (void) INB(dp, CR9346); (void) INB(dp, CR9346); }
E 28
I 28
	{ (void) INB(dp, CR9346); drv_usecwait(3); }
E 28
E 22

static uint16_t
gani_read_eeprom(struct gem_dev *dp, int addr)
{
	int		i;
	int		addr_bits;
	uint_t		cmd;
	uint8_t		chip_select;
	uint8_t		di;
	uint16_t	ret;
D 22
	struct gani_dev	*lp = (struct gani_dev *)dp->private;
E 22

D 22
	addr_bits = ((INL(dp, RCR) & RCR_9356SEL) != 0) ? 8 : 6;
E 22
I 22
	addr_bits = (INL(dp, RCR) & RCR_9356SEL) ? 8 : 6;
E 22

D 22
	DPRINTF(2, (CE_CONT, "!%s: gani_read_eeprom: called: addr_bits:%d",
			dp->name, addr_bits));
E 22
I 22
D 26
	DPRINTF(2, (CE_CONT, "!%s: %s: called: addr_bits:%d",
E 26
I 26
	DPRINTF(4, (CE_CONT, "!%s: %s: called: addr_bits:%d",
E 26
	    dp->name, __func__, addr_bits));
E 22

	/* make command bits */
	cmd = (6 << addr_bits) | addr;

	/* enable eeprom interface register */
D 28
	chip_select = CR9346_EEM_PROGRAM;
E 28
I 28
	chip_select = INB(dp, CR9346);
	chip_select &= ~(CR9346_EEDI | CR9346_EEDO | CR9346_EEM | CR9346_EESK);
	chip_select |= CR9346_EEM_PROGRAM | CR9346_EECS;
E 28
	OUTB(dp, CR9346, chip_select);
D 28

	chip_select |= CR9346_EECS;
	OUTB(dp, CR9346, chip_select);
E 28
	gani_eeprom_delay(dp);

	/* output eeprom command */
D 28
	for (i = 4 + addr_bits; i >= 0; i--) {
E 28
I 28
	for (i = 3 + addr_bits - 1; i >= 0; i--) {
E 28
		di = ((cmd >> i) << CR9346_EEDI_SHIFT) & CR9346_EEDI;
		OUTB(dp, CR9346, chip_select | di);
		gani_eeprom_delay(dp);

		OUTB(dp, CR9346, chip_select | di | CR9346_EESK);
		gani_eeprom_delay(dp);
I 28

		OUTB(dp, CR9346, chip_select | di);
		gani_eeprom_delay(dp);
E 28
	}

D 28
	/* release clock but keep chip_select asserted */
	OUTB(dp, CR9346, chip_select);
	gani_eeprom_delay(dp);

E 28
	/* get returned value */
D 22
	ret = 0;
E 22
I 22
#ifdef lint
	ret = ret;
#endif
E 22
	for (i = 16; i > 0; i--) {
		/* get 1 bit */
		OUTB(dp, CR9346, chip_select | CR9346_EESK);
		gani_eeprom_delay(dp);

D 22
		ret = (ret << 1)
		    | ((INB(dp, CR9346) >> CR9346_EEDO_SHIFT) & 1);
E 22
I 22
		ret = (ret << 1) |
		    ((INB(dp, CR9346) >> CR9346_EEDO_SHIFT) & 1);
E 22

		OUTB(dp, CR9346, chip_select);
		gani_eeprom_delay(dp);
	}

	/* Terminate the EEPROM access. */
D 28
	OUTB(dp, CR9346, CR9346_EEM_PROGRAM);
	OUTB(dp, CR9346, CR9346_EEM_NORMAL);
E 28
I 28
	chip_select &= ~CR9346_EECS;
	OUTB(dp, CR9346, chip_select | CR9346_EESK);
E 28
	gani_eeprom_delay(dp);
I 28
	OUTB(dp, CR9346, chip_select);
	gani_eeprom_delay(dp);
E 28

I 28
	chip_select &= ~CR9346_EEM;	/* i.e. CR9346_EEM_NORMAL */
	OUTB(dp, CR9346, chip_select);

E 28
D 22
	DPRINTF(2, (CE_CONT, "!gani_read_eeprom: returned 0x%x", ret));
E 22
I 22
D 26
	DPRINTF(2, (CE_CONT, "!%s: %s: returned 0x%x",
E 26
I 26
	DPRINTF(4, (CE_CONT, "!%s: %s: returned 0x%x",
E 26
	    dp->name, __func__, ret));
E 22

	return (ret);
}

I 22
#if DEBUG_LEVEL > 0
E 22
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
D 22
		"!0x%02x: %02x %02x %02x %02x %02x %02x %02x %02x", 
			i*2,
			(uint8_t)x0, (uint8_t)(x0 >> 8),
			(uint8_t)x1, (uint8_t)(x1 >> 8),
			(uint8_t)x2, (uint8_t)(x2 >> 8),
			(uint8_t)x3, (uint8_t)(x3 >> 8));
E 22
I 22
		    "!0x%02x: %02x %02x %02x %02x %02x %02x %02x %02x",
		    i*2,
		    (uint8_t)x0, (uint8_t)(x0 >> 8),
		    (uint8_t)x1, (uint8_t)(x1 >> 8),
		    (uint8_t)x2, (uint8_t)(x2 >> 8),
		    (uint8_t)x3, (uint8_t)(x3 >> 8));
E 22
	}
}
I 22
#endif
E 22
D 26
#endif /* CONFIG_EEPROM_IO */
E 26

I 31
static void
gani_fixup_params(struct gem_dev *dp)
{
	int	rxmaxsize;
	struct gani_dev	*lp = dp->private;

	/*
	 * Fix rx buffer length:
	 * It must have additional space depend on chip model,
	 * and its size must be multiple of 8.
	 */
	rxmaxsize = GANI_PCI(lp) ? RMS_PCI(dp->mtu) : RMS_PCIE(dp->mtu);
	dp->rx_buf_len = ROUNDUP2(rxmaxsize, 8);

#ifdef GEM_CONFIG_VLAN_HW
	/*
	 * RTL816x series will corrupt vlan-tagged outgoing packets
	 * when hw checksum is enabled and hw vlan tagging is disabled.
	 */
	dp->misc_flag |= GEM_VLAN_HARD;
#ifdef CONFIG_CKSUM_OFFLOAD
	lp->new_cksum = !(GANI_PCI(lp) ||
	    lp->chip->type == R8168_1 /* RTL8168B rev.B */ ||
	    lp->chip->type == R8168_2 /* RTL8168B rev.E */ ||
	    lp->chip->type == R8168_3 /* RTL8168B rev.F */ ||
	    lp->chip->type == R8101_1 /* RTL8101E rev.B */ ||
	    lp->chip->type == R8101_2 /* RTL8101E rev.E */ ||
	    lp->chip->type == R8101_3 /* RTL8191E rev.h */);

	if (GANI_PCIE_GIGA(lp) && dp->mtu > ETHERMTU) {
		/*
		 * checksum offload doesn't work for jumbo packets.
		 * clear previous setting, it's garbage.
		 */
		dp->misc_flag &=
		    ~(GEM_CKSUM_FULL_IPv4 | GEM_CKSUM_HEADER_IPv4 | GEM_LSO);
	} else {
		/* XXX - ok for 8169 and 8101 */
		dp->misc_flag |= GEM_CKSUM_FULL_IPv4 | GEM_CKSUM_HEADER_IPv4;
#ifdef CONFIG_LSO
		dp->misc_flag |= GEM_LSO;
#endif
	}
#endif /* CONFIG_CKSUM_OFFLOAD */
#else
	dp->misc_flag |= GEM_VLAN_SOFT;
#endif /* GEM_CONFIG_VLAN_HW */
}

E 31
E 16
static int
gani_attach_chip(struct gem_dev *dp)
{
	int		i;
	uint32_t	val;
	uint8_t		*m;
D 22
	struct gani_dev	*lp = (struct gani_dev *)dp->private;
E 22
I 22
	struct gani_dev	*lp = dp->private;
E 22
I 5
D 16
	ddi_acc_handle_t	conf_handle;
E 16
I 9
D 10
	int		len;
	int		*params;
	char		propname[32];
E 10
E 9
E 5

I 17
	DPRINTF(0, (CE_CONT, "!%s: %s: called", dp->name, __func__));

E 17
I 9
D 10
	sprintf(propname, "%s-pkt-delay", dp->name);

	lp->poll_pkt_delay = 6;
	if (ddi_prop_lookup_int_array(
		DDI_DEV_T_ANY, dp->dip, DDI_PROP_DONTPASS,
		propname, &params, &len) == DDI_PROP_SUCCESS) {
		if (len == 1) {
			lp->poll_pkt_delay = params[0];
		}
		ddi_prop_free(params);

		if (lp->poll_pkt_delay < 1) {
			lp->poll_pkt_delay = 1;
		}
	}

E 10
E 9
D 26
	/*
D 14
	 * The mac address in EEPROM has been loaded into the ID registers
	 * after chip reset.
E 14
I 14
	 * reload default mac address from EEPROM
E 14
	 */
E 26
I 16
	m = &dp->dev_addr.ether_addr_octet[0];
D 26
#ifdef CONFIG_EEPROM_IO
E 26
I 26
D 28
	if ((lp->chip->type == R8101_1 || lp->chip->type == R8101_2) &&
	    gani_read_eeprom(dp, 0) == 0x8128) {
E 28
I 28
	if (GANI_PCIE_GIGA(lp) &&
	    (gani_read_eeprom(dp, 0) == 0x8128 ||
	    gani_read_eeprom(dp, 0) == 0x8129)) {
E 28
		/*
		 * read factory mac address from EEPROM
		 */
E 26
D 22
#  if DEBUG_LEVEL > 0
E 22
I 22
#if DEBUG_LEVEL > 10
E 22
D 26
	gani_eeprom_dump(dp, 0x40);
E 26
I 26
		gani_eeprom_dump(dp, 0x40);
E 26
D 22
#  endif
E 22
I 22
#endif
E 22
D 26
	for (i = 0; i < ETHERADDRL/2; i++) {
D 22
		val = gani_read_eeprom(dp, i + 7);
		m[i*2  ] = (uint8_t) val;
		m[i*2+1] = (uint8_t)(val >> 8);
E 22
I 22
		val = gani_read_eeprom(dp, 7 + i);
		m[i*2 + 0] = (uint8_t)val;
		m[i*2 + 1] = (uint8_t)(val >> 8);
E 26
I 26
		for (i = 0; i < ETHERADDRL/2; i++) {
			val = gani_read_eeprom(dp, 7 + i);
			m[i*2 + 0] = (uint8_t)val;
			m[i*2 + 1] = (uint8_t)(val >> 8);
		}
	} else {
		/*
I 28
		 * no eeprom
E 28
		 * read factory mac address from IDR register
		 */
		for (i = 0; i < ETHERADDRL; i++) {
			m[i] = INB(dp, IDR + i);
		}
E 26
E 22
	}
D 26
#else
E 16
I 14
	OUTB(dp, CR9346, CR9346_EEM_AUTOLD);
D 16
	drv_usecwait(10000);	/* XXX - typically we must wait 2mS */
E 16

E 14
D 4
	m = dp->dev_addr.ether_addr_octet;
	val = INL(dp, IDR + 0);
	m[0] = (uint8_t) val;
	m[1] = (uint8_t) (val >> 8);
	m[2] = (uint8_t) (val >> 16);
	m[3] = (uint8_t) (val >> 24);
E 4
I 4
D 16
	m = &dp->dev_addr.ether_addr_octet[0];
E 16
I 16
	/*
D 22
	 * XXX - the old datasheet says it takes 2mS typically, but
	 * it still caused bus timeouts for Netgear cardbus products
D 21
	 * even if we waited for 10mS. Now we wait for 100mS.
E 21
I 21
	 * even if we waited for 10mS. Now we wait for 1000mS.
E 22
I 22
	 * XXX - the old datasheet says the autoloading takes 2mS typically,
	 * but it still caused bus timeouts for Netgear cardbus products
	 * even if we waited for 10mS. Now we wait for 1000mS. :-(
E 22
E 21
	 */
D 21
	drv_usecwait(1000000);
E 21
I 21
	delay(drv_usectohz(1000000));
E 21

E 16
	for (i = 0; i < ETHERADDRL; i++) {
		m[i] = INB(dp, IDR + i);
	}
I 16

E 26
D 27
	/* initialize soft copy of mac registers */
E 16
I 15
	bcopy(m, lp->mac, ETHERADDRL);
E 27
I 27
	/* invalidate soft copy of mac registers */
	bzero(lp->mac, ETHERADDRL);
E 27
I 16
D 26
#endif /* CONFIG_EEPROM_IO */
E 26
E 16
E 15
E 4

D 4
	val = INL(dp, IDR + 4);
	m[4] = (uint8_t) val;
	m[5] = (uint8_t) (val >> 8);

E 4
	/* no need to scan phy */
	dp->mii_phy_addr = -1;

D 4
	/* mtu: max rx packet size is 16kbyte -1 */
	dp->mtu = min(dp->mtu, (16*1024-1) - 14 - ETHERFCSL);
E 4
I 4
D 9
	/* mtu: max rx packet size is 16kbyte - 1 */
E 9
I 9
D 16
	/* mtu: max packet size is 8kbyte - 1 */
E 9
	dp->mtu = min(dp->mtu,
D 5
			RMS_MASK - sizeof(struct ether_header) - ETHERFCSL);
E 5
I 5
D 9
		RMS_MASK - sizeof(struct ether_header) - ETHERFCSL - 4);
E 9
I 9
		8192 - 1 - sizeof(struct ether_header) - ETHERFCSL - 4);
E 16
I 16
D 31
	/*
	 * Fix rx buffer length:
D 23
	 * It must have additional 4 byte for vlan and must be multiple
E 23
I 23
D 28
	 * It must have additional 4 byte and must be multiple
E 23
	 * of rx buffer align.
E 28
I 28
	 * It must have additional 4 byte and its size must be multiple
	 * of rx buffer alignment.
E 28
	 */
D 28
	dp->rx_buf_len = ROUNDUP2(PKTSIZE(dp->mtu), dp->gc.gc_rx_buf_align + 1);
E 28
I 28
	dp->rx_buf_len =
	    ROUNDUP2(PKTSIZE(dp->mtu), dp->gc.gc_rx_buf_align + 1);
E 28
E 16
E 9
E 5
E 4

E 31
I 31
#ifndef GEM_CONFIG_JUMBO_FRAME
	gani_fixup_params(dp);
#endif
E 31
I 3
D 5
	/* fix tx threashold */
D 4
	dp->txthr = (dp->mtu + 14 + ETHERFCSL + ETThR_UNIT);
E 4
I 4
	dp->txthr = sizeof(struct ether_header) + dp->mtu + ETHERFCSL;
E 4

I 4
	/* fix rx threashold */
	dp->rxthr = sizeof(struct ether_header) + dp->mtu + ETHERFCSL;

E 5
I 5
D 9
	/* fix tx threashold for strore and forward */
E 9
I 9
D 16
	/* increase tx dma burst size for performance */
D 10
	dp->txmaxdma = max(256, dp->txmaxdma);		/* default is 64 */
E 10
I 10
	dp->txmaxdma = max(4*64, dp->txmaxdma);		/* default is 64 */
E 10

	/* rx priority should be higher than tx */
D 10
	dp->rxmaxdma = 2 * dp->txmaxdma;
E 10
I 10
	dp->rxmaxdma = dp->txmaxdma * 2;
E 10

E 16
D 22
	/* store & foward for tx */
E 9
D 16
	dp->txthr = sizeof(struct ether_header) + dp->mtu + ETHERFCSL + 4;
E 16
I 16
D 17
	/* XXX: RTL8168 series supports only store & forword for tx */
E 17
I 17
	/* XXX - RTL8168 series supports only store & forword for tx */
E 22
I 22
D 23
	/*  RTL8168 series supports only store & forword for tx */
E 23
I 23
D 24
	/* RTL816x series supports only store & forword for tx and rx */
E 24
I 24
	/* RTL816x series support only store & forword for tx and rx */
E 24
E 23
E 22
E 17
	dp->txthr = INT32_MAX;
I 23
	dp->rxthr = INT32_MAX;
I 28

E 28
E 23
E 16
D 9
#ifdef notdef
	/* fix rx threashold for store and forward */
	dp->rxthr = sizeof(struct ether_header) + dp->mtu + ETHERFCSL + 4;
#endif
E 9
I 9
D 27

E 27
D 16
	/* enable early dma for rx */
D 10
	dp->rxthr = dp->rxmaxdma / 2;
E 10
I 10
	dp->rxthr = (3 * dp->rxmaxdma) / 4;
E 16
I 16
D 17
	/* increase burst size for performance */
#ifdef notdef
	if (!GANI_8168_OR_LATER(lp->chip->type)) {
		/*
		 * To make rx priority is higher than tx, we use bigger
		 * rxmaxdma than txmaxdma.
		 */
		dp->txmaxdma = max(4*64, dp->txmaxdma);	/* 256 bytes */
		dp->rxmaxdma = dp->txmaxdma * 2;	/* 512 bytes */
E 17
I 17
	/*
D 18
	 * XXX - For SiS965L txmaxdma and rxmaddma must be
	 * unlimited, and rxthr *must* be S&F, otherwise
	 * the system will hang.
E 18
I 18
	 * XXX - workaround for SiS965L
D 22
	 * txmaxdma and rxmaddma must be unlimited, and rxthr *must* be S&F,
E 22
I 22
D 23
	 * txmaxdma and rxmaxdma must be unlimited, and rxthr must be S&F,
E 22
	 * otherwise the system will hang.
E 23
I 23
	 * txmaxdma and rxmaxdma must be unlimited otherwise the system
	 * will hang.
E 23
E 18
	 */
D 22
	dp->txmaxdma = INT32_MAX;
	dp->rxmaxdma = INT32_MAX;
	dp->rxthr    = INT32_MAX;
E 22
I 22
	dp->txmaxdma = max(dp->mtu, 1024+1);
D 23
	if (lp->chip->type == R8168_CFG_METHOD_1) {
E 23
I 23
	if (lp->chip->type == R8168_1 /* RTL8168B rev.B */) {
E 23
		dp->txmaxdma = min(dp->txmaxdma,  512);
	}
I 27

E 27
	dp->rxmaxdma = dp->mtu;
E 22
E 17
E 16
E 10

E 9
E 5
E 4
E 3
D 16
	/* undocumented patch */
	OUTB(dp, 0x82, 0x01);

D 5
	if (lp->chip->type < MAC_VER_E) {
		ddi_acc_handle_t	conf_handle;
E 5
D 9

E 9
D 5
		/* set pci latency timer to 0x40 */
		if (pci_config_setup(dp->dip, &conf_handle) != DDI_SUCCESS) {
			cmn_err(CE_WARN,
			"!%s: gani_attach_chip: pci_config_setup failed",
				dp->name);
		}
		else {
			pci_config_put8(conf_handle,
				PCI_CONF_LATENCY_TIMER, 0x40);
			pci_config_teardown(&conf_handle);
		}
E 5
I 5
	/* set pci latency timer to 0x40 */
	if (pci_config_setup(dp->dip, &conf_handle) != DDI_SUCCESS) {
		cmn_err(CE_WARN,
		"!%s: gani_attach_chip: pci_config_setup failed",
			dp->name);
E 16
I 16
D 17
		/* enable early dma for rx */
		dp->rxthr = (3 * dp->rxmaxdma) / 4;
	} else
#endif
	{
		/*
		 * pci-e rtl8169 series and rtl8169sc
		 *
		 * XXX - For SiS965L txmaxdma and rxmaddma must eb
		 * unlimited, and rxthr *must* be S&F, otherwise
		 * the system will hang.
		 */
		dp->txmaxdma = INT32_MAX;
		dp->rxmaxdma = INT32_MAX;
		dp->rxthr    = INT32_MAX;
E 16
E 5
	}
I 5
D 16
	else {
D 10
		pci_config_put8(conf_handle, PCI_CONF_LATENCY_TIMER, 0x40);
E 10
I 10
		pci_config_put8(conf_handle, PCI_CONF_LATENCY_TIMER, 0x20);
E 10
		pci_config_teardown(&conf_handle);
	}
E 16
E 5

E 17
D 10
	/* rtl8169/rtl8110 doesn't support 1000Tx half duplex mode */
E 10
I 10
D 16
	/* rtl8169 and rtl8110 don't support 1000Tx half duplex mode */
E 10
	dp->anadv_1000hdx = FALSE;
E 16
I 16
D 22
	/*
D 17
	 * XXX : the data sheets says rtl816x doesn't support 1Gbps half
E 17
I 17
	 * XXX - the datasheet says rtl816x doesn't support 1Gbps half
E 17
	 * duplex mode, but phys in rtl8168 seem to require 1000hdx bit
D 17
	 * in 1000TC register for 1G bps operation.
E 17
I 17
D 18
	 * set in 1000TC register for 1G bps operation.
E 18
I 18
	 * set in 1000TC register for 1G bps full duplex negotiation.
E 18
E 17
	 */
	dp->anadv_1000hdx = dp->anadv_1000fdx;
E 22
I 22
D 23
	dp->rxthr = INT32_MAX;
E 22
E 16
I 4

I 22
#if defined(GEM_CONFIG_CKSUM_OFFLOAD) && defined(GEM_CONFIG_VLAN_HW)
E 23
I 23
D 31
#ifdef GEM_CONFIG_VLAN_HW
E 23
E 22
D 13
	/* fix rx buffer length, it must be 4byte-aligned */
	dp->rx_buf_len = ROUNDUP2(dp->rx_buf_len, dp->gc.gc_rx_buf_align + 1);
E 13
I 13
D 16
	/* fix rx buffer length, it must have additional 4 byte */
	dp->rx_buf_len = dp->mtu + sizeof(struct ether_header) + ETHERFCSL + 4;
E 13
I 5

	if (dp->mii_fixedmode) {
E 16
I 16
D 19
	if (dp->mii_fixedmode && dp->speed == GEM_SPD_1000) {
E 19
I 19
	/*
D 22
	 * XXX - 816x nics seem to have promblem in fixed mode. The link
	 * never go up again after it once become down from up.
E 22
I 22
D 23
	 * 816x series will corrupt vlan-tagged outgoing packets
E 23
I 23
	 * RTL816x series will corrupt vlan-tagged outgoing packets
E 23
D 26
	 * when hw check summing is enabled and hw vlan tagging is deisabled.
E 26
I 26
	 * when hw checksum is enabled and hw vlan tagging is disabled.
E 26
D 23
	 * Therefore, both of them must be enabled at the same time.
E 23
E 22
	 */
D 22
	if (dp->mii_fixedmode) {
E 19
E 16
		cmn_err(CE_WARN,
D 10
			"%s: rtl8169 does not support fixed mode. "
"arranging auto negotiation capability instead of specified fixed mode.",
E 10
I 10
D 16
			"!%s: rtl8169 does not support fixed mode. "
D 13
			"arranging limited auto negotiation capability "
E 13
I 13
			"limited auto negotiation capability is used "
E 13
			"instead of specified fixed mode.",
E 10
			dp->name);
		dp->anadv_1000fdx = FALSE;
		dp->anadv_1000hdx = FALSE;
		dp->anadv_100t4   = FALSE;
		dp->anadv_100fdx  = FALSE;
		dp->anadv_100hdx  = FALSE;
		dp->anadv_10fdx   = FALSE;
		dp->anadv_10hdx   = FALSE;
E 16
I 16
D 17
		"!%s: rtl8169 series does not support fixed mode for"
E 17
I 17
D 19
		"!%s: rtl816x series does not support fixed mode for"
E 17
		"1G bps connection. "
E 19
I 19
		"!%s: rtl816x series does not support fixed mode."
E 19
		"limited auto negotiation capability is used "
		"instead of given forced mode.",
		dp->name);
E 16

D 16
		switch(dp->speed) {
		case GEM_SPD_1000:
			if (!dp->full_duplex) {
				cmn_err(CE_WARN,
D 9
"%s: rtl8169 does not support 1000M half duplex. using full duplex instead of.",
E 9
I 9
D 10
	"%s: 1G half duplex isn't supported. using full duplex instead of.",
E 10
I 10
	"!%s: 1G half duplex isn't supported. using full duplex instead of.",
E 10
E 9
				dp->name);
			}
			dp->anadv_100fdx = TRUE;
D 6
			
E 6
I 6
			dp->full_duplex  = TRUE;
E 6
			break;
E 16
I 16
D 19
		dp->anadv_1000fdx = B_TRUE;
		dp->anadv_1000hdx = B_TRUE;	/* workaround for PCIE nics */
E 19
I 19
		dp->anadv_1000fdx = B_FALSE;
		dp->anadv_1000hdx = B_FALSE;
E 19
		dp->anadv_100t4   = B_FALSE;
		dp->anadv_100fdx  = B_FALSE;
		dp->anadv_100hdx  = B_FALSE;
		dp->anadv_10fdx   = B_FALSE;
		dp->anadv_10hdx   = B_FALSE;
E 16

D 16
		case GEM_SPD_100:
D 6
			if (dp->full_duplex) {
				dp->anadv_100fdx = TRUE;
			}
			dp->anadv_100hdx = TRUE;
E 6
I 6
			dp->anadv_100fdx = dp->full_duplex;
			dp->anadv_100hdx =!dp->full_duplex;
E 6
			break;
E 16
I 16
D 19
		dp->full_duplex   = B_TRUE;
E 19
I 19
		switch (dp->speed) {
		case GEM_SPD_1000:
			dp->full_duplex   = B_TRUE;
			dp->anadv_1000fdx = B_TRUE;
			/* XXX - workaround for PCIE nics */
			dp->anadv_1000hdx = B_TRUE;
			break;
		
		case GEM_SPD_100:
			dp->anadv_100fdx  = dp->full_duplex;
			dp->anadv_100hdx  =!dp->full_duplex;
			break;

		case GEM_SPD_10:
			dp->anadv_10fdx   = dp->full_duplex;
			dp->anadv_10hdx   =!dp->full_duplex;
			break;
		}

E 19
		dp->mii_fixedmode = B_FALSE;
I 19
		dp->gc.gc_flow_control = FLOW_CONTROL_NONE;
E 19
	}
E 16

D 6
		default:
			if (dp->full_duplex) {
				dp->anadv_10fdx = TRUE;
			}
			dp->anadv_10hdx = TRUE;
E 6
I 6
D 16
		case GEM_SPD_10:
			dp->anadv_10fdx = dp->full_duplex;
			dp->anadv_10hdx =!dp->full_duplex;
E 6
			break;
		}
E 16
I 16
D 17
#ifdef GEM_CONFIG_CKSUM_OFFLOAD
	dp->misc_flag |= (GEM_CKSUM_IPv4 | GEM_CKSUM_TCP | GEM_CKSUM_UDP);
#endif
#ifdef CONFIG_VLAN
E 17
I 17
#if defined(GEM_CONFIG_CKSUM_OFFLOAD) && defined(CONFIG_VLAN)
	/*
	 * XXX - 816x series corrupts vlan-tagged packets on tx
	 * if the hw-cksum is enabled and hw-vlan is deisabled.
	 * Therefore, the both must be enabled at the same time.
	 */
E 22
E 17
	dp->misc_flag |= GEM_VLAN_HARD;
I 23
#ifdef CONFIG_CKSUM_OFFLOAD
E 23
I 17
D 22
	dp->misc_flag |= (GEM_CKSUM_FULL_IPv4 | GEM_CKSUM_HEADER_IPv4);
E 22
I 22
D 28
	if (GANI_PCIE_GIGA(lp->chip->type) && dp->mtu > ETHERMTU) {
E 28
I 28
	lp->new_cksum = !(GANI_PCI(lp) ||
	    lp->chip->type == R8168_1 /* RTL8168B rev.B */ ||
	    lp->chip->type == R8168_2 /* RTL8168B rev.E */ ||
	    lp->chip->type == R8168_3 /* RTL8168B rev.F */ ||
	    lp->chip->type == R8101_1 /* RTL8101E rev.B */ ||
	    lp->chip->type == R8101_2 /* RTL8101E rev.E */ ||
	    lp->chip->type == R8101_3 /* RTL8191E rev.h */);

	if (GANI_PCIE_GIGA(lp) && dp->mtu > ETHERMTU) {
E 28
I 23
		/* XXX - checksum offload doesn't work for jumbo packets */
E 23
		/* EMPTY */
	} else {
I 23
		/* XXX - ok for 8168 and 8101 */
E 23
		dp->misc_flag |= GEM_CKSUM_FULL_IPv4 | GEM_CKSUM_HEADER_IPv4;
#ifdef CONFIG_LSO
		dp->misc_flag |= GEM_LSO;
#endif
	}
I 23
#endif /* CONFIG_CKSUM_OFFLOAD */
E 23
E 22
#else
	dp->misc_flag |= GEM_VLAN_SOFT;
E 17
D 23
#endif
E 23
I 23
#endif /* GEM_CONFIG_VLAN_HW */
E 23
D 17
#ifdef NEVER
	if (GANI_PCIE(lp->chip->type)) {
		gani_patch_sis_pci_host_bridge(dp);
	}
#endif
E 17
I 17

E 31
E 17
	/* Receive control register: write an initial value */
	val = 0;
	if (dp->rxmaxdma <= 64) {
		val |= RCR_MXDMA_64;
D 22
	} else if (dp->rxmaxdma<= 128) {
E 22
I 22
	} else if (dp->rxmaxdma <= 128) {
E 22
		val |= RCR_MXDMA_128;
D 22
	} else if (dp->rxmaxdma<= 256) {
E 22
I 22
	} else if (dp->rxmaxdma <= 256) {
E 22
		val |= RCR_MXDMA_256;
D 22
	} else if (dp->rxmaxdma<= 512) {
E 22
I 22
	} else if (dp->rxmaxdma <= 512) {
E 22
		val |= RCR_MXDMA_512;
D 22
	} else if (dp->rxmaxdma<= 1024) {
E 22
I 22
	} else if (dp->rxmaxdma <= 1024) {
E 22
		val |= RCR_MXDMA_1024;
	} else {
		val |= RCR_MXDMA_UNLIMITED;
	}
D 22
	if (dp->rxthr <= 64) {
E 22
I 22

D 28
	if (GANI_PCIE_FAST(lp->chip->type)) {
E 28
I 28
	if (GANI_PCIE_FAST(lp)) {
E 28
		val |= RCR_RXFTH_SF;	/* reserved */
I 23
D 28
	} else if (GANI_PCIE_GIGA(lp->chip->type)) {
E 28
I 28
	} else if (GANI_PCIE_GIGA(lp)) {
E 28
		switch (lp->chip->type) {
		case R8168_1: /* RTL8168B rev.B  */
		case R8168_2: /* RTL8168B rev.E */
		case R8168_3: /* RTL8168B rev.F */
D 27
			val |= RCR_RXFTH_SF;	/* reserved */
E 27
I 27
			val |= 7 << 13;	/* reserved */
E 27
			break;

		case R8168_4: /* RTL8168C */
		case R8168_5: /* RTL8168C rev.B */
		case R8168_6: /* RTL8168C rev.C */
		case R8168_7: /* RTL8168CP rev.B */
		case R8168_8: /* RTL8168CP rev.C */
			val |= RCR_128_INT | RCR_FET_MULTI;
			break;

		case R8168_9: /* RTL8168D */
		case R8168_10: /* RTL8168D rev.B */
I 24
		case R8168_11: /* RTL8168D rev.C */
E 24
		default:
			val |= RCR_128_INT;
			break;
		}
E 23
	} else if (dp->rxthr <= 64) {
E 22
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
I 28

E 28
D 22
	/* XXX - Keep undocumented bits.  */
	lp->rcr = (val | (INL(dp, RCR) & ~RCR_MASK));
E 22
I 22
D 27
	/* XXX - keep undocumented bits.  */
E 27
I 27
	/* keep undocumented bits in RCR  */
E 27
	lp->rcr = val | (INL(dp, RCR) & ~RCR_MASK);
I 27
	DPRINTF(10, (CE_CONT, "!%s: %s: RCR_MASK:0x%x",
	    dp->name, __func__, ~RCR_MASK));
E 27
E 22
E 16

D 16
		dp->mii_fixedmode = FALSE;
E 16
I 16
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
I 28
		/* vendor choice for 8101 */
E 28
		val |= TCR_MXDMA_1024;
	} else {
		val |= TCR_MXDMA_UNLIMITED;
E 16
	}
I 16
D 24
	lp->tcr = (TCR_IFG_802_3 | TCR_LBK_NORMAL | val);
E 24
I 24
D 28
	lp->tcr = TCR_IFG_802_3 | TCR_LBK_NORMAL | val;
E 28
I 28
	lp->tcr |= TCR_IFG_802_3 | TCR_LBK_NORMAL | val;
E 28
E 24
E 16

I 21
	mutex_init(&lp->stat_lock, NULL, MUTEX_DRIVER, dp->iblock_cookie);
D 22
	lp->stat_to_id = (timeout_id_t) 0;
E 22
I 22
	lp->stat_to_id = (timeout_id_t)0;
E 22

I 23
D 28
	lp->new_cksum = !(GANI_PCI(lp->chip->type) ||
	    lp->chip->type == R8168_1 /* RTL8168B rev.B */ ||
	    lp->chip->type == R8168_2 /* RTL8168B rev.E */ ||
	    lp->chip->type == R8168_3 /* RTL8168B rev.F */ ||
	    lp->chip->type == R8101_1 /* RTL8101E rev.B */ ||
	    lp->chip->type == R8101_2 /* RTL8101E rev.E */ ||
	    lp->chip->type == R8101_3 /* RTL8191E rev.h */);
E 28
I 28
	if (GANI_PCIE_GIGA(lp)) {
		/* disable flow control by default for pci-e GbE */
		if (!ddi_prop_exists(DDI_DEV_T_ANY, dp->dip,
		    DDI_PROP_DONTPASS, "adv_pause")) {
			dp->anadv_pause = 0;
		}
		if (!ddi_prop_exists(DDI_DEV_T_ANY, dp->dip,
		    DDI_PROP_DONTPASS, "adv_asmpause")) {
			dp->anadv_asmpause = 0;
		}
	}
E 28

E 23
E 21
I 6
D 9
#ifdef NOT_NEEDED
E 6
	/*
	 * XXX - workaround for funny auto negotiation behaviour.
	 * fix lower priority bits in advertisement register
	 */	
	if (dp->anadv_1000fdx) goto adv100f;
	if (dp->anadv_100fdx) goto adv100h;
	if (dp->anadv_100hdx) goto adv10f;
	goto adv10h;

	adv100f:
		dp->anadv_100fdx = TRUE;
	adv100h:
		dp->anadv_100hdx = TRUE;
	adv10f:
		dp->anadv_10fdx = TRUE;
	adv10h:
		dp->anadv_10hdx = TRUE;
D 6

E 6
I 6
#endif
E 9
E 6
D 16
	return 0;	/* currently return code is not used. */
E 16
I 16
	return (GEM_SUCCESS);	/* currently return code is not used. */
E 16
E 5
E 4
}

static int
ganiattach(dev_info_t *dip, ddi_attach_cmd_t cmd)
{
	int			i;
I 4
D 16
	int			n;
E 4
	ddi_iblock_cookie_t	c;
E 16
D 23
	ddi_acc_handle_t	conf_handle;
E 23
I 23
	ddi_acc_handle_t	conf_ha;
E 23
D 16
	uint16_t		comm;
	int			ret;
E 16
D 22
	int			vid;
	int			did;
E 22
	int			revid;
	int			unit;
	struct chip_info	*p;
	uint32_t		tcr;
D 4
	int			len;
E 4
I 4
D 16
	u_int			len;
E 4
	struct pci_phys_spec	*regs;
E 16
	const char		*drv_name;
	struct gem_dev		*dp;
D 28
	void			*base;
E 28
I 28
	caddr_t			base;
E 28
D 23
	ddi_acc_handle_t	regs_handle;
E 23
I 23
	ddi_acc_handle_t	regs_ha;
E 23
	struct gem_conf		*gcp;
	struct gani_dev		*lp;
D 16
	uint8_t			cap_ptr;
	uint32_t		cap;
	uint32_t		ps;
E 16
	uint32_t		ilr;
I 16
D 22
	boolean_t		is_pcie;
E 22
I 22
	uint_t			pcie_cap;
I 28
	uint_t			msi_cap;
E 28
E 22
E 16

D 22
	unit =  ddi_get_instance(dip);
E 22
I 22
	unit = ddi_get_instance(dip);
E 22
	drv_name = ddi_driver_name(dip);
D 16

E 16
D 17
	DPRINTF(3, (CE_CONT, "!%s%d: ganiattach: called", drv_name, unit));
E 17
I 17
D 22
	DPRINTF(1, (CE_CONT, "!%s%d: ganiattach: called", drv_name, unit));
E 22
I 22
	DPRINTF(1, (CE_CONT, "!%s%d: %s: called", drv_name, unit, __func__));
E 22
E 17

D 16
	if (cmd == DDI_ATTACH) {
E 16
I 16
	/*
	 * Common routine after power-on
	 */
E 16

D 16
		/*
		 * Check if chip is supported.
		 */
E 16
I 16
	/* fix config registers */
D 23
	if (pci_config_setup(dip, &conf_handle) != DDI_SUCCESS) {
E 23
I 23
	if (pci_config_setup(dip, &conf_ha) != DDI_SUCCESS) {
E 23
		cmn_err(CE_WARN, "!%s%d: pci_config_setup failed",
D 22
			drv_name, unit);
E 22
I 22
		    drv_name, unit);
E 22
		goto err;
	}
E 16

D 16
		/*
		 * Map in the device registers.
		 */
		/* Search IO-range or memory-range to be mapped */
		regs = NULL;
		len  = 0;
E 16
I 16
D 23
	pci_config_put16(conf_handle, PCI_CONF_COMM,
D 22
		pci_config_get16(conf_handle, PCI_CONF_COMM)
			| PCI_COMM_IO | PCI_COMM_MAE | PCI_COMM_ME);
E 22
I 22
	    pci_config_get16(conf_handle, PCI_CONF_COMM)
E 23
I 23
	pci_config_put16(conf_ha, PCI_CONF_COMM,
	    pci_config_get16(conf_ha, PCI_CONF_COMM)
E 23
	    | PCI_COMM_IO | PCI_COMM_MAE | PCI_COMM_ME);
E 22
E 16
D 4
		if (ddi_getlongprop(DDI_DEV_T_ANY, dip, DDI_PROP_DONTPASS,
			"reg", (caddr_t)&regs, &len) != DDI_PROP_SUCCESS) {
E 4
I 4

D 16
		if (ddi_prop_lookup_int_array(
			DDI_DEV_T_ANY, dip, DDI_PROP_DONTPASS,
			"reg", (int **)&regs, &len) != DDI_PROP_SUCCESS) {
E 4
			cmn_err(CE_WARN,
D 10
				"%s%d: failed to get reg property",
E 10
I 10
				"!%s%d: failed to get reg property",
E 10
					drv_name, unit);
			goto err;
		}
I 4
		n = len / (sizeof(struct pci_phys_spec) / sizeof(int));
E 16
I 16
	/* ensure D0 mode */
D 23
	(void) gem_pci_set_power_state(dip, conf_handle, PCI_PMCSR_D0);
E 23
I 23
	(void) gem_pci_set_power_state(dip, conf_ha, PCI_PMCSR_D0);
E 23
E 16
E 4

D 16
		ASSERT(regs != NULL && len > 0);
#if DEBUG_LEVEL > 0
D 4
		for (i = 0; i <len / sizeof(struct pci_phys_spec); i++) {
E 4
I 4
		for (i = 0; i < n; i++) {
E 4
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
D 4
		for (i = 0; i <len / sizeof(struct pci_phys_spec); i++) {
E 4
I 4
		for (i = 0; i < n; i++) {
E 4
			if ((regs[i].pci_phys_hi & PCI_REG_ADDR_M) == 
D 3
			    PCI_ADDR_IO) {
E 3
I 3
#ifdef MAP_MEM
			    PCI_ADDR_MEM32
#else
			    PCI_ADDR_IO
#endif
			) {
E 3
				/* it's I/O space */
D 4
				kmem_free(regs, len);
E 4
I 4
				ddi_prop_free(regs);
E 4
				goto io_range_found;
			}
		}
D 3
		cmn_err(CE_WARN, "!%s%d: failed to find IO space",
E 3
I 3
		cmn_err(CE_WARN,
#ifdef MAP_MEM
			"!%s%d: failed to find MEM32 space",
#else
			"!%s%d: failed to find IO space",
#endif
E 3
				drv_name, unit);
D 4
		kmem_free(regs, len);
E 4
I 4
		ddi_prop_free(regs);
E 4
		goto err;
io_range_found:
		if (ddi_regs_map_setup(dip, i, (caddr_t *)&base,
			0, 0, &gani_dev_attr, &regs_handle)) {
			cmn_err(CE_WARN, "!%s%d: ddi_regs_map_setup failed",
				drv_name, unit);
			goto err;
		}
E 16
I 16
D 23
	/* set pci latency timer to 0x40 */
	if (pci_config_get8(conf_handle, PCI_CONF_LATENCY_TIMER) < 64) {
		pci_config_put8(conf_handle, PCI_CONF_LATENCY_TIMER, 64);
	}
D 22
	vid = pci_config_get16(conf_handle, PCI_CONF_VENID);
	did = pci_config_get16(conf_handle, PCI_CONF_DEVID);
E 22
	revid = pci_config_get8(conf_handle, PCI_CONF_REVID);
	ilr = pci_config_get32(conf_handle, PCI_CONF_ILINE);
E 23
I 23
	revid = pci_config_get8(conf_ha, PCI_CONF_REVID);
	ilr = pci_config_get32(conf_ha, PCI_CONF_ILINE);
E 23
	DPRINTF(0, (CE_CONT, "!%s%d: ilr 0x%08x", drv_name, unit, ilr));
E 16

D 16
		/*
		 * Check if chip is supported.
		 */
E 16
I 16
D 22
	is_pcie = gem_is_pcie(dip, conf_handle);
E 22
I 22
D 23
	pcie_cap = gem_search_pci_cap(dip, conf_handle, PCI_CAP_ID_PCI_E);
	if (pcie_cap) {
		uint32_t	devcap;
		uint32_t	devcsr;
E 23
I 23
	pcie_cap = gem_search_pci_cap(dip, conf_ha, PCI_CAP_ID_PCI_E);
I 28
	msi_cap = gem_search_pci_cap(dip, conf_ha, PCI_CAP_ID_MSI);
E 28
	pci_config_teardown(&conf_ha);
E 23
E 22
E 16

I 22
D 23
		devcap = pci_config_get32(conf_handle, pcie_cap + 4);
		devcsr = pci_config_get32(conf_handle, pcie_cap + 8);

		DPRINTF(0, (CE_CONT,
		    "!%s: pcie cap:%x, dev_cap:%x, dev_csr:%x",
		    __func__,
		    pci_config_get32(conf_handle, pcie_cap),
		    devcap, devcsr));

		/*
		 * increase max read request 2:512, 3:1024, 4:2048
		 */
		if ((devcsr & (7 << 12)) < (3 << 12)) {
			devcsr = (devcsr & ~(7 << 12)) | (3 << 12);
			pci_config_put32(conf_handle,
			    pcie_cap + 8, devcsr);
		}
	}
E 22
I 16
	pci_config_teardown(&conf_handle);

E 23
	switch (cmd) {
D 21
	case DDI_RESUME: {
		struct gem_dev  *dp;

E 21
I 21
	case DDI_RESUME:
E 21
		dp = GEM_GET_DEV(dip);

D 22
		gani_mii_patch(dp);
E 22
D 21
		return gem_resume(dip);
	}
E 21
I 21
		if ((i = gem_resume(dip)) == DDI_SUCCESS) {
			gani_stat_timeout(dp);
		}
		return (i);

E 21
	case DDI_ATTACH:
E 16
		/*
D 16
		 * Make sure the I/O access and memory access, master enable.
		 * Bits are set in the config command register
E 16
I 16
D 28
		 * Map in the device registers.
D 22
		 * XXX - MEM64 for PCI-E cause to hung the system.
E 22
I 22
D 24
		 * XXX - MEM32 for PCI-E cause to hang system.
E 24
I 24
		 * XXX - MEM32 for PCI-E caused to hang system.
E 28
I 28
		 * Map in the device registers. Try to map register
		 * in pci memory space first.
		 *  rnumber 1: i/o
		 *  rnumber 2: mem32(pci) or mem64(pcie)
E 28
E 24
E 22
E 16
		 */
D 16
		if (pci_config_setup(dip, &conf_handle) != DDI_SUCCESS) {
			cmn_err(CE_WARN, "!%s%d: pci_config_setup failed",
				drv_name, unit);
E 16
I 16
D 28
		if (gem_pci_regs_map_setup(dip,
E 28
I 17
#ifdef MAP_MEM
E 17
D 22
			(is_pcie ? PCI_ADDR_MEM64 : PCI_ADDR_MEM32),
E 22
I 22
D 28
		    (pcie_cap ? PCI_ADDR_MEM64 : PCI_ADDR_MEM32),
E 22
I 17
#else
D 22
			PCI_ADDR_IO,
E 22
I 22
		    PCI_ADDR_IO,
E 28
I 28
		if (ddi_regs_map_setup(dip, 2, &base, 0, 0,
		    &gani_dev_attr, &regs_ha) != DDI_SUCCESS) {
E 28
E 22
#endif
E 17
D 22
			PCI_ADDR_MASK,
			&gani_dev_attr,
			(caddr_t *)&base, &regs_handle) != DDI_SUCCESS) {
E 22
I 22
D 28
		    PCI_ADDR_MASK,
		    &gani_dev_attr,
D 23
		    (void *)&base, &regs_handle) != DDI_SUCCESS) {
E 23
I 23
		    (void *)&base, &regs_ha) != DDI_SUCCESS) {
E 23
E 22
E 16
			goto err;
E 28
I 28
			if (ddi_regs_map_setup(dip, 1, &base, 0, 0,
			    &gani_dev_attr, &regs_ha) != DDI_SUCCESS) {
				goto err;
			}
#ifdef MAP_MEM
E 28
		}
I 28
#endif
E 28
D 16
		vid = pci_config_get16(conf_handle, PCI_CONF_VENID);
		did = pci_config_get16(conf_handle, PCI_CONF_DEVID);
		revid = pci_config_get8(conf_handle, PCI_CONF_REVID);
		comm = pci_config_get16(conf_handle, PCI_CONF_COMM);
		if ((comm & (PCI_COMM_IO | PCI_COMM_ME)) !=
						(PCI_COMM_IO | PCI_COMM_ME)) {
			comm |= PCI_COMM_IO | PCI_COMM_ME;
			pci_config_put16(conf_handle, PCI_CONF_COMM, comm);
		}
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
				ps = pci_config_get32(conf_handle, cap_ptr + 4);
E 16

D 6
				DPRINTF(0, (CE_CONT,
E 6
I 6
D 16
				DPRINTF(2, (CE_CONT,
E 6
				"!%s%d: pmc found at 0x%x: ps: 0x%08x",
				drv_name, unit, cap_ptr, ps));

				ps &= ~PCI_PMCSR_STATE_MASK;
				pci_config_put32(conf_handle, cap_ptr + 4, ps);
				break;
			}
			/* get next_ptr */
			cap_ptr = (cap >> 8) & 0xff;
		}

		ilr = pci_config_get32(conf_handle, PCI_CONF_ILINE);
		DPRINTF(0, (CE_CONT, "!%s%d: ilr 0x%08x", drv_name, unit, ilr));

		pci_config_teardown(&conf_handle);

E 16
		/*
		 * Check hardware revision
		 */
D 22
		tcr = ddi_get32(regs_handle,
D 16
			(uint32_t *)((caddr_t)base + TCR)) & TCR_MACVER;
E 16
I 16
			(uint32_t *)((caddr_t)base + TCR)) & TCR_HWVERID;
E 22
I 22
D 23
		tcr = ddi_get32(regs_handle, (void *)((caddr_t)base + TCR));
E 23
I 23
D 28
		tcr = ddi_get32(regs_ha, (void *)((caddr_t)base + TCR));
E 28
I 28
		tcr = ddi_get32(regs_ha, (void *)(base + TCR));
E 28
E 23
E 22
E 16

D 10
		for (i = 0; i < CHIPTABLESIZE; i++) {
			if ((chiptbl_8169[i].tcr_val & tcr) != 0) {
E 10
I 10
		for (p = chiptbl_8169, i = 0; i < CHIPTABLESIZE; p++, i++) {
D 22
			if (p->tcr_val == tcr) {
E 22
I 22
			if (((p->tcr_val ^ tcr) & p->tcr_mask) == 0) {
E 22
E 10
				/* found */
D 10
				p = &chiptbl_8169[i];
E 10
				goto chip_found;
			}
		}

		cmn_err(CE_WARN,
D 22
			"!%s%d: attach: unknown mac version: tcr:0x%08x",
			drv_name, unit, tcr);
E 22
I 22
		    "!%s%d: attach: unknown mac version: tcr:0x%08x",
		    drv_name, unit, tcr);
E 22

D 10
		p = &chiptbl_8169[CHIPTABLESIZE-1];	/* MAC ver B */
E 10
I 10
D 16
		p = &chiptbl_8169[0];	/* MAC ver B */
E 16
I 16
D 18
		p = &chiptbl_8169[0];	/* 8169 */
E 18
I 18
D 28
		p = &chiptbl_8169[0];	/* choose the oldest 8169 chipset */
E 28
I 28
		/* choose the oldest 8169 chipset */
		p = &chiptbl_8169[0];
E 28
E 18
E 16
E 10

chip_found:
D 27
		cmn_err(CE_CONT, "!%s%d: chip is %s rev:0x%02x tcr:0x%08x",
D 22
			drv_name, unit, p->name, revid, tcr);
E 22
I 22
		    drv_name, unit, p->name, revid, tcr);
E 27
I 27
		cmn_err(CE_CONT,
D 28
		    "!%s%d: chip is %s rev:0x%02x tcr:0x%08x pcie_cap:0x%02x",
		    drv_name, unit, p->name, revid, tcr, pcie_cap);
E 28
I 28
		    "!%s%d: chip is %s rev:0x%02x tcr:0x%08x "
		    "pcie_cap:0x%02x msi_cap:0x%02x",
		    drv_name, unit, p->name, revid, tcr, pcie_cap, msi_cap);
E 28
E 27
E 22

D 23
		if ((ddi_get8(regs_handle,
D 22
			(uint8_t *)((caddr_t)base + PHYS)) & PHYS_EnTBI) != 0) {
E 22
I 22
		    (uint8_t *)((caddr_t)base + PHYS)) & PHYS_EnTBI)) {
E 22
			cmn_err(CE_CONT,
D 10
				"%s: tbi interfaces isn't supported",
				dp->name);
E 10
I 10
D 22
				"!%s%d: tbi interfaces isn't supported",
				drv_name, unit);
E 10
			goto err;	
E 22
I 22
			    "!%s%d: tbi interfaces isn't supported",
			    drv_name, unit);
			goto err;
E 22
		}

E 23
I 16
D 22
		lp = (struct gani_dev *)
				kmem_zalloc(sizeof(struct gani_dev), KM_SLEEP);
E 22
I 22
		lp = kmem_zalloc(sizeof (struct gani_dev), KM_SLEEP);
E 22
		lp->chip = p;
I 22
		lp->pcie_cap = pcie_cap;
I 28
		lp->msi = msi_cap != 0;
E 28
I 23
		lp->isr_pended = 0;
		lp->initialized = B_FALSE;
I 28
		lp->tcr = tcr & p->tcr_mask;
E 28
E 23
E 22

		/* read config2 register */
D 28
		if (GANI_PCIE(p->type)) {
E 28
I 28
		if (GANI_PCIE(lp)) {
E 28
			lp->busclk = BUSCLK_PCIE; /* PCI-E (125MHz) */
		} else {
D 22
			lp->busclk = 
			ddi_get8(regs_handle,
E 22
I 22
D 23
			lp->busclk = ddi_get8(regs_handle,
E 23
I 23
			lp->busclk = ddi_get8(regs_ha,
E 23
E 22
D 28
			    (uint8_t *)((caddr_t)base + CFG2)) & CFG2_PCICLKF
E 28
I 28
			    (uint8_t *)(base + CFG2)) & CFG2_PCICLKF
E 28
D 22
				 ? BUSCLK_PCI66 : BUSCLK_PCI33;
E 22
I 22
			    ? BUSCLK_PCI66 : BUSCLK_PCI33;
E 22
		}
D 22
		DPRINTF(0, (CE_CONT, "!%s%d: busclk:%d",
			drv_name, unit, lp->busclk));
E 22
I 22
		DPRINTF(0, (CE_CONT, "!%s%d: busclk:%d, cfg2:0x%x",
		    drv_name, unit, lp->busclk,
D 23
		    ddi_get8(regs_handle, (uint8_t *)((caddr_t)base + CFG2))));
E 23
I 23
D 28
		    ddi_get8(regs_ha, (uint8_t *)((caddr_t)base + CFG2))));
E 28
I 28
		    ddi_get8(regs_ha, (uint8_t *)(base + CFG2))));
E 28
E 23
E 22

E 16
		/*
		 * construct gem configration
		 */
D 22
		gcp = (struct gem_conf *) kmem_zalloc(sizeof(*gcp), KM_SLEEP);
E 22
I 22
D 27
		gcp = (struct gem_conf *)kmem_zalloc(sizeof (*gcp), KM_SLEEP);
E 27
I 27
		gcp = kmem_zalloc(sizeof (*gcp), KM_SLEEP);
E 27
E 22

		/* name */
D 22
		sprintf(gcp->gc_name, "%s%d", drv_name, unit);
E 22
I 22
		(void) sprintf(gcp->gc_name, "%s%d", drv_name, unit);
E 22

D 22
		gcp->gc_tx_buf_align = sizeof(uint8_t) - 1;
E 22
I 22
		gcp->gc_tx_buf_align = sizeof (uint8_t) - 1;
E 22
D 9
#ifdef TDU_TEST
		gcp->gc_tx_max_frags = 1;
#else
E 9
D 16
		gcp->gc_tx_max_frags = GEM_MAXTXFRAGS;
D 9
#endif
E 9
D 4
		gcp->gc_tx_desc_size = sizeof(struct tx_desc)*TX_RING_SIZE;
E 4
I 4
		gcp->gc_tx_desc_size =
D 13
			ROUNDUP2(sizeof(struct tx_desc)*TX_RING_SIZE + TC_SIZE,
				256);
E 13
I 13
			ROUNDUP2(sizeof(struct tx_desc)*TX_RING_SIZE,
				DESC_BASE_ALIGN) + TC_SIZE,
E 13
E 4
		gcp->gc_tx_ring_size = TX_RING_SIZE;
E 16
I 16
		gcp->gc_tx_max_frags = TX_MAX_FRAGS;
I 22
D 23
#ifdef WA_NO_TPPOLL_WRAP
		gcp->gc_tx_max_descs_per_pkt = 2*gcp->gc_tx_max_frags - 1;
#else
E 23
E 22
D 19
		gcp->gc_tx_max_descs_per_pkt = TX_MAX_FRAGS;
E 19
I 19
		gcp->gc_tx_max_descs_per_pkt = gcp->gc_tx_max_frags;
I 22
D 23
#endif
E 23
E 22
E 19
		gcp->gc_tx_desc_unit_shift = 4;
E 16
D 22
		gcp->gc_tx_buf_size  = TX_BUF_SIZE;
E 22
I 22
		gcp->gc_tx_buf_size = TX_BUF_SIZE;
E 22
D 16
		gcp->gc_tx_max_descs_per_pkt = gcp->gc_tx_max_frags;
D 4
		gcp->gc_tx_auto_pad  = FALSE;
E 4
I 4
		gcp->gc_tx_auto_pad  = TRUE;
E 16
I 16
		gcp->gc_tx_buf_limit = gcp->gc_tx_buf_size;
		gcp->gc_tx_ring_size = TX_RING_SIZE;
D 22
		gcp->gc_tx_ring_limit= gcp->gc_tx_ring_size;
		gcp->gc_tx_auto_pad  = B_TRUE;
E 22
I 22
		gcp->gc_tx_ring_limit = gcp->gc_tx_ring_size;
		gcp->gc_tx_auto_pad = B_TRUE;
E 22
E 16
E 4
		gcp->gc_tx_copy_thresh = gani_tx_copy_thresh;
D 16

D 9
		gcp->gc_rx_buf_align = sizeof(uint32_t) - 1;
E 9
I 9
		gcp->gc_rx_buf_align = 64 - 1;
E 16
I 16
D 22
		gcp->gc_tx_desc_write_oo = B_FALSE;
#ifdef CONFIG_OO
D 19
		gcp->gc_tx_desc_write_oo = B_TRUE;
		gcp->gc_tx_max_frags = 1;
		gcp->gc_tx_max_descs_per_pkt = 1;
E 19
I 19
		gcp->gc_tx_desc_write_oo = (TX_MAX_FRAGS == 1);
E 19
#endif
E 22
I 22

E 22
D 28
		gcp->gc_rx_buf_align = (GANI_PCIE(p->type) ? 8 : 1) - 1;
E 28
I 28
		gcp->gc_rx_buf_align = (GANI_PCIE(lp) ? 8 : 1) - 1;
E 28
E 16
E 9
		gcp->gc_rx_max_frags = 1;
D 4
		gcp->gc_rx_desc_size = sizeof(struct rx_desc) * RX_RING_SIZE;
E 4
I 4
D 16
		gcp->gc_rx_desc_size =
D 13
			ROUNDUP2(sizeof(struct rx_desc) * RX_RING_SIZE, 256);
E 13
I 13
			ROUNDUP2(sizeof(struct rx_desc) * RX_RING_SIZE,
				DESC_BASE_ALIGN);
E 16
I 16
		gcp->gc_rx_desc_unit_shift = 4;
E 16
E 13
E 4
		gcp->gc_rx_ring_size = RX_RING_SIZE;
D 16
		gcp->gc_rx_buf_size  = RX_BUF_SIZE;
E 16
I 16
D 22
		gcp->gc_rx_buf_max   = RX_BUF_SIZE;
E 22
I 22
		gcp->gc_rx_buf_max = RX_BUF_SIZE;
E 22
E 16
		gcp->gc_rx_copy_thresh = gani_rx_copy_thresh;
D 5
		gcp->gc_rx_buf_max  = gcp->gc_rx_buf_size;
E 5
I 5
D 16
		gcp->gc_rx_buf_max  = gcp->gc_rx_buf_size + 1;
E 16
I 16
		gcp->gc_io_area_size = TC_SIZE;
E 16
E 5

		/* map attributes */
D 5
		gcp->gc_dev_attr  = gani_dev_attr;
		gcp->gc_buf_attr  = gani_buf_attr;
		gcp->gc_desc_attr = gani_dev_attr;
E 5
I 5
D 19
		STRUCT_COPY(gcp->gc_dev_attr, gani_dev_attr);
		STRUCT_COPY(gcp->gc_buf_attr, gani_buf_attr);
D 9
		STRUCT_COPY(gcp->gc_desc_attr, gani_buf_attr);
E 9
I 9
D 16
		STRUCT_COPY(gcp->gc_desc_attr, gani_dev_attr);
E 16
I 16
		STRUCT_COPY(gcp->gc_desc_attr, gani_buf_attr);
E 19
I 19
		gcp->gc_dev_attr = gani_dev_attr;
		gcp->gc_buf_attr = gani_buf_attr;
		gcp->gc_desc_attr = gani_buf_attr;
E 19
E 16
E 9
E 5

		/* dma attributes */
D 5
		gcp->gc_dma_attr_desc  = gani_dma_attr_nosc32;
		gcp->gc_dma_attr_txbuf = gani_dma_attr_buf32;
E 5
I 5
D 19
		STRUCT_COPY(gcp->gc_dma_attr_desc, gani_dma_attr_desc);
E 19
I 19
		gcp->gc_dma_attr_desc = gani_dma_attr_desc;
E 19
D 16
		STRUCT_COPY(gcp->gc_dma_attr_txbuf, gani_dma_attr_buf32);
E 16
I 16
D 24
		if (GANI_PCIE(p->type)) {
E 24
I 24
		if (gani_64bit_addr) {
E 24
D 19
			STRUCT_COPY(gcp->gc_dma_attr_txbuf,gani_dma_attr_buf64);
E 19
I 19
			gcp->gc_dma_attr_txbuf = gani_dma_attr_buf64;
E 19
		} else {
D 24
#ifdef CONFIG_DAC
E 24
D 19
			STRUCT_COPY(gcp->gc_dma_attr_txbuf,gani_dma_attr_buf64);
E 19
I 19
D 27
			gcp->gc_dma_attr_txbuf = gani_dma_attr_buf64;
E 27
I 27
			gcp->gc_dma_attr_txbuf = gani_dma_attr_buf32;
E 27
E 19
D 24
#else
D 19
			STRUCT_COPY(gcp->gc_dma_attr_txbuf,gani_dma_attr_buf32);
E 19
I 19
			gcp->gc_dma_attr_txbuf = gani_dma_attr_buf32;
E 19
#endif
E 24
		}
		gcp->gc_dma_attr_txbuf.dma_attr_align = gcp->gc_tx_buf_align+1;
E 16
E 5
I 3
		gcp->gc_dma_attr_txbuf.dma_attr_sgllen = gcp->gc_tx_max_frags;
E 3
D 5
		gcp->gc_dma_attr_rxbuf = gani_dma_attr_buf32;
E 5
I 5
D 16
		STRUCT_COPY(gcp->gc_dma_attr_rxbuf, gani_dma_attr_buf32);
E 16
I 16

D 24
		if (GANI_PCIE(p->type)) {
E 24
I 24
		if (gani_64bit_addr) {
E 24
D 19
			STRUCT_COPY(gcp->gc_dma_attr_rxbuf,gani_dma_attr_buf64);
E 19
I 19
			gcp->gc_dma_attr_rxbuf = gani_dma_attr_buf64;
E 19
		} else {
D 24
#ifdef CONFIG_DAC
D 19
			STRUCT_COPY(gcp->gc_dma_attr_rxbuf,gani_dma_attr_buf64);
E 19
I 19
			gcp->gc_dma_attr_rxbuf = gani_dma_attr_buf64;
E 19
#else
E 24
D 19
			STRUCT_COPY(gcp->gc_dma_attr_rxbuf,gani_dma_attr_buf32);
E 19
I 19
			gcp->gc_dma_attr_rxbuf = gani_dma_attr_buf32;
E 19
D 24
#endif
E 24
		}
E 16
E 5
I 4
		gcp->gc_dma_attr_rxbuf.dma_attr_align = gcp->gc_rx_buf_align+1;
E 4
I 3
		gcp->gc_dma_attr_rxbuf.dma_attr_sgllen = gcp->gc_rx_max_frags;
E 3

		/* time out parameters */
D 5
		gcp->gc_tx_timeout = 2*ONESEC;
E 5
I 5
D 22
		gcp->gc_tx_timeout = 5*ONESEC;
E 22
I 22
D 23
		gcp->gc_tx_timeout = 3*ONESEC;
E 23
I 23
		gcp->gc_tx_timeout = GEM_TX_TIMEOUT;
E 23
E 22
E 5
		gcp->gc_tx_timeout_interval = ONESEC;

D 23
		/* flow control */
D 6
		gcp->gc_flow_control = TRUE;
E 6
I 6
		gcp->gc_flow_control = FLOW_CONTROL_RX_PAUSE;
E 23
I 23
D 28
		/* flow control was FLOW_CONTROL_RX_PAUSE */
E 28
I 28
		/* flow control capability */
		/* XXX - rx hangs for 8168 when flow control is enabled */
E 28
		gcp->gc_flow_control = FLOW_CONTROL_NONE;
E 23
E 6
I 3
D 5
		gcp->gc_flow_control = FALSE;
E 5
E 3

D 22
		/* mii mode */
D 16
		gcp->gc_mii_mode = GEM_MODE_1000BASET;
E 16
I 16
		gcp->gc_mii_mode =
			(p->flags & 0xf) == GEM_SPD_1000 ?
				GEM_MODE_1000BASET : GEM_MODE_100BASETX;
E 16

E 22
		/* MII timeout parameters */
		gcp->gc_mii_link_watch_interval = ONESEC;
D 16
		gcp->gc_mii_an_watch_interval = ONESEC/10;
		gcp->gc_mii_reset_timeout = MII_RESET_TIMEOUT;	/* 1 sec */
D 5
		gcp->gc_mii_an_timeout  = 3*ONESEC;
		gcp->gc_mii_an_wait	= ONESEC/100;
E 5
I 5
D 6
		gcp->gc_mii_an_timeout  = 5*ONESEC;	/* XXX - is it too long? */
		gcp->gc_mii_an_wait	= 2*(ONESEC/100);   /* 20mS */
E 6
I 6
		gcp->gc_mii_an_timeout  = MII_AN_TIMEOUT;
		gcp->gc_mii_an_wait	= 0;
E 6
E 5
		gcp->gc_mii_linkdown_timeout = MII_LINKDOWN_TIMEOUT;
E 16
I 16
D 22
		gcp->gc_mii_an_watch_interval   = ONESEC/10;
		gcp->gc_mii_reset_timeout       = MII_RESET_TIMEOUT; /* 1 sec */
		gcp->gc_mii_an_timeout          = MII_AN_TIMEOUT;
D 18
		gcp->gc_mii_an_wait	        = 0;
E 18
I 18
		gcp->gc_mii_an_wait	        = ONESEC;
E 18
		gcp->gc_mii_linkdown_timeout    = MII_LINKDOWN_TIMEOUT;
E 22
I 22
		gcp->gc_mii_an_watch_interval = ONESEC/10;
D 28
		if (GANI_PCIE_FAST(p->type)) {
E 28
I 28
D 30
		if (GANI_PCIE_FAST(lp)) {
E 28
			gcp->gc_mii_reset_timeout = 25*(ONESEC/10);
		} else {
			gcp->gc_mii_reset_timeout = ONESEC;
		}
E 30
I 30
		gcp->gc_mii_reset_timeout = 25*(ONESEC/10);
E 30
		gcp->gc_mii_an_timeout = MII_AN_TIMEOUT;
		gcp->gc_mii_an_wait = ONESEC;
		gcp->gc_mii_linkdown_timeout = MII_LINKDOWN_TIMEOUT;
E 22
E 16

D 5
		gcp->gc_mii_an_delay	    = 0;
E 5
I 5
D 13
		/* it seems rtl8169 needs delay to recognize PHY status */
E 13
I 13
		/* rtl8169 seems to delay to recognize PHY status */
E 13
D 6
		gcp->gc_mii_an_delay	    = 2*(ONESEC/100);	/* 20mS */
E 6
I 6
D 16
		gcp->gc_mii_an_delay	    = ONESEC/10;	/* 100mS */
E 6
E 5
D 13
		gcp->gc_mii_linkdown_action = MII_ACTION_RESET;
E 13
I 13
		gcp->gc_mii_linkdown_action = MII_ACTION_NONE;
E 16
I 16
D 22
		gcp->gc_mii_an_delay	      = ONESEC/10;	/* 100mS */
D 20
		gcp->gc_mii_linkdown_action   = MII_ACTION_NONE;
E 16
		gcp->gc_mii_linkdown_timeout_action = MII_ACTION_NONE;
E 20
I 20
		gcp->gc_mii_linkdown_action   = MII_ACTION_RSA;
E 22
I 22
		gcp->gc_mii_an_delay = ONESEC/10;	/* 100mS */
		/* we must reset rtl8169 phy to update advert register */
		gcp->gc_mii_linkdown_action = MII_ACTION_RESET;

		/*
		 * XXX - MAC_VER_8169S or later chipset requires reset
		 * on link down timeout for 1Gbps connection
		 */
E 22
		gcp->gc_mii_linkdown_timeout_action = MII_ACTION_RESET;
E 20
E 13
D 16
		gcp->gc_mii_dont_reset      = FALSE;
		gcp->gc_mii_an_oneshot      = FALSE;
E 16
I 16
D 22
		gcp->gc_mii_dont_reset        = B_FALSE;
		gcp->gc_mii_an_oneshot        = B_FALSE;
E 22
I 22
		gcp->gc_mii_dont_reset = B_FALSE;
		gcp->gc_mii_an_oneshot = B_FALSE;
E 22
		gcp->gc_mii_hw_link_detection = B_TRUE;
E 16

		/* I/O methods */

		/* mac operation */
D 16
		gcp->gc_attach_chip = &gani_attach_chip;
		gcp->gc_reset_chip  = &gani_reset_chip;
		gcp->gc_init_chip   = &gani_init_chip;
		gcp->gc_start_chip  = &gani_start_chip;
		gcp->gc_stop_chip   = &gani_stop_chip;
		gcp->gc_multicast_hash = &gani_mcast_hash;
E 16
I 16
D 22
		gcp->gc_attach_chip   = &gani_attach_chip;
		gcp->gc_reset_chip    = &gani_reset_chip;
		gcp->gc_init_chip     = &gani_init_chip;
		gcp->gc_start_chip    = &gani_start_chip;
		gcp->gc_stop_chip     = &gani_stop_chip;
		gcp->gc_multicast_hash= &gani_mcast_hash;
E 22
I 22
		gcp->gc_attach_chip = &gani_attach_chip;
I 31
#ifdef GEM_CONFIG_JUMBO_FRAME
		gcp->gc_fixup_params = &gani_fixup_params;
#endif
E 31
D 23
		if (GANI_PCI(p->type)) {
			gcp->gc_reset_chip = &gani_reset_chip_8169;
			gcp->gc_init_chip = &gani_init_chip_8169;
		} else if (GANI_PCIE_GIGA(p->type)) {
			gcp->gc_reset_chip = &gani_reset_chip_8168;
			gcp->gc_init_chip = &gani_init_chip_8168;
		} else {
			gcp->gc_reset_chip = &gani_reset_chip_8101;
			gcp->gc_init_chip = &gani_init_chip_8101;
		}
E 23
I 23
		gcp->gc_reset_chip = &gani_reset_chip;
		gcp->gc_init_chip = &gani_init_chip;
E 23
		gcp->gc_start_chip = &gani_start_chip;
		gcp->gc_stop_chip = &gani_stop_chip;
		gcp->gc_multicast_hash = &gani_mcast_hash;
E 22
E 16
		gcp->gc_set_rx_filter = &gani_set_rx_filter;
D 16
		gcp->gc_set_media   = &gani_set_media;
		gcp->gc_get_stats   = &gani_get_stats;
		gcp->gc_interrupt   = &gani_interrupt;
E 16
I 16
D 22
		gcp->gc_set_media     = &gani_set_media;
		gcp->gc_get_stats     = &gani_get_stats;
		gcp->gc_interrupt     = &gani_interrupt;
E 22
I 22
		gcp->gc_set_media = &gani_set_media;
		gcp->gc_get_stats = &gani_get_stats;
		gcp->gc_interrupt = &gani_interrupt;
E 22
E 16

		/* descriptor operation */
		gcp->gc_tx_desc_write = &gani_tx_desc_write;
		gcp->gc_rx_desc_write = &gani_rx_desc_write;
D 16
		gcp->gc_tx_desc_stat = &gani_tx_desc_stat;
		gcp->gc_rx_desc_stat = &gani_rx_desc_stat;
		gcp->gc_tx_desc_init = &gani_tx_desc_init;
		gcp->gc_rx_desc_init = &gani_rx_desc_init;
E 16
I 16
D 22
		gcp->gc_tx_start      = &gani_tx_start;
		gcp->gc_rx_start      = NULL;
		gcp->gc_tx_desc_stat  = &gani_tx_desc_stat;
		gcp->gc_rx_desc_stat  = &gani_rx_desc_stat;
		gcp->gc_tx_desc_init  = &gani_tx_desc_init;
		gcp->gc_rx_desc_init  = &gani_rx_desc_init;
E 22
I 22
		gcp->gc_tx_start = &gani_tx_start;
		gcp->gc_rx_start = NULL;
		gcp->gc_tx_desc_stat = &gani_tx_desc_stat;
		gcp->gc_rx_desc_stat = &gani_rx_desc_stat;
		gcp->gc_tx_desc_init = &gani_tx_desc_init;
		gcp->gc_rx_desc_init = &gani_rx_desc_init;
E 22
E 16
D 5
		gcp->gc_tx_desc_clean = &gani_tx_desc_clean;
		gcp->gc_rx_desc_clean = &gani_rx_desc_clean;
E 5
I 5
		gcp->gc_tx_desc_clean = &gani_tx_desc_init;
		gcp->gc_rx_desc_clean = &gani_rx_desc_init;
E 5

		/* mii operations */
D 16
		gcp->gc_mii_init   = &gani_mii_init;
		gcp->gc_mii_config = &gem_mii_config_default;
		gcp->gc_mii_sync  = &gani_mii_sync;
		gcp->gc_mii_read  = &gani_mii_read;
		gcp->gc_mii_write = &gani_mii_write;
		gcp->gc_mii_tune_phy = NULL;
E 16
I 16
D 22
		gcp->gc_mii_init      = &gani_mii_init;
		gcp->gc_mii_config    = &gem_mii_config_default;
		gcp->gc_mii_sync      = &gani_mii_sync;
		gcp->gc_mii_read      = &gani_mii_read;
		gcp->gc_mii_write     = &gani_mii_write;
		gcp->gc_mii_tune_phy  = NULL;
E 22
I 22
		gcp->gc_mii_probe = &gani_mii_probe;
		gcp->gc_mii_init = &gani_mii_init;
		gcp->gc_mii_config = &gani_mii_config;
		gcp->gc_mii_sync = &gani_mii_sync;
		gcp->gc_mii_read = &gani_mii_read;
		gcp->gc_mii_write = &gani_mii_write;
		gcp->gc_mii_tune_phy = NULL;
E 22
E 16

I 28
		/* MSI/MSIX interrupts */
#ifdef CONFIG_INTR_MSI
		gcp->gc_nintrs_req = 1;
#else
		gcp->gc_nintrs_req = 0;
#endif

I 29
		/* offload and jumbo frame */
D 30
		gcp->gc_max_lso = 16 * 1024;
E 30
I 30
		gcp->gc_max_lso = 16 * 1024 - 1;
E 30
D 31
		gcp->gc_max_mtu = ETHERMTU;
E 31
I 31
		gcp->gc_max_mtu = p->max_mtu;
E 31
		gcp->gc_default_mtu = ETHERMTU;
		gcp->gc_min_mtu = ETHERMIN - sizeof (struct ether_header);

E 29
E 28
D 16
		lp = (struct gani_dev *)
				kmem_zalloc(sizeof(struct gani_dev), KM_SLEEP);
		lp->chip = p;
D 5
#ifdef NOINTR_WORKAROUND
		ddi_set_driver_private(dip, NULL);
E 5
I 5

		/* read config2 register */
		lp->cfg2 = ddi_get8(regs_handle,
				(uint8_t *)((caddr_t)base + CFG2));
D 6
		DPRINTF(0, (CE_CONT, "!%s%d: cfg2:0x%02x",
E 6
I 6
		DPRINTF(2, (CE_CONT, "!%s%d: cfg2:0x%02x",
E 6
			drv_name, unit, lp->cfg2));
E 16
D 6
#ifdef IO_BARRIER
E 6
I 6
D 9
#ifdef OPT_TDU_INTR
E 6
		mutex_init(&lp->reglock, NULL, MUTEX_DRIVER, NULL);
E 5
#endif
E 9
D 22
		dp = gem_do_attach(dip, gcp, base, &regs_handle,
					lp, sizeof(struct gani_dev));
		kmem_free(gcp, sizeof(*gcp));
E 22
I 22
D 23
		dp = gem_do_attach(dip, 0, gcp, base, &regs_handle,
E 23
I 23
		dp = gem_do_attach(dip, 0, gcp, base, &regs_ha,
E 23
		    lp, sizeof (struct gani_dev));
		kmem_free(gcp, sizeof (*gcp));
E 22

D 3
		if (dp != NULL) {
			return DDI_SUCCESS;
E 3
I 3
		if (dp == NULL) {
			goto err_free_mem;
E 3
		}
I 3

D 4
#ifdef OPT_TX_INTR
		if (ddi_add_softintr(dp->dip,
					DDI_SOFTINT_LOW, &lp->soft_id,
					NULL, NULL,
					(uint_t (*)(caddr_t))&gani_update_imr,
					(caddr_t)dp) != DDI_SUCCESS) {
			goto  err_free_mem;
		}
#endif
E 4
D 21
		return DDI_SUCCESS;
E 21
I 21
		gani_stat_timeout(dp);
E 21
D 4
		return DDI_SUCCESS;
E 4
I 4

I 21
		return (DDI_SUCCESS);

E 21
E 4
E 3
err_free_mem:
D 22
		kmem_free(lp, sizeof(struct gani_dev));
E 22
I 22
		kmem_free(lp, sizeof (struct gani_dev));
E 22
err:
D 22
		return DDI_FAILURE;
E 22
I 22
		return (DDI_FAILURE);
E 22
	}
I 16

E 16
D 22
	return DDI_FAILURE;
E 22
I 22
	return (DDI_FAILURE);
E 22
}

static int
ganidetach(dev_info_t *dip, ddi_detach_cmd_t cmd)
{
I 3
D 4
#ifdef OPT_TX_INTR
E 4
	struct gem_dev  *dp;
I 21
	struct gani_dev	*lp;
E 21
D 16
	gld_mac_info_t  *macinfo;
	struct gani_dev	*lp;
E 16

D 16
	macinfo = (gld_mac_info_t *)ddi_get_driver_private(dip);
	dp = (struct gem_dev *)macinfo->gldm_private;
	lp = (struct gani_dev *)dp->private;
E 16
I 16
	dp = GEM_GET_DEV(dip);
I 21
D 22
	lp = (struct gani_dev *) dp->private;
E 22
I 22
	lp = dp->private;
E 22
E 21
E 16
D 4
#endif
E 4
I 4

E 4
E 3
D 16
	if (cmd == DDI_DETACH) {
I 13
#ifdef notdef
		/*
		 * disable PHY
		 */
		gani_mii_write(dp, MII_CONTROL, MII_CONTROL_ISOLATE | MII_CONTROL_PWRDN);
#endif
E 16
I 16
	switch (cmd) {
	case DDI_DETACH:
E 16
E 13
I 5
D 6
#ifdef IO_BARRIER
E 6
I 6
D 9
#ifdef OPT_TDU_INTR
E 6
		mutex_destroy(&lp->reglock);
#endif
E 9
E 5
I 3
D 4
#ifdef OPT_TX_INTR
		ddi_remove_softintr(lp->soft_id);
#endif
E 4
E 3
D 21
		return  gem_do_detach(dip);
I 16

E 21
	case DDI_SUSPEND:
D 21
		return gem_suspend(dip);
E 21
I 21
		/* Ensure statistics timer routine stopped */
		mutex_enter(&lp->stat_lock);
		if (lp->stat_to_id != 0) {
			timeout_id_t	old_id;

			do {
				old_id = lp->stat_to_id;
				mutex_exit(&lp->stat_lock);
D 22
				untimeout(old_id);
E 22
I 22
				(void) untimeout(old_id);
E 22
				mutex_enter(&lp->stat_lock);
			} while (old_id != lp->stat_to_id);
			lp->stat_to_id = 0;
		}
		mutex_exit(&lp->stat_lock);

		switch (cmd) {
		case DDI_DETACH:
			mutex_destroy(&lp->stat_lock);
D 22
			return  gem_do_detach(dip);
E 22
I 22
			return (gem_do_detach(dip));
E 22

		case DDI_SUSPEND:
D 22
			return gem_suspend(dip);
E 22
I 22
			return (gem_suspend(dip));
E 22
		}
E 21
E 16
	}
I 4

E 4
D 22
	return DDI_FAILURE;
E 22
I 22
	return (DDI_FAILURE);
E 22
}

/* ======================================================== */
/*
 * OS depend (loadable streams driver) routine
 */
/* ======================================================== */
I 22
#ifdef GEM_CONFIG_GLDv3
D 27
DDI_DEFINE_STREAM_OPS(gani_ops, nulldev, nulldev, ganiattach, ganidetach,
    nodev, NULL, D_MP, NULL);
E 27
I 27
GEM_STREAM_OPS(gani_ops, ganiattach, ganidetach);
E 27
#else
E 22
static	struct module_info ganiminfo = {
	0,			/* mi_idnum */
	"gani",			/* mi_idname */
	0,			/* mi_minpsz */
D 4
	ETHERMTU,		/* mi_maxpsz */
	32*1024,		/* mi_hiwat */
E 4
I 4
D 6
	INFPSZ,			/* mi_maxpsz */
	INT32_MAX,		/* mi_hiwat */
E 6
I 6
D 9
	RMS_MASK,		/* mi_maxpsz */
E 9
I 9
D 17
	8192,			/* mi_maxpsz */
E 9
	TX_BUF_SIZE*ETHERMAX,	/* mi_hiwat */
E 17
I 17
	INFPSZ,			/* mi_maxpsz */
	64*1024,		/* mi_hiwat */
E 17
E 6
E 4
	1,			/* mi_lowat */
};

static	struct qinit ganirinit = {
	(int (*)()) NULL,	/* qi_putp */
D 16
	gld_rsrv,		/* qi_srvp */
	gld_open,		/* qi_qopen */
	gld_close,		/* qi_qclose */
E 16
I 16
	gem_rsrv,		/* qi_srvp */
	gem_open,		/* qi_qopen */
	gem_close,		/* qi_qclose */
E 16
	(int (*)()) NULL,	/* qi_qadmin */
	&ganiminfo,		/* qi_minfo */
	NULL			/* qi_mstat */
};

static	struct qinit ganiwinit = {
D 16
	gld_wput,		/* qi_putp */
	gld_wsrv,		/* qi_srvp */
E 16
I 16
	gem_wput,		/* qi_putp */
	gem_wsrv,		/* qi_srvp */
E 16
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
D 16
	D_NEW|D_MP	/* cb_flag */
E 16
I 16
	D_MP,		/* cb_flag */
D 22
#ifdef notdef /* GEM_CONFIG_MAC */
	CB_REV,		/* cb_rev */
	nodev,		/* cb_aread */
	nodev,		/* cb_awrite */
#endif
E 22
E 16
};

static	struct dev_ops gani_ops = {
	DEVO_REV,	/* devo_rev */
	0,		/* devo_refcnt */
D 16
	gld_getinfo,	/* devo_getinfo */
E 16
I 16
	gem_getinfo,	/* devo_getinfo */
E 16
	nulldev,	/* devo_identify */
	nulldev,	/* devo_probe */
	ganiattach,	/* devo_attach */
	ganidetach,	/* devo_detach */
	nodev,		/* devo_reset */
	&cb_gani_ops,	/* devo_cb_ops */
	NULL,		/* devo_bus_ops */
D 16
	ddi_power	/* devo_power */
E 16
I 16
D 31
	gem_power	/* devo_power */
E 31
I 31
	gem_power,	/* devo_power */
#if DEVO_REV >= 4
	gem_quiesce,	/* devo_quiesce */
#endif
E 31
E 16
};
I 22
#endif /* GEM_CONFIG_GLDv3 */
E 22

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
D 28
	int 	status;
E 28
I 28
	int	status;
E 28

	DPRINTF(2, (CE_CONT, "!gani: _init: called"));
D 16
	status = mod_install(&modlinkage);
E 16

I 16
D 31
	gem_mod_init(&gani_ops, "gani");
E 31
I 31
	status = gem_mod_init(&gani_ops, "gani");
	if (status != DDI_SUCCESS) {
		return (status);
	}
E 31
	status = mod_install(&modlinkage);
	if (status != DDI_SUCCESS) {
		gem_mod_fini(&gani_ops);
	}
E 16
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
I 16
	if (status == DDI_SUCCESS) {
		gem_mod_fini(&gani_ops);
	}
E 16
	return (status);
}

int
_info(struct modinfo *modinfop)
{
	return (mod_info(&modlinkage, modinfop));
}
D 6

E 6
E 1
