h42686
s 00072/00051/01902
d D 1.5 11/09/19 22:31:46 mrym 5 4
c 2.6.2
e
s 00294/00282/01659
d D 1.4 08/10/10 19:14:01 mrym 4 3
c 2.6.1
e
s 00127/00123/01814
d D 1.3 07/09/22 10:36:50 mrym 3 2
c 2.6.0
e
s 00181/00131/01756
d D 1.2 07/09/02 19:13:33 mrym 2 1
c 2.4.0
e
s 01887/00000/00000
d D 1.1 06/09/02 21:48:21 mrym 1 0
c date and time created 06/09/02 21:48:21 by mrym
e
u
U
f e 0
t
T
I 1
/*
 *  ife_gem.c: Intel 8255x 10/100 ethernet controler driver for Solaris
 *
D 4
 * Copyright (c) 2003-2006 Masayuki Murayama.  All rights reserved.
 * 
E 4
I 4
D 5
 * Copyright (c) 2003-2008 Masayuki Murayama.  All rights reserved.
E 5
I 5
 * Copyright (c) 2003-2011 Masayuki Murayama.  All rights reserved.
E 5
 *
E 4
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
D 4
 * 
E 4
I 4
 *
E 4
 * 1. Redistributions of source code must retain the above copyright notice,
D 4
 *    this list of conditions and the following disclaimer. 
 * 
E 4
I 4
 *    this list of conditions and the following disclaimer.
 *
E 4
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
D 4
 *    and/or other materials provided with the distribution. 
 * 
E 4
I 4
 *    and/or other materials provided with the distribution.
 *
E 4
 * 3. Neither the name of the author nor the names of its contributors may be
 *    used to endorse or promote products derived from this software without
D 4
 *    specific prior written permission. 
 * 
E 4
I 4
 *    specific prior written permission.
 *
E 4
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
#pragma ident	"%W% %E%"

/*
 Change log
I 3
09/22/2007 2.6.0 release
E 3

 */

/*
 TODO:
	pci device ID table
	extended TxCB support
	503 support for i82557
	auto-nego
 */

/*
 * System Header files.
 */
#include <sys/types.h>
#include <sys/conf.h>
#include <sys/debug.h>
D 4
#include <sys/stropts.h>
#include <sys/stream.h>
#include <sys/strlog.h>
E 4
#include <sys/kmem.h>
D 4
#include <sys/stat.h>
#include <sys/kstat.h>
#include <sys/vtrace.h>
#include <sys/dlpi.h>
#include <sys/strsun.h>
#include <sys/ethernet.h>
E 4
#include <sys/modctl.h>
#include <sys/errno.h>
D 4
#include <sys/dditypes.h>
E 4
#include <sys/ddi.h>
#include <sys/sunddi.h>
I 3
#include <sys/byteorder.h>
E 3
D 4

E 4
I 4
#include <sys/ethernet.h>
E 4
#include <sys/pci.h>
I 4

E 4
D 3
#include "mii.h"
E 3
I 3
#include "gem_mii.h"
E 3
#include "gem.h"
#include "i8255xreg.h"

char	ident[] = "i8255x nic driver v" VERSION;

/*
 * Useful macros and typedefs
 */
#define	ROUNDUP(x, a)	(((x) + (a) - 1) & ~((a) - 1))

D 2
#define	STRUCT_COPY(a, b)	bcopy(&(b), &(a), sizeof(a))

E 2
#define	INT8(x)		(0xff & (x))
#define	INT16(x)	(0xffff & (x))
D 3
#if defined(i86pc)
#define	LE32(x)		(x)
#define	LE16(x)		(x)
#elif defined(sparc)
#define	LE32(x)		ddi_swap32(x)
#define	LE16(x)		ddi_swap16(x)
#else
D 2
# error  "kernel architecture is not supported"
E 2
I 2
/* # error  "kernel architecture is not supported" /**/
E 2
#endif
E 3

#define	FLUSH(dp)	(void)INW(dp, SCBSTAT)

#define	SETINTMASK(dp, mask)	OUTB((dp), SCBCMD+1, (mask)>>8)
/* Debugging support */
#ifdef DEBUG_LEVEL
static int ife_debug = DEBUG_LEVEL;
D 4
#define	DPRINTF(n, args)	if (ife_debug>(n)) cmn_err args
E 4
I 4
#define	DPRINTF(n, args)	if (ife_debug > (n)) cmn_err args
E 4
#else
#define	DPRINTF(n, args)
#endif

/*
 * Descriptor implementation
 */
/* Command block size */
I 4
#define	MAXTXFRAGS	(min(8, GEM_MAXTXFRAGS))
E 4
#define	MAX_CB_SIZE	\
D 4
	ROUNDUP(sizeof(struct cb)+ \
	max(sizeof(struct tcb)+sizeof(struct tbd)*GEM_MAXTXFRAGS, 6*8+2), 8)
#define	MAX_CONFIG_SIZE		ROUNDUP(22, sizeof(uint32_t))
E 4
I 4
	ROUNDUP(sizeof (struct cb)+ \
	max(sizeof (struct tcb)+sizeof (struct tbd)*MAXTXFRAGS, 6*8+2), 8)
#define	MAX_CONFIG_SIZE		ROUNDUP(22, sizeof (uint32_t))
E 4
#define	MAX_STATISTICS_SIZE	128

/*
 * Our configuration
 */
D 4
#define TX_RING_SIZE	64
#define TX_BUF_SIZE	TX_RING_SIZE
D 3
#define RX_RING_SIZE	64
E 3
I 3
#define RX_RING_SIZE	256
E 3
#define RX_BUF_SIZE	RX_RING_SIZE
E 4
I 4
D 5
#define	TX_RING_SIZE	64
#define	TX_BUF_SIZE	TX_RING_SIZE
#define	RX_RING_SIZE	256
#define	RX_BUF_SIZE	RX_RING_SIZE
E 5
I 5
#define	TX_BUF_SIZE	64
#define	TX_RING_SIZE	TX_BUF_SIZE
#define	RX_BUF_SIZE	256
#define	RX_RING_SIZE	RX_BUF_SIZE
E 5
E 4

#define	ONESEC			(drv_usectohz(1*1000000))

static int	ife_tx_copy_thresh = 256;
static int	ife_rx_copy_thresh = 256;

/*
 * Supported chips
 */
#define	REV_D101A4	4	/* i82558A */
#define	REV_D101B0	5	/* i82558B */
#define	REV_D101MA	8	/* i82559 */
#define	REV_D101S	9	/* i82669ER */
#define	REV_D102	12
#define	REV_D102C	13
#define	REV_D102E	15

#define	IS_i82557(rev)			((rev) < REV_D101A4)
#define	IS_i82558A_OR_LATER(rev)	((rev) >= REV_D101A4)
#define	IS_i82558B(rev)			((rev) == REV_D101B0)
#define	IS_i82559_OR_LATER(rev)		((rev) >= 6)
#define	IS_i82559ER(rev)		((rev) == REV_D101S)

struct chip_info {
	uint16_t	venid;
	uint16_t	devid;
	uint8_t		revmin;
	uint8_t		revmax;
	uint16_t	flags;
#define	ICH	0x0001
	char		*name;

} ife_chiptbl[] = {
	0x8086,	0x1229,	0x01, 0x03, 0, "i82557",
	0x8086,	0x1229,	0x04, 0x04, 0, "i82558 A Step",
	0x8086,	0x1229,	0x05, 0x05, 0, "i82558 B Step",
	0x8086,	0x1229,	0x06, 0x08, 0, "i82559",
	0x8086,	0x1229,	0x09, 0x09, 0, "i82559ER",
	0x8086,	0x1229,	0x0a, 0x0b, 0, "i82559",
	0x8086,	0x1229,	0x0c, 0x0e, 0, "i82550",
	0x8086,	0x1229,	0x0f, 0x10, 0, "i82551",
	0x8086,	0x1209,	0x00, 0xff, 0, "i82559ER",
	0x8086,	0x1029,	0x00, 0xff, 0, "i82559",
	0x8086,	0x1030,	0x00, 0xff, 0, "In business fast ethernet",
	0x8086,	0x1031,	0x00, 0xff, ICH, "PRO/100VE",	/* ICH3 */
	0x8086,	0x1032,	0x00, 0xff, ICH, "PRO/100VE",	/* ICH3 */
	0x8086,	0x1033,	0x00, 0xff, ICH, "PRO/100VM",	/* ICH3 */
	0x8086,	0x1034,	0x00, 0xff, ICH, "PRO/100VM",	/* ICH3 */
	0x8086,	0x1035,	0x00, 0xff, ICH, "i82562EH",	/* ICH3 */
	0x8086,	0x1036,	0x00, 0xff, ICH, "i82562EH",	/* ICH3 */
	0x8086,	0x1037,	0x00, 0xff, ICH, "i82562EH",	/* ICH3 */
	0x8086,	0x1038,	0x00, 0xff, ICH, "PRO/100VM",	/* ICH3 */
	0x8086,	0x1039,	0x00, 0xff, ICH, "PRO/100VE w/ 82562ET/EZ PHY",
	0x8086,	0x103a,	0x00, 0xff, ICH, "PRO/100VE w/ 82562ET/EZ(CNR)",
	0x8086,	0x103b,	0x00, 0xff, ICH, "PRO/100VM w/ 82562EM/EZ PHY",
	0x8086,	0x103c,	0x00, 0xff, ICH, "PRO/100VM w/ 82562EM/EZ(CNR)",
	0x8086,	0x103d,	0x00, 0xff, ICH, "PRO/100VE(mob)",
	0x8086,	0x103e,	0x00, 0xff, ICH, "PRO/100VM(mob)",
	0x8086,	0x1050,	0x00, 0xff, ICH, "PRO/100VM",	/* ICH5 */
	0x8086,	0x1051,	0x00, 0xff, ICH, "82559",	/* ICH5 */
	0x8086,	0x1052,	0x00, 0xff, ICH, "82559",	/* ICH5 */
	0x8086,	0x1053,	0x00, 0xff, ICH, "82559",	/* ICH5 */
	0x8086,	0x1054,	0x00, 0xff, ICH, "82559",	/* ICH5 */
	0x8086,	0x1055,	0x00, 0xff, ICH, "82559",	/* ICH5 */
	0x8086,	0x1056,	0x00, 0xff, ICH, "82559",	/* ICH5 */
	0x8086,	0x1057,	0x00, 0xff, ICH, "82559",	/* ICH5 */
	0x8086,	0x1059,	0x00, 0xff, 0, "PRO/100M",
	0x8086,	0x1064,	0x00, 0xff, ICH, "82559",	/* ICH6 */
	0x8086,	0x1065,	0x00, 0xff, ICH, "82559",	/* ICH6 */
	0x8086,	0x1066,	0x00, 0xff, ICH, "82559",	/* ICH6 */
	0x8086,	0x1067,	0x00, 0xff, ICH, "82559",	/* ICH6 */
	0x8086,	0x1068,	0x00, 0xff, ICH, "82559",	/* ICH6 */
	0x8086,	0x1069,	0x00, 0xff, ICH, "82559",	/* ICH6 */
	0x8086,	0x106a,	0x00, 0xff, ICH, "82559",	/* ICH6 */
	0x8086,	0x106b,	0x00, 0xff, ICH, "82559",	/* ICH6 */
	0x8086,	0x1091,	0x00, 0xff, ICH, "82559",	/* ICH7 */
	0x8086,	0x1092,	0x00, 0xff, ICH, "82559",	/* ICH7 */
	0x8086,	0x1093,	0x00, 0xff, ICH, "82559",	/* ICH7 */
	0x8086,	0x1094,	0x00, 0xff, ICH, "82559",	/* ICH7 */
	0x8086,	0x1095,	0x00, 0xff, ICH, "82559",	/* ICH7 */
	0x8086,	0x1227,	0x00, 0xff, 0, "i82559",
	0x8086,	0x1228,	0x00, 0xff, 0, "i82559",
	0x8086,	0x2449,	0x00, 0xff, ICH, "i82559",	/* ICH2 */
	0x8086,	0x2459,	0x00, 0xff, ICH, "i82559",	/* ICH2 */
	0x8086,	0x245d,	0x00, 0xff, ICH, "i82559",	/* ICH2 */
	0x8086,	0x27dc,	0x00, 0xff, ICH, "i82559",	/* ICH7 */
	0x8086,	0x5200,	0x00, 0xff, 0, "i82559",
	0x8086,	0x5201,	0x00, 0xff, 0, "i82559",
};
D 4
#define CHIPTABLESIZE   (sizeof(ife_chiptbl)/sizeof(struct chip_info))
E 4
I 4
#define	CHIPTABLESIZE	(sizeof (ife_chiptbl)/sizeof (struct chip_info))
E 4

struct ife_dev {
	uint8_t			rev_id;
	uint16_t		intmask;	/* intmask field in scbcmd */
	struct chip_info	*hw_info;

D 2
	boolean_t		rx_list_loaded;
	int			rx_list_len;
	struct rxbuf		*prev_rxb;

E 2
	uint8_t			config[MAX_CONFIG_SIZE];

	int			eeprom_addr_bits;
	uint16_t		prom[128];

	uint8_t			mac_addr[ETHERADDRL];
	clock_t			last_stats_time;
I 2

	/* rx buffer management */
D 4
	boolean_t		rx_list_loaded;
E 4
	struct rxbuf		*rbp[RX_RING_SIZE];

	/* cuc status */
	boolean_t		cuc_active;
I 5

	/* local lock */
	kmutex_t		reglock;
E 5
E 2
};

/* ======================================================== */
D 4
 
E 4
I 4

E 4
/* mii operations */
static void  ife_mii_sync(struct gem_dev *);
static uint16_t  ife_mii_read(struct gem_dev *, uint_t);
static void ife_mii_write(struct gem_dev *, uint_t, uint16_t);

/* nic operations */
static int ife_reset_chip(struct gem_dev *);
D 2
static void ife_init_chip(struct gem_dev *);
static void ife_start_chip(struct gem_dev *);
E 2
I 2
static int ife_init_chip(struct gem_dev *);
static int ife_start_chip(struct gem_dev *);
E 2
static int ife_stop_chip(struct gem_dev *);
D 2
static void ife_set_media(struct gem_dev *);
static void ife_set_rx_filter(struct gem_dev *);
static void ife_get_stats(struct gem_dev *);
E 2
I 2
static int ife_set_media(struct gem_dev *);
static int ife_set_rx_filter(struct gem_dev *);
static int ife_get_stats(struct gem_dev *);
E 2
static int ife_init_mac_addr(struct gem_dev *);

