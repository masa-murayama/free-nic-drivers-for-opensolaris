/*
 * usge_usbgem.c : SmSC LAN7500 USB to Giga Ethernet Driver for Solaris
 *
 * Copyright (c) 2012-2016 Masayuki Murayama.  All rights reserved.
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

/* minimum kernel headers for drivers */
#include <sys/types.h>
#include <sys/sysmacros.h>
#include <sys/conf.h>
#include <sys/debug.h>
#include <sys/kmem.h>
#include <sys/modctl.h>
#include <sys/errno.h>
#include <sys/ddi.h>
#include <sys/sunddi.h>
#include <sys/byteorder.h>

/* ethernet stuff */
#include <sys/ethernet.h>
#include <sys/gld.h>

/* interface card depend stuff */
#include <sys/stropts.h>
#include <sys/stream.h>
#include <sys/strlog.h>
#include <sys/strsun.h>
#include <sys/usb/usba.h>
#include "usbgem.h"
#include "usbgem_mii.h"

/* hardware stuff */
#include "lan7500reg.h"

char	ident[] = "SmSC LAN7500 driver " VERSION;

/*
 * Useful macros
 */
#define	CHECK_AND_JUMP(err, label)	if (err != USB_SUCCESS) goto label

/*
 * Debugging
 */
#ifdef DEBUG_LEVEL
static int usge_debug = DEBUG_LEVEL;
#define	DPRINTF(n, args)	if (usge_debug > (n)) cmn_err args
#else
#define	DPRINTF(n, args)
#endif

/*
 * Our configration for ax88172
 */
/* timeouts */
#define	ONESEC		(drv_usectohz(1*1000000))

/*
 * RX/TX buffer size
 */

/*
 * Local device definitions
 */
struct usge_dev {
	uint32_t	rxctl;
	boolean_t	turbo;
	uint32_t	last_phycsr;
	boolean_t	linkdown_latched;
	uint64_t	pmatch[PMAF_ENTRY_NUM];
	uint32_t	mhash[DPSEL_VHF_HASH_LEN];
};

/*
 * private functions
 */

/* mii operations */
static uint16_t  usge_mii_read(struct usbgem_dev *, uint_t, int *errp);
static void usge_mii_write(struct usbgem_dev *, uint_t, uint16_t, int *errp);

/* nic operations */
static int usge_reset_chip(struct usbgem_dev *);
static int usge_init_chip(struct usbgem_dev *);
static int usge_start_chip(struct usbgem_dev *);
static int usge_stop_chip(struct usbgem_dev *);
static int usge_set_media(struct usbgem_dev *);
static int usge_set_rx_filter(struct usbgem_dev *);
static int usge_get_stats(struct usbgem_dev *);
static int usge_init_mac_addr(struct usbgem_dev *);

/* packet operations */
static mblk_t *usge_tx_make_packet(struct usbgem_dev *, mblk_t *);
static mblk_t *usge_rx_make_packet(struct usbgem_dev *, mblk_t *);

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

#define	OUTL(dp, ix, val, errp, label)	\
	if ((*(errp) = usbgem_ctrl_out_val((dp), 	\
	/* bmRequestType */ USB_DEV_REQ_HOST_TO_DEV	\
		    | USB_DEV_REQ_TYPE_VENDOR | USB_DEV_REQ_RCPT_DEV,	\
	/* bRequest */ (USB_VENDOR_REQUEST_WRITE_REGISTER),	\
	/* wValue */   (0),	\
	/* wIndex */   (ix),	\
	/* wLength */  (4),	\
	/* value */    (val))) != USB_SUCCESS) goto label

#define	IN(dp, req, val, ix, len, buf, errp, label)	\
	if ((*(errp) = usbgem_ctrl_in((dp), 	\
	/* bmRequestType */ USB_DEV_REQ_DEV_TO_HOST	\
		    | USB_DEV_REQ_TYPE_VENDOR | USB_DEV_REQ_RCPT_DEV,	\
	/* bRequest */ (req),	\
	/* wValue */   (val),	\
	/* wIndex */   (ix),	\
	/* wLength */  (len),	\
	/* valuep */   (buf),	\
	/* size */     (len))) != USB_SUCCESS) goto label

#define	INL(dp, ix, valp, errp, label)	\
	if ((*(errp) = usbgem_ctrl_in_val((dp), 	\
	/* bmRequestType */ USB_DEV_REQ_DEV_TO_HOST	\
		    | USB_DEV_REQ_TYPE_VENDOR | USB_DEV_REQ_RCPT_DEV,	\
	/* bRequest */ (USB_VENDOR_REQUEST_READ_REGISTER),	\
	/* wValue */   (0),	\
	/* wIndex */   (ix),	\
	/* wLength */  (4),	\
	/* valuep */   (valp))) != USB_SUCCESS) goto label

/* =============================================================== */
/*
 * variables
 */
/* =============================================================== */

/* =============================================================== */
/*
 * debugging support
 */
/* =============================================================== */
static int
usge_dump_regs(struct usbgem_dev *dp)
{
	int	err = USB_SUCCESS;
	int	i;
	uint32_t	val[4];

	for (i = 0; i < 16*256; i += 4*4) {
		INL(dp, i + 0 * 4, &val[0], &err, usberr);
		INL(dp, i + 1 * 4, &val[1], &err, usberr);
		INL(dp, i + 2 * 4, &val[2], &err, usberr);
		INL(dp, i + 3 * 4, &val[3], &err, usberr);

		cmn_err(CE_CONT, "!%s: %02x: %08x %08x %08x %08x",
		    __func__, i,
		    val[0], val[1], val[2], val[3]);
	}
usberr:
	return (err);
}
/* =============================================================== */
/*
 * Hardware manupilation
 */
