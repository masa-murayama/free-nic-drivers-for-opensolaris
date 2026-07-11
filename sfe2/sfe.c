/*
 *  A DP83815/SiS900 PCI Fast Ethernet driver for Solaris.
 *  %W% %E%
 *  Copyright (C) 2002  Masayuki Murayama (KHF04453@nifty.ne.jp)
 *
 *  CAUTION: NO WARRANTY
 *  This software may be used and distributed according to the terms
 *  of the GNU Lesser General Public License, incorporated herein by reference.
 */

/*
 Change log:
 04/07/2002 Alpha version 0.8.0 released.
 04/13/2002
	sfe_receive() and sfe_append_rxbuf():
	    refill RX buffer on call back
	sfe_set_media():
	    flow control enabled but not tested.
	sfe_send():
	    free transmitted descriptors before abandon transmitting

 04/19/2002 0.8.1
	fixed mode supported
	tx flow control supported (sis900 and dp83815)

 06/02/2002
	sfe_mii_link_watcher():
	inserting delay before readint ANLPAR reg in auto-negotiation

 06/05/2002
	sfeattach():
	adding register address space auto-selection

 06/05/2002
	remove __FUNCTION__ macro
	fix sfe_read_eeprom for speed.

 07/28/2002
	fixed for sis6xx adn sis7016
	0.8.2 released

 08/06/2002
	sfe_get_mac_addr_sis635() INW instruction fixed to INL
	0.8.3 released

 08/23/2002
	fix mii I/O  routines for builtin sis900
	sfe_get_mac_addr_sis962() was added (not tested).
	0.8.4 released

 08/25/2002
	ready for compiling on SPARC platforms
	0.8.5 released

 09/08/2002
	sfeprobe deleted.

 09/09/2002
	sfe_mii_read_sis900. sfe_mii_write_sis900. transfering bit count
	fixed. and delays are inserted.

	0.8.6 released

 10/03/2002
	sfe_tx_timeout enabled.
	name of some sfe_dev member changed
	RESUME/SUSPED implemented but not tested yet
	TX_FLOW_CONTROL and RX_FLOW_CONTROL macro swapped
	sfe_set_rx_filter_sis900 refined

 WARNING:
	TX_FLOW_CONTROL does not work. Do not define it.

 TODO:
	resume/suspend : done but not tested
	tx_timeout : done
	swap macro definition of TX_FLOW_CONTROL and RX_FLOW_CONTROL :done
 */

/*
 * Solaris System Header files.
 */
#include <sys/types.h>
#include <sys/sysmacros.h>
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

#include <sys/pci.h>
#include "mii.h"
#include "sfereg.h"

char	ident[] = "sfe v" VERSION;
char	_depends_on[] = {"misc/gld"};


#define	FALSE	(0)
#define	TRUE	(!FALSE)

/*
 * I/O instructions
 */
#define	OUTB(dp, p, v)	\
	ddi_put8((dp)->regs_handle, \
		(uint8_t *)((caddr_t)((dp)->base_addr) + (p)), v)
#define	OUTW(dp, p, v)	\
	ddi_put16((dp)->regs_handle, \
		(uint16_t *)((caddr_t)((dp)->base_addr) + (p)), v)
#define	OUTL(dp, p, v)	\
	ddi_put32((dp)->regs_handle, \
		(uint32_t *)((caddr_t)((dp)->base_addr) + (p)), v)
#define	INB(dp, p)	\
	ddi_get8((dp)->regs_handle, \
		(uint8_t *)(((caddr_t)(dp)->base_addr) + (p)))
#define	INW(dp, p)	\
	ddi_get16((dp)->regs_handle, \
		(uint16_t *)(((caddr_t)(dp)->base_addr) + (p)))
#define	INL(dp, p)	\
	ddi_get32((dp)->regs_handle, \
		(uint32_t *)(((caddr_t)(dp)->base_addr) + (p)))

/*
 * For debugging
 */
#ifdef DEBUG_LEVEL
static int sfe_debug = DEBUG_LEVEL;
#define	DPRINTF(n, args)	\
	if (sfe_debug > (n)) cmn_err args
#else
#define	DPRINTF(n, args)
#endif

/*
 * Patchable parameters
 */
#define	PKT_BUF_SZ	P2ROUNDUP(ETHERMAX + ETHERFCSL, 32)

#define	TX_RING_SIZE	32
#if 1   /* tx block test */
#define	TX_BUF_SIZE	(TX_RING_SIZE/8)
#else
#define	TX_BUF_SIZE	(TX_RING_SIZE/2)
#endif
#define	RX_RING_SIZE	64
#define	MAXFRAGMENTS	(TX_RING_SIZE/4)
static int	sfe_tx_fragments = MAXFRAGMENTS;

/*
 * Useful macros
 */
#define	OUR_INTR_BITS	\
	(ISR_RXSOVR | ISR_HIBERR | ISR_TXURN | ISR_TXIDLE | ISR_TXERR |	\
	 ISR_RXORN | ISR_RXOK | ISR_RXERR)

#define	OUR_INTR_BITS_SIS900	\
	 (OUR_INTR_BITS | ISR_PAUSE_END | ISR_PAUSE_ST)

#define TX_TIMEOUT		(drv_usectohz(5*1000000))
#define TX_TIMEOUT_INTERVAL	(drv_usectohz(1*1000000))
#define LINK_WATCH_INTERVAL	(drv_usectohz(1*1000000))	/* 1 sec */

#define	SLOT(seqnum, size)	(((unsigned int)(seqnum)) & ((size)-1))

#define	PCI_ANY_ID	0xffff

struct chip_info {
	uint16_t	venid;
	uint16_t	devid;
	char		*chip_name;
	int		chip_type;
#define	CHIPTYPE_DP83815	0
#define	CHIPTYPE_SIS900		1
	boolean_t	(*chip_info_init)();
};

/* IEEE802.3x mac control frame for flow controi */
struct pause_frame {
	struct ether_addr	dest;
	struct ether_addr	src;
	uint16_t	type_len;
	uint16_t	pause_flag;
	uint16_t	pause_time;
};

struct sfe_stats {
	uint32_t	intr;

	uint32_t	crc;
	uint32_t	errrcv;
	uint32_t	overflow;
	uint32_t	frame;
	uint32_t	missed ;
	uint32_t	runt;
	uint32_t	frame_too_long;
	uint32_t	norcvbuf;

	uint32_t	collisions;
	uint32_t	first_coll;
	uint32_t	multi_coll;
	uint32_t	collisions16;
	uint32_t	excoll;
	uint32_t	nocarrier;
	uint32_t	defer;
	uint32_t	errxmt;
	uint32_t	underflow;
	uint32_t	xmtlatecoll;
};


#define	SFE_LOCAL_BUF_INIT	(RX_RING_SIZE*2)
#ifdef RX_NOBUF_TEST
#define	SFE_LOCAL_BUF_MAX	(RX_RING_SIZE*3)
#else
#define	SFE_LOCAL_BUF_MAX	64*1024
#endif
/* local buffer management */
struct lbuf {
	struct lbuf		*next;
	ddi_dma_handle_t	dma_handle;
	ddi_acc_handle_t	acc_handle;
	caddr_t			buf;	
	size_t			buf_len;
#ifdef ALWAYS_MAPPED
	uint32_t		dma_addr;
#endif
	frtn_t			frtn;
	struct sfe_dev		*devp;
};

#define	SFEMAXMC		GLD_MAX_MULTICAST
#define	SFEMCALLOC		(sizeof(struct ether_addr) * SFEMAXMC)

typedef	long		seqnum_t;	/* should be signed */

#define	SUB(x, y)	((seqnum_t)((x) - (y)))

struct sfe_dev {
	/*
	 * Address of registers
	 */
	dev_info_t		*dip;
	gld_mac_info_t		*macinfo;
	char			name[32];
	void			*base_addr;
	ddi_acc_handle_t	regs_handle;
	ddi_iblock_cookie_t	iblock_cookie;

	/* MAC address information */
	struct ether_addr	cur_addr;
	struct ether_addr	dev_addr;

	/* Descriptor rings and buffers */
	struct sfe_desc		*rx_desc;
	struct sfe_desc		*tx_desc;
	uint32_t		rx_desc_dma;	/* dma address from PCI bus */
	uint32_t		tx_desc_dma;	/* dma address from PCI bus */
	ddi_dma_handle_t	desc_dma_handle;
	ddi_acc_handle_t	desc_acc_handle;
#ifdef TXSOFTPAD
	uint32_t		tx_pad_dma;
#endif
#ifdef RX_FLOW_CONTROL
	caddr_t			tx_pause_buf[2];
	uint32_t		tx_pause_dma[2];
#endif
	/* RX ring management */
	kmutex_t		intrlock;
	boolean_t		intr_busy;
	seqnum_t		rx_head;	/* hd of RX buffer ring */
	seqnum_t		rx_tail;	/* tail of RX buffer ring */
	boolean_t		rx_in_pause;
	boolean_t		rx_pause_request;
	struct lbuf		*rx_lbp[RX_RING_SIZE];
	int			rx_drain_threshold;

	/* TX ring management */
	kmutex_t		xmitlock;
	kcondvar_t		drain_cv;
	seqnum_t		tx_head;	/* hd of TX buffer ring */
	seqnum_t		tx_tail;	/* tail of TX buffer ring */
	void			*tx_bp[TX_RING_SIZE];
	uint8_t			tx_buf_type[TX_RING_SIZE];
#define		TX_BUF_INVALID	0
#define		TX_BUF_MBLK	1
#define		TX_BUF_LBUF	2
#define		TX_BUF_PAUSE	3

	ddi_dma_handle_t	tx_dma_handle_used[TX_RING_SIZE];
	int			tx_reserved;
	clock_t			tx_start_time;
	int			tx_busy;
	boolean_t		tx_blocked;
	int			tx_drain_threshold;
	int			tx_fill_threshold;

	/* timer and watchdog */
	timeout_id_t		timeout_id;

	/* nic state */
	boolean_t		nic_active;

	/* local buffer management */
	struct lbuf		*buf_free_list;
	kmutex_t		buflock;
	int			buf_allocated;
	int			buf_free;

	/* free dma handle management */
	kmutex_t		dma_handle_lock;
	int			dma_handle_free;
	ddi_dma_handle_t	dma_handle[TX_RING_SIZE];
#define		SFE_MAX_BUF	1000

	/* MII management */
	boolean_t		full_duplex;
	boolean_t		speed100;
	boolean_t		flow_control;
	int			mii_state;
#define		MII_STATE_RESETTING		0
#define		MII_STATE_AUTONEGOTIATING	1
#define		MII_STATE_LINKUP		2
#define		MII_STATE_LINKDOWN		3

	int			mii_timer;	/* in secound */
#define		MII_RESET_TIMEOUT	1
#define		MII_AUTONEGO_TIMEOUT	4
#define		MII_LINKDOWN_TIMEOUT	10

	boolean_t		mii_fixedmode;
	timeout_id_t		link_watcher_id;
	boolean_t		mii_supress_msg;
	uint32_t		mii_phyid;
	int			mii_phy_addr;

	uint16_t	(* mii_read_reg)(struct sfe_dev *, int);
	void		(* mii_write_reg)(struct sfe_dev *, int, uint16_t);
#define	mii_read(dp, off)	((dp)->mii_read_reg)(dp, off)
#define	mii_write(dp, off, v)	((dp)->mii_write_reg)(dp, off, v)

	/* RX filter mode and multicast list management */
	int			mc_count;
	struct ether_addr	*mc_list;
	int			rxmode;
#define		RXMODE_PROMISC	0x01
#define		RXMODE_ALLMULTI	0x02
	boolean_t		(*get_mac_addr)(struct sfe_dev *);
	void 			(*set_rx_filter)(struct sfe_dev *);
#define	sfe_set_rx_filter(dp)	((dp)->set_rx_filter)(dp)

	/* misc HW information */
	struct chip_info	*chip;
	uint32_t		our_intr_bits;
	uint8_t			revid;	/* revision from PCI configuration */
#ifdef TUNE_PHY_630
	uint8_t			bridge_revid;
#endif
	/* statistcs */
	struct sfe_stats	stats;
};

/* Private functions */
  /* MII */
static int sfe_mii_init(struct sfe_dev *);
static int sfe_mii_config(struct sfe_dev *dp);
static void sfe_mii_stop(struct sfe_dev *);
static void sfe_mii_link_watcher(struct sfe_dev *dp);

  /* register manupilation */
static uint16_t sfe_read_eeprom(struct sfe_dev *dp, int offset);
static int sfe_set_media(struct sfe_dev *dp);

  /* get mac address */
static boolean_t sfe_get_mac_addr_conf(struct sfe_dev *dp);

static int sfe_reset_chip(struct sfe_dev *);
static void sfe_init_chip(struct sfe_dev *dp);
static void sfe_start_chip(struct sfe_dev *dp);

  /* chip dependant routines */
static boolean_t sfe_chipinfo_init_dp83815(struct sfe_dev *dp);
static boolean_t sfe_chipinfo_init_sis900(struct sfe_dev *dp);

static struct lbuf *sfe_get_lbuf(struct sfe_dev *dp, int cansleep);
static ddi_dma_handle_t sfe_get_dma_handle(struct sfe_dev *dp);
static void sfe_free_dma_handle(struct sfe_dev *dp, ddi_dma_handle_t dh);

static void sfe_tx_timeout(struct sfe_dev *);

static void sfe_init_tx_desc(struct sfe_dev *);
static void sfe_init_rx_desc(struct sfe_dev *);
static void sfe_clean_tx_desc(struct sfe_dev *);
static void sfe_clean_rx_desc(struct sfe_dev *);

static int sfe_alloc_memory(struct sfe_dev *dp);
static void sfe_free_memory(struct sfe_dev *dp);

static void sfe_reclaim_rxbuf(struct lbuf *lbp);
static void sfe_transmit_done(struct sfe_dev *dp);

/* DDI/DKI functions */
static int sfeattach(dev_info_t *, ddi_attach_cmd_t);
static int sfedetach(dev_info_t *, ddi_detach_cmd_t);

/* GLD interfaces */
static int sfe_reset(gld_mac_info_t *);
static int sfe_start(gld_mac_info_t *);
static int sfe_stop(gld_mac_info_t *);
static int sfe_set_mac_address(gld_mac_info_t *, unsigned char *);
static int sfe_set_multicast(gld_mac_info_t *, struct ether_addr *, int);
static int sfe_set_promiscuous(gld_mac_info_t *, int);
static int sfe_get_stats(gld_mac_info_t *, struct gld_stats *);
static int sfe_send(gld_mac_info_t *, mblk_t *);
static u_int sfe_interrupt(gld_mac_info_t *);

/*
 * Hardware information
 */
struct chip_info chiptbl[] = {
#ifdef CONFIG_SIS900
 {
	0x1039,	0x0900,	"SiS900", CHIPTYPE_SIS900, sfe_chipinfo_init_sis900,
 },
#endif
#ifdef CONFIG_DP83815
 {
	0x100b,	0x0020,	"DP83815", CHIPTYPE_DP83815, sfe_chipinfo_init_dp83815,
 },
#endif
#ifdef CONFIG_SIS7016
 {
	0x1039,	0x7016,	"SiS7016", CHIPTYPE_SIS900, sfe_chipinfo_init_sis900,
 },
#endif
};
#define	CHIPTABLESIZE	(sizeof(chiptbl)/sizeof(struct chip_info))


/* Data access requirements. */
static struct ddi_device_acc_attr dev_attr = {
	DDI_DEVICE_ATTR_V0,
	DDI_STRUCTURE_LE_ACC,
	DDI_STRICTORDER_ACC
};


/* On sparc, the buffers should be native endianness */
static struct ddi_device_acc_attr buf_attr = {
	DDI_DEVICE_ATTR_V0,
	DDI_NEVERSWAP_ACC,	/* native endianness */
	DDI_STRICTORDER_ACC
};

