/*
 *  gem.c: general ethernet mac driver framework
 *
 * Copyright (c) 2002-2004 Masayuki Murayama.  All rights reserved.
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

#pragma ident	"%W% %E%"

/*
 Change log
 04/08/2003  gem_get_packet_default fixed for sparc
 05/18/2003  no interrupt option implemented
 10/06/2003  link watcher rewriten
 04/01/2004  license changed
 04/11/2004  threshold of tx desc changed; 2*desc => 3*desc
 */

/*
 TODO:
	separete allocation descriptors and bufferes
	txbuf allocation in attach
	fix rx_desc_write/tx_desc_write interface
	programable mtu, txmaxdma, rxmaxdma, txthr, rxthr
 */

/*
 * System Header files.
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
#include <sys/ddi_impldefs.h>

#include "mii.h"
#include "gem.h"

#ifdef MODULE
char	ident[] = "general ethernet mac driver v" VERSION;
char	_depends_on[] = {"misc/gld"};
#endif

/* Debugging support */
#ifdef GEM_DEBUG_LEVEL
static int gem_debug = GEM_DEBUG_LEVEL;
#define	DPRINTF(n, args)	if (gem_debug>(n)) cmn_err args
#else
#define	DPRINTF(n, args)
#undef ASSERT
#define ASSERT(x)
#endif

#if defined(sun4u)
# define IOMMU
# define IOCACHE
#endif

/*
 * Useful macros and typedefs
 */
#define	FALSE	(0)
#define	TRUE	(!FALSE)
#define	ROUNDUP(x, a)	(((x) + (a) - 1) & ~((a) - 1))

/*
 * configuration parameters
 */
#define	MAXPKTLEN(dp)	((dp)->mtu + 14)
#define	MAXPKTBUF(dp)	((dp)->mtu + 14 + ETHERFCSL)

#define	WATCH_INTERVAL_FAST	drv_usectohz(100*1000)

/*
 * Macros to distinct chip generation.
 */

/*
 * Private functions
 */
static void gem_mii_start(struct gem_dev *);
static void gem_mii_stop(struct gem_dev *);

/* local buffer management */
static struct rxbuf *gem_get_rxbuf(struct gem_dev *, int);
static void gem_free_rxbuf(struct rxbuf *);
static void gem_reclaim_rxbuf(struct rxbuf *);
static int gem_alloc_memory(struct gem_dev *);
static void gem_free_memory(struct gem_dev *);
static void gem_init_rx_desc(struct gem_dev *);
static void gem_init_rx_buffer(struct gem_dev *);
static void gem_init_tx_desc(struct gem_dev *);
static void gem_clean_rx_desc(struct gem_dev *);
static void gem_clean_tx_desc(struct gem_dev *);
static void gem_append_rxbuf(struct gem_dev *, struct rxbuf *, int);

static int gem_reclaim_txbuf(struct gem_dev *dp);

static void gem_tx_timeout(struct gem_dev *);

/* GLD interfaces */
static int gem_reset(gld_mac_info_t *);
static int gem_start(gld_mac_info_t *);
static int gem_stop(gld_mac_info_t *);
static int gem_set_mac_address(gld_mac_info_t *, uint8_t *);
static int gem_set_multicast(gld_mac_info_t *, uint8_t *, int);
static int gem_set_promiscuous(gld_mac_info_t *, int);
static int gem_get_stats(gld_mac_info_t *, struct gld_stats *);
static int gem_send(gld_mac_info_t *, mblk_t *);
static u_int gem_interrupt(gld_mac_info_t *);
static	struct ether_addr	etherbroadcastaddr = {
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff
};

static int gem_speed_value[] = {10, 100, 1000};

#ifdef MODULE
extern struct mod_ops mod_miscops;

static struct modlmisc modlmisc = {
	&mod_miscops,
	"gem v" VERSION,
};

static struct modlinkage modlinkage = {
	MODREV_1, &modlmisc, NULL
};

/*
 * _init : done
 */
int
_init(void)
{
	int 	status;

	DPRINTF(2, (CE_CONT, "gem: _init: called"));
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

	DPRINTF(2, (CE_CONT, "gem: _fini: called"));
	status = mod_remove(&modlinkage);
	return (status);
}

int
_info(struct modinfo *modinfop)
{
	return (mod_info(&modlinkage, modinfop));
}
#endif /* MODULE */

/* ============================================================== */
/*
 * gcc3 runtime routines
 */
/* ============================================================== */
int
gem_memcmp(void *s1, void *s2, int n)
{
	int	i;
	int	ret;

	ret = 0;
	for (i = 0; i < n; i++) {
		ret = (int)((uint8_t *)s1)[i] - (int)((uint8_t *)s2)[i];
		if (ret != 0) {
			return ret;
		}
	}
	return 0;
}

void *
gem_memset(void *s, int c, size_t n)
{
	if ((c & 0xff) == 0) {
		bzero(s, n);
	}
	else {
		while (n--) {
			((uint8_t *)s)[n] = c;
		}
	}
	return s;
}

void *
gem_memcpy(void *s1, void *s2, size_t n)
{
	bcopy(s2, s1, n);
	return s1;
}

/* ============================================================== */
/*
 * Ether CRC calculation utilities
 */
/* ============================================================== */
/*
 * Ether CRC calculation according to 21143 data sheet
 */
#define	CRC32_POLY_LE	0xedb88320
uint32_t
gem_ether_crc_le(uint8_t *addr)
{
	int		idx;
	int		bit;
	u_int		data;
	uint32_t	crc = 0xffffffff;

	crc = 0xffffffff;
	for (idx = 0; idx < ETHERADDRL; idx++) {
		for (data = *addr++, bit = 0; bit < 8; bit++, data >>= 1) {
			crc = (crc >> 1)
			    ^ (((crc ^ data) & 1) ? CRC32_POLY_LE : 0);
		}
	}
	return	crc;
}

#define	CRC32_POLY_BE	0x04c11db7
uint32_t
gem_ether_crc_be(uint8_t *addr)
{
	int		idx;
	int		bit;
	u_int		data;
	uint32_t	crc;

	crc = 0xffffffff;
	for (idx = 0; idx < ETHERADDRL; idx++) {
                for (data = *addr++, bit = 0; bit < 8; bit++, data >>= 1) {
			crc = (crc << 1)
			    ^ ((((crc >> 31) ^ data) & 1) ? CRC32_POLY_BE : 0);
		}
	}
	return crc;
}

/* ============================================================== */
/*
 * Buffer management
 */
/* ============================================================== */

/* gem_get_rxbuf: supply mapped receive buffer */

static struct rxbuf *
gem_get_rxbuf(struct gem_dev *dp, int cansleep)
{
	struct rxbuf		*rbp;
	ddi_dma_cookie_t	cookie;
	uint_t			count = 0;
	int			err;
	const int		rx_max_frags = dp->gc.gc_rx_max_frags;

	ASSERT(mutex_owned(&dp->intrlock));
	DPRINTF(3, (CE_CONT, "gem_get_rxbuf: called freecnt:%d",
		dp->rx_buf_freecnt));
	/*
	 * Get rx buffer management structure
	 */
	if ((rbp = dp->rx_buf_freelist) != NULL) {
		/* get from recycle list */
		ASSERT(dp->rx_buf_freecnt > 0);

		dp->rx_buf_freelist = rbp->rxb_next;
		dp->rx_buf_freecnt--;

		ASSERT(rbp->rxb_mp == NULL);

		switch (rx_max_frags) {
		default:
			/* type 1 */
			ASSERT(rx_max_frags > 1);
			if (rbp->rxb_mp == NULL) {
				goto type1_allocb;
			}
			return rbp;

		case 1:
			/* type 2 */
			if (rbp->rxb_mp == NULL) {
				goto type2_esballoc;
			}
			return rbp;

		case 0:
			/* type 3 */
			return rbp;
		}
	}
	else {
		if (dp->rx_buf_allocated >= dp->gc.gc_rx_buf_max) {
			/* exceed limit */
			return NULL;
		}

		/*
		 * Allocate rx buffer management structure
		 */
		if ((rbp = (struct rxbuf *) kmem_zalloc(sizeof(struct rxbuf),
				cansleep ? KM_SLEEP : KM_NOSLEEP)) == NULL) {
			/* no memory */
			return NULL;
		}
#ifdef SANITY
		rbp->rxb_buf    = NULL;
		rbp->rxb_mp     = NULL;
		rbp->rxb_ah     = NULL;
#endif
		dp->rx_buf_allocated++;
		rbp->rxb_devp = dp;

		if (rx_max_frags == 0) {
			/* No need to allocate a dma buffer in memory */
			rbp->rxb_nfrags = 0;
			return rbp;
		}

		/* allocate dma handle */
		if (ddi_dma_alloc_handle(dp->dip, &dp->gc.gc_dma_attr_rxbuf, 
				cansleep ? DDI_DMA_SLEEP : DDI_DMA_DONTWAIT,
				NULL, &rbp->rxb_dh) != DDI_SUCCESS) {

			cmn_err(CE_CONT,
				"%s: gem_get_rxbuf: ddi_dma_mem_alloc: failed",
				dp->name);

			dp->rx_buf_allocated--;
			kmem_free(rbp, sizeof(struct rxbuf));
			return NULL;
		}

	}

	/* Allocate memory */
	if (rx_max_frags > 1) {
		int	align;
type1_allocb:
		/* type 1 buffer use normal allocb'd area */
		if (dp->gc.gc_rx_buf_align > 7) {
			align = dp->gc.gc_rx_buf_align + 1;
		} else {
			align = 1;
		}
		if ((rbp->rxb_mp = allocb(dp->rx_buf_len + align - 1, BPRI_MED))
								== NULL) {
			kmem_free(rbp, sizeof(struct rxbuf));
			return NULL;
		}
		rbp->rxb_buf = (caddr_t)
			ROUNDUP((long)rbp->rxb_mp->b_rptr, align);
		rbp->rxb_mp->b_rptr =
			(uchar_t *)rbp->rxb_buf + dp->gc.gc_rx_header_len;
		rbp->rxb_buf_len = dp->rx_buf_len;
	}
	else {
		ASSERT(rx_max_frags == 1);

		/*
		 * type 2 buffer have strong restriction on memeory allocation
		 */
		if (ddi_dma_mem_alloc(rbp->rxb_dh,
			dp->rx_buf_len, &dp->gc.gc_buf_attr,
			0, cansleep ? DDI_DMA_SLEEP : DDI_DMA_DONTWAIT,
			NULL,
			&rbp->rxb_buf, &rbp->rxb_buf_len,
			&rbp->rxb_ah) != DDI_SUCCESS) {

			cmn_err(CE_CONT,
				"%s: gem_get_rxbuf: ddi_dma_mem_alloc: failed",
				dp->name);

			ddi_dma_free_handle(&rbp->rxb_dh);
			kmem_free(rbp, sizeof(struct rxbuf));
			return NULL;
		}
		rbp->rxb_frtn.free_func=(void (*)())&gem_reclaim_rxbuf;
		rbp->rxb_frtn.free_arg =(caddr_t) rbp;
	}

	/* Mapin data buffer */
	if ((err = ddi_dma_addr_bind_handle(rbp->rxb_dh,
				NULL, rbp->rxb_buf, rbp->rxb_buf_len,
				dp->gc.gc_rx_header_len > 0
					? DDI_DMA_RDWR : DDI_DMA_READ,
				cansleep ? DDI_DMA_SLEEP : DDI_DMA_DONTWAIT,
				NULL,
				rbp->rxb_dmacookie, &count)) != DDI_SUCCESS) {

		ASSERT(err != DDI_DMA_INUSE);
		cmn_err(CE_CONT,
			"%s: gem_get_rxbuf: ddi_dma_addr_bind_handle: failed",
			dp->name);

		if(rbp->rxb_ah != NULL) {
			ASSERT(rx_max_frags == 1);
			ddi_dma_mem_free(&rbp->rxb_ah);
		}
		ddi_dma_free_handle(&rbp->rxb_dh);
		kmem_free(rbp, sizeof(struct rxbuf));
		return NULL;
	}
#ifdef IOMMU
	ASSERT(count == 1);
#else	
	ASSERT(count <= rx_max_frags && count <= 2);
	if (count == 2) {
		ddi_dma_nextcookie(rbp->rxb_dh, &rbp->rxb_dmacookie[1]);
	}
#endif
	rbp->rxb_nfrags = count;

	if (rx_max_frags == 1) {
		/* for type2 only */
type2_esballoc:
		ASSERT(rbp->rxb_mp == NULL);
		if ((rbp->rxb_mp = esballoc((uchar_t *)rbp->rxb_buf, rbp->rxb_buf_len,
					BPRI_MED, &rbp->rxb_frtn)) == NULL) {
			/* recycle rxbuf */
			rbp->rxb_next = dp->rx_buf_freelist;
			dp->rx_buf_freelist = rbp;
			dp->rx_buf_freecnt++;

			cmn_err(CE_CONT,
				"%s: gem_get_rxbuf: esballoc: failed",
				dp->name);

			return NULL;
		}
		/* bcm440x support: fix start addres of data area */
		rbp->rxb_mp->b_rptr =
			(uchar_t *) rbp->rxb_buf + dp->gc.gc_rx_header_len;
	}
	return rbp;
}

static void
gem_free_rxbuf(struct rxbuf *rbp)
{
	struct gem_dev	*dp;

	dp = rbp->rxb_devp;

	ASSERT(mutex_owned(&dp->intrlock));
	ASSERT(rbp->rxb_mp == NULL);
	rbp->rxb_next = dp->rx_buf_freelist;
	dp->rx_buf_freelist = rbp;
	dp->rx_buf_freecnt++;
}

static void
gem_reclaim_rxbuf(struct rxbuf *rbp)
{
	struct gem_dev	*dp;

	dp = rbp->rxb_devp;

	ASSERT(rbp->rxb_mp == NULL);

	mutex_enter(&dp->intrlock);
	gem_free_rxbuf(rbp);
	mutex_exit(&dp->intrlock);
}

/* ============================================================== */
/*
 * memory resource management
 */