/* =============================================================== */
static int
usge_dp_wait_idle(struct usbgem_dev *dp)
{
	int	i;
	int	err;
	uint32_t	val;

	err = USB_SUCCESS;
	i = 0;
	for (;;) {
		INL(dp, DPSEL, &val, &err, usberr);
		if (val & DPSEL_DPRDY) {
			break;
		}
		if (i++ > 100) {
			/* timeout */
			cmn_err(CE_CONT, "!%s: %s: timeout",
			    dp->name, __func__);
			err = USB_FAILURE;
			break;
		}
		drv_usecwait(40);
	}
usberr:
	return (err);
}

static int
usge_reset_chip(struct usbgem_dev *dp)
{
	int		i;
	uint32_t	val;
	int		err = USB_SUCCESS;
	struct usge_dev	*lp = dp->private;

	DPRINTF(0, (CE_CONT, "!%s: %s: called", dp->name, __func__));
#if DEBUG_LEVEL > 0
	INL(dp, PHYCSR, &val, &err, usberr);
	cmn_err(CE_CONT, "!%s: %s: PHYCSR:%b",
	    dp->name, __func__, val, PHYCSR_BITS);
#endif
	INL(dp, HWCFG, &val, &err, usberr);
	val |= HWCFG_LRST;
	OUTL(dp, HWCFG, val, &err, usberr);

	i = 0;
	do {
		if (i++ > 100) {
			/* timeout */
			cmn_err(CE_WARN, "!%s: %s: timeout: HWCFG_LRST",
			    dp->name, __func__);
			err = USB_FAILURE;
			goto usberr;
		}
		delay(drv_usectohz(10*1000));
		INL(dp, HWCFG, &val, &err, usberr);
	} while ((val & HWCFG_LRST) != 0);

#if DEBUG_LEVEL > 0
	INL(dp, HWCFG, &val, &err, usberr);
	cmn_err(CE_CONT, "!%s: %s: HWCFG:%b",
	    dp->name, __func__, val, HWCFG_BITS);
#endif
#if 0
	INL(dp, PMCSR, &val, &err, usberr);
	val |= PMCSR_PHY_RST;
	OUTL(dp, PMCSR, val, &err, usberr);

	i = 0;
	do {
		if (++i > 100) {
			/* timeout */
			cmn_err(CE_CONT,
			    "!%s: %s: timeout: PMCSR_PHY_RST",
			    __func__, dp->name);
			goto usberr;
		}
		delay(drv_usectohz(10*1000));
		INL(dp, PMCSR, &val, &err, usberr);
	} while ((val & PMCSR_PHY_RST) != 0);
#endif
#if 0
#if DEBUG_LEVEL > 0
	INL(dp, PMCSR, &val, &err, usberr);
	cmn_err(CE_CONT, "!%s: %s: PMCSR:%b",
	    dp->name, __func__, val, PMCSR_BITS);

	OUTL(dp, PHYCSR, PHYCSR_ADP | PHYCSR_ADD | PHYCSR_ASD, &err, usberr);
	INL(dp, PHYCSR, &val, &err, usberr);
	DPRINTF(0, (CE_CONT, "!%s: %s: PHYCSR:%x",
	    dp->name, __func__, val));
#endif
#endif
	DPRINTF(0, (CE_CONT, "!%s: %s: done", dp->name, __func__));

usberr:
	return (err);
}

/*
 * Setup lan7500
 */
