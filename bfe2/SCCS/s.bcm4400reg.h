h34295
s 00022/00023/00331
d D 1.6 11/09/19 23:07:17 mrym 6 5
c 2.6.2
e
s 00012/00007/00342
d D 1.5 08/01/12 20:06:22 mrym 5 4
c os putback
e
s 00010/00009/00339
d D 1.4 07/11/12 00:02:50 mrym 4 3
c cstyled
e
s 00127/00127/00221
d D 1.3 07/09/23 16:36:19 mrym 3 2
c 2.6.0 unsigned
e
s 00006/00000/00342
d D 1.2 07/09/23 16:31:38 mrym 2 1
c 2.6.0
e
s 00342/00000/00000
d D 1.1 06/05/21 15:46:58 mrym 1 0
c date and time created 06/05/21 15:46:58 by mrym
e
u
U
f e 0
t
T
I 1
/*
 * bcm4400reg.h : Macro definitions for bcm440x fast ethernet mac chips
 * Coded by Masayuki Murayama (KHF04453@nifty.ne.jp)
I 4
 * This file is public domain.
E 4
 */
I 5
#ifndef _BCM4400REG_H_
#define	_BCM4400REG_H_
E 5

D 4
#pragma ident   "%W% %E%"
E 4
I 4
#pragma	ident	"%Z%%M% %I%     %E%"
E 4

/*
 * register offsets
 */
#define	PHYCTL		0x0000	/* PHY control register */
#define	BISTSTAT	0x000c
#define	WAKEUPLEN	0x0010

#define	INTSTAT		0x0020	/* interrupt status */
#define	INTMASK		0x0024	/* interrupt mask */
#define	GPTIMER		0x0028	/* general purpose timer */

#define	ENETADDRLO	0x0088
#define	ENETADDRHI	0x008c
#define	ENETFTADDR	0x0090
#define	ENETFTDATA	0x0094

#define	TXMAXBURSTLEN	0x00a0
#define	RXMAXBURSTLEN	0x00a4
#define	MACCTL		0x00a8	/* mac control register */
#define	FLOWCTL		0x00ac	/* flow control register */

D 4
#define	RXINTDELAY	0x0100	/* rx interrupt delay */ 
E 4
I 4
#define	RXINTDELAY	0x0100	/* rx interrupt delay */
E 4

/* dma registers */
D 6
#define	TXCTL		0x0200	/* transmit control register */
#define	TXDESCBASE	0x0204	/* transmit descriptor base addr */
#define	TXTAIL		0x0208	/* tail of transmit descriptor */
#define	TXSTAT		0x020c	/* transmit status register */
#define	RXCTL		0x0210	/* receive control register */
E 6
I 6
#define	TXCTL		0x0200	/* transmit channel control register */
#define	TXDESCBASE	0x0204	/* transmit descriptor table address */
#define	TXTAIL		0x0208	/* transmit descriptor table pointer */
#define	TXSTAT		0x020c	/* transmit channel status register */
#define	RXCTL		0x0210	/* receive channel control register */
E 6
#define	RXDESCBASE	0x0214	/* receive descriptor base address */
#define	RXTAIL		0x0218	/* tail of receive descriptor */
#define	RXSTAT		0x021c	/* receive status register */

/* mac registers */
#define	RXCFG		0x0400	/* receive configuration register */
#define	RXMAXLEN	0x0404	/* max length of rx packet */
#define	TXMAXLEN	0x0408	/* max length of tx packet */
#define	MIICTL		0x0410	/* MII control register */
#define	MIIDATA		0x0414	/* MII data register */
#define	MACINTMASK	0x0418	/* MAC interrupt mask register */
#define	MACINTSTAT	0x041c	/* MAC interrupt status register */
#define	CAMLOW		0x0420	/* LSB of CAM data */
#define	CAMHI		0x0424	/* MSB of CAM data */
#define	CAMCTL		0x0428	/* CAM control register */
#define	ENETCTL		0x042c	/* Ethernet control register */
#define	TXCFG		0x0430	/* transmit configuration register */
#define	TXHIWAT		0x0434	/* trasmit water mark */
#define	MIBCTL		0x0438	/* MIB control register */