/* ============================================================== */
static int
gem_alloc_memory(struct gem_dev* dp)
{
	caddr_t			ring;
	caddr_t			buf;
	size_t			ring_len;
	size_t			buf_len;
	ddi_dma_cookie_t	ring_cookie;
	ddi_dma_cookie_t	buf_cookie;
	uint_t			count;
	int			i;
	int			j;
	int			err;
	struct rxbuf		*rbp, *head;
	struct txbuf		*tbp;
	size_t			offset;
	const int		tx_ring_size = dp->gc.gc_tx_ring_size;
	const int		tx_buf_size  = dp->gc.gc_tx_buf_size;
	const int		rx_ring_size = dp->gc.gc_rx_ring_size;
	int			tx_buf_len;

	/*
	 * Alloc RX/TX descriptors
	 */
	if (dp->gc.gc_rx_desc_size + dp->gc.gc_tx_desc_size > 0) {
		if ((err = ddi_dma_alloc_handle(dp->dip,
				&dp->gc.gc_dma_attr_desc,
				DDI_DMA_SLEEP,NULL,
				&dp->desc_dma_handle)) != DDI_SUCCESS) {
			cmn_err(CE_WARN,
			"%s: gem_alloc_memory: ddi_dma_alloc_handle failed: %d",
				dp->name, err);
			return ENOMEM;
		}

		if ((err = ddi_dma_mem_alloc(dp->desc_dma_handle,
				dp->gc.gc_rx_desc_size + dp->gc.gc_tx_desc_size,
				&dp->gc.gc_desc_attr,
				DDI_DMA_CONSISTENT, DDI_DMA_SLEEP, NULL,
				&ring, &ring_len,
				&dp->desc_acc_handle)) != DDI_SUCCESS) {
			cmn_err(CE_WARN,
			"%s: gem_alloc_memory: ddi_dma_mem_alloc failed: %d",
				dp->name, err);
			ddi_dma_free_handle(&dp->desc_dma_handle);
			return ENOMEM;
		}

		if ((err = ddi_dma_addr_bind_handle(dp->desc_dma_handle,
					NULL, ring, ring_len,
					DDI_DMA_RDWR | DDI_DMA_CONSISTENT,
					DDI_DMA_SLEEP, NULL,
					&ring_cookie, &count)) != DDI_SUCCESS) {
			ASSERT(err != DDI_DMA_INUSE);
			cmn_err(CE_WARN,
		"%s: gem_alloc_memory: ddi_dma_addr_bind_handle failed: %d",
				dp->name, err);
			ddi_dma_mem_free(&dp->desc_acc_handle);
			ddi_dma_free_handle(&dp->desc_dma_handle);
			return ENOMEM;
		}
		ASSERT(count == 1);
	}

	/*
	 * Allocate TX bounce buffers
	 */
	if ((err = ddi_dma_alloc_handle(dp->dip, &dp->gc.gc_dma_attr_desc,
			DDI_DMA_SLEEP,NULL,
			&dp->buf_dma_handle)) != DDI_SUCCESS) {
		cmn_err(CE_WARN,
			"%s: gem_alloc_memory: ddi_dma_alloc_handle failed: %d",
			dp->name, err);
		goto err;
	}

	if (dp->gc.gc_tx_max_frags > 1) {
		/* type 1 */
		tx_buf_len = min(MAXPKTBUF(dp), dp->gc.gc_tx_copy_thresh);
	} else {
		/* type 2, 3*/
		tx_buf_len = MAXPKTBUF(dp);
	}
	tx_buf_len = ROUNDUP(tx_buf_len, 8);
	tx_buf_len = ROUNDUP(tx_buf_len, (dp->gc.gc_tx_buf_align + 1));
	if ((err = ddi_dma_mem_alloc(dp->buf_dma_handle,
				ETHERMIN + tx_buf_len * tx_buf_size,
				&dp->gc.gc_buf_attr,
				0, DDI_DMA_SLEEP, NULL,
				&buf, &buf_len,
				&dp->buf_acc_handle)) != DDI_SUCCESS) {
		cmn_err(CE_WARN,
			"%s: gem_alloc_memory: ddi_dma_mem_alloc failed: %d",
			dp->name, err);
		ddi_dma_free_handle(&dp->buf_dma_handle);
		goto err;
	}

	if ((err = ddi_dma_addr_bind_handle(dp->buf_dma_handle,
				NULL, buf, buf_len,
				DDI_DMA_RDWR,
				DDI_DMA_SLEEP, NULL,
				&buf_cookie, &count)) != DDI_SUCCESS) {
		ASSERT(err != DDI_DMA_INUSE);
		cmn_err(CE_WARN,
		"%s: gem_alloc_memory: ddi_dma_addr_bind_handle failed: %d",
			dp->name, err);
		ddi_dma_mem_free(&dp->buf_acc_handle);
		ddi_dma_free_handle(&dp->buf_dma_handle);
		goto err;
	}
	ASSERT(count == 1);

	/* base of rx descriptor ring */
	if (dp->gc.gc_rx_desc_size > 0) {;
		dp->rx_ring = ring;
		dp->rx_ring_dma = ring_cookie.dmac_laddress;
	}
	/* base of tx descriptor ring */
	if (dp->gc.gc_tx_desc_size > 0) {;
		dp->tx_ring = ring + dp->gc.gc_rx_desc_size;
		dp->tx_ring_dma = ring_cookie.dmac_laddress
				+ dp->gc.gc_rx_desc_size;
	}

	/* base of tx bounce buffer */
	if (tx_buf_size > 0) {
		dp->tx_bounce_buf = buf;
		dp->tx_bounce_buf_dma = buf_cookie.dmac_laddress;
	}
	/* base of zero buffer for software tx padding */
	dp->tx_pad_dma = buf_cookie.dmac_laddress + tx_buf_len * tx_buf_size;
#ifdef notyet
	/* allocate rx ring buffer */
#endif
	if (dp->gc.gc_tx_max_frags > 0) {
		/*
		 * Allocate dma handles for each Tx buffer
		 */
		DPRINTF(4, (CE_CONT, "%s: tx_bounce_buf:0x%x, tx_buf_len: 0x%x",
			dp->name, dp->tx_bounce_buf, tx_buf_len));
		for (i = tx_buf_size, tbp = dp->tx_buf, offset = 0;
					i--; tbp++, offset += tx_buf_len) {
			for (j = 0; j < GEM_MAXTXSEGS; j++) {

				if (ddi_dma_alloc_handle(dp->dip,
#if 1
	/*
	 * We use attr_desc instead of attr_txbuf because currently
	 * tx bounce buffer must be physically continueous.
	 */
					&dp->gc.gc_dma_attr_desc,
#else
					&dp->gc.gc_dma_attr_txbuf,
#endif
					DDI_DMA_SLEEP, NULL,
					&tbp->txb_dh[j]) != DDI_SUCCESS) {

					cmn_err(CE_WARN,
			"%s: gem_alloc_memory: ddi_dma_alloc_handle failed.",
						dp->name);
					goto err_alloc_dh;
				}
			}
			/* setup bounce buffer */
			tbp->txb_buf = dp->tx_bounce_buf + offset;
			tbp->txb_buf_dma = dp->tx_bounce_buf_dma + offset;
		}
	}
#ifdef notdef
	/* Preallocate rx buffer for performance */
	mutex_enter(&dp->intrlock);
	head = NULL;
	for (i = 0; i < rx_ring_size*2; i++) {
		rbp = gem_get_rxbuf(dp, TRUE);
		rbp->rxb_next = head;
		head = rbp;
	}
	while ((rbp = head) != NULL) {
		head = head->rxb_next;
		gem_free_rxbuf(rbp);
	}
	mutex_exit(&dp->intrlock);
#endif
	return 0;

err_alloc_dh:
	if (dp->gc.gc_tx_max_descs_per_pkt > 0) {
		while (j-- > 0) {
			ddi_dma_free_handle(&dp->tx_buf[i].txb_dh[j]);
		}
		while (i-- > 0) {
			j = GEM_MAXTXSEGS;
			while (j-- > 0) {
				ddi_dma_free_handle(&dp->tx_buf[i].txb_dh[j]);
			}
		}
	}
err:
	if (dp->desc_dma_handle) {
		err = ddi_dma_unbind_handle(dp->desc_dma_handle);
		ASSERT(err == DDI_SUCCESS);
		ddi_dma_mem_free(&dp->desc_acc_handle);
		ddi_dma_free_handle(&dp->desc_dma_handle);
	}

	return ENOMEM;
}

static void
gem_free_memory(struct gem_dev* dp)
{
	int		i;
	int		j;
	int		err;
	struct rxbuf	*rbp;
	struct txbuf	*tbp;

	/* Free TX/RX descriptors */
	if (dp->desc_dma_handle) {
		err = ddi_dma_unbind_handle(dp->desc_dma_handle);
		ASSERT(err == DDI_SUCCESS);

		ddi_dma_mem_free(&dp->desc_acc_handle);
		ddi_dma_free_handle(&dp->desc_dma_handle);
	}

	/* Free TX bounce buffers */
	if (dp->buf_dma_handle) {
		err = ddi_dma_unbind_handle(dp->buf_dma_handle);
		ASSERT(err == DDI_SUCCESS);

		ddi_dma_mem_free(&dp->buf_acc_handle);
		ddi_dma_free_handle(&dp->buf_dma_handle);
	}

	/* Free dma handles for Tx */
	if (dp->gc.gc_tx_max_frags > 0) {
		for (i = dp->gc.gc_tx_buf_size, tbp = dp->tx_buf; i--; tbp++) {
			for (j = 0; j < GEM_MAXTXSEGS; j++) {
				ddi_dma_free_handle(&tbp->txb_dh[j]);
			}
		}
	}

	/* Free rx buffer */
	while (rbp = dp->rx_buf_freelist) {
		dp->rx_buf_freelist = rbp->rxb_next;

		if (dp->gc.gc_rx_max_frags > 0) {
			/* release DMA mapping */
			ASSERT(rbp->rxb_dh != NULL);

			if (rbp->rxb_nfrags > 0) {
				err = ddi_dma_unbind_handle(rbp->rxb_dh);
				ASSERT(err == DDI_SUCCESS);
			}

			ASSERT(rbp->rxb_mp == NULL);

			if (rbp->rxb_ah != NULL) {
				/* type 2 */
				ASSERT(dp->gc.gc_rx_max_frags == 1);
				ASSERT(rbp->rxb_ah);
				ddi_dma_mem_free(&rbp->rxb_ah);
			}

			ddi_dma_free_handle(&rbp->rxb_dh);
		}
		kmem_free(rbp, sizeof(struct rxbuf));
	}
}

/* ============================================================== */
/*
 * Rx/Tx descriptor management
 */
/* ============================================================== */
static void
gem_init_rx_desc(struct gem_dev *dp)
{
	int		i;
	const int	rx_ring_size = dp->gc.gc_rx_ring_size;
	const int	rx_buf_size  = dp->gc.gc_rx_buf_size;
	struct rxbuf	*rbp;

	DPRINTF(1, (CE_CONT, "gem_init_rx_desc: ring_size:%d, buf_size:%d",
		rx_ring_size, rx_buf_size));

	ASSERT(dp->rx_ring != NULL);

	dp->rx_desc_head = 0;
	dp->rx_desc_tail = 0;

	/* make physical chain of rx descriptors */
	for (i = 0; i < rx_ring_size; i++) {
		GEM_RX_DESC_INIT(dp, i);
	}

	dp->rx_buf_head = NULL;
	dp->rx_buf_tail = NULL;
}

static void
gem_init_rx_buf(struct gem_dev *dp)
{
	int		i;
	const int	rx_buf_size  = dp->gc.gc_rx_buf_size;
	struct rxbuf	*rbp;

	for (i = 0; i < rx_buf_size; i++) {
		if ((rbp = gem_get_rxbuf(dp, TRUE)) == NULL) {
			break;
		}
		gem_append_rxbuf(dp, rbp, TRUE);
	}

}

static void
gem_clean_rx_ring(struct gem_dev* dp)
{
	struct rxbuf	*rbp;
	mblk_t		*mp;
#ifdef GEM_DEBUG_LEVEL
	int		i;
#endif
	ASSERT(mutex_owned(&dp->intrlock));
	ASSERT(!dp->nic_active);

	DPRINTF(2, (CE_CONT, "%s: gem_clean_rx_ring: %d buffers are free",
		dp->name, dp->rx_buf_freecnt));
#ifdef GEM_DEBUG_LEVEL
	i = 0;
#endif
	while ((rbp = dp->rx_buf_head) != NULL) {
#ifdef GEM_DEBUG_LEVEL
		i++;
#endif
		if ((dp->rx_buf_head = rbp->rxb_next) == NULL) {
			dp->rx_buf_tail = NULL;
		}

		switch (dp->gc.gc_rx_max_frags) {
		default:
			/* type 1 */
			/* release DMA resource */
			ASSERT (rbp->rxb_nfrags > 0);
			ddi_dma_unbind_handle(rbp->rxb_dh);
			rbp->rxb_nfrags = 0;

			ASSERT(rbp->rxb_mp != NULL);
			mp = rbp->rxb_mp;
			rbp->rxb_mp = NULL;
			freemsg(mp);

			gem_free_rxbuf(rbp);
			break;

		case 1:
			/* type 2 */
			/* dont release DMA mappping */
			ASSERT(rbp->rxb_nfrags == 1);

			/* release mblk */
			ASSERT(rbp->rxb_mp != NULL);
			mp = rbp->rxb_mp;
			rbp->rxb_mp = NULL;
			freemsg(mp);
			break;

		case 0:
			/* type 3 */
			ASSERT(rbp->rxb_mp == NULL);
			ASSERT (rbp->rxb_nfrags == 0);
			gem_free_rxbuf(rbp);
			break;
		}

	}
	dp->rx_buf_tail = NULL;

	DPRINTF(2, (CE_CONT,
		"%s: gem_clean_rx_ring: %d buffers freeed, total: %d free",
		dp->name, i, dp->rx_buf_freecnt));
}

static void
gem_init_tx_desc(struct gem_dev* dp)
{
	int		i;
	struct txbuf	*tbp;
	struct txbuf	*head;
	const int	tx_ring_size = dp->gc.gc_tx_ring_size;
	const int	tx_buf_size  = dp->gc.gc_tx_buf_size;

	DPRINTF(1, (CE_CONT, "gem_init_tx_desc: ring_size:%d, buf_size:%d",
		tx_ring_size, tx_buf_size));

#ifdef notdef
	ASSERT(mutex_owned(&dp->xmitlock));
#endif
	dp->tx_desc_head = 0;
	dp->tx_desc_tail = 0;
	dp->tx_desc_intr = -1;

	for (i = 0; i < tx_ring_size; i++) {
		GEM_TX_DESC_INIT(dp, i);
	}

	dp->tx_buf_head = NULL;
	dp->tx_buf_tail = NULL;
	dp->tx_softq_head = NULL;

	/* make txbuf free list */
	head = NULL;
	for (i = 0, tbp = dp->tx_buf; i < tx_buf_size; i++, tbp++) {
		tbp->txb_next = head;
		head = tbp;
		tbp->txb_nfrags = 0; /* no dma mapping flag */
#ifdef SANITY
		tbp->txb_ndesc  = 0;
		tbp->txb_mp      = NULL;
		tbp->txb_dh_used = NULL;
#endif
	}
	dp->tx_buf_freelist = head;
	dp->tx_buf_freecnt  = tx_buf_size;
}

