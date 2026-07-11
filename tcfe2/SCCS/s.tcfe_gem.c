h35277
s 00218/00136/02218
d D 1.7 11/09/19 23:18:48 mrym 7 6
c 2.6.0
e
s 00512/00554/01842
d D 1.6 09/03/01 23:36:20 mrym 6 5
c 2.6.0
e
s 00009/00010/02387
d D 1.5 07/09/23 06:18:02 mrym 5 4
c 2.4.0
e
s 00228/00138/02169
d D 1.4 07/02/10 11:53:15 mrym 4 3
c 2.4.0
e
s 00110/00077/02197
d D 1.3 06/12/24 23:58:32 mrym 3 2
c 2.4.0, multicast hash bit fixed
e
s 00141/00074/02133
d D 1.2 06/07/12 23:52:49 mrym 2 1
c 
e
s 02207/00000/00000
d D 1.1 06/07/11 21:57:11 mrym 1 0
c date and time created 06/07/11 21:57:11 by mrym
e
u
U
f e 0
t
T
I 1
/*
 *  tcfe: 3Com Fast Ethernet MAC driver for Solaris
 *  %W% %E%
 *
D 4
 * Copyright (c) 2006 Masayuki Murayama.  All rights reserved.
E 4
I 4
D 6
 * Copyright (c) 2006-2007 Masayuki Murayama.  All rights reserved.
E 4
 * 
E 6
I 6
D 7
 * Copyright (c) 2006-2009 Masayuki Murayama.  All rights reserved.
E 7
I 7
 * Copyright (c) 2006-2011 Masayuki Murayama.  All rights reserved.
E 7
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
/*
 Change log
E 6
I 6
#ifdef notdef
    Change log
E 6
D 3

E 3
I 3
	2006/12/24 multicast hash calculation fixed
I 4
	2007/02/10 cleanup
	2007/02/10 2.4.0
E 4
E 3
D 6
 */
E 6
I 6
#endif
E 6

/*
D 6
 TODO:
E 6
I 6
 * TODO:
E 6
 */

/*
 * System Header files.
 */
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
D 6

E 6
I 6
#include <sys/byteorder.h>
#include <sys/ethernet.h>
E 6
#include <sys/pci.h>
D 6
#include "mii.h"
E 6
I 6

#include "gem_mii.h"
E 6
#include "gem.h"
#include "3c90xreg.h"

char	ident[] = "3com 3c90x driver v" VERSION;

/* Debugging support */
#ifdef DEBUG_LEVEL
static int tcfe_debug = DEBUG_LEVEL;
D 6
#define	DPRINTF(n, args)	if (tcfe_debug>(n)) cmn_err args
E 6
I 6
#define	DPRINTF(n, args)	if (tcfe_debug > (n)) cmn_err args
E 6
#else
#define	DPRINTF(n, args)
#endif

/*
 * Useful macros and typedefs
 */
D 6
#define	ROUNDUP(x, a)	(((x) + (a) - 1) & ~((a) - 1))

D 3
#define	STRUCT_COPY(a, b)	bcopy(&(b), &(a), sizeof(a))

E 3
#if defined(sparc) || defined(sparcv9)
D 4
#define	LE32(x)	gem_le32(x)
E 4
I 4
#define	LE32(x)		ddi_swap32(x)
E 4
#else
D 4
#define	LE32(x)	(x)
E 4
I 4
#define	LE32(x)		(x)
E 4
#endif

E 6
I 6
#define	ROUNDUP(x, a)		(((x) + (a) - 1) & ~((a) - 1))
E 6
D 7
#define	EXEC_CMD(dp, cmd)	OUTW((dp), (WxCommand), (cmd))
#define	EXEC_CMD_WAIT(dp, cmd)	tcfe_exec_cmd_wait((dp), (cmd))
E 7

I 7
#define	EXEC_CMD(dp, cmd)	{ \
	mutex_enter(&((struct tcfe_dev *)(dp)->private)->cmdlock); \
	OUTW((dp), WxCommand, (cmd)); \
	mutex_exit(&((struct tcfe_dev *)(dp)->private)->cmdlock); \
}

#define	EXEC_CMD_WAIT(dp, cmd)	{ \
	mutex_enter(&((struct tcfe_dev *)(dp)->private)->cmdlock); \
	tcfe_exec_cmd_wait((dp), (cmd)); \
	mutex_exit(&((struct tcfe_dev *)(dp)->private)->cmdlock); \
}

E 7
D 4
#define	SET_WIN(dp, n)	EXEC_CMD(dp, CmdSelectRegisterWindow | (n))
E 4
I 4
#define	SET_WIN(dp, n)		EXEC_CMD(dp, CmdSelectRegisterWindow | (n))
E 4

D 4
#define	REG_LOCK(lp)	mutex_enter(&lp->reglock)
#define	REG_UNLOCK(lp)	mutex_exit(&lp->reglock)
E 4
I 4
#define	REG_LOCK(lp)		mutex_enter(&lp->reglock)
#define	REG_UNLOCK(lp)		mutex_exit(&lp->reglock)
E 4

#define	DN_LIST_SIZE_SHIFT	6
D 4
#define	DN_LIST_SIZE	(1 << DN_LIST_SIZE_SHIFT)
E 4
I 4
#define	DN_LIST_SIZE		(1 << DN_LIST_SIZE_SHIFT)
E 4
#define	MAXTXFRAGS	\
D 6
	((DN_LIST_SIZE - sizeof(uint32_t) * 2) / sizeof(struct DnFrag))
E 6
I 6
	((DN_LIST_SIZE - sizeof (uint32_t) * 2) / sizeof (struct DnFrag))
E 6

#define	UP_LIST_SIZE_SHIFT	5
D 4
#define	UP_LIST_SIZE	(1 << UP_LIST_SIZE_SHIFT)
E 4
I 4
#define	UP_LIST_SIZE		(1 << UP_LIST_SIZE_SHIFT)
E 4
#define	MAXRXFRAGS	\
D 6
	((UP_LIST_SIZE - sizeof(uint32_t) * 2) / sizeof(struct UpFrag))
E 6
I 6
	((UP_LIST_SIZE - sizeof (uint32_t) * 2) / sizeof (struct UpFrag))
E 6

/*
 * Our configuration
 */
D 6
#define	OUR_INTR_BITS \
E 6
I 6
#define	OUR_INTR_BITS	\
E 6
	(IS_hostError | IS_txComplete | IS_intRequested | \
D 6
	 IS_updateStats | IS_upComplete | IS_dnComplete | IS_interruptLatch)
E 6
I 6
	IS_updateStats | IS_upComplete | IS_dnComplete | IS_interruptLatch)
E 6

#define	TXFIFOSIZE	(2*1024)
#define	RXFIFOSIZE	(2*1024)

D 4
#define TX_RING_SIZE	256
#define RX_RING_SIZE	256
#define TX_BUF_SIZE	TX_RING_SIZE
#define RX_BUF_SIZE	RX_RING_SIZE
E 4
I 4
D 7
#ifndef TX_RING_SIZE
D 6
#  define TX_RING_SIZE	256
E 6
I 6
#define	TX_RING_SIZE	64
E 7
I 7
#ifndef TX_BUF_SIZE
#define	TX_BUF_SIZE	64
E 7
E 6
#endif
D 7
#ifndef RX_RING_SIZE
D 6
#  define RX_RING_SIZE	256
E 6
I 6
#define	RX_RING_SIZE	256
E 7
I 7
#ifndef RX_BUF_SIZE
#define	RX_BUF_SIZE	256
E 7
E 6
#endif
E 4

D 4
#define	ONESEC			(drv_usectohz(1*1000000))
E 4
I 4
D 7
#ifndef TX_BUF_SIZE
D 6
#  define TX_BUF_SIZE	TX_RING_SIZE
E 6
I 6
#define	TX_BUF_SIZE	TX_RING_SIZE
E 7
I 7
#ifndef TX_RING_SIZE
#define	TX_RING_SIZE	TX_BUF_SIZE
E 7
E 6
#endif
D 7
#ifndef RX_BUF_SIZE
D 6
#  define RX_BUF_SIZE	RX_RING_SIZE
E 6
I 6
#define	RX_BUF_SIZE	RX_RING_SIZE
E 7
I 7
#ifndef RX_RING_SIZE
#define	RX_RING_SIZE	RX_BUF_SIZE
E 7
E 6
#endif
E 4

I 4
#define	ONESEC		(drv_usectohz(1*1000000))

E 4
static int	tcfe_tx_copy_thresh = 256;
static int	tcfe_rx_copy_thresh = 256;

/*
 * Supported chips
 */
struct chip_info {
	uint16_t	venid;
	uint16_t	devid;
	char		*name;
	uint_t		flags;
#define	CHIP_TYPE	0x0007
#define	CHIP_TYPE_59X	0x0000
#define	CHIP_TYPE_90X	0x0001
#define	CHIP_TYPE_90XB	0x0002
#define	CHIP_TYPE_90XC	0x0003
#define	EEADDRSIZE_8	0x4000
#define	CHIP_CARDBUS	0x8000
	uint16_t	ee_offset;
	uint16_t	reset_opt;
};

#define	IS_3C59X(lp)	(((lp)->chip->flags & CHIP_TYPE) == CHIP_TYPE_59X)
#define	IS_3C90X(lp)	(((lp)->chip->flags & CHIP_TYPE) == CHIP_TYPE_90X)
#define	IS_3C90XB(lp)	(((lp)->chip->flags & CHIP_TYPE) == CHIP_TYPE_90XB)
#define	IS_3C90XC(lp)	(((lp)->chip->flags & CHIP_TYPE) == CHIP_TYPE_90XC)
#define	IS_3C90XB_OR_LATER(lp)	\
			(((lp)->chip->flags & CHIP_TYPE) >= CHIP_TYPE_90XB)
#define	IS_CARDBUS(lp)	(((lp)->chip->flags & CHIP_CARDBUS) != 0)

I 4
#define	ASIC_40_0502_00X(lp)	(IS_3C90XB(lp) && ((lp)->rev_id >> 5) == 0)
#define	ASIC_40_0483_00X(lp)	(IS_3C90XB(lp) && ((lp)->rev_id >> 5) == 1)
#define	ASIC_40_0476_001(lp)	(IS_3C90XB(lp) && ((lp)->rev_id >> 5) == 3)

E 4
static struct chip_info tcfe_chiptbl[] = {
#ifdef CONFIG_3C59X
D 5
 {	0x10B7, 0x5900, "3C590", CHIP_TYPE_59X, 0, 0, },
 {	0x10B7, 0x5920, "3C592", CHIP_TYPE_59X, 0, 0, },
 {	0x10B7, 0x5970, "3C597", CHIP_TYPE_59X, 0, 0, },
 {	0x10B7, 0x5950, "3C595", CHIP_TYPE_59X, 0, 0, },
 {	0x10B7, 0x5951, "3C595", CHIP_TYPE_59X, 0, 0, },
 {	0x10B7, 0x5952, "3C595", CHIP_TYPE_59X, 0, 0, },
E 5
I 5
D 6
 {	0x10b7, 0x5900, "3C590", CHIP_TYPE_59X, 0, 0, },
 {	0x10b7, 0x5920, "3C592", CHIP_TYPE_59X, 0, 0, },
 {	0x10b7, 0x5970, "3C597", CHIP_TYPE_59X, 0, 0, },
 {	0x10b7, 0x5950, "3C595", CHIP_TYPE_59X, 0, 0, },
 {	0x10b7, 0x5951, "3C595", CHIP_TYPE_59X, 0, 0, },
 {	0x10b7, 0x5952, "3C595", CHIP_TYPE_59X, 0, 0, },
E 6
I 6
	{0x10b7, 0x5900, "3C590", CHIP_TYPE_59X, 0, 0},
	{0x10b7, 0x5920, "3C592", CHIP_TYPE_59X, 0, 0},
	{0x10b7, 0x5970, "3C597", CHIP_TYPE_59X, 0, 0},
	{0x10b7, 0x5950, "3C595", CHIP_TYPE_59X, 0, 0},
	{0x10b7, 0x5951, "3C595", CHIP_TYPE_59X, 0, 0},
	{0x10b7, 0x5952, "3C595", CHIP_TYPE_59X, 0, 0},
E 6
E 5
#endif
D 6
 /* boomerang 10M */
 {	0x10b7, 0x9000, "3C900 10baseT", CHIP_TYPE_90X, 0, 0,},
 {	0x10b7, 0x9001, "3C900 10Mbps combo", CHIP_TYPE_90X, 0, 0,},
 /* cyclone 10M */
D 2
 {	0x10b7, 0x9004, "3C900 10Mbps TPO", CHIP_TYPE_90X, 0, 0,},
E 2
I 2
 {	0x10b7, 0x9004, "3C900 10Mbps TPO", CHIP_TYPE_90XB, 0, 0,},
E 2
 {	0x10b7, 0x9005, "3C900 10Mbps combo", CHIP_TYPE_90XB, 0, 0,},
D 2
 {	0x10b7, 0x9006, "3C900 10Mbps TPC", CHIP_TYPE_90XC, 0, 0,},
 {	0x10b7, 0x900a, "3C900B-FL 10base-FL", CHIP_TYPE_90XC, 0, 0,},

