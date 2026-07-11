h42588
s 00009/00040/01591
d D 1.9 11/08/17 23:54:05 mrym 9 8
c 2.6.1 again
e
s 00001/00001/01630
d D 1.8 11/08/14 09:04:56 mrym 8 7
c 2.6.1 with cls bug fix
e
s 00027/00020/01604
d D 1.7 11/08/14 01:13:01 mrym 7 6
c 2.6.1
e
s 00109/00167/01515
d D 1.6 09/02/23 23:07:18 mrym 6 5
c 2.6.0
e
s 00474/00369/01208
d D 1.5 09/02/17 07:00:14 mrym 5 4
c 2.6.0
e
s 00016/00017/01561
d D 1.4 07/02/11 19:21:21 mrym 4 3
c 2.4.0 again
e
s 00086/00048/01492
d D 1.3 07/02/11 18:54:09 mrym 3 2
c 2.4.0
e
s 00007/00002/01533
d D 1.2 06/11/04 18:27:58 mrym 2 1
c 2.4.x
e
s 01535/00000/00000
d D 1.1 06/11/04 14:22:36 mrym 1 0
c date and time created 06/11/04 14:22:36 by mrym
e
u
U
f e 0
t
T
I 1
/*
 *  mtd_gem.c : Myson mtd80x fast ethernet MAC driver for Solaris
 *
D 3
 * Copyright (c) 2006 Masayuki Murayama.  All rights reserved.
E 3
I 3
D 5
 * Copyright (c) 2006,2007 Masayuki Murayama.  All rights reserved.
E 3
 * 
E 5
I 5
D 7
 * Copyright (c) 2006-2009 Masayuki Murayama.  All rights reserved.
E 7
I 7
 * Copyright (c) 2006-2011 Masayuki Murayama.  All rights reserved.
E 7
 *
E 5
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
D 5
 * 
E 5
I 5
 *
E 5
 * 1. Redistributions of source code must retain the above copyright notice,
D 5
 *    this list of conditions and the following disclaimer. 
 * 
E 5
I 5
 *    this list of conditions and the following disclaimer.
 *
E 5
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
D 5
 *    and/or other materials provided with the distribution. 
 * 
E 5
I 5
 *    and/or other materials provided with the distribution.
 *
E 5
 * 3. Neither the name of the author nor the names of its contributors may be
 *    used to endorse or promote products derived from this software without
D 5
 *    specific prior written permission. 
 * 
E 5
I 5
 *    specific prior written permission.
 *
E 5
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
D 5
#pragma	ident	"%W% %E%"
E 5
I 5
#pragma	ident	"%Z%%M% %I%     %E%"
E 5

/*
D 5
 CHANGE LOG:
  03/23/2006  dditypes.h added, ddi_impledefs.h removed

E 5
I 5
 * CHANGE LOG:
 *  03/23/2006  dditypes.h added, ddi_impledefs.h removed
I 6
 *  02/21/2009  nicdrv passed
E 6
 *
E 5
 */

/*
D 5
 TODO:
E 5
I 5
 * TODO:
E 5
 */

/*
 * System Header files.
 */
#include <sys/types.h>
#include <sys/conf.h>
#include <sys/debug.h>
D 5
#include <sys/stropts.h>
#include <sys/stream.h>
#include <sys/strlog.h>
E 5
#include <sys/kmem.h>
D 5
#include <sys/stat.h>
#include <sys/kstat.h>
#include <sys/vtrace.h>
#include <sys/dlpi.h>
#include <sys/strsun.h>
#include <sys/ethernet.h>
E 5
#include <sys/modctl.h>
#include <sys/errno.h>
D 5
#include <sys/dditypes.h>
E 5
#include <sys/ddi.h>
#include <sys/sunddi.h>
D 5

E 5
#include <sys/byteorder.h>
D 5

E 5
I 5
#include <sys/ethernet.h>
E 5
#include <sys/pci.h>
D 5
#include "mii.h"
E 5
I 5

#include "gem_mii.h"
E 5
#include "gem.h"
#include "mtd800reg.h"

char	ident[] = "Myson mtd80x driver v" VERSION;

/* Debugging support */
#ifdef DEBUG_LEVEL
static int mtd_debug = DEBUG_LEVEL;
D 5
# if DEBUG_LEVEL > 4
#    define	CONS	"^"
#  else
#    define	CONS	"!"
#  endif
#define	DPRINTF(n, args)	if (mtd_debug>(n)) cmn_err args
E 5
I 5
#if DEBUG_LEVEL > 4
#define	CONS	"^"
E 5
#else
#define	CONS	"!"
I 5
#endif
#define	DPRINTF(n, args)	if (mtd_debug > (n)) cmn_err args
#else
#define	CONS	"!"
E 5
#define	DPRINTF(n, args)
#endif

/*
 * Useful macros and typedefs
 */
#define	ONESEC			(drv_usectohz(1*1000000))
D 3

E 3
#define	ROUNDUP2(x, a)		(((x) + (a) - 1) & ~((a) - 1))
I 2
D 3
#ifdef GEM_GCC_RUNTIME
#define	STRUCT_COPY(a, b)	(a) = (b)
#else
E 2
#define	STRUCT_COPY(a, b)	bcopy(&(b), &(a), sizeof(a))
I 2
#endif
E 3
E 2

D 3
#if defined(sun4u)
# define LE16(x)	ddi_swap16(x)
# define LE32(x)	ddi_swap32(x)
# define LE64(x)	ddi_swap64(x)
#else
E 3
I 3
D 5
#if defined(i86pc)
E 3
# define LE16(x)	(x)
# define LE32(x)	(x)
# define LE64(x)	(x)
I 3
#else
# define LE16(x)	ddi_swap16(x)
# define LE32(x)	ddi_swap32(x)
# define LE64(x)	ddi_swap64(x)
E 3
#endif

E 5
#ifdef MAP_MEM
D 6
#define	FLSHB(dp, reg)	INB(dp, reg)
#define	FLSHW(dp, reg)	INW(dp, reg)
#define	FLSHL(dp, reg)	INL(dp, reg)
E 6
I 6
#define	FLSHB(dp, reg)	(void) INB(dp, reg)
#define	FLSHW(dp, reg)	(void) INW(dp, reg)
#define	FLSHL(dp, reg)	(void) INL(dp, reg)
E 6
#else
#define	FLSHB(dp, reg)
#define	FLSHW(dp, reg)
#define	FLSHL(dp, reg)
#endif

#define	READ_RXTX_CFG(rc, tc) { \
	uint32_t	val;	\
	val = INL(dp, RCR);	\
D 5
	(rc) = (uint16_t) val;	\
	(tc) = (uint16_t) (val >> 16);	\
E 5
I 5
	(rc) = (uint16_t)val;	\
	(tc) = (uint16_t)(val >> 16);	\
E 5
}

#define	WRITE_RXTX_CFG(rc, tc)	OUTL(dp, RCR, ((tc) << 16) | (rc))

I 5
#define	TXDESC(p)	((struct tx_desc *)(void *)(p))
#define	RXDESC(p)	((struct rx_desc *)(void *)(p))

E 5
/*
 * Our configuration
 */
I 6
#ifndef MAXTXFLAGS
D 7
#define	MAXTXFLAGS	1	/* otherwize it will cause tx timeout */
E 7
I 7
D 9
#define	MAXTXFLAGS	1	/* otherwise it will cause tx timeout */
E 9
I 9
#define	MAXTXFLAGS	min(GEM_MAXTXFRAGS, 8)
E 9
E 7
#endif
E 6
#ifndef	TX_BUF_SIZE
D 3
#define	TX_BUF_SIZE	64
E 3
I 3
D 5
# define TX_BUF_SIZE	128
E 5
I 5
#define	TX_BUF_SIZE	64
E 5
E 3
#endif
#ifndef	TX_RING_SIZE
D 3
#define	TX_RING_SIZE	(TX_BUF_SIZE)
E 3
I 3
D 5
# define TX_RING_SIZE	TX_BUF_SIZE
E 5
I 5
D 6
#define	TX_RING_SIZE	TX_BUF_SIZE
E 6
I 6
#define	TX_RING_SIZE	(TX_BUF_SIZE * (MAXTXFLAGS >= 4 ? 4 : 1))
E 6
E 5
E 3
#endif

#ifndef	RX_BUF_SIZE
D 3
#define	RX_BUF_SIZE	64
E 3
I 3
D 5
# define RX_BUF_SIZE	128
E 5
I 5
#define	RX_BUF_SIZE	256
E 5
E 3
#endif
#ifndef	RX_RING_SIZE
D 3
#define	RX_RING_SIZE	RX_BUF_SIZE
E 3
I 3
D 5
# define RX_RING_SIZE	RX_BUF_SIZE
E 5
I 5
#define	RX_RING_SIZE	RX_BUF_SIZE
E 5
E 3
#endif

D 3
#ifdef notdef
D 2
/* XXX - tx seems unstable in multipile fragment  transmission */
E 2
I 2
/* XXX - mtd803 seems unstable in multipull fragment transmission */
E 3
I 3
D 5
#ifdef NEVER
E 5
I 5
D 6
#ifndef MAXTXFRAGS
E 5
/* XXX - mtd803 seems unstable in multi fragment transmission */
E 3
E 2
D 5
#define	MAXTXFRAGS	GEM_MAXTXFRAGS
#else
E 5
#define	MAXTXFRAGS	1
#endif
I 5

E 6
E 5
#define	MAXRXFRAGS	1

I 5
D 9
#ifdef OPT_TXPOLL
E 9
I 9
#if defined(WA_TXINTR)
/*
 * sometimes INT_TI isn't raised. Use INT_TBU, instead of.
 */
E 9
E 5
#define	OUR_INTR_BITS	\
I 5
D 9
	(INT_LSC | INT_RI | INT_RxErr | INT_RBU | INT_TI | INT_TBU | \
E 9
I 9
	(INT_LSC | INT_RI | INT_RxErr | INT_RBU | INT_TBU | \
E 9
	INT_CNTOVF | INT_ROVF | INT_TUNF | INT_FBE | INT_ANC)
#else
#define	OUR_INTR_BITS	\
E 5
D 4
	(INT_LSC | INT_RI | INT_RxErr | INT_RBU | INT_TI | INT_TBU | \
E 4
I 4
	(INT_LSC | INT_RI | INT_RxErr | INT_RBU | INT_TI | \
E 4
D 5
	 INT_CNTOVF | INT_ROVF | INT_TUNF | INT_FBE)
E 5
I 5
	INT_CNTOVF | INT_ROVF | INT_TUNF | INT_FBE | INT_ANC)
#endif
E 5

static int	mtd_tx_copy_thresh = 256;
static int	mtd_rx_copy_thresh = 256;

/*
 * Chip dependant MAC state
 */
struct mtd_dev {
	/* register shadows */
	uint32_t	our_intr_bits;
	uint16_t	rx_config;
	uint16_t	tx_config;
	uint8_t		mac_addr[ETHERADDRL];
I 6
	uint_t		cls;
E 6
I 5
D 9
#ifdef OPT_TXPOLL
	boolean_t	tx_active;
#endif
E 9
E 5
};

/* ======================================================== */
D 5
 
E 5
I 5

E 5
/* mii operations */
static void  mtd_mii_sync_internal(struct gem_dev *);
static uint16_t  mtd_mii_read_internal(struct gem_dev *, uint_t);
static void mtd_mii_write_internal(struct gem_dev *, uint_t, uint16_t);
/* nic operations */
static int mtd_reset_chip(struct gem_dev *);
static int mtd_init_chip(struct gem_dev *);
static int mtd_start_chip(struct gem_dev *);
static int mtd_stop_chip(struct gem_dev *);
static int mtd_set_media(struct gem_dev *);
static int mtd_set_rx_filter(struct gem_dev *);
static int mtd_get_stats(struct gem_dev *);
static int mtd_attach_chip(struct gem_dev *);

/* descriptor operations */
static int mtd_tx_desc_write(struct gem_dev *dp, int slot,
D 5
		    ddi_dma_cookie_t *dmacookie, int frags, uint32_t intreq);
E 5
I 5
	ddi_dma_cookie_t *dmacookie, int frags, uint64_t intreq);
E 5
static void mtd_tx_start(struct gem_dev *dp, int slot, int frags);
static void mtd_rx_desc_write(struct gem_dev *dp, int slot,
D 5
		    ddi_dma_cookie_t *dmacookie, int frags);