/* descriptor operations */
static int ife_cmd_desc_write(struct gem_dev *dp, int slot,
D 3
		    ddi_dma_cookie_t *dmacookie, int frags, uint32_t flag);
E 3
I 3
D 4
		    ddi_dma_cookie_t *dmacookie, int frags, uint64_t flag);
E 4
I 4
    ddi_dma_cookie_t *dmacookie, int frags, uint64_t flag);
E 4
E 3
static void ife_rx_desc_write(struct gem_dev *dp, int slot,
D 4
		    ddi_dma_cookie_t *dmacookie, int frags);
E 4
I 4
    ddi_dma_cookie_t *dmacookie, int frags);
E 4
static uint_t ife_cmd_desc_stat(struct gem_dev *dp, int slot, int ndesc);
static uint64_t ife_rx_desc_stat(struct gem_dev *dp, int slot, int ndesc);

static void ife_cmd_desc_init(struct gem_dev *dp, int slot);
static void ife_rx_desc_init(struct gem_dev *dp, int slot);

/* interrupt handler */
D 4
static u_int ife_interrupt(struct gem_dev *dp);
E 4
I 4
static uint_t ife_interrupt(struct gem_dev *dp);
E 4

D 2
static void ife_load_rx_list(struct gem_dev *dp);

E 2
/* ======================================================== */

/* mapping attributes */
/* Data access requirements. */
static struct ddi_device_acc_attr ife_dev_attr = {
	DDI_DEVICE_ATTR_V0,
	DDI_STRUCTURE_LE_ACC,
	DDI_STRICTORDER_ACC
};

/* On sparc, the buffers should be native endianness */
static struct ddi_device_acc_attr ife_buf_attr = {
	DDI_DEVICE_ATTR_V0,
	DDI_NEVERSWAP_ACC,	/* native endianness */
	DDI_STRICTORDER_ACC
};

static ddi_dma_attr_t ife_dma_attr_txbuf = {
	DMA_ATTR_V0,		/* dma_attr_version */
	0,			/* dma_attr_addr_lo */
	0xffffffffull,		/* dma_attr_addr_hi */
	0xffffffffull,		/* dma_attr_count_max */
	1,			/* dma_attr_align */
	0,			/* dma_attr_burstsizes */
	1,			/* dma_attr_minxfer */
	0xffffffffull,		/* dma_attr_maxxfer */
	0xffffffffull,		/* dma_attr_seg */
D 4
	GEM_MAXTXFRAGS,		/* dma_attr_sgllen */
E 4
I 4
	MAXTXFRAGS,		/* dma_attr_sgllen */
E 4
	1,			/* dma_attr_granular */
	0			/* dma_attr_flags */
};

static ddi_dma_attr_t ife_dma_attr_rxbuf = {
	DMA_ATTR_V0,		/* dma_attr_version */
	0,			/* dma_attr_addr_lo */
	0xffffffffull,		/* dma_attr_addr_hi */
	0xffffffffull,		/* dma_attr_count_max */
	1,			/* dma_attr_align */
	0,			/* dma_attr_burstsizes */
	1,			/* dma_attr_minxfer */
	0xffffffffull,		/* dma_attr_maxxfer */
	0xffffffffull,		/* dma_attr_seg */
	1,			/* dma_attr_sgllen */
	1,			/* dma_attr_granular */
	0			/* dma_attr_flags */
};

static ddi_dma_attr_t ife_dma_attr_desc = {
	DMA_ATTR_V0,		/* dma_attr_version */
	0,			/* dma_attr_addr_lo */
	0xffffffffull,		/* dma_attr_addr_hi */
	0xffffffffull,		/* dma_attr_count_max */
	8,			/* dma_attr_align */
	0,			/* dma_attr_burstsizes */
	1,			/* dma_attr_minxfer */
	0xffffffffull,		/* dma_attr_maxxfer */
	0xffffffffull,		/* dma_attr_seg */
	1,			/* dma_attr_sgllen */
	1,			/* dma_attr_granular */
	0			/* dma_attr_flags */
};

/* ======================================================== */
/*
 * misc subroutines
 */
/* ======================================================== */
/*
 * bcopy does not work correctly for little-endian attributed
 * memory on sparc.
 */
I 4
#ifdef notdef
E 4
static void
ife_bcopy_le(void *sp, void *dp, size_t len)
{
	int	i;

	for (i = 0; i < len; i++) {
		((uint8_t *)dp)[i] = ((uint8_t *)sp)[i];
	}
}
I 4
#else
/* the descripor area has native endian attibute now */
#define	ife_bcopy_le	bcopy
#endif
E 4

/* ======================================================== */
/*
 * HW manupilation subroutines
 */
/* ======================================================== */
D 3
static int
E 3
I 3
static boolean_t
E 3
ife_issue_scbcmd(struct gem_dev *dp, uint16_t cmd, uint32_t arg)
{
D 5
	int		i;
E 5
I 5
	int	i;
	int	ret;
E 5
D 4
	struct ife_dev	*lp = (struct ife_dev *)dp->private;
E 4
I 4
	struct ife_dev	*lp = dp->private;
E 4
D 3
#if DEBUG_LEVEL > 2
E 3
	static uint16_t	prev_cmd = 0;
D 3
#endif
E 3
I 3

E 3
D 5
	ASSERT(mutex_owned(&dp->xmitlock));
E 5
I 5
	ret = B_FALSE;
E 5

I 5
	mutex_enter(&lp->reglock);

E 5
D 3
	for (i = 0; (INB(dp, SCBCMD) & (SC_CUC | SC_RUC)) != 0; i++) {
E 3
I 3
	for (i = 0; INB(dp, SCBCMD) & (SC_CUC | SC_RUC); i++) {
E 3
		if (i > 100) {
D 5
			cmn_err(CE_WARN,
E 5
I 5
			cmn_err(cmd == SC_CUC_RESUME ? CE_CONT : CE_WARN,
E 5
D 3
#if DEBUG_LEVEL > 2
			"%s: %s: timeout, prev_cmd:%x, cmd:%x",
				dp->name, __func__, prev_cmd, cmd
#else
			"%s: %s: timeout, cmd:%x",
				dp->name, __func__, cmd
#endif
			);
			break;
E 3
I 3
D 4
				"!%s: %s: timeout, prev_cmd:%x, cmd:%x",
				dp->name, __func__, prev_cmd, cmd);
E 4
I 4
			    "!%s: %s: timeout, prev_cmd:%x, cmd:%x",
			    dp->name, __func__, prev_cmd, cmd);
E 4
D 5
			return (B_FALSE);
E 5
I 5
			goto x;
E 5
E 3
		}
D 3
		drv_usecwait(10);
E 3
I 3
		if (i > 20) {
			drv_usecwait(10);
		}
E 3
	}

I 5
	ret = B_TRUE;

E 5
	switch (cmd) {
	case SC_CUC_START:
	case SC_CUC_LOADSDMP:
	case SC_CUC_LOADBASE:
	case SC_RUC_START:
	case SC_RUC_LOADHDS:
	case SC_RUC_LOADBASE:
		OUTL(dp, GENPTR, arg);
	}

	OUTB(dp, SCBCMD, cmd);
D 3
#if DEBUG_LEVEL > 2
E 3
	prev_cmd = cmd;
I 5
x:
	mutex_exit(&lp->reglock);
E 5
D 3
#endif
E 3
I 3

D 5
	return (B_TRUE);
E 5
I 5
	return (ret);
E 5
E 3
}

D 2
static void
ife_load_rx_list(struct gem_dev *dp)
{
	struct ife_dev	*lp = (struct ife_dev *)dp->private;

	ASSERT(mutex_owned(&dp->intrlock));
	ASSERT(!mutex_owned(&dp->xmitlock));
	ASSERT(dp != NULL);
	ASSERT(dp->rx_buf_head != NULL);
	DPRINTF(0, (CE_CONT, "!%s: loading rx list", dp->name));
	mutex_enter(&dp->xmitlock);
	ife_issue_scbcmd(dp, SC_RUC_START,
			dp->rx_buf_head->rxb_dmacookie[0].dmac_address);
	lp->rx_list_loaded = B_TRUE;
	mutex_exit(&dp->xmitlock);
}

E 2
#define	LOCAL_OP	0x8
D 2
static void
E 2
I 2
static int
E 2
ife_send_op(struct gem_dev *dp, uint32_t opcode)
{
I 3
	int	i;
E 3
	mblk_t	*mp;
I 2
	int	ret = GEM_SUCCESS;
E 2

	ASSERT(!mutex_owned(&dp->xmitlock));

	/* allocate a dummy mblk to fake gem_send_common */
	if ((mp = allocb(ETHERMIN, BPRI_MED)) == NULL) {
		cmn_err(CE_WARN, "!%s: %s: allocb failed", dp->name, __func__);
D 2
		return;
E 2
I 2
		return (GEM_FAILURE);
E 2
	}
D 4
#ifdef GEM_CONFIG_VLAN
E 4
I 4
#ifdef GEM_CONFIG_GLDv3
E 4
	/* avoid errors in vtag scanning */
	mp->b_wptr = mp->b_rptr + ETHERMIN;
	bzero(mp->b_rptr, ETHERMIN);
#endif
D 3
	mp = gem_send_common(dp, mp, opcode | LOCAL_OP);
	if (mp != NULL) {
		cmn_err(CE_WARN,
			"!%s: %s: failed, opcode:%d",
			dp->name, __func__, opcode);
		freemsg(mp);
I 2
		ret = GEM_FAILURE;
E 3
I 3
	for (i = 0; gem_send_common(dp, mp, opcode | LOCAL_OP); i++) {
		if (i > 100) {
			cmn_err(CE_WARN, "!%s: %s: failed, opcode:%d",
D 4
				dp->name, __func__, opcode);
E 4
I 4
			    dp->name, __func__, opcode);
E 4
			freemsg(mp);
			ret = GEM_FAILURE;
			break;
		}
		gem_reclaim_txbuf(dp);
E 3
E 2
	}
I 2

	return (ret);
E 2
}

/* ======================================================== */
/*
 * HW manupilation routines
 */
/* ======================================================== */
static int
ife_reset_chip(struct gem_dev *dp)
{
D 2
	int		i;
E 2
D 4
	struct ife_dev	*lp = (struct ife_dev *)dp->private;
E 4
I 4
	struct ife_dev	*lp = dp->private;
E 4

D 3
	DPRINTF(2, (CE_CONT, "!%s: ife_reset_chip", dp->name));
E 3
I 3
	DPRINTF(2, (CE_CONT, "!%s: %s", dp->name, __func__));
E 3

	/* clear pended interrupts */
	OUTW(dp, SCBSTAT, INW(dp, SCBSTAT));

D 4
	/* write a reset command into PORT register*/
E 4
I 4
	/* write a reset command into PORT register */
E 4
	OUTL(dp, PORT, PORT_SOFTRESET);

D 4
	/* wait 10 system clocks and 5 transmit clocks (10uS)*/
E 4
I 4
	/* wait 10 system clocks and 5 transmit clocks (10uS) */
E 4
	drv_usecwait(10);

I 2
	/* update software copy of device state */
D 4
	lp->cuc_active     = B_FALSE;
	lp->rx_list_loaded = B_FALSE;
E 4
I 4
	lp->cuc_active = B_FALSE;
E 4

E 2
	/* mask interrupt */
	lp->intmask = SC_M;
	SETINTMASK(dp, lp->intmask);

	return (GEM_SUCCESS);
}

