h45921
s 00094/00072/02268
d D 1.12 11/09/28 23:10:27 mrym 12 11
c 2.6.6
e
s 00486/00681/01854
d D 1.11 05/01/01 01:03:05 mrym 11 10
c 2.6.4
e
s 00025/00017/02510
d D 1.10 07/11/04 07:20:52 mrym 10 9
c 2.6.3t0
e
s 00171/00105/02356
d D 1.9 07/09/18 01:17:49 mrym 9 8
c 2.6.2
e
s 00132/00138/02329
d D 1.8 07/08/31 00:06:02 mrym 8 7
c 2.6.1
e
s 00029/00042/02438
d D 1.7 07/08/19 21:43:23 mrym 7 6
c 2.6.0 fibre improved
e
s 00039/00051/02441
d D 1.6 07/08/18 19:24:34 mrym 6 5
c 2.6.0
e
s 00201/00058/02291
d D 1.5 07/03/29 23:29:01 mrym 5 4
c mii_read/mii_write phy address, config_mauto
e
s 00129/00089/02220
d D 1.4 06/11/04 21:24:08 mrym 4 3
c 2.4.0
e
s 00020/00010/02289
d D 1.3 06/06/16 00:15:04 mrym 3 2
c 2.2.1  RXMODE_ENABLE added, gem is the same with bfe-2.2.2
e
s 00003/00003/02296
d D 1.2 06/05/28 16:44:34 mrym 2 1
c 2.2.0
e
s 02299/00000/00000
d D 1.1 06/05/21 15:54:31 mrym 1 0
c date and time created 06/05/21 15:54:31 by mrym
e
u
U
f e 0
t
T
I 1
/*
D 11
 * vfe_gem.c: VIA Technology RHINE seris Fast Ethernet MAC driver
E 11
I 11
 * vfe.c: VIA Technology RHINE seris Fast Ethernet MAC driver
E 11
 *
D 3
 * Copyright (c) 2002-2005 Masayuki Murayama.  All rights reserved.
E 3
I 3
D 5
 * Copyright (c) 2002-2006 Masayuki Murayama.  All rights reserved.
E 5
I 5
D 11
 * Copyright (c) 2002-2007 Masayuki Murayama.  All rights reserved.
E 5
E 3
 * 
E 11
I 11
D 12
 * Copyright (c) 2002-2008 Masayuki Murayama.  All rights reserved.
E 12
I 12
 * Copyright (c) 2002-2011 Masayuki Murayama.  All rights reserved.
E 12
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
D 11
#pragma	ident	"%W% %E%"
E 11
I 11
#pragma	ident	"%Z%%M% %I%     %E%"
E 11

/*
D 11
 Change log
 0.9.0	11/23/2002
	first release of gem based vfe driver

 0.9.1  11/30/2002
	Added debugging code for rhine1 emulation on rhine2 chips.
	0.9.0 did not work for rhine1 chips because gem did not check
	tx buffer alignment. Gem was fixed.

 0.9.2  12/1/2002
	vfe_set_rx_filter(): multcast hash table was fixed
	Issue MII_RESET on attach

	02/16/2003
	struct gc cleared. gem_get_packet_default added.

	02/17/2003 vfe_get_stats fixed for rhine I.
 0.9.3  02/17/2003 release
 	04/12/2002 ddi_dma_sync added
 	04/26/2002 vfe_tx_desc_write was fixed for type mismactch.
 		   calling ddi_get/put8 in vfeattach fixed for type mismatch
		   multicast cam filtering added (not tested)
		   shape up source code
 0.9.4  04/27/2003 release
 0.9.5  05/18/2003 no interrupt implemented
 0.9.5  05/18/2003 release
 0.9.8
        11/10/2003 vfe_mii_init() removed
 1.0.0  11/10/2003 release
		   burst size tuning on tx underflow/rx overflow implemented.
 1.0.1  03/07/2004 release
		   TDWBI workaround implemented. Tx errors gone!
		   Licensing changed to the BSD license from LGPL.
 1.0.2  04/01/2004 release
		   a workaround for VT6103 implemented in vfe_mii_write.
 1.0.5  04/29/2004 release
		   tx interrput optimizatoin for rhine1
 1.0.7  05/29/2004 release
		   bus error while eeprom autoloading fixed.
		   RCR accessed in wrong size (long).
 1.0.8  06/06/2004 release
 1.0.12 08/09/2004 vfe_set_rx_filter fixed not to stop the nic core.
 1.0.18 04/12/2005 ddi_put/get are used for descriptor access
I 3
 2.0.0
 2.2.0
	06/16/2006 set_rx_filter: RXMODE_ENABLE added
 2.2.1
I 4
	11/03/2006 TDWB workaround fixed.
 2.4.0
I 5
	03/28/2007 phy address was not specified in mii read/write routines
I 6
 2.6.0
	08/18/2007 ndd supported
I 8
 2.6.1
D 10
	08/31/2007 code cleanup
E 10
I 10
	08/31/2007 code clean up
E 10
I 9
 2.6.2
	09/17/2007 error statistics fixed
I 10
 2.6.3t0
	11/04/2007 clean up
E 10
E 9
E 8
E 6
E 5
E 4
E 3
 */

/*
 TODO:
D 6
	tuning on tx underflow.
E 6
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
I 9
#include <sys/byteorder.h>
E 9
D 11

E 11
I 11
#include <sys/ethernet.h>
E 11
#include <sys/pci.h>
I 11

E 11
D 9
#include "mii.h"
E 9
I 9
#include "gem_mii.h"
E 9
#include "gem.h"
I 11

E 11
#include "rhinereg.h"

char	ident[] = "via rhine nic driver v" VERSION;

/* Debugging support */
#ifdef DEBUG_LEVEL
static int vfe_debug = DEBUG_LEVEL;
D 11
#define	DPRINTF(n, args)	if (vfe_debug>(n)) cmn_err args
E 11
I 11
#define	DPRINTF(n, args)	if (vfe_debug > (n)) cmn_err args
E 11
#else
#define	DPRINTF(n, args)
#endif

/*
 * Useful macros and typedefs
 */
#define	ONESEC	drv_usectohz(1*1000000)

I 11
#ifdef MAP_MEM
#define	FLSHL(dp, r)	(void)INL(dp, r)
#define	FLSHW(dp, r)	(void)INW(dp, r)
#define	FLSHB(dp, r)	(void)INB(dp, r)
#else
#ifdef __sparc
#define	FLSHL(dp, r)	(void)INL(dp, r)
#define	FLSHW(dp, r)	(void)INW(dp, r)
#define	FLSHB(dp, r)	(void)INB(dp, r)
#else
#define	FLSHL(dp, r)
#define	FLSHW(dp, r)
#define	FLSHB(dp, r)
#endif /* __sparc */
#endif /* MAP_MEM */

E 11
D 8
#define	RH_WRITE_IMR(dp, imr)	{	\
E 8
I 8
#define	VFE_WRITE_IMR(dp, imr)	{	\
E 8
	OUTW((dp), IMR, (imr));	\
D 3
	if (((struct vfe_dev *)dp->private)->revid > 0x40) {	\
E 3
I 3
	if (((struct vfe_dev *)(dp)->private)->revid > 0x40) {	\
E 3
		OUTB((dp), MIMR, (imr) >> 16);	\
	}	\
}

D 8
#define	RH_WRITE_ISR(dp, isr)	{	\
E 8
I 8
#define	VFE_WRITE_ISR(dp, isr)	{	\
E 8
	OUTW((dp), ISR, (isr));	\
D 3
	if (((struct vfe_dev *)dp->private)->revid > 0x40) {	\
E 3
I 3
	if (((struct vfe_dev *)(dp)->private)->revid > 0x40) {	\
E 3
		OUTB((dp), MISR, (isr) >> 16);	\
	}	\
}

D 8
#define	RH_READ_ISR(dp, isr)	{	\
E 8
I 8
#define	VFE_READ_ISR(dp, isr)	{	\
E 8
D 9
	isr = INW((dp), ISR);	\
E 9
I 9
	(isr) = INW((dp), ISR);	\
E 9
D 3
	if (((struct vfe_dev *)dp->private)->revid > 0x40) {	\
E 3
I 3
	if (((struct vfe_dev *)(dp)->private)->revid > 0x40) {	\
E 3
D 9
		isr |= INB((dp), MISR) << 16;	\
E 9
I 9
		(isr) |= INB((dp), MISR) << 16;	\
E 9
	}	\
}

D 8
#define	RH_KICK_TX(dp, cr)	{	\
E 8
I 8
#define	VFE_KICK_TX(dp, cr)	{	\
E 8
D 6
	if (IS_RHINE3M_OR_LATER(((struct vfe_dev *)(dp)->private)->revid)) { \
E 6
I 6
	if (IS_RHINE3M(((struct vfe_dev *)(dp)->private)->revid)) { \
E 6
		OUTB((dp), TXQW, 1 << 7);	\
	}	\
	OUTB((dp), CR+1, ((CR_TDMD1 | (cr)) >> 8));	\
}

I 9
D 11
#define	VFE_KICK_RX(dp, cr)	OUTB((dp), CR+1, ((CR_RDMD1 | (cr)) >> 8))
E 11
I 11
#define	VFE_TXDESC(p)	((struct tx_desc *)(void *)(p))
#define	VFE_RXDESC(p)	((struct rx_desc *)(void *)(p))
E 11

E 9
I 4
D 11
/* workaroud for TDWB problem */
E 11
I 11
#define	VFE_KICK_RX(dp, cr)	{ \
	OUTB((dp), CR+1, ((CR_RDMD1 | (cr)) >> 8));	\
}

/* workaround for TDWB problem */
E 11
#define	TSR_TDWB	TSR_JAB	/* this bit isn't defined for 6102 */

E 4
D 11
#ifdef MAP_MEM
# define	FLSHB(dp, reg)	INB(dp, reg)
# define	FLSHW(dp, reg)	INW(dp, reg)
# define	FLSHL(dp, reg)	INL(dp, reg)
#else
# define	FLSHB(dp, reg)
# define	FLSHW(dp, reg)
# define	FLSHL(dp, reg)
#endif

E 11
D 8
#define	STRUCT_COPY(a, b)	bcopy(&(b), &(a), sizeof(a))

E 8
D 4
#define	LE32(x)	((uint32_t)(x))
E 4
I 4
D 9
#if defined(sun4u)
# define LE16(x)	ddi_swap16(x)
# define LE32(x)	ddi_swap32(x)
# define LE64(x)	ddi_swap64(x)
#else
# define LE16(x)	(x)
# define LE32(x)	(x)
# define LE64(x)	(x)
#endif
E 4

E 9
/*
 * Our configuration
 */
D 11
#if defined(CONFIG_OO) || defined(PTX_TEST)
#define MAXTXFRAGS	1
#else
#define MAXTXFRAGS	GEM_MAXTXFRAGS
#endif

E 11
#define	OUR_INTR_BITS	\
	(ISR_ABTI | ISR_NORBF | ISR_PKRACE | ISR_OVFI |	\
D 11
	 ISR_CNT | ISR_BE | ISR_RU | ISR_TU |	\
	 ISR_RXE | ISR_TXE | 	\
	 ISR_PTX | ISR_PRX)
E 11
I 11
	ISR_CNT | ISR_BE | ISR_RU | ISR_TU |	\
	ISR_RXE | ISR_TXE | ISR_PTX | ISR_PRX)
E 11

I 11
#ifdef GEM_CONFIG_TX_DIRECT
#define	MAXTXFRAGS	(min(8, GEM_MAXTXFRAGS))
#else
#define	MAXTXFRAGS	1
#endif

E 11
#ifdef TEST_RX_EMPTY
D 11
# define RX_BUF_SIZE	1
E 11
I 11
#define	RX_BUF_SIZE	1
E 11
#endif
#ifdef TEST_TXDESC_FULL
D 11
# define TX_BUF_SIZE	4
# define TX_RING_SIZE	8
E 11
I 11
#define	TX_BUF_SIZE	4
#define	TX_RING_SIZE	8
E 11
#endif

#ifndef TX_BUF_SIZE
D 11
# define TX_BUF_SIZE	64
E 11
I 11
#define	TX_BUF_SIZE	64
E 11
#endif
I 11

E 11
#ifndef TX_RING_SIZE
D 11
# define TX_RING_SIZE	(TX_BUF_SIZE*4)
E 11
I 11
#if MAXTXFRAGS == 1
#define	TX_RING_SIZE	TX_BUF_SIZE
#else
#define	TX_RING_SIZE	(TX_BUF_SIZE*4)
E 11
#endif
I 11
#endif
E 11

#ifndef RX_BUF_SIZE
D 9
# define RX_BUF_SIZE	64
E 9
I 9
D 11
# define RX_BUF_SIZE	256
E 11
I 11
#define	RX_BUF_SIZE	256
E 11
E 9
#endif
D 11
#ifndef RX_RING_SIZE
# define RX_RING_SIZE	RX_BUF_SIZE
#endif
E 11

D 9
#if RX_RING_SIZE >= 256
#  error RX_RING_SIZE must be less than 256
#endif

E 9
static int	vfe_tx_copy_thresh = 256;
static int	vfe_rx_copy_thresh = 256;

/*
 * rhine chip state
 */
struct vfe_dev {
	uint8_t		mac_addr[ETHERADDRL];
	uint16_t	cr;	/* soft copy of command reg. */
	uint8_t		revid;	/* chip revision id */
	uint8_t		tft;	/* tx fifo threshold */
	uint8_t		rft;	/* rx fifo threshold */
	uint8_t		maxdma;
D 11
	volatile uint32_t	imr;
	volatile uint32_t	imr_hw;
E 11
I 11
	uint32_t	imr;
#ifdef WA_SPURIOUS_INTR
	uint32_t	isr_pended;
#endif
E 11
I 5
	int		last_phy_addr;
E 5
D 4
	boolean_t	td_unreliable;
E 4
#ifdef RESET_TEST
	int		reset_test;
#endif
D 11
#ifdef OPT_TX_INTR
	ddi_softintr_t	soft_id;
	boolean_t	imr_change_req;
#endif
E 11
I 4
#ifdef TEST_TDWB
	int		tdwb_cnt;
#endif
E 4
};

/*
 * Supported chips
 */
struct chip_info {
	uint16_t	venid;
	uint16_t	devid;
	char		*name;
};

static struct chip_info vfe_chiptbl[] = {
	{VID_VIA, DID_VT3043, "DL10030/VT86C100A Rhine"},
D 5
	{VID_VIA, DID_VT6102, "VT6102 Rhine-II"},
E 5
I 5
D 11
	{VID_VIA, DID_VT6102, "VT6102/VT6107 Rhine-II"},
E 5
	{VID_VIA, DID_VT6105, "VT6105 Rhine-III"},
E 11
I 11
	{VID_VIA, DID_VT6102, "VT6102 Rhine-II"},
	{VID_VIA, DID_VT6105, "VT6105/VT6107 Rhine-III"},
E 11
	{VID_VIA, DID_VT6105M, "VT6105M Rhine-III"},
};
D 11
#define CHIPTABLESIZE   (sizeof(vfe_chiptbl)/sizeof(struct chip_info))
E 11
I 11
#define	CHIPTABLESIZE   (sizeof (vfe_chiptbl)/sizeof (struct chip_info))
E 11

/*
 * Macros to identify chip generation.
 */
#define	IS_RHINE1_VT86C100A_E(r)	((r) <= 0x4)
#define	IS_RHINE1_VT86C100A(r)		((r) < 0x20)
#define	IS_RHINE1(r)			((r) < 0x40)
#define	IS_RHINE2(r)			(0x40 <= (r) && (r) < 0x80)
#define	IS_RHINE2_OR_LATER(r)		(0x40 <= (r))
#define	IS_RHINE3(r)			(0x80 <= (r) && (r) < 0x90)
#define	IS_RHINE3_OR_LATER(r)		(0x80 <= (r))
D 5
#define	IS_RHINE3LOM(r)			(0x8a <= (r) && (r) < 0x90)
E 5
I 5
D 11
#define	IS_RHINE3LOM(r)			(0x8a <= (r) && (r) < 0x90)	
E 11
I 11
#define	IS_RHINE3LOM(r)			(0x8a <= (r) && (r) < 0x90)
E 11
E 5
#define	IS_RHINE3M(r)			(0x90 <= (r))
D 6
#define	IS_RHINE3M_OR_LATER(r)		(0x90 <= (r))
E 6
I 5
D 11
#define	IS_VT6107A1_OR_LATER(r)		(0x8d <= (r) && (r) < 0x90)
E 11
I 11
#define	IS_VT6107A1(r)			(0x8d <= (r) && (r) < 0x90)
E 11
E 5

#define	IS_VT6103(phyid)	\
	(((phyid) & 0xfffffff0) == 0x01018f20 && ((phyid) & 0xf) > 4)
/* ======================================================== */
D 11
 
E 11
I 11

E 11
/* mii operations */
static void  vfe_mii_sync(struct gem_dev *);
static uint16_t  vfe_mii_read(struct gem_dev *, uint_t);
static void vfe_mii_write(struct gem_dev *, uint_t, uint16_t);
D 11
static int vfe_mii_init(struct gem_dev *);
E 11

/* nic operations */
static int vfe_attach_chip(struct gem_dev *);
static int vfe_reset_chip(struct gem_dev *);
D 4
static void vfe_init_chip(struct gem_dev *);
static void vfe_start_chip(struct gem_dev *);
E 4
I 4
static int vfe_init_chip(struct gem_dev *);
static int vfe_start_chip(struct gem_dev *);
E 4
static int vfe_stop_chip(struct gem_dev *);
D 4
static void vfe_set_media(struct gem_dev *);
static void vfe_set_rx_filter(struct gem_dev *);
static void vfe_get_stats(struct gem_dev *);
E 4
I 4
static int vfe_set_media(struct gem_dev *);
static int vfe_set_rx_filter(struct gem_dev *);
static int vfe_get_stats(struct gem_dev *);
E 4

/* descriptor operations */
static int vfe_tx_desc_write(struct gem_dev *dp, int slot,
D 6
		    ddi_dma_cookie_t *dmacookie, int frags, uint32_t flags);
E 6
I 6
		    ddi_dma_cookie_t *dmacookie, int frags, uint64_t flags);
E 6
static void vfe_tx_start(struct gem_dev *dp, int startslot, int nslot);
static void vfe_rx_desc_write(struct gem_dev *dp, int slot,
		    ddi_dma_cookie_t *dmacookie, int frags);
static void vfe_rx_start(struct gem_dev *dp, int startslot, int nslot);
static uint_t vfe_tx_desc_stat(struct gem_dev *dp, int slot, int ndesc);
static uint64_t vfe_rx_desc_stat(struct gem_dev *dp, int slot, int ndesc);

static void vfe_tx_desc_init(struct gem_dev *dp, int slot);
static void vfe_rx_desc_init(struct gem_dev *dp, int slot);
static void vfe_tx_desc_clean(struct gem_dev *dp, int slot);
static void vfe_rx_desc_clean(struct gem_dev *dp, int slot);

/* interrupt handler */
D 11
static u_int vfe_interrupt(struct gem_dev *dp);
E 11
I 11
static uint_t vfe_interrupt(struct gem_dev *dp);
E 11

/* ======================================================== */

/* mapping attributes */
/* Data access requirements. */
static struct ddi_device_acc_attr vfe_dev_attr = {
	DDI_DEVICE_ATTR_V0,
	DDI_STRUCTURE_LE_ACC,
	DDI_STRICTORDER_ACC
};

/* On sparc, the buffers should be native endianness */
static struct ddi_device_acc_attr vfe_buf_attr = {
	DDI_DEVICE_ATTR_V0,
	DDI_NEVERSWAP_ACC,	/* native endianness */
	DDI_STRICTORDER_ACC
};

