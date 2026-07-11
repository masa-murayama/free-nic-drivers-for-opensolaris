h44319
s 00224/00101/02406
d D 1.13 05/01/01 01:16:44 mrym 13 12
c 2.6.3
e
s 00105/00088/02402
d D 1.12 08/04/20 21:25:37 mrym 12 11
c LSO support
e
s 00604/00633/01886
d D 1.11 08/02/03 10:34:58 mrym 11 10
c 2.6.0
e
s 00154/00124/02365
d D 1.10 07/10/14 11:50:57 mrym 10 9
c missing flush after writing imr* and isr
e
s 00004/00003/02485
d D 1.9 07/08/10 23:22:57 mrym 9 8
c 2.4.5
e
s 00331/00222/02157
d D 1.8 07/08/09 00:36:52 mrym 8 7
c 2.4.4
e
s 00001/00001/02378
d D 1.7 07/05/03 04:20:10 mrym 7 6
c 2.4.3
e
s 00636/00256/01743
d D 1.6 07/05/03 04:16:30 mrym 6 5
c 2.4.2
e
s 00076/00049/01923
d D 1.5 07/01/20 14:52:20 mrym 5 4
c 2.4.1: mii_an_oneshot changed to FALSE, cleanup
e
s 00002/00001/01970
d D 1.4 07/01/08 22:34:36 mrym 4 3
c 
e
s 00076/00065/01895
d D 1.3 07/01/08 22:33:27 mrym 3 2
c 2.4.0
e
s 00064/00052/01896
d D 1.2 07/01/08 01:41:24 mrym 2 1
c 2.4.0
e
s 01948/00000/00000
d D 1.1 06/10/02 05:22:21 mrym 1 0
c date and time created 06/10/02 05:22:21 by mrym
e
u
U
f e 0
t
T
I 1
D 8
/*
E 8
I 8
D 11
 /*
E 8
 * nfo_gem.c: nforce ethernet mac driver
E 11
I 11
/*
 * nfo: nforce integrated ethernet mac driver
E 11
 *
D 2
 * Copyright (c) 2005-2006 Masayuki Murayama.  All rights reserved.
E 2
I 2
D 11
 * Copyright (c) 2005-2007 Masayuki Murayama.  All rights reserved.
E 2
 * 
E 11
I 11
 * Copyright (c) 2005-2008 Masayuki Murayama.  All rights reserved.
 *
E 11
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
D 11
 * 
E 11
I 11
 *
E 11
 * 1. Redistributions of source code must retain the above copyright notice,
D 11
 *    this list of conditions and the following disclaimer. 
 * 
E 11
I 11
 *    this list of conditions and the following disclaimer.
 *
E 11
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
D 11
 *    and/or other materials provided with the distribution. 
 * 
E 11
I 11
 *    and/or other materials provided with the distribution.
 *
E 11
 * 3. Neither the name of the author nor the names of its contributors may be
 *    used to endorse or promote products derived from this software without
D 11
 *    specific prior written permission. 
 * 
E 11
I 11
 *    specific prior written permission.
 *
E 11
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
I 2

/*
 * Acknowledgement:
D 3
 * this driver is a result of experience on re-engineering forcedeth
 * driver. I deeply respect and thank the authers of forcedeth driver.
E 3
I 3
 * I thank and respect the authors and the contributors of forcedeth driver
 * in Linux. As NVIDIA doesn't publish datasheets of the ethernet core
 * in nForce chepset, I made this driver by experience on re-engineering
D 11
 * source code of forcedeth driver.
E 11
I 11
 * the source code of forcedeth driver.
E 11
E 3
 */

E 2
D 11
#pragma	ident	"%W% %E%"
E 11
I 11
#pragma	ident	"%Z%%M% %I%     %E%"
E 11

/*
D 11
 Change log
D 4
 */
E 4
I 4

E 4
I 3
2007/01/07
	2.4.0 release
I 5
2007/01/18
	tx checksum offloading flag in format 2 fixed
2007/01/20
	mii_an_oneshot changed (TRUE->FALSE)
2007/01/20
	2.4.1 release
I 6
2007/05/02
D 7
	2.4.2 release
E 7
I 7
	2.4.3 release
I 8
2007/08/10
	2.4.4 release
I 10
2007/10/14
	missing flush after writing imr* and isr
E 11
I 11
 * TODO:
E 11
E 10
E 8
E 7
E 6
E 5
I 4
 */
E 4
E 3

/*
D 11
 TODO:
I 5
D 6
	hardware vlan for format 3
E 6
I 6
	power management - done
	management unit - done
	enhanced test - not yet
	enhanced statistics - no need
	workaround for CICADA phy - done
	workaround for VITESSE phy - done
	workaround for MARVELL phy - done
	keep PHY led state while reset - done
	Tx and Rx path control for management unit - done
	mac address format fix - done
E 6
E 5
D 2
 vlan tagging
 hw cksum
 fmt3
E 2
 */

/*
E 11
 * System Header files.
 */
#include <sys/types.h>
#include <sys/conf.h>
#include <sys/debug.h>
D 11
#include <sys/stropts.h>
#include <sys/stream.h>
#include <sys/strlog.h>
E 11
#include <sys/kmem.h>
D 11
#include <sys/stat.h>
#include <sys/kstat.h>
#include <sys/vtrace.h>
#include <sys/dlpi.h>
#include <sys/strsun.h>
#include <sys/ethernet.h>
E 11
#include <sys/modctl.h>
#include <sys/errno.h>
D 11
#include <sys/dditypes.h>
E 11
#include <sys/ddi.h>
#include <sys/sunddi.h>
D 11

E 11
I 11
#include <sys/byteorder.h>
#include <sys/ethernet.h>
E 11
#include <sys/pci.h>
I 11

E 11
D 10
#include "mii.h"
E 10
I 10
#include "gem_mii.h"
E 10
#include "gem.h"
D 11

E 11
#include "nvenetreg.h"

D 5
char	ident[] = "nVIDIA nForce GbE driver v" VERSION;
E 5
I 5
D 6
char	ident[] = "NVIDIA nForce GbE driver v" VERSION;
E 6
I 6
D 11
char	ident[] = "nForce GbE driver v" VERSION;
E 11
I 11
char	ident[] = "nForce ethernet driver v" VERSION;
E 11
E 6
E 5

/* Debugging support */
#ifdef DEBUG_LEVEL
static int nfo_debug = DEBUG_LEVEL;
D 11
#define	DPRINTF(n, args)	if (nfo_debug>(n)) cmn_err args
E 11
I 11
#define	DPRINTF(n, args)	if (nfo_debug > (n)) cmn_err args
E 11
#else
#define	DPRINTF(n, args)
#endif

/*
 * Useful macros and typedefs
 */
D 2
#define	ONESEC	drv_usectohz(1*1000000)
E 2
I 2
#define	ONESEC		drv_usectohz(1*1000000)
E 2
D 11
#define	ARRAY_SIZE(a)	(sizeof(a)/sizeof(a[0]))
E 11
I 11
#define	ARRAY_SIZE(a)	(sizeof (a) / sizeof ((a)[0]))
E 11

D 11
#define	LE32PACKED(a)	((a)[3]<<24 | ((a)[2]<<16) | ((a)[1]<<8) | (a)[0])
#define	LE16PACKED(a)	(((a)[1]<<8) | (a)[0])
E 11
I 11
#define	LE32PACKED(a)	\
	(((a)[3] << 24) | ((a)[2] << 16) | ((a)[1] << 8) | (a)[0])
#define	LE16PACKED(a)	\
	(((a)[1] << 8) | (a)[0])
E 11

D 11
#define	FLSHB(dp,reg)		INB(dp, reg)
#define	FLSHW(dp,reg)		INW(dp, reg)
#define	FLSHL(dp,reg)		INL(dp, reg)
E 11
I 11
#define	FLSHB(dp, reg)	(void) INB(dp, reg)
#define	FLSHW(dp, reg)	(void) INW(dp, reg)
#define	FLSHL(dp, reg)	(void) INL(dp, reg)
E 11

D 8
#define	IS_DFMT1(dmactrl)	(((dmactrl) & DMACTRL_EXFMT_EN) == 0)
E 8
I 8
#define	IS_DFMT1(dmactrl)	\
D 11
			(((dmactrl) & DMACTRL_DFMT) == DMACTRL_DFMT_1)
E 11
I 11
	(((dmactrl) & DMACTRL_DFMT) == DMACTRL_DFMT_1)
E 11
E 8

#define	IS_DFMT2(dmactrl)	\
D 8
			(((dmactrl) & (DMACTRL_EXFMT_EN | DMACTRL_EXFMT)) \
				== (DMACTRL_EXFMT_EN | DMACTRL_EXFMT_2))
E 8
I 8
D 11
			(((dmactrl) & DMACTRL_DFMT) == DMACTRL_DFMT_2)
E 11
I 11
	(((dmactrl) & DMACTRL_DFMT) == DMACTRL_DFMT_2)
E 11
E 8

#define	IS_DFMT3(dmactrl)	\
D 8
			(((dmactrl) & (DMACTRL_EXFMT_EN | DMACTRL_EXFMT)) \
				== (DMACTRL_EXFMT_EN | DMACTRL_EXFMT_3))
E 8
I 8
D 11
			(((dmactrl) & DMACTRL_DFMT) == DMACTRL_DFMT_3)
E 11
I 11
	(((dmactrl) & DMACTRL_DFMT) == DMACTRL_DFMT_3)
E 11
E 8

I 8
D 11
#define	IS_MCP(lp)	((lp)->chip->devid == 0x1c3)

E 11
E 8
I 6
D 12
#define	OUI_CICADA	0x0003f1
#define	OUI_VITESSE	0x0001c1
#define	OUI_MARVELL	0x005043
E 12
I 12
#define	OUI_CICADA	0x03f1U
#define	OUI_VITESSE	0x01c1U
#define	OUI_MARVELL	0x5043U
#define	OUI_REALTEK	0x0732U
E 12
#define	OUI_CMP(dp, oui)	\
D 11
		((((dp)->mii_phy_id >> 10) ^ (oui)) & 0xffffff)
E 11
I 11
D 12
	((((dp)->mii_phy_id >> 10) ^ (oui)) & 0xffffff)
E 12
I 12
	((((dp)->mii_phy_id >> 10) ^ (oui)) & 0xffff)
E 12
E 11
#define	IS_PHY(dp, oui, model)	\
D 11
		(OUI_CMP(dp, oui) == 0 && (model) == ((dp)->mii_phy_id & 0x3f0))
E 11
I 11
D 12
	(OUI_CMP(dp, oui) == 0 && (model) == ((dp)->mii_phy_id & 0x3f0))
E 12
I 12
	(OUI_CMP(dp, oui) == 0 && (model) == ((dp)->mii_phy_id & 0x03f0))
E 12

D 12
#define	NFO_TXDESC32(p)	((struct txdesc32 *)((void *)(p)))
#define	NFO_TXDESC64(p)	((struct txdesc64 *)((void *)(p)))
#define	NFO_RXDESC32(p)	((struct rxdesc32 *)((void *)(p)))
#define	NFO_RXDESC64(p)	((struct rxdesc64 *)((void *)(p)))
E 12
I 12
#define	TXDESC32(dp)	((struct txdesc32 *)((void *)(dp)->tx_ring))
#define	TXDESC64(dp)	((struct txdesc64 *)((void *)(dp)->tx_ring))
#define	RXDESC32(dp)	((struct rxdesc32 *)((void *)(dp)->rx_ring))
#define	RXDESC64(dp)	((struct rxdesc64 *)((void *)(dp)->rx_ring))
E 12

E 11
E 6
D 2
/* workaround for implicit use of memset/memcpy in gcc structual assignment */
#define	STRUCT_COPY(a, b)	bcopy(&(b), &(a), sizeof(a))

E 2
/*
 * Our configuration
 */
#define	OUR_INTR_BITS	\
D 6
	(INTR_TXDESC | INTR_TXERR1 | INTR_LSC | INTR_TXERR2 | \
	 INTR_RDU | INTR_RXOK | INTR_RXERR)
E 6
I 6
	(INTR_RXERR_FATAL | INTR_TXDESC | INTR_RXDESC | INTR_LSC | \
D 11
	 INTR_TXERR | INTR_RDU | INTR_RXOK | INTR_RXERR)
E 11
I 11
	INTR_TXERR | INTR_RDU | INTR_RXOK | INTR_RXERR)
E 11
E 6

I 13
#ifndef	TX_BUF_SIZE
E 13
D 11
#define TX_RING_SIZE	64
#define RX_RING_SIZE	128
E 11
I 11
#define	TX_BUF_SIZE	64
D 13
#ifdef GEM_CONFIG_TX_DIRECT
#define	TX_RING_SIZE	(TX_BUF_SIZE*4)
#else
#define	TX_RING_SIZE	TX_BUF_SIZE
E 13
#endif
E 11

I 11
D 13
#define	RX_RING_SIZE	256

E 11
I 8
#if TX_RING_SIZE > 1024
D 11
# error TX_RING_SIZE must be equal or lower than 1024
E 11
I 11
#error TX_RING_SIZE must be equal or lower than 1024
E 13
I 13
#ifndef RX_BUF_SIZE
#define	RX_BUF_SIZE	256
E 13
E 11
#endif
D 13
#if RX_RING_SIZE > 1024
D 11
# error RX_RING_SIZE must be equal or lower than 1024
E 11
I 11
#error RX_RING_SIZE must be equal or lower than 1024
E 11
#endif
E 13

I 13
#ifdef DEBUG_TX_SINGLE
static int	nfo_tx_copy_thresh = INT32_MAX;
#else
E 13
E 8
static int	nfo_tx_copy_thresh = 256;
I 13
#endif
E 13
static int	nfo_rx_copy_thresh = 256;

/* supported chipsets */
struct chip_info {
	uint16_t	venid;
	uint16_t	devid;
	char		*name;
D 6
	uint_t		hwmode;
#define	HWMODE_JUMBO	0x00000001
#define	HWMODE_64BIT	0x00000002
E 6
I 6
	uint_t		hwcap;
#define	CAP_JUMBO	0x00000001
#define	CAP_CKSUM	0x00000002
#define	CAP_64BIT	0x00000004
#define	CAP_VLAN	0x00000008
#define	CAP_MSI		0x00000010
#define	CAP_MSIX	0x00000020
D 8
#define	CAP_PM		0x00000040
E 8
I 8
D 11
#define	CAP_PM		0x00000030
E 11
I 11
#define	CAP_PM		0x00000040
E 11
E 8
D 13
#define	CAP_TXPAUSE	0x00000080
#define	CAP_STAT	0x00000100
#define	CAP_TEST	0x00000200
#define	CAP_MGMT	0x00000400
I 8
#define	CAP_RESET	0x00000800
#define	CAP_CORRECT_MAC	0x00001000
E 13
I 13
#define	CAP_TXPAUSE1	0x00000080
#define	CAP_TXPAUSE2	0x00000100
#define	CAP_TXPAUSE3	0x00000200
#define	CAP_STAT	0x00000400
#define	CAP_TEST	0x00000800
#define	CAP_MGMT	0x00001000
#define	CAP_RESET	0x00002000
#define	CAP_CORRECT_MAC	0x00004000
#define	CAP_WA_TX16	0x00008000
#define	CAP_WA_TX16_2	0x00010000
#define	CAP_COLFIX	0x00020000
E 13
E 8
E 6
};


/* private driver state */
struct nfo_dev {
	uint8_t			mac_addr[ETHERADDRL];
	uint32_t		factory_mac_addr[2];
	struct chip_info	*chip;
I 6
	uint_t			hwcap;	/* copy of hwcap in chip_info */
E 6

	uint32_t		imr;
	uint32_t		dmac;
D 11
	uint32_t		clkctrl;
E 11

	/* statstics support */
	clock_t			last_stats_time;
D 13
#ifdef GEM_CONFIG_POLLING
E 13
I 13
#ifdef CONFIG_POLLING
E 13
	int			last_poll_interval;
#endif
I 6

	boolean_t		mac_in_use;
	boolean_t		phy_initialized;
	boolean_t		mac_initialized;

	uint8_t			revid;

	uint16_t		mii_led_stats[3];
E 6
};

/*
 * Macros to identify chip generation.
 */
static struct chip_info nfo_chiptbl[] = {
D 2
	0x10de,	0x01c3,	"nForce mac type 1",	0,
	0x10de,	0x0066,	"nForce mac type 2",	0,
	0x10de,	0x00d6,	"nForce mac type 3",	0,
	0x10de,	0x0086,	"nForce mac type 4",	HWMODE_JUMBO,
	0x10de,	0x008c,	"nForce mac type 5",	HWMODE_JUMBO,
	0x10de,	0x00e6,	"nForce mac type 6",	HWMODE_JUMBO,
	0x10de,	0x00df,	"nForce mac type 7",	HWMODE_JUMBO,
	0x10de,	0x0056,	"nForce mac type 8",	HWMODE_64BIT | HWMODE_JUMBO,
	0x10de,	0x0057,	"nForce mac type 9",	HWMODE_64BIT | HWMODE_JUMBO,
	0x10de,	0x0037,	"nForce mac type 10",	HWMODE_64BIT | HWMODE_JUMBO,
	0x10de,	0x0038,	"nForce mac type 11",	HWMODE_64BIT | HWMODE_JUMBO,
	0x10de, 0x0038, "nForce mac type 11",	HWMODE_64BIT | HWMODE_JUMBO,
	0x10de, 0x0268, "nForce mac type 12",	HWMODE_64BIT,
	0x10de, 0x0269, "nForce4 410/430 type 13",	HWMODE_64BIT,
	0x10de, 0x0372, "nForce MCP55 type 14",	HWMODE_64BIT | HWMODE_JUMBO,
	0x10de, 0x0373, "nForce MCP55 type 15",	HWMODE_64BIT | HWMODE_JUMBO,
E 2
I 2
D 3
0x10de,	0x01c3,	"nForce MCP type 1",	0,
0x10de,	0x0066,	"nForce MCP-T type 2",	0,
0x10de,	0x00d6,	"nForce MCP3 type 3",	0,
0x10de,	0x0086,	"nForce mac type 4",	HWMODE_JUMBO,
0x10de,	0x008c,	"nForce mac type 5",	HWMODE_JUMBO,
0x10de,	0x00e6,	"nForce mac type 6",	HWMODE_JUMBO,
0x10de,	0x00df,	"nForce mac type 7",	HWMODE_JUMBO,
0x10de,	0x0056,	"nForce4 CK804 type 8",	HWMODE_64BIT | HWMODE_JUMBO,
E 3
I 3
D 8
0x10de,	0x01c3,	"nForce MCP type 1",		0,
0x10de,	0x0066,	"nForce MCP-T type 2",		0,
0x10de,	0x00d6,	"nForce MCP3 type 3",		0,
D 6
0x10de,	0x0086,	"nForce mac type 4",		HWMODE_JUMBO,
0x10de,	0x008c,	"nForce mac type 5",		HWMODE_JUMBO,
0x10de,	0x00e6,	"nForce mac type 6",		HWMODE_JUMBO,
0x10de,	0x00df,	"nForce mac type 7",		HWMODE_JUMBO,
0x10de,	0x0056,	"nForce4 CK804 type 8",		HWMODE_64BIT | HWMODE_JUMBO,
E 3
0x10de,	0x0057,	"nForce4 CK804 Ultra type 9",	HWMODE_64BIT | HWMODE_JUMBO,
D 3
0x10de,	0x0037,	"nForce MCP04 type 10",	HWMODE_64BIT | HWMODE_JUMBO,
0x10de,	0x0038,	"nForce MCP04 type 11",	HWMODE_64BIT | HWMODE_JUMBO,
0x10de, 0x0268, "nForce MCP51 type 12",	HWMODE_64BIT,
E 3
I 3
0x10de,	0x0037,	"nForce MCP04 type 10",		HWMODE_64BIT | HWMODE_JUMBO,
0x10de,	0x0038,	"nForce MCP04 type 11",		HWMODE_64BIT | HWMODE_JUMBO,
0x10de, 0x0268, "nForce MCP51 type 12",		HWMODE_64BIT,
E 3
0x10de, 0x0269, "nForce 410/430 MCP51 type 13",	HWMODE_64BIT,
D 3
0x10de, 0x0372, "nForce MCP55 type 14",	HWMODE_64BIT | HWMODE_JUMBO,
0x10de, 0x0373, "nForce MCP55 type 15",	HWMODE_64BIT | HWMODE_JUMBO,
E 3
I 3
0x10de, 0x0372, "nForce MCP55 type 14",		HWMODE_64BIT | HWMODE_JUMBO,
0x10de, 0x0373, "nForce MCP55 type 15",		HWMODE_64BIT | HWMODE_JUMBO,
E 6
I 6
0x10de,	0x0086,	"nForce mac type 4",		CAP_JUMBO | CAP_CKSUM,
0x10de,	0x008c,	"nForce mac type 5",		CAP_JUMBO | CAP_CKSUM,
0x10de,	0x00e6,	"nForce mac type 6",		CAP_JUMBO | CAP_CKSUM,
0x10de,	0x00df,	"nForce mac type 7",		CAP_JUMBO | CAP_CKSUM,
E 8
I 8
0x10de,	0x01c3,	"type1 (nForce MCP)",		0,
0x10de,	0x0066,	"type2 (nForce MCP-T)",		CAP_RESET,
D 11
0x10de,	0x00d6,	"type3 (nForce3 150/Go150/Pro150)",	CAP_RESET,
E 11
I 11
0x10de,	0x00d6,	"type3 (nForce3 150)",		CAP_RESET,
E 11
0x10de,	0x0086,	"type4 (nForce2 MCP-R)",	CAP_JUMBO | CAP_CKSUM,
0x10de,	0x008c,	"type5 (nForce2 MCP-Gb)",	CAP_JUMBO | CAP_CKSUM,
0x10de,	0x00e6,	"type6 (nForce3 250Gb)",	CAP_JUMBO | CAP_CKSUM,
0x10de,	0x00df,	"type7 (nForce3 250)",		CAP_JUMBO | CAP_CKSUM,
E 8

D 13
#define	CAP_CK804	(CAP_JUMBO | CAP_CKSUM | CAP_64BIT)
E 13
I 13
#define	CAP_CK804	(CAP_JUMBO | CAP_CKSUM | CAP_64BIT | CAP_WA_TX16)
E 13
D 8
0x10de,	0x0056,	"nForce4 CK804 type 8",		CAP_CK804,
0x10de,	0x0057,	"nForce4 CK804 Ultra type 9",	CAP_CK804,
E 8
I 8
D 11
0x10de,	0x0056,	"type8 (nForce4 CK804)",		CAP_CK804,
0x10de,	0x0057,	"type9 (nForce4 Ultra CK804)",		CAP_CK804,
E 11
I 11
0x10de,	0x0056,	"type8 (nForce4 CK804)",	CAP_CK804,
0x10de,	0x0057,	"type9 (nForce4 Ultra CK804)",	CAP_CK804,
E 11
E 8

D 13
#define	CAP_MCP04	(CAP_JUMBO | CAP_CKSUM | CAP_64BIT)
E 13
I 13
#define	CAP_MCP04	(CAP_JUMBO | CAP_CKSUM | CAP_64BIT | CAP_WA_TX16)
E 13
D 8
0x10de,	0x0037,	"nForce MCP04 type 10",		CAP_MCP04,
0x10de,	0x0038,	"nForce MCP04 type 11",		CAP_MCP04,
E 8
I 8
D 11
0x10de,	0x0037,	"type10 (nForce MCP04)",		CAP_MCP04,
0x10de,	0x0038,	"type11 (nForce MCP04 Ultra)",		CAP_MCP04,
E 11
I 11
0x10de,	0x0037,	"type10 (nForce MCP04)",	CAP_MCP04,
0x10de,	0x0038,	"type11 (nForce MCP04 Ultra)",	CAP_MCP04,
E 11
E 8

#define	CAP_MCP51	(CAP_64BIT | CAP_PM)
D 8
0x10de, 0x0268, "nForce MCP51 type 12",		CAP_MCP51,
0x10de, 0x0269, "nForce 410/430 MCP51 type 13",	CAP_MCP51,
E 8
I 8
D 11
0x10de, 0x0268, "type12 (nForce MCP51)",		CAP_MCP51,
0x10de, 0x0269, "type13 (GF6100/NF410 MCP51)",		CAP_MCP51,
E 11
I 11
0x10de, 0x0268, "type12 (nForce MCP51)",	CAP_MCP51,
0x10de, 0x0269, "type13 (GF6150/NF430,GF6100/NF410 MCP51)", CAP_MCP51,
E 11
E 8

#define	CAP_MCP55	\
	(CAP_JUMBO | CAP_CKSUM | CAP_64BIT | CAP_VLAN | CAP_MSI | \
D 11
	 CAP_MSIX | CAP_PM | CAP_TXPAUSE | CAP_STAT | CAP_TEST | CAP_MGMT)
D 8
0x10de, 0x0372, "nForce MCP55 type 14",		CAP_MCP55,
0x10de, 0x0373, "nForce MCP55 type 15",		CAP_MCP55,
E 8
I 8
0x10de, 0x0372, "type14 (nForce590 MCP55)",		CAP_MCP55,
0x10de, 0x0373, "type15 (nForce570 Ultra MCP55)",	CAP_MCP55,
E 11
I 11
D 13
	CAP_MSIX | CAP_PM | CAP_TXPAUSE | CAP_STAT | CAP_TEST | CAP_MGMT)
E 13
I 13
	CAP_MSIX | CAP_PM | CAP_TXPAUSE1 | CAP_STAT | CAP_TEST | CAP_MGMT | \
	CAP_WA_TX16)
E 13
0x10de, 0x0372, "type14 (nForce590 MCP55)",	CAP_MCP55,
0x10de, 0x0373, "type15 (nForce570 Ultra, 680a, MCP55)",	CAP_MCP55,
E 11
E 8

#define	CAP_MCP61	\
D 13
	(CAP_64BIT | CAP_PM | CAP_MSI | CAP_TXPAUSE | CAP_STAT | \
E 13
I 13
	(CAP_64BIT | CAP_PM | CAP_MSI | CAP_TXPAUSE1 | CAP_STAT | \
E 13
D 8
	 CAP_TEST | CAP_MGMT)
0x10de, 0x03e5, "nForce MCP61 type 16",		CAP_MCP61,
0x10de, 0x03e6, "nForce MCP61 type 17",		CAP_MCP61,
0x10de, 0x03ee, "nForce MCP61 type 18",		CAP_MCP61,
0x10de, 0x03ef, "nForce MCP61 type 19",		CAP_MCP61,
E 8
I 8
D 11
	 CAP_TEST | CAP_MGMT | CAP_CORRECT_MAC)
0x10de, 0x03e5, "type16 (nForce MCP61)",		CAP_MCP61,
0x10de, 0x03e6, "type17 (nForce MCP61)",		CAP_MCP61,
0x10de, 0x03ee, "type18 (nForce MCP61)",		CAP_MCP61,
D 10
0x10de, 0x03ef, "type19 (GF6100/NF405 MCP61)",		CAP_MCP61,
E 10
I 10
0x10de, 0x03ef, "type19 (GF6100/nF405 MCP61)",		CAP_MCP61,
E 11
I 11
	CAP_TEST | CAP_MGMT | CAP_CORRECT_MAC)