D 2
static void
E 2
I 2
static int
E 2
ife_init_chip(struct gem_dev *dp)
{
	int		i;
D 4
	struct ife_dev	*lp = (struct ife_dev *)dp->private;
E 4
I 4
	struct ife_dev	*lp = dp->private;
E 4

D 2
	DPRINTF(2, (CE_CONT, "!%s: ife_init_chip: called", dp->name));
E 2
I 2
D 3
	DPRINTF(0, (CE_CONT, "!%s: ife_init_chip: called", dp->name));
E 3
I 3
	DPRINTF(0, (CE_CONT, "!%s: %s: called", dp->name, __func__));
E 3
E 2

	/* disable early Rx Int */
	OUTB(dp, EARLYRXINT, 0);

	/* disable flow control */
	OUTB(dp, FCTRL, 0);

	if (lp->rev_id >= 6 /* i82559 or later */) {
		/* clear general control register */
		OUTB(dp, GENCTRL, 0);
	}

D 2
	/* reset register copies */
	lp->rx_list_loaded  = B_FALSE;
	lp->rx_list_len     = 0;

E 2
	/* invalidate mac address */
	for (i = 0; i < ETHERADDRL; i++) {
		lp->mac_addr[i] = 0xff;
	}

D 2
	bzero(dp->rx_ring, MAX_STATISTICS_SIZE);
E 2
I 2
	bzero(dp->io_area, MAX_STATISTICS_SIZE);
E 2

	/* load base addresses */
D 5
	mutex_enter(&dp->xmitlock);
E 5
D 3
	ife_issue_scbcmd(dp, SC_CUC_LOADBASE, 0);
	ife_issue_scbcmd(dp, SC_RUC_LOADBASE, 0);
D 2
	ife_issue_scbcmd(dp, SC_CUC_LOADSDMP, dp->rx_ring_dma);
E 2
I 2
	ife_issue_scbcmd(dp, SC_CUC_LOADSDMP, dp->io_area_dma);
E 3
I 3
	(void) ife_issue_scbcmd(dp, SC_CUC_LOADBASE, 0);
	(void) ife_issue_scbcmd(dp, SC_RUC_LOADBASE, 0);
	(void) ife_issue_scbcmd(dp, SC_CUC_LOADSDMP, dp->io_area_dma);
E 3
E 2
D 5
	mutex_exit(&dp->xmitlock);
E 5

	/* send first configure command to enable Tx/Rx */
	ife_send_op(dp, OP_CONFIGURE);
D 2
#if 0
E 2
I 2

E 2
	/* kick CU */
D 5
	mutex_enter(&dp->xmitlock);
E 5
D 3
	ife_issue_scbcmd(dp, SC_CUC_START, dp->tx_ring_dma);
E 3
I 3
	(void) ife_issue_scbcmd(dp, SC_CUC_START, dp->tx_ring_dma);
E 3
I 2
	lp->cuc_active = B_TRUE;
E 2
D 5
	mutex_exit(&dp->xmitlock);
E 5
D 2
#endif
E 2
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
ife_start_chip(struct gem_dev *dp)
{
D 4
	struct ife_dev	*lp = (struct ife_dev *)dp->private;
E 4
I 4
	struct ife_dev	*lp = dp->private;
E 4

I 2
	DPRINTF(0, (CE_CONT, "!%s: %s: called", dp->name, __func__));

E 2
	ASSERT(mutex_owned(&dp->intrlock));
D 5
	ASSERT(!mutex_owned(&dp->xmitlock));
E 5

D 2
	/* enable interrupt */
E 2
I 2
	/* enable interrupts */
E 2
	if ((dp->misc_flag & GEM_NOINTR) == 0) {
		lp->intmask &= ~SC_M;
		SETINTMASK(dp, lp->intmask);
	}
D 2
#if 1
	/* kick CU */
	mutex_enter(&dp->xmitlock);
	ife_issue_scbcmd(dp, SC_CUC_START, dp->tx_ring_dma);
	if (dp->tx_desc_head != dp->tx_desc_tail) {
		ife_issue_scbcmd(dp, SC_CUC_RESUME, 0);
	}
	mutex_exit(&dp->xmitlock);
#endif
	/* Kick Rx */
	ASSERT(!lp->rx_list_loaded);
	ASSERT(dp->mac_active);
	ife_load_rx_list(dp);
E 2
I 2

I 4
	/* as RU has halted, kick it now */
D 5
	mutex_enter(&dp->xmitlock);
E 5
	(void) ife_issue_scbcmd(dp, SC_RUC_START,
	    dp->rx_buf_head->rxb_dmacookie[0].dmac_address);
D 5
	mutex_exit(&dp->xmitlock);
E 5

E 4
	return (GEM_SUCCESS);
E 2
}

static int
ife_stop_chip(struct gem_dev *dp)
{
D 2
	uint16_t	stat;
E 2
	int		i;
I 2
	uint16_t	stat;
E 2
D 4
	struct ife_dev	*lp = (struct ife_dev *)dp->private;
E 4
I 4
	struct ife_dev	*lp = dp->private;
E 4

I 2
	DPRINTF(0, (CE_CONT, "!%s: %s: called", dp->name, __func__));

E 2
D 5
	ASSERT(!mutex_owned(&dp->xmitlock));

E 5
D 2
	/* Stop Rx */
E 2
I 2
D 3
	/* stop Rx */
E 3
I 3
	/* stop rx */
E 3
E 2
D 5
	mutex_enter(&dp->xmitlock);
E 5
D 3
	ife_issue_scbcmd(dp, SC_RUC_ABORT, 0);
E 3
I 3
	(void) ife_issue_scbcmd(dp, SC_RUC_ABORT, 0);
E 3
D 5
	mutex_exit(&dp->xmitlock);
E 5

	/* wait for the nic becomes idle */
	i = (dp->speed == GEM_SPD_100) ? 20 : 200;
D 2
	while (i-- > 0) {
E 2
I 2
	while (1) {
E 2
		stat = INW(dp, SCBSTAT) & (SS_CUS | SS_RUS);
		if (stat == (SS_CUS_IDLE | SS_RUS_IDLE) ||
		    stat == (SS_CUS_SUSPENDED | SS_RUS_IDLE)) {
			break;
		}
I 2
		if (i-- == 0) {
			cmn_err(CE_NOTE, "%s: %s: timeout: stat:0x%x",
D 4
				dp->name, __func__, stat);
E 4
I 4
			    dp->name, __func__, stat);
E 4
			break;
		}
E 2
		drv_usecwait(10);
	}

D 2
	/* disable interrupt */
	if ((dp->misc_flag & GEM_NOINTR) == 0) {
		lp->intmask |= SC_M;
		SETINTMASK(dp, lp->intmask);
	}
E 2
I 2
	/* stop the hardware completely */
	(void) ife_reset_chip(dp);
E 2

	return (GEM_SUCCESS);
}

/*
 * EEPROM I/O routines
 */
#define	EEPROM_READ_CMD		6

/* 2 reads required for 66MHz operation */
D 4
#define	IFE_EEPROM_DELAY(dp)	{INB(dp, EECTRL); INB(dp, EECTRL);}
E 4
I 4
#define	IFE_EEPROM_DELAY(dp)	{ INB(dp, EECTRL); INB(dp, EECTRL); }
E 4

static void
ife_check_eeprom_size(struct gem_dev *dp)
{
	int		i;
	int		addr_bits;
	uint8_t		chip_select;
	uint8_t		di;
	uint16_t	ret;
D 4
	struct ife_dev	*lp = (struct ife_dev *)dp->private;
E 4
I 4
	struct ife_dev	*lp = dp->private;
E 4

	/* enable eeprom interface register */
	chip_select = EC_EECS;
	OUTB(dp, EECTRL, chip_select);

	/* output eeprom command */
	for (i = 4; i >= 0; i--) {
		di = ((EEPROM_READ_CMD >> i) & 1) << EC_EEDI_SHIFT;
		OUTB(dp, EECTRL, chip_select | di);
		OUTB(dp, EECTRL, chip_select | di | EC_EESK);
		IFE_EEPROM_DELAY(dp);

		OUTB(dp, EECTRL, chip_select | di);
		IFE_EEPROM_DELAY(dp);
	}

D 5
	/* How many addres bits required  until eeprom responds with 0 */
E 5
I 5
	/* How many address bits required  until eeprom responds with 0 */
E 5
	i = 0;
	do {
		OUTB(dp, EECTRL, chip_select);
		OUTB(dp, EECTRL, chip_select | EC_EESK);
		IFE_EEPROM_DELAY(dp);

		OUTB(dp, EECTRL, chip_select);
		IFE_EEPROM_DELAY(dp);
		i++;
D 4
	} while ((INB(dp, EECTRL) & EC_EEDO) != 0 && i < 8);
E 4
I 4
	} while ((INB(dp, EECTRL) & EC_EEDO) && i < 8);
E 4

	/* save the result */
	lp->eeprom_addr_bits = i;

	/* read 16bits of data to terminate the seaquence */
	for (i = 16; i > 0; i--) {
		OUTB(dp, EECTRL, chip_select | EC_EESK);
		IFE_EEPROM_DELAY(dp);

		OUTB(dp, EECTRL, chip_select);
		IFE_EEPROM_DELAY(dp);
	}

	/* De-activate the EEPROM */
	OUTB(dp, EECTRL, 0);
}

static uint16_t
ife_read_eeprom(struct gem_dev *dp, uint_t addr)
{
	int		i;
	uint_t		cmd;
	uint8_t		chip_select;
	uint8_t		di;
	uint16_t	ret;
D 4
	struct ife_dev	*lp = (struct ife_dev *)dp->private;
E 4
I 4
	struct ife_dev	*lp = dp->private;
E 4

D 3
	DPRINTF(3, (CE_CONT, "!%s: ife_read_eeprom: called: addr_bits:%d",
			dp->name, lp->eeprom_addr_bits));
E 3
I 3
	DPRINTF(3, (CE_CONT, "!%s: %s: called: addr_bits:%d",
D 4
		dp->name, __func__, lp->eeprom_addr_bits));
E 4
I 4
	    dp->name, __func__, lp->eeprom_addr_bits));
E 4
E 3

I 3
	if (addr >= (1 << lp->eeprom_addr_bits)) {
		cmn_err(CE_WARN,
D 4
			"!%s: %s: address(0x%x) must be lower than 0x%x",
			dp->name, __func__, addr, 1 << lp->eeprom_addr_bits);
E 4
I 4
		    "!%s: %s: address(0x%x) must be lower than 0x%x",
		    dp->name, __func__, addr, 1 << lp->eeprom_addr_bits);
E 4
		return (0);
	}

E 3
	/* make command bits */
D 3
	cmd = (EEPROM_READ_CMD << lp->eeprom_addr_bits)
	    | (addr & ((1 << lp->eeprom_addr_bits) - 1));
E 3
I 3
	cmd = (EEPROM_READ_CMD << lp->eeprom_addr_bits) | addr;
E 3

	/* enable eeprom interface register */
	chip_select = EC_EECS;
	OUTB(dp, EECTRL, chip_select);
	IFE_EEPROM_DELAY(dp);

	/* output eeprom command */
	for (i = 4 + lp->eeprom_addr_bits; i >= 0; i--) {
		di = ((cmd >> i) & 1) << EC_EEDI_SHIFT;
		OUTB(dp, EECTRL, chip_select | di);
		OUTB(dp, EECTRL, chip_select | di | EC_EESK);
		IFE_EEPROM_DELAY(dp);

		OUTB(dp, EECTRL, chip_select | di);
		IFE_EEPROM_DELAY(dp);
	}

	/* get returned value */
	ret = 0;
	for (i = 16; i > 0; i--) {
		/* get 1 bit */
		OUTB(dp, EECTRL, chip_select | EC_EESK);
		IFE_EEPROM_DELAY(dp);

		ret = (ret << 1)
		    | ((INB(dp, EECTRL) >> EC_EEDO_SHIFT) & 1);

		OUTB(dp, EECTRL, chip_select);
		IFE_EEPROM_DELAY(dp);
	}

	/* Terminate the EEPROM access. */
	OUTB(dp, EECTRL, 0);
	IFE_EEPROM_DELAY(dp);

D 3
	DPRINTF(3, (CE_CONT, "!ife_read_eeprom: returned 0x%x", ret));
E 3
I 3
	DPRINTF(3, (CE_CONT, "!%s: %s: returned 0x%x",
D 4
		dp->name, __func__, ret));
E 4
I 4
	    dp->name, __func__, ret));
E 4
E 3

	return (ret);
}

#ifdef DEBUG_LEVEL
static void
ife_eeprom_dump(struct gem_dev *dp)
{
	int		i;
D 4
	struct ife_dev	*lp = (struct ife_dev *)dp->private;
E 4
I 4
	struct ife_dev	*lp = dp->private;
E 4

	for (i = 0; i < 128; i++) {
		lp->prom[i] = ife_read_eeprom(dp, i);
	}

	cmn_err(CE_CONT, "!%s: eeprom dump:", dp->name);
D 4
	for (i = 0; i < 128; i += sizeof(lp->prom[0])) {
E 4
I 4
	for (i = 0; i < 128; i += sizeof (lp->prom[0])) {
E 4
		cmn_err(CE_CONT, "!0x%02x: 0x%04x 0x%04x 0x%04x 0x%04x ",
D 4
		i, lp->prom[i  ], lp->prom[i+1], lp->prom[i+2], lp->prom[i+3]);
E 4
I 4
		    i, lp->prom[i], lp->prom[i+1],
		    lp->prom[i+2], lp->prom[i+3]);
E 4
	}
}
#endif /* DEBUG_LEVEL */

static uint8_t ife_config_default[24] = {
	/*  0 */ 22,		/* size of configure block itself */
	/*  1 */ 0x08,		/* Tx/Rx FIFO threshold */
	/*  2 */ 0,		/* atapive IFS */
	/*  3 */ 0,		/* terminale on CL/read AL/MWI enable */
	/*  4 */ 0,		/* Rx DMA max byte count */
	/*  5 */ 0,		/* Tx DMA max byte count */
	/*  6 */ 0x02 | C6_SaveBadFrames | C6_DiscardOverruns_ |
		C6_ExtStatCount_ | C6_ExtTCB_ | C6_CIInterrupt,
	/*  7 */ 0x00,
	/*  8 */ C8_MII,
	/*  9 */ 0x00,
	/* 10 */ 0x06 | C10_PreambleLen_7 | C10_NSAI,
	/* 11 */ 0x00,
	/* 12 */ C12_IFS_STD,
	/* 13 */ 0x00,
	/* 14 */ 0xf2,
	/* 15 */ 0x48,
	/* 16 */ 0x00,		/* FC delay LSB */
	/* 17 */ 0x40,		/* FC delay MSB */
	/* 18 */ 0xf0 | C18_Padding,
	/* 19 */ C19_AutoFDX,	/* Enable full duplex pin */
	/* 20 */ 0x3f,
	/* 21 */ 0x05,
	/* 22 */ 0x00,		/* pad for double word boundary */
	/* 23 */ 0x00,		/* pad for double word boundary */
};


static void
D 4
ife_flow_control(struct gem_dev *dp)	
E 4
I 4
ife_flow_control(struct gem_dev *dp)
E 4
{
D 4
	struct ife_dev	*lp = (struct ife_dev *)dp->private;
E 4
I 4
	struct ife_dev	*lp = dp->private;
E 4
	int		rev = lp->rev_id;

	/* setup current flow-control mode */

	if (IS_i82557(rev)) {
		/* i82557 doesn't support flow-control */
		return;
	}

	switch (dp->flow_control) {
	case FLOW_CONTROL_TX_PAUSE:
		/* send pause only */
		lp->config[16] = 0x00;
		lp->config[17] = 0x40;
		lp->config[19] &= ~(C19_RxFCRestart | C19_RxFCRestop);
		lp->config[19] |= C19_RejectFC;
		lp->config[19] &= ~C19_TxFC_;
		break;
D 4
	
E 4
I 4

E 4
	case FLOW_CONTROL_RX_PAUSE:
		/* receive pause only */
		lp->config[16] = 0x011f & 0xff;
		lp->config[17] = 0x011f >> 8;
		lp->config[19] |=
D 4
			     (C19_RejectFC | C19_RxFCRestart | C19_RxFCRestop);
E 4
I 4
		    (C19_RejectFC | C19_RxFCRestart | C19_RxFCRestop);
E 4
		lp->config[19] |= C19_TxFC_;
		break;

	case FLOW_CONTROL_SYMMETRIC:
		/* tx and rx pause */
		lp->config[16] = 0x011f & 0xff;
		lp->config[17] = 0x011f >> 8;
		lp->config[19] |=
D 4
			     (C19_RejectFC | C19_RxFCRestart | C19_RxFCRestop);
E 4
I 4
		    (C19_RejectFC | C19_RxFCRestart | C19_RxFCRestop);
E 4
		lp->config[19] &= ~C19_TxFC_;
		break;
D 4
	
E 4
I 4

E 4
	case FLOW_CONTROL_NONE:
		/* Disable tx and rx flow-control */
		lp->config[16] = 0x00;
		lp->config[17] = 0x40;
		lp->config[19] &=
D 4
			~(C19_RejectFC | C19_RxFCRestart | C19_RxFCRestop);
E 4
I 4
		    ~(C19_RejectFC | C19_RxFCRestart | C19_RxFCRestop);
E 4
		lp->config[19] |= C19_TxFC_;
		break;
	}
}

