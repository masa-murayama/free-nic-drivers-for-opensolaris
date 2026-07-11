/* sis190.c: A SiS 191/190 PCI Gigabit/Fast Ethernet driver for Linux.
   Copyright 2004 Silicon Integrated Systems Corporation 
   Revision:	1.00.00 <2004/12/20>

   Modified from the driver which is originally written by Donald Becker.
   
   This software may be used and distributed according to the terms
   of the GNU General Public License (GPL), incorporated herein by reference.
   Drivers based on this skeleton fall under the GPL and must retain
   the authorship (implicit copyright) notice.
   
   References:
   SiS 965 MuTIOL Media I/O Programming Guide
   preliminary Rev. 1.0 Nov. 01, 2004
   http://www.sis.com.tw/support/databook.htm

   Rev 1.00.00 <2004/12/20> Chung-Hsien Chang <changch@sis.com> Initial release
*/

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/string.h>
#include <linux/timer.h>
#include <linux/errno.h>
#include <linux/ioport.h>
#include <linux/slab.h>
#include <linux/interrupt.h>
#include <linux/pci.h>
#include <linux/netdevice.h>
#include <linux/init.h>
#include <linux/mii.h>
#include <linux/etherdevice.h>
#include <linux/skbuff.h>
#include <linux/delay.h>
#include <linux/ethtool.h>
#include <linux/crc32.h>
#include <asm/processor.h>      /* Processor type for cache alignment. */
#include <asm/bitops.h>
#include <asm/io.h>
#include <asm/uaccess.h>	/* User space memory access functions */


#define SIS190_MODULE_NAME "sis190"
#define SIS190_DRV_VERSION "v1.00.00 12/14/2004"

#define COOL_DEBUG 0

/* The I/O extent, SiS 190 needs 256 bytes of io address */
#define SIS190_TOTAL_SIZE 0x100

#define BIT_0	0x00000001
#define BIT_1	0x00000002
#define BIT_2	0x00000004
#define BIT_3	0x00000008
#define BIT_4	0x00000010
#define BIT_5	0x00000020
#define BIT_6	0x00000040
#define BIT_7	0x00000080
#define BIT_8	0x00000100
#define BIT_9	0x00000200
#define BIT_10	0x00000400
#define BIT_11	0x00000800
#define BIT_12	0x00001000
#define BIT_13	0x00002000
#define BIT_14	0x00004000
#define BIT_15	0x00008000
#define BIT_16	0x00010000
#define BIT_17	0x00020000
#define BIT_18	0x00040000
#define BIT_19	0x00080000
#define BIT_20	0x00100000
#define BIT_21	0x00200000
#define BIT_22	0x00400000
#define BIT_23	0x00800000
#define BIT_24	0x01000000
#define BIT_25	0x02000000
#define BIT_26	0x04000000
#define BIT_27	0x08000000
#define BIT_28	0x10000000
#define BIT_29	0x20000000
#define BIT_30	0x40000000
#define BIT_31	0x80000000

#define BIT_0_5	0x0000003f
#define BIT_3_15	0x0000fff8
#define BIT_8_11	0x00000f00
#define BIT_10_11	0x00000c00
#define BIT_16_19	0x000f0000
#define BIT_24_27	0x0f000000
#define BIT_24_30	0x7f000000


/* Symbolic offsets to registers. */
enum sis190_registers {
	TxCtrl 	= 0x0,			// Tx Host Control/status Register
	TxBase 	= 0x4,			// Tx Home Descriptor Base Register
	rsv0 		= 0x8,			// Reserved
	TxSts 		= 0xc,			// Tx Next Descriptor Control/Status Register
	RxCtrl 	= 0x10,		// Rx Host Control/status Register
	RxBase 	= 0x14,		// Rx Home Descriptor Base Register
	rsv1 		= 0x18,		// Reserved
	RxSts 		= 0x1c,		// Rx Next Descriptor Control/Status Register
	IntSrc 	= 0x20,		// Interrupt Source Register
	IntMask 	= 0x24,		// Interrupt Mask Register
	IntCtrl 	= 0x28,		// Interrupt Control Register
	IntTimer	= 0x2c,		// Interupt Timer Register
	PowCtrl	= 0x30,		// Power Management Control/Status Register
	rsv2		= 0x34,		// Reserved
	EepCtrl	= 0x38,		// EEPROM Control/Status Register
	EepIntf	= 0x3c,		// EEPROM Interface Register
	StationCtrl 	= 0x40,		// Station Control/Status Register
	SmiIntf 	= 0x44,		// Station Management Interface Register
	GIoCR 		= 0x48,		// GMAC IO Compensation Register
	GIoCtrl 	= 0x4c,		// GMAC IO Control Register
	TxMacCtrl 	= 0x50,		// Tx MAC Control Register
	TxLimit 	= 0x54,		// Tx MAC Timer/TryLimit Register
	RGDelay 	= 0x58,		// RGMII Tx Internal Delay Control Register
	rsv3 		= 0x5c,		// Reserved
	RxMacCtrl	= 0x60,		// Rx MAC Control Register
	RxMacAddr	= 0x62,		// Rx MAC Unicast Address Register
	RxHashTbl	= 0x68,		// Rx MAC Multicast Hash Table Register
	RxWolCtrl	= 0x70,		// Rx WOL Control Register
	RxWolData	= 0x74,		// Rx WOL Data Access Register
	RxMpsCtrl	= 0x78,		// Rx MPS Control Register
	rsv4		= 0x7c			// Reserved
};

enum sis190_tx_desc_cmd_bits {
	PADEN	= BIT_16,
	CRCEN	= BIT_17,
	COLEN	= BIT_18,
	CRSEN	= BIT_19,
	BKFEN	= BIT_20,
	DEFEN	= BIT_21,
	EXTEN	= BIT_22,
	BSTEN	= BIT_23,
	UDPCS	= BIT_24,
	TCPCS	= BIT_25,
	IPCS	= BIT_26,
	LSEN	= BIT_27,
	THOL0	= 0x00000000,
	THOL1	= 0x10000000,
	THOL2	= 0x20000000,
	THOL3	= 0x30000000,
	TXINT	= BIT_30,
	TXOWN	= BIT_31
};

enum sis190_rx_desc_sts_bits {
	CRCOK	= BIT_16,
	COLON	= BIT_17,
	NIBON	= BIT_18,
	OVRUN	= BIT_19,
	MIIER	= BIT_20,
	LIMIT	= BIT_21,
	SHORT	= BIT_22,
	ABORT	= BIT_23,
	TAGON	= BIT_31
};

enum sis190_rx_desc_info_bits {
	PREADD	= BIT_16,
	CRCOFF	= BIT_17,	
	UCAST	= 0x00040000,
	MCAST	= 0x00080000,
	BCAST	= 0x000c0000,
	PAUSE	= BIT_20,
	MAGIC	= BIT_21,
	WAKUP	= BIT_22,
	UDPON	= BIT_27,
	TCPON	= BIT_28,
	IPON	= BIT_29,
	RXINT	= BIT_30,
	RXOWN	= BIT_31
};

enum sis190_eeprom_access_reigster_bits {
	EECS = 0x00000001, EECLK = 0x00000002, EEDO = 0x00000008,
	EEDI = 0x00000004, EEREQ = 0x00000080, EEROP = 0x00000200, 
	EEWOP = 0x00000100
};

enum sis190_smi_access_reigster_bits {
	MDC  = 0x00000002, MDDIR = 0x00000004, MDIO = 0x00000008, 
	MDEN = 0x00000001, SMIREQ = 0x00000010, SMIWRITE = 0x00000020,
	SMIREAD = 0x00000000
};


/* EEPROM Addresses */
enum sis190_eeprom_address {
	EEPROMSignature = 0x00, EEPROMCLK = 0x01, EEPROMInfo = 0x02,
	EEPROMMACAddr   = 0x03
};

/* MII register offsets */
enum mii_registers {
	MII_CONTROL = 0x0000, MII_STATUS = 0x0001, MII_PHY_ID0 = 0x0002,
	MII_PHY_ID1 = 0x0003, MII_ANADV  = 0x0004, MII_ANLPAR  = 0x0005,
	MII_ANEXT   = 0x0006, MII_ANGADV = 0x0009, MII_ANGLPAR = 0x000a
};

/* MII Control register bit definitions. */
enum mii_control_register_bits {
	MII_CNTL_FDX     = 0x0100, MII_CNTL_RST_AUTO = 0x0200, 
	MII_CNTL_ISOLATE = 0x0400, MII_CNTL_PWRDWN   = 0x0800,
	MII_CNTL_AUTO    = 0x1000, MII_CNTL_SPEED    = 0x2000,
	MII_CNTL_LPBK    = 0x4000, MII_CNTL_RESET    = 0x8000
};

/* MII Status register bit  */
enum mii_status_register_bits {
	MII_STAT_EXT    = 0x0001, MII_STAT_JAB        = 0x0002, 
	MII_STAT_LINK   = 0x0004, MII_STAT_CAN_AUTO   = 0x0008, 
	MII_STAT_FAULT  = 0x0010, MII_STAT_AUTO_DONE  = 0x0020,
	MII_STAT_CAN_T  = 0x0800, MII_STAT_CAN_T_FDX  = 0x1000,
	MII_STAT_CAN_TX = 0x2000, MII_STAT_CAN_TX_FDX = 0x4000,
	MII_STAT_CAN_T4 = 0x8000
};

/* MII NWAY Register Bits ...
   valid for the ANAR (Auto-Negotiation Advertisement) and
   ANLPAR (Auto-Negotiation Link Partner) registers */
enum mii_nway_register_bits {
	MII_NWAY_NODE_SEL = 0x001f, MII_NWAY_CSMA_CD = 0x0001,
	MII_NWAY_T	  = 0x0020, MII_NWAY_T_FDX   = 0x0040,
	MII_NWAY_TX       = 0x0080, MII_NWAY_TX_FDX  = 0x0100,
	MII_NWAY_T4       = 0x0200, MII_NWAY_PAUSE   = 0x0400,
	MII_NWAY_RF       = 0x2000, MII_NWAY_ACK     = 0x4000,
	MII_NWAY_NP       = 0x8000
};

#define INT_MASK	0x000100cf

#define FDX_CAPABLE_DUPLEX_UNKNOWN      0
#define FDX_CAPABLE_HALF_SELECTED       1
#define FDX_CAPABLE_FULL_SELECTED       2

#define HW_SPEED_UNCONFIG		0
#define HW_SPEED_HOME		1
#define HW_SPEED_10_MBPS        	10
#define HW_SPEED_100_MBPS       	100
#define HW_SPEED_1000_MBPS       	1000
#define HW_SPEED_DEFAULT        	(HW_SPEED_100_MBPS)