 /* boomrang 100M */
E 2
I 2
 /* tornade 10M */
 {	0x10b7, 0x9006, "3C900 10Mbps TPC", CHIP_TYPE_90XB, 0, 0,},
 {	0x10b7, 0x900a, "3C900B-FL 10base-FL", CHIP_TYPE_90XB, 0, 0,},
 /* boomerang 100M */
E 2
 {	0x10b7, 0x9050, "3C905 100baseTx", CHIP_TYPE_90X, 0, 0,},
 {	0x10b7, 0x9051, "3C905 100baseT4", CHIP_TYPE_90X, 0, 0,},
D 2

E 2
 /* cyclone 100M */
D 2
 {	0x10b7, 0x9055, "3C905 10/100/BNC", CHIP_TYPE_90XB, 0, 0,},
 {	0x10b7, 0x9056, "3C905-FX 100baseFx", CHIP_TYPE_90XC, 0, 0,},
E 2
I 2
 {	0x10b7, 0x9055, "3C905B 100baseTx", CHIP_TYPE_90XB, 0, 0,},
 {	0x10b7, 0x9058, "3C905B 10/100/BNC", CHIP_TYPE_90XB, 0, 0,},
 {	0x10b7, 0x905a, "3C905B-FX 100baseFx", CHIP_TYPE_90XB, 0, 0,},
E 2
 /* tornade 100M */
 {	0x10b7, 0x9200, "3C905C", CHIP_TYPE_90XC , 0, 0},
 {	0x10b7, 0x9202, "3C920B-EMB-WNM (ATI)", CHIP_TYPE_90XC , 0, 0},
 {	0x10b7, 0x9201, "3C920", CHIP_TYPE_90XC , 0, 0},
D 2
/* 980 series cyclone */
 {	0x10b7, 0x9800, "3C980", CHIP_TYPE_90XC , 0, 0},
 {	0x10b7, 0x9805, "3C980C Python", CHIP_TYPE_90XC , 0, 0},

/* cardbus 575 series */
E 2
I 2
 /* 980 series cyclone */
 {	0x10b7, 0x9800, "3C980", CHIP_TYPE_90XB , 0, 0},
 {	0x10b7, 0x9805, "3C980C Python", CHIP_TYPE_90XB , 0, 0},
 /* SOHO series tornade */
 {	0x10b7, 0x7646, "3CSOHO100-TX", CHIP_TYPE_90XC, 0, 0},
 /* mini-pci 555/556w/modem series */
D 3
 {	0x10b7, 0x5055, "3C555", 
		CHIP_TYPE_90XB | EEADDRSIZE_8,
			0x30, RO_invertMIIPwr},
E 3
I 3
 {	0x10b7, 0x5055, "3C555", CHIP_TYPE_90XB | EEADDRSIZE_8, 0x30, 0},
E 3
 {	0x10b7, 0x6055, "3C556", 
E 6
I 6
/* boomerang 10M */
	{0x10b7, 0x9000, "3C900 10baseT", CHIP_TYPE_90X, 0, 0},
	{0x10b7, 0x9001, "3C900 10Mbps combo", CHIP_TYPE_90X, 0, 0},
/* cyclone 10M */
	{0x10b7, 0x9004, "3C900 10Mbps TPO", CHIP_TYPE_90XB, 0, 0},
	{0x10b7, 0x9005, "3C900 10Mbps combo", CHIP_TYPE_90XB, 0, 0},
/* tornade 10M */
	{0x10b7, 0x9006, "3C900 10Mbps TPC", CHIP_TYPE_90XC, 0, 0},
	{0x10b7, 0x900a, "3C900B-FL 10base-FL", CHIP_TYPE_90XC, 0, 0},
/* boomerang 100M */
	{0x10b7, 0x9050, "3C905 100baseTx", CHIP_TYPE_90X, 0, 0},
	{0x10b7, 0x9051, "3C905 100baseT4", CHIP_TYPE_90X, 0, 0},
/* cyclone 100M */
	{0x10b7, 0x9055, "3C905B 100baseTx", CHIP_TYPE_90XB, 0, 0},
	{0x10b7, 0x9058, "3C905B 10/100/BNC", CHIP_TYPE_90XB, 0, 0},
	{0x10b7, 0x905a, "3C905B-FX 100baseFx", CHIP_TYPE_90XB, 0, 0},
/* tornade 100M */
	{0x10b7, 0x9200, "3C905C", CHIP_TYPE_90XC, 0, 0},
	{0x10b7, 0x9202, "3C920B-EMB-WNM (ATI)", CHIP_TYPE_90XC, 0, 0},
	{0x10b7, 0x9201, "3C920", CHIP_TYPE_90XC, 0, 0},
/* 980 series cyclone */
	{0x10b7, 0x9800, "3C980", CHIP_TYPE_90XB, 0, 0},
	{0x10b7, 0x9805, "3C980C Python", CHIP_TYPE_90XB, 0, 0},
/* SOHO series tornade */
	{0x10b7, 0x7646, "3CSOHO100-TX", CHIP_TYPE_90XC, 0, 0},
/* mini-pci 555/556w/modem series */
	{0x10b7, 0x5055, "3C555", CHIP_TYPE_90XB | EEADDRSIZE_8, 0x30, 0},
	{0x10b7, 0x6055, "3C556",
E 6
		CHIP_TYPE_90XC | CHIP_CARDBUS | EEADDRSIZE_8,
			0x30, RO_invertMIIPwr},
D 6
 {	0x10b7, 0x6056, "3C556B", 
E 6
I 6
	{0x10b7, 0x6056, "3C556B",
E 6
		CHIP_TYPE_90XC | CHIP_CARDBUS,
			0x30, RO_invertMIIPwr},
D 6
 /* cardbus 575 series */
E 2
 {	0x10b7, 0x5b57, "3C575", CHIP_TYPE_90X | EEADDRSIZE_8, 0x30, 0},
 {	0x10b7, 0x5057, "3C575", CHIP_TYPE_90X | EEADDRSIZE_8, 0x30, 0},
 {	0x10b7, 0x5157, "3C575BT",
E 6
I 6
/* cardbus 575 series */
	{0x10b7, 0x5b57, "3C575", CHIP_TYPE_90X | EEADDRSIZE_8, 0x30, 0},
	{0x10b7, 0x5057, "3C575", CHIP_TYPE_90X | EEADDRSIZE_8, 0x30, 0},
	{0x10b7, 0x5157, "3C575BT",
E 6
D 2
		CHIP_TYPE_90XC | CHIP_CARDBUS | EEADDRSIZE_8,
E 2
I 2
		CHIP_TYPE_90XB | CHIP_CARDBUS | EEADDRSIZE_8,
E 2
			0x30, RO_invertLEDPwr},
D 6
 {	0x10b7, 0x5257, "3C575CT",
E 6
I 6
	{0x10b7, 0x5257, "3C575CT",
E 6
		CHIP_TYPE_90XC | CHIP_CARDBUS | EEADDRSIZE_8,
			0x30, RO_invertMIIPwr},
D 2

E 2
I 2
D 6
 /* cardbus 656 series */
E 2
 {	0x10b7, 0x6560, "3C656", 
E 6
I 6
/* cardbus 656 series */
	{0x10b7, 0x6560, "3C656",
E 6
I 2
		CHIP_TYPE_90XB | CHIP_CARDBUS | EEADDRSIZE_8,
			0x30, RO_invertMIIPwr | RO_invertLEDPwr},
D 6
 {	0x10b7, 0x6562, "3C656B", 
E 6
I 6
	{0x10b7, 0x6562, "3C656B",
E 6
		CHIP_TYPE_90XB | CHIP_CARDBUS | EEADDRSIZE_8,
			0x30, RO_invertMIIPwr | RO_invertLEDPwr},
D 6
 {	0x10b7, 0x6564, "3C656C", 
E 6
I 6
	{0x10b7, 0x6564, "3C656C",
E 6
E 2
		CHIP_TYPE_90XC | CHIP_CARDBUS | EEADDRSIZE_8,
			0x30, RO_invertMIIPwr},
D 2
 {	0x10b7, 0x6561, "3C656B", 
		CHIP_TYPE_90XC | CHIP_CARDBUS | EEADDRSIZE_8,
			0x30, RO_invertMIIPwr},
 {	0x10b7, 0x6561, "3C656C", 
		CHIP_TYPE_90XC | CHIP_CARDBUS | EEADDRSIZE_8,
			0x30, RO_invertMIIPwr},
E 2
D 6

 {	0x10b7, 0x4500, "3C450", CHIP_TYPE_90XC , 0, 0},


E 6
I 6
	{0x10b7, 0x4500, "3C450", CHIP_TYPE_90XC, 0, 0},
E 6
/* tornade chipset */
D 6
 {	0x10b7, 0x1201, "3C982", CHIP_TYPE_90XC , 0, 0},
 {	0x10b7, 0x1202, "3C982", CHIP_TYPE_90XC , 0, 0},
 {	0x10b7, 0x9056, "3C905BT4", CHIP_TYPE_90XC , 0, 0},
 {	0x10b7, 0x9210, "3C920B-EMB-WNM", CHIP_TYPE_90XC , 0, 0},
D 2

/* cyclone chipset  must be last */
E 2
 {	0xffff, 0xffff, "unknown 3com chipset", CHIP_TYPE_90XC, 0, },
E 6
I 6
	{0x10b7, 0x1201, "3C982", CHIP_TYPE_90XC, 0, 0},
	{0x10b7, 0x1202, "3C982", CHIP_TYPE_90XC, 0, 0},
	{0x10b7, 0x9056, "3C905BT4", CHIP_TYPE_90XC, 0, 0},
	{0x10b7, 0x9210, "3C920B-EMB-WNM", CHIP_TYPE_90XC, 0, 0},
	{0xffff, 0xffff, "unknown 3com chipset", CHIP_TYPE_90XC, 0},
E 6
};
D 6
#define CHIPTABLESIZE   (sizeof(tcfe_chiptbl)/sizeof(struct chip_info))
E 6
I 6
#define	CHIPTABLESIZE   (sizeof (tcfe_chiptbl)/sizeof (struct chip_info))
E 6

struct tcfe_dev {
	uint8_t			rev_id;
	struct chip_info	*chip;

	kmutex_t		reglock;
I 7
	kmutex_t		cmdlock;
E 7

	boolean_t		dnlistptr_loaded;
	uint32_t		intenable;

	/* cardbus staff */
	ddi_acc_handle_t	base2_ha;
	void			*base2;

	/* configuration */
	int			media;
	uint16_t		bmcr;
	uint16_t		bmsr;
	uint16_t		adv;

	/* polling mode */
#ifdef GEM_CONFIG_POLLING
	int			last_poll_interval;
#endif
I 3
	/* multicast hash */
	uint8_t			mhash[256/8];
I 4

	/* rx list mngt */
	int			rx_last_slot;

	/* global error recovery */
	boolean_t		need_to_reset;
I 6

	/* configuration */
	uint_t			ic;	/* internal config */
	uint_t			ms;	/* media status */
	boolean_t		mii_initialized;
I 7

	uint_t			tx_last_slot;
E 7
E 6
E 4
E 3
};

/* ======================================================== */
D 6
 
E 6
I 6

E 6
/* mii operations */
static void  tcfe_mii_sync(struct gem_dev *);
static uint16_t  tcfe_mii_read(struct gem_dev *, uint_t);
static void tcfe_mii_write(struct gem_dev *, uint_t, uint16_t);

/* nic operations */
static int tcfe_reset_chip(struct gem_dev *);
static int tcfe_attach_chip(struct gem_dev *);
D 3
static void tcfe_init_chip(struct gem_dev *);
static void tcfe_start_chip(struct gem_dev *);
E 3
I 3
static int tcfe_init_chip(struct gem_dev *);
static int tcfe_start_chip(struct gem_dev *);
E 3
static int tcfe_stop_chip(struct gem_dev *);
D 3
static void tcfe_set_media(struct gem_dev *);
static void tcfe_set_rx_filter(struct gem_dev *);
static void tcfe_get_stats(struct gem_dev *);
E 3
I 3
static int tcfe_set_media(struct gem_dev *);
static int tcfe_set_rx_filter(struct gem_dev *);
static int tcfe_get_stats(struct gem_dev *);
E 3

/* descriptor operations */
static int tcfe_tx_desc_write(struct gem_dev *dp, int slot,
D 6
		    ddi_dma_cookie_t *dmacookie, int frags, uint32_t flag);
E 6
I 6
    ddi_dma_cookie_t *dmacookie, int frags, uint64_t flag);
E 6
static void tcfe_rx_desc_write(struct gem_dev *dp, int slot,
D 6
		    ddi_dma_cookie_t *dmacookie, int frags);
E 6
I 6
    ddi_dma_cookie_t *dmacookie, int frags);
E 6
static void tcfe_tx_start(struct gem_dev *dp, int slot, int nslot);
static void tcfe_rx_start(struct gem_dev *dp, int slot, int nslot);
static uint_t tcfe_tx_desc_stat(struct gem_dev *dp, int slot, int ndesc);
static uint64_t tcfe_rx_desc_stat(struct gem_dev *dp, int slot, int ndesc);

static void tcfe_tx_desc_init(struct gem_dev *dp, int slot);
static void tcfe_rx_desc_init(struct gem_dev *dp, int slot);
static void tcfe_tx_desc_clean(struct gem_dev *dp, int slot);
static void tcfe_rx_desc_clean(struct gem_dev *dp, int slot);

/* interrupt handler */
D 6
static u_int tcfe_interrupt(struct gem_dev *dp);
E 6
I 6
static uint_t tcfe_interrupt(struct gem_dev *dp);
E 6

/* ======================================================== */

/* mapping attributes */
/* Data access requirements. */
static struct ddi_device_acc_attr tcfe_dev_attr = {
	DDI_DEVICE_ATTR_V0,
	DDI_STRUCTURE_LE_ACC,
	DDI_STRICTORDER_ACC
};

D 4
/* On sparc, the buffers should be native endianness */
E 4
I 4
/* Tx and rx buffers should have native endianness for sparc platforms. */
E 4
static struct ddi_device_acc_attr tcfe_buf_attr = {
	DDI_DEVICE_ATTR_V0,
	DDI_NEVERSWAP_ACC,	/* native endianness */
	DDI_STRICTORDER_ACC
};

I 7
#define	TCFE_MAX_PACKET_SIZE	(0x1fff * (min(MAXRXFRAGS, MAXTXFRAGS) - 2) + 2)
E 7
static ddi_dma_attr_t tcfe_dma_attr_buf = {
	DMA_ATTR_V0,		/* dma_attr_version */
	0,			/* dma_attr_addr_lo */
	0xffffffffull,		/* dma_attr_addr_hi */
D 5
	0x1fffull,		/* dma_attr_count_max */
E 5
I 5
D 6
	0x3fffull,		/* dma_attr_count_max */
E 6
I 6
D 7
	0x7ffull,		/* dma_attr_count_max */
E 7
I 7
	0x1fffull,		/* dma_attr_count_max */
E 7
E 6
E 5
	1,			/* dma_attr_align */
	0xffffffff,		/* dma_attr_burstsizes */
	1,			/* dma_attr_minxfer */
D 5
	0x1fff,			/* dma_attr_maxxfer */
E 5
I 5
D 6
	0x3fff,			/* dma_attr_maxxfer */
E 6
I 6
D 7
	0x7ff,			/* dma_attr_maxxfer */
E 7
I 7
	TCFE_MAX_PACKET_SIZE,	/* dma_attr_maxxfer */
E 7
E 6
E 5
	0xffffffffull,		/* dma_attr_seg */
D 6
	0,/* patched later */	/* dma_attr_sgllen */
E 6
I 6
	0, /* patched later */	/* dma_attr_sgllen */
E 6
	1,			/* dma_attr_granular */
	0			/* dma_attr_flags */
};

static ddi_dma_attr_t tcfe_dma_attr_desc = {
	DMA_ATTR_V0,		/* dma_attr_version */
	16,			/* dma_attr_addr_lo */
	0xffffffffull,		/* dma_attr_addr_hi */
	0xffffffffull,		/* dma_attr_count_max */
	16,			/* dma_attr_align */
	0xffffffff,		/* dma_attr_burstsizes */
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
static void
tcfe_exec_cmd_wait(struct gem_dev *dp, int cmd)
{
	int		i;
D 6
	struct tcfe_dev	*lp = (struct tcfe_dev *)dp->private;
E 6
I 6
	struct tcfe_dev	*lp = dp->private;
E 6

D 7
	ASSERT(mutex_owned(&lp->reglock));
E 7
I 7
	OUTW(dp, WxCommand, cmd);
E 7

D 7
	EXEC_CMD(dp, cmd);

D 6
	for (i = 0; (INW(dp, WxIntStatus) & IS_cmdInProgress) != 0; i++) {
E 6
I 6
	for (i = 0; (INW(dp, WxIntStatus) & IS_cmdInProgress); i++) {
E 7
I 7
	for (i = 0; INW(dp, WxIntStatus) & IS_cmdInProgress; i++) {
E 7
E 6
		if (i > 200) {
			cmn_err(CE_WARN,
D 6
				"%s: cmd timeout error: cmd:0x%04",
			       dp->name, cmd);
E 6
I 6
			    "%s: cmd timeout error: cmd:0x%04",
			    dp->name, cmd);
E 6
I 4
			lp->need_to_reset = B_TRUE;
E 4
			break;
		}
		drv_usecwait(10);
	}
}

static int
tcfe_reset_chip(struct gem_dev *dp)
{
D 6
	int		i;
E 6
I 6
	int	i;
E 6
	uint32_t	val;
D 6
	struct tcfe_dev	*lp = (struct tcfe_dev *)dp->private;
E 6
I 6
	struct tcfe_dev	*lp = dp->private;
E 6

D 7
	REG_LOCK(lp);
D 6
#ifdef NEVER
	EXEC_CMD_WAIT(dp, CmdGlobalReset | 0xff);
	delay(drv_usectohz(10000));
#endif
E 6
I 6

E 7
	if (!lp->mii_initialized) {
		EXEC_CMD_WAIT(dp, CmdGlobalReset);
		delay(drv_usectohz(10000));
	}

E 6
	if (IS_CARDBUS(lp)) {
I 7
		REG_LOCK(lp);

E 7
		SET_WIN(dp, 2);
		val = INW(dp, W2ResetOptions) &
D 6
				~(RO_invertLEDPwr | RO_invertMIIPwr);
E 6
I 6
		    ~(RO_invertLEDPwr | RO_invertMIIPwr);
E 6
D 3
#ifdef NEVER
		val = 0;
#endif
E 3
		OUTW(dp, W2ResetOptions, val | lp->chip->reset_opt);
I 7

		REG_UNLOCK(lp);

E 7
D 4

E 4
I 4
		DPRINTF(0, (CE_CONT, "%s: %s reset option:%b",
D 6
			dp->name, __func__, val, ResetOptionsBits));
E 6
I 6
		    dp->name, __func__, val, ResetOptionsBits));
E 6
E 4
		/* enable cardbus interrupt */
		ddi_put32(lp->base2_ha,
D 4
			(uint32_t *)(((caddr_t) lp->base2) + 4), 0x8000);
E 4
I 4
D 6
			(uint32_t *)(((caddr_t) lp->base2) + 4), 0x8000); /*X*/
E 6
I 6
		    (void *)(((caddr_t)lp->base2) + 4), 0x8000); /* X */
E 6

		/*
		 * XXX - need to enable tranceiver power by writing
D 6
		 * 0x0800 into reg 0 in window 0?
E 6
I 6
		 * 0x0800 into reg 0 in window 0
E 6
		 */
E 4
	}
I 2

	/* Reset transmitter */
	EXEC_CMD_WAIT(dp, CmdTxReset);
I 4
D 5
	EXEC_CMD_WAIT(dp, CmdTxReset);
E 5
E 4

	/* Reset receiver */
	EXEC_CMD_WAIT(dp, CmdRxReset);

E 2
D 7
	REG_UNLOCK(lp);

E 7
I 4
	lp->need_to_reset = B_FALSE;

E 4
	return (GEM_SUCCESS);
}

D 3
static void
E 3
I 3
static int
E 3
tcfe_init_chip(struct gem_dev *dp)
{
D 6
	int		i;
E 6
I 6
	int	i;
E 6
D 4
	int		pktsize;
E 4
	uint32_t	val;
I 4
D 6
	int		pktsize;
E 4
	struct tcfe_dev	*lp = (struct tcfe_dev *)dp->private;
E 6
I 6
	int	pktsize;
	struct tcfe_dev	*lp = dp->private;
E 6

	DPRINTF(1, (CE_CONT, "!%s: %s: called", dp->name, __func__));

D 6
	pktsize = sizeof(struct ether_header) + 4 + dp->mtu;
E 6
I 6
	pktsize = sizeof (struct ether_header) + 4 + dp->mtu;
E 6

D 7
	REG_LOCK(lp);

E 7
D 2
	/* Reset transmitter */
	EXEC_CMD_WAIT(dp, CmdTxReset);

	/* Reset receiver */
	EXEC_CMD_WAIT(dp, CmdRxReset);

E 2
	/* Set InterruptMask */
	lp->intenable = 0;
	EXEC_CMD(dp, CmdSetInterruptEnable | lp->intenable);
	EXEC_CMD(dp, CmdAcknowledgeInterrupt | AllAck);

	/* Set IndicationEnable */
	EXEC_CMD(dp, CmdSetIndicationEnable | AllIndications);

	/* setup transmitter */
	EXEC_CMD_WAIT(dp, CmdSetTxStartThresh |
D 6
		min(TxStartThreshMask, dp->txthr / TxStartThreshUnit));
E 6
I 6
	    min(TxStartThreshMask, dp->txthr / TxStartThreshUnit));
E 6

	if (IS_3C90XB_OR_LATER(lp)) {
		/* XXX - use default */
		EXEC_CMD(dp, CmdSetTxReclaimThresh | 8);
	}

	/* setup rx */
D 4
	val = (pktsize + ETHERFCSL + RxEarlyThreshUnit - 1) / RxEarlyThreshUnit;
E 4
I 4
	val = ROUNDUP(pktsize, RxEarlyThreshUnit) / RxEarlyThreshUnit;
E 4
	EXEC_CMD(dp, CmdSetRxEarlyThresh | min(RxEarlyThreshMask, val));

	/* common and extended registers */

	/* WxTxPktId 0x18 90xB ro */
	/* WxTimer		0x1a */
	/* WxTxStatus		0x1b */
	/* WxIntStatus_1e	0x1e */
	/* WxIntStatusAuto	0x1e */
	/* WxCommand_1e		0x1e */
	/* WxDmaCtrl		0x20 */
	val = INL(dp, WxDmaCtrl);
	val |= DC_upRxEarlyEnable;	/* rw */
	val |= DC_counterSpeed;		/* rw 0:3.2uS, 1:320nS */
D 6
	val &= ~DC_countdownMode;	/* rw 0:from now, 1:from intr*/
E 6
I 6
	val &= ~DC_countdownMode;	/* rw 0:from now, 1:from intr */
E 6
	if (IS_3C90XB_OR_LATER(lp)) {
		val &= ~DC_upAltSeqDisable;	/* rw 90xB/C */
		val &= ~DC_defeatMWI;		/* rw 90xB/C */
		val &= ~DC_defeatMRL;		/* rw 90xB/C */
		val &= ~DC_upOverDiscDisable;	/* rw 90xB/C */
	}
	OUTL(dp, WxDmaCtrl, val);

	/* WxDnListPtr 0x24 */
I 4
	EXEC_CMD_WAIT(dp, CmdDnStall);
E 4
	OUTL(dp, WxDnListPtr, 0);
	lp->dnlistptr_loaded = B_FALSE;

	/* WxDnBurstThresh 0x2a 90XB/C */
	if (IS_3C90XB_OR_LATER(lp)) {
		val = dp->txmaxdma/DnBurstThreshUnit;
		val = max(1, min(val, DnBurstThreshMask));
		OUTB(dp, WxDnBurstThresh, val);
	}

	/* WxDnPriorityThreash 0x2c */
	if (IS_3C90XB_OR_LATER(lp)) {
		val = TXFIFOSIZE/8/DnPriorityThreshUnit;
		val = max(1, min(val, DnPriorityThreshMask));
		OUTB(dp, WxDnPriorityThresh, val);
	}

	/* WxDnPoll 0x2d */
D 4
#if defined(CONFIG_DNPOLL)
E 4
	if (IS_3C90XB_OR_LATER(lp)) {
I 4
D 7
#ifdef TEST_BOOMERANG
		OUTB(dp, WxDnPoll, 0);
#else
E 7
I 7
#ifdef CONFIG_TX_AUTO_POLL
E 7
E 4
D 6
		OUTB(dp, WxDnPoll, 0x7f);
E 6
I 6
		OUTB(dp, WxDnPoll, 0x7f);	/* in 320uS */
I 7
#else
		OUTB(dp, WxDnPoll, 0);
E 7
E 6
D 4
	}
E 4
#endif
D 4
	/* WxTxFreeThresh 0x2f	only 90x */
E 4
I 4
	}
	/* WxTxFreeThresh 0x2f (3c90x) */
E 4
	if (IS_3C90X(lp)) {
		/*
		 * XXX - 3C90X nics must have enough space in tx fifo
		 * when it starts DMAing a packet, otherwise it may
		 * hang frequently during downloading.
		 */
D 4
		val = pktsize / TxFreeThreshUnit;
E 4
I 4
		val = ROUNDUP(pktsize, TxFreeThreshUnit) / TxFreeThreshUnit;
E 4
		OUTB(dp, WxTxFreeThresh, min(TxFreeThreshMask, val));
	}

	/* WxUpPktStatus 0x30, ro */
	/* WxFreeTimer 0x34 */
	/* WxCountdown 0x36, stop */
	OUTW(dp, WxCountdown, 0);

D 4
	/* WxUpListPtr 0x38 */
D 3
#ifdef notdef
E 3
I 3
#ifdef NEVER
E 4
E 3
	/*
D 2
	 * XXX - we cannot setup UpListPtr here because the upload dma engine
E 2
I 2
D 3
	 * XXX - we cannot setup UpListPtr here because upload dma engine
E 2
	 * will start as soon as  we write a non-zero value.
E 3
I 3
D 4
	 * XXX - we cannot setup UpListPtr here, because upload dma engine
	 * will start as soon as we write a non-zero value.
E 4
I 4
	 * WxUpListPtr 0x38
E 4
E 3
	 */
	EXEC_CMD_WAIT(dp, CmdUpStall);
D 6
	OUTL(dp, WxUpListPtr, (uint32_t) dp->rx_ring_dma);
D 4
#endif
E 4
I 4

E 6
I 6
D 7
#if 0
	OUTL(dp, WxUpListPtr, (uint32_t)dp->rx_ring_dma);
#endif
E 7
I 7

E 7
E 6
E 4
	/* WxUnPriorityThreash 0x3c */
	if (IS_3C90XB_OR_LATER(lp)) {
D 4
		val = RXFIFOSIZE/8/UpPriorityThreshUnit;
E 4
I 4
		val = (RXFIFOSIZE/8)/UpPriorityThreshUnit;
E 4
		val = max(1, min(val, UpPriorityThreshMask));
		OUTB(dp, WxUpPriorityThresh, val);
	}

	/* WxUpPoll 0x3d */
	if (IS_3C90XB_OR_LATER(lp)) {
I 4
D 7
#ifdef TEST_BOOMERANG
		OUTB(dp, WxUpPoll, 0);
#else
E 7
I 7
#ifdef CONFIG_RX_AUTO_POLL
E 7
E 4
		OUTB(dp, WxUpPoll, 0x7f);
I 7
#else
		OUTB(dp, WxUpPoll, 0);
E 7
I 4
#endif
E 4
	}

	/* WxUpBurstThresh 0x3e */
	if (IS_3C90XB_OR_LATER(lp)) {
		val = dp->rxmaxdma/UpBurstThreshUnit;
		val = max(1, min(val, UpBurstThreshMask));
		OUTB(dp, WxUpBurstThresh, val);
	}

	/* WxRealTimeCnt 0x40 */
	/* WxDebugData 0x70 */
	/* WxDebugControl 0x74 */
	/* WxDnMaxBurst 0x78, rw, no need to setup */
	/* WxPowerMgmtCtrl 0x7a */

I 7
	REG_LOCK(lp);

E 7
	/* Window 0 */
	SET_WIN(dp, 0);
	/* W0EepromCommand:0xa, nothing */
D 6
	/* W0EepromData:0xc, nothing*/
E 6
I 6
	/* W0EepromData:0xc, nothing */
E 6

	/* Window 1 */
	SET_WIN(dp, 1);
	/* XXX - all registers in window 1 are obsolute */

	/* Window 2 */
	SET_WIN(dp, 2);
	/* W2StationAddress 0x0, set in set_rx_filter */
	/* W2StationMask 0x6 */
	for (i = 0; i < ETHERADDRL; i += 2) {
		OUTW(dp, W2StationMask + i, 0);
	}
	/* W2ResetOptions 0xc (90xB/C) */
D 2
	/* XXX - ResetOptions register will be configured in reset_chip. */
E 2
I 2
D 4
	/* XXX - ResetOptions register is configured in mii_init. */
E 4
I 4
	/* XXX - ResetOptions register will be configured in mii_init. */
E 4
E 2

	/* Window 3 */
	SET_WIN(dp, 3);
	/* W3InternalConfig offset 0x0 dw, set in reset_chip */
	/* W3MaxPktSize 0x4 w 90XB/C */
	if (IS_3C90XB_OR_LATER(lp)) {
D 4
		OUTW(dp, W3MaxPktSize, sizeof(struct ether_header) + dp->mtu);
E 4
I 4
		OUTW(dp, W3MaxPktSize,
D 6
			sizeof(struct ether_header) + 4 + dp->mtu);
E 6
I 6
		    sizeof (struct ether_header) + 4 + dp->mtu);
E 6
E 4
	}

