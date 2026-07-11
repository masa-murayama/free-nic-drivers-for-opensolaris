h00743
s 00009/00001/05156
d D 1.30 11/08/18 00:09:44 mrym 30 29
c 2.6.2
e
s 00451/00374/04706
d D 1.29 11/08/14 01:15:13 mrym 29 28
c 2.6.2
e
s 01115/01079/03965
d D 1.28 08/07/04 22:31:23 mrym 28 27
c 2.6.1
e
s 00001/00001/05043
d D 1.27 07/09/22 10:53:51 mrym 27 26
c count max changed for solaris8
e
s 00231/00176/04813
d D 1.26 07/09/22 10:50:10 mrym 26 25
c 2.6.0 & ULI suppoted
e
s 00027/00012/04962
d D 1.25 07/09/02 16:09:51 mrym 25 24
c 2.4.1 Uli worked
e
s 00025/00025/04949
d D 1.24 07/01/07 10:15:40 mrym 24 23
c RXMODE_ENABLE fixed
e
s 00018/00004/04956
d D 1.23 07/01/06 21:27:03 mrym 23 22
c RXMODE_ENABLE implemented
e
s 00210/00138/04750
d D 1.22 07/01/06 16:05:35 mrym 22 21
c set_rx_filter clean up
e
s 00027/00007/04861
d D 1.21 07/01/04 19:27:27 mrym 21 20
c hash table size for LC82C115 fixed
e
s 00228/00083/04640
d D 1.20 06/11/01 01:41:50 mrym 20 19
c fixmode for pnic, nway(21144,98715)
e
s 00050/00041/04673
d D 1.19 06/07/16 23:39:21 mrym 19 18
c first release
e
s 00002/00003/04712
d D 1.18 06/05/30 20:56:04 mrym 18 17
c restart_nic fixed
e
s 00979/00714/03736
d D 1.17 06/05/28 18:18:49 mrym 17 16
c 2.2.0
e
s 01228/00905/03222
d D 1.16 05/08/28 12:52:48 mrym 16 15
c 0.9.39
e
s 00090/00071/04037
d D 1.15 05/04/23 01:12:50 mrym 15 14
c 0.9.38
e
s 00131/00086/03977
d D 1.14 05/01/18 03:20:16 mrym 14 13
c for amd64
e
s 00001/00001/04062
d D 1.13 04/06/16 22:54:37 mrym 13 12
c ALLMULTI isn't enabled in set_rx_filter
e
s 00021/00011/04042
d D 1.12 04/06/06 10:33:15 mrym 12 11
c 0.9.35
e
s 00813/00572/03240
d D 1.11 04/05/10 08:49:34 mrym 11 10
c release 0.9.34
e
s 00650/00629/03162
d D 1.10 03/11/10 01:29:54 mrym 10 9
c worked with 82169
e
s 01492/01027/02299
d D 1.9 03/11/03 07:05:33 mrym 9 8
c 0.9.26
e
s 00440/00032/02886
d D 1.8 03/08/02 20:31:31 mrym 8 7
c liteon LC82C168 suppor
e
s 00299/00124/02619
d D 1.7 03/07/05 21:45:22 mrym 7 6
c 
e
s 00262/00122/02481
d D 1.6 03/04/15 21:28:41 mrym 6 5
c release 10
e
s 00007/00006/02596
d D 1.5 03/02/11 22:30:28 mrym 5 4
c 0.9.7
e
s 00001/00003/02601
d D 1.4 03/01/15 22:07:41 mrym 4 3
c 0.9.6
e
s 00170/00046/02434
d D 1.3 03/01/15 00:50:00 mrym 3 2
c tu-0.9.5 for Conexant RS7112
e
s 00722/00440/01758
d D 1.2 02/12/29 02:13:41 mrym 2 1
c 0.9.1 release
e
s 02198/00000/00000
d D 1.1 02/12/22 20:53:48 mrym 1 0
c date and time created 02/12/22 20:53:48 by mrym
e
u
U
f e 0
t
T
I 1
/*
D 2
 *  tu: ADMtek AN983B and dec2114x compatible  Fast Ethernet MAC driver
E 2
I 2
D 3
 *  tu: DIGITAL 2114x compatible Fast Ethernet MAC driver
E 3
I 3
D 11
 *  tu: digital 2114x compatible Fast Ethernet MAC driver
E 3
E 2
 *  %W% %E%
E 11
I 11
 * tu: digital 2114x compatible Fast Ethernet MAC driver
E 11
 *
D 3
 *  Copyright (C) 2002  Masayuki Murayama (KHF04453@nifty.ne.jp)
E 3
I 3
D 11
 *  Copyright (C) 2002-2003  Masayuki Murayama (KHF04453@nifty.ne.jp)
E 3
 *
 *  CAUTION: NO WARRANTY
 *  This software may be used and distributed according to the terms
 *  of the Lesser GNU Public License, incorporated herein by reference.
E 11
I 11
D 14
 * Copyright (c) 2002-2004 Masayuki Murayama.  All rights reserved.
E 14
I 14
D 17
 * Copyright (c) 2002-2005 Masayuki Murayama.  All rights reserved.
E 17
I 17
D 21
 * Copyright (c) 2002-2006 Masayuki Murayama.  All rights reserved.
E 21
I 21
D 28
 * Copyright (c) 2002-2007 Masayuki Murayama.  All rights reserved.
E 21
E 17
E 14
 * 
E 28
I 28
D 29
 * Copyright (c) 2002-2008 Masayuki Murayama.  All rights reserved.
E 29
I 29
 * Copyright (c) 2002-2011 Masayuki Murayama.  All rights reserved.
E 29
 *
E 28
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
D 28
 * 
E 28
I 28
 *
E 28
 * 1. Redistributions of source code must retain the above copyright notice,
D 28
 *    this list of conditions and the following disclaimer. 
 * 
E 28
I 28
 *    this list of conditions and the following disclaimer.
 *
E 28
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
D 28
 *    and/or other materials provided with the distribution. 
 * 
E 28
I 28
 *    and/or other materials provided with the distribution.
 *
E 28
 * 3. Neither the name of the author nor the names of its contributors may be
 *    used to endorse or promote products derived from this software without
D 28
 *    specific prior written permission. 
 * 
E 28
I 28
 *    specific prior written permission.
 *
E 28
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
E 11
 */

I 11
D 28
#pragma ident "%W% %E%"
E 28
I 28
#pragma ident "%Z%%M% %I%     %E%"
E 28

E 11
/*
D 29
 Change log
I 5
 02/11/2003 0.9.7 release
I 6
 03/13/2003 fixed for sparc
 04/06/2003 tudetach caused panic on sparc, fixed.
 04/06/2003 0.9.8 release
 04/09/2003 ddi_dma_sync added when accessing tx/rx descripters (for sparc)
 04/09/2003 0.9.9 release (worked with dc21140 under 64bit/32bit sparc)
 04/14/2003 tu_set_rx_filter fixed to use imperfect hash filtering.
 04/15/2003 0.9.10 release
I 7
 04/20/2003 work around for DM9102A_E3: don't touch chip after auto-nego kicked
 04/30/2003 tu_get_stats: bug fixed (LPC -> LPC_LPC)
	    tu_interrupt: calling tu_get_stats on SR_RDU to avoid missed
	    packet counter overflow.
 05/04/2003 NOINTR_WORKAROUND added (0.9.15)
 05/31/2003 burstsizes in ddi_dma_attr fixed for sparc
I 8
D 9
 07/06/2003 liteon LC82C168 100M half mode worked
E 9
I 9
 07/06/2003 lite-on LC82C168 100M half mode worked
 10/05/2003 lite-on LC82C168 autonegotiation worked
D 28
	    PCI bus access commnads was changed to use memory read multiple and 
E 28
I 28
	    PCI bus access commnads was changed to use memory read multiple and
E 28
	    memory read line command for all type of chips.
I 10
	    worked with 21143 + KENDIN PHY
 11/06/2003 tu-0.9.27 worked with 21140+NS83840 on sparc. (tested by Klaus)
 11/10/2003 tu-0.9.30 worked with LC82C169 with MII PHY. (tested by Klaus)
I 11
 12/29/2003 tu_mii_write_9102: work around for DM9102A_E3 fixed.
 01/17/2004 MX98713 tested but it hung while stress test.
 05/10/2004 0.9.34 reseased (MX98713, LC82C115 tested)
I 12
 06/06/2004 interrupts masked while tu_interrupt()
I 17
 04/22/2006 backport fixes and enhancements from tu-0.9.44
 05/28/2006 release 2.2.0
I 21
 01/04/2007 multicast hash size for LC82C115 fixed
 01/04/2007 release 2.4.0
I 22
 01/06/2007 set_rx_filter cleanup
I 26
 09/22/2007 release 2.6.0
E 29
I 29
 * Change log
 * 02/11/2003 0.9.7 release
 * 03/13/2003 fixed for sparc
 * 04/06/2003 tudetach caused panic on sparc, fixed.
 * 04/06/2003 0.9.8 release
 * 04/09/2003 ddi_dma_sync added when accessing tx/rx descripters (for sparc)
 * 04/09/2003 0.9.9 release (worked with dc21140 under 64bit/32bit sparc)
 * 04/14/2003 tu_set_rx_filter fixed to use imperfect hash filtering.
 * 04/15/2003 0.9.10 release
 * 04/20/2003 work around for DM9102A_E3: don't touch chip after auto-nego
 *		kicked
 * 04/30/2003 tu_get_stats: bug fixed (LPC -> LPC_LPC)
 *		tu_interrupt: calling tu_get_stats on SR_RDU to avoid missed
 *		packet counter overflow.
 * 05/04/2003 NOINTR_WORKAROUND added (0.9.15)
 * 05/31/2003 burstsizes in ddi_dma_attr fixed for sparc
 * 07/06/2003 lite-on LC82C168 100M half mode worked
 * 10/05/2003 lite-on LC82C168 autonegotiation worked
 *	    PCI bus access commnads was changed to use memory read multiple and
 *	    memory read line command for all type of chips.
 *	    worked with 21143 + KENDIN PHY
 * 11/06/2003 tu-0.9.27 worked with 21140+NS83840 on sparc. (tested by Klaus)
 * 11/10/2003 tu-0.9.30 worked with LC82C169 with MII PHY. (tested by Klaus)
 * 12/29/2003 tu_mii_write_9102: work around for DM9102A_E3 fixed.
 *  01/17/2004 MX98713 tested but it hung while stress test.
 * 05/10/2004 0.9.34 reseased (MX98713, LC82C115 tested)
 * 06/06/2004 interrupts masked while tu_interrupt()
 * 04/22/2006 backport fixes and enhancements from tu-0.9.44
 * 05/28/2006 release 2.2.0
 * 01/04/2007 multicast hash size for LC82C115 fixed
 * 01/04/2007 release 2.4.0
 * 01/06/2007 set_rx_filter cleanup
 * 09/22/2007 release 2.6.0
E 29
E 26
E 22
E 21
E 17
E 12
E 11
E 10
E 9
E 8
E 7
E 6
E 5
 */

/*
D 29
 TODO:
E 29
I 29
 * TODO:
E 29
D 17
	enable pause
	fix registers acording to media modes
	fix pci access register
I 3
	Conexant RS7112 support
		support 8address bit serial rom - done
		change offset to station address in serial rom - done
		skip HomePNA PHY at MII address 0  - done
I 6
D 11
	rx filter test for MX99715: done
E 11
I 11
	rx filter test for MX98715: done
E 11
	NWAY reset test for MX98715 : done
I 9
	consider PBL and CAL again
D 11
	it doesn't work with LC82C169
E 11
I 11
	it doesn't work with LC82C169 : done
E 11
	dm9102 flowcontrol
	enable AN done interrupt on PNIC
E 17
I 17
D 22
	adding COMET
	adding ULI
E 22
I 22
D 26
	testing ULI
E 26
E 22
E 17
E 9
E 6
E 3
 */

/*
 * System Header files.
 */
#include <sys/types.h>
#include <sys/conf.h>
#include <sys/debug.h>
D 28
#include <sys/stropts.h>
#include <sys/stream.h>
#include <sys/strlog.h>
E 28
#include <sys/kmem.h>
D 28
#include <sys/stat.h>
#include <sys/kstat.h>
#include <sys/vtrace.h>
#include <sys/dlpi.h>
#include <sys/strsun.h>
#include <sys/ethernet.h>
E 28
#include <sys/modctl.h>
#include <sys/errno.h>
I 17
D 28
#include <sys/dditypes.h>
E 28
E 17
#include <sys/ddi.h>
#include <sys/sunddi.h>
I 26
#include <sys/byteorder.h>
E 26
D 9
#include <sys/gld.h>
E 9
D 17
#include <sys/ddi_impldefs.h>
E 17
D 28

E 28
I 28
#include <sys/ethernet.h>
E 28
#include <sys/pci.h>
I 28

E 28
D 26
#include "mii.h"
E 26
I 26
#include "gem_mii.h"
E 26
#include "gem.h"
D 28

E 28
#include "dec2114x.h"

I 6
D 14
#ifdef sun4u
# define	IOCACHE
# define	IOMMU
#endif

E 14
E 6
D 7
char	ident[] = "2114x compat nic driver v" VERSION;
E 7
I 7
D 10
char	ident[] = "2114x-like nic driver " VERSION;
E 10
I 10
char	ident[] = "2114x nic driver " VERSION;
E 10
E 7
D 17
char	_depends_on[] = {"misc/gld"};
E 17

/* Debugging support */
#ifdef DEBUG_LEVEL
static int tu_debug = DEBUG_LEVEL;
D 28
#define	DPRINTF(n, args)	if (tu_debug>(n)) cmn_err args
E 28
I 28
#define	DPRINTF(n, args)	if (tu_debug > (n)) cmn_err args
E 28
#else
#define	DPRINTF(n, args)
#endif

/*
 * Useful macros and typedefs
 */
I 29
#define	BOOLEAN(x)	((x) != 0)
E 29
D 17
#define	FALSE	(0)
#define	TRUE	(!FALSE)
E 17
I 17
D 26
#define	FALSE	B_FALSE
E 26
D 28
#define	TRUE	B_TRUE
E 28
E 17
I 7
D 9
#define	ONESEC	(drv_usectohz(1*1000000))
E 9
I 9
#define	ONESEC	(drv_usectohz(1000*1000))
E 9
E 7

I 14
#define	ROUNDUP2(x, y)	(((x)+(y)-1) & ~((y)-1))
D 22
#define	STRUCT_COPY(a, b)	bcopy(&(b), &(a), sizeof(a))
E 22

I 17
D 26
#if defined(sun4u)
# define LE16(x)	ddi_swap16(x)
# define LE32(x)	ddi_swap32(x)
# define LE64(x)	ddi_swap64(x)
#else
# define LE16(x)	(x)
# define LE32(x)	(x)
# define LE64(x)	(x)
#endif

E 26
E 17
E 14
I 9
#define	REPLACE_BIT(dest, dest_bit, src, src_bit)	\
D 28
	if (((src) & (src_bit)) != 0) {	\
E 28
I 28
	if ((src) & (src_bit)) {	\
E 28
		(dest) |= (dest_bit);	\
	} else {	\
		(dest) &= ~(dest_bit);	\
	}

I 16
#define	LEWORD(c)	(((uint8_t *)(c))[0] | (((uint8_t *)(c))[1] << 8))
D 17
#define	ZEROS6	"\0\0\0\0\0\0"
#define	ONES6	"\377\377\377\377\377\377"
E 17

D 28
#define	MX98713(lp)	((lp)->hw_info->chip_type == CHIP_MX987XX && \
			 ((lp)->pci_revid & 0xf0) == 0x00)
E 28
I 28
D 29
#define	MX98713(lp)	\
	((lp)->hw_info->chip_type == CHIP_MX987XX && \
	((lp)->pci_revid & 0xf0) == 0x00)
E 28

E 29
I 28
#ifdef MAP_MEM
#define	FLSHB(dp, reg)	(void) INB(dp, reg)
#define	FLSHW(dp, reg)	(void) INW(dp, reg)
#define	FLSHL(dp, reg)	(void) INL(dp, reg)
#else
#define	FLSHB(dp, reg)
#define	FLSHW(dp, reg)
#define	FLSHL(dp, reg)
#endif

#define	TXDESC(p)	((struct tx_desc *)(void *)(p))
#define	RXDESC(p)	((struct rx_desc *)(void *)(p))

E 28
E 16
/* port selection index */
#define	PORT_10_HD	0
#define	PORT_10_FD	1
#define	PORT_100_HD	2
#define	PORT_100_FD	3
#define	NUM_PORT_SELECTION	4
#define	PORT_IX(s, d)	(((s) ? 2 : 0) + ((d) ? 1 : 0))
I 16
D 29
#define	PORT_IS_FDX(port)	(((port) & 1) != 0)
E 29
I 29
#define	PORT_IS_FDX(port)	BOOLEAN((port) & 1)
E 29
E 16
#define	CSR6_PORT_BITS	\
D 28
		(NAR_PS | NAR_TTM | NAR_PCS | NAR_SCR | NAR_SQE | NAR_FD)
E 28
I 28
	(NAR_PS | NAR_TTM | NAR_PCS | NAR_SCR | NAR_SQE | NAR_FD)
E 28

I 16
#define	VID_COGENT	0x1109

I 29
#ifndef VTAG_SIZE
#define	VTAG_SIZE	4
#endif

E 29
E 16
E 9
/*
 * Setup frame type
 */
#define	SETUP_PERFECT	1
#define	SETUP_HASH	2
#define	SETUP_INVERSE	3
#define	SETUP_HASHONLY	4

/*
 * Our configuration
 */
#define	OUR_INTR_BITS	\
D 7
	(SR_NISS | SR_AISS | SR_FBE | SR_RCI | SR_TUF | SR_TJT | SR_TCI)
E 7
I 7
D 9
    (SR_NISS | SR_AISS | SR_FBE | SR_RDU | SR_RCI | SR_TUF | SR_TJT | SR_TCI)
E 9
I 9
D 16
    (SR_NISS | SR_AISS | SR_FBE | SR_RWT | SR_RDU | SR_RCI | SR_TUF | SR_TJT | SR_TCI)
E 16
I 16
	(SR_NISS | SR_AISS | SR_FBE | SR_RWT | SR_RDU | SR_RCI | \
D 28
	 SR_TUF | SR_TJT | SR_TCI)
E 28
I 28
	SR_TUF | SR_TJT | SR_TCI)
E 28
E 16

I 16
#ifdef TEST_RX_EMPTY
D 28
# define RX_BUF_SIZE	1
E 28
I 28
#define	RX_BUF_SIZE	1
E 28
#endif

I 28
#ifndef GEM_CONFIG_TX_DIRECT
#error GEM_CONFIG_TX_DIRECT is required
#endif
D 29

#define	MAXTXFRAGS	GEM_MAXTXFRAGS

E 29
I 29
#ifndef DEBUG_TX_WAKEUP
#define	MAXTXFRAGS	min(GEM_MAXTXFRAGS, 8)
#else
#define	MAXTXFRAGS	1
#define	TX_BUF_SIZE	256
#define	TX_RING_SIZE	TX_BUF_SIZE
#endif
E 29
E 28
E 16
I 14
#ifndef TX_BUF_SIZE
E 14
E 9
E 7
D 3

E 3
D 11
#define TX_RING_SIZE	128
#define TX_BUF_SIZE	(TX_RING_SIZE/4)
#define RX_RING_SIZE	64
E 11
I 11
D 28
#define TX_BUF_SIZE	64
E 28
I 28
#define	TX_BUF_SIZE	64
E 28
I 14
#endif
E 14
D 28
#define TX_RING_SIZE	(TX_BUF_SIZE*4)
E 28
I 28
#ifndef TX_RING_SIZE
#define	TX_RING_SIZE	(TX_BUF_SIZE*4)
#endif
E 28
I 14

#ifndef RX_BUF_SIZE
E 14
D 26
#define RX_BUF_SIZE	64
E 26
I 26
D 28
#define RX_BUF_SIZE	256
E 28
I 28
#define	RX_BUF_SIZE	256
E 28
E 26
D 14
#define RX_RING_SIZE	(RX_BUF_SIZE*2)
E 14
I 14
#endif
D 28
#define RX_RING_SIZE	RX_BUF_SIZE
E 28
I 28
#define	RX_RING_SIZE	RX_BUF_SIZE
E 28
E 14
E 11

static int	tu_tx_copy_thresh = 256;
static int	tu_rx_copy_thresh = 256;

I 9
D 16
#define	PBL_DEFAULT	32	/* for both of i386 and sparc */
D 14
static tu_cache_linesz_default = 8;
E 14
I 14
static int tu_cache_linesz_default = 8;
E 16
I 16
D 17
#define	PBL_DEFAULT	64	/* for both of i386 and sparc */
E 17
I 17
#define	PBL_DEFAULT	(32*4)	/* for both of i386 and sparc */
E 17
static int tu_cache_linesz_default = PBL_DEFAULT/4;
E 16
E 14

E 9
/*
 * tu local chip state
 */
D 7
struct tu_chip_state {
E 7
I 7
struct tu_dev {
I 10
	/* chip infomation */
E 10
E 7
I 2
	struct chip_info	*hw_info;

E 2
D 7
	uint16_t		pci_comm;
	uint8_t			pci_cache_linesz;
I 2
	uint8_t			pci_revid;
E 7
I 7
	uint32_t		pci_comm;
	uint32_t		pci_cache_linesz;
	uint32_t		pci_revid;
I 10
	int			ee_abits;	/* eeprom size */

	/* shadow registers */
E 10
E 7
E 2
	uint32_t		nar;
I 10
	uint32_t		ier;
D 11
#ifdef notdef
	uint32_t		pnic_nway;
#endif
E 11
E 10
D 2
	struct chip_info	*hw_info;
E 2
I 2

I 17
	/* error checking */
	uint32_t		tx_errbits;

E 17
D 10
	/* for MII emulation using Nway */
E 10
I 10
	/* MII emulation using Nway */
E 10
	clock_t			reset_expire;
	uint16_t		bmcr;	/* MII basic mode control reg */
I 9
	uint16_t		bmsr;	/* MII basic mode status reg */
E 9
	uint16_t		adv;	/* MII advertisement reg */
	uint16_t		lpar;
I 20
	uint16_t		exp;	/* expanstion reg */
E 20
D 11
	int			port;
E 11
I 11
	int			port;	/* selected port */
E 11
#define	PORT_MII	0
#define	PORT_SYM	1
I 20
	clock_t			an_start_time;
E 20
I 3

D 10
	/* eeprom size */
	int			ee_abits;
I 9

	/* interrupt control */
E 9
I 7
	uint32_t		ier;
I 9

E 10
	/* error recovering */
	boolean_t		need_to_reset;
I 28

	/* setupframe */
	boolean_t		first_setupframe;

E 28
D 10
	uint32_t		pnic_nway;
E 10
D 16

E 16
I 16
D 17
#ifdef CONFIG_POLLING
E 17
I 17
D 29
#ifdef GEM_CONFIG_POLLING
E 29
I 29
#ifdef CONFIG_POLLING
E 29
E 17
E 16
	/* receive delay control */
D 16
	uint32_t		rx_delay_pkts;
	uint32_t		rx_delay;

E 16
I 16
D 29
	int			timer_resolution;	/* uS */
I 28
	uint32_t		timer_mask;
E 29
E 28
	int			last_poll_interval;
#endif
#ifdef CONFIG_MULTIPORT
	uint8_t			dev_num;
	uint8_t			dev_index;
	dev_info_t		*dip0;		/* ptr to first port */
#endif
E 16
D 10
	/* control bits */
E 10
I 10
	/* srom information */
	boolean_t	have_srom;
E 10
	uint16_t	gp_ctrl[NUM_PORT_SELECTION];
	uint16_t	gp_data[NUM_PORT_SELECTION];
D 10
	uint32_t	csr6[NUM_PORT_SELECTION];

	uint32_t	csr12[NUM_PORT_SELECTION];
	uint32_t	csr13[NUM_PORT_SELECTION];
	uint32_t	csr14[NUM_PORT_SELECTION];
	uint32_t	csr15[NUM_PORT_SELECTION];

E 10
I 10
	uint32_t	cfg_csr6[NUM_PORT_SELECTION];
	uint32_t	cfg_csr12[NUM_PORT_SELECTION];
	uint32_t	cfg_csr13[NUM_PORT_SELECTION];
	uint32_t	cfg_csr14[NUM_PORT_SELECTION];
	uint32_t	cfg_csr15[NUM_PORT_SELECTION];
E 10
	int		gp_seq_len;
	uint8_t		*gp_seq;
I 16
	int		gp_seq_unit;
E 16
	int		reset_seq_len;
	uint8_t		*reset_seq;
I 16
	int		reset_seq_unit;
I 26

	uint8_t		mac_addr[ETHERADDRL];
	int		last_mc_count;

E 26
E 16
D 17

D 10
	/* srom */
	boolean_t	have_srom;
	uint8_t		srom_data[256];
E 10
I 10
D 16
	uint8_t		srom_data[256];		/* raw data */
E 16
I 16
	uint8_t		srom_data[(1<<8) * sizeof(short)];
#define	SROM_ABITS	6			/* for 2114x */
#define	SROM_SIZE	(2 << SROM_ABITS)	/* in byte for 2114x */
E 17
I 17
D 28
#define	MAX_SROM_ABITS	8					/* for 2114x */
#define	MAX_SROM_SIZE	(sizeof(uint16_t) << MAX_SROM_ABITS)	/* in byte for 2114x */
E 28
I 28
#define	MAX_SROM_ABITS	8				/* for 2114x */
#define	MAX_SROM_SIZE	(sizeof (uint16_t) << MAX_SROM_ABITS)
							/* in byte for 2114x */
E 28
	uint8_t		srom_data[MAX_SROM_SIZE];
E 17
E 16
E 10
E 9
E 7
E 3
E 2
};

/*
 * Supported chips
 */
struct chip_info {
I 2
	char		*name;
E 2
	uint16_t	venid;
	uint16_t	devid;
I 29
	uint8_t		minrev;
E 29
I 10
	uint8_t		maxrev;
E 10
	int		chip_type;
D 2
	uint8_t		tx_align;
	uint8_t		capability;
E 2
I 2
	int		tx_align;
D 29
	int		capability;
E 2
#define	CHIP_CAP_RING	0x01
#define	CHIP_CAP_MII	0x02
D 2
	char		*name;
E 2
I 2
D 11
#define	CHIP_CAP_SYM	0x04
I 10
#define	CHIP_CAP_NWAY	0x08
E 11
I 11
#define	CHIP_CAP_SYM	0x04	/* SYM port, aka non MII port */
E 29
I 29
	uint32_t	capability;
#define	CHIP_CAP_RING	0x0001
#define	CHIP_CAP_MII	0x0002
#define	CHIP_CAP_SYM	0x0004	/* SYM port, aka non MII port */
#define	CHIP_WA_TXINTR	0x0008	/* workaround for lack of tx interrupt */
#define	CHIP_CAP_PBL_UNLMT	0x0010
#define	CHIP_WA_NO_PAD_TXDESC	0x0020
	int		hash_bits;
	uint32_t	spr_mbo;
	int		timer_resolution;
	uint32_t	timer_mask;
E 29
E 11
E 10
E 2
};

D 2
#define	CHIP_AN983	0
#define	CHIP_DM9102	1
#define	CHIP_MX98715	2
E 2
I 2
D 9
#define	CHIP_COMET	0	/* not tested yet */
#define	CHIP_CENTAUR	1	/* tested */
#define	CHIP_DM9102	2	/* tested */
#define	CHIP_MX98713	3	/* not tested yet */
#define	CHIP_MX98715	4	/* tested */
#define	CHIP_LC82C115	5	/* not supported yet */
D 6
#define	CHIP_21140	6	/* not tested yet */
E 6
I 6
#define	CHIP_21140	6	/* tested on sparc */
E 6
D 7
#define	CHIP_21142	7	/* not tested yet */
E 7
I 7
#define	CHIP_21142	7	/* tested on sparc */
E 7
I 3
#define	CHIP_CONEXANT	8	/* tested by Antonio */
I 8
#define	CHIP_LC82C168	9	/* under developping */
E 9
I 9
D 10
#define	CHIP_CENTAUR	0	/* tested */
E 10
I 10
D 11
#define	CHIP_CENTAUR	0	/* COMET/CENTAUR tested */
E 11
I 11
D 17
#define	CHIP_CENTAUR	0	/* COMET not tested, CENTAUR tested */
E 17
I 17
#define	CHIP_CENTAUR	0	/* COMET tested, CENTAUR tested */
E 17
E 11
E 10
D 29
#define	CHIP_DM9102	1	/* tested */
D 11
#define	CHIP_MX98713	2	/* not tested yet */
#define	CHIP_MX98715	3	/* tested */
#define	CHIP_LC82C115	4	/* not supported yet */
D 10
#define	CHIP_21140	5	/* tested on sparc */
#define	CHIP_21142	6	/* tested on sparc */
E 10
I 10
#define	CHIP_21140	5	/* 21140/21140A  tested */
#define	CHIP_21142	6	/* 21142/21143 tested */
E 10
#define	CHIP_CONEXANT	7	/* tested by Antonio */
D 10
#define	CHIP_LC82C168	8	/* under developping */
E 10
I 10
#define	CHIP_LC82C168	8	/* 82168/82169, under developping */
E 11
I 11
#define	CHIP_MX987XX	2	/* 98713, 98715, 98725 tested */
#define	CHIP_LC82C115	3	/* tested */
#define	CHIP_21140	4	/* 21140/21140A  tested */
#define	CHIP_21142	5	/* 21142/21143 tested */
#define	CHIP_CONEXANT	6	/* tested by Antonio */
#define	CHIP_LC82C168	7	/* LC82C168/82C169 tested */
I 17
#define	CHIP_XIRCOM	8	/* tested */
D 26
#define	CHIP_ULI526X	9	/* not tested */
E 26
I 26
#define	CHIP_ULI526X	9	/* tested */
E 29
I 29
#define	CHIP_DM9102	1	/* not tested */
#define	CHIP_DM9102A	2	/* tested */
#define	CHIP_MX98713	3	/* 98713, 98715, 98725 tested */
#define	CHIP_MX98713A	4	/* 98713, 98715, 98725 tested */
#define	CHIP_MX98715	5	/* 98713, 98715, 98725 tested */
#define	CHIP_MX98725	6	/* 98713, 98715, 98725 tested */
#define	CHIP_LC82C115	7	/* tested */
#define	CHIP_21140	8	/* 21140/21140A  tested */
#define	CHIP_21142	9	/* 21142/21143 tested */
#define	CHIP_CONEXANT	10	/* tested by Antonio */
#define	CHIP_LC82C168	11	/* LC82C168/82C169 tested */
#define	CHIP_XIRCOM	12	/* tested */
#define	CHIP_ULI526X	13	/* tested */
E 29
E 26
E 17
E 11
E 10
E 9
E 8
E 3
E 2

I 7
D 29
#define	DM9102A_E3	((PCI_PMCAP_VER_1_0 << 16) | 0x31)
E 29
I 29
#define	DM9102A_E3	(PCI_PMCAP_VER_1_0 << 16 | 0x31)
E 29
D 9

E 9
I 9
#define	DEVID_COMET	0x981
I 10
#define	IS_21140(lp)	((lp->pci_revid & 0xf0) == 0x10)
E 10
E 9
E 7
static struct chip_info tu_chiptbl[] = {
I 10
/* 21140 and its valiants */
E 10
D 2
	{0x1317, 0x0985, CHIP_AN983,   1, CHIP_CAP_RING|CHIP_CAP_MII,
		"ADMtek AN983B"},
	{0x1259, 0xa120, CHIP_AN983,   1, CHIP_CAP_RING|CHIP_CAP_MII,
		"ADMtek AN983B (Corega EtherPCI-TM)"},
	{0x1282, 0x9102, CHIP_DM9102,  4, CHIP_CAP_MII,
		"DAVICOM DM9102/DM9102A"},
	{0x10d9, 0x0531, CHIP_MX98715, 1, 0,
		"Macronix MX98715"},
E 2
I 2
D 28
 {
I 10
	/* 
E 28
I 28
{
	/*
E 28
D 17
	 * 21140(A) does't have an internal endec and CSR13-14.
E 17
I 17
	 * 21140(A) doesn't have an internal endec and CSR13-14.
E 17
	 * It supports 100M SYM interface but doesn't have NWAY capability.
	 * Usage on TTM bit in 21140 is a little different from other 2114x
	 * chips.
	 */
	"digital 21140(A)",
D 29
	0x1011, 0x0009, 0xff,	CHIP_21140,	1,
E 29
I 29
	0x1011, 0x0009, 0, 0xff,	CHIP_21140,	1,
E 29
	CHIP_CAP_RING | CHIP_CAP_MII | CHIP_CAP_SYM,
I 29
	512,	0,	82*1000, 0,
E 29
D 28
 },
 {
E 28
I 28
},
{
E 28
	/*
D 11
	 * LITE-ON PNIC
	 * LC82C168 seems a 21140 valiant with integrated NWAY.
	 * LC82C168 supports only SYM interface.
E 11
I 11
	 * LITE-ON PNIC (LC82C168)
	 * It seems a 21140 valiant with integrated NWAY.
E 11
D 14
	 * LC82C169 has MII and SYM interface.
E 14
I 14
	 * LC82C168 has SYM interface.
E 14
	 */
D 11
	"LITE-ON LC82C169/169",
E 11
I 11
	"LITE-ON LC82C168",
D 29
	0x11ad, 0x0002, 0x1f,	CHIP_LC82C168,	1,
	CHIP_CAP_SYM,	/* RING not work */
E 29
I 29
	0x11ad, 0x0002, 0, 0x1f,	CHIP_LC82C168,	1,
	CHIP_CAP_SYM | CHIP_CAP_PBL_UNLMT,	/* RING not work */
	512,	0,	0, 0,
E 29
D 28
 },
 {
E 28
I 28
},
{
E 28
	/*
	 * LITE-ON PNIC (LC82C169)
	 * It seems a 21140 valiant with integrated NWAY.
	 * LC82C169 has MII and SYM interface.
	 */
	"LITE-ON LC82C169",
E 11
D 29
	0x11ad, 0x0002, 0xff,	CHIP_LC82C168,	1,
D 11
	CHIP_CAP_MII | CHIP_CAP_SYM | CHIP_CAP_NWAY,		/* CHIP_CAP_RING not work */
E 11
I 11
	CHIP_CAP_MII | CHIP_CAP_SYM,	/* RING not work */
E 29
I 29
	0x11ad, 0x0002, 0x20, 0xff,	CHIP_LC82C168,	1,
	CHIP_CAP_MII | CHIP_CAP_SYM | CHIP_CAP_PBL_UNLMT,
	512,	0,	0, 0,
E 29
E 11
D 28
 },
I 11
 {
E 28
I 28
},
{
E 28
	/*
	 * MX98713 seems a 21140 valiant with integrated NWAY.
	 * Its MII interface is a little different from DEC way.
	 */
	"Macronix MX98713",
D 29
	0x10d9,	0x0512,	0x0f,	CHIP_MX987XX,	1,
E 29
I 29
	0x10d9,	0x0512,	0, 0x0f,	CHIP_MX98713,	1,
E 29
	CHIP_CAP_MII | CHIP_CAP_SYM,	/* RING does not work */
I 29
	512,	SPR_SWC,	82*1000, 3,
E 29
D 28
 },
E 28
I 28
},
E 28
E 11
/* 21142 */
D 28
 {
	/* 
E 28
I 28
{
	/*
E 28
	 * 21142 has an internal ENDEC and CSR13-14.
	 * But it doesn't support 100M SYM interface.
	 */
	"digital 21142",
D 29
	0x1011,	0x0019,	0x2f,	CHIP_21142,	1,
E 29
I 29
	0x1011,	0x0019,	0, 0x2f,	CHIP_21142,	1,
E 29
	CHIP_CAP_RING | CHIP_CAP_MII,
I 29
	512,	0,	82*1000, 0,
E 29
D 28
 },
E 28
I 28
},
E 28

/* 21142 clones with integrated MII PHY */
D 28
 {
E 28
I 28
{
E 28
E 10
D 9
	"ADMtek AL981",				/* Comet */
	0x1317,	0x0981,	CHIP_COMET,	1,
E 9
I 9
D 17
	"ADMtek AL981",				/* Comet: not tested */
E 17
I 17
	"ADMtek AL981",				/* Comet: tested */
E 17
D 10
	0x1317,	DEVID_COMET,	CHIP_CENTAUR,	1,
E 10
I 10
D 29
	0x1317,	DEVID_COMET,	0xff,	CHIP_CENTAUR,	1,
E 10
E 9
D 16
	CHIP_CAP_RING | CHIP_CAP_MII
E 16
I 16
	CHIP_CAP_RING | CHIP_CAP_MII,
E 29
I 29
	0x1317,	DEVID_COMET, 0, 0xff,	CHIP_CENTAUR,	1,
	CHIP_CAP_RING | CHIP_CAP_MII | CHIP_CAP_PBL_UNLMT,
	64,	0,	205*1000, 0,
E 29
E 16
D 28
 },
 {
E 28
I 28
},
{
E 28
	"ADMtek ADM9511",			/* Centaur II w/ modem */
D 10
	0x1317,	0x9511,	CHIP_CENTAUR,	1,
E 10
I 10
D 29
	0x1317,	0x9511,	0xff,	CHIP_CENTAUR,	1,
E 10
	CHIP_CAP_RING | CHIP_CAP_MII,
E 29
I 29
	0x1317,	0x9511,	0, 0xff,	CHIP_CENTAUR,	1,
	CHIP_CAP_RING | CHIP_CAP_MII | CHIP_CAP_PBL_UNLMT,
	64,	0,	205*1000, 0,
E 29
D 28
 },
 {
E 28
I 28
},
{
E 28
	"ADMtek ADM9513",			/* Centaur II w/ modem */
D 10
	0x1317,	0x9513,	CHIP_CENTAUR,	1,
E 10
I 10
D 29
	0x1317,	0x9513,	0xff,	CHIP_CENTAUR,	1,
E 10
	CHIP_CAP_RING | CHIP_CAP_MII,
E 29
I 29
	0x1317,	0x9513,	0, 0xff,	CHIP_CENTAUR,	1,
	CHIP_CAP_RING | CHIP_CAP_MII | CHIP_CAP_PBL_UNLMT,
	64,	0,	205*1000, 0,
E 29
D 28
 },
 {
E 28
I 28
},
{
E 28
D 7
	"ADMtek AN983/983B",			/* Centaur P */
E 7
I 7
	"ADMtek AN983(B)",			/* Centaur P */
E 7
D 10
	0x1317,	0x0985,	CHIP_CENTAUR,	1,
E 10
I 10
D 29
	0x1317,	0x0985,	0xff,	CHIP_CENTAUR,	1,
E 10
	CHIP_CAP_RING | CHIP_CAP_MII,
E 29
I 29
	0x1317,	0x0985,	0, 0xff,	CHIP_CENTAUR,	1,
	CHIP_CAP_RING | CHIP_CAP_MII | CHIP_CAP_PBL_UNLMT,
	64,	0,	205*1000, 0,
E 29
D 28
 },
 {
E 28
I 28
},
{
E 28
	"ADMtek AN983B (Corega EtherPCI-TM)",	/* Centaur P */
D 10
	0x1259,	0xa120,	CHIP_CENTAUR,	1,
D 9
	CHIP_CAP_RING | CHIP_CAP_MII,
E 9
I 9
	/*CHIP_CAP_RING |*/CHIP_CAP_MII,	/* XXX */
E 10
I 10
D 29
	0x1259,	0xa120,	0xff,	CHIP_CENTAUR,	1,
D 11
	CHIP_CAP_RING | CHIP_CAP_MII,	/* XXX */
E 11
I 11
	CHIP_CAP_RING | CHIP_CAP_MII,
E 29
I 29
	0x1259,	0xa120,	0, 0xff,	CHIP_CENTAUR,	1,
	CHIP_CAP_RING | CHIP_CAP_MII | CHIP_CAP_PBL_UNLMT,
	64,	0,	205*1000, 0,
E 29
E 11
E 10
E 9
D 28
 },
 {
E 28
I 28
},
{
E 28
I 17
	"ADMtek AN985",				/* Centaur C */
D 29
	0x1317,	0x1985,	0xff,	CHIP_CENTAUR,	1,
	CHIP_CAP_RING | CHIP_CAP_MII,
E 29
I 29
	0x1317,	0x1985,	0, 0xff,	CHIP_CENTAUR,	1,
D 30
	CHIP_CAP_RING | CHIP_CAP_MII | CHIP_WA_TXINTR | CHIP_CAP_PBL_UNLMT,
E 30
I 30
	CHIP_CAP_RING | CHIP_CAP_MII | CHIP_CAP_PBL_UNLMT,
E 30
	64,	0,	205*1000, 0,
E 29
D 28
 },
 {
E 28
I 28
},
{
E 28
I 19
	/* for Planex and IO DATA cardbus products */
	"ADMtek AN985 (AboCom)",		/* Centaur C */
D 29
	0x13d1, 0xab02,	0xff,	CHIP_CENTAUR,	1,
	CHIP_CAP_RING | CHIP_CAP_MII,
E 29
I 29
	0x13d1, 0xab02,	0, 0xff,	CHIP_CENTAUR,	1,
	CHIP_CAP_RING | CHIP_CAP_MII | CHIP_CAP_PBL_UNLMT,
	64,	0,	205*1000, 0,
E 29
D 28
 },
 {
E 28
I 28
},
{
E 28
E 19
E 17
D 7
	"DAVICOM DM9102",
E 7
I 7
D 29
	"DAVICOM DM9102(A)",
E 7
D 9
	0x1282,	0x9102,	CHIP_DM9102,	4,
E 9
I 9
D 10
	0x1282,	0x9102,	CHIP_DM9102,	4,	/* buffer alignment must be 4 */
E 10
I 10
	0x1282,	0x9102,	0xff,	CHIP_DM9102,	4, /* alignment must be 4 */
E 10
E 9
	CHIP_CAP_MII,
E 29
I 29
	"DAVICOM DM9102",
	0x1282,	0x9102,	0, 0x2f,	CHIP_DM9102,	4,
	CHIP_CAP_MII | CHIP_WA_NO_PAD_TXDESC,
	512,	0,	0, 0,
E 29
D 28
 },
I 17
 {
E 28
I 28
},
{
I 29
	"DAVICOM DM9102A",
	0x1282,	0x9102,	0x30, 0xff,	CHIP_DM9102A,	4,
	CHIP_CAP_MII | CHIP_WA_NO_PAD_TXDESC,
	512,	0,	0, 0,
},
{
E 29
E 28
	"Xircom CB-100",
D 29
	0x115d,	0x0003,	0xff,	CHIP_XIRCOM,	4, /* alignment must be 4 */
	CHIP_CAP_MII,
E 29
I 29
	0x115d,	0x0003,	0, 0xff,	CHIP_XIRCOM,	4,
	CHIP_CAP_MII | CHIP_WA_TXINTR,
	512,	0,	0, 0,
E 29
D 28
 },
E 28
I 28
},
E 28
E 17
I 7
#ifdef CONFIG_DM9100
E 7
D 28
 {
E 28
I 28
{
E 28
I 7
	/*
D 10
	 * DM 9100 should not be supported as rx crc doesn't work correctly.
E 10
I 10
	 * DM 9100 isn't supported as rx crc doesn't work correctly.
E 10
	 */
E 7
I 3
	"DAVICOM DM9100",
D 7
	0x1282,	0x9100,	CHIP_DM9102,	4,
E 7
I 7
D 10
	0x1282,	0x9100,	CHIP_DM9100,	4,
E 10
I 10
D 29
	0x1282,	0x9100,	0xff,	CHIP_DM9100,	4,
E 29
I 29
	0x1282,	0x9100,	0, 0xff,	CHIP_DM9100,	4,
E 29
E 10
E 7
	CHIP_CAP_MII,
I 29
	512,	0,	0, 0,
E 29
D 28
 },
E 28
I 28
},
E 28
I 7
#endif
E 7
D 28
 {
E 28
I 28
{
E 28
I 10
	"Conexant LANfinity RS7112",	/* Tx-align may 1; not tested */
D 29
	0x14f1,	0x1803,	0xff,	CHIP_CONEXANT,	4,
E 29
I 29
	0x14f1,	0x1803,	0, 0xff,	CHIP_CONEXANT,	4,
E 29
	CHIP_CAP_MII,
I 29
	512,	0,	0, 0,
E 29
D 28
 },
I 17
 {
E 28
I 28
},
{
E 28
	"ULI 5261",
D 29
	0x10b9,	0x5261,	0xff,	CHIP_ULI526X,	4,
	CHIP_CAP_MII,
E 29
I 29
	0x10b9,	0x5261,	0, 0xff,	CHIP_ULI526X,	4,
	CHIP_CAP_MII | CHIP_WA_NO_PAD_TXDESC,
	512,	0,	82*1000, 0,
E 29
D 28
 },
 {
E 28
I 28
},
{
E 28
	"ULI 5263",
D 29
	0x10b9,	0x5263,	0xff,	CHIP_ULI526X,	4,
	CHIP_CAP_MII,
E 29
I 29
	0x10b9,	0x5263,	0, 0xff,	CHIP_ULI526X,	4,
	CHIP_CAP_MII | CHIP_WA_NO_PAD_TXDESC,
	512,	0,	82*1000, 0,
E 29
D 28
 },
E 28
I 28
},
E 28
E 17
D 11

/* 21143 and its valiants with integrated SYM PHY */
E 11
I 11
/* 21143 and its valiants with integrated PCS PHY */
E 11
D 28
 {
	/* 
E 28
I 28
{
	/*
E 28
	 * 21143 has an internal endec and CSR13-14.
	 * It has an internal PCS and an internal SCR unit.
	 * It also has nway capability.
	 */
	"digital 21143",
D 29
	0x1011,	0x0019,	0xff,	CHIP_21142,	1,
E 29
I 29
	0x1011,	0x0019,	0x30, 0xff,	CHIP_21142,	1,
E 29
D 11
	CHIP_CAP_RING | CHIP_CAP_MII | CHIP_CAP_SYM | CHIP_CAP_NWAY,
E 11
I 11
	CHIP_CAP_RING | CHIP_CAP_MII | CHIP_CAP_SYM,
I 29
	512,	0,	82*1000, 0,
E 29
E 11
D 28
 },
 {
E 28
I 28
},
{
E 28
	/*
D 11
	 * MX98713 is a clone of 21143, that doesn't have integrated PHY.
E 11
I 11
	 * MX98713A is a clone of 21143. It don't have MII interface.
	 * It is very similer to mx98715 rather than mx98713.
E 11
	 */
E 10
E 3
D 11
	"Macronix MX98713",
D 10
	0x10d9,	0x0512,	CHIP_MX98713,	1,
	CHIP_CAP_SYM | CHIP_CAP_MII,
E 10
I 10
	0x10d9,	0x0512,	0xff,	CHIP_MX98713,	4,
	CHIP_CAP_MII | CHIP_CAP_SYM | CHIP_CAP_NWAY,
E 11
I 11
	"Macronix MX98713A",
D 29
	0x10d9,	0x0512,	0x1f,	CHIP_MX987XX,	1,
E 29
I 29
	0x10d9,	0x0512,	0x10, 0x1f,	CHIP_MX98713A,	1,
E 29
	CHIP_CAP_SYM,	/* RING does not work */
I 29
	512,	SPR_SWC,	82*1000, 0,
E 29
E 11
E 10
D 28
 },
 {
E 28
I 28
},
{
E 28
	/*
D 3
	 * MX98715 is low cost version of MX98713. It does not support
E 3
I 3
D 6
	 * MX98715 seems low cost version of MX98713. It does not support
E 6
I 6
D 9
	 * MX98715 seems a low cost version of MX98713. It does not support
E 6
E 3
	 * external MII PHYs and have only 128bit-width hash table.
E 9
I 9
D 10
	 * MX98715 seems a low cost version of MX98713. It only supports
	 * an internal PCS PHY and have only 128bit-width hash table.
E 9
D 3
	 * MX98725 is APCI version of 98715. It expands hash size up to
E 3
I 3
D 6
	 * MX98725 seems APCI version of 98715. It expands hash size up to
E 6
I 6
	 * MX98725 seems ACPI version of 98715. It expands hash size up to
E 6
E 3
D 9
	 * 512bit-width, but does not support external MII PHYs.
E 9
I 9
	 * 512bit-width, but also supports only an internal PCS PHY.
E 10
I 10
D 11
	 * MX98715 is a clone of 21143 with integrated SYM PHY, so that
E 11
I 11
	 * MX98715 is a clone of 21143 with integrated PCS PHY, so that
E 11
	 * it doesn't support MII interface.
D 11
	 * It has only 128bit-width hash table.
E 11
I 11
	 * It has shortened 128bit-width hash table.
E 11
	 * MX98725 seems ACPI version of 98715. It expands hash size up
	 * to standard 512bit-width.
E 10
E 9
D 11
	 * MX98715 has rev-id 0x2X, MX98725 has rev-id 0x0X or 0x3X. 
I 9
	 * Rx align is 4, Ring descriptor is not supported.
E 11
I 11
D 28
	 * MX98715 has rev-id 0x2X, MX98725 has rev-id 0x3X. 
E 28
I 28
D 29
	 * MX98715 has rev-id 0x2X, MX98725 has rev-id 0x3X.
E 29
I 29
	 * MX98715 has rev-id 0x2X.
E 29
E 28
	 * Rx buffer alignment is 4, Ring descriptor is not supported.
E 11
E 9
	 */
D 10
	"Macronix MX98715/25",
	0x10d9, 0x0531, CHIP_MX98715,	1,
	CHIP_CAP_SYM,
E 10
I 10
D 29
	"Macronix MX98715/725",
D 11
	0x10d9, 0x0531,	0xff,	CHIP_MX98715,	1,
	CHIP_CAP_SYM | CHIP_CAP_NWAY,
E 11
I 11
	0x10d9, 0x0531,	0xff,	CHIP_MX987XX,	1,
E 29
I 29
	"Macronix MX98715",
	0x10d9, 0x0531,	0x20, 0x2f,	CHIP_MX98715,	1,
E 29
	CHIP_CAP_SYM,
I 29
	128,	SPR_SWC,	82*1000, 0,
E 29
E 11
E 10
D 28
 },
 {
E 28
I 28
},
{
E 28
I 3
D 10
	"Conexant LANfinity RS7112",
	0x14f1,	0x1803,	CHIP_CONEXANT,	4,	/* Tx-align may 1; not tested */
	CHIP_CAP_MII,
 },
 {
E 10
I 10
	/*
I 29
	 * MX98725 is a clone of 21143 with integrated PCS PHY, so that
	 * it doesn't support MII interface.
	 * MX98725 seems ACPI version of 98715. It expands hash size up
	 * to standard 512bit-width.
	 * MX98725 has rev-id 0x3X.
	 * Rx buffer alignment is 4, Ring descriptor is not supported.
	 */
	"Macronix MX98725",
	0x10d9, 0x0531,	0x30, 0x3f,	CHIP_MX98725,	1,
	CHIP_CAP_SYM,
	512,	SPR_SWC,	82*1000, 0,
},
{
	/*
E 29
D 11
	 * LC82C115 is a clone of 21143 with integrated SYM PHY, so that
E 11
I 11
	 * LC82C115 is a clone of 21143 with integrated PCS PHY, so that
E 11
	 * it doesn't support MII interface.
	 */
E 10
E 3
D 8
	"LITE-ON LC82C115",
E 8
I 8
D 9
	"LITEON LC82C115",
E 9
I 9
	"LITE-ON LC82C115",
E 9
E 8
D 10
	0x11ad, 0xc115, CHIP_LC82C115,	4,
D 9
	CHIP_CAP_SYM,
E 9
I 9
	CHIP_CAP_SYM,				/* PNIC II has NWAY only */
E 10
I 10
D 11
	0x11ad, 0xc115, 0xff,	CHIP_LC82C115,	4,
	CHIP_CAP_SYM | CHIP_CAP_NWAY,				/* PNIC II has NWAY only */
E 11
I 11
D 29
	0x11ad, 0xc115, 0xff,	CHIP_LC82C115,	1,
	CHIP_CAP_SYM,		/* ring doesn't work, PNIC II has NWAY only */
E 29
I 29
	0x11ad, 0xc115, 0, 0xff,	CHIP_LC82C115,	1,
	CHIP_CAP_SYM | CHIP_CAP_PBL_UNLMT,
	128,	0,	82*1000, 0,
E 29
E 11
E 10
E 9
D 28
 },
E 28
I 28
},
E 28
D 10
{
D 7
	"digital 21140/40A",
E 7
I 7
	"digital 21140(A)",
E 7
	0x1011, 0x0009, CHIP_21140,	1,
	CHIP_CAP_RING | CHIP_CAP_MII | CHIP_CAP_SYM,
 },
 {
	"digital 21142/43",
	0x1011,	0x0019,	CHIP_21142,	1,
	CHIP_CAP_RING | CHIP_CAP_MII | CHIP_CAP_SYM,
 },
I 8
 {
D 9
	"LITEON LC82C168/169",
E 9
I 9
	"LITE-ON LC82C168/169",
#define	PNIC_82C169_REV	0x20
E 9
	0x11ad, 0x0002, CHIP_LC82C168,	1,
	CHIP_CAP_MII | CHIP_CAP_SYM,	/* CHIP_CAP_RING not work */
 },
E 10
E 8
E 2
};
D 28
#define CHIPTABLESIZE   (sizeof(tu_chiptbl)/sizeof(struct chip_info))
E 28
I 28
#define	CHIPTABLESIZE   (sizeof (tu_chiptbl)/sizeof (struct chip_info))
E 28

/*
 * Macros to distinct chip generation.
 */

/* ======================================================== */
D 16
 
E 16
I 16
D 28
/* local function */ 
E 28
I 28
/* local function */
E 28
D 17
static void tu_reset_phy(struct gem_dev *dp);
E 17
I 17
static void tu_enable_phy(struct gem_dev *dp);
E 17

E 16
/* mii operations */
static void  tu_mii_sync(struct gem_dev *);
I 7
D 17
static void  tu_mii_sync_9102(struct gem_dev *);
E 17
I 17
static void  tu_mii_sync_null(struct gem_dev *);
E 17
E 7
D 16
static uint16_t  tu_mii_read(struct gem_dev *, int);
I 7
static uint16_t  tu_mii_read_9102(struct gem_dev *, int);
E 7
static void tu_mii_write(struct gem_dev *, int, uint16_t);
I 7
static void tu_mii_write_9102(struct gem_dev *, int, uint16_t);
E 16
I 16
static uint16_t  tu_mii_read(struct gem_dev *, uint_t);
D 17
static uint16_t  tu_mii_read_9102(struct gem_dev *, uint_t);
E 17
static void tu_mii_write(struct gem_dev *, uint_t, uint16_t);
static void tu_mii_write_9102(struct gem_dev *, uint_t, uint16_t);
E 16
E 7

/* nic operations */
I 16
static int tu_attach_chip(struct gem_dev *);
E 16
static int tu_reset_chip(struct gem_dev *);
D 20
static void tu_init_chip(struct gem_dev *);
static void tu_start_chip(struct gem_dev *);
E 20
I 20
static int tu_init_chip(struct gem_dev *);
static int tu_start_chip(struct gem_dev *);
E 20
D 17
static void tu_stop_chip(struct gem_dev *);
E 17
I 17
static int tu_stop_chip(struct gem_dev *);
E 17
D 20
static void tu_set_media(struct gem_dev *);
E 20
I 20
static int tu_set_media(struct gem_dev *);
E 20
static uint_t tu_multicast_hash(struct gem_dev *, uint8_t *);
D 20
static void tu_set_rx_filter(struct gem_dev *);
static void tu_get_stats(struct gem_dev *);
E 20
I 20
static int tu_set_rx_filter(struct gem_dev *);
static int tu_get_stats(struct gem_dev *);
I 28

E 28
E 20
D 16
static int tu_init_mac_addr(struct gem_dev *);
E 16
I 9
D 10
static void tu_write_siactrl(struct gem_dev *, uint32_t);
static void tu_select_port(struct gem_dev *, int, int);
E 9

E 10
/* descriptor operations */
D 17
static int tu_tx_desc_write1(struct gem_dev *dp, uint_t slot,
E 17
I 17
static int tu_tx_desc_write1(struct gem_dev *dp, int slot,
E 17
D 26
		    ddi_dma_cookie_t *dmacookie, int frags, uint32_t flag);
E 26
I 26
D 28
		    ddi_dma_cookie_t *dmacookie, int frags, uint64_t flag);
E 28
I 28
    ddi_dma_cookie_t *dmacookie, int frags, uint64_t flag);
E 28
E 26
D 10
static int tu_tx_desc_write2(struct gem_dev *dp, uint_t slot,
		    ddi_dma_cookie_t *dmacookie, int frags, uint32_t flag);
static int tu_rx_desc_write1(struct gem_dev *dp, uint_t slot,
		    ddi_dma_cookie_t *dmacookie, int frags);
E 10
D 17
static int tu_rx_desc_write2(struct gem_dev *dp, uint_t slot,
E 17
I 17
static void tu_tx_start(struct gem_dev *dp, int startslot, int nslot);
static void tu_rx_desc_write2(struct gem_dev *dp, int slot,
E 17
D 28
		    ddi_dma_cookie_t *dmacookie, int frags);
E 28
I 28
    ddi_dma_cookie_t *dmacookie, int frags);
E 28
static uint_t tu_tx_desc_stat(struct gem_dev *dp, int slot, int ndesc);
D 16
static uint_t tu_rx_desc_stat(struct gem_dev *dp, int slot, int ndesc);
E 16
I 16
static uint64_t tu_rx_desc_stat(struct gem_dev *dp, int slot, int ndesc);
E 16
D 28

E 28
static void tu_tx_desc_init1(struct gem_dev *dp, int slot);
D 10
static void tu_tx_desc_init2(struct gem_dev *dp, int slot);
E 10
static void tu_rx_desc_init1(struct gem_dev *dp, int slot);
static void tu_rx_desc_init2(struct gem_dev *dp, int slot);
I 28

E 28
D 10
static void tu_tx_desc_clean(struct gem_dev *dp, int slot);
static void tu_rx_desc_clean(struct gem_dev *dp, int slot);

E 10
/* interrupt handler */
D 28
static u_int tu_interrupt(struct gem_dev *dp);
E 28
I 28
static uint_t tu_interrupt(struct gem_dev *dp);
E 28

/* ======================================================== */

/* mapping attributes */
/* Data access requirements. */
D 6
static struct ddi_device_acc_attr gem_dev_attr = {
E 6
I 6
static struct ddi_device_acc_attr tu_dev_attr = {
E 6
	DDI_DEVICE_ATTR_V0,
	DDI_STRUCTURE_LE_ACC,
	DDI_STRICTORDER_ACC
};

/* On sparc, the buffers should be native endianness */
static struct ddi_device_acc_attr tu_buf_attr = {
	DDI_DEVICE_ATTR_V0,
	DDI_NEVERSWAP_ACC,	/* native endianness */
	DDI_STRICTORDER_ACC
};

static ddi_dma_attr_t tu_dma_attr_buf = {
	DMA_ATTR_V0,		/* dma_attr_version */
	0,			/* dma_attr_addr_lo */
	0xffffffffull,		/* dma_attr_addr_hi */
D 19
	0xffffffffull,		/* dma_attr_count_max */
	1,			/* dma_attr_align */
D 7
	0xffffffff,		/* dma_attr_burstsizes */
E 7
I 7
	0,			/* dma_attr_burstsizes */
E 19
I 19
D 27
	0x00000fffull,		/* dma_attr_count_max */
E 27
I 27
D 28
	0x0000ffffull,		/* dma_attr_count_max */
E 28
I 28
	0x000007ffull,		/* dma_attr_count_max */
E 28
E 27
	0, /* patched later */	/* dma_attr_align */
D 28
	0x00000fff,		/* dma_attr_burstsizes */
E 28
I 28
	0x000007ff,		/* dma_attr_burstsizes */
E 28
E 19
E 7
	1,			/* dma_attr_minxfer */
	0xffffffffull,		/* dma_attr_maxxfer */
	0xffffffffull,		/* dma_attr_seg */
D 19
	GEM_MAXTXFRAGS,		/* dma_attr_sgllen */
E 19
I 19
D 28
	0,/* patched later*/	/* dma_attr_sgllen */
E 28
I 28
	0, /* patched later */	/* dma_attr_sgllen */
E 28
E 19
	1,			/* dma_attr_granular */
	0			/* dma_attr_flags */
};

D 14
static ddi_dma_attr_t tu_dma_attr_nosc = {
E 14
I 14
static ddi_dma_attr_t tu_dma_attr_desc = {
E 14
	DMA_ATTR_V0,		/* dma_attr_version */
	0,			/* dma_attr_addr_lo */
	0xffffffffull,		/* dma_attr_addr_hi */
	0xffffffffull,		/* dma_attr_count_max */
	16,			/* dma_attr_align */
D 7
	0xffffffff,		/* dma_attr_burstsizes */
E 7
I 7
D 19
	0,			/* dma_attr_burstsizes */
E 19
I 19
	0x00000fff,		/* dma_attr_burstsizes */
E 19
E 7
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
I 9
#define	UPDATE_NAR(dp, val)	\
D 10
	{OUTL((dp), NAR, (val) & ~(NAR_ST | NAR_SR)); drv_usecwait(5);}
E 10
I 10
D 28
	{OUTL((dp), NAR, (val)); drv_usecwait(10);}
E 28
I 28
	{ OUTL((dp), NAR, (val)); drv_usecwait(10); }
E 28
E 10
E 9

I 9
D 28
static void
E 28
I 28
static uint32_t
E 28
D 10
tu_freeze_chip(struct gem_dev *dp)
E 10
I 10
tu_freeze_chip(struct gem_dev *dp, uint32_t which)
E 10
{
D 28
	struct tu_dev	*lp = (struct tu_dev *)dp->private;
E 28
I 28
	struct tu_dev	*lp = dp->private;
E 28
	int		i;
	uint32_t	sr;
I 28
	uint32_t	old;
E 28

	/* Temporary stop Tx and Rx */
D 10
	if ((lp->nar & (NAR_ST | NAR_SR)) != 0) {
E 10
I 10
	which &= NAR_ST | NAR_SR;
I 28
	old = lp->nar & (NAR_ST | NAR_SR);

	switch (lp->hw_info->chip_type) {
	case CHIP_CENTAUR:
D 29
#if 0
	case CHIP_DM9102:
#endif
E 29
	case CHIP_XIRCOM:
	case CHIP_LC82C115:
D 29
	case CHIP_MX987XX:	/* for both of MX98713 and MX98715 */
E 29
I 29
	case CHIP_MX98713:
	case CHIP_MX98713A:
	case CHIP_MX98715:
	case CHIP_MX98725:
E 29
		/* rx engine never stops */
		which &= ~NAR_SR;
		break;
	}

E 28
	if ((lp->nar & which) == 0) {
D 28
		/* the nic have stopped */
		return;
E 28
I 28
		/* the nic has stopped for the specified direction */
		return (old);
E 28
	}
E 10

D 10
		UPDATE_NAR(dp, lp->nar);
E 10
I 10
	/* reset designated bits in csr6 */
D 28
	UPDATE_NAR(dp, lp->nar & ~which);
E 28
I 28
	lp->nar &= ~which;
	DPRINTF(1, (CE_CONT, "!%s: %s: nar:%b -> %b",
	    dp->name, __func__,
	    INL(dp, NAR), CSR6BITS, lp->nar, CSR6BITS));
	UPDATE_NAR(dp, lp->nar);
E 28
E 10
D 29

E 29
I 29
#if 0
E 29
I 28
	switch (lp->hw_info->chip_type) {
	case CHIP_DM9102:
I 29
	case CHIP_DM9102A:
E 29
		/* no need to wait rx engine stops */
		which &= ~NAR_SR;
		break;
	}
D 29

E 29
I 29
#endif
E 29
E 28
D 10
		for(i = 1000; i > 0; i--) {
			sr = INL(dp, SR);
			if ((sr & SR_TPS) != 0 || (sr & 0xe0000) == 0) {
E 10
I 10
	/*
	 * Note: FreeBSD driver says that PNIC takes 10mS to process
D 16
	 * its setupframe.
E 16
I 16
	 * a setupframe.
E 16
	 */
D 28
	for(i = 0; i < 20000; i++) {
E 28
I 28
	for (i = 0; i < 20000; i++) {
E 28
		sr = INL(dp, SR);
D 28
		if ((which & NAR_ST) != 0) {
			switch (lp->hw_info->chip_type) {
			default:
				if ((sr & SR_TS) != (TS_STOP << SR_TS_SHIFT)) {
					drv_usecwait(10);
					continue;
				}
E 10
				break;
E 28
I 28
		if (which & NAR_ST) {
			if ((sr & SR_TS) != (TS_STOP << SR_TS_SHIFT)) {
				drv_usecwait(10);
				continue;
E 28
			}
D 10
			drv_usecwait(10);
E 10
		}

D 10
		DPRINTF(3, (CE_CONT, "%s: tu_freeze_chip: stopped in %d uS",
			dp->name, (1000 - i)*10));

		if (i <= 0) {
			cmn_err(CE_WARN, "%s: tu_freeze_chip: timeout",
				dp->name);
E 10
I 10
D 28
		if ((which & NAR_SR) != 0) {
			switch (lp->hw_info->chip_type) {
			case CHIP_CENTAUR:
			case CHIP_DM9102:
I 17
			case CHIP_XIRCOM:
E 17
D 16
				/* Rx engine never stop */
E 16
I 16
				/* the rx engine never stops */
E 16
				break;
			default:
				if ((sr & SR_RS) != (RS_STOP << SR_RS_SHIFT)) {
					drv_usecwait(10);
					continue;
				}
				break;
E 28
I 28
		if (which & NAR_SR) {
			if ((sr & SR_RS) != (RS_STOP << SR_RS_SHIFT)) {
				drv_usecwait(10);
				continue;
E 28
			}
E 10
		}
I 10

D 26
		DPRINTF(2, (CE_CONT,
			"%s: tu_freeze_chip: %b stopped in %d uS",
			dp->name, which, CSR6BITS, i*10));
E 26
I 26
D 28
		DPRINTF(2, (CE_CONT, "%s: %s: %b stopped in %d uS",
			dp->name, __func__, which, CSR6BITS, i*10));
E 26
		return;
E 28
I 28
		DPRINTF(2, (CE_CONT, "!%s: %s: %b stopped in %d uS",
		    dp->name, __func__, which, CSR6BITS, i*10));
		return (old);
E 28
E 10
	}
I 10

D 26
	cmn_err(CE_WARN, "!%s: tu_freeze_chip: timeout, sr:%b, csr6:%b",
		dp->name, sr, SR_BITS, INL(dp, NAR), CSR6BITS);
E 26
I 26
	cmn_err(CE_NOTE, "!%s: %s: timeout, sr:%b, csr6:%b",
D 28
		dp->name, __func__, sr, SR_BITS, INL(dp, NAR), CSR6BITS);
E 28
I 28
	    dp->name, __func__, sr, SR_BITS, INL(dp, NAR), CSR6BITS);
	return (old);
E 28
E 26
E 10
}

static void
D 28
tu_restart_chip(struct gem_dev *dp)
E 28
I 28
tu_restart_chip(struct gem_dev *dp, uint32_t which)
E 28
{
D 28
	struct tu_dev	*lp = (struct tu_dev *)dp->private;
E 28
I 10
	uint32_t	curr;
I 28
	struct tu_dev	*lp = dp->private;
E 28
E 10

I 28
	/* restore previous ST and SR bit */
	lp->nar &= ~(NAR_ST | NAR_SR);
	lp->nar |= which & (NAR_ST | NAR_SR);

E 28
I 26
#if DEBUG_LEVEL > 3
D 28
	if ((lp->nar & (NAR_SR | NAR_ST)) != (NAR_SR | NAR_ST)) {
		cmn_err(CE_CONT, "!%s: %s: new nar:%b",
			dp->name, __func__, lp->nar, CSR6BITS);
	}
E 28
I 28
	cmn_err(CE_CONT, "!%s: %s: nar:%b -> %b",
	    dp->name, __func__,
	    INL(dp, NAR), CSR6BITS, lp->nar, CSR6BITS);
E 28
#endif

E 26
D 10
	if ((lp->nar & NAR_SR) != 0) {
E 10
I 10
	curr = INL(dp, NAR);
D 11
	if ((lp->nar & ~curr & NAR_SR) != 0) {
E 10
		/* retart Rx engine */
E 11
I 11
D 26
	if ((lp->nar & (~curr) & NAR_SR) != 0) {
E 26
I 26
	if (lp->nar & (~curr) & NAR_SR) {
		if (lp->hw_info->chip_type == CHIP_ULI526X) {
D 28
			DPRINTF(2, (CE_CONT, "%s: %s: called for ULI526X",
				dp->name, __func__));
E 28
I 28
			DPRINTF(2, (CE_CONT, "!%s: %s: called for ULI526X",
			    dp->name, __func__));
E 28
			/* XXX - fix rx descriptor base */
			OUTL(dp, RDB, dp->rx_ring_dma +
D 28
				sizeof(struct rx_desc) *
					SLOT(dp->rx_active_head, RX_RING_SIZE));
E 28
I 28
			    sizeof (struct rx_desc) *
			    SLOT(dp->rx_active_head, RX_RING_SIZE));
E 28
		}
E 26
		/* restart Rx engine */
E 11
D 10
		OUTL(dp, NAR, lp->nar & ~NAR_ST);
E 10
I 10
D 26
		OUTL(dp, NAR, lp->nar & ~(~curr & NAR_ST));
E 26
I 26
D 28
		OUTL(dp, NAR, (lp->nar & ~NAR_ST) | (curr & NAR_ST));
E 26
E 10
		drv_usecwait(5);
E 28
I 28
		UPDATE_NAR(dp, (lp->nar & ~NAR_ST) | (curr & NAR_ST));
E 28
	}

D 10
	if ((lp->nar & NAR_ST) != 0) {
E 10
I 10
D 11
	if ((lp->nar & ~curr & NAR_ST) != 0) {
E 10
		/* retart Tx engine */
E 11
I 11
D 26
	if ((lp->nar & (~curr) & NAR_ST) != 0) {
E 26
I 26
	if (lp->nar & (~curr) & NAR_ST) {
E 26
		/* restart Tx engine */
E 11
D 28
		OUTL(dp, NAR, lp->nar);
		drv_usecwait(5);
E 28
I 28
		UPDATE_NAR(dp, lp->nar);
E 28
	}
I 28

E 28
I 17
	DPRINTF(1, (CE_CONT, "!%s: %s: new nar:%b",
D 28
		dp->name, __func__, lp->nar, CSR6BITS));
E 28
I 28
	    dp->name, __func__, lp->nar, CSR6BITS));
E 28
E 17
}

E 9
static int
tu_reset_chip(struct gem_dev *dp)
{
D 7
	int	i;
	struct tu_chip_state	*lp = (struct tu_chip_state *)dp->private;
E 7
I 7
	int		i;
I 9
	uint32_t	val;
E 9
D 28
	struct tu_dev	*lp = (struct tu_dev *)dp->private;
E 28
I 28
	struct tu_dev	*lp = dp->private;
E 28
E 7

I 9
D 28
	DPRINTF(2, (CE_CONT, "!%s: tu_reset_chip: called: csr6: %b",
			dp->name, lp->nar, CSR6BITS));
E 28
I 28
	DPRINTF(1, (CE_CONT, "!%s: %s: called: nar:%b, csr6:%b",
	    dp->name, __func__,
	    lp->nar, CSR6BITS,
	    INL(dp, NAR), CSR6BITS));
E 28

I 26
	/* invalidate address cache */
D 28
	bzero(lp->mac_addr, sizeof(lp->mac_addr));
E 28
I 28
	bzero(lp->mac_addr, sizeof (lp->mac_addr));
E 28
	lp->last_mc_count = -1;

E 26
E 9
	/* IER (CSR7) - Interrupt Enable register, zero */
D 7
	OUTL(dp, IER, 0);
E 7
I 7
D 28
	lp->ier = 0;
	OUTL(dp, IER, lp->ier);
E 28
I 28
	OUTL(dp, IER, 0);
	FLSHL(dp, IER);
	if (lp->ier == 0) {
		/* clear pended interrupt */
		OUTL(dp, SR, 0xffffffffU);
	}
E 28
E 7

D 28
	/* clear pended interrupt */
	OUTL(dp, SR, 0xffffffff);

E 28
D 2
	if (lp->hw_info->chip_type == CHIP_AN983) {
E 2
I 2
	if (lp->hw_info->chip_type == CHIP_CENTAUR) {
E 2
		/* IER2 (ACSR7) - Interrupt Enable register 2, zero */
		OUTL(dp, IER2_AN, 0);
		/* clear pended interrupt */
D 28
		OUTL(dp, SR2_AN, 0xffffffff);
E 28
I 28
		OUTL(dp, SR2_AN, 0xffffffffU);
E 28
	}

D 2
	/* initialize operating mode (stop tx and rx) */
E 2
I 2
	/* stop tx and rx but keep other operating mode bits */
D 10
	lp->nar &= ~(NAR_ST | NAR_SR);
E 2
D 9
	OUTL(dp, NAR, INL(dp, NAR) & ~(NAR_ST | NAR_SR));
I 2
	drv_usecwait(5);
E 2

E 9
I 9
#ifdef notdef
	val = INL(dp, NAR);
	UPDATE_NAR(dp, val);
#endif
E 10
I 10
	lp->nar &= ~(NAR_ST | NAR_SR); /* dont write it to CSR6 */

E 10
E 9
	/* Reset the chip. */
I 11
	switch (lp->hw_info->chip_type) {
	case CHIP_21140:
	case CHIP_21142:
		/* workaround for tx hang */
D 28
		OUTL(dp, NAR, NAR_PS);
E 28
I 28
		UPDATE_NAR(dp, NAR_PS);
E 28
	}
E 11
	OUTL(dp, PAR, PAR_SWR);

D 3
	/* DM9102 requires 100us to complete resetting */
E 3
I 3
D 9
	/* Davicom DM9102 requires 100us to complete resetting */
E 3
	drv_usecwait(100);
E 9
I 9
D 10
	switch (lp->hw_info->chip_type) {
	case CHIP_DM9102:
		/* Davicom DM9102 requires 100us to complete resetting */
		drv_usecwait(100);
		OUTL(dp, PAR, 0);
		drv_usecwait(5);
		break;
E 10
I 10
	/* wait a while, as it seems to cause a PCI bus error on sparc. */
	/* DM9102 needs 100uS, MX98715 needs 50uS */
	drv_usecwait(100);
E 10
E 9

I 10
	switch (lp->hw_info->chip_type) {
E 10
I 3
D 9
	if (lp->hw_info->chip_type == CHIP_CONEXANT) {
E 9
I 9
	case CHIP_CONEXANT:
E 9
		/*
		 * For Conexant RS7112 chips,
D 9
		 * need to reset SWR bit explicitly
E 9
I 9
		 * it need to reset SWR bit explicitly
E 9
		 */
		/* Freebsd waits 10ms, but I do not know the reason */
		drv_usecwait(10000);
I 11
D 28
		/* fall down */

E 28
I 28
		/* FALLTHRU */
E 28
E 11
D 10

E 10
I 10
	case CHIP_DM9102:
I 29
	case CHIP_DM9102A:
E 29
I 17
	case CHIP_XIRCOM:
E 17
E 10
		OUTL(dp, PAR, INL(dp, PAR) & ~PAR_SWR);
I 10
		drv_usecwait(5);
E 10
D 9
	}
E 9
I 9
		break;
E 9

E 3
D 9
	i = 0;
	while ((INL(dp, PAR) & PAR_SWR) != 0) {
		drv_usecwait(10);
		if (i++ > 100) {
			cmn_err(CE_WARN, "%s: tu_reset_chip: timeout",
				dp->name);
E 9
I 9
	default:
D 28
		i = 0;
		while ((INL(dp, PAR) & PAR_SWR) != 0) {
E 28
I 28
		for (i = 0; INL(dp, PAR) & PAR_SWR; i++) {
E 28
			drv_usecwait(10);
D 28
			if (i++ > 100) {
E 28
I 28
			if (i > 100) {
E 28
D 29
				cmn_err(CE_WARN, "%s: tu_reset_chip: timeout",
D 28
					dp->name);
E 28
I 28
				    dp->name);
E 28
E 9
#if DEBUG_LEVEL > 1
E 29
I 29
				cmn_err(CE_WARN, "%s: %s: timeout",
				    dp->name, __func__);
#if DEBUG_LEVEL > 2
E 29
D 9
			return -1;
E 9
I 9
D 17
				return -1;
E 17
I 17
				return (GEM_FAILURE);
E 17
E 9
#endif
I 9
			}
E 9
		}
	}
I 10

I 17
D 26
	/* phy reset sequence if defined */
E 26
I 26
D 29
	/* issue external phy reset sequence if defined */
E 29
I 29
	/* issue external phy reset sequence if it is defined */
E 29
E 26
	tu_enable_phy(dp);

E 17
D 28
	DPRINTF(2, (CE_CONT, "!%s: tu_reset_chip 1: called: csr6: %b",
		dp->name, INL(dp, NAR), CSR6BITS));
E 28
I 28
	lp->first_setupframe = B_TRUE;
E 28
E 10
D 17
	return 0;
E 17
I 17

I 28
	DPRINTF(2, (CE_CONT, "!%s: %s: return: csr6: %b",
	    dp->name, __func__, INL(dp, NAR), CSR6BITS));

E 28
	return (GEM_SUCCESS);
E 17
}

I 9
/*
 * tu_init_chip: initialize all registers except in PHY layer
 */
E 9
D 20
static void
E 20
I 20
static int
E 20
tu_init_chip(struct gem_dev *dp)
{
	int		i;
D 9
	int		offset;
E 9
I 9
	int		linesize;
E 9
	uint32_t	val;
	volatile int	x;
D 7
	struct tu_chip_state	*lp = (struct tu_chip_state *)dp->private;
E 7
I 7
D 28
	struct tu_dev	*lp = (struct tu_dev *)dp->private;
E 28
E 7
	uint32_t	burst_len;
I 28
	struct tu_dev	*lp = dp->private;
E 28

I 2
D 8
	DPRINTF(0, (CE_CONT, "!%s: tu_init_chip: called: csr6: %b",
E 8
I 8
D 10
	DPRINTF(2, (CE_CONT, "!%s: tu_init_chip: called: csr6: %b",
E 8
			dp->name, lp->nar, CSR6BITS));
E 10
I 10
D 16
	DPRINTF(2, (CE_CONT, "!%s: tu_init_chip called: nar:%b csr6: %b",
		dp->name, lp->nar, CSR6BITS, INL(dp, NAR), CSR6BITS));
E 16
I 16
D 17
	DPRINTF(0, (CE_CONT,
E 17
I 17
D 28
	DPRINTF(1, (CE_CONT,
E 17
		"!%s: %s called: csr0:%x nar:%b csr6: %b",
		dp->name, __func__,
		INL(dp, PAR), lp->nar, CSR6BITS, INL(dp, NAR), CSR6BITS));
E 28
I 28
	DPRINTF(-1, (CE_CONT,
	    "!%s: %s called: csr0:%x nar:%b csr6: %b",
	    dp->name, __func__,
	    INL(dp, PAR), lp->nar, CSR6BITS, INL(dp, NAR), CSR6BITS));
E 28
E 16
E 10

E 2
	/* IER (CSR7) - Interrupt Enable register, zero */
D 7
	OUTL(dp, IER, 0);
E 7
I 7
	lp->ier = 0;
	OUTL(dp, IER, lp->ier);

E 7
D 2
	if (lp->hw_info->chip_type == CHIP_AN983) {
E 2
I 2
D 9
	if (lp->hw_info->chip_type == CHIP_COMET ||
	    lp->hw_info->chip_type == CHIP_CENTAUR) {
E 9
I 9
	if (lp->hw_info->chip_type == CHIP_CENTAUR) {
E 9
E 2
		/* IER2 (ACSR7) - Interrupt Enable register 2, zero */
		OUTL(dp, IER2_AN, 0);
	}

	/*
D 28
	 * PAR (CSR0) - PCI accress register 
E 28
I 28
	 * PAR (CSR0) - PCI accress register
E 28
I 2
	 * This register determines behaviour of the chip on DMA.
E 2
	 */
D 16
	val = 0;
E 16
I 16
	val = INL(dp, PAR) &
D 28
		~(PAR_PBL | PAR_RME | PAR_RLE | PAR_WIE | PAR_BAR | PAR_CAL);
E 28
I 28
	    ~(PAR_PBL | PAR_RME | PAR_RLE | PAR_WIE |
	    PAR_BAR | PAR_CAL | PAR_TAP);
E 28

	/* determin valid cache line size */
E 16
D 9
	if (lp->pci_cache_linesz > 32) {
E 9
I 9
D 28
	linesize = lp->pci_cache_linesz;
	if (linesize > 32 || (linesize & (linesize - 1)) != 0) {
E 28
I 28
	linesize = lp->pci_cache_linesz;	/* in double word */
	if (linesize > 32 || (linesize & (linesize - 1))) {
E 28
E 9
		/*
D 9
		 * Sytem cache line size is too big.
D 2
		 * Disable all cache oriented transactions
E 2
I 2
		 * Disable using all cache oriented transactions
E 9
I 9
D 28
		 * Sytem cache line size is too big or invalid.
E 28
I 28
		 * System cache line size is too big or invalid.
E 28
		 * Disable all cache oriented transactions.
E 9
E 2
		 */
D 9
		lp->pci_cache_linesz = 0;
E 9
I 9
		linesize = 0;
E 9
	}
I 16
D 28
	if (linesize > 0 && linesize < 8) {
E 28
I 28
	if (linesize > 0) {
E 28
		/* minimum cache line size is 8DW for the device */
D 28
		linesize = 8;
E 28
I 28
		linesize = max(linesize, 8);
E 28
	}
E 16

D 2
	/* PBL: is equal or greater than cache_linesz if WIE or RLE */
E 2
I 2
	/*
	 * PBL (Programmable Burst Length) is equal or greater than
	 * cache_linesz if WIE or RLE is enabled.
D 3
	 * DM9802 does not have PBL field, but it seems ok.
E 3
I 3
D 9
	 * DM9102 does not have PBL field, but it seems ok.
E 9
E 3
	 */
E 2
D 9
	burst_len = 32;	/* in double word unit */
D 2
#if 0
	if (lp->hw_info->chip_type == CHIP_AN983) {
		/* work around for ADMtek 983B */
		burst_len = 16;
	}
#endif
E 2
	if (lp->pci_cache_linesz > burst_len) {
D 2
		/* disable cache oriented transactions */
E 2
I 2
		/* disable using cache oriented transactions */
E 2
		lp->pci_cache_linesz = 0;
	}
E 9
I 9
D 11
	burst_len = 32;	/* maximum value */
E 11
I 11
D 16
	burst_len = max(dp->rxmaxdma, dp->txmaxdma)/sizeof(uint32_t);
E 16
I 16
D 28
	burst_len = max(dp->rxmaxdma, dp->txmaxdma)/4;
E 16
D 17
	if (burst_len > 0 && burst_len < linesize) {
E 17
I 17
	if (burst_len < linesize) {
E 17
I 16
		/*
		 * For performance, burst length should be increased
		 * to cache line size.
		 */
E 16
		burst_len = linesize;
	}
E 28
I 28
	burst_len = max(dp->rxmaxdma, dp->txmaxdma)/4;	/* in double word */
	/*
	 * For performance, burst length should be increased
	 * to the cache line size.
	 */
	burst_len = max(burst_len, linesize);

E 28
I 16
	/* burst length should be power of 2 */
E 16
	burst_len = 2*burst_len - 1;
D 28
	while ((burst_len & (burst_len - 1)) != 0) {
E 28
I 28
	while ((burst_len & (burst_len - 1))) {
E 28
D 17
		burst_len &= (burst_len -1);
E 17
I 17
		burst_len &= (burst_len - 1);
E 17
	}
I 28

E 28
D 16

	switch (lp->hw_info->chip_type) {
#if 0
	case CHIP_MX987XX:
	case CHIP_LC82C115:
	case CHIP_LC82C168:
	case CHIP_CENTAUR:
	case CHIP_21142:
		if (burst_len > 32) {
			burst_len = 0;	/* unlimited */
		} else if (burst_len < 1) {
			burst_len = 1;
		}
		break;

	case CHIP_DM9102:
		burst_len = 0;
		break;
#endif
	default:
		burst_len = max(min(burst_len, 32), 1);
		break;
	}
E 16
I 16
D 17
	/* burst length should be between 1 and 32 */
	burst_len = max(min(burst_len, 32), 1);
E 17
I 17
	/* burst length must be between 1 and 32 */
	burst_len = max(burst_len, 1);
I 29
	if ((lp->hw_info->capability & CHIP_CAP_PBL_UNLMT) &&
	    burst_len > 32) {
		/* unlimited */
		burst_len = 0;
	} else {
		burst_len = min(burst_len, 32);
	}

E 29
	switch (lp->hw_info->chip_type) {
I 28
	case CHIP_DM9102:
I 29
	case CHIP_DM9102A:
E 29
		/*
		 * XXX - DM9102 chip bug: PBL must be unlimited.
		 * if PBL is not zero, received packets are corrupted.
		 */
		burst_len = 0;
		break;
D 29

E 28
	case CHIP_MX987XX:
I 28
#if 1 /* not yet */
E 28
		if (lp->pci_revid <= 0x1f) {
			/* mx98713 or mx98713a */
			goto pbl_default;
		}
D 28
		/* falldown */
E 28
I 28
		/* FALLTHRU */
#endif
E 28
	case CHIP_CENTAUR:
	case CHIP_LC82C168:
	case CHIP_LC82C115:
		if (burst_len > 32) {
			/* unlimited */
			burst_len = 0;
		}
		break;

	pbl_default:
	default:
		burst_len = min(burst_len, 32);
		break;
E 29
	}
E 17
E 16
E 11
E 9
	val |= burst_len << PAR_PBL_SHIFT;
D 7

D 2
	if (lp->pci_cache_linesz > 0) {
		/*
		 * Set WIE if the system has memory write invalidate
		 * capebility
E 2
I 2

E 7
I 7
D 9
#ifdef notdef
	/*
	 * XXX - This code cause system stuck.
	 */
	if (lp->hw_info->chip_type == CHIP_DM9102) {
		if ((lp->pci_revid & 0xff) >= 0x30) {
			/* DM9102A */
			val = 0x00400000 | PAR_RLE | PAR_RME;
		} else {
			/* DM9102 */
			val = 0;
		}
	} else
#endif
I 8
#if 1
	if (lp->hw_info->chip_type == CHIP_LC82C168) {
		/* is it right ? */
		val |= PAR_CAL_32DW;
	} else
#endif
E 8
E 7
	if (lp->pci_cache_linesz >= 8 && lp->pci_cache_linesz <= 32 &&
D 3
	   (lp->pci_cache_linesz & (lp->pci_cache_linesz >> 1)) == 0) {
E 3
I 3
	   (lp->pci_cache_linesz & (lp->pci_cache_linesz - 1)) == 0) {
E 9
I 7

D 9
		/* We can use cache-oriented PCI transactions */

E 7
E 3
		/* 
		 * Set RLE (Read Line Enable) for read transactions in PCI bus.
E 2
		 */
D 2
		val |= (lp->pci_comm & PCI_COMM_MEMWR_INVAL) ? PAR_WIE : 0;
E 2
I 2
		val |= PAR_RLE;
E 2

		/* 
D 2
		 * Set RLE and RME for read transactions in PCI bus.
E 2
I 2
		 * Set RME (Read Multiple Enable) always.
E 2
		 */
D 2
		val |= PAR_RLE | PAR_RME;
E 2
I 2
		val |= PAR_RME;
E 2

E 9
I 9
	if (linesize > 0) {
E 9
		/*
D 2
		 * Cache Alignment:
		 *  must be equeal to system cache line size if RLE is 1.			 */
		val |= lp->pci_cache_linesz << PAR_CAL_SHIFT;
E 2
I 2
		 * Set WIE (Write Invalidate Enable) if the system has
		 * memory write invalidate capability
		 */
		/* avoid buggy 21143 rev 0x41 */
		if (!(lp->hw_info->chip_type == CHIP_21142 &&
D 28
		      lp->pci_revid == 0x41)) {
E 28
I 28
		    lp->pci_revid == 0x41)) {
E 28
			val |= (lp->pci_comm & PCI_COMM_MEMWR_INVAL)
D 28
					? PAR_WIE : 0;
E 28
I 28
			    ? PAR_WIE : 0;
E 28
		}
I 9
	}
E 9

I 9
D 11
	if (lp->hw_info->chip_type == CHIP_DM9102) {
E 11
I 11
	switch (lp->hw_info->chip_type) {
	case CHIP_DM9102:
E 11
E 9
D 29
		/*
D 3
		 * CAL (Cache ALignment) must be equeal to system cache
E 3
I 3
D 9
		 * CAL (Cache ALignment) must be equal to system cache
E 3
		 * line size if RLE is set.
E 9
I 9
		 * DM9102 does not have PBL and CAL field.
E 9
		 */
D 9
		switch (lp->pci_cache_linesz) {
		case 8:
			val |= PAR_CAL_8DW;
			break;
		case 16:
			val |= PAR_CAL_16DW;
			break;
		case 32:
			val |= PAR_CAL_32DW;
			break;
E 9
I 9
		if ((lp->pci_revid & 0xff) >= 0x30) {
D 14
			/* DM9102A have read multiple PCI bud command */
E 14
I 14
			/* DM9102A have read multiple PCI bus command */
E 14
			val |= PAR_RME;
E 9
		}
E 29
I 29
	case CHIP_MX98713:
	case CHIP_MX98713A:
	case CHIP_MX98715:
	case CHIP_MX98725:
		/* do nothing */
E 29
E 2
D 11
	}
I 9
	else {
E 11
I 11
		break;
I 16

I 29
	case CHIP_DM9102A:
		/* DM9102A have read multiple PCI bus command */
		val |= PAR_RME;
		break;

E 29
E 16
	default:
E 11
D 28
		/* 
E 28
I 28
		/*
E 28
		 * Set RLE (Read Line Enable) for read transactions in PCI bus.
		 */
		val |= PAR_RLE;

D 28
		/* 
E 28
I 28
		/*
E 28
		 * Set RME (Read Multiple Enable).
		 */
		val |= PAR_RME;
I 29
		break;
E 29
	}

	/*
	 * CAL (Cache ALignment) must be equal to system cache
	 * line size if RLE is set.
	 */
D 16
	if (linesize == 0) {
		/* fix cache line size */
		linesize = min(burst_len, tu_cache_linesz_default);
	}
E 16
	switch (linesize) {
	case 8:
		val |= PAR_CAL_8DW;
		break;
	case 16:
I 16
D 17
	default:
E 17
E 16
		val |= PAR_CAL_16DW;
		break;
	case 32:
I 17
	default:
E 17
		val |= PAR_CAL_32DW;
		break;
	}
I 16

E 16
#ifdef CENTAUR_BUG
	if (lp->hw_info->chip_type == CHIP_CENTAUR) {
D 11
		/* This aboid 983 becomes crazy on too long packet, but why? */
E 11
I 11
		/*
		 * This avoids ADMtek 983 becomes crazy on receiving
		 * too long packet, but why?
		 */
E 11
		val |= PAR_BAR;
	}
#endif
I 16
D 28
#if 0
D 17
	if (lp->hw_info->chip_type == CHIP_MX987XX) {
		if ((lp->pci_revid & 0xf0) == 0x00) {
			/* mx98713 */
			val |= PAR_BAR;
		}
E 17
I 17
	if (lp->hw_info->chip_type == CHIP_DM9102) {
		val |= PAR_BAR;
E 17
	}
#endif	
E 28
E 16
I 11
	/*
	 * To enable early transmit, tx bus arbitration priority should
	 * be higher than that of Rx.
	 */
	if ((lp->nar & NAR_SF) == 0) {
		val |= PAR_BAR;
	}
I 28

	/* TAP */
	switch (lp->hw_info->chip_type) {
	case CHIP_DM9102:
I 29
	case CHIP_DM9102A:
E 29
		val |= 1 << PAR_TAP_SHIFT;	/* 200uS */
	}

E 28
E 11
E 9
	OUTL(dp, PAR, val);
I 2
D 29
	drv_usecwait(5); /* DM9102 requires 5uS after PAR changed */
E 29
I 29
	drv_usecwait(5); /* DM9102 require 5uS after PAR changed */

E 29
I 7
D 8
	DPRINTF(0, (CE_CONT, "!%s: tu_init_chip: csr0: 0x%08x", dp->name, val));
E 8
I 8
D 28
	DPRINTF(2, (CE_CONT, "!%s: tu_init_chip: csr0: 0x%08x", dp->name, val));
E 28
I 28
	DPRINTF(2, (CE_CONT,
D 29
	    "!%s: %s: csr0: 0x%08x", dp->name, __func__, val));
E 29
I 29
	    "!%s: %s: csr0: 0x%08x", dp->name, __func__, INL(dp, PAR)));
E 29
E 28
E 8
E 7
E 2

D 2
#if 0
	/* OK */
	OUTL(dp, PAR,
		PAR_WIE | PAR_RLE | PAR_RME |PAR_CAL_16DW |PAR_PBL_16DW);

	/* NG */
	OUTL(dp, PAR,
		PAR_WIE | PAR_RLE | PAR_RME | PAR_CAL_16DW | PAR_PBL_32DW);
	OUTL(dp, PAR,0x009000 | PAR_BAR);
	/* AN983B */
	OUTL(dp, PAR,0xfe794800);
#endif
	/* DM9102 requires 5uS */
	drv_usecwait(5);

E 2
D 11
	/* TDR (CSR1) - Transmit demand register, do nothing*/
E 11
I 11
	/* TDR (CSR1) - Transmit demand register, do nothing */
E 11

D 11
	/* RDR (CSR2) - Receive demand register, do nothing*/
E 11
I 11
	/* RDR (CSR2) - Receive demand register, do nothing */
E 11

	/* RDB (CSR3) - Receeive descriptor base address */
D 16
	OUTL(dp, RDB, (uint32_t)dp->rx_ring_dma);
E 16
I 16
	OUTL(dp, RDB, dp->rx_ring_dma);
E 16

	/* TDB (CSR4) - Transmit descriptor base address */
D 16
	OUTL(dp, TDB, (uint32_t)dp->tx_ring_dma);
E 16
I 16
	OUTL(dp, TDB, dp->tx_ring_dma);
E 16

D 11
	/* SR (CSR5): dont touch */
E 11
I 11
	/* SR (CSR5) - don't touch */
E 11
D 28
	
E 28
I 28

E 28
D 2
	/* NAR (CSR6) - Network access register (set_rx_filter) */
	lp->nar = NAR_MBO	/* 25: constant */
#ifdef notdef
		| NAR_SF	/* 21: Store and forward for Tx operations */
#eles
		| (TR_1024 << NAR_TR_SHIFT)	/* Tx FIFO threshold */
#endif
		| NAR_SQE;	/* 19: disable SQE for MII 100m and 10m */
E 2
I 2
D 11
	/*
D 9
	 * NAR (CSR6) - Network access register
E 9
I 9
	 * NAR (CSR6) - Network access register: ensure port selection
	 *	tu_set_rx_filter() will write to csr6 later.
E 9
	 */
I 10
	DPRINTF(2, (CE_CONT, "!%s: tu_init_chip 1: nar:%b csr6: %b",
		dp->name, lp->nar, CSR6BITS, INL(dp, NAR), CSR6BITS));
E 10
E 2
D 9

D 2
	if (lp->hw_info->chip_type != CHIP_MX98715) {
		/* for mx98715, do not set PS bit */
		lp->nar |= NAR_PS;	/* 18: select MII/SYM */
	}
E 2
I 2
	/* Reset unused bits, but keep port selection info  */
	lp->nar &=~(NAR_SC	/* bit31: Special Capture mode */
		   |NAR_RA	/* bit30: Raceive All */
		   |NAR_ID	/* bit26: Ignore destination address MSB */
		   |NAR_CA	/* bit17: Capture Effect */
		   |NAR_FC	/* bit12: force collision */
		   |NAR_OM	/* bit11-10: operating mode */
		   |NAR_SBC	/* bit5: start/stop backoff counter */
		   |NAR_IF	/* bit4: inverse filtering */
		   );
I 7

E 7
	/* bit21: Store and forward for Tx operations */
D 7
	lp->nar |= NAR_SF;
E 7
I 7
	/* bit15-14: Transmit threshold control */
#ifdef notdef
	if (lp->hw_info->chip_type == CHIP_DM9102 &&
	   (lp->pci_revid & 0xff) >=0x30) {
		/* XXX - is this needed ? */
		lp->nar &= ~(NAR_SF | NAR_TR);
		lp->nar |= TR_256 << NAR_TR_SHIFT;
	} else
#endif
	{
		lp->nar |= NAR_SF;
E 9
I 9
	if (dp->mii_state == MII_STATE_LINKUP ||
	    dp->mii_state == MII_STATE_LINKDOWN) {
I 10
		/* we can sync NAR as auto-nego isn't in progress */
E 10
		tu_set_media(dp);
E 9
	}
I 10
#ifdef notdef
	else {
		/* sync csr6 to avoid to be in undefined state */
		ASSERT((lp->nar & (NAR_SR | NAR_ST)) == 0);
		UPDATE_NAR(dp, lp->nar & ~(NAR_ST | NAR_SR));
	}
#endif
	DPRINTF(2, (CE_CONT, "!%s: tu_init_chip 2: nar:%b csr6: %b",
		dp->name, lp->nar, CSR6BITS, INL(dp, NAR), CSR6BITS));
E 10
E 7
E 2

E 11
D 2
	if ((lp->hw_info->capability & CHIP_CAP_MII) == 0) {
		/* for SYM mode (MX98715) */
		lp->nar |= NAR_SCR	/* 24: Scrambler mode */
			|  NAR_PCS;	/* 23: Select SYM mode */
	}
	OUTL(dp, NAR,  lp->nar);	/* Write initial value for NAR */
	tu_set_media(dp);		/* Update NAR with media mode */
E 2
I 2
D 9
	/* bit19: disable SQE for SYM and MII 100M/10M */
D 3
	/* For DM9102, it is reserved. But it seems no effect. */
E 3
I 3
D 6
	/* For DM9102, that is reserved. But it seems no effect. */
E 6
I 6
	/* For DM9102, it is reserved. But it seems no effect. */
E 6
E 3
	lp->nar |= NAR_SQE;
E 2

I 2
	/*
	 * Dont touch following bits
	 * bit18: PS  : Port Select:
D 3
	 * bit18: SCR : Scrambler
	 * bit18: PCS : PCS function
	 * bit18: TTM : 10 base mode
	 * bit18: FD  : Full Duplex
E 3
I 3
	 * bit24: SCR : Scrambler
	 * bit23: PCS : PCS function
	 * bit22: TTM : 10 base mode
	 * bit9 : FD  : Full Duplex
E 3
	 */

	OUTL(dp, NAR,  lp->nar);
	drv_usecwait(5);
I 7
D 8
	DPRINTF(0, (CE_CONT, "!%s: tu_init_chip: csr6: %b",
E 8
I 8
	DPRINTF(2, (CE_CONT, "!%s: tu_init_chip: csr6: %b",
E 8
			dp->name, lp->nar, CSR6BITS));
E 7

	tu_set_media(dp);	/* Update NAR with media mode */

E 9
E 2
	/* LPC (CSR8) - Lost packet counter, cleared by reading */
	(void) INL(dp, LPC);

	/* SPR (CSR9) - Serial port register */
	OUTL(dp, SPR, 0);
D 2
	if (lp->hw_info->chip_type == CHIP_AN983) {
		/* TMR (CSR11) - General purpose timer, clear */
		OUTL(dp, TMR, 0);
	}
	if (lp->hw_info->chip_type == CHIP_AN983) {
E 2
I 2

	/* TMR (CSR11) - General purpose timer, clear */
D 16
	/* XXX - DM9102 does not have it. But it seems ok */
E 16
	OUTL(dp, TMR, 0);
I 17
D 29
#ifdef GEM_CONFIG_POLLING
I 28
	lp->timer_mask = 0;
E 28
E 17
I 16
	switch (lp->hw_info->chip_type) {
	case CHIP_CENTAUR:
D 28
		lp->timer_resolution = 205;
E 28
I 28
		lp->timer_resolution = 205*1000; /* nS */
E 28
		break;
E 29
E 16

I 16
D 29
	case CHIP_MX987XX:
I 28
		if (MX98713(lp)) {
			/*
			 * The datasheet says the timer resolution
			 * is 204.8uS, but it seems 82uS actually.
			 * In addition, lower 2 bit of TMR seems to
			 * be ignored. Therefore, effective timer
			 * resolution is 82 * 4 = 324uS.
			 */
			lp->timer_mask = 3;
			break;
		}
		/* FALLTHRU */
E 28
	case CHIP_LC82C115:
	case CHIP_21140:
	case CHIP_21142:
I 26
	case CHIP_ULI526X:
E 26
D 28
		lp->timer_resolution = 82;
E 28
I 28
		lp->timer_resolution = 82*1000; /* nS */
E 28
		break;

	default:
		/* CHIP_DM9102:  no timer */
		/* CHIP_LC82C168: no timer */
		lp->timer_resolution = 0;
		break;
	}
D 17

E 17
I 17
#endif
E 29
E 17
E 16
D 9
	if (lp->hw_info->chip_type == CHIP_COMET ||
	    lp->hw_info->chip_type == CHIP_CENTAUR) {
E 9
I 9
	if (lp->hw_info->chip_type == CHIP_CENTAUR) {
E 9
E 2
		/* WCSR(CSR13) - Wakeup control/status register, clear */
		OUTL(dp, WCSR_AN, 0);
	}

D 9
	/* WTMR (CSR15) - Watchdog and jabber timer register */
	OUTL(dp, WTMR, WTMR_ABM);
E 9
I 9
	/* SIAGP (CSR15) - Watchdog and jabber timer register: set later */
E 9

D 2
	if (lp->hw_info->chip_type == CHIP_AN983) {
E 2
I 2
D 9
	if (lp->hw_info->chip_type == CHIP_COMET ||
	    lp->hw_info->chip_type == CHIP_CENTAUR) {
E 9
I 9
	if (lp->hw_info->chip_type == CHIP_CENTAUR) {
E 9
E 2
		/* CR(CSR18) - Command register */
D 2
#if 1
E 2
		OUTL(dp, CR_AN, CR_ATUR);
D 2
#else
		OUTL(dp, CR_AN, 0xa4c800a5);
		OUTL(dp, 0xa0, 0x00000000);
		OUTL(dp, 0x9c, 0xffeaf000);	/* CSR23 */
		OUTL(dp, 0x90, 0x00008000);	/* CSR20 */
		OUTL(dp, WCSR, 0x60010604);
#endif
E 2
	}
I 9

I 17
	/*
	 * additional hardware depend initialization
	 */
E 17
I 10
	switch (lp->hw_info->chip_type) {
D 11
	case CHIP_MX98713:
		OUTL(dp, 0x80/* CSR16*/, 0x0f370000 | (INL(dp, 0x80) & 0xffff));
E 11
I 11
D 29
	case CHIP_MX987XX:
		if ((lp->pci_revid & 0xf0) == 0x00) {
			/* mx98713 */
D 16
			OUTL(dp, 0x80/* CSR16*/, 0x0f37fec8);
E 16
I 16
D 28
			OUTL(dp, 0x80/* CSR16*/,
				0x0f370000 | (INL(dp, 0x80) & 0xffff));
E 28
I 28
			OUTL(dp, 0x80 /* CSR16 */,
			    0x0f370000 | (INL(dp, 0x80) & 0xffff));
E 28
E 16
		} else {
			/* mx98713a, mx98715, mx98725 */
D 28
			OUTL(dp, 0x80/* CSR16*/,
				0x0b3c0000 | (INL(dp, 0x80) & 0xffff));
E 28
I 28
			OUTL(dp, 0x80 /* CSR16 */,
			    0x0b3c0000 | (INL(dp, 0x80) & 0xffff));
E 28
		}
E 29
I 29
	case CHIP_MX98713:
		OUTL(dp, 0x80 /* CSR16 */,
		    0x0f370000 | (INL(dp, 0x80) & 0xffff));
		break;
E 29

D 29
		if ((lp->pci_revid & 0xf0) >= 0x20) {
			/* mx98715 and mx98725 */
D 28
			OUTL(dp, 0xa0/* CSR20*/,
				0x00011000 | (INL(dp, 0xa0) & 0xffff));
E 28
I 28
			OUTL(dp, 0xa0 /* CSR20 */,
			    0x00011000 | (INL(dp, 0xa0) & 0xffff));
E 28
		}
E 29
I 29
	case CHIP_MX98713A:
		OUTL(dp, 0x80 /* CSR16 */,
		    0x0b3c0000 | (INL(dp, 0x80) & 0xffff));
E 29
E 11
		break;
I 29

	case CHIP_MX98715:
	case CHIP_MX98725:
		OUTL(dp, 0x80 /* CSR16 */,
		    0x0b3c0000 | (INL(dp, 0x80) & 0xffff));

		OUTL(dp, 0xa0 /* CSR20 */,
		    0x00011000 | (INL(dp, 0xa0) & 0xffff));
		break;
E 29
D 11
	case CHIP_MX98715:
		OUTL(dp, 0x80/* CSR16*/, 0x0b3c0000 | (INL(dp, 0x80) & 0xffff));
		OUTL(dp, 0xa0/* CSR20*/, 0x00011000 | (INL(dp, 0xa0) & 0xffff));
		break;
E 11
	}

E 10
D 17
	if (lp->port == PORT_MII) {
		/*
		 * disable built-in NWAY logic and SIA port
		 */
I 10
		ASSERT((lp->nar & (NAR_ST | NAR_SR)) == 0);

E 10
		switch (lp->hw_info->chip_type) {
		case CHIP_LC82C168:
			/* disable NWAY logic */
			val = INL(dp, PNIC_NWAY);
			OUTL(dp, PNIC_NWAY, val | NWAY_PD | NWAY_LC);
			break;

		case CHIP_21142:
I 16
			/* shutdown SIA media */
E 16
D 11
		case CHIP_LC82C115:
D 10
		case CHIP_MX98715:
E 10
		case CHIP_MX98713:
D 10
			ASSERT((lp->nar & (NAR_ST | NAR_SR)) == 0);
E 10
I 10
		case CHIP_MX98715:
			UPDATE_NAR(dp, lp->nar & ~(NAR_PS & NAR_ST | NAR_SR));
E 11
I 11
			UPDATE_NAR(dp, lp->nar & ~NAR_PS);
E 11
E 10
			OUTL(dp, SIACONN, 0);	/* csr13 */
			OUTL(dp, SIACTRL, 0);	/* csr14 */
D 10
			UPDATE_NAR(dp, lp->nar);
E 10
I 10
D 11
			UPDATE_NAR(dp, lp->nar & ~(NAR_ST | NAR_SR));
E 11
I 11
			UPDATE_NAR(dp, lp->nar);
E 11
E 10
			break;
		}
I 10
D 11

E 11
E 10
	}
I 10

E 17
D 11
	/* Prepare to send setupframes */
E 11
I 11
	/*
	 * NAR (CSR6) - Network access register:
	 *	Prepare to send setupframes
	 */
	DPRINTF(2, (CE_CONT, "!%s: tu_init_chip 1: nar:%b csr6: %b",
D 28
		dp->name, lp->nar, CSR6BITS, INL(dp, NAR), CSR6BITS));
E 28
I 28
	    dp->name, lp->nar, CSR6BITS, INL(dp, NAR), CSR6BITS));
E 28
E 11
	lp->nar |= NAR_ST;
	UPDATE_NAR(dp, lp->nar);
I 11
	DPRINTF(2, (CE_CONT, "!%s: tu_init_chip 2: nar:%b csr6: %b",
D 28
		dp->name, lp->nar, CSR6BITS, INL(dp, NAR), CSR6BITS));
E 28
I 28
	    dp->name, lp->nar, CSR6BITS, INL(dp, NAR), CSR6BITS));
E 28
I 20

	return (GEM_SUCCESS);
E 20
E 11
E 10
E 9
D 2
#ifdef notdef
	for (i=0; i<22; i++) {
		cmn_err(CE_CONT, "%d: 0x%04x", i, tu_mii_read(dp, i));
	}
#endif
E 2
}

D 2
#if 0
E 2
D 20
static void
E 20
I 20
static int
E 20
D 2
tu_dump_regs(struct gem_dev *dp)
{
	int	i;

	cmn_err(CE_CONT, "CSR%d: 0x%08x", 0, INL(dp, 0*8));
	cmn_err(CE_CONT, "CSR%d: 0x%08x", 1, INL(dp, 1*8));
	cmn_err(CE_CONT, "CSR%d: 0x%08x", 2, INL(dp, 2*8));
	cmn_err(CE_CONT, "CSR%d: 0x%08x", 3, INL(dp, 3*8));
	cmn_err(CE_CONT, "CSR%d: 0x%08x", 4, INL(dp, 4*8));
	cmn_err(CE_CONT, "CSR%d: 0x%08x", 5, INL(dp, 5*8));
	cmn_err(CE_CONT, "CSR%d: 0x%08x", 6, INL(dp, 6*8));
	cmn_err(CE_CONT, "CSR%d: 0x%08x", 7, INL(dp, 7*8));
	cmn_err(CE_CONT, "CSR%d: 0x%08x", 8, INL(dp, 8*8));
	cmn_err(CE_CONT, "CSR%d: 0x%08x", 9, INL(dp, 9*8));
	cmn_err(CE_CONT, "CSR%d: 0x%08x", 10, INL(dp, 10*8));
	cmn_err(CE_CONT, "CSR%d: 0x%08x", 11, INL(dp, 11*8));
	cmn_err(CE_CONT, "CSR%d: 0x%08x", 12, INL(dp, 12*8));
	cmn_err(CE_CONT, "CSR%d: 0x%08x", 13, INL(dp, 13*8));
	cmn_err(CE_CONT, "CSR%d: 0x%08x", 14, INL(dp, 14*8));
	cmn_err(CE_CONT, "CSR%d: 0x%08x", 15, INL(dp, 15*8));
	cmn_err(CE_CONT, "CSR%d: 0x%08x", 16, INL(dp, 16*8+0*4));
	cmn_err(CE_CONT, "CSR%d: 0x%08x", 17, INL(dp, 16*8+1*4));
	cmn_err(CE_CONT, "CSR%d: 0x%08x", 18, INL(dp, 16*8+2*4));
	cmn_err(CE_CONT, "CSR%d: 0x%08x", 19, INL(dp, 16*8+3*4));
	cmn_err(CE_CONT, "CSR%d: 0x%08x", 20, INL(dp, 16*8+4*4));
	cmn_err(CE_CONT, "CSR%d: 0x%08x", 21, INL(dp, 16*8+5*4));
	cmn_err(CE_CONT, "CSR%d: 0x%08x", 22, INL(dp, 16*8+6*4));
	cmn_err(CE_CONT, "CSR%d: 0x%08x", 23, INL(dp, 16*8+7*4));
	cmn_err(CE_CONT, "CSR%d: 0x%08x", 24, INL(dp, 16*8+8*4));
	cmn_err(CE_CONT, "CSR%d: 0x%08x", 25, INL(dp, 16*8+9*4));
	cmn_err(CE_CONT, "CSR%d: 0x%08x", 26, INL(dp, 16*8+10*4));
	cmn_err(CE_CONT, "CSR%d: 0x%08x", 27, INL(dp, 16*8+11*4));
	cmn_err(CE_CONT, "CSR%d: 0x%08x", 28, INL(dp, 16*8+12*4));

	for (i=0; i<40; i++) {
		cmn_err(CE_CONT, "phy%d: 0x%04x", i, tu_mii_read(dp, i));
	}
	
}
#endif

static void
E 2
tu_start_chip(struct gem_dev *dp)
{
D 7
	struct tu_chip_state	*lp = (struct tu_chip_state *)dp->private;
E 7
I 7
D 28
	struct tu_dev	*lp = (struct tu_dev *)dp->private;
E 28
I 28
	struct tu_dev	*lp = dp->private;
E 28
E 7

D 2
	DPRINTF(2, (CE_CONT, "%sd: tu_start_chip: called", dp->name));
E 2
I 2
D 6
	DPRINTF(2, (CE_CONT, "!%sd: tu_start_chip: called", dp->name));
E 6
I 6
D 10
	DPRINTF(2, (CE_CONT, "!%s: tu_start_chip: called", dp->name));
E 10
I 10
D 28
	DPRINTF(2, (CE_CONT, "!%s: tu_start_chip called: nar:%b csr6: %b",
		dp->name, lp->nar, CSR6BITS, INL(dp, NAR), CSR6BITS));
E 28
I 28
	DPRINTF(1, (CE_CONT, "!%s: %s called: nar:%b csr6: %b",
	    dp->name, __func__, lp->nar, CSR6BITS, INL(dp, NAR), CSR6BITS));
E 28
E 10
E 6
E 2

	/* enable interrupt */
D 7
	OUTL(dp, IER, OUR_INTR_BITS);
E 7
I 7
	lp->ier = OUR_INTR_BITS;
I 28

	switch (lp->hw_info->chip_type) {
	case CHIP_DM9102:
I 29
	case CHIP_DM9102A:
E 29
		/*
		 * XXX - don't mask TDU because DM9102 sometimes doesn't
		 * raise TCI bit
		 */
		lp->ier |= SR_TDU;
		break;
	}
E 28
I 17
D 29
#ifdef GEM_CONFIG_POLLING
E 17
I 16
D 28
	if (lp->timer_resolution != 0) {
E 28
I 28
	if (lp->timer_resolution) {
E 29
I 29

#ifdef CONFIG_POLLING
	if (lp->hw_info->timer_resolution) {
E 29
E 28
		lp->ier |= SR_GPTT;
	}
I 17
#endif
E 17
E 16
	if ((dp->misc_flag & GEM_NOINTR) == 0) {
		OUTL(dp, IER, lp->ier);
	}
E 7

I 7
D 9
#if 1
	if (lp->hw_info->chip_type == CHIP_DM9102 &&
	    lp->pci_revid == DM9102A_E3) {
		/* disable autonegotiation mode */
		dp->mii_state = MII_STATE_RESETTING;
		dp->mii_timer = dp->gc.gc_mii_reset_timeout;
		GEM_MII_WRITE(dp, MII_CONTROL, 0);
		lp->bmcr = 0;
	}
#endif
E 9
I 9
D 10
	mutex_exit(&dp->xmitlock);
	tu_set_rx_filter(dp);
	mutex_enter(&dp->xmitlock);
E 10
E 9
D 11

E 11
E 7
D 10
	/* Kick TX and send setup frame */
D 2
#ifdef SANITY
	lp->nar = INL(dp, NAR);
#endif
E 2
	lp->nar |= NAR_ST;
	OUTL(dp, NAR, lp->nar);
I 2
	drv_usecwait(5);
E 2

E 10
D 9
	mutex_exit(&dp->xmitlock);
	tu_set_rx_filter(dp);
	mutex_enter(&dp->xmitlock);

E 9
	/* Kick Rx */
D 2
#ifdef SANITY
	lp->nar = INL(dp, NAR);
#endif
E 2
	lp->nar |= NAR_SR;
D 10
	OUTL(dp, NAR, lp->nar);
I 2
	drv_usecwait(5);
E 10
I 10
	UPDATE_NAR(dp, lp->nar);
I 20

	return (GEM_SUCCESS);
E 20
E 10
E 2
}

D 17
static void
E 17
I 17
static int
E 17
tu_stop_chip(struct gem_dev *dp)
{
D 7
	struct tu_chip_state *lp = (struct tu_chip_state *)dp->private;
E 7
I 7
D 28
	struct tu_dev *lp = (struct tu_dev *)dp->private;
E 28
I 28
	struct tu_dev *lp = dp->private;
E 28
E 7

I 6
D 28
	DPRINTF(2, (CE_CONT, "!%s: tu_stop_chip: called", dp->name));
E 28
I 28
D 29
	DPRINTF(1, (CE_CONT, "!%s: %s: called", dp->name, __func__));
E 29
I 29
	DPRINTF(1, (CE_CONT, "!%s: %s: called, chip_type:%x",
	    dp->name, __func__, lp->hw_info->chip_type));
E 29
E 28

E 6
	/* Disable interrupts by clearing the interrupt mask */
D 7
	OUTL(dp, IER, 0);
E 7
I 7
D 28
	lp->ier = 0;
	OUTL(dp, IER, lp->ier);
I 9
	OUTL(dp, SR, 0xffffffff);
E 28
I 28
	/* XXX - don't clear SR and soft copy of IER */
	OUTL(dp, IER, 0);
E 28
E 9
E 7
D 2
#ifdef notdef
	if (lp->hw_info->chip_type == CHIP_AN983) {
		OUTL(dp, IER2_AN, 0);
	}
#endif
E 2
I 2

E 2
D 28
	/* Stop the chip's Tx and Rx processes. */
I 10
	tu_freeze_chip(dp, NAR_ST | NAR_SR);
E 10
D 6
	OUTL(dp, PAR, 0);
E 6
I 6
	lp->nar &= ~(NAR_ST | NAR_SR);
D 9
	OUTL(dp, NAR, lp->nar);
	drv_usecwait(5);
E 9
I 9
D 10
	tu_freeze_chip(dp);
E 10

E 28
D 17
	/* reset tx and rx descriptor ptr */
	tu_reset_chip(dp);
E 17
I 17
D 29
	/* wait until the dma engine stops */
	if (dp->speed == GEM_SPD_10) {
		drv_usecwait(2000);
	} else {
		drv_usecwait(200);
	}
E 17
I 10

E 29
I 11
D 28
	/* synchronize csr6 with lp->nar */
E 11
	lp->nar |= NAR_PR;
	lp->nar &= ~(NAR_ST | NAR_SR | NAR_MM);
E 28
I 28
	/* Stop the chip's Tx and Rx processes. */
	(void) tu_freeze_chip(dp, NAR_ST | NAR_SR);

I 29
	switch (lp->hw_info->chip_type) {
	case CHIP_DM9102:
	case CHIP_DM9102A:
		(void) tu_reset_chip(dp);
	}

E 29
	if (lp->nar & (NAR_ST | NAR_SR)) {
		/* we failed to stop tx and rx */
I 29
		DPRINTF(-2, (CE_CONT,
		    "!%s: %s: failed to stop tx and rx, nar:%b",
		    dp->name, __func__, lp->nar, CSR6BITS));
E 29
		(void) tu_reset_chip(dp);
		lp->nar &= ~(NAR_ST | NAR_SR);
	}
D 29

E 29
I 29
#if 0
E 29
	/* mask rx filter bits, and synchronize csr6 with lp->nar */
	lp->nar &= ~(NAR_PB | NAR_PR | NAR_MM);
E 28
	UPDATE_NAR(dp, lp->nar);
I 17
D 29

E 29
I 29
#endif
E 29
	return (GEM_SUCCESS);
E 17
E 10
E 9
E 6
}

I 16
D 28
kmutex_t	tu_srom_lock;
E 28
I 28
static kmutex_t	tu_srom_lock;
E 28

E 16
D 17
static uint16_t
D 16
tu_read_eeprom(struct gem_dev *dp, uint_t offset)
E 16
I 16
tu_read_eeprom_shared(ddi_acc_handle_t ha, void *base, int offset, int abits)
E 17
I 17
D 28
#define	EEPROM_DELAY(ha, spr)	{ddi_get32(ha, spr); ddi_get32(ha, spr);}
E 28
I 28
#define	EEPROM_DELAY(ha, spr)	{ddi_get32(ha, spr); ddi_get32(ha, spr); }
E 28
#define	EE93C46_READ	6

static int
tu_check_eeprom_size_shared(struct gem_dev *dp, ddi_acc_handle_t ha, void *base)
E 17
E 16
{
I 16
D 28
	uint32_t	*spr = (uint32_t *)((caddr_t)base + SPR);
E 28
I 28
	uint32_t	*spr = (void *)((caddr_t)base + SPR);
E 28
E 16
	int		i;
D 9
	uint16_t	ret;
E 9
I 9
D 17
	uint_t		ret;
E 17
I 17
	int		abits;
E 17
E 9
	uint32_t	chip_select;
	uint32_t	di;
	uint32_t	cfga_saved;
I 3
D 7
	struct tu_chip_state	*lp = (struct tu_chip_state *)dp->private;
E 7
I 7
D 16
	struct tu_dev	*lp = (struct tu_dev *)dp->private;
E 16
E 7
E 3

D 16
#define	EEPROM_DELAY(dp)	{INL(dp, SPR); INL(dp, SPR);}
E 16
I 16
D 17
#define	EEPROM_DELAY(ha, spr)	{ddi_get32(ha, spr); ddi_get32(ha, spr);}
E 16
#define	EE93C46_READ	6
E 17
I 17
	mutex_enter(&tu_srom_lock);
E 17

I 17
D 28
	/* ensure de-assert chip select and di, clock*/
E 28
I 28
	/* ensure de-assert chip select and di, clock */
E 28
	chip_select = SPR_SRC | SPR_SRS;
	ddi_put32(ha, spr, chip_select);
	EEPROM_DELAY(ha, spr);

	/* assert chip select */
	chip_select |= SPR_SCS;
	ddi_put32(ha, spr, chip_select);
	EEPROM_DELAY(ha, spr);

D 28
	/* send command*/
E 28
I 28
	/* send command */
E 28
	for (i = 5 - 1; i >= 0; i--) {
		/* send 1 bit */
		di = ((EE93C46_READ >> i) & 1) << SPR_SDI_SHIFT;

		ddi_put32(ha, spr, chip_select | di);
		EEPROM_DELAY(ha, spr);

		ddi_put32(ha, spr, chip_select | di | SPR_SCLK);
		EEPROM_DELAY(ha, spr);
	}

	/* send addresss (max 16bits) */
	for (abits = 0; abits < 16; abits++) {
		ddi_put32(ha, spr, chip_select);
		EEPROM_DELAY(ha, spr);

		if (((ddi_get32(ha, spr) >> SPR_SDO_SHIFT) & 1) == 0) {
			/* srom responded */
			DPRINTF(4, (CE_CONT,
D 28
			"!%s: %s: srom responded after sending %d address bits",
				dp->name, __func__, abits));
E 28
I 28
			    "!%s: %s: srom responded"
			    " after sending %d address bits",
			    dp->name, __func__, abits));
E 28
			break;
		}

		ddi_put32(ha, spr, chip_select | SPR_SCLK);
		EEPROM_DELAY(ha, spr);
	}

	/* get a 16bit value */
	for (i = 0; i < 16; i++) {
		/* Get 1 bit */
		ddi_put32(ha, spr, chip_select | SPR_SCLK);
		EEPROM_DELAY(ha, spr);

		ddi_put32(ha, spr, chip_select);
		EEPROM_DELAY(ha, spr);
	}

	/* negate chip_select */
	chip_select &= ~SPR_SCS;
	ddi_put32(ha, spr, chip_select);
	EEPROM_DELAY(ha, spr);
#if 0
	ddi_put32(ha, spr, chip_select | SPR_SCLK);
	EEPROM_DELAY(ha, spr);
#endif
	/* disable EEPROM access */
	ddi_put32(ha, spr, 0);

	mutex_exit(&tu_srom_lock);

	if (abits != 6 && abits != 8) {
		cmn_err(CE_WARN,
D 28
			"!%s: %s: srom responded after sending %d address bits",
				dp->name, __func__, abits);
E 28
I 28
		    "!%s: %s: srom responded after sending %d address bits",
		    dp->name, __func__, abits);
E 28
	}

	return ((abits == 6 || abits == 8) ? abits : 0);
}

static uint32_t
tu_read_eeprom_shared(
	struct gem_dev *dp,
	ddi_acc_handle_t ha, void *base, int offset, int abits)
{
D 28
	uint32_t	*spr = (uint32_t *)((caddr_t)base + SPR);
E 28
I 28
	uint32_t	*spr = (void *)((caddr_t)base + SPR);
E 28
	int		i;
	uint_t		ret = 0;
	uint32_t	chip_select;
	uint32_t	di;
	uint32_t	cfga_saved;


E 17
I 16
	mutex_enter(&tu_srom_lock);

E 16
	/* ensure de-assert chip select */
	chip_select = SPR_SRC | SPR_SRS;
D 16
	OUTL(dp, SPR, chip_select);
I 11
	EEPROM_DELAY(dp);
E 16
I 16
	ddi_put32(ha, spr, chip_select);
	EEPROM_DELAY(ha, spr);
E 16
E 11

	/* assert chip select */
	chip_select |= SPR_SCS;
D 16
	OUTL(dp, SPR, chip_select);
	EEPROM_DELAY(dp);
E 16
I 16
	ddi_put32(ha, spr, chip_select);
	EEPROM_DELAY(ha, spr);
E 16

	/* make a read command for eeprom */
D 3
	offset = (offset & 0x3f) | (EE93C46_READ << 6);
E 3
I 3
D 10
	offset = (offset & ((1 << lp->ee_abits) - 1)) | (EE93C46_READ << lp->ee_abits);
E 10
I 10
D 16
	offset = (offset & ((1 << lp->ee_abits) - 1)) 
	       | (EE93C46_READ << lp->ee_abits);
E 16
I 16
D 28
	offset = (offset & ((1 << abits) - 1)) 
	       | (EE93C46_READ << abits);
E 28
I 28
	offset = (offset & ((1 << abits) - 1)) | (EE93C46_READ << abits);
E 28
E 16
E 10
E 3

D 3
	for (i = 10; i >= 0; i--) {
E 3
I 3
D 16
	for (i = lp->ee_abits + 5 - 1; i >= 0; i--) {
E 16
I 16
	for (i = abits + 5 - 1; i >= 0; i--) {
E 16
E 3
		/* send 1 bit */
		di = ((offset >> i) & 1) << SPR_SDI_SHIFT;

D 16
		OUTL(dp, SPR, chip_select | di);
		EEPROM_DELAY(dp);
E 16
I 16
		ddi_put32(ha, spr, chip_select | di);
		EEPROM_DELAY(ha, spr);
E 16

D 16
		OUTL(dp, SPR, chip_select | di | SPR_SCLK);
		EEPROM_DELAY(dp);
E 16
I 16
		ddi_put32(ha, spr, chip_select | di | SPR_SCLK);
		EEPROM_DELAY(ha, spr);
I 17
		ret = (ret << 1) | ((ddi_get32(ha, spr) >> SPR_SDO_SHIFT) & 1);
E 17
E 16
	}

D 16
	OUTL(dp, SPR, chip_select);
	EEPROM_DELAY(dp);
E 16
I 16
	ddi_put32(ha, spr, chip_select);
	EEPROM_DELAY(ha, spr);
E 16

	/* get the reply and construct a 16bit value */
D 9
	ret = 0;
E 9
	for (i = 0; i < 16; i++) {
		/* Get 1 bit */
D 16
		OUTL(dp, SPR, chip_select | SPR_SCLK);
		EEPROM_DELAY(dp);
E 16
I 16
		ddi_put32(ha, spr, chip_select | SPR_SCLK);
		EEPROM_DELAY(ha, spr);
E 16

D 10
		ret = (ret << 1)
		    | ((INL(dp, SPR) >> SPR_SDO_SHIFT) & 1);

E 10
I 10
D 16
		ret = (ret << 1) | ((INL(dp, SPR) >> SPR_SDO_SHIFT) & 1);
E 10
		OUTL(dp, SPR, chip_select);
		EEPROM_DELAY(dp);
E 16
I 16
		ret = (ret << 1) | ((ddi_get32(ha, spr) >> SPR_SDO_SHIFT) & 1);
		ddi_put32(ha, spr, chip_select);
		EEPROM_DELAY(ha, spr);
E 16
	}

	/* negate chip_select */
D 11
	OUTL(dp, SPR, 0);
E 11
I 11
	chip_select &= ~SPR_SCS;
D 16
	OUTL(dp, SPR, chip_select);
E 11
	EEPROM_DELAY(dp);
I 11
	OUTL(dp, SPR, chip_select | SPR_SCLK);
	EEPROM_DELAY(dp);
E 16
I 16
	ddi_put32(ha, spr, chip_select);
	EEPROM_DELAY(ha, spr);
I 17
#if 0
E 17
	ddi_put32(ha, spr, chip_select | SPR_SCLK);
	EEPROM_DELAY(ha, spr);
E 16
E 11
D 17

E 17
I 17
#endif
E 17
I 11
	/* disable EEPROM access */
D 16
	OUTL(dp, SPR, 0);
E 16
I 16
	ddi_put32(ha, spr, 0);
I 17
	EEPROM_DELAY(ha, spr);
E 17
E 16

I 16
	mutex_exit(&tu_srom_lock);

E 16
E 11
D 17
	return ret;
E 17
I 17
	DPRINTF(4, (CE_CONT, "!%s: ret:0x%08x", __func__, ret));

	return (ret);
E 17
}

I 8
static uint16_t
I 16
tu_read_eeprom(struct gem_dev *dp, int offset)
{
D 28
	struct tu_dev	*lp = (struct tu_dev *)dp->private;
E 28
I 28
	struct tu_dev	*lp = dp->private;
E 28

D 17
	return tu_read_eeprom_shared(dp->regs_handle,
					dp->base_addr, offset, lp->ee_abits);
E 17
I 17
D 28
	return (tu_read_eeprom_shared(dp, dp->regs_handle,
					dp->base_addr, offset, lp->ee_abits));
E 28
I 28
	return (tu_read_eeprom_shared(dp,
	    dp->regs_handle, dp->base_addr, offset, lp->ee_abits));
E 28
E 17
}

static uint16_t
E 16
tu_read_eeprom_pnic(struct gem_dev *dp, uint_t offset)
{
	int		i;
	uint32_t	ret;
D 28
	struct tu_dev	*lp = (struct tu_dev *)dp->private;
E 28
I 28
	struct tu_dev	*lp = dp->private;
E 28

	/* make a read command for eeprom */
D 9
	offset = (offset & ((1 << lp->ee_abits) - 1)) | (EE93C46_READ << lp->ee_abits);

	i = 10;
	while ((INL(dp, PNIC_EECSR/*CSR19*/) & EECSR_BUSY) && --i >= 0) {
E 9
I 9
D 28
	offset = (offset & ((1 << lp->ee_abits) - 1)) |
		 (EE93C46_READ << lp->ee_abits);
E 28
I 28
	offset = (offset & ((1 << lp->ee_abits) - 1))
	    | (EE93C46_READ << lp->ee_abits);
E 28
D 17
#ifdef notdef
E 17
I 17
#ifdef NEVER
E 17
D 11
	/* Following code cause reading data corrupted */
E 11
I 11
	/* XXX - following code corrupts the read data */
E 11
	i = 100;
D 28
	while ((INL(dp, PNIC_EECSR) & EECSR_BUSY) != 0 &&
		--i >= 0) {
E 28
I 28
	while ((INL(dp, PNIC_EECSR) & EECSR_BUSY) &&
	    --i >= 0) {
E 28
E 9
		drv_usecwait(10);
	}
D 9
	if (i < 0) {
		cmn_err(CE_WARN, "%s: tu_read_eeprom: not ready",
		dp->name);
		return 0;
	}

E 9
I 9
#endif
E 9
	OUTL(dp, PNIC_EECSR, offset);

D 9
	i = 10;
	while (((ret = INL(dp, PNIC_EEDATA/*CSR9*/)) & EEDATA_BUSY) && --i >= 0) {
E 9
I 9
D 16
	i = 100;
	while (((ret = INL(dp, PNIC_EEDATA)) & EEDATA_BUSY) != 0) {
		if (--i < 0) {
E 16
I 16
D 28
	for (i = 0; ((ret = INL(dp, PNIC_EEDATA)) & EEDATA_BUSY) != 0; i++) {
E 28
I 28
	for (i = 0; ((ret = INL(dp, PNIC_EEDATA)) & EEDATA_BUSY); i++) {
E 28
		if (i > 100) {
E 16
			/* time out */
D 16
			break;
E 16
I 16
D 28
			cmn_err(CE_WARN, "%s: %s: not ready",
				dp->name, __func__);
E 28
I 28
			cmn_err(CE_WARN, "!%s: %s: not ready",
			    dp->name, __func__);
E 28
D 17
			return 0xffff;
E 17
I 17
			return (0xffff);
E 17
E 16
		}
E 9
		drv_usecwait(10);
	}
D 16
	if (i < 0) {
		cmn_err(CE_WARN, "%s: tu_read_eeprom: not ready",
		dp->name);
		return 0;
	}
E 16

D 17
	return ret;
E 17
I 17
	return (ret);
E 17
}
E 8
D 17
#ifdef DEBUG
E 17
I 17

D 26
static uint16_t
E 26
I 26
static void
E 26
tu_read_eeprom_xircom(struct gem_dev *dp)
{
	int			i;
D 28
	struct tu_dev		*lp = (struct tu_dev *)dp->private;
E 28
I 28
	struct tu_dev		*lp = dp->private;
E 28
#define	CSR10	0x50

	OUTL(dp, SPR, 1 << 12);	/* csr9 */
	for (i = 0; i < 0x100; i++) {
		OUTL(dp, CSR10, 0x100 + i);
		lp->srom_data[i] = INL(dp, SPR);
	}
	OUTL(dp, SPR, 0);	/* csr9 */
}

#ifdef DEBUG_LEVEL
E 17
static void
D 2
tu_eeprom_dump(struct gem_dev *dp)
E 2
I 2
tu_eeprom_dump(struct gem_dev *dp, int size)
E 2
{
I 16
D 28
	struct tu_dev	*lp = (struct tu_dev *)dp->private;
E 28
I 28
	struct tu_dev	*lp = dp->private;
E 28
E 16
	int		i;
D 2
	uint16_t	prom[0x10];
E 2

D 2
	for (i = 0; i < 0x10; i++) {
		prom[i] = tu_read_eeprom(dp, i);
	}

E 2
	cmn_err(CE_CONT, "!%s: eeprom dump:", dp->name);
D 2
	for (i = 0; i < 0x10; i += 4) {
E 2
I 2
D 16
	for (i = 0; i < size; i += 4) {
E 2
D 3
		cmn_err(CE_CONT, "!0x%02x: 0x%04x 0x%04x 0x%04x 0x%04x", 
D 2
			i, prom[i], prom[i + 1], prom[i + 2], prom[i + 3]);
E 2
I 2
			i, tu_read_eeprom(dp, i), tu_read_eeprom(dp, i + 1),
E 3
I 3
		cmn_err(CE_CONT, "!0x%03x: 0x%04x 0x%04x 0x%04x 0x%04x", 
			i*2, tu_read_eeprom(dp, i), tu_read_eeprom(dp, i + 1),
E 3
			tu_read_eeprom(dp, i + 2), tu_read_eeprom(dp, i + 3));
E 16
I 16
	for (i = 0; i < size; i += 8) {
		cmn_err(CE_CONT,
D 28
			"!%03x: %02x %02x %02x %02x %02x %02x %02x %02x", 
			i,
			lp->srom_data[i + 0], lp->srom_data[i + 1],
			lp->srom_data[i + 2], lp->srom_data[i + 3],
			lp->srom_data[i + 4], lp->srom_data[i + 5],
			lp->srom_data[i + 6], lp->srom_data[i + 7]);
E 28
I 28
		    "!%03x: %02x %02x %02x %02x %02x %02x %02x %02x",
		    i,
		    lp->srom_data[i + 0], lp->srom_data[i + 1],
		    lp->srom_data[i + 2], lp->srom_data[i + 3],
		    lp->srom_data[i + 4], lp->srom_data[i + 5],
		    lp->srom_data[i + 6], lp->srom_data[i + 7]);
E 28
E 16
E 2
	}
}
#endif /* DEBUG */

I 16
#ifdef CONFIG_MULTIPORT
static boolean_t
D 17
tu_read_eeprom_in_first_port(struct gem_dev *dp)
E 17
I 17
tu_read_eeprom_at_first_port(struct gem_dev *dp)
E 17
{
D 28
	struct tu_dev		*lp = (struct tu_dev *)dp->private;
E 28
I 28
	struct tu_dev		*lp = dp->private;
E 28
	dev_info_t		*dip;
	ddi_acc_handle_t	ha;
	void			*base;
	int			i;
D 17
	uint16_t		anded;
	uint16_t		ored;
E 17
	uint16_t		vid;
	uint16_t		did;
	uint16_t		val;
	int			cont_cnt;
	uint8_t			*cp;
E 16
I 9

I 16
	/*
	 * first, we ensure it is multiport card.
	 */

	/* Are all childlen device of my parent same ? */
	for (dip = ddi_get_child(ddi_get_parent(dp->dip));
D 28
			dip != NULL;
					dip = ddi_get_next_sibling(dip)) {
E 28
I 28
	    dip != NULL;
	    dip = ddi_get_next_sibling(dip)) {
E 28

D 17
		vid = gem_getprop(DDI_DEV_T_ANY, dip,
E 17
I 17
		vid = ddi_prop_get_int(DDI_DEV_T_ANY, dip,
E 17
D 28
					DDI_PROP_DONTPASS, "vendor-id", -1);
E 28
I 28
		    DDI_PROP_DONTPASS, "vendor-id", -1);
E 28
D 17
		did = gem_getprop(DDI_DEV_T_ANY, dip,
E 17
I 17
		did = ddi_prop_get_int(DDI_DEV_T_ANY, dip,
E 17
D 28
					DDI_PROP_DONTPASS, "device-id", -1);
E 28
I 28
		    DDI_PROP_DONTPASS, "device-id", -1);
E 28

		DPRINTF(0, (CE_CONT, "!%s: %s: trying vid:%04x did:%04x",
D 28
			dp->name, __func__, vid, did));
E 28
I 28
		    dp->name, __func__, vid, did));
E 28

		if (vid != lp->hw_info->venid || did != lp->hw_info->devid) {
			/* not multiport */
#ifdef DEBUG_MULTIPORT
			continue;
#else
D 17
			return FALSE;
E 17
I 17
D 26
			return (FALSE);
E 26
I 26
			return (B_FALSE);
E 26
E 17
#endif
		}

		/* map regs */
D 28
		if (ddi_regs_map_setup(dip, 1/*IO space*/, (caddr_t *)&base,
			0, 0, &tu_dev_attr, &ha)) {
			cmn_err(CE_WARN, "%s: %s: ddi_regs_map_setup failed",
				dp->name, __func__);
E 28
I 28
		if (ddi_regs_map_setup(dip,
D 29
		    1 /* IO space */, (caddr_t *)&base,
E 29
I 29
		    1 /* IO space */, (void *)&base,
E 29
		    0, 0, &tu_dev_attr, &ha)) {
			cmn_err(CE_WARN, "!%s: %s: ddi_regs_map_setup failed",
			    dp->name, __func__);
E 28
			continue;
		}

		/* read entire eeprom */
D 17
		anded = 0xffff;
		ored  = 0x0000;
		for (i = 0; i < SROM_SIZE/2; i++) {
			val = tu_read_eeprom_shared(ha, base, i, SROM_ABITS);
			lp->srom_data[i*2    ] = val;
			lp->srom_data[i*2 + 1] = val >> 8;
			anded &= val;
			ored  |= val;
E 17
I 17
		lp->ee_abits = tu_check_eeprom_size_shared(dp, ha, base);

		if (lp->ee_abits > 0) {
			for (i = 0; i < (1 << lp->ee_abits); i++) {
D 28
				val = tu_read_eeprom_shared(
						dp, ha, base, i, lp->ee_abits);
				lp->srom_data[i*2]     = (uint8_t) val;
				lp->srom_data[i*2 + 1] = (uint8_t) (val >> 8);
E 28
I 28
				val = tu_read_eeprom_shared(dp,
				    ha, base, i, lp->ee_abits);
				lp->srom_data[i*2] = (uint8_t)val;
				lp->srom_data[i*2 + 1] = (uint8_t)(val >> 8);
E 28
			}
E 17
		}

		/* ummap regs */
D 28
		 ddi_regs_map_free(&ha);
E 28
I 28
		ddi_regs_map_free(&ha);
E 28

D 17
		if (anded != 0xffff && ored != 0x0000) {
			/* srom exits for this device */
E 17
I 17
		if (lp->ee_abits > 0) {
			/* srom exists for first port of the device */
E 17
			goto found;
		}
	}
D 17
	return FALSE;
E 17
I 17
	/* no srom for the device */
D 26
	return (FALSE);
E 26
I 26
	return (B_FALSE);
E 26
E 17

found:
	/*
	 * find controller index for me
	 */
	DPRINTF(0, (CE_CONT, "!\t\tsrom found, dip0:%p, dip:%p",
D 28
				dip, dp->dip));
E 28
I 28
	    dip, dp->dip));
E 28
	cp = lp->srom_data;
	lp->dip0 = dip;
	cont_cnt = cp[19];
	if (cont_cnt > 16) {
		/* corrupted eeprom data */
D 17
		return FALSE;
E 17
I 17
D 26
		return (FALSE);
E 26
I 26
		return (B_FALSE);
E 26
E 17
	}

D 17
	lp->dev_index = 0;
E 17
I 17
D 28
	/* find device index for me to fix mac address later.*/
E 28
I 28
	/* find device index for me to fix mac address later. */
E 28
E 17
	for (i = 0; i < cont_cnt; i++) {
D 28
		DPRINTF(0, (CE_CONT, 
			"!index:%d device number: 0x%02x, offset: 0x%04x",
			i, cp[26+i*3], LEWORD(&cp[27+i*3])));
E 28
I 28
		DPRINTF(0, (CE_CONT,
		    "!index:%d device number: 0x%02x, offset: 0x%04x",
		    i, cp[26+i*3], LEWORD(&cp[27+i*3])));
E 28
		if (cp[26+i*3] == lp->dev_num) {
			/* found */
			lp->dev_index = i;
			break;
		}
		if (cp[26+i*3] == 0) {
			/* end of device list */
			break;
		}
	}

D 17
	/* fix mac address for me */
	cp[25] += lp->dev_index;

	return TRUE;
E 17
I 17
D 26
	return (TRUE);
E 26
I 26
	return (B_TRUE);
E 26
E 17
}
#endif /* CONFIG_MULTIPORT */

E 16
E 9
static int
tu_attach_chip(struct gem_dev *dp)
{
	int		i;
D 16
	uint_t		val;
E 16
I 16
	uint32_t	val;
E 16
I 14
D 17
	int		*valp;
E 17
E 14
D 2
	int		ether_offset;
E 2
D 7
	struct tu_chip_state *lp = (struct tu_chip_state *)dp->private;
E 7
I 7
D 28
	struct tu_dev	*lp = (struct tu_dev *)dp->private;
E 28
I 28
	struct tu_dev	*lp = dp->private;
E 28
E 7
D 3
	uint8_t		mac[ETHERADDRL];
E 3
I 3
D 17
	uint8_t		*mac;
E 17
	int		offset;
I 29
	uint8_t	zeros[ETHERADDRL] = {0, 0, 0, 0, 0, 0};
E 29
I 9
D 17
	char		propname[32];
E 9
E 3
D 16

E 16
I 16
	uint16_t	anded;
	uint16_t	ored;
E 17
#ifdef CONFIG_MULTIPORT
D 26
	boolean_t	multiport = FALSE;
E 26
I 26
	boolean_t	multiport = B_FALSE;
E 26
	uint16_t	svid = 0;
	uint16_t	sdid = 0;
#endif
	/*
D 17
	 * Read mac addres
E 17
I 17
	 * Read srom and a factory mac address.
E 17
	 */
E 16
I 3
D 17
	/* assume eeprom is 93C46: 1024 bit (64 word) serial rom */
D 16
	lp->ee_abits = 6;
E 16
I 16
	lp->ee_abits = SROM_ABITS;
E 17
I 17
D 28
	bzero(&lp->srom_data[0], sizeof(lp->srom_data));
E 28
I 28
	bzero(&lp->srom_data[0], sizeof (lp->srom_data));
E 28

	/* assume eeprom is 93C46, 1024 bit (64 word) serial rom */
	lp->ee_abits = 6;
E 17
E 16
I 9
D 26
	lp->have_srom = FALSE;
E 26
I 26
	lp->have_srom = B_FALSE;
E 26
I 17
	offset = 0;
E 17
E 9
D 16
	mac = dp->dev_addr.ether_addr_octet;
E 16

E 3
D 2
	ether_offset = 8;
	if (lp->hw_info->chip_type == CHIP_DM9102) {
		ether_offset = 10*2;
	}

E 2
D 9
	if (!gem_get_mac_addr_conf(dp)) {
D 2
		if (lp->hw_info->chip_type == CHIP_AN983) {
			for (i = 0; i < ETHERADDRL; i += 2) {
				val = tu_read_eeprom(dp, (8 + i)>>1);
				mac[i]   = val;
				mac[i+1] = val>>8;
			}
E 2
I 2
		if (lp->hw_info->chip_type == CHIP_COMET ||
		    lp->hw_info->chip_type == CHIP_CENTAUR) {
			val = INL(dp, PAR0_AN);
			mac[0] = val;
			mac[1] = val>>8;
			mac[2] = val>>16;
			mac[3] = val>>24;
			val = INL(dp, PAR1_AN);
			mac[4] = val;
			mac[5] = val>>8;
E 9
I 9
D 16
	if (lp->hw_info->chip_type == CHIP_CENTAUR) {
E 16
I 16
D 17
	mac = dp->dev_addr.ether_addr_octet;
E 17
	switch (lp->hw_info->chip_type) {
	case CHIP_CENTAUR:
E 16
D 29
		val = INL(dp, PAR0_AN);
D 17
		mac[0] = val;
		mac[1] = val>>8;
		mac[2] = val>>16;
		mac[3] = val>>24;
		val = INL(dp, PAR1_AN);
		mac[4] = val;
		mac[5] = val>>8;
E 17
I 17
D 28
		lp->srom_data[0] = (uint8_t) val;
		lp->srom_data[1] = (uint8_t) (val >> 8);
		lp->srom_data[2] = (uint8_t) (val >> 16);
		lp->srom_data[3] = (uint8_t) (val >> 24);
E 28
I 28
		lp->srom_data[0] = (uint8_t)val;
		lp->srom_data[1] = (uint8_t)(val >> 8);
		lp->srom_data[2] = (uint8_t)(val >> 16);
		lp->srom_data[3] = (uint8_t)(val >> 24);
E 28
		val = INL(dp, PAR0_AN + 4);
D 28
		lp->srom_data[4] = (uint8_t) val;
		lp->srom_data[5] = (uint8_t) (val >> 8);
E 28
I 28
		lp->srom_data[4] = (uint8_t)val;
		lp->srom_data[5] = (uint8_t)(val >> 8);
E 29
I 29
		offset = 8;
		lp->ee_abits = tu_check_eeprom_size_shared(dp,
		    dp->regs_handle, dp->base_addr);
		if (lp->ee_abits > 0) {
			/* we have a local srom, read the whole of it. */
			for (i = 0; i < (1 << lp->ee_abits); i++) {
				val = tu_read_eeprom(dp, i);
				lp->srom_data[i*2 + 0] = (uint8_t)val;
				lp->srom_data[i*2 + 1] = (uint8_t)(val >> 8);
			}
		}
E 29
E 28
E 17
D 16
	}
	else if (lp->hw_info->chip_type == CHIP_LC82C168) {
E 16
I 16
		break;

D 17
	case CHIP_LC82C168:
E 16
		lp->ee_abits = 8;
		for (i = 0; i < ETHERADDRL; i += 2) {
			val = tu_read_eeprom_pnic(dp, i>>1);
			mac[i]   = (uint8_t) (val >> 8);
			mac[i+1] = (uint8_t) val;
E 9
E 2
		}
I 8
D 9
		if (lp->hw_info->chip_type == CHIP_LC82C168) {
			lp->ee_abits = 8;
			for (i = 0; i < ETHERADDRL; i += 2) {
				val = tu_read_eeprom_pnic(dp, (offset + i)>>1);
				mac[i]   = (uint8_t) (val >> 8);
				mac[i+1] = (uint8_t) val;
			}
E 9
I 9
D 16
	}
	else if (lp->hw_info->chip_type == CHIP_CONEXANT) {
E 16
I 16
		break;
E 17
I 17
	case CHIP_XIRCOM:
		/* Xircom have a 128word srom for cis data. */
		lp->ee_abits = 7;
		tu_read_eeprom_xircom(dp);
E 17

D 17
	case CHIP_CONEXANT:
E 16
		/*
		 * Conexant RS7112 chips use
		 *  4096 bit (256word) serial rom
		 */
		lp->ee_abits = 8;
D 16
		offset = 0x19a;
E 16
I 16
		offset = 0x19a;		/* in byte */
E 16

		for (i = 0; i < ETHERADDRL; i += 2) {
			val = tu_read_eeprom(dp, (offset + i)>>1);
			mac[i]   = (uint8_t) val;
			mac[i+1] = (uint8_t) (val >> 8);
E 17
I 17
		/* parse cis data to find a factory mac-address */
		for (i = 0;
D 28
			i < MAX_SROM_SIZE - (4 + ETHERADDRL) ||
			lp->srom_data[i+1] == 0;
					i += lp->srom_data[i+1] + 2) {
			if (lp->srom_data[i+0] == 0x22 &&
			    lp->srom_data[i+2] == 0x04 &&
			    lp->srom_data[i+3] == ETHERADDRL) {
E 28
I 28
		    i < MAX_SROM_SIZE - (4 + ETHERADDRL) ||
		    lp->srom_data[i + 1] == 0;
		    i += lp->srom_data[i + 1] + 2) {
			if (lp->srom_data[i + 0] == 0x22 &&
			    lp->srom_data[i + 2] == 0x04 &&
			    lp->srom_data[i + 3] == ETHERADDRL) {
E 28
				/* we found mac address in the CIS tupples. */
				break;
			}
E 17
E 9
		}
I 17
		offset = i + 4;
E 17
E 8
D 2
		else if (lp->hw_info->chip_type == CHIP_DM9102) {
E 2
I 2
D 9
		else {
			/* DEC SROM format */
D 3
			/* DM9102, MX987xx */
E 3
I 3
			offset = 0;
			for (i = 0; i < 8; i += 2) {
				if (tu_read_eeprom(dp, i >> 1) !=
				    tu_read_eeprom(dp, (i + 0x10) >> 1)) {
					offset = 0x14;
					break;
				}
			}
E 9
I 9
D 16
	}
	else {
E 16
I 16
		break;

D 17
	default:
E 16
		/* read eeprom */
D 16
		for (i = 0; i < 128; i++) {
E 16
I 16
		anded = 0xffff;
		ored  = 0x0000;
		for (i = 0; i < SROM_SIZE/2; i++) {
E 16
			val = tu_read_eeprom(dp, i);
I 16
#ifdef DEBUG_MULTIPORT
			val = 0xffff;
#endif
E 16
			lp->srom_data[i*2    ] = val;
			lp->srom_data[i*2 + 1] = val >> 8;
I 16
			anded &= val;
			ored  |= val;
E 17
I 17
	case CHIP_21140:
	case CHIP_21142:
		/* first of all, check if local srom exist. */
D 28
		lp->ee_abits = tu_check_eeprom_size_shared(
					dp, dp->regs_handle, dp->base_addr);
E 28
I 28
		lp->ee_abits = tu_check_eeprom_size_shared(dp,
		    dp->regs_handle, dp->base_addr);
E 28
		if (lp->ee_abits > 0) {
D 28
			/* we gave a local srom, read whole of it. */
E 28
I 28
			/* we have a local srom, read the whole of it. */
E 28
			for (i = 0; i < (1 << lp->ee_abits); i++) {
				val = tu_read_eeprom(dp, i);
D 28
				lp->srom_data[i*2]     = (uint8_t) val;
				lp->srom_data[i*2 + 1] = (uint8_t) (val >> 8);
E 28
I 28
				lp->srom_data[i*2 + 0] = (uint8_t)val;
				lp->srom_data[i*2 + 1] = (uint8_t)(val >> 8);
E 28
			}
E 17
E 16
D 28
		}
I 17
		else {
E 28
I 28
		} else {
E 28
E 17
E 9
D 16

E 16
I 16
#ifdef CONFIG_MULTIPORT
D 17
		if (anded == 0xffff || ored == 0x0000) {
			/* no srom, try multiport configuration */
			multiport = tu_read_eeprom_in_first_port(dp);
		}
E 17
I 17
			/*
			 * No local srom detected,
			 * try multiport configuration.
			 */
			multiport = tu_read_eeprom_at_first_port(dp);
#else
D 28
			cmn_err(CE_WARN, "%s: no srom", dp->name);
E 28
I 28
			cmn_err(CE_WARN, "!%s: no srom", dp->name);
E 28
E 17
#endif
E 16
D 9
			/* DM9102, MX987xx use 93c46 */
E 9
I 9
D 17
		offset = 0;
E 17
I 17
		}

		/* validate srom format */
E 17
D 16
		if (bcmp(&lp->srom_data[0], &lp->srom_data[0x10],
							ETHERADDRL) != 0) {
E 16
I 16
D 28
		if (bcmp(&lp->srom_data[0], &lp->srom_data[0x10], 8) != 0) {
E 28
I 28
		if (bcmp(&lp->srom_data[0], &lp->srom_data[0x10], 8)) {
E 28
			uint8_t	*cp = &lp->srom_data[0];

E 16
			/* DEC SROM format, ID block is not zero */
D 26
			lp->have_srom = TRUE;
E 26
I 26
			lp->have_srom = B_TRUE;
E 26
			offset = 0x14;
D 16
		}
E 16
E 9

D 9
		    	if (lp->hw_info->chip_type == CHIP_CONEXANT) {
				/*
				 * Conexant RS7112 chips use
				 *  4096 bit (256word) serial rom
				 */
				lp->ee_abits = 8;
D 4
				if (tu_read_eeprom(dp, 0x198 >> 1) == 0x0604) {
					offset = 0x19a;
				}
E 4
I 4
				offset = 0x19a;
E 4
			}
E 9
D 16
#if DEBUG_LEVEL > 4
D 9
			tu_eeprom_dump(dp, 256);
E 9
I 9
		tu_eeprom_dump(dp, 256);
E 16
I 16
			svid = LEWORD(&cp[0]);
			sdid = LEWORD(&cp[2]);
#ifdef DEBUG_MULTIPORT
			svid = VID_COGENT;
E 16
E 9
#endif
I 16
		}
E 16
E 3
E 2
D 9
			for (i = 0; i < ETHERADDRL; i += 2) {
D 3
				val = tu_read_eeprom(dp, (20 + i)>>1);
				mac[i]   = val;
				mac[i+1] = val>>8;
E 3
I 3
				val = tu_read_eeprom(dp, (offset + i)>>1);
				mac[i]   = (uint8_t) val;
				mac[i+1] = (uint8_t) (val >> 8);
E 3
			}
		}
D 2
		else if (lp->hw_info->chip_type == CHIP_MX98715) {
			int	base;
			base = tu_read_eeprom(dp, 0x70/2);
			for (i = 0; i < ETHERADDRL; i += 2) {
				val = tu_read_eeprom(dp, (base + i)>>1);
				mac[i]   = val;
				mac[i+1] = val>>8;
			}
		}
E 2

E 9
I 9
D 17
		bcopy(&lp->srom_data[offset], mac, ETHERADDRL);
E 17
I 17
		break;

	case CHIP_LC82C168:
		lp->ee_abits = 8;
D 28
		for (i = 0; i < ETHERADDRL; i+=2) {
E 28
I 28
		for (i = 0; i < ETHERADDRL; i += 2) {
E 28
			val = tu_read_eeprom_pnic(dp, i/2);
D 28
			lp->srom_data[i + 0] = (uint8_t) (val >> 8);
			lp->srom_data[i + 1] = (uint8_t) val;
E 28
I 28
			lp->srom_data[i + 0] = (uint8_t)(val >> 8);
			lp->srom_data[i + 1] = (uint8_t)val;
E 28
		}
		break;

	default:
		/* for clones without DEC format srom. */
		switch (lp->hw_info->chip_type) {
		case CHIP_CONEXANT:
			/*
			 * Conexant RS7112 chips use
			 *  4096 bit (256word) serial rom
			 */
			lp->ee_abits = 8;
			offset = 0x19a;		/* in byte */
			break;
		}

		/* read the entire srom */
		for (i = 0; i < (1 << lp->ee_abits); i++) {
			val = tu_read_eeprom(dp, i);
D 28
			lp->srom_data[i*2]     = (uint8_t) val;
			lp->srom_data[i*2 + 1] = (uint8_t) (val >> 8);
E 28
I 28
			lp->srom_data[i*2] = (uint8_t)val;
			lp->srom_data[i*2 + 1] = (uint8_t)(val >> 8);
E 28
		}

D 28
		if (bcmp(&lp->srom_data[0], &lp->srom_data[0x10], 8) != 0) {
E 28
I 28
		if (bcmp(&lp->srom_data[0], &lp->srom_data[0x10], 8)) {
			/* DEC SROM format, ID block is not zero */
			lp->have_srom = B_TRUE;
E 28
			offset = 0x14;
		}
		break;
	}
E 17
I 16
#if DEBUG_LEVEL > 0
D 17
		tu_eeprom_dump(dp, 1 << (lp->ee_abits + 1));
E 17
I 17
	tu_eeprom_dump(dp, 1 << (lp->ee_abits + 1));
E 17
#endif
E 16
E 9
D 3
		for (i = 0; i < ETHERADDRL; i++) {
			dp->dev_addr.ether_addr_octet[i] = mac[i];
		}
E 3
D 17
	}

E 17
I 17
	bcopy(&lp->srom_data[offset],
D 28
		&dp->dev_addr.ether_addr_octet[0], ETHERADDRL);
E 28
I 28
	    &dp->dev_addr.ether_addr_octet[0], ETHERADDRL);
E 28
#ifdef CONFIG_MULTIPORT
	/* fix mac address for me */
	dp->dev_addr.ether_addr_octet[ETHERADDRL-1] += lp->dev_index;
#endif
E 17
I 9
	gem_get_mac_addr_conf(dp);

I 29
	if (bcmp(dp->dev_addr.ether_addr_octet, zeros, ETHERADDRL) == 0) {
		gem_generate_macaddr(dp, dp->dev_addr.ether_addr_octet);
	}

E 29
I 16
D 28
	if (multiport 
E 28
D 17
#ifdef notdef
		/* tu driver in linux doen't check vendor ID. */
E 17
I 17
#ifdef NEVER
D 28
		/* linux tulip driver doesn't check vendor ID. */
E 17
		&& svid == VID_COGENT
E 28
I 28
	/* linux tulip driver doesn't check vendor ID. VID_COGENT */
E 28
#endif
D 28
	) {
E 28
I 28
	if (multiport) {
E 28
		ddi_iblock_cookie_t	c;
		int			ret;

		/*
		 * Workaround for multiport PCI cards with non-standard
		 * interrupt routing at pci-pci bridge in the pci add-on card.
		 */
#ifdef sun4u
		/*
		 * For sparc platforms:
		 * hack "interrupts" property so that the recommended
		 * interrupt routing at pci-pci bridge results in INT-A.
		 */
		val = (4 - (lp->dev_num % 4)) % 4 + 1;
		ret = ddi_prop_update_int_array(DDI_DEV_T_NONE, dp->dip,
D 28
				"interrupts", &val, 1);
E 28
I 28
		    "interrupts", &val, 1);
E 28
		if (ret != DDI_PROP_SUCCESS) {
			cmn_err(CE_WARN,
D 28
		"%s: error: %d, failed to update \"interrupts\" property",
				dp->name, ret);
E 28
I 28
			    "!%s: error: %d, failed to update"
			    " \"interrupts\" property",
			    dp->name, ret);
E 28
		}
		DPRINTF(0, (CE_CONT, "!%s: interrupts:%d",
D 28
				dp->name,
D 17
				ddi_getprop(DDI_DEV_T_ANY, dp->dip,
E 17
I 17
				ddi_prop_get_int(DDI_DEV_T_ANY, dp->dip,
E 17
					DDI_PROP_DONTPASS,
					"interrupts", -1)));
E 28
I 28
		    dp->name,
		    ddi_prop_get_int(DDI_DEV_T_ANY,
		    dp->dip, DDI_PROP_DONTPASS, "interrupts", -1)));
E 28
#endif
#ifdef i86pc
		/*
		 * For solaris9 x86 or previous:
		 * copy vec in intrspec from first port
		 */
		/* force to load vec into intrspec */
		ddi_get_iblock_cookie(dp->dip, 0, &c);
		ddi_get_iblock_cookie(lp->dip0, 0, &c);

D 28
		if (DEVI_PD(dp->dip) != NULL && DEVI_PD(lp->dip0) != NULL
		   && DEVI_PD(dp->dip)->par_intr != NULL
		   && DEVI_PD(lp->dip0)->par_intr != NULL) {
E 28
I 28
		if (DEVI_PD(dp->dip) != NULL && DEVI_PD(lp->dip0) != NULL &&
		    DEVI_PD(dp->dip)->par_intr != NULL &&
		    DEVI_PD(lp->dip0)->par_intr != NULL) {
E 28
			DEVI_PD(dp->dip)->par_intr[0].intrspec_vec =
D 28
				DEVI_PD(lp->dip0)->par_intr[0].intrspec_vec;
E 28
I 28
			    DEVI_PD(lp->dip0)->par_intr[0].intrspec_vec;
E 28
		}
#endif
	}

E 16
E 9
D 2
#ifdef notdef 
	tu_eeprom_dump(dp);
#endif
E 2
I 2
D 7
	/* Read initial value for NAR (CSR6) */
	lp->nar = INL(dp, NAR) & ~(NAR_ST | NAR_SR);
	lp->nar |= NAR_MBO;	/* bit 25: constant */
I 6
	if (lp->hw_info->chip_type == CHIP_21140) {
E 7
I 7
D 10
	/* initial value for NAR (CSR6) */
E 10
I 10
	/* Initial value for NAR (CSR6) is 10M HD */
E 10
D 9
	switch (lp->hw_info->chip_type) {
	default:
		lp->nar = INL(dp, NAR) & ~(NAR_ST | NAR_SR);
		lp->nar |= NAR_MBO;	/* bit 25: constant */
		/* fall through */	
	case CHIP_21140:
E 7
		lp->nar &=
		  ~((1<<28) | (1<<27) | (1<<26) | (1<<20) | (1<<16) | (1<<8));
I 7
		break;
E 9
I 9
	/* worked with 21140, AN983B, DM9102A */
D 10
	lp->nar = NAR_MBO;
E 9

E 10
D 9
	case CHIP_DM9102:
		lp->nar = NAR_SQE;
		break;
E 9
I 9
	/* bit21: Store and forward for Tx operations */
D 10
	/* bit15-14: Transmit threshold control */
	lp->nar |= NAR_SF;
#ifdef notdef
	UPDATE_NAR(dp, lp->nar);
#endif
	/* PHY emulation initialization */
E 10
I 10
D 11
	lp->nar = NAR_MBO | NAR_SF | NAR_PR;
	/* PHY emulation initialization for built-in NWAY */
E 10
	lp->bmsr = MII_STATUS_100_BASEX_FD
		 | MII_STATUS_100_BASEX
		 | MII_STATUS_10_FD
		 | MII_STATUS_10;
I 10
	if ((lp->hw_info->capability & CHIP_CAP_NWAY) != 0) {
		lp->bmsr |= MII_STATUS_CANAUTONEG;
E 11
I 11
D 17
	val = NAR_SF;
E 17

	switch (lp->hw_info->chip_type) {
D 29
	case CHIP_MX987XX:
E 29
I 29
	case CHIP_MX98713:
	case CHIP_MX98713A:
	case CHIP_MX98715:
	case CHIP_MX98725:
E 29
I 16
D 28
		if ((lp->pci_revid & 0xf0) == 0x00) {
			/* 98713 */
			dp->txthr = max(dp->txthr, ETHERMAX);
			break;
		}
		/* fall through */
E 28
E 16
	case CHIP_LC82C168:
	case CHIP_DM9102:
I 29
	case CHIP_DM9102A:
E 29
		dp->txthr = max(dp->txthr, 1024);
		break;

	case CHIP_LC82C115:
		dp->txthr = max(dp->txthr, ETHERMAX);
		break;
E 11
	}
E 10

I 11
	if (dp->txthr <= 128) {
		val = TR_128 << NAR_TR_SHIFT;
	} else if (dp->txthr <= 256) {
		val = TR_256 << NAR_TR_SHIFT;
	} else if (dp->txthr <= 512) {
		val = TR_512 << NAR_TR_SHIFT;
	} else if (dp->txthr <= 1024) {
		val = TR_1024 << NAR_TR_SHIFT;
I 14
	} else {
		val = NAR_SF;
E 14
	}
D 28
	lp->nar = NAR_MBO | val | NAR_PR;
D 16
#ifdef notdef
	switch (lp->hw_info->chip_type) {
	case CHIP_LC82C115:
		dp->txmaxdma = max(256, dp->txmaxdma);
		dp->rxmaxdma = max(256, dp->txmaxdma);
	}
#endif
I 14
	lp->rx_delay_pkts = 1;
E 14
E 11
	sprintf(propname, "%s-rx-delay", dp->name);
D 14
	lp->rx_delay_pkts = ddi_getprop(DDI_DEV_T_ANY, dp->dip,
				DDI_PROP_DONTPASS, propname, 1);
E 14
I 14
	if (ddi_prop_lookup_int_array(
		DDI_DEV_T_ANY, dp->dip, DDI_PROP_DONTPASS,
		propname, &valp, (uint_t *)&i) == DDI_PROP_SUCCESS) {
E 16
D 17

E 17
I 17
#if 0
E 17
D 16
		if (i == 1) {
			lp->rx_delay_pkts = valp[0];
		}
		ddi_prop_free(valp);
E 16
I 16
	/* XXX - workaround for MX98713 */
	if (MX98713(lp)) {
		dp->txmaxdma = 4;
		dp->rxmaxdma = 4;
E 16
	}
E 14
D 16
	if (lp->rx_delay_pkts < 1) {
		lp->rx_delay_pkts = 1;
E 9
E 7
	}
E 16
I 7
D 17

E 17
I 17
#endif
I 19
	switch (lp->hw_info->chip_type) {
	case CHIP_DM9102:
		dp->txmaxdma = max(dp->txmaxdma, 128);
		dp->rxmaxdma = max(dp->rxmaxdma, 128);
		break;
	}
E 28
I 28
	lp->nar = NAR_MBO | val;
E 28

E 19
E 17
I 11
D 28
	/* long packet is not supported */
E 28
I 28
D 29
	/* long packets are not supported */
E 28
	dp->mtu = min(ETHERMAX, dp->mtu);

E 29
I 14
D 28
	/* fix rx buffer length */
E 28
I 28
	/* increase rx buffer length for 4 byte alignment */
E 28
	dp->rx_buf_len = ROUNDUP2(dp->rx_buf_len, 4);

I 28
D 29
#ifdef GEM_CONFIG_POLLING
E 29
I 29
#ifdef CONFIG_POLLING
E 29
E 28
I 19
	dp->misc_flag |= GEM_POLL_RXONLY;
D 26
#ifdef CONFIG_VLAN
E 26
I 26
D 28
#ifdef GEM_CONFIG_VLAN
E 28
I 28
#endif
#ifdef GEM_CONFIG_GLDv3
E 28
E 26
	dp->misc_flag |= GEM_VLAN_SOFT;
#endif

E 19
E 14
E 11
E 7
E 6
D 9
	OUTL(dp, NAR, lp->nar);
	drv_usecwait(5);
E 9
I 9
	DPRINTF(2, (CE_CONT, "!%s: tu_attach_chip: done", dp->name));
E 9

I 16
D 29
#if defined(i86pc) && DEBUG_LEVEL > 1
E 29
I 29
#if defined(i86pc) && DEBUG_LEVEL > 2
E 29
{
	struct intrspec	*ispecp;

	cmn_err(CE_CONT, "!%s: parent_data nreg:%d, nintr:%d",
D 28
		dp->name,
		sparc_pd_getnreg(dp->dip), sparc_pd_getnintr(dp->dip));
E 28
I 28
	    dp->name, sparc_pd_getnreg(dp->dip), sparc_pd_getnintr(dp->dip));
E 28

	ispecp = DEVI_PD(dp->dip)->par_intr;
	if (ispecp != NULL) {
		for (i = 0; i < sparc_pd_getnintr(dp->dip); i++) {
			cmn_err(CE_CONT, "!%d: pri:%d vec:%d",
D 28
				i,
				ispecp[i].intrspec_pri,
				ispecp[i].intrspec_vec);
E 28
I 28
			    i,
			    ispecp[i].intrspec_pri,
			    ispecp[i].intrspec_vec);
E 28
		}
	}
}
#endif
E 16
I 3
D 9
	DPRINTF(2, (CE_CONT,
		"!%s: tu_attach_chip: done", dp->name));

E 9
E 3
E 2
D 17
	return 0;
E 17
I 17
	return (GEM_SUCCESS);
E 17
}

D 9

E 9
/*
 * Multicast hash calculation according to 21143 data sheet
 */
D 6
#define	CRC32_POLY	0xedb88320
#define	HASH_BITS	9

static uint_t
E 6
I 6
static uint32_t
E 6
tu_multicast_hash(struct gem_dev *dp, uint8_t *addr)
{
D 6
	int	idx;
	int	bit;
	u_int	data;
	u_int	crc = 0xffffffff;

	for (idx = 0; idx < ETHERADDRL; idx++) {
		for (data = *addr++, bit = 0; bit < 8; bit++, data >>= 1) {
			crc = (crc >> 1) ^ (((crc ^ data) & 1) ? CRC32_POLY : 0);
		}
	}
	return	crc & ((1 << HASH_BITS) - 1);
E 6
I 6
D 17
	return	gem_ether_crc_le(addr);
E 17
I 17
D 22
	return (gem_ether_crc_le(addr, ETHERADDRL));
E 22
I 22
	uint32_t	val;
D 28
	struct tu_dev	*lp = (struct tu_dev *)dp->private;
E 28
I 28
	struct tu_dev	*lp = dp->private;
E 28

	val = gem_ether_crc_le(addr, ETHERADDRL);

D 29
	switch (lp->hw_info->chip_type) {
	case CHIP_CENTAUR:
		val &= 64 - 1;
		break;
E 29
I 29
	val &= lp->hw_info->hash_bits - 1;
E 29

D 29
	case CHIP_XIRCOM:
E 29
I 29
	if (lp->hw_info->chip_type == CHIP_XIRCOM) {
E 29
		/* this comes from *bsd if_dc.c */
D 29
		val &= 512 - 1;
E 29
		if ((val & 0x180) == 0x180) {
			val = ((val & 0x0f) + (val & 0x70) * 3 + (14 << 4));
		} else {
			val = ((val & 0x1f) + ((val >> 1) & 0xf0) * 3
			    + (12 << 4));
		}
D 29
		break;

	case CHIP_LC82C115:
		/* PNIC II */
		val &= 128 - 1;
		break;

	case CHIP_MX987XX:
		if ((lp->pci_revid & 0xf0) == 0x20) {
			/* MX98715 */
			val &= 128 - 1;
			break;
		}
		/* fall down */
	default:
		val &= 512 -1;
		break;
E 29
	}
I 29

E 29
	return (val);
E 22
E 17
E 6
}

I 22
#define	HASH_MAC_COPY(d, s) {	\
	((uint16_t *)(d))[0] = ((uint16_t *)(s))[0];	\
	((uint16_t *)(d))[2] = ((uint16_t *)(s))[1];	\
	((uint16_t *)(d))[4] = ((uint16_t *)(s))[2];	\
}

D 28
#define HASH_OFFSET(val)	((((val) >> 4) << 2) + (((val) >> 3) & 1))
E 28
I 28
#define	HASH_OFFSET(val)	((((val) >> 4) << 2) + (((val) >> 3) & 1))
E 28

/*
 * Special rx_filter method for ADMtek chips.
 */
E 22
D 20
static void
E 20
I 20
static int
I 22
tu_set_rx_filter_admtek(struct gem_dev *dp)
{
	int		i;
	uint32_t	mode;
	uint64_t	hash;
D 24
	uint8_t		*m;
E 24
I 24
	uint8_t		*pa;
E 24
I 23
D 28
	static uint8_t	zeros[] = {0, 0, 0, 0, 0, 0};
E 23
	struct tu_dev	*lp = (struct tu_dev *)dp->private;
E 28
I 28
	uint32_t	txrx_state;
	static uint8_t	zeros[] = { 0, 0, 0, 0, 0, 0 };
	struct tu_dev	*lp = dp->private;
E 28

	DPRINTF(2, (CE_CONT,
D 28
	"!%s: %s: called active:%d nar:%b csr6: %b tail:%d",
		dp->name, __func__, dp->mac_active,
		lp->nar, CSR6BITS, INL(dp, NAR), CSR6BITS, dp->tx_desc_tail));
E 28
I 28
	    "!%s: %s: called active:%d nar:%b csr6: %b tail:%d",
	    dp->name, __func__, dp->mac_active,
	    lp->nar, CSR6BITS, INL(dp, NAR), CSR6BITS, dp->tx_desc_tail));
E 28
I 23

	/* my mac address */
D 24
	m = dp->cur_addr.ether_addr_octet;
E 24
I 24
	pa = dp->cur_addr.ether_addr_octet;
E 24

E 23
	/* clear hash table */
	hash = 0;

	/* pass bad packet */
	mode = NAR_PB;	/* pass bad packet */
#if DEBUG_LEVEL > 4
	mode |= NAR_PR;	/* use promiscous mode for debugging */
#endif

D 23
	if ((dp->rxmode & RXMODE_PROMISC) != 0) {
E 23
I 23
	if ((dp->rxmode & RXMODE_ENABLE) == 0) {
		mode = 0;
D 24
		m = zeros;
		goto x;
E 24
I 24
		pa = zeros;
E 24
D 28
	}
	else if ((dp->rxmode & RXMODE_PROMISC) != 0) {
E 28
I 28
	} else if (dp->rxmode & RXMODE_PROMISC) {
E 28
E 23
		/* promiscous mode */
		mode |= NAR_PR;
D 28
	}
	else if (dp->mc_count > 32 || (dp->rxmode & RXMODE_ALLMULTI) != 0) {
E 28
I 28
	} else if (dp->mc_count > 32 || (dp->rxmode & RXMODE_ALLMULTI)) {
E 28
		mode |= NAR_MM;	/* accept all muticast packets */
D 28
	}
	else {
E 28
I 28
	} else {
E 28
		/* make a 64 bit width multicast hash table */
		for (i = 0; i < dp->mc_count; i++) {
D 29
			hash |= 1ull << dp->mc_list[i].hash;
E 29
I 29
			hash |= 1ULL << dp->mc_list[i].hash;
E 29
		}
	}
D 23

E 23
I 23
D 24
x:
E 24
I 24

E 24
E 23
	/* stop rx for a while */
D 28
	tu_freeze_chip(dp, NAR_SR);
E 28
I 28
	txrx_state = tu_freeze_chip(dp, NAR_SR);
E 28

	/* set mac address */
D 23
	m = dp->cur_addr.ether_addr_octet;
E 23
D 24
	OUTL(dp, PAR0_AN, (m[3]<<24) | (m[2]<<16) | (m[1]<<8) | m[0]);
	OUTL(dp, PAR1_AN, (m[5]<<8) | m[4]);
E 24
I 24
D 29
	OUTL(dp, PAR0_AN, (pa[3]<<24) | (pa[2]<<16) | (pa[1]<<8) | pa[0]);
	OUTL(dp, PAR1_AN, (pa[5]<<8) | pa[4]);
E 29
I 29
	OUTL(dp, PAR0_AN, pa[3] << 24 | pa[2] << 16 | pa[1] << 8 | pa[0]);
	OUTL(dp, PAR1_AN, pa[5] << 8 | pa[4]);
E 29
E 24

	/* set hash table */
D 28
	OUTL(dp, MAR0_AN, (uint32_t) hash);
	OUTL(dp, MAR1_AN, (uint32_t) (hash >> 32));
E 28
I 28
	OUTL(dp, MAR0_AN, (uint32_t)hash);
	OUTL(dp, MAR1_AN, (uint32_t)(hash >> 32));
E 28

	/* update rx filter mode */
	lp->nar = (lp->nar & ~(NAR_PB | NAR_PR | NAR_MM)) | mode;
D 28
	UPDATE_NAR(dp, lp->nar & ~NAR_SR);
E 28
I 28
	UPDATE_NAR(dp, lp->nar);
E 28

D 28
	tu_restart_chip(dp);
E 28
I 28
	tu_restart_chip(dp, txrx_state);
E 28

	DPRINTF(1, (CE_CONT, "!%s: %s: mode:0x%b, hash:0x%llx",
D 28
		dp->name, __func__, mode, CSR6BITS, hash));
E 28
I 28
	    dp->name, __func__, mode, CSR6BITS, hash));
E 28

	return (GEM_SUCCESS);
}

static int
E 22
E 20
tu_set_rx_filter(struct gem_dev *dp)
{
	uint32_t	mode;
	int		i;
I 22
	int		ix;
	int		naddr;
E 22
D 24
	uint8_t		*m;
E 24
I 24
	uint8_t		*sf;
E 24
D 7
	struct tu_chip_state	*lp = (struct tu_chip_state *)dp->private;
E 7
I 7
D 22
	struct tu_dev	*lp = (struct tu_dev *)dp->private;
E 22
E 7
I 6
	int		hashtype;
D 22
	int		err;
E 22
I 22
D 29
	int		hashbits;
E 29
E 22
	int		val;
	mblk_t		*mp;
I 26
	uint8_t		*mac;
E 26
I 10
D 17
	int		xmitlock_owned;
E 17
E 10
D 22
	static  struct ether_addr	bcast = {
E 22
I 22
D 24
	static uint8_t	bcast[] = {
E 22
		0xff, 0xff, 0xff, 0xff, 0xff, 0xff
	};
E 24
I 24
D 28
	static uint8_t	bcast[] = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff};
I 26
	static uint8_t	zeros[] = {0, 0, 0, 0, 0, 0};
E 26
E 24
I 22
	struct tu_dev	*lp = (struct tu_dev *)dp->private;
E 28
I 28
	uint32_t	txrx_state;
	static uint8_t	bcast[] = { 0xff, 0xff, 0xff, 0xff, 0xff, 0xff };
	static uint8_t	zeros[] = { 0, 0, 0, 0, 0, 0 };
	struct tu_dev	*lp = dp->private;
E 28
E 22
E 6

D 2
	DPRINTF(2, (CE_CONT, "%sd: tu_set_rx_filter: called active:%d",
E 2
I 2
D 6
	DPRINTF(2, (CE_CONT, "!%sd: tu_set_rx_filter: called active:%d",
E 6
I 6
D 10
	DPRINTF(2, (CE_CONT, "!%s: tu_set_rx_filter: called active:%d",
E 6
E 2
			dp->name, dp->nic_active));

	if (!dp->nic_active) {
		return;
	}

E 10
I 10
D 28
	DPRINTF(2, (CE_CONT,
D 17
	"!%s: tu_set_rx_filter: called active:%d nar:%b csr6: %b tail:%d",
		dp->name, dp->nic_active,
E 17
I 17
	"!%s: %s: called active:%d nar:%b csr6: %b tail:%d",
		dp->name, __func__, dp->mac_active,
E 17
		lp->nar, CSR6BITS, INL(dp, NAR), CSR6BITS, dp->tx_desc_tail));
E 28
I 28
	DPRINTF(1, (CE_CONT,
	    "!%s: %s: called active:%d nar:%b csr6:%b tail:%d mode:%b",
	    dp->name, __func__, dp->mac_active,
	    lp->nar, CSR6BITS, INL(dp, NAR), CSR6BITS, dp->tx_desc_tail,
	    dp->rxmode, RXMODE_BITS));
E 28
I 21

D 22
#if DEBUG_LEVEL > 0
E 22
I 22
#if DEBUG_LEVEL > 1
E 22
	for (i = 0; i < dp->mc_count; i++) {
		cmn_err(CE_CONT,
D 28
		"!%s: adding mcast(%d) %02x:%02x:%02x:%02x:%02x:%02x, hash:%d",
			dp->name, i,
			dp->mc_list[i].addr.ether_addr_octet[0],
			dp->mc_list[i].addr.ether_addr_octet[1],
			dp->mc_list[i].addr.ether_addr_octet[2],
			dp->mc_list[i].addr.ether_addr_octet[3],
			dp->mc_list[i].addr.ether_addr_octet[4],
			dp->mc_list[i].addr.ether_addr_octet[5],
			tu_multicast_hash(dp,
D 22
				dp->mc_list[i].addr.ether_addr_octet) % 512);
E 22
I 22
				dp->mc_list[i].addr.ether_addr_octet));
E 28
I 28
		    "!%s: adding mcast(%d)"
		    " %02x:%02x:%02x:%02x:%02x:%02x, hash:%d",
		    dp->name, i,
		    dp->mc_list[i].addr.ether_addr_octet[0],
		    dp->mc_list[i].addr.ether_addr_octet[1],
		    dp->mc_list[i].addr.ether_addr_octet[2],
		    dp->mc_list[i].addr.ether_addr_octet[3],
		    dp->mc_list[i].addr.ether_addr_octet[4],
		    dp->mc_list[i].addr.ether_addr_octet[5],
		    tu_multicast_hash(dp,
		    dp->mc_list[i].addr.ether_addr_octet));
E 28
E 22
	}
#endif

E 21
E 10
D 6
	/* pass bad packet */
	mode = NAR_PB;
	if ((dp->rxmode & RXMODE_PROMISC) != 0) {
		mode |= NAR_PR;	/* promiscous */
	}

E 6
D 2
#ifdef SANITY
	lp->nar = INL(dp, NAR);
#endif
	if ((lp->nar & NAR_SR) != 0) {
E 2
I 2
D 7
	if ((lp->nar & (NAR_ST | NAR_SR)) != 0) {
E 7
I 7
D 9
	if ((lp->nar & NAR_SR) != 0) {
E 7
E 2
		/* temporary stop Rx engine */
D 2
		OUTL(dp, NAR, lp->nar & ~NAR_SR);
E 2
I 2
D 7
		OUTL(dp, NAR, lp->nar & ~(NAR_ST | NAR_SR));
E 7
I 7
		OUTL(dp, NAR, lp->nar & ~NAR_SR);
E 7
		drv_usecwait(5);
E 2
	}

E 9
I 6
	/* pass bad packet */
D 7
	mode = NAR_PB;
E 7
I 7
	mode = NAR_PB;	/* pass bad packet */
#if DEBUG_LEVEL > 4
	mode |= NAR_PR;	/* use promiscous mode for debugging */
#endif
E 7
D 22
	if ((dp->rxmode & RXMODE_PROMISC) != 0) {
		/* promiscous */
		mode |= NAR_PR;
		/*
		 * Don't optimize setup frame due to the first packet after
D 11
		 * reset, must be a setup frame.
E 11
I 11
		 * reset must be a setup frame.
E 11
		 */
	}
E 22

E 6
D 2
	if (lp->hw_info->chip_type == CHIP_AN983) {
E 2
I 2
D 9
	if (lp->hw_info->chip_type == CHIP_COMET ||
	    lp->hw_info->chip_type == CHIP_CENTAUR) {
E 9
I 9
D 22
	if (lp->hw_info->chip_type == CHIP_CENTAUR) {
E 9
E 2
D 6
		/* set mac address */
E 6
I 6
		/*
D 9
		 * Special case for ADMtek chips
E 9
I 9
		 * Special case for ADMtek chips.
E 9
		 */
E 6
		uint32_t	hash[2];
D 6
		int		val;
E 6

I 9
D 10
		/* stop rx and tx for a while */
		tu_freeze_chip(dp);
E 10
I 10
		/* stop rx for a while */
		tu_freeze_chip(dp, NAR_SR);
E 10

E 9
I 6
		/* set mac address */
E 6
D 16
		m = dp->dev_addr.ether_addr_octet;
E 16
I 16
		m = dp->cur_addr.ether_addr_octet;
E 16
		OUTL(dp, PAR0_AN, (m[3]<<24) | (m[2]<<16) | (m[1]<<8) | m[0]);
		OUTL(dp, PAR1_AN, (m[5]<<8) | m[4]);

I 6
		/* set multicast hash table */
E 6
		hash[0] = hash[1] = 0;
D 2
		if (dp->mc_count > 20 || (dp->rxmode & RXMODE_ALLMULTI) != 0) {
E 2
I 2
D 6
		if (dp->mc_count > 100 || (dp->rxmode & RXMODE_ALLMULTI) != 0) {
E 6
I 6
D 17
		if (dp->mc_count>64/2 || (dp->rxmode & RXMODE_ALLMULTI) != 0) {
E 17
I 17
		if (dp->mc_count > 32 || (dp->rxmode & RXMODE_ALLMULTI) != 0) {
E 17
			/* too many multicast addresses */
E 6
E 2
			mode |= NAR_MM;	/* all muticalst */
D 6
		} else {
			/* make multicast hash table */
E 6
I 6
		}
		else {
			/* make 64bit width multicast hash table */
E 6
			for (i = 0; i < dp->mc_count; i++) {
D 6
				val = dp->mc_list[i].hash & 0x3f;
E 6
I 6
				val = dp->mc_list[i].hash & (64 - 1);
E 6
				hash[val/32] |= 1 << (val % 32);
			}
		}
		OUTL(dp, MAR0_AN, hash[0]);
		OUTL(dp, MAR1_AN, hash[1]);
I 6
D 10
		goto x;
E 10
I 10

		lp->nar = (lp->nar & ~(NAR_PB | NAR_PR | NAR_MM)) | mode;
		UPDATE_NAR(dp, lp->nar & ~NAR_SR);
		tu_restart_chip(dp);

D 20
		return;
E 20
I 20
		return (GEM_SUCCESS);
E 20
E 10
E 6
	}
D 6
	else {
		int		hashtype;
		int		err;
		mblk_t		*mp;
		static  struct ether_addr	bcast = {
			0xff, 0xff, 0xff, 0xff, 0xff, 0xff
		};
E 6
D 17

#define	HASH_MAC_COPY(d, s)	\
{	\
E 17
I 17
#define	HASH_MAC_COPY(d, s) {	\
E 17
	((uint16_t *)(d))[0] = ((uint16_t *)(s))[0];	\
	((uint16_t *)(d))[2] = ((uint16_t *)(s))[1];	\
	((uint16_t *)(d))[4] = ((uint16_t *)(s))[2];	\
}
E 22
I 6
	/*
D 24
	 * 2114x style setup
E 24
I 24
	 * 2114x style setup:
E 24
	 * allocate a setup frame as a messages block
	 */
	if ((mp = allocb(SETUP_FRAME_SIZE, BPRI_MED)) == NULL) {
D 28
		cmn_err(CE_WARN,
D 20
			"%s: tu_set_rx_filter failed to allocate setup frame",
			dp->name);
D 10
		goto x;
E 10
I 10
		return;
E 20
I 20
			"%s: %s failed to allocate setup frame",
			dp->name, __func__);
E 28
I 28
		cmn_err(CE_WARN, "!%s: %s failed to allocate setup frame",
		    dp->name, __func__);
E 28
		return (GEM_FAILURE);
E 20
E 10
	}
	bzero(mp->b_rptr, SETUP_FRAME_SIZE);
	mp->b_wptr = mp->b_rptr + SETUP_FRAME_SIZE;
D 17

E 17
I 17
	mp->b_next = NULL;
D 22
#ifdef SANITY
	hashtype = 0;
#endif
E 22
I 22
D 24
	m  = mp->b_rptr;
E 24
I 24
	sf = mp->b_rptr;
E 24

	ix = 0;
	naddr = 16;
	hashtype = SETUP_PERFECT;

D 29
	hashbits = 512;
	if ((lp->hw_info->chip_type == CHIP_MX987XX &&
D 28
			   (lp->pci_revid & 0xf0) == 0x20) ||
	     lp->hw_info->chip_type == CHIP_LC82C115) {
E 28
I 28
	    (lp->pci_revid & 0xf0) == 0x20) ||
	    lp->hw_info->chip_type == CHIP_LC82C115) {
E 28
		/* MX98715, PNIC II */
		hashbits = 128;
	}

E 29
I 26
	mac = dp->cur_addr.ether_addr_octet;

E 26
D 23
	if ((dp->rxmode & RXMODE_PROMISC) != 0) {
E 23
I 23
	if ((dp->rxmode & RXMODE_ENABLE) == 0) {
D 24
		mode = 0;
		goto x;
E 24
I 24
		/* send a setup frame in which all entries are 0:0:0:0:0:0. */
D 28

		/* XXX - changing PB bit made LC82C115 hang. */
		/* mode = 0; */
E 28
I 28
		mode = 0;
E 28
I 26
		mac = zeros;
E 26
		goto set_rx_mode;
E 24
D 28
	}
D 26
	else if ((dp->rxmode & RXMODE_PROMISC) != 0) {
E 23
		/* promiscous */
E 26
I 26
	else if (dp->rxmode & RXMODE_PROMISC) {
E 28
I 28
	} else if (dp->rxmode & RXMODE_PROMISC) {
E 28
		/* promiscuous */
E 26
		mode |= NAR_PR;
		/*
		 * Don't optimize setup frame due to the first packet after
		 * reset must be a setup frame.
		 */
D 28
	}
	else if (dp->mc_count > hashbits / 2 ||
D 26
				(dp->rxmode & RXMODE_ALLMULTI) != 0) {
E 26
I 26
		(dp->rxmode & RXMODE_ALLMULTI)) {
E 28
I 28
D 29
	} else if (dp->mc_count > hashbits / 2 ||
E 29
I 29
	} else if (dp->mc_count > lp->hw_info->hash_bits / 2 ||
E 29
	    (dp->rxmode & RXMODE_ALLMULTI)) {
E 28
E 26
		mode |= NAR_MM;	/* all multicalst */
D 28
	}
E 28
E 22
E 17
D 16
#ifndef HASH_FILTERING_TEST
E 16
I 16
#ifndef TEST_HASH_FILTERING
E 16
D 13
	if (dp->mc_count <= 14) {
E 13
I 13
D 22
	if (dp->mc_count <= 14 && (dp->rxmode & RXMODE_ALLMULTI) == 0) {
E 22
I 22
D 28
	else if (dp->mc_count <= 14) {
E 28
I 28
	} else if (dp->mc_count <= 14) {
E 28
E 22
E 13
E 6
		/*
D 6
		 * Allocate Setup Frame as a messages block
E 6
I 6
		 * Use perfect match filtering
E 6
		 */
D 6
		if ((mp = allocb(SETUP_FRAME_SIZE, BPRI_MED)) == NULL) {
			goto x;
E 6
I 6
		/* add multicast addresses */
		for (i = 0; i < dp->mc_count; i++) {
D 22
			HASH_MAC_COPY(&mp->b_rptr[i*2*ETHERADDRL],
E 22
I 22
			HASH_MAC_COPY(&mp->b_rptr[ix*2*ETHERADDRL],
E 22
D 28
				dp->mc_list[i].addr.ether_addr_octet);
E 28
I 28
			    dp->mc_list[i].addr.ether_addr_octet);
E 28
I 22
			ix++;
E 22
E 6
		}
D 6
		bzero(mp->b_rptr, SETUP_FRAME_SIZE);
		mp->b_wptr = mp->b_rptr + SETUP_FRAME_SIZE;
E 6
I 6
D 22
		/* add my physical address */
		HASH_MAC_COPY(&mp->b_rptr[i*2*ETHERADDRL],
D 16
				dp->dev_addr.ether_addr_octet);
E 16
I 16
				dp->cur_addr.ether_addr_octet);
E 16
		i++; /* next */
E 6

D 6
#ifdef HASHONLY_SUPPORT
		if () {
		} else
#endif
		if (dp->mc_count <= 14 ) {
			/*
			 * Use perfect match filtering
			 */
			for (i = 0; i < dp->mc_count; i++) {
				HASH_MAC_COPY(&mp->b_rptr[i*2*ETHERADDRL],
					dp->mc_list[i].addr.ether_addr_octet);
			}
E 6
I 6
		/* add broadcast address */
		for (; i < 16; i++) {
E 6
			HASH_MAC_COPY(&mp->b_rptr[i*2*ETHERADDRL],
D 6
					dp->dev_addr.ether_addr_octet);
			i++;
E 6
I 6
				&bcast.ether_addr_octet);
		}
		hashtype = SETUP_PERFECT;
# if DEBUG_LEVEL > 4
D 11
		/* dump setup frame */
E 11
I 11
D 21
		/* dump the contentes of the setup frame */
E 21
I 21
		/* dump the contents of the setup frame */
E 21
E 11
		for (i = 0; i < 16*3; i++) {
			cmn_err(CE_CONT, "0x%08x", ((uint32_t *)mp->b_rptr)[i]);
		}
# endif
	} else
E 22
I 22
D 28
	}
E 28
E 22
D 16
#endif /* !HASH_FILTERING_TEST */
E 16
I 16
#endif /* !TEST_HASH_FILTERING */
I 17
D 22
#ifdef CHIP_XIRCOM
	if (lp->hw_info->chip_type == CHIP_XIRCOM) {
		/* special treatment for xircom chipset */
		/* set my physical address */
		HASH_MAC_COPY(mp->b_rptr, dp->cur_addr.ether_addr_octet);

		/* add broadcast address */
		for (i = 1; i < 3; i++) {
			HASH_MAC_COPY(&mp->b_rptr[i*2*ETHERADDRL],
				&bcast.ether_addr_octet);
		}
		mode |= NAR_MM;	/* all multicalst */

		hashtype = SETUP_HASH;
	} else
#endif
E 17
E 16
	{
		int	hashbits;
E 6

E 22
I 22
D 28
	else {
E 28
I 28
	} else {
E 28
E 22
D 6
			for (; i < 16; i++) {
				HASH_MAC_COPY(&mp->b_rptr[i*2*ETHERADDRL],
					&bcast.ether_addr_octet);
			}
			hashtype = SETUP_PERFECT;
#ifdef notdef
			/* dump setupframe */
			for (i = 0; i < 16*3; i++) {
D 2
				cmn_err(CE_CONT, "0x%08x", ((uint32_t *)mp->b_rptr)[i]);
E 2
I 2
				cmn_err(CE_CONT,
					"0x%08x", ((uint32_t *)mp->b_rptr)[i]);
E 2
			}
#endif
		} else {
			/*
			 * Use hash filtering with one physcal address.
			 */
I 2
#ifdef notyet
E 2
			uint8_t	*hash = (uint8_t *) mp->b_rptr;
			int		val;
			uint32_t	hashbits;
E 6
I 6
		/*
D 26
		 * Use imperfect hash filtering with one physcal address.
E 26
I 26
		 * Use imperfect hash filtering with one physical address.
E 26
		 */
D 22
		hashbits = 512;
D 11
		if (lp->hw_info->chip_type == CHIP_MX98715 &&
E 11
I 11
D 21
		if (lp->hw_info->chip_type == CHIP_MX987XX &&
E 11
		   (lp->pci_revid & 0xf0) == 0x20) {
D 10
			/* how about Line-On chips */
E 10
I 10
			/* MX98715 */
E 21
I 21
		if ((lp->hw_info->chip_type == CHIP_MX987XX &&
				   (lp->pci_revid & 0xf0) == 0x20) ||
		     lp->hw_info->chip_type == CHIP_LC82C115) {
			/* MX98715, PNIC II */
E 21
E 10
			hashbits = 128;
E 22
I 22
		hashtype = SETUP_HASH;
		if (lp->hw_info->chip_type == CHIP_XIRCOM) {
			/*
D 24
			 * xircom's hash format has four entries for
E 24
I 24
			 * xircom's hash format also has four entries for
E 24
D 28
			 * perfect matching including my address.
E 28
I 28
			 * perfect match including my address.
E 28
			 */
			naddr = 4;
		} else {
			/* specify index for my address */
			ix = 13;
D 26
			/* avoid to filled with broadcast address */
E 26
I 26

			/*
D 28
			 * avoid that unused entries are filled with
E 28
I 28
			 * avoid unused entries to be filled with
E 28
			 * broadcast address
			 */
E 26
			naddr = 14;
E 22
		}
E 6

D 2
			if (dp->mc_count > 20 ||
E 2
I 2
D 6
			if (dp->mc_count > 100 ||
E 2
			   (dp->rxmode & RXMODE_ALLMULTI) != 0) {
D 2
				/* too many multicast addresses */
E 2
I 2
				/* Use all-multicast mode */
E 2
				mode |= NAR_MM;	/* all muticalst */
E 6
I 6
D 22
		if (dp->mc_count > hashbits/2 ||
		   (dp->rxmode & RXMODE_ALLMULTI) != 0) {
			/* Use all-multicast mode */
			mode |= NAR_MM;	/* all multicalst */
E 22
I 22
		/* make a hash table */
		for (i = 0; i < dp->mc_count; i++) {
			val = dp->mc_list[i].hash;
D 24
			m[HASH_OFFSET(val)] |= 1 << (val % 8);
E 24
I 24
			sf[HASH_OFFSET(val)] |= 1 << (val % 8);
E 24
E 22
		}
D 22
		else if (dp->mc_count > 0) {
D 11
#ifdef USE_MULTICAST_HASHTBL
E 11
			int	ix;
E 22

D 22
			for (i = 0; i < dp->mc_count; i++) {
				val = dp->mc_list[i].hash & (hashbits - 1);
				ix = val / 8;
				mp->b_rptr[(ix/2)*4 + (ix&1)] |= 1 << (val % 8);
E 6
D 2
#ifdef notdef
				for (i = 0; i < 64; i++) {
					hash[i] = 0xff;
				}
#endif
E 2
			}
E 22
I 22
		switch (lp->hw_info->chip_type) {
		case CHIP_XIRCOM:
I 26
			/* no need add an entry for broadcast address */
E 26
			break;
E 22
D 6
			else {
				hashbits = 512;
D 2
				if (lp->hw_info->chip_type == CHIP_MX98715) {
E 2
I 2
				if (lp->hw_info->chip_type == CHIP_MX98715 &&
				   (lp->hw_info->pci_revid & 0xf0) == 0x20) {
I 3
					/* how about Line-On chips */
E 3
E 2
					hashbits = 128;
				}
D 2
				bzero(hash, hashbits/8);
E 2
				for (i = 0; i < dp->mc_count; i++) {
					val = dp->mc_list[i].hash &
								(hashbits - 1);
					hash[val/8] |= 1 << (val % 8);
				}
			}
E 6
I 6

I 22
		default:
E 22
D 24
			/* add hash entry for broadcast address */
E 24
I 24
			/* need a hash entry for broadcast address */
E 24
D 17
			val = GEM_MULTICAST_HASH(dp, bcast.ether_addr_octet)
E 17
I 17
D 22
			val = tu_multicast_hash(dp, bcast.ether_addr_octet)
E 17
				& (hashbits - 1);
			ix = val / 8;
			mp->b_rptr[(ix/2)*4 + (ix&1)] |= 1 << (val % 8);

			DPRINTF(3, (CE_CONT, "!%s: hash for broacast: 0x%x",
				dp->name, val));
E 22
I 22
			val = tu_multicast_hash(dp, bcast);
D 24
			m[HASH_OFFSET(val)] |= 1 << (val % 8);
E 24
I 24
			sf[HASH_OFFSET(val)] |= 1 << (val % 8);
E 24
E 22
E 6
I 2
D 11
#else
			mode |= NAR_MM;	/* use all muticalst */
#endif
E 11
E 2
D 6
			HASH_MAC_COPY(&mp->b_rptr[13*2*ETHERADDRL],
				dp->dev_addr.ether_addr_octet);
			hashtype = SETUP_HASH;
E 6
		}
I 6
D 22
		/* add my physical address */
		HASH_MAC_COPY(&mp->b_rptr[13*2*ETHERADDRL],
D 16
			dp->dev_addr.ether_addr_octet);
E 16
I 16
			dp->cur_addr.ether_addr_octet);
E 16
		hashtype = SETUP_HASH;
E 22
	}
E 6

I 22
D 24
	/* fill with broadcast address */
E 24
I 24
	/* fill the rest entries except the last with broadcast address */
E 24
	for (; ix < naddr - 1; ix++) {
D 24
		HASH_MAC_COPY(&m[ix*2*ETHERADDRL], bcast);
E 24
I 24
		HASH_MAC_COPY(&sf[ix*2*ETHERADDRL], bcast);
E 24
	}

	/* add my physical address */
D 24
	/* XXX - it must be the last entry */
E 24
I 24
	/* XXX - it must be the last entry for hash format */
E 24
	ASSERT(ix == naddr - 1);
D 24
	HASH_MAC_COPY(&m[ix*2*ETHERADDRL], dp->cur_addr.ether_addr_octet);
E 24
I 24
	HASH_MAC_COPY(&sf[ix*2*ETHERADDRL], dp->cur_addr.ether_addr_octet);
E 24

D 28
# if DEBUG_LEVEL > 4
E 28
I 28
#if DEBUG_LEVEL > 4
E 28
	/* dump the contents of the setup frame */
	for (i = 0; i < 16*3; i++) {
D 24
		cmn_err(CE_CONT, "0x%08x", ((uint32_t *)mp->b_rptr)[i]);
E 24
I 24
D 28
		cmn_err(CE_CONT, "0x%08x", ((uint32_t *) sf)[i]);
E 28
I 28
		cmn_err(CE_CONT, "!0x%08x", ((uint32_t *)sf)[i]);
E 28
E 24
	}
D 28
# endif
E 28
I 28
#endif
E 28

E 22
I 11
	/*
	 * set rx mode
	 */
I 23
D 24
x:
E 24
I 24
set_rx_mode:
E 24
E 23
E 11
I 10
D 22
	if ((lp->nar & (NAR_PB | NAR_PR | NAR_MM)) != mode) {
E 22
I 22
D 26
	if (lp->hw_info->chip_type == CHIP_XIRCOM) {
E 26
I 26
	if ((lp->nar & (NAR_PB | NAR_PR | NAR_MM)) != mode) {
D 28
		boolean_t	restart_rx;
E 28
I 28
		txrx_state = tu_freeze_chip(dp, NAR_SR);
E 28
D 29

E 29
D 28
		/* need to change rx mode */
		switch (lp->hw_info->chip_type) {
		case CHIP_XIRCOM:
		case CHIP_ULI526X:
			/* don't stop rx */
			restart_rx = B_FALSE;
			break;
	
		default:
			/* stop rx for a while  (required for 98715) */
			tu_freeze_chip(dp, NAR_SR);
			restart_rx = B_TRUE;
		}

E 26
		lp->nar = (lp->nar & ~(NAR_PB | NAR_PR | NAR_MM)) | mode;
E 28
I 28
		lp->nar &= ~(NAR_PB | NAR_PR | NAR_MM);
		lp->nar |= mode;
E 28
		UPDATE_NAR(dp, lp->nar);
D 26
	}
	else if ((lp->nar & (NAR_PB | NAR_PR | NAR_MM)) != mode) {
E 22
D 11
		/*
		 * set rx mode
		 */
		lp->nar = (lp->nar & ~(NAR_PB | NAR_PR | NAR_MM)) | mode;

E 11
		/* stop rx for a while  (required for 98715) */
		tu_freeze_chip(dp, NAR_SR);
E 26
D 29

E 29
I 11
D 26
		lp->nar = (lp->nar & ~(NAR_PB | NAR_PR | NAR_MM)) | mode;
E 11
		UPDATE_NAR(dp, lp->nar & ~NAR_SR);
I 22

E 22
		tu_restart_chip(dp);
E 26
I 26
D 28
		if (restart_rx) {
			tu_restart_chip(dp);
		}
E 28
I 28
		tu_restart_chip(dp, txrx_state);
		DPRINTF(2, (CE_CONT,
		    "%s: %s: updating csr6:%b",
		    dp->name, __func__, lp->nar, CSR6BITS));
E 28
E 26
	}
D 16

E 16
I 16
D 17
#ifdef notdef
E 16
	if ((xmitlock_owned = mutex_owned(&dp->xmitlock)) == 0) {
		mutex_enter(&dp->xmitlock);
	}
E 10
D 6
		err = gem_send_common(dp->macinfo, mp, TRUE, hashtype);
		if (err != GLD_SUCCESS) {
			cmn_err(CE_WARN,
E 6
I 6
D 16
	err = gem_send_common(dp->macinfo, mp, TRUE, hashtype);
E 16
I 16
#endif
	err = gem_send_common(dp, mp, 0, hashtype);
#ifdef notdef
E 16
I 10
	if (xmitlock_owned == 0) {
		mutex_exit(&dp->xmitlock);
	}
E 10
D 16
	if (err != GLD_SUCCESS) {
E 16
I 16
#endif
	if (err != GLD_SUCCESS && err != -2) {
E 17
I 17

D 26
	if (gem_send_common(dp, mp, hashtype) != NULL) {
E 17
E 16
		cmn_err(CE_WARN,
E 6
D 9
			"%s: tu_set_rx_filter: failed to send setup frame: %d",
E 9
I 9
D 22
			"%s: tu_set_rx_filter: failed to send a setupframe: %d",
E 9
			dp->name, err);
E 22
I 22
			"%s: %s: failed to send a setupframe",
			dp->name, __func__);
E 26
I 26
	if (bcmp(mac, lp->mac_addr, ETHERADDRL) ||
	    lp->last_mc_count != dp->mc_count) {
		/*
D 29
		 * send a setup frame
E 29
I 29
		 * send the setup frame
E 29
		 */
D 28
		DPRINTF(0, (CE_CONT,
			"%s: %s: sending a setupframe, tx_head:%d",
			dp->name, __func__, dp->tx_desc_head));
E 28
I 28
		DPRINTF(2, (CE_CONT,
		    "%s: %s: sending a setupframe, tx_head:%d",
		    dp->name, __func__, dp->tx_desc_head));
E 28

		for (i = 0; gem_send_common(dp, mp, hashtype); i++) {
			if (i > 10) {
				cmn_err(CE_WARN,
D 28
					"%s: %s: failed to send a setupframe",
					dp->name, __func__);
E 28
I 28
				    "!%s: %s: failed to send a setupframe",
				    dp->name, __func__);
E 28
				freemsg(mp);
				return (GEM_FAILURE);
			}
I 28
			if (i != 0) {
				delay(drv_usectohz(1000000));
			}
E 28
			gem_reclaim_txbuf(dp);
		}
		bcopy(mac, lp->mac_addr, ETHERADDRL);
		lp->last_mc_count = dp->mc_count;
	} else {
E 26
E 22
I 17
		freemsg(mp);
I 20
D 26
		return (GEM_FAILURE);
E 26
E 20
E 17
I 7
D 16
		freemsg(mp);
E 16
E 7
D 6
		}
E 6
	}
I 20

	return (GEM_SUCCESS);
E 20
I 16
D 17
	freemsg(mp);
E 17
E 16
I 9
D 10

E 9
x:
	/*
D 9
	 * set rx mode and kick potentially stopped rx engine
E 9
I 9
	 * set rx mode and kick stopped rx engine
E 9
	 */
	lp->nar = (lp->nar & ~(NAR_PB | NAR_PR | NAR_MM)) | mode;
D 9
	if ((lp->nar & (NAR_ST | NAR_SR)) != 0) {
		OUTL(dp, NAR, lp->nar & ~(NAR_ST | NAR_SR));
I 2
		drv_usecwait(5);
E 2
	}
	OUTL(dp, NAR, lp->nar);
I 2
	drv_usecwait(5);
E 9
I 9

	/* stop rx and tx for a while */
	tu_freeze_chip(dp);

	UPDATE_NAR(dp, lp->nar);
	tu_restart_chip(dp);
E 10
E 9
E 2
}
I 2
#undef HASH_MAC_COPY
E 2

I 9
/*
 * CAUTION: xx_set_media may be called before xx_init_chip
 */
E 9
static void
D 16
tu_set_media(struct gem_dev *dp)
E 16
I 16
D 17
tu_setup_speed_duplex(struct gem_dev *dp, boolean_t speed, boolean_t duplex)
E 17
I 17
tu_setup_speed_duplex(struct gem_dev *dp, int port, uint32_t adv)
E 17
E 16
{
D 7
	int			val;
	struct tu_chip_state	*lp = (struct tu_chip_state *)dp->private;
E 7
I 7
D 9
	int		val;
E 9
I 9
	int		i;
D 17
	int		ix;
E 17
I 10
	uint32_t	val;
E 10
D 16
	char		propname[32];
E 16
E 9
D 28
	struct tu_dev	*lp = (struct tu_dev *)dp->private;
E 28
I 28
	uint32_t	txrx_state;
	struct tu_dev	*lp = dp->private;
E 28
E 7

I 9
D 10
	DPRINTF(3, (CE_CONT, "!%s: tu_set_media: active:%d",
			dp->name, dp->nic_active));
E 10
I 10
D 17
	DPRINTF(2, (CE_CONT,
D 11
		"!%s: tu_set_media called: active:%d nar:%b csr6:%b",
E 11
I 11
D 16
		"!%s: tu_set_media called: active:%d nar:%b csr6:%b sr:%b",
E 11
		dp->name, dp->nic_active,
E 16
I 16
		"!%s: %s called: active:%d nar:%b csr6:%b sr:%b",
		dp->name, __func__, dp->nic_active,
E 17
I 17
	DPRINTF(1, (CE_CONT,
D 28
		"!%s: %s called: port:%d active:%d nar:%b csr6:%b sr:%b",
		dp->name, __func__,
		port, dp->mac_active,
E 17
E 16
D 11
		lp->nar, CSR6BITS, INL(dp, NAR), CSR6BITS));
E 11
I 11
		lp->nar, CSR6BITS, INL(dp, NAR), CSR6BITS,
		INL(dp, SR), SR_BITS));
E 28
I 28
	    "!%s: %s called: port:%d active:%d nar:%b csr6:%b sr:%b",
	    dp->name, __func__,
	    port, dp->mac_active,
	    lp->nar, CSR6BITS, INL(dp, NAR), CSR6BITS,
	    INL(dp, SR), SR_BITS));
E 28
E 11
E 10

I 28
	/* stop tx and rx */
	txrx_state = tu_freeze_chip(dp, NAR_ST | NAR_SR);

E 28
E 9
	/*
D 9
	 * Notify current duplex mode to mac core
E 9
I 9
	 * Notify current speed and duplex mode to mac core
E 9
	 */
D 2
#ifdef SANITY
	lp->nar = INL(dp, NAR);
#endif
	if ((lp->nar & (NAR_ST | NAR_SR)) != 0) {
		/* Stop Tx and Rx temporary */
		OUTL(dp, NAR, lp->nar & ~(NAR_ST | NAR_SR));
	}
E 2
I 2
D 9
	if (lp->port == PORT_MII) {
		/* Temporary stop Tx and Rx */
		if ((lp->nar & (NAR_ST | NAR_SR)) != 0) {
			OUTL(dp, NAR, lp->nar & ~(NAR_ST | NAR_SR));
		}
		drv_usecwait(5);
E 9
I 9
D 10
	tu_freeze_chip(dp);
E 10
I 10
D 16
	tu_freeze_chip(dp, NAR_ST | NAR_SR);
E 10
D 11
	ix = PORT_IX(dp->speed100, dp->full_duplex);
E 11
I 11
	ix = PORT_IX(dp->speed != GEM_SPD_10, dp->full_duplex);
E 16
I 16
D 17
	ix = PORT_IX(speed, duplex);
E 16
E 11
E 9
E 2

I 16
	OUTL(dp, SIACONN, 0);	/* csr13 */
	OUTL(dp, SIACTRL, lp->cfg_csr14[ix]);
	if (lp->cfg_csr13[ix]) {
		OUTL(dp, SIACONN, lp->cfg_csr13[ix]);
E 17
I 17
	lp->nar = (lp->nar & ~CSR6_PORT_BITS) | lp->cfg_csr6[port];
D 28
	if ((adv & SIACTRL_ANE) != 0) {
E 28
I 28
	if (adv & SIACTRL_ANE) {
E 28
		ASSERT(port == PORT_10_HD || port == PORT_10_FD);
		switch (lp->hw_info->chip_type) {
D 29
		case CHIP_MX987XX:
E 29
I 29
		case CHIP_MX98713:
		case CHIP_MX98713A:
		case CHIP_MX98715:
		case CHIP_MX98725:
E 29
		case CHIP_LC82C115:
			lp->nar |= NAR_SCR;
			break;
		}
		port = PORT_10_HD;
E 17
	}
D 17

E 16
D 2
	if (dp->mii_fixedmode) {
		/*
		 * FD bit determines duplex mode (full/half),
		 * when autonegotiation is disabled,
		 * No effect for AN983.
		 */
		lp->nar &= ~NAR_FD;
		if (dp->full_duplex) {
			lp->nar |= NAR_FD;
E 2
I 2
D 9
		/* select speed (100/10) */
		lp->nar |= NAR_TTM | NAR_SQE;
		if (dp->speed100) {
			lp->nar &= ~NAR_TTM;
E 2
		}
E 9
I 9
D 10
	lp->nar = (lp->nar & ~CSR6_PORT_BITS) | lp->csr6[ix];
	UPDATE_NAR(dp, lp->nar);
E 10
I 10
	lp->nar = (lp->nar & ~CSR6_PORT_BITS) | lp->cfg_csr6[ix];
E 17
D 28
	UPDATE_NAR(dp, lp->nar & ~(NAR_ST | NAR_SR));
E 10
E 9
D 2
	} else {
		/*
		 * Dont touch here.
		 * When autonegotiation is enabled, FD bit is used
		 * for advertisement bit of 10M-fullduplex capability.
		 */
	}
E 2

E 28
I 28
	UPDATE_NAR(dp, lp->nar);
E 28
D 2
	/*
	 * Determin speed (100M/10M)
	 * No effect for AN983
	 */
	lp->nar &= ~NAR_TTM;
	if (!dp->speed100) {
		lp->nar |= NAR_TTM;
E 2
I 2
D 9
		if (dp->mii_fixedmode) {
			/* select duplex mode (full/half) */
			lp->nar &= ~NAR_FD;
			if (dp->full_duplex){
				lp->nar |= NAR_FD;
E 9
I 9
D 11
	/* configure generaul purpose registers and watch dog */
E 11
I 11
	/* configure general purpose port and watch-dog registers */
E 11
	switch (lp->hw_info->chip_type) {
	case CHIP_21140:
D 10
		OUTL(dp, GPIO, lp->gp_ctrl[ix]); /* csr12 */
E 10
I 10
D 17
		OUTL(dp, GPIO, lp->gp_ctrl[0]); /* csr12 */
E 17
I 17
		/* csr12 */
		OUTL(dp, GPIO, lp->gp_ctrl[0]);
E 17
E 10
		if (lp->gp_seq_len > 0) {
			for (i = 0; i < lp->gp_seq_len; i++) {
D 10
				OUTL(dp, GPIO, lp->gp_seq[i]); /* csr12 */
E 10
I 10
				OUTL(dp, GPIO, lp->gp_seq[i]);
E 10
E 9
			}
I 9
		} else {
D 17
			OUTL(dp, GPIO, lp->gp_data[ix]); /* csr12 */
E 17
I 17
			OUTL(dp, GPIO, lp->gp_data[port]); /* csr12 */
E 17
E 9
		}
I 16
		/* csr15 is watchdog timer register, not gpio */
E 16
I 9
D 10
		OUTL(dp, SIAGP, lp->csr15[ix]);
E 10
I 10
D 17
		OUTL(dp, SIAGP, lp->cfg_csr15[ix]);
E 17
I 17
		OUTL(dp, SIAGP, lp->cfg_csr15[port]);
E 17
E 10
		break;
E 9

D 9
		/* update NAR */
D 7
		if ((lp->nar & (NAR_ST | NAR_SR)) != 0) {;
E 7
I 7
		if ((lp->nar & (NAR_ST | NAR_SR)) != 0) {
E 7
			OUTL(dp, NAR, lp->nar & ~(NAR_ST | NAR_SR));
			drv_usecwait(5);
E 9
I 9
	case CHIP_21142:
D 10
		OUTL(dp, SIAGP, (lp->gp_ctrl[ix] << 16) | lp->csr15[ix]);
		OUTL(dp, SIAGP, (lp->gp_data[ix] << 16) | lp->csr15[ix]);
E 10
I 10
D 11
	case CHIP_MX98713:
E 11
D 17
		OUTL(dp, SIAGP, (lp->gp_ctrl[ix] << 16) | lp->cfg_csr15[ix]);
E 17
I 17
		OUTL(dp, SIACONN, 0);	/* csr13 */
		OUTL(dp, SIACTRL, adv | lp->cfg_csr14[port]);
		if (lp->cfg_csr13[port]) {
			OUTL(dp, SIACONN, lp->cfg_csr13[port]);
		}

		OUTL(dp, SIAGP,
D 28
			(lp->gp_ctrl[port] << 16) | lp->cfg_csr15[port]);
E 28
I 28
		    (lp->gp_ctrl[port] << 16) | lp->cfg_csr15[port]);
E 28
E 17
		if (lp->gp_seq_len > 0) {
			for (i = 0; i < lp->gp_seq_len; i++) {
D 16
				val = (lp->gp_seq[2*i+1]<<8) | lp->gp_seq[2*i];
E 16
I 16
				val = LEWORD(&lp->gp_seq[2*i]);
E 16
D 17
				OUTL(dp, SIAGP, (val<<16) | lp->cfg_csr15[ix]);
E 17
I 17
				OUTL(dp, SIAGP,
D 28
					(val << 16) | lp->cfg_csr15[port]);
E 28
I 28
				    (val << 16) | lp->cfg_csr15[port]);
E 28
E 17
			}
		} else {
			OUTL(dp, SIAGP,
D 17
				(lp->gp_data[ix] << 16) | lp->cfg_csr15[ix]);
E 17
I 17
D 28
				(lp->gp_data[port]<<16) | lp->cfg_csr15[port]);
E 28
I 28
			    (lp->gp_data[port] << 16) | lp->cfg_csr15[port]);
E 28
E 17
		}
E 10
		break;

	case CHIP_LC82C168:
D 16
		OUTL(dp, GPIO, lp->gp_data[ix]); /* csr12: relay control */
E 16
I 16
		/* csr12: relay control */
D 17
		OUTL(dp, GPIO, lp->gp_data[ix]);
E 16
D 10
		OUTL(dp, SIAGP, lp->csr15[ix]);
E 10
I 10
		OUTL(dp, SIAGP, lp->cfg_csr15[ix]);
E 17
I 17
		OUTL(dp, GPIO, lp->gp_data[port]);
		OUTL(dp, SIAGP, lp->cfg_csr15[port]);

		if (lp->port == PORT_MII) {
			/* disable NWAY logic */
			val = INL(dp, PNIC_NWAY);
			OUTL(dp, PNIC_NWAY, val | NWAY_PD | NWAY_LC);
		}
E 17
E 10
		break;

	case CHIP_DM9102:
I 29
	case CHIP_DM9102A:
E 29
D 14
		OUTL(dp, SIAGP,
D 10
			lp->csr15[ix] | (dp->flow_control ? SIAGP_FLCE_DM : 0));
E 10
I 10
		    lp->cfg_csr15[ix] | (dp->flow_control ? SIAGP_FLCE_DM : 0));
E 14
I 14
		/* it doesn't seems to work */
D 28
		switch(dp->flow_control) {
E 28
I 28
#ifdef GEM_CONFIG_GLDv3
		val = SIAGP_VLAN_DM;
#else
		val = 0;
#endif
		switch (dp->flow_control) {
E 28
		case FLOW_CONTROL_RX_PAUSE:
D 28
			val = SIAGP_FLCE_DM;
E 28
I 28
			val |= SIAGP_FLCE_DM;
E 28
			break;
		case FLOW_CONTROL_TX_PAUSE:
D 28
			val = SIAGP_TXPM_DM | SIAGP_TXP0_DM | SIAGP_TXPF_DM;
E 28
I 28
			val |= SIAGP_TXPM_DM | SIAGP_TXP0_DM | SIAGP_TXPF_DM;
E 28
			break;
		case FLOW_CONTROL_SYMMETRIC:
D 28
			val = SIAGP_FLCE_DM
E 28
I 28
			val |= SIAGP_FLCE_DM
E 28
			    | SIAGP_TXPM_DM | SIAGP_TXP0_DM | SIAGP_TXPF_DM;
			break;
D 28
		default:
			val = 0;
			break;
E 28
		}
D 17
		OUTL(dp, SIAGP, lp->cfg_csr15[ix] | val);
E 17
I 17
		OUTL(dp, SIAGP, lp->cfg_csr15[port] | val);
E 17
E 14
E 10
		break;
I 17
D 28
	
E 28
I 28

E 28
	case CHIP_XIRCOM:
		/* do nothing here */
		break;
E 17

I 17
D 29
	case CHIP_MX987XX:
E 29
I 29
	case CHIP_MX98713:
	case CHIP_MX98713A:
	case CHIP_MX98715:
	case CHIP_MX98725:
E 29
	case CHIP_LC82C115:
D 28
		if ((lp->bmcr & MII_CONTROL_ANE) != 0) {
			if ((adv & SIACTRL_ANE) != 0) {
E 28
I 28
		if (lp->bmcr & MII_CONTROL_ANE) {
			if (adv & SIACTRL_ANE) {
E 28
				OUTL(dp, SIACONN, 0);	/* csr13 */
				OUTL(dp, SIACTRL, adv | lp->cfg_csr14[port]);
				OUTL(dp, SIACONN, lp->cfg_csr13[port]);
			}
D 28
		} 
		else {
E 28
I 28
		} else {
E 28
			OUTL(dp, SIACONN, 0);	/* csr13 */
			OUTL(dp, SIACTRL, lp->cfg_csr14[port]);
D 28
			if (lp->cfg_csr13[port] != 0) {
E 28
I 28
			if (lp->cfg_csr13[port]) {
E 28
				OUTL(dp, SIACONN, lp->cfg_csr13[port]);
			}
		}
D 28
		/* fall down */
E 28
I 28
		/* FALLTHRU */
E 28
E 17
	default:
D 10
		/* CENTAUR, LC82C115, MX98715, MX98713, CONEXANT */
		OUTL(dp, SIAGP, lp->csr15[ix]);
E 10
I 10
D 11
		/* CENTAUR, LC82C115, MX98715, CONEXANT */
E 11
I 11
		/* No general purpose port */
		/* CENTAUR, LC82C115, MX987XX, CONEXANT */
E 11
D 17
		OUTL(dp, SIAGP, lp->cfg_csr15[ix]);
E 17
I 17
		OUTL(dp, SIAGP, lp->cfg_csr15[port]);
E 17
E 10
		break;
	}
I 28

	/* restart Tx and Rx */
	tu_restart_chip(dp, txrx_state);
E 28
I 16
}
E 16

I 16
D 20
static void
E 20
I 20
static int
E 20
tu_set_media(struct gem_dev *dp)
{
	int		i;
D 17
	int		ix;
E 17
	uint32_t	val;
D 28
	struct tu_dev	*lp = (struct tu_dev *)dp->private;
E 28
I 28
	struct tu_dev	*lp = dp->private;
E 28

D 26
	DPRINTF(2, (CE_CONT,
		"!%s: %s called: active:%d nar:%b csr6:%b sr:%b",
E 26
I 26
	DPRINTF(1, (CE_CONT,
D 28
		"!%s: %s called: active:%d nar:%b csr6:%b sr:%b rba;%x",
E 26
D 17
		dp->name, __func__, dp->nic_active,
E 17
I 17
		dp->name, __func__, dp->mac_active,
E 17
		lp->nar, CSR6BITS, INL(dp, NAR), CSR6BITS,
D 26
		INL(dp, SR), SR_BITS));
E 26
I 26
		INL(dp, SR), SR_BITS, INL(dp, RDB)));
E 28
I 28
	    "!%s: %s called: active:%d nar:%b csr6:%b sr:%b rba;%x",
	    dp->name, __func__, dp->mac_active,
	    lp->nar, CSR6BITS, INL(dp, NAR), CSR6BITS,
	    INL(dp, SR), SR_BITS, INL(dp, RDB)));
E 28
E 26

E 16
	/*
D 16
	 * rx delay control
E 16
I 16
	 * Notify current speed and duplex mode to mac core
E 16
	 */
D 16
	switch (lp->hw_info->chip_type) {
	case CHIP_CENTAUR:
		lp->rx_delay = ((lp->rx_delay_pkts-1)*150000)/204800;
		break;
E 16
I 16
D 28
	tu_freeze_chip(dp, NAR_ST | NAR_SR);
I 26

E 28
E 26
I 17
	tu_setup_speed_duplex(dp,
D 28
			PORT_IX(dp->speed != GEM_SPD_10, dp->full_duplex), 0);
E 28
I 28
	    PORT_IX(dp->speed != GEM_SPD_10, dp->full_duplex), 0);
E 28
E 17
E 16

D 16
	case CHIP_21140:
	case CHIP_21142:
		if (lp->port == PORT_SYM) {
			lp->rx_delay = ((lp->rx_delay_pkts - 1)*150000)/204800;
E 9
		}
D 9
		OUTL(dp, NAR, lp->nar);
		drv_usecwait(5);
E 9
I 9
D 11
		else if (dp->speed100) {
E 11
I 11
		else if (dp->speed == GEM_SPD_100) {
E 11
			lp->rx_delay = ((lp->rx_delay_pkts - 1)*150000)/81920;
		}
		else {
			lp->rx_delay = ((lp->rx_delay_pkts - 1)*150000)/819200;
		}
		break;
E 9
E 2
	}
E 16
I 16
D 17
	tu_setup_speed_duplex(dp, dp->speed != GEM_SPD_10, dp->full_duplex);
E 16

E 17
	/*
	 * Flow control
	 */
D 2
	if (lp->hw_info->chip_type == CHIP_AN983) {
E 2
I 2
D 9
	if (lp->hw_info->chip_type == CHIP_COMET ||
	    lp->hw_info->chip_type == CHIP_CENTAUR) {
E 9
I 9
	switch (lp->hw_info->chip_type) {
	case CHIP_CENTAUR:
E 9
E 2
D 14
		if (dp->flow_control) {
E 14
I 14
		if (dp->flow_control == FLOW_CONTROL_SYMMETRIC) {
E 14
			OUTL(dp, CR_AN, INL(dp, CR_AN) | CR_PAUSE);
		} else {
			OUTL(dp, CR_AN, INL(dp, CR_AN) & ~CR_PAUSE);
		}
D 17
		DPRINTF(2, (CE_CONT, "!%s: set_media: OPM: 0x%x",
				dp->name, INL(dp, OPM_AN)));
E 17
I 17
		DPRINTF(2, (CE_CONT, "!%s: %s: OPM: 0x%x",
D 28
				dp->name, __func__, INL(dp, OPM_AN)));
E 28
I 28
		    dp->name, __func__, INL(dp, OPM_AN)));
E 28
E 17
I 9
		break;
E 9
	}
D 9
	else if (lp->hw_info->chip_type == CHIP_DM9102) {
		if (dp->flow_control) {
			OUTL(dp, WTMR, INL(dp, WTMR) | WTMR_FLCE_DM);
		} else {
			OUTL(dp, WTMR, INL(dp, WTMR) & ~WTMR_FLCE_DM);
		}
	}
E 9
I 9

D 28
	/* restart Tx and Rx */
	tu_restart_chip(dp);
I 10

E 28
D 11
	DPRINTF(2, (CE_CONT, "!%s: tu_set_media: nar:%b csr6:%b",
		dp->name, lp->nar, CSR6BITS, INL(dp, NAR), CSR6BITS));
E 11
I 11
D 17
	DPRINTF(2, (CE_CONT, "!%s: tu_set_media: nar:%b csr6:%b sr:%b",
		dp->name, lp->nar, CSR6BITS, INL(dp, NAR), CSR6BITS,
E 17
I 17
	/* fix error bits for tx */
	lp->tx_errbits = TDES0_TO | TDES0_LC | TDES0_EC | TDES0_UF;

	switch (lp->hw_info->chip_type) {
	case CHIP_XIRCOM:
		if (!dp->full_duplex) {
			/* check lost carrier errors if half duplex */
			lp->tx_errbits |= TDES0_LO | TDES0_NC;
		}
		break;

	case CHIP_CENTAUR:
		if (dp->full_duplex) {
			/* check lost carrier errors if full duplex */
			lp->tx_errbits |= TDES0_LO | TDES0_NC;
		}
		break;

	default:
		lp->tx_errbits |= TDES0_LO | TDES0_NC;
		break;
	}

	if ((lp->nar & NAR_SQE) == 0) {
		lp->tx_errbits |= TDES0_HF;
	}

	DPRINTF(2, (CE_CONT, "!%s: %s: nar:%b csr6:%b sr:%b",
D 28
		dp->name, __func__, lp->nar, CSR6BITS, INL(dp, NAR), CSR6BITS,
E 17
		INL(dp, SR), SR_BITS));
E 28
I 28
	    dp->name, __func__, lp->nar, CSR6BITS, INL(dp, NAR), CSR6BITS,
	    INL(dp, SR), SR_BITS));
E 28
I 20

	return (GEM_SUCCESS);
E 20
E 11
E 10
E 9
D 2

	if ((lp->nar & (NAR_ST | NAR_SR)) != 0) {
		OUTL(dp, NAR, lp->nar & ~(NAR_ST | NAR_SR));
	}
	OUTL(dp, NAR, lp->nar);
E 2
}

D 20
static void
E 20
I 20
static int
E 20
tu_get_stats(struct gem_dev *dp)
{
D 7
	dp->stats.missed += INL(dp, LPC) & (LPC_LPCO | LPC);
E 7
I 7
D 26
	dp->stats.missed += INL(dp, LPC) & LPC_LPC;
E 26
I 26
	uint_t	missed;
E 26
I 20

I 26
	missed = INL(dp, LPC) & LPC_LPC;
	dp->stats.missed += missed;
	dp->stats.errrcv += missed;

E 26
	return (GEM_SUCCESS);
E 20
E 7
}

/*
 * discriptor  manupiration
 */
static uint_t tu_filter_mode[] = {
D 11
	/* 0		*/	0,
E 11
I 11
	/* 0: reserved	*/	0,
E 11
	/* 1: PERFECT	*/	TDES1_PERFECT,
	/* 2: HASH	*/	TDES1_HASH,
	/* 3: INVERSE	*/	TDES1_INVERSE,
	/* 4: HASHONLY	*/	TDES1_HASHONLY,
};

static int
tu_tx_setupframe(struct gem_dev *dp, uint_t slot,
D 19
		ddi_dma_cookie_t *dmacookie, int flag)
E 19
I 19
		ddi_dma_cookie_t *dmacookie, uint32_t flag)
E 19
{
D 7
	struct tx_desc		*tdp;
	uint32_t		mark;
	int			filter;
	struct tu_chip_state	*lp = (struct tu_chip_state *)dp->private;
E 7
I 7
D 15
	struct tx_desc	*tdp;
	uint32_t	mark;
	int		filter;
	struct tu_dev	*lp = (struct tu_dev *)dp->private;
E 7
D 14
	int	used;
E 14
I 14
	int		used;
E 15
I 15
	struct tx_desc		*tdp;
	uint32_t		mark;
I 28
	uint32_t		addr;
E 28
	int			filter;
D 28
	struct tu_dev		*lp = (struct tu_dev *)dp->private;
E 28
I 28
	struct tu_dev		*lp = dp->private;
E 28
	int			used;
I 19
	uint32_t		own;
E 19
D 17
	ddi_acc_handle_t	h = dp->desc_acc_handle;
E 17
E 15
E 14

I 28
	DPRINTF(1, (CE_CONT, "!%s: %s called", dp->name, __func__));
E 28
	/*
D 28
	 * Setupframe
E 28
I 28
	 * send a setupframe
E 28
	 */
D 2
	DPRINTF(2, (CE_CONT, "%s: tu_tx_setupframe called", dp->name));
E 2
I 2
D 17
	DPRINTF(2, (CE_CONT, "!%s: tu_tx_setupframe called", dp->name));
E 17
I 17
D 28
	DPRINTF(2, (CE_CONT, "!%s: %s called", dp->name, __func__));
E 28
E 17
E 2
	used = 1;
D 14
	filter = flag >> 8;
E 14
I 14
	filter = (flag & GEM_TXFLAG_PRIVATE) >> GEM_TXFLAG_PRIVATE_SHIFT;
I 19
D 26
	own = ((flag & GEM_TXFLAG_HEAD) != 0) ? 0 : LE32(TDES0_OWN);
E 26
I 26
D 28
	own = ((flag & GEM_TXFLAG_HEAD) != 0) ? 0 : LE_32(TDES0_OWN);
E 28
I 28
	own = (flag & GEM_TXFLAG_HEAD) ? 0 : LE_32(TDES0_OWN);
E 28
E 26
E 19
E 14

	/* setupframe must be a double word aligned single buffer */
	ASSERT((dmacookie->dmac_address & 3) == 0);

D 11
	ASSERT(0 < filter && filter <= 4);
E 11
I 11
	ASSERT(1 <= filter && filter <= 4);
E 11
D 14
	mark = ((flag & 1) ? TDES1_IC : 0)
E 14
I 14
D 28
	mark = (((flag & GEM_TXFLAG_INTR) != 0) ? TDES1_IC : 0)
E 14
	     | tu_filter_mode[filter] | TDES1_SETF;
E 28
I 28
	mark = ((flag & GEM_TXFLAG_INTR) ? TDES1_IC : 0)
	    | tu_filter_mode[filter] | TDES1_SETF;
E 28

D 7
	if (slot != 0) {
		/* insert a zero length descriptor */
E 7
I 7
D 17
	if (slot != 0 && lp->hw_info->chip_type != CHIP_DM9102) {
E 17
I 17
	switch (lp->hw_info->chip_type) {
	case CHIP_XIRCOM:
D 28
		/* xircom chipsets need FIRST and LAST bit in tdes1 */
E 28
I 28
		/* xircom chipset need FIRST and LAST bits in tdes1 */
E 28
		mark |= TDES1_FS | TDES1_LS;
	}

D 26
	if (slot != 0 && !(
		lp->hw_info->chip_type == CHIP_DM9102 ||
		(lp->hw_info->chip_type == CHIP_ULI526X &&
			(lp->pci_revid == 0x40 || lp->pci_revid == 0x50)))) {

E 26
I 26
D 28
	if (slot != 0 && lp->hw_info->chip_type != CHIP_DM9102 &&
E 28
I 28
	if (!lp->first_setupframe &&
D 29
	    lp->hw_info->chip_type != CHIP_DM9102 &&
E 28
	    lp->hw_info->chip_type != CHIP_ULI526X) {
E 29
I 29
	    (lp->hw_info->capability & CHIP_WA_NO_PAD_TXDESC) == 0) {
E 29
E 26
E 17
D 19
		/* insert a zero length descriptor except DM9102 */
E 19
I 19
		/* insert a zero length descriptor except DM9102 and ULI */
E 19
E 7
D 14
		tdp = &((struct tx_desc *)dp->tx_ring)[
				SLOT(slot, TX_RING_SIZE)];
E 14
I 14
D 28
		tdp = &((struct tx_desc *)dp->tx_ring)[slot];
E 14
D 15
		tdp->td_baddr1  = 0;
		tdp->td_control &= (TDES1_TER | TDES1_TCH);
		tdp->td_status  = TDES0_OWN;
E 15
I 15
D 17
		ddi_put32(h, &tdp->td_baddr1, 0);
		ddi_put32(h, &tdp->td_control,
			ddi_get32(h, &tdp->td_control) & (TDES1_TER | TDES1_TCH));
		ddi_put32(h, &tdp->td_status, TDES0_OWN);
E 15
I 6
D 14
#ifdef IOCACHE
E 14
I 14

E 17
I 17
		tdp->td_baddr1  = 0;
E 28
I 28
		tdp = &TXDESC(dp->tx_ring)[slot];
		tdp->td_baddr1 = 0;
E 28
D 26
		tdp->td_control &= LE32(TDES1_TER | TDES1_TCH);
E 26
I 26
		tdp->td_control &= LE_32(TDES1_TER | TDES1_TCH);
E 26
D 19
#if 0
		tdp->td_status  = LE32(TDES0_OWN);
#else
		tdp->td_status  = 0;
#endif
E 17
E 14
		ddi_dma_sync(dp->desc_dma_handle,
			(off_t)(((caddr_t)tdp) - dp->rx_ring) ,
			sizeof(struct tx_desc), DDI_DMA_SYNC_FORDEV);
E 19
I 19
D 28
		tdp->td_status  = own;
E 28
I 28
		tdp->td_status = own;
E 28
D 26
		own = LE32(TDES0_OWN);
E 26
I 26
		own = LE_32(TDES0_OWN);
E 26
E 19
D 14
#endif
E 6
		slot++;
E 14
I 14

I 28
		/* advance current index */
E 28
		slot = SLOT(slot + 1, TX_RING_SIZE);
E 14
		used++;
	}
I 28
	lp->first_setupframe = B_FALSE;
E 28
I 10

E 10
D 14
	tdp = &((struct tx_desc *)dp->tx_ring)[
				SLOT(slot, TX_RING_SIZE)];
E 14
I 14
D 28
	tdp = &((struct tx_desc *)dp->tx_ring)[slot];
E 14
D 15
	tdp->td_baddr1  = dmacookie->dmac_address;
	tdp->td_control = dmacookie->dmac_size | mark
			| (tdp->td_control & (TDES1_TER | TDES1_TCH));
	tdp->td_status  = TDES0_OWN;
E 15
I 15
D 17
	ddi_put32(h, &tdp->td_baddr1,dmacookie->dmac_address);
	ddi_put32(h, &tdp->td_control, dmacookie->dmac_size | mark
			| (ddi_get32(h, &tdp->td_control) & (TDES1_TER | TDES1_TCH)));
	ddi_put32(h, &tdp->td_status, TDES0_OWN);
E 17
I 17
D 26
	tdp->td_baddr1  = LE32(dmacookie->dmac_address);
	tdp->td_control = LE32(dmacookie->dmac_size | mark)
			| (tdp->td_control & LE32(TDES1_TER | TDES1_TCH));
E 26
I 26
	tdp->td_baddr1  = LE_32(dmacookie->dmac_address);
	tdp->td_control = LE_32(dmacookie->dmac_size | mark)
			| (tdp->td_control & LE_32(TDES1_TER | TDES1_TCH));
E 26
D 19
#if 0
	tdp->td_status  = LE32(TDES0_OWN);
#else
	tdp->td_status  = 0;
#endif
E 19
I 19
	tdp->td_status  = own;
E 28
I 28
	tdp = &TXDESC(dp->tx_ring)[slot];
	addr = dmacookie->dmac_address;
	mark |= (uint32_t)dmacookie->dmac_size;
	tdp->td_baddr1 = LE_32(addr);
	tdp->td_control = LE_32(mark)
	    | (tdp->td_control & LE_32(TDES1_TER | TDES1_TCH));
	tdp->td_status = own;
E 28
E 19
E 17
E 15
D 6

E 6
I 6
D 14
#ifdef IOCACHE
E 14
I 14

E 14
D 19
	ddi_dma_sync(dp->desc_dma_handle,
		(off_t)(((caddr_t)tdp) - dp->rx_ring) ,
		sizeof(struct tx_desc), DDI_DMA_SYNC_FORDEV);
D 14
#endif
E 14
I 14

E 19
E 14
E 6
D 28
	OUTL(dp, TDR, 0xffffffff);
E 28
I 28
	OUTL(dp, TDR, 0xffffffffU);
E 28

D 17
	return used;
E 17
I 17
	return (used);
E 17
}
I 14

E 14
D 10

static int
tu_tx_desc_write2(struct gem_dev *dp, uint_t slot,
		ddi_dma_cookie_t *dmacookie, int frags, uint32_t flag)
{
	int			i;
	struct tx_desc		*tdp;
	ddi_dma_cookie_t	*dcp;
	uint32_t		mark;
	uint32_t		addr2;
	uint32_t		size2;
D 7
	struct tu_chip_state	*lp = (struct tu_chip_state *)dp->private;
E 7
I 7
	struct tu_dev		*lp = (struct tu_dev *)dp->private;
E 7

#if DEBUG_LEVEL > 2
	cmn_err(CE_CONT,
D 6
		"%s: tu_tx_desc_write seqnum: %d, slot %d, frags: %d flag: %d",
E 6
I 6
D 7
		"%s: tu_tx_desc_write seqnum: %d, slot %d, frags: %d flag: %x",
E 6
		dp->name, dp->tx_desc_tail, slot, frags, flag);
E 7
I 7
	"%s: time:%d tu_tx_desc_write seqnum: %d, slot %d, frags: %d flag: %x",
		dp->name, ddi_get_lbolt(), dp->tx_desc_tail, slot, frags, flag);
E 7
	for (i = 0; i < frags; i++) {
		cmn_err(CE_CONT, "%d: addr: 0x%x, len: 0x%x",
			i, dmacookie[i].dmac_address, dmacookie[i].dmac_size);
	}
#endif
I 7
#if DEBUG_LEVEL > 3
	flag |= 1;
#endif
E 7
	if ((flag >> 8) != 0) {
		/*
		 * Send setupframe
		 */
		return tu_tx_setupframe(dp, slot, dmacookie, flag);
	}

	/*
	 * write tx descriptor(s) in reversed order
	 */
D 2
#ifdef notdef
	flag = 1;
#endif
E 2
	mark = ((flag & 1) ? TDES1_IC : 0) | TDES1_LS;
	i = (frags - 1)/2;
	dcp = &dmacookie[i*2];

	if ((frags & 1) != 0) {
		/* odd fragments */
		size2 = 0;
		addr2 = 0;
		goto odd;
	}

	for (; i >= 0; i--, dcp -= 2) {
		addr2 = dcp[1].dmac_address;
		size2 = dcp[1].dmac_size;
odd:
		if (i == 0) {
			mark |= TDES1_FS;
		}
		tdp = &((struct tx_desc *)dp->tx_ring)[
				SLOT(slot + i, TX_RING_SIZE)];
		tdp->td_baddr1 = dcp[0].dmac_address;
		tdp->td_baddr2 = addr2;
		tdp->td_control = (size2 << TDES1_TBS2_SHIFT)
				| dcp[0].dmac_size | mark
				| (tdp->td_control & TDES1_TER);
		tdp->td_status  = TDES0_OWN;
I 6
#ifdef IOCACHE
		ddi_dma_sync(dp->desc_dma_handle,
			(off_t)(((caddr_t)tdp) - dp->rx_ring) ,
			sizeof(struct tx_desc), DDI_DMA_SYNC_FORDEV);
#endif
E 6

		mark = 0;
	}

	/* kick Tx engine */
#ifdef TXTIMEOUT_TEST
	if ((tu_send_cnt++ % 100) == 99) {
	}
#endif
	OUTL(dp, TDR, 0xffffffff);

	return (frags + 1) / 2;
}

E 10
I 3
#ifdef DEBUG_LEVEL
static int	tu_send_cnt;
#endif
E 3
static int
D 17
tu_tx_desc_write1(struct gem_dev *dp, uint_t slot,
		ddi_dma_cookie_t *dmacookie, int frags, u_int flag)
E 17
I 17
tu_tx_desc_write1(struct gem_dev *dp, int slot,
D 26
		ddi_dma_cookie_t *dmacookie, int frags, uint32_t flag)
E 26
I 26
		ddi_dma_cookie_t *dmacookie, int frags, uint64_t flag)
E 26
E 17
{
	int			i;
	struct tx_desc		*tdp;
	ddi_dma_cookie_t	*dcp;
	uint32_t		mark;
I 28
	uint32_t		addr;
E 28
I 17
D 26
	uint32_t		own = LE32(TDES0_OWN);
E 26
I 26
	uint32_t		own = LE_32(TDES0_OWN);
E 26
E 17
D 14
	int			filter;
E 14
D 7
	struct tu_chip_state	*lp = (struct tu_chip_state *)dp->private;
E 7
I 7
D 28
	struct tu_dev		*lp = (struct tu_dev *)dp->private;
E 28
I 28
	struct tu_dev		*lp = dp->private;
E 28
I 15
D 17
	ddi_acc_handle_t	h = dp->desc_acc_handle;
E 17
E 15
E 7

D 28
#if DEBUG_LEVEL > 2
E 28
I 28
D 29
#if DEBUG_LEVEL > 1
E 29
I 29
#if DEBUG_LEVEL > 2
E 29
E 28
	cmn_err(CE_CONT,
D 6
		"%s: tu_tx_desc_write1 seqnum: %d, slot %d, frags: %d flag: %d",
E 6
I 6
D 7
		"%s: tu_tx_desc_write1 seqnum: %d, slot %d, frags: %d flag: %x",
E 6
		dp->name, dp->tx_desc_tail, slot, frags, flag);
E 7
I 7
D 11
	"%s: time:%d tu_tx_desc_write1 seqnum: %d, slot %d, frags: %d flag: %x",
E 11
I 11
D 17
	"!%s: time:%d tu_tx_desc_write1 seqnum: %d, slot %d, frags: %d flag: %x",
E 11
		dp->name, ddi_get_lbolt(), dp->tx_desc_tail, slot, frags, flag);
E 17
I 17
D 28
		"!%s: time:%d %s seqnum: %d, slot %d, frags: %d flag: %x",
		dp->name, ddi_get_lbolt(), __func__,
		dp->tx_desc_tail, slot, frags, flag);
E 28
I 28
	    "!%s: time:%d %s seqnum: %d, slot %d, frags: %d flag: %x",
	    dp->name, ddi_get_lbolt(), __func__,
	    dp->tx_desc_tail, slot, frags, flag);
E 28
E 17
E 7
	for (i = 0; i < frags; i++) {
D 11
		cmn_err(CE_CONT, "%d: addr: 0x%x, len: 0x%x",
E 11
I 11
		cmn_err(CE_CONT, "!%d: addr: 0x%x, len: 0x%x",
E 11
D 28
			i, dmacookie[i].dmac_address, dmacookie[i].dmac_size);
E 28
I 28
		    i, dmacookie[i].dmac_address, dmacookie[i].dmac_size);
E 28
	}
I 7
D 9
	flag |= 1;
E 9
E 7
#endif
I 29
	if (lp->hw_info->capability & CHIP_WA_TXINTR) {
		flag |= GEM_TXFLAG_INTR;
	}
E 29
D 7

E 7
I 7
#if DEBUG_LEVEL > 3
D 14
	flag |= 1;
E 14
I 14
	flag |= GEM_TXFLAG_INTR;
E 14
#endif
E 7
D 14
	mark = (flag & 1) ? TDES1_IC : 0;	/* XXX - should last segment? */
D 2

E 2
	filter = flag >> 8;
	if (filter != 0) {
E 14
I 14
D 28
	/* XXX - should last segment? */
	mark = (flag & GEM_TXFLAG_INTR) ? TDES1_IC : 0;
	if ((flag & GEM_TXFLAG_PRIVATE) != 0) {
E 28
I 28
	if (flag & GEM_TXFLAG_PRIVATE) {
E 28
E 14
		ASSERT(frags == 1);
D 17
		return tu_tx_setupframe(dp, slot, dmacookie, flag);
E 17
I 17
		return (tu_tx_setupframe(dp, slot, dmacookie, flag));
E 17
	}
I 28
	/* XXX - should last segment? */
	mark = (flag & GEM_TXFLAG_INTR) ? TDES1_IC : 0;
E 28
I 10
D 11
	else {
		mark |= TDES1_LS;
	}
E 11
E 10

	/*
	 * write tx descriptor(s) in reversed order
	 */
I 17
#ifdef TEST_CRCERR
	if ((tu_send_cnt % 100) == 50) {
		mark |= TDES1_AC;
		dmacookie[frags - 1].dmac_size += ETHERFCSL;
	}
#endif
E 17
D 10
	mark |= TDES1_LS;
E 10
D 11
	for (i = frags - 1, dcp = &dmacookie[i]; i >= 0; i--, dcp--) {
D 10
		if (i == 0) {
E 10
I 10
		if (i == 0 && filter == 0) {
E 10
			mark |= TDES1_FS;
		}
E 11
I 11
D 16
	mark |= TDES1_LS;
	for (i = frags - 1, dcp = &dmacookie[i]; i > 0; i--, dcp--) {
E 16
I 16
	mark |= TDES1_LS | TDES1_TCH;
D 17
	for (i = frags - 1, dcp = &dmacookie[i]; i >= 0; i--, dcp--) {
E 17
I 17
	for (i = frags - 1, dcp = &dmacookie[i]; i > 0; i--, dcp--) {
E 17
E 16
E 11
D 28
		tdp = &((struct tx_desc *)dp->tx_ring)[
				SLOT(slot + i, TX_RING_SIZE)];
D 15
		tdp->td_baddr1  = dcp->dmac_address;
		tdp->td_control = dcp->dmac_size | mark | TDES1_TCH;
E 15
I 15
D 16
		ddi_put32(h, &tdp->td_baddr1, dcp->dmac_address);
		ddi_put32(h, &tdp->td_control,
				dcp->dmac_size | mark | TDES1_TCH);
E 15
I 3
#ifdef CRCERR_TEST
E 16
I 16
D 17
		if (i == 0) {
			mark |= TDES1_FS;
		}
#ifdef TEST_CRCERR
E 16
		if ((tu_send_cnt % 100) == 50) {
D 15
			tdp->td_control += ETHERFCSL;
			tdp->td_control |= TDES1_AC;
E 15
I 15
D 16
			ddi_put32(h, &tdp->td_control
				ddi_get32(h, &tdp->td_control) + ETHERFCSL);
			ddi_put32(h, &tdp->td_control,
				ddi_get32(h, &tdp->td_control) | TDES1_AC);
E 16
I 16
			mark |= TDES1_AC;
			if (i == frags - 1) {
				dcp->dmac_size += ETHERFCSL;
			}
E 16
E 15
		}
E 17
I 17
D 26
		tdp->td_control = LE32(dcp->dmac_size | mark);
		tdp->td_baddr1  = LE32(dcp->dmac_address);
E 26
I 26
		tdp->td_control = LE_32(dcp->dmac_size | mark);
		tdp->td_baddr1  = LE_32(dcp->dmac_address);
E 26
		tdp->td_status  = own;
E 28
I 28
		tdp = &TXDESC(dp->tx_ring)[SLOT(slot + i, TX_RING_SIZE)];
		addr = dcp->dmac_address;
		mark |= dcp->dmac_size;
		tdp->td_control = LE_32(mark);
		tdp->td_baddr1 = LE_32(addr);
		tdp->td_status = own;
E 28
D 29

E 29
I 29
#ifdef DEBUG_TX_WAKEUP
		mark = TDES1_TCH | (mark & TDES1_IC);
#else
E 29
		mark = TDES1_TCH;
I 29
#endif
E 29
	}

D 28
	tdp = &((struct tx_desc *)dp->tx_ring)[slot];
E 28
I 28
	tdp = &TXDESC(dp->tx_ring)[slot];
E 28
	mark |= TDES1_FS;
D 28
	if ((flag & GEM_TXFLAG_HEAD) != 0) {
E 28
I 28
	if (flag & GEM_TXFLAG_HEAD) {
E 28
		own = 0;
	}

D 26
	tdp->td_control = LE32(dcp->dmac_size | mark);
	tdp->td_baddr1  = LE32(dcp->dmac_address);
E 26
I 26
D 28
	tdp->td_control = LE_32(dcp->dmac_size | mark);
	tdp->td_baddr1  = LE_32(dcp->dmac_address);
E 26
	tdp->td_status  = own;
E 28
I 28
	mark |= (uint32_t)dcp->dmac_size;
	addr = dcp->dmac_address;
E 28

I 28
	tdp->td_control = LE_32(mark);
	tdp->td_baddr1 = LE_32(addr);
	tdp->td_status = own;

E 28
#ifdef DEBUG_LEVEL
	tu_send_cnt++;
E 17
#endif
I 16
D 17
		ddi_put32(h, &tdp->td_control, dcp->dmac_size | mark);
		ddi_put32(h, &tdp->td_baddr1, dcp->dmac_address);
E 16
E 3
D 15
		tdp->td_status  = TDES0_OWN;
E 15
I 15
		ddi_put32(h, &tdp->td_status, TDES0_OWN);
E 17
I 17
	return (frags);
}
E 17
E 15
D 6

E 6
I 6
D 14
#ifdef IOCACHE
E 14
I 14

E 14
D 17
		ddi_dma_sync(dp->desc_dma_handle,
			(off_t)(((caddr_t)tdp) - dp->rx_ring) ,
			sizeof(struct tx_desc), DDI_DMA_SYNC_FORDEV);
E 17
I 17
static void
tu_tx_start(struct gem_dev *dp, int start_slot, int nslot)
{
I 28
D 29
	DPRINTF(1, (CE_CONT, "!%s: %s called, start:%d, %d",
E 29
I 29
	DPRINTF(2, (CE_CONT, "!%s: %s called, start:%d, %d",
E 29
	    dp->name, __func__, start_slot, nslot));
E 28
D 19
	int		i;
	uint32_t	own;
	struct tx_desc	*tdp;
E 17
D 14
#endif
E 14
I 14

E 14
E 6
D 16
		mark = 0;
E 16
I 16
D 17
		mark = TDES1_TCH;
E 17
I 17
	own = LE32(TDES0_OWN);

E 19
	if (nslot > 1) {
		gem_tx_desc_dma_sync(dp,
D 28
				SLOT(start_slot + 1, TX_RING_SIZE),
				nslot - 1, DDI_DMA_SYNC_FORDEV);
E 28
I 28
		    SLOT(start_slot + 1, TX_RING_SIZE),
		    nslot - 1, DDI_DMA_SYNC_FORDEV);
E 28
E 17
E 16
	}

I 17
D 19
	tdp = &((struct tx_desc *)dp->tx_ring)[start_slot];
	tdp->td_status = own;
E 19
I 19
D 28
	((struct tx_desc *) dp->tx_ring)[start_slot].td_status
D 26
			= LE32(TDES0_OWN);
E 26
I 26
			= LE_32(TDES0_OWN);
E 28
I 28
	TXDESC(dp->tx_ring)[start_slot].td_status = LE_32(TDES0_OWN);
E 28
E 26
E 19

	gem_tx_desc_dma_sync(dp, start_slot, 1, DDI_DMA_SYNC_FORDEV);

E 17
I 11
D 16
	/* for the first descripter */
	tdp = &((struct tx_desc *)dp->tx_ring)[slot];
D 15
	tdp->td_baddr1  = dcp->dmac_address;
	tdp->td_control = dcp->dmac_size | mark | TDES1_FS | TDES1_TCH;
	tdp->td_status  = TDES0_OWN;
E 15
I 15
	ddi_put32(h, &tdp->td_baddr1, dcp->dmac_address);
	ddi_put32(h, &tdp->td_control,
				dcp->dmac_size | mark | TDES1_FS | TDES1_TCH);
	ddi_put32(h, &tdp->td_status, TDES0_OWN);
E 15
D 14
#ifdef IOCACHE
E 14
I 14

E 14
	ddi_dma_sync(dp->desc_dma_handle,
		(off_t)(((caddr_t)tdp) - dp->rx_ring) ,
		sizeof(struct tx_desc), DDI_DMA_SYNC_FORDEV);
D 14
#endif
E 14

I 14

E 16
E 14
E 11
	/* kick Tx engine */
D 16
#ifdef TXTIMEOUT_TEST
E 16
I 16
#ifdef TEST_TXTIMEOUT
E 16
D 3
	if ((tu_send_cnt++ % 100) == 99) {
E 3
I 3
	if ((tu_send_cnt % 100) == 99) {
I 16
D 28
		/* do nothing */
E 28
I 28
		return;
E 28
E 16
E 3
	}
I 16
D 28
	else
E 28
E 16
#endif
D 10
	OUTL(dp, TDR, 0xffffffff);

E 10
I 10
D 17
	if (dp->nic_active) {
E 17
I 17
D 28
	if (dp->mac_active) {
E 17
		OUTL(dp, TDR, 0xffffffff);
	}
E 28
I 28
	OUTL(dp, TDR, 0xffffffffU);
E 28
E 10
I 3
D 17
#ifdef DEBUG_LEVEL
	tu_send_cnt++;
#endif
E 3
	return frags;
E 17
}

D 17
static int
tu_rx_desc_write2(struct gem_dev *dp, uint_t slot,
E 17
I 17
static void
tu_rx_desc_write2(struct gem_dev *dp, int slot,
E 17
D 28
	    ddi_dma_cookie_t *dmacookie, int frags)
E 28
I 28
	ddi_dma_cookie_t *dmacookie, int frags)
E 28
{
D 28
	struct rx_desc		*rdp;
	int			i;
E 28
I 28
	int		i;
	uint32_t	addr;
	uint32_t	control;
	struct rx_desc	*rdp;
E 28
I 15
D 17
	ddi_acc_handle_t	h = dp->desc_acc_handle;
E 17
E 15

#if DEBUG_LEVEL > 2
	cmn_err(CE_CONT,
D 7
		"%s: tu_rx_desc_write seqnum: %d, slot %d, frags: %d",
		dp->name, dp->rx_desc_tail, slot, frags);
E 7
I 7
D 11
		"%s: time:%d tu_rx_desc_write seqnum: %d, slot %d, frags: %d",
E 11
I 11
D 28
		"!%s: time:%d tu_rx_desc_write seqnum: %d, slot %d, frags: %d",
E 11
D 17
		dp->name, ddi_get_lbolt(), dp->rx_desc_tail, slot, frags);
E 17
I 17
		dp->name, ddi_get_lbolt(), dp->rx_active_tail, slot, frags);
E 28
I 28
	    "!%s: time:%d %s: seqnum: %d, slot %d, frags %d",
	    dp->name, ddi_get_lbolt(), __func__,
	    dp->rx_active_tail, slot, frags);
E 28
E 17
E 7
	for (i = 0; i < frags; i++) {
D 11
		cmn_err(CE_CONT, "%d: addr: 0x%x, len: 0x%x",
E 11
I 11
		cmn_err(CE_CONT, "!%d: addr: 0x%x, len: 0x%x",
E 11
D 28
			i, dmacookie[i].dmac_address, dmacookie[i].dmac_size);
E 28
I 28
		    i, dmacookie[i].dmac_address, dmacookie[i].dmac_size);
E 28
	}
#endif
	/*
	 * write a RX descriptor
	 */
D 28
	rdp = &((struct rx_desc *)dp->rx_ring)[slot];
E 28
I 28
	rdp = &RXDESC(dp->rx_ring)[slot];
	control = dmacookie[0].dmac_size;
E 28
	if (frags == 2) {
D 15
		rdp->rd_baddr2  = (uint32_t)dmacookie[1].dmac_address;
D 14
		rdp->rd_control = dmacookie[1].dmac_size << RDES1_RBS2_SHIFT
				| dmacookie[0].dmac_size
E 14
I 14
		rdp->rd_control = (dmacookie[1].dmac_size << RDES1_RBS2_SHIFT)
E 15
I 15
D 16
		ddi_put32(h, &rdp->rd_baddr2,
				(uint32_t)dmacookie[1].dmac_address);
E 16
I 16
D 17
		ddi_put32(h, &rdp->rd_baddr2, dmacookie[1].dmac_address);
E 16
		ddi_put32(h, &rdp->rd_control,
				(dmacookie[1].dmac_size << RDES1_RBS2_SHIFT)
E 15
				|  dmacookie[0].dmac_size
E 14
D 10
				| (rdp->rd_control & RDES1_RER);
E 10
I 10
D 15
				| (rdp->rd_control & (RDES1_RCH | RDES1_RER));
E 15
I 15
				| (ddi_get32(h, &rdp->rd_control) & (RDES1_RCH | RDES1_RER)));
E 17
I 17
D 26
		rdp->rd_baddr2  = LE32(dmacookie[1].dmac_address);
		rdp->rd_control = LE32(
E 26
I 26
D 28
		rdp->rd_baddr2  = LE_32(dmacookie[1].dmac_address);
		rdp->rd_control = LE_32(
E 26
				  (dmacookie[1].dmac_size << RDES1_RBS2_SHIFT)
				|  dmacookie[0].dmac_size)
D 26
				| (rdp->rd_control & LE32(RDES1_RCH | RDES1_RER));
E 26
I 26
				| (rdp->rd_control & LE_32(RDES1_RCH | RDES1_RER));
E 28
I 28
		addr = dmacookie[1].dmac_address;
		control |= dmacookie[1].dmac_size << RDES1_RBS2_SHIFT;
		rdp->rd_baddr2 = LE_32(addr);
#ifdef DEBUG
E 28
E 26
E 17
E 15
E 10
	} else {
		ASSERT(frags == 1);
I 10
D 14
#ifdef SANITY
E 14
I 14
D 28
#ifdef NEVER
E 14
E 10
D 15
		rdp->rd_baddr2  = 0;
E 15
I 15
D 17
		ddi_put32(h, &rdp->rd_baddr2, 0);
E 17
I 17
		rdp->rd_baddr2 = 0;
E 28
I 28
		/* EMPTY */
E 28
E 17
E 15
I 10
#endif
E 10
D 15
		rdp->rd_control = dmacookie[0].dmac_size 
D 10
				| (rdp->rd_control & RDES1_RER);
E 10
I 10
				| (rdp->rd_control & (RDES1_RCH | RDES1_RER));
E 15
I 15
D 17
		ddi_put32(h, &rdp->rd_control, dmacookie[0].dmac_size 
				| (rdp->rd_control & (RDES1_RCH | RDES1_RER)));
E 17
I 17
D 26
		rdp->rd_control = LE32(dmacookie[0].dmac_size)
E 26
I 26
D 28
		rdp->rd_control = LE_32(dmacookie[0].dmac_size)
E 26
				| (rdp->rd_control &
D 26
					LE32(RDES1_RCH | RDES1_RER));
E 26
I 26
					LE_32(RDES1_RCH | RDES1_RER));
E 28
E 26
E 17
E 15
E 10
	}
D 15
	rdp->rd_baddr1 = (uint32_t)dmacookie[0].dmac_address;
	rdp->rd_status = RDES0_OWN;
E 15
I 15
D 16
	ddi_put32(h, &rdp->rd_baddr1, (uint32_t)dmacookie[0].dmac_address);
E 16
I 16
D 17
	ddi_put32(h, &rdp->rd_baddr1, dmacookie[0].dmac_address);
E 16
	ddi_put32(h, &rdp->rd_status, RDES0_OWN);
E 15
D 6

E 6
I 6
D 14
#ifdef IOCACHE
E 14
I 14

E 14
	ddi_dma_sync(dp->desc_dma_handle,
		(off_t)(((caddr_t)rdp) - dp->rx_ring) ,
		sizeof(struct rx_desc), DDI_DMA_SYNC_FORDEV);
D 14
#endif
E 14
I 14

E 14
E 6
	return 1;
E 17
I 17
D 26
	rdp->rd_baddr1 = LE32(dmacookie[0].dmac_address);
	rdp->rd_status = LE32(RDES0_OWN);
E 26
I 26
D 28
	rdp->rd_baddr1 = LE_32(dmacookie[0].dmac_address);
E 28
I 28
	rdp->rd_control = LE_32(control)
	    | (rdp->rd_control & LE_32(RDES1_RCH | RDES1_RER));
	addr = dmacookie[0].dmac_address;
	rdp->rd_baddr1 = LE_32(addr);
E 28
	rdp->rd_status = LE_32(RDES0_OWN);
E 26
E 17
}
I 16

E 16
D 10

static int
tu_rx_desc_write1(struct gem_dev *dp, uint_t slot,
	    ddi_dma_cookie_t *dmacookie, int frags)
{
	struct rx_desc		*rdp;
	int			i;

#if DEBUG_LEVEL > 2
	cmn_err(CE_CONT,
D 7
		"%s: tu_rx_desc_write1 seqnum: %d, slot %d, frags: %d",
		dp->name, dp->rx_desc_tail, slot, frags);
E 7
I 7
		"%s: time:%d tu_rx_desc_write1 seqnum: %d, slot %d, frags: %d",
		dp->name, ddi_get_lbolt(), dp->rx_desc_tail, slot, frags);
E 7
	for (i = 0; i < frags; i++) {
		cmn_err(CE_CONT, "%d: addr: 0x%x, len: 0x%x",
			i, dmacookie[i].dmac_address, dmacookie[i].dmac_size);
	}
#endif
	ASSERT(frags == 1);

	/*
	 * write a RX descriptor
	 */
	rdp = &((struct rx_desc *)dp->rx_ring)[slot];
	rdp->rd_control = RDES1_RCH | dmacookie->dmac_size;
I 9
#ifdef DEBUG_LEVEL
	rdp->rd_baddr1  = (uint32_t)dmacookie->dmac_address
			+ dp->gc.gc_rx_header_len;
#else
E 9
	rdp->rd_baddr1  = (uint32_t)dmacookie->dmac_address;
I 9
#endif
E 9
	rdp->rd_status  = RDES0_OWN;
D 6

E 6
I 6
#ifdef IOCACHE
	ddi_dma_sync(dp->desc_dma_handle,
		(off_t)(((caddr_t)rdp) - dp->rx_ring) ,
		sizeof(struct rx_desc), DDI_DMA_SYNC_FORDEV);
#endif
E 6
	return 1;
}

E 10
static uint_t
tu_tx_desc_stat(struct gem_dev *dp, int slot, int ndesc)
{
D 7
	struct tx_desc		*tdp;
	uint32_t		status;
	uint32_t		errbits;
	uint_t			ret;
	int			cols;
	struct tu_chip_state	*lp = (struct tu_chip_state *)dp->private;
E 7
I 7
D 15
	struct tx_desc	*tdp;
	uint32_t	status;
	uint32_t	errbits;
	uint_t		ret;
	int		cols;
	struct tu_dev	*lp = (struct tu_dev *)dp->private;
E 15
I 15
	struct tx_desc		*tdp;
	uint32_t		status;
I 28
	uint32_t		control;
E 28
D 17
	uint32_t		errbits;
E 17
	uint_t			ret;
	int			cols;
D 28
	struct tu_dev		*lp = (struct tu_dev *)dp->private;
E 28
I 28
	struct tu_dev		*lp = dp->private;
E 28
D 17
	ddi_acc_handle_t	h = dp->desc_acc_handle;
E 17
E 15
E 7

	/*
D 29
	 * check the last fragment
E 29
I 29
	 * transmit status will be remain in the last fragment.
E 29
	 */
D 28
	tdp = &((struct tx_desc *)dp->tx_ring)[
			SLOT(slot + ndesc - 1, TX_RING_SIZE)];
E 28
I 28
	tdp = &TXDESC(dp->tx_ring)[SLOT(slot + ndesc - 1, TX_RING_SIZE)];
E 28
I 6
D 14
#ifdef IOCACHE
E 14
I 14

E 14
D 17
	ddi_dma_sync(dp->desc_dma_handle,
		(off_t)(((caddr_t)tdp) - dp->rx_ring) ,
		sizeof(struct tx_desc), DDI_DMA_SYNC_FORKERNEL);
E 17
I 17
D 26
	status = LE32(tdp->td_status);
E 26
I 26
D 28
	status = LE_32(tdp->td_status);
E 28
I 28
D 29
	/* don't use LE_32() directly to read descriptors, it is NOT atomic */
E 29
I 29
	/*
	 * don't use LE_32() directly to read descriptors,
	 * it may NOT be atomic.
	 */
E 29
	status = tdp->td_status;
	status = LE_32(status);
I 29
	control = tdp->td_control;
	control = LE_32(control);
E 29
E 28
E 26
E 17
D 14
#endif
E 14
I 14

E 14
E 6
D 15
	status = tdp->td_status;
E 15
I 15
D 17
	status = ddi_get32(h, &tdp->td_status);
E 15

E 17
#if DEBUG_LEVEL > 2
	if (ndesc > 0) {
		int	i;
D 7
		cmn_err(CE_CONT, "%s: tu_tx_desc_stat: slot:%d ndesc:%d",
				dp->name, slot, ndesc);
E 7
I 7
		cmn_err(CE_CONT,
D 11
			"%s: time:%d tu_tx_desc_stat: slot:%d ndesc:%d sr:%b",
E 11
I 11
D 28
			"!%s: time:%d tu_tx_desc_stat: slot:%d ndesc:%d sr:%b",
E 11
D 17
				dp->name, ddi_get_lbolt(), slot, ndesc, INL(dp, SR), SR_BITS);
E 17
I 17
				dp->name, ddi_get_lbolt(),
				slot, ndesc, INL(dp, SR), SR_BITS);
E 28
I 28
		    "!%s: time:%d %s: slot:%d ndesc:%d sr:%b",
		    dp->name, ddi_get_lbolt(), __func__,
		    slot, ndesc, INL(dp, SR), SR_BITS);
E 28
E 17
E 7
		for (i = 0; i < ndesc; i++) {
			struct tx_desc	*tp;

D 28
			tp = &((struct tx_desc *)dp->tx_ring)[
						SLOT(slot + i, TX_RING_SIZE)];
E 28
I 28
			tp = &TXDESC(dp->tx_ring)[SLOT(slot + i, TX_RING_SIZE)];
E 28
D 11
			cmn_err(CE_CONT, "%d: buf1(0x%x, %d), buf2(0x%x, %d), tsr: %b tcr: %b",
E 11
I 11
D 17
			cmn_err(CE_CONT, "!%d: buf1(0x%x, %d), buf2(0x%x, %d), tsr: %b tcr: %b",
E 17
I 17
D 25
			cmn_err(CE_CONT, "!%d: buf1(0x%x, %d), buf2(0x%x, %d),
				tsr: %b tcr: %b",
E 25
I 25
			cmn_err(CE_CONT,
D 28
			"!%d: buf1(0x%x, %d), buf2(0x%x, %d), tsr: %b tcr: %b",
E 28
I 28
			    "!%d: buf1(0x%x, %d), buf2(0x%x, %d),"
			    " tsr: %b tcr: %b",
E 28
E 25
E 17
E 11
			    i,
D 15
			    tp->td_baddr1,
			    tp->td_control & TDES1_TBS1,
			    tp->td_baddr2,
			    (tp->td_control & TDES1_TBS2) >> TDES1_TBS2_SHIFT,
			    tp->td_status, TSR_BITS,
			    tp->td_control, TCR_BITS);
E 15
I 15
D 17
			    ddi_get32(h, &tp->td_baddr1),
			    ddi_get32(h, &tp->td_control) & TDES1_TBS1,
			    ddi_get32(h, &tp->td_baddr2),
			    (ddi_get32(h, &tp->td_control) & TDES1_TBS2) >> TDES1_TBS2_SHIFT,
			    ddi_get32(h, &tp->td_status), TSR_BITS,
			    ddi_get32(h, &tp->td_control), TCR_BITS);
E 17
I 17
D 26
			    LE32(tp->td_baddr1),
			    LE32(tp->td_control) & TDES1_TBS1,
			    LE32(tp->td_baddr2),
			    (LE32(tp->td_control) & TDES1_TBS2) >> TDES1_TBS2_SHIFT,
			    LE32(tp->td_status), TSR_BITS,
			    LE32(tp->td_control), TCR_BITS);
E 26
I 26
			    LE_32(tp->td_baddr1),
			    LE_32(tp->td_control) & TDES1_TBS1,
			    LE_32(tp->td_baddr2),
D 28
			    (LE_32(tp->td_control) & TDES1_TBS2) >> TDES1_TBS2_SHIFT,
E 28
I 28
			    (LE_32(tp->td_control) & TDES1_TBS2)
			    >> TDES1_TBS2_SHIFT,
E 28
			    LE_32(tp->td_status), TSR_BITS,
			    LE_32(tp->td_control), TCR_BITS);
E 26
E 17
E 15
		}
	}
#endif
D 9

E 9
D 28
	if ((status & TDES0_OWN) != 0) {
E 28
I 28
	if (status & TDES0_OWN) {
E 28
		/* not transmitted yet */
D 17
		return 0;
E 17
I 17
		return (0);
E 17
	}

	ret = GEM_TX_DONE;

I 28
D 29
	/* don't use LE_32() directly to read descriptors, it is NOT atomic */
	control = tdp->td_control;
	control = LE_32(control);

E 28
D 2
	/*
	 * Ignore lost carrier for AN983 in half duplex
	 */
E 2
D 17
	errbits = TDES0_TO | TDES0_LC | TDES0_EC | TDES0_UF;
D 9
#if 1
D 2
	if (!(lp->hw_info->chip_type == CHIP_AN983 && !dp->full_duplex)) {
E 2
I 2
D 5
	if (!(lp->hw_info->chip_type == CHIP_CENTAUR && !dp->full_duplex)) {
		/*
		 * Ignore lost carrier errors for AN983 in half duplex
		 */
E 2
		errbits |= TDES0_LO | TDES0_NC;
E 5
I 5
	if (!dp->full_duplex) {
		/* check carrier error for half duplex except AN983 */
		if (lp->hw_info->chip_type != CHIP_CENTAUR) {
			errbits |= TDES0_LO | TDES0_NC;
		}
E 9
I 9
	if (!(lp->hw_info->chip_type == CHIP_CENTAUR && !dp->full_duplex)) {
E 17
I 17
	if ((status & lp->tx_errbits) == 0) {
E 29
I 29
	if ((status & lp->tx_errbits) == 0 && (control & TDES1_SETF) == 0) {
E 29
E 17
		/*
D 17
		 * Ignore lost carrier errors for AN983 in half duplex
		 */
		errbits |= TDES0_LO | TDES0_NC;
E 9
E 5
	}
D 9
#else
	errbits |= TDES0_LO | TDES0_NC;
#endif
D 2
	if ((lp->nar & NAR_SQE) == 0) {
E 2
I 2
	if (lp->port == PORT_SYM && (lp->nar & NAR_SQE) == 0) {
E 9
I 9
	if ((lp->nar & NAR_SQE) == 0) {
E 9
E 2
		errbits |= TDES0_HF;
	}

	if ((status & errbits) == 0) {
I 9
		/*
E 17
		 * No error detected on transmitting normal packets.
		 */
E 9
		if (!dp->full_duplex) {
I 9
			/*
			 * Update statistics on collisions and deferrals
			 */
E 9
			cols = (status & TDES0_CC) >> TDES0_CC_SHIFT;

			if (cols > 0) {
				dp->stats.collisions += cols;
				if (cols == 1) {
					dp->stats.first_coll++;
D 28
				} else /* if (cols > 1)*/ {
E 28
I 28
				} else /* if (cols > 1) */ {
E 28
					dp->stats.multi_coll++;
				}
D 28
			}
			else if ((status & TDES0_DE) != 0) {
E 28
I 28
			} else if (status & TDES0_DE) {
E 28
				dp->stats.defer++;
			}
		}
D 28
	}
D 15
	else if (status == 0x7fffffff && (tdp->td_control & TDES1_SETF) != 0) {
E 15
I 15
D 16
	else if (status == 0x7fffffff && (ddi_get32(h, &tdp->td_control) & TDES1_SETF) != 0) {
E 16
I 16
	else if (status == 0x7fffffff &&
D 17
		 (ddi_get32(h, &tdp->td_control) & TDES1_SETF) != 0) {
E 17
I 17
D 26
		 (LE32(tdp->td_control) & TDES1_SETF) != 0) {
E 26
I 26
		 (LE_32(tdp->td_control) & TDES1_SETF) != 0) {
E 28
I 28
	} else if (status == 0x7fffffff && (control & TDES1_SETF)) {
E 28
E 26
E 17
E 16
E 15
		/*
		 * Setup frame was processed successfully, do nothing.
		 */
D 28
	}
	else {
D 2
		DPRINTF(1,
E 2
I 2
D 9
		DPRINTF(2,
E 9
I 9
D 10
		DPRINTF(1,
E 10
I 10
D 17
		DPRINTF(2,
E 17
I 17
		DPRINTF(0,
E 17
E 10
E 9
E 2
			(CE_CONT,
			"!%s: tx error: slot:%d status:%b tcr:%b errbits:%b",
			dp->name, slot,
D 15
			status, TSR_BITS, tdp->td_control, TCR_BITS,
E 15
I 15
			status, TSR_BITS,
D 17
			ddi_get32(h, &tdp->td_control), TCR_BITS,
E 15
			errbits, TSR_BITS));
E 17
I 17
D 26
			LE32(tdp->td_control), TCR_BITS,
E 26
I 26
			LE_32(tdp->td_control), TCR_BITS,
E 26
			lp->tx_errbits, TSR_BITS));
E 28
I 28
		/* EMPTY */
	} else {
		DPRINTF(0, (CE_CONT,
		    "!%s: tx error: slot:%d status:%b tcr:%b errbits:%b",
		    dp->name, slot,
		    status, TSR_BITS,
		    control, TCR_BITS,
		    lp->tx_errbits, TSR_BITS));
E 28
E 17
I 10
		DPRINTF(2, (CE_CONT, "! csr6: %b", lp->nar, CSR6BITS));
E 10

		dp->stats.errxmt++;

D 28
		if ((status & (TDES0_NC | TDES0_LO | TDES0_TO)) != 0) {
E 28
I 28
		if (status & (TDES0_NC | TDES0_LO | TDES0_TO)) {
E 28
			dp->stats.nocarrier++;
D 28
		}
		if ((status & TDES0_LC) != 0) {
E 28
I 28
		} else if (status & TDES0_LC) {
E 28
			dp->stats.xmtlatecoll++;
D 28
		}
		if ((status & TDES0_UF) != 0) {
E 28
I 28
		} else if (status & TDES0_UF) {
E 28
			dp->stats.underflow++;
D 28
		}
		if ((!dp->full_duplex) && (status & TDES0_EC) != 0) {
E 28
I 28
		} else if ((!dp->full_duplex) && (status & TDES0_EC)) {
E 28
			dp->stats.excoll++;
			dp->stats.collisions += 16;
		}
	}

D 17
	return ret;
E 17
I 17
	return (ret);
E 17
}

I 25
#ifdef DEBUG_LEVEL
static void
tu_dump_packet(struct gem_dev *dp, uint8_t *bp, int n)
{
	int	i;

D 28
	for (i=0; i < n; i += 8, bp += 8) {
		cmn_err(CE_CONT, "%02x %02x %02x %02x %02x %02x %02x %02x",
		bp[0], bp[1], bp[2], bp[3], bp[4], bp[5], bp[6], bp[7]);
E 28
I 28
	for (i = 0; i < n; i += 8, bp += 8) {
		cmn_err(CE_CONT, "!%02x %02x %02x %02x %02x %02x %02x %02x",
		    bp[0], bp[1], bp[2], bp[3], bp[4], bp[5], bp[6], bp[7]);
E 28
	}
}
#endif

E 25
D 16
static uint_t
E 16
I 16
static uint64_t
E 16
tu_rx_desc_stat(struct gem_dev *dp, int slot, int ndesc)
{
D 15
	struct rx_desc	*rdp;
	uint32_t	rsr;
D 9
	uint_t		ret;
E 9
	uint32_t	rxlen;
I 9
	struct tu_dev	*lp = (struct tu_dev *)dp->private;
E 15
I 15
	struct rx_desc		*rdp;
	uint32_t		rsr;
	uint32_t		rxlen;
D 28
	struct tu_dev		*lp = (struct tu_dev *)dp->private;
E 28
I 28
	struct tu_dev		*lp = dp->private;
E 28
D 17
	ddi_acc_handle_t	h = dp->desc_acc_handle;
E 17
E 15
E 9

	/* ack to interrupt */

D 28
	rdp = &((struct rx_desc *)dp->rx_ring)[slot];
E 28
I 28
	rdp = &RXDESC(dp->rx_ring)[slot];
E 28
I 6
D 14
#ifdef IOCACHE
E 14
I 14

E 14
D 17
	ddi_dma_sync(dp->desc_dma_handle,
		(off_t)(((caddr_t)rdp) - dp->rx_ring) ,
		sizeof(struct rx_desc), DDI_DMA_SYNC_FORKERNEL);
D 14
#endif
E 14
I 14

E 14
E 6
D 15
	rsr = rdp->rd_status;
E 15
I 15
	rsr = ddi_get32(h, &rdp->rd_status);
E 17
I 17
D 26
	rsr = LE32(rdp->rd_status);
E 26
I 26
D 28
	rsr = LE_32(rdp->rd_status);
E 28
I 28
	/* don't use LE_32() directly to read descriptors, it is NOT atomic */
	rsr = rdp->rd_status;
	rsr = LE_32(rsr);

E 28
E 26
E 17
E 15
	rxlen = (rsr & RDES0_FL) >> RDES0_FL_SHIFT;
D 9
	ret = GEM_RX_DONE;
E 9

	DPRINTF(2, (CE_CONT,
D 2
		"%s: tu_rx_desc_stat: slot:%d "
E 2
I 2
D 7
		"!%s: tu_rx_desc_stat: slot:%d "
E 7
I 7
D 25
		"!%s: time:%d tu_rx_desc_stat: slot:%d "
E 25
I 25
D 28
		"!%s: time:%d %s: slot:%d "
E 25
E 7
E 2
		"buf1(0x%x, %d), buf2(0x%x, %d) rsr 0x%b",
D 7
		dp->name, slot,
E 7
I 7
D 25
		dp->name, ddi_get_lbolt(), slot,
E 25
I 25
		dp->name, ddi_get_lbolt(), __func__, slot,
E 25
E 7
D 15
		rdp->rd_baddr1,
		rdp->rd_control & RDES1_RBS1,
		rdp->rd_baddr2,
		(rdp->rd_control & RDES1_RBS2) >> RDES1_RBS2_SHIFT,
		rdp->rd_status, RSR_BITS));
E 15
I 15
D 17
		ddi_get32(h, &rdp->rd_baddr1),
		ddi_get32(h, &rdp->rd_control) & RDES1_RBS1,
		ddi_get32(h, &rdp->rd_baddr2),
		(ddi_get32(h, &rdp->rd_control) & RDES1_RBS2)
E 17
I 17
D 26
		LE32(rdp->rd_baddr1),
		LE32(rdp->rd_control) & RDES1_RBS1,
		LE32(rdp->rd_baddr2),
		(LE32(rdp->rd_control) & RDES1_RBS2)
E 26
I 26
		LE_32(rdp->rd_baddr1),
		LE_32(rdp->rd_control) & RDES1_RBS1,
		LE_32(rdp->rd_baddr2),
		(LE_32(rdp->rd_control) & RDES1_RBS2)
E 26
E 17
						>> RDES1_RBS2_SHIFT,
D 17
		ddi_get32(h, &rdp->rd_status), RSR_BITS));
E 17
I 17
D 26
		LE32(rdp->rd_status), RSR_BITS));
E 26
I 26
		LE_32(rdp->rd_status), RSR_BITS));
E 28
I 28
	    "!%s: time:%d %s: slot:%d buf1(0x%x, %d), buf2(0x%x, %d) rsr 0x%b",
	    dp->name, ddi_get_lbolt(), __func__, slot,
	    LE_32(rdp->rd_baddr1),
	    LE_32(rdp->rd_control) & RDES1_RBS1,
	    LE_32(rdp->rd_baddr2),
	    (LE_32(rdp->rd_control) & RDES1_RBS2) >> RDES1_RBS2_SHIFT,
	    LE_32(rdp->rd_status), RSR_BITS));
E 28
E 26
E 17
E 15

D 28
	if ((rsr & RDES0_OWN) != 0) {
E 28
I 28
	if (rsr & RDES0_OWN) {
E 28
D 29
		/* the end of received packet */
E 29
I 29
		/* the end of received packets */
E 29
D 17
		return 0;
E 17
I 17
		return (0);
E 17
	}

	if ((rsr & (RDES0_FS | RDES0_LS)) != (RDES0_FS | RDES0_LS)) {
I 29
		/* big packet */

E 29
D 9
		/* big packet, ignore this fragment */
		dp->stats.errrcv++;
		dp->stats.frame_too_long++;
D 2
		DPRINTF(0, (CE_CONT, "%s: exceed buffer size", dp->name));
E 2
I 2
		DPRINTF(0, (CE_CONT, "!%s: exceed buffer size", dp->name));
E 2

E 9
D 17
		DPRINTF(0, (CE_CONT,
E 17
I 17
D 25
		DPRINTF(1, (CE_CONT,
E 17
D 2
			"%s: tu_rx_desc_stat: slot:%d "
E 2
I 2
			"!%s: tu_rx_desc_stat: slot:%d "
E 25
I 25
		DPRINTF(0, (CE_CONT,
D 28
			"!%s: %s: slot:%d "
E 25
E 2
			"buf1(0x%x, %d), buf2(0x%x, %d) rsr 0x%b",
D 25
			dp->name, slot,
E 25
I 25
			dp->name, __func__, slot,
E 25
D 15
			rdp->rd_baddr1,
			rdp->rd_control & RDES1_RBS1,
			rdp->rd_baddr2,
			(rdp->rd_control & RDES1_RBS2) >> RDES1_RBS2_SHIFT,
E 15
I 15
D 17
			ddi_get32(h, &rdp->rd_baddr1),
			ddi_get32(h, &rdp->rd_control) & RDES1_RBS1,
			ddi_get32(h, &rdp->rd_baddr2),
			(ddi_get32(h, &rdp->rd_control) & RDES1_RBS2)
E 17
I 17
D 26
			LE32(rdp->rd_baddr1),
			LE32(rdp->rd_control) & RDES1_RBS1,
			LE32(rdp->rd_baddr2),
			(LE32(rdp->rd_control) & RDES1_RBS2)
E 26
I 26
			LE_32(rdp->rd_baddr1),
			LE_32(rdp->rd_control) & RDES1_RBS1,
			LE_32(rdp->rd_baddr2),
			(LE_32(rdp->rd_control) & RDES1_RBS2)
E 26
E 17
							>> RDES1_RBS2_SHIFT,
E 15
D 2
			rdp->rd_status, RSR_BITS));
E 2
I 2
			rsr, RSR_BITS));
E 2
D 9

		return GEM_RX_DONE | GEM_RX_ERR;
E 9
I 9
		
E 28
I 28
		    "!%s: %s: slot:%d "
		    "buf1(0x%x, %d), buf2(0x%x, %d) rsr 0x%b",
		    dp->name, __func__, slot,
		    LE_32(rdp->rd_baddr1),
		    LE_32(rdp->rd_control) & RDES1_RBS1,
		    LE_32(rdp->rd_baddr2),
		    (LE_32(rdp->rd_control) & RDES1_RBS2) >> RDES1_RBS2_SHIFT,
		    rsr, RSR_BITS));

E 28
D 29
		if ((rsr & RDES0_LS) == 0) {
			/* rx status is invalid for the fragment */
D 17
			return GEM_RX_DONE | GEM_RX_ERR;
E 17
I 17
			return (GEM_RX_DONE | GEM_RX_ERR);
E 29
I 29
		if (rsr & RDES0_FS) {
			DPRINTF(1, (CE_CONT,
			    "!%s: exceed buffer size", dp->name));
			dp->stats.frame_too_long++;
E 29
E 17
		}
D 29
		/* big packet, this is not last fragment */
D 17
		DPRINTF(0, (CE_CONT, "!%s: exceed buffer size", dp->name));
E 17
I 17
		DPRINTF(1, (CE_CONT, "!%s: exceed buffer size", dp->name));
E 17
I 11
		rsr |= RDES0_ES | RDES0_TL;
E 29
I 29
		return (GEM_RX_DONE | GEM_RX_ERR);
E 29
E 11
E 9
	}

D 19
	if ((rsr & RDES0_ES) != 0) {
E 19
I 19
#define	RDES0_ES_VLAN	\
	(RDES0_DE | RDES0_RF | RDES0_CS | RDES0_RW | RDES0_CE | RDES0_OF)

D 26
	if ((rsr & RDES0_ES_VLAN) != 0) {
E 26
I 26
	if (rsr & RDES0_ES_VLAN) {
E 26
E 19
		/* error packet */
		dp->stats.errrcv++;
D 26
		if ((rsr & RDES0_DE) != 0) {
E 26
I 26
		if (rsr & RDES0_DE) {
E 26
D 28
			cmn_err(CE_WARN,
D 14
			"%s: tu_rx_desc_stat: descriptor error", dp->name);
E 14
I 14
D 25
			"%s: tu_rx_desc_stat: descriptor error rsr:%b",
D 15
			dp->name, rdp->rd_status, RSR_BITS);
E 15
I 15
D 17
			dp->name, ddi_get32(h, &rdp->rd_status), RSR_BITS);
E 17
I 17
			dp->name, LE32(rdp->rd_status), RSR_BITS);
E 25
I 25
D 26
			"%s: %s: descriptor error rsr:%b",
			dp->name, __func__, LE32(rdp->rd_status), RSR_BITS);
E 26
I 26
			"%s: %s: descriptor error rsr:0x%b",
			dp->name, __func__, LE_32(rdp->rd_status), RSR_BITS);
E 26
E 25
E 17
E 15
E 14
		}
D 26
		if ((rsr & RDES0_RF) != 0) {
E 26
I 26
		else if (rsr & RDES0_RF) {
E 28
I 28
			cmn_err(CE_WARN, "!%s: %s: descriptor error rsr:0x%b",
			    dp->name, __func__,
			    LE_32(rdp->rd_status), RSR_BITS);
		} else if (rsr & RDES0_RF) {
E 28
E 26
			dp->stats.runt++;
D 28
		}
D 26
		if ((rsr & RDES0_TL) != 0) {
E 26
I 26
		else if (rsr & RDES0_TL) {
E 28
I 28
		} else if (rsr & RDES0_TL) {
E 28
E 26
			dp->stats.frame_too_long++;
D 28
		}
D 26
		if ((rsr & RDES0_CE) != 0) {
E 26
I 26
		else if (rsr & RDES0_CE) {
E 28
I 28
		} else if (rsr & RDES0_CE) {
E 28
E 26
			dp->stats.crc++;
D 28
		}
D 26
		if ((rsr & RDES0_OF) != 0) {
E 26
I 26
		else if (rsr & RDES0_OF) {
E 28
I 28
		} else if (rsr & RDES0_OF) {
E 28
E 26
D 11
			dp->stats.overflow++;
E 11
I 11
			switch (lp->hw_info->chip_type) {
			case CHIP_21140:
			case CHIP_21142:
I 26
				dp->stats.rcv_internal_err++;
E 26
				break;
			default:
				dp->stats.overflow++;
				break;
			}
E 11
D 28
		}
I 26
		else {
E 28
I 28
		} else {
E 28
			dp->stats.rcv_internal_err++;
		}
E 26
D 9
		ret |= GEM_RX_ERR;
E 9
I 9
D 17
		return GEM_RX_DONE | GEM_RX_ERR;
E 17
I 17
		return (GEM_RX_DONE | GEM_RX_ERR);
E 17
E 9
	}
D 9
	return ret | rxlen;
E 9
I 9
D 25

E 25
I 25
#if DEBUG_LEVEL > 3
	tu_dump_packet(dp, dp->rx_buf_head->rxb_buf, rxlen);
#endif
E 25
D 17
	return GEM_RX_DONE | ((rxlen - ETHERFCSL) & GEM_RX_LEN);
E 17
I 17
	return (GEM_RX_DONE | ((rxlen - ETHERFCSL) & GEM_RX_LEN));
E 17
E 9
}
I 28

E 28
D 10

E 10
static void
D 10
tu_tx_desc_init2(struct gem_dev *dp, int slot)
{
	struct tx_desc	*tdp;

	tdp = &((struct tx_desc *)dp->tx_ring)[slot];

	tdp->td_status = 0;
	tdp->td_control = (slot == TX_RING_SIZE - 1) ? TDES1_TER : 0;
I 6
#ifdef IOCACHE
	ddi_dma_sync(dp->desc_dma_handle,
		(off_t)(((caddr_t)tdp) - dp->rx_ring) ,
		sizeof(struct tx_desc), DDI_DMA_SYNC_FORDEV);
#endif
E 6
}

static void
E 10
tu_tx_desc_init1(struct gem_dev *dp, int slot)
{
I 28
	uint32_t		addr;
E 28
D 15
	struct tx_desc	*tdp;
E 15
I 15
	struct tx_desc		*tdp;
D 17
	ddi_acc_handle_t	h = dp->desc_acc_handle;
E 17
E 15

D 28
	tdp = &((struct tx_desc *)dp->tx_ring)[slot];
E 28
I 28
	tdp = &TXDESC(dp->tx_ring)[slot];
E 28

D 28
	/* invalidate this descriptor */
D 15
	tdp->td_status  = 0;
	tdp->td_control = TDES1_TCH;
E 15
I 15
D 17
	ddi_put32(h, &tdp->td_status, 0);
	ddi_put32(h, &tdp->td_control, TDES1_TCH);
E 17
I 17
	tdp->td_status  = (0);
E 28
I 28
	/* invalidate the descriptor */
	tdp->td_status = 0;
E 28
D 26
	tdp->td_control = LE32(TDES1_TCH);
E 26
I 26
	tdp->td_control = LE_32(TDES1_TCH);
E 26
E 17
E 15
I 6
D 10
#ifdef IOCACHE
	ddi_dma_sync(dp->desc_dma_handle,
		(off_t)(((caddr_t)tdp) - dp->rx_ring) ,
		sizeof(struct tx_desc), DDI_DMA_SYNC_FORDEV);
#endif
E 6

	/* link to previous descriptor */
	if (slot == 0) {
		tdp = &((struct tx_desc *)dp->tx_ring)[TX_RING_SIZE];
	}
	tdp--;
E 10
I 10
D 28
	slot = SLOT(slot+1, TX_RING_SIZE);
E 10
D 15
	tdp->td_baddr2 = 
		((uint32_t)dp->tx_ring_dma) + slot*sizeof(struct tx_desc);
E 15
I 15
D 17
	ddi_put32(h, &tdp->td_baddr2,
E 17
I 17
D 26
	tdp->td_baddr2 = LE32(
E 26
I 26
	tdp->td_baddr2 = LE_32(
E 26
E 17
		((uint32_t)dp->tx_ring_dma) + slot*sizeof(struct tx_desc));
E 28
I 28
	slot = SLOT(slot + 1, TX_RING_SIZE);
	addr = slot * sizeof (struct tx_desc) + (uint32_t)dp->tx_ring_dma;
	tdp->td_baddr2 = LE_32(addr);
E 28
E 15
I 6
D 14
#ifdef IOCACHE
E 14
I 14
D 17

E 14
	ddi_dma_sync(dp->desc_dma_handle,
		(off_t)(((caddr_t)tdp) - dp->rx_ring) ,
		sizeof(struct tx_desc), DDI_DMA_SYNC_FORDEV);
E 17
D 14
#endif
E 14
E 6
D 10

E 10
}

static void
tu_rx_desc_init2(struct gem_dev *dp, int slot)
{
I 28
	uint32_t		ctrl;
E 28
D 15
	struct rx_desc	*rdp;
E 15
I 15
	struct rx_desc		*rdp;
D 17
	ddi_acc_handle_t	h = dp->desc_acc_handle;
E 17
E 15

D 28
	rdp = &((struct rx_desc *)dp->rx_ring)[slot];
E 28
I 28
	rdp = &RXDESC(dp->rx_ring)[slot];
E 28

D 15
	rdp->rd_status = 0;
	rdp->rd_control = (slot == RX_RING_SIZE - 1) ? RDES1_RER : 0;
E 15
I 15
D 17
	ddi_put32(h, &rdp->rd_status, 0);
	ddi_put32(h, &rdp->rd_control,
			(slot == RX_RING_SIZE - 1) ? RDES1_RER : 0);
E 15
I 6
D 14
#ifdef IOCACHE
E 14
I 14

E 14
	ddi_dma_sync(dp->desc_dma_handle,
		(off_t)(((caddr_t)rdp) - dp->rx_ring) ,
		sizeof(struct rx_desc), DDI_DMA_SYNC_FORDEV);
E 17
I 17
D 28
	rdp->rd_status  =(0);
D 26
	rdp->rd_control = LE32((slot == RX_RING_SIZE - 1) ? RDES1_RER : 0);
E 26
I 26
	rdp->rd_control = LE_32((slot == RX_RING_SIZE - 1) ? RDES1_RER : 0);
E 28
I 28
	rdp->rd_status = 0;
	ctrl = (slot == RX_RING_SIZE - 1) ? RDES1_RER : 0;
	rdp->rd_control = LE_32(ctrl);
E 28
E 26
E 17
D 14
#endif
E 14
E 6
}

static void
tu_rx_desc_init1(struct gem_dev *dp, int slot)
{
I 28
	uint32_t		addr;
E 28
D 15
	struct rx_desc	*rdp;
E 15
I 15
	struct rx_desc		*rdp;
D 17
	ddi_acc_handle_t	h = dp->desc_acc_handle;
E 17
E 15

D 28
	rdp = &((struct rx_desc *)dp->rx_ring)[slot];
E 28
I 28
	rdp = &RXDESC(dp->rx_ring)[slot];
E 28

	/* invalidate this descriptor */
D 15
	rdp->rd_status  = 0;
	rdp->rd_control = RDES1_RCH;
E 15
I 15
D 17
	ddi_put32(h, &rdp->rd_status, 0);
	ddi_put32(h, &rdp->rd_control, RDES1_RCH);
E 17
I 17
D 28
	rdp->rd_status  = 0;
E 28
I 28
	rdp->rd_status = 0;
E 28
D 26
	rdp->rd_control = LE32(RDES1_RCH);
E 26
I 26
	rdp->rd_control = LE_32(RDES1_RCH);
E 26
E 17
E 15
I 6
D 10
#ifdef IOCACHE
	ddi_dma_sync(dp->desc_dma_handle,
		(off_t)(((caddr_t)rdp) - dp->rx_ring) ,
		sizeof(struct rx_desc), DDI_DMA_SYNC_FORDEV);
#endif
E 6

	/* link to previous descriptor */
	if (slot == 0) {
		rdp = &((struct rx_desc *)dp->rx_ring)[RX_RING_SIZE];
	}
	rdp--;
E 10
I 10
D 28
	slot = SLOT(slot+1, RX_RING_SIZE);
E 10
D 15
	rdp->rd_baddr2 = 
		((uint32_t)dp->rx_ring_dma) + slot*sizeof(struct rx_desc);
E 15
I 15
D 17
	ddi_put32(h, &rdp->rd_baddr2,
		((uint32_t)dp->rx_ring_dma) + slot*sizeof(struct rx_desc));
E 15
I 6
D 14
#ifdef IOCACHE
E 14
I 14

E 14
	ddi_dma_sync(dp->desc_dma_handle,
		(off_t)(((caddr_t)rdp) - dp->rx_ring) ,
		sizeof(struct rx_desc), DDI_DMA_SYNC_FORDEV);
E 17
I 17
	rdp->rd_baddr2 =
D 26
		LE32(((uint32_t)dp->rx_ring_dma) + slot*sizeof(struct rx_desc));
E 26
I 26
	    LE_32(((uint32_t)dp->rx_ring_dma) + slot*sizeof(struct rx_desc));
E 28
I 28
	slot = SLOT(slot + 1, RX_RING_SIZE);
	addr = slot * sizeof (struct rx_desc) + (uint32_t)dp->rx_ring_dma;
	rdp->rd_baddr2 = LE_32(addr);
E 28
E 26
E 17
D 14
#endif
E 14
E 6
}
I 28

E 28
D 10

static void
tu_tx_desc_clean(struct gem_dev *dp, int slot)
{
	struct tx_desc	*tdp;

	tdp = &((struct tx_desc *)dp->tx_ring)[slot];
I 6
#ifdef IOCACHE
	ddi_dma_sync(dp->desc_dma_handle,
		(off_t)(((caddr_t)tdp) - dp->rx_ring) ,
		sizeof(struct tx_desc), DDI_DMA_SYNC_FORKERNEL);
#endif
E 6
	tdp->td_status = 0;
I 6
#ifdef IOCACHE
	ddi_dma_sync(dp->desc_dma_handle,
		(off_t)(((caddr_t)tdp) - dp->rx_ring) ,
		sizeof(struct tx_desc), DDI_DMA_SYNC_FORDEV);
#endif
E 6
}

static void
tu_rx_desc_clean(struct gem_dev *dp, int slot)
{
	struct rx_desc		*rdp;

	rdp = &((struct rx_desc *)dp->rx_ring)[slot];
I 6
#ifdef IOCACHE
	ddi_dma_sync(dp->desc_dma_handle,
		(off_t)(((caddr_t)rdp) - dp->rx_ring) ,
		sizeof(struct rx_desc), DDI_DMA_SYNC_FORKERNEL);
#endif
E 6
	rdp->rd_status = 0;
I 6
#ifdef IOCACHE
	ddi_dma_sync(dp->desc_dma_handle,
		(off_t)(((caddr_t)rdp) - dp->rx_ring) ,
		sizeof(struct rx_desc), DDI_DMA_SYNC_FORDEV);
#endif
E 6
}

E 10
/*
 * Device depend interrupt handler
 */
D 9

E 9
I 9
#ifdef DEBUG_LEVEL
static int	tu_intr_cnt;
#endif
E 9
D 28
static u_int
E 28
I 28
static uint_t
E 28
tu_interrupt(struct gem_dev *dp)
{
	uint32_t	sr;
I 16
D 19
	int		val;
E 19
I 19
	uint32_t	val;
E 19
E 16
D 2
#ifdef notdef
	uint32_t	sr2;
#endif
E 2
D 14
	boolean_t	tx_sched = FALSE;
E 14
I 14
D 28
	u_int		tx_sched = 0;
E 14
D 7
	struct tu_chip_state	*lp = (struct tu_chip_state *)dp->private;
E 7
I 7
	struct tu_dev	*lp = (struct tu_dev *)dp->private;
E 28
I 28
	uint32_t	ier_org;
	uint_t		tx_sched = 0;
	uint32_t	txrx_state;
	struct tu_dev	*lp = dp->private;
E 28
I 9
D 11
	int		loop = 30;
E 11
I 11
D 16
	int		loop = 100;
E 16
E 11
E 9
E 7

D 28
	sr  = INL(dp, SR);
E 28
I 28
	sr = INL(dp, SR);
E 28
I 7

E 7
D 2
#ifdef notdef
	sr2 = INL(dp, SR2_AN);
#endif
E 2
D 9
	if ((sr & OUR_INTR_BITS) == 0) {
E 9
I 9
D 28
	if ((sr & lp->ier) == 0) {
E 28
I 28
	ier_org = lp->ier;
	if ((sr & ier_org) == 0) {
E 28
E 9
		/* Not for us */
I 9
D 16
		OUTL(dp, SR, sr);
E 16
E 9
D 17
		return DDI_INTR_UNCLAIMED;
E 17
I 17
		return (DDI_INTR_UNCLAIMED);
E 17
	}

I 7
D 17
	DPRINTF(2, (CE_CONT, "!%s: time:%d tu_interrupt, sr: %b",
		dp->name, ddi_get_lbolt(), sr, SR_BITS));
E 17
I 17
	DPRINTF(2, (CE_CONT, "!%s: time:%d %s, sr: %b",
D 28
		dp->name, ddi_get_lbolt(), __func__, sr, SR_BITS));
E 28
I 28
	    dp->name, ddi_get_lbolt(), __func__, sr, SR_BITS));
E 28
E 17

I 12
D 28
	/* disable all interrupts */
	OUTL(dp, IER, 0);

E 28
E 12
E 7
D 11
	/* To clear PCI interrupt signal line, mask all interrupts */
	OUTL(dp, IER, 0);
D 7
	OUTL(dp, SR, sr);
E 7
D 2
#ifdef notdef
	OUTL(dp, SR2_AN, sr2);
#endif
	DPRINTF(2, (CE_CONT, "%s: Interrupt, sr: %b", dp->name, sr, SR_BITS));
E 2

E 11
I 2
D 7
	DPRINTF(2, (CE_CONT, "!%s: Interrupt, sr: %b", dp->name, sr, SR_BITS));

E 7
E 2
D 17
	if (!dp->nic_active) {
E 17
I 17
	if (!dp->mac_active) {
E 17
I 7
D 28
		/* clear interrupt */
E 28
I 28
		/* the device is not active */

		/* disable all interrupts */
		lp->ier = 0;
		OUTL(dp, IER, 0);
I 29
		FLSHL(dp, IER);
E 29

		/* clear all interrupts */
E 28
I 11
D 12
		OUTL(dp, IER, 0);
E 12
E 11
D 16
		OUTL(dp, SR, sr);
E 16
I 16
		OUTL(dp, SR, 0x1ffff);
I 29
		FLSHL(dp, SR);
E 29
E 16

E 7
D 28
		/* the device is not active */
E 28
D 17
		return DDI_INTR_CLAIMED;
E 17
I 17
		return (DDI_INTR_CLAIMED);
E 17
	}

I 9
D 16
#ifdef RESET_ON_ERR_TEST
E 16
I 16
#ifdef TEST_RESET_ON_ERR
E 16
D 28
	tu_intr_cnt++;;
E 28
I 28
	tu_intr_cnt++;
E 28
#endif
E 9
D 7
	if ((sr & SR_RCI) != 0) {
		/* packet was received, or receive error happened */
		gem_receive(dp);
	}
E 7
I 7
D 16
	do {
		/* clear interrupt */
I 9
D 11
#ifdef notdef
E 9
		OUTL(dp, SR, sr);
E 7
D 9

E 9
I 9
#else
		OUTL(dp, SR, 0xffffffff);
#endif
E 11
I 11
		OUTL(dp, SR, sr & 0x1ffff);
E 16
I 16
	/* clear interrupt */
	OUTL(dp, SR, sr & 0x1ffff);
E 16
I 14
D 28
#ifdef MAP_MEM
D 16
		INL(dp, SR); /* XXX - flush write buffer */
E 16
I 16
	INL(dp, SR); /* XXX - flush write buffer */
E 16
#endif
E 14
D 16
		sr &= lp->ier;
E 16
I 16
D 17
	sr &= (lp->ier | SR_RCI | SR_TCI);
E 17
I 17
	/*
	 * XXX - don't mask TDU because DM9102 sometimes doen't
	 * raise TCI bit
	 */
	sr &= (lp->ier | SR_RCI | SR_TCI | SR_TDU);
E 28
I 28
	FLSHL(dp, SR);
E 28
E 17
E 16

E 11
E 9
D 7
	if ((sr & (SR_TUF | SR_TJT | SR_TDU | SR_TCI)) != 0) {
		/* packet was transmitted or transmit errpr happened */
		tx_sched = gem_tx_done(dp);
	}
E 7
I 7
D 16
		if ((sr & SR_RDU) != 0) {
			/*
			 * rx descriptor is unavailable.
			 * update missed packet counter
			 */
			tu_get_stats(dp);
E 16
I 16
D 17
#ifdef CONFIG_POLLING
E 17
I 17
D 29
#ifdef GEM_CONFIG_POLLING
E 29
I 29
#ifdef CONFIG_POLLING
E 29
E 17
D 28
	if (lp->timer_resolution != 0 &&
	    dp->speed == GEM_SPD_100 &&
	    dp->poll_interval != lp->last_poll_interval) {
E 28
I 28
	sr &= lp->ier | SR_RCI;
E 28

D 19
		lp->ier |= (SR_RCI | SR_TCI); /* normal mode */

E 19
D 28
		if ((val = dp->poll_interval/lp->timer_resolution) != 0) {
D 19
			/* choose polled mode */
			lp->ier &= ~(SR_RCI | SR_TCI);
E 19
I 19
			/* choose rx polled mode */
E 28
I 28
D 29
	if (lp->timer_resolution &&
E 29
I 29
	if (lp->hw_info->timer_resolution &&
E 29
	    dp->poll_interval != lp->last_poll_interval) {
D 29
		val = dp->poll_interval/lp->timer_resolution;
		val &= ~lp->timer_mask;
E 29
I 29
		val = dp->poll_interval/lp->hw_info->timer_resolution;
		val &= ~lp->hw_info->timer_mask;
E 29
		if (val) {
			/* move to polled mode */
E 28
			lp->ier &= ~SR_RCI;
E 19
			val |= TMR_COM;
I 28
		} else {
			/* return to normal mode */
			lp->ier |= SR_RCI;
E 28
E 16
		}
I 19
D 28
		else {
			lp->ier |= SR_RCI; /* normal mode */
		}
E 28
E 19
I 16
		OUTL(dp, TMR, val);
E 16
E 7

D 7
	/* re-enable all interrupts */
	OUTL(dp, IER, OUR_INTR_BITS);
E 7
I 7
D 9
		if ((sr & (SR_RCI | SR_RDU)) != 0) {
E 9
I 9
D 16
		if ((sr & (SR_RCI | SR_RDU | SR_RWT)) != 0) {
E 9
			/* packet was received, or receive error happened */
			gem_receive(dp);
E 16
I 16
		lp->last_poll_interval = dp->poll_interval;
	}
I 28
#else
	sr &= lp->ier;
E 28
D 17
#endif /* CONFIG_POLLING */
E 17
I 17
D 29
#endif /* GEM_CONFIG_POLLING */
E 29
I 29
#endif /* CONFIG_POLLING */
E 29
E 17
E 16
I 9

D 10
			if (sr & SR_RWT) {
				cmn_err(CE_NOTE,
					"%s: rx watch dog detected",
E 10
I 10
D 16
			if ((sr & SR_RWT) != 0) {
				cmn_err(CE_NOTE, "%s: rx watch dog detected",
E 10
					dp->name);
D 11
				tu_restart_chip(dp);
#ifdef notdef
E 11
				lp->need_to_reset = TRUE;
E 16
I 16
D 26
	if ((sr & SR_RDU) != 0) {
		/*
		 * rx descriptor is unavailable.
		 * update missed packet counter
		 */
		tu_get_stats(dp);
	}

	if ((sr & (SR_RCI | SR_RDU | SR_RWT)) != 0) {
E 26
I 26
	if (sr & (SR_RCI | SR_RDU | SR_RWT)) {
E 26
		/* packet was received, or receive error happened */
D 26
		gem_receive(dp);
E 26
I 26
		(void) gem_receive(dp);
E 26

D 26
		if ((sr & SR_RWT) != 0) {
			cmn_err(CE_NOTE, "%s: rx watch dog detected",
				dp->name);
			lp->need_to_reset = TRUE;
E 26
I 26
		if (sr & SR_RWT) {
			cmn_err(CE_NOTE,
D 28
				"!%s: rx watch dog detected, sr:0x%b, nar:0x%b",
				dp->name, sr, SR_BITS, INL(dp, NAR), CSR6BITS);
E 28
I 28
			    "!%s: rx watch dog detected, sr:0x%b, nar:0x%b",
			    dp->name, sr, SR_BITS, INL(dp, NAR), CSR6BITS);
E 28
			/* need to reset to recover from the error */
			lp->need_to_reset = B_TRUE;
E 26
		}

		if (sr & SR_RDU) {
I 26
D 28
			/*rx descriptor is unavailable.  */

			/* the error will be counted in tu_getstats())*/
E 28
I 28
			/* rx descriptor is unavailable. */
			DPRINTF(0, (CE_NOTE,
			    "!%s: rx descriptors were unavailable, "
			    "sr:0x%b, nar:0x%b",
			    dp->name, sr, SR_BITS, INL(dp, NAR), CSR6BITS));
			/* the error will be counted in tu_getstats()) */
E 28
			tu_get_stats(dp);

E 26
			/* restart Rx */
D 28
			OUTL(dp, RDR, 0xffffffff);
E 28
I 28
			OUTL(dp, RDR, 0xffffffffU);
E 28
E 16
I 11
D 26
#ifdef notdef
D 16
				break;
E 16
I 16
			dp->stats.norcvbuf++;
E 16
E 11
#endif
E 26
D 16
			}
I 11

E 11
			if (lp->rx_delay && (sr & SR_RCI) != 0) {
				switch (lp->hw_info->chip_type) {
				case CHIP_CENTAUR:
				case CHIP_21140:
				case CHIP_21142:
					lp->ier |= SR_GPTT;
					lp->ier &= ~SR_RCI;
					OUTL(dp, TMR, lp->rx_delay);
					break;
				}
			}
			if (sr & SR_RDU) {
				/* restart Rx */
				OUTL(dp, RDR, 0xffffffff);
			}
E 16
E 9
		}
I 16
	}
E 16
E 7

I 7
D 16
		if ((sr & (SR_TUF | SR_TJT | SR_TDU | SR_TCI)) != 0) {
E 16
I 16
D 26
	if ((sr & (SR_TUF | SR_TJT | SR_TDU | SR_TCI)) != 0) {
E 26
I 26
	if (sr & (SR_TUF | SR_TJT | SR_TDU | SR_TCI)) {
E 26
E 16
I 11

E 11
D 16
			/* packet was transmitted or transmit error happened */
D 14
			tx_sched = gem_tx_done(dp);
E 14
I 14
			if (gem_tx_done(dp)) {
				tx_sched = INTR_RESTART_TX;
			}
E 16
I 16
D 29
		/* packet was transmitted or transmit error happened */
E 29
I 29
		/* packets were transmitted or transmit error happened */
E 29
		if (gem_tx_done(dp)) {
			tx_sched = INTR_RESTART_TX;
		}
E 16
E 14
I 9
D 28

I 11
D 16
			if ((sr & SR_TUF) != 0 && (lp->nar & NAR_SF) == 0) {
				uint32_t	tr;
E 16
I 16
D 26
		if ((sr & SR_TUF) != 0 && (lp->nar & NAR_SF) == 0) {
E 26
I 26
		if ((sr & SR_TUF) && (lp->nar & NAR_SF) == 0) {
E 28
I 28
		if (sr & (SR_TUF | SR_TJT)) {
			cmn_err(CE_WARN,
			    "!%s: tx error happened, sr:0x%b, nar:0x%b",
			    dp->name, sr, SR_BITS, INL(dp, NAR), CSR6BITS);
			txrx_state = tu_freeze_chip(dp, NAR_ST | NAR_SR);
		}
		if ((sr & SR_TUF) && (lp->nar & NAR_SF)) {
E 28
E 26
			uint32_t	tr;
E 16

D 16
				tr = ((lp->nar & NAR_TR) >> NAR_TR_SHIFT) + 1;
				if (tr > TR_1024) {
					lp->nar |= NAR_SF;
					if (lp->hw_info->chip_type !=
								CHIP_CENTAUR) {
						OUTL(dp, PAR,
							INL(dp, PAR)&~PAR_BAR);
					}
				} else {
					lp->nar = (lp->nar & ~NAR_TR)
						| (tr << NAR_TR_SHIFT);
E 16
I 16
			tr = ((lp->nar & NAR_TR) >> NAR_TR_SHIFT) + 1;
			if (tr > TR_1024) {
				lp->nar |= NAR_SF;
D 28
				if (lp->hw_info->chip_type !=
							CHIP_CENTAUR) {
E 28
I 28
				if (lp->hw_info->chip_type != CHIP_CENTAUR) {
E 28
					OUTL(dp, PAR,
D 28
						INL(dp, PAR)&~PAR_BAR);
E 28
I 28
					    INL(dp, PAR)&~PAR_BAR);
E 28
E 16
				}
D 16

				UPDATE_NAR(dp, lp->nar & ~(NAR_ST | NAR_SR));
E 16
I 16
			} else {
				lp->nar = (lp->nar & ~NAR_TR)
D 28
					| (tr << NAR_TR_SHIFT);
E 28
I 28
				    | (tr << NAR_TR_SHIFT);
E 28
E 16
			}
D 16
					
E 11
			if ((sr & (SR_TUF | SR_TJT)) != 0) {
				tu_restart_chip(dp);
			}
E 9
		}
E 16

I 9
D 16
		if ((lp->ier & sr & (SR_LC | SR_LNF | SR_ANE)) != 0) {
			/* link changed or autonegotiation done */
			DPRINTF(0, (CE_CONT,
			"!%s: tu_interrupt: link changed/autonego done, sr: %b",
				dp->name, sr, SR_BITS));
			
			gem_mii_link_check(dp);
			lp->ier &= ~(sr & (SR_LC | SR_LNF | SR_ANE));
E 16
I 16
D 28
			UPDATE_NAR(dp, lp->nar & ~(NAR_ST | NAR_SR));
E 28
I 28
			UPDATE_NAR(dp, lp->nar);
E 28
E 16
		}
D 16

		if ((sr & SR_GPTT) != 0) {
			/* rx delay control */
			switch (lp->hw_info->chip_type) {
			case CHIP_CENTAUR:
				lp->ier &= ~SR_GPTT;
				lp->ier |= SR_RCI;
				break;
			}
E 16
I 16
D 28
				
E 28
I 28

E 28
D 26
		if ((sr & (SR_TUF | SR_TJT)) != 0) {
E 26
I 26
		if (sr & (SR_TUF | SR_TJT)) {
E 26
D 28
			tu_restart_chip(dp);
E 28
I 28
			tu_restart_chip(dp, txrx_state);
E 28
E 16
		}
I 16
	}
E 16

I 11
D 16
		if ((sr & SR_AISS) != 0) {
			/* clear all abnormal interrupts again */
			OUTL(dp, SR,
				SR_LC|(0xffff&~(SR_TCI|SR_TDU|SR_RCI|SR_GPTT)));
		}
E 16
I 16
D 28
	if ((lp->ier & sr & (SR_LC | SR_LNF | SR_ANE)) != 0) {
E 28
I 28
	if (sr & (SR_LC | SR_LNF | SR_ANE)) {
E 28
D 29
		/* link changed or autonegotiation done */
E 29
I 29
		/* link status changed or autonegotiation done */
E 29
		DPRINTF(0, (CE_CONT,
D 17
		"!%s: tu_interrupt: link changed/autonego done, sr: %b",
			dp->name, sr, SR_BITS));
E 17
I 17
D 28
			"!%s: %s: link changed/autonego done, sr: %b",
			dp->name, __func__, sr, SR_BITS));
E 17
		
E 28
I 28
		    "!%s: %s: link changed/autonego done, sr: %b",
		    dp->name, __func__, sr, SR_BITS));

E 28
		gem_mii_link_check(dp);
		lp->ier &= ~(sr & (SR_LC | SR_LNF | SR_ANE));
	}
E 16

E 11
E 9
D 16
		sr  = INL(dp, SR);
D 9
	} while ((sr & OUR_INTR_BITS) != 0);
E 9
I 9
D 11
	} while ((sr & lp->ier) != 0 && --loop);
E 11
I 11
	} while ((sr & lp->ier) != 0 && --loop > 0);
E 16
I 16
D 26
	if ((sr & SR_AISS) != 0) {
E 26
I 26
	if (sr & SR_AISS) {
E 26
		/* clear all abnormal interrupts again */
		OUTL(dp, SR,
D 28
			SR_LC|(0xffff&~(SR_TCI|SR_TDU|SR_RCI|SR_GPTT)));
E 28
I 28
		    SR_LC | (0xffff & ~(SR_TCI | SR_TDU | SR_RCI | SR_GPTT)));
		FLSHL(dp, SR);
E 28
	}
E 16
E 11
E 9
D 19

E 19
I 19
D 28
#ifdef MAP_MEM
	/* flush register writing transaction */
E 19
I 9
D 16
#ifdef RESET_ON_ERR_TEST
E 16
I 16
	sr  = INL(dp, SR);
I 19
#endif
E 28
E 19

#ifdef TEST_RESET_ON_ERR
E 16
	if ((tu_intr_cnt++ % 25000) == 249) {
D 26
		lp->need_to_reset = TRUE;
E 26
I 26
		lp->need_to_reset = B_TRUE;
E 26
	}
#endif
D 16

D 11
	if (lp->need_to_reset || loop == 0) {
		cmn_err(CE_NOTE, "%s: resetting the nic",
			dp->name);
E 11
I 11
	if (loop <= 0) {
		lp->need_to_reset = TRUE;
I 12
		lp->ier = 0;
		OUTL(dp, IER, 0);
E 12
		cmn_err(CE_WARN, "%s: interrupts maxmum exceeded", dp->name);
	}

E 16
	if (lp->need_to_reset) {
I 18
D 19
		/* XXX - we cannot keep untransmitted tx buffers */
E 19
I 19
		/*
D 29
		 * XXX - we cannot keep untransmitted tx buffers because
		 * we issue setupframes before the tx buffers on reset.
E 29
I 29
		 * Note - we cannot keep untransmitted tx buffers because
		 * a additional tx buffer to issue a setupframe on reset
		 * is required before we re-transmit the tx buffers.
E 29
		 */
E 19
E 18
D 28
		cmn_err(CE_NOTE, "%s: resetting the nic", dp->name);
E 28
I 28
		cmn_err(CE_NOTE, "!%s: resetting the nic", dp->name);
E 28
E 11
D 18
		mutex_enter(&dp->xmitlock);
D 16
		gem_restart_tx(dp);
E 16
I 16
		gem_restart_nic(dp, TRUE);
E 16
		mutex_exit(&dp->xmitlock);
E 18
I 18
D 26
		gem_restart_nic(dp, FALSE);
E 26
I 26
		gem_restart_nic(dp, 0);
E 26
E 18
D 16
		tx_sched = TRUE;
E 16
I 16
		tx_sched = INTR_RESTART_TX;
E 16
D 26
		lp->need_to_reset = FALSE;
E 26
I 26
		lp->need_to_reset = B_FALSE;
E 26
	}

I 12
D 29
	/* enable interrupts again */
E 29
I 29
	/* change interrupt mask bits if required */
E 29
D 16
	if ((dp->misc_flag & GEM_NOINTR) == 0 && loop > 0) {
E 16
I 16
D 28
	if ((dp->misc_flag & GEM_NOINTR) == 0) {
E 28
I 28
	if ((dp->misc_flag & GEM_NOINTR) == 0 && ier_org != lp->ier) {
E 28
E 16
		OUTL(dp, IER, lp->ier);
	}
E 12
E 9
D 11
	/* re-enable all interrupts */
D 9
	if ((dp->misc_flag & GEM_NOINTR) == 0) {
E 9
I 9
	if ((dp->misc_flag & GEM_NOINTR) == 0 && loop) {
E 9
		OUTL(dp, IER, lp->ier);
	}
I 9
	else {
		OUTL(dp, IER, 0);
	}
E 11
I 11

I 12
D 16

E 16
E 12
E 11
E 9
E 7
D 14
	return DDI_INTR_CLAIMED | (tx_sched ? INTR_RESTART_TX : 0);
E 14
I 14
D 17
	return DDI_INTR_CLAIMED | tx_sched;
E 17
I 17
	return (DDI_INTR_CLAIMED | tx_sched);
E 17
E 14
}

/*
D 14
 * HW depend MII routine
E 14
I 14
 * HW depend MII routines
E 14
 */

D 28
#define MDIO_DELAY(dp)    {INL(dp, SPR);INL(dp, SPR);}
E 28
I 28
#define	MDIO_DELAY(dp)    {(void) INL(dp, SPR); (void) INL(dp, SPR); }
E 28

I 17
static void
tu_mii_sync_null(struct gem_dev *dp)
{
	/* nothing to do */
}

E 17
I 2
/*
 * MII routines using 2114x Serial Port Register.
 */
E 2
static void
tu_mii_sync(struct gem_dev *dp)
{
D 11
	int	i;
E 11
I 11
	int		i;
	uint32_t	dir;
D 28
	struct tu_dev	*lp = (struct tu_dev *)dp->private;
E 28
I 28
	struct tu_dev	*lp = dp->private;
E 28
E 11

I 11
D 29
	dir = (lp->hw_info->chip_type == CHIP_MX987XX) ? SPR_SWC : 0;
E 29
I 29
	dir = lp->hw_info->spr_mbo;
E 29

E 11
D 2
	/* output 35 ones */
	for (i = 0; i < 35; i++) {
E 2
I 2
	/* output 32 ones */
	for (i = 0; i < 32; i++) {
E 2
D 11
		OUTL(dp, SPR, SPR_MDO);
E 11
I 11
		OUTL(dp, SPR, dir | SPR_MDO);
E 11
		MDIO_DELAY(dp);
D 11
		OUTL(dp, SPR, SPR_MDO | SPR_MDC);
E 11
I 11
		OUTL(dp, SPR, dir | SPR_MDO | SPR_MDC);
E 11
		MDIO_DELAY(dp);
	}
I 11
D 28
	OUTL(dp, SPR, dir | SPR_MDO);
E 28
I 28
	/* keep clock signal in high level to save power */
E 28
E 11
}

static uint16_t
D 16
tu_mii_read(struct gem_dev *dp, int reg)
E 16
I 16
tu_mii_read(struct gem_dev *dp, uint_t reg)
E 16
{
	uint32_t	cmd;
D 16
	uint16_t	ret;
E 16
I 16
	uint16_t	ret = 0;
E 16
	int		i;
	uint32_t	data;
I 11
	uint32_t	dir;
	uint32_t	addr;
E 11
D 7
	struct tu_chip_state	*lp = (struct tu_chip_state *)dp->private;
E 7
I 7
D 28
	struct tu_dev	*lp = (struct tu_dev *)dp->private;
E 28
I 28
	struct tu_dev	*lp = dp->private;
E 28
E 7

D 2
	cmd = (6<<(18+5+5)) | (dp->mii_phy_addr<<(18+5)) | (reg<<18);
E 2
I 2
D 11
	cmd = MII_READ_CMD(dp->mii_phy_addr, reg);
E 11
I 11
D 29
	dir = (lp->hw_info->chip_type == CHIP_MX987XX) ? SPR_SWC : 0;
E 29
I 29
	dir = lp->hw_info->spr_mbo;
E 29
	addr = max(dp->mii_phy_addr, 0);
E 11
E 2

D 11
	tu_mii_sync(dp);
E 11
I 11
	cmd = MII_READ_CMD(addr, reg);
E 11

	for (i = 31; i >= 18; i--) {
		data = ((cmd >> i) & 1) << SPR_MDO_SHIFT;
D 11
		OUTL(dp, SPR, data);
E 11
I 11
		OUTL(dp, SPR, dir | data);
E 11
		MDIO_DELAY(dp);
D 11
		OUTL(dp, SPR, data | SPR_MDC);
E 11
I 11
		OUTL(dp, SPR, dir | data | SPR_MDC);
E 11
		MDIO_DELAY(dp);
	}

D 11
	for (i = 17; i >= 0; i--) {
		OUTL(dp, SPR, SPR_MMC);
		MDIO_DELAY(dp);
E 11
I 11
	/* turn around */
D 29
	dir = SPR_MMC;
	if (lp->hw_info->chip_type == CHIP_MX987XX) {
		dir |= SPR_SRC;
	}
E 29
I 29
	dir |= SPR_MMC;
E 29
	OUTL(dp, SPR, dir);

	/* get response from PHY */
	OUTL(dp, SPR, dir | SPR_MDC);
	MDIO_DELAY(dp);
	OUTL(dp, SPR, dir);
D 26
	if ((INL(dp, SPR) & SPR_MDI) != 0) {
E 26
I 26
	if (INL(dp, SPR) & SPR_MDI) {
E 26
D 16
		DPRINTF(1, (CE_CONT, "!%s: phy@%d didn't respond",
E 16
I 16
		DPRINTF(2, (CE_CONT, "!%s: phy@%d didn't respond",
E 16
D 28
			dp->name, addr));
E 28
I 28
		    dp->name, addr));
E 28
	}
	OUTL(dp, SPR, dir | SPR_MDC);

	for (i = 16; i > 0; i--) {
		OUTL(dp, SPR, dir);
E 11
		ret = (ret << 1) | ((INL(dp, SPR) >> SPR_MDI_SHIFT) & 1);
D 11
		OUTL(dp, SPR, SPR_MMC | SPR_MDC);
E 11
I 11
		OUTL(dp, SPR, dir | SPR_MDC);
E 11
		MDIO_DELAY(dp);
	}
D 17

E 17
D 11
	OUTL(dp, SPR, 0);
E 11
I 11
D 29
	dir = (lp->hw_info->chip_type == CHIP_MX987XX) ? SPR_SWC : 0;
E 29
I 29
	dir &= ~SPR_MMC;
E 29
E 11

I 11
	/* output 2 ones */
	for (i = 0; i < 2; i++) {
		OUTL(dp, SPR, dir | SPR_MDO);
		MDIO_DELAY(dp);
		OUTL(dp, SPR, dir | SPR_MDO | SPR_MDC);
		MDIO_DELAY(dp);
	}
D 28
	OUTL(dp, SPR, dir | SPR_MDO);
E 28
I 28
	/* keep clock signal in high level to save power */
E 28

D 16
	DPRINTF(2, (CE_CONT, "!%s: tu_mii_read: ret:0x%x", dp->name, ret));
E 16
I 16
D 26
	if (reg == MII_STATUS && ret != 0 && ret != 0xffff && lp->bmsr != 0) {
E 26
I 26
	if (reg == MII_STATUS && ret && ret != 0xffff && lp->bmsr) {
E 26
		/* fix my capability according to srom */
D 26
		ret = (ret & ~MII_STATUS_ABILITY) |
			(lp->bmsr & MII_STATUS_ABILITY);
E 26
I 26
		ret = (ret & ~MII_STATUS_ABILITY_TECH) |
D 28
			(lp->bmsr & MII_STATUS_ABILITY_TECH);
E 28
I 28
		    (lp->bmsr & MII_STATUS_ABILITY_TECH);
E 28
E 26
	}
E 16

I 16
D 17
	DPRINTF(2, (CE_CONT, "!%s: tu_mii_read: ret:0x%x", dp->name, ret));
E 16
E 11
	return ret;
E 17
I 17
	DPRINTF(2, (CE_CONT, "!%s: %s: reg:0x%x, ret:0x%x",
D 28
		dp->name, __func__, reg, ret));
E 28
I 28
	    dp->name, __func__, reg, ret));
E 28
	return (ret);
E 17
}

static void
D 16
tu_mii_write(struct gem_dev *dp, int reg, uint16_t val)
E 16
I 16
tu_mii_write(struct gem_dev *dp, uint_t reg, uint16_t val)
E 16
{
	uint32_t	cmd;
	int		i;
	uint32_t	data;
I 11
	uint32_t	dir;
	uint32_t	addr;
E 11
D 7
	struct tu_chip_state	*lp = (struct tu_chip_state *)dp->private;
E 7
I 7
D 28
	struct tu_dev	*lp = (struct tu_dev *)dp->private;
E 28
I 28
	struct tu_dev	*lp = dp->private;
E 28
E 7

I 17
	DPRINTF(1, (CE_CONT, "!%s: %s: reg %x: 0x%x",
D 28
		dp->name, __func__, reg, val));
E 28
I 28
	    dp->name, __func__, reg, val));
E 28

E 17
D 2
	cmd = (5<<(18+5+5)) | (dp->mii_phy_addr<<(18+5))
		| (reg<<18) | (2 << 16) | val;
E 2
I 2
D 5
	cmd = MII_READ_CMD(dp->mii_phy_addr, reg);
E 5
I 5
D 11
	cmd = MII_WRITE_CMD(dp->mii_phy_addr, reg, val);
E 11
I 11
D 29
	dir = lp->hw_info->chip_type == CHIP_MX987XX ? SPR_SWC : 0;
E 29
I 29
	dir = lp->hw_info->spr_mbo;
E 29
	addr = max(dp->mii_phy_addr, 0);
E 11
E 5
E 2

D 11
	tu_mii_sync(dp);
E 11
I 11
	cmd = MII_WRITE_CMD(addr, reg, val);
E 11

	for (i = 31; i >= 0; i--) {
		data = ((cmd >> i) & 1) << SPR_MDO_SHIFT;
D 11
		OUTL(dp, SPR, data);
E 11
I 11
		OUTL(dp, SPR, dir | data);
E 11
		MDIO_DELAY(dp);
D 11
		OUTL(dp, SPR, data | SPR_MDC);
E 11
I 11
		OUTL(dp, SPR, dir | data | SPR_MDC);
E 11
		MDIO_DELAY(dp);
	}

I 11
	/* output 2 ones */
E 11
	for (i = 0; i < 2; i++) {
D 11
		OUTL(dp, SPR, 0);
E 11
I 11
		OUTL(dp, SPR, dir | SPR_MDO);
E 11
		MDIO_DELAY(dp);
D 11
		OUTL(dp, SPR, SPR_MDC);
E 11
I 11
		OUTL(dp, SPR, dir | SPR_MDO | SPR_MDC);
E 11
		MDIO_DELAY(dp);
	}
I 11
D 28
	OUTL(dp, SPR, dir | SPR_MDO);
E 28
I 28
	/* keep clock signal in high level to save power */
E 28
E 11
}
#undef MDIO_DELAY

I 16
/*
 * workarounds for buggy dm9102 mii logic
 */
E 16
I 7
static void
D 17
tu_mii_sync_9102(struct gem_dev *dp)
{
	tu_mii_sync(dp);
}

static uint16_t
D 16
tu_mii_read_9102(struct gem_dev *dp, int reg)
E 16
I 16
tu_mii_read_9102(struct gem_dev *dp, uint_t reg)
E 16
{
	struct tu_dev	*lp = (struct tu_dev *)dp->private;
D 16

E 16
I 16
#ifdef notdef
E 16
	if (reg == MII_STATUS) {
		/* read twice */
		(void)tu_mii_read(dp, reg);
I 11

		if (!dp->no_preamble) {
			tu_mii_sync(dp);
		}
E 11
	}
I 16
#endif
E 16
	return tu_mii_read(dp, reg);
}

static void
E 17
D 16
tu_mii_write_9102(struct gem_dev *dp, int reg, uint16_t val)
E 16
I 16
tu_mii_write_9102(struct gem_dev *dp, uint_t reg, uint16_t val)
E 16
{
D 28
	struct tu_dev	*lp = (struct tu_dev *)dp->private;
E 28
I 9
	int		need_ane_workaround;
E 9
D 28
	
E 28
I 28
	uint32_t	txrx_state;
	struct tu_dev	*lp = dp->private;

E 28
I 9
D 26
	need_ane_workaround = FALSE;
E 26
I 26
	need_ane_workaround = B_FALSE;
E 26

	if (reg == MII_CONTROL && lp->pci_revid == DM9102A_E3) {
#define	MII_CONTROL_RSAN_9102A_E3	0x800
D 26
		need_ane_workaround = TRUE;
E 26
I 26
D 28
		need_ane_workaround = B_TRUE;
E 26

E 28
D 26
		if ((val & MII_CONTROL_RESET) != 0) {
E 26
I 26
		if (val & MII_CONTROL_RESET) {
E 26
I 11
			/* set initial value */
E 11
			lp->bmcr = val & ~MII_CONTROL_ANE;
		}

		if ((lp->bmcr & MII_CONTROL_ANE) == 0 &&
D 26
			(val & MII_CONTROL_ANE) != 0) {
E 26
I 26
D 28
			(val & MII_CONTROL_ANE)) {
E 28
I 28
		    (val & MII_CONTROL_ANE)) {
E 28
E 26
			val &= ~MII_CONTROL_RSAN;
		}

I 11
		lp->bmcr = val;

E 11
D 26
		if ((val & MII_CONTROL_RSAN) != 0) {
E 26
I 26
		if (val & MII_CONTROL_RSAN) {
E 26
			/* fix RSAN bit position */
D 16
#ifndef DM9102A_E3_TEST
E 16
I 16
#ifndef TEST_DM9102A_E3
E 16
			val = (val & ~MII_CONTROL_RSAN)
D 28
				| MII_CONTROL_RSAN_9102A_E3;
E 28
I 28
			    | MII_CONTROL_RSAN_9102A_E3;
E 28
#endif
		}
D 11
		lp->bmcr = val;
E 11

D 26
		if ((lp->nar & NAR_PS) != 0) {
E 26
I 26
		if (lp->nar & NAR_PS) {
I 28
			need_ane_workaround = B_TRUE;
			txrx_state = tu_freeze_chip(dp, NAR_ST | NAR_SR);
E 28
E 26
			lp->nar &= ~NAR_PS;
D 10
			UPDATE_NAR(dp, lp->nar);
E 10
I 10
D 28
			UPDATE_NAR(dp, lp->nar & ~(NAR_ST | NAR_SR));
E 28
I 28
			UPDATE_NAR(dp, lp->nar);
E 28
E 10
		}
	}

write_val:
E 9
	if (reg == MII_CONTROL &&
D 28
	   (val & (MII_CONTROL_RESET | MII_CONTROL_ANE)) == 0) {
E 28
I 28
	    (val & (MII_CONTROL_RESET | MII_CONTROL_ANE)) == 0) {
E 28
		/* work around for forced mode; write twice */
		tu_mii_write(dp, reg, val);
		if (lp->pci_revid == DM9102A_E3) {
			drv_usecwait(20*1000);
		}
	}

	tu_mii_write(dp, reg, val);
I 9

	if (need_ane_workaround) {
		lp->nar |= NAR_PS;
D 10
		UPDATE_NAR(dp, lp->nar);
E 10
I 10
D 28
		UPDATE_NAR(dp, lp->nar & ~(NAR_ST | NAR_SR));
E 10
		tu_restart_chip(dp);
E 28
I 28
		UPDATE_NAR(dp, lp->nar);
		tu_restart_chip(dp, txrx_state);
E 28
	}
E 9
}

E 7
D 2
static int
tu_mii_init_dm9102(struct gem_dev *dp)
E 2
I 2
/*
 * MII routines for ADMtek COMET
I 16
 * XXX - not tested.
E 16
 */
I 3
D 17
static void
E 3
tu_mii_sync_comet(struct gem_dev *dp)
E 2
{
D 2
	int		phy;
	uint16_t	adv;
	uint16_t	status;
	uint32_t	phyid;
	uint16_t	val;
E 2
I 2
	/* Do nothing */
}
E 17
I 17
static uint8_t tu_comet_mii_map[] = {
D 28
	/* 0: MII_CONTROL*/	XCR,
E 28
I 28
	/* 0: MII_CONTROL */	XCR,
E 28
	/* 1: MII_STATUS */	XSR,
	/* 2: MII_PHYIDH */	PID1,
	/* 3: MII_PHYIDL */	PID2,
	/* 4: MII_AN_ADVERT */	ANA,
	/* 5: MII_AN_LPABLE */	ANLPAR,
D 28
	/* 6: MII_AN_EXPANSION*/ANE,
E 28
I 28
	/* 6: MII_AN_EXPANSION */ ANE,
E 28
};
E 17
E 2

D 2
	DPRINTF(3, (CE_CONT, "%s: tu_mii_init_dm9102: called", dp->name));
E 2
I 2
static uint16_t
D 16
tu_mii_read_comet(struct gem_dev *dp, int index)
E 16
I 16
tu_mii_read_comet(struct gem_dev *dp, uint_t index)
E 16
{
D 17
	uint16_t	ret;
E 2

D 2
	/*
	 * Scan PHY
	 */
again:
	GEM_MII_SYNC(dp);
E 2
I 2
	switch (index) {
	case MII_CONTROL:
		ret = INL(dp, XCR);
		break;
E 2

D 2
	for (phy = 0; phy < 32; phy++) {
		dp->mii_phy_addr = phy;
		status = GEM_MII_READ(dp, MII_STATUS);
E 2
I 2
	case MII_STATUS:
		ret = INL(dp, XSR);
		break;
E 2

D 2
		if (status != 0xffff && status != 0x0000) {
			if (phy == 0) {
				GEM_MII_WRITE(dp, MII_CONTROL, MII_CONTROL_RESET);
				drv_usecwait(100*1000);
				goto again;
			}
			goto PHY_found;
		}
E 2
I 2
	case MII_PHYIDH:
		ret = INL(dp, PID1);
		break;

	case MII_PHYIDL:
		ret = INL(dp, PID2);
		break;

	case MII_AN_ADVERT:
		ret = INL(dp, ANA);
		break;

	case MII_AN_LPABLE:
		ret = INL(dp, ANLPAR);
		break;

	case MII_AN_EXPANSION:
		ret = INL(dp, ANE);
		break;

	case MII_AN_NXTPGXMIT:
	default:
I 14
		ret = 0;
E 14
		break;
E 17
I 17
D 28
	if (index >= sizeof(tu_comet_mii_map)/sizeof(tu_comet_mii_map[0])) {
E 28
I 28
D 29
	if (index >= sizeof (tu_comet_mii_map)/sizeof (tu_comet_mii_map[0])) {
E 29
I 29
	if (index >=
	    sizeof (tu_comet_mii_map) / sizeof (tu_comet_mii_map[0])) {
E 29
E 28
		/* out of range, do nothing */
D 28
		cmn_err(CE_WARN, "%s: %s: out of register address: %d",
			dp->name, __func__, index);
E 28
I 28
		cmn_err(CE_WARN, "!%s: %s: out of register address: %d",
		    dp->name, __func__, index);
E 28
		return (0);
E 17
E 2
	}
I 2
D 17
	return ret;
E 17
I 17
	return (INL(dp, tu_comet_mii_map[index]));
E 17
}
E 2

D 2
	cmn_err(CE_WARN, "!%s: failed to find PHY", dp->name);
	return -1;
E 2
I 2
static void
D 16
tu_mii_write_comet(struct gem_dev *dp, int index, uint16_t val)
E 16
I 16
tu_mii_write_comet(struct gem_dev *dp, uint_t index, uint16_t val)
E 16
{
D 3
	uint16_t	ret;
E 2

E 3
D 2
PHY_found:
E 2
I 2
D 17
	switch (index) {
	case MII_CONTROL:
		OUTL(dp, XCR, val);
		break;
E 2

D 2
	phyid  = GEM_MII_READ(dp, MII_PHYIDH) << 16;
	phyid |= GEM_MII_READ(dp, MII_PHYIDL);
	adv = GEM_MII_READ(dp, MII_AN_ADVERT);
	val = GEM_MII_READ(dp, MII_CONTROL);
E 2
I 2
	case MII_STATUS:
		OUTL(dp, XSR, val);
		break;
E 2

D 2
	cmn_err(CE_CONT, "!%s: PHY (0x%08x) "
		"found at %d, control:%b, status:%b, advert:%b, lpar:%b",
		dp->name, phyid, dp->mii_phy_addr,
		val, MII_CONTROL_BITS,
		status, MII_STATUS_BITS,
		adv, MII_ABILITY_BITS,
		GEM_MII_READ(dp, MII_AN_LPABLE),
		MII_ABILITY_BITS);
E 2
I 2
D 7
	case MII_PHYIDH:
		OUTL(dp, PID1, val);
		break;
E 2

D 2
	return 0;
E 2
I 2
	case MII_PHYIDL:
		OUTL(dp, PID2, val);
		break;

E 7
	case MII_AN_ADVERT:
		OUTL(dp, ANA, val);
		break;

	case MII_AN_LPABLE:
		OUTL(dp, ANLPAR, val);
		break;

	case MII_AN_EXPANSION:
		OUTL(dp, ANE, val);
		break;

	case MII_AN_NXTPGXMIT:
I 7
	case MII_PHYIDH:
	case MII_PHYIDL:
E 7
	default:
		break;
E 17
I 17
D 28
	if (index >= sizeof(tu_comet_mii_map)/sizeof(tu_comet_mii_map[0])) {
E 28
I 28
D 29
	if (index >= sizeof (tu_comet_mii_map)/sizeof (tu_comet_mii_map[0])) {
E 29
I 29
	if (index >=
	    sizeof (tu_comet_mii_map) / sizeof (tu_comet_mii_map[0])) {
E 29
E 28
		/* out of range, do nothing */
D 28
		cmn_err(CE_WARN, "%s: %s: out of register address: %d",
			dp->name, __func__, index);
E 28
I 28
		cmn_err(CE_WARN, "!%s: %s: out of register address: %d",
		    dp->name, __func__, index);
E 28
		return;
E 17
	}
I 17
	OUTL(dp, tu_comet_mii_map[index], val);
E 17
E 2
}

I 2
/*
I 8
D 9
 * MII routines for LITEON PNIC
E 9
I 9
 * MII routines for LITE-ON PNIC
E 9
 */
D 17
static void
tu_mii_sync_pnic(struct gem_dev *dp)
{
	/* do nothing */
}

E 17
static uint16_t
D 16
tu_mii_read_pnic(struct gem_dev *dp, int reg)
E 16
I 16
tu_mii_read_pnic(struct gem_dev *dp, uint_t reg)
E 16
{
D 16
	uint32_t	cmd;
E 16
	uint32_t	ret;
	int		i;

D 16
	cmd = MII_READ_CMD(dp->mii_phy_addr, reg);

E 16
	/* ensure not busy */
D 16
	i = 10;
	while ((INL(dp, PNIC_MII) & MII_BUSY) && --i >= 0) {
E 16
I 16
D 26
	for (i = 0; (INL(dp, PNIC_MII) & MII_BUSY) != 0; i++) {
E 26
I 26
	for (i = 0; INL(dp, PNIC_MII) & MII_BUSY; i++) {
E 26
		if (i > 10) {
			cmn_err(CE_WARN,
D 28
				"%s: %s: PNIC_MII register is not ready",
				dp->name, __func__);
E 28
I 28
			    "!%s: %s: PNIC_MII register is not ready",
			    dp->name, __func__);
E 28
D 17
			return 0;
E 17
I 17
			return (0);
E 17
		}
E 16
		drv_usecwait(10);
	}
D 16
	if (i < 0) {
		cmn_err(CE_WARN,
			"%s: tu_mii_read_pnic: csr20 is not ready",
		dp->name);
		return 0;
	}
E 16

D 16
	OUTL(dp, PNIC_MII, cmd);

	i = 10;
E 16
I 16
	OUTL(dp, PNIC_MII, MII_READ_CMD(dp->mii_phy_addr, reg));
E 16
D 29
	drv_usecwait(64*1);
E 29
I 29
	drv_usecwait(64);
E 29
D 16
	while (((ret = INL(dp, PNIC_MII)) & MII_BUSY) && --i >= 0) {
E 16
I 16

D 26
	for (i = 0; ((ret = INL(dp, PNIC_MII)) & MII_BUSY) != 0; i++) {
E 26
I 26
D 28
	for (i = 0; ((ret = INL(dp, PNIC_MII)) & MII_BUSY); i++) {
E 28
I 28
	for (i = 0; (ret = INL(dp, PNIC_MII)) & MII_BUSY; i++) {
E 28
E 26
		if (i > 10) {
			cmn_err(CE_WARN,
D 28
				"%s: %s: PNIC_MII register is busy",
				dp->name, __func__);
E 28
I 28
			    "!%s: %s: PNIC_MII register is busy",
			    dp->name, __func__);
E 28
D 17
			return 0;
E 17
I 17
			return (0);
E 17
		}
E 16
		drv_usecwait(10);
	}

D 16
	if (i < 0) {
		cmn_err(CE_WARN,
			"%s: tu_mii_read_pnic: csr20 is busy(2)",
			dp->name);
		return 0;
	}

E 16
D 17
	return ret & 0xffff;
E 17
I 17
	return (ret & 0xffff);
E 17
}

static void
D 16
tu_mii_write_pnic(struct gem_dev *dp, int reg, uint16_t val)
E 16
I 16
tu_mii_write_pnic(struct gem_dev *dp, uint_t reg, uint16_t val)
E 16
{
D 16
	uint32_t	cmd;
	int		i;
E 16
I 16
	int	i;
E 16

D 16
	cmd = MII_WRITE_CMD(dp->mii_phy_addr, reg, val);

E 16
	/* ensure not busy */
D 16
	i = 10;
	while ((INL(dp, PNIC_MII) & MII_BUSY) && --i >= 0) {
E 16
I 16
D 26
	for (i = 0; (INL(dp, PNIC_MII) & MII_BUSY) != 0; i++) {
E 26
I 26
D 28
	for (i = 0; (INL(dp, PNIC_MII) & MII_BUSY); i++) {
E 28
I 28
	for (i = 0; INL(dp, PNIC_MII) & MII_BUSY; i++) {
E 28
E 26
		if (i > 10) {
			cmn_err(CE_WARN,
D 28
				"%s: %s: PNIC_MII register is not ready",
				dp->name, __func__);
E 28
I 28
			    "!%s: %s: PNIC_MII register is not ready",
			    dp->name, __func__);
E 28
			return;
		}
E 16
		drv_usecwait(10);
	}
D 16
	if (i < 0) {
		cmn_err(CE_WARN,
			"%s: tu_mii_write_pnic: PNIC_MII is not ready",
			dp->name);
		return;
	}
E 16

D 16
	OUTL(dp, PNIC_MII, cmd);

	i = 10;
E 16
I 16
	OUTL(dp, PNIC_MII, MII_WRITE_CMD(dp->mii_phy_addr, reg, val));
E 16
D 29
	drv_usecwait(64*1);
E 29
I 29
	drv_usecwait(64);
E 29
D 16
	while ((INL(dp, PNIC_MII) & MII_BUSY) && --i >= 0) {
E 16
I 16

D 26
	for (i = 0; (INL(dp, PNIC_MII) & MII_BUSY) != 0; i++) {
E 26
I 26
D 28
	for (i = 0; (INL(dp, PNIC_MII) & MII_BUSY); i++) {
E 28
I 28
	for (i = 0; INL(dp, PNIC_MII) & MII_BUSY; i++) {
E 28
E 26
		if (i > 10) {
			cmn_err(CE_WARN,
D 28
				"%s: %s: PNIC_MII register is busy",
				dp->name, __func__);
E 28
I 28
			    "!%s: %s: PNIC_MII register is busy",
			    dp->name, __func__);
E 28
			return;
		}
E 16
		drv_usecwait(10);
	}
I 16
}
E 16

D 16
	if (i < 0) {
		cmn_err(CE_WARN,
			"%s: tu_mii_read_pnic: PNIC_MII is busy",
			dp->name);
E 16
I 16
/*
I 17
 * MII routines for ULI562x
 */
#define	ULI_MII_CMD	0x48	/* CSR9 */
#define	ULI_MII_DATA	0x50	/* CSR10 */

static uint16_t
tu_mii_read_uli(struct gem_dev *dp, uint_t reg)
{
	uint32_t	ret;
	int		i;

	ret = INL(dp, ULI_MII_CMD) & ~0x00100000;
	OUTL(dp, ULI_MII_CMD, ret);

	OUTL(dp, ULI_MII_DATA,
D 28
		0x08000000 | (dp->mii_phy_addr << 21) | (reg << 16));
E 28
I 28
D 29
	    0x08000000 | (dp->mii_phy_addr << 21) | (reg << 16));
E 29
I 29
	    0x08000000 | dp->mii_phy_addr << 21 | reg << 16);
E 29
E 28

	for (i = 0; ((ret = INL(dp, ULI_MII_DATA)) & 0x10000000) == 0; i++) {
D 25
		if (i > 10) {
E 25
I 25
		if (i > 100) {
E 25
			cmn_err(CE_WARN,
D 28
				"%s: %s: ULI_MII_CMD register is busy",
				dp->name, __func__);
E 28
I 28
			    "!%s: %s: ULI_MII_CMD register is busy",
			    dp->name, __func__);
E 28
			return (0);
		}
		drv_usecwait(10);
	}

	return (ret & 0xffff);
}

static void
tu_mii_write_uli(struct gem_dev *dp, uint_t reg, uint16_t val)
{
	uint32_t	ret;
	int		i;

	ret = INL(dp, ULI_MII_CMD) & ~0x00100000;
	OUTL(dp, ULI_MII_CMD, ret);

	OUTL(dp, ULI_MII_DATA,
D 28
		0x04000000 | (dp->mii_phy_addr << 21) | (reg << 16) | val);
E 28
I 28
D 29
	    0x04000000 | (dp->mii_phy_addr << 21) | (reg << 16) | val);
E 29
I 29
	    0x04000000 | dp->mii_phy_addr << 21 | reg << 16 | val);
E 29
E 28

	for (i = 0; ((ret = INL(dp, ULI_MII_DATA)) & 0x10000000) == 0; i++) {
D 25
		if (i > 10) {
E 25
I 25
		if (i > 100) {
E 25
			cmn_err(CE_WARN,
D 28
				"%s: %s: ULI_MII_CMD register is busy",
				dp->name, __func__);
E 28
I 28
			    "!%s: %s: ULI_MII_CMD register is busy",
			    dp->name, __func__);
E 28
			return;
		}
		drv_usecwait(10);
	}
}

/*
E 17
 * MII PHY emulators for combination of 100M sym and 10Base-T ports
 */
/* for dec 21143 and its variants */
static int
tu_mii_choose_technology(uint16_t val)
{
	int	ret = 0;

	/*
	 * choose common technology
	 */
D 28
	if ((val & MII_ABILITY_100BASE_TX_FD) != 0) {
E 28
I 28
	if (val & MII_ABILITY_100BASE_TX_FD) {
E 28
		/* 100BaseTx & fullduplex */
		ret = MII_CONTROL_100MB | MII_CONTROL_FDUPLEX;
E 16
D 28
	}
I 16
	else if ((val & MII_ABILITY_100BASE_TX) != 0) {
E 28
I 28
	} else if (val & MII_ABILITY_100BASE_TX) {
E 28
		/* 100BaseTx & half duplex */
		ret = MII_CONTROL_100MB;
D 28
	}
	else if ((val & MII_ABILITY_10BASE_T_FD) != 0) {
E 28
I 28
	} else if (val & MII_ABILITY_10BASE_T_FD) {
E 28
		/* 10BaseT & full duplex */
		ret = MII_CONTROL_FDUPLEX;
D 28
	}
	else if ((val & MII_ABILITY_10BASE_T) != 0) {
E 28
I 28
	} else if (val & MII_ABILITY_10BASE_T) {
E 28
		/* do nothing */
		ret = 0;
	}
E 16

D 16
	return;
E 16
I 16
D 17
	return ret;
E 17
I 17
	return (ret);
E 17
E 16
}

D 16
/*
E 8
 * MII emulation routines for combination of 100M sym and 10Base-T ports
 */
E 16
E 2
static void
D 2
tu_mii_sync_sym(struct gem_dev *dp)
E 2
I 2
D 9
tu_mii_sync_nway(struct gem_dev *dp)
E 9
I 9
tu_nway_sync(struct gem_dev *dp)
E 9
E 2
{
	/* Do nothing */
}
I 11

E 11
D 10

E 10
I 8
/*
I 29
 * MII PHY emulator with 21143 nway logic
 */
/*
E 29
D 10
 * write a 10-baseT control value to lower layer
 */
E 8
I 2
static void
D 9
tu_write_siacntl(struct gem_dev *dp, uint32_t siacntl)
E 9
I 9
tu_write_siactrl(struct gem_dev *dp, uint32_t siactrl)
E 9
{
D 7
	struct tu_chip_state	*lp = (struct tu_chip_state *)dp->private;
E 7
I 7
	struct tu_dev	*lp = (struct tu_dev *)dp->private;
E 7

D 9
	DPRINTF(2, (CE_CONT, "!%s: tu_write_siacntl: writing 0x%08x",
			dp->name, siacntl));
E 9
I 9
	DPRINTF(2, (CE_CONT, "!%s: tu_write_siactrl: writing 0x%08x",
			dp->name, siactrl));
E 9

D 8
	lp->nar &= ~NAR_PS;
	OUTL(dp, NAR, lp->nar & ~(NAR_ST | NAR_SR));
	drv_usecwait(5);

	OUTL(dp, SIACONN, 0);
	OUTL(dp, SIACNTL, siacntl);
D 6
	OUTL(dp, SIACONN, SIACONN_RST);
E 6
I 6
	if (siacntl != 0) {
		OUTL(dp, SIACONN, SIACONN_RST);
E 8
I 8
	if (lp->hw_info->chip_type == CHIP_LC82C168) {
		/*
		 * Control relay to select 100/10 port by writing
D 9
		 * into GPIO reg, instead of SIACNTL reg.
E 9
I 9
		 * into GPIO reg, instead of SIACTRL reg.
E 9
		 */
D 9
		OUTL(dp, PNIC_GPIO,
			siacntl ? (PNIC_GPIO_100_LB | PNIC_GPIO_RL_10)
				: (PNIC_GPIO_100_EN | PNIC_GPIO_RL_100));
E 9
I 9
		if (siactrl != 0) {
			/* select 10M port */
			OUTL(dp, PNIC_GPIO,
				PNIC_GPIO_100_LB | PNIC_GPIO_RL_10);
		}
		else {
			/* select 100M port */
			OUTL(dp, PNIC_GPIO,
				PNIC_GPIO_100_EN | PNIC_GPIO_RL_100);
		}
E 9
E 8
	}
I 8
	else {
		OUTL(dp, SIACONN, 0);
D 9
		OUTL(dp, SIACNTL, siacntl);
		if (siacntl != 0) {
E 9
I 9
		OUTL(dp, SIACTRL, siactrl);
		if (siactrl != 0) {
E 9
			OUTL(dp, SIACONN, SIACONN_RST);
		}
	}
E 8
E 6
}

I 8
/*
E 10
D 9
 * Select port acording to bmcr
E 9
I 9
D 11
 * Kick auto negotiation (for sym interface of 21143 and MX98715)
E 11
I 11
D 17
 * Kick auto negotiation (for sym interface of 21143, MX98713A and MX98715)
E 17
I 17
 * Kick auto negotiation
 * (for sym interface of 21143, LC82C115, MX98713A and MX98715)
E 17
E 11
E 9
 */
E 8
static void
D 9
tu_select_port(struct gem_dev *dp)
E 9
I 9
tu_nway_start_21143(struct gem_dev *dp)
E 9
{
D 9
	uint32_t	siacntl;
E 9
I 9
	uint32_t	adv;
E 9
D 7
	struct tu_chip_state	*lp = (struct tu_chip_state *)dp->private;
E 7
I 7
D 28
	struct tu_dev	*lp = (struct tu_dev *)dp->private;
E 28
I 28
	struct tu_dev	*lp = dp->private;
E 28
E 7

I 17
D 28
	DPRINTF(1, (CE_CONT, "!%s: %s: called, SIAGP:%x", dp->name, __func__));
E 28
I 28
	DPRINTF(1, (CE_CONT, "!%s: %s: called, SIAGP:%x",
	    dp->name, __func__));
E 28

E 17
D 9
	DPRINTF(2, (CE_CONT, "!%s: tu_select_port: fdx:%d speed100:%d csr6:%b",
			dp->name,
			lp->bmcr & MII_CONTROL_FDUPLEX ? 1 : 0,
			lp->bmcr & MII_CONTROL_100MB ? 1 : 0,
			lp->nar, CSR6BITS));

	/* temporary stop Tx and Rx */
	if ((lp->nar & (NAR_ST | NAR_SR)) != 0) {
		OUTL(dp, NAR, lp->nar & ~(NAR_ST | NAR_SR));
I 6
		drv_usecwait(5);
E 6
	}

	if ((lp->bmcr & MII_CONTROL_100MB) != 0) {

		/* disable 10Base-T port */
		tu_write_siacntl(dp, 0);

		/* enable 100M port as half duplex */
		lp->nar |= NAR_PS | NAR_SCR | NAR_PCS | NAR_SQE;
		lp->nar &= ~(NAR_TTM | NAR_FD);

I 3
D 7
		if (lp->hw_info->chip_type == CHIP_DM9102) {
			/* select internal PHY */
			lp->nar &= ~NAR_PS;
		}

E 7
E 3
		/* select duplex */
		if ((lp->bmcr & MII_CONTROL_FDUPLEX) != 0) {
			lp->nar |= NAR_FD;
		}

		OUTL(dp, NAR, lp->nar & ~(NAR_ST | NAR_SR));
		drv_usecwait(5);
	}
	else {
		/*
		 * Use 10Base-T port
		 */
		/* disable 100M port */
		lp->nar &= ~(NAR_PS | NAR_TTM);

		switch (lp->hw_info->chip_type) {
		case CHIP_MX98713:
		case CHIP_MX98715:
			/* patch for MX987xx seris */
			lp->nar &= ~(NAR_SCR | NAR_PCS);
I 8
			/* fall down */

		case CHIP_LC82C168: /* datasheet doesn't say, but required */
		case CHIP_LC82C115:
E 8
			lp->nar |= NAR_TTM;
		}

D 6
		/* enable 10Bast-T port as half duplex */
E 6
I 6
		/* enable 10Base-T port as half duplex */
E 6
		lp->nar &= ~(NAR_FD | NAR_SQE);
		siacntl = SIACNTL_10BASET_HALF;

		/* select duplex */
		if ((lp->bmcr & MII_CONTROL_FDUPLEX) != 0) {
			lp->nar |= NAR_FD;
			siacntl &= ~SIACNTL_LBK;
		}

I 6
		OUTL(dp, NAR, lp->nar & ~(NAR_ST | NAR_SR));
		drv_usecwait(5);

E 6
		tu_write_siacntl(dp, siacntl);
	}

	/* restart Tx and Rx */
	if ((lp->nar & (NAR_ST | NAR_SR)) != 0) {
		OUTL(dp, NAR, lp->nar);
	}
}

static void
tu_start_an(struct gem_dev *dp)
{
	uint32_t	siastat;
	uint32_t	siacntl;
D 8
	uint16_t	val;
E 8
D 7
	struct tu_chip_state	*lp = (struct tu_chip_state *)dp->private;
E 7
I 7
	struct tu_dev	*lp = (struct tu_dev *)dp->private;
E 7

E 9
	/*
D 9
	 * Issuse autonego
E 9
I 9
	 * construct AN advertisement bits in siactrl register
E 9
	 */
D 8
	siacntl = SIACNTL_10BASET_HALF;
	siacntl |= SIACNTL_ANE;	/* autonego */
E 8
I 8
D 9
	siacntl = SIACNTL_10BASET_HALF | SIACNTL_ANE;
E 9
I 9
D 10
	tu_freeze_chip(dp);
E 10
D 16
	/* MX chips need SCR */
E 16
I 16
D 17
	/* XXX - undocumented: MX chips need SCR */
E 16
	lp->nar = (lp->nar & ~CSR6_PORT_BITS)
D 10
		| (lp->csr6[PORT_10_HD] | NAR_SCR);
E 10
I 10
		| (lp->cfg_csr6[PORT_10_HD] | NAR_SCR);
E 10
	adv = 0;
E 17
I 17
	adv = SIACTRL_ANE;
E 17
E 9
E 8
D 10

E 10
D 9
	/* Construct advertisement bits */
	if (lp->adv & MII_ABILITY_10BASE_T) {
		siacntl |= SIACNTL_TH;
	}
	if (lp->adv & MII_ABILITY_10BASE_T_FD) {
		lp->nar |= NAR_FD;
	}
	if (lp->adv & MII_ABILITY_100BASE_TX) {
		siacntl |= SIACNTL_TXH;
	}
	if (lp->adv & MII_ABILITY_100BASE_TX_FD) {
		siacntl |= SIACNTL_TXF;
	}
	if (lp->adv & MII_ABILITY_100BASE_T4) {
		siacntl |= SIACNTL_T4;
	}
	if (lp->adv & MII_ABILITY_PAUSE) {
		siacntl |= SIACNTL_PAUSE;
	}
E 9
I 9
	REPLACE_BIT(adv, SIACTRL_TH,  lp->adv, MII_ABILITY_10BASE_T);
	REPLACE_BIT(lp->nar, NAR_FD,  lp->adv, MII_ABILITY_10BASE_T_FD);
	REPLACE_BIT(adv, SIACTRL_TXH, lp->adv, MII_ABILITY_100BASE_TX);
	REPLACE_BIT(adv, SIACTRL_TXF, lp->adv, MII_ABILITY_100BASE_TX_FD);
	REPLACE_BIT(adv, SIACTRL_T4,  lp->adv, MII_ABILITY_100BASE_T4);
	REPLACE_BIT(adv, SIACTRL_PAUSE, lp->adv, MII_ABILITY_PAUSE);
D 10
	UPDATE_NAR(dp, lp->nar);
E 10
E 9

I 10
D 17
	UPDATE_NAR(dp, lp->nar & ~(NAR_ST | NAR_SR));
E 17
I 17
	/*
	 * Configure 10M port for autonegotiation.
	 */
	tu_setup_speed_duplex(dp,
D 28
		((lp->nar & NAR_FD) != 0 ? PORT_10_FD : PORT_10_HD), adv);
E 28
I 28
	    ((lp->nar & NAR_FD) ? PORT_10_FD : PORT_10_HD), adv);
E 28
E 17
I 11

E 11
E 10
D 9
	/* setup 10Base-T port for autonegotiation */
I 8
	if ((lp->nar & NAR_PS) != 0) {
		lp->nar &= ~NAR_PS;
		OUTL(dp, NAR, lp->nar & ~(NAR_ST | NAR_SR));
		drv_usecwait(5);
	}
E 8
	tu_write_siacntl(dp, siacntl);
E 9
I 9
D 17
	OUTL(dp, SIACONN, 0);
D 10
	OUTL(dp, SIACTRL, adv | lp->csr14[PORT_10_HD] | SIACTRL_ANE);
	OUTL(dp, SIACONN, lp->csr13[PORT_10_HD]);
E 10
I 10
	OUTL(dp, SIACTRL, adv | lp->cfg_csr14[PORT_10_HD] | SIACTRL_ANE);
	OUTL(dp, SIACONN, lp->cfg_csr13[PORT_10_HD]);
E 10
E 9

E 17
	/* Kick auto-negotiation */
	OUTL(dp, SIASTAT, 1 << SIASTAT_ANS_SHIFT);
I 16

D 17
	/* reset auto_negotiation status bits */
E 17
I 17
	/* reset auto negotiation status bits */
E 17
	lp->bmcr &= ~MII_CONTROL_RSAN;
	lp->bmsr &= ~MII_STATUS_ANDONE;
	lp->lpar = 0;
I 20
D 28
	lp->exp  = 0;
E 28
I 28
	lp->exp = 0;
E 28
	lp->an_start_time = ddi_get_lbolt();
E 20
E 16
D 9

D 8
	/* save current value */
	lp->bmcr &= (MII_CONTROL_100MB | MII_CONTROL_FDUPLEX);
	lp->bmcr |= val &
		   ~(MII_CONTROL_100MB | MII_CONTROL_FDUPLEX);

E 8
	/* clear last LPAR */
	lp->lpar = 0;
I 8

	/* reset restart_auto_nego bit */
	lp->bmcr &= ~MII_CONTROL_RSAN;
E 9
E 8
}

E 2
static uint16_t
D 2
tu_mii_read_sym(struct gem_dev *dp, int index)
E 2
I 2
D 9
tu_mii_read_nway(struct gem_dev *dp, int index)
E 9
I 9
D 16
tu_nway_read_21143(struct gem_dev *dp, int index)
E 16
I 16
tu_nway_read_21143(struct gem_dev *dp, uint_t index)
E 16
E 9
E 2
{
D 2
	uint_t	ret;
	uint_t	csr14;
	uint_t	csr12;
	uint_t	csr6;
E 2
I 2
	uint16_t	ret;
I 9
	uint16_t	val;
E 9
	uint32_t	csr14;
	uint32_t	csr12;
I 16
	int		port;
I 17
	int		anstate = 0;
E 17
E 16
D 7
	struct tu_chip_state	*lp = (struct tu_chip_state *)dp->private;
E 7
I 7
D 28
	struct tu_dev	*lp = (struct tu_dev *)dp->private;
E 28
I 28
	struct tu_dev	*lp = dp->private;
E 28
E 7
E 2

D 2
	DPRINTF(4, (CE_CONT, "!%s: tu_mii_read_sym: called", dp->name));
E 2
I 2
D 9
	DPRINTF(4, (CE_CONT, "!%s: tu_mii_read_nway: called", dp->name));
E 9
I 9
D 16
	DPRINTF(4, (CE_CONT, "!%s: tu_nway_read_21143: called", dp->name));
E 16
I 16
	DPRINTF(4, (CE_CONT, "!%s: %s: called", dp->name, __func__));
E 16
E 9
E 2

	switch (index) {
	case MII_CONTROL:
D 2
		csr14 = INL(dp, SIACNTL);
		ret = 0;
		if ((csr14 & SIACNTL_ANE) != 0) {
			ret |= MII_CONTROL_ANE;
E 2
I 2
		ret = lp->bmcr;
D 28
		if ((ret & MII_CONTROL_RESET) != 0) {
E 28
I 28
		if (ret & MII_CONTROL_RESET) {
E 28
			if (ddi_get_lbolt() - lp->reset_expire <= 0) {
				break;
			}
			/*
D 29
			 * It's first access after reseting.
E 29
I 29
			 * It's the first access after the last reset.
E 29
D 9
			 * Ensure port selection.
E 9
			 */
			ret &= ~MII_CONTROL_RESET;
			lp->bmcr = ret;
D 9
			if ((ret & MII_CONTROL_ANE) == 0) {
				tu_select_port(dp);
			}
			else {
E 9
I 9
D 16
#ifdef notdef
E 16
I 16

E 16
D 28
			if ((ret & MII_CONTROL_ANE) != 0) {
E 28
I 28
			if (ret & MII_CONTROL_ANE) {
E 28
E 9
				/* Start auto-negotiation */
I 11
D 28
				tu_freeze_chip(dp, NAR_ST | NAR_SR);
E 28
E 11
D 9
				tu_start_an(dp);
			}
E 9
I 9
				tu_nway_start_21143(dp);
I 11
D 16
				tu_restart_chip(dp);
E 11

				/* reset auto_negotiation status bits */
				lp->bmcr &= ~MII_CONTROL_RSAN;
				lp->bmsr &= ~MII_STATUS_ANDONE;
				lp->lpar = 0;
E 16
I 11
			}
E 11
D 16
#endif
E 16
E 9
E 2
		}
D 2
#ifdef notdef
MII_CONTROL_RESET
MII_CONTROL_LOOPBACK
MII_CONTROL_100MB 
MII_CONTROL_PWRDN
MII_CONTROL_ISOLATE
MII_CONTROL_RSAN
MII_CONTROL_FDUPLEX
MII_CONTROL_COLTST
#endif
E 2
I 2
D 9
	/*
E 9
I 9
#ifdef notdef
E 9
D 28
		MII_CONTROL_RESET
D 9
		MII_CONTROL_LOOPBACK
		MII_CONTROL_100MB 
		MII_CONTROL_PWRDN
		MII_CONTROL_ISOLATE
E 9
I 9
		MII_CONTROL_LOOPBACK	not supported
		MII_CONTROL_100MB
		MII_CONTROL_PWRDN	not supported
		MII_CONTROL_ISOLATE	not supported
E 9
		MII_CONTROL_RSAN
		MII_CONTROL_FDUPLEX
D 9
		MII_CONTROL_COLTST
	*/
E 9
I 9
		MII_CONTROL_COLTST	not supported
E 28
I 28
		/* MII_CONTROL_RESET */
		/* MII_CONTROL_LOOPBACK	not supported */
		/* MII_CONTROL_100MB */
		/* MII_CONTROL_PWRDN	not supported */
		/* MII_CONTROL_ISOLATE	not supported */
		/* MII_CONTROL_RSAN */
		/* MII_CONTROL_FDUPLEX */
		/* MII_CONTROL_COLTST	not supported */
E 28
#endif
E 9
E 2
		break;

	case MII_STATUS:
		csr12 = INL(dp, SIASTAT);
I 9
D 16
		DPRINTF(2, (CE_CONT, "!%s: nway_read_21143 0x%08x", dp->name, csr12));
E 16
I 16
		DPRINTF(2, (CE_CONT, "!%s: %s csr12:0x%08x",
D 28
			dp->name, __func__, csr12));
E 28
I 28
		    dp->name, __func__, csr12));
E 28
E 16
E 9

D 2
		DPRINTF(2, (CE_CONT, "%s: mii_read_sym 0x%08x",
E 2
I 2
D 9
		DPRINTF(2, (CE_CONT, "!%s: mii_read_nway 0x%08x",
E 2
			dp->name, csr12));

		ret =   MII_STATUS_100_BASEX_FD |
			MII_STATUS_100_BASEX |
			MII_STATUS_10_FD |
			MII_STATUS_10;

E 9
I 9
D 11
		ret = lp->bmsr;
E 11
I 11
		ret = lp->bmsr
		    | MII_STATUS_CANAUTONEG
D 16
		    | MII_STATUS_MFPRMBLSUPR
		    | MII_STATUS_100_BASEX_FD
		    | MII_STATUS_100_BASEX
		    | MII_STATUS_10_FD
		    | MII_STATUS_10;
E 16
I 16
		    | MII_STATUS_MFPRMBLSUPR;

		ret &= ~MII_STATUS_LINKUP;

E 16
E 11
E 9
D 17
		if (((csr12 & SIASTAT_ANS) >> SIASTAT_ANS_SHIFT) == 5) {
E 17
I 17
D 20
		anstate = (csr12 & SIASTAT_ANS) >> SIASTAT_ANS_SHIFT;
		if (anstate == 5) {
E 17
I 2
D 9
			uint16_t	val;

E 9
I 9
			/*
			 * Auto-negotiation has done.
			 * Here we need to determin common technology.
			 */
E 9
E 2
			ret |= MII_STATUS_ANDONE;
I 9
D 16
			ret &= ~MII_STATUS_LINKUP;
E 16
E 9
I 2
			lp->lpar = csr12 >> 16;
E 20
I 20
D 28
		if ((lp->bmcr & MII_CONTROL_ANE) != 0 &&
E 28
I 28
		if ((lp->bmcr & MII_CONTROL_ANE) &&
E 28
		    (lp->bmsr & MII_STATUS_ANDONE) == 0) {
E 20

D 9
			val = lp->adv & lp->lpar;

			lp->bmcr &= ~(MII_CONTROL_100MB | MII_CONTROL_FDUPLEX);
			if (val == 0) {
				/* what should we do */
			}
			if (val & MII_ABILITY_100BASE_TX_FD) {
				lp->bmcr |= MII_CONTROL_FDUPLEX;
				lp->bmcr |= MII_CONTROL_100MB;
			}
			else if (val & MII_ABILITY_100BASE_TX) {
				lp->bmcr |= MII_CONTROL_100MB;
			}
			else if (val & MII_ABILITY_10BASE_T_FD) {
				lp->bmcr |= MII_CONTROL_FDUPLEX;
			}
			else if (val & MII_ABILITY_10BASE_T) {
				/* nothing */
			}

			tu_select_port(dp);
E 9
I 9
D 16
			DPRINTF(2, (CE_CONT,
				"!%s: nway_read_21143, autonego done, 0x%08x",
				dp->name, csr12));
E 16
I 16
D 20
			DPRINTF(1, (CE_CONT,
				"!%s: %s, autonego done, csr12:0x%08x",
				dp->name, __func__, csr12));
			/*
			 * choose common technology
			 */
			lp->bmcr &= ~(MII_CONTROL_SPEED | MII_CONTROL_FDUPLEX);
			if ((val = (lp->adv & lp->lpar)) != 0) {
				lp->bmcr |= tu_mii_choose_technology(val);
			} else {
				cmn_err(CE_CONT,
			"!%s: %s autonego done, but no common technology",
					dp->name, __func__);
E 20
I 20
			/* auto-negotiation is in progress now */
			anstate = (csr12 & SIASTAT_ANS) >> SIASTAT_ANS_SHIFT;

D 28
			if (ddi_get_lbolt() - lp->an_start_time
						> MII_AN_TIMEOUT*3/4) {
E 28
I 28
			if (ddi_get_lbolt() - lp->an_start_time >
D 29
			    MII_AN_TIMEOUT*3/4) {
E 29
I 29
			    (MII_AN_TIMEOUT * 3)/4) {
E 29
E 28
				/*
D 28
				 * AN timeout, although we continue to detect
E 28
I 28
D 29
				 * Although AN timeout, we continue to detect
E 28
				 * 100Mbps fixed mode.
E 29
I 29
				 * Although AN timeout happened, we continue
				 * to detect 100Mbps fixed mode.
E 29
				 */
D 28

				if ((SIASTAT_LS100 & ~csr12) != 0) {
E 28
I 28
				if (SIASTAT_LS100 & ~csr12) {
E 28
					/* Link-up, move to ANDONE state */
					ret |= MII_STATUS_ANDONE;

					/* emulate parallel detection */
					lp->lpar = MII_ABILITY_100BASE_TX;

					DPRINTF(0, (CE_CONT,
D 28
					"!%s: %s: 100M fixed mode detected",
					dp->name, __func__));
				}
				else if (INL(dp, SIACTRL) & SIACTRL_ANE) {
E 28
I 28
					    "!%s: %s: 100M fixed mode detected",
					    dp->name, __func__));
				} else if (INL(dp, SIACTRL) & SIACTRL_ANE) {
E 28
					/*
					 * disable nway and select 100M
					 * for detecting 100M fixed mode.
					 */
D 28
					tu_freeze_chip(dp, NAR_ST | NAR_SR);
E 28
					tu_setup_speed_duplex(dp,
D 28
							PORT_100_HD, 0);

					DPRINTF(0, (CE_CONT,
					"!%s: %s: port changed, anstate:%d",
					dp->name, __func__, anstate));
E 28
I 28
					    PORT_100_HD, 0);
					DPRINTF(1, (CE_CONT,
					    "!%s: %s: port changed, anstate:%d",
					    dp->name, __func__, anstate));
E 28
				}
E 20
D 28
			}
I 20
			else if (anstate == 5) {
E 28
I 28
			} else if (anstate == 5) {
E 28
				/*
				 * Auto-negotiation has done.
				 * Here we need to determin common technology.
				 */
D 28
				DPRINTF(0, (CE_CONT,
					"!%s: %s, autonego done, csr12:0x%08x",
					dp->name, __func__, csr12));
E 28
I 28
				DPRINTF(1, (CE_CONT,
				    "!%s: %s, autonego done, csr12:0x%08x",
				    dp->name, __func__, csr12));
E 28
E 20

D 17
			tu_setup_speed_duplex(dp,
					(lp->bmcr & MII_CONTROL_100MB) != 0,
					(lp->bmcr & MII_CONTROL_FDUPLEX) != 0);
E 17
I 17
D 20
			/*
			 * XXX : Don't disable nway logic here.
			 * It will cause to link down.
			 */
E 20
I 20
				ret |= MII_STATUS_ANDONE;
				lp->bmcr &=
				    ~(MII_CONTROL_SPEED | MII_CONTROL_FDUPLEX);

D 28
				if ((csr12 & SIASTAT_LPN) != 0) {
E 28
I 28
				if (csr12 & SIASTAT_LPN) {
E 28
					/*
					 * the link partnar is
					 * auto-negotiatable
					 */
					lp->lpar = csr12 >> 16;
					lp->exp |= MII_AN_EXP_LPCANAN;

					/* choose common technology */
D 28
					if ((val = (lp->adv & lp->lpar)) != 0) {
E 28
I 28
					if (val = (lp->adv & lp->lpar)) {
E 28
						lp->bmcr |=
D 28
						  tu_mii_choose_technology(val);
E 28
I 28
						    tu_mii_choose_technology(
						    val);
E 28
					}
D 28
				}
				else {
E 28
I 28
				} else {
E 28
					/*
					 * As the link partnar isn't
					 * auto-negotiatable, we see
					 * current link status.
					 */
					lp->lpar = 0;
D 28
					if ((SIASTAT_LS100 & ~csr12) != 0) {
E 28
I 28
					if (SIASTAT_LS100 & ~csr12) {
E 28
						lp->bmcr |=
D 28
							MII_CONTROL_100MB;
E 28
I 28
						    MII_CONTROL_100MB;
E 28
						lp->lpar =
D 28
							MII_ABILITY_100BASE_TX;
					}
					else if ((SIASTAT_LS10 & ~csr12) != 0) {
E 28
I 28
						    MII_ABILITY_100BASE_TX;
					} else if (SIASTAT_LS10 & ~csr12) {
E 28
						lp->lpar = MII_ABILITY_10BASE_T;
					}
				}
				/*
D 29
				 * XXX : Don't disable nway logic here.
E 29
I 29
				 * XXX - Don't disable nway logic here.
E 29
				 * It will make the link down.
				 */
			}
E 20
E 17
E 16
E 9
E 2
		}
D 9
		if ((csr12 & SIASTAT_TRF) != 0) {
			ret |= MII_STATUS_REMFAULT;
		}
		if ((csr12 & SIASTAT_LPN) != 0) {
			ret |= MII_STATUS_CANAUTONEG;
		}
D 2
		if ((csr12 & SIASTAT_LS10) == 0 || (csr12 & SIASTAT_LS100) == 0) {
			ret |= MII_STATUS_LINKUP;
E 2
I 2
		if ((lp->bmcr & MII_CONTROL_100MB) != 0) {
			if ((csr12 & SIASTAT_LS100) == 0) {
				ret |= MII_STATUS_LINKUP;
			}
		} else {
			if ((csr12 & SIASTAT_LS10) == 0) {
				ret |= MII_STATUS_LINKUP;
			}
E 2
		}
E 9
D 2
#ifdef notdef
E 2
I 2

D 9
	/* Following bits are unsupported
E 9
I 9
		REPLACE_BIT(ret, MII_STATUS_REMFAULT, csr12, SIASTAT_TRF);
D 10
		REPLACE_BIT(ret, MII_STATUS_CANAUTONEG, csr12, SIASTAT_LPN);
E 10
D 16
		if ((lp->bmcr & MII_CONTROL_ANE) == 0) {
E 16
I 16

		if ((lp->bmcr & MII_CONTROL_ANE) == 0 ||
D 28
		    (ret & MII_STATUS_ANDONE) != 0) {
E 28
I 28
		    (ret & MII_STATUS_ANDONE)) {
E 28
			/* auto-negtiation isn't in progresss */
E 16
			REPLACE_BIT(ret, MII_STATUS_LINKUP, ~csr12,
D 28
				(lp->bmcr & MII_CONTROL_100MB)
					? SIASTAT_LS100 : SIASTAT_LS10);
E 28
I 28
			    (lp->bmcr & MII_CONTROL_100MB)
			    ? SIASTAT_LS100 : SIASTAT_LS10);
E 28
		}
I 17

		/*
		 * for quick link down detection to restart ANE
		 */
D 28
		if ((ret & MII_STATUS_LINKUP) != 0 && lp->ier != 0) {
E 28
I 28
		if ((ret & MII_STATUS_LINKUP) && lp->ier) {
E 28
			switch (lp->hw_info->chip_type) {
			case CHIP_21142:
			case CHIP_LC82C115:
				lp->ier |= SR_LC;
				OUTL(dp, SR, SR_LC);
				OUTL(dp, IER, lp->ier);
			}
		}

E 17
D 28
	/* Following bits are not supported
E 9
E 2
D 11
		MII_STATUS_MFPRMBLSUPR
E 11
		MII_STATUS_JABBERING
		MII_STATUS_EXTENDED
D 2
#endif
E 2
I 2
	*/
E 28
I 28
	/*
	 * Following bits are not supported
	 *	MII_STATUS_JABBERING
	 *	MII_STATUS_EXTENDED
	 */
E 28
I 9
		lp->bmsr = ret;
E 9
E 2
		break;

	case MII_AN_ADVERT:
D 2
		csr14 = INL(dp, SIACNTL);
		csr6  = INL(dp, NAR);
		ret = 0;
		if (csr14 & SIACNTL_TH) {
			ret |= MII_ABILITY_10BASE_T;
		}
		if (csr6 & NAR_FD) {
			ret |= MII_ABILITY_10BASE_T_FD;
		}
		if (csr14 & SIACNTL_TXH) {
			ret |= MII_ABILITY_100BASE_TX;
		}
		if (csr14 & SIACNTL_TXF) {
			ret |=  MII_ABILITY_100BASE_TX_FD;
		}
		if (csr14 & SIACNTL_T4) {
			ret |= MII_ABILITY_100BASE_T4;
		}
		if (csr14 & SIACNTL_PAUSE) {
			ret |= MII_ABILITY_PAUSE;
		}
E 2
I 2
		ret = lp->adv;
E 2
		break;

	case MII_AN_LPABLE:
D 2
		ret = INL(dp, SIASTAT) >> 16;
E 2
I 2
		ret = lp->lpar;
E 2
		break;
D 8
#ifdef notdef
I 2
	/* unsupported */
E 8
I 8

E 8
E 2
	case MII_AN_EXPANSION:
I 20
		ret = lp->exp;
		break;

E 20
D 8
		ret = 0;
		break;
#endif
E 8
	default:
		ret = 0;
		break;
	}

I 11
	DPRINTF(4, (CE_CONT,
D 16
		"!%s: tu_nway_read_21143: reg;%x ret:%x",
		dp->name, index, ret));
E 16
I 16
D 17
		"!%s: %s: reg:%x ret:%x",
		dp->name, __func__, index, ret));
E 17
I 17
D 28
		"!%s: %s: reg:%x ret:%x (anstate:%d)",
		dp->name, __func__, index, ret, anstate));
E 28
I 28
	    "!%s: %s: reg:%x ret:%x (anstate:%d)",
	    dp->name, __func__, index, ret, anstate));
E 28
E 17
E 16

E 11
D 17
	return ret;
E 17
I 17
	return (ret);
E 17
}

static void
D 2
tu_mii_write_sym(struct gem_dev *dp, int index, uint16_t val)
E 2
I 2
D 9
tu_mii_write_nway(struct gem_dev *dp, int index, uint16_t val)
E 9
I 9
D 16
tu_nway_write_21143(struct gem_dev *dp, int index, uint16_t val)
E 16
I 16
tu_nway_write_21143(struct gem_dev *dp, uint_t index, uint16_t new)
E 16
E 9
E 2
{
D 2
	uint32_t	reg;
	uint32_t	nar;
	uint32_t	siastat;
	uint32_t	siactrl;
	struct tu_chip_state	*lp = (struct tu_chip_state *)dp->private;
E 2
I 2
D 20
	uint32_t        reg;
E 20
I 20
D 28
	uint32_t        val;
E 28
I 28
	uint32_t	val;
E 28
E 20
I 8
	uint16_t	old;
I 9
	int		port;
E 9
E 8
D 7
	struct tu_chip_state    *lp = (struct tu_chip_state *)dp->private;
E 7
I 7
D 28
	struct tu_dev    *lp = (struct tu_dev *)dp->private;
E 28
I 28
	uint32_t	nar;
	struct tu_dev	*lp = dp->private;
E 28
E 7
E 2

D 2
	DPRINTF(4, (CE_CONT, "!mii_write_sym called"));
E 2
I 2
D 3
	DPRINTF(2, (CE_CONT, "!mii_write_nway called: reg:%x val:%04x",
		index, val));
E 3
I 3
D 9
	DPRINTF(2, (CE_CONT, "!%s: mii_write_nway called: reg:%x val:%04x",
E 9
I 9
D 16
	DPRINTF(2, (CE_CONT, "!%s: nway_write_21143 called: reg:%x val:%04x",
E 9
		dp->name, index, val));
E 16
I 16
D 17
	DPRINTF(2, (CE_CONT, "!%s: %s called: reg:%x new:%04x",
E 17
I 17
D 20
	DPRINTF(4, (CE_CONT, "!%s: %s called: reg:%x new:%04x",
E 20
I 20
D 28
	DPRINTF(0, (CE_CONT, "!%s: %s called: reg:%x new:%04x",
E 20
E 17
		dp->name, __func__, index, new));
E 28
I 28
	DPRINTF(2, (CE_CONT, "!%s: %s called: reg:%x new:%04x",
	    dp->name, __func__, index, new));
E 28
E 16
E 3
E 2

	switch (index) {
	case MII_CONTROL:
I 11
D 16
		old = lp->bmcr;
E 16
D 28
		tu_freeze_chip(dp, NAR_ST | NAR_SR);

E 28
E 11
D 16
		if ((val & MII_CONTROL_RESET) != 0) {
E 16
I 16
		/* update bmcr */
		old = lp->bmcr;
D 28
		if ((new & MII_CONTROL_ANE) != 0) {
E 28
I 28
		if (new & MII_CONTROL_ANE) {
E 28
			/* keep SPEED bits and FDUPLEX bit in bmcr */
			new &= ~(MII_CONTROL_SPEED | MII_CONTROL_FDUPLEX);
			new |= lp->bmcr &
D 28
				(MII_CONTROL_SPEED | MII_CONTROL_FDUPLEX);
E 28
I 28
			    (MII_CONTROL_SPEED | MII_CONTROL_FDUPLEX);
E 28
		}
		lp->bmcr = new;
E 16
I 6
D 9
			uint32_t	nar;
E 9
E 6
D 2
			/* Do reset */
			OUTL(dp, SIACONN, SIACONN_RST);
			drv_usecwait(10);
			OUTL(dp, SIACONN, 0);
		}
E 2

D 2
		siactrl = INL(dp, SIACNTL) & ~SIACNTL_ANE;
		if ((val & MII_CONTROL_ANE) != 0) {
			/* enable autonego */
			siactrl |= SIACNTL_ANE | SIACNTL_LTE | SIACNTL_RSQ
				|  SIACNTL_PWD10B;
		}
		OUTL(dp, SIACNTL, siactrl);
		DPRINTF(2, (CE_CONT,
			"%s: mii_write_sym miictrl: siactrl: 0x%08x",
			dp->name, siactrl));
E 2
I 2
D 9
			/* temporary stop Tx and Rx */
I 6
			nar = lp->nar;
E 6
			if ((lp->nar & (NAR_ST | NAR_SR)) != 0) {
D 6
				OUTL(dp, NAR, lp->nar & ~(NAR_ST | NAR_SR));
E 6
I 6
				lp->nar &= ~(NAR_ST | NAR_SR);
				OUTL(dp, NAR, lp->nar);
				drv_usecwait(5);
E 6
			}
E 2

E 9
D 2
		siastat = INL(dp, SIASTAT) & ~SIASTAT_ANS;
		if ((val & MII_CONTROL_RSAN) != 0) {
			/* Kick autonego */
			siastat |= 1 << SIASTAT_ANS_SHIFT;
		}
		OUTL(dp, SIASTAT, siastat);
		DPRINTF(2, (CE_CONT,
			"%s: mii_write_sym miictrl: siastat: 0x%08x",
			dp->name, siastat));
		break;
E 2
I 2
D 6
			/* select 10BastT port and make it link-down */
E 6
I 6
D 16
			/* select 10BaseT port and make it link-down */
E 16
I 16
D 28
		if ((new & MII_CONTROL_RESET) != 0) {
E 28
I 28
		if (new & MII_CONTROL_RESET) {
E 28

			/* select 10BaseT port and make the link down */
E 16
D 9
			lp->bmcr &= ~MII_CONTROL_100MB;
			tu_select_port(dp);
E 6
			tu_write_siacntl(dp, 0);
E 9
I 9
D 10
			tu_freeze_chip(dp);
E 9
E 2

E 10
D 2
	case MII_AN_ADVERT:
#ifdef SANITY
		lp->nar = INL(dp, NAR);
#endif
		nar = lp->nar & ~NAR_FD;
E 2
I 2
D 9
			/* restore default advertisement bits */
			lp->adv = MII_ABILITY_10BASE_T
				| MII_ABILITY_10BASE_T_FD
				| MII_ABILITY_100BASE_TX
				| MII_ABILITY_100BASE_TX_FD
				| MII_ABILITY_PAUSE;
E 9
I 9
D 17
			lp->nar &= ~NAR_PS;
E 17
I 17
D 28
			tu_freeze_chip(dp, NAR_ST | NAR_SR);
E 28
I 28
			nar = tu_freeze_chip(dp, NAR_ST | NAR_SR);
E 28
			lp->nar = (lp->nar & ~CSR6_PORT_BITS)
D 28
				| lp->cfg_csr6[PORT_10_HD];
E 17
D 10
			UPDATE_NAR(dp, lp->nar);
E 10
I 10
			UPDATE_NAR(dp, lp->nar & ~(NAR_ST | NAR_SR));
E 28
I 28
			    | lp->cfg_csr6[PORT_10_HD];
			UPDATE_NAR(dp, lp->nar);
E 28
I 16

E 16
E 10
			OUTL(dp, SIACONN, 0);	/* csr13 */
			OUTL(dp, SIACTRL, 0);	/* csr14 */
I 17
			OUTL(dp, SIACONN, lp->cfg_csr13[PORT_10_HD]);
E 17
E 9
E 2

D 2
		/* stop Tx and Rx temporary */
		if ((nar & (NAR_ST | NAR_SR)) != 0) {
			OUTL(dp, NAR, nar & ~(NAR_ST | NAR_SR));
E 2
I 2
D 16
			/* save current bmcr register value */
			lp->bmcr = val;
E 16
I 16
D 17
			tu_reset_phy(dp);
E 17
I 17
D 28
			tu_restart_chip(dp);
E 28
I 28
			tu_restart_chip(dp, nar);
E 28
E 17

I 17
			tu_enable_phy(dp);

E 17
E 16
I 6
D 9
			lp->nar  = nar;
E 9
E 6
D 28
			lp->reset_expire = ddi_get_lbolt()
D 9
						+ drv_usectohz(1000000);
E 9
I 9
						+ drv_usectohz(200*1000);
E 28
I 28
			lp->reset_expire =
			    ddi_get_lbolt() + drv_usectohz(200*1000);
E 28
I 16
			break;
E 16
E 9
D 11
			break;
E 11
E 2
		}
I 11
D 16
		else if ((val & MII_CONTROL_ANE) != 0) {
E 16
E 11

I 8
D 11
		old = lp->bmcr;
D 9
		lp->bmcr = val;
E 9
E 8
D 2
		siactrl = INL(dp, SIACNTL)
			& ~(SIACNTL_TH  | SIACNTL_TXH |
			    SIACNTL_TXF | SIACNTL_T4  | SIACNTL_PAUSE);

		if (val & MII_ABILITY_10BASE_T) {
			siactrl |= SIACNTL_TH;
E 2
I 2
		if ((val & MII_CONTROL_ANE) != 0) {
I 9

E 11
D 16
			/* keep 100M bit and FDUPLEX bit */
			lp->bmcr &= MII_CONTROL_100MB | MII_CONTROL_FDUPLEX;
			lp->bmcr |=
			    val & ~(MII_CONTROL_100MB | MII_CONTROL_FDUPLEX);

E 9
D 8
			lp->bmcr = val;
E 8
			if ((val & MII_CONTROL_RSAN) != 0 ||
E 16
I 16
D 28
		if ((new & MII_CONTROL_ANE) != 0) {
			if (((~old) & new & MII_CONTROL_RSAN) != 0 ||
E 16
D 8
			   ((lp->bmcr & MII_CONTROL_ANE) == 0)) {
E 8
I 8
D 17
			   ((old & MII_CONTROL_ANE) == 0)) {
E 8
D 16
				/* Issuse autonego */
E 16
I 16
				/* issuse autonego */
E 17
I 17
			     (old & MII_CONTROL_ANE) == 0) {
E 28
I 28
		if (new & MII_CONTROL_ANE) {
			if (((~old) & new & MII_CONTROL_RSAN) ||
			    (old & MII_CONTROL_ANE) == 0) {
E 28
				/* setup AN-done interrupt for quick link up */
				lp->ier |= SR_ANE;
				OUTL(dp, SR, SR_ANE);
				OUTL(dp, IER, lp->ier);

				/* issue autonego */
E 17
E 16
D 9
				tu_start_an(dp);
E 9
I 9
				tu_nway_start_21143(dp);
D 16

				/* reset auto_negotiation status bits */
				lp->bmcr &= ~MII_CONTROL_RSAN;
				lp->bmsr &= ~MII_STATUS_ANDONE;
				lp->lpar = 0;
D 11
#ifdef notdef
				/* schedule one-shot interrupt*/
E 11
I 11
#ifdef notyet
				/* schedule one-shot interrupt */
E 11
D 10
				lp->ier |= SR_ANE;
				OUTL(dp, SR, SR_ANE);
				if (!dp->intr_busy) {
					/* update hw register */
					OUTL(dp, IER, lp->ier);
E 10
I 10
				if (dp->nic_active) {
					lp->ier |= SR_ANE;
					OUTL(dp, SR, SR_ANE);
					if (!dp->intr_busy) {
						/* update hw register */
						OUTL(dp, IER, lp->ier);
					}
E 10
				}
#endif
E 16
E 9
			}
E 2
D 28
		}
I 20
		else {
E 28
I 28
		} else {
E 28
			/*
D 29
			 * XXX - we do nothing to disable nway, bacause
E 29
I 29
			 * note - no need to disable nway here, bacause
E 29
			 * nway will be disabled when tu_set_media()
			 * is called later.
			 */
		}
E 20
D 2
		if (val & MII_ABILITY_10BASE_T_FD) {
			nar |= NAR_FD;
E 2
I 2
D 17
		else {
D 8
			lp->bmcr = val;
E 8
D 9
			tu_select_port(dp);
E 9
I 9
			/* fixed mode */
D 16
			lp->bmcr = val;

			/*
			 * Configure SIA control register
			 */
			port = PORT_IX((val & MII_CONTROL_100MB) != 0,
				       (val & MII_CONTROL_FDUPLEX) != 0);

D 10
			tu_freeze_chip(dp);
E 10
I 10
D 11
			tu_freeze_chip(dp, NAR_ST | NAR_SR);
E 10

E 11
D 10
			UPDATE_NAR(dp, lp->nar & ~NAR_PS);
E 10
I 10
			UPDATE_NAR(dp, lp->nar & ~(NAR_PS | NAR_ST | NAR_SR));
E 10
			OUTL(dp, SIACONN, 0);	/* csr13 */
D 10
			OUTL(dp, SIACTRL, lp->csr14[port]);
			if (lp->csr13[port]) {
				OUTL(dp, SIACONN, lp->csr13[port]);
E 10
I 10
			OUTL(dp, SIACTRL, lp->cfg_csr14[port]);
			if (lp->cfg_csr13[port]) {
				OUTL(dp, SIACONN, lp->cfg_csr13[port]);
E 10
			}
D 10
			UPDATE_NAR(dp, lp->nar);
E 10
I 10
			UPDATE_NAR(dp, lp->nar & ~(NAR_ST | NAR_SR));
E 10

E 16
I 16
			tu_setup_speed_duplex(dp,
					(new & MII_CONTROL_100MB) != 0,
					(new & MII_CONTROL_FDUPLEX) != 0);
E 16
D 11
			tu_restart_chip(dp);
E 11
E 9
E 2
		}
E 17
I 11

I 17
		/*
D 29
		 * XXX - for fixed mode, PHY mode wil be set later
		 * on calling tu_set_media.
E 29
I 29
		 * For forced mode, PHY mode will be set on calling
		 * tu_set_media later.
E 29
		 */

E 17
D 16
		tu_restart_chip(dp);
E 16
I 16
		/* still the nic stopped */
E 16
E 11
D 2
		if (val & MII_ABILITY_100BASE_TX) {
			siactrl |= SIACNTL_TXH;
		}
		if (val & MII_ABILITY_100BASE_TX_FD) {
			siactrl |= SIACNTL_TXF;
		}
		if (val & MII_ABILITY_100BASE_T4) {
			siactrl |= SIACNTL_T4;
		}
		if (val & MII_ABILITY_PAUSE) {
			siactrl |= SIACNTL_PAUSE;
		}
		lp->nar = nar;
		OUTL(dp, NAR, nar);
		OUTL(dp, SIACNTL, siactrl);
		DPRINTF(2, (CE_CONT,
			"%s: mii_write_sym advert: siactrl: 0x%08x",
			dp->name, siactrl));
E 2
		break;

I 2
	case MII_AN_ADVERT:
D 16
		lp->adv = val;
E 16
I 16
		lp->adv = new;
E 16
		break;

E 2
	default:
D 2
		DPRINTF(0, (CE_PANIC, "%s: writing mii reg %d",
E 2
I 2
D 16
		DPRINTF(0, (CE_WARN, "%s: writing mii reg %d",
E 2
				dp->name, index));
E 16
I 16
		DPRINTF(0, (CE_WARN, "!%s: %s: invalid register %d",
D 28
				dp->name, __func__, index));
E 28
I 28
		    dp->name, __func__, index));
E 28
E 16
D 2
		return;
E 2
I 2
		break;
E 2
	}
D 28
	return;
E 28
}

I 16
/* for PNIC */
E 16
I 8
static uint16_t
D 9
tu_mii_read_nway_pnic(struct gem_dev *dp, int index)
E 9
I 9
D 16
tu_nway_read_pnic(struct gem_dev *dp, int index)
E 16
I 16
tu_nway_read_pnic(struct gem_dev *dp, uint_t index)
E 16
E 9
{
	uint16_t	ret;
	uint32_t	nway;
	uint32_t	sr;
	uint32_t	val;
D 28
	struct tu_dev	*lp = (struct tu_dev *)dp->private;
E 28
I 28
	struct tu_dev	*lp = dp->private;
E 28

	nway = INL(dp, PNIC_NWAY);

D 9
	DPRINTF(2, (CE_CONT, "!%s: tu_mii_read_nway_pnic: called: nway:0x%b",
E 9
I 9
D 17
	DPRINTF(2, (CE_CONT, "!%s: tu_nway_read_pnic: called: nway:0x%b",
E 9
			dp->name, nway, NWAY_BITS));
E 17
I 17
	DPRINTF(2, (CE_CONT, "!%s: %s: called: nway:0x%b",
D 28
			dp->name, __func__, nway, NWAY_BITS));
E 28
I 28
	    dp->name, __func__, nway, NWAY_BITS));
E 28
E 17

	switch (index) {
	case MII_CONTROL:
D 17
		if ((lp->bmcr & MII_CONTROL_RESET) != 0) {
			/*
			 * PHY reset is in progress
			 */
			if (ddi_get_lbolt() - lp->reset_expire <= 0) {
				/* timer is not expired yet. */
				break;
			}
			/*
D 9
			 * It's first access after reseting.
E 9
I 9
			 * It's first access after reset have done.
E 9
			 */
			lp->bmcr &= ~MII_CONTROL_RESET;

			/*  It's time to clear reset bit in NWAY register */
			OUTL(dp, PNIC_NWAY, nway & ~(NWAY_RS | NWAY_RN));
			nway = INL(dp, PNIC_NWAY);

			DPRINTF(2, (CE_CONT,
D 9
				"!%s: tu_mii_read_nway_pnic: nway:0x%b",
E 9
I 9
				"!%s: tu_nway_read_pnic: nway:0x%b",
E 9
				dp->name, nway, NWAY_BITS));
		}

E 17
D 9

E 9
		/* update media mode */
D 9
		ret = 0;
		if ((lp->bmcr & MII_CONTROL_ANE) != 0) {
			if ((nway & NWAY_T4) != 0) {
				/* XXX - is it right ? */
				ret |= MII_CONTROL_FDUPLEX;
				ret |= MII_CONTROL_100MB;
			}
			else if ((nway & NWAY_XF) != 0) {
				ret |= MII_CONTROL_FDUPLEX;
				ret |= MII_CONTROL_100MB;
			}
			else if ((nway & NWAY_XM) != 0) {
				ret |= MII_CONTROL_100MB;
			}
			else if ((nway & NWAY_TF) != 0) {
				ret |= MII_CONTROL_FDUPLEX;
			}
			else if ((nway & NWAY_TM) != 0) {
				/* nothing */
			}
		}
		else {
			ret |= (nway & NWAY_100) ? MII_CONTROL_100MB : 0;
			ret |= (nway & NWAY_FD) ? MII_CONTROL_FDUPLEX : 0;
		}

		ret |= (nway & 0x00000000) ? MII_CONTROL_COLTST : 0;
		ret |= (nway & NWAY_RS) ? MII_CONTROL_RESET : 0;
		ret |= (nway & 0x00000000) ? MII_CONTROL_LOOPBACK : 0;
		ret |= (nway & 0x00000000) ? MII_CONTROL_ISOLATE : 0;
		ret |= (nway & NWAY_NW) ? MII_CONTROL_ANE : 0;
		ret |= (nway & NWAY_PD) ? MII_CONTROL_PWRDN : 0;
		ret |= (nway & NWAY_RN) ? MII_CONTROL_RSAN : 0;
		ret |= (nway & 0x00000000) ? MII_CONTROL_COLTST : 0;
E 9
I 9
		ret = lp->bmcr;
		REPLACE_BIT(ret, MII_CONTROL_100MB, nway, NWAY_100);
		REPLACE_BIT(ret, MII_CONTROL_FDUPLEX, nway, NWAY_FD);
D 28
				/* MII_CONTROL_COLTST */
E 28
I 28
		/* MII_CONTROL_COLTST */
E 28
		REPLACE_BIT(ret, MII_CONTROL_RESET, nway, NWAY_RS);
D 28
				/* MII_CONTROL_LOOPBACK */
				/* MII_CONTROL_ISOLATE */
E 28
I 28
		/* MII_CONTROL_LOOPBACK */
		/* MII_CONTROL_ISOLATE */
E 28
D 16
		REPLACE_BIT(ret, MII_CONTROL_ANE, nway, NWAY_NW);
E 16
		REPLACE_BIT(ret, MII_CONTROL_PWRDN, nway, NWAY_PD);
I 16
D 17
#ifdef notdef
		/* AN bits are stateful */
E 17
		REPLACE_BIT(ret, MII_CONTROL_ANE, nway, NWAY_NW);
I 20
D 29
#if 0
		/* RSAN bit must be read as 0 always. */
E 29
I 29
#ifdef NEVER
		/* XXX - RSAN bit must be read as 0 always. */
E 29
E 20
E 16
		REPLACE_BIT(ret, MII_CONTROL_RSAN, nway, NWAY_RN);
I 20
#endif
E 20
I 16
D 17
#endif
E 17
E 16
D 28
				/* MII_CONTROL_COLTST */
E 9
D 16
		lp->bmcr = ret;
E 16
I 16
		lp->bmcr = ret;	
E 28
I 28
		/* MII_CONTROL_COLTST */
		lp->bmcr = ret;
E 28
E 16
D 17

E 17
		break;

	case MII_STATUS:
I 16
		/* set capability bits */
E 16
D 9
		/* my capability */
		ret = MII_STATUS_100_BASEX_FD
		    | MII_STATUS_100_BASEX
		    | MII_STATUS_10_FD
		    | MII_STATUS_10;

E 9
I 9
D 11
		ret = lp->bmsr;
E 11
I 11
		ret = lp->bmsr
		    | MII_STATUS_CANAUTONEG
D 16
		    | MII_STATUS_MFPRMBLSUPR
		    | MII_STATUS_100_BASEX_FD
		    | MII_STATUS_100_BASEX
		    | MII_STATUS_10_FD
		    | MII_STATUS_10;
E 16
I 16
		    | MII_STATUS_MFPRMBLSUPR;

D 17
		/* update mii state bits */
E 16
E 11
E 9
		sr= INL(dp, SR);
E 17
I 17
		/* make mii state bits */
D 29
#if 0
E 29
I 29
#ifdef NEVER
E 29
		/*
D 29
		 * XXX - NWAY_RF bit doesn't seem to represent remote fault
		 * state of the link partnar correctly.
E 29
I 29
		 * XXX - NWAY_RF bit doesn't seem to represent the remote the
		 * fault state of the link partnar correctly.
E 29
		 */
E 17
D 9
		ret |= (nway & 0x00000000) ? MII_STATUS_MFPRMBLSUPR : 0;
		ret |= (nway & (NWAY_T4|NWAY_XM|NWAY_XF|NWAY_TF|NWAY_TM))
				? MII_STATUS_ANDONE : 0;
		ret |= (nway & NWAY_RF) ? MII_STATUS_REMFAULT : 0;
		ret |= (nway & 0x00000000) ? MII_STATUS_CANAUTONEG : 0;
		ret |= (sr & SR_ANE) ? MII_STATUS_LINKUP : 0;
		ret |= (nway & 0x00000000) ? MII_STATUS_JABBERING : 0;
		ret |= (nway & 0x00000000) ? MII_STATUS_EXTENDED : 0;
E 9
I 9
		REPLACE_BIT(ret, MII_STATUS_REMFAULT, nway, NWAY_RF);
I 17
#endif
D 28
		sr= INL(dp, SR);
E 28
I 28
		sr = INL(dp, SR);
E 28
E 17
D 11
			/* MII_STATUS_MFPRMBLSUPR */
E 11
D 16
		REPLACE_BIT(ret, MII_STATUS_ANDONE, ~nway, NWAY_RN);
		REPLACE_BIT(ret, MII_STATUS_REMFAULT, nway, NWAY_RF);
E 16
D 10
			/* MII_STATUS_CANAUTONEG */
E 10
		REPLACE_BIT(ret, MII_STATUS_LINKUP, sr, SR_ANE);
D 28
			/* MII_STATUS_JABBERING */
			/* MII_STATUS_EXTENDED */
E 28
I 28
		/* MII_STATUS_JABBERING */
		/* MII_STATUS_EXTENDED */
E 28
I 16

D 17
		if ((nway & NWAY_NW) != 0  && (nway & NWAY_RN) == 0) {
E 17
I 17
D 20
		if ((nway & (NWAY_NW | NWAY_RN)) == NWAY_NW) {
E 17
			/*
			 * Auto-negotiation has done.
			 */
I 17
			if ((lp->bmcr & MII_CONTROL_RSAN) != 0) {
E 20
I 20
D 28
		if ((lp->bmcr & MII_CONTROL_ANE) != 0 &&
E 28
I 28
		if ((lp->bmcr & MII_CONTROL_ANE) &&
E 28
		    (lp->bmsr & MII_STATUS_ANDONE) == 0) {

			/* auto-negotiation is in progress now */

D 28
			if (ddi_get_lbolt() - lp->an_start_time
						> MII_AN_TIMEOUT*3/4) {
E 28
I 28
			if (ddi_get_lbolt() - lp->an_start_time >
			    MII_AN_TIMEOUT*3/4) {
E 28
E 20
				/*
I 20
				 * AN timeout, although we continue to detect
				 * 100Mbps fixed mode.
				 */
D 28

				if ((sr & SR_ANE) != 0) {
E 28
I 28
				if (sr & SR_ANE) {
E 28
					/* Link-up, move to ANDONE state */
					ret |= MII_STATUS_ANDONE;

					/* emulate parallel detection */
					lp->lpar = MII_ABILITY_100BASE_TX;

					DPRINTF(0, (CE_CONT,
D 28
					"!%s: %s: 100M fixed mode detected",
					dp->name, __func__));
				}
				else if ((nway & NWAY_NW) != 0) {
E 28
I 28
					    "!%s: %s: 100M fixed mode detected",
					    dp->name, __func__));
				} else if (nway & NWAY_NW) {
E 28
					/*
					 * disable nway and select 100M
					 * for detecting 100M fixed mode.
					 */
					nway &= ~(NWAY_NW | NWAY_RN);
D 28
					nway |=  NWAY_100;
E 28
I 28
					nway |= NWAY_100;
E 28
					OUTL(dp, PNIC_NWAY, nway);
				}
D 28
			}
			else if ((nway & (NWAY_NW | NWAY_RN)) == NWAY_NW) {
E 28
I 28
			} else if ((nway & (NWAY_NW | NWAY_RN)) == NWAY_NW) {
E 28
				/*
				 * Auto-negotiation has done.
				 */
				/*
E 20
				 * XXX - we must write back the negotiated
				 * mode to the PHY.
				 * NWAY_100 bit seems to contol speed LED and
				 * NWAY_FD bit seems to control duplex mode of
				 * internal endec.
				 */
				nway &= ~(NWAY_100 | NWAY_FD);
D 28
				if ((nway & (NWAY_XM | NWAY_XF)) != 0) {
E 28
I 28
				if (nway & (NWAY_XM | NWAY_XF)) {
E 28
					nway |= NWAY_100;
				}
D 28
				if ((nway & (NWAY_XF | NWAY_TF)) != 0) {
E 28
I 28
				if (nway & (NWAY_XF | NWAY_TF)) {
E 28
					nway |= NWAY_FD;
				}
				OUTL(dp, PNIC_NWAY, nway);
E 17

D 17
			/* enable restarting auto-negotiation */
			lp->bmcr &= ~MII_CONTROL_RSAN;
E 17
I 17
				DPRINTF(0, (CE_CONT,
D 28
					"!%s: %s: autonego done, %b",
					dp->name, __func__, nway, NWAY_BITS));
E 28
I 28
				    "!%s: %s: autonego done, %b",
				    dp->name, __func__, nway, NWAY_BITS));
E 28
E 17

D 17
			/* latch ANDONE */
			ret |= MII_STATUS_ANDONE;

			/* save link partner abilities */
			val = 0;
			REPLACE_BIT(val, MII_ABILITY_100BASE_T4, nway, NWAY_T4);
			REPLACE_BIT(val, MII_ABILITY_100BASE_TX_FD, nway, NWAY_XF);
			REPLACE_BIT(val, MII_ABILITY_100BASE_TX, nway, NWAY_XM);
			REPLACE_BIT(val, MII_ABILITY_10BASE_T, nway, NWAY_TM);
			REPLACE_BIT(val, MII_ABILITY_10BASE_T_FD, nway, NWAY_TF);
			lp->lpar = val;

			/* disable nway */
			OUTL(dp, PNIC_NWAY, nway & ~(NWAY_NW | NWAY_RN));

			DPRINTF(1, (CE_CONT,
				"!%s: %s: autonego done, %b",
				dp->name, __func__, val, MII_ABILITY_BITS));

			/*
			 * Here we need to determin common technology.
			 */
			lp->bmcr &= ~(MII_CONTROL_SPEED | MII_CONTROL_FDUPLEX);
			if ((val = (lp->adv & lp->lpar)) != 0) {
				lp->bmcr |= tu_mii_choose_technology(val);
E 17
I 17
				/* move to ANDONE state */
				ret |= MII_STATUS_ANDONE;
I 20
				lp->exp |= MII_AN_EXP_LPCANAN;

				/* extract link partnar ability */
				val = 0;
				REPLACE_BIT(val, MII_ABILITY_100BASE_T4,
D 28
								nway, NWAY_T4);
E 28
I 28
				    nway, NWAY_T4);
E 28
				REPLACE_BIT(val, MII_ABILITY_100BASE_TX_FD,
D 28
								nway, NWAY_XF);
E 28
I 28
				    nway, NWAY_XF);
E 28
				REPLACE_BIT(val, MII_ABILITY_100BASE_TX,
D 28
								nway, NWAY_XM);
E 28
I 28
				    nway, NWAY_XM);
E 28
				REPLACE_BIT(val, MII_ABILITY_10BASE_T,
D 28
								nway, NWAY_TM);
E 28
I 28
				    nway, NWAY_TM);
E 28
				REPLACE_BIT(val, MII_ABILITY_10BASE_T_FD,
D 28
								nway, NWAY_TF);
E 28
I 28
				    nway, NWAY_TF);
E 28
				lp->lpar = val;
E 20
E 17
			}
D 17
			else {
				cmn_err(CE_CONT,
			"!%s: %s autonego done, but no common technology",
					dp->name, __func__);
			}

			/* setup nic hardware for new speed and duplex mode */
			tu_setup_speed_duplex(dp,
				(lp->bmcr & MII_CONTROL_100MB) != 0,
				(lp->bmcr & MII_CONTROL_FDUPLEX) != 0);
E 17
		}
E 16
		lp->bmsr = ret;

I 17
		/*
		 * for quick link down detection to restart ANE
		 */
D 28
		if ((ret & MII_STATUS_LINKUP) != 0 && lp->ier != 0) {
E 28
I 28
		if ((ret & MII_STATUS_LINKUP) && lp->ier) {
E 28
			lp->ier |= SR_LC;
			OUTL(dp, SR, SR_LC);
			OUTL(dp, IER, lp->ier);
		}

E 17
D 16
		DPRINTF(2, (CE_CONT, "!%s: tu_nway_read_pnic: : MII_STAT:0x%b",
				dp->name, ret, MII_STATUS_BITS));
E 16
I 16
D 20
		DPRINTF(2, (CE_CONT, "!%s: %s: MII_STAT:0x%b",
				dp->name, __func__, ret, MII_STATUS_BITS));
E 20
I 20
		DPRINTF(3, (CE_CONT, "!%s: %s: MII_STAT:0x%b, csr12:%x",
D 28
				dp->name, __func__, ret, MII_STATUS_BITS,
				INL(dp, GPIO)));
E 28
I 28
		    dp->name, __func__, ret, MII_STATUS_BITS,
		    INL(dp, GPIO)));
E 28
E 20
E 16
E 9
		break;

	case MII_AN_ADVERT:
I 16
		/* return saved value at the previous auto-negotiation */
E 16
D 9
		ret = 0;
		ret |= (nway & NWAY_CAP_T4) ? MII_ABILITY_100BASE_T4 : 0;
		ret |= (nway & NWAY_CAP_XF) ? MII_ABILITY_100BASE_TX_FD : 0;
		ret |= (nway & NWAY_CAP_XM) ? MII_ABILITY_100BASE_TX : 0;
		ret |= (nway & NWAY_CAP_TM) ? MII_ABILITY_10BASE_T : 0;
		ret |= (nway & NWAY_CAP_TF) ? MII_ABILITY_10BASE_T_FD : 0;
E 9
I 9
		ret = lp->adv;
D 16
		DPRINTF(2, (CE_CONT,
				"!%s: tu_nway_read_pnic: : MII_ADV:0x%b",
				dp->name, ret, MII_ABILITY_BITS));
E 16
I 16
		DPRINTF(2, (CE_CONT, "!%s: %s: MII_ADV:0x%b",
D 28
			dp->name, __func__, ret, MII_ABILITY_BITS));
E 28
I 28
		    dp->name, __func__, ret, MII_ABILITY_BITS));
E 28
E 16
E 9
		break;

	case MII_AN_LPABLE:
I 16
D 17
		/* return saved value at the previous auto-negotiation */
E 16
D 9
		ret = 0;
		ret |= (nway & NWAY_T4) ? MII_ABILITY_100BASE_T4 : 0;
		ret |= (nway & NWAY_XF) ? MII_ABILITY_100BASE_TX_FD : 0;
		ret |= (nway & NWAY_XM) ? MII_ABILITY_100BASE_TX : 0;
		ret |= (nway & NWAY_TM) ? MII_ABILITY_10BASE_T : 0;
		ret |= (nway & NWAY_TF) ? MII_ABILITY_10BASE_T_FD : 0;

E 9
I 9
		ret = lp->lpar;
E 17
I 17
D 20
		ret = 0;
		REPLACE_BIT(ret, MII_ABILITY_100BASE_T4, nway, NWAY_T4);
		REPLACE_BIT(ret, MII_ABILITY_100BASE_TX_FD, nway, NWAY_XF);
		REPLACE_BIT(ret, MII_ABILITY_100BASE_TX, nway, NWAY_XM);
		REPLACE_BIT(ret, MII_ABILITY_10BASE_T, nway, NWAY_TM);
		REPLACE_BIT(ret, MII_ABILITY_10BASE_T_FD, nway, NWAY_TF);
		lp->lpar = ret;
E 20
I 20
		ret = lp->lpar;
E 20
E 17
D 16
		REPLACE_BIT(ret, MII_ABILITY_100BASE_T4, nway, NWAY_T4);
		REPLACE_BIT(ret, MII_ABILITY_100BASE_TX_FD, nway, NWAY_XF);
		REPLACE_BIT(ret, MII_ABILITY_100BASE_TX, nway, NWAY_XM);
		REPLACE_BIT(ret, MII_ABILITY_10BASE_T, nway, NWAY_TM);
		REPLACE_BIT(ret, MII_ABILITY_10BASE_T_FD, nway, NWAY_TF);
		lp->lpar = ret;
E 16
E 9
		break;

	case MII_AN_EXPANSION:
I 20
		ret = lp->exp;
		break;

E 20
	default:
		ret = 0;
		break;
	}

D 17
	return ret;
E 17
I 17
	return (ret);
E 17
}

static void
D 9
tu_mii_write_nway_pnic(struct gem_dev *dp, int index, uint16_t val)
E 9
I 9
D 16
tu_nway_write_pnic(struct gem_dev *dp, int index, uint16_t val)
E 16
I 16
tu_nway_write_pnic(struct gem_dev *dp, uint_t index, uint16_t val)
E 16
E 9
{
D 9
	uint32_t        reg;
E 9
I 9
D 17
	uint32_t        nway;
D 16
	char		*regname;
E 16
E 9
	struct tu_dev    *lp = (struct tu_dev *)dp->private;
D 16

E 16
I 16
#ifdef DEBUG_LEVEL
	char		*regname;
#endif
E 17
I 17
	uint32_t	nway;
D 28
	struct tu_dev	*lp = (struct tu_dev *)dp->private;
E 28
I 28
	struct tu_dev	*lp = dp->private;
E 28

E 17
E 16
	DPRINTF(2, (CE_CONT,
D 9
		"!%s: mii_write_nway_pnic called: reg:%x val:%04x",
E 9
I 9
D 10
		"!%s: nway_write_pnic called: reg:%x val:%04x",
E 9
		dp->name, index, val));
E 10
I 10
D 17
		"!%s: nway_write_pnic called: reg:%x val:%04x, csr6:0x%b",
		dp->name, index, val, INL(dp, NAR), CSR6BITS));
E 17
I 17
D 28
		"!%s: %s called: reg:%x val:%04x, csr6:0x%b",
		dp->name, __func__, index, val, INL(dp, NAR), CSR6BITS));
E 28
I 28
	    "!%s: %s called: reg:%x val:%04x, csr6:0x%b",
	    dp->name, __func__, index, val, INL(dp, NAR), CSR6BITS));
E 28
E 17
E 10

	switch (index) {
	case MII_CONTROL:
D 17
		if ((val & MII_CONTROL_RESET) != 0) {
D 9
			uint32_t	nar;
E 9
I 9
D 16
			lp->reset_expire = ddi_get_lbolt()
						+ drv_usectohz(50*1000);
E 16
I 16
			lp->reset_expire =
				ddi_get_lbolt() + drv_usectohz(50*1000);
E 16
		}
E 9

D 9
			/* temporary stop Tx and Rx */
			nar = lp->nar;
			if ((lp->nar & (NAR_ST | NAR_SR)) != 0) {
				lp->nar &= ~(NAR_ST | NAR_SR);
				OUTL(dp, NAR, lp->nar);
				drv_usecwait(5);
E 9
I 9
D 16
		if ((val & MII_CONTROL_ANE) != 0 &&
			((val & MII_CONTROL_RSAN) != 0 ||
			 (lp->bmcr & MII_CONTROL_ANE) == 0)) {
D 10

E 10
			 /* prepare for autonego, select 10M port */
			OUTL(dp, GPIO, lp->gp_data[PORT_10_HD]);
D 10
#ifdef notyet	/* it cause system hung */
E 10
I 10

D 11
#ifdef notdef	/* it cause system hung */
E 11
I 11
#ifdef notyet	/* this will cause to hung the system. */
E 11
E 10
			/* schedule link up interrupt */
D 10
			lp->ier |= SR_ANE;
			OUTL(dp, SR, SR_ANE);
			if (!dp->intr_busy) {
				OUTL(dp, IER, lp->ier);
E 10
I 10
			if (dp->nic_active) {
				lp->ier |= SR_ANE;
				OUTL(dp, SR, SR_ANE);
				if (!dp->intr_busy) {
					OUTL(dp, IER, lp->ier);
				}
E 16
I 16
		nway = INL(dp, PNIC_NWAY);
		if ((val & MII_CONTROL_ANE) != 0) {
			 if ((lp->bmcr & MII_CONTROL_ANE) == 0 ||
			     ((~lp->bmcr) & val & MII_CONTROL_RSAN) != 0) {
				/*
				 * prepare for autonego, select 10M port
				 */
				OUTL(dp, GPIO, lp->gp_data[PORT_10_HD]);
				nway |= NWAY_NW | NWAY_RN;
E 16
E 10
E 9
			}
I 9
D 16
#endif
E 16
		}
I 16

		/* update bmcr */
E 16
		lp->bmcr = val;
D 16
		nway = INL(dp, PNIC_NWAY);
E 16
I 16
#ifdef DEBUG_LEVEL
E 16
		regname = "MII_CONTROL";
I 16
#endif
E 17
E 16
		break;
E 9

D 9
			/* select 10BaseT port and make it link-down */
			lp->bmcr &= ~MII_CONTROL_100MB;
			tu_select_port(dp);
E 9
I 9
	case MII_AN_ADVERT:
		lp->adv = val;
D 17
		nway = INL(dp, PNIC_NWAY);
I 16
#ifdef DEBUG_LEVEL
E 16
		regname = "MII_AN_ADVERT";
I 16
#endif
E 16
		break;
E 17
I 17
		/* don't change NWAY register */
		return;
E 17
E 9

D 9
			/* XXX - how we make it down */
E 9
I 9
	default:
D 28
		cmn_err(CE_WARN, 
D 17
			"%s: tu_nway_write_pnic: writing 0x%04x to reg:%d",
			dp->name, val, index);
E 17
I 17
			"%s: %s: writing 0x%04x to unimplemented register:%d",
			dp->name, __func__, val, index);
E 28
I 28
		cmn_err(CE_WARN,
		    "%s: %s: writing 0x%04x to unimplemented register:%d",
		    dp->name, __func__, val, index);
E 28
E 17
		return;
	}
E 9

I 17
D 28
	/* 
E 28
I 28
	/*
E 28
	 * case MII_CONTROL:
	 */
D 20
	if ((val & MII_CONTROL_ANE) != 0) {
		/*
		 * prepare for autonego, select 10M port
		 */
		tu_setup_speed_duplex(dp, PORT_10_HD, SIACTRL_ANE);
E 20

D 20
		if ((val & MII_CONTROL_RSAN) != 0) {
			val &= ~MII_CONTROL_100MB;
		}
	}

	/* update bmcr and bmsr */
	lp->bmcr = val;

	/* Only ANDONE is stateful */
	lp->bmsr &= ~MII_STATUS_ANDONE;

E 20
E 17
D 9
			/* save current bmcr register value */
			lp->bmcr = val;
			lp->nar  = nar;
			lp->reset_expire = ddi_get_lbolt()
						+ drv_usectohz(1000000);
		}
		else if ((val & MII_CONTROL_ANE) != 0) {
			if ((val & MII_CONTROL_RSAN) != 0 ||
			   ((lp->bmcr & MII_CONTROL_ANE) == 0)) {
E 9
I 9
	/* update NWAY register */
I 17
	nway = INL(dp, PNIC_NWAY);

	/* clear link partner ability bits */
	nway &= ~(NWAY_T4 | NWAY_XM | NWAY_XF | NWAY_TM | NWAY_TF);
I 20
	REPLACE_BIT(nway, NWAY_NW, val, MII_CONTROL_ANE);
E 20

E 17
E 9
D 16

D 9
				/* prepare for  autonego */
E 9
I 9
	/* XXX - dont use saved RSAN bit as it is auto-clear
	 * REPLACE_BIT(nway, NWAY_RN, lp->bmcr, MII_CONTROL_RSAN);
	 */
E 16
D 20
	REPLACE_BIT(nway, NWAY_RS, lp->bmcr, MII_CONTROL_RESET);
E 20
I 20
D 28
	if ((val & MII_CONTROL_ANE) != 0 &&
	   ((lp->bmcr & MII_CONTROL_ANE) == 0 ||
	    (val & MII_CONTROL_RSAN) != 0)) {
E 28
I 28
	if ((val & MII_CONTROL_ANE) &&
	    ((lp->bmcr & MII_CONTROL_ANE) == 0 ||
	    (val & MII_CONTROL_RSAN))) {
E 28
		/*
		 * start/restart auto-negotiation
		 */
		/* prepare for autonego, select 10M port */
		tu_setup_speed_duplex(dp, PORT_10_HD, SIACTRL_ANE);
I 28

E 28
		val &= ~MII_CONTROL_100MB;
		nway |= NWAY_RN;

		/* Only ANDONE is stateful */
		lp->bmsr &= ~MII_STATUS_ANDONE;
		lp->lpar = 0;
D 28
		lp->exp  = 0;
E 28
I 28
		lp->exp = 0;
E 28
		lp->an_start_time = ddi_get_lbolt();
	} else {
		/* don't initiate auto-negotiation */
		nway &= ~NWAY_RN;
	}
	/* RSAN bit is auto-clear. */
	val &= ~MII_CONTROL_RSAN;

	REPLACE_BIT(nway, NWAY_RS, val, MII_CONTROL_RESET);
E 20
D 17
				/* MII_CONTROL_LOOPBACK */
E 17
I 17
D 28
					  /* MII_CONTROL_LOOPBACK */
E 28
I 28
	/* MII_CONTROL_LOOPBACK */
E 28
E 17
D 20
	REPLACE_BIT(nway, NWAY_100, lp->bmcr, MII_CONTROL_100MB);
I 16
D 17
#ifdef notdef
E 17
E 16
	REPLACE_BIT(nway, NWAY_NW, lp->bmcr, MII_CONTROL_ANE);
I 16
D 17
#endif
E 17
E 16
	REPLACE_BIT(nway, NWAY_PD, lp->bmcr, MII_CONTROL_PWRDN);
E 20
I 20
	REPLACE_BIT(nway, NWAY_100, val, MII_CONTROL_100MB);
	REPLACE_BIT(nway, NWAY_PD, val, MII_CONTROL_PWRDN);
E 20
D 17
				/* MII_CONTROL_ISOLATE */
I 16
#ifdef notdef
E 17
I 17
D 28
			  		  /* MII_CONTROL_ISOLATE */
E 28
I 28
	/* MII_CONTROL_ISOLATE */
E 28
E 17
E 16
D 20
	REPLACE_BIT(nway, NWAY_RN, lp->bmcr, MII_CONTROL_RSAN);
I 16
D 17
#endif
E 17
E 16
	REPLACE_BIT(nway, NWAY_FD, lp->bmcr, MII_CONTROL_FDUPLEX);
E 20
I 20
	REPLACE_BIT(nway, NWAY_FD, val, MII_CONTROL_FDUPLEX);
E 20
D 17
				/* MII_CONTROL_COLTST */
E 9

E 17
I 17
D 28
					  /* MII_CONTROL_COLTST */
E 28
I 28
	/* MII_CONTROL_COLTST */
E 28
I 20
	/* update bmcr */
	lp->bmcr = val;

E 20
	/* set my ability */
E 17
D 9
				/* select 10M port */
				OUTL(dp, PNIC_GPIO,
					PNIC_GPIO_100_LB | PNIC_GPIO_RL_10);
				drv_usecwait(1000*50);
E 9
I 9
	REPLACE_BIT(nway, NWAY_CAP_T4, lp->adv, MII_ABILITY_100BASE_T4);
	REPLACE_BIT(nway, NWAY_CAP_XM, lp->adv, MII_ABILITY_100BASE_TX);
	REPLACE_BIT(nway, NWAY_CAP_XF, lp->adv, MII_ABILITY_100BASE_TX_FD);
	REPLACE_BIT(nway, NWAY_CAP_TM, lp->adv, MII_ABILITY_10BASE_T);
	REPLACE_BIT(nway, NWAY_CAP_TF, lp->adv, MII_ABILITY_10BASE_T_FD);
D 28
	REPLACE_BIT(nway, NWAY_RF,     lp->adv, MII_AN_ADVERT_REMFAULT);
E 28
I 28
	REPLACE_BIT(nway, NWAY_RF, lp->adv, MII_AN_ADVERT_REMFAULT);
E 28
E 9

D 9
				lp->nar &= ~NAR_PS;
				lp->nar |= NAR_SCR;
				OUTL(dp, NAR, lp->nar & ~(NAR_ST | NAR_SR));
				drv_usecwait(5);
E 9
I 9
	OUTL(dp, PNIC_NWAY, nway);
I 10
D 11
#ifdef notdef
E 10
	lp->pnic_nway = nway;	/* save current nway */
E 9
D 10

E 10
I 10
#endif
E 11
I 11

E 11
E 10
D 9
				DPRINTF(2, (CE_CONT,
					"!%s: mii_write_nway_pnic: csr6:%b",
					dp->name, lp->nar, CSR6BITS));
			}
			lp->bmcr = val;
		}
		else {
			lp->bmcr = val;
			tu_select_port(dp);
		}
E 9
I 9
D 16
	DPRINTF(2, (CE_CONT,
		"!%s: nway_write_pnic %s nway: 0x%b",
E 16
I 16
D 17
	DPRINTF(2, (CE_CONT, "!%s: tu_nway_write_pnic %s nway: 0x%b",
E 16
		dp->name, regname, nway, NWAY_BITS));
E 17
I 17
	DPRINTF(0, (CE_CONT, "!%s: %s writing nway: 0x%b",
D 28
		dp->name, __func__, nway, NWAY_BITS));
E 28
I 28
	    dp->name, __func__, nway, NWAY_BITS));
E 28
E 17
E 9
D 16

D 9
		reg = INL(dp, PNIC_NWAY) &
		~(NWAY_RS | NWAY_100 | NWAY_NW | NWAY_PD | NWAY_RN | NWAY_FD);
E 9
I 9
	return;
E 16
}
E 9

D 9
		reg |= (val & MII_CONTROL_RESET)	? NWAY_RS : 0;
		reg |= (val & MII_CONTROL_LOOPBACK)	? 0x00000000 : 0;
		reg |= (val & MII_CONTROL_100MB)	? NWAY_100 : 0;
		reg |= (val & MII_CONTROL_ANE)		? NWAY_NW : 0;
		reg |= (val & MII_CONTROL_PWRDN)	? NWAY_PD : 0;
		reg |= (val & MII_CONTROL_ISOLATE)	? 0x00000000 : 0;
		reg |= (val & MII_CONTROL_RSAN)		? NWAY_RN : 0;
		reg |= (val & MII_CONTROL_FDUPLEX)	? NWAY_FD : 0;
		reg |= (val & MII_CONTROL_COLTST)	? 0x00000000 : 0;
E 9
I 9
D 10
static int8_t	mc_to_port[] = {
E 10
I 10
static uint16_t
D 16
tu_no_nway_read(struct gem_dev *dp, int index)
E 16
I 16
tu_no_nway_read(struct gem_dev *dp, uint_t index)
E 16
{
D 17
	struct tu_dev    *lp = (struct tu_dev *)dp->private;
E 17
I 17
D 28
	struct tu_dev	*lp = (struct tu_dev *)dp->private;
E 28
I 28
	struct tu_dev	*lp = dp->private;
E 28
E 17
	uint16_t	ret;

	ret = 0;
	switch (index) {
	case MII_CONTROL:
		ret = lp->bmcr;
		break;
I 28

E 28
	case MII_STATUS:
		/* TODO: should return proper link status */
D 11
		ret = lp->bmsr | MII_STATUS_LINKUP;
E 11
I 11
		ret = lp->bmsr
		    | MII_STATUS_LINKUP
D 16
		    | MII_STATUS_MFPRMBLSUPR
		    | MII_STATUS_100_BASEX_FD
		    | MII_STATUS_100_BASEX
		    | MII_STATUS_10_FD
		    | MII_STATUS_10;
E 16
I 16
		    | MII_STATUS_MFPRMBLSUPR;
E 16
E 11
		break;
I 11

E 11
	case MII_AN_ADVERT:
		ret = lp->adv;
		break;
	}
D 17
	return ret;
E 17
I 17
	return (ret);
E 17
}

static void
D 16
tu_no_nway_write(struct gem_dev *dp, int index, uint16_t val)
E 16
I 16
tu_no_nway_write(struct gem_dev *dp, uint_t index, uint16_t val)
E 16
{
D 28
	struct tu_dev    *lp = (struct tu_dev *)dp->private;
E 28
I 28
	struct tu_dev    *lp = dp->private;
E 28

	switch (index) {
	case MII_CONTROL:
		lp->bmcr = val;
		break;
D 11
#ifdef notdef
	case MII_STATUS:
		lp->bmsr = val;
		break;
#endif
E 11
I 11

E 11
	case MII_AN_ADVERT:
		lp->adv = val;
		break;
I 11

	default:
		cmn_err(CE_WARN,
D 28
			"!%s: writing to register %d in phy isn't permitted.",
			dp->name, index);
E 28
I 28
		    "!%s: writing to register %d in phy isn't permitted.",
		    dp->name, index);
E 28
		break;
E 11
	}
}

static int8_t	mc_to_port[0x12] = {
E 10
D 29
	PORT_10_HD,	/* 0 10Base T */
	-1,		/* 1 10Base2 BNC */
	-1,		/* 2 10Base5 BNC */
	PORT_100_HD,	/* 3 100BaseTX */
E 29
I 29
	PORT_10_HD,	/* 0x0: 10Base T */
	-1,		/* 0x1: 10Base2 BNC */
	-1,		/* 0x2: 10Base5 BNC */
	PORT_100_HD,	/* 0x3: 100BaseTX */
E 29
E 9

D 9
		OUTL(dp, PNIC_NWAY, reg & ~NWAY_RN);
		OUTL(dp, PNIC_NWAY, reg);
		DPRINTF(2, (CE_CONT,
			"!%s: mii_write_nway_pnic called: nway:0x%b",
			dp->name, reg, NWAY_BITS));
E 9
I 9
D 29
	PORT_10_FD,	/* 4 10Base T full duplex */
D 16
	PORT_100_FD,	/* 5 100BaseTX */
E 16
I 16
	PORT_100_FD,	/* 5 100BaseTX full duplex */
E 16
	-1,		/* 6 100BaseT4 */
	-1,		/* 7 100BaseFx */
E 29
I 29
	PORT_10_FD,	/* 0x4: 10Base T full duplex */
	PORT_100_FD,	/* 0x5: 100BaseTX full duplex */
	-1,		/* 0x6: 100BaseT4 */
	-1,		/* 0x7: 100BaseFx */
E 29

D 29
	-1,		/* 8 100BaseFx full duplex */
	PORT_10_HD,	/* 9 MII 10BaseT */
D 16
	PORT_10_FD,	/* a MII 10BaseT full*/
E 16
I 16
	PORT_10_FD,	/* a MII 10BaseT full duplex */
E 16
D 28
	-1,		/* b none*/
E 28
I 28
	-1,		/* b none */
E 29
I 29
	-1,		/* 0x8: 100BaseFx full duplex */
	PORT_10_HD,	/* 0x9: MII 10BaseT */
	PORT_10_FD,	/* 0xa: MII 10BaseT full duplex */
	-1,		/* 0xb: none */
E 29
E 28
I 10

E 10
D 28
	-1,		/* c none*/
E 28
I 28
D 29
	-1,		/* c none */
E 28
	PORT_100_HD,	/* d MII 100base */
D 16
	PORT_100_FD,	/* e MII 100base */
E 16
I 16
	PORT_100_FD,	/* e MII 100base full duplex */
E 16
D 28
	-1,		/* f MII 100base Fx*/
E 28
I 28
	-1,		/* f MII 100base Fx */
E 29
I 29
	-1,		/* 0xc: none */
	PORT_100_HD,	/* 0xd: MII 100base */
	PORT_100_FD,	/* 0xe: MII 100base full duplex */
	-1,		/* 0xf: MII 100base Fx */
E 29
E 28
I 10

D 28
	-1,		/* 10 MII 100base Fx*/
E 28
I 28
D 29
	-1,		/* 10 MII 100base Fx */
E 28
	-1,		/* 11 MII 100base Fx full duplex */
E 29
I 29
	-1,		/* 0x10: MII 100base Fx */
	-1,		/* 0x11: MII 100base Fx full duplex */
E 29
E 10
};

I 10
#define	CMD_BITS (NAR_SCR | NAR_PCS | NAR_TTM | NAR_PS)

I 16
D 28
#define	SROM_READ_BYTE(x, cp)		{x = *cp++;}
#define	SROM_READ_WORD(x, cp)		{x = LEWORD(cp); cp += 2;}
#define	SROM_READ_RECORD(x, cp, len)	{x = cp; cp += len;}
E 28
I 28
D 29
#define	SROM_READ_BYTE(x, cp)		{ x = *cp++; }
#define	SROM_READ_WORD(x, cp)		{ x = LEWORD(cp); cp += 2; }
#define	SROM_READ_RECORD(x, cp, len)	{ x = cp; cp += len; }
E 29
I 29
#define	SROM_READ_BYTE(x, cp)		{ x = *(cp)++; }
#define	SROM_READ_WORD(x, cp)		{ x = LEWORD(cp); (cp) += 2; }
#define	SROM_READ_RECORD(x, cp, len)	{ x = cp; (cp) += len; }
E 29
E 28

E 16
E 10
static int
tu_srom_media_block(struct gem_dev *dp, uint8_t *cp)
{
D 16
	uint_t	type;
	uint_t	length;
	int	port;
	uint_t	ext;
	uint_t	f;
	uint_t	media_code;
	uint_t	gp_data;
	uint_t	cmd;
	uint_t	phy;
I 10
	uint_t	mii_ind;
E 10
	int	i;
E 16
I 16
	int		info_blk_fmt;
	int		length;
	int		port;
	int		ext;
	int		f;
	int		media_code;
	uint_t		gp_data;
	uint_t		cmd;
	int		phy;
	uint_t		mii_ind;
	int		i;
E 16
	uint16_t	media_cap, adv, fdx, ttm;
D 28
	struct tu_dev	*lp = (struct tu_dev *)dp->private;
E 28
I 28
	struct tu_dev	*lp = dp->private;
E 28

D 16
	f = (cp[0] & 0x80) != 0;
E 16
I 16
	/* peek first byte */
D 29
	f = (*cp & 0x80) != 0;
E 29
I 29
	f = BOOLEAN(*cp & 0x80);
E 29
E 16

D 29
	if (f == 0) {
E 29
I 29
	if (f == B_FALSE) {
E 29
D 10
		/* 21140 compat format */
E 10
I 10
D 16
		/* 21140 compact format */
E 16
I 16
		/* 21140 compact format for non MII media */
E 16
E 10
		length = 3;
D 16
		media_code = cp[0] & 0x3f;
D 10
		port = mc_to_port[media_code & 0xf];
		lp->gp_data[port]    = cp[1];
E 10
		cmd = (cp[3] << 8) | cp[2];
E 16
I 16
D 29
		info_blk_fmt = -1;
E 29
I 29
		info_blk_fmt = -1;	/* invalid */
E 29
E 16

		DPRINTF(0, (CE_CONT,
D 10
			"!type: 21140 Compact Format\n"
			"media code:0x%04x gp_data[%d]:0x%02x cmd 0x%04x",
			media_code, port, lp->gp_data[port], cmd));
E 10
I 10
D 16
			"!type: 21140 Compact Format -  "
			"media_code:0x%04x gp_data:0x%02x cmd:0x%04x",
			media_code, cp[1], cmd));
E 16
I 16
D 28
			"!info_blk_fmt: 21140 Compact Format"));
	}
	else {
E 28
I 28
D 29
		    "!info_blk_fmt: 21140 Compact Format"));
E 29
I 29
		    "!21140 compact format"));
E 29
	} else {
E 28
		/* variable length extended format */
		SROM_READ_BYTE(length, cp);
		length &= 0x7f;
E 16

D 16
		if ((media_code & 0xff) >= 0x10) {
E 16
I 16
		SROM_READ_BYTE(info_blk_fmt, cp);

		DPRINTF(0, (CE_CONT,
D 28
			"!f:%d length:%d info_blk_fmt:%d",
			f, length, info_blk_fmt));
E 28
I 28
D 29
		    "!f:%d length:%d info_blk_fmt:%d",
		    f, length, info_blk_fmt));
E 29
I 29
		    "!variable length extended format: len:%d info_blk_fmt:%d",
		    length, info_blk_fmt));
E 29
E 28
	}

	switch (info_blk_fmt) {
	case -1: /* 21140 compact format for non MII media */
	case 0: /* for 21140 with non MII media */
		SROM_READ_BYTE(media_code, cp);

		media_code &= 0x3f;
		if ((port = mc_to_port[media_code]) < 0) {
I 28
			DPRINTF(0, (CE_CONT, "! unknown media code:0x%x",
			    media_code));
E 28
E 16
			goto x;
		}
D 16
		port = mc_to_port[media_code & 0xf];
		if (port < 0) {
			goto x;
		}
E 16

D 16
		lp->gp_data[port] = cp[1];
		lp->cfg_csr6[port] = (lp->cfg_csr6[port] & ~CMD_BITS)
				   | ((cmd << 18) & CMD_BITS);
E 10
		goto x;
	}
E 16
I 16
		SROM_READ_BYTE(lp->gp_data[port], cp);
E 16

D 16
	length = cp[0] & 0x7f;
	type = cp[1];
	ext = (cp[2] & 0x40) != 0;
D 10
	media_code =  cp[2] & 0x1f;
	port = mc_to_port[media_code & 0xf];
E 10
I 10
	media_code =  cp[2] & 0x3f;
E 16
I 16
		switch (port) {
		case PORT_10_HD:
			lp->cfg_csr6[port] = 0;
			lp->bmsr |= MII_STATUS_10;
			break;
E 16
E 10

D 10
	DPRINTF(0, (CE_CONT, "!f:%d length:%d type: 0x%x",
		f, length, type));
E 10
I 10
D 16
	DPRINTF(0, (CE_CONT, "!f:%d length:%d type: 0x%x media_code:0x%x",
		f, length, type, media_code));
E 16
I 16
		case PORT_10_FD:
			lp->cfg_csr6[port] = NAR_SQE | NAR_FD;
			lp->bmsr |= MII_STATUS_10_FD;
			break;
E 16
E 10

I 10
D 16
	if (media_code >= 0x10) {
		goto x;
	}
	port = mc_to_port[media_code & 0xf];
	if (port < 0) {
		goto x;
	}
E 16
I 16
		case PORT_100_HD:
			lp->cfg_csr6[port] = NAR_SQE;
			lp->bmsr |= MII_STATUS_100_BASEX;
			break;
E 16

E 10
D 16
	switch (type) {
	case 0:
		/* for 21140 with non MII media */
		lp->gp_data[port] = cp[3];
		cmd = (cp[5] << 8) | cp[4];
D 10

E 10
I 10
		lp->cfg_csr6[port] = (lp->cfg_csr6[port] & ~CMD_BITS)
				   | ((cmd << 18) & CMD_BITS);
E 16
I 16
		case PORT_100_FD:
			lp->cfg_csr6[port] = NAR_SQE | NAR_FD;
			lp->bmsr |= MII_STATUS_100_BASEX_FD;
			break;
		}

		SROM_READ_WORD(cmd, cp);
		lp->cfg_csr6[port] |= (cmd << 18) & CMD_BITS;

E 16
E 10
		DPRINTF(0, (CE_CONT,
D 10
		"!ext: %d  media code:0x%x gp_data[%d]:0x%04x, cmd:0x%04x",
			ext, media_code, port, lp->gp_data[port], cmd));
E 10
I 10
D 16
		"!media code:0x%x port:%d gp_data:0x%04x, cmd:0x%04x",
E 16
I 16
D 28
			"!media code:0x%x port:%d gp_data:0x%04x, cmd:0x%04x",
E 16
			media_code, port, lp->gp_data[port], cmd));
E 28
I 28
		    "!media code:0x%x port:%d gp_data:0x%04x, cmd:0x%04x",
		    media_code, port, lp->gp_data[port], cmd));
E 28
E 10
E 9
		break;

D 9
	case MII_AN_ADVERT:
E 9
I 9
D 16
	case 1:
		/* for 21140 with MII media */
		phy = cp[2];
		lp->gp_seq_len = cp[3];
		lp->gp_seq = &cp[4];
E 16
I 16
	case 1: /* for 21140 with MII media */
	case 3: /* for 21142/43/45 with MII media */
		lp->gp_seq_unit =
D 28
		lp->reset_seq_unit = (info_blk_fmt == 1) ? 1 : 2;
E 28
I 28
		    lp->reset_seq_unit = (info_blk_fmt == 1) ? 1 : 2;
E 28
E 16
E 9

D 9
		reg = INL(dp, PNIC_NWAY) &
	~(NWAY_CAP_T4 | NWAY_CAP_XF | NWAY_CAP_XM | NWAY_CAP_TM | NWAY_CAP_TF);
E 9
I 9
D 16
		lp->reset_seq_len = cp[4 + lp->gp_seq_len];
		lp->reset_seq = &cp[5 + lp->gp_seq_len];
E 16
I 16
		SROM_READ_BYTE(phy, cp);
E 16
E 9

D 9
		reg |= (val & MII_ABILITY_100BASE_T4   ) ? NWAY_CAP_T4 : 0;
		reg |= (val & MII_ABILITY_100BASE_TX   ) ? NWAY_CAP_XM : 0;
		reg |= (val & MII_ABILITY_100BASE_TX_FD) ? NWAY_CAP_XF : 0;
		reg |= (val & MII_ABILITY_10BASE_T     ) ? NWAY_CAP_TM : 0;
		reg |= (val & MII_ABILITY_10BASE_T_FD  ) ? NWAY_CAP_TF : 0;
E 9
I 9
D 16
		i = 5 + lp->gp_seq_len + lp->reset_seq_len;
D 11
		media_cap = (cp[i+1] << 8) | cp[i+0];
E 11
I 11
		media_cap = (cp[i+1] << 8) | cp[i+0];	/* not used */
E 11
I 10
#ifdef notyet
		lp->bmsr = (lp->bmsr & ~MII_STATUS_ABILITY)
			 | (media_cap & MII_STATUS_ABILITY);
#endif
E 10
		adv = (cp[i+3] << 8) | cp[i+2];
		fdx = (cp[i+5] << 8) | cp[i+4];
		ttm = (cp[i+7] << 8) | cp[i+6];
E 16
I 16
		SROM_READ_BYTE(lp->gp_seq_len, cp);
		SROM_READ_RECORD(lp->gp_seq, cp,
D 28
				 lp->gp_seq_len * lp->gp_seq_unit);
E 28
I 28
		    lp->gp_seq_len * lp->gp_seq_unit);
E 28
E 16
E 9

I 10
D 16
		for (i=0; i<4; i++) {
			lp->cfg_csr6[i] &= ~NAR_FD;
E 16
I 16
		SROM_READ_BYTE(lp->reset_seq_len, cp);
		SROM_READ_RECORD(lp->reset_seq, cp,
D 28
				 lp->reset_seq_len * lp->reset_seq_unit);
E 28
I 28
		    lp->reset_seq_len * lp->reset_seq_unit);
E 28

		SROM_READ_WORD(media_cap, cp);
		SROM_READ_WORD(adv, cp);
		SROM_READ_WORD(fdx, cp);
		SROM_READ_WORD(ttm, cp);

D 26
		media_cap &= MII_STATUS_ABILITY;
E 26
I 26
		media_cap &= MII_STATUS_ABILITY_TECH;
E 26
D 28
		if (media_cap != 0) {
E 28
I 28
		if (media_cap) {
E 28
			/*
			 * configure supported media bits in phy status
			 * register.
			 */
D 26
			lp->bmsr = (lp->bmsr & ~MII_STATUS_ABILITY) | media_cap;
E 26
I 26
			lp->bmsr =
			    (lp->bmsr & ~MII_STATUS_ABILITY_TECH) | media_cap;
E 26
		}

		/* configure auto negotiation advertisement bits */
D 28
		dp->anadv_100t4  = (adv & MII_ABILITY_100BASE_T4) != 0;
		dp->anadv_100fdx = (adv & MII_ABILITY_100BASE_TX_FD) != 0;
		dp->anadv_100hdx = (adv & MII_ABILITY_100BASE_TX) != 0;
		dp->anadv_10fdx  = (adv & MII_ABILITY_10BASE_T_FD) != 0;
		dp->anadv_10hdx  = (adv & MII_ABILITY_10BASE_T) != 0;
E 28
I 28
D 29
		dp->anadv_100t4  &= (adv & MII_ABILITY_100BASE_T4) != 0;
		dp->anadv_100fdx &= (adv & MII_ABILITY_100BASE_TX_FD) != 0;
		dp->anadv_100hdx &= (adv & MII_ABILITY_100BASE_TX) != 0;
		dp->anadv_10fdx  &= (adv & MII_ABILITY_10BASE_T_FD) != 0;
		dp->anadv_10hdx  &= (adv & MII_ABILITY_10BASE_T) != 0;
E 29
I 29
		dp->anadv_100t4 &= BOOLEAN(adv & MII_ABILITY_100BASE_T4);
		dp->anadv_100fdx &= BOOLEAN(adv & MII_ABILITY_100BASE_TX_FD);
		dp->anadv_100hdx &= BOOLEAN(adv & MII_ABILITY_100BASE_TX);
		dp->anadv_10fdx &= BOOLEAN(adv & MII_ABILITY_10BASE_T_FD);
		dp->anadv_10hdx &= BOOLEAN(adv & MII_ABILITY_10BASE_T);
E 29
E 28

		/* configure csr6 for MII media */
		for (i = 0; i < NUM_PORT_SELECTION; i++) {
			lp->cfg_csr6[i] = NAR_PS | NAR_SQE;
E 16
			if (fdx & (1 << (i+11))) {
				lp->cfg_csr6[i] |= NAR_FD;
			}
D 16

			lp->cfg_csr6[i] &= ~NAR_TTM;
E 16
			if (ttm & (1 << (i+11))) {
				lp->cfg_csr6[i] |= NAR_TTM;
			}
		}
I 16
		if (info_blk_fmt == 3) {
			SROM_READ_BYTE(mii_ind, cp);	/* not used */
		}
E 16

E 10
D 9
		OUTL(dp, PNIC_NWAY, reg);
		DPRINTF(2, (CE_CONT,
			"!%s: mii_write_nway_pnic called: nway: 0x%b",
			dp->name, reg, NWAY_BITS));
E 9
I 9
		DPRINTF(0, (CE_CONT, "!phy index: %d", phy));
		DPRINTF(0, (CE_CONT,
D 28
			"!gp_seq_len:%d data:%02x %02x %02x %02x",
D 16
			lp->gp_seq_len, cp[4], cp[5], cp[6], cp[7]));
E 16
I 16
			lp->gp_seq_len,
D 17
			lp->gp_seq[0], lp->gp_seq[1], lp->gp_seq[2], lp->gp_seq[3]));
E 17
I 17
			lp->gp_seq[0], lp->gp_seq[1],
			lp->gp_seq[2], lp->gp_seq[3]));
E 28
I 28
		    "!gp_seq_len:%d data:%02x %02x %02x %02x",
		    lp->gp_seq_len,
		    lp->gp_seq[0], lp->gp_seq[1],
		    lp->gp_seq[2], lp->gp_seq[3]));
E 28
E 17
E 16

		DPRINTF(0, (CE_CONT,
D 28
			"!reset_seq_len:%d data:%02x %02x %02x %02x",
			lp->reset_seq_len,
D 16
			cp[5+lp->gp_seq_len], cp[6+lp->gp_seq_len],
			cp[7+lp->gp_seq_len], cp[8+lp->gp_seq_len]));
E 16
I 16
			lp->reset_seq[0], lp->reset_seq[1],
			lp->reset_seq[2], lp->reset_seq[3]));
E 28
I 28
		    "!reset_seq_len:%d data:%02x %02x %02x %02x",
		    lp->reset_seq_len,
		    lp->reset_seq[0], lp->reset_seq[1],
		    lp->reset_seq[2], lp->reset_seq[3]));
E 28
E 16

D 16
		DPRINTF(0, (CE_CONT, "!adv 0x%04x, fdx: 0x%04x, ttm: 0x%04x",
			adv, fdx, ttm));
E 16
I 16
D 17
		DPRINTF(0, (CE_CONT, "!media_cap 0x%04x, adv 0x%04x, fdx 0x%04x, ttm 0x%04x",
E 17
I 17
		DPRINTF(0, (CE_CONT,
D 28
			"!media_cap 0x%04x, adv 0x%04x, fdx 0x%04x, ttm 0x%04x",
E 17
			media_cap, adv, fdx, ttm));
E 28
I 28
		    "!media_cap 0x%04x, adv 0x%04x, fdx 0x%04x, ttm 0x%04x",
		    media_cap, adv, fdx, ttm));
E 28
E 16
E 9
		break;

I 9
D 16
	case 2:
		/* 21142/43 */
		if (ext == 0) {
			lp->gp_ctrl[port] = (cp[4] << 8) | cp[3];
			lp->gp_data[port] = (cp[6] << 8) | cp[5];
		} else {
D 10
			lp->csr13[port] = (cp[4] << 8) | cp[3];
			lp->csr14[port] = (cp[6] << 8) | cp[5];
			lp->csr15[port] = (cp[8] << 8) | cp[7];
E 10
I 10
			lp->cfg_csr13[port] = (cp[4] << 8) | cp[3];
			lp->cfg_csr14[port] = (cp[6] << 8) | cp[5];
			lp->cfg_csr15[port] = (cp[8] << 8) | cp[7];
E 16
I 16
	case 2: /* SIA media, aka 10M endec for 21142/43 */
	case 4: /* SYM media 21143 */
		SROM_READ_BYTE(media_code, cp);
D 29
		ext = (media_code & 0x40) != 0;
E 29
I 29
		ext = BOOLEAN(media_code & 0x40);
E 29
		media_code &= 0x3f;
		if ((port = mc_to_port[media_code]) < 0) {
			goto x;
		}
E 16
E 10

D 16
			lp->gp_ctrl[port] = (cp[10] << 8) | cp[9];
			lp->gp_data[port] = (cp[12] << 8) | cp[11];
E 16
I 16
D 28
		if (ext != 0) {
E 28
I 28
		if (ext) {
E 28
			SROM_READ_WORD(lp->cfg_csr13[port], cp);
			SROM_READ_WORD(lp->cfg_csr14[port], cp);
			SROM_READ_WORD(lp->cfg_csr15[port], cp);
E 16

			DPRINTF(0, (CE_CONT,
D 10
		"!csr13[%d]:0x%04x, csr14[%d]:0x%04x, csr15[%d]:0x%04x",
				port, lp->csr13[port],
				port, lp->csr14[port],
				port, lp->csr15[port]));
E 10
I 10
D 16
		"!port:%d csr13:0x%04x, csr14:0x%04x, csr15:0x%04x",
E 16
I 16
D 28
			"!port:%d csr13:0x%04x, csr14:0x%04x, csr15:0x%04x",
E 16
				port, lp->cfg_csr13[port],
				lp->cfg_csr14[port], lp->cfg_csr15[port]));
E 10
		}
I 16
		else {
E 28
I 28
			    "!port:%d csr13:0x%04x, csr14:0x%04x, csr15:0x%04x",
			    port, lp->cfg_csr13[port],
			    lp->cfg_csr14[port], lp->cfg_csr15[port]));
		} else {
E 28
			/* setup default for csr13, csr14, csr15 */
			lp->cfg_csr13[port] = SIACONN_RST;
			lp->cfg_csr14[port] = SIACTRL_10BASET_HALF;
			if (PORT_IS_FDX(port)) {
				lp->cfg_csr14[port] &= ~SIACTRL_LBK;
			}
			/* CSR15: SIA control register configuration */
			lp->cfg_csr15[port] = SIAGP_ABM; /* only for 21143 */
		}
E 16

D 16
		DPRINTF(0, (CE_CONT,
D 10
	"!ext: %d  media code:0x%x, gp_ctrl[%d] 0x%04x, gp_data[%d] 0x%04x",
			ext, media_code, port, lp->gp_ctrl[port],
			port, lp->gp_data[port]));
E 10
I 10
	"!ext:%d media_code:0x%x port:%d gp_ctrl:0x%04x gp_data:0x%04x",
			ext, media_code, port,
			lp->gp_ctrl[port], lp->gp_data[port]));
E 10
		break;
E 16
I 16
		SROM_READ_WORD(lp->gp_ctrl[port], cp);
		SROM_READ_WORD(lp->gp_data[port], cp);
E 16

I 10
D 16
	case 3:
		/* for 21142 with MII media */
		phy = cp[2];
		lp->gp_seq_len = cp[3];
		lp->gp_seq = &cp[4];
E 16
I 16
		switch (port) {
		case PORT_10_HD:
			lp->cfg_csr6[port] = 0;
			lp->bmsr |= MII_STATUS_10;
			break;
D 28
		
E 28
I 28

E 28
		case PORT_10_FD:
			lp->cfg_csr6[port] = NAR_SQE | NAR_FD;
			lp->bmsr |= MII_STATUS_10_FD;
I 17
			break;
E 17
E 16

D 16
		lp->reset_seq_len = cp[4 + 2*lp->gp_seq_len];
		lp->reset_seq = &cp[5 + 2*lp->gp_seq_len];
E 16
I 16
		case PORT_100_HD:
			lp->cfg_csr6[port] = NAR_SQE;
			lp->bmsr |= MII_STATUS_100_BASEX;
			break;
E 16

D 16
		i = 5 + 2*lp->gp_seq_len + 2*lp->reset_seq_len;
D 11
		media_cap = (cp[i+1] << 8) | cp[i+0];
E 11
I 11
		media_cap = (cp[i+1] << 8) | cp[i+0];	/* not used */
E 11
#ifdef notyet
		lp->bmsr = (lp->bmsr & ~MII_STATUS_ABILITY)
			 | (media_cap & MII_STATUS_ABILITY);
#endif
		adv = (cp[i+3] << 8) | cp[i+2];
		fdx = (cp[i+5] << 8) | cp[i+4];
		ttm = (cp[i+7] << 8) | cp[i+6];
E 16
I 16
		case PORT_100_FD:
			lp->cfg_csr6[port] = NAR_SQE | NAR_FD;
			lp->bmsr |= MII_STATUS_100_BASEX_FD;
I 17
			break;
E 17
D 28
		} 
E 28
I 28
		}
E 28
E 16

D 16
		for (i=0; i<4; i++) {
			lp->cfg_csr6[i] &= ~NAR_FD;
			if (fdx & (1 << (i+11))) {
				lp->cfg_csr6[i] |= NAR_FD;
			}

			lp->cfg_csr6[i] &= ~NAR_TTM;
			if (ttm & (1 << (i+11))) {
				lp->cfg_csr6[i] |= NAR_TTM;
			}
E 16
I 16
		if (info_blk_fmt == 4) {
D 17
			/* marge SCR, PCS, TTM, PS bits from cmd field in srom */
E 17
I 17
			/* marge SCR,PCS,TTM,PS bits from cmd field in srom */
E 17
			SROM_READ_WORD(cmd, cp);
			lp->cfg_csr6[port] |= (cmd << 18) & CMD_BITS;
E 16
		}

D 16
		DPRINTF(0, (CE_CONT, "!phy index: %d", phy));
E 16
		DPRINTF(0, (CE_CONT,
D 16
			"!gp_seq_len:%d data:%04x %04x %04x %04x",
			lp->gp_seq_len, (cp[5]<<8)|cp[4], (cp[7]<<8)|cp[6],
			(cp[9]<<8)|cp[8], (cp[11]<<8)|cp[10]));
E 16
I 16
D 17
		"!ext:%d media_code:0x%x port:%d gp_ctrl:0x%04x gp_data:0x%04x",
E 17
I 17
D 28
			"!ext:%d media_code:0x%x port:%d "
			"gp_ctrl:0x%04x gp_data:0x%04x, csr6:%b",
E 17
			ext, media_code, port,
D 17
			lp->gp_ctrl[port], lp->gp_data[port]));
E 17
I 17
			lp->gp_ctrl[port], lp->gp_data[port],
			lp->cfg_csr6[port], CSR6BITS));
E 28
I 28
		    "!ext:%d media_code:0x%x port:%d "
		    "gp_ctrl:0x%04x gp_data:0x%04x, csr6:%b",
		    ext, media_code, port,
		    lp->gp_ctrl[port], lp->gp_data[port],
		    lp->cfg_csr6[port], CSR6BITS));
E 28
E 17
		break;
E 16

I 16
	case 5:
		/* reset sequence by words for 21140/42/43/45 */
		SROM_READ_BYTE(lp->reset_seq_len, cp);
		lp->reset_seq_unit = 2;
		SROM_READ_RECORD(lp->reset_seq, cp,
D 28
				 lp->reset_seq_len * lp->reset_seq_unit);
E 28
I 28
		    lp->reset_seq_len * lp->reset_seq_unit);
E 28

E 16
		DPRINTF(0, (CE_CONT,
D 28
			"!reset_seq_len:%d data:%04x %04x %04x %04x",
			lp->reset_seq_len,
D 16
			(cp[6+2*lp->gp_seq_len]<<8) | cp[5+2*lp->gp_seq_len],
			(cp[8+2*lp->gp_seq_len]<<8) | cp[7+2*lp->gp_seq_len],
			(cp[10+2*lp->gp_seq_len]<<8)| cp[9+2*lp->gp_seq_len],
			(cp[12+2*lp->gp_seq_len]<<8)| cp[11+2*lp->gp_seq_len]));
E 16
I 16
			LEWORD(&lp->reset_seq[0]), LEWORD(&lp->reset_seq[2]),
			LEWORD(&lp->reset_seq[4]), LEWORD(&lp->reset_seq[6])));
E 28
I 28
		    "!reset_seq_len:%d data:%04x %04x %04x %04x",
		    lp->reset_seq_len,
		    LEWORD(&lp->reset_seq[0]), LEWORD(&lp->reset_seq[2]),
		    LEWORD(&lp->reset_seq[4]), LEWORD(&lp->reset_seq[6])));
E 28
E 16

D 16
		mii_ind = cp[13 + 2*lp->gp_seq_len + 2*lp->reset_seq_len];

		DPRINTF(0, (CE_CONT,
			"!adv:0x%04x, fdx:0x%04x, ttm:0x%04x mii_ind:0x%02x",
			adv, fdx, ttm, mii_ind));
E 16
		break;

E 10
D 16
	case 4:
		/* 21143 only */
		lp->gp_ctrl[port] = (cp[4] << 8) | cp[3];
		lp->gp_data[port] = (cp[6] << 8) | cp[5];
		cmd = (cp[8] << 8) | cp[7];
I 10
		lp->cfg_csr6[port] = (lp->cfg_csr6[port] & ~CMD_BITS)
				   | ((cmd << 18) & CMD_BITS);
E 16
I 16
	default:
E 16
		DPRINTF(0, (CE_CONT,
D 16
			"!ext: %d  media_code:0x%x port:%d gp_ctrl:0x%04x "
			"gp_data:0x%04x cmd:0x%04x",
			ext, media_code, port,
			lp->gp_ctrl[port], lp->gp_data[port], cmd));
E 16
I 16
D 28
		"!info_blk_fmt: 0x%x -- not implemented", info_blk_fmt));
E 28
I 28
		    "!info_blk_fmt: 0x%x -- not implemented", info_blk_fmt));
E 28
E 16
		break;
E 10
D 16

D 10
		DPRINTF(0, (CE_CONT, "!ext: %d  Media Code:0x%x",
				ext, media_code));
		DPRINTF(0, (CE_CONT, "!gp_ctrl[%d] 0x%04x",
				port, lp->gp_ctrl[port]));
		DPRINTF(0, (CE_CONT, "!gp_data[%d] 0x%04x",
				port, lp->gp_data[port]));
		DPRINTF(0, (CE_CONT, "!cmd 0x%04x", cmd));
E 10
I 10
	case 5:
		/* reset sequence */
		lp->reset_seq_len = cp[2];
		lp->reset_seq = &cp[3];
E 10
		break;

D 10
	case 3:
		/* 21142 for MII media */
E 10
E 9
	default:
D 9
		DPRINTF(0, (CE_WARN, 
			"%s: tu_mii_write_nway_pnic: writing mii reg %d",
			dp->name, index));
E 9
I 9
		DPRINTF(0, (CE_CONT, "!type: 0x%x -- not implemented", type));
E 9
		break;
E 16
	}
D 9
	return;
E 9
I 9
x:
D 11
	DPRINTF(0, (CE_CONT,"!\n"));
E 11
I 11
D 16
	DPRINTF(0, (CE_CONT,"!"));
E 16
I 16
	DPRINTF(0, (CE_CONT, "!"));
E 16
E 11
D 17
	return length + 1;
E 17
I 17
	return (length + 1);
E 17
E 9
}

E 8
I 2
static int
D 9
tu_mii_init(struct gem_dev *dp)
E 9
I 9
tu_srom_parser(struct gem_dev *dp)
E 9
{
D 9
	int		phy;
	uint16_t	adv;
	uint16_t	status;
	uint32_t	phyid;
	uint16_t	val;
	uint32_t	data;
I 3
	boolean_t	first;
E 9
I 9
	uint8_t		*cp;
D 16
	uint16_t	svid;
	uint16_t	sdid;
	uint16_t	offset;
	int		i, numdev;
E 16
I 16
	int		cont_cnt;
	int		i, blocknum;
E 16
E 9
E 3
D 7
	struct tu_chip_state	*lp = (struct tu_chip_state *)dp->private;
E 7
I 7
D 28
	struct tu_dev	*lp = (struct tu_dev *)dp->private;
E 28
I 28
	struct tu_dev	*lp = dp->private;
E 28
E 7

I 11
	switch (lp->hw_info->chip_type) {
	case CHIP_21140:
	case CHIP_21142:
		break;
D 14

E 14
I 14
#ifdef NEVER
	case CHIP_DM9102:
I 29
	case CHIP_DM9102A:
E 29
D 28
		if (lp->srom_data[18] != 0x14 /*SROM V41*/) {
E 28
I 28
		if (lp->srom_data[18] != 0x14 /* SROM V41 */) {
E 28
D 20
			return 0;
E 20
I 20
			return (0);
E 20
		}
		break;
#endif
E 14
	default:
D 20
		return 0;
E 20
I 20
		return (0);
E 20
	}

E 11
D 3
	DPRINTF(3, (CE_CONT, "!%s: tu_mii_init: called", dp->name));
E 3
I 3
D 9
	DPRINTF(2, (CE_CONT, "!%s: tu_mii_init: called", dp->name));
E 9
I 9
	cp = lp->srom_data;
E 9
E 3

I 8
D 9
	lp->adv = MII_ABILITY_10BASE_T
		| MII_ABILITY_10BASE_T_FD
		| MII_ABILITY_100BASE_TX
		| MII_ABILITY_100BASE_TX_FD
		| MII_ABILITY_PAUSE;
E 9
I 9
	/* parse ID block */
D 16
	svid = cp[1] << 8 | cp[0];
	sdid = cp[3] << 8 | cp[2];
E 16
I 16
	cont_cnt = cp[19];
E 16

D 16
	DPRINTF(0, (CE_CONT,
		"!%s: parsing srom...\n"
		"svid: %04x sdid: %04x\n"
		"hwoptions func1: %02x misc: %02x: func0 %02x",
		dp->name, svid, sdid, cp[14], cp[15], cp[17]));
E 16
I 16
	DPRINTF(0, (CE_CONT, "!%s: parsing srom...", dp->name));
	DPRINTF(0, (CE_CONT, "!svid: 0x%04x sdid: 0x%04x",
D 28
				LEWORD(cp+0), LEWORD(cp+2)));
E 28
I 28
	    LEWORD(cp+0), LEWORD(cp+2)));
E 28
	DPRINTF(0, (CE_CONT, "!hwoptions func1: 0x%x misc: 0x%02x: func0 0x%x",
D 28
				cp[14], cp[15], cp[17]));
E 28
I 28
	    cp[14], cp[15], cp[17]));
E 28
E 16

D 16
	DPRINTF(0, (CE_CONT, "!srom format version: %02x", cp[18]));
D 11
	DPRINTF(0, (CE_CONT, "!num controler: %02x", cp[19]));
E 11
I 11
	DPRINTF(0, (CE_CONT, "!num controller: %02x", cp[19]));
E 16
I 16
	DPRINTF(0, (CE_CONT, "!srom format version: 0x%02x", cp[18]));
	DPRINTF(0, (CE_CONT, "!controller count: %d", cont_cnt));
E 16
E 11

	DPRINTF(0, (CE_CONT, "!mac address: %02x:%02x:%02x:%02x:%02x:%02x",
D 28
		cp[20], cp[21], cp[22], cp[23], cp[24], cp[25]));
E 28
I 28
	    cp[20], cp[21], cp[22], cp[23], cp[24], cp[25]));
E 28

D 16
	DPRINTF(0, (CE_CONT, "!device number: %02x", cp[26]));

E 16
D 11
	switch (lp->hw_info->chip_type) {
	case CHIP_21140:
	case CHIP_21142:
I 10
	case CHIP_MX98713:
#ifdef notdef
	case CHIP_MX98715:	/* buffalo card doesn't have */
#endif
E 10
		break;
	default:
		return 0;
	}

E 11
E 9
E 8
	/*
I 9
	 * parse info leaf
	 */
D 16
	offset = (cp[28] << 8) | cp[27];
	cp = lp->srom_data + offset;
	DPRINTF(0, (CE_CONT, "!selected connection type:0x%04x",
		(cp[1] << 8) | cp[0]));
E 16
I 16
	cp = lp->srom_data + LEWORD(cp + 27 + lp->dev_index*3);
	DPRINTF(0, (CE_CONT, "!selected connection type:0x%04x", LEWORD(cp)));
E 16

	switch (lp->hw_info->chip_type) {
	case CHIP_21140:
I 28
	case CHIP_ULI526X:
E 28
D 10
		for (i = 0; i < 5; i++) {
			lp->gp_ctrl[i] = cp[2] | 0x100;
E 10
I 10
		for (i = 0; i < NUM_PORT_SELECTION; i++) {
			lp->gp_ctrl[i] = cp[2] | GPR_GPC;
E 10
		}
D 16
		numdev = cp[3];
E 16
I 16
		blocknum = cp[3];
E 16
		cp += 4;
		DPRINTF(0, (CE_CONT, "!gp ctrl:0x%02x", lp->gp_ctrl[0]));
		break;

	case CHIP_21142:
I 10
D 11
	case CHIP_MX98713:
	case CHIP_MX98715:
E 11
E 10
D 16
		numdev = cp[2];
E 16
I 16
		blocknum = cp[2];
E 16
		cp += 3;
		break;
	}
D 16
	DPRINTF(0, (CE_CONT, "!block count: 0x%02x", numdev));
E 16
I 16
	DPRINTF(0, (CE_CONT, "!block count: %d", blocknum));
E 16

D 16
	if (numdev >= 16) {
E 16
I 16
	if (blocknum >= 16) {
E 16
		cmn_err(CE_NOTE, "%s: srom corrupted: too many devices",
D 28
				dp->name);
E 28
I 28
		    dp->name);
E 28
D 20
		return 0;
E 20
I 20
		return (0);
E 20
	}

	/*
D 11
	 * each media blocks
E 11
I 11
D 16
	 * parse each media blocks
E 16
I 16
	 * parse each media block
E 16
E 11
	 */
D 16
	for (i = 0; i < numdev; i++) {
E 16
I 16
D 26
	lp->bmsr &= ~MII_STATUS_ABILITY;
E 26
I 26
	lp->bmsr &= ~MII_STATUS_ABILITY_TECH;
E 26
	for (i = 0; i < blocknum; i++) {
E 16
		cp += tu_srom_media_block(dp, cp);
D 16
		if (cp < lp->srom_data || cp >= &lp->srom_data[256]) {
D 11
			cmn_err(CE_NOTE, "%s: srom corrupted: parse error",
E 11
I 11
			cmn_err(CE_NOTE, "%s: srom corrupted: parsing error",
E 16
I 16
		if (cp < lp->srom_data ||
		    cp >= &lp->srom_data[1 << (lp->ee_abits + 1)]) {
			cmn_err(CE_WARN, "%s: srom corrupted: parsing error",
E 16
E 11
D 28
				dp->name);
E 28
I 28
			    dp->name);
E 28
			break;
		}
	}
D 17
	return 0;
E 17
I 17
	return (0);
E 17
}

I 16
static void
D 17
tu_reset_phy(struct gem_dev *dp)
E 17
I 17
tu_enable_phy(struct gem_dev *dp)
E 17
{
	int		i;
	uint32_t	val;
D 28
	struct tu_dev	*lp = (struct tu_dev *)dp->private;
E 28
I 28
	struct tu_dev	*lp = dp->private;
E 28

D 17
	if (lp->reset_seq_len > 0) {
		/*
		 * Need to issue a PHY reset sequence to GPIO register
		 */
		switch (lp->hw_info->chip_type) {
		case CHIP_21140:
E 17
I 17
	/*
	 * Need to issue a PHY reset sequence to GPIO register
	 */
	switch (lp->hw_info->chip_type) {
	case CHIP_21140:
		if (lp->reset_seq_len > 0) {
E 17
			OUTL(dp, GPIO, lp->gp_ctrl[0]);
			if (lp->reset_seq_unit == 1) {
				for (i = 0; i < lp->reset_seq_len; i++) {
					OUTL(dp, GPIO, lp->reset_seq[i]);
				}
			} else {
				ASSERT(lp->reset_seq_unit == 2);
				/* block type 5 */
				for (i = 0; i < lp->reset_seq_len; i++) {
					OUTL(dp, GPIO,
D 28
						LEWORD(&lp->reset_seq[2*i]));
E 28
I 28
					    LEWORD(&lp->reset_seq[2*i]));
E 28
				}
			}
D 17
			break;
E 17
I 17
			dp->mii_state = MII_STATE_UNKNOWN;
		}
		break;
E 17

D 17
		case CHIP_21142:
E 17
I 17
	case CHIP_21142:
	case CHIP_XIRCOM:
		if (lp->reset_seq_len > 0) {
E 17
			OUTL(dp, SIAGP,
D 28
				(lp->gp_ctrl[0] << 16) | lp->cfg_csr15[0]);
E 28
I 28
			    (lp->gp_ctrl[0] << 16) | lp->cfg_csr15[0]);
I 29
			FLSHL(dp, SIAGP);
			drv_usecwait(100);
E 29
E 28
			for (i = 0; i < lp->reset_seq_len; i++) {
				val = LEWORD(&lp->reset_seq[2*i]);
				OUTL(dp, SIAGP,
D 28
					(val << 16) | lp->cfg_csr15[0]);
E 28
I 28
				    (val << 16) | lp->cfg_csr15[0]);
I 29
				FLSHL(dp, SIAGP);
				drv_usecwait(100);
E 29
E 28
			}
D 17
			break;
E 17
I 17
			dp->mii_state = MII_STATE_UNKNOWN;
E 17
		}
I 17
		break;
E 17
	}
}

E 16
static int
D 16
tu_mii_attach(struct gem_dev *dp)
E 16
I 16
D 26
tu_mii_init(struct gem_dev *dp)
E 26
I 26
tu_mii_probe(struct gem_dev *dp)
E 26
E 16
{
	int		i;
I 10
	uint32_t	val;
E 10
D 26
	boolean_t	first = TRUE;
E 26
I 26
	boolean_t	first = B_TRUE;
E 26
D 28
	struct tu_dev	*lp = (struct tu_dev *)dp->private;
E 28
I 28
	struct tu_dev	*lp = dp->private;
E 28

D 16
	DPRINTF(2, (CE_CONT, "!%s: tu_mii_attach: called", dp->name));
E 16
I 16
D 26
	DPRINTF(2, (CE_CONT, "!%s: tu_mii_init: called", dp->name));
E 26
I 26
D 29
	DPRINTF(2, (CE_CONT, "!%s: %s: called", dp->name, __func__));
E 29
I 29
	DPRINTF(0, (CE_CONT, "!%s: %s: called", dp->name, __func__));
E 29
E 26
E 16
I 11
	ASSERT((lp->nar & (NAR_ST | NAR_SR)) == 0);
E 11

I 16
D 28
	bzero(lp->gp_ctrl, sizeof(lp->gp_ctrl));
	bzero(lp->gp_data, sizeof(lp->gp_data));
	bzero(lp->cfg_csr13, sizeof(lp->cfg_csr13));
	bzero(lp->cfg_csr14, sizeof(lp->cfg_csr14));
	bzero(lp->cfg_csr15, sizeof(lp->cfg_csr15));
E 28
I 28
	bzero(lp->gp_ctrl, sizeof (lp->gp_ctrl));
	bzero(lp->gp_data, sizeof (lp->gp_data));
	bzero(lp->cfg_csr13, sizeof (lp->cfg_csr13));
	bzero(lp->cfg_csr14, sizeof (lp->cfg_csr14));
	bzero(lp->cfg_csr15, sizeof (lp->cfg_csr15));
E 28

	lp->bmsr = MII_STATUS_100_BASEX_FD
D 28
		 | MII_STATUS_100_BASEX
		 | MII_STATUS_10_FD
		 | MII_STATUS_10;
E 28
I 28
	    | MII_STATUS_100_BASEX
	    | MII_STATUS_10_FD
	    | MII_STATUS_10;
E 28

	if (lp->have_srom) {
D 17
		tu_srom_parser(dp);
E 17
I 17
		lp->have_srom = tu_srom_parser(dp);
E 17
	}

E 16
	/*
E 9
	 * Try MII interface first
	 */
D 6
	if (lp->hw_info->capability & CHIP_CAP_MII) {
E 6
I 6
D 28
	if ((lp->hw_info->capability & CHIP_CAP_MII) != 0) {
E 28
I 28
	if (lp->hw_info->capability & CHIP_CAP_MII) {
E 28
E 6
		/*
D 9
		 * Ensure that port is  MII mode
E 9
I 9
		 * selet MII mode
E 9
		 */
I 8
D 9
		if (lp->hw_info->chip_type == CHIP_LC82C168
				&& lp->pci_revid < 0x20 /* PNIC_82C169_REV */) {
			goto sym;
		}
E 8
I 3
		first = TRUE;
E 9
E 3
		lp->port = PORT_MII;
D 6
		lp->nar |=  NAR_PS;	/* bit18: select 100M port */
E 6
I 6
D 9
		lp->nar |=  NAR_PS;	/* bit18: select MII/SYM port */
E 6
		lp->nar &= ~NAR_SCR;	/* bit24: disable Scrambler mode */
		lp->nar &= ~NAR_PCS;	/* bit23: disable PCS function */
E 9
I 9
D 11
#ifdef notdef
		/* No need to setup csr6 for MII operations */
		tu_set_media(dp);
#endif
		ASSERT((lp->nar & (NAR_ST | NAR_SR)) == 0);
E 11
E 9
I 3

D 9
		if (lp->hw_info->chip_type == CHIP_DM9102) {
			/* select internal PHY */
			lp->nar &= ~NAR_PS;
		}

E 3
		OUTL(dp, NAR, lp->nar);
		drv_usecwait(5);

I 7
		if (lp->hw_info->chip_type == CHIP_DM9102) {
E 9
I 9
		switch (lp->hw_info->chip_type) {
		case CHIP_DM9102:
I 29
		case CHIP_DM9102A:
E 29
E 9
			/* reset PHY */
			OUTL(dp, SIASTAT, 0x180);
			drv_usecwait(10);
			OUTL(dp, SIASTAT, 0);
			lp->bmcr = 0;
I 9
			break;
D 11

E 11
I 11
D 29
#ifdef notdef
E 29
I 29
#ifdef NEVER
E 29
E 11
		case CHIP_CONEXANT:
			/*
			 * FreeBSD if_dc.c says phy@0 is
			 * for HomePNA. We skip it.
			 */
			dp->mii_phy_addr = 1;
			break;
D 11

E 11
I 11
#endif
E 11
		case CHIP_CENTAUR:
D 11
			dp->mii_phy_addr = 1;
E 11
			if (lp->hw_info->devid == DEVID_COMET) {
D 11
				/* comet has built-in PHY */
E 11
I 11
				/* comet has a non-MII built-in  PHY */
E 11
				dp->mii_phy_addr = -1;
D 28
			}
I 11
			else {
E 28
I 28
			} else {
E 28
				/* centaur has a MII style built-in PHY */
				dp->mii_phy_addr = 1;
			}
E 11
			break;
I 17

		case CHIP_XIRCOM:
			for (i = 0; i < NUM_PORT_SELECTION; i++) {
				lp->gp_ctrl[i] = 0x0805;
				lp->gp_data[i] = 0x000f;
			}
			lp->reset_seq_unit = 2;
			lp->reset_seq_len = 2;
			lp->reset_seq = lp->srom_data;
			lp->srom_data[0] = 0x00;
			lp->srom_data[1] = 0x00;	/* gpio data write */
			lp->srom_data[2] = 0x0f;
			lp->srom_data[3] = 0x00;	/* gpio data write */
			break;
E 17
E 9
		}

E 7
D 9
		/* Scan PHY */
again:
		GEM_MII_SYNC(dp);
E 9
I 9
D 16
		/*
D 11
		 * Configure default csr6
E 11
I 11
		 * Configure csr6
E 11
		 */
D 10
		bzero(lp->csr6, sizeof(lp->csr6));
		lp->csr6[PORT_10_HD]  = NAR_PS | NAR_TTM | NAR_SQE;
		lp->csr6[PORT_10_FD]  = lp->csr6[PORT_10_HD] | NAR_FD;
		lp->csr6[PORT_100_HD] = NAR_PS | NAR_SQE;
		lp->csr6[PORT_100_FD] = lp->csr6[PORT_100_HD] | NAR_FD;
E 10
I 10
		lp->cfg_csr6[PORT_10_HD]  = NAR_PS | NAR_TTM | NAR_SQE;
		lp->cfg_csr6[PORT_10_FD]  = lp->cfg_csr6[PORT_10_HD] | NAR_FD;
		lp->cfg_csr6[PORT_100_HD] = NAR_PS | NAR_SQE;
		lp->cfg_csr6[PORT_100_FD] = lp->cfg_csr6[PORT_100_HD] | NAR_FD;
E 10
		if (lp->hw_info->chip_type == CHIP_DM9102) {
			for (i = 0; i < NUM_PORT_SELECTION; i++) {
D 10
				lp->csr6[i] &= ~NAR_PS;
E 10
I 10
				lp->cfg_csr6[i] &= ~NAR_PS;
E 10
			}
		}
E 16
I 16
		if (!lp->have_srom) {
			/*
			 * Configure default csr6
			 */
D 28
			lp->cfg_csr6[PORT_10_HD]  = NAR_PS | NAR_TTM | NAR_SQE;
			lp->cfg_csr6[PORT_10_FD]  =
					lp->cfg_csr6[PORT_10_HD] | NAR_FD;
E 28
I 28
			lp->cfg_csr6[PORT_10_HD] = NAR_PS | NAR_TTM | NAR_SQE;
			lp->cfg_csr6[PORT_10_FD] =
			    lp->cfg_csr6[PORT_10_HD] | NAR_FD;
E 28
			lp->cfg_csr6[PORT_100_HD] = NAR_PS | NAR_SQE;
			lp->cfg_csr6[PORT_100_FD] =
D 28
					lp->cfg_csr6[PORT_100_HD] | NAR_FD;
E 28
I 28
			    lp->cfg_csr6[PORT_100_HD] | NAR_FD;
E 28
E 16
E 9

D 9
		for (phy = 0; phy < 32; phy++) {
			dp->mii_phy_addr = phy;
			status = GEM_MII_READ(dp, MII_STATUS);
E 9
I 9
D 16
		bzero(lp->gp_ctrl, sizeof(lp->gp_ctrl));
		bzero(lp->gp_data, sizeof(lp->gp_data));
E 16
I 16
			switch (lp->hw_info->chip_type) {
I 28
D 29
#ifdef notdef
E 29
I 29
#ifdef NEVER
E 29
E 28
			case CHIP_DM9102:
I 29
			case CHIP_DM9102A:
E 29
				for (i = 0; i < NUM_PORT_SELECTION; i++) {
					lp->cfg_csr6[i] &= ~NAR_PS;
				}
				break;
E 16
E 9
D 28

E 28
I 28
#endif
E 28
D 7
			if (status != 0xffff && status != 0x0000) {
I 3
				DPRINTF(0, (CE_CONT,
					"!%s: tu_mii_init: PHY found at %d",
					dp->name, phy));
E 3
				if (lp->hw_info->chip_type == CHIP_DM9102 &&
D 3
				    phy == 0) {
E 3
I 3
				    first) {
E 7
I 7
D 9
			if (status == 0xffff || status == 0x0000) {
				/* a PHY does not exit at the address */
				continue;
E 9
I 9
D 10
		bzero(lp->csr13, sizeof(lp->csr13));
		bzero(lp->csr14, sizeof(lp->csr14));
E 10
I 10
D 16
		bzero(lp->cfg_csr13, sizeof(lp->cfg_csr13));
		bzero(lp->cfg_csr14, sizeof(lp->cfg_csr14));
E 10

D 10
		bzero(lp->csr15, sizeof(lp->csr15));
E 10
I 10
		bzero(lp->cfg_csr15, sizeof(lp->cfg_csr15));
E 10
		switch (lp->hw_info->chip_type) {
		case CHIP_LC82C168:
			for (i = 0; i < NUM_PORT_SELECTION; i++) {
D 10
				lp->csr15[i] = SIAGP_JBD;
E 10
I 10
				lp->cfg_csr15[i] = SIAGP_JBD;
E 16
I 16
			case CHIP_LC82C168:
				/* for only 169 */
				for (i = 0; i < NUM_PORT_SELECTION; i++) {
					lp->cfg_csr15[i] = SIAGP_JBD;
				}
				break;
E 16
E 10
E 9
			}
I 9
D 16
			break;
E 16
		}
E 9
D 26

E 26
I 26
D 28
#ifdef never	/* moved to tu_reset_chip */
E 26
D 9
			DPRINTF(0, (CE_CONT,
				"!%s: tu_mii_init: PHY found at %d",
				dp->name, phy));
E 9
I 9
D 17
		if (lp->have_srom) {
D 16
			tu_srom_parser(dp);
E 16
I 16
			/*
			 * we may have phy reset sequence
			 */
			tu_reset_phy(dp);
E 16
		}
E 17
I 17
		/* we may have phy reset sequence */
		tu_enable_phy(dp);
E 17
E 9
D 26

E 26
I 26
#endif
E 28
I 28
D 29

E 29
I 29
#ifdef NEVER	/* moved to tu_reset_chip */
		tu_enable_phy(dp);
#endif
E 29
E 28
E 26
I 10
D 11
		/* work around for LC82C168 */
		/* set csr6 one of valid configuration */
E 11
I 11
		/* initialize csr6 */
E 11
		lp->nar = (lp->nar & ~CSR6_PORT_BITS)
D 11
			| lp->cfg_csr6[PORT_IX(dp->speed100, dp->full_duplex)];
		UPDATE_NAR(dp, lp->nar & ~(NAR_ST | NAR_SR));
E 11
I 11
D 28
			| lp->cfg_csr6[PORT_IX(dp->speed != GEM_SPD_10,
							dp->full_duplex)];
E 28
I 28
		    | lp->cfg_csr6[PORT_IX(dp->speed != GEM_SPD_10,
		    dp->full_duplex)];
E 28
		UPDATE_NAR(dp, lp->nar);
E 11

E 10
I 9
D 16
		if (lp->reset_seq_len > 0) {
I 10
			/*
D 14
			 * Need to issue PHY reset sequence to GPIO register
E 14
I 14
			 * Need to issue a PHY reset sequence to GPIO register
E 14
			 */
E 10
E 9
			switch (lp->hw_info->chip_type) {
D 9
			case CHIP_DM9102:
				if (first && phy != 1) {
E 7
E 3
					/*
					 * Work around for DM9102.
					 * Reset and scan PHY again because
D 3
					 * Windows changed PHY address to
E 3
I 3
D 7
					 * Windows changes PHY address to
E 7
I 7
					 * MS Windows changes PHY address to
E 7
E 3
					 * power down it.
					 */
					GEM_MII_WRITE(dp, MII_CONTROL,
						MII_CONTROL_RESET);
					drv_usecwait(100*1000);
I 3
					first = FALSE;
E 3
					goto again;
E 9
I 9
			case CHIP_21140:
				OUTL(dp, GPIO, lp->gp_ctrl[0]);
				for (i=0; i<lp->reset_seq_len; i++) {
					OUTL(dp, GPIO, lp->reset_seq[i]);
E 9
				}
I 10
				break;

			case CHIP_21142:
D 11
			case CHIP_MX98713:
E 11
				OUTL(dp, SIAGP,
					(lp->gp_ctrl[0]<<16)|lp->cfg_csr15[0]);
				for (i = 0; i < lp->reset_seq_len; i++) {
					val = (lp->reset_seq[2*i+1] << 8)
					    |  lp->reset_seq[2*i];
					OUTL(dp, SIAGP,
						(val << 16) | lp->cfg_csr15[0]);
				}
				break;
E 10
I 7
D 9
				break;
E 7
I 3

D 7
				if (lp->hw_info->chip_type == CHIP_CONEXANT &&
				    phy == 0){
E 7
I 7
			case CHIP_CONEXANT:
				if (phy == 0) {
E 7
					/*
					 * FreeBSD if_dc.c says phy@0 is
					 * for HomePNA. We skip it.
					 */
					continue;
				}
E 3
D 7
				goto PHY_found;
E 7
I 7
				break;
E 9
E 7
			}
I 9
		}
E 9
I 7

E 16
D 9
			goto PHY_found;
E 9
I 9
		/* Scan PHY */
again:
D 20
		if (gem_mii_init_default(dp) < 0) {
E 20
I 20
D 26
		if (gem_mii_init_default(dp) != GEM_SUCCESS) {
E 26
I 26
		if (gem_mii_probe_default(dp) != GEM_SUCCESS) {
E 26
E 20
D 10
			/* failed, MII PHY doesn't exit */
E 10
I 10
D 14
			/* failed, MII PHY doesn't exist. */
E 14
I 14
			/* As it failed, MII PHY doesn't exist. */
E 14
E 10
			goto sym;
E 9
E 7
		}
I 9

D 29
		if (lp->hw_info->chip_type == CHIP_DM9102 &&
E 29
I 29
		if ((lp->hw_info->chip_type == CHIP_DM9102 ||
		    lp->hw_info->chip_type == CHIP_DM9102A) &&
E 29
		    first && dp->mii_phy_addr != 1) {
			/*
D 29
			 * Work around for DM9102.
E 29
I 29
			 * Work around for DM9102 series.
E 29
			 * Reset and scan PHY again because
D 14
			 * MS Windows changes PHY address to
E 14
I 14
			 * I observed MS Windows changed the PHY address to
E 14
			 * power down it.
			 */
D 17
			GEM_MII_WRITE(dp, MII_CONTROL, MII_CONTROL_RESET);
E 17
I 17
			dp->gc.gc_mii_write(dp, MII_CONTROL, MII_CONTROL_RESET);
E 17
D 28
			drv_usecwait(100*1000);
E 28
I 28
			delay(drv_usectohz(100*1000));
E 28
D 26
			first = FALSE;
E 26
I 26
			first = B_FALSE;
E 26
			goto again;
		}
I 10
D 28
#ifdef notdef
		if (lp->hw_info->chip_type == CHIP_DM9102 &&
		    lp->pci_revid == DM9102A_E3) {
			/* work around according to Davicom's driver */
D 26
			dp->gc.gc_mii_an_oneshot = TRUE;
E 26
I 26
			dp->gc.gc_mii_an_oneshot = B_TRUE;
E 26
		}
#endif
E 28
E 10
D 20
		return 0;
E 20
I 20
		return (0);
E 20
E 9
	}
D 8

E 8
I 8
sym:
E 8
D 6
	if (lp->hw_info->capability & CHIP_CAP_SYM) {
E 6
I 6
D 28
	if ((lp->hw_info->capability & CHIP_CAP_SYM) != 0) {
E 28
I 28
	if (lp->hw_info->capability & CHIP_CAP_SYM) {
E 28
E 6
		/*
		 * Switch to MII emulation routines for SYM interface
		 */
		lp->port = PORT_SYM;
D 28

E 28
D 8
		dp->gc.gc_mii_sync   = &tu_mii_sync_nway;
		dp->gc.gc_mii_read   = &tu_mii_read_nway;
		dp->gc.gc_mii_write  = &tu_mii_write_nway;
E 8
I 8
D 9
		dp->gc.gc_mii_sync = &tu_mii_sync_nway;
		if (lp->hw_info->chip_type == CHIP_LC82C168) {
			dp->gc.gc_mii_read  = &tu_mii_read_nway_pnic;
			dp->gc.gc_mii_write = &tu_mii_write_nway_pnic;
E 9
I 9
D 11
		dp->gc.gc_mii_sync = &tu_nway_sync;
D 10
		switch (lp->hw_info->chip_type) {
		case CHIP_LC82C168:
E 10
I 10
		if (lp->hw_info->chip_type == CHIP_LC82C168) {
E 11
I 11
		dp->mii_phy_addr = -1;	/* no MII address */
I 16
D 28
#ifdef NEVER
		/* SYM interface needs to disable AN after completion of AN. */
D 26
		dp->gc.gc_mii_an_oneshot = TRUE;
E 26
I 26
		dp->gc.gc_mii_an_oneshot = B_TRUE;
E 28
E 26
D 17
#endif
E 17

I 17
D 28
		/* need to reset PHY to stop link pulse on link-down */
		dp->gc.gc_mii_linkdown_action = MII_ACTION_RESET;
#endif
E 28
E 17
E 16
		switch (lp->hw_info->chip_type) {
		case CHIP_LC82C168:
D 28
			dp->gc.gc_mii_sync  = &tu_nway_sync;
E 11
E 10
			dp->gc.gc_mii_read  = &tu_nway_read_pnic;
E 28
I 28
			dp->gc.gc_mii_sync = &tu_nway_sync;
			dp->gc.gc_mii_read = &tu_nway_read_pnic;
E 28
			dp->gc.gc_mii_write = &tu_nway_write_pnic;
E 9
			DPRINTF(2, (CE_CONT, "!%s: using SYM-pnic interface",
D 28
				dp->name));
E 28
I 28
			    dp->name));
E 28
D 9
		} else {
			dp->gc.gc_mii_read  = &tu_mii_read_nway;
			dp->gc.gc_mii_write = &tu_mii_write_nway;
E 9
I 9
D 10
			break;
		default:
E 10
I 10
D 11
		}
		else if ((lp->hw_info->capability & CHIP_CAP_NWAY) != 0) {
E 11
I 11
			break;

D 29
		case CHIP_MX987XX:
D 28
			if ((lp->pci_revid & 0xf0) == 0x00) {
E 28
I 28
			if (MX98713(lp)) {
E 28
				/*
D 28
				 * For mx98713, the internal NWAY register
				 * is accessed as an MII PHY at 0.
I 16
				 * We left mii_phy_addr -1  to supress a PHY					 * detected message.
E 28
I 28
				 * The internal NWAY register is accessed
				 * as an MII PHY at 0.
				 * We leave mii_phy_addr as -1  to suppress
				 * PHY detection messages.
E 28
E 16
				 */
D 16
#ifdef notdef
				dp->mii_phy_addr = 0;
				dp->gc.gc_mii_addr_min = 0;
#endif
E 16
				break;
			}
D 28
			/* fall down */
E 28
I 28
			/* FALL THROUGH */
E 29
I 29
		case CHIP_MX98713:
			/*
			 * The internal NWAY register is accessed
			 * as an MII PHY at 0.
			 * We leave mii_phy_addr as -1  to suppress
			 * PHY detection messages.
			 */
			break;
E 29
E 28

I 29
		case CHIP_MX98713A:
		case CHIP_MX98715:
		case CHIP_MX98725:
E 29
		case CHIP_LC82C115:
		case CHIP_21142:
			/* 21143 style NWAY register */
D 28
			dp->gc.gc_mii_sync  = &tu_nway_sync;
E 11
E 10
			dp->gc.gc_mii_read  = &tu_nway_read_21143;
E 28
I 28
			dp->gc.gc_mii_sync = &tu_nway_sync;
			dp->gc.gc_mii_read = &tu_nway_read_21143;
E 28
			dp->gc.gc_mii_write = &tu_nway_write_21143;
D 10
			break;
E 10
E 9
D 11
		}
I 10
		else {
E 11
I 11
			break;

		default: /* 21140 does not have NWAY capability */
D 28
			dp->gc.gc_mii_sync  = &tu_nway_sync;
E 11
			dp->gc.gc_mii_read  = &tu_no_nway_read;
E 28
I 28
			dp->gc.gc_mii_sync = &tu_nway_sync;
			dp->gc.gc_mii_read = &tu_no_nway_read;
E 28
			dp->gc.gc_mii_write = &tu_no_nway_write;
I 11
			break;
E 11
		}
E 10
I 9
D 11
		dp->mii_phy_addr = -1;	/* no MII address */
E 11
E 9
E 8

D 9
		cmn_err(CE_CONT,
D 3
			"!%s: using SYM interface: Nway status:%b, lpar:%b",
E 3
I 3
			"!%s: using SYM interface: NWay status:%b, lpar:%b",
E 3
			dp->name, 
			GEM_MII_READ(dp, MII_STATUS), MII_STATUS_BITS,
			GEM_MII_READ(dp, MII_AN_LPABLE), MII_ABILITY_BITS);
E 9
I 9
D 11
		/* SYM needs to write the result of AN to control register */
E 11
I 11
D 16
		/* SYM interface needs to disable AN after completion of AN. */
E 11
		dp->gc.gc_mii_an_oneshot = TRUE;
E 9

E 16
D 9
		return 0;
	}
E 9
I 9
		/* SYM interface needs faster AN watch interval */
		dp->gc.gc_mii_an_watch_interval = ONESEC/50;	/* 20mS */
E 9

I 17
		DPRINTF(1, (CE_CONT, "%s:%s have_srom: %d",
D 28
				dp->name, __func__, lp->have_srom));
E 28
I 28
		    dp->name, __func__, lp->have_srom));
E 28
E 17
D 9
	cmn_err(CE_WARN, "!%s: failed to find PHY", dp->name);
	return -1;
E 9
I 9
D 11
		/* standard csr6 configutation */
E 11
I 11
D 16
		/* make standard csr6 configutation */
E 11
D 10
		bzero(lp->csr6, sizeof(lp->csr6));
		lp->csr6[PORT_10_HD]  = 0;
		lp->csr6[PORT_10_FD]  = lp->csr6[PORT_10_HD] | NAR_SQE | NAR_FD;
		lp->csr6[PORT_100_HD] = NAR_PS | NAR_PCS | NAR_SCR | NAR_SQE;
		lp->csr6[PORT_100_FD] = lp->csr6[PORT_100_HD] | NAR_FD;
E 10
I 10
		lp->cfg_csr6[PORT_10_HD] = 0;
		lp->cfg_csr6[PORT_10_FD] =
				lp->cfg_csr6[PORT_10_HD] | NAR_SQE | NAR_FD;
		lp->cfg_csr6[PORT_100_HD]= NAR_PS | NAR_PCS | NAR_SCR | NAR_SQE;
		lp->cfg_csr6[PORT_100_FD]= lp->cfg_csr6[PORT_100_HD] | NAR_FD;
E 16
I 16
		if (!lp->have_srom) {
			/*
			 * make standard csr6 configutation for SIA/SYM media
			 */
			lp->cfg_csr6[PORT_10_HD] = 0;
			lp->cfg_csr6[PORT_10_FD] = NAR_SQE | NAR_FD;
			lp->cfg_csr6[PORT_100_HD] =
D 28
					NAR_PS | NAR_PCS | NAR_SCR | NAR_SQE;
E 28
I 28
			    NAR_PS | NAR_PCS | NAR_SCR | NAR_SQE;
E 28
			lp->cfg_csr6[PORT_100_FD] =
D 28
					lp->cfg_csr6[PORT_100_HD] | NAR_FD;
E 28
I 28
			    lp->cfg_csr6[PORT_100_HD] | NAR_FD;
E 28
E 16
E 10
E 9

D 9
PHY_found:
E 9
I 9
D 10
		/* patch for various nic's*/
E 10
I 10
D 11
		/* patch for various nics*/
E 11
I 11
D 16
		/* patch for various nics */
E 11
E 10
		switch (lp->hw_info->chip_type) {
I 10
		case CHIP_21140:
			if (IS_21140(lp)) {
E 16
I 16
			/* patch csr6 for various nics */
			switch (lp->hw_info->chip_type) {
			case CHIP_21140:
				if (IS_21140(lp)) {
					lp->cfg_csr6[PORT_10_HD] |= NAR_TTM;
					lp->cfg_csr6[PORT_10_FD] |= NAR_TTM;
				}
				break;

D 29
			case CHIP_MX987XX:
E 29
I 29
			case CHIP_MX98713:
			case CHIP_MX98713A:
			case CHIP_MX98715:
			case CHIP_MX98725:
E 29
			case CHIP_LC82C168:
			case CHIP_LC82C115:
E 16
				lp->cfg_csr6[PORT_10_HD] |= NAR_TTM;
				lp->cfg_csr6[PORT_10_FD] |= NAR_TTM;
I 16
				break;
E 16
			}
D 16
			break;
E 16
E 10
D 11
		case CHIP_MX98713:
		case CHIP_MX98715:
E 11
I 11

D 16
		case CHIP_MX987XX:
E 11
		case CHIP_LC82C168:
		case CHIP_LC82C115:
D 10
			lp->csr6[PORT_10_HD] |= NAR_TTM;
			lp->csr6[PORT_10_FD] |= NAR_TTM;
E 10
I 10
			lp->cfg_csr6[PORT_10_HD] |= NAR_TTM;
			lp->cfg_csr6[PORT_10_FD] |= NAR_TTM;
			break;
E 10
		}
E 16
I 16
			/* CSR13/14 21143 SIA registers configuration */
			/* XXX - pnic doesn't use csr13 & 14 */
			lp->cfg_csr13[PORT_10_HD] = SIACONN_RST;
			lp->cfg_csr13[PORT_10_FD] = SIACONN_RST;
			lp->cfg_csr14[PORT_10_HD] = SIACTRL_10BASET_HALF;
D 28
			lp->cfg_csr14[PORT_10_FD] = SIACTRL_10BASET_HALF 
							& ~SIACTRL_LBK;
E 28
I 28
			lp->cfg_csr14[PORT_10_FD] =
			    SIACTRL_10BASET_HALF & ~SIACTRL_LBK;
E 28
E 16
E 9

D 9
	phyid  = GEM_MII_READ(dp, MII_PHYIDH) << 16;
	phyid |= GEM_MII_READ(dp, MII_PHYIDL);
	adv = GEM_MII_READ(dp, MII_AN_ADVERT);
	val = GEM_MII_READ(dp, MII_CONTROL);
E 9
I 9
D 11
		/* CSR13/14 21143 SIA regisgiers configuration */
E 11
I 11
D 16
		/* CSR13/14 21143 SIA registers configuration */
E 11
D 10
		bzero(lp->csr13, sizeof(lp->csr13));
		bzero(lp->csr14, sizeof(lp->csr14));
E 10
I 10
		bzero(lp->cfg_csr13, sizeof(lp->cfg_csr13));
		bzero(lp->cfg_csr14, sizeof(lp->cfg_csr14));
E 10
		switch (lp->hw_info->chip_type) {
		case CHIP_21142:
D 11
		case CHIP_MX98713:
		case CHIP_MX98715:
E 11
I 11
		case CHIP_MX987XX:
E 11
		case CHIP_LC82C115:
D 10
			lp->csr13[PORT_10_HD]  = SIACONN_RST;
			lp->csr13[PORT_10_FD]  = SIACONN_RST;
			lp->csr14[PORT_10_HD]  = SIACTRL_10BASET_HALF;
			lp->csr14[PORT_10_FD]  =
E 10
I 10
D 11
			lp->cfg_csr13[PORT_10_HD]  = SIACONN_RST;
			lp->cfg_csr13[PORT_10_FD]  = SIACONN_RST;
			lp->cfg_csr14[PORT_10_HD]  = SIACTRL_10BASET_HALF;
			lp->cfg_csr14[PORT_10_FD]  =
E 10
					SIACTRL_10BASET_HALF & ~SIACTRL_LBK;
			break;
		}
E 9

D 9
	cmn_err(CE_CONT, "!%s: PHY (0x%08x) "
		"found at %d, control:%b, status:%b, advert:%b, lpar:%b",
		dp->name, phyid, dp->mii_phy_addr,
		val, MII_CONTROL_BITS,
		status, MII_STATUS_BITS,
		adv, MII_ABILITY_BITS,
		GEM_MII_READ(dp, MII_AN_LPABLE),
		MII_ABILITY_BITS);
E 9
I 9
		/* CSR15: SIA control register configuration */
D 10
		lp->csr15[PORT_10_HD] = SIAGP_ABM; /* no effect except 21143 */
		lp->csr15[PORT_10_FD] = SIAGP_ABM; /* no effect except 21143 */
		lp->csr15[PORT_100_HD] = 0;
		lp->csr15[PORT_100_FD] = 0;
E 10
I 10
		lp->cfg_csr15[PORT_10_HD] = SIAGP_ABM; /* only for 21143 */
		lp->cfg_csr15[PORT_10_FD] = SIAGP_ABM; /* only for 21143 */
		lp->cfg_csr15[PORT_100_HD] = 0;
		lp->cfg_csr15[PORT_100_FD] = 0;
E 10
E 9

D 9
	return 0;
E 9
I 9
		/* GP ctrl/data registers */
		bzero(lp->gp_ctrl, sizeof(lp->gp_ctrl));
		bzero(lp->gp_data, sizeof(lp->gp_data));
		switch (lp->hw_info->chip_type) {
		case CHIP_LC82C168:
			lp->gp_data[PORT_10_HD] =
			lp->gp_data[PORT_10_FD] =
					PNIC_GPIO_100_LB | PNIC_GPIO_RL_10;
			lp->gp_data[PORT_100_HD] =
			lp->gp_data[PORT_100_FD] =
					PNIC_GPIO_100_EN | PNIC_GPIO_RL_100;
			break;
		}

		if (lp->have_srom) {
			tu_srom_parser(dp);
		}

D 10
		if (gem_mii_init_default(dp) == 0) {
			return 0;
E 10
I 10
		/* work around for LC82C168 */
		/* set csr6 one of valid configuration */
		lp->nar = (lp->nar & ~CSR6_PORT_BITS)
			| lp->cfg_csr6[PORT_IX(dp->speed100, dp->full_duplex)];
		UPDATE_NAR(dp, lp->nar & ~(NAR_ST | NAR_SR));

		if (gem_mii_init_default(dp) != 0) {
			goto x;
E 10
		}
D 10
	}
E 10

I 10
		return 0;
	}
x:
E 10
	cmn_err(CE_WARN, "!%s: failed to find PHY", dp->name);
	return -1;
E 9
}
I 7

E 7
E 2
/* ======================================================== */
/*
D 7
 * OS depend (device driver) routine
E 7
I 7
 * OS depend (Solaris DKI) routine
E 7
 */
/* ======================================================== */
static int
tuattach(dev_info_t *dip, ddi_attach_cmd_t cmd)
{
	int			i;
	ddi_iblock_cookie_t	c;
	ddi_acc_handle_t	conf_handle;
	int			ret;
	uint16_t		vid;
	uint16_t		did;
	uint16_t		svid;
	uint16_t		ssid;
	uint32_t		dd;
	uint32_t		ps;
	uint8_t			cap_ptr;
D 7
	uint8_t			revid;
E 7
I 7
	uint32_t		revid;
	uint32_t		pmr;
	uint32_t		ilr;
E 7
	int			unit;
	struct chip_info	*p;
	int			len;
	struct pci_phys_spec	*regs;
	const char		*drv_name;
	struct gem_dev		*dp;
D 7
	struct tu_chip_state	*lp;
E 7
I 7
	struct tu_dev		*lp;
E 7
	void			*base;
	ddi_acc_handle_t	regs_handle;
	struct gem_conf		gc;
	int			cache_linesz;
	int			comm;

	unit =  ddi_get_instance(dip);
	drv_name = ddi_driver_name(dip);

D 2
	DPRINTF(3, (CE_CONT, "%s%d: tuattach: called", drv_name, unit));
E 2
I 2
	DPRINTF(3, (CE_CONT, "!%s%d: tuattach: called", drv_name, unit));
E 2

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
		svid = pci_config_get16(conf_handle, PCI_CONF_SUBVENID);
		ssid = pci_config_get16(conf_handle, PCI_CONF_SUBSYSID);
I 2
		revid= pci_config_get8(conf_handle, PCI_CONF_REVID);
I 7
		ilr  = pci_config_get32(conf_handle, PCI_CONF_ILINE);

E 7
I 3
D 10
#ifdef notdef
E 3
E 2
		cache_linesz  =
		       pci_config_get8(conf_handle, PCI_CONF_CACHE_LINESZ);
		comm  = pci_config_get16(conf_handle, PCI_CONF_COMM);
D 3

E 3
		dd   = pci_config_get32(conf_handle, CFDD);
		pci_config_put32(conf_handle, CFDD,
					dd & ~(CFDD_SLEEP | CFDD_SNOOZE));

		cap_ptr = pci_config_get8(conf_handle, PCI_CONF_CAP_PTR);
		ps = pci_config_get32(conf_handle, cap_ptr + 4);
		pci_config_put32(conf_handle, cap_ptr + 4,
						ps & ~PCI_PMCSR_STATE_MASK);

		ret = pci_config_get16(conf_handle, PCI_CONF_COMM);
		ret |= PCI_COMM_IO | PCI_COMM_ME;
		pci_config_put16(conf_handle, PCI_CONF_COMM, ret);

		pci_config_teardown(&conf_handle);
D 3

E 3
I 3
#endif
E 10
E 3
		for (i = 0, p = tu_chiptbl; i < CHIPTABLESIZE; i++, p++) {
D 10
			if ((p->venid == vid && p->devid == did) ||
			    (p->venid == svid && p->devid == ssid)) {
E 10
I 10
			if (((p->venid == vid && p->devid == did) ||
			     (p->venid == svid && p->devid == ssid)) &&
			     revid <= p->maxrev) {
E 10
				/* found */
				cmn_err(CE_CONT,
			"!%s%d: %s (vid: 0x%04x, did: 0x%04x, revid: 0x%02x)",
				drv_name, unit, p->name, vid, did, revid);
				goto chip_found;
			}
		}
I 3

E 3
		/* Not found */
		cmn_err(CE_WARN,
			"%s: tu_attach: wrong PCI venid/devid (0x%x, 0x%x)",
			drv_name, vid, did);
I 3
		pci_config_teardown(&conf_handle);
E 3
		goto err;
I 3

E 3
chip_found:
I 3
		/* get capabilities on PCI bus */
		cache_linesz  =
D 9
		       pci_config_get8(conf_handle, PCI_CONF_CACHE_LINESZ);
		comm = pci_config_get16(conf_handle, PCI_CONF_COMM);
E 9
I 9
			pci_config_get8(conf_handle, PCI_CONF_CACHE_LINESZ);
E 9

		/* exit power down mode */
		dd   = pci_config_get32(conf_handle, CFDD);
		pci_config_put32(conf_handle, CFDD,
D 7
					dd & ~(CFDD_SLEEP | CFDD_SNOOZE));
E 7
I 7
				dd & ~(CFDD_SLEEP | CFDD_SNOOZE | 0x38000000));
E 7
		cap_ptr = pci_config_get8(conf_handle, PCI_CONF_CAP_PTR);
I 7
		pmr= pci_config_get32(conf_handle, cap_ptr);
E 7
		ps = pci_config_get32(conf_handle, cap_ptr + 4);
		pci_config_put32(conf_handle, cap_ptr + 4,
						ps & ~PCI_PMCSR_STATE_MASK);

		ret = pci_config_get16(conf_handle, PCI_CONF_COMM);
		ret |= PCI_COMM_IO | PCI_COMM_ME;
		pci_config_put16(conf_handle, PCI_CONF_COMM, ret);

I 9
		comm = pci_config_get16(conf_handle, PCI_CONF_COMM);

E 9
		pci_config_teardown(&conf_handle);


E 3
		/*
		 * Map in the device registers.
		 */

		/* Search IO-range or memory-range to be mapped */
		regs = NULL;
		len  = 0;
		if (ddi_getlongprop(DDI_DEV_T_ANY, dip, DDI_PROP_DONTPASS,
			"reg", (caddr_t)&regs, &len) != DDI_PROP_SUCCESS) {
			cmn_err(CE_WARN,
			"%s%d: failed to get reg property", drv_name, unit);
			goto err;
		}

		ASSERT(regs != NULL && len > 0);
#if DEBUG_LEVEL > 0
		cmn_err(CE_CONT,
D 7
		"!%s%d: dd:%x cap_ptr:%x ps:%x cache_linesz:0x%x cmd:0x%x",
			drv_name, unit, dd, cap_ptr, ps, cache_linesz, comm);
E 7
I 7
"!%s%d: dd:%x cap_ptr:%x pmr:%x ps:%x cache_linesz:0x%x cmd:0x%x ilr:0x%x",
			drv_name, unit,
			dd, cap_ptr, pmr, ps, cache_linesz, comm, ilr);
E 7
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
			    PCI_ADDR_IO) {
				/* it's I/O space */
				kmem_free(regs, len);
				goto io_range_found;
			}
		}
		cmn_err(CE_WARN, "%s%d: failed to find IO space", drv_name, unit);
		kmem_free(regs, len);
		goto err;
io_range_found:

		if (ddi_regs_map_setup(dip, i, (caddr_t *)&base,
D 6
			0, 0, &gem_dev_attr, &regs_handle)) {
E 6
I 6
			0, 0, &tu_dev_attr, &regs_handle)) {
E 6
			cmn_err(CE_WARN, "%s%d: ddi_regs_map_setup failed",
				drv_name, unit);
			goto err;
		}
I 7

		if (p->chip_type == CHIP_DM9102) {
#ifdef DM9102A_E3_TEST
			revid = DM9102A_E3;
#else
			revid |= pmr & (PCI_PMCAP_VER_MASK << 16);
#endif
		}

E 7
		/*
D 2
		 * construct gem configration
E 2
I 2
		 * Construct gem configration
E 2
		 */
I 3
		bzero(&gc, sizeof(gc));
E 3

		/* name */
		sprintf(gc.gc_name, "%s%d", drv_name, unit);

		/* consistency on tx and rx */
		gc.gc_tx_buf_align = p->tx_align - 1;
		gc.gc_tx_max_frags = GEM_MAXTXFRAGS;
		gc.gc_tx_desc_size = sizeof(struct tx_desc) * TX_RING_SIZE;
		gc.gc_tx_ring_size = TX_RING_SIZE;
		gc.gc_tx_buf_size  = TX_BUF_SIZE;
D 2
		if (p->capability & CHIP_CAP_RING) {
E 2
I 2
D 10
		if ((p->capability & CHIP_CAP_RING) != 0) {
E 2
			gc.gc_tx_max_descs_per_pkt =
						(gc.gc_tx_max_frags + 1) / 2;
		} else {
			gc.gc_tx_max_descs_per_pkt = gc.gc_tx_max_frags;
		}
E 10
I 10
		gc.gc_tx_max_descs_per_pkt = gc.gc_tx_max_frags;
E 10
I 9

E 9
		gc.gc_tx_auto_pad  = TRUE;
		gc.gc_tx_copy_thresh = tu_tx_copy_thresh;

		gc.gc_rx_buf_align = sizeof(uint32_t) - 1;
D 2
		gc.gc_rx_max_frags = p->capability & CHIP_CAP_RING ? 2 : 1;
E 2
I 2
D 9
		if (p->chip_type == CHIP_MX98715) {
			gc.gc_rx_buf_align = 0x10 - 1;
		}
E 9
		gc.gc_rx_max_frags = ((p->capability & CHIP_CAP_RING) != 0)
					? 2 : 1;
E 11
E 2
D 11
		gc.gc_rx_desc_size = sizeof(struct rx_desc) * RX_RING_SIZE;
		gc.gc_rx_ring_size = RX_RING_SIZE;
		gc.gc_rx_buf_size  = RX_RING_SIZE;
		gc.gc_rx_max_descs_per_pkt = 1;
		gc.gc_rx_copy_thresh = tu_rx_copy_thresh;
D 9

E 9
I 9
#ifdef DEBUG_LEVEL
		gc.gc_rx_header_len = 0;
E 11
I 11
			lp->cfg_csr13[PORT_10_HD]  = SIACONN_RST;
			lp->cfg_csr13[PORT_10_FD]  = SIACONN_RST;
			lp->cfg_csr14[PORT_10_HD]  = SIACTRL_10BASET_HALF;
			lp->cfg_csr14[PORT_10_FD]  =
					SIACTRL_10BASET_HALF & ~SIACTRL_LBK;
			break;
		}
E 16
I 16
			/* CSR15: SIA control register configuration */
			lp->cfg_csr15[PORT_10_HD] = SIAGP_ABM; /* 21143 only */
			lp->cfg_csr15[PORT_10_FD] = SIAGP_ABM; /* 21143 only */
			lp->cfg_csr15[PORT_100_HD] = 0;
			lp->cfg_csr15[PORT_100_FD] = 0;
E 16

D 16
		/* CSR15: SIA control register configuration */
		lp->cfg_csr15[PORT_10_HD] = SIAGP_ABM; /* only for 21143 */
		lp->cfg_csr15[PORT_10_FD] = SIAGP_ABM; /* only for 21143 */
		lp->cfg_csr15[PORT_100_HD] = 0;
		lp->cfg_csr15[PORT_100_FD] = 0;

		/* GP ctrl/data registers */
		bzero(lp->gp_ctrl, sizeof(lp->gp_ctrl));
		bzero(lp->gp_data, sizeof(lp->gp_data));
		switch (lp->hw_info->chip_type) {
		case CHIP_LC82C168:
			lp->gp_data[PORT_10_HD] =
			lp->gp_data[PORT_10_FD] =
E 16
I 16
			/* patch GP ctrl/data registers */
			switch (lp->hw_info->chip_type) {
			case CHIP_LC82C168:
				lp->gp_data[PORT_10_HD] =
D 28
				lp->gp_data[PORT_10_FD] =
E 16
					PNIC_GPIO_100_LB | PNIC_GPIO_RL_10;
E 28
I 28
				    lp->gp_data[PORT_10_FD] =
				    PNIC_GPIO_100_LB | PNIC_GPIO_RL_10;
E 28
I 17

E 17
D 16
			lp->gp_data[PORT_100_HD] =
			lp->gp_data[PORT_100_FD] =
E 16
I 16
				lp->gp_data[PORT_100_HD] =
D 28
				lp->gp_data[PORT_100_FD] =
E 16
					PNIC_GPIO_100_EN | PNIC_GPIO_RL_100;
E 28
I 28
				    lp->gp_data[PORT_100_FD] =
				    PNIC_GPIO_100_EN | PNIC_GPIO_RL_100;
E 28
D 16
			break;
E 16
I 16
				break;
			}
E 16
		}
D 26

E 26
I 26
D 28
#ifdef never	/* moved to tu_reset_chip */
E 28
I 28
#ifdef NEVER	/* moved to tu_reset_chip */
E 28
E 26
D 17
		if (lp->have_srom) {
D 16
			tu_srom_parser(dp);
E 16
I 16
			tu_reset_phy(dp);
E 16
		}
E 17
I 17
		tu_enable_phy(dp);
E 17
D 26

E 26
I 26
#endif
E 26
D 16
		/* work around for LC82C168 */
		/* set csr6 one of valid configuration */
E 16
I 16
		/* XXX - work around for LC82C168 */
		/* choose and set csr6 to one of valid configuration */
E 16
		lp->nar = (lp->nar & ~CSR6_PORT_BITS)
D 28
			| lp->cfg_csr6[PORT_IX(dp->speed != GEM_SPD_10,
							dp->full_duplex)];
E 28
I 28
		    | lp->cfg_csr6[PORT_IX(dp->speed != GEM_SPD_10,
		    dp->full_duplex)];
E 28
		UPDATE_NAR(dp, lp->nar);

D 20
		if (gem_mii_init_default(dp) != 0) {
E 20
I 20
D 26
		if (gem_mii_init_default(dp) != GEM_SUCCESS) {
E 26
I 26
		if (gem_mii_probe_default(dp) != GEM_SUCCESS) {
E 26
E 20
			goto x;
		}
#ifdef notdef
{
		int	addr, reg;

		for (addr = 0; addr < 32; addr++) {
			dp->mii_phy_addr = addr;
			for (reg = 0; reg < 8; reg++) {
D 28
				cmn_err(CE_CONT, "addr:%d, reg:%d: 0x%04x",
D 12
					addr, reg, GEM_MII_READ(dp, reg));
			}
		}
		dp->mii_phy_addr = 0;
}
E 11
#endif
E 9
D 2
		gc.gc_rx_buf_max = p->capability & CHIP_CAP_RING
E 2
I 2
D 11
		gc.gc_rx_buf_max = ((p->capability & CHIP_CAP_RING) != 0)
E 2
					? RX_RING_SIZE + 1
					: 10*RX_RING_SIZE;
E 11
I 11
		return 0;
	}
x:
	cmn_err(CE_WARN, "!%s: failed to find PHY", dp->name);
E 12
I 12
D 17
					addr, reg, GEM_MII_READ(dp, reg));
E 17
I 17
					addr, reg, dp->gc.gc_mii_read(dp, reg));
E 28
I 28
				cmn_err(CE_CONT, "!addr:%d, reg:%d: 0x%04x",
				    addr, reg, dp->gc.gc_mii_read(dp, reg));
E 28
E 17
			}
		}
		dp->mii_phy_addr = 0;
}
#endif
D 17
		return 0;
E 17
I 17
		return (GEM_SUCCESS);
E 17
	}
x:
	cmn_err(CE_WARN, "!%s: failed to find PHY", dp->name);
E 12
D 17
	return -1;
E 17
I 17
	return (GEM_FAILURE);
E 17
}
E 11

I 11
/* ======================================================== */
/*
 * OS depend (Solaris DKI) routine
 */
/* ======================================================== */
static int
tuattach(dev_info_t *dip, ddi_attach_cmd_t cmd)
{
	int			i;
I 14
D 16
	int			n;
E 14
	ddi_iblock_cookie_t	c;
E 16
	ddi_acc_handle_t	conf_handle;
	int			ret;
	uint16_t		vid;
	uint16_t		did;
D 16
	uint32_t		dd;
	uint32_t		ps;
	uint8_t			cap_ptr;
E 16
	uint32_t		revid;
D 16
	uint32_t		pmr;
E 16
	uint32_t		ilr;
	int			unit;
	struct chip_info	*p;
D 14
	int			len;
E 14
I 14
D 16
	uint_t			len;
E 14
	struct pci_phys_spec	*regs;
E 16
I 16
	uint32_t		dev_num;
E 16
	const char		*drv_name;
	struct gem_dev		*dp;
	struct tu_dev		*lp;
	void			*base;
	ddi_acc_handle_t	regs_handle;
	struct gem_conf		*gcp;
	int			cache_linesz;
D 16
	int			comm;
E 16
I 16
	uint16_t		comm;
E 16

D 16
	unit =  ddi_get_instance(dip);
E 16
I 16
	unit = ddi_get_instance(dip);
E 16
	drv_name = ddi_driver_name(dip);

D 17
	DPRINTF(3, (CE_CONT, "!%s%d: tuattach: called", drv_name, unit));
E 17
I 17
D 28
	DPRINTF(0, (CE_CONT, "!%s%d: tuattach: called (%s)", drv_name, unit, ident));
E 28
I 28
	DPRINTF(0, (CE_CONT,
	    "!%s%d: tuattach: called (%s)", drv_name, unit, ident));
E 28
E 17

D 16
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
		revid= pci_config_get8(conf_handle, PCI_CONF_REVID);
		ilr  = pci_config_get32(conf_handle, PCI_CONF_ILINE);
E 16
I 16
	if (pci_config_setup(dip, &conf_handle) != DDI_SUCCESS) {
D 28
		cmn_err(CE_WARN, "%s%d: ddi_regs_map_setup failed",
			drv_name, unit);
E 28
I 28
		cmn_err(CE_WARN, "!%s%d: ddi_regs_map_setup failed",
		    drv_name, unit);
E 28
D 17
		return DDI_FAILURE;
E 17
I 17
		return (DDI_FAILURE);
E 17
	}
E 16

D 16
		for (i = 0, p = tu_chiptbl; i < CHIPTABLESIZE; i++, p++) {
			if (p->venid == vid && p->devid == did &&
			    revid <= p->maxrev) {
				/* found */
				cmn_err(CE_CONT,
			"!%s%d: %s (vid: 0x%04x, did: 0x%04x, revid: 0x%02x)",
				drv_name, unit, p->name, vid, did, revid);
				goto chip_found;
			}
E 16
I 16
	/*
	 * Check if chip is supported.
	 */
D 28
	vid  = pci_config_get16(conf_handle, PCI_CONF_VENID);
	did  = pci_config_get16(conf_handle, PCI_CONF_DEVID);
	revid= pci_config_get8(conf_handle, PCI_CONF_REVID);
	ilr  = pci_config_get32(conf_handle, PCI_CONF_ILINE);
E 28
I 28
	vid = pci_config_get16(conf_handle, PCI_CONF_VENID);
	did = pci_config_get16(conf_handle, PCI_CONF_DEVID);
	revid = pci_config_get8(conf_handle, PCI_CONF_REVID);
	ilr = pci_config_get32(conf_handle, PCI_CONF_ILINE);
E 28
D 29

E 29
I 29
#if DEBUG_LEVEL > 10
	for (i = 0; i < 256; i += 4*4) {
		cmn_err(CE_CONT, "%04x: %08x %08x %08x %08x",
		    i,
		    pci_config_get32(conf_handle, i + 0),
		    pci_config_get32(conf_handle, i + 4),
		    pci_config_get32(conf_handle, i + 8),
		    pci_config_get32(conf_handle, i + 12));
	}
#endif
E 29
	for (i = 0, p = tu_chiptbl; i < CHIPTABLESIZE; i++, p++) {
		if (p->venid == vid && p->devid == did &&
D 29
		    revid <= p->maxrev) {
E 29
I 29
		    p->minrev <= revid && revid <= p->maxrev) {
E 29
			/* found */
D 28
			cmn_err(CE_CONT,
		"!%s%d: %s (vid: 0x%04x, did: 0x%04x, revid: 0x%02x)",
			drv_name, unit, p->name, vid, did, revid);
E 28
I 28
			cmn_err(CE_CONT, "!%s%d: %s "
			    "(vid: 0x%04x, did: 0x%04x, revid: 0x%02x)",
			    drv_name, unit, p->name, vid, did, revid);
E 28
			goto chip_found;
E 16
		}
I 16
	}
E 16

D 16
		/* Not found */
		cmn_err(CE_WARN,
			"%s: tu_attach: wrong PCI venid/devid (0x%x, 0x%x)",
			drv_name, vid, did);
		pci_config_teardown(&conf_handle);
		goto err;
E 16
I 16
	/* Not found */
D 28
	cmn_err(CE_WARN,
		"%s: tu_attach: wrong PCI venid/devid (0x%x, 0x%x)",
		drv_name, vid, did);
E 28
I 28
	cmn_err(CE_WARN, "!%s: tu_attach: wrong PCI venid/devid (0x%x, 0x%x)",
	    drv_name, vid, did);
E 28
E 16

I 16
	pci_config_teardown(&conf_handle);
D 17
	return DDI_FAILURE;
E 17
I 17
	return (DDI_FAILURE);
E 17

E 16
chip_found:
D 16
		/* get capabilities on PCI bus */
		cache_linesz  =
			pci_config_get8(conf_handle, PCI_CONF_CACHE_LINESZ);
E 16
I 16
	/* exit power down mode */
	pci_config_put32(conf_handle, CFDD,
D 28
			pci_config_get32(conf_handle, CFDD) &
				~(CFDD_SLEEP | CFDD_SNOOZE | 0x38000000));
E 28
I 28
	    pci_config_get32(conf_handle, CFDD) &
	    ~(CFDD_SLEEP | CFDD_SNOOZE | 0x38000000));
E 28
	/* ensure D0 mode */
	(void) gem_pci_set_power_state(dip, conf_handle, PCI_PMCSR_D0);
E 16

D 16
		/* exit power down mode */
		dd   = pci_config_get32(conf_handle, CFDD);
		pci_config_put32(conf_handle, CFDD,
				dd & ~(CFDD_SLEEP | CFDD_SNOOZE | 0x38000000));
		cap_ptr = pci_config_get8(conf_handle, PCI_CONF_CAP_PTR);
		pmr= pci_config_get32(conf_handle, cap_ptr);
		ps = pci_config_get32(conf_handle, cap_ptr + 4);
		pci_config_put32(conf_handle, cap_ptr + 4,
						ps & ~PCI_PMCSR_STATE_MASK);
E 16
I 16
	/* get capabilities on PCI bus */
	cache_linesz = pci_config_get8(conf_handle, PCI_CONF_CACHE_LINESZ);
I 17
	cmn_err(CE_CONT, "!%s%d: cache line size:%d",
D 28
			drv_name, unit, cache_linesz);
E 28
I 28
	    drv_name, unit, cache_linesz);
E 28
E 17
E 16

I 30
	if (cache_linesz < 8) {
		pci_config_put8(conf_handle, PCI_CONF_CACHE_LINESZ, 0);
		cache_linesz = pci_config_get8(conf_handle,
		    PCI_CONF_CACHE_LINESZ);
		cmn_err(CE_CONT, "!%s%d: cache line size:%d",
		    drv_name, unit, cache_linesz);
	}

E 30
D 16
		ret = pci_config_get16(conf_handle, PCI_CONF_COMM);
		ret |= PCI_COMM_IO | PCI_COMM_MAE | PCI_COMM_ME;
		pci_config_put16(conf_handle, PCI_CONF_COMM, ret);
E 16
I 16
	/* fix pci command register */
	comm = pci_config_get16(conf_handle, PCI_CONF_COMM);
	pci_config_put16(conf_handle, PCI_CONF_COMM,
D 28
			comm | PCI_COMM_IO | PCI_COMM_MAE | PCI_COMM_ME);
E 28
I 28
	    comm | PCI_COMM_IO | PCI_COMM_MAE | PCI_COMM_ME);
E 28
E 16

D 16
		comm = pci_config_get16(conf_handle, PCI_CONF_COMM);
E 16
I 16
	/* fix latency timer */
D 29
	if (p->chip_type == CHIP_MX987XX && (revid & 0xf0) == 0) {
E 29
I 29
	if (p->chip_type == CHIP_MX98713) {
E 29
		pci_config_put8(conf_handle,
D 28
			PCI_CONF_LATENCY_TIMER, 0x28);
E 28
I 28
		    PCI_CONF_LATENCY_TIMER, 0x28);
E 28
	}
E 16
D 29

D 16
		pci_config_teardown(&conf_handle);
E 16
I 16
	/* workaround for DM9102 */
	if (p->chip_type == CHIP_DM9102) {
E 29
I 29
#if 0
	pci_config_put8(conf_handle, PCI_CONF_LATENCY_TIMER, 0x20);
#endif
	/* workaround for DM9102A */
	if (p->chip_type == CHIP_DM9102A) {
E 29
		uint32_t	pmr;
E 16

I 16
D 28
		pmr= pci_config_get32(conf_handle,
			pci_config_get8(conf_handle, PCI_CONF_CAP_PTR));
E 28
I 28
		pmr = pci_config_get32(conf_handle,
		    pci_config_get8(conf_handle, PCI_CONF_CAP_PTR));
E 28
#ifdef TEST_DM9102A_E3
		revid = DM9102A_E3;
#else
		revid |= pmr & (PCI_PMCAP_VER_MASK << 16);
#endif
	}
E 16

I 16
	pci_config_teardown(&conf_handle);

	switch (cmd) {
D 17
	case DDI_RESUME: {
		gld_mac_info_t  *macinfo;
E 17
I 17
	case DDI_RESUME:
		return (gem_resume(dip));
E 17

D 17
		macinfo = (gld_mac_info_t *)ddi_get_driver_private(dip);
		dp = (struct gem_dev *)macinfo->gldm_private;

		tu_reset_phy(dp);
		return gem_resume(dip);
	}

E 17
	case DDI_ATTACH:
E 16
		/*
		 * Map in the device registers.
		 */
D 16

		/* Search IO-range or memory-range to be mapped */
		regs = NULL;
		len  = 0;
D 14
		if (ddi_getlongprop(DDI_DEV_T_ANY, dip, DDI_PROP_DONTPASS,
			"reg", (caddr_t)&regs, &len) != DDI_PROP_SUCCESS) {
E 14
I 14
		if (ddi_prop_lookup_int_array(
			DDI_DEV_T_ANY, dip, DDI_PROP_DONTPASS,
			"reg", (int **)&regs, &len) != DDI_PROP_SUCCESS) {
E 14
			cmn_err(CE_WARN,
			"%s%d: failed to get reg property", drv_name, unit);
			goto err;
		}
I 14
		n = len / (sizeof(struct pci_phys_spec) / sizeof(int));
E 14

		ASSERT(regs != NULL && len > 0);
#if DEBUG_LEVEL > 0
		cmn_err(CE_CONT,
"!%s%d: dd:%x cap_ptr:%x pmr:%x ps:%x cache_linesz:0x%x cmd:0x%x ilr:0x%x",
			drv_name, unit,
			dd, cap_ptr, pmr, ps, cache_linesz, comm, ilr);
D 14
		for (i = 0; i <len / sizeof(struct pci_phys_spec); i++) {
E 14
I 14
		for (i = 0; i < n; i++) {
E 14
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
D 14
		for (i = 0; i <len / sizeof(struct pci_phys_spec); i++) {
E 14
I 14
		for (i = 0; i < n; i++) {
E 14
			if ((regs[i].pci_phys_hi & PCI_REG_ADDR_M) == 
E 16
I 16
		if (gem_pci_regs_map_setup(dip,
E 16
#ifdef MAP_MEM
D 16
			    PCI_ADDR_MEM32
E 16
I 16
D 17
			PCI_ADDR_MEM32,
E 17
I 17
D 28
			PCI_ADDR_MEM32, PCI_ADDR_MASK,
E 28
I 28
		    PCI_ADDR_MEM32, PCI_ADDR_MASK,
E 28
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
D 28
			PCI_ADDR_IO, PCI_ADDR_MASK,
E 28
I 28
		    PCI_ADDR_IO, PCI_ADDR_MASK,
E 28
E 17
E 16
#endif
D 16
			) {
D 14
				/* it's I/O space */
				kmem_free(regs, len);
E 14
I 14
				/* it's I/O or MEM32 space */
				ddi_prop_free(regs);
E 14
				goto io_range_found;
			}
		}
		cmn_err(CE_WARN, 
#ifdef MAP_MEM
			"%s%d: failed to find MEM32 space",
#else
			"%s%d: failed to find IO space",
#endif
			drv_name, unit);
D 14
		kmem_free(regs, len);
E 14
I 14
		ddi_prop_free(regs);
E 14
		goto err;
io_range_found:

		if (ddi_regs_map_setup(dip, i, (caddr_t *)&base,
			0, 0, &tu_dev_attr, &regs_handle)) {
			cmn_err(CE_WARN, "%s%d: ddi_regs_map_setup failed",
				drv_name, unit);
E 16
I 16
D 28
			&tu_dev_attr,
			(caddr_t *)&base, &regs_handle) != DDI_SUCCESS) {
E 28
I 28
		    &tu_dev_attr,
D 29
		    (caddr_t *)&base, &regs_handle) != DDI_SUCCESS) {
E 29
I 29
		    (void *)&base, &regs_handle) != DDI_SUCCESS) {
E 29
E 28
E 16
			goto err;
		}

D 16
		if (p->chip_type == CHIP_DM9102) {
#ifdef DM9102A_E3_TEST
			revid = DM9102A_E3;
#else
			revid |= pmr & (PCI_PMCAP_VER_MASK << 16);
#endif
		}
E 16

		/*
		 * Construct gem configration
		 */
D 28
		gcp = (struct gem_conf *) kmem_zalloc(sizeof(*gcp), KM_SLEEP);
E 28
I 28
		gcp = kmem_zalloc(sizeof (*gcp), KM_SLEEP);
E 28

I 28
		lp = kmem_zalloc(sizeof (struct tu_dev), KM_SLEEP);

		lp->hw_info = p;
		lp->pci_cache_linesz = cache_linesz;
		lp->pci_comm = comm;
		lp->pci_revid = revid;
#ifdef CONFIG_MULTIPORT
		lp->dev_num = dev_num;
		lp->dev_index = 0;
#endif

E 28
		/* name */
		sprintf(gcp->gc_name, "%s%d", drv_name, unit);

		/* consistency on tx and rx */
		gcp->gc_tx_buf_align = p->tx_align - 1;
D 28
		gcp->gc_tx_max_frags = GEM_MAXTXFRAGS;
E 28
I 28
		gcp->gc_tx_max_frags = MAXTXFRAGS;
E 28
D 17
		gcp->gc_tx_desc_size = sizeof(struct tx_desc) * TX_RING_SIZE;
		gcp->gc_tx_ring_size = TX_RING_SIZE;
		gcp->gc_tx_buf_size  = TX_BUF_SIZE;
E 17
		gcp->gc_tx_max_descs_per_pkt = gcp->gc_tx_max_frags;
D 17

E 17
I 17
		gcp->gc_tx_desc_unit_shift = 4;		/* 16 byte */
I 29
#ifdef DEBUG_TX_WAKEUP
E 29
D 28
		gcp->gc_tx_buf_size  = TX_BUF_SIZE;
E 28
I 28
		gcp->gc_tx_buf_size = TX_BUF_SIZE;
I 29
		gcp->gc_tx_buf_limit = gcp->gc_tx_buf_size - 1;
		gcp->gc_tx_ring_size = TX_RING_SIZE;
		gcp->gc_tx_ring_limit = gcp->gc_tx_ring_size - 1;
#else
		gcp->gc_tx_buf_size = TX_BUF_SIZE;
E 29
E 28
		gcp->gc_tx_buf_limit = gcp->gc_tx_buf_size;
		gcp->gc_tx_ring_size = TX_RING_SIZE;
D 28
		gcp->gc_tx_ring_limit= gcp->gc_tx_ring_size;
E 17
D 26
		gcp->gc_tx_auto_pad  = TRUE;
E 26
I 26
		gcp->gc_tx_auto_pad  = B_TRUE;
E 28
I 28
		gcp->gc_tx_ring_limit = gcp->gc_tx_ring_size;
I 29
#endif
E 29
		gcp->gc_tx_auto_pad = B_TRUE;
E 28
E 26
		gcp->gc_tx_copy_thresh = tu_tx_copy_thresh;
I 17
D 28
		gcp->gc_tx_desc_write_oo = B_FALSE;
E 28
E 17

D 28
		gcp->gc_rx_buf_align = sizeof(uint32_t) - 1;
I 16
		if (p->chip_type == CHIP_MX987XX && (revid & 0xf0) == 0) {
			gcp->gc_rx_buf_align = PBL_DEFAULT - 1;
		}
E 16
		gcp->gc_rx_max_frags = ((p->capability & CHIP_CAP_RING) != 0)
					? 2 : 1;
E 28
I 28
		gcp->gc_rx_buf_align = sizeof (uint32_t) - 1;
		gcp->gc_rx_max_frags =
		    (p->capability & CHIP_CAP_RING) ? 2 : 1;
E 28
D 17
		gcp->gc_rx_desc_size = sizeof(struct rx_desc) * RX_RING_SIZE;
E 17
I 17
		gcp->gc_rx_desc_unit_shift = 4;		/* 16 byte */
E 17
		gcp->gc_rx_ring_size = RX_RING_SIZE;
D 17
		gcp->gc_rx_buf_size  = RX_BUF_SIZE;
		gcp->gc_rx_max_descs_per_pkt = 1;
E 17
I 17
D 28
		gcp->gc_rx_buf_max   = RX_BUF_SIZE;
E 28
I 28
		gcp->gc_rx_buf_max = RX_BUF_SIZE;
E 28
E 17
		gcp->gc_rx_copy_thresh = tu_rx_copy_thresh;
		gcp->gc_rx_header_len = 0;
D 17
		gcp->gc_rx_copy_thresh = tu_rx_copy_thresh;
D 14
		if (gcp->gc_rx_max_frags > 1) {
			gcp->gc_rx_buf_max = gcp->gc_rx_buf_size+1;
		} else {
			gcp->gc_rx_buf_max = gcp->gc_rx_buf_size;
		}
E 14
I 14
		gcp->gc_rx_buf_max = gcp->gc_rx_buf_size + 1;
E 17

I 17
		gcp->gc_io_area_size = 0;

I 29
		switch (p->chip_type) {
		case CHIP_XIRCOM:
			/* xircom causes an interrupt for every fragment */
			gcp->gc_tx_max_frags = 1;
			gcp->gc_tx_max_descs_per_pkt = gcp->gc_tx_max_frags;
			break;
		}

E 29
E 17
E 14
E 11
		/* map attributes */
D 6
		gc.gc_dev_attr = gem_dev_attr;
		gc.gc_buf_attr = gem_dev_attr;
E 6
I 6
D 11
		gc.gc_dev_attr  = tu_dev_attr;
		gc.gc_buf_attr  = tu_buf_attr;
		gc.gc_desc_attr = tu_dev_attr;
E 11
I 11
D 14
		gcp->gc_dev_attr  = tu_dev_attr;
		gcp->gc_buf_attr  = tu_buf_attr;
		gcp->gc_desc_attr = tu_dev_attr;
E 14
I 14
D 22
		STRUCT_COPY(gcp->gc_dev_attr, tu_dev_attr);
		STRUCT_COPY(gcp->gc_buf_attr, tu_buf_attr);
D 19
		STRUCT_COPY(gcp->gc_desc_attr, tu_dev_attr);
E 19
I 19
		STRUCT_COPY(gcp->gc_desc_attr, tu_buf_attr);
E 22
I 22
		gcp->gc_dev_attr = tu_dev_attr;
		gcp->gc_buf_attr = tu_buf_attr;
		gcp->gc_desc_attr = tu_buf_attr;
E 22
E 19
E 14
E 11
E 6

		/* dma attributes */
D 11
		gc.gc_dma_attr_desc = tu_dma_attr_nosc;
		gc.gc_dma_attr_txbuf = tu_dma_attr_buf;
		gc.gc_dma_attr_txbuf.dma_attr_align  = gc.gc_tx_buf_align + 1;
		gc.gc_dma_attr_txbuf.dma_attr_sgllen = gc.gc_tx_max_frags;
		gc.gc_dma_attr_rxbuf = tu_dma_attr_buf;
		gc.gc_dma_attr_rxbuf.dma_attr_align  = gc.gc_rx_buf_align + 1;
		gc.gc_dma_attr_rxbuf.dma_attr_sgllen = gc.gc_rx_max_frags;
E 11
I 11
D 14
		gcp->gc_dma_attr_desc = tu_dma_attr_nosc;
		gcp->gc_dma_attr_txbuf = tu_dma_attr_buf;
E 14
I 14
D 22
		STRUCT_COPY(gcp->gc_dma_attr_desc, tu_dma_attr_desc);
		STRUCT_COPY(gcp->gc_dma_attr_txbuf, tu_dma_attr_buf);
E 22
I 22
		gcp->gc_dma_attr_desc = tu_dma_attr_desc;
		gcp->gc_dma_attr_txbuf = tu_dma_attr_buf;
E 22
E 14
D 28
		gcp->gc_dma_attr_txbuf.dma_attr_align  = gcp->gc_tx_buf_align+1;
E 28
I 28
		gcp->gc_dma_attr_txbuf.dma_attr_align = gcp->gc_tx_buf_align+1;
E 28
		gcp->gc_dma_attr_txbuf.dma_attr_sgllen = gcp->gc_tx_max_frags;
D 14
		gcp->gc_dma_attr_rxbuf = tu_dma_attr_buf;
E 14
I 14
D 22
		STRUCT_COPY(gcp->gc_dma_attr_rxbuf, tu_dma_attr_buf);
E 22
I 22
		gcp->gc_dma_attr_rxbuf = tu_dma_attr_buf;
E 22
E 14
D 28
		gcp->gc_dma_attr_rxbuf.dma_attr_align  = gcp->gc_rx_buf_align+1;
E 28
I 28
		gcp->gc_dma_attr_rxbuf.dma_attr_align = gcp->gc_rx_buf_align+1;
E 28
		gcp->gc_dma_attr_rxbuf.dma_attr_sgllen = gcp->gc_rx_max_frags;
E 11

D 29

E 29
		/* time out parameters */
D 9
		gc.gc_tx_timeout = drv_usectohz(5*1000000);
		gc.gc_tx_timeout_interval = drv_usectohz(1000000);
E 9
I 9
D 11
		gc.gc_tx_timeout = 2*ONESEC;
		gc.gc_tx_timeout_interval = ONESEC;
E 11
I 11
D 28
		gcp->gc_tx_timeout = 5*ONESEC;
E 28
I 28
		gcp->gc_tx_timeout = 3*ONESEC;
E 28
		gcp->gc_tx_timeout_interval = ONESEC;
E 11
E 9
D 10

D 9
		/* auto negotiation */
		gc.gc_flow_control = TRUE;
		if (p->chip_type == CHIP_MX98715) {
			/* Not implemented yet */
E 9
I 9
		/* auto negotiation parameters */
		switch (p->chip_type) {
		case CHIP_DM9102:
			gc.gc_flow_control = TRUE;
			break;
		case CHIP_CENTAUR: /* not implemented completely */
		default:
E 9
			gc.gc_flow_control = FALSE;
I 9
			break;
E 9
		}

		/* MII timeout parameters */
D 9
		gc.gc_mii_link_watch_interval = drv_usectohz(1*1000000);
D 2
		gc.gc_mii_reset_timeout    = 1;
		gc.gc_mii_an_timeout       = 5;	/* 5 sec */
E 2
I 2
		gc.gc_mii_reset_timeout    = 2;
		gc.gc_mii_an_timeout       = 5;	/* in second */
E 2
D 7
		gc.gc_mii_an_wait          = 0;
E 7
I 7
		if (p->chip_type == CHIP_DM9102) {
			gc.gc_mii_an_wait  = 3;
		} else {
			gc.gc_mii_an_wait  = 0;
E 9
I 9
		gc.gc_mii_link_watch_interval = ONESEC;
		gc.gc_mii_reset_timeout       = MII_RESET_TIMEOUT;
		gc.gc_mii_an_watch_interval   = ONESEC/10;	/* 100mS */
		gc.gc_mii_an_timeout          = MII_AN_TIMEOUT;

		switch(p->chip_type) {
#ifdef notdef
		case CHIP_CENTAUR:
			gc.gc_mii_an_wait = (25*ONESEC)/10;
			break;
#endif
		default:
			gc.gc_mii_an_wait = 0;
			break;
E 9
		}
E 7
D 9
		gc.gc_mii_linkdown_timeout = 10; 
E 9

I 9
		gc.gc_mii_linkdown_timeout = MII_LINKDOWN_TIMEOUT;

E 9
		/* workarounds */
D 9
		gc.gc_mii_need_an_delay   = FALSE;
D 2
		gc.gc_mii_linkdown_action = MII_ACTION_NONE;
E 2
I 2
		if (p->chip_type == CHIP_MX98715) {
E 9
I 9
                gc.gc_mii_an_delay = 0;
		switch(p->chip_type) {
		case CHIP_MX98715:
E 9
			gc.gc_mii_linkdown_action = MII_ACTION_RESET;
D 9
		} else {
E 9
I 9
			gc.gc_mii_dont_reset = FALSE;
			break;
#ifdef notdef
		case CHIP_DM9102:
E 9
			gc.gc_mii_linkdown_action = MII_ACTION_NONE;
D 9
		}
E 2
D 7
		gc.gc_mii_dont_reset      = FALSE;
E 7
I 7
		gc.gc_mii_dont_reset = FALSE;
E 7

		/* I/O methods */

		/* mac operation */
		gc.gc_attach_chip = &tu_attach_chip;
		gc.gc_reset_chip = &tu_reset_chip;
		gc.gc_init_chip = &tu_init_chip;
		gc.gc_start_chip = &tu_start_chip;
		gc.gc_stop_chip = &tu_stop_chip;
		gc.gc_multicast_hash = &tu_multicast_hash;
		gc.gc_set_rx_filter = &tu_set_rx_filter;
		gc.gc_set_media = &tu_set_media;
		gc.gc_get_stats = &tu_get_stats;
		gc.gc_interrupt = &tu_interrupt;

		/* descriptor operation */
		if (p->capability & CHIP_CAP_RING) {
			/* Use tx/rx descriptors as ring method */
			gc.gc_tx_desc_write = &tu_tx_desc_write2;
			gc.gc_rx_desc_write = &tu_rx_desc_write2;

			gc.gc_tx_desc_init = &tu_tx_desc_init2;
			gc.gc_rx_desc_init = &tu_rx_desc_init2;
		}
		else {
			/* Use tx/rx descriptors as chain method */
			gc.gc_tx_desc_write = &tu_tx_desc_write1;
			gc.gc_rx_desc_write = &tu_rx_desc_write1;

			gc.gc_tx_desc_init = &tu_tx_desc_init1;
			gc.gc_rx_desc_init = &tu_rx_desc_init1;
		}
		gc.gc_tx_desc_stat  = &tu_tx_desc_stat;
		gc.gc_rx_desc_stat  = &tu_rx_desc_stat;
		gc.gc_tx_desc_clean = &tu_tx_desc_clean;
		gc.gc_rx_desc_clean = &tu_rx_desc_clean;

		/* mii operations */
D 2
		if (p->chip_type == CHIP_DM9102) {
			gc.gc_mii_init = &tu_mii_init_dm9102;
		} else {
			gc.gc_mii_init = &gem_mii_init_default;
		}
E 2
I 2
		gc.gc_mii_init   = &tu_mii_init;
E 2
		gc.gc_mii_config = &gem_mii_config_default;
D 2
		
		if ((p->capability & CHIP_CAP_MII) == 0) {
E 2
I 2
D 3
#ifdef notdef
		if ((p->hw_info->chip_type == CHIP_AN981) == 0) {
E 2
			/* Use MII emulation routines for SYM interface */
D 2
			gc.gc_mii_sync   = &tu_mii_sync_sym;
			gc.gc_mii_read   = &tu_mii_read_sym;
			gc.gc_mii_write  = &tu_mii_write_sym;
		} else {
E 2
I 2
			gc.gc_mii_sync   = &tu_mii_sync_nway;
			gc.gc_mii_read   = &tu_mii_read_nway;
			gc.gc_mii_write  = &tu_mii_write_nway;
		} else
#endif
		{
E 3
I 3

		if (p->chip_type == CHIP_COMET) {
			gc.gc_mii_sync   = &tu_mii_sync_comet;
			gc.gc_mii_read   = &tu_mii_read_comet;
			gc.gc_mii_write  = &tu_mii_write_comet;
		}
I 7
		else if (p->chip_type == CHIP_DM9102) {
			gc.gc_mii_sync   = &tu_mii_sync_9102;
			gc.gc_mii_read   = &tu_mii_read_9102;
			gc.gc_mii_write  = &tu_mii_write_9102;
		}
I 8
		else if (p->chip_type == CHIP_LC82C168) {
			gc.gc_mii_sync   = &tu_mii_sync_pnic;
			gc.gc_mii_read   = &tu_mii_read_pnic;
			gc.gc_mii_write  = &tu_mii_write_pnic;
		}
E 8
E 7
		else {
E 3
E 2
			gc.gc_mii_sync   = &tu_mii_sync;
			gc.gc_mii_read   = &tu_mii_read;
			gc.gc_mii_write  = &tu_mii_write;
		}
		gc.gc_mii_tune_phy = NULL;
I 3
		gc.gc_get_packet   = &gem_get_packet_default;
E 3

D 7
		lp = (struct tu_chip_state *)
			kmem_zalloc(sizeof(struct tu_chip_state), KM_SLEEP);
E 7
I 7
		lp = (struct tu_dev *)
			kmem_zalloc(sizeof(struct tu_dev), KM_SLEEP);
E 7

		lp->hw_info  = p;
		lp->pci_cache_linesz = cache_linesz;
		lp->pci_comm = comm;
I 2
		lp->pci_revid= revid;
E 2

I 7
		ddi_set_driver_private(dip, NULL);

E 7
I 3
		DPRINTF(2, (CE_CONT,
			"tuattach: %s%d pre gem_do_attach", drv_name, unit));

E 3
		dp = gem_do_attach(dip, &gc, base, &regs_handle,
						lp, sizeof(*lp));
		if (dp != NULL) {
I 3
			DPRINTF(2, (CE_CONT,
			"!%s%d: tuattach: success", drv_name, unit));
E 3
			return DDI_SUCCESS;
		}
err_free_mem:
D 7
		kmem_free(lp, sizeof(struct tu_chip_state));
E 7
I 7
		kmem_free(lp, sizeof(struct tu_dev));
E 7
err:
		return DDI_FAILURE;
	}
	return DDI_FAILURE;
}

static int
tudetach(dev_info_t *dip, ddi_detach_cmd_t cmd)
{
D 7
	struct gem_dev *dp;
D 6
	struct tu_chip_state	*lp = (struct tu_chip_state *)dp->private;
E 6
I 6
	gld_mac_info_t  *macinfo;
E 7
I 7
	gld_mac_info_t	*macinfo;
	struct gem_dev	*dp;
	struct tu_dev	*lp;
E 7
E 6

I 6
	macinfo = (gld_mac_info_t *)ddi_get_driver_private(dip);
	dp = (struct gem_dev *)macinfo->gldm_private;

	DPRINTF(2, (CE_CONT, "!%s: tudetach: called", dp->name));

E 6
	if (cmd == DDI_DETACH) {
		return gem_do_detach(dip);
	}
	return DDI_FAILURE;
}

/* ======================================================== */
/*
 * OS depend (loadable streams driver) routine
 */
/* ======================================================== */
static	struct module_info tuminfo = {
	0,			/* mi_idnum */
	"tu",			/* mi_idname */
	0,			/* mi_minpsz */
	ETHERMTU,		/* mi_maxpsz */
	TX_BUF_SIZE*2048,	/* mi_hiwat */
	1,			/* mi_lowat */
};

static	struct qinit turinit = {
	(int (*)()) NULL,	/* qi_putp */
	gld_rsrv,		/* qi_srvp */
	gld_open,		/* qi_qopen */
	gld_close,		/* qi_qclose */
	(int (*)()) NULL,	/* qi_qadmin */
	&tuminfo,		/* qi_minfo */
	NULL			/* qi_mstat */
};

static	struct qinit tuwinit = {
	gld_wput,		/* qi_putp */
	gld_wsrv,		/* qi_srvp */
	(int (*)()) NULL,	/* qi_qopen */
	(int (*)()) NULL,	/* qi_qclose */
	(int (*)()) NULL,	/* qi_qadmin */
	&tuminfo,		/* qi_minfo */
	NULL			/* qi_mstat */
};

static struct streamtab	tu_info = {
	&turinit,	/* st_rdinit */
	&tuwinit,	/* st_wrinit */
	NULL,		/* st_muxrinit */
	NULL		/* st_muxwrinit */
};

static	struct cb_ops cb_tu_ops = {
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
	&tu_info,	/* cb_stream */
	D_NEW|D_MP	/* cb_flag */
};

static	struct dev_ops tu_ops = {
	DEVO_REV,	/* devo_rev */
	0,		/* devo_refcnt */
	gld_getinfo,	/* devo_getinfo */
	nulldev,	/* devo_identify */
	nulldev,	/* devo_probe */
	tuattach,	/* devo_attach */
	tudetach,	/* devo_detach */
	nodev,		/* devo_reset */
	&cb_tu_ops,	/* devo_cb_ops */
	NULL,		/* devo_bus_ops */
	ddi_power	/* devo_power */
};

static struct modldrv modldrv = {
	&mod_driverops,	/* Type of module.  This one is a driver */
	ident,
	&tu_ops,	/* driver ops */
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

D 2
	DPRINTF(2, (CE_CONT, "tu: _init: called"));
E 2
I 2
	DPRINTF(2, (CE_CONT, "!tu: _init: called"));
E 2
	status = mod_install(&modlinkage);

	return (status);
}

/*
 * _fini : done
 */
int
_fini(void)
{
	int	status;

D 2
	DPRINTF(2, (CE_CONT, "tu: _fini: called"));
E 2
I 2
	DPRINTF(2, (CE_CONT, "!tu: _fini: called"));
E 2
	status = mod_remove(&modlinkage);
	return (status);
}

int
_info(struct modinfo *modinfop)
{
	return (mod_info(&modlinkage, modinfop));
}
E 9
E 1
I 9
			gc.gc_mii_dont_reset = FALSE;
			break;

		case CHIP_21140:
E 10
I 10

		/* auto negotiation parameters */
		switch (p->chip_type) {
I 14
#ifdef NEVER
E 14
		case CHIP_DM9102:
I 29
		case CHIP_DM9102A:
E 29
D 11
			gc.gc_flow_control = TRUE;
E 11
I 11
D 14
			gcp->gc_flow_control = TRUE;
E 14
I 14
			/* it doesn't work */
			gcp->gc_flow_control = FLOW_CONTROL_RX_PAUSE;
E 14
E 11
			break;

D 14
		case CHIP_CENTAUR: /* not implemented completely */
			/* fall down */
E 14
I 14
		case CHIP_CENTAUR:
			/* it doesn't work */
			gcp->gc_flow_control = FLOW_CONTROL_SYMMETRIC;
			break;
#endif
E 14
		default:
D 11
			gc.gc_flow_control = FALSE;
E 11
I 11
D 14
			gcp->gc_flow_control = FALSE;
E 14
I 14
			gcp->gc_flow_control = FLOW_CONTROL_NONE;
E 14
E 11
			break;
		}

		/* MII timeout parameters */
D 11
		gc.gc_mii_link_watch_interval = ONESEC;
		gc.gc_mii_reset_timeout       = MII_RESET_TIMEOUT;
		gc.gc_mii_an_watch_interval   = ONESEC/10;	/* 100mS */
		gc.gc_mii_an_timeout          = MII_AN_TIMEOUT;
E 11
I 11
D 17
		gcp->gc_mii_link_watch_interval = ONESEC;
E 17
I 17
		gcp->gc_mii_link_watch_interval = GEM_LINK_WATCH_INTERVAL;
E 17
D 28
		gcp->gc_mii_reset_timeout       = MII_RESET_TIMEOUT;
		gcp->gc_mii_an_watch_interval   = ONESEC/10;	/* 100mS */
		gcp->gc_mii_an_timeout          = MII_AN_TIMEOUT;
E 28
I 28
		gcp->gc_mii_reset_timeout = MII_RESET_TIMEOUT;
		gcp->gc_mii_an_watch_interval = ONESEC/10;	/* 100mS */
		gcp->gc_mii_an_timeout = MII_AN_TIMEOUT;
E 28
E 11

D 17
		switch(p->chip_type) {
E 17
I 17
		switch (p->chip_type) {
E 17
D 29
		case CHIP_DM9102:
E 29
I 29
		case CHIP_DM9102A:
E 29
			/* work around for rev E3 */
D 11
			gc.gc_mii_an_wait = (25*ONESEC)/10;
E 11
I 11
			gcp->gc_mii_an_wait = (25*ONESEC)/10;
E 11
			break;

		default:
D 11
			gc.gc_mii_an_wait = 0;
E 11
I 11
			gcp->gc_mii_an_wait = 0;
E 11
			break;
		}

D 11
		gc.gc_mii_linkdown_timeout = MII_LINKDOWN_TIMEOUT;
E 11
I 11
		gcp->gc_mii_linkdown_timeout = MII_LINKDOWN_TIMEOUT;
E 11

		/* workarounds */
D 11
                gc.gc_mii_an_delay = 0;
E 11
I 11
D 28
                gcp->gc_mii_an_delay = 0;
E 28
I 28
		gcp->gc_mii_an_delay = 0;
E 28
I 20
D 26

E 20
		gcp->gc_mii_dont_reset = FALSE;
I 20
#if 1
E 20
I 17
		gcp->gc_mii_dont_reset = TRUE;
I 20
#endif
E 26
I 26
		gcp->gc_mii_dont_reset = B_FALSE;
E 26
E 20
E 17
D 14
		gcp->gc_mii_linkdown_action = MII_ACTION_RSA;
E 14
I 14
D 16
		gcp->gc_mii_linkdown_action = MII_ACTION_RESET;
E 16
I 16
		gcp->gc_mii_linkdown_action = MII_ACTION_RSA;
		gcp->gc_mii_linkdown_timeout_action = MII_ACTION_RESET;
E 16
E 14
E 11
D 17
		switch(p->chip_type) {
E 17
I 17
		switch (p->chip_type) {
E 17
D 11
		case CHIP_MX98715:
			gc.gc_mii_linkdown_action = MII_ACTION_RESET;
			gc.gc_mii_dont_reset = FALSE;
E 11
I 11
D 29
		case CHIP_MX987XX:
E 29
I 29
		case CHIP_MX98713:
		case CHIP_MX98713A:
		case CHIP_MX98715:
		case CHIP_MX98725:
E 29
D 16
			gcp->gc_mii_linkdown_action = MII_ACTION_RESET;
			gcp->gc_mii_addr_min = 1; /* for mx98713 only */
E 16
I 16
D 17
			/* for mx98713 only, skip internal nway registers */
E 17
I 17
			/* for mx98713 only, skip internal NWAY register */
E 17
			gcp->gc_mii_addr_min = 1;
I 20
D 26
			gcp->gc_mii_dont_reset = FALSE;
E 26
I 26
			gcp->gc_mii_dont_reset = B_FALSE;
E 26
E 20
E 16
E 11
			break;
D 11
#ifdef notdef
		case CHIP_DM9102:
			gc.gc_mii_linkdown_action = MII_ACTION_NONE;
			gc.gc_mii_dont_reset = FALSE;
			break;
E 11

D 11
		case CHIP_21140:
E 10
			/* 21140 may use DAVICOM DM9101 that needs RSA option */
			gc.gc_mii_an_delay = ONESEC/10;
			gc.gc_mii_linkdown_action = MII_ACTION_NONE;
			gc.gc_mii_dont_reset = TRUE;
E 11
I 11
		case CHIP_CONEXANT:
			gcp->gc_mii_addr_min = 1; /* skip HomePNA PHY at 0 */
E 11
			break;
I 26

		case CHIP_ULI526X:
			gcp->gc_mii_linkdown_action = MII_ACTION_RESET;
			break;
I 29

		case CHIP_XIRCOM:
			gcp->gc_mii_linkdown_action = MII_ACTION_RESET;
			break;
E 29
E 26
D 11
#endif
		default:
			gc.gc_mii_linkdown_action = MII_ACTION_RSA;
			gc.gc_mii_dont_reset = FALSE;
			break;
E 11
		}

		/* I/O methods */

		/* mac operation */
D 11
		gc.gc_attach_chip = &tu_attach_chip;
		gc.gc_reset_chip  = &tu_reset_chip;
		gc.gc_init_chip   = &tu_init_chip;
		gc.gc_start_chip  = &tu_start_chip;
		gc.gc_stop_chip   = &tu_stop_chip;
		gc.gc_multicast_hash = &tu_multicast_hash;
		gc.gc_set_rx_filter  = &tu_set_rx_filter;
		gc.gc_set_media   = &tu_set_media;
		gc.gc_get_stats   = &tu_get_stats;
		gc.gc_interrupt   = &tu_interrupt;
E 11
I 11
		gcp->gc_attach_chip = &tu_attach_chip;
D 28
		gcp->gc_reset_chip  = &tu_reset_chip;
		gcp->gc_init_chip   = &tu_init_chip;
		gcp->gc_start_chip  = &tu_start_chip;
		gcp->gc_stop_chip   = &tu_stop_chip;
E 28
I 28
		gcp->gc_reset_chip = &tu_reset_chip;
		gcp->gc_init_chip = &tu_init_chip;
		gcp->gc_start_chip = &tu_start_chip;
		gcp->gc_stop_chip = &tu_stop_chip;
E 28
		gcp->gc_multicast_hash = &tu_multicast_hash;
D 22
		gcp->gc_set_rx_filter  = &tu_set_rx_filter;
E 22
I 22
		switch (p->chip_type) {
		case CHIP_CENTAUR:
D 28
			gcp->gc_set_rx_filter  = &tu_set_rx_filter_admtek;
E 28
I 28
			gcp->gc_set_rx_filter = &tu_set_rx_filter_admtek;
E 28
			break;
		default:
D 28
			gcp->gc_set_rx_filter  = &tu_set_rx_filter;
E 28
I 28
			gcp->gc_set_rx_filter = &tu_set_rx_filter;
E 28
			break;
		}
E 22
D 28
		gcp->gc_set_media   = &tu_set_media;
		gcp->gc_get_stats   = &tu_get_stats;
		gcp->gc_interrupt   = &tu_interrupt;
E 28
I 28
		gcp->gc_set_media = &tu_set_media;
		gcp->gc_get_stats = &tu_get_stats;
		gcp->gc_interrupt = &tu_interrupt;
E 28
E 11

		/* descriptor operation */
I 10
D 11
		gc.gc_tx_desc_write = &tu_tx_desc_write1;
		gc.gc_rx_desc_write = &tu_rx_desc_write2;
		gc.gc_tx_desc_init = &tu_tx_desc_init1;
		gc.gc_tx_desc_clean = &tu_tx_desc_init1;
E 11
I 11
		gcp->gc_tx_desc_write = &tu_tx_desc_write1;
I 17
D 28
		gcp->gc_tx_start      = &tu_tx_start;
E 28
I 28
		gcp->gc_tx_start = &tu_tx_start;
E 28
E 17
		gcp->gc_rx_desc_write = &tu_rx_desc_write2;
		gcp->gc_tx_desc_init = &tu_tx_desc_init1;
		gcp->gc_tx_desc_clean = &tu_tx_desc_init1;
E 11
E 10
D 28
		if ((p->capability & CHIP_CAP_RING) != 0) {
E 28
I 28
		if (p->capability & CHIP_CAP_RING) {
E 28
D 10
			/* Use tx/rx descriptors as ring method */
			gc.gc_tx_desc_write = &tu_tx_desc_write2;
			gc.gc_rx_desc_write = &tu_rx_desc_write2;

			gc.gc_tx_desc_init = &tu_tx_desc_init2;
E 10
D 11
			gc.gc_rx_desc_init = &tu_rx_desc_init2;
D 10
		}
		else {
			/* Use tx/rx descriptors as chain method */
			gc.gc_tx_desc_write = &tu_tx_desc_write1;
			gc.gc_rx_desc_write = &tu_rx_desc_write1;

			gc.gc_tx_desc_init = &tu_tx_desc_init1;
E 10
I 10
			gc.gc_rx_desc_clean = &tu_rx_desc_init2;
E 11
I 11
			gcp->gc_rx_desc_init = &tu_rx_desc_init2;
			gcp->gc_rx_desc_clean = &tu_rx_desc_init2;
E 11
		} else {
E 10
D 11
			gc.gc_rx_desc_init = &tu_rx_desc_init1;
I 10
			gc.gc_rx_desc_clean = &tu_rx_desc_init1;
E 11
I 11
			gcp->gc_rx_desc_init = &tu_rx_desc_init1;
			gcp->gc_rx_desc_clean = &tu_rx_desc_init1;
E 11
E 10
		}

D 10
		/* work arounds */
		switch (p->chip_type) {
		case CHIP_CENTAUR:
			/* Use chaing method for tx descripor */
			gc.gc_tx_max_descs_per_pkt = gc.gc_tx_max_frags;
			gc.gc_tx_desc_write = &tu_tx_desc_write1;
			gc.gc_tx_desc_init  = &tu_tx_desc_init1;
			break;
#ifdef notdef
		case CHIP_DM9102:
			/* restrict to single fragment */
			ASSERT((p->capability & CHIP_CAP_RING) == 0);
			gc.gc_tx_max_frags = 1;
			gc.gc_tx_max_descs_per_pkt = gc.gc_tx_max_frags;
			break;
#endif
		}

E 10
D 11
		gc.gc_tx_desc_stat  = &tu_tx_desc_stat;
		gc.gc_rx_desc_stat  = &tu_rx_desc_stat;
E 11
I 11
D 28
		gcp->gc_tx_desc_stat  = &tu_tx_desc_stat;
		gcp->gc_rx_desc_stat  = &tu_rx_desc_stat;
E 28
I 28
		gcp->gc_tx_desc_stat = &tu_tx_desc_stat;
		gcp->gc_rx_desc_stat = &tu_rx_desc_stat;
E 28
I 17

E 17
E 11
D 10
		gc.gc_tx_desc_clean = &tu_tx_desc_clean;
		gc.gc_rx_desc_clean = &tu_rx_desc_clean;

E 10
		/* mii operations */
D 11
		gc.gc_mii_init   = &tu_mii_attach;
		gc.gc_mii_config = &gem_mii_config_default;
E 11
I 11
D 16
		gcp->gc_mii_init   = &tu_mii_attach;
E 16
I 16
D 26
		gcp->gc_mii_init   = &tu_mii_init;
E 26
I 26
D 28
		gcp->gc_mii_probe  = &tu_mii_probe;
		gcp->gc_mii_init   = NULL;
E 28
I 28
		gcp->gc_mii_probe = &tu_mii_probe;
		gcp->gc_mii_init = NULL;
E 28
E 26
E 16
		gcp->gc_mii_config = &gem_mii_config_default;
I 17
D 28
		gcp->gc_mii_sync   = &tu_mii_sync;
		gcp->gc_mii_read   = &tu_mii_read;
		gcp->gc_mii_write  = &tu_mii_write;
E 28
I 28
		gcp->gc_mii_sync = &tu_mii_sync;
		gcp->gc_mii_read = &tu_mii_read;
		gcp->gc_mii_write = &tu_mii_write;
E 28
		gcp->gc_mii_tune_phy = NULL;
E 17
E 11

		switch (p->chip_type) {
		case CHIP_LC82C168:
D 11
			gc.gc_mii_sync  = &tu_mii_sync_pnic;
			gc.gc_mii_read  = &tu_mii_read_pnic;
			gc.gc_mii_write = &tu_mii_write_pnic;
E 11
I 11
D 17
			gcp->gc_mii_sync  = &tu_mii_sync_pnic;
E 17
I 17
D 28
			gcp->gc_mii_sync  = &tu_mii_sync_null;
E 17
			gcp->gc_mii_read  = &tu_mii_read_pnic;
E 28
I 28
			gcp->gc_mii_sync = &tu_mii_sync_null;
			gcp->gc_mii_read = &tu_mii_read_pnic;
E 28
			gcp->gc_mii_write = &tu_mii_write_pnic;
E 11
			break;

		case CHIP_DM9102:
I 29
		case CHIP_DM9102A:
E 29
D 11
			gc.gc_mii_sync  = &tu_mii_sync_9102;
			gc.gc_mii_read  = &tu_mii_read_9102;
			gc.gc_mii_write = &tu_mii_write_9102;
E 11
I 11
D 17
			gcp->gc_mii_sync  = &tu_mii_sync_9102;
			gcp->gc_mii_read  = &tu_mii_read_9102;
E 17
			gcp->gc_mii_write = &tu_mii_write_9102;
E 11
			break;

		case CHIP_CENTAUR:
			if (p->devid == DEVID_COMET) {
				/* comet */
D 11
				gc.gc_mii_sync  = &tu_mii_sync_comet;
				gc.gc_mii_read  = &tu_mii_read_comet;
				gc.gc_mii_write = &tu_mii_write_comet;
E 11
I 11
D 17
				gcp->gc_mii_sync  = &tu_mii_sync_comet;
E 17
I 17
D 28
				gcp->gc_mii_sync  = &tu_mii_sync_null;
E 17
				gcp->gc_mii_read  = &tu_mii_read_comet;
E 28
I 28
				gcp->gc_mii_sync = &tu_mii_sync_null;
				gcp->gc_mii_read = &tu_mii_read_comet;
E 28
				gcp->gc_mii_write = &tu_mii_write_comet;
E 11
D 17
				break;
E 17
			}
D 17
			/* fall down */
		default:
D 11
			gc.gc_mii_sync  = &tu_mii_sync;
			gc.gc_mii_read  = &tu_mii_read;
			gc.gc_mii_write = &tu_mii_write;
E 11
I 11
			gcp->gc_mii_sync  = &tu_mii_sync;
			gcp->gc_mii_read  = &tu_mii_read;
			gcp->gc_mii_write = &tu_mii_write;
E 17
E 11
			break;
I 17

		case CHIP_ULI526X:
			if (revid >= 0x40) {
D 28
				gcp->gc_mii_sync  = &tu_mii_sync_null;
				gcp->gc_mii_read  = &tu_mii_read_uli;
E 28
I 28
				gcp->gc_mii_sync = &tu_mii_sync_null;
				gcp->gc_mii_read = &tu_mii_read_uli;
E 28
				gcp->gc_mii_write = &tu_mii_write_uli;
			}
			break;
E 17
		}
D 11
		gc.gc_mii_tune_phy = NULL;
E 11
I 11
D 17
		gcp->gc_mii_tune_phy = NULL;
E 17
E 11

I 29
		/* offload and jumbo frame */
		gcp->gc_max_lso = 0;
		gcp->gc_max_mtu = 1920;
		gcp->gc_default_mtu = ETHERMTU;
		gcp->gc_min_mtu = ETHERMIN - sizeof (struct ether_header);

E 29
D 28
		lp = (struct tu_dev *)
			kmem_zalloc(sizeof(struct tu_dev), KM_SLEEP);
E 28
I 28
		DPRINTF(2, (CE_CONT, "tuattach: %s%d pre gem_do_attach",
		    drv_name, unit));
E 28

D 28
		lp->hw_info  = p;
		lp->pci_cache_linesz = cache_linesz;
		lp->pci_comm = comm;
		lp->pci_revid= revid;
D 16

E 16
I 16
#ifdef CONFIG_MULTIPORT
		lp->dev_num   = dev_num;
		lp->dev_index = 0;
#endif
E 16
		ddi_set_driver_private(dip, NULL);
E 28
I 28
		dp = gem_do_attach(dip,
		    0, gcp, base, &regs_handle, lp, sizeof (*lp));
E 28

D 28
		DPRINTF(2, (CE_CONT,
			"tuattach: %s%d pre gem_do_attach", drv_name, unit));
E 28
I 28
		kmem_free(gcp, sizeof (*gcp));
E 28

D 11
		dp = gem_do_attach(dip, &gc, base, &regs_handle,
E 11
I 11
D 26
		dp = gem_do_attach(dip, gcp, base, &regs_handle,
E 26
I 26
D 28
		dp = gem_do_attach(dip, 0, gcp, base, &regs_handle,
E 26
E 11
						lp, sizeof(*lp));
I 11

		kmem_free(gcp, sizeof(*gcp));

E 28
E 11
		if (dp != NULL) {
D 28
			DPRINTF(2, (CE_CONT,
			"!%s%d: tuattach: success", drv_name, unit));
E 28
I 28
			DPRINTF(2, (CE_CONT, "!%s%d: tuattach: success",
			    drv_name, unit));
E 28
D 17
			return DDI_SUCCESS;
E 17
I 17
			return (DDI_SUCCESS);
E 17
		}
err_free_mem:
D 28
		kmem_free(lp, sizeof(struct tu_dev));
E 28
I 28
		kmem_free(lp, sizeof (struct tu_dev));
E 28
err:
I 29
		DPRINTF(2, (CE_CONT, "!%s%d: tuattach: failure",
		    drv_name, unit));
E 29
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
tudetach(dev_info_t *dip, ddi_detach_cmd_t cmd)
{
D 16
	struct gem_dev	*dp;
	struct tu_dev	*lp;

E 16
	DPRINTF(2, (CE_CONT, "tudetach: called"));

D 16
	if (cmd == DDI_DETACH) {
E 16
I 16
	switch (cmd) {
	case DDI_SUSPEND:
D 17
		return gem_suspend(dip);
E 17
I 17
		return (gem_suspend(dip));
E 17

	case DDI_DETACH:
E 16
D 17
		return gem_do_detach(dip);
E 17
I 17
		return (gem_do_detach(dip));
E 17
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
I 28
#ifdef GEM_CONFIG_GLDv3
D 29
DDI_DEFINE_STREAM_OPS(tu_ops, nulldev, nulldev, tuattach, tudetach,
    nodev, NULL, D_MP, NULL);
E 29
I 29
GEM_STREAM_OPS(tu_ops, tuattach, tudetach);
E 29
#else
E 28
static	struct module_info tuminfo = {
	0,			/* mi_idnum */
	"tu",			/* mi_idname */
	0,			/* mi_minpsz */
D 21
	ETHERMTU,		/* mi_maxpsz */
D 14
	TX_BUF_SIZE*2048,	/* mi_hiwat */
E 14
I 14
	TX_BUF_SIZE*ETHERMAX,	/* mi_hiwat */
E 21
I 21
	INFPSZ,			/* mi_maxpsz */
	64*1024,		/* mi_hiwat */
E 21
E 14
	1,			/* mi_lowat */
};

static	struct qinit turinit = {
	(int (*)()) NULL,	/* qi_putp */
	gem_rsrv,		/* qi_srvp */
	gem_open,		/* qi_qopen */
	gem_close,		/* qi_qclose */
	(int (*)()) NULL,	/* qi_qadmin */
	&tuminfo,		/* qi_minfo */
	NULL			/* qi_mstat */
};

static	struct qinit tuwinit = {
	gem_wput,		/* qi_putp */
	gem_wsrv,		/* qi_srvp */
	(int (*)()) NULL,	/* qi_qopen */
	(int (*)()) NULL,	/* qi_qclose */
	(int (*)()) NULL,	/* qi_qadmin */
	&tuminfo,		/* qi_minfo */
	NULL			/* qi_mstat */
};

static struct streamtab	tu_info = {
	&turinit,	/* st_rdinit */
	&tuwinit,	/* st_wrinit */
	NULL,		/* st_muxrinit */
	NULL		/* st_muxwrinit */
};

static	struct cb_ops cb_tu_ops = {
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
	&tu_info,	/* cb_stream */
D 17
	D_NEW|D_MP	/* cb_flag */
E 17
I 17
	D_MP,		/* cb_flag */
E 17
};

static	struct dev_ops tu_ops = {
	DEVO_REV,	/* devo_rev */
	0,		/* devo_refcnt */
	gem_getinfo,	/* devo_getinfo */
	nulldev,	/* devo_identify */
	nulldev,	/* devo_probe */
	tuattach,	/* devo_attach */
	tudetach,	/* devo_detach */
	nodev,		/* devo_reset */
	&cb_tu_ops,	/* devo_cb_ops */
	NULL,		/* devo_bus_ops */
D 17
	ddi_power	/* devo_power */
E 17
I 17
	gem_power	/* devo_power */
E 17
};
D 28

E 28
I 28
#endif /* GEM_CONFIG_GLDv3 */
E 28
static struct modldrv modldrv = {
	&mod_driverops,	/* Type of module.  This one is a driver */
	ident,
	&tu_ops,	/* driver ops */
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

	DPRINTF(2, (CE_CONT, "!tu: _init: called"));
I 17
	gem_mod_init(&tu_ops, "tu");
E 17
	status = mod_install(&modlinkage);
I 16
D 17
	if (status == 0) {
E 17
I 17
	if (status == DDI_SUCCESS) {
E 17
		mutex_init(&tu_srom_lock, NULL, MUTEX_DRIVER, NULL);
D 28
	}
I 17
	else {
E 28
I 28
	} else {
E 28
		gem_mod_fini(&tu_ops);
	}
E 17
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

	DPRINTF(2, (CE_CONT, "!tu: _fini: called"));
	status = mod_remove(&modlinkage);
I 16
D 17
	if (status == 0) {
E 17
I 17
	if (status == DDI_SUCCESS) {
E 17
		mutex_destroy(&tu_srom_lock);
I 17
		gem_mod_fini(&tu_ops);
E 17
	}

E 16
	return (status);
}

int
_info(struct modinfo *modinfop)
{
	return (mod_info(&modlinkage, modinfop));
}
E 9
