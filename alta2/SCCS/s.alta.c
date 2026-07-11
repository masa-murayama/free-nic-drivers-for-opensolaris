h60725
s 03191/00000/00000
d D 1.1 02/10/01 02:00:05 mrym 1 0
c date and time created 02/10/01 02:00:05 by mrym
e
u
U
f e 0
t
T
I 1
/*
 *  Sundance ST201 Fast Ethernet MAC driver
 *  %W% %E%
 *
 *  Copyright (C) 2002  Masayuki Murayama (KHF04453@nifty.ne.jp)
 *
 *  CAUTION: NO WARRANTY
 *  This software may be used and distributed according to the terms
 *  of the Lesser GNU Public License, incorporated herein by reference.
 */

/*
 Change log
 */

/*
 TODO:
 Rx descriptor ring - done
 disable Rx early  - done
 Tx start thresh - done
 Tx release thresh - done
 Tx Timeout - done
 Tx Error
 Rx Error - done
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
#include <sys/gld.h>
#include <sys/ddi_impldefs.h>

#include <sys/pci.h>
#include "mii.h"
#include "st201reg.h"

char	ident[] = "ST201 NIC driver v" VERSION;
char	_depends_on[] = {"misc/gld"};

/* Debugging support */
#ifdef DEBUG_LEVEL
static int alta_debug = DEBUG_LEVEL;
#define	DPRINTF(n, args)	if (alta_debug>(n)) cmn_err args
#else
#define	DPRINTF(n, args)
#endif

/*
 * Useful macros and typedefs
 */
#define	FALSE	(0)
#define	TRUE	(!FALSE)

/*
 * ST201 TFD and RFD structure
 */
#define	MAXTXFRAGS	3
struct alta_tfd{
	uint32_t	TxDMANextPtr;
	uint32_t	TxFrameControl;
	struct {
		uint32_t	Addr;
		uint32_t	Len;
	} TxDMAFrag[MAXTXFRAGS*2];
};

#define	MAXRXFRAGS	1
struct alta_rfd{
	uint32_t	RxDMANextPtr;
	uint32_t	RxFrameStatus;
	struct {
		uint32_t	Addr;
		uint32_t	Len;
	} RxDMAFrag[MAXRXFRAGS*2];
};

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
 * Our configuration
 */
#define	OUR_INTR_BITS \
	(INT_HostError | INT_TxComplete | \
	 INT_UpdateStats | INT_TxDMAComplete | INT_RxDMAComplete)

#define TX_RING_SIZE	16
#define RX_RING_SIZE	64

#define TX_TIMEOUT		(drv_usectohz(5*1000000))
#define TX_TIMEOUT_INTERVAL	(drv_usectohz(1*1000000))
#define LINK_WATCH_INTERVAL	(drv_usectohz(1*1000000))	/* 1 sec */


/*
 * Supported chips
 */
struct chip_info {
	uint16_t	venid;
	uint16_t	devid;
	char		*name;
};

static struct chip_info alta_chiptbl[] = {
	{PCI_VID_DLINK,		PCI_DID_DFE550, "DL10050"},
	{PCI_VID_SUNDANCE,	PCI_DID_ST201,	"ST201"},
};
#define CHIPTABLESIZE   (sizeof(alta_chiptbl)/sizeof(struct chip_info))

/*
 * Macros to distinct chip generation.
 */

/*
 * Local structures
 */

struct alta_stats {
	uint32_t	intr;

	uint32_t	crc;
	uint32_t	errrcv;
	uint32_t	overflow;
	uint32_t	frame;
	uint32_t	missed;
	uint32_t	runt;
	uint32_t	frame_too_long;
	uint32_t	norcvbuf;

	uint32_t	collisions;
	uint32_t	first_coll;
	uint32_t	multi_coll;
	uint32_t	excoll;
	uint32_t	nocarrier;
	uint32_t	defer;
	uint32_t	errxmt;
	uint32_t	underflow;
	uint32_t	xmtlatecoll;
};

#define	ALTA_LOCAL_BUF_INIT	(RX_RING_SIZE*2)
#define	ALTA_LOCAL_BUF_MAX	64*1024

/* mbk buffer management */
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
	struct alta_dev	*devp;
};

#define	ALTAMAXMC		GLD_MAX_MULTICAST
#define	ALTAMCALLOC		(sizeof(struct ether_addr) * ALTAMAXMC)

typedef	int32_t			seqnum_t;
#define	SUB(x, y)		((seqnum_t)((x) - (y)))
#define	SLOT(seqnum, size)	(((unsigned int)(seqnum)) & ((size)-1))

struct alta_dev {
	dev_info_t		*dip;
	gld_mac_info_t		*macinfo;
	char			name[32];
	void			*base_addr;
	ddi_acc_handle_t	regs_handle;
	ddi_iblock_cookie_t	iblock_cookie;

	/* MAC address information */
	struct ether_addr	cur_addr;
	struct ether_addr	dev_addr;

	/* Descriptor rings */
	struct alta_rfd		*rx_ring;
	struct alta_tfd		*tx_ring;
	uint32_t		rx_ring_dma;	/* dma address from PCI bus */
	uint32_t		tx_ring_dma;	/* dma address from PCI bus */
	ddi_dma_handle_t	desc_dma_handle;
	ddi_acc_handle_t	desc_acc_handle;
#ifdef TXSOFTPAD
	uint32_t		tx_pad_dma;
#endif

	/* RX ring management */
	kmutex_t		intrlock;
	boolean_t		intr_busy;
	seqnum_t		rx_head;
	seqnum_t		rx_tail;
	struct lbuf		*rx_lbp[RX_RING_SIZE];

	/* TX ring management */
	kmutex_t		xmitlock;
	kcondvar_t		drain_cv;
	seqnum_t		tx_head;
	seqnum_t		tx_tail;
	mblk_t 			*tx_mp[TX_RING_SIZE];
	struct lbuf		*tx_lbp[TX_RING_SIZE];
	ddi_dma_handle_t	tx_dma_handle_used[TX_RING_SIZE][MAXTXFRAGS*2];

	int			tx_reserved;
	clock_t			tx_start_time;
	int			tx_busy;
	boolean_t		tx_blocked;
	boolean_t		tx_list_loaded;

	/* NIC state */
	boolean_t		start;

	/* timer and watchdog */
	timeout_id_t		timeout_id;

	/* Local buffer management */
	struct lbuf		*buf_free_list;
	kmutex_t		buflock;
	int			buf_allocated;
	int			buf_free;

	/* free dma handle management */
	kmutex_t		dma_handle_lock;
	int			dma_handle_free;
	ddi_dma_handle_t	dma_handle[TX_RING_SIZE*MAXTXFRAGS];
#define	ALTA_MAX_BUF	1000

	/* MII mamagement */
	boolean_t		full_duplex;
	boolean_t		speed100;
	boolean_t		flow_control;
	boolean_t		flow_control_req;
	int			mii_state;
	int			mii_phy_addr;		
#define		MII_STATE_RESETTING		0
#define		MII_STATE_AUTONEGOTIATING	1
#define		MII_STATE_LINKUP		2
#define		MII_STATE_LINKDOWN		3

	int			mii_timer;
#define		MII_RESET_TIMEOUT	1
#define		MII_AUTONEGO_TIMEOUT	5
#define		MII_LINKDOWN_TIMEOUT	10

	boolean_t		mii_fixedmode;
	timeout_id_t		link_watcher_id;
	boolean_t		mii_supress_msg;

	/* multcast list */
	int			mc_count;
	struct ether_addr	*mc_list;
	int			rxmode;
#define		RXMODE_PROMISC	0x01
#define		RXMODE_ALLMULTI	0x02

	/* Misc HW info and status */
	struct chip_info	*chip;
	uint8_t			revid;		/* chip revision id */

	/* statistcs */
	struct alta_stats		stats;
};

static int alta_mii_init(struct alta_dev *);
static void alta_mii_stop(struct alta_dev *);
static void  alta_mii_sync(struct alta_dev *);
static uint16_t  alta_mii_read(struct alta_dev *, int);
static void alta_mii_write(struct alta_dev *, int, uint16_t);
#define	MII_SYNC(dp)		alta_mii_sync(dp)
#define	MII_READ(dp, reg)	alta_mii_read(dp, reg)
#define	MII_WRITE(dp, reg, val)	alta_mii_write(dp, reg, val)

/* private functions */
static int alta_reset_chip(struct alta_dev *);
static void alta_init_chip(struct alta_dev *);
static void alta_start_chip(struct alta_dev *);
static int alta_set_media(struct alta_dev *);
static void alta_set_rx_filter(struct alta_dev *);
static void alta_get_stats_chip(struct alta_dev *);
static int alta_init_mac_addr(struct alta_dev *);

static int alta_append_rxbuf(struct alta_dev *, struct lbuf *, int);
static void alta_tx_timeout(struct alta_dev *);
static void alta_txdma_done(struct alta_dev *);
static void alta_receive(struct alta_dev *);

/* local buffer management */
static struct lbuf *alta_get_lbuf(struct alta_dev *, int);
static void alta_free_lbuf(struct lbuf *);
static void alta_reclaim_rxbuf(struct lbuf *lbp);
static int alta_alloc_memory(struct alta_dev *);
static void alta_init_rx_desc(struct alta_dev *);
static void alta_free_memory(struct alta_dev *);

/* DDI/DKI functions */
static int altaattach(dev_info_t *, ddi_attach_cmd_t);
static int altadetach(dev_info_t *, ddi_detach_cmd_t);

/* GLD interfaces */
static int alta_reset(gld_mac_info_t *);
static int alta_start(gld_mac_info_t *);
static int alta_stop(gld_mac_info_t *);
static int alta_set_mac_address(gld_mac_info_t *, unsigned char *);
static int alta_set_multicast(gld_mac_info_t *, struct ether_addr *, int);
static int alta_set_promiscuous(gld_mac_info_t *, int);
static int alta_get_stats(gld_mac_info_t *, struct gld_stats *);
static int alta_send(gld_mac_info_t *, mblk_t *);
static u_int alta_interrupt(gld_mac_info_t *);


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
	DMA_ATTR_V0,		/* dma_attr_version */
	0,			/* dma_attr_addr_lo */
	0xffffffffull,		/* dma_attr_addr_hi */
	0xffffffffull,		/* dma_attr_count_max */
	4,			/* dma_attr_align */
	0xffffffff,		/* dma_attr_burstsizes */
	1,			/* dma_attr_minxfer */
	0xffffffffull,		/* dma_attr_maxxfer */
	0xffffffffull,		/* dma_attr_seg */
	16,			/* dma_attr_sgllen */
	1,			/* dma_attr_granular */
	0			/* dma_attr_flags */
};

