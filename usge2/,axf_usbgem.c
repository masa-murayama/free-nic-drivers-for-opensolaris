/*
 * axf_usbgem.c : axis ax88172 USB to Fast Ethernet Driver for Solaris
 *
 * Copyright (c) 2004 Masayuki Murayama.  All rights reserved.
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

#pragma ident "%W% %E%"

/*
 *  Changelog:
 */

/*
 * TODO
 */
/* ======================================================= */

/*
 * Solaris system header files and macros
 */
#include <sys/types.h>
#include <sys/conf.h>
#include <sys/debug.h>
#include <sys/stropts.h>
#include <sys/stream.h>
#include <sys/strlog.h>
#include <sys/kmem.h>
#include <sys/stat.h>
#include <sys/kstat.h>
#include <sys/vtrace.h>
#include <sys/dlpi.h>
#include <sys/strsun.h>
#include <sys/ethernet.h>
#include <sys/modctl.h>
#include <sys/errno.h>
#include <sys/ddi.h>
#include <sys/sunddi.h>
#include <sys/gld.h>
#include <sys/ddi_impldefs.h>

#include <sys/usb/usba.h>

#include "usbgem.h"
#include "mii.h"
#include "ax88172reg.h"

char	ident[] = "ax88172 usbnic driver v" VERSION;
char	_depends_on[] = {"misc/gld misc/usba"};

/*
 * Useful macros
 */
#define	ROUNDUP2(x, y)	(((x)+(y)-1) & ~((y)-1))
#define	FALSE	(0)
#define	TRUE	(!FALSE)
#define	CHECK_AND_JUMP(err, label)	if (err != USB_SUCCESS) goto label
#define	LE16P(p)	(((uint8_t *)(p))[1]<<8 | ((uint8_t *)(p))[0])
#define	AX88172(dp)	TRUE

/*
 * Debugging
 */
#ifdef DEBUG_LEVEL
static int axf_debug = DEBUG_LEVEL;
#define DPRINTF(n, args)	if (axf_debug > (n)) cmn_err args
#else
#define DPRINTF(n, args)
#endif

/*
 * Our configration for ax88172
 */
/* timeouts */
#define	ONESEC			(drv_usectohz(1*1000000))

/*
 * RX/TX buffer size
 */

/*
 * Local device definitions
 */
struct chip_info {
	uint16_t	vid;
	uint16_t	did;
	int		flags;
	char		*name;
	int		type;
};

#define	CHIPTABLESIZE	(sizeof(chiptbl_88172)/sizeof(struct chip_info))

struct axf_dev {
	/*
	 * Misc HW information
	 */
	struct chip_info	*chip;
	uint8_t			ipg[3];
	uint8_t			rcr[2];
	uint8_t			msr;
};

/*
 * private functions
 */
 
/* mii operations */
static void  axf_mii_sync(struct usbgem_dev *, int *errp);
static uint16_t  axf_mii_read(struct usbgem_dev *, int, int *errp);
static void axf_mii_write(struct usbgem_dev *, int, uint16_t, int *errp);

/* nic operations */
static int axf_reset_chip(struct usbgem_dev *);
static int axf_init_chip(struct usbgem_dev *);
static int axf_start_chip(struct usbgem_dev *);
static int axf_stop_chip(struct usbgem_dev *);
static int axf_set_media(struct usbgem_dev *);
static int axf_set_rx_filter(struct usbgem_dev *);
static int axf_get_stats(struct usbgem_dev *);
static int axf_init_mac_addr(struct usbgem_dev *);

/* packet operations */
static mblk_t *axf_tx_make_packet(struct usbgem_dev *, mblk_t *);
static mblk_t *axf_rx_make_packet(struct usbgem_dev *, mblk_t *);

/* =============================================================== */
/*
 * I/O functions
 */
/* =============================================================== */
#define	OUT(dp, req, val, ix, len, buf, errp, label)	\
	if ((*(errp) = usbgem_ctrl_out((dp), 	\
	/* bmRequestType */ USB_DEV_REQ_HOST_TO_DEV	\
		    | USB_DEV_REQ_TYPE_VENDOR | USB_DEV_REQ_RCPT_DEV,	\
	/* bRequest */ (req),	\
	/* wValue */   (val),	\
	/* wIndex */   (ix),	\
	/* wLength */  (len),	\
	/* value */    (buf),	\
	/* size */     (len))) != USB_SUCCESS) goto label