0x10de, 0x03e5, "type16 (nForce MCP61)",	CAP_MCP61,
0x10de, 0x03e6, "type17 (nForce MCP61)",	CAP_MCP61,
0x10de, 0x03ee, "type18 (nForce MCP61)",	CAP_MCP61,
D 13
0x10de, 0x03ef, "type19 (GF6100/nF430, GF/6100/nF405 MCP61)", CAP_MCP61,
E 13
I 13
0x10de, 0x03ef, "type19 (GF6100/nF430, GF6100/nF405, MCP61)", CAP_MCP61,
E 13
E 11
E 10
E 8

D 13
#define	CAP_MCP65	(CAP_MCP61 | CAP_JUMBO | CAP_CKSUM)
E 13
I 13
#define	CAP_MCP65	(CAP_MCP61 | CAP_JUMBO | CAP_CKSUM | CAP_WA_TX16)
E 13
D 8
0x10de, 0x0450, "nForce MCP65 type 20",		CAP_MCP65,
0x10de, 0x0451, "nForce MCP65 type 21",		CAP_MCP65,
0x10de, 0x0452, "nForce MCP65 type 22",		CAP_MCP65,
0x10de, 0x0453, "nForce MCP65 type 23",		CAP_MCP65,
E 8
I 8
D 11
0x10de, 0x0450, "type20 (nForce MCP65)",		CAP_MCP65,
0x10de, 0x0451, "type21 (nForce MCP65)",		CAP_MCP65,
0x10de, 0x0452, "type22 (nForce MCP65)",		CAP_MCP65,
0x10de, 0x0453, "type23 (nForce MCP65)",		CAP_MCP65,
E 11
I 11
0x10de, 0x0450, "type20 (nForce MCP65)",	CAP_MCP65,
0x10de, 0x0451, "type21 (nForce MCP65)",	CAP_MCP65,
0x10de, 0x0452, "type22 (nForce MCP65)",	CAP_MCP65,
0x10de, 0x0453, "type23 (nForce MCP65)",	CAP_MCP65,
E 11

D 12
#define	CAP_MCP67	(CAP_MCP61)
E 12
I 12
#define	CAP_MCP67	CAP_MCP61
E 12
D 10
0x10de, 0x054c, "type24 (nForce MCP67)",		CAP_MCP67,
E 10
I 10
0x10de, 0x054c, "type24 (GF7000M/nF610M MCP67-MV)",	CAP_MCP67,
E 10
D 11
0x10de, 0x054d, "type25 (nForce MCP67)",		CAP_MCP67,
0x10de, 0x054e, "type26 (nForce MCP67)",		CAP_MCP67,
0x10de, 0x054f, "type27 (nForce MCP67)",		CAP_MCP67,
E 11
I 11
0x10de, 0x054d, "type25 (nForce MCP67)",	CAP_MCP67,
0x10de, 0x054e, "type26 (nForce MCP67)",	CAP_MCP67,
0x10de, 0x054f, "type27 (nForce MCP67)",	CAP_MCP67,
I 12

#define	CAP_MCP73	\
D 13
	(CAP_64BIT | CAP_PM | CAP_MSI | CAP_TXPAUSE | CAP_STAT | \
	CAP_TEST | CAP_MGMT | CAP_CORRECT_MAC)
E 13
I 13
	(CAP_64BIT | CAP_PM | CAP_MSI | CAP_TXPAUSE1 | CAP_STAT | \
	CAP_TEST | CAP_MGMT | CAP_CORRECT_MAC | CAP_COLFIX)
E 13
0x10de, 0x07dc, "type28 (nForce MCP73)",	CAP_MCP73,
0x10de, 0x07dd, "type29 (nForce MCP73)",	CAP_MCP73,
0x10de, 0x07de, "type30 (nForce MCP73)",	CAP_MCP73,
0x10de, 0x07df, "type31 (nForce MCP73)",	CAP_MCP73,

#define	CAP_MCP77	\
D 13
	(CAP_CKSUM | CAP_64BIT | CAP_PM | CAP_MSI | CAP_TXPAUSE | CAP_STAT | \
	CAP_TEST | CAP_MGMT)
0x10de, 0x0760, "type32 (nForce MCP77)",	CAP_MCP77,
E 13
I 13
	(CAP_CKSUM | CAP_64BIT | CAP_PM | CAP_MSI | CAP_TXPAUSE2 | CAP_STAT | \
	CAP_TEST | CAP_MGMT | CAP_CORRECT_MAC | CAP_WA_TX16_2 | CAP_COLFIX)
0x10de, 0x0760, "type32 (GF8200, MCP77)",	CAP_MCP77,
E 13
0x10de, 0x0761, "type33 (nForce MCP77)",	CAP_MCP77,
0x10de, 0x0762, "type34 (nForce MCP77)",	CAP_MCP77,
0x10de, 0x0763, "type35 (nForce MCP77)",	CAP_MCP77,

D 13
#define	CAP_MCP79	CAP_MCP77
E 13
I 13
#define	CAP_MCP79	\
	(CAP_CKSUM | CAP_64BIT | CAP_PM | CAP_MSI | CAP_TXPAUSE3 | CAP_STAT | \
	CAP_TEST | CAP_MGMT | CAP_CORRECT_MAC | CAP_WA_TX16_2 | CAP_COLFIX)
E 13
0x10de, 0x0ab0, "type36 (nForce MCP79)",	CAP_MCP79,
0x10de, 0x0ab1, "type37 (nForce MCP79)",	CAP_MCP79,
0x10de, 0x0ab2, "type38 (nForce MCP79)",	CAP_MCP79,
0x10de, 0x0ab3, "type39 (nForce MCP79)",	CAP_MCP79,
E 12
E 11
E 8
E 6
E 3
E 2
};
D 11
#define CHIPTABLESIZE   (sizeof(nfo_chiptbl)/sizeof(struct chip_info))
E 11
I 11
#define	CHIPTABLESIZE	(sizeof (nfo_chiptbl) / sizeof (struct chip_info))
E 11

I 8
D 9
#define	IS_TYPE4_OR_LATER(lp)	((lp)->hwcap != 0)
E 9
I 9
D 10
#define	IS_TYPE4_OR_LATER(lp)	\
			(((lp)->hwcap & (CAP_JUMBO | CAP_64BIT)) != 0)
E 10
I 10
#define	IS_TYPE4_OR_LATER(lp)	((lp)->hwcap & (CAP_JUMBO | CAP_64BIT))
E 10
E 9

E 8
/* ======================================================== */
/* local functions */

/* mii operations */
static void  nfo_mii_sync(struct gem_dev *);
static uint16_t  nfo_mii_read(struct gem_dev *, uint_t);
static void nfo_mii_write(struct gem_dev *, uint_t, uint16_t);

/* nic operations */
static int nfo_reset_chip(struct gem_dev *);
D 2
static void nfo_init_chip(struct gem_dev *);
static void nfo_start_chip(struct gem_dev *);
E 2
I 2
static int nfo_init_chip(struct gem_dev *);
static int nfo_start_chip(struct gem_dev *);
E 2
static int nfo_stop_chip(struct gem_dev *);
D 2
static void nfo_set_media(struct gem_dev *);
static void nfo_set_rx_filter(struct gem_dev *);
static void nfo_get_stats(struct gem_dev *);
E 2
I 2
static int nfo_set_media(struct gem_dev *);
static int nfo_set_rx_filter(struct gem_dev *);
static int nfo_get_stats(struct gem_dev *);
E 2

/* descriptor operations */
static int nfo_tx_desc_write32(struct gem_dev *dp, int slot,
D 10
		    ddi_dma_cookie_t *dmacookie, int frags, uint32_t intreq);
E 10
I 10
D 12
		    ddi_dma_cookie_t *dmacookie, int frags, uint64_t intreq);
E 12
I 12
    ddi_dma_cookie_t *dmacookie, int frags, uint64_t intreq);
E 12
E 10
static int nfo_tx_desc_write64(struct gem_dev *dp, int slot,
D 10
		    ddi_dma_cookie_t *dmacookie, int frags, uint32_t intreq);
E 10
I 10
D 12
		    ddi_dma_cookie_t *dmacookie, int frags, uint64_t intreq);
E 12
I 12
    ddi_dma_cookie_t *dmacookie, int frags, uint64_t intreq);
E 12
E 10
D 11
static uint_t nfo_tx_desc_stat32(struct gem_dev *dp, int slot, int ndesc);
static uint_t nfo_tx_desc_stat64(struct gem_dev *dp, int slot, int ndesc);

E 11
I 11
static uint_t nfo_tx_desc_stat(struct gem_dev *dp, int slot, int ndesc);
static uint64_t nfo_rx_desc_stat(struct gem_dev *dp, int slot, int ndesc);
E 11
static void nfo_rx_desc_write32(struct gem_dev *dp, int slot,
D 12
		    ddi_dma_cookie_t *dmacookie, int frags);
E 12
I 12
    ddi_dma_cookie_t *dmacookie, int frags);
E 12
static void nfo_rx_desc_write64(struct gem_dev *dp, int slot,
D 12
		    ddi_dma_cookie_t *dmacookie, int frags);
E 12
I 12
    ddi_dma_cookie_t *dmacookie, int frags);
E 12

static void nfo_tx_desc_init32(struct gem_dev *dp, int slot);
static void nfo_tx_desc_init64(struct gem_dev *dp, int slot);
static void nfo_rx_desc_init32(struct gem_dev *dp, int slot);
static void nfo_rx_desc_init64(struct gem_dev *dp, int slot);

/* interrupt handler */
D 11
static u_int nfo_interrupt(struct gem_dev *dp);
E 11
I 11
static uint_t nfo_interrupt(struct gem_dev *dp);
E 11

/* ======================================================== */

/* mapping attributes */
/* Data access requirements. */
static struct ddi_device_acc_attr nfo_dev_attr = {
	DDI_DEVICE_ATTR_V0,
	DDI_STRUCTURE_LE_ACC,
	DDI_STRICTORDER_ACC
};

/* On sparc, the buffers should be native endianness */
static struct ddi_device_acc_attr nfo_buf_attr = {
	DDI_DEVICE_ATTR_V0,
	DDI_NEVERSWAP_ACC,	/* native endianness */
	DDI_STRICTORDER_ACC
};

static ddi_dma_attr_t nfo_dma_attr_buf32 = {
	DMA_ATTR_V0,		/* dma_attr_version */
	0,			/* dma_attr_addr_lo */
	0xffffffffull,		/* dma_attr_addr_hi */
D 13
	0x00003fffull,		/* dma_attr_count_max */
E 13
I 13
	0x00004000ull,		/* dma_attr_count_max */
E 13
D 11
	0,/* patched later */	/* dma_attr_align */
E 11
I 11
	0, /* patched later */	/* dma_attr_align */
E 11
	0x00003fff,		/* dma_attr_burstsizes */
	1,			/* dma_attr_minxfer */
D 13
	0x00003fffull,		/* dma_attr_maxxfer */
E 13
I 13
#ifdef CONFIG_LSO
	0x00004000ull,		/* dma_attr_maxxfer */
#else
	9202ull,		/* dma_attr_maxxfer */
#endif
E 13
	0xffffffffull,		/* dma_attr_seg */
D 11
	0,/* patched later */	/* dma_attr_sgllen */
E 11
I 11
	0, /* patched later */	/* dma_attr_sgllen */
E 11
	1,			/* dma_attr_granular */
	0			/* dma_attr_flags */
};

static ddi_dma_attr_t nfo_dma_attr_buf64 = {
	DMA_ATTR_V0,		/* dma_attr_version */
	0,			/* dma_attr_addr_lo */
D 6
	0xffffffffffull,	/* dma_attr_addr_hi 40bit */
	0x00003fffull,		/* dma_attr_count_max */
E 6
I 6
D 11
	0x000000ffffffffffull,	/* dma_attr_addr_hi 40bit */
E 11
I 11
	0x000000ffffffffffull,	/* dma_attr_addr_hi (40bit) */
E 11
D 13
	0x0000000000003fffull,	/* dma_attr_count_max */
E 13
I 13
	0x0000000000004000ull,	/* dma_attr_count_max */
E 13
E 6
D 11
	0,/* patched later */	/* dma_attr_align */
E 11
I 11
	0, /* patched later */	/* dma_attr_align */
E 11
	0x00003fff,		/* dma_attr_burstsizes */
	1,			/* dma_attr_minxfer */
D 6
	0x00003fffull,		/* dma_attr_maxxfer */
	0xffffffffffull,	/* dma_attr_seg */
E 6
I 6
D 13
	0x0000000000003fffull,	/* dma_attr_maxxfer */
E 13
I 13
#ifdef CONFIG_LSO
	0x0000000000004000ull,	/* dma_attr_maxxfer */
#else
	9202ull,		/* dma_attr_maxxfer */
#endif
E 13
	0x000000ffffffffffull,	/* dma_attr_seg */
E 6
D 11
	0,/* patched later */	/* dma_attr_sgllen */
E 11
I 11
	0, /* patched later */	/* dma_attr_sgllen */
E 11
	1,			/* dma_attr_granular */
	0			/* dma_attr_flags */
};

static ddi_dma_attr_t nfo_dma_attr_desc = {
	DMA_ATTR_V0,		/* dma_attr_version */
	0,			/* dma_attr_addr_lo */
	0xffffffffull,		/* dma_attr_addr_hi */
	0xffffffffull,		/* dma_attr_count_max */
	16,			/* dma_attr_align */
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
I 8
 *	Debug routines
 */
/* ======================================================== */
I 11
#ifdef DEBUG_LEVEL
E 11
static void
nfo_dump_regs(struct gem_dev *dp, char *title)
{
	int		i;
D 11
	caddr_t		base = dp->base_addr;
	ssize_t	 	len = 0x400;
E 11
I 11
	ssize_t		len = 0x400;
E 11

	cmn_err(CE_CONT, "!%s", title);

	for (i = 0; i < len; i += 4*4) {
		cmn_err(CE_CONT, "!%04x: %08x %08x %08x %08x",
D 11
			i, INL(dp, i), INL(dp, i + 4*1),
			INL(dp, i + 4*2), INL(dp, i + 4*3));
E 11
I 11
		    i, INL(dp, i), INL(dp, i + 4*1),
		    INL(dp, i + 4*2), INL(dp, i + 4*3));
E 11
	}
}
I 11
#endif
E 11

/* ======================================================== */
/*
E 8
 * HW manupilation routines
 */
/* ======================================================== */
D 6
static void
nfo_dmac_reset(struct gem_dev *dp)
{
	struct nfo_dev	*lp = (struct nfo_dev *)dp->private;

	DPRINTF(0, (CE_CONT, "!%s: %s", dp->name, __func__));

	OUTL(dp, DMACTRL, DMACTRL_RESET | lp->dmac);
	FLSHL(dp, DMACTRL);
	drv_usecwait(10);

	OUTL(dp, DMACTRL, DMACTRL_UNRESET | lp->dmac);
	FLSHL(dp, DMACTRL);
}

E 6
static int
nfo_reset_chip(struct gem_dev *dp)
{
I 8
D 11
	int		i;
E 11
	int		ret;
D 11
	uint32_t	val;
E 11
	uint32_t	miiauto;
E 8
D 6
	struct nfo_dev	*lp = (struct nfo_dev *)dp->private;
E 6
I 6
D 11
	struct nfo_dev	*lp = (struct nfo_dev *) dp->private;
E 11
I 11
	struct nfo_dev	*lp = dp->private;
E 11
E 6

	DPRINTF(0, (CE_CONT, "!%s: %s: called, time:%d",
D 11
		dp->name, __func__, ddi_get_lbolt()));
E 11
I 11
	    dp->name, __func__, ddi_get_lbolt()));
E 11

D 8
	/* inhibit interrupts */
E 8
I 8
	ret = GEM_SUCCESS;
D 11

E 11
I 11
#if DEBUG_LEVEL > 0
	nfo_dump_regs(dp, (void *)__func__);
#endif
E 11
	/*
	 * Disable MIIAUTO
	 */
	miiauto = INL(dp, MIIAUTO);
D 10
	if ((miiauto & MIIAUTO_EN) != 0) {
E 10
I 10
	if (miiauto & MIIAUTO_EN) {
E 10
		OUTL(dp, MIIAUTO, miiauto & ~MIIAUTO_EN);
	}

	/*
	 * Inhibit interrupts
	 */
E 8
D 10
	lp->imr = 0;
E 10
I 6
	OUTL(dp, MIIIMR, 0);
E 6
D 10
	OUTL(dp, IMR, 0); FLSHL(dp, IMR);
E 10
I 10
	FLSHL(dp, MIIIMR);
	OUTL(dp, IMR, 0);
	FLSHL(dp, IMR);
E 10
I 6
D 8
	/* global interrupt disable */
	OUTL(dp, REG_008, 0);
E 8
E 6

D 6
	OUTL(dp, TxCTRL, 0);
	OUTL(dp, RxCTRL, 0);
E 6
I 6
	if (!lp->mac_in_use) {
D 8
		/* stop tx and rx activities */
		OUTL(dp, TxCTRL, INL(dp, TxCTRL) & ~TxCTRL_START);
		OUTL(dp, RxCTRL, INL(dp, RxCTRL) & ~RxCTRL_START);
E 6
D 3
#if 1
E 3
I 3

E 8
E 3
D 6
	OUTL(dp, MIIAUTO, 0);
	OUTL(dp, CLKCTRL, 0);
E 6
I 6
D 11
		OUTL(dp, CLKCTRL, 0);
E 11
I 11
		OUTL(dp, RxPOLL, 0);
E 11
I 8
		OUTL(dp, TxPOLL, INL(dp, TxPOLL) & TxPOLL_MACADDR_REV);
E 8
	}
E 6
D 3
#endif
E 3
I 3

E 3
D 6
	OUTL(dp, REG_008, 0);
E 6
I 6
D 8
	/* stop dma activities */
	OUTL(dp, DMACTRL, DMACTRL_RESET | lp->dmac);
	FLSHL(dp, DMACTRL);
	drv_usecwait(10);
E 8
I 8
	/* halt dma */
	OUTL(dp, DMACTRL, DMACTRL_RESET | DMACTRL_STOP | lp->dmac);
	drv_usecwait(20);
E 8
E 6

D 6
	nfo_dmac_reset(dp);
E 6
I 6
D 10
	if ((lp->hwcap & CAP_PM) != 0 && !lp->mac_initialized) {
E 10
I 10
	if ((lp->hwcap & CAP_PM) && !lp->mac_initialized) {
E 10
		/* reset mac */
		OUTL(dp, MACRESET, 0xf3);
		FLSHL(dp, MACRESET);
D 8
		drv_usecwait(64);
E 8
I 8
		drv_usecwait(100);
E 8
E 6

D 6
	OUTL(dp, REG_008, 0);
E 6
I 6
		OUTL(dp, MACRESET, 0);
		FLSHL(dp, MACRESET);
D 8
		drv_usecwait(64);
E 8
I 8
		drv_usecwait(100);
E 8
	}
E 6
D 11

E 11
I 11
#ifdef NEVER
	/* XXX - not required */
E 11
D 6
	/*
	 * need to enable phy interface
	 */
D 5
	DPRINTF(5, (CE_CONT, "%s: MIISTAT:%b (before resetting)",
E 5
I 5
	DPRINTF(5, (CE_CONT, "!%s: MIISTAT:%b (before resetting)",
E 5
			dp->name, INL(dp, MIISTAT), MIISTAT_BITS));
E 6
I 6
D 8
	OUTL(dp, DMACTRL, DMACTRL_UNRESET | lp->dmac);
	FLSHL(dp, DMACTRL);
E 8
I 8
D 10
	if ((lp->chip->hwcap & CAP_RESET) != 0)  {
E 10
I 10
	if (lp->chip->hwcap & CAP_RESET)  {
E 10
		uint32_t	mac0_save;
		uint32_t	mac1_save;
E 8
E 6

I 8
		mac1_save = INL(dp, MACADDR + 4);
		mac0_save = INL(dp, MACADDR);

D 13
		OUTL(dp, REG_034, INL(dp, REG_034) | 0xff);
E 13
I 13
		OUTL(dp, MACRESET, INL(dp, MACRESET) | 0xff);
E 13
		drv_usecwait(10);

D 13
		OUTL(dp, REG_034, INL(dp, REG_034) & ~0xff);
E 13
I 13
		OUTL(dp, MACRESET, INL(dp, MACRESET) & ~0xff);
E 13
		drv_usecwait(10);

		OUTL(dp, MACADDR + 4, mac1_save);
		OUTL(dp, MACADDR, mac0_save);
	}
D 11

E 11
I 11
#endif
E 11
	OUTL(dp, DMACTRL, DMACTRL_STOP | lp->dmac);
	drv_usecwait(20);

D 11
	/* disable global interrupt */
	OUTL(dp, REG_008, 0);
E 11
I 11
	/* disable timer */
	OUTL(dp, TIMERCTL, 0);
E 11

E 8
D 11
	/* clear MII error */
D 6
	OUTL(dp, MIISTAT, MIISTAT_ERROR);
D 5
	DPRINTF(5, (CE_CONT, "%s: MIISTAT:%b (after resetting)",
E 5
I 5
	DPRINTF(5, (CE_CONT, "!%s: MIISTAT:%b (after resetting)",
E 5
			dp->name, INL(dp, MIISTAT), MIISTAT_BITS));
E 6
I 6
	OUTL(dp, MIIISR, MIIISR_ALL);
E 11
I 11
	if (!lp->mac_initialized) {
		/* clear MII error */
		OUTL(dp, MIIISR, MIIISR_ALL);
E 11
E 6

I 10
D 11
	/* clear bugus interrupts */
	OUTL(dp, ISR, INTR_ALL);
E 11
I 11
		/* clear bugus interrupts */
		OUTL(dp, ISR, INTR_ALL);
	}
E 11

E 10
I 8
D 9
	if ((lp->chip->hwcap & (CAP_JUMBO | CAP_64BIT)) == 0) {
E 9
I 9
	if (!IS_TYPE4_OR_LATER(lp)) {
E 9
D 11
		/* old chipset only for 100Mbps */
E 11
I 11
		/* old chipset have only MII interface for 100Mbps */
E 11
		OUTL(dp, PHYIF, INL(dp, PHYIF) & ~PHYIF_RGMII);
I 11
D 12
#if 0
E 12
I 12
#ifdef NEVER
E 12
E 11
	} else {
I 11
		/* recent chipset have RGMII interfase for 1Gbps */
E 11
		OUTL(dp, PHYIF, INL(dp, PHYIF) | PHYIF_RGMII);
I 11
#endif
E 11
	}

D 10
	if (lp->mac_initialized && (miiauto & MIIAUTO_EN) != 0) {
E 10
I 10
	if (lp->mac_initialized && (miiauto & MIIAUTO_EN)) {
E 10
		/*
		 * restore MIIAUTO
		 */
		OUTL(dp, MIIAUTO, miiauto);
	}

E 8
D 6
	OUTL(dp, MIICFG, 0x105);
E 6
I 6
	lp->mac_initialized = B_TRUE;
E 6

D 8
	return (GEM_SUCCESS);
E 8
I 8
	return (ret);
E 8
}

D 2
static void
E 2
I 2
static int
E 2
nfo_init_chip(struct gem_dev *dp)
{
	int		i;
D 11
	uint32_t	val;
D 6
	struct nfo_dev	*lp = (struct nfo_dev *)dp->private;
E 6
I 6
	struct nfo_dev	*lp = (struct nfo_dev *) dp->private;
E 11
I 11
	struct nfo_dev	*lp = dp->private;
E 11
E 6

	DPRINTF(0, (CE_CONT, "!%s: %s: called at time:%d",
D 11
		dp->name, __func__, ddi_get_lbolt()));
E 11
I 11
	    dp->name, __func__, ddi_get_lbolt()));
E 11

D 6
	OUTL(dp, TIMER, 0);

	/* Setup tx and rx descriptor rings */
E 6
I 6
	/* setup tx and rx descriptor rings */
E 6
D 11
	OUTL(dp, RxDESCBASE, (uint32_t) dp->rx_ring_dma);
	OUTL(dp, TxDESCBASE, (uint32_t) dp->tx_ring_dma);
E 11
I 11
	OUTL(dp, RxDESCBASE, (uint32_t)dp->rx_ring_dma);
	OUTL(dp, TxDESCBASE, (uint32_t)dp->tx_ring_dma);
E 11
	if (IS_DFMT3(lp->dmac)) {
D 11
		OUTL(dp, RxDESCBASE_HI, (uint32_t) (dp->rx_ring_dma >> 32));
		OUTL(dp, TxDESCBASE_HI, (uint32_t) (dp->tx_ring_dma >> 32));
	}	
E 11
I 11
		OUTL(dp, RxDESCBASE_HI, (uint32_t)(dp->rx_ring_dma >> 32));
		OUTL(dp, TxDESCBASE_HI, (uint32_t)(dp->tx_ring_dma >> 32));
	}
E 11
D 6

E 6
	OUTL(dp, RINGCFG,
D 11
		((RX_RING_SIZE - 1) << RINGCFG_RX_SHIFT) | (TX_RING_SIZE - 1));
E 11
I 11
D 13
	    ((RX_RING_SIZE - 1) << RINGCFG_RX_SHIFT) | (TX_RING_SIZE - 1));
E 13
I 13
	    ((dp->gc.gc_rx_ring_size - 1) << RINGCFG_RX_SHIFT)
	    | (dp->gc.gc_tx_ring_size - 1));
E 13
E 11
D 6
	OUTL(dp, DMACFG, 0x00200010);
E 6

I 8
D 11
	OUTL(dp, CLKCTRL, CLKCTRL_FIXED | 10);
E 11
I 11
	OUTL(dp, RxPOLL, RxPOLL_EN | 10);
E 11

	/* unreset DMAC */
	OUTL(dp, DMACTRL, lp->dmac);

D 9
	/* enable dma */
E 9
I 9
D 11
	/* enable dma engine */
E 9
	OUTL(dp, DMACTRL, DMACTRL_START | lp->dmac);
	for (i = 0; (INL(dp, DMASTAT) & DMASTAT_RUNNING) == 0; i++) {
E 11
I 11
	/* start rx side of dma engine */
	OUTL(dp, DMACTRL, DMACTRL_RxPOLL | lp->dmac);
	for (i = 0; (INL(dp, RxDMASTAT) & RxDMASTAT_RUNNING) == 0; i++) {
E 11
		if (i > 1000) {
D 10
			cmn_err(CE_WARN, "!%s: %s: failed to start DMA engine",
				dp->name, __func__);
E 10
I 10
			DPRINTF(1, (CE_CONT,
D 11
				"!%s: %s: failed to start DMA engine",
				dp->name, __func__));
E 11
I 11
			    "!%s: %s: failed to start rx side of dma engine",
			    dp->name, __func__));
E 11
E 10
			break;
		}
		drv_usecwait(10);
	}

	OUTL(dp, TxSTAT, INL(dp, TxSTAT));

E 8
D 6
	nfo_dmac_reset(dp);

E 6
D 11
	/* make a random number */
D 8
	val = ddi_get_lbolt() ^ ddi_get_time();
	OUTL(dp, RNDCTRL, RNDCTRL_SPEED_1G | (val & RNDCTRL_SEED));
E 8
I 8
	val = 8;
	if (IS_DFMT1(lp->dmac)) {
		if ((val =
		((ddi_get_lbolt() ^ ddi_get_time()) & RNDCTRL_SEED)) == 0) {
			/* avoid zero */
			val = 8;
		}
	}
	OUTL(dp, RNDCTRL, RNDCTRL_SPEED_1G | val);
E 8

E 11
D 8
	OUTL(dp, MAXBUFSIZE, dp->rx_buf_len);
D 6

	OUTL(dp, REG_0A0, 0x16070f);
	OUTL(dp, REG_0A4, 0x16);
	OUTL(dp, REG_008, 3);
	OUTL(dp, REG_184, 8);
D 3
	OUTL(dp, WAKECTRL, WAKECTRL_VAL);
E 3
I 3
	OUTL(dp, WAKECTRL, 0x7770);
E 3
#ifdef CONFIG_HWVLAN
	OUTL(dp, VLANCTRL, VLANCTRL_EN);
E 6
I 6
#if 0
	OUTL(dp, TXWM, IS_DFMT1(lp->dmac) ? 0x0200010 : 0x1e08000);
	OUTL(dp, TxDEFER, 0x15050f);	/* default */
E 6
#else
E 8
I 8
	OUTL(dp, MAXBUFSIZE,
D 11
		dp->mtu + sizeof(struct ether_header) + ETHERFCSL + 8);
E 11
I 11
	    dp->mtu + sizeof (struct ether_header) + ETHERFCSL + 4);
E 11

	OUTL(dp, RxSTAT, INL(dp, RxSTAT));

E 8
D 6
	OUTL(dp, VLANCTRL, 0);
E 6
I 6
	(void) nfo_set_media(dp);
E 6
D 8
#endif
E 8
I 8

E 8
I 6
	OUTL(dp, RxDEFER, 0x16);
D 11

E 11
I 11
D 13
#ifdef CONFIG_VLAN_HARD
E 13
I 13
#ifdef CONFIG_VLAN_HW
E 13
E 11
D 8
	OUTL(dp, VLANCTRL, ((lp->hwcap & CAP_VLAN) != 0) ? VLANCTRL_EN : 0);
E 8
I 8
D 10
	if ((lp->hwcap & CAP_VLAN) != 0) {
E 10
I 10
	if (lp->hwcap & CAP_VLAN) {
E 10
		OUTL(dp, VLANCTRL, VLANCTRL_EN);
	}
I 11
#endif
E 11
E 8
E 6
D 13
#ifdef GEM_CONFIG_POLLING
E 13
I 13
#ifdef CONFIG_POLLING
E 13
	lp->last_poll_interval = 0;
#endif
I 3

D 6
	nfo_set_media(dp);
E 6
I 6
	DPRINTF(2, (CE_CONT, "!%s: %s: out", dp->name, __func__));
E 6

E 3
D 6
	DPRINTF(2, (CE_CONT, "%s: %s: out", dp->name, __func__));
I 2

E 6
	return (GEM_SUCCESS);
E 2
}

D 2
static void
E 2
I 2
static int
E 2
nfo_start_chip(struct gem_dev *dp)
{
D 11
	int		i;
E 11
	uint32_t	val;
D 6
	struct nfo_dev	*lp = (struct nfo_dev *)dp->private;
E 6
I 6
D 11
	struct nfo_dev	*lp = (struct nfo_dev *) dp->private;
E 11
I 11
	struct nfo_dev	*lp = dp->private;
E 11
E 6

	DPRINTF(0, (CE_CONT, "!%s: %s: called at time:%d",
D 11
		dp->name, __func__, ddi_get_lbolt()));
E 11
I 11
	    dp->name, __func__, ddi_get_lbolt()));
E 11

I 6
D 8
	OUTL(dp, TxSTAT, INL(dp, TxSTAT));
	OUTL(dp, RxSTAT, INL(dp, RxSTAT));

E 6
	/* enable dma */
	OUTL(dp, DMACTRL, DMACTRL_START | lp->dmac);
	for (i = 0; (INL(dp, DMASTAT) & DMASTAT_RUNNING) == 0; i++) {
		if (i > 100) {
			cmn_err(CE_WARN, "!%s: %s: failed to start DMA engine",
				dp->name, __func__);
			break;
		}
		drv_usecwait(10);
	}

D 6
	OUTL(dp, REG_184, 0);

	OUTL(dp, MIIAUTO,
D 3
		(dp->mii_phy_addr << MIIAUTO_PHY_SHIFT) |
		MIIAUTO_PHYVALID | MIIAUTO_RUNNING);
E 3
I 3
		(dp->mii_phy_addr << MIIAUTO_PHYADDR_SHIFT) |
		MIIAUTO_PHYVALID | MIIAUTO_EN);
