/* %W% %E% ported by Masayuki Murayama (KHF04453@nifty.ne.jp) */

/*
 *  A SiS 900/7016 PCI Fast Ethernet driver for Solaris
 *  Revised from Linux sis900.c
 *
 *  Copyright (C) 2001  Masayuki Murayama (KHF04453@nifty.ne.jp)
 *
 *  CAUTION: NO WARRANTY
 *  This software may be used and distributed according to the terms
 *  of the GNU Public License, incorporated herein by reference.
 */

/*
 Change log:
 */

/*
 * Solaris System Header files.
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

#include <sys/pci.h>
/*#include <sys/miiregs.h>*/

#include "sisreg.h"

char	ident[] = "sis900 v" VERSION;
char	_depends_on[] = {"misc/gld"};


#ifdef SOLARIS

#define	FALSE	(0)
#define	TRUE	(!FALSE)
/* typedef	unsigned int	boolean_t;	/* */

/* linux type definition compatibility */
typedef	uint32_t	u32;
typedef	uint16_t	u16;
typedef	uint8_t		u8;

/* linux macro definition compatibility */
#define	ARRAY_SIZE(a)	(sizeof(a)/sizeof((a)[0]))

/* printing kernel messages emulation */
#define printk  cmn_err
#define KERN_INFO	CE_CONT,
#define KERN_DEBUG	CE_CONT,
#define KERN_NOTICE	CE_CONT,
#define KERN_WARNING	CE_WARN,
#define KERN_ERR	CE_PANIC,

/* I/O instructions */
#define	OUTB(v, p)	outb((int)(p), v)
#define	OUTW(v, p)	outw((int)(p), v)
#define	OUTL(v, p)	outl((int)(p), v)
#define	INB(p)		inb((int)(p))
#define	INW(p)		inw((int)(p))
#define	INL(p)		inl((int)(p))
#endif /* SOLARIS */

/*
 * For debugging
 */
#ifdef DEBUG_LEVEL
static int sis900_debug = DEBUG_LEVEL;
				/* 1 normal messages, 0 quiet .. 7 verbose. */
#define	DPRINTF(n, args...)	\
	if (sis900_debug > (n)) cmn_err(CE_CONT, args)
#else
#define	DPRINTF(n, args...)
#endif

/*
 * Patchable parameters
 */
static int sis_multicast_filter_limit = 128;
static int sis_tx_copybreak = 0 /* ETHERMIN */;
static int sis_rx_copybreak = 0;

#ifdef LINUX
#define	TX_BUF_SIZE     1536
#define	RX_BUF_SIZE     1536
#define	NUM_TX_DESC	16		/* Number of Tx descriptor registers. */
#define	NUM_RX_DESC	16		/* Number of Rx descriptor registers. */
#endif
#ifdef SOLARIS
#define	PKT_BUF_SZ	1536		/* >= ETHERMAX + ETHERFCSL */
#define	NUM_TX_DESC	64		/* Number of Tx descriptor registers. */
#define	NUM_RX_DESC	128		/* Number of Rx descriptor registers. */
#endif
#define	TX_TOTAL_SIZE	(NUM_TX_DESC * sizeof(BufferDesc))
#define	RX_TOTAL_SIZE	(NUM_RX_DESC * sizeof(BufferDesc))

#define	MAXFRAGMENTS	(NUM_TX_DESC/4)
static int	sis_tx_fragments = MAXFRAGMENTS;

/*
 * Usefull macros
 */
#define	OUR_INTR_BITS	\
	(RxSOVR|RxORN|RxERR|RxOK|TxURN|TxERR|TxIDLE)

#define TX_TIMEOUT		(drv_usectohz(10*1000000))	/* was 4 sec */
#define TX_TIMEOUT_INTERVAL	(drv_usectohz(1*1000000))

/* SiS 900 is capable of 32 bits BM DMA */
#define SIS900_DMA_MASK 0xffffffff

enum {
	SIS_900 = 0,
	SIS_7016
};
static char	*card_names[] = {
	"SiS 900 PCI Fast Ethernet",
	"SiS 7016 PCI Fast Ethernet"
};

#ifdef SOLARIS
#define	PCI_ANY_ID	0xffff
struct pci_device_id {
	uint16_t	venid;
	uint16_t	devid;
	uint16_t	subvenid;
	uint16_t	subsysid;
	uint8_t		pad0;
	uint8_t		pad1;
	uint8_t		driver_data;
};
#endif
static struct pci_device_id sis900_pci_tbl [] /*__devinitdata*/ = {
	{PCI_VENDOR_ID_SI, PCI_DEVICE_ID_SI_900,
	 PCI_ANY_ID, PCI_ANY_ID, 0, 0, SIS_900},
	{PCI_VENDOR_ID_SI, PCI_DEVICE_ID_SI_7016,
	 PCI_ANY_ID, PCI_ANY_ID, 0, 0, SIS_7016},
	{0,}
};

static struct mii_chip_info {
	const char	*name;
	uint16_t	phy_id0;
	uint16_t	phy_id1;
	uint8_t 	phy_types;
#define	HOME 	0x01
#define LAN	0x02
#define MIX	0x03
} mii_chip_table[] = {
	{ "SiS 900 Internal MII PHY", 		0x001d, 0x8000, LAN },
	{ "SiS 7014 Physical Layer Solution", 	0x0016, 0xf830, LAN },
	{ "AMD 79C901 10BASE-T PHY",  		0x0000, 0x6B70, LAN },
	{ "AMD 79C901 HomePNA PHY",		0x0000, 0x6B90, HOME},
	{ "ICS LAN PHY",			0x0015, 0xF440, LAN },
	{ "NS 83851 PHY",			0x2000, 0x5C20, MIX },
	{ "Realtek RTL8201 PHY",		0x0000, 0x8200, LAN },
};

struct mii_phy {
	struct mii_phy	*next;
	int		phy_addr;
	uint16_t	phy_id0;
	uint16_t	phy_id1;
	uint16_t	status;
	uint8_t		phy_types;
};

typedef struct _BufferDesc {
	uint32_t	link;
	uint32_t	cmdsts;
	uint32_t	bufptr;
} BufferDesc;

#ifdef LINUX
struct sis900_private {
	struct net_device_stats stats;
	struct pci_dev * pci_dev;

	spinlock_t lock;

	struct mii_phy * mii;
	struct mii_phy * first_mii; /* record the first mii structure */
	unsigned int cur_phy;

	struct timer_list timer; /* Link status detection timer. */
	u8     autong_complete; /* 1: auto-negotiate complete  */

	unsigned int cur_rx, dirty_rx; /* producer/comsumer pointers for Tx/Rx ring */
	unsigned int cur_tx, dirty_tx;

	/* The saved address of a sent/receive-in-place packet buffer */
	struct sk_buff *tx_skbuff[NUM_TX_DESC];
	struct sk_buff *rx_skbuff[NUM_RX_DESC];
	BufferDesc *tx_ring;
	BufferDesc *rx_ring;

	dma_addr_t tx_ring_dma;
	dma_addr_t rx_ring_dma;

	unsigned int tx_full;			/* The Tx queue is full.    */
};
#endif /* LINUX */

#ifdef SOLARIS
struct sis900_stats {
	uint32_t	intr;

	uint32_t	rx_bytes ;
	uint32_t	rx_crc_errors;
	uint32_t	rx_dropped;
	uint32_t	rx_errors;
	uint32_t	rx_fifo_errors;
	uint32_t	rx_frame_errors;
	uint32_t	rx_missed_errors ;
	uint32_t	rx_packets;
	uint32_t	rx_runt_errors;
	uint32_t	rx_toolong_errors;

	uint32_t	collisions;
	uint32_t	tx_first_coll;
	uint32_t	tx_multi_coll;
	uint32_t	collisions16;
	uint32_t	tx_aborted_errors;
	uint32_t	tx_buf_mapped;
	uint32_t	tx_carrier_errors;
	uint32_t	tx_defer;
	uint32_t	tx_dropped;
	uint32_t	tx_errors;
	uint32_t	tx_fifo_errors;
	uint32_t	tx_window_errors;
	uint32_t	tx_heartbeat_errors;
};


#define	SIS_LOCAL_BUF_INIT	(NUM_RX_DESC*2)
#define	SIS_LOCAL_BUF_MAX	64*1024

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
	struct sis900_private	*devp;
};

#define	SISMAXMC		GLD_MAX_MULTICAST
#define	SISMCALLOC		(sizeof(struct ether_addr) * SISMAXMC)

typedef	long		seqnum_t;	/* should be signed */

#define	SUB(x, y)	((seqnum_t)((x) - (y)))

struct sis900_private {
	dev_info_t		*dip;
	gld_mac_info_t		*macinfo;
	char			name[32];
	void			*base_addr;
	ddi_acc_handle_t	regs_handle;
	ddi_iblock_cookie_t	iblock_cookie;

	struct ether_addr	cur_addr;
	struct ether_addr	dev_addr;

	/* Descriptor rings */
	BufferDesc		*rx_ring;
	BufferDesc		*tx_ring;
	uint32_t		rx_ring_dma;	/* dma address from PCI bus */
	uint32_t		tx_ring_dma;	/* dma address from PCI bus */
	ddi_dma_handle_t	desc_dma_handle;
	ddi_acc_handle_t	desc_acc_handle;

	seqnum_t		cur_rx;	/* Producer/consumer ring indices */
	seqnum_t		dirty_rx;
	seqnum_t		cur_tx;
	seqnum_t		dirty_tx;

	/* locks for RX and TX */
	kmutex_t		intrlock;
	kmutex_t		xmitlock;
	kcondvar_t		drain_cv;

	/* interrupt service */
	boolean_t		intr_busy;

	/* Rx */
	struct lbuf		*rx_lbp[NUM_RX_DESC];
	clock_t			last_rx;

	/* Tx */
	mblk_t 			*tx_mp[NUM_TX_DESC];
	struct lbuf		*tx_lbp[NUM_TX_DESC];
	ddi_dma_handle_t	tx_dma_handle_used[NUM_TX_DESC];
	int			tx_reserved;
	clock_t			trans_start;
	int			tx_busy;
	boolean_t		tx_blocked;
	boolean_t		start;
#ifdef TXSOFTPAD
	uint32_t		tx_pad_dma;
#endif
	/* timer and watchdog */
	timeout_id_t		timer_id;
	timeout_id_t		timeout_id;

	/* local buffer management */
	struct lbuf		*buf_free_list;
	kmutex_t		buflock;
	int			buf_allocated;
	int			buf_free;

	/* free dma handle management */
	kmutex_t		dma_handle_lock;
	int			dma_handle_free;
	ddi_dma_handle_t	dma_handle[NUM_TX_DESC];
#define		SIS_MAX_BUF	1000

	/* HW info and status */
	uint8_t			revid;	/* revision from PCI configration */

	/* These values are keep track of the transceiver/media in use. */
	uint_t		autong_complete:1; /* 1: auto-negotiate complete  */
	uint_t		carrier_ok:1;
	uint_t		full_duplex:1;	/* 0: half 1: full */
	uint_t		speed:8;	/* Mbps */

	/* MII transceiver section. */
	struct mii_phy		*mii;		/* ptr to default phy */
	struct mii_phy		*first_mii;/* record the first mii structure */
	unsigned int		cur_phy;	/* phy addr of default phy */
	struct mii_phy		mii_list[32];	/* data area */

	/* multicast list */
	int			mc_count;
	struct ether_addr	*mc_list;
	int			flags;
#define		IFF_PROMISC	0x01
#define		IFF_ALLMULTI	0x02

	/* statistcs */
	struct sis900_stats	stats;
};
#endif /* SOLARIS */

/* private functions */
static int sis900_open(struct sis900_private *);
static int sis900_mii_probe (struct sis900_private *);
static void sis900_init_rxfilter (struct sis900_private *);
static u16 read_eeprom(long ioaddr, int location);
static u16 mdio_read(struct sis900_private *, int, int);
static void mdio_write(struct sis900_private *, int, int, int);
static void sis900_timer(struct sis900_private *);
static void sis900_check_mode (struct sis900_private *, struct mii_phy *);
static void sis900_tx_timeout(struct sis900_private *);
static void sis900_init_tx_ring(struct sis900_private *);
static void sis900_init_rx_ring(struct sis900_private *);
static int sis900_start_xmit(struct sis900_private *, mblk_t *);
static int sis900_rx(struct sis900_private *);
static void sis900_finish_xmit (struct sis900_private *);
static void sis900_interrupt(gld_mac_info_t *);
static int sis900_close(struct sis900_private *);
static u16 sis900_compute_hashtable_index(u8 *addr, uint8_t revision);
static void sis900_set_rx_mode(struct sis900_private *);
static void sis900_reset(struct sis900_private *);
static void sis630_set_eq(struct sis900_private *, uint8_t revision);
static u16 sis900_default_phy(struct sis900_private *);
static void sis900_set_capability(struct sis900_private *, struct mii_phy *);
static u16 sis900_reset_phy(struct sis900_private *, int phy_addr);
static void sis900_auto_negotiate(struct sis900_private *, int phy_addr);
static void sis900_set_mode (long ioaddr, int speed, int duplex);
static void sis900_read_mode(struct sis900_private *, int *speed, int *duplex);

static int sis900_alloc_ring(struct sis900_private *sis_priv);
static void sis900_free_ring(struct sis900_private *sis_priv);
static int sis900_init_one(struct sis900_private *, struct pci_device_id *);

/* DDI/DKI functions */
static int sisprobe(dev_info_t *);
static int sisattach(dev_info_t *, ddi_attach_cmd_t);
static int sisdetach(dev_info_t *, ddi_detach_cmd_t);

/* GLD interfaces */
static int sis_reset(gld_mac_info_t *);
static int sis_start(gld_mac_info_t *);
static int sis_stop(gld_mac_info_t *);
static int sis_set_mac_address(gld_mac_info_t *, unsigned char *);
static int sis_set_multicast(gld_mac_info_t *, struct ether_addr *, int);
static int sis_set_promiscuous(gld_mac_info_t *, int);
static int sis_get_stats(gld_mac_info_t *, struct gld_stats *);
static int sis_send(gld_mac_info_t *, mblk_t *);
static u_int sis_interrupt(gld_mac_info_t *);


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
	4,					/* dma_attr_align */
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

static	struct module_info sisminfo = {
	0,			/* mi_idnum */
	"sis",			/* mi_idname */
	0,			/* mi_minpsz */
	ETHERMTU,		/* mi_maxpsz */
	32*1024,		/* mi_hiwat */
	1,			/* mi_lowat */
};

static	struct qinit sisrinit = {
	(int (*)()) NULL,	/* qi_putp */
	gld_rsrv,		/* qi_srvp */
	gld_open,		/* qi_qopen */
	gld_close,		/* qi_qclose */
	(int (*)()) NULL,	/* qi_qadmin */
	&sisminfo,		/* qi_minfo */
	NULL			/* qi_mstat */
};