#define	MIBDATA		0x0500	/* MIB data register */

#define	SBCFG_BASE	0x0f00	/* Silicon Backplane configuration register */

/* PHY control register */
D 3
#define	PHYCTL_RESET	0x00008000
#define	PHYCTL_INTERNAL	0x00000400
E 3
I 3
#define	PHYCTL_RESET	0x00008000U
#define	PHYCTL_INTERNAL	0x00000400U
E 3

/* INTMASK and INTSTAT register */
D 3
#define	INT_MIIRD	0x10000000
#define	INT_MIIWR	0x08000000
#define	INT_MAC		0x04000000
#define	INT_TX		0x01000000
#define	INT_RX		0x00010000
#define	INT_TXUF	0x00008000
#define	INT_RXOF	0x00004000
#define	INT_RXDESCEMPTY	0x00002000
#define	INT_DESCPROT	0x00001000
#define	INT_DATAERR	0x00000800
#define	INT_DESCERR	0x00000400
#define	INT_GPTIMER	0x00000080
#define	INT_PME		0x00000040
E 3
I 3
#define	INT_MIIRD	0x10000000U
#define	INT_MIIWR	0x08000000U
#define	INT_MAC		0x04000000U
#define	INT_TX		0x01000000U
#define	INT_RX		0x00010000U
#define	INT_TXUF	0x00008000U
#define	INT_RXOF	0x00004000U
#define	INT_RXDESCEMPTY	0x00002000U
#define	INT_DESCPROT	0x00001000U
#define	INT_DATAERR	0x00000800U
#define	INT_DESCERR	0x00000400U
#define	INT_GPTIMER	0x00000080U
#define	INT_PME		0x00000040U
E 3

#define	INT_BITS	\
	"\020"	\
	"\035MIIRD"	\
	"\034MIIWR"	\
	"\033MAC"	\
	"\031TX"	\
	"\021RX"	\
	"\020TXUF"	\
	"\017RXOF"	\
	"\016RXDESCEMPTY"	\
	"\015DESCPROT"	\
	"\014DATAERR"	\
	"\013DESCERR"	\
	"\010GPTIMER"	\
	"\007PME"

/* MAC control register */
D 3
#define	MACCTL_EN_CRC	0x00000001
#define	MACCTL_EN_LED	0x000000e0	/* LED control for rev >= 1 */
E 3
I 3
#define	MACCTL_EN_CRC	0x00000001U
#define	MACCTL_EN_LED	0x000000e0U	/* LED control for rev >= 1 */
E 3

/* Flow control register */
D 3
#define	FLOWCTL_ENABLE	0x00008000
#define	FLOWCTL_RXHIWAT	0x000000ff
E 3
I 3
#define	FLOWCTL_ENABLE	0x00008000U
#define	FLOWCTL_RXHIWAT	0x000000ffU
E 3

D 6
/* TX and RX DESCBASE register */
E 6
I 6
/* TX and RX descriptor table address register */
E 6
#define	DESC_BASE_ALIGN	0x1000

D 6
/* Transmit control register */
E 6
I 6
/* Transmit channel control register */
E 6
D 3
#define	TXCTL_FLUSH	0x00000010
#define	TXCTL_FPRI	0x00000008
#define	TXCTL_LPBK	0x00000004
#define	TXCTL_SUSPEND	0x00000002
#define	TXCTL_EN	0x00000001
E 3
I 3
#define	TXCTL_FLUSH	0x00000010U
#define	TXCTL_FPRI	0x00000008U
#define	TXCTL_LPBK	0x00000004U
#define	TXCTL_SUSPEND	0x00000002U
#define	TXCTL_EN	0x00000001U
E 3