E 3

	OUTL(dp, MIICFG, 0x105);
	OUTL(dp, REG_184, 8);
D 3
	OUTL(dp, WAKECTRL, WAKECTRL_VAL);
E 3
I 3
	OUTL(dp, WAKECTRL, 0x7770);
E 3

D 3
#if 0
E 3
I 3
#ifdef notyet
E 6
I 6
#ifdef CONFIG_PM
E 8
E 6
E 3
	val = INL(dp, PWRSTAT);
	if ((val & PWRSTAT_POWEREDUP) == 0) {
D 2
		OUTL(dp, PowerState, PWRSTAT_POWEREDUP | val);
E 2
I 2
		OUTL(dp, PWRSTAT, PWRSTAT_POWEREDUP | val);
E 2
	}
D 8
	FLSHL(dp, PWRSTAT);
	drv_usecwait(10);
D 2
	OUTL(dp, PowerState, INL(dp, PWRSTAT) | PWRSTAT_VALID);
E 2
I 2
	OUTL(dp, PWRSTAT, INL(dp, PWRSTAT) | PWRSTAT_VALID);
E 2
D 6
#endif
E 6
I 6
#endif /* CONFIG_PM */
E 8
E 6
D 11

D 2
	/* clear bogus interrrups */
E 2
I 2
	/* clear bogus interrupts */
E 2
D 3
	OUTL(dp, MIISTAT, MIISTAT_LINKCHANGE);
E 3
I 3
D 6
	OUTL(dp, MIISTAT, MIISTAT_LSC);
E 6
I 6
	OUTL(dp, MIIISR, MIIISR_ALL);
I 10
	FLSHL(dp, MIIISR);
E 10
E 6
E 3
	OUTL(dp, ISR, INTR_ALL);
	FLSHL(dp, ISR);

E 11
I 8
	OUTL(dp, PWRSTAT, INL(dp, PWRSTAT) | PWRSTAT_VALID);

E 8
	lp->imr = OUR_INTR_BITS;
I 8
D 11
	if (IS_DFMT1(lp->dmac)) {
		lp->imr |= INTR_TXOK;
	}
E 11
E 8
#if DEBUG_LEVEL >= 5
	lp->imr |= INTR_TXOK;
#endif
I 6
D 11
	OUTL(dp, MIIIMR, MIIISR_LSC);
I 10
	FLSHL(dp, MIIIMR);
E 11
E 10
E 6
	if ((dp->misc_flag & GEM_NOINTR) == 0) {
I 11
		OUTL(dp, MIIIMR, MIIISR_LSC);
		FLSHL(dp, MIIIMR);
E 11
		OUTL(dp, IMR, lp->imr);
I 10
		FLSHL(dp, IMR);
E 10
I 6
D 11
		OUTL(dp, REG_008, 3);
I 10
		FLSHL(dp, REG_008);
E 11
I 11
D 13
#ifdef GEM_CONFIG_POLLING
E 13
I 13
#ifdef CONFIG_POLLING
E 13
		OUTL(dp, TIMERCTL, 3);
		FLSHL(dp, TIMERCTL);
#endif
E 11
E 10
E 6
	}

D 6
	/* start rx and tx */
	OUTL(dp, RxCTRL, RxCTRL_START);
E 6
I 6
	/* start rx */
	val = INL(dp, RxCTRL) | RxCTRL_START;
	if (lp->mac_in_use) {
		/* take rx path from management unit */
		val &= ~RxCTRL_RxPATH;
	}
	OUTL(dp, RxCTRL, val);

	/* start tx activety */
D 11
	val = INL(dp, TxCTRL)| TxCTRL_START;
E 11
I 11
	val = INL(dp, TxCTRL) | TxCTRL_START;
E 11
	if (lp->mac_in_use) {
		/* take tx path from management unit */
		val &= ~TxCTRL_TxPATH;
	}
E 6
D 11
        OUTL(dp, TxCTRL, TxCTRL_START);
E 11
I 11
	OUTL(dp, TxCTRL, val);
E 11

D 5
	DPRINTF(2, (CE_CONT, "%s: %s: return", dp->name, __func__));
E 5
I 5
	DPRINTF(2, (CE_CONT, "!%s: %s: return", dp->name, __func__));
E 5
I 2

	return (GEM_SUCCESS);
E 2
}

static int
nfo_stop_chip(struct gem_dev *dp)
{
	int		i;
D 6
	struct nfo_dev	*lp = (struct nfo_dev *)dp->private;
E 6
I 6
	int		ret;
	uint32_t	val;
D 11
	struct nfo_dev	*lp = (struct nfo_dev *) dp->private;
E 11
I 11
	struct nfo_dev	*lp = dp->private;
E 11
E 6

D 13
	DPRINTF(2, (CE_CONT, "!%s: %s: called at time:%d",
E 13
I 13
	DPRINTF(0, (CE_CONT, "!%s: %s: called at time:%d",
E 13
D 11
		dp->name, __func__, ddi_get_lbolt()));
E 11
I 11
	    dp->name, __func__, ddi_get_lbolt()));
E 11

D 6
	OUTL(dp, TxCTRL, 0);
E 6
I 6
	ret = GEM_SUCCESS;
E 6
D 13

E 13
I 13
#ifdef notdef
E 13
I 6
D 8
	/* stop tx activety */
E 8
I 8
D 11
	/*
	 * Ensure dma is not working
	 */
E 11
I 11
	/* wait until dma engine becomes idle */
E 11
	OUTL(dp, DMACTRL, DMACTRL_STOP | lp->dmac);

	for (i = 0; (INL(dp, DMACTRL) & DMACTRL_IDLE) == 0; i++) {
		if (i > 10000) {
I 13
			cmn_err(CE_WARN, "!%s: %s: timeout - DMACTRL busy",
			    dp->name, __func__);
E 13
			ret = GEM_FAILURE;
			break;
		}
		drv_usecwait(50);
	}
D 13

E 13
I 13
#endif
E 13
D 11
	/*
	 * Stop tx activety
	 */
E 11
I 11
	/* stop tx activety */
E 11
E 8
	val = INL(dp, TxCTRL);
	if (!lp->mac_in_use) {
		/* stop tx completely */
		val &= ~TxCTRL_START;
	} else {
		/* return tx path for management unit */
		val |= TxCTRL_TxPATH;
	}
	OUTL(dp, TxCTRL, val);

E 6
D 10
	for (i = 0; (INL(dp, TxSTAT) & TxSTAT_RUNNING) != 0; i++) {
E 10
I 10
	for (i = 0; (INL(dp, TxSTAT) & TxSTAT_RUNNING); i++) {
E 10
		if (i > 500) {
D 5
			cmn_err(CE_WARN, "%s: %s tx still running",
E 5
I 5
			cmn_err(CE_WARN, "!%s: %s tx engine is still running",
E 5
D 11
				dp->name, __func__);
E 11
I 11
			    dp->name, __func__);
E 11
D 6
			return (GEM_FAILURE);
E 6
I 6
			ret = GEM_FAILURE;
			break;
E 6
		}
		drv_usecwait(10);
	}
D 6

E 6
	drv_usecwait(100);

D 6
	OUTL(dp, REG_008, 0);
E 6
I 6
D 8
	if (!lp->mac_in_use) {
		OUTL(dp, TxPOLL, INL(dp, TxPOLL) & TxPOLL_MACADDR_REV);
	}
E 6

D 6
	OUTL(dp, RxCTRL, 0);
E 6
I 6
	/* stop rx activety */
E 8
I 8
D 11
	/*
	 * Stop rx activety
	 */
E 11
I 11
	/* stop rx activety */
E 11
E 8
	val = INL(dp, RxCTRL);
	if (!lp->mac_in_use) {
		/* stop rx completely */
		val &= ~RxCTRL_START;
	} else {
		/* return rx path for management unit */
		val |= RxCTRL_RxPATH;
	}
	OUTL(dp, RxCTRL, val);
E 6

D 10
	for (i = 0; (INL(dp, RxSTAT) & RxSTAT_RUNNING) != 0; i++) {
E 10
I 10
	for (i = 0; (INL(dp, RxSTAT) & RxSTAT_RUNNING); i++) {
E 10
		if (i > 500) {
D 5
			cmn_err(CE_WARN, "!%s: %s: rx still running",
E 5
I 5
			cmn_err(CE_WARN, "!%s: %s: rx engine is still running",
E 5
D 11
				dp->name, __func__);
E 11
I 11
			    dp->name, __func__);
E 11
D 6
			return (GEM_FAILURE);
E 6
I 6
			ret = GEM_FAILURE;
			break;
E 6
		}
		drv_usecwait(10);
	}
D 6

E 6
	drv_usecwait(100);
D 6
	OUTL(dp, CLKCTRL, 0);
E 6

D 6
	nfo_reset_chip(dp);
E 6
I 6
D 11
	(void) nfo_reset_chip(dp);
E 11
I 11
	/* inhibit interrupts */
	OUTL(dp, MIIIMR, 0);
	FLSHL(dp, MIIIMR);
	OUTL(dp, IMR, 0);
	FLSHL(dp, IMR);
E 11
E 6

D 6
	/*
	 * XXX - We need to restore the original factory mac address.
	 * Once we changed the node addresss, there is no way
	 * to get the correct address.
	 */
	OUTL(dp, MACADDR + 0, lp->factory_mac_addr[0]);
	OUTL(dp, MACADDR + 4, lp->factory_mac_addr[1]);
E 6
I 6
D 8
	if ((INL(dp, TxPOLL) & TxPOLL_MACADDR_REV) == 0) {
E 8
I 8
D 11
	if ((INL(dp, TxPOLL) & TxPOLL_MACADDR_REV) == 0 &&
	    (lp->chip->hwcap & CAP_CORRECT_MAC) == 0) {
E 8
		/*
		 * XXX - We need to restore the original factory mac address.
		 * Once we changed the node addresss, there is no way
		 * to get the correct address.
		 */
		OUTL(dp, MACADDR + 0, lp->factory_mac_addr[0]);
		OUTL(dp, MACADDR + 4, lp->factory_mac_addr[1]);
	}
E 11
I 11
	/* reset dma engine */
	OUTL(dp, DMACTRL, DMACTRL_RESET | DMACTRL_STOP | lp->dmac);
	FLSHL(dp, DMACTRL);
	drv_usecwait(20);
E 11
E 6

I 11
	OUTL(dp, DMACTRL, DMACTRL_STOP | lp->dmac);
	FLSHL(dp, DMACTRL);
	drv_usecwait(20);

	/* disable timer */
	OUTL(dp, TIMERCTL, 0);
	FLSHL(dp, TIMERCTL);

E 11
D 6
	return (GEM_SUCCESS);
E 6
I 6
	return (ret);
E 6
}

D 2
static void
E 2
I 2
static int
E 2
D 11
nfo_set_rx_filter(struct gem_dev *dp)	
E 11
I 11
nfo_set_rx_filter(struct gem_dev *dp)
E 11
{
D 11
	int		i, j;
E 11
I 11
	int		i;
E 11
	uint32_t	mode;
	uint8_t		*m;
	uint64_t	mac;
	uint64_t	oraddr;
	uint64_t	andaddr;
	uint64_t	MulticastMask;
	uint64_t	MulticastAddress;
D 6
	struct nfo_dev	*lp = (struct nfo_dev *)dp->private;
E 6
I 6
D 11
	struct nfo_dev	*lp = (struct nfo_dev *) dp->private;
E 11
I 11
	struct nfo_dev	*lp = dp->private;
E 11
E 6

I 13
	m = dp->cur_addr.ether_addr_octet;
E 13
	DPRINTF(0, (CE_CONT, "!%s: %s: called at time:%d, "
D 11
		"active:%d, rxmode:%b",
		dp->name, __func__, ddi_get_lbolt(),
D 10
		dp->mac_active, dp->rxmode, "\020\002AllMulti\001Promisc"));
E 10
I 10
		dp->mac_active, dp->rxmode, RXMODE_BITS));
E 11
I 11
D 13
	    "active:%d, rxmode:%b",
E 13
I 13
	    "active:%d, rxmode:%b, %02x:%02x:%02x:%02x:%02x:%02x",
E 13
	    dp->name, __func__, ddi_get_lbolt(),
D 13
	    dp->mac_active, dp->rxmode, RXMODE_BITS));
E 13
I 13
	    dp->mac_active, dp->rxmode, RXMODE_BITS,
	    m[0], m[1], m[2], m[3], m[4], m[5]));
E 13
E 11
E 10

	/*
	 * Initialize filter
	 */
D 11
	bzero(&oraddr, sizeof(oraddr));
	bzero(&andaddr, sizeof(andaddr));
E 11
I 11
	bzero(&oraddr, sizeof (oraddr));
	bzero(&andaddr, sizeof (andaddr));
E 11
D 6
	mode = RxPF_MBO;
E 6
I 6
	mode = RxPF_MBO | (INL(dp, RxPF) & RxPF_RxPAUSE);
E 6

	if ((dp->rxmode & RXMODE_ENABLE) == 0) {
D 11
		MulticastMask    = 0xffffffffffffull;
E 11
I 11
		MulticastMask = 0xffffffffffffull;
E 11
		MulticastAddress = 0x000000000000ull;
D 11
	}
	else if ((dp->rxmode & RXMODE_PROMISC) != 0) {
E 11
I 11
	} else if ((dp->rxmode & RXMODE_PROMISC) != 0) {
E 11
		mode |= RxPF_PROMISC;
D 11
	}
	else if ((dp->rxmode & RXMODE_ALLMULTI) != 0 || dp->mc_count > 32) {
E 11
I 11
	} else if ((dp->rxmode & RXMODE_ALLMULTI) != 0 || dp->mc_count > 32) {
E 11
		mode |= RxPF_UNICAST;
D 11
		MulticastMask    = 0x000000000001ull;
E 11
I 11
		MulticastMask = 0x000000000001ull;
E 11
		MulticastAddress = 0x000000000001ull;
D 11
        }
        else if (dp->mc_count > 0) {
E 11
I 11
	} else if (dp->mc_count > 0) {
E 11
		/*
		 * Process multicast address list
		 */
		mode |= RxPF_UNICAST;

		andaddr = 0xffffffffffffull;
D 11
		oraddr  = 0x000000000000ull;
E 11
I 11
		oraddr = 0x000000000000ull;
E 11

		for (i = 0; i < dp->mc_count; i++) {
			m = dp->mc_list[i].addr.ether_addr_octet;
D 11
			mac = (((uint64_t) LE16PACKED(m+4)) << 32)
			    | ((uint64_t) LE32PACKED(m));
E 11
I 11
			mac = (((uint64_t)LE16PACKED(m+4)) << 32)
			    | ((uint64_t)LE32PACKED(m));
E 11

D 11
			andaddr  &= mac;
			oraddr   |= mac;
E 11
I 11
			andaddr &= mac;
			oraddr |= mac;
E 11
		}

D 11
		/* 
		 * Write 1s to mask where all addresses have 0 bit or 1 bit. 
E 11
I 11
		/*
		 * Write 1s to mask where all addresses have 0 bit or 1 bit.
E 11
		 * Compute mask and address value.
		 */
		MulticastAddress = (andaddr & oraddr) | 1ull;
D 11
		MulticastMask    = (andaddr | ~oraddr) | 1ull;
        }
	else {
E 11
I 11
		MulticastMask = (andaddr | ~oraddr) | 1ull;
	} else {
E 11
		mode |= RxPF_UNICAST;
	}

	OUTL(dp, RxPF, mode);
	if ((dp->rxmode & RXMODE_ENABLE) != 0) {
		OUTL(dp, MCASTMASK + 0, 1);
		OUTL(dp, MCASTMASK + 4, 0);
	}
D 11
	OUTL(dp, MCASTADDR + 0, (uint32_t) MulticastAddress);
E 11
I 11
	OUTL(dp, MCASTADDR + 0, (uint32_t)MulticastAddress);
E 11
	OUTL(dp, MCASTADDR + 4, (uint32_t)(MulticastAddress >> 32));
D 11
	OUTL(dp, MCASTMASK + 0, (uint32_t) MulticastMask);
E 11
I 11
	OUTL(dp, MCASTMASK + 0, (uint32_t)MulticastMask);
E 11
	OUTL(dp, MCASTMASK + 4, (uint32_t)(MulticastMask >> 32));

