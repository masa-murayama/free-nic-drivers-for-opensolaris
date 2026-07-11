/* sis900.h Definitions for SiS ethernet controllers including 7014/7016 and 900
 * Copyright 1999 Silicon Integrated System Corporation
 * References:
 * SiS 7016 Fast Ethernet PCI Bus 10/100 Mbps LAN Controller with OnNow Support,
 *	preliminary Rev. 1.0 Jan. 14, 1998
 * SiS 900 Fast Ethernet PCI Bus 10/100 Mbps LAN Single Chip with OnNow Support,
 *	preliminary Rev. 1.0 Nov. 10, 1998
 * SiS 7014 Single Chip 100BASE-TX/10BASE-T Physical Layer Solution,
 *	preliminary Rev. 1.0 Jan. 18, 1998
 * http://www.sis.com.tw/support/databook.htm
 */

/*
 * SiS 7016 and SiS 900 ethernet controller registers
 */

/* The I/O extent, SiS 900 needs 256 bytes of io address */
#define SIS900_TOTAL_SIZE 0x100

/* Symbolic offsets to registers. */
/* sis900_registers */
#define	cr		0x0	/* Command Register */
#define	cfg		0x4	/* Configuration Register */
#define	mear		0x8	/* EEPROM Access Register */
#define	ptscr		0xc	/* PCI Test Control Register */
#define	isr		0x10	/* Interrupt Status Register */
#define	imr		0x14	/* Interrupt Mask Register */
#define	ier		0x18	/* Interrupt Enable Register */
#define	epar		0x18	/* Enhanced PHY Access Register */
#define	txdp		0x20	/* Transmit DescriptorPointer Register */
#define	txcfg		0x24	/* Transmit Configuration Register */
#define	rxdp		0x30	/* Receive Descriptor Pointer Register */
#define	rxcfg		0x34	/* Receive Configuration Register */
#define	flctrl		0x38	/* Flow Control Register */
#define	rxlen		0x3c	/* Receive Packet Length Register */
#define	rfcr		0x48	/* Receive Filter Control Register */
#define	rfdr		0x4C	/* Receive Filter Data Register */
#define	pmctrl		0xB0	/* Power Management Control Register */
#define	pmer		0xB4	/* Power Management Wake-up Event Register */

/* Symbolic names for bits in various registers */
/* sis900_command_register_bits */
#define	RELOAD		0x00000400
#define	RESET		0x00000100
#define	SWI 		0x00000080
#define	RxRESET		0x00000020
#define	TxRESET		0x00000010
#define	RxDIS		0x00000008
#define	RxENA		0x00000004
#define	TxDIS		0x00000002
#define	TxENA		0x00000001

#define	CR_BITS	\
	"\020"		\
	"\013Reload"	\
	"\011Reset"	\
	"\010SWI"	\
	"\006RxReset"	\
	"\005TxReset"	\
	"\004RxDis"	\
	"\003RxEna"	\
	"\002TxDis"	\
	"\001TxEna"

/* sis900_configuration_register_bits */
#define	DESCRFMT	0x00000100 /* 7016 specific */
#define	REQALG		0x00000080
#define	SB		0x00000040
#define	POW		0x00000020
#define	EXD		0x00000010 
#define	PESEL		0x00000008
#define	LPM		0x00000004
#define	BEM		0x00000001
	/* 635 & 900B Specific */
#define	RND_CNT		0x00000400
#define	FAIR_BACKOFF	0x00000200
#define	EDB_MASTER_EN	0x00002000

/* sis900_eeprom_access_reigster_bits */
#define	MDC		0x00000040
#define	MDDIR		0x00000020
#define	MDIO		0x00000010 /* 7016 specific */ 
#define	EECS		0x00000008
#define	EECLK		0x00000004
#define	EEDO		0x00000002
#define	EEDI		0x00000001