static ddi_dma_attr_t dma_attr_nosc = {
	DMA_ATTR_V0,				/* dma_attr_version */
	0,			/* dma_attr_addr_lo */
	0xffffffffull,		/* dma_attr_addr_hi */
	0xffffffffull,		/* dma_attr_count_max */
	4,			/* dma_attr_align */
	0xffffffff,		/* dma_attr_burstsizes */
	1,			/* dma_attr_minxfer */
	0xffffffffull,		/* dma_attr_maxxfer */
	0xffffffffull,		/* dma_attr_seg */
	1,			/* dma_attr_sgllen */
	1,			/* dma_attr_granular */
	0			/* dma_attr_flags */
};

/*
 * Ethernet broadcast address definition.
 */
static	struct ether_addr	etherbroadcastaddr = {
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff
};

static	struct module_info altaminfo = {
	0,			/* mi_idnum */
	"alta",			/* mi_idname */
	0,			/* mi_minpsz */
	ETHERMTU,		/* mi_maxpsz */
	32*1024,		/* mi_hiwat */
	1,			/* mi_lowat */
};

static	struct qinit altarinit = {
	(int (*)()) NULL,	/* qi_putp */
	gld_rsrv,		/* qi_srvp */
	gld_open,		/* qi_qopen */
	gld_close,		/* qi_qclose */
	(int (*)()) NULL,	/* qi_qadmin */
	&altaminfo,		/* qi_minfo */
	NULL			/* qi_mstat */
};

static	struct qinit altawinit = {
	gld_wput,		/* qi_putp */
	gld_wsrv,		/* qi_srvp */
	(int (*)()) NULL,	/* qi_qopen */
	(int (*)()) NULL,	/* qi_qclose */
	(int (*)()) NULL,	/* qi_qadmin */
	&altaminfo,		/* qi_minfo */
	NULL			/* qi_mstat */
};

static struct streamtab	alta_info = {
	&altarinit,	/* st_rdinit */
	&altawinit,	/* st_wrinit */
	NULL,		/* st_muxrinit */
	NULL		/* st_muxwrinit */
};

static	struct cb_ops cb_alta_ops = {
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
	&alta_info,	/* cb_stream */
	D_NEW|D_MP	/* cb_flag */
};

static	struct dev_ops alta_ops = {
	DEVO_REV,	/* devo_rev */
	0,		/* devo_refcnt */
	gld_getinfo,	/* devo_getinfo */
	nulldev,	/* devo_identify */
	nulldev,	/* devo_probe */
	altaattach,	/* devo_attach */
	altadetach,	/* devo_detach */
	nodev,		/* devo_reset */
	&cb_alta_ops,	/* devo_cb_ops */
	NULL,		/* devo_bus_ops */
	ddi_power	/* devo_power */
};

static struct modldrv modldrv = {
	&mod_driverops,	/* Type of module.  This one is a driver */
	ident,
	&alta_ops,	/* driver ops */
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

	DPRINTF(2, (CE_CONT, "alta: _init: called"));
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

	DPRINTF(2, (CE_CONT, "alta: _fini: called"));
	status = mod_remove(&modlinkage);
	return (status);
}

int
_info(struct modinfo *modinfop)
{
	return (mod_info(&modlinkage, modinfop));
}

/*
 * Probe for device. : not needed
 */

/*
 * Interface exists: make available by filling in network interface
 * record.  System will initialize the interface when it is ready
 * to accept packets.
 */
static int
altaattach(dev_info_t *dip, ddi_attach_cmd_t cmd)
{
	struct alta_dev		*dp;
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
	int			unit;
	struct chip_info	*p;
	char			valstr[32];
	char			propname[32];
	int			val;
	int			len;
	struct pci_phys_spec	*regs;

	unit =  ddi_get_instance(dip);

	DPRINTF(3, (CE_CONT, "alta%d: altaattach: called", unit));

	if (cmd == DDI_ATTACH) {
		DPRINTF(2, (CE_CONT, "alta%d: altaattach: called cmd:ATTACH",
			unit));
	
		macinfo = gld_mac_alloc(dip);
		if (macinfo == NULL) {
			return DDI_FAILURE;
		}

		/*
		 * Allocate soft data structure
		 */
		dp = (struct alta_dev *)
			kmem_zalloc(sizeof(*dp) + ALTAMCALLOC, KM_SLEEP);
		if (dp == NULL) {
			gld_mac_free(macinfo);
			return DDI_FAILURE;
		}
		dp->mc_count = 0;
		dp->mc_list = (struct ether_addr *) &dp[1];

		dp->dip = dip;
		dp->macinfo = macinfo;
		sprintf(dp->name, "%s%d", ddi_driver_name(dip), unit);

		macinfo->gldm_devinfo	   = dip;
		macinfo->gldm_private	   = (caddr_t)dp;

		macinfo->gldm_reset        = alta_reset;
		macinfo->gldm_start        = alta_start;
		macinfo->gldm_stop         = alta_stop;
		macinfo->gldm_set_mac_addr = alta_set_mac_address;
		macinfo->gldm_send         = alta_send;
		macinfo->gldm_set_promiscuous = alta_set_promiscuous;
		macinfo->gldm_get_stats    = alta_get_stats;
		macinfo->gldm_ioctl        = NULL; 
		macinfo->gldm_set_multicast= alta_set_multicast;
		macinfo->gldm_intr         = alta_interrupt;
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
				"%s: altaattach: ddi_get_iblock_cookie: failed",
				dp->name);
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
		 * Map in the device registers.
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
#ifdef DEBUG_LEVEL
		for (i = 0; i <len / sizeof(struct pci_phys_spec); i++) {
			cmn_err(CE_CONT,
				"!%s: regs[%d]: %08x.%08x.%08x.%08x.%08x",
				dp->name, i,
				regs[i].pci_phys_hi,
				regs[i].pci_phys_mid,
				regs[i].pci_phys_low,
				regs[i].pci_size_hi,
				regs[i].pci_size_low);
		}
#endif
		for (i = 0; i <len / sizeof(struct pci_phys_spec); i++) {
			if ((regs[i].pci_phys_hi & PCI_REG_ADDR_M) == 
			    PCI_ADDR_IO) {
				/* it's I/O space */
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
		ssid = pci_config_get16(conf_handle, PCI_CONF_SUBSYSID);
		dp->revid = pci_config_get8(conf_handle, PCI_CONF_REVID);
		comm = pci_config_get16(conf_handle, PCI_CONF_COMM);
		comm |= PCI_COMM_IO | PCI_COMM_ME;
		pci_config_put16(conf_handle, PCI_CONF_COMM, comm);

		pci_config_teardown(&conf_handle);

		/* initialize chip */
		for (i = 0, p = alta_chiptbl; i < CHIPTABLESIZE; i++, p++) {
			if ((p->venid==vid && p->devid==did) ||
			    (p->venid==svid && p->devid==ssid)) {
				/* found */
				dp->chip = p;
				goto chip_found;
			}
		}

		/* Not found */
		cmn_err(CE_WARN,
			"%s: alta_attach: wrong PCI venid/devid (0x%x, 0x%x)",
			dp->name, vid, did);
			goto err_free_regs;
chip_found:
		/*
		 * Reset the chip
		 */
		if (alta_reset_chip(dp) != 0) {
			goto err_free_regs;
		}

		dp->rxmode  = 0;
		dp->mii_fixedmode = FALSE;
		dp->speed100      = FALSE;	/* default is 10Mbps */
		dp->full_duplex   = FALSE;	/* default is half */
		dp->flow_control  =  dp->flow_control_req  = TRUE;

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
				dp->flow_control_req = TRUE;
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

		sprintf(propname, "%s-flow-control", dp->name);
		val = ddi_getprop(DDI_DEV_T_ANY, dp->dip, DDI_PROP_DONTPASS, propname, -1);
		if (val != -1) {
			if (val == 1) {
				dp->flow_control_req = TRUE;
			}
			else if (val == 0) {
				dp->flow_control_req = FALSE;
			}
			else {
				cmn_err(CE_WARN,
					"%s: property %s: illegal value (%d)",
					dp->name, propname, val);
			}
		}

		/*
		 * XXX - Get media mode infomation from config registers
		 */

		alta_init_mac_addr(dp);

		cmn_err(CE_CONT,
		"!%s: %s (rev:0x%02x) at 0x%x, %02x:%02x:%02x:%02x:%02x:%02x",
			dp->name, dp->chip->name, dp->revid,
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
		if (alta_alloc_memory(dp) != 0) {
			goto err_free_regs;
		}

		/* Init MII */
		if (alta_mii_init(dp) != 0) {
			goto err_free_ring;
		}

		/*
		 * Add interrupt to system.
		 */
		if (gld_register(dip, "alta", macinfo) != DDI_SUCCESS) {
			goto err_free_ring;
		}

		if (ddi_add_intr(dip, 0, NULL, NULL, gld_intr,
					(caddr_t)macinfo) != DDI_SUCCESS) {
			ddi_regs_map_free(&dp->regs_handle);
			cmn_err(CE_WARN, "%s: ddi_add_intr failed", dp->name);
			goto err_unregister;
		}

		DPRINTF(2, (CE_CONT, "altaattach: return: successed"));
		return DDI_SUCCESS;
err_free_intr:
		/* release allocated resource */
		(void) ddi_remove_intr(dip, 0, c);
err_unregister:
		gld_unregister(macinfo);
err_free_ring:
		alta_free_memory(dp);
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
			sizeof(struct alta_dev) + ALTAMCALLOC);
		gld_mac_free(macinfo);

		return DDI_FAILURE;
	}
	return DDI_FAILURE;
}

static int
altadetach(dev_info_t *dip, ddi_detach_cmd_t cmd)
{
	int		i;
	struct alta_dev *dp;
	gld_mac_info_t	*macinfo;

	if (cmd == DDI_DETACH) {
		macinfo = (gld_mac_info_t *)ddi_get_driver_private(dip);
		dp = (struct alta_dev *)macinfo->gldm_private;

		/* check if all rx buffers are freed */

		if (dp->buf_allocated != dp->buf_free) {
			/*
			 * resource is busy
			 */
			cmn_err(CE_NOTE,
			"%s: alta_detach: buffer is busy", dp->name);

			return DDI_FAILURE;
		}

		/*
		 * stop the device
		 */
		alta_mii_stop(dp);
#ifdef notdef
		alta_reset_chip(dp);
#endif
		/*
		 * unregister interrupt handler
		 */
		ddi_remove_intr(dip, 0, dp->iblock_cookie);

		(void)gld_unregister(macinfo);

		alta_free_memory(dp);

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
		 * Release memory resources
		 */
		kmem_free((caddr_t)dp, sizeof(struct alta_dev)+ALTAMCALLOC);
		gld_mac_free(macinfo);
		DPRINTF(2, (CE_CONT, "%s: altadetach: return: success",
				dp->name));

		return DDI_SUCCESS;
	}
	return DDI_FAILURE;
}

/* ============================================================== */
/*
 * Buffer management
 */
/* ============================================================== */
static ddi_dma_handle_t
alta_get_dma_handle(struct alta_dev *dp)
{
	ddi_dma_handle_t	dh;

	mutex_enter(&dp->dma_handle_lock);
	ASSERT(dp->dma_handle_free >= 0);
	if (dp->dma_handle_free == 0) {
		mutex_exit(&dp->dma_handle_lock);
		cmn_err(CE_PANIC,
			"%s: alta_get_dma_handle: no dma handle resource",
			dp->name);
		return NULL;
	}
	dh = dp->dma_handle[--dp->dma_handle_free];
	mutex_exit(&dp->dma_handle_lock);

	return dh;
}

static void
alta_free_dma_handle(struct alta_dev *dp, ddi_dma_handle_t dh)
{
	mutex_enter(&dp->dma_handle_lock);
	ASSERT(dp->dma_handle_free < TX_RING_SIZE*MAXTXFRAGS);
	dp->dma_handle[dp->dma_handle_free++] = dh;
	mutex_exit(&dp->dma_handle_lock);
	return;
}

static struct lbuf *
alta_get_lbuf(struct alta_dev *dp, int cansleep)
{
	struct lbuf		*lbp;
	ddi_dma_cookie_t	cookie;
	uint_t			count;
	int			err;

	mutex_enter(&dp->buflock);
	if ((lbp = dp->buf_free_list) != NULL) {
		ASSERT(dp->buf_free > 0);

		dp->buf_free_list = lbp->next;
		dp->buf_free--;
		mutex_exit(&dp->buflock);
		return lbp;	
	}
	if (dp->buf_allocated >= ALTA_LOCAL_BUF_MAX) {
		return NULL;
	}
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
				ETHERMAX + ETHERFCSL, &buf_attr,
				DDI_DMA_STREAMING,
				cansleep ? DDI_DMA_SLEEP : DDI_DMA_DONTWAIT,
				NULL,
				&lbp->buf, &lbp->buf_len,
				&lbp->acc_handle) != DDI_SUCCESS) {

		ddi_dma_free_handle(&lbp->dma_handle);
		kmem_free(lbp, sizeof(struct lbuf));
		return NULL;
	}
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
#endif
	lbp->devp = dp;
	lbp->frtn.free_func = (void (*)())&alta_reclaim_rxbuf;
	lbp->frtn.free_arg  = (caddr_t) lbp;

	mutex_enter(&dp->buflock);
	dp->buf_allocated++;
	mutex_exit(&dp->buflock);

	return lbp;
}