D 6
/* Transmit status register */
D 3
#define	TXSTAT_FLUSH	0x00100000
#define	TXSTAT_ERR	0x000f0000
E 3
I 3
#define	TXSTAT_FLUSH	0x00100000U
E 6
I 6
/* Transmit channel status register */
E 6
#define	TXSTAT_ERR	0x000f0000U
E 3
#define		TXSTAT_ERR_SHIFT	16
D 3
#define		TXSTAT_ERR_NONE		(0 << TXSTAT_ERR_SHIFT)
#define		TXSTAT_ERR_DESCPROT	(1 << TXSTAT_ERR_SHIFT)
#define		TXSTAT_ERR_FIFOUN	(2 << TXSTAT_ERR_SHIFT)
#define		TXSTAT_ERR_BEBUFRD	(3 << TXSTAT_ERR_SHIFT)
#define		TXSTAT_ERR_BEDESC	(4 << TXSTAT_ERR_SHIFT)
#define	TXSTAT_STATE	0x0000f000
E 3
I 3
#define		TXSTAT_ERR_NONE		(0U << TXSTAT_ERR_SHIFT)
#define		TXSTAT_ERR_DESCPROT	(1U << TXSTAT_ERR_SHIFT)
#define		TXSTAT_ERR_FIFOUN	(2U << TXSTAT_ERR_SHIFT)
#define		TXSTAT_ERR_BEBUFRD	(3U << TXSTAT_ERR_SHIFT)
#define		TXSTAT_ERR_BEDESC	(4U << TXSTAT_ERR_SHIFT)
#define	TXSTAT_STATE	0x0000f000U
E 3
#define		TXSTAT_STATE_SHIFT	12
D 3
#define		TXSTAT_STATE_DISABLED	(0 << TXSTAT_STATE_SHIFT)
#define		TXSTAT_STATE_ACTIVE	(1 << TXSTAT_STATE_SHIFT)
#define		TXSTAT_STATE_IDLE	(2 << TXSTAT_STATE_SHIFT)
#define		TXSTAT_STATE_STOPPED	(3 << TXSTAT_STATE_SHIFT)
#define		TXSTAT_STATE_SUSP	(4 << TXSTAT_STATE_SHIFT)	
#define	TXSTAT_DESCOFFSET	0x00000fff
E 3
I 3
#define		TXSTAT_STATE_DISABLED	(0U << TXSTAT_STATE_SHIFT)
#define		TXSTAT_STATE_ACTIVE	(1U << TXSTAT_STATE_SHIFT)
#define		TXSTAT_STATE_IDLE	(2U << TXSTAT_STATE_SHIFT)
#define		TXSTAT_STATE_STOPPED	(3U << TXSTAT_STATE_SHIFT)
D 4
#define		TXSTAT_STATE_SUSP	(4U << TXSTAT_STATE_SHIFT)	
E 4
I 4
#define		TXSTAT_STATE_SUSP	(4U << TXSTAT_STATE_SHIFT)
E 4
D 6
#define	TXSTAT_DESCOFFSET	0x00000fffU
E 6
I 6
#define	TXSTAT_CURRDSCR	0x00000fffU
E 6
E 3

/* Receive control register */
D 3
#define	RXCTL_EN	0x00000001
#define	RXCTL_OFFSET	0x000000fe
E 3
I 3
D 6
#define	RXCTL_EN	0x00000001U
#define	RXCTL_OFFSET	0x000000feU
E 6
I 6
#define	RXCTL_OFFSET	0x000000feU	/* size of status region in bytes */
E 6
E 3
#define		RXCTL_OFFSET_SHIFT	1
I 6
#define	RXCTL_EN	0x00000001U
E 6