/* sis900_interrupt_register_bits */
#define	WKEVT		0x10000000
#define	TxPAUSEEND	0x08000000
#define	TxPAUSE		0x04000000
#define	TxRCMP		0x02000000
#define	RxRCMP		0x01000000
#define	DPERR		0x00800000
#define	SSERR		0x00400000
#define	RMABT		0x00200000
#define	RTABT		0x00100000
#define	RxSOVR		0x00010000
#define	HIBERR		0x00008000
#define	SWINT		0x00001000
#define	MIBINT		0x00000800
#define	TxURN		0x00000400
#define	TxIDLE		0x00000200
#define	TxERR		0x00000100
#define	TxDESC		0x00000080
#define	TxOK		0x00000040
#define	RxORN		0x00000020
#define	RxIDLE		0x00000010
#define	RxEARLY		0x00000008
#define	RxERR		0x00000004
#define	RxDESC		0x00000002
#define	RxOK		0x00000001

#define	INTR_BITS	\
	"\020"		\
	"\035WKEVT"	\
	"\034TxPAUSEEND"	\
	"\033TxPAUSE"	\
	"\032TxRCMP"	\
	"\031RxRCMP"	\
	"\030DPErr"	\
	"\027SSErr"	\
	"\026RMAbt"	\
	"\025RTAbt"	\
	"\021RxSOVR"	\
	"\020HIBErr"	\
	"\015SWINT"	\
	"\014MIBINT"	\
	"\013TxUrn"	\
	"\012TxIdle"	\
	"\011TxErr"	\
	"\010TxDesc"	\
	"\007TxOk"	\
	"\006RxORN"	\
	"\005RxIdle"	\
	"\004RxEarly"	\
	"\003RxErr"	\
	"\002RxDesc"	\
	"\001RxOk"

/* sis900_interrupt_enable_reigster_bits */
#define	IE		0x00000001

/* maximum dma burst fro transmission and receive*/
#define	MAX_DMA_RANGE	7	/* actually 0 means MAXIMUM !! */
#define	TxMXDMA_shift	20
#define	RxMXDMA_shift	20

/* sis900_tx_rx_dma */
#define	DMA_BURST_512	0
#define	DMA_BURST_64	5

/* transmit FIFO threshholds */
#define TX_FILL_THRESH	16	/* 1/4 FIFO size (512byte) */
#define TxFILLT_shift  	8
#define TxDRNT_shift   	0
#define TxDRNT_100     	48	/* 3/4 FIFO size (1536byte) */
#define TxDRNT_10	16 	/* 1/4 FIFO size (512byte) */

/* sis900_transmit_config_register_bits */
#define	TxCSI		0x80000000
#define	TxHBI		0x40000000
#define	TxMLB		0x20000000
#define	TxATP		0x10000000
#define	TxIFG		0x0C000000
#define	TxFILLT		0x00003F00
#define	TxDRNT		0x0000003F

/* recevie FIFO thresholds */
#define	RxDRNT_shift	1
#define	RxDRNT_100	16	/* 1/2 FIFO size */
#define	RxDRNT_10	24 	/* 3/4 FIFO size */

/* sis900_reveive_config_register_bits */
#define	RxAEP		0x80000000
#define	RxARP		0x40000000
#define	RxATX		0x10000000
#define	RxAJAB		0x08000000
#define	RxDRNT		0x0000007F

#define	RFAA_shift	28
#define	RFADDR_shift	16

/* sis900_receive_filter_control_register_bits */
#define	RFEN		0x80000000
#define	RFAAB		0x40000000
#define	RFAAM		0x20000000
#define	RFAAP		0x10000000
#define	RFPromiscuous	(RFAAB|RFAAM|RFAAP)

/* sis900_reveive_filter_data_mask */
#define	RFDAT		0x0000FFFF

/* EEPROM Addresses */
/* sis900_eeprom_address */
#define	EEPROMSignature	0x00
#define	EEPROMVendorID	0x02
#define	EEPROMDeviceID	0x03
#define	EEPROMMACAddr	0x08
#define	EEPROMChecksum	0x0b

/* The EEPROM commands include the alway-set leading bit. Refer to NM93Cxx datasheet */
/* sis900_eeprom_command */
#define	EEread		0x0180
#define	EEwrite		0x0140
#define	EEerase 	0x01C0 
#define	EEwriteEnable	0x0130
#define	EEwriteDisable	0x0100
#define	EEeraseAll	0x0120
#define	EEwriteAll	0x0110 
#define	EEaddrMask	0x013F
#define	EEcmdShift	16