static void
gem_clean_tx_ring(struct gem_dev *dp)
{
	int		i;
	struct txbuf	*tbp;

	ASSERT(mutex_owned(&dp->xmitlock));

	while (tbp = dp->tx_buf_head) {

		/* dequeue one from tx list */
		if ((dp->tx_buf_head = tbp->txb_next) == NULL) {
			dp->tx_buf_tail = NULL;
		}
		
		if (tbp->txb_mp != NULL) {

			ASSERT(tbp->txb_dh_used > 0);

			i = tbp->txb_dh_used;
			while (i--) {
				/* release dma resource */
				ddi_dma_unbind_handle(tbp->txb_dh[i]);
			}

			/* free direct tx buffer */
			freemsg(tbp->txb_mp);
			tbp->txb_mp = NULL;
		}

		/* free descriptor */
		dp->tx_desc_head += tbp->txb_ndesc;
#ifdef SANITY
		tbp->txb_ndesc = 0;
#endif
		dp->stats.errxmt++;

		/* recycle txbuf */
		tbp->txb_next = dp->tx_buf_freelist;
		dp->tx_buf_freelist = tbp;
		dp->tx_buf_freecnt++;
	}

	ASSERT(dp->tx_desc_head == dp->tx_desc_tail);
}

static void
gem_restart_nic(struct gem_dev *dp, boolean_t keep_tx_buf)
{
	int		i;
	struct rxbuf	*rbp;
	struct txbuf	*tbp;

	ASSERT(mutex_owned(&dp->xmitlock));

	DPRINTF(1, (CE_CONT, "%s: gem_restart_nic: called: tx_desc:%d %d %d",
		dp->name,
		dp->tx_desc_head, dp->tx_desc_tail, dp->tx_desc_intr));

	dp->nic_active = FALSE;
	while (dp->tx_busy > 0) {
		cv_wait(&dp->drain_cv, &dp->xmitlock);
	}

	/* Reset the chip. */
	GEM_RESET_CHIP(dp);

	/* unload rx buffers */
	for (i = 0; i < dp->gc.gc_rx_ring_size; i++) {
		GEM_RX_DESC_CLEAN(dp, i);
	}

	/* reset rx descriptor position */
	dp->rx_desc_head = 0;
	dp->rx_desc_tail = 0;

	if (keep_tx_buf) {
		/* keep untransmited buffers */
		dp->tx_softq_head = dp->tx_buf_head;

		/* clean tx descriptors */
		for (i = 0; i < dp->gc.gc_tx_ring_size; i++) {
			GEM_TX_DESC_CLEAN(dp, i);
		}

		/* reset tx descriptor position  */
		dp->tx_desc_head = 0;
		dp->tx_desc_tail = 0;
		dp->tx_desc_intr = -1;
	}
	else {
		/* discard all untranmitted tx buffers */
		gem_clean_tx_ring(dp);

		/* reset tx descriptor ring */
		gem_init_tx_desc(dp);
	}

	/* Reinitialize the hardware. */
	GEM_INIT_CHIP(dp);

	/* reload rx buffers */
	for (rbp = dp->rx_buf_head; rbp != NULL; rbp = rbp->rxb_next) {
		rbp->rxb_slot = dp->rx_desc_tail;
		dp->rx_desc_tail += rbp->rxb_ndesc =
		GEM_RX_DESC_WRITE(dp, rbp->rxb_slot, rbp->rxb_dmacookie,
				rbp->rxb_nfrags);
	}

	/* Set mac address and rx mode */
	GEM_SET_RX_FILTER(dp);

	/* Restart the nic */
	dp->nic_active = TRUE;
	GEM_START_CHIP(dp);
}

void
gem_restart_tx(struct gem_dev *dp)
{
	gem_restart_nic(dp, TRUE);
}

/* ============================================================== */
/*
 * GLD interface
 */
/* ============================================================== */

static int
gem_reset(gld_mac_info_t *macinfo)
{
	struct gem_dev *dp;

	dp = (struct gem_dev *)macinfo->gldm_private;

	DPRINTF(1, (CE_CONT, "%s: gem_reset: called", dp->name));

	mutex_enter(&dp->intrlock);
	mutex_enter(&dp->xmitlock);

	gem_init_rx_desc(dp);
	gem_init_tx_desc(dp);

	dp->nic_active  = FALSE;
	dp->tx_blocked  = FALSE;
	dp->tx_busy     = 0;
	dp->mc_count    = 0;

	GEM_INIT_CHIP(dp);

	gem_init_rx_buf(dp);

	mutex_exit(&dp->xmitlock);
	mutex_exit(&dp->intrlock);

	return GLD_SUCCESS;
}

static int
gem_start(gld_mac_info_t *macinfo)
{
	struct gem_dev *dp;

	dp = (struct gem_dev *)macinfo->gldm_private;

	DPRINTF(1, (CE_CONT, "%s: gem_start: called", dp->name));

	mutex_enter(&dp->intrlock);
	mutex_enter(&dp->xmitlock);

	/* init driver state */
	dp->nic_active   = TRUE;
#ifdef notdef
	dp->tx_blocked   = FALSE;
	dp->tx_busy      = FALSE;
#endif
	GEM_START_CHIP(dp);

	mutex_exit(&dp->xmitlock);
	mutex_exit(&dp->intrlock);

	dp->timeout_id = timeout((void (*)(void *))gem_tx_timeout,
				(void *)dp, dp->gc.gc_tx_timeout_interval);

	return GLD_SUCCESS;
}

static int
gem_stop(gld_mac_info_t *macinfo)
{
	timeout_id_t	old_id;
	struct gem_dev	*dp;
	int		i;
	boolean_t	tx_sched;

	dp = (struct gem_dev *)macinfo->gldm_private;

	DPRINTF(2, (CE_CONT, "%s: gem_stop: called, rx_buf_free:%d",
		dp->name, dp->rx_buf_freecnt));

	/* stop tx timeout watcher */
	if (dp->timeout_id) {
		do {
			untimeout(old_id = dp->timeout_id);
		} while (dp->timeout_id != old_id);	
		dp->timeout_id = 0;
	}

	/* make nic state inactive */
	mutex_enter(&dp->intrlock);
	mutex_enter(&dp->xmitlock);
	dp->nic_active = FALSE;
	mutex_exit(&dp->xmitlock);

#ifdef notdef
	mutex_exit(&dp->intrlock);
	/* This cause recursive mutex lock */
	/* drain blocked tx request */
	gld_sched(dp->macinfo);
	mutex_enter(&dp->intrlock);
#endif

	while (dp->intr_busy) {
		cv_wait(&dp->drain_cv, &dp->intrlock);
	}

	/* block tx */
	mutex_enter(&dp->xmitlock);
	while (dp->tx_busy > 0) {
		cv_wait(&dp->drain_cv, &dp->xmitlock);
	}

	GEM_STOP_CHIP(dp);

	(void) gem_reclaim_txbuf(dp);
	gem_clean_tx_ring(dp);
	gem_clean_rx_ring(dp);

	mutex_exit(&dp->xmitlock);
	mutex_exit(&dp->intrlock);

#ifdef notdef
	if (dp->rx_buf_allocated !=  dp->rx_buf_freecnt) {
		cmn_err(CE_CONT, "%s: gem_stop: rxbuf alloced:%d, free: %d\n",
			dp->name,
			dp->rx_buf_allocated, dp->rx_buf_freecnt);
	}
#endif

	return GLD_SUCCESS;
}

static int
gem_set_multicast(gld_mac_info_t *macinfo, uint8_t *ep, int flag)
{
	struct gem_dev	*dp;
	size_t			len;
	int			i;
	int			cnt;

	dp = (struct gem_dev *)macinfo->gldm_private;

	DPRINTF(1, (CE_CONT, "%s: gem_set_multicast: called", dp->name));

	cnt = dp->mc_count;

	if (flag == GLD_MULTI_ENABLE) {
		/* append the new addess at the end of the mclist */
		if (cnt >= GEM_MAXMC) {
			return GLD_FAILURE;
		}
		bcopy(ep, dp->mc_list[cnt].addr.ether_addr_octet, ETHERADDRL);
		if (dp->gc.gc_multicast_hash != NULL) {
			dp->mc_list[cnt].hash = GEM_MULTICAST_HASH(dp, ep);
		}
		dp->mc_count++;
	}
	else {
		for (i = 0; i < cnt; i++) {
			if (bcmp(ep, &dp->mc_list[i].addr, ETHERADDRL) == 0) {
				goto found;
			}
		}
		return GLD_FAILURE;
found:
		/* squeeze mclist by copying forward */
		len = (cnt - (i + 1)) * sizeof(*dp->mc_list);
		if (len > 0) {
			bcopy(&dp->mc_list[i+1], &dp->mc_list[i], len);
		}
		dp->mc_count--;
	}

	mutex_enter(&dp->intrlock);
	GEM_SET_RX_FILTER(dp);
	mutex_exit(&dp->intrlock);

	return GLD_SUCCESS;
}

static int
gem_set_promiscuous(gld_mac_info_t *macinfo, int flag)
{
	struct gem_dev *dp;

	dp = (struct gem_dev *)macinfo->gldm_private;

	DPRINTF(1, (CE_CONT, "%s: gem_set_promiscuos: called", dp->name));
#ifdef S10
	if (flag == GLD_MAC_PROMISC_NOOP) {
		/* mode unchanged */
		return GLD_SUCCESS;
	}
#endif
	if (flag == GLD_MAC_PROMISC_NONE) {
		dp->rxmode &= ~(RXMODE_PROMISC | RXMODE_ALLMULTI);
	}
	else if (flag == GLD_MAC_PROMISC_MULTI) {
		dp->rxmode |= RXMODE_ALLMULTI;
	}
	else {
		ASSERT(flag == GLD_MAC_PROMISC_PHYS);
		dp->rxmode |= RXMODE_PROMISC;
	}

	mutex_enter(&dp->intrlock);
	GEM_SET_RX_FILTER(dp);
	mutex_exit(&dp->intrlock);

	return GLD_SUCCESS;
}

static int
gem_set_mac_address(gld_mac_info_t *macinfo, uint8_t *mac) /* done */
{
	struct gem_dev	*dp;

	dp = (struct gem_dev *)macinfo->gldm_private;

	DPRINTF(1, (CE_CONT, "%s: gem_set_mac_address: called", dp->name));

	bcopy(mac, dp->cur_addr.ether_addr_octet, ETHERADDRL);
	mutex_enter(&dp->intrlock);
	GEM_SET_RX_FILTER(dp);
	mutex_exit(&dp->intrlock);

	return GLD_SUCCESS;
}

static	int
gem_get_stats(gld_mac_info_t *macinfo, struct gld_stats *gs)
{
	struct gem_dev		*dp;
	struct gem_stats	*vs;

	dp = (struct gem_dev *)macinfo->gldm_private;
#ifdef notdef
	mutex_enter(&dp->intrlock);
#endif
	GEM_GET_STATS_CHIP(dp);
#ifdef notdef
	mutex_exit(&dp->intrlock);
#endif
	vs = &dp->stats;

	gs->glds_errxmt    = vs->errxmt;
	gs->glds_errrcv    = vs->errrcv;
	gs->glds_collisions= vs->collisions;

	gs->glds_excoll    = vs->excoll;
	gs->glds_defer     = vs->defer;
	gs->glds_frame     = vs->frame;
	gs->glds_crc       = vs->crc;

	gs->glds_overflow  = vs->overflow; /* fifo err,underrun,rbufovf*/
	gs->glds_underflow = vs->underflow;
	gs->glds_short     = vs->runt;
	gs->glds_missed    = vs->missed; /* missed pkts while rbuf ovf */
	gs->glds_xmtlatecoll = vs->xmtlatecoll;
	gs->glds_nocarrier = vs->nocarrier;
	gs->glds_norcvbuf  = vs->norcvbuf;	/* OS resource exaust */
	gs->glds_intr      = vs->intr;

	/* all before here must be kept in place for v0 compatibility */
	gs->glds_speed     = gem_speed_value[dp->speed] * 1000000;
	gs->glds_media     = GLDM_PHYMII;
	gs->glds_duplex    = dp->full_duplex
				? GLD_DUPLEX_FULL : GLD_DUPLEX_HALF;

	/* gs->glds_media_specific */
	gs->glds_dot3_first_coll     = vs->first_coll;
	gs->glds_dot3_multi_coll     = vs->multi_coll;
	gs->glds_dot3_sqe_error	     = 0;
	gs->glds_dot3_mac_xmt_error  = 0;
	gs->glds_dot3_mac_rcv_error  = 0;
	gs->glds_dot3_frame_too_long = vs->frame_too_long;

	return GLD_SUCCESS;
}

/*==========================================================*/
/*
 * Start transmission.
 * Return zero on success,
 */
/*==========================================================*/

static int
gem_reclaim_txbuf(struct gem_dev *dp)
{
	struct txbuf		*tbp;
	int			i;
	uint_t			txstat;
	int			err;
#if GEM_DEBUG > 0
	clock_t			now = ddi_get_lbolt();
#endif
	err = 0;
	while ((tbp = dp->tx_buf_head) != NULL) {

		if (tbp == dp->tx_softq_head) {
			break;
		}

		txstat = GEM_TX_DESC_STAT(dp, tbp->txb_slot, tbp->txb_ndesc);

		if (txstat == 0) {
			/* not transmitted yet */
			break;
		}

		if ((txstat & GEM_TX_ERR) != 0) {
			err = 1;
		}
#if GEM_DEBUG > 0
		if (now - tbp->txb_stime >= 50) {
			cmn_err(CE_WARN, "%s: tx delay while %d mS",
			dp->name, (now - tbp->stime)*10);
		}
#endif
		ASSERT((txstat & ~(GEM_TX_DONE | GEM_TX_ERR)) == 0);

		/* Dequeue this tx buffer from tx list */
		if ((dp->tx_buf_head = tbp->txb_next) == NULL) {
			dp->tx_buf_tail = NULL;
		}
		dp->tx_desc_head += tbp->txb_ndesc;

		/* Update interrupted position */
		if (dp->tx_desc_intr - (dp->tx_desc_head - 1) < 0) {
			dp->tx_desc_intr = dp->tx_desc_head - 1;
		}
#ifdef SANITY
		tbp->txb_ndesc = 0;
#endif
		/* Free dma mapping resources of each fragment */
		if (tbp->txb_mp) {
			i = tbp->txb_dh_used;
			while (i--) {
				ddi_dma_unbind_handle(tbp->txb_dh[i]);
			}
			tbp->txb_nfrags  = 0;
#ifdef SANITY
			tbp->txb_dh_used = 0;
#endif
			/* Free the original mblk. */
			freemsg(tbp->txb_mp);
#ifdef SANITY
			tbp->txb_mp = NULL;
#endif
		}

		/* Recycle txbuf */
		tbp->txb_next = dp->tx_buf_freelist;
		dp->tx_buf_freelist = tbp;
		dp->tx_buf_freecnt++;
	}

	return err;
}