static void
alta_free_lbuf(struct lbuf *lbp)
{
	struct alta_dev	*dp;

	dp = lbp->devp;

	mutex_enter(&dp->buflock);
	lbp->next = dp->buf_free_list;
	dp->buf_free_list = lbp;
	dp->buf_free++;
	mutex_exit(&dp->buflock);
}

static int
alta_alloc_memory(struct alta_dev* dp)
{
	caddr_t			ring;
	size_t			ring_len;
	ddi_dma_cookie_t	cookie;
	uint_t			count;
	int			i;
	int			err;
	struct lbuf		*lbp, *head;

	/*
	 * Alloc RX/TX descriptors
	 */
	if ((err = ddi_dma_alloc_handle(dp->dip, &dma_attr_nosc,
			DDI_DMA_SLEEP,NULL,
			&dp->desc_dma_handle)) != DDI_SUCCESS) {
		cmn_err(CE_WARN,
			"%s: alta_alloc_memory: ddi_dma_alloc_handle failed: %d",
			dp->name, err);
		return ENOMEM;
	}

	if ((err = ddi_dma_mem_alloc(dp->desc_dma_handle,
#ifdef TXSOFTPAD
				ETHERMIN +
#endif
				RX_RING_SIZE * sizeof(struct alta_rfd) +
				TX_RING_SIZE * sizeof(struct alta_tfd),
				&dev_attr,
				DDI_DMA_CONSISTENT, DDI_DMA_SLEEP, NULL,
				&ring, &ring_len,
				&dp->desc_acc_handle)) != DDI_SUCCESS) {
		cmn_err(CE_WARN,
			"%s: alta_alloc_memory: ddi_dma_mem_alloc failed: %d",
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
		"%s: alta_alloc_memory: ddi_dma_addr_bind_handle failed: %d",
			dp->name, err);
		ddi_dma_mem_free(&dp->desc_acc_handle);
		ddi_dma_free_handle(&dp->desc_dma_handle);
		return ENOMEM;
	}
	ASSERT(count == 1);

	dp->rx_ring = (struct alta_rfd *)ring;
	dp->tx_ring = (struct alta_tfd *)
			(ring + RX_RING_SIZE * sizeof(struct alta_rfd));
	dp->rx_ring_dma = cookie.dmac_address;
	dp->tx_ring_dma = cookie.dmac_address
				+ RX_RING_SIZE * sizeof(struct alta_rfd);
#ifdef TXSOFTPAD
	dp->tx_pad_dma = dp->tx_ring_dma
				+ TX_RING_SIZE * sizeof(struct alta_tfd);
#endif
	/*
	 * Allocate dma handle for Tx
	 */
	for (i = 0; i< TX_RING_SIZE*MAXTXFRAGS; i++) {
		if (ddi_dma_alloc_handle(dp->dip, &dma_attr, DDI_DMA_SLEEP,
			NULL, &dp->dma_handle[i]) != DDI_SUCCESS) {

			cmn_err(CE_WARN,
			"%s: alta_alloc_memory: ddi_dma_alloc_handle failed.",
				dp->name);
			while (i-- > 0) {
				ddi_dma_free_handle(&dp->dma_handle[i]);
			}
			goto err;
		}
	}
	dp->dma_handle_free = TX_RING_SIZE*MAXTXFRAGS;

	/* Preallocate local buffer for performance */
	head = NULL;
	for (i = 0; i < ALTA_LOCAL_BUF_INIT; i++) {
		lbp = alta_get_lbuf(dp, TRUE);
		lbp->next = head;
		head = lbp;
	}
	while ((lbp = head) != NULL) {
		head = head->next;
		alta_free_lbuf(lbp);
	}

	return 0;

err:
	ddi_dma_unbind_handle(dp->desc_dma_handle);
	ddi_dma_mem_free(&dp->desc_acc_handle);
	ddi_dma_free_handle(&dp->desc_dma_handle);

	return ENOMEM;
}

static void
alta_free_memory(struct alta_dev* dp)
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
	for (i = 0; i < TX_RING_SIZE*MAXTXFRAGS; i++) {
		ddi_dma_free_handle(&dp->dma_handle[i]);
	}

	/* Free local buffer */
	while (lbp = dp->buf_free_list) {
		dp->buf_free_list = lbp->next;
#ifdef ALWAYS_MAPPED
		err = ddi_dma_unbind_handle(lbp->dma_handle);
		ASSERT(err == DDI_SUCCESS);
#endif
		ddi_dma_mem_free(&lbp->acc_handle);
		ddi_dma_free_handle(&lbp->dma_handle);
		kmem_free(lbp, sizeof(struct lbuf));
	}
}

static void
alta_init_rx_desc(struct alta_dev *dp)
{
	int		i;
	int		next;

	ASSERT(dp->rx_ring != NULL);

	dp->rx_head = 0;
	dp->rx_tail = 0;
	for (i = 0; i < RX_RING_SIZE; i++) {
		dp->rx_lbp[i]            = NULL;
		next = SLOT(i+1, RX_RING_SIZE);
		dp->rx_ring[i].RxDMANextPtr =
			dp->rx_ring_dma + sizeof(struct alta_rfd)*next;
	}

	for (i = 0; i < RX_RING_SIZE; i++) {
		struct lbuf	*lbp;

		if ((lbp = alta_get_lbuf(dp, TRUE)) == NULL) {
			break;
		}
		alta_append_rxbuf(dp, lbp, TRUE);
	}

}

static void
alta_clean_rx_ring(struct alta_dev* dp)
{
	int		i;
	struct lbuf	*lbp;

	ASSERT(mutex_owned(&dp->intrlock));
	ASSERT(!dp->start);

	for (i = 0; i < RX_RING_SIZE; i++) {
		if ((lbp = dp->rx_lbp[i]) != NULL) {
#ifndef ALWAYS_MAPPED
			/* release DMA resource */
			ddi_dma_unbind_handle(lbp->dma_handle);
#endif
			alta_free_lbuf(lbp);
			dp->rx_lbp[i] = NULL;
		}
	}
}

static void
alta_init_tx_desc(struct alta_dev* dp)
{
	int	i;
	int	j;

#ifdef notdef
	ASSERT(mutex_owned(&dp->xmitlock));
#endif
	dp->tx_head = 0;
	dp->tx_tail = 0;
	for (i = 0; i < TX_RING_SIZE; i++) {
		dp->tx_mp[i]   = NULL;
		dp->tx_lbp[i]  = NULL;
		for (j = 0; j < MAXTXFRAGS*2; j++) {
			dp->tx_dma_handle_used[i][j] = NULL;
		}
		dp->tx_ring[i].TxDMANextPtr   = 0;
		dp->tx_ring[i].TxFrameControl = 0;	/* XXX */
	}
}

static void
alta_clean_tx_ring(struct alta_dev *dp)
{
	int			i;
	int			j;
	ddi_dma_handle_t	dh;
	struct lbuf		*lbp;
	mblk_t			*mp;

	/*ASSERT(mutex_owned(&dp->xmitlock));*/

	dp->tx_head = 0;
	dp->tx_tail = 0;

	for (i = 0; i < TX_RING_SIZE; i++) {
		dp->tx_ring[i].TxDMANextPtr   = 0;
		dp->tx_ring[i].TxFrameControl = 0;	/* XXX */
		for (j = 0; j < MAXTXFRAGS*2; j++) {
			if ((dh = dp->tx_dma_handle_used[i][j]) != NULL) {
				/* release dma resource */
				ddi_dma_unbind_handle(dh);
				dp->tx_dma_handle_used[i][j] = NULL;
				alta_free_dma_handle(dp, dh);
			}
		}

		if ((mp = dp->tx_mp[i]) != NULL) {
			/* free direct mapped mblk */
			ASSERT(dp->tx_lbp[i] == NULL);
			freemsg(mp);
			dp->tx_mp[i] = NULL;

			dp->stats.errxmt++;
		}
		else if (lbp = dp->tx_lbp[i]) {
			/* free bounce buffer */
#ifndef ALWAYS_MAPPED
			ddi_dma_unbind_handle(lbp->dma_handle);
#endif
			alta_free_lbuf(lbp);
			dp->tx_lbp[i] = NULL;
			dp->stats.errxmt++;
		}
	}
}

/* ============================================================== */
/*
 * GLD interface
 */
/* ============================================================== */

static int
alta_reset(gld_mac_info_t *macinfo)
{
	struct alta_dev *dp;

	dp = (struct alta_dev *)macinfo->gldm_private;

	DPRINTF(3, (CE_CONT, "%s: alta_reset: called", dp->name));

	mutex_enter(&dp->intrlock);
	mutex_enter(&dp->xmitlock);

	alta_init_rx_desc(dp);
	alta_init_tx_desc(dp);

	dp->start       = FALSE;
	dp->tx_blocked  = FALSE;
	dp->tx_busy     = 0;
	dp->tx_reserved = 0;

	alta_init_chip(dp);

	mutex_exit(&dp->xmitlock);
	mutex_exit(&dp->intrlock);

	return GLD_SUCCESS;
}