#define IN(dp, req, val, ix, len, buf, errp, label)	\
	if ((*(errp) = usbgem_ctrl_in((dp), 	\
	/* bmRequestType */ USB_DEV_REQ_DEV_TO_HOST	\
		    | USB_DEV_REQ_TYPE_VENDOR | USB_DEV_REQ_RCPT_DEV,	\
	/* bRequest */ (req),	\
	/* wValue */   (val),	\
	/* wIndex */   (ix),	\
	/* wLength */  (len),	\
	/* valuep */   (buf),	\
	/* size */     (len))) != USB_SUCCESS) goto label

/* =============================================================== */
/*
 * variables
 */
/* =============================================================== */
static int axf_ppa = 0;

/* =============================================================== */
/*
 * Hardware manupilation
 */
/* =============================================================== */
static int
axf_reset_chip(struct usbgem_dev *dp)
{
	struct axf_dev	*lp = (struct axf_dev *)dp->private;

	DPRINTF(2, (CE_CONT, "!%s: axf_reset_chip: called", dp->name));

	return USB_SUCCESS;
}

/*
 * Setup ax88172
 */
static int
axf_init_chip(struct usbgem_dev *dp)
{
	int		i;
	uint32_t	val;
	int		err;
	struct axf_dev	*lp = (struct axf_dev *)dp->private;

	DPRINTF(2, (CE_CONT, "!%s: axf_init_chip: called", dp->name));

	/* rx configuration register: read default value */
	IN(dp, 0x0f, 0, 0, 2, lp->rcr, &err, usberr);
	DPRINTF(0, (CE_CONT, "!%s: axf_init_chip: rcr(default):%b",
		dp->name, LE16P(lp->rcr), RCR_BITS));
	lp->rcr[0] &= ~RCR_SO;

	/* Media status register */
	IN(dp, 0x1a, 0, 0, 1, &lp->msr, &err, usberr);
	err = axf_set_media(dp);
	CHECK_AND_JUMP(err, usberr);

	/* write IPG0-2 registers */
	if (AX88172(dp)) {
		OUT(dp,0x12, lp->ipg[0], 0, 0, NULL, &err, usberr);
		OUT(dp,0x13, lp->ipg[1], 0, 0, NULL, &err, usberr);
		OUT(dp,0x14, lp->ipg[2], 0, 0, NULL, &err, usberr);
	}
	else {
		/* ax88772 */
		OUT(dp,0x12, lp->ipg[0], lp->ipg[1], lp->ipg[2],
			NULL, &err, usberr);
	}

	DPRINTF(2, (CE_CONT, "!%s: axf_start_chip: end (success)", dp->name));
	return USB_SUCCESS;

usberr:
	cmn_err(CE_NOTE, "!%s: axf_start_chip: usberr detected", dp->name);
	return USB_FAILURE;
}

static int
axf_start_chip(struct usbgem_dev *dp)
{
	int		err;
	struct axf_dev	*lp = (struct axf_dev *)dp->private;

	lp->rcr[0] |= RCR_SO;
	OUT(dp, 0x10, lp->rcr[0], lp->rcr[1], 0, NULL, &err, usberr);
usberr:
	return USB_SUCCESS;
}

static int
axf_stop_chip(struct usbgem_dev *dp)
{
	int		err;
	struct axf_dev	*lp = (struct axf_dev *)dp->private;

	/* Enable Rx */
	lp->rcr[0] &= ~RCR_SO;
	OUT(dp, 0x10, lp->rcr[0], lp->rcr[1], 0, NULL, &err, usberr);
usberr:
	return axf_reset_chip(dp);
}

static int
axf_get_stats(struct usbgem_dev *dp)
{
	/* do nothing */
	return USB_SUCCESS;
}

static uint_t
axf_mcast_hash(struct usbgem_dev *dp, uint8_t *addr)
{
	return usbgem_ether_crc_be(addr);
}