static void
gem_tx_start_unit(struct gem_dev *dp)
{
	struct txbuf	*tbp;
	uint32_t	intreq;
	seqnum_t	curr;
	int		dfree;
	const int	tx_ring_size = dp->gc.gc_tx_ring_size;
	const int	descs = dp->gc.gc_tx_max_descs_per_pkt;

	for (tbp = dp->tx_softq_head; tbp != NULL;
			dp->tx_softq_head = tbp = tbp->txb_next) {

		dfree = tx_ring_size - SUB(dp->tx_desc_tail, dp->tx_desc_head);
		if (dfree < descs) {
			break;
		}

		/* allocate hw descriptor and link it to software structure */
		tbp->txb_slot = SLOT(dp->tx_desc_tail, tx_ring_size);
		curr = dp->tx_desc_tail;

		/*
		 * Guarantee to have a chance to be interrupted before
		 * tx thread will be blocked.
		 */
		intreq = 0;
		if (dp->tx_desc_tail - (dp->tx_desc_intr + 1)
						> tx_ring_size - 3*descs){
			/*
			 * Schedule a tx-done interrupt before free tx
			 * descriptors will run out.
			 */
			intreq = 1;
		} else if (dp->tx_desc_intr - dp->tx_desc_head < 0 &&
			   dp->tx_buf_freecnt < 2) {
			/*
			 * No tx interrupt is scheduled and the
			 * number of free tx buffers is less than 2.
			 * Schedule a tx-done interrupt before free tx buffers
			 * will run out.
			 */
			intreq = 1;
		}
#if GEM_DEBUG_LEVEL > 1
		if (dp->tx_cnt < 100) {
			dp->tx_cnt++;
			intreq = 1;
		}
#endif
		/*
		 * Write tx descriptor(s)
		 */
		dp->tx_desc_tail += tbp->txb_ndesc =
			GEM_TX_DESC_WRITE(dp, tbp->txb_slot, tbp->txb_dmacookie,
				tbp->txb_nfrags, intreq | (tbp->txb_flag << 8));
		tbp->txb_stime = dp->tx_start_time = ddi_get_lbolt();

		/* update interrupted position */
		if (intreq) {
			dp->tx_desc_intr = dp->tx_desc_tail - 1;
#if GEM_DEBUG_LEVEL > 0
			ASSERT(dp->tx_desc_intr >= dp->tx_desc_head);
#endif
		}
	}
#if GEM_DEBUG_LEVEL > 3
	if (dp->tx_softq_head != NULL) {
		int		i;
		struct txbuf *tbp;

		cmn_err(CE_CONT, "%s: gem_tx_start_unit", dp->name);
		i = 0;

		for (tbp = dp->tx_buf_head; tbp; tbp = tbp->txb_next) {
			cmn_err(CE_CONT, "%d: tbp:%p slot:%d ndesc:%d %s",
				i, tbp, tbp->txb_slot, tbp->txb_ndesc,
				(tbp==dp->tx_softq_head ? "(softq_head)": ""));
			i++;
		}
	}
#endif
#if GEM_DEBUG_LEVEL > 0
	ASSERT((dp->tx_softq_head == NULL) ||
	((dp->tx_desc_intr - dp->tx_desc_head) >= 0 && (dp->tx_desc_intr - dp->tx_desc_tail) < 0));
#endif
#if GEM_DEBUG_LEVEL > 3
	if (dp->tx_softq_head != NULL) {
		cmn_err(CE_CONT, "%s: gem_tx_start_unit: hw descriptor full",
			dp->name);
	}
#endif
}

#ifdef TXTIMEOUT_TEST
static int gem_send_cnt = 0;
#endif

/*
 * gem_send_common is external function because we use it directly
 * send control frame like setup frame of 2114x chip.
 */
int
gem_send_common(gld_mac_info_t *macinfo, mblk_t *mp, boolean_t single,
		int local_flag)
{
	mblk_t			*tp;
	mblk_t			*mp_org;
	ddi_dma_cookie_t	*dcp;
	ddi_dma_cookie_t	*dma;
	int			i;
	int			dh_used;
	int			segs;
#ifndef IOMMU
	int			frags;
#endif
	long			align;
	size_t			len;
	int			docopy;
	int			err;
	boolean_t		shortpkt;
	boolean_t		shortfrag;
	struct txbuf		*tbp;
	struct gem_dev		*dp;
	boolean_t		have_blocked;

	dp = (struct gem_dev *)macinfo->gldm_private;
	mp_org = NULL;

	DPRINTF(2, (CE_CONT, "gem_send: called: free bufs"));

	/* check buffer length and alignment */
	align = 0;
	len   = 0;
	segs  = 0;
#ifndef IOMMU
	frags = 0;
#endif
	shortfrag = FALSE;
	for (tp = mp; tp != NULL; tp = tp->b_cont) {
		int	diff; 

		len  +=  (diff = tp->b_wptr - tp->b_rptr);
		if (diff < 8) {
			shortfrag = TRUE;
		}

		align |= (long)tp->b_rptr;
		if (tp->b_cont != NULL) {
			align |= (long)tp->b_wptr;
		}
		segs++;
#ifndef IOMMU
		frags += (((long)tp->b_wptr + PAGESIZE - 1) >> PAGESHIFT) -
				(((long)tp->b_rptr) >> PAGESHIFT);
#endif
	}
	if (len < ETHERMIN && !dp->gc.gc_tx_auto_pad) {
		segs++;
#ifndef IOMMU
		frags++;
#endif
	}

	if (len > MAXPKTLEN(dp)) {
		cmn_err(CE_CONT, "%s: gem_send: msg too big: %d",
			dp->name, len);
		/* Do not free mp here, GLD will free it */
		return GLD_NOTSUPPORTED;
	}

	docopy   = FALSE;
	shortpkt = (len <= dp->gc.gc_tx_copy_thresh);

	if (segs > GEM_MAXTXSEGS ||
	    (align & dp->gc.gc_tx_buf_align) != 0 ||
#ifndef IOMMU
	    frags > dp->gc.gc_tx_max_frags ||
#else
	    segs > dp->gc.gc_tx_max_frags ||
#endif
	    segs > GEM_MAXTXSEGS || shortpkt || single || shortfrag) {
		docopy = TRUE;
		segs   = 1;
#ifndef IOMMU
		frags  = 1;
#endif
	}

	/* reserve required resources */
	have_blocked = dp->tx_blocked;

	if (!dp->nic_active && local_flag == 0) {
		/* the device is not working */
#if 0
		dp->stats.errxmt++;
		dp->stats.nocarrier++;
#endif
#ifdef S10
		return GLD_NOLINK;
#else
		return GLD_FAILURE;
#endif
	}

	/* get txbuf */
	DPRINTF(2, (CE_CONT, "gem_send: free txbufs:%d", dp->tx_buf_freecnt));

	/*
	 * Improving CPU utilazation by avoiding occurences of tx interrupts,
	 * we try to reclaim transmitted buffers on each trasmit request.
	 */
	if (gem_reclaim_txbuf(dp) != 0) {
		boolean_t	unlock = FALSE;
		/*
		 * TX has been stuck by a fatal error, reset tx side
		 * of the chip. This is for VIA Rhine chips.
		 */
		if (mutex_owned(&dp->intrlock) == 0) {
			mutex_exit(&dp->xmitlock);
			mutex_enter(&dp->intrlock);
			mutex_enter(&dp->xmitlock);
			unlock = TRUE;
		}
		gem_restart_tx(dp);
		if (unlock) {
			mutex_exit(&dp->xmitlock);
			mutex_exit(&dp->intrlock);

			mutex_enter(&dp->xmitlock);
		}
		gem_tx_start_unit(dp);
		DPRINTF(2, (CE_CONT,
			"%s: gem_send: desc_head:%d desc_tail:%d",
			dp->name, dp->tx_desc_head, dp->tx_desc_tail));
	}

	if ((tbp = dp->tx_buf_freelist) == NULL) {
		dp->tx_blocked = TRUE;

		/* Tx interrupt should have been scheduled */
		ASSERT(dp->tx_busy > 0 ||
		       dp->tx_desc_intr - dp->tx_desc_head >= 0);

#if GEM_DEBUG_LEVEL > 4
		if (!((dp->tx_busy > 0) ||
		     (dp->tx_desc_intr - dp->tx_desc_head >= 0))) {
			cmn_err(CE_CONT,
		"%s: gem_send: hung: head:%d tail:%d intr:%d blocked:%d",
			dp->name, dp->tx_desc_head, dp->tx_desc_tail,
			dp->tx_desc_intr, have_blocked);
		}
#endif
		DPRINTF(4, (CE_CONT, "%s: tx blocked", dp->name));
		return GLD_NORESOURCES;
	}

	/* dequeue tbp from the free list */
	dp->tx_buf_freelist = tbp->txb_next;
	dp->tx_buf_freecnt--;

	dp->tx_blocked = FALSE;
	dp->tx_busy++;
copy:
	dcp = tbp->txb_dmacookie;
	dh_used = 0;
	if (shortpkt || (docopy && (dp->gc.gc_tx_max_frags <= 1)) || single) {
		caddr_t	bp;
		/*
		 * copy case except big type1
		 */
		if (!shortpkt) {
			/*
			 * prepare for copying a big packet
			 */
			mutex_exit(&dp->xmitlock);
		}

		bp = tbp->txb_buf;
		for (tp = mp; tp; tp = tp->b_cont) {
			size_t	nbyte;
			nbyte = tp->b_wptr - tp->b_rptr;
			bcopy(tp->b_rptr, bp, nbyte);
			bp += nbyte;
		}

		if (len < ETHERMIN && !dp->gc.gc_tx_auto_pad) {
			bzero(bp, ETHERMIN - len);
			len = ETHERMIN;
		}
# ifdef IOCACHE
		ddi_dma_sync(dp->buf_dma_handle,
				(off_t)(tbp->txb_buf - dp->tx_bounce_buf),
				len, DDI_DMA_SYNC_FORDEV);
# endif
		ASSERT((tbp->txb_buf_dma & dp->gc.gc_tx_buf_align) == 0);
		dcp->dmac_laddress = tbp->txb_buf_dma;
		dcp->dmac_size    = len;
		DPRINTF(2, (CE_CONT, "gem_send: copy: addr:0x%llx len:0x%x",
			dcp->dmac_laddress, dcp->dmac_size));
		dcp++;

		/* prepare to destroy mp */
		mp_org = mp;
		mp = NULL;

		if (!shortpkt) {
			mutex_enter(&dp->xmitlock);
		}
	}
	else {
		if (docopy) {
			/*
			 * big type1
			 */
			mutex_exit(&dp->xmitlock);
			mp_org = mp;
			mp = msgpullup(mp, -1);
			mutex_enter(&dp->xmitlock);

			if (mp == NULL) {
				mp = mp_org;
				mp_org = NULL;
				err = GLD_NORESOURCES;
				goto x;
			}
		}

		/*
		 * prepare dma environment for direct transmit
		 */
		for (tp = mp; tp; tp = tp->b_cont) {
			ddi_dma_handle_t	dma_handle;
			uint_t			count;
			size_t			len;

			len = tp->b_wptr - tp->b_rptr;
			dma_handle = tbp->txb_dh[dh_used++];

			if ((err = ddi_dma_addr_bind_handle(
				dma_handle, NULL,
				(caddr_t)tp->b_rptr, len,
				DDI_DMA_WRITE,
				DDI_DMA_DONTWAIT, NULL,
				dcp++, &count))!= DDI_DMA_MAPPED) {

				DPRINTF(0, (CE_CONT,
				"%s: gem_send_common: dma_bind error: %d",
					dp->name, err));

				/* failed to bind dma resource */
				dh_used--;
				while (dh_used--) {
					ddi_dma_unbind_handle(
						tbp->txb_dh[dh_used]);
				}

				/* force to copy */
				single = TRUE;
				goto copy;
			}
			ASSERT(count == 1 || count == 2);
			while (--count > 0) {
				ddi_dma_nextcookie(dma_handle, dcp++);
			}
		}

		DPRINTF(2, (CE_CONT,
			"%s: gem_send: mp:0x%p, tbp:0x%p, dma frags:%d",
			dp->name, mp, tbp, dcp-tbp->txb_dmacookie));
#ifndef IOMMU
		/* check if dma range is valid */
		for (i = 0, dma = tbp->txb_dmacookie;
				i < (dcp - tbp->txb_dmacookie); i++, dma++) {

			DPRINTF(2, (CE_CONT,
				" frag:%dth: dma_addr:0x%llx len:0x%x",
				i, dma->dmac_laddress, dma->dmac_size));

			if (!(dma->dmac_laddress >=
				dp->gc.gc_dma_attr_txbuf.dma_attr_addr_lo &&
			   (uint64_t)(dma->dmac_laddress+(dma->dmac_size-1)) <=
				dp->gc.gc_dma_attr_txbuf.dma_attr_addr_hi)) {

				/* release allocated dma resources */
				while (dh_used--) {
					ddi_dma_unbind_handle(
						tbp->txb_dh[dh_used]);
				}

				/* force to copy */
				single = TRUE;
				goto copy;
			}
		}
#endif
		if (len < ETHERMIN && !dp->gc.gc_tx_auto_pad) {
			/* add pad fragment */
			dcp->dmac_laddress = dp->tx_pad_dma;
			dcp->dmac_size    = len - ETHERMIN;
			dcp++;
		}
	}
	err = GLD_SUCCESS;
x:
	dp->tx_busy--;

	if (!dp->nic_active && local_flag == 0) {
		/* device status has changed while we were preparing tx buf */
		if (dp->tx_busy == 0) {
			/* someone may wait for us */
			cv_broadcast(&dp->drain_cv);
		}
#ifdef S10
		err = GLD_NOLINK;
#else
		err = GLD_FAILURE;
#endif
	}

	if (err != GLD_SUCCESS) {
		/* something wrong, no resources? */
		if (err == GLD_NORESOURCES) {
			DPRINTF(2, (CE_CONT,
	"%s: gem_send: no resource: desc_head:%d desc_tail:%d desc_intr:%d",
			dp->name,
			dp->tx_desc_head, dp->tx_desc_tail, dp->tx_desc_intr));

			dp->tx_blocked = TRUE;
		}
		if (mp_org) {
			/* destory copied mblk */
			freemsg(mp);
		}
		return err;
	}

	/* save misc info */
	tbp->txb_mp      = mp;
	tbp->txb_dh_used = dh_used;
	tbp->txb_nfrags  = dcp - tbp->txb_dmacookie;
	tbp->txb_ndesc   = 0;
	tbp->txb_flag    = local_flag;

	/* Append tbp at the tail of the active tx buffer list */
	tbp->txb_next = NULL;
	if (dp->tx_buf_head == NULL) {
		dp->tx_buf_head = tbp;
		dp->tx_buf_tail = tbp;
	} else {
		dp->tx_buf_tail->txb_next = tbp;
		dp->tx_buf_tail = tbp;
	}
	if (dp->tx_softq_head == NULL) {
		dp->tx_softq_head = tbp;
	}

	/*
	 * load tx buffer(s) into hardware descriptors.
	 */
	gem_tx_start_unit(dp);
	if (mp_org != NULL) {
		/* destroy original mblk when we use copied tx buffer */
		freemsg(mp_org);
	}
	ASSERT(err == GLD_SUCCESS);
	return GLD_SUCCESS;
}

