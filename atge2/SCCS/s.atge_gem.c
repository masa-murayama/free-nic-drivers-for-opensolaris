h55562
s 01274/00463/04555
d D 1.15 12/11/02 20:59:14 mrym 15 14
c 2.6.12
e
s 00004/00002/05014
d D 1.14 12/01/08 08:49:01 mrym 14 13
c 2.6.10 again
e
s 00001/00002/05015
d D 1.13 12/01/08 08:32:59 mrym 13 12
c 2.6.10
e
s 00001/00001/05016
d D 1.12 11/12/31 10:51:34 mrym 12 11
c 2.6.9 DEV0->DEVO
e
s 00035/00006/04982
d D 1.11 11/12/04 23:27:25 mrym 11 10
c 2.6.9 
e
s 00230/00108/04758
d D 1.10 11/07/10 22:10:35 mrym 10 9
c 2.6.8
e
s 00032/00034/04834
d D 1.9 10/11/21 23:27:03 mrym 9 8
c 2.6.8 rx hang on receiving errored packets was fixed
e
s 00364/00192/04504
d D 1.8 10/11/18 01:03:10 mrym 8 7
c 2.6
e
s 01190/00192/03506
d D 1.7 10/09/08 17:51:23 mrym 7 6
c 2.6.6
e
s 00394/00228/03304
d D 1.6 09/05/17 21:28:03 mrym 6 5
c 2.6.4, many fixed for L1E
e
s 00027/00002/03505
d D 1.5 08/12/31 22:52:41 mrym 5 4
c 2.6.4: read request packet size increased
e
s 00018/00013/03489
d D 1.4 08/12/17 03:58:08 mrym 4 3
c 2.6.2
e
s 01633/00294/01869
d D 1.3 08/12/06 01:42:22 mrym 3 2
c 2.6.2 release; L1/L1E/L2 support
e
s 00290/00127/01873
d D 1.2 08/10/05 17:00:58 mrym 2 1
c 2.6.1
e
s 02000/00000/00000
d D 1.1 08/08/18 00:14:38 mrym 1 0
c date and time created 08/08/18 00:14:38 by mrym
e
u
U
f e 0
t
T
I 1
/*
D 3
 * atge_gem.c: Attansic L1 Gigabit Ethernet MAC driver
E 3
I 3
D 7
 * atge_gem.c: Attansic L1/L2, Athros L1E Ethernet MAC driver
E 7
I 7
 * atge_gem.c: Attansic L1/L2, Atheros L1/L1C Ethernet MAC driver
E 7
E 3
 *
D 6
 * Copyright (c) 2008 Masayuki Murayama.  All rights reserved.
E 6
I 6
D 7
 * Copyright (c) 2008-2009 Masayuki Murayama.  All rights reserved.
E 7
I 7
D 15
 * Copyright (c) 2008-2010 Masayuki Murayama.  All rights reserved.
E 15
I 15
 * Copyright (c) 2008-2012 Masayuki Murayama.  All rights reserved.
E 15
E 7
E 6
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the author nor the names of its contributors may be
 *    used to endorse or promote products derived from this software without
 *    specific prior written permission.
 *
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
I 3

/*
 * Acknowledgement:
D 4
 * Masafumi Ohta who tested the driver repeatedly on his eee PC 
E 4
I 4
 * Masafumi Ohta who tested the driver repeatedly on his eee PC
E 4
 */
E 3
#pragma	ident	"%W% %E%"

/*
 * Change log
I 2
 *
 * 2008/10/05 2.6.1 released
I 7
 * 2009/07/08 L2 didn't exit power save mode in atge_reset_phy()
 *            MII_DBG_ADDR -> MII_DBG_DATA
 * 2009/07/09 2.6.5 released
E 7
E 2
 */

/*
 * TODO:
D 2
 * fix for test04 of nicdrv - multicast hash function fixed
 * rx cksum
 * statistics
E 2
I 2
D 7
 * fix for nicdrv test04 - multicast hash function fixed
E 7
 * rx cksum - not supported because of no UDP cksum
D 7
 * statistics - done
E 2
 * get dma burst len from PCI-E info block in PCI configuration space
 * syncing descriptors before dma - done
 * tuning interrupt coalesce timers
I 3
 * add PCIE_PHYMISC_FORCE_RCV_DET to PCIE_PHYMISC
E 7
I 7
 * L1C
D 15
 * read mac address from EEPROM
E 15
I 15
 * force to load EEPROM
 * wol
 * msi_patch
E 15
E 7
E 3
 */

/*
 * System Header files.
 */
#include <sys/types.h>
#include <sys/conf.h>
#include <sys/debug.h>
#include <sys/kmem.h>
#include <sys/modctl.h>
#include <sys/errno.h>
#include <sys/ddi.h>
#include <sys/sunddi.h>
#include <sys/byteorder.h>
#include <sys/ethernet.h>
#include <sys/pci.h>
I 14
#include <sys/atomic.h>
E 14

#include "gem_mii.h"
#include "gem.h"
#include "atl1reg.h"

D 15
char	ident[] = "atheros L1 nic driver v" VERSION;
E 15
I 15
char	ident[] = "atheros L1 driver v" VERSION;
E 15

/* Debugging support */
#ifdef DEBUG_LEVEL
static int atge_debug = DEBUG_LEVEL;
#define	DPRINTF(n, args)	if (atge_debug > (n)) cmn_err args
#else
#define	DPRINTF(n, args)
#endif

/*
 * Useful macros and typedefs
 */
#define	ONESEC	drv_usectohz(1*1000000)
#define	ROUNDUP(x, a)	(((x) + (a) - 1) & ~((a) - 1))

#define	FLSHB(dp, reg)	(void) INB(dp, reg)
#define	FLSHW(dp, reg)	(void) INW(dp, reg)
#define	FLSHL(dp, reg)	(void) INL(dp, reg)

D 2
#define	UPDATE_MBOX(dp, lp)	{	\
E 2
I 2
D 10
#define	UPDATE_MBOX(dp)	{	\
E 10
I 10
#define	UPDATE_MBOX_1(dp)	{	\
E 10
	struct atge_dev	*lp = dp->private;	\
E 2
D 3
	OUTL(dp, MBOX,	\
E 3
I 3
	OUTL(dp, MBOX_1,	\
E 3
D 15
	    ((lp)->tx_buffer_tail << MBOX_TBD_TAIL_SHIFT)	\
D 6
	    | ((lp)->rx_status_tail << MBOX_RSD_HEAD_SHIFT)	\
E 6
I 6
	    | ((lp)->rx_status_head << MBOX_RSD_HEAD_SHIFT)	\
E 6
	    | ((lp)->rx_buffer_tail << MBOX_RBD_TAIL_SHIFT));	\
E 15
I 15
	    (lp)->tx_buffer_tail << MBOX_TBD_TAIL_SHIFT	\
	    | (lp)->rx_status_head << MBOX_RSD_HEAD_SHIFT	\
	    | (lp)->rx_buffer_tail << MBOX_RBD_TAIL_SHIFT);	\
E 15
}

#define	INSIDE(slot, head, tail)	\
	(((head) <= (tail)) ?	\
	    ((head) <= (slot) && (slot) < (tail)) :	\
	    ((slot) < (tail) || (head) <= (slot)))

I 3
#ifndef VTAG_SIZE
E 3
#define	VTAG_SIZE	4
I 3
#endif
E 3

I 15
#define	NITEMS(a)	(sizeof (a) / sizeof (a[0]))

E 15
I 7
#ifdef GEM3
#define	IS_MAC_ONLINE(dp)	((dp)->mac_state == MAC_STATE_ONLINE)
#define	mac_active	mac_state
#else
#define	IS_MAC_ONLINE(dp)	((dp)->mac_active)
#endif
E 7
/*
 * Our configuration
 */
I 3
D 6
#define	ISR_RX_ERR_1	\
	(ISR_RXF_OVF_1 | ISR_RBD_UNRUN_1 | ISR_RSD_OVF_1 | \
	ISR_HOST_RBD_UNRUN_1 | ISR_HOST_RSD_OVF_1)
#define	ISR_RX_OK_1	\
	(ISR_ISM_RX_1 | ISR_MAC_RX_1 | ISR_RX_DMA_1 | ISR_RX_PKT_1)
#define	ISR_TX_1 \
	(ISR_ISM_TX_1 | ISR_MAC_TX_1 | ISR_TX_DMA_1 | ISR_TX_PKT_1)

#define	ISR_RX_ERR_2	(ISR_RXD_OV_2 | ISR_RXS_OV_2 | ISR_RXF_OVF_2)
#define	ISR_RX_OK_2	(ISR_RX_UPDATE_2)
#define	ISR_TX_2 \
	(ISR_TX_UPDATE_2 | ISR_TXD_UR_2 | ISR_TXS_OV_2 | ISR_TXF_UR_2)

#define	ISR_RX_ERR_1e	(ISR_RXF_OVF_1e | ISR_RXF0_OV_1e)
#define	ISR_RX_OK_1e	(ISR_RX_PKT_1e)
#define	ISR_TX_1e 	(ISR_TX_DMA_1e | ISR_TX_PKT_1e)

E 3
#ifdef CONFIG_POLLING
D 3
#define	OUR_INTR_MASK	\
	(ISR_SM | ISR_GPHY | ISR_PCIE_ERR | ISR_DMAR_TO_RST | \
	ISR_DMAW_TO_RST | ISR_TX_DMA | ISR_ISM_RX)
E 3
I 3
#define	OUR_INTR_MASK_1	\
	(ISR_SM_1 | ISR_GPHY_1 | ISR_PCIE_ERR_1 | ISR_DMAR_TO_RST_1 | \
	ISR_DMAW_TO_RST_1 | ISR_TX_DMA_1 | ISR_ISM_RX_1)

#define	OUR_INTR_MASK_2	\
	(ISR_GPHY_2 | ISR_PCIE_ERR_2 | \
	ISR_DMAR_TO_RST_2 | ISR_DMAW_TO_RST_2 | \
	ISR_TX_UPDATE_2 | ISR_TXD_UR_2 | ISR_TXS_OV_2 | ISR_TXF_UR_2 | \
	ISR_RX_UPDATE_2 | ISR_RXD_OV_2 | ISR_RXS_OV_2 | ISR_RXF_OVF_2)

#define	OUR_INTR_MASK_1e	\
	(ISR_SM_1e | ISR_GPHY_1e | ISR_PCIE_ERR_1e | ISR_DMAR_TO_RST_1e | \
	ISR_DMAW_TO_RST_1e | ISR_TX_DMA_1e | ISR_RX_PKT_1e)
E 3
#else
D 3
#define	OUR_INTR_MASK	\
	(ISR_SM | ISR_GPHY | ISR_PCIE_ERR | ISR_DMAR_TO_RST | \
	ISR_DMAW_TO_RST | ISR_ISM_TX | ISR_ISM_RX)
E 3
I 3
#define	OUR_INTR_MASK_1	\
	(ISR_GPHY_1 | ISR_PCIE_ERR_1 | ISR_DMAR_TO_RST_1 | \
	ISR_DMAW_TO_RST_1 | ISR_ISM_TX_1 | ISR_ISM_RX_1)

#define	OUR_INTR_MASK_2	\
	(ISR_SM_2 | ISR_GPHY_2 | ISR_PCIE_ERR_2 | \
	ISR_DMAR_TO_RST_2 | ISR_DMAW_TO_RST_2 | \
	ISR_TX_UPDATE_2 | ISR_TXD_UR_2 | ISR_TXS_OV_2 | ISR_TXF_UR_2 | \
	ISR_RX_UPDATE_2 | ISR_RXD_OV_2 | ISR_RXS_OV_2 | ISR_RXF_OVF_2)

#define	OUR_INTR_MASK_1e	\
	(ISR_SM_1e | ISR_GPHY_1e | ISR_PCIE_ERR_1e | ISR_DMAR_TO_RST_1e | \
	ISR_DMAW_TO_RST_1e | ISR_TX_PKT_1e | ISR_RX_PKT_1e)
E 3
#endif
E 6
#ifdef GEM_CONFIG_TX_DIRECT
D 2
#define	MAXTXFRAGS	min(18, GEM_MAXTXFRAGS)
E 2
I 2
#define	MAXTXFRAGS	min(GEM_MAXTXFRAGS, 18)
E 2
#else
#define	MAXTXFRAGS	1
#endif

#ifdef TEST_RX_EMPTY
#define	RX_BUF_SIZE	1
#endif
#ifdef TEST_TXDESC_FULL
#define	TX_BUF_SIZE	4
#define	TX_RING_SIZE	8
#endif

#ifndef TX_BUF_SIZE
D 7
#define	TX_BUF_SIZE	64
E 7
I 7
D 10
#define	TX_BUF_SIZE	128
E 10
I 10
#define	TX_BUF_SIZE	256
E 10
E 7
#endif

#ifndef TX_RING_SIZE
D 2
#if MAXTXFRAGS == 1
#define	TX_RING_SIZE	TX_BUF_SIZE
#else
#define	TX_RING_SIZE	(TX_BUF_SIZE * 4)
E 2
I 2
D 5
#define	TX_RING_SIZE	(TX_BUF_SIZE * min(MAXTXFRAGS, 4))
E 5
I 5
#define	TX_RING_SIZE	(min(TX_BUF_SIZE * min(MAXTXFRAGS, 4), 512))
E 5
E 2
#endif
D 2
#endif
E 2

#ifndef RX_BUF_SIZE
#define	RX_BUF_SIZE	256
#endif
D 3
#ifndef RX_RING_SIZE
#define	RX_RING_SIZE	RX_BUF_SIZE
#endif
E 3

static int	atge_tx_copy_thresh = 256;
static int	atge_rx_copy_thresh = 256;

D 3
/* io area offsets */
/* we use gem tx_ring for tpd */
#define	IOA_TBD_SIZE	(sizeof (struct tx_buffer_desc) * TX_RING_SIZE)
#define	IOA_RBD_SIZE	(sizeof (struct rx_buffer_desc) * RX_RING_SIZE)
#define	IOA_ISM_SIZE	(sizeof (struct intr_status_msg))
#define	IOA_SM_SIZE	(sizeof (uint32_t) * STAT_MAX)

E 3
/*
D 3
 * rsd should be in rx desc area.
 */
#define	IOA_TBD_OFFSET	0
#define	IOA_RBD_OFFSET	(IOA_TBD_OFFSET + IOA_TBD_SIZE)
#define	IOA_ISM_OFFSET	(IOA_RBD_OFFSET + IOA_RBD_SIZE)
#define	IOA_SM_OFFSET	(IOA_ISM_OFFSET + IOA_ISM_SIZE)
#define	IOA_SIZE	(IOA_TBD_SIZE + IOA_RBD_SIZE \
			+ IOA_ISM_SIZE + IOA_SM_SIZE)

/*
E 3
 * the nic state
 */
I 3
struct l2_rxf {
	uint32_t	rf_head;	/* offset from rxf_offset[][] */
	uint32_t	rf_tail;	/* offset from rxf_offset[][] */
	int		rf_curr_ring;
	uint16_t	rf_seqnum;
};

E 3
struct atge_dev {
	boolean_t	initialized;
	boolean_t	need_to_reset;

	uint8_t		mac_addr[ETHERADDRL];
	uint8_t		revid;	/* chip revision id */

	uint32_t	mac_ctl;
	uint32_t	imr;
I 2
	uint32_t	isr_pended;
E 2

D 6
	uint_t		tx_buffer_head;
E 6
I 6
D 10
	volatile uint_t	tx_buffer_head;
E 6
	uint_t		tx_buffer_tail;
	uint_t		rx_buffer_head;
	uint_t		rx_buffer_tail;
	uint_t		rx_status_head;
	uint_t		rx_status_tail;
E 10
I 10
	volatile uint_t	tx_buffer_head;	/* L1 L1E L1C */
	uint_t		tx_buffer_tail;	/* L1 L1E L2 L1C */
	uint_t		rx_buffer_head;	/* L2 */
	uint_t		rx_buffer_tail;	/* L1 */
	uint_t		rx_status_head;	/* L1 */
	uint_t		rx_status_tail;	/* L1 */
E 10

D 3
	kmutex_t	mbox_lock;
E 3
I 3
	kmutex_t	mbox_lock;	/* L1 */
E 3

I 3
	offset_t	tbd_offset;
	offset_t	rbd_offset;	/* L1 L2 */
	offset_t	ism_offset;	/* L1 */
#define	tbd_tail_offset	ism_offset	/* L1 */
	offset_t	sm_offset;


	offset_t	rxf_offset[4][2];	/* L1E L2E */
	offset_t	rxf_mb_offset[4][2];	/* L1E L2E */
	size_t		rxf_buf_len;		/* L1E L2E */
	size_t		rxf_buf_hiwat;		/* L1E L2E */

	size_t		tbd_size;
E 3
#ifdef RESET_TEST
	int		reset_test;
#endif
D 3
	uint32_t	last_stat[STAT_MAX];
I 2
	boolean_t	ignore_linkdown;
E 3
I 3
D 15
	uint16_t	gphyc;
E 15
I 15
	uint32_t	gphyc;
E 15
I 6
	boolean_t	phy_initialized;
E 6

	struct l2_rxf	rxf[4];
	int		chip;

	uint_t		tbd_pos[TX_BUF_SIZE];	/* L2 */
D 7
#ifdef CONFIG_POLLING
E 7
I 7
#ifdef CONFIG_ADAPTIVE_COALESCE
E 7
	int		last_poll_interval;
#endif
I 6
D 7
	/* interrupt status bits */
E 7
I 7
	/* interrupt status bits configuration */
E 7
	uint32_t	isr_disable;
	uint32_t	isr_enable;
	uint32_t	isr_tx_ok;
	uint32_t	isr_tx_err;
	uint32_t	isr_rx_ok;
	uint32_t	isr_rx_err;
	uint32_t	isr_dma_err;
	uint32_t	isr_gphy;
	uint32_t	isr_sm;
	uint32_t	isr_pcie_err;
I 7
	uint32_t	isr_fatal_err;
	uint32_t	isr_clear_all;
E 7
	char		*isr_bits;

	/* statistics */
	clock_t		last_stats_update;
I 8

D 10
	/* pci-e configration info */
E 10
I 10
	/* pci-e configuration info */
E 10
	uint_t		maxpayload;
	uint_t		maxrequest;
I 10

	boolean_t	intr_rdclr;
I 15

	uint_t		ctrl_flags;
#define	ATL1C_ASPM_L0S_SUPPORT	0x0001
#define	ATL1C_ASPM_L1_SUPPORT	0x0002

	boolean_t	msi_lnkpatch;
E 15
E 10
E 8
E 6
E 3
E 2
};

/*
 * Supported chips
 */
struct chip_info {
	uint16_t	venid;
	uint16_t	devid;
	char		*name;
I 3
	int		chip_type;
#define	CHIP_L1		0
#define	CHIP_L2		1
#define	CHIP_L1E	2
#define	CHIP_L2E_A	3
#define	CHIP_L2E_B	4
I 7
D 10
#ifdef CONFIG_1C
E 10
#define	CHIP_L1C	5
#define	CHIP_L2C	6
#define	CHIP_L2C_B	7
#define	CHIP_L2C_B2	8
#define	CHIP_L1D	9
I 8
#define	CHIP_L1D_2_0	10
E 8
D 10
#endif
E 10
E 7
E 3
};

static struct chip_info atge_chiptbl[] = {
D 3
	{ 0x1969, 0x1048, "Attansic L1", },
E 3
I 3
	{ 0x1969, 0x1048, "Attansic L1", CHIP_L1},
	{ 0x1969, 0x2048, "Attansic L2", CHIP_L2},
	{ 0x1969, 0x1026, "Atheros AR8121/8113/8114", CHIP_L1E},
I 7
D 10
#ifdef CONFIG_1C
E 10
	{ 0x1969, 0x1063, "Atheros AR8131", CHIP_L1C},
	{ 0x1969, 0x1062, "Atheros AR8132", CHIP_L2C},
	{ 0x1969, 0x2060, "Atheros AR8152 v1.1", CHIP_L2C_B},
	{ 0x1969, 0x2062, "Atheros AR8152 v2.0", CHIP_L2C_B2},
	{ 0x1969, 0x1073, "Atheros AR8151 v1.0", CHIP_L1D},
I 8
	{ 0x1969, 0x1083, "Atheros AR8151 v2.0", CHIP_L1D_2_0},
E 8
D 10
#endif
E 10
E 7
E 3
};
D 15
#define	CHIPTABLESIZE   (sizeof (atge_chiptbl) / sizeof (struct chip_info))
E 15

I 15
static struct patch_info {
	uint16_t	devid;
	uint8_t		revid;
	uint16_t	subvenid;
	uint16_t	subsysid;
} patch_list[] = {
	{0x2060U, 0xC1U, 0x1019U, 0x8152U},
	{0x2060U, 0xC1U, 0x1019U, 0x2060U},
	{0x2060U, 0xC1U, 0x1019U, 0xE000U},
	{0x2062U, 0xC0U, 0x1019U, 0x8152U},
	{0x2062U, 0xC0U, 0x1019U, 0x2062U},
	{0x2062U, 0xC0U, 0x1458U, 0xE000U},
	{0x2062U, 0xC1U, 0x1019U, 0x8152U},
	{0x2062U, 0xC1U, 0x1019U, 0x2062U},
	{0x2062U, 0xC1U, 0x1458U, 0xE000U},
	{0x2062U, 0xC1U, 0x1565U, 0x2802U},
	{0x2062U, 0xC1U, 0x1565U, 0x2801U},
	{0x1073U, 0xC0U, 0x1019U, 0x8151U},
	{0x1073U, 0xC0U, 0x1019U, 0x1073U},
	{0x1073U, 0xC0U, 0x1458U, 0xE000U},
	{0x1083U, 0xC0U, 0x1458U, 0xE000U},
	{0x1083U, 0xC0U, 0x1019U, 0x8151U},
	{0x1083U, 0xC0U, 0x1019U, 0x1083U},
	{0x1083U, 0xC0U, 0x1462U, 0x7680U},
	{0x1083U, 0xC0U, 0x1565U, 0x2803U},
};


E 15
/*
 * Macros to identify chip generation.
 */

/* ======================================================== */

/* mii operations */
static void  atge_mii_sync(struct gem_dev *);
I 15
static uint16_t atge_mii_read_raw(struct gem_dev *, uint_t);
static uint16_t atge_mii_read_ext(struct gem_dev *, uint_t, uint_t);
E 15
D 2
static uint16_t  atge_mii_read(struct gem_dev *, uint_t);
E 2
I 2
static uint16_t atge_mii_read(struct gem_dev *, uint_t);
static void atge_mii_write_raw(struct gem_dev *, uint_t, uint16_t);
I 15
static void atge_mii_write_ext(struct gem_dev *, uint_t, uint_t, uint16_t);
E 15
E 2
static void atge_mii_write(struct gem_dev *, uint_t, uint16_t);
static int atge_mii_init(struct gem_dev *);
I 15
static void atge_mii_tune_phy(struct gem_dev *dp);
E 15

/* nic operations */
static int atge_attach_chip(struct gem_dev *);
static int atge_reset_chip(struct gem_dev *);
D 3
static int atge_init_chip(struct gem_dev *);
E 3
I 3
static int atge_init_chip_1(struct gem_dev *);
E 3
static int atge_start_chip(struct gem_dev *);
static int atge_stop_chip(struct gem_dev *);
static int atge_set_media(struct gem_dev *);
static int atge_set_rx_filter(struct gem_dev *);
static int atge_get_stats(struct gem_dev *);
I 3
static int atge_init_chip_1e(struct gem_dev *);
I 7
D 10
#ifdef CONFIG_1C
E 10
static int atge_init_chip_1c(struct gem_dev *);
D 10
#endif
E 10
E 7
E 3

/* descriptor operations */
D 3
static int atge_tx_desc_write(struct gem_dev *dp, int slot,
E 3
I 3
static int atge_tx_desc_write_1_1e(struct gem_dev *dp, int slot,
E 3
	ddi_dma_cookie_t *dmacookie, int frags, uint64_t flags);
D 3
static void atge_tx_start(struct gem_dev *dp, int startslot, int nslot);
static void atge_rx_desc_write(struct gem_dev *dp, int slot,
E 3
I 3
static void atge_tx_start_1_1e(struct gem_dev *dp, int startslot, int nslot);
static void atge_rx_desc_write_1(struct gem_dev *dp, int slot,
E 3
	ddi_dma_cookie_t *dmacookie, int frags);
D 3
static void atge_rx_start(struct gem_dev *dp, int startslot, int nslot);
static uint_t atge_tx_desc_stat(struct gem_dev *dp, int slot, int ndesc);
static uint64_t atge_rx_desc_stat(struct gem_dev *dp, int slot, int ndesc);
E 3
I 3
static void atge_rx_start_1(struct gem_dev *dp, int startslot, int nslot);
I 11
#ifdef GEM_CONFIG_TX_HEAD_PTR
D 15
static uint_t atge_tx_desc_head_1_1e(struct gem_dev *dp);
E 15
I 15
static uint_t atge_tx_desc_head_1(struct gem_dev *dp);
static uint_t atge_tx_desc_head_1e(struct gem_dev *dp);
E 15
#else
E 11
static uint_t atge_tx_desc_stat_1_1e(struct gem_dev *dp, int slot, int ndesc);
I 11
#endif /* GEM_CONFIG_TX_HEAD_PTR */
E 11
static uint64_t atge_rx_desc_stat_1(struct gem_dev *dp, int slot, int ndesc);
E 3

D 3
static void atge_tx_desc_init(struct gem_dev *dp, int slot);
static void atge_rx_desc_init(struct gem_dev *dp, int slot);
E 3
I 3
static void atge_tx_desc_init_1_1e(struct gem_dev *dp, int slot);
static void atge_rx_desc_init_1(struct gem_dev *dp, int slot);
E 3

I 3
static void atge_rx_desc_write_1e(struct gem_dev *dp, int slot,
	ddi_dma_cookie_t *dmacookie, int frags);
static uint64_t atge_rx_desc_stat_1e(struct gem_dev *dp, int slot, int ndesc);
static void atge_rx_desc_init_1e(struct gem_dev *dp, int slot);

E 3
/* interrupt handler */
static uint_t atge_interrupt(struct gem_dev *dp);

/* ======================================================== */

/* mapping attributes */
/* Data access requirements. */
static struct ddi_device_acc_attr atge_dev_attr = {
	DDI_DEVICE_ATTR_V0,
	DDI_STRUCTURE_LE_ACC,
	DDI_STRICTORDER_ACC
};

/* On sparc, the buffers should be native endianness */
static struct ddi_device_acc_attr atge_buf_attr = {
	DDI_DEVICE_ATTR_V0,
	DDI_NEVERSWAP_ACC,	/* native endianness */
	DDI_STRICTORDER_ACC
};

static ddi_dma_attr_t atge_dma_attr_buf = {
	DMA_ATTR_V0,		/* dma_attr_version */
	0,			/* dma_attr_addr_lo */
	0x00ffffffffffull,	/* dma_attr_addr_hi */
D 2
	0x0000000027ffull,	/* dma_attr_count_max */
E 2
I 2
	0x000000003fffull,	/* dma_attr_count_max */
E 2
	0, /* patched later */	/* dma_attr_align */
	0x00003ffc,		/* dma_attr_burstsizes */
	1,			/* dma_attr_minxfer */
D 2
	0x00000000ffffull,	/* dma_attr_maxxfer */
E 2
I 2
	0x0000000027ffull,	/* dma_attr_maxxfer */
E 2
	0x0000ffffffffull,	/* dma_attr_seg */
	0, /* patched later */	/* dma_attr_sgllen */
	1,			/* dma_attr_granular */
	0			/* dma_attr_flags */
};

static ddi_dma_attr_t atge_dma_attr_desc = {
	DMA_ATTR_V0,		/* dma_attr_version */
	0,			/* dma_attr_addr_lo */
	0x0000ffffffffull,	/* dma_attr_addr_hi */
	0x0000ffffffffull,	/* dma_attr_count_max */
D 3
	8,			/* dma_attr_align */
E 3
I 3
	128,			/* dma_attr_align */
E 3
	0x0000fffc,		/* dma_attr_burstsizes */
	1,			/* dma_attr_minxfer */
	0x0000ffffffffull,	/* dma_attr_maxxfer */
	0x0000ffffffffull,	/* dma_attr_seg */
	1,			/* dma_attr_sgllen */
	1,			/* dma_attr_granular */
	0			/* dma_attr_flags */
};

/* ======================================================== */
/*
D 10
 * HW manupilation routines
E 10
I 10
 * HW manipulation routines
E 10
 */
/* ======================================================== */
I 15
#ifdef DEBUG_IOTRACE

#undef	OUTB
#undef	OUTW
#undef	OUTL
#undef	INB
#undef	INW
#undef	INL


#define	OUTB(dp, p, v)	\
	atge_put8((dp)->regs_handle, \
		(void *)((caddr_t)((dp)->base_addr) + (p)), v)
#define	OUTW(dp, p, v)	\
	atge_put16((dp)->regs_handle, \
		(void *)((caddr_t)((dp)->base_addr) + (p)), v)
#define	OUTL(dp, p, v)	\
	atge_put32((dp)->regs_handle, \
		(void *)((caddr_t)((dp)->base_addr) + (p)), v)
#define	INB(dp, p)	\
	atge_get8((dp)->regs_handle, \
		(void *)(((caddr_t)(dp)->base_addr) + (p)))
#define	INW(dp, p)	\
	atge_get16((dp)->regs_handle, \
		(void *)(((caddr_t)(dp)->base_addr) + (p)))
#define	INL(dp, p)	\
	atge_get32((dp)->regs_handle, \
		(void *)(((caddr_t)(dp)->base_addr) + (p)))
#if 0
extern uint8_t atge_get8(ddi_acc_handle_t handle, uint8_t *dev_addr);
extern uint16_t atge_get16(ddi_acc_handle_t handle, uint16_t *dev_addr);
extern uint32_t atge_get32(ddi_acc_handle_t handle, uint32_t *dev_addr);
extern uint64_t atge_get64(ddi_acc_handle_t handle, uint64_t *dev_addr);
extern void atge_put8(ddi_acc_handle_t handle, uint8_t *dev_addr,
    uint8_t value);
extern void atge_put16(ddi_acc_handle_t handle, uint16_t *dev_addr,
    uint16_t value);
extern void atge_put32(ddi_acc_handle_t handle, uint32_t *dev_addr,
    uint32_t value);
extern void atge_put64(ddi_acc_handle_t handle, uint64_t *dev_addr,
    uint64_t value);
#endif

uint8_t
atge_get8(ddi_acc_handle_t handle, uint8_t *dev_addr)
{
	uint8_t	ret;

	ret = ddi_get8(handle, dev_addr);
	DPRINTF(-1, (CE_CONT, "!%s: %x %x(%x) -> %x",
	    __func__, handle, dev_addr,
	    ((caddr_t)dev_addr) - ((ddi_acc_hdl_t *)handle)->ah_addr,
	    ret));
	return (ret);
}

uint16_t
atge_get16(ddi_acc_handle_t handle, uint16_t *dev_addr)
{
	uint16_t	ret;

	ret = ddi_get16(handle, dev_addr);
	DPRINTF(-1, (CE_CONT, "!%s: %x %x(%x) -> %x",
	    __func__, handle, dev_addr,
	    ((caddr_t)dev_addr) - ((ddi_acc_hdl_t *)handle)->ah_addr,
	    ret));
	return (ret);
}

uint32_t
atge_get32(ddi_acc_handle_t handle, uint32_t *dev_addr)
{
	uint32_t	ret;

	ret = ddi_get32(handle, dev_addr);
	DPRINTF(-1, (CE_CONT, "!%s: %x %x(%x) -> %x",
	    __func__, handle, dev_addr,
	    ((caddr_t)dev_addr) - ((ddi_acc_hdl_t *)handle)->ah_addr,
	    ret));
	return (ret);
}

uint64_t
atge_get64(ddi_acc_handle_t handle, uint64_t *dev_addr)
{
	uint64_t	ret;

	ret = ddi_get64(handle, dev_addr);

	DPRINTF(-1, (CE_CONT, "!%s: %x %x(%x) -> %x",
	    __func__, handle, dev_addr,
	    ((caddr_t)dev_addr) - ((ddi_acc_hdl_t *)handle)->ah_addr,
	    ret));
	return (ret);
}

void
atge_put8(ddi_acc_handle_t handle, uint8_t *dev_addr, uint8_t value)
{
	DPRINTF(-1, (CE_CONT, "!%s: %x %x(%x) <- %x",
	    __func__, handle, dev_addr,
	    ((caddr_t)dev_addr) - ((ddi_acc_hdl_t *)handle)->ah_addr,
	    value));
	ddi_put8(handle, dev_addr, value);
}

void
atge_put16(ddi_acc_handle_t handle, uint16_t *dev_addr, uint16_t value)
{
	DPRINTF(-1, (CE_CONT, "!%s: %x %x(%x) <- %x",
	    __func__, handle, dev_addr,
	    ((caddr_t)dev_addr) - ((ddi_acc_hdl_t *)handle)->ah_addr,
	    value));
	ddi_put16(handle, dev_addr, value);
}

void
atge_put32(ddi_acc_handle_t handle, uint32_t *dev_addr, uint32_t value)
{
	DPRINTF(-1, (CE_CONT, "!%s: %x %x(%x) <- %x",
	    __func__, handle, dev_addr,
	    ((caddr_t)dev_addr) - ((ddi_acc_hdl_t *)handle)->ah_addr,
	    value));
	ddi_put32(handle, dev_addr, value);
}

void
atge_put64(ddi_acc_handle_t handle, uint64_t *dev_addr, uint64_t value)
{
	DPRINTF(-1, (CE_CONT, "!%s: %x %x(%x) <- %x",
	    __func__, handle, dev_addr,
	    ((caddr_t)dev_addr) - ((ddi_acc_hdl_t *)handle)->ah_addr,
	    value));
	ddi_put64(handle, dev_addr, value);
}
#endif /* DEBUG_IOTRACE */

E 15
__INLINE__ static void
atge_ioarea_dma_sync(struct gem_dev *dp, off_t start, size_t len, int how)
{
	(void) ddi_dma_sync(dp->desc_dma_handle,
	    (off_t)(dp->io_area_dma - dp->rx_ring_dma + start),
	    len, how);
}

__INLINE__ static void
D 3
atge_rbd_desc_dma_sync(struct gem_dev *dp, int head, int nslot)
E 3
I 3
atge_rbd_desc_dma_sync_1(struct gem_dev *dp, int head, int nslot)
E 3
{
	int	n;
	int	m;
I 3
	struct atge_dev	*lp = dp->private;
E 3

	/* sync active descriptors */
	if (nslot == 0) {
		/* no rx descriptor ring */
		return;
	}

	n = dp->gc.gc_rx_ring_size - head;
	if ((m = nslot - n) > 0) {
		(void) atge_ioarea_dma_sync(dp,
D 3
		    (off_t)IOA_RBD_OFFSET,
E 3
I 3
		    (off_t)lp->rbd_offset,
E 3
		    (size_t)(m * sizeof (struct rx_buffer_desc)),
		    DDI_DMA_SYNC_FORDEV);
		nslot = n;
	}

	(void) atge_ioarea_dma_sync(dp,
D 3
	    (off_t)(head * sizeof (struct rx_buffer_desc) + IOA_RBD_OFFSET),
E 3
I 3
	    (off_t)(head * sizeof (struct rx_buffer_desc) + lp->rbd_offset),
E 3
	    (size_t)(nslot * sizeof (struct rx_buffer_desc)),
	    DDI_DMA_SYNC_FORDEV);
}

__INLINE__ static void
I 3
atge_rbd_desc_dma_sync_2(struct gem_dev *dp, int head, int nslot, uint_t type)
{
	int	n;
	int	m;
	struct atge_dev	*lp = dp->private;

	/* sync active descriptors */
	if (nslot == 0) {
		/* no rx descriptor ring */
		return;
	}

	n = dp->gc.gc_rx_ring_size - head;
	if ((m = nslot - n) > 0) {
		(void) atge_ioarea_dma_sync(dp, (off_t)lp->rbd_offset,
		    (size_t)(m * 1536), type);
		nslot = n;
	}

	(void) atge_ioarea_dma_sync(dp, (off_t)(head * 1536 + lp->rbd_offset),
	    (size_t)(nslot * 1536), type);
}

I 7
D 10
#ifdef CONFIG_1C
E 10
E 7
__INLINE__ static void
I 7
atge_rfd_desc_dma_sync_1c(struct gem_dev *dp, int head, int nslot)
{
	int	n;
	int	m;
	struct atge_dev	*lp = dp->private;

	/* sync active descriptors */
	if (nslot == 0) {
		/* no rx descriptor ring */
		return;
	}

	n = dp->gc.gc_rx_ring_size - head;
	if ((m = nslot - n) > 0) {
		(void) atge_ioarea_dma_sync(dp,
		    (off_t)lp->rbd_offset,
		    (size_t)(m * sizeof (struct rx_free_desc)),
		    DDI_DMA_SYNC_FORDEV);
		nslot = n;
	}

	(void) atge_ioarea_dma_sync(dp,
	    (off_t)(head * sizeof (struct rx_free_desc) + lp->rbd_offset),
	    (size_t)(nslot * sizeof (struct rx_free_desc)),
	    DDI_DMA_SYNC_FORDEV);
}

D 10
#endif
E 10
__INLINE__ static void
E 7
E 3
atge_tx_desc_dma_sync(struct gem_dev *dp, int head, int nslot)
{
	int	n;
	int	m;
I 3
	struct atge_dev	*lp = dp->private;
E 3

	/* sync active descriptors */
	if (nslot == 0) {
		/* no tx descriptor ring */
		return;
	}

	n = dp->gc.gc_tx_ring_size - head;
	if ((m = nslot - n) > 0) {
		(void) atge_ioarea_dma_sync(dp,
D 3
		    (off_t)IOA_TBD_OFFSET,
E 3
I 3
		    (off_t)lp->tbd_offset,
E 3
		    (size_t)(m * sizeof (struct tx_buffer_desc)),
		    DDI_DMA_SYNC_FORDEV);
		nslot = n;
	}

	(void) atge_ioarea_dma_sync(dp,
D 3
	    (off_t)(head * sizeof (struct tx_buffer_desc) + IOA_TBD_OFFSET),
E 3
I 3
	    (off_t)(head * sizeof (struct tx_buffer_desc) + lp->tbd_offset),
E 3
	    (size_t)(nslot * sizeof (struct tx_buffer_desc)),
	    DDI_DMA_SYNC_FORDEV);
}

I 15
static void
atge_set_aspm_1c(struct gem_dev *dp, uint_t flags)
{
	uint32_t	val;
	uint32_t	link_l1_timer;
	struct atge_dev	*lp = dp->private;

	/* disable l0s_l1 */
	val = INL(dp, PM_CTRL);
#if 0
	val &= ~(PM_CTRL_L1_ENTRY_TIMER
	    | PM_CTRL_CLK_SWH_L1
	    | PM_CTRL_ASPM_L0S_EN
	    | PM_CTRL_ASPM_L1_EN
	    | PM_CTRL_MAC_ASPM_CHK
	    | PM_CTRL_SERDES_PD_EX_L1);

	val |= (PM_CTRL_SERDES_BUFS_RX_L1_EN
	    | PM_CTRL_SERDES_PLL_L1_EN
	    | PM_CTRL_SERDES_L1_EN);
#else
	val &= ~(PM_CTRL_ASPM_L1_EN |
	    PM_CTRL_ASPM_L0S_EN |
	    PM_CTRL_MAC_ASPM_CHK);

	/* L1 timer */
	if (lp->chip == CHIP_L2C_B2 || lp->chip == CHIP_L1D_2_0) {
		val &= ~PMCTRL_TXL1_AFTER_L0S;
		if (dp->mii_state == MII_STATE_LINKUP &&
		    (dp->speed == GEM_SPD_1000 || dp->speed == GEM_SPD_100)) {
			link_l1_timer = L1D_PMCTRL_L1_ENTRY_TM_16US;
		} else {
			link_l1_timer = 1;
		}
		val = (val & ~L1D_PMCTRL_L1_ENTRY_TM)
		    | link_l1_timer << L1D_PMCTRL_L1_ENTRY_TM_SHIFT;
	} else {
		if (dp->mii_state == MII_STATE_LINKUP &&
		    dp->speed == GEM_SPD_10) {
			link_l1_timer = 1;
		} else if (lp->chip == CHIP_L2C_B) {
			link_l1_timer = L2CB1_PM_CTRL_L1_ENTRY_TM;
		} else {
			link_l1_timer = L1C_PM_CTRL_L1_ENTRY_TM;
		}

		val = (val & ~PM_CTRL_L1_ENTRY_TIMER)
		    | link_l1_timer << PM_CTRL_L1_ENTRY_TIMER_SHIFT;
	}

	/* L0S/L1 enable */
	if ((flags & ATL1C_ASPM_L0S_SUPPORT) &&
	    dp->mii_state == MII_STATE_LINKUP) {
		val |= PM_CTRL_ASPM_L0S_EN | PM_CTRL_MAC_ASPM_CHK;
	}
	if (flags & ATL1C_ASPM_L1_SUPPORT) {
		val |= PM_CTRL_ASPM_L1_EN | PM_CTRL_MAC_ASPM_CHK;
	}

	/* L2CB & L1D & L2CB2 & L1D2 */
	switch (lp->chip) {
	case CHIP_L2C_B:
	case CHIP_L1D:
	case CHIP_L2C_B2:
	case CHIP_L1D_2_0:
		val &= ~PM_CTRL_PM_REQ_TIMER;
		val |= PM_CTRL_PM_REQ_TO_DEF << PM_CTRL_PM_REQ_TIMER_SHIFT;

		val |= PM_CTRL_RCVR_WT_TIMER |
		    PM_CTRL_SERDES_PD_EX_L1 |
		    PM_CTRL_CLK_SWH_L1;
		val &= ~(PM_CTRL_SERDES_L1_EN |
		    PM_CTRL_SERDES_PLL_L1_EN |
		    PM_CTRL_SERDES_BUFS_RX_L1_EN |
		    PM_CTRL_SA_DLY_EN |
		    PM_CTRL_HOTRST);

		/* disable l0s if link down or L2CB */
		if (dp->mii_state != MII_STATE_LINKUP ||
		    lp->chip == CHIP_L2C_B) {
			val &= ~PM_CTRL_ASPM_L0S_EN;
		}
		break;

	default: /* L1C */
		val &= ~PM_CTRL_L1_ENTRY_TIMER;

		if (dp->mii_state == MII_STATE_LINKUP) {
			val |= PM_CTRL_SERDES_L1_EN
			    | PM_CTRL_SERDES_PLL_L1_EN
			    | PM_CTRL_SERDES_BUFS_RX_L1_EN;

			val &= ~(PM_CTRL_SERDES_PD_EX_L1
			    | PM_CTRL_CLK_SWH_L1
			    | PM_CTRL_ASPM_L0S_EN
			    | PM_CTRL_ASPM_L1_EN);
		} else {
			/* link down */
			val |= PM_CTRL_CLK_SWH_L1;

			val &= ~(PM_CTRL_SERDES_L1_EN
			    | PM_CTRL_SERDES_PLL_L1_EN
			    | PM_CTRL_SERDES_BUFS_RX_L1_EN
			    | PM_CTRL_ASPM_L0S_EN);
		}
	}
#endif
	OUTL(dp, PM_CTRL, val);
}

static boolean_t
atge_wait_idle(struct gem_dev *dp, uint_t which)
{
	int	i;
	uint32_t	val;

	for (i = 0; (val = INL(dp, IDLE)) & which; i++) {
		if (i > 10) {
			cmn_err(CE_WARN, "!%s: %s: timeout, IDLE: %b",
			    dp->name, __func__, val, IDLE_BITS);

			return (B_FALSE);
		}
		delay(drv_usectohz(1000));
	}
	return (B_TRUE);
}

E 15
static int
D 2
atge_reset_chip(struct gem_dev *dp)	/* ok */
E 2
I 2
atge_reset_chip(struct gem_dev *dp)
E 2
{
	int		i;
	uint32_t	val;
I 15
	uint32_t	mstc;
E 15
I 8
	int		wait;
E 8
	struct atge_dev	*lp = dp->private;

	DPRINTF(0, (CE_CONT, "!%s: %s: called, time:%d",
	    dp->name, __func__, ddi_get_lbolt()));

	/* initialize soft copy of mac address registers */
	bzero(lp->mac_addr, ETHERADDRL);

	if (!lp->initialized) {
D 2
		/* much vendor magic here */
E 2
I 2
D 3
		/* initialize PCI-E */
E 2
		OUTL(dp, 0x12fc, 0x6500);
D 2
		/* pcie flow control mode change */
E 2
I 2
		/* pcie flow control mode */
E 2
		OUTL(dp, 0x1008, 0x8000 | INL(dp, 0x1008));
		lp->initialized = B_TRUE;
I 2
#ifdef notdef
		/* XXX - moved to atge_mii_init */
		/* reset PHY to exit power saving mode */
		OUTW(dp, GPHYC, 0);
		delay(drv_usectohz(2000));
		OUTW(dp, GPHYC, GPHYC_ENABLE);
		delay(drv_usectohz(25000));
E 3
I 3
		switch (lp->chip) {
		case CHIP_L1:
			/* initialize PCI-E */
			OUTL(dp, 0x12fc, 0x6500);
E 3

D 3
		atge_mii_write_raw(dp, 18, 0x0c00);
#endif
E 3
I 3
			/* change pcie flow control mode */
			OUTL(dp, 0x1008, 0x8000 | INL(dp, 0x1008));
			break;

		case CHIP_L2:
			/* initialize PCI-E */
			OUTL(dp, 0x12fc, 0x6500);

			/* PCIE_DLL_TX_CTRL */
			OUTL(dp, 0x1104, 0x0568);
			break;
I 8
D 10
#ifdef CONFIG_1C
E 10
I 10

E 10
		case CHIP_L1C:
		case CHIP_L2C:
		case CHIP_L2C_B:
		case CHIP_L2C_B2:
		case CHIP_L1D:
		case CHIP_L1D_2_0:
I 15

			(void)INL(dp, WOLCTL);
			OUTL(dp, WOLCTL, 0);

E 15
			OUTL(dp, 0x010c, INL(dp, 0x010c) & ~0x12000);
I 15
			/* LTSSM_ID_CTRL */
E 15
			OUTL(dp, 0x12fc, INL(dp, 0x12fc) & ~0x1000);
E 8

I 8
D 15
			OUTL(dp, PCIE_PHYMISC,
			    INL(dp, PCIE_PHYMISC) | 0x0004);
E 15
I 15
			/* pclk sel could switch to 25M */
			mstc = INL(dp, MSTC) & ~MSTC_CLK_SEL_DIS_1c;
			OUTL(dp, MSTC, mstc);

			if (lp->chip == CHIP_L1C || lp->chip == CHIP_L2C) {
				OUTL(dp, PCIE_PHYMISC,
				    INL(dp, PCIE_PHYMISC) | 0x0004);
			} else {
				if ((mstc & MSTC_WAKEN_25M_1c) == 0) {
					OUTL(dp, MSTC,
					    mstc | MSTC_WAKEN_25M_1c);
				}
			}

E 15
			if (lp->chip == CHIP_L2C_B && lp->revid == 0xc0) {
				val = INL(dp, PCIE_PHYMISC2);
				val &= ~(PCIE_PHYMISC2_SERDES_TH
				    | PCIE_PHYMISC2_SERDES_CDR);
D 15
				val |= (3 << PCIE_PHYMISC2_SERDES_TH_SHIFT)
				    | (3 << PCIE_PHYMISC2_SERDES_CDR_SHIFT);
E 15
I 15
				val |= 3U << PCIE_PHYMISC2_SERDES_TH_SHIFT
				    | 3U << PCIE_PHYMISC2_SERDES_CDR_SHIFT;
E 15
				OUTL(dp, PCIE_PHYMISC2, val);
I 15

				/* extend L1 sync timer */
				OUTL(dp, LINKCTRL,
				    INL(dp, LINKCTRL) | LINKCTRL_EXT_SYNC);
E 15
			}

			/* disable l0s_l1 */
D 15
			val = INL(dp, PM_CTRL);
			val &= ~(PM_CTRL_L1_ENTRY_TIMER
			    | PM_CTRL_CLK_SWH_L1
			    | PM_CTRL_ASPM_L0S_EN
			    | PM_CTRL_ASPM_L1_EN
			    | PM_CTRL_MAC_ASPM_CHK
			    | PM_CTRL_SERDES_PD_EX_L1);

			val |= (PM_CTRL_SERDES_BUDS_RX_L1_EN
			    | PM_CTRL_SERDES_PLL_L1_EN
			    | PM_CTRL_SERDES_L1_EN);
			OUTL(dp, PM_CTRL, val);
E 15
I 15
			atge_set_aspm_1c(dp, 0);
E 15
			break;
D 10
#endif
E 10

E 8
		default:
			/* L1E/L2E_A/L2E_B */
			/* change pcie flow control mode */
			OUTL(dp, 0x1008, 0x8000 | INL(dp, 0x1008));
			break;
		}
		lp->initialized = B_TRUE;
E 3
E 2
	}

I 2
D 7
	/* save pended interrupts */
E 7
I 7
D 8
	/* before clearing interrupts, save them to avoid bogus interrupts */
E 8
I 8
	/* before clearing interrupts, save ISR to avoid bogus interrupts */
E 8
E 7
	OUTL(dp, IMR, 0);
I 7
	OUTL(dp, ISR, lp->isr_disable);	/* for L1C */
E 7
	FLSHL(dp, IMR);
	lp->isr_pended |= INL(dp, ISR);

I 8
	wait = 1000;
E 8
E 2
D 3
	OUTL(dp, MSTC, MSTC_SRST);
E 3
I 3
	switch (lp->chip) {
	case CHIP_L1:
	case CHIP_L2:
		OUTL(dp, MSTC, MSTC_SRST);
		break;

D 7
	default:
		/* L1E L2E_A L2E_B */
		OUTL(dp, MSTC, MSTC_LEDMODE | MSTC_SRST);
E 7
I 7
D 10
#ifdef CONFIG_1C
E 10
	case CHIP_L1C:
	case CHIP_L2C:
	case CHIP_L2C_B:
	case CHIP_L2C_B2:
	case CHIP_L1D:
D 8
		OUTW(dp, MSTC, MSTC_SRST);
E 8
I 8
	case CHIP_L1D_2_0:
D 15
		OUTW(dp, MSTC,
D 10
		    INL(dp, MSTC) | MSTC_OOB_DIS_OFF | MSTC_SRST);
E 10
I 10
		    INL(dp, MSTC) | MSTC_OOB_DIS_OFF_1c | MSTC_SRST);
E 15
I 15
		mstc = INL(dp, MSTC) | MSTC_OOB_DIS_OFF_1c; /* ok */
		OUTL(dp, MSTC, mstc | MSTC_SRST); /* ok */
E 15
E 10
		wait = 10*1000;
E 8
E 7
		break;
I 7

D 10
#endif
E 10
	case CHIP_L1E:
	case CHIP_L2E_A:
	case CHIP_L2E_B:
		OUTL(dp, MSTC, MSTC_LEDMODE_1e | MSTC_SRST);
		break;
E 7
	}
E 3
	FLSHL(dp, MSTC);

D 3
	delay(drv_usectohz(1000));
E 3
I 3
D 7
	delay(drv_usectohz(1000)); /* L1 L2 L1E */
E 7
I 7
D 8
	delay(drv_usectohz(1000)); /* L1 L2 L1E L1C */
E 8
I 8
	delay(drv_usectohz(wait));
E 8
E 7
E 3
D 15

E 15
I 15
#if 0
E 15
D 8
	for (i = 0; val = INL(dp, IDLE); i++) {
E 8
I 8
	for (i = 0; (val = INL(dp, IDLE)) & IDLE_ALL; i++) {
E 8
		if (i > 10) {
			cmn_err(CE_WARN, "!%s: %s: timeout, IDLE: %b",
			    dp->name, __func__, val, IDLE_BITS);

			return (GEM_FAILURE);
		}
D 3
		delay(drv_usectohz(1000));
E 3
I 3
D 8
		delay(drv_usectohz(1000)); /* L1/L2/L1E */
E 8
I 8
		delay(drv_usectohz(1000));
E 8
E 3
	}
I 15
#else
	if (!atge_wait_idle(dp, IDLE_ALL)) {
		return (GEM_FAILURE);
	}
#endif
E 15

I 15
	switch (lp->chip) {
	case CHIP_L1C:
	case CHIP_L2C:
	case CHIP_L2C_B:
	case CHIP_L2C_B2:
	case CHIP_L1D:
	case CHIP_L1D_2_0:
		OUTL(dp, MSTC, mstc); /* ok */
		OUTL(dp, MACCTL, INL(dp, MACCTL) | MACCTL_SPEED_MODE_SW);
		break;
	}

E 15
I 2
D 3
	/* XXX - Is it required ? */
E 3
I 3
D 7
	/* clear wake on lan state - is it required ? */
E 7
I 7
	/* clear wake on lan state - is it required for every reset ? */
E 7
	(void) INL(dp, WOLCTL);
E 3
	OUTL(dp, WOLCTL, 0);

I 3
	/* disable interrupt again */
	OUTL(dp, IMR, 0);
	FLSHL(dp, IMR);

I 15
	/* clock switch setting for L2C_B, L2CB2 and L1D_2 */
	switch (lp->chip) {
	case CHIP_L2C_B:
		val = INL(dp, SERDES_LOCK);
		val &= ~SERDES_MAC_CLK_SLOWDOWN;
		val &= ~SERDES_PYH_CLK_SLOWDOWN;
		OUTL(dp, SERDES_LOCK, val);		/* ok */
		break;

	case CHIP_L2C_B2:
	case CHIP_L1D_2_0:
		val = INL(dp, SERDES_LOCK);
		val |= SERDES_MAC_CLK_SLOWDOWN;
		val |= SERDES_PYH_CLK_SLOWDOWN;
		OUTL(dp, SERDES_LOCK, val);		/* ok */
		break;
	}

E 15
E 3
E 2
	return (GEM_SUCCESS);
}

static int
D 3
atge_init_chip(struct gem_dev *dp)
E 3
I 3
atge_init_chip_1(struct gem_dev *dp)
E 3
{
	int		i;
	int		ret;
	uint32_t	val;
	uint32_t	hiwat;
	uint32_t	lowat;
I 2
D 8
	uint_t		maxpayload;
	uint_t		maxrequest;
E 8
E 2
	struct atge_dev	*lp = dp->private;

	DPRINTF(0, (CE_CONT, "!%s: %s: called at time:%d",
	    dp->name, __func__, ddi_get_lbolt()));

	/* clear bogus interrupt status */
D 7
	OUTL(dp, ISR, 0xffffffffU);
E 7
I 7
	OUTL(dp, ISR, lp->isr_disable | lp->isr_clear_all);
E 7

D 7
	/* mac control: do later */
E 7
I 7
	/* mac control: setup later */
E 7
D 2
	lp->mac_ctl = 0;
E 2
I 2
	lp->mac_ctl = MACCTL_CRCEN | MACCTL_AUTOPAD
D 15
	    | (7 << MACCTL_PRMLEN_SHIFT) | MACCTL_FD | MACCTL_SPEED_10_100
E 15
I 15
	    | 7U << MACCTL_PRMLEN_SHIFT | MACCTL_FD | MACCTL_SPEED_10_100
E 15
	    | MACCTL_TXFC | MACCTL_RXFC;
I 3
D 7
#if 0
E 3
E 2
	OUTL(dp, MACCTL, lp->mac_ctl);
I 3
#endif
E 7
I 7

E 7
	/* setup various base address */
	OUTL(dp, DESCBASE_1, 0);
	OUTL(dp, RSDADDR_1, dp->rx_ring_dma);
	OUTL(dp, TBDADDR_1, dp->io_area_dma + lp->tbd_offset);
	OUTL(dp, ISMADDR_1, dp->io_area_dma + lp->ism_offset);
	OUTL(dp, SMADDR_1, dp->io_area_dma + lp->sm_offset);
	OUTL(dp, RBDADDR_1, dp->io_area_dma + lp->rbd_offset);
E 3

D 3
	/* base address */
	OUTL(dp, DESCBASE, 0);
	OUTL(dp, RSDADDR, dp->rx_ring_dma);
	OUTL(dp, TBDADDR, dp->io_area_dma + IOA_TBD_OFFSET);
	OUTL(dp, ISMADDR, dp->io_area_dma + IOA_ISM_OFFSET);
	OUTL(dp, SMADDR, dp->io_area_dma + IOA_SM_OFFSET);
	OUTL(dp, RBDADDR, dp->io_area_dma + IOA_RBD_OFFSET);

E 3
	/* the number of descriptors */
D 3
	OUTL(dp, RBD_RSD_CNT,
E 3
I 3
	OUTL(dp, RBD_RSD_CNT_1,
E 3
D 15
	    (dp->gc.gc_rx_ring_size << 16) | dp->gc.gc_rx_ring_size);
E 15
I 15
	    dp->gc.gc_rx_ring_size << 16 | dp->gc.gc_rx_ring_size);
E 15
D 3
	OUTL(dp, TBD_CNT, dp->gc.gc_tx_ring_size);
E 3
I 3
	OUTL(dp, TBD_CNT_1, dp->gc.gc_tx_ring_size);
E 3

	/* load the descriptor configuration */
D 3
	OUTL(dp, DESCEN, 1);
E 3
I 3
	OUTL(dp, DESCEN_1, 1);
E 3

	/* mailbox */
	lp->tx_buffer_tail = 0;
	lp->rx_status_head = 0;
	lp->rx_status_tail = 0;
D 3
	lp->rx_status_head = 0;
E 3
	lp->rx_buffer_tail = 0;
D 2
	UPDATE_MBOX(dp, lp);
	DPRINTF(0, (CE_CONT, "%s: %s: MBOX:0x%x",
E 2
I 2
D 10
	UPDATE_MBOX(dp);
E 10
I 10
	UPDATE_MBOX_1(dp);
E 10
	DPRINTF(0, (CE_CONT, "!%s: %s: MBOX:0x%x",
E 2
D 3
	    dp->name, __func__, INL(dp, MBOX)));
E 3
I 3
	    dp->name, __func__, INL(dp, MBOX_1)));
E 3

	/* inter packet gap and inter frame gap */
	OUTL(dp, GAPC, GAPC_STD);
D 2
	DPRINTF(0, (CE_CONT, "%s: %s: GAPC:0x%x",
E 2
I 2
	DPRINTF(0, (CE_CONT, "!%s: %s: GAPC:0x%x",
E 2
	    dp->name, __func__, INL(dp, GAPC)));

	/* half duplex control register */
D 2
#ifdef notdef
	val = 0x37 /* lcol */
	    | (15 << HDCTL_RETRY_SHIFT)
	    | HDCTL_EXC_DEF_EN
	    | (10 << HDCTL_ABEBT_SHIFT)
	    | (7 << HDCTL_JAMIPG_SHIFT);
#else
	val = HDCTL_STD;
#endif
	OUTL(dp, HDCTL, val);
	DPRINTF(0, (CE_CONT, "%s: %s: HDCTL:0x%x",
E 2
I 2
	OUTL(dp, HDCTL, HDCTL_STD);
	DPRINTF(0, (CE_CONT, "!%s: %s: HDCTL:0x%x",
E 2
	    dp->name, __func__, INL(dp, HDCTL)));

	/* Interrupt Delay */
D 7
#ifdef CONFIG_POLLING
E 7
I 7
#ifdef CONFIG_ADAPTIVE_COALESCE
E 7
	val = 1;	/* 2uS */
#else
	val = 200/2;	/* original: 200uS */
#endif
	OUTW(dp, INTRDELAY_INIT, val);
	DPRINTF(0, (CE_CONT, "!%s: %s: INTRDELAY_INIT:0x%x",
	    dp->name, __func__, INW(dp, INTRDELAY_INIT)));

	OUTL(dp, MSTC, MSTC_ITIMER);

	/* Interrupt Clear Timer */
D 3
	OUTW(dp, ISMDISDMA_TIMER, 100*1000/2);	/* original: 100mS in 2uS */
E 3
I 3
	OUTW(dp, INTRCLR_TIMER, 100*1000/2); /* original: 100mS in 2uS */
E 3

D 3
	DPRINTF(0, (CE_CONT, "!%s: %s: ISMDISDMA_TIMER:0x%x",
	    dp->name, __func__, INW(dp, ISMDISDMA_TIMER)));
E 3
I 3
	DPRINTF(0, (CE_CONT, "!%s: %s: INTRCLR_TIMER:0x%x",
	    dp->name, __func__, INW(dp, INTRCLR_TIMER)));
E 3

	/* MTU */
	OUTL(dp, MTU,
	    sizeof (struct ether_header) + dp->mtu + ETHERFCSL + VTAG_SIZE);
	DPRINTF(0, (CE_CONT, "!%s: %s: MTU: 0x%x",
	    dp->name, __func__, INL(dp, MTU)));

	/* Rx jumbo packet configuration */
D 3
	OUTL(dp, RXJCFG,
E 3
I 3
	OUTL(dp, RXJCFG_1,
E 3
D 15
	    (16 << RXJCFG_RSDTIMER_SHIFT)
	    | (1 << RXJCFG_LKAH_SHIFT)
	    | ((dp->rx_buf_len / 8) << RXJCFG_THRESH_SHIFT));
E 15
I 15
	    16U << RXJCFG_RSDTIMER_SHIFT
	    | 1U << RXJCFG_LKAH_SHIFT
	    | (dp->rx_buf_len / 8) << RXJCFG_THRESH_SHIFT);
E 15

	DPRINTF(0, (CE_CONT, "!%s: %s: RXJCFG: 0x%x",
D 3
	    dp->name, __func__, INL(dp, RXJCFG)));
E 3
I 3
	    dp->name, __func__, INL(dp, RXJCFG_1)));
E 3

	/* descriptor flow control */
	val = (INL(dp, MSTC) & (MSTC_DID | MSTC_REV)) >> MSTC_REV_SHIFT;
I 2
	DPRINTF(0, (CE_CONT,
	    "!%s: %s: device id:%x", dp->name, __func__, val));
E 2
	if (val == 0x8001 || val == 0x9001 ||
	    val == 0x9002 || val == 0x9003) {
		/* setup RBD flow control using RXFFC register */
		lowat = (dp->gc.gc_rx_ring_size * 7) / 8;
		hiwat = max(dp->gc.gc_rx_ring_size / 16, 2);
D 3
		OUTL(dp, RXFFC, (hiwat << RXFFC_HIWAT_SHIFT) | lowat);
E 3
I 3
D 15
		OUTL(dp, RXFFC_1, (hiwat << RXFFC_HIWAT_SHIFT) | lowat);
E 15
I 15
		OUTL(dp, RXFFC_1, hiwat << RXFFC_HIWAT_SHIFT | lowat);
E 15
E 3

		/* setup RSD flow control */
D 3
		OUTL(dp, RSDFC, (lowat << RSDFC_LOWAT_SHIFT) | hiwat);
E 3
I 3
D 15
		OUTL(dp, RSDFC_1, (lowat << RSDFC_LOWAT_SHIFT) | hiwat);
E 15
I 15
		OUTL(dp, RSDFC_1, lowat << RSDFC_LOWAT_SHIFT | hiwat);
E 15
E 3
	} else {
		/* setup RXF flow control */
D 3
		val = INL(dp, RAM_RXF_SIZE);
E 3
I 3
		val = INL(dp, RAM_RXF_SIZE_1);
E 3
D 2
		lowat = max(val / 16, 192);
E 2
I 2
		DPRINTF(0, (CE_CONT, "!%s: %s: ram rxf size :%d",
		    dp->name, __func__, val));
		lowat = max(val / 16, 192);	/* was min 192 */
E 2
		hiwat = max((val * 7) / 8, lowat + 16);
D 3
		OUTL(dp, RXFFC, (hiwat << RXFFC_HIWAT_SHIFT) | lowat);
E 3
I 3
D 15
		OUTL(dp, RXFFC_1, (hiwat << RXFFC_HIWAT_SHIFT) | lowat);
E 15
I 15
		OUTL(dp, RXFFC_1, hiwat << RXFFC_HIWAT_SHIFT | lowat);
E 15
E 3

		/* setup RSD flow control */
D 3
		val = INL(dp, RAM_RSD_SIZE);
E 3
I 3
		val = INL(dp, RAM_RSD_SIZE_1);
E 3
D 2
		lowat = max(val / 8, 2);
E 2
I 2
		DPRINTF(0, (CE_CONT, "!%s: %s: ram rsd size :%d",
		    dp->name, __func__, val));
		lowat = max(val / 8, 2);	/* was min 2 */
E 2
		hiwat = max((val * 7) / 8, lowat + 3);
D 3
		OUTL(dp, RSDFC, (lowat << RSDFC_LOWAT_SHIFT) | hiwat);
E 3
I 3
D 15
		OUTL(dp, RSDFC_1, (lowat << RSDFC_LOWAT_SHIFT) | hiwat);
E 15
I 15
		OUTL(dp, RSDFC_1, lowat << RSDFC_LOWAT_SHIFT | hiwat);
E 15
E 3
	}

	/* TXQCTL: */
D 3
	OUTL(dp, TXQCTL,
E 3
I 3
	OUTL(dp, TXQCTL_1,
E 3
D 15
	    (0x100 << TXQCTL_TXF_BURST_NUM_SHIFT)
	    | (16 << TXQCTL_TBD_FETCH_TH_SHIFT)
E 15
I 15
	    0x100U << TXQCTL_TXF_BURST_NUM_SHIFT
	    | 16U << TXQCTL_TBD_FETCH_TH_SHIFT
E 15
	    | TXQCTL_EN
	    | TXQCTL_ENH_MODE
D 15
	    | (4 << TXQCTL_TBD_BURST_NUM_SHIFT));
E 15
I 15
	    | 4U << TXQCTL_TBD_BURST_NUM_SHIFT);
E 15
	DPRINTF(0, (CE_CONT, "!%s: %s: TXQCTL:0x%x",
D 3
	    dp->name, __func__, INL(dp, TXQCTL)));
E 3
I 3
	    dp->name, __func__, INL(dp, TXQCTL_1)));
E 3

	/* tx jumbo packet cfg */
D 3
	OUTL(dp, TXJCFG,
E 3
I 3
	OUTL(dp, TXJCFG_1,
E 3
D 15
	    (1 << TXJCFG_TBDIPG_SHIFT)
	    | ((dp->rx_buf_len / 8) << TXJCFG_THRESH_SHIFT));
E 15
I 15
	    1U << TXJCFG_TBDIPG_SHIFT
	    | (dp->rx_buf_len / 8) << TXJCFG_THRESH_SHIFT);
E 15
	DPRINTF(0, (CE_CONT,
	    "!%s: %s: TXJCFG:0x%x",
D 3
	    dp->name, __func__, INL(dp, TXJCFG)));
E 3
I 3
	    dp->name, __func__, INL(dp, TXJCFG_1)));
E 3

	/* RXQCTL: */
D 3
	OUTL(dp, RXQCTL,
E 3
I 3
	OUTL(dp, RXQCTL_1,
E 3
	    RXQCTL_EN
	    | RXQCTL_CUT_THRU_EN
D 15
	    | (1 << RXQCTL_RBD_PREF_MIN_IPG_SHIFT)
	    | (8 << RXQCTL_RSD_BURST_THRESH_SHIFT)
	    | (8 << RXQCTL_RBD_BURST_NUM_SHIFT));
E 15
I 15
	    | 1U << RXQCTL_RBD_PREF_MIN_IPG_SHIFT
	    | 8U << RXQCTL_RSD_BURST_THRESH_SHIFT
	    | 8U << RXQCTL_RBD_BURST_NUM_SHIFT);
E 15
	DPRINTF(0, (CE_CONT, "!%s: %s: RXQCTL: 0x%x",
D 3
	    dp->name, __func__, INL(dp, RXQCTL)));
E 3
I 3
	    dp->name, __func__, INL(dp, RXQCTL_1)));
E 3

	/* dma control */
I 2
D 8
	val = INL(dp, PCIE_DEVCTRL);
	maxpayload = (val >> 5) & 7;
	maxrequest = (val >> 12) & 7;
	DPRINTF(0, (CE_CONT,
	    "!%s: %s: PCIE DEVCTRL:0x%x (payload:%d request:%d)",
	    dp->name, __func__, val, maxpayload, maxrequest));
E 8
E 2
D 3
	OUTL(dp, DMAC,
	    DMAC_DMAW_EN | DMAC_DMAR_EN
E 3
I 3
	OUTL(dp, DMAC_1,
	    DMAC_DMAW_EN_1 | DMAC_DMAR_EN_1
E 3
D 2
	    | DMAC_DMAW_MAXDMA_256
	    | DMAC_DMAR_MAXDMA_512	/* was 256, poor performance */
	    | DMAC_DMAR_ENH_ORDER);
E 2
I 2
D 8
	    | (min(MAXDMA_1024, maxpayload) << DMAC_DMAW_MAXDMA_SHIFT)
	    | (min(MAXDMA_1024, maxrequest) << DMAC_DMAR_MAXDMA_SHIFT)
	    | DMAC_DMAR_OUT_ORDER);	/* was ENH */
E 8
I 8
D 15
	    | (MAXDMA_256 << DMAC_DMAW_MAXDMA_SHIFT)
	    | (MAXDMA_256 << DMAC_DMAR_MAXDMA_SHIFT)
E 15
I 15
	    | MAXDMA_256 << DMAC_DMAW_MAXDMA_SHIFT
	    | MAXDMA_256 << DMAC_DMAR_MAXDMA_SHIFT
E 15
	    | DMAC_DMAR_ENH_ORDER);	/* was OUT_ORDER */
E 8
E 2
	DPRINTF(0, (CE_CONT, "!%s: %s: DMAC:0x%x",
D 3
	    dp->name, __func__, INL(dp, DMAC)));
E 3
I 3
	    dp->name, __func__, INL(dp, DMAC_1)));
E 3

	/* configure ISM / SM */
I 2
D 7
#ifdef CONFIG_POLLING
E 7
I 7
#ifdef CONFIG_ADAPTIVE_COALESCE
E 7
E 2
D 3
	OUTL(dp, ISMTHRESH,
E 3
I 3
	OUTL(dp, ISMTHRESH_1,
E 3
D 15
	    (dp->gc.gc_tx_ring_size << ISMTHRESH_TBD_SHIFT)
E 15
I 15
	    dp->gc.gc_tx_ring_size << ISMTHRESH_TBD_SHIFT
E 15
D 5
	    | (max(dp->poll_pkt_delay, 1)));
E 5
I 5
	    | (max(dp->poll_pkt_delay * 2, 1)));
E 5
I 2
#else
D 3
	OUTL(dp, ISMTHRESH,
E 3
I 3
	OUTL(dp, ISMTHRESH_1,
E 3
D 15
	    (max(dp->gc.gc_tx_ring_size, 4) << ISMTHRESH_TBD_SHIFT) | 4);
E 15
I 15
	    max(dp->gc.gc_tx_ring_size, 4) << ISMTHRESH_TBD_SHIFT | 4);
E 15
#endif
E 2
	DPRINTF(0, (CE_CONT, "!%s: %s: ISMTHRESH:0x%x",
D 3
	    dp->name, __func__, INL(dp, ISMTHRESH)));
E 3
I 3
	    dp->name, __func__, INL(dp, ISMTHRESH_1)));
E 3

	/* ISMDELAY: original ism_tx_timer 2uS, ism_rx_timer 2uS */
D 2
	OUTL(dp, ISMDELAY, (1 << ISMDELAY_TBD_SHIFT) | 50);
E 2
I 2
D 7
#ifdef CONFIG_POLLING
E 7
I 7
#ifdef CONFIG_ADAPTIVE_COALESCE
E 7
D 3
	OUTL(dp, ISMDELAY,
E 3
I 3
	OUTL(dp, ISMDELAY_1,
E 3
D 15
	    (1 << ISMDELAY_TBD_SHIFT) | (max(dp->poll_pkt_delay, 1) * 6));
E 15
I 15
	    1U << ISMDELAY_TBD_SHIFT | (max(dp->poll_pkt_delay, 1) * 6));
E 15
#else
D 3
	OUTL(dp, ISMDELAY, (1 << ISMDELAY_TBD_SHIFT) | 1);
E 3
I 3
D 15
	OUTL(dp, ISMDELAY_1, (1 << ISMDELAY_TBD_SHIFT) | 1);
E 15
I 15
	OUTL(dp, ISMDELAY_1, 1U << ISMDELAY_TBD_SHIFT | 1);
E 15
E 3
#endif
E 2
	DPRINTF(0, (CE_CONT, "!%s: %s: ISMDELAY:0x%x",
D 3
	    dp->name, __func__, INL(dp, ISMDELAY)));
E 3
I 3
	    dp->name, __func__, INL(dp, ISMDELAY_1)));
E 3

D 3
	OUTL(dp, SMDELAY, 200*1000/2);	/* 200mS */
E 3
I 3
	OUTL(dp, SMDELAY_1, 200*1000/2);	/* 200mS */
E 3

	/* enable ISM / SM */
D 3
	OUTL(dp, ISMCTL, ISMCTL_ISM_EN | ISMCTL_SM_EN);
E 3
I 3
	OUTL(dp, ISMCTL_1, ISMCTL_ISM_EN | ISMCTL_SM_EN);
E 3

D 3
	if (INL(dp, ISR) & ISR_PCIE_ERR) {
E 3
I 3
	if (INL(dp, ISR) & ISR_PCIE_ERR_1) {
E 3
		/* pci-e phy linkdown */
		ret = GEM_FAILURE;
	} else {
		ret = GEM_SUCCESS;
	}

	/* clear all interrupt status */
D 7
	OUTL(dp, ISR, 0x3fffffff);
	OUTL(dp, ISR, 0);
E 7
I 7
	OUTL(dp, ISR, lp->isr_clear_all);
E 7

I 3
	/* clear statistics area */
	bzero(dp->io_area + lp->sm_offset, sizeof (uint32_t) * STAT_MAX);

E 3
	return (ret);
}

I 3
static int
atge_init_chip_2(struct gem_dev *dp)
{
	int		i;
	int		ret;
	uint32_t	val;
	uint32_t	hiwat;
	uint32_t	lowat;
D 8
	uint_t		maxpayload;
	uint_t		maxrequest;
E 8
	struct atge_dev	*lp = dp->private;

	DPRINTF(0, (CE_CONT, "!%s: %s: called at time:%d",
	    dp->name, __func__, ddi_get_lbolt()));

	/* clear bogus interrupt status */
D 7
	OUTL(dp, ISR, 0xffffffffU);
E 7
I 7
	OUTL(dp, ISR, lp->isr_disable | lp->isr_clear_all);
E 7

D 7
	/* mac control: do later */
E 7
I 7
	/* mac control: setup later */
E 7
	lp->mac_ctl = MACCTL_CRCEN | MACCTL_AUTOPAD
D 15
	    | (7 << MACCTL_PRMLEN_SHIFT) | MACCTL_FD | MACCTL_SPEED_10_100
E 15
I 15
	    | 7U << MACCTL_PRMLEN_SHIFT | MACCTL_FD | MACCTL_SPEED_10_100
E 15
	    | MACCTL_TXFC | MACCTL_RXFC;
D 7
#if 0
	OUTL(dp, MACCTL, lp->mac_ctl);
#endif
E 7
I 7

E 7
	/* setup various base address */
	OUTL(dp, DESCBASE_2, 0);
	OUTL(dp, TBDADDR_2, dp->io_area_dma + lp->tbd_offset);
	OUTL(dp, TSDADDR_2, dp->tx_ring_dma);
	OUTL(dp, RBDADDR_2, dp->io_area_dma + lp->rbd_offset);

	/* number of descriptors */
	OUTW(dp, TBDLEN_2, lp->tbd_size/4);
	OUTW(dp, TSDCNT_2, dp->gc.gc_tx_ring_size);
	OUTW(dp, RBDCNT_2, dp->gc.gc_rx_ring_size);

	/* interpacket gap and interframe gap */
	OUTL(dp, GAPC, GAPC_STD);
	DPRINTF(0, (CE_CONT, "!%s: %s: GAPC:0x%x",
	    dp->name, __func__, INL(dp, GAPC)));

	/* half duplex control register */
	OUTL(dp, HDCTL, HDCTL_STD);
	DPRINTF(0, (CE_CONT, "!%s: %s: HDCTL:0x%x",
	    dp->name, __func__, INL(dp, HDCTL)));

	/* Interrupt Delay */
D 7
#ifdef CONFIG_POLLING
E 7
I 7
#ifdef CONFIG_ADAPTIVE_COALESCE
E 7
	val = 1;	/* 2uS */
	lp->last_poll_interval = 0;
#else
	val = 200/2;	/* original: 200uS */
#endif
	OUTW(dp, INTRDELAY_INIT, val);
	DPRINTF(0, (CE_CONT, "!%s: %s: INTRDELAY_INIT:0x%x",
	    dp->name, __func__, INW(dp, INTRDELAY_INIT)));

	OUTL(dp, MSTC, MSTC_ITIMER);

	/* Interrupt Clear Timer */
	OUTW(dp, INTRCLR_TIMER, 100*1000/2);	/* original: 100mS in 2uS */
	DPRINTF(0, (CE_CONT, "!%s: %s: INTRCLR_TIMER:0x%x",
	    dp->name, __func__, INW(dp, INTRCLR_TIMER)));

	/* MTU */
	OUTL(dp, MTU,
	    sizeof (struct ether_header) + dp->mtu + ETHERFCSL + VTAG_SIZE);
	DPRINTF(0, (CE_CONT, "!%s: %s: MTU: 0x%x",
	    dp->name, __func__, INL(dp, MTU)));

	OUTL(dp, TXTHRESH_2, 0x177);

	/* flow control */
	OUTW(dp, RXHIWAT_2, dp->gc.gc_rx_ring_size * 7 / 8);
	OUTW(dp, RXLOWAT_2, min(dp->gc.gc_rx_ring_size / 12, 16/8));

	/* mailbox */
	lp->tx_buffer_tail = 0;
	lp->rx_buffer_head = 0;
	OUTW(dp, TBDTAIL_2, 0);
	OUTW(dp, RBDTAIL_2, 0);

	/* dma control */
	OUTB(dp, DMAR_2, 1);
	OUTB(dp, DMAW_2, 1);

	if (INL(dp, ISR) & ISR_PCIE_ERR_2) {
		/* pci-e phy linkdown */
		ret = GEM_FAILURE;
	} else {
		ret = GEM_SUCCESS;
	}

	/* clear all interrupt status */
D 7
	OUTL(dp, ISR, 0x3fffffff);
	OUTL(dp, ISR, 0);
E 7
I 7
	OUTL(dp, ISR, lp->isr_clear_all);
E 7

	return (ret);
}

static int
atge_init_chip_1e(struct gem_dev *dp)
{
	int		i;
	int		q;
	int		ret;
	uint32_t	val;
	uint32_t	imt;
	uint32_t	hiwat;
	uint32_t	lowat;
D 8
	uint_t		maxpayload;
	uint_t		maxrequest;
E 8
	struct atge_dev	*lp = dp->private;

	DPRINTF(0, (CE_CONT, "!%s: %s: called at time:%d",
	    dp->name, __func__, ddi_get_lbolt()));

	/* clear bogus interrupt status */
D 7
	OUTL(dp, ISR, 0xffffffffU);
E 7
I 7
	OUTL(dp, ISR, lp->isr_disable | lp->isr_clear_all);
E 7

	/* mac control: do later */
	lp->mac_ctl = MACCTL_CRCEN | MACCTL_AUTOPAD
D 15
	    | (7 << MACCTL_PRMLEN_SHIFT) | MACCTL_FD | MACCTL_SPEED_10_100
E 15
I 15
	    | 7U << MACCTL_PRMLEN_SHIFT | MACCTL_FD | MACCTL_SPEED_10_100
E 15
	    | MACCTL_TXFC | MACCTL_RXFC;
D 6
#ifdef notdef
	OUTL(dp, MACCTL, lp->mac_ctl);
#endif
E 6
I 6

E 6
	/* setup various base address */
	OUTL(dp, DESCBASE_1e, 0);
	OUTL(dp, TBDADDR_1e, dp->io_area_dma + lp->tbd_offset);
	OUTL(dp, TBD_CNT_1e, dp->gc.gc_tx_ring_size);
	OUTL(dp, TBD_TAIL_PTR_1e, dp->io_area_dma + lp->tbd_tail_offset);

	OUTL(dp, RXF0_RING_BASE_1e + 0, dp->io_area_dma + lp->rxf_offset[0][0]);
	OUTL(dp, RXF0_RING_BASE_1e + 4, dp->io_area_dma + lp->rxf_offset[0][1]);
	OUTL(dp, RXF_RING_MB_1e + 0, dp->io_area_dma + lp->rxf_mb_offset[0][0]);
	OUTL(dp, RXF_RING_MB_1e + 4, dp->io_area_dma + lp->rxf_mb_offset[0][1]);
	OUTB(dp, RXF_RING_VALID_1e + 0, 1);
	OUTB(dp, RXF_RING_VALID_1e + 1, 1);
	OUTB(dp, RXF_RING_VALID_1e + 2, 0);
	OUTB(dp, RXF_RING_VALID_1e + 3, 0);
	OUTB(dp, RXF_RING_VALID_1e + 4, 0);
	OUTB(dp, RXF_RING_VALID_1e + 5, 0);
	OUTB(dp, RXF_RING_VALID_1e + 6, 0);
	OUTB(dp, RXF_RING_VALID_1e + 7, 0);

	OUTL(dp, RXF_RING_HIWAT_1e, lp->rxf_buf_hiwat);

	/* load the descriptor configuration */
	OUTL(dp, DESCEN_1e, 1);

	/* Interrupt Delay */
D 6
#ifdef CONFIG_POLLING
E 6
I 6
D 7
#if 1 /*  CONFIG_POLLING */
E 7
I 7
#ifdef CONFIG_ADAPTIVE_COALESCE
E 7
E 6
	imt = 1;	/* 2uS */
#else
	imt = 200/2;	/* original: 200uS */
#endif
D 6
	OUTW(dp, INTRDELAY_INIT, imt);
E 6
I 6
	OUTW(dp, INTRDELAY_INIT, imt);	/* worked only for tx_pkt */
E 6
	DPRINTF(0, (CE_CONT, "!%s: %s: INTRDELAY_INIT:0x%x",
	    dp->name, __func__, INW(dp, INTRDELAY_INIT)));
D 6
	OUTW(dp, INTRDELAY2_INIT, imt);
E 6
I 6
D 7
	OUTW(dp, INTRDELAY2_INIT, imt);	/* workded only for rx_pkt*/
E 7
I 7
	OUTW(dp, INTRDELAY2_INIT, imt);	/* workded only for rx_pkt */
E 7
E 6
	DPRINTF(0, (CE_CONT, "!%s: %s: INTRDELAY2_INIT:0x%x",
	    dp->name, __func__, INW(dp, INTRDELAY2_INIT)));

D 7
	OUTL(dp, MSTC, MSTC_LEDMODE | MSTC_ITIMER | MSTC_ITIMER2);
E 7
I 7
	OUTL(dp, MSTC,
	    MSTC_LEDMODE_1e | MSTC_ITIMER_TX_1e | MSTC_ITIMER_RX_1e);
E 7
	DPRINTF(0, (CE_CONT, "!%s: %s: MSTC:0x%x",
	    dp->name, __func__, INL(dp, MSTC)));

	/* inter packet gap and inter frame gap */
D 7
#ifdef notdef
E 7
I 7
#ifdef NEVER
E 7
	OUTL(dp, GAPC, GAPC_STD);	/* use default */
#endif
	DPRINTF(0, (CE_CONT, "!%s: %s: GAPC:0x%x",
	    dp->name, __func__, INL(dp, GAPC)));

	/* half duplex control register */
	OUTL(dp, HDCTL, HDCTL_STD);
	DPRINTF(0, (CE_CONT, "!%s: %s: HDCTL:0x%x",
	    dp->name, __func__, INL(dp, HDCTL)));
D 6

	OUTW(dp, RX_COALSC_PKT_1e, 1);
E 6
I 6
D 7
#if 0
E 7
I 7
#ifdef CONFIG_ADAPTIVE_COALESCE
	OUTW(dp, RX_COALSC_PKT_1e, 1);	/* didn't work */
	OUTW(dp, RX_COALSC_TO_1e, 1);	/* didn't work */
	OUTW(dp, TX_COALSC_PKT_1e, dp->gc.gc_tx_ring_size/8); /* in descs */
	OUTW(dp, TX_COALSC_TO_1e, 0xffff);	/* no timeout */
#else
E 7
	/* original parameters */
	OUTW(dp, RX_COALSC_PKT_1e, max(1, dp->poll_pkt_delay));
	OUTW(dp, RX_COALSC_TO_1e, 4);
E 6
	OUTW(dp, TX_COALSC_PKT_1e, dp->gc.gc_tx_ring_size/16);
D 6
	OUTW(dp, RX_COALSC_TO_1e, 4);	/* 10uS */
E 6
	OUTW(dp, TX_COALSC_TO_1e, imt*4/3);
D 6

E 6
I 6
D 7
#else
	OUTW(dp, RX_COALSC_PKT_1e, 0);
	OUTW(dp, RX_COALSC_TO_1e, 0);
	OUTW(dp, TX_COALSC_PKT_1e, dp->gc.gc_tx_ring_size/8);
	OUTW(dp, TX_COALSC_TO_1e, 4000/2);	/* 4mS */
E 7
#endif
E 6
	/* Interrupt Clear Timer */
D 6
	OUTW(dp, INTRCLR_TIMER, 20*1000/2); /* original: 20mS in 2uS */
E 6
I 6
	OUTW(dp, INTRCLR_TIMER, 100*1000/2); /* original: 100mS in 2uS */
E 6

	DPRINTF(0, (CE_CONT, "!%s: %s: INTRCLR_TIMER:0x%x",
	    dp->name, __func__, INW(dp, INTRCLR_TIMER)));

	/* MTU */
	OUTL(dp, MTU,
	    sizeof (struct ether_header) + dp->mtu + ETHERFCSL + VTAG_SIZE);
	DPRINTF(0, (CE_CONT, "!%s: %s: MTU: 0x%x",
	    dp->name, __func__, INL(dp, MTU)));

	if (lp->chip != CHIP_L2E_B) {
		val = dp->mtu + sizeof (struct ether_header) + ETHERFCSL + 4;
		if (dp->mtu <= 1500) {
			/* store and forward */
			/* EMPTY */
		} else if (dp->mtu < 6*1024) {
			val = val * 2 / 3;
		} else {
			val = val / 2;
		}
		OUTW(dp, TXJCFG_1e, ROUNDUP(val, 8) / 8);
	}
D 8
	/* TXQCTL: */
	val = INL(dp, PCIE_DEVCTRL);
	maxpayload = (val >> 5) & 7;
	maxrequest = (val >> 12) & 7;
	DPRINTF(0, (CE_CONT,
	    "!%s: %s: PCIE DEVCTRL:0x%x (payload:%d request:%d)",
	    dp->name, __func__, val, maxpayload, maxrequest));
E 8

I 8
	/* TXQCTL: */
E 8
	if (lp->chip != CHIP_L2E_B) {
D 8
		OUTW(dp, TXQCTL_1e + 2, 128 << maxrequest);
E 8
I 8
D 15
		OUTW(dp, TXQCTL_1e + 2, 128 << lp->maxrequest);
E 15
I 15
		OUTW(dp, TXQCTL_1e + 2, 128U << lp->maxrequest);
E 15
E 8
	}

	OUTW(dp, TXQCTL_1e,
	    TXQCTL_EN
	    | TXQCTL_ENH_MODE
D 15
	    | (5 << TXQCTL_TBD_BURST_NUM_SHIFT));
E 15
I 15
	    | 5U << TXQCTL_TBD_BURST_NUM_SHIFT);
E 15
	DPRINTF(0, (CE_CONT, "!%s: %s: TXQCTL:0x%x",
	    dp->name, __func__, INL(dp, TXQCTL_1e)));

	/*
	 * configure RXQ
	 */
	if (lp->chip != CHIP_L2E_B) {
		/* Rx jumbo packet configuration */
		OUTW(dp, RXJCFG_1e,
D 15
		    (1 << RXJCFG_LKAH_SHIFT) | (dp->rx_buf_len / 8));
E 15
I 15
		    1U << RXJCFG_LKAH_SHIFT | (dp->rx_buf_len / 8));
E 15

		DPRINTF(0, (CE_CONT, "!%s: %s: RXJCFG: 0x%x",
		    dp->name, __func__, INL(dp, RXJCFG_1e)));

		/* flow control */
		val = INL(dp, RAM_RXF_SIZE_1e);
		hiwat = val * 4 / 5;
		lowat = val / 5;
D 15
		OUTL(dp, RXFFC_1e, (hiwat << RXFFC_HIWAT_SHIFT) | lowat);
E 15
I 15
		OUTL(dp, RXFFC_1e, hiwat << RXFFC_HIWAT_SHIFT | lowat);
E 15
	}
	/* RSS: */
	OUTL(dp, IDT_TABLE0_1e, 0);
	OUTL(dp, BASE_CPU_NUM_1e, 0);

	/* RXQCTL: */
	OUTL(dp, RXQCTL_1e,
	    RXQCTL_EN
	    | RXQCTL_CUT_THRU_EN
	    | RXQCTL_IPV6_CKSUM_EN
	    | RXQCTL_PBA_ALIGN_32);
	DPRINTF(0, (CE_CONT, "!%s: %s: RXQCTL: 0x%x",
	    dp->name, __func__, INL(dp, RXQCTL_1e)));

	/* DMA control */
	OUTL(dp, DMAC_1e,
	    DMAC_RXCMB_1e /* | DMAC_TXCMB_1e */
D 15
	    | (4 << DMAC_DMAW_DLY_CNT_SHIFT)
	    | (15 << DMAC_DMAR_DLY_CNT_SHIFT)
E 15
I 15
	    | 4U << DMAC_DMAW_DLY_CNT_SHIFT
	    | 15U << DMAC_DMAR_DLY_CNT_SHIFT
E 15
D 8
	    | DMAC_DMAR_REQ_PRI_1e
	    | (min(MAXDMA_1024, maxpayload) << DMAC_DMAW_MAXDMA_SHIFT)
	    | (min(MAXDMA_1024, maxrequest) << DMAC_DMAR_MAXDMA_SHIFT)
E 8
I 8
	    | DMAC_DMAR_REQ_PRI
D 15
	    | (lp->maxpayload << DMAC_DMAW_MAXDMA_SHIFT)
	    | (lp->maxrequest << DMAC_DMAR_MAXDMA_SHIFT)
E 15
I 15
	    | lp->maxpayload << DMAC_DMAW_MAXDMA_SHIFT
	    | lp->maxrequest << DMAC_DMAR_MAXDMA_SHIFT
E 15
E 8
	    | DMAC_DMAR_OUT_ORDER);
	DPRINTF(0, (CE_CONT, "!%s: %s: DMAC:0x%x",
	    dp->name, __func__, INL(dp, DMAC_1e)));

	/* statistics messages */
D 6
	OUTL(dp, SM_TIMER_1e, 100000/2);
E 6
I 6
D 8
	OUTL(dp, SM_TIMER_1e, 200000);	/* 200mS */
E 8
I 8
	OUTL(dp, SM_TIMER_1e, 200000);	/* 400mS */
E 8
E 6

	if (INL(dp, ISR) & ISR_PCIE_ERR_1e) {
		/* pci-e phy linkdown */
		ret = GEM_FAILURE;
	} else {
		ret = GEM_SUCCESS;
	}

	/* clear all interrupt status */
D 7
	OUTL(dp, ISR, 0x7fffffff);
	OUTL(dp, ISR, 0);
E 7
I 7
	OUTL(dp, ISR, lp->isr_clear_all);
E 7

	for (q = 0; q < 4; q++) {
		lp->rxf[q].rf_head = 0;
		lp->rxf[q].rf_tail = 0;
		lp->rxf[q].rf_curr_ring = 0;
		lp->rxf[q].rf_seqnum = 0;
		for (i = 0; i < 2; i++) {
			*((uint32_t *)(dp->io_area +
			    lp->rxf_mb_offset[q][i])) = 0;
		}
	}

	/* clear statistics area */
	bzero(dp->io_area + lp->sm_offset, sizeof (uint32_t) * STAT_MAX);
I 6
	atge_ioarea_dma_sync(dp, lp->sm_offset,
	    (size_t)(sizeof (uint32_t) * STAT_MAX), DDI_DMA_SYNC_FORDEV);
E 6

	return (ret);
}

I 7
D 10
#ifdef CONFIG_1C
E 10
static int
atge_init_chip_1c(struct gem_dev *dp)
{
	int		i;
	uint32_t	val;
	uint32_t	rx_delay;
	uint32_t	tx_delay;
	uint32_t	hiwat;
	uint32_t	lowat;
	uint64_t	addr;
D 8
	uint_t		maxpayload;
	uint_t		maxrequest;
E 8
	struct atge_dev	*lp = dp->private;

	DPRINTF(0, (CE_CONT, "!%s: %s: called at time:%d",
	    dp->name, __func__, ddi_get_lbolt()));

	/* clear bogus interrupt status */
D 8
	OUTL(dp, ISR, lp->isr_disable | lp->isr_clear_all);	/* ok */
E 8
I 8
D 15
	OUTL(dp, ISR, lp->isr_disable | lp->isr_clear_all);
E 15
I 15
	OUTL(dp, ISR, lp->isr_disable | lp->isr_clear_all);	/* ok */
E 15
E 8

	/* clear wol status */
D 8
	OUTL(dp, WOLCTL, 0);	/* ok */
E 8
I 8
D 15
	OUTL(dp, WOLCTL, 0);
E 15
I 15
	OUTL(dp, WOLCTL, 0);	/* ok */
E 15
E 8

I 8
	/* clock gating */
D 15
	OUTL(dp, CLK_GATING_1c, 0);
E 15
I 15
	OUTL(dp, CLK_GATING_1c, 0);	/* ok */
E 15

E 8
	/* interrupt clear timer */
D 8
	OUTL(dp, INTRCLR_TIMER_lc, 100*1000/2); /* original: 100mS in 2uS ok */
E 8
I 8
D 15
	OUTL(dp, INTRCLR_TIMER_lc, 0); /* original: 100mS in 2uS ok */
E 15
I 15
	OUTL(dp, INTRCLR_TIMER_lc, 0); /* original: 100mS in 2uS */ /* ok */
E 15
E 8
	DPRINTF(0, (CE_CONT, "!%s: %s: INTRCLR_TIMER:0x%x",
	    dp->name, __func__, INL(dp, INTRCLR_TIMER_lc)));

	/*
	 * setup various base address
	 */
	/* the base address of tx descriptor array */
	ASSERT(((dp->io_area_dma + lp->tbd_offset) >> 32) == 0);
D 8
	OUTL(dp, TX_BASE_HI_1c, 0);	/* ok */
	OUTL(dp, NTPD_HEAD_LO_1c, dp->io_area_dma + lp->tbd_offset);	/* ok */
	OUTL(dp, HTPD_HEAD_LO_1c, 0);	/* ok */
E 8
I 8
D 15
	OUTL(dp, TX_BASE_HI_1c, 0);
	OUTL(dp, NTPD_HEAD_LO_1c, dp->io_area_dma + lp->tbd_offset);
	OUTL(dp, HTPD_HEAD_LO_1c, 0);
E 15
I 15
	OUTL(dp, TX_BASE_HI_1c, 0);	/* ok */
	OUTL(dp, NTPD_HEAD_LO_1c, dp->io_area_dma + lp->tbd_offset);	/* ok */
	OUTL(dp, HTPD_HEAD_LO_1c, 0);	/* ok */
E 15
E 8

D 8
	OUTL(dp, TPD_RING_SIZE_1c, dp->gc.gc_tx_ring_size);	/* ok */
E 8
I 8
D 15
	OUTL(dp, TPD_RING_SIZE_1c, dp->gc.gc_tx_ring_size);
E 15
I 15
	OUTL(dp, TPD_RING_SIZE_1c, dp->gc.gc_tx_ring_size);	/* ok */
E 15
E 8

	/* the base address of rx descriptor array */
	ASSERT((dp->io_area_dma + lp->rbd_offset) >> 32 == 0);
D 15
	OUTL(dp, RX_BASE_HI_1c, 0);
	OUTL(dp, RFD_HEAD_LO_1c + 0*4, dp->io_area_dma + lp->rbd_offset);
E 15
I 15
	OUTL(dp, RX_BASE_HI_1c, 0);	/* ok */
	OUTL(dp, RFD_HEAD_LO_1c + 0*4, dp->io_area_dma + lp->rbd_offset); /* ok */
#if 0
E 15
	OUTL(dp, RFD_HEAD_LO_1c + 1*4, 0);
	OUTL(dp, RFD_HEAD_LO_1c + 2*4, 0);
	OUTL(dp, RFD_HEAD_LO_1c + 3*4, 0);
I 15
#endif
	OUTL(dp, RFD_RING_SIZE_1c, dp->gc.gc_rx_ring_size);	/* ok */
E 15

D 8
	OUTL(dp, RFD_RING_SIZE_1c, dp->gc.gc_rx_ring_size);	/* ok */
E 8
I 8
D 15
	OUTL(dp, RFD_RING_SIZE_1c, dp->gc.gc_rx_ring_size);
E 8

D 8
	OUTL(dp, RX_BUF_SIZE_1c, dp->rx_buf_len);	/* ok */
E 8
I 8
	OUTL(dp, RX_BUF_SIZE_1c, dp->rx_buf_len);
E 15
I 15
	OUTL(dp, RX_BUF_SIZE_1c, dp->rx_buf_len);	/* ok */
E 15
E 8
	DPRINTF(0, (CE_CONT, "!%s: %s: RX_BUF_SIZE: 0x%x",
	    dp->name, __func__, INL(dp, RX_BUF_SIZE_1c)));

D 8
	OUTL(dp, RRD_HEAD_LO_1c + 0*4, dp->rx_ring_dma);	/* ok */
E 8
I 8
D 15
	OUTL(dp, RRD_HEAD_LO_1c + 0*4, dp->rx_ring_dma);
E 15
I 15
	OUTL(dp, RRD_HEAD_LO_1c + 0*4, dp->rx_ring_dma);	/* ok */
#if 0
E 15
E 8
	OUTL(dp, RRD_HEAD_LO_1c + 1*4, 0);
	OUTL(dp, RRD_HEAD_LO_1c + 2*4, 0);
	OUTL(dp, RRD_HEAD_LO_1c + 3*4, 0);
D 15

E 15
I 15
#endif
E 15
D 8
	OUTL(dp, RRD_RING_SIZE_1c, dp->gc.gc_rx_ring_size);	/* ok */
E 8
I 8
	OUTL(dp, RRD_RING_SIZE_1c, dp->gc.gc_rx_ring_size);
E 8
D 15

E 15
I 15
#if 0
E 15
	/* the base address of interrupt massage */
	ASSERT((dp->io_area_dma + lp->ism_offset) >> 32 == 0);
D 8
	OUTL(dp, CMB_BASE_LO_1c, dp->io_area_dma + lp->ism_offset);	/* ok */
E 8
I 8
	OUTL(dp, CMB_BASE_LO_1c, dp->io_area_dma + lp->ism_offset);
E 8

	/* the base address of statistics area */
	addr = dp->io_area_dma + lp->sm_offset;
D 8
	OUTL(dp, SMB_BASE_HI_1c, addr >> 32);	/* ok */
	OUTL(dp, SMB_BASE_LO_1c, addr);	/* ok */
E 8
I 8
	OUTL(dp, SMB_BASE_HI_1c, addr >> 32);
	OUTL(dp, SMB_BASE_LO_1c, addr);
E 8
D 15

E 15
I 15
#endif
E 15
I 8
	/* sram setting for L2C_B */
	if (lp->chip == CHIP_L2C_B) {
D 15
		OUTL(dp, SRAM_RXF_LEN_1c, 0x000002a0U);
		OUTL(dp, SRAM_TXF_LEN_1c, 0x00000100U);
		OUTL(dp, SRAM_RXF_ADDR_1c, 0x029f0000U);
		OUTL(dp, SRAM_RFD0_INFO_1c, 0x02bf02a0U);
		OUTL(dp, SRAM_TXF_ADDR_1c, 0x03bf02c0U);
		OUTL(dp, SRAM_TRD_ADDR_1c, 0x03df03c0U);
E 15
I 15
		OUTL(dp, SRAM_RXF_LEN_1c, 0x000002a0U);		/* ok */
		OUTL(dp, SRAM_TXF_LEN_1c, 0x00000100U);		/* ok */
		OUTL(dp, SRAM_RXF_ADDR_1c, 0x029f0000U);	/* ok */
		OUTL(dp, SRAM_RFD0_INFO_1c, 0x02bf02a0U);	/* ok */
		OUTL(dp, SRAM_TXF_ADDR_1c, 0x03bf02c0U);	/* ok */
		OUTL(dp, SRAM_TRD_ADDR_1c, 0x03df03c0U);	/* ok */
E 15

D 11
		/* TX watermark, to enter l1 state.*/
E 11
I 11
		/* TX watermark, to enter l1 state. */
E 11
D 15
		OUTL(dp, TXF_WATER_MARK_1c, 0);
E 15
I 15
		OUTL(dp, TXF_WATER_MARK_1c, 0);		/* ok */
E 15

		/* RXD threshold */
D 15
		OUTL(dp, RXD_DMAC_1c, 0);
E 15
I 15
		OUTL(dp, RXD_DMAC_1c, 0);		/* ok */
E 15
	}

D 15
	/* power saving setting for L2C_B ans L1D_2 */
	if (lp->chip == CHIP_L2C_B || lp->chip == CHIP_L1D_2_0) {
E 15
I 15
	/* load the descriptor configuration */
	OUTL(dp, DESCEN_1c, 1);		/* ok */

#if 0
	/* clock switch setting for L2C_B, L2CB2 and L1D_2 */
	switch (lp->chip) {
	case CHIP_L2C_B:
E 15
		val = INL(dp, SERDES_LOCK);
I 15
		val &= ~SERDES_MAC_CLK_SLOWDOWN;
		val &= ~SERDES_PYH_CLK_SLOWDOWN;
		OUTL(dp, SERDES_LOCK, val);		/* ok */
		break;

	case CHIP_L2C_B2:
	case CHIP_L1D_2_0:
		val = INL(dp, SERDES_LOCK);
E 15
		val |= SERDES_MAC_CLK_SLOWDOWN;
		val |= SERDES_PYH_CLK_SLOWDOWN;
D 15
		OUTL(dp, SERDES_LOCK, val);
E 15
I 15
		OUTL(dp, SERDES_LOCK, val);		/* ok */
		break;
E 15
	}
I 15
#endif
	/* Interrupt Delay */
	val = 0;
#ifdef CONFIG_INTR_RDCLR
	/* XXX - don't use CONFIG_INTR_RDCLR, it hangs the system */
	val |= MSTC_INT_RDCLR_1c;
	lp->intr_rdclr = B_TRUE;
#else
	lp->intr_rdclr = B_FALSE;
#endif
#ifdef CONFIG_ADAPTIVE_COALESCE
	rx_delay = 1;		/* original: 400uS */
	tx_delay = 1;		/* original: 2mS */
#else
	rx_delay = 400/2;	/* original: 400uS */
	tx_delay = 2000/2;	/* original: 2mS */
#endif
	val |= MSTC_TX_ITIMER_EN_1c | MSTC_RX_ITIMER_EN_1c;
E 15

E 8
D 15
	/* load the descriptor configuration */
D 8
	OUTL(dp, DESCEN_1c, 1);	/* ok */
E 8
I 8
	OUTL(dp, DESCEN_1c, 1);
E 15
I 15
	OUTL(dp, INTRDELAY_INIT, rx_delay << 16 | tx_delay);
	DPRINTF(0, (CE_CONT, "!%s: %s: INTRDELAY_INIT:0x%x",
	    dp->name, __func__, INL(dp, INTRDELAY_INIT)));
E 15
E 8

I 8
D 15
	OUTL(dp, TSO_THRESH_1c, (9*1024) >> 3);
E 15
I 15
	/* master control */
	OUTL(dp, MSTC, val);
	DPRINTF(0, (CE_CONT, "!%s: %s: MSTC:0x%x",
	    dp->name, __func__, INL(dp, MSTC)));
E 15

I 15

	/* MTU */
	OUTL(dp, MTU,
	    sizeof (struct ether_header) + dp->mtu + ETHERFCSL + VTAG_SIZE);
	DPRINTF(0, (CE_CONT, "!%s: %s: MTU: 0x%x",
	    dp->name, __func__, INL(dp, MTU)));

	/*
	 * configure tx
	 */
	OUTL(dp, TSO_THRESH_1c, (7*1024) >> 3);

E 15
	/* TXQCTL: */
	switch (lp->chip) {
	case CHIP_L2C_B:
	case CHIP_L2C_B2:
D 15
		val = (128 << lp->maxrequest) / 2;
E 15
I 15
		val = (128U << lp->maxrequest) / 2;
E 15
		break;

	default:
D 15
		val = 128 << lp->maxrequest;
E 15
I 15
		val = 128U << lp->maxrequest;
E 15
		break;
	}
	OUTL(dp, TXQCTL_1c,
D 15
	    (val << TXQCTL_TXF_BURST_NUM_SHIFT)
E 15
I 15
	    val << TXQCTL_TXF_BURST_NUM_SHIFT
#if 0
	    | TXQCTL_EN
#endif
E 15
	    | TXQCTL_ENH_MODE
D 15
	    | (5 << TXQCTL_NUM_TPD_BURST_SHIFT));
E 15
I 15
	    | 5U << TXQCTL_NUM_TPD_BURST_SHIFT);
E 15
	DPRINTF(0, (CE_CONT, "!%s: %s: TXQCTL:0x%x",
	    dp->name, __func__, INL(dp, TXQCTL_1c)));


I 15
	/*
	 * configure rx
	 */
E 15
	/* RXQCTL: */
	OUTL(dp, RXQCTL_1c,
D 15
	    (8 << RXQCTL_RFD_BURST_NUM_SHIFT)
E 15
I 15
	    8U << RXQCTL_RFD_BURST_NUM_SHIFT
#if 0
	    | RXQCTL_EN
#endif
E 15
	    | RXQCTL_IPV6_CKSUM_EN);
	DPRINTF(0, (CE_CONT, "!%s: %s: RXQCTL: 0x%x",
	    dp->name, __func__, INL(dp, RXQCTL_1c)));

D 15

E 15
I 15
#ifdef NEVER
E 15
	/* RSS */
	OUTL(dp, IDT_TABLE0_1c, 0xe4e4e4e4);
	OUTL(dp, BASE_CPU_NUM_1c, 0);
D 15

E 15
I 15
#endif
E 15
	/* RXJCFG */
	DPRINTF(0, (CE_CONT, "!%s: %s: RXJCFG: 0x%x",
	    dp->name, __func__, INL(dp, RXJCFG_1e)));

	/* RXFFC */
	DPRINTF(0, (CE_CONT, "!%s: %s: RXFFC: 0x%x",
	    dp->name, __func__, INL(dp, RXFFC_1e)));

E 8
D 15
	/* Interrupt Delay */
D 8
	val = MSTC_INT_RDCLR;
#ifndef CONFIG_ADAPTIVE_COALESCE_1C
E 8
I 8
	val = 0;
D 10
#ifdef CONFIG_ADAPTIVE_COALESCE_1C
	/* XXX - notyet implemented */
E 10
I 10
#ifdef CONFIG_INTR_RDCLR
	/* XXX - don't use CONFIG_INTR_RDCLR, it hangs the system */
	val |= MSTC_INT_RDCLR_1c;
	lp->intr_rdclr = B_TRUE;
E 10
#else
I 10
	lp->intr_rdclr = B_FALSE;
#endif
#ifdef CONFIG_ADAPTIVE_COALESCE
	rx_delay = 1;		/* original: 400uS */
	tx_delay = 1;		/* original: 2mS */
#else
E 10
E 8
	rx_delay = 400/2;	/* original: 400uS */
	tx_delay = 2000/2;	/* original: 2mS */
D 8
	val |= MSTC_RX_ITIMER_EN | MSTC_INT_RDCLR;
E 8
I 8
D 10
	val |= MSTC_TX_ITIMER_EN | MSTC_RX_ITIMER_EN;
E 10
I 10
#endif
	val |= MSTC_TX_ITIMER_EN_1c | MSTC_RX_ITIMER_EN_1c;
E 10
E 8

	OUTL(dp, INTRDELAY_INIT, (rx_delay << 16) | tx_delay);
	DPRINTF(0, (CE_CONT, "!%s: %s: INTRDELAY_INIT:0x%x",
	    dp->name, __func__, INL(dp, INTRDELAY_INIT)));
D 10
#endif
E 10
I 10

E 10
	/* master control */
D 8
	OUTL(dp, MSTC, val);	/* ok */
E 8
I 8
	OUTL(dp, MSTC, val);
	DPRINTF(0, (CE_CONT, "!%s: %s: MSTC:0x%x",
	    dp->name, __func__, INL(dp, MSTC)));
E 8

E 15
	/* mac control: do later */
D 15
	lp->mac_ctl = MACCTL_CRCEN | MACCTL_AUTOPAD
	    | (7 << MACCTL_PRMLEN_SHIFT) | MACCTL_FD | MACCTL_SPEED_10_100
	    | MACCTL_TXFC | MACCTL_RXFC | MACCTL_SINGLE_PAUSE;
E 15
I 15
	lp->mac_ctl = INL(dp, MACCTL)
	    | MACCTL_CRCEN | MACCTL_AUTOPAD
	    | 7U << MACCTL_PRMLEN_SHIFT | MACCTL_FD | MACCTL_SPEED_10_100
	    | MACCTL_TXFC | MACCTL_RXFC | MACCTL_SINGLE_PAUSE
	    | MACCTL_HASH_ALG_CRC32;
E 15

D 15
	switch (lp->chip) {
	case CHIP_L2C_B2:
	case CHIP_L1D:
I 8
	case CHIP_L1D_2_0:
E 8
		lp->mac_ctl |= MACCTL_SPEED_MODE_SW | MACCTL_HASH_ALG_CRC32;
		break;
	}

E 15
	/* mailbox */
	lp->tx_buffer_tail = 0;
I 10
#ifdef NEVER
E 10
	lp->rx_status_head = 0;
	lp->rx_status_tail = 0;
	lp->rx_buffer_tail = 0;
I 10
#endif
E 10
D 15

D 8
	/* MTU */	/* ok */
E 8
I 8
	/* MTU */
E 8
	OUTL(dp, MTU,
	    sizeof (struct ether_header) + dp->mtu + ETHERFCSL + VTAG_SIZE);
	DPRINTF(0, (CE_CONT, "!%s: %s: MTU: 0x%x",
	    dp->name, __func__, INL(dp, MTU)));

E 15
I 15
#ifdef NEVER
E 15
	/* HDS */
D 8
	OUTL(dp, HDS_CTL_1c, 0);	/* ok */
E 8
I 8
	OUTL(dp, HDS_CTL_1c, 0);
E 8
	DPRINTF(0, (CE_CONT, "!%s: %s: HDS_CTL: 0x%x",
	    dp->name, __func__, INL(dp, HDS_CTL_1c)));
D 15

E 15
I 15
#endif
E 15
D 8
	val = INL(dp, PCIE_DEVCTRL);
	maxpayload = (val >> 5) & 7;
	maxrequest = (val >> 12) & 7;
	DPRINTF(0, (CE_CONT,
	    "!%s: %s: PCIE DEVCTRL:0x%x (payload:%d request:%d)",
	    dp->name, __func__, val, maxpayload, maxrequest));
E 8
I 8
	/* GAPC */
	DPRINTF(0, (CE_CONT, "!%s: %s: GAPC:0x%x",
	    dp->name, __func__, INL(dp, GAPC)));
E 8

D 8
	/* TXQCTL: */
	OUTL(dp, TSO_THRESH_1c, (9*1024) >> 3);	/* ok */
	OUTL(dp, TXQCTL_1c,
	    ((128 << min(maxrequest, MAXDMA_1024))
	    << TXQCTL_TXF_BURST_NUM_SHIFT)
	    | TXQCTL_ENH_MODE
	    | (5 << TXQCTL_NUM_TPD_BURST_SHIFT));	/* ok */
	DPRINTF(0, (CE_CONT, "!%s: %s: TXQCTL:0x%x",
	    dp->name, __func__, INL(dp, TXQCTL_1c)));
E 8
I 8
D 15
	/* half duplex control register */
	DPRINTF(0, (CE_CONT, "!%s: %s: HDCTL:0x%x",
	    dp->name, __func__, INL(dp, HDCTL)));
E 8

E 15
D 8
	/* RXQCTL: */
	/* rss is not implemented */
	OUTL(dp, RXQCTL_1c,
	    (8 << RXQCTL_RFD_BURST_NUM_SHIFT)
	    | RXQCTL_IPV6_CKSUM_EN);
	DPRINTF(0, (CE_CONT, "!%s: %s: RXQCTL: 0x%x",
	    dp->name, __func__, INL(dp, RXQCTL_1c)));

E 8
	/* DMA control */
	OUTL(dp, DMAC_1c,
	    DMAC_SMB_DIS_1c
D 15
	    | (4 << DMAC_DMAW_DLY_CNT_SHIFT)
	    | (15 << DMAC_DMAR_DLY_CNT_SHIFT)
E 15
I 15
	    | 4U << DMAC_DMAW_DLY_CNT_SHIFT
	    | 15U << DMAC_DMAR_DLY_CNT_SHIFT
E 15
D 8
	    | DMAC_DMAR_REQ_PRI_1c
	    | (min(MAXDMA_1024, maxpayload) << DMAC_DMAW_MAXDMA_SHIFT)
	    | (min(MAXDMA_1024, maxrequest) << DMAC_DMAR_MAXDMA_SHIFT)
E 8
I 8
	    | DMAC_DMAR_REQ_PRI
D 15
	    | (lp->maxpayload << DMAC_DMAW_MAXDMA_SHIFT)
	    | (lp->maxrequest << DMAC_DMAR_MAXDMA_SHIFT)
E 8
	    | DMAC_DMAR_OUT_ORDER);
E 15
I 15
#if 0
	    | lp->maxpayload << DMAC_DMAW_MAXDMA_SHIFT
#else
	    | MAXDMA_128 << DMAC_DMAW_MAXDMA_SHIFT
#endif
	    | lp->maxrequest << DMAC_DMAR_MAXDMA_SHIFT
	    | DMAC_DMAR_OUT_ORDER);				/* ok */
E 15
	DPRINTF(0, (CE_CONT, "!%s: %s: DMAC:0x%x",
	    dp->name, __func__, INL(dp, DMAC_1c)));

	/* clear all interrupt status */
	OUTL(dp, ISR, lp->isr_clear_all);

D 8
#ifdef notdef
E 8
	/* clear statistics area */
	bzero(dp->io_area + lp->sm_offset, sizeof (uint32_t) * STAT_MAX);
D 8
#endif
E 8
I 8

E 8
	return (GEM_SUCCESS);
}

D 10
#endif
E 10
E 7
E 3
static uint_t
atge_mcast_hash(struct gem_dev *dp, uint8_t *addr)
{
	/* extract MSB 6bits of crc in big endian */
	return (gem_ether_crc_be(addr, ETHERADDRL) >> (32 - 6));
}

static int
atge_set_rx_filter(struct gem_dev *dp)
{
	int		i;
	uint32_t	mode;
	uint64_t	mhash;
	uint8_t		*mac;
	static uint8_t	invalid_mac[ETHERADDRL] = {0, 0, 0, 0, 0, 0};
	struct atge_dev	*lp = dp->private;

	DPRINTF(0, (CE_CONT,
I 7
#ifdef GEM3
	    "!%s: %s: called at time:%d, state:%d, rxmode:%b, MACCTL:%08b",
#else
E 7
	    "!%s: %s: called at time:%d, active:%d, rxmode:%b, MACCTL:%08b",
I 7
#endif
E 7
	    dp->name, __func__, ddi_get_lbolt(),
	    dp->mac_active,
	    dp->rxmode, RXMODE_BITS, INL(dp, MACCTL), MACCTL_BITS));

	mode = MACCTL_AB;
	mhash = 0ULL;
	mac = &dp->cur_addr.ether_addr_octet[0];

	if ((dp->rxmode & RXMODE_ENABLE) == 0) {
		/* disable all filters */
		mode = 0;
		mac = invalid_mac;
	} else if (dp->rxmode & RXMODE_PROMISC) {
		/* XXX - no need to set MACCTL_AAM bit */
		mode |= MACCTL_PROMISC;
		mhash = ~0ULL;
	} else if ((dp->rxmode & RXMODE_ALLMULTI) || dp->mc_count > 32) {
		mode |= MACCTL_AAM;
	} else if (dp->mc_count > 0) {
		/* make a hash table */
		for (i = 0; i < dp->mc_count; i++) {
			mhash |= 1ULL << dp->mc_list[i].hash;
		}
	}

	if (bcmp(lp->mac_addr, mac, ETHERADDRL) != 0) {
		OUTL(dp, MACADDR,
D 15
		    (mac[2] << 24) | (mac[3] << 16) | (mac[4] << 8) | mac[5]);
E 15
I 15
		    mac[2] << 24 | mac[3] << 16 | mac[4] << 8 | mac[5]);
E 15
		OUTL(dp, MACADDR + 4,
D 15
		    (mac[0] << 8) | mac[1]);
E 15
I 15
		    mac[0] << 8 | mac[1]);
E 15
		bcopy(mac, lp->mac_addr, ETHERADDRL);
	}

	if ((mode & MACCTL_AAM) == 0) {
		/* need to set multicast hash table */
		OUTL(dp, MHASH, (uint32_t)mhash);
		OUTL(dp, MHASH + 4, (uint32_t)(mhash >> 32));
	}

	/* update rx filter mode */
D 2
	lp->mac_ctl = (lp->mac_ctl &
	    ~(MACCTL_PROMISC | MACCTL_AAM | MACCTL_AB)) |
	    mode;
E 2
I 2
	lp->mac_ctl = mode
	    | (lp->mac_ctl & ~(MACCTL_PROMISC | MACCTL_AAM | MACCTL_AB));
E 2
	OUTL(dp, MACCTL, lp->mac_ctl);

	return (GEM_SUCCESS);
}

static int
atge_set_media(struct gem_dev *dp)
{
	uint32_t	new;
I 6
	int	pkt_coalsc;
	int	pkt_time;
E 6
	struct atge_dev	*lp = dp->private;

	DPRINTF(0, (CE_CONT, "!%s: %s: called at time:%d, "
I 7
#ifdef GEM3
	    "state:%d, MACCTL:%b",
#else
E 7
	    "active:%d, MACCTL:%b",
I 7
#endif
E 7
	    dp->name, __func__, ddi_get_lbolt(),
	    dp->mac_active, INL(dp, MACCTL), MACCTL_BITS));

	new = lp->mac_ctl &
	    ~(MACCTL_FD | MACCTL_SPEED | MACCTL_TXFC | MACCTL_RXFC);

	/* duplex mode */
	if (dp->full_duplex) {
		new |= MACCTL_FD;
	}

	/* speed */
D 6
	if (dp->speed == GEM_SPD_1000) {
E 6
I 6
	switch (dp->speed) {
	case GEM_SPD_1000:
E 6
		new |= MACCTL_SPEED_1000;
D 6
	} else {
E 6
I 6
		pkt_time = 12;
		break;

	case GEM_SPD_100:
E 6
		new |= MACCTL_SPEED_10_100;
I 6
		pkt_time = 120;
		break;

	case GEM_SPD_10:
		new |= MACCTL_SPEED_10_100;
		/* no need to coalesce interrupts */
		pkt_time = 0;
		break;
E 6
	}

	/* setup flow control */
	switch (dp->flow_control) {
	case FLOW_CONTROL_SYMMETRIC:
		new |= MACCTL_TXFC | MACCTL_RXFC;
		break;

	case FLOW_CONTROL_TX_PAUSE:
		new |= MACCTL_TXFC;
		break;

	case FLOW_CONTROL_RX_PAUSE:
		new |= MACCTL_RXFC;
		break;
	}

	if (lp->mac_ctl != new) {
		lp->mac_ctl = new;
		OUTL(dp, MACCTL, new);
	}
D 7

E 7
I 7
D 10
#ifndef CONFIG_ADAPTIVE_COALESCE
E 10
I 10

E 10
E 7
I 6
	/* setup coalsce parameters depend on media speed */
D 10
	if (lp->chip == CHIP_L1E) {
E 10
I 10
	switch (lp->chip) {
	case CHIP_L1E:
#ifndef CONFIG_ADAPTIVE_COALESCE
E 10
D 7
		/* interrupt delay for rx_pkt*/
E 7
I 7
		/* interrupt delay for rx_pkt */
E 7
		OUTW(dp, INTRDELAY2_INIT,
		    min(0xffff, pkt_time * dp->poll_pkt_delay / 2));
		DPRINTF(0, (CE_CONT, "!%s: %s: INTRDELAY2_INIT:0x%x",
		    dp->name, __func__, INW(dp, INTRDELAY2_INIT)));
D 10
	}
E 10
D 7

E 7
I 7
#endif
I 8
D 10
	if (lp->chip == CHIP_L1C) {
		/* interrupt delay for rx_pkt */
E 10
I 10
		break;

	case CHIP_L1C:
	case CHIP_L2C:
	case CHIP_L2C_B:
	case CHIP_L2C_B2:
	case CHIP_L1D:
	case CHIP_L1D_2_0:
		/* interrupt delay for rx_pkt and tx packets */
E 10
		new = min(0xffff, pkt_time * dp->poll_pkt_delay) / 2;
I 10
#ifndef CONFIG_ADAPTIVE_COALESCE
E 10
		OUTL(dp, INTRDELAY_INIT,
D 15
		    (new << 16) | min(0xffff, new << 1));
E 15
I 15
		    new << 16 | min(0xffff, new << 1));
E 15
I 10
#else
		OUTL(dp, INTRDELAY_INIT,
D 15
		    (1 << 16) |
E 15
I 15
		    1U << 16 |
E 15
		    (min(0xffff, (pkt_time * dp->gc.gc_tx_buf_size / 8) / 2)));
#endif
		break;
E 10
	}

E 8
E 7
E 6
	return (GEM_SUCCESS);
}

static int
atge_start_chip(struct gem_dev *dp)
{
	struct atge_dev	*lp = dp->private;

	DPRINTF(0, (CE_CONT, "!%s: %s: called at time:%d",
	    dp->name, __func__, ddi_get_lbolt()));
D 7

E 7
I 7
D 10
#ifdef CONFIG_1C
E 10
I 10

E 10
	switch (lp->chip) {
	case CHIP_L1C:
	case CHIP_L2C:
	case CHIP_L2C_B:
	case CHIP_L2C_B2:
	case CHIP_L1D:
I 8
	case CHIP_L1D_2_0:
E 8
		OUTL(dp, TXQCTL_1c, INL(dp, TXQCTL_1c) | TXQCTL_EN);
		OUTL(dp, RXQCTL_1c, INL(dp, RXQCTL_1c) | RXQCTL_EN);
		break;
	}
D 10
#endif
E 7
	/* start mac */
D 2
	/* XXX - we dont use MACCTL_RXVTAG */
	lp->mac_ctl |= MACCTL_TX | MACCTL_RX | MACCTL_CRCEN
	    | MACCTL_AUTOPAD | (7 << MACCTL_PRMLEN_SHIFT);
E 2
I 2
	/* XXX - we don't use MACCTL_RXVTAG */
E 10
I 10

	/*
	 * Start mac
	 */
	/* we don't use MACCTL_RXVTAG */
E 10
	lp->mac_ctl |= MACCTL_TX | MACCTL_RX;
E 2
	OUTL(dp, MACCTL, lp->mac_ctl);

	/* enable interrupt */
D 3
	lp->imr = OUR_INTR_MASK;
E 3
I 3
D 6
	switch (lp->chip) {
	case CHIP_L1:
		lp->imr = OUR_INTR_MASK_1;
		break;

	case CHIP_L2:
		lp->imr = OUR_INTR_MASK_2;
		break;

	case CHIP_L1E:
	case CHIP_L2E_A:
	case CHIP_L2E_B:
		lp->imr = OUR_INTR_MASK_1e;
		break;
	}
E 6
I 6
	lp->imr = lp->isr_rx_err | lp->isr_rx_ok |
	    lp->isr_tx_err | lp->isr_tx_ok |
	    lp->isr_dma_err | lp->isr_gphy | lp->isr_sm | lp->isr_pcie_err;
	DPRINTF(0, (CE_CONT, "!%s: %s: imr:%b",
	    dp->name, __func__, lp->imr, lp->isr_bits));
E 6
E 3
	if ((dp->misc_flag & GEM_NOINTR) == 0) {
		OUTL(dp, IMR, lp->imr);
	}

	return (GEM_SUCCESS);
}

static int
atge_stop_chip(struct gem_dev *dp)
{
I 3
	uint8_t		*mac;
E 3
	struct atge_dev	*lp = dp->private;

	DPRINTF(0, (CE_CONT, "!%s: %s: called at time:%d",
	    dp->name, __func__, ddi_get_lbolt()));

I 7
D 10
#ifdef CONFIG_1C
E 10
	switch (lp->chip) {
	case CHIP_L1C:
	case CHIP_L2C:
	case CHIP_L2C_B:
	case CHIP_L2C_B2:
	case CHIP_L1D:
I 8
	case CHIP_L1D_2_0:
E 8
D 15
		OUTL(dp, TXQCTL_1c, INL(dp, TXQCTL_1c) & ~TXQCTL_EN);
		OUTL(dp, RXQCTL_1c, INL(dp, RXQCTL_1c) & ~RXQCTL_EN);
E 15
I 15
		OUTL(dp, TXQCTL_1c, INL(dp, TXQCTL_1c) & ~TXQCTL_EN); /* ok */
		OUTL(dp, RXQCTL_1c, INL(dp, RXQCTL_1c) & ~RXQCTL_EN); /* ok */
E 15
I 8
		DPRINTF(0, (CE_CONT, "!%s: %s: tx_list:%d %d, reg:%d",
		    dp->name, __func__,
		    lp->tx_buffer_head, lp->tx_buffer_tail,
		    INL(dp, MB_PRIO_CONS_IDX) >> 16));
I 15

		atge_wait_idle(dp, IDLE_RXQ | IDLE_TXQ);

		lp->mac_ctl &= ~(MACCTL_TX | MACCTL_RX);
		OUTL(dp, MACCTL, lp->mac_ctl);

		atge_wait_idle(dp, IDLE_TXMAC | IDLE_RXMAC);
E 15
E 8
		break;
	}
D 10
#endif
E 10
I 10
D 15

E 15
E 10
E 7
	/* Disable interrupts by clearing the interrupt mask */
D 2
	lp->imr = 0;
E 2
	if ((dp->misc_flag & GEM_NOINTR) == 0) {
D 2
		OUTL(dp, IMR, lp->imr);
E 2
I 2
		/* XXX - don't clear imr to avoid bogus interrupts */
		OUTL(dp, IMR, 0);
E 2
	}

I 3
	/* restore factory mac address */
	mac = dp->dev_addr.ether_addr_octet;
	OUTL(dp, MACADDR,
D 15
	    (mac[2] << 24) | (mac[3] << 16) | (mac[4] << 8) | mac[5]);
E 15
I 15
	    mac[2] << 24 | mac[3] << 16 | mac[4] << 8 | mac[5]);
E 15
	OUTL(dp, MACADDR + 4,
D 15
	    (mac[0] << 8) | mac[1]);
E 15
I 15
	    mac[0] << 8 | mac[1]);
E 15
	bcopy(mac, lp->mac_addr, ETHERADDRL);

E 3
	(void) atge_reset_chip(dp);

	return (GEM_SUCCESS);
}

static boolean_t
D 7
atge_read_eeprom(struct gem_dev *dp, uint_t offset, uint32_t *valp)
E 7
I 7
atge_read_eeprom_1(struct gem_dev *dp, uint_t offset, uint32_t *valp)
E 7
{
	int	i;

	if (offset & 3) {
		/* offset should be aligned by 4 */
		return (B_FALSE);
	}

	OUTL(dp, VPDDATA, 0);
	OUTL(dp, VPDCAP, offset << VPDCAP_ADDR_SHIFT);

	delay(drv_usectohz(2000));

	for (i = 0; (INL(dp, VPDCAP) & VPDCAP_FLAG) == 0; i++) {
		if (i > 10) {
			/* timeout */
			DPRINTF(0, (CE_CONT, "!%s: %s: timeout",
			    dp->name, __func__));
			return (B_FALSE);
		}
		delay(drv_usectohz(2000));
	}

	*valp = INL(dp, VPDDATA);

	DPRINTF(4, (CE_CONT, "!%s: %s: offset:%x: %x",
	    dp->name, __func__, offset, *valp));

	return (B_TRUE);
}

I 7
static boolean_t
atge_read_eeprom_1c(struct gem_dev *dp, uint_t offset, uint32_t *valp)
{
	int	i;
	uint32_t	otp;
	uint32_t	val;
D 8
	int		ret = B_TRUE;
E 8
I 8
	int		ret;
E 8

	if (offset & 3) {
		/* offset should be aligned by 4 */
		return (B_FALSE);
	}

	otp = INL(dp, OTPCTL);
	if ((otp & OTPCTL_CLK_EN) == 0) {
		OUTL(dp, OTPCTL, otp | OTPCTL_CLK_EN);
	}

	OUTL(dp, EEPROM_DATA, 0);
	OUTL(dp, EEPROMCTL, offset << EEC_ADDR_SHIFT);

	for (i = 0; (INL(dp, EEPROMCTL) & EEC_RW) == 0; i++) {
		if (i > 10) {
			/* timeout */
			DPRINTF(0, (CE_CONT, "!%s: %s: timeout",
			    dp->name, __func__));
			ret = B_FALSE;
			goto x;
		}
		delay(drv_usectohz(100));
	}

I 8
	ret = B_TRUE;
E 8
	val = INL(dp, EEPROMCTL);
D 15
	*valp = ((val & EEC_DATA_HI) << 16) | (INL(dp, EEPROM_DATA) >> 16);
E 15
I 15
	*valp = (val & EEC_DATA_HI) << 16 | INL(dp, EEPROM_DATA) >> 16;
E 15

	DPRINTF(0, (CE_CONT, "!%s: %s: offset:%x: %x",
	    dp->name, __func__, offset, *valp));
x:
	if ((otp & OTPCTL_CLK_EN) == 0) {
		OUTL(dp, OTPCTL, otp);
	}

	return (ret);
}

static boolean_t
atge_read_eeprom(struct gem_dev *dp, uint_t offset, uint32_t *valp)
{
	struct atge_dev	*lp = dp->private;
D 10
#ifdef CONFIG_1C
E 10
I 10

E 10
	switch (lp->chip) {
	case CHIP_L1C:
	case CHIP_L2C:
	case CHIP_L2C_B:
	case CHIP_L2C_B2:
	case CHIP_L1D:
I 8
	case CHIP_L1D_2_0:
E 8
		return (atge_read_eeprom_1c(dp, offset, valp));
	}
D 10
#endif
E 10
	return (atge_read_eeprom_1(dp, offset, valp));
}

E 7
#ifdef DEBUG_LEVEL
static void
atge_eeprom_dump(struct gem_dev *dp)
{
	int		i;
D 8
	uint32_t	prom[0x10];
E 8
I 8
#define	EEPROM_DUMP_SIZE	0x10
	uint32_t	prom[EEPROM_DUMP_SIZE];
E 8

D 8
	for (i = 0; i < 0x10; i++) {
E 8
I 8
	for (i = 0; i < EEPROM_DUMP_SIZE; i++) {
E 8
		(void) atge_read_eeprom(dp, i*4, &prom[i]);
	}

	cmn_err(CE_CONT, "!%s: eeprom dump:", dp->name);
D 8
	for (i = 0; i < 0x10; i += 4) {
E 8
I 8
	for (i = 0; i < EEPROM_DUMP_SIZE; i += 4) {
E 8
		cmn_err(CE_CONT, "!0x%02x: 0x%08x 0x%08x 0x%08x 0x%08x",
		    i, prom[i], prom[i + 1], prom[i + 2], prom[i + 3]);
	}
I 8
#undef	EEPROM_DUMP_SIZE
E 8
}
D 15
#endif /* DEBUG_LEVEL */
E 15
I 15
#endif
E 15

static boolean_t
atge_read_mac_addr(struct gem_dev *dp, uint8_t *mac)
{
	uint32_t	i;
	uint_t		offset;
	uint32_t	val;
	uint16_t	reg;
	boolean_t	(*read_prom)(struct gem_dev *, uint_t, uint32_t *);
D 2
	static uint8_t	zeros[] = {0, 0, 0, 0, 0, 0};
E 2
I 2
	static uint8_t	zero6[ETHERADDRL] = {0, 0, 0, 0, 0, 0};
E 2

	/* check if eeprom exists */
	val = INL(dp, FLASHCTL);
	if (val & FLASHCTL_VPD_EN) {
		val &= ~FLASHCTL_VPD_EN;
		OUTL(dp, FLASHCTL, val);
	}

	if ((INW(dp, PCIE_CAP_LIST) & 0xff00) == 0x6c00) {
		/* get mac address from EEPROM content */
		DPRINTF(0, (CE_CONT,
		    "!%s: %s: reading factory mac address from eeprom",
		    dp->name, __func__));
		read_prom = &atge_read_eeprom;
		offset = 0x100;
	} else {
D 2
		cmn_err(CE_CONT,
		    "!%s: %s: reading flash rom:  not supported",
E 2
I 2
		cmn_err(CE_NOTE,
		    "!%s: %s: reading flash rom: not supported",
E 2
		    dp->name, __func__);
		return (B_FALSE);
	}

	for (i = 0; i < 2048; i++) {
		if (!(*read_prom)(dp, offset, &val)) {
			break;
		}
		offset += 4;

		if ((val & 0xff) != 0x5a) {
			break;
		}
		reg = val >> 16;

		if (!(*read_prom)(dp, offset, &val)) {
			break;
		}
		offset += 4;

		if (reg ==  MACADDR) {
			mac[2] = (uint8_t)(val >> 24);
			mac[3] = (uint8_t)(val >> 16);
			mac[4] = (uint8_t)(val >> 8);
			mac[5] = (uint8_t)val;
		} else if (reg == MACADDR + 4) {
			mac[0] = (uint8_t)(val >> 8);
			mac[1] = (uint8_t)val;
		} else {
			break;
		}
	}

D 2
	if ((mac[0] & 1) || bcmp(mac, zeros, ETHERADDRL) == 0) {
E 2
I 2
	if ((mac[0] & 1) || bcmp(mac, zero6, ETHERADDRL) == 0) {
E 2
		/* wrong mac address */
		return (B_FALSE);
	}

	DPRINTF(0, (CE_CONT,
	    "!%s: %s: mac address found (%x:%x:%x:%x:%x:%x)",
	    dp->name, __func__,
	    mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]));

	return (B_TRUE);
}

static int
atge_attach_chip(struct gem_dev *dp)
{
	uint8_t		*mac;
I 2
	uint32_t	uval;
E 2
	struct atge_dev	*lp = dp->private;
I 2
	static uint8_t	zero6[6] = {0, 0, 0, 0, 0, 0};
E 2

	DPRINTF(0, (CE_CONT, "!%s: %s: called at time:%ld",
	    dp->name, __func__, ddi_get_lbolt()));

	mac = dp->dev_addr.ether_addr_octet;
I 7
	bzero(mac, ETHERADDRL);
E 7
D 2
	atge_read_mac_addr(dp, mac);
E 2
I 2
D 3
#ifdef notdef
E 3
I 3
#ifdef CONFIG_READ_MACADDR_FROM_EEPROM
E 3
D 7
	if (!atge_read_mac_addr(dp, mac)) {
		gem_generate_macaddr(dp, mac);
	}
E 2

E 7
I 7
D 15
	(void) atge_read_mac_addr(dp, mac);
E 15
I 15
	switch (lp->chip) {
	case CHIP_L1C:
	case CHIP_L2C:
	case CHIP_L2C_B:
	case CHIP_L2C_B2:
	case CHIP_L1D:
	case CHIP_L1D_2_0:
		/* XXX - todo: load eeprom contants */
		break;

	default:
		(void) atge_read_mac_addr(dp, mac);
	}
E 15
#endif
E 7
I 2
	if ((mac[0] & 1) || bcmp(mac, zero6, ETHERADDRL) == 0) {
		/* try to get mac address from BIOS */
		uval = INL(dp, MACADDR + 4);
		mac[0] = (uint8_t)(uval >> 8);
		mac[1] = (uint8_t)uval;
		uval = INL(dp, MACADDR);
		mac[2] = (uint8_t)(uval >> 24);
		mac[3] = (uint8_t)(uval >> 16);
		mac[4] = (uint8_t)(uval >> 8);
		mac[5] = (uint8_t)uval;
	}
D 7
#else
	uval = INL(dp, MACADDR + 4);
	mac[0] = (uint8_t)(uval >> 8);
	mac[1] = (uint8_t)uval;
	uval = INL(dp, MACADDR);
	mac[2] = (uint8_t)(uval >> 24);
	mac[3] = (uint8_t)(uval >> 16);
	mac[4] = (uint8_t)(uval >> 8);
	mac[5] = (uint8_t)uval;
#endif
E 7
I 7
	if ((mac[0] & 1) || bcmp(mac, zero6, ETHERADDRL) == 0) {
I 8
		/* factory mac address seems to be corrupted */
E 8
		gem_generate_macaddr(dp, mac);
	}
E 7

E 2
	gem_get_mac_addr_conf(dp);

D 2
	if (mac[0] & 1) {
E 2
I 2
	if ((mac[0] & 1) || bcmp(mac, zero6, ETHERADDRL) == 0) {
E 2
		/* wrong mac address, generate new one. */
		cmn_err(CE_NOTE,
		    "!%s: mac address %x:%x:%x:%x:%x:%x is corrupted.",
		    dp->name,
		    mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);

		gem_generate_macaddr(dp, mac);
	}
D 3
#if DEBUG_LEVEL > 5
E 3
I 3
D 7
#if DEBUG_LEVEL > 9999
E 7
I 7
D 15
#if DEBUG_LEVEL > -1
E 7
E 3
	atge_eeprom_dump(dp);
E 15
I 15
#ifdef DEBUG_LEVEL
	if (DEBUG_LEVEL > 10) {
		atge_eeprom_dump(dp);
	}
E 15
#endif /* DEBUG_LEVEL */

I 8
	uval = INL(dp, PCIE_DEVCTRL);
	lp->maxpayload = (uval >> 5) & 7;
	lp->maxrequest = (uval >> 12) & 7;
	lp->maxpayload = min(lp->maxpayload, MAXDMA_1024);
	lp->maxrequest = min(lp->maxrequest, MAXDMA_1024);
D 10

E 10
I 10
#ifndef GEM_CONFIG_JUMBO_FRAME
E 10
E 8
D 3
#ifdef GEM_CONFIG_GLD3
	dp->misc_flag |= GEM_VLAN_SOFT;
#endif

E 3
D 7
	/* fix rx buffer size */
E 7
I 7
	/* rx buffer size should be aligned by 8 */
E 7
	dp->rx_buf_len = ROUNDUP(dp->rx_buf_len, 8);
D 10

E 10
I 10
#endif
E 10
	mutex_init(&lp->mbox_lock,
	    NULL, MUTEX_DRIVER, (void *)dp->iblock_cookie);

I 3
D 6
#ifdef GEM_CONFIG_GLD3
E 6
E 3
D 10
#ifdef CONFIG_CKSUM_OFFLOAD
E 10
I 8
	switch (lp->chip) {
D 10
	default:
E 10
I 10
	case CHIP_L1:
	case CHIP_L1E:
	case CHIP_L2E_A:
	case CHIP_L2E_B:
#ifdef CONFIG_CKSUM_OFFLOAD
I 15
#if 0
E 15
E 10
		/* GEM_CKSUM_HEADER_IPv4 didn't work for partial checksum */
		dp->misc_flag |= GEM_CKSUM_PARTIAL;
E 8
D 15
#ifdef CONFIG_LSO
D 8
	dp->misc_flag |= GEM_LSO;
E 8
I 8
		dp->misc_flag |= GEM_LSO;
E 15
I 15
#endif
#if 0 /* CONFIG_LSO */
		dp->misc_flag |= GEM_LSO_IPv4 | GEM_LSO_IPv4_PHCKSUM
		    | GEM_LSO_CLR_LEN_IPv4 | GEM_LSO_MULTIPLE_MSS_ONLY;
E 15
E 8
#endif /* CONFIG_LSO */
I 10
#endif /* CONFIG_CKSUM_OFFLOAD */
#ifdef not_tested /* CONFIG_VLAN_HW */
		dp->misc_flag |= GEM_VLAN_HARD;
#else
		dp->misc_flag |= GEM_VLAN_SOFT;
#endif
E 10
D 8
	/* XXX - GEM_CKSUM_HEADER_IPv4 didn't work for partial checksum */
	dp->misc_flag |= GEM_CKSUM_PARTIAL;
E 8
I 8
		break;
E 8
I 7
D 10
#ifdef CONFIG_1C
E 10
D 8
	switch (lp->chip) {
E 8
I 8

E 8
	case CHIP_L1C:
	case CHIP_L2C:
	case CHIP_L2C_B:
	case CHIP_L2C_B2:
	case CHIP_L1D:
D 8
		dp->misc_flag &= ~(GEM_LSO | GEM_CKSUM_PARTIAL);
	}
E 8
I 8
	case CHIP_L1D_2_0:
D 10
		/* for tests */
E 10
I 10
#ifdef CONFIG_CKSUM_OFFLOAD
E 10
D 15
		dp->misc_flag |= GEM_CKSUM_PARTIAL;
E 15
D 10
		break;
E 8
#endif /* CONFIG_1C */
I 8
	}
E 10
I 10
#ifdef CONFIG_LSO
D 15
		dp->misc_flag |= GEM_LSO;
E 15
I 15
		dp->misc_flag |= GEM_LSO_IPv4 | GEM_LSO_IPv4_PHCKSUM
		    | GEM_LSO_CLR_LEN_IPv4 | GEM_LSO_MULTIPLE_MSS_ONLY;
E 15
#endif
E 10
E 8
E 7
#endif /* CONFIG_CKSUM_OFFLOAD */
D 10

E 10
#ifdef CONFIG_VLAN_HW
D 10
	dp->misc_flag |= GEM_VLAN_HARD;
E 10
I 10
		dp->misc_flag |= GEM_VLAN_HARD;
E 10
#else
D 10
	dp->misc_flag |= GEM_VLAN_SOFT;
E 10
I 10
		dp->misc_flag |= GEM_VLAN_SOFT;
E 10
#endif
I 10
		break;
E 10
I 3
D 6
#endif /* GEM_CONFIG_GLD3 */
E 6

I 10
	case CHIP_L2:
	default:
		break;
	}

I 15
	/*
	 * configure rx
	 */
E 15
E 10
D 7
	if (lp->chip != CHIP_L1) {
E 7
I 7
	switch (lp->chip) {
	case CHIP_L1:
D 10
#ifdef CONFIG_1C
E 10
	case CHIP_L1C:
	case CHIP_L2C:
	case CHIP_L2C_B:
	case CHIP_L2C_B2:
	case CHIP_L1D:
I 8
	case CHIP_L1D_2_0:
E 8
D 10
#endif
E 10
I 10
		dp->misc_flag |= GEM_POLL_RXONLY;
E 10
		break;

D 10
	default:
E 10
I 10
	case CHIP_L2:
E 10
E 7
		dp->misc_flag |= GEM_NORXBUF;
I 7
		break;
E 7
D 10
	}
E 10

D 7
	lp->rxf_buf_hiwat =  lp->rxf_buf_len  -
	    ROUNDUP(sizeof (struct ether_header) + dp->mtu + ETHERFCSL
D 6
	    + VTAG_SIZE, 32);
E 6
I 6
	    + VTAG_SIZE + sizeof (struct rx_status_desc), 32);
E 7
I 7
D 10
	/* for l1e */
	switch (lp->chip) {
E 10
	case CHIP_L1E:
	case CHIP_L2E_A:
	case CHIP_L2E_B:
I 10
		dp->misc_flag |= GEM_NORXBUF;
E 10
		lp->rxf_buf_hiwat =  lp->rxf_buf_len  -
		    ROUNDUP(sizeof (struct ether_header) + dp->mtu + ETHERFCSL
		    + VTAG_SIZE + sizeof (struct rx_status_desc), 32);
		dp->misc_flag |= GEM_POLL_RXONLY;
		break;
	}
E 7
E 6

E 3
	return (GEM_SUCCESS);
}

I 10
#ifdef GEM_CONFIG_JUMBO_FRAME
static void
atge_fixup_params(struct gem_dev *dp)
{
	struct atge_dev	*lp = dp->private;

	/* rx buffer size should be aligned by 8 */
	dp->rx_buf_len = ROUNDUP(dp->rx_buf_len, 8);
}

#endif
E 10
static int
D 6
atge_get_stats(struct gem_dev *dp)
E 6
I 6
atge_update_stats(struct gem_dev *dp)
E 6
{
	int		i;
	int		diff;
	uint32_t	uval;
	uint32_t	*statp;
	struct atge_dev	*lp = dp->private;

	DPRINTF(4, (CE_CONT, "!%s: %s:", dp->name, __func__));

D 3
	atge_ioarea_dma_sync(dp, IOA_SM_OFFSET,
	    (off_t)IOA_SM_SIZE, DDI_DMA_SYNC_FORKERNEL);
E 3
I 3
D 6
	if (lp->chip == CHIP_L2) {
		return (GEM_SUCCESS);
	}
E 3

D 3
	statp = (uint32_t *)(dp->io_area + IOA_SM_OFFSET);
E 3
I 3
	atge_ioarea_dma_sync(dp, lp->sm_offset,
	    (size_t)(sizeof (uint32_t) * STAT_MAX), DDI_DMA_SYNC_FORKERNEL);
E 3

E 6
I 3
	statp = (uint32_t *)(dp->io_area + lp->sm_offset);

E 3
I 2
D 6
	if (statp[STAT_SM_VALID] == 0) {
I 3
		/* not yet */
E 6
I 6
	switch (lp->chip) {
	case CHIP_L2:
		/* no statistics info */
E 6
E 3
		return (GEM_SUCCESS);
I 6

	case CHIP_L1:
		atge_ioarea_dma_sync(dp, lp->sm_offset,
		    (size_t)(sizeof (uint32_t) * STAT_MAX),
		    DDI_DMA_SYNC_FORKERNEL);
		break;

	case CHIP_L1E:
	case CHIP_L2E_A:
	case CHIP_L2E_B:
D 7
		/* read statistics counters by ourselves */
E 7
I 7
D 10
#ifdef CONFIG_1C
E 10
	case CHIP_L1C:
	case CHIP_L2C:
	case CHIP_L2C_B:
	case CHIP_L2C_B2:
	case CHIP_L1D:
I 8
	case CHIP_L1D_2_0:
E 8
D 10
#endif
E 10
		/* read statistics counter registers by ourselves */
E 7
		for (i = 0; i < STAT_MAX; i++) {
			statp[i] = INL(dp,
			    MAC_STATS_BASE + i * sizeof (uint32_t));
		}
		break;
E 6
	}

E 2
	for (i = 0; i < STAT_MAX; i++) {
I 2
D 3
#if 0
E 2
		uval = statp[i];
		uval = LE_32(uval);
		diff = uval - lp->last_stat[i];
D 2

E 2
I 2
		lp->last_stat[i] = uval;
#else
E 3
		diff = statp[i];
D 3
#endif
E 3
E 2
		switch (i) {
I 2
D 6
#ifdef USE_GETSTAT_RX
E 6
		case STAT_RxCRC:
			dp->stats.errrcv += diff;
			dp->stats.crc += diff;
			break;

		case STAT_RxLONG:
		case STAT_RxLEN:
			dp->stats.errrcv += diff;
			dp->stats.frame_too_long += diff;
			break;

		case STAT_RxRUNT: /* too short and crc is good */
		case STAT_RxFRAG: /* too short and crc is bad */
			dp->stats.errrcv += diff;
			dp->stats.runt += diff;
			break;

		case STAT_RxFIFO:
			dp->stats.errrcv += diff;
			dp->stats.overflow += diff;
			break;

		case STAT_RxNORRD:
			dp->stats.errrcv += diff;
			dp->stats.norcvbuf += diff;
			break;

		case STAT_RxALIGN:
			dp->stats.errrcv += diff;
			dp->stats.frame += diff;
			break;
D 6
#endif /* USE_GETSTAT_RX */
E 6

E 2
		case STAT_TxEXCDEFER:
		case STAT_TxABORT:
			dp->stats.errxmt += diff;
			dp->stats.excoll += diff;
			break;

		case STAT_TxDEFER:
			dp->stats.defer += diff;
			break;

		case STAT_Tx1COL:
			dp->stats.errxmt += diff;
			dp->stats.first_coll += diff;
			break;

		case STAT_TxMCOL:
			dp->stats.errxmt += diff;
			dp->stats.multi_coll += diff;
			break;

		case STAT_TxLATE_COL:
			dp->stats.errxmt += diff;
			dp->stats.xmtlatecoll += diff;
			break;

		case STAT_TxUNDERRUN:
		case STAT_TxTRUNC:
			dp->stats.errxmt += diff;
			dp->stats.underflow += diff;
			break;

		default:
		case STAT_TxCTRL:
		case STAT_TxBYTE:
		case STAT_TxRD_EOP:
		case STAT_TxLEN:
			break;
		}
D 2
		lp->last_stat[i] = uval;
E 2
	}

I 6
#if 0
E 6
D 2
	DPRINTF(4, (CE_CONT, "%s: %s: sm_magic:%x",
E 2
I 2
	DPRINTF(4, (CE_CONT, "!%s: %s: sm_magic:%x",
E 2
	    dp->name, __func__, statp[STAT_SM_VALID]));
D 6

E 6
	statp[STAT_SM_VALID] = 0;
I 6
#endif
	return (GEM_SUCCESS);
}
E 6

I 6
static int
atge_get_stats(struct gem_dev *dp)
{
	clock_t	now;
	struct atge_dev	*lp = dp->private;

	now = ddi_get_lbolt();

	if (now - lp->last_stats_update > drv_usectohz(10*1000)) {
		atge_update_stats(dp);
		lp->last_stats_update = now;
	}
E 6
	return (GEM_SUCCESS);
I 6

E 6
}

/*
 * tx/rx descriptor manipulations
 */
#ifdef DEBUG_LEVEL
static int atge_tx_frags[MAXTXFRAGS];
#endif
static int
D 3
atge_tx_desc_write(struct gem_dev *dp, int slot,
E 3
I 3
atge_tx_desc_write_1_1e(struct gem_dev *dp, int slot,
E 3
	ddi_dma_cookie_t *dmacookie, int frags, uint64_t flags)
{
	int	i;
	int	used;
D 2
	uint64_t	headerlen = 0;
E 2
I 2
	uint_t	tx_ring_size = dp->gc.gc_tx_ring_size;
	uint64_t	headerlen;
E 2
	uint64_t	addr;
	uint64_t	mark;
I 15
	uint64_t	tmp;
E 15
I 2
#ifdef CONFIG_CKSUM_OFFLOAD
E 2
	uint64_t	mss;
	uint64_t	hck_start;
	uint64_t	hck_stuff;
I 2
	uint64_t	ip_header_len;
I 15
	uint64_t	lsolen = 0;
E 15
#endif
I 10
#ifdef CONFIG_VLAN_HW
D 15
	uint_t	vtag;
E 15
I 15
	uint64_t	vtag;
E 15
#endif
E 10
E 2
	struct atge_dev	*lp = dp->private;
	struct tx_buffer_desc	*tdp;
	ddi_dma_cookie_t	*dcp;

I 2

E 2
#if DEBUG_LEVEL > 2
	cmn_err(CE_CONT,
D 3
	    "!%s: %s time: %d, seqnum: %d, slot %d, frags: %d flags: %lld",
E 3
I 3
	    "!%s: %s time: %d, seqnum: %d, slot %d, frags: %d flags:0x%llx",
E 3
	    dp->name, __func__, ddi_get_lbolt(),
	    dp->tx_desc_tail, slot, frags, flags);
	for (i = 0; i < frags; i++) {
		cmn_err(CE_CONT, "!%d: addr: 0x%llx, len: 0x%x",
		    i, dmacookie[i].dmac_laddress, dmacookie[i].dmac_size);
	}
#endif
#if DEBUG_LEVEL > 2
	if (flags & GEM_TXFLAG_INTR) {
		cmn_err(CE_CONT,
		    "!%s: %s time: %d, "
D 3
		    "seqnum: %d, slot %d, frags: %d flags: %lld",
E 3
I 3
		    "seqnum: %d, slot %d, frags: %d flags:0x%llx",
E 3
		    dp->name, __func__, ddi_get_lbolt(),
		    dp->tx_desc_tail, slot, frags, flags);
	}
#endif
D 6
#if DEBUG_LEVEL > 10
E 6
I 6
#if DEBUG_LEVEL > 0
E 6
	flags |= GEM_TXFLAG_INTR;
#endif
#ifdef DEBUG_LEVEL
	atge_tx_frags[min(frags, MAXTXFRAGS) - 1]++;
#endif
	/*
	 * write tx descriptor(s)
	 */
D 6
#ifdef CONFIG_POLLING
D 2
	if (flags & GEM_TXFLAG_INTR) {
		mark = TBF_DMAINT;
	} else {
		mark = 0;
	}
E 2
I 2
	mark = (flags & GEM_TXFLAG_INTR) ? TBF_DMAINT : 0;
E 2
#else
E 6
	mark = 0;
I 6
D 7
#ifdef CONFIG_POLLING
E 7
I 7
#ifdef CONFIG_ADAPTIVE_COALESCE
E 7
	/*
	 * XXX - don't use TBF_DMAINT or TBF_TXINT for L1E chipset.
	 * it caused tx-hang.
	 */
	if (lp->chip == CHIP_L1 && (flags & GEM_TXFLAG_INTR)) {
		mark |= TBF_DMAINT;
	}
E 6
#endif
I 2
	headerlen = 0;

E 2
#ifdef CONFIG_CKSUM_OFFLOAD
	/* Check for TCP Large Segmentation Offload */
	mss = (flags & GEM_TXFLAG_MSS) >> GEM_TXFLAG_MSS_SHIFT;
	hck_start = (flags & GEM_TXFLAG_HCKSTART) >> GEM_TXFLAG_HCKSTART_SHIFT;
	hck_stuff = (flags & GEM_TXFLAG_HCKSTUFF) >> GEM_TXFLAG_HCKSTUFF_SHIFT;
I 2

	ip_header_len = hck_start - sizeof (struct ether_header);

E 2
	if (mss) {
		uint64_t	tcp_header_len;
D 2
		uint64_t	ip_header_len;
E 2

I 15
		lsolen = dmacookie[0].dmac_type;
E 15
		tcp_header_len =
D 2
		    (flags & GEM_TXFLAG_TCPHLEN) >> GEM_TXFLAG_TCPHLEN_SHIFT;
		ip_header_len = hck_start - sizeof (struct ether_header);
E 2
I 2
		    ((flags & GEM_TXFLAG_TCPHLEN)
		    >> GEM_TXFLAG_TCPHLEN_SHIFT) * 4;
E 2
		headerlen = tcp_header_len + hck_start;

D 15
		mark |= (mss << TBF_MSS_SHIFT)
E 15
I 15
		mark |= mss << TBF_MSS_SHIFT
E 15
		    | TBF_HDRFLG
D 15
		    | ((tcp_header_len / 4) << TBF_TCPHL_SHIFT)
		    | ((ip_header_len / 4) << TBF_IPHL_SHIFT)
E 15
I 15
		    | (tcp_header_len >> 2) << TBF_TCPHL_SHIFT
		    | (ip_header_len >> 2) << TBF_IPHL_SHIFT
E 15
		    | TBF_TCPC
		    | TBF_IPC
		    | TBF_SEGMENT;
		if (flags & GEM_TXFLAG_IPv6) {
			mark |= TBF_COALESE;
		}

		/* TBF_CKSUM flag is not required */
		if (flags & GEM_TXFLAG_SWVTAG) {
			/* XXX - need to check if it is really required */
			mark |= TBF_ETHTYPE;
		}
	} else if (hck_start) {
D 2
		/* XXX - IPC flag didn't work */
E 2
I 2
		/* XXX - don't use custom checksum for UDP */
E 2
D 15
		mark |= (hck_stuff << TBF_CKSUMOFF_SHIFT)
		    | (hck_start << TBF_PAYLDOFF_SHIFT)
E 15
I 15
		mark |= hck_stuff << TBF_CKSUMOFF_SHIFT
		    | hck_start << TBF_PAYLDOFF_SHIFT
E 15
		    | TBF_CKSUM;
D 2
		if (flags & GEM_TXFLAG_TCP) {
			mark |= TBF_TCPC;
		} else if (flags & GEM_TXFLAG_UDP) {
			mark |= TBF_UDPC;
		}
E 2
	}
D 2
#endif
E 2
I 2
#endif /* CONFIG_CKSUM_OFFLOAD */
E 2
D 10
#ifdef CONFIG_HW_VTAG
E 10
I 10
#ifdef CONFIG_VLAN_HW
E 10
D 15
	if (vtag = (flags & GEM_TXFLAG_VTAG) >> GEM_TXFLAG_VTAG_SHIFT) {
		vtag = (vtag << 4) | (vtag >> 13) | ((vtag >> 9) & 0x8);
		mark |= TBF_INSVTAG | (vtag << TBF_VTAG_SHIFT);
E 15
I 15
	vtag = (flags & GEM_TXFLAG_VTAG) >> GEM_TXFLAG_VTAG_SHIFT;
	if (vtag) {
		vtag = vtag << 4 | vtag >> 13 | ((vtag >> 9) & 0x8);
		vtag = TBF_INSVTAG | vtag << TBF_VTAG_SHIFT;
		mark |= vtag;
E 15
	}
#endif
	dcp = &dmacookie[0];
	used = 0;
	for (i = 0; i < frags - 1; i++, dcp++) {
I 4
		ASSERT(dcp->dmac_laddress != 0);
E 4
		if (headerlen > 0 && headerlen < dcp->dmac_size) {
			tdp = &((struct tx_buffer_desc *)(dp->io_area +
D 2
			    IOA_TBD_OFFSET))[SLOT(slot + used, TX_RING_SIZE)];
E 2
I 2
D 3
			    IOA_TBD_OFFSET))[SLOT(slot + used, tx_ring_size)];
E 3
I 3
			    lp->tbd_offset))[SLOT(slot + used, tx_ring_size)];
E 3
E 2
			used++;

D 15
			mark |= headerlen;
E 15
I 15
			tmp = mark | headerlen;
E 15
D 3
			addr = dcp->dmac_address;
E 3
I 3
			addr = dcp->dmac_laddress;
E 3
D 15
			tdp->tb_flags = LE_64(mark);
E 15
I 15
			tdp->tb_flags = LE_64(tmp);
E 15
			tdp->tb_addr = LE_64(addr);

			mark &= ~(TBF_BUFLEN | TBF_HDRFLG);
			dcp->dmac_size -= headerlen;
D 3
			dcp->dmac_address += headerlen;
E 3
I 3
			dcp->dmac_laddress += headerlen;
I 15
			lsolen -= headerlen;
E 15
E 3
			headerlen = 0;
D 15
		} else if (headerlen >= dcp->dmac_size) {
E 15
I 15
#if DEBUG_LEVEL > 10
		} else if (headerlen > dcp->dmac_size) {
E 15
			/* no need to break the fragment in two pieces */
D 15
			headerlen -= dcp->dmac_size;
E 15
I 15
			cmn_err(CE_CONT, "!%s: header is fragmented",
			    __func__);
#endif
E 15
		}
		tdp = &((struct tx_buffer_desc *)(dp->io_area +
D 2
		    IOA_TBD_OFFSET))[SLOT(slot + used, TX_RING_SIZE)];
E 2
I 2
D 3
		    IOA_TBD_OFFSET))[SLOT(slot + used, tx_ring_size)];
E 3
I 3
		    lp->tbd_offset))[SLOT(slot + used, tx_ring_size)];
E 3
E 2
		used++;

D 15
		mark |= dcp->dmac_size;
E 15
I 15
		tmp = mark | dcp->dmac_size;
E 15
D 3
		addr = dcp->dmac_address;
E 3
I 3
		addr = dcp->dmac_laddress;
E 3
D 15
		tdp->tb_flags = LE_64(mark);
E 15
I 15
		tdp->tb_flags = LE_64(tmp);
E 15
		tdp->tb_addr = LE_64(addr);

		mark &= ~(TBF_BUFLEN | TBF_HDRFLG);
D 15
	}
E 15

D 15
	/* for the last fragment */
	if (headerlen > 0 && headerlen < dcp->dmac_size) {
I 4
		ASSERT(dcp->dmac_laddress != 0);
E 4
		tdp = &((struct tx_buffer_desc *)(dp->io_area +
D 2
		    IOA_TBD_OFFSET))[SLOT(slot + used, TX_RING_SIZE)];
E 2
I 2
D 3
		    IOA_TBD_OFFSET))[SLOT(slot + used, tx_ring_size)];
E 3
I 3
		    lp->tbd_offset))[SLOT(slot + used, tx_ring_size)];
E 3
E 2
		used++;
E 15
I 15
		headerlen -= min(headerlen, dcp->dmac_size);
		lsolen -= dcp->dmac_size;
		if (mss && lsolen == 0) {
			tdp->tb_flags |= LE_64(TBF_EOP);
E 15

D 15
		mark |= headerlen;
D 3
		addr = dcp->dmac_address;
E 3
I 3
		addr = dcp->dmac_laddress;
E 3
		tdp->tb_flags = LE_64(mark);
		tdp->tb_addr = LE_64(addr);

		mark &= ~(TBF_BUFLEN | TBF_HDRFLG);
		dcp->dmac_size -= headerlen;
D 3
		dcp->dmac_address += headerlen;
E 3
I 3
		dcp->dmac_laddress += headerlen;
E 15
I 15
			mss = 0;
			mark = 0;
			if (lp->chip == CHIP_L1 && (flags & GEM_TXFLAG_INTR)) {
				mark |= TBF_DMAINT;
			}
			ASSERT(headerlen == 0);
			ASSERT(mark == 0);
#ifdef CONFIG_VLAN_HW
			if (vtag) {
				mark |= vtag;
			}
#endif
			mark |= hck_stuff << TBF_CKSUMOFF_SHIFT
			    | hck_start << TBF_PAYLDOFF_SHIFT
			    | TBF_CKSUM;
		}
E 15
E 3
	}

D 15
	tdp = &((struct tx_buffer_desc *)(dp->io_area +
D 2
	    IOA_TBD_OFFSET))[SLOT(slot + used, TX_RING_SIZE)];
E 2
I 2
D 3
	    IOA_TBD_OFFSET))[SLOT(slot + used, tx_ring_size)];
E 3
I 3
	    lp->tbd_offset))[SLOT(slot + used, tx_ring_size)];
E 3
E 2
	used++;
E 15
I 15
	tdp->tb_flags |= LE_64(TBF_EOP);
E 15

I 4
D 15
	ASSERT(dcp->dmac_laddress != 0);
E 4
	mark |= TBF_EOP | dcp->dmac_size;
D 3
	addr = dcp->dmac_address;
E 3
I 3
	addr = dcp->dmac_laddress;
E 3
	tdp->tb_flags = LE_64(mark);
	tdp->tb_addr = LE_64(addr);

E 15
#if DEBUG_LEVEL > 4
	if (mss) {
		cmn_err(CE_CONT,
		    "!%s: frags:%d, used:%d, addr:%p flags:%p",
		    __func__, frags, used,
		    LE_64(tdp->tb_addr), LE_64(tdp->tb_flags));
	}
#endif
	return (used);
}

static void
D 3
atge_tx_start(struct gem_dev *dp, int start_slot, int nslot)
E 3
I 3
atge_tx_start_1_1e(struct gem_dev *dp, int start_slot, int nslot)
E 3
{
D 2
	int	i;
	int	tail;
E 2
I 2
	int		tail;
E 2
	struct atge_dev	*lp = dp->private;

	DPRINTF(1, (CE_CONT, "!%s: %s: start:%d, nslot:%d",
	    dp->name, __func__, start_slot, nslot));

	atge_tx_desc_dma_sync(dp, start_slot, nslot);

	/* kick Tx dma engine */
	tail = SLOT(start_slot + nslot, dp->gc.gc_tx_ring_size);
D 3
	mutex_enter(&lp->mbox_lock);
	lp->tx_buffer_tail = tail;
D 2
	UPDATE_MBOX(dp, lp);
E 2
I 2
	UPDATE_MBOX(dp);
E 2
	mutex_exit(&lp->mbox_lock);
E 3
I 3
	if (lp->chip == CHIP_L1) {
		mutex_enter(&lp->mbox_lock);
		lp->tx_buffer_tail = tail;
D 10
		UPDATE_MBOX(dp);
E 10
I 10
		UPDATE_MBOX_1(dp);
E 10
		mutex_exit(&lp->mbox_lock);
	} else /* L1E */ {
		lp->tx_buffer_tail = tail;
		OUTL(dp, MBOX_1e, tail);
	}
E 3
}

I 11
#ifdef GEM_CONFIG_TX_HEAD_PTR
E 11
I 3
static uint_t
I 11
D 15
atge_tx_desc_head_1_1e(struct gem_dev *dp)
E 15
I 15
atge_tx_desc_head_1(struct gem_dev *dp)
E 15
{
	struct atge_dev	*lp = dp->private;

D 15
	membar_consumer();
E 15
	return (lp->tx_buffer_head);
}
I 15

static uint_t
atge_tx_desc_head_1e(struct gem_dev *dp)
{
	struct atge_dev	*lp = dp->private;

	lp->tx_buffer_head = INW(dp, TBDHEAD_1e);
	return (lp->tx_buffer_head);
}
E 15
#else
static uint_t
E 11
D 15
atge_tx_desc_stat_1_1e(struct gem_dev *dp, int slot, int ndesc)
E 15
I 15
atge_tx_desc_stat_1(struct gem_dev *dp, int slot, int ndesc)
E 15
{
	int	last;
I 6
D 15
	uint_t	buffer_head;
E 15
E 6
	struct atge_dev	*lp = dp->private;

	last = SLOT(slot + ndesc - 1, dp->gc.gc_tx_ring_size);
D 6
	if (INSIDE(last, lp->tx_buffer_head, lp->tx_buffer_tail)) {
E 6
I 6
D 15
	membar_consumer();
	buffer_head = lp->tx_buffer_head;
	if (INSIDE(last, buffer_head, lp->tx_buffer_tail)) {
E 15
I 15
	if (INSIDE(last, lp->tx_buffer_head, lp->tx_buffer_tail)) {
E 15
E 6
		DPRINTF(1, (CE_CONT,
		    "!%s: %s: slot:%d+%d tx_buffer:[%d, %d](%d)",
		    dp->name, __func__,
		    slot, ndesc,
D 6
		    lp->tx_buffer_head, lp->tx_buffer_tail,
		    lp->tx_buffer_tail - lp->tx_buffer_head));
E 6
I 6
D 15
		    buffer_head, lp->tx_buffer_tail,
		    lp->tx_buffer_tail - buffer_head));
E 15
I 15
		    lp->tx_buffer_head, lp->tx_buffer_tail,
		    lp->tx_buffer_tail - lp->tx_buffer_head));
E 15
E 6
		return (0);
	}
	return (GEM_TX_DONE);
}
I 15

static uint_t
atge_tx_desc_stat_1e(struct gem_dev *dp, int slot, int ndesc)
{
	int	last;
	struct atge_dev	*lp = dp->private;

	last = SLOT(slot + ndesc - 1, dp->gc.gc_tx_ring_size);
	if (INSIDE(last, lp->tx_buffer_head, lp->tx_buffer_tail)) {
		/* update tx_buffer_head and check again */
		lp->tx_buffer_head = INW(dp, TBDHEAD_1e);
		if (INSIDE(last, lp->tx_buffer_head, lp->tx_buffer_tail)) {
			DPRINTF(1, (CE_CONT,
			    "!%s: %s: slot:%d+%d tx_buffer:[%d, %d](%d)",
			    dp->name, __func__,
			    slot, ndesc,
			    lp->tx_buffer_head, lp->tx_buffer_tail,
			    lp->tx_buffer_tail - lp->tx_buffer_head));
			return (0);
		}
	}
	return (GEM_TX_DONE);
}
E 15
I 11
#endif /* GEM_CONFIG_TX_HEAD_PTR */
E 11

E 3
static void
D 3
atge_rx_desc_write(struct gem_dev *dp, int slot,
E 3
I 3
atge_tx_desc_dump_1_1e(struct gem_dev *dp)
{
	int	i;
	struct tx_buffer_desc	*tdp;
	struct atge_dev	*lp = dp->private;

D 4
	cmn_err(CE_CONT, "!%s: %s: tx_ring_size:%d",
	    dp->name, __func__, dp->gc.gc_tx_ring_size);
E 4
I 4
	cmn_err(CE_CONT, "!%s: %s: tx_ring_size:%d, head:%d, tail:%d",
	    dp->name, __func__, dp->gc.gc_tx_ring_size,
	    lp->tx_buffer_head, lp->tx_buffer_tail);
E 4

	for (i = 0; i < dp->gc.gc_tx_ring_size; i++) {
		tdp = &((struct tx_buffer_desc *)(dp->io_area +
		    lp->tbd_offset))[i];
D 4
		cmn_err(CE_CONT, "!%s: %llx %llx",
		    i, 
E 4
I 4
		cmn_err(CE_CONT, "!%d: %llx %llx",
D 8
		    i,
E 8
E 4
		    LE_64(tdp->tb_addr),
		    LE_64(tdp->tb_flags));
	}
}

static void
atge_tx_desc_init_1_1e(struct gem_dev *dp, int slot)
{
	/* do nothing */
}

static int
atge_tx_desc_write_2(struct gem_dev *dp, int slot,
	ddi_dma_cookie_t *dmacookie, int frags, uint64_t flags)
{
	int	i;
	size_t	len;
	size_t	rest;
	uint32_t	mark;
	struct atge_dev	*lp = dp->private;
	caddr_t		tbp;
	caddr_t		txbuf;
I 6
#ifdef CONFIG_VLAN_HW
	uint_t	vtag;
#endif
E 6

#if DEBUG_LEVEL > 2
	cmn_err(CE_CONT,
	    "!%s: %s time: %d, seqnum: %d, slot %d, frags: %d flags:0x%llx",
	    dp->name, __func__, ddi_get_lbolt(),
	    dp->tx_desc_tail, slot, frags, flags);
	for (i = 0; i < frags; i++) {
		cmn_err(CE_CONT, "!%d: addr: 0x%llx, len: 0x%x",
		    i, dmacookie[i].dmac_laddress, dmacookie[i].dmac_size);
	}
#endif
	/*
	 * write tx descriptor
	 */
I 7
#ifdef GEM3
	txbuf = dp->tx_curr_txbuf->txb_buf;
#else
E 7
D 4
#define GET_TXBUF(dp, sn)       \
E 4
I 4
#define	GET_TXBUF(dp, sn)	\
E 4
	(dp)->tx_buf[SLOT((dp)->tx_slots_base + (sn), (dp)->gc.gc_tx_buf_size)]

	txbuf = GET_TXBUF(dp, dp->tx_desc_tail).txb_buf;
I 7
#endif
E 7
	len = dmacookie->dmac_size;
	mark = len;
#ifdef CONFIG_VLAN_HW
	if (vtag = (flags & GEM_TXFLAG_VTAG) >> GEM_TXFLAG_VTAG_SHIFT) {
		vtag = ((vtag << 4) & 0xfff0)
		    | ((vtag >> 13) & 0x0007)
		    | ((vtag >> 9) & 0x8);
D 15
		mark |= TH_INSVTAG | (vtag << TH_VTAG_SHIFT);
E 15
I 15
		mark |= TH_INSVTAG | vtag << TH_VTAG_SHIFT;
E 15
	}
#endif
	tbp = dp->io_area + lp->tbd_offset + lp->tx_buffer_tail;
	*(uint32_t *)tbp = LE_32(mark);

	lp->tx_buffer_tail += 4;
	if (lp->tx_buffer_tail >= lp->tbd_size) {
		lp->tx_buffer_tail -= lp->tbd_size;
	}

	rest = len;
	len = min(len, lp->tbd_size - lp->tx_buffer_tail);
	tbp = dp->io_area + lp->tbd_offset + lp->tx_buffer_tail;
	bcopy(txbuf, tbp, len);
	rest -= len;
	if (rest) {
		bcopy(txbuf + len, dp->io_area + lp->tbd_offset, rest);
		lp->tx_buffer_tail = ROUNDUP(rest, 4);
	} else {
		lp->tx_buffer_tail += ROUNDUP(len, 4);
		if (lp->tx_buffer_tail >= lp->tbd_size) {
			lp->tx_buffer_tail -= lp->tbd_size;
		}
	}
	/* save the last position */
	ASSERT((lp->tx_buffer_tail & 3) == 0);
	lp->tbd_pos[slot] = lp->tx_buffer_tail;

	/* clear tx status descriptor */
	((uint32_t *)dp->tx_ring)[slot] = 0;

	DPRINTF(1, (CE_CONT, "!%s: %s: slot:%d len:%d+%d pos:0x%x",
	    dp->name, __func__, slot, len, rest, lp->tbd_pos[slot]));
	return (1);
}

static void
atge_tx_start_2(struct gem_dev *dp, int start_slot, int nslot)
{
	int	last;
	struct atge_dev	*lp = dp->private;

	last = SLOT(start_slot + nslot - 1, dp->gc.gc_tx_ring_size);
	OUTW(dp, TBDTAIL_2, lp->tbd_pos[last] / 4);

	DPRINTF(1, (CE_CONT, "!%s: %s: start_slot:%d nslot:%d, pos:0x%x",
	    dp->name, __func__, start_slot, nslot, lp->tbd_pos[last]));
}

static uint_t
atge_tx_desc_stat_2(struct gem_dev *dp, int slot, int ndesc)
{
	uint32_t	tsr;

	ASSERT(ndesc == 1);
	tsr = ((uint32_t *)dp->tx_ring)[slot];
	tsr = LE_32(tsr);

	DPRINTF(1, (CE_CONT, "!%s: %s: slot:%d tsr:0x%b",
	    dp->name, __func__, slot, tsr, TS_BITS));

	return ((tsr & TS_UPDATE) ? GEM_TX_DONE : 0);
}

static void
atge_tx_desc_init_2(struct gem_dev *dp, int slot)
{
	((uint32_t *)(dp->tx_ring))[slot] = 0;
}

I 7
#ifdef DEBUG_LEVEL
static int atge_tx_frags[MAXTXFRAGS];
#endif
D 10
#ifdef CONFIG_1C
E 10
static int
atge_tx_desc_write_1c(struct gem_dev *dp, int slot,
	ddi_dma_cookie_t *dmacookie, int frags, uint64_t flags)
{
	int	i;
D 15
	int	used;
E 15
I 15
	int	used = 0;
E 15
	uint_t	tx_ring_size = dp->gc.gc_tx_ring_size;
	uint64_t	headerlen;
	uint64_t	addr;
	uint64_t	mark;
I 15
	uint64_t	tmp;
E 15
#ifdef CONFIG_CKSUM_OFFLOAD
	uint64_t	mss;
	uint64_t	hck_start;
	uint64_t	hck_stuff;
	uint64_t	ip_header_len;
I 15
	int		lsolen = 0;
E 15
#endif
I 10
#ifdef CONFIG_VLAN_HW
D 15
	uint_t	vtag;
E 15
I 15
	uint64_t	vtag;
E 15
#endif
E 10
	struct atge_dev	*lp = dp->private;
	struct tx_buffer_desc	*tdp;
	ddi_dma_cookie_t	*dcp;
D 15
	uint_t		len;
E 15

D 15

D 8
#if DEBUG_LEVEL > 0
E 8
I 8
#if DEBUG_LEVEL > 2
E 15
I 15
#if DEBUG_LEVEL > 4
E 15
E 8
	cmn_err(CE_CONT,
	    "!%s: %s time: %d, seqnum: %d, slot %d, frags: %d flags:0x%llx",
	    dp->name, __func__, ddi_get_lbolt(),
	    dp->tx_desc_tail, slot, frags, flags);
	for (i = 0; i < frags; i++) {
D 15
		cmn_err(CE_CONT, "!%d: addr: 0x%llx, len: 0x%x",
		    i, dmacookie[i].dmac_laddress, dmacookie[i].dmac_size);
E 15
I 15
		cmn_err(CE_CONT, "!%d: addr: 0x%llx, len: 0x%x, lsolen: %d",
		    i, dmacookie[i].dmac_laddress, dmacookie[i].dmac_size,
		    dmacookie[i].dmac_type);
E 15
	}
#endif
#if DEBUG_LEVEL > 2
	if (flags & GEM_TXFLAG_INTR) {
		cmn_err(CE_CONT,
		    "!%s: %s time: %d, "
		    "seqnum: %d, slot %d, frags: %d flags:0x%llx",
		    dp->name, __func__, ddi_get_lbolt(),
		    dp->tx_desc_tail, slot, frags, flags);
	}
#endif
D 8
#if DEBUG_LEVEL > 0
	flags |= GEM_TXFLAG_INTR;
#endif
E 8
#ifdef DEBUG_LEVEL
	atge_tx_frags[min(frags, MAXTXFRAGS) - 1]++;
#endif
	/*
	 * write tx descriptor(s)
	 */
	mark = 0;
D 8
#ifdef CONFIG_ADAPTIVE_COALESCE
	/*
	 * XXX - don't use TBF_DMAINT or TBF_TXINT for L1E chipset.
	 * it caused tx-hang.
	 */
	if (lp->chip == CHIP_L1 && (flags & GEM_TXFLAG_INTR)) {
		mark |= TBF_DMAINT;
	}
#endif
E 8
	headerlen = 0;

#ifdef CONFIG_CKSUM_OFFLOAD
	/* Check for TCP Large Segmentation Offload */
	mss = (flags & GEM_TXFLAG_MSS) >> GEM_TXFLAG_MSS_SHIFT;
	hck_start = (flags & GEM_TXFLAG_HCKSTART) >> GEM_TXFLAG_HCKSTART_SHIFT;
	hck_stuff = (flags & GEM_TXFLAG_HCKSTUFF) >> GEM_TXFLAG_HCKSTUFF_SHIFT;

	ip_header_len = hck_start - sizeof (struct ether_header);

	if (mss) {
		uint64_t	tcp_header_len;

		tcp_header_len =
		    ((flags & GEM_TXFLAG_TCPHLEN)
		    >> GEM_TXFLAG_TCPHLEN_SHIFT) * 4;
D 15
		headerlen = tcp_header_len + hck_start;
E 15
I 15
		headerlen = hck_start + tcp_header_len;
E 15

D 15
		mark |= (mss << TPD_MSS_SHIFT)
D 10
		    | (tcp_header_len << TPD_CKOFF_SHIFT)
E 10
I 10
		    | (hck_start << TPD_CKOFF_SHIFT)
E 10
		    | TPD_LSO;
E 15
I 15
		lsolen = dmacookie[0].dmac_type;

E 15
		if (flags & GEM_TXFLAG_IPv4) {
D 15
			mark |= TPD_LSO_IPv4;
E 15
I 15
			if (lsolen == headerlen) {
#ifdef DEBUG_LEVEL
				cmn_err(CE_CONT, "!%s: no tcp payload",
				    __func__);
#endif
				mss = 0;
				goto hck_sum;
			}
			mark |= mss << TPD_MSS_SHIFT
			    | hck_start << TPD_CKOFF_SHIFT
			    | TPD_LSO | TPD_LSO_IPv4;
E 15
		}
		if (flags & GEM_TXFLAG_IPv6) {
D 15
			mark |= TPD_LSO_IPv6;
E 15
I 15
			if (lsolen == headerlen) {
				mss = 0;
				goto hck_sum;
			}
			mark |= mss << TPD_MSS_SHIFT
			    | hck_start << TPD_CKOFF_SHIFT
			    | TPD_LSO | TPD_LSO_IPv6;
E 15

			/*
			 * IPv6 needs extra tpd
			 */
			tdp = &((struct tx_buffer_desc *)(dp->io_area +
			    lp->tbd_offset))[SLOT(slot + used, tx_ring_size)];
			used++;

D 15
			len = 0;
			for (i = 0; i < frags; i++) {
				len += dmacookie[i].dmac_size;
			}
E 15
			tdp->tpd_flags = TPD_LSO | TPD_LSO_IPv6;
D 15
			tdp->tpd_addr = len;
E 15
I 15
			tdp->tpd_addr = lsolen;
E 15
		}

		/* TBF_CKSUM flag is not required */
		if (flags & GEM_TXFLAG_SWVTAG) {
			/* XXX - need to check if it is really required */
			mark |= TPD_ETHTYPE;
		}
I 15
		DPRINTF(4, (CE_CONT,
		    "headerlen:%d, tcphlen:%d, lsolen:%d, mss_frag:%d",
		    headerlen, tcp_header_len, lsolen,
		    (lsolen - hck_start - tcp_header_len) % mss));
E 15
	} else if (hck_start) {
I 15
hck_sum:
E 15
		/* XXX - don't use custom checksum for UDP */
D 15
		mark |= ((hck_stuff / 2) << TPD_CCSUM_OFF_SHIFT)
		    | ((hck_start / 2) << TPD_CKOFF_SHIFT)
E 15
I 15
		mark |= (hck_stuff >> 1) << TPD_CCSUM_OFF_SHIFT
		    | (hck_start >> 1) << TPD_CKOFF_SHIFT
E 15
		    | TPD_CCSUM;
	}
#endif /* CONFIG_CKSUM_OFFLOAD */
D 10
#ifdef CONFIG_HW_VTAG
E 10
I 10
#ifdef CONFIG_VLAN_HW
E 10
D 15
	if (vtag = (flags & GEM_TXFLAG_VTAG) >> GEM_TXFLAG_VTAG_SHIFT) {
I 10
#if 0
E 10
		vtag = (vtag << 4) | (vtag >> 13) | ((vtag >> 9) & 0x8);
I 10
#else
		vtag = BSWAP_16(vtag);
#endif
E 10
		mark |= TPD_INSVTAG | (vtag << TPD_VTAG_SHIFT);
E 15
I 15
	vtag = (flags >> GEM_TXFLAG_VTAG_SHIFT) & 0xffff;
	if (vtag) {
		vtag = TPD_INSVTAG | BSWAP_16(vtag) << TPD_VTAG_SHIFT;
		mark |= vtag;
E 15
	}
#endif
	dcp = &dmacookie[0];
D 15
	used = 0;
	for (i = 0; i < frags - 1; i++, dcp++) {
E 15
I 15
	for (i = 0; i < frags; i++, dcp++) {
E 15
		ASSERT(dcp->dmac_laddress != 0);
I 15
#ifdef DEBUG_LEVEL
		if (dcp->dmac_size == 0) {
			cmn_err(CE_CONT, "!%s: dmac_sizep == 0", __func__);
		}
#endif
E 15
		if (headerlen > 0 && headerlen < dcp->dmac_size) {
			tdp = &((struct tx_buffer_desc *)(dp->io_area +
			    lp->tbd_offset))[SLOT(slot + used, tx_ring_size)];
			used++;

D 15
			mark |= headerlen;
E 15
I 15
			tmp = mark | headerlen;
E 15
			addr = dcp->dmac_laddress;
D 8
			tdp->tpd_flags = LE_64(mark);
E 8
			tdp->tpd_addr = LE_64(addr);
I 8
D 15
			tdp->tpd_flags = LE_64(mark);
E 15
I 15
			tdp->tpd_flags = LE_64(tmp);
E 15
E 8

D 15
			mark &= ~(TPD_BUFLEN | TPD_LSO);
E 15
			dcp->dmac_size -= headerlen;
			dcp->dmac_laddress += headerlen;
I 15
			lsolen -= headerlen;

E 15
			headerlen = 0;
D 15
		} else if (headerlen >= dcp->dmac_size) {
E 15
I 15
			mark = 0;
#if DEBUG_LEVEL > 10
		} else if (headerlen > dcp->dmac_size) {
E 15
			/* no need to break the fragment in two pieces */
D 15
			headerlen -= dcp->dmac_size;
E 15
I 15
			cmn_err(CE_CONT, "!%s: header is fragmented",
			    __func__);
#endif
E 15
		}
D 15
		tdp = &((struct tx_buffer_desc *)(dp->io_area +
		    lp->tbd_offset))[SLOT(slot + used, tx_ring_size)];
		used++;
E 15

D 15
		mark |= dcp->dmac_size;
		addr = dcp->dmac_laddress;
D 8
		tdp->tpd_flags = LE_64(mark);
E 8
		tdp->tpd_addr = LE_64(addr);
I 8
		tdp->tpd_flags = LE_64(mark);
E 8

		mark &= ~(TPD_BUFLEN | TPD_LSO);
	}

	/* for the last fragment */
	if (headerlen > 0 && headerlen < dcp->dmac_size) {
		ASSERT(dcp->dmac_laddress != 0);
E 15
		tdp = &((struct tx_buffer_desc *)(dp->io_area +
		    lp->tbd_offset))[SLOT(slot + used, tx_ring_size)];
		used++;

D 15
		mark |= headerlen;
E 15
I 15
		tmp = mark | dcp->dmac_size;
E 15
		addr = dcp->dmac_laddress;
D 8
		tdp->tpd_flags = LE_64(mark);
E 8
		tdp->tpd_addr = LE_64(addr);
I 8
D 15
		tdp->tpd_flags = LE_64(mark);
E 15
I 15
		tdp->tpd_flags = LE_64(tmp);
		mark = 0;
E 15
E 8

D 15
		mark &= ~(TPD_BUFLEN | TPD_LSO);
		dcp->dmac_size -= headerlen;
		dcp->dmac_laddress += headerlen;
E 15
I 15
		headerlen -= min(headerlen, dcp->dmac_size);
		lsolen -= dcp->dmac_size;
		if (mss && lsolen == 0) {
			tdp->tpd_flags |= LE_64(TPD_EOP);

			mss = 0;
			ASSERT(headerlen == 0);
			ASSERT(mark == 0);
#ifdef CONFIG_VLAN_HW
			if (vtag) {
				mark |= vtag;
			}
#endif
			mark |= (hck_stuff >> 1) << TPD_CCSUM_OFF_SHIFT
			    | (hck_start >> 1) << TPD_CKOFF_SHIFT
			    | TPD_CCSUM;
		}
E 15
	}
I 15
	tdp->tpd_flags |= LE_64(TPD_EOP);
E 15

D 15
	tdp = &((struct tx_buffer_desc *)(dp->io_area +
	    lp->tbd_offset))[SLOT(slot + used, tx_ring_size)];
	used++;

	ASSERT(dcp->dmac_laddress != 0);
	mark |= TPD_EOP | dcp->dmac_size;
	addr = dcp->dmac_laddress;
D 8
	tdp->tpd_flags = LE_64(mark);
E 8
	tdp->tpd_addr = LE_64(addr);
I 8
	tdp->tpd_flags = LE_64(mark);
E 8

E 15
#if DEBUG_LEVEL > 4
	if (mss) {
		cmn_err(CE_CONT,
		    "!%s: frags:%d, used:%d, addr:%p flags:%p",
		    __func__, frags, used,
		    LE_64(tdp->tpd_addr), LE_64(tdp->tpd_flags));
	}
#endif
	return (used);
}

E 7
static void
I 7
atge_tx_start_1c(struct gem_dev *dp, int start_slot, int nslot)
{
	int		tail;
	struct atge_dev	*lp = dp->private;

D 8
	DPRINTF(0, (CE_CONT, "!%s: %s: start:%d, nslot:%d",
E 8
I 8
	DPRINTF(2, (CE_CONT, "!%s: %s: start:%d, nslot:%d",
E 8
	    dp->name, __func__, start_slot, nslot));

	atge_tx_desc_dma_sync(dp, start_slot, nslot);

	/* kick Tx dma engine */
	tail = SLOT(start_slot + nslot, dp->gc.gc_tx_ring_size);
	lp->tx_buffer_tail = tail;
	OUTL(dp, MB_PRIO_PROD_IDX, tail << 16);
}

I 10
#ifdef GEM_CONFIG_TX_HEAD_PTR
E 10
static uint_t
I 10
atge_tx_desc_head_1c(struct gem_dev *dp)
{
	struct atge_dev	*lp = dp->private;
D 11

E 11
I 11
D 15
#if 0
E 15
I 15

E 15
E 11
	lp->tx_buffer_head = INL(dp, MB_PRIO_CONS_IDX) >> 16;
D 11

E 11
I 11
D 15
#endif
E 15
E 11
	return (lp->tx_buffer_head);
}
#else
static uint_t
E 10
atge_tx_desc_stat_1c(struct gem_dev *dp, int slot, int ndesc)
{
	int	last;
D 15
	uint_t	buffer_head;
E 15
	struct atge_dev	*lp = dp->private;

D 8
	DPRINTF(0, (CE_CONT, "!%s: %s: slot:%d, ndesc:%d",
E 8
I 8
	DPRINTF(2, (CE_CONT, "!%s: %s: slot:%d, ndesc:%d",
E 8
	    dp->name, __func__, slot, ndesc));

	last = SLOT(slot + ndesc - 1, dp->gc.gc_tx_ring_size);
D 15
	membar_consumer();
	buffer_head = lp->tx_buffer_head;
	if (INSIDE(last, buffer_head, lp->tx_buffer_tail)) {
D 8
		DPRINTF(0, (CE_CONT,
E 8
I 8
		DPRINTF(2, (CE_CONT,
E 8
		    "!%s: %s: slot:%d+%d tx_buffer:[%d, %d](%d)",
		    dp->name, __func__,
		    slot, ndesc,
		    buffer_head, lp->tx_buffer_tail,
		    lp->tx_buffer_tail - buffer_head));
		return (0);
E 15
I 15
	if (INSIDE(last, lp->tx_buffer_head, lp->tx_buffer_tail)) {
		/* update tx_buffer_head and check again */
		lp->tx_buffer_head = INL(dp, MB_PRIO_CONS_IDX) >> 16;
		if (INSIDE(last, lp->tx_buffer_head, lp->tx_buffer_tail)) {
			DPRINTF(2, (CE_CONT,
			    "!%s: %s: slot:%d+%d tx_buffer:[%d, %d](%d)",
			    dp->name, __func__,
			    slot, ndesc,
			    lp->tx_buffer_head, lp->tx_buffer_tail,
			    lp->tx_buffer_tail - lp->tx_buffer_head));
			return (0);
		}
E 15
	}
	return (GEM_TX_DONE);
}
I 10
#endif
E 10

static void
atge_tx_desc_dump_1c(struct gem_dev *dp)
{
	int	i;
	struct tx_buffer_desc	*tdp;
	struct atge_dev	*lp = dp->private;

	cmn_err(CE_CONT, "!%s: %s: tx_ring_size:%d, head:%d, tail:%d",
	    dp->name, __func__, dp->gc.gc_tx_ring_size,
	    lp->tx_buffer_head, lp->tx_buffer_tail);

	for (i = 0; i < dp->gc.gc_tx_ring_size; i++) {
		tdp = &((struct tx_buffer_desc *)(dp->io_area +
		    lp->tbd_offset))[i];
		cmn_err(CE_CONT, "!%d: %llx %llx",
		    i,
		    LE_64(tdp->tpd_flags),
		    LE_64(tdp->tpd_addr));
	}
}

static void
atge_tx_desc_init_1c(struct gem_dev *dp, int slot)
{
	/* do nothing */
}

D 10
#endif
E 10
static void
E 7
atge_rx_desc_write_1(struct gem_dev *dp, int slot,
E 3
	ddi_dma_cookie_t *dmacookie, int frags)
{
D 6
	uint64_t	hi_addr;
E 6
I 6
	uint64_t	dmaaddr;
	uint32_t	hi_addr;
E 6
	uint32_t	lo_addr;
	uint64_t	len;
	struct atge_dev	*lp = dp->private;
	struct rx_buffer_desc	*rbdp;

#if DEBUG_LEVEL > 2
{
	int	i;

	cmn_err(CE_CONT,
	    "!%s: %s: seqnum: %d, slot %d, frags: %d",
	    dp->name, __func__, dp->rx_active_tail, slot, frags);
	for (i = 0; i < frags; i++) {
		cmn_err(CE_CONT, "!%d: addr: 0x%llx, len: 0x%x",
		    i, dmacookie[i].dmac_laddress, dmacookie[i].dmac_size);
	}
}
#endif
	/*
	 * write a RX descriptor
	 */
D 3
	rbdp = &((struct rx_buffer_desc *)(dp->io_area + IOA_RBD_OFFSET))[slot];
E 3
I 3
	rbdp = &((struct rx_buffer_desc *)(dp->io_area + lp->rbd_offset))[slot];
E 3

D 3
	hi_addr = dmacookie->dmac_address;
E 3
I 3
D 6
	hi_addr = dmacookie->dmac_laddress;
E 3
	lo_addr = (uint32_t)hi_addr;
D 3
	hi_addr >>= 32;
E 3
I 3
	hi_addr >>= 32U;
E 6
I 6
	dmaaddr = dmacookie->dmac_laddress;
	lo_addr = (uint32_t)dmaaddr;
	hi_addr = (uint32_t)(dmaaddr >> 32);
E 6
E 3
	len = dmacookie->dmac_size;

	rbdp->rb_addr = LE_32(lo_addr);
	rbdp->rb_haddr = LE_32(hi_addr);
	rbdp->rb_flags = LE_32(len);
}

static void
D 3
atge_rx_start(struct gem_dev *dp, int start_slot, int nslot)
E 3
I 3
atge_rx_start_1(struct gem_dev *dp, int start_slot, int nslot)
E 3
{
	int	tail;
	struct atge_dev	*lp = dp->private;

	DPRINTF(1, (CE_CONT, "!%s: %s: start:%d, nslot:%d",
	    dp->name, __func__, start_slot, nslot));

D 3
	atge_rbd_desc_dma_sync(dp, start_slot, nslot);
E 3
I 3
	atge_rbd_desc_dma_sync_1(dp, start_slot, nslot);
E 3

	tail = SLOT(start_slot + nslot, dp->gc.gc_rx_ring_size);
	mutex_enter(&lp->mbox_lock);
	lp->rx_buffer_tail = tail;
D 2
	UPDATE_MBOX(dp, lp);
E 2
I 2
D 10
	UPDATE_MBOX(dp);
E 10
I 10
	UPDATE_MBOX_1(dp);
E 10
E 2
	mutex_exit(&lp->mbox_lock);
}

D 3
static uint_t
atge_tx_desc_stat(struct gem_dev *dp, int slot, int ndesc)
{
	int	head;
	struct atge_dev	*lp = dp->private;

	if (INSIDE(slot, lp->tx_buffer_head, lp->tx_buffer_tail)) {
		DPRINTF(1, (CE_CONT, "!%s: %s: new tx_buffer_head:%d",
		    dp->name, __func__, lp->tx_buffer_head));
		return (0);
	}
	return (GEM_TX_DONE);
}

E 3
static uint64_t
D 3
atge_rx_desc_stat(struct gem_dev *dp, int slot, int ndesc)
E 3
I 3
atge_rx_desc_stat_1(struct gem_dev *dp, int slot, int ndesc)
E 3
{
	int		retry;
	int		head;
	uint_t		index;
	uint64_t	len;
	uint64_t	rsd0;
	uint64_t	rsd1;
	uint64_t	ret;
	struct rx_status_desc	*rsdp;
	struct atge_dev	*lp = dp->private;

	retry = 0;
	ret = 0;
again:
	rsdp = &((struct rx_status_desc *)(dp->rx_ring))[lp->rx_status_head];
	rsd0 = rsdp->rsd0;
	rsd1 = rsdp->rsd1;

	rsd0 = LE_64(rsd0);
	rsd1 = LE_64(rsd1);

	if ((rsd0 & RSD0_OWN) == 0) {
		/* not yet received */
D 3
		return (ret);
E 3
I 3
		return (0);
E 3
	}

	DPRINTF(1, (CE_CONT,
	    "!%s: %s: slot:%x, %llx, %llx, flags:%b, rsd/rbd index:0x%x",
	    dp->name, __func__, slot, rsd0, rsd1,
	    (uint32_t)(rsd1 & RSD1_FLAGS), RSD1_BITS,
D 3
	    INL(dp, CURR_RBD_RSD)));
E 3
I 3
	    INL(dp, CURR_RBD_RSD_1)));
E 3

	/* invalidate the rx status descriptor */
	rsdp->rsd0 = 0;
	ret = GEM_RX_DONE;

	if ((rsd0 & RSD0_NUM) != 1) {
		if (retry++ < 1) {
			gem_rx_desc_dma_sync(dp,
			    slot, 1, DDI_DMA_SYNC_FORKERNEL);
			goto again;
		}
I 4
		cmn_err(CE_WARN, "!%s: %s: (rsd0(%llx) & RSD0_NUM) != 1",
		    dp->name, __func__, rsd0);
E 4
		lp->need_to_reset = B_TRUE;
D 3
		return (ret | GEM_RX_ERR);
E 3
I 3
		return (GEM_RX_DONE | GEM_RX_ERR);
E 3
	}

	index = (rsd0 & RSD0_INDEX) >> RSD0_INDEX_SHIFT;
	if (slot != index) {
D 4
		cmn_err(CE_WARN, "%s: %s: slot(%d) != index(%d)",
E 4
I 4
		cmn_err(CE_WARN, "!%s: %s: slot(%d) != index(%d)",
E 4
		    dp->name, __func__, slot, index);
		lp->need_to_reset = B_TRUE;
D 3
		return (ret | GEM_RX_ERR);
E 3
I 3
		return (GEM_RX_DONE | GEM_RX_ERR);
E 3
	}

	/* now current slot == index in current return descriptor */

D 6
	/* increase rx_status_head to point the next descriptor */
E 6
I 6
	/*
	 * Increase rx_status_head to point the next descriptor,
	 * we don't update MBOX here. it have to be updated when new
	 * rx buffers are prepared later. we also don't use mutex lock,
	 * because an assignment of a 4 byte word is naturally atomic,
	 * the modification is only performed in this function and
	 * intrlock is held.
	 */
E 6
	lp->rx_status_head = SLOT(index + 1, dp->gc.gc_rx_ring_size);

I 2
D 6
#ifndef USE_GETSTAT_RX
E 6
I 6
#ifdef NEVER
E 6
E 2
	if (rsd1 & (RSD1_E_TRUNC | RSD1_E_OVF |
	    RSD1_E_RUNT | RSD1_E_CODE | RSD1_E_CRC)) {
		DPRINTF(0, (CE_CONT,
		    "!%s: %s: slot:%x, %llx, %llx, flags:%b, "
		    "rsd/rbd index:0x%x",
		    dp->name, __func__, slot, rsd0, rsd1,
		    (uint32_t)(rsd1 & RSD1_FLAGS), RSD1_BITS,
D 3
		    INL(dp, CURR_RBD_RSD)));
E 3
I 3
		    INL(dp, CURR_RBD_RSD_1)));
E 3

		ret |= GEM_RX_ERR;
D 2

E 2
		dp->stats.errrcv++;
		if (rsd1 & RSD1_E_TRUNC) {
			dp->stats.frame_too_long++;
D 2
		} if (rsd1 & RSD1_E_OVF) {
E 2
I 2
		} else if (rsd1 & RSD1_E_OVF) {
E 2
			dp->stats.overflow++;
		} else if (rsd1 & RSD1_E_RUNT) {
			dp->stats.runt++;
		} else if (rsd1 & RSD1_E_CODE) {
			dp->stats.frame++;
		} else if (rsd1 & RSD1_E_CRC) {
			dp->stats.crc++;
		} else {
			dp->stats.rcv_internal_err++;
		}
	}
I 2
#endif /* USE_GETSTAT_RX */
E 2

	len = (rsd0 & RSD0_LEN) >> RSD0_LEN_SHIFT;
	if (len >= ETHERFCSL) {
		len -= ETHERFCSL;
	}
#ifdef CONFIG_CKSUM_OFFLOAD
D 7
	if (rsd1 & RSD1_IPv4) {
E 7
I 7
	if ((rsd1 & RSD1_IPv4) &&
	    (rsd1 & (RSD1_E_IPCHKSUM | RSD1_E_L4CHKSUM)) == 0) {
E 7
		/* IPv4 packets, full checksum */
D 7
		if ((rsd1 & RSD1_E_IPCHKSUM) == 0) {
			ret |= GEM_RX_CKSUM_IPv4;
E 7
I 7
		ret |= GEM_RX_CKSUM_IPv4;
		if (rsd1 & RSD1_TCP) {
			ret |= GEM_RX_CKSUM_TCP;
		} else if (rsd1 & RSD1_UDP) {
			ret |= GEM_RX_CKSUM_UDP;
E 7
		}
D 7
		if ((rsd1 & RSD1_E_L4CHKSUM) == 0) {
			if (rsd1 & RSD1_TCP) {
				ret |= GEM_RX_CKSUM_TCP;
			} else if (rsd1 & RSD1_UDP) {
				ret |= GEM_RX_CKSUM_UDP;
			}
		}
	} else {
		/* non IPv4 packets, partial checksum */
		ret |= ((rsd0 & RSD0_CKSUM) >> RSD0_CKSUM_SHIFT)
		    << GEM_RX_CKSUM_SHIFT;
E 7
	}
#endif /* CONFIG_CKSUM_OFFLOAD */
	return (ret | len);
}

static void
I 7
atge_rx_desc_init_1(struct gem_dev *dp, int slot)
{
	struct rx_status_desc	*rsdp;

	rsdp = &((struct rx_status_desc *)(dp->rx_ring))[slot];
	rsdp->rsd0 = 0;
}

static void
E 7
D 3
atge_tx_desc_init(struct gem_dev *dp, int slot)
E 3
I 3
atge_rx_desc_write_2(struct gem_dev *dp, int slot,
	ddi_dma_cookie_t *dmacookie, int frags)
E 3
{
D 3
	/* do nothing */
E 3
I 3
	uint32_t	*rbdp;
	struct atge_dev	*lp = dp->private;

#if DEBUG_LEVEL > 2
{
	int	i;

	cmn_err(CE_CONT,
	    "!%s: %s: seqnum: %d, slot %d, frags: %d",
	    dp->name, __func__, dp->rx_active_tail, slot, frags);
	for (i = 0; i < frags; i++) {
		cmn_err(CE_CONT, "!%d: addr: 0x%llx, len: 0x%x",
		    i, dmacookie[i].dmac_laddress, dmacookie[i].dmac_size);
	}
E 3
}
I 3
#endif
	/*
	 * write a RX descriptor
	 */
	rbdp = (uint32_t *)(dp->io_area + lp->rbd_offset + slot * 1536);
E 3

I 3
	rbdp[0] = 0;
}

E 3
static void
D 3
atge_rx_desc_init(struct gem_dev *dp, int slot)
E 3
I 3
atge_rx_start_2(struct gem_dev *dp, int start_slot, int nslot)
E 3
{
I 3
D 7
	int	tail;
E 7
	struct atge_dev	*lp = dp->private;

	DPRINTF(1, (CE_CONT, "!%s: %s: start:%d, nslot:%d",
	    dp->name, __func__, start_slot, nslot));

	atge_rbd_desc_dma_sync_2(dp, start_slot, nslot, DDI_DMA_SYNC_FORDEV);

D 7
	tail = SLOT(start_slot + nslot, dp->gc.gc_rx_ring_size);
	OUTW(dp, RBDTAIL_2, tail);
	lp->rx_buffer_tail = tail;
E 7
I 7
	OUTW(dp, RBDTAIL_2,
D 10
	    lp->rx_buffer_tail =
E 10
	    SLOT(start_slot + nslot, dp->gc.gc_rx_ring_size));
E 7
}


static uint64_t
atge_rx_desc_stat_2(struct gem_dev *dp, int slot, int ndesc)
{
	uint64_t	len;
	off_t		io_offset;
	uint32_t	rs0;
	uint32_t	rs1;
	uint32_t	*rsp;
	struct atge_dev	*lp = dp->private;

	/* XXX - don't use ndesc, it is not valid */
	atge_rbd_desc_dma_sync_2(dp, slot, 1, DDI_DMA_SYNC_FORKERNEL);

	io_offset = lp->rbd_offset + lp->rx_buffer_head * 1536;

	rsp = (uint32_t *)(dp->io_area + io_offset);
	rs0 = rsp[0];
	rs0 = LE_32(rs0);
	rs1 = rsp[1];
	rs1 = LE_32(rs1);
	if ((rs0 & RS_UPDATE) == 0) {
		return (0);
	}

	DPRINTF(1, (CE_CONT,
	    "!%s: %s: slot:%x flags:%b %x",
	    dp->name, __func__, slot, rs0, RS_BITS, rs1));

	len = rs0 & RS_PKTSIZE;
	if (len >= ETHERFCSL) {
		len -= ETHERFCSL;
	}
#ifdef CONFIG_VLAN_HW
	if (rs0 & RS_VLAN) {
		len |= (((uint64_t)rs1 & 0xfff0ULL) >> 4) << GEM_RX_VID_SHIFT;
D 4
		len |= (((uint64_t)rs1 & 0x0007ULL) << GEM_RX_PRI_SHIFT;
E 4
I 4
		len |= ((uint64_t)rs1 & 0x0007ULL) << GEM_RX_PRI_SHIFT;
E 4
		len |= (((uint64_t)rs1 & 0x0008ULL) >> 3) << GEM_RX_CFI_SHIFT;
	}
#endif
	return (GEM_RX_DONE | len);
}

static mblk_t *
atge_get_packet_2(struct gem_dev *dp, struct rxbuf *rbp, size_t pkt_len)
{
	mblk_t		*mp;
	off_t		io_offset;
	uint32_t	rs0;
	uint32_t	rs1;
	uint32_t	*rsp;
	struct atge_dev	*lp = dp->private;

	/* check rx status desc */
	mp = NULL;
	io_offset = lp->rbd_offset + lp->rx_buffer_head * 1536;

	rsp = (uint32_t *)(dp->io_area + io_offset);
	rs0 = rsp[0];
	rs0 = LE_32(rs0);
	rs1 = rsp[1];
	rs1 = LE_32(rs1);

	DPRINTF(1, (CE_CONT,
	    "!%s: %s: %b %x plen:%d",
	    dp->name, __func__, rs0, RS_BITS, rs1, (int)pkt_len));

	if ((rs0 & RS_OK) == 0) {
D 7
		DPRINTF(0, (CE_CONT,
E 7
I 7
		DPRINTF(1, (CE_CONT,
E 7
D 6
		    "!%s: %s: errord pkt, %b %x plen:%d",
E 6
I 6
		    "!%s: %s: errored pkt, %b %x plen:%d",
E 6
		    dp->name, __func__,
		    rs0, RS_BITS, rs1, (int)pkt_len));

		if (rs0 & (RS_TRUNC | RS_FRAG |
		    RS_RUNT | RS_CODE | RS_CRC)) {
			dp->stats.errrcv++;
			if (rs0 & RS_TRUNC) {
				dp->stats.frame_too_long++;
			}
			if (rs0 & (RS_RUNT | RS_FRAG)) {
				dp->stats.runt++;
			}
			if (rs0 & RS_CODE) {
				dp->stats.frame++;
			}
			if (rs0 & (RS_CRC | RS_FRAG)) {
				dp->stats.crc++;
			}
		} else {
			dp->stats.errrcv++;
			dp->stats.rcv_internal_err++;
		}
		goto x;
	}

	/* aquire packet buffer */
	if ((mp = allocb(pkt_len, BPRI_MED)) == NULL) {
		/*
		 * No receive buffer, OS resource exaust
		 */
		dp->stats.errrcv++;
		dp->stats.norcvbuf++;
		goto x;
	}

	mp->b_wptr = mp->b_rptr + pkt_len;
D 4
	bcopy(dp->io_area + io_offset + sizeof(uint32_t) * 2,
E 4
I 4
	bcopy(dp->io_area + io_offset + sizeof (uint32_t) * 2,
E 4
	    mp->b_rptr, pkt_len);
x:
	lp->rx_buffer_head =
	    SLOT(lp->rx_buffer_head + 1, dp->gc.gc_rx_ring_size);

	return (mp);
}

static void
atge_rx_desc_init_2(struct gem_dev *dp, int slot)
{
	uint32_t	*rsp;
	struct atge_dev	*lp = dp->private;

	rsp = (uint32_t *)(dp->io_area + lp->rbd_offset + slot * 1536);
	rsp[0] = 0;
}

static void
atge_rx_desc_write_1e(struct gem_dev *dp, int slot,
	ddi_dma_cookie_t *dmacookie, int frags)
{
	/* EMPTY */
}

I 6
static void
atge_rxf_dump_1e(struct gem_dev *dp, uint8_t *start, size_t len)
{
	int	i;

D 7
	for (i = 0; i < len; i +=8 ) {
E 7
I 7
	for (i = 0; i < len; i += 8) {
E 7
		cmn_err(CE_CONT,
		    "%d: %02x %02x %02x %02x %02x %02x %02x %02x",
		    i,
		    start[i+0], start[i+1], start[i+2], start[i+3],
		    start[i+4], start[i+5], start[i+6], start[i+7]);
	}
}

E 6
static mblk_t *
atge_get_packet_1e(struct gem_dev *dp, struct rxbuf *rbp, size_t pkt_len)
{
	int		index;
	int		head;
	int		tail;
	uint64_t	len;
	mblk_t		*mp;
	off_t		io_offset;
	uint64_t	rsd0;
	uint64_t	rsd1;
	struct l2_rxf	*rxfp;
E 3
	struct rx_status_desc	*rsdp;
I 3
	struct atge_dev	*lp = dp->private;
E 3

I 3
	mp = NULL;
	rxfp = &lp->rxf[0];
	index = rxfp->rf_curr_ring;

D 6
	/* check rx status desc */
E 6
I 6
	/*
	 * get current rx status desc. No need to flush io cache lines for
	 * that here. We have flushed in rx_desc_stat_1e.
	 */
E 6
	io_offset = lp->rxf_offset[0][index] + rxfp->rf_head;
	rsdp = (struct rx_status_desc *)(dp->io_area + io_offset);
	rsd0 = rsdp->rsd0;
	rsd1 = rsdp->rsd1;

	rsd0 = LE_64(rsd0);
	rsd1 = LE_64(rsd1);

	len = (rsd0 & RSD0_LEN) >> RSD0_LEN_SHIFT;

	DPRINTF(1, (CE_CONT,
	    "!%s: %s: %llx, %llx, flags:%b, pkt_len:%d",
	    dp->name, __func__, rsd0, rsd1,
	    (uint32_t)(rsd1 & RSD1_FLAGS), RSD1_BITS, (int)pkt_len));
D 6

E 6
I 6
#ifdef notdef
E 6
	if ((uint16_t)(rsd0 & RSD0_SEQNUM) != rxfp->rf_seqnum) {
D 4
		lp->need_to_reset = B_TRUE;
E 4
D 6
		cmn_err(CE_WARN, "!%s: %s: %d != %d",
E 6
I 6
		cmn_err(CE_WARN,
		    "!%s: %s: wrong seq num, (actual) %d != (expected) %d, "
		    "rsg0:%llx, rsd1:%llx, flags:%b, pkt_len:%d, "
		    "rxf%d + head:%d",
E 6
		    dp->name, __func__,
D 6
		    (int)(rsd0 & RSD0_SEQNUM), rxfp->rf_seqnum);
E 6
I 6
		    (int)(rsd0 & RSD0_SEQNUM), rxfp->rf_seqnum,
		    rsd0, rsd1,
		    (uint32_t)(rsd1 & RSD1_FLAGS), RSD1_BITS, (int)pkt_len,
		    index, rxfp->rf_head);
D 14
		atge_rxf_dump_1e(dp, dp->io_area + (io_offset - 64), 128);
E 14
I 14
		atge_rxf_dump_1e(dp,
		    (uint8_t *)dp->io_area + (io_offset - 64), 128);
E 14
E 6
I 4
		lp->need_to_reset = B_TRUE;
E 4
		goto x;
	}
	rxfp->rf_seqnum++;
D 6

	if (rsd1 & RSD1_ERR) {
E 6
I 6
#endif
D 7
	if (rsd1 & 
E 7
I 7
	if (rsd1 &
E 7
	    (RSD1_E_DES_ADDR | RSD1_E_LEN | RSD1_E_TRUNC | RSD1_E_OVF |
	    RSD1_E_RUNT | RSD1_E_DRIBBLE | RSD1_E_CODE | RSD1_E_CRC)) {
E 6
D 7
		DPRINTF(0, (CE_CONT,
E 7
I 7
		DPRINTF(1, (CE_CONT,
E 7
D 6
		    "!%s: %s: %llx, %llx, flags:%b",
E 6
I 6
		    "!%s: %s: rx errored packet: %llx, %llx, flags:%b",
E 6
		    dp->name, __func__, rsd0, rsd1,
		    (uint32_t)(rsd1 & RSD1_FLAGS), RSD1_BITS));
D 6
#ifndef USE_GETSTAT_RX
E 6
I 6
#ifdef NEVER
E 6
		if (rsd1 & (RSD1_E_TRUNC | RSD1_E_OVF |
		    RSD1_E_RUNT | RSD1_E_CODE | RSD1_E_CRC)) {
			dp->stats.errrcv++;
			if (rsd1 & RSD1_E_TRUNC) {
				dp->stats.frame_too_long++;
			}
			if (rsd1 & RSD1_E_OVF) {
				dp->stats.overflow++;
			}
			if (rsd1 & RSD1_E_RUNT) {
				dp->stats.runt++;
			}
			if (rsd1 & RSD1_E_CODE) {
				dp->stats.frame++;
			}
			if (rsd1 & RSD1_E_CRC) {
				dp->stats.crc++;
			}
		} else {
			dp->stats.errrcv++;
			dp->stats.rcv_internal_err++;
		}
D 6
#endif /* USE_GETSTAT_RX */
E 6
I 6
#endif
E 6
		goto x;
	}

	/* aquire packet buffer */
	if ((mp = allocb(pkt_len, BPRI_MED)) == NULL) {
		/*
		 * No receive buffer, OS resource exaust
		 */
		dp->stats.errrcv++;
		dp->stats.norcvbuf++;
		goto x;
	}

	mp->b_wptr = mp->b_rptr + pkt_len;
D 6
	io_offset += sizeof (struct rx_status_desc);
D 4
	ddi_dma_sync(dp->desc_dma_handle,
	    (off_t)io_offset, pkt_len, DDI_DMA_SYNC_FORKERNEL);
E 4
I 4
	atge_ioarea_dma_sync(dp, io_offset, pkt_len, DDI_DMA_SYNC_FORKERNEL);
E 4
	bcopy(dp->io_area + io_offset, mp->b_rptr, pkt_len);
E 6
I 6
	bcopy(dp->io_area + io_offset + sizeof (struct rx_status_desc),
	    mp->b_rptr, pkt_len);
E 6
x:
D 6
	/* set new limit */
E 6
I 6
	/* update next rx buffer offset in the rx ring */
E 6
	rxfp->rf_head += ROUNDUP(sizeof (struct rx_status_desc) + len, 32);
	if (rxfp->rf_head >= lp->rxf_buf_hiwat) {
D 6
		DPRINTF(0, (CE_CONT, "!%s: %s: switching rx0 ring %d -> %d",
E 6
I 6
		DPRINTF(4, (CE_CONT, "!%s: %s: switching rx0 ring %d -> %d",
E 6
		    dp->name, __func__,
		    rxfp->rf_curr_ring, rxfp->rf_curr_ring ^ 1));

		/* reset current ring */
D 6
		*((uint32_t *)(dp->io_area + lp->rxf_mb_offset[0][index])) = 0;
E 6
I 6
		io_offset = lp->rxf_mb_offset[0][index];
		*((uint32_t *)(dp->io_area + io_offset)) = 0;
		atge_ioarea_dma_sync(dp, io_offset, sizeof (uint32_t),
		    DDI_DMA_SYNC_FORDEV);

		/* notify the nic that the rx ring become available again */
E 6
		OUTB(dp, RXF_RING_VALID_1e + index, 1);

		/* select the next ring */
		rxfp->rf_curr_ring ^= 1;
		rxfp->rf_head = 0;
		rxfp->rf_tail = 0;
	}

	return (mp);
}

static uint64_t
atge_rx_desc_stat_1e(struct gem_dev *dp, int slot, int ndesc)
{
I 6
	int		i;
E 6
	uint64_t	len;
	uint64_t	ret;
	int		tail;
	struct l2_rxf	*rxfp;
	uint_t		index;
	off_t		io_offset;
	uint64_t	rsd0;
	uint64_t	rsd1;
	struct rx_status_desc	*rsdp;
	struct atge_dev	*lp = dp->private;

	ret = GEM_RX_DONE;

	rxfp = &lp->rxf[0];
	index = rxfp->rf_curr_ring;

	if (rxfp->rf_head < rxfp->rf_tail) {
D 6
		/* we have received packets */
E 6
I 6
		/* we have remained packets in current rx ring */
E 6
		io_offset = lp->rxf_offset[0][index] + rxfp->rf_head;
D 6
		goto done;
E 6
I 6
		goto read_rx_desc;
E 6
	}

	/* get new tail position */
	io_offset = lp->rxf_mb_offset[0][index];
	atge_ioarea_dma_sync(dp, io_offset, sizeof (uint32_t),
	    DDI_DMA_SYNC_FORKERNEL);
	tail = *((uint32_t *)(dp->io_area + io_offset));
	tail = LE_32(tail);

	/* save the new tail */
	rxfp->rf_tail = tail;

D 6
	if (rxfp->rf_head >= tail) {
E 6
I 6
	if (rxfp->rf_head == tail) {
E 6
		/* not yet received */
		return (0);
I 6
	} else if (rxfp->rf_head > tail) {
		cmn_err(CE_WARN,
		    "!%s: wrong rx packet offset, "
		    "rx:%d head:%x tail:%x hiwat:%x",
		    dp->name, index, rxfp->rf_head, rxfp->rf_tail,
D 7
		     lp->rxf_buf_hiwat);
E 7
I 7
		    lp->rxf_buf_hiwat);

		/* XXX - terminate gem_receive() immediately */
E 7
		lp->need_to_reset = B_TRUE;
D 7
		return (GEM_RX_ERR);
E 7
I 7
		return (0);
E 7
E 6
	}

	/* we have new packets */
D 6
	io_offset = lp->rxf_offset[0][index] + rxfp->rf_head;
	atge_ioarea_dma_sync(dp, io_offset,
	    sizeof (struct rx_status_desc), DDI_DMA_SYNC_FORKERNEL);
done:
	rsdp = (struct rx_status_desc *)(dp->io_area + io_offset);
E 6
I 6
	for (i = 0; i < 2; i++) {
		io_offset = lp->rxf_offset[0][index] + rxfp->rf_head;
		atge_ioarea_dma_sync(dp,
		    io_offset, rxfp->rf_tail - rxfp->rf_head,
		    DDI_DMA_SYNC_FORKERNEL);
read_rx_desc:
		rsdp = (struct rx_status_desc *)(dp->io_area + io_offset);
E 6

D 6
	rsd0 = rsdp->rsd0;
	rsd1 = rsdp->rsd1;
E 6
I 6
		rsd0 = rsdp->rsd0;
		rsd1 = rsdp->rsd1;
E 6

D 6
	rsd0 = LE_64(rsd0);
	rsd1 = LE_64(rsd1);
E 6
I 6
		rsd0 = LE_64(rsd0);
		rsd1 = LE_64(rsd1);
E 6

D 6
	DPRINTF(1, (CE_CONT,
	    "!%s: %s: slot:%x, %llx, %llx, flags:%b",
	    dp->name, __func__, slot, rsd0, rsd1,
	    (uint32_t)(rsd1 & RSD1_FLAGS), RSD1_BITS));
E 6
I 6
		DPRINTF(1, (CE_CONT,
		    "!%s: %s: slot:%x, %llx, %llx, flags:%b",
		    dp->name, __func__, slot, rsd0, rsd1,
		    (uint32_t)(rsd1 & RSD1_FLAGS), RSD1_BITS));
E 6

I 6
		if ((uint16_t)(rsd0 & RSD0_SEQNUM) == rxfp->rf_seqnum) {
			rxfp->rf_seqnum++;
			goto correct_seqnum;
		}

		DPRINTF(-1, (CE_CONT, "!%s: %s: waiting for a while",
		    dp->name, __func__));
		drv_usecwait(10);
	}

	cmn_err(CE_WARN,
	    "!%s: %s: wrong seq num, (actual) %d != (expected) %d, "
	    "rsg0:%llx, rsd1:%llx, flags:%b, pkt_len:%d, "
	    "rxf%d + head:%d",
	    dp->name, __func__,
	    (int)(rsd0 & RSD0_SEQNUM), rxfp->rf_seqnum,
	    rsd0, rsd1,
	    (uint32_t)(rsd1 & RSD1_FLAGS), RSD1_BITS,
	    (int)((rsd0 & RSD0_LEN) >> RSD0_LEN_SHIFT),
	    index, rxfp->rf_head);
D 14
	atge_rxf_dump_1e(dp, dp->io_area + (io_offset - 64), 128);
E 14
I 14
	atge_rxf_dump_1e(dp, (uint8_t *)dp->io_area + (io_offset - 64), 128);
E 14
I 7

	/* XXX - terminate gem_receive() immediately */
E 7
	lp->need_to_reset = B_TRUE;
D 7
	return (GEM_RX_ERR);
E 7
I 7
	return (0);
E 7

correct_seqnum:

E 6
#ifdef CONFIG_CKSUM_OFFLOAD
D 7
	if (rsd1 & RSD1_IPv4) {
		/* IPv4 packets, full checksum */
		if ((rsd1 & RSD1_E_IPCHKSUM) == 0) {
			ret |= GEM_RX_CKSUM_IPv4;
E 7
I 7
	if ((rsd1 & (RSD1_IPv4 | RSD1_IPv6)) &&
	    (rsd1 & (RSD1_E_IPCHKSUM | RSD1_E_L4CHKSUM)) == 0) {
		if (rsd1 & RSD1_TCP) {
			ret |= GEM_RX_CKSUM_TCP;
		} else if (rsd1 & RSD1_UDP) {
			ret |= GEM_RX_CKSUM_UDP;
E 7
		}
D 7
		if ((rsd1 & RSD1_E_L4CHKSUM) == 0) {
			if (rsd1 & RSD1_TCP) {
				ret |= GEM_RX_CKSUM_TCP;
			} else if (rsd1 & RSD1_UDP) {
				ret |= GEM_RX_CKSUM_UDP;
			}
I 6
		} else {
			/*
			 * it may be an ip-fragmented packet,
			 * send up partial check sum
			 */
			ret |= ((rsd0 & RSD0_CKSUM) >> RSD0_CKSUM_SHIFT)
			    << GEM_RX_CKSUM_SHIFT;
E 6
		}
	} else {
		/* non IPv4 packets, partial checksum */
		ret |= ((rsd0 & RSD0_CKSUM) >> RSD0_CKSUM_SHIFT)
		    << GEM_RX_CKSUM_SHIFT;
E 7
	}
#endif /* CONFIG_CKSUM_OFFLOAD */

	len = (rsd0 & RSD0_LEN) >> RSD0_LEN_SHIFT;
	if (len >= ETHERFCSL) {
		len -= ETHERFCSL;
	}

	return (ret | len);
}

static void
D 7
atge_rx_desc_init_1(struct gem_dev *dp, int slot)
E 7
I 7
atge_rx_desc_init_1e(struct gem_dev *dp, int slot)
E 7
{
I 7
	/* do nothing */
}

D 10
#ifdef CONFIG_1C
E 10
static void
atge_rx_desc_write_1c(struct gem_dev *dp, int slot,
	ddi_dma_cookie_t *dmacookie, int frags)
{
	uint64_t	dmaaddr;
	struct atge_dev	*lp = dp->private;
	struct rx_free_desc	*rfdp;

D 8
#if DEBUG_LEVEL > 0
E 8
I 8
#if DEBUG_LEVEL > 2
E 8
{
	int	i;

	cmn_err(CE_CONT,
	    "!%s: %s: seqnum: %d, slot %d, frags: %d",
	    dp->name, __func__, dp->rx_active_tail, slot, frags);
	for (i = 0; i < frags; i++) {
		cmn_err(CE_CONT, "!%d: addr: 0x%llx, len: 0x%x",
		    i, dmacookie[i].dmac_laddress, dmacookie[i].dmac_size);
	}
}
#endif
	/*
	 * write a RX descriptor
	 */
	rfdp = &((struct rx_free_desc *)(dp->io_area + lp->rbd_offset))[slot];

	dmaaddr = dmacookie->dmac_laddress;
	rfdp->rf_addr = LE_64(dmaaddr);
}
D 10

E 10
I 10
#if 0
E 10
static void
atge_rx_start_1c(struct gem_dev *dp, int start_slot, int nslot)
{
	int	tail;
	struct atge_dev	*lp = dp->private;

D 8
	DPRINTF(0, (CE_CONT, "!%s: %s: start:%d, nslot:%d",
E 8
I 8
	DPRINTF(2, (CE_CONT, "!%s: %s: start:%d, nslot:%d",
E 8
	    dp->name, __func__, start_slot, nslot));

	atge_rfd_desc_dma_sync_1c(dp, start_slot, nslot);

	tail = SLOT(start_slot + nslot, dp->gc.gc_rx_ring_size);
D 8

E 8
	lp->rx_buffer_tail = tail;
	OUTL(dp, MB_RFD_PROD_IDX + 0*4, tail);
}
I 10
#else
static void
atge_rx_start_1c(struct gem_dev *dp, int start_slot, int nslot)
{
	int	i;
	int	tail;
	struct rx_status_desc	*rsdp;
	struct atge_dev	*lp = dp->private;
E 10

I 10
	DPRINTF(2, (CE_CONT, "!%s: %s: start:%d, nslot:%d",
	    dp->name, __func__, start_slot, nslot));

	/* invalidate rx status descriptors */
	for (i = 0; i < nslot; i++) {
		tail = SLOT(start_slot + i, dp->gc.gc_rx_ring_size);
		rsdp = &((struct rx_status_desc *)(dp->rx_ring))[tail];
		rsdp->rsd0 = 0;	/* sanity */
		rsdp->rsd1 = 0;
	}
	gem_rx_desc_dma_sync(dp,
	    SLOT(start_slot, dp->gc.gc_rx_ring_size), nslot,
	    DDI_DMA_SYNC_FORDEV);

	/* sync rx buffer descriptors */
	atge_rfd_desc_dma_sync_1c(dp, start_slot, nslot);

	/* notify to the nic */
	OUTL(dp, MB_RFD_PROD_IDX + 0*4,
	    SLOT(start_slot + nslot, dp->gc.gc_rx_ring_size));
}
#endif

E 10
static uint64_t
atge_rx_desc_stat_1c(struct gem_dev *dp, int slot, int ndesc)
{
I 10
#ifdef NEVER
E 10
	int		retry;
I 10
#endif
E 10
	int		head;
	uint_t		index;
	uint64_t	len;
	uint64_t	rsd0;
	uint64_t	rsd1;
	uint64_t	ret;
E 7
	struct rx_status_desc	*rsdp;
I 7
	struct atge_dev	*lp = dp->private;
E 7

E 3
D 7
	rsdp = &((struct rx_status_desc *)(dp->rx_ring))[slot];
	rsdp->rsd0 = 0;
E 7
I 7
D 10
	retry = 0;
E 10
I 10
	ASSERT(ndesc == 1);
E 10
	ret = 0;
I 10
#ifdef NEVER
	retry = 0;
E 10
again:
D 10
	rsdp = &((struct rx_status_desc *)(dp->rx_ring))[lp->rx_status_head];
E 10
I 10
#endif
	rsdp = &((struct rx_status_desc *)(dp->rx_ring))[slot];
E 10

	rsd1 = rsdp->rsd1;
	rsd1 = LE_64(rsd1);

	if ((rsd1 & RRS1_UPDATED) == 0) {
		/* not yet received */
		return (0);
	}

	rsd0 = rsdp->rsd0;
	rsd0 = LE_64(rsd0);

D 8
	DPRINTF(0, (CE_CONT,
E 8
I 8
	DPRINTF(2, (CE_CONT,
E 8
D 9
	    "!%s: %s: slot:%x, %llx, %llx, flags:%b, rsd/rbd index:0x%x",
E 9
I 9
	    "!%s: %s: slot:%x, %llx, %llx, flags:%b",
E 9
	    dp->name, __func__, slot, rsd0, rsd1,
D 9
	    (uint32_t)(rsd1 & RSD1_FLAGS), RSD1_BITS,
	    INL(dp, CURR_RBD_RSD_1)));
E 9
I 9
	    (uint32_t)(rsd1 >> RRS1_PKT_SIZE_SHIFT), RRS1_BITS));
E 9

D 9
	/* invalidate the rx status descriptor */
	rsdp->rsd1 = 0;
	ret = GEM_RX_DONE;

E 9
I 9
	/*
	 * check fatal errors
	 */
E 9
	if (((rsd0 & RRS0_CNT) >> RRS0_CNT_SHIFT) != 1) {
I 10
#ifdef NEVER
E 10
		if (retry++ < 1) {
			gem_rx_desc_dma_sync(dp,
			    slot, 1, DDI_DMA_SYNC_FORKERNEL);
			goto again;
		}
I 10
#endif
E 10
		cmn_err(CE_WARN, "!%s: %s: (rsd0(%llx) & RRS0_CNT) != 1",
		    dp->name, __func__, rsd0);
		lp->need_to_reset = B_TRUE;
		return (GEM_RX_DONE | GEM_RX_ERR);
	}

D 9
	if (rsd1 & (RRS1_E_SUM | RRS1_LEN_ERR)) {
		return (GEM_RX_DONE | GEM_RX_ERR);
	}

E 9
	index = (rsd0 & RRS0_INDEX) >> RRS0_INDEX_SHIFT;
	if (slot != index) {
		cmn_err(CE_WARN, "!%s: %s: slot(%d) != index(%d)",
		    dp->name, __func__, slot, index);
		lp->need_to_reset = B_TRUE;
		return (GEM_RX_DONE | GEM_RX_ERR);
	}

	/* now current slot == index in current return descriptor */
I 9
	ret = GEM_RX_DONE;
E 9
D 10

E 10
I 10
#ifdef NEVER
E 10
I 9
	/* invalidate the rx status descriptor */
I 10
	rsdp->rsd0 = 0;
E 10
	rsdp->rsd1 = 0;

E 9
	/*
	 * Increase rx_status_head to point the next descriptor,
D 15
	 * we don't update MBOX here. it have to be updated when new
	 * rx buffers are prepared later. we also don't use mutex lock,
E 15
I 15
	 * we don't update MBOX here. It have to be updated later when
	 * new rx buffers are prepared. we also don't use mutex lock,
E 15
	 * because an assignment of a 4 byte word is naturally atomic,
	 * the modification is only performed in this function and
	 * intrlock is held.
	 */
	lp->rx_status_head = SLOT(index + 1, dp->gc.gc_rx_ring_size);
I 10
#endif
E 10

I 9
	if (rsd1 & (RRS1_E_SUM | RRS1_LEN_ERR)) {
		ret |= GEM_RX_ERR;
E 9
#ifdef NEVER
D 9
	if (rsd1 & (RSD1_E_TRUNC | RSD1_E_OVF |
	    RSD1_E_RUNT | RSD1_E_CODE | RSD1_E_CRC)) {
		DPRINTF(0, (CE_CONT,
		    "!%s: %s: slot:%x, %llx, %llx, flags:%b, "
		    "rsd/rbd index:0x%x",
		    dp->name, __func__, slot, rsd0, rsd1,
		    (uint32_t)(rsd1 & RSD1_FLAGS), RSD1_BITS,
		    INL(dp, CURR_RBD_RSD_1)));
E 9
I 9
		if (rsd1 & (RRS1_E_TRUNC | RRS1_E_RUNT |
		    RRS1_E_FAE | RRS1_E_CRC)) {
			DPRINTF(0, (CE_CONT,
			    "!%s: %s: slot:%x, %llx, %llx, flags:%b",
			    dp->name, __func__, slot, rsd0, rsd1,
			    (uint32_t)(rsd1 >> 32), RRS1_BITS));
E 9

D 9
		ret |= GEM_RX_ERR;
		dp->stats.errrcv++;
		if (rsd1 & RSD1_E_TRUNC) {
			dp->stats.frame_too_long++;
		} else if (rsd1 & RSD1_E_OVF) {
			dp->stats.overflow++;
		} else if (rsd1 & RSD1_E_RUNT) {
			dp->stats.runt++;
		} else if (rsd1 & RSD1_E_CODE) {
			dp->stats.frame++;
		} else if (rsd1 & RSD1_E_CRC) {
			dp->stats.crc++;
		} else {
			dp->stats.rcv_internal_err++;
E 9
I 9
			dp->stats.errrcv++;
			if (rsd1 & RRS1_E_TRUNC) {
				dp->stats.frame_too_long++;
			} else if (rsd1 & RRS1_E_RUNT) {
				dp->stats.runt++;
			} else if (rsd1 & RRS1_E_FAE) {
				dp->stats.frame++;
			} else if (rsd1 & RRS1_E_CRC) {
				dp->stats.crc++;
			} else {
				dp->stats.rcv_internal_err++;
			}
E 9
		}
D 9
	}
E 9
#endif /* USE_GETSTAT_RX */
I 9
		return (ret);
	}
E 9

I 9

E 9
	len = (rsd1 & RRS1_PKT_SIZE) >> RRS1_PKT_SIZE_SHIFT;
	if (len >= ETHERFCSL) {
		len -= ETHERFCSL;
	}

	return (ret | len);
E 7
}

I 3
static void
D 7
atge_rx_desc_init_1e(struct gem_dev *dp, int slot)
E 7
I 7
atge_rx_desc_init_1c(struct gem_dev *dp, int slot)
E 7
{
D 7
	/* do nothing */
E 7
I 7
	struct rx_status_desc	*rsdp;

	rsdp = &((struct rx_status_desc *)(dp->rx_ring))[slot];
D 10
	rsdp->rsd0 = 0;
E 10
I 10
	rsdp->rsd0 = 0;	/* sanity */
	rsdp->rsd1 = 0;
E 10
E 7
}

I 7
D 10
#endif
E 10
E 7
E 3
/*
 * Device depend interrupt handler
 */
static uint_t
atge_interrupt(struct gem_dev *dp)
{
	int		i;
	uint32_t	isr;
I 2
	uint32_t	bogus_isr;
I 3
D 6
	uint32_t	isr_disable;
	uint32_t	isr_enable;
	uint32_t	isr_tx;
	uint32_t	isr_rx_ok;
	uint32_t	isr_rx_err;
	uint32_t	isr_dma_err;
	uint32_t	isr_gphy;
	uint32_t	isr_sm;
	uint32_t	isr_pcie_err;
E 6
E 3
E 2
	uint_t		uval;
	uint_t		flag = 0;
I 3
D 6
	char		*isr_bits;
E 6
E 3
	struct atge_dev	*lp = dp->private;
	struct intr_status_msg *ismp;

D 2
#ifndef CONFIG_MSI
	FLSHL(dp, ISR);
#endif
E 2
D 3
	atge_ioarea_dma_sync(dp, IOA_ISM_OFFSET,
	    sizeof (struct intr_status_msg), DDI_DMA_SYNC_FORKERNEL);
E 3
I 3
	switch (lp->chip) {
	case CHIP_L1:
I 15
#ifdef CONFIG_ISM_L1C
	case CHIP_L1C:
#endif
E 15
		atge_ioarea_dma_sync(dp, lp->ism_offset,
		    sizeof (struct intr_status_msg), DDI_DMA_SYNC_FORKERNEL);
E 3

D 3
	ismp = (struct intr_status_msg *)(dp->io_area + IOA_ISM_OFFSET);
	isr = ismp->ism_isr;
	isr = LE_32(isr);
E 3
I 3
		ismp = (struct intr_status_msg *)(dp->io_area + lp->ism_offset);
		isr = ismp->ism_isr;
		isr = LE_32(isr);
E 3
D 6

I 3
		isr_disable = ISR_DIS_INT_1 | ISR_DIS_DMA_1;
		isr_enable = ISR_DIS_SM_1 | ISR_DIS_DMA_1;
		isr_rx_err = ISR_RX_ERR_1;
		isr_rx_ok = ISR_RX_OK_1;
		isr_tx = ISR_TX_1;
		isr_dma_err = ISR_DMAR_TO_RST_1 | ISR_DMAW_TO_RST_1;
		isr_gphy = ISR_GPHY_1;
		isr_sm = ISR_SM_1;
		isr_pcie_err = ISR_PCIE_ERR_1;
		isr_bits = ISR_BITS_1;
E 6
		break;

D 6
	case CHIP_L2:
E 6
I 6
	default:
E 6
		isr = INL(dp, ISR);
D 6

		isr_disable = ISR_DIS_INT_2;
		isr_enable = 0;
		isr_rx_err = ISR_RX_ERR_2;
		isr_rx_ok = ISR_RX_OK_2;
		isr_tx = ISR_TX_UPDATE_2;
		isr_dma_err = ISR_DMAR_TO_RST_2 | ISR_DMAW_TO_RST_2;
		isr_gphy = ISR_GPHY_2;
		isr_sm = 0;
		isr_pcie_err = ISR_PCIE_ERR_2;
		isr_bits = ISR_BITS_2;
E 6
		break;
D 6

	case CHIP_L1E:
	case CHIP_L2E_A:
	case CHIP_L2E_B:
		isr = INL(dp, ISR);

		isr_disable = ISR_DIS_INT_1e;
		isr_enable = 0;
		isr_rx_err = ISR_RX_ERR_1e;
		isr_rx_ok = ISR_RX_OK_1e;
		isr_tx = ISR_TX_1e;
		isr_dma_err = ISR_DMAR_TO_RST_1e | ISR_DMAW_TO_RST_1e;
		isr_gphy = ISR_GPHY_1e;
		isr_sm = ISR_SM_1e;
		isr_pcie_err = ISR_PCIE_ERR_1e;
		isr_bits = ISR_BITS_1e;
		break;
E 6
	}
E 3
I 2
	bogus_isr = lp->isr_pended;
	lp->isr_pended = 0;

E 2
D 3
	DPRINTF(100, (CE_CONT,
D 2
	    "!%s: Interrupt, time:%d isr: %b "
	    "rsd:%d rbd:%d tbd:%d",
E 2
I 2
	    "!%s: Interrupt, time:%d isr:%b rsd:%d rbd:%d tbd:%d",
E 2
	    dp->name, ddi_get_lbolt(), isr, ISR_BITS,
	    LE_16(ismp->ism_rsd), LE_16(ismp->ism_rbd), LE_16(ismp->ism_tbd)));

E 3
D 2
	if (isr == 0) {
E 2
I 2
	if (((isr | bogus_isr) & lp->imr) == 0) {
I 6
D 15
#ifdef CONFIG_INTR_MSI
D 10
		cmn_err(CE_WARN,
D 8
		    "!%s: %s: wrong interrupt isr:%b isr_pended:%b",
E 8
I 8
		    "!%s: %s: wrong interrupt isr:%b bogus:%b isr_pended:%b",
E 8
		    dp->name, __func__,
D 8
		    isr, lp->isr_bits, lp->isr_pended, lp->isr_bits);
E 8
I 8
		    isr, lp->isr_bits, bogus_isr, lp->isr_bits,
		    lp->isr_pended, lp->isr_bits);
E 10
I 10
		/* it seems we cannot use imr in INTR_RDCLR mode */
		if (!lp->intr_rdclr) {
			cmn_err(CE_WARN,
D 13
			    "!%s: %s: wrong interrupt "
E 13
I 13
			    "!%s: %s: bogus interrupt "
E 13
			    "isr:%b bogus:%b isr_pended:%b",
			    dp->name, __func__,
			    isr, lp->isr_bits, bogus_isr, lp->isr_bits,
			    lp->isr_pended, lp->isr_bits);
E 15
I 15
#ifdef GEM_CONFIG_INTR_MSI
		if ((dp->intr_types &
		    (DDI_INTR_TYPE_MSIX | DDI_INTR_TYPE_MSI)) &&
		    dp->gc.gc_nintrs_req > 0)  {
			/*
			 * IMR doesn't seem to mask interrupts
			 * in INTR_RDCLR mode
			 */
			if (!lp->intr_rdclr) {
				cmn_err(CE_WARN,
				    "!%s: %s: bogus interrupt "
				    "isr:%b bogus:%b isr_pended:%b",
				    dp->name, __func__,
				    isr, lp->isr_bits, bogus_isr, lp->isr_bits,
				    lp->isr_pended, lp->isr_bits);
			}
			return (DDI_INTR_CLAIMED);
E 15
		}
E 10
E 8
D 15
		return (DDI_INTR_CLAIMED);
#else
E 15
I 15
#endif
E 15
E 6
E 2
		/* Not for us */
		return (DDI_INTR_UNCLAIMED);
I 6
D 15
#endif
E 15
E 6
	}

D 3
	DPRINTF(2, (CE_CONT,
	    "!%s: Interrupt, time:%d isr: %b "
	    "rsd:%d rbd:%d tbd:%d",
	    dp->name, ddi_get_lbolt(), isr, ISR_BITS,
	    LE_16(ismp->ism_rsd), LE_16(ismp->ism_rbd), LE_16(ismp->ism_tbd)));
E 3
I 3
D 6
	DPRINTF(1, (CE_CONT,
E 6
I 6
D 7
	DPRINTF(0, (CE_CONT,
E 7
I 7
	DPRINTF(2, (CE_CONT,
E 7
E 6
	    "!%s: Interrupt, time:%d isr: %b ",
D 6
	    dp->name, ddi_get_lbolt(), isr, isr_bits));
E 6
I 6
	    dp->name, ddi_get_lbolt(), isr, lp->isr_bits));
E 6
E 3

D 3
	/* update free tx buffer head */
	uval = ismp->ism_tbd;
	lp->tx_buffer_head = LE_16(uval);
	uval = ismp->ism_rsd;
	lp->rx_status_tail = LE_16(uval);
E 3
I 3
	switch (lp->chip) {
	case CHIP_L1:
		/* update tx buffer head */
D 6
		mutex_enter(&dp->xmitlock);
E 6
		uval = ismp->ism_tbd;
		lp->tx_buffer_head = LE_16(uval);
D 6
		mutex_exit(&dp->xmitlock);
E 6
I 6

		/* update rx buffer tail */
E 6
		uval = ismp->ism_rsd;
		lp->rx_status_tail = LE_16(uval);
		break;
E 3
D 15

I 3
	case CHIP_L2:
E 15
I 15
	default:
E 15
		/* nothing to do */
		break;
D 15

	case CHIP_L1E:
	case CHIP_L2E_A:
	case CHIP_L2E_B:
D 6
		if (isr & isr_tx) {
			mutex_enter(&dp->xmitlock);
E 6
I 6
		if (isr & (lp->isr_tx_ok | lp->isr_tx_err)) {
E 6
			lp->tx_buffer_head = INW(dp, TBDHEAD_1e);
D 6
			mutex_exit(&dp->xmitlock);
E 6
		}
		break;
I 7
D 10
#ifdef CONFIG_1C
E 10
I 10

D 11
#ifndef GEM_CONFIG_TX_HEAD_PTR
E 11
I 11
#if !defined(GEM_CONFIG_TX_HEAD_PTR)
E 11
E 10
	case CHIP_L1C:
	case CHIP_L2C:
	case CHIP_L2C_B:
	case CHIP_L2C_B2:
	case CHIP_L1D:
D 8
		DPRINTF(0, (CE_CONT,
E 8
I 8
	case CHIP_L1D_2_0:
		DPRINTF(2, (CE_CONT,
E 8
		    "!%s: Interrupt, time:%d isr: %b ",
		    dp->name, ddi_get_lbolt(), isr, lp->isr_bits));

		if (isr & (lp->isr_tx_ok | lp->isr_tx_err)) {
			lp->tx_buffer_head = INL(dp, MB_PRIO_CONS_IDX) >> 16;
		}
		break;
#endif
E 15
E 7
	}

E 3
D 7
	if (!dp->mac_active) {
E 7
I 7
	if (!IS_MAC_ONLINE(dp)) {
E 7
		/* the device is not active, no more interrupts */
I 2
		lp->imr = 0;
		OUTL(dp, IMR, lp->imr);
		FLSHL(dp, IMR);

		/* clear and disable interrupts */
D 3
		ismp->ism_isr = 0;
		OUTL(dp, ISR, isr | ISR_DIS_INT);
E 3
I 3
		if (lp->chip == CHIP_L1) {
			ismp->ism_isr = 0;
		}
D 6
		OUTL(dp, ISR, isr | isr_disable);
E 6
I 6
		OUTL(dp, ISR, isr | lp->isr_disable);
E 6
E 3
		FLSHL(dp, ISR);

E 2
		return (DDI_INTR_CLAIMED);
	}
#ifdef TEST_RESET_ON_ERRROR
	lp->reset_test++;
	if ((lp->reset_test % 10000) == 9999) {
		lp->need_to_reset = B_TRUE;
	}
#endif
	/* clear and disable interrupts */
D 3
	ismp->ism_isr = 0;
I 2
	atge_ioarea_dma_sync(dp, IOA_ISM_OFFSET,
	    sizeof (struct intr_status_msg), DDI_DMA_SYNC_FORDEV);
E 2

	if (isr & ISR_GPHY) {
E 3
I 3
D 6
	if (isr & isr_gphy) {
E 6
I 6
	if (isr & lp->isr_gphy) {
E 6
E 3
		/* ack to interrupts from PHY */
I 7
		sema_p(&dp->hal_op_lock);
E 7
D 15
		(void) atge_mii_read(dp, 19);
E 15
I 15
		(void) atge_mii_read_raw(dp, 19);
E 15
I 7
		sema_v(&dp->hal_op_lock);
E 7
	}

I 15
	/* XXX - RDCLR mode cannot handle PHY interrupts */
E 15
D 3
	OUTL(dp, ISR, isr | ISR_DIS_INT);
E 3
I 3
D 6
	OUTL(dp, ISR, isr | isr_disable);
E 6
I 6
	OUTL(dp, ISR, isr | lp->isr_disable);
E 6
D 7
#ifdef notdef /* CONFIG_POLLING */
	if (lp->chip == CHIP_L2 && dp->speed == GEM_SPD_100 &&
	    dp->poll_interval != lp->last_poll_interval) {
E 7
I 7

#if defined(CONFIG_ADAPTIVE_COALESCE)
D 8
	 if ((dp->speed == GEM_SPD_1000 || dp->speed == GEM_SPD_100) &&
	     dp->poll_interval != lp->last_poll_interval) {
E 8
I 8
	if ((dp->speed == GEM_SPD_1000 || dp->speed == GEM_SPD_100) &&
	    dp->poll_interval != lp->last_poll_interval) {
E 8
E 7
		uint_t	val;

		val = dp->poll_interval/2000;
		val = max(val, 1);
		val = min(val, 0xffff);
D 7
		OUTW(dp, INTRDELAY_INIT, val);
		DPRINTF(5, (CE_CONT, "!%s: %s: INTRDELAY_INIT:0x%x",
		    dp->name, __func__, INW(dp, INTRDELAY_INIT)));
E 7

I 7
		switch (lp->chip) {
		case CHIP_L1E:
		case CHIP_L2E_A:
		case CHIP_L2E_B:
			OUTW(dp, INTRDELAY2_INIT, val);
			DPRINTF(5, (CE_CONT, "!%s: %s: INTRDELAY2_INIT:0x%x",
			    dp->name, __func__, INW(dp, INTRDELAY2_INIT)));
			break;
#ifdef notyet
		case CHIP_L2:
			OUTW(dp, INTRDELAY_INIT, val);
			DPRINTF(5, (CE_CONT, "!%s: %s: INTRDELAY_INIT:0x%x",
			    dp->name, __func__, INW(dp, INTRDELAY_INIT)));
			break;
#endif
I 8
D 10
#ifdef notyet
E 10
		case CHIP_L1C:
D 10
			OUTL(dp, INTRDELAY2_INIT, val);
E 10
I 10
		case CHIP_L2C:
		case CHIP_L2C_B:
		case CHIP_L2C_B2:
		case CHIP_L1D:
		case CHIP_L1D_2_0:
			/* don't change delay for tx */
			OUTW(dp, INTRDELAY_INIT + 2, val);
E 10
			break;
D 10
#endif
E 10
E 8
		}

E 7
		lp->last_poll_interval = dp->poll_interval;
	}
#endif
E 3
D 10
	FLSHL(dp, ISR);

E 10
D 3
	if (isr & ISR_SM) {
E 3
I 3
D 15
	if (lp->chip == CHIP_L1) {
E 15
I 15
	switch (lp->chip) {
	case CHIP_L1:
#ifdef CONFIG_ISM_L1C
	case CHIP_L1C:
#endif
E 15
I 10
		/* XXX - Is clearning isr not required for msi mode ? */
D 11
		/* XXX - the nic might not update isr because interrupts
E 11
I 11
		/*
		 * XXX - the nic might not update isr because interrupts
E 11
		 * are disabled now.
		 */
E 10
D 6
		ismp->ism_isr &= ~isr;
E 6
I 6
		/*
		 * there will be race conditions between clearing the
		 * isr in the interrupt status message and updating it from
		 * the nic.
		 * But it will not cause serious probems even if the nic
		 * updates isr right before we clear it.
		 * The interrupt reasons we don't serve now, will remain
		 * until the next update from the nic.
		 */
D 15
		ismp->ism_isr = 0;
E 15
I 15
		ismp->ism_isr &= ~isr;
E 15
E 6
		atge_ioarea_dma_sync(dp, lp->ism_offset,
		    sizeof (struct intr_status_msg), DDI_DMA_SYNC_FORDEV);
	}

I 10
	if (!lp->intr_rdclr) {
		FLSHL(dp, ISR);
	}

E 10
D 6
	if (isr & isr_sm) {
E 6
I 6
	/* mask interrupts we are not interrested in */
	isr &= lp->imr;

	if (isr & lp->isr_sm) {
E 6
E 3
D 10
		/* update staticstics */
E 10
I 10
		/* update statistics */
E 10
D 6
		atge_get_stats(dp);
E 6
I 6
		DPRINTF(4, (CE_CONT,
		    "!%s: statistics full, isr:0x%b", dp->name,
		    isr, lp->isr_bits));
		atge_update_stats(dp);
E 6
	}

D 3
	if (isr & ISR_PCIE_ERR) {
		/* pci-e phy linkdown */
E 3
I 3
D 6
	if (isr & isr_pcie_err) {
E 6
I 6
	if (isr & lp->isr_pcie_err) {
E 6
		/* pci-e phy link down */
E 3
D 2
		DPRINTF(0, (CE_WARN,
		    "!%s: pcie error, isr:0x%b", dp->name, isr, ISR_BITS));
E 2
I 2
		cmn_err(CE_WARN,
D 3
		    "!%s: pcie error, isr:0x%b", dp->name, isr, ISR_BITS);
E 3
I 3
		    "!%s: pcie error, isr:0x%b", dp->name,
D 6
		    isr, isr_bits);
E 6
I 6
		    isr, lp->isr_bits);
E 6
E 3
E 2
		OUTL(dp, IMR, 0);
		lp->need_to_reset = B_TRUE;
	}

D 3
	if (isr & (ISR_DMAR_TO_RST | ISR_DMAW_TO_RST)) {
E 3
I 3
D 6
	if (isr & isr_dma_err) {
E 6
I 6
	if (isr & lp->isr_dma_err) {
E 6
E 3
		/* DMA transfer error happened */
D 2
		DPRINTF(0, (CE_WARN,
E 2
I 2
		cmn_err(CE_WARN,
E 2
		    "!%s: dma error happened, isr:0x%b",
D 2
		    dp->name, isr, ISR_BITS));
E 2
I 2
D 3
		    dp->name, isr, ISR_BITS);
E 3
I 3
D 6
		    dp->name, isr, isr_bits);
E 6
I 6
		    dp->name, isr, lp->isr_bits);
E 6
E 3
E 2
		OUTL(dp, IMR, 0);
		lp->need_to_reset = B_TRUE;
	}

D 3
	if (isr & ISR_GPHY) {
E 3
I 3
D 6
	if (isr & isr_gphy) {
E 6
I 6
	if (isr & lp->isr_gphy) {
E 6
E 3
		/* link status has changed */
D 2
		DPRINTF(0, (CE_CONT,
		    "!%s: %s link status has changed",
		    dp->name, __func__));
		if (gem_mii_link_check(dp)) {
			flag |= INTR_RESTART_TX;
E 2
I 2
D 3
		cmn_err(CE_NOTE,
		    "!%s: %s: link status has changed",
E 3
I 3
D 6
		cmn_err(CE_NOTE, "!%s: %s: link status has changed",
E 6
I 6
D 7
		cmn_err(CE_CONT, "!%s: %s: link status has changed",
E 6
E 3
		    dp->name, __func__);
E 7
I 7
		DPRINTF(1, (CE_CONT, "!%s: %s: link status has changed",
		    dp->name, __func__));
#ifdef GEM3
		gem_mii_link_check(dp);
#else
E 7
D 3
		if (!lp->ignore_linkdown) {
			if (gem_mii_link_check(dp)) {
				flag |= INTR_RESTART_TX;
			}
		} else {
			(void) atge_mii_read(dp, MII_STATUS);
			lp->ignore_linkdown = B_FALSE;
E 3
I 3
		if (gem_mii_link_check(dp)) {
			flag |= INTR_RESTART_TX;
E 3
E 2
		}
I 7
#endif
E 7
	}

I 7
#ifdef GEM3
	if (((isr & lp->isr_tx_ok) &&
	    dp->tx_free_bufs < dp->gc.gc_tx_buf_size / 1) ||
	    (isr & lp->isr_tx_err)) {
		/* reclaim tx descriptors */
		if (isr & lp->isr_tx_err) {
			cmn_err(CE_WARN, "!%s: tx error, isr:%b",
			    dp->name, isr, lp->isr_bits);
		}
		if (gem_tx_done(dp)) {
			flag |= INTR_RESTART_TX;
		}
	}

#endif
E 7
D 3
	if (isr & (ISR_RXF_OVF | ISR_RBD_UNRUN | ISR_RSD_OVF |
	    ISR_HOST_RBD_UNRUN | ISR_HOST_RSD_OVF |
	    ISR_ISM_RX | ISR_MAC_RX | ISR_RX_DMA | ISR_RX_PKT)) {
E 3
I 3
D 6
	if (isr & (isr_rx_ok | isr_rx_err)) {
E 6
I 6
	if (isr & (lp->isr_rx_ok | lp->isr_rx_err)) {
E 6
E 3
		/*
		 * one or more packets were received, or receive error
		 * happened
		 */
D 3
		if (isr & (ISR_RXF_OVF | ISR_RBD_UNRUN | ISR_RSD_OVF |
		    ISR_HOST_RBD_UNRUN | ISR_HOST_RSD_OVF)) {
			/* reveive error happened */
			DPRINTF(4, (CE_WARN, "!%s: receive error, isr:0x%b",
			    dp->name, isr, ISR_BITS));
E 3
I 3
D 6
		if (isr & isr_rx_err) {
E 6
I 6
#ifdef notdef
		if (isr & lp->isr_rx_err) {
E 6
			/* receive error happened */
I 6
#if DEBUG_LEVEL > 4
E 6
			cmn_err(CE_WARN, "!%s: receive error, isr:0x%b",
D 6
			    dp->name, isr, isr_bits);
E 6
I 6
			    dp->name, isr, lp->isr_bits);
#endif
			dp->stats.overflow++;
E 6
E 3
		}
I 6
#endif
E 6
		(void) gem_receive(dp);
	}

I 7
#ifndef GEM3
E 7
D 3
	if (isr & (ISR_ISM_TX | ISR_MAC_TX | ISR_TX_DMA | ISR_TX_PKT)) {
E 3
I 3
D 6
	if (isr & isr_tx) {
E 6
I 6
	if (isr & (lp->isr_tx_ok | lp->isr_tx_err)) {
E 6
E 3
		/* reclaim tx descriptors */
I 6
		if (isr & lp->isr_tx_err) {
			cmn_err(CE_WARN, "!%s: tx error, isr:%b",
			    dp->name, isr, lp->isr_bits);
		}
E 6
		if (gem_tx_done(dp)) {
			flag |= INTR_RESTART_TX;
		}
	}

D 7
	if (lp->need_to_reset) {
E 7
I 7
#endif
	if ((isr & lp->isr_fatal_err) || lp->need_to_reset) {
E 7
I 6
#if DEBUG_LEVEL > 4
E 6
I 3
		switch (lp->chip) {
		case CHIP_L1:
		case CHIP_L1E:
		case CHIP_L2E_A:
		case CHIP_L2E_B:
			atge_tx_desc_dump_1_1e(dp);
		}
I 6
#endif
E 6
E 3
		gem_restart_nic(dp, GEM_RESTART_KEEP_BUF);
		flag |= INTR_RESTART_TX;
		lp->need_to_reset = B_FALSE;
	}

	if ((dp->misc_flag & GEM_NOINTR) == 0) {
		/* enable interrupts again */
D 3
		OUTL(dp, ISR, ISR_DIS_SM | ISR_DIS_DMA);
E 3
I 3
D 6
		OUTL(dp, ISR, isr_enable);
E 6
I 6
		OUTL(dp, ISR, lp->isr_enable);
E 6
E 3
	}

	return (DDI_INTR_CLAIMED | flag);
}

/*
 * HW depend MII routines
 */
static void
I 3
D 7
atge_reset_phy(struct gem_dev *dp)
E 7
I 7
atge_reset_phy(struct gem_dev *dp)	/* L1C */
E 7
{
D 8
	uint_t		uval;
E 8
I 8
D 15
	uint16_t	uval;
E 15
I 15
	uint32_t	uval;
E 15
E 8
	struct atge_dev	*lp = dp->private;

I 6
	if (lp->phy_initialized) {
		/* no need to initialize phy twice after power up */
		return;
	}
	lp->phy_initialized = B_TRUE;

E 6
	switch (lp->chip) {
	case CHIP_L2:
		OUTW(dp, GPHYC, lp->gphyc | GPHYC_ENABLE);
		delay(drv_usectohz(1000));
		break;

D 7
	default:
		/* L1, L1E, L2E */
E 7
I 7
	case CHIP_L1:
	case CHIP_L1E:
	case CHIP_L2E_A:
	case CHIP_L2E_B:
E 7
		/* reset PHY first */
		OUTW(dp, GPHYC, lp->gphyc);
		delay(drv_usectohz(2000));
		OUTW(dp, GPHYC, lp->gphyc | GPHYC_ENABLE);
		delay(drv_usectohz(2000));
		break;
I 7
D 10
#ifdef CONFIG_1C
E 10
I 8

E 8
	case CHIP_L1C:
	case CHIP_L2C:
	case CHIP_L2C_B:
	case CHIP_L2C_B2:
	case CHIP_L1D:
I 8
	case CHIP_L1D_2_0:
E 8
		/* reset PHY first */
D 8
		OUTW(dp, GPHYC, lp->gphyc);	/* ok */
E 8
I 8
D 15
		OUTW(dp, GPHYC, lp->gphyc);
E 8
		delay(drv_usectohz(40000));
		OUTW(dp, GPHYC, lp->gphyc | GPHYC_EXT_RESET_1c);
D 8
		delay(drv_usectohz(10000));	/* ok */
E 8
I 8
		delay(drv_usectohz(10000));
E 15
I 15
		DPRINTF(0, (CE_CONT, "!%s: %s: GPHYC:%x",
		    dp->name, __func__, INL(dp, GPHYC)));
#if 0
		lp->gphyc = INL(dp, GPHYC) & 
		    ~(GPHYC_EXT_RESET_1c | GPHYC_PHY_IDDQ |
		    GPHYC_GATE_25M_EN | GPHYC_PWDOWN_HW | GPHYC_CLS_1c);
		lp->gphyc &= ~GPHYC_GIGA_DIS;
		lp->gphyc |= GPHYC_DEFAULT_1c;
#endif
		OUTL(dp, GPHYC, lp->gphyc);
		FLSHL(dp, 0);
		delay(drv_usectohz(10));
		DPRINTF(0, (CE_CONT, "!%s: %s: GPHYC:%x:%x",
		    dp->name, __func__, lp->gphyc, INL(dp, GPHYC)));

		OUTL(dp, GPHYC, lp->gphyc | GPHYC_EXT_RESET_1c);
		FLSHL(dp, 0);
		delay(drv_usectohz(800));
E 15
E 8
		break;
D 10
#endif
E 10
E 7
	}

	switch (lp->chip) {
	case CHIP_L1E:
	case CHIP_L2E_A:
	case CHIP_L2E_B:
		/* patch for L1E and L2E phys */
		/* eable hibernation mode */
		atge_mii_write_raw(dp, MII_DBG_ADDR, 0xb);
D 6
		atge_mii_write_raw(dp, MII_DBG_DATA, 0xbC00);
E 6
I 6
		atge_mii_write_raw(dp, MII_DBG_DATA, 0xbc00);
E 6

		/* set Class A/B for all modes */
		atge_mii_write_raw(dp, MII_DBG_ADDR, 0);
D 6
		uval = atge_mii_read(dp, MII_DBG_DATA);
		atge_mii_write_raw(dp, MII_DBG_ADDR, 0);
		atge_mii_write_raw(dp, MII_DBG_DATA, uval | 0x025f);
E 6
I 6
		atge_mii_write_raw(dp, MII_DBG_DATA, 0x02ef);
E 6

		/* 10B */
		atge_mii_write_raw(dp, MII_DBG_ADDR, 0x12);
		atge_mii_write_raw(dp, MII_DBG_DATA, 0x4c04);

		/* 1000T power */
		atge_mii_write_raw(dp, MII_DBG_ADDR, 0x4);
		atge_mii_write_raw(dp, MII_DBG_DATA, 0x8bbb);

		atge_mii_write_raw(dp, MII_DBG_ADDR, 0x5);
D 6
		atge_mii_write_raw(dp, MII_DBG_DATA, 0x2C46);
E 6
I 6
		atge_mii_write_raw(dp, MII_DBG_DATA, 0x2c46);
E 6

		delay(drv_usectohz(1000));
		break;

	case CHIP_L2:
		atge_mii_write_raw(dp, MII_DBG_ADDR, 0);
D 15
		uval = atge_mii_read(dp, MII_DBG_DATA);
E 15
I 15
		uval = atge_mii_read_raw(dp, MII_DBG_DATA);
E 15
		if (uval & 0x1000) {
D 7
			atge_mii_write_raw(dp, MII_DBG_ADDR, uval & ~0x1000);
E 7
I 7
			atge_mii_write_raw(dp, MII_DBG_DATA, uval & ~0x1000);
E 7
		}
D 4
		break;	
E 4
I 4
		break;
I 8
D 10
#ifdef CONFIG_1C
E 10
E 8
E 4

I 8
	case CHIP_L1C:
	case CHIP_L2C:
	case CHIP_L2C_B:
	case CHIP_L2C_B2:
	case CHIP_L1D:
	case CHIP_L1D_2_0:
D 15
		if (lp->chip == CHIP_L2C_B) {
E 15
I 15
		/* switch clock */
		if (lp->chip == CHIP_L2C_B) {	/* ok */
			/* MIIDBG_CFGLPSPD */
E 15
			atge_mii_write_raw(dp, MII_DBG_ADDR, 10);
D 15
			uval = atge_mii_read(dp, MII_DBG_DATA);
			atge_mii_write_raw(dp, MII_DBG_DATA, uval & ~0x2000);
E 15
I 15
			uval = atge_mii_read_raw(dp, MII_DBG_DATA);
			atge_mii_write_raw(dp, MII_DBG_DATA,
			    uval & ~0x2000);	/* ~CFGLPSPD_RSTCNT_CLK125SW */
E 15
		}
D 15
		if (lp->chip == CHIP_L2C_B ||
		    lp->chip == CHIP_L2C_B2 ||
		    lp->chip == CHIP_L1D ||
		    lp->chip == CHIP_L1D_2_0) {
E 15
I 15
		/* clear bit3 of dbgport 59 to lower voltage */
		if (lp->chip == CHIP_L2C_B || lp->chip == CHIP_L2C_B2) {
			/* VOLT_CTRL */
E 15
			atge_mii_write_raw(dp, MII_DBG_ADDR, 59);
D 15
			uval = atge_mii_read(dp, MII_DBG_DATA);
			atge_mii_write_raw(dp, MII_DBG_DATA, uval & ~0x0008);
E 15
I 15
			uval = atge_mii_read_raw(dp, MII_DBG_DATA);
			atge_mii_write_raw(dp, MII_DBG_DATA,
			    uval & ~0x0008);	/* VOLT_CTRL_SWLOWEST */
E 15
			delay(drv_usectohz(20000));
		}
D 15
		if (lp->chip == CHIP_L1D) {
			atge_mii_write_raw(dp, MII_DBG_ADDR, MII_ANA_CTRL_41);
			atge_mii_write_raw(dp, MII_DBG_DATA, 0x929d);
		} else if (lp->chip == CHIP_L1C ||
		    lp->chip == CHIP_L2C_B2 ||
		    lp->chip == CHIP_L2C) {
			atge_mii_write_raw(dp, MII_DBG_ADDR, MII_ANA_CTRL_41);
			atge_mii_write_raw(dp, MII_DBG_DATA, 0xb6dd);
E 15
I 15

		/* power saving config */
		/* LEGCYPS */
		if (lp->chip == CHIP_L1D || lp->chip == CHIP_L1D_2_0) {
			uval = 0x129d;
		} else {
			uval = 0x36dd;
E 15
		}
I 15
		atge_mii_write_raw(dp, MII_DBG_ADDR, MII_ANA_CTRL_41);
		atge_mii_write_raw(dp, MII_DBG_DATA, uval);
E 15
D 10
#endif
E 10
I 10

E 10
E 8
D 7
	case CHIP_L1:
		/* do nothing */
E 7
I 7
D 15
	default:
D 8
		/* L1/L1C, do nothing */
E 8
I 8
		/* do nothing */
E 8
E 7
		break;
	}
E 15
I 15
		/* hib */
		/* SYSMODCTRL */
		atge_mii_write_raw(dp, MII_DBG_ADDR, MII_ANA_CTRL_4);
		atge_mii_write_raw(dp, MII_DBG_DATA,
		    11U << ANA_IECHO_ADJ_3_SHIFT
		    | 11U << ANA_IECHO_ADJ_2_SHIFT
		    | 8U << ANA_IECHO_ADJ_1_SHIFT
		    | 8U << ANA_IECHO_ADJ_0_SHIFT);
E 15

D 8
	/* enable link change interrupts */
	atge_mii_write_raw(dp, 18, 0x0c00);	/* common */
E 8
I 8
D 15
	/* common: enable link change interrupts */
	atge_mii_write_raw(dp, MII_IER, MII_IER_LINKUP | MII_IER_LINKDOWN);
E 15
I 15
		/* disable AZ(EEE) by default */
		if (lp->chip == CHIP_L1D ||
		    lp->chip == CHIP_L1D_2_0 ||
		    lp->chip == CHIP_L2C_B2) {
			OUTL(dp, LPICTRL,
			    INL(dp, LPICTRL) & ~LPICTRL_EN);
E 15

D 10
#ifdef CONFIG_1C
E 10
D 15
	switch (lp->chip) {
	case CHIP_L1C:
	case CHIP_L2C:
	case CHIP_L2C_B:
	case CHIP_L2C_B2:
	case CHIP_L1D:
	case CHIP_L1D_2_0:
E 15
I 15
			atge_mii_write_ext(dp,
			    MIIEXT_ANEG, MIIEXT_LOCAL_EEEADV, 0);
			atge_mii_write_ext(dp, MIIEXT_PCS, MIIEXT_CLDCTRL3,
			    L2CB_CLDCTRL3);
		}

E 15
		/*
		 * additional mii setting for L*C/L*D chipset
		 */
D 15
		atge_mii_write_raw(dp, MII_DBG_ADDR, MII_ANA_CTRL_18);
E 15
I 15
		/* ANACTRL */
		atge_mii_write_raw(dp, MII_DBG_ADDR, MII_ANA_CTRL_0);
E 15
		atge_mii_write_raw(dp, MII_DBG_DATA,
D 15
		    ANA_LOOP_SEL_10BT
		    | ANA_EN_MASK_TB
		    | ANA_EN_10BT_IDLE
		    | (1 << ANA_INTERVAL_SEL_TIMER_SHIFT));
E 15
I 15
		    ANA_RESTART_CAL
		    | 7U << ANA_MANUL_SWICH_ON_SHIFT
		    | ANA_MAN_ENABLE
		    | ANA_SEL_HSP
		    | ANA_EN_HB
		    | ANA_OEN_125M);
E 15

I 15
		/* SRDSYSMOD */
E 15
		atge_mii_write_raw(dp, MII_DBG_ADDR, MII_ANA_CTRL_5);
		atge_mii_write_raw(dp, MII_DBG_DATA,
D 15
		    (2 << ANA_SERDES_CDR_BW_SHIFT)
E 15
I 15
		    2U << ANA_SERDES_CDR_BW_SHIFT
E 15
		    | ANA_MS_PAD_DBG
		    | ANA_SERDES_EN_DEEM
		    | ANA_SERDES_SEL_HSP
		    | ANA_SERDES_EN_PLL
		    | ANA_SERDES_EN_LCKDT);

I 15
		/* TST10BTCFG */
		atge_mii_write_raw(dp, MII_DBG_ADDR, MII_ANA_CTRL_18);
		atge_mii_write_raw(dp, MII_DBG_DATA,
		    ANA_LOOP_SEL_10BT
		    | ANA_EN_MASK_TB
		    | ANA_EN_10BT_IDLE
		    | 1U << ANA_INTERVAL_SEL_TIMER_SHIFT);

		/* UNH-IOL test issue, set bit7 */ 
		/* TST100BTCFG */
E 15
		atge_mii_write_raw(dp, MII_DBG_ADDR, MII_ANA_CTRL_54);
		atge_mii_write_raw(dp, MII_DBG_DATA,
D 15
		    (44 << ANA_LONG_CABLE_TH_100_SHIFT)
		    | (33 << ANA_SHORT_CABLE_TH_100_SHIFT)
E 15
I 15
		    44U << ANA_LONG_CABLE_TH_100_SHIFT
		    | 33U << ANA_SHORT_CABLE_TH_100_SHIFT
E 15
		    | ANA_BP_BAD_LINK_ACCUM
		    | ANA_BP_SMALL_BW);

I 15
#ifdef notdef
		/* SYSMODCTRL */
E 15
		atge_mii_write_raw(dp, MII_DBG_ADDR, MII_ANA_CTRL_4);
		atge_mii_write_raw(dp, MII_DBG_DATA,
D 15
		    (11 << ANA_IECHO_ADJ_3_SHIFT)
		    | (11 << ANA_IECHO_ADJ_2_SHIFT)
		    | (8 << ANA_IECHO_ADJ_1_SHIFT)
		    | (8 << ANA_IECHO_ADJ_0_SHIFT));
E 15
I 15
		    11U << ANA_IECHO_ADJ_3_SHIFT
		    | 11U << ANA_IECHO_ADJ_2_SHIFT
		    | 8U << ANA_IECHO_ADJ_1_SHIFT
		    | 8U << ANA_IECHO_ADJ_0_SHIFT);
E 15

D 15
		atge_mii_write_raw(dp, MII_DBG_ADDR, MII_ANA_CTRL_0);
		atge_mii_write_raw(dp, MII_DBG_DATA,
		    ANA_RESTART_CAL
		    | (7 << ANA_MANUL_SWICH_ON_SHIFT)
		    | ANA_MAN_ENABLE
		    | ANA_SEL_HSP
		    | ANA_EN_HB
		    | ANA_OEN_125M);

E 15
I 15
		/* LEGCYPS */
E 15
		atge_mii_write_raw(dp, MII_DBG_ADDR, MII_ANA_CTRL_41);
		atge_mii_write_raw(dp, MII_DBG_DATA,
D 15
		    atge_mii_read(dp, MII_DBG_DATA)
E 15
I 15
		    atge_mii_read_raw(dp, MII_DBG_DATA)
E 15
		    & ~ANA_TOP_PS_EN);

I 15
		/* HIBNEG */
E 15
		atge_mii_write_raw(dp, MII_DBG_ADDR, MII_ANA_CTRL_11);
		atge_mii_write_raw(dp, MII_DBG_DATA,
D 15
		    atge_mii_read(dp, MII_DBG_DATA)
E 15
I 15
		    atge_mii_read_raw(dp, MII_DBG_DATA)
E 15
		    & ~ANA_PS_HIB_EN);
I 15
#endif
E 15
		break;
I 15

	default:
		/* do nothing */
		break;
E 15
	}
I 15

	/* common: enable link change interrupts */
	atge_mii_write_raw(dp, MII_IER, MII_IER_LINKUP | MII_IER_LINKDOWN);
E 15
D 10
#endif /* CONFIG_1C */
E 10
E 8
}

static void
E 3
atge_mii_sync(struct gem_dev *dp)
{
	/* nothing to do */
}

D 15
static uint16_t
atge_mii_read(struct gem_dev *dp, uint_t reg)
E 15
I 15
static uint32_t
atge_mii_idle(struct gem_dev *dp)
E 15
{
	int		i;
	uint32_t	val;
	struct atge_dev	*lp = dp->private;

I 15
	for (i = 0; (val = INL(dp, MIIC)) & (MIIC_GO | MIIC_BUSY); i++) {
		if (i > 120) {
			cmn_err(CE_WARN, "%s: %s: timeout",
			    dp->name, __func__);
			break;
		}
		drv_usecwait(20);
	}

	return (val);
}

static uint16_t
atge_mii_read_core(struct gem_dev *dp, uint_t phyid, uint_t reg)
{
	uint32_t	val;
	uint_t		clk;
	struct atge_dev	*lp = dp->private;

E 15
	DPRINTF(3, (CE_CONT, "!%s: %s: called at time:%d",
	    dp->name, __func__, ddi_get_lbolt()));

D 15
	OUTL(dp, MIIC, MIIC_CLK_4 | MIIC_GO | MIIC_SUPR | MIIC_READ
	    | (reg << MIIC_ADDR_SHIFT));
I 2
	drv_usecwait(2);
E 15
I 15
	clk = MIIC_CLK_4;
E 15
E 2

D 6
	for (i = 0;
	    (val = INL(dp, MIIC)) & (MIIC_GO | MIIC_BUSY);
	    i++) {
E 6
I 6
D 15
	for (i = 0; (val = INL(dp, MIIC)) & (MIIC_GO | MIIC_BUSY); i++) {
E 6
		if (i > 100) {
			cmn_err(CE_WARN, "%s: %s: timeout",
			    dp->name, __func__);
			return (0);
E 15
I 15
	switch (lp->chip) {
	case CHIP_L2C_B2:
	case CHIP_L1D_2_0:
		if (dp->mii_state != MII_STATE_LINKUP) {
			clk = MIIC_CLK_128;
E 15
		}
D 2
		drv_usecwait(10);
E 2
I 2
D 15
		drv_usecwait(2);
E 15
I 15
		break;
E 15
E 2
	}
I 15

	if (phyid == 0) {
		/* internal PHY */
		OUTL(dp, MIIC, clk | MIIC_GO | MIIC_SUPR | MIIC_READ
		    | reg << MIIC_ADDR_SHIFT);
	} else {
		/* extention registers */
		OUTL(dp, MIICEXT,
		    phyid << MIICEXT_DEVAD_SHIFT
		    | reg << MIICEXT_REG_SHIFT);
		OUTL(dp, MIIC, clk | MIIC_GO | MIIC_SUPR | MIIC_READ
		    | MIIC_EXT);
	}

	val = atge_mii_idle(dp);
	if (val & (MIIC_GO | MIIC_BUSY)) {
		/* timeout */
		val = 0;
	}

E 15
D 3

E 3
D 2
	DPRINTF(3, (CE_CONT, "%s: %s: reg:0x%x, val:0x%x",
E 2
I 2
	DPRINTF(3, (CE_CONT, "!%s: %s: reg:0x%x, val:0x%x",
E 2
	    dp->name, __func__, reg, val & MIIC_DATA));

I 15
	return (val & MIIC_DATA);
}

static uint16_t
atge_mii_read_raw(struct gem_dev *dp, uint_t reg)
{
	return (atge_mii_read_core(dp, 0, reg));
}

static uint16_t
atge_mii_read_ext(struct gem_dev *dp, uint_t phyid, uint_t reg)
{
	return (atge_mii_read_core(dp, phyid, reg));
}

static uint16_t
atge_mii_read(struct gem_dev *dp, uint_t reg)
{
	uint32_t	val;
	struct atge_dev	*lp = dp->private;

	val = atge_mii_read_raw(dp, reg);

E 15
I 3
	switch (reg) {
	case MII_STATUS:
		switch (lp->chip) {
		case CHIP_L2:
		case CHIP_L2E_B:
			/* mask XSTATUS bit in MII_STATUS register */
			val &= ~MII_STATUS_XSTATUS;
			break;
		}
		break;

	case MII_XSTATUS:
		switch (lp->chip) {
		case CHIP_L2E_A:
I 15
		case CHIP_L2C:
		case CHIP_L2C_B:
		case CHIP_L2C_B2:
E 15
D 7
			/* actually no 1giga bit capabilities */
E 7
I 7
			/* actually no giga bit capability */
E 7
			val = 0;
			break;
		}
		break;
	}

E 3
D 15
	return (val & MIIC_DATA);
E 15
I 15
	return (val);
E 15
}

static void
D 2
atge_mii_write(struct gem_dev *dp, uint_t reg, uint16_t val)
E 2
I 2
D 15
atge_mii_write_raw(struct gem_dev *dp, uint_t reg, uint16_t val)
E 15
I 15
atge_mii_write_core(struct gem_dev *dp, uint_t phyid, uint_t reg, uint16_t val)
E 15
E 2
{
D 2
	int		i;
	struct atge_dev	*lp = dp->private;
E 2
I 2
D 15
	int	i;
E 15
I 15
	uint_t	clk;
	struct atge_dev	*lp = dp->private;
E 15
E 2

D 2
	DPRINTF(3, (CE_CONT, "%s: %s: reg:0x%x, val:0x%x",
E 2
I 2
D 15
	DPRINTF(3, (CE_CONT, "!%s: %s: reg:0x%x, val:0x%x",
E 2
	    dp->name, __func__, reg, val));
E 15
I 15
	DPRINTF(3, (CE_CONT, "!%s: %s: phyid:0x%x, reg:0x%x, val:0x%x",
	    dp->name, __func__, phyid, reg, val));
E 15

D 2
	if (reg == MII_CONTROL && (val & MII_CONTROL_RESET)) {
		/* disable GPHYC once to program phy again */
		OUTW(dp, GPHYC, 0);
		FLSHW(dp, GPHYC);
		OUTW(dp, GPHYC, GPHYC_ENABLE);
		FLSHW(dp, GPHYC);
	}

E 2
D 15
	OUTL(dp, MIIC, MIIC_CLK_4 | MIIC_GO | MIIC_SUPR
	    | (reg << MIIC_ADDR_SHIFT) | val);
I 2
	drv_usecwait(2);
E 15
I 15
	clk = MIIC_CLK_4;
E 15
E 2

D 15
	for (i = 0; INL(dp, MIIC) & (MIIC_GO | MIIC_BUSY); i++) {
		if (i > 100) {
			cmn_err(CE_WARN,
			    "!%s: %s: timeout", dp->name, __func__);
			break;
E 15
I 15
	switch (lp->chip) {
	case CHIP_L2C_B2:
	case CHIP_L1D_2_0:
		if (dp->mii_state != MII_STATE_LINKUP) {
			clk = MIIC_CLK_128;
E 15
		}
D 2
		drv_usecwait(10);
E 2
I 2
D 15
		drv_usecwait(2);
E 15
I 15
		break;
E 15
E 2
	}
I 15

	if (phyid == 0) {
		/* internal phy */
		OUTL(dp, MIIC, clk | MIIC_GO | MIIC_SUPR
		    | reg << MIIC_ADDR_SHIFT | val);
	} else {
		/* extention registers */
		OUTL(dp, MIICEXT,
		    phyid << MIICEXT_DEVAD_SHIFT
		    | reg << MIICEXT_REG_SHIFT);
		OUTL(dp, MIIC, clk | MIIC_GO | MIIC_SUPR
		    | MIIC_EXT | val);
	}

	(void)atge_mii_idle(dp);
E 15
}

D 2
static int
atge_mii_init(struct gem_dev *dp)
E 2
I 2
static void
I 15
atge_mii_write_raw(struct gem_dev *dp, uint_t reg, uint16_t val)
{
	atge_mii_write_core(dp, 0, reg, val);
}

static void
atge_mii_write_ext(struct gem_dev *dp, uint_t phyid, uint_t reg, uint16_t val)
{
	atge_mii_write_core(dp, phyid, reg, val);
}

static void
E 15
atge_mii_write(struct gem_dev *dp, uint_t reg, uint16_t val)
E 2
{
D 2
	/* enable link change interrupt */
	atge_mii_write(dp, 18, 0x0c00);
E 2
I 2
	struct atge_dev	*lp = dp->private;
E 2

D 2
	/* exit power saving mode */
	atge_mii_write(dp, 29, 0x0029);
	atge_mii_write(dp, 30, 0x0000);
E 2
I 2
	DPRINTF(3, (CE_CONT, "!%s: %s: reg:0x%x, val:0x%x",
	    dp->name, __func__, reg, val));
E 2

D 2
	return (GEM_SUCCESS);
E 2
I 2
	if (reg == MII_CONTROL && (val & MII_CONTROL_RESET)) {
D 3
		/* disable GPHYC once to program phy */
		OUTW(dp, GPHYC, 0);
		delay(drv_usectohz(2000));
		OUTW(dp, GPHYC, GPHYC_ENABLE);
		delay(drv_usectohz(25000));
#ifndef CONFIG_AN_WITH_RESET
E 3
I 3
		/* reset PHY externally once to program phy */
		atge_reset_phy(dp);

E 3
		/*
D 6
		 * don't issue reset here, otherwise it occationally
E 6
I 6
		 * don't issue a reset here, otherwise it occationally
E 6
		 * advertises incorrect capability
		 */
D 3
		atge_mii_write_raw(dp, reg, val);
#endif
		/* enable link change interrupt */
		atge_mii_write_raw(dp, 18, 0x0c00);
#ifdef CONFIG_AN_WITH_RESET
E 3
	} else if (reg == MII_CONTROL && (val & MII_CONTROL_RSAN)) {
		/*
		 * We must issue AUTO-NEG with reset, otherwise
D 3
		 * it doesn't advertise current capability.
E 3
I 3
		 * it doesn't advertise the correct capability.
E 3
		 */
		atge_mii_write_raw(dp, reg, val | MII_CONTROL_RESET);
I 15

	} else if (reg == MII_CONTROL) {
		/*
		 * Avoid to write MII_CONTROL register without RESET bit
		 */

E 15
D 3
#endif
E 3
	} else {
		atge_mii_write_raw(dp, reg, val);
	}
E 2
}

static int
D 2
atge_mii_probe(struct gem_dev *dp)
E 2
I 2
atge_mii_init(struct gem_dev *dp)
E 2
{
D 3
	/* reset PHY first */
	OUTW(dp, GPHYC, 0);
D 2
	FLSHW(dp, GPHYC);
E 2
I 2
	delay(drv_usectohz(2000));
E 2
	OUTW(dp, GPHYC, GPHYC_ENABLE);
D 2
	FLSHW(dp, GPHYC);
E 2
I 2
	delay(drv_usectohz(2000));
	atge_mii_write_raw(dp, 18, 0x0c00);
E 3
I 3
	uint_t	uval;
	struct atge_dev	*lp = dp->private;
E 3
E 2

I 15
	sema_p(&dp->hal_op_lock);
E 15
D 3
	/* exit power saving mode */
	atge_mii_write(dp, 29, 0x0029);
	atge_mii_write(dp, 30, 0x0000);
E 3
I 3
	atge_reset_phy(dp);
E 3

I 3
	if (lp->chip == CHIP_L1) {
		/* exit power saving mode */
		atge_mii_write_raw(dp, 29, 0x0029);
		atge_mii_write_raw(dp, 30, 0x0000);
	}

I 15
	atge_mii_tune_phy(dp);

	sema_v(&dp->hal_op_lock);

E 15
E 3
I 2
	return (GEM_SUCCESS);
}

static int
atge_mii_probe(struct gem_dev *dp)
{
I 15
	sema_p(&dp->hal_op_lock);
E 15
D 6
	(void) atge_mii_init(dp);
E 6
I 6
	atge_reset_phy(dp);
I 15
	dp->mii_phy_addr = -1;
	sema_v(&dp->hal_op_lock);
E 15
E 6

E 2
	return (gem_mii_probe_default(dp));
}

I 15
static int
atge_mii_config(struct gem_dev *dp)
{
	int	ret;

	ret = gem_mii_config_default(dp);

	if (!dp->anadv_autoneg) {
		uint16_t	val;
		/*
		 * write specified mode to phy.
		 */
		val = gem_mii_read(dp, MII_CONTROL) &
		    ~(MII_CONTROL_SPEED | MII_CONTROL_FDUPLEX |
		    MII_CONTROL_ANE | MII_CONTROL_RSAN);

		if (dp->full_duplex) {
			val |= MII_CONTROL_FDUPLEX;
		}

		switch (dp->speed) {
		case GEM_SPD_1000:
			val |= MII_CONTROL_1000MB;
			break;

		case GEM_SPD_100:
			val |= MII_CONTROL_100MB;
			break;

		default:
			cmn_err(CE_WARN, "%s: unknown speed:%d",
			    dp->name, dp->speed);
			/* FALLTHROUGH */
		case GEM_SPD_10:
			/* for GEM_SPD_10, do nothing */
			break;
		}

		sema_p(&dp->hal_op_lock);
		atge_mii_write_raw(dp, MII_CONTROL, val | MII_CONTROL_RESET);
		sema_v(&dp->hal_op_lock);
	}

	return (ret);
}

static void
atge_mii_tune_phy(struct gem_dev *dp)
{
	boolean_t	adj_thresh;
	uint_t		phy_val;
	struct atge_dev	*lp = dp->private;

	switch (lp->chip) {
	case CHIP_L1C:
	case CHIP_L2C:
	case CHIP_L2C_B:
	case CHIP_L2C_B2:
	case CHIP_L1D:
	case CHIP_L1D_2_0:

		switch (lp->chip) {
		case CHIP_L2C_B:
		case CHIP_L2C_B2:
		case CHIP_L1D:
		case CHIP_L1D_2_0:
			adj_thresh = B_TRUE;
			break;

		default:
			adj_thresh = B_FALSE;
			break;
		}

		if (dp->mii_state == MII_STATE_LINKUP) {
			/* link up */
			atge_set_aspm_1c(dp, lp->ctrl_flags);
			/* az with brcm, half-amp */
			if (lp->chip == CHIP_L1D_2_0) {
				phy_val =  atge_mii_read_ext(dp,
				   MIIEXT_PCS, MIIEXT_CLDCTRL6);

				phy_val &= CLDCTRL6_CAB_LEN;
				phy_val >>= CLDCTRL6_CAB_LEN_SHIFT;

				phy_val = phy_val > CLDCTRL6_CAB_LEN_SHORT ?
					AZ_ANADECT_LONG : AZ_ANADECT_DEF;
				atge_mii_write_raw(dp,
				    MII_DBG_ADDR, MIIDBG_AZ_ANADECT);
				atge_mii_write_raw(dp,
				    MII_DBG_DATA, phy_val);
			}

			/* threshold adjust */
			if (adj_thresh && dp->speed == GEM_SPD_100 &&
			   lp->msi_lnkpatch) {
				atge_mii_write_raw(dp,
				    MII_DBG_ADDR, MIIDBG_MSE16DB);
				atge_mii_write_raw(dp,
				    MII_DBG_DATA, L1D_MSE16DB_UP);
				atge_mii_write_raw(dp,
				    MII_DBG_ADDR, MIIDBG_SYSMODCTRL);
				atge_mii_write_raw(dp,
				    MII_DBG_DATA, L1D_SYSMODCTRL_IECHOADJ_DEF);
			}
		} else {
			/* link down */
			atge_set_aspm_1c(dp, 0);
			if (adj_thresh && lp->msi_lnkpatch) {
				atge_mii_write_raw(dp,
				    MII_DBG_ADDR, MIIDBG_SYSMODCTRL);
				atge_mii_write_raw(dp,
				    MII_DBG_DATA, SYSMODCTRL_IECHOADJ_DEF);
				atge_mii_write_raw(dp,
				    MII_DBG_ADDR, MIIDBG_MSE16DB);
				atge_mii_write_raw(dp,
				    MII_DBG_DATA, L1D_MSE16DB_DOWN);
			}
		}
	}
}

E 15
/* ======================================================== */
/*
 * OS depend (device driver) routine
 */
/* ======================================================== */
I 7
static void
atge_power_up(dev_info_t *dip, ddi_acc_handle_t	conf_handle)
{
D 8
	uint_t	pcie_cap;
	uint32_t	devcap;
	uint32_t	devcsr;


	/* ensure we can access the registers through IO space. */
#if 0
E 8
I 8
	/* ensure we can access registers through IO space. */
E 8
	pci_config_put16(conf_handle, PCI_CONF_COMM,
	    (pci_config_get16(conf_handle, PCI_CONF_COMM)
	    | PCI_COMM_IO | PCI_COMM_ME | PCI_COMM_MAE)
	    & ~PCI_COMM_INTX_DISABLE);
D 8
#else
	pci_config_put16(conf_handle, PCI_CONF_COMM,
	    (pci_config_get16(conf_handle, PCI_CONF_COMM)
	    | PCI_COMM_IO | PCI_COMM_ME | PCI_COMM_MAE));
#endif
E 8

	/* ensure PME is clear */
	pci_config_put32(conf_handle, PM_CTRLSTAT, 0);
	delay(drv_usectohz(1000));

	/* ensure pmr status is D0 mode */
	(void) gem_pci_set_power_state(dip, conf_handle, PCI_PMCSR_D0);
D 8

	pcie_cap = gem_search_pci_cap(dip, conf_handle, PCI_CAP_ID_PCI_E);

	if (pcie_cap == 0) {
		cmn_err(CE_WARN, "%s%d: %s: pcie capability not found",
		    ddi_driver_name(dip), ddi_get_instance(dip), __func__);
		goto x;
	}
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
	/* read request */
	if ((devcsr & (7 << 12)) < (3 << 12)) {
		devcsr = (devcsr & ~(7 << 12)) | (3 << 12);
	}

	/*
	 * XXX - don't increase payload size. it caused to
	 * hang P5KPL-CM.
	 */
#ifdef notdef
	/* payload */
	if ((devcsr & (7 << 5)) < (3 << 5)) {
		devcsr = (devcsr & ~(7 << 5)) | (3 << 5);
	}
#endif
	pci_config_put32(conf_handle, pcie_cap + 8, devcsr);
x:
	;
E 8
}

I 15
#define	WOL_MAG		0x1
#define	WOL_LNKC	0x2

E 15
static void
D 15
atge_power_down(dev_info_t *dip)
E 15
I 15
atge_power_saving_1c(struct gem_dev *dp, uint32_t wolflag)
E 15
{
I 8
D 15
	/* not yet implemented */
E 15
I 15
	uint32_t	mstc;
	uint32_t	macctl;
	uint32_t	gphyc;
	uint32_t	wolctl;
	uint32_t	speed;
	uint16_t	phy_data;
	struct atge_dev	*lp = dp->private;

	wolctl = 0;

	mstc = INL(dp, MSTC);
	mstc &= ~MSTC_CLK_SEL_DIS_1c;

	macctl = INL(dp, MACCTL);
	if (dp->mii_state == MII_STATE_LINKUP &&
	    dp->speed == GEM_SPD_1000) {
		speed = MACCTL_SPEED_1000;
	} else {
		speed = MACCTL_SPEED_10_100;
	}
	macctl = (macctl & ~MACCTL_SPEED) | speed;
	macctl &= ~(MACCTL_FD | MACCTL_RX | MACCTL_TX);
	if (dp->full_duplex) {
		macctl |= MACCTL_FD;
	}

	gphyc = INL(dp, GPHYC);
	gphyc &= ~(GPHYC_EXT_RESET_1c | GPHYC_CLS_1c);

	if (wolflag == 0) {
		/* without WoL */
		mstc |= MSTC_CLK_SEL_DIS_1c;
		gphyc |= GPHYC_PHY_IDDQ | GPHYC_PWDOWN_HW;
		OUTL(dp, MSTC, mstc);
		OUTL(dp, MACCTL, macctl);
		OUTL(dp, GPHYC, gphyc);
		OUTL(dp, WOLCTL, 0);
		lp->initialized = B_FALSE;
		return;
	}

	gphyc |= GPHYC_EXT_RESET_1c;
	if (wolflag & WOL_MAG) {
		macctl |= MACCTL_RX | MACCTL_AB;
		wolctl |= WOLCTL_MGC_EN | WOLCTL_MGC_PME_EN;
		if (lp->chip == CHIP_L2C_B && lp->revid == 0xc1) {
			wolctl |= WOLCTL_PAT_EN | WOLCTL_PAT_PME_EN;
		}
	}

	if (wolflag & WOL_LNKC) {
		wolctl |= WOLCTL_LCHG_EN | WOLCTL_LCHG_PME_EN;
		atge_mii_write_raw(dp, MII_IER, MII_IER_LINKUP);
	}

	/* clear PHY interrupt */
	phy_data = atge_mii_read_raw(dp, MII_ISR);

	DPRINTF(0, (CE_CONT,
	    "!%s: suspend MAC:0x%x, MSTC:0x%x, GPHYC:0x%x ,WOLCTL:0x%x",
	    dp->name, macctl, mstc, gphyc, wolctl));

	OUTL(dp, MSTC, mstc);
	OUTL(dp, MACCTL, macctl);
	OUTL(dp, GPHYC, gphyc);
	OUTL(dp, WOLCTL, wolctl);
E 15
E 8
}

I 15
static void
atge_power_down(struct gem_dev *dp)
{
	struct atge_dev	*lp = dp->private;

	switch (lp->chip) {
	case CHIP_L1C:
	case CHIP_L2C:
	case CHIP_L2C_B:
	case CHIP_L2C_B2:
	case CHIP_L1D:
	case CHIP_L1D_2_0:
		atge_set_aspm_1c(dp, 0);
		atge_power_saving_1c(dp, 0);
		break;

	default:
		break;
	}
}

E 15
E 7
static int
atgeattach(dev_info_t *dip, ddi_attach_cmd_t cmd)
{
	int			i;
I 7
#if 0
E 7
	int			n;
I 7
#endif
E 7
	ddi_iblock_cookie_t	c;
	ddi_acc_handle_t	conf_handle;
	uint16_t		vid;
	uint16_t		did;
I 15
	uint16_t		subvid;
	uint16_t		subsid;
E 15
	uint8_t			revid;
	int			unit;
	struct chip_info	*p;
	const char		*drv_name;
	struct gem_dev		*dp;
	struct atge_dev		*lp;
	uint8_t			*base;
	ddi_acc_handle_t	reg_ha;
	struct gem_conf		*gcp;
	uint32_t		ilr;
I 3
	offset_t		io_off;
I 5
D 7
	uint_t			pcie_cap;
E 7
I 6
	int			mtu;
E 6
E 5
E 3

	unit = ddi_get_instance(dip);
	drv_name = ddi_driver_name(dip);

	DPRINTF(1, (CE_CONT, "!%s%d: %s: called at time:%d",
	    drv_name, unit, __func__, ddi_get_lbolt()));

	/*
	 * Common codes after power-up
	 */
	if (pci_config_setup(dip, &conf_handle) != DDI_SUCCESS) {
		cmn_err(CE_WARN, "!%s%d: pci_config_setup failed",
		    drv_name, unit);
		return (DDI_FAILURE);
	}

D 7
	/* ensure we can access the registers through IO space. */
	pci_config_put16(conf_handle, PCI_CONF_COMM,
	    PCI_COMM_IO | PCI_COMM_ME | PCI_COMM_MAE |
	    pci_config_get16(conf_handle, PCI_CONF_COMM));

I 2
	/* ensure PME is clear */
	pci_config_put32(conf_handle, PM_CTRLSTAT, 0);
	delay(drv_usectohz(1000));

E 2
	/* ensure the pmr status is D0 mode */
	(void) gem_pci_set_power_state(dip, conf_handle, PCI_PMCSR_D0);

E 7
	vid = pci_config_get16(conf_handle, PCI_CONF_VENID);
	did = pci_config_get16(conf_handle, PCI_CONF_DEVID);
I 15
	subvid = pci_config_get16(conf_handle, PCI_CONF_SUBVENID);
	subsid = pci_config_get16(conf_handle, PCI_CONF_SUBSYSID);
E 15
	revid = pci_config_get8(conf_handle, PCI_CONF_REVID);
	ilr = pci_config_get32(conf_handle, PCI_CONF_ILINE);
	DPRINTF(0, (CE_CONT, "!%s%d: ilr 0x%08x", drv_name, unit, ilr));

I 5
D 7
	pcie_cap = gem_search_pci_cap(dip, conf_handle, PCI_CAP_ID_PCI_E);

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
		if ((devcsr & (7 << 12)) < (3 << 12)) {
			devcsr = (devcsr & ~(7 << 12)) | (3 << 12);
			pci_config_put32(conf_handle,
			    pcie_cap + 8, devcsr);
		}
	}
E 5
	pci_config_teardown(&conf_handle);
I 5
	conf_handle = NULL;
E 5

E 7
	/* check chip revision and report it */
D 15
	for (i = 0, p = atge_chiptbl; i < CHIPTABLESIZE; i++, p++) {
E 15
I 15
	for (i = 0, p = atge_chiptbl; i < NITEMS(atge_chiptbl); i++, p++) {
E 15
		if (p->venid == vid && p->devid == did) {
			/* found */
			cmn_err(CE_CONT,
			    "!%s%d: %s "
			    "(vid: 0x%04x, did: 0x%04x, revid: 0x%02x)",
			    drv_name, unit, p->name, vid, did, revid);
			break;
		}
	}
D 15
	if (i >= CHIPTABLESIZE) {
E 15
I 15
	if (i >= NITEMS(atge_chiptbl)) {
E 15
		/* Not found */
		cmn_err(CE_NOTE,
		    "!%s%d: %s: unknown PCI venid/devid (0x%x, 0x%x)",
		    drv_name, unit, __func__, vid, did);
I 3
		/* assume the latest chipset */
D 15
		p = &atge_chiptbl[CHIPTABLESIZE - 1];
E 15
I 15
		p = &atge_chiptbl[NITEMS(atge_chiptbl) - 1];
E 15
E 3
	}

	switch (cmd) {
	case DDI_RESUME:
I 7
		atge_power_up(dip, conf_handle);

E 7
		dp = GEM_GET_DEV(dip);
		lp = dp->private;
		lp->initialized = B_FALSE;
I 6
		lp->phy_initialized = B_FALSE;
E 6
		return (gem_resume(dip));

	case DDI_ATTACH:
I 7
		atge_power_up(dip, conf_handle);

E 7
		if (gem_pci_regs_map_setup(dip,
		    PCI_ADDR_MEM64, PCI_ADDR_MASK,
		    &atge_dev_attr, (void *)&base, &reg_ha)
		    != DDI_SUCCESS) {
			goto err;
		}

		/*
I 3
		 * allocate local device structure
		 */
		lp = kmem_zalloc(sizeof (struct atge_dev), KM_SLEEP);
		lp->revid = revid;
		lp->initialized = B_FALSE;
I 6
		lp->phy_initialized = B_FALSE;
E 6
		lp->need_to_reset = B_FALSE;
		lp->isr_pended = 0;
I 6

		/* determin chip type */
E 6
#ifdef DEBUG_L1E
		lp->chip = CHIP_L1E;
#else
		lp->chip = p->chip_type;
#endif
		if (p->chip_type == CHIP_L1E) {
			/* fix chip type */
			if (revid >= 0xf0) {
				lp->chip = CHIP_L2E_B;
			} else {
				if (ddi_get32(reg_ha,
				    (void *)(base + PHYSTAT)) & PHYSTAT_100M) {
					lp->chip = CHIP_L1E;
				} else {
					lp->chip = CHIP_L2E_A;
				}
			}
		}

I 6
		/* configure initial value for gphyc register */
E 6
		switch (lp->chip) {
		case CHIP_L1:
		case CHIP_L2:
			lp->gphyc = 0;
			break;

D 7
		default:
E 7
I 7
		case CHIP_L1E:
		case CHIP_L2E_A:
		case CHIP_L2E_B:
E 7
			lp->gphyc = GPHYC_DEFAULT_1e;
			break;
I 7
D 10
#ifdef CONFIG_1C
E 10
I 10

E 10
		case CHIP_L1C:
		case CHIP_L2C:
		case CHIP_L2C_B:
		case CHIP_L2C_B2:
		case CHIP_L1D:
I 8
		case CHIP_L1D_2_0:
E 8
			lp->gphyc = GPHYC_DEFAULT_1c;
			break;
D 10
#endif
E 10
E 7
		}

I 6
		/* configure interrupts status bits */
		mtu = ddi_prop_get_int(DDI_DEV_T_ANY, dip,
		    DDI_PROP_DONTPASS, "mtu", ETHERMTU);
		DPRINTF(4, (CE_CONT, "!%s%d: %s: mtu:%d",
		    drv_name, unit, __func__, mtu));
		switch (lp->chip) {
		case CHIP_L1:
			lp->isr_disable = ISR_DIS_INT_1;
			lp->isr_enable = ISR_DIS_SM_1 | ISR_DIS_DMA_1;
D 7
			lp->isr_rx_err = 
E 7
I 7
			lp->isr_rx_err =
E 7
			    ISR_RXF_OVF_1 | ISR_RBD_UNRUN_1 | ISR_RSD_OVF_1 |
			    ISR_HOST_RBD_UNRUN_1 | ISR_HOST_RSD_OVF_1;
			lp->isr_rx_ok = ISR_ISM_RX_1;
			lp->isr_tx_err = 0;
D 7
#ifdef CONFIG_POLLING
E 7
I 7
#ifdef CONFIG_ADAPTIVE_COALESCE
E 7
			lp->isr_tx_ok = ISR_TX_DMA_1;
#else
			lp->isr_tx_ok = ISR_ISM_TX_1;
#endif
			lp->isr_dma_err =
			    ISR_DMAR_TO_RST_1 | ISR_DMAW_TO_RST_1;
			lp->isr_gphy = ISR_GPHY_1;
			lp->isr_sm = ISR_SM_1;
			lp->isr_pcie_err = ISR_PCIE_ERR_1;
			lp->isr_bits = ISR_BITS_1;
I 7
			lp->isr_fatal_err = 0;
			lp->isr_clear_all = 0x3fffffffU;
E 7
			break;

		case CHIP_L2:
			lp->isr_disable = ISR_DIS_INT_2;
			lp->isr_enable = 0;
D 7
			lp->isr_rx_err = 
E 7
I 7
			lp->isr_rx_err =
E 7
			    ISR_RXD_OV_2 | ISR_RXS_OV_2 | ISR_RXF_OVF_2;
			lp->isr_rx_ok = ISR_RX_UPDATE_2;
			lp->isr_tx_err = 0;
			lp->isr_tx_ok = ISR_TX_UPDATE_2;
			lp->isr_dma_err =
			    ISR_DMAR_TO_RST_2 | ISR_DMAW_TO_RST_2;
			lp->isr_gphy = ISR_PHY_2;
			lp->isr_sm = 0;
			lp->isr_pcie_err = ISR_PCIE_ERR_2;
			lp->isr_bits = ISR_BITS_2;
I 7
			lp->isr_fatal_err = 0;
			lp->isr_clear_all = 0x3fffffffU;
E 7
			break;

		case CHIP_L1E:
		case CHIP_L2E_A:
		case CHIP_L2E_B:
			lp->isr_disable = ISR_DIS_INT_1e;
			lp->isr_enable = 0;
			lp->isr_rx_err = ISR_RXF_OVF_1e | ISR_RXF0_OV_1e;
			lp->isr_rx_ok = ISR_RX_PKT_1e;
			lp->isr_tx_err = ISR_TXF_UNRUN_1e;
			lp->isr_tx_ok = ISR_TX_PKT_1e;
			lp->isr_dma_err =
			    ISR_DMAR_TO_RST_1e | ISR_DMAW_TO_RST_1e;
			lp->isr_gphy = ISR_GPHY_1e;
			lp->isr_sm = ISR_SM_1e;
			lp->isr_pcie_err = ISR_PCIE_ERR_1e;
			lp->isr_bits = ISR_BITS_1e;
I 7
			lp->isr_fatal_err = 0;
			lp->isr_clear_all = 0x7fffffffU;
E 7
			break;
I 7
D 10
#ifdef CONFIG_1C
E 10
I 10

E 10
		case CHIP_L1C:
		case CHIP_L2C:
		case CHIP_L2C_B:
		case CHIP_L2C_B2:
		case CHIP_L1D:
I 8
		case CHIP_L1D_2_0:
E 8
			lp->isr_disable = ISR_DIS_INT_1c;
			lp->isr_enable = 0;
			lp->isr_rx_err =
			    ISR_RFD0_UR_1c | ISR_RFD1_UR_1c |
			    ISR_RFD2_UR_1c | ISR_RFD3_UR_1c |
			    ISR_HW_RXF_OV_1c;
			lp->isr_rx_ok =
			    ISR_RX_PKT0_1c | ISR_RX_PKT1_1c |
			    ISR_RX_PKT2_1c | ISR_RX_PKT3_1c;
			lp->isr_tx_err = ISR_TXF_UR_1c | ISR_TXQ_TO_RST_1c;
			lp->isr_tx_ok = ISR_TX_PKT_1c;
			lp->isr_dma_err =
			    ISR_DMAR_TO_RST_1c | ISR_DMAW_TO_RST_1c;
			lp->isr_gphy = ISR_GPHY_1c;
			lp->isr_sm = ISR_SMB_1c;
			lp->isr_pcie_err = ISR_PHY_LINKDOWN_1c;
			lp->isr_bits = ISR_BITS_1c;
			lp->isr_fatal_err = 0;
			lp->isr_clear_all = 0x7fffffffU;
			break;
D 10
#endif
E 10
E 7
		}

E 6
		/*
		 * allocate ioarea
		 */
		io_off = 0;

		switch (lp->chip) {
		case CHIP_L1:
			/* statistics message area */
			lp->sm_offset = io_off = ROUNDUP(io_off, 8);
			io_off += sizeof (uint32_t) * STAT_MAX;
			DPRINTF(0, (CE_CONT, "!%s%d: sm_offset:0x%x",
			    drv_name, unit, lp->sm_offset));

			/* tx buffer descriptors */
			lp->tbd_offset = io_off = ROUNDUP(io_off, 8);
D 8
			io_off += sizeof (struct tx_buffer_desc) * TX_RING_SIZE;
E 8
I 8
			io_off +=
			    sizeof (struct tx_buffer_desc) * TX_RING_SIZE;
E 8
			DPRINTF(0, (CE_CONT, "!%s%d: tbd_offset:0x%x",
			    drv_name, unit,  lp->tbd_offset));

			/* rx buffer descriptors */
			lp->rbd_offset = io_off = ROUNDUP(io_off, 8);
D 8
			io_off += sizeof (struct rx_buffer_desc) * RX_BUF_SIZE;
E 8
I 8
			io_off +=
			    sizeof (struct rx_buffer_desc) * RX_BUF_SIZE;
E 8
			DPRINTF(0, (CE_CONT, "!%s%d: rbd_offset:0x%x",
			    drv_name, unit,  lp->rbd_offset));

			/* interrupt status message area */
			lp->ism_offset = io_off = ROUNDUP(io_off, 8);
			io_off += sizeof (struct intr_status_msg);
			DPRINTF(0, (CE_CONT, "!%s%d: ism_offset:0x%x",
			    drv_name, unit,  lp->ism_offset));
			break;

		case CHIP_L2:
			/* tx buffer descriptors */
			lp->tbd_offset = io_off = ROUNDUP(io_off, 8);
			lp->tbd_size = 1536 * TX_BUF_SIZE;
			io_off += lp->tbd_size;
			DPRINTF(0, (CE_CONT, "!%s%d: tbd_offset:0x%x",
			    drv_name, unit,  lp->tbd_offset));

			/*
			 * tx descriptors in gem are used for tx status
			 * descriptors
			 */

			/* rx buffer descriptors */
D 8
			lp->rbd_offset = io_off = ROUNDUP(io_off + 8, 128) - 8;
E 8
I 8
			lp->rbd_offset =
			    io_off = ROUNDUP(io_off + 8, 128) - 8;
E 8
			io_off += 1536 * RX_BUF_SIZE;
			DPRINTF(0, (CE_CONT, "!%s%d: rbd_offset:0x%x",
			    drv_name, unit,  lp->rbd_offset));
			break;

D 7
		default:
			/* L1E L2E_A L2E_B */
E 7
I 7
		case CHIP_L1E:
		case CHIP_L2E_A:
		case CHIP_L2E_B:
E 7
D 6
			/* statistics message area */
E 6
I 6
			/*
			 * Statistics message are *not* DMAed actually.
			 * But we allocate it in DMA area for compatibility
			 * with L1.
			 */
E 6
			lp->sm_offset = io_off = ROUNDUP(io_off, 8);
			io_off += sizeof (uint32_t) * STAT_MAX;
			DPRINTF(0, (CE_CONT, "!%s%d: sm_offset:0x%x",
			    drv_name, unit, lp->sm_offset));

			/* tx buffer descriptors */
			lp->tbd_offset = io_off = ROUNDUP(io_off, 64);
D 8
			io_off += sizeof (struct tx_buffer_desc) * TX_RING_SIZE;
E 8
I 8
			io_off +=
			    sizeof (struct tx_buffer_desc) * TX_RING_SIZE;
E 8
			DPRINTF(0, (CE_CONT, "!%s%d: tbd_offset:0x%x",
			    drv_name, unit,  lp->tbd_offset));

D 6
			/* rx buffer area */
			lp->rxf_buf_len = 1024 * (RX_BUF_SIZE / 2);
E 6
I 6
			/* rx buffer */
			lp->rxf_buf_len = ROUNDUP(
			    sizeof (struct ether_header) + mtu + VTAG_SIZE +
			    ETHERFCSL + sizeof (struct rx_status_desc), 32) *
			    (RX_BUF_SIZE / 2);
E 6

			lp->rxf_offset[0][0] = io_off = ROUNDUP(io_off, 32);
			io_off += lp->rxf_buf_len;
			DPRINTF(0, (CE_CONT, "!%s%d: rxf_offset[0][0]:0x%x",
			    drv_name, unit,  lp->rxf_offset[0][0]));

			lp->rxf_offset[0][1] = io_off = ROUNDUP(io_off, 32);
			io_off += lp->rxf_buf_len;
			DPRINTF(0, (CE_CONT, "!%s%d: rxf_offset[0][1]:0x%x",
			    drv_name, unit,  lp->rxf_offset[0][1]));

D 6
			/* tx_tail area */
E 6
I 6
			/* tx_tail */
E 6
			lp->tbd_tail_offset = io_off = ROUNDUP(io_off, 4);
			io_off += 4;
			DPRINTF(0, (CE_CONT, "!%s%d: tbd_tail_offset:0x%x",
			    drv_name, unit,  lp->tbd_tail_offset));

D 6
			/* rx mail box area */
E 6
I 6
			/* rx mail box */
E 6
			lp->rxf_mb_offset[0][0] = io_off = ROUNDUP(io_off, 4);
			io_off += 4;
D 8
			DPRINTF(0, (CE_CONT, "!%s%d: rxf_mb_offset[0][0]:0x%x",
E 8
I 8
			DPRINTF(0, (CE_CONT,
			    "!%s%d: rxf_mb_offset[0][0]:0x%x",
E 8
			    drv_name, unit,  lp->rxf_mb_offset[0][0]));

			lp->rxf_mb_offset[0][1] = io_off = ROUNDUP(io_off, 4);
			io_off += 4;
D 8
			DPRINTF(0, (CE_CONT, "!%s%d: rxf_mb_offset[0][1]:0x%x",
E 8
I 8
			DPRINTF(0, (CE_CONT,
			    "!%s%d: rxf_mb_offset[0][1]:0x%x",
E 8
			    drv_name, unit,  lp->rxf_mb_offset[0][1]));
I 7
			break;
D 10
#ifdef CONFIG_1C
E 10
I 10

E 10
		case CHIP_L1C:
		case CHIP_L2C:
		case CHIP_L2C_B:
		case CHIP_L2C_B2:
		case CHIP_L1D:
I 8
		case CHIP_L1D_2_0:
D 15
			/* the dma alignment seems 16byte, not 8 byte */
E 15
I 15
			/* dma alignment seems to be 16byte, not 8 byte */
E 15
E 8
			/* statistics message area */
D 8
			lp->sm_offset = io_off = ROUNDUP(io_off, 8);
E 8
I 8
			lp->sm_offset = io_off = ROUNDUP(io_off, 16);
E 8
			io_off += sizeof (uint32_t) * STAT_MAX;
			DPRINTF(0, (CE_CONT, "!%s%d: sm_offset:0x%x",
			    drv_name, unit, lp->sm_offset));

			/* tx buffer descriptors */
D 8
			lp->tbd_offset = io_off = ROUNDUP(io_off, 8);
			io_off += sizeof (struct tx_buffer_desc) * TX_RING_SIZE;
E 8
I 8
			lp->tbd_offset = io_off = ROUNDUP(io_off, 16);
			io_off +=
			    sizeof (struct tx_buffer_desc) * TX_RING_SIZE;
E 8
			DPRINTF(0, (CE_CONT, "!%s%d: tbd_offset:0x%x",
			    drv_name, unit,  lp->tbd_offset));

			/* rx free buffer descriptors */
D 8
			lp->rbd_offset = io_off = ROUNDUP(io_off, 8);
			io_off += sizeof (struct rx_free_desc) * RX_BUF_SIZE;
E 8
I 8
			lp->rbd_offset = io_off = ROUNDUP(io_off, 16);
			io_off +=
			    sizeof (struct rx_free_desc) * RX_BUF_SIZE;
E 8
			DPRINTF(0, (CE_CONT, "!%s%d: rbd_offset:0x%x",
			    drv_name, unit,  lp->rbd_offset));

			/* interrupt status message area */
D 8
			lp->ism_offset = io_off = ROUNDUP(io_off, 8);
E 8
I 8
			lp->ism_offset = io_off = ROUNDUP(io_off, 16);
E 8
			io_off += sizeof (struct intr_status_msg);
			DPRINTF(0, (CE_CONT, "!%s%d: ism_offset:0x%x",
			    drv_name, unit,  lp->ism_offset));
D 8
			break;
E 8
D 10
#endif
E 10
E 7
		}
		/* round up io area to the next 8 byte boundary */
		io_off = ROUNDUP(io_off, 8);

		/*
E 3
D 10
		 * construct gem configration
E 10
I 10
		 * construct gem configuration
E 10
		 */
		gcp = kmem_zalloc(sizeof (*gcp), KM_SLEEP);

		/* name */
		sprintf(gcp->gc_name, "%s%d", drv_name, unit);

		/* consistency on tx and rx */
		gcp->gc_tx_buf_align = sizeof (uint8_t) - 1;
D 3
		gcp->gc_tx_max_frags = MAXTXFRAGS;
#ifdef CONFIG_LSO
		gcp->gc_tx_max_descs_per_pkt = gcp->gc_tx_max_frags + 1;
#else
		gcp->gc_tx_max_descs_per_pkt = gcp->gc_tx_max_frags;
#endif
		gcp->gc_tx_desc_unit_shift = -1;
		gcp->gc_tx_buf_size = TX_BUF_SIZE;
D 2
		gcp->gc_tx_buf_limit = gcp->gc_tx_buf_size - 1;
E 2
I 2
		gcp->gc_tx_buf_limit = gcp->gc_tx_buf_size;
E 2
		gcp->gc_tx_ring_size = TX_RING_SIZE;
		gcp->gc_tx_ring_limit = gcp->gc_tx_ring_size - 1;

E 3
		gcp->gc_tx_auto_pad = B_TRUE;
D 3
		gcp->gc_tx_copy_thresh = atge_tx_copy_thresh;
E 3

		/* we use rx desc area for rx return descriptors */
		gcp->gc_rx_buf_align = sizeof (uint64_t) - 1;
		gcp->gc_rx_max_frags = 1;
D 3
		gcp->gc_rx_desc_unit_shift = 4;	/* 16 byte */
		gcp->gc_rx_ring_size = RX_RING_SIZE;
		gcp->gc_rx_buf_max = min(RX_BUF_SIZE, gcp->gc_rx_ring_size - 1);
		gcp->gc_rx_copy_thresh = atge_rx_copy_thresh;
E 3
I 3
		gcp->gc_rx_ring_size = RX_BUF_SIZE;
		gcp->gc_rx_buf_max = RX_BUF_SIZE - 1;
E 3

D 3
		gcp->gc_io_area_size = IOA_SIZE;
E 3
I 3
		gcp->gc_io_area_size = io_off;
E 3
		gcp->gc_hck_rx_start = sizeof (struct ether_header);

		/* map attributes */
		gcp->gc_dev_attr = atge_dev_attr;
		gcp->gc_buf_attr = atge_buf_attr;
		gcp->gc_desc_attr = atge_buf_attr;

		/* dma attributes */
		gcp->gc_dma_attr_desc = atge_dma_attr_desc;
		gcp->gc_dma_attr_txbuf = atge_dma_attr_buf;
		gcp->gc_dma_attr_txbuf.dma_attr_align =
		    gcp->gc_tx_buf_align + 1;
		gcp->gc_dma_attr_txbuf.dma_attr_sgllen = gcp->gc_tx_max_frags;
		gcp->gc_dma_attr_rxbuf = atge_dma_attr_buf;
		gcp->gc_dma_attr_rxbuf.dma_attr_align =
		    gcp->gc_rx_buf_align + 1;
		gcp->gc_dma_attr_rxbuf.dma_attr_sgllen = gcp->gc_rx_max_frags;

D 3

E 3
		/* timeout parameters */
		gcp->gc_tx_timeout = GEM_TX_TIMEOUT;
		gcp->gc_tx_timeout_interval = GEM_TX_TIMEOUT_INTERVAL;

		/* flow control */
I 8
#if 0
E 8
		gcp->gc_flow_control = FLOW_CONTROL_RX_PAUSE;
I 8
#else
		gcp->gc_flow_control = FLOW_CONTROL_NONE;
#endif
E 8

		/* MII timeout parameters */
		gcp->gc_mii_link_watch_interval = GEM_LINK_WATCH_INTERVAL;
		gcp->gc_mii_an_watch_interval = ONESEC/5;
		gcp->gc_mii_reset_timeout = MII_RESET_TIMEOUT;
		gcp->gc_mii_an_timeout = 45 * (ONESEC / 10);
D 2
		gcp->gc_mii_an_wait = 0;
E 2
I 2
		gcp->gc_mii_an_wait = ONESEC / 4;
E 2
		gcp->gc_mii_linkdown_timeout = MII_LINKDOWN_TIMEOUT;
D 2
#if 0
E 2
		gcp->gc_mii_hw_link_detection = B_TRUE;
D 2
#else
		gcp->gc_mii_hw_link_detection = B_FALSE;
#endif
E 2
I 2
D 13

E 13
E 2
		gcp->gc_mii_an_delay = 0;
		gcp->gc_mii_linkdown_action = MII_ACTION_RESET;
		gcp->gc_mii_linkdown_timeout_action = MII_ACTION_RESET;
I 2
D 15
#ifdef CONFIG_DONT_RESET_PHY
E 15
I 15
#ifdef CONFIG_DONT_RESET_PHY	/* not defined */
E 15
		gcp->gc_mii_dont_reset = B_TRUE;
#else
E 2
		gcp->gc_mii_dont_reset = B_FALSE;
I 2
#endif
E 2

		/* I/O methods */

		/* mac operation */
		gcp->gc_attach_chip = &atge_attach_chip;
I 10
#ifdef GEM_CONFIG_JUMBO_FRAME
		gcp->gc_fixup_params = &atge_fixup_params;
#endif
E 10
		gcp->gc_reset_chip = &atge_reset_chip;
D 3
		gcp->gc_init_chip = &atge_init_chip;
E 3
		gcp->gc_start_chip = &atge_start_chip;
		gcp->gc_stop_chip = &atge_stop_chip;
		gcp->gc_multicast_hash = &atge_mcast_hash;
		gcp->gc_set_rx_filter = &atge_set_rx_filter;
		gcp->gc_set_media = &atge_set_media;
		gcp->gc_get_stats = &atge_get_stats;
		gcp->gc_interrupt = &atge_interrupt;

I 15
		/* mii operations */
		gcp->gc_mii_probe = &atge_mii_probe;
		gcp->gc_mii_init = &atge_mii_init;
		gcp->gc_mii_config = &atge_mii_config;
		gcp->gc_mii_sync = &atge_mii_sync;
		gcp->gc_mii_read = &atge_mii_read;
		gcp->gc_mii_write = &atge_mii_write;
		gcp->gc_mii_tune_phy = &atge_mii_tune_phy;
		gcp->gc_mii_stop_mac_on_linkdown = B_FALSE;

		gcp->gc_hck_rx_start = sizeof (struct ether_header) + 20;

		/* enable MSI/MSIX interrupts */
		gcp->gc_nintrs_req = 1;

		gcp->gc_default_mtu = ETHERMTU;
		gcp->gc_min_mtu = ETHERMIN - sizeof (struct ether_header);

E 15
		/* descriptor operation */
D 3
		gcp->gc_tx_desc_write = &atge_tx_desc_write;
		gcp->gc_rx_desc_write = &atge_rx_desc_write;
		gcp->gc_tx_start = &atge_tx_start;
		gcp->gc_rx_start = &atge_rx_start;
		gcp->gc_tx_desc_stat = &atge_tx_desc_stat;
		gcp->gc_rx_desc_stat = &atge_rx_desc_stat;
		gcp->gc_tx_desc_init = &atge_tx_desc_init;
		gcp->gc_rx_desc_init = &atge_rx_desc_init;
		gcp->gc_tx_desc_clean = &atge_tx_desc_init;
		gcp->gc_rx_desc_clean = &atge_rx_desc_init;
		gcp->gc_get_packet = &gem_get_packet_default;
E 3
I 3
		switch (lp->chip) {
		case CHIP_L1:
			gcp->gc_tx_max_frags = MAXTXFRAGS;
#ifdef CONFIG_LSO
			gcp->gc_tx_max_descs_per_pkt = gcp->gc_tx_max_frags + 1;
#else
			gcp->gc_tx_max_descs_per_pkt = gcp->gc_tx_max_frags;
#endif
			gcp->gc_tx_buf_size = TX_BUF_SIZE;
			gcp->gc_tx_buf_limit = gcp->gc_tx_buf_size;
			gcp->gc_tx_ring_size = TX_RING_SIZE;
			gcp->gc_tx_ring_limit = gcp->gc_tx_ring_size - 1;
E 3

I 3
			/* tx: direct buffer */
			gcp->gc_tx_desc_unit_shift = -1;
			gcp->gc_tx_copy_thresh = atge_tx_copy_thresh;

			/* rx: direct buffer */
			gcp->gc_rx_desc_unit_shift = 4; /* desc */
			gcp->gc_rx_copy_thresh = atge_rx_copy_thresh;

			gcp->gc_init_chip = &atge_init_chip_1;

			gcp->gc_tx_desc_write = &atge_tx_desc_write_1_1e;
			gcp->gc_tx_start = &atge_tx_start_1_1e;
I 11
#ifdef GEM_CONFIG_TX_HEAD_PTR
			gcp->gc_tx_desc_stat = NULL;
D 15
			gcp->gc_tx_desc_head = &atge_tx_desc_head_1_1e;
E 15
I 15
			gcp->gc_tx_desc_head = &atge_tx_desc_head_1;
E 15
#else
E 11
D 15
			gcp->gc_tx_desc_stat = &atge_tx_desc_stat_1_1e;
E 15
I 15
			gcp->gc_tx_desc_stat = &atge_tx_desc_stat_1;
E 15
I 11
#endif /* GEM_CONFIG_TX_HEAD_PTR */
E 11
			gcp->gc_tx_desc_init = &atge_tx_desc_init_1_1e;
			gcp->gc_tx_desc_clean = &atge_tx_desc_init_1_1e;
			gcp->gc_rx_desc_write = &atge_rx_desc_write_1;
			gcp->gc_rx_start = &atge_rx_start_1;
			gcp->gc_get_packet = &gem_get_packet_default;
			gcp->gc_rx_desc_stat = &atge_rx_desc_stat_1;
			gcp->gc_rx_desc_init = &atge_rx_desc_init_1;
			gcp->gc_rx_desc_clean = &atge_rx_desc_init_1;
I 10

			gcp->gc_max_lso = 16 * 1024 - 1;
			gcp->gc_max_mtu =
			    10*1024 - sizeof (struct ether_header);
E 10
			break;

		case CHIP_L2:
			gcp->gc_tx_max_frags = 1;
			gcp->gc_tx_max_descs_per_pkt = 1;

			gcp->gc_tx_buf_size = TX_BUF_SIZE;
			gcp->gc_tx_buf_limit = gcp->gc_tx_buf_size;
			gcp->gc_tx_ring_size = TX_BUF_SIZE;
			gcp->gc_tx_ring_limit = gcp->gc_tx_ring_size - 1;

			/* tx: variable length ring with status descriptors */
			gcp->gc_tx_desc_unit_shift = 2;	/* 4byte */
			gcp->gc_tx_copy_thresh = INT32_MAX;

			/* rx: fixed length record ring */
			gcp->gc_rx_desc_unit_shift = -1;
			gcp->gc_rx_copy_thresh = INT32_MAX;

			gcp->gc_init_chip = &atge_init_chip_2;

			gcp->gc_tx_desc_write = &atge_tx_desc_write_2;
			gcp->gc_tx_start = &atge_tx_start_2;
			gcp->gc_tx_desc_stat = &atge_tx_desc_stat_2;
			gcp->gc_tx_desc_init = &atge_tx_desc_init_2;
			gcp->gc_tx_desc_clean = &atge_tx_desc_init_2;

			gcp->gc_rx_desc_write = &atge_rx_desc_write_2;
			gcp->gc_rx_start = &atge_rx_start_2;
			gcp->gc_get_packet = &atge_get_packet_2;
			gcp->gc_rx_desc_stat = &atge_rx_desc_stat_2;
			gcp->gc_rx_desc_init = &atge_rx_desc_init_2;
			gcp->gc_rx_desc_clean = &atge_rx_desc_init_2;
I 10

			gcp->gc_max_mtu = ETHERMTU;
E 10
			break;

		case CHIP_L1E:
		case CHIP_L2E_A:
		case CHIP_L2E_B:
			gcp->gc_tx_max_frags = MAXTXFRAGS;
#ifdef CONFIG_LSO
			gcp->gc_tx_max_descs_per_pkt = gcp->gc_tx_max_frags + 1;
#else
			gcp->gc_tx_max_descs_per_pkt = gcp->gc_tx_max_frags;
#endif
			gcp->gc_tx_buf_size = TX_BUF_SIZE;
			gcp->gc_tx_buf_limit = gcp->gc_tx_buf_size;
			gcp->gc_tx_ring_size = TX_RING_SIZE;
			gcp->gc_tx_ring_limit = gcp->gc_tx_ring_size - 1;

			/* tx: direct buffer */
			gcp->gc_tx_desc_unit_shift = -1; /* separate desc */
			gcp->gc_tx_copy_thresh = atge_tx_copy_thresh;

			/* rx: variable length record ring */
			gcp->gc_rx_desc_unit_shift = -1; /* ring */
			gcp->gc_rx_copy_thresh = INT32_MAX; /* ring */

			gcp->gc_init_chip = &atge_init_chip_1e;

			gcp->gc_tx_desc_write = &atge_tx_desc_write_1_1e;
			gcp->gc_tx_start = &atge_tx_start_1_1e;
I 11
#ifdef GEM_CONFIG_TX_HEAD_PTR
			gcp->gc_tx_desc_stat = NULL;
D 15
			gcp->gc_tx_desc_head = &atge_tx_desc_head_1_1e;
E 15
I 15
			gcp->gc_tx_desc_head = &atge_tx_desc_head_1e;
E 15
#else
E 11
D 15
			gcp->gc_tx_desc_stat = &atge_tx_desc_stat_1_1e;
E 15
I 15
			gcp->gc_tx_desc_stat = &atge_tx_desc_stat_1e;
E 15
I 11
#endif
E 11
			gcp->gc_tx_desc_init = &atge_tx_desc_init_1_1e;
			gcp->gc_tx_desc_clean = &atge_tx_desc_init_1_1e;
			gcp->gc_rx_desc_write = &atge_rx_desc_write_1e;
			gcp->gc_rx_start = NULL;
			gcp->gc_get_packet = &atge_get_packet_1e;
			gcp->gc_rx_desc_stat = &atge_rx_desc_stat_1e;
			gcp->gc_rx_desc_init = &atge_rx_desc_init_1e;
			gcp->gc_rx_desc_clean = &atge_rx_desc_init_1e;
I 10

			gcp->gc_max_lso = 16 * 1024 - 1;
			gcp->gc_max_mtu =
			    0x2000 - sizeof (struct ether_header);
E 10
			break;
I 7
D 10
#ifdef CONFIG_1C
E 10
I 10

E 10
		case CHIP_L1C:
		case CHIP_L2C:
		case CHIP_L2C_B:
		case CHIP_L2C_B2:
		case CHIP_L1D:
I 8
		case CHIP_L1D_2_0:
I 15
			for (i = 0; i < NITEMS(patch_list); i++) {
				struct patch_info	*p;

				p = &patch_list[i];
				if (p->devid == did &&
				    p->revid == revid &&
				    p->subvenid == subvid &&
				    p->subsysid == subsid) {
					/* found */
					lp->msi_lnkpatch = B_TRUE;
					break;
				}
			}
E 15
E 8
			gcp->gc_tx_max_frags = MAXTXFRAGS;
#ifdef CONFIG_LSO
			gcp->gc_tx_max_descs_per_pkt = gcp->gc_tx_max_frags + 1;
#else
			gcp->gc_tx_max_descs_per_pkt = gcp->gc_tx_max_frags;
#endif
			gcp->gc_tx_buf_size = TX_BUF_SIZE;
			gcp->gc_tx_buf_limit = gcp->gc_tx_buf_size;
			gcp->gc_tx_ring_size = TX_RING_SIZE;
			gcp->gc_tx_ring_limit = gcp->gc_tx_ring_size - 1;

			/* tx: direct buffer */
			gcp->gc_tx_desc_unit_shift = -1;
			gcp->gc_tx_copy_thresh = atge_tx_copy_thresh;

			/* rx: direct buffer */
			gcp->gc_rx_desc_unit_shift = 4; /* desc */
			gcp->gc_rx_copy_thresh = atge_rx_copy_thresh;

			gcp->gc_init_chip = &atge_init_chip_1c;

			gcp->gc_tx_desc_write = &atge_tx_desc_write_1c;
			gcp->gc_tx_start = &atge_tx_start_1c;
I 10
#ifdef GEM_CONFIG_TX_HEAD_PTR
			gcp->gc_tx_desc_stat = NULL;
			gcp->gc_tx_desc_head = &atge_tx_desc_head_1c;
#else
E 10
			gcp->gc_tx_desc_stat = &atge_tx_desc_stat_1c;
I 10
#endif
E 10
			gcp->gc_tx_desc_init = &atge_tx_desc_init_1c;
			gcp->gc_tx_desc_clean = &atge_tx_desc_init_1c;
			gcp->gc_rx_desc_write = &atge_rx_desc_write_1c;
			gcp->gc_rx_start = &atge_rx_start_1c;
			gcp->gc_get_packet = &gem_get_packet_default;
			gcp->gc_rx_desc_stat = &atge_rx_desc_stat_1c;
			gcp->gc_rx_desc_init = &atge_rx_desc_init_1c;
			gcp->gc_rx_desc_clean = &atge_rx_desc_init_1c;
I 10
D 15
#ifdef notyet
E 15
I 15

E 15
			gcp->gc_max_lso = 64 * 1024 - 1;
D 15
#else
			gcp->gc_max_lso = 16 * 1024 - 1;
#endif
E 15
			gcp->gc_max_mtu =
			    6*1024 - sizeof (struct ether_header);
I 15

			gcp->gc_mii_stop_mac_on_linkdown = B_TRUE;
E 15
E 10
			break;
D 8
#endif
E 8
I 8
D 10
#endif /* CONFIG_1C */
E 10
E 8
E 7
		}
I 7
		DPRINTF(-1, (CE_CONT,
		    "!%s: tx buf size:%d limit:%d, ring size:%d limit:%d",
		    __func__, gcp->gc_tx_buf_size, gcp->gc_tx_buf_limit,
		    gcp->gc_tx_ring_size, gcp->gc_tx_ring_limit));
E 7

E 3
D 15
		/* mii operations */
		gcp->gc_mii_probe = &atge_mii_probe;
		gcp->gc_mii_init = &atge_mii_init;
		gcp->gc_mii_config = &gem_mii_config_default;
		gcp->gc_mii_sync = &atge_mii_sync;
		gcp->gc_mii_read = &atge_mii_read;
		gcp->gc_mii_write = &atge_mii_write;
		gcp->gc_mii_tune_phy = NULL;
I 3
		gcp->gc_mii_stop_mac_on_linkdown = B_FALSE;
E 3

I 7
		gcp->gc_hck_rx_start = sizeof (struct ether_header) + 20;

E 7
I 6
		/* MSI/MSIX interrupts */
		gcp->gc_nintrs_req = 1;

I 7
D 10
		gcp->gc_max_lso = 16 * 1024 - 1;
		gcp->gc_max_mtu = ETHERMTU;
		gcp->gc_min_mtu = ETHERMTU;
E 10
I 10
		gcp->gc_default_mtu = ETHERMTU;
		gcp->gc_min_mtu = ETHERMIN - sizeof (struct ether_header);
E 10

E 15
E 7
E 6
D 3
		lp = kmem_zalloc(sizeof (struct atge_dev), KM_SLEEP);
		lp->revid = revid;
		lp->initialized = B_FALSE;
		lp->need_to_reset = B_FALSE;
I 2
		lp->isr_pended = 0;
E 2

E 3
		dp = gem_do_attach(dip, 0,
		    gcp, base, &reg_ha, lp, sizeof (*lp));

		kmem_free(gcp, sizeof (*gcp));
		if (dp == NULL) {
			goto  err_free_mem;
		}

I 7
		pci_config_teardown(&conf_handle);
E 7
		return (DDI_SUCCESS);

err_free_mem:
		kmem_free(lp, sizeof (struct atge_dev));
D 7
err:
		return (DDI_FAILURE);
E 7
	}
I 7
err:
	pci_config_teardown(&conf_handle);
E 7
	return (DDI_FAILURE);
}

static int
atgedetach(dev_info_t *dip, ddi_detach_cmd_t cmd)
{
I 2
	uint8_t	*mac;
E 2
	struct gem_dev  *dp = GEM_GET_DEV(dip);
	struct atge_dev  *lp = dp->private;

	switch (cmd) {
	case DDI_DETACH:
I 3
D 15
#ifdef notdef
E 15
E 3
I 2
		/* restore factory mac address */
I 15
		atge_power_down(dp);
E 15
		mac = dp->dev_addr.ether_addr_octet;
		OUTL(dp, MACADDR,
D 15
		    (mac[2] << 24) | (mac[3] << 16) | (mac[4] << 8) | mac[5]);
E 15
I 15
		    mac[2] << 24 | mac[3] << 16 | mac[4] << 8 | mac[5]);
E 15
		OUTL(dp, MACADDR + 4,
D 15
		    (mac[0] << 8) | mac[1]);
E 15
I 15
		    mac[0] << 8 | mac[1]);
E 15

		DPRINTF(0, (CE_NOTE,
		    "!%s: factory mac address %x:%x:%x:%x:%x:%x is restored.",
		    dp->name,
		    mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]));
D 3

E 3
I 3
D 15
#endif
E 15
E 3
E 2
		mutex_destroy(&lp->mbox_lock);
		return (gem_do_detach(dip));

	case DDI_SUSPEND:
I 15
		atge_power_down(dp);
E 15
		return (gem_suspend(dip));
	}
	return (DDI_FAILURE);
}

/* ======================================================== */
/*
 * OS depend (loadable streams driver) routine
 */
/* ======================================================== */
#ifdef GEM_CONFIG_GLDv3
D 3
DDI_DEFINE_STREAM_OPS(atge_ops, nulldev, nulldev, atgeattach, atgedetach,
    nodev, NULL, D_MP, NULL);
E 3
I 3
GEM_STREAM_OPS(atge_ops, atgeattach, atgedetach);
E 3
#else
static	struct module_info atgeminfo = {
	0,			/* mi_idnum */
	"atge",			/* mi_idname */
	0,			/* mi_minpsz */
	INFPSZ,			/* mi_maxpsz */
	64 * 1024,		/* mi_hiwat */
	1,			/* mi_lowat */
};

static	struct qinit atgerinit = {
	(int (*)()) NULL,	/* qi_putp */
	gem_rsrv,		/* qi_srvp */
	gem_open,		/* qi_qopen */
	gem_close,		/* qi_qclose */
	(int (*)()) NULL,	/* qi_qadmin */
	&atgeminfo,		/* qi_minfo */
	NULL			/* qi_mstat */
};

static	struct qinit atgewinit = {
	gem_wput,		/* qi_putp */
	gem_wsrv,		/* qi_srvp */
	(int (*)()) NULL,	/* qi_qopen */
	(int (*)()) NULL,	/* qi_qclose */
	(int (*)()) NULL,	/* qi_qadmin */
	&atgeminfo,		/* qi_minfo */
	NULL			/* qi_mstat */
};

static struct streamtab	atge_info = {
	&atgerinit,	/* st_rdinit */
	&atgewinit,	/* st_wrinit */
	NULL,		/* st_muxrinit */
	NULL		/* st_muxwrinit */
};

static	struct cb_ops cb_atge_ops = {
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
	&atge_info,	/* cb_stream */
	D_MP,		/* cb_flag */
D 3
#ifdef notdef
	CB_REV,		/* cb_rev */
	nodev,		/* cb_aread */
	nodev,		/* cb_awrite */
#endif
E 3
};

static	struct dev_ops atge_ops = {
	DEVO_REV,	/* devo_rev */
	0,		/* devo_refcnt */
	gem_getinfo,	/* devo_getinfo */
	nulldev,	/* devo_identify */
	nulldev,	/* devo_probe */
	atgeattach,	/* devo_attach */
	atgedetach,	/* devo_detach */
	nodev,		/* devo_reset */
	&cb_atge_ops,	/* devo_cb_ops */
	NULL,		/* devo_bus_ops */
D 11
	gem_power	/* devo_power */
E 11
I 11
	gem_power,	/* devo_power */
D 12
#if DEV0_REV >= 4
E 12
I 12
#if DEVO_REV >= 4
E 12
	gem_quiesce,	/* devo_quiesce */
#endif
E 11
};
#endif
static struct modldrv modldrv = {
	&mod_driverops,	/* Type of module.  This one is a driver */
	ident,
	&atge_ops,	/* driver ops */
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

	DPRINTF(2, (CE_CONT, "!atge: _init: called"));
D 15
	gem_mod_init(&atge_ops, "atge");
E 15
I 15
	status = gem_mod_init(&atge_ops, "atge");
	if (status != DDI_SUCCESS) {
		return (status);
	}
E 15
	status = mod_install(&modlinkage);
	if (status != DDI_SUCCESS) {
		gem_mod_fini(&atge_ops);
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

	DPRINTF(2, (CE_CONT, "!atge: _fini: called"));
	status = mod_remove(&modlinkage);
	if (status == DDI_SUCCESS) {
		gem_mod_fini(&atge_ops);
	}
	return (status);
}

int
_info(struct modinfo *modinfop)
{
	return (mod_info(&modlinkage, modinfop));
}
E 1