static ddi_dma_attr_t dma_attr = {
	DMA_ATTR_V0,				/* dma_attr_version */
	0ULL,					/* dma_attr_addr_lo */
	0xffffffffULL,				/* dma_attr_addr_hi */
	0xffffffffULL,				/* dma_attr_count_max */
	32/*4*/,				/* dma_attr_align */
	0xffffffff,				/* dma_attr_burstsizes */
	1,					/* dma_attr_minxfer */
	0xffffffffULL,				/* dma_attr_maxxfer */
	0xffffffffULL,				/* dma_attr_seg */
	MAXFRAGMENTS,				/* dma_attr_sgllen */
	1,					/* dma_attr_granular */
	0					/* dma_attr_flags */
};

/*
 * Dma attribute to allocate physically continuous memory
 */
static ddi_dma_attr_t dma_attr_nosc = {
	DMA_ATTR_V0,				/* dma_attr_version */
	0ULL,					/* dma_attr_addr_lo */
	0xffffffffULL,				/* dma_attr_addr_hi */
	0xffffffffULL,				/* dma_attr_count_max */
	4,					/* dma_attr_align */
	0xffffffff,				/* dma_attr_burstsizes */
	1,					/* dma_attr_minxfer */
	0xffffffffULL,				/* dma_attr_maxxfer */
	0xffffffffULL,				/* dma_attr_seg */
	1,					/* dma_attr_sgllen */
	1,					/* dma_attr_granular */
	0					/* dma_attr_flags */
};

/*
 * Ethernet broadcast address definition.
 */
static	struct ether_addr	etherbroadcastaddr = {
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff
};

static struct ether_addr	sfe_pause_mac_addr = {
	0x01, 0x80, 0xc2, 0x00, 0x00, 0x01
};

static	struct module_info sfeminfo = {
	0,			/* mi_idnum */
	"sfe",			/* mi_idname */
	0,			/* mi_minpsz */
	ETHERMTU,		/* mi_maxpsz */
	32*1024,		/* mi_hiwat */
	1,			/* mi_lowat */
};

static	struct qinit sferinit = {
	(int (*)()) NULL,	/* qi_putp */
	gld_rsrv,		/* qi_srvp */
	gld_open,		/* qi_qopen */
	gld_close,		/* qi_qclose */
	(int (*)()) NULL,	/* qi_qadmin */
	&sfeminfo,		/* qi_minfo */
	NULL			/* qi_mstat */
};

static	struct qinit sfewinit = {
	gld_wput,		/* qi_putp */
	gld_wsrv,		/* qi_srvp */
	(int (*)()) NULL,	/* qi_qopen */
	(int (*)()) NULL,	/* qi_qclose */
	(int (*)()) NULL,	/* qi_qadmin */
	&sfeminfo,		/* qi_minfo */
	NULL		/* qi_mstat */
};

static struct streamtab	sfe_info = {
	&sferinit,	/* st_rdinit */
	&sfewinit,	/* st_wrinit */
	NULL,		/* st_muxrinit */
	NULL		/* st_muxwrinit */
};

static	struct cb_ops cb_sfe_ops = {
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
	&sfe_info,	/* cb_stream */
	D_NEW|D_MP	/* cb_flag */
};

static	struct dev_ops sfe_ops = {
	DEVO_REV,	/* devo_rev */
	0,		/* devo_refcnt */
	gld_getinfo,	/* devo_getinfo */
	nulldev,	/* devo_identify */
	nulldev,	/* devo_probe */
	sfeattach,	/* devo_attach */
	sfedetach,	/* devo_detach */
	nodev,		/* devo_reset */
	&cb_sfe_ops,	/* devo_cb_ops */
	NULL,		/* devo_bus_ops */
	ddi_power	/* devo_power */
};

static struct modldrv modldrv = {
	&mod_driverops,	/* Type of module.  This one is a driver */
	ident,
	&sfe_ops,	/* driver ops */
};

static struct modlinkage modlinkage = {
	MODREV_1, &modldrv, NULL
};

/*
 * _init : done
 */
int
_init(void)
{
	int 	status;

	DPRINTF(2, (CE_CONT, "sfe: _init: called"));
	status = mod_install(&modlinkage);
	return status;
}

/*
 * _fini : done
 */
int
_fini(void)
{
	int	status;

	DPRINTF(2, (CE_CONT, "sfe: _fini: called"));
	status = mod_remove(&modlinkage);
	return (status);
}

int
_info(struct modinfo *modinfop)
{
	return (mod_info(&modlinkage, modinfop));
}

/*
 * Probe for device.: Not needed
 */

/*
 * Interface exists: make available by filling in network interface
 * record.  System will initialize the interface when it is ready
 * to accept packets.
 */