/* Receive status register */
D 3
#define	RXSTAT_ERR	0x000f0000
E 3
I 3
#define	RXSTAT_ERR	0x000f0000U
E 3
#define		RXSTAT_ERR_SHIFT	16
D 3
#define		RXSTAT_ERR_NONE		(0 << RXSTAT_ERR_SHIFT)
#define		RXSTAT_ERR_DESCPROT	(1 << RXSTAT_ERR_SHIFT)
#define		RXSTAT_ERR_DATAOV	(2 << RXSTAT_ERR_SHIFT)
#define		RXSTAT_ERR_BEBUFWR	(3 << RXSTAT_ERR_SHIFT)
#define		RXSTAT_ERR_BERDESC	(4 << RXSTAT_ERR_SHIFT)
#define	RXSTAT_STATE	0x0000f000
E 3
I 3
#define		RXSTAT_ERR_NONE		(0U << RXSTAT_ERR_SHIFT)
#define		RXSTAT_ERR_DESCPROT	(1U << RXSTAT_ERR_SHIFT)
#define		RXSTAT_ERR_DATAOV	(2U << RXSTAT_ERR_SHIFT)
#define		RXSTAT_ERR_BEBUFWR	(3U << RXSTAT_ERR_SHIFT)
#define		RXSTAT_ERR_BERDESC	(4U << RXSTAT_ERR_SHIFT)
#define	RXSTAT_STATE	0x0000f000U
E 3
#define		RXSTAT_STATE_SHIFT	12
D 3
#define		RXSTAT_STATE_DISABLED	(0 << RXSTAT_STATE_SHIFT)
#define		RXSTAT_STATE_ACTIVE	(1 << RXSTAT_STATE_SHIFT)
#define		RXSTAT_STATE_IDLE	(2 << RXSTAT_STATE_SHIFT)
#define		RXSTAT_STATE_STOPPED	(3 << RXSTAT_STATE_SHIFT)
#define	RXSTAT_DESCOFFSET	0x00000fff
E 3
I 3
#define		RXSTAT_STATE_DISABLED	(0U << RXSTAT_STATE_SHIFT)
#define		RXSTAT_STATE_ACTIVE	(1U << RXSTAT_STATE_SHIFT)
#define		RXSTAT_STATE_IDLE	(2U << RXSTAT_STATE_SHIFT)
#define		RXSTAT_STATE_STOPPED	(3U << RXSTAT_STATE_SHIFT)
D 6
#define	RXSTAT_DESCOFFSET	0x00000fffU
E 6
I 6
#define	RXSTAT_CURRDSCR	0x00000fffU
E 6
E 3

/* receive configuration register */
D 3
#define	RXCFG_REJECT_FILTER	0x00000080
#define	RXCFG_UNIFLOWCTL	0x00000040
#define	RXCFG_EN_FLOWCTL	0x00000020
#define	RXCFG_LOOPBACK		0x00000010
#define	RXCFG_PROMISC		0x00000008
#define	RXCFG_RXDIS_TX		0x00000004
#define	RXCFG_ALLMULT		0x00000002
#define	RXCFG_DISBRD		0x00000001
E 3
I 3
#define	RXCFG_REJECT_FILTER	0x00000080U
#define	RXCFG_UNIFLOWCTL	0x00000040U
#define	RXCFG_EN_FLOWCTL	0x00000020U
#define	RXCFG_LOOPBACK		0x00000010U
#define	RXCFG_PROMISC		0x00000008U
#define	RXCFG_RXDIS_TX		0x00000004U
#define	RXCFG_ALLMULT		0x00000002U
#define	RXCFG_DISBRD		0x00000001U
E 3

/* MII control register */
D 3
#define	MIICTL_PREAMBLE		0x00000080
#define	MIICTL_FREQ		0x0000007f
E 3
I 3
#define	MIICTL_PREAMBLE		0x00000080U
#define	MIICTL_FREQ		0x0000007fU
E 3

/* MAC interrupt mask and status register */
D 3
#define	MACINT_MII		0x00000001
#define	MACINT_MIB		0x00000002
#define	MACINT_FLOW		0x00000004
E 3
I 3
#define	MACINT_MII		0x00000001U
#define	MACINT_MIB		0x00000002U
#define	MACINT_FLOW		0x00000004U
E 3

I 2
#define	MACINT_BITS	\
	"\020"	\
	"\003FLOW"	\
	"\002MIB"	\
	"\001MII"

E 2
/* MSB of CAM data */
D 3
#define	CAMHI_VALID		0x00010000
E 3
I 3
#define	CAMHI_VALID		0x00010000U
E 3