E 5
I 5
	ddi_dma_cookie_t *dmacookie, int frags);
E 5
static void mtd_rx_start(struct gem_dev *dp, int slot, int frags);
static uint_t mtd_tx_desc_stat(struct gem_dev *dp, int slot, int ndesc);
static uint64_t mtd_rx_desc_stat(struct gem_dev *dp, int slot, int ndesc);

static void mtd_tx_desc_init(struct gem_dev *dp, int slot);
static void mtd_rx_desc_init(struct gem_dev *dp, int slot);

/* interrupt handler */
D 5
static u_int mtd_interrupt(struct gem_dev *dp);
E 5
I 5
static uint_t mtd_interrupt(struct gem_dev *dp);
E 5

/* ======================================================== */

/* mapping attributes */
/* Data access requirements. */
static struct ddi_device_acc_attr mtd_dev_attr = {
	DDI_DEVICE_ATTR_V0,
	DDI_STRUCTURE_LE_ACC,
	DDI_STRICTORDER_ACC
};

/* On sparc, the buffers should be native endianness */
static struct ddi_device_acc_attr mtd_buf_attr = {
	DDI_DEVICE_ATTR_V0,
	DDI_NEVERSWAP_ACC,	/* native endianness */
	DDI_STRICTORDER_ACC
};

static ddi_dma_attr_t mtd_dma_attr_buf = {
	DMA_ATTR_V0,		/* dma_attr_version */
	0,			/* dma_attr_addr_lo */
	0xffffffffull,		/* dma_attr_addr_hi */
D 5
	0xffffffffull,		/* dma_attr_count_max */
E 5
I 5
	0x000007ffull,		/* dma_attr_count_max */
E 5
	0, /* patched later */	/* dma_attr_align */
	0,			/* dma_attr_burstsizes */
	1,			/* dma_attr_minxfer */
D 5
	0xffffffffull,		/* dma_attr_maxxfer */
E 5
I 5
	0x000007ffull,		/* dma_attr_maxxfer */
E 5
	0xffffffffull,		/* dma_attr_seg */
	0, /* patched later */	/* dma_attr_sgllen */
	1,			/* dma_attr_granular */
	0			/* dma_attr_flags */
};

static ddi_dma_attr_t mtd_dma_attr_desc = {
	DMA_ATTR_V0,		/* dma_attr_version */
	0,			/* dma_attr_addr_lo */
	0xffffffffull,		/* dma_attr_addr_hi */
	0xffffffffull,		/* dma_attr_count_max */
D 3
	16,			/* dma_attr_align */
E 3
I 3
D 5
	4,			/* dma_attr_align */
E 3
	0xffffffff,		/* dma_attr_burstsizes */
E 5
I 5
	16,			/* dma_attr_align */
	0xffffffffull,		/* dma_attr_burstsizes */
E 5
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
#define	MTD_EEPROM_DELAY(dp)	{ \
	INL(dp, SROM_CR); INL(dp, SROM_CR); \
	INL(dp, SROM_CR); INL(dp, SROM_CR); \
}
#define	EE_CMD_READ	6
#define	EE_CMD_SHIFT	6

static uint16_t
mtd_eeprom_read(struct gem_dev *dp, uint_t offset)
{
	uint32_t	eedi;
	uint16_t	ret;
	int		i;
	uint_t		cs = SROM_DPM | SROM_ECS;

	/* ensure de-assert chip select */
	OUTL(dp, SROM_CR, cs);
	MTD_EEPROM_DELAY(dp);

	/* assert chip select */
	offset |= EE_CMD_READ << EE_CMD_SHIFT;

	for (i = 10; i >= 0; i--) {
		/* send one bit */
		eedi = ((offset >> i) & 1) << SROM_EDI_SHIFT;

		/* send 1 bit */
		OUTL(dp, SROM_CR, cs | eedi);
		MTD_EEPROM_DELAY(dp);
		OUTL(dp, SROM_CR, cs | eedi | SROM_ECK);
		MTD_EEPROM_DELAY(dp);
	}

	OUTL(dp, SROM_CR, cs);

	ret = 0;
	for (i = 0; i < 16; i++) {
		/* Get 1 bit */
		OUTL(dp, SROM_CR, cs);
		MTD_EEPROM_DELAY(dp);
		OUTL(dp, SROM_CR, cs | SROM_ECK);
		MTD_EEPROM_DELAY(dp);
		ret = (ret << 1) | ((INL(dp, SROM_CR) >> SROM_EDO_SHIFT) & 1);
	}

	OUTL(dp, SROM_CR, cs);
	OUTL(dp, SROM_CR, 0);
	MTD_EEPROM_DELAY(dp);

	return (ret);
}

static void
mtd_eeprom_dump(struct gem_dev *dp, int size)
{
	int		i;

	cmn_err(CE_CONT, "!%s: eeprom dump:", dp->name);
	for (i = 0; i < size; i += 4) {
D 5
		cmn_err(CE_CONT, "!0x%02x: 0x%04x 0x%04x 0x%04x 0x%04x", 
			i, mtd_eeprom_read(dp, i), mtd_eeprom_read(dp, i + 1),
			mtd_eeprom_read(dp, i + 2), mtd_eeprom_read(dp, i + 3));
E 5
I 5
		cmn_err(CE_CONT, "!0x%02x: 0x%04x 0x%04x 0x%04x 0x%04x",
		    i, mtd_eeprom_read(dp, i), mtd_eeprom_read(dp, i + 1),
		    mtd_eeprom_read(dp, i + 2), mtd_eeprom_read(dp, i + 3));
E 5
	}
}