static int
usge_init_chip(struct usbgem_dev *dp)
{
	int		i;
	uint32_t	val;
	int		err = USB_SUCCESS;
	uint16_t	reg;
	uint8_t		buf[2];
	struct usge_dev	*lp = dp->private;

	DPRINTF(2, (CE_CONT, "!%s: %s: called", dp->name, __func__));

	INL(dp, HWCFG, &val, &err, usberr);
	val |= HWCFG_BIR;
	OUTL(dp, HWCFG, val, &err, usberr);

#if DEBUG_LEVEL > 0
	INL(dp, HWCFG, &val, &err, usberr);
	cmn_err(CE_CONT, "!%s: %s: HWCFG:%b",
	    dp->name, __func__, val, HWCFG_BITS);
#endif

	OUTL(dp, BURSTLMT, (16 * 1024 + 5 * 512)/512, &err, usberr);

	OUTL(dp, RXDELAY, 0x2000, &err, usberr);

	if (lp->turbo) {
		INL(dp, HWCFG, &val, &err, usberr);
		val |= HWCFG_MEF | HWCFG_BCE;
		OUTL(dp, HWCFG, val, &err, usberr);
#if DEBUG_LEVEL > 0
		INL(dp, HWCFG, &val, &err, usberr);
		cmn_err(CE_CONT, "!%s: %s: HWCFG:%b",
		    dp->name, __func__, val, HWCFG_BITS);
#endif
	}

	OUTL(dp, RXFIFOEND, (20*1024 - 512)/512, &err, usberr);	/* ok */
	OUTL(dp, TXFIFOEND, (12*1024 - 512)/512, &err, usberr);	/* ok */

	OUTL(dp, INTS, INTS_CLEAR_ALL, &err, usberr);	/* ok */

#if DEBUG_LEVEL > 0
	INL(dp, IDREV, &val, &err, usberr);
	cmn_err(CE_CONT, "!%s: %s: IDREV:%x", dp->name, __func__, val);
#endif


        /* setup GPIO */
	INL(dp, LEDCFG, &val, &err, usberr);
	val &= ~(LEDCFG_LED2_FUN_SEL | LEDCFG_LED10_FUN_SEL);
	val |= LEDCFG_LEDGPIO_EN | LEDCFG_LED2_FUN_SEL;
	OUTL(dp, LEDCFG, val, &err, usberr);

	OUTL(dp, FLCTL, 0, &err, usberr);
	OUTL(dp, FIFOTHSH, 0, &err, usberr);

	INL(dp, RXFCTL, &val, &err, usberr);
	DPRINTF(0, (CE_CONT, "!%s: %s: RXFCTL:%b",
	    dp->name, __func__, val, RXFCTL_BITS));

#ifdef CONFIG_PERFECT_FILTER
	/* clear perfect match address filter table */
	for (i = 0; i < PMAF_ENTRY_NUM; i++) {
		OUTL(dp, PMAF_BASE + i*8, 0, &err, usberr);
		OUTL(dp, PMAF_BASE + i*8 + 4, 0, &err, usberr);
		lp->pmatch[i] = 0;
	}
#endif
	/* clear multicast hash table */
	for (i = 0; i < DPSEL_VHF_HASH_LEN; i++) {
		OUTL(dp, DPADDR, DPSEL_VHF_VLAN_LEN + i, &err, usberr);
		OUTL(dp, DPDATA, 0, &err, usberr);
		OUTL(dp, DPCMD, DPCMD_WRITE, &err, usberr);
		if (usge_dp_wait_idle(dp) != USB_SUCCESS) {
			goto usberr;
		}
		lp->mhash[i] = 0;
	}
#ifdef notdef
	val |= RXFCTL_AB | RXFCTL_DPF;
	OUTL(dp, RXFCTL, val, &err, usberr);
#else
	lp->rxctl = RXFCTL_AB | RXFCTL_DPF;
#endif
	/* XXX - we don't use cksum offload for the time being */
	INL(dp, RXFCTL, &val, &err, usberr);
	val &= ~(RXFCTL_TCPUDPCK | RXFCTL_IPCK);
	OUTL(dp, RXFCTL, val, &err, usberr);

#if DEBUG_LEVEL > 0
	INL(dp, RXFCTL, &val, &err, usberr);
	cmn_err(CE_CONT, "!%s: %s: RXFCTL:%b",
	    dp->name, __func__, val, RXFCTL_BITS);
#endif

usberr:
	DPRINTF(2, (CE_CONT, "!%s: %s: end %d (%s)",
	    dp->name, __func__,
	    err, err == USB_SUCCESS ? "success" : "error"));
	return (err);
}

static int
usge_start_chip(struct usbgem_dev *dp)
{
	int	err = USB_SUCCESS;
	uint32_t	val;
	struct usge_dev	*lp = dp->private;

	DPRINTF(2, (CE_CONT, "!%s: %s: called", dp->name, __func__));

	INL(dp, PMCSR, &val, &err, usberr);
	cmn_err(CE_CONT, "!%s: %s: PMCSR:%b",
	    dp->name, __func__, val, PMCSR_BITS);

	INL(dp, PHYCSR, &val, &err, usberr);
	val |= PHYCSR_ADD | PHYCSR_ASD;
	OUTL(dp, PHYCSR, val, &err, usberr);

	INL(dp, PHYCSR, &val, &err, usberr);
	DPRINTF(0, (CE_CONT, "!%s: %s: PHYCSR:%b",
	    dp->name, __func__, val, PHYCSR_BITS));

#ifdef notdef
	INL(dp, INTCTL, &val, &err, usberr);
	val |= INTEP_PHY_EN;
	OUTL(dp, INTCTL, val, &err, usberr);
#endif
	INL(dp, TXCTL, &val, &err, usberr);
	val |= TXCTL_EN;
	OUTL(dp, TXCTL, val, &err, usberr);

	INL(dp, TXFIFO, &val, &err, usberr);
	val |= TXFIFO_EN;
	OUTL(dp, TXFIFO, val, &err, usberr);

	INL(dp, RXCTL, &val, &err, usberr);
	val &= ~RXCTL_MAXSIZE;
	val |= RXCTL_EN
	    | (dp->mtu + sizeof (struct ether_header) + 4 + ETHERFCSL)
	    << RXCTL_MAXSIZE_SHIFT;
	OUTL(dp, RXCTL, val, &err, usberr);

	INL(dp, RXFIFO, &val, &err, usberr);
	val |= RXFIFO_EN;
	OUTL(dp, RXFIFO, val, &err, usberr);
#if 0
	usge_dump_regs(dp);
#endif
usberr:
	DPRINTF(2, (CE_CONT, "!%s: %s: end %d (%s)",
	    dp->name, __func__,
	    err, err == USB_SUCCESS ? "success" : "error"));
	return (err);
}

static int
usge_stop_chip(struct usbgem_dev *dp)
{
	uint32_t	val;
	int	err = USB_SUCCESS;
	struct usge_dev	*lp = dp->private;

	/* Disable Rx */
	INL(dp, RXFIFO, &val, &err, usberr);
	val &= ~RXFIFO_EN;
	OUTL(dp, RXFIFO, val, &err, usberr);

	INL(dp, RXCTL, &val, &err, usberr);
	val &= ~RXCTL_EN;
	OUTL(dp, RXCTL, val, &err, usberr);

usberr:
	return (usge_reset_chip(dp));
}

static int
usge_get_stats(struct usbgem_dev *dp)
{
	/* EMPTY */
	return (USB_SUCCESS);
}