static	struct qinit siswinit = {
	gld_wput,		/* qi_putp */
	gld_wsrv,		/* qi_srvp */
	(int (*)()) NULL,	/* qi_qopen */
	(int (*)()) NULL,	/* qi_qclose */
	(int (*)()) NULL,	/* qi_qadmin */
	&sisminfo,		/* qi_minfo */
	NULL		/* qi_mstat */
};

static struct streamtab	sis_info = {
	&sisrinit,	/* st_rdinit */
	&siswinit,	/* st_wrinit */
	NULL,		/* st_muxrinit */
	NULL		/* st_muxwrinit */
};

static	struct cb_ops cb_sis_ops = {
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
	&sis_info,	/* cb_stream */
	D_NEW|D_MP	/* cb_flag */
};

static	struct dev_ops sis_ops = {
	DEVO_REV,	/* devo_rev */
	0,		/* devo_refcnt */
	gld_getinfo,	/* devo_getinfo */
	nulldev,	/* devo_identify */
	sisprobe,	/* devo_probe */
	sisattach,	/* devo_attach */
	sisdetach,	/* devo_detach */
	nodev,		/* devo_reset */
	&cb_sis_ops,	/* devo_cb_ops */
	NULL,		/* devo_bus_ops */
	ddi_power	/* devo_power */
};

static struct modldrv modldrv = {
	&mod_driverops,	/* Type of module.  This one is a driver */
	ident,
	&sis_ops,	/* driver ops */
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

	DPRINTF(2,  "sis: _init: called");
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

	DPRINTF(2,  "sis: _fini: called");
	status = mod_remove(&modlinkage);
	return (status);
}

int
_info(struct modinfo *modinfop)
{
	return (mod_info(&modlinkage, modinfop));
}

/*
 * Probe for device.
 */
/*ARGSUSED*/
static int
sisprobe(dev_info_t *dip)
{
	return (DDI_PROBE_SUCCESS);
}


/*
 * Interface exists: make available by filling in network interface
 * record.  System will initialize the interface when it is ready
 * to accept packets.
 */
static int
sisattach(dev_info_t *dip, ddi_attach_cmd_t cmd)
{
	struct sis900_private	*sis_priv;
	int			i;
	ddi_iblock_cookie_t	c;
	ddi_acc_handle_t	conf_handle;
	uint16_t		comm;
	gld_mac_info_t		*macinfo;
	int			ret;
	int			vid;
	int			did;
	int			svid;
	int			ssid;
	struct pci_device_id	*p;

	DPRINTF(2, "sisattach: called\n");

	if (cmd == DDI_ATTACH) {
		DPRINTF(2, "sisattach: called cmd:ATTACH\n");
	
		macinfo = gld_mac_alloc(dip);
		if (macinfo == NULL) {
			return DDI_FAILURE;
		}

		/*
		 * Allocate soft data structure
		 */
		sis_priv = (struct sis900_private *)
			kmem_zalloc(sizeof(*sis_priv) + SISMCALLOC, KM_SLEEP);
		if (sis_priv == NULL) {
			gld_mac_free(macinfo);
			return DDI_FAILURE;
		}
		sis_priv->mc_count = 0;
		sis_priv->mc_list = (struct ether_addr *) &sis_priv[1];

		sis_priv->dip = dip;
		sis_priv->macinfo = macinfo;
		sprintf(sis_priv->name, "%s%d",
			ddi_driver_name(dip), ddi_get_instance(dip));

		/* GLD ver2 don't lock on xmit */
		macinfo->gldm_devinfo	   = dip;
		macinfo->gldm_private	   = (caddr_t)sis_priv;

		macinfo->gldm_reset        = sis_reset;
		macinfo->gldm_start        = sis_start;
		macinfo->gldm_stop         = sis_stop;
		macinfo->gldm_set_mac_addr = sis_set_mac_address;
		macinfo->gldm_send         = sis_send;
		macinfo->gldm_set_promiscuous = sis_set_promiscuous;
		macinfo->gldm_get_stats    = sis_get_stats;
		macinfo->gldm_ioctl        = NULL; 
		macinfo->gldm_set_multicast= sis_set_multicast;
		macinfo->gldm_intr         = sis_interrupt;
		macinfo->gldm_mctl         = NULL;

		macinfo->gldm_ident   = ident;
		macinfo->gldm_type    = DL_ETHER;
		macinfo->gldm_minpkt  = 0;
		macinfo->gldm_maxpkt  = ETHERMTU;
		macinfo->gldm_addrlen = ETHERADDRL;
		macinfo->gldm_saplen  = -2;
		macinfo->gldm_ppa     = ddi_get_instance(dip);


		/*
		 * Get iblock cookie
		 */
		if (ddi_get_iblock_cookie(dip, 0, &c) != DDI_SUCCESS) {
			cmn_err(CE_CONT,
				"sisattach: ddi_get_iblock_cookie: failed");
			goto err_free_private;
		}

		/*
		 * Initialize mutex's for this device.
		 */
		sis_priv->iblock_cookie = c;
		macinfo->gldm_cookie = c;

		mutex_init(&sis_priv->intrlock, NULL, MUTEX_DRIVER, (void *)c);
		mutex_init(&sis_priv->xmitlock, NULL, MUTEX_DRIVER, (void *)c);
		mutex_init(&sis_priv->buflock, NULL, MUTEX_DRIVER, (void *)c);
		mutex_init(&sis_priv->dma_handle_lock, NULL, MUTEX_DRIVER, (void *)c);
		cv_init(&sis_priv->drain_cv, NULL, CV_DRIVER, NULL);

		/*
		 * Map in the device registers into I/O space.
		 */
		if (ddi_regs_map_setup(dip, 1, (caddr_t *)&sis_priv->base_addr,
			0, 0, &dev_attr, &sis_priv->regs_handle)) {
			cmn_err(CE_WARN, "sis%d: ddi_regs_map_setup failed",
				ddi_get_instance(dip));
			goto err_free_locks;
		}

		/*
		 * Make sure the I/O access and memory access, master enable.
		 * Bits are set in the config command register
		 */
		if (pci_config_setup(dip, &conf_handle) != DDI_SUCCESS) {
			cmn_err(CE_WARN, "sis%d: ddi_regs_map_setup failed",
				ddi_get_instance(dip));
			goto err_free_regs;
		}
		vid  = pci_config_get16(conf_handle, PCI_CONF_VENID);
		did  = pci_config_get16(conf_handle, PCI_CONF_DEVID);
		svid = pci_config_get16(conf_handle, PCI_CONF_SUBVENID);
		ssid = pci_config_get16(conf_handle, PCI_CONF_SUBSYSID);
		sis_priv->revid = pci_config_get8(conf_handle, PCI_CONF_REVID);
		comm = pci_config_get16(conf_handle, PCI_CONF_COMM);
		comm |= PCI_COMM_IO | PCI_COMM_ME;
		pci_config_put16(conf_handle, PCI_CONF_COMM, comm);

		pci_config_teardown(&conf_handle);

		/* initialize chip */
		for (i=0, p=sis900_pci_tbl;
				i<ARRAY_SIZE(sis900_pci_tbl); i++, p++) {

			if ((p->venid==PCI_ANY_ID || p->venid==vid) && 
			    (p->devid==PCI_ANY_ID || p->devid==did) &&
			    (p->subvenid==PCI_ANY_ID || p->subvenid==svid) && 
			    (p->subsysid==PCI_ANY_ID || p->subsysid==ssid)) {
				/* found */
				goto chip_found;
			}
		}
		/* chip not found */
		cmn_err(CE_WARN, "%s: attach: error: "
				"wrong PCI venid/devid (0x%x, 0x%x)",
				sis_priv->name, vid, did);
		goto err_free_regs;
chip_found:
		if (sis900_init_one(sis_priv, p) != 0) {
			goto err_free_regs;
		}

		/* copy mac address */
		sis_priv->cur_addr = sis_priv->dev_addr;
		macinfo->gldm_vendor_addr =
				sis_priv->dev_addr.ether_addr_octet;
		macinfo->gldm_broadcast_addr =
				etherbroadcastaddr.ether_addr_octet;

		/* allocate tx and rx resources */
		if (sis900_alloc_ring(sis_priv) != 0) {
			goto err_free_regs;
		}

		/*
		 * Add interrupt to system.
		 */
		if (gld_register(dip, "sis", macinfo) != DDI_SUCCESS) {
			goto err_free_ring;
		}

		if (ddi_add_intr(dip, 0, NULL, NULL, gld_intr,
					(caddr_t)macinfo) != DDI_SUCCESS) {
			ddi_regs_map_free(&sis_priv->regs_handle);
			cmn_err(CE_WARN, "%s: ddi_add_intr failed", sis_priv->name);
			goto err_unregister;
		}

		DPRINTF(2, "sisattach: return: successed");
		return DDI_SUCCESS;
err_free_intr:
		/* release allocated resource */
		(void) ddi_remove_intr(dip, 0, c);
err_unregister:
		gld_unregister(macinfo);
err_free_ring:
		sis900_free_ring(sis_priv);
err_free_regs:
		ddi_regs_map_free(&sis_priv->regs_handle);
err_free_locks:
		mutex_destroy(&sis_priv->intrlock);
		mutex_destroy(&sis_priv->xmitlock);
		mutex_destroy(&sis_priv->buflock);
		mutex_destroy(&sis_priv->dma_handle_lock);
		cv_destroy(&sis_priv->drain_cv);
err_free_private:
		kmem_free((caddr_t)sis_priv,
			sizeof(struct sis900_private) + SISMCALLOC);
		gld_mac_free(macinfo);

		return DDI_FAILURE;
	}
	return DDI_FAILURE;
}

static int
sisdetach(dev_info_t *dip, ddi_detach_cmd_t cmd)
{
	int		i;
	struct sis900_private *sis_priv;
	gld_mac_info_t	*macinfo;

	if (cmd == DDI_DETACH) {
		macinfo = (gld_mac_info_t *)ddi_get_driver_private(dip);
		sis_priv = (struct sis900_private *)macinfo->gldm_private;

		/*
		 * stop the device
		 */
#ifdef notdef
		sis_stop(macinfo);
#endif
		/*
		 * unregister interrupt handler
		 */
		ddi_remove_intr(dip, 0, sis_priv->iblock_cookie);

		(void)gld_unregister(macinfo);

		sis900_free_ring(sis_priv);

		/*
		 * Release mapping resources
		 */
		ddi_regs_map_free(&sis_priv->regs_handle);

		mutex_destroy(&sis_priv->xmitlock);
		mutex_destroy(&sis_priv->intrlock);
		mutex_destroy(&sis_priv->buflock);
		mutex_destroy(&sis_priv->dma_handle_lock);
		cv_destroy(&sis_priv->drain_cv);

		/*
		 * Release memory and mapping resources
		 */
		kmem_free((caddr_t)sis_priv,
			sizeof(struct sis900_private)+SISMCALLOC);
		gld_mac_free(macinfo);

		DPRINTF(2, "sis%d: sisdetach: return: success",
			ddi_get_instance(dip));

		return DDI_SUCCESS;
	}
	return DDI_FAILURE;
}

static int
sis_set_mac_address(gld_mac_info_t *macinfo, unsigned char *addr)
{
	struct sis900_private *sis_priv;
	int	i;

	sis_priv = (struct sis900_private *)macinfo->gldm_private;
	bcopy((void *)addr,
		sis_priv->cur_addr.ether_addr_octet, ETHERADDRL);

	sis900_init_rxfilter(sis_priv);

	return GLD_SUCCESS;
}

/* sis_reset: done */
static int
sis_reset(gld_mac_info_t *macinfo)
{
	struct sis900_private *sis_priv;

	sis_priv = (struct sis900_private *)macinfo->gldm_private;
#ifdef notyet
	sis900_chip_reset(sis_priv);
#endif
	return GLD_SUCCESS;
}

static int
sis_start(gld_mac_info_t *macinfo)
{
	struct sis900_private *sis_priv;

	sis_priv = (struct sis900_private *)macinfo->gldm_private;

	sis900_open(sis_priv);

	return GLD_SUCCESS;
}

static int
sis_stop(gld_mac_info_t *macinfo)
{
	struct sis900_private *sis_priv;

	sis_priv = (struct sis900_private *)macinfo->gldm_private;

	sis900_close(sis_priv);

	return GLD_SUCCESS;
}

static int
sis_set_multicast(gld_mac_info_t *macinfo, struct ether_addr *ep, int flag)
{
	struct sis900_private	*sis_priv;
	size_t			len;
	int			i;
	int			cnt;

	sis_priv = (struct sis900_private *)macinfo->gldm_private;

	cnt = sis_priv->mc_count;

	if (flag == GLD_MULTI_ENABLE) {
		/* append new addess into mclist */
		if (cnt >= SISMAXMC) {
			return GLD_FAILURE;
		}
		bcopy(ep, &sis_priv->mc_list[cnt], sizeof(struct ether_addr));
		sis_priv->mc_count++;
	}
	else {
		if (cnt == 0) {
			return GLD_FAILURE;
		}
		for (i=0; i<cnt; i++) {
			if (bcmp(ep, &sis_priv->mc_list[i],
					sizeof(struct ether_addr)) == 0) {
				goto found;
			}
		}
		return GLD_FAILURE;
found:
		/* squeeze mclist by copying forward */
		len = (cnt - (i + 1)) * sizeof(struct ether_addr);
		if (len > 0) {
			bcopy(&sis_priv->mc_list[i+1], &sis_priv->mc_list[i], len);
		}
		sis_priv->mc_count--;
	}

	mutex_enter(&sis_priv->intrlock);
	sis900_set_rx_mode(sis_priv);
	mutex_exit(&sis_priv->intrlock);

	return GLD_SUCCESS;
}

static int
sis_set_promiscuous(gld_mac_info_t *macinfo, int flag)
{
	struct sis900_private *sis_priv;

	sis_priv = (struct sis900_private *)macinfo->gldm_private;

	if (flag == GLD_MAC_PROMISC_NONE) {
		sis_priv->flags &= ~(IFF_PROMISC|IFF_ALLMULTI);
	}
	else if (flag == GLD_MAC_PROMISC_MULTI) {
		sis_priv->flags |= IFF_ALLMULTI;
	}
	else {
		sis_priv->flags |= IFF_PROMISC;
	}

	sis900_set_rx_mode(sis_priv);

	return GLD_SUCCESS;
}