static int
D 4
ife_attach_chip(struct gem_dev *dp)	
E 4
I 4
ife_attach_chip(struct gem_dev *dp)
E 4
{
	int		i;
	uint16_t	val;
D 4
	struct ife_dev	*lp = (struct ife_dev *)dp->private;
E 4
I 4
	struct ife_dev	*lp = dp->private;
E 4
	int		rev = lp->rev_id;

I 2
	DPRINTF(0, (CE_CONT, "!%s: %s: called", dp->name, __func__));

E 2
	ife_check_eeprom_size(dp);
#if DEBUG_LEVEL > 3
	ife_eeprom_dump(dp);
#endif
	for (i = 0; i < ETHERADDRL; i += 2) {
		val = ife_read_eeprom(dp, i/2);
D 4
		dp->dev_addr.ether_addr_octet[i]   = (uint8_t) val;
		dp->dev_addr.ether_addr_octet[i+1] = (uint8_t) (val >> 8);
E 4
I 4
		dp->dev_addr.ether_addr_octet[i] = (uint8_t)val;
		dp->dev_addr.ether_addr_octet[i+1] = (uint8_t)(val >> 8);
E 4
	}

	/* clear statistics */
D 4
	bzero(&dp->stats, sizeof(dp->stats));
E 4
I 4
	bzero(&dp->stats, sizeof (dp->stats));
E 4

	/* make config parameters */
D 4
	bcopy(ife_config_default, lp->config, sizeof(ife_config_default));
E 4
I 4
	bcopy(ife_config_default, lp->config, sizeof (ife_config_default));
E 4

	/* config[2]: we don't use adaptive ifs */

	if (IS_i82558A_OR_LATER(rev)) {
		lp->config[3] |= C3_MWIEn;
	}

D 2
#ifdef notdef
E 2
	/* Rx DMA max byte cnt */
	lp->config[4] = min(0x7f, dp->rxmaxdma/4);

	/* Tx DMA max byte cnt */
	lp->config[5] = min(0x7f, dp->txmaxdma/4) | C5_DMBC;
D 2
#endif

E 2
I 2
#ifdef EXTEND_TCB
E 2
	if (IS_i82558A_OR_LATER(rev)) {
		lp->config[6] &= ~C6_ExtTCB_;
		if (IS_i82559_OR_LATER(rev)) {
			/* 82559 or later */
			lp->config[6] |= C6_ExtStatCount_;
			lp->config[6] |= C6_TCOStat;
D 4
		}
		else {
E 4
I 4
		} else {
E 4
			lp->config[6] &= ~C6_ExtStatCount_;
			lp->config[6] &= ~C6_TCOStat;
		}
	}
D 2

E 2
I 2
#endif
E 2
	/* config 503/MII */
	if (IS_i82557(rev) && dp->mii_phy_addr == -1) {
		/* It's 503 */
		lp->config[8]  &= ~C8_MII;
		lp->config[15] |= C15_CRSCDT;
	}

	if (IS_i82558A_OR_LATER(rev)) {
		lp->config[12] |= C12_LinearPrioMode;
	}

D 2
#ifdef notdef
E 2
I 2
#ifdef NEVER
E 2
	if (rev == REV_D101B0 /* 82558B */) {
		/* for IP checksum offload */
		lp->config[13] = 0;
		lp->config[14] = 0;
	}
#endif
	ife_flow_control(dp);

	if (IS_i82557(rev)) {
		/* i82557 does not support long packets */
		/*
		 * XXX - we cannot implement software vlan because
		 * i82557 doesn't receive any long packets.
		 */
		dp->mtu = min(ETHERMTU, dp->mtu);
D 4
	}
	else {
D 3
#ifdef CONFIG_VLAN
E 3
I 3
#ifdef GEM_CONFIG_VLAN
E 4
I 4
	} else {
#ifdef GEM_CONFIG_GLDv3
E 4
E 3
		dp->mtu = min(IFE_MAX_MTU - 4, dp->mtu);
		lp->config[18] |= C18_LongRxOK;
		dp->misc_flag |= GEM_VLAN_SOFT;
#else
D 5
		dp->mtu = min(IFE_MAX_MTU, dp->mtu);
		if (dp->mtu > ETHERMTU) {
			lp->config[18] |= C18_LongRxOK;
		}
E 5
I 5
		dp->mtu = min(ETHERMTU, dp->mtu);
E 5
#endif
#ifdef notdef
		/* priority flow-control is not implemented */
		lp->config[18] &= ~C18_PrioFCThr;
		lp->config[18] |= 0 << C18_PrioFCThr_SHIFT;
		lp->config[20] &= ~C20_PrioFCLocation;
#endif
	}

	if (IS_i82558A_OR_LATER(rev) && !IS_i82559ER(rev)) {
		/* disable WOL */
		lp->config[19] |= C19_MagicPkt_;
	}

I 3
	/* i8255x requires control packets to be tranmitted */
	dp->misc_flag |= GEM_CTRL_PKT;

E 3
#if DEBUG_LEVEL > 1
	for (i = 0; i < lp->config[0]; i++) {
D 4
		cmn_err(CE_CONT, "%d:0x%02x", i, lp->config[i]);
E 4
I 4
		cmn_err(CE_CONT, "!%d:0x%02x", i, lp->config[i]);
E 4
	}
#endif
	return (GEM_SUCCESS);
}