static int
usge_dp_write(struct usbgem_dev *dp,
    uint32_t ram, uint32_t addr, uint32_t len, uint32_t *datap)
{
	int	i;
	int	err;
	uint32_t	val;

	err = USB_SUCCESS;

	for (i = 0; i < len; i++) {
		OUTL(dp, DPADDR, addr + i, &err, usberr);
		OUTL(dp, DPDATA, datap[i], &err, usberr);
		OUTL(dp, DPCMD, DPCMD_WRITE, &err, usberr);
		if (usge_dp_wait_idle(dp) != USB_SUCCESS) {
			goto usberr;
		}
	}

usberr:
	return (err);
}

static uint32_t
usge_mcast_hash(struct usbgem_dev *dp, const uint8_t *addr)
{
	/* not yet */
	return ((usbgem_ether_crc_be(addr) >> 23) & 0x1ff);
}

static int
usge_set_rx_filter(struct usbgem_dev *dp)
{
	int		i;
	uint32_t	mode;
	uint32_t	mhash[DPSEL_VHF_HASH_LEN];
	uint_t		h;
	int		err = USB_SUCCESS;
	uint8_t		*m;
	uint32_t	high;
	uint32_t	low;
	uint32_t	val;
	uint64_t	tmp64;
	struct usge_dev	*lp = dp->private;

	DPRINTF(2, (CE_CONT, "!%s: %s: called, rxmode:%x",
	    dp->name, __func__, dp->rxmode));
	mode = RXFCTL_AB	/* accept broadcast packets */
	    | RXFCTL_DPF;	/* accept physical address packets */

	bzero(mhash, sizeof (mhash));

	if (dp->rxmode & RXMODE_PROMISC) {
		/* promiscious mode implies all multicast and all unicast */
		mode |= RXFCTL_AM | RXFCTL_AU;
	} else if ((dp->rxmode & RXMODE_ALLMULTI)
	    || dp->mc_count > DPSEL_VHF_HASH_LEN*32/2) {
		/* accept all multicast packets */
		mode |= RXFCTL_AM;
#ifdef CONFIG_PERFECT_FILTER
	} else if (dp->mc_count <= PMAF_ENTRY_NUM - 1) {
		/* do noting */
#endif
	} else if (dp->mc_count > 0) {
		/*
		 * make hash table to select interresting
		 * multicast address only.
		 */
		mode |= RXFCTL_MHF | RXFCTL_DPF;
		for (i = 0; i < dp->mc_count; i++) {
			/* hash table is 512 bit width */
			h = dp->mc_list[i].hash;
			mhash[h / 32] |= 1U << (h % 32);
		}
	}

	/*
	 * Set mac unicast address.
	 * Use the last entry in perfect match address filter table.
	 */
	m = dp->cur_addr.ether_addr_octet;
	high = PMAF_VALID | LE_IN16(m + 4);
	low = LE_IN32(m);

	i = PMAF_ENTRY_NUM - 1;
	tmp64 = (((uint64_t)high) << 32) | (uint64_t)low;
	if (lp->pmatch[i] != tmp64) {
		OUTL(dp, PMAF_BASE + i * 8 + 4, low, &err, usberr);
		OUTL(dp, PMAF_BASE + i * 8, high, &err, usberr);

		lp->pmatch[i] = tmp64;
	}

	lp->rxctl &=
	    ~(RXFCTL_AB | RXFCTL_AU | RXFCTL_AM | RXFCTL_DPF | RXFCTL_MHF);
	lp->rxctl |= mode;

#ifdef CONFIG_PERFECT_FILTER
	if (dp->mc_count <= PMAF_ENTRY_NUM - 1) {
		for (i = 0; i < PMAF_ENTRY_NUM - 1; i++) {
			high = 0;
			low = 0;
			if (i < dp->mc_count) {
				m = &dp->mc_list[i].addr.ether_addr_octet[0];
				high = LE_IN16(m + 4) | PMAF_VALID;
				low = LE_IN32(m);
			}

			tmp64 = (((uint64_t)high) << 32) | (uint64_t)low;
			if (lp->pmatch[i] == tmp64) {
				continue;
			}

			OUTL(dp, PMAF_BASE + i * 8 + 4, low, &err, usberr);
			OUTL(dp, PMAF_BASE + i * 8, high, &err, usberr);
			lp->pmatch[i] = tmp64;
		}
	} else
#endif
	/* set up multicast hash table */
	if (mode & RXFCTL_MHF) {
		if (usge_dp_wait_idle(dp) != USB_SUCCESS) {
			err = USB_FAILURE;
			goto usberr;
		}

		INL(dp, DPSEL, &val, &err, usberr);
		val &= ~DPSEL_RSEL;
		val |= DPSEL_VHF;
		OUTL(dp, DPSEL, val, &err, usberr);

		for (i = 0; i < DPSEL_VHF_HASH_LEN; i++) {
			if (lp->mhash[i] == mhash[i]) {
				continue;
			}
			OUTL(dp, DPADDR, DPSEL_VHF_VLAN_LEN + i, &err, usberr);
			OUTL(dp, DPDATA, mhash[i], &err, usberr);
			OUTL(dp, DPCMD, DPCMD_WRITE, &err, usberr);
			if (usge_dp_wait_idle(dp) != USB_SUCCESS) {
				goto usberr;
			}
			lp->mhash[i] = mhash[i];
		}
	}

	/* update rx filter mode */
	OUTL(dp, RXFCTL, lp->rxctl, &err, usberr);

usberr:
	DPRINTF(2, (CE_CONT, "!%s: %s: end %d (%s)",
	    dp->name, __func__,
	    err, err == USB_SUCCESS ? "success" : "error"));
	return (err);
}

