h28494
s 00138/00056/01576
d D 1.13 10/05/14 21:39:25 mrym 13 12
c 2.6.4
e
s 00016/00005/01616
d D 1.12 09/06/08 21:57:26 mrym 12 11
c 2.6.3, giga bit ether support
e
s 00001/00002/01620
d D 1.11 08/12/17 03:59:50 mrym 11 10
c 2.6.3
e
s 00005/00024/01617
d D 1.10 08/06/08 22:48:31 mrym 10 9
c 2.6.1
e
s 00051/00046/01590
d D 1.9 08/04/06 12:44:02 mrym 9 8
c 2.6.2
e
s 00348/00376/01288
d D 1.8 08/02/26 01:56:15 mrym 8 7
c 2.6.1 for sis191
e
s 00005/00001/01659
d D 1.7 07/10/14 11:47:23 mrym 7 6
c missing flush after writing imr and isr
e
s 00003/00001/01657
d D 1.6 07/10/08 22:16:17 mrym 6 5
c inside comment problem fixed
e
s 00130/00132/01528
d D 1.5 07/09/29 17:34:09 mrym 5 4
c 2.6.0
e
s 00006/00007/01654
d D 1.4 02/01/01 04:03:28 mrym 4 3
c STRUCT_COPY removed
e
s 00037/00021/01624
d D 1.3 06/12/22 01:02:19 mrym 3 2
c 2.4.1
e
s 00362/00233/01283
d D 1.2 06/07/16 23:48:42 mrym 2 1
c 2.2.0
e
s 01516/00000/00000
d D 1.1 06/03/11 15:14:18 mrym 1 0
c date and time created 06/03/11 15:14:18 by mrym
e
u
U
f e 0
t
T
I 1
/*
D 8
 *  sige_gem.c : SiS190/191 integrated fast/giga ethernet MAC driver for Solaris
E 8
I 8
 * sige_gem.c : SiS190/191 integrated fast/giga ethernet MAC driver for Solaris
E 8
 *
D 8
 * Copyright (c) 2005-2006 Masayuki Murayama.  All rights reserved.
 * 
E 8
I 8
D 12
 * Copyright (c) 2005-2008 Masayuki Murayama.  All rights reserved.
E 12
I 12
D 13
 * Copyright (c) 2005-2009 Masayuki Murayama.  All rights reserved.
E 13
I 13
 * Copyright (c) 2005-2010 Masayuki Murayama.  All rights reserved.
E 13
E 12
 *
E 8
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
D 8
 * 
E 8
I 8
 *
E 8
 * 1. Redistributions of source code must retain the above copyright notice,
D 8
 *    this list of conditions and the following disclaimer. 
 * 
E 8
I 8
 *    this list of conditions and the following disclaimer.
 *
E 8
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
D 8
 *    and/or other materials provided with the distribution. 
 * 
E 8
I 8
 *    and/or other materials provided with the distribution.
 *
E 8
 * 3. Neither the name of the author nor the names of its contributors may be
 *    used to endorse or promote products derived from this software without
D 8
 *    specific prior written permission. 
 * 
E 8
I 8
 *    specific prior written permission.
 *
E 8
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
D 8
#pragma	ident	"%W% %E%"
E 8
I 8
#pragma	ident	"%Z%%M% %I%     %E%"
E 8

/*
I 2
D 8
 CHANGE LOG:
  03/23/2006  dditypes.h added, ddi_impledefs.h removed
I 5
  09/29/2007  2.6.0
E 5
D 7

E 7
I 7
  10/14/2007  missing flush after writing imr and isr
E 7
E 2
 */

/*
 TODO:
 */

/*
E 8
 * System Header files.
 */
#include <sys/types.h>
#include <sys/conf.h>
#include <sys/debug.h>
D 8
#include <sys/stropts.h>
#include <sys/stream.h>
#include <sys/strlog.h>
E 8
#include <sys/kmem.h>
D 8
#include <sys/stat.h>
#include <sys/kstat.h>
#include <sys/vtrace.h>
#include <sys/dlpi.h>
#include <sys/strsun.h>
#include <sys/ethernet.h>
E 8
#include <sys/modctl.h>
#include <sys/errno.h>
I 2
D 8
#include <sys/dditypes.h>
E 8
E 2
#include <sys/ddi.h>
#include <sys/sunddi.h>
D 2
#include <sys/ddi_impldefs.h>
E 2
D 5

E 5
#include <sys/byteorder.h>
D 8

E 8
I 8
#include <sys/ethernet.h>
E 8
#include <sys/pci.h>
I 8

E 8
D 5
#include "mii.h"
E 5
I 5
#include "gem_mii.h"
E 5
#include "gem.h"
#include "sis190reg.h"

D 2
char	ident[] = "sis190/191 driver " VERSION;
E 2
I 2
char	ident[] = "sis190/191 driver v" VERSION;
E 2

/* Debugging support */
#ifdef DEBUG_LEVEL
static int sige_debug = DEBUG_LEVEL;
D 8
# if DEBUG_LEVEL > 4
#    define	CONS	"^"
#  else
#    define	CONS	"!"
#  endif
#define	DPRINTF(n, args)	if (sige_debug>(n)) cmn_err args
E 8
I 8
#if DEBUG_LEVEL > 4
#define	CONS	"^"
E 8
#else
#define	CONS	"!"
I 8
#endif
#define	DPRINTF(n, args)	if (sige_debug > (n)) cmn_err args
#else
#define	CONS	"!"
E 8
#define	DPRINTF(n, args)
#endif

/*
 * Useful macros and typedefs
 */
#define	ONESEC			(drv_usectohz(1*1000000))

#define	ROUNDUP(x, a)		(((x) + (a) - 1) & ~((a) - 1))
D 4
#define	STRUCT_COPY(a, b)	bcopy(&(b), &(a), sizeof(a))
E 4

#ifdef MAP_MEM
D 8
#define	FLSHB(dp,reg)		INB(dp, reg)
#define	FLSHW(dp,reg)		INW(dp, reg)
#define	FLSHL(dp,reg)		INL(dp, reg)
E 8
I 8
#define	FLSHB(dp, reg)		INB(dp, reg)
#define	FLSHW(dp, reg)		INW(dp, reg)
#define	FLSHL(dp, reg)		INL(dp, reg)
E 8
#else
D 8
#define	FLSHB(dp,reg)
#define	FLSHW(dp,reg)
#define	FLSHL(dp,reg)
E 8
I 8
#define	FLSHB(dp, reg)
#define	FLSHW(dp, reg)
#define	FLSHL(dp, reg)
E 8
#endif /* MAP_MEM */

I 8
#define	PHY_ID_MARVELL88E1111	0x01410cc1
#define	PHY_ID_BCM5461_1	0x00206021

I 13
#ifdef GEM3
#define	IS_MAC_ONLINE(dp)	((dp)->mac_state == MAC_STATE_ONLINE)
#else
#define	IS_MAC_ONLINE(dp)	((dp)->mac_active)
#endif
E 13
E 8
D 3
/*
 * As sis190/191 is builtin-nic in x86 south brigde,
 * no need to define swap functions for other archtectures.
 */
D 2
#define	LE64(x)	(x)
#define	LE32(x)	(x)
#define	LE16(x)	(x)
E 2
I 2
#define	LE64(x)	((uint64_t) (x))
#define	LE32(x)	((uint32_t) (x))
#define	LE16(x)	((uint16_t) (x))
E 3
I 3
D 5
#if defined(sun4u)
# define LE16(x)	ddi_swap16(x)
# define LE32(x)	ddi_swap32(x)
# define LE64(x)	ddi_swap64(x)
#else
# define LE16(x)	((uint16_t) (x))
# define LE32(x)	((uint32_t) (x))
# define LE64(x)	((uint64_t) (x))
#endif
E 3
E 2

E 5
/*
 * Our configuration
 */
#ifndef	TX_BUF_SIZE
#define	TX_BUF_SIZE	64
#endif
#ifndef	TX_RING_SIZE
D 13
#define	TX_RING_SIZE	TX_BUF_SIZE
E 13
I 13
#define	TX_RING_SIZE	256
E 13
#endif

#ifndef	RX_BUF_SIZE
D 5
#define	RX_BUF_SIZE	64
E 5
I 5
#define	RX_BUF_SIZE	256
E 5
#endif
#ifndef	RX_RING_SIZE
#define	RX_RING_SIZE	RX_BUF_SIZE
#endif

D 2
#define	MAXTXFRAGS	1
E 2
I 2
D 5
#define	MAXTXFRAGS	1	
E 5
I 5
D 13
#define	MAXTXFRAGS	1	/* GEM_MAXTXFRAGS */
E 13
I 13
#define	MAXTXFRAGS	(min(8, GEM_MAXTXFRAGS))
E 13
E 5
E 2
#define	MAXRXFRAGS	1

D 8
#define	OUR_INTR_BITS	(INT_LINK | \
			 INT_RXIDLE | INT_RXDONE | INT_TXDONE | \
			 INT_TXHALT | INT_RXHALT)
E 8
I 8
#define	OUR_INTR_BITS	( \
	INT_LINK | \
	INT_RXIDLE | INT_RXDONE | INT_TXDONE | \
	INT_TXHALT | INT_RXHALT \
)
E 8

static int	sige_tx_copy_thresh = 256;
static int	sige_rx_copy_thresh = 256;

/*
 * Supported chips
 */
struct chip_info {
	uint16_t	venid;
	uint16_t	devid;
	char		*chip_name;
D 5
	int		chip_type;
#define	CHIPTYPE_SIS190		0
#define	CHIPTYPE_SIS191		1
E 5
};

/*
 * Chip dependant MAC state
 */
struct sige_dev {
	/* misc HW information */
	struct chip_info	*chip;
	boolean_t		phy_rgmii;
	boolean_t		mac_in_apc;

	uint32_t		tx_desc_flags;

	/* register shadows */
	uint32_t		our_intr_bits;
	uint32_t		tx_control;
	uint32_t		rx_control;
I 2
	uint8_t			mac_addr[ETHERADDRL];
	uint16_t		rx_mac_ctrl;

	boolean_t		tx_running;
D 10
	boolean_t		rx_running;
E 10
E 2
};

/*
 * Hardware information
 */
struct chip_info sige_chiptbl[] = {
D 5
	0x1039,	0x0190,	"SiS190", CHIPTYPE_SIS190,
	0x1039,	0x0191,	"SiS191", CHIPTYPE_SIS191,
E 5
I 5
	0x1039,	0x0190,	"SiS190",
	0x1039,	0x0191,	"SiS191",
E 5
};
D 8
#define	CHIPTABLESIZE	(sizeof(sige_chiptbl)/sizeof(struct chip_info))
E 8
I 8
#define	CHIPTABLESIZE	(sizeof (sige_chiptbl)/sizeof (struct chip_info))
E 8

/* ======================================================== */
D 8
 
E 8
I 8

E 8
/* mii operations */
static void  sige_mii_sync(struct gem_dev *);
static uint16_t  sige_mii_read(struct gem_dev *, uint_t);
static void sige_mii_write(struct gem_dev *, uint_t, uint16_t);
/* nic operations */
static int sige_reset_chip(struct gem_dev *);
D 3
static void sige_init_chip(struct gem_dev *);
static void sige_start_chip(struct gem_dev *);
E 3
I 3
static int sige_init_chip(struct gem_dev *);
static int sige_start_chip(struct gem_dev *);
E 3
D 2
static void sige_stop_chip(struct gem_dev *);
E 2
I 2
static int sige_stop_chip(struct gem_dev *);
E 2
D 3
static void sige_set_media(struct gem_dev *);
static void sige_set_rx_filter(struct gem_dev *);
static void sige_get_stats(struct gem_dev *);
E 3
I 3
static int sige_set_media(struct gem_dev *);
static int sige_set_rx_filter(struct gem_dev *);
static int sige_get_stats(struct gem_dev *);
E 3
static int sige_attach_chip(struct gem_dev *);

/* descriptor operations */
static int sige_tx_desc_write(struct gem_dev *dp, int slot,
D 5
		    ddi_dma_cookie_t *dmacookie, int frags, uint32_t intreq);
E 5
I 5
D 8
		    ddi_dma_cookie_t *dmacookie, int frags, uint64_t intreq);
E 8
I 8
	ddi_dma_cookie_t *dmacookie, int frags, uint64_t intreq);
E 8
E 5
static void sige_tx_start(struct gem_dev *dp, int slot, int frags);
static void sige_rx_desc_write(struct gem_dev *dp, int slot,
D 8
		    ddi_dma_cookie_t *dmacookie, int frags);
E 8
I 8
	ddi_dma_cookie_t *dmacookie, int frags);
E 8
D 10
static void sige_rx_start(struct gem_dev *dp, int slot, int frags);
E 10
static uint_t sige_tx_desc_stat(struct gem_dev *dp, int slot, int ndesc);
static uint64_t sige_rx_desc_stat(struct gem_dev *dp, int slot, int ndesc);

static void sige_tx_desc_init(struct gem_dev *dp, int slot);
static void sige_rx_desc_init(struct gem_dev *dp, int slot);

/* interrupt handler */
D 8
static u_int sige_interrupt(struct gem_dev *dp);
E 8
I 8
static uint_t sige_interrupt(struct gem_dev *dp);
E 8

/* ======================================================== */

/* mapping attributes */
/* Data access requirements. */
static struct ddi_device_acc_attr sige_dev_attr = {
	DDI_DEVICE_ATTR_V0,
	DDI_STRUCTURE_LE_ACC,
	DDI_STRICTORDER_ACC
};

/* On sparc, the buffers should be native endianness */
static struct ddi_device_acc_attr sige_buf_attr = {
	DDI_DEVICE_ATTR_V0,
	DDI_NEVERSWAP_ACC,	/* native endianness */
	DDI_STRICTORDER_ACC
};

static ddi_dma_attr_t sige_dma_attr_buf = {
	DMA_ATTR_V0,		/* dma_attr_version */
	0,			/* dma_attr_addr_lo */
	0xffffffffull,		/* dma_attr_addr_hi */
	0xffffffffull,		/* dma_attr_count_max */
	0, /* patched later */	/* dma_attr_align */
	0,			/* dma_attr_burstsizes */
	1,			/* dma_attr_minxfer */
	0xffffffffull,		/* dma_attr_maxxfer */
	0xffffffffull,		/* dma_attr_seg */
	0, /* patched later */	/* dma_attr_sgllen */
	1,			/* dma_attr_granular */
	0			/* dma_attr_flags */
};