#define CRC_SIZE                4
#define MAC_HEADER_SIZE         14

#define TX_BUF_SIZE     1536
#define RX_BUF_SIZE     1536

#define NUM_TX_DESC     32      	/* Number of Tx descriptor registers. */
#define NUM_RX_DESC     32       	/* Number of Rx descriptor registers. */
#define TX_TOTAL_SIZE	NUM_TX_DESC*sizeof(HwTcb)
#define RX_TOTAL_SIZE	NUM_RX_DESC*sizeof(HwRfd)

static char version[] __devinitdata =
KERN_INFO "sis190.c: " SIS190_DRV_VERSION "\n";

static int max_interrupt_work = 40;
static int multicast_filter_limit = 128;

#define sis190_debug debug
static int sis190_debug;

/* Time in jiffies before concluding the transmitter is hung. */
#define TX_TIMEOUT  (4*HZ)
/* SiS 190 is capable of 32 bits BM DMA */
#define SIS190_DMA_MASK 0xffffffff

enum {
	SIS_190 = 0,
	SIS_191
};
static char * card_names[] = {
	"SiS 190 PCI Fast Ethernet Adapter",
	"SiS 191 PCI Gigabit Ethernet Adapter"
};
static struct pci_device_id sis190_pci_tbl [] = {
	{0x1039, 0x0190, PCI_ANY_ID, PCI_ANY_ID, 0, 0, SIS_190},
	{0x1039, 0x0191, PCI_ANY_ID, PCI_ANY_ID, 0, 0, SIS_191},
	{0,}
};
MODULE_DEVICE_TABLE (pci, sis190_pci_tbl);

static void sis190_read_mode(struct net_device *net_dev, int *speed, int *duplex);

static struct mii_chip_info {
	const char * name;
	u16 phy_id0;
	u16 phy_id1;
	u8  phy_types;
#define HOME	0x0001
#define LAN	0x0002
#define MIX	0x0003
#define UNKNOWN	0x0
} mii_chip_table[] = {
	{ "Broadcom PHY BCM5461", 		0x0020, 0x60c0, LAN },
	{ "Agere PHY ET1101B", 			0x0282, 0xf010, LAN },
	{ "Marvell PHY 88E1111", 			0x0141, 0x0cc0, LAN },
	{NULL,},
};

struct mii_phy {
	struct mii_phy * next;
	int phy_addr;
	u16 phy_id0;
	u16 phy_id1;
	u16 status;
	u8  phy_types;
};

typedef struct _HwTcb {
	u32	PktSize;
	u32	cmdsts;
	u32	bufptr;
	u32 EOD;
	//u32 link;
} HwTcb;

typedef struct _HwRfd {
	u32	StsSize;
	u32	PktInfo;
	u32	bufptr;
	u32 EOD;
	//u32 cmdsts;
} HwRfd;

struct sis190_private {
	struct net_device_stats stats;
	struct pci_dev * pci_dev;

	spinlock_t lock;

	struct mii_phy * mii;
	struct mii_phy * first_mii; /* record the first mii structure */
	unsigned int cur_phy;

	struct timer_list timer; /* Link status detection timer. */
	u8     autong_complete; /* 1: auto-negotiate complete  */
	u32 vendor; /* Vendor ID */
	u32 device; /* Device ID */

	unsigned int cur_rx, dirty_rx; /* producer/comsumer pointers for Tx/Rx ring */
	unsigned int cur_tx, dirty_tx;

	/* The saved address of a sent/receive-in-place packet buffer */
	struct sk_buff *tx_skbuff[NUM_TX_DESC];
	struct sk_buff *rx_skbuff[NUM_RX_DESC];
	HwTcb *org_tx_ring;	
	HwTcb *tx_ring;
	HwRfd *org_rx_ring;
	HwRfd *rx_ring;

	dma_addr_t org_tx_ring_dma;
	dma_addr_t tx_ring_dma;
	dma_addr_t org_rx_ring_dma;
	dma_addr_t rx_ring_dma;

	unsigned int tx_full;			/* The Tx queue is full.    */
	u8 host_bridge_rev;
	u32 pci_state[16];
	int speed;
	int duplex;
	int RGMII;
};

MODULE_AUTHOR("C.H. Chang <changch@sis.com>");
MODULE_DESCRIPTION("SiS191/SiS190 1000/100/10 Ethernet driver");
MODULE_LICENSE("GPL");

MODULE_PARM(multicast_filter_limit, "i");
MODULE_PARM(max_interrupt_work, "i");
MODULE_PARM(debug, "i");
MODULE_PARM_DESC(multicast_filter_limit, "SiS 191/190 maximum number of filtered multicast addresses");
MODULE_PARM_DESC(max_interrupt_work, "SiS 191/190 maximum events handled per interrupt");
MODULE_PARM_DESC(debug, "SiS 191/190 debug level (2-4)");

static int sis190_open(struct net_device *net_dev);
static int sis190_mii_probe (struct net_device * net_dev);
static void sis190_init_rxfilter (struct net_device * net_dev);
static u16 read_eeprom(long ioaddr, int location);
static u16 mdio_read(struct net_device *net_dev, int phy_id, int location);
static void mdio_write(struct net_device *net_dev, int phy_id, int location, int val);
static void sis190_timer(unsigned long data);
static void sis190_tx_timeout(struct net_device *net_dev);
static void sis190_init_tx_ring(struct net_device *net_dev);
static void sis190_init_rx_ring(struct net_device *net_dev);
static int sis190_start_xmit(struct sk_buff *skb, struct net_device *net_dev);
static int sis190_rx(struct net_device *net_dev);
static void sis190_finish_xmit (struct net_device *net_dev);
static irqreturn_t sis190_interrupt(int irq, void *dev_instance, struct pt_regs *regs);
static int sis190_close(struct net_device *net_dev);
static int mii_ioctl(struct net_device *net_dev, struct ifreq *rq, int cmd);
static struct net_device_stats *sis190_get_stats(struct net_device *net_dev);
static u16 sis190_mcast_bitnr(u8 *addr);
static void set_rx_mode(struct net_device *net_dev);
static void sis190_reset(struct net_device *net_dev);
static u16 sis190_default_phy(struct net_device * net_dev);
static u16 sis190_reset_phy(struct net_device *net_dev, int phy_addr);
static void sis190_set_mode (struct net_device *net_dev, int speed, int duplex);
static struct ethtool_ops sis190_ethtool_ops;

#if COOL_DEBUG
static void ShowMacReg(struct net_device *net_dev)
{
	long ioaddr = net_dev->base_addr;
	long i;

	printk("Show Mac Registers\n");
	for(i = 0; i < 0x80; i+=4)
	{
		if((i%16) == 0)
			printk("%2.2xh: ", (char)i);
		
		printk("%8.8x ", inl(ioaddr + i));
		
		if((i%16) == 12)
			printk("\n");
	
	}
	printk("\n");
}

static void ShowTxDesc(struct net_device *net_dev)
{
	struct sis190_private * sis_priv = net_dev->priv;
	u32 i;

	printk("Show Tx Descriptors\n");
	for(i = 0; i < NUM_TX_DESC; i++)
	{
		printk("%2.2xh: %8.8x %8.8x %8.8x %8.8x\n", 
			i, sis_priv->tx_ring[i].PktSize, sis_priv->tx_ring[i].cmdsts, 
			sis_priv->tx_ring[i].bufptr, sis_priv->tx_ring[i].EOD);
	}
	printk("\n");
}

static void ShowRxDesc(struct net_device *net_dev)
{
	struct sis190_private * sis_priv = net_dev->priv;
	u32 i;

	printk("Show Rx Descriptors\n");
	for(i = 0; i < NUM_RX_DESC; i++)
	{
		printk("%2.2xh: %8.8x %8.8x %8.8x %8.8x\n", 
			i, sis_priv->rx_ring[i].StsSize, sis_priv->rx_ring[i].PktInfo, 
			sis_priv->rx_ring[i].bufptr, sis_priv->rx_ring[i].EOD);
	}
	printk("\n");
}

static void ShowPciReg(struct pci_dev *pci_dev)
{
	u32 reg;
	u32 i;

	printk("Show Pci Registers\n");
	for(i=0;i<0x80;i+=4)
	{
		if((i%16) == 0 )
			printk("%2.2xh: ", (char)i);

		pci_read_config_dword(pci_dev, i, &reg);
		printk("%8.8x ", reg);

		if((i%16)==12)
			printk("\n");
	}
	printk("\n");
}

static void ShowPhyReg(struct net_device *net_dev)
{
	struct sis190_private * sis_priv = net_dev->priv;
	u32 i;

	printk("Show Phy Registers\n");
	for(i=0;i<0x20;i++)
	{
		if((i%8) == 0 )
			printk("%2.2xh: ", i);

		printk("%4.4x ", mdio_read(net_dev, sis_priv->cur_phy, i));

		if((i%8)==7)
			printk("\n");
	}
	printk("\n");
}
#endif

/**
 *	sis190_get_mac_addr - Get MAC address for stand alone SiS190 model
 *	@pci_dev: the sis190 pci device
 *	@net_dev: the net device to get address for 
 *
 *	SiS190 use EEPROM or APC to store MAC address.
 *	MAC address is read from read_eeprom() into @net_dev->dev_addr.
 */

static int __devinit sis190_get_mac_addr_from_eeprom(struct pci_dev * pci_dev, struct net_device *net_dev)
{
	struct sis190_private * sis_priv = net_dev->priv;
	long ioaddr = net_dev->base_addr;
	u16 signature;
	u16 reg;
	int i;

	printk(KERN_INFO "%s: Read MAC address from EEPROM\n", net_dev->name);

	/* check to see if we have sane EEPROM */
	signature = (u16) read_eeprom(ioaddr, EEPROMSignature);
	
	if (signature == 0xffff || signature == 0x0000) {
		printk (KERN_INFO "%s: Error EERPOM read %x\n", 
			net_dev->name, signature);
		return 0;
	}

	/* get MAC address from EEPROM */
	for (i = 0; i < 3; i++)
	        ((u16 *)(net_dev->dev_addr))[i] = read_eeprom(ioaddr, i+EEPROMMACAddr);

	reg = (u16) read_eeprom(ioaddr, EEPROMInfo);

	if(reg & BIT_7)
	{
		sis_priv->RGMII = 1;
	}
	else
	{
		sis_priv->RGMII = 0;
	}

	return 1;
}

/**
 *	sis190_get_mac_addr_from_apc - Get MAC address for SiS965 model
 *	@pci_dev: the sis190 pci device
 *	@net_dev: the net device to get address for 
 *
 *	SiS965 model, use APC CMOS RAM to store MAC address.
 *	APC CMOS RAM is accessed through ISA bridge.
 *	MAC address is read into @net_dev->dev_addr.
 */