I 5
static int
mtd_freeze_tx(struct gem_dev *dp)
{
	int		i;
	uint16_t	rcr;
	uint16_t	tcr;
	int		ret = GEM_SUCCESS;
	struct mtd_dev	*lp = dp->private;

	lp->tx_config &= ~TCR_TE;
	WRITE_RXTX_CFG(lp->rx_config, lp->tx_config);

D 6
	for (i = 0; B_TRUE; i++) {
E 6
I 6
	i = 0;
	while (1) {
E 6
		READ_RXTX_CFG(rcr, tcr);
		if ((tcr & TCR_TE) == 0) {
			break;
		}
D 6
		if (i > 200) {
E 6
I 6
		if (i++ > 200) {
E 6
			cmn_err(CE_WARN, "!%s: %s: failed to stop tx",
			    dp->name, __func__);
			ret = GEM_FAILURE;
			break;
		}
		drv_usecwait(10);
	}

	return (ret);
}

E 5
#ifdef CONFIG_EEPROM_WRITE
#include "mtd_eeprom_wr.c"
#endif

static int
mtd_reset_chip(struct gem_dev *dp)
{
	int		i;
	uint16_t	rcr;
	uint16_t	tcr;
	int		ret = GEM_SUCCESS;
D 5
	struct mtd_dev	*lp = (struct mtd_dev *) dp->private;
E 5
I 5
	struct mtd_dev	*lp = dp->private;
E 5

D 5
	DPRINTF(4, (CE_CONT, "!%s: %s called", dp->name, __func__));
E 5
I 5
	DPRINTF(1, (CE_CONT, "!%s: %s called", dp->name, __func__));
E 5

D 5
	OUTL(dp, IMR, lp->our_intr_bits = 0);
E 5
I 5
	OUTL(dp, IMR, 0);
E 5
	FLSHL(dp, IMR);

	lp->rx_config &= ~RCR_RE;
	lp->tx_config &= ~TCR_TE;
	WRITE_RXTX_CFG(lp->rx_config, lp->tx_config);

D 5
	i = 0;
	while (1) {
E 5
I 5
	for (i = 0; B_TRUE; i++) {
E 5
		READ_RXTX_CFG(rcr, tcr);
		if ((rcr & RCR_RE) == 0 && (tcr & TCR_TE) == 0) {
			break;
		}
D 5
		if (++i > 100) {
			cmn_err(CE_WARN, "%s: %s: failed to stop rx",
				dp->name, __func__);
E 5
I 5
		if (i > 100) {
			cmn_err(CE_WARN, "!%s: %s: failed to stop rx",
			    dp->name, __func__);
E 5
			break;
		}
		drv_usecwait(10);
	}

	/* reset the nic */
	OUTL(dp, BCR, BCR_SWR);
	FLSHL(dp, BCR);
D 5
	for (i = 0;  (INL(dp, BCR) & BCR_SWR) != 0; i++) {
E 5
I 5
D 7
	for (i = 0; (INL(dp, BCR) & BCR_SWR); i++) {
E 7
I 7
	for (i = 0; INL(dp, BCR) & BCR_SWR; i++) {
E 7
E 5
		if (i > 100) {
D 5
			cmn_err(CE_WARN, "%s: %s: timeout",
				dp->name, __func__);
E 5
I 5
			cmn_err(CE_WARN, "!%s: %s: timeout",
			    dp->name, __func__);
E 5
			ret = GEM_FAILURE;
			break;
		}
		drv_usecwait(10);
	}

	/* clear the register shadow for mac_addr */
D 5
	bzero(lp->mac_addr, sizeof(lp->mac_addr));
E 5
I 5
	bzero(lp->mac_addr, sizeof (lp->mac_addr));
E 5

	return (ret);
}

static int
mtd_init_chip(struct gem_dev *dp)
{
	uint32_t	val;
	int		maxdma;
D 5
	struct mtd_dev	*lp = (struct mtd_dev *)dp->private;
E 5
I 5
	struct mtd_dev	*lp = dp->private;
E 5

	DPRINTF(1, (CE_CONT, "!%s: %s called", dp->name, __func__));

D 5
	OUTL(dp, TxLBA, (uint32_t) dp->tx_ring_dma);
	OUTL(dp, RxLBA, (uint32_t) dp->rx_ring_dma);
E 5
I 5
	OUTL(dp, TxLBA, (uint32_t)dp->tx_ring_dma);
	OUTL(dp, RxLBA, (uint32_t)dp->rx_ring_dma);
E 5

I 6
	/*
	 * accept all multicast packets because we cannot change
	 * multicast hash filter after once tx is enabled.
	 */
D 7
	OUTL(dp, MAR + 0, 0xffffffff);
	OUTL(dp, MAR + 4, 0xffffffff);
E 7
I 7
	OUTL(dp, MAR + 0, 0xffffffffU);
	OUTL(dp, MAR + 4, 0xffffffffU);
E 7

E 6
	/* configure the PCI bus bursts and FIFO thresholds */
D 5
#if 0
	OUTL(dp, BCR, 0x38);
	OUTL(dp, BCR, 0x01f8);
#endif
E 5
D 4
	maxdma = max(dp->txmaxdma, 2048)/4;
E 4
	maxdma = dp->txmaxdma;
I 5
D 6
	maxdma = 1024;
E 6
E 5
D 4
	if (maxdma < 4) {
E 4
I 4
	if (maxdma <= 4) {
E 4
		val = BCR_PBL_1;
D 4
	} else if (maxdma < 8) {
E 4
I 4
	} else if (maxdma <= 16) {
E 4
		val = BCR_PBL_4;
D 4
	} else if (maxdma < 16) {
E 4
I 4
	} else if (maxdma <= 32) {
E 4
		val = BCR_PBL_8;
D 4
	} else if (maxdma < 32) {
E 4
I 4
	} else if (maxdma <= 64) {
E 4
		val = BCR_PBL_16;
D 4
	} else if (maxdma < 64) {
E 4
I 4
	} else if (maxdma <= 128) {
E 4
		val = BCR_PBL_32;
D 4
	} else if (maxdma < 128) {
E 4
I 4
	} else if (maxdma <= 256) {
E 4
		val = BCR_PBL_64;
D 4
	} else if (maxdma < 512) {
E 4
I 4
	} else if (maxdma <= 512) {
E 4
		val = BCR_PBL_128;
	} else {
		val = BCR_PBL_512;
	}
D 6
	val |= BCR_RLE | BCR_RME;
E 6
I 6
D 7
	/* XXX - RLE not worked, RME caused performance degraded */
E 7
I 7
	/* XXX - RLE not worked, RME made performance degraded */
E 7
	if (lp->cls != 0) {
		val |= BCR_RLE | BCR_RME;
	}
E 6
	OUTL(dp, BCR, val);

D 4
	maxdma = dp->rxmaxdma/4;
	if (maxdma < 4) {
E 4
I 4
	maxdma = dp->rxmaxdma;
	if (maxdma <= 4) {
E 4
		val = RCR_RPB_1;
D 4
	} else if (maxdma < 8) {
E 4
I 4
	} else if (maxdma <= 16) {
E 4
		val = RCR_RPB_4;
D 4
	} else if (maxdma < 16) {
E 4
I 4
	} else if (maxdma <= 32) {
E 4
		val = RCR_RPB_8;
D 4
	} else if (maxdma < 32) {
E 4
I 4
	} else if (maxdma <= 64) {
E 4
		val = RCR_RPB_16;
D 4
	} else if (maxdma < 64) {
E 4
I 4
	} else if (maxdma <= 128) {
E 4
		val = RCR_RPB_32;
D 4
	} else if (maxdma < 128) {
E 4
I 4
	} else if (maxdma <= 256) {
E 4
		val = RCR_RPB_64;
D 4
	} else if (maxdma < 512) {
E 4
I 4
	} else if (maxdma <= 512) {
E 4
		val = RCR_RPB_128;
	} else {
		val = RCR_RPB_512;
	}
	lp->rx_config |= RCR_RBLEN | val;
D 5
	
E 5
I 5

E 5
	if (dp->txthr <= 32) {
		val = TCR_TFT_32;
	} else if (dp->txthr <= 64) {
		val = TCR_TFT_64;
	} else if (dp->txthr <= 12) {
		val = TCR_TFT_128;
	} else if (dp->txthr <= 256) {
		val = TCR_TFT_256;
	} else if (dp->txthr <= 512) {
		val = TCR_TFT_512;
	} else if (dp->txthr <= 768) {
		val = TCR_TFT_768;
	} else if (dp->txthr <= 1024) {
		val = TCR_TFT_1024;
D 5
	} else { 
		val = TCR_TFT_SF ;
E 5
I 5
	} else {
		val = TCR_TFT_SF;
E 5
	}
	lp->tx_config = val | TCR_FBACK;

I 5
D 6
#ifndef CONFIG_MULTICAST_FILTER
	/* Load Multicast hash table */
	OUTL(dp, MAR + 0, 0xffffffffU);
	OUTL(dp, MAR + 4, 0xffffffffU);
#endif
E 6
E 5
	WRITE_RXTX_CFG(lp->rx_config, lp->tx_config);

I 5
D 9
#ifdef OPT_TXPOLL
	lp->tx_active = B_FALSE;
#endif
E 5
#if 0
D 5
	/* test for timer function */
	DPRINTF(0, (CE_CONT, "%s:%s: flow control addr :%x %x",
		dp->name, __func__, INL(dp, FAR), INL(dp, FAR+4)));
E 5
I 5
	DPRINTF(0, (CE_CONT, "!%s:%s: flow control addr :%x %x",
E 9
I 9
	DPRINTF(10, (CE_CONT, "!%s:%s: flow control addr :%x %x",
E 9
	    dp->name, __func__, INL(dp, FAR), INL(dp, FAR+4)));
E 5
D 9
#endif
E 9

	return (GEM_SUCCESS);
}

D 6
static uint_t
mtd_mcast_hash(struct gem_dev *dp, uint8_t *addr)
{
	return (gem_ether_crc_be(addr, ETHERADDRL) >> 26);
}

E 6
static int
mtd_set_rx_filter(struct gem_dev *dp)
{
	int		i;
	uint16_t	mode;
	uint64_t	hash_tbl;
I 3
	uint8_t		*m;
	uint16_t	rcr, tcr;
E 3
D 5
	struct mtd_dev	*lp = (struct mtd_dev *)dp->private;
E 5
I 5
	struct mtd_dev	*lp = dp->private;
E 5

D 5
	DPRINTF(4, (CE_CONT, "!%s: %s: called", dp->name, __func__));
E 5
I 5
	DPRINTF(1, (CE_CONT, "!%s: %s: called", dp->name, __func__));
E 5

D 3
	mode = 0;
E 3
I 3
D 5
#if DEBUG_LEVEL > 3
E 5
I 5
D 6
#if DEBUG_LEVEL > 4
E 5
	for (i = 0; i < dp->mc_count; i++) {
		cmn_err(CE_CONT,
D 5
		"!%s: adding mcast(%d) %02x:%02x:%02x:%02x:%02x:%02x - %d",
			dp->name, i,
			dp->mc_list[i].addr.ether_addr_octet[0],
			dp->mc_list[i].addr.ether_addr_octet[1],
			dp->mc_list[i].addr.ether_addr_octet[2],
			dp->mc_list[i].addr.ether_addr_octet[3],
			dp->mc_list[i].addr.ether_addr_octet[4],
			dp->mc_list[i].addr.ether_addr_octet[5],
			dp->mc_list[i].hash);
E 5
I 5
		    "!%s: adding mcast(%d) %02x:%02x:%02x:%02x:%02x:%02x - %d",
		    dp->name, i,
		    dp->mc_list[i].addr.ether_addr_octet[0],
		    dp->mc_list[i].addr.ether_addr_octet[1],
		    dp->mc_list[i].addr.ether_addr_octet[2],
		    dp->mc_list[i].addr.ether_addr_octet[3],
		    dp->mc_list[i].addr.ether_addr_octet[4],
		    dp->mc_list[i].addr.ether_addr_octet[5],
		    dp->mc_list[i].hash);
E 5
	}
#endif

E 3
	hash_tbl = 0ull;

E 6
	/* Set Receive filter control register */
	mode = RCR_AB | RCR_AM | RCR_ARP | RCR_ALP | RCR_SEP;

D 3
	if ((dp->rxmode & RXMODE_PROMISC) != 0) {
E 3
I 3
	if ((dp->rxmode & RXMODE_ENABLE) == 0) {
		mode = 0;
D 5
	}
	else if ((dp->rxmode & RXMODE_PROMISC) != 0) {
E 3
		/* accept all physcal address */
E 5
I 5
	} else if (dp->rxmode & RXMODE_PROMISC) {
		/* accept all physcal address and multicast packets */
E 5
		mode |= RCR_PROM;
D 3
		hash_tbl = 0xffffffffffffffffull;
E 3
I 3
D 5
		hash_tbl = ~0ull;
E 3
	}
I 3
#ifdef notdef
E 3
	else if ((dp->rxmode & RXMODE_ALLMULTI) != 0 || dp->mc_count > 32) {
E 5
I 5
D 6
#ifdef CONFIG_MULTICAST_FILTER
	} else if ((dp->rxmode & RXMODE_ALLMULTI) || dp->mc_count > 32) {
E 5
		/* enable all multicast address */
D 3
		hash_tbl = 0xffffffffffffffffull;
E 3
I 3
		hash_tbl = ~0ull;
E 3
D 5
	}
	else {
E 5
I 5
	} else {
E 5
		/* make hash table for selected multicast address */
		for (i = 0; i < dp->mc_count; i++) {
			hash_tbl |= 1ull << dp->mc_list[i].hash;
		}
I 3
D 5
# if 0
		DPRINTF(3, (CE_CONT, "%s: hash_tbl 0x%016llx",
			dp->name, hash_tbl));
E 5
I 5
#if 0
		DPRINTF(3, (CE_CONT, "!%s: hash_tbl 0x%016llx",
		    dp->name, hash_tbl));
E 5
		/* hash_tbl |= 0x0010000000000000ull; - 244.0.0.7 - 52 */
D 5
		DPRINTF(3, (CE_CONT, "%s: hash_tbl 0x%016llx",
			dp->name, hash_tbl));
# endif
E 3
	}
E 5
I 5
		DPRINTF(3, (CE_CONT, "!%s: hash_tbl 0x%016llx",
		    dp->name, hash_tbl));
#endif
E 5
I 3
#else
D 5
	else {
		/* XXX - we cannot update MAR correctly after nic start */
E 5
I 5
	} else {
		/* XXX - we cannot update MAR correctly after nic once starts */
E 5
		hash_tbl = ~0ull;
I 5
#endif /* CONFIG_MULTICAST_FILTER */
E 6
E 5
	}
D 5
#endif
E 5
E 3

	/* Load station address if it has been changed */
D 3
	if (bcmp(dp->cur_addr.ether_addr_octet,
			lp->mac_addr, ETHERADDRL) != 0) {
		uint8_t	*m;
E 3
I 3
	m = dp->cur_addr.ether_addr_octet;
	if (bcmp(m, lp->mac_addr, ETHERADDRL) != 0) {
E 3

		/* update my station address */
D 3
		m = dp->cur_addr.ether_addr_octet;
		bcopy(dp->cur_addr.ether_addr_octet, lp->mac_addr, ETHERADDRL);
E 3
I 3
		bcopy(m, lp->mac_addr, ETHERADDRL);
E 3
		OUTL(dp, PAR + 0,
D 5
			(m[3] << 24) | (m[2] << 16) | (m[1] << 8) | m[0]);
E 5
I 5
D 7
		    (m[3] << 24) | (m[2] << 16) | (m[1] << 8) | m[0]);
E 5
		OUTL(dp, PAR + 4, (m[5] << 8) | m[4]);
E 7
I 7
		    m[3] << 24 | m[2] << 16 | m[1] << 8 | m[0]);
		OUTL(dp, PAR + 4, m[5] << 8 | m[4]);
E 7
I 5
D 6
		DPRINTF(-1, (CE_CONT, "!%s: updating mac_addr", dp->name));
E 6
I 6
		DPRINTF(1, (CE_CONT, "!%s: updating mac_addr", dp->name));
E 6
E 5
	}

I 5
D 6
#ifdef CONFIG_MULTICAST_FILTER
	/* workaround for changing multicast filter, but I dont't know why */
	if (mode != 0) {
		WRITE_RXTX_CFG(lp->rx_config | RCR_PROM, lp->tx_config);
	}

E 5
	/* Load Multicast hash table */
D 5
	OUTL(dp, MAR + 0, (uint32_t) hash_tbl);
E 5
I 5
	OUTL(dp, MAR + 0, (uint32_t)hash_tbl);
E 5
D 3
	OUTL(dp, MAR + 4, (uint32_t) (hash_tbl >> 32));

E 3
I 3
	OUTL(dp, MAR + 4, (uint32_t)(hash_tbl >> 32));
I 5
#endif
E 5
#ifdef notdef
	READ_RXTX_CFG(rcr, tcr);
D 5
	DPRINTF(0, (CE_CONT, "%s: hash_tbl 0x%08x.%08x",
		dp->name, (uint32_t)(hash_tbl >> 32), (uint32_t)hash_tbl));
	DPRINTF(0, (CE_CONT, "%s: MAR 0x%08x.%08x",
		dp->name, INL(dp, MAR+4), INL(dp, MAR)));
	DPRINTF(0, (CE_CONT, "%s: rcr:%b", dp->name, rcr, RCR_BITS));
E 5
I 5
	DPRINTF(0, (CE_CONT, "!%s: hash_tbl 0x%08x.%08x",
	    dp->name, (uint32_t)(hash_tbl >> 32), (uint32_t)hash_tbl));
	DPRINTF(0, (CE_CONT, "!%s: MAR 0x%08x.%08x",
	    dp->name, INL(dp, MAR+4), INL(dp, MAR)));
	DPRINTF(0, (CE_CONT, "!%s: rcr:%b", dp->name, rcr, RCR_BITS));
E 5
#endif
E 6
E 3
D 7
	/* Load new rx filter mode */
E 7
I 7
	/* Load the new rx filter mode */
E 7
D 6
	if ((lp->rx_config & RxFilterMode) != mode) {
D 3
		lp->rx_config &= ~RxFilterMode;
		lp->rx_config |= mode;
E 3
I 3
		lp->rx_config = (lp->rx_config & ~RxFilterMode) | mode;
E 3
		WRITE_RXTX_CFG(lp->rx_config, lp->tx_config);
I 5
		DPRINTF(-1, (CE_CONT, "!%s: updating rcr:%b",
		    dp->name, lp->rx_config, RCR_BITS));
E 5
	}
E 6
I 6
	lp->rx_config = (lp->rx_config & ~RxFilterMode) | mode;
	WRITE_RXTX_CFG(lp->rx_config, lp->tx_config);
I 7

E 7
	DPRINTF(1, (CE_CONT, "!%s: updating rcr:%b",
	    dp->name, lp->rx_config, RCR_BITS));
E 6

	return (GEM_SUCCESS);
}

static int
mtd_start_chip(struct gem_dev *dp)
{
D 5
	struct mtd_dev	*lp = (struct mtd_dev *)dp->private;
E 5
I 5
	struct mtd_dev	*lp = dp->private;
E 5

D 5
	DPRINTF(4, (CE_CONT, "!%s: %s: called", dp->name, __func__));
E 5
I 5
	DPRINTF(1, (CE_CONT, "!%s: %s: called", dp->name, __func__));
E 5

D 5
	/* clear bogus interruts */
	OUTL(dp, ISR, 0xffffffff);
	FLSHL(dp, ISR);

E 5
	/* enable interrupt */
	lp->our_intr_bits = OUR_INTR_BITS;
I 6
D 9
#ifdef WA_MISSED_TXINTR
D 7
	lp->our_intr_bits |=INT_TBU;
E 7
I 7
	lp->our_intr_bits |= INT_TBU;
E 7
#endif
E 9
I 9

E 9
E 6
	if ((dp->misc_flag & GEM_NOINTR) == 0) {
		OUTL(dp, IMR, lp->our_intr_bits);
	}

	/* enable rx and tx */
	lp->rx_config |= RCR_RE;
	lp->tx_config |= TCR_TE;
	WRITE_RXTX_CFG(lp->rx_config, lp->tx_config);

	return (GEM_SUCCESS);
}

static int
mtd_stop_chip(struct gem_dev *dp)
{
	int		i;
	uint16_t	rcr;
	uint16_t	tcr;
	int		ret = GEM_SUCCESS;
D 5
	struct mtd_dev	*lp = (struct mtd_dev *)dp->private;
E 5
I 5
	struct mtd_dev	*lp = dp->private;
E 5

D 5
	DPRINTF(4, (CE_CONT, "!%s: %s: called", dp->name, __func__));
E 5
I 5
	DPRINTF(1, (CE_CONT, "!%s: %s: called", dp->name, __func__));
E 5

	/* disable interrupts */
D 5
	OUTL(dp, IMR, lp->our_intr_bits = 0);
E 5
I 5
	OUTL(dp, IMR, 0);
E 5
	FLSHL(dp, IMR);

D 5
        /* stop rx and tx state machines */
E 5
I 5
	/* stop rx and tx state machines */
E 5
	lp->rx_config &= ~RCR_RE;
	lp->tx_config &= ~TCR_TE;
	WRITE_RXTX_CFG(lp->rx_config, lp->tx_config);
	FLSHW(dp, RCR);

D 5
	i = 0;
	while (1) {
E 5
I 5
	for (i = 0; B_TRUE; i++) {
E 5
		READ_RXTX_CFG(rcr, tcr);
		if ((rcr & RCR_RE) == 0 && (tcr & TCR_TE) == 0) {
			break;
		}
D 5
		if (++i > 200) {
			cmn_err(CE_WARN, "%s: %s: failed to stop rx",
				dp->name, __func__);
E 5
I 5
		if (i > 200) {
			cmn_err(CE_WARN, "!%s: %s: failed to stop rx",
			    dp->name, __func__);
E 5
			ret = GEM_FAILURE;
			break;
		}
		drv_usecwait(10);
	}

	return (ret);
}

static int
mtd_set_media(struct gem_dev *dp)
{
	uint16_t	new_tx;
	uint16_t	new_rx;
D 5
	struct mtd_dev	*lp = (struct mtd_dev *)dp->private;
E 5
I 5
	struct mtd_dev	*lp = dp->private;
E 5
	extern int	gem_speed_value[];

	DPRINTF(0, (CE_CONT, "!%s: %s: %s duplex, %d Mbps",
D 5
		dp->name, __func__,
		dp->full_duplex ? "full" : "half",
		gem_speed_value[dp->speed]));
E 5
I 5
	    dp->name, __func__,
	    dp->full_duplex ? "full" : "half",
	    gem_speed_value[dp->speed]));
E 5

	READ_RXTX_CFG(new_rx, new_tx);
	new_rx &= ~(RCR_RFCEN);
	new_tx &= ~(TCR_FD | TCR_PS | TCR_TFCEN);

	if (dp->full_duplex) {
		new_tx |= TCR_FD;
	}

	if (dp->speed == GEM_SPD_10) {
		new_tx |= TCR_PS;
	}

	/* flow control */
D 5
	switch(dp->flow_control) {
E 5
I 5
	switch (dp->flow_control) {
E 5
	case FLOW_CONTROL_SYMMETRIC:
		new_tx |= TCR_TFCEN;
		new_rx |= RCR_RFCEN;
		break;

	case FLOW_CONTROL_TX_PAUSE:
		new_tx |= TCR_TFCEN;
		break;

	case FLOW_CONTROL_RX_PAUSE:
		new_rx |= RCR_RFCEN;
		break;
	}

	if (lp->tx_config != new_tx || lp->rx_config != new_rx) {
		lp->rx_config = new_rx;
		lp->tx_config = new_tx;
		WRITE_RXTX_CFG(lp->rx_config, lp->tx_config);
	}

	return (GEM_SUCCESS);
}

static int
mtd_get_stats(struct gem_dev *dp)
{
	volatile uint32_t	x;

	dp->stats.crc += INW(dp, TC_CRC);
	dp->stats.missed += INW(dp, TC_MPA);
D 5
	
E 5
I 5

E 5
	x = INL(dp, TC_TSR);

	return (GEM_SUCCESS);
}

/*
 * discriptor  manupiration
 */
static int
mtd_tx_desc_write(struct gem_dev *dp, int slot,
D 5
		ddi_dma_cookie_t *dmacookie, int frags, uint32_t flags)
E 5
I 5
D 6
		ddi_dma_cookie_t *dmacookie, int frags, uint64_t flags)
E 6
I 6
    ddi_dma_cookie_t *dmacookie, int frags, uint64_t flags)
E 6
E 5
{
D 6
	int			i;
I 5
	uint_t			len;
E 5
	uint_t			total;
	ddi_dma_cookie_t	*dcp;
	uint32_t		mark;
I 5
	uint32_t		addr;
E 5
	uint32_t		own;
	struct tx_desc		*tdp;
E 6
I 6
	int		i;
	uint_t		len;
	uint_t		total;
	uint32_t	mark;
	uint32_t	addr;
	uint32_t	own;
	struct tx_desc	*tdp;
	struct mtd_dev	*lp = dp->private;
	int		additional = 0;
	uint_t		tx_ring_size = dp->gc.gc_tx_ring_size;
E 6
D 5
	struct mtd_dev		*lp = (struct mtd_dev *)dp->private;
E 5

#if DEBUG_LEVEL > 3
	cmn_err(CE_CONT,
D 5
		"!%s: time:%d %s seqnum: %d, slot %d, frags: %d flags: %d",
		dp->name, ddi_get_lbolt(), __func__,
		dp->tx_desc_tail, slot, frags, flags);
E 5
I 5
	    "!%s: time:%d %s seqnum: %d, slot %d, frags: %d flags: %lld",
	    dp->name, ddi_get_lbolt(), __func__,
	    dp->tx_desc_tail, slot, frags, flags);
E 5

	for (i = 0; i < frags; i++) {
D 6
		cmn_err(CE_CONT, "!%d: addr: 0x%x, len: 0x%x",
E 6
I 6
		cmn_err(CE_CONT, "!%d: addr: 0x%llx, len: 0x%llx",
E 6
D 5
			i, dmacookie[i].dmac_address, dmacookie[i].dmac_size);
E 5
I 5
		    i, dmacookie[i].dmac_address, dmacookie[i].dmac_size);
E 5
	}
#endif
I 6

E 6
	/*
	 * write tx descriptor in reversed order.
	 */
#if DEBUG_LEVEL > 3
	flags |= GEM_TXFLAG_INTR;
#endif
	total = 0;
D 5
	own   = LE32(TDES0_OWN);
E 5
I 5
	own = LE_32(TDES0_OWN);
E 5
	mark = TDES1_LD | TDES1_CRC | TDES1_PAD;
D 5
	if ((flags & GEM_TXFLAG_INTR) != 0) {
E 5
I 5
	if (flags & GEM_TXFLAG_INTR) {
E 5
		mark |= TDES1_IC;
	}
I 3

E 3
D 6
#if MAXTXFRAGS > 1
E 6
I 6
#if defined(CONFIG_PCI_MRL) && defined(WA_PCI_MRL_HANG)
	/*
D 7
	 * a work around to avoid that received packets will be lost
	 * when we use pci read line or read multiple. Otherwise, we will not
E 7
I 7
	 * XXX - a work around to avoid that received packets will be lost
	 * when we use pci read line or read multiple. Otherwise, we won't
E 7
	 * be able to get the response packets for ping -s HOSTNAME 220.
	 */
	i = frags - 1;
	addr = dmacookie[i].dmac_address + dmacookie[i].dmac_size;
D 8
	if ((dmacookie[i].dmac_size & (lp->cls - 1)) == 6) {
E 8
I 8
	if (lp->cls != 0 && (dmacookie[i].dmac_size & (lp->cls - 1)) == 6) {
E 8
		len = 1;
		dmacookie[i].dmac_size -= len;
		mark |= len;
		addr -= len;
		tdp = &TXDESC(dp->tx_ring)[SLOT(slot + i + 1, tx_ring_size)];
		tdp->tdes2 = LE_32(addr);
		tdp->tdes1 = LE_32(mark);
		tdp->tdes0 = own;

		mark &= ~(TDES1_LD | TDES1_TBS);
		total += len;
		additional = 1;
	}
#endif

#if MAXTXFLAGS != 1
E 6
	for (i = frags - 1; i > 0; i--) {
D 5
		tdp = &((struct tx_desc *)
				dp->tx_ring)[SLOT(slot + i, TX_RING_SIZE)];
		tdp->tdes2 = LE32(dmacookie[i].dmac_address);
		tdp->tdes1 = LE32(mark | dmacookie[i].dmac_size);
E 5
I 5
		len = dmacookie[i].dmac_size;
		mark |= len;
		addr = dmacookie[i].dmac_address;
D 6
		tdp = &TXDESC(dp->tx_ring)[SLOT(slot + i, TX_RING_SIZE)];
E 6
I 6
		tdp = &TXDESC(dp->tx_ring)[SLOT(slot + i, tx_ring_size)];
E 6
		tdp->tdes2 = LE_32(addr);
		tdp->tdes1 = LE_32(mark);
E 5
		tdp->tdes0 = own;

D 5
		mark &= ~TDES1_LD;
		total += dmacookie[i].dmac_size;
E 5
I 5
		mark &= ~(TDES1_LD | TDES1_TBS);
		total += len;
E 5
	}
#endif
D 5
	if ((flags & GEM_TXFLAG_HEAD) != 0) {
E 5
I 5
	if (flags & GEM_TXFLAG_HEAD) {
E 5
		own = 0;
	}
D 5
	tdp = &((struct tx_desc *) dp->tx_ring)[slot];
E 5

D 5
	total += dmacookie[0].dmac_size;
I 3

E 3
	tdp->tdes2 = LE32(dmacookie[0].dmac_address);
	tdp->tdes1 = LE32((mark | TDES1_FD)
		   | (total << TDES1_PKTS_SHIFT)
		   | dmacookie[0].dmac_size);
E 5
I 5
	len = dmacookie[0].dmac_size;
	total += len;
D 6
#ifdef WA_TX_CORRUPTED_PKT
	if (total >= 489 && total < 489+4) {
		total += 4;
		len += 4;
	}
#endif
E 6
I 6

E 6
	addr = dmacookie[0].dmac_address;
D 7
	mark |= TDES1_FD | (total << TDES1_PKTS_SHIFT) | len;
E 7
I 7
	mark |= TDES1_FD | total << TDES1_PKTS_SHIFT | len;
E 7
	tdp = &TXDESC(dp->tx_ring)[slot];
	tdp->tdes2 = LE_32(addr);
	tdp->tdes1 = LE_32(mark);
E 5
	tdp->tdes0 = own;

D 6
	return (frags);
E 6
I 6
	return (frags + additional);
E 6
}

static void
mtd_tx_start(struct gem_dev *dp, int start_slot, int nslot)
{
D 5
	struct mtd_dev		*lp = (struct mtd_dev *)dp->private;
E 5
I 5
	struct mtd_dev	*lp = dp->private;
E 5

	if (nslot > 1) {
		gem_tx_desc_dma_sync(dp,
D 5
				SLOT(start_slot + 1, TX_RING_SIZE),
				nslot - 1, DDI_DMA_SYNC_FORDEV);
E 5
I 5
D 6
		    SLOT(start_slot + 1, TX_RING_SIZE),
E 6
I 6
		    SLOT(start_slot + 1, dp->gc.gc_tx_ring_size),
E 6
		    nslot - 1, DDI_DMA_SYNC_FORDEV);
E 5
	}

D 5
	((struct tx_desc *) dp->tx_ring)[start_slot].tdes0 = LE32(TDES0_OWN);
E 5
I 5
	TXDESC(dp->tx_ring)[start_slot].tdes0 = LE_32(TDES0_OWN);
E 5
	gem_tx_desc_dma_sync(dp, start_slot, 1, DDI_DMA_SYNC_FORDEV);

	/*
	 * Let the Transmit Buffer Manager Fill state machine active.
	 */
D 5
	if (dp->mac_active) {
E 5
I 5
D 9
#ifdef OPT_TXPOLL
	if (!lp->tx_active) {
E 5
		OUTL(dp, TxPDR, 0);
I 5
		lp->tx_active = B_TRUE;
E 5
	}
I 5
#else
E 9
	OUTL(dp, TxPDR, 0);
D 9
#endif
E 9
E 5
}

static void
mtd_rx_desc_write(struct gem_dev *dp, int slot,
D 5
	    ddi_dma_cookie_t *dmacookie, int frags)
E 5
I 5
    ddi_dma_cookie_t *dmacookie, int frags)
E 5
{
I 5
	uint32_t	addr;
	uint32_t	size;
E 5
	struct rx_desc	*rdp;
#if DEBUG_LEVEL > 3
	int		i;

	ASSERT(frags == 1);

	cmn_err(CE_CONT,
D 5
		"!%s: %s seqnum: %d, slot %d, frags: %d",
		dp->name, __func__, dp->rx_active_tail, slot, frags);
E 5
I 5
	    "!%s: %s seqnum: %d, slot %d, frags: %d",
	    dp->name, __func__, dp->rx_active_tail, slot, frags);
E 5
	for (i = 0; i < frags; i++) {
		cmn_err(CE_CONT, "!  frag: %d addr: 0x%x, len: 0x%x",
D 5
			i, dmacookie[i].dmac_address, dmacookie[i].dmac_size);
E 5
I 5
		    i, dmacookie[i].dmac_address, dmacookie[i].dmac_size);
E 5
	}
#endif
D 5
	/* for the last slot of the packet */
	rdp = &((struct rx_desc *) dp->rx_ring)[slot];
E 5
I 5
	rdp = &RXDESC(dp->rx_ring)[slot];
E 5

D 5
	rdp->rdes2 = LE32(dmacookie->dmac_address);
	rdp->rdes1 = LE32(dmacookie->dmac_size);
	rdp->rdes0 = LE32(RDES0_OWN);
E 5
I 5
	addr = dmacookie->dmac_address;
	size = dmacookie->dmac_size;
	rdp->rdes2 = LE_32(addr);
	rdp->rdes1 = LE_32(size);
	rdp->rdes0 = LE_32(RDES0_OWN);
E 5
}

static uint_t
mtd_tx_desc_stat(struct gem_dev *dp, int slot, int ndesc)
{
	struct tx_desc	*tdp;
	uint32_t	status;
	int		i;
	int		cols;
I 9
	struct mtd_dev	*lp = dp->private;
E 9
D 6
#ifdef DEBUG_LEVEL
D 5
	struct mtd_dev	*lp = (struct mtd_dev *) dp->private;
E 5
I 5
	struct mtd_dev	*lp = dp->private;
E 5
	clock_t		delay;
E 6
I 6

	/* check status of the last descriptor */
#if MAXTXFLAGS == 1
	tdp = &TXDESC(dp->tx_ring)[SLOT(slot, dp->gc.gc_tx_ring_size)];
#else
	tdp = &TXDESC(dp->tx_ring)[SLOT(slot + ndesc - 1,
	    dp->gc.gc_tx_ring_size)];
E 6
#endif
D 6
	/* check status of the first descriptor */
D 3
	tdp = &((struct tx_desc *)dp->tx_ring)[SLOT(slot, TX_RING_SIZE)];

E 3
I 3
D 5
	tdp = &((struct tx_desc *) dp->tx_ring)[SLOT(slot, TX_RING_SIZE)];
E 3
	status = LE32(tdp->tdes0);
E 5
I 5
	tdp = &TXDESC(dp->tx_ring)[slot];
E 6
I 6

E 6
	status = tdp->tdes0;
	status = LE_32(status);
E 5

D 3
	DPRINTF(2, (CE_CONT,
		"!%s: time:%d %s: slot:%d, status:0x%b",
		dp->name, ddi_get_lbolt(), __func__, slot, status, TDS_BITS));

E 3
I 3
#ifdef NEVER
D 5
	if (ndesc > 1) for (i = 0; i < ndesc; i++) {
		tdp = &((struct tx_desc *) dp->tx_ring)
					[SLOT(slot + i, TX_RING_SIZE)];
		DPRINTF(-1, (CE_CONT,
		"!%s: time:%d %s: slot:%d+%d, status:0x%b, ctrl:0x%x",
		dp->name, ddi_get_lbolt(), __func__, slot, i,
		LE32(tdp->tdes0), TDS_BITS, LE32(tdp->tdes1)));
E 5
I 5
	if (ndesc > 1) {
		for (i = 0; i < ndesc; i++) {
D 6
			tdp = &TX_DESC(dp->tx_ring)[
			    SLOT(slot + i, TX_RING_SIZE)];
E 6
I 6
			tdp = &TXDESC(dp->tx_ring)[
			    SLOT(slot + i, dp->gc.gc_tx_ring_size)];
E 6
			DPRINTF(-1, (CE_CONT,
			    "!%s: time:%d %s:"
D 6
			    " slot:%d+%d, status:0x%b, ctrl:0x%x",
E 6
I 6
			    " slot:%d+%d, status:0x%b, ctrl:0x%b",
E 6
			    dp->name, ddi_get_lbolt(), __func__,
			    slot, i,
D 6
			    LE_32(tdp->tdes0), TDS_BITS, LE_32(tdp->tdes1)));
E 6
I 6
			    LE_32(tdp->tdes0), TDS_BITS,
			    LE_32(tdp->tdes1), TDES1_BITS));
E 6
		}
E 5
	}
#endif
E 3
D 5
	if ((status & TDES0_OWN) != 0) {
E 5
I 5
	if (status & TDES0_OWN) {
E 5
		/*
		 * not yet transmitted
		 */
I 5
D 6
#ifdef WA_TXHANG
		if (dp->mac_active) {
			clock_t		now = ddi_get_lbolt();
			uint16_t	tcr;

			/* stop tx */
			tcr = INW(dp, TCR);
			mtd_freeze_tx(dp);

			/* read current tx desc again */
			gem_tx_desc_dma_sync(dp, slot, 1,
			    DDI_DMA_SYNC_FORKERNEL);
			status = tdp->tdes0;
			status = LE_32(status);

			/* Have halted */
			if (status & TDES0_OWN) {
				DPRINTF(-1, (CE_CONT,
				    "!%s: %s: tx hang, tcr:%04x",
				    dp->name, __func__, tcr));

				OUTL(dp, TxLBA,
				    dp->tx_ring_dma +
				    slot*sizeof (struct tx_desc));
			}

			lp->tx_config |= TCR_TE;
			WRITE_RXTX_CFG(lp->rx_config, lp->tx_config);

			OUTL(dp, TxPDR, 0);
		}
#endif
E 6
E 5
		return (0);
	}

	/*
	 *  collect statictics
	 */
D 5
	if ((status & (TDES0_ABORT | TDES0_CSL |
			TDES0_LC | TDES0_EC | TDES0_HF)) != 0) {
E 5
I 5
D 7
	if (status & (TDES0_ABORT | TDES0_CSL |
	    TDES0_LC | TDES0_EC | TDES0_HF)) {
E 7
I 7
	if (status &
	    (TDES0_ABORT | TDES0_CSL | TDES0_LC | TDES0_EC | TDES0_HF)) {
E 7
E 5

		/* failed to transmit the packet */

		DPRINTF(2, (CE_CONT, "!%s: Transmit error, Tx status %b",
D 5
			       dp->name, status, TDS_BITS));
E 5
I 5
		    dp->name, status, TDS_BITS));
E 5

		dp->stats.errxmt++;

D 5
		if ((status & TDES0_CSL) != 0) {
E 5
I 5
		if (status & TDES0_CSL) {
E 5
			dp->stats.nocarrier++;
D 5
		}
		if ((status & TDES0_LC) != 0) {
E 5
I 5
		} else if (status & TDES0_LC) {
E 5
			dp->stats.xmtlatecoll++;
I 5
		} else if ((!dp->full_duplex) && (status & TDES0_NCR) == 16) {
			dp->stats.excoll++;
			dp->stats.collisions += 16;
E 5
		}
D 5

		if (!dp->full_duplex) {
			if (status & TDES0_NCR == 16) {
				dp->stats.excoll++;
				dp->stats.collisions += 16;
			}
		}
	}
	else if (!dp->full_duplex) {
E 5
I 5
	} else if (!dp->full_duplex) {
E 5
D 7
		/* half duplex: update collision counters */
E 7
I 7
		/* update collision counters in half duplex mode */
E 7
		cols = status & TDES0_NCR;

		if (cols > 0) {
			if (cols == 1) {
				dp->stats.first_coll++;
			} else /* (cols > 1) */ {
				dp->stats.multi_coll++;
			}
			dp->stats.collisions += cols;
D 5
		}
		else if ((status & TDES0_DFR) != 0) {
E 5
I 5
		} else if (status & TDES0_DFR) {
E 5
			dp->stats.defer++;
		}
	}

	return (GEM_TX_DONE);
}

static uint64_t
mtd_rx_desc_stat(struct gem_dev *dp, int slot, int ndesc)
{
	struct rx_desc		*rdp;
	uint_t			len;
	uint_t			flag;
	uint32_t		status;

D 5
	flag = GEM_RX_DONE;
E 5
I 5
	rdp = &RXDESC(dp->rx_ring)[slot];
E 5

D 5
	rdp = &((struct rx_desc *)dp->rx_ring)[slot];
E 5
I 5
	status = rdp->rdes0;
	status = LE_32(status);
E 5

D 5
	status = LE32(rdp->rdes0);

E 5
	DPRINTF(2, (CE_CONT,
D 5
		"!%s: time:%d %s: slot:%d, status:0x%b",
		dp->name, ddi_get_lbolt(), __func__,
		slot, status, RDS_BITS));
E 5
I 5
	    "!%s: time:%d %s: slot:%d, status:0x%b",
	    dp->name, ddi_get_lbolt(), __func__,
	    slot, status, RDS_BITS));
E 5

D 5
	if ((status & RDES0_OWN) != 0) {
E 5
I 5
	if (status & RDES0_OWN) {
E 5
		/*
		 * No more received packets because
		 * this buffer is owned by NIC.
		 */
		return (0);
	}

D 5

E 5
#define	RX_ERR_BITS \
	(RDS_COLON | RDS_NIBON | RDS_OVRUN | RDS_MIIER | \
D 5
	 RDS_LIMIT | RDS_SHORT | RDS_ABORT | RDS_CRCOK | RDS_DESCS)
E 5
I 5
	RDS_LIMIT | RDS_SHORT | RDS_ABORT | RDS_CRCOK | RDS_DESCS)
E 5

D 5
	if ((status & (RDES0_FSD | RDES0_LSD | RDES0_ES)) != 
					(RDES0_FSD | RDES0_LSD)) {
E 5
I 5
	if ((status & (RDES0_FSD | RDES0_LSD | RDES0_ES))
	    != (RDES0_FSD | RDES0_LSD)) {
E 5
		/*
		 * we received a packet with error.
		 */
		DPRINTF(0, (CE_CONT, "!%s: Corrupted packet "
D 5
			"received, buffer status: %b",
			dp->name, status, RDS_BITS));
E 5
I 5
		    "received, buffer status: %b",
		    dp->name, status, RDS_BITS));
E 5

		/* collect statistics information */
		dp->stats.errrcv++;

D 5
		if ((status & RDES0_LONG) != 0 ||
		    (status & (RDES0_FSD | RDES0_LSD))
						== RDES0_FSD) {
E 5
I 5
		if ((status & RDES0_LONG) ||
		    (status & (RDES0_FSD | RDES0_LSD)) == RDES0_FSD) {
E 5
			dp->stats.frame_too_long++;
D 5
		}
		if ((status & RDES0_RUNT) != 0) {
E 5
I 5
		} else if (status & RDES0_RUNT) {
E 5
			dp->stats.runt++;
D 5
		}
		if ((status & (RDES0_FAE | RDES0_RXER)) != 0) {
E 5
I 5
		} else if (status & (RDES0_FAE | RDES0_RXER)) {
E 5
			dp->stats.frame++;
D 5
		}
		if ((status & RDES0_CRC) != 0) {
E 5
I 5
		} else if (status & RDES0_CRC) {
E 5
#ifdef notdef
			dp->stats.crc++;
I 5
#else
			/* EMPTY */
E 5
#endif
		}

D 5
		return (flag | GEM_RX_ERR);
E 5
I 5
		return (GEM_RX_DONE | GEM_RX_ERR);
E 5
	}

	/*
D 5
	 * this packet was received without errors 
E 5
I 5
	 * this packet was received without errors
E 5
	 */
	len = (status & RDES0_FLNG) >> RDES0_FLNG_SHIFT;
	if (len - ETHERFCSL > 0) {
		len -= ETHERFCSL;
	}

#ifdef notdef
D 5
	if (1) {
		int	i;
		uint8_t	*bp = dp->rx_buf_head->rxb_buf;
E 5
I 5
{
	int	i;
	uint8_t	*bp = dp->rx_buf_head->rxb_buf;
E 5

D 5
		cmn_err(CE_CONT, "!%s: len:%d", dp->name, len);
E 5
I 5
	cmn_err(CE_CONT, "!%s: len:%d", dp->name, len);
E 5

D 5
		for (i = 0; i < 60; i += 10) {
			cmn_err(CE_CONT,
			"!%02x %02x %02x %02x %02x %02x %02x %02x %02x %02x",
			bp[0], bp[1], bp[2], bp[3], bp[4],
			bp[5], bp[6], bp[7], bp[8], bp[9]);
		}
		bp += 10;
E 5
I 5
	for (i = 0; i < 60; i += 10) {
		cmn_err(CE_CONT,
		    "!%02x %02x %02x %02x %02x"
		    " %02x %02x %02x %02x %02x",
		    bp[0], bp[1], bp[2], bp[3], bp[4],
		    bp[5], bp[6], bp[7], bp[8], bp[9]);
E 5
	}
I 5
	bp += 10;
}
E 5
#endif
D 5
	return (flag | (len & GEM_RX_LEN));
E 5
I 5
	return (GEM_RX_DONE | (len & GEM_RX_LEN));
E 5
}

static void
mtd_tx_desc_init(struct gem_dev *dp, int slot)
{
	uint32_t	here;
D 5
	struct tx_desc	*tdp;
E 5

D 5
	((struct tx_desc *) dp->tx_ring)[slot].tdes0 = 0;
E 5
I 5
	TXDESC(dp->tx_ring)[slot].tdes0 = 0;
E 5

	/* make a link to this from the previous descriptor */
D 5
	here = ((uint32_t) dp->tx_ring_dma) + sizeof(struct tx_desc)*slot;
E 5
I 5
	here = ((uint32_t)dp->tx_ring_dma) + sizeof (struct tx_desc) * slot;
E 5

D 5
	tdp = &((struct tx_desc *)dp->tx_ring)[SLOT(slot - 1, TX_RING_SIZE)];
	tdp->tdes3 = LE32(here);
E 5
I 5
D 6
	TXDESC(dp->tx_ring)[SLOT(slot - 1, TX_RING_SIZE)].tdes3 = LE_32(here);
E 6
I 6
	TXDESC(dp->tx_ring)[SLOT(slot - 1, dp->gc.gc_tx_ring_size)].tdes3
	    = LE_32(here);
E 6
E 5
}

static void
mtd_rx_desc_init(struct gem_dev *dp, int slot)
{
	uint32_t	here;
D 5
	struct rx_desc	*rdp;
E 5

D 5
	((struct rx_desc *) dp->rx_ring)[slot].rdes0 = 0;
E 5
I 5
	RXDESC(dp->rx_ring)[slot].rdes0 = 0;
E 5

	/* make a link to this from the previous descriptor */
D 5
	here = ((uint32_t) dp->rx_ring_dma) + sizeof(struct tx_desc)*slot;
E 5
I 5
	here = ((uint32_t)dp->rx_ring_dma) + sizeof (struct rx_desc) * slot;
E 5

D 5
	rdp = &((struct rx_desc *)dp->rx_ring)[SLOT(slot - 1, RX_RING_SIZE)];
	rdp->rdes3 = LE32(here);
E 5
I 5
	RXDESC(dp->rx_ring)[SLOT(slot - 1, RX_RING_SIZE)].rdes3 = LE_32(here);
E 5
}

static void
mtd_tx_desc_clean(struct gem_dev *dp, int slot)
{
D 5
	((struct tx_desc *) dp->tx_ring)[slot].tdes0 = 0;
E 5
I 5
	TXDESC(dp->tx_ring)[slot].tdes0 = 0;
E 5
}

static void
mtd_rx_desc_clean(struct gem_dev *dp, int slot)
{
D 5
	((struct rx_desc *) dp->rx_ring)[slot].rdes0 = 0;
E 5
I 5
	RXDESC(dp->rx_ring)[slot].rdes0 = 0;
E 5
}


/*
 * Device depend interrupt handler
 */
D 5
static u_int
E 5
I 5
static uint_t
E 5
mtd_interrupt(struct gem_dev *dp)
{
	uint32_t	intsrc;
	uint_t		flags = 0;
	boolean_t	need_to_reset = B_FALSE;
D 5
	struct mtd_dev	*lp = (struct mtd_dev *) dp->private;
E 5
I 5
	struct mtd_dev	*lp = dp->private;
E 5

D 5
	/* disable interrupts before clearing intsrc.*/
	OUTL(dp, IMR, 0);

E 5
D 2
	/* read reason and clear interrupt */
E 2
I 2
	/* read interrupt reason */
E 2
	intsrc = INL(dp, ISR);

	if ((intsrc & lp->our_intr_bits) == 0) {
D 5
		/* not for us, enable interrupts again */
		if (intsrc != 0) {
			OUTL(dp, ISR, intsrc);	
		}
		OUTL(dp, IMR, lp->our_intr_bits);
E 5
		return (DDI_INTR_UNCLAIMED);
	}

I 5
	DPRINTF(2, (CE_CONT,
	    "!%s: time:%d %s: called: intsrc:0x%b rx_active_head: %d",
	    dp->name, ddi_get_lbolt(), __func__,
	    intsrc, INT_BITS, dp->rx_active_head));

E 5
I 2
D 6
	/* clear the interrupt reason */
E 6
I 6
	/* clear the interrupt reasons */
E 6
I 5
	intsrc &= lp->our_intr_bits;
E 5
E 2
	OUTL(dp, ISR, intsrc);

D 5
	DPRINTF(2, (CE_CONT,
		"!%s: time:%d %s: called: intsrc:0x%b rx_active_head: %d",
		dp->name, ddi_get_lbolt(), __func__,
		intsrc, INT_BITS, dp->rx_active_head));

E 5
	if (!dp->mac_active) {
		/* the device is going to stop */
I 5
		if (intsrc) {
			OUTL(dp, ISR, intsrc);
		}
		lp->our_intr_bits = 0;
		OUTL(dp, IMR, lp->our_intr_bits);
		FLSHL(dp, IMR);
E 5
		return (DDI_INTR_CLAIMED);
	}

D 5
	if ((intsrc & INT_CNTOVF) != 0) {
E 5
I 5
	/* barrier for interrupt state */
	FLSHL(dp, ISR);

	if (intsrc & INT_CNTOVF) {
E 5
		mtd_get_stats(dp);
	}

D 5
	if ((intsrc & (INT_RI | INT_RBU | INT_ROVF | INT_RxErr)) != 0) {
E 5
I 5
	if (intsrc & (INT_RI | INT_RBU | INT_ROVF | INT_RxErr)) {
E 5
		(void) gem_receive(dp);

D 5
		if ((intsrc & INT_ROVF) != 0) {
E 5
I 5
		if (intsrc & INT_ROVF) {
E 5
			dp->stats.overflow++;
			/* restart the nic */
#ifdef TEST_RESTART
			need_to_reset = B_TRUE;
			DPRINTF(0, (CE_NOTE,
D 5
				"%s: %s: rx overflow", dp->name, __func__));
E 5
I 5
			    "!%s: %s: rx overflow", dp->name, __func__));
E 5
#else
			OUTL(dp, RxPDR, 0);
#endif
		}

D 5
		if ((intsrc & INT_RBU) != 0) {
E 5
I 5
		if (intsrc & INT_RBU) {
E 5
			DPRINTF(0, (CE_NOTE,
D 5
				"%s: %s: rx empty", dp->name, __func__));
E 5
I 5
			    "!%s: %s: rx empty", dp->name, __func__));
E 5
			dp->stats.norcvbuf++;
			/* restart the nic */
			OUTL(dp, RxPDR, 0);
		}
	}

D 5
	if ((intsrc & (INT_TI | INT_TBU)) != 0) {
E 5
I 5
	if (intsrc & (INT_TI | INT_TBU)) {
D 9
#ifdef OPT_TXPOLL
		if (intsrc & INT_TBU) {
			mutex_enter(&dp->xmitlock);
			lp->tx_active = B_FALSE;
			mutex_exit(&dp->xmitlock);
		}
#endif
E 9
E 5
		/* need to relaim tx buffers */
		if (gem_tx_done(dp)) {
			flags |= INTR_RESTART_TX;
		}
I 5
D 9
#ifdef OPT_TXPOLL
		if (intsrc & INT_TBU) {
			mutex_enter(&dp->xmitlock);
			if (dp->tx_desc_head != dp->tx_desc_tail &&
			    !lp->tx_active) {
				OUTL(dp, TxPDR, 0);
				lp->tx_active = B_TRUE;
			}
			mutex_exit(&dp->xmitlock);
		}
#endif
E 9
E 5
	}

D 5
	if ((intsrc & INT_TUNF) != 0) {
E 5
I 5
	if (intsrc & INT_TUNF) {
E 5
		dp->stats.underflow++;
#ifdef TEST_RESTART
		need_to_reset = B_TRUE;
D 5
		DPRINTF(0, (CE_NOTE, "%s: %s: time:%d tx underrun",
			dp->name, __func__, ddi_get_lbolt()));
E 5
I 5
		DPRINTF(0, (CE_NOTE, "!%s: %s: time:%d tx underrun",
		    dp->name, __func__, ddi_get_lbolt()));
E 5
#else
		OUTL(dp, TxPDR, 0);
#endif
	}

D 5
	if ((intsrc & INT_LSC) != 0) {
		DPRINTF(0, (CE_NOTE, "!%s: %s: link changed",
			dp->name, __func__));
		if (gem_mii_link_check(dp) != 0) {
E 5
I 5
	if (intsrc & (INT_LSC | INT_ANC)) {
		DPRINTF(2, (CE_NOTE, "!%s: %s: link status changed",
		    dp->name, __func__));
		if (gem_mii_link_check(dp)) {
E 5
			flags |= INTR_RESTART_TX;
		}
	}

D 5
	if ((intsrc & (INT_ERI | INT_ETI | INT_FBE)) != 0) {
		cmn_err(CE_WARN, "%s: %s: abnormal interrupt: %b",
			dp->name, __func__, intsrc, INT_BITS);
E 5
I 5
	if (intsrc & (INT_ERI | INT_ETI)) {
		cmn_err(CE_NOTE, "!%s: %s: unexpected interrupt: %b",
		    dp->name, __func__, intsrc, INT_BITS);
	}

	if (intsrc & INT_FBE) {
		cmn_err(CE_WARN, "!%s: %s: abnormal interrupt: %b",
		    dp->name, __func__, intsrc, INT_BITS);
E 5
		need_to_reset = B_TRUE;
	}

	if (need_to_reset) {
D 3
		gem_restart_nic(dp, B_TRUE);
E 3
I 3
		gem_restart_nic(dp, GEM_RESTART_KEEP_BUF);
E 3
		flags |= INTR_RESTART_TX;
	}

D 5
	/* enable interrupts again */
	if ((dp->misc_flag & GEM_NOINTR) == 0) {
		OUTL(dp, IMR, lp->our_intr_bits);
	}

E 5
	DPRINTF(5, (CE_CONT, "!%s: %s: return: isr: %b",
D 5
	       dp->name, __func__, intsrc, INT_BITS));
E 5
I 5
	    dp->name, __func__, intsrc, INT_BITS));
E 5

	return (DDI_INTR_CLAIMED | flags);
}

/* ======================================================== */
/*
 * HW depend MII routine
 */
/* ======================================================== */
static void
mtd_mii_sync_internal(struct gem_dev *dp)
{
	/* do nothing */
}

static uint16_t
mtd_mii_read_internal(struct gem_dev *dp, uint_t reg)
{
	uint16_t	val;

	switch (reg) {
D 5
	case MII_CONTROL:  case MII_STATUS:     case MII_PHYIDH:
	case MII_PHYIDL:   case MII_AN_ADVERT:  case MII_AN_LPABLE:
		val = INL(dp, PHYBA + reg*2);
E 5
I 5
	case MII_CONTROL:
	case MII_STATUS:
	case MII_PHYIDH:
	case MII_PHYIDL:
	case MII_AN_ADVERT:
	case MII_AN_LPABLE:
D 7
		val = INL(dp, PHYBA + reg * 2);
E 7
I 7
		val = INL(dp, PHYBA + reg * sizeof (uint16_t));
E 7
E 5
		break;

D 5
	case MII_AN_EXPANSION:
		val = (INL(dp, PHYBA + MII_AN_LPABLE) != 0)
				? MII_AN_EXP_LPCANAN : 0;
		break;

E 5
	default:
D 3
		val = 0xffff;
E 3
I 3
		val = 0;
E 3
		break;
	}

D 5
	DPRINTF(4, (CE_CONT, "%s: %s: reg:%d val:0x%04x",
		dp->name, __func__, reg, val));
E 5
I 5
	DPRINTF(4, (CE_CONT, "!%s: %s: reg:%d val:0x%04x",
	    dp->name, __func__, reg, val));
E 5

	return (val);
}

static void
mtd_mii_write_internal(struct gem_dev *dp, uint_t reg, uint16_t val)
{
	switch (reg) {
D 5
	case MII_CONTROL:  case MII_STATUS:     case MII_PHYIDH:
	case MII_PHYIDL:   case MII_AN_ADVERT:  case MII_AN_LPABLE:
E 5
I 5
	case MII_CONTROL:
	case MII_STATUS:
	case MII_PHYIDH:
	case MII_PHYIDL:
	case MII_AN_ADVERT:
	case MII_AN_LPABLE:
E 5
D 7
		OUTL(dp, PHYBA + reg*2, val);
E 7
I 7
		OUTL(dp, PHYBA + reg * sizeof (uint16_t), val);
E 7
		break;
	}
}

/* ======================================================== */
/*
 * OS depend (device driver) routine
 */
/* ======================================================== */
static int
D 5
mtd_attach_chip(struct gem_dev *dp)	
E 5
I 5
mtd_attach_chip(struct gem_dev *dp)
E 5
{
	int		i;
	uint32_t	val;
	uint8_t		*m;
D 5
	struct mtd_dev	*lp = (struct mtd_dev *) dp->private;
E 5

	DPRINTF(0, (CE_CONT, "!%s: %s: called", dp->name, __func__));
D 5
#if DEBUG_LEVEL > 0
E 5
I 5
#if DEBUG_LEVEL > 4
E 5
	mtd_eeprom_dump(dp, 0x40);
#endif
#ifdef notdef
	/* fix eeprom contents */
	/* enable flow control */
	mtd_control_eeprom(dp, WEN);
	for (i = 0; i < 0x40; i++) {
		mtd_erase_eeprom(dp, i);
		delay(2);
	}
	mtd_control_eeprom(dp, WDS);
	mtd_eeprom_dump(dp, 0x40);
	mtd_control_eeprom(dp, WEN);
	for (i = 0; i < 0x40; i++) {
		mtd_write_eeprom(dp, i, mtd803_eeprom[i]);
		delay(2);
	}
	mtd_control_eeprom(dp, WDS);
	mtd_eeprom_dump(dp, 0x40);
#endif
	m = dp->dev_addr.ether_addr_octet;

D 5
	for (i = 0; i < ETHERADDRL; i +=2) {
E 5
I 5
	for (i = 0; i < ETHERADDRL; i += 2) {
E 5
		val = mtd_eeprom_read(dp, i/2 + 8);
D 5
		m[i    ] = (uint8_t) val;
		m[i + 1] = (uint8_t) (val >> 8);
E 5
I 5
		m[i + 0] = (uint8_t)val;
		m[i + 1] = (uint8_t)(val >> 8);
E 5
	}
D 5
#if 0
E 5
I 5
#ifdef never
E 5
	/* mac address is incorrect */
	if (!gem_get_mac_addr_conf(dp)) {
D 5
		cmn_err(CE_WARN, "%s: %s: cannot read mac address from eeprom",
			dp->name, __func__);
E 5
I 5
		cmn_err(CE_WARN,
		    "!%s: %s: cannot read mac address from eeprom",
		    dp->name, __func__);
E 5
		gem_generate_macaddr(dp, dp->dev_addr.ether_addr_octet);
	}
#endif
	/* rx buffer length must be multiple of 4 */
	dp->rx_buf_len = ROUNDUP2(dp->rx_buf_len, 4);

D 5
	/* clear statistic counter */
E 5
I 5
	/* clear statistic counters */
E 5
	mtd_get_stats(dp);
D 5
	bzero(&dp->stats, sizeof(dp->stats));
E 5
I 5
	bzero(&dp->stats, sizeof (dp->stats));
E 5

I 5
#ifdef GEM_CONFIG_GLDv3
	dp->misc_flag |= GEM_VLAN_SOFT;
#endif
E 5
	return (GEM_SUCCESS);
}

static int
mtdattach(dev_info_t *dip, ddi_attach_cmd_t cmd)
{
	int			unit;
	const char		*drv_name;
	int			i;
	ddi_acc_handle_t	conf_handle;
	uint16_t		vid;
	uint16_t		did;
	uint8_t			rev;
#ifdef DEBUG_LEVEL
	uint32_t		iline;
	uint8_t			latim;
#endif
I 6
	uint8_t			cls;
E 6
	struct gem_dev		*dp;
	struct mtd_dev		*lp;
	void			*base;
	ddi_acc_handle_t	regs_ha;
	struct gem_conf		*gcp;

D 5
	unit     = ddi_get_instance(dip);
E 5
I 5
	unit = ddi_get_instance(dip);
E 5
	drv_name = ddi_driver_name(dip);

	DPRINTF(0, (CE_CONT, "!%s%d: %s: called (%s)",
D 5
		drv_name, unit, __func__, ident));
E 5
I 5
	    drv_name, unit, __func__, ident));
E 5

	/*
	 * Common codes after power-up
	 */
	if (pci_config_setup(dip, &conf_handle) != DDI_SUCCESS) {
D 5
		cmn_err(CE_WARN, "%s%d: ddi_regs_map_setup failed",
			drv_name, unit);
E 5
I 5
		cmn_err(CE_WARN, "!%s%d: ddi_regs_map_setup failed",
		    drv_name, unit);
E 5
		goto err;
	}

D 5
	vid  = pci_config_get16(conf_handle, PCI_CONF_VENID);
	did  = pci_config_get16(conf_handle, PCI_CONF_DEVID);
	rev  = pci_config_get16(conf_handle, PCI_CONF_REVID);
E 5
I 5
	vid = pci_config_get16(conf_handle, PCI_CONF_VENID);
	did = pci_config_get16(conf_handle, PCI_CONF_DEVID);
	rev = pci_config_get16(conf_handle, PCI_CONF_REVID);
E 5
#ifdef DEBUG_LEVEL
D 5
	iline =	pci_config_get32(conf_handle, PCI_CONF_ILINE),
E 5
I 5
	iline =	pci_config_get32(conf_handle, PCI_CONF_ILINE);
E 5
	latim = pci_config_get8(conf_handle, PCI_CONF_LATENCY_TIMER);
#endif
I 6
#ifdef CONFIG_PCI_MRL
	if (pci_config_get8(conf_handle, PCI_CONF_CACHE_LINESZ) == 0) {
		pci_config_put8(conf_handle, PCI_CONF_CACHE_LINESZ, 8);
	}
#else
	pci_config_put8(conf_handle, PCI_CONF_CACHE_LINESZ, 0);
#endif
	cls = pci_config_get8(conf_handle, PCI_CONF_CACHE_LINESZ) * 4;
E 6
	pci_config_put16(conf_handle, PCI_CONF_COMM,
D 5
		PCI_COMM_IO | PCI_COMM_MAE | PCI_COMM_ME |
			pci_config_get16(conf_handle, PCI_CONF_COMM));
E 5
I 5
	    PCI_COMM_IO | PCI_COMM_MAE | PCI_COMM_ME |
	    pci_config_get16(conf_handle, PCI_CONF_COMM));
E 5


	/* ensure D0 mode */
	(void) gem_pci_set_power_state(dip, conf_handle, PCI_PMCSR_D0);

	pci_config_teardown(&conf_handle);

	switch (cmd) {
	case DDI_RESUME:
		return (gem_resume(dip));

	case DDI_ATTACH:

		DPRINTF(0, (CE_CONT,
D 5
			"!%s%d: ilr 0x%08x, latency_timer:0x%02x",
			drv_name, unit, iline, latim));
E 5
I 5
D 6
		    "!%s%d: ilr 0x%08x, latency_timer:0x%02x",
		    drv_name, unit, iline, latim));
E 6
I 6
		    "!%s%d: ilr 0x%08x, latency_timer:0x%02x, "
		    "cache line size:%d double words",
		    drv_name, unit, iline, latim, cls/4));
E 6
E 5
		/*
		 * Map in the device registers.
		 */

		if (gem_pci_regs_map_setup(dip,
#ifdef MAP_MEM
D 5
			PCI_ADDR_MEM32, PCI_ADDR_MASK,
E 5
I 5
		    PCI_ADDR_MEM32, PCI_ADDR_MASK,
E 5
#else
D 5
			PCI_ADDR_IO, PCI_ADDR_MASK,
E 5
I 5
		    PCI_ADDR_IO, PCI_ADDR_MASK,
E 5
#endif
D 5
			&mtd_dev_attr, (caddr_t *)&base, &regs_ha) !=
								DDI_SUCCESS) {
			cmn_err(CE_WARN, "%s%d: ddi_regs_map_setup failed",
				drv_name, unit);
E 5
I 5
		    &mtd_dev_attr, (void *)&base, &regs_ha)
		    != DDI_SUCCESS) {
			cmn_err(CE_WARN, "!%s%d: ddi_regs_map_setup failed",
			    drv_name, unit);
E 5
			goto err;
		}

		/*
		 * construct gem configration
		 */
D 5
		gcp = (struct gem_conf *) kmem_zalloc(sizeof(*gcp), KM_SLEEP);
E 5
I 5
		gcp = kmem_zalloc(sizeof (*gcp), KM_SLEEP);
E 5

I 7
		lp = kmem_zalloc(sizeof (struct mtd_dev), KM_SLEEP);
		lp->cls = cls;

E 7
		/* name */
		sprintf(gcp->gc_name, "%s%d", drv_name, unit);

		/* consistency on tx and rx */
D 5
		gcp->gc_tx_buf_align = sizeof(uint8_t) - 1;
E 5
I 5
D 6
#ifdef WA_TXHANG
E 6
		gcp->gc_tx_buf_align = sizeof (uint32_t) - 1;
I 6
		gcp->gc_tx_max_frags = min(GEM_MAXTXFRAGS, MAXTXFLAGS);
#if defined(CONFIG_PCI_MRL) && defined(WA_PCI_MRL_HANG)
		gcp->gc_tx_max_descs_per_pkt = gcp->gc_tx_max_frags + 1;
E 6
#else
D 6
		gcp->gc_tx_buf_align = sizeof (uint8_t) - 1;
#endif
E 5
		gcp->gc_tx_max_frags = MAXTXFRAGS;
E 6
		gcp->gc_tx_max_descs_per_pkt = gcp->gc_tx_max_frags;
I 6
#endif
E 6
		gcp->gc_tx_desc_unit_shift = 4;
D 5
		gcp->gc_tx_buf_size   = TX_BUF_SIZE;
		gcp->gc_tx_buf_limit  = gcp->gc_tx_buf_size;
		gcp->gc_tx_ring_size  = TX_RING_SIZE;
E 5
I 5
		gcp->gc_tx_buf_size = TX_BUF_SIZE;
D 6
#ifdef WA_TXHANG
		gcp->gc_tx_buf_limit = gcp->gc_tx_buf_size - 1;
#else
E 6
		gcp->gc_tx_buf_limit = gcp->gc_tx_buf_size;
D 6
#endif
E 6
		gcp->gc_tx_ring_size = TX_RING_SIZE;
E 5
		gcp->gc_tx_ring_limit = gcp->gc_tx_ring_size;
D 5
		gcp->gc_tx_auto_pad   = B_TRUE;
E 5
I 5
		gcp->gc_tx_auto_pad = B_TRUE;
E 5
		gcp->gc_tx_copy_thresh = mtd_tx_copy_thresh;
D 5
		gcp->gc_tx_desc_write_oo = B_FALSE;
E 5

D 5
		gcp->gc_rx_buf_align = sizeof(uint32_t) - 1;
E 5
I 5
		gcp->gc_rx_buf_align = sizeof (uint32_t) - 1;
E 5
		gcp->gc_rx_max_frags = 1;
		gcp->gc_rx_desc_unit_shift = 4;
		gcp->gc_rx_ring_size = RX_RING_SIZE;
D 5
		gcp->gc_rx_buf_max   = RX_BUF_SIZE;
E 5
I 5
		gcp->gc_rx_buf_max = RX_BUF_SIZE;
E 5
		gcp->gc_rx_copy_thresh = mtd_rx_copy_thresh;

D 5
		gcp->gc_io_area_size   = 0;
E 5
I 5
		gcp->gc_io_area_size = 0;
E 5

		/* map attributes */
D 3
		STRUCT_COPY(gcp->gc_dev_attr, mtd_dev_attr);
		STRUCT_COPY(gcp->gc_buf_attr, mtd_buf_attr);
		STRUCT_COPY(gcp->gc_desc_attr, mtd_buf_attr);
E 3
I 3
		gcp->gc_dev_attr = mtd_dev_attr;
		gcp->gc_buf_attr = mtd_buf_attr;
		gcp->gc_desc_attr = mtd_buf_attr;
E 3

		/* dma attributes */
D 3
		STRUCT_COPY(gcp->gc_dma_attr_desc, mtd_dma_attr_desc);
E 3
I 3
		gcp->gc_dma_attr_desc = mtd_dma_attr_desc;
E 3

D 3
		STRUCT_COPY(gcp->gc_dma_attr_txbuf, mtd_dma_attr_buf);
E 3
I 3
		gcp->gc_dma_attr_txbuf = mtd_dma_attr_buf;
E 3
		gcp->gc_dma_attr_txbuf.dma_attr_align = gcp->gc_tx_buf_align+1;
		gcp->gc_dma_attr_txbuf.dma_attr_sgllen = gcp->gc_tx_max_frags;

D 3
		STRUCT_COPY(gcp->gc_dma_attr_rxbuf, mtd_dma_attr_buf);
E 3
I 3
		gcp->gc_dma_attr_rxbuf = mtd_dma_attr_buf;
E 3
		gcp->gc_dma_attr_rxbuf.dma_attr_align = gcp->gc_rx_buf_align+1;
		gcp->gc_dma_attr_rxbuf.dma_attr_sgllen = gcp->gc_rx_max_frags;

		/* time out parameters */
D 6
		gcp->gc_tx_timeout = 3*ONESEC;
I 5
#ifdef WA_TXHANG
		gcp->gc_tx_timeout_interval = ONESEC / 50;
#else
E 5
		gcp->gc_tx_timeout_interval = ONESEC;
I 5
#endif
E 6
I 6
		gcp->gc_tx_timeout = GEM_TX_TIMEOUT;
		gcp->gc_tx_timeout_interval = GEM_TX_TIMEOUT_INTERVAL;
E 6
E 5

		/* MII timeout parameters */
		gcp->gc_mii_link_watch_interval = ONESEC;
D 5
		gcp->gc_mii_an_watch_interval   = ONESEC/5;
E 5
I 5
		gcp->gc_mii_an_watch_interval = ONESEC/5;
E 5
		gcp->gc_mii_reset_timeout = MII_RESET_TIMEOUT;	/* 1 sec */
		gcp->gc_mii_an_timeout = MII_AN_TIMEOUT;	/* 5 sec */
		gcp->gc_mii_an_wait = 0;
		gcp->gc_mii_linkdown_timeout = MII_LINKDOWN_TIMEOUT;

		/* setting for general PHY */
		gcp->gc_mii_an_delay = 0;
		gcp->gc_mii_linkdown_action = MII_ACTION_RSA;
		gcp->gc_mii_linkdown_timeout_action = MII_ACTION_RESET;
		gcp->gc_mii_dont_reset = B_FALSE;
		gcp->gc_mii_hw_link_detection = B_TRUE;


		/* I/O methods */

		/* mac operation */
		gcp->gc_attach_chip = &mtd_attach_chip;
		gcp->gc_reset_chip = &mtd_reset_chip;
D 5
		gcp->gc_init_chip  = &mtd_init_chip;
E 5
I 5
		gcp->gc_init_chip = &mtd_init_chip;
E 5
		gcp->gc_start_chip = &mtd_start_chip;
D 5
		gcp->gc_stop_chip  = &mtd_stop_chip;
E 5
I 5
		gcp->gc_stop_chip = &mtd_stop_chip;
E 5
D 6
		gcp->gc_multicast_hash = &mtd_mcast_hash;
E 6
I 6
		gcp->gc_multicast_hash = NULL;
E 6
		gcp->gc_set_rx_filter = &mtd_set_rx_filter;
		gcp->gc_set_media = &mtd_set_media;
		gcp->gc_get_stats = &mtd_get_stats;
		gcp->gc_interrupt = &mtd_interrupt;

		/* descriptor operation */
		gcp->gc_tx_desc_write = &mtd_tx_desc_write;
		gcp->gc_rx_desc_write = &mtd_rx_desc_write;
		gcp->gc_tx_start = &mtd_tx_start;
		gcp->gc_rx_start = NULL;

D 5
		gcp->gc_tx_desc_stat  = &mtd_tx_desc_stat;
		gcp->gc_rx_desc_stat  = &mtd_rx_desc_stat;
		gcp->gc_tx_desc_init  = &mtd_tx_desc_init;
		gcp->gc_rx_desc_init  = &mtd_rx_desc_init;
E 5
I 5
		gcp->gc_tx_desc_stat = &mtd_tx_desc_stat;
		gcp->gc_rx_desc_stat = &mtd_rx_desc_stat;
		gcp->gc_tx_desc_init = &mtd_tx_desc_init;
		gcp->gc_rx_desc_init = &mtd_rx_desc_init;
E 5
		gcp->gc_tx_desc_clean = &mtd_tx_desc_clean;
		gcp->gc_rx_desc_clean = &mtd_rx_desc_clean;

		/* mii operations */
D 5
		gcp->gc_mii_init     = &gem_mii_init_default;
		gcp->gc_mii_config   = &gem_mii_config_default;
		gcp->gc_mii_sync     = &mtd_mii_sync_internal;
		gcp->gc_mii_read     = &mtd_mii_read_internal;
		gcp->gc_mii_write    = &mtd_mii_write_internal;
E 5
I 5
		gcp->gc_mii_probe = &gem_mii_probe_default;
		gcp->gc_mii_init = NULL;
		gcp->gc_mii_config = &gem_mii_config_default;
		gcp->gc_mii_sync = &mtd_mii_sync_internal;
		gcp->gc_mii_read = &mtd_mii_read_internal;
		gcp->gc_mii_write = &mtd_mii_write_internal;
E 5
		gcp->gc_flow_control = FLOW_CONTROL_RX_PAUSE;

D 5
		lp = (struct mtd_dev *)
			kmem_zalloc(sizeof(struct mtd_dev), KM_SLEEP);
E 5
I 5
D 7
		lp = kmem_zalloc(sizeof (struct mtd_dev), KM_SLEEP);
I 6
		lp->cls = cls;
E 7
I 7
		/* offload and jumbo frame */
		gcp->gc_max_lso = 0;
		gcp->gc_max_mtu = 1920;
		gcp->gc_default_mtu = ETHERMTU;
		gcp->gc_min_mtu = ETHERMIN - sizeof (struct ether_header);
E 7
E 6
E 5

D 5
		dp = gem_do_attach(dip, gcp, base, &regs_ha,
			lp, sizeof(*lp));
		kmem_free(gcp, sizeof(*gcp));
E 5
I 5
		dp = gem_do_attach(dip, 0,
		    gcp, base, &regs_ha, lp, sizeof (*lp));
E 5

I 5
		kmem_free(gcp, sizeof (*gcp));

E 5
		if (dp == NULL) {
			goto err_freelp;
		}

		return (DDI_SUCCESS);

err_freelp:
D 5
		kmem_free(lp, sizeof(struct mtd_dev));
E 5
I 5
		kmem_free(lp, sizeof (struct mtd_dev));
E 5
err:
		break;
	}
	return (DDI_FAILURE);
}

static int
mtddetach(dev_info_t *dip, ddi_detach_cmd_t cmd)
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
I 5
#ifdef GEM_CONFIG_GLDv3
GEM_STREAM_OPS(mtd_ops, mtdattach, mtddetach);
#else
E 5
static	struct module_info mtdminfo = {
	0,			/* mi_idnum */
	"mtd",			/* mi_idname */
	0,			/* mi_minpsz */
D 3
	ETHERMTU,		/* mi_maxpsz */
	TX_BUF_SIZE*ETHERMAX,	/* mi_hiwat */
E 3
I 3
	INFPSZ,			/* mi_maxpsz */
	64*1024,		/* mi_hiwat */
E 3
	1,			/* mi_lowat */
};

static	struct qinit mtdrinit = {
	(int (*)()) NULL,	/* qi_putp */
	gem_rsrv,		/* qi_srvp */
	gem_open,		/* qi_qopen */
	gem_close,		/* qi_qclose */
	(int (*)()) NULL,	/* qi_qadmin */
	&mtdminfo,		/* qi_minfo */
	NULL			/* qi_mstat */
};

static	struct qinit mtdwinit = {
	gem_wput,		/* qi_putp */
	gem_wsrv,		/* qi_srvp */
	(int (*)()) NULL,	/* qi_qopen */
	(int (*)()) NULL,	/* qi_qclose */
	(int (*)()) NULL,	/* qi_qadmin */
	&mtdminfo,		/* qi_minfo */
	NULL			/* qi_mstat */
};

static struct streamtab	mtd_info = {
	&mtdrinit,	/* st_rdinit */
	&mtdwinit,	/* st_wrinit */
	NULL,		/* st_muxrinit */
	NULL		/* st_muxwrinit */
};

static	struct cb_ops cb_mtd_ops = {
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
	&mtd_info,	/* cb_stream */
	D_MP,		/* cb_flag */
};

static	struct dev_ops mtd_ops = {
	DEVO_REV,	/* devo_rev */
	0,		/* devo_refcnt */
	gem_getinfo,	/* devo_getinfo */
	nulldev,	/* devo_identify */
	nulldev,	/* devo_probe */
	mtdattach,	/* devo_attach */
	mtddetach,	/* devo_detach */
	nodev,		/* devo_reset */
	&cb_mtd_ops,	/* devo_cb_ops */
	NULL,		/* devo_bus_ops */
	gem_power,	/* devo_power */
};
I 5
#endif /* GEM_CONFIG_GLDv3 */
E 5

static struct modldrv modldrv = {
	&mod_driverops,	/* Type of module.  This one is a driver */
	ident,
	&mtd_ops,	/* driver ops */
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
D 5
	int 	status;
E 5
I 5
	int	status;
E 5

	DPRINTF(2, (CE_CONT, "!mtd: _init: called"));

	gem_mod_init(&mtd_ops, "mtd");
	status = mod_install(&modlinkage);
	if (status != DDI_SUCCESS) {
		gem_mod_fini(&mtd_ops);
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

	DPRINTF(2, (CE_CONT, "!mtd: _fini: called"));
	status = mod_remove(&modlinkage);
	if (status == DDI_SUCCESS) {
		gem_mod_fini(&mtd_ops);
	}
	return (status);
}

int
_info(struct modinfo *modinfop)
{
	return (mod_info(&modlinkage, modinfop));
}
E 1