static int
axf_set_rx_filter(struct usbgem_dev *dp)
{
	int		i;
	uint8_t		mode;
	uint8_t		mhash[8];
	int		err;
	uint8_t		buf[2];
	uint_t		h;
	struct axf_dev	*lp = (struct axf_dev *)dp->private;

	DPRINTF(2, (CE_CONT, "!%s: axf_set_rx_mode: called, rxmode:%x",
		dp->name, dp->rxmode));

	if ((lp->rcr[0] & RCR_SO) != 0) {
		/* disable rx filter before changing it. */
	 	OUT(dp, 0x10, lp->rcr[0] & ~RCR_SO, lp->rcr[1], 0,
			NULL, &err, usberr);
	}

	lp->rcr[0] &= ~(RCR_AP | RCR_AM | RCR_SEP | RCR_AMALL | RCR_PRO);
	mode = RCR_AB;	/* accept broadcast */

	bzero(mhash, sizeof(mhash));

	if ((dp->rxmode & RXMODE_PROMISC) != 0) {
		/* promiscious mode implies all multicast and all physical */
		mode |= RCR_PRO;
	}
	else if ((dp->rxmode & RXMODE_ALLMULTI) != 0 || dp->mc_count > 32) {
		/* accept all multicast packets */
		mode |= RCR_AMALL;
	}	
	else if (dp->mc_count > 0) {
		/*
		 * make hash table to select interresting
		 * multicast address only.
		 */
		mode |= RCR_AM;
		for (i = 0; i < dp->mc_count; i++) {
			/* hash table is 64 = 2^6 bit width */
			h = dp->mc_list[i].hash >> (32 - 6);
			mhash[h / 8] |= 1 << (h % 8);
		}
	}	
	if (AX88172(dp)) {
		if (bcmp(dp->dev_addr.ether_addr_octet,
			dp->cur_addr.ether_addr_octet, ETHERADDRL) != 0) { 
			/*
			 * we use promiscious mode instead of changing the
			 * mac address in ax88172
			 */
			mode |= RCR_PRO;
		}
	}
	else {
		OUT(dp, 0x14, 0, 0, ETHERADDRL,
			dp->cur_addr.ether_addr_octet, &err, usberr);
	}
	lp->rcr[0] |= mode;

	/* set multicast hash table */
	if ((mode & RCR_AM) != 0) {
		/* need to set up multicast hash table */
		OUT(dp, 0x16, 0, 0, sizeof(mhash), mhash, &err, usberr);
	}

	/* update rcr */
	OUT(dp, 0x10, lp->rcr[0], lp->rcr[1], 0, NULL, &err, usberr);

#if DEBUG_LEVEL > 1
	IN(dp, 0x0f, 0, 0, 2, buf, &err, usberr);
	cmn_err(CE_CONT, "!%s: axf_set_rx_filter: rcr:%b returned",
		dp->name, LE16P(buf), RCR_BITS);
#endif
	return USB_SUCCESS;

usberr:
	cmn_err(CE_NOTE, "!%s: axf_set_rx_filter: usberr detected", dp->name);
	return USB_FAILURE;
}

static int
axf_set_media(struct usbgem_dev *dp)
{
	uint8_t		msr;
	int		err;
	struct axf_dev	*lp = (struct axf_dev *)dp->private;

	DPRINTF(2, (CE_CONT, "!%s: axf_set_media: called", dp->name));

	msr = lp->msr & ~(MSR_FDPX | MSR_FCEN);

	/* select duplex */
	if (dp->full_duplex) {
		msr |= MSR_FDPX;
	}

	/* select speed: do nothing */

	/* select flow control */
	if (dp->full_duplex && dp->flow_control) {
		msr |= MSR_FCEN; 
	}

	/* update medium status register */
	lp->msr = msr;
	OUT(dp, 0x1b, lp->msr, 0, 0, NULL, &err, usberr);

	DPRINTF(2, (CE_CONT, "!axf_set_media: returned"));

	return USB_SUCCESS;

usberr:
	cmn_err(CE_NOTE, "!%s: axf_set_media: usberr detected", dp->name);
	return USB_FAILURE;
}

/*
 * send/receive packet check
 */
static mblk_t *
axf_tx_make_packet(struct usbgem_dev *dp, mblk_t *mp)
{
	size_t		len;
	size_t		n;
	mblk_t		*new;
	mblk_t		*tp;
	uint8_t		*bp;

	len = msgdsize(mp);

	if (len > ETHERMAX) {
		return NULL;
	}

	if (len < ETHERMIN || mp->b_cont != NULL) {
		/*	
		 * re-allocate mp
		 */
		n = max(len, ETHERMIN);
		if ((new = allocb(n, 0)) == NULL) {
			return NULL;
		}

		/* copy contents of the buffer */
		if (len < ETHERMIN) {
			bzero(new->b_rptr, ETHERMIN);
		}
		new->b_wptr = new->b_rptr + n;
		bp = new->b_rptr;
		for (tp = mp; tp; tp = tp->b_cont) {
			len = tp->b_wptr - tp->b_rptr;
			bcopy(tp->b_rptr, bp, len);
			bp += len;
		}
		mp = new;
	}

	return mp;
}