static int __devinit sis190_get_mac_addr_from_apc(struct pci_dev * pci_dev, struct net_device *net_dev)
{
	struct pci_dev *isa_bridge = NULL;
	struct sis190_private * sis_priv = net_dev->priv;
	u8 reg, temp;
	int i;

	printk(KERN_INFO "%s: Read MAC address from APC\n", net_dev->name);
	
	isa_bridge = pci_find_device(0x1039, 0x0965, isa_bridge);
	if (!isa_bridge) {
		printk("%s: Can not find ISA bridge\n", net_dev->name);
		return 0;
	}
	
	// Enable port 78h & 79h to access APC Registers
	pci_read_config_byte(isa_bridge, 0x48, &temp);
	reg = (temp & ~BIT_1);
	pci_write_config_byte(isa_bridge, 0x48, reg);
	udelay(50);
	pci_read_config_byte(isa_bridge, 0x48, &reg);
	
	// Get MAC Address From APC 
	for ( i = 0; i < 6; i++ )
	{
		outb(0x9+i, 0x78);
		((u8 *)(net_dev->dev_addr))[i] = inb(0x79);
	}

	outb(0x12, 0x78);
	reg = inb(0x79);
	if(reg & BIT_7)
	{
		sis_priv->RGMII = 1;
	}
	else
	{
		sis_priv->RGMII = 0;
	}

	// Restore the value to ISA Bridge
	pci_write_config_byte(isa_bridge, 0x48, temp);

	return 1;
}


/**
 *	sis190_probe - Probe for sis190 device
 *	@pci_dev: the sis190 pci device
 *	@pci_id: the pci device ID
 *
 *	Check and probe sis190 net device for @pci_dev.
 *	Get mac address from EEPROM or APC, 
 *	and assign SiS190-specific entries in the device structure.
 *	ie: sis190_open(), sis190_start_xmit(), sis190_close(), etc.
 */

static int __devinit sis190_probe (struct pci_dev *pci_dev, const struct pci_device_id *pci_id)
{
	struct sis190_private *sis_priv;
	struct net_device *net_dev;
	dma_addr_t ring_dma;
	void *ring_space;
	long ioaddr;
	int i, ret;
	u8 From;
	char *card_name = card_names[pci_id->driver_data];

#if COOL_DEBUG
	printk("SiS190 ==> sis190_probe !!\n");
#endif
	
/* when built into the kernel, we only print version if device is found */
#ifndef MODULE
	static int printed_version;
	if (!printed_version++)
		printk(version);
#endif

	/* setup various bits in PCI command register */
	ret = pci_enable_device(pci_dev);
	if(ret) return ret;
	
	i = pci_set_dma_mask(pci_dev, SIS190_DMA_MASK);
	if(i){
		printk(KERN_ERR "sis190.c: architecture does not support"
			"32bit PCI busmaster DMA\n");
		return i;
	}
	
	pci_set_master(pci_dev);
	
	net_dev = alloc_etherdev(sizeof(struct sis190_private));
	if (!net_dev)
		return -ENOMEM;
	SET_MODULE_OWNER(net_dev);
	SET_NETDEV_DEV(net_dev, &pci_dev->dev);

	/* We do a request_region() to register /proc/ioports info. */
	ioaddr = pci_resource_start(pci_dev, 1);	
	ret = pci_request_regions(pci_dev, "sis190");
	if (ret)
		goto err_out;

	sis_priv = net_dev->priv;
	net_dev->base_addr = ioaddr;
	net_dev->irq = pci_dev->irq;
	sis_priv->pci_dev = pci_dev;
	sis_priv->vendor = pci_id->vendor;
	sis_priv->device = pci_id->device;
	spin_lock_init(&sis_priv->lock);

	printk("sis_priv->vendor = %x, sis_priv->device = %x\n", sis_priv->vendor, sis_priv->device);

	pci_set_drvdata(pci_dev, net_dev);

	// Allocate Tx Descriptors
	ring_space = pci_alloc_consistent(pci_dev, TX_TOTAL_SIZE + 15, &ring_dma);
	if (!ring_space) {
		ret = -ENOMEM;
		goto err_out_cleardev;
	}
	sis_priv->org_tx_ring = (HwTcb *)ring_space;
	sis_priv->org_tx_ring_dma = ring_dma;

	// Alignment for Tx descriptor ring
	sis_priv->tx_ring_dma = ((ring_dma + 0xf) & 0xfffffff0);
	sis_priv->tx_ring = (HwTcb *)(ring_space + (sis_priv->tx_ring_dma - ring_dma));

#if COOL_DEBUG
	printk("sis_priv->org_tx_ring = %x, sis_priv->tx_ring = %x\n", (u32)sis_priv->org_tx_ring, (u32)sis_priv->tx_ring);
	printk("sis_priv->org_tx_ring_dma = %x, sis_priv->tx_ring_dma = %x\n", 
			(u32)sis_priv->org_tx_ring_dma, (u32)sis_priv->tx_ring_dma);
#endif

	// Allocate Rx Descriptors
	ring_space = pci_alloc_consistent(pci_dev, RX_TOTAL_SIZE + 15, &ring_dma);
	if (!ring_space) {
		ret = -ENOMEM;
		goto err_unmap_tx;
	}
	sis_priv->org_rx_ring = (HwRfd *)ring_space;
	sis_priv->org_rx_ring_dma = ring_dma;

	// Alignment for Rx descriptor ring
	sis_priv->rx_ring_dma = ((ring_dma + 0xf) & 0xfffffff0);
	sis_priv->rx_ring = (HwRfd *)(ring_space + (sis_priv->rx_ring_dma - ring_dma));

#if COOL_DEBUG
	printk("sis_priv->org_rx_ring = %x, sis_priv->rx_ring = %x\n", (u32)sis_priv->org_rx_ring, (u32)sis_priv->rx_ring);
	printk("sis_priv->org_rx_ring_dma = %x, sis_priv->rx_ring_dma = %x\n", 
			(u32)sis_priv->org_rx_ring_dma, (u32)sis_priv->rx_ring_dma);
#endif

	/* The SiS190-specific entries in the device structure. */
	net_dev->open = &sis190_open;
	net_dev->hard_start_xmit = &sis190_start_xmit;
	net_dev->stop = &sis190_close;
	net_dev->get_stats = &sis190_get_stats;
	net_dev->set_multicast_list = &set_rx_mode;
	net_dev->do_ioctl = &mii_ioctl;
	net_dev->tx_timeout = sis190_tx_timeout;
	net_dev->watchdog_timeo = TX_TIMEOUT;
	net_dev->ethtool_ops = &sis190_ethtool_ops;
	
	ret = register_netdev(net_dev);
	if (ret)
		goto err_unmap_rx;
		
	/* Get Mac address according to the from bit */
	pci_read_config_byte(pci_dev, 0x73, &From);
	ret = 0;
	
	if (From & BIT_0)
		ret = sis190_get_mac_addr_from_apc(pci_dev, net_dev);
	else
		ret = sis190_get_mac_addr_from_eeprom(pci_dev, net_dev);
	
	if (ret == 0) {
		ret = -ENODEV;
		goto err_out_unregister;
	}
	
	/* probe for mii transceiver */
	if (sis190_mii_probe(net_dev) == 0) {
		ret = -ENODEV;
		goto err_out_unregister;
	}

	/* print some information about our NIC */
	printk(KERN_INFO "%s: %s at %#lx, IRQ %d, ", net_dev->name,
	       card_name, ioaddr, net_dev->irq);
	
	for(i = 0; i < 5; i++)
		printk("%2.2x:", (u8)net_dev->dev_addr[i]);
	printk("%2.2x.\n", (u8)net_dev->dev_addr[i]);

	if(sis_priv->RGMII)
		printk(KERN_INFO "%s: Run in RGMII mode.\n", net_dev->name);
	else
		printk(KERN_INFO "%s: Run in GMII mode.\n", net_dev->name);
	return 0;

 err_out_unregister:
 	unregister_netdev(net_dev);
 err_unmap_rx:
	pci_free_consistent(pci_dev, RX_TOTAL_SIZE + 15, sis_priv->org_rx_ring,
		sis_priv->org_rx_ring_dma);
 err_unmap_tx:
	pci_free_consistent(pci_dev, TX_TOTAL_SIZE + 15, sis_priv->org_tx_ring,
		sis_priv->org_tx_ring_dma);
 err_out_cleardev:
 	pci_set_drvdata(pci_dev, NULL);
	pci_release_regions(pci_dev);
 err_out:
	free_netdev(net_dev);
	return ret;
}

/**
 *	sis190_mii_probe - Probe MII PHY for sis190
 *	@net_dev: the net device to probe for
 *	
 *	Search for total of 32 possible mii phy addresses.
 *	Identify and set current phy if found one,
 *	return error if it failed to found.
 */