/*
 * gem_send is used only to send data packet into ethernet line.
 */
static int
gem_send(gld_mac_info_t *macinfo, mblk_t *mp)
{
	struct gem_dev	*dp;
	int		ret;

	dp = (struct gem_dev *)macinfo->gldm_private;

	/*
	 * Some nics hate to send packets while link down
	 */
	mutex_enter(&dp->xmitlock);
	if (dp->mii_state != MII_STATE_LINKUP) {
#if 0
		dp->stats.errxmt++;
		dp->stats.nocarrier++;
#endif
		mutex_exit(&dp->xmitlock);
#ifdef S10
		return GLD_NOLINK;
#else
		return GLD_FAILURE;
#endif
	}

	ret = gem_send_common(macinfo, mp, FALSE, 0);
	mutex_exit(&dp->xmitlock);
	return ret;
}


static void
gem_tx_timeout(struct gem_dev *dp)
{
	clock_t		now;
	boolean_t	tx_sched;
	struct rxbuf	*rbp;
	struct txbuf	*tbp;

	now = ddi_get_lbolt();
	tx_sched = FALSE;

	mutex_enter(&dp->intrlock);
	mutex_enter(&dp->xmitlock); 

	if (!dp->nic_active || dp->mii_state != MII_STATE_LINKUP) {
		mutex_exit(&dp->xmitlock); 
		mutex_exit(&dp->intrlock);
		goto schedule_next;
	}

	/* reclaim last tx buffer */
	if (gem_reclaim_txbuf(dp) != 0) {
		/* tx error, reset tx side of the chip */
		gem_restart_tx(dp);
	}

	/* load new tx buffers into hardware descriptors */
	gem_tx_start_unit(dp);

	/* if the downstream is blocked, reschedule it */
	tx_sched = dp->tx_blocked;

	/* check if the transmitter is stuck */
	if (dp->tx_buf_head == NULL) {
		mutex_exit(&dp->xmitlock); 
		mutex_exit(&dp->intrlock);
		goto schedule_next;
	}
	if (now - dp->tx_buf_head->txb_stime < dp->gc.gc_tx_timeout) {
		mutex_exit(&dp->xmitlock); 
		mutex_exit(&dp->intrlock);
		goto schedule_next;
	}

	cmn_err(CE_WARN, "%s: tx timeout: tx_desc_head: %d %d, starttime:%d",
		dp->name, dp->tx_desc_head,dp->tx_desc_tail, dp->tx_start_time);
#if 1
	/*
	 * Discard untransmitted packet
	 */
	gem_restart_nic(dp, FALSE);
#else
	/*
	 * Keep untransmitted packet
	 */
	gem_restart_nic(dp, TRUE);
	gem_tx_start_unit(dp);
	DPRINTF(0, (CE_CONT,
	"!%s: tx_timeout: reload: desc_head:%d desc_tail:%d desc_intr:%d",
		dp->name,
		dp->tx_desc_head, dp->tx_desc_tail, dp->tx_desc_intr));
	tx_sched = TRUE;
#endif
#ifdef TXTIMEOUT_TEST
	gem_send_cnt = 0;
#endif
	mutex_exit(&dp->xmitlock); 
	mutex_exit(&dp->intrlock);


schedule_next:
	if (tx_sched) {
		gld_sched(dp->macinfo);
	}

	DPRINTF(4, (CE_CONT,
"%s: blocked:%d txbuf_cnt:%d desc_head:%d desc_tail:%d desc_intr:%d",
		dp->name, dp->tx_blocked, dp->tx_buf_freecnt,
		dp->tx_desc_head, dp->tx_desc_tail, dp->tx_desc_intr));

	dp->timeout_id =
		timeout((void (*)(void *))gem_tx_timeout,
			(void *)dp, dp->gc.gc_tx_timeout_interval);
}

/*==================================================================*/
/*
 * Interrupt handler
 */
/*==================================================================*/
static void
gem_append_rxbuf(struct gem_dev *dp, struct rxbuf *rbp, int cansleep)
{
	int		err;
	mblk_t		*mp;
	const int	rx_ring_size = dp->gc.gc_rx_ring_size;
	const int	rx_max_frags = dp->gc.gc_rx_max_frags;


	ASSERT(rbp != NULL);
	ASSERT(mutex_owned(&dp->intrlock));

	DPRINTF(3, (CE_CONT,
		"%s: gem_append_rxbuf: desc_head:%d, desc_tail:%d",
		dp->name, dp->rx_desc_head, dp->rx_desc_tail));

	if (rx_ring_size - SUB(dp->rx_desc_tail, dp->rx_desc_head)
			< dp->gc.gc_rx_max_descs_per_pkt) {

		/* number of free rx descriptors is too short */

		switch (rx_max_frags) {
		default:
			/* type 1 *\
			/* release DMA resource */
			ASSERT(rbp->rxb_nfrags > 0);
			ddi_dma_unbind_handle(rbp->rxb_dh);
			rbp->rxb_nfrags = 0;

			ASSERT(rbp->rxb_mp != NULL);
			mp = rbp->rxb_mp;
			rbp->rxb_mp = NULL;
			freemsg(mp);

			gem_free_rxbuf(rbp);
			break;

		case 1:
			/* type 2 */
			/* dont release DMA mappping */
			ASSERT(rbp->rxb_nfrags == 1);

			/* release mblk */
			ASSERT(rbp->rxb_mp != NULL);
			mp = rbp->rxb_mp;
			rbp->rxb_mp = NULL;
			freemsg(mp);
			break;

		case 0:
			/* type 3 */
			ASSERT(rbp->rxb_nfrags == 0);
			ASSERT(rbp->rxb_mp == NULL);
			gem_free_rxbuf(rbp);
			break;
		}
		return;
	}

	/*
	 * Add it into active rx buffer list
	 */	
	rbp->rxb_slot = SLOT(dp->rx_desc_tail, rx_ring_size);
	rbp->rxb_next = NULL;
	if (dp->rx_buf_head == NULL) {
		dp->rx_buf_head = rbp;
		dp->rx_buf_tail = rbp;
	}
	else {
		dp->rx_buf_tail->rxb_next = rbp;
		dp->rx_buf_tail = rbp;
	}

	dp->rx_desc_tail += rbp->rxb_ndesc =
		GEM_RX_DESC_WRITE(dp, rbp->rxb_slot, rbp->rxb_dmacookie,
				rbp->rxb_nfrags);

	return;
}

mblk_t *
gem_get_packet_default(struct gem_dev *dp, struct rxbuf *rbp, size_t len)
{
	mblk_t	*mp;

	if ((mp = allocb(len, BPRI_MED)) != NULL) {
#ifdef IOCACHE
		ddi_dma_sync(rbp->rxb_dh, 0, len, DDI_DMA_SYNC_FORKERNEL);
#endif
		bcopy(rbp->rxb_buf, mp->b_rptr, len);
		mp->b_wptr = mp->b_rptr + len;
	}
	return mp;
}

#ifdef GEM_DEBUG_LEVEL
uint_t	gem_rx_pkts[17];
#endif

void
gem_receive(struct gem_dev *dp)
{
	int		len;
	struct rxbuf	*rbp;
	struct rxbuf	*nrbp;
	int		limit;
	mblk_t		*mp;
	boolean_t	docopy;
	uint_t		rxstat;

	ASSERT(mutex_owned(&dp->intrlock));

	DPRINTF(2, (CE_CONT, "%s: gem_receive: rx_buf_head:%p",
			dp->name, dp->rx_buf_head));

	limit = max(dp->gc.gc_rx_buf_size, 10);
	while ((rbp = dp->rx_buf_head) != NULL && (limit--) > 0) {

		if ((rxstat = GEM_RX_DESC_STAT(dp,
				rbp->rxb_slot, rbp->rxb_ndesc)) == 0) {
			/* not received yet */
			break;
		}

		/* Remove the head of rx buffer list */
		if ((dp->rx_buf_head = rbp->rxb_next) == NULL) {
			dp->rx_buf_tail = NULL;
		}
		dp->rx_desc_head += rbp->rxb_ndesc;

		if ((rxstat & GEM_RX_ERR) != 0) {
			gem_append_rxbuf(dp, rbp, FALSE);
			continue;
		}

		len = (int16_t)(rxstat & GEM_RX_LEN);
		DPRINTF(2, (CE_CONT, "%s: gem_receive: rxstat:0x%x, len:0x%x",
				dp->name, rxstat, len));

		if (len > MAXPKTLEN(dp) || len < ETHERMIN) {
			if (len > 0) {
				dp->stats.errrcv++;
				if (len > MAXPKTLEN(dp)) {
					dp->stats.frame_too_long++;
				} else /* (len < ETHERMIN) */ {
					dp->stats.runt++;
				}
			}
			gem_append_rxbuf(dp, rbp, FALSE);
			continue;
		}

		nrbp   = NULL;
		docopy = FALSE;
		if (rbp->rxb_ah != NULL) {	/* copy if type2 */
			docopy = TRUE;
		}
		else if (len <= dp->gc.gc_rx_copy_thresh) {
			/* packet is short */
			docopy = TRUE;
		}
		else if ((nrbp = gem_get_rxbuf(dp, FALSE)) == NULL) {
			/* no rx buffer */
			dp->stats.norcvbuf++;
			docopy = TRUE;
		}

		if (docopy) {
			/*
			 * Copy the packet
			 */
			ASSERT(nrbp == NULL);
			if ((mp = allocb(len, BPRI_MED)) == NULL) {
				/* no memory */
				dp->stats.norcvbuf++;
				gem_append_rxbuf(dp, rbp, FALSE);
				continue;
			}
#ifdef IOCACHE
			ddi_dma_sync(rbp->rxb_dh, dp->gc.gc_rx_header_len,
					len, DDI_DMA_SYNC_FORKERNEL);
#endif
			bcopy(rbp->rxb_mp->b_rptr, mp->b_rptr, len);
			mp->b_wptr = mp->b_rptr + len;
			gem_append_rxbuf(dp, rbp, FALSE);
		}
		else {
			/*
			 * Direct reception
			 */
			ASSERT(nrbp != NULL);
			ASSERT(rbp->rxb_nfrags > 0);
			mp = rbp->rxb_mp;
			rbp->rxb_mp = NULL;
			mp->b_wptr = mp->b_rptr + len;

			if (rbp->rxb_ah == NULL) {
				/* type 1: release dma resources */
				ddi_dma_unbind_handle(rbp->rxb_dh);
				rbp->rxb_nfrags = 0;
				gem_free_rxbuf(rbp);
				ASSERT(dp->rx_buf_freecnt == 1);
			} else /* type 2 */ {
#ifdef IOCACHE
				ddi_dma_sync(rbp->rxb_dh,
						dp->gc.gc_rx_header_len,
						dp->gc.gc_rx_header_len + len,
						DDI_DMA_SYNC_FORKERNEL);
#endif /* IOCACHE */
				/* avoid to be freed */
			}
			gem_append_rxbuf(dp, nrbp, FALSE);
		}

		mutex_exit(&dp->intrlock);
		gld_recv(dp->macinfo, mp);
		mutex_enter(&dp->intrlock);
	}
#ifdef GEM_DEBUG_LEVEL
	{
		int	n;
		n = max(dp->gc.gc_rx_buf_size, 10) - (limit + 1);
		gem_rx_pkts[min(n, sizeof(gem_rx_pkts)/sizeof(uint_t)-1)]++;
	}
#endif
	return;
}

void
gem_receive_copy(struct gem_dev *dp)
{
	int		len;
	int		limit;
	mblk_t		*mp;
	uint32_t	rxstat;

	ASSERT(mutex_owned(&dp->intrlock));

	DPRINTF(2, (CE_CONT, "%s: gem_receive_copy: rx_buf_head:%p",
			dp->name, dp->rx_buf_head));

	limit = max(dp->gc.gc_rx_buf_size, 10);
	while (limit-- > 0) {

		if ((rxstat = GEM_RX_DESC_STAT(dp, 0, 0)) == 0) {
			/* not received yet */
			break;
		}

		if ((rxstat & GEM_RX_ERR) != 0) {
			continue;
		}

		len = (int16_t)(rxstat & GEM_RX_LEN);
		DPRINTF(2, (CE_CONT, "%s: gem_receive: rxstat:0x%x, len:0x%x",
				dp->name, rxstat, len));

		if (len > MAXPKTLEN(dp) || len < ETHERMIN) {
			if (len > 0) {
				dp->stats.errrcv++;
				if (len > MAXPKTLEN(dp)) {
					dp->stats.frame_too_long++;
				} else /* (len < ETHERMIN) */ {
					dp->stats.runt++;
				}
			}
			continue;
		}

		/*
		 * Copy the packet
		 */
		mp = GEM_GET_PACKET(dp, NULL, len);
		if (mp == NULL) {
			/* no memory */
			dp->stats.norcvbuf++;
			continue;
		}

		mutex_exit(&dp->intrlock);
		gld_recv(dp->macinfo, mp);
		mutex_enter(&dp->intrlock);
	}
#ifdef GEM_DEBUG_LEVEL
	{
		int	n;
		n = max(dp->gc.gc_rx_buf_size, 10) - (limit + 1);
		gem_rx_pkts[min(n, sizeof(gem_rx_pkts)/sizeof(uint_t)-1)]++;
	}
#endif
	return;
}

boolean_t
gem_tx_done(struct gem_dev *dp)
{
	struct txbuf		*tbp;
	boolean_t		tx_sched;

	tx_sched = FALSE;
	mutex_enter(&dp->xmitlock);

	if (gem_reclaim_txbuf(dp) != 0) {
		gem_restart_tx(dp);
		gem_tx_start_unit(dp);
		DPRINTF(2, (CE_CONT, "%s: gem_tx_done: tx_desc: %d %d",
			dp->name, dp->tx_desc_head, dp->tx_desc_tail));
	}
	else {
		gem_tx_start_unit(dp);
	}

	DPRINTF(3, (CE_CONT, "%s: gem_tx_done: ret: blocked:%d",
		dp->name, dp->tx_blocked));

	tx_sched = (dp->tx_blocked && (dp->tx_buf_freelist != NULL));

	ASSERT(tx_sched || !dp->tx_blocked || (dp->tx_busy > 0 && dp->tx_buf_freelist == NULL) || dp->tx_desc_intr - dp->tx_desc_head >= 0);
	mutex_exit(&dp->xmitlock);

	return tx_sched;
}