static int
usge_set_media(struct usbgem_dev *dp)
{
	uint32_t	val;
	uint32_t	fct;
	int	err = USB_SUCCESS;
	struct usge_dev	*lp = dp->private;

	/* setup flow control */
	val = 0;
	fct = 0;
	if (dp->full_duplex) {
		/* select flow control */
		switch (dp->flow_control) {
		case FLOW_CONTROL_TX_PAUSE:
		case FLOW_CONTROL_SYMMETRIC:
			val |= FLCTL_TXEN | 0xffffU;
			fct = 8 << FIFOTHSH_OFF_SHIFT
			    | 32 << FIFOTHSH_ON_SHIFT;
			break;
		}

		switch (dp->flow_control) {
		case FLOW_CONTROL_RX_PAUSE:
		case FLOW_CONTROL_SYMMETRIC:
			val |= FLCTL_RXEN;
			break;
		}
	}
	OUTL(dp, FLCTL, val, &err, usberr);
	OUTL(dp, FIFOTHSH, fct, &err, usberr);

usberr:
	DPRINTF(2, (CE_CONT, "!%s: %s: end %d (%s)",
	    dp->name, __func__,
	    err, err == USB_SUCCESS ? "success" : "error"));
	return (err);
}

#define	TX_PKT_HEADER_SIZE	8

/*
 * send/receive packet check
 */
static mblk_t *
usge_tx_make_packet(struct usbgem_dev *dp, mblk_t *mp)
{
	uint_t		n;
	uint_t		pkt_size;
	uint_t		len;
	mblk_t		*new;
	mblk_t		*tp;
	uint8_t		*bp;

	len = msgdsize(mp);
	pkt_size = max(len, ETHERMIN);

	/*
	 * re-allocate the mp
	 */
	new = allocb(TX_PKT_HEADER_SIZE + pkt_size, 0);
	if (new == NULL) {
		/* mo memory */
		goto x;
	}

	/* make a header */
	bp = new->b_rptr;
	LE_OUT32(bp, pkt_size | TXHDR0_FCS);
	LE_OUT32(bp + 4, 0);

	bp += TX_PKT_HEADER_SIZE;

	/* copy contents of the buffer */
	for (tp = mp; tp; tp = tp->b_cont) {
		n = tp->b_wptr - tp->b_rptr;
		bcopy(tp->b_rptr, bp, n);
		bp += n;
	}

	/* zero padds */
	n = pkt_size - len;
	if (n) {
		bzero(bp, n);
		bp += n;
	}

	/* close the payload of the packet */
	new->b_wptr = bp;
x:
	return (new);
}

static void
usge_dump_packet(struct usbgem_dev *dp, uint8_t *bp, int n)
{
	int	i;

	for (i = 0; i < n; i += 8, bp += 8) {
		cmn_err(CE_CONT, "%02x %02x %02x %02x %02x %02x %02x %02x",
		    bp[0], bp[1], bp[2], bp[3], bp[4], bp[5], bp[6], bp[7]);
	}
}

#ifdef notdef
 Recieve packet format

	packet0
		header
			4byte - err flags, length of payload 
			4byte - cksum
		payload
			2byte - pad
			rcved ethernet packet
	padding	to next 4 byte boundary
	packet1

#endif

#define	RX_PKT_HEADER_SIZE	8
#define	RX_PKT_PADDING	2

static mblk_t *
usge_rx_make_packet(struct usbgem_dev *dp, mblk_t *mp)
{
	mblk_t	*tp;
	mblk_t	**mpp;
	uint8_t	*bp;
	uint8_t	*bp_start;
	uint8_t	*bp_end;
	int	len;
	int	rest;

	bp_start = mp->b_rptr;
	bp_end = mp->b_wptr;
	bp = bp_start;
	rest = bp_end - bp_start;

	tp = mp;
	tp->b_wptr = tp->b_rptr;
	mpp = &tp->b_next;

	DPRINTF(20, (CE_CONT, "!%s: %s: size:%d", dp->name, __func__, len));
#if DEBUG_LEVEL > 20
	usge_dump_packet(dp, mp->b_rptr, 16);
#endif

	while (rest > RX_PKT_HEADER_SIZE + RX_PKT_PADDING) {
		uint32_t	rxhdr0;
		uint32_t	rxhdr1;

		/* analyse the header of the received usb frame */
		rxhdr0 = LE_IN32(bp);
		rxhdr1 = LE_IN32(bp + 4);
		len = rxhdr0 & RXHDR0_LEN; /* includes pad and fcs, but header */

		if (len < RX_PKT_PADDING + ETHERMIN + ETHERFCSL) {
			cmn_err(CE_NOTE,
			    "!%s: %s: too short pktsize:%d, off:%d, total:%d",
			    dp->name, __func__, len, bp - bp_start, bp_end - bp_start);
			dp->stats.errrcv++;
			dp->stats.runt++;
			break;
		}
		else if (len > RX_PKT_PADDING + sizeof (struct ether_header)
		    + sizeof (struct ether_vlan_header)
		    + dp->mtu + ETHERFCSL) {
			cmn_err(CE_NOTE,
			    "!%s: %s: too long pktsize:%d, off:%d, total:%d",
			    dp->name, __func__, len, bp - bp_start, bp_end - bp_start);
			dp->stats.errrcv++;
			dp->stats.frame_too_long++;
			break;
		}
#if DEBUG_LEVEL > 20
		cmn_err(CE_CONT, "!%s: %s: header: %08x %08x",
		    dp->name, __func__, rxhdr0, rxhdr1);
#endif

		if (rxhdr0 & RXHDR0_RED) {
			DPRINTF(0, (CE_CONT,
			    "!%s: %s: rx error hdr:0x%08x, off:%d, total:%d",
			    dp->name, __func__, rxhdr0, bp - bp_start, bp_end - bp_start));
			dp->stats.errrcv++;

			if (rxhdr0 & RXHDR0_FCS) {
				dp->stats.crc++;
			} else if (rxhdr0 & RXHDR0_RUNT) {
				dp->stats.runt++;
			} else if (rxhdr0 & RXHDR0_LONG) {
				dp->stats.frame_too_long++;
			}
		} else {

			/* allocate mblk */
			if (tp == NULL) {
				tp = dupb(mp);
				if (tp == NULL) {
					/* no memory or share count exceeds 255 */
					goto x;
				}
				*mpp = tp;
				mpp = &tp->b_next;
			}

			/* extract a ethernet packet from the bulk-in frame */
			tp->b_rptr = bp + RX_PKT_HEADER_SIZE + RX_PKT_PADDING;
			tp->b_wptr = tp->b_rptr + (len - RX_PKT_PADDING - ETHERFCSL);

			tp = NULL;
		}

		/* consume the packet */
		len = P2ROUNDUP(RX_PKT_HEADER_SIZE + len, 4);
		rest -= len;

		/* the next packet buffer starts at the next 4 byte boundary */
		bp += len;

#if DEBUG_LEVEL > 20
		usge_dump_packet(dp, tp->b_wptr, 18);
#endif
	}
x:
	*mpp = NULL;

	return (mp->b_rptr != mp->b_wptr ? mp : NULL);
}