static void
axf_dump_packet(struct usbgem_dev *dp, uint8_t *bp, int n)
{
	int	i;

	for (i=0; i < n; i += 8, bp += 8) {
		cmn_err(CE_CONT, "%02x %02x %02x %02x %02x %02x %02x %02x",
		bp[0], bp[1], bp[2], bp[3], bp[4], bp[5], bp[6], bp[7]);
	}
}

static mblk_t *
axf_rx_make_packet(struct usbgem_dev *dp, mblk_t *mp)
{
	return mp;
}

/* 
 * MII Interfaces
 */
static void
axf_mii_sync(struct usbgem_dev *dp, int *errp)
{
	DPRINTF(4, (CE_CONT, "!%s: axf_mii_sync: called", dp->name));

	/* do nothing */
	*errp = USB_SUCCESS;
}

static uint16_t
axf_mii_read(struct usbgem_dev *dp, int index, int *errp)
{
	uint8_t		buf[2];
	uint16_t	val;

	DPRINTF(4, (CE_CONT, "!%s: axf_mii_read: called, ix:%d",
		dp->name, index));

	*errp = USB_SUCCESS;

	/* Software MII Operation */
	OUT(dp, 0x06, 0, 0, 0, NULL, errp, usberr);

	/* Read MII register */
	IN(dp, 0x07, dp->mii_phy_addr, index, 2, buf, errp, usberr);

	/* Hardware MII Operation */
	OUT(dp, 0x0a, 0, 0, 0, NULL, errp, usberr);

	val = LE16P(buf);
	if (index == MII_STATUS && val != 0) {
		/* avoid to call mii_sync */
		val |= MII_STATUS_MFPRMBLSUPR;
	}
	return val;

usberr:
	cmn_err(CE_CONT,
		"!%s: axf_mii_read: usberr(%d) detected", dp->name, *errp);

	return 0;
}

static void
axf_mii_write(struct usbgem_dev *dp, int index, uint16_t val, int *errp)
{
	uint8_t		buf[2];

	DPRINTF(5, (CE_CONT, "!%s: axf_mii_write called", dp->name));

	*errp = USB_SUCCESS;

	/* Software MII Operation */
	OUT(dp, 0x06, 0, 0, 0, NULL, errp, usberr);

	/* Write to the specified MII register */
	buf[0] = val;
	buf[1] = val >> 8;
	OUT(dp, 0x08, dp->mii_phy_addr, index, 2, buf, errp, usberr);

	/* Hardware MII Operation */
	OUT(dp, 0x0a, 0, 0, 0, NULL, errp, usberr);

usberr:
	return;
}

/* ======================================================== */
/*
 * OS depend (device driver DKI) routine
 */
/* ======================================================== */
#ifdef DEBUG_LEVEL
static void
axf_eeprom_dump(struct usbgem_dev *dp, int size)
{
	int	i;
	int	err;
	uint8_t	w0[2], w1[2], w2[2], w3[2];

	cmn_err(CE_CONT, "!%s: eeprom dump:", dp->name);

	err = USB_SUCCESS;

	for (i = 0; i < size; i += 4) {
		IN(dp, 0x0b, i + 0, 0, 2, w0, &err, usberr);
		IN(dp, 0x0b, i + 1, 0, 2, w1, &err, usberr);
		IN(dp, 0x0b, i + 2, 0, 2, w2, &err, usberr);
		IN(dp, 0x0b, i + 3, 0, 2, w3, &err, usberr);
		cmn_err(CE_CONT, "!0x%02x: 0x%04x 0x%04x 0x%04x 0x%04x",
			i*8,
			(w0[1] << 8) | w0[0],
			(w1[1] << 8) | w1[0],
			(w2[1] << 8) | w2[0],
			(w3[1] << 8) | w3[0]);
	}
usberr:
	return;
}
#endif