static int __init sis190_mii_probe (struct net_device * net_dev)
{
	struct sis190_private * sis_priv = net_dev->priv;
	long ioaddr = net_dev->base_addr;
	u16 poll_bit = MII_STAT_LINK, status = 0;
	unsigned long timeout = jiffies + 5 * HZ;
	int phy_addr;
	int complete = 0;
	int speed, duplex;
	int i;

	sis_priv->mii = NULL;

	/* search for total of 32 possible mii phy addresses */
	for (phy_addr = 0; phy_addr < 32; phy_addr++) 
	{	
		struct mii_phy * mii_phy = NULL;
		u16 mii_status;
		int i;

		mii_phy = NULL;
		for(i = 0; i < 2; i++)
			mii_status = mdio_read(net_dev, phy_addr, MII_STATUS);

		if (mii_status == 0xffff || mii_status == 0x0000)
			/* the mii is not accessible, try next one */
			continue;
		
		if ((mii_phy = kmalloc(sizeof(struct mii_phy), GFP_KERNEL)) == NULL) 
		{
			printk(KERN_INFO "Cannot allocate mem for struct mii_phy\n");
			mii_phy = sis_priv->first_mii;
			while (mii_phy) 
			{
				struct mii_phy *phy;
				phy = mii_phy;
				mii_phy = mii_phy->next;
				kfree(phy);
			}
			return 0;
		}
		
		mii_phy->phy_id0 = mdio_read(net_dev, phy_addr, MII_PHY_ID0);
		mii_phy->phy_id1 = mdio_read(net_dev, phy_addr, MII_PHY_ID1);		
		mii_phy->phy_addr = phy_addr;
		mii_phy->status = mii_status;
		mii_phy->next = sis_priv->mii;
		sis_priv->mii = mii_phy;
		sis_priv->first_mii = mii_phy;

		for (i = 0; mii_chip_table[i].phy_id1; i++)
		{
			if ((mii_phy->phy_id0 == mii_chip_table[i].phy_id0 ) &&
			    ((mii_phy->phy_id1 & 0xFFF0) == mii_chip_table[i].phy_id1))
			{
				mii_phy->phy_types = mii_chip_table[i].phy_types;
				if (mii_chip_table[i].phy_types == MIX)
					mii_phy->phy_types =
						(mii_status & (MII_STAT_CAN_TX_FDX | MII_STAT_CAN_TX)) ? LAN : HOME;
				
				printk(KERN_INFO "%s: %s transceiver found at address %d.\n",
				       net_dev->name, mii_chip_table[i].name, phy_addr);
				break;
			}
		}
			
		if( !mii_chip_table[i].phy_id1 ) {
			printk(KERN_INFO "%s: Unknown PHY transceiver found at address %d.\n",
			       net_dev->name, phy_addr);
			mii_phy->phy_types = UNKNOWN;
		}
	}
	
	if (sis_priv->mii == NULL) {
		printk(KERN_INFO "%s: No MII transceivers found!\n",
		       net_dev->name);
		return 0;
	}

	/* select default PHY for mac */
	sis_priv->mii = NULL;
	sis190_default_phy( net_dev );

	// For Marvell 88E1111 PHY
	if((sis_priv->mii->phy_id0 == 0x0141) && (sis_priv->mii->phy_id1 == 0x0cc1))
	{
		// Set RGMII mode for Marvell 88E1111 PHY
		if(sis_priv->RGMII)
		{
			mdio_write(net_dev, sis_priv->cur_phy, 0x1b, 0x808b);
			udelay(200);
			mdio_write(net_dev, sis_priv->cur_phy, 0x14, 0x0ce1);
			udelay(200);
		}
		// Set GMII mode for Marvell 88E1111 PHY
		else
		{
			mdio_write(net_dev, sis_priv->cur_phy, 0x1b, 0x808f);
			udelay(200);
			mdio_write(net_dev, sis_priv->cur_phy, 0x14, 0x0c60);
			udelay(200);
		}
	}

	/* Reset phy */
	status = sis190_reset_phy(net_dev, sis_priv->cur_phy);
        
	if(status & MII_STAT_LINK){
		while (poll_bit) {
			yield();

			poll_bit ^= (mdio_read(net_dev, sis_priv->cur_phy, MII_STATUS) & poll_bit);
			if (time_after_eq(jiffies, timeout)) {
				printk(KERN_WARNING "%s: reset phy and link down now\n", net_dev->name);
				return -ETIME;
			}
		}
	}

	status = mdio_read(net_dev, sis_priv->cur_phy, MII_STATUS);
	if(status & MII_STAT_LINK)
	{
		for( i = 0; i < 1000; i++)
		{
			status = mdio_read(net_dev, sis_priv->cur_phy, MII_STATUS);
			if(status & MII_STAT_AUTO_DONE)
			{
				complete = 1;
				break;
			}
			udelay(100);
		}
	}

	if(complete)
	{
		sis190_read_mode(net_dev, &speed, &duplex);
		sis_priv->speed = speed;
		sis_priv->duplex = duplex;	
		sis190_set_mode(net_dev, speed, duplex);	
	}

	if (sis_priv->mii->status & MII_STAT_LINK)
	{
		// Set Tx Dealy
		if(sis_priv->RGMII)
		{
			// For Broadcom BCM5461 PHY, set Tx Delay in RGMII mode
			if((sis_priv->mii->phy_id0 == 0x0020) && (sis_priv->mii->phy_id1 == 0x60c1))
			{
				mdio_write(net_dev, sis_priv->cur_phy, 0x18, 0xf1c7);
				udelay(200);
				mdio_write(net_dev, sis_priv->cur_phy, 0x1c, 0x8c00);
			}

			outl(0x0441, ioaddr + RGDelay);
			outl(0x0440, ioaddr + RGDelay);
		}
		netif_carrier_on(net_dev);
	}
	else
	{
		netif_carrier_off(net_dev);
	}
	return 1;
}

/**
 *	sis190_default_phy - Select default PHY for sis190 mac.
 *	@net_dev: the net device to probe for
 *
 *	Select first detected PHY with link as default.
 *	If no one is link on, select PHY whose types is HOME as default.
 *	If HOME doesn't exist, select LAN.
 */

static u16 sis190_default_phy(struct net_device * net_dev)
{
	struct sis190_private * sis_priv = net_dev->priv;
 	struct mii_phy *phy = NULL, *phy_home = NULL, *default_phy = NULL, *phy_lan = NULL;
	u16 status;

        for( phy=sis_priv->first_mii; phy; phy=phy->next ){
		status = mdio_read(net_dev, phy->phy_addr, MII_STATUS);
		status = mdio_read(net_dev, phy->phy_addr, MII_STATUS);

		/* Link ON & Not select default PHY & not ghost PHY */
		 if ( (status & MII_STAT_LINK) && !default_phy && (phy->phy_types != UNKNOWN) )
		 	default_phy = phy;
		 else{
			status = mdio_read(net_dev, phy->phy_addr, MII_CONTROL);
			mdio_write(net_dev, phy->phy_addr, MII_CONTROL,
				status | MII_CNTL_AUTO | MII_CNTL_ISOLATE);
			if( phy->phy_types == HOME )
				phy_home = phy;
			else if (phy->phy_types == LAN)
				phy_lan = phy;
		 }
	}

	if( !default_phy && phy_home )
		default_phy = phy_home;
	else if( !default_phy && phy_lan )
		default_phy = phy_lan;
	else if ( !default_phy )
		default_phy = sis_priv->first_mii;

	if( sis_priv->mii != default_phy ){
		sis_priv->mii = default_phy;
		sis_priv->cur_phy = default_phy->phy_addr;
		printk(KERN_INFO "%s: Using transceiver found at address %d as default\n", net_dev->name,sis_priv->cur_phy);
	}
	
	status = mdio_read(net_dev, sis_priv->cur_phy, MII_CONTROL);
	status &= (~MII_CNTL_ISOLATE);

	mdio_write(net_dev, sis_priv->cur_phy, MII_CONTROL, status);	
	status = mdio_read(net_dev, sis_priv->cur_phy, MII_STATUS);
	status = mdio_read(net_dev, sis_priv->cur_phy, MII_STATUS);

	return status;	
}

/**
 *	read_eeprom - Read Parallel EEPROM
 *	@ioaddr: base i/o address
 *	@location: the EEPROM location to read
 *
 *	Read Parallel EEPROM through EEPROM Access Register.
 *	Note that location is in word (16 bits) unit
 */

static u16 __devinit read_eeprom(long ioaddr, int location)
{
	int i;
	u16 retval = 0;
	long ee_addr = ioaddr + EepIntf;
	u32 read_cmd;
	u32 ulval;

	read_cmd = EEREQ | EEROP | (((u32)location & 0x3f) << 10);

	outl(read_cmd, ee_addr);

	udelay(500);

	for ( i = 0; i < 1000; i++ )
	{		
		ulval = inl(ee_addr);

		if(!(ulval & EEREQ))
			break;
		
		udelay(100);
	}
	
	// Read EEPROM Failed
	if ( i > 999 )
		retval = 0xffff;
	else
		retval = (u16)((ulval & 0xffff0000) >> 16);
	
	return (retval);
}

/**
 *	mdio_read - read MII PHY register
 *	@net_dev: the net device to read
 *	@phy_id: the phy address to read
 *	@location: the phy regiester id to read
 *
 *	Read MII registers through SMI Interface Register
 */

static u16 mdio_read(struct net_device *net_dev, int phy_id, int location)
{
	long mdio_addr = net_dev->base_addr + SmiIntf;
	int mii_cmd;
	u32 reg;
	u16 retval = 0;
	int i;

	mii_cmd = (SMIREQ | SMIREAD | (((u32)phy_id & 0x1f) << 6) | (((u32)location & 0x1f) << 11));
	outl(mii_cmd, mdio_addr);
	udelay(50);

	for(i= 0; i < 1000; i++)
	{
		reg = inl(mdio_addr);
		if(!(reg & SMIREQ))
			break;

		udelay(50);
	}
	
	// Read SMI Register Failed
	if ( i > 999 )
		printk(KERN_INFO "%s: Read SMI Registers failed\n", net_dev->name);
	else
		retval = (u16)((reg & 0xffff0000) >> 16);
	
	return retval;
}

/**
 *	mdio_write - write MII PHY register
 *	@net_dev: the net device to write
 *	@phy_id: the phy address to write
 *	@location: the phy regiester id to write
 *	@value: the register value to write with
 *
 *	Write MII registers with @value through SMI Interface Register
 */

static void mdio_write(struct net_device *net_dev, int phy_id, int location, int value)
{
	long mdio_addr = net_dev->base_addr + SmiIntf;
	int mii_cmd;
	u32 reg;
	int i;

	mii_cmd = (SMIREQ | SMIWRITE | (((u32)phy_id & 0x1f) << 6) | 
	           (((u32)location & 0x1f) << 11) | (((u32)value & 0xffff) << 16));
	outl(mii_cmd, mdio_addr);
	udelay(500);

	for(i= 0; i < 1000; i++)
	{
		reg = inl(mdio_addr);
		if(!(reg & SMIREQ))
			break;

		udelay(50);
	}
	
	// Write SMI Register Failed
	if ( i > 999 )
		printk(KERN_INFO "%s: Write SMI Registers failed\n", net_dev->name);
	
	return;
}


/**
 *	sis190_reset_phy - reset sis190 mii phy.
 *	@net_dev: the net device to write
 *	@phy_addr: default phy address
 *
 *	Some specific phy can't work properly without reset.
 *	This function will be called during initialization.
 */

static u16 sis190_reset_phy(struct net_device *net_dev, int phy_addr)
{
	int i = 0;
	u16 status;

	while (i++ < 2)
		status = mdio_read(net_dev, phy_addr, MII_STATUS);

	mdio_write( net_dev, phy_addr, MII_CONTROL, (MII_CNTL_RESET | MII_CNTL_AUTO | MII_CNTL_RST_AUTO));
	
	return status;
}

/**
 *	sis190_open - open sis190 device
 *	@net_dev: the net device to open
 *
 *	Do some initialization and start net interface.
 *	enable interrupts and set sis190 timer.
 */