static int
sfeattach(dev_info_t *dip, ddi_attach_cmd_t cmd)
{
	struct sfe_dev	*dp;
	int			i;
	ddi_iblock_cookie_t	c;
	ddi_acc_handle_t	conf_handle;
	uint16_t		comm;
	gld_mac_info_t		*macinfo;
	int			ret;
	int			vid;
	int			did;
	int			svid;
	int			sdid;
	int			unit;
	struct chip_info	*p;
	char			valstr[32];
	char			propname[32];
	int			val;
	int			len;
	struct pci_phys_spec	*regs;

	DPRINTF(2, (CE_CONT, "sfeattach: called"));

	if (cmd == DDI_ATTACH) {
		DPRINTF(2, (CE_CONT, "sfeattach: called cmd:ATTACH"));
	
		macinfo = gld_mac_alloc(dip);
		if (macinfo == NULL) {
			return DDI_FAILURE;
		}

		/*
		 * Allocate soft data structure
		 */
		dp = (struct sfe_dev *)
			kmem_zalloc(sizeof(*dp) + SFEMCALLOC, KM_SLEEP);
		if (dp == NULL) {
			gld_mac_free(macinfo);
			return DDI_FAILURE;
		}
		dp->mc_count = 0;
		dp->mc_list = (struct ether_addr *) &dp[1];
		dp->dip = dip;
		dp->macinfo = macinfo;
		unit = ddi_get_instance(dip);
		sprintf(dp->name, "%s%d", ddi_driver_name(dip), unit);

		/* GLD ver2 don't lock on xmit */
		macinfo->gldm_devinfo	   = dip;
		macinfo->gldm_private	   = (caddr_t)dp;

		macinfo->gldm_reset        = sfe_reset;
		macinfo->gldm_start        = sfe_start;
		macinfo->gldm_stop         = sfe_stop;
		macinfo->gldm_set_mac_addr = sfe_set_mac_address;
		macinfo->gldm_send         = sfe_send;
		macinfo->gldm_set_promiscuous = sfe_set_promiscuous;
		macinfo->gldm_get_stats    = sfe_get_stats;
		macinfo->gldm_ioctl        = NULL; 
		macinfo->gldm_set_multicast= sfe_set_multicast;
		macinfo->gldm_intr         = sfe_interrupt;
		macinfo->gldm_mctl         = NULL;

		macinfo->gldm_ident   = ident;
		macinfo->gldm_type    = DL_ETHER;
		macinfo->gldm_minpkt  = 0;
		macinfo->gldm_maxpkt  = ETHERMTU;
		macinfo->gldm_addrlen = ETHERADDRL;
		macinfo->gldm_saplen  = -2;
		macinfo->gldm_ppa     = unit;


		/*
		 * Get iblock cookie
		 */
		if (ddi_get_iblock_cookie(dip, 0, &c) != DDI_SUCCESS) {
			cmn_err(CE_CONT,
				"sfeattach: ddi_get_iblock_cookie: failed");
			goto err_free_private;
		}

		/*
		 * Initialize mutex's for this device.
		 */
		dp->iblock_cookie = c;
		macinfo->gldm_cookie = c;

		mutex_init(&dp->intrlock, NULL, MUTEX_DRIVER, (void *)c);
		mutex_init(&dp->xmitlock, NULL, MUTEX_DRIVER, (void *)c);
		mutex_init(&dp->buflock, NULL, MUTEX_DRIVER, (void *)c);
		mutex_init(&dp->dma_handle_lock, NULL, MUTEX_DRIVER, (void *)c);
		cv_init(&dp->drain_cv, NULL, CV_DRIVER, NULL);

		/*
		 * Map in the device registers into I/O space.
		 */
		/* Search IO-range */
		regs = NULL;
		len  = 0;
		if (ddi_getlongprop(DDI_DEV_T_ANY, dip, DDI_PROP_DONTPASS,
			"reg", (caddr_t)&regs, &len) != DDI_PROP_SUCCESS) {
			cmn_err(CE_WARN,
				"%s: failed to get reg property", dp->name);
			goto err_free_private;
		}

		ASSERT(regs != NULL && len > 0);
#if DEBUG_LEVEL > 0
		for (i = 0; i <len / sizeof(struct pci_phys_spec); i++) {
			DPRINTF(0, (CE_CONT,
				"?%s: regs[%d]: %08x.%08x.%08x.%08x.%08x",
				dp->name, i,
				regs[i].pci_phys_hi,
				regs[i].pci_phys_mid,
				regs[i].pci_phys_low,
				regs[i].pci_size_hi,
				regs[i].pci_size_low));
		}
#endif
		for (i = 0; i <len / sizeof(struct pci_phys_spec); i++) {
			if ((regs[i].pci_phys_hi & PCI_REG_ADDR_M) == 
			    PCI_ADDR_IO) {
				kmem_free(regs, len);
				goto io_range_found;
			}
		}
		cmn_err(CE_WARN, "%s: failed to find IO space", dp->name);
		kmem_free(regs, len);
		goto err_free_private;

io_range_found:
		if (ddi_regs_map_setup(dip, i, (caddr_t *)&dp->base_addr,
			0, 0, &dev_attr, &dp->regs_handle)) {
			cmn_err(CE_WARN, "%s: ddi_regs_map_setup failed",
				dp->name);
			goto err_free_locks;
		}

		/*
		 * Make sure the I/O access and memory access, master enable.
		 * Bits are set in the config command register
		 */
		if (pci_config_setup(dip, &conf_handle) != DDI_SUCCESS) {
			cmn_err(CE_WARN, "%s: ddi_regs_map_setup failed",
				dp->name);
			goto err_free_regs;
		}
		vid  = pci_config_get16(conf_handle, PCI_CONF_VENID);
		did  = pci_config_get16(conf_handle, PCI_CONF_DEVID);
		svid = pci_config_get16(conf_handle, PCI_CONF_SUBVENID);
		sdid = pci_config_get16(conf_handle, PCI_CONF_SUBSYSID);
		dp->revid = pci_config_get8(conf_handle, PCI_CONF_REVID);
#ifdef DEBUG_SIS630ET
		dp->revid = SIS630ET_900_REV;
#endif
		comm = pci_config_get16(conf_handle, PCI_CONF_COMM);
		comm |= PCI_COMM_IO | PCI_COMM_ME;
		pci_config_put16(conf_handle, PCI_CONF_COMM, comm);

		pci_config_teardown(&conf_handle);

		/* initialize chip */
		for (i=0, p=chiptbl; i<CHIPTABLESIZE; i++, p++) {

			if ((p->venid == vid && p->devid == did) ||
			    (p->venid == svid && p->devid == sdid)) {
				/* found */
				goto chip_found;
			}
		}
		/* chip not found */
		cmn_err(CE_WARN, "%s: attach: error: "
			"Unknown PCI venid/devid (0x%x, 0x%x) rev:0x%x",
				dp->name, vid, did, dp->revid);
		goto err_free_regs;
chip_found:
		/* reset chip */
		dp->chip = p;
		if (!(*p->chip_info_init)(dp)) {
			goto err_free_regs;
		}

		cmn_err(CE_CONT, "?%s: nic chip is %s rev:0x%x",
			dp->name, dp->chip->chip_name, dp->revid);

		if (sfe_reset_chip(dp) != 0) {
			cmn_err(CE_WARN, "%s: sfeattach: reset chip failed.",
				dp->name);
			goto err_free_regs;
		}
		DPRINTF(3, (CE_CONT, "%s: reset done", dp->name));

		dp->rxmode  = 0;
		dp->mii_fixedmode = FALSE;
		dp->full_duplex = FALSE;
		dp->flow_control= FALSE;

		sprintf(propname, "sfe%d-duplex", unit);
		len = sizeof(valstr);
		if ((ddi_getlongprop_buf(DDI_DEV_T_ANY, dp->dip,
                                DDI_PROP_DONTPASS, propname, valstr,
                                &len)) == DDI_PROP_SUCCESS) {
			dp->mii_fixedmode = TRUE;
			if (strcmp(valstr, "full") == 0) {
				dp->full_duplex = TRUE;
				dp->flow_control = TRUE;
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

		sprintf(propname, "sfe%d-speed", unit);
		val = ddi_getprop(DDI_DEV_T_ANY, dp->dip, DDI_PROP_DONTPASS, propname, -1);
		if (val != -1)  {
			dp->mii_fixedmode = TRUE;
			if (val == 100) {
				dp->speed100 = TRUE;
			}
			else if (val == 10) {
				dp->speed100 = FALSE;
			}
			else {
				cmn_err(CE_WARN,
					"%s: property %s: illegal value (%d)",
					dp->name, propname, val);
			}
		}

		sprintf(propname, "sfe%d-flow-control", unit);
		val = ddi_getprop(DDI_DEV_T_ANY, dp->dip, DDI_PROP_DONTPASS, propname, -1);
		if (val != -1) {
			if (val == 1) {
				dp->flow_control = TRUE;
			}
			else if (val == 0) {
				dp->flow_control = FALSE;
			}
			else {
				cmn_err(CE_WARN,
					"%s: property %s: illegal value (%d)",
					dp->name, propname, val);
			}
		}

		/* read MAC address */
		if (!sfe_get_mac_addr_conf(dp)) {
			if (!((dp->get_mac_addr)(dp))) {
				cmn_err(CE_WARN,
					"%s: cannot get mac address", dp);
				goto err_free_regs;
			}
		}
		cmn_err(CE_CONT,
			"?%s: %s at 0x%p, %02x:%02x:%02x:%02x:%02x:%02x",
			dp->name, dp->chip->chip_name,
			(long)dp->base_addr,
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

		/* allocate tx and rx resources */
		if (sfe_alloc_memory(dp) != 0) {
			goto err_free_regs;
		}

		/* Init MII */
		if (sfe_mii_init(dp) != 0) {
			goto err_free_desc;
		}

		/*
		 * Add interrupt to system.
		 */
		if (gld_register(dip, "sfe", macinfo) != DDI_SUCCESS) {
			goto err_free_desc;
		}

		if (ddi_add_intr(dip, 0, NULL, NULL, gld_intr,
					(caddr_t)macinfo) != DDI_SUCCESS) {
			ddi_regs_map_free(&dp->regs_handle);
			cmn_err(CE_WARN, "%s: ddi_add_intr failed", dp->name);
			goto err_unregister;
		}

		DPRINTF(2, (CE_CONT, "sfeattach: return: successed"));
		return DDI_SUCCESS;
err_free_intr:
		/* release allocated resource */
		(void) ddi_remove_intr(dip, 0, c);
err_unregister:
		gld_unregister(macinfo);
err_free_desc:
		sfe_free_memory(dp);
err_free_regs:
		ddi_regs_map_free(&dp->regs_handle);
err_free_locks:
		mutex_destroy(&dp->intrlock);
		mutex_destroy(&dp->xmitlock);
		mutex_destroy(&dp->buflock);
		mutex_destroy(&dp->dma_handle_lock);
		cv_destroy(&dp->drain_cv);
err_free_private:
		kmem_free((caddr_t)dp,
			sizeof(struct sfe_dev) + SFEMCALLOC);
		gld_mac_free(macinfo);

		return DDI_FAILURE;
	}

	if (cmd == DDI_RESUME) {
		/* start mii */
		if (sfe_mii_init(dp) != 0) {
			return DDI_FAILURE;
		}

		mutex_enter(&dp->intrlock);
		mutex_enter(&dp->xmitlock);

		/* construct descriptor rings */
		sfe_init_tx_desc(dp);
		sfe_init_rx_desc(dp);

		/* setup hardware */
		sfe_init_chip(dp);

		/* setup Rx filter and mac address */
		sfe_set_rx_filter(dp);

		/* start chip */
		dp->nic_active = TRUE;
		sfe_start_chip(dp);

		mutex_exit(&dp->xmitlock);
		mutex_exit(&dp->intrlock);

		/* start tx timeout watcher */
		dp->timeout_id = timeout((void (*)(void *))sfe_tx_timeout,
					(void *)dp, TX_TIMEOUT_INTERVAL);

		return DDI_SUCCESS;
	}

	return DDI_FAILURE;
}

static int
sfedetach(dev_info_t *dip, ddi_detach_cmd_t cmd)
{
	int		i;
	struct sfe_dev *dp;
	gld_mac_info_t	*macinfo;

	if (cmd == DDI_DETACH) {
		macinfo = (gld_mac_info_t *)ddi_get_driver_private(dip);
		dp = (struct sfe_dev *)macinfo->gldm_private;

                /* ensure all rx buffers are free */
		if (dp->buf_allocated != dp->buf_free) {
			/*
			 * some resource is busy
			 */
			cmn_err(CE_NOTE,
			"!%s: sfedetach: some buffer are busy (a:%d, f:%d)",
				dp->name, dp->buf_allocated, dp->buf_free);
			return DDI_FAILURE;
		}

		/*
		 * stop the device
		 */
		sfe_mii_stop(dp);
		sfe_reset_chip(dp);

		/*
		 * unregister interrupt handler
		 */
		ddi_remove_intr(dip, 0, dp->iblock_cookie);

		(void)gld_unregister(macinfo);

		sfe_free_memory(dp);

		/*
		 * Release mapping resources
		 */
		ddi_regs_map_free(&dp->regs_handle);

		mutex_destroy(&dp->xmitlock);
		mutex_destroy(&dp->intrlock);
		mutex_destroy(&dp->buflock);
		mutex_destroy(&dp->dma_handle_lock);
		cv_destroy(&dp->drain_cv);

		/*
		 * Release memory and mapping resources
		 */
		kmem_free((caddr_t)dp, sizeof(struct sfe_dev) + SFEMCALLOC);
		gld_mac_free(macinfo);

		DPRINTF(2, (CE_CONT, "%s: sfedetach: return: success",
			dp->name));

		return DDI_SUCCESS;
	}

	if (cmd == DDI_SUSPEND) {
		timeout_id_t	old_id;

		/* stop tx timeout watcher */
		if (dp->timeout_id) {
			do {
				untimeout(old_id = dp->timeout_id);
			} while (dp->timeout_id != old_id);
			dp->timeout_id = 0;
		}

		/* stop the chip */
		mutex_enter(&dp->intrlock);
		mutex_enter(&dp->xmitlock);

		dp->nic_active = FALSE;

		/* Inhibit interrupt */
		OUTL(dp, IER, 0);

		/* stop TX and RX immediately */
		OUTL(dp, CR, CR_TXR | CR_RXR);

		/* Stop chip core */

		/* Release unused TX and RX buffers */
		sfe_clean_tx_desc(dp);
		sfe_clean_rx_desc(dp);

		mutex_exit(&dp->xmitlock);
		mutex_exit(&dp->intrlock);

		/* stop mii_watcher */
		sfe_mii_stop(dp);

		return DDI_SUCCESS;
	}

	return DDI_FAILURE;
}

/*
 * GLD interface routines
 */

static int
sfe_reset(gld_mac_info_t *macinfo)
{
	struct sfe_dev *dp;

	dp = (struct sfe_dev *)macinfo->gldm_private;

	mutex_enter(&dp->intrlock);
	mutex_enter(&dp->xmitlock);

	/* construct descriptor rings */
	sfe_init_tx_desc(dp);
	sfe_init_rx_desc(dp);

	/* setup hardware */
	sfe_init_chip(dp);

	mutex_exit(&dp->xmitlock);
	mutex_exit(&dp->intrlock);

	return GLD_SUCCESS;
}

static int
sfe_set_mac_address(gld_mac_info_t *macinfo, unsigned char *addr)
{
	struct sfe_dev *dp;
	int	i;

	dp = (struct sfe_dev *)macinfo->gldm_private;
	bcopy((void *)addr,
		dp->cur_addr.ether_addr_octet, ETHERADDRL);

	mutex_enter(&dp->intrlock);
	sfe_set_rx_filter(dp);
	mutex_exit(&dp->intrlock);

	return GLD_SUCCESS;
}

static int
sfe_start(gld_mac_info_t *macinfo)
{
	struct sfe_dev *dp;

	dp = (struct sfe_dev *)macinfo->gldm_private;

	mutex_enter(&dp->intrlock);
	mutex_enter(&dp->xmitlock);

	dp->nic_active = TRUE;
	sfe_start_chip(dp);

	mutex_exit(&dp->xmitlock);
	mutex_exit(&dp->intrlock);

	dp->timeout_id = timeout((void (*)(void *))sfe_tx_timeout,
				(void *)dp, TX_TIMEOUT_INTERVAL);

	return GLD_SUCCESS;
}

static int
sfe_stop(gld_mac_info_t *macinfo)
{
	timeout_id_t	old_id;
	struct sfe_dev *dp;
	int		i;

	dp = (struct sfe_dev *)macinfo->gldm_private;

	/* stop tx timeout watcher */
	if (dp->timeout_id) {
		do {
			untimeout(old_id = dp->timeout_id);
		} while (dp->timeout_id != old_id);
		dp->timeout_id = 0;
	}

	mutex_enter(&dp->intrlock);
	mutex_enter(&dp->xmitlock);

	dp->nic_active = FALSE;

	/* Inhibit interrupt */
	OUTL(dp, IER, 0);

	/* stop TX and RX immediately */
	OUTL(dp, CR, CR_TXR | CR_RXR);

	/* Stop chip core */

	/* Release unused TX and RX buffers */
	sfe_clean_tx_desc(dp);
	sfe_clean_rx_desc(dp);

	mutex_exit(&dp->xmitlock);
	mutex_exit(&dp->intrlock);

	return GLD_SUCCESS;
}

static int
sfe_set_multicast(gld_mac_info_t *macinfo, struct ether_addr *ep, int flag)
{
	struct sfe_dev	*dp;
	size_t			len;
	int			i;
	int			cnt;

	dp = (struct sfe_dev *)macinfo->gldm_private;

	cnt = dp->mc_count;

	if (flag == GLD_MULTI_ENABLE) {
		/* append new addess into mclist */
		if (cnt >= SFEMAXMC) {
			return GLD_FAILURE;
		}
		bcopy(ep, &dp->mc_list[cnt], sizeof(struct ether_addr));
		dp->mc_count++;
	}
	else {
		if (cnt == 0) {
			return GLD_FAILURE;
		}
		for (i=0; i<cnt; i++) {
			if (bcmp(ep, &dp->mc_list[i],
					sizeof(struct ether_addr)) == 0) {
				goto found;
			}
		}
		return GLD_FAILURE;
found:
		/* squeeze mclist by copying forward */
		len = (cnt - (i + 1)) * sizeof(struct ether_addr);
		if (len > 0) {
			bcopy(&dp->mc_list[i+1], &dp->mc_list[i], len);
		}
		dp->mc_count--;
	}

	mutex_enter(&dp->intrlock);
	sfe_set_rx_filter(dp);
	mutex_exit(&dp->intrlock);

	return GLD_SUCCESS;
}

static int
sfe_set_promiscuous(gld_mac_info_t *macinfo, int flag)
{
	struct sfe_dev *dp;

	dp = (struct sfe_dev *)macinfo->gldm_private;


	if (flag == GLD_MAC_PROMISC_NONE) {
		dp->rxmode &= ~(RXMODE_PROMISC|RXMODE_ALLMULTI);
	}
	else if (flag == GLD_MAC_PROMISC_MULTI) {
		dp->rxmode |= RXMODE_ALLMULTI;
	}
	else {
		dp->rxmode |= RXMODE_PROMISC;
	}

	mutex_enter(&dp->intrlock);
	sfe_set_rx_filter(dp);
	mutex_exit(&dp->intrlock);

	return GLD_SUCCESS;
}

static	int
sfe_get_stats(gld_mac_info_t *macinfo, struct gld_stats *gs)
{
	struct sfe_dev	*dp;
	struct sfe_stats	*vs;

	dp = (struct sfe_dev *)macinfo->gldm_private;

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
	gs->glds_speed     = dp->speed100 ? 100000000: 10000000;
	gs->glds_media     = GLDM_TP;
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

static int
sfe_send(gld_mac_info_t *macinfo, mblk_t *mp)
{
	struct sfe_dev	*dp;
	mblk_t			*mp0;
	ddi_dma_cookie_t	dmacookie[MAXFRAGMENTS];
	ddi_dma_handle_t	dh[MAXFRAGMENTS];
	int			n;
	int			i;
	size_t			len;
	unsigned		slot;
	struct lbuf		*lbp = NULL;
	int			frags;
	int			docopy;
	int			err;
	int			ret;
	struct sfe_desc		*tdp;

	dp = (struct sfe_dev *)macinfo->gldm_private;

	DPRINTF(2, (CE_CONT, "sfe_send: called"));

	bzero(dmacookie, sizeof(dmacookie));

	/* calculate packet size and check number of fragments */
	docopy  = FALSE;
	len = 0;
	frags   = 0;
	for (mp0 = mp; mp0; mp0 = mp0->b_cont) {
		long	l0, l1;

		l1 = mp0->b_wptr - mp0->b_rptr;
		len += l1;
		frags++;
#ifdef i386
		l0 = min(l1, PAGESIZE - ((long)mp0->b_rptr & PAGEOFFSET));
		l1 = l1 - l0;

		if (l1 > 0) {
			frags++;
		}
#endif
#ifdef SIS900_TXOVERRUN
		if (l0 < 32) {
			/* check possibility of txoverrun */
			docopy = TRUE;
		}
#endif
	}
	ASSERT(len == msgdsize(mp));

	if (len > ETHERMAX) {
		cmn_err(CE_CONT, "msg too big:  %d", len);

		/* Do not free mp here, GLD will free it */
		return GLD_NOTSUPPORTED;
	}

#ifdef TXSOFTPAD
	if (len < ETHERMIN) {
		frags++;
	}
#endif

	if (frags > sfe_tx_fragments) {
		docopy = TRUE;
		frags = 1;
	}

	/* check required resources */
	mutex_enter(&dp->xmitlock);
	if (!dp->nic_active) {
		dp->tx_blocked = TRUE;
		mutex_exit(&dp->xmitlock);
		return GLD_FAILURE;
	}

	if ((TX_RING_SIZE - 2) - SUB(dp->tx_tail, dp->tx_head)
					- dp->tx_reserved < frags) {
		/* No transmit descriptor, free transmitted slots */
		sfe_transmit_done(dp);

		/* Check again */
		if (TX_RING_SIZE - SUB(dp->tx_tail, dp->tx_head)
					- dp->tx_reserved < frags) {

			dp->tx_blocked = TRUE;
			mutex_exit(&dp->xmitlock);
			/* no resources, try later */
			return GLD_NORESOURCES;
		}
	}
	dp->tx_blocked = FALSE;
	dp->tx_reserved += frags;
	dp->tx_busy++;
	mutex_exit(&dp->xmitlock);

	err = GLD_SUCCESS;

	if (docopy) {
		caddr_t			bp;
#ifndef ALWAYS_MAPPED
		uint_t			count;
#endif
#ifdef DEBUG
		dp->stats.xmtlatecoll++;
#endif
		/* Must use local buffer. */
		if ((lbp = sfe_get_lbuf(dp, FALSE)) == NULL) {
			/* no resource, try later */
			err = GLD_NORESOURCES;
			goto x;
		}

		/* copy payload from stream message to local buffer */
		bp = lbp->buf;
		for (mp0 = mp; mp0; mp0 = mp0->b_cont) {
			size_t	len;
			len = mp0->b_wptr - mp0->b_rptr;
			bcopy(mp0->b_rptr, bp, len);
			bp += len;
		}
		ASSERT(bp-lbp->buf == len);

		/* fix packet size for short packets */
		if (len < ETHERMIN) {
			bzero(bp, ETHERMIN - len);
			len = ETHERMIN;
		}

#ifdef ALWAYS_MAPPED
		ddi_dma_sync(lbp->dma_handle, (off_t)0,
				len, DDI_DMA_SYNC_FORDEV);
		dmacookie[0].dmac_address = lbp->dma_addr;
		dmacookie[0].dmac_size    = len;
#else
		if ((ret = ddi_dma_addr_bind_handle(
				lbp->dma_handle, NULL,
				lbp->buf, len,
				DDI_DMA_WRITE | DDI_DMA_STREAMING,
				DDI_DMA_DONTWAIT, NULL,
				&dmacookie[0], &count)) != DDI_DMA_MAPPED) {
			ASSERT(ret != DDI_DMA_INUSE);
			sfe_free_lbuf(lbp);
			lbp = NULL;	/* sanity */
			err = GLD_NORESOURCES;	/* mp will not be freed */
			goto x;
		}
		ASSERT(count == 1);
#endif /* ALWAYS_MAPPED */
		dh[0] = NULL;	/* Do not free dmahandle on TX completion */
		i     = 1;
		mp0   = mp;
		mp    = NULL;
	}
	else {
		/*
		 * prepare for direct transmit
		 */
		i = 0;
		for (mp0 = mp; mp0; mp0 = mp0->b_cont) {
			ddi_dma_handle_t	dma_handle;
			uint_t			count;
			size_t			len;

			len = mp0->b_wptr - mp0->b_rptr;
			dma_handle = sfe_get_dma_handle(dp);
			ASSERT(dma_handle != NULL);

			if ((ret = ddi_dma_addr_bind_handle(
				dma_handle, NULL,
				mp0->b_rptr, len,
				DDI_DMA_WRITE | DDI_DMA_STREAMING,
				DDI_DMA_DONTWAIT, NULL,
				&dmacookie[i], &count)) != DDI_DMA_MAPPED) {

				/* failed to bind dma resources */
				while (i--) {
					if ((dma_handle = dh[i]) == NULL) {
						continue;
					}
					ddi_dma_unbind_handle(dma_handle);
					sfe_free_dma_handle(dp, dma_handle);
				}
				err = GLD_NORESOURCES;
				break;
			}
			ASSERT(count == 1 || count == 2);
			dh[i++] = dma_handle;

			/* collect rest of dma cookies */
			while (--count > 0) {
				ddi_dma_nextcookie(dma_handle, &dmacookie[i]);
				ASSERT(dmacookie[i].dmac_size <= CMDSTS_SIZE);
				dh[i++] = NULL;
			}
		}
#ifdef TXSOFTPAD
		if (len < ETHERMIN) {
			/* add a pad fragment */
			dmacookie[i].dmac_address = dp->tx_pad_dma;
			dmacookie[i].dmac_size    = ETHERMIN - len;
			dh[i++] = NULL;
		}
#endif
	}
x:
#if DEBUG_LEVEL > 2
	if (i > 4) {
		cmn_err(CE_CONT,
"%s: sfe_send: frags:%d (%d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d)",
			dp->name, i,
			dmacookie[0].dmac_size, dmacookie[1].dmac_size,
			dmacookie[2].dmac_size, dmacookie[3].dmac_size,
			dmacookie[4].dmac_size, dmacookie[5].dmac_size,
			dmacookie[6].dmac_size, dmacookie[7].dmac_size,
			dmacookie[8].dmac_size, dmacookie[9].dmac_size,
			dmacookie[10].dmac_size, dmacookie[11].dmac_size,
			dmacookie[12].dmac_size, dmacookie[13].dmac_size,
			dmacookie[14].dmac_size, dmacookie[15].dmac_size);
	}
#endif
	mutex_enter(&dp->xmitlock);
	dp->tx_busy--;
	dp->tx_reserved -= frags;
	if (!dp->nic_active && dp->tx_busy == 0) {
		/* someone may wait for me */
		cv_broadcast(&dp->drain_cv);
	}

	if (err != GLD_SUCCESS || !dp->nic_active) {
		/* something wrong, no resources? */
		dp->tx_blocked = TRUE;
		if (err == GLD_SUCCESS) {
			err = GLD_FAILURE;
		}
		mutex_exit(&dp->xmitlock);
		return err;
	}

	/*
	 * write tx descriptor in reversed order, here:
	 *  i: actual used slots
	 */

	/* for the last slot of the packet */
	n = i - 1;
	slot = SLOT(dp->tx_tail + n, TX_RING_SIZE);
	if (docopy) {
		dp->tx_buf_type[slot] = TX_BUF_LBUF;
		dp->tx_bp[slot] = lbp;
	}
	else {
		dp->tx_buf_type[slot] = TX_BUF_MBLK;
		dp->tx_bp[slot] = mp;
	}
	dp->tx_dma_handle_used[slot] = dh[n];
	tdp = &dp->tx_desc[slot];
	tdp->d_bufptr = dmacookie[n].dmac_address;
	tdp->d_cmdsts = dmacookie[n].dmac_size | CMDSTS_OWN;

	while (n--) {
		/* slot for n-th fragment */
		slot = SLOT(dp->tx_tail + n, TX_RING_SIZE);

		dp->tx_dma_handle_used[slot] = dh[n];
		tdp = &dp->tx_desc[slot];
		tdp->d_bufptr = dmacookie[n].dmac_address;
		tdp->d_cmdsts = dmacookie[n].dmac_size
						| CMDSTS_OWN | CMDSTS_MORE;
	}

	DPRINTF(2, (CE_CONT,
		"%s: sfe_send: tx-ing a packet (seqnum %d-%d) using slot %d-%d",
		dp->name,
		dp->tx_tail, dp->tx_tail + i - 1,
		SLOT(dp->tx_tail, TX_RING_SIZE),
		SLOT(dp->tx_tail + i - 1, TX_RING_SIZE)));

	dp->tx_tail += i;

	/*
	 * Let the Transmit Buffer Manager Fill state machine active
	 */
	OUTL(dp, CR, CR_TXE);
	dp->tx_start_time = ddi_get_lbolt();

	mutex_exit(&dp->xmitlock);

	if (lbp != NULL) {
		/* local buffer is used instead of mp */
		freemsg(mp0);
	}

	return GLD_SUCCESS;
}

/* ========================================================================= */
/* 
 * Dma handle and Local buffer management
 */
/* ========================================================================= */

static ddi_dma_handle_t
sfe_get_dma_handle(struct sfe_dev *dp)
{
	ddi_dma_handle_t	dh;

	mutex_enter(&dp->dma_handle_lock);
	ASSERT(dp->dma_handle_free >= 0);
	if (dp->dma_handle_free == 0) {
		mutex_exit(&dp->dma_handle_lock);
		cmn_err(CE_PANIC,
			"%s: sfe_get_dma_handle: no dma handle resource",
			dp->name);
		return NULL;
	}
	dh = dp->dma_handle[--dp->dma_handle_free];
	mutex_exit(&dp->dma_handle_lock);

	return dh;
}

static void
sfe_free_dma_handle(struct sfe_dev *dp, ddi_dma_handle_t dh)
{
	mutex_enter(&dp->dma_handle_lock);
	ASSERT(dp->dma_handle_free < TX_RING_SIZE);
	dp->dma_handle[dp->dma_handle_free++] = dh;
	mutex_exit(&dp->dma_handle_lock);
	return;
}

static void
sfe_free_lbuf(struct lbuf *lbp)
{
	struct sfe_dev	*dp;

	dp = lbp->devp;

	mutex_enter(&dp->buflock);
	lbp->next = dp->buf_free_list;
	dp->buf_free_list = lbp;
	dp->buf_free++;
	mutex_exit(&dp->buflock);
}

static struct lbuf *
sfe_get_lbuf(struct sfe_dev *dp, int cansleep)
{
	struct lbuf		*lbp;
	ddi_dma_cookie_t	cookie;
	uint_t			count;
	int			err;

	mutex_enter(&dp->buflock);
	if ((lbp = dp->buf_free_list) != NULL) {
		dp->buf_free_list = lbp->next;
		dp->buf_free--;
		mutex_exit(&dp->buflock);
		return lbp;	
	}
	if (dp->buf_allocated >= SFE_LOCAL_BUF_MAX) {
		mutex_exit(&dp->buflock);
		return NULL;
	}
	dp->buf_allocated++;
	mutex_exit(&dp->buflock);

	lbp = (struct lbuf *) kmem_alloc(sizeof(struct lbuf),
				cansleep ? KM_SLEEP : KM_NOSLEEP);

	if (ddi_dma_alloc_handle(dp->dip,  &dma_attr_nosc, 
				cansleep ? DDI_DMA_SLEEP : DDI_DMA_DONTWAIT,
				NULL, &lbp->dma_handle) != DDI_SUCCESS) {
		kmem_free(lbp, sizeof(struct lbuf));
		return NULL;
	}

	if (ddi_dma_mem_alloc(lbp->dma_handle,
				PKT_BUF_SZ, &buf_attr,
				DDI_DMA_STREAMING,
				cansleep ? DDI_DMA_SLEEP : DDI_DMA_DONTWAIT,
				NULL,
				&lbp->buf, &lbp->buf_len,
				&lbp->acc_handle) != DDI_SUCCESS) {

		ddi_dma_free_handle(&lbp->dma_handle);
		kmem_free(lbp, sizeof(struct lbuf));
		return NULL;
	}
	ASSERT(lbp->buf_len >= ETHERMAX+ETHERFCSL);
#ifdef ALWAYS_MAPPED
	if ((err = ddi_dma_addr_bind_handle(lbp->dma_handle,
				NULL, lbp->buf, lbp->buf_len,
				DDI_DMA_RDWR | DDI_DMA_STREAMING,
				cansleep ? DDI_DMA_SLEEP : DDI_DMA_DONTWAIT,
				NULL,
				&cookie, &count)) != DDI_SUCCESS) {

		ASSERT(err != DDI_DMA_INUSE);

		ddi_dma_mem_free(&lbp->acc_handle);
		ddi_dma_free_handle(&lbp->dma_handle);
		kmem_free(lbp, sizeof(struct lbuf));
		return NULL;
	}
	ASSERT(count == 1);
	lbp->dma_addr = cookie.dmac_address;
#endif /* ALWAYS_MAPPED */
	lbp->devp = dp;
	lbp->frtn.free_func = (void (*)())&sfe_reclaim_rxbuf;
	lbp->frtn.free_arg  = (caddr_t) lbp;

	return lbp;
}

static int
sfe_alloc_memory(struct sfe_dev* dp)
{
	caddr_t			ring;
	size_t			ring_len;
	ddi_dma_cookie_t	cookie;
	uint_t			count;
	int			i;
	int			err;
	struct lbuf		*lbp, *head;
	caddr_t			bp;
	uint32_t		dma;

	/*
	 * Allocate RX/TX descriptors
	 */
	if ((err = ddi_dma_alloc_handle(dp->dip, &dma_attr_nosc,
			DDI_DMA_SLEEP,NULL,
			&dp->desc_dma_handle)) != DDI_SUCCESS) {
		cmn_err(CE_WARN,
			"%s: sfe_alloc_memory: ddi_dma_alloc_handle failed: %d",
			dp->name, err);
		return ENOMEM;
	}

	if ((err = ddi_dma_mem_alloc(dp->desc_dma_handle,
#ifdef TXSOFTPAD
				ETHERMIN +
#endif
#ifdef RX_FLOW_CONTROL
				ETHERMIN*2 +
#endif
				RX_RING_SIZE * sizeof(struct sfe_desc) +
				TX_RING_SIZE * sizeof(struct sfe_desc),
				&dev_attr,
				DDI_DMA_CONSISTENT, DDI_DMA_SLEEP, NULL,
				&ring, &ring_len,
				&dp->desc_acc_handle)) != DDI_SUCCESS) {
		cmn_err(CE_WARN,
			"%s: sfe_alloc_memory: ddi_dma_mem_alloc failed: %d",
			dp->name, err);
		ddi_dma_free_handle(&dp->desc_dma_handle);
		return ENOMEM;
	}

	if ((err = ddi_dma_addr_bind_handle(dp->desc_dma_handle,
				NULL, ring, ring_len,
				DDI_DMA_RDWR | DDI_DMA_CONSISTENT,
				DDI_DMA_SLEEP, NULL,
				&cookie, &count)) != DDI_SUCCESS) {
		ASSERT(err != DDI_DMA_INUSE);
		cmn_err(CE_WARN,
		"%s: sfe_alloc_memory: ddi_dma_addr_bind_handle failed: %d",
			dp->name, err);
		ddi_dma_mem_free(&dp->desc_acc_handle);
		ddi_dma_free_handle(&dp->desc_dma_handle);
		return ENOMEM;
	}
	ASSERT(count == 1);

	dp->rx_desc = (struct sfe_desc *)ring;
	dp->tx_desc = (struct sfe_desc *)
			(ring + RX_RING_SIZE * sizeof(struct sfe_desc));
	dp->rx_desc_dma = cookie.dmac_address;
	dp->tx_desc_dma = cookie.dmac_address
				+ RX_RING_SIZE * sizeof(struct sfe_desc);
#ifdef TXSOFTPAD
	bp = ((caddr_t)dp->tx_desc) + TX_RING_SIZE * sizeof(struct sfe_desc);
	bzero(bp, ETHERMIN);

	dp->tx_pad_dma = dp->tx_desc_dma
				+ TX_RING_SIZE * sizeof(struct sfe_desc);
#endif
#ifdef RX_FLOW_CONTROL
	bp += ETHERMIN;
	dma = dp->tx_pad_dma + ETHERMIN;
	for (i = 0; i < 2; i++, bp += ETHERMIN, dma += ETHERMIN) {

		/* set destination and source address */
		bcopy(sfe_pause_mac_addr.ether_addr_octet,
			((struct pause_frame *)bp)->dest.ether_addr_octet,
			 ETHERADDRL);
		bcopy(sfe_pause_mac_addr.ether_addr_octet,
			((struct pause_frame *)bp)->src.ether_addr_octet,
			ETHERADDRL);

		/* set type */
		((struct pause_frame *)bp)->type_len = htons(0x8808);

		/* set pause flag */
		((struct pause_frame *)bp)->pause_flag = htons(0x0001);

		/* pause time */
		if (i == 0) {
			/* short hand for pause-off */
			((struct pause_frame *)bp)->pause_time = htons(0x0000);
		} else {
			/* short hand for pause-on */
			((struct pause_frame *)bp)->pause_time = htons(0xffff);
		}

		/* clear reserved field */
		bzero(bp + sizeof(struct pause_frame),
			ETHERMIN - sizeof(struct pause_frame));

		dp->tx_pause_dma[i] = dma;
	}
#endif
	/*
	 * Allocate dma handle for each direct tx buffer.
	 */
	for (i = 0; i < TX_RING_SIZE; i++) {
		if ((err = ddi_dma_alloc_handle(dp->dip,
			&dma_attr, DDI_DMA_SLEEP,
			NULL, &dp->dma_handle[i])) != DDI_SUCCESS) {

			cmn_err(CE_WARN,
	"%s: sfe_alloc_memory: ddi_dma_alloc_handle failed. err:%d i:%d ",
				dp->name, err, i);
			while (i-- > 0) {
				ddi_dma_free_handle(&dp->dma_handle[i]);
			}
			goto err;
		}
	}
	dp->dma_handle_free = TX_RING_SIZE;

	/* Allocate local buffer */
	head = NULL;
	for (i = 0; i < SFE_LOCAL_BUF_INIT; i++) {
		lbp = sfe_get_lbuf(dp, TRUE);
		lbp->next = head;
		head = lbp;
	}
	while ((lbp = head) != NULL) {
		head = head->next;
		sfe_free_lbuf(lbp);
	}

	return 0;

err:
	ddi_dma_unbind_handle(dp->desc_dma_handle);
	ddi_dma_mem_free(&dp->desc_acc_handle);
	ddi_dma_free_handle(&dp->desc_dma_handle);

	return ENOMEM;
}

static void
sfe_free_memory(struct sfe_dev* dp)
{
	int		i;
	int		err;
	struct lbuf	*lbp;

	/* Free descriptor */
	err = ddi_dma_unbind_handle(dp->desc_dma_handle);
	ASSERT(err == DDI_SUCCESS);

	ddi_dma_mem_free(&dp->desc_acc_handle);
	ddi_dma_free_handle(&dp->desc_dma_handle);

	/* Free dma handles for Tx */
	for (i=0; i<TX_RING_SIZE; i++) {
		ddi_dma_free_handle(&dp->dma_handle[i]);
	}

	/* Free local buffers */
	while (lbp = dp->buf_free_list) {
		dp->buf_free_list = lbp->next;
#ifdef ALWAYS_MAPPED
		if (lbp->dma_handle) {
			err = ddi_dma_unbind_handle(lbp->dma_handle);
			ASSERT(err == DDI_SUCCESS);
		}
#endif
		ddi_dma_mem_free(&lbp->acc_handle);
		if (lbp->dma_handle) {
			ddi_dma_free_handle(&lbp->dma_handle);
		}
		kmem_free(lbp, sizeof(struct lbuf));
	}
}

static void
sfe_init_tx_desc(struct sfe_dev *dp)
{
	int	i;
	int	next;

	ASSERT(mutex_owned(&dp->xmitlock));

	dp->tx_head = dp->tx_tail = 0;

	for (i = 0, next = 0; i < TX_RING_SIZE; i++) {

		if (i < TX_RING_SIZE - 1) {
			next += sizeof(struct sfe_desc);
		} else {
			next = 0;
		}
		dp->tx_bp[i] = NULL;
		dp->tx_buf_type[i] = TX_BUF_INVALID;
		dp->tx_dma_handle_used[i]= NULL;

		dp->tx_desc[i].d_link = dp->tx_desc_dma + next;
		dp->tx_desc[i].d_cmdsts = 0;
	}
}

static void
sfe_clean_tx_desc(struct sfe_dev *dp)
{
	int			i;
	ddi_dma_handle_t	dh;
	struct lbuf		*lbp;
	mblk_t			*mp;

	ASSERT(mutex_owned(&dp->xmitlock));

	for (i = 0; i < TX_RING_SIZE; i++) {
		dp->tx_desc[i].d_cmdsts = 0;

		if ((dh = dp->tx_dma_handle_used[i]) != NULL) {
			/* release dma resource */
			ddi_dma_unbind_handle(dh);
			dp->tx_dma_handle_used[i] = NULL;
			sfe_free_dma_handle(dp, dh);
		}

		/* free untransmitted packet */
		switch (dp->tx_buf_type[i]) {
		case TX_BUF_MBLK:
			mp = dp->tx_bp[i];
			ASSERT(mp != NULL);
			/* free direct mapped mblk */
			freemsg(mp);
			dp->stats.errxmt++;
			break;

		case TX_BUF_LBUF:
			lbp = dp->tx_bp[i];
			ASSERT(lbp != NULL);
			/* free bounce buffer */
#ifndef ALWAYS_MAPPED
			ddi_dma_unbind_handle(lbp->dma_handle);
#endif
			sfe_free_lbuf(lbp);
			dp->stats.errxmt++;
			break;
		}
		dp->tx_buf_type[i] = TX_BUF_INVALID;
		dp->tx_bp[i] = NULL;
	}
}

static void 
sfe_init_rx_desc(struct sfe_dev *dp)
{
	int			i;
	struct lbuf		*lbp;
	ddi_dma_cookie_t	cookie;
	uint_t			count;
	uint_t			next;

	/*
	 * Construct RX descriptor ring
	 */
	for (i = 0, next = 0; i < RX_RING_SIZE; i++) {

		if (i < RX_RING_SIZE - 1) {
			next += sizeof(struct sfe_desc);
		} else {
			next = 0;
		}

		dp->rx_lbp[i] = NULL;
		dp->rx_desc[i].d_link = dp->rx_desc_dma + next;
		dp->rx_desc[i].d_cmdsts = 0;
	}

	for (i = 0; i < RX_RING_SIZE; i++) {

		/* * Allocate receive buffer */
		if ((lbp = sfe_get_lbuf(dp, TRUE)) == NULL) {
			/* No buffer */
			break;
		}

#ifdef ALWAYS_MAPPED
		dp->rx_desc[i].d_bufptr = lbp->dma_addr;
#else
		/* setup dma resource */
		if (ddi_dma_addr_bind_handle(lbp->dma_handle, NULL, lbp->buf,
					lbp->buf_len,
					DDI_DMA_READ | DDI_DMA_STREAMING,
					DDI_DMA_SLEEP, NULL,
					&cookie, &count) != DDI_SUCCESS) {
			/* No DMA resource */
			sfe_free_lbuf(lbp);
			continue;
		}

		ASSERT(count == 1);
		dp->rx_desc[i].d_bufptr = cookie.dmac_address;
#endif /* ALWAYS_MAPPED */
		dp->rx_lbp[i] = lbp;
		dp->rx_desc[i].d_cmdsts = lbp->buf_len;
	}

	/* Init RX buffer ring fifo */
	dp->rx_head = 0;
	dp->rx_tail = i;
}

static void
sfe_clean_rx_desc(struct sfe_dev* dp)
{
	int		i;
	struct lbuf	*lbp;

	ASSERT(mutex_owned(&dp->intrlock));

	/* Free all lbufs in the Rx queue. */
	for (i = 0; i < RX_RING_SIZE; i++) {

		dp->rx_desc[i].d_cmdsts = 0;

		if ((lbp = dp->rx_lbp[i]) != NULL) {
#ifndef ALWAYS_MAPPED
			/* release DMA resource */
			ddi_dma_unbind_handle(lbp->dma_handle);
#endif
			sfe_free_lbuf(lbp);
			dp->rx_lbp[i] = NULL;
		}
	}
}

/*==========================================================================*/

static void
sfe_tx_timeout(struct sfe_dev *dp)
{
	clock_t		now;
	unsigned long	flags;
	int		i;

	now = ddi_get_lbolt();

	mutex_enter(&dp->xmitlock); 
	if (!(dp->nic_active && dp->tx_head != dp->tx_tail &&
	     (now - dp->tx_start_time >= TX_TIMEOUT))) {
		mutex_exit(&dp->xmitlock); 
		goto schedule_next;
	}
	mutex_exit(&dp->xmitlock); 

	cmn_err(CE_WARN, "%s: transmit timeout detected: cr: %b isr: %b",
		dp->name,
		INL(dp, CR), CR_BITS,
		INL(dp, ISR), INTR_BITS);

	/* Block Rx */
	mutex_enter(&dp->intrlock);
	while (dp->intr_busy) {
		cv_wait(&dp->drain_cv, &dp->intrlock);
	}

	/* Block Tx */
	mutex_enter(&dp->xmitlock);
	dp->nic_active = FALSE;
	while (dp->tx_busy > 0) {
		cv_wait(&dp->drain_cv, &dp->xmitlock);
	}

	/* Disable interrupts*/
	OUTL(dp, IER, 0);

	/* Clear TX buffer */
	dp->tx_head = dp->tx_tail = 0;
	sfe_clean_tx_desc(dp);

	/* Restart HW */
	dp->tx_start_time = ddi_get_lbolt();
	dp->nic_active = TRUE;
	OUTL(dp, CR, CR_TXE);

	/* Enable interrupts */
	OUTL(dp, IER, IER_IE);

	mutex_exit(&dp->xmitlock);
	mutex_exit(&dp->intrlock);

	/* Restaret TX thread */
	gld_sched(dp->macinfo);

schedule_next:
	dp->timeout_id =
		timeout((void (*)(void *))sfe_tx_timeout,
			(void *)dp, TX_TIMEOUT_INTERVAL);
	return;
}

/*========================================================================*/
/*
 * Flow control support
 */
/*========================================================================*/
static void
sfe_pause_received(struct sfe_dev *dp, uint8_t *bp)
{
	uint16_t	type_len;
	uint16_t	pause_flag;
	uint16_t	pause_time;
	uint32_t	val;

	type_len = ntohs(((struct pause_frame *)bp)->type_len);
	pause_flag = ntohs(((struct pause_frame *)bp)->pause_flag);
	pause_time = ntohs(((struct pause_frame *)bp)->pause_time);

	DPRINTF(2, (CE_CONT,
		"%s: pause packet received: src:%02x:%02x:%02x:%02x:%02x:%02x "
		"type:0x%04x flag:0x%04x time:0x%04x",
		dp->name, bp[6], bp[7], bp[8], bp[9], bp[10], bp[11],
		type_len, pause_flag, pause_time));

	if (dp->chip->chip_type == CHIPTYPE_DP83815) {
		/*
		 * It seems that DP83815 does not pause TX automatically
		 * when it receives a IEEE 802.3x pause frame.
		 * For a workaround, we pause transmition manually.
		 * Is it right ? But it works.
		 */
		switch (pause_flag) {
		case 1:
			if (pause_time == 0) {
				/* release HW */
				/* cancel pause */
				val = INL(dp, PCR);
				OUTL(dp, PCR, val & ~PCR_PSEN);
				drv_usecwait(1);
				/* restore PCR */
				OUTL(dp, PCR, val);
			}
			else {
				/* issue pause command */
				val = INL(dp, PCR);
				if ((val & (PCR_PS_RCVD | PCR_PS_ACT)) == 0) {
					val &= ~PCR_PAUSE_CNT;
					val |=  pause_time | PCR_MLD_EN;
					OUTL(dp, PCR, val);
				}
			}
			break;

		default:
			cmn_err(CE_NOTE,
				"%s: unknown mac control frame: flag:%d",
				pause_flag);
			break;
		}
	}
	return;
}

#ifdef TX_FLOW_CONTROL
static void
sfe_push_pause_frame(struct sfe_dev *dp, int on)
{
	int	slot;

	ASSERT(SUB(dp->tx_tail, dp->tx_head) < TX_RING_SIZE);
	ASSERT(on == 0 || on == 1);
	/*
	 * put pause frame at the top of TX buffer list
	 */
	mutex_enter(&dp->xmitlock);

	dp->tx_head--;
	slot = SLOT(dp->tx_head, TX_RING_SIZE);

	dp->tx_buf_type[slot] = TX_BUF_PAUSE;
	dp->tx_bp[slot] = NULL;
	dp->tx_dma_handle_used[slot] = NULL;

	dp->tx_desc[slot].d_bufptr = dp->tx_pause_dma[on];
	dp->tx_desc[slot].d_cmdsts = ETHERMIN | CMDSTS_OWN;

	/* change TX descriptor base */
	OUTL(dp, TXDP, dp->tx_desc_dma + sizeof(struct sfe_desc) * slot);

	/* kick HW */
	OUTL(dp, CR, CR_TXE);
	dp->tx_start_time = ddi_get_lbolt();

	mutex_exit(&dp->xmitlock);
}

static void
sfe_send_pause_frame(struct sfe_dev *dp, int on)
{
	int	slot;

	ASSERT(SUB(dp->tx_tail, dp->tx_head) < TX_RING_SIZE);
	ASSERT(on == 0 || on == 1);

	mutex_enter(&dp->xmitlock);

	slot = SLOT(dp->tx_tail, TX_RING_SIZE);

	dp->tx_buf_type[slot] = TX_BUF_PAUSE;
	dp->tx_bp[slot] = NULL;
	dp->tx_dma_handle_used[slot] = NULL;

	dp->tx_desc[slot].d_bufptr = dp->tx_pause_dma[on];
	dp->tx_desc[slot].d_cmdsts = ETHERMIN | CMDSTS_OWN;

	dp->tx_tail++;
	OUTL(dp, CR, CR_TXE);
	dp->tx_start_time = ddi_get_lbolt();

	mutex_exit(&dp->xmitlock);
}
#endif /* TX_FLOW_CONTROL */
/*========================================================================*/
/*
 * Interrupt handling routines
 */
/*========================================================================*/
static int
sfe_append_rxbuf(struct sfe_dev *dp, struct lbuf *lbp)
{
	int		slot;
	int		err;
	ddi_dma_cookie_t cookie;
	uint_t		count;

	ASSERT(lbp != NULL);
	ASSERT(SUB(dp->rx_tail, dp->rx_head) < RX_RING_SIZE);
	ASSERT(mutex_owned(&dp->intrlock));

	/*
	 * Append newly allocated empty rx buffer into rx buffer list.
	 */
	slot = SLOT(dp->rx_tail, RX_RING_SIZE);

	ASSERT(dp->rx_lbp[slot] == NULL);

#ifdef ALWAYS_MAPPED
	dp->rx_desc[slot].d_bufptr = lbp->dma_addr;
#else
	if ((err = ddi_dma_addr_bind_handle(lbp->dma_handle,
				NULL,
				lbp->buf, lbp->buf_len,
				DDI_DMA_READ | DDI_DMA_STREAMING,
				DDI_DMA_DONTWAIT, NULL,
				&cookie, &count)) != DDI_SUCCESS) {
		/*
		 * No DMA resource available
		 */
		ASSERT(err != DDI_DMA_INUSE);
		sfe_free_lbuf(lbp);
		return -1;
	}

	ASSERT(count == 1);
	dp->rx_desc[slot].d_bufptr = cookie.dmac_address;
#endif /* ALWAYS_MAPPED */
	dp->rx_lbp[slot] = lbp;
	dp->rx_desc[slot].d_cmdsts = lbp->buf_len;

	dp->rx_tail++;

	return 0;
}

static void
sfe_reclaim_rxbuf(struct lbuf *lbp)
{
	struct sfe_dev	*dp;

	ASSERT(lbp != NULL);

	dp = lbp->devp;
	mutex_enter(&dp->intrlock);
	if (SUB(dp->rx_tail, dp->rx_head) < RX_RING_SIZE) {
		(void)sfe_append_rxbuf(dp, lbp);
		OUTL(dp, CR, CR_RXE);
		mutex_exit(&dp->intrlock);
		return;
	}
	mutex_exit(&dp->intrlock);

	sfe_free_lbuf(lbp);
	return;
}

static int
sfe_receive(struct sfe_dev *dp)
{
	int		err;
	unsigned int	slot;
	uint32_t	status;
	unsigned int	len;
	struct lbuf	*lbp;
	mblk_t		*mp;
	int		i;
	seqnum_t	limit;
#ifdef TX_FLOW_CONTROL
	unsigned int	hiwater;
#endif

	/*
	 * We have a free rx buffer list  which pointed by
	 * rx_head and rx_tail. (Actually rx_tail points the next slot of
	 * the end of the list.)
	 * NIC consumes this list from head to tail. So, we pop received packet
	 * from the head of this list. 
	 */

	/*
	 * Pop up all received packets from the head of the rx buffer list.
	 */
	DPRINTF(3, (CE_CONT, "%s: sfe_receive: rx_head:%d, status:%b",
			dp->name, dp->rx_head, 
			dp->rx_desc[SLOT(dp->rx_head, RX_RING_SIZE)].d_cmdsts,
			RXSTAT_BITS));
#ifdef TX_FLOW_CONTROL
#ifdef DEBUG
	hiwater = SLOT(dp->rx_head + 3, RX_RING_SIZE);
#else
	hiwater = SLOT(dp->rx_tail - (RX_RING_SIZE/4), RX_RING_SIZE);
#endif
#endif /* TX_FLOW_CONTROL */
	limit   = dp->rx_tail;

	while (dp->rx_head != limit) {

		slot = SLOT(dp->rx_head, RX_RING_SIZE);
		status = dp->rx_desc[slot].d_cmdsts;

		if ((status & CMDSTS_OWN) == 0) {
			/*
			 * No more received packets because
			 * this buffer is owned by NIC.
			 */
			break;
		}

		/* remove the head from rx buffer list */
		lbp = dp->rx_lbp[slot];
		dp->rx_lbp[slot] = NULL;
		dp->rx_head++;

#define	RX_ERR_BITS \
	(CMDSTS_RXA | CMDSTS_RXO | CMDSTS_LONG | CMDSTS_RUNT | \
	 CMDSTS_ISE | CMDSTS_CRCE | CMDSTS_FAE)

		if ((status & RX_ERR_BITS) != 0) {
			/*
			 * Packet with error received
			 */
			DPRINTF(0, (CE_CONT, "%s: Corrupted packet "
				"received, buffer status: %b",
				dp->name, status, RXSTAT_BITS));

			/* collect statistics information */
			dp->stats.errrcv++;
			if ((status & CMDSTS_RXO) != 0) {
				dp->stats.overflow++;
			}
			if ((status & CMDSTS_LONG) != 0) {
				dp->stats.frame_too_long++;
			}
			if ((status & CMDSTS_RUNT) != 0) {
				dp->stats.runt++;
			}
			if ((status & (CMDSTS_ISE | CMDSTS_FAE)) != 0) {
				dp->stats.frame++;
			}
			if ((status & CMDSTS_CRCE) != 0) {
				dp->stats.crc++;
			}

			/* reuse current receive buffer */
			sfe_free_lbuf(lbp);
			continue;
		}

		/*
		 *  RX packet without no error received
		 */
		len = (status & CMDSTS_SIZE) - ETHERFCSL;
		ASSERT(lbp != NULL);
#ifdef RX_FLOW_CONTROL
		if (dp->flow_control && bcmp(lbp->buf,
			sfe_pause_mac_addr.ether_addr_octet, ETHERADDRL) == 0) {

			sfe_pause_received(dp, lbp->buf);

			/* treat as a psuedo collision */
			dp->stats.collisions++;

			/*
			 * For performance, we discard this packet
			 * if we are not in promiscous mode
			 */
			sfe_free_lbuf(lbp);
			continue;
		}
#endif

		/* Allocate msg block structure */
		if ((mp = esballoc(lbp->buf, len, BPRI_LO,
							&lbp->frtn)) == NULL) {
			dp->stats.norcvbuf++;

			/* reuse current receive buffer */
			sfe_free_lbuf(lbp);
			continue;
		}

		/*
		 * Direct reception
		 */
		mp->b_wptr = mp->b_rptr + len;
#ifdef ALWAYS_MAPPED
		ddi_dma_sync(lbp->dma_handle, 0, len, DDI_DMA_SYNC_FORKERNEL);
#else
		/* release dma resources */
		ddi_dma_unbind_handle(lbp->dma_handle);
#endif /* ALWAYS_MAPPED */

		/* send received message up */
		mutex_exit(&dp->intrlock);
		gld_recv(dp->macinfo, mp);
		mutex_enter(&dp->intrlock);

#ifdef TX_FLOW_CONTROL
		/*
		 * IEEE 802.3x flow contol
		 */	
		if (dp->flow_control && !dp->rx_in_pause &&
		   (dp->rx_desc[hiwater].d_cmdsts & CMDSTS_OWN) != 0) {
#ifdef DEBUG
			dp->stats.norcvbuf++;
#endif
			/*
			 * High water mark was exceeded . Send a pause frame.
			 */
			dp->rx_in_pause = TRUE;
#if 1
			sfe_send_pause_frame(dp, 1);
#else
			/*
			 * Stop TX to put a pause frame on the top
			 * of the TX list.
			 * And quit RX loop to issue the pause frame.
			 */
			dp->rx_pause_request = TRUE;
			OUTL(dp, CR, CR_TXR);
			break;
#endif
		}
#endif /* TX_FLOW_CONTROL */
	}

	/*
	 * Append newly allocated empty rx buffer into rx buffer list.
	 */
	i = RX_RING_SIZE - SUB(dp->rx_tail, dp->rx_head);
	while (i--) {
		ASSERT(dp->rx_lbp[SLOT(dp->rx_tail, RX_RING_SIZE)] == NULL);
		if ((lbp = sfe_get_lbuf(dp, FALSE)) == NULL) {
			/*
			 * No memory available.
			 */
			cmn_err(CE_WARN, "%s: no rx buffer", dp->name);
			dp->stats.norcvbuf++;
			break;
		}
		sfe_append_rxbuf(dp, lbp);
	}

	/* kick RX engine again */
	OUTL(dp, CR, CR_RXE);

#ifdef TX_FLOW_CONTROL
	if (dp->flow_control && !dp->rx_pause_request &&
	    SUB(dp->rx_tail, dp->rx_head) > 3*(RX_RING_SIZE/4)) {
		if (dp->rx_in_pause) {
			sfe_send_pause_frame(dp, 0);
			dp->rx_in_pause = FALSE;
		}
	}
#endif /* TX_FLOW_CONTROL */

	return 0;
}

static void
sfe_transmit_done(struct sfe_dev *dp)
{
	ddi_dma_handle_t dh;
	struct lbuf	*lbp;
	mblk_t		*mp;
	unsigned int	slot;
	uint32_t	status;

	ASSERT(mutex_owned(&dp->xmitlock));
	ASSERT(SUB(dp->tx_tail, dp->tx_head) >= 0);

	for (; dp->tx_head != dp->tx_tail; dp->tx_head++) {

		slot = SLOT(dp->tx_head, TX_RING_SIZE);

		if (((status = dp->tx_desc[slot].d_cmdsts) & CMDSTS_OWN) != 0) {
			/*
			 * Done. This fragment is owned by the nic.
			 */
			break;
		}

		if ((dh = dp->tx_dma_handle_used[slot]) != NULL) {
			/* free dma resource */
			ddi_dma_unbind_handle(dh);
			sfe_free_dma_handle(dp, dh);
			dp->tx_dma_handle_used[slot] = NULL;
		}

		if ((status & CMDSTS_MORE) != 0) {
			/* this is not last fragment */
			ASSERT(dp->tx_buf_type[slot] == TX_BUF_INVALID);
			ASSERT(dp->tx_bp[slot] == NULL);
			continue;
		}

		/*
		 *  collect statictics
		 */
		if ((status & CMDSTS_OK) != 0) {
			if (!dp->full_duplex) {
				int	cols;

				cols = (status & CMDSTS_CCNT)
						>> CMDSTS_CCNT_SHIFT;

				if (cols > 0) {
					if (cols == 1) {
						dp->stats.first_coll++;
					} else /* (cols > 1) */ {
						dp->stats.multi_coll++;
					}
					dp->stats.collisions += cols;
				}
				else if (status & CMDSTS_TD) {
					dp->stats.defer++;
				}
			}
		}
		else {
			/* packet failed to transmit */
			DPRINTF(2, (CE_CONT, "%s: Transmit error, Tx status %b",
				       dp->name, status, TXSTAT_BITS));

			dp->stats.errxmt++;
			if (status & CMDSTS_TFU) {
				dp->stats.underflow++;
			}
			if (status & CMDSTS_CRS) {
				dp->stats.nocarrier++;
			}
			if (status & CMDSTS_OWC) {
				dp->stats.xmtlatecoll++;
			}
			if (!dp->full_duplex) {
				if (status & CMDSTS_EC) {
					dp->stats.excoll++;
					dp->stats.collisions += 16;
				}
			}
		}

		/*
		 * Free TX buffer
		 */
		switch (dp->tx_buf_type[slot]) {
		case TX_BUF_MBLK:
			mp = dp->tx_bp[slot];
			ASSERT(mp != NULL);
			/* Free the original mblk. */
			freemsg(mp);
			break;

		case TX_BUF_LBUF:
			lbp = dp->tx_bp[slot];
			ASSERT(lbp != NULL);
			/* Free tx bounce buffer. */
#ifndef ALWAYS_MAPPED
			ddi_dma_unbind_handle(lbp->dma_handle);
#endif
			sfe_free_lbuf(lbp);
			break;

		case TX_BUF_PAUSE:
			/* Do nothing */
			break;

		default:
			cmn_err(CE_PANIC, "%s: invalid tx buffer type",
				dp->name);
			/* Not Reached */
		}
		dp->tx_buf_type[slot] = TX_BUF_INVALID;
		dp->tx_bp[slot] = NULL;
	}
}

static u_int
sfe_interrupt(gld_mac_info_t *macinfo)
{
	struct sfe_dev	*dp;
	uint32_t	isr;
	int		restart_tx = FALSE;

	dp = (struct sfe_dev *)macinfo->gldm_private;

	mutex_enter(&dp->intrlock);

	/* read reason and clear interrupt */
	isr = INL(dp, ISR);

	DPRINTF(3, (CE_CONT, "%s: sfe_interrupt: called: isr:0x%b",
		dp->name, isr, INTR_BITS));

	if ((isr & dp->our_intr_bits) == 0) {
		/* not for us */
		mutex_exit(&dp->intrlock);
		return DDI_INTR_UNCLAIMED;
	}
	dp->stats.intr++;
	dp->intr_busy = TRUE;

	if (!dp->nic_active) {
		goto x;
	}

	if (dp->chip->chip_type == CHIPTYPE_SIS900) {
		if (isr & ISR_PAUSE_ST) {
			dp->stats.collisions++;
		}
	}

#ifdef TX_FLOW_CONTROL
	if ((isr & ISR_TXRCMP) != 0) {
		if (dp->rx_pause_request) {
			sfe_push_pause_frame(dp, 1);
			dp->rx_pause_request = FALSE;
		}
	}
#endif
	if ((isr & (ISR_RXORN | ISR_RXERR | ISR_RXOK)) != 0) {
		/* receive  done */
		sfe_receive(dp);
	}

	if ((isr & (ISR_TXURN | ISR_TXERR | ISR_TXIDLE | ISR_TXOK)) != 0) {
		/* transmit done */
		mutex_enter(&dp->xmitlock);
		sfe_transmit_done(dp);
		restart_tx = dp->tx_blocked;
		mutex_exit(&dp->xmitlock);
	}

	if ((isr & ISR_HIBERR) != 0) {
		cmn_err(CE_WARN, "%s: ERROR interrupt: isr %b.",
			dp->name, isr, INTR_BITS);
	}
x:
	if (!dp->nic_active) {
		cv_broadcast(&dp->drain_cv);
	}
	dp->intr_busy = FALSE;
#ifdef notdef
	DPRINTF(3, (CE_CONT, "%s: sfe_interrupt: return: isr: %b",
	       dp->name, INL(dp, ISR), INTR_BITS));
#endif
	mutex_exit(&dp->intrlock);

	if (restart_tx) {
		/* schedule tx task again */
		gld_sched(macinfo);
	}

	return DDI_INTR_CLAIMED;
}

/* ======================================================== */
/*
 * Chip dependant register manupilation routines
 */
/* ======================================================== */

static void
sfe_generate_macaddr(struct sfe_dev *dp, uint8_t *mac)
{
	int		i;
	uint_t		val;
	extern char	hw_serial[];

	cmn_err(CE_CONT,
	"!%s: using temporal ether address, do not use this for long time",
		dp->name);
	val = 0;
	for (i = 0; i < 11; i++) {
		if (hw_serial[i] == 0) {
			break;
		}
		val = val * 10 + hw_serial[i] - '0';
	}
	mac[0] = 0;
	mac[1] = 0;
	mac[2] = 0;
	mac[3] = val >> 16;
	mac[4] = val >> 8;
	mac[5] = val ^ (val >> 24);

	return;
}

static boolean_t
sfe_get_mac_addr_conf(struct sfe_dev *dp)
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
		sfe_generate_macaddr(dp, mac);
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

static void
sfe_set_rx_filter_dp83815(struct sfe_dev *dp)
{
	int		i;
	uint32_t	mode;
	int		addr_shift;
	uint8_t		*mac;
#ifdef USE_MULTICAST_HASHTBL
	static uint16_t	hash_tbl[0x200/2];
#endif

	DPRINTF(4, (CE_CONT, "%s: sfe_set_rx_filter_dp83815: called",
		dp->name));

	addr_shift = RFCR_RFADDR_SHIFT_DP83815;
	mac = dp->cur_addr.ether_addr_octet;

	/* Set Receive filter control register */

	if ((dp->rxmode & RXMODE_PROMISC) != 0) {
		mode = RFCR_AAB		/* all broadcast */
		     | RFCR_AAM		/* all multicast */
		     | RFCR_AAP;	/* all physcal */
	}
	else if ((dp->rxmode & RXMODE_ALLMULTI) != 0) {
		mode = RFCR_AAB		/* all broadcast */
		     | RFCR_AAM		/* all multicast */
		     | RFCR_APM_DP83815;/* physical for the chip */
	}
	else {
		mode = RFCR_AAB		/* all broadcast */
		     | RFCR_APM_DP83815;/* physical for the chip */
		if (dp->mc_count > 0) {
#ifdef USE_MULTICAST_HASHTBL
			mode |= RFCR_MHEN_DP83815;	/* ? */
			bzero(hash_tbl, sizeof(hash_tbl));
			/* make hash table; not implemented */
#else
			mode |= RFCR_AAM;
#endif
		}
	}

	/* Disable Rx filter and load mac address for the chip */
	for (i = 0; i < ETHERADDRL; i += 2) {
		OUTL(dp, RFCR, RFADDR_MAC_DP83815 + i);
		OUTL(dp, RFDR, (mac[i+1] << 8) | mac[i]);
	}

#ifdef USE_MULTICAST_HASHTBL
	if (mode & RFCR_MHEN_DP83815) {
		/* Load Multicast hash table */
		/* Sorry, not yet */
	}
#endif
	/* Set rx filter mode and enable rx filter */
	OUTL(dp, RFCR, RFCR_RFEN | mode);
}

static boolean_t
sfe_get_mac_addr_dp83815(struct sfe_dev *dp)
{
	uint8_t		*mac;
	int		val;
	int		i;

#define	BITSET(p, ix, v)	(p)[(ix)/8] |= ((v) ? 1 : 0) << ((ix) & 0x7)
#define	BITTEST(v, pos)		((v) & (1 << (pos)))

	DPRINTF(4, (CE_CONT, "%s: sfe_get_mac_addr_dp83815: called", dp->name));

	mac = dp->dev_addr.ether_addr_octet;

	/* first of all, clear MAC address buffer */
	bzero(mac, ETHERADDRL);

	/* get bit 0 */
	val = sfe_read_eeprom(dp, 0x6);
	BITSET(mac, 0, val & 1);

	/* get bit 1 - 16 */
	val = sfe_read_eeprom(dp, 0x7);
	for (i = 0; i < 16; i++) {
		BITSET(mac, 1 + i, val & (1 << (15 - i)));
	}

	/* get bit 17 -  32 */
	val = sfe_read_eeprom(dp, 0x8);
	for (i = 0; i < 16; i++) {
		BITSET(mac, 17 + i, val & (1 << (15 - i)));
	}

	/* get bit 33 -  47 */
	val = sfe_read_eeprom(dp, 0x9);
	for (i = 0; i < 15; i++) {
		BITSET(mac, 33 + i, val & (1 << (15 - i)));
	}

	return TRUE;
#undef BITSET
#undef BITTEST
}

static uint16_t
sfe_mii_read_dp83815(struct sfe_dev *dp, int offset)
{
	return (uint16_t) INL(dp, MII_REGS_BASE + offset*4);
}

static void
sfe_mii_write_dp83815(struct sfe_dev *dp, int offset, uint16_t val)
{
	OUTL(dp, MII_REGS_BASE + offset*4, val);
}

static boolean_t
sfe_chipinfo_init_dp83815(struct sfe_dev *dp)
{
	dp->get_mac_addr  = &sfe_get_mac_addr_dp83815;
	dp->mii_write_reg = &sfe_mii_write_dp83815;
	dp->mii_read_reg  = &sfe_mii_read_dp83815;
	dp->set_rx_filter = &sfe_set_rx_filter_dp83815;

	return TRUE;
}

static void
sfe_set_rx_filter_sis900(struct sfe_dev *dp)
{
	int		i;
	uint32_t	mode;
	uint32_t	hash_tbl[8];
	uint8_t		*mac;
	uint16_t	m[3];

	DPRINTF(4, (CE_CONT, "%s: sfe_set_rx_filter_sis900: called", dp->name));

	mac = dp->cur_addr.ether_addr_octet;

	/* Set Receive filter control register */

	if ((dp->rxmode & RXMODE_PROMISC) != 0) {
		mode = RFCR_AAB | RFCR_AAM | RFCR_AAP;
	}
	else if ((dp->rxmode & RXMODE_ALLMULTI) != 0) {
		mode = RFCR_AAB | RFCR_AAM;
	}
	else {
		mode = RFCR_AAB;
		if (dp->mc_count > 0) {
#ifdef USE_MULTICAST_HASHTBL
			/* make hash table; not implemented */
#else
			mode |= RFCR_AAM;
#endif
		} else {
			bzero(hash_tbl, sizeof(hash_tbl));
		}
	}

	/* Disable Rx filter and load mac address */
	for (i = 0; i < ETHERADDRL; i += 2) {
		OUTL(dp, RFCR, (RFADDR_MAC_SIS900 + (i/2)) << RFCR_RFADDR_SHIFT_SIS900);
		OUTL(dp, RFDR, (mac[i+1] << 8) | mac[i]);
	}

	/* Load Multicast hash table */
	for (i = 0; i < 8; i++) {
		OUTL(dp, RFCR,
		    (RFADDR_MULTICAST_SIS900 + i) << RFCR_RFADDR_SHIFT_SIS900);
		OUTL(dp, RFDR, hash_tbl[i]);
	}

	/* Load rx filter mode and enable rx filter */
	OUTL(dp, RFCR, RFCR_RFEN | mode);
}

static boolean_t
sfe_get_mac_addr_sis900(struct sfe_dev *dp)
{
	int	val;
	int	i;
	uint8_t	*mac;
	
	mac = dp->dev_addr.ether_addr_octet;

	for (i = 0; i < ETHERADDRL/2; i++) {
		val = sfe_read_eeprom(dp, 0x8 + i);
		*mac++ = val;
		*mac++ = val >> 8;
	}

	return TRUE;
}

static boolean_t
sfe_get_mac_addr_sis630e(struct sfe_dev *dp)
{
#ifdef GET_MAC_ADDR_SIS630E
	uint32_t	rfcrSave;
	int		i;
	uint16_t	v;
        dev_info_t	*isa_bridge;
        ddi_acc_handle_t isa_handle;
        int		reg;

	/*
	 * ddi_find_devinfo() is undocumented officially,
	 * but it is described in /usr/include/sys/sunddi.h
	 */
	if ((isa_bridge = ddi_find_devinfo("pci1039,8", -1, 0)) == NULL) {
		cmn_err(CE_WARN, "%s: cannot find isa-bridge (pci1039,8)",
				dp->name);
		return FALSE;
	}

	if (pci_config_setup(isa_bridge, &isa_handle) != DDI_SUCCESS) {
		cmn_err(CE_WARN, "%s: ddi_regs_map_setup failed",
			dp->name);
		return FALSE;
	}

	/* enable to access CMOS RAM */
	reg = pci_config_get8(isa_handle, 0x48);
	pci_config_put8(isa_handle, 0x48, reg | 0x40);

	for (i = 0; i < ETHERADDRL; i++) {
		outb(0x70, 0x09 + i);
		dp->dev_addr.ether_addr_octet[i] = inb(0x71); 
	}

	/* disnable to access CMOS RAM */
	pci_config_put8(isa_handle, 0x48, reg);
	pci_config_teardown(&isa_handle);
x:

	return TRUE;
#else
	return FALSE;
#endif
}

static boolean_t
sfe_get_mac_addr_sis635(struct sfe_dev *dp)
{
	int		i;
	uint32_t	old;
	uint16_t	v;

	DPRINTF(0, (CE_CONT, "%s: sfe_get_mac_addr_sis635: called", dp->name));

	old = INL(dp, RFCR);

	OUTL(dp, CR, CR_RELOAD);
	OUTL(dp, CR, 0);

	/* disable packet filtering before reading filter */
	OUTL(dp, RFCR, old & ~RFCR_RFEN);

	/* load MAC addr from filter data register */
	for (i = 0 ; i < ETHERADDRL/2 ; i++) {
		OUTL(dp, RFCR, i << RFCR_RFADDR_SHIFT_SIS900);
		v = INL(dp, RFDR);
		dp->dev_addr.ether_addr_octet[i*2    ] = v;
		dp->dev_addr.ether_addr_octet[i*2 + 1] = v >> 8;
	}

	/* re-enable packet filitering */
	OUTL(dp, RFCR, old | RFCR_RFEN);

	return TRUE;
}

static boolean_t
sfe_get_mac_addr_sis962(struct sfe_dev *dp)
{
	int	ret;
	int	i;

	/* rise request signal */
	OUTL(dp, MEAR, EROMAR_EEREQ);
	i = 200;
	while (--i) {
		if ((INL(dp, MEAR) & EROMAR_EEGNT) != 0) {
			break;
		}
		drv_usecwait(10);      
	}

	if (i > 0) {
		ret = sfe_get_mac_addr_sis900(dp);
	} else {
		/* failed to get eeprom */
		cmn_err(CE_NOTE, "!%s: failed to access eeprom", dp->name);
		ret = FALSE;
	}

	/* release EEPROM */
	OUTL(dp, MEAR, EROMAR_EEDONE);

	return ret;
}

#define MDIO_DELAY(dp)    INL(dp, MEAR)

static void
sfe_mii_sync_sis900(struct sfe_dev *dp)
{
	int	i;

	for (i = 0; i < 32; i++) {
		OUTL(dp, MEAR, MEAR_MDDIR | MEAR_MDIO);
		MDIO_DELAY(dp);
		OUTL(dp, MEAR, MEAR_MDDIR | MEAR_MDIO | MEAR_MDC);
		MDIO_DELAY(dp);
	}
	return;
}

static uint16_t
sfe_mii_read_sis900(struct sfe_dev *dp, int reg)
{
	uint32_t	cmd;
	uint16_t	ret;
	int		i;
	int		data;

	cmd = (6<<(18+5+5)) | (dp->mii_phy_addr<<(18+5)) | (reg<<18);

	sfe_mii_sync_sis900(dp);

	OUTL(dp, MEAR, MEAR_MDDIR | MEAR_MDIO);
	MDIO_DELAY(dp);
	OUTL(dp, MEAR, MEAR_MDDIR | MEAR_MDIO | MEAR_MDC);

	for (i = 31; i >= 16; i--) {
		data = ((cmd >> i) & 1) <<  MEAR_MDIO_SHIFT;
		OUTL(dp, MEAR, data | MEAR_MDDIR);
		MDIO_DELAY(dp);
		OUTL(dp, MEAR, data | MEAR_MDDIR | MEAR_MDC);
		MDIO_DELAY(dp);
	}

	for (i = 15; i >= 0; i--) {
		OUTL(dp, MEAR, 0);
		MDIO_DELAY(dp);
		ret = (ret << 1) | ((INL(dp, MEAR) >> MEAR_MDIO_SHIFT) & 1);
		OUTL(dp, MEAR, MEAR_MDC);
		MDIO_DELAY(dp);
	}

	OUTL(dp, MEAR, 0);

	return ret;
}

static void
sfe_mii_write_sis900(struct sfe_dev *dp, int reg, uint16_t val)
{
	int	cmd;
	int	i;
	int	data;

	cmd = (5<<(18+5+5)) | (dp->mii_phy_addr<<(18+5))
		| (reg<<18) | (2 << 16) | val;

	sfe_mii_sync_sis900(dp);
	OUTL(dp, MEAR, MEAR_MDDIR | MEAR_MDIO);
	MDIO_DELAY(dp);
	OUTL(dp, MEAR, MEAR_MDDIR | MEAR_MDIO | MEAR_MDC);

	for (i = 31; i >= 16; i--) {
		data = ((cmd >> i) & 1) << MEAR_MDIO_SHIFT;
		OUTL(dp, MEAR, data | MEAR_MDDIR);
		MDIO_DELAY(dp);
		OUTL(dp, MEAR, data | MEAR_MDDIR | MEAR_MDC);
		MDIO_DELAY(dp);
	}
	MDIO_DELAY(dp);

	for (i = 15; i >= 0; i--) {
		data = ((cmd >> i) & 1) << MEAR_MDIO_SHIFT;
		OUTL(dp, MEAR, data | MEAR_MDDIR);
		MDIO_DELAY(dp);
		OUTL(dp, MEAR, data | MEAR_MDDIR | MEAR_MDC);
		MDIO_DELAY(dp);
	}
	MDIO_DELAY(dp);

	/* Clear out extra bits. */
	for (i = 0; i < 2; i++) {
		OUTL(dp, MEAR, 0);
		MDIO_DELAY(dp);
		OUTL(dp, MEAR, MEAR_MDC);
		MDIO_DELAY(dp);
	}
	OUTL(dp, MEAR, 0);

	return;
}
#undef MDIO_DELAY

static boolean_t
sfe_chipinfo_init_sis900(struct sfe_dev *dp)
{
	int	rev;

	rev = dp->revid;

	if (rev == SIS630E_900_REV /* 0x81 */) {
		/* sis630E */
		dp->get_mac_addr = &sfe_get_mac_addr_sis630e;
	}
	else if (rev > 0x81 &&  rev <= 0x90) {
		/* 630S ... 635A */
		dp->get_mac_addr = &sfe_get_mac_addr_sis635;
	}
	else if (rev == SIS962_900_REV /* 0x91 */) {
		/* sis962 */
		dp->get_mac_addr = &sfe_get_mac_addr_sis962;
	}
	else {
		/* sis900 */
		dp->get_mac_addr = &sfe_get_mac_addr_sis900;
	}

	dp->mii_write_reg = &sfe_mii_write_sis900;
	dp->mii_read_reg  = &sfe_mii_read_sis900;
	dp->set_rx_filter = &sfe_set_rx_filter_sis900;

#ifdef TUNE_PHY_630
	dp->bridge_revid = 0;

	if (rev == SIS630E_900_REV || rev == SIS630EA1_900_REV ||
	    rev == SIS630A_900_REV || rev ==  SIS630ET_900_REV) {
		/*
		 * read host bridge revision
		 */
		dev_info_t	*bridge;
		ddi_acc_handle_t bridge_handle;
		int		reg;

		/*
		 * ddi_find_devinfo() is undocumented officially,
		 * but it is described in /usr/include/sys/sunddi.h
		 */
		if ((bridge = ddi_find_devinfo("pci1039,630", -1, 0)) == NULL) {
			cmn_err(CE_WARN,
				"%s: cannot find host bridge (pci1039,630)",
				dp->name);
			goto x;
		}

		if (pci_config_setup(bridge, &bridge_handle) != DDI_SUCCESS) {
			cmn_err(CE_WARN, "%s: pci_config_setup failed",
				dp->name);
			goto x;
		}

		dp->bridge_revid =
			pci_config_get8(bridge_handle, PCI_CONF_REVID);
		pci_config_teardown(bridge_handle);
	}
#endif /* TUNE_PHY_630 */
x:
	return TRUE;
}

/* ======================================================== */
/*
 * HW manupilation routines
 */
/* ======================================================== */
static int
sfe_reset_chip(struct sfe_dev *dp)
{
	int	i;
	int	isr;

	OUTL(dp, CR, CR_RST);
	drv_usecwait(10);

	i   = 100;
	while ((INL(dp, CR) & CR_RST) != 0) {
		if (--i == 0) {
			cmn_err(CE_WARN, "%s: chip reset timeout", dp->name);
			return 1;	
		}
		drv_usecwait(10);
	}

	if (dp->chip->chip_type == CHIPTYPE_SIS900) {
		if (dp->revid == SIS630ET_900_REV) {
			OUTL(dp, CR, CR_ACCESSMODE | INL(dp, CR));
		}
	}

	return 0;
}

static void
sfe_init_chip(struct sfe_dev *dp)
{
	uint32_t	val;
	int		i;

	/* Configration register: PCI parity enable */
	DPRINTF(1, (CE_CONT, "?%s: cfg:%b", dp->name, INL(dp, CFG), CFG_BITS));
	val = CFG_PESEL;
	if (dp->chip->chip_type == CHIPTYPE_DP83815) {
		/* force to advertise pause capability */
		val |= CFG_PAUSE_ADV;
	}
	else if (dp->chip->chip_type == CHIPTYPE_SIS900) {
		if (dp->revid >= SIS635A_900_REV ||
		    dp->revid == SIS900B_900_REV) {
			/* what is this ? */
			val |= CFG_RND_CNT;
		}
	}
	OUTL(dp, CFG, val);
	DPRINTF(1, (CE_CONT, "?%s: cfg:%b", dp->name, INL(dp, CFG), CFG_BITS));

	/* PCI test control register: do nothing */

	/* Interrupt status register : clear pended interrupts */
	(volatile int)i = INL(dp, ISR);

	/* Interrupt enable register: enable interrupt */
	OUTL(dp, IER, 0);

	/* Interrupt mask register: clear */
	if (dp->chip->chip_type == CHIPTYPE_SIS900) {
		dp->our_intr_bits = OUR_INTR_BITS_SIS900;
	} else {
		dp->our_intr_bits = OUR_INTR_BITS;
	}
	OUTL(dp, IMR, dp->our_intr_bits);

	/* Enhanced PHY Access register (sis900): do nothing */

	/* Transmit Descriptor Pointer register: base addr of TX ring */
	OUTL(dp, TXDP, dp->tx_desc_dma);

	/* Receive descriptor pointer register: base addr of RX ring */
	OUTL(dp, RXDP, dp->rx_desc_dma);

	/* Tx and Rx configuration registers, flow/pause control register */
	sfe_set_media(dp);

#ifdef notdef
	/* Set Mac address, Rx filter and Rx mode */
	sfe_set_rx_filter(dp);
#else
	/* Disable Rx filter */
	OUTL(dp, RFCR, 0);
#endif
}

static void
sfe_start_chip(struct sfe_dev *dp)
{
	/* enable interrupt */
	OUTL(dp, IER, IER_IE);

	/* Kick TX and RX */
	OUTL(dp, CR, CR_TXE | CR_RXE);
}


#define	SFE_EEPROM_DELAY(dp)	{INL(dp, EROMAR);INL(dp, EROMAR);}
#define	EE_CMD_READ	6
#define	EE_CMD_SHIFT	6

static uint16_t
sfe_read_eeprom(struct sfe_dev *dp, int offset)
{
	int	eedi;
	int	i;
	int	ret;

	/* ensure de-assert chip select */
	OUTL(dp, EROMAR, 0);
	SFE_EEPROM_DELAY(dp);
	OUTL(dp, EROMAR, EROMAR_EESK);
	SFE_EEPROM_DELAY(dp);

	/* assert chip select */
	offset |= EE_CMD_READ << EE_CMD_SHIFT;

	for (i = 8; i >= 0; i--) {
		/* make command */
		eedi = ((offset >> i) << EROMAR_EEDI_SHIFT) & EROMAR_EEDI;

		/* send 1 bit */
		OUTL(dp, EROMAR, EROMAR_EECS | eedi);
		SFE_EEPROM_DELAY(dp);
		OUTL(dp, EROMAR, EROMAR_EECS | eedi | EROMAR_EESK);
		SFE_EEPROM_DELAY(dp);
	}

	OUTL(dp, EROMAR, EROMAR_EECS);

	ret = 0;
	for (i=0; i<16; i++) {
		/* Get 1 bit */
		OUTL(dp, EROMAR, EROMAR_EECS);
		SFE_EEPROM_DELAY(dp);
		OUTL(dp, EROMAR, EROMAR_EECS | EROMAR_EESK);
		SFE_EEPROM_DELAY(dp);

		ret <<= 1;
		ret |= (INL(dp, EROMAR) >> EROMAR_EEDO_SHIFT) & 1;
	}

	OUTL(dp, EROMAR, 0);
	SFE_EEPROM_DELAY(dp);

	return ret;
}

static int
sfe_set_media(struct sfe_dev *dp)
{
	uint32_t	txcfg;
	uint32_t	rxcfg;
	uint32_t	pcr;

	DPRINTF(1, (CE_CONT, "%s: sfe_set_media: %s duplex, %d Mbps",
		dp->name,
		dp->full_duplex?"full":"half", dp->speed100?100:10));

	dp->tx_fill_threshold = TXFIFOSIZE / 4;			/* 1/4 FIFO */
	if (dp->speed100) {
		/* transmit starting threshold */
		dp->tx_drain_threshold = (TXFIFOSIZE/4)*3;	/* 3/4 FIFO */
		dp->rx_drain_threshold = RXFIFOSIZE/2;		/* 2/4 FIFO */
	} else {
		/* transmit starting threshold */
		dp->tx_drain_threshold = (TXFIFOSIZE/4);	/* 1/4 FIFO */
		dp->rx_drain_threshold = (RXFIFOSIZE/4)*3;	/* 3/4 FIFO */
	}

	/* fix tx_drain_theshold */
	if (dp->tx_drain_threshold >= TXFIFOSIZE - dp->tx_fill_threshold) {
		dp->tx_drain_threshold = TXFIFOSIZE - dp->tx_fill_threshold;
	}
	/* fix rx_drain_theshold; it have only 5bit-wide field */
	if (dp->rx_drain_threshold > 31 * RXCFG_DRTH_UNIT) {
		dp->rx_drain_threshold = 31 * RXCFG_DRTH_UNIT;
	}
	ASSERT(dp->tx_drain_threshold < 64*TXCFG_DRTH_UNIT);
	ASSERT(dp->tx_fill_threshold < 64*TXCFG_FLTH_UNIT);
	ASSERT(dp->rx_drain_threshold < 32*RXCFG_DRTH_UNIT);

	txcfg =	TXCFG_ATP |		/* auto padding */
		TXCFG_MXDMA_512 |	/* MAX DMA burst size */
		(dp->full_duplex ? (TXCFG_CSI | TXCFG_HBI) : 0) |
		(dp->tx_fill_threshold/TXCFG_FLTH_UNIT) << TXCFG_FLTH_SHIFT |
		dp->tx_drain_threshold/TXCFG_DRTH_UNIT;
	OUTL(dp, TXCFG, txcfg);

	rxcfg =	RXCFG_AEP | RXCFG_ARP |
		(dp->full_duplex ? RXCFG_ATX : 0) |
		RXCFG_MXDMA_512 |
		(dp->rx_drain_threshold/RXCFG_DRTH_UNIT) << RXCFG_DRTH_SHIFT;
	OUTL(dp, RXCFG, rxcfg);

	DPRINTF(1, (CE_CONT, "?%s: sfe_set_media: txcfg:%b rxcfg:%b",
		dp->name,
		txcfg, TXCFG_BITS, rxcfg, RXCFG_BITS));

	/* Flow control */
	if (dp->chip->chip_type == CHIPTYPE_DP83815) {
		pcr = INL(dp, PCR);
		if (dp->flow_control) {
			OUTL(dp, PCR, pcr | PCR_PSEN | PCR_PS_MCAST);
		}
		else {
			OUTL(dp, PCR,
				pcr & ~(PCR_PSEN | PCR_PS_MCAST | PCR_PS_DA));
		}
		DPRINTF(1, (CE_CONT,
			"?%s: PCR: %b", dp->name, INL(dp, PCR), PCR_BITS));
	}
	else if (dp->chip->chip_type == CHIPTYPE_SIS900) {
 
		if (dp->flow_control) {
			OUTL(dp, FLOWCTL, FLOWCTL_FLOWEN);
		}
		else {
			OUTL(dp, FLOWCTL, 0);
		}
		DPRINTF(1, (CE_CONT, "?%s: FLOWCTL: %b",
			dp->name, INL(dp, FLOWCTL), FLOWCTL_BITS));
	}
}
/* ======================================================================== */
/*
 * MII support routines
 */
/* ======================================================================== */

/* special PHY register for SIS900 */
#define	MII_CONFIG1	0x0010
#define	MII_CONFIG2	0x0011
#define	MII_MASK	0x0013
#define	MII_RESV	0x0014

static void
sfe_set_eq_sis630(struct sfe_dev *dp)
{
	uint16_t	reg14h;
	uint16_t	eq_value;
	uint16_t	max_value;
	uint16_t	min_value;
	int		i;
	uint8_t		rev;

	rev = dp->revid;

	if (!(rev == SIS630E_900_REV || rev == SIS630EA1_900_REV ||
	      rev == SIS630A_900_REV || rev ==  SIS630ET_900_REV) ) {
		/* it dont have a internal PHY */
		return;
	}

#ifdef TUNE_PHY_630
	if (dp->mii_state = MII_STATE_LINKUP) {
		reg14h = mii_read(dp, MII_RESV);
		mii_write(dp, MII_RESV, (0x2200 | reg14h) & 0xBFFF);

		eq_value = (0x00f8 & mii_read(dp, MII_RESV)) >> 3;
		max_value = min_value = eq_value;
		for (i = 1; i < 10; i++) {
			eq_value = (0x00F8 & mii_read(dp, MII_RESV)) >> 3;
			max_value = max(eq_value, max_value);
			min_value = min(eq_value, min_value);
		}

		/* 630E rule to determine the equalizer value */
		if (rev == SIS630E_900_REV || rev == SIS630EA1_900_REV ||
		    rev == SIS630ET_900_REV) {
			if (max_value < 5) {
				eq_value = max_value;
			}
			else if (5 <= max_value && max_value < 15) {
				eq_value = max(max_value + 1, min_value + 2);
			}
			else if (15 <= max_value) {
				eq_value = max(max_value + 5, min_value + 6);
			}
		}
		/* 630B0&B1 rule to determine the equalizer value */
		else
		if (rev == SIS630A_900_REV && 
			(dp->bridge_revid == SIS630B0 ||
			 dp->bridge_revid == SIS630B1)) {

			if (max_value == 0) {
				eq_value = 3;
			}
			else {
				eq_value = (max_value + min_value + 1)/2;
			}
		}
		/* write equalizer value and setting */
		reg14h = mii_read(dp, MII_RESV);
		reg14h = (reg14h & ~0x00f8) | ((eq_value << 3) & 0x00f8);
		reg14h = (reg14h | 0x6000) & ~0x0200;
		mii_write(dp, MII_RESV, reg14h);
	}
	else {
		reg14h = mii_read(dp, MII_RESV);
		if (rev== SIS630A_900_REV && 
			 (dp->bridge_revid == SIS630B0 ||
			  dp->bridge_revid == SIS630B1)) {

			mii_write(dp, MII_RESV, (reg14h | 0x2200) & ~0x4000);
		}
		else {
			mii_write(dp, MII_RESV, (reg14h | 0x2000) & ~0x4000);
		}
	}
#endif /* TUNE_PHY_630 */
	return;
}

static int
sfe_mii_config(struct sfe_dev *dp)
{
	uint16_t	mii_stat;
	uint16_t	val;
	int		i, j;

	DPRINTF(2, (CE_CONT, "%s: sfe_mii_config: called", dp->name));

	if (dp->chip->chip_type == CHIPTYPE_SIS900) {
		/* workaround for ICS1893 PHY */
		if (dp->mii_phyid == 0x0015F440) {
			mii_write(dp, 0x0018, 0xD200);
		}

		if (dp->revid == SIS630E_900_REV) {
			/*
			 * SiS 630E has some bugs on default value
			 * of PHY registers
			 */
			mii_write(dp, MII_AN_ADVERT, 0x05e1);
			mii_write(dp, MII_CONFIG1, 0x0022);
			mii_write(dp, MII_CONFIG2, 0xff00);
			mii_write(dp, MII_MASK,    0xffc0);
		}

		sfe_set_eq_sis630(dp);
	}

	if (dp->mii_fixedmode) {
		val = 0;
		if (dp->full_duplex) {
			val |= MII_CONTROL_FDUPLEX;
		}
		if (dp->speed100) {
			val |= MII_CONTROL_100MB;
		}
		mii_write(dp, MII_CONTROL, val);
		return 0;
	}

	/*
	 * Set advertisement register
	 */
	mii_stat = mii_read(dp, MII_STATUS);
	DPRINTF(2, (CE_CONT, "%s: sfe_mii_config: MII_STATUS reg:%b",
		dp->name, mii_stat, MII_STATUS_BITS));

	if ((mii_stat & MII_STATUS_ABILITY) == 0) {
		/* it's funny */
		cmn_err(CE_WARN, "%s: wrong ability bits: mii_status:%b",
			dp->name, mii_stat, MII_STATUS_BITS);
		return -1;
	}

	/* Do not change rest of ability bits in advert reg */
	val = mii_read(dp, MII_AN_ADVERT) & ~MII_ABILITY;

	if ((mii_stat & MII_STATUS_100_BASE_T4) != 0) {
		val |= MII_ABILITY_100BASE_T4;
	}
	if ((mii_stat & MII_STATUS_100_BASEX_FD) != 0) {
		val |= MII_ABILITY_100BASE_TX_FD;
	}
	if ((mii_stat & MII_STATUS_100_BASEX) != 0) {
		val |= MII_ABILITY_100BASE_TX;
	}
	if ((mii_stat & MII_STATUS_10_FD) != 0) {
		val |= MII_ABILITY_10BASE_T;
	}
	if ((mii_stat & MII_STATUS_10) != 0) {
		val |= MII_ABILITY_10BASE_T_FD;
	}
#ifdef NO_PAUSE
	val &= ~ MII_ABILITY_PAUSE;
#endif
	DPRINTF(2, (CE_CONT, "%s: sfe_mii_config: setting MII_AN_ADVERT reg:%b",
		dp->name, val, MII_ABILITY_BITS));

	mii_write(dp, MII_AN_ADVERT, val);

	return 0;
}

static void
sfe_mii_link_watcher(struct sfe_dev *dp)
{
	uint16_t	mii_stat;
	uint16_t	advert;
	uint16_t	lpable;
	uint16_t	val;

	/* read PHY status */
	mii_stat = mii_read(dp, MII_STATUS);
	DPRINTF(4, (CE_CONT,
	"%s: sfe_mii_link_watcher: called: mii_state:%d MII_STATUS reg:%b",
		dp->name, dp->mii_state,
		mii_stat, MII_STATUS_BITS));

	if (dp->mii_state == MII_STATE_RESETTING) {
		if (--dp->mii_timer > 0) {
			/* wait for time-up */
			goto next;
		}
		/* Timer expired, ensure reset bit is not set */
		if ((mii_read(dp, MII_CONTROL) & MII_CONTROL_RESET) != 0) {
			/* reset have not done, try reset again */
			cmn_err(CE_WARN, "%s: resetting mii not complete.",
				dp->name);
			goto reset_phy;
		}
		/* Configure PHY registers */
		if (sfe_mii_config(dp) != 0) {
			goto reset_phy;
		}

		if (dp->mii_fixedmode) {
			dp->mii_state = MII_STATE_LINKDOWN;
			dp->mii_timer = MII_LINKDOWN_TIMEOUT;
			goto next;
		}
		else {
			/* Issue auto-negotiation command */
			goto autonego;
		}
	}

	if (dp->mii_state == MII_STATE_AUTONEGOTIATING) {
		/*
		 * Autonegotiation in progress
		 */
		dp->mii_timer--;

		if ((mii_stat & MII_STATUS_REMFAULT) != 0) {
			/*
			 * link partner does not have auto nego capability
			 * What do we do ?
			 */
			cmn_err(CE_CONT, "?%s: auto nego remote fault",
				dp->name);
			goto reset_phy;
		}

		if ((mii_stat & MII_STATUS_ANDONE) == 0) {
			if (dp->mii_timer == 0) {
				/*
				 * Auto-negotiation timed out,
				 * Reset PHY and try again.
				 */
				if (!dp->mii_supress_msg) {
					cmn_err(CE_WARN,
					"%s: autonegotiation timed out.",
					dp->name);
					dp->mii_supress_msg = TRUE;
				}
				goto reset_phy;
			}
			/*
			 * Auto-negotiation in progress. Wait.
			 */
			goto next;
		}
		/*
		 * Auto-negotiation have done.
		 * Assume that we are link down state and fall through.
		 */
		dp->mii_state = MII_STATE_LINKDOWN;
		dp->mii_timer = MII_LINKDOWN_TIMEOUT;
		cmn_err(CE_CONT, "?%s: auto-negotiation done", dp->name);

		/*
		 * 06/02/2002
		 * Some PHY needs delay before reading LPAR reg
		 */
		goto next;
	}

	dp->mii_supress_msg = FALSE;

	if (dp->mii_state != MII_STATE_LINKDOWN &&
	    ((mii_stat & MII_STATUS_LINKUP) == 0)) {
		/*
		 * link going down
		 */
		cmn_err(CE_NOTE, "%s: link down detected: mii_stat:%b",
			dp->name, mii_stat, MII_STATUS_BITS);

		if (dp->chip->chip_type == CHIPTYPE_SIS900) {
			if (dp->mii_phyid == 0x001D8000) {
				/* wordaround for internal PHY */
				goto reset_phy;
			}
		}

		dp->mii_state = MII_STATE_LINKDOWN;
		dp->mii_timer = MII_LINKDOWN_TIMEOUT;

		if (dp->chip->chip_type == CHIPTYPE_SIS900) {
			sfe_set_eq_sis630(dp);
		}
	}
	else if (dp->mii_state != MII_STATE_LINKUP &&
		((mii_stat & MII_STATUS_LINKUP) != 0)) {
		/*
		 * Link going up
		 */
		dp->mii_state = MII_STATE_LINKUP;

		DPRINTF(1, (CE_CONT, "?%s: link up detected: mii_stat:%b",
			dp->name, mii_stat, MII_STATUS_BITS));

		if (!dp->mii_fixedmode) {
			/*
			 * Auto negosiation
			 */
			/* determine full/half and 100mbps/10mbps */
			advert = mii_read(dp, MII_AN_ADVERT);
			lpable = mii_read(dp, MII_AN_LPABLE);

			DPRINTF(1, (CE_CONT,
			"?%s: sfe_mii_link_watcher: advert:%b, lpable:%b",
				dp->name,
				advert, MII_ABILITY_BITS,
				lpable, MII_ABILITY_BITS));
			/*
			 * configure link mode according to AN priority.
			 */	
			val = advert & lpable;
			if ((val & MII_ABILITY_100BASE_TX_FD) != 0) {
				/* 100BaseTx & fullduplex */
				dp->speed100    = TRUE;
				dp->full_duplex = TRUE;
				dp->flow_control =
				      (val & MII_ABILITY_PAUSE) ? TRUE : FALSE;
			}
			else if ((val & MII_ABILITY_100BASE_TX) != 0) {
				/* 100BaseTx & half duplex */
				dp->speed100    = TRUE;
				dp->full_duplex = FALSE;
				dp->flow_control= FALSE;
			}
			else if ((val & MII_ABILITY_10BASE_T_FD) != 0) {
				/* 10BaseT & full duplex */
				dp->speed100    = FALSE;
				dp->full_duplex = TRUE;
				dp->flow_control =
				      (val & MII_ABILITY_PAUSE) ? TRUE : FALSE;
			}
			else if ((val & MII_ABILITY_10BASE_T) != 0) {
				/* 10BaseT & half duplex */
				dp->speed100    = FALSE;
				dp->full_duplex = FALSE;
				dp->flow_control= FALSE;
			}
			else {
				/* No solution */
				/* not yet workaround for RTL8200 */
				cmn_err(CE_WARN,
	"%s: link up but auto-nego failed, no common mode with link partner, "
					"advert:%b lpable:%b",
					dp->name,
					advert, MII_ABILITY_BITS,
					lpable, MII_ABILITY_BITS);
				goto reset_phy;
			}

			mutex_enter(&dp->intrlock);
			sfe_set_media(dp);
			mutex_exit(&dp->intrlock);

			if (dp->chip->chip_type == CHIPTYPE_SIS900) {
				sfe_set_eq_sis630(dp);
			}
		}

		/*
		 * MII_CONTROL_100MB and  MII_CONTROL_FDUPLEX are ignored
		 * when MII_CONTROL_ANEN is set.
		 */
		cmn_err(CE_CONT,
			"?%s: Link up: %d Mbps %s duplex %s flow control",
			dp->name,
			dp->speed100 ? 100 : 10,
			dp->full_duplex ? "full" : "half",
			dp->flow_control ? "with" : "without");
	}
	else {
		/* link status not changed */
		if (!dp->mii_fixedmode &&
		     (dp->mii_state == MII_STATE_LINKDOWN)) {
			dp->mii_timer--;
			if (dp->mii_timer <= 0) {
				goto reset_phy;
			}
		}
	}
	goto next;

reset_phy:
	if (!dp->mii_supress_msg) {
		cmn_err(CE_CONT, "?%s: resetting PHY", dp->name);
	}
	dp->mii_state = MII_STATE_RESETTING;
	dp->mii_timer = MII_RESET_TIMEOUT;

	mii_write(dp, MII_CONTROL, MII_CONTROL_RESET);
	goto next;

autonego:
	if (!dp->mii_supress_msg) {
		cmn_err(CE_CONT, "?%s: start auto-negotiation", dp->name);
	}
	dp->mii_state = MII_STATE_AUTONEGOTIATING;
	dp->mii_timer = MII_AUTONEGO_TIMEOUT;

	val = mii_read(dp, MII_CONTROL);
	mii_write(dp, MII_CONTROL,
		 val | MII_CONTROL_ANE | MII_CONTROL_RSAN);
	/* fall through */

next:
	dp->link_watcher_id =
		timeout((void (*)(void *))& sfe_mii_link_watcher,
				(void *)dp, LINK_WATCH_INTERVAL);

	return;
}

static int
sfe_mii_init(struct sfe_dev *dp)
{
	int		phy;
	uint16_t	adv;
	uint16_t	status;
	uint32_t	phyid;
	uint16_t	val;

	DPRINTF(3, (CE_CONT, "%s: sfe_mii_init: called", dp->name));

	dp->mii_phy_addr = -1;

	if (dp->chip->chip_type == CHIPTYPE_SIS900) {
		/*
		 * Scan PHY
		 */
		for (phy = 0; phy < 32; phy++) {
			dp->mii_phy_addr = phy;

			status = mii_read(dp, MII_STATUS);
			status = mii_read(dp, MII_STATUS);

			if (status != 0xffff && status != 0x0000) {
				goto PHY_found;
			}
		}

		cmn_err(CE_WARN, "!%s: failed to find PHY", dp->name);
		return -1;
	}
PHY_found:
	phyid  = mii_read(dp, MII_PHYIDH) << 16;
	phyid |= mii_read(dp, MII_PHYIDL);
	adv = mii_read(dp, MII_AN_ADVERT);
	val = mii_read(dp, MII_CONTROL);
	cmn_err(CE_CONT, "!%s: PHY (0x%08x) found at %d,"
			"control:%b, status:%b, advert:%b, lpar:%b",
		dp->name, phyid, dp->mii_phy_addr,
		val, MII_CONTROL_BITS,
		status, MII_STATUS_BITS,
		adv, MII_ABILITY_BITS,
		mii_read(dp, MII_AN_LPABLE),
		MII_ABILITY_BITS);

	dp->mii_phyid = phyid & 0xfffffff0;

	/* reset PHY */
	dp->mii_state = MII_STATE_RESETTING;
	dp->mii_timer = MII_RESET_TIMEOUT;
	mii_write(dp, MII_CONTROL, MII_CONTROL_RESET);

	/* schedule first call of sfe_link_watcher */
	dp->link_watcher_id =
		timeout((void (*)(void *))sfe_mii_link_watcher,
				(void *)dp, LINK_WATCH_INTERVAL);
	return 0;
}

static void
sfe_mii_stop(struct sfe_dev *dp)
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