/*
 * MII Interfaces
 */
static uint16_t
usge_mii_read(struct usbgem_dev *dp, uint_t index, int *errp)
{
	struct usge_dev	*lp = dp->private;
	uint32_t	reg;
	uint32_t	data;
	int		i;

	INL(dp, MII_ACCESS, &reg, errp, usberr);

	if (reg & MII_ACCESS_BUSY) {
		/* hang ? */
		cmn_err(CE_CONT, "!%s:%s MII is busy",
		    dp->name, __func__);
		data = 0;
		goto usberr;
	}

	/* set the address, index & direction (read from PHY) */
	reg = ((dp->mii_phy_addr << MII_ACCESS_PHY_ADDR_SHIFT))
	    | ((index << MII_ACCESS_REG_ADDR_SHIFT))
	    | MII_ACCESS_BUSY;

	OUTL(dp, MII_ACCESS, reg, errp, usberr);

	i = 0;
	do {
		if (i++ > 100) {
			/* timeout */
			INL(dp, MII_DATA, &data, errp, usberr);
			cmn_err(CE_CONT,
			    "!%s:%s timeout, mii_accss:%x, data:%x",
			    dp->name, __func__, reg, data);
			data = 0;
			goto usberr;
		}
		INL(dp, MII_ACCESS, &reg, errp, usberr);
	} while (reg & MII_ACCESS_BUSY);

	INL(dp, MII_DATA, &data, errp, usberr);

	DPRINTF(10, (CE_CONT, "!%s: %s called phy:%d index:%d data:0x%x",
	    dp->name, __func__, dp->mii_phy_addr, index, data));

usberr:
	return ((uint16_t)data);
}

static void
usge_mii_write(struct usbgem_dev *dp, uint_t index, uint16_t val, int *errp)
{
	uint32_t	reg;
	int		i;

	*errp = USB_SUCCESS;

	ASSERT(index >= 0 && index < 32);
	DPRINTF(10, (CE_CONT, "!%s: %s called", dp->name, __func__));

	INL(dp, MII_ACCESS, &reg, errp, usberr);
	if (reg & MII_ACCESS_BUSY) {
		/* hang ? */
		cmn_err(CE_CONT, "!%s:%s MII is busy",
		    dp->name, __func__);
		reg = 0;
		goto usberr;
	}

	OUTL(dp, MII_DATA, val, errp, usberr);

	/* set the address, index & direction (read from PHY) */
	reg = (dp->mii_phy_addr << MII_ACCESS_PHY_ADDR_SHIFT)
	    | (index << MII_ACCESS_REG_ADDR_SHIFT)
	    | MII_ACCESS_WRITE
	    | MII_ACCESS_BUSY;
	OUTL(dp, MII_ACCESS, reg, errp, usberr);

	i = 0;
	do {
		if (i++ > 100) {
			/* timeout */
			cmn_err(CE_CONT, "!%s:%s timeout",
			    dp->name, __func__);
			goto usberr;
		}
		INL(dp, MII_ACCESS, &reg, errp, usberr);
	} while (reg & MII_ACCESS_BUSY);

usberr:
	return;
}

static int
usge_mii_probe(struct usbgem_dev *dp)
{
	int	ret;

	ret = usbgem_mii_probe_default(dp);

	/* we cannot change speed/duplex/an manuall */
	dp->mii_status_ro = 0xffffU;
	dp->mii_xstatus_ro = 0xffffU;

	return (ret);
}

/* ======================================================== */
/*
 * OS depend (device driver DKI) routine
 */
/* ======================================================== */
static int
usge_wait_eeprom(struct usbgem_dev *dp, uint32_t which, int max)
{
	int	i;
	int	err;
	uint32_t	val;

	err = USB_SUCCESS;
	i = 0;
	for (;;) {
		INL(dp, EEPROM, &val, &err, usberr);
		if ((val & which) == 0) {
			break;
		}
		if (i++ > max) {
			cmn_err(CE_CONT, "!%s: %s: timeout",
			    dp->name, __func__);
			goto usberr;
		}
		drv_usecwait(40);
	}
usberr:
	return (err);
}