/* Manamgement Data I/O (mdio) frame */
#define MIIread         0x6000
#define MIIwrite        0x5002
#define MIIpmdShift     7
#define MIIregShift     2
#define MIIcmdLen       16
#define MIIcmdShift     16

/* Buffer Descriptor Status*/
#define	OWN		0x80000000
#define	MORE		0x40000000
#define	INTR		0x20000000
#define	SUPCRC		0x10000000
#define	INCCRC		0x10000000
#define	OK		0x08000000
#define	DSIZE		0x00000fff

/* Status for TX Buffers */
#define	ABORT		0x04000000
#define	UNDERRUN	0x02000000
#define	NOCARRIER	0x01000000
#define	DEFERD		0x00800000
#define	EXCDEFER	0x00400000
#define	OWCOLL		0x00200000
#define	EXCCOLL		0x00100000
#define	COLCNT		0x000f0000

#define	TXSTAT_BITS	\
	"\020"		\
	"\040Own"	\
	"\037More"	\
	"\036Intr"	\
	"\035SupCrc"	\
	"\034Ok"	\
	"\033Abort"	\
	"\032UnderRun"	\
	"\031NoCarrier"	\
	"\030Deferd"	\
	"\027ExcDefer"	\
	"\026OWColl"	\
	"\025ExcColl"

/* Status for RX Buffers */
#define	OVERRUN		0x02000000
#define	DEST		0x00800000
#define	BCAST		0x01800000
#define	MCAST		0x01000000
#define	UNIMATCH	0x00800000
#define	TOOLONG		0x00400000
#define	RUNT		0x00200000
#define	RXISERR		0x00100000
#define	CRCERR		0x00080000
#define	FAERR		0x00040000
#define	LOOPBK		0x00020000
#define	RXCOL		0x00010000

#define	RXSTAT_BITS	\
	"\020"		\
	"\040Own"	\
	"\037More"	\
	"\036Intr"	\
	"\035IncCrc"	\
	"\034Ok"	\
	"\032OverRun"	\
	"\031MCast"	\
	"\030UniMatch"	\
	"\027TooLong"	\
	"\026Runt"	\
	"\025RxISErr"	\
	"\024CrcErr"	\
	"\023FaErr"	\
	"\022LoopBk"	\
	"\021RxCol"

/* MII register offsets */
#define	MII_CONTROL	0x0000
#define	MII_STATUS	0x0001
#define	MII_PHY_ID0	0x0002
#define	MII_PHY_ID1	0x0003
#define	MII_ANADV	0x0004
#define	MII_ANLPAR	0x0005
#define	MII_ANEXT	0x0006

/* mii registers specific to SiS 900 */
#define	MII_CONFIG1	0x0010
#define	MII_CONFIG2	0x0011
#define	MII_STSOUT	0x0012
#define	MII_MASK	0x0013
#define	MII_RESV	0x0014

/* mii registers specific to ICS 1893 */
#define	MII_EXTCTRL	0x0010
#define	MII_QPDSTS	0x0011
#define	MII_10BTOP	0x0012
#define	MII_EXTCTRL2	0x0013

/* mii registers specific to AMD 79C901 */
/* amd_mii_registers */
#define	MII_STATUS_SUMMARY	0x0018

/* MII Control register bit definitions. */
#define	MII_CNTL_FDX		0x0100
#define	MII_CNTL_RST_AUTO	0x0200 
#define	MII_CNTL_ISOLATE	0x0400
#define	MII_CNTL_PWRDWN		0x0800
#define	MII_CNTL_AUTO		0x1000
#define	MII_CNTL_SPEED		0x2000
#define	MII_CNTL_LPBK		0x4000
#define	MII_CNTL_RESET		0x8000

/* MII Status register bit  */
#define	MII_STAT_EXT		0x0001
#define	MII_STAT_JAB		0x0002 
#define	MII_STAT_LINK		0x0004
#define	MII_STAT_CAN_AUTO	0x0008 
#define	MII_STAT_FAULT		0x0010
#define	MII_STAT_AUTO_DONE	0x0020
#define	MII_STAT_CAN_T		0x0800
#define	MII_STAT_CAN_T_FDX	0x1000
#define	MII_STAT_CAN_TX		0x2000
#define	MII_STAT_CAN_TX_FDX	0x4000
#define	MII_STAT_CAN_T4		0x8000