static	int
sis_get_stats(gld_mac_info_t *macinfo, struct gld_stats *gs)
{
	struct sis900_private	*sis_priv;
	struct sis900_stats	*vs;

	sis_priv = (struct sis900_private *)macinfo->gldm_private;

	vs = &sis_priv->stats;

	gs->glds_errxmt    = vs->tx_errors;
	gs->glds_errrcv    = vs->rx_errors;
	gs->glds_collisions= vs->collisions;

	gs->glds_excoll    = vs->tx_aborted_errors;
	gs->glds_defer     = vs->tx_defer;
	gs->glds_frame     = vs->rx_frame_errors;
	gs->glds_crc       = vs->rx_crc_errors;

	gs->glds_overflow  = vs->rx_fifo_errors; /* fifo err,underrun,rbufovf*/
	gs->glds_underflow = vs->tx_fifo_errors;
	gs->glds_short     = vs->rx_runt_errors;
	gs->glds_missed    = vs->rx_missed_errors; /* missed pkts while rbuf ovf */
	gs->glds_xmtlatecoll = vs->tx_window_errors;
	gs->glds_nocarrier = vs->tx_carrier_errors;
	gs->glds_norcvbuf  = vs->rx_dropped;	/* OS resource exaust */
	gs->glds_intr      = vs->intr;

	/* all before here must be kept in place for v0 compatibility */
	gs->glds_speed     = 10000000;
	gs->glds_media     = GLDM_TP;
	gs->glds_duplex    = sis_priv->full_duplex
				? GLD_DUPLEX_FULL : GLD_DUPLEX_HALF;

	/* gs->glds_media_specific */
	gs->glds_dot3_first_coll     = vs->tx_first_coll;
	gs->glds_dot3_multi_coll     = vs->tx_multi_coll;
	gs->glds_dot3_sqe_error	     = 0;
	gs->glds_dot3_mac_xmt_error  = 0;
	gs->glds_dot3_mac_rcv_error  = 0;
	gs->glds_dot3_frame_too_long = vs->rx_toolong_errors;

	return GLD_SUCCESS;
}

/*
 * Start transmission.
 * Return zero on success,
 */
static int
sis_send(gld_mac_info_t *macinfo, mblk_t *mp)
{
	int	len;
	struct sis900_private	*sis_priv;

	sis_priv = (struct sis900_private *)macinfo->gldm_private;

	DPRINTF(2, "sis_send: called");

	len = msgdsize(mp);
	if (len > ETHERMAX) {
		cmn_err(CE_CONT, "msg too big:  %d", len);

		/* Do not free mp here, GLD will free it */
		return GLD_NOTSUPPORTED;
	}

	if (sis900_start_xmit(sis_priv, mp) != 0) {
		/*
		 * Transmition failed.
		 * Tx buf maybe full or in RX buffer overflow. Try later.
		 */
		return GLD_NORESOURCES;
	}

	DPRINTF(2, "sis_send end");

	return GLD_SUCCESS;
}

/* ========================================================================= */

/* 
 * Dma handle and Local buffer management
 */
#ifdef SOLARIS
static ddi_dma_handle_t
get_dma_handle(struct sis900_private *sis_priv)
{
	ddi_dma_handle_t	dh;

	mutex_enter(&sis_priv->dma_handle_lock);
	ASSERT(sis_priv->dma_handle_free >= 0);
	if (sis_priv->dma_handle_free == 0) {
		mutex_exit(&sis_priv->dma_handle_lock);
		cmn_err(CE_PANIC, "%s: %s: no dma handle resource",
			sis_priv->name, __FUNCTION__);
		return NULL;
	}
	dh = sis_priv->dma_handle[--sis_priv->dma_handle_free];
	mutex_exit(&sis_priv->dma_handle_lock);

	return dh;
}

static void
free_dma_handle(struct sis900_private *sis_priv, ddi_dma_handle_t dh)
{
	mutex_enter(&sis_priv->dma_handle_lock);
	ASSERT(sis_priv->dma_handle_free < NUM_TX_DESC);
	sis_priv->dma_handle[sis_priv->dma_handle_free++] = dh;
	mutex_exit(&sis_priv->dma_handle_lock);
	return;
}

static void
free_lbuf(struct lbuf *lbp)
{
	struct sis900_private	*sis_priv;

	sis_priv = lbp->devp;

	mutex_enter(&sis_priv->buflock);
	lbp->next = sis_priv->buf_free_list;
	sis_priv->buf_free_list = lbp;
	sis_priv->buf_free++;
	mutex_exit(&sis_priv->buflock);
}