static int
axf_attach_chip(struct usbgem_dev *dp)
{
	int		err;
	struct axf_dev	*lp = (struct axf_dev *)dp->private;

	DPRINTF(0, (CE_CONT, "!%s: axf_attach enter", dp->name));

	/* wait 100mS until the PHY becomes stable */
	delay(drv_usectohz(500*1000));

	/*
	 * mac address in EEPROM has loaded to ID registers.
	 */
	IN(dp, 0x17, 0, 0, ETHERADDRL,
		dp->dev_addr.ether_addr_octet, &err, usberr);

	/*
	 * read IPG values
	 */
	IN(dp,0x11, 0, 0, 3, lp->ipg, &err, usberr);

	DPRINTF(0, (CE_CONT, "%s: axf_attach_chip: ipg %x %x %x",
		dp->name, lp->ipg[0], lp->ipg[1], lp->ipg[2]));

	/* no need to scan phy */
	dp->mii_phy_addr = 0;

	/* we dont use interrupt messages */
	dp->misc_flag |= USBGEM_NOINTR;

#if DEBUG_LEVEL > 2
	axf_eeprom_dump(dp, 0x80);
#endif
	return USB_SUCCESS;

usberr:
	cmn_err(CE_WARN, "%s: axf_attach_chip: usb error detected", dp->name);
	return USB_FAILURE;
}

static int
axfattach(dev_info_t *dip, ddi_attach_cmd_t cmd)
{
	int			i;
	ddi_iblock_cookie_t	c;
	int			ret;
	int			revid;
	int			unit;
	struct chip_info	*p;
	int			len;
	const char		*drv_name;
	struct usbgem_dev	*dp;
	void			*base;
	struct usbgem_conf	*ugcp;
	struct axf_dev		*lp;

	unit =  ddi_get_instance(dip);
	drv_name = ddi_driver_name(dip);

	DPRINTF(3, (CE_CONT, "!%s%d: axfattach: called, cmd:%d",
			drv_name, unit, cmd));

	if (cmd == DDI_ATTACH) {
		/*
		 * Check if the chip is supported.
		 */

		/*
		 * construct usbgem configration
		 */
		ugcp = (struct usbgem_conf *) kmem_zalloc(sizeof(*ugcp), KM_SLEEP);

		/* name */
		sprintf(ugcp->usbgc_name, "%s%d(ppa=%d)", drv_name, unit, axf_ppa);
		ugcp->usbgc_ppa = axf_ppa;

		ugcp->usbgc_ifnum = 0;
		ugcp->usbgc_alt   = 0;

		ugcp->usbgc_tx_auto_pad   = FALSE;
		ugcp->usbgc_tx_list_max   = 128;

		ugcp->usbgc_rx_header_len = 0; /* no additional rx info */
		ugcp->usbgc_rx_list_max   = 16;

		/* time out parameters */
		ugcp->usbgc_tx_timeout = 2*ONESEC;
		ugcp->usbgc_tx_timeout_interval = ONESEC;

		/* flow control */
		ugcp->usbgc_flow_control = TRUE;

		/* MII timeout parameters */
		ugcp->usbgc_mii_link_watch_interval = ONESEC;
		ugcp->usbgc_mii_an_watch_interval = ONESEC/5;
		ugcp->usbgc_mii_reset_timeout = MII_RESET_TIMEOUT;	/* 1 sec */
		ugcp->usbgc_mii_an_timeout    = MII_AN_TIMEOUT;	/* 5 sec */
		ugcp->usbgc_mii_an_wait = (25*ONESEC)/10;
		ugcp->usbgc_mii_linkdown_timeout = MII_LINKDOWN_TIMEOUT;

		ugcp->usbgc_mii_an_delay   = ONESEC/10;
		ugcp->usbgc_mii_linkdown_action = MII_ACTION_RESET;
		ugcp->usbgc_mii_dont_reset      = FALSE;

		/* I/O methods */

		/* mac operation */
		ugcp->usbgc_attach_chip = &axf_attach_chip;
		ugcp->usbgc_reset_chip  = &axf_reset_chip;
		ugcp->usbgc_init_chip   = &axf_init_chip;
		ugcp->usbgc_start_chip  = &axf_start_chip;
		ugcp->usbgc_stop_chip   = &axf_stop_chip;
		ugcp->usbgc_multicast_hash = &axf_mcast_hash;

		ugcp->usbgc_set_rx_filter = &axf_set_rx_filter;
		ugcp->usbgc_set_media   = &axf_set_media;
		ugcp->usbgc_get_stats   = &axf_get_stats;
		ugcp->usbgc_interrupt   = NULL;

		/* packet operation */
		ugcp->usbgc_tx_make_packet = &axf_tx_make_packet;
		ugcp->usbgc_rx_make_packet = &axf_rx_make_packet;

		/* mii operations */
		ugcp->usbgc_mii_init   = &usbgem_mii_init_default;
		ugcp->usbgc_mii_config = &usbgem_mii_config_default;
		ugcp->usbgc_mii_sync  = &axf_mii_sync;
		ugcp->usbgc_mii_read  = &axf_mii_read;
		ugcp->usbgc_mii_write = &axf_mii_write;

		ugcp->usbgc_mii_tune_phy = NULL;

		lp = (struct axf_dev *)
			kmem_zalloc(sizeof(struct axf_dev), KM_SLEEP);
		lp->chip = p;

		ddi_set_driver_private(dip, NULL);

		dp = usbgem_do_attach(dip, ugcp, lp, sizeof(struct axf_dev));

		kmem_free(ugcp, sizeof(*ugcp));

		if (dp != NULL) {
			axf_ppa++;
			return DDI_SUCCESS;
		}
		
err_free_mem:
		kmem_free(lp, sizeof(struct axf_dev));
err_close_pipe:
err:
		return DDI_FAILURE;
	}
	return DDI_FAILURE;
}