static int
sis190_open(struct net_device *net_dev)
{
	struct sis190_private *sis_priv = net_dev->priv;
	long ioaddr = net_dev->base_addr;
	int speed, duplex;
	int ret;

#if COOL_DEBUG
	printk("SiS190 ==> sis190_open !!\n");
#endif

	/* Soft reset the chip. */
	sis190_reset(net_dev);

	if (!sis_priv->autong_complete)
	{
		sis190_read_mode(net_dev, &speed, &duplex);
		sis_priv->speed = speed;
		sis_priv->duplex = duplex;
		sis190_set_mode(net_dev, speed, duplex);
	}
	else
	{
		sis190_set_mode(net_dev, sis_priv->speed, sis_priv->duplex);
	}
	
	ret = request_irq(net_dev->irq, &sis190_interrupt, SA_SHIRQ, net_dev->name, net_dev);

	if (ret)
		return ret;
	
	outl(0, ioaddr + RxMacAddr);
	sis190_init_rxfilter(net_dev);

	sis190_init_tx_ring(net_dev);
	sis190_init_rx_ring(net_dev);

	set_rx_mode(net_dev);

	/* Enable all known interrupts by setting the interrupt mask. */
	outl(INT_MASK, ioaddr + IntMask);

	// Enable Tx and Rx
	outl((inl(ioaddr + TxCtrl) | BIT_0), ioaddr + TxCtrl);
	outl((inl(ioaddr + RxCtrl) | BIT_0 | BIT_4), ioaddr + RxCtrl);

	netif_start_queue(net_dev);

	/* Set the timer to switch to check for link beat and perhaps switch
	   to an alternate media type. */
	init_timer(&sis_priv->timer);
	sis_priv->timer.expires = jiffies + HZ;
	sis_priv->timer.data = (unsigned long)net_dev;
	sis_priv->timer.function = &sis190_timer;
	add_timer(&sis_priv->timer);

	return 0;
}

/**
 *	sis190_init_rxfilter - Initialize the Rx filter
 *	@net_dev: the net device to initialize for
 *
 *	Set receive filter address to our MAC address
 *	and enable packet filtering.
 */

static void
sis190_init_rxfilter (struct net_device * net_dev)
{
	long ioaddr = net_dev->base_addr;
	u16 rfcrSave;
	u32 i;

	rfcrSave = inw(ioaddr + RxMacCtrl);

	/* disable packet filtering before setting filter */
	outl((rfcrSave & ~BIT_8_11), ioaddr + RxMacCtrl);

	/* load MAC addr to filter data register */
	for (i = 0 ; i < 6 ; i++) {
		u8 w;

		w = (u8) *((u8 *)(net_dev->dev_addr)+i);
		outb(w, ioaddr + RxMacAddr + i);
	}

	/* enable packet filtering */
	outw(rfcrSave, ioaddr + RxMacCtrl);
}

/**
 *	sis190_init_tx_ring - Initialize the Tx descriptor ring
 *	@net_dev: the net device to initialize for
 *
 *	Initialize the Tx descriptor ring, 
 */

static void
sis190_init_tx_ring(struct net_device *net_dev)
{
	struct sis190_private *sis_priv = net_dev->priv;
	long ioaddr = net_dev->base_addr;
	int i;

	sis_priv->tx_full = 0;
	sis_priv->dirty_tx = sis_priv->cur_tx = 0;

	for (i = 0; i < NUM_TX_DESC; i++) {
		sis_priv->tx_skbuff[i] = NULL;

		sis_priv->tx_ring[i].PktSize = 0;
		sis_priv->tx_ring[i].cmdsts = 0; 
		sis_priv->tx_ring[i].bufptr = 0;
		
		if(i == (NUM_TX_DESC - 1))
		{
			sis_priv->tx_ring[i].EOD = BIT_31; 
		}
		else
		{
			sis_priv->tx_ring[i].EOD = 0;  
		}

	}

	/* load Transmit Descriptor Register */
	outl(sis_priv->tx_ring_dma, ioaddr + TxBase);
	if (sis190_debug > 2)
		printk(KERN_INFO "%s: TX descriptor register loaded with: %8.8x\n",
		       net_dev->name, inl(ioaddr + TxBase));
}

/**
 *	sis190_init_rx_ring - Initialize the Rx descriptor ring
 *	@net_dev: the net device to initialize for
 *
 *	Initialize the Rx descriptor ring, 
 *	and pre-allocate recevie buffers (socket buffer)
 */

static void 
sis190_init_rx_ring(struct net_device *net_dev)
{
	struct sis190_private *sis_priv = net_dev->priv;
	long ioaddr = net_dev->base_addr;
	int i;

	sis_priv->cur_rx = 0;
	sis_priv->dirty_rx = 0;

	/* init RX descriptor */
	for (i = 0; i < NUM_RX_DESC; i++) {
		sis_priv->rx_skbuff[i] = NULL;

		sis_priv->rx_ring[i].StsSize = 0;
		sis_priv->rx_ring[i].PktInfo = 0xc0000000;
		sis_priv->rx_ring[i].bufptr = 0;

		if(i == (NUM_RX_DESC - 1))
		{
			sis_priv->rx_ring[i].EOD = BIT_31; 
		}
		else
		{
			sis_priv->rx_ring[i].EOD = 0;  
		}	
	}

	/* allocate sock buffers */
	for (i = 0; i < NUM_RX_DESC; i++) {
		struct sk_buff *skb;

		if ((skb = dev_alloc_skb(RX_BUF_SIZE)) == NULL) {
			/* not enough memory for skbuff, this makes a "hole"
			   on the buffer ring, it is not clear how the
			   hardware will react to this kind of degenerated
			   buffer */
			printk(KERN_INFO "%s: Not enough RX skb buffer\n", net_dev->name);
			break;
		}
		skb->dev = net_dev;
		sis_priv->rx_skbuff[i] = skb;
		sis_priv->rx_ring[i].EOD |= (RX_BUF_SIZE & BIT_3_15);
             sis_priv->rx_ring[i].bufptr = pci_map_single(sis_priv->pci_dev,
                        skb->tail, RX_BUF_SIZE, PCI_DMA_FROMDEVICE);
	}
	sis_priv->dirty_rx = (unsigned int) (i - NUM_RX_DESC);

	/* load Receive Descriptor Register */
	outl(sis_priv->rx_ring_dma, ioaddr + RxBase);
	if (sis190_debug > 2)
		printk(KERN_INFO "%s: RX descriptor register loaded with: %8.8x\n",
		       net_dev->name, inl(ioaddr + RxBase));
}

/**
 *	sis190_timer - sis190 timer routine
 *	@data: pointer to sis190 net device
 *
 *	On each timer ticks we check two things, 
 *	link status (ON/OFF) and link mode (10/100/Full/Half)
 */

static void sis190_timer(unsigned long data)
{
	struct net_device *net_dev = (struct net_device *)data;
	struct sis190_private *sis_priv = net_dev->priv;
	long ioaddr;
	struct mii_phy *mii_phy = sis_priv->mii;
	static int next_tick = 5*HZ;
	int speed, duplex;
	u16 status;

	ioaddr = net_dev->base_addr;

	if (!sis_priv->autong_complete){
		int speed, duplex = 0;

		sis190_read_mode(net_dev, &speed, &duplex);
		if (duplex){
			sis190_set_mode(net_dev, speed, duplex);
			netif_start_queue(net_dev);
		}

		sis_priv->timer.expires = jiffies + HZ;
		add_timer(&sis_priv->timer);
		return;
	}

	status = mdio_read(net_dev, sis_priv->cur_phy, MII_STATUS);
	status = mdio_read(net_dev, sis_priv->cur_phy, MII_STATUS);

	/* Link OFF -> ON */
	if (!netif_carrier_ok(net_dev)) {
		/* Search for new PHY */
		status = sis190_default_phy(net_dev);
		mii_phy = sis_priv->mii;

		if (status & MII_STAT_LINK){
			sis190_read_mode(net_dev, &speed, &duplex);
			sis_priv->speed = speed;
			sis_priv->duplex = duplex;
			sis190_set_mode(net_dev, speed, duplex);
			// Set Tx Dealy
			if(sis_priv->RGMII)
			{
				// For Broadcom BCM5461 PHY, set Tx Delay in RGMII mode
				if((mii_phy->phy_id0 == 0x0020) && (mii_phy->phy_id1 == 0x60c1))
				{	
					mdio_write(net_dev, sis_priv->cur_phy, 0x18, 0xf1c7);
					udelay(200);
					mdio_write(net_dev, sis_priv->cur_phy, 0x1c, 0x8c00);
				}
				outl(0x0441, ioaddr + RGDelay);
				outl(0x0440, ioaddr + RGDelay);
			}
			// Start Rx
			outl((inl(ioaddr + RxCtrl) | BIT_4), ioaddr + RxCtrl);
			netif_carrier_on(net_dev);
		}
	}
	/* Link ON -> OFF */
	else {
		if (!(status & MII_STAT_LINK)){
			// Stop Rx
			outl((inl(ioaddr + RxCtrl) & ~BIT_4), ioaddr + RxCtrl);
                	netif_carrier_off(net_dev);
                	printk(KERN_INFO "%s: Media Link Off\n", net_dev->name);
                }
	}

	sis_priv->timer.expires = jiffies + next_tick;
	add_timer(&sis_priv->timer);
}

/**
 *	sis190_set_mode - Set the media mode of mac register.
 *	@ioaddr: the address of the device
 *	@speed : the transmit speed to be determined
 *	@duplex: the duplex mode to be determined
 *
 *	Set the media mode of mac register StationCtrl according to
 *	speed and duplex of phy.
 */

static void sis190_set_mode (struct net_device *net_dev, int speed, int duplex)
{
	struct sis190_private *sis_priv = net_dev->priv;
	struct mii_phy *mii_phy = sis_priv->mii;
	long ioaddr = net_dev->base_addr;
	u32 reg;

	reg = inl(ioaddr + StationCtrl);	
	reg &= ~(BIT_24_27 | BIT_12 | BIT_10_11);

	if(speed == HW_SPEED_1000_MBPS)
	{
		reg |= ((0x3 << 10) | (0x3 << 24) | (0x1 << 26));
	}
	if(speed == HW_SPEED_100_MBPS)
	{
		reg |= ((0x2 << 10) | (0x0 << 24) | (0x1 << 26));
	}
	if(speed == HW_SPEED_10_MBPS)
	{
		reg |= ((0x1 << 10) | (0x0 << 24) | (0x1 << 26));
	}
	if(duplex == FDX_CAPABLE_FULL_SELECTED)
	{
		reg |= BIT_12;
	}
	if(sis_priv->RGMII)
	{
		// For Broadcom BCM5461 PHY, set Tx Delay in RGMII mode
		if((mii_phy->phy_id0 == 0x0020) && (mii_phy->phy_id1 == 0x60c1))
		{
			mdio_write(net_dev, sis_priv->cur_phy, 0x18, 0xf1c7);
			udelay(200);
			mdio_write(net_dev, sis_priv->cur_phy, 0x1c, 0x8c00);
		}

		reg |= (0x3 << 24);
	}
	
	outl(reg, ioaddr + StationCtrl);
}