static ddi_dma_attr_t vfe_dma_attr_buf = {
	DMA_ATTR_V0,		/* dma_attr_version */
	0,			/* dma_attr_addr_lo */
	0xffffffffull,		/* dma_attr_addr_hi */
D 9
	0xffffffffull,		/* dma_attr_count_max */
E 9
I 9
D 11
	0x00003fffull,		/* dma_attr_count_max */
E 9
	0,/* patched later */	/* dma_attr_align */
E 11
I 11
	0x000007ffull,		/* dma_attr_count_max */
	0, /* patched later */	/* dma_attr_align */
E 11
D 9
	0xffffffff,		/* dma_attr_burstsizes */
E 9
I 9
	0x00003ffc,		/* dma_attr_burstsizes */
E 9
	1,			/* dma_attr_minxfer */
D 9
	0xffffffffull,		/* dma_attr_maxxfer */
E 9
I 9
D 11
	0x00003fffull,		/* dma_attr_maxxfer */
E 11
I 11
	0x000007ffull,		/* dma_attr_maxxfer */
E 11
E 9
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

static ddi_dma_attr_t vfe_dma_attr_desc = {
	DMA_ATTR_V0,		/* dma_attr_version */
	0,			/* dma_attr_addr_lo */
	0xffffffffull,		/* dma_attr_addr_hi */
	0xffffffffull,		/* dma_attr_count_max */
	16,			/* dma_attr_align */
D 9
	0xffffffff,		/* dma_attr_burstsizes */
E 9
I 9
	0xfffffffc,		/* dma_attr_burstsizes */
E 9
	1,			/* dma_attr_minxfer */
	0xffffffffull,		/* dma_attr_maxxfer */
	0xffffffffull,		/* dma_attr_seg */
	1,			/* dma_attr_sgllen */
	1,			/* dma_attr_granular */
	0			/* dma_attr_flags */
};

/* ======================================================== */
/*
D 11
 * HW manupilation routines
E 11
I 11
 * HW manipulation routines
E 11
 */
/* ======================================================== */
static void
I 9
D 11
vfe_freeze_rx(struct gem_dev *dp)
{
	int	cnt;
	struct vfe_dev	*lp = (struct vfe_dev *)dp->private;

	if ((lp->cr & CR_RXON) == 0) {
		return;
	}

	OUTW(dp, CR, lp->cr & ~CR_RXON);
	drv_usecwait(10);

	/* wait a while until rx side stops */
	for (cnt = 0; INW(dp, CR) & CR_RXON; cnt++) {
		if (cnt > 100) {
			cmn_err(CE_CONT,
			"%s: %s: timeout: rx side is still active.",
				dp->name, __func__);
			break;
		}
		drv_usecwait(10);
	}
}

static void
vfe_restart_rx(struct gem_dev *dp)
{
	struct vfe_dev	*lp = (struct vfe_dev *)dp->private;

	if ((lp->cr & CR_RXON) == 0) {
		return;
	}
#if 0
	OUTL(dp, CRDA,
		((uint32_t)dp->rx_ring_dma) +
		SLOT(dp->rx_active_head, RX_RING_SIZE)
				* sizeof(struct rx_desc));
#endif
	OUTW(dp, CR, lp->cr);
#if 0
	VFE_KICK_RX(dp, lp->cr);
#endif
}

static void
E 11
E 9
vfe_stop_mauto(struct gem_dev *dp)
{
	int		i;
D 11
	int		ret;
	struct vfe_dev	*lp = (struct vfe_dev *)dp->private;
E 11
I 11
	struct vfe_dev	*lp = dp->private;
E 11

	/*
	 * Initialize MII logic
	 */
	OUTB(dp, MIICR, 0);

	/* wait for midle */
D 8
	if (IS_RHINE1_VT86C100A_E(lp->revid)) {
E 8
I 8
	if (IS_RHINE1_VT86C100A(lp->revid)) {
E 8
		/*
		 * turn off MSRCEN
		 */
D 5
		OUTB(dp, MIIADR, 1);
E 5
I 5
		OUTB(dp, MIIADR, MII_STATUS);
E 5
		drv_usecwait(1000);

		/* turn on MAUTO */
		OUTB(dp, MIICR, MIICR_MAUTO);

		for (i = 0; (INB(dp, MIIADR) & MIIADR_MDONE) == 0; i++) {
			if (i > 100000) {
				break;
			}
			drv_usecwait(10);
		}

		/*
		 * as soon as MDONE is on,
		 * this is the right time to turn off MAUTO
		 */
		OUTB(dp, MIICR, 0);
D 11
	}
	else {
E 11
I 11
	} else {
E 11
		for (i = 0; (INB(dp, MIIADR) & MIIADR_MIDLE) == 0; i++) {
			if (i > 1000) {
I 5
D 8
				cmn_err(CE_WARN, "%s: %s: timeout",
E 8
I 8
				cmn_err(CE_WARN, "!%s: %s: timeout",
E 8
D 11
					dp->name, __func__);
E 11
I 11
				    dp->name, __func__);
E 11
E 5
				break;
			}
			drv_usecwait(10);
		}
I 5
		DPRINTF(2, (CE_CONT, "%s: %s: nic became MIDLE in %duS",
D 11
					dp->name, __func__, i*10));
E 11
I 11
		    dp->name, __func__, i*10));
E 11
D 6
#if 0
		drv_usecwait(1000);

		OUTB(dp, MIIADR, 0);

		OUTB(dp, MIICR, INB(dp, MIICR) | MIICR_RCMD);

		for (i = 0; (INB(dp, MIICR) & MIICR_RCMD) != 0; i++) {
			if  (i > 100) {
				cmn_err(CE_WARN,
					"!%s: %s: timeout", dp->name, __func__);
				break;
			}
			drv_usecwait(10);
		}
#endif
E 6
E 5
	}
D 11
	DPRINTF(1, (CE_CONT, "!%s: mauto stopped in %d uS", __func__, i*10));
E 11
I 11
	DPRINTF(2, (CE_CONT, "!%s: mauto stopped in %d uS", __func__, i*10));
E 11
}

I 5
static void
vfe_start_mauto(struct gem_dev *dp)
{
	int	i;

	OUTB(dp, MIICR, 0);
	OUTB(dp, MIIADR, MII_STATUS);
	OUTB(dp, MIICR, MIICR_MAUTO);

	for (i = 0; (INB(dp, MIIADR) & MIIADR_MDONE) == 0; i++) {
		if (i > 1000) {
			cmn_err(CE_WARN, "%s: %s: timeout",
D 11
				dp->name, __func__);
E 11
I 11
			    dp->name, __func__);
E 11
			break;
		}
		drv_usecwait(10);
	}

	DPRINTF(2, (CE_CONT, "%s: %s: nic became MAUTO in %duS",
D 11
			dp->name, __func__, i*10));
E 11
I 11
	    dp->name, __func__, i*10));
E 11

	OUTB(dp, MIIADR, MIIADR_MSRCEN | MII_STATUS);
}