	/* W3MacControl 0x6 word */
	val = INW(dp, W3MacControl);
D 4
	val |= MC_allowLargePackets;
E 4
I 4
	if (IS_3C90X(lp)) {
		val |= MC_allowLargePackets;
	}
E 4
D 3
	if (IS_3C90XB_OR_LATER(lp)) {
E 3
#ifdef NEVER
D 3
		val |= MC_vltEnable; /* 3com propriaty vlan tagging for 90xB */
#endif
E 3
I 3
	if (IS_3C90XB_OR_LATER(lp)) {
		/* we don't use 3com vlan tagging. */
		val |= MC_vltEnable;
E 3
	}
I 3
#endif
E 3
	OUTW(dp, W3MacControl, val);

	/* W3ResetOptions_old 0x8 w, obsolute, 90x */
	/* W3MediaOptions 0x8 w, will be refered in mii_init */
	/* W3RxFree 0xa	w ro */
	/* W3TxFree 0xc	w ro */

	/* Window 4 */
	SET_WIN(dp, 4);
	/* W4FifoDiagnostic 0x4	*/
	/* W4NetworkDiagnostic 0x6 */
	OUTW(dp, W4NetworkDiagnostic,
D 6
		INW(dp, W4NetworkDiagnostic) | ND_upperBytesEnable);
E 6
I 6
	    INW(dp, W4NetworkDiagnostic) | ND_upperBytesEnable);
E 6

	/* W4PhysicalMgmt 0x8, do nothing */
D 4
	/* W4MediaStatus 0xa */
I 2
#ifdef notdef
I 3
	/* XXX - moved to txfe_mii_init() */
E 3
E 2
	val = INW(dp, W4MediaStatus);
	val &= ~MS_enableSqeStats;
	val &= ~MS_jabberGuardEnable;
	val &= ~MS_linkBeatEnale;
	OUTW(dp, W4MediaStatus, val);
D 2

E 2
I 2
#endif
E 4
I 4
	/* W4MediaStatus 0xa, configured in mii_init */
E 4
E 2
	/* W4BadSSD 0xc */
	/* W4UpperBytesOk 0xd, do nothing */

	/* Window 5 */
	SET_WIN(dp, 5);
	/* no registers to manupilate in window 5 */