D 13
	if (bcmp(dp->cur_addr.ether_addr_octet,
D 11
			lp->mac_addr, ETHERADDRL) != 0) {
E 11
I 11
	    lp->mac_addr, ETHERADDRL) != 0) {
E 13
I 13
	m = dp->cur_addr.ether_addr_octet;
	if (bcmp(m, lp->mac_addr, ETHERADDRL) != 0) {
E 13
E 11
		/* Set new node address */
D 13
		m = dp->cur_addr.ether_addr_octet;
E 13
		bcopy(m, lp->mac_addr, ETHERADDRL);
		OUTL(dp, MACADDR + 0, LE32PACKED(m));
		OUTL(dp, MACADDR + 4, LE16PACKED(m+4));
	}

D 5
	DPRINTF(2, (CE_CONT, "%s: %s return", dp->name, __func__));
E 5
I 5
	DPRINTF(2, (CE_CONT, "!%s: %s return", dp->name, __func__));
E 5
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
nfo_set_media(struct gem_dev *dp)
{
D 11
	uint32_t	clkctrl;
D 8
	uint32_t	phyreg;
E 8
I 8
	uint32_t	clk_div10;
E 8
	uint32_t	misc;
	uint32_t	rndctrl;
E 11
I 11
	uint32_t	rxpoll;
	uint32_t	txcfg;
	uint32_t	backoff;
E 11
D 6
	struct nfo_dev	*lp = (struct nfo_dev *)dp->private;
E 6
I 6
	uint32_t	rxpf;
	uint32_t	phyif;
	uint32_t	txdefer;
	uint32_t	txwm;
D 11
	struct nfo_dev	*lp = (struct nfo_dev *) dp->private;
E 11
I 11
	struct nfo_dev	*lp = dp->private;
E 11
E 6

D 11
	DPRINTF(0, (CE_CONT, "!%s: %s: called at time:%d",
		dp->name, __func__, ddi_get_lbolt(),
		dp->mac_active));
E 11
I 11
	DPRINTF(0, (CE_CONT, "!%s: %s: called at time:%ld",
	    dp->name, __func__, ddi_get_lbolt(), dp->mac_active));
E 11

D 8
	/*
	 * Set speed and duplex settings on the hardware
	 */
D 3
	phyreg  = INL(dp, PHYIF) & ~(PHYIF_HALF | PHYIF_100 | PHYIF_1000);
	misc    = MISC_FORCE;
	clkctrl = CLKCTRL_EN;
E 3
I 3
	phyreg  = INL(dp, PHYIF) & ~(PHYIF_HALF | PHYIF_SPEED);
	misc    = MISC_CONST;
	clkctrl = CLKCTRL_FIXED;
E 3
	rndctrl = INL(dp, RNDCTRL) & ~(RNDCTRL_SPEED);
I 6
	rxpf    = INL(dp, RxPF);
	phyif   = INL(dp, PHYIF);
	txdefer = 0x15050f;
	txwm    = IS_DFMT1(lp->dmac) ? 0x0200010 : 0x1e08000;
E 8
I 8
D 11
	/* setup duplex and tx flow control */
	misc = dp->full_duplex ?  MISC_CONST : (MISC_CONST | MISC_HD);
E 11
I 11
	/*
	 * Set speed and duplex settings depend on the hardware
	 */

	/* tx config register */
	txcfg = TxCFG_DEFAULT;
	/*
	 * XXX - HD bit is required for legacy chipset, i.e. MCP1 family,
	 * but it seems no effect for recent chipset.
	 */
	if (!dp->full_duplex) {
		txcfg |= TxCFG_HD;
	}
E 11
D 10
	if ((lp->hwcap & CAP_TXPAUSE) != 0) {
E 10
I 10
D 13
	if (lp->hwcap & CAP_TXPAUSE) {
E 13
I 13
	if (lp->hwcap & (CAP_TXPAUSE1 | CAP_TXPAUSE2 | CAP_TXPAUSE3)) {
E 13
E 10
		switch (dp->flow_control) {
		case FLOW_CONTROL_SYMMETRIC:
		case FLOW_CONTROL_TX_PAUSE:
D 11
			misc |= MISC_TxPAUSE;
E 11
I 11
			txcfg |= TxCFG_TxPAUSE;
E 11
			break;
E 8
E 6

D 8
	switch (dp->speed) {
	case GEM_SPD_10:
		clkctrl |= CLKCTRL_DIV_10M;
I 3
		phyreg  |= PHYIF_SPEED_10M;
E 3
		rndctrl |= RNDCTRL_SPEED_10M;
I 6
		if ((phyif & PHYIF_RGMII) != 0) {
			txdefer = 0x16070f;
E 8
I 8
D 13
		case FLOW_CONTROL_RX_PAUSE:
		case FLOW_CONTROL_NONE:
E 13
I 13
		default:
E 13
D 11
			misc &= ~MISC_TxPAUSE;
E 11
I 11
			txcfg &= ~TxCFG_TxPAUSE;
E 11
			break;
E 8
		}
E 6
D 8
		break;

	case GEM_SPD_100:
		clkctrl |= CLKCTRL_DIV_100M;
D 3
		phyreg  |= PHYIF_100;
E 3
I 3
		phyreg  |= PHYIF_SPEED_100M;
E 3
		rndctrl |= RNDCTRL_SPEED_100M;
I 6
		if ((phyif & PHYIF_RGMII) != 0) {
			txdefer = 0x16070f;
		}
E 6
		break;

	case GEM_SPD_1000:
		clkctrl |= CLKCTRL_DIV_1G;
D 3
		phyreg  |= PHYIF_1000;
E 3
I 3
		phyreg  |= PHYIF_SPEED_1G;
E 3
		rndctrl |= RNDCTRL_SPEED_1G;
I 6
		if ((phyif & PHYIF_RGMII) != 0) {
			txdefer = 0x14050f;
		}
		if (!IS_DFMT1(lp->dmac)) {
			txwm = 0xfe08000;
		}
E 6
		break;
E 8
	}

D 8
	if (!dp->full_duplex) {
		phyreg |= PHYIF_HALF;
		misc   |= MISC_HD;
	}
E 8
I 8
D 11
	DPRINTF(0, (CE_CONT, "!%s: %s MISC:%x -> %x",
		dp->name, __func__, INL(dp, MISC), misc));
	OUTL(dp, MISC, misc);
	FLSHL(dp, MISC);
E 11
I 11
	DPRINTF(1, (CE_CONT, "!%s: %s TxCFG:%x -> %x",
	    dp->name, __func__, INL(dp, TxCFG), txcfg));
	OUTL(dp, TxCFG, txcfg);
	FLSHL(dp, TxCFG);
E 11
E 8

I 6
D 8
	/* setup flow control */
E 8
I 8
	/* setup rx flow control */
	rxpf = INL(dp, RxPF);

E 8
	switch (dp->flow_control) {
	case FLOW_CONTROL_SYMMETRIC:
	case FLOW_CONTROL_RX_PAUSE:
		rxpf |= RxPF_RxPAUSE;
		break;

	case FLOW_CONTROL_TX_PAUSE:
	case FLOW_CONTROL_NONE:
		rxpf &= ~RxPF_RxPAUSE;
		break;
	}

D 8
	if ((lp->hwcap & CAP_TXPAUSE) != 0) {
		switch (dp->flow_control) {
		case FLOW_CONTROL_SYMMETRIC:
		case FLOW_CONTROL_TX_PAUSE:
			misc |= MISC_TxPAUSE;
E 8
I 8
D 11
	DPRINTF(0, (CE_CONT, "!%s: %s RxPF:%x -> %x",
		dp->name, __func__, INL(dp, RxPF), rxpf));
E 11
I 11
	DPRINTF(1, (CE_CONT, "!%s: %s RxPF:%x -> %x",
	    dp->name, __func__, INL(dp, RxPF), rxpf));
E 11
	OUTL(dp, RxPF, rxpf);
	FLSHL(dp, RxPF);

D 11
	/*
	 * Set speed and duplex settings on the hardware
	 */
E 11
I 11
	/* tx watermark register */
E 11
	if (IS_DFMT1(lp->dmac)) {
I 11
		/* descriptor format 1 */
E 11
		txwm = 0x0200010;
	} else {
D 11
		txwm = IS_TYPE4_OR_LATER(lp) ? 0x1e08000 : 0x1e08020;
E 11
I 11
		/* descriptor format 2 or 3 */
		if (dp->speed == GEM_SPD_1000) {
			txwm = 0x0fe08000;
		} else {
			txwm = 0x01e08000;
		}
E 11
	}
D 11
	txdefer = IS_TYPE4_OR_LATER(lp) ? 0x15050f : 0x16070f;
E 11

D 11
	clkctrl = CLKCTRL_FIXED;
E 11
I 11
	DPRINTF(1, (CE_CONT, "!%s: %s TXWM:%x -> %x",
	    dp->name, __func__, INL(dp, TXWM), txwm));
	OUTL(dp, TXWM, txwm);
	FLSHL(dp, TXWM);

	/* rx polling register */
	rxpoll = RxPOLL_EN;
E 11
	switch (dp->speed) {
	case GEM_SPD_1000:
D 11
#ifdef CONFIG_V1COMPAT
		/* falldown */
#else
		clkctrl |= CLKCTRL_DIV_1G;
E 11
I 11
		rxpoll |= RxPOLL_ITV_1G;
E 11
		break;
D 11
#endif
E 11
I 11

E 11
	case GEM_SPD_10:
D 11
		clkctrl |= CLKCTRL_DIV_10M;
E 11
I 11
		rxpoll |= RxPOLL_ITV_10M;
E 11
		break;

	case GEM_SPD_100:
D 11
		clkctrl |= CLKCTRL_DIV_100M;
E 11
I 11
		rxpoll |= RxPOLL_ITV_100M;
E 11
		break;

	}
D 11
	DPRINTF(0, (CE_CONT, "!%s: %s CLKCTRL:%x -> %x",
		dp->name, __func__, INL(dp, CLKCTRL), clkctrl));
	OUTL(dp, CLKCTRL, clkctrl);
	FLSHL(dp, CLKCTRL);
E 11
I 11
	DPRINTF(1, (CE_CONT, "!%s: %s RxPOLL:%x -> %x",
	    dp->name, __func__, INL(dp, RxPOLL), rxpoll));
	OUTL(dp, RxPOLL, rxpoll);
	FLSHL(dp, RxPOLL);
E 11

D 11
	phyif = INL(dp, PHYIF);
	rndctrl = INL(dp, RNDCTRL);
E 11
I 11
	/* phy interface register */
	phyif = INL(dp, PHYIF) & ~(PHYIF_HALF | PHYIF_SPEED);
	/*
	 * XXX - duplex and speed bits are required for recent chipset,
	 * but it seems no effect for legacy chipset.
	 */
	if (!dp->full_duplex) {
		phyif |= PHYIF_HALF;
	}
	switch (dp->speed) {
	case GEM_SPD_10:
		phyif |= PHYIF_SPEED_10M;
		break;

	case GEM_SPD_100:
		phyif |= PHYIF_SPEED_100M;
		break;

	case GEM_SPD_1000:
		phyif |= PHYIF_SPEED_1G;
		break;
	}

	DPRINTF(1, (CE_CONT, "!%s: %s PHYIF:%x -> %x",
	    dp->name, __func__, INL(dp, PHYIF), phyif));
	OUTL(dp, PHYIF, phyif);

	/* backoff and tx defer register */
	backoff = 8;
E 11
D 10
	if ((phyif & PHYIF_RGMII) != 0) {
E 10
I 10
	if (phyif & PHYIF_RGMII) {
E 10
D 11
		phyif &= ~(PHYIF_HALF | PHYIF_SPEED);
		rndctrl &= ~RNDCTRL_SPEED;
E 11
		switch (dp->speed) {
		case GEM_SPD_10:
D 11
			phyif   |= PHYIF_SPEED_10M;
			rndctrl |= RNDCTRL_SPEED_10M;
E 11
I 11
			backoff |= BACKOFF_SPEED_10M;
E 11
D 12
			txdefer = 0x16070f;
E 12
I 12
D 13
			txdefer = 0x0016070f;
E 13
I 13
			if ((dp->mii_exp & MII_AN_EXP_LPCANAN) == 0 &&
			    (!dp->full_duplex) && (lp->hwcap & CAP_COLFIX)) {
				txdefer = 0x0016190f;
			} else {
				txdefer = 0x0016070f;
			}
E 13
E 12
E 8
			break;

D 8
		case FLOW_CONTROL_RX_PAUSE:
		case FLOW_CONTROL_NONE:
			misc &= ~MISC_TxPAUSE;
E 8
I 8
		case GEM_SPD_100:
D 11
			phyif   |= PHYIF_SPEED_100M;
			rndctrl |= RNDCTRL_SPEED_100M;
E 11
I 11
			backoff |= BACKOFF_SPEED_100M;
E 11
D 12
			txdefer = 0x16070f;
E 12
I 12
D 13
			txdefer = 0x0016070f;
E 13
I 13
			if ((dp->mii_exp & MII_AN_EXP_LPCANAN) == 0 &&
			    (!dp->full_duplex) && (lp->hwcap & CAP_COLFIX)) {
				txdefer = 0x0016300f;
			} else {
				txdefer = 0x0016070f;
			}
E 13
E 12
E 8
			break;
I 8

		case GEM_SPD_1000:
D 11
			phyif   |= PHYIF_SPEED_1G;
			rndctrl |= RNDCTRL_SPEED_1G;
			txwm = 0xfe08000;
			txdefer = 0x14050f;
E 11
I 11
			backoff |= BACKOFF_SPEED_1G;
			if (dp->full_duplex) {
D 12
				txdefer = 0x14050f;
E 12
I 12
				txdefer = 0x0014050f;
E 12
			} else {
D 12
				txdefer = 0x16050f;
E 12
I 12
				txdefer = 0x0016050f;
E 12
			}
E 11
			break;
E 8
		}
D 8
	}
E 8
D 11

D 8
	/* update registers */
E 6
	if (rndctrl != INL(dp, RNDCTRL)) {
E 8
I 8
		if (!dp->full_duplex) {
			phyif |= PHYIF_HALF;
		}

		/*
		 * Update registers for RGMII
		 */
		/* XXX - we can write PHYIF only RGMII */
		DPRINTF(0, (CE_CONT, "!%s: %s PHYIF:%x -> %x",
			dp->name, __func__, INL(dp, PHYIF), phyif));
		OUTL(dp, PHYIF, phyif);
		FLSHL(dp, PHYIF);

E 8
D 6
		DPRINTF(0, (CE_CONT, "%s: %s RNDCTRL:%x -> %x",
E 6
I 6
		DPRINTF(0, (CE_CONT, "!%s: %s RNDCTRL:%x -> %x",
E 6
			dp->name, __func__, INL(dp, RNDCTRL), rndctrl));
		OUTL(dp, RNDCTRL, rndctrl);
		FLSHL(dp, RNDCTRL);
E 11
I 11
	} else {
		backoff |= BACKOFF_SPEED_MII;
D 13
		txdefer = 0x15050f;
E 13
I 13
		if ((dp->mii_exp & MII_AN_EXP_LPCANAN) == 0 &&
		    (!dp->full_duplex) && (lp->hwcap & CAP_COLFIX)) {
			txdefer = 0x152000;
		} else {
			txdefer = 0x15050f;
		}
E 13
E 11
	}

D 8
	if (phyreg != INL(dp, PHYIF)) {
D 6
		DPRINTF(0, (CE_CONT, "%s: %s PHYIF:%x -> %x",
E 6
I 6
		DPRINTF(0, (CE_CONT, "!%s: %s PHYIF:%x -> %x",
E 6
			dp->name, __func__, INL(dp, PHYIF), phyreg));
		OUTL(dp, PHYIF, phyreg);
		FLSHL(dp, PHYIF);
	}
E 8
I 8
D 11
	DPRINTF(0, (CE_CONT, "!%s: %s TxDEFER:%x -> %x",
		dp->name, __func__, INL(dp, TxDEFER), txdefer));
E 11
I 11
	DPRINTF(1, (CE_CONT, "!%s: %s BACKOFF:%x -> %x",
	    dp->name, __func__, INL(dp, BACKOFF), backoff));
	OUTL(dp, BACKOFF, backoff);
	FLSHL(dp, BACKOFF);

	DPRINTF(1, (CE_CONT, "!%s: %s TxDEFER:%x -> %x",
	    dp->name, __func__, INL(dp, TxDEFER), txdefer));
E 11
	OUTL(dp, TxDEFER, txdefer);
	FLSHL(dp, TxDEFER);
E 8

D 8
	if (misc != INL(dp, MISC)) {
D 6
		DPRINTF(0, (CE_CONT, "%s: %s MISC:%x -> %x",
E 6
I 6
		DPRINTF(0, (CE_CONT, "!%s: %s MISC:%x -> %x",
E 6
			dp->name, __func__, INL(dp, MISC), misc));
		OUTL(dp, MISC, misc);
		FLSHL(dp, MISC);
	}
E 8
I 8
D 11
	DPRINTF(0, (CE_CONT, "!%s: %s TXWM:%x -> %x",
		dp->name, __func__, INL(dp, TXWM), txwm));
	OUTL(dp, TXWM, txwm);
	FLSHL(dp, TXWM);
E 8

E 11
I 11
	/* tx pause regiseter */
E 11
D 8
	if (clkctrl != INL(dp, CLKCTRL)) {
D 3
		DPRINTF(0, (CE_CONT, "%s: %s CLKCTRL:%x -> %x",
E 3
I 3
D 6
		DPRINTF(1, (CE_CONT, "%s: %s CLKCTRL:%x -> %x",
E 6
I 6
		DPRINTF(0, (CE_CONT, "!%s: %s CLKCTRL:%x -> %x",
E 6
E 3
			dp->name, __func__, INL(dp, CLKCTRL), clkctrl));
		OUTL(dp, CLKCTRL, clkctrl);
		FLSHL(dp, CLKCTRL);
	}
I 2

I 6
	if (rxpf != INL(dp, RxPF)) {
		DPRINTF(0, (CE_CONT, "!%s: %s RxPF:%x -> %x",
			dp->name, __func__, INL(dp, RxPF), rxpf));
		OUTL(dp, RxPF, rxpf);
		FLSHL(dp, RxPF);
	}

E 8
D 10
	if ((lp->hwcap & CAP_TXPAUSE) != 0) {
E 10
I 10
D 13
	if (lp->hwcap & CAP_TXPAUSE) {
E 13
I 13
	if (lp->hwcap & (CAP_TXPAUSE1 | CAP_TXPAUSE2 | CAP_TXPAUSE3)) {
E 13
E 10
		uint32_t	txpause;

D 10
		txpause = ((misc & MISC_TxPAUSE) != 0) ?
E 10
I 10
D 11
		txpause = (misc & MISC_TxPAUSE) ?
E 10
				TXPAUSE_EN : TXPAUSE_DIS;
D 8
		if (txpause != INL(dp, TXPAUSE)) {
			DPRINTF(0, (CE_CONT, "!%s: %s TXPAUSE:%x -> %x",
				dp->name, __func__, INL(dp, TXPAUSE), txpause));
			OUTL(dp, TXPAUSE, txpause);
			FLSHL(dp, TXPAUSE);
		}
E 8
I 8
		DPRINTF(0, (CE_CONT, "!%s: %s TXPAUSE:%x -> %x",
			dp->name, __func__, INL(dp, TXPAUSE), txpause));
E 11
I 11
D 13
		txpause = (txcfg & TxCFG_TxPAUSE) ? TXPAUSE_EN : TXPAUSE_DIS;
E 13
I 13
		if ((txcfg & TxCFG_TxPAUSE) == 0) {
			txpause = TXPAUSE_DIS;
		} else if (lp->hwcap & CAP_TXPAUSE1) {
			txpause = TXPAUSE_EN1;
		} else if (lp->hwcap & CAP_TXPAUSE2) {
			txpause = TXPAUSE_EN2;
		} else {
			ASSERT(lp->hwcap & CAP_TXPAUSE3);
			txpause = TXPAUSE_EN3;
		}
E 13
		DPRINTF(1, (CE_CONT, "!%s: %s TXPAUSE:%x -> %x",
		    dp->name, __func__, INL(dp, TXPAUSE), txpause));
E 11
		OUTL(dp, TXPAUSE, txpause);
		FLSHL(dp, TXPAUSE);
E 8
	}
D 10

E 10
I 10
D 11
#if DEBUG_LEVEL > 0
E 10
D 8
	if (txdefer != INL(dp, TxDEFER)) {
		DPRINTF(0, (CE_CONT, "!%s: %s TxDEFER:%x -> %x",
			dp->name, __func__, INL(dp, TxDEFER), txdefer));
		OUTL(dp, TxDEFER, txdefer);
		FLSHL(dp, TxDEFER);
	}
E 8
I 8
	nfo_dump_regs(dp, "set_media");
E 11
I 11
#if DEBUG_LEVEL > 2
	nfo_dump_regs(dp, (void *)__func__);
E 11
E 8
D 10

E 10
I 10
#endif
E 10
D 8
	if (txwm != INL(dp, TXWM)) {
		DPRINTF(0, (CE_CONT, "!%s: %s TXWM:%x -> %x",
			dp->name, __func__, INL(dp, TXWM), txwm));
		OUTL(dp, TXWM, txwm);
		FLSHL(dp, TXWM);
	}

E 8
E 6
	return (GEM_SUCCESS);
E 2
}

D 2
static void
E 2
I 2
static int
E 2
nfo_get_stats(struct gem_dev *dp)
{
I 2
	return (GEM_SUCCESS);
E 2
}

/*
 * discriptor manupiration
 */
static int
nfo_tx_desc_write32(struct gem_dev *dp, int slot,
D 10
		ddi_dma_cookie_t *dmacookie, int frags, uint32_t flags)
E 10
I 10
D 12
		ddi_dma_cookie_t *dmacookie, int frags, uint64_t flags)
E 12
I 12
    ddi_dma_cookie_t *dmacookie, int frags, uint64_t flags)
E 12
E 10
{
	int			i;
	struct txdesc32		*tdp;
	uint32_t		mark;
	ddi_dma_cookie_t	*dcp;
I 12
	uint32_t		mss;
I 13
	uint_t			tx_ring_size = dp->gc.gc_tx_ring_size;
E 13
E 12
D 6
	struct nfo_dev		*lp = (struct nfo_dev *)dp->private;
E 6
I 6
D 11
	struct nfo_dev		*lp = (struct nfo_dev *) dp->private;
E 11
I 11
	struct nfo_dev		*lp = dp->private;
E 11
E 6

#if DEBUG_LEVEL > 2
	cmn_err(CE_CONT,
D 10
	"!%s: %s: time: %d, seqnum: %d, slot %d, frags: %d flags: %d",
E 10
I 10
D 11
	"!%s: %s: time: %d, seqnum: %d, slot %d, frags: %d flags: %llx",
E 10
		dp->name, __func__, ddi_get_lbolt(),
		dp->tx_desc_tail, slot, frags, intreq);
E 11
I 11
	    "!%s: %s: time: %d, seqnum: %d, slot %d, frags: %d flags: %llx",
	    dp->name, __func__, ddi_get_lbolt(),
D 12
	    dp->tx_desc_tail, slot, frags, intreq);
E 12
I 12
	    dp->tx_desc_tail, slot, frags, flags);
E 12
E 11
	for (i = 0; i < frags; i++) {
		cmn_err(CE_CONT, "!%d: addr: 0x%llx, len: 0x%x",
D 11
			i, dmacookie[i].dmac_laddress, dmacookie[i].dmac_size);
E 11
I 11
		    i, dmacookie[i].dmac_laddress, dmacookie[i].dmac_size);
E 11
	}
#endif
#if DEBUG_LEVEL > 2
	flags |= GEM_TXFLAG_INTR;
#endif
	/*
	 * write tx descriptor(s) in reversed order
	 */
	if (IS_DFMT1(lp->dmac)) {
		/* format 1 */
D 8
		mark = TxD_LAST_1 | TxD_OWN;
		if ((flags & GEM_TXFLAG_INTR) != 0) {
			mark |= TxD_INT_1;
		}
E 8
I 8
D 11
		mark = TxD_LAST_1 | TxD_OWN | TxD_INT_1;
E 8
	}
	else {
E 11
I 11
		mark = TxD_LAST_1 | TxD_OWN;
		if (flags & GEM_TXFLAG_INTR) {
			mark |= TxD_INT_1_NF4 | TxD_INT_1;
		}
	} else {
E 11
		/* format 2 or later */
		mark = TxD_LAST_2 | TxD_OWN;
D 10
		if ((flags & GEM_TXFLAG_INTR) != 0) {
E 10
I 10
		if (flags & GEM_TXFLAG_INTR) {
E 10
			mark |= TxD_INT_2;
		}
D 5

		if ((flags & GEM_TXFLAG_IPv4) != 0) {
			mark |= TxD_CKSUM_IPv4_2;
			if ((flags & (GEM_TXFLAG_TCP | GEM_TXFLAG_UDP)) != 0) {
				mark |= TxD_CKSUM_TCPUDP_2;
			}
		}
E 5
	}

	dcp = &dmacookie[frags - 1];
	for (i = frags - 1; i > 0; i--) {
		int	curslot;

D 13
		curslot = SLOT(slot + i, TX_RING_SIZE);
E 13
I 13
		curslot = SLOT(slot + i, tx_ring_size);
E 13
D 11
		tdp = &((struct txdesc32 *)dp->tx_ring)[curslot];
E 11
I 11
D 12
		tdp = &NFO_TXDESC32(dp->tx_ring)[curslot];
E 12
I 12
		tdp = &TXDESC32(dp)[curslot];
E 12
E 11

		tdp->txd0 = dcp->dmac_address;
		tdp->txd1 = mark | (dcp->dmac_size - 1);

		mark &= TxD_OWN;
		dcp--;
	}
D 5

E 5
I 5
D 6
#ifdef GEM_CONFIG_CKSUM_OFFLOAD
E 6
I 6

I 13
#ifdef CONFIG_CKSUM_OFFLOAD
E 13
E 6
D 10
	if ((flags & GEM_TXFLAG_IPv4) != 0) {
E 10
I 10
D 12
	if (flags & GEM_TXFLAG_IPv4) {
E 12
I 12
	if (mss = ((flags & GEM_TXFLAG_MSS) >> GEM_TXFLAG_MSS_SHIFT)) {
		mark |= (mss << TxD_MSS_SHIFT_2) | TxD_TSO_2;
	} else if (flags & GEM_TXFLAG_IPv4) {
E 12
E 10
		mark |= TxD_CKSUM_IPv4_2;
D 10
		if ((flags & (GEM_TXFLAG_TCP | GEM_TXFLAG_UDP)) != 0) {
E 10
I 10
		if (flags & (GEM_TXFLAG_TCP | GEM_TXFLAG_UDP)) {
E 10
			mark |= TxD_CKSUM_TCPUDP_2;
		}
	}
D 6
#endif
E 6
I 6
D 13

E 13
I 13
#endif
E 13
E 6
E 5
D 10
	if ((flags & GEM_TXFLAG_HEAD) != 0) {
E 10
I 10
	if (flags & GEM_TXFLAG_HEAD) {
E 10
		/* remove own bit for the first fragment */
		mark &= ~TxD_OWN;
	}
D 11
	tdp = &((struct txdesc32 *)dp->tx_ring)[slot];
E 11
I 11
D 12
	tdp = &NFO_TXDESC32(dp->tx_ring)[slot];
E 12
I 12
	tdp = &TXDESC32(dp)[slot];
E 12
E 11

	tdp->txd0 = dcp->dmac_address;
	tdp->txd1 = mark | (dcp->dmac_size - 1);

	return (frags);
}

static int
nfo_tx_desc_write64(struct gem_dev *dp, int slot,
D 10
		ddi_dma_cookie_t *dmacookie, int frags, uint32_t flags)
E 10
I 10
D 12
		ddi_dma_cookie_t *dmacookie, int frags, uint64_t flags)
E 12
I 12
    ddi_dma_cookie_t *dmacookie, int frags, uint64_t flags)
E 12
E 10
{
	int			i;
	uint64_t		phys;
I 6
	uint32_t		vtag;
E 6
	uint32_t		mark;
	struct txdesc64		*tdp;
	ddi_dma_cookie_t	*dcp;
I 12
	uint32_t		mss;
I 13
	uint_t			tx_ring_size = dp->gc.gc_tx_ring_size;
E 13
E 12
D 11
	struct nfo_dev		*lp = (struct nfo_dev *) dp->private;
E 11

D 3
#if DEBUG_LEVEL > 0
E 3
I 3
D 12
#if DEBUG_LEVEL > 1
E 12
I 12
#if DEBUG_LEVEL > 2
E 12
E 3
	cmn_err(CE_CONT,
D 10
	"!%s: %s: time: %d, seqnum: %d, slot %d, frags: %d flags: %d",
E 10
I 10
D 11
	"!%s: %s: time: %d, seqnum: %d, slot %d, frags: %d flags: %llx",
E 10
		dp->name, __func__, ddi_get_lbolt(),
		dp->tx_desc_tail, slot, frags, flags);
E 11
I 11
	    "!%s: %s: time: %d, seqnum: %d, slot %d, frags: %d flags: %llx",
	    dp->name, __func__, ddi_get_lbolt(),
	    dp->tx_desc_tail, slot, frags, flags);
E 11
	for (i = 0; i < frags; i++) {
		cmn_err(CE_CONT, "!%d: addr: 0x%llx, len: 0x%x",
D 11
			i, dmacookie[i].dmac_laddress, dmacookie[i].dmac_size);
E 11
I 11
		    i, dmacookie[i].dmac_laddress, dmacookie[i].dmac_size);
E 11
	}
#endif
#if DEBUG_LEVEL > 2
	flags |= GEM_TXFLAG_INTR;
#endif
	/*
	 * write tx descriptor(s) in reversed order
	 */
	mark = TxD_LAST_2 | TxD_OWN;
D 10
	if ((flags & GEM_TXFLAG_INTR) != 0) {
E 10
I 10
	if (flags & GEM_TXFLAG_INTR) {
E 10
		mark |= TxD_INT_2;
	}

	dcp = &dmacookie[frags - 1];
	for (i = frags - 1; i > 0; i--) {
		phys = dcp->dmac_laddress;
D 11
		tdp = &((struct txdesc64 *) dp->tx_ring)
					[SLOT(slot + i, TX_RING_SIZE)];
E 11
I 11
D 12
		tdp = &((struct txdesc64 *)(void *)dp->tx_ring)
		    [SLOT(slot + i, TX_RING_SIZE)];
E 12
I 12
D 13
		tdp = &TXDESC64(dp)[SLOT(slot + i, TX_RING_SIZE)];
E 13
I 13
		tdp = &TXDESC64(dp)[SLOT(slot + i, tx_ring_size)];
E 13
E 12
E 11
D 6
		tdp->txd0 = (uint32_t) (phys >> 32);
E 6
I 6
		tdp->txd0 = (uint32_t)(phys >> 32);
E 6
D 11
		tdp->txd1 = (uint32_t) phys;
E 11
I 11
		tdp->txd1 = (uint32_t)phys;
E 11
		tdp->txd2 = 0;
		tdp->txd3 = mark | (dcp->dmac_size - 1);

		mark &= TxD_OWN;
		dcp--;
	}
D 5

E 5
I 5
D 6
#ifdef GEM_CONFIG_CKSUM_OFFLOAD
E 6
I 6

I 13
#ifdef CONFIG_CKSUM_OFFLOAD
E 13
E 6
E 5
D 10
	if ((flags & GEM_TXFLAG_IPv4) != 0) {
E 10
I 10
D 12
	if (flags & GEM_TXFLAG_IPv4) {
E 12
I 12
	if (mss = ((flags & GEM_TXFLAG_MSS) >> GEM_TXFLAG_MSS_SHIFT)) {
		mark |= (mss << TxD_MSS_SHIFT_2) | TxD_TSO_2;
	} else if (flags & GEM_TXFLAG_IPv4) {
E 12
E 10
		mark |= TxD_CKSUM_IPv4_2;
D 10
		if ((flags & (GEM_TXFLAG_TCP | GEM_TXFLAG_UDP)) != 0) {
E 10
I 10
		if (flags & (GEM_TXFLAG_TCP | GEM_TXFLAG_UDP)) {
E 10
			mark |= TxD_CKSUM_TCPUDP_2;
		}
	}
D 5

E 5
I 5
D 6
#endif
E 6
I 6
D 13

E 13
I 13
#endif
E 13
E 6
E 5
D 10
	if ((flags & GEM_TXFLAG_HEAD) != 0) {
E 10
I 10
	if (flags & GEM_TXFLAG_HEAD) {
E 10
		/* remove own bit for the first fragment */
		mark &= ~TxD_OWN;
	}

D 6
	phys = dcp->dmac_laddress;
E 6
D 11
	tdp = &((struct txdesc64 *)dp->tx_ring)[slot];
E 11
I 11
D 12
	tdp = &((struct txdesc64 *)(void *)dp->tx_ring)[slot];
E 12
I 12
	tdp = &TXDESC64(dp)[slot];
E 12
E 11

D 6
	tdp->txd0 = (uint32_t) (phys >> 32);
E 6
I 6
	phys = dcp->dmac_laddress;
	tdp->txd0 = (uint32_t)(phys >> 32);
E 6
D 11
	tdp->txd1 = (uint32_t) phys;
E 11
I 11
	tdp->txd1 = (uint32_t)phys;
E 11
D 6
#ifdef CONFIG_HWVLAN
	tdp->txd2 = ((flags & GEM_TXFLAG_VTAG) >> GEM_TXFLAG_VTAG_SHIFT)
		  | TxD_VLAN_EN;
#else
	tdp->txd2 = 0;
#endif
E 6
I 6

	vtag = (flags & GEM_TXFLAG_VTAG) >> GEM_TXFLAG_VTAG_SHIFT;
D 10
	if (vtag != 0) {
E 10
I 10
	if (vtag) {
E 10
		vtag |= TxD_VLAN_EN;
	}
	tdp->txd2 = vtag;

E 6
	tdp->txd3 = mark | (dcp->dmac_size - 1);

	return (frags);
}

static void
nfo_tx_start(struct gem_dev *dp, int start_slot, int nslot)
{
	uint32_t	own;
D 6
	struct nfo_dev	*lp = (struct nfo_dev *)dp->private;
E 6
I 6
D 11
	struct nfo_dev	*lp = (struct nfo_dev *) dp->private;
E 11
I 11
	struct nfo_dev	*lp = dp->private;
E 11
E 6

	own = TxD_OWN;

	if (nslot > 1) {
		gem_tx_desc_dma_sync(dp,
D 11
				SLOT(start_slot + 1, TX_RING_SIZE),
				nslot - 1, DDI_DMA_SYNC_FORDEV);
E 11
I 11
D 13
		    SLOT(start_slot + 1, TX_RING_SIZE),
E 13
I 13
		    SLOT(start_slot + 1, dp->gc.gc_tx_ring_size),
E 13
		    nslot - 1, DDI_DMA_SYNC_FORDEV);
E 11
	}

	if (IS_DFMT3(lp->dmac)) {
D 11
		((struct txdesc64 *)dp->tx_ring)[start_slot].txd3 |= own;
E 11
I 11
D 12
		NFO_TXDESC64(dp->tx_ring)[start_slot].txd3 |= own;
E 12
I 12
		TXDESC64(dp)[start_slot].txd3 |= own;
E 12
E 11
	} else {
D 11
		((struct txdesc32 *)dp->tx_ring)[start_slot].txd1 |= own;
E 11
I 11
D 12
		NFO_TXDESC32(dp->tx_ring)[start_slot].txd1 |= own;
E 12
I 12
		TXDESC32(dp)[start_slot].txd1 |= own;
E 12
E 11
	}

	gem_tx_desc_dma_sync(dp, start_slot, 1, DDI_DMA_SYNC_FORDEV);

D 13
	if (dp->mac_active) {
D 11
		/* kick dma engine for tx.*/
E 11
I 11
		/* kick dma engine for tx */
E 11
D 8
		OUTL(dp, DMACTRL, lp->dmac | DMACTRL_TxPOLL);
E 8
I 8
		OUTL(dp, DMACTRL, DMACTRL_TxPOLL | lp->dmac);
E 8
	}
E 13
I 13
	/* kick dma engine for tx */
	OUTL(dp, DMACTRL, DMACTRL_TxPOLL | lp->dmac);
E 13
}

static uint_t
nfo_tx_desc_stat(struct gem_dev *dp, int slot, int ndesc)
{
D 6
	struct nfo_dev	*lp = (struct nfo_dev *)dp->private;
E 6
I 6
D 11
	struct nfo_dev	*lp = (struct nfo_dev *) dp->private;
E 11
I 11
	struct nfo_dev	*lp = dp->private;
E 11
E 6
	uint_t		ret = GEM_TX_DONE;
	uint32_t	status;
	uint_t		curslot;
	int		col;

	/* check tx status flag in the last fragmenet */
D 13
	curslot = SLOT(slot + ndesc - 1, TX_RING_SIZE);
E 13
I 13
	curslot = SLOT(slot + ndesc - 1, dp->gc.gc_tx_ring_size);
E 13

	if (IS_DFMT3(lp->dmac)) {
		/* formt 3 (64bit addressing) */
D 11
		status = ((struct txdesc64 *) dp->tx_ring)[curslot].txd3;
E 11
I 11
D 12
		status = NFO_TXDESC64(dp->tx_ring)[curslot].txd3;
E 12
I 12
		status = TXDESC64(dp)[curslot].txd3;
E 12
E 11
	} else {
		/* formt 1 or 2 (32bit addressing) */
D 11
		status = ((struct txdesc32 *) dp->tx_ring)[curslot].txd1;
E 11
I 11
D 12
		status = NFO_TXDESC32(dp->tx_ring)[curslot].txd1;
E 12
I 12
		status = TXDESC32(dp)[curslot].txd1;
E 12
E 11
	}

D 10
	if ((status & TxD_OWN) != 0) {
E 10
I 10
	if (status & TxD_OWN) {
E 10
		return (0);
	}

	DPRINTF(4, (CE_CONT,
D 11
		"!%s: %s status:%08x", dp->name, __func__, status));
E 11
I 11
	    "!%s: %s status:%08x", dp->name, __func__, status));
E 11

	if (IS_DFMT1(lp->dmac)) {
D 5
		if (status & ~(TxD_COL_1 |TxD_LAST_1 | TxD_DEF_1 | 0x050007ff)) {
E 5
I 5
#ifdef DEBUG_LEVEL
		if (status &
D 6
			~(TxD_COL_1 |TxD_LAST_1 | TxD_DEF_1 | 0x050007ff)) {
E 6
I 6
D 11
			~(TxD_COL_1 |TxD_LAST_1 | TxD_DEF_1 | 0x010007ff)) {
E 11
I 11
		    ~(TxD_COL_1 |TxD_LAST_1 | TxD_DEF_1 | 0x010007ff)) {
E 11
E 6
E 5
			cmn_err(CE_CONT,
D 11
				"!%s: %s status_1:%08x", dp->name, __func__,
				status);
E 11
I 11
			    "!%s: %s status_1:%08x", dp->name, __func__,
			    status);
E 11
		}
I 5
#endif
E 5
D 10
		if ((status &
	(TxD_ABORT_1 | TxD_CRS_1 | TxD_OWC_1 | TxD_UDF_1 | TxD_ERR_1)) != 0) {
E 10
I 10
D 11
		if (status &
	(TxD_ABORT_1 | TxD_CRS_1 | TxD_OWC_1 | TxD_UDF_1 | TxD_ERR_1)) {
E 11
I 11
		if (status & (TxD_ABORT_1 | TxD_CRS_1 |
		    TxD_OWC_1 | TxD_UDF_1 | TxD_ERR_1)) {
E 11
E 10
			dp->stats.errxmt++;
D 10
			if ((status & TxD_UDF_1) != 0) {
E 10
I 10
			if (status & TxD_UDF_1) {
E 10
				dp->stats.underflow++;
D 11
			}
D 10
			if ((status & TxD_CRS_1) != 0) {
E 10
I 10
			else if (status & TxD_CRS_1) {
E 11
I 11
			} else if (status & TxD_CRS_1) {
E 11
E 10
				dp->stats.nocarrier++;
D 11
			}
D 10
			if ((status & TxD_OWC_1) != 0) {
E 10
I 10
			else if (status & TxD_OWC_1) {
E 11
I 11
			} else if (status & TxD_OWC_1) {
E 11
E 10
				dp->stats.xmtlatecoll++;
D 11
			}
D 10
			if ((status & TxD_ABORT_1) != 0) {
E 10
I 10
			else if (status & TxD_ABORT_1) {
E 11
I 11
			} else if (status & TxD_ABORT_1) {
E 11
E 10
				dp->stats.excoll++;
				dp->stats.collisions += 16;
D 11
			}
I 10
			else {
E 11
I 11
			} else {
E 11
				dp->stats.xmit_internal_err++;
			}
E 10
D 11
		}
D 6
		else if ((col = (status & TxD_COL_1)) != 0) {
			col >>= TxD_COL_SHIFT_1;
			dp->stats.collisions += col;
			if (col == 1) {
				dp->stats.first_coll++;
			} else {
				dp->stats.multi_coll++;
E 6
I 6
		else if (!dp->full_duplex) {
D 10
			if ((col = (status & TxD_COL_1)) != 0) {
E 10
I 10
			if (col = (status & TxD_COL_1)) {
E 11
I 11
		} else if (!dp->full_duplex) {
			col = status & TxD_COL_1;
			if (col) {
E 11
E 10
				col >>= TxD_COL_SHIFT_1;
				dp->stats.collisions += col;
				if (col == 1) {
					dp->stats.first_coll++;
				} else {
					dp->stats.multi_coll++;
				}
E 6
D 11
			}
I 6
D 10
			else if ((status & TxD_DEF_1) != 0) {
E 10
I 10
			else if (status & TxD_DEF_1) {
E 11
I 11
			} else if (status & TxD_DEF_1) {
E 11
E 10
				dp->stats.defer++;
			}
E 6
		}
D 6
		else if ((status & TxD_DEF_1) != 0) {
			dp->stats.defer++;
		}
E 6
	} else {
#ifdef NEVER
		if (status & ~(TxD_LAST_2 | TxD_COL_2 |
D 11
				TxD_DEF_2 | TxD_TOK_2 | 0x3fff)) {
E 11
I 11
		    TxD_DEF_2 | TxD_TOK_2 | 0x3fff)) {
E 11
			cmn_err(CE_CONT,
D 11
				"!%s: %s status_2:%08x", dp->name, __func__,
				status);
E 11
I 11
			    "!%s: %s status_2:%08x", dp->name, __func__,
			    status);
E 11
		}
#endif
D 10
		if ((status &
E 10
I 10
D 11
		if (status &
E 10
			(TxD_ABORT_2 | TxD_CRS_2 | TxD_OWC_2 |
D 10
			 TxD_UDF_2 | TxD_COL_2 | TxD_DEF_2)) != 0) {
E 10
I 10
			 TxD_UDF_2 | TxD_COL_2 | TxD_DEF_2)) {
E 11
I 11
		if (status & (TxD_ABORT_2 | TxD_CRS_2 | TxD_OWC_2 |
		    TxD_UDF_2 | TxD_COL_2 | TxD_DEF_2)) {
E 11
E 10

D 10
			if ((status & (TxD_ABORT_2 | TxD_CRS_2 |
					TxD_OWC_2 | TxD_UDF_2)) != 0) {
E 10
I 10
			if (status & (TxD_ABORT_2 | TxD_CRS_2 |
D 11
					TxD_OWC_2 | TxD_UDF_2)) {
E 11
I 11
			    TxD_OWC_2 | TxD_UDF_2)) {
E 11
E 10
				dp->stats.errxmt++;
D 10
				if ((status & TxD_UDF_2) != 0) {
E 10
I 10
				if (status & TxD_UDF_2) {
E 10
					dp->stats.underflow++;
D 11
				}
D 10
				if ((status & TxD_CRS_2) != 0) {
E 10
I 10
				else if (status & TxD_CRS_2) {
E 11
I 11
				} else if (status & TxD_CRS_2) {
E 11
E 10
					dp->stats.nocarrier++;
D 11
				}
D 10
				if ((status & TxD_OWC_2) != 0) {
E 10
I 10
				else if (status & TxD_OWC_2) {
E 11
I 11
				} else if (status & TxD_OWC_2) {
E 11
E 10
					dp->stats.xmtlatecoll++;
D 11
				}
D 10
				if ((status & TxD_ABORT_2) != 0) {
E 10
I 10
				else if (status & TxD_ABORT_2) {
E 11
I 11
				} else if (status & TxD_ABORT_2) {
E 11
E 10
					dp->stats.excoll++;
					dp->stats.collisions += 16;
D 11
				}
I 10
				else {
E 11
I 11
				} else {
E 11
					dp->stats.xmit_internal_err++;
				}
E 10
D 11
			}
D 6
			else if ((col = (status & TxD_COL_2)) != 0) {
				col >>= TxD_COL_SHIFT_2;
				dp->stats.collisions += col;
				if (col == 1) {
					dp->stats.first_coll++;
				} else {
					dp->stats.multi_coll++;
E 6
I 6
			else if (!dp->full_duplex) {
D 10
				if ((col = (status & TxD_COL_2)) != 0) {
E 10
I 10
				if (col = (status & TxD_COL_2)) {
E 11
I 11
			} else if (!dp->full_duplex) {
				col = status & TxD_COL_2;
				if (col) {
E 11
E 10
					col >>= TxD_COL_SHIFT_2;
					dp->stats.collisions += col;
					if (col == 1) {
						dp->stats.first_coll++;
					} else {
						dp->stats.multi_coll++;
					}
E 6
D 11
				}
I 6
D 10
				else if ((status & TxD_DEF_2) != 0) {
E 10
I 10
				else if (status & TxD_DEF_2) {
E 11
I 11
				} else if (status & TxD_DEF_2) {
E 11
E 10
					dp->stats.defer++;
				}
E 6
			}
D 6
			else if ((status & TxD_DEF_2) != 0) {
				dp->stats.defer++;
			}
E 6
		}
	}
D 6

E 6
	return (ret);
}

static void
nfo_rx_desc_write32(struct gem_dev *dp, int slot,
	    ddi_dma_cookie_t *dmacookie, int frags)
{
	struct rxdesc32	*rdp;
D 6
	struct nfo_dev	*lp = (struct nfo_dev *)dp->private;
E 6
I 6
D 11
	struct nfo_dev	*lp = (struct nfo_dev *) dp->private;
E 11
E 6

#if DEBUG_LEVEL > 2
	int		i;

	ASSERT(frags == 1);

	cmn_err(CE_CONT,
D 11
		"!%s: %s seqnum: %d, slot %d, frags: %d",
		dp->name, __func__, dp->rx_active_tail, slot, frags);
E 11
I 11
	    "!%s: %s seqnum: %d, slot %d, frags: %d",
	    dp->name, __func__, dp->rx_active_tail, slot, frags);
E 11
	for (i = 0; i < frags; i++) {
D 5
		cmn_err(CE_CONT, "  frag: %d addr: 0x%x, len: 0x%x",
E 5
I 5
		cmn_err(CE_CONT, "!  frag: %d addr: 0x%x, len: 0x%x",
E 5
D 11
			i, dmacookie[i].dmac_address, dmacookie[i].dmac_size);
E 11
I 11
		    i, dmacookie[i].dmac_address, dmacookie[i].dmac_size);
E 11
	}
#endif
	/* for the last slot of the packet */
D 11
	rdp = &((struct rxdesc32 *) dp->rx_ring)[slot];
E 11
I 11
D 12
	rdp = &((struct rxdesc32 *)(void *)dp->rx_ring)[slot];
E 12
I 12
	rdp = &RXDESC32(dp)[slot];
E 12
E 11

	rdp->rxd0 = dmacookie->dmac_address;
D 6
	rdp->rxd1 = RxD_OWN | (dmacookie->dmac_size - 1);
E 6
I 6
D 8
	rdp->rxd1 = RxD_OWN | dmacookie->dmac_size;
E 8
I 8
	rdp->rxd1 = RxD_OWN |
D 11
		(dp->mtu + sizeof(struct ether_header) + ETHERFCSL + 8 - 1);
E 11
I 11
	    (dp->mtu + sizeof (struct ether_header) + ETHERFCSL + 8 - 1);
E 11
E 8
E 6
}

static void
nfo_rx_desc_write64(struct gem_dev *dp, int slot,
D 12
	    ddi_dma_cookie_t *dmacookie, int frags)
E 12
I 12
    ddi_dma_cookie_t *dmacookie, int frags)
E 12
{
	struct rxdesc64	*rdp;
D 6
	struct nfo_dev	*lp = (struct nfo_dev *)dp->private;
E 6
I 6
D 11
	struct nfo_dev	*lp = (struct nfo_dev *) dp->private;
E 11
E 6
D 3
#if DEBUG_LEVEL > 0
E 3
I 3
#if DEBUG_LEVEL > 1
E 3
	int		i;

	ASSERT(frags == 1);

D 11
	cmn_err(CE_CONT,
		"!%s: %s seqnum: %d, slot %d, frags: %d",
		dp->name, __func__, dp->rx_active_tail, slot, frags);
E 11
I 11
	cmn_err(CE_CONT, "!%s: %s seqnum: %d, slot %d, frags: %d",
	    dp->name, __func__, dp->rx_active_tail, slot, frags);

E 11
	for (i = 0; i < frags; i++) {
D 5
		cmn_err(CE_CONT, "  frag: %d addr: 0x%x, len: 0x%x",
E 5
I 5
D 13
		cmn_err(CE_CONT, "!  frag: %d addr: 0x%x, len: 0x%x",
E 5
D 11
			i, dmacookie[i].dmac_address, dmacookie[i].dmac_size);
E 11
I 11
		    i, dmacookie[i].dmac_address, dmacookie[i].dmac_size);
E 13
I 13
		cmn_err(CE_CONT, "!  frag: %d addr: 0x%llx, len: 0x%x",
		    i, dmacookie[i].dmac_laddress, dmacookie[i].dmac_size);
E 13
E 11
	}
#endif
	/* for the last slot of the packet */
D 11
	rdp = &((struct rxdesc64 *) dp->rx_ring)[slot];
E 11
I 11
D 12
	rdp = &((struct rxdesc64 *)(void *)dp->rx_ring)[slot];
E 12
I 12
	rdp = &RXDESC64(dp)[slot];
E 12
E 11

D 11
	rdp->rxd0 = (uint32_t) (dmacookie->dmac_laddress >> 32);
	rdp->rxd1 = (uint32_t) dmacookie->dmac_laddress;
E 11
I 11
	rdp->rxd0 = (uint32_t)(dmacookie->dmac_laddress >> 32);
	rdp->rxd1 = (uint32_t)dmacookie->dmac_laddress;
E 11
	rdp->rxd2 = 0;
D 6
	rdp->rxd3 = RxD_OWN | (dmacookie->dmac_size - 1);
E 6
I 6
D 8
	rdp->rxd3 = RxD_OWN | dmacookie->dmac_size;
E 8
I 8
	rdp->rxd3 = RxD_OWN |
D 11
		(dp->mtu + sizeof(struct ether_header) + ETHERFCSL + 8 - 1);
E 11
I 11
	    (dp->mtu + sizeof (struct ether_header) + ETHERFCSL + 8 - 1);
E 11
E 8
E 6
}

I 11
#ifdef DEBUG_LEVEL
E 11
static void
nfo_packet_dump(struct gem_dev *dp, uint8_t *bp)
{
	cmn_err(CE_CONT, "!%s: "
D 11
		"%02x %02x %02x %02x %02x %02x %02x %02x "
		"%02x %02x %02x %02x %02x %02x",
		dp->name,
		bp[0], bp[1], bp[2], bp[3], bp[4], bp[5], bp[6], bp[7],
		bp[8], bp[9], bp[10], bp[11], bp[12], bp[13]);
E 11
I 11
	    "%02x %02x %02x %02x %02x %02x %02x %02x "
	    "%02x %02x %02x %02x %02x %02x",
	    dp->name,
	    bp[0], bp[1], bp[2], bp[3], bp[4], bp[5], bp[6], bp[7],
	    bp[8], bp[9], bp[10], bp[11], bp[12], bp[13]);
E 11
}
I 11
#endif
E 11

static uint64_t
nfo_rx_desc_stat(struct gem_dev *dp, int slot, int ndesc)
{
	uint32_t	status;
D 6
#ifdef CONFIG_HWVLAN
E 6
	uint64_t	vlan;
D 6
#endif
E 6
	uint64_t	ret;
D 6
	struct nfo_dev	*lp = (struct nfo_dev *)dp->private;
E 6
I 6
D 11
	struct nfo_dev	*lp = (struct nfo_dev *) dp->private;
E 11
I 11
	struct nfo_dev	*lp = dp->private;
E 11
E 6

	if (IS_DFMT3(lp->dmac)) {
		/* formt 3 (64bit addressing) */
D 11
		status = ((struct rxdesc64 *) dp->rx_ring)[slot].rxd3;
E 11
I 11
D 12
		status = ((struct rxdesc64 *)(void *)dp->rx_ring)[slot].rxd3;
E 12
I 12
		status = RXDESC64(dp)[slot].rxd3;
E 12
E 11
D 6
#ifdef CONFIG_HWVLAN
D 5
		vlan   = ((struct rxdesc64 *) dp->rx_ring)[slot].rxd1;
E 5
I 5
		vlan   = ((struct rxdesc64 *) dp->rx_ring)[slot].rxd2;
E 5
#endif
E 6
	} else {
		/* formt 1 or 2 (32bit addressing) */
D 11
		status = ((struct rxdesc32 *) dp->rx_ring)[slot].rxd1;
E 11
I 11
D 12
		status = ((struct rxdesc32 *)(void *)dp->rx_ring)[slot].rxd1;
E 12
I 12
		status = RXDESC32(dp)[slot].rxd1;
E 12
E 11
I 5
D 6
#ifdef CONFIG_HWVLAN
		vlan   = 0;
#endif
E 6
E 5
	}

D 6
#ifdef CONFIG_HWVLAN
E 6
I 6
D 10
	if ((lp->hwcap & CAP_VLAN) != 0) {
E 10
I 10
	if (lp->hwcap & CAP_VLAN) {
E 10
D 11
		vlan = ((struct rxdesc64 *) dp->rx_ring)[slot].rxd1; /* XX */
E 11
I 11
D 12
		vlan = ((struct rxdesc64 *)(void *)dp->rx_ring)[slot].rxd1;
E 12
I 12
		vlan = RXDESC64(dp)[slot].rxd1;
E 12
E 11
	} else {
		vlan = 0;
	}

E 6
D 3
	DPRINTF(0, (CE_CONT,
E 3
I 3
	DPRINTF(1, (CE_CONT,
E 3
D 11
		"!%s: time:%d %s: slot:%d, status:0x%b, vlan:0x%x",
		dp->name, ddi_get_lbolt(), __func__,
		slot, status,
		(IS_DFMT1(lp->dmac) ? RxD_1_BITS : RxD_2_BITS), vlan));
E 11
I 11
	    "!%s: time:%d %s: slot:%d, status:0x%b, vlan:0x%x",
	    dp->name, ddi_get_lbolt(), __func__,
	    slot, status,
	    (IS_DFMT1(lp->dmac) ? RxD_1_BITS : RxD_2_BITS), vlan));
E 11
D 6
#else
D 3
	DPRINTF(0, (CE_CONT,
E 3
I 3
	DPRINTF(1, (CE_CONT,
E 3
		"!%s: time:%d %s: slot:%d, status:0x%b",
		dp->name, ddi_get_lbolt(), __func__,
		slot, status,
		(IS_DFMT1(lp->dmac) ? RxD_1_BITS : RxD_2_BITS)));
#endif
E 6

	if ((status & (RxD_OWN | RxD_ERR)) == 0) {
		/*
D 11
		 * this packet was received without errors 
E 11
I 11
		 * this packet was received without errors
E 11
		 */
D 8
#if 0
E 8
I 8
#if DEBUG_LEVEL > 4
E 8
		nfo_packet_dump(dp, dp->rx_buf_head->rxb_buf);
#endif
		ret = GEM_RX_DONE;
D 6
#ifdef GEM_CONFIG_CKSUM_OFFLOAD
		/* fmt 2 and 3 */
		if ((!IS_DFMT1(lp->dmac)) && (status & RxD_CKSUMOK_2) != 0) {
E 6
I 6

		/* check result of hw checksum */
D 10
		if ((lp->hwcap & CAP_CKSUM) != 0 &&
		    (status & RxD_CKSUMOK_2) != 0) {
E 10
I 10
D 11
		if ((lp->hwcap & CAP_CKSUM) && (status & RxD_CKSUMOK_2)) {
E 11
I 11
		if ((lp->hwcap & CAP_CKSUM) && !IS_DFMT1(lp->dmac)) {
E 11
E 10
E 6
			switch ((status >> RxD_CKSUMP_SHIFT_2) & CKSUMP_2) {
			case CKSUMP_TCP_2:
				ret |= GEM_RX_CKSUM_TCP | GEM_RX_CKSUM_IPv4;
				break;

			case CKSUMP_UDP_2:
				ret |= GEM_RX_CKSUM_UDP | GEM_RX_CKSUM_IPv4;
				break;

			case CKSUMP_IP_2:
				ret |= GEM_RX_CKSUM_IPv4;
				break;

I 11
			case CKSUMP_NONE_2:
				break;
#ifdef DEBUG_LEVEL
E 11
			default:
I 11
				cmn_err(CE_CONT,
				    "%s: %s: cksum error cksump:%d",
				    dp->name, __func__,
				    (status >> RxD_CKSUMP_SHIFT_2) &
				    CKSUMP_2);
E 11
				break;
I 11
#endif
E 11
			}
		}
D 6
#endif
#ifdef CONFIG_HWVLAN
D 5
		/* XXX - this doesn't work */
E 5
I 5
		/* XXX - vtag is always 0 */
E 5
		if (IS_DFMT3(lp->dmac) && (vlan & RxD_VLAN) != 0) {
E 6
I 6

D 10
		if ((vlan & RxD_VLAN) != 0) {
E 10
I 10
		if (vlan & RxD_VLAN) {
E 10
E 6
			/* extract stripped vlan tag */
			ret |= (vlan & RxD_VTAG) << GEM_RX_VTAG_SHIFT;
		}
D 6
#endif
E 6
I 6

E 6
		return (ret | (status & RxD_LEN & GEM_RX_LEN));
	}

D 10
	if ((status & RxD_OWN) != 0) {
E 10
I 10
	if (status & RxD_OWN) {
E 10
		/*
		 * No more received packets because
		 * this buffer is owned by NIC.
		 */
		return (0);
	}

	/*
	 * Packet with error received
	 */
	if (IS_DFMT1(lp->dmac)) {
		DPRINTF(0, (CE_CONT,
D 11
			"!%s: Corrupted packet received, buffer status: %b",
			dp->name, status, RxD_1_BITS));
E 11
I 11
		    "!%s: Corrupted packet received, buffer status: %b",
		    dp->name, status, RxD_1_BITS));
E 11

		/* collect statistics information */
		dp->stats.errrcv++;
D 10
		if ((status & RxD_OVF_1) != 0) {
E 10
I 10
		if (status & RxD_OVF_1) {
E 10
			dp->stats.overflow++;
D 11
		}
D 10
		if ((status & RxD_MISSED_1) != 0) {
E 10
I 10
		else if (status & RxD_MISSED_1) {
E 11
I 11
		} else if (status & RxD_MISSED_1) {
E 11
E 10
			dp->stats.missed++;
D 11
		}
D 10
		if ((status & RxD_CRC_1) != 0) {
E 10
I 10
		else if (status & RxD_CRC_1) {
E 11
I 11
		} else if (status & RxD_CRC_1) {
E 11
E 10
			dp->stats.crc++;
D 11
		}
D 10
		if ((status & RxD_FRAME_1) != 0) {
E 10
I 10
		else if (status & RxD_FRAME_1) {
E 11
I 11
		} else if (status & RxD_FRAME_1) {
E 11
E 10
			dp->stats.frame++;
D 11
		}
I 10
		else {
E 11
I 11
		} else {
E 11
			dp->stats.rcv_internal_err++;
		}
E 10
D 11
	}
	else {
E 11
I 11
	} else {
E 11
		DPRINTF(0, (CE_CONT,
D 11
			"!%s: Corrupted packet received, buffer status: %b",
			dp->name, status, RxD_2_BITS));
E 11
I 11
		    "!%s: Corrupted packet received, buffer status: %b",
		    dp->name, status, RxD_2_BITS));
E 11

		/* collect statistics information */
		dp->stats.errrcv++;
D 10
		if ((status & RxD_OVF_2) != 0) {
E 10
I 10
		if (status & RxD_OVF_2) {
E 10
			dp->stats.overflow++;
D 11
		}
D 10
		if ((status & RxD_CRC_2) != 0) {
E 10
I 10
		else if (status & RxD_CRC_2) {
E 11
I 11
		} else if (status & RxD_CRC_2) {
E 11
E 10
			dp->stats.crc++;
D 11
		}
D 10
		if ((status & RxD_FRAME_2) != 0) {
E 10
I 10
		else if (status & RxD_FRAME_2) {
E 11
I 11
		} else if (status & RxD_FRAME_2) {
E 11
E 10
			dp->stats.frame++;
D 11
		}
I 10
		else {
E 11
I 11
		} else {
E 11
			dp->stats.rcv_internal_err++;
		}
E 10
	}

	return (GEM_RX_ERR);
}

static void
nfo_tx_desc_init32(struct gem_dev *dp, int slot)
{
D 11
	((struct txdesc32 *) dp->tx_ring)[slot].txd1 = 0;
E 11
I 11
D 12
	NFO_TXDESC32(dp->tx_ring)[slot].txd1 = 0;
E 12
I 12
	TXDESC32(dp)[slot].txd1 = 0;
E 12
E 11
}

static void
nfo_tx_desc_init64(struct gem_dev *dp, int slot)
{
D 11
	((struct txdesc64 *) dp->tx_ring)[slot].txd3 = 0;
E 11
I 11
D 12
	NFO_TXDESC64(dp->tx_ring)[slot].txd3 = 0;
E 12
I 12
	TXDESC64(dp)[slot].txd3 = 0;
E 12
E 11
}

static void
nfo_rx_desc_init32(struct gem_dev *dp, int slot)
{
D 11
	((struct rxdesc32 *) dp->rx_ring)[slot].rxd1 = 0;
E 11
I 11
D 12
	NFO_RXDESC32(dp->rx_ring)[slot].rxd1 = 0;
E 12
I 12
	RXDESC32(dp)[slot].rxd1 = 0;
E 12
E 11
}

static void
nfo_rx_desc_init64(struct gem_dev *dp, int slot)
{
D 11
	((struct rxdesc64 *) dp->rx_ring)[slot].rxd3 = 0;
E 11
I 11
D 12
	NFO_RXDESC64(dp->rx_ring)[slot].rxd3 = 0;
E 12
I 12
	RXDESC64(dp)[slot].rxd3 = 0;
E 12
E 11
}

/*
 * Device depend interrupt handler
 */
D 11
static u_int
E 11
I 11
static uint_t
E 11
nfo_interrupt(struct gem_dev *dp)
{
	uint32_t	isr;
D 11
	u_int		restart_tx = 0;
E 11
I 11
	uint_t		restart_tx = 0;
E 11
	boolean_t	need_to_reset = B_FALSE;
D 5
	struct nfo_dev	*lp = (struct gani_dev *)dp->private;
E 5
I 5
D 6
	struct nfo_dev	*lp = (struct nfo_dev *)dp->private;
E 6
I 6
D 11
	struct nfo_dev	*lp = (struct nfo_dev *) dp->private;
E 11
I 11
	struct nfo_dev	*lp = dp->private;
E 11
E 6
E 5

	isr = INL(dp, ISR);

D 10
	DPRINTF(5, (CE_CONT,"!%s: %s: time:%d isr:%b",
E 10
I 10
D 11
	DPRINTF(2, (CE_CONT,"!%s: %s: time:%d isr:%b",
E 10
		dp->name, __func__, ddi_get_lbolt(), isr, INTR_BITS));
E 11
I 11
	DPRINTF(2, (CE_CONT, "!%s: %s: time:%d isr:%b",
	    dp->name, __func__, ddi_get_lbolt(), isr, INTR_BITS));
E 11

	if ((isr & lp->imr) == 0) {
		/* not for us */
		return (DDI_INTR_UNCLAIMED);
	}

D 3
	DPRINTF(0, (CE_CONT,"!%s: %s: time:%d isr:%b imr:%b",
E 3
I 3
D 8
	DPRINTF(1, (CE_CONT,"!%s: %s: time:%d isr:%b imr:%b",
E 8
I 8
D 11
	DPRINTF(2, (CE_CONT,"!%s: %s: time:%d isr:%b imr:%b",
E 8
E 3
		dp->name, __func__, ddi_get_lbolt(), isr, INTR_BITS,
		INL(dp, IMR), INTR_BITS));
D 10

E 10
I 10
#ifndef CONFIG_OPT_IO
E 10
	/* disable interrupts */
	OUTL(dp, IMR, 0);
D 10

E 10
I 10
	FLSHL(dp, IMR);
#endif
E 11
I 11
	DPRINTF(3, (CE_CONT, "!%s: %s: time:%d isr:%b imr:%b",
	    dp->name, __func__, ddi_get_lbolt(), isr, INTR_BITS,
	    INL(dp, IMR), INTR_BITS));

E 11
E 10
	if (!dp->mac_active) {
I 10
D 11
#if 0
E 11
E 10
		/* inhibit further interrupts */
		lp->imr = 0;
D 10

E 10
I 10
D 11
#endif
#ifdef CONFIG_OPT_IO
		/* disable interrupts */
		OUTL(dp, IMR, 0);
		FLSHL(dp, IMR);
#endif
E 11
I 11

E 11
E 10
		/* ack to all interrupts */
I 11
		OUTL(dp, MIIISR, MIIISR_LSC);
		FLSHL(dp, MIIISR);
E 11
		OUTL(dp, ISR, INTR_ALL);
		FLSHL(dp, ISR);
		return (DDI_INTR_CLAIMED);
	}

I 3
	/*
D 11
	 * XXX - we must clear the reason of LSC, link status changed,
	 * interrupts first to avoid bogus LSC interrups.
E 11
I 11
	 * First of all, we must clear the reason of LSC, link status
	 * changed, interrupts to avoid bogus LSC interrupts.
E 11
	 */
D 10
	if ((isr & INTR_LSC) != 0) {
E 10
I 10
	if (isr & INTR_LSC) {
E 10
		/*
		 * Link or PHY status has changed
		 */
		DPRINTF(0, (CE_CONT, "!%s: isr:%b, miistat:%b",
D 11
			dp->name, isr, INTR_BITS,
D 6
			INL(dp, MIISTAT), MIISTAT_BITS));
E 6
I 6
			INL(dp, MIIISR), MIIISR_BITS));
E 11
I 11
		    dp->name, isr, INTR_BITS,
		    INL(dp, MIIISR), MIIISR_BITS));
E 11
E 6

D 6
		OUTL(dp, MIISTAT, MIISTAT_LSC);
E 6
I 6
		OUTL(dp, MIIISR, MIIISR_LSC);
I 10
		FLSHL(dp, MIIISR);
E 10
E 6

		if (gem_mii_link_check(dp)) {
			restart_tx |= INTR_RESTART_TX;
		}
	}

E 3
	/* clear interrupt sources explicitly */
	OUTL(dp, ISR, isr);
I 10

E 10
D 11
	isr &= lp->imr;

E 11
D 13
#ifdef GEM_CONFIG_POLLING
E 13
I 13
#ifdef CONFIG_POLLING
E 13
D 8
	if (dp->poll_interval != lp->last_poll_interval) {
E 8
I 8
D 11
	if ((!IS_DFMT1(lp->dmac)) &&
	    dp->poll_interval != lp->last_poll_interval) {
E 11
I 11
	isr &= lp->imr | INTR_RXOK;

	if (dp->poll_interval != lp->last_poll_interval) {
E 11
E 8
D 10
		if (dp->poll_interval != 0) {
E 10
I 10
D 13
		if (dp->poll_interval) {
E 13
I 13
		uint_t	rate;

		rate = dp->poll_interval/7000;
		if (rate) {
E 13
E 10
			/* polling mode */
D 11
			lp->imr &= ~(INTR_RXOK | INTR_TXDESC);
E 11
I 11
			lp->imr &= ~INTR_RXOK;
E 11
			lp->imr |= INTR_TIMER;
D 8
			OUTL(dp, TIMER, dp->poll_interval/10);

			if (lp->last_poll_interval == 0) {
				/*
				 * To schedule the next timer interrupt,
				 * we pretend as we were interrupted from
				 * polling timer
				 */
				isr |= INTR_TIMER;
			}
		}
		else {
E 8
I 8
		} else {
E 8
			/* normal mode */
D 11
			lp->imr |= (INTR_RXOK | INTR_TXDESC);
E 11
I 11
			lp->imr |= INTR_RXOK;
E 11
			lp->imr &= ~INTR_TIMER;
		}
I 8
D 11
		OUTL(dp, TIMER, dp->poll_interval/10);
E 11
I 11
D 13
		OUTL(dp, TIMER, dp->poll_interval/7000);
E 13
I 13
		OUTL(dp, TIMER, rate);
E 13
E 11
E 8

		lp->last_poll_interval = dp->poll_interval;
D 11
	}
E 11

D 10
	if ((isr & INTR_TIMER) != 0) {
E 10
I 10
D 11
	if (isr & INTR_TIMER) {
E 10
		/* force to process RX and TOK */
		isr |= (INTR_RXOK | INTR_TXDESC);
E 11
I 11
		if ((dp->misc_flag & GEM_NOINTR) == 0) {
			OUTL(dp, IMR, lp->imr);
		}
E 11
	}
I 11
#else
	isr &= lp->imr;
E 11
D 13
#endif /* GEM_CONFIG_POLLING */
E 13
I 13
#endif /* CONFIG_POLLING */
E 13
I 11

E 11
	/* barrier for interrupt state */
	FLSHL(dp, ISR);

D 3
	if ((isr & INTR_LSC) != 0) {
		/*
		 * Link or PHY status has changed
		 */
		DPRINTF(0, (CE_CONT, "!%s: isr:%b, miistat:%b",
			dp->name, isr, INTR_BITS,
			INL(dp, MIISTAT), MIISTAT_BITS));
E 3
D 11

E 11
D 3
		OUTL(dp, MIISTAT, MIISTAT_LINKCHANGE);
D 2
#if 0
		gem_mii_link_check(dp);
#endif
E 2
I 2

		if (gem_mii_link_check(dp)) {
			restart_tx |= INTR_RESTART_TX;
		}
E 2
	}

E 3
D 6
	if ((isr & (INTR_RXOK | INTR_RXERR | INTR_RDU)) != 0) {
E 6
I 6
D 10
	if ((isr & INTR_RXERR_FATAL) != 0) {
E 10
I 10
	if (isr & INTR_RXERR_FATAL) {
E 10
		cmn_err(CE_NOTE, "!%s: Rx fatal error, isr:%b",
D 11
			dp->name, isr, INTR_BITS);
E 11
I 11
		    dp->name, isr, INTR_BITS);
E 11
		need_to_reset = B_TRUE;
	}

D 10
	if ((isr & (INTR_RXOK | INTR_RXDESC | INTR_RXERR | INTR_RDU)) != 0) {
E 10
I 10
	if (isr & (INTR_RXOK | INTR_RXDESC | INTR_RXERR | INTR_RDU)) {
E 10
E 6
		(void) gem_receive(dp);
D 10
		if ((isr & INTR_RDU) != 0) {
E 10
I 10
		if (isr & INTR_RDU) {
E 10
			dp->stats.norcvbuf++;
		}
	}

D 6
	if ((isr &
		(INTR_TXOK | INTR_TXERR1 | INTR_TXERR2 | INTR_TXDESC)) != 0) {
E 6
I 6
D 10
	if ((isr & (INTR_TXOK | INTR_TXERR | INTR_TXDESC)) != 0) {
E 10
I 10
	if (isr & (INTR_TXOK | INTR_TXERR | INTR_TXDESC)) {
E 10
E 6
D 5
		/* Need to kick potentially blocked down stream */
E 5
I 5
D 11

E 11
E 5
		if (gem_tx_done(dp)) {
I 5
			/* Need to kick potentially blocked down stream */
E 5
			restart_tx |= INTR_RESTART_TX;
		}
D 8

E 8
I 8
#if DEBUG_LEVEL > 2
E 8
D 6
		if ((isr & (INTR_TXERR1 | INTR_TXERR2)) != 0) {
E 6
I 6
D 10
		if ((isr & INTR_TXERR) != 0) {
E 10
I 10
		if (isr & INTR_TXERR) {
E 10
E 6
			cmn_err(CE_WARN, "!%s: Tx error, isr:%b",
D 11
				dp->name, isr, INTR_BITS);
E 11
I 11
			    dp->name, isr, INTR_BITS);
E 11
		}
I 8
#endif
E 8
	}

	if (need_to_reset) {
D 2
		gem_restart_nic(dp, B_TRUE);
E 2
I 2
D 11
		gem_restart_nic(dp, GEM_RESTART_KEEP_BUF);
E 11
I 11
		(void) gem_restart_nic(dp, GEM_RESTART_KEEP_BUF);
E 11
E 2

		restart_tx = INTR_RESTART_TX;
	}
D 10

E 10
I 10
D 11
#ifndef CONFIG_OPT_IO
E 10
	if ((dp->misc_flag & GEM_NOINTR) == 0) {
		/* enable interrupts again */
		OUTL(dp, IMR, lp->imr);
I 10
		FLSHL(dp, IMR);
E 10
	}
D 10

E 10
I 10
#endif
E 11
I 11

E 11
E 10
	return (DDI_INTR_CLAIMED | restart_tx);
}
I 11

E 11
/*
 * HW depend MII routines
 */
static void
nfo_mii_sync(struct gem_dev *dp)
{
D 6
	struct nfo_dev	*lp = (struct nfo_dev *)dp->private;
E 6
I 6
D 11
	struct nfo_dev	*lp = (struct nfo_dev *) dp->private;
E 6

E 11
	/* nothing to do */
}

static uint16_t
nfo_mii_read(struct gem_dev *dp, uint_t reg)
{
	int		i;
D 2
	uint32_t	val = 0xffff;
E 2
I 2
D 12
	uint32_t	val = 0;
E 12
I 12
	uint32_t	val;
E 12
E 2
	uint32_t	stat;
D 6
	struct nfo_dev	*lp = (struct nfo_dev *)dp->private;
E 6
I 6
D 11
	struct nfo_dev	*lp = (struct nfo_dev *) dp->private;
E 11
E 6

#if DEBUG_LEVEL > 5
D 10
	if ((INL(dp, MIICTL) & MIICTL_BUSY) != 0) {
E 10
I 10
	if (INL(dp, MIICTL) & MIICTL_BUSY) {
E 10
		DPRINTF(0, (CE_NOTE,
D 11
			"!%s: %s: miictl is busy", dp->name, __func__));
E 11
I 11
		    "!%s: %s: miictl is busy", dp->name, __func__));
E 11
		OUTL(dp, MIICTL, MIICTL_BUSY);
		FLSHL(dp, MIICTL);
		drv_usecwait(10);
	}
#endif
	OUTL(dp, MIICTL,
D 11
		(dp->mii_phy_addr << MIICTL_ADDR_SHIFT) | (uint32_t) reg);
E 11
I 11
	    (dp->mii_phy_addr << MIICTL_ADDR_SHIFT) | (uint32_t)reg);
E 11
	FLSHL(dp, MIICTL);
	drv_usecwait(20);

D 10
	for (i = 0; (INL(dp, MIICTL) & MIICTL_BUSY) != 0; i++) {
E 10
I 10
	for (i = 0; (INL(dp, MIICTL) & MIICTL_BUSY); i++) {
E 10
		if (i > 100) {
			/* time out */
D 5
			cmn_err(CE_WARN, "%s: %s: timeout", dp->name, __func__);
E 5
I 5
			cmn_err(CE_WARN, "!%s: %s: timeout",
D 11
				dp->name, __func__);
E 11
I 11
			    dp->name, __func__);
E 11
E 5

D 3
			/* stop MII control */
E 3
I 3
			/* force to stop MII control */
E 3
			OUTL(dp, MIICTL, MIICTL_BUSY);
			FLSHL(dp, MIICTL);
			drv_usecwait(10);

D 6
			/* prepare to ack to MIISTAT */
			stat = MIISTAT_DONE | MIISTAT_ERROR;
E 6
I 6
			/* prepare to ack to MIIISR */
			stat = MIIISR_DONE | MIIISR_ERROR;
E 6
			goto x;
		}
		drv_usecwait(10);
	}

D 3
	/* XXX: Don't read MIISTAT until MIICTL_BUSY reset */
E 3
I 3
D 5
	/* XXX -  Don't read MIISTAT while MIICTL_BUSY set */
E 5
I 5
D 6
	/* XXX -  we should read MIISTAT after MIICTL_BUSY is reset */
E 5
E 3
	stat = INL(dp, MIISTAT);
D 5
	DPRINTF(5, (CE_CONT, "%s: %s: MIISTAT:%b (after reading)",
E 5
I 5
	DPRINTF(5, (CE_CONT, "!%s: %s: MIISTAT:%b (after reading)",
E 5
			dp->name, __func__, stat, MIISTAT_BITS));
E 6
I 6
	/* XXX -  we should read MIIISR after MIICTL_BUSY is reset */
	stat = INL(dp, MIIISR);
	DPRINTF(5, (CE_CONT, "!%s: %s: MIIISR:%b (after reading)",
D 11
			dp->name, __func__, stat, MIIISR_BITS));
E 11
I 11
	    dp->name, __func__, stat, MIIISR_BITS));
E 11
E 6

I 12
x:
E 12
D 6
	if ((stat & MIISTAT_ERROR) == 0) {
E 6
I 6
	if ((stat & MIIISR_ERROR) == 0) {
E 6
		val = INL(dp, MIIDATA);
D 11
	}
E 11
D 12
#if DEBUG_LEVEL > 5
E 12
D 11
	else {
E 11
I 11
	} else {
E 11
D 5
		cmn_err(CE_CONT, "%s: %s: error, phy addr:%d",
E 5
I 5
D 12
		cmn_err(CE_CONT, "!%s: %s: error, phy addr:%d",
E 5
D 11
			dp->name, __func__, dp->mii_phy_addr);
	}
E 11
I 11
		    dp->name, __func__, dp->mii_phy_addr);
E 11
#endif
E 12
I 12
D 13
		cmn_err(CE_WARN, "!%s: %s: error, phy addr:%d, MIIISR:%b",
		    dp->name, __func__, dp->mii_phy_addr, stat, MIIISR_BITS);
E 13
I 13
		if (dp->mii_state != MII_STATE_UNKNOWN) {
			/* surpress error messages under probing phys */
			cmn_err(CE_WARN,
			    "!%s: %s: error, phy addr:%d, MIIISR:%b",
			    dp->name, __func__,
			    dp->mii_phy_addr, stat, MIIISR_BITS);
		}
E 13
		val = 0;
E 12
I 11
	}
E 11
D 12
x:
E 12
I 12

E 12
	/* ack to MII status */
D 6
	OUTL(dp, MIISTAT, stat);
E 6
I 6
	/* XXX - this enables the mii interface again. */
	OUTL(dp, MIIISR, stat);
E 6

D 11
	return (val);
E 11
I 11
	return ((uint16_t)val);
E 11
}

static void
nfo_mii_write(struct gem_dev *dp, uint_t index, uint16_t val)
{
	int		i;
D 11
	uint32_t	stat;
D 6
	struct nfo_dev	*lp = (struct nfo_dev *)dp->private;
E 6
I 6
	struct nfo_dev	*lp = (struct nfo_dev *) dp->private;
E 11
E 6

#if DEBUG_LEVEL > 5
D 10
	if ((INL(dp, MIICTL) & MIICTL_BUSY) != 0) {
E 10
I 10
	if (INL(dp, MIICTL) & MIICTL_BUSY) {
E 10
		DPRINTF(0, (CE_WARN,
D 11
			"!%s: %s: miictl is busy", dp->name, __func__));
E 11
I 11
		    "!%s: %s: miictl is busy", dp->name, __func__));
E 11
		OUTL(dp, MIICTL, MIICTL_BUSY);
		FLSHL(dp, MIICTL);
		drv_usecwait(10);
	}
#endif
I 13
#if 0
	/* XXX - doesn't work */
	if (index == MII_CONTROL) {
		val |= MII_CONTROL_RESET;
	}
#endif
E 13
D 3
#if 0
	if (index == MII_CONTROL && (val & MII_CONTROL_RESET) != 0) {
		val |= MII_CONTROL_PWRDN;
	}
#endif
E 3
	OUTL(dp, MIIDATA, val);

	OUTL(dp, MIICTL,
D 11
		MIICTL_WRITE |
		(((uint32_t) dp->mii_phy_addr) << MIICTL_ADDR_SHIFT) |
		(uint32_t) index);
E 11
I 11
	    MIICTL_WRITE |
	    (((uint32_t)dp->mii_phy_addr) << MIICTL_ADDR_SHIFT) |
	    (uint32_t)index);
E 11
	FLSHL(dp, MIICTL);
	drv_usecwait(20);

D 10
	for (i = 0; (INL(dp, MIICTL) & MIICTL_BUSY) != 0; i++) {
E 10
I 10
	for (i = 0; (INL(dp, MIICTL) & MIICTL_BUSY); i++) {
E 10
		if (i > 100) {
D 5
			cmn_err(CE_WARN, "%s: %s: timeout", dp->name, __func__);
E 5
I 5
			cmn_err(CE_WARN, "!%s: %s: timeout",
D 11
				dp->name, __func__);
E 11
I 11
			    dp->name, __func__);
E 11
E 5

D 3
			/* stop MII control */
E 3
I 3
			/* force to stop MII control */
E 3
			OUTL(dp, MIICTL, MIICTL_BUSY);
			FLSHL(dp, MIICTL);
			drv_usecwait(10);

			break;
		}
		drv_usecwait(10);
	}
I 6

E 6
D 3
#ifdef notdef
E 3
I 3
#ifdef NEVER
D 6
	/* XXX - no need to ack MIISTAT on write */
E 6
E 3
	/* ack to MII status */
D 6
	OUTL(dp, MIISTAT, (stat = INL(dp, MIISTAT)));
E 6
I 6
	/* XXX - no need to ack MIIISR for writing */
D 11
	OUTL(dp, MIIISR, (stat = INL(dp, MIIISR)));
E 11
I 11
	OUTL(dp, MIIISR, INL(dp, MIIISR));
E 11
E 6
D 3

	DPRINTF(0, (CE_CONT, "%s: %s: MIISTAT:%b (after writing)",
			dp->name, __func__, INL(dp, MIISTAT), MIISTAT_BITS));
E 3
#endif
I 3
D 5
	DPRINTF(5, (CE_CONT, "%s: %s: MIISTAT:%b (after writing)",
E 5
I 5
D 6
	DPRINTF(5, (CE_CONT, "!%s: %s: MIISTAT:%b (after writing)",
E 5
			dp->name, __func__, INL(dp, MIISTAT), MIISTAT_BITS));
E 6
I 6
	DPRINTF(5, (CE_CONT, "!%s: %s: MIIISR:%b (after writing)",
D 11
			dp->name, __func__, INL(dp, MIIISR), MIIISR_BITS));
E 11
I 11
	    dp->name, __func__, INL(dp, MIIISR), MIIISR_BITS));
E 11
E 6
E 3
}

D 6
#define	PHY_ID_CICADA	0x000fc400

E 6
static int
nfo_mii_config(struct gem_dev *dp)
{
I 6
	int		i;
E 6
	int		ret;
	uint32_t	val;
D 6
	
E 6
I 6
D 11
	struct nfo_dev	*lp = (struct nfo_dev *) dp->private;
E 11
I 11
	struct nfo_dev	*lp = dp->private;
E 11

	if (OUI_CMP(dp, OUI_MARVELL) == 0) {
		/* restore LED stats */
		nfo_mii_write(dp, 22, 3);
		drv_usecwait(5);
		for (i = 0; i < 3; i++) {
			nfo_mii_write(dp, 16 + i, lp->mii_led_stats[i]);
		}
		nfo_mii_write(dp, 22, 0);
		drv_usecwait(5);
	}

E 6
	if ((ret = gem_mii_config_default(dp)) != GEM_SUCCESS) {
		return (ret);
	}

D 6
	if ((dp->mii_phy_id & 0xfffffc00) == PHY_ID_CICADA) {
D 5
		DPRINTF(0, (CE_CONT, "%s: %s: CICADA phy found",
E 5
I 5
		DPRINTF(0, (CE_CONT, "!%s: %s: CICADA phy found",
E 5
			dp->name, __func__));
E 6
I 6
	if (OUI_CMP(dp, OUI_CICADA) == 0) {
D 11
		cmn_err(CE_CONT, "!%s: %s: CICADA phy (model:%x ver:%x) found",
			dp->name, __func__,
			(dp->mii_phy_id >> 4) & 0x3f, dp->mii_phy_id & 0xf);
E 11
I 11
		cmn_err(CE_CONT,
		    "!%s: %s: CICADA phy (model:%x ver:%x) found",
		    dp->name, __func__,
		    (dp->mii_phy_id >> 4) & 0x3f, dp->mii_phy_id & 0xf);
E 11

E 6
		val = INL(dp, PHYIF);
D 10
		if ((val & PHYIF_RGMII) != 0) {
E 10
I 10
		if (val & PHYIF_RGMII) {
E 10
			DPRINTF(0, (CE_CONT,
D 11
				"!%s: %s: RGMII phy found, PHYIF:%04x",
				dp->name, __func__, val));
E 11
I 11
			    "!%s: %s: RGMII phy found, PHYIF:%04x",
			    dp->name, __func__, val));
E 11
			nfo_mii_write(dp, 0x17,
D 11
				(nfo_mii_read(dp, 0x17) & ~(0xfe00)) | 0x1200);
E 11
I 11
			    (nfo_mii_read(dp, 0x17) & ~(0xfe00)) | 0x1200);
E 11

			nfo_mii_write(dp, 0x1c,
D 11
				nfo_mii_read(dp, 0x1c) | 0x0004);
E 11
I 11
			    nfo_mii_read(dp, 0x1c) | 0x0004);
E 11
		}

D 11
		nfo_mii_write(dp, 0x16,
			nfo_mii_read(dp, 0x16) | 0x2000);
E 11
I 11
		nfo_mii_write(dp, 0x16, nfo_mii_read(dp, 0x16) | 0x2000);
E 11
	}

I 6
	if (OUI_CMP(dp, OUI_VITESSE) == 0) {
D 10
		cmn_err(CE_CONT, "!%s: %s: VITESSE phy (model:%x ver:%x) found",
E 10
I 10
		cmn_err(CE_CONT,
D 11
			"!%s: %s: VITESSE phy (model:%x ver:%x) found",
E 10
			dp->name, __func__,
			(dp->mii_phy_id >> 4) & 0x3f, dp->mii_phy_id & 0xf);
E 11
I 11
		    "!%s: %s: VITESSE phy (model:%x ver:%x) found",
		    dp->name, __func__,
		    (dp->mii_phy_id >> 4) & 0x3f, dp->mii_phy_id & 0xf);
E 11

		nfo_mii_write(dp, 0x1f, 0x52b5);
		nfo_mii_write(dp, 0x10, 0xaf8a);
		nfo_mii_write(dp, 0x12, nfo_mii_read(dp, 0x12));
		nfo_mii_write(dp, 0x11,
D 11
			(nfo_mii_read(dp, 0x11) & ~0xc) | 0x8);
E 11
I 11
		    (nfo_mii_read(dp, 0x11) & ~0xc) | 0x8);
E 11
		nfo_mii_write(dp, 0x10, 0x8f8a);
		nfo_mii_write(dp, 0x10, 0xaf86);
D 11
		nfo_mii_write(dp, 0x12, 
			(nfo_mii_read(dp, 0x12) & ~0xc) | 0x8);
E 11
I 11
		nfo_mii_write(dp, 0x12,
		    (nfo_mii_read(dp, 0x12) & ~0xc) | 0x8);
E 11
		nfo_mii_write(dp, 0x11, nfo_mii_read(dp, 0x11));
		nfo_mii_write(dp, 0x10, 0x8f86);
		nfo_mii_write(dp, 0x10, 0xaf82);
		nfo_mii_write(dp, 0x12, nfo_mii_read(dp, 0x12));
		nfo_mii_write(dp, 0x11,
D 11
			(nfo_mii_read(dp, 0x11) & ~0x0180) | 0x0100);
E 11
I 11
		    (nfo_mii_read(dp, 0x11) & ~0x0180) | 0x0100);
E 11
		nfo_mii_write(dp, 0x10, 0x8f82);
		nfo_mii_write(dp, 0x1f, 0x0);
	}

I 12
	if (OUI_CMP(dp, OUI_REALTEK) == 0) {
		cmn_err(CE_CONT, "!%s: %s:"
		    " REALTEK phy (model:%x ver:%x) found",
		    dp->name, __func__,
		    (dp->mii_phy_id >> 4) & 0x3f, dp->mii_phy_id & 0xf);

		nfo_mii_write(dp, 0x1f, 0x0000);
		nfo_mii_write(dp, 0x19, 0x8e00);
		nfo_mii_write(dp, 0x1f, 0x0001);
		nfo_mii_write(dp, 0x13, 0xad17);
		nfo_mii_write(dp, 0x1f, 0x0000);
	}

E 12
E 6
	return (ret);
}

I 6
static boolean_t
nfo_mgmt_acq_sema(struct gem_dev *dp)
{
	int		i;
	uint32_t	val;

	i = 0;
	while ((INL(dp, TxCTRL) & TxCTRL_MSEMA) != TxCTRL_MSEMA_FREE) {
		if (i++ > 10) {
			cmn_err(CE_WARN,
D 11
		"!%s: %s: failed to acquire msema: msema didn't become free",
				dp->name, __func__);
E 11
I 11
			    "!%s: %s: failed to acquire msema:"
			    " msema didn't become free",
			    dp->name, __func__);
E 11
			return (B_FALSE);
D 11
                }
E 11
I 11
		}
E 11
		delay(drv_usectohz(500*1000));
	}

	for (i = 0; i < 2; i++) {
		/* try to acquire semaphore */
		OUTL(dp, TxCTRL, INL(dp, TxCTRL) | TxCTRL_HSEMA_ACQ);

		/* verify that semaphore was acquired */
		val = INL(dp, TxCTRL);
		if ((val & TxCTRL_HSEMA) == TxCTRL_HSEMA_ACQ &&
		    (val & TxCTRL_MSEMA) == TxCTRL_MSEMA_FREE) {
			/* we got !! */
			return (B_TRUE);
		}
		drv_usecwait(50);
	}

	cmn_err(CE_NOTE, "!%s: %s: failed to acuire msema: time over",
D 11
		dp->name, __func__);
E 11
I 11
	    dp->name, __func__);
E 11

	return (B_FALSE);
}

E 6
static int
D 10
nfo_mii_init(struct gem_dev *dp)
E 10
I 10
nfo_mii_probe(struct gem_dev *dp)
E 10
{
I 6
	int		i;
E 6
	int		ret;
I 6
	uint32_t	miiauto;
E 6
D 11
	uint32_t	val;
I 6
	struct nfo_dev	*lp = (struct nfo_dev *) dp->private;
E 11
I 11
	struct nfo_dev	*lp = dp->private;
E 11
E 6

I 6
	/* clear phy state and temporarily halt phy interrupts */
	OUTL(dp, MIIIMR, 0);
I 10
	FLSHL(dp, MIIIMR);
E 10
	miiauto = INL(dp, MIIAUTO);
D 10
	if ((miiauto & MIIAUTO_EN) != 0) {
E 10
I 10
	if (miiauto & MIIAUTO_EN) {
E 10
		OUTL(dp, MIIAUTO, miiauto & ~MIIAUTO_EN);
	}
	OUTL(dp, MIIISR, MIIISR_ALL);
I 10
	FLSHL(dp, MIIISR);
E 10

D 10
	if ((lp->hwcap & CAP_MGMT) != 0) {
E 10
I 10
D 12
	if (lp->hwcap & CAP_MGMT) {
E 10
		/* XXX - not implemented yet */
		int	msync;

		OUTL(dp, PTNCRC, 1);
D 8
		drv_usecwait(500*1000);
E 8
I 8
		delay(drv_usectohz(500*1000));
E 12
I 12
	if ((lp->hwcap & CAP_MGMT) &&
	    (INL(dp, TxCTRL) & TxCTRL_SYNC_PHYINIT)) {
E 12
E 8
		lp->mac_in_use = (INL(dp, TxCTRL) & TxCTRL_MGMT_ST) != 0;
D 12
		if (!lp->mac_in_use) {
			goto x;
		}
		msync = INL(dp, TxCTRL) & TxCTRL_MSYNC;
		if (msync == TxCTRL_MSYNC_PHYINIT) {
			/* avoid to initialize phy by myself */
			lp->phy_initialized = B_TRUE;
			goto x;
		}
		if (msync != TxCTRL_MSYNC_NOTREADY) {
			/* we need to init the phy */
			goto x;
		}
E 12

I 12
		DPRINTF(0, (CE_CONT, "!%s: %s: management is active: %d",
		    dp->name, __func__, lp->mac_in_use));

E 12
		if (nfo_mgmt_acq_sema(dp)) {
D 12
			/* as we got the phy, we need to init the phy */
			goto x;
E 12
I 12
			lp->phy_initialized =
			    (INL(dp, TxCTRL) & TxCTRL_SYNC)
			    == TxCTRL_SYNC_PHYINIT;
E 12
		}
D 12

		i = 0;
		do {
			drv_usecwait(1000);
			msync = INL(dp, TxCTRL) & TxCTRL_MSYNC;

			if (msync == TxCTRL_MSYNC_PHYINIT) {
				lp->phy_initialized = B_TRUE;
				break;
			}
			if (i++ > 5000) {
				break;
			}
		} while (msync == TxCTRL_MSYNC_NOTREADY);
E 12
	}
D 12
x:
E 12
I 12

E 12
E 6
D 10
	ret = gem_mii_init_default(dp);
E 10
I 10
	ret = gem_mii_probe_default(dp);
E 10
I 6

E 6
	if (ret != GEM_SUCCESS) {
I 6
		/* restore MIIAUTO */
D 10
		if ((miiauto & MIIAUTO_EN) != 0) {
E 10
I 10
		if (miiauto & MIIAUTO_EN) {
E 10
			OUTL(dp, MIIAUTO, miiauto);
		}
E 6
D 10
		return (ret);
E 10
	}
D 3
#ifdef notdef
E 3
I 3
D 6
#ifdef NEVER
E 3
	val = nfo_mii_read(dp, MII_CONTROL);
E 6

I 10
	/* 1000Mbps half duplex isn't supported */
	dp->mii_xstatus &= ~(MII_XSTATUS_1000BASEX | MII_XSTATUS_1000BASET);

	return (ret);
}

static int
nfo_mii_init(struct gem_dev *dp)
{
	int		i;
	int		ret = GEM_SUCCESS;
D 11
	struct nfo_dev	*lp = (struct nfo_dev *) dp->private;
E 11
I 11
	struct nfo_dev	*lp = dp->private;
E 11

E 10
D 3
	DPRINTF(0, (CE_CONT, "!%s: %s mii_control:%b",
E 3
I 3
D 6
	DPRINTF(1, (CE_CONT, "!%s: %s mii_control:%b",
E 3
		dp->name, __func__, val, MII_CONTROL_BITS));
E 6
I 6
	/* setup mii interface */
	OUTL(dp, MIIISR, MIIISR_ALL);
	OUTL(dp, MIIAUTO,
D 11
		(dp->mii_phy_addr << MIIAUTO_PHYADDR_SHIFT) |
D 8
		MIIAUTO_PHYVALID | MIIAUTO_EN);
E 8
I 8
		MIIAUTO_PHYVALID);
E 11
I 11
	    (dp->mii_phy_addr << MIIAUTO_PHYADDR_SHIFT) | MIIAUTO_PHYVALID);
E 11
	OUTL(dp, MIIAUTO, INL(dp, MIIAUTO) | MIIAUTO_EN);
E 8
E 6

D 6
	/* work around for CICIDA */
	if ((dp->mii_phy_id & 0xfffffc00) == PHY_ID_CICADA) {
		nfo_mii_write(dp, MII_CONTROL,
			MII_CONTROL_RESET | MII_CONTROL_ANE);
		delay(drv_usectohz(100000));
E 6
I 6
	/* tune mii interface speed */
	OUTL(dp, MIICFG, 0x105);

	if (!lp->phy_initialized) {
		if (IS_PHY(dp, OUI_MARVELL, 0x220)) {
			/* XXX -- workaround for 88E3016 */
D 11
			cmn_err(CE_CONT,
D 10
			"!%s: %s: MARVELL 88E3016 phy (model:%x ver:%x) found",
E 10
I 10
		"!%s: %s: MARVELL 88E3016 phy (model:%x ver:%x) found",
E 10
				dp->name, __func__,
				(dp->mii_phy_id >> 4) & 0x3f,
				dp->mii_phy_id & 0xf);
E 11
I 11
			cmn_err(CE_CONT, "!%s: %s:"
			    " MARVELL 88E3016 phy (model:%x ver:%x) found",
			    dp->name, __func__,
			    (dp->mii_phy_id >> 4) & 0x3f,
			    dp->mii_phy_id & 0xf);
E 11
			nfo_mii_write(dp, 0x1c,
D 11
				nfo_mii_read(dp, 0x1c) & ~0x0300);
E 11
I 11
			    nfo_mii_read(dp, 0x1c) & ~0x0300);
E 11
		}
E 6
D 11
	}
D 6
#endif
E 6
I 6
	else {
E 11
I 11
	} else {
E 11
		/* don't reset phy setting by management unit */
		dp->gc.gc_mii_dont_reset = B_TRUE;
	}

	if (lp->mac_in_use) {
		/* XXX - indicate driverloaded flag */
		OUTL(dp, TxCTRL, INL(dp, TxCTRL) | TxCTRL_HSEMA_LOADED);
	}

D 13
	/* save LED stats */
E 13
I 13
	/* save LED status */
E 13
	nfo_mii_write(dp, 22, 3);
	drv_usecwait(5);

	if (OUI_CMP(dp, OUI_MARVELL) == 0) {
		for (i = 0; i < 3; i++) {
			lp->mii_led_stats[i] = nfo_mii_read(dp, 16 + i);
		}

		DPRINTF(0, (CE_CONT, "!%s: %s: mii_led_stats:%x, %x, %x",
D 11
				dp->name, __func__, 
				lp->mii_led_stats[0],
				lp->mii_led_stats[1],
				lp->mii_led_stats[2]));
E 11
I 11
		    dp->name, __func__,
		    lp->mii_led_stats[0],
		    lp->mii_led_stats[1],
		    lp->mii_led_stats[2]));
E 11
	}
	nfo_mii_write(dp, 22, 0);
	drv_usecwait(5);

E 6
	return (ret);
}

D 10
static int
E 10
I 10
static void
E 10
I 6
nfo_power_up(struct gem_dev *dp)
{
	uint32_t	val;
D 11
	struct nfo_dev	*lp = (struct nfo_dev *) dp->private;
E 11
I 11
	struct nfo_dev	*lp = dp->private;
E 11

	/* disalble wol */
	OUTL(dp, WAKECTRL, 0);

D 8
#ifdef CONFIG_PM
E 8
D 10
	if ((lp->hwcap & CAP_PM) != 0) {
E 10
I 10
	if (lp->hwcap & CAP_PM) {
E 10
		val = INL(dp, PWRSTAT2) & ~0x0f11;
D 10
		if ((lp->chip->devid == 0x0268 || lp->chip->devid == 0x0269) &&
		     lp->revid >= 0xa3) {
E 10
I 10
D 11
		if ((lp->chip->devid == 0x0268 || lp->chip->devid == 0x0269)
		   && lp->revid >= 0xa3) {
E 11
I 11
		if ((lp->chip->devid == 0x0268 ||
		    lp->chip->devid == 0x0269) && lp->revid >= 0xa3) {
E 11
E 10
			/* workaround for MCP51 */
			val |= 1;
		}
		OUTL(dp, PWRSTAT2, val);
	}
D 8
#endif /* CONFIG_PM */
E 8
}

static int
E 6
nfo_attach_chip(struct gem_dev *dp)
{
D 6
	struct nfo_dev	*lp = (struct nfo_dev *)dp->private;
E 6
I 6
	uint32_t	val;
	uint32_t	*mac_addr;
D 11
	struct nfo_dev	*lp = (struct nfo_dev *) dp->private;
E 11
I 11
	struct nfo_dev	*lp = dp->private;
E 11
E 6

D 11
	DPRINTF(2, (CE_CONT, "!%s: %s: called at time:%d",
		dp->name, __func__, ddi_get_lbolt()));
E 11
I 11
	DPRINTF(0, (CE_CONT, "!%s: %s: called at time:%d",
	    dp->name, __func__, ddi_get_lbolt()));
E 11

I 6
	nfo_power_up(dp);

E 6
D 11
        /* fix rx buffer length, it needs additional 48 bytes. */
        dp->rx_buf_len += 48;
E 11
I 11
D 13
	/* fix rx buffer length, it needs additional 48 bytes. */
	dp->rx_buf_len += 48;
E 13
I 13
	/* fix rx buffer length, it needs additional 48 + 64 bytes. */
	dp->rx_buf_len += 48 + 64;
E 13
E 11

D 10
	/*
	 * Set speed and duplex settings
	 */
	dp->anadv_1000hdx = 0;	/* 1000HD isn't supported by the mac */
	if (dp->mii_fixedmode &&
	   (dp->speed == GEM_SPD_1000) && !dp->full_duplex) {
		cmn_err(CE_WARN,
	"!%s: fixed 1000Mbps half duplex isn't supported, using full duplex.",
			dp->name);
		dp->anadv_1000fdx = B_TRUE;
		dp->anadv_1000hdx = B_FALSE;
		dp->anadv_100fdx  = B_FALSE;
		dp->anadv_100hdx  = B_FALSE;
		dp->anadv_10fdx   = B_FALSE;
		dp->anadv_10hdx   = B_FALSE;
		dp->mii_fixedmode = B_FALSE;
	}

E 10
	/* Save factory mac address */
	lp->factory_mac_addr[0] = INL(dp, MACADDR + 0);
	lp->factory_mac_addr[1] = INL(dp, MACADDR + 4);

	/*
D 5
	 * BUG - As the factory mac address is set in incorrect format,
E 5
I 5
	 * XXX - As the factory mac address is set in incorrect format,
E 5
	 * aka in reversed order after power-on, we must re-write it.
D 5
	 * But it aren't copies anywhre else, the original address gone
	 * when we fix it.
E 5
I 5
	 * But as there are no copies of the original mac address anywhere
	 * else, it is gone after we fix it.
E 5
	 */
D 6
	dp->dev_addr.ether_addr_octet[0] = lp->factory_mac_addr[1] >> (1*8);
	dp->dev_addr.ether_addr_octet[1] = lp->factory_mac_addr[1] >> (0*8);
	dp->dev_addr.ether_addr_octet[2] = lp->factory_mac_addr[0] >> (3*8);
	dp->dev_addr.ether_addr_octet[3] = lp->factory_mac_addr[0] >> (2*8);
	dp->dev_addr.ether_addr_octet[4] = lp->factory_mac_addr[0] >> (1*8);
	dp->dev_addr.ether_addr_octet[5] = lp->factory_mac_addr[0] >> (0*8);
E 6
I 6
	mac_addr = lp->factory_mac_addr;
	val = INL(dp, TxPOLL);
	DPRINTF(0, (CE_CONT, "!%s: %s: TxPOLL:%x", dp->name, __func__, val));
E 6

D 6
#ifdef GEM_CONFIG_CKSUM_OFFLOAD
D 5
	if (IS_DFMT3(lp->dmac)) {
E 5
I 5
	if (IS_DFMT2(lp->dmac) || IS_DFMT3(lp->dmac)) {
E 6
I 6
D 8
	if ((val & TxPOLL_MACADDR_REV) == 0) {
E 8
I 8
D 13
	if ((val & TxPOLL_MACADDR_REV) == 0 &&
	    (lp->chip->hwcap & CAP_CORRECT_MAC) == 0) {
E 13
I 13
	if ((lp->chip->hwcap & CAP_CORRECT_MAC) == 0) {
E 13
E 8
		/* original format */
		dp->dev_addr.ether_addr_octet[0] = mac_addr[1] >> (1*8);
		dp->dev_addr.ether_addr_octet[1] = mac_addr[1] >> (0*8);
		dp->dev_addr.ether_addr_octet[2] = mac_addr[0] >> (3*8);
		dp->dev_addr.ether_addr_octet[3] = mac_addr[0] >> (2*8);
		dp->dev_addr.ether_addr_octet[4] = mac_addr[0] >> (1*8);
		dp->dev_addr.ether_addr_octet[5] = mac_addr[0] >> (0*8);
D 11
		/* mark that we will change it in correct format */
		OUTL(dp, TxPOLL, val | TxPOLL_MACADDR_REV);
E 11
	} else {
		/* mac address format has been fixed */
		dp->dev_addr.ether_addr_octet[0] = mac_addr[0] >> (0*8);
		dp->dev_addr.ether_addr_octet[1] = mac_addr[0] >> (1*8);
		dp->dev_addr.ether_addr_octet[2] = mac_addr[0] >> (2*8);
		dp->dev_addr.ether_addr_octet[3] = mac_addr[0] >> (3*8);
		dp->dev_addr.ether_addr_octet[4] = mac_addr[1] >> (0*8);
		dp->dev_addr.ether_addr_octet[5] = mac_addr[1] >> (1*8);
	}
D 11

D 10
	if ((lp->dmac & CAP_CKSUM) != 0) {
E 10
I 10
	if (lp->dmac & CAP_CKSUM) {
E 10
E 6
E 5
		/* for fmt 3 */
E 11
I 11
D 12
#if 1
E 12
I 12

E 12
	dp->misc_flag |= GEM_POLL_RXONLY;
D 12
#endif
E 12
I 12
D 13

E 13
I 13
#ifdef CONFIG_CKSUM_OFFLOAD
E 13
E 12
	if ((lp->hwcap & CAP_CKSUM) && !IS_DFMT1(lp->dmac)) {
E 11
D 6
		dp->misc_flag |= (GEM_CKSUM_FULL_IPv4 | GEM_CKSUM_HEADER_IPv4);
E 6
I 6
		dp->misc_flag |= GEM_CKSUM_FULL_IPv4 | GEM_CKSUM_HEADER_IPv4;
I 12
#ifdef CONFIG_LSO
		dp->misc_flag |= GEM_LSO;
D 13
#endif
E 13
I 13
#endif /* CONFIG_LSO */
E 13
E 12
E 6
	}
D 6
#endif
#ifdef GEM_CONFIG_VLAN
# ifdef CONFIG_HWVLAN
	dp->misc_flag |= GEM_VLAN_HARD;
# else
	dp->misc_flag |= GEM_VLAN_SOFT;
# endif
#endif
E 6
D 11

E 11
I 11
D 13
#ifdef CONFIG_VLAN_HARD
E 11
I 6
	dp->misc_flag |=
D 10
		((lp->hwcap & CAP_VLAN) != 0) ? GEM_VLAN_HARD : GEM_VLAN_SOFT;
E 10
I 10
D 11
		(lp->hwcap & CAP_VLAN) ? GEM_VLAN_HARD : GEM_VLAN_SOFT;
E 11
I 11
	    (lp->hwcap & CAP_VLAN) ? GEM_VLAN_HARD : GEM_VLAN_SOFT;
E 13
I 13
#endif /* CONFIG_CKSUM_OFFLOAD */
#ifdef CONFIG_VLAN_HW
	if (lp->hwcap & CAP_VLAN) {
		dp->misc_flag |= GEM_VLAN_HARD;
	} else {
		dp->misc_flag |= GEM_VLAN_SOFT;
	}
E 13
#else
	dp->misc_flag |= GEM_VLAN_SOFT;
D 13
#endif
E 13
I 13
#endif /* CONFIG_VLAN_HW */
E 13
E 11
E 10

E 6
#if DEBUG_LEVEL > 4
{
	uint8_t		*mac;

	mac = dp->dev_addr.ether_addr_octet;
D 5
	cmn_err(CE_CONT, "%s: mac:%02x:%02x:%02x:%02x:%02x:%02x",
E 5
I 5
	cmn_err(CE_CONT, "!%s: mac:%02x:%02x:%02x:%02x:%02x:%02x",
E 5
D 11
		dp->name, mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
E 11
I 11
	    dp->name, mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
E 11
}
D 11
#endif		
E 11
I 11
#endif
E 11
I 6
	if (IS_PHY(dp, OUI_MARVELL, 0x220)) {
		/* workaround for Marvell 88E3016 100/10 phy */
		dp->gc.gc_mii_linkdown_action = MII_ACTION_RESET;
	}

E 6
	return (GEM_SUCCESS);
}

/* ======================================================== */
/*
 * OS depend (device driver) routine
 */
/* ======================================================== */
static int
nfoattach(dev_info_t *dip, ddi_attach_cmd_t cmd)
{
	int			i;
D 11
	ddi_iblock_cookie_t	c;
E 11
	ddi_acc_handle_t	conf_handle;
	int			ret;
	uint16_t		vid;
	uint16_t		did;
	uint8_t			revid;
	int			unit;
	struct chip_info	*p;
D 11
	int			len;
	struct pci_phys_spec	*regs;
E 11
	const char		*drv_name;
	struct gem_dev		*dp;
	struct nfo_dev	*lp;
	caddr_t			base;
	ddi_acc_handle_t	regs_ha;
	struct gem_conf		*gcp;
D 11
	uint32_t		val;
	uint32_t		cap_ptr;
	uint32_t		cap;
	uint32_t		ps;
E 11
	uint32_t		ilr;
	boolean_t		is64bit;
I 13
	boolean_t		tx16;
	uint_t			max_ring_size;
	uint_t			tx_ring_size;
	uint_t			pcie_cap;
E 13

D 11
	unit =  ddi_get_instance(dip);
E 11
I 11
	unit = ddi_get_instance(dip);
E 11
	drv_name = ddi_driver_name(dip);

	DPRINTF(2, (CE_CONT, "!%s%d: nfoattach: called at time:%d",
D 11
		drv_name, unit, ddi_get_lbolt()));
E 11
I 11
	    drv_name, unit, ddi_get_lbolt()));
E 11

	/*
	 * Check if chip is supported.
	 */
	if (pci_config_setup(dip, &conf_handle) != DDI_SUCCESS) {
D 11
		cmn_err(CE_WARN, "!%s%d: ddi_regs_map_setup failed",
			drv_name, unit);
E 11
I 11
		cmn_err(CE_WARN, "!%s%d: pci_config_setup failed",
		    drv_name, unit);
E 11
		return (DDI_FAILURE);
	}

D 11
	vid  = pci_config_get16(conf_handle, PCI_CONF_VENID);
	did  = pci_config_get16(conf_handle, PCI_CONF_DEVID);
	revid= pci_config_get8(conf_handle, PCI_CONF_REVID);
E 11
I 11
	vid = pci_config_get16(conf_handle, PCI_CONF_VENID);
	did = pci_config_get16(conf_handle, PCI_CONF_DEVID);
	revid = pci_config_get8(conf_handle, PCI_CONF_REVID);
E 11
D 8

E 8
I 8
#ifdef TEST_NF3
	did = 0xd6;
#endif
	if (did == 0) {
		/* workaround for MCP compatible chipset */
		did = 0x1c3;
	}
E 8
D 11
	for (i = 0, p = nfo_chiptbl; i < CHIPTABLESIZE; i++, p++) {
E 11
I 11
	for (i = 0, p = nfo_chiptbl; i < ARRAY_SIZE(nfo_chiptbl); i++, p++) {
E 11
		if (p->venid == vid && p->devid == did) {
			/* found */
			cmn_err(CE_CONT,
D 11
		"!%s%d: %s (vid: 0x%04x, did: 0x%04x, revid: 0x%02x)",
			drv_name, unit, p->name, vid, did, revid);
E 11
I 11
			    "!%s%d: %s (vid: 0x%04x, did: 0x%04x,"
			    " revid: 0x%02x)",
			    drv_name, unit, p->name, vid, did, revid);
E 11
			goto chip_found;
		}
	}
	/* Not found */
D 11
	cmn_err(CE_WARN, "!%s: %s: unsupported  PCI venid/devid (0x%x, 0x%x)",
		drv_name, __func__, vid, did);
E 11
I 11
	cmn_err(CE_WARN,
	    "!%s: %s: unsupported  PCI venid/devid (0x%x, 0x%x)",
	    drv_name, __func__, vid, did);
E 11
	pci_config_teardown(&conf_handle);
	return (DDI_FAILURE);

chip_found:
	/* ensure we can access the registers through IO and MEM space. */
	ret = pci_config_get16(conf_handle, PCI_CONF_COMM);
	ret |= PCI_COMM_IO | PCI_COMM_ME | PCI_COMM_MAE;
	pci_config_put16(conf_handle, PCI_CONF_COMM, ret);

	/* ensure D0 mode */
	(void) gem_pci_set_power_state(dip, conf_handle, PCI_PMCSR_D0);

	ilr = pci_config_get32(conf_handle, PCI_CONF_ILINE);
	DPRINTF(0, (CE_CONT, "!%s%d: ilr 0x%08x", drv_name, unit, ilr));
I 11
#ifdef lint
	ilr = ilr;
#endif
I 13
	pcie_cap = gem_search_pci_cap(dip, conf_handle, PCI_CAP_ID_PCI_E);
E 13
E 11

I 13
	if (pcie_cap) {
		uint32_t	devcap;
		uint32_t	devcsr;

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
#if 1
		if ((devcsr & (7 << 12)) < (3 << 12)) {
			devcsr = (devcsr & ~(7 << 12)) | (3 << 12);
			pci_config_put32(conf_handle,
			    pcie_cap + 8, devcsr);
		}
#else
		devcsr = (devcsr & ~(7 << 12)) | (3 << 12);
		pci_config_put32(conf_handle, pcie_cap + 8, devcsr);
#endif
	}
E 13
	pci_config_teardown(&conf_handle);
I 13
	conf_handle = NULL;
E 13

	switch (cmd) {
	case DDI_ATTACH:
		/*
		 * Map the device registers in the kernel virtual space.
		 */
		if (gem_pci_regs_map_setup(dip,
D 11
			PCI_ADDR_MEM32, PCI_ADDR_MASK, &nfo_dev_attr,
			(caddr_t *)&base, &regs_ha) != DDI_SUCCESS) {
E 11
I 11
		    PCI_ADDR_MEM32, PCI_ADDR_MASK, &nfo_dev_attr,
		    (caddr_t *)&base, &regs_ha) != DDI_SUCCESS) {
E 11

D 5
			return DDI_FAILURE;
E 5
I 5
			return (DDI_FAILURE);
E 5
		}

		/*
		 * construct gem configration
		 */
D 11
		gcp = (struct gem_conf *) kmem_zalloc(sizeof(*gcp), KM_SLEEP);
		lp  = (struct nfo_dev *)
			kmem_zalloc(sizeof(struct nfo_dev), KM_SLEEP);
E 11
I 11
		gcp = kmem_zalloc(sizeof (*gcp), KM_SLEEP);
		lp = kmem_zalloc(sizeof (struct nfo_dev), KM_SLEEP);
E 11

		lp->chip = p;
I 6
		lp->hwcap = p->hwcap;
E 6

		/* name */
D 11
		sprintf(gcp->gc_name, "%s%d", drv_name, unit);
E 11
I 11
		(void) sprintf(gcp->gc_name, "%s%d", drv_name, unit);
E 11

D 11
		/* consistency on tx and rx */
E 11
D 3
#ifdef CONFIG_DAC
E 3
I 3
#if !defined(TEST_FMT1) && !defined(TEST_FMT2)
E 3
D 6
		is64bit = (p->hwmode & HWMODE_64BIT) != 0;
E 6
I 6
D 10
		is64bit = (p->hwcap & CAP_64BIT) != 0;
E 10
I 10
		is64bit = ((p->hwcap & CAP_64BIT) != 0);
E 10
E 6
#else
		is64bit = B_FALSE;
#endif
D 11
		gcp->gc_tx_buf_align = sizeof(uint8_t) - 1;
E 11
I 11
D 13
		gcp->gc_tx_buf_align = sizeof (uint8_t) - 1;
E 13
I 13
		/* tx ring depends on descriptor format */
		if (is64bit) {
			/* format 3 */
			max_ring_size = 16*1024;
#ifndef TEST_FMT1
		} else if (lp->hwcap & CAP_JUMBO) {
			/* format 2 */
			max_ring_size = 16*1024;
#endif
		} else {
			/* format 1 */
			max_ring_size = 1024;
		}
E 13
#ifdef GEM_CONFIG_TX_DIRECT
E 11
D 13
		gcp->gc_tx_max_frags = GEM_MAXTXFRAGS;
E 13
I 13
#define	MAXTXFRAGS	(min(GEM_MAXTXFRAGS, 16))
E 13
D 11
		gcp->gc_tx_max_descs_per_pkt = GEM_MAXTXFRAGS;
		gcp->gc_tx_desc_unit_shift = (!is64bit) ? 3 : 4;
D 5
		gcp->gc_tx_buf_size  = TX_RING_SIZE;
E 5
I 5
		gcp->gc_tx_buf_size   = TX_RING_SIZE;
E 5
		gcp->gc_tx_buf_limit  = gcp->gc_tx_buf_size;
D 5
		gcp->gc_tx_ring_size = TX_RING_SIZE;
E 5
I 5
		gcp->gc_tx_ring_size  = TX_RING_SIZE;
E 11
I 11
#else
D 13
		gcp->gc_tx_max_frags = 1;
E 13
I 13
#define	MAXTXFRAGS	1
E 13
#endif
I 13
		tx_ring_size = TX_BUF_SIZE * max(MAXTXFRAGS / 2, 1);
		tx_ring_size = max(min(tx_ring_size, max_ring_size), 64);

		/* workaround for tx hang */
		tx16 = B_FALSE;
#ifdef WA_TX16
		if ((lp->hwcap & CAP_WA_TX16) ||
		    ((lp->hwcap & CAP_WA_TX16_2) && revid < 0xa2)) {
			tx16 = B_TRUE;
		}
#endif

		gcp->gc_tx_buf_align = sizeof (uint8_t) - 1;
		gcp->gc_tx_max_frags = MAXTXFRAGS;
E 13
		gcp->gc_tx_max_descs_per_pkt = gcp->gc_tx_max_frags;
		gcp->gc_tx_desc_unit_shift = is64bit ? 4 : 3;
I 13
#ifdef GEM_CONFIG_TX_DIRECT
E 13
		gcp->gc_tx_buf_size = TX_BUF_SIZE;
D 13
		gcp->gc_tx_buf_limit = gcp->gc_tx_buf_size;
		gcp->gc_tx_ring_size = TX_RING_SIZE;
E 13
I 13
#else
		gcp->gc_tx_buf_size = tx_ring_size;
#endif
		gcp->gc_tx_buf_limit = tx16 ? 16 : gcp->gc_tx_buf_size;
		gcp->gc_tx_ring_size = tx_ring_size;
E 13
E 11
E 5
		gcp->gc_tx_ring_limit = gcp->gc_tx_ring_size;
D 5
		gcp->gc_tx_auto_pad  = B_FALSE;
E 5
I 5
D 11
		gcp->gc_tx_auto_pad   = B_FALSE;
E 11
I 11
		gcp->gc_tx_auto_pad = B_TRUE;
E 11
E 5
		gcp->gc_tx_copy_thresh = nfo_tx_copy_thresh;
D 11
		gcp->gc_tx_desc_write_oo = B_FALSE;
E 11
I 11
D 13
		gcp->gc_tx_desc_write_oo = B_TRUE;
E 13
I 13
#ifdef WA_SHORT_FRAG
		gcp->gc_tx_min_fraglen = 64;
#endif
E 13
E 11

D 11
		gcp->gc_rx_buf_align = sizeof(uint32_t) - 1;
E 11
I 11
		gcp->gc_rx_buf_align = sizeof (uint32_t) - 1;
E 11
		gcp->gc_rx_max_frags = 1;
D 11
		gcp->gc_rx_desc_unit_shift = (!is64bit) ? 3 : 4;
E 11
I 11
		gcp->gc_rx_desc_unit_shift = is64bit ? 4 : 3;
E 11
D 13
		gcp->gc_rx_ring_size = RX_RING_SIZE;
E 13
I 13
		gcp->gc_rx_ring_size = min(RX_BUF_SIZE, max_ring_size);
E 13
D 5
		gcp->gc_rx_buf_max  = RX_RING_SIZE;
E 5
I 5
D 11
		gcp->gc_rx_buf_max   = RX_RING_SIZE;
E 11
I 11
		gcp->gc_rx_buf_max = gcp->gc_rx_ring_size;
E 11
E 5
		gcp->gc_rx_copy_thresh = nfo_rx_copy_thresh;
D 11
		gcp->gc_rx_header_len  = 0;
E 11
I 11
		gcp->gc_rx_header_len = 0;
E 11

D 5
		gcp->gc_io_area_size   = 0;
E 5
I 5
		gcp->gc_io_area_size = 0;
E 5

		/* map attributes */
D 2
		STRUCT_COPY(gcp->gc_dev_attr, nfo_dev_attr);
		STRUCT_COPY(gcp->gc_buf_attr, nfo_buf_attr);
		STRUCT_COPY(gcp->gc_desc_attr, nfo_buf_attr);
E 2
I 2
		gcp->gc_dev_attr = nfo_dev_attr;
		gcp->gc_buf_attr = nfo_buf_attr;
		gcp->gc_desc_attr = nfo_buf_attr;
E 2

		/* dma attributes */
D 2
		STRUCT_COPY(gcp->gc_dma_attr_desc, nfo_dma_attr_desc);
E 2
I 2
		gcp->gc_dma_attr_desc = nfo_dma_attr_desc;
E 2
		if (is64bit) {
D 2
			STRUCT_COPY(gcp->gc_dma_attr_txbuf, nfo_dma_attr_buf64);
E 2
I 2
			gcp->gc_dma_attr_txbuf = nfo_dma_attr_buf64;
E 2
		} else {
D 2
			STRUCT_COPY(gcp->gc_dma_attr_txbuf, nfo_dma_attr_buf32);
E 2
I 2
			gcp->gc_dma_attr_txbuf = nfo_dma_attr_buf32;
E 2
		}
D 11
		gcp->gc_dma_attr_txbuf.dma_attr_align  = gcp->gc_tx_buf_align+1;
		gcp->gc_dma_attr_txbuf.dma_attr_sgllen = gcp->gc_tx_max_frags;
E 11
I 11
		gcp->gc_dma_attr_txbuf.dma_attr_align =
		    gcp->gc_tx_buf_align + 1;
		gcp->gc_dma_attr_txbuf.dma_attr_sgllen =
		    gcp->gc_tx_max_frags;

E 11
		if (is64bit) {
D 2
			STRUCT_COPY(gcp->gc_dma_attr_rxbuf, nfo_dma_attr_buf64);
E 2
I 2
			gcp->gc_dma_attr_rxbuf = nfo_dma_attr_buf64;
E 2
		} else {
D 2
			STRUCT_COPY(gcp->gc_dma_attr_rxbuf, nfo_dma_attr_buf32);
E 2
I 2
			gcp->gc_dma_attr_rxbuf = nfo_dma_attr_buf32;
E 2
		}
D 11
		gcp->gc_dma_attr_rxbuf.dma_attr_align  = gcp->gc_rx_buf_align+1;
		gcp->gc_dma_attr_rxbuf.dma_attr_sgllen = gcp->gc_rx_max_frags;
E 11
I 11
		gcp->gc_dma_attr_rxbuf.dma_attr_align =
		    gcp->gc_rx_buf_align + 1;
		gcp->gc_dma_attr_rxbuf.dma_attr_sgllen =
		    gcp->gc_rx_max_frags;
E 11

D 13

E 13
		/* timeout parameters */
		gcp->gc_tx_timeout = GEM_TX_TIMEOUT;
		gcp->gc_tx_timeout_interval = GEM_TX_TIMEOUT_INTERVAL;

		/* flow control */
		gcp->gc_flow_control = FLOW_CONTROL_RX_PAUSE;

D 11
                /* mii mode */
E 11
I 11
D 13
		/* mii mode */
E 11
		gcp->gc_mii_mode = GEM_MODE_1000BASET;

E 13
		/* MII timeout parameters */
		gcp->gc_mii_link_watch_interval = GEM_LINK_WATCH_INTERVAL;
		gcp->gc_mii_an_watch_interval = ONESEC/10;
D 11
		gcp->gc_mii_reset_timeout    = MII_RESET_TIMEOUT;
		gcp->gc_mii_an_timeout       = MII_AN_TIMEOUT;
		gcp->gc_mii_an_wait          = 0;
		gcp->gc_mii_linkdown_timeout = MII_LINKDOWN_TIMEOUT; 
E 11
I 11
		gcp->gc_mii_reset_timeout = MII_RESET_TIMEOUT;
		gcp->gc_mii_an_timeout = MII_AN_TIMEOUT;
		gcp->gc_mii_an_wait = 0;
		gcp->gc_mii_linkdown_timeout = MII_LINKDOWN_TIMEOUT;
E 11

		/* workaround for PHY */
D 11
		gcp->gc_mii_an_delay        = 0;
		gcp->gc_mii_linkdown_action = MII_ACTION_RSA;
E 11
I 11
		gcp->gc_mii_an_delay = 0;
		gcp->gc_mii_linkdown_action = MII_ACTION_RESET;
E 11
		gcp->gc_mii_linkdown_timeout_action = MII_ACTION_RESET;
I 13
#if 1
E 13
D 5
		gcp->gc_mii_dont_reset      = B_FALSE;	/* XXX */
E 5
I 5
D 11
		gcp->gc_mii_dont_reset      = B_FALSE;
D 6
#ifdef NEVER
E 5
I 2
		gcp->gc_mii_an_oneshot	    = B_TRUE;
I 5
#else
		gcp->gc_mii_an_oneshot	    = B_FALSE;	/* XXX */
#endif
E 5
I 3
#ifdef notyet
E 6
I 6
		gcp->gc_mii_an_oneshot	    = B_FALSE;
E 11
I 11
		gcp->gc_mii_dont_reset = B_FALSE;
I 13
#else
		gcp->gc_mii_dont_reset = B_TRUE;
#endif
E 13
		gcp->gc_mii_an_oneshot = B_FALSE;
E 11
E 6
E 3
		gcp->gc_mii_hw_link_detection = B_TRUE;
E 2
D 3

E 3
I 3
D 6
#else
		gcp->gc_mii_hw_link_detection = B_FALSE;
#endif
E 6
I 6

E 6
E 3
		/* I/O methods */

		/* mac operation */
		gcp->gc_attach_chip = &nfo_attach_chip;
		gcp->gc_reset_chip = &nfo_reset_chip;
D 11
		gcp->gc_init_chip  = &nfo_init_chip;
E 11
I 11
		gcp->gc_init_chip = &nfo_init_chip;
E 11
		gcp->gc_start_chip = &nfo_start_chip;
D 11
		gcp->gc_stop_chip  = &nfo_stop_chip;
E 11
I 11
		gcp->gc_stop_chip = &nfo_stop_chip;
E 11
		gcp->gc_multicast_hash = NULL;
		gcp->gc_set_rx_filter = &nfo_set_rx_filter;
		gcp->gc_set_media = &nfo_set_media;
		gcp->gc_get_stats = &nfo_get_stats;
		gcp->gc_interrupt = &nfo_interrupt;

		/* descriptor operation */
		gcp->gc_tx_start = &nfo_tx_start;
		gcp->gc_rx_start = NULL;

I 8
D 13
		lp->dmac = DMACTRL_TxRCMP_EN;
E 13
I 13
		lp->dmac = 0;	/* was DMACTRL_TxRCMP_EN */
E 13

E 8
		if (!is64bit) {
D 8
			/* format 1 and 2 */
E 8
I 8
			/* format 1 or 2 */
E 8
			gcp->gc_tx_desc_write = &nfo_tx_desc_write32;
			gcp->gc_rx_desc_write = &nfo_rx_desc_write32;
D 11
			gcp->gc_tx_desc_stat  = &nfo_tx_desc_stat;
			gcp->gc_rx_desc_stat  = &nfo_rx_desc_stat;
			gcp->gc_tx_desc_init  = &nfo_tx_desc_init32;
			gcp->gc_rx_desc_init  = &nfo_rx_desc_init32;
E 11
I 11
			gcp->gc_tx_desc_stat = &nfo_tx_desc_stat;
			gcp->gc_rx_desc_stat = &nfo_rx_desc_stat;
			gcp->gc_tx_desc_init = &nfo_tx_desc_init32;
			gcp->gc_rx_desc_init = &nfo_rx_desc_init32;
E 11
			gcp->gc_tx_desc_clean = &nfo_tx_desc_init32;
			gcp->gc_rx_desc_clean = &nfo_rx_desc_init32;
D 3
#ifdef CONFIG_JUMBO
E 3
I 3
#ifndef TEST_FMT1
E 3
D 6
			if ((p->hwmode & HWMODE_JUMBO) != 0) {
E 6
I 6
D 10
			if ((p->hwcap & CAP_JUMBO) != 0) {
E 10
I 10
			if (p->hwcap & CAP_JUMBO) {
E 10
E 6
				/* format 2 */
D 8
				lp->dmac = DMACTRL_EXFMT_EN | DMACTRL_EXFMT_2
					 | DMACTRL_RXCHECK;
			} else
#endif
			{
				/* format 1 */
				lp->dmac = 0;
E 8
I 8
D 11
				lp->dmac |= DMACTRL_DFMT_2 | DMACTRL_RXCHECK;
E 11
I 11
D 13
				lp->dmac |= DMACTRL_DFMT_2;
E 13
I 13
				lp->dmac |= DMACTRL_DFMT_2 | DMACTRL_TxRCMP_EN;
E 13
				if (lp->hwcap & CAP_CKSUM) {
					lp->dmac |= DMACTRL_RXCHECK;
				}
E 11
E 8
			}
I 8
#endif
E 8
D 11
		}
		else {
E 11
I 11
		} else {
E 11
			/* format 3 */
			gcp->gc_tx_desc_write = &nfo_tx_desc_write64;
			gcp->gc_rx_desc_write = &nfo_rx_desc_write64;
D 11
			gcp->gc_tx_desc_stat  = &nfo_tx_desc_stat;
			gcp->gc_rx_desc_stat  = &nfo_rx_desc_stat;
			gcp->gc_tx_desc_init  = &nfo_tx_desc_init64;
			gcp->gc_rx_desc_init  = &nfo_rx_desc_init64;
E 11
I 11
			gcp->gc_tx_desc_stat = &nfo_tx_desc_stat;
			gcp->gc_rx_desc_stat = &nfo_rx_desc_stat;
			gcp->gc_tx_desc_init = &nfo_tx_desc_init64;
			gcp->gc_rx_desc_init = &nfo_rx_desc_init64;
E 11
			gcp->gc_tx_desc_clean = &nfo_tx_desc_init64;
			gcp->gc_rx_desc_clean = &nfo_rx_desc_init64;

D 8
			lp->dmac = DMACTRL_EXFMT_EN | DMACTRL_EXFMT_3
E 8
I 8
D 11
			lp->dmac |= DMACTRL_DFMT_3
E 8
D 6
				 | DMACTRL_RXCHECK;
#ifdef CONFIG_HWVLAN
			lp->dmac |= DMACTRL_VLANSTRIP | DMACTRL_VLANINS;
#endif
E 6
I 6
				 | DMACTRL_RXCHECK | 0x00c00000;
E 11
I 11
D 13
			lp->dmac |= DMACTRL_DFMT_3 | 0x00c00000;
E 13
I 13
			lp->dmac |=
			    DMACTRL_DFMT_3 | DMACTRL_TxRCMP_EN | 0x00c00000;
E 13
			if (lp->hwcap & CAP_CKSUM) {
				lp->dmac |= DMACTRL_RXCHECK;
			}
E 11

D 10
			if ((lp->hwcap & CAP_VLAN) != 0) {
E 10
I 10
			if (lp->hwcap & CAP_VLAN) {
E 10
				lp->dmac |= DMACTRL_VLANSTRIP | DMACTRL_VLANINS;
			}
E 6
		}

		gcp->gc_get_packet = NULL;

		/* mii operations */
I 10
D 11
		gcp->gc_mii_probe  = &nfo_mii_probe;
E 10
		gcp->gc_mii_init   = &nfo_mii_init;
E 11
I 11
		gcp->gc_mii_probe = &nfo_mii_probe;
		gcp->gc_mii_init = &nfo_mii_init;
E 11
		gcp->gc_mii_config = &nfo_mii_config;
D 11
		gcp->gc_mii_sync   = &nfo_mii_sync;
		gcp->gc_mii_read   = &nfo_mii_read;
		gcp->gc_mii_write  = &nfo_mii_write;
E 11
I 11
		gcp->gc_mii_sync = &nfo_mii_sync;
		gcp->gc_mii_read = &nfo_mii_read;
		gcp->gc_mii_write = &nfo_mii_write;
E 11
		gcp->gc_mii_tune_phy = NULL;

D 6
		/* disalble wol */
		ddi_put32(regs_ha, (uint32_t *)(base + WAKECTRL), 0);
E 6
I 6
		lp->revid = revid;
D 11
		lp->mac_in_use      = B_FALSE;
E 11
I 11
		lp->mac_in_use = B_FALSE;
E 11
		lp->mac_initialized = B_FALSE;
		lp->phy_initialized = B_FALSE;
E 6

D 10
		dp = gem_do_attach(dip, gcp, base, &regs_ha, lp, sizeof(*lp));
E 10
I 10
		dp = gem_do_attach(dip, 0,
D 11
				gcp, base, &regs_ha, lp, sizeof(*lp));
E 11
I 11
		    gcp, base, &regs_ha, lp, sizeof (*lp));
E 11
E 10

D 11
		kmem_free(gcp, sizeof(*gcp));
E 11
I 11
		kmem_free(gcp, sizeof (*gcp));
E 11
		if (dp == NULL) {
			cmn_err(CE_WARN, "!%s%d: gem_do_attach failed",
D 11
				drv_name, unit);
E 11
I 11
			    drv_name, unit);
E 11
I 6
			goto err_free_mem;
E 6
		}

		return (DDI_SUCCESS);

err_free_mem:
D 11
		kmem_free(lp, sizeof(struct nfo_dev));
E 11
I 11
		kmem_free(lp, sizeof (struct nfo_dev));
E 11
err:
		return (DDI_FAILURE);

	case DDI_RESUME:
I 6
		nfo_power_up(GEM_GET_DEV(dip));
E 6
D 11
		return gem_resume(dip);
E 11
I 11
		return (gem_resume(dip));
E 11

	}
	return (DDI_FAILURE);
}

static int
nfodetach(dev_info_t *dip, ddi_detach_cmd_t cmd)
{
I 6
	struct gem_dev	*dp;
	struct nfo_dev	*lp;

E 6
	switch (cmd) {
	case DDI_DETACH:
I 6
		dp = GEM_GET_DEV(dip);
D 11
		lp = (struct nfo_dev *) dp->private;
E 11
I 11
		lp = dp->private;
E 11

		if (lp->mac_in_use) {
			/* XXX - reset driverloaded flag */
			OUTL(dp, TxCTRL,
D 11
				INL(dp, TxCTRL) & ~TxCTRL_HSEMA_LOADED);
E 11
I 11
			    INL(dp, TxCTRL) & ~TxCTRL_HSEMA_LOADED);
E 11
		}
I 11

		/*
		 * XXX - We need to restore the original factory mac address.
		 * Once we changed the node addresss, there is no way
		 * to get the correct address.
		 */
		OUTL(dp, MACADDR + 0, lp->factory_mac_addr[0]);
		OUTL(dp, MACADDR + 4, lp->factory_mac_addr[1]);
E 11
E 6
		return (gem_do_detach(dip));

	case DDI_SUSPEND:
	case DDI_PM_SUSPEND:
D 11
		gem_suspend(dip);
		return (DDI_SUCCESS);
E 11
I 11
		return (gem_suspend(dip));
E 11
	}
	return (DDI_FAILURE);
}

/* ======================================================== */
/*
 * OS depend (loadable streams driver) routine
 */
/* ======================================================== */
I 11
#ifdef GEM_CONFIG_GLDv3
D 13
DDI_DEFINE_STREAM_OPS(nfo_ops, nulldev, nulldev, nfoattach, nfodetach,
    nodev, NULL, D_MP, NULL);
E 13
I 13
GEM_STREAM_OPS(nfo_ops, nfoattach, nfodetach);
E 13
#else
E 11
static	struct module_info nfominfo = {
	0,			/* mi_idnum */
	"nfo",			/* mi_idname */
	0,			/* mi_minpsz */
D 2
	ETHERMTU,		/* mi_maxpsz */
	TX_RING_SIZE*ETHERMAX,	/* mi_hiwat */
E 2
I 2
	INFPSZ,			/* mi_maxpsz */
	64*1024,		/* mi_hiwat */
E 2
	1,			/* mi_lowat */
};

static	struct qinit nforinit = {
	(int (*)()) NULL,	/* qi_putp */
	gem_rsrv,		/* qi_srvp */
	gem_open,		/* qi_qopen */
	gem_close,		/* qi_qclose */
	(int (*)()) NULL,	/* qi_qadmin */
	&nfominfo,		/* qi_minfo */
	NULL			/* qi_mstat */
};

static	struct qinit nfowinit = {
	gem_wput,		/* qi_putp */
	gem_wsrv,		/* qi_srvp */
	(int (*)()) NULL,	/* qi_qopen */
	(int (*)()) NULL,	/* qi_qclose */
	(int (*)()) NULL,	/* qi_qadmin */
	&nfominfo,		/* qi_minfo */
	NULL			/* qi_mstat */
};

static struct streamtab	nfo_info = {
	&nforinit,	/* st_rdinit */
	&nfowinit,	/* st_wrinit */
	NULL,		/* st_muxrinit */
	NULL		/* st_muxwrinit */
};

static	struct cb_ops cb_nfo_ops = {
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
	&nfo_info,	/* cb_stream */
	D_MP,		/* cb_flag */
};

static	struct dev_ops nfo_ops = {
	DEVO_REV,	/* devo_rev */
	0,		/* devo_refcnt */
	gem_getinfo,	/* devo_getinfo */
	nulldev,	/* devo_identify */
	nulldev,	/* devo_probe */
	nfoattach,	/* devo_attach */
	nfodetach,	/* devo_detach */
	nodev,		/* devo_reset */
	&cb_nfo_ops,	/* devo_cb_ops */
	NULL,		/* devo_bus_ops */
D 5
	ddi_power,	/* devo_power */
E 5
I 5
	gem_power,	/* devo_power */
E 5
};
D 11

E 11
I 11
#endif /* GEM_CONFIG_GLDv3 */
E 11
static struct modldrv modldrv = {
	&mod_driverops,	/* Type of module.  This one is a driver */
	ident,
	&nfo_ops,	/* driver ops */
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

	DPRINTF(2, (CE_CONT, "!nfo: _init: called"));
D 5
	status = mod_install(&modlinkage);
E 5

D 5
	return status;
E 5
I 5
	gem_mod_init(&nfo_ops, "nfo");
	status = mod_install(&modlinkage);
	if (status != DDI_SUCCESS) {
		gem_mod_fini(&nfo_ops);
	}
	return (status);
E 5
}

/*
D 5
 * _fini : 
E 5
I 5
 * _fini : done
E 5
 */
int
_fini(void)
{
	int	status;

	DPRINTF(2, (CE_CONT, "!nfo: _fini: called"));
	status = mod_remove(&modlinkage);
D 5
	return status;
E 5
I 5
	if (status == DDI_SUCCESS) {
		gem_mod_fini(&nfo_ops);
	}
	return (status);
E 5
}

int
_info(struct modinfo *modinfop)
{
D 5
	return mod_info(&modlinkage, modinfop);
E 5
I 5
	return (mod_info(&modlinkage, modinfop));
E 5
}
E 1