#define	MII_ID1_OUI_LO		0xFC00	/* low bits of OUI mask */
#define	MII_ID1_MODEL		0x03F0	/* model number */
#define	MII_ID1_REV		0x000F	/* model number */

/* MII NWAY Register Bits ...
   valid for the ANAR (Auto-Negotiation Advertisement) and
   ANLPAR (Auto-Negotiation Link Partner) registers */
/* mii_nway_register_bits */
#define	MII_NWAY_NODE_SEL	0x001f
#define	MII_NWAY_CSMA_CD	0x0001
#define	MII_NWAY_T		0x0020
#define	MII_NWAY_T_FDX		0x0040
#define	MII_NWAY_TX		0x0080
#define	MII_NWAY_TX_FDX		0x0100
#define	MII_NWAY_T4		0x0200
#define	MII_NWAY_PAUSE		0x0400
#define	MII_NWAY_RF		0x2000
#define	MII_NWAY_ACK		0x4000
#define	MII_NWAY_NP		0x8000

/* mii_stsout_register_bits */
#define	MII_STSOUT_LINK_FAIL	0x4000
#define	MII_STSOUT_SPD		0x0080
#define	MII_STSOUT_DPLX		0x0040

/* mii_stsics_register_bits */
#define	MII_STSICS_SPD		0x8000
#define	MII_STSICS_DPLX		0x4000
#define	MII_STSICS_LINKSTS	0x0001

/* mii_stssum_register_bits */
#define	MII_STSSUM_LINK		0x0008
#define	MII_STSSUM_DPLX		0x0004
#define	MII_STSSUM_AUTO		0x0002
#define	MII_STSSUM_SPD		0x0001

/* sis900_revision_id */
#define	SIS630A_900_REV		0x80
#define	SIS630E_900_REV		0x81
#define	SIS630S_900_REV		0x82
#define	SIS630EA1_900_REV	0x83
#define	SIS635A_900_REV		0x90
#define	SIS900B_900_REV		0x03

/* sis630_revision_id */
#define	SIS630A0		0x00
#define	SIS630A1		0x01
#define	SIS630B0		0x10
#define	SIS630B1		0x11

#define	FDX_CAPABLE_DUPLEX_UNKNOWN	0
#define	FDX_CAPABLE_HALF_SELECTED	1
#define	FDX_CAPABLE_FULL_SELECTED	2

#define	HW_SPEED_UNCONFIG	0
#define	HW_SPEED_HOME		1
#define	HW_SPEED_10_MBPS	10
#define	HW_SPEED_100_MBPS	100
#define	HW_SPEED_DEFAULT	(HW_SPEED_100_MBPS)

#define	CRC_SIZE		4
#define	MAC_HEADER_SIZE		14

#ifdef notdef
#define	TX_BUF_SIZE     1536
#define	RX_BUF_SIZE     1536
#ifdef LINUX
#define	NUM_TX_DESC	16		/* Number of Tx descriptor registers. */
#define	NUM_RX_DESC	16		/* Number of Rx descriptor registers. */
#endif
#ifdef SOLARIS
#define	NUM_TX_DESC	64		/* Number of Tx descriptor registers. */
#define	NUM_RX_DESC	128		/* Number of Rx descriptor registers. */
#endif
#define	TX_TOTAL_SIZE	(NUM_TX_DESC*sizeof(BufferDesc))
#define	RX_TOTAL_SIZE	(NUM_RX_DESC*sizeof(BufferDesc))
#endif

#define	SIS630_VENDOR_ID	0x1039
#define	SIS630_DEVICE_ID	0x0630

#define	PCI_VENDOR_ID_SI	0x1039
#define	PCI_DEVICE_ID_SI_900	0x0900
#define	PCI_DEVICE_ID_SI_7016	0x7016
#define	PCI_DEVICE_ID_SI_630	0x0630