	/* Window 7 */
	SET_WIN(dp, 7);
D 3
	OUTW(dp, W7VlanEtherType, 0x8100);	/* setup TPID */
E 3
I 3
	if (IS_3C90XB_OR_LATER(lp)) {
		OUTW(dp, W7VlanEtherType, 0x8100);	/* setup TPID */
	}
E 3

I 7
	REG_UNLOCK(lp);

E 7
I 3
	if (IS_3C90XB_OR_LATER(lp)) {
I 4
		int	hashsize = ASIC_40_0502_00X(lp) ? 64 : 256;
E 4
		/* clear entire multicast hash table */
D 4
		for (i = 0; i < 256; i++) {
E 4
I 4
		for (i = 0; i < hashsize; i++) {
E 4
			EXEC_CMD(dp, CmdSetHashFilterBits | i);
		}
D 6
		bzero(&lp->mhash[0], sizeof(lp->mhash));
E 6
I 6
		bzero(&lp->mhash[0], sizeof (lp->mhash));
E 6
	}

E 3
D 4
	/* End of initialization */
E 4
I 4
	/* end of hardware initialization */
E 4
D 7
	REG_UNLOCK(lp);
E 7

#ifdef GEM_CONFIG_POLLING
	lp->last_poll_interval = 0;
#endif
I 4
	lp->rx_last_slot = 0;
I 7
	lp->tx_last_slot = 0;
E 7
E 4
I 3

	return (GEM_SUCCESS);
E 3
}

static uint32_t
tcfe_mcast_hash(struct gem_dev *dp, uint8_t *addr)
{
D 3
	/* only several bits of LSB is valid */
	return (gem_ether_crc_be(addr, ETHERADDRL));
E 3
I 3
D 4
	/* only 8bits of LSB are valid */
	return (gem_ether_crc_be(addr, ETHERADDRL) & 0xff);
E 4
I 4
	return (gem_ether_crc_be(addr, ETHERADDRL));
E 4
E 3
}

D 3
static void
E 3
I 3
static int
E 3
D 6
tcfe_set_rx_filter(struct gem_dev *dp)	
E 6
I 6
tcfe_set_rx_filter(struct gem_dev *dp)
E 6
{
	int		i;
	uint8_t		*mac;
D 3
	uint64_t	mhash[4] = {0, 0, 0, 0};
	uint_t		hashmask = 0;
E 3
I 3
	uint8_t		mhash[256/8];
E 3
	uint16_t	operand;
D 3
	int		hashlimit = 0;
E 3
I 3
D 4
	int		hashlimit;
E 4
I 4
	int		hashsize;
	uint_t		h;
E 4
E 3
D 6
	struct tcfe_dev	*lp = (struct tcfe_dev *)dp->private;
E 6
I 6
	struct tcfe_dev	*lp = dp->private;
E 6

I 3
#if DEBUG_LEVEL > 3
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
		    "!%s: adding mcast(%d)"
		    " %02x:%02x:%02x:%02x:%02x:%02x",
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

E 3
	/* Normal RX operation mode */
I 3
D 4
	hashlimit = 0;
E 4
E 3
	operand = rxFilterIndividual | rxFilterBroadcast;
I 3

E 3
D 2
	if (IS_3C90XB(lp)) {
E 2
I 2
	if (IS_3C90XB_OR_LATER(lp)) {
E 2
D 3
		hashlimit = (1 << 8) / 2;
		hashmask  = (1 << 8) - 1;
E 3
I 3
D 4
		/* we can use a 256bit-width hardware multicast filter */
		hashlimit = 256 / 2;
		bzero(mhash, sizeof(mhash));
E 4
I 4
D 6
		/* we can use a 64/256bit-width hardware multicast filter */
E 6
I 6
		/* we can use a 64 or 256bit-width hardware multicast filter */
E 6
		hashsize = ASIC_40_0502_00X(lp) ? 64 : 256;
		bzero(mhash, hashsize/8);
E 4
E 3
D 6
	}
I 4
	else {
E 6
I 6
	} else {
E 6
		hashsize = 0;
	}
E 4

	if ((dp->rxmode & RXMODE_ENABLE) == 0) {
		operand = 0;
D 6
	}
	else if ((dp->rxmode & RXMODE_PROMISC) != 0) {
E 6
I 6
	} else if (dp->rxmode & RXMODE_PROMISC) {
E 6
		/* Promiscous mode */
D 3
		operand |=  rxFilterAllMulticast | rxFilterPromiscuous;
E 3
I 3
		operand |= rxFilterAllMulticast | rxFilterPromiscuous;
E 3
D 6
	}
D 4
	else if (dp->mc_count > hashlimit ||
E 4
I 4
	else if (dp->mc_count > hashsize/2 ||
E 4
			(dp->rxmode & RXMODE_ALLMULTI) != 0) {
E 6
I 6
	} else if (dp->mc_count > hashsize / 2 ||
	    (dp->rxmode & RXMODE_ALLMULTI)) {
E 6
		/* All Multicast mode */
		operand |= rxFilterAllMulticast;
D 6
	}
	else if (dp->mc_count > 0) {
E 6
I 6
	} else if (dp->mc_count > 0) {
E 6
		/*
		 * make hash table to select interresting
		 * multicast address only.
		 */
I 3
		operand |= rxFilterMulticastHash;
E 3
		for (i = 0; i < dp->mc_count; i++) {
D 3
			/* hash table is 64 = 2^6 bit width */
			uint64_t	h;
			h = (long) (dp->mc_list[i].hash) & hashmask;
D 2
			mhash[h/64] |= 1 << (h % 64);
E 2
I 2
			mhash[h/64] |= 1ull << (h % 64);
E 3
I 3
D 4
			int	h;
			h = dp->mc_list[i].hash;
			mhash[h / 8] |= 1ull << (h % 8);
E 4
I 4
			h = dp->mc_list[i].hash & (hashsize - 1);
			mhash[h / 8] |= 1 << (h % 8);
E 4
E 3
E 2
		}
	}

	REG_LOCK(lp);
	SET_WIN(dp, 2);
	mac = &dp->cur_addr.ether_addr_octet[0];
	for (i = 0; i < ETHERADDRL; i += 2) {
D 7
		OUTW(dp, W2StationAddress + i, (mac[i + 1] << 8) | mac[i]);
E 7
I 7
		OUTW(dp, W2StationAddress + i, mac[i + 1] << 8 | mac[i]);
E 7
	}
I 7
	REG_UNLOCK(lp);
E 7

D 4
	if (hashlimit > 0) {
E 4
I 4
	if (hashsize > 0) {
E 4
I 3
		/* update hardware multicast hash filter */
E 3
D 4
		for (i = 0; i < 256; i++) {
D 3
			EXEC_CMD(dp, CmdSetHashFilterBits |
				(mhash[i/64] & (1ull << (i%64)) ? 0x0400 : 0) |
				i);
E 3
I 3
			if (((lp->mhash[i/8] ^ mhash[i/8]) &
					(1 << (i%8))) == 0) {
				/* no need to change the hash bit */
E 4
I 4
		for (i = 0; i < hashsize; i++) {
			h = (mhash[i/8] >> (i%8)) & 1;

			if (((lp->mhash[i/8] >> (i%8)) & 1) == h) {
				/* no need to change the bit in hash filter */
E 4
				continue;
			}
D 4
			EXEC_CMD(dp,
				CmdSetHashFilterBits |
				(mhash[i/8] & (1 << (i%8)) ? 0x0400 : 0) | i);
E 4
I 4

D 7
			EXEC_CMD(dp, CmdSetHashFilterBits | (h << 10) | i);
E 7
I 7
			EXEC_CMD(dp, CmdSetHashFilterBits | h << 10 | i);
E 7
E 4
E 3
		}
I 3
D 4
		bcopy(&mhash[0], &lp->mhash[0], sizeof(lp->mhash));
E 4
I 4
		bcopy(&mhash[0], &lp->mhash[0], hashsize/8);
E 4
E 3
	}

	EXEC_CMD(dp, CmdSetRxFilter | operand);

D 7
	REG_UNLOCK(lp);
I 3

E 7
	return (GEM_SUCCESS);
E 3
}

D 3
static void
E 3
I 3
static int
E 3
tcfe_set_media(struct gem_dev *dp)
{
	uint16_t	old;
	uint16_t	new;
I 7
	uint32_t	ic;
E 7
D 6
	struct tcfe_dev	*lp = (struct tcfe_dev *)dp->private;
E 6
I 6
	struct tcfe_dev	*lp = dp->private;
I 7
	extern int	gem_speed_value[];
E 7
E 6

I 7
	DPRINTF(0, (CE_CONT, "!%s: %s speed:%d duplex:%s",
	    dp->name, __func__,
	    gem_speed_value[dp->speed],
	    dp->full_duplex ? "full" : "half"));

E 7
	REG_LOCK(lp);
	SET_WIN(dp, 3);

	old = INW(dp, W3MacControl);
	new = old & ~(MC_fullDuplexEnable | MC_flowControlEnable);

	/* duplex mode */
	if (dp->full_duplex) {
		new |= MC_fullDuplexEnable;
	}

	/* flow control */
D 6
	if(dp->flow_control == FLOW_CONTROL_SYMMETRIC) {
E 6
I 6
	if (dp->flow_control == FLOW_CONTROL_SYMMETRIC) {
E 6
		new |= MC_flowControlEnable;
	}

	if (new != old) {
		OUTW(dp, W3MacControl, new);
I 2
D 7
#ifdef notdef
		if (dp->mac_active) {
			/* XXX -- reset rx and tx here */
			EXEC_CMD_WAIT(dp, CmdTxReset);
			EXEC_CMD_WAIT(dp, CmdRxReset);

			drv_usecwait(2000);

			EXEC_CMD(dp, CmdTxEnable);
			EXEC_CMD(dp, CmdRxEnable);
E 7
I 7
	}
#ifdef WA_905B_10M
	if (lp->media == xcvrSelectAN) {
		/* fix tranceiver selection */
		ic = INL(dp, W3InternalConfig) & ~IC_xcvrSelect;
		if (dp->speed == GEM_SPD_100) {
			ic |= xcvrSelect100BASETX << IC_xcvrSelectShift;
		} else {
			ic |= xcvrSelect10BASET << IC_xcvrSelectShift;
E 7
		}
D 7
#endif
E 7
I 7
		OUTL(dp, W3InternalConfig, ic);
E 7
E 2
	}
D 6

E 6
I 6
D 7
#ifdef notdef
	OUTL(dp, WxUpListPtr, (uint32_t)dp->rx_ring_dma);
E 7
#endif
E 6
	REG_UNLOCK(lp);
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
tcfe_start_chip(struct gem_dev *dp)
{
D 6
	struct tcfe_dev	*lp = (struct tcfe_dev *)dp->private;
E 6
I 6
	struct tcfe_dev	*lp = dp->private;
E 6

	ASSERT(mutex_owned(&dp->intrlock));

D 7
	REG_LOCK(lp);

E 7
	/* Enable statistics */
	EXEC_CMD(dp, CmdStatisticsEnable);

	/* Enable interrupts */
	lp->intenable = OUR_INTR_BITS;
	EXEC_CMD(dp, CmdSetInterruptEnable | lp->intenable);

	/* Enable transmitter */
	EXEC_CMD(dp, CmdTxEnable);

	/* Enable receiver */
	EXEC_CMD(dp, CmdRxEnable);

I 4
	/* Start Dnload DMA engine */
	EXEC_CMD(dp, CmdDnUnstall);
D 6

E 6
I 6
D 7
#if 1
E 7
I 7

E 7
E 6
E 4
	/* Start Upload DMA engine */
D 6
	OUTL(dp, WxUpListPtr, (uint32_t) dp->rx_ring_dma);
E 6
I 6
	OUTL(dp, WxUpListPtr, (uint32_t)dp->rx_ring_dma);
E 6
I 4
	EXEC_CMD(dp, CmdUpUnstall);
E 4
D 6

E 6
I 6
D 7
#endif
E 6
	REG_UNLOCK(lp);
E 7
I 3

	return (GEM_SUCCESS);
E 3
}

static int
tcfe_stop_chip(struct gem_dev *dp)
{
D 6
	struct tcfe_dev	*lp = (struct tcfe_dev *)dp->private;
E 6
I 6
	struct tcfe_dev	*lp = dp->private;
E 6

	DPRINTF(1, (CE_CONT, "!%s: %s: called", dp->name, __func__));

D 7
	REG_LOCK(lp);

E 7
	/* inhibit interrupt */
	EXEC_CMD(dp, CmdSetInterruptEnable | 0);

	/* no more statistics */
	EXEC_CMD(dp, CmdStatisticsDisable);

D 6
	/* stop receiver, then stop rx dma/	
E 6
I 6
	/* stop receiver, then stop rx dma */
E 6
	EXEC_CMD(dp, CmdRxDisable);
	EXEC_CMD_WAIT(dp, CmdUpStall);

	/* stop tx dma, then stop transmitter */
	EXEC_CMD_WAIT(dp, CmdDnStall);
	EXEC_CMD(dp, CmdTxDisable);

	/* wait DMA completes */
D 4
	drv_usecwait(2000);
E 4
I 4
	drv_usecwait(dp->speed == GEM_SPD_100 ? dp->mtu/10 : dp->mtu);
E 4

	if (lp->media == xcvrSelect10BASE2) {
		EXEC_CMD(dp, CmdDisableDcConverter);
		drv_usecwait(800);
	}

	EXEC_CMD_WAIT(dp, CmdRxReset);
	EXEC_CMD_WAIT(dp, CmdTxReset);

D 7
	REG_UNLOCK(lp);

E 7
	return (GEM_SUCCESS);
}

D 3
static void
E 3
I 3
static int
E 3
tcfe_get_stats(struct gem_dev *dp)
{
	int		first_coll;
	int		multi_coll;
	volatile int	x;
D 6
	struct tcfe_dev	*lp = (struct tcfe_dev *)dp->private;
E 6
I 6
	struct tcfe_dev	*lp = dp->private;
E 6

	DPRINTF(2, (CE_CONT, "!%s: %s: called", dp->name, __func__));

D 7
	REG_LOCK(lp);
E 7
	EXEC_CMD(dp, CmdStatisticsDisable);

I 7
	REG_LOCK(lp);
E 7
	SET_WIN(dp, 6);
D 6
	dp->stats.nocarrier 	+= INB(dp, W6CarrierLost); 
	/* heartbeat err */	x= INB(dp, W6SqeErrors);
E 6
I 6
	dp->stats.nocarrier 	+= INB(dp, W6CarrierLost);
	x /* heartbeat err */	 = INB(dp, W6SqeErrors);
E 6
	multi_coll		 = INB(dp, W6MultipleCollisions);
	dp->stats.multi_coll	+= multi_coll;
	first_coll		 = INB(dp, W6SingleCollisions);
	dp->stats.first_coll	+= first_coll;
	dp->stats.xmtlatecoll	+= INB(dp, W6LateCollisions);
	dp->stats.missed	+= INB(dp, W6RxOverruns);
D 6
	dp->stats.opackets	+= INB(dp, W6FramesXmittedOk);
	dp->stats.rpackets	+= INB(dp, W6FramesRcvdOk);
	dp->stats.defer  	+= INB(dp, W6FramesDeferred); 
	dp->stats.rbytes	+= INW(dp, W6BytesRcvdOk);
	dp->stats.obytes	+= INW(dp, W6BytesXmittedOk);
E 6
I 6
	x /* dp->stats.opackets */ += INB(dp, W6FramesXmittedOk);
	x /* dp->stats.rpackets */ += INB(dp, W6FramesRcvdOk);
	dp->stats.defer  	+= INB(dp, W6FramesDeferred);
	x /* dp->stats.rbytes */ += INW(dp, W6BytesRcvdOk);
	x /* dp->stats.obytes */ += INW(dp, W6BytesXmittedOk);
E 6

D 6
	/* read extended statistics */
				x= INB(dp, W6UpperFramesOk);
E 6
I 6
	x /* read extended statistics */ = INB(dp, W6UpperFramesOk);
#ifdef notdef
E 6
	dp->stats.rpackets	+=
D 6
	  ((x & UF_upperFramesRcvdOk) >> UF_upperFramesRcvdOkShift) << 8;
E 6
I 6
	    ((x & UF_upperFramesRcvdOk) >> UF_upperFramesRcvdOkShift) << 8;
E 6
	dp->stats.opackets	+=
D 6
	  ((x & UF_upperFramesXmittedOk) >> UF_upperFramesXmittedOkShift) << 8;

E 6
I 6
	    ((x & UF_upperFramesXmittedOk) >> UF_upperFramesXmittedOkShift)
	    << 8;
#endif
E 6
	SET_WIN(dp, 4);
D 6
				x= INB(dp, W4BadSSD);
				x= INW(dp, W4UpperBytesOk);
E 6
I 6
	x			 = INB(dp, W4BadSSD);
	x			 = INW(dp, W4UpperBytesOk);
#ifdef notdef
E 6
	dp->stats.rpackets	+=
D 6
	((x & UF_upperFramesRcvdOk) >> UF_upperFramesRcvdOkShift) << 16;
E 6
I 6
	    ((x & UF_upperFramesRcvdOk) >> UF_upperFramesRcvdOkShift)
	    << 16;
E 6
	dp->stats.opackets	+=
D 6
	((x & UF_upperFramesXmittedOk) >> UF_upperFramesXmittedOkShift) << 16;

E 6
I 6
	    ((x & UF_upperFramesXmittedOk) >> UF_upperFramesXmittedOkShift)
	    << 16;
#endif
I 7
	REG_UNLOCK(lp);

E 7
E 6
	/*
	 * Guess total collisions
	 */
	dp->stats.collisions += first_coll + multi_coll*2;

	EXEC_CMD(dp, CmdStatisticsEnable);

D 7
	REG_UNLOCK(lp);
E 7
I 3

	return (GEM_SUCCESS);
E 3
}

/*
 * discriptor  manupiration
 */
static int
tcfe_tx_desc_write(struct gem_dev *dp, int slot,
D 6
		ddi_dma_cookie_t *dmacookie, int frags, uint32_t flag)
E 6
I 6
		ddi_dma_cookie_t *dmacookie, int frags, uint64_t flag)
E 6
{
	int			i;
	struct DPD_type0	*tfdp;
	struct DnFrag		*tfp;
	ddi_dma_cookie_t	*dcp;
	uint32_t		mark;
	uint32_t		total;
D 6
	struct tcfe_dev		*lp = (struct tcfe_dev *)dp->private;
E 6
I 6
	struct tcfe_dev		*lp = dp->private;
E 6

D 6
#if DEBUG_LEVEL > 2
E 6
I 6
#if DEBUG_LEVEL > 20
E 6
	/* force to cause interrupt upon tx completion */
	flag |= GEM_TXFLAG_INTR;
#endif
D 6
	tfdp = (struct DPD_type0 *)(dp->tx_ring + DN_LIST_SIZE * slot);
E 6
I 6
	tfdp = (void *)(dp->tx_ring + DN_LIST_SIZE * slot);
E 6
#if DEBUG_LEVEL > 2
	cmn_err(CE_CONT,
D 6
		"!%s: %s seqnum: %d, slot %d, frags: %d flag: %d",
		dp->name, __func__, dp->tx_desc_tail, slot, frags, flag);
E 6
I 6
	    "!%s: %s seqnum: %d, slot %d, frags: %d flag: %llx",
	    dp->name, __func__, dp->tx_desc_tail, slot, frags, flag);
E 6
	for (i = 0; i < frags; i++) {
		cmn_err(CE_CONT, "%d: addr: 0x%x, len: 0x%x",
D 6
			i, dmacookie[i].dmac_address, dmacookie[i].dmac_size);
E 6
I 6
		    i, dmacookie[i].dmac_address, dmacookie[i].dmac_size);
E 6
	}
#endif

	/* copy fragment list */
	total = 0;
D 6
	mark  = DF_dnFragLast; /* last fragment */
E 6
I 6
	mark = DF_dnFragLast; /* last fragment */
E 6
	dcp = &dmacookie[frags - 1];
	tfp = &tfdp->frags[frags - 1];
	for (i = frags-1; i >= 0; dcp--, tfp--, i--, mark = 0) {
I 7
		uint32_t	len;
		uint32_t	addr;

E 7
		total += dcp->dmac_size;
D 6
		tfp->DnFragLen  = LE32(dcp->dmac_size | mark);
		tfp->DnFragAddr = LE32(dcp->dmac_address);
E 6
I 6
D 7
		tfp->DnFragLen = LE_32(dcp->dmac_size | mark);
		tfp->DnFragAddr = LE_32(dcp->dmac_address);
E 7
I 7
		len = dcp->dmac_size | mark;
		addr = dcp->dmac_address;
		tfp->DnFragLen = LE_32(len);
		tfp->DnFragAddr = LE_32(addr);
E 7
E 6
	}

D 6
	tfdp->DnNextPtr = LE32(dp->tx_ring_dma +
				DN_LIST_SIZE * SLOT(slot + 1, TX_RING_SIZE));
E 6
I 6
	tfdp->DnNextPtr = LE_32(dp->tx_ring_dma +
	    DN_LIST_SIZE * SLOT(slot + 1, TX_RING_SIZE));
E 6
I 4

E 4
D 6
	if ((flag & GEM_TXFLAG_INTR) != 0) {
E 6
I 6
	if (flag & GEM_TXFLAG_INTR) {
E 6
		total |= FS_dnIndicate;
	}

#ifdef GEM_CONFIG_CKSUM_OFFLOAD
D 2
	if ((flag & GEM_TXFLAG_IPv4) != 0) {
		total |= FS_addIpChecksum;
E 2
I 2
	if (IS_3C90XB_OR_LATER(lp)) {
D 4
		if ((flag & GEM_TXFLAG_IPv4) != 0) {
			total |= FS_addIpChecksum;
		}
E 4
D 6
		if ((flag & GEM_TXFLAG_TCP) != 0) {
E 6
I 6
		if (flag & GEM_TXFLAG_TCP) {
E 6
			total |= FS_addTcpChecksum | FS_addIpChecksum;
D 6
		}
		else if ((flag & GEM_TXFLAG_UDP) != 0) {
E 6
I 6
		} else if (flag & GEM_TXFLAG_UDP) {
E 6
			total |= FS_addUdpChecksum | FS_addIpChecksum;
D 6
		}
I 4
		else if ((flag & GEM_TXFLAG_IPv4) != 0) {
E 6
I 6
		} else if (flag & GEM_TXFLAG_IPv4) {
E 6
			total |= FS_addIpChecksum;
		}
E 4
E 2
	}
D 2
	if ((flag & GEM_TXFLAG_TCP) != 0) {
		total |= FS_addTcpChecksum;
		total |= FS_addIpChecksum;
	}
	else if ((flag & GEM_TXFLAG_UDP) != 0) {
		total |= FS_addUdpChecksum;
		total |= FS_addIpChecksum;
	}
E 2
#endif
I 4
	ASSERT((total & FS_dnComplete) == 0);
E 4
D 6
	tfdp->FrameStartHeader = LE32(total);
E 6
I 6
	tfdp->FrameStartHeader = LE_32(total);
E 6

	return (1);
}

static void
tcfe_tx_start(struct gem_dev *dp, int start_slot, int nslots)
{
	struct DPD_type0	*tfdp;
	int			prev_slot;
	uint32_t		head_dma;
	boolean_t		need_restart;
D 6
	struct tcfe_dev		*lp = (struct tcfe_dev *)dp->private;
E 6
I 6
	struct tcfe_dev		*lp = dp->private;
I 7
	int			tx_ring_size = dp->gc.gc_tx_ring_size;
E 7
E 6

D 3
	/* fix next pointer in the last descriptor int the tx list */
E 3
I 3
D 4
	/* fix next pointer in the last descriptor of the tx list */
E 4
I 4
	/* fix next pointer in the last descriptor of the new tx list */
E 4
E 3
D 6
	tfdp = (struct DPD_type0 *)(dp->tx_ring +
		 DN_LIST_SIZE * SLOT(start_slot + nslots - 1, TX_RING_SIZE));
E 6
I 6
	tfdp = (void *)(dp->tx_ring +
D 7
	    DN_LIST_SIZE * SLOT(start_slot + nslots - 1, TX_RING_SIZE));
E 7
I 7
	    DN_LIST_SIZE * SLOT(start_slot + nslots - 1, tx_ring_size));
E 7
E 6
	tfdp->DnNextPtr = 0;
	gem_tx_desc_dma_sync(dp, start_slot, nslots, DDI_DMA_SYNC_FORDEV);

D 4
	/* link this to the previous descritor */
E 4
I 4
	/* append the new tx descriptors at the tail of current tx list */
E 4
D 7
	prev_slot = SLOT(start_slot - 1, TX_RING_SIZE);
E 7
I 7
	prev_slot = SLOT(start_slot - 1, tx_ring_size);
E 7
D 6
	tfdp = (struct DPD_type0 *) (dp->tx_ring + DN_LIST_SIZE * prev_slot);
E 6
I 6
	tfdp = (void *)(dp->tx_ring + DN_LIST_SIZE * prev_slot);
E 6

D 4
	need_restart = B_FALSE;
E 4
I 4
D 6
	head_dma = ((uint32_t) dp->tx_ring_dma) + DN_LIST_SIZE * start_slot;
	tfdp->DnNextPtr = LE32(head_dma);
E 6
I 6
	head_dma = ((uint32_t)dp->tx_ring_dma) + DN_LIST_SIZE * start_slot;
	tfdp->DnNextPtr = LE_32(head_dma);
E 6
	gem_tx_desc_dma_sync(dp, prev_slot, 1, DDI_DMA_SYNC_FORDEV);

E 4
D 7
	if (IS_3C90X(lp) || !lp->dnlistptr_loaded) {
E 7
I 7
	if (!lp->dnlistptr_loaded) {
E 7
D 4
		/* ensure download engine stopped */
E 4
I 4
		/* stop the download engine */
E 4
D 7
		REG_LOCK(lp);
E 7
		EXEC_CMD_WAIT(dp, CmdDnStall);
D 4
		REG_UNLOCK(lp);
		need_restart = B_TRUE;
	}
E 4

D 4
	tfdp->DnNextPtr = head_dma =
		((uint32_t) dp->tx_ring_dma) + DN_LIST_SIZE * start_slot;
	gem_tx_desc_dma_sync(dp, prev_slot, 1, DDI_DMA_SYNC_FORDEV);

	if (need_restart) {
		/* restart download engine */
E 4
I 4
		/* update DnListPtr if download engine has finished */
E 4
		if (INL(dp, WxDnListPtr) == 0) {
D 4
			/* kick download engine */
E 4
			OUTL(dp, WxDnListPtr, head_dma);
I 4
D 6
#ifdef TEST_BOOMERANG
E 6
I 6
D 7
#ifndef TEST_BOOMERANG
E 6
			lp->dnlistptr_loaded = B_TRUE;
E 7
I 7
#ifdef CONFIG_TX_AUTO_POLL
			if (IS_3C90XB_OR_LATER(lp)) {
				lp->dnlistptr_loaded = B_TRUE;
			}
E 7
#endif
E 4
		}
D 7

D 4
		REG_LOCK(lp);
E 4
I 4
		/* activate the download engine */
E 4
		EXEC_CMD(dp, CmdDnUnstall);
		REG_UNLOCK(lp);
E 7
D 4
#if defined(CONFIG_DNPOLL)
		lp->dnlistptr_loaded = B_TRUE;
#endif
E 4
	}
I 7

	/* activate the download engine */
	EXEC_CMD(dp, CmdDnUnstall);

	lp->tx_last_slot = SLOT(start_slot + nslots, tx_ring_size);
E 7
}

static void
tcfe_rx_desc_write(struct gem_dev *dp, int slot,
	    ddi_dma_cookie_t *dmacookie, int frags)
{
	int			i;
	struct UPD		*rfdp;
	struct UpFrag		*rfp;
	ddi_dma_cookie_t	*dcp;
	uint32_t		len;
	uint32_t		n;
I 7
	uint32_t		addr;
E 7
D 6
	struct tcfe_dev		*lp = (struct tcfe_dev *)dp->private;
E 6
I 6
	struct tcfe_dev		*lp = dp->private;
E 6

D 6
	rfdp = (struct UPD *) (dp->rx_ring + UP_LIST_SIZE * slot);
E 6
I 6
	rfdp = (void *)(dp->rx_ring + UP_LIST_SIZE * slot);
E 6

#if DEBUG_LEVEL > 2
	cmn_err(CE_CONT, "!%s: %s seqnum: %d, slot %d, frags: %d",
D 6
		dp->name, __func__, dp->rx_active_tail, slot, frags);
E 6
I 6
	    dp->name, __func__, dp->rx_active_tail, slot, frags);
E 6
	for (i = 0; i < frags; i++) {
		cmn_err(CE_CONT, "  frag: %d addr: 0x%x, len: 0x%x",
D 6
			i, dmacookie[i].dmac_address, dmacookie[i].dmac_size);
E 6
I 6
		    i, dmacookie[i].dmac_address, dmacookie[i].dmac_size);
E 6
	}
#endif

	/* copy fragment list */
	len = 0;
	dcp = dmacookie;
	rfp = rfdp->frags;
	for (i = frags - 1; i--; dcp++, rfp++) {
D 6
		len += n = (uint32_t) dcp->dmac_size;
		rfp->UpFragLen  = LE32(n);
		rfp->UpFragAddr = LE32((uint32_t) dcp->dmac_address);
E 6
I 6
		len += n = (uint32_t)dcp->dmac_size;
I 7
		addr = (uint32_t)dcp->dmac_address;
E 7
		rfp->UpFragLen = LE_32(n);
D 7
		rfp->UpFragAddr = LE_32((uint32_t)dcp->dmac_address);
E 7
I 7
		rfp->UpFragAddr = LE_32(addr);
E 7
E 6
	}

	/* for last fragment */
D 6
	len += n = (uint32_t) dcp->dmac_size;
	rfp->UpFragLen  = LE32(n | UF_upFragLast);
	rfp->UpFragAddr = LE32((uint32_t) dcp->dmac_address);
E 6
I 6
	len += n = (uint32_t)dcp->dmac_size;
D 7
	rfp->UpFragLen = LE_32(n | UF_upFragLast);
	rfp->UpFragAddr = LE_32((uint32_t)dcp->dmac_address);
E 7
I 7
	n |= UF_upFragLast;
	addr = (uint32_t)dcp->dmac_address;
	rfp->UpFragLen = LE_32(n);
	rfp->UpFragAddr = LE_32(addr);
E 7
E 6

D 4
	/* make upload header */
E 4
I 4
	/* make an upload header */
E 4
	/* XXX - this storing action must be the last for auto polling */
D 4
	rfdp->UpPktStatus = 0;
E 4
I 4
	if (lp->rx_last_slot != slot) {
		rfdp->UpPktStatus = 0;
	}
E 4
}

static void
tcfe_rx_start(struct gem_dev *dp, int start_slot, int nslots)
{
D 4
	struct tcfe_dev		*lp = (struct tcfe_dev *)dp->private;
E 4
I 4
	int		i;
	struct UPD	*rfdp;
D 6
	struct tcfe_dev	*lp = (struct tcfe_dev *) dp->private;
E 6
I 6
	struct tcfe_dev	*lp = dp->private;
E 6
E 4

D 4
	gem_tx_desc_dma_sync(dp, start_slot, nslots, DDI_DMA_SYNC_FORDEV);
E 4
I 4
	if (nslots > 1) {
D 7
		gem_tx_desc_dma_sync(dp,
E 7
I 7
		gem_rx_desc_dma_sync(dp,
E 7
D 6
			SLOT(start_slot + 1, RX_RING_SIZE), nslots - 1,
			DDI_DMA_SYNC_FORDEV);
E 6
I 6
		    SLOT(start_slot + 1, RX_RING_SIZE), nslots - 1,
		    DDI_DMA_SYNC_FORDEV);
E 6
	}
E 4

D 4
	if (IS_3C90X(lp)) {
E 4
I 4
	/* enable the first descriptor of the new list */
D 6
	rfdp = (struct UPD *) (dp->rx_ring + UP_LIST_SIZE * start_slot);
E 6
I 6
	rfdp = (void *)(dp->rx_ring + UP_LIST_SIZE * start_slot);
E 6
	lp->rx_last_slot = SLOT(start_slot + nslots, RX_RING_SIZE);

	rfdp->UpPktStatus = 0;
D 7
	gem_tx_desc_dma_sync(dp, start_slot, 1, DDI_DMA_SYNC_FORDEV);
E 7
I 7
	gem_rx_desc_dma_sync(dp, start_slot, 1, DDI_DMA_SYNC_FORDEV);
E 7

D 7
#ifndef TEST_BOOMERANG
D 6
	if (IS_3C90X(lp))
E 6
I 6
	if (IS_3C90X(lp)) {
E 7
I 7
#ifdef CONFIG_RX_AUTO_POLL
	if (IS_3C90XB_OR_LATER(lp)) {
		/* no need to restart upload engine explicitly */
		return;
	}
E 7
E 6
#endif
D 6
	{
E 6
E 4
D 7
		REG_LOCK(lp);
I 4
D 5
#ifdef never
E 5
I 5
D 6
#ifdef NEVER
E 5
		/* XXX - don't stall upload engine. it drops packets */
		EXEC_CMD_WAIT(dp, CmdUpStall);
#endif
		i = 0;
		while ((INW(dp, WxIntStatus) & IS_cmdInProgress) != 0) {
			if (i++ > 200) {
E 6
I 6
		/*
		 * XXX - don't stall upload engine. it drops packets.
		 * EXEC_CMD_WAIT(dp, CmdUpStall);
		 */
		for (i = 0; INW(dp, WxIntStatus) & IS_cmdInProgress; i++) {
			if (i > 200) {
E 6
				cmn_err(CE_WARN,
D 6
					"%s: %s: timeout error: upLoad busy",
					dp->name, __func__);
E 6
I 6
				    "!%s: %s: timeout error: upLoad busy",
				    dp->name, __func__);
E 6
				lp->need_to_reset = B_TRUE;
				break;
			}
			drv_usecwait(10);
E 7
I 7
#ifdef NEVER
	/*
	 * XXX - don't stall upload engine. it will make packets dropped.
	 */
	EXEC_CMD_WAIT(dp, CmdUpStall);
	for (i = 0; INW(dp, WxIntStatus) & IS_cmdInProgress; i++) {
		if (i > 200) {
			cmn_err(CE_WARN,
			    "!%s: %s: timeout error: upLoad busy",
			    dp->name, __func__);
			lp->need_to_reset = B_TRUE;
			break;
E 7
		}
D 7

D 6
		/* start the stopped upload engine */
E 6
I 6
		/* start possibly stopped upload engine */
E 6
E 4
		EXEC_CMD(dp, CmdUpUnstall);
		REG_UNLOCK(lp);
I 6
#ifndef TEST_BOOMERANG
E 7
I 7
		drv_usecwait(10);
E 7
E 6
	}
I 6
#endif
I 7
	/* start possibly stopped upload engine */
	EXEC_CMD(dp, CmdUpUnstall);
E 7
E 6
}

I 7
#if defined(GEM_CONFIG_TX_HEAD_PTR) && defined(CONFIG_TX_AUTO_POLL)
E 7
static uint_t
I 7
tcfe_tx_desc_head(struct gem_dev *dp)
{
	uint_t		slot;
	uint32_t	cur_pos;
	struct tcfe_dev	*lp = dp->private;

	cur_pos = INL(dp, WxDnListPtr);
	if (cur_pos == 0) {
		return (lp->tx_last_slot);
	}

	slot = (cur_pos - (uint32_t)dp->tx_ring_dma) >> DN_LIST_SIZE_SHIFT;

	/* sanity check */
	if (slot < 0 || slot >= dp->gc.gc_tx_ring_size) {
		lp->need_to_reset = B_TRUE;
		return (lp->tx_last_slot);
	}

	return (slot);
}
#endif /* GEM_CONFIG_TX_HEAD_PTR */
static uint_t
E 7
tcfe_tx_desc_stat(struct gem_dev *dp, int slot, int ndesc)
{
D 4
	int			ret = 0;
E 4
I 4
	int			ret;
E 4
	struct DPD_type0	*tfdp;
	uint32_t		header;
D 6
	struct tcfe_dev		*lp = (struct tcfe_dev *)dp->private;
E 6
I 6
	struct tcfe_dev		*lp = dp->private;
E 6

I 4
D 7
#ifndef TEST_BOOMERANG
E 7
I 7
#ifdef CONFIG_TX_AUTO_POLL
E 7
E 4
	if (IS_3C90XB_OR_LATER(lp)) {
D 4
		tfdp = (struct DPD_type0 *)(dp->tx_ring + DN_LIST_SIZE * slot);
E 4
I 4
D 6
		tfdp = (struct DPD_type0 *) (dp->tx_ring + DN_LIST_SIZE * slot);
E 4
		header = LE32(tfdp->FrameStartHeader);
		return ((header & FS_dnComplete) != 0 ? GEM_TX_DONE : 0);
E 6
I 6
		tfdp = (void *)(dp->tx_ring + DN_LIST_SIZE * slot);
		header = tfdp->FrameStartHeader;
		header = LE_32(header);
		return ((header & FS_dnComplete) ? GEM_TX_DONE : 0);
E 6
	}
D 4

E 4
I 4
#endif
	ret = 0;
E 4
D 2
#if 0
E 2
I 2
D 3
#if 1
E 3
E 2
D 7
	REG_LOCK(lp);
E 7
I 7
#ifdef CONFIG_STALL_ON_TXSTAT
E 7
	EXEC_CMD_WAIT(dp, CmdDnStall);
I 7
#endif
E 7
D 3
#endif
E 3
D 6
	if (INL(dp, WxDnListPtr) != 
D 4
		((uint32_t)dp->tx_ring_dma) + DN_LIST_SIZE * slot) {
E 4
I 4
		((uint32_t) dp->tx_ring_dma) + DN_LIST_SIZE * slot) {
E 6
I 6
	if (INL(dp, WxDnListPtr) !=
	    ((uint32_t)dp->tx_ring_dma) + DN_LIST_SIZE * slot) {
E 6
E 4
		ret = GEM_TX_DONE;
	}
I 7
#ifdef CONFIG_STALL_ON_TXSTAT
E 7
D 2
#if 0
E 2
I 2
D 3
#if 1
E 3
E 2
	EXEC_CMD(dp, CmdDnUnstall);
D 7
	REG_UNLOCK(lp);
D 3
#endif
E 3

E 7
I 7
#endif
E 7
	return (ret);
}

static uint64_t
tcfe_rx_desc_stat(struct gem_dev *dp, int slot, int ndesc)
{
	struct UPD	*rfdp;
	uint32_t	rfs;
	uint64_t	len;
	uint64_t	flag = 0;
D 6
	struct tcfe_dev	*lp = (struct tcfe_dev *)dp->private;
E 6
I 6
	struct tcfe_dev	*lp = dp->private;
E 6

D 6
	rfdp = (struct UPD *) (dp->rx_ring + UP_LIST_SIZE * slot);
E 6
I 6
	rfdp = (void *)(dp->rx_ring + UP_LIST_SIZE * slot);
E 6

D 6
	rfs  = LE32(rfdp->UpPktStatus);
E 6
I 6
	rfs = rfdp->UpPktStatus;
	rfs = LE_32(rfs);
E 6

	DPRINTF(2, (CE_CONT,
D 6
		"!%s: %s: slot:%d, rfs:0x%b",
		dp->name, __func__, slot, rfs, UpPktStatusBits));
E 6
I 6
	    "!%s: %s: slot:%d, rfs:0x%b",
	    dp->name, __func__, slot, rfs, UpPktStatusBits));
E 6

	if ((rfs & UPS_upComplete) == 0) {
		/* not received */
		return (flag);
	}

	flag = GEM_RX_DONE | (rfs & UPS_upPktLen);

#define	UPS_upErrorVlan	\
D 6
	(UPS_alignmentError | UPS_upOverflow | UPS_runtFrame | \
	 UPS_crcError | UPS_upOverrun)
E 6
I 6
	    (UPS_alignmentError | UPS_upOverflow | UPS_runtFrame | \
	    UPS_crcError | UPS_upOverrun)
E 6

D 6
	if ((rfs & UPS_upErrorVlan) != 0) {
E 6
I 6
	if (rfs & UPS_upErrorVlan) {
E 6
		/* error packet */

		DPRINTF(4, (CE_CONT,
D 6
			"!%s: %s: slot:%d, rfs:0x%b",
			dp->name, __func__, slot, rfs, UpPktStatusBits));
E 6
I 6
		    "!%s: %s: slot:%d, rfs:0x%b",
		    dp->name, __func__, slot, rfs, UpPktStatusBits));
E 6

		dp->stats.errrcv++;
D 6
		if ((rfs & UPS_alignmentError) != 0) {
E 6
I 6
		if (rfs & UPS_alignmentError) {
E 6
			dp->stats.frame++;
D 6
		}
		if ((rfs & UPS_upOverflow) != 0) {
E 6
I 6
		} else if (rfs & UPS_upOverflow) {
E 6
			dp->stats.overflow++;
D 6
		}
I 4
		if ((rfs & UPS_upOverrun) != 0) {
E 6
I 6
		} else if (rfs & UPS_upOverrun) {
E 6
			dp->stats.overflow++;
D 6
		}
E 4
		if ((rfs & UPS_runtFrame) != 0) {
E 6
I 6
		} else if (rfs & UPS_runtFrame) {
E 6
			dp->stats.runt++;
D 6
		}
		if ((rfs & UPS_crcError) != 0) {
E 6
I 6
		} else if (rfs & UPS_crcError) {
E 6
			dp->stats.crc++;
D 6
		}
D 4
		if ((rfs & (UPS_upOverrun/*| UPS_oversizedFrame*/)) != 0) {
E 4
I 4
		if ((rfs & UPS_oversizedFrame) != 0) {
E 6
I 6
		} else if (rfs & UPS_oversizedFrame) {
E 6
E 4
			dp->stats.frame_too_long++;
I 6
		} else {
			dp->stats.rcv_internal_err++;
E 6
		}

		flag = GEM_RX_ERR;
D 6
	}

E 6
#ifdef GEM_CONFIG_CKSUM_OFFLOAD
D 6
	else if ((rfs & (UPS_tcpChecksumChecked | UPS_tcpChecksumError))
						== UPS_tcpChecksumChecked) {
E 6
I 6
	} else if ((rfs & (UPS_tcpChecksumChecked | UPS_tcpChecksumError))
	    == UPS_tcpChecksumChecked) {
E 6
		flag |= GEM_RX_CKSUM_TCP;
D 6
	}
	else if ((rfs & (UPS_udpChecksumChecked | UPS_udpChecksumError))
						== UPS_udpChecksumChecked) {
E 6
I 6
	} else if ((rfs & (UPS_udpChecksumChecked | UPS_udpChecksumError))
	    == UPS_udpChecksumChecked) {
E 6
		flag |= GEM_RX_CKSUM_UDP;
D 6
	}
	else if ((rfs & (UPS_ipChecksumChecked | UPS_ipChecksumError))
						== UPS_ipChecksumChecked) {
E 6
I 6
	} else if ((rfs & (UPS_ipChecksumChecked | UPS_ipChecksumError))
	    == UPS_ipChecksumChecked) {
E 6
		flag |= GEM_RX_CKSUM_IPv4;
D 6
	}
E 6
#endif
I 6
	}
E 6

	return (flag);
}

static void
tcfe_tx_desc_init(struct gem_dev *dp, int slot)
{
	struct DPD_type0	*tfdp;

D 6
	tfdp = (struct DPD_type0 *) (dp->tx_ring + DN_LIST_SIZE * slot);
E 6
I 6
	tfdp = (void *)(dp->tx_ring + DN_LIST_SIZE * slot);
E 6
	bzero(tfdp, DN_LIST_SIZE);
}

static void
tcfe_rx_desc_init(struct gem_dev *dp, int slot)
{
	struct UPD	*rfdp;
	uint32_t	next_dma;

D 6
	next_dma = ((uint32_t) dp->rx_ring_dma) +
				UP_LIST_SIZE * SLOT(slot + 1, RX_RING_SIZE);
	rfdp = (struct UPD *) (dp->rx_ring + UP_LIST_SIZE * slot);
E 6
I 6
	next_dma = ((uint32_t)dp->rx_ring_dma) +
	    UP_LIST_SIZE * SLOT(slot + 1, RX_RING_SIZE);
	rfdp = (void *)(dp->rx_ring + UP_LIST_SIZE * slot);
E 6

D 6
	rfdp->UpPktStatus = LE32(UPS_upComplete);
	rfdp->UpNextPtr = LE32(next_dma);
E 6
I 6
	rfdp->UpPktStatus = LE_32(UPS_upComplete);
	rfdp->UpNextPtr = LE_32(next_dma);
E 6
}

static void
tcfe_tx_desc_clean(struct gem_dev *dp, int slot)
{
	struct DPD_type0	*tfdp;

D 6
	tfdp = (struct DPD_type0 *) (dp->tx_ring + DN_LIST_SIZE * slot);
E 6
I 6
	tfdp = (void *)(dp->tx_ring + DN_LIST_SIZE * slot);
E 6
	bzero(tfdp, DN_LIST_SIZE);
}

static void
tcfe_rx_desc_clean(struct gem_dev *dp, int slot)
{
	struct UPD	*rfdp;

D 6
	rfdp = (struct UPD *) (dp->rx_ring + UP_LIST_SIZE * slot);
E 6
I 6
	rfdp = (void *)(dp->rx_ring + UP_LIST_SIZE * slot);
E 6

D 6
	rfdp->UpPktStatus = LE32(UPS_upComplete);
E 6
I 6
	rfdp->UpPktStatus = LE_32(UPS_upComplete);
E 6
}

/*
 * Device depend interrupt handler
 */
D 4
static boolean_t
E 4
I 4
static void
E 4
tcfe_get_tx_status(struct gem_dev  *dp)
{
	int		error = 0;
D 4
	boolean_t	need_to_reset = B_FALSE;
E 4
	uint8_t		tx_status;
D 6
	struct tcfe_dev	*lp = (struct tcfe_dev *)dp->private;
E 6
I 6
	struct tcfe_dev	*lp = dp->private;
E 6

	DPRINTF(2, (CE_CONT, "%s: %s: called", dp->name, __func__));

D 3
	/* Clear the Tx status stack. */
E 3
I 3
	/* Clear Tx status stack. */
E 3
D 6
	while ((INW(dp, WxIntStatus) & IS_txComplete) != 0) {
E 6
I 6
	while (INW(dp, WxIntStatus) & IS_txComplete) {
E 6

		tx_status = INB(dp, WxTxStatus);
		OUTB(dp, WxTxStatus, 0);

D 6
		if ((tx_status & TS_txStatusOverflow) != 0) {
E 6
I 6
		if (tx_status & TS_txStatusOverflow) {
E 6
			cmn_err(CE_WARN,
			    "%s: tx status overflow: tx_status: %b",
			    dp->name, tx_status, TxStatusBits);
I 6
			dp->stats.xmit_internal_err++;
			dp->stats.errxmt++;
E 6
		}

		/* update stats */
D 6
		if ((tx_status & TS_txUnderrun) != 0) {
E 6
I 6
		if (tx_status & TS_txUnderrun) {
E 6
			/* fifo underflow */
			dp->stats.underflow++;
			dp->stats.errxmt++;
		}

D 6
		if ((tx_status & TS_maxCollisions) != 0) {
E 6
I 6
		if (tx_status & TS_maxCollisions) {
E 6
			/* exceed maximum collisions */
			dp->stats.excoll++;
			dp->stats.collisions += 16;
			dp->stats.errxmt++;
		}

D 6
		if ((tx_status & TS_txJabber) != 0) {
E 6
I 6
		if (tx_status & TS_txJabber) {
			dp->stats.xmit_internal_err++;
E 6
			dp->stats.errxmt++;
		}

		/* collect status bits */
		error |= (tx_status &
D 6
			     (TS_txJabber | TS_txUnderrun | TS_maxCollisions));
E 6
I 6
		    (TS_txJabber | TS_txUnderrun | TS_maxCollisions));
E 6
	}

D 6
	if (error != 0) {
E 6
I 6
	if (error) {
E 6
D 7
		REG_LOCK(lp);
E 7
D 6
		if ((error & (TS_txUnderrun | TS_txJabber)) != 0) {
E 6
I 6
		if (error & (TS_txUnderrun | TS_txJabber)) {
E 6
			/*
			 * XXX - not implemented completely
			 */
			EXEC_CMD_WAIT(dp, CmdTxReset);
D 4
			need_to_reset = B_TRUE;
E 4
I 4
			lp->need_to_reset = B_TRUE;
E 4
		}

D 6
		if ((error & TS_maxCollisions) != 0) {
E 6
I 6
		if (error & TS_maxCollisions) {
E 6
			EXEC_CMD(dp, CmdStatisticsEnable);
		}

D 6
		EXEC_CMD(dp, CmdTxEnable); 
E 6
I 6
		EXEC_CMD(dp, CmdTxEnable);
E 6
D 7
		REG_UNLOCK(lp);
E 7
	}
D 4

	return (need_to_reset);
E 4
}

D 6
static u_int
E 6
I 6
static uint_t
E 6
tcfe_interrupt(struct gem_dev *dp)
{
D 4
	boolean_t	need_to_reset = B_FALSE;
E 4
	uint16_t	status;
D 6
	u_int		tx_sched = 0;
	struct tcfe_dev	*lp = (struct tcfe_dev *)dp->private;
E 6
I 6
	uint_t		tx_sched = 0;
	struct tcfe_dev	*lp = dp->private;
E 6

	/* Read interrupt status */
	status = INW(dp, WxIntStatus);
D 6
	DPRINTF(2, (CE_CONT, "%s: %s, status: %b",
		   dp->name, __func__, status, IntStatusBits));
E 6
I 6
	DPRINTF(3, (CE_CONT, "%s: %s, status: %b",
	    dp->name, __func__, status, IntStatusBits));
E 6

D 6
	if ((status & OUR_INTR_BITS) == 0) {
E 6
I 6
	if ((status & lp->intenable) == 0) {
E 6
		/* Not for us */
		return (DDI_INTR_UNCLAIMED);
	}

	DPRINTF(2, (CE_CONT, "%s: %s, status: %b",
D 6
		   dp->name, __func__, status, IntStatusBits));
E 6
I 6
	    dp->name, __func__, status, IntStatusBits));
E 6

	/*
	 * Clear all interrupt mask and ack interrupt,
	 */
D 7
	REG_LOCK(lp);
E 7
D 6
	EXEC_CMD(dp, CmdSetInterruptEnable | 0);
E 6
	EXEC_CMD(dp, CmdAcknowledgeInterrupt | (status & AllAck));
D 7
	REG_UNLOCK(lp);
E 7

	if (!dp->mac_active) {
		/*
		 * the device is not active.
		 * side effect: left interrupt masked.
		 */
I 6
		lp->intenable = 0;
D 7
		REG_LOCK(lp);
E 7
		EXEC_CMD(dp, CmdSetInterruptEnable | lp->intenable);
D 7
		REG_UNLOCK(lp);
E 7
E 6
		return (DDI_INTR_CLAIMED);
	}

	status &= OUR_INTR_BITS;

#ifdef GEM_CONFIG_POLLING
D 6
	/*
	 * XXX - the driver become funny when we use Countdown timer.
	 */
E 6
	if (dp->poll_interval != lp->last_poll_interval) {
D 6
		if (dp->poll_interval != 0) {
			/* polling mode */
E 6
I 6
		if (dp->poll_interval) {
			/* move to polling mode */
E 6
			lp->intenable &= ~IS_upComplete;
D 6
		}
		else {
			/* normal mode */
E 6
I 6
		} else {
			/* return to normal mode */
E 6
			lp->intenable |= IS_upComplete;
		}

		/*
		 * To schedule the next timer interrupt,
		 * we pretend as we were interrupted from
		 * polling timer
		 */
		status |= IS_intRequested;

		lp->last_poll_interval = dp->poll_interval;
I 6

		if ((dp->misc_flag & GEM_NOINTR) == 0) {
			/* change interrupt mask */
D 7
			REG_LOCK(lp);
E 7
			EXEC_CMD(dp, CmdSetInterruptEnable | lp->intenable);
D 7
			REG_UNLOCK(lp);
E 7
		}
E 6
	}

D 6
	if ((status & IS_intRequested) != 0) {
E 6
I 6
	if (status & IS_intRequested) {
E 6
		/*
D 6
		 * Reset timer  counter to schedule the next polling
E 6
I 6
		 * Reset timer counter to schedule the next polling
E 6
		 * timer interrupt.
		 */
D 6
		OUTW(dp, WxCountdown, dp->poll_interval * 3);

D 4
		/* force to process dnload complete  */
E 4
I 4
		/* force to process upload complete  */
E 4
		status |= IS_upComplete;
E 6
I 6
		OUTW(dp, WxCountdown, dp->poll_interval / 320);
E 6
	}
#endif /* GEM_CONFIG_POLLING */

D 6
	if ((status & IS_rxEarly) != 0) {
E 6
I 6
	if (status & IS_rxEarly) {
E 6
		cmn_err(CE_WARN, "%s: unexpected RX_EARLY, status: %b",
D 6
			dp->name, status, IntStatusBits);
E 6
I 6
		    dp->name, status, IntStatusBits);
E 6
	}

D 6
	if ((status & IS_upComplete) != 0) {
E 6
I 6
	if (status & IS_upComplete) {
E 6
		/* Receive Complete */
D 6
		gem_receive(dp);
E 6
I 6
		(void) gem_receive(dp);
E 6
	}

D 6
	if ((status & IS_dnComplete) != 0) {
E 6
I 6
	if (status & IS_dnComplete) {
E 6
		if (gem_tx_done(dp)) {
			tx_sched = INTR_RESTART_TX;
		}
	}

D 6
	if ((status & IS_txComplete) != 0) {
E 6
I 6
	if (status & IS_txComplete) {
E 6
D 4
		(void) tcfe_get_tx_status(dp);
E 4
I 4
		tcfe_get_tx_status(dp);
E 4
	}
D 6
	
	if ((status & IS_updateStats) != 0) {
E 6
I 6

	if (status & IS_updateStats) {
E 6
		/* Update Statistics */
		tcfe_get_stats(dp);
	}

D 6
	if ((status & IS_hostError) != 0) {
E 6
I 6
	if (status & IS_hostError) {
E 6
D 4
		need_to_reset = B_TRUE;
E 4
I 4
		lp->need_to_reset = B_TRUE;
E 4
	}

	/*
	 * Postamble for interrupt thread
	 */
x:
D 4
	if (need_to_reset) {
E 4
I 4
	if (lp->need_to_reset) {
E 4
D 6
		gem_restart_nic(dp, B_TRUE);
E 6
I 6
		(void) gem_restart_nic(dp, GEM_RESTART_KEEP_BUF);
E 6
		tx_sched = INTR_RESTART_TX;
	}

	/*
	 * Recover Interrput Enable register
	 */
	DPRINTF(4, (CE_CONT, "!%s: %s done: status: %b",
D 6
		dp->name, __func__, INW(dp, WxIntStatus), IntStatusBits));
E 6
I 6
	    dp->name, __func__, INW(dp, WxIntStatus), IntStatusBits));
E 6

D 6
	if ((dp->misc_flag & GEM_NOINTR) == 0) {
		/* enable interrupt again */
		REG_LOCK(lp);
		EXEC_CMD(dp, CmdSetInterruptEnable | lp->intenable);
		REG_UNLOCK(lp);
	}

E 6
	return (DDI_INTR_CLAIMED | tx_sched);
}
/*
 * HW depend MII routine
 */
D 6
#define MDIO_DELAY(dp)    {INW(dp, W4PhysicalMgmt);INW(dp, W4PhysicalMgmt);}
E 6
I 6
#define	MDIO_DELAY(dp)	{INW(dp, W4PhysicalMgmt); INW(dp, W4PhysicalMgmt); }
E 6
static void
tcfe_mii_sync(struct gem_dev *dp)
{
	int		i;
D 6
	struct tcfe_dev	*lp = (struct tcfe_dev *)dp->private;
E 6
I 6
	struct tcfe_dev	*lp = dp->private;
E 6

	/* output 32 ones */
	REG_LOCK(lp);
	SET_WIN(dp, 4);
	for (i = 0; i < 32; i++) {
		OUTW(dp, W4PhysicalMgmt, PM_mgmtDir | PM_mgmtData);
		MDIO_DELAY(dp);
D 4
		OUTW(dp, W4PhysicalMgmt, PM_mgmtDir | PM_mgmtData | PM_mgmtClk);
E 4
I 4
		OUTW(dp, W4PhysicalMgmt,
D 6
				PM_mgmtDir | PM_mgmtData | PM_mgmtClk);
E 6
I 6
		    PM_mgmtDir | PM_mgmtData | PM_mgmtClk);
E 6
E 4
		MDIO_DELAY(dp);
	}
	REG_UNLOCK(lp);
}

static uint16_t
tcfe_mii_read(struct gem_dev *dp, uint_t reg)
{
	uint32_t	cmd;
	uint16_t	ret;
	int		i;
	uint16_t	data;
D 6
	struct tcfe_dev	*lp = (struct tcfe_dev *)dp->private;
E 6
I 6
	boolean_t	error = B_FALSE;
	struct tcfe_dev	*lp = dp->private;
E 6

	cmd = MII_READ_CMD(dp->mii_phy_addr, reg);

	REG_LOCK(lp);
	SET_WIN(dp, 4);

	for (i = 31; i >= 18; i--) {
		data = ((cmd >> i) & 1) <<  PM_mgmtDataShift;
		OUTW(dp, W4PhysicalMgmt, data | PM_mgmtDir);
		MDIO_DELAY(dp);
		OUTW(dp, W4PhysicalMgmt, data | PM_mgmtDir | PM_mgmtClk);
		MDIO_DELAY(dp);
	}
	/* turn around */
	OUTW(dp, W4PhysicalMgmt, 0);
	MDIO_DELAY(dp);

	/* get response from PHY */
	OUTW(dp, W4PhysicalMgmt, PM_mgmtClk);
	MDIO_DELAY(dp);
	OUTW(dp, W4PhysicalMgmt, 0);
D 6
	if ((INW(dp, W4PhysicalMgmt) & PM_mgmtData) != 0) {
		DPRINTF(5, (CE_CONT, "%s: no response from phy@%d",
			dp->name, dp->mii_phy_addr));
E 6
I 6
	if (INW(dp, W4PhysicalMgmt) & PM_mgmtData) {
		DPRINTF(2, (CE_CONT, "%s: no response from phy@%d",
		    dp->name, dp->mii_phy_addr));
		error = B_TRUE;
E 6
	}

	OUTW(dp, W4PhysicalMgmt, PM_mgmtClk);
	MDIO_DELAY(dp);

	for (i = 16; i > 0; i--) {
		OUTW(dp, W4PhysicalMgmt, 0);
		ret = (ret << 1) |
D 6
			((INW(dp, W4PhysicalMgmt) >> PM_mgmtDataShift) & 1);
E 6
I 6
		    ((INW(dp, W4PhysicalMgmt) >> PM_mgmtDataShift) & 1);
E 6
		OUTW(dp, W4PhysicalMgmt, PM_mgmtClk);
		MDIO_DELAY(dp);
	}

	/* send 2 ones to phy */
	for (i = 0; i < 2; i++) {
D 6
		OUTW(dp, W4PhysicalMgmt, PM_mgmtDir | PM_mgmtData);
E 6
I 6
		OUTW(dp, W4PhysicalMgmt,
		    PM_mgmtDir | PM_mgmtData);
E 6
		MDIO_DELAY(dp);
D 6
		OUTW(dp, W4PhysicalMgmt, PM_mgmtDir | PM_mgmtData | PM_mgmtClk);
E 6
I 6
		OUTW(dp, W4PhysicalMgmt,
		    PM_mgmtDir | PM_mgmtData | PM_mgmtClk);
E 6
		MDIO_DELAY(dp);
	}
I 7

	if (lp->media == xcvrSelectAN && reg == MII_STATUS) {
		if (INW(dp, W4MediaStatus) & MS_linkDetect) {
			ret |= MII_STATUS_LINKUP;
		}
	}

E 7
	REG_UNLOCK(lp);
D 6
#ifndef notdef
	if (reg == MII_STATUS) {
		if ((ret & MII_STATUS_100_BASEX) != 0) {
			ret |= MII_STATUS_100_BASEX_FD;
		}
		if ((ret & MII_STATUS_10) != 0) {
			ret |= MII_STATUS_10_FD;
		}
E 6
I 6

	if (error) {
		ret = 0;
E 6
	}
D 6
#endif
E 6
I 6
	DPRINTF(10, (CE_CONT, "%s:%s: reg:%d: val:0x%04x",
	    dp->name, __func__, reg, ret));
E 6
	return (ret);
}

static void
tcfe_mii_write(struct gem_dev *dp, uint_t reg, uint16_t val)
{
	int		i;
	uint32_t	cmd;
	uint16_t	data;
D 6
	struct tcfe_dev	*lp = (struct tcfe_dev *)dp->private;
E 6
I 6
	struct tcfe_dev	*lp = dp->private;
E 6

	cmd = MII_WRITE_CMD(dp->mii_phy_addr, reg, val);

	REG_LOCK(lp);
I 7
#ifdef WA_905B_10M
	if (lp->media == xcvrSelectAN && reg == MII_CONTROL) {
		uint32_t	ic;

		/* fix tranceiver selection */
		SET_WIN(dp, 3);
		ic = INL(dp, W3InternalConfig) & ~IC_xcvrSelect;
		ic |= xcvrSelectAN << IC_xcvrSelectShift;
		OUTL(dp, W3InternalConfig, ic);
	}
#endif
E 7
	SET_WIN(dp, 4);
	for (i = 31; i >= 0; i--) {
		data = ((cmd >> i) & 1) << PM_mgmtDataShift;
D 6
		OUTW(dp, W4PhysicalMgmt, data | PM_mgmtDir);
E 6
I 6
		OUTW(dp, W4PhysicalMgmt,
		    data | PM_mgmtDir);
E 6
		MDIO_DELAY(dp);
D 6
		OUTW(dp, W4PhysicalMgmt, data | PM_mgmtDir | PM_mgmtClk);
E 6
I 6
		OUTW(dp, W4PhysicalMgmt,
		    data | PM_mgmtDir | PM_mgmtClk);
E 6
		MDIO_DELAY(dp);
	}

	/* send 2 ones to phy */
	for (i = 0; i < 2; i++) {
D 6
		OUTW(dp, W4PhysicalMgmt, PM_mgmtDir | PM_mgmtData);
E 6
I 6
		OUTW(dp, W4PhysicalMgmt,
		    PM_mgmtDir | PM_mgmtData);
E 6
		MDIO_DELAY(dp);
D 6
		OUTW(dp, W4PhysicalMgmt, PM_mgmtDir | PM_mgmtData | PM_mgmtClk);
E 6
I 6
		OUTW(dp, W4PhysicalMgmt,
		    PM_mgmtDir | PM_mgmtData | PM_mgmtClk);
E 6
		MDIO_DELAY(dp);
	}
	REG_UNLOCK(lp);
}
#undef MDIO_DELAY

static void
tcfe_nomii_sync(struct gem_dev *dp)
{
	/* do nothing */
}

static uint16_t
tcfe_nomii_read(struct gem_dev *dp, uint_t index)
{
	uint16_t	ret;
D 6
	uint16_t	val;
	struct tcfe_dev	*lp = (struct tcfe_dev *)dp->private;
E 6
I 6
	struct tcfe_dev	*lp = dp->private;
E 6

	ret = 0;
	switch (index) {
	case MII_CONTROL:
		ret = lp->bmcr;
		break;
I 2

E 2
	case MII_STATUS:
		/* TODO: should return proper link status */
		/* setup capability */
D 6
		switch (lp->media) {
		case xcvrSelect100BASETX:
		case xcvrSelect100BASEFX:
			lp->bmsr = MII_STATUS_100_BASEX |
				   MII_STATUS_100_BASEX_FD;
			break;
E 6
I 6
		ret = lp->bmsr;
E 6

I 2
D 6
		case xcvrSelect10BASET:
			lp->bmsr = MII_STATUS_10 | MII_STATUS_10_FD;
			break;

E 2
		default:
			ASSERT(lp->media != xcvrSelectMII);
			ASSERT(lp->media != xcvrSelectMIIExt);
			ASSERT(lp->media != xcvrSelectAN);
			lp->bmsr = MII_STATUS_10;
			break;
		}
D 2
		ret = lp->bmsr;
#ifdef notdef
		val = ae_bcr_read(dp, LED0);
		if (val != LED0_DEFAULT) {
E 2
I 2

		ret = lp->bmsr & ~MII_STATUS_LINKUP;

E 6
		switch (lp->media) {
		case xcvrSelectAUI:
		case xcvrSelect10BASE2:
			/* no way to detect link up */
E 2
			ret |= MII_STATUS_LINKUP;
D 2
		}
E 2
I 2
			break;

		default:
D 3
#if 1
E 3
			REG_LOCK(lp);
			SET_WIN(dp, 4);
D 6
			val = INW(dp, W4MediaStatus);
			if ((val & MS_linkDetect) != 0) {
E 6
I 6
			if (INW(dp, W4MediaStatus) & MS_linkDetect) {
E 6
				ret |= MII_STATUS_LINKUP;
			}
			REG_UNLOCK(lp);
E 2
D 3
#else
D 2
		ret |= MII_STATUS_LINKUP;
E 2
I 2
			ret |= MII_STATUS_LINKUP;
E 2
#endif
E 3
I 2
			break;
		}
D 6

		lp->bmsr = ret;
E 6
E 2
		break;

	case MII_AN_ADVERT:
		ret = lp->adv;
		break;
	}
	return (ret);
}

static void
tcfe_nomii_write(struct gem_dev *dp, uint_t index, uint16_t val)
{
D 6
	struct tcfe_dev    *lp = (struct tcfe_dev *)dp->private;
E 6
I 6
	struct tcfe_dev    *lp = dp->private;
E 6

	switch (index) {
	case MII_CONTROL:
		lp->bmcr = val & ~MII_CONTROL_RESET;
		break;

	case MII_AN_ADVERT:
		lp->adv = val;
		break;

	default:
		cmn_err(CE_WARN,
D 6
		"!%s: %s: writing to register %d in phy isn't permitted.",
			dp->name, __func__, index);
E 6
I 6
		    "!%s: %s: writing to register %d in phy isn't permitted.",
		    dp->name, __func__, index);
E 6
		break;
	}
}

static char *tcfe_media_name[] = {
	"10BASET",		/* 0 */
	"AUI",			/* 1 */
	"(reserved)",		/* 2 */
	"10BASE2",		/* 3 */
	"100BASETX",		/* 4 */
	"100BASEFX",		/* 5 */
	"MII",			/* 6 */
	"(reserved)",		/* 7 */
D 4
	"10BASET w/ AN",	/* 8 */
E 4
I 4
	"10/100Mbps w/ AN",	/* 8 */
E 4
	"external MII",		/* 9 */
	"(reserved)",		/* 10 */
	"(reserved)",		/* 11 */
	"(reserved)",		/* 12 */
	"(reserved)",		/* 13 */
	"(reserved)",		/* 14 */
	"(reserved)",		/* 15 */
};

static int
D 6
tcfe_mii_init(struct gem_dev *dp)
E 6
I 6
tcfe_mii_probe(struct gem_dev *dp)
E 6
{
D 2
	uint32_t	val;
E 2
I 2
	uint32_t	ic;
E 2
	uint16_t	mopt;
I 2
	uint16_t	ms;
E 2
	uint32_t	port;
D 6
	struct tcfe_dev	*lp = (struct tcfe_dev *) dp->private;
E 6
I 6
	struct tcfe_dev	*lp = dp->private;
E 6

	/*
	 * select media here
	 */
D 3
#ifndef notdef
E 3
D 4
	OUTW(dp, W3MacControl, INW(dp, W3MacControl) | MC_fullDuplexEnable);
E 4
D 3
#endif
E 3
I 3

E 3
	/* read internal config register */
	REG_LOCK(lp);
I 2

	/*
	 * choose media port
	 */
E 2
	SET_WIN(dp, 3);
	mopt = INW(dp, W3MediaOptions);
	cmn_err(CE_CONT, "!%s: media options:%b",
D 6
		dp->name, mopt, 
		IS_3C90X(lp) ? MediaOptionsBits : MediaOptionsBits_BC);
E 6
I 6
	    dp->name, mopt,
	    IS_3C90X(lp) ? MediaOptionsBits : MediaOptionsBits_BC);
E 6

D 2
	val = INL(dp, W3InternalConfig);
E 2
I 2
	ic = INL(dp, W3InternalConfig);
E 2

	DPRINTF(0, (CE_CONT, "!%s: %s: internal_config:%b",
D 2
		dp->name, __func__, val, InternalConfigBits));
E 2
I 2
D 6
		dp->name, __func__, ic, InternalConfigBits));
E 6
I 6
	    dp->name, __func__, ic, InternalConfigBits));
E 6
E 2

D 2
	if ((val & IC_autoSelect) != 0) {
E 2
I 2
D 6
	if ((ic & IC_autoSelect) != 0) {
E 6
I 6
	if (ic & IC_autoSelect) {
E 6
E 2
		/* scan available media */
D 6
		if ((mopt & MO_baseT4Available) != 0) {
E 6
I 6
		if (mopt & MO_baseT4Available) {
E 6
			lp->media = xcvrSelectMII;
I 4
			/* XXX - should we use 100M full forced mode ? */
E 4
D 6
		}
I 4
		else if (IS_3C90XB_OR_LATER(lp) &&
			(mopt & (MO_baseTxAvailable | MO_10bTAvailable)) != 0) {
E 6
I 6
		} else
		if (IS_3C90XB_OR_LATER(lp) &&
		    (mopt & (MO_baseTxAvailable | MO_10bTAvailable))) {
E 6
			lp->media = xcvrSelectAN;
D 6
		}
E 4
		else if ((mopt & MO_baseTxAvailable) != 0) {
E 6
I 6
		} else if (mopt & MO_baseTxAvailable) {
E 6
D 4
			if (IS_3C90XB_OR_LATER(lp)) {
				lp->media = xcvrSelectAN;
			} else {
				lp->media = xcvrSelect100BASETX;
			}
E 4
I 4
			lp->media = xcvrSelect100BASETX;
E 4
D 6
		}
		else if ((mopt & MO_baseFxAvailable) != 0) {
E 6
I 6
		} else if (mopt & MO_baseFxAvailable) {
E 6
			lp->media = xcvrSelect100BASEFX;
D 6
		}
		else if ((mopt & MO_10BaseFL) != 0 && IS_3C90XB(lp)) {
E 6
I 6
		} else if ((mopt & MO_10BaseFL) && IS_3C90XB(lp)) {
E 6
			lp->media = xcvrSelectAUI;
D 6
		}
		else if ((mopt & MO_10bTAvailable) != 0) {
E 6
I 6
		} else if (mopt & MO_10bTAvailable) {
E 6
D 4
			if (IS_3C90XB_OR_LATER(lp)) {
				lp->media = xcvrSelectAN;
			} else {
				lp->media = xcvrSelect10BASET;
			}
E 4
I 4
			lp->media = xcvrSelect10BASET;
E 4
D 6
		}
		else if ((mopt & MO_miiDevice) != 0) {
E 6
I 6
		} else if (mopt & MO_miiDevice) {
E 6
			lp->media = xcvrSelectMII;
D 6
		}
		else {
E 6
I 6
		} else {
E 6
			lp->media = xcvrSelect10BASET;
		}

		/* fix tranceiver selection */
D 2
		val = (val & ~IC_xcvrSelect) |
E 2
I 2
		ic = (ic & ~IC_xcvrSelect) |
E 2
D 6
				(lp->media << IC_xcvrSelectShift);
	}
	else {
E 6
I 6
		    (lp->media << IC_xcvrSelectShift);
	} else {
E 6
D 2
		lp->media = (val & IC_xcvrSelect) >> IC_xcvrSelectShift;
E 2
I 2
		lp->media = (ic & IC_xcvrSelect) >> IC_xcvrSelectShift;
E 2
D 4
#ifdef notdef
E 4
I 4
D 6
#ifdef NEVER
E 4
		if (IS_CARDBUS(lp)) {
			lp->media = xcvrSelectAN;
D 2
			val = (val & ~IC_xcvrSelect) |
E 2
I 2
			ic = (ic & ~IC_xcvrSelect) |
E 2
					(lp->media << IC_xcvrSelectShift);
		}
#endif
E 6
	}
I 6

E 6
I 2
	OUTL(dp, W3InternalConfig, ic);
I 6
	lp->ic = ic;
E 6
E 2

D 6
	cmn_err(CE_CONT, "!%s: media %s[%d] selected",
		dp->name,
		tcfe_media_name[lp->media], lp->media);
E 6
I 6
	cmn_err(CE_CONT, "!%s: media %s[%d] selected, ic:0x%b",
	    dp->name, tcfe_media_name[lp->media], lp->media,
	    ic, InternalConfigBits);
E 6

I 2
	/*
	 * setup media
	 */
	SET_WIN(dp, 4);
	ms = INW(dp, W4MediaStatus);
D 6
	ms &= ~MS_enableSqeStats;
	ms &= ~MS_jabberGuardEnable;
	ms &= ~MS_linkBeatEnale;
E 6

I 6
	DPRINTF(0, (CE_CONT,
	    "!%s: ms:0x%b", dp->name, ms, MediaStatusBits));

	ms &= ~(MS_enableSqeStats | MS_jabberGuardEnable | MS_linkBeatEnale);
E 6
E 2
	switch (lp->media) {
	case xcvrSelectMII:
	case xcvrSelectAN:
D 4
		/* w/ auto negotiation capability and use MII */
E 4
I 4
D 6
		/* use MII with auto negotiation capability */
E 6
I 6
		/* use MII with autonegotiation capability */
E 6
E 4
		dp->mii_phy_addr = 0;
D 4
		if (IS_3C90XC(lp)) {
E 4
I 4
		if (lp->media == xcvrSelectAN) {
E 4
			dp->mii_phy_addr = 24;
		}
I 6
		if (IS_3C90XC(lp)) {
			ms |= MS_linkBeatEnale;
		}
E 6
		break;

D 2
	case xcvrSelect100BASEFX:
		/* w/o auto negotiation capability and use MII */
		dp->mii_fixedmode = B_TRUE;
		dp->speed = GEM_SPD_100;
		break;

E 2
	case xcvrSelect10BASET:
D 2
	case xcvrSelect10BASE2:
E 2
I 2
D 6
		dp->speed = GEM_SPD_10;
E 6
D 3
		ms |= MS_jabberGuardEnable| MS_linkBeatEnale;
E 3
I 3
		ms |= MS_jabberGuardEnable | MS_linkBeatEnale;
I 6
		lp->bmsr = MII_STATUS_10 | MII_STATUS_10_FD;
E 6
E 3
		goto non_mii;

E 2
	case xcvrSelectAUI:
I 2
D 6
		dp->speed = GEM_SPD_10;
E 6
		ms |= MS_enableSqeStats;
I 6
		lp->bmsr = MII_STATUS_10;
E 6
		goto non_mii;

	case xcvrSelect10BASE2:
D 6
		dp->speed = GEM_SPD_10;
E 6
I 6
		lp->bmsr = MII_STATUS_10;
E 6
		goto non_mii;

E 2
	case xcvrSelect100BASETX:
I 2
	case xcvrSelect100BASEFX:
D 6
		dp->speed = GEM_SPD_100;
E 6
		ms |= MS_linkBeatEnale;
I 6
		lp->bmsr = MII_STATUS_100_BASEX | MII_STATUS_100_BASEX_FD;
E 6
		goto non_mii;

	non_mii:
E 2
D 6
		dp->mii_fixedmode = B_TRUE;
D 2
		if (lp->media == xcvrSelect100BASETX) {
			dp->speed = GEM_SPD_100;
		} else {
			dp->speed = GEM_SPD_10;
		}
E 2
		dp->gc.gc_mii_sync  = &tcfe_nomii_sync;
		dp->gc.gc_mii_read  = &tcfe_nomii_read;
E 6
I 6
		dp->gc.gc_mii_sync = &tcfe_nomii_sync;
		dp->gc.gc_mii_read = &tcfe_nomii_read;
E 6
		dp->gc.gc_mii_write = &tcfe_nomii_write;

		/* no need to scan phy */
		dp->mii_phy_addr = -1;
		break;

	default:
	case xcvrSelectMIIExt:
I 4
		REG_UNLOCK(lp);
E 4
		cmn_err(CE_WARN,
D 6
			"!%s: unknow media in InternalConfig: media:%d",
			dp->name, lp->media);
E 6
I 6
		    "!%s: unknown media in InternalConfig: media:%d",
		    dp->name, lp->media);
E 6
		return (GEM_FAILURE);
	}
I 6

E 6
I 2
	SET_WIN(dp, 4);
	OUTW(dp, W4MediaStatus, ms);
I 6
	lp->ms = ms;
E 6
E 2

D 2
	OUTL(dp, W3InternalConfig, val);
E 2
	REG_UNLOCK(lp);

D 6
	if (gem_mii_init_default(dp) == GEM_SUCCESS) {
I 4
#if DEBUG_LEVEL > 4
		int	i;
		for (i = 0; i < 32; i++) {
			DPRINTF(0, (CE_CONT, "%s: mii reg%d:%04x",
				dp->name, i, gem_mii_read(dp, i)));
		}
#endif
E 6
I 6
	lp->mii_initialized = B_TRUE;

	return (gem_mii_probe_default(dp));
}

static int
tcfe_mii_init(struct gem_dev *dp)
{
	struct tcfe_dev	*lp = dp->private;

	if (lp->mii_initialized) {
E 6
E 4
		return (GEM_SUCCESS);
	}
D 6
#ifdef notdef
	if (IS_3C90XB(lp)) {
		/* check built-in 10baseT port */
		REG_LOCK(lp);
		SET_WIN(dp, 3);
		val = INL(dp, W3InternalConfig);
		val = (val & ~IC_xcvrSelect) | IC_xcvrSelectAN;
		OUTL(dp, W3InternalConfig, val);
		REG_UNLOCK(lp);
E 6

D 6
		DPRINTF(0, (CE_CONT, "!%s: %s: internal_config:%b",
			dp->name, __func__, val, InternalConfigBits));
E 6
I 6
	REG_LOCK(lp);
E 6

D 6
		/* search phy again */
		dp->mii_phy_addr = 0;
		if (gem_mii_init_default(dp) == GEM_SUCCESS) {
			return (GEM_SUCCESS);
		}
	}
#endif
	return (GEM_FAILURE);
}
E 6
I 6
	SET_WIN(dp, 3);
	OUTL(dp, W3InternalConfig, lp->ic);
E 6

I 6
	SET_WIN(dp, 4);
	OUTW(dp, W4MediaStatus, lp->ms);
E 6

I 6
	REG_UNLOCK(lp);

	return (GEM_SUCCESS);
}

E 6
D 3
static uint16_t
E 3
I 3
static int
E 3
tcfe_read_eeprom(struct gem_dev *dp, uint_t offset)
{
	int		i;
	uint16_t	eecmd;
	uint16_t	val;
D 6
	struct tcfe_dev	*lp = (struct tcfe_dev *)dp->private;
E 6
I 6
	struct tcfe_dev	*lp = dp->private;
E 6

	/* window should be write-locked */
D 3
#ifdef notdef
	eecmd = offset + lp->chip->ee_offset;
#else
E 3
	eecmd = offset;
D 3
#endif
E 3
I 3

E 3
D 6
	if ((lp->chip->flags & EEADDRSIZE_8) != 0) {
E 6
I 6
	if (lp->chip->flags & EEADDRSIZE_8) {
E 6
		eecmd |= (EE_ReadRegister << (8 - 2));
	} else {
		eecmd |= (EE_ReadRegister << (6 - 2));
	}

	REG_LOCK(lp);
	SET_WIN(dp, 0);
	OUTW(dp, W0EepromCommand, eecmd);
	drv_usecwait(162);

D 6
	for (i = 0; (INW(dp, W0EepromCommand) & EC_eepromBusy) != 0; i++) {
E 6
I 6
	for (i = 0; (INW(dp, W0EepromCommand) & EC_eepromBusy); i++) {
E 6
		if (i > 20) {
I 4
			REG_UNLOCK(lp);
E 4
D 7
			cmn_err(CE_WARN, "!%s: %s: timeout",
D 6
				dp->name, __func__);
			return (-1);
E 6
I 6
			    dp->name, __func__);
E 7
I 7
			cmn_err(CE_WARN,
			    "!%s: %s: timeout, offset 0x%x, flags 0x%x",
			    dp->name, __func__, offset, lp->chip->flags);
E 7
			return (0);
E 6
		}
		drv_usecwait(10);
	}

	val = INW(dp, W0EepromData);
	REG_UNLOCK(lp);

	return (val);
}

#ifdef DEBUG_LEVEL
static void
tcfe_eeprom_dump(struct gem_dev *dp)
{
	int		i;
	uint16_t	*prom;
D 7
	uint16_t	sum;
E 7
I 7
	uint8_t		sum;
E 7
	int		epsize;
D 6
	struct tcfe_dev	*lp = (struct tcfe_dev *)dp->private;
E 6
I 6
	struct tcfe_dev	*lp = dp->private;
E 6

	epsize = 0x21;
	if (IS_CARDBUS(lp)) {
		epsize = 0x80;
	}
	/* allocate temporary buffer for reading eeprom contents */
D 6
	prom = (uint16_t *) kmem_alloc(epsize * sizeof(uint16_t), KM_SLEEP);
E 6
I 6
	prom = kmem_alloc(epsize * sizeof (uint16_t), KM_SLEEP);
E 6

	for (i = 0; i < epsize; i++) {
		prom[i] = tcfe_read_eeprom(dp, i);
	}
	/* calculate checksum for eeprom area */
	sum = 0;
	for (i = 0; i < 0x20; i++) {
D 7
		sum += prom[i + lp->chip->ee_offset];
E 7
I 7
		uint16_t	val;
		val = prom[i + lp->chip->ee_offset];
		sum ^= (val >> 8) ^ val;
		DPRINTF(10, (CE_CONT, "!%s: %x: sum:%x", __func__, i, sum));
E 7
	}

	cmn_err(CE_CONT, "!%s: eeprom dump:", dp->name);
	for (i = 0; i < epsize; i += 4) {
D 6
		cmn_err(CE_CONT, "!0x%02x: 0x%04x 0x%04x 0x%04x 0x%04x", 
			i, prom[i], prom[i + 1], prom[i + 2], prom[i + 3]);
E 6
I 6
		cmn_err(CE_CONT, "!0x%02x: 0x%04x 0x%04x 0x%04x 0x%04x",
		    i, prom[i], prom[i + 1], prom[i + 2], prom[i + 3]);
E 6
	}
	cmn_err(CE_CONT, "!sum[00-1f]: 0x%04x", sum);

D 6
	kmem_free(prom, epsize * sizeof(uint16_t));
E 6
I 6
	kmem_free(prom, epsize * sizeof (uint16_t));
E 6
}
#endif /* DEBUG_LEVEL */

D 7
#ifdef notdef
E 7
I 7
#if 0
E 7
#include "tcfe_eeprom_wr.c"
#endif

static int
D 6
tcfe_attach_chip(struct gem_dev *dp)	
E 6
I 6
tcfe_attach_chip(struct gem_dev *dp)
E 6
{
	int		i;
D 3
	uint16_t	val;
E 3
I 3
	int		val;
E 3
	uint8_t		*mac;
D 6
	struct tcfe_dev	*lp = (struct tcfe_dev *)dp->private;
E 6
I 6
	struct tcfe_dev	*lp = dp->private;
I 7
	static uint8_t	zero6[] = {0, 0, 0, 0, 0, 0,};
	static uint8_t	bcast[] = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff,};
E 7
E 6

D 7
#if DEBUG_LEVEL > 0
E 7
I 7
#if 0
	tcfe_fix_eeprom905b(dp);
#endif

#if DEBUG_LEVEL > 1
E 7
	tcfe_eeprom_dump(dp);
#endif

D 6
#ifdef notdef
E 6
I 6
#ifdef NEVER
E 6
	/* fix eeprom contents */
	val = tcfe_read_eeprom(dp,
D 6
			EO_SoftwareIntormation + lp->chip->ee_offset);
E 6
I 6
	    EO_SoftwareIntormation + lp->chip->ee_offset);
E 6

	tcfe_exec_eeprom_cmd(dp, EE_WriteEnable, 0, 0);
	tcfe_exec_eeprom_cmd(dp, EE_EraseRegister,
D 6
			EO_SoftwareIntormation + lp->chip->ee_offset, 0);
E 6
I 6
	    EO_SoftwareIntormation + lp->chip->ee_offset, 0);
E 6

	tcfe_exec_eeprom_cmd(dp, EE_WriteEnable, 0, 0);
	tcfe_exec_eeprom_cmd(dp, EE_WriteRegister,
D 6
			EO_SoftwareIntormation + lp->chip->ee_offset,
			val | 0x8000);
E 6
I 6
	    EO_SoftwareIntormation + lp->chip->ee_offset,
	    val | 0x8000);
E 6

	tcfe_exec_eeprom_cmd(dp, EE_WriteDisable, 0, 0);
D 7
#if DEBUG_LEVEL > 0
E 7
I 7
#endif /* NEVER */
#if DEBUG_LEVEL > -1
E 7
	tcfe_eeprom_dump(dp);
#endif
D 6
#endif
E 6
I 6
D 7
#endif /* NEVER */
E 7
E 6

	mac = &dp->dev_addr.ether_addr_octet[0];
	for (i = 0; i < ETHERADDRL; i += 2) {
		val = tcfe_read_eeprom(dp,
D 6
				EO_OEMNodeAddress + i/2 + lp->chip->ee_offset);
E 6
I 6
		    EO_OEMNodeAddress + i/2 + lp->chip->ee_offset);
E 6
I 3
		if (val < 0) {
			return (GEM_FAILURE);
		}
E 3
		/* the station address is stored in network byteorder */
D 6
		mac[i]     = (uint8_t) (val >> 8);
		mac[i + 1] = (uint8_t) val;
E 6
I 6
		mac[i + 0] = (uint8_t)(val >> 8);
		mac[i + 1] = (uint8_t)val;
E 6
	}
D 7
#ifdef notdef
	gem_get_mac_addr_conf(dp);
#endif
E 7
I 7

	if (bcmp(mac, zero6, ETHERADDRL) == 0 || (mac[0] & 0x1) ||
	    bcmp(mac, bcast, ETHERADDRL) == 0) {
		gem_generate_macaddr(dp, mac);
	}

E 7
D 2
	dp->txmaxdma = max(dp->txmaxdma, 256);
	dp->rxmaxdma = max(dp->rxmaxdma, 256);
E 2
I 2
	dp->txmaxdma = max(dp->txmaxdma, 512);
	dp->rxmaxdma = max(dp->rxmaxdma, 512);
E 2

D 3
#if defined(GEM_CONFIG_CKSUM_OFFLOAD) && defined(CONFIG_VLAN)
E 3
I 3
#ifdef GEM_CONFIG_CKSUM_OFFLOAD
E 3
	if (IS_3C90XB_OR_LATER(lp)) {
D 3
		dp->misc_flag |= GEM_VLAN_HARD;
E 3
D 6
		dp->misc_flag |= (GEM_CKSUM_FULL_IPv4 | GEM_CKSUM_HEADER_IPv4);
D 3
	}
#elif defined(GEM_CONFIG_CKSUM_OFFLOAD)
E 3
I 3
	} 
#endif
#ifdef CONFIG_VLAN
E 3
	if (IS_3C90XB_OR_LATER(lp)) {
D 3
		dp->misc_flag |= (GEM_CKSUM_FULL_IPv4 | GEM_CKSUM_HEADER_IPv4);
E 3
I 3
		dp->misc_flag |= GEM_VLAN_HARD;
	} else {
		dp->misc_flag |= GEM_VLAN_SOFT;
E 6
I 6
		dp->misc_flag |= GEM_CKSUM_FULL_IPv4 | GEM_CKSUM_HEADER_IPv4;
E 6
E 3
	}
D 3
        dp->misc_flag |= GEM_VLAN_SOFT;
E 3
#endif
I 6
#ifdef GEM_CONFIG_GLDv3
	dp->misc_flag |= GEM_VLAN_SOFT;
#endif
	dp->misc_flag |= GEM_POLL_RXONLY;

E 6
I 3
D 4

E 4
E 3
	return (GEM_SUCCESS);
}

/* ======================================================== */
/*
 * OS depend (device driver) routine
 */
/* ======================================================== */
static int
tcfeattach(dev_info_t *dip, ddi_attach_cmd_t cmd)
{
	int			i;
	int			n;
	ddi_iblock_cookie_t	c;
	ddi_acc_handle_t	conf_handle;
	uint16_t		comm;
	int			ret;
	int			vid;
	int			did;
	int			unit;
	struct chip_info	*p;
	int			val;
	int			len;
	struct pci_phys_spec	*regs;
	const char		*drv_name;
	struct gem_dev		*dp;
	struct tcfe_dev		*lp;
D 6
	void			*base;
	void			*base2;
E 6
I 6
	caddr_t			base;
	caddr_t			base2;
E 6
	ddi_acc_handle_t	regs_handle;
	ddi_acc_handle_t	regs2_handle;
	struct gem_conf		*gcp;
	uint8_t			revid;
	uint8_t			lat;
	uint32_t		iline;

D 6
	unit =  ddi_get_instance(dip);
E 6
I 6
	unit = ddi_get_instance(dip);
E 6
	drv_name = ddi_driver_name(dip);

	DPRINTF(3, (CE_CONT, "%s%d: tcfeattach: called", drv_name, unit));

	/*
	 * Check if chip is supported.
	 */
	if (pci_config_setup(dip, &conf_handle) != DDI_SUCCESS) {
D 6
		cmn_err(CE_WARN, "%s: ddi_regs_map_setup failed",
			drv_name);
E 6
I 6
		cmn_err(CE_WARN, "%s: ddi_regs_map_setup failed", drv_name);
E 6
		goto err;
	}
D 6
	vid  = pci_config_get16(conf_handle, PCI_CONF_VENID);
	did  = pci_config_get16(conf_handle, PCI_CONF_DEVID);
	revid= pci_config_get8(conf_handle, PCI_CONF_REVID);
E 6
I 6
	vid = pci_config_get16(conf_handle, PCI_CONF_VENID);
	did = pci_config_get16(conf_handle, PCI_CONF_DEVID);
	revid = pci_config_get8(conf_handle, PCI_CONF_REVID);
E 6
	comm = pci_config_get16(conf_handle, PCI_CONF_COMM);
D 6
	lat  = pci_config_get8(conf_handle, PCI_CONF_LATENCY_TIMER);
	iline  = pci_config_get32(conf_handle, PCI_CONF_ILINE);
E 6
I 6
	lat = pci_config_get8(conf_handle, PCI_CONF_LATENCY_TIMER);
	iline = pci_config_get32(conf_handle, PCI_CONF_ILINE);
E 6
	comm |= PCI_COMM_IO | PCI_COMM_ME | PCI_COMM_MAE;
	pci_config_put16(conf_handle, PCI_CONF_COMM, comm);

	pci_config_teardown(&conf_handle);

	switch (cmd) {
	case DDI_RESUME:
I 6
		dp = GEM_GET_DEV(dip);
		lp = dp->private;
		lp->mii_initialized = B_FALSE;
E 6
		return (gem_resume(dip));

	case DDI_ATTACH:
		for (i = 0, p = tcfe_chiptbl; i < CHIPTABLESIZE; i++, p++) {
			if (p->venid == vid && p->devid == did) {
				/* found */
				cmn_err(CE_CONT,
D 6
"!%s%d: %s (vid: 0x%04x, did: 0x%04x, revid: 0x%02x, latency timer: 0x%02x)",
				drv_name, unit, p->name, vid, did, revid, lat);
E 6
I 6
				    "!%s%d: %s (vid: 0x%04x, did: 0x%04x,"
				    " revid: 0x%02x, latency timer: 0x%02x)",
				    drv_name, unit, p->name,
				    vid, did, revid, lat);
E 6
				goto chip_found;
			}
		}

		/* Not found */
		cmn_err(CE_WARN,
D 6
			"%s: tcfe_attach: wrong PCI venid/devid (0x%x, 0x%x)",
			drv_name, vid, did);
E 6
I 6
		    "%s: tcfe_attach: wrong PCI venid/devid (0x%x, 0x%x)",
		    drv_name, vid, did);
E 6
		p--;
chip_found:
D 6
		DPRINTF(0, (CE_CONT,
			"%s: tcfe_attach: iline %08x", drv_name, iline));
E 6
I 6
		DPRINTF(2, (CE_CONT,
		    "%s: %s: iline %08x", drv_name, __func__, iline));
E 6
		/*
		 * Map in the device registers.
		 */
		if (gem_pci_regs_map_setup(dip,
D 6
			PCI_ADDR_IO, PCI_ADDR_MASK,
			&tcfe_dev_attr,
			(caddr_t *)&base, &regs_handle) != DDI_SUCCESS) {
E 6
I 6
		    PCI_ADDR_IO, PCI_ADDR_MASK,
		    &tcfe_dev_attr,
		    &base, &regs_handle) != DDI_SUCCESS) {
E 6
			goto err;
		}

		regs2_handle = NULL;
D 6
		if ((p->flags & CHIP_CARDBUS) != 0) {
E 6
I 6
		if (p->flags & CHIP_CARDBUS) {
E 6
			if (gem_pci_regs_map_setup(dip,
D 6
				PCI_CONF_BASE2, PCI_REG_REG_M,
				&tcfe_dev_attr,
				(caddr_t *)&base2, &regs2_handle)
							!= DDI_SUCCESS) {
E 6
I 6
			    PCI_CONF_BASE2, PCI_REG_REG_M,
			    &tcfe_dev_attr,
			    &base2, &regs2_handle)
			    != DDI_SUCCESS) {
E 6
				ddi_regs_map_free(&regs_handle);
				goto err;
			}
		}

I 4
D 6
		lp = kmem_zalloc(sizeof(struct tcfe_dev), KM_SLEEP);
E 6
I 6
		lp = kmem_zalloc(sizeof (struct tcfe_dev), KM_SLEEP);
E 6
		lp->rev_id = revid;
D 6
		lp->chip   = p;
		lp->base2  = base2;
E 6
I 6
		lp->chip = p;
		lp->base2 = base2;
E 6
		lp->base2_ha = regs2_handle;

E 4
		/*
		 * construct gem configration
		 */
D 6
		gcp = (struct gem_conf *) kmem_zalloc(sizeof(*gcp), KM_SLEEP);
E 6
I 6
		gcp = kmem_zalloc(sizeof (*gcp), KM_SLEEP);
E 6

		/* name */
		sprintf(gcp->gc_name, "%s%d", drv_name, unit);

		/* consistency on tx and rx */
D 6
		gcp->gc_tx_buf_align   = sizeof(uint8_t) - 1;
E 6
I 6
		gcp->gc_tx_buf_align = sizeof (uint8_t) - 1;
E 6
I 4
D 7
#if 0
		/*
		 * XXX - 3c90x seems to hang on rx in multi tx fragment
		 * configuration.
		 */
E 4
D 6
		gcp->gc_tx_max_frags   =
D 4
			((p->flags & CHIP_TYPE) >= CHIP_TYPE_90XB)
						? MAXTXFRAGS : 1;
E 4
I 4
				IS_3C90XB_OR_LATER(lp) ? MAXTXFRAGS : 1;
E 6
I 6
		gcp->gc_tx_max_frags =
		    IS_3C90XB_OR_LATER(lp) ? MAXTXFRAGS : 1;
E 6
#else
E 7
D 6
		gcp->gc_tx_max_frags   = MAXTXFRAGS;
E 6
I 6
		gcp->gc_tx_max_frags = MAXTXFRAGS;
E 6
D 7
#endif
E 7
E 4
		gcp->gc_tx_max_descs_per_pkt = 1;
D 4
		gcp->gc_tx_desc_unit_shift = DN_LIST_SIZE_SHIFT;/* 64 byte */
E 4
I 4
		gcp->gc_tx_desc_unit_shift = DN_LIST_SIZE_SHIFT; /* 64 byte */
E 4
D 6
		gcp->gc_tx_buf_size    = TX_BUF_SIZE;
		gcp->gc_tx_buf_limit   = gcp->gc_tx_buf_size - 1;
		gcp->gc_tx_ring_size   = TX_RING_SIZE;
D 4
		gcp->gc_tx_ring_limit  = gcp->gc_tx_ring_size - 1;
E 4
I 4
		gcp->gc_tx_ring_limit  = min(TX_BUF_SIZE, TX_RING_SIZE - 1);
E 4
		gcp->gc_tx_auto_pad    = B_FALSE;
E 6
I 6
		gcp->gc_tx_buf_size = TX_BUF_SIZE;
D 7
		gcp->gc_tx_buf_limit = gcp->gc_tx_buf_size - 1;
E 7
I 7
		gcp->gc_tx_buf_limit = gcp->gc_tx_buf_size;
E 7
		gcp->gc_tx_ring_size = TX_RING_SIZE;
D 7
		gcp->gc_tx_ring_limit = min(TX_BUF_SIZE, TX_RING_SIZE - 1);
E 7
I 7
		gcp->gc_tx_ring_limit = gcp->gc_tx_ring_size - 1;
E 7
		gcp->gc_tx_auto_pad = B_FALSE;
E 6
		gcp->gc_tx_copy_thresh = tcfe_tx_copy_thresh;
I 4
D 6
#ifdef CONFIG_OO
		gcp->gc_tx_desc_write_oo = TX_BUF_SIZE == TX_RING_SIZE;
#else
E 4
		gcp->gc_tx_desc_write_oo = B_FALSE;
E 6
I 6
#ifndef GEM_CONFIG_TX_DIRECT
		gcp->gc_tx_desc_write_oo = (TX_BUF_SIZE == TX_RING_SIZE);
E 6
D 4

E 4
I 4
#endif
E 4
D 6
		gcp->gc_rx_buf_align   = sizeof(uint8_t) - 1;
		gcp->gc_rx_max_frags   = MAXRXFRAGS;
E 6
I 6

		gcp->gc_rx_buf_align	= sizeof (uint8_t) - 1;
		gcp->gc_rx_max_frags	= MAXRXFRAGS;
E 6
D 4
		gcp->gc_rx_desc_unit_shift = UP_LIST_SIZE_SHIFT;/* 32 byte */
E 4
I 4
		gcp->gc_rx_desc_unit_shift = UP_LIST_SIZE_SHIFT; /* 32 byte */
E 4
D 6
		gcp->gc_rx_ring_size   = RX_RING_SIZE;
D 4
		gcp->gc_rx_buf_max     = RX_BUF_SIZE - 1;
E 4
I 4
		gcp->gc_rx_buf_max     = RX_RING_SIZE - 1;
E 4
		gcp->gc_rx_copy_thresh = tcfe_rx_copy_thresh;
		gcp->gc_rx_header_len  = 0;
E 6
I 6
		gcp->gc_rx_ring_size	= RX_RING_SIZE;
D 7
		gcp->gc_rx_buf_max	= RX_RING_SIZE - 1;
E 7
I 7
		gcp->gc_rx_buf_max	= gcp->gc_rx_ring_size;
E 7
		gcp->gc_rx_copy_thresh	= tcfe_rx_copy_thresh;
		gcp->gc_rx_header_len	= 0;
E 6

		gcp->gc_io_area_size = 0;

		/* map attributes */
D 3
		STRUCT_COPY(gcp->gc_dev_attr, tcfe_dev_attr);
		STRUCT_COPY(gcp->gc_buf_attr, tcfe_buf_attr);
		STRUCT_COPY(gcp->gc_desc_attr, tcfe_buf_attr);
E 3
I 3
		gcp->gc_dev_attr = tcfe_dev_attr;
		gcp->gc_buf_attr = tcfe_buf_attr;
		gcp->gc_desc_attr = tcfe_buf_attr;
E 3

		/* dma attributes */
D 3
		STRUCT_COPY(gcp->gc_dma_attr_desc, tcfe_dma_attr_desc);
		STRUCT_COPY(gcp->gc_dma_attr_txbuf, tcfe_dma_attr_buf);
E 3
I 3
		gcp->gc_dma_attr_desc = tcfe_dma_attr_desc;
		gcp->gc_dma_attr_txbuf = tcfe_dma_attr_buf;
E 3
		gcp->gc_dma_attr_txbuf.dma_attr_sgllen = gcp->gc_tx_max_frags;
D 3
		STRUCT_COPY(gcp->gc_dma_attr_rxbuf, tcfe_dma_attr_buf);
E 3
I 3
		gcp->gc_dma_attr_rxbuf = tcfe_dma_attr_buf;
E 3
		gcp->gc_dma_attr_rxbuf.dma_attr_sgllen = gcp->gc_rx_max_frags;

		/* time out parameters */
D 7
		gcp->gc_tx_timeout = 3*ONESEC;
		gcp->gc_tx_timeout_interval = ONESEC;
E 7
I 7
		gcp->gc_tx_timeout = GEM_TX_TIMEOUT;
		gcp->gc_tx_timeout_interval = GEM_TX_TIMEOUT_INTERVAL;
E 7

		/* flow control */
		gcp->gc_flow_control = FLOW_CONTROL_SYMMETRIC;

		/* MII timeout parameters */
		gcp->gc_mii_link_watch_interval = ONESEC;
D 6
		gcp->gc_mii_an_watch_interval   = ONESEC/5;
E 6
I 6
		gcp->gc_mii_an_watch_interval = ONESEC/5;
E 6
		gcp->gc_mii_reset_timeout = MII_RESET_TIMEOUT;	/* 1 sec */
		gcp->gc_mii_an_timeout = MII_AN_TIMEOUT;	/* 5 sec */
		gcp->gc_mii_an_wait = 0;
		gcp->gc_mii_linkdown_timeout = MII_LINKDOWN_TIMEOUT;

		/* MII work arounds */
		gcp->gc_mii_addr_min = 0;
		gcp->gc_mii_an_delay = 0;
		gcp->gc_mii_linkdown_action = MII_ACTION_RSA;
		gcp->gc_mii_linkdown_timeout_action = MII_ACTION_RESET;
		gcp->gc_mii_dont_reset = B_FALSE;
I 7
#ifdef WA_905B_10M
		/* not worked, link up but ping failed */
		gcp->gc_mii_an_oneshot = B_TRUE;
#endif
E 7

		/* I/O methods */

		/* mac operation */
		gcp->gc_attach_chip = &tcfe_attach_chip;
D 6
		gcp->gc_reset_chip  = &tcfe_reset_chip;
		gcp->gc_init_chip   = &tcfe_init_chip;
		gcp->gc_start_chip  = &tcfe_start_chip;
		gcp->gc_stop_chip   = &tcfe_stop_chip;
E 6
I 6
		gcp->gc_reset_chip = &tcfe_reset_chip;
		gcp->gc_init_chip = &tcfe_init_chip;
		gcp->gc_start_chip = &tcfe_start_chip;
		gcp->gc_stop_chip = &tcfe_stop_chip;
E 6
		gcp->gc_multicast_hash = &tcfe_mcast_hash;
		gcp->gc_set_rx_filter = &tcfe_set_rx_filter;
D 6
		gcp->gc_set_media   = &tcfe_set_media;
		gcp->gc_get_stats   = &tcfe_get_stats;
		gcp->gc_interrupt   = &tcfe_interrupt;
E 6
I 6
		gcp->gc_set_media = &tcfe_set_media;
		gcp->gc_get_stats = &tcfe_get_stats;
		gcp->gc_interrupt = &tcfe_interrupt;
E 6

		/* descriptor operation */
		gcp->gc_tx_desc_write = &tcfe_tx_desc_write;
D 6
		gcp->gc_tx_start      = &tcfe_tx_start;
E 6
I 6
		gcp->gc_tx_start = &tcfe_tx_start;
E 6
		gcp->gc_rx_desc_write = &tcfe_rx_desc_write;
D 6
		gcp->gc_rx_start      = &tcfe_rx_start;
E 6
I 6
		gcp->gc_rx_start = &tcfe_rx_start;
E 6

		gcp->gc_tx_desc_init = &tcfe_tx_desc_init;
		gcp->gc_rx_desc_init = &tcfe_rx_desc_init;
I 7
#if defined(GEM_CONFIG_TX_HEAD_PTR) && defined(CONFIG_TX_AUTO_POLL)
		if (IS_3C90XB_OR_LATER(lp)) {
			gcp->gc_tx_desc_stat = &tcfe_tx_desc_stat;
		} else {
			gcp->gc_tx_desc_head = &tcfe_tx_desc_head;
		}
#else
E 7
		gcp->gc_tx_desc_stat = &tcfe_tx_desc_stat;
I 7
#endif
E 7
		gcp->gc_rx_desc_stat = &tcfe_rx_desc_stat;
		gcp->gc_tx_desc_clean = &tcfe_tx_desc_clean;
		gcp->gc_rx_desc_clean = &tcfe_rx_desc_clean;

		/* mii operations */
D 6
		gcp->gc_mii_init  = &tcfe_mii_init;
E 6
I 6
		gcp->gc_mii_probe = &tcfe_mii_probe;
		gcp->gc_mii_init = &tcfe_mii_init;
E 6
		gcp->gc_mii_config = &gem_mii_config_default;
D 6
		gcp->gc_mii_sync  = &tcfe_mii_sync;
		gcp->gc_mii_read  = &tcfe_mii_read;
E 6
I 6
		gcp->gc_mii_sync = &tcfe_mii_sync;
		gcp->gc_mii_read = &tcfe_mii_read;
E 6
		gcp->gc_mii_write = &tcfe_mii_write;
		gcp->gc_mii_tune_phy = NULL;

D 4
		lp = kmem_zalloc(sizeof(struct tcfe_dev), KM_SLEEP);
		lp->rev_id = revid;
		lp->chip   = p;
		lp->base2  = base2;
		lp->base2_ha = regs2_handle;

E 4
		mutex_init(&lp->reglock, NULL, MUTEX_DRIVER, NULL);
I 7
		mutex_init(&lp->cmdlock, NULL, MUTEX_DRIVER, NULL);

		/* offload and jumbo frame */
		gcp->gc_max_lso = 0;
		gcp->gc_max_mtu = TCFE_MAX_PACKET_SIZE -
		    (sizeof (struct ether_header) + ETHERFCSL + 4);
		gcp->gc_default_mtu = ETHERMTU;
		gcp->gc_min_mtu = ETHERMIN - sizeof (struct ether_header);

E 7
D 6
		dp = gem_do_attach(dip, gcp, base, &regs_handle,
					lp, sizeof(*lp));
E 6
I 6
		dp = gem_do_attach(dip,
		    0, gcp, base, &regs_handle, lp, sizeof (*lp));
E 6

D 6
		kmem_free(gcp, sizeof(*gcp));
E 6
I 6
		kmem_free(gcp, sizeof (*gcp));
E 6

		if (dp != NULL) {
D 3
			return DDI_SUCCESS;
E 3
I 3
			return (DDI_SUCCESS);
E 3
		}

		mutex_destroy(&lp->reglock);
I 7
		mutex_destroy(&lp->cmdlock);
E 7
err_free_mem:
D 6
		kmem_free(lp, sizeof(struct tcfe_dev));
E 6
I 6
		kmem_free(lp, sizeof (struct tcfe_dev));
E 6
err:
D 3
		return DDI_FAILURE;
E 3
I 3
		return (DDI_FAILURE);
E 3
	}
D 3
	return DDI_FAILURE;
E 3
I 3
	return (DDI_FAILURE);
E 3
}

static int
tcfedetach(dev_info_t *dip, ddi_detach_cmd_t cmd)
{
	int	ret;
	struct gem_dev  *dp;
	struct tcfe_dev   *lp;

	dp = GEM_GET_DEV(dip);
D 6
	lp = (struct tcfe_dev *) dp->private;
E 6
I 6
	lp = dp->private;
E 6

D 6
        switch (cmd) {
        case DDI_DETACH:
E 6
I 6
	switch (cmd) {
	case DDI_DETACH:
E 6
		if (lp->base2_ha != NULL) {
			ddi_regs_map_free(&lp->base2_ha);
		}
		mutex_destroy(&lp->reglock);
I 7
		mutex_destroy(&lp->cmdlock);
E 7
		return (gem_do_detach(dip));

	case DDI_SUSPEND:
		return (gem_suspend(dip));
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
GEM_STREAM_OPS(tcfe_ops, tcfeattach, tcfedetach);
#else
E 6
static	struct module_info tcfeminfo = {
	0,			/* mi_idnum */
	"tcfe",			/* mi_idname */
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

static	struct qinit tcferinit = {
	(int (*)()) NULL,	/* qi_putp */
	gem_rsrv,		/* qi_srvp */
	gem_open,		/* qi_qopen */
	gem_close,		/* qi_qclose */
	(int (*)()) NULL,	/* qi_qadmin */
	&tcfeminfo,		/* qi_minfo */
	NULL			/* qi_mstat */
};

static	struct qinit tcfewinit = {
	gem_wput,		/* qi_putp */
	gem_wsrv,		/* qi_srvp */
	(int (*)()) NULL,	/* qi_qopen */
	(int (*)()) NULL,	/* qi_qclose */
	(int (*)()) NULL,	/* qi_qadmin */
	&tcfeminfo,		/* qi_minfo */
	NULL			/* qi_mstat */
};

static struct streamtab	tcfe_info = {
	&tcferinit,	/* st_rdinit */
	&tcfewinit,	/* st_wrinit */
	NULL,		/* st_muxrinit */
	NULL		/* st_muxwrinit */
};

static	struct cb_ops cb_tcfe_ops = {
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
	&tcfe_info,	/* cb_stream */
	D_NEW|D_MP	/* cb_flag */
};

static	struct dev_ops tcfe_ops = {
	DEVO_REV,	/* devo_rev */
	0,		/* devo_refcnt */
	gem_getinfo,	/* devo_getinfo */
	nulldev,	/* devo_identify */
	nulldev,	/* devo_probe */
	tcfeattach,	/* devo_attach */
	tcfedetach,	/* devo_detach */
	nodev,		/* devo_reset */
	&cb_tcfe_ops,	/* devo_cb_ops */
	NULL,		/* devo_bus_ops */
	ddi_power	/* devo_power */
};
I 6
#endif /* GEM_CONFIG_GLDv3 */
E 6

static struct modldrv modldrv = {
D 6
	&mod_driverops,	/* Type of module.  This one is a driver */
E 6
I 6
	&mod_driverops,
E 6
	ident,
D 6
	&tcfe_ops,	/* driver ops */
E 6
I 6
	&tcfe_ops,
E 6
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

D 4
	DPRINTF(2, (CE_CONT, "tcfe: _init: called"));
	status = mod_install(&modlinkage);
E 4
I 4
	DPRINTF(2, (CE_CONT, "!tcfe: _init: called"));
E 4

I 4
	gem_mod_init(&tcfe_ops, "tcfe");
	status = mod_install(&modlinkage);
	if (status != DDI_SUCCESS) {
		gem_mod_fini(&tcfe_ops);
	}
E 4
	return (status);
}

/*
 * _fini : done
 */
int
_fini(void)
{
	int	status;

D 4
	DPRINTF(2, (CE_CONT, "tcfe: _fini: called"));
E 4
I 4
	DPRINTF(2, (CE_CONT, "!tcfe: _fini: called"));
E 4
	status = mod_remove(&modlinkage);
I 4
	if (status == DDI_SUCCESS) {
		gem_mod_fini(&tcfe_ops);
	}
E 4
	return (status);
}

int
_info(struct modinfo *modinfop)
{
	return (mod_info(&modlinkage, modinfop));
}
D 4

E 4
E 1