/**
 *	sis190_read_mode - read media mode for sis190 internal phy
 *	@net_dev: the net device to read mode for
 *	@speed  : the transmit speed to be determined
 *	@duplex : the duplex mode to be determined
 *
 *	The capability of remote end will be put in mii register autorec
 *	after auto-negotiation. Use AND operation to get the upper bound
 *	of speed and duplex between two ends.
 */

static void sis190_read_mode(struct net_device *net_dev, int *speed, int *duplex)
{
	struct sis190_private *sis_priv = net_dev->priv;
	int phy_addr = sis_priv->cur_phy;
	u32 status;
	u16 autoadv, autorec, autoexp, gigadv, gigrec;
	int i = 0;

	while (i++ < 2)
		status = mdio_read(net_dev, phy_addr, MII_STATUS);

	if (!(status & MII_STAT_LINK))
		return;

	/* AutoNegotiate completed */
	autoadv = mdio_read(net_dev, phy_addr, MII_ANADV);
	autorec = mdio_read(net_dev, phy_addr, MII_ANLPAR);
	autoexp = mdio_read(net_dev, phy_addr, MII_ANEXT);
	
	*speed = HW_SPEED_10_MBPS;
	*duplex = FDX_CAPABLE_HALF_SELECTED;

	// Link partner has 1000 Mbps capability
	if((sis_priv->device == 0x191) && (autorec & MII_NWAY_NP) && (autoexp & BIT_1))
	{
		gigadv = mdio_read(net_dev, phy_addr, MII_ANGADV);
		gigrec = mdio_read(net_dev, phy_addr, MII_ANGLPAR);
		status = (gigadv & (gigrec >> 2));
		if(status & BIT_9)
		{
			*speed = HW_SPEED_1000_MBPS;
			*duplex = FDX_CAPABLE_FULL_SELECTED;
		}
		else if (status & BIT_8)
		{
			*speed = HW_SPEED_1000_MBPS;
			*duplex = FDX_CAPABLE_HALF_SELECTED;
		}
	}
	else
	{
		status = autoadv & autorec;
		
		if (status & (MII_NWAY_TX | MII_NWAY_TX_FDX))
			*speed = HW_SPEED_100_MBPS;
		if (status & ( MII_NWAY_TX_FDX | MII_NWAY_T_FDX))
			*duplex = FDX_CAPABLE_FULL_SELECTED;
	}
	
	sis_priv->autong_complete = 1;


	printk(KERN_INFO "%s: Media Link On %d Mbps %s-duplex \n",
	       net_dev->name,
	       *speed,
	       *duplex == FDX_CAPABLE_FULL_SELECTED ?
	       "full" : "half");
	return;
}

/**
 *	sis190_tx_timeout - sis190 transmit timeout routine
 *	@net_dev: the net device to transmit
 *
 *	print transmit timeout status
 *	disable interrupts and do some tasks
 */

static void sis190_tx_timeout(struct net_device *net_dev)
{
	struct sis190_private *sis_priv = net_dev->priv;
	long ioaddr = net_dev->base_addr;
	unsigned long flags;
	int i;
	u32 reg;

#if COOL_DEBUG
	printk("SiS190 ==> sis190_tx_timeout !!\n");
#endif

	printk(KERN_INFO "%s: Transmit timeout, status %8.8x %8.8x \n",
	       net_dev->name, inl(ioaddr + TxCtrl), inl(ioaddr + TxSts));

	/* use spinlock to prevent interrupt handler accessing buffer ring */
	spin_lock_irqsave(&sis_priv->lock, flags);

	/* Disable interrupts by clearing the interrupt mask. */
	outl(0x0000, ioaddr + IntMask);

	// Disable Tx 
	reg = (inl(ioaddr + TxCtrl) & ~(BIT_0 | BIT_4));
	outl(reg, ioaddr + TxCtrl);	
	udelay(50);

	if(inl(ioaddr + TxCtrl) & BIT_0)
		printk(KERN_INFO "%s: Can not disable Tx, status %8.8x %8.8x \n",
		       net_dev->name, inl(ioaddr + TxCtrl), inl(ioaddr + TxSts));	

	/* discard unsent packets */
	sis_priv->dirty_tx = sis_priv->cur_tx = 0;
	for (i = 0; i < NUM_TX_DESC; i++) {
		struct sk_buff *skb = sis_priv->tx_skbuff[i];

		if (skb) {
			pci_unmap_single(sis_priv->pci_dev, 
				sis_priv->tx_ring[i].bufptr, skb->len,
				PCI_DMA_TODEVICE);
			dev_kfree_skb_irq(skb);
			sis_priv->tx_skbuff[i] = NULL;
			sis_priv->stats.tx_dropped++;
		}

		sis_priv->tx_ring[i].PktSize = 0;
		sis_priv->tx_ring[i].cmdsts = 0;
		sis_priv->tx_ring[i].bufptr = 0;
		sis_priv->tx_ring[i].bufptr &= 0x80000000;
	}
	sis_priv->tx_full = 0;
	netif_wake_queue(net_dev);

	net_dev->trans_start = jiffies;

	/* Enable Tx */
	outl((reg | BIT_0), ioaddr + TxCtrl);

	/* Enable all known interrupts by setting the interrupt mask. */
	outl(INT_MASK, ioaddr + IntMask);

	spin_unlock_irqrestore(&sis_priv->lock, flags);
	
	return;
}

/**
 *	sis190_start_xmit - sis190 start transmit routine
 *	@skb: socket buffer pointer to put the data being transmitted
 *	@net_dev: the net device to transmit with
 *
 *	Set the transmit buffer descriptor, 
 *	and write TxStart to enable transmit state machine.
 *	tell upper layer if the buffer is full
 */

static int
sis190_start_xmit(struct sk_buff *skb, struct net_device *net_dev)
{
	struct sis190_private *sis_priv = net_dev->priv;
	long ioaddr = net_dev->base_addr;
	unsigned int  entry;
	unsigned long flags;

#if COOL_DEBUG
	//printk("SiS190 ==> sis190_start_xmit !!\n");
#endif

	/* Don't transmit data before the complete of auto-negotiation */
	if(!sis_priv->autong_complete){
		netif_stop_queue(net_dev);
		return 1;
	}

	spin_lock_irqsave(&sis_priv->lock, flags);

	/* Calculate the next Tx descriptor entry. */
	entry = sis_priv->cur_tx % NUM_TX_DESC;
	sis_priv->tx_skbuff[entry] = skb;

#if COOL_DEBUG
	//printk("sis_priv->cur_tx = %x, sis_priv->dirty_tx = %x\n", sis_priv->cur_tx, sis_priv->dirty_tx);
	//printk("entry = %2.2x, TxDescAddr = %8.8x\n", entry, inl(ioaddr + TxSts));
#endif

	/* set the transmit buffer descriptor and enable Transmit State Machine */
	sis_priv->tx_ring[entry].bufptr = pci_map_single(sis_priv->pci_dev,
		skb->data, skb->len, PCI_DMA_TODEVICE);
	sis_priv->tx_ring[entry].PktSize = (skb->len & 0xffff);
	sis_priv->tx_ring[entry].EOD |= (skb->len & 0xffff);
	sis_priv->tx_ring[entry].cmdsts = (PADEN | CRCEN | DEFEN | THOL3 | TXINT);
	if(sis_priv->duplex == FDX_CAPABLE_HALF_SELECTED)
	{
		sis_priv->tx_ring[entry].cmdsts |= (COLEN | CRSEN | BKFEN);
		if(sis_priv->speed == HW_SPEED_1000_MBPS)
			sis_priv->tx_ring[entry].cmdsts |= (EXTEN | BSTEN);
	}
	sis_priv->tx_ring[entry].cmdsts |= TXOWN;

	outl(BIT_4 | inl(ioaddr + TxCtrl), ioaddr + TxCtrl);

	sis_priv->cur_tx ++;

	if((sis_priv->cur_tx - sis_priv->dirty_tx) >= (NUM_TX_DESC - 4))
	{
		/* dirty_tx is met in the cycle of cur_tx, buffer full */
		printk(KERN_INFO "%s: Tx buffers is full, queue stoped !!\n", net_dev->name);	
		sis_priv->tx_full = 1;
		netif_stop_queue(net_dev);
	}

	spin_unlock_irqrestore(&sis_priv->lock, flags);

	net_dev->trans_start = jiffies;

	if (sis190_debug > 3)
		printk(KERN_INFO "%s: Queued Tx packet at %p size %d "
		       "to slot %d.\n",
		       net_dev->name, skb->data, (int)skb->len, entry);

	return 0;
}

/**
 *	sis190_interrupt - sis190 interrupt handler
 *	@irq: the irq number
 *	@dev_instance: the client data object
 *	@regs: snapshot of processor context
 *
 *	The interrupt handler does all of the Rx thread work, 
 *	and cleans up after the Tx thread
 */

static irqreturn_t sis190_interrupt(int irq, void *dev_instance, struct pt_regs *regs)
{
	struct net_device *net_dev = dev_instance;
	struct sis190_private *sis_priv = net_dev->priv;
	int boguscnt = max_interrupt_work;
	long ioaddr = net_dev->base_addr;
	u32 status, mask;
	unsigned int handled = 0;

	spin_lock (&sis_priv->lock);
	
	// Disable interrupts
	outl(0, ioaddr + IntMask);

	do {
		status = inl(ioaddr + IntSrc);
		mask = INT_MASK;

		if ((status & mask) == 0)
		{
			/* nothing intresting happened */
			break;
		}
		handled = 1;
		outl(status, ioaddr + IntSrc);

		if (status & BIT_0)
			printk(KERN_INFO "%s: Tx Halt interrupt issued !!\n", net_dev->name);

		if (status & BIT_1)
			printk(KERN_INFO "%s: Rx Halt interrupt issued !!\n", net_dev->name);

		if (status & (BIT_2 | BIT_3))
			/* Tx interrupt */
			sis190_finish_xmit(net_dev);

		if (status & (BIT_6 | BIT_7))
			/* Rx interrupt */
			sis190_rx(net_dev);		

		if (status & BIT_16)
			printk(KERN_INFO "%s: Link changed interrupt issued !!\n", net_dev->name);


		if (--boguscnt < 0) {
			printk(KERN_INFO "%s: Too much work at interrupt, "
			       "interrupt status = %#8.8x.\n",
			       net_dev->name, status);
			break;
		}
	} while (1);

	// Enable interrupts
	outl(INT_MASK, ioaddr + IntMask);
	spin_unlock (&sis_priv->lock);
	return IRQ_RETVAL(handled);
}

/**
 *	sis190_rx - sis190 receive routine
 *	@net_dev: the net device which receives data
 *
 *	Process receive interrupt events, 
 *	put buffer to higher layer and refill buffer pool
 *	Note: This fucntion is called by interrupt handler, 
 *	don't do "too much" work here
 */