static u_int
gem_interrupt(gld_mac_info_t *macinfo)
{
	struct gem_dev	*dp;
	u_int		ret;

	dp = (struct gem_dev *)(macinfo->gldm_private);

	mutex_enter(&dp->intrlock);
	dp->intr_busy = TRUE;

	ret = GEM_INTERRUPT(dp);

	if (ret == DDI_INTR_UNCLAIMED) {
		dp->intr_busy = FALSE;
		mutex_exit(&dp->intrlock);
		return ret;
	}

	if (!dp->nic_active) {
		cv_broadcast(&dp->drain_cv);
	}

	dp->stats.intr++;
	dp->intr_busy = FALSE;

	mutex_exit(&dp->intrlock);

	if ((ret & INTR_RESTART_TX) != 0) {
		DPRINTF(4, (CE_CONT, "%s: calling gld_sched", dp->name));
		gld_sched(macinfo);
	}

	return ret & ~INTR_RESTART_TX;
}

static void
gem_intr_watcher(gld_mac_info_t *macinfo)
{
	struct gem_dev	*dp;

	dp = (struct gem_dev *)macinfo->gldm_private;

	(macinfo->gldm_intr)(macinfo);
next:
	/* schedule next call of tu_intr_watcher */
	dp->intr_watcher_id =
		timeout((void (*)(void *))gem_intr_watcher, (void *)macinfo, 1);
}

/* ======================================================================== */
/*
 * MII support routines
 */
/* ======================================================================== */
static uint16_t
gem_mii_read(struct gem_dev *dp, uint_t reg)
{
	if (!dp->no_preamble) {
		GEM_MII_SYNC(dp);
	}
	return GEM_MII_READ(dp, reg);
}

static void
gem_mii_write(struct gem_dev *dp, uint_t reg, uint16_t val)
{
	if (!dp->no_preamble) {
		GEM_MII_SYNC(dp);
	}
	GEM_MII_WRITE(dp, reg, val);
}

int
gem_mii_config_default(struct gem_dev *dp)
{
	uint16_t	mii_stat;
	uint16_t	xstat;
	uint16_t	val;

	DPRINTF(2, (CE_CONT, "%s: gem_mii_config: called", dp->name));

	/*
	 * Set advertisement register
	 */
	mii_stat = gem_mii_read(dp, MII_STATUS);
	DPRINTF(2, (CE_CONT, "%s: gem_mii_config: MII_STATUS reg:%b",
		dp->name, mii_stat, MII_STATUS_BITS));

	if ((mii_stat & MII_STATUS_ABILITY) == 0) {
		/* it's funny */
		cmn_err(CE_WARN, "%s: wrong ability bits: mii_status:%b",
			dp->name, mii_stat, MII_STATUS_BITS);
		return -1;
	}

	/* Do not change the rest of ability bits in advert reg */
	val = gem_mii_read(dp, MII_AN_ADVERT) & ~MII_ABILITY;

	if ((mii_stat & MII_STATUS_100_BASE_T4) != 0 && dp->anadv_100t4) {
		val |= MII_ABILITY_100BASE_T4;
	}
	if ((mii_stat & MII_STATUS_100_BASEX_FD) != 0 && dp->anadv_100fdx) {
		val |= MII_ABILITY_100BASE_TX_FD;
	}
	if ((mii_stat & MII_STATUS_100_BASEX) != 0 && dp->anadv_100hdx) {
		val |= MII_ABILITY_100BASE_TX;
	}
	if ((mii_stat & MII_STATUS_10_FD) != 0 && dp->anadv_10fdx) {
		val |= MII_ABILITY_10BASE_T_FD;
	}
	if ((mii_stat & MII_STATUS_10) != 0 && dp->anadv_10hdx) {
		val |= MII_ABILITY_10BASE_T;
	}

	if (dp->gc.gc_flow_control) {
		val |= MII_ABILITY_PAUSE;
	} else {
		val &= ~MII_ABILITY_PAUSE;
	}

	DPRINTF(1, (CE_CONT, "%s: gem_mii_config: setting MII_AN_ADVERT reg:%b",
		dp->name, val, MII_ABILITY_BITS));

	gem_mii_write(dp, MII_AN_ADVERT, val);
#ifdef GEM_GIGA
	if (dp->gc.gc_mii_mode == GEM_MODE_1000BASET) {
		/*
		 * 1000Base-T GMII support
		 */
		val = gem_mii_read(dp, MII_1000TC) &
				~(MII_1000TC_ADV_FULL | MII_1000TC_ADV_HALF);
		xstat = gem_mii_read(dp, MII_XSTATUS);
		if ((xstat & MII_XSTATUS_1000BASET_FD) != 0 &&
		     dp->anadv_1000fdx) {
			val |= MII_1000TC_ADV_FULL;
		}
		if ((xstat & MII_XSTATUS_1000BASET) != 0 &&
		     dp->anadv_1000hdx) {
			val |= MII_1000TC_ADV_HALF;
		}

		DPRINTF(1, (CE_CONT,
			"%s: gem_mii_config: setting MII_1000TC reg:%b",
			dp->name, val, MII_1000TC_BITS));

		gem_mii_write(dp, MII_1000TC, val);
	}
#endif /* GEM_GIGA */
	return 0;
}

clock_t
gem_mii_link_check(struct gem_dev *dp)
{
	uint16_t	mii_stat;
	uint16_t	advert;
	uint16_t	lpable;
#ifdef GEM_GIGA
	uint16_t	ctl1000;
	uint16_t	stat1000;
#endif
	uint16_t	val;
	clock_t		now;
	clock_t		diff;
	clock_t		interval;
	boolean_t	use_rsan = TRUE;

	now = ddi_get_lbolt();
	diff = now - dp->mii_last_check;
	dp->mii_last_check = now;

	DPRINTF(3, (CE_CONT, "!%s: mii_link_check: time:%d state:%d",
				dp->name, now, dp->mii_state));

next_nowait:
	switch (dp->mii_state) {
	case MII_STATE_RESETTING:
		dp->mii_timer -= diff;
		if (dp->mii_timer > 0) {
			/* wait for time-up */
			interval = WATCH_INTERVAL_FAST;
			goto next;
		}

		/* Timer expired, ensure reset bit is not set */

		GEM_MII_SYNC(dp);
		if ((gem_mii_read(dp, MII_CONTROL) & MII_CONTROL_RESET) != 0) {
			/*
			 * Workaround for DL10050B
			 * PHY doesn't seems to have reset autoclear capability
			 * Deassert reset state manually
			 */
			cmn_err(CE_NOTE, "!%s: resetting phy not complete.",
				dp->name);
			gem_mii_write(dp, MII_CONTROL, 0);
		}

		/* Configure PHY registers */
		if (GEM_MII_CONFIG(dp) != 0) {
			goto reset_phy;
		}

		if (dp->mii_fixedmode) {
			dp->mii_state = MII_STATE_MEDIA_SETUP;
			dp->mii_timer = 0;
			interval = 0;
			goto next_nowait;
		}

		/* Issue auto-negotiation command */
		goto autonego;

	case MII_STATE_AUTONEGOTIATING:
		/*
		 * Autonegotiation in progress
		 */
		dp->mii_timer -= diff;
		if (dp->mii_timer -
		      (dp->gc.gc_mii_an_timeout - dp->gc.gc_mii_an_wait) > 0) {
			/* wait for minimum time (2.3 - 2.5 sec) for rhine */
			interval = WATCH_INTERVAL_FAST;
			goto next;
		}

		/* read PHY status */
		mii_stat = gem_mii_read(dp, MII_STATUS);
		DPRINTF(4, (CE_CONT,
			"%s: gem_mii_link_check: called: "
			"mii_state:%d MII_STATUS reg:%b",
			dp->name, dp->mii_state,
			mii_stat, MII_STATUS_BITS));

		if ((mii_stat & MII_STATUS_REMFAULT) != 0) {
			/*
			 * The link parnert told me something wrong happend.
			 * What do we do ?
			 */
			cmn_err(CE_CONT,
				"!%s: auto-negotiation failed: remote fault",
				dp->name);
			goto autonego;
		}

		if ((mii_stat & MII_STATUS_ANDONE) == 0) {
			if (dp->mii_timer <= 0) {
				/*
				 * Auto-negotiation timed out,
				 * Reset PHY and try again.
				 */
				if (!dp->mii_supress_msg) {
					cmn_err(CE_WARN,
					"!%s: auto-negotiation failed: timeout",
					dp->name);
					dp->mii_supress_msg = TRUE;
				}
#ifdef notdef
				/* stop auto negotiation */
				val = gem_mii_read(dp, MII_CONTROL);
				gem_mii_write(dp, MII_CONTROL,
				   val & ~(MII_CONTROL_RSAN | MII_CONTROL_ANE));
#endif
				goto autonego;
			}
			/*
			 * Auto-negotiation is in progress. Wait.
			 */
			interval = dp->gc.gc_mii_an_watch_interval;
			goto next;
		}

		/*
		 * Auto-negotiation have done.
		 * Assume linkdown and fall through.
		 */
		dp->mii_supress_msg = FALSE;
		dp->mii_state = MII_STATE_AN_DONE;
		cmn_err(CE_CONT, "!%s: auto-negotiation done", dp->name);

		if (dp->gc.gc_mii_an_delay > 0) {
			/*
			 * 2002/06/02
			 * VT86C100A needs additional waiting time (100mS)
			 * before AN_LPAR register becomes ready.
			 */
			dp->mii_timer = dp->gc.gc_mii_an_delay;
			interval = drv_usectohz(20*1000);
			goto next;
		}

		dp->mii_timer = 0;
		diff = 0;
		goto next_nowait;

	case MII_STATE_AN_DONE:
		/*
		 * Auto-negotiation have done.
		 * Now we can set up media.
		 */
		dp->mii_timer -= diff;
		if (dp->mii_timer > 0) {
			/*
			 * wait for a while
			 */
			interval = WATCH_INTERVAL_FAST;
			goto next;
		}

		/*
		 * set up the result of auto negotiation 
		 */

		/* determine full/half and 1000Mbps/100Mbps/10Mbps */
		advert = gem_mii_read(dp, MII_AN_ADVERT);
		lpable = gem_mii_read(dp, MII_AN_LPABLE);

		DPRINTF(0, (CE_CONT,
			"!%s: gem_mii_link_check: advert:%b, lpable:%b",
			dp->name,
			advert, MII_ABILITY_BITS,
			lpable, MII_ABILITY_BITS));
		/*
		 * configure link mode according to AN priority.
		 */	
		val = advert & lpable;
#ifdef GEM_GIGA
		ctl1000  = 0;
		stat1000 = 0;
		if (dp->gc.gc_mii_mode == GEM_MODE_1000BASET) {
			ctl1000  = GEM_MII_READ(dp, MII_1000TC);
			stat1000 = GEM_MII_READ(dp, MII_1000TS);
			DPRINTF(1, (CE_CONT,
				"%s: MII_1000TC reg:%b, MII_1000TS reg:%b",
				dp->name,
				ctl1000, MII_1000TC_BITS,
				stat1000, MII_1000TS_BITS));
		}

		if ((ctl1000 & MII_1000TC_ADV_FULL) != 0 &&
		    (stat1000 & MII_1000TS_LP_FULL) != 0) {
			/* 1000BaseT & full duplex */
			dp->speed	 = GEM_SPD_1000;
			dp->full_duplex  = TRUE;
			dp->flow_control = (val & MII_ABILITY_PAUSE) != 0;
		}
		else if ((ctl1000 & MII_1000TC_ADV_HALF) != 0 &&
			 (stat1000 & MII_1000TS_LP_HALF) != 0) {
			/* 1000BaseT & half duplex */
			dp->speed	 = GEM_SPD_1000;
			dp->full_duplex  = FALSE;
		}
		else 
#endif /* GEM_GIGA */
		if ((val & MII_ABILITY_100BASE_TX_FD) != 0) {
			/* 100BaseTx & fullduplex */
			dp->speed	 = GEM_SPD_100;
			dp->full_duplex  = TRUE;
			dp->flow_control = (val & MII_ABILITY_PAUSE) != 0;
		}
		else if ((val & MII_ABILITY_100BASE_TX) != 0) {
			/* 100BaseTx & half duplex */
			dp->speed	 = GEM_SPD_100;
			dp->full_duplex  = FALSE;
			dp->flow_control = FALSE;
		}
		else if ((val & MII_ABILITY_10BASE_T_FD) != 0) {
			/* 10BaseT & full duplex */
			dp->speed	 = GEM_SPD_10;
			dp->full_duplex  = TRUE;
			dp->flow_control = (val & MII_ABILITY_PAUSE) != 0;
		}
		else if ((val & MII_ABILITY_10BASE_T) != 0) {
			/* 10BaseT & half duplex */
			dp->speed	 = GEM_SPD_10;
			dp->full_duplex  = FALSE;
			dp->flow_control = FALSE;
		}
		else {
			/*
			 * It seem that the link partnar don't have
			 * auto-negotiation capability and our PHY
			 * could not report the correct current mode.
			 * This case happened on VT86C100A chip so
			 * that we guess current mode by mii_control
			 * register.
			 */

			val = gem_mii_read(dp, MII_CONTROL);

			cmn_err(CE_NOTE,
				"!%s: auto-negotiation done but "
				"common ability not found.\n"
				"PHY state: control:%b advert:%b lpable:%b\n"
				"guessing the following mode...",
				dp->name,
				val, MII_CONTROL_BITS,
				advert, MII_ABILITY_BITS,
				lpable, MII_ABILITY_BITS);

			/* select 100m full or 10m half */
			dp->speed = ((val & MII_CONTROL_100MB) != 0)
						? GEM_SPD_100 : GEM_SPD_10;
			dp->full_duplex  = dp->speed != GEM_SPD_10;
			dp->flow_control = FALSE;
		}
#ifdef notdef
		dp->mii_state = MII_STATE_MEDIA_SETUP;
		goto next_nowait;
#else
		/* fall down */
#endif

	case MII_STATE_MEDIA_SETUP:
		if (dp->mii_fixedmode || dp->gc.gc_mii_an_oneshot) {
			/*
			 * write the result of auto negotiation back.
			 * XXX - This code didn't work on AN983B.
			 */
			val = gem_mii_read(dp, MII_CONTROL);
			val &= ~(MII_CONTROL_SPEED | MII_CONTROL_FDUPLEX |
				 MII_CONTROL_ANE   | MII_CONTROL_RSAN);

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
				/* for GEM_SPD_10, do nothing */
				break;
			}

			gem_mii_write(dp, MII_CONTROL, val);
		}

		GEM_SET_MEDIA(dp);

		if ((void *)(dp->gc.gc_mii_tune_phy) != NULL) {
			/* for built-in sis900 */
			GEM_MII_TUNE_PHY(dp);
		}

		dp->mii_state = MII_STATE_LINKDOWN;
		dp->mii_timer = dp->gc.gc_mii_linkdown_timeout;
		DPRINTF(2, (CE_CONT, "!%s: setup midia mode done", dp->name));
		dp->mii_supress_msg = FALSE;

		/* use short interval */
		interval = WATCH_INTERVAL_FAST;
		goto next_nowait;

	case MII_STATE_LINKDOWN:
		mii_stat = gem_mii_read(dp, MII_STATUS);
		if ((mii_stat & MII_STATUS_LINKUP) != 0) {
			/*
			 * Link going up
			 */
			dp->mii_state = MII_STATE_LINKUP;
			dp->mii_supress_msg = FALSE;

			DPRINTF(0, (CE_CONT,
				"!%s: link up detected: mii_stat:%b",
				dp->name, mii_stat, MII_STATUS_BITS));

			/* restart tx watchdog */
			dp->tx_start_time = ddi_get_lbolt();

			/*
			 * MII_CONTROL_100MB and  MII_CONTROL_FDUPLEX are
			 * ignored when MII_CONTROL_ANE is set.
			 */
			cmn_err(CE_CONT,
			    "!%s: Link up: %d Mbps %s duplex %s flow control",
				dp->name,
				gem_speed_value[dp->speed],
				dp->full_duplex ? "full" : "half",
				dp->flow_control ? "with" : "without");

			interval = dp->gc.gc_mii_link_watch_interval;
#ifdef S10
			gld_linkstate(dp->macinfo, GLD_LINKSTATE_UP);
#endif
			goto next;
		}

		dp->mii_supress_msg = TRUE;
		if (!dp->mii_fixedmode) {
			dp->mii_timer -= diff;
			if (dp->mii_timer <= 0) {
				/*
				 * the link down timer expired.
				 * need to restart auto-negotiation.
				 */
				goto restart_autonego;
			}
		}
		/* don't change mii_state */
		break;

	case MII_STATE_LINKUP:
		mii_stat = gem_mii_read(dp, MII_STATUS);
		if ((mii_stat & MII_STATUS_LINKUP) == 0) {
			/*
			 * Link going down
			 */
			cmn_err(CE_NOTE,
				"%s: link down detected: mii_stat:%b "
				"restarting auto-negotiation",
				dp->name, mii_stat, MII_STATUS_BITS);
#ifdef S10
			gld_linkstate(dp->macinfo, GLD_LINKSTATE_DOWN);
#endif
			dp->mii_supress_msg = TRUE;

			if (!dp->mii_fixedmode) {
				/* need to restart auto-negotiation */
#ifdef notdef
				goto restart_autonego;
#else
				goto reset_phy;
#endif
			}

			dp->mii_state = MII_STATE_LINKDOWN;
			dp->mii_timer = dp->gc.gc_mii_linkdown_timeout;

			if ((void *)(dp->gc.gc_mii_tune_phy) != NULL) {
				/* for built-in sis900 */
				GEM_MII_TUNE_PHY(dp);
			}
		}
		/* don't change mii_state */
		break;
	}
	interval = dp->gc.gc_mii_link_watch_interval;
	goto next;

	/* Actions on the end of state routine */