static struct lbuf *
get_lbuf(struct sis900_private *sis_priv, int cansleep)
{
	struct lbuf		*lbp;
	ddi_dma_cookie_t	cookie;
	uint_t			count;
	int			err;

	mutex_enter(&sis_priv->buflock);
	if ((lbp = sis_priv->buf_free_list) != NULL) {
		sis_priv->buf_free_list = lbp->next;
		sis_priv->buf_free--;
		mutex_exit(&sis_priv->buflock);
		return lbp;	
	}
	if (sis_priv->buf_allocated >= SIS_LOCAL_BUF_MAX) {
		return NULL;
	}
	sis_priv->buf_allocated++;
	mutex_exit(&sis_priv->buflock);

	lbp = (struct lbuf *) kmem_alloc(sizeof(struct lbuf),
				cansleep ? KM_SLEEP : KM_NOSLEEP);

	if (ddi_dma_alloc_handle(sis_priv->dip,  &dma_attr_nosc, 
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
	ASSERT(lbp->buf_len >= ETHERMAX+CRC_SIZE);
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
#ifdef NO_IOMMU
	ASSERT(cookie.dmac_laddress + cookie.dmac_size =< 0x100000000ULL);
	ddi_dma_unbind_handle(lbp->dma_handle);
	ddi_dma_free_handle(lbp->dma_handle);
	lbp->dma_handle = NULL;
#endif /* NO_IOMMU */
#endif /* ALWAYS_MAPPED */
	lbp->devp = sis_priv;
	lbp->frtn.free_func = (void (*)())&free_lbuf;
	lbp->frtn.free_arg  = (caddr_t) lbp;

	return lbp;
}
#endif

static int
sis900_alloc_ring(struct sis900_private* sis_priv)
{
	caddr_t			ring;
	size_t			ring_len;
	ddi_dma_cookie_t	cookie;
	uint_t			count;
	int			i;
	int			err;
	struct lbuf		*lbp, *head;

	/*
	 * Allocate RX/TX descriptors
	 */
	if ((err = ddi_dma_alloc_handle(sis_priv->dip, &dma_attr_nosc,
			DDI_DMA_SLEEP,NULL,
			&sis_priv->desc_dma_handle)) != DDI_SUCCESS) {
		cmn_err(CE_WARN, "%s: %s: ddi_dma_alloc_handle failed: %d",
			sis_priv->name, __FUNCTION__, err);
		return ENOMEM;
	}

	if ((err = ddi_dma_mem_alloc(sis_priv->desc_dma_handle,
#ifdef TXSOFTPAD
				ETHERMIN +
#endif
				NUM_RX_DESC * sizeof(BufferDesc) +
				NUM_TX_DESC * sizeof(BufferDesc),
				&dev_attr,
				DDI_DMA_CONSISTENT, DDI_DMA_SLEEP, NULL,
				&ring, &ring_len,
				&sis_priv->desc_acc_handle)) != DDI_SUCCESS) {
		cmn_err(CE_WARN, "%s: %s: ddi_dma_mem_alloc failed: %d",
			sis_priv->name, __FUNCTION__, err);
		ddi_dma_free_handle(&sis_priv->desc_dma_handle);
		return ENOMEM;
	}

	if ((err = ddi_dma_addr_bind_handle(sis_priv->desc_dma_handle,
				NULL, ring, ring_len,
				DDI_DMA_RDWR | DDI_DMA_CONSISTENT,
				DDI_DMA_SLEEP, NULL,
				&cookie, &count)) != DDI_SUCCESS) {
		ASSERT(err != DDI_DMA_INUSE);
		cmn_err(CE_WARN, "%s: %s: ddi_dma_addr_bind_handle failed: %d",
			sis_priv->name, __FUNCTION__, err);
		ddi_dma_mem_free(&sis_priv->desc_acc_handle);
		ddi_dma_free_handle(&sis_priv->desc_dma_handle);
		return ENOMEM;
	}
	ASSERT(count == 1);

	sis_priv->rx_ring = (BufferDesc *)ring;
	sis_priv->tx_ring = (BufferDesc *)
			(ring + NUM_RX_DESC * sizeof(BufferDesc));
	sis_priv->rx_ring_dma = cookie.dmac_address;
	sis_priv->tx_ring_dma = cookie.dmac_address
				+ NUM_RX_DESC * sizeof(BufferDesc);
#ifdef TXSOFTPAD
	bzero(((caddr_t)sis_priv->tx_ring) + NUM_TX_DESC * sizeof(BufferDesc),
		ETHERMIN);

	sis_priv->tx_pad_dma = sis_priv->tx_ring_dma
				+ NUM_TX_DESC * sizeof(BufferDesc);
#endif

	/*
	 * Allocate dma handle for each direct tx buffer.
	 */
	for (i = 0; i < NUM_TX_DESC; i++) {
		if ((err = ddi_dma_alloc_handle(sis_priv->dip,
			&dma_attr, DDI_DMA_SLEEP,
			NULL, &sis_priv->dma_handle[i])) != DDI_SUCCESS) {

			cmn_err(CE_WARN,
				"%s: %s: ddi_dma_alloc_handle failed. "
				"err:%d i:%d ",
				sis_priv->name, __FUNCTION__, err, i);
			while (i-- > 0) {
				ddi_dma_free_handle(&sis_priv->dma_handle[i]);
			}
			goto err;
		}
	}
	sis_priv->dma_handle_free = NUM_TX_DESC;

	/* Allocate local buffer */
	head = NULL;
	for (i = 0; i < SIS_LOCAL_BUF_INIT; i++) {
		lbp = get_lbuf(sis_priv, TRUE);
		lbp->next = head;
		head = lbp;
	}
	while ((lbp = head) != NULL) {
		head = head->next;
		free_lbuf(lbp);
	}

	return 0;

err:
	ddi_dma_unbind_handle(sis_priv->desc_dma_handle);
	ddi_dma_mem_free(&sis_priv->desc_acc_handle);
	ddi_dma_free_handle(&sis_priv->desc_dma_handle);

	return ENOMEM;
}

static void
sis900_free_ring(struct sis900_private* sis_priv)
{
	int		i;
	int		err;
	struct lbuf	*lbp;

	/* Free descriptor */
	err = ddi_dma_unbind_handle(sis_priv->desc_dma_handle);
	ASSERT(err == DDI_SUCCESS);

	ddi_dma_mem_free(&sis_priv->desc_acc_handle);
	ddi_dma_free_handle(&sis_priv->desc_dma_handle);

	/* Free dma handles for Tx */
	for (i=0; i<NUM_TX_DESC; i++) {
		ddi_dma_free_handle(&sis_priv->dma_handle[i]);
	}

	/* Free local buffers */
	while (lbp = sis_priv->buf_free_list) {
		sis_priv->buf_free_list = lbp->next;
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

/* ========================================================================= */

/**
 *	sis900_get_mac_addr: - Get MAC address for stand alone SiS900 model
 *	@pci_dev: the sis900 pci device
 *	@net_dev: the net device to get address for 
 *
 *	Older SiS900 and friends, use EEPROM to store MAC address.
 *	MAC address is read from read_eeprom() into @net_dev->dev_addr.
 */
static int
sis900_get_mac_addr(struct sis900_private *sis_priv)
{
	long		ioaddr = (long)sis_priv->base_addr;
	uint16_t	signature;
	int		i;

	/* check to see if we have sane EEPROM */
	signature = (uint16_t) read_eeprom(ioaddr, EEPROMSignature);    
	if (signature == 0xffff || signature == 0x0000) {
		printk (KERN_INFO "%s: Error EERPOM read %x\n", 
			sis_priv->name, signature);
		return 0;
	}

	/* get MAC address from EEPROM */
	for (i = 0; i < ETHERADDRL/2; i++) {
	        ((uint16_t *)(sis_priv->dev_addr.ether_addr_octet))[i] =
				read_eeprom(ioaddr, i+EEPROMMACAddr);
	}

	return 1;
}

/**
 *	sis630e_get_mac_addr: - Get MAC address for SiS630E model
 *	@pci_dev: the sis900 pci device
 *	@net_dev: the net device to get address for 
 *
 *	SiS630E model, use APC CMOS RAM to store MAC address.
 *	APC CMOS RAM is accessed through ISA bridge.
 *	MAC address is read into @net_dev->dev_addr.
 */
static int
sis630e_get_mac_addr(struct sis900_private *sis_priv)
{
	dev_info_t		*isa_bridge;
	ddi_acc_handle_t	isa_handle;
	int			i;
	int			reg;

	/*
	 * ddi_find_devinfo() is undocumented officially,
	 * but it is described in /usr/include/sys/sunddi.h
	 */
	if ((isa_bridge = ddi_find_devinfo("pci1039,8", -1, 0)) == NULL) {
		cmn_err(CE_WARN, "%s: %s: cannot find isa-bridge (pci1039,8)",
				sis_priv->name, __FUNCTION__);
		return 0;
	}

	if (pci_config_setup(isa_bridge, &isa_handle) != DDI_SUCCESS) {
		cmn_err(CE_WARN, "%s: %s: pci_config_setup failed",
			__FUNCTION__, sis_priv->name);
		return 0;
	}
	reg = pci_config_get8(isa_handle, 0x48);
	pci_config_put8(isa_handle, 0x48, reg | 0x40);

	for (i = 0; i < ETHERADDRL; i++) {
		OUTB(0x09 + i, 0x70);
		sis_priv->dev_addr.ether_addr_octet[i] = INB(0x71); 
	}

	pci_config_put8(isa_handle, 0x48, reg & ~0x40);
	pci_config_teardown(&isa_handle);

	return 1;
}


/**
 *	sis635_get_mac_addr: - Get MAC address for SIS635 model
 *	@pci_dev: the sis900 pci device
 *	@net_dev: the net device to get address for 
 *
 *	SiS635 model, set MAC Reload Bit to load Mac address from APC
 *	to rfdr. rfdr is accessed through rfcr. MAC address is read into 
 *	@net_dev->dev_addr.
 */
static int
sis635_get_mac_addr(struct sis900_private *sis_priv)
{
	long		ioaddr = (long)sis_priv->base_addr;
	uint32_t	rfcrSave;
	int		i;

	rfcrSave = INL(rfcr + ioaddr);

	OUTL(rfcrSave | RELOAD, ioaddr + cr);
	OUTL(0, ioaddr + cr);

	/* disable packet filtering before setting filter */
	OUTL(rfcrSave & ~RFEN, rfcr + ioaddr);

	/* load MAC addr to filter data register */
	for (i = 0 ; i < ETHERADDRL/sizeof(uint16_t) ; i++) {
		OUTL((i << RFADDR_shift), ioaddr + rfcr);
		((uint16_t *)sis_priv->dev_addr.ether_addr_octet)[i] =
							INW(ioaddr + rfdr);
	}

	/* enable packet filitering */
	OUTL(rfcrSave | RFEN, rfcr + ioaddr);

	return 1;
}


/**
 *	sis900_probe: - Probe for sis900 device
 *	@pci_dev: the sis900 pci device
 *	@pci_id: the pci device ID
 *
 *	Check and probe sis900 net device for @pci_dev.
 *	Get mac address according to the chip revision, 
 *	and assign SiS900-specific entries in the device structure.
 *	ie: sis900_open(), sis900_start_xmit(), sis900_close(), etc.
 */
static int
sis900_init_one(struct sis900_private *sis_priv, struct pci_device_id *pci_id)
{
#ifdef SOLARIS
	int		ioaddr;
	uint8_t		revision;
#endif
	int		i, ret;
	char		*card_name = card_names[pci_id->driver_data];

	/* Get Mac address according to the chip revision */
#ifdef SOLARIS
	ioaddr   = (long)sis_priv->base_addr;
	revision = sis_priv->revid;
#endif
	ret = 0;

#ifdef SOLARIS
#  ifdef CONFIG_SIS630E
	if (revision == SIS630E_900_REV) {
		ret = sis630e_get_mac_addr(sis_priv);
	} else
#  endif
#  ifdef CONFIG_SIS635
	if ((revision > 0x81) && (revision <= 0x90)) {
		ret = sis635_get_mac_addr(sis_priv);
	} else
#  endif
	{
		ret = sis900_get_mac_addr(sis_priv);
	}

	if (ret == 0) {
		ret = ENODEV;
		goto err;
	}

	/* probe for mii transciver */
	if (sis900_mii_probe(sis_priv) == 0) {
		ret = ENODEV;
		goto err;
	}
#endif

	/* print some information about our NIC */
	DPRINTF(0, "%s: %s at 0x%x, %02x:%02x:%02x:%02x:%02x:%02x",
		sis_priv->name,
		card_name, ioaddr,
		sis_priv->dev_addr.ether_addr_octet[0],
		sis_priv->dev_addr.ether_addr_octet[1],
		sis_priv->dev_addr.ether_addr_octet[2],
		sis_priv->dev_addr.ether_addr_octet[3],
		sis_priv->dev_addr.ether_addr_octet[4],
		sis_priv->dev_addr.ether_addr_octet[5]);

	return 0;

#ifdef SOLARIS
 err:
#endif
	return ret;
}

/**
 *	sis900_mii_probe: - Probe MII PHY for sis900
 *	@net_dev: the net device to probe for
 *	
 *	Search for total of 32 possible mii phy addresses.
 *	Identify and set current phy if found one,
 *	return error if it failed to found.
 */
static int
sis900_mii_probe(struct sis900_private *sis_priv)
{
	int		timeout = 50;
	int		status;
	int		phy_addr;

	sis_priv->mii = NULL;

	/* search for total of 32 possible mii phy addresses */
	for (phy_addr = 0; phy_addr < 32; phy_addr++) {	
		struct mii_phy	*mii_phy = NULL;
		uint16_t	mii_status;
		int		i;

		mii_phy = NULL;
		for(i = 0; i < 2; i++) {
			mii_status = mdio_read(sis_priv, phy_addr, MII_STATUS);
		}

		if (mii_status == 0xffff || mii_status == 0x0000) {
			/* the mii is not accessable, try next one */
			continue;
		}	
#ifdef SOLARIS
		mii_phy = &sis_priv->mii_list[phy_addr];
#endif	
		mii_phy->phy_id0 = mdio_read(sis_priv, phy_addr, MII_PHY_ID0);
		mii_phy->phy_id1 = mdio_read(sis_priv, phy_addr, MII_PHY_ID1);		
		mii_phy->phy_addr = phy_addr;
		mii_phy->status   = mii_status;
		mii_phy->next     = sis_priv->mii;
		sis_priv->mii     = mii_phy;
		sis_priv->first_mii = mii_phy;

		for (i=0; i<ARRAY_SIZE(mii_chip_table); i++) {

			if (mii_phy->phy_id0 != mii_chip_table[i].phy_id0 || 
			   (mii_phy->phy_id1 & 0xFFF0) !=
						mii_chip_table[i].phy_id1) {
				/* not matched */
				continue;
			}

			mii_phy->phy_types = mii_chip_table[i].phy_types;

			if (mii_chip_table[i].phy_types == MIX) {
				mii_phy->phy_types =
			(mii_status & (MII_STAT_CAN_TX_FDX | MII_STAT_CAN_TX))
						? LAN : HOME;
			}
			cmn_err(CE_CONT,
				"%s: %s transceiver found at address %d",
				sis_priv->name,
				mii_chip_table[i].name, phy_addr);
			goto next_phy_addr;
		}

		cmn_err(CE_CONT,
			"%s: Unknown PHY transceiver found at address %d",
			sis_priv->name, phy_addr);			
next_phy_addr:
	}
	
	if (sis_priv->mii == NULL) {
		cmn_err(CE_WARN, "%s: No MII transceivers found!",
			sis_priv->name);
		return 0;
	}

	/* select default PHY for mac */
	sis_priv->mii = NULL;
	sis900_default_phy(sis_priv);

	/* Reset phy if default phy is internal sis900 */
        if ((sis_priv->mii->phy_id0 == 0x001D) &&
	   ((sis_priv->mii->phy_id1 & 0xFFF0) == 0x8000)) {
        	status = sis900_reset_phy(sis_priv, sis_priv->cur_phy);
	}

	if (status & MII_STAT_LINK) {
		while ((mdio_read(sis_priv, sis_priv->cur_phy, MII_STATUS) & 
				MII_STAT_LINK) == 0) {
			
			if (timeout-- == 0) {
				cmn_err(CE_WARN,
					"%s: %s: reset phy and link down now",
					__FUNCTION__, sis_priv->name);
				return ETIME;
			}
			delay(drv_usectohz(100*1000));
		}
	}

	if (sis_priv->revid == SIS630E_900_REV) {
		/* SiS 630E has some bugs on default value of PHY registers */
		mdio_write(sis_priv, sis_priv->cur_phy, MII_ANADV, 0x05e1);
		mdio_write(sis_priv, sis_priv->cur_phy, MII_CONFIG1, 0x22);
		mdio_write(sis_priv, sis_priv->cur_phy, MII_CONFIG2, 0xff00);
		mdio_write(sis_priv, sis_priv->cur_phy, MII_MASK, 0xffc0);
#ifdef notdef
		//mdio_write(net_dev, sis_priv->cur_phy, MII_CONTROL, 0x1000);	
#endif
	}

#ifdef LINUX
	if (sis_priv->mii->status & MII_STAT_LINK)
		netif_carrier_on(net_dev);
	else
		netif_carrier_off(net_dev);
#endif
	return 1;
}

/**
 *	sis900_default_phy: - Select default PHY for sis900 mac.
 *	@net_dev: the net device to probe for
 *
 *	Select first detected PHY with link as default.
 *	If no one is link on, select PHY whose types is HOME as default.
 *	If HOME doesn't exist, select LAN.
 */
static uint16_t
sis900_default_phy(struct sis900_private *sis_priv)
{
 	struct mii_phy	*phy = NULL,
			*phy_home = NULL,
			*default_phy = NULL;
	uint16_t	status;

        for (phy=sis_priv->first_mii; phy; phy=phy->next) {
		status = mdio_read(sis_priv, phy->phy_addr, MII_STATUS);
		status = mdio_read(sis_priv, phy->phy_addr, MII_STATUS);

		if ((status & MII_STAT_LINK) && default_phy == NULL) {
			/* first link-on phy is default */
		 	default_phy = phy;
			continue;
		}

		/* others should be ISOLATE mode */
		status = mdio_read(sis_priv, phy->phy_addr, MII_CONTROL);
		mdio_write(sis_priv, phy->phy_addr, MII_CONTROL,
				status | MII_CNTL_AUTO | MII_CNTL_ISOLATE);

		if (phy->phy_types == HOME) {
			/* last HOME phy */
			phy_home = phy;
		}
	}

	if (default_phy == NULL) {
		default_phy = phy_home;
		if (default_phy == NULL) {
			default_phy = sis_priv->first_mii;
		}
	}

	if (sis_priv->mii != default_phy) {
		sis_priv->mii = default_phy;
		sis_priv->cur_phy = default_phy->phy_addr;
		printk(KERN_INFO
			"%s: Using transceiver found at address %d as default",
			sis_priv->name, sis_priv->cur_phy);
	}
	
	status = mdio_read(sis_priv, sis_priv->cur_phy, MII_CONTROL);
	status &= ~MII_CNTL_ISOLATE;
	mdio_write(sis_priv, sis_priv->cur_phy, MII_CONTROL, status);	

	status = mdio_read(sis_priv, sis_priv->cur_phy, MII_STATUS);
	status = mdio_read(sis_priv, sis_priv->cur_phy, MII_STATUS);

	return status;	
}


/**
 * 	sis900_set_capability: - set the media capability of network adapter.
 *	@net_dev : the net device to probe for
 *	@mii_phy : default PHY
 *
 *	Set the media capability of network adapter according to
 *	mii status register. It's necessary before auto-negotiate.
 */
 
static void
sis900_set_capability(struct sis900_private *sis_priv, struct mii_phy *phy)
{
	u16 cap;
	u16 status;
	
	status = mdio_read(sis_priv, phy->phy_addr, MII_STATUS);
	status = mdio_read(sis_priv, phy->phy_addr, MII_STATUS);
	
	cap = MII_NWAY_CSMA_CD |
		((phy->status & MII_STAT_CAN_TX_FDX)? MII_NWAY_TX_FDX:0) |
		((phy->status & MII_STAT_CAN_TX)    ? MII_NWAY_TX:0) |
		((phy->status & MII_STAT_CAN_T_FDX) ? MII_NWAY_T_FDX:0)|
		((phy->status & MII_STAT_CAN_T)     ? MII_NWAY_T:0);

	mdio_write(sis_priv, phy->phy_addr, MII_ANADV, cap);
}


/* Delay between EEPROM clock transitions. */
#define eeprom_delay()  INL(ee_addr)

/*
 *	read_eeprom: - Read Serial EEPROM
 *	@ioaddr: base i/o address
 *	@location: the EEPROM location to read
 *
 *	Read Serial EEPROM through EEPROM Access Register.
 *	Note that location is in word (16 bits) unit
 */
static u16 read_eeprom(long ioaddr, int location)
{
	int	i;
	u16	retval = 0;
	long	ee_addr = ioaddr + mear;
	u32	read_cmd = location | EEread;

	OUTL(0, ee_addr);
	eeprom_delay();
	OUTL(EECLK, ee_addr);
	eeprom_delay();

	/* Shift the read command (9) bits out. */
	for (i = 8; i >= 0; i--) {
		u32 dataval = (read_cmd & (1 << i)) ? EEDI | EECS : EECS;
		OUTL(dataval, ee_addr);
		eeprom_delay();
		OUTL(dataval | EECLK, ee_addr);
		eeprom_delay();
	}
	OUTB(EECS, ee_addr);
	eeprom_delay();

	/* read the 16-bits data in */
	for (i = 16; i > 0; i--) {
		OUTL(EECS, ee_addr);
		eeprom_delay();
		OUTL(EECS | EECLK, ee_addr);
		eeprom_delay();
		retval = (retval << 1) | ((INL(ee_addr) & EEDO) ? 1 : 0);
		eeprom_delay();
	}

	/* Terminate the EEPROM access. */
	OUTL(0, ee_addr);
	eeprom_delay();
	OUTL(EECLK, ee_addr);

	return (retval);
}

/*
 * Read and write the MII management registers using software-generated
 * serial MDIO protocol. Note that the command bits and data bits are
 * send out seperately
 */
#define mdio_delay()    INL(mdio_addr)

static void
mdio_idle(long mdio_addr)
{
	OUTL(MDIO | MDDIR, mdio_addr);
	mdio_delay();
	OUTL(MDIO | MDDIR | MDC, mdio_addr);
}

/* Syncronize the MII management interface by shifting 32 one bits out. */
static void
mdio_reset(long mdio_addr)
{
	int i;

	for (i = 31; i >= 0; i--) {
		OUTL(MDDIR | MDIO, mdio_addr);
		mdio_delay();
		OUTL(MDDIR | MDIO | MDC, mdio_addr);
		mdio_delay();
	}
	return;
}

/*
 *	mdio_read: - read MII PHY register
 *	@net_dev: the net device to read
 *	@phy_id: the phy address to read
 *	@location: the phy regiester id to read
 *
 *	Read MII registers through MDIO and MDC
 *	using MDIO management frame structure and protocol(defined by ISO/IEC).
 *	Please see SiS7014 or ICS spec
 */
static uint16_t
mdio_read(struct sis900_private *lp, int phy_id, int location)
{
	long	mdio_addr = (long)lp->base_addr + mear;
	int	mii_cmd = MIIread|(phy_id<<MIIpmdShift)|(location<<MIIregShift);
	u16	retval = 0;
	int	i;

	mdio_reset(mdio_addr);
	mdio_idle(mdio_addr);

	for (i = 15; i >= 0; i--) {
		int dataval = (mii_cmd & (1 << i)) ? MDDIR | MDIO : MDDIR;
		OUTL(dataval, mdio_addr);
		mdio_delay();
		OUTL(dataval | MDC, mdio_addr);
		mdio_delay();
	}

	/* Read the 16 data bits. */
	for (i = 16; i > 0; i--) {
		OUTL(0, mdio_addr);
		mdio_delay();
		retval = (retval << 1) | ((INL(mdio_addr) & MDIO) ? 1 : 0);
		OUTL(MDC, mdio_addr);
		mdio_delay();
	}
	OUTL(0x00, mdio_addr);

	return retval;
}

/*
 *	mdio_write: - write MII PHY register
 *	@net_dev: the net device to write
 *	@phy_id: the phy address to write
 *	@location: the phy regiester id to write
 *	@value: the register value to write with
 *
 *	Write MII registers with @value through MDIO and MDC
 *	using MDIO management frame structure and protocol(defined by ISO/IEC)
 *	please see SiS7014 or ICS spec
 */

static void
mdio_write(struct sis900_private *lp, int phy_id, int location, int value)
{
	long	mdio_addr = (long)lp->base_addr + mear;
	int	mii_cmd=MIIwrite|(phy_id<<MIIpmdShift)|(location<<MIIregShift);
	int	i;

	mdio_reset(mdio_addr);
	mdio_idle(mdio_addr);

	/* Shift the command bits out. */
	for (i = 15; i >= 0; i--) {
		int	dataval = (mii_cmd & (1 << i)) ? MDDIR | MDIO : MDDIR;
		OUTB(dataval, mdio_addr);
		mdio_delay();
		OUTB(dataval | MDC, mdio_addr);
		mdio_delay();
	}
	mdio_delay();

	/* Shift the value bits out. */
	for (i = 15; i >= 0; i--) {
		int dataval = (value & (1 << i)) ? MDDIR | MDIO : MDDIR;
		OUTL(dataval, mdio_addr);
		mdio_delay();
		OUTL(dataval | MDC, mdio_addr);
		mdio_delay();
	}
	mdio_delay();

	/* Clear out extra bits. */
	for (i = 2; i > 0; i--) {
		OUTB(0, mdio_addr);
		mdio_delay();
		OUTB(MDC, mdio_addr);
		mdio_delay();
	}
	OUTL(0x00, mdio_addr);

	return;
}


/*
 *	sis900_reset_phy: - reset sis900 mii phy.
 *	@net_dev: the net device to write
 *	@phy_addr: default phy address
 *
 *	Some specific phy can't work properly without reset.
 *	This function will be called during initialization and
 *	link status change from ON to DOWN.
 */

static uint16_t
sis900_reset_phy(struct sis900_private *sis_priv, int phy_addr)
{
	int		i = 0;
	uint16_t	status;

	while (i++ < 2) {
		status = mdio_read(sis_priv, phy_addr, MII_STATUS);
	}
	mdio_write(sis_priv, phy_addr, MII_CONTROL, MII_CNTL_RESET);
	
	return status;
}

/*
 *	sis900_open: - open sis900 device
 *	@net_dev: the net device to open
 *
 *	Do some initialization and start net interface.
 *	enable interrupts and set sis900 timer.
 */

static int
sis900_open(struct sis900_private *sis_priv)
{
	long	ioaddr = (long)sis_priv->base_addr;
	int	ret;

	mutex_enter(&sis_priv->intrlock);
	mutex_enter(&sis_priv->xmitlock);

	/* Soft reset the chip. */
	sis900_reset(sis_priv);

	/* Equalizer workaround Rule */
	sis630_set_eq(sis_priv, sis_priv->revid);

	sis900_init_rxfilter(sis_priv);

	sis900_init_tx_ring(sis_priv);
	sis900_init_rx_ring(sis_priv);

	sis900_set_rx_mode(sis_priv);

	/* Enable all known interrupts by setting the interrupt mask. */
	OUTL(OUR_INTR_BITS, ioaddr + imr);
	OUTL(RxENA, ioaddr + cr);
	OUTL(IE, ioaddr + ier);

	sis900_check_mode(sis_priv, sis_priv->mii);
	sis_priv->start = TRUE;
	sis_priv->tx_blocked = FALSE;
	sis_priv->tx_busy = 0;
	sis_priv->tx_reserved = 0;
	sis_priv->intr_busy = FALSE;

	mutex_exit(&sis_priv->xmitlock);
	mutex_exit(&sis_priv->intrlock);

	return 0;
}

/*
 *	sis900_init_rxfilter: - Initialize the Rx filter
 *	@net_dev: the net device to initialize for
 *
 *	Set receive filter address to our MAC address
 *	and enable packet filtering.
 */
static void
sis900_init_rxfilter(struct sis900_private *sis_priv)
{
	long		ioaddr = (long)sis_priv->base_addr;
	uint32_t	rfcrSave;
	int		i;

	rfcrSave = INL(rfcr + ioaddr);

	/* disable packet filtering before setting filter */
	OUTL(rfcrSave & ~RFEN, rfcr + ioaddr);

	/* load MAC addr to filter data register */
	for (i = 0 ; i < ETHERADDRL/2 ; i++) {
		unsigned	w;

		w = ((uint16_t *)sis_priv->cur_addr.ether_addr_octet)[i];
		OUTL((i << RFADDR_shift), ioaddr + rfcr);
		OUTL(w, ioaddr + rfdr);

		DPRINTF(2, "%s: Receive Filter Addrss[%d]=%04x",
			       sis_priv->name, i, INL(ioaddr + rfdr));
	}

	/* enable packet filitering */
	OUTL(rfcrSave | RFEN, rfcr + ioaddr);
}

/*
 *	sis900_init_tx_ring: - Initialize the Tx descriptor ring
 *	@net_dev: the net device to initialize for
 *
 *	Initialize the Tx descriptor ring, 
 */

static void
sis900_init_tx_ring(struct sis900_private *sis_priv)
{
	long	ioaddr = (long)sis_priv->base_addr;
	int	i;

	sis_priv->dirty_tx = sis_priv->cur_tx = 0;

	for (i = 0; i < NUM_TX_DESC; i++) {
		sis_priv->tx_mp[i]   = NULL;
		sis_priv->tx_lbp[i]  = NULL;
		sis_priv->tx_dma_handle_used[i]= NULL;

		sis_priv->tx_ring[i].link = sis_priv->tx_ring_dma +
				((i + 1) % NUM_TX_DESC) * sizeof(BufferDesc);
		sis_priv->tx_ring[i].cmdsts = 0;
		sis_priv->tx_ring[i].bufptr = 0xBADF00D0;
	}

	/* load Transmit Descriptor Register */
	OUTL(sis_priv->tx_ring_dma, ioaddr + txdp);

	DPRINTF(2, "%s: TX descriptor register loaded with: 0x%08p\n",
		       sis_priv->name, INL(ioaddr + txdp));
}

static void
sis900_free_tx_ring(struct sis900_private *sis_priv)
{
	int			i;
	ddi_dma_handle_t	dh;
	struct lbuf		*lbp;
	mblk_t			*mp;

	ASSERT(mutex_owned(&sis_priv->xmitlock));

	for (i = 0; i < NUM_TX_DESC; i++) {
		sis_priv->tx_ring[i].cmdsts = 0;
		sis_priv->tx_ring[i].bufptr = 0xBADF00D0;

		if ((dh = sis_priv->tx_dma_handle_used[i]) != NULL) {
			/* release dma resource */
			ddi_dma_unbind_handle(dh);
			sis_priv->tx_dma_handle_used[i] = NULL;
			free_dma_handle(sis_priv, dh);
		}

		if ((mp = sis_priv->tx_mp[i]) != NULL) {
			/* free direct mapped mblk */
			ASSERT(sis_priv->tx_lbp[i] == NULL);
			freemsg(mp);
			sis_priv->tx_mp[i] = NULL;

			sis_priv->stats.tx_errors++;
		}
		else if (lbp = sis_priv->tx_lbp[i]) {
			/* free bounce buffer */
#ifndef ALWAYS_MAPPED
			ddi_dma_unbind_handle(lbp->dma_handle);
#endif
			free_lbuf(lbp);
			sis_priv->tx_lbp[i] = NULL;
			sis_priv->stats.tx_errors++;
		}
	}
}

/**
 *	sis900_init_rx_ring: - Initialize the Rx descriptor ring
 *	@net_dev: the net device to initialize for
 *
 *	Initialize the Rx descriptor ring, 
 *	and pre-allocate recevie buffers (socket buffer)
 */

static void 
sis900_init_rx_ring(struct sis900_private *sis_priv)
{
	long	ioaddr = (long)sis_priv->base_addr;
	int	i;

	sis_priv->cur_rx = 0;
	sis_priv->dirty_rx = 0;

	/* init RX descriptor */
	for (i = 0; i < NUM_RX_DESC; i++) {
		sis_priv->rx_lbp[i]    = NULL;

		sis_priv->rx_ring[i].link = sis_priv->rx_ring_dma +
			((i+1)%NUM_RX_DESC)*sizeof(BufferDesc);
		sis_priv->rx_ring[i].cmdsts = 0;
		sis_priv->rx_ring[i].bufptr = 0xBADF00D0;
	}

	/* allocate buffers */
	for (i = 0; i < NUM_RX_DESC; i++) {
		struct lbuf		*lbp;
		ddi_dma_cookie_t	cookie;
		uint_t			count;

		if ((lbp = get_lbuf(sis_priv, TRUE)) == NULL) {
			/*
			 * Not enough memory for rcv-buf, this makes a "hole"
			 * on the buffer ring, it is not clear how the
			 * hardware will react to this kind of degenerated
			 * buffer
			 */
			break;
		}
#ifdef ALWAYS_MAPPED
		sis_priv->rx_ring[i].bufptr = lbp->dma_addr;
#else
		/* setup dma resource */
		if (ddi_dma_addr_bind_handle(lbp->dma_handle,
					NULL, lbp->buf, lbp->buf_len,
					DDI_DMA_READ | DDI_DMA_STREAMING,
					DDI_DMA_SLEEP, NULL,
					&cookie, &count) != DDI_SUCCESS) {
			free_lbuf(lbp);
			break;
		}
		ASSERT(count == 1);
		sis_priv->rx_ring[i].bufptr = cookie.dmac_address;
#endif /* ALWAYS_MAPPED */
		sis_priv->rx_ring[i].cmdsts = lbp->buf_len;
		sis_priv->rx_lbp[i] = lbp;
	}
	sis_priv->dirty_rx = (unsigned int) (i - NUM_RX_DESC);

	/* load Receive Descriptor Register */
	OUTL(sis_priv->rx_ring_dma, ioaddr + rxdp);

	DPRINTF(2, "%s: RX descriptor register loaded with: 0x%08x\n",
		       sis_priv->name, INL(ioaddr + rxdp));
}

static void
sis900_free_rx_ring(struct sis900_private* sis_priv)
{
	int		i;
	struct lbuf	*lbp;

	ASSERT(mutex_owned(&sis_priv->intrlock));

	/* Free all the lbuf in the Rx queue. */
	for (i = 0; i < NUM_RX_DESC; i++) {

		sis_priv->rx_ring[i].cmdsts = 0;
		sis_priv->rx_ring[i].bufptr = 0xBADF00D0;

		if ((lbp = sis_priv->rx_lbp[i]) != NULL) {
#ifndef ALWAYS_MAPPED
			/* release DMA resource */
			ddi_dma_unbind_handle(lbp->dma_handle);
#endif
			free_lbuf(lbp);
			sis_priv->rx_lbp[i] = NULL;
		}
	}
}

/*
 *	sis630_set_eq: - set phy equalizer value for 630 LAN
 *	@net_dev: the net device to set equalizer value
 *	@revision: 630 LAN revision number
 *
 *	630E equalizer workaround rule(Cyrus Huang 08/15)
 *	PHY register 14h(Test)
 *	Bit 14: 0 -- Automatically dectect (default)
 *		1 -- Manually set Equalizer filter
 *	Bit 13: 0 -- (Default)
 *		1 -- Speed up convergence of equalizer setting
 *	Bit 9 : 0 -- (Default)
 *		1 -- Disable Baseline Wander
 *	Bit 3~7   -- Equalizer filter setting
 *	Link ON: Set Bit 9, 13 to 1, Bit 14 to 0
 *	Then calculate equalizer value
 *	Then set equalizer value, and set Bit 14 to 1, Bit 9 to 0
 *	Link Off:Set Bit 13 to 1, Bit 14 to 0
 *	Calculate Equalizer value:
 *	When Link is ON and Bit 14 is 0, SIS900PHY will auto-dectect
 *	proper equalizer value.
 *	When the equalizer is stable, this value is not a fixed value.
 *	It will be within a small range(eg. 7~9). Then we get a minimum
 *	and a maximum value(eg. min=7, max=9)
 *	0 <= max <= 4  --> set equalizer to max
 *	5 <= max <= 14 --> set equalizer to max+1
 *			   or set equalizer to max+2 if max == min
 *	max >= 15      --> set equalizer to max+5
 *			   or set equalizer to max+6 if max == min
 */
static void
sis630_set_eq(struct sis900_private *sis_priv, uint8_t revision)
{
#ifdef LINUX
	struct sis900_private *sis_priv = net_dev->priv;
#endif
	uint16_t	reg14h, eq_value=0, max_value=0, min_value=0;
	uint8_t		host_bridge_rev;
	int		i, maxcount=10;
#ifdef LINUX
	struct pci_dev *dev=NULL;
#endif
#ifdef SOLARIS
	char		node630[16];	/* "pciXXXX,YYYY" */
	dev_info_t	*host_bridge;
	ddi_acc_handle_t hb_handle;
#endif
	if ( !(revision == SIS630E_900_REV || revision == SIS630EA1_900_REV ||
	       revision == SIS630A_900_REV) ) {
		return;
	}
#ifdef LINUX
	dev = pci_find_device(PCI_VENDOR_ID_SI, PCI_DEVICE_ID_SI_630, dev);
	if (dev)
		pci_read_config_byte(dev, PCI_CLASS_REVISION, &host_bridge_rev);
#endif
#ifdef SOLARIS
	sprintf(node630, "pci%x,%x", PCI_VENDOR_ID_SI, PCI_DEVICE_ID_SI_630);
	if ((host_bridge = ddi_find_devinfo(node630, -1, 0)) == NULL) {
		cmn_err(CE_WARN, "%s: %s: cannot find host-bridge: %s",
			sis_priv->name, __FUNCTION__, node630);
		return;
	}
	if (pci_config_setup(host_bridge, &hb_handle) != DDI_SUCCESS) {
		cmn_err(CE_WARN, "%s: %s: pci_config_setup failed",
			sis_priv->name, __FUNCTION__);
		return;
	}
	host_bridge_rev = pci_config_get8(hb_handle, PCI_CONF_REVID);
	pci_config_teardown(&hb_handle);
#endif
#ifdef LINUX
	if (netif_carrier_ok(net_dev))
#endif
#ifdef SOLARIS
	if (sis_priv->carrier_ok)
#endif
	{
		reg14h = mdio_read(sis_priv, sis_priv->cur_phy, MII_RESV);
		mdio_write(sis_priv, sis_priv->cur_phy, MII_RESV,
						(0x2200 | reg14h) & 0xBFFF);

		for (i=0; i < maxcount; i++) {
			eq_value =
	(0x00F8 & mdio_read(sis_priv, sis_priv->cur_phy, MII_RESV)) >> 3;
			if (i == 0) {
				max_value = min_value = eq_value;
#ifdef SOLARIS
				continue;
#endif
			}
#ifdef LINUX
			max_value=(eq_value > max_value) ? eq_value : max_value;
			min_value=(eq_value < min_value) ? eq_value : min_value;
#endif
#ifdef SOLARIS
			max_value = max(eq_value, max_value);
			min_value = min(eq_value, min_value);
#endif
		}
		/* 630E rule to determine the equalizer value */
		if (revision == SIS630E_900_REV ||
		    revision == SIS630EA1_900_REV) {
			if (max_value < 5) {
				eq_value = max_value;
			}
			else if (max_value >= 5 && max_value < 15) {
				eq_value = (max_value == min_value)
						? max_value + 2 : max_value + 1;
			}
			else if (max_value >= 15) {
				eq_value = (max_value == min_value)
						? max_value + 6 : max_value + 5;
			}
		}
		/* 630B0&B1 rule to determine the equalizer value */
		if (revision == SIS630A_900_REV && 
		    (host_bridge_rev==SIS630B0 || host_bridge_rev==SIS630B1)) {
			if (max_value == 0) {
				eq_value = 3;
			}
			else {
				eq_value = (max_value + min_value + 1) / 2;
			}
		}
		/* write equalizer value and setting */
		reg14h = mdio_read(sis_priv, sis_priv->cur_phy, MII_RESV);
		reg14h = (reg14h & 0xFF07) | ((eq_value << 3) & 0x00F8);
		reg14h = (reg14h | 0x6000) & 0xFDFF;
		mdio_write(sis_priv, sis_priv->cur_phy, MII_RESV, reg14h);
	}
	else {
		reg14h = mdio_read(sis_priv, sis_priv->cur_phy, MII_RESV);

		if (revision == SIS630A_900_REV && 
		    (host_bridge_rev==SIS630B0 || host_bridge_rev==SIS630B1)) {
			mdio_write(sis_priv, sis_priv->cur_phy, MII_RESV,
				(reg14h | 0x2200) & 0xBFFF);
		}
		else {
			mdio_write(sis_priv, sis_priv->cur_phy, MII_RESV,
				(reg14h | 0x2000) & 0xBFFF);
		}
	}
	return;
}

/**
 *	sis900_timer: - sis900 timer routine
 *	@data: pointer to sis900 net device
 *
 *	On each timer ticks we check two things, 
 *	link status (ON/OFF) and link mode (10/100/Full/Half)
 */
static void
sis900_timer(struct sis900_private *sis_priv)
{
	struct mii_phy	*mii_phy = sis_priv->mii;
	long		ioaddr = (long)sis_priv->base_addr;
	uint16_t	status;

	if (!sis_priv->autong_complete){
		int	speed, duplex = 0;

		sis900_read_mode(sis_priv, &speed, &duplex);
		if (duplex) {
			sis900_set_mode(ioaddr, speed, duplex);
			sis630_set_eq(sis_priv, sis_priv->revid);

		}
		sis_priv->timer_id =
			timeout((void (*)(void *))&sis900_timer,
				(void *)sis_priv, drv_usectohz(1000000));
		return;
	}

	status = mdio_read(sis_priv, sis_priv->cur_phy, MII_STATUS);
	status = mdio_read(sis_priv, sis_priv->cur_phy, MII_STATUS);

	/* Link OFF -> ON */
	if (!sis_priv->carrier_ok) {
LookForLink:
		/* Search for new PHY */
		status = sis900_default_phy(sis_priv);
		mii_phy = sis_priv->mii;

		if (status & MII_STAT_LINK){
			sis900_check_mode(sis_priv, mii_phy);
			sis_priv->carrier_ok = TRUE;
		}
	}
	/* Link ON -> OFF */
	else {
                if (!(status & MII_STAT_LINK)){
			sis_priv->carrier_ok = FALSE;
                	printk(KERN_INFO "%s: Media Link Off", sis_priv->name);

                	/* Change mode issue */
                	if ((mii_phy->phy_id0 == 0x001D) && 
			    ((mii_phy->phy_id1 & 0xFFF0) == 0x8000)) {
               			sis900_reset_phy(sis_priv,  sis_priv->cur_phy);
 			} 
			sis630_set_eq(sis_priv, sis_priv->revid);
                	goto LookForLink;
                }
	}
	sis_priv->timer_id = timeout((void (*)(void *))sis900_timer,
					(void *)sis_priv,
					drv_usectohz(5*1000000));
	return;
}

/**
 *	sis900_check_mode: - check the media mode for sis900
 *	@net_dev: the net device to be checked
 *	@mii_phy: the mii phy
 *
 *	Older driver gets the media mode from mii status output
 *	register. Now we set our media capability and auto-negotiate
 *	to get the upper bound of speed and duplex between two ends.
 *	If the types of mii phy is HOME, it doesn't need to auto-negotiate
 *	and autong_complete should be set to 1.
 */
static void
sis900_check_mode(struct sis900_private *sis_priv, struct mii_phy *mii_phy)
{
	long	ioaddr = (long)sis_priv->base_addr;
	int	speed, duplex;

	if (mii_phy->phy_types == LAN) {
		OUTL(~EXD & INL(ioaddr + cfg), ioaddr + cfg);
		sis900_set_capability(sis_priv , mii_phy);
		sis900_auto_negotiate(sis_priv, sis_priv->cur_phy);
	}
	else {
		OUTL(EXD | INL(ioaddr + cfg), ioaddr + cfg);
		speed  = HW_SPEED_HOME;
		duplex = FDX_CAPABLE_HALF_SELECTED;
		sis900_set_mode(ioaddr, speed, duplex);
		sis_priv->autong_complete = 1;
	}
}

/**
 *	sis900_set_mode: - Set the media mode of mac register.
 *	@speed : the transmit speed to be determined
 *	@duplex: the duplex mode to be determined
 *
 *	Set the media mode of mac register txcfg/rxcfg according to
 *	speed and duplex of phy. Bit EDB_MASTER_EN indicates the EDB
 *	bus is used instead of PCI bus. When this bit is set 1, the
 *	Max DMA Burst Size for TX/RX DMA should be no larger than 16
 *	double words.
 */
static void
sis900_set_mode(long ioaddr, int speed, int duplex)
{
	uint32_t	tx_flags = 0, rx_flags = 0;

	if (INL(ioaddr + cfg) & EDB_MASTER_EN) {
#ifdef TXSOFTPAD
		tx_flags = (DMA_BURST_64 << TxMXDMA_shift)
					| (TX_FILL_THRESH << TxFILLT_shift);
#else
		tx_flags = TxATP | (DMA_BURST_64 << TxMXDMA_shift)
					| (TX_FILL_THRESH << TxFILLT_shift);
#endif
		rx_flags = DMA_BURST_64 << RxMXDMA_shift;
	}
	else {
#ifdef TXSOFTPAD
		tx_flags = (DMA_BURST_512 << TxMXDMA_shift)
					| (TX_FILL_THRESH << TxFILLT_shift);
#else
		tx_flags = TxATP | (DMA_BURST_512 << TxMXDMA_shift)
					| (TX_FILL_THRESH << TxFILLT_shift);
#endif
		rx_flags = DMA_BURST_512 << RxMXDMA_shift;
	}

	if (speed == HW_SPEED_HOME || speed == HW_SPEED_10_MBPS ) {
		rx_flags |= (RxDRNT_10 << RxDRNT_shift);
		tx_flags |= (TxDRNT_10 << TxDRNT_shift);
	}
	else {
		rx_flags |= (RxDRNT_100 << RxDRNT_shift);
		tx_flags |= (TxDRNT_100 << TxDRNT_shift);
	}

	if (duplex == FDX_CAPABLE_FULL_SELECTED) {
		tx_flags |= (TxCSI | TxHBI);
		rx_flags |= RxATX;
	}

	OUTL(tx_flags, ioaddr + txcfg);
	OUTL(rx_flags, ioaddr + rxcfg);
}

/**
 *	sis900_auto_negotiate:  Set the Auto-Negotiation Enable/Reset bit.
 *	@net_dev: the net device to read mode for
 *	@phy_addr: mii phy address
 *
 *	If the adapter is link-on, set the auto-negotiate enable/reset bit.
 *	autong_complete should be set to 0 when starting auto-negotiation.
 *	autong_complete should be set to 1 if we didn't start auto-negotiation.
 *	sis900_timer will wait for link on again if autong_complete = 0.
 */
static void
sis900_auto_negotiate(struct sis900_private *sis_priv, int phy_addr)
{
	int		i = 0;
	u32		status;
	
	while (i++ < 2) {
		status = mdio_read(sis_priv, phy_addr, MII_STATUS);
	}

	if (!(status & MII_STAT_LINK)){
		printk(KERN_INFO "%s: Media Link Off\n", sis_priv->name);
		sis_priv->autong_complete = 1;
		sis_priv->carrier_ok = FALSE;
		return;
	}

	/* (Re)start AutoNegotiate */
	mdio_write(sis_priv, phy_addr, MII_CONTROL,
		   MII_CNTL_AUTO | MII_CNTL_RST_AUTO);
	sis_priv->autong_complete = 0;
}


/**
 *	sis900_read_mode: - read media mode for sis900 internal phy
 *	@net_dev: the net device to read mode for
 *	@speed  : the transmit speed to be determined
 *	@duplex : the duplex mode to be determined
 *
 *	The capability of remote end will be put in mii register autorec
 *	after auto-negotiation. Use AND operation to get the upper bound
 *	of speed and duplex between two ends.
 */
static void
sis900_read_mode(struct sis900_private *sis_priv, int *speed, int *duplex)
{
	struct mii_phy	*phy = sis_priv->mii;
	int		phy_addr = sis_priv->cur_phy;
	u32		status;
	u16		autoadv, autorec;
	int		i = 0;

	while (i++ < 2) {
		status = mdio_read(sis_priv, phy_addr, MII_STATUS);
	}

	if (!(status & MII_STAT_LINK)) {
		return;
	}

	/* AutoNegotiate completed */
	autoadv = mdio_read(sis_priv, phy_addr, MII_ANADV);
	autorec = mdio_read(sis_priv, phy_addr, MII_ANLPAR);
	status = autoadv & autorec;
	
	*speed = HW_SPEED_10_MBPS;
	*duplex = FDX_CAPABLE_HALF_SELECTED;

	if (status & (MII_NWAY_TX | MII_NWAY_TX_FDX)) {
		*speed = HW_SPEED_100_MBPS;
	}
	if (status & ( MII_NWAY_TX_FDX | MII_NWAY_T_FDX)) {
		*duplex = FDX_CAPABLE_FULL_SELECTED;
	}
	sis_priv->autong_complete = 1;

	/* Workaround for Realtek RTL8201 PHY issue */
	if((phy->phy_id0 == 0x0000) && ((phy->phy_id1 & 0xFFF0) == 0x8200)){
		if (mdio_read(sis_priv, phy_addr, MII_CONTROL) & MII_CNTL_FDX) {
			*duplex = FDX_CAPABLE_FULL_SELECTED;
		}
		if (mdio_read(sis_priv, phy_addr, 0x0019) & 0x01) {
			*speed = HW_SPEED_100_MBPS;
		}
	}

	printk(KERN_INFO "%s: Media Link On %s %s-duplex",
	       sis_priv->name,
	       *speed == HW_SPEED_100_MBPS ?
	       "100mbps" : "10mbps",
	       *duplex == FDX_CAPABLE_FULL_SELECTED ?
	       "full" : "half");
}

/**
 *	sis900_tx_timeout: - sis900 transmit timeout routine
 *	@net_dev: the net device to transmit
 *
 *	print transmit timeout status
 *	disable interrupts and do some tasks
 */
static void
sis900_tx_timeout(struct sis900_private *sis_priv)
{
	long		ioaddr = (long)sis_priv->base_addr;
	clock_t		now;
	unsigned long	flags;
	int		i;

	now = ddi_get_lbolt();

	mutex_enter(&sis_priv->xmitlock); 
	if (!(sis_priv->start && sis_priv->tx_blocked &&
	     (now - sis_priv->trans_start >= TX_TIMEOUT))) {
		mutex_exit(&sis_priv->xmitlock); 
		goto schedule_next;
	}
	mutex_exit(&sis_priv->xmitlock); 

	cmn_err(CE_WARN, "%s: Transmit timeout, cr: %b isr: %b",
		sis_priv->name,
		INL(ioaddr + cr), CR_BITS,
		INL(ioaddr + isr), INTR_BITS);

	/* Block Rx */
	mutex_enter(&sis_priv->intrlock);
	while (sis_priv->intr_busy) {
		cv_broadcast(&sis_priv->drain_cv);
	}

	/* Block Tx */
	mutex_enter(&sis_priv->xmitlock);
	sis_priv->start = FALSE;
	while (sis_priv->tx_busy > 0) {
		cv_broadcast(&sis_priv->drain_cv);
	}

	/* Disable interrupts by clearing the interrupt mask. */
	OUTL(0x0000, ioaddr + imr);

	/* discard unsent packets */
	sis_priv->dirty_tx = sis_priv->cur_tx = 0;
	sis900_free_tx_ring(sis_priv);

	sis_priv->trans_start = ddi_get_lbolt();
	sis_priv->start = TRUE;

	/* FIXME: Should we restart the transmission thread here  ?? */
	OUTL(TxENA, ioaddr + cr);

	/* Enable all known interrupts by setting the interrupt mask. */
	OUTL(OUR_INTR_BITS, ioaddr + imr);

	mutex_exit(&sis_priv->xmitlock);
	mutex_exit(&sis_priv->intrlock);

	gld_sched(sis_priv->macinfo);

schedule_next:
	sis_priv->timeout_id =
		timeout((void (*)(void *))sis900_tx_timeout,
			(void *)sis_priv, TX_TIMEOUT_INTERVAL);
	return;
}

/**
 *	sis900_start_xmit: - sis900 start transmit routine
 *	@skb: socket buffer pointer to put the data being transmitted
 *	@net_dev: the net device to transmit with
 *
 *	Set the transmit buffer descriptor, 
 *	and write TxENA to enable transimt state machine.
 *	tell upper layer if the buffer is full
 */

static int
sis900_start_xmit(struct sis900_private *sis_priv, mblk_t *mp)
{
#ifdef SOLARIS
	long			ioaddr = (long)sis_priv->base_addr;
	mblk_t			*mp0;
	ddi_dma_cookie_t	dmacookie[MAXFRAGMENTS];
	ddi_dma_handle_t	dh[MAXFRAGMENTS];
	int			n;
	int			i;
	size_t			pkt_len;
	unsigned		entry;
	struct lbuf		*lbp = NULL;
	int			frags;
	int			docopy;
	int			err;
	int			ret;
	int			flags;
#ifdef DEBUG_LEVEL
	int			first_cur_tx;
	int			first_entry;
#endif
#ifdef DEBUG_LEVEL
	bzero(dmacookie, sizeof(dmacookie));
#endif
	/*
	 * Caution: the write order is important here, set the field
	 * with the "ownership" bits last.
	 */

	/* check number of fragments */
	pkt_len = 0;
	frags   = 0;
	i       = 0;
	for (mp0 = mp; mp0; mp0 = mp0->b_cont) {
		long	l0, l1;

		pkt_len +=  mp0->b_wptr - mp0->b_rptr;
		l0 = min(pkt_len, PAGESIZE - ((long)mp0->b_rptr & PAGEOFFSET));
		l1 = (pkt_len > l1) ? pkt_len - l1 : 0;

		if (frags == 0) {
			i = l0 / 16;
		} else {
			i--;
		}

		frags++;
		if (l1 > 0) {
			frags++;
			i--;
		}
	}

#ifdef TXSOFTPAD
	if (pkt_len < ETHERMIN) {
		frags++;
		i--;
	}
#endif
	docopy = FALSE;

	/* check possibility of tx underrun */
	if (i < 0) {
		docopy = TRUE;
	}

	if (pkt_len < sis_tx_copybreak || frags > sis_tx_fragments) {
		docopy = TRUE;
		frags = 1;
	}

	/* check required resources */
	mutex_enter(&sis_priv->xmitlock);
	if (!sis_priv->start) {
		sis_priv->tx_blocked = TRUE;
		mutex_exit(&sis_priv->xmitlock);
		/* no resources, try later */
		return 1;
	}

	if (NUM_TX_DESC - SUB(sis_priv->cur_tx, sis_priv->dirty_tx)
					- sis_priv->tx_reserved < frags) {
		sis_priv->tx_blocked = TRUE;
		mutex_exit(&sis_priv->xmitlock);
		/* no resources, try later */
		return 1;
	}
	sis_priv->tx_blocked = FALSE;
	sis_priv->tx_reserved += frags;
	sis_priv->tx_busy++;
	mutex_exit(&sis_priv->xmitlock);

	err = 0;

	if (docopy) {
		caddr_t			bp;
#ifndef ALWAYS_MAPPED
		uint_t			count;
#endif
#ifdef DEBUG
		sis_priv->stats.tx_window_errors++;
#endif
		/* Must use local buffer. */
		if ((lbp = get_lbuf(sis_priv, FALSE)) == NULL) {
			/* no resource, try later */
			err = 1;
			goto x;
		}

		bp = lbp->buf;
		for (mp0 = mp; mp0; mp0 = mp0->b_cont) {
			size_t	len;
			len = mp0->b_wptr - mp0->b_rptr;
			bcopy(mp0->b_rptr, bp, len);
			bp += len;
		}
#ifdef TXSOFTPAD
		/* sis900 has auto padding function for runt packets */
		if (pkt_len < ETHERMIN) {
			bzero(bp, ETHERMIN - pkt_len);
			pkt_len = ETHERMIN;
		}
#endif
#ifdef ALWAYS_MAPPED
		ddi_dma_sync(lbp->dma_handle, (off_t)0,
				pkt_len, DDI_DMA_SYNC_FORDEV);
		dmacookie[0].dmac_address = lbp->dma_addr;
		dmacookie[0].dmac_size    = pkt_len;
#else
		if ((ret = ddi_dma_addr_bind_handle(
				lbp->dma_handle, NULL,
				lbp->buf, pkt_len,
				DDI_DMA_WRITE | DDI_DMA_STREAMING,
				DDI_DMA_DONTWAIT, NULL,
				&dmacookie[0], &count)) != DDI_DMA_MAPPED) {
			ASSERT(ret != DDI_DMA_INUSE);
			free_lbuf(lbp);
			lbp = NULL;	/* sanity */
			err = 1;	/* mp will not be freed */
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
		 * prepare for direct xmit
		 */
		i = 0;
		for (mp0 = mp; mp0; mp0 = mp0->b_cont) {
			ddi_dma_handle_t	dma_handle;
			uint_t			count;
			size_t			len;

			len = mp0->b_wptr - mp0->b_rptr;
			dma_handle = get_dma_handle(sis_priv);
			ASSERT(dma_handle != NULL);

			if ((ret = ddi_dma_addr_bind_handle(
				dma_handle, NULL,
				mp0->b_rptr, len,
				DDI_DMA_WRITE | DDI_DMA_STREAMING,
				DDI_DMA_DONTWAIT, NULL,
				&dmacookie[i], &count)) != DDI_DMA_MAPPED) {

				/* failed to bind dma resource */
				while (i--) {
					if ((dma_handle = dh[i]) == NULL) {
						continue;
					}
					ddi_dma_unbind_handle(dma_handle);
					free_dma_handle(sis_priv, dma_handle);
				}
				err = 1;
				break;
			}
			ASSERT(count == 1 || count == 2);
#ifdef notdef
			ddi_dma_sync(dma_handle, 0, len, DDI_DMA_SYNC_FORDEV);
#endif
			dh[i++] = dma_handle;

			/* collect rest of dma cookies */
			while (--count > 0) {
				ddi_dma_nextcookie(dma_handle, &dmacookie[i]);
				dh[i++] = NULL;
			}
		}
#ifdef TXSOFTPAD
		if (pkt_len < ETHERMIN) {
			/* add pad fragment */
			dmacookie[i].dmac_address = sis_priv->tx_pad_dma;
			dmacookie[i].dmac_size    = ETHERMIN - pkt_len;
			dh[i++] = NULL;
		}
#endif
	}
x:
#if DEBUG_LEVEL > 2
	if (i > 4) {
		cmn_err(CE_CONT, "%s: %s: frags:%d (%d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d)",
			sis_priv->name, __FUNCTION__, i,
			dmacookie[0].dmac_size,
			dmacookie[1].dmac_size,
			dmacookie[2].dmac_size,
			dmacookie[3].dmac_size,
			dmacookie[4].dmac_size,
			dmacookie[5].dmac_size,
			dmacookie[6].dmac_size,
			dmacookie[7].dmac_size,
			dmacookie[8].dmac_size,
			dmacookie[9].dmac_size,
			dmacookie[10].dmac_size,
			dmacookie[11].dmac_size,
			dmacookie[12].dmac_size,
			dmacookie[13].dmac_size,
			dmacookie[14].dmac_size,
			dmacookie[15].dmac_size);
	}
#endif
	mutex_enter(&sis_priv->xmitlock);
	sis_priv->tx_busy--;
	sis_priv->tx_reserved -= frags;
	if (!sis_priv->start && sis_priv->tx_busy == 0) {
		/* someone may wait for me */
		cv_broadcast(&sis_priv->drain_cv);
	}

	if (err || !sis_priv->start) {
		/* something wrong, no resources? */
		sis_priv->tx_blocked = TRUE;
		mutex_exit(&sis_priv->xmitlock);
		return 1;
	}

	/*
	 * write tx descriptor
	 */
	entry = ((unsigned)(sis_priv->cur_tx + i - 1)) % NUM_TX_DESC;
	sis_priv->tx_mp[entry]  = mp;
	sis_priv->tx_lbp[entry] = lbp;

	flags = OWN;	/* for the last fragment */
	for (n=i; n--; entry=((unsigned)(entry-1))%NUM_TX_DESC) {
		BufferDesc 	*tdp = &sis_priv->tx_ring[entry];

		sis_priv->tx_dma_handle_used[entry] = dh[n];
		tdp->bufptr = dmacookie[n].dmac_address;
		tdp->cmdsts = (dmacookie[n].dmac_size & DSIZE) | flags;
		flags = OWN | MORE;
	}
#ifdef DEBUG_LEVEL
	first_entry = ((unsigned)(entry + 1)) % NUM_TX_DESC;
	first_cur_tx = sis_priv->cur_tx;
#endif
	DPRINTF(2, "%s: Transmit frame #%d-#%d queued in slot %d-%d.\n",
		sis_priv->name,
		first_cur_tx, sis_priv->cur_tx + i - 1,
		first_entry, (first_entry + i - 1) % NUM_TX_DESC);

	sis_priv->cur_tx += i;

	/* Wake the potentially-idle transmit channel. */
	OUTL(TxENA, ioaddr + cr);
	sis_priv->trans_start = ddi_get_lbolt();

	mutex_exit(&sis_priv->xmitlock);

	if (lbp != NULL) {
		/* local buffer is used instead of mp */
		freemsg(mp0);
	}

	return 0;
#endif /* SOLARIS */
}

/**
 *	sis900_interrupt: - sis900 interrupt handler
 *	@irq: the irq number
 *	@dev_instance: the client data object
 *	@regs: snapshot of processor context
 *
 *	The interrupt handler does all of the Rx thread work, 
 *	and cleans up after the Tx thread
 */
static u_int
sis_interrupt(gld_mac_info_t *macinfo)
{
	struct sis900_private	*sis_priv;
	long		ioaddr;
	uint32_t	status;
	int		serviced = DDI_INTR_UNCLAIMED;
	int		restart_tx = FALSE;

	sis_priv = (struct sis900_private *)macinfo->gldm_private;
	ioaddr = (long)sis_priv->base_addr;

	mutex_enter(&sis_priv->intrlock);

	status = INL(ioaddr + isr);

	DPRINTF(3, "%s: sis_interrupt: called, status 0x%b",
				sis_priv->name, status, INTR_BITS);

	if ((status & (HIBERR|TxURN|TxERR|TxIDLE|RxORN|RxERR|RxOK)) != 0) {
		serviced = DDI_INTR_CLAIMED;
		sis_priv->intr_busy = TRUE;

		if (!sis_priv->start) {
			goto x;
		}

		/*
		 * why dow't we break after Tx/Rx case ??
		 * keyword: full-duplex	
		 */
		if (status & (RxORN | RxERR | RxOK)) {
			/* Rx interrupt */
			sis900_rx(sis_priv);
		}

		if (status & (TxURN | TxERR | TxIDLE)) {
			/* Tx interrupt */
			mutex_enter(&sis_priv->xmitlock);
			sis900_finish_xmit(sis_priv);
			restart_tx = sis_priv->tx_blocked;
			mutex_exit(&sis_priv->xmitlock);
		}

		/* something strange happened !!! */
		if (status & HIBERR) {
			cmn_err(CE_WARN, "%s: Abnormal interrupt, status %b.",
				sis_priv->name, status, INTR_BITS);
		}
x:
		if (!sis_priv->start) {
			cv_broadcast(&sis_priv->drain_cv);
		}
		sis_priv->intr_busy = FALSE;
	}

	DPRINTF(3, "%s: exiting interrupt, interrupt status: %b.",
		       sis_priv->name, INL(ioaddr + isr), INTR_BITS);

	mutex_exit(&sis_priv->intrlock);

	if (restart_tx) {
		gld_sched(macinfo);
	}

	return serviced;
}

/**
 *	sis900_rx: - sis900 receive routine
 *	@net_dev: the net device which receives data
 *
 *	Process receive interrupt events, 
 *	put buffer to higher layer and refill buffer pool
 *	Note: This fucntion is called by interrupt handler, 
 *	don't do "too much" work here
 */
static int
sis900_rx(struct sis900_private *sis_priv)
{
	long	ioaddr = (long)sis_priv->base_addr;
	int	errors = 0;
	int	fifo_errors = 0;
	int	runt_errors = 0;
	int	toolong_errors = 0;
	int	frame_errors = 0;
	int	crc_errors = 0;
	int	dropped = 0;
	int	err;

	unsigned int entry = ((unsigned)sis_priv->cur_rx) % NUM_RX_DESC;
	u32 rx_status = sis_priv->rx_ring[entry].cmdsts;

	DPRINTF(3, "sis900_rx, cur_rx:%d, dirty_rx:%d status:%b",
			sis_priv->cur_rx, sis_priv->dirty_rx,
			rx_status, RXSTAT_BITS);

	mutex_exit(&sis_priv->intrlock);


	while (rx_status & OWN) {
		unsigned int	rx_size;
		mblk_t		*mp;
		struct lbuf	*lbp;

		mp = NULL;
		rx_size = (rx_status & DSIZE) - CRC_SIZE;

		if (rx_status & (ABORT|OVERRUN|TOOLONG|RUNT|RXISERR|CRCERR|FAERR)) {
			/* corrupted packet received */
			DPRINTF(0, "%s: Corrupted packet "
				"received, buffer status: %b",
				sis_priv->name, rx_status, RXSTAT_BITS);

			/* collect statics information */
			errors++;
			if (rx_status & OVERRUN) {
				fifo_errors++;
			}
			if (rx_status & RUNT) {
				runt_errors++;
			}
			if (rx_status & TOOLONG) {
				toolong_errors++;
			}
			if (rx_status & (RXISERR | FAERR)) {
				frame_errors++;
			}
			if (rx_status & CRCERR) {
				crc_errors++;
			}
		}
		else {
			/*
			 * This situation should never happen, but due to
			 * some unknow bugs, it is possible that
			 * we are working on NULL mblk :-(
			 */
			if ((lbp = sis_priv->rx_lbp[entry]) == NULL) {
				cmn_err(CE_WARN, "%s: NULL pointer " 
				       "encountered in Rx ring, skipping",
				       sis_priv->name);
				break;
			}

			if (rx_size < sis_rx_copybreak) {
				if ((mp = allocb(rx_size, BPRI_LO)) == NULL) {
					dropped++;
					goto next;
				}
				mp->b_wptr = mp->b_rptr + rx_size;
				ddi_dma_sync(lbp->dma_handle, 0, rx_size,
							DDI_DMA_SYNC_FORKERNEL);
				bcopy(lbp->buf, mp->b_rptr, rx_size);

			}
			else {
				/* allocate msg block structure */
				if ((mp = esballoc(lbp->buf, rx_size, BPRI_LO,
							&lbp->frtn)) == NULL) {
					/* free_lbuf(lbp); */
					dropped++;
					goto next;
				}
				mp->b_wptr = mp->b_rptr + rx_size;
#ifdef ALWAYS_MAPPED
				ddi_dma_sync(lbp->dma_handle, 0, rx_size,
						DDI_DMA_SYNC_FORKERNEL);
#else
				/* release dma resources */
				ddi_dma_unbind_handle(lbp->dma_handle);
#endif /* ALWAYS_MAPPED */
				sis_priv->rx_lbp[entry] = NULL;
			}
			sis_priv->last_rx = ddi_get_lbolt();

			if (mp != NULL) {
				gld_recv(sis_priv->macinfo, mp);
			}
next:
		}
		sis_priv->cur_rx++;
		entry = ((unsigned)sis_priv->cur_rx) % NUM_RX_DESC;
		rx_status = sis_priv->rx_ring[entry].cmdsts;
	} /* while */

	mutex_enter(&sis_priv->intrlock);

	/*
	 * refill the Rx buffer, what if the rate of refilling is slower than 
	 * consuming ??
	 */
	for (; SUB(sis_priv->cur_rx, sis_priv->dirty_rx) > 0;
							sis_priv->dirty_rx++) {
		struct lbuf		*lbp;
		ddi_dma_cookie_t	cookie;
		uint_t			count;

		entry = ((unsigned)sis_priv->dirty_rx) % NUM_RX_DESC;

		if ((lbp = sis_priv->rx_lbp[entry]) != NULL) {
			/* reset rx-desc status only */
			sis_priv->rx_ring[entry].cmdsts = lbp->buf_len;
			continue;
		}

		if ((lbp = get_lbuf(sis_priv, FALSE)) == NULL) {
			/*
			 * Not enough memory for skbuff, this makes a "hole"
			 * on the buffer ring, it is not clear how the 
			 * hardware will react to this kind of degenerated 
			 * buffer
			 */
			cmn_err(CE_WARN, "%s: Memory squeeze,deferring packet.",
				sis_priv->name);
			dropped++;
			break;
		}
#ifdef ALWAYS_MAPPED
		sis_priv->rx_ring[entry].bufptr = lbp->dma_addr;
#else
		if ((err = ddi_dma_addr_bind_handle(lbp->dma_handle,
					NULL,
					lbp->buf, lbp->buf_len,
					DDI_DMA_READ | DDI_DMA_STREAMING,
					DDI_DMA_DONTWAIT, NULL,
					&cookie, &count)) != DDI_SUCCESS) {
			ASSERT(err != DDI_DMA_INUSE);
			free_lbuf(lbp);
			break;
		}
		ASSERT(count == 1);
		sis_priv->rx_ring[entry].bufptr = cookie.dmac_address;
#endif /* ALWAYS_MAPPED */
		sis_priv->rx_ring[entry].cmdsts = lbp->buf_len;
		sis_priv->rx_lbp[entry] = lbp;
	}

	/* re-enable the potentially idle receive state matchine */
	OUTL(RxENA , ioaddr + cr );

	sis_priv->stats.rx_errors += errors;
	sis_priv->stats.rx_fifo_errors += fifo_errors;
	sis_priv->stats.rx_runt_errors += runt_errors;
	sis_priv->stats.rx_toolong_errors += toolong_errors;
	sis_priv->stats.rx_frame_errors += frame_errors;
	sis_priv->stats.rx_crc_errors += crc_errors;
	sis_priv->stats.rx_dropped += dropped;

	return 0;
}

/**
 *	sis900_finish_xmit: - finish up transmission of packets
 *	@net_dev: the net device to be transmitted on
 *
 *	Check for error condition and free socket buffer etc 
 *	schedule for more transmission as needed
 *	Note: This fucntion is called by interrupt handler, 
 *	don't do "too much" work here
 */
static void
sis900_finish_xmit(struct sis900_private *sis_priv)
{
	ASSERT(mutex_owned(&sis_priv->xmitlock));
	ASSERT(SUB(sis_priv->cur_tx, sis_priv->dirty_tx) >= 0);

	for (; sis_priv->dirty_tx != sis_priv->cur_tx; sis_priv->dirty_tx++) {
		ddi_dma_handle_t dh;
		struct lbuf	*lbp;
		mblk_t		*mp;
		unsigned int	entry;
		uint32_t	tx_status;

		entry = ((unsigned)sis_priv->dirty_tx) % NUM_TX_DESC;
		tx_status = sis_priv->tx_ring[entry].cmdsts;

		if (tx_status & OWN) {
			/*
			 * The packet is not transmitted yet(owned by hardware)!
			 * Note: the interrupt is generated only when Tx Machine
			 * is idle, so this is an almost impossible case
			 */
			break;
		}

		if ((dh = sis_priv->tx_dma_handle_used[entry]) != NULL) {
			/* free dma resource */
			ddi_dma_unbind_handle(dh);
			free_dma_handle(sis_priv, dh);
			sis_priv->tx_dma_handle_used[entry] = NULL;
		}

		if (tx_status & MORE) {
			/* this is not last fragment */
			ASSERT(sis_priv->tx_mp[entry] == NULL);
			ASSERT(sis_priv->tx_lbp[entry] == NULL);
			continue;
		}

		/*
		 * For the last fragment
		 */
		if (tx_status & (ABORT | UNDERRUN | OWCOLL)) {
			/* packet unsuccessfully transmitted */
			DPRINTF(2, "%s: Transmit error, Tx status %b",
				       sis_priv->name, tx_status, TXSTAT_BITS);

			sis_priv->stats.tx_errors++;
			if (tx_status & UNDERRUN) {
				sis_priv->stats.tx_fifo_errors++;
			}
			if (tx_status & EXCCOLL) {
				sis_priv->stats.tx_aborted_errors++;
				sis_priv->stats.collisions += 16;
			}
			if (tx_status & NOCARRIER) {
				sis_priv->stats.tx_carrier_errors++;
			}
			if (tx_status & OWCOLL) {
				sis_priv->stats.tx_window_errors++;
			}
		}
		else {
			int	cols;

			ASSERT(tx_status & OK);

			cols = (tx_status & COLCNT)>>16;

			if (cols > 0) {
				if (cols == 1) {
					sis_priv->stats.tx_first_coll++;
				} else /* (cols > 1) */ {
					sis_priv->stats.tx_multi_coll++;
				}
				sis_priv->stats.collisions += cols;
			}
			else if (tx_status & DEFERD) {
				sis_priv->stats.tx_defer++;
			}
		}

		if ((mp = sis_priv->tx_mp[entry]) != NULL) {
			/* Free the original mblk. */
			ASSERT(sis_priv->tx_lbp[entry] == NULL);
			freemsg(mp);
			sis_priv->tx_mp[entry] = NULL;
		}
		else if (lbp = sis_priv->tx_lbp[entry]) {
			/* Free tx bounce buffer. */
#ifndef ALWAYS_MAPPED
			ddi_dma_unbind_handle(lbp->dma_handle);
#endif
			free_lbuf(lbp);
			sis_priv->tx_lbp[entry] = NULL;
		}
#ifdef DEBUG
		else {
			cmn_err(CE_PANIC,
			  "%s: tx_mp[entry] == NULL && tx_lbp[entry] == NULL");
			/* Not Reached */
		}
#endif /* DEBUG */
#ifdef SANITY
		sis_priv->tx_ring[entry].bufptr = 0;
		sis_priv->tx_ring[entry].cmdsts = 0;
#endif
	}
}

/**
 *	sis900_close: - close sis900 device 
 *	@net_dev: the net device to be closed
 *
 *	Disable interrupts, stop the Tx and Rx Status Machine 
 *	free Tx and RX socket buffer
 */
static int
sis900_close(struct sis900_private *sis_priv)
{
	long		ioaddr = (long)sis_priv->base_addr;
	timeout_id_t	old_id;
	int		i;

	if (sis_priv->timer_id != 0) {
		do {
			untimeout(old_id = sis_priv->timer_id);
		} while (old_id != sis_priv->timer_id);
		sis_priv->timer_id = 0;
	}

	mutex_enter(&sis_priv->intrlock);
	mutex_enter(&sis_priv->xmitlock);
	sis_priv->start = FALSE;
	mutex_exit(&sis_priv->xmitlock);

	/* stop Rx */
	while (sis_priv->intr_busy) {
		cv_wait(&sis_priv->drain_cv, &sis_priv->intrlock);
	}

	/* stop Tx */
	mutex_enter(&sis_priv->xmitlock);
	while (sis_priv->tx_busy > 0) {
		cv_wait(&sis_priv->drain_cv, &sis_priv->xmitlock);
	}
	
	/* Disable interrupts by clearing the interrupt mask. */
	OUTL(0x0000, ioaddr + imr);
	OUTL(0x0000, ioaddr + ier);

	/* Stop the chip's Tx and Rx Status Machine */
	OUTL(RxDIS | TxDIS, ioaddr + cr);

	/* Free Tx and RX buffer */
	sis900_free_tx_ring(sis_priv);
	sis900_free_rx_ring(sis_priv);

	mutex_exit(&sis_priv->xmitlock);
	mutex_exit(&sis_priv->intrlock);

	/* Green! Put the chip in low-power mode. */

	return 0;
}

/**
 *	sis900_compute_hashtable_index: - compute hashtable index 
 *	@addr: multicast address
 *	@revision: revision id of chip
 *
 *	SiS 900 uses the most sigificant 7 bits to index a 128 bits multicast
 *	hash table, which makes this function a little bit different from other drivers
 *	SiS 900 B0 & 635 M/B uses the most significat 8 bits to index 256 bits
 *   	multicast hash table. 
 */

static uint16_t
sis900_compute_hashtable_index(uint8_t *addr, uint8_t revision)
{

/* what is the correct value of the POLYNOMIAL ??
   Donald Becker use 0x04C11DB7U
   Joseph Zbiciak im14u2c@primenet.com gives me the
   correct answer, thank you Joe !! */
#define POLYNOMIAL 0x04C11DB7L
	u32 crc = 0xffffffff, msb;
	int  i, j;
	u32  byte;

	for (i = 0; i < 6; i++) {
		byte = *addr++;
		for (j = 0; j < 8; j++) {
			msb = crc >> 31;
			crc <<= 1;
			if (msb ^ (byte & 1)) {
				crc ^= POLYNOMIAL;
			}
			byte >>= 1;
		}
	}

	/* leave 8 or 7 most siginifant bits */
	if ((revision == SIS635A_900_REV) || (revision == SIS900B_900_REV))
		return ((int)(crc >> 24));
	else
		return ((int)(crc >> 25));
}

/**
 *	sis900_set_rx_mode: - Set SiS900 receive mode 
 *	@net_dev: the net device to be set
 *
 *	Set SiS900 receive mode for promiscuous, multicast, or broadcast mode.
 *	And set the appropriate multicast filter.
 *	Multicast hash table changes from 128 to 256 bits for 635M/B & 900B0.
 */
static void
sis900_set_rx_mode(struct sis900_private *sis_priv)
{
	long		ioaddr = (long)sis_priv->base_addr;
	uint16_t	mc_filter[16] = {0};	/* 256/128 bits multicast hash table */
	int		i, table_entries;
	uint32_t	rx_mode;
	uint8_t		revision;

	/* 635 Hash Table entires = 256(2^16) */
	revision = sis_priv->revid;

	if((revision == SIS635A_900_REV) || (revision == SIS900B_900_REV)) {
		table_entries = 16;
	}
	else {
		table_entries = 8;
	}
	if (sis_priv->flags & IFF_PROMISC) {
		/* Accept any kinds of packets */
		rx_mode = RFPromiscuous;
		for (i = 0; i < table_entries; i++) {
			mc_filter[i] = 0xffff;
		}
	}
	else if ((sis_priv->mc_count > sis_multicast_filter_limit) ||
		   (sis_priv->flags & IFF_ALLMULTI)) {
		/* too many multicast addresses or accept all multicast packet */
		rx_mode = RFAAB | RFAAM;
		for (i = 0; i < table_entries; i++) {
			mc_filter[i] = 0xffff;
		}
	}
	else {
		/*
		 * Accept Broadcast packet, destination address matchs
		 * our MAC address, use Receive Filter to reject unwanted
		 * MCAST packet
		 */
#ifdef LINUX
		struct dev_mc_list *mclist;

		for (i = 0, mclist = net_dev->mc_list;
			mclist && i < net_dev->mc_count;
				i++, mclist = mclist->next) {

			set_bit(
		sis900_compute_hashtable_index(mclist->dmi_addr, revision),
				mc_filter);
		}
#endif
#ifdef SOLARIS
#define	set_bit(ix, p)	\
	((uint8_t *)(p))[(ix)/8] |= 1 << (ix % 8)

		for (i = 0; i < sis_priv->mc_count; i++) {

			set_bit(
		sis900_compute_hashtable_index(
			sis_priv->mc_list[i].ether_addr_octet, revision),
				mc_filter);
		}
#undef set_bit
#endif
		rx_mode = RFAAB;
	}

	/* update Multicast Hash Table in Receive Filter */
	for (i = 0; i < table_entries; i++) {
                /* why plus 0x04 ??, That makes the correct value for hash table. */
		OUTL((u32)(0x00000004+i) << RFADDR_shift, ioaddr + rfcr);
		OUTL(mc_filter[i], ioaddr + rfdr);
	}

	OUTL(RFEN | rx_mode, ioaddr + rfcr);

	return;
}

/**
 *	sis900_reset: - Reset sis900 MAC 
 *	@net_dev: the net device to reset
 *
 *	reset sis900 MAC and wait until finished
 *	reset through command register
 *	change backoff algorithm for 900B0 & 635 M/B
 */
static void
sis900_reset(struct sis900_private *sis_priv)
{
	long		ioaddr = (long)sis_priv->base_addr;
	int		i = 0;
	uint32_t	status = TxRCMP | RxRCMP;
	uint8_t		revision;

	OUTL(0, ioaddr + ier);
	OUTL(0, ioaddr + imr);
	OUTL(0, ioaddr + rfcr);

	OUTL(RxRESET | TxRESET | RESET, ioaddr + cr);
	
	/* Check that the chip has finished the reset. */
	while (status && (i++ < 1000)) {
		drv_usecwait(10);
		status ^= (INL(isr + ioaddr) & status);
	}

	revision = sis_priv->revid;

	if ((revision == SIS635A_900_REV) || (revision == SIS900B_900_REV)) {
		OUTL(PESEL | RND_CNT, ioaddr + cfg);
	}
	else {
		OUTL(PESEL, ioaddr + cfg);
	}
}

/**
 *	sis900_remove: - Remove sis900 device 
 *	@pci_dev: the pci device to be removed
 *
 *	remove and release SiS900 net device
 */
#ifdef LINUX
static void __devexit sis900_remove(struct pci_dev *pci_dev)
{
	struct net_device *net_dev = pci_get_drvdata(pci_dev);
	struct sis900_private * sis_priv = net_dev->priv;
	struct mii_phy *phy = NULL;

	while (sis_priv->first_mii) {
		phy = sis_priv->first_mii;
		sis_priv->first_mii = phy->next;
		kfree(phy);
	}

	pci_free_consistent(pci_dev, RX_TOTAL_SIZE, sis_priv->rx_ring,
		sis_priv->rx_ring_dma);
	pci_free_consistent(pci_dev, TX_TOTAL_SIZE, sis_priv->tx_ring,
		sis_priv->tx_ring_dma);
	unregister_netdev(net_dev);
	kfree(net_dev);
	pci_release_regions(pci_dev);
	pci_set_drvdata(pci_dev, NULL);
}

#define SIS900_MODULE_NAME "sis900"

static struct pci_driver sis900_pci_driver = {
	name:		SIS900_MODULE_NAME,
	id_table:	sis900_pci_tbl,
	probe:		sis900_probe,
	remove:		sis900_remove,
};

static int __init sis900_init_module(void)
{
/* when a module, this is printed whether or not devices are found in probe */
#ifdef MODULE
	printk(version);
#endif

	return pci_module_init(&sis900_pci_driver);
}

static void __exit sis900_cleanup_module(void)
{
	pci_unregister_driver(&sis900_pci_driver);
}

module_init(sis900_init_module);
module_exit(sis900_cleanup_module);
#endif /* LINUX */