static int
usge_read_eeprom(struct usbgem_dev *dp,
    uint_t start, int len, uint8_t *data)
{
	int	err;
        uint32_t	val;

	err = USB_SUCCESS;

	if (usge_wait_eeprom(dp, EEPCMD_BUSY, 100) != USB_SUCCESS) {
		cmn_err(CE_CONT, "!%s: %s: timeout, not ready",
		    dp->name, __func__);
		goto usberr;
	}

	while (len-- > 0) {
		OUTL(dp, EEPROM,
		    EEPCMD_BUSY | EEPCMD_READ | start++, &err, usberr);

		if (usge_wait_eeprom(dp, EEPCMD_BUSY | EEPCMD_TIMEOUT, 100)
		    != USB_SUCCESS) {
			cmn_err(CE_CONT, "!%s: %s: timeout, io\n",
			    dp->name, __func__);
			goto usberr;
		}

		INL(dp, EEPDATA, &val, &err, usberr);

		*data++ = val;
	}

usberr:
	return (err);
}

#ifdef DEBUG_LEVEL
static void
usge_eeprom_dump(struct usbgem_dev *dp, int size)
{
	int	i;
	int	err;
	uint8_t	w0[8];

	cmn_err(CE_CONT, "!%s: eeprom dump:", dp->name);

	err = USB_SUCCESS;

	for (i = 0; i < size; i += 8) {
		usge_read_eeprom(dp, i, 8, &w0[0]);
		cmn_err(CE_CONT, "!0x%02x: 0x%04x 0x%04x 0x%04x 0x%04x",
		    i,
		    w0[1] << 8 | w0[0],
		    w0[3] << 8 | w0[2],
		    w0[4] << 8 | w0[4],
		    w0[7] << 8 | w0[6]);
	}

usberr:
	;
}
#endif

static int
usge_attach_chip(struct usbgem_dev *dp)
{
	int		err;
	int		ret;
#ifdef DEBUG_LEVEL
	uint8_t		val8;
#endif
	struct usge_dev	*lp = dp->private;

	DPRINTF(0, (CE_CONT, "!%s: %s enter", dp->name, __func__));

	/*
	 * mac address in EEPROM has loaded to ID registers.
	 */
	err = usge_read_eeprom(dp,
	    EEPROM_MAC_OFFSET, ETHERADDRL, dp->dev_addr.ether_addr_octet);
	if (err != USB_SUCCESS) {
		goto usberr;
	}

	/* fix rx buffer size */
	if (dp->ep_bulkin->wMaxPacketSize == 512) {
		/* usb 2.x mode */
		dp->rx_buf_len = 16 * 1024 + 5 * 512;
	} else {
		/* usb 1.x mode */
		dp->rx_buf_len = 6 * 1024 + 33 * 64;
	}

	dp->mii_phy_addr = 1;

#if defined(DEBUG_LEVEL) && DEBUG_LEVEL > -2
	usge_eeprom_dump(dp, 0x80);
#endif

	return (USB_SUCCESS);

usberr:
	cmn_err(CE_WARN, "%s: %s: usb error detected", dp->name, __func__);
	return (USB_FAILURE);
}

static int
usgeattach(dev_info_t *dip, ddi_attach_cmd_t cmd)
{
	int			i;
	ddi_iblock_cookie_t	c;
	int			ret;
	int			revid;
	int			unit;
	int			vid;
	int			pid;
	int			len;
	const char		*drv_name;
	struct usbgem_dev	*dp;
	void			*base;
	struct usbgem_conf	*ugcp;
	struct usge_dev		*lp;

	unit = ddi_get_instance(dip);
	drv_name = ddi_driver_name(dip);

	DPRINTF(3, (CE_CONT, "!%s%d: %s: called, cmd:%d",
	    drv_name, unit, __func__, cmd));

	if (cmd == DDI_ATTACH) {
		/*
		 * Check if the chip is supported.
		 */
		vid = ddi_prop_get_int(DDI_DEV_T_ANY, dip, DDI_PROP_DONTPASS,
		    "usb-vendor-id", -1);
		pid = ddi_prop_get_int(DDI_DEV_T_ANY, dip, DDI_PROP_DONTPASS,
		    "usb-product-id", -1);
		revid = ddi_prop_get_int(DDI_DEV_T_ANY, dip, DDI_PROP_DONTPASS,
		    "usb-revision-id", -1);
		/*
		 * construct usbgem configration
		 */
		ugcp = kmem_zalloc(sizeof (*ugcp), KM_SLEEP);

		/* name */
		sprintf(ugcp->usbgc_name, "%s%d", drv_name, unit);

		ugcp->usbgc_ifnum = 0;
		ugcp->usbgc_alt = 0;

		ugcp->usbgc_tx_list_max = 256;

		ugcp->usbgc_rx_header_len = 0;
		ugcp->usbgc_rx_list_max = 64;

		/* time out parameters */
		ugcp->usbgc_tx_timeout = USBGEM_TX_TIMEOUT;
		ugcp->usbgc_tx_timeout_interval = USBGEM_TX_TIMEOUT_INTERVAL;

		/* flow control */
		ugcp->usbgc_flow_control = FLOW_CONTROL_SYMMETRIC;

		/* MII timeout parameters */
		ugcp->usbgc_mii_link_watch_interval = ONESEC;
		ugcp->usbgc_mii_an_watch_interval = ONESEC/5;
		ugcp->usbgc_mii_reset_timeout = MII_RESET_TIMEOUT; /* 1 sec */
		ugcp->usbgc_mii_an_timeout = MII_AN_TIMEOUT;	/* 5 sec */
		ugcp->usbgc_mii_an_wait = 0;
		ugcp->usbgc_mii_linkdown_timeout = MII_LINKDOWN_TIMEOUT;

		ugcp->usbgc_mii_an_delay = 0;
		ugcp->usbgc_mii_linkdown_action = MII_ACTION_RSA;
		ugcp->usbgc_mii_linkdown_timeout_action = MII_ACTION_RESET;
		ugcp->usbgc_mii_dont_reset = B_FALSE;

		/* I/O methods */

		/* mac operation */
		ugcp->usbgc_attach_chip = &usge_attach_chip;
		ugcp->usbgc_reset_chip = &usge_reset_chip;
		ugcp->usbgc_init_chip = &usge_init_chip;
		ugcp->usbgc_start_chip = &usge_start_chip;
		ugcp->usbgc_stop_chip = &usge_stop_chip;
		ugcp->usbgc_multicast_hash = &usge_mcast_hash;

		ugcp->usbgc_set_rx_filter = &usge_set_rx_filter;
		ugcp->usbgc_set_media = &usge_set_media;
		ugcp->usbgc_get_stats = &usge_get_stats;
		ugcp->usbgc_interrupt = NULL;

		/* packet operation */
		ugcp->usbgc_tx_make_packet = &usge_tx_make_packet;
		ugcp->usbgc_rx_make_packet = &usge_rx_make_packet;

		/* mii operations */
		ugcp->usbgc_mii_probe = &usge_mii_probe;
		ugcp->usbgc_mii_init = &usbgem_mii_init_default;
		ugcp->usbgc_mii_config = &usbgem_mii_config_default;
		ugcp->usbgc_mii_read = &usge_mii_read;
		ugcp->usbgc_mii_write = &usge_mii_write;

		lp = kmem_zalloc(sizeof (struct usge_dev), KM_SLEEP);

		ddi_set_driver_private(dip, NULL);

		dp = usbgem_do_attach(dip, ugcp, lp, sizeof (struct usge_dev));

		kmem_free(ugcp, sizeof (*ugcp));

		if (dp != NULL) {
			return (DDI_SUCCESS);
		}

err_free_mem:
		kmem_free(lp, sizeof (struct usge_dev));
err_close_pipe:
err:
		return (DDI_FAILURE);
	}
	return (DDI_FAILURE);
}