/* CAM control register */
D 3
#define	CAMCTL_BUSY		0x80000000
#define	CAMCTL_INDEX		0x003f0000
#define		CAMCTL_INDEX_SHIFT	16
E 3
I 3
#define	CAMCTL_BUSY		0x80000000U
#define	CAMCTL_INDEX		0x003f0000U
#define		CAMCTL_INDEX_SHIFT	16U
E 3
#define		CAM_ENTRY_SIZE	64
D 3
#define	CAMCTL_WRITE		0x00000008
#define	CAMCTL_READ		0x00000004
#define	CAMCTL_MSEL		0x00000002
#define	CAMCTL_EN		0x00000001
E 3
I 3
#define	CAMCTL_WRITE		0x00000008U
#define	CAMCTL_READ		0x00000004U
#define	CAMCTL_MSEL		0x00000002U
#define	CAMCTL_EN		0x00000001U
E 3

/* Ethernet control register */
D 3
#define	ENETCTL_EXTERNALPHY	0x00000008
#define	ENETCTL_SOFTRESET	0x00000004
#define	ENETCTL_DISABLE		0x00000002
#define	ENETCTL_ENABLE		0x00000001
E 3
I 3
#define	ENETCTL_EXTERNALPHY	0x00000008U
#define	ENETCTL_SOFTRESET	0x00000004U
#define	ENETCTL_DISABLE		0x00000002U
#define	ENETCTL_ENABLE		0x00000001U
E 3

/* Transmit control register */
D 3
#define	TXCFG_SMALLSLOT		0x00000008
#define	TXCFG_SNGLBCKOFF	0x00000004
#define	TXCFG_FLOWMODE		0x00000002
#define	TXCFG_FULLDPX		0x00000001
E 3
I 3
#define	TXCFG_SMALLSLOT		0x00000008U
#define	TXCFG_SNGLBCKOFF	0x00000004U
#define	TXCFG_FLOWMODE		0x00000002U
#define	TXCFG_FULLDPX		0x00000001U
E 3

/* MIB control register */
D 3
#define	MIBCTL_AUTOCLR		0x00000001
E 3
I 3
#define	MIBCTL_AUTOCLR		0x00000001U
E 3


/* Sonics SiliconBackplane config registers */

D 3
#define	RXINTDELAY_FRAMECNT	0xff000000
E 3
I 3
#define	RXINTDELAY_FRAMECNT	0xff000000U
E 3
#define		RXINTDELAY_FRAMECNT_SHIFT	24
D 3
#define	RXINTDELAY_TIMEOUT	0x00ffffff
E 3
I 3
#define	RXINTDELAY_TIMEOUT	0x00ffffffU
E 3

/*
 * TX and RX descriptor format
 */
struct bfe_desc {
D 5
	uint32_t	desc_ctl;
	uint32_t	desc_addr;
E 5
I 5
	volatile uint32_t	desc_ctl;
D 6
	volatile uint32_t	desc_addr;
E 6
I 6
	volatile uint32_t	desc_databufptr;
E 6
E 5
};


/* control flags */
D 3
#define	CTL_STARTF	0x80000000
#define	CTL_ENDF	0x40000000
#define	CTL_INTREQ	0x20000000	/* interrupt on completion */
#define	CTL_ENDTBL	0x10000000	/* end of descriptor table */
#define	CTL_LENGTH	0x00001fff	/* buffer byte count */
E 3
I 3
D 6
#define	CTL_STARTF	0x80000000U
#define	CTL_ENDF	0x40000000U
#define	CTL_INTREQ	0x20000000U	/* interrupt on completion */
#define	CTL_ENDTBL	0x10000000U	/* end of descriptor table */
#define	CTL_LENGTH	0x00001fffU	/* buffer byte count */
E 6
I 6
#define	CTL_SOF		0x80000000U
#define	CTL_EOF		0x40000000U
#define	CTL_IOC		0x20000000U	/* interrupt on completion */
#define	CTL_EOT		0x10000000U	/* end of descriptor table */
#define	CTL_BUFCOUNT	0x00001fffU	/* buffer byte count */
E 6
E 3

#define	CTL_BITS	\
	"\020"		\
D 6
	"\040STARTF"	\
	"\037ENDF"	\
	"\036INTREQ"	\
	"\035ENDTBL"
E 6
I 6
	"\040SOF"	\
	"\037EOF"	\
	"\036IOC"	\
	"\035EOT"
E 6

/* MIB registers */
#define	MIB_SIZE	(0xdc/4)

/*
 * RX header and related definitions
 */
#define	RX_HEADER_SIZE	28