static ddi_dma_attr_t sige_dma_attr_desc = {
	DMA_ATTR_V0,		/* dma_attr_version */
	0,			/* dma_attr_addr_lo */
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
static uint16_t
sige_read_eeprom(struct gem_dev *dp, int offset)
{
	int		i;
	uint32_t	ret;
	ASSERT(offset <= EI_OFFSET);
D 2
	OUTL(dp, EepIntf,
		EI_REQ | EI_OP_RD | (offset << EI_OFFSET_SHIFT));
E 2
I 2
	OUTL(dp, ROMCMD, EI_REQ | EI_OP_RD | (offset << EI_OFFSET_SHIFT));
E 2
	drv_usecwait(500);

D 2
	for (i = 0; ((ret = INL(dp, EepIntf)) & EI_REQ) != 0; i++) {		
E 2
I 2
D 5
	for (i = 0; ((ret = INL(dp, ROMCMD)) & EI_REQ) != 0; i++) {
E 2
		if (i > 1000) {
E 5
I 5
	i = 0;
	while ((ret = INL(dp, ROMCMD)) & EI_REQ) {
		if (i++ > 1000) {
E 5
			/* timeout */
D 5
			cmn_err(CE_WARN, "%s: %s: timeout", dp->name, __func__);
E 5
I 5
			cmn_err(CE_WARN, "!%s: %s: timeout",
D 8
				dp->name, __func__);
E 8
I 8
			    dp->name, __func__);
E 8
E 5
D 2
			return 0xffff;
E 2
I 2
			return (0xffff);
E 2
		}
		drv_usecwait(100);
	}

	return ((ret & EI_DATA) >> EI_DATA_SHIFT);
}

D 2
static boolean_t
E 2
I 2
static int
E 2
sige_get_mac_addr_eeprom(struct gem_dev *dp)
{
	int		i;
	uint16_t	val;
	uint8_t		*mac;
D 8
	struct sige_dev	*lp = (struct sige_dev *) dp->private;
	
E 8
I 8
	struct sige_dev	*lp = dp->private;

	DPRINTF(0, (CE_CONT, "!%s: %s called", dp->name, __func__));

E 8
	val = sige_read_eeprom(dp, EEPROMSignature);

	if (val == 0xffff || val == 0x0000) {
D 5
		cmn_err(CE_WARN, "%s: invalid eeprom signature (%x)",
E 5
I 5
		cmn_err(CE_WARN, "!%s: invalid eeprom signature (%x)",
E 5
D 8
			dp->name, val);
E 8
I 8
		    dp->name, val);
E 8
D 2
		return B_FALSE;
E 2
I 2
		return (GEM_FAILURE);
E 2
	}

	mac = dp->dev_addr.ether_addr_octet;

	for (i = 0; i < ETHERADDRL; i += 2) {
		val = sige_read_eeprom(dp, EEPROMMACAddr + i/2);
D 8
		mac[i + 0] = (uint8_t) val;
		mac[i + 1] = (uint8_t) (val >> 8);
E 8
I 8
		mac[i + 0] = (uint8_t)val;
		mac[i + 1] = (uint8_t)(val >> 8);
E 8
	}

	/* check RGMII/GMII mode */
	lp->phy_rgmii = (sige_read_eeprom(dp, EEPROMInfo) & 0x80) != 0;

D 2
	return B_TRUE;
E 2
I 2
	return (GEM_SUCCESS);
E 2
}

D 2
/* DONE */
E 2
static dev_info_t *
sige_search_pci_dev_subr(dev_info_t *cur_node,
D 10
	uint_t vendor_id, uint_t device_id)
E 10
I 10
    uint_t vendor_id, uint_t device_id)
E 10
{
	dev_info_t	*child_id;
	dev_info_t	*ret;
	uint_t		vid, did;

	ASSERT(cur_node != NULL);

	/* check brothers */
	do {
D 2
		vid = ddi_getprop(DDI_DEV_T_ANY, cur_node,
E 2
I 2
		vid = ddi_prop_get_int(DDI_DEV_T_ANY, cur_node,
E 2
D 8
					DDI_PROP_DONTPASS, "vendor-id", -1);
E 8
I 8
		    DDI_PROP_DONTPASS, "vendor-id", -1);
E 8
D 2
		did = ddi_getprop(DDI_DEV_T_ANY, cur_node,
E 2
I 2
		did = ddi_prop_get_int(DDI_DEV_T_ANY, cur_node,
E 2
D 8
					DDI_PROP_DONTPASS, "device-id", -1);
E 8
I 8
		    DDI_PROP_DONTPASS, "device-id", -1);
E 8

		if (vid == vendor_id && did == device_id) {
			/* found */
D 2
			return cur_node;
E 2
I 2
			return (cur_node);
E 2
		}

		/* check children */
		if ((child_id = ddi_get_child(cur_node)) != NULL) {
			if ((ret = sige_search_pci_dev_subr(
D 8
				child_id, vendor_id, device_id)) != NULL) {
E 8
I 8
			    child_id, vendor_id, device_id)) != NULL) {
E 8
D 2
				return ret;
E 2
I 2
				return (ret);
E 2
			}
		}

	} while ((cur_node = ddi_get_next_sibling(cur_node)) != NULL);

	/* not found */
D 2
	return NULL;
E 2
I 2
	return (NULL);
E 2
}

D 2
/* DONE */
E 2
static dev_info_t *
sige_search_pci_dev(int vendor_id, int device_id)
{
D 8
	return sige_search_pci_dev_subr(ddi_root_node(), vendor_id, device_id);
E 8
I 8
	return (sige_search_pci_dev_subr(
	    ddi_root_node(), vendor_id, device_id));
E 8
}

D 2
/* DONE */
static boolean_t
E 2
I 2
static int
E 2
sige_get_mac_addr_apc(struct gem_dev *dp)
{
	int		i;
D 8
        uint_t		reg;
        dev_info_t	*isa_bridge;
        ddi_acc_handle_t isa_handle;
	struct sige_dev	*lp = (struct sige_dev *) dp->private;
E 8
I 8
	uint_t		reg;
	dev_info_t	*isa_bridge;
	ddi_acc_handle_t isa_handle;
	struct sige_dev	*lp = dp->private;
E 8

D 8
	if ((isa_bridge = sige_search_pci_dev(0x1039, 0x965)) == NULL) {
D 2
		cmn_err(CE_WARN,
			"%s: failed to find pci1039,965 isa bridge",
				dp->name);
		return B_FALSE;
E 2
I 2
		cmn_err(CE_WARN, "!%s: failed to find pci1039,965 isa bridge",
			dp->name);
		return (GEM_FAILURE);
E 8
I 8
	DPRINTF(0, (CE_CONT, "!%s: %s called", dp->name, __func__));

	if (isa_bridge = sige_search_pci_dev(0x1039, 0x965)) {
		goto found;
E 8
E 2
	}
I 8
	if (isa_bridge = sige_search_pci_dev(0x1039, 0x966)) {
		goto found;
	}
	if (isa_bridge = sige_search_pci_dev(0x1039, 0x968)) {
		goto found;
	}
E 8

I 8
	cmn_err(CE_WARN, "!%s: %s: isa bridge not found",
	    dp->name, __func__);
	return (GEM_FAILURE);

found:
E 8
	if (pci_config_setup(isa_bridge, &isa_handle) != DDI_SUCCESS) {
D 2
		cmn_err(CE_WARN, "%s: %s: ddi_regs_map_setup failed",
E 2
I 2
D 8
		cmn_err(CE_WARN, "!%s: %s: ddi_regs_map_setup failed",
E 2
			dp->name, __func__);
E 8
I 8
D 9
		cmn_err(CE_WARN, "!%s: %s: pci?config_setup failed",
E 9
I 9
		cmn_err(CE_WARN, "!%s: %s: pci_config_setup failed",
E 9
		    dp->name, __func__);
E 8
D 2
		return B_FALSE;
E 2
I 2
		return (GEM_FAILURE);
E 2
	}

D 2
	/* enable port 0x78 & 0x79 to access apc registgers */
E 2
I 2
	/* enable port 0x78 & 0x79 to access APC registgers */
E 2
	reg = pci_config_get8(isa_handle, 0x48);
	pci_config_put8(isa_handle, 0x48, reg & ~0x02);
I 8
	drv_usecwait(50);
	(void) pci_config_get8(isa_handle, 0x48);
E 8

I 8
	/* get factory mac addresss */
E 8
	for (i = 0; i < ETHERADDRL; i++) {
		outb(0x78, 0x09 + i);
D 8
		dp->dev_addr.ether_addr_octet[i] = inb(0x79); 
E 8
I 8
		dp->dev_addr.ether_addr_octet[i] = inb(0x79);
E 8
	}

	/* check MII/RGMII */
	outb(0x78, 0x12);
D 5
	lp->phy_rgmii = (inb(0x79) & 0x80) != 0;
E 5
I 5
	lp->phy_rgmii = ((inb(0x79) & 0x80) != 0);
E 5

D 2
	/* disable to access apc registers */
E 2
I 2
	/* close to access APC registers */
E 2
	pci_config_put8(isa_handle, 0x48, reg);
	pci_config_teardown(&isa_handle);

D 2
	return B_TRUE;
E 2
I 2
	return (GEM_SUCCESS);
E 2
}

static int
sige_reset_chip(struct gem_dev *dp)
{
D 8
	struct sige_dev	*lp = (struct sige_dev *) dp->private;
E 8
I 8
	struct sige_dev	*lp = dp->private;
E 8

D 2
	DPRINTF(4, (CE_CONT, CONS "%s: %s called", dp->name, __func__));
E 2
I 2
D 8
	DPRINTF(4, (CE_CONT, "!%s: %s called", dp->name, __func__));
E 8
I 8
	DPRINTF(0, (CE_CONT, "!%s: %s called", dp->name, __func__));
E 8
E 2

D 2
	/* Disable Interrupt */
	OUTL(dp, IntMask, 0);
	OUTL(dp, IntSrc, 0xffffffff);
E 2
I 2
	lp->our_intr_bits = 0;
	OUTL(dp, IMR, lp->our_intr_bits);
	OUTL(dp, ISR, 0xffffffff);
E 2

I 12
	/* soft reset */
E 12
D 2
	/* Reset Tx & Rx */
	OUTL(dp, TxCtrl, lp->tx_control = 0x00001c00);
	OUTL(dp, RxCtrl, lp->rx_control = 0x001e1c00);
E 2
I 2
D 8
	lp->tx_control = 0x00001c00;
	lp->rx_control = 0x001e1c00;
	OUTL(dp, TxCTL, lp->tx_control);
	OUTL(dp, RxCTL, lp->rx_control);
E 2

D 2
	/* stop the state machine */
	OUTL(dp, IntCtrl, 0x8000);
E 2
I 2
	OUTL(dp, ICR, 0x00008000);
	FLSHL(dp, ICR);
E 8
I 8
D 9
	OUTL(dp, ICR, 0x8000);	/* ok */
	FLSHL(dp, ICR);		/* ok */
E 9
I 9
	OUTL(dp, ICR, 0x8000);
	FLSHL(dp, ICR);
E 9
E 8
E 2
	drv_usecwait(100);
D 2
	OUTL(dp, IntCtrl, 0);
E 2
I 2
D 8
	OUTL(dp, ICR, 0);
E 8
I 8
D 9
	OUTL(dp, ICR, 0);	/* ok */
E 9
I 9
	OUTL(dp, ICR, 0);
E 9
E 8
E 2

I 12
	/* stop mac */
E 12
D 2
	/* Disable Interrupt */
	OUTL(dp, IntMask, 0);
	OUTL(dp, IntSrc, 0xffffffff);
E 2
I 2
D 8
	OUTL(dp, IMR, 0);
	OUTL(dp, ISR, 0xffffffff);
E 8
I 8
D 9
	lp->tx_control = 0x1a00;	/* ok */
	lp->rx_control = 0x1a00;	/* ok */
	OUTL(dp, TxCTL, lp->tx_control);	/* ok */
	OUTL(dp, RxCTL, lp->rx_control);	/* ok */
E 9
I 9
	lp->tx_control = 0x1a00;
	lp->rx_control = 0x1a00;
	OUTL(dp, TxCTL, lp->tx_control);
	OUTL(dp, RxCTL, lp->rx_control);
E 9
E 8
E 2

I 8
D 9
	OUTL(dp, IMR, lp->our_intr_bits);	/* ok */
	OUTL(dp, ISR, 0xffffffff);	/* ok */
E 9
I 9
	OUTL(dp, IMR, lp->our_intr_bits);
	OUTL(dp, ISR, 0xffffffff);
E 9

E 8
D 2
	return 0;
E 2
I 2
	/* clear the register shadow for mac_addr */
D 8
	bzero(lp->mac_addr, sizeof(lp->mac_addr));
E 8
I 8
	bzero(lp->mac_addr, sizeof (lp->mac_addr));
E 8

D 8
	return (GEM_SUCCESS);
E 2
}

D 3
static void
E 3
I 3
static int
E 3
sige_init_chip(struct gem_dev *dp)
{
I 2
	uint32_t	val;
E 2
	struct sige_dev	*lp = (struct sige_dev *)dp->private;

D 2
	DPRINTF(1, (CE_CONT, CONS "%s: %s called", dp->name, __func__));
E 2
I 2
	DPRINTF(1, (CE_CONT, "!%s: %s called", dp->name, __func__));
	OUTL(dp, TxDESC, (uint32_t) dp->tx_ring_dma);
	OUTL(dp, TxDESC+4, 0);
	OUTL(dp, RxDESC, (uint32_t) dp->rx_ring_dma);
	OUTL(dp, Reserved1, 0);
	OUTL(dp, PMCTL, 0xffc00000);
	OUTL(dp, Reserved2, 0);
E 2

D 2
	/* Give initial value for all MAC registers */
	OUTL(dp, TxBase, (uint32_t) dp->tx_ring_dma);
	OUTL(dp, rsv0, 0);
	OUTL(dp, RxBase, (uint32_t) dp->rx_ring_dma);
	OUTL(dp, rsv1, 0);
	OUTL(dp, PwrCtrl, 0xffc00000);
	OUTL(dp, rsv2, 0);

	/* also set in set_media */
E 2
I 2
	val = 0x04000001;
E 8
I 8
D 9
	OUTL(dp, GMIICTL, 0);	/* ok */
E 9
I 9
	OUTL(dp, GMIICTL, 0);
E 9
E 8
E 2
	if (lp->phy_rgmii) {
D 2
		OUTL(dp, StationCtrl, 0x04000001 | SC_RGMII);
E 2
I 2
D 8
		val |= SC_RGMII;
E 8
I 8
		OUTL(dp, RGMIIDelay, 0x0441);	/* was  0x4441 */
		OUTL(dp, RGMIIDelay, 0x0440);	/* was  0x4440 */
E 8
E 2
	}
D 2
	else {
		OUTL(dp, StationCtrl, 0x04000001);
	}
E 2
I 2
D 8
	OUTL(dp, StationCTL, val);	/* also it will be set in set_media */
E 2

D 2
	OUTL(dp, GIoCR, 0);
	OUTL(dp, GIoCtrl, 0);
	OUTL(dp, TxMacCtrl, 0x00002364);
	OUTL(dp, TxLimit, 0x0000000f);
	OUTL(dp, RGDelay, 0);
E 2
I 2
	OUTL(dp, GMacIOCR, 0);
	OUTL(dp, GMacIOCTL, 0);
	OUTL(dp, TxMacCTL, 0x00002364);
	OUTL(dp, TxTimerLimit, 0x0000000f);
	OUTL(dp, RGMIIDelay, 0);
E 2
	if (lp->phy_rgmii) {
D 2
		OUTL(dp, RGDelay,  0x4441);
		OUTL(dp, RGDelay,  0x4440);
E 2
I 2
		OUTL(dp, RGMIIDelay,  0x4441);
		OUTL(dp, RGMIIDelay,  0x4440);
E 2
	}
D 2
	OUTL(dp, rsv3, 0);
	OUTW(dp, RxMacCtrl, 0x0252);
	OUTL(dp, RxHashTbl+0, 0);
	OUTL(dp, RxHashTbl+4, 0);
	OUTL(dp, RxWolCtrl, 0x80ff0000);
	OUTL(dp, RxWolData, 0x80ff0000);
	OUTL(dp, RxMpsCtrl, 0x0);
	OUTL(dp, rsv4, 0x0);
E 2
I 2
	OUTL(dp, Reserved3, 0);
	lp->rx_mac_ctrl = 0x0252;

	OUTL(dp, RxWOL, 0x80ff0000);
	OUTL(dp, RxWOLData, 0x80ff0000);
	OUTL(dp, RxMPSCTL, 0x0);
	OUTL(dp, Reserved4, 0x0);

	lp->tx_running = B_FALSE;
	lp->rx_running = B_FALSE;

E 8
#if 0
{
	clock_t	now;

	DPRINTF(0, (CE_CONT,
D 5
		"%s: %s: TIMER:0x%x", dp->name, __func__, INL(dp, TIMER)));
	OUTL(dp, TIMER, 0);
E 5
I 5
D 8
		"!%s: %s: TIMER:0x%x", dp->name, __func__, INL(dp, TIMER)));
E 8
I 8
	    "!%s: %s: TIMER:0x%x", dp->name, __func__, INL(dp, TIMER)));
E 8
	OUTL(dp, TIMER, 0xffffffff);
E 5
	OUTL(dp, ISR, INT_TIMER);
	DPRINTF(0, (CE_CONT,
D 5
		"%s: %s: TIMER:%d, ISR:%x", dp->name, __func__,
E 5
I 5
D 8
		"!%s: %s: TIMER:%x, ISR:%b", dp->name, __func__,
E 5
		INL(dp, TIMER), INL(dp, ISR), INT_BITS));
E 8
I 8
	    "!%s: %s: TIMER:%x, ISR:%b", dp->name, __func__,
	    INL(dp, TIMER), INL(dp, ISR), INT_BITS));