static int
usgedetach(dev_info_t *dip, ddi_detach_cmd_t cmd)
{
	int	ret;

	if (cmd == DDI_DETACH) {
		ret = usbgem_do_detach(dip);
		if (ret != DDI_SUCCESS) {
			DDI_FAILURE;
		}
		return (DDI_SUCCESS);
	}
	return (DDI_FAILURE);
}

/* ======================================================== */
/*
 * OS depend (loadable streams driver) routine
 */
/* ======================================================== */
#ifdef USBGEM_CONFIG_GLDv3
USBGEM_STREAM_OPS(usge_ops, usgeattach, usgedetach);
#else
static	struct module_info usgeminfo = {
	0,			/* mi_idnum */
	"usge",			/* mi_idname */
	0,			/* mi_minpsz */
	ETHERMTU,		/* mi_maxpsz */
	ETHERMTU*128,		/* mi_hiwat */
	1,			/* mi_lowat */
};

static	struct qinit usgerinit = {
	(int (*)()) NULL,	/* qi_putp */
	usbgem_rsrv,		/* qi_srvp */
	usbgem_open,		/* qi_qopen */
	usbgem_close,		/* qi_qclose */
	(int (*)()) NULL,	/* qi_qadmin */
	&usgeminfo,		/* qi_minfo */
	NULL			/* qi_mstat */
};

static	struct qinit usgewinit = {
	usbgem_wput,		/* qi_putp */
	usbgem_wsrv,		/* qi_srvp */
	(int (*)()) NULL,	/* qi_qopen */
	(int (*)()) NULL,	/* qi_qclose */
	(int (*)()) NULL,	/* qi_qadmin */
	&usgeminfo,		/* qi_minfo */
	NULL			/* qi_mstat */
};

static struct streamtab	usge_info = {
	&usgerinit,	/* st_rdinit */
	&usgewinit,	/* st_wrinit */
	NULL,		/* st_muxrinit */
	NULL		/* st_muxwrinit */
};

static	struct cb_ops cb_usge_ops = {
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
	&usge_info,	/* cb_stream */
	D_NEW|D_MP	/* cb_flag */
};

static	struct dev_ops usge_ops = {
	DEVO_REV,	/* devo_rev */
	0,		/* devo_refcnt */
	usbgem_getinfo,	/* devo_getinfo */
	nulldev,	/* devo_identify */
	nulldev,	/* devo_probe */
	usgeattach,	/* devo_attach */
	usgedetach,	/* devo_detach */
	nodev,		/* devo_reset */
	&cb_usge_ops,	/* devo_cb_ops */
	NULL,		/* devo_bus_ops */
	usbgem_power,	/* devo_power */
#if DEVO_REV >= 4
	usbgem_quiesce,	/* devo_quiesce */
#endif
};
#endif

static struct modldrv modldrv = {
	&mod_driverops,	/* Type of module.  This one is a driver */
	ident,
	&usge_ops,	/* driver ops */
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

	DPRINTF(2, (CE_CONT, "!usge: _init: called"));

	status = usbgem_mod_init(&usge_ops, "usge");
	if (status != DDI_SUCCESS) {
		return (status);
	}
	status = mod_install(&modlinkage);
	if (status != DDI_SUCCESS) {
		usbgem_mod_fini(&usge_ops);
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

	DPRINTF(2, (CE_CONT, "!usge: _fini: called"));
	status = mod_remove(&modlinkage);
	if (status == DDI_SUCCESS) {
		usbgem_mod_fini(&usge_ops);
	}
	return (status);
}

int
_info(struct modinfo *modinfop)
{
	return (mod_info(&modlinkage, modinfop));
}