/* offset */
#define	RXHD_LEN	0	/* word: packet length including fcs */
#define	RXHD_RXF	2	/* word: rxf flags */

/* Receive flags in receive header */
D 3
#define	RXF_LAST	0x0800
#define	RXF_MISS	0x0080
#define	RXF_BROADCAST	0x0040
#define	RXF_MULTICAST	0x0020
#define	RXF_LONG	0x0010
#define	RXF_NIBBLEODD	0x0008
#define	RXF_RXERR	0x0004
#define	RXF_CRC		0x0002
#define	RXF_OV		0x0001
E 3
I 3
#define	RXF_LAST	0x0800U
#define	RXF_MISS	0x0080U
#define	RXF_BROADCAST	0x0040U
#define	RXF_MULTICAST	0x0020U
#define	RXF_LONG	0x0010U
#define	RXF_NIBBLEODD	0x0008U
#define	RXF_RXERR	0x0004U
#define	RXF_CRC		0x0002U
#define	RXF_OV		0x0001U
E 3

#define	RXF_BITS	\
	"\020"		\
	"\014LAST"	\
	"\010MISS"	\
	"\007BROADCAST"	\
	"\006MULTICAST"	\
	"\005LONG"	\
	"\004NIBBLEODD"	\
	"\003RXERR"	\
	"\002CRC"	\
	"\001OV"

D 4
#define RXF_ERRORS (RXF_NIBBLEODD | RXF_RXERR | RXF_CRC | RXF_OV)
E 4
I 4
#define	RXF_ERRORS (RXF_NIBBLEODD | RXF_RXERR | RXF_CRC | RXF_OV)
E 4

/*
 * PCI configration register
 */
#define	PCI_BAR0_WIN	0x80

/*
 * Silicon Backplane address map
 */
D 3
#define	SB_PCIDMA_BASE	0x40000000
#define	SB_PCIDMA_SIZE	0x40000000
#define	SB_ENUM_BASE	0x18000000
#define	SB_EMAC_BASE	0x18000000
#define	SB_CODEC_BASE	0x18001000
#define	SB_PCI_BASE	0x18002000
E 3
I 3
#define	SB_PCIDMA_BASE	0x40000000U
#define	SB_PCIDMA_SIZE	0x40000000U
#define	SB_ENUM_BASE	0x18000000U
#define	SB_EMAC_BASE	0x18000000U
#define	SB_CODEC_BASE	0x18001000U
#define	SB_PCI_BASE	0x18002000U
E 3

/*
 * Silicon backplane PCI control register
 */
#define	SBTOPCI2	0x108
D 3
#define	SBTOPCI_PREF	0x4
#define	SBTOPCI_BURST	0x8
E 3
I 3
#define	SBTOPCI_PREF	0x4U
#define	SBTOPCI_BURST	0x8U
E 3

/*
 * Register definition of Silicon Backplane
 */
/* imstate */
D 4
#define SB_IMSTATE	(0x90 + SBCFG_BASE)
E 4
I 4
#define	SB_IMSTATE	(0x90 + SBCFG_BASE)
E 4
D 3
#define	SB_IMSTATE_TO		0x00040000
#define	SB_IMSTATE_IBE		0x00020000
#define	SB_IMSTATE_AP_MASK	0x00000030
E 3
I 3
#define	SB_IMSTATE_TO		0x00040000U
#define	SB_IMSTATE_IBE		0x00020000U
#define	SB_IMSTATE_AP_MASK	0x00000030U
E 3
#define		SB_IMSTATE_AP_SHIFT	4
D 3
#define		SB_IMSTATE_AP_BOTH	(0 << SBIM_AP_SHIFT)
#define		SB_IMSTATE_AP_TS	(1 << SBIM_AP_SHIFT)
#define		SB_IMSTATE_AP_TK	(2 << SBIM_AP_SHIFT)
#define		SB_IMSTATE_AP_RSV	(3 << SBIM_AP_SHIFT)
#define	SB_IMSTATE_PC		0x0000000f
E 3
I 3
#define		SB_IMSTATE_AP_BOTH	(0U << SBIM_AP_SHIFT)
#define		SB_IMSTATE_AP_TS	(1U << SBIM_AP_SHIFT)
#define		SB_IMSTATE_AP_TK	(2U << SBIM_AP_SHIFT)
#define		SB_IMSTATE_AP_RSV	(3U << SBIM_AP_SHIFT)
#define	SB_IMSTATE_PC		0x0000000fU
E 3