static int
alta_start(gld_mac_info_t *macinfo)
{
	struct alta_dev *dp;

	dp = (struct alta_dev *)macinfo->gldm_private;

	mutex_enter(&dp->intrlock);
	mutex_enter(&dp->xmitlock);

	/* init driver state */
	dp->start        = TRUE;
	dp->tx_blocked   = FALSE;
	dp->tx_busy      = FALSE;
	dp->tx_reserved  = 0;
	dp->tx_list_loaded = FALSE;

	alta_start_chip(dp);

	mutex_exit(&dp->xmitlock);
	mutex_exit(&dp->intrlock);

	dp->timeout_id = timeout((void (*)(void *))alta_tx_timeout,
				(void *)dp, TX_TIMEOUT_INTERVAL);

	return GLD_SUCCESS;
}

static int
alta_stop(gld_mac_info_t *macinfo)
{
	timeout_id_t	old_id;
	struct alta_dev	*dp;
	int		i;

	dp = (struct alta_dev *)macinfo->gldm_private;

	/* stop tx timeout watcher */
	if (dp->timeout_id) {
		do {
			untimeout(old_id = dp->timeout_id);
		} while (dp->timeout_id != old_id);	
		dp->timeout_id = 0;
	}

	/* block rx */
	mutex_enter(&dp->intrlock);

	mutex_enter(&dp->xmitlock);
	dp->start = FALSE;
	mutex_exit(&dp->xmitlock);

	while (dp->intr_busy) {
		cv_wait(&dp->drain_cv, &dp->intrlock);
	}

	/* block tx */
	mutex_enter(&dp->xmitlock);
	while (dp->tx_busy > 0) {
		cv_wait(&dp->drain_cv, &dp->xmitlock);
	}

	/* inhibit interrupt */
	OUTW(dp, IntEnable, 0);

	/* no more statistics */
	OUTW(dp, MACCtrl1, MC1_StatisticsDisable);

	/* stop receiver and transceiver */
	OUTW(dp, MACCtrl1, MC1_RxDisable | MC1_TxDisable);

	alta_clean_tx_ring(dp);
	alta_clean_rx_ring(dp);
#if DEBUG_LEVEL >= 0
	if (dp->buf_allocated !=  dp->buf_free) {
		cmn_err(CE_CONT, "%s: alta_stop: buf alloced:%d, free: %d\n",
			dp->name,
			dp->buf_allocated, dp->buf_free);
	}
#endif
	mutex_exit(&dp->xmitlock);
	mutex_exit(&dp->intrlock);

	return GLD_SUCCESS;
}