static int
axfdetach(dev_info_t *dip, ddi_detach_cmd_t cmd)
{
	int	ret;

	if (cmd == DDI_DETACH) {
		ret = usbgem_do_detach(dip);
		if (ret != DDI_SUCCESS) {
			DDI_FAILURE;
		}
		axf_ppa--;
		return DDI_SUCCESS;
	}
	return DDI_FAILURE;
}

/* ======================================================== */
/*
 * OS depend (loadable streams driver) routine
 */
/* ======================================================== */
static	struct module_info axfminfo = {
	0,			/* mi_idnum */
	"axf",			/* mi_idname */
	0,			/* mi_minpsz */
	ETHERMTU,		/* mi_maxpsz */
	32*1024,		/* mi_hiwat */
	1,			/* mi_lowat */
};

static	struct qinit axfrinit = {
	(int (*)()) NULL,	/* qi_putp */
	usbgem_rsrv,		/* qi_srvp */
	usbgem_open,		/* qi_qopen */
	usbgem_close,		/* qi_qclose */
	(int (*)()) NULL,	/* qi_qadmin */
	&axfminfo,		/* qi_minfo */
	NULL			/* qi_mstat */
};

static	struct qinit axfwinit = {
	usbgem_wput,		/* qi_putp */
	usbgem_wsrv,		/* qi_srvp */
	(int (*)()) NULL,	/* qi_qopen */
	(int (*)()) NULL,	/* qi_qclose */
	(int (*)()) NULL,	/* qi_qadmin */
	&axfminfo,		/* qi_minfo */
	NULL			/* qi_mstat */
};

static struct streamtab	axf_info = {
	&axfrinit,	/* st_rdinit */
	&axfwinit,	/* st_wrinit */
	NULL,		/* st_muxrinit */
	NULL		/* st_muxwrinit */
};

static	struct cb_ops cb_axf_ops = {
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
	&axf_info,	/* cb_stream */
	D_NEW|D_MP	/* cb_flag */
};

static	struct dev_ops axf_ops = {
	DEVO_REV,	/* devo_rev */
	0,		/* devo_refcnt */
	usbgem_getinfo,	/* devo_getinfo */
	nulldev,	/* devo_identify */
	nulldev,	/* devo_probe */
	axfattach,	/* devo_attach */
	axfdetach,	/* devo_detach */
	nodev,		/* devo_reset */
	&cb_axf_ops,	/* devo_cb_ops */
	NULL,		/* devo_bus_ops */
	ddi_power	/* devo_power */
};

static struct modldrv modldrv = {
	&mod_driverops,	/* Type of module.  This one is a driver */
	ident,
	&axf_ops,	/* driver ops */
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

	DPRINTF(2, (CE_CONT, "!axf: _init: called"));
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

	DPRINTF(2, (CE_CONT, "!axf: _fini: called"));
	status = mod_remove(&modlinkage);
	return (status);
}

int
_info(struct modinfo *modinfop)
{
	return (mod_info(&modlinkage, modinfop));
}