static int sis190_rx(struct net_device *net_dev)
{
	struct sis190_private *sis_priv = net_dev->priv;
	long ioaddr = net_dev->base_addr;
	unsigned int entry = sis_priv->cur_rx % NUM_RX_DESC;
	u32 descount;
	u32 rx_status = sis_priv->rx_ring[entry].StsSize;
	u32 rx_info = sis_priv->rx_ring[entry].PktInfo;

	if (sis190_debug > 3)
		printk(KERN_INFO "sis190_rx, cur_rx:%4.4d, dirty_rx:%4.4d "
		       "status:0x%8.8x\n",
		       sis_priv->cur_rx, sis_priv->dirty_rx, rx_status);

	while (!(rx_info & RXOWN)) {
		unsigned int rx_size;

		rx_size = (rx_status & 0xffff);
		descount = ((rx_status & BIT_24_30) >> 24);
		if(descount > 1)
			printk(KERN_INFO "%s: Rx Desc Count %d in a packet.\n", net_dev->name, descount);		

		if ((rx_status & (COLON|NIBON|OVRUN|MIIER|LIMIT|SHORT|ABORT)) ||
		    !(rx_status & CRCOK))
		{
			/* corrupted packet received */
			if (sis190_debug > 3)
				printk(KERN_INFO "%s: Corrupted packet "
				       "received, buffer status = 0x%8.8x.\n",
				       net_dev->name, rx_status);
			sis_priv->stats.rx_errors++;
			if (rx_status & OVRUN)
				sis_priv->stats.rx_over_errors++;
			if (rx_status & (SHORT|LIMIT))
				sis_priv->stats.rx_length_errors++;
			if (rx_status & (MIIER | NIBON | COLON))
				sis_priv->stats.rx_frame_errors++;
			if (!(rx_status & CRCOK)) 
				sis_priv->stats.rx_crc_errors++;
			/* reset buffer descriptor state */
			sis_priv->rx_ring[entry].StsSize = 0;
			sis_priv->rx_ring[entry].PktInfo = 0xc0000000;
		} else {
			struct sk_buff * skb;

			/* This situation should never happen, but due to
			   some unknow bugs, it is possible that
			   we are working on NULL sk_buff :-( */
			if (sis_priv->rx_skbuff[entry] == NULL) {
				printk(KERN_INFO "%s: NULL pointer " 
				       "encountered in Rx ring, skipping\n",
				       net_dev->name);
				break;
			}

			pci_unmap_single(sis_priv->pci_dev, 
				sis_priv->rx_ring[entry].bufptr, RX_BUF_SIZE, 
				PCI_DMA_FROMDEVICE);
			/* give the socket buffer to upper layers */
			skb = sis_priv->rx_skbuff[entry];
			skb_put(skb, rx_size);
			skb->protocol = eth_type_trans(skb, net_dev);
			netif_rx(skb);

			/* some network statistics */
			if ((rx_status & BCAST) == MCAST)
				sis_priv->stats.multicast++;
			net_dev->last_rx = jiffies;
			sis_priv->stats.rx_bytes += rx_size;
			sis_priv->stats.rx_packets++;

			/* refill the Rx buffer, what if there is not enought memory for
			   new socket buffer ?? */
			if ((skb = dev_alloc_skb(RX_BUF_SIZE)) == NULL) {
				/* not enough memory for skbuff, this makes a "hole"
				   on the buffer ring, it is not clear how the
				   hardware will react to this kind of degenerated
				   buffer */
				printk(KERN_INFO "%s: Memory squeeze,"
				       "deferring packet.\n",
				       net_dev->name);
				sis_priv->rx_skbuff[entry] = NULL;
				/* reset buffer descriptor state */
				sis_priv->rx_ring[entry].StsSize = 0;
				sis_priv->rx_ring[entry].PktInfo = 0;
				sis_priv->rx_ring[entry].bufptr = 0;
				sis_priv->stats.rx_dropped++;
				break;
			}
			skb->dev = net_dev;
			sis_priv->rx_skbuff[entry] = skb;
			sis_priv->rx_ring[entry].StsSize = 0;
			sis_priv->rx_ring[entry].PktInfo = 0xc0000000;
                	sis_priv->rx_ring[entry].bufptr = 
				pci_map_single(sis_priv->pci_dev, skb->tail, 
					RX_BUF_SIZE, PCI_DMA_FROMDEVICE);
			sis_priv->dirty_rx++;
		}
		sis_priv->cur_rx++;
		entry = sis_priv->cur_rx % NUM_RX_DESC;
		rx_status = sis_priv->rx_ring[entry].StsSize;
		rx_info = sis_priv->rx_ring[entry].PktInfo;
	} // while

	/* refill the Rx buffer, what if the rate of refilling is slower than 
	   consuming ?? */
	for (;sis_priv->cur_rx - sis_priv->dirty_rx > 0; sis_priv->dirty_rx++) {
		struct sk_buff *skb;

		entry = sis_priv->dirty_rx % NUM_RX_DESC;

		if (sis_priv->rx_skbuff[entry] == NULL) {
			if ((skb = dev_alloc_skb(RX_BUF_SIZE)) == NULL) {
				/* not enough memory for skbuff, this makes a "hole"
				   on the buffer ring, it is not clear how the 
				   hardware will react to this kind of degenerated 
				   buffer */
				printk(KERN_INFO "%s: Memory squeeze,"
				       "deferring packet.\n",
				       net_dev->name);
				sis_priv->stats.rx_dropped++;
				break;
			}
			skb->dev = net_dev;
			sis_priv->rx_skbuff[entry] = skb;
                	sis_priv->rx_ring[entry].bufptr =
				pci_map_single(sis_priv->pci_dev, skb->tail,
					RX_BUF_SIZE, PCI_DMA_FROMDEVICE);
		}
	}
	/* re-enable the potentially idle receive state matchine */
	outl(BIT_4 | inl(ioaddr + RxCtrl), ioaddr + RxCtrl );

	return 0;
}

/**
 *	sis190_finish_xmit - finish up transmission of packets
 *	@net_dev: the net device to be transmitted on
 *
 *	Check for error condition and free socket buffer etc 
 *	schedule for more transmission as needed
 *	Note: This fucntion is called by interrupt handler, 
 *	don't do "too much" work here
 */

static void sis190_finish_xmit (struct net_device *net_dev)
{
	struct sis190_private *sis_priv = net_dev->priv;

	for (; sis_priv->dirty_tx != sis_priv->cur_tx; sis_priv->dirty_tx++) {
		struct sk_buff *skb;
		unsigned int entry;
		u32 tx_status;
		u32 pkt_size;

		entry = sis_priv->dirty_tx % NUM_TX_DESC;
		tx_status = sis_priv->tx_ring[entry].cmdsts;
		pkt_size = (sis_priv->tx_ring[entry].EOD & 0xffff);

		if (tx_status & TXOWN) {
			/* The packet is not transmitted yet (owned by hardware) !
			   Note: the interrupt is generated only when Tx Machine
			   is idle, so this is an almost impossible case */
			break;
		}

		if (tx_status & BIT_16_19) {
			/* packet unsuccessfully transmitted */
			if (sis190_debug > 3)
				printk(KERN_INFO "%s: Transmit "
				       "error, Tx status %8.8x.\n",
				       net_dev->name, tx_status);
			sis_priv->stats.tx_errors++;
			if (tx_status & BIT_17)
				sis_priv->stats.tx_fifo_errors++;
			if (tx_status & BIT_18)
				sis_priv->stats.tx_aborted_errors++;
			if (tx_status & BIT_16)
				sis_priv->stats.tx_carrier_errors++;
			if (tx_status & BIT_19)
				sis_priv->stats.tx_window_errors++;
		} else {
			/* packet successfully transmitted */
			sis_priv->stats.collisions += ((tx_status & 0xffff) - 1);
			sis_priv->stats.tx_bytes += pkt_size;
			sis_priv->stats.tx_packets++;
		}
		/* Free the original skb. */
		skb = sis_priv->tx_skbuff[entry];
		pci_unmap_single(sis_priv->pci_dev, 
			sis_priv->tx_ring[entry].bufptr, skb->len,
			PCI_DMA_TODEVICE);
		dev_kfree_skb_irq(skb);
		sis_priv->tx_skbuff[entry] = NULL;
		sis_priv->tx_ring[entry].bufptr = 0;
		sis_priv->tx_ring[entry].cmdsts = 0;
		sis_priv->tx_ring[entry].PktSize = 0;
		sis_priv->tx_ring[entry].EOD &= 0x80000000;
	}

	if (sis_priv->tx_full && netif_queue_stopped(net_dev) &&
	    sis_priv->cur_tx - sis_priv->dirty_tx < NUM_TX_DESC - 4) {
		/* The ring is no longer full, clear tx_full and schedule more transmission
		   by netif_wake_queue(net_dev) */
		printk(KERN_INFO "%s: Some Tx buffers are released, queue restarted !!\n", net_dev->name);	
		sis_priv->tx_full = 0;
		netif_wake_queue (net_dev);
	}
}

/**
 *	sis190_close - close sis190 device 
 *	@net_dev: the net device to be closed
 *
 *	Disable interrupts, stop the Tx and Rx Status Machine 
 *	free Tx and RX socket buffer
 */

static int
sis190_close(struct net_device *net_dev)
{
	long ioaddr = net_dev->base_addr;
	struct sis190_private *sis_priv = net_dev->priv;
	struct sk_buff *skb;
	int i;
	u32 ulvalue;

#if COOL_DEBUG
	printk("SiS190 ==> sis190_close !!\n");
#endif
	netif_stop_queue(net_dev);

	/* Disable interrupts by clearing the interrupt mask. */
	outl(0x0000, ioaddr + IntMask);
	udelay(2000);

	/* Stop the chip's Tx and Rx Status Machine */
	ulvalue = inl(ioaddr + IntCtrl) | BIT_15;
	outl(ulvalue, ioaddr + IntCtrl);
	udelay(50);
	ulvalue &= ~BIT_15;
	outl(ulvalue, ioaddr + IntCtrl);	

	del_timer(&sis_priv->timer);

	free_irq(net_dev->irq, net_dev);

	/* Free Tx and RX skbuff */
	for (i = 0; i < NUM_RX_DESC; i++) {
		skb = sis_priv->rx_skbuff[i];
		if (skb) {
			pci_unmap_single(sis_priv->pci_dev, 
				sis_priv->rx_ring[i].bufptr,
				RX_BUF_SIZE, PCI_DMA_FROMDEVICE);
			dev_kfree_skb(skb);
			sis_priv->rx_skbuff[i] = NULL;
		}
	}
	for (i = 0; i < NUM_TX_DESC; i++) {
		skb = sis_priv->tx_skbuff[i];
		if (skb) {
			pci_unmap_single(sis_priv->pci_dev, 
				sis_priv->tx_ring[i].bufptr, skb->len,
				PCI_DMA_TODEVICE);
			dev_kfree_skb(skb);
			sis_priv->tx_skbuff[i] = NULL;
		}
	}

	/* Green! Put the chip in low-power mode. */

	return 0;
}