D 2
static void
E 2
I 2
static int
E 2
D 4
ife_set_rx_filter(struct gem_dev *dp)	
E 4
I 4
ife_set_rx_filter(struct gem_dev *dp)
E 4
{
	uint8_t		c15_old;
	uint8_t		c21_old;
I 5
	uint8_t		*new_mac;
E 5
D 4
	struct ife_dev	*lp = (struct ife_dev *)dp->private;
E 4
I 4
	struct ife_dev	*lp = dp->private;
E 4

	ASSERT(mutex_owned(&dp->intrlock));
	ASSERT(!mutex_owned(&dp->xmitlock));

I 5
	if ((dp->rxmode & RXMODE_ENABLE) == 0) {
		new_mac = (void *)"\002\000\000\000\000\000";
	} else {
		new_mac = dp->cur_addr.ether_addr_octet;
	}

E 5
	/* check mac address */
D 4
	if (bcmp(dp->cur_addr.ether_addr_octet, lp->mac_addr,
			ETHERADDRL) != 0) {
E 4
I 4
D 5
	if (bcmp(dp->cur_addr.ether_addr_octet, lp->mac_addr, ETHERADDRL)
	    != 0) {
E 4
		bcopy(dp->cur_addr.ether_addr_octet, lp->mac_addr, ETHERADDRL);
E 5
I 5
	if (bcmp(new_mac, lp->mac_addr, ETHERADDRL) != 0) {
		bcopy(new_mac, lp->mac_addr, ETHERADDRL);
E 5
D 2
		ife_send_op(dp, OP_ADDRSETUP);
E 2
I 2
		if (ife_send_op(dp, OP_ADDRSETUP) != GEM_SUCCESS) {
			return (GEM_FAILURE);
		}
E 2
	}

	/* check multicast address */
	c15_old = lp->config[15];
	c21_old = lp->config[21];

	lp->config[15] &= ~C15_Promiscuous;
	lp->config[21] &= ~C21_MulticastAll;
D 4
	if ((dp->rxmode & RXMODE_PROMISC) != 0) {
E 4
I 4
D 5
	if (dp->rxmode & RXMODE_PROMISC) {
E 5
I 5
	if ((dp->rxmode & RXMODE_ENABLE) == 0) {
		/* do nothing */
	} else if (dp->rxmode & RXMODE_PROMISC) {
E 5
E 4
		/* promiscous */
		lp->config[15] |= C15_Promiscuous;
D 4
	}
	else if ((dp->rxmode & RXMODE_ALLMULTI) != 0 &&
		dp->mc_count > (MAX_CB_SIZE-sizeof(struct cb)-2)/ETHERADDRL) {
E 4
I 4
	} else if ((dp->rxmode & RXMODE_ALLMULTI) ||
		dp->mc_count > (MAX_CB_SIZE-sizeof (struct cb)-2)/ETHERADDRL) {
E 4
		/* all multi */
		lp->config[21] |= C21_MulticastAll;
D 4
	}
	else {
E 4
I 4
	} else {
E 4
		/* Normal mode */
D 2
		ife_send_op(dp, OP_MULTICAST);
E 2
I 2
		if (ife_send_op(dp, OP_MULTICAST) != GEM_SUCCESS) {
			return (GEM_FAILURE);
		}
E 2
	}

D 3
	if (c15_old != lp->config[15] || c21_old != lp->config[21]) {
E 3
I 3
	if ((c15_old ^ lp->config[15]) | (c21_old ^ lp->config[21])) {
E 3
D 2
		ife_send_op(dp, OP_CONFIGURE);
E 2
I 2
		if (ife_send_op(dp, OP_CONFIGURE) != GEM_SUCCESS) {
			return (GEM_FAILURE);
		}
E 2
	}
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
ife_set_media(struct gem_dev *dp)
{
D 4
	struct ife_dev	*lp = (struct ife_dev *)dp->private;
E 4
I 4
	struct ife_dev	*lp = dp->private;
E 4

	ASSERT(mutex_owned(&dp->intrlock));
	ASSERT(!mutex_owned(&dp->xmitlock));

	/* update configuration */
	if ((lp->config[19] & C19_AutoFDX) == 0) {
		if (dp->full_duplex) {
			lp->config[19] |= C19_ForceFDX;
		} else {
			lp->config[19] &= ~C19_ForceFDX;
		}
	}

	ife_flow_control(dp);

	/* Notify current duplex mode to MAC */
D 2
	ife_send_op(dp, OP_CONFIGURE);
E 2
I 2
	return (ife_send_op(dp, OP_CONFIGURE));
E 2
}

D 2
static void
E 2
I 2
static int
E 2
ife_get_stats(struct gem_dev *dp)
{
	int		i;
I 3
	int		err;
E 3
	uint32_t	x;
D 4
	struct ife_dev	*lp = (struct ife_dev *)dp->private;
D 2
	uint32_t	*stat = (uint32_t *) dp->rx_ring;
E 2
I 2
	uint32_t	*stat = (uint32_t *) dp->io_area;
E 4
I 4
	struct ife_dev	*lp = dp->private;
	uint32_t	*stat = (uint32_t *)dp->io_area;
E 4
E 2
	int		magic_off;

D 3
	DPRINTF(4, (CE_CONT, "!%s: ife_get_stats: called", dp->name));
E 3
I 3
	DPRINTF(4, (CE_CONT, "!%s: %s: called", dp->name, __func__));
E 3

	if (!dp->mac_active) {
		/* dump base is not loaded yet */
D 2
		return;
E 2
I 2
		return (GEM_SUCCESS);
E 2
	}

	lp->last_stats_time = ddi_get_lbolt();

	/* using rx desc area for statistics information */
	if (IS_i82559_OR_LATER(lp->rev_id)) {
		magic_off = 80;
	} else if (IS_i82558A_OR_LATER(lp->rev_id)) {
		magic_off = 72;
	} else {
		magic_off = 64;
	}

	ddi_dma_sync(dp->desc_dma_handle,
D 2
		(off_t)0, (size_t)(magic_off + sizeof(uint32_t)),
E 2
I 2
D 4
		(off_t) 0, (size_t) (magic_off + sizeof(uint32_t)),
E 2
		DDI_DMA_SYNC_FORKERNEL);
E 4
I 4
	    (off_t)0, (size_t)(magic_off + sizeof (uint32_t)),
	    DDI_DMA_SYNC_FORKERNEL);
E 4

	if (stat[magic_off/4] == 0xA007) {

		dp->stats.excoll += x = stat[SO_TxMaxCollisionsErrors/4];
		dp->stats.errxmt += x;

		dp->stats.xmtlatecoll += x = stat[SO_TxLateCollisions/4];
		dp->stats.errxmt += x;

		dp->stats.underflow += x = stat[SO_TxUnderrunErrors/4];
		dp->stats.errxmt += x;

		dp->stats.nocarrier += x = stat[SO_TxLostCarrierSense/4];
		dp->stats.errxmt += x;

D 4
		dp->stats.defer      += stat[SO_TxDeferred/4];
E 4
I 4
		dp->stats.defer += stat[SO_TxDeferred/4];
E 4
		dp->stats.first_coll += stat[SO_TxSingleCollision/4];
		dp->stats.multi_coll += stat[SO_TxMultipleCollision/4];
		dp->stats.collisions += stat[SO_TxTotalCollision/4];

		dp->stats.crc += x = stat[SO_RxCRCErrrs/4];
		dp->stats.errrcv += x;

		dp->stats.frame += x = stat[SO_RxAlignmentErrors/4];
		dp->stats.errrcv += x;

		dp->stats.missed += x = stat[SO_RxResourceErrors/4];
		dp->stats.errrcv += x;

		dp->stats.overflow += x = stat[SO_RxOverrunErrors/4];
		dp->stats.errrcv += x;

		dp->stats.runt += x = stat[SO_RxShortFrameErrors/4];
		dp->stats.errrcv += x;

		/* clear stamp */
		stat[magic_off/4] = 0;
	}

	if (stat[magic_off/4] == 0) {
D 5
		mutex_enter(&dp->xmitlock);
E 5
D 3
		ife_issue_scbcmd(dp, SC_CUC_SDMPRST, 0);
E 3
I 3
		if (ife_issue_scbcmd(dp, SC_CUC_SDMPRST, 0)) {
			stat[magic_off/4] = 0xffff;
		}
E 3
D 5
		mutex_exit(&dp->xmitlock);
E 5
D 3
		stat[magic_off/4] = 0xffff;
E 3
	}
I 2

	return (GEM_SUCCESS);
E 2
}

static char *ife_cu_op_name[] = {
	"NOP",
	"ADDRSETUP",
	"CONFIGURE",
	"MULTICAST",
	"TX",
	"LOADMCODE",
	"DUMP",
	"DIAG",
};

#ifdef TXTIMEOUT_TEST
static int	ife_send_cnt;
#endif
static int
ife_cmd_desc_write(struct gem_dev *dp, int slot,
D 3
		ddi_dma_cookie_t *dmacookie, int frags, uint32_t flag)
E 3
I 3
D 4
		ddi_dma_cookie_t *dmacookie, int frags, uint64_t flag)
E 4
I 4
    ddi_dma_cookie_t *dmacookie, int frags, uint64_t flag)
E 4
E 3
{
D 4
	int			i;
	int 			local_flag;
E 4
I 4
	int		i;
	uint32_t	tmp0;
	uint32_t	tmp1;
	int		local_flag;
E 4
	ddi_dma_cookie_t	*dcp;
D 4
	struct cb		*cbp;
	struct tcb		*tcbp;
	struct tbd		*tbdp;
	uint32_t		cbp_dma;
	uint8_t			*bp;
	uint_t			opcode;
	struct ife_dev		*lp = (struct ife_dev *)dp->private;
E 4
I 4
	struct cb	*cbp;
	struct tcb	*tcbp;
	struct tbd	*tbdp;
	uint32_t	cbp_dma;
	uint8_t		*bp;
	uint_t		opcode;
	struct ife_dev	*lp = dp->private;
E 4

	local_flag = (flag & GEM_TXFLAG_PRIVATE) >> GEM_TXFLAG_PRIVATE_SHIFT;

D 4
	cbp = (struct cb *)(dp->tx_ring + MAX_CB_SIZE * slot);
E 4
I 4
	cbp = (void *)(dp->tx_ring + MAX_CB_SIZE * slot);
E 4
	cbp_dma = dp->tx_ring_dma + MAX_CB_SIZE * slot;
D 4
	bp = (uint8_t *) &cbp[1];
E 4
I 4
	bp = (uint8_t *)&cbp[1];
E 4

	opcode = OP_TX;
D 4
	if (local_flag != 0) {
E 4
I 4
	if (local_flag) {
E 4
		opcode = local_flag & OPMASK;
	}

#if DEBUG_LEVEL > 3
	cmn_err(CE_CONT,
D 3
		"%s: ife_cmd_desc_write "
		"seqnum:%d, slot:%d, frags:%d flag:0x%x, op:%s",
		dp->name, dp->tx_desc_tail, slot, frags, flag,
E 3
I 3
D 4
		"%s: %s: seqnum:%d, slot:%d, frags:%d flag:0x%llx, op:%s",
		dp->name, __func__, dp->tx_desc_tail, slot, frags, flag,
E 3
		ife_cu_op_name[opcode]);
E 4
I 4
	    "!%s: %s: seqnum:%d, slot:%d, frags:%d flag:0x%llx, op:%s",
	    dp->name, __func__, dp->tx_desc_tail, slot, frags, flag,
	    ife_cu_op_name[opcode]);
E 4
	for (i = 0; i < frags; i++) {
D 4
		cmn_err(CE_CONT, "%d: addr: 0x%x, len: 0x%x",
			i, dmacookie[i].dmac_address, dmacookie[i].dmac_size);
E 4
I 4
		cmn_err(CE_CONT, "!%d: addr: 0x%x, len: 0x%x",
		    i, dmacookie[i].dmac_address, dmacookie[i].dmac_size);
E 4
	}
D 5
	flag |= GEM_TXFLAG_INTR;
E 5
#endif
D 5
#if DEBUG_LEVEL > 0
E 5
I 5
#if DEBUG_LEVEL > 3
E 5
	flag |= GEM_TXFLAG_INTR;
#endif

	switch (opcode) {
	case OP_NOP:		/* 0 */
		break;

	case OP_ADDRSETUP:	/* 1 */
		/* setup mac address */
		ife_bcopy_le(dp->dev_addr.ether_addr_octet, bp, ETHERADDRL);
		break;

	case OP_CONFIGURE:	/* 2 */
		/* set configure information */
D 4
		ife_bcopy_le(lp->config, bp, sizeof(lp->config));
E 4
I 4
		ife_bcopy_le(lp->config, bp, sizeof (lp->config));
E 4
		break;

	case OP_MULTICAST:	/* 3 */
		/* send multicast address list */
D 4
	ASSERT(dp->mc_count <= (MAX_CB_SIZE-sizeof(struct cb)-2)/ETHERADDRL);
E 4
I 4
	ASSERT(dp->mc_count <= (MAX_CB_SIZE-sizeof (struct cb)-2)/ETHERADDRL);
E 4

D 2
		*(uint16_t *)bp = LE16(dp->mc_count);
E 2
I 2
D 3
		*(uint16_t *)bp = LE16(dp->mc_count*ETHERADDRL);
E 3
I 3
		*(uint16_t *)bp = LE_16(dp->mc_count * ETHERADDRL);
E 3
E 2
D 4
		bp += sizeof(uint16_t);
E 4
I 4
		bp += sizeof (uint16_t);
E 4

		for (i = 0; i < dp->mc_count; i++) {
			ife_bcopy_le(dp->mc_list[i].addr.ether_addr_octet,
D 4
				bp, ETHERADDRL);
E 4
I 4
			    bp, ETHERADDRL);
E 4
			bp += ETHERADDRL;
I 2
#if DEBUG_LEVEL > 3
			cmn_err(CE_CONT,
D 4
			"!%s: adding mcast(%d) %02x:%02x:%02x:%02x:%02x:%02x",
				dp->name, i,
				dp->mc_list[i].addr.ether_addr_octet[0],
				dp->mc_list[i].addr.ether_addr_octet[1],
				dp->mc_list[i].addr.ether_addr_octet[2],
				dp->mc_list[i].addr.ether_addr_octet[3],
				dp->mc_list[i].addr.ether_addr_octet[4],
				dp->mc_list[i].addr.ether_addr_octet[5]);
E 4
I 4
			    "!%s: adding mcast(%d) "
			    "%02x:%02x:%02x:%02x:%02x:%02x",
			    dp->name, i,
			    dp->mc_list[i].addr.ether_addr_octet[0],
			    dp->mc_list[i].addr.ether_addr_octet[1],
			    dp->mc_list[i].addr.ether_addr_octet[2],
			    dp->mc_list[i].addr.ether_addr_octet[3],
			    dp->mc_list[i].addr.ether_addr_octet[4],
			    dp->mc_list[i].addr.ether_addr_octet[5]);
E 4
#endif
E 2
		}
		break;

	case OP_TX:	/* 4 */
I 3
		if (dp->speed == GEM_SPD_10 && !dp->full_duplex) {
			/* workaround for tx hang on 10Mbps half duplex */
			(void) ife_issue_scbcmd(dp, SC_CUC_NOP, 0);
			/* wait for 1uS at least */
			drv_usecwait(10);
		}

E 3
D 4
		tcbp = (struct tcb *) bp;
		tbdp = (struct tbd *) &tcbp[1];
E 4
I 4
		tcbp = (struct tcb *)bp;
		tbdp = (struct tbd *)&tcbp[1];
E 4

		/* copy fragment list from dmacookie */
		for (i = 0; i < frags; i++, tbdp++) {
D 3
			tbdp->tb_size = LE32(dmacookie[i].dmac_size);
			tbdp->tb_addr = LE32(dmacookie[i].dmac_address);
E 3
I 3
D 4
			tbdp->tb_size = LE_32(dmacookie[i].dmac_size);
			tbdp->tb_addr = LE_32(dmacookie[i].dmac_address);
E 4
I 4
			tmp0 = dmacookie[i].dmac_size;
			tbdp->tb_size = LE_32(tmp0);
			tmp1 = dmacookie[i].dmac_address;
			tbdp->tb_addr = LE_32(tmp1);
E 4
E 3
		}

		/* make tcb */
D 3
		tcbp->tcb_ctrl = LE32(
E 3
I 3
D 4
		tcbp->tcb_ctrl = LE_32(
E 3
			    (frags << TCB_TBDNUM_SHIFT)
			   |(((dp->txthr + TXTHR_UNIT - 1) / TXTHR_UNIT)
							<< TCB_TXTHR_SHIFT));
E 4
I 4
		tmp0 = (frags << TCB_TBDNUM_SHIFT)
		    | (((dp->txthr + TXTHR_UNIT - 1) / TXTHR_UNIT)
		    << TCB_TXTHR_SHIFT);
		tcbp->tcb_ctrl = LE_32(tmp0);
E 4
I 2
#ifdef EXTEND_TCB
E 2
		if (IS_i82558A_OR_LATER(lp->rev_id)) {
			if (frags > 2) {
D 3
				tcbp->tcb_tbdptr = LE32(
E 3
I 3
D 4
				tcbp->tcb_tbdptr = LE_32(
E 3
					cbp_dma +
					sizeof(struct cb) + sizeof(struct tcb) +
					2*sizeof(struct tbd));
E 4
I 4
				tmp0 = cbp_dma +
				    sizeof (struct cb) + sizeof (struct tcb) +
				    2*sizeof (struct tbd);
				tcbp->tcb_tbdptr = LE_32(tmp0);
E 4
			} else {
D 3
				tcbp->tcb_tbdptr = LE32(TBD_ADDR_NULL);
E 3
I 3
				tcbp->tcb_tbdptr = LE_32(TBD_ADDR_NULL);
E 3
			}
D 2
		}
		else {
E 2
I 2
		} else
#endif
		{
E 2
D 3
			tcbp->tcb_tbdptr = LE32(cbp_dma +
E 3
I 3
D 4
			tcbp->tcb_tbdptr = LE_32(cbp_dma +
E 3
				sizeof(struct cb) + sizeof(struct tcb));
E 4
I 4
			tmp0 = cbp_dma +
			    sizeof (struct cb) + sizeof (struct tcb);
			tcbp->tcb_tbdptr = LE_32(tmp0);
E 4
		}
		break;

	default:
		cmn_err(CE_PANIC, "%s: %s: opcode:%x not supported",
D 4
			dp->name, __func__, opcode);
E 4
I 4
		    dp->name, __func__, opcode);
E 4
		break;
	}

	/* make command block */
D 3
	cbp->cmdstat = LE32(
E 3
I 3
D 4
	cbp->cmdstat = LE_32(
E 3
		       ((flag & GEM_TXFLAG_INTR) ? CS_I : 0)
		     | ((opcode == OP_TX) ? CS_SF_ : 0)
		     | (opcode << CS_OP_SHIFT));
E 4
I 4
	tmp0 = opcode << CS_OP_SHIFT;
	if (flag & GEM_TXFLAG_INTR) {
		tmp0 |= CS_I;
	}
	if (opcode == OP_TX) {
		tmp0 |= CS_SF_;
	}
	cbp->cmdstat = LE_32(tmp0);
E 4

#if DEBUG_LEVEL > 2
D 4
	ASSERT((cbp_dma & (2*sizeof(uint32_t) - 1)) == 0);
E 4
I 4
	ASSERT((cbp_dma & (2*sizeof (uint32_t) - 1)) == 0);
E 4
#endif
#ifdef TXTIMEOUT_TEST
	ife_send_cnt++;
	if (ife_send_cnt > 100) {
	}
#endif
	return (1);
}

static void
ife_cmd_start(struct gem_dev *dp, int start_slot, int nslot)
{
	uint8_t		*bp;
I 2
D 4
	struct ife_dev	*lp = (struct ife_dev *) dp->private;
E 4
I 4
	struct ife_dev	*lp = dp->private;
I 5
	const uint_t	tx_ring_size = dp->gc.gc_tx_ring_size;
E 5
E 4
E 2

	DPRINTF(1, (CE_CONT, "!%s: %s start:%d, nslot:%d",
D 4
		dp->name, __func__, start_slot, nslot));
E 4
I 4
	    dp->name, __func__, start_slot, nslot));
E 4

D 2
	/* Add suspended bit into last descriptor */
E 2
I 2
	/* Add suspend bit into last descriptor */
E 2
D 4
	bp = ((uint8_t *) dp->tx_ring) +
		MAX_CB_SIZE * SLOT(start_slot + nslot - 1, TX_RING_SIZE);
E 4
I 4
	bp = ((uint8_t *)dp->tx_ring) +
D 5
	    MAX_CB_SIZE * SLOT(start_slot + nslot - 1, TX_RING_SIZE);
E 5
I 5
	    MAX_CB_SIZE * SLOT(start_slot + nslot - 1, tx_ring_size);
E 5
E 4
	bp[3] |= CS_S >> (8*3);

D 2
	/* flush it */
E 2
I 2
	/* flush new descriptors */
E 2
	gem_tx_desc_dma_sync(dp, start_slot, nslot, DDI_DMA_SYNC_FORDEV);

	/* remove suspend bit in the previous descriptor */
D 4
	bp = ((uint8_t *) dp->tx_ring) +
		MAX_CB_SIZE * SLOT(start_slot - 1, TX_RING_SIZE);
E 4
I 4
	bp = ((uint8_t *)dp->tx_ring) +
D 5
	    MAX_CB_SIZE * SLOT(start_slot - 1, TX_RING_SIZE);
E 5
I 5
	    MAX_CB_SIZE * SLOT(start_slot - 1, tx_ring_size);
E 5
E 4
	bp[3] &= ~(CS_S >> (8*3));

	/* flush it */
	gem_tx_desc_dma_sync(dp,
D 4
		SLOT(start_slot - 1, TX_RING_SIZE), 1, DDI_DMA_SYNC_FORDEV);
E 4
I 4
D 5
	    SLOT(start_slot - 1, TX_RING_SIZE), 1, DDI_DMA_SYNC_FORDEV);
E 5
I 5
	    SLOT(start_slot - 1, tx_ring_size), 1, DDI_DMA_SYNC_FORDEV);
E 5
E 4

	/* Here we resume potentially supended CU. */
D 2
	if (dp->mac_active) {
E 2
I 2
	if (lp->cuc_active) {
E 2
D 3
		ife_issue_scbcmd(dp, SC_CUC_RESUME, 0);
E 3
I 3
		(void) ife_issue_scbcmd(dp, SC_CUC_RESUME, 0);
E 3
	}
}

static void
ife_rx_desc_write(struct gem_dev *dp, int slot,
	    ddi_dma_cookie_t *dmacookie, int frags)
{
	int		i;
I 4
	uint32_t	tmp;
E 4
I 2
	struct rxbuf	*rbp;
E 2
	struct rfd	*rfd;
D 2
	struct ife_dev	*lp = (struct ife_dev *)dp->private;
E 2
I 2
D 4
	struct ife_dev	*lp = (struct ife_dev *) dp->private;
E 4
I 4
	struct ife_dev	*lp = dp->private;
E 4
E 2

D 2
#if DEBUG_LEVEL > 3
E 2
I 2
#if DEBUG_LEVEL > 1
E 2
	cmn_err(CE_CONT,
D 4
		"%s: ife_rx_desc_write seqnum: %d, slot %d, frags: %d",
		dp->name, dp->rx_active_tail, slot, frags);
E 4
I 4
	    "!%s: %s seqnum: %d, slot %d, frags: %d",
	    dp->name, __func__, dp->rx_active_tail, slot, frags);
E 4
	for (i = 0; i < frags; i++) {
D 4
		cmn_err(CE_CONT, "  frag: %d addr: 0x%x, len: 0x%x",
			i, dmacookie[i].dmac_address, dmacookie[i].dmac_size);
E 4
I 4
		cmn_err(CE_CONT, "!  frag: %d addr: 0x%x, len: 0x%x",
		    i, dmacookie[i].dmac_address, dmacookie[i].dmac_size);
E 4
	}
#endif
	ASSERT(frags == 1);

D 2
	rfd = (struct rfd *) dp->rx_buf_tail->rxb_buf;
	rfd->cmdstat = LE32(CS_EL);
E 2
I 2
	rbp = dp->rx_buf_tail;
	lp->rbp[slot] = rbp;

D 4
	rfd = (struct rfd *) rbp->rxb_buf;
E 4
I 4
	rfd = (struct rfd *)rbp->rxb_buf;
E 4
D 3
	rfd->cmdstat = LE32(CS_EL);	/* end of list */
E 3
I 3
	rfd->cmdstat = LE_32(CS_EL);	/* end of list */
E 3
E 2
D 4
	rfd->link    = 0;
	rfd->size    =
D 2
		LE32((((uint_t)dmacookie->dmac_size) - sizeof(struct rfd))
E 2
I 2
D 3
		LE32((((uint_t) dmacookie->dmac_size) - sizeof(struct rfd))
E 3
I 3
		LE_32((((uint_t) dmacookie->dmac_size) - sizeof(struct rfd))
E 3
E 2
				<< RFD_SIZE_SHIFT);
E 4
I 4
	rfd->link = 0;
	tmp = (((uint32_t)dmacookie->dmac_size) - sizeof (struct rfd))
	    << RFD_SIZE_SHIFT;
	rfd->size = LE_32(tmp);
E 4

D 2
        ddi_dma_sync(dp->rx_buf_tail->rxb_dh,
                        0, sizeof(struct rfd), DDI_DMA_SYNC_FORDEV);

E 2
	/* append this frame to the hardware rx list */
D 2
	if (lp->rx_list_len > 0)  {
E 2
I 2
D 5
	rbp = lp->rbp[SLOT(slot - 1, RX_RING_SIZE)];
E 5
I 5
	rbp = lp->rbp[SLOT(slot - 1, dp->gc.gc_rx_ring_size)];
E 5
D 4
	if (rbp != NULL) {
E 4
I 4
	if (rbp) {
E 4
E 2
		/* Link this to the previous rfd */
D 2
		rfd = (struct rfd *)(lp->prev_rxb->rxb_buf);
		rfd->link = LE32((uint32_t)dmacookie->dmac_address);
		((uint8_t *)&rfd->cmdstat)[3] &= ~(CS_EL>>24);
E 2
I 2
		/* XXX - we left the suspend bit set */
D 4
		rfd = (struct rfd *) rbp->rxb_buf;
D 3
		rfd->link = LE32((uint32_t) dmacookie->dmac_address);
E 3
I 3
		rfd->link = LE_32((uint32_t) dmacookie->dmac_address);
E 4
I 4
		rfd = (void *)rbp->rxb_buf;
		tmp = (uint32_t)dmacookie->dmac_address;
		rfd->link = LE_32(tmp);
E 4
E 3
	}
}
E 2

D 2
		ddi_dma_sync(lp->prev_rxb->rxb_dh,
E 2
I 2
static void
ife_rx_start(struct gem_dev *dp, int start_slot, int nslot)
{
	int		slot;
	struct rxbuf	*rbp;
	struct rfd	*rfd;
	uint8_t		mark;
D 4
	struct ife_dev	*lp = (struct ife_dev *)dp->private;
E 4
I 4
	struct ife_dev	*lp = dp->private;
I 5
	const uint_t	rx_ring_size = dp->gc.gc_rx_ring_size;
E 5
E 4

	DPRINTF(1, (CE_CONT, "!%s: %s start:%d, nslot:%d",
D 4
		dp->name, __func__, start_slot, nslot));
E 4
I 4
	    dp->name, __func__, start_slot, nslot));
E 4

	/*
	 * As i8255x doesn't have a rx descriptor ring, no need
	 * to flush that.
	 */
	slot = start_slot + nslot;
	mark = 0;
	while (slot-- != start_slot) {
D 5
		rbp = lp->rbp[SLOT(slot, RX_RING_SIZE)];
E 5
I 5
		rbp = lp->rbp[SLOT(slot, rx_ring_size)];
E 5

		/* remove end_of_list bit except for the last descriptor */
D 4
		rfd = (struct rfd *) rbp->rxb_buf;
		((uint8_t *) &rfd->cmdstat)[3] &= ~mark;
E 4
I 4
		rfd = (struct rfd *)rbp->rxb_buf;
		((uint8_t *)&rfd->cmdstat)[3] &= ~mark;
E 4

		ddi_dma_sync(rbp->rxb_dh,
E 2
D 4
				0, sizeof(struct rfd), DDI_DMA_SYNC_FORDEV);
E 4
I 4
		    0, sizeof (struct rfd), DDI_DMA_SYNC_FORDEV);
E 4
I 2
		mark = CS_EL >> 24;
E 2
	}
D 2
	lp->rx_list_len++;
	
	lp->prev_rxb = dp->rx_buf_tail;
E 2

I 2
D 5
	rbp = lp->rbp[SLOT(slot, RX_RING_SIZE)];
E 5
I 5
	rbp = lp->rbp[SLOT(slot, rx_ring_size)];
E 5
D 4
	if (rbp != NULL) {
E 4
I 4
	if (rbp) {
E 4
		/* append new rx buffers to the hardware rx list */

		/* remove suspend bit except */
D 4
		rfd = (struct rfd *) (rbp->rxb_buf);
		((uint8_t *) &rfd->cmdstat)[3] &= ~(CS_EL >> 24);
E 4
I 4
		rfd = (void *)rbp->rxb_buf;
		((uint8_t *)&rfd->cmdstat)[3] &= ~(CS_EL >> 24);
E 4

		ddi_dma_sync(rbp->rxb_dh,
D 4
				0, sizeof(struct rfd), DDI_DMA_SYNC_FORDEV);
E 4
I 4
		    0, sizeof (struct rfd), DDI_DMA_SYNC_FORDEV);
E 4
	}
D 4

E 2
	if (!lp->rx_list_loaded && dp->mac_active) {
D 2
		ife_load_rx_list(dp);
E 2
I 2
		/* as RU has halted, kick it now */
		mutex_enter(&dp->xmitlock);
D 3
		ife_issue_scbcmd(dp, SC_RUC_START,
E 3
I 3
		(void) ife_issue_scbcmd(dp, SC_RUC_START,
E 3
			dp->rx_buf_head->rxb_dmacookie[0].dmac_address);
		lp->rx_list_loaded = B_TRUE;
		mutex_exit(&dp->xmitlock);
E 2
	}
E 4
}

static uint_t
ife_cmd_desc_stat(struct gem_dev *dp, int slot, int ndesc)
{
	struct cb	*cbp;
	uint32_t	cstat;
D 4
	struct ife_dev	*lp = (struct ife_dev *)dp->private;
E 4
I 4
	struct ife_dev	*lp = dp->private;
E 4

D 4
	cbp = (struct cb *) (dp->tx_ring + MAX_CB_SIZE * slot);
E 4
I 4
	cbp = (void *)(dp->tx_ring + MAX_CB_SIZE * slot);
E 4

D 3
	cstat = LE32(cbp->cmdstat);
E 3
I 3
D 4
	cstat = LE_32(cbp->cmdstat);
E 4
I 4
	cstat = cbp->cmdstat;
	cstat = LE_32(cstat);
E 4
E 3

D 2
	DPRINTF(1, (CE_CONT,
E 2
I 2
	DPRINTF(2, (CE_CONT,
E 2
D 3
	"!%s: ife_cmd_desc_stat: slot:%d, cmdstat:0x%b op:%s scbstat:0x%04x",
		dp->name, slot, cstat, CS_BITS,
E 3
I 3
D 4
		"!%s: %s: slot:%d, cmdstat:0x%b op:%s scbstat:0x%04x",
		dp->name, __func__, slot, cstat, CS_BITS,
E 3
		ife_cu_op_name[(cstat & CS_OP) >> CS_OP_SHIFT],
		INW(dp, SCBSTAT)));
E 4
I 4
	    "!%s: %s: slot:%d, cmdstat:0x%b op:%s scbstat:0x%04x",
	    dp->name, __func__, slot, cstat, CS_BITS,
	    ife_cu_op_name[(cstat & CS_OP) >> CS_OP_SHIFT],
	    INW(dp, SCBSTAT)));
E 4

	if ((cstat & CS_C) == 0) {
		/* not completed */
		return (0);
	}

	/* tx error statitcs */
D 4
	if ((cstat & CS_U) != 0) {
E 4
I 4
	if (cstat & CS_U) {
E 4
		/* tx underrun happened */
		dp->txthr = min(TXTHR_SF*TXTHR_UNIT, dp->txthr + 64);
	}

	return (GEM_TX_DONE);
}

#ifdef DEBUG_LEVEL
static void
ife_dump_packet(struct gem_dev *dp, uint8_t *bp, int n)
{
	int	i;

D 4
	for (i=0; i < n; i += 8, bp += 8) {
E 4
I 4
	for (i = 0; i < n; i += 8, bp += 8) {
E 4
		cmn_err(CE_CONT, "%02x %02x %02x %02x %02x %02x %02x %02x",
D 4
		bp[0], bp[1], bp[2], bp[3], bp[4], bp[5], bp[6], bp[7]);
E 4
I 4
		    bp[0], bp[1], bp[2], bp[3], bp[4], bp[5], bp[6], bp[7]);
E 4
	}
}
#endif

static uint64_t
ife_rx_desc_stat(struct gem_dev *dp, int slot, int ndesc)
{
D 2
	struct rxbuf	*rbp = dp->rx_buf_head;
	struct rfd	*rfd;
E 2
	uint_t		flag;
	uint_t		len;
	uint16_t	cstat;
I 2
	struct rxbuf	*rbp;
	struct rfd	*rfd;
E 2
D 4
	struct ife_dev	*lp = (struct ife_dev *)dp->private;
E 4
I 4
	struct ife_dev	*lp = dp->private;
E 4

I 2
	rbp = lp->rbp[slot];
	ASSERT(rbp != NULL);
D 4

E 4
I 4
#ifdef notdef
E 4
E 2
	ddi_dma_sync(rbp->rxb_dh, 0,
D 4
		sizeof(struct rfd), DDI_DMA_SYNC_FORKERNEL);
E 4
I 4
	    sizeof (struct rfd), DDI_DMA_SYNC_FORKERNEL);
#endif
	rfd = (struct rfd *)rbp->rxb_buf;
	len = rfd->size;
	len = LE_32(len) & RFD_COUNT;
	cstat = rfd->cmdstat;
	cstat = LE_32(cstat);
E 4

D 2
	ASSERT(lp->rx_list_len > 0);

	rfd   = (struct rfd *)rbp->rxb_buf;
E 2
I 2
D 4
	rfd   = (struct rfd *) rbp->rxb_buf;
E 2
D 3
	len   = LE32(rfd->size) & RFD_COUNT;
	cstat = LE32(rfd->cmdstat);
E 3
I 3
	len   = LE_32(rfd->size) & RFD_COUNT;
	cstat = LE_32(rfd->cmdstat);
E 3

E 4
	DPRINTF(2, (CE_CONT,
D 4
		"!%s: %s: slot:%d, rx_cstat:0x%b framesize:0x%x",
		dp->name, __func__, slot, cstat, CS_BITS, len));
E 4
I 4
	    "!%s: %s: slot:%d, rx_cstat:0x%b framesize:0x%x",
	    dp->name, __func__, slot, cstat, CS_BITS, len));
E 4

	if ((cstat & CS_C) == 0) {
		/* not received yet */
		return (0);
	}

D 2
	lp->rx_list_len--;
E 2
I 2
	lp->rbp[slot] = NULL;

E 2
	flag = GEM_RX_DONE;
	if ((cstat & CS_OK) == 0) {
		flag |= GEM_RX_ERR;
	}
#if DEBUG_LEVEL > 3
	ife_dump_packet(dp, dp->rx_buf_head->rxb_buf, len);
#endif
	return (flag | len);
}

static void
ife_cmd_desc_init(struct gem_dev *dp, int slot)
{
D 4
	struct cb		*cbp;
	uint32_t		cbp_dma;
	struct ife_dev		*lp = (struct ife_dev *)dp->private;
E 4
I 4
	struct cb	*cbp;
	uint32_t	cbp_dma;
	uint32_t	link;
	struct ife_dev	*lp = dp->private;
I 5
	const uint_t	tx_ring_size = dp->gc.gc_tx_ring_size;
E 5
E 4

	/*
	 * Make cmd block ring structure
	 */
D 4
	cbp = (struct cb *) (dp->tx_ring + MAX_CB_SIZE * slot);
E 4
I 4
	cbp = (void *)(dp->tx_ring + MAX_CB_SIZE * slot);
E 4

	/* link to the next cb in the command block ring */
D 4
	cbp->link =
D 3
	    LE32(dp->tx_ring_dma + MAX_CB_SIZE * SLOT(slot+1, TX_RING_SIZE));
E 3
I 3
	    LE_32(dp->tx_ring_dma + MAX_CB_SIZE * SLOT(slot+1, TX_RING_SIZE));
E 4
I 4
D 5
	link = dp->tx_ring_dma + MAX_CB_SIZE * SLOT(slot+1, TX_RING_SIZE);
E 5
I 5
	link = dp->tx_ring_dma + MAX_CB_SIZE * SLOT(slot + 1, tx_ring_size);
E 5
	cbp->link = LE_32(link);
E 4
E 3
}

static void
ife_rx_desc_init(struct gem_dev *dp, int slot)
{
D 2
	/* do nothing */
E 2
I 2
D 4
	struct ife_dev	*lp = (struct ife_dev *) dp->private;
E 4
I 4
	struct ife_dev	*lp = dp->private;
E 4

	lp->rbp[slot] = NULL;
E 2
}

/*
 * Device depend interrupt handler
 */
#define	INTRBITS	\
D 4
		(SS_CX | SS_FR | SS_CNA | SS_RNR | SS_MDI | SS_SWI | SS_FCP)
static u_int
E 4
I 4
	(SS_CX | SS_FR | SS_CNA | SS_RNR | SS_MDI | SS_SWI | SS_FCP)
static uint_t
E 4
ife_interrupt(struct gem_dev *dp)
{
	uint16_t	stat;
	uint_t		flag = 0;
D 4
	struct ife_dev	*lp = (struct ife_dev *)dp->private;
E 4
I 4
	struct ife_dev	*lp = dp->private;
E 4
	uint16_t	intmask_saved = lp->intmask;

	stat = INW(dp, SCBSTAT);
D 3
	if ((stat & INTRBITS) == 0) {
E 3
I 3
	if (!((lp->intmask & SC_M) == 0 && (stat & INTRBITS))) {
E 3
		/* Not for us */
		return (DDI_INTR_UNCLAIMED);
	}
D 3

E 3
I 3
#ifndef CONFIG_OPT_IO
E 3
	/* Before we clear PCI interrupt signal line, mask all interrupts */
	if ((dp->misc_flag & GEM_NOINTR) == 0) {
		lp->intmask |= SC_M;
		SETINTMASK(dp, lp->intmask);
	}
D 3

	DPRINTF(2, (CE_CONT, "%s: Interrupt, scbstat: %b",
E 3
I 3
#endif
	DPRINTF(2, (CE_CONT, "!%s: Interrupt, scbstat: %b",
E 3
D 4
			   dp->name, stat, SCBSTAT_BITS));
E 4
I 4
	    dp->name, stat, SCBSTAT_BITS));
E 4

D 3
	if (!dp->mac_active) {
		/* the device is not active, no more interrupts */
		OUTW(dp, SCBSTAT, INW(dp, SCBSTAT));
		return (DDI_INTR_CLAIMED);
	}

E 3
	/* clear interrupt */
	OUTW(dp, SCBSTAT, stat);
#ifdef MAP_MEM
	FLUSH(dp);
#endif
D 3
	if ((stat & (SS_FR | SS_RNR)) != 0) {
		/* a packet was received */
D 2
		gem_receive(dp);

E 2
		if ((stat & SS_RNR) != 0) {
E 3
I 3

	if (!dp->mac_active) {
#ifdef CONFIG_OPT_IO
		/* the device is not active, no more interrupts */
		lp->intmask |= SC_M;
		SETINTMASK(dp, lp->intmask);
#endif
		return (DDI_INTR_CLAIMED);
	}

	if (stat & (SS_FR | SS_RNR)) {
		/* packets were received */
I 4
		(void) gem_receive(dp);

E 4
		if (stat & SS_RNR) {
E 3
D 2
			/* RU became not ready */
			DPRINTF(4, (CE_CONT, "%s: RU not ready",
				dp->name));
E 2
I 2
D 4
			/* RU became inactive */
E 2
			lp->rx_list_loaded = B_FALSE;
E 4
I 4
			/* as RU has halted, kick it now */
E 4
D 2
			if (lp->rx_list_len > 0) {
				ife_load_rx_list(dp);
			}
E 2
I 2
D 3
			DPRINTF(0, (CE_NOTE, "%s: RU not ready", dp->name));
E 3
I 3
			DPRINTF(0, (CE_NOTE, "!%s: RU not ready", dp->name));
I 4
D 5
			mutex_enter(&dp->xmitlock);
E 5
			(void) ife_issue_scbcmd(dp, SC_RUC_START,
			    dp->rx_buf_head->rxb_dmacookie[0].dmac_address);
D 5
			mutex_exit(&dp->xmitlock);
E 5
E 4
E 3
E 2
		}
I 2
D 4
		(void) gem_receive(dp);
E 4
E 2
	}

D 3
	if ((stat & SS_CX) != 0) {
E 3
I 3
	if (stat & SS_CX) {
E 3
		/* cmd has processed */
		if (gem_tx_done(dp)) {
			flag |= INTR_RESTART_TX;
		}
	}
D 3

E 3
I 3
#ifndef CONFIG_OPT_IO
E 3
	if ((dp->misc_flag & GEM_NOINTR) == 0) {
		/* restore interrupt mask */
		lp->intmask = intmask_saved;
		SETINTMASK(dp, lp->intmask);
	}
D 3

E 3
I 3
#endif
E 3
	return (DDI_INTR_CLAIMED | flag);
}

/*
 * HW depend MII routine
 */
static int
ife_mii_config(struct gem_dev *dp)
{
	uint16_t	val;
D 3
	uint32_t	phyid;
E 3
D 4
	struct ife_dev	*lp = (struct ife_dev *)dp->private;
E 4
I 4
	struct ife_dev	*lp = dp->private;
E 4

D 3
	phyid = (gem_mii_read(dp, MII_PHYIDH) << 16)
	      |  gem_mii_read(dp, MII_PHYIDL);

	if ((phyid & 0xfffffff0) == 0x20005c00) {
E 3
I 3
	if ((dp->mii_phy_id & 0xfffffff0) == 0x20005c00) {
E 3
		/* configure DP83840/DP83840A */
		val = gem_mii_read(dp, 23);
		gem_mii_write(dp, 23, val | 0x0422 | 0x0100);
	}

D 3
	if (IS_i82558A_OR_LATER(lp->rev_id)) {
		dp->gc.gc_flow_control =
		    (gem_mii_read(dp, MII_AN_ADVERT) & MII_ABILITY_PAUSE) != 0
			? FLOW_CONTROL_RX_PAUSE : FLOW_CONTROL_NONE;
	}

E 3
	return (gem_mii_config_default(dp));
}

static void
ife_mii_sync(struct gem_dev *dp)
{
	/* do nothing */
}

static uint16_t
ife_mii_read(struct gem_dev *dp, uint_t reg)
{
	uint32_t	val;
	int		i;
D 4
	struct ife_dev	*lp = (struct ife_dev *)dp->private;
E 4
I 4
	struct ife_dev	*lp = dp->private;
E 4

	if (dp->mac_active &&
D 4
	   (ddi_get_lbolt() - lp->last_stats_time) > ONESEC) {
E 4
I 4
	    (ddi_get_lbolt() - lp->last_stats_time) > ONESEC) {
E 4
I 3
#if 1 /* for debug */
E 3
		ife_get_stats(dp);
I 3
#endif
E 3
		if (IS_i82557(lp->rev_id) &&
D 2
		    ((uint32_t *) dp->rx_ring)[SO_RxGoodFrames/4] == 0) {
E 2
I 2
D 4
		    ((uint32_t *) dp->io_area)[SO_RxGoodFrames/4] == 0) {
E 4
I 4
		    ((uint32_t *)dp->io_area)[SO_RxGoodFrames/4] == 0) {
E 4
E 2
			ife_send_op(dp, OP_MULTICAST);
		}
	}

D 4
	OUTL(dp, MDICTRL, 
		MC_OP_READ | (dp->mii_phy_addr << MC_PHYADD_SHIFT) |
		(reg << MC_REGADD_SHIFT));
E 4
I 4
	OUTL(dp, MDICTRL,
	    MC_OP_READ | (dp->mii_phy_addr << MC_PHYADD_SHIFT) |
	    (reg << MC_REGADD_SHIFT));
E 4
	FLUSH(dp);

	/* wait until done */
D 3
	i = 0;
	do {
		drv_usecwait(20);
		if (i++ > 100) {
			cmn_err(CE_CONT, "%s: mii_read: timeout: 0x%b",
				dp->name, val, MII_STATUS_BITS);
			return (0xffff);
E 3
I 3
	drv_usecwait(40);
	for (i = 0; (((val = INL(dp, MDICTRL)) & MC_R) == 0); i++) {
		if (i > 100) {
			cmn_err(CE_CONT, "!%s: %s: timeout: 0x%b",
D 4
				dp->name, __func__, val, MII_STATUS_BITS);
E 4
I 4
			    dp->name, __func__, val, MII_STATUS_BITS);
E 4
			return (0);
E 3
		}
D 3
	} while(((val = INL(dp, MDICTRL)) & MC_R) == 0);
	DPRINTF(4, (CE_CONT, "%s: mii_read: done: 0x%04x",
			dp->name, (uint16_t)val));
E 3
I 3
		drv_usecwait(20);
	}
	DPRINTF(4, (CE_CONT, "!%s: %s: done: 0x%04x",
D 4
			dp->name, __func__, (uint16_t)val));
E 4
I 4
	    dp->name, __func__, (uint16_t)val));
E 4
E 3
	return (val & MC_DATA);
}

static void
ife_mii_write(struct gem_dev *dp, uint_t reg, uint16_t val)
{
	int		i;

D 4
	OUTL(dp, MDICTRL, 
		MC_OP_WRITE | (dp->mii_phy_addr << MC_PHYADD_SHIFT) |
		(reg << MC_REGADD_SHIFT) | val);
E 4
I 4
	OUTL(dp, MDICTRL,
	    MC_OP_WRITE | (dp->mii_phy_addr << MC_PHYADD_SHIFT) |
	    (reg << MC_REGADD_SHIFT) | val);
E 4
	FLUSH(dp);

	i = 0;
	do {
		drv_usecwait(20);
		if (i++ > 100) {
D 4
			cmn_err(CE_WARN, "%s: ife_mii_write: timeout",
					dp->name);
E 4
I 4
			cmn_err(CE_WARN, "!%s: %s: timeout",
			    dp->name, __func__);
E 4
			return;
		}
D 4
	} while((INL(dp, MDICTRL) & MC_R) == 0);
I 2

E 2
	return;
E 4
I 4
	} while ((INL(dp, MDICTRL) & MC_R) == 0);
E 4
}

/* ======================================================== */
/*
 * OS depend (device driver) routine
 */
/* ======================================================== */
static int
ifeattach(dev_info_t *dip, ddi_attach_cmd_t cmd)
{
	int			unit;
	const char		*drv_name;
	int			i;
	ddi_acc_handle_t	conf_handle;
	int			vid;
	int			did;
	int			svid;
	int			ssid;
	uint8_t			revid;
	struct chip_info	*p;
	struct gem_dev		*dp;
	struct ife_dev		*lp;
	void			*base;
	ddi_acc_handle_t	regs_ha;
	struct gem_conf		*gcp;

D 4
	unit =  ddi_get_instance(dip);
E 4
I 4
	unit = ddi_get_instance(dip);
E 4
	drv_name = ddi_driver_name(dip);

D 3
	DPRINTF(3, (CE_CONT, "!%s%d: ifeattach: called", drv_name, unit));
E 3
I 3
	DPRINTF(3, (CE_CONT, "!%s%d: %s: called", drv_name, unit, __func__));
E 3

	/*
	 * Check if chip is supported.
	 */
	if (pci_config_setup(dip, &conf_handle) != DDI_SUCCESS) {
D 4
		cmn_err(CE_WARN, "%s: ddi_regs_map_setup failed",
			drv_name);
E 4
I 4
		cmn_err(CE_WARN, "!%s%d: %s: pci_config_setup failed",
		    drv_name, unit, __func__);
E 4
		goto err;
	}

D 4
	vid  = pci_config_get16(conf_handle, PCI_CONF_VENID);
	did  = pci_config_get16(conf_handle, PCI_CONF_DEVID);
E 4
I 4
	vid = pci_config_get16(conf_handle, PCI_CONF_VENID);
	did = pci_config_get16(conf_handle, PCI_CONF_DEVID);
E 4
	svid = pci_config_get16(conf_handle, PCI_CONF_SUBVENID);
	ssid = pci_config_get16(conf_handle, PCI_CONF_SUBSYSID);
D 4
	revid= pci_config_get8(conf_handle, PCI_CONF_REVID);
E 4
I 4
	revid = pci_config_get8(conf_handle, PCI_CONF_REVID);
E 4

D 4
	pci_config_put16(conf_handle, PCI_CONF_COMM, 
		PCI_COMM_IO | PCI_COMM_MAE | PCI_COMM_ME |
			pci_config_get16(conf_handle, PCI_CONF_COMM));
E 4
I 4
	pci_config_put16(conf_handle, PCI_CONF_COMM,
	    PCI_COMM_IO | PCI_COMM_MAE | PCI_COMM_ME |
	    pci_config_get16(conf_handle, PCI_CONF_COMM));
E 4

	/* ensure the pmr status is D0 mode */
	(void) gem_pci_set_power_state(dip, conf_handle, PCI_PMCSR_D0);

	pci_config_teardown(&conf_handle);

	switch (cmd) {
	case DDI_RESUME:
		return (gem_resume(dip));

	case DDI_ATTACH:
		for (i = 0, p = ife_chiptbl; i < CHIPTABLESIZE; i++, p++) {
			if (((p->venid == vid && p->devid == did) ||
D 4
			     (p->venid == svid && p->devid == ssid)) &&
E 4
I 4
			    (p->venid == svid && p->devid == ssid)) &&
E 4
			    (p->revmin <= revid && revid <= p->revmax)) {
				/* found */
				goto chip_found;
			}
		}

		/* Not found */
		cmn_err(CE_WARN,
D 4
			"%s: ife_attach: wrong PCI venid/devid (0x%x, 0x%x)",
			drv_name, vid, did);
E 4
I 4
		    "!%s%d: %s: wrong PCI venid/devid (0x%x, 0x%x)",
		    drv_name, unit, __func__, vid, did);
E 4
		goto err;
chip_found:
		cmn_err(CE_CONT,
D 4
			"!%s%d: %s (vid: 0x%04x, did: 0x%04x, revid: 0x%02x)",
			drv_name, unit, p->name, vid, did, revid);
E 4
I 4
		    "!%s%d: %s (vid: 0x%04x, did: 0x%04x, revid: 0x%02x)",
		    drv_name, unit, p->name, vid, did, revid);
E 4
		/* fix revision id */
		if (revid == 0xff) {
			revid = 1;
		}
		if (p->flags & ICH) {
			revid = REV_D101MA;
		}

		if (gem_pci_regs_map_setup(dip,
#ifdef MAP_MEM
D 4
			PCI_ADDR_MEM32, PCI_ADDR_MASK,
E 4
I 4
		    PCI_ADDR_MEM32, PCI_ADDR_MASK,
E 4
#else
D 4
			PCI_ADDR_IO, PCI_ADDR_MASK,
E 4
I 4
		    PCI_ADDR_IO, PCI_ADDR_MASK,
E 4
#endif
D 4
			&ife_dev_attr, (caddr_t *)&base, &regs_ha)
					!= DDI_SUCCESS) {
E 4
I 4
		    &ife_dev_attr, (void *)&base, &regs_ha)
		    != DDI_SUCCESS) {
E 4
			goto err;
		}

		/*
D 3
		/*
E 3
		 * construct gem configration
		 */
D 4
		gcp = (struct gem_conf *) kmem_zalloc(sizeof(*gcp), KM_SLEEP);
E 4
I 4
		gcp = kmem_zalloc(sizeof (*gcp), KM_SLEEP);
E 4

		/* name */
		sprintf(gcp->gc_name, "%s%d", drv_name, unit);

		/* consistency on tx and rx */
D 4
		gcp->gc_tx_buf_align = sizeof(uint8_t) - 1;
		gcp->gc_tx_max_frags = GEM_MAXTXFRAGS;
E 4
I 4
		gcp->gc_tx_buf_align = sizeof (uint8_t) - 1;
		gcp->gc_tx_max_frags = MAXTXFRAGS;
E 4
		gcp->gc_tx_max_descs_per_pkt = 1;
		gcp->gc_tx_desc_unit_shift = 7;	/* 128 byte */
D 4
		gcp->gc_tx_buf_size  = TX_BUF_SIZE;
		gcp->gc_tx_buf_limit = gcp->gc_tx_buf_size-1;
E 4
I 4
		gcp->gc_tx_buf_size = TX_BUF_SIZE;
D 5
		gcp->gc_tx_buf_limit = gcp->gc_tx_buf_size - 1;
E 5
I 5
		gcp->gc_tx_buf_limit = gcp->gc_tx_buf_size;
E 5
E 4
		gcp->gc_tx_ring_size = TX_RING_SIZE;
D 4
		gcp->gc_tx_ring_limit= gcp->gc_tx_ring_size-1;
		gcp->gc_tx_auto_pad  = B_FALSE;
E 4
I 4
		gcp->gc_tx_ring_limit = gcp->gc_tx_ring_size - 1;
		gcp->gc_tx_auto_pad = B_FALSE;
E 4
		gcp->gc_tx_copy_thresh = ife_tx_copy_thresh;
		gcp->gc_tx_desc_write_oo = B_FALSE;

D 4
		gcp->gc_rx_buf_align = sizeof(uint8_t)-1;
E 4
I 4
		gcp->gc_rx_buf_align = sizeof (uint8_t) - 1;
E 4
		gcp->gc_rx_max_frags = 1;
D 2
		gcp->gc_rx_desc_unit_shift = 2; /* no rx desc */
E 2
I 2
		gcp->gc_rx_desc_unit_shift = -1; /* no rx desc */
E 2
D 5
		gcp->gc_rx_ring_size = RX_RING_SIZE;
E 5
I 5
		gcp->gc_rx_ring_size = RX_BUF_SIZE;
E 5
D 2
		gcp->gc_rx_buf_max  = gcp->gc_rx_ring_size - 1;
E 2
I 2
D 4
		gcp->gc_rx_buf_max   = gcp->gc_rx_ring_size - 1;
E 4
I 4
		gcp->gc_rx_buf_max = gcp->gc_rx_ring_size - 1;
E 4
E 2
		gcp->gc_rx_copy_thresh = ife_rx_copy_thresh;
D 4
		gcp->gc_rx_header_len= sizeof(struct rfd);
E 4
I 4
		gcp->gc_rx_header_len = sizeof (struct rfd);
E 4

		gcp->gc_io_area_size = MAX_STATISTICS_SIZE;

		/* map attributes */
D 2
		STRUCT_COPY(gcp->gc_dev_attr, ife_dev_attr);
		STRUCT_COPY(gcp->gc_buf_attr, ife_buf_attr);
		STRUCT_COPY(gcp->gc_desc_attr, ife_buf_attr);
E 2
I 2
		gcp->gc_dev_attr = ife_dev_attr;
		gcp->gc_buf_attr = ife_buf_attr;
		gcp->gc_desc_attr = ife_buf_attr;
E 2

		/* dma attributes */
D 2
		STRUCT_COPY(gcp->gc_dma_attr_desc, ife_dma_attr_desc);
		STRUCT_COPY(gcp->gc_dma_attr_txbuf, ife_dma_attr_txbuf);
		STRUCT_COPY(gcp->gc_dma_attr_rxbuf, ife_dma_attr_rxbuf);
E 2
I 2
		gcp->gc_dma_attr_desc = ife_dma_attr_desc;
		gcp->gc_dma_attr_txbuf = ife_dma_attr_txbuf;
		gcp->gc_dma_attr_rxbuf = ife_dma_attr_rxbuf;
E 2

		/* time out parameters */
D 5
		gcp->gc_tx_timeout = 3*ONESEC;
		gcp->gc_tx_timeout_interval = ONESEC;
E 5
I 5
		gcp->gc_tx_timeout = GEM_TX_TIMEOUT;
		gcp->gc_tx_timeout_interval = GEM_TX_TIMEOUT_INTERVAL;
E 5

		/* flow control */
D 3
#ifdef notdef
E 3
		gcp->gc_flow_control = IS_i82558A_OR_LATER(revid)
D 4
				? FLOW_CONTROL_RX_PAUSE : FLOW_CONTROL_NONE;
E 4
I 4
		    ? FLOW_CONTROL_RX_PAUSE : FLOW_CONTROL_NONE;
E 4
D 3
#endif
E 3
I 3

E 3
		/* MII timeout parameters */
D 5
		gcp->gc_mii_link_watch_interval = ONESEC;
D 4
		gcp->gc_mii_an_watch_interval   = ONESEC/5;
E 4
I 4
		gcp->gc_mii_an_watch_interval = ONESEC/5;
E 5
I 5
		gcp->gc_mii_link_watch_interval =GEM_LINK_WATCH_INTERVAL;
		gcp->gc_mii_an_watch_interval = GEM_LINK_WATCH_INTERVAL/5;
E 5
E 4
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
		gcp->gc_mii_an_oneshot = B_FALSE;

		/* I/O methods */

		/* mac operation */
		gcp->gc_attach_chip = &ife_attach_chip;
D 4
		gcp->gc_reset_chip  = &ife_reset_chip;
		gcp->gc_init_chip   = &ife_init_chip;
		gcp->gc_start_chip  = &ife_start_chip;
		gcp->gc_stop_chip   = &ife_stop_chip;
E 4
I 4
		gcp->gc_reset_chip = &ife_reset_chip;
		gcp->gc_init_chip = &ife_init_chip;
		gcp->gc_start_chip = &ife_start_chip;
		gcp->gc_stop_chip = &ife_stop_chip;
E 4
		gcp->gc_multicast_hash = NULL;
		gcp->gc_set_rx_filter = &ife_set_rx_filter;
D 4
		gcp->gc_set_media   = &ife_set_media;
		gcp->gc_get_stats   = &ife_get_stats;
		gcp->gc_interrupt   = &ife_interrupt;
E 4
I 4
		gcp->gc_set_media = &ife_set_media;
		gcp->gc_get_stats = &ife_get_stats;
		gcp->gc_interrupt = &ife_interrupt;
E 4

		/* descriptor operation */
		gcp->gc_tx_desc_write = &ife_cmd_desc_write;
		gcp->gc_rx_desc_write = &ife_rx_desc_write;
D 4
		gcp->gc_tx_start      = &ife_cmd_start;
D 2
		gcp->gc_rx_start      = NULL;
E 2
I 2
		gcp->gc_rx_start      = &ife_rx_start;
E 4
I 4
		gcp->gc_tx_start = &ife_cmd_start;
		gcp->gc_rx_start = &ife_rx_start;
E 4
E 2

		gcp->gc_tx_desc_init = &ife_cmd_desc_init;
		gcp->gc_rx_desc_init = &ife_rx_desc_init;
		gcp->gc_tx_desc_stat = &ife_cmd_desc_stat;
		gcp->gc_rx_desc_stat = &ife_rx_desc_stat;
		gcp->gc_tx_desc_clean = &ife_cmd_desc_init;
		gcp->gc_rx_desc_clean = &ife_rx_desc_init;

		/* mii operations */
D 3
		gcp->gc_mii_init  = &gem_mii_init_default;
E 3
I 3
		gcp->gc_mii_probe = &gem_mii_probe_default;
D 4
		gcp->gc_mii_init  = NULL;
E 4
I 4
		gcp->gc_mii_init = NULL;
E 4
E 3
		gcp->gc_mii_config = &ife_mii_config;
D 4
		gcp->gc_mii_sync  = &ife_mii_sync;
		gcp->gc_mii_read  = &ife_mii_read;
E 4
I 4
		gcp->gc_mii_sync = &ife_mii_sync;
		gcp->gc_mii_read = &ife_mii_read;
E 4
		gcp->gc_mii_write = &ife_mii_write;
		gcp->gc_mii_tune_phy = NULL;

I 5
		/* MSI/MSIX interrupts */
		gcp->gc_nintrs_req = 1;

		gcp->gc_default_mtu = ETHERMTU;
		gcp->gc_max_mtu = IFE_MAX_MTU - 4;
		gcp->gc_min_mtu = ETHERMIN - sizeof (struct ether_header);

E 5
D 4
		lp = kmem_zalloc(sizeof(struct ife_dev), KM_SLEEP);
E 4
I 4
		lp = kmem_zalloc(sizeof (struct ife_dev), KM_SLEEP);
E 4

		lp->rev_id = revid;
		lp->hw_info = p;
I 5
		mutex_init(&lp->reglock, NULL, MUTEX_DRIVER, NULL);

E 5
D 3
		dp = gem_do_attach(dip, gcp, base, &regs_ha,
E 3
I 3
D 4
		dp = gem_do_attach(dip, 0, gcp, base, &regs_ha,
E 3
					lp, sizeof(*lp));
E 4
I 4
		dp = gem_do_attach(dip, 0,
		    gcp, base, &regs_ha, lp, sizeof (*lp));
E 4

D 4
		kmem_free(gcp, sizeof(*gcp));
E 4
I 4
		kmem_free(gcp, sizeof (*gcp));
E 4

D 4
		if (dp != NULL) {
E 4
I 4
		if (dp) {
E 4
			return (DDI_SUCCESS);
		}
I 5

		mutex_destroy(&lp->reglock);
E 5
err_free_mem:
D 4
		kmem_free(lp, sizeof(struct ife_dev));
E 4
I 4
		kmem_free(lp, sizeof (struct ife_dev));
E 4
err:
		return (DDI_FAILURE);
	}
	return (DDI_FAILURE);
}

static int
ifedetach(dev_info_t *dip, ddi_detach_cmd_t cmd)
{
	int	ret;
I 5
	struct gem_dev	*dp;
	struct ife_dev	*lp;
E 5

I 5
	dp = GEM_GET_DEV(dip);
	lp = dp->private;

E 5
	switch (cmd) {
	case DDI_SUSPEND:
		return (gem_suspend(dip));

	case DDI_DETACH:
I 5

		/* free driver depend resource */
		mutex_destroy(&lp->reglock);

E 5
		return (gem_do_detach(dip));
	}
	return (DDI_FAILURE);
}

/* ======================================================== */
/*
 * OS depend (loadable streams driver) routine
 */
/* ======================================================== */
I 4
#ifdef GEM_CONFIG_GLDv3
D 5
DDI_DEFINE_STREAM_OPS(ife_ops, nulldev, nulldev, ifeattach, ifedetach,
    nodev, NULL, D_MP, NULL);
E 5
I 5
GEM_STREAM_OPS(ife_ops, ifeattach, ifedetach);
E 5
#else
E 4
static	struct module_info ifeminfo = {
	0,			/* mi_idnum */
	"ife",			/* mi_idname */
	0,			/* mi_minpsz */
D 3
	IFE_MAX_MTU,		/* mi_maxpsz */
	IFE_MAX_MTU*TX_BUF_SIZE,/* mi_hiwat */
E 3
I 3
	INFPSZ,			/* mi_maxpsz */
	64 * 1024,		/* mi_hiwat */
E 3
	1,			/* mi_lowat */
};

static	struct qinit iferinit = {
	(int (*)()) NULL,	/* qi_putp */
	gem_rsrv,		/* qi_srvp */
	gem_open,		/* qi_qopen */
	gem_close,		/* qi_qclose */
	(int (*)()) NULL,	/* qi_qadmin */
	&ifeminfo,		/* qi_minfo */
	NULL,			/* qi_mstat */
};

static	struct qinit ifewinit = {
	gem_wput,		/* qi_putp */
	gem_wsrv,		/* qi_srvp */
	(int (*)()) NULL,	/* qi_qopen */
	(int (*)()) NULL,	/* qi_qclose */
	(int (*)()) NULL,	/* qi_qadmin */
	&ifeminfo,		/* qi_minfo */
	NULL,			/* qi_mstat */
};

static struct streamtab	ife_info = {
	&iferinit,	/* st_rdinit */
	&ifewinit,	/* st_wrinit */
	NULL,		/* st_muxrinit */
	NULL,		/* st_muxwrinit */
};

static	struct cb_ops cb_ife_ops = {
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
	&ife_info,	/* cb_stream */
D 3
	D_NEW|D_MP,	/* cb_flag */
E 3
I 3
	D_MP,		/* cb_flag */
E 3
};

static	struct dev_ops ife_ops = {
	DEVO_REV,	/* devo_rev */
	0,		/* devo_refcnt */
	gem_getinfo,	/* devo_getinfo */
	nulldev,	/* devo_identify */
	nulldev,	/* devo_probe */
	ifeattach,	/* devo_attach */
	ifedetach,	/* devo_detach */
	nodev,		/* devo_reset */
	&cb_ife_ops,	/* devo_cb_ops */
	NULL,		/* devo_bus_ops */
	ddi_power,	/* devo_power */
};
I 4
#endif
E 4

static struct modldrv modldrv = {
	&mod_driverops,	/* Type of module.  This one is a driver */
	ident,
	&ife_ops,	/* driver ops */
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
D 4
	int 	status;
E 4
I 4
	int	status;
E 4

	DPRINTF(2, (CE_CONT, "!ife: _init: called"));
	gem_mod_init(&ife_ops, "ife");
	status = mod_install(&modlinkage);
	if (status != DDI_SUCCESS) {
		gem_mod_fini(&ife_ops);
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

	DPRINTF(2, (CE_CONT, "!ife: _fini: called"));
	status = mod_remove(&modlinkage);
	if (status == DDI_SUCCESS) {
		gem_mod_fini(&ife_ops);
	}
	return (status);
}

int
_info(struct modinfo *modinfop)
{
	return (mod_info(&modlinkage, modinfop));
}
E 1