E 5
static int
vfe_reset_chip(struct gem_dev *dp)
{
	int		i;
	int		ret;
D 11
	struct vfe_dev	*lp = (struct vfe_dev *)dp->private;
E 11
I 11
#ifdef WA_SPURIOUS_INTR
	uint32_t	isr;
#endif
	struct vfe_dev	*lp = dp->private;
E 11

D 8
	DPRINTF(1, (CE_CONT, "!%s: vfe_reset_chip: called, time:%d, cr:%b",
		dp->name, ddi_get_lbolt(),
E 8
I 8
D 9
	DPRINTF(1, (CE_CONT, "!%s: %s: called, time:%d, cr:%b",
		dp->name, __func__, ddi_get_lbolt(),
E 9
I 9
D 10
	DPRINTF(1, (CE_CONT, "!%s: vfe_reset_chip: called, time:%d, cr:%b",
E 10
I 10
D 12
	DPRINTF(1, (CE_CONT, "!%s: vfe_reset_chip: called, time:%ld, cr:%b",
E 10
D 11
		dp->name, ddi_get_lbolt(),
E 9
E 8
		lp->cr, CR_BITS));
E 11
I 11
	    dp->name, ddi_get_lbolt(),
E 12
I 12
	DPRINTF(1, (CE_CONT, "!%s: %s: called, time:%ld, cr:%b",
	    dp->name, __func__, ddi_get_lbolt(),
E 12
	    lp->cr, CR_BITS));
E 11

	ret = GEM_SUCCESS;
D 4
#ifdef notdef /* DEBUG_LEVEL */
E 4
I 4
D 11
#ifdef NEVER /* DEBUG_LEVEL */
E 11
I 11
#if DEBUG_LEVEL > 10
E 11
E 4
	/* white a dummy mac address to ensure eeprom autoloading works */
	for (i = 0; i < ETHERADDRL; i++) {
		OUTB(dp, PAR + i, i);
	}
#endif
D 4
	/* invalidate a software cache of current mac address */
E 4
I 4
	/* invalidate a software cache for current mac address */
E 4
D 11
	bzero(lp->mac_addr, sizeof(lp->mac_addr));
E 11
I 11
	bzero(lp->mac_addr, sizeof (lp->mac_addr));
E 11

D 11
	/* clear interrupt mask */
E 11
I 11
	/* clear interrupt mask, but don't clear interrupt causes */
E 11
D 8
	RH_WRITE_IMR(dp, 0);
E 8
I 8
	VFE_WRITE_IMR(dp, 0);
I 11
#ifdef WA_SPURIOUS_INTR
	/* save interrupt status */
	VFE_READ_ISR(dp, isr);
	lp->isr_pended |= isr;
#endif
E 11
E 8

D 11
	/* Reset the chip. */
E 11
I 11
	/* reset the chip. */
E 11
	lp->cr = 0;
I 5
D 6
#if 0
E 6
E 5
	OUTB(dp, CR + 1, (CR_SRST >> 8) | INB(dp, CR + 1));
I 5
D 6
#else
	OUTB(dp, CR + 1, CR_SRST >> 8);	/* for test */
#endif
E 6
E 5
	drv_usecwait(10);

	if (IS_RHINE1(lp->revid)) {
		/* extra wait time for Rhine-I chips */
		drv_usecwait(100);
	}

D 8
	for (i = 0; (INB(dp, CR + 1) & (CR_SRST >> 8)) != 0; i++) {
		if (i > 1000) {
E 8
I 8
D 9
	i = 0;
	while (INB(dp, CR + 1) & (CR_SRST >> 8)) {
		if (i++ > 1000) {
E 9
I 9
D 11
	for (i = 0; (INB(dp, CR + 1) & (CR_SRST >> 8)) != 0; i++) {
		if (i > 1000) {
E 9
E 8
D 5
			cmn_err(CE_WARN, "!%s: vfe_reset_chip: timeout",
				dp->name);
E 5
I 5
			cmn_err(CE_WARN, "!%s: %s: timeout",
				dp->name, __func__);
E 11
I 11
	for (i = 0; INB(dp, CR + 1) & (CR_SRST >> 8); i++) {
		if (i > 2000) {
			cmn_err(CE_CONT, "!%s: %s: timeout",
			    dp->name, __func__);
E 11
E 5

			if (IS_RHINE1_VT86C100A(lp->revid)) {
				ret = GEM_FAILURE;
				break;
			}

			/* Use force_software_reset bit in MISC register */
I 5
D 6
#if 0
E 6
E 5
			OUTB(dp, MISC + 1,
D 11
				(MISC_FORSRST >> 8) | INB(dp, MISC + 1));
E 11
I 11
			    (MISC_FORSRST >> 8) | INB(dp, MISC + 1));
E 11
I 5
D 6
#else
			OUTB(dp, MISC + 1, MISC_FORSRST >> 8); /* test */
#endif
E 6
E 5
			drv_usecwait(2000);
			break;
		}
		drv_usecwait(10);
	}

D 11
	drv_usecwait(5000);
E 11
I 11
	delay(drv_usectohz(5000));
E 11

	/* clear interrupt mask again */
D 8
	RH_WRITE_IMR(dp, 0);
E 8
I 8
	VFE_WRITE_IMR(dp, 0);
E 8

I 5
	/* initialize cached value for PHY address */
	lp->last_phy_addr = INB(dp, MPHY) & PHYADR_PHYAD;
D 12
	/* XXX - write it back */
E 12
I 12

	/* setup MII polling interval and disable acceleration */
E 12
	OUTB(dp, MPHY, lp->last_phy_addr);

E 5
	vfe_stop_mauto(dp);

	return (ret);
}

D 4
static void
E 4
I 4
static int
E 4
vfe_init_chip(struct gem_dev *dp)
{
	int		i;
D 11
	u_int		val;
E 11
I 11
	uint_t		val;
E 11
I 5
	ddi_acc_handle_t	conf_handle;
E 5
D 11
	struct vfe_dev	*lp = (struct vfe_dev *)dp->private;
E 11
I 11
	struct vfe_dev	*lp = dp->private;
E 11

D 8
	DPRINTF(1, (CE_CONT, "!%s: vfe_init_chip: called at time:%d",
		dp->name, ddi_get_lbolt()));
E 8
I 8
D 10
	DPRINTF(1, (CE_CONT, "!%s: %s: called at time:%d",
E 10
I 10
	DPRINTF(1, (CE_CONT, "!%s: %s: called at time:%ld",
E 10
D 11
		dp->name, __func__, ddi_get_lbolt()));
E 11
I 11
	    dp->name, __func__, ddi_get_lbolt()));
E 11
E 8
I 5
D 6
#ifdef notdef
E 6
I 6

E 6
	if (pci_config_setup(dp->dip, &conf_handle) != DDI_SUCCESS) {
		cmn_err(CE_WARN, "!%s: ddi_regs_map_setup failed",
D 11
			dp->name);
E 11
I 11
		    dp->name);
E 11
		return (GEM_FAILURE);
	}
E 5

I 5
	/* Undocumented dances and songs for PCI config registers */
	if (IS_RHINE2_OR_LATER(lp->revid)) {
		/* PCEROPT */
		pci_config_put8(conf_handle, 0x52,
D 11
			pci_config_get8(conf_handle, 0x52) | 0x80);
E 11
I 11
		    pci_config_get8(conf_handle, 0x52) | 0x80);
E 11
		/* MII ON */
D 11
		pci_config_put8(conf_handle, 0x53, 
			pci_config_get8(conf_handle, 0x53) | 0x04);
E 11
I 11
		pci_config_put8(conf_handle, 0x53,
		    pci_config_get8(conf_handle, 0x53) | 0x04);
E 11
	}
	if (IS_RHINE1(lp->revid) || IS_RHINE3LOM(lp->revid)) {
		/* enable MODE10T */
		pci_config_put8(conf_handle, 0x52,
D 11
			pci_config_get8(conf_handle, 0x52) | 0x02);
E 11
I 11
		    pci_config_get8(conf_handle, 0x52) | 0x02);
E 11
	}
D 11
	if (IS_VT6107A1_OR_LATER(lp->revid)) {
E 11
I 11
	if (IS_VT6107A1(lp->revid)) {
E 11
		/* enable MRM */
		pci_config_put8(conf_handle, 0x52,
D 11
			pci_config_get8(conf_handle, 0x52) | 0x08);
E 11
I 11
		    pci_config_get8(conf_handle, 0x52) | 0x08);
E 11
	}
	pci_config_teardown(&conf_handle);
D 6
#endif
E 6
I 6

E 6
E 5
D 4
	/* PAR: do nothing */
E 4
I 4
	/* PAR: don't touch */
E 4

	/* RCR: disable all rx filter */
	OUTB(dp, RCR, lp->rft << RCR_RRFT_SHIFT);

I 6
	/* CFGA */
	if (IS_RHINE2_OR_LATER(lp->revid)) {
		OUTB(dp, CFGA, INB(dp, CFGA) & ~0x01);
	}

E 6
	/* TCR */
D 11
	OUTB(dp, TCR, (lp->tft << TCR_RTFT_SHIFT) | TCR_LB_NORMAL | TCR_OFSET);
E 11
I 11
	OUTB(dp, TCR,
	    (lp->tft << TCR_RTFT_SHIFT) | TCR_LB_NORMAL | TCR_OFSET);
E 11

	/* CR: don't touch  */

	/* ISR: don't touch */

	/* IMR & MIMR */
	lp->imr = 0;
D 11
	lp->imr_hw = lp->imr;
D 8
	RH_WRITE_IMR(dp, lp->imr_hw);
E 8
I 8
	VFE_WRITE_IMR(dp, lp->imr_hw);
E 11
I 11
	VFE_WRITE_IMR(dp, lp->imr);
E 11
E 8

	/* Curr Rx Desc Addr */
D 4
	/* This seems to reset rx desc pointer. */
E 4
I 4
	/* This also seems to reset Rx Desc Pointer register. */
E 4
	OUTL(dp, CRDA, (uint32_t)dp->rx_ring_dma);

	/* Curr Tx Desc Addr */
D 4
	/* This seems to reset tx desc pointer. */
E 4
I 4
	/* This also seems to reset Tx Desc Pointer register. */
E 4
	OUTL(dp, CTDA, (uint32_t)dp->tx_ring_dma);
D 6
	if (IS_RHINE3M_OR_LATER(lp->revid)) {
E 6
I 6
	if (IS_RHINE3M(lp->revid)) {
E 6
		/* It has 8 transmit queues, but we use only the first one. */
I 5
		bzero(dp->io_area, dp->gc.gc_io_area_size);
E 5
		for (i = 1; i < 8; i++) {
			OUTL(dp, CTDA + i*4, dp->io_area_dma);
		}
	}

	/* BCR */
	OUTW(dp, BCR,
D 11
		(lp->tft << BCR_CTFT_SHIFT) |
		(lp->rft << BCR_CRFT_SHIFT) |
		lp->maxdma);
E 11
I 11
D 12
	    (lp->tft << BCR_CTFT_SHIFT) |
	    (lp->rft << BCR_CRFT_SHIFT) |
E 12
I 12
	    lp->tft << BCR_CTFT_SHIFT |
	    lp->rft << BCR_CRFT_SHIFT |
E 12
	    lp->maxdma);
E 11

	/* CFGB */
	val = INB(dp, CFGB);
	if (IS_RHINE1(lp->revid)) {
		/* Disable queuing packets */
		val |= CFGB_QPKTDIS;
D 11
	}
	else {
E 11
I 11
	} else {
E 11
		/* Enable queuing packets */
		val &= ~CFGB_QPKTDIS;
		OUTB(dp, WOLCG_SET, WOLCG_SAM | WOLCG_SAB);
	}
	OUTB(dp, CFGB, val);

	/* CFGD */
	val = INB(dp, CFGD);
	val &= ~(CFGD_CRANDOM | CFGD_CAP | CFGD_MBA | CFGD_BAKOPT);
	if (IS_RHINE1(lp->revid)) {
		/* Disable MII status change interrupt as it doesn't work */
		val &= ~CFGD_GPIOEN;
	}
	OUTB(dp, CFGD, val);

	if (IS_RHINE3_OR_LATER(lp->revid)) {
		/* setup RhineIII flow control */
		OUTB(dp, FCR1,
D 11
			FCR1_TXLOWAT_24 | FCR1_TXHIWAT_48 | FCR1_XONOFF_EN);
E 11
I 11
		    FCR1_TXLOWAT_24 | FCR1_TXHIWAT_48 | FCR1_XONOFF_EN);
E 11
		OUTW(dp, PAUSE_TIMER, 0xffff);
	}

	DPRINTF(1, (CE_CONT, "!%s: txthr:%d rxthr:%d maxdma:%d",
D 11
		dp->name, lp->tft, lp->rft, lp->maxdma));
E 11
I 11
	    dp->name, lp->tft, lp->rft, lp->maxdma));
E 11
I 4

	return (GEM_SUCCESS);
E 4
}

static uint_t
vfe_mcast_hash(struct gem_dev *dp, uint8_t *addr)
{
	/* hash key is most significant 6 bits of crc in big endian manner */
	return (gem_ether_crc_be(addr, ETHERADDRL) >> (32 - 6));
}

D 4
static void
E 4
I 4
static int
E 4
D 11
vfe_set_rx_filter(struct gem_dev *dp)	
E 11
I 11
vfe_set_rx_filter(struct gem_dev *dp)
E 11
{
	uint32_t	mode;
	int		i, j;
D 11
	uint32_t	mhash[2];
E 11
I 11
	uint64_t	mhash;
E 11
	uint8_t		*mac;
I 3
D 11
	static uint8_t	invalid_mac[ETHERADDRL] = {0,0,0,0,0,0};
E 3
	struct vfe_dev	*lp = (struct vfe_dev *)dp->private;
E 11
I 11
	static uint8_t	invalid_mac[ETHERADDRL] = {0, 0, 0, 0, 0, 0};
	struct vfe_dev	*lp = dp->private;
E 11

D 8
	DPRINTF(1, (CE_CONT, "!%s: vfe_set_rx_filter: called at time:%d, "
E 8
I 8
D 10
	DPRINTF(1, (CE_CONT, "!%s: %s: called at time:%d, "
E 10
I 10
	DPRINTF(1, (CE_CONT, "!%s: %s: called at time:%ld, "
E 10
E 8
D 11
		"active:%d, rxmode:%b, cr:%b",
D 8
		dp->name, ddi_get_lbolt(),
E 8
I 8
		dp->name, __func__, ddi_get_lbolt(),
E 8
D 2
		dp->nic_active, dp->rxmode, "\020\002AllMulti\001Promisc",
E 2
I 2
D 3
		dp->mac_active, dp->rxmode, "\020\002AllMulti\001Promisc",
E 3
I 3
D 9
		dp->mac_active,
		dp->rxmode, "\020\004Enable\003MultiOvf\002AllMulti\001Promisc",
E 3
E 2
		lp->cr, CR_BITS));
E 9
I 9
		dp->mac_active, dp->rxmode, RXMODE_BITS, lp->cr, CR_BITS));
E 11
I 11
	    "active:%d, rxmode:%b, cr:%b",
	    dp->name, __func__, ddi_get_lbolt(),
	    dp->mac_active, dp->rxmode, RXMODE_BITS, lp->cr, CR_BITS));
E 11
E 9

D 3
	mode = RCR_AB;	/* broadcast */
E 3
I 3
D 9
	mode = RCR_SEP | RCR_AR | RCR_AB; /* error packets and broadcast */
E 9
I 9
	mode = RCR_SEP | RCR_AR | RCR_AB /* error packets and broadcast */
D 11
	     | RCR_AM;			/* enable multicast packet reception */
E 9
E 3
	mhash[0] = mhash[1] = 0;
E 11
I 11
	    | RCR_AM;			/* enable multicast packet reception */
	mhash = 0ULL;
E 11
D 3
	if ((dp->rxmode & RXMODE_PROMISC) != 0) {
E 3
I 3
	mac = &dp->cur_addr.ether_addr_octet[0];

	if ((dp->rxmode & RXMODE_ENABLE) == 0) {
		mode = 0;	/* disable all filters */
D 11
		mac  = invalid_mac;
	}
D 8
	else if ((dp->rxmode & RXMODE_PROMISC) != 0) {
E 8
I 8
	else if (dp->rxmode & RXMODE_PROMISC) {
E 8
E 3
D 9
		mode |=RCR_PRO	/* promiscous */
                     | RCR_AM;	/* muticast */
		mhash[0] = mhash[1] = 0xffffffff;
E 9
I 9
		mode |=RCR_PRO;	/* promiscous */
		mhash[0] = mhash[1] = 0xffffffffU;
E 9
	}
D 8
	else if ((dp->rxmode & RXMODE_ALLMULTI) != 0 ||
E 8
I 8
	else if ((dp->rxmode & RXMODE_ALLMULTI) ||
E 8
				dp->mc_count > MULTICAST_CAM_SIZE) {
D 9
		mode |= RCR_AM;	/* multicast */
		mhash[0] = mhash[1] = 0xffffffff;
E 9
I 9
		mhash[0] = mhash[1] = 0xffffffffU;
E 9
	}
D 6
	else if (IS_RHINE3M_OR_LATER(lp->revid) && dp->mc_count > 0) {
E 6
I 6
D 9
	else if (IS_RHINE3M(lp->revid) && dp->mc_count > 0) {
E 6
		/*
D 4
		 * use multicast cam. The multicast hash table should be 0.
E 4
I 4
		 * As weuse multicast cam, multicast hash table should be 0.
E 4
		 */
D 4
		mode |= RCR_AM;	/* enable multicast reception */
E 4
I 4
		mode |= RCR_AM;	/* enable multicast packet reception */
E 4
	}
	else if (dp->mc_count > 0) {
D 4
		mode |= RCR_AM;	/* enable multicast reception */
E 4
I 4
		mode |= RCR_AM;	/* enable multicast packet reception */
E 4

E 9
I 9
	else if (!IS_RHINE3M(lp->revid)) {
E 11
I 11
		mac = invalid_mac;
	} else if (dp->rxmode & RXMODE_PROMISC) {
		mode |= RCR_PRO;	/* promiscuous */
		mhash = ~0ULL;
	} else if ((dp->rxmode & RXMODE_ALLMULTI) ||
	    dp->mc_count > MULTICAST_CAM_SIZE) {
		mhash = ~0ULL;
	} else if (!IS_RHINE3M(lp->revid)) {
E 11
E 9
		/* make a hash table */
		for (i = 0; i < dp->mc_count; i++) {
D 11
			j = dp->mc_list[i].hash;
			mhash[j / 32] |= 1 << (j % 32);
E 11
I 11
			mhash |= 1ULL << dp->mc_list[i].hash;
E 11
		}
	}

D 3
	mac = &dp->cur_addr.ether_addr_octet[0];

E 3
D 8
	if (bcmp(lp->mac_addr, mac, ETHERADDRL) != 0) {
E 8
I 8
D 9
	if (bcmp(lp->mac_addr, mac, ETHERADDRL)) {
E 8
		/*
D 4
		 * XXX - as we cannot resume rx w/o resetting, don't stop rx.
E 4
I 4
		 * XXX - as we cannot re-enable rx w/o resetting, don't stop rx.
E 4
		 */
E 9
I 9
	/* update rx filter related registers */
	if (bcmp(lp->mac_addr, mac, ETHERADDRL) != 0) {
		/* update station address */
E 9
		for (i = 0; i < ETHERADDRL; i++) {
D 11
			OUTB(dp, PAR + i, lp->mac_addr[i] = mac[i]);
E 11
I 11
			OUTB(dp, PAR + i, mac[i]);
			lp->mac_addr[i] = mac[i];
E 11
		}
	}

D 6
	if (IS_RHINE3M_OR_LATER(lp->revid)) {
E 6
I 6
	if (IS_RHINE3M(lp->revid)) {
E 6
		uint32_t	cammask;
		/*
D 4
		 * VT6105M has 32 entry cams for multicast filtering
E 4
I 4
		 * VT6105M has 32 entry cams for filtering muticast packets.
E 4
		 */
		cammask = 0;

D 4
		/* enable cam port for writing multicast address*/
E 4
I 4
		/* enable cam port for writing multicast address */
E 4
		OUTB(dp, CAMCTRL, CAMCTRL_EN);

		if (dp->mc_count <= MULTICAST_CAM_SIZE) {
			for (i = 0; i < dp->mc_count; i++) {
				/* write cam index */
				OUTB(dp, CAMADDR, i);

D 9
				/* write a multicast address into cam */
E 9
I 9
				/* write the multicast address into cam */
E 9
				mac = dp->mc_list[i].addr.ether_addr_octet;
				for (j = 0; j < ETHERADDRL; j++) {
					OUTB(dp, MAR + j, mac[j]);
				}
				drv_usecwait(10);

				/* issue a cam write command */
				OUTB(dp, CAMCTRL, CAMCTRL_EN | CAMCTRL_WR);
				drv_usecwait(10);

				cammask |= 1 << i;
			}
		}

		/* setup multicast cam mask */
		OUTL(dp, CAMMASK, cammask);
		OUTB(dp, CAMCTRL, 0);

D 9
		/* initialize VLAN cam mask */
E 9
I 9
		/* we don't use VLAN cam */
E 9
		OUTB(dp, CAMCTRL, CAMCTRL_EN | CAMCTRL_VLAN);
		OUTL(dp, CAMMASK, 0);
		OUTB(dp, CAMCTRL, 0);
	}

D 8
	if ((mode & RCR_AM) != 0) {
E 8
I 8
	if (mode & RCR_AM) {
E 8
D 9
		/* need to set multicast hash table */
E 9
I 9
		/* update multicast hash table */
E 9
		for (i = 0; i < 2; i++) {
D 11
			OUTL(dp, MAR + i*4, mhash[i]);
E 11
I 11
			OUTL(dp, MAR + i*4, (uint32_t)mhash);
			mhash >>= 32;
E 11
		}
	}

D 4
	/* update new rx filter mode */
E 4
I 4
	/* update rx filter mode */
E 4
D 3
	OUTB(dp, RCR, (lp->rft << RCR_RRFT_SHIFT) | mode | RCR_SEP | RCR_AR);
E 3
I 3
	OUTB(dp, RCR, (lp->rft << RCR_RRFT_SHIFT) | mode);
I 4

	return (GEM_SUCCESS);
E 4
E 3
}

D 4
static void
E 4
I 4
static int
E 4
vfe_set_media(struct gem_dev *dp)
{
D 11
	u_int		val;
	struct vfe_dev	*lp = (struct vfe_dev *)dp->private;
E 11
I 11
	uint_t		val;
	struct vfe_dev	*lp = dp->private;
E 11

D 8
	DPRINTF(1, (CE_CONT, "!%s: vfe_set_media: called at time:%d, "
E 8
I 8
D 10
	DPRINTF(1, (CE_CONT, "!%s: %s: called at time:%d, "
E 10
I 10
	DPRINTF(1, (CE_CONT, "!%s: %s: called at time:%ld, "
E 10
E 8
D 11
		"active:%d, cr:%b, misc:%04x",
D 8
		dp->name, ddi_get_lbolt(),
E 8
I 8
		dp->name, __func__, ddi_get_lbolt(),
E 8
D 2
		dp->nic_active, lp->cr, CR_BITS, INW(dp, MISC)));
E 2
I 2
		dp->mac_active, lp->cr, CR_BITS, INW(dp, MISC)));
E 11
I 11
	    "active:%d, cr:%b, misc:%04x",
	    dp->name, __func__, ddi_get_lbolt(),
	    dp->mac_active, lp->cr, CR_BITS, INW(dp, MISC)));
E 11
E 2

	/*
	 * Notify current duplex mode to mac
	 */
D 5
	/* XXX - don't stop the nic, it isn't recoverble. */
E 5
I 5
	/* XXX - don't stop the nic, it isn't recoverable. */
E 5
	if (dp->full_duplex) {
		lp->cr |= CR_FDX;
D 11
	}
	else {
E 11
I 11
	} else {
E 11
		lp->cr &= ~CR_FDX;
	}
	OUTB(dp, CR+1, lp->cr >> 8);

	/* Set up flow control register */
	if (IS_RHINE2(lp->revid)) {
		/* VT6102 has partial flow control */
		val = INW(dp, MISC) &
D 11
				~(MISC_FDXTFEN | MISC_FDXRFEN | MISC_HDXFEN);
E 11
I 11
		    ~(MISC_FDXTFEN | MISC_FDXRFEN | MISC_HDXFEN);
E 11
		switch (dp->flow_control) {
		case FLOW_CONTROL_SYMMETRIC:
		case FLOW_CONTROL_RX_PAUSE:
			val |= MISC_FDXRFEN;
			break;
D 11
#ifdef NEVER
		case FLOW_CONTROL_NONE:
			if (!dp->full_duplex) {
				/* XXX - don't use half duplex flow control */
				val |= MISC_HDXFEN;
			}
			break;
#endif
E 11
		}
		OUTW(dp, MISC, val);
D 11
	}	
	else if (IS_RHINE3_OR_LATER(lp->revid)) {
E 11
I 11
	} else if (IS_RHINE3_OR_LATER(lp->revid)) {
E 11
		val = INB(dp, FCR1) &
D 11
			~(FCR1_FDFCTX_EN | FCR1_FDFCRX_EN | FCR1_HDFC_EN);
E 11
I 11
		    ~(FCR1_FDFCTX_EN | FCR1_FDFCRX_EN | FCR1_HDFC_EN);
E 11

		switch (dp->flow_control) {
		case FLOW_CONTROL_RX_PAUSE:
			val |= FCR1_FDFCRX_EN;
			break;

		case FLOW_CONTROL_TX_PAUSE:
			val |= FCR1_FDFCTX_EN;
			break;

		case FLOW_CONTROL_SYMMETRIC:
			val |= FCR1_FDFCTX_EN | FCR1_FDFCRX_EN;
			break;
D 11
#ifdef NEVER
		case FLOW_CONTROL_NONE:
			if (!dp->full_duplex) {
				/* XXX - don't use half duplex flow control */
				val |=  FCR1_HDFC_EN;
			}
			break;
#endif
E 11
		}
		OUTB(dp, FCR1, val);
	}
I 4

	return (GEM_SUCCESS);
E 4
}

D 4
static void
E 4
I 4
static int
E 4
vfe_start_chip(struct gem_dev *dp)
{
D 11
	struct vfe_dev	*lp = (struct vfe_dev *)dp->private;
E 11
I 11
	struct vfe_dev	*lp = dp->private;
E 11

D 8
	DPRINTF(1, (CE_CONT, "!%s: vfe_start_chip: called at time:%d",
		dp->name, ddi_get_lbolt()));
E 8
I 8
D 10
	DPRINTF(1, (CE_CONT, "!%s: %s: called at time:%d",
E 10
I 10
	DPRINTF(1, (CE_CONT, "!%s: %s: called at time:%ld",
E 10
D 11
		dp->name, __func__, ddi_get_lbolt()));
E 11
I 11
	    dp->name, __func__, ddi_get_lbolt()));
E 11
E 8

	/* enable interrupt */
D 11
	lp->imr =
#ifdef OPT_TX_INTR
		  IS_RHINE1(lp->revid) ? (OUR_INTR_BITS & ~ISR_PTX) :
#endif
		  OUR_INTR_BITS;
E 11
I 11
	lp->imr = OUR_INTR_BITS;
E 11
D 5
	if (lp->revid > 0x40 && lp->revid < 0x90) {
E 5
I 5
#ifdef CONFIG_MAUTO
	if (IS_RHINE2_OR_LATER(lp->revid)) {
		lp->imr |= ISR_SRCI;
	}
#endif
	if (IS_RHINE2(lp->revid) || IS_RHINE3(lp->revid)) {
E 5
		lp->imr |= MISR_TDWBI << 16;
	}

D 11
	lp->imr_hw = lp->imr;
E 11
	if ((dp->misc_flag & GEM_NOINTR) == 0) {
D 8
		RH_WRITE_IMR(dp, lp->imr_hw);
E 8
I 8
D 11
		VFE_WRITE_IMR(dp, lp->imr_hw);
E 11
I 11
		VFE_WRITE_IMR(dp, lp->imr);
E 11
E 8
	}

	/* Kick TX and RX */
D 5
#if 0
	if (IS_RHINE3_OR_LATER(lp->revid)) {
		OUTB(dp, FCR0, RX_BUF_SIZE);
	}
#endif
E 5
	lp->cr |= CR_TXON | CR_RXON | CR_DPOLL | CR_STRT;
	OUTW(dp, CR, lp->cr);
I 4

I 5
#ifdef CONFIG_MAUTO
	if (IS_RHINE2_OR_LATER(lp->revid)) {
		vfe_start_mauto(dp);
	}
#endif
E 5
	return (GEM_SUCCESS);
E 4
}

static int
vfe_stop_chip(struct gem_dev *dp)
{
D 11
	struct vfe_dev	*lp = (struct vfe_dev *)dp->private;
E 11
I 11
	struct vfe_dev	*lp = dp->private;
E 11

D 8
	DPRINTF(1, (CE_CONT, "!%s: vfe_stop_chip: called at time:%d",
		dp->name, ddi_get_lbolt()));
E 8
I 8
D 10
	DPRINTF(1, (CE_CONT, "!%s: %s: called at time:%d",
E 10
I 10
	DPRINTF(1, (CE_CONT, "!%s: %s: called at time:%ld",
E 10
D 11
		dp->name, __func__, ddi_get_lbolt()));
E 11
I 11
	    dp->name, __func__, ddi_get_lbolt()));
E 11
E 8

I 5
#ifdef CONFIG_MAUTO
	if (IS_RHINE2_OR_LATER(lp->revid)) {
		vfe_stop_mauto(dp);
	}
#endif
E 5
	/* Disable interrupts by clearing the interrupt mask */
D 11
	lp->imr = 0;
	lp->imr_hw = lp->imr;
E 11
	if ((dp->misc_flag & GEM_NOINTR) == 0) {
D 8
		RH_WRITE_IMR(dp, lp->imr_hw);
E 8
I 8
D 11
		VFE_WRITE_IMR(dp, lp->imr_hw);
E 11
I 11
D 12
		/* XXX - don't clear imr to avoid bogus interrupts */
		VFE_WRITE_IMR(dp, lp->imr);
E 12
I 12
		/* XXX - don't clear lp->imr to avoid bogus interrupts */
		VFE_WRITE_IMR(dp, 0);
E 12
E 11
E 8
	}

	/* Stop Tx and Rx processes in the chip. */
	lp->cr &= ~(CR_TXON | CR_RXON | CR_DPOLL | CR_STRT);
	OUTW(dp, CR, lp->cr | CR_STOP);

D 4
	/* Note: No need to call vfe_reset_chip() to reset Tx/Rx desc pointers */
E 4
I 4
	/*
D 11
	 * XXX - No need to call vfe_reset_chip() to reset
	 * Tx/Rx desc pointers.
E 11
I 11
D 12
	 * XXX -  sometimes rx doesn't restart after stop.
E 12
I 12
	 * XXX - sometimes rx doesn't restart after stop.
E 12
E 11
	 */
I 11
	(void) vfe_reset_chip(dp);
E 11
E 4

	return (GEM_SUCCESS);
}

#ifdef DEBUG_LEVEL
static uint16_t
vfe_read_eeprom(struct gem_dev *dp, uint_t offset)
{
	int		i;
	uint16_t	ret;
	uint8_t		chip_select;
	uint8_t		di;
	uint8_t		cfga_saved;

D 8
#define	RH_EEPROM_DELAY(dp)	{INB(dp, EECSR); INB(dp, EECSR);}
E 8
I 8
D 11
#define	VFE_EEPROM_DELAY(dp)	{INB(dp, EECSR); INB(dp, EECSR);}
E 11
I 11
#define	VFE_EEPROM_DELAY(dp)	{INB(dp, EECSR); INB(dp, EECSR); }
E 11
E 8
#define	EE93C46_READ	6

D 11
	/* enable eeprom direct programing */
E 11
I 11
	/* enable eeprom direct programming */
E 11
	cfga_saved = INB(dp, CFGA);
	OUTB(dp, CFGA, cfga_saved | CFGA_EELOAD);
D 8
	RH_EEPROM_DELAY(dp);
E 8
I 8
	VFE_EEPROM_DELAY(dp);
E 8

	/* ensure de-assert chip select */
	chip_select = EECSR_DPM;
	OUTB(dp, EECSR, chip_select);
D 8
	RH_EEPROM_DELAY(dp);
E 8
I 8
	VFE_EEPROM_DELAY(dp);
E 8

	/* assert chip select */
	chip_select |= EECSR_ECS;
	OUTB(dp, EECSR, chip_select);
D 8
	RH_EEPROM_DELAY(dp);
E 8
I 8
	VFE_EEPROM_DELAY(dp);
E 8

	/* make a read command for eeprom */
	offset = (offset & 0x3f) | (EE93C46_READ << 6);

	for (i = 10; i >= 0; i--) {
		/* send 1 bit */
		di = ((offset >> i) & 1) << EECSR_EDI_SHIFT;

		OUTB(dp, EECSR, chip_select | di);
D 8
		RH_EEPROM_DELAY(dp);
E 8
I 8
		VFE_EEPROM_DELAY(dp);
E 8

		OUTB(dp, EECSR, chip_select | di | EECSR_ECK);
D 8
		RH_EEPROM_DELAY(dp);
E 8
I 8
		VFE_EEPROM_DELAY(dp);
E 8
	}

	OUTB(dp, EECSR, chip_select);
D 8
	RH_EEPROM_DELAY(dp);
E 8
I 8
	VFE_EEPROM_DELAY(dp);
E 8

	/* get the reply and construct a 16bit value */
	ret = 0;
	for (i = 0; i < 16; i++) {
		/* Get 1 bit */
		OUTB(dp, EECSR, chip_select | EECSR_ECK);
D 8
		RH_EEPROM_DELAY(dp);
E 8
I 8
		VFE_EEPROM_DELAY(dp);
E 8

		ret = (ret << 1)
		    | ((INB(dp, EECSR) >> EECSR_EDO_SHIFT) & 1);

		OUTB(dp, EECSR, chip_select);
D 8
		RH_EEPROM_DELAY(dp);
E 8
I 8
		VFE_EEPROM_DELAY(dp);
E 8
	}

	/* negate chip_select */
	OUTB(dp, EECSR, EECSR_DPM);
D 8
	RH_EEPROM_DELAY(dp);
E 8
I 8
	VFE_EEPROM_DELAY(dp);
E 8

	OUTB(dp, EECSR, 0);
D 8
	RH_EEPROM_DELAY(dp);
E 8
I 8
	VFE_EEPROM_DELAY(dp);
E 8

	/* disable eeprom direct programming */
	OUTB(dp, CFGA, cfga_saved);
D 8
	RH_EEPROM_DELAY(dp);
E 8
I 8
	VFE_EEPROM_DELAY(dp);
E 8

	return (ret);
}

static void
vfe_eeprom_dump(struct gem_dev *dp)
{
	int		i;
	uint16_t	prom[0x10];

	for (i = 0; i < 0x10; i++) {
		prom[i] = vfe_read_eeprom(dp, i);
	}

	cmn_err(CE_CONT, "!%s: eeprom dump:", dp->name);
	for (i = 0; i < 0x10; i += 4) {
D 11
		cmn_err(CE_CONT, "!0x%02x: 0x%04x 0x%04x 0x%04x 0x%04x", 
			i, prom[i], prom[i + 1], prom[i + 2], prom[i + 3]);
E 11
I 11
		cmn_err(CE_CONT, "!0x%02x: 0x%04x 0x%04x 0x%04x 0x%04x",
		    i, prom[i], prom[i + 1], prom[i + 2], prom[i + 3]);
E 11
	}
}
#endif /* DEBUG_LEVEL */

static int
vfe_attach_chip(struct gem_dev *dp)
{
	int		i;
D 11
	uint_t		val;
E 11
	uint8_t		*mac;
D 11
	struct vfe_dev	*lp = (struct vfe_dev *)dp->private;
E 11
I 11
	struct vfe_dev	*lp = dp->private;
E 11

D 8
	DPRINTF(1, (CE_CONT, "!%s: vfe_attach_chip: called at time:%d",
		dp->name, ddi_get_lbolt()));
E 8
I 8
D 10
	DPRINTF(1, (CE_CONT, "!%s: %s: called at time:%d",
E 10
I 10
	DPRINTF(1, (CE_CONT, "!%s: %s: called at time:%ld",
E 10
D 11
		dp->name, __func__, ddi_get_lbolt()));
E 11
I 11
	    dp->name, __func__, ddi_get_lbolt()));
E 11
E 8

	mac = dp->dev_addr.ether_addr_octet;

I 4
	/*
	 * XXX - Don't read a mac address from eeprom, it doesn't
	 * work for built-in rhine II core in VT8235 south bridge.
D 12
	 * We can read a factory mac address from PAR register,
	 *  only after the eeprom contents have been auto-loaded.
E 12
I 12
	 * We can read a factory mac address from PAR register
	 * just after the eeprom contents have been auto-loaded.
E 12
	 */
	for (i = 0; i < ETHERADDRL; i++) {
		mac[i] = INB(dp, PAR + i);
	}

E 4
	if (gem_get_mac_addr_conf(dp)) {
D 4
		/* the mac address has been specified by vfe.conf */
E 4
I 4
		/* Use a mac address specified in vfe.conf. */
E 4
		for (i = 0; i < ETHERADDRL; i++) {
			OUTB(dp, PAR + i, mac[i]);
		}
	}
D 4
	else {
		/*
		 * XXX - Don't read a mac address from eeprom, it doesn't
		 * work for built-in rhine II core in VT8235 south bridge.
		 * We can read a factory mac address from PAR reg after
		 * the eeprom contents are auto-loaded.
		 */
E 4
I 4

D 8
	if ((mac[0] & 1) != 0) {
E 8
I 8
	if (mac[0] & 1) {
E 8
		/* it seems the mac address is corrupted, generate new one. */
		cmn_err(CE_NOTE,
D 8
		"%s: mac address %x:%x:%x:%x:%x:%x is corrupted.",
E 8
I 8
D 11
		"!%s: mac address %x:%x:%x:%x:%x:%x is corrupted.",
E 8
			dp->name,
			mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
		
E 11
I 11
		    "!%s: mac address %x:%x:%x:%x:%x:%x is corrupted.",
		    dp->name,
		    mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
#ifdef OS_PUTBACK
		return (GEM_FAILURE);
#else
E 11
		gem_generate_macaddr(dp, mac);

E 4
		for (i = 0; i < ETHERADDRL; i++) {
D 4
			mac[i]= INB(dp, PAR + i);
E 4
I 4
			OUTB(dp, PAR + i, mac[i]);
E 4
		}
I 11
#endif
E 11
	}

D 12
	/* initialize soft copy of mac address registers */
E 12
I 12
	/* save a soft copy of the factory mac address */
E 12
	bcopy(mac, lp->mac_addr, ETHERADDRL);

D 5
#ifdef DEBUG_LEVEL
E 5
I 5
#if DEBUG_LEVEL > 4
E 5
	vfe_eeprom_dump(dp);
#endif /* DEBUG_LEVEL */

	/* read default address of PHY in eeprom */
	dp->mii_phy_addr = INB(dp, MPHY) & PHYADR_PHYAD;

	if (dp->rxthr <= 32) {
		lp->rft = RRFT_32;
	} else if (dp->rxthr <= 64) {
		lp->rft = RRFT_64;
	} else if (dp->rxthr <= 128) {
		lp->rft = RRFT_128;
	} else if (dp->rxthr <= 256) {
		lp->rft = RRFT_256;
	} else if (dp->rxthr <= 512) {
		lp->rft = RRFT_512;
	} else if (dp->rxthr <= 768) {
		lp->rft = RRFT_768;
	} else if (dp->rxthr <= 1024) {
		lp->rft = RRFT_1024;
	} else {
		lp->rft = RRFT_SF;
	}

	/* setup initial tft */
I 11
#ifdef notdef
	/* XXX - not required, now txthr is ETHERMAX */
E 11
	/* XXX - smaller tx threshold will cause performance issue. */
	if (IS_RHINE1(lp->revid)) {
		dp->txthr = max(dp->txthr, ETHERMAX); /* vfe-1.0.0 default */
D 11
	}
	else if (IS_RHINE2(lp->revid)) {
E 11
I 11
	} else if (IS_RHINE2(lp->revid)) {
E 11
		dp->txthr = max(dp->txthr, 512);
	}
D 11

E 11
I 11
#endif
E 11
	if (dp->txthr <= 128) {
		lp->tft = RTFT_128;
	} else if (dp->txthr <= 256) {
		lp->tft = RTFT_256;
	} else if (dp->txthr <= 512) {
		lp->tft = RTFT_512;
	} else if (dp->txthr <= 1024) {
		lp->tft = RTFT_1024;
	} else {
		lp->tft = RTFT_SF;
	}

	/* XXX - smaller txmaxdma will cause performance issue. */
D 11
	dp->txmaxdma = max(128, dp->txmaxdma);
E 11
I 11
	dp->txmaxdma = dp->mtu;
E 11

	if (dp->txmaxdma < 32) {
		lp->maxdma = BCR_DMA_32;
	} else if (dp->txmaxdma < 64) {
		lp->maxdma = BCR_DMA_64;
	} else if (dp->txmaxdma < 128) {
		lp->maxdma = BCR_DMA_128;
	} else if (dp->txmaxdma < 256) {
		lp->maxdma = BCR_DMA_256;
	} else if (dp->txmaxdma < 512) {
		lp->maxdma = BCR_DMA_512;
	} else if (dp->txmaxdma < 1024) {
		lp->maxdma = BCR_DMA_1024;
	} else {
		lp->maxdma = BCR_DMA_NOLIMIT;
	}
I 6
D 11
#ifdef GEM_CONFIG_VLAN
E 11
I 11
#ifdef GEM_CONFIG_GLDv3
E 11
	dp->misc_flag |= GEM_VLAN_SOFT;
#endif
E 6

D 11
#if 0
E 11
I 11
#if DEBUG_LEVEL > 10
E 11
	/* test for timer function */
{
	clock_t		tim;
	int		i;

#define	TEST_COUNT	300
	tim = ddi_get_lbolt();

	/* OUTB(dp, GMCR, INB(dp, GMCR) | GMCR_TMR1US); */

	OUTW(dp, SOFT_TMR0, TEST_COUNT);
	/* OUTB(dp, MIMR, INB(dp, MIMR) | MIMR_TIM0IM); */
	OUTW(dp, MISC, INW(dp, MISC) | MISC_Tm0EN);
	for (i = 100000; (INB(dp, MISR) & MISR_TIM0I) == 0; i--) {
		if (i == 0) {
			cmn_err(CE_CONT, "!%s: soft_timer0 timeout", dp->name);
		}
		drv_usecwait(100);
	}
D 11
	tim = (ddi_get_lbolt() - tim);
E 11
I 11
	tim = ddi_get_lbolt() - tim;
E 11

	if (i > 0) {
		cmn_err(CE_CONT, "!%s: soft_timer0 resolution in 10mS: %d",
D 4
			dp->name, tim > 0 ? TEST_COUNT/tim: 9999999);
E 4
I 4
D 11
			dp->name, tim > 0 ? TEST_COUNT/tim : 9999999);
E 11
I 11
		    dp->name, tim > 0 ? TEST_COUNT/tim : 9999999);
E 11
E 4
	}
	/* OUTL(dp, CR_CLR, CR_TM0EN); */
D 11
	
E 11
I 11

E 11
}
#endif
	return (GEM_SUCCESS);
}

D 4
static void
E 4
I 4
static int
E 4
vfe_get_stats(struct gem_dev *dp)
{
	volatile int	x;
D 11
	struct vfe_dev	*lp = (struct vfe_dev *)dp->private;
E 11
I 11
	struct vfe_dev	*lp = dp->private;
E 11

	if (IS_RHINE2_OR_LATER(lp->revid)) {
		dp->stats.missed += INW(dp, MPAC);
D 11
	}
	else {
E 11
I 11
	} else {
E 11
D 4
		/* they are unreliable on rhine I */
E 4
I 4
		/* MPAC is unreliable on rhine I */
E 4
		x = INW(dp, MPAC);
	}
	x = INW(dp, CRCC);
	OUTW(dp, MPAC, 0);
I 4
D 11

E 11
I 11
#ifdef lint
	x = x;
#endif
E 11
	return (GEM_SUCCESS);
E 4
}

/*
D 11
 * tx/rx discriptor manupirations
E 11
I 11
 * tx/rx descriptor manipurations
E 11
 */
#ifdef DEBUG_LEVEL
static int vfe_tx_frags[MAXTXFRAGS];
#endif
static int
vfe_tx_desc_write(struct gem_dev *dp, int slot,
D 6
		ddi_dma_cookie_t *dmacookie, int frags, uint32_t flags)
E 6
I 6
		ddi_dma_cookie_t *dmacookie, int frags, uint64_t flags)
E 6
{
	int			i;
	struct tx_desc		*tdp;
	ddi_dma_cookie_t	*dcp;
	uint32_t		mark;
D 11
	struct vfe_dev		*lp = (struct vfe_dev *)dp->private;
E 11
I 11
	uint32_t		tmp;
#ifdef GEM_CONFIG_TX_DIRECT
	uint_t			tx_ring_size = dp->gc.gc_tx_ring_size;
#endif
	struct vfe_dev		*lp = dp->private;
E 11

I 11
#ifdef lint
	i = 0;
	i = i;
#endif
E 11
#if DEBUG_LEVEL > 2
	cmn_err(CE_CONT,
D 5
	"!%s: vfe_tx_desc_write time: %d, seqnum: %d, slot %d, frags: %d flags: %d",
		dp->name, ddi_get_lbolt(), dp->tx_desc_tail, slot, frags, flags);
E 5
I 5
D 6
		"!%s: %s time: %d, seqnum: %d, slot %d, frags: %d flags: %d",
E 6
I 6
D 8
		"!%s: %s time: %d, seqnum: %d, slot %d, frags: %d flags: %lld",
E 8
I 8
D 11
		"!%s: %s time: %d, seqnum: %d, slot %d, frags: %d flags: %llx",
E 8
E 6
		dp->name, __func__, ddi_get_lbolt(),
		dp->tx_desc_tail, slot, frags, flags);
E 11
I 11
	    "!%s: %s time: %d, seqnum: %d, slot %d, frags: %d flags: %llx",
	    dp->name, __func__, ddi_get_lbolt(),
	    dp->tx_desc_tail, slot, frags, flags);
E 11
E 5
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
D 8
	if ((flags & GEM_TXFLAG_INTR) != 0) {
E 8
I 8
	if (flags & GEM_TXFLAG_INTR) {
E 8
D 11
		cmn_err(CE_CONT,
D 6
		"!%s: %s time: %d, seqnum: %d, slot %d, frags: %d flags: %d",
E 6
I 6
D 8
		"!%s: %s time: %d, seqnum: %d, slot %d, frags: %d flags: %lld",
E 8
I 8
		"!%s: %s time: %d, seqnum: %d, slot %d, frags: %d flags: %llx",
E 8
E 6
		dp->name, __func__, ddi_get_lbolt(),
		dp->tx_desc_tail, slot, frags, flags);
E 11
I 11
		cmn_err(CE_CONT, "!%s: %s time: %d,"
		    " seqnum: %d, slot %d, frags: %d flags: %llx",
		    dp->name, __func__, ddi_get_lbolt(),
		    dp->tx_desc_tail, slot, frags, flags);
E 11
	}
#endif
#if DEBUG_LEVEL > 3
	flags |= GEM_TXFLAG_INTR;
#endif
#ifdef DEBUG_LEVEL
	vfe_tx_frags[min(frags, MAXTXFRAGS) - 1]++;
#endif
	/*
D 4
	 * To avoid condition race, enabme PTx interrupt before making
E 4
I 4
D 11
	 * To avoid condition race, enable PTx interrupt before making
E 4
	 * descriptor(s) for the packet
	 */
#ifdef OPT_TX_INTR
	if ((dp->misc_flag & GEM_NOINTR) == 0 && IS_RHINE1(lp->revid) &&
D 8
	    (flags & GEM_TXFLAG_INTR) != 0 && (lp->imr & ISR_PTX) == 0) {
E 8
I 8
	    (flags & GEM_TXFLAG_INTR) && (lp->imr & ISR_PTX) == 0) {
E 8
		/*
		 * enable PTX interrupt for the time being
		 */
		lp->imr |= ISR_PTX;
D 5
#if 0
		if (mutex_tryenter(&dp->intrlock)) {
			if (lp->imr_hw != 0) {
				lp->imr_hw = lp->imr;
				RH_WRITE_IMR(dp, lp->imr_hw);
				mutex_exit(&dp->intrlock);
			}
		} else
#endif
		{
			lp->imr_change_req = B_TRUE;
			ddi_trigger_softintr(lp->soft_id);
		}
E 5
I 5
		lp->imr_change_req = B_TRUE;
		ddi_trigger_softintr(lp->soft_id);
E 5
	}
#endif /* OPT_TX_INTR */
	/*
E 11
	 * write tx descriptor(s) in reversed order
	 */
D 4
	mark = TDES1_EDP | TDES1_C/*| ((flags & GEM_TXFLAG_INTR) ? TDES1_IC : 0)*/;
E 4
I 4
	mark = TDES1_EDP | TDES1_C;
E 4
D 11
	for (i = frags - 1, dcp = &dmacookie[frags - 1]; i > 0; i--, dcp--) {
E 11
I 11
	dcp = &dmacookie[frags - 1];
#ifdef GEM_CONFIG_TX_DIRECT
	for (i = frags - 1; i > 0; i--, dcp--) {
E 11

D 11
		tdp = &((struct tx_desc *)dp->tx_ring)[
				SLOT(slot + i, TX_RING_SIZE)];
D 9
		tdp->td_length = LE32(dcp->dmac_size | mark);
		tdp->td_addr   = LE32(dcp->dmac_address);
E 9
I 9
		tdp->td_length = LE_32(dcp->dmac_size | mark);
		tdp->td_addr   = LE_32(dcp->dmac_address);
E 9
		tdp->td_csr    = 0;
E 11
I 11
		tdp = &VFE_TXDESC(dp->tx_ring)[SLOT(slot + i, tx_ring_size)];
		mark |= dcp->dmac_size;
		tdp->td_length = LE_32(mark);
		tmp = dcp->dmac_address;
		tdp->td_addr = LE_32(tmp);
		tdp->td_csr = 0;
E 11
I 10

		/*
		 * XXX - The datasheets says that the flags for intermediate
		 * fragments are STP=1 and EDP=0, but it didn't work.
D 12
		 * The right flags are STP=0 and EDP=0 in my experience.
E 12
I 12
		 * The correct flags are STP=0 and EDP=0 in my experience.
E 12
		 */
E 10
		mark = TDES1_C;
	}
I 11
#else
	ASSERT(frags == 1);
#endif
E 11

	/* for the first fragment */
D 11
	tdp = &((struct tx_desc *)dp->tx_ring)[slot];
D 9
	tdp->td_length = LE32(dcp->dmac_size | mark | TDES1_STP);
	tdp->td_addr   = LE32(dcp->dmac_address);
E 9
I 9
	tdp->td_length = LE_32(dcp->dmac_size | mark | TDES1_STP);
	tdp->td_addr   = LE_32(dcp->dmac_address);
E 11
I 11
	tdp = &VFE_TXDESC(dp->tx_ring)[slot];
	mark |= dcp->dmac_size | TDES1_STP;
	tdp->td_length = LE_32(mark);
	tmp = dcp->dmac_address;
	tdp->td_addr = LE_32(tmp);
E 11
E 9

D 12
	if ((flags & GEM_TXFLAG_INTR) == 0 && IS_RHINE2_OR_LATER(lp->revid)) {
E 12
I 12
	if (IS_RHINE2_OR_LATER(lp->revid) &&
	    (flags & GEM_TXFLAG_INTR) == 0) {
E 12
		/* set suppress-interrupt request for the packet */
D 9
		tdp->td_next |= LE32(TDES3_TDCTL);
E 9
I 9
		tdp->td_next |= LE_32(TDES3_TDCTL);
E 9
	}
I 11

E 11
D 8
	tdp->td_csr = LE32(TDES0_OWN);
E 8
I 8
	if ((flags & GEM_TXFLAG_HEAD) == 0) {
D 9
		tdp->td_csr = LE32(TDES0_OWN);
E 9
I 9
		tdp->td_csr = LE_32(TDES0_OWN);
E 9
	}
E 8

	return (frags);
}

static void
vfe_tx_start(struct gem_dev *dp, int start_slot, int nslot)
{
I 8
D 11
	struct tx_desc	*tdp;
E 8
D 4
	struct vfe_dev		*lp = (struct vfe_dev *)dp->private;
E 4
I 4
	struct vfe_dev	*lp = (struct vfe_dev *)dp->private;
E 11
I 11
	struct vfe_dev	*lp = dp->private;
E 11
E 4

I 11
	DPRINTF(2, (CE_CONT, "!%s: %s: called at time:%ld",
	    dp->name, __func__, ddi_get_lbolt()));

E 11
D 8
	gem_tx_desc_dma_sync(dp, start_slot, nslot, DDI_DMA_SYNC_FORDEV);
E 8
I 8
	if (nslot > 1) {
		gem_tx_desc_dma_sync(dp,
D 11
				SLOT(start_slot + 1, TX_RING_SIZE),
				nslot - 1, DDI_DMA_SYNC_FORDEV);
E 11
I 11
		    SLOT(start_slot + 1, dp->gc.gc_tx_ring_size),
		    nslot - 1, DDI_DMA_SYNC_FORDEV);
E 11
	}
E 8

I 12
	/*
	 * link the new buffers to the tail of the current tx list
	 */
E 12
I 8
D 9
	((struct tx_desc *) dp->tx_ring)[start_slot].td_csr = LE32(TDES0_OWN);
E 9
I 9
D 11
	((struct tx_desc *) dp->tx_ring)[start_slot].td_csr = LE_32(TDES0_OWN);
E 11
I 11
	VFE_TXDESC(dp->tx_ring)[start_slot].td_csr = LE_32(TDES0_OWN);
E 11
E 9
	gem_tx_desc_dma_sync(dp, start_slot, 1, DDI_DMA_SYNC_FORDEV);

E 8
	/* kick Tx engine */
D 4
#ifdef TXTIMEOUT_TEST
E 4
I 4
#ifdef TEST_TXTIMEOUT
E 4
	if ((vfe_send_cnt++ % 100) == 99) {
		lp->cr &= ~CR_TXON;
		OUTW(dp, CR, lp->cr);
	}
#endif
D 8
	RH_KICK_TX(dp, lp->cr);
E 8
I 8
	VFE_KICK_TX(dp, lp->cr);
E 8
}

static void
vfe_rx_desc_write(struct gem_dev *dp, int slot,
	    ddi_dma_cookie_t *dmacookie, int frags)
{
D 11
	struct rx_desc		*rdp;
	int			i;
	struct vfe_dev		*lp = (struct vfe_dev *)dp->private;
E 11
I 11
	uint32_t	tmp0;
	uint32_t	tmp1;
	struct rx_desc	*rdp;
E 11

#if DEBUG_LEVEL > 2
I 11
{
	int	i;

E 11
	cmn_err(CE_CONT,
D 11
		"!%s: vfe_rx_desc_write seqnum: %d, slot %d, frags: %d",
		dp->name, dp->rx_active_tail, slot, frags);
E 11
I 11
	    "!%s: vfe_rx_desc_write seqnum: %d, slot %d, frags: %d",
	    dp->name, dp->rx_active_tail, slot, frags);
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
I 11
}
E 11
#endif
	/*
	 * write a RX descriptor
	 */
D 4
	rdp = &((struct rx_desc *)dp->rx_ring)[slot];
E 4
I 4
D 11
	rdp = &((struct rx_desc *) dp->rx_ring)[slot];
E 11
I 11
	rdp = &VFE_RXDESC(dp->rx_ring)[slot];
E 11
E 4

D 9
	rdp->rd_addr   = LE32(dmacookie->dmac_address);
	rdp->rd_length = LE32(dmacookie->dmac_size);
	rdp->rd_status = LE32(RDES0_OWN);
E 9
I 9
D 11
	rdp->rd_addr   = LE_32(dmacookie->dmac_address);
	rdp->rd_length = LE_32(dmacookie->dmac_size);
E 11
I 11
	tmp0 = dmacookie->dmac_address;
	rdp->rd_addr = LE_32(tmp0);
	tmp1 = dmacookie->dmac_size;
	rdp->rd_length = LE_32(tmp1);
E 11
	rdp->rd_status = LE_32(RDES0_OWN);
E 9
}

static void
vfe_rx_start(struct gem_dev *dp, int start_slot, int nslot)
{
D 11
	struct vfe_dev		*lp = (struct vfe_dev *)dp->private;
E 11
I 11
	struct vfe_dev	*lp = dp->private;
E 11

	gem_rx_desc_dma_sync(dp, start_slot, nslot, DDI_DMA_SYNC_FORDEV);

	if (IS_RHINE3_OR_LATER(lp->revid)) {
		OUTB(dp, FCR0, nslot);
	}
}

I 11
#ifdef DEBUG_LEVEL
E 11
static void
vfe_tx_desc_dump(struct gem_dev *dp, seqnum_t head, int ndesc)
{
D 11
	int			i;
	struct tx_desc		*tdp;
	struct vfe_dev		*lp = (struct vfe_dev *)dp->private;
E 11
I 11
	int		i;
	uint_t		tx_ring_size = dp->gc.gc_tx_ring_size;
	struct tx_desc	*tdp;
E 11

D 8
	cmn_err(CE_CONT, "!%s: tx_desc_dump:  slot:%d, seqnum:%d",
		dp->name,SLOT(head, TX_RING_SIZE), head);
E 8
I 8
	cmn_err(CE_CONT, "!%s: %s:  slot:%d, seqnum:%d",
D 11
		dp->name, __func__, SLOT(head, TX_RING_SIZE), head);
E 11
I 11
	    dp->name, __func__, SLOT(head, tx_ring_size), head);
E 11
E 8

	for (i = 0; i < ndesc; i++) {
D 11
		tdp = &((struct tx_desc *)dp->tx_ring)[
				SLOT(head + i, TX_RING_SIZE)];
E 11
I 11
		tdp = &VFE_TXDESC(dp->tx_ring)[SLOT(head + i, tx_ring_size)];
E 11

D 11
		ddi_dma_sync(dp->desc_dma_handle,
			(off_t)(((caddr_t)tdp) - dp->rx_ring),
			sizeof(struct tx_desc), DDI_DMA_SYNC_FORKERNEL);
E 11
I 11
		(void) ddi_dma_sync(dp->desc_dma_handle,
		    (off_t)(((caddr_t)tdp) - (intptr_t)dp->rx_ring),
		    sizeof (struct tx_desc), DDI_DMA_SYNC_FORKERNEL);
E 11

		cmn_err(CE_CONT, "! %d: %b, %b, 0x%08x",
D 9
			i, LE32(tdp->td_csr), TSR_BITS,
			LE32(tdp->td_length), TDES1_BITS,
			LE32(tdp->td_addr));
E 9
I 9
D 11
			i, LE_32(tdp->td_csr), TSR_BITS,
			LE_32(tdp->td_length), TDES1_BITS,
			LE_32(tdp->td_addr));
E 11
I 11
		    i, LE_32(tdp->td_csr), TSR_BITS,
		    LE_32(tdp->td_length), TDES1_BITS,
		    LE_32(tdp->td_addr));
E 11
E 9
	}
}
D 11

E 11
I 11
#endif /* DEBUG LEVEL */
E 11
static uint_t
vfe_tx_desc_stat(struct gem_dev *dp, int slot, int ndesc)
{
D 11
	struct tx_desc		*tdp;
	uint32_t		csr;
	uint_t			ret;
	int			cols;
	int			i;
	struct vfe_dev		*lp = (struct vfe_dev *)dp->private;
E 11
I 11
	struct tx_desc	*tdp;
	uint32_t	csr;
	uint_t		ret;
	int		cols;
	int		i;
	uint_t		tx_ring_size = dp->gc.gc_tx_ring_size;
	struct vfe_dev	*lp = dp->private;
E 11

	/*
D 12
	 * check the first descriptor of the packet
E 12
I 12
	 * tx status are stored in the first descriptor of the packet
E 12
	 */
D 11
	tdp = &((struct tx_desc *)dp->tx_ring)[slot];
E 11
I 11
	tdp = &VFE_TXDESC(dp->tx_ring)[slot];
E 11
D 12

E 12
D 9
	csr = LE32(tdp->td_csr);
E 9
I 9
D 11
	csr = LE_32(tdp->td_csr);
E 11
I 11
	csr = tdp->td_csr;
	csr = LE_32(csr);
E 11
E 9

#if DEBUG_LEVEL > 2
D 12
	if (ndesc > 0) {
E 12
I 12
	if (ndesc >= 2 && (csr & TSR_NCR)) {
E 12
		int		i;
		uint32_t	isr;

D 8
		RH_READ_ISR(dp, isr);
		cmn_err(CE_CONT,
			"!%s: vfe_tx_desc_stat: time: %d "
E 8
I 8
		VFE_READ_ISR(dp, isr);
		cmn_err(CE_CONT, "!%s: %s: time: %d "
E 8
D 11
			"slot:%d ndesc:%d isr:%b misr:%b",
D 8
			dp->name, ddi_get_lbolt(), slot, ndesc,
E 8
I 8
			dp->name, __func__, ddi_get_lbolt(), slot, ndesc,
E 8
			isr & 0xffff, ISR_BITS, isr >> 16, MISR_BITS);
E 11
I 11
		    "slot:%d ndesc:%d isr:%b misr:%b",
		    dp->name, __func__, ddi_get_lbolt(), slot, ndesc,
		    isr & 0xffff, ISR_BITS, isr >> 16, MISR_BITS);
E 11
		for (i = 0; i < ndesc; i++) {
			struct tx_desc	*tp;

D 11
			tp = &((struct tx_desc *)dp->tx_ring)[
						SLOT(slot + i, TX_RING_SIZE)];
E 11
I 11
			tp = &VFE_TXDESC(dp->tx_ring)[
			    SLOT(slot + i, tx_ring_size)];
E 11
			cmn_err(CE_CONT, "!%d: tsr: %b txdesc1: %b",
			    i,
D 9
			    LE32(tp->td_csr), TSR_BITS,
			    LE32(tp->td_length), TDES1_BITS);
E 9
I 9
			    LE_32(tp->td_csr), TSR_BITS,
			    LE_32(tp->td_length), TDES1_BITS);
E 9
		}
	}
#endif
D 8
	if ((csr & TDES0_OWN) != 0) {
E 8
I 8
	if (csr & TDES0_OWN) {
E 8
		/* not transmitted yet */
		return (0);
	}

	ret = GEM_TX_DONE;

D 4
	if (lp->td_unreliable) {
		goto x;
	}

E 4
#define	TSR_ERRS	\
D 4
	(TSR_SERR | TSR_TBUFF | TSR_UDF | TSR_CRS | TSR_OWC | TSR_ABT | TSR_CDH)
E 4
I 4
	(TSR_SERR | TSR_TBUFF | TSR_UDF | TSR_CRS | \
D 11
	 TSR_OWC | TSR_ABT | TSR_CDH | TSR_TDWB)
E 11
I 11
	TSR_OWC | TSR_ABT | TSR_CDH | TSR_TDWB)

E 11
E 4
	if ((csr & TSR_TXERR) == 0) {
		if (!dp->full_duplex && (cols = (csr & TSR_NCR)) > 0) {
			dp->stats.collisions += cols;
			if (cols == 1) {
				dp->stats.first_coll++;
D 11
			}
			else /* if (cols > 1)*/ {
E 11
I 11
			} else /* if (cols > 1) */ {
E 11
				dp->stats.multi_coll++;
			}
		}
		/* short cut for normal case */
D 12
		goto x;
E 12
I 12
		goto done;
E 12
	}

	DPRINTF(2, (CE_CONT, "!%s: tx error: tsr: %b  desc:%d",
D 11
		dp->name, csr, TSR_BITS, dp->tx_desc_head));
E 11
I 11
	    dp->name, csr, TSR_BITS, dp->tx_desc_head));
E 11

	dp->stats.errxmt++;

D 8
	if ((csr & TSR_CRS) != 0) {
E 8
I 8
	if (csr & TSR_CRS) {
E 8
		dp->stats.nocarrier++;
D 11
	}
D 8
	if ((csr & TSR_OWC) != 0) {
E 8
I 8
D 9
	if (csr & TSR_OWC) {
E 9
I 9
	else if (csr & TSR_OWC) {
E 11
I 11
	} else if (csr & TSR_OWC) {
E 11
E 9
E 8
		dp->stats.xmtlatecoll++;
D 11
	}
D 8
	if ((csr & TSR_UDF) != 0) {
E 8
I 8
D 9
	if (csr & TSR_UDF) {
E 9
I 9
	else if (csr & TSR_UDF) {
E 11
I 11
	} else if (csr & TSR_UDF) {
E 11
E 9
E 8
		dp->stats.underflow++;

		lp->tft = min(lp->tft+1, RTFT_SF);

		OUTB(dp, TCR,
D 11
			(lp->tft << TCR_RTFT_SHIFT) |
			TCR_LB_NORMAL | TCR_OFSET);
E 11
I 11
D 12
		    (lp->tft << TCR_RTFT_SHIFT) |
E 12
I 12
		    lp->tft << TCR_RTFT_SHIFT |
E 12
		    TCR_LB_NORMAL | TCR_OFSET);
E 11

		OUTW(dp, BCR,
D 11
			(lp->tft << BCR_CTFT_SHIFT) |
			(lp->rft << BCR_CRFT_SHIFT) |
			lp->maxdma);
E 11
I 11
D 12
		    (lp->tft << BCR_CTFT_SHIFT) |
		    (lp->rft << BCR_CRFT_SHIFT) |
E 12
I 12
		    lp->tft << BCR_CTFT_SHIFT |
		    lp->rft << BCR_CRFT_SHIFT |
E 12
		    lp->maxdma);
E 11

		/* transmitter halted, resend the packet */
D 8
		cmn_err(CE_CONT, "%s: transmitter halted, resend the packet",
E 8
I 8
		cmn_err(CE_CONT, "!%s: transmitter halted, resend the packet",
E 8
D 11
			dp->name);
E 11
I 11
		    dp->name);
E 11
		ndesc = 0;
		ret |= GEM_TX_ERR;
D 11
	}
D 8
	if ((csr & TSR_ABT) != 0) {
E 8
I 8
D 9
	if (csr & TSR_ABT) {
E 9
I 9
	else if (csr & TSR_ABT) {
E 11
I 11
	} else if (csr & TSR_ABT) {
E 11
E 9
E 8
		if (!dp->full_duplex) {
			dp->stats.excoll++;
			dp->stats.collisions += 16;
I 9
		} else {
			dp->stats.xmit_internal_err++;
E 9
		}
D 8
#ifdef notdef
E 8
I 8
D 11
#ifdef notdef /* debug */
E 11
I 11
#if DEBUG_LEVEL > 10
E 11
E 8
		vfe_tx_desc_dump(dp, dp->tx_desc_head, ndesc);
#endif
		/* transmitter halted, drop the packet */
		ret |= GEM_TX_ERR;
D 11
	}
I 9
	else {
E 11
I 11
	} else {
E 11
		/* unknown error */
		dp->stats.xmit_internal_err++;
	}
E 9

D 12
	if ((ret & GEM_TX_ERR) == 0) {
D 4
		/* no need to recover from a fatal error */
E 4
I 4
D 9
		/* no need to recover from the fatal error */
E 9
I 9
		/* no need to recover from fatal error */
E 9
E 4
		goto x;
	}
E 12
I 12
	if (ret & GEM_TX_ERR) {
		/*
		 * Try to recover the transmitter state without resetting
		 * the chip.
		 */
E 12

D 12
	/*
	 * Try to recover the transmitter state without resetting the chip.
	 */
	/* wait until the transmitter becomes idle */
D 8
	for (i = 0; (INW(dp, CR) & CR_TXON) != 0; i++) {
		if (i > 10) {
E 8
I 8
D 11
	i = 0;
	while (INW(dp, CR) & CR_TXON) {
		if (i++ > 10) {
E 8
			cmn_err(CE_WARN,
				"!%s: %s: timeout: stopping tx",
				dp->name, __func__);
E 11
I 11
	for (i = 0; INW(dp, CR) & CR_TXON; i++) {
		if (i > 10) {
			cmn_err(CE_WARN, "!%s: %s: timeout: stopping tx",
			    dp->name, __func__);
E 11
			goto x;
E 12
I 12
		/* wait until the transmitter becomes idle */
		i = 0;
		while (INW(dp, CR) & CR_TXON) {
			if (++i > 10) {
				cmn_err(CE_WARN,
				    "!%s: %s: timeout: stopping tx",
				    dp->name, __func__);
				goto done;
			}
			drv_usecwait(10);
E 12
		}
D 12
		drv_usecwait(10);
	}
	DPRINTF(2, (CE_CONT, "!%s: tx stopped in %d uS", dp->name, i*10));
E 12
I 12
		DPRINTF(2, (CE_CONT,
		    "!%s: tx stopped in %d uS", dp->name, i*10));
E 12

D 4
	/* fix Current Tx Desctriptor Address */
E 4
I 4
D 12
	/* fix Current Tx Desctriptor Address register */
E 4
	OUTL(dp, CTDA, ((uint32_t)dp->tx_ring_dma) +
D 11
		    SLOT(slot + ndesc, TX_RING_SIZE) * sizeof(struct tx_desc));
E 11
I 11
	    SLOT(slot + ndesc, tx_ring_size) * sizeof (struct tx_desc));
E 12
I 12
		/* correct Current Tx Desctriptor Address register */
		OUTL(dp, CTDA, ((uint32_t)dp->tx_ring_dma) +
		    SLOT(slot + ndesc, tx_ring_size) *
		    sizeof (struct tx_desc));
E 12
E 11

D 11
	/* fix the next actions to do. */
E 11
I 11
D 12
	/* fix the next action to do. */
E 11
	ret = (ndesc > 0) ? GEM_TX_DONE : 0;
E 12
I 12
		/* determin the next action to do. */
		ret = (ndesc > 0) ? GEM_TX_DONE : 0;
E 12

D 12
	/* enable the transmitter again. */
	OUTW(dp, CR, lp->cr);
E 12
I 12
		/* enable the transmitter again. */
		OUTW(dp, CR, lp->cr);
E 12

D 12
	/* kick tx polling */
D 8
	RH_KICK_TX(dp, lp->cr);
E 8
I 8
	VFE_KICK_TX(dp, lp->cr);
E 8
x:
D 11
	/* reset supress-intr bit */
	if (ret != 0) {
E 11
I 11
	/* reset suppress-intr bit */
	if (ret) {
E 12
I 12
		/* kick tx polling */
		VFE_KICK_TX(dp, lp->cr);
	}

done:
	/* reset suppress-intr bit in the first descriptor of the packet */
	if (ret != 0 && IS_RHINE2_OR_LATER(lp->revid)) {
E 12
E 11
		/*
D 12
		 * As tx was finished, update the interrupt mask.
E 12
I 12
		 * For Rhine II or later:
		 * Ensure that there is no suppress interrupt request
		 * in TD3.
E 12
		 */
D 11
		if (IS_RHINE1(lp->revid)) {
#ifdef OPT_TX_INTR
			if (dp->tx_desc_intr == dp->tx_desc_head + ndesc &&
D 8
			   (lp->imr & ISR_PTX) != 0) {
E 8
I 8
			   (lp->imr & ISR_PTX)) {
E 8
				/*
				 * XXX - Hardware IMR will be updated later.
				 */
				lp->imr &= ~ISR_PTX;
			}
#endif
		}
		else {
E 11
I 11
D 12
		if (!IS_RHINE1(lp->revid)) {
E 11
			/*
			 * For Rhine II or later:
			 * Ensure that there is no suppress interrupt request
			 * in TD3.
			 */
D 9
			tdp->td_next &= LE32(TDES3_NEXT);
E 9
I 9
			tdp->td_next &= LE_32(TDES3_NEXT);
E 9
		}
E 12
I 12
		tdp->td_next &= LE_32(TDES3_NEXT);
E 12
	}
	return (ret);
}

static uint64_t
vfe_rx_desc_stat(struct gem_dev *dp, int slot, int ndesc)
{
	struct rx_desc		*rdp;
	uint32_t		rsr;
	uint_t			ret;
	uint_t			len;
D 11
	struct vfe_dev		*lp = (struct vfe_dev *)dp->private;
E 11

D 11
	rdp = &((struct rx_desc *)dp->rx_ring)[slot];
E 11
I 11
	rdp = &VFE_RXDESC(dp->rx_ring)[slot];
E 11

D 9
	rsr = LE32(rdp->rd_status);
E 9
I 9
D 11
	rsr = LE_32(rdp->rd_status);
E 11
I 11
	rsr = rdp->rd_status;
	rsr = LE_32(rsr);
E 11
E 9
	len = (rsr >> RDES0_LEN_SHIFT) & RDES0_LEN_MASK;
	ret = GEM_RX_DONE;

D 6
	DPRINTF(2, (CE_CONT,
E 6
I 6
D 9
	DPRINTF(0, (CE_CONT,
E 9
I 9
D 11
	DPRINTF(1, (CE_CONT,
E 9
E 6
D 8
		"!%s: vfe_rx_desc_stat: slot:%d dma_addr:0x%x len:%d rsr 0x%b",
		dp->name, slot,
E 8
I 8
		"!%s: %s: slot:%d dma_addr:0x%x len:%d rsr 0x%b",
		dp->name, __func__, slot,
E 8
D 9
		LE32(rdp->rd_addr),
		LE32(rdp->rd_length),
		LE32(rdp->rd_status), RSR_BITS));
E 9
I 9
		LE_32(rdp->rd_addr),
		LE_32(rdp->rd_length),
		LE_32(rdp->rd_status), RSR_BITS));
E 11
I 11
	DPRINTF(2, (CE_CONT,
	    "!%s: %s: slot:%d dma_addr:0x%x len:%d rsr 0x%b",
	    dp->name, __func__, slot,
	    LE_32(rdp->rd_addr),
	    LE_32(rdp->rd_length),
	    LE_32(rdp->rd_status), RSR_BITS));
E 11
E 9

D 8
	if ((rsr & RDES0_OWN) != 0) {
E 8
I 8
	if (rsr & RDES0_OWN) {
E 8
D 4
		/* it isn't received yet */
E 4
I 4
		/* packets aren't received yet. */
E 4
		return (0);
	}

	if ((rsr & (RSR_STP | RSR_EDP)) != (RSR_STP | RSR_EDP)) {
		/* big packet, ignore this fragment */
I 12
		DPRINTF(-2, (CE_CONT,
		    "!%s: %s: slot:%d dma_addr:0x%x"
		    " len:%d rsr 0x%b",
		    dp->name, __func__, slot,
		    LE_32(rdp->rd_addr),
		    LE_32(rdp->rd_length),
		    LE_32(rdp->rd_status), RSR_BITS));
E 12
D 8
		if ((rsr & RSR_STP) != 0) {
E 8
I 8
		if (rsr & RSR_STP) {
E 8
			dp->stats.errrcv++;
			dp->stats.frame_too_long++;
		}
		return (GEM_RX_DONE | GEM_RX_ERR);
	}

D 12
	if ((rsr & RSR_RXOK) == 0) {
E 12
I 12
	if ((rsr & RSR_RXOK) == 0 ||
	    len > sizeof (struct ether_header) + 4 + dp->mtu + ETHERFCSL) {
E 12
		/* errored packet */
		dp->stats.errrcv++;
I 12
		DPRINTF(-2, (CE_CONT,
		    "!%s: %s: slot:%d dma_addr:0x%x"
		    " len:%d rsr 0x%b",
		    dp->name, __func__, slot,
		    LE_32(rdp->rd_addr),
		    LE_32(rdp->rd_length),
		    LE_32(rdp->rd_status), RSR_BITS));
E 12
D 8
		if ((rsr & RSR_LONG) != 0) {
E 8
I 8
		if (rsr & RSR_LONG) {
E 8
			dp->stats.frame_too_long++;
D 11
		}
D 8
		if ((rsr & RSR_RUNT) != 0) {
E 8
I 8
D 9
		if (rsr & RSR_RUNT) {
E 9
I 9
		else if (rsr & RSR_RUNT) {
E 11
I 11
		} else if (rsr & RSR_RUNT) {
E 11
E 9
E 8
			dp->stats.runt++;
D 12
			DPRINTF(2, (CE_CONT,
D 8
		"!%s: vfe_rx_desc_stat: slot:%d dma_addr:0x%x len:%d rsr 0x%b",
				dp->name, slot,
E 8
I 8
D 11
			"!%s: %s: slot:%d dma_addr:0x%x len:%d rsr 0x%b",
				dp->name, __func__, slot,
E 8
D 9
				LE32(rdp->rd_addr),
				LE32(rdp->rd_length),
				LE32(rdp->rd_status), RSR_BITS));
E 9
I 9
				LE_32(rdp->rd_addr),
				LE_32(rdp->rd_length),
				LE_32(rdp->rd_status), RSR_BITS));
E 9
		}
D 8
		if ((rsr & (RSR_SERR | RSR_BUFF)) != 0) {
E 8
I 8
D 9
		if (rsr & (RSR_SERR | RSR_BUFF)) {
E 9
I 9
		else if (rsr & (RSR_SERR | RSR_BUFF)) {
E 11
I 11
			    "!%s: %s: slot:%d dma_addr:0x%x"
			    " len:%d rsr 0x%b",
			    dp->name, __func__, slot,
			    LE_32(rdp->rd_addr),
			    LE_32(rdp->rd_length),
			    LE_32(rdp->rd_status), RSR_BITS));
E 12
		} else if (rsr & (RSR_SERR | RSR_BUFF)) {
E 11
E 9
E 8
			dp->stats.overflow++;
D 11
		}
D 8
		if ((rsr & RSR_FAE) != 0) {
E 8
I 8
D 9
		if (rsr & RSR_FAE) {
E 9
I 9
		else if (rsr & RSR_FAE) {
E 11
I 11
		} else if (rsr & RSR_FAE) {
E 11
E 9
E 8
			dp->stats.frame++;
D 11
		}
D 8
		if ((rsr & RSR_CRC) != 0) {
E 8
I 8
D 9
		if (rsr & RSR_CRC) {
E 9
I 9
		else if (rsr & RSR_CRC) {
E 11
I 11
		} else if (rsr & RSR_CRC) {
E 11
E 9
E 8
			dp->stats.crc++;
D 11
		}
I 9
		else {
E 11
I 11
		} else {
E 11
			dp->stats.rcv_internal_err++;
		}
E 9

		ret |= GEM_RX_ERR;
	}

	if (len >= ETHERFCSL) {
I 12
		/* remove fcs */
E 12
		len -= ETHERFCSL;
	}

	return (ret | (len & GEM_RX_LEN));
}

static void
vfe_tx_desc_init(struct gem_dev *dp, int slot)
{
D 11
	struct tx_desc		*tdp;
E 11
I 11
	uint_t		tx_ring_size = dp->gc.gc_tx_ring_size;
	uint32_t	tmp;
	struct tx_desc	*tdp;
E 11

D 11
	tdp = &((struct tx_desc *)dp->tx_ring)[slot];
E 11
I 11
	tdp = &VFE_TXDESC(dp->tx_ring)[slot];
E 11

	/* invalidate this descriptor */
	tdp->td_csr = 0;

	/* link to previous descriptor */
D 11
	tdp = &((struct tx_desc *)dp->tx_ring)[SLOT(slot - 1, TX_RING_SIZE)];
D 9
	tdp->td_next = LE32(dp->tx_ring_dma + slot*sizeof(struct tx_desc));
E 9
I 9
	tdp->td_next = LE_32(dp->tx_ring_dma + slot*sizeof(struct tx_desc));
E 11
I 11
	tdp = &VFE_TXDESC(dp->tx_ring)[SLOT(slot - 1, tx_ring_size)];
	tmp = dp->tx_ring_dma + slot*sizeof (struct tx_desc);
	tdp->td_next = LE_32(tmp);
E 11
E 9
}

static void
vfe_rx_desc_init(struct gem_dev *dp, int slot)
{
D 11
	struct rx_desc		*rdp;
E 11
I 11
	uint32_t	tmp;
	struct rx_desc	*rdp;
E 11

D 11
	rdp = &((struct rx_desc *)dp->rx_ring)[slot];
E 11
I 11
	rdp = &VFE_RXDESC(dp->rx_ring)[slot];
E 11

	/* invalidate this descriptor */
	rdp->rd_status = 0;

	/* link this to its previous descriptor */
D 11
	rdp = &((struct rx_desc *)dp->rx_ring)[SLOT(slot - 1, RX_RING_SIZE)];
D 9
	rdp->rd_next = LE32(dp->rx_ring_dma + slot*sizeof(struct rx_desc));
E 9
I 9
	rdp->rd_next = LE_32(dp->rx_ring_dma + slot*sizeof(struct rx_desc));
E 11
I 11
	rdp = &VFE_RXDESC(dp->rx_ring)[SLOT(slot - 1, dp->gc.gc_rx_ring_size)];
D 12
	tmp = dp->rx_ring_dma + slot*sizeof (struct rx_desc);
E 12
I 12
	tmp = dp->rx_ring_dma + sizeof (struct rx_desc) * slot;
E 12
	rdp->rd_next = LE_32(tmp);
E 11
E 9
}

static void
vfe_tx_desc_clean(struct gem_dev *dp, int slot)
{
	struct tx_desc		*tdp;

D 11
	tdp = &((struct tx_desc *)dp->tx_ring)[slot];
E 11
I 11
	tdp = &VFE_TXDESC(dp->tx_ring)[slot];
E 11

	/* invalidate this descriptor */
	tdp->td_csr = 0;
D 9
	tdp->td_next &= LE32(TDES3_NEXT);
E 9
I 9
	tdp->td_next &= LE_32(TDES3_NEXT);
E 9
}

static void
vfe_rx_desc_clean(struct gem_dev *dp, int slot)
{
	struct rx_desc		*rdp;

D 11
	rdp = &((struct rx_desc *)dp->rx_ring)[slot];
E 11
I 11
	rdp = &VFE_RXDESC(dp->rx_ring)[slot];
E 11

	/* invalidate this descriptor */
	rdp->rd_status = 0;
}

/*
 * Device depend interrupt handler
 */
D 11
#ifdef OPT_TX_INTR
static
uint_t vfe_update_imr(struct gem_dev *dp)
{
	uint_t		ret;
	struct vfe_dev	*lp = (struct vfe_dev *)dp->private;

	ret = DDI_INTR_UNCLAIMED;

	mutex_enter(&dp->intrlock);
	mutex_enter(&dp->xmitlock);

	if (lp->imr_change_req) {
D 8
		if ((dp->misc_flag & GEM_NOINTR) == 0 && lp->imr_hw != 0 &&
E 8
I 8
		if ((dp->misc_flag & GEM_NOINTR) == 0 && lp->imr_hw &&
E 8
		     lp->imr_hw != lp->imr) {
			lp->imr_hw = lp->imr;
D 8
			RH_WRITE_IMR(dp, lp->imr_hw);
E 8
I 8
			VFE_WRITE_IMR(dp, lp->imr_hw);
E 8
		}
		lp->imr_change_req = B_FALSE;
		ret = DDI_INTR_CLAIMED;
	}

	mutex_exit(&dp->xmitlock);
	mutex_exit(&dp->intrlock);

	return (ret);
}
#endif /* OPT_TX_INTR */

static u_int
E 11
I 11
static uint_t
E 11
vfe_interrupt(struct gem_dev *dp)
{
D 8
	int		i;
E 8
I 8
D 9
	seqnum_t	i;
E 9
I 9
	seqnum_t	s;
E 9
E 8
	uint32_t	isr;
I 9
D 11
	volatile uint_t	x;
E 11
I 11
#ifdef WA_SPURIOUS_INTR
	uint32_t	bogus_isr;
#endif
E 11
E 9
	uint_t		flag = 0;
	boolean_t	need_to_reset = B_FALSE;
D 11
	struct vfe_dev	*lp = (struct vfe_dev *)dp->private;
E 11
I 11
	uint_t		tx_ring_size = dp->gc.gc_tx_ring_size;
	struct vfe_dev	*lp = dp->private;
E 11

D 8
	RH_READ_ISR(dp, isr);
E 8
I 8
	VFE_READ_ISR(dp, isr);
E 8

D 11
	if ((isr & lp->imr_hw) == 0) {
E 11
I 11
#ifdef WA_SPURIOUS_INTR
	bogus_isr = lp->isr_pended;
	lp->isr_pended = 0;
	if (((isr | bogus_isr) & lp->imr) == 0) {
E 11
		/* Not for us */
		return (DDI_INTR_UNCLAIMED);
	}
D 11

D 10
	DPRINTF(2, (CE_CONT, "!%s: Interrupt, time:%d isr: %b, misr: %b",
E 10
I 10
	DPRINTF(2, (CE_CONT, "!%s: Interrupt, time:%ld isr: %b, misr: %b",
E 10
		dp->name, ddi_get_lbolt(),
		isr & 0xffff, ISR_BITS, isr >> 16, MISR_BITS));
D 9

E 9
I 9
#ifndef CONFIG_OPT_IO
E 9
	/* disable interrupt */
D 8
	RH_WRITE_IMR(dp, 0);
E 8
I 8
	VFE_WRITE_IMR(dp, 0);
E 11
I 11
#else
	if ((isr & lp->imr) == 0) {
		/* Not for us */
		return (DDI_INTR_UNCLAIMED);
	}
E 11
E 8
D 9

E 9
I 9
#endif
I 11

	DPRINTF(2, (CE_CONT,
	    "!%s: Interrupt, time:%ld isr: %b, misr: %b",
	    dp->name, ddi_get_lbolt(),
	    isr & 0xffff, ISR_BITS, isr >> 16, MISR_BITS));

E 11
E 9
D 2
	if (!dp->nic_active) {
E 2
I 2
	if (!dp->mac_active) {
E 2
		/* the device is not active, no more interrupts */
		lp->imr = 0;
D 11
		lp->imr_hw = lp->imr;
I 9
#ifdef CONFIG_OPT_IO
E 11
I 11

E 11
		/* disable interrupt */
		VFE_WRITE_IMR(dp, 0);
D 11
#endif
E 11
I 11

E 11
E 9
D 8
		RH_WRITE_ISR(dp, isr);
E 8
I 8
		VFE_WRITE_ISR(dp, isr);
E 8

		return (DDI_INTR_CLAIMED);
	}
D 4
#ifdef RESET_TEST
E 4
I 4
#ifdef TEST_RESET_ON_ERRROR
E 4
	lp->reset_test++;
	if ((lp->reset_test % 10000) == 9999) {
		need_to_reset = B_TRUE;
	}
#endif

	/* clear interrupts */
D 8
	RH_WRITE_ISR(dp, isr); FLSHW(dp, ISR);
E 8
I 8
D 11
	VFE_WRITE_ISR(dp, isr); FLSHW(dp, ISR);
E 11
I 11
	VFE_WRITE_ISR(dp, isr);
E 11
E 8

D 11
	isr &= lp->imr_hw;
E 11
I 11
	/* barrier to commit interrupt status */
	FLSHW(dp, ISR);
E 11

I 11
	isr &= lp->imr;

E 11
D 8
	if ((isr & ISR_CNT) != 0) {
E 8
I 8
	if (isr & ISR_CNT) {
E 8
		/* statics counter overflow */
D 11
		vfe_get_stats(dp);
E 11
I 11
		(void) vfe_get_stats(dp);
E 11
	}

	if (isr & (ISR_PRX | ISR_RXE | ISR_PKRACE | ISR_RU | ISR_NORBF)) {
D 9

E 9
D 4
		/* packet was received, or receive error happened */
E 4
I 4
		/* A packet was received, or receive error happened */
E 4
		/* RU: receive buffer unavailable */
		(void) gem_receive(dp);

D 8
		if ((isr & (ISR_RU | ISR_NORBF)) != 0) {
E 8
I 8
		if (isr & (ISR_RU | ISR_NORBF)) {
I 9
			dp->stats.errrcv++;
E 9
E 8
			dp->stats.norcvbuf++;
I 9

			DPRINTF(2, (CE_CONT,
D 11
				"!%s: rx buffer ran out: isr:%b misr:%b cr:%b",
				dp->name, isr & 0xffff, ISR_BITS,
				(isr >> 16), MISR_BITS, lp->cr, CR_BITS));
E 11
I 11
			    "!%s: rx buffer ran out: isr:%b misr:%b cr:%b",
			    dp->name, isr & 0xffff, ISR_BITS,
			    (isr >> 16), MISR_BITS, lp->cr, CR_BITS));
E 11
E 9
		}
D 4

E 4
	}

D 8
	if ((isr & ISR_OVFI) != 0) {
E 8
I 8
	if (isr & ISR_OVFI) {
E 8
		/*
		 * receive FIFO overflow
		 */
		dp->stats.overflow++;
I 9
		goto x;
E 9
	}

D 8
	if ((isr & ISR_BE) != 0) {
E 8
I 8
	if (isr & ISR_BE) {
E 8
		cmn_err(CE_WARN, "!%s: unexpected interrupt: isr:%b misr:%b",
D 11
			dp->name, isr & 0xffff, ISR_BITS, isr >> 16, MISR_BITS);
E 11
I 11
		    dp->name, isr & 0xffff, ISR_BITS, isr >> 16, MISR_BITS);
E 11
		need_to_reset = B_TRUE;
		goto x;
	}
D 4

E 4
I 4
#ifdef TEST_TDWB
	if ((++(lp->tdwb_cnt) % 10000) == 0) {
		isr |= MISR_TDWBI << 16;
		OUTW(dp, CR, lp->cr & ~CR_TXON);
	}
#endif
E 4
D 9
	if ((isr & (MISR_TDWBI << 16)) != 0) {
E 9
I 9
	if (isr & (MISR_TDWBI << 16)) {
E 9
		int	cnt;

		DPRINTF(0, (CE_WARN, "!%s: TDWBI interrupt: isr:%b misr:%b",
D 11
			dp->name, isr & 0xffff, ISR_BITS,
			isr >> 16, MISR_BITS));
E 11
I 11
		    dp->name, isr & 0xffff, ISR_BITS,
		    isr >> 16, MISR_BITS));
E 11

		mutex_enter(&dp->xmitlock);

D 4
		/* XXX - stop Tx */
E 4
I 4
		/* wait a while until tx side stops */
E 4
D 8
		for (cnt = 0; (INW(dp, CR) & CR_TXON) != 0; cnt++) {
			if (cnt == 10) {
E 8
I 8
D 9
		cnt = 0;
		while (INW(dp, CR) & CR_TXON) {
			if (cnt++ > 10) {
E 9
I 9
		for (cnt = 0; (INW(dp, CR) & CR_TXON); cnt++) {
			if (cnt > 10) {
E 9
E 8
D 4
				break;
E 4
I 4
D 11
				/* timeout: tx side is still active.*/
E 11
I 11
				/* timeout: tx side is still active */
E 11
				need_to_reset = B_TRUE;
				mutex_exit(&dp->xmitlock);
				goto x;
E 4
			}
			drv_usecwait(10);
		}

		DPRINTF(2, (CE_CONT, "!%s: tx stopped on TDWBI in %d uS",
D 11
			dp->name, cnt*10));
E 11
I 11
		    dp->name, cnt*10));
E 11

D 4
		if (cnt == 10) {
			/* timeout: we failed to stop tx side */
			need_to_reset = B_TRUE;
			mutex_exit(&dp->xmitlock);
			goto x;
E 4
I 4
		/* force to reset OWN bit in all current tx descriptors. */
D 9
		for (i = dp->tx_desc_head; i != dp->tx_desc_tail; i++) {
E 9
I 9
		for (s = dp->tx_desc_head; s != dp->tx_desc_tail; s++) {
E 9
			/*
			 * XXX - we use non-fatal TSR_TDWB (JAB) error bit
			 * to show the error in statistics.
			 */
D 11
			((struct tx_desc *) dp->tx_ring)
D 9
				[SLOT(i, TX_RING_SIZE)].td_csr = LE32(TSR_TDWB);
E 9
I 9
				[SLOT(s, TX_RING_SIZE)].td_csr=LE_32(TSR_TDWB);
E 11
I 11
			VFE_TXDESC(dp->tx_ring)[
			    SLOT(s, tx_ring_size)].td_csr = LE_32(TSR_TDWB);
E 11
E 9
E 4
		}
I 4
		gem_tx_desc_dma_sync(dp,
D 11
				SLOT(dp->tx_desc_head, TX_RING_SIZE),
				dp->tx_desc_tail - dp->tx_desc_head,
				DDI_DMA_SYNC_FORDEV);
E 11
I 11
		    SLOT(dp->tx_desc_head, tx_ring_size),
		    dp->tx_desc_tail - dp->tx_desc_head,
		    DDI_DMA_SYNC_FORDEV);
E 11
E 4

D 4
		lp->td_unreliable = B_TRUE;
		(void)gem_reclaim_txbuf(dp);
		lp->td_unreliable = B_FALSE;

E 4
		/*
D 4
		 * Fix Current Tx Desctriptor to point
		 * the head of tx list.
E 4
I 4
D 9
		 * fix Current Tx Desctriptor to point the tail of tx list.
E 9
I 9
		 * fix Current Tx Desctriptor to point the tail of the tx list.
E 9
E 4
		 */
D 11
		OUTL(dp, CTDA, ((uint32_t)dp->tx_ring_dma) +
D 4
			    SLOT(dp->tx_desc_head, TX_RING_SIZE)
E 4
I 4
			    SLOT(dp->tx_desc_tail, TX_RING_SIZE)
E 4
				* sizeof(struct tx_desc));
E 11
I 11
		OUTL(dp, CTDA,
		    ((uint32_t)dp->tx_ring_dma) +
		    SLOT(dp->tx_desc_tail, tx_ring_size)
		    * sizeof (struct tx_desc));
E 11

D 4
		/* XXX - restart Tx */
E 4
I 4
		/* force to call gem_tx_done() later. */
		isr |= ISR_TXE;

		/* restart Tx side again. */
E 4
		OUTW(dp, CR, lp->cr);
D 8
		RH_KICK_TX(dp, lp->cr);
E 8
I 8
		VFE_KICK_TX(dp, lp->cr);
E 8

I 4
		/* we have done all dirty things. */
E 4
		mutex_exit(&dp->xmitlock);
	}

D 4
	if ((isr & ISR_PTX) != 0) {
E 4
I 4
D 8
	if ((isr & (ISR_PTX | ISR_TXE | ISR_TU | ISR_ABTI)) != 0) {
E 8
I 8
	if (isr & (ISR_PTX | ISR_TXE | ISR_TU | ISR_ABTI)) {
E 8
E 4
		if (gem_tx_done(dp)) {
			flag |= INTR_RESTART_TX;
		}
	}
I 9

E 9
D 4

	if ((isr & (ISR_TXE | ISR_TU | ISR_ABTI)) != 0) {
		/*
		 * Need to process transmitted buffer immediately.
		 */
		if (gem_tx_done(dp)) {
			flag |= INTR_RESTART_TX;
		}
	}
E 4
D 5
#ifdef notdef
E 5
I 5
#ifdef CONFIG_MAUTO
E 5
D 8
	if ((isr & ISR_SRCI) != 0) {
E 8
I 8
	if (isr & ISR_SRCI) {
E 8
		/*
		 * PHY port status changed.
		 */
D 5
		DPRINTF(0, (CE_WARN,
			"%s: port status changed: isr:%b misr:%b",
E 5
I 5
		DPRINTF(0, (CE_CONT,
D 8
			"%s: port status changed: isr:0x%b misr:0x%b",
E 8
I 8
D 11
			"!%s: port status changed: isr:0x%b misr:0x%b",
E 8
E 5
			dp->name,
			isr & 0xffff, ISR_BITS, isr >> 16, MISR_BITS));
E 11
I 11
		    "!%s: port status changed: isr:0x%b misr:0x%b",
		    dp->name,
		    isr & 0xffff, ISR_BITS, isr >> 16, MISR_BITS));
E 11
		if (gem_mii_link_check(dp)) {
			flag |= INTR_RESTART_TX;
		}
	}
#endif
D 8
	if ((isr & (ISR_TU | ISR_ETI/*| ISR_KEYI*/)) != 0) {
E 8
I 8
D 9
	if (isr & (ISR_TU | ISR_ETI/*| ISR_KEYI*/)) {
E 9
I 9
	if (isr & (ISR_TU | ISR_ETI | ISR_KEYI)) {
E 9
E 8
		/*
		 * unexpected interrupt
		 */
		/* BE: PCI bus error */
		/* TU: Transmit buffer underflow */
		/* ETI: Transmit descriptor underflow */
		/* KEYI : magic packet received / gpio  */

		cmn_err(CE_WARN,
D 11
			"!%s: unexpected interrupt: isr:%b misr:%b",
			dp->name,
			isr & 0xffff, ISR_BITS, isr >> 16, MISR_BITS);
E 11
I 11
		    "!%s: unexpected interrupt: isr:%b misr:%b",
		    dp->name,
		    isr & 0xffff, ISR_BITS, isr >> 16, MISR_BITS);
E 11
I 9

		need_to_reset = B_TRUE;
E 9
	}
x:
D 8
	RH_READ_ISR(dp, isr);
E 8
I 8
D 9
	VFE_READ_ISR(dp, isr);
E 8

E 9
	if (need_to_reset) {
D 8
		gem_restart_nic(dp, B_TRUE);
E 8
I 8
D 11
		gem_restart_nic(dp, GEM_RESTART_KEEP_BUF);
E 11
I 11
		(void) gem_restart_nic(dp, GEM_RESTART_KEEP_BUF);
E 11
E 8
		flag |= INTR_RESTART_TX;
	}

D 11
	if ((dp->misc_flag & GEM_NOINTR) == 0) {
		/* enable interrupts again */
		if (lp->imr_hw != lp->imr) {
			mutex_enter(&dp->xmitlock);
			if (lp->imr_hw != lp->imr) {
				lp->imr_hw = lp->imr;
			}
			mutex_exit(&dp->xmitlock);
I 9
#ifdef CONFIG_OPT_IO
			VFE_WRITE_IMR(dp, lp->imr_hw);
#endif
E 9
		}
I 9
#ifndef CONFIG_OPT_IO
E 9
D 8
		RH_WRITE_IMR(dp, lp->imr_hw);
E 8
I 8
		VFE_WRITE_IMR(dp, lp->imr_hw);
I 9
#endif
E 9
E 8
	}

E 11
	return (DDI_INTR_CLAIMED | flag);
}

/*
 * HW depend MII routines
 */
I 7

/* vendor specific registers in VT6103 based PHY */
#define	MII_PHYCFG1	0x10
#define	MII_PHYCFG1_PHYADDR	0xf800u
#define	MII_PHYCFG1_PHYADDR_SHIFT	11
#define	MII_PHYCFG1_FIBRE	0x0400u
#define	MII_PHYCFG1_SIP		0x0200u
#define	MII_PHYCFG1_FORCE_LINK	0x0100u
#define	MII_PHYCFG1_SQUELCH	0x0080u
#define	MII_PHYCFG1_LED		0x0060u
#define	MII_PHYCFG1_REPEATER	0x0010u
#define	MII_PHYCFG1_PHYINT	0x0008u
#define	MII_PHYCFG1_SYMBOL	0x0004u

E 7
static void
vfe_mii_sync(struct gem_dev *dp)
{
	/* nothing to do */
}

static uint16_t
vfe_mii_read(struct gem_dev *dp, uint_t reg)
{
D 5
	int	i;
E 5
I 5
	int		i;
	uint16_t	val;
D 11
	struct vfe_dev	*lp = (struct vfe_dev *)dp->private;
E 11
I 11
	struct vfe_dev	*lp = dp->private;
E 11
E 5

I 5
D 10
	DPRINTF(3, (CE_CONT, "!%s: %s: called at time:%d",
E 10
I 10
	DPRINTF(3, (CE_CONT, "!%s: %s: called at time:%ld",
E 10
D 11
		dp->name, __func__, ddi_get_lbolt()));
E 11
I 11
	    dp->name, __func__, ddi_get_lbolt()));
E 11

#ifdef CONFIG_MAUTO
	if (dp->mac_active && IS_RHINE2_OR_LATER(lp->revid)) {
		vfe_stop_mauto(dp);
	}
#endif
	if (lp->last_phy_addr != dp->mii_phy_addr) {
		OUTB(dp, MPHY, dp->mii_phy_addr);
		lp->last_phy_addr = dp->mii_phy_addr;
	}
E 5
	OUTB(dp, MIIADR, reg);
I 11
	FLSHB(dp, MIIADR);
E 11
	OUTB(dp, MIICR, INB(dp, MIICR) | MIICR_RCMD);

D 8
	for (i = 0; (INB(dp, MIICR) & MIICR_RCMD) != 0; i++) {
		if  (i > 100) {
E 8
I 8
D 11
	i = 0;
	while (INB(dp, MIICR) & MIICR_RCMD) {
		if  (i++ > 100) {
E 11
I 11
	for (i = 0; INB(dp, MIICR) & MIICR_RCMD; i++) {
		if (i > 100) {
E 11
E 8
			cmn_err(CE_WARN,
D 11
				"!%s: %s: timeout", dp->name, __func__);
E 11
I 11
			    "!%s: %s: timeout", dp->name, __func__);
E 11
D 5
			return (0xffff);
E 5
I 5
			val = 0;
			goto x;
E 5
		}
		drv_usecwait(10);
	}
D 5
	return (INW(dp, MIIDATA));
E 5
I 5

	val = INW(dp, MIIDATA);
I 7

E 7
x:
#ifdef CONFIG_MAUTO
	if (dp->mac_active && IS_RHINE2_OR_LATER(lp->revid)) {
		vfe_start_mauto(dp);
	}
#endif
	return (val);
E 5
}

static void
vfe_mii_write_raw(struct gem_dev *dp, uint_t reg, uint16_t val)
{
D 5
	int	i;
E 5
I 5
	int		i;
D 11
	struct vfe_dev	*lp = (struct vfe_dev *)dp->private;
E 11
I 11
	struct vfe_dev	*lp = dp->private;
E 11
E 5

I 5
#ifdef CONFIG_MAUTO
	if (dp->mac_active && IS_RHINE2_OR_LATER(lp->revid)) {
		vfe_stop_mauto(dp);
	}
#endif
	if (lp->last_phy_addr != dp->mii_phy_addr) {
		OUTB(dp, MPHY, dp->mii_phy_addr);
		lp->last_phy_addr = dp->mii_phy_addr;
	}
E 5
	OUTB(dp, MIIADR, reg);
I 11
	FLSHB(dp, MIIADR);
E 11
	OUTW(dp, MIIDATA, val);
I 11
	FLSHW(dp, MIIDATA);
E 11
	OUTB(dp, MIICR, INB(dp, MIICR) | MIICR_WCMD);
D 8
	for (i = 0; (INB(dp, MIICR) & MIICR_WCMD) != 0; i++) {
		if (i > 100) {
E 8
I 8
D 11
	i = 0;
	while (INB(dp, MIICR) & MIICR_WCMD) {
		if (i++ > 100) {
E 11
I 11
	for (i = 0; INB(dp, MIICR) & MIICR_WCMD; i++) {
		if (i > 100) {
E 11
E 8
			cmn_err(CE_WARN,
D 11
				"!%s: %s: timeout", dp->name, __func__);
E 11
I 11
			    "!%s: %s: timeout", dp->name, __func__);
E 11
D 5
			return;
E 5
I 5
			break;
E 5
		}
		drv_usecwait(10);
	}
I 5
#ifdef CONFIG_MAUTO
	if (dp->mac_active && IS_RHINE2_OR_LATER(lp->revid)) {
		vfe_start_mauto(dp);
	}
#endif
E 5
}

static void
vfe_mii_write(struct gem_dev *dp, uint_t reg, uint16_t val)
{
	uint16_t	ret;
D 11
	struct vfe_dev	*lp = (struct vfe_dev *)dp->private;
E 11
I 11
	struct vfe_dev	*lp = dp->private;
E 11

	if (reg == MII_CONTROL &&
D 11
	   (IS_RHINE3_OR_LATER(lp->revid)
	   || (IS_RHINE2_OR_LATER(lp->revid) && IS_VT6103(dp->mii_phy_id)))) {
E 11
I 11
	    (IS_RHINE3_OR_LATER(lp->revid) ||
	    (IS_RHINE2_OR_LATER(lp->revid) && IS_VT6103(dp->mii_phy_id)))) {
E 11

D 7
		ret = vfe_mii_read(dp, 0x10);
E 7
I 7
		/* fix MII_PHYCFG1 register in VT6103 based PHY */

		ret = vfe_mii_read(dp, MII_PHYCFG1);
E 7
D 8
		if ((val & MII_CONTROL_ANE) != 0) {
E 8
I 8
		if (val & MII_CONTROL_ANE) {
E 8
			ret &= ~1;
		} else {
			ret |= 1;
		}
D 7
		vfe_mii_write_raw(dp, 0x10, ret);
E 7
I 7
		vfe_mii_write_raw(dp, MII_PHYCFG1, ret);
E 7
	}

	vfe_mii_write_raw(dp, reg, val);
}

static int
D 6
vfe_mii_init(struct gem_dev *dp)
E 6
I 6
vfe_mii_probe(struct gem_dev *dp)
E 6
{
I 7
	int		ret;
I 9
	uint16_t	adv;
	uint16_t	adv_org;
E 9
E 7
D 11
	struct vfe_dev	*lp = (struct vfe_dev *)dp->private;
E 11
I 11
	struct vfe_dev	*lp = dp->private;
E 11

I 5
D 8
	DPRINTF(0, (CE_CONT, "%s: %s: MIISR:%x",
E 8
I 8
	DPRINTF(0, (CE_CONT, "!%s: %s: MIISR:%x",
E 8
D 11
			dp->name, __func__, INB(dp, MIISR)));
E 11
I 11
	    dp->name, __func__, INB(dp, MIISR)));
E 11

E 5
D 4
	if (gem_mii_init_default(dp) < 0) {
E 4
I 4
D 6
	if (gem_mii_init_default(dp) != GEM_SUCCESS) {
E 6
I 6
D 7
	if (gem_mii_probe_default(dp) != GEM_SUCCESS) {
E 6
E 4
		return (GEM_FAILURE);
E 7
I 7
	if ((ret = gem_mii_probe_default(dp)) != GEM_SUCCESS) {
		return (ret);
E 7
	}
D 9

E 9
I 9
D 10
#if 1
	/* check if the phy can advertize pause abilities */
E 10
I 10

	/* check if the phy can advertise pause abilities */
E 10
	adv_org = vfe_mii_read(dp, MII_AN_ADVERT);
D 11
	vfe_mii_write(dp, MII_AN_ADVERT,
				MII_ABILITY_PAUSE | MII_ABILITY_ASM_DIR);
E 11
I 11
	vfe_mii_write(dp,
	    MII_AN_ADVERT,
	    MII_ABILITY_PAUSE | MII_ABILITY_ASM_DIR);
E 11
	adv = vfe_mii_read(dp, MII_AN_ADVERT);
	if ((adv & MII_ABILITY_PAUSE) == 0) {
		dp->gc.gc_flow_control &= ~1;
	}
	if ((adv & MII_ABILITY_ASM_DIR) == 0) {
		dp->gc.gc_flow_control &= ~2;
	}
	vfe_mii_write(dp, MII_AN_ADVERT, adv_org);
D 10
#endif
E 10
I 10

E 10
E 9
D 5
	vfe_stop_mauto(dp);

E 5
	/*
	 * Fibre mode support for VT6105M and VT6103.
D 12
	 * The default bits in mii status register are still
D 4
	 * normal mii mode even if LED port waa strapped for fibre mode.
E 4
I 4
	 * normal mii mode even if LED port was strapped for fibre mode.
E 4
D 11
	 * Therefore, we need to check fibre mode bit in PHY configuration1
E 11
I 11
	 * Therefore, we need to check fibre mode bit in PHY config1
E 11
	 * register by ourselves.
E 12
I 12
	 * The bits in mii status register were still default, that 10Mbps
	 * bits were set, even if LED port was strapped for fibre mode.
	 * Therefore, we need to check the fibre mode bit in PHY config1
	 * register by ourselves, and remove 10Mbps mode bits from the
	 * value of mii_status, which are not sepported by 100M fibre media.
E 12
	 */
D 7
#define	MII_PHYCFG1	0x10
#define	MII_PHYCFG1_PHYADDR	0xf800u
#define	MII_PHYCFG1_PHYADDR_SHIFT	11
#define	MII_PHYCFG1_FIBRE	0x0400u
#define	MII_PHYCFG1_SIP		0x0200u
#define	MII_PHYCFG1_FORCE_LINK	0x0100u
#define	MII_PHYCFG1_SQUELCH	0x0080u
#define	MII_PHYCFG1_LED		0x0060u
#define	MII_PHYCFG1_REPEATER	0x0010u
#define	MII_PHYCFG1_PHYINT	0x0008u
#define	MII_PHYCFG1_SYMBOL	0x0004u

E 7
D 6
	if (IS_RHINE3M_OR_LATER(lp->revid) || IS_VT6103(dp->mii_phy_id)) {
E 6
I 6
	if (IS_RHINE3M(lp->revid) || IS_VT6103(dp->mii_phy_id)) {
E 6
		/* check fibre mode */
D 7
		if ((vfe_mii_read(dp, MII_PHYCFG1) & MII_PHYCFG1_FIBRE) != 0
D 6
		     && !dp->mii_fixedmode) {
E 6
I 6
		     && dp->anadv_autoneg) {
E 6
			/*
			 * force to use 100Mbps full duplex mode
			 */
D 6
			dp->mii_fixedmode = B_TRUE;
			dp->speed = GEM_SPD_100;
			dp->full_duplex = B_TRUE;
E 6
I 6
			dp->anadv_autoneg = B_FALSE;
E 7
I 7
		if (vfe_mii_read(dp, MII_PHYCFG1) & MII_PHYCFG1_FIBRE) {
E 7
E 6

I 6
D 7
			dp->anadv_100fdx = B_TRUE;
			dp->anadv_100t4  = B_FALSE;
			dp->anadv_100hdx = B_FALSE;
			dp->anadv_10fdx  = B_FALSE;
			dp->anadv_10hdx  = B_FALSE;
#ifdef NEVER
			dp->full_duplex = B_TRUE;
			dp->speed = GEM_SPD_100;
#endif
E 6
			cmn_err(CE_CONT,
D 5
	"%s: fibre mode detected, forcing to 100M full duplex fixed mode",
E 5
I 5
		"%s: fibre mode detected, forcing to 100M full duplex mode",
E 5
				dp->name);
E 7
I 7
			/* fix capabilities in status register */

D 11
			dp->mii_status &= ~(MII_STATUS_10_FD | MII_STATUS_10 |
					    MII_STATUS_CANAUTONEG);
E 11
I 11
			dp->mii_status &=
			    ~(MII_STATUS_10_FD | MII_STATUS_10 |
			    MII_STATUS_CANAUTONEG);
I 12

			dp->mii_status_ro = ~dp->mii_status;
E 12
E 11
E 7
		}
	}

D 7
	return (GEM_SUCCESS);
E 7
I 7
	return (ret);
E 7
}

/* ======================================================== */
/*
 * OS depend (device driver) routine
 */
/* ======================================================== */
static int
vfeattach(dev_info_t *dip, ddi_attach_cmd_t cmd)
{
	int			i;
I 11
#ifdef notdef
E 11
	int			n;
	ddi_iblock_cookie_t	c;
I 11
#endif
E 11
	ddi_acc_handle_t	conf_handle;
	uint16_t		vid;
	uint16_t		did;
	uint8_t			revid;
	int			unit;
	struct chip_info	*p;
	const char		*drv_name;
	struct gem_dev		*dp;
	struct vfe_dev		*lp;
	uint8_t			*base;
	ddi_acc_handle_t	reg_ha;
	struct gem_conf		*gcp;
	uint32_t		ilr;

D 11
	unit     = ddi_get_instance(dip);
E 11
I 11
	unit = ddi_get_instance(dip);
E 11
	drv_name = ddi_driver_name(dip);

D 8
	DPRINTF(1, (CE_CONT, "!%s%d: vfeattach: called at time:%d",
		drv_name, unit, ddi_get_lbolt()));
E 8
I 8
D 10
	DPRINTF(1, (CE_CONT, "!%s%d: %s: called at time:%d",
		drv_name, __func__, unit, ddi_get_lbolt()));
E 10
I 10
	DPRINTF(1, (CE_CONT, "!%s%d: %s: called at time:%ld",
D 11
		drv_name, unit, __func__, ddi_get_lbolt()));
E 11
I 11
	    drv_name, unit, __func__, ddi_get_lbolt()));
E 11
E 10
E 8

	/*
	 * Common codes after power-up
	 */
	if (pci_config_setup(dip, &conf_handle) != DDI_SUCCESS) {
		cmn_err(CE_WARN, "!%s%d: ddi_regs_map_setup failed",
D 11
			drv_name, unit);
E 11
I 11
		    drv_name, unit);
E 11
		return (DDI_FAILURE);
	}

	/* ensure we can access the registers through IO space. */
D 11
	pci_config_put16(conf_handle, PCI_CONF_COMM, 
		PCI_COMM_IO | PCI_COMM_ME | PCI_COMM_MAE |
			pci_config_get16(conf_handle, PCI_CONF_COMM));
E 11
I 11
	pci_config_put16(conf_handle, PCI_CONF_COMM,
	    PCI_COMM_IO | PCI_COMM_ME | PCI_COMM_MAE |
	    pci_config_get16(conf_handle, PCI_CONF_COMM));
E 11

	/* ensure the pmr status is D0 mode */
	(void) gem_pci_set_power_state(dip, conf_handle, PCI_PMCSR_D0);

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
	ilr = pci_config_get32(conf_handle, PCI_CONF_ILINE);
I 11
#ifdef lint
	ilr = ilr;
#endif
E 11
	DPRINTF(0, (CE_CONT, "!%s%d: ilr 0x%08x", drv_name, unit, ilr));
I 9

	/* ensure D0 mode */
	(void) gem_pci_set_power_state(dip, conf_handle, PCI_PMCSR_D0);
E 9
D 8

	/* Undocumented dances and songs for PCI config registers */
	if (IS_RHINE2_OR_LATER(revid)) {
		/* PCEROPT */
		pci_config_put8(conf_handle, 0x52,
			pci_config_get8(conf_handle, 0x52) | 0x80);
		/* MII On */
		pci_config_put8(conf_handle, 0x53, 
			pci_config_get8(conf_handle, 0x53) | 0x04);
	}
	if (IS_RHINE1(revid) || IS_RHINE3LOM(revid)) {
		pci_config_put8(conf_handle, 0x52,
			pci_config_get8(conf_handle, 0x52) | 0x02);
	}
I 5
	if (IS_VT6107A1_OR_LATER(revid)) {
		/* enable MRM */
		pci_config_put8(conf_handle, 0x52,
			pci_config_get8(conf_handle, 0x52) | 0x08);
	}
E 5

E 8
	pci_config_teardown(&conf_handle);

	/*
D 11
	 * Misc setup for rhine registsers
E 11
I 11
	 * Misc setup for rhine registers
E 11
	 */
	if (gem_pci_regs_map_setup(dip, PCI_ADDR_IO, PCI_ADDR_MASK,
D 10
		&vfe_dev_attr, (caddr_t *)&base, &reg_ha) != DDI_SUCCESS) {
E 10
I 10
D 11
		&vfe_dev_attr, (void *)&base, &reg_ha) != DDI_SUCCESS) {
E 11
I 11
	    &vfe_dev_attr, (void *)&base, &reg_ha) != DDI_SUCCESS) {
E 11
E 10
		goto err;
	}

	/*
	 * we use eeprom autoload function to initialize registers including
	 * mac address
	 */
#ifdef DEBUG_LEVEL
	/* write a dummy address to ensure eeprom autoloading works. */
	for (i = 0; i < ETHERADDRL; i++) {
		ddi_put8(reg_ha, base + PAR + i, i);
	}
#endif
	ddi_put8(reg_ha, base + EECSR,
D 11
			EECSR_AUTOLD | ddi_get8(reg_ha, base + EECSR));
E 11
I 11
	    EECSR_AUTOLD | ddi_get8(reg_ha, base + EECSR));
E 11

	/*
D 4
	 * XXX - Don't access rhine for 10mS.
E 4
I 4
	 * XXX - Don't access rhine nics for 10mS after autoloading.
E 4
	 * Rhine doesn't respond to any PCI transactions
D 4
	 * while it is loading eeprom. On sparc, it caused
	 * a bus error panic. We must wait for 2.5 mS at least.
E 4
I 4
	 * while it is loading eeprom. On sparc platforms, it caused
	 * to panic the system with PCI bus timeout errors.
D 5
	 * We must wait for 2.5 mS at least by experience.
E 5
I 5
	 * We must wait for 2.5 mS at least in experience.
E 5
E 4
	 */
D 11
	drv_usecwait(10000);
D 5

E 5
I 5
#ifdef MAP_MEM
E 5
	/* enable memory mapped I/O */
	/* XXX - reloading eeprom will disable MMIO */
	if (IS_RHINE1_VT86C100A(revid)) {
		ddi_put8(reg_ha, base + CFGA, 
			ddi_get8(reg_ha, base + CFGA) | CFGA_MMIOEN);
	}
	else {
		ddi_put8(reg_ha, base + CFGD,
			ddi_get8(reg_ha, base + CFGD) | CFGD_MMIOEN);
	}                                                        
D 5

E 5
I 5
#endif
E 11
I 11
	delay(drv_usectohz(10000));

E 11
E 5
	/* disable WOL */
	if (IS_RHINE2_OR_LATER(revid)) {
		ddi_put8(reg_ha, base + STICKHW,
D 11
			ddi_get8(reg_ha, base + STICKHW) &
				~(STICKHW_DS1 | STICKHW_DS0));
E 11
I 11
		    ddi_get8(reg_ha, base + STICKHW) &
		    ~(STICKHW_DS1 | STICKHW_DS0));
E 11
D 5
		ddi_put8(reg_ha, base + WOLCR_CLR, WOLCR_LinkOFF);
		ddi_put8(reg_ha, base + WOLCG_CLR, 0xff);
E 5
I 5
		ddi_put8(reg_ha, base + WOLCG_CLR, WOLCG_PMEOVR);
		ddi_put8(reg_ha, base + WOLCR_CLR, 0xff);
		if (revid > 0x83 /* VT6105B0 */) {
			ddi_put8(reg_ha, base + TSTREG_CLR, 0x03);
		}
E 5
		ddi_put8(reg_ha, base + PWRCSR_CLR, 0xff);
I 5
		if (revid > 0x83 /* VT6105B0 */) {
			ddi_put8(reg_ha, base + PWRCSR1_CLR, 0x03);
		}
E 5
	}

	ddi_regs_map_free(&reg_ha);

D 5

E 5
	/* check chip revision and report it */
	for (i = 0, p = vfe_chiptbl; i < CHIPTABLESIZE; i++, p++) {
		if (p->venid == vid && p->devid == did) {
			/* found */
D 11
			cmn_err(CE_CONT,
			"!%s%d: %s (vid: 0x%04x, did: 0x%04x, revid: 0x%02x)",
				drv_name, unit, p->name, vid, did, revid);
E 11
I 11
			cmn_err(CE_CONT, "!%s%d: %s"
			    " (vid: 0x%04x, did: 0x%04x, revid: 0x%02x)",
			    drv_name, unit, p->name, vid, did, revid);
E 11
			break;
		}
	}
	if (i >= CHIPTABLESIZE) {
		/* Not found */
D 5
		cmn_err(CE_WARN,
			"!%s: vfe_attach: wrong PCI venid/devid (0x%x, 0x%x)",
			drv_name, vid, did);
E 5
I 5
		cmn_err(CE_NOTE,
D 11
			"!%s%d: %s: unknown PCI venid/devid (0x%x, 0x%x)",
			drv_name, unit, __func__, vid, did);
E 11
I 11
		    "!%s%d: %s: unknown PCI venid/devid (0x%x, 0x%x)",
		    drv_name, unit, __func__, vid, did);
E 11
E 5
	}

	switch (cmd) {
	case DDI_RESUME:
		return (gem_resume(dip));

	case DDI_ATTACH:
D 4
		/* XXX - memory mapped io doesn't work for sparc platforms */
E 4
I 4
		/* XXX - memory mapped io doesn't work for sparc platforms. */
E 4
		if (gem_pci_regs_map_setup(dip,
D 11
#ifdef MAP_MEM
			PCI_ADDR_MEM32, PCI_ADDR_MASK,
#else
			PCI_ADDR_IO, PCI_ADDR_MASK,
#endif
D 10
			&vfe_dev_attr, (caddr_t *)&base, &reg_ha)
E 10
I 10
			&vfe_dev_attr, (void *)&base, &reg_ha)
E 10
					!= DDI_SUCCESS) {
E 11
I 11
		    PCI_ADDR_IO, PCI_ADDR_MASK,
		    &vfe_dev_attr, (void *)&base, &reg_ha)
		    != DDI_SUCCESS) {
E 11
			goto err;
		}

		/*
D 11
		 * construct gem configration
E 11
I 11
		 * construct gem configuration
E 11
		 */
D 11
		gcp = (struct gem_conf *) kmem_zalloc(sizeof(*gcp), KM_SLEEP);
E 11
I 11
		gcp = kmem_zalloc(sizeof (*gcp), KM_SLEEP);
E 11

		/* name */
D 11
		sprintf(gcp->gc_name, "%s%d", drv_name, unit);
E 11
I 11
		(void) sprintf(gcp->gc_name, "%s%d", drv_name, unit);
E 11

		/* consistency on tx and rx */
D 11
		gcp->gc_tx_buf_align = 
			IS_RHINE2_OR_LATER(revid)
			? (sizeof(uint8_t) - 1)
			: (sizeof(uint32_t) - 1);
E 11
I 11
		gcp->gc_tx_buf_align = IS_RHINE2_OR_LATER(revid)
		    ? (sizeof (uint8_t) - 1)
		    : (sizeof (uint32_t) - 1);
E 11
		/* rhine I supports only a fragment per tx packet */
D 11
		gcp->gc_tx_max_frags = 
			IS_RHINE2_OR_LATER(revid) ? MAXTXFRAGS : 1;
E 11
I 11
		gcp->gc_tx_max_frags =
		    IS_RHINE2_OR_LATER(revid) ? MAXTXFRAGS : 1;
E 11
		gcp->gc_tx_max_descs_per_pkt = gcp->gc_tx_max_frags;
		gcp->gc_tx_desc_unit_shift = 4; /* 16byte */
D 11
		gcp->gc_tx_buf_size  = TX_BUF_SIZE;
E 11
I 11
		gcp->gc_tx_buf_size = TX_BUF_SIZE;
E 11
		gcp->gc_tx_buf_limit = gcp->gc_tx_buf_size;
		gcp->gc_tx_ring_size = TX_RING_SIZE;
D 4
#ifdef notdef
		gcp->gc_tx_ring_limit = gcp->gc_tx_ring_size - 1;
#else
E 4
		gcp->gc_tx_ring_limit = gcp->gc_tx_ring_size;
D 4
#endif
E 4
I 4
D 11

E 4
		gcp->gc_tx_auto_pad  = B_FALSE;
E 11
I 11
		gcp->gc_tx_auto_pad = B_FALSE;
E 11
		gcp->gc_tx_copy_thresh = vfe_tx_copy_thresh;
D 5
#ifdef CONFIG_OO
		gcp->gc_tx_desc_write_oo = B_TRUE;
#else
		gcp->gc_tx_desc_write_oo = B_FALSE;
#endif
E 5
I 5
D 11
		gcp->gc_tx_desc_write_oo =
			(gcp->gc_tx_max_descs_per_pkt == 1) &&
			(TX_RING_SIZE == TX_BUF_SIZE) &&
			(RX_RING_SIZE == RX_BUF_SIZE);
E 11
I 11
#ifndef GEM_CONFIG_TX_DIRECT
		gcp->gc_tx_desc_write_oo = B_TRUE;
#endif
E 11
E 5

D 11
		gcp->gc_rx_buf_align = sizeof(uint32_t) - 1;
E 11
I 11
		gcp->gc_rx_buf_align = sizeof (uint32_t) - 1;
E 11
		gcp->gc_rx_max_frags = 1;
		gcp->gc_rx_desc_unit_shift = 4; /* 16byte */
D 11
		gcp->gc_rx_ring_size = RX_RING_SIZE;
D 9
		gcp->gc_rx_buf_max   = RX_BUF_SIZE;
E 9
I 9
		gcp->gc_rx_buf_max   = min(RX_BUF_SIZE, 255);
E 11
I 11
		gcp->gc_rx_ring_size = RX_BUF_SIZE;
		gcp->gc_rx_buf_max = min(RX_BUF_SIZE, 255);
E 11
E 9
		gcp->gc_rx_copy_thresh = vfe_rx_copy_thresh;

		gcp->gc_io_area_size = 16; /* a dummy tx desc */

		/* map attributes */
D 8
		STRUCT_COPY(gcp->gc_dev_attr, vfe_dev_attr);
		STRUCT_COPY(gcp->gc_buf_attr, vfe_buf_attr);
D 4
		STRUCT_COPY(gcp->gc_desc_attr, vfe_dev_attr);
E 4
I 4
		STRUCT_COPY(gcp->gc_desc_attr, vfe_buf_attr);
E 8
I 8
		gcp->gc_dev_attr = vfe_dev_attr;
		gcp->gc_buf_attr = vfe_buf_attr;
		gcp->gc_desc_attr = vfe_buf_attr;
E 8
E 4

		/* dma attributes */
D 8
		STRUCT_COPY(gcp->gc_dma_attr_desc, vfe_dma_attr_desc);
		STRUCT_COPY(gcp->gc_dma_attr_txbuf, vfe_dma_attr_buf);
E 8
I 8
		gcp->gc_dma_attr_desc = vfe_dma_attr_desc;
		gcp->gc_dma_attr_txbuf = vfe_dma_attr_buf;
E 8
D 11
		gcp->gc_dma_attr_txbuf.dma_attr_align  = gcp->gc_tx_buf_align+1;
E 11
I 11
		gcp->gc_dma_attr_txbuf.dma_attr_align =
		    gcp->gc_tx_buf_align + 1;
E 11
		gcp->gc_dma_attr_txbuf.dma_attr_sgllen = gcp->gc_tx_max_frags;
D 8
		STRUCT_COPY(gcp->gc_dma_attr_rxbuf, vfe_dma_attr_buf);
E 8
I 8
		gcp->gc_dma_attr_rxbuf = vfe_dma_attr_buf;
E 8
D 11
		gcp->gc_dma_attr_rxbuf.dma_attr_align  = gcp->gc_rx_buf_align+1;
E 11
I 11
		gcp->gc_dma_attr_rxbuf.dma_attr_align =
		    gcp->gc_rx_buf_align + 1;
E 11
		gcp->gc_dma_attr_rxbuf.dma_attr_sgllen = gcp->gc_rx_max_frags;


		/* timeout parameters */
		gcp->gc_tx_timeout = GEM_TX_TIMEOUT;
		gcp->gc_tx_timeout_interval = GEM_TX_TIMEOUT_INTERVAL;

		/* flow control */
		gcp->gc_flow_control = FLOW_CONTROL_NONE;
		if (IS_RHINE2_OR_LATER(revid)) {
			/* rx_pause implies symmetric */
			gcp->gc_flow_control = FLOW_CONTROL_RX_PAUSE;
		}

		/* MII timeout parameters */
		gcp->gc_mii_link_watch_interval = GEM_LINK_WATCH_INTERVAL;
		gcp->gc_mii_an_watch_interval = ONESEC/5;
D 11
		gcp->gc_mii_reset_timeout    = MII_RESET_TIMEOUT;
		gcp->gc_mii_an_timeout       = MII_AN_TIMEOUT;
		gcp->gc_mii_an_wait          = 0; /* was (25*ONESEC)/10 */
		gcp->gc_mii_linkdown_timeout = MII_LINKDOWN_TIMEOUT; 
E 11
I 11
		gcp->gc_mii_reset_timeout = MII_RESET_TIMEOUT;
		gcp->gc_mii_an_timeout = MII_AN_TIMEOUT;
D 12
		gcp->gc_mii_an_wait = 0; /* was (25*ONESEC)/10 */
E 12
I 12
		gcp->gc_mii_an_wait = 0;
E 12
		gcp->gc_mii_linkdown_timeout = MII_LINKDOWN_TIMEOUT;
E 11
D 5
		gcp->gc_mii_hw_link_detection = B_FALSE;	/*  mii_auto is turned off */
E 5
I 5
#ifdef CONFIG_MAUTO
		gcp->gc_mii_hw_link_detection = IS_RHINE2_OR_LATER(revid);
#else
		gcp->gc_mii_hw_link_detection = B_FALSE;
#endif
E 5

		/* workaround for DAVICOM PHY */
D 11
		gcp->gc_mii_an_delay        = ONESEC/10;
E 11
I 11
		gcp->gc_mii_an_delay = ONESEC/10;
E 11
		gcp->gc_mii_linkdown_action = MII_ACTION_RSA;
		gcp->gc_mii_linkdown_timeout_action = MII_ACTION_RESET;
D 11
		gcp->gc_mii_dont_reset      = B_FALSE;
E 11
I 11
		gcp->gc_mii_dont_reset = B_FALSE;
E 11

		/* I/O methods */

		/* mac operation */
		gcp->gc_attach_chip = &vfe_attach_chip;
		gcp->gc_reset_chip = &vfe_reset_chip;
D 11
		gcp->gc_init_chip  = &vfe_init_chip;
E 11
I 11
		gcp->gc_init_chip = &vfe_init_chip;
E 11
		gcp->gc_start_chip = &vfe_start_chip;
D 11
		gcp->gc_stop_chip  = &vfe_stop_chip;
E 11
I 11
		gcp->gc_stop_chip = &vfe_stop_chip;
E 11
		gcp->gc_multicast_hash = &vfe_mcast_hash;
		gcp->gc_set_rx_filter = &vfe_set_rx_filter;
		gcp->gc_set_media = &vfe_set_media;
		gcp->gc_get_stats = &vfe_get_stats;
		gcp->gc_interrupt = &vfe_interrupt;

		/* descriptor operation */
		gcp->gc_tx_desc_write = &vfe_tx_desc_write;
		gcp->gc_rx_desc_write = &vfe_rx_desc_write;
D 11
		gcp->gc_tx_start      = &vfe_tx_start;
		gcp->gc_rx_start      = &vfe_rx_start;
E 11
I 11
		gcp->gc_tx_start = &vfe_tx_start;
		gcp->gc_rx_start = &vfe_rx_start;
E 11
		gcp->gc_tx_desc_stat = &vfe_tx_desc_stat;
		gcp->gc_rx_desc_stat = &vfe_rx_desc_stat;
		gcp->gc_tx_desc_init = &vfe_tx_desc_init;
		gcp->gc_rx_desc_init = &vfe_rx_desc_init;
		gcp->gc_tx_desc_clean = &vfe_tx_desc_clean;
		gcp->gc_rx_desc_clean = &vfe_rx_desc_clean;
D 11
		gcp->gc_get_packet    = &gem_get_packet_default;
E 11
I 11
		gcp->gc_get_packet = &gem_get_packet_default;
E 11

		/* mii operations */
D 6
		gcp->gc_mii_init   = &vfe_mii_init;
E 6
I 6
D 11
		gcp->gc_mii_probe  = &vfe_mii_probe;
		gcp->gc_mii_init   = NULL;
E 11
I 11
		gcp->gc_mii_probe = &vfe_mii_probe;
		gcp->gc_mii_init = NULL;
E 11
E 6
		gcp->gc_mii_config = &gem_mii_config_default;
D 11
		gcp->gc_mii_sync   = &vfe_mii_sync;
		gcp->gc_mii_read   = &vfe_mii_read;
		gcp->gc_mii_write  = &vfe_mii_write;
E 11
I 11
		gcp->gc_mii_sync = &vfe_mii_sync;
		gcp->gc_mii_read = &vfe_mii_read;
		gcp->gc_mii_write = &vfe_mii_write;
E 11
		gcp->gc_mii_tune_phy = NULL;

I 12
		/* offload and jumbo frame */
		gcp->gc_max_lso = 0;
		gcp->gc_default_mtu = ETHERMTU;
		gcp->gc_max_mtu =
		    0x7ff - sizeof (struct ether_header) - 4 - ETHERFCSL;
		gcp->gc_min_mtu = ETHERMIN - sizeof (struct ether_header);

E 12
D 11
		lp = (struct vfe_dev *)
			kmem_zalloc(sizeof(struct vfe_dev), KM_SLEEP);
E 11
I 11
		lp = kmem_zalloc(sizeof (struct vfe_dev), KM_SLEEP);
E 11
		lp->revid = revid;
D 5

E 5
I 5
D 6
#ifdef GEM_SOFTINTR
E 6
D 11
		dp = gem_do_attach(dip, 0, gcp, base, &reg_ha, lp, sizeof(*lp));
D 6
#else
E 5
		dp = gem_do_attach(dip, gcp, base, &reg_ha, lp, sizeof(*lp));
D 5

E 5
I 5
#endif
E 6
E 5
		kmem_free(gcp, sizeof(*gcp));
E 11
I 11
		dp = gem_do_attach(dip, 0,
		    gcp, base, &reg_ha, lp, sizeof (*lp));
		kmem_free(gcp, sizeof (*gcp));
E 11
		if (dp == NULL) {
D 6
			goto  err_free_mem;
E 6
I 6
			goto err_free_mem;
E 6
		}

D 11
#ifdef OPT_TX_INTR
		if (IS_RHINE1(lp->revid)) {
			if (ddi_add_softintr(dp->dip,
					DDI_SOFTINT_LOW, &lp->soft_id,
					NULL, NULL,
					(uint_t (*)(caddr_t))&vfe_update_imr,
					(caddr_t)dp) != DDI_SUCCESS) {
				goto  err_free_mem;
			}
		}
#endif
E 11
		return (DDI_SUCCESS);

err_free_mem:
D 11
		kmem_free(lp, sizeof(struct vfe_dev));
E 11
I 11
		kmem_free(lp, sizeof (struct vfe_dev));
E 11
err:
		return (DDI_FAILURE);
	}
	return (DDI_FAILURE);
}

static int
vfedetach(dev_info_t *dip, ddi_detach_cmd_t cmd)
{
D 11
#ifdef OPT_TX_INTR
	struct gem_dev  *dp;
D 7
	gld_mac_info_t  *macinfo;
E 7
	struct vfe_dev	*lp;

D 7
#  if GEM_CONFIG_MAC
	dp = (struct gem_dev *) ddi_get_driver_private(dip);
#  else
	macinfo = (gld_mac_info_t *) ddi_get_driver_private(dip);
	dp = (struct gem_dev *) macinfo->gldm_private;
#  endif
E 7
I 7
D 9
	dp = GET_DEV(dip);
E 9
I 9
	dp = GEM_GET_DEV(dip);
E 9
E 7
	lp = (struct vfe_dev *) dp->private;
#endif
E 11
	switch (cmd) {
	case DDI_DETACH:
D 11
#ifdef OPT_TX_INTR
		if (IS_RHINE1(lp->revid)) {
			ddi_remove_softintr(lp->soft_id);
		}
#endif
E 11
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
I 11
#ifdef GEM_CONFIG_GLDv3
GEM_STREAM_OPS(vfe_ops, vfeattach, vfedetach);
#else
E 11
static	struct module_info vfeminfo = {
	0,			/* mi_idnum */
	"vfe",			/* mi_idname */
	0,			/* mi_minpsz */
D 6
	ETHERMTU,		/* mi_maxpsz */
E 6
I 6
	INFPSZ,			/* mi_maxpsz */
E 6
D 5
	TX_BUF_SIZE * ETHERMAX,	/* mi_hiwat */
E 5
I 5
	64 * 1024,		/* mi_hiwat */
E 5
	1,			/* mi_lowat */
};

static	struct qinit vferinit = {
	(int (*)()) NULL,	/* qi_putp */
	gem_rsrv,		/* qi_srvp */
	gem_open,		/* qi_qopen */
	gem_close,		/* qi_qclose */
	(int (*)()) NULL,	/* qi_qadmin */
	&vfeminfo,		/* qi_minfo */
	NULL			/* qi_mstat */
};

static	struct qinit vfewinit = {
	gem_wput,		/* qi_putp */
	gem_wsrv,		/* qi_srvp */
	(int (*)()) NULL,	/* qi_qopen */
	(int (*)()) NULL,	/* qi_qclose */
	(int (*)()) NULL,	/* qi_qadmin */
	&vfeminfo,		/* qi_minfo */
	NULL			/* qi_mstat */
};

static struct streamtab	vfe_info = {
	&vferinit,	/* st_rdinit */
	&vfewinit,	/* st_wrinit */
	NULL,		/* st_muxrinit */
	NULL		/* st_muxwrinit */
};

static	struct cb_ops cb_vfe_ops = {
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
	&vfe_info,	/* cb_stream */
	D_MP,		/* cb_flag */
D 8
#ifdef notdef
E 8
I 8
D 11
#ifdef NEVER
E 8
	CB_REV,		/* cb_rev */
	nodev,		/* cb_aread */
	nodev,		/* cb_awrite */
#endif
E 11
};

static	struct dev_ops vfe_ops = {
	DEVO_REV,	/* devo_rev */
	0,		/* devo_refcnt */
	gem_getinfo,	/* devo_getinfo */
	nulldev,	/* devo_identify */
	nulldev,	/* devo_probe */
	vfeattach,	/* devo_attach */
	vfedetach,	/* devo_detach */
	nodev,		/* devo_reset */
	&cb_vfe_ops,	/* devo_cb_ops */
	NULL,		/* devo_bus_ops */
	gem_power	/* devo_power */
};
I 11
#endif /* GEM_CONFIG_GLDv3 */
E 11

static struct modldrv modldrv = {
	&mod_driverops,	/* Type of module.  This one is a driver */
	ident,
	&vfe_ops,	/* driver ops */
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

	DPRINTF(2, (CE_CONT, "!vfe: _init: called"));
	gem_mod_init(&vfe_ops, "vfe");
	status = mod_install(&modlinkage);
	if (status != DDI_SUCCESS) {
		gem_mod_fini(&vfe_ops);
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

	DPRINTF(2, (CE_CONT, "!vfe: _fini: called"));
	status = mod_remove(&modlinkage);
	if (status == DDI_SUCCESS) {
		gem_mod_fini(&vfe_ops);
	}
	return (status);
}

int
_info(struct modinfo *modinfop)
{
	return (mod_info(&modlinkage, modinfop));
}
E 1