static int
alta_set_multicast(gld_mac_info_t *macinfo, struct ether_addr *ep, int flag)
{
	struct alta_dev	*dp;
	size_t			len;
	int			i;
	int			cnt;

	dp = (struct alta_dev *)macinfo->gldm_private;

	cnt = dp->mc_count;

	if (flag == GLD_MULTI_ENABLE) {
		/* append new addess into mclist */
		if (cnt >= ALTAMAXMC) {
			return GLD_FAILURE;
		}
		bcopy(ep, &dp->mc_list[cnt], sizeof(struct ether_addr));
		dp->mc_count++;
	}
	else {
		for (i = 0; i < cnt; i++) {
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
	alta_set_rx_filter(dp);
	mutex_exit(&dp->intrlock);

	return GLD_SUCCESS;
}

static int
alta_set_promiscuous(gld_mac_info_t *macinfo, int flag)
{
	struct alta_dev *dp;

	dp = (struct alta_dev *)macinfo->gldm_private;

	mutex_enter(&dp->intrlock);

	if (flag == GLD_MAC_PROMISC_NONE) {
		dp->rxmode &= ~(RXMODE_PROMISC | RXMODE_ALLMULTI);
	}
	else if (flag == GLD_MAC_PROMISC_MULTI) {
		dp->rxmode |= RXMODE_ALLMULTI;
	}
	else {
		dp->rxmode |= RXMODE_PROMISC;
	}

	alta_set_rx_filter(dp);

	mutex_exit(&dp->intrlock);

	return GLD_SUCCESS;
}

static	int
alta_get_stats(gld_mac_info_t *macinfo, struct gld_stats *gs)
{
	struct alta_dev		*dp;
	struct alta_stats	*vs;

	dp = (struct alta_dev *)macinfo->gldm_private;

	mutex_enter(&dp->intrlock);
	alta_get_stats_chip(dp);
	mutex_exit(&dp->intrlock);

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
	gs->glds_speed     = dp->speed100 ? 100000000 : 10000000;
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

/*
 * Start transmission.
 * Return zero on success,
 */
#ifdef TXTIMEOUT_TEST
static int alta_send_cnt = 0;
#endif
static int
alta_send(gld_mac_info_t *macinfo, mblk_t *mp)
{
	mblk_t			*mp0;
	mblk_t			*mp_org;
	ddi_dma_cookie_t	dmacookie[MAXTXFRAGS*2];
	ddi_dma_handle_t	dh[MAXTXFRAGS*2];
	int			j;
	int			i;
	long			align;
	size_t			len;
	unsigned		slot;
	unsigned		prev;
	struct lbuf		*lbp = NULL;
	int			frags;
	int			docopy;
	int			err;
#ifdef DEBUG_LEVEL
	int			first_tx_tail;
	int			first_slot;
#endif
	struct alta_dev		*dp;
	struct alta_tfd		*tdp;
	uint32_t		tfd_dma;

	dp = (struct alta_dev *)macinfo->gldm_private;
	mp_org = NULL;

	DPRINTF(2, (CE_CONT, "alta_send: called"));

	/* check buffer length and alignment */
	align = 0;
	len   = 0;
	frags = 1;
	for (mp0 = mp; mp0->b_cont; mp0 = mp0->b_cont) {
		len   +=  mp0->b_wptr - mp0->b_rptr;
		align |= (long)mp0->b_rptr | (long)mp0->b_wptr;
		frags++;
	}
	len   += mp0->b_wptr - mp0->b_rptr;
	align |= (long)mp0->b_rptr;

	if (len > ETHERMAX) {
		cmn_err(CE_CONT, "%s: alta_send: msg too big: %d",
			dp->name, len);
		/* Do not free mp here, GLD will free it */
		return GLD_NOTSUPPORTED;
	}

	docopy = FALSE;

	if (frags > MAXTXFRAGS) {
		docopy = TRUE;
		frags = 1;
	}

	/* reserve required resources */
	mutex_enter(&dp->xmitlock);
	if (!dp->start) {
		/* the device is not working */
#ifdef notdef
		/* Do not change tx_blocked state */
		dp->tx_blocked = TRUE;
#endif
		mutex_exit(&dp->xmitlock);
		return GLD_FAILURE;
	}

	/*
	 * Check tfd resource.
	 * ST201 use just one tfd on a transmittion.
	 */
	if (TX_RING_SIZE <= SUB(dp->tx_tail, dp->tx_head) - dp->tx_reserved) {

		/* No resources, try later */

		/* mark to restart on tx-dma-done */
		dp->tx_blocked = TRUE;
		mutex_exit(&dp->xmitlock);
		return GLD_NORESOURCES;
	}

	/* not need to restart on tx-dma-done */
	dp->tx_blocked = FALSE;

	dp->tx_reserved++;

	dp->tx_busy++;
	mutex_exit(&dp->xmitlock);
#define OLD_TXCOPY
#ifdef OLD_TXCOPY
	if (docopy) {
		caddr_t			bp;
#ifndef ALWAYS_MAPPED
		uint_t			count;
#endif
tx_copy:
		/* Must use aligned buffer. */
		if ((lbp = alta_get_lbuf(dp, FALSE)) == NULL) {
			/* no resource, try later */
			err = GLD_NORESOURCES;
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
		if (len < ETHERMIN) {
			bzero(bp, ETHERMIN - len);
			len = ETHERMIN;
		}
#endif
#ifdef ALWAYS_MAPPED
		ddi_dma_sync(lbp->dma_handle, (off_t)0,
				len, DDI_DMA_SYNC_FORDEV);
		dmacookie[0].dmac_address = lbp->dma_addr;
		dmacookie[0].dmac_size    = len;
#else
		if ((err = ddi_dma_addr_bind_handle(
				lbp->dma_handle, NULL,
				lbp->buf, len,
				DDI_DMA_WRITE|DDI_DMA_STREAMING,
				DDI_DMA_DONTWAIT, NULL,
				&dmacookie[0], &count)) != DDI_DMA_MAPPED) {
			ASSERT(err != DDI_DMA_INUSE);
			alta_free_lbuf(lbp);
			err = GLD_NORESOURCES;
			goto x;
		}
		ASSERT(count == 1);
#endif /* ALWAYS_MAPPED */
		dh[0] = NULL;	/* Do not free dmahandle on TX completion */
		i = 1;

		/* prepare to destroy mp */
		mp_org = mp;
		mp = NULL;
	}
	else
#else /* OLD_TXCOPY */
	if (docopy) {
		mp0 = msgpullup(mp, -1);
		if (mp0 == NULL) {
			err = GLD_NORESOURCES;
			goto x;
		}
		mp_org = mp;	/* destroyed on success return here */
		mp     = mp0;	/* destroyed on success transmittion */
	}
#endif /* OLD_TXCOPY */
	{
		/*
		 * prepare for direct transmit
		 */
		i = 0;
		for (mp0 = mp; mp0; mp0 = mp0->b_cont) {
			ddi_dma_handle_t	dma_handle;
			uint_t			count;
			size_t			len;

			len = mp0->b_wptr - mp0->b_rptr;
			dma_handle = alta_get_dma_handle(dp);
			ASSERT(dma_handle != NULL);

			if ((err = ddi_dma_addr_bind_handle(
				dma_handle, NULL,
				mp0->b_rptr, len,
				DDI_DMA_WRITE|DDI_DMA_STREAMING,
				DDI_DMA_DONTWAIT, NULL,
				&dmacookie[i], &count)) != DDI_DMA_MAPPED) {

				/* failed to bind dma resource */
				alta_free_dma_handle(dp, dma_handle);
				while (i--) {
					if (dh[i] != NULL) {
						ddi_dma_unbind_handle(dh[i]);
						alta_free_dma_handle(dp, dh[i]);
					}
				}
				err = GLD_NORESOURCES;
				goto x;
			}
			ASSERT(count == 1 || count == 2);
			dh[i] = dma_handle;
			i++;

			while (--count > 0) {
				ddi_dma_nextcookie(dma_handle, &dmacookie[i]);
				dh[i] = NULL;
				i++;
			}
		}
#if DEBUG_LEVEL > 3
		cmn_err(CE_CONT,
			"%s: alta_send: mp:0x%p, lbp:0x%p, dma frags:%d",
			dp->name, mp, lbp, i);
		for (j = 0; j < i; j++) {
			cmn_err(CE_CONT,
				" frag:%dth: dh:0x%x dma_addr:0x%x len:0x%x",
				j, dh[j],
				dmacookie[j].dmac_address,
				dmacookie[j].dmac_size);
		}
#endif
#ifdef TXSOFTPAD
		if (len < ETHERMIN) {
			/* add pad fragment */
			dh[i] = NULL;
			dmacookie[i].dmac_address = dp->tx_pad_dma;
			dmacookie[i].dmac_size    = len - ETHERMIN;
			i++;
		}
#endif
	}
	err = GLD_SUCCESS;
x:
	mutex_enter(&dp->xmitlock);
	dp->tx_busy--;
	dp->tx_reserved--;

	if (!dp->start) {
		/* device status has changed while preparing tx */
		if (dp->tx_busy == 0) {
			/* someone may wait for us */
			cv_broadcast(&dp->drain_cv);
		}
		err = GLD_FAILURE;
	}

	if (err != GLD_SUCCESS) {
		/* something wrong, no resources? */
		if (err == GLD_NORESOURCES) {
			dp->tx_blocked = TRUE;
		}
		mutex_exit(&dp->xmitlock);
		if (mp_org) {
			/* destory copied mblk */
			freemsg(mp);
		}
		return err;
	}

	/*
	 * write tx fragment descriptor(s)
	 */
	slot = SLOT(dp->tx_tail, TX_RING_SIZE);
	tdp  = &dp->tx_ring[slot];
	dp->tx_mp[slot]  = mp;
	dp->tx_lbp[slot] = lbp;

	tdp->TxDMANextPtr   = 0;
	tdp->TxFrameControl = TFC_TxDMAIndicate |
#if DEBUG_LEVEL > 4
			TFC_TxIndicate |
#endif
			(TFC_FrameId & (slot << TFC_FrameIdShift)) |
			TFC_WordAlignDisable;
	/* Copy start address and length og each fragment */
	for (j = 0; j < i; j++) {
		ASSERT(dmacookie[j].dmac_size <= TFD_TxDMAFragLen);
		dp->tx_dma_handle_used[slot][j] = dh[j];
		tdp->TxDMAFrag[j].Len  = dmacookie[j].dmac_size;
		tdp->TxDMAFrag[j].Addr = dmacookie[j].dmac_address;
	}
	/* mark last fragment */
	tdp->TxDMAFrag[i-1].Len |= TFD_TxDMAFragLast;

	DPRINTF(2, (CE_CONT, "%s: tx packet seqnum: %d slot %d",
		dp->name, dp->tx_tail, slot));

	tfd_dma = dp->tx_ring_dma + sizeof(struct alta_tfd)*slot;
	ASSERT((tfd_dma & 7 ) == 0);
#ifdef TXTIMEOUT_TEST
	alta_send_cnt++;
	if (alta_send_cnt > 100) {
		OUTW(dp, MACCtrl1, MC1_TxDisable);
	} else
#endif
	if (dp->tx_list_loaded)  {
		/* Link this to the previous slot and kick Tx engine */
		prev = SLOT(dp->tx_tail-1, TX_RING_SIZE);
		dp->tx_ring[prev].TxDMANextPtr = tfd_dma;
		OUTW(dp, MACCtrl1, MC1_TxEnable);
	}
	else {
		/* Treat this as head of new tx list, tell to nic */
		OUTL(dp, TxDMAListPtr, tfd_dma);
		dp->tx_list_loaded = TRUE;
	}
	dp->tx_start_time = ddi_get_lbolt();
	dp->tx_tail++;

	mutex_exit(&dp->xmitlock);

	if (mp_org != NULL) {
		/* destroy original mblk */
		freemsg(mp_org);
	}
	ASSERT(err == GLD_SUCCESS);
	return GLD_SUCCESS;
}

static int
alta_set_mac_address(gld_mac_info_t *macinfo, unsigned char *mac) /* done */
{
	struct alta_dev	*dp;

	dp = (struct alta_dev *)macinfo->gldm_private;

	bcopy(mac, dp->cur_addr.ether_addr_octet, ETHERADDRL);

	mutex_enter(&dp->intrlock);
	alta_set_rx_filter(dp);
	mutex_exit(&dp->intrlock);

	return GLD_SUCCESS;
}

/*==========================================================*/

static void
alta_tx_timeout(struct alta_dev *dp)
{
	clock_t	now;

	now = ddi_get_lbolt();

	mutex_enter(&dp->xmitlock); 
	if (!(dp->start && dp->tx_head != dp->tx_tail &&
	     (now - dp->tx_start_time >= TX_TIMEOUT))) {
		mutex_exit(&dp->xmitlock); 
		goto schedule_next;
	}
	mutex_exit(&dp->xmitlock); 

	cmn_err(CE_WARN, "%s: tx timeout", dp->name);

	/* block Rx */
	mutex_enter(&dp->intrlock);

	/* block Tx */
	mutex_enter(&dp->xmitlock); 
	dp->start = FALSE;
	while (dp->tx_busy > 0) {
		cv_wait(&dp->drain_cv, &dp->xmitlock);
	}

	/* Reset the chip. */
	alta_reset_chip(dp);

	/* clear all descriptors */
	alta_clean_tx_ring(dp);
	alta_clean_rx_ring(dp);

	alta_init_rx_desc(dp);

	/* Reinitialize the hardware. */
	alta_init_chip(dp);

	/* Set mac address and rx mode */
	alta_set_rx_filter(dp);

	/* Restart the nic */
	dp->start         = TRUE;
	dp->tx_blocked    = FALSE;
	dp->tx_busy       = FALSE;
	dp->tx_reserved   = 0;
	dp->tx_list_loaded = FALSE;

	alta_start_chip(dp);
#ifdef TXTIMEOUT_TEST
	alta_send_cnt = 0;
#endif
	mutex_exit(&dp->xmitlock); 
	mutex_exit(&dp->intrlock);

	gld_sched(dp->macinfo);

schedule_next:
	dp->timeout_id =
		timeout((void (*)(void *))alta_tx_timeout,
			(void *)dp, TX_TIMEOUT_INTERVAL);
}

/*==================================================================*/
/*
 * Interrupt handler
 */
/*==================================================================*/
static int
alta_append_rxbuf(struct alta_dev *dp, struct lbuf *lbp, int cansleep)
{
	int		slot;
	int		prev;
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
	prev = SLOT(dp->rx_tail-1, RX_RING_SIZE);

	ASSERT(dp->rx_lbp[slot] == NULL);

#ifdef ALWAYS_MAPPED
	dp->rx_ring[slot].RxDMAFrag[0].Addr = lbp->dma_addr;
#else
	if ((err = ddi_dma_addr_bind_handle(lbp->dma_handle,
				NULL,
				lbp->buf, lbp->buf_len,
				DDI_DMA_READ | DDI_DMA_STREAMING,
				cansleep ? DDI_DMA_SLEEP : DDI_DMA_DONTWAIT,
				NULL,
				&cookie, &count)) != DDI_SUCCESS) {
		/*
		 * No DMA resource available
		 */
		ASSERT(err != DDI_DMA_INUSE);
		alta_free_lbuf(lbp);
		return -1;
	}

	ASSERT(count == 1);
	dp->rx_ring[slot].RxDMAFrag[0].Addr = cookie.dmac_address;
#endif /* ALWAYS_MAPPED */
	dp->rx_lbp[slot] = lbp;
	dp->rx_ring[slot].RxDMAFrag[0].Len =
		(lbp->buf_len & RFD_RxDMAFragLen) | RFD_RxDMALastFrag;
	dp->rx_ring[slot].RxFrameStatus= 0;

#ifdef notdef
	/* tail of the rx list */
	dp->rx_ring[slot].RxDMANextPtr = 0;

	/* XXX - Link it to previous slot */
	dp->rx_ring[prev].RxDMANextPtr =
			dp->rx_ring_dma + sizeof(struct alta_rfd)*slot;
#endif
	dp->rx_tail++;

	return 0;
}

static void
alta_reclaim_rxbuf(struct lbuf *lbp)
{
	struct alta_dev	*dp;

	ASSERT(lbp != NULL);

	dp = lbp->devp;

	mutex_enter(&dp->intrlock);
	if (!dp->intr_busy && dp->start) {
		if (SUB(dp->rx_tail, dp->rx_head) < RX_RING_SIZE) {
			(void)alta_append_rxbuf(dp, lbp, FALSE);

			/* XXX - kick Rx engine */

			mutex_exit(&dp->intrlock);
			return;
		}
	}
	mutex_exit(&dp->intrlock);

	alta_free_lbuf(lbp);

	return;
}

static void
alta_receive(struct alta_dev *dp)
{
	int		i;
	int		len;
	unsigned	slot;
	uint32_t	rfs;
	struct lbuf	*lbp;
	mblk_t		*mp;
	seqnum_t	limit;
	int		err;

	slot = 	SLOT(dp->rx_head, RX_RING_SIZE);
	DPRINTF(2, (CE_CONT,
		"%s: alta_receive: slot:%d addr:0x%x len:0x%x rfs 0x%b",
		dp->name, slot,
		dp->rx_ring[slot].RxDMAFrag[0].Addr,
		dp->rx_ring[slot].RxDMAFrag[0].Len,
		dp->rx_ring[slot].RxFrameStatus, RFS_BITS));

	ASSERT(mutex_owned(&dp->intrlock));

	limit = dp->rx_tail;
	while (dp->rx_head != limit) {

		slot = SLOT(dp->rx_head, RX_RING_SIZE);
		rfs = dp->rx_ring[slot].RxFrameStatus;

		if ((rfs & RFS_RxDMAComplete) == 0) {
			/* the end of received packet */
			break;
		}

		DPRINTF(2, (CE_CONT, "%s: alta_receive: slot:%d rx status %b",
				dp->name, slot, rfs, RFS_BITS));

		/* remove the head of rx buffer list */
		lbp = dp->rx_lbp[slot];
		dp->rx_lbp[slot] = NULL;
		dp->rx_head++;

		if ((rfs & RFS_ERRORS) != 0) {
			/* error packet */
			dp->stats.errrcv++;
			if ((rfs & (RFS_RxAlignmentError
					| RFS_RxFrameError)) != 0) {
				dp->stats.frame++;
			}
			if ((rfs & RFS_RxFIFOOverrun) != 0) {
				dp->stats.overflow++;
			}
			if ((rfs & RFS_RxRuntFrame) != 0) {
				dp->stats.runt++;
			}
			if ((rfs & RFS_RxFCSError) != 0) {
				dp->stats.crc++;
			}
			if ((rfs & RFS_RxDMAOverflow
					| RFS_RxOversizedFrame) != 0) {
				dp->stats.frame_too_long++;
			}
			alta_free_lbuf(lbp);
			continue;
		}

		len = rfs & RFS_RxDMAFrameLen;
		ASSERT(lbp != NULL);

		/* allocate a msg block structure w/o actual data block */
		if ((mp = esballoc(lbp->buf, len, BPRI_LO,
					&lbp->frtn)) == NULL) {
			dp->stats.norcvbuf++;
			alta_free_lbuf(lbp);
			continue;
		}

		/*
		 * Direct reception
		 */
		mp->b_wptr = mp->b_rptr + len;
#ifdef ALWAYS_MAPPED
		ddi_dma_sync(lbp->dma_handle, 0, len,
					DDI_DMA_SYNC_FORKERNEL);
#else
		/* release dma resources */
		ddi_dma_unbind_handle(lbp->dma_handle);
#endif
		mutex_exit(&dp->intrlock);
		gld_recv(dp->macinfo, mp);
		mutex_enter(&dp->intrlock);
	}

	/*
	 * Append newly allocated empty rx buffer into rx buffer list.
	 */
	i = RX_RING_SIZE - SUB(dp->rx_tail, dp->rx_head);
	while (i--) {
		ASSERT(dp->rx_lbp[SLOT(dp->rx_tail, RX_RING_SIZE)] == NULL);

		if ((lbp = alta_get_lbuf(dp, FALSE)) == NULL) {
			/*
			 * No memory available.
			 */
			cmn_err(CE_WARN, "%s: cannot allocate rx buffer",
					dp->name);
			dp->stats.norcvbuf++;
			break;
		}
		alta_append_rxbuf(dp, lbp, FALSE);
	}

	return;
}

static void
alta_txdma_done(struct alta_dev *dp)
{
	uint32_t		tfc;
	unsigned		slot;
	ddi_dma_handle_t	dh;
	int			i;
	struct lbuf		*lbp;

	ASSERT(mutex_owned(&dp->xmitlock));
	ASSERT(SUB(dp->tx_tail, dp->tx_head) >= 0);

	for (;dp->tx_head != dp->tx_tail; dp->tx_head++) {

		slot = SLOT(dp->tx_head, TX_RING_SIZE);

		tfc  = dp->tx_ring[slot].TxFrameControl;
#if DEBUG_LEVEL >  4
		DPRINTF(4, (CE_CONT,
			"%s: alta_txdma_done: TxDMAListPtr:%p head:%d, tail:%d",
			dp->name, INL(dp, TxDMAListPtr),
			dp->tx_head, dp->tx_tail));

		for (i=0; i<TX_RING_SIZE; i++) {
			DPRINTF(4, (CE_CONT, "  slot:%d TxFrameControl: %b",
				i, dp->tx_ring[i].TxFrameControl, TFC_BITS));
		}
#endif
		if ((tfc & TFC_TxDMAComplete) == 0) {
			/* done */
			break;
		}

		/*
		 * Free dma mapping on each fragment
		 */
		i = 0;
		do {
			if ((dh = dp->tx_dma_handle_used[slot][i]) != NULL) {
				/* free dma resource */
				ddi_dma_unbind_handle(dh);
				alta_free_dma_handle(dp, dh);
				dp->tx_dma_handle_used[slot][i] = NULL;
			}
		} while((dp->tx_ring[slot].TxDMAFrag[i++].Len & TFD_TxDMAFragLast) == 0);

		if (dp->tx_mp[slot]) {
			/* Free the original mblk. */
			ASSERT(dp->tx_lbp[slot] == NULL);
			freemsg(dp->tx_mp[slot]);
			dp->tx_mp[slot] = NULL;
		}
		else if (lbp = dp->tx_lbp[slot]) {
			/* Free tx bounce buffer. */
#ifndef ALWAYS_MAPPED
			ddi_dma_unbind_handle(lbp->dma_handle);
#endif
			alta_free_lbuf(lbp);
			dp->tx_lbp[slot] = NULL;
		}
	}
}

static int
alta_transmit_done(struct alta_dev  *dp)
{
	int	error = 0;
	int	restart_xmit;
	u_char	tx_status;
	int	i;

	ASSERT(mutex_owned(&dp->intrlock));

	/* Pop all status from  the Tx status stack. */
	while (((tx_status = INW(dp, TxStatus)) & TS_TxComplete) != 0) {

		/* Discard one */
		OUTW(dp, TxStatus, 0);

		if ((tx_status & TS_TxReleaseError) != 0) {
			cmn_err(CE_WARN,
			    "%s: tx release error: tx_status: %b",
			    dp->name, tx_status, TS_BITS);
		}

		if ((tx_status & TS_TxStatusOverflow) != 0) {
			cmn_err(CE_WARN,
			    "%s: tx status overflow: tx_status: %b",
			    dp->name, tx_status, TS_BITS);
		}

		/* update statistics */
		if ((tx_status & TS_TxUnderrun) != 0) {
			/* fifo underflow. TxReset and TxEnable are required */
			cmn_err(CE_WARN,
			    "%s: tx underrun error: tx_status: %b",
			    dp->name, tx_status, TS_BITS);
			dp->stats.underflow++;
			dp->stats.errxmt++;
		}

		if ((tx_status & TS_MaxCollisions) != 0) {
			/* exceed maximum collisions */
			dp->stats.excoll++;
			dp->stats.collisions += 16;
			dp->stats.errxmt++;
		}

		/* collect status bits */
		error |= (tx_status &
		    (TS_TxReleaseError | TS_TxUnderrun | TS_MaxCollisions));
	}

	mutex_enter(&dp->xmitlock);

	if (error != 0) {
		if ((error & (TS_TxReleaseError | TS_TxUnderrun)) != 0) {
			/* wait for tx fifo free */
			dp->start = FALSE;
			while (dp->tx_busy) {
				cv_wait(&dp->drain_cv, &dp->xmitlock);
			}

			OUTL(dp, AsicCtrl, AC_TxReset);

			drv_usecwait(10);
			i = 0;
			while ((INL(dp, AsicCtrl) & AC_ResetBusy) != 0) {
				if (i++>100) {
					/* TxReset timeout */
					break;
				}
				drv_usecwait(10);
			}
		}

		if ((error & TS_MaxCollisions) != 0) {
			OUTW(dp, MACCtrl1, MC1_StatisticsEnable);
		}

		OUTW(dp, MACCtrl1, MC1_TxEnable); 
		dp->start = TRUE;
	}

	/*
	 * kick someone who waits for enough space in TX fifo
	 */
	restart_xmit = dp->tx_blocked;
	mutex_exit(&dp->xmitlock);

	return restart_xmit;
}

static u_int
alta_interrupt(gld_mac_info_t *macinfo)
{
	struct alta_dev	*dp;
	uint16_t	int_status;
	int		tx_sched = 0;

	dp = (struct alta_dev *)macinfo->gldm_private;

	mutex_enter(&dp->intrlock);

	/*
	 * Read interrupt status
	 * Caution: Do not use IntStatusAck. It's funny.
	 */
	int_status = INW(dp, IntStatus);
	if ((int_status & OUR_INTR_BITS) == 0) {
		/* Not for us */
		mutex_exit(&dp->intrlock);
		return DDI_INTR_UNCLAIMED;
	}
	dp->stats.intr++;

	/*
	 * Acknowledge to the interrupt.
	 * Mask interrupt signal first, because PCI bus recognize
	 * interrupts by edge-triggered method.
	 */
	OUTW(dp, IntEnable, 0);
	OUTW(dp, IntStatus, int_status);

	dp->intr_busy = TRUE;

	DPRINTF(2, (CE_CONT, "%s: Interrupt, int_status: %b",
			   dp->name, int_status, INT_BITS));
	if (!dp->start) {
		/*
		 * the device is not active.
		 * side effect: left interrupt masked.
		 */
		goto x;
	}

	if ((int_status & INT_UpdateStats) != 0) {
		/*
		 * Statistics counter overflow
		 */
		alta_get_stats_chip(dp);
	}

	if ((int_status & (INT_RxDMAComplete | INT_MACControlFrame)) != 0) {
		/*
		 * packet was received, or receive error happened
		 */
		alta_receive(dp);
	}

	if ((int_status & INT_TxComplete) != 0) {
		/*
		 * Pull up TxStatus
		 */
		tx_sched = alta_transmit_done(dp);
	}

	if ((int_status & INT_TxDMAComplete) != 0) {
		/*
		 * Packets was transfered into TxFIFO or error happened
		 */
		mutex_enter(&dp->xmitlock);
		alta_txdma_done(dp);

		if (dp->tx_blocked && SUB(dp->tx_tail, dp->tx_head) < 4) {
			tx_sched = 1;
		}
		mutex_exit(&dp->xmitlock);
	}

	if ((int_status &
		(INT_RxEarly | INT_IntRequest | INT_HostError)) != 0) {

		cmn_err(CE_WARN, "%s: unexpected interrupt: %b",
			dp->name, int_status, INT_BITS);

	}
	/*
	 * Recover Interrput Enable register
	 */
	DPRINTF(4, (CE_CONT, "%s: alta_inter done: int_status: %b",
			   dp->name, INW(dp, IntStatus), INT_BITS));
	OUTW(dp, IntEnable, OUR_INTR_BITS);
x:
	if (!dp->start) {
		cv_broadcast(&dp->drain_cv);
	}
	dp->intr_busy = FALSE;

	mutex_exit(&dp->intrlock);

	if (tx_sched) {
		gld_sched(macinfo);
	}

	return DDI_INTR_CLAIMED;
}

/* ======================================================== */
/*
 * HW manupilation routines
 */
/* ======================================================== */
static int
alta_reset_chip(struct alta_dev *dp)
{
	int	i;

	/* Reset the chip. */
	OUTL(dp, AsicCtrl,
		AC_GlobalReset | AC_DMA | AC_FIFO | AC_Network
		| AC_Host | AC_AutoInit | AC_RstOut);
	i = 0;
	while ((INL(dp, AsicCtrl) & AC_ResetBusy) != 0) {
		drv_usecwait(10);
		if (i++ > 200) {
			cmn_err(CE_WARN, "%s: alta_reset_chip: timeout",
				dp->name);
			return -1;
		}
	}
	DPRINTF(1, (CE_CONT, "!%s: alta_reset_chip: took %d uS",
				dp->name, i*10));

	return 0;
}

static void
alta_init_chip(struct alta_dev *dp)
{
	int     i;

	DPRINTF(2, (CE_CONT, "?%s: alta_init_chip: called", dp->name));

	ASSERT(mutex_owned(&dp->intrlock));

	/* AsicCtrl : assume the chip stopped */

	DPRINTF(3, (CE_CONT, "!alta_init_chip called, mc0: %b",
		INW(dp, MACCtrl0), MC0_BITS));
	DPRINTF(3, (CE_CONT, "!mc1: %b",
		INW(dp, MACCtrl1), MC1_BITS));
	DPRINTF(3, (CE_CONT, "!ac: %b",
		INL(dp, AsicCtrl), AC_BITS));
	
	/* MACCtrl1: Ensure all functions are disabled */
	OUTW(dp, MACCtrl1,
		MC1_StatisticsDisable | MC1_TxDisable | MC1_RxDisable);

	/* MACCtrl0: Ensure normal operational mode*/
	OUTW(dp, MACCtrl0, MC0_IFSSelect802_3);

	/* TxDMA */
	OUTL(dp, TxDMAListPtr, 0);
	OUTB(dp, TxDMAPollPeriod, TxDMAPollPeriodMax);

	/* RxDMA */
	OUTL(dp, RxDMAListPtr, 0);
	OUTB(dp, RxDMAPollPeriod, RxDMAPollPeriodMax);
#ifdef TXUNDERRUNTEST
	/* TxStartThread : 256 byte */
	OUTW(dp, TxStartThresh, 1);
	OUTW(dp, TxDMABurstThresh, 2047/TxDMABurstThreshUnit);
#else
	/* TxStartThread : 256 byte */
	OUTW(dp, TxStartThresh, 256/TxStartThreshUnit);
#endif
	/* TxDMAUrgentThread : 128 byte */
	OUTB(dp, TxDMAUrgentThresh, 128/TxDMAUrgentThreshUnit);

	/* TxReleaseThread : 512 byte */
	OUTB(dp, TxReleaseThresh, 512/TxReleaseThreshUnit);

	/* RxEarlyThreth: disable Eerly Rx */
	OUTW(dp, RxEarlyThresh, RxEarlyThreshDisable);

	/* Set InterruptMask */
	OUTW(dp, IntEnable, OUR_INTR_BITS);

#ifdef notdef
	/*
	 * Set RxFilter
	 * XXX -- called later.
	 */
	alta_set_rx_filter(dp);
#endif
	DPRINTF(1, (CE_CONT, "!alta_init_chip: mc0: %b",
		INW(dp, MACCtrl0), MC0_BITS));
	DPRINTF(1, (CE_CONT, "!mc1: %b",
		INW(dp, MACCtrl1), MC1_BITS));
	DPRINTF(1, (CE_CONT, "!ac: %b",
		INL(dp, AsicCtrl), AC_BITS));
}

static void
alta_start_chip(struct alta_dev *dp)
{
	ASSERT(mutex_owned(&dp->intrlock));
	/*ASSERT(mutex_owned(&dp->xmitlock));*/

	/* Enable statistics */
	alta_get_stats_chip(dp);
	bzero(&dp->stats, sizeof(dp->stats));
	OUTW(dp, MACCtrl1, MC1_StatisticsEnable);

	/* Set media */
	alta_set_media(dp);

	/* Enable transmitter and receiver */
	OUTW(dp, MACCtrl1, MC1_TxEnable | MC1_RxEnable);

	ASSERT((dp->rx_ring_dma & 7) == 0);
	OUTL(dp, RxDMAListPtr, dp->rx_ring_dma);

	DPRINTF(1, (CE_CONT, "!alta_start_chip: mc0: %b",
		INW(dp, MACCtrl0), MC0_BITS));
	DPRINTF(1, (CE_CONT, "!alta_start_chip: mc1: %b",
		INW(dp, MACCtrl1), MC1_BITS));
	DPRINTF(1, (CE_CONT, "!alta_start_chip: dmactrl: %b",
		INW(dp, DMACtrl), DC_BITS));
}


static uint16_t
alta_read_eeprom(struct alta_dev *dp, uint_t offset)
{
	int		i;

	OUTW(dp, EepromCtrl, EEC_OpcodeRd | (offset & EEC_Address));
	drv_usecwait(100);

	i = 0;
	while (++i<100) {
		if ((INW(dp, EepromCtrl) & EEC_Busy) == 0) {
			/* done */
			DPRINTF(4, (CE_CONT, "%s eeprom_read took %d uS",
				dp->name, i*10));
			return INW(dp, EepromData);
		}
		drv_usecwait(10);
	}

	cmn_err(CE_CONT, "%s eeprom_read timeout", dp->name);

	return 0xffff;
}

#ifdef DEBUG_LEVEL
static void
alta_eeprom_dump(struct alta_dev *dp)
{
	int		i;
	uint16_t	prom[0x14];

	for (i = 0; i < 0x14; i++) {
		prom[i] = alta_read_eeprom(dp, i);
	}

	cmn_err(CE_CONT, "!%s: eeprom dump:", dp->name);
	for (i = 0; i < 0x14; i += 4) {
		cmn_err(CE_CONT, "!0x%02x: 0x%04x 0x%04x 0x%04x 0x%04x", 
			i, prom[i], prom[i + 1], prom[i + 2], prom[i + 3]);
	}
}
#endif /* DEBUG_LEVEL */

static int
alta_init_mac_addr(struct alta_dev *dp)	
{
	int		i;
	uint16_t	val;

	for (i = 0; i < ETHERADDRL; i += 2) {
		val =  alta_read_eeprom(dp, 0x10 + i/2);

		dp->dev_addr.ether_addr_octet[i    ] = val;
		dp->dev_addr.ether_addr_octet[i + 1] = val >> 8;

		OUTW(dp, StationAddress + i, val);
	}
#if DEBUG_LEVEL > 4
	alta_eeprom_dump(dp);
#endif
	return 0;
}

static void
alta_set_rx_filter(struct alta_dev *dp)	
{
	uint8_t		mode;
	uint8_t		*newmac;
	int		i;
	int		chip_state;
	uint16_t	val;

	ASSERT(mutex_owned(&dp->intrlock));

	if ((dp->rxmode & RXMODE_PROMISC) != 0) {
		/* promiscous */
		mode = RM_ReceiveAllFrames;
	}
	else if (dp->mc_count > 0 || (dp->rxmode & RXMODE_ALLMULTI) != 0) {
		/* Normal mode with multicast */
		mode = RM_ReceiveUnicast
		     | RM_ReceiveBroadcast
		     | RM_ReceiveMulticast;
	}
	else {
		/* Normal mode */
		mode = RM_ReceiveUnicast | RM_ReceiveBroadcast;
	}


	/* set rx mode */
	DPRINTF(1, (CE_CONT, "!%s: set_rx_filter: setting mode: %b",
		dp->name, mode, RM_BITS));

	/* stop rx temporary */
	if (dp->start) {
		OUTW(dp, MACCtrl1, MC1_RxDisable);
	}

	OUTB(dp, ReceiveMode, mode);

	/* clear multicast hash table */
	for (i = 0; i < 4; i++) {
		OUTW(dp, HashTable + i*sizeof(uint16_t), 0);
	}

	/* set station address */
	newmac = dp->cur_addr.ether_addr_octet;
	for (i = 0; i < ETHERADDRL; i += 2) {
		OUTW(dp, StationAddress + i, (newmac[i+1] << 8) | newmac[i]);
	}

	/* enable rx again */
	if (dp->start) {
		OUTW(dp, MACCtrl1, MC1_RxEnable);
	}
}

static int
alta_set_media(struct alta_dev *dp)
{
	uint16_t	old;
	uint16_t	new;
	int		i;

	ASSERT(mutex_owned(&dp->intrlock));

	/*
	 * Notify current duplex mode to MAC
	 */
	old = INW(dp, MACCtrl0);
	new = old & ~(MC0_FullDuplexEnable | MC0_FlowControlEnable);

	if (dp->full_duplex) {
		new |= MC0_FullDuplexEnable;
		if (dp->flow_control) {
			new |= MC0_FlowControlEnable;
		}
	}

	OUTW(dp, MACCtrl0, new);
	
	if ((old ^ new) & MC0_FullDuplexEnable) {
		/*
		 * Duplex mode is changed. Need to reset Tx/Rx.
		 */
		OUTL(dp, AsicCtrl, AC_TxReset | AC_RxReset);
		i = 200;
		while (INL(dp, AsicCtrl) & AC_ResetBusy) {
			if (i-- == 0) {
				/* Time out */
				cmn_err(CE_WARN,
				"%s alta_set_media: tx/rx reset timeout",
				dp->name);
				break;
			}
			drv_usecwait(10);
		}

		if (dp->start) {
			OUTW(dp, MACCtrl1, MC1_TxEnable | MC1_RxEnable);
		}
	}

	return 0;
}

static void
alta_get_stats_chip(struct alta_dev *dp)
{
	int		first_coll;
	int		multi_coll;
	volatile int	x;

	DPRINTF(4, (CE_CONT, "!%s: alta_get_stats_chip: called", dp->name));

	ASSERT(mutex_owned(&dp->intrlock));

	OUTW(dp, MACCtrl1, MC1_StatisticsDisable);

				x= INL(dp, OctetsRecevedOK);
				x= INL(dp, OctetsTransmittedOK);

				x= INW(dp, FramesTransmittedOK);
				x= INW(dp, FramesReceivedOK);

	dp->stats.nocarrier     += INB(dp, CarrierSenseErrors);
	dp->stats.xmtlatecoll   += INB(dp, LateCollisionss);
	multi_coll               = INB(dp, MultipleColFrames);
	first_coll               = INB(dp, SingleColFrames);
	dp->stats.defer         += INB(dp, FramesWDeferedXmt);
	dp->stats.missed        += INB(dp, FramesLostRxErrors);
				x= INB(dp, FramesWEXDeferral);
				x= INB(dp, FramesAbortXSClls);
				x= INB(dp, BcstFramesXmtdOK);
				x= INB(dp, BcstFramesRcvdOK);
				x= INB(dp, McstFramesXmtdOK);
				x= INB(dp, McstFramesRcvdOK);

	dp->stats.multi_coll    += multi_coll;
	dp->stats.first_coll    += first_coll;


	/*
	 * Guess total collisions
	 */
	dp->stats.collisions += first_coll + multi_coll*2;

	OUTW(dp, MACCtrl1, MC1_StatisticsEnable);

	return;
}

/* ======================================================================== */
/*
 * MII support routines
 */
/* ======================================================================== */

#define MDIO_DELAY(dp)    {INB(dp, PhyCtrl);INB(dp, PhyCtrl);}

static void
alta_mii_sync(struct alta_dev *dp)
{
	int	i;

	/* output 32 ones */
	for (i = 0; i < 32; i++) {
		OUTB(dp, PhyCtrl, PC_MgmtDir | PC_MgmtData);
		MDIO_DELAY(dp);
		OUTB(dp, PhyCtrl, PC_MgmtDir | PC_MgmtData | PC_MgmtClk);
		MDIO_DELAY(dp);
	}
	return;
}

static uint16_t
alta_mii_read(struct alta_dev *dp, int reg)
{
	uint32_t	cmd;
	uint16_t	ret;
	int		i;
	int		data;

	cmd = (6<<(18+5+5)) | (dp->mii_phy_addr<<(18+5)) | (reg<<18);

	alta_mii_sync(dp);

	OUTB(dp, PhyCtrl, PC_MgmtDir | PC_MgmtData);
	MDIO_DELAY(dp);
	OUTB(dp, PhyCtrl, PC_MgmtDir | PC_MgmtData | PC_MgmtClk);

	for (i = 31; i >= 18; i--) {
		data = ((cmd >> i) & 1) <<  PC_MgmtDataShift;
		OUTB(dp, PhyCtrl, data | PC_MgmtDir);
		MDIO_DELAY(dp);
		OUTB(dp, PhyCtrl, data | PC_MgmtDir | PC_MgmtClk);
		MDIO_DELAY(dp);
	}

	for (i = 17; i >= 0; i--) {
		OUTB(dp, PhyCtrl, 0);
		MDIO_DELAY(dp);
		ret = (ret << 1) | ((INB(dp, PhyCtrl) >> PC_MgmtDataShift) & 1);
		OUTB(dp, PhyCtrl, PC_MgmtClk);
		MDIO_DELAY(dp);
	}

	OUTB(dp, PhyCtrl, 0);

	return ret;
}

static void
alta_mii_write(struct alta_dev *dp, int reg, uint16_t val)
{
	int	cmd;
	int	i;
	int	data;

	cmd = (5<<(18+5+5)) | (dp->mii_phy_addr<<(18+5))
		| (reg<<18) | (2 << 16) | val;

	alta_mii_sync(dp);

	OUTB(dp, PhyCtrl, PC_MgmtDir | PC_MgmtData);
	MDIO_DELAY(dp);
	OUTB(dp, PhyCtrl, PC_MgmtDir | PC_MgmtData | PC_MgmtClk);

	for (i = 31; i >= 0; i--) {
		data = ((cmd >> i) & 1) << PC_MgmtDataShift;
		OUTB(dp, PhyCtrl, data | PC_MgmtDir);
		MDIO_DELAY(dp);
		OUTB(dp, PhyCtrl, data | PC_MgmtDir | PC_MgmtClk);
		MDIO_DELAY(dp);
	}

	for (i = 0; i < 2; i++) {
		OUTB(dp, PhyCtrl, 0);
		MDIO_DELAY(dp);
		OUTB(dp, PhyCtrl, PC_MgmtClk);
		MDIO_DELAY(dp);
	}

	return;
}
#undef MDIO_DELAY

static int
alta_mii_config(struct alta_dev *dp)
{
	uint16_t	mii_stat;
	uint16_t	val;

	DPRINTF(2, (CE_CONT, "%s: alta_mii_config: called", dp->name));

	if (dp->mii_fixedmode) {
		val = 0;
		dp->flow_control = FALSE;
		if (dp->full_duplex) {
			val |= MII_CONTROL_FDUPLEX;
		}
		if (dp->speed100) {
			val |= MII_CONTROL_100MB;
		}
		MII_WRITE(dp, MII_CONTROL, val);
		return 0;
	}

	/*
	 * Set advertisement register
	 */
	mii_stat = MII_READ(dp, MII_STATUS);
	DPRINTF(2, (CE_CONT, "%s: alta_mii_config: MII_STATUS reg:%b",
		dp->name, mii_stat, MII_STATUS_BITS));

	if ((mii_stat & MII_STATUS_ABILITY) == 0) {
		/* it's funny */
		cmn_err(CE_WARN, "%s: wrong ability bits: mii_status:%b",
			dp->name, mii_stat, MII_STATUS_BITS);
		return -1;
	}

	/* Do not change rest of ability bits in advert reg */
	val = MII_READ(dp, MII_AN_ADVERT) & ~MII_ABILITY;

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

	if (dp->flow_control_req) {
		val |= MII_ABILITY_PAUSE;
	} else {
		val &= ~MII_ABILITY_PAUSE;
	}

	DPRINTF(2, (CE_CONT, "%s: alta_mii_config: setting MII_AN_ADVERT reg:%b",
		dp->name, val, MII_ABILITY_BITS));

	MII_WRITE(dp, MII_AN_ADVERT, val);

	return 0;
}

static void
alta_mii_link_watcher(struct alta_dev *dp)
{
	uint16_t	mii_stat;
	uint16_t	advert;
	uint16_t	lpable;
	uint16_t	val;

	/* read PHY status */
	mii_stat = MII_READ(dp, MII_STATUS);
	DPRINTF(4, (CE_CONT,
	"%s: alta_mii_link_watcher: called: mii_state:%d MII_STATUS reg:%b",
		dp->name, dp->mii_state,
		mii_stat, MII_STATUS_BITS));

	if (dp->mii_state == MII_STATE_RESETTING) {
		if (--dp->mii_timer > 0) {
			/* wait for time-up */
			goto next;
		}
		/* Timer expired, ensure reset bit is not set */
		MII_SYNC(dp);
		if ((MII_READ(dp, MII_CONTROL) & MII_CONTROL_RESET) != 0) {
			/* reset have not done, try reset again */
			cmn_err(CE_WARN, "%s: resetting mii not complete.",
				dp->name);
			goto reset_phy;

		}
		/* Configure PHY registers */
		if (alta_mii_config(dp) != 0) {
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
			 * Something wrong happend on the link partner.
			 * What do we do ?
			 */
			cmn_err(CE_CONT,
				"!%s: auto-negotiation failed: remfault",
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
					"%s: auto-negotiation failed: timeout",
					dp->name);
					dp->mii_supress_msg = TRUE;
				}
				goto reset_phy;
			}
			/*
			 * Auto-negotiation is in progress. Wait.
			 */
			goto next;
		}
		/*
		 * Auto-negotiation have done.
		 * Assume linkdown and fall through.
		 */
		dp->mii_state = MII_STATE_LINKDOWN;
		dp->mii_timer = MII_LINKDOWN_TIMEOUT;
		cmn_err(CE_CONT, "!%s: auto-negotiation done", dp->name);
	}

	dp->mii_supress_msg = FALSE;

	if (dp->mii_state != MII_STATE_LINKDOWN &&
	    ((mii_stat & MII_STATUS_LINKUP) == 0)) {
		/*
		 * Link going down
		 */
		cmn_err(CE_NOTE, "%s: link down detected: mii_stat:%b",
			dp->name, mii_stat, MII_STATUS_BITS);
		dp->mii_state = MII_STATE_LINKDOWN;
		dp->mii_timer = MII_LINKDOWN_TIMEOUT;
	}
	else if (dp->mii_state != MII_STATE_LINKUP &&
		((mii_stat & MII_STATUS_LINKUP) != 0)) {
		/*
		 * Link going up
		 */
		dp->mii_state = MII_STATE_LINKUP;

		DPRINTF(0, (CE_CONT, "!%s: link up detected: mii_stat:%b",
			dp->name, mii_stat, MII_STATUS_BITS));

		if (!dp->mii_fixedmode) {
			/*
			 * Auto negotiation
			 */
			/* determine full/half and 100mbps/10mbps */
			advert = MII_READ(dp, MII_AN_ADVERT);
			lpable = MII_READ(dp, MII_AN_LPABLE);

			DPRINTF(0, (CE_CONT,
			"!%s: alta_mii_link_watcher: advert:%b, lpable:%b",
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
				/*
				 * It seem that the link partnar don't have
				 * auto-negotiation capability and our PHY
				 * could not report current mode correctly.
				 * This case happened on VT86C100A chip.
				 * Guessing current mode from mii_control
				 * register.
				 */
				uint16_t	val17;

				val = MII_READ(dp, MII_CONTROL);
				val17 = MII_READ(dp, 17);

				cmn_err(CE_WARN,
	"%s: link up but auto-nego failed, it's funny.\n"
	"PHY state: control:%b advert:%b lpable:%b r17:0x%x\n"
	"guesses following mode..., but auto-negotiation should be disabled.",
					dp->name,
					val, MII_CONTROL_BITS,
					advert, MII_ABILITY_BITS,
					lpable, MII_ABILITY_BITS, val17);

				dp->speed100 =
				    (val & MII_CONTROL_100MB) ? TRUE : FALSE;
				dp->full_duplex = dp->speed100;

				dp->flow_control = FALSE;
			}

			mutex_enter(&dp->intrlock);
			alta_set_media(dp);
			mutex_exit(&dp->intrlock);
		}

		/*
		 * MII_CONTROL_100MB and  MII_CONTROL_FDUPLEX are ignored
		 * when MII_CONTROL_ANE is set.
		 */
		cmn_err(CE_CONT,
			"!%s: Link up: %d Mbps %s duplex %s flow control",
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
		cmn_err(CE_CONT, "!%s: resetting PHY", dp->name);
	}
	dp->mii_state = MII_STATE_RESETTING;
	dp->mii_timer = MII_RESET_TIMEOUT;

	MII_WRITE(dp, MII_CONTROL, MII_CONTROL_RESET);
	goto next;

autonego:
	if (!dp->mii_supress_msg) {
		cmn_err(CE_CONT, "!%s: start auto-negotiation", dp->name);
	}
	dp->mii_state = MII_STATE_AUTONEGOTIATING;
	dp->mii_timer = MII_AUTONEGO_TIMEOUT;

	val = MII_READ(dp, MII_CONTROL);

	MII_WRITE(dp, MII_CONTROL, val | MII_CONTROL_ANE | MII_CONTROL_RSAN);
	/* fall through */

next:
	dp->link_watcher_id =
		timeout((void (*)(void *))& alta_mii_link_watcher,
				(void *)dp, LINK_WATCH_INTERVAL);

	return;
}

static int
alta_mii_init(struct alta_dev *dp)
{
	int		phy;
	uint16_t	adv;
	uint16_t	status;
	uint32_t	phyid;
	uint16_t	val;

	DPRINTF(3, (CE_CONT, "%s: alta_mii_init: called", dp->name));

	/*
	 * Scan PHY
	 */
	MII_SYNC(dp);

	for (phy = 0; phy < 32; phy++) {
		dp->mii_phy_addr = phy;
		status = MII_READ(dp, MII_STATUS);

		if (status != 0xffff && status != 0x0000) {
			goto PHY_found;
		}
	}

	cmn_err(CE_WARN, "!%s: failed to find PHY", dp->name);
	return -1;

PHY_found:
	phyid  = MII_READ(dp, MII_PHYIDH) << 16;
	phyid |= MII_READ(dp, MII_PHYIDL);
	adv = MII_READ(dp, MII_AN_ADVERT);
	val = MII_READ(dp, MII_CONTROL);
	cmn_err(CE_CONT, "!%s: PHY (0x%08x) "
		"found at %d, control:%b, status:%b, advert:%b, lpar:%b",
		dp->name, phyid, dp->mii_phy_addr,
		val, MII_CONTROL_BITS,
		status, MII_STATUS_BITS,
		adv, MII_ABILITY_BITS,
		MII_READ(dp, MII_AN_LPABLE),
		MII_ABILITY_BITS);

	/* reset PHY */
	dp->mii_state = MII_STATE_RESETTING;
	dp->mii_timer = MII_RESET_TIMEOUT;
	MII_WRITE(dp, MII_CONTROL, MII_CONTROL_RESET);

	/* schedule first call of alta_link_watcher */
	dp->link_watcher_id =
		timeout((void (*)(void *))alta_mii_link_watcher,
				(void *)dp, LINK_WATCH_INTERVAL);
	return 0;
}

static void
alta_mii_stop(struct alta_dev *dp)
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
E 1