restart_autonego:
	switch (dp->gc.gc_mii_linkdown_action) {
	case MII_ACTION_RESET:
		goto reset_phy;

	case MII_ACTION_NONE:
		if (dp->gc.gc_mii_an_oneshot) {
			goto autonego;
		}
		/* PHY will restart autonego automatically */
		dp->mii_state = MII_STATE_AUTONEGOTIATING;
		dp->mii_timer = dp->gc.gc_mii_an_timeout;
		interval = dp->gc.gc_mii_an_watch_interval;
		goto next;

	case MII_ACTION_RSA:
		use_rsan = TRUE;
		goto autonego;

	default:
		cmn_err(CE_PANIC, "%s: unknowm linkdown action: %d",
			dp->name, dp->gc.gc_mii_linkdown_action);
	}
	/* NOTREACHED */

reset_phy:
#ifdef S10
	gld_linkstate(dp->macinfo, GLD_LINKSTATE_DOWN);
#endif
	if (!dp->mii_supress_msg) {
		cmn_err(CE_CONT, "!%s: resetting PHY", dp->name);
	}
	dp->mii_state = MII_STATE_RESETTING;
	dp->mii_timer = dp->gc.gc_mii_reset_timeout;
	if (!dp->gc.gc_mii_dont_reset) {
		gem_mii_write(dp, MII_CONTROL, MII_CONTROL_RESET);
	}
	interval = WATCH_INTERVAL_FAST;
	goto next;

autonego:
#ifdef S10
	gld_linkstate(dp->macinfo, GLD_LINKSTATE_DOWN);
#endif
	if (!dp->mii_supress_msg) {
		cmn_err(CE_CONT, "!%s: auto-negotiation started", dp->name);
	}
	dp->mii_state = MII_STATE_AUTONEGOTIATING;
	dp->mii_timer = dp->gc.gc_mii_an_timeout;

	val = gem_mii_read(dp, MII_CONTROL);
	if (use_rsan || (val & MII_CONTROL_ANE) != 0) {
		/* restart auto nego */
		gem_mii_write(dp, MII_CONTROL,
				val | MII_CONTROL_ANE | MII_CONTROL_RSAN);
	}
	else {
		/* enable auto nego */
		/* it doesn't work for mx98715 */
		gem_mii_write(dp, MII_CONTROL, val | MII_CONTROL_ANE);
	}

	interval = dp->gc.gc_mii_an_watch_interval;

next:
	return interval;
}

static void
gem_mii_link_watcher(struct gem_dev *dp)
{
	clock_t	next;

	mutex_enter(&dp->intrlock);
	next = gem_mii_link_check(dp);
	mutex_exit(&dp->intrlock);

	if (next != (clock_t)0) {
		dp->link_watcher_id =
			timeout((void (*)(void *))& gem_mii_link_watcher,
				(void *)dp, next);
	}

	return;
}

int
gem_mii_init_default(struct gem_dev *dp)
{
	int		phy;
	uint16_t	status;
	uint16_t	xstatus;

	DPRINTF(3, (CE_CONT, "%s: gem_mii_init: called", dp->name));

	/*
	 * Scan PHY
	 */
	dp->no_preamble = FALSE;
	GEM_MII_SYNC(dp);

	/* Try default phy first */
	if (dp->mii_phy_addr != 0) {
		status = gem_mii_read(dp, MII_STATUS);
		if (status != 0xffff && status != 0x0000) {
			goto PHY_found;
		}

		if (dp->mii_phy_addr < 0) {
			cmn_err(CE_NOTE,
			"!%s: failed to probe default internal/non-MII PHY",
				dp->name);
			return -1;
		}

		cmn_err(CE_NOTE,
			"!%s: failed to probe default MII PHY at %d",
			dp->name, dp->mii_phy_addr);
	}

	/* Try all possible address */
	for (phy = dp->gc.gc_mii_addr_min; phy < 32; phy++) {
		dp->mii_phy_addr = phy;
		status = gem_mii_read(dp, MII_STATUS);

		if (status != 0xffff && status != 0x0000) {
			goto PHY_found;
		}
	}

	cmn_err(CE_NOTE, "!%s: no MII PHY found", dp->name);
	return -1;

PHY_found:
	dp->mii_phy_id  = gem_mii_read(dp, MII_PHYIDH) << 16;
	dp->mii_phy_id |= gem_mii_read(dp, MII_PHYIDL);

	dp->no_preamble = (status & MII_STATUS_MFPRMBLSUPR) != 0;

	if (dp->mii_phy_addr < 0) {
		cmn_err(CE_CONT, "!%s: using internal/non-MII PHY(0x%08x)",
			dp->name, dp->mii_phy_id);
	} else {
		cmn_err(CE_CONT, "!%s: MII PHY (0x%08x) found at %d",
			dp->name, dp->mii_phy_id, dp->mii_phy_addr);
	}

	cmn_err(CE_CONT, "!%s: PHY control:%b, status:%b, advert:%b, lpar:%b",
		dp->name,
		gem_mii_read(dp, MII_CONTROL), MII_CONTROL_BITS,
		status, MII_STATUS_BITS,
		gem_mii_read(dp, MII_AN_ADVERT), MII_ABILITY_BITS,
		gem_mii_read(dp, MII_AN_LPABLE), MII_ABILITY_BITS);
#ifdef GEM_GIGA
	cmn_err(CE_CONT, "!%s: xstatus:%b",
		dp->name,
		gem_mii_read(dp, MII_XSTATUS), MII_XSTATUS_BITS);
#endif
	if (!dp->mii_fixedmode && (status & MII_STATUS_CANAUTONEG) == 0) {
		dp->mii_fixedmode = TRUE;
		/* fix speed and duplex mode. check half duplex first */
		if ((status & MII_STATUS_10) != 0) {
			dp->speed	= GEM_SPD_10;
			dp->full_duplex = FALSE;
		}
		else if ((status & MII_STATUS_100_BASEX) != 0) {
			dp->speed	= GEM_SPD_100;
			dp->full_duplex = FALSE;
		}
		else if ((status & MII_STATUS_10_FD) != 0) {
			dp->speed	= GEM_SPD_10;
			dp->full_duplex = TRUE;
		}
		else if ((status & MII_STATUS_100_BASEX_FD) != 0) {
			dp->speed	= GEM_SPD_100;
			dp->full_duplex = TRUE;
		}
		else if ((status & MII_STATUS_100_BASE_T4) != 0) {
			dp->speed	= GEM_SPD_100;
			dp->full_duplex = FALSE;
		}
	}

	return 0;
}

static void
gem_mii_start(struct gem_dev *dp)
{
	int		phy;
	uint16_t	adv;
	uint16_t	status;
	uint16_t	val;
	clock_t		interval;

#ifdef S10
	gld_linkstate(dp->macinfo, GLD_LINKSTATE_DOWN);
#endif
	if (dp->gc.gc_mii_dont_reset) {
		/* avoid resetting PHY */
		if (GEM_MII_CONFIG(dp) != 0) {
			cmn_err(CE_WARN, "%s: gem_mii_config failed",
				dp->name);
		}
		if (dp->mii_fixedmode) {
			dp->mii_state = MII_STATE_LINKDOWN;
			dp->mii_timer = dp->gc.gc_mii_linkdown_timeout;
			goto x;
		}
		dp->mii_state = MII_STATE_AUTONEGOTIATING;
		dp->mii_timer = dp->gc.gc_mii_an_timeout;
		val = gem_mii_read(dp, MII_CONTROL);
		gem_mii_write(dp, MII_CONTROL,
			val | MII_CONTROL_ANE | MII_CONTROL_RSAN);
		interval = dp->gc.gc_mii_an_watch_interval;
	}
	else {
		/* reset PHY */
		dp->mii_state = MII_STATE_RESETTING;
		dp->mii_timer = dp->gc.gc_mii_reset_timeout;
		gem_mii_write(dp, MII_CONTROL, MII_CONTROL_RESET);
		interval = WATCH_INTERVAL_FAST;
	}
x:
	/* schedule first call of gem_link_watcher */
	dp->mii_last_check = ddi_get_lbolt();
	dp->link_watcher_id =
		timeout((void (*)(void *))& gem_mii_link_watcher,
			(void *)dp, interval);
}

static void
gem_mii_stop(struct gem_dev *dp)
{
	timeout_id_t	old_id;

	/* Ensure timer routine stopped */
	if (dp->link_watcher_id != 0) {
		do {
			untimeout(old_id = dp->link_watcher_id);
		} while (old_id != dp->link_watcher_id);
		dp->link_watcher_id = 0;
	}
}

void
gem_generate_macaddr(struct gem_dev *dp, uint8_t *mac)
{
	int		i;
	uint_t		val;

	cmn_err(CE_CONT,
	"!%s: using temporal ether address, do not use this for long time",
		dp->name);
	val = ddi_get_lbolt() ^ ddi_get_time();

	/* 00:00:17:xx:xx:xx seems not to be assigned */
	mac[0] = 0x00;
	mac[1] = 0x00;
	mac[2] = 0x17;
	mac[3] = val >> 16;
	mac[4] = val >> 8;
	mac[5] = val ^ (val >> 24);

	return;
}

boolean_t
gem_get_mac_addr_conf(struct gem_dev *dp)
{
	char		propname[32];
	char		valstr[32];
	uint8_t		mac[ETHERADDRL];
	char		*cp;
	int		len;
	int		c;
	int		i;
	int		j;
	int		v;
	int		d;
	int		ored;

	/*
	 * Get ethernet address from .conf file
	 */
	valstr[0] = 0;
	sprintf(propname, "%s-mac-addr", dp->name);
	len = sizeof(valstr);
	if ((ddi_getlongprop_buf(DDI_DEV_T_ANY, dp->dip,
			DDI_PROP_DONTPASS, propname, valstr,
			&len)) != DDI_PROP_SUCCESS) {
#ifdef notdef
		cmn_err(CE_CONT,
			"!%s: trying to read %s property from .conf: undefined",
			dp->name, propname);
#endif
		return FALSE;
	}

	if (strlen(valstr) != ETHERADDRL*3-1) {
		goto syntax_err;
	}

	cp = valstr;
	j  = 0;
	ored = 0;
	while (1) {
		v = 0;
		for (i = 0; i < 2; i++) {
			c = *cp++;

			if (c >= 'a' && c <= 'f') {
				d = c - 'a' + 10;
			}
			else if (c >= 'A' && c <= 'F') {
				d = c - 'A' + 10;
			}
			else if (c >= '0' && c <= '9') {
				d = c - '0';
			}
			else {
				goto syntax_err;
			}
			v = (v << 4) | d;
		}

		mac[j++] = v;
		ored |= v;
		if (j == ETHERADDRL) {
			/* done */
			break;
		}

		c = *cp++;
		if (c != ':') {
			goto syntax_err;
		}
	}

	if (ored == 0) {
		gem_generate_macaddr(dp, mac);
	}

	for (i = 0; i < ETHERADDRL; i++) {
		dp->dev_addr.ether_addr_octet[i] = mac[i];
	}
	return TRUE;

syntax_err:
	cmn_err(CE_CONT,
		"!%s: read mac addr: trying .conf: syntax err %s",
		dp->name, valstr);

	return FALSE;
}

/* ======================================================================== */
/*
 * attach/detatch support
 */