E 8
	drv_usecwait(1000);
	DPRINTF(0, (CE_CONT,
D 5
		"%s: %s: TIMER:%d, ISR:%x", dp->name, __func__,
E 5
I 5
D 8
		"!%s: %s: TIMER:%x, ISR:%b", dp->name, __func__,
E 5
		INL(dp, TIMER), INL(dp, ISR), INT_BITS));
E 8
I 8
	    "!%s: %s: TIMER:%x, ISR:%b", dp->name, __func__,
	    INL(dp, TIMER), INL(dp, ISR), INT_BITS));
E 8
	drv_usecwait(1000);
	DPRINTF(0, (CE_CONT,
D 5
		"%s: %s: TIMER:%d, ISR:%x", dp->name, __func__,
E 5
I 5
D 8
		"!%s: %s: TIMER:%x, ISR:%b", dp->name, __func__,
E 5
		INL(dp, TIMER), INL(dp, ISR), INT_BITS));
E 8
I 8
	    "!%s: %s: TIMER:%x, ISR:%b", dp->name, __func__,
	    INL(dp, TIMER), INL(dp, ISR), INT_BITS));
E 8
	OUTL(dp, TIMER, 1000);
	now = ddi_get_lbolt();
	OUTL(dp, ISR, INT_TIMER);
	while ((INL(dp, ISR) & INT_TIMER) == 0) {
		drv_usecwait(10);
	}

	cmn_err(CE_CONT, "!%s: %s: %d mS",
D 8
		dp->name, __func__,  (ddi_get_lbolt() - now)*10);
E 8
I 8
	    dp->name, __func__,  (ddi_get_lbolt() - now)*10);
E 8

	OUTL(dp, TIMER, 0);
E 2
}
I 2
#endif
I 3
	return (GEM_SUCCESS);
E 3
}
E 2

I 8
static int
sige_init_chip(struct gem_dev *dp)
{
	uint32_t	val;
	struct sige_dev	*lp = dp->private;

	DPRINTF(0, (CE_CONT, "!%s: %s called", dp->name, __func__));

	OUTL(dp, TxDESC, (uint32_t)dp->tx_ring_dma);
	OUTL(dp, RxDESC, (uint32_t)dp->rx_ring_dma);

D 9
	OUTL(dp, TxMacCTL, 0x60);	/* ok */
	lp->rx_mac_ctrl = 0x0002;	/* ok */
	OUTW(dp, RxMacCTL, lp->rx_mac_ctrl);	/* ok */
E 9
I 9
	OUTL(dp, TxMacCTL, 0x60);
	lp->rx_mac_ctrl = 0x0002;
I 13
#ifdef CONFIG_RX_PAD
	lp->rx_mac_ctrl |= RM_PAD_ENB;
#endif
#ifdef CONFIG_CRC_STRIP
	lp->rx_mac_ctrl |= RM_STRIP_FCS;
#endif
#ifdef CONFIG_VLAN_HW
	lp->rx_mac_ctrl |= RM_STRIP_VLAN;
#endif
E 13
	OUTW(dp, RxMacCTL, lp->rx_mac_ctrl);
E 9

I 12
	OUTL(dp, 0x6c, 0);
E 12
D 9
	OUTL(dp, RxWOL, 0);	/* ok */
	OUTL(dp, RxWOLData, 0);	/* ok */
E 9
I 9
	OUTL(dp, RxWOL, 0);
	OUTL(dp, RxWOLData, 0);
E 9

	lp->tx_running = B_FALSE;
D 10
	lp->rx_running = B_FALSE;
E 10

	return (GEM_SUCCESS);
}

E 8
static uint_t
sige_mcast_hash(struct gem_dev *dp, uint8_t *addr)
{
	return (gem_ether_crc_be(addr, ETHERADDRL) & (64 - 1));
}