/**
 *	sis190_get_drvinfo - Return information about driver
 *	@net_dev: the net device to probe
 *	@info: container for info returned
 *
 *	Process ethtool command such as "ehtool -i" to show information
 */
 
static void sis190_get_drvinfo(struct net_device *net_dev,
			       struct ethtool_drvinfo *info)
{
 	struct sis190_private *sis_priv = net_dev->priv;

	strcpy (info->driver, SIS190_MODULE_NAME);
	strcpy (info->version, SIS190_DRV_VERSION);
	strcpy (info->bus_info, pci_name(sis_priv->pci_dev));
}

static struct ethtool_ops sis190_ethtool_ops = {
	.get_drvinfo =		sis190_get_drvinfo,
};

/**
 *	mii_ioctl - process MII i/o control command 
 *	@net_dev: the net device to command for
 *	@rq: parameter for command
 *	@cmd: the i/o command
 *
 *	Process MII command like read/write MII register
 */

static int mii_ioctl(struct net_device *net_dev, struct ifreq *rq, int cmd)
{
	struct sis190_private *sis_priv = net_dev->priv;
	struct mii_ioctl_data *data = if_mii(rq);

#if COOL_DEBUG
	printk("SiS190 ==> mii_ioctl !!\n");
#endif

	switch(cmd) {
	case SIOCGMIIPHY:		/* Get address of MII PHY in use. */
	#if COOL_DEBUG		
		//printk("Get Address of MII PHY\n");
	#endif
		data->phy_id = sis_priv->mii->phy_addr;
		return 0;

	case SIOCGMIIREG:		/* Read MII PHY register. */		
		data->val_out = mdio_read(net_dev, (data->phy_id & 0x1f), (data->reg_num & 0x1f));
	#if COOL_DEBUG
		//printk("Read PHY register, Phy = %d, Reg = %d, Data = %x\n", data->phy_id, data->reg_num, data->val_out);
	#endif
		return 0;

	case SIOCSMIIREG:		/* Write MII PHY register. */
		if (!capable(CAP_NET_ADMIN))
			return -EPERM;
	#if COOL_DEBUG
		//printk("Write PHY register, Phy = %d, Reg = %d, Value = %x\n", data->phy_id, data->reg_num, data->val_in);
	#endif
		mdio_write(net_dev, data->phy_id & 0x1f, data->reg_num & 0x1f, data->val_in);
		return 0;
	default:
		return -EOPNOTSUPP;
	}
}

/**
 *	sis190_get_stats - Get sis190 read/write statistics 
 *	@net_dev: the net device to get statistics for
 *
 *	get tx/rx statistics for sis190
 */

static struct net_device_stats *
sis190_get_stats(struct net_device *net_dev)
{
#if COOL_DEBUG
	//printk("SiS190 ==> sis190_get_stats !!\n");
#endif	
	struct sis190_private *sis_priv = net_dev->priv;

	return &sis_priv->stats;
}

/**
 *	sis190_mcast_bitnr - compute hashtable index 
 *	@addr: multicast address
 *
 *	SiS 190 uses the last sigificant 6 bits to index a 64 bits multicast
 *	hash table.
 */

static inline u16 sis190_mcast_bitnr(u8 *addr)
{

	u32 crc = ether_crc(6, addr);

	return ((u16)(crc & BIT_0_5));
}

/**
 *	set_rx_mode - Set SiS190 receive mode 
 *	@net_dev: the net device to be set
 *
 *	Set SiS190 receive mode for promiscuous, multicast, or broadcast mode.
 *	And set the appropriate multicast filter.
 *	Multicast hash table has the size of 64 bits for SiS190.
 */

static void set_rx_mode(struct net_device *net_dev)
{
	long ioaddr = net_dev->base_addr;
	u32 mc_filter[2] = {0};	/* 64 bits multicast hash table */
	int i;
	u16 rx_mode;

#if COOL_DEBUG
	printk("SiS190 ==> set_rx_mode !!\n");
#endif
	outw((inw(ioaddr + RxMacCtrl) & ~BIT_8_11), ioaddr + RxMacCtrl);

	if (net_dev->flags & IFF_PROMISC) {
		/* Accept any kinds of packets */
		rx_mode = BIT_8_11;
		for (i = 0; i < 2; i++)
			mc_filter[i] = 0xffffffff;
	} else if ((net_dev->mc_count > multicast_filter_limit) ||
		   (net_dev->flags & IFF_ALLMULTI)) {
		/* too many multicast addresses or accept all multicast packet */
		rx_mode = BIT_11 | BIT_10 | BIT_9;
		for (i = 0; i < 2; i++)
			mc_filter[i] = 0xffffffff;
	} else {
		/* Accept Broadcast packet, destination address matchs our MAC address,
		   use Receive Filter to reject unwanted MCAST packet */
		struct dev_mc_list *mclist;
		rx_mode = BIT_11 | BIT_10 | BIT_9;
		for (i = 0, mclist = net_dev->mc_list; mclist && i < net_dev->mc_count;
		     i++, mclist = mclist->next) {
			u16 bit_nr =
				sis190_mcast_bitnr(mclist->dmi_addr);
			if(bit_nr < 0x20)
			{
				mc_filter[0] |= (1 << bit_nr);
			}
			else
			{
				mc_filter[1] |= (1 << (bit_nr - 0x20));
			}
		}
	}

	/* update Multicast Hash Table in Receive Filter */
	outl(mc_filter[0], ioaddr + RxHashTbl);
	outl(mc_filter[1], ioaddr + RxHashTbl + 4);	

	outw( (inw(ioaddr + RxMacCtrl) | rx_mode), ioaddr + RxMacCtrl);

	/* sis190 is capatable of looping back packet at MAC level for debugging purpose */
	if (net_dev->flags & IFF_LOOPBACK) {
		u32 txcr_saved, rxcr_saved;
		/* We must disable Tx/Rx before setting loopback mode */
		txcr_saved = inl(ioaddr + TxCtrl);
		outl((txcr_saved & ~BIT_0), ioaddr + TxMacCtrl);
		rxcr_saved = inl(ioaddr + RxCtrl);
		outl((rxcr_saved & ~BIT_0), ioaddr + RxMacCtrl);
		/* enable loopback */
		outl(inl(ioaddr + StationCtrl) | BIT_31, ioaddr + StationCtrl);
		/* restore Tx/Rx Ctrl registers */
		outl(txcr_saved, ioaddr + TxMacCtrl);
		outl(rxcr_saved, ioaddr + RxMacCtrl);
	}

	return;
}

/**
 *	sis190_reset - Reset sis190 MAC 
 *	@net_dev: the net device to reset
 *
 *	Reset sis190 MAC and wait until finished
 *	Initialize all MAC registers.
 */

static void sis190_reset(struct net_device *net_dev)
{
	struct sis190_private *sis_priv = net_dev->priv;
	long ioaddr = net_dev->base_addr;

	// Reset Tx & Rx
	outl(0x00001c00, ioaddr + TxCtrl);
	outl(0x001e1c00, ioaddr + RxCtrl);
	outl(BIT_15, ioaddr + IntCtrl);
	udelay(100);
	outl(0, ioaddr + IntCtrl);

	// Disable Interrupt
	outl(0, ioaddr + IntMask);
	outl(0xffffffff, ioaddr + IntSrc);

	// Give initial value for all MAC registers
	outl(0, ioaddr + TxBase);
	outl(0, ioaddr + rsv0);
	outl(0, ioaddr + RxBase);
	outl(0, ioaddr + rsv1);
	outl(0xffc00000, ioaddr + PowCtrl);
	outl(0, ioaddr + rsv2);
	if(sis_priv->RGMII)
		outl(0x04008001, ioaddr + StationCtrl);
	else
		outl(0x04000001, ioaddr + StationCtrl);
	outl(0, ioaddr + GIoCR);
	outl(0, ioaddr + GIoCtrl);
	outl(0x00002364, ioaddr + TxMacCtrl);
	outl(0x0000000f, ioaddr + TxLimit);
	outl(0, ioaddr + RGDelay);
	outl(0, ioaddr + rsv3);
	outw(0x0252, ioaddr + RxMacCtrl);
	outl(0, ioaddr + RxHashTbl);
	outl(0, ioaddr + RxHashTbl + 4);
	outl(0x80ff0000, ioaddr + RxWolCtrl);
	outl(0x80ff0000, ioaddr + RxWolData);
	outl(0x0, ioaddr + RxMpsCtrl);
	outl(0x0, ioaddr + rsv4);
}

/**
 *	sis190_remove - Remove sis190 device 
 *	@pci_dev: the pci device to be removed
 *
 *	remove and release SiS190 net device
 */

static void __devexit sis190_remove(struct pci_dev *pci_dev)
{
	struct net_device *net_dev = pci_get_drvdata(pci_dev);
	struct sis190_private * sis_priv = net_dev->priv;
	struct mii_phy *phy = NULL;

#if COOL_DEBUG
	printk("SiS190 ==> sis190_remove !!\n");
#endif

	while (sis_priv->first_mii) {
		phy = sis_priv->first_mii;
		sis_priv->first_mii = phy->next;
		kfree(phy);
	}

	pci_free_consistent(pci_dev, RX_TOTAL_SIZE + 15, sis_priv->org_rx_ring,
		sis_priv->org_rx_ring_dma);
	pci_free_consistent(pci_dev, TX_TOTAL_SIZE + 15, sis_priv->org_tx_ring,
		sis_priv->org_tx_ring_dma);
	unregister_netdev(net_dev);
	free_netdev(net_dev);
	pci_release_regions(pci_dev);
	pci_set_drvdata(pci_dev, NULL);
}

static struct pci_driver sis190_pci_driver = {
	.name		= SIS190_MODULE_NAME,
	.id_table	= sis190_pci_tbl,
	.probe		= sis190_probe,
	.remove	= __devexit_p(sis190_remove),
};

static int __init sis190_init_module(void)
{
#if COOL_DEBUG
	printk("SiS190 ==> sis190_init_module !!\n");
#endif

/* when a module, this is printed whether or not devices are found in probe */
#ifdef MODULE
	printk(version);
#endif

	return pci_module_init(&sis190_pci_driver);
}

static void __exit sis190_cleanup_module(void)
{
#if COOL_DEBUG
	printk("SiS190 ==> sis190_cleanup_module !!\n");
#endif

	pci_unregister_driver(&sis190_pci_driver);
}

module_init(sis190_init_module);
module_exit(sis190_cleanup_module);