/* sbintvec */
D 4
#define SB_INTMASK	(0x94 + SBCFG_BASE)
E 4
I 4
#define	SB_INTMASK	(0x94 + SBCFG_BASE)
E 4
D 3
#define	SB_INTMASK_ENET0	0x02
E 3
I 3
#define	SB_INTMASK_ENET0	0x02U
E 3

/* sbtmstatelow */
D 4
#define SB_TMSTATEL		(0x98 + SBCFG_BASE)
E 4
I 4
D 5
#define	SB_TMSTATEL		(0x98 + SBCFG_BASE)
E 5
I 5
#define	SB_TMSTATEL	(0x98 + SBCFG_BASE)
E 5
E 4

D 3
#define	SB_TMSTATEL_BE		0x80000000
#define	SB_TMSTATEL_PE		0x40000000
#define	SB_TMSTATEL_FGC		0x00020000
#define	SB_TMSTATEL_CLK		0x00010000
#define	SB_TMSTATEL_REJ		0x00000002
#define	SB_TMSTATEL_RESET	0x00000001
E 3
I 3
#define	SB_TMSTATEL_BE		0x80000000U
#define	SB_TMSTATEL_PE		0x40000000U
#define	SB_TMSTATEL_FGC		0x00020000U
#define	SB_TMSTATEL_CLK		0x00010000U
#define	SB_TMSTATEL_REJ		0x00000002U
#define	SB_TMSTATEL_RESET	0x00000001U
E 3

/* tmstate (high) */
D 4
#define SB_TMSTATEH	(0x9c + SBCFG_BASE)
E 4
I 4
#define	SB_TMSTATEH	(0x9c + SBCFG_BASE)
E 4
D 3
#define	SB_TMSTATEH_BISTD	0x80000000
#define	SB_TMSTATEH_BISTF	0x40000000
#define	SB_TMSTATEH_GCR		0x20000000
#define	SB_TMSTATEH_BUSY	0x00000004
#define	SB_TMSTATEH_INT1	0x00000002
#define	SB_TMSTATEH_SERR	0x00000001
E 3
I 3
#define	SB_TMSTATEH_BISTD	0x80000000U
#define	SB_TMSTATEH_BISTF	0x40000000U
#define	SB_TMSTATEH_GCR		0x20000000U
#define	SB_TMSTATEH_BUSY	0x00000004U
#define	SB_TMSTATEH_INT1	0x00000002U
#define	SB_TMSTATEH_SERR	0x00000001U
E 3

/* ID register (high) */
D 4
#define SB_IDH		(0xfc + SBCFG_BASE)
E 4
I 4
#define	SB_IDH		(0xfc + SBCFG_BASE)
E 4
#define	SB_IDH_VENDOR	0xffff0000
#define		SB_IDH_VENDOR_SHIFT	16
#define	SB_IDH_CORE	0x0000fff0
#define		SB_IDH_CORE_SHIFT	4
#define		SB_IDH_CORE_PCI		(0x804 << SB_IDH_CORE_SHIFT)
#define	SB_IDH_REV	0x0000000f


/* EEPROM */
#define	EEPROM_BASE	0x1000		/* eeprom starts here */
D 5
#define	EEPROM_SIZE	32		/* in int32 */
#define	EEPROM_NODEADDR	78		/* in int8 */
#define	EEPROM_PHYADDR	90		/* in int8 */
#define	EEPROM_MAGIC	126		/* in int8 */
E 5
I 5
#define	EEPROM_SIZE	32		/* in uint32_t */
#define	EEPROM_NODEADDR	78		/* in uint8_t */
#define	EEPROM_PHYADDR	90		/* in uint8_t */
#define	EEPROM_MAGIC	126		/* in uint8_t */


#endif	/* _BCM4400REG_H_ */
E 5
E 1