D 3
static void
E 3
I 3
static int
E 3
sige_set_rx_filter(struct gem_dev *dp)
{
	int		i;
	uint16_t	mode;
D 2
	uint32_t	hash_tbl[2];
	uint16_t	rxmacctrl;
E 2
I 2
	uint64_t	hash_tbl;
D 8
	struct sige_dev	*lp = (struct sige_dev *)dp->private;
E 8
I 8
	struct sige_dev	*lp = dp->private;
E 8
E 2

D 2
	DPRINTF(4, (CE_CONT, CONS "%s: %s: called", dp->name, __func__));
E 2
I 2
D 8
	DPRINTF(4, (CE_CONT, "!%s: %s: called", dp->name, __func__));
E 8
I 8
	DPRINTF(0, (CE_CONT, "!%s: %s: called", dp->name, __func__));
E 8
E 2

	mode = 0;
D 2
	hash_tbl[0] = 0;
	hash_tbl[1] = 0;
E 2
I 2
	hash_tbl = 0ull;
E 2

	/* Set Receive filter control register */
D 2
	mode = RM_AB | RM_AM | RM_AP; /*accept broadcast multicast my physical*/
E 2
I 2
D 8
	mode = RM_AB | RM_AM | RM_AP; /* broadcast, multicast, my physical*/
E 8
I 8
	mode = RM_AB | RM_AM | RM_AP; /* broadcast, multicast, my physical */
E 8
E 2

D 5
	if ((dp->rxmode & RXMODE_PROMISC) != 0) {
E 5
I 5
	if ((dp->rxmode & RXMODE_ENABLE) == 0) {
		mode = 0;
	} else if (dp->rxmode & RXMODE_PROMISC) {
E 5
		/* accept all physcal address */
		mode |= RM_AAP;
D 8
	}
D 5
	else if ((dp->rxmode & RXMODE_ALLMULTI) != 0 || dp->mc_count > 32) {
E 5
I 5
	else if ((dp->rxmode & RXMODE_ALLMULTI) || dp->mc_count > 32) {
E 8
I 8
	} else if ((dp->rxmode & RXMODE_ALLMULTI) || dp->mc_count > 32) {
E 8
E 5
		/* enable all multicast address */
D 2
		hash_tbl[0] = hash_tbl[1] = 0xffffffff;
E 2
I 2
		hash_tbl = ~0ull;
E 2
D 8
	}
	else {
E 8
I 8
	} else {
E 8
		/* make hash table for selected multicast address */
		for (i = 0; i < dp->mc_count; i++) {
D 2
			uint_t	h;
			h = dp->mc_list[i].hash;
			hash_tbl[h / 32] |= 1 << (h % 32);
E 2
I 2
			hash_tbl |= 1ull << dp->mc_list[i].hash;
E 2
		}
	}

D 2
	/* Disable Rx filter */
	rxmacctrl = INW(dp, RxMacCtrl) & ~(RM_AB | RM_AM | RM_AAP | RM_AP);
	OUTW(dp, RxMacCtrl, rxmacctrl);
	FLSHW(dp, RxMacCtrl);
E 2
I 2
	/* Load station address if it has been changed */
D 5
	if (bcmp(dp->cur_addr.ether_addr_octet,
			lp->mac_addr, ETHERADDRL) != 0) {
E 5
I 5
	if (bcmp(dp->cur_addr.ether_addr_octet, lp->mac_addr, ETHERADDRL)) {
E 5
		/* temporally disable my station address before chaning it */
D 8
		OUTW(dp, RxMacCTL, lp->rx_mac_ctrl & ~RM_AP);
E 8
I 8
D 9
		OUTW(dp, RxMacCTL, lp->rx_mac_ctrl);	/* ok */
E 9
I 9
		OUTW(dp, RxMacCTL, lp->rx_mac_ctrl);
E 9
E 8
		FLSHW(dp, RxMacCTL);
E 2

D 2
	/* Load station address */
	for (i = 0; i < ETHERADDRL; i++) {
		OUTB(dp, RxMacAddr + i, dp->cur_addr.ether_addr_octet[i]);
E 2
I 2
		/* update my station address */
		bcopy(dp->cur_addr.ether_addr_octet, lp->mac_addr, ETHERADDRL);
		for (i = 0; i < ETHERADDRL; i++) {
			OUTB(dp, RxMacAddr + i, lp->mac_addr[i]);
		}
E 2
	}

	/* Load Multicast hash table */
D 2
	OUTL(dp, RxHashTbl + 0, hash_tbl[0]);
	OUTL(dp, RxHashTbl + 4, hash_tbl[1]);
E 2
I 2
D 8
	OUTL(dp, MCASTHASH + 0, (uint32_t) hash_tbl);
	OUTL(dp, MCASTHASH + 4, (uint32_t) (hash_tbl >> 32));
E 8
I 8
	OUTL(dp, MCASTHASH + 0, (uint32_t)hash_tbl);
	OUTL(dp, MCASTHASH + 4, (uint32_t)(hash_tbl >> 32));
E 8
E 2

	/* Load new rx filter mode */
D 2
	OUTW(dp, RxMacCtrl, rxmacctrl | mode);
E 2
I 2
D 8
	lp->rx_mac_ctrl &= ~(RM_AB | RM_AM | RM_AAP | RM_AP);
	lp->rx_mac_ctrl |= mode;
	OUTW(dp, RxMacCTL, lp->rx_mac_ctrl);
E 8
I 8
D 9
	OUTW(dp, RxMacCTL, lp->rx_mac_ctrl | mode);	/* ok */
E 9
I 9
	OUTW(dp, RxMacCTL, lp->rx_mac_ctrl | mode);
E 9
E 8
I 3

	return (GEM_SUCCESS);
E 3
E 2
}

D 2
/* DONE */
E 2
D 3
static void
E 3
I 3
static int
E 3
sige_start_chip(struct gem_dev *dp)
{
D 8
	struct sige_dev	*lp = (struct sige_dev *)dp->private;
E 8
I 8
	struct sige_dev	*lp = dp->private;
E 8

D 2
	DPRINTF(4, (CE_CONT, CONS "%s: %s: called", dp->name, __func__));
E 2
I 2
D 8
	DPRINTF(4, (CE_CONT, "!%s: %s: called", dp->name, __func__));
E 8
I 8
	DPRINTF(0, (CE_CONT, "!%s: %s: called", dp->name, __func__));
E 8
E 2

	/* enable interrupt */
	lp->our_intr_bits = OUR_INTR_BITS;
I 2
#ifdef OPT_TxPOLL
	lp->our_intr_bits |= INT_TXIDLE;
#endif
E 2
	if ((dp->misc_flag & GEM_NOINTR) == 0) {
D 2
		OUTL(dp, IntMask, lp->our_intr_bits);
E 2
I 2
		OUTL(dp, IMR, lp->our_intr_bits);
E 2
	}

	/* enable tx */
D 2
	lp->tx_control |= TxCtrl_EN;
	OUTL(dp, TxCtrl, lp->tx_control);
E 2
I 2
	lp->tx_control |= TxCTL_EN;
	OUTL(dp, TxCTL, lp->tx_control);
E 2

	/* enable rx */
D 2
	lp->rx_control |= RxCtrl_EN;
	OUTL(dp, RxCtrl, lp->rx_control | RxCtrl_POLL);
E 2
I 2
D 8
	lp->rx_control |= RxCTL_EN;
	OUTL(dp, RxCTL, lp->rx_control);
E 8
I 8
	lp->rx_control |= 0x0c | RxCTL_EN;
I 10
	OUTL(dp, RxCTL, lp->rx_control | RxCTL_POLL);
E 10
E 8
I 3

	return (GEM_SUCCESS);
E 3
E 2
}

D 2
/* DONE */
static void
E 2
I 2
static int
E 2
sige_stop_chip(struct gem_dev *dp)
{
	uint32_t	val;
D 8
	struct sige_dev	*lp = (struct sige_dev *)dp->private;
E 8
I 8
	struct sige_dev	*lp = dp->private;
E 8

D 2
	DPRINTF(4, (CE_CONT, CONS "%s: %s: called", dp->name, __func__));
E 2
I 2
	DPRINTF(4, (CE_CONT, "!%s: %s: called", dp->name, __func__));
E 2

I 8
	/* stop tx and rx state machines */
D 9
	lp->tx_control = 0x1a00;	/* ok */
	lp->rx_control = 0x1a00;	/* ok */
	OUTL(dp, TxCTL, lp->tx_control);	/* ok */
	OUTL(dp, RxCTL, lp->rx_control);	/* ok */
E 9
I 9
	lp->tx_control = 0x1a00;
	lp->rx_control = 0x1a00;
	OUTL(dp, TxCTL, lp->tx_control);
	OUTL(dp, RxCTL, lp->rx_control);
E 9

E 8
	/* disable interrupts */
D 2
	OUTL(dp, IntMask, 0);
	drv_usecwait(2000);
E 2
I 2
	OUTL(dp, IMR, 0);
	FLSHL(dp, IMR);
E 2
D 8

        /* stop tx and rx state machines */
E 8
I 8
#ifdef notdef
	/* stop tx and rx state machines */
E 8
D 2
	val = INL(dp, IntCtrl) & ~0x8000;
	OUTL(dp, IntCtrl, val | 0x8000);
E 2
I 2
	val = INL(dp, ICR);
	OUTL(dp, ICR, val | 0x8000);
	FLSHL(dp, ICR);
E 2
	drv_usecwait(50);
D 2
	OUTL(dp, IntCtrl, val);
E 2
I 2
	OUTL(dp, ICR, val & ~0x8000);
D 8

E 8
I 8
#endif
E 8
	drv_usecwait(2000);

	return (GEM_SUCCESS);
E 2
}

D 2
/* DONE */
E 2
D 3
static void
E 3
I 3
static int
E 3
sige_set_media(struct gem_dev *dp)
{
	uint32_t	val;
D 8
	struct sige_dev	*lp = (struct sige_dev *)dp->private;
E 8
I 8
	struct sige_dev	*lp = dp->private;
E 8
	extern int gem_speed_value[];

D 2
	DPRINTF(2, (CE_CONT, CONS "%s: %s: %s duplex, %d Mbps",
E 2
I 2
D 8
	DPRINTF(2, (CE_CONT, "!%s: %s: %s duplex, %d Mbps",
E 2
		dp->name, __func__,
		dp->full_duplex ? "full" : "half",
		gem_speed_value[dp->speed]));
E 8
I 8
	DPRINTF(0, (CE_CONT, "!%s: %s: %s duplex, %d Mbps, StationCTL:%x",
	    dp->name, __func__,
	    dp->full_duplex ? "full" : "half",
	    gem_speed_value[dp->speed], INL(dp, StationCTL)));
E 8

D 2
	val = INL(dp, StationCtrl) & ~(0x0f000000 | SC_FDX | SC_SPEED);
E 2
I 2
	val = INL(dp, StationCTL) & ~(0x0f000000 | SC_FDX | SC_SPEED);
E 2

	switch (dp->speed) {
	case GEM_SPD_1000:
		val |= SC_SPEED_1000;
		break;

	case GEM_SPD_100:
		val |= SC_SPEED_100;
		break;

	case GEM_SPD_10:
		val |= SC_SPEED_10;
		break;
	}

D 8
	if(dp->full_duplex) {
E 8
I 8
	if (dp->full_duplex) {
E 8
		val |= SC_FDX;
	}

	/* XXX: MII phy operation mode? */
D 8
	if (lp->phy_rgmii || dp->speed == GEM_SPD_1000) {
E 8
I 8
	if (dp->speed == GEM_SPD_1000) {
E 8
		val |= 0x07000000;
	} else {
		val |= 0x04000000;
	}
I 8
	if (lp->phy_rgmii && dp->mii_phy_id == PHY_ID_BCM5461_1) {
		val |= 0x03000000;
	}
E 8
D 12

E 12
D 2
	OUTL(dp, StationCtrl, val);
E 2
I 2
D 8
	OUTL(dp, StationCTL, val);
E 8
I 8
D 9
	OUTL(dp, StationCTL, val);	/* ok */
E 9
I 9
	OUTL(dp, StationCTL, val);
E 9
E 8
E 2

I 8
	DPRINTF(0, (CE_CONT, "!%s: %s: new StationCTL:%x",
	    dp->name, __func__, val));

E 8
	/*
	 * setup tx descriptor flags
	 */
D 8
	lp->tx_desc_flags =
D 5
		TDC_TXOWN | TDC_PADEN | TDC_CRCEN | TDC_DEFEN | TDC_THOL3;
E 5
I 5
		TDC_TXOWN | TDC_PADEN | TDC_CRCEN | TDC_DEFEN | TDC_THOL0;
E 8
I 8
	lp->tx_desc_flags = TDC_TXOWN | TDC_PADEN | TDC_CRCEN | TDC_DEFEN;
I 13
	if (dp->speed == GEM_SPD_1000) {
		lp->tx_desc_flags |= TDC_BSTEN;
	}
E 13
E 8
E 5
D 12

E 12
I 12
#ifdef notdef
E 12
	if (!dp->full_duplex) {
D 8
		lp->tx_desc_flags |= TDC_COLEN | TDC_CRSEN | TDC_BKFEN;
E 8
I 8
		lp->tx_desc_flags |= TDC_COLEN | TDC_BKFEN;
	}
E 8
D 13

D 8
		if (dp->speed == GEM_SPD_1000) {
			lp->tx_desc_flags |= TDC_EXTEN | TDC_BSTEN;
		}
E 8
I 8
	if (dp->speed != GEM_SPD_1000) {
		lp->tx_desc_flags |= TDC_CRSEN;
E 8
	}
E 13
I 3
D 12

E 12
I 12
#endif
E 12
	return (GEM_SUCCESS);
E 3
}

D 3
static void
E 3
I 3
static int
E 3
sige_get_stats(struct gem_dev *dp)
{
	/* do nothing */
I 3
	return (GEM_SUCCESS);
E 3
}

/*
 * discriptor  manupiration
 */
static int
sige_tx_desc_write(struct gem_dev *dp, int slot,
D 5
		ddi_dma_cookie_t *dmacookie, int frags, uint32_t flags)
E 5
I 5
		ddi_dma_cookie_t *dmacookie, int frags, uint64_t flags)
E 5
{
I 2
	int			i;
D 13
	uint32_t		pktsize;
E 13
I 13
	uint32_t		pktsize = 0;
E 13
E 2
	uint32_t		mark;
	struct sige_txdesc	*tdp;
D 8
	struct sige_dev		*lp = (struct sige_dev *)dp->private;
#if DEBUG_LEVEL > 2
E 8
I 8
	struct sige_dev		*lp = dp->private;
I 13
#ifdef CONFIG_CKSUM_OFFLOAD
	uint32_t		mss;
#endif
E 13
E 8
D 2
	int			i;
E 2

I 8
D 13
#if DEBUG_LEVEL > 2
E 13
I 13
#if DEBUG_LEVEL > 10
E 13
E 8
	cmn_err(CE_CONT,
D 2
	CONS "%s: time:%d %s seqnum: %d, slot %d, frags: %d flags: %d",
E 2
I 2
D 5
		"!%s: time:%d %s seqnum: %d, slot %d, frags: %d flags: %d",
E 5
I 5
D 8
		"!%s: time:%d %s seqnum: %d, slot %d, frags: %d flags: %llx",
E 5
E 2
		dp->name, ddi_get_lbolt(), __func__,
		dp->tx_desc_tail, slot, frags, flags);
E 8
I 8
D 13
	    "!%s: time:%d %s seqnum: %d, slot %d, frags: %d flags: %llx",
	    dp->name, ddi_get_lbolt(), __func__,
E 13
I 13
	    "!%s: %s: seqnum:%d, slot%d, frags:%d flags:%llx",
	    dp->name, __func__,
E 13
	    dp->tx_desc_tail, slot, frags, flags);
E 8

	for (i = 0; i < frags; i++) {
D 2
		cmn_err(CE_CONT, CONS "%d: addr: 0x%x, len: 0x%x",
E 2
I 2
D 13
		cmn_err(CE_CONT, "!%d: addr: 0x%x, len: 0x%x",
E 13
I 13
		cmn_err(CE_CONT, "!%d: addr:0x%x, len:%d",
E 13
E 2
D 8
			i, dmacookie[i].dmac_address, dmacookie[i].dmac_size);
E 8
I 8
		    i, dmacookie[i].dmac_address, dmacookie[i].dmac_size);
E 8
	}
#endif
	/*
	 * write tx descriptor in reversed order.
	 */
#if DEBUG_LEVEL > 3
	flags |= GEM_TXFLAG_INTR;
#endif
D 2
	tdp = &((struct sige_txdesc *) dp->tx_ring)[slot];

	tdp->td_bufptr  = LE32((uint32_t) dmacookie->dmac_address);
	tdp->td_pktsize = LE32((uint32_t) dmacookie->dmac_size);
	tdp->td_eod     = (tdp->td_eod & LE32(TX_RING_EOD))
			| LE32((uint32_t) dmacookie->dmac_size);

E 2
D 5
	if ((flags & GEM_TXFLAG_INTR) != 0) {
E 5
I 5
	if (flags & GEM_TXFLAG_INTR) {
E 5
D 8
		mark = lp->tx_desc_flags | TDC_TXINT; 
E 8
I 8
		mark = lp->tx_desc_flags | TDC_TXINT;
E 8
	} else {
		mark = lp->tx_desc_flags;
	}
D 13
#ifdef GEM_CONFIG_CKSUM_OFFLOAD
E 13
I 13
#ifdef CONFIG_CKSUM_OFFLOAD
E 13
D 2
	if ((flags & GEM_TXFLAG_IPv4) != 0) {
E 2
I 2
	/* only 1 bit in tcp, udp and ip, is allowed */
D 5
	if ((flags & GEM_TXFLAG_UDP) != 0) {
E 5
I 5
D 13
	if (flags & GEM_TXFLAG_UDP) {
E 13
I 13
	mss = (flags & GEM_TXFLAG_MSS) >> GEM_TXFLAG_MSS_SHIFT;
	if (mss) {
		mark |= TDC_LSEN;
		pktsize |= mss << TX_MSS_SHIFT;
	} else if (flags & GEM_TXFLAG_UDP) {
E 13
E 5
		/* it requires psuedo header check sum */
		mark |= TDC_UDPCS;
D 8
	}
D 5
	else if ((flags & GEM_TXFLAG_TCP) != 0) {
E 5
I 5
	else if (flags & GEM_TXFLAG_TCP) {
E 8
I 8
	} else if (flags & GEM_TXFLAG_TCP) {
E 8
E 5
		/* it requires psuedo header check sum */
		mark |= TDC_TCPCS;
D 8
	}
D 5
	else if ((flags & GEM_TXFLAG_IPv4) != 0) {
E 5
I 5
	else if (flags & GEM_TXFLAG_IPv4) {
E 8
I 8
D 13
	} else if (flags & GEM_TXFLAG_IPv4) {
E 13
I 13
	}
	if (flags & GEM_TXFLAG_IPv4) {
E 13
E 8
E 5
E 2
		mark |= TDC_IPCS;
	}
D 2
	if ((flags & GEM_TXFLAG_UDP) != 0) {
		mark |= TDC_IPCS | TDC_UDPCS;
E 2
I 2
#endif
D 5
#ifdef notdef
E 5
I 5
D 13
#if MAXTXFRAGS > 1
E 5
	pktsize = 0;

E 13
	for (i = frags - 1; i > 0; i--) {
D 8
		tdp = &((struct sige_txdesc *) dp->tx_ring)[
				SLOT(slot+i, TX_RING_SIZE)];
E 8
I 8
		tdp = &((struct sige_txdesc *)dp->tx_ring)[
D 13
		    SLOT(slot+i, TX_RING_SIZE)];
E 13
I 13
		    SLOT(slot+i, dp->gc.gc_tx_ring_size)];
E 13
E 8

		pktsize += dmacookie[i].dmac_size;
D 5
		tdp->td_bufptr  = LE32(dmacookie[i].dmac_address);
E 5
I 5
D 8
		tdp->td_bufptr  = LE_32(dmacookie[i].dmac_address);
E 8
I 8
		tdp->td_bufptr = LE_32(dmacookie[i].dmac_address);
E 8
E 5
		tdp->td_pktsize = 0;
D 5
		tdp->td_flags   = (tdp->td_flags & LE32(TX_RING_EOD))
				| LE32(dmacookie[i].dmac_size);
E 5
I 5
D 8
		tdp->td_flags   = (tdp->td_flags & LE_32(TX_RING_EOD))
				| LE_32(dmacookie[i].dmac_size);
E 8
I 8
		tdp->td_flags = (tdp->td_flags & LE_32(TX_RING_EOD))
		    | LE_32(dmacookie[i].dmac_size);
E 8
D 9
		tdp->td_cmdsts = LE_32(0xffffffff);
E 9
I 9
D 13
		tdp->td_cmdsts = LE_32(0xffffffffU);
E 13
I 13
		tdp->td_cmdsts = LE_32(TDC_TXOWN);
E 13
E 9
E 5
E 2
	}
D 2
	if ((flags & GEM_TXFLAG_TCP) != 0) {
		mark |= TDC_IPCS | TDC_TCPCS;
E 2
I 2
D 8

D 5
	if ((flags & GEM_TXFLAG_HEAD) != 0) {
E 5
I 5
	if (flags & GEM_TXFLAG_HEAD) {
E 5
		mark &= ~TDC_TXOWN;
E 2
	}
E 8
I 2
	pktsize += dmacookie[0].dmac_size;
D 13
#else
	pktsize = dmacookie[0].dmac_size;
E 2
#endif
E 13
I 13

E 13
I 2
D 8
	tdp = &((struct sige_txdesc *) dp->tx_ring)[slot];
D 5
	tdp->td_bufptr  = LE32(dmacookie[0].dmac_address);
	tdp->td_pktsize = LE32(pktsize);
	tdp->td_flags   = (tdp->td_flags & LE32(TX_RING_EOD))
			| LE32(dmacookie[0].dmac_size);
E 2
	tdp->td_cmdsts = LE32(mark);
E 5
I 5
	tdp->td_bufptr  = LE_32(dmacookie[0].dmac_address);
E 8
I 8
	if (flags & GEM_TXFLAG_HEAD) {
		mark &= ~TDC_TXOWN;
	}
D 13

E 13
I 13
#ifdef CONFIG_VLAN_HW
	if (flags & GEM_TXFLAG_VTAG) {
		pktsize |= TX_INS_VTAG;
		mark |= (GEM_TXFLAG_VTAG & flags) >> GEM_TXFLAG_VTAG_SHIFT;
	}
#endif
E 13
	tdp = &((struct sige_txdesc *)dp->tx_ring)[slot];
	tdp->td_bufptr = LE_32(dmacookie[0].dmac_address);
E 8
	tdp->td_pktsize = LE_32(pktsize);
D 8
	tdp->td_flags   = (tdp->td_flags & LE_32(TX_RING_EOD))
			| LE_32(dmacookie[0].dmac_size);
E 8
I 8
	tdp->td_flags = (tdp->td_flags & LE_32(TX_RING_EOD))
	    | LE_32(dmacookie[0].dmac_size);
E 8
	tdp->td_cmdsts = LE_32(mark);
E 5

	return (frags);
}

static void
D 2
sige_tx_start(struct gem_dev *dp, int slot, int frags)
E 2
I 2
sige_tx_start(struct gem_dev *dp, int start_slot, int nslot)
E 2
{
D 8
	struct sige_dev		*lp = (struct sige_dev *)dp->private;
E 8
I 8
	struct sige_dev		*lp = dp->private;
E 8

I 2
D 13
	if (nslot > 1) {
		gem_tx_desc_dma_sync(dp,
D 8
				SLOT(start_slot + 1, TX_RING_SIZE),
				nslot - 1, DDI_DMA_SYNC_FORDEV);
E 8
I 8
		    SLOT(start_slot + 1, TX_RING_SIZE),
		    nslot - 1, DDI_DMA_SYNC_FORDEV);
E 8
	}
E 13
I 13
	/* add a NOT OWNed descriptor to terminate tx list */
	((struct sige_txdesc *)dp->tx_ring)[
	    SLOT(start_slot + nslot, dp->gc.gc_tx_ring_size)].td_cmdsts = 0;
	gem_tx_desc_dma_sync(dp,
	    SLOT(start_slot + 1, dp->gc.gc_tx_ring_size),
	    nslot, DDI_DMA_SYNC_FORDEV);
E 13

I 13
	/* activate the first discriptor of the tx list */
E 13
D 8
	((struct sige_txdesc *) dp->tx_ring)[start_slot].td_cmdsts
D 5
						|= LE32(TDC_TXOWN);
E 5
I 5
						|= LE_32(TDC_TXOWN);
E 8
I 8
	((struct sige_txdesc *)dp->tx_ring)[start_slot].td_cmdsts |=
	    LE_32(TDC_TXOWN);
E 8
E 5
	gem_tx_desc_dma_sync(dp, start_slot, 1, DDI_DMA_SYNC_FORDEV);

E 2
	/*
	 * Let the Transmit Buffer Manager Fill state machine active.
	 */
D 2
	OUTL(dp, TxCtrl, lp->tx_control | TxCtrl_POLL);
E 2
I 2
	if (!lp->tx_running) {
D 8
		OUTL(dp, TxCTL, lp->tx_control | TxCTL_POLL);
E 8
I 8
D 9
		OUTL(dp, TxCTL, lp->tx_control | TxCTL_POLL); /* ok */
E 9
I 9
		OUTL(dp, TxCTL, lp->tx_control | TxCTL_POLL);
E 9
E 8
#ifdef OPT_TxPOLL
		lp->tx_running = B_TRUE;
#endif
	}
E 2
}

static void
sige_rx_desc_write(struct gem_dev *dp, int slot,
	    ddi_dma_cookie_t *dmacookie, int frags)
{
	struct sige_rxdesc	*rdp;
I 8
	struct sige_dev		*lp = dp->private;
E 8
#if DEBUG_LEVEL > 2
	int			i;

	ASSERT(frags == 1);

D 2
	cmn_err(CE_CONT, CONS
		"%s: sige_rx_desc_write seqnum: %d, slot %d, frags: %d",
		dp->name, dp->rx_desc_tail, slot, frags);
E 2
I 2
	cmn_err(CE_CONT,
D 8
		"!%s: %s seqnum: %d, slot %d, frags: %d",
		dp->name, __func__, dp->rx_active_tail, slot, frags);
E 8
I 8
	    "!%s: %s seqnum: %d, slot %d, frags: %d",
	    dp->name, __func__, dp->rx_active_tail, slot, frags);
E 8
E 2
	for (i = 0; i < frags; i++) {
D 2
		cmn_err(CE_CONT, CONS "  frag: %d addr: 0x%x, len: 0x%x",
E 2
I 2
		cmn_err(CE_CONT, "!  frag: %d addr: 0x%x, len: 0x%x",
E 2
D 8
			i, dmacookie[i].dmac_address, dmacookie[i].dmac_size);
E 8
I 8
		    i, dmacookie[i].dmac_address, dmacookie[i].dmac_size);
E 8
	}
#endif
	/* for the last slot of the packet */
D 8
	rdp = &((struct sige_rxdesc *) dp->rx_ring)[slot];
E 8
I 8
	rdp = &((struct sige_rxdesc *)dp->rx_ring)[slot];
E 8

D 2
	rdp->rd_bufptr  = LE32((uint32_t) dmacookie->dmac_address);
E 2
I 2
D 5
	rdp->rd_bufptr  = LE32(dmacookie->dmac_address);
E 5
I 5
D 8
	rdp->rd_bufptr  = LE_32(dmacookie->dmac_address);
E 8
I 8
	rdp->rd_bufptr = LE_32(dmacookie->dmac_address);
E 8
E 5
E 2
	rdp->rd_stssize = 0;
D 2
	rdp->rd_eod     = (rdp->rd_eod & LE32(RX_RING_EOD))
			| LE32((uint32_t) dmacookie->dmac_size);
	rdp->rd_pktinfo = LE32(RDI_RXOWN | RDI_RXINT);
E 2
I 2
D 5
	rdp->rd_flags   = (rdp->rd_flags & LE32(RX_RING_EOD))
			| LE32(dmacookie->dmac_size);
	rdp->rd_pktinfo = LE32(RDI_RXOWN | RDI_RXINT | RDI_TCPON | RDI_UDPON | RDI_IPON);
E 5
I 5
D 8
	rdp->rd_flags   = (rdp->rd_flags & LE_32(RX_RING_EOD))
			| LE_32(dmacookie->dmac_size);
E 8
I 8
	rdp->rd_flags = (rdp->rd_flags & LE_32(RX_RING_EOD))
	    | LE_32(dmacookie->dmac_size);

D 13
#ifdef GEM_CONFIG_CKSUM_OFFLOAD
E 13
I 13
#ifdef CONFIG_CKSUM_OFFLOAD
E 13
E 8
	rdp->rd_pktinfo = LE_32(
D 8
		RDI_RXOWN | RDI_RXINT | RDI_TCPON | RDI_UDPON | RDI_IPON);
E 8
I 8
	    RDI_RXOWN | RDI_RXINT | RDI_TCPON | RDI_UDPON | RDI_IPON);
#else
	rdp->rd_pktinfo = LE_32(RDI_RXOWN | RDI_RXINT);
#endif
E 8
E 5
E 2
}

I 2
D 10
static void
sige_rx_start(struct gem_dev *dp, int start_slot, int nslot)
{
D 8
	struct sige_dev		*lp = (struct sige_dev *)dp->private;
E 8
I 8
	struct sige_dev		*lp = dp->private;
E 8

	gem_rx_desc_dma_sync(dp, start_slot, nslot, DDI_DMA_SYNC_FORDEV);

	/*
	 * Let the Receive Buffer Manager Fill state machine active.
	 */
	if (!lp->rx_running) {
		OUTL(dp, RxCTL, lp->rx_control | RxCTL_POLL);
		lp->rx_running = B_TRUE;
	}
}

E 10
E 2
static uint_t
sige_tx_desc_stat(struct gem_dev *dp, int slot, int ndesc)
{
	struct sige_txdesc	*tdp;
	uint32_t		status;
	int			i;
	int			cols;
#ifdef DEBUG_LEVEL
D 8
	struct sige_dev		*lp = (struct sige_dev *) dp->private;
E 8
I 8
	struct sige_dev		*lp = dp->private;
E 8
	clock_t			delay;
#endif
D 13
	/* check status of the last descriptor */
I 2
D 8
#ifndef notdef
E 8
E 2
	tdp = &((struct sige_txdesc *)dp->tx_ring)[
D 8
		SLOT(slot + ndesc - 1, TX_RING_SIZE)];
D 2

E 2
I 2
#else
	tdp = &((struct sige_txdesc *)dp->tx_ring)[
		SLOT(slot, TX_RING_SIZE)];
#endif
E 8
I 8
	    SLOT(slot + ndesc - 1, TX_RING_SIZE)];
E 13
I 13
	/* check status of the first descriptor */
	tdp = &((struct sige_txdesc *)dp->tx_ring)[slot];
E 13

E 8
E 2
D 5
	status = LE32(tdp->td_cmdsts);
E 5
I 5
D 9
	status = LE_32(tdp->td_cmdsts);
E 9
I 9
	status = tdp->td_cmdsts;
	status = LE_32(status);
E 9
E 5

	DPRINTF(2, (CE_CONT,
D 2
		CONS "%s: time:%d sige_tx_desc_stat: slot:%d, status:0x%b",
		dp->name, ddi_get_lbolt(), slot, status, TDS_BITS));
E 2
I 2
D 8
		"!%s: time:%d %s: slot:%d, status:0x%b",
		dp->name, ddi_get_lbolt(), __func__, slot, status, TDS_BITS));
E 8
I 8
	    "!%s: time:%d %s: slot:%d, status:0x%b",
	    dp->name, ddi_get_lbolt(), __func__, slot, status, TDS_BITS));
E 8
E 2

D 5
	if ((status & TDC_TXOWN) != 0) {
E 5
I 5
	if (status & TDC_TXOWN) {
E 5
		/*
		 * not yet transmitted
		 */
		return (0);
	}
D 13

E 13
#if DEBUG_LEVEL > 3
	delay = (ddi_get_lbolt() - dp->tx_buf_head->txb_stime) * 10;
	if (delay >= 50) {
D 5
		DPRINTF(0, (CE_NOTE, "%s: tx deferred %d mS: slot %d",
E 5
I 5
		DPRINTF(0, (CE_NOTE, "!%s: tx deferred %d mS: slot %d",
E 5
D 8
			dp->name, delay, slot));
E 8
I 8
		    dp->name, delay, slot));
E 8
	}
#endif
D 13

E 13
	/*
	 *  collect statictics
	 */
D 5
	if ((status & (TDS_OWC | TDS_FIFO | TDS_CRS | TDS_ABT)) != 0) {
E 5
I 5
	if (status & (TDS_OWC | TDS_FIFO | TDS_CRS | TDS_ABT)) {
E 5

		/* failed to transmit the packet */

D 2
		DPRINTF(2, (CE_CONT, CONS "%s: Transmit error, Tx status %b",
E 2
I 2
		DPRINTF(2, (CE_CONT, "!%s: Transmit error, Tx status %b",
E 2
D 8
			       dp->name, status, TDS_BITS));
E 8
I 8
		    dp->name, status, TDS_BITS));
E 8

		dp->stats.errxmt++;

D 5
		if ((status & TDS_FIFO) != 0) {
E 5
I 5
		if (status & TDS_FIFO) {
E 5
			dp->stats.underflow++;
D 8
		}
D 5
		if ((status & TDS_CRS) != 0) {
E 5
I 5
		else if (status & TDS_CRS) {
E 8
I 8
		} else if (status & TDS_CRS) {
E 8
E 5
			dp->stats.nocarrier++;
D 8
		}
D 5
		if ((status & TDS_OWC) != 0) {
E 5
I 5
		else if (status & TDS_OWC) {
E 8
I 8
		} else if (status & TDS_OWC) {
E 8
E 5
			dp->stats.xmtlatecoll++;
D 8
		}
D 5
		if (!dp->full_duplex) {
			if (status & TDS_ABT) {
				dp->stats.excoll++;
				dp->stats.collisions += 16;
			}
E 5
I 5
		else if (!dp->full_duplex && (status & TDS_ABT)) {
E 8
I 8
		} else if (!dp->full_duplex && (status & TDS_ABT)) {
E 8
			dp->stats.excoll++;
			dp->stats.collisions += 16;
E 5
D 8
		}
I 5
		else {
E 8
I 8
		} else {
E 8
			dp->stats.xmit_internal_err++;
		}
E 5
D 8
	}
	else if (!dp->full_duplex) {
E 8
I 8
	} else if (!dp->full_duplex) {
E 8
		/* half duplex: update collision counters */
		cols = (status & TDS_COLLS) - 1;

		if (cols > 0) {
			if (cols == 1) {
				dp->stats.first_coll++;
			} else /* (cols > 1) */ {
				dp->stats.multi_coll++;
			}
			dp->stats.collisions += cols;
		}
	}

	return (GEM_TX_DONE);
}

static uint64_t
sige_rx_desc_stat(struct gem_dev *dp, int slot, int ndesc)
{
	struct sige_rxdesc	*rdp;
D 13
	uint_t			len;
	uint_t			flag;
E 13
I 13
	uint64_t		len;
	uint64_t		flag;
E 13
	uint32_t		rxinfo;
	uint32_t		status;

	flag = GEM_RX_DONE;

D 2
	/* Dont read ISR because we cannot ack only to rx interrupt. */

E 2
	rdp = &((struct sige_rxdesc *)dp->rx_ring)[slot];

D 5
	rxinfo = LE32(rdp->rd_pktinfo);
	status = LE32(rdp->rd_stssize);
E 5
I 5
D 9
	rxinfo = LE_32(rdp->rd_pktinfo);
E 9
I 9
	rxinfo = rdp->rd_pktinfo;
	rxinfo = LE_32(rxinfo);
E 9
	status = LE_32(rdp->rd_stssize);
E 5

	DPRINTF(2, (CE_CONT,
D 2
		CONS "%s: time:%d %s: slot:%d, rxinfo:0x%b, status:0x%b",
E 2
I 2
D 8
		"!%s: time:%d %s: slot:%d, rxinfo:0x%b, status:0x%b",
E 2
		dp->name, ddi_get_lbolt(), __func__,
		slot, rxinfo, RDI_BITS, status, RDS_BITS));
E 8
I 8
	    "!%s: time:%d %s: slot:%d, rxinfo:0x%b, status:0x%b",
	    dp->name, ddi_get_lbolt(), __func__,
	    slot, rxinfo, RDI_BITS, status, RDS_BITS));
E 8

D 5
	if ((rxinfo & RDI_RXOWN) != 0) {
E 5
I 5
	if (rxinfo & RDI_RXOWN) {
E 5
		/*
		 * No more received packets because
D 5
		 * this buffer is owned by NIC.
E 5
I 5
		 * the buffer is owned by NIC.
E 5
		 */
		return (0);
	}

I 2
	DPRINTF(2, (CE_CONT,
D 5
		"!%s: time:%d %s: slot:%d, rxinfo:0x%b, status:0x%b",
E 5
I 5
D 8
"!%s: time:%d %s: slot:%d, rxinfo:0x%b, status:0x%b, bufptr:0x%x, flags:0x%x",
E 5
		dp->name, ddi_get_lbolt(), __func__,
D 5
		slot, rxinfo, RDI_BITS, status, RDS_BITS));
E 5
I 5
		slot, rxinfo, RDI_BITS, status, RDS_BITS,
		LE_32(rdp->rd_bufptr), LE_32(rdp->rd_flags)));
E 8
I 8
	    "!%s: time:%d"
	    " %s: slot:%d, rxinfo:0x%b, status:0x%b, bufptr:0x%x, flags:0x%x",
	    dp->name, ddi_get_lbolt(), __func__,
	    slot, rxinfo, RDI_BITS, status, RDS_BITS,
	    LE_32(rdp->rd_bufptr), LE_32(rdp->rd_flags)));
E 8
E 5
E 2

#define	RX_ERR_BITS \
	(RDS_COLON | RDS_NIBON | RDS_OVRUN | RDS_MIIER | \
D 8
	 RDS_LIMIT | RDS_SHORT | RDS_ABORT | RDS_CRCOK | RDS_DESCS)
E 8
I 8
	RDS_LIMIT | RDS_SHORT | RDS_ABORT | RDS_CRCOK | RDS_DESCS)
E 8

	if ((status & RX_ERR_BITS) != (RDS_CRCOK | (1 << RDS_DESCS_SHIFT))) {
		/*
		 * we received a packet with error.
		 */
D 2
		DPRINTF(0, (CE_CONT, CONS "%s: Corrupted packet "
E 2
I 2
D 5
		DPRINTF(0, (CE_CONT, "!%s: Corrupted packet "
E 2
			"received, buffer status: %b",
E 5
I 5
		DPRINTF(0, (CE_CONT,
D 8
			"!%s: Corrupted packet received, buffer status: %b",
E 5
			dp->name, status, RDS_BITS));
E 8
I 8
		    "!%s: Corrupted packet received, buffer status: %b",
		    dp->name, status, RDS_BITS));
E 8

		/* collect statistics information */
		dp->stats.errrcv++;
D 5
		if ((status & RDS_OVRUN) != 0) {
E 5
I 5
		if (status & RDS_OVRUN) {
E 5
			dp->stats.overflow++;
D 8
		}
D 5
		if ((status & RDS_LIMIT) != 0 ||
		   ((status & RDS_DESCS) >> RDS_DESCS_SHIFT) > 1) {
E 5
I 5
		else if ((status & RDS_LIMIT) ||
			((status & RDS_DESCS) >> RDS_DESCS_SHIFT) > 1) {
E 8
I 8
		} else if ((status & RDS_LIMIT) ||
		    ((status & RDS_DESCS) >> RDS_DESCS_SHIFT) > 1) {
E 8
E 5
			dp->stats.frame_too_long++;
D 8
		}
D 5
		if ((status & RDS_SHORT) != 0) {
E 5
I 5
		else if (status & RDS_SHORT) {
E 8
I 8
		} else if (status & RDS_SHORT) {
E 8
E 5
			dp->stats.runt++;
D 8
		}
D 5
		if ((status & (RDS_NIBON | RDS_MIIER | RDS_COLON)) != 0) {
E 5
I 5
		else if (status & (RDS_NIBON | RDS_MIIER | RDS_COLON)) {
E 8
I 8
		} else if (status & (RDS_NIBON | RDS_MIIER | RDS_COLON)) {
E 8
E 5
			dp->stats.frame++;
D 8
		}
D 5
		if ((status & RDS_CRCOK) == 0) {
E 5
I 5
		else if ((status & RDS_CRCOK) == 0) {
E 8
I 8
		} else if ((status & RDS_CRCOK) == 0) {
E 8
E 5
			dp->stats.crc++;
D 8
		}
I 5
		else {
E 8
I 8
		} else {
E 8
			dp->stats.rcv_internal_err++;
		}
E 5

		return (flag | GEM_RX_ERR);
	}

	/*
D 8
	 * this packet was received without errors 
E 8
I 8
	 * this packet was received without errors
E 8
	 */
D 13
	len = status & RDS_SIZE;
	if ((rxinfo & RDI_CRCOFF) == 0) {
		if (len - ETHERFCSL > 0) {
			len -= ETHERFCSL;
E 13
I 13
#ifdef CONFIG_CKSUM_OFFLOAD
	if ((rxinfo & (RDI_IPON | RDI_IPOK)) == (RDI_IPON | RDI_IPOK)) {
		if ((rxinfo & (RDI_TCPON | RDI_TCPOK)) ==
		    (RDI_TCPON | RDI_TCPOK)) {
			flag |= GEM_RX_CKSUM_TCP;
		} else if ((rxinfo & (RDI_UDPON | RDI_UDPOK)) ==
		    (RDI_UDPON | RDI_UDPOK)) {
			flag |= GEM_RX_CKSUM_UDP;
		} else {
			flag |= GEM_RX_CKSUM_IPv4;
E 13
		}
	}
D 2

E 2
D 13
#ifdef notdef
D 2
	if (1) {
E 2
I 2
	if (0) {
E 13
I 13
#endif
	len = status & RDS_SIZE;
	if ((rxinfo & RDI_CRCOFF) == 0 && len - ETHERFCSL > 0) {
		len -= ETHERFCSL;
	}
#ifdef CONFIG_RX_PAD
	if ((rxinfo & RDI_PREADD) && len - RM_PAD_LEN > 0) {
		len -= RM_PAD_LEN;
	}
#endif
#ifdef CONFIG_VLAN_HW
	if (status & RDS_TAGON) {
		flag |= ((uint64_t)rxinfo & RDI_VTAG) << GEM_RX_VTAG_SHIFT;
	}
#endif
#if DEBUG_LEVEL > 10
	{
E 13
E 2
		int	i;
D 2
		uint8_t	*bp = dp->rx_buf_head->rxb_buf;
E 2
I 2
D 5
		uint8_t	*bp = &dp->rx_buf_head->rxb_buf[len];
E 5
I 5
D 13
		uint8_t	*bp = &dp->rx_buf_head->rxb_buf[0];
E 13
I 13
		uint8_t	*bp = (void *)&dp->rx_buf_head->rxb_buf[0];
E 13
E 5
E 2

D 2
		cmn_err(CE_CONT, CONS "%s: len:%d", dp->name, len);
E 2
I 2
D 13
		cmn_err(CE_CONT, "!%s: len:%d", dp->name, len);
E 13
I 13
		cmn_err(CE_CONT, "!%s: len:%d (org:%d)",
		    dp->name, len, status & RDS_SIZE);
E 13
E 2

D 2
		for (i = 0; i < 60; i += 10) {
			cmn_err(CE_CONT, CONS
			"%02x %02x %02x %02x %02x %02x %02x %02x %02x %02x",
E 2
I 2
D 5
		for (i = 0; i < 10; i += 10) {
E 5
I 5
		for (i = 0; i < 20; i += 10) {
E 5
			cmn_err(CE_CONT,
D 8
			"!%02x %02x %02x %02x %02x %02x %02x %02x %02x %02x",
E 2
			bp[0], bp[1], bp[2], bp[3], bp[4],
			bp[5], bp[6], bp[7], bp[8], bp[9]);
E 8
I 8
			    "!%02x %02x %02x %02x %02x"
			    " %02x %02x %02x %02x %02x",
			    bp[0], bp[1], bp[2], bp[3], bp[4],
			    bp[5], bp[6], bp[7], bp[8], bp[9]);
E 8
I 5
			bp += 10;
E 5
		}
D 5
		bp += 10;
E 5
	}
#endif
	return (flag | (len & GEM_RX_LEN));
}

D 2
/* DONE */
E 2
static void
sige_tx_desc_init(struct gem_dev *dp, int slot)
{
	struct sige_txdesc	*tdp;

D 8
	tdp = &((struct sige_txdesc *) dp->tx_ring)[slot];
E 8
I 8
	tdp = &((struct sige_txdesc *)dp->tx_ring)[slot];
E 8

	tdp->td_pktsize = 0;
D 8
	tdp->td_cmdsts  = 0;
	tdp->td_bufptr  = 0;
D 2
	tdp->td_eod = (slot == TX_RING_SIZE - 1) ? TX_RING_EOD : 0;
E 2
I 2
	tdp->td_flags   = (slot == TX_RING_SIZE - 1) ? TX_RING_EOD : 0;
E 8
I 8
	tdp->td_cmdsts = 0;
	tdp->td_bufptr = 0;
D 13
	tdp->td_flags = (slot == TX_RING_SIZE - 1) ? TX_RING_EOD : 0;
E 13
I 13
	tdp->td_flags = (slot == dp->gc.gc_tx_ring_size - 1) ? TX_RING_EOD : 0;
E 13
E 8
E 2
}

static void
sige_rx_desc_init(struct gem_dev *dp, int slot)
{
	struct sige_rxdesc	*rdp;

D 8
	rdp = &((struct sige_rxdesc *) dp->rx_ring)[slot];
E 8
I 8
	rdp = &((struct sige_rxdesc *)dp->rx_ring)[slot];
E 8

	rdp->rd_stssize = 0;
	rdp->rd_pktinfo = 0;
D 8
	rdp->rd_bufptr  = 0;
D 2
	rdp->rd_eod = (slot == RX_RING_SIZE - 1) ? RX_RING_EOD : 0;
E 2
I 2
	rdp->rd_flags   = (slot == RX_RING_SIZE - 1) ? RX_RING_EOD : 0;
E 8
I 8
	rdp->rd_bufptr = 0;
	rdp->rd_flags = (slot == RX_RING_SIZE - 1) ? RX_RING_EOD : 0;
E 8
E 2
}

/*
 * Device depend interrupt handler
 */
D 8
static u_int
E 8
I 8
static uint_t
E 8
sige_interrupt(struct gem_dev *dp)
{
	uint32_t	intsrc;
	uint_t		flags = 0;
	boolean_t	need_to_reset = B_FALSE;
D 8
	struct sige_dev	*lp = (struct sige_dev *) dp->private;
E 8
I 8
	struct sige_dev	*lp = dp->private;
E 8

D 2
	/* disable interrupts before clearing intsrc.*/
	OUTL(dp, IntMask, 0);
E 2
I 2
	/* read reason */
	intsrc = INL(dp, ISR);
E 2

D 2
	/* read reason and clear interrupt */
	intsrc = INL(dp, IntSrc);

E 2
	if ((intsrc & lp->our_intr_bits) == 0) {
D 2
		/* not for us, enable interrupts again */
		OUTL(dp, IntMask, lp->our_intr_bits);
E 2
I 2
		/* not for us, clear unused interrupts */
D 5
		if (intsrc != 0) {
E 5
I 5
		if (intsrc) {
E 5
			OUTL(dp, ISR, intsrc);
		}
E 2
		return (DDI_INTR_UNCLAIMED);
	}

I 5
D 8
#ifndef CONFIG_OPT_IO
E 5
D 2
	OUTL(dp, IntSrc, intsrc);
E 2
I 2
	/* disable interrupts before clearing intsrc.*/
	OUTL(dp, IMR, 0);
I 7
	FLSHL(dp, IMR);
E 7
E 2
D 5

E 5
I 5
#endif
E 8
E 5
I 2
	OUTL(dp, ISR, intsrc);
I 7
	FLSHL(dp, ISR);
E 7

E 2
D 3
	DPRINTF(2, (CE_CONT,
E 3
I 3
	DPRINTF(1, (CE_CONT,
E 3
D 2
		CONS "%s: time:%d %s: called: intsrc:0x%b rx_active_head: %d",
E 2
I 2
D 8
		"!%s: time:%d %s: called: intsrc:0x%b rx_active_head: %d",
E 2
		dp->name, ddi_get_lbolt(), __func__,
		intsrc, INT_BITS, dp->rx_active_head));
E 8
I 8
	    "!%s: time:%d %s: called: intsrc:0x%b rx_active_head: %d",
	    dp->name, ddi_get_lbolt(), __func__,
	    intsrc, INT_BITS, dp->rx_active_head));
E 8

D 2
	if (!dp->nic_active) {
E 2
I 2
D 13
	if (!dp->mac_active) {
E 13
I 13
	if (!IS_MAC_ONLINE(dp)) {
E 13
E 2
		/* the device is going to stop */
I 5
D 8
#ifdef CONFIG_OPT_IO
E 8
I 8
		lp->our_intr_bits = 0;
E 8
		OUTL(dp, IMR, 0);
I 7
		FLSHL(dp, IMR);
E 7
D 8
#endif
E 8
E 5
D 2
		return DDI_INTR_CLAIMED;
E 2
I 2
		return (DDI_INTR_CLAIMED);
E 2
	}

I 3
	DPRINTF(1, (CE_CONT,
D 8
		"!%s: time:%d %s: called: intsrc:0x%b rx_active_head: %d",
		dp->name, ddi_get_lbolt(), __func__,
		intsrc, INT_BITS, dp->rx_active_head));
E 8
I 8
	    "!%s: time:%d %s: called: intsrc:0x%b rx_active_head: %d",
	    dp->name, ddi_get_lbolt(), __func__,
	    intsrc, INT_BITS, dp->rx_active_head));
E 8

E 3
D 5
	if ((intsrc & INT_TXHALT) != 0) {
		DPRINTF(0, (CE_NOTE, "%s: %s: tx halt", dp->name, __func__));
E 5
I 5
	if (intsrc & INT_TXHALT) {
		DPRINTF(0, (CE_NOTE, "!%s: %s: tx halt", dp->name, __func__));
E 5
	}

D 5
	if ((intsrc & INT_RXHALT) != 0) {
		DPRINTF(0, (CE_NOTE, "%s: %s: rx halt", dp->name, __func__));
E 5
I 5
	if (intsrc & INT_RXHALT) {
		DPRINTF(0, (CE_NOTE, "!%s: %s: rx halt", dp->name, __func__));
E 5
	}

I 13
#ifdef GEM3
	if (intsrc & (INT_TXDONE | INT_TXIDLE)) {
		/* need to relaim tx buffers */
		if (gem_tx_done(dp)) {
			DPRINTF(1, (CE_NOTE, "!%s: resched tx", dp->name));
			flags |= INTR_RESTART_TX;
		}
#ifdef OPT_TxPOLL
		if (intsrc & INT_TXIDLE) {
			ASSERT(lp->tx_running);
			mutex_enter(&dp->xmitlock);
			if (dp->tx_desc_head != dp->tx_desc_tail) {
				OUTL(dp, TxCTL, lp->tx_control | TxCTL_POLL);
			} else {
				lp->tx_running = B_FALSE;
			}
			mutex_exit(&dp->xmitlock);
		}
#endif
	}
#endif
E 13
D 5
	if ((intsrc & (INT_RXDONE | INT_RXIDLE)) != 0) {
D 2
		gem_receive(dp);
E 2
		if ((intsrc & INT_RXIDLE) != 0) {
I 2
#ifdef notdef
E 2
			/* re-enable rx state machine */
D 2
			OUTL(dp, RxCtrl, lp->rx_control | RxCtrl_POLL);
E 2
I 2
			OUTL(dp, RxCTL, lp->rx_control | RxCTL_POLL);
#else
E 5
I 5
	if (intsrc & (INT_RXDONE | INT_RXIDLE)) {
I 10
		(void) gem_receive(dp);
E 10
		if (intsrc & INT_RXIDLE) {
			/*
			 * we schedule to re-enable rx state machine
			 * when we add rx buffer next time.
			 */
E 5
D 10
			lp->rx_running = B_FALSE;
E 10
I 10
			OUTL(dp, RxCTL, lp->rx_control | RxCTL_POLL);
E 10
D 5
#endif
E 5
I 5

			dp->stats.errrcv++;
			dp->stats.norcvbuf++;
E 5
E 2
		}
I 2
D 8
		gem_receive(dp);
E 8
I 8
D 10
		(void) gem_receive(dp);
E 10
E 8
E 2
	}
D 13

E 13
I 13
#ifndef GEM3
E 13
D 2
	if ((intsrc & INT_TXDONE) != 0) {
E 2
I 2
D 5
	if ((intsrc & (INT_TXDONE | INT_TXIDLE)) != 0) {
E 5
I 5
	if (intsrc & (INT_TXDONE | INT_TXIDLE)) {
E 5
E 2
		/* need to relaim tx buffers */
		if (gem_tx_done(dp)) {
I 3
D 5
			DPRINTF(1, (CE_NOTE, "%s: resched tx", dp->name));
E 5
I 5
			DPRINTF(1, (CE_NOTE, "!%s: resched tx", dp->name));
E 5
E 3
			flags |= INTR_RESTART_TX;
		}
I 2
#ifdef OPT_TxPOLL
D 5
		if ((intsrc & INT_TXIDLE) != 0) {
E 5
I 5
		if (intsrc & INT_TXIDLE) {
E 5
			ASSERT(lp->tx_running);
			mutex_enter(&dp->xmitlock);
			if (dp->tx_desc_head != dp->tx_desc_tail) {
				OUTL(dp, TxCTL, lp->tx_control | TxCTL_POLL);
			} else {
				lp->tx_running = B_FALSE;
			}
			mutex_exit(&dp->xmitlock);
		}
#endif
E 2
	}
D 13

E 13
I 13
#endif
E 13
D 5
	if ((intsrc & INT_LINK) != 0) {
E 5
I 5
	if (intsrc & INT_LINK) {
E 5
D 2
		DPRINTF(0, (CE_NOTE, CONS "%s: %s: link changed",
E 2
I 2
		DPRINTF(2, (CE_NOTE, "!%s: %s: link changed",
E 2
D 8
			dp->name, __func__));
E 8
I 8
		    dp->name, __func__));
I 13
#ifdef GEM3
		gem_mii_link_check(dp);
#else
E 13
E 8
I 2
		if (gem_mii_link_check(dp)) {
			flags |= INTR_RESTART_TX;
		}
I 13
#endif
E 13
E 2
	}

	if (need_to_reset) {
D 3
		gem_restart_nic(dp, B_TRUE);
E 3
I 3
D 8
		gem_restart_nic(dp, GEM_RESTART_KEEP_BUF);
E 8
I 8
		(void) gem_restart_nic(dp, GEM_RESTART_KEEP_BUF);
E 8
E 3
		flags |= INTR_RESTART_TX;
	}

I 5
D 8
#ifndef CONFIG_OPT_IO
E 5
	/* enable interrupts again */
	if ((dp->misc_flag & GEM_NOINTR) == 0) {
D 2
		OUTL(dp, IntMask, lp->our_intr_bits);
E 2
I 2
		OUTL(dp, IMR, lp->our_intr_bits);
I 7
		FLSHL(dp, IMR;
E 7
E 2
	}
I 5
#endif
E 8
	DPRINTF(5, (CE_CONT, "!%s: %s: return: isr: %b",
D 8
	       dp->name, __func__, intsrc, INT_BITS));
E 8
I 8
	    dp->name, __func__, intsrc, INT_BITS));
E 8
E 5

D 2
	DPRINTF(5, (CE_CONT, CONS "%s: sige_interrupt: return: isr: %b",
E 2
I 2
D 5
	DPRINTF(5, (CE_CONT, "!%s: sige_interrupt: return: isr: %b",
E 2
	       dp->name, intsrc, INT_BITS));

E 5
	return (DDI_INTR_CLAIMED | flags);
}

/* ======================================================== */
/*
 * HW depend MII routine
 */
/* ======================================================== */
static void
sige_mii_sync(struct gem_dev *dp)
{
	/* nothing to do */
}

static uint16_t
sige_mii_read(struct gem_dev *dp, uint_t reg)
{
	int		i;
	uint32_t	ret;

D 2
	OUTL(dp, SMI,
		(dp->mii_phy_addr << SMI_PHY_SHIFT) |
		(reg << SMI_REG_SHIFT) |
		SMI_OP_RD | SMI_REQ);
E 2
I 2
	OUTL(dp, GMIICTL,
D 8
		(dp->mii_phy_addr << GMI_PHY_SHIFT) |
		(reg << GMI_REG_SHIFT) |
		GMI_OP_RD | GMI_REQ);
E 8
I 8
	    (dp->mii_phy_addr << GMI_PHY_SHIFT) |
	    (reg << GMI_REG_SHIFT) |
	    GMI_OP_RD | GMI_REQ);
E 8
E 2

	drv_usecwait(10);

D 2
	for (i = 0; ((ret = INL(dp, SMI)) & SMI_REQ) != 0; i++) {
E 2
I 2
D 5
	for (i = 0; ((ret = INL(dp, GMIICTL)) & GMI_REQ) != 0; i++) {
E 2
		if (i > 1000) {
E 5
I 5
D 8
	i = 0;
	while ((ret = INL(dp, GMIICTL)) & GMI_REQ) {
		if (i++ > 1000) {
E 5
			/* timeout error happened */	
E 8
I 8
	for (i = 0; (ret = INL(dp, GMIICTL)) & GMI_REQ; i++) {
		if (i > 1000) {
			/* timeout error happened */
E 8
D 5
			cmn_err(CE_WARN, "%s: %s: timeout", dp->name, __func__);
E 5
I 5
			cmn_err(CE_WARN, "!%s: %s: timeout",
D 8
				dp->name, __func__);
E 5
D 2
			return 0xffff;
E 2
I 2
			return (0xffff);
E 8
I 8
			    dp->name, __func__);
			return (0);
E 8
E 2
		}
		drv_usecwait(10);
	}

D 2
	return ((ret & SMI_DATA) >> SMI_DATA_SHIFT);
E 2
I 2
	return ((ret & GMI_DATA) >> GMI_DATA_SHIFT);
E 2
}

static void
sige_mii_write(struct gem_dev *dp, uint_t reg, uint16_t val)
{
	int		i;

I 12
	/* workaround for starting auto-negotiation */
D 13
	if (reg == MII_CONTROL && (val & MII_CONTROL_RSAN)) {
E 13
I 13
	if ((dp->mii_status & MII_STATUS_XSTATUS) &&
	    reg == MII_CONTROL && (val & MII_CONTROL_RSAN)) {
E 13
		val |= MII_CONTROL_RESET;
	}

E 12
D 2
	OUTL(dp, SMI,
		(((uint32_t) val) << SMI_DATA_SHIFT) |
		(((uint32_t) dp->mii_phy_addr) << SMI_PHY_SHIFT) |
		(reg << SMI_REG_SHIFT) |
		SMI_OP_WR | SMI_REQ);
E 2
I 2
	OUTL(dp, GMIICTL,
D 8
		(((uint32_t) val) << GMI_DATA_SHIFT) |
		(((uint32_t) dp->mii_phy_addr) << GMI_PHY_SHIFT) |
		(reg << GMI_REG_SHIFT) |
		GMI_OP_WR | GMI_REQ);
E 8
I 8
	    (((uint32_t)val) << GMI_DATA_SHIFT) |
	    (((uint32_t)dp->mii_phy_addr) << GMI_PHY_SHIFT) |
	    (reg << GMI_REG_SHIFT) |
	    GMI_OP_WR | GMI_REQ);
E 8
E 2

	drv_usecwait(10);

D 2
	for (i= 0; (INL(dp, SMI) & SMI_REQ) != 0; i++) {
E 2
I 2
D 5
	for (i= 0; (INL(dp, GMIICTL) & GMI_REQ) != 0; i++) {
E 2
		if (i > 1000) {
E 5
I 5
D 8
	i = 0;
	while (INL(dp, GMIICTL) & GMI_REQ) {
		if (i++ > 1000) {
E 5
			/* timeout error happened */	
E 8
I 8
	for (i = 0; INL(dp, GMIICTL) & GMI_REQ; i++) {
		if (i > 1000) {
			/* timeout error happened */
E 8
D 5
			cmn_err(CE_WARN, "%s: %s: timeout", dp->name, __func__);
E 5
I 5
			cmn_err(CE_WARN, "!%s: %s: timeout",
D 8
				dp->name, __func__);
E 8
I 8
			    dp->name, __func__);
E 8
E 5
			break;
		}
		drv_usecwait(10);
	}
}

static int
sige_mii_init(struct gem_dev *dp)
{
D 8
	struct sige_dev	*lp = (struct sige_dev *)dp->private;
E 8
I 8
	struct sige_dev	*lp = dp->private;
E 8

D 2
	if (gem_mii_init_default(dp) != 0) {
		return -1;
E 2
I 2
D 5
	if (gem_mii_init_default(dp) != GEM_SUCCESS) {
		return (GEM_FAILURE);
E 2
	}

E 5
D 8
#define	PHY_ID_MARVELL88E1111	0x01410cc1
#define	PHY_ID_BCM5461_1	0x00206021
E 8
	switch (dp->mii_phy_id) {
	case PHY_ID_MARVELL88E1111:
		if (lp->phy_rgmii) {
			sige_mii_write(dp, 0x1b, 0x808b);
			drv_usecwait(200);
			sige_mii_write(dp, 0x14, 0x0ce1);
			drv_usecwait(200);
D 8
		}
		else {
E 8
I 8
		} else {
E 8
			sige_mii_write(dp, 0x1b, 0x808f);
			drv_usecwait(200);
			sige_mii_write(dp, 0x14, 0x0c60);
			drv_usecwait(200);
		}
		break;

	case PHY_ID_BCM5461_1:
		/* for Broadcom BCM5461 PHY, set Tx Delay in RGMII mode */
		if (lp->phy_rgmii) {
			sige_mii_write(dp, 0x18, 0xf1c7);
			drv_usecwait(200);
			sige_mii_write(dp, 0x1c, 0x8c00);
I 5
			drv_usecwait(200);
E 5
		}
		break;
	}

D 2
	return (0);
E 2
I 2
	return (GEM_SUCCESS);
E 2
}

/* ======================================================== */
/*
 * OS depend (device driver) routine
 */
/* ======================================================== */
static int
D 8
sige_attach_chip(struct gem_dev *dp)	
E 8
I 8
sige_attach_chip(struct gem_dev *dp)
E 8
{
I 12
	int	ret;
E 12
D 8
	struct sige_dev	*lp = (struct sige_dev *) dp->private;
D 2
	boolean_t	mac_ok;
E 2
I 2
	int	ret;
E 8
I 8
	struct sige_dev	*lp = dp->private;
D 12
	int		ret;
E 12
E 8
E 2

D 2
	DPRINTF(4, (CE_CONT, CONS "%s: %s: called", dp->name, __func__));
E 2
I 2
	DPRINTF(4, (CE_CONT, "!%s: %s: called", dp->name, __func__));
E 2

D 2
	if (!(mac_ok = gem_get_mac_addr_conf(dp))) {
		if (lp->mac_in_apc) {
			mac_ok = sige_get_mac_addr_apc(dp);
		} else {
			mac_ok = sige_get_mac_addr_eeprom(dp);
		}
E 2
I 2
	if (lp->mac_in_apc) {
		ret = sige_get_mac_addr_apc(dp);
	} else {
		ret = sige_get_mac_addr_eeprom(dp);
E 2
	}

D 2
	if (!mac_ok) {
		cmn_err(CE_WARN,
			"%s: %s: cannot read mac address from %s",
				dp->name, __func__,
				lp->mac_in_apc
					? "apc registger" : "eeprom");
		gem_generate_macaddr(dp, dp->dev_addr.ether_addr_octet);
E 2
I 2
	if (ret != GEM_SUCCESS) {
		cmn_err(CE_WARN, "%s: %s: cannot read mac address from %s",
D 8
			dp->name, __func__,
			lp->mac_in_apc ? "apc registger" : "eeprom");
E 8
I 8
		    dp->name, __func__,
		    lp->mac_in_apc ? "apc registger" : "eeprom");
E 8
		if (!gem_get_mac_addr_conf(dp)) {
D 5
			gem_generate_macaddr(dp, dp->dev_addr.ether_addr_octet);
E 5
I 5
			gem_generate_macaddr(dp,
D 8
					dp->dev_addr.ether_addr_octet);
E 8
I 8
			    dp->dev_addr.ether_addr_octet);
E 8
E 5
		}
E 2
	}

D 2
	lp->our_intr_bits = OUR_INTR_BITS;

E 2
	/* fix rx buffer length, it must be aligned by 8 */
D 2
        dp->rx_buf_len =
		ROUNDUP(dp->mtu + sizeof(struct ether_header) + ETHERFCSL, 8);

#ifdef GEM_CONFIG_CKSUM_OFFLOAD
	dp->misc_flag |= (GEM_CKSUM_IPv4 | GEM_CKSUM_TCP | GEM_CKSUM_UDP);
E 2
I 2
D 8
        dp->rx_buf_len = ROUNDUP(dp->rx_buf_len, 8);
E 8
I 8
	dp->rx_buf_len = ROUNDUP(dp->rx_buf_len, 8);
E 8
D 13
#ifdef CONFIG_VLAN
E 13
I 13
#ifdef CONFIG_VLAN_HW
	dp->misc_flag |= GEM_VLAN_HARD;
#else
E 13
	dp->misc_flag |= GEM_VLAN_SOFT;
D 13
#elif defined(GEM_CONFIG_CKSUM_OFFLOAD)
I 8
	/* XXX - GEM_CKSUM_FULL_IPv4 didn't work */
E 8
D 9
	dp->misc_flag |= GEM_CKSUM_PARTIAL; /* ok */
E 9
I 9
	dp->misc_flag |= GEM_CKSUM_PARTIAL;
E 13
E 9
D 6
	/* dp->misc_flag |= GEM_CKSUM_FULL_IPv4;  /* didn't work */
E 6
I 6
D 8
# if NEVER
	dp->misc_flag |= GEM_CKSUM_FULL_IPv4;  /* didn't work */
# endif
E 8
E 6
E 2
#endif
I 13
#ifdef CONFIG_CKSUM_OFFLOAD
#ifdef CONFIG_LSO
	dp->misc_flag |= GEM_LSO;
#endif
	dp->misc_flag |= GEM_CKSUM_NOFULL_IPv4;
#endif
E 13
I 12

	/* 1G half mode isn't supported */
	dp->anadv_1000hdx = B_FALSE;

E 12
D 2

	return (0);
E 2
I 2
	return (GEM_SUCCESS);
E 2
}

static int
sigeattach(dev_info_t *dip, ddi_attach_cmd_t cmd)
{
	int			unit;
	const char		*drv_name;
	int			i;
	ddi_acc_handle_t	conf_handle;
	uint16_t		vid;
	uint16_t		did;
	uint8_t			rev;
	uint8_t			cfg73;
#ifdef DEBUG_LEVEL
	uint32_t		iline;
	uint8_t			latim;
#endif
	struct chip_info	*p;
	struct gem_dev		*dp;
	struct sige_dev		*lp;
	void			*base;
	ddi_acc_handle_t	regs_ha;
	struct gem_conf		*gcp;

D 8
	unit     = ddi_get_instance(dip);
E 8
I 8
	unit = ddi_get_instance(dip);
E 8
	drv_name = ddi_driver_name(dip);

D 2
	DPRINTF(3, (CE_CONT, CONS "%s%d: %s: called (%s)",
E 2
I 2
	DPRINTF(3, (CE_CONT, "!%s%d: %s: called (%s)",
E 2
D 8
		drv_name, unit, __func__, ident));
E 8
I 8
	    drv_name, unit, __func__, ident));
E 8

	/*
	 * Common codes after power-up
	 */
	if (pci_config_setup(dip, &conf_handle) != DDI_SUCCESS) {
D 5
		cmn_err(CE_WARN, "%s%d: ddi_regs_map_setup failed",
E 5
I 5
		cmn_err(CE_WARN, "!%s%d: ddi_regs_map_setup failed",
E 5
D 8
			drv_name, unit);
E 8
I 8
		    drv_name, unit);
E 8
		goto err;
	}

D 8
	vid  = pci_config_get16(conf_handle, PCI_CONF_VENID);
	did  = pci_config_get16(conf_handle, PCI_CONF_DEVID);
	rev  = pci_config_get16(conf_handle, PCI_CONF_REVID);
E 8
I 8
	vid = pci_config_get16(conf_handle, PCI_CONF_VENID);
	did = pci_config_get16(conf_handle, PCI_CONF_DEVID);
	rev = pci_config_get16(conf_handle, PCI_CONF_REVID);
E 8
#ifdef DEBUG_LEVEL
D 8
	iline =	pci_config_get32(conf_handle, PCI_CONF_ILINE),
E 8
I 8
D 9
	iline =	pci_config_get32(conf_handle, PCI_CONF_ILINE);
E 9
I 9
	iline = pci_config_get32(conf_handle, PCI_CONF_ILINE);
E 9
E 8
	latim = pci_config_get8(conf_handle, PCI_CONF_LATENCY_TIMER);
#endif
	for (i = 0, p = sige_chiptbl; i < CHIPTABLESIZE; i++, p++) {
		if (p->venid == vid && p->devid == did) {
			/* found */
			goto chip_found;
		}
	}

	/* Not found */
D 5
	cmn_err(CE_WARN, 
		"%s%d: sige_attach: wrong PCI venid/devid (0x%x, 0x%x)",
		drv_name, unit, vid, did);
	pci_config_teardown(&conf_handle);
	goto err;
E 5
I 5
D 8
	cmn_err(CE_NOTE, 
		"!%s%d: %s: unknown PCI venid/devid (0x%x, 0x%x)",
		drv_name, unit, __func__, vid, did);
E 8
I 8
	cmn_err(CE_NOTE,
	    "!%s%d: %s: unknown PCI venid/devid (0x%x, 0x%x)",
	    drv_name, unit, __func__, vid, did);
E 8
	/* fall through */
E 5

chip_found:
	pci_config_put16(conf_handle, PCI_CONF_COMM,
D 8
		PCI_COMM_IO | PCI_COMM_MAE | PCI_COMM_ME |
			pci_config_get16(conf_handle, PCI_CONF_COMM));
E 8
I 8
	    PCI_COMM_IO | PCI_COMM_MAE | PCI_COMM_ME |
	    pci_config_get16(conf_handle, PCI_CONF_COMM));
E 8

	cfg73 = pci_config_get8(conf_handle, 0x73);

	/* ensure D0 mode */
	(void) gem_pci_set_power_state(dip, conf_handle, PCI_PMCSR_D0);

	pci_config_teardown(&conf_handle);

	switch (cmd) {
	case DDI_RESUME:
D 2
		return gem_resume(dip);
E 2
I 2
		return (gem_resume(dip));
E 2

	case DDI_ATTACH:

		DPRINTF(0, (CE_CONT,
D 2
			CONS "%s%d: ilr 0x%08x, latency_timer:0x%02x",
E 2
I 2
D 8
			"!%s%d: ilr 0x%08x, latency_timer:0x%02x",
E 2
			drv_name, unit, iline, latim));
E 8
I 8
		    "!%s%d: ilr 0x%08x, latency_timer:0x%02x",
		    drv_name, unit, iline, latim));
E 8
		/*
		 * Map in the device registers.
		 */

		if (gem_pci_regs_map_setup(dip,
#ifdef MAP_MEM
D 2
			PCI_ADDR_MEM32,
E 2
I 2
D 8
			PCI_ADDR_MEM32, PCI_ADDR_MASK,
E 8
I 8
		    PCI_ADDR_MEM32, PCI_ADDR_MASK,
E 8
E 2
#else
D 2
			PCI_ADDR_IO,
E 2
I 2
D 8
			PCI_ADDR_IO, PCI_ADDR_MASK,
E 8
I 8
		    PCI_ADDR_IO, PCI_ADDR_MASK,
E 8
E 2
#endif
D 8
			&sige_dev_attr, (caddr_t *)&base, &regs_ha) !=
								DDI_SUCCESS) {
E 8
I 8
		    &sige_dev_attr, (void *)&base, &regs_ha) !=
		    DDI_SUCCESS) {
E 8
D 5
			cmn_err(CE_WARN, "%s%d: ddi_regs_map_setup failed",
E 5
I 5
			cmn_err(CE_WARN, "!%s%d: ddi_regs_map_setup failed",
E 5
D 8
				drv_name, unit);
E 8
I 8
			    drv_name, unit);
E 8
			goto err;
		}

		/*
		 * construct gem configration
		 */
D 8
		gcp = (struct gem_conf *) kmem_zalloc(sizeof(*gcp), KM_SLEEP);
E 8
I 8
		gcp = (struct gem_conf *)kmem_zalloc(sizeof (*gcp), KM_SLEEP);
E 8

		/* name */
		sprintf(gcp->gc_name, "%s%d", drv_name, unit);

		/* consistency on tx and rx */
D 8
		gcp->gc_tx_buf_align = sizeof(uint8_t) - 1;
E 8
I 8
		gcp->gc_tx_buf_align = sizeof (uint8_t) - 1;
E 8
		gcp->gc_tx_max_frags = MAXTXFRAGS;
		gcp->gc_tx_max_descs_per_pkt = gcp->gc_tx_max_frags;
		gcp->gc_tx_desc_unit_shift = 4;
D 8
		gcp->gc_tx_buf_size   = TX_BUF_SIZE;
		gcp->gc_tx_buf_limit  = gcp->gc_tx_buf_size;
		gcp->gc_tx_ring_size  = TX_RING_SIZE;
E 8
I 8
		gcp->gc_tx_buf_size = TX_BUF_SIZE;
		gcp->gc_tx_buf_limit = gcp->gc_tx_buf_size;
		gcp->gc_tx_ring_size = TX_RING_SIZE;
E 8
D 13
		gcp->gc_tx_ring_limit = gcp->gc_tx_ring_size;
E 13
I 13
		gcp->gc_tx_ring_limit = gcp->gc_tx_ring_size - 1;
E 13
D 8
		gcp->gc_tx_auto_pad   = B_TRUE;
E 8
I 8
		gcp->gc_tx_auto_pad = B_TRUE;
E 8
		gcp->gc_tx_copy_thresh = sige_tx_copy_thresh;
D 2
		gcp->gc_tx_desc_write_oo = B_FALSE;
E 2
I 2
D 10
		gcp->gc_tx_desc_write_oo = B_TRUE;
E 10
E 2

D 8
		gcp->gc_rx_buf_align = sizeof(uint64_t) - 1;
E 8
I 8
		gcp->gc_rx_buf_align = sizeof (uint64_t) - 1;
E 8
		gcp->gc_rx_max_frags = 1;
		gcp->gc_rx_desc_unit_shift = 4;
		gcp->gc_rx_ring_size = RX_RING_SIZE;
D 8
		gcp->gc_rx_buf_max   = RX_BUF_SIZE;
E 8
I 8
		gcp->gc_rx_buf_max = RX_BUF_SIZE;
E 8
		gcp->gc_rx_copy_thresh = sige_rx_copy_thresh;
I 13
#ifdef CONFIG_RX_PAD
		gcp->gc_rx_header_len = RM_PAD_LEN;
#else
E 13
I 2
		gcp->gc_rx_header_len = 0;
E 2
D 13

E 13
I 13
#endif
E 13
D 8
		gcp->gc_io_area_size   = 0;
E 8
I 8
		gcp->gc_io_area_size = 0;
E 8

		/* map attributes */
D 4
		STRUCT_COPY(gcp->gc_dev_attr, sige_dev_attr);
		STRUCT_COPY(gcp->gc_buf_attr, sige_buf_attr);
		STRUCT_COPY(gcp->gc_desc_attr, sige_buf_attr);
E 4
I 4
		gcp->gc_dev_attr = sige_dev_attr;
		gcp->gc_buf_attr = sige_buf_attr;
		gcp->gc_desc_attr = sige_buf_attr;
E 4

		/* dma attributes */
D 4
		STRUCT_COPY(gcp->gc_dma_attr_desc, sige_dma_attr_desc);
E 4
I 4
		gcp->gc_dma_attr_desc = sige_dma_attr_desc;
E 4

D 4
		STRUCT_COPY(gcp->gc_dma_attr_txbuf, sige_dma_attr_buf);
E 4
I 4
		gcp->gc_dma_attr_txbuf = sige_dma_attr_buf;
E 4
		gcp->gc_dma_attr_txbuf.dma_attr_align = gcp->gc_tx_buf_align+1;
		gcp->gc_dma_attr_txbuf.dma_attr_sgllen = gcp->gc_tx_max_frags;

D 4
		STRUCT_COPY(gcp->gc_dma_attr_rxbuf, sige_dma_attr_buf);
E 4
I 4
		gcp->gc_dma_attr_rxbuf = sige_dma_attr_buf;
E 4
		gcp->gc_dma_attr_rxbuf.dma_attr_align = gcp->gc_rx_buf_align+1;
		gcp->gc_dma_attr_rxbuf.dma_attr_sgllen = gcp->gc_rx_max_frags;

		/* time out parameters */
		gcp->gc_tx_timeout = 3*ONESEC;
		gcp->gc_tx_timeout_interval = ONESEC;

		/* MII timeout parameters */
		gcp->gc_mii_link_watch_interval = ONESEC;
D 8
		gcp->gc_mii_an_watch_interval   = ONESEC/5;
E 8
I 8
		gcp->gc_mii_an_watch_interval = ONESEC/5;
E 8
		gcp->gc_mii_reset_timeout = MII_RESET_TIMEOUT;	/* 1 sec */
		gcp->gc_mii_an_timeout = MII_AN_TIMEOUT;	/* 5 sec */
		gcp->gc_mii_an_wait = 0;
		gcp->gc_mii_linkdown_timeout = MII_LINKDOWN_TIMEOUT;

		/* setting for general PHY */
D 8
		gcp->gc_mii_an_delay =  0;
E 8
I 8
		gcp->gc_mii_an_delay = 0;
E 8
		gcp->gc_mii_linkdown_action = MII_ACTION_RSA;
		gcp->gc_mii_linkdown_timeout_action = MII_ACTION_RESET;
		gcp->gc_mii_dont_reset = B_FALSE;
I 2
D 9
		gcp->gc_mii_hw_link_detection = B_TRUE;
E 9
E 2

I 9
		/*
		 * XXX - we cannot enable hw_link_detection because a
		 * phy didn't generate interrupts on link down after
		 * once it became link up.
		 */
		gcp->gc_mii_hw_link_detection = B_FALSE;
E 9
D 5
		if (p->chip_type == CHIPTYPE_SIS191) {
			gcp->gc_mii_mode = GEM_MODE_1000BASET;
		} else {
			gcp->gc_mii_mode = GEM_MODE_100BASETX;
		}
E 5

I 9

E 9
D 5

E 5
		/* I/O methods */

		/* mac operation */
		gcp->gc_attach_chip = &sige_attach_chip;
		gcp->gc_reset_chip = &sige_reset_chip;
D 8
		gcp->gc_init_chip  = &sige_init_chip;
E 8
I 8
		gcp->gc_init_chip = &sige_init_chip;
E 8
		gcp->gc_start_chip = &sige_start_chip;
D 8
		gcp->gc_stop_chip  = &sige_stop_chip;
E 8
I 8
		gcp->gc_stop_chip = &sige_stop_chip;
E 8
		gcp->gc_multicast_hash = &sige_mcast_hash;
		gcp->gc_set_rx_filter = &sige_set_rx_filter;
		gcp->gc_set_media = &sige_set_media;
		gcp->gc_get_stats = &sige_get_stats;
		gcp->gc_interrupt = &sige_interrupt;

		/* descriptor operation */
		gcp->gc_tx_desc_write = &sige_tx_desc_write;
		gcp->gc_rx_desc_write = &sige_rx_desc_write;
		gcp->gc_tx_start = &sige_tx_start;
D 2
		gcp->gc_rx_start = NULL;
E 2
I 2
D 10
		gcp->gc_rx_start = &sige_rx_start;
E 10
I 10
		gcp->gc_rx_start = NULL;
E 10
E 2

D 8
		gcp->gc_tx_desc_stat  = &sige_tx_desc_stat;
		gcp->gc_rx_desc_stat  = &sige_rx_desc_stat;
		gcp->gc_tx_desc_init  = &sige_tx_desc_init;
		gcp->gc_rx_desc_init  = &sige_rx_desc_init;
		gcp->gc_tx_desc_clean = &sige_tx_desc_init;
		gcp->gc_rx_desc_clean = &sige_rx_desc_init;
E 8
I 8
D 9
		gcp->gc_tx_desc_stat =	&sige_tx_desc_stat;
		gcp->gc_rx_desc_stat =	&sige_rx_desc_stat;
		gcp->gc_tx_desc_init =	&sige_tx_desc_init;
		gcp->gc_rx_desc_init =	&sige_rx_desc_init;
		gcp->gc_tx_desc_clean =	&sige_tx_desc_init;
		gcp->gc_rx_desc_clean =	&sige_rx_desc_init;
E 9
I 9
		gcp->gc_tx_desc_stat = &sige_tx_desc_stat;
		gcp->gc_rx_desc_stat = &sige_rx_desc_stat;
		gcp->gc_tx_desc_init = &sige_tx_desc_init;
		gcp->gc_rx_desc_init = &sige_rx_desc_init;
		gcp->gc_tx_desc_clean = &sige_tx_desc_init;
		gcp->gc_rx_desc_clean = &sige_rx_desc_init;
E 9
E 8

		/* mii operations */
I 5
D 8
		gcp->gc_mii_probe    = &gem_mii_probe_default;
E 5
		gcp->gc_mii_init     = &sige_mii_init;
		gcp->gc_mii_config   = &gem_mii_config_default;
		gcp->gc_mii_sync     = &sige_mii_sync;
		gcp->gc_mii_read     = &sige_mii_read;
		gcp->gc_mii_write    = &sige_mii_write;
		gcp->gc_flow_control = FLOW_CONTROL_SYMMETRIC;
E 8
I 8
D 9
		gcp->gc_mii_probe =	&gem_mii_probe_default;
		gcp->gc_mii_init =	&sige_mii_init;
		gcp->gc_mii_config =	&gem_mii_config_default;
		gcp->gc_mii_sync =	&sige_mii_sync;
		gcp->gc_mii_read =	&sige_mii_read;
		gcp->gc_mii_write =	&sige_mii_write;
		gcp->gc_flow_control =	FLOW_CONTROL_SYMMETRIC;
E 9
I 9
		gcp->gc_mii_probe = &gem_mii_probe_default;
		gcp->gc_mii_init = &sige_mii_init;
		gcp->gc_mii_config = &gem_mii_config_default;
		gcp->gc_mii_sync = &sige_mii_sync;
		gcp->gc_mii_read = &sige_mii_read;
		gcp->gc_mii_write = &sige_mii_write;
		gcp->gc_flow_control = FLOW_CONTROL_SYMMETRIC;
E 9
E 8

D 8
		lp = (struct sige_dev *)
			kmem_zalloc(sizeof(struct sige_dev), KM_SLEEP);

E 8
I 8
		lp = kmem_zalloc(sizeof (struct sige_dev), KM_SLEEP);
D 9
#if 0
		p = &sige_chiptbl[1];
#endif
E 9
E 8
		lp->chip = p;
		lp->mac_in_apc = (cfg73 & 0x01) != 0;

		DPRINTF(0, (CE_CONT,
D 2
			CONS "%s%d: chip:%s rev:0x%02x, cfg73:0x%02x",
E 2
I 2
D 8
			"!%s%d: chip:%s rev:0x%02x, cfg73:0x%02x",
E 2
			drv_name, unit, p->chip_name, rev, cfg73));
E 8
I 8
		    "!%s%d: chip:%s rev:0x%02x, cfg73:0x%02x",
		    drv_name, unit, p->chip_name, rev, cfg73));
E 8

I 13
		/* offload and jumbo frame */
		gcp->gc_max_lso = 16 * 1024 - 1;
		gcp->gc_max_mtu = ETHERMTU;
		gcp->gc_default_mtu = ETHERMTU;
		gcp->gc_min_mtu = ETHERMIN - sizeof (struct ether_header);

E 13
D 5
		ddi_set_driver_private(dip, NULL);

		dp = gem_do_attach(dip, gcp, base, &regs_ha,
E 5
I 5
		dp = gem_do_attach(dip, 0, gcp, base, &regs_ha,
E 5
D 8
			lp, sizeof(*lp));
		kmem_free(gcp, sizeof(*gcp));
E 8
I 8
		    lp, sizeof (*lp));
		kmem_free(gcp, sizeof (*gcp));
E 8

		if (dp == NULL) {
			goto err_freelp;
		}

D 2
		return DDI_SUCCESS;
E 2
I 2
		return (DDI_SUCCESS);
E 2

err_freelp:
D 8
		kmem_free(lp, sizeof(struct sige_dev));
E 8
I 8
		kmem_free(lp, sizeof (struct sige_dev));
E 8
err:
D 2
		return DDI_FAILURE;
E 2
I 2
		return (DDI_FAILURE);
E 2
	}
D 2
	return DDI_FAILURE;
E 2
I 2
	return (DDI_FAILURE);
E 2
}

D 2
/* DONE */
E 2
static int
sigedetach(dev_info_t *dip, ddi_detach_cmd_t cmd)
{
	switch (cmd) {
	case DDI_SUSPEND:
D 2
		return  gem_suspend(dip);
E 2
I 2
		return (gem_suspend(dip));
E 2

	case DDI_DETACH:
D 2
		return  gem_do_detach(dip);
E 2
I 2
		return (gem_do_detach(dip));
E 2
	}
D 2
	return DDI_FAILURE;
E 2
I 2
	return (DDI_FAILURE);
E 2
}

/* ======================================================== */
/*
 * OS depend (loadable streams driver) routine
 */
/* ======================================================== */
I 8
#ifdef GEM_CONFIG_GLDv3
D 11
DDI_DEFINE_STREAM_OPS(sige_ops, nulldev, nulldev, sigeattach, sigedetach,
    nodev, NULL, D_MP, NULL);
E 11
I 11
GEM_STREAM_OPS(sige_ops, sigeattach, sigedetach);
E 11
#else
E 8
static	struct module_info sigeminfo = {
	0,			/* mi_idnum */
	"sige",			/* mi_idname */
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

static	struct qinit sigerinit = {
	(int (*)()) NULL,	/* qi_putp */
	gem_rsrv,		/* qi_srvp */
	gem_open,		/* qi_qopen */
	gem_close,		/* qi_qclose */
	(int (*)()) NULL,	/* qi_qadmin */
	&sigeminfo,		/* qi_minfo */
	NULL			/* qi_mstat */
};

static	struct qinit sigewinit = {
	gem_wput,		/* qi_putp */
	gem_wsrv,		/* qi_srvp */
	(int (*)()) NULL,	/* qi_qopen */
	(int (*)()) NULL,	/* qi_qclose */
	(int (*)()) NULL,	/* qi_qadmin */
	&sigeminfo,		/* qi_minfo */
	NULL			/* qi_mstat */
};

static struct streamtab	sige_info = {
	&sigerinit,	/* st_rdinit */
	&sigewinit,	/* st_wrinit */
	NULL,		/* st_muxrinit */
	NULL		/* st_muxwrinit */
};

static	struct cb_ops cb_sige_ops = {
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
	&sige_info,	/* cb_stream */
	D_MP,		/* cb_flag */
};

static	struct dev_ops sige_ops = {
	DEVO_REV,	/* devo_rev */
	0,		/* devo_refcnt */
	gem_getinfo,	/* devo_getinfo */
	nulldev,	/* devo_identify */
	nulldev,	/* devo_probe */
	sigeattach,	/* devo_attach */
	sigedetach,	/* devo_detach */
	nodev,		/* devo_reset */
	&cb_sige_ops,	/* devo_cb_ops */
	NULL,		/* devo_bus_ops */
D 2
	ddi_power	/* devo_power */
E 2
I 2
	gem_power,	/* devo_power */
E 2
};
I 8
#endif
E 8

static struct modldrv modldrv = {
	&mod_driverops,	/* Type of module.  This one is a driver */
	ident,
	&sige_ops,	/* driver ops */
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
D 8
	int 	status;
E 8
I 8
	int	status;
E 8

D 2
	DPRINTF(2, (CE_CONT, CONS "sige: _init: called"));
	status = mod_install(&modlinkage);
E 2
I 2
	DPRINTF(2, (CE_CONT, "!sige: _init: called"));
E 2

I 2
	gem_mod_init(&sige_ops, "sige");
	status = mod_install(&modlinkage);
	if (status != DDI_SUCCESS) {
		gem_mod_fini(&sige_ops);
	}
E 2
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
	DPRINTF(2, (CE_CONT, CONS "sige: _fini: called"));
E 2
I 2
	DPRINTF(2, (CE_CONT, "!sige: _fini: called"));
E 2
	status = mod_remove(&modlinkage);
I 2
	if (status == DDI_SUCCESS) {
		gem_mod_fini(&sige_ops);
	}
E 2
	return (status);
}

int
_info(struct modinfo *modinfop)
{
	return (mod_info(&modlinkage, modinfop));
}
E 1