/* ======================================================================== */
static void
gem_read_conf(struct gem_dev *dp)
{
	char			valstr[32];
	char			propname[32];
	int			len;
	int			val;

	/*
	 * Get media mode infomation from .conf file
	 */
	sprintf(propname, "%s-duplex", dp->name);
	len = sizeof(valstr);
	if ((ddi_getlongprop_buf(DDI_DEV_T_ANY, dp->dip,
			DDI_PROP_DONTPASS, propname, valstr,
			&len)) == DDI_PROP_SUCCESS) {
		dp->mii_fixedmode = TRUE;
		if (strcmp(valstr, "full") == 0) {
			dp->full_duplex = TRUE;
			dp->gc.gc_flow_control = TRUE;
		}
		else if (strcmp(valstr, "half") == 0) {
			dp->full_duplex = FALSE;
		}
		else {
			cmn_err(CE_WARN,
				"%s: property %s: illegal value (%s)",
				dp->name, propname, valstr);
		}
	}

	sprintf(propname, "%s-speed", dp->name);
	val = ddi_getprop(DDI_DEV_T_ANY, dp->dip,
				DDI_PROP_DONTPASS, propname, -1);
	if (val != -1)  {
		dp->mii_fixedmode = TRUE;
		if (val == 1000) {
			dp->speed = GEM_SPD_1000;
		}
		else if (val == 100) {
			dp->speed = GEM_SPD_100;
		}
		else if (val == 10) {
			dp->speed = GEM_SPD_10;
		}
		else {
			cmn_err(CE_WARN,
				"%s: property %s: illegal value (%d)",
				dp->name, propname, val);
		}
	}

	sprintf(propname, "%s-flow-control", dp->name);
	val = ddi_getprop(DDI_DEV_T_ANY, dp->dip, DDI_PROP_DONTPASS, propname, -1);
	if (val != -1) {
		dp->gc.gc_flow_control = !(val == 0);
		if (val != 1 && val != 0) {
			cmn_err(CE_WARN,
				"%s: property %s: illegal value (%d)",
				dp->name, propname, val);
		}
	}

	if (dp->gc.gc_mii_mode == GEM_MODE_1000BASET) {
		sprintf(propname, "%s-anadv-1000fdx", dp->name);
		val = ddi_getprop(DDI_DEV_T_ANY, dp->dip,
						DDI_PROP_DONTPASS, propname, 1);
		dp->anadv_1000fdx = (val != 0);

		sprintf(propname, "%s-anadv-1000hdx", dp->name);
		val = ddi_getprop(DDI_DEV_T_ANY, dp->dip,
						DDI_PROP_DONTPASS, propname, 1);
		dp->anadv_1000hdx = (val != 0);
	}

	sprintf(propname, "%s-anadv-100t4", dp->name);
	val = ddi_getprop(DDI_DEV_T_ANY, dp->dip,
					DDI_PROP_DONTPASS, propname, 1);
	dp->anadv_100t4 = (val != 0);

	sprintf(propname, "%s-anadv-100fdx", dp->name);
	val = ddi_getprop(DDI_DEV_T_ANY, dp->dip,
					DDI_PROP_DONTPASS, propname, 1);
	dp->anadv_100fdx = (val != 0);

	sprintf(propname, "%s-anadv-100hdx", dp->name);
	val = ddi_getprop(DDI_DEV_T_ANY, dp->dip,
					DDI_PROP_DONTPASS, propname, 1);
	dp->anadv_100hdx = (val != 0);

	sprintf(propname, "%s-anadv-10fdx", dp->name);
	val = ddi_getprop(DDI_DEV_T_ANY, dp->dip,
					DDI_PROP_DONTPASS, propname, 1);
	dp->anadv_10fdx = (val != 0);

	sprintf(propname, "%s-anadv-10hdx", dp->name);
	val = ddi_getprop(DDI_DEV_T_ANY, dp->dip,
					DDI_PROP_DONTPASS, propname, 1);
	dp->anadv_10hdx = (val != 0);

	sprintf(propname, "%s-nointr", dp->name);
	val = ddi_getprop(DDI_DEV_T_ANY, dp->dip,
					DDI_PROP_DONTPASS, propname, 0);
	if (val != 0) {
		dp->misc_flag |= GEM_NOINTR;
		cmn_err(CE_CONT, "%s: polling mode enabled", dp->name);
	}

	sprintf(propname, "%s-mtu", dp->name);
	dp->mtu = ddi_getprop(DDI_DEV_T_ANY, dp->dip,
				DDI_PROP_DONTPASS, propname, dp->mtu);

	sprintf(propname, "%s-txthr", dp->name);
	dp->txthr = ddi_getprop(DDI_DEV_T_ANY, dp->dip,
				DDI_PROP_DONTPASS, propname, dp->txthr);

	sprintf(propname, "%s-txmaxdma", dp->name);
	dp->txmaxdma = ddi_getprop(DDI_DEV_T_ANY, dp->dip,
				DDI_PROP_DONTPASS, propname, dp->txmaxdma);

	sprintf(propname, "%s-rxthr", dp->name);
	dp->rxthr = ddi_getprop(DDI_DEV_T_ANY, dp->dip,
				DDI_PROP_DONTPASS, propname, dp->rxthr);

	sprintf(propname, "%s-rxmaxdma", dp->name);
	dp->rxmaxdma = ddi_getprop(DDI_DEV_T_ANY, dp->dip,
				DDI_PROP_DONTPASS, propname, dp->rxmaxdma);
}

#define	GEM_LOCAL_DATA_SIZE(gc)	\
	(sizeof(struct gem_dev) + GEM_MCALLOC + \
	sizeof(struct txbuf)*((gc)->gc_tx_buf_size))

struct gem_dev *
gem_do_attach(dev_info_t *dip,
	struct gem_conf *gc, void *base, ddi_acc_handle_t *regs_handlep,
	void *lp, int lmsize)
{
	struct gem_dev		*dp;
	int			i;
	ddi_iblock_cookie_t	c;
	gld_mac_info_t		*macinfo;
	int			ret;
	int			unit;

	unit = ddi_get_instance(dip);

	DPRINTF(2, (CE_CONT, "gem%d: gem_do_attach: called cmd:ATTACH",
		unit));

	macinfo = gld_mac_alloc(dip);
	if (macinfo == NULL) {
		return NULL;
	}

	/*
	 * Allocate soft data structure
	 */
	dp = (struct gem_dev *)
		kmem_zalloc(GEM_LOCAL_DATA_SIZE(gc), KM_SLEEP);
	if (dp == NULL) {
		gld_mac_free(macinfo);
		return NULL;
	}
	/* link to private area */
	dp->private   = lp;
	dp->priv_size = lmsize;

	dp->mc_count   = 0;
	dp->mc_list = (struct mcast_addr *) &dp[1];

	dp->dip = dip;
	dp->macinfo = macinfo;
	bcopy(gc->gc_name, dp->name, GEM_NAME_LEN);

	/*
	 * Get iblock cookie
	 */
	if (ddi_get_iblock_cookie(dip, 0, &c) != DDI_SUCCESS) {
		cmn_err(CE_CONT,
			"%s: gem_do_attach: ddi_get_iblock_cookie: failed",
			dp->name);
		goto err_free_private;
	}
	dp->iblock_cookie = c;

	/*
	 * Initialize mutex's for this device.
	 */
	mutex_init(&dp->intrlock, NULL, MUTEX_DRIVER, (void *)c);
	mutex_init(&dp->xmitlock, NULL, MUTEX_DRIVER, (void *)c);
	cv_init(&dp->drain_cv, NULL, CV_DRIVER, NULL);

	/*
	 * configure gem parameter
	 */
	dp->base_addr   = base;
	dp->regs_handle = *regs_handlep;
	dp->gc = *gc;
	gc     = &dp->gc;
#ifdef IOMMU
	if (dp->gc.gc_rx_max_frags == 1) {
		/*
		 * fake gem to use allocb for rx buffer allocation
		 */
		dp->gc.gc_rx_max_frags = 2;
		dp->gc.gc_rx_max_descs_per_pkt = 1;
	}
#endif
	dp->mtu		= ETHERMTU;
	dp->tx_buf	= (struct txbuf *)((caddr_t)(&dp[1])+GEM_MCALLOC);
	dp->rxmode	= 0;
	dp->mii_fixedmode = FALSE;	/* default is autoneg */
	dp->speed	  = GEM_SPD_10;	/* default is 10Mbps */
	dp->full_duplex   = FALSE;	/* default is half */
	dp->flow_control  = gc->gc_flow_control;


        /* performance tuning parameters */
	dp->txthr    = 256;		/* tx fifo threshoold */
	dp->txmaxdma = 128;		/* tx max dma burst size */
	dp->rxthr    = 128;		/* rx fifo threshoold */
	dp->rxmaxdma = 128;		/* rx max dma burst size */

	/*
	 * Get media mode infomation from .conf file
	 */
	gem_read_conf(dp);

	/* XXX - buflen was aligned to support rtl8169 */
	dp->rx_buf_len = ROUNDUP(MAXPKTBUF(dp) + dp->gc.gc_rx_header_len,
				dp->gc.gc_rx_buf_align + 1);

	/*
	 * Reset the chip
	 */
	if (GEM_RESET_CHIP(dp) != 0) {
		goto err_free_regs;
	}

	/*
	 * HW dependant paremeter initialization
	 */
	GEM_ATTACH_CHIP(dp);

	/*
	 * configure GLD 
	 */
	macinfo->gldm_devinfo	   = dip;
	macinfo->gldm_private	   = (caddr_t)dp;
	macinfo->gldm_cookie       = dp->iblock_cookie;
	macinfo->gldm_reset        = gem_reset;
	macinfo->gldm_start        = gem_start;
	macinfo->gldm_stop         = gem_stop;
	macinfo->gldm_set_mac_addr = gem_set_mac_address;
	macinfo->gldm_send         = gem_send;
	macinfo->gldm_set_promiscuous = gem_set_promiscuous;
	macinfo->gldm_get_stats    = gem_get_stats;
	macinfo->gldm_ioctl        = NULL; 
	macinfo->gldm_set_multicast= gem_set_multicast;
	macinfo->gldm_intr         = gem_interrupt;
	macinfo->gldm_mctl         = NULL;

	macinfo->gldm_ident   = (char *)ddi_driver_name(dip);
	macinfo->gldm_type    = DL_ETHER;
	macinfo->gldm_minpkt  = 0;
	macinfo->gldm_maxpkt  = dp->mtu /*ETHERMTU*/;
	macinfo->gldm_addrlen = ETHERADDRL;
	macinfo->gldm_saplen  = -2;
	macinfo->gldm_ppa     = unit;

#ifdef S10
	macinfo->gldm_capabilities = GLD_CAP_LINKSTATE;
#endif


	/* allocate tx and rx resources */
	if (gem_alloc_memory(dp) != 0) {
		goto err_free_regs;
	}

	cmn_err(CE_CONT,
	"!%s: at 0x%x, %02x:%02x:%02x:%02x:%02x:%02x",
		dp->name, (long)dp->base_addr,
		dp->dev_addr.ether_addr_octet[0],
		dp->dev_addr.ether_addr_octet[1],
		dp->dev_addr.ether_addr_octet[2],
		dp->dev_addr.ether_addr_octet[3],
		dp->dev_addr.ether_addr_octet[4],
		dp->dev_addr.ether_addr_octet[5]);

	/* copy mac address */
	dp->cur_addr = dp->dev_addr;
	macinfo->gldm_vendor_addr =
			dp->dev_addr.ether_addr_octet;
	macinfo->gldm_broadcast_addr =
			etherbroadcastaddr.ether_addr_octet;

	/* Init MII (scan phy)*/
	if (GEM_MII_INIT(dp) == 0) {
		/* reset_mii and start mii link watcher */
		gem_mii_start(dp);
	}

	/*
	 * Add interrupt to system.
	 */
	if (gld_register(dip,
			(char *)ddi_driver_name(dip), macinfo) != DDI_SUCCESS) {
		goto err_stop_mii;
	}

	if ((dp->misc_flag & GEM_NOINTR) == 0) {
		if (ddi_add_intr(dip, 0, NULL, NULL, gld_intr,
					(caddr_t)macinfo) != DDI_SUCCESS) {
			ddi_regs_map_free(&dp->regs_handle);
			cmn_err(CE_WARN, "%s: ddi_add_intr failed", dp->name);
			goto err_unregister;
		}
	}
	else {
		/*
		 * Dont use interrupt.
		 * schedule first call of gem_intr_watcher
		 */
		dp->intr_watcher_id =
			timeout((void (*)(void *))gem_intr_watcher,
				(void *)macinfo, drv_usectohz(3*1000000));
	}

	DPRINTF(2, (CE_CONT, "gem_do_attach: return: success"));
	return dp;

err_unregister:
	gld_unregister(macinfo);
err_stop_mii:
	gem_mii_stop(dp);
err_free_ring:
	gem_free_memory(dp);
err_free_regs:
	ddi_regs_map_free(&dp->regs_handle);
err_free_locks:
	mutex_destroy(&dp->intrlock);
	mutex_destroy(&dp->xmitlock);
	cv_destroy(&dp->drain_cv);
err_free_private:
	kmem_free((caddr_t)dp, GEM_LOCAL_DATA_SIZE(gc));
	gld_mac_free(macinfo);

	return NULL;
}

int
gem_do_detach(dev_info_t *dip)
{
	struct gem_dev	*dp;
	gld_mac_info_t	*macinfo;
	timeout_id_t	old_id;

	macinfo = (gld_mac_info_t *)ddi_get_driver_private(dip);
	dp = (struct gem_dev *)macinfo->gldm_private;

	/* check if all rx buffers are freed */

	if (dp->rx_buf_allocated != dp->rx_buf_freecnt) {
		/*
		 * resource is busy
		 */
		cmn_err(CE_NOTE,
		"%s: gem_do_detach: rxbuf is busy: allocated:%d, freecnt:%d",
			dp->name, dp->rx_buf_allocated, dp->rx_buf_freecnt);

		return DDI_FAILURE;
	}

	/*
	 * stop the device
	 */

	/* stop interrupt watcher */
	if ((dp->misc_flag & GEM_NOINTR) != 0 &&
	    dp->intr_watcher_id != 0) {
		do {
			untimeout(old_id = dp->intr_watcher_id);
		} while (old_id != dp->intr_watcher_id);
		dp->intr_watcher_id = 0;
	}

	gem_mii_stop(dp);

	/*
	 * unregister interrupt handler
	 */
	if ((dp->misc_flag & GEM_NOINTR) == 0) {
		ddi_remove_intr(dip, 0, dp->iblock_cookie);
	}

	(void)gld_unregister(macinfo);

	gem_free_memory(dp);

	/*
	 * Release mapping resources
	 */
	ddi_regs_map_free(&dp->regs_handle);

	mutex_destroy(&dp->xmitlock);
	mutex_destroy(&dp->intrlock);
	cv_destroy(&dp->drain_cv);

	/*
	 * Release memory resources
	 */
	kmem_free((caddr_t)(dp->private), dp->priv_size);
	kmem_free((caddr_t)dp, GEM_LOCAL_DATA_SIZE(&dp->gc));
	gld_mac_free(macinfo);
	DPRINTF(2, (CE_CONT, "%s%d: gem_do_detach: return: success",
			ddi_driver_name(dip), ddi_get_instance(dip)));

	return DDI_SUCCESS;
}
