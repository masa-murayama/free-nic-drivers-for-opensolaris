h38932
s 00021/00021/00468
d D 1.8 05/01/01 01:17:12 mrym 8 7
c 2.6.3
e
s 00169/00133/00320
d D 1.7 08/02/03 10:36:38 mrym 7 6
c 2.6.0
e
s 00029/00029/00424
d D 1.6 07/08/10 23:21:33 mrym 6 5
c 
e
s 00146/00146/00307
d D 1.5 07/08/09 00:36:41 mrym 5 4
c 
e
s 00100/00026/00353
d D 1.4 07/05/02 21:09:18 mrym 4 3
c 2.4.2
e
s 00068/00109/00311
d D 1.3 07/01/20 14:51:20 mrym 3 2
c cleanup & refine at 2.4.1
e
s 00065/00105/00355
d D 1.2 07/01/08 22:32:37 mrym 2 1
c 2.4.0
e
s 00460/00000/00000
d D 1.1 07/01/08 01:41:10 mrym 1 0
c date and time created 07/01/08 01:41:10 by mrym
e
u
U
f e 0
t
T
I 1
/*
D 7
 * evenetreg.h:  %W% %E%
E 7
I 7
D 8
 * evenetreg.h:  %Z%%M% %I%     %E%
E 8
I 8
 * nvenetreg.h:  %Z%%M% %I%     %E%
E 8
E 7
D 2
 * Macro definitions for nVIDIA integrated ethernet controller
E 2
I 2
 * Macro definitions for NVIDIA nForce integrated ethernet controller
E 2
 * Based on experience on re-engineering of forcedeth.c driver in linux.
 */
D 7

E 7
I 7
#ifndef _NVENETREG_H_
#define	_NVENETREG_H_
E 7
/*
 * Register offsets
 */
#define	ISR			0x000	/* interrupt status register */
#define	IMR			0x004	/* interrupt mask register */
D 7
#define	REG_008			0x008	/* reserverd */
E 7
I 7
#define	TIMERCTL		0x008
E 7
#define	TIMER			0x00c
I 4
#define	MSIMAP0			0x020
#define	MSIMAP1			0x024
#define	MSIIMR			0x030
D 5
#define	MACRESET		0x030
E 5
I 5
D 8
#define	REG_034			0x034
#define	MACRESET		0x03c
E 8
I 8
#define	MACRESET		0x034
E 8
E 5
E 4
D 7
#define	MISC			0x080
E 7
I 7
#define	TxCFG			0x080	/* tx configration */
E 7
#define	TxCTRL			0x084	/* tx control */
#define	TxSTAT			0x088	/* tx status */
#define	RxPF			0x08c	/* rx packet filter */
#define	MAXBUFSIZE		0x090
#define	RxCTRL			0x094	/* rx control */
#define	RxSTAT			0x098	/* rx status */
D 7
#define	RNDCTRL			0x09c
E 7
I 7
#define	BACKOFF			0x09c
E 7
D 4
#define	REG_0A0			0x0a0
#define	REG_0A4			0x0a4
E 4
I 4
#define	TxDEFER			0x0a0
#define	RxDEFER			0x0a4
E 4
#define	MACADDR			0x0a8	/* uint32 * 2 */
#define	MCASTADDR		0x0b0	/* uint32 * 2 */
#define	MCASTMASK		0x0b8	/* uint32 * 2 */
#define	PHYIF			0x0c0
#define	TxDESCBASE		0x100
#define	RxDESCBASE		0x104
#define	RINGCFG			0x108
D 4
#define	REG_10C			0x10c
E 4
I 4
#define	TxPOLL			0x10c
E 4
D 7
#define	CLKCTRL			0x110	/* clock control for line speed */
#define	DMASTAT			0x130	/* was setup5 */
E 7
I 7
#define	RxPOLL			0x110
#define	RxDMASTAT		0x130	/* was setup5 */
E 7
D 4
#define	DMACFG			0x13c	/* */
E 4
I 4
#define	TXWM			0x13c	/* tx watermark */
E 4
#define	DMACTRL			0x144	/* DMA for tx and rx */
#define	TxDESCBASE_HI		0x148
#define	RxDESCBASE_HI		0x14c
D 4
#define	MIISTAT			0x180
#define	REG_184			0x184
E 4
I 4
#define	TXPAUSE			0x170
#define	MIIISR			0x180
#define	MIIIMR			0x184
E 4
#define	MIIAUTO			0x188
#define	MIICFG			0x18c
#define	MIICTL			0x190
#define	MIIDATA			0x194
#define	WAKECTRL		0x200
#define	PTNCRC			0x204
#define	PTNMASK			0x208
#define	PWRCTRL			0x268
#define	PWRSTAT			0x26c
I 4
#define	StatTxCNT		0x280
#define	StatTxZeroReXmt		0x284
#define	StatTxOneReXmt		0x288
#define	StatTxManyReXmt		0x28c
#define	StatTxLateCol		0x290
#define	StatTxUnderflow		0x294
#define	StatTxLostCarrier	0x298
#define	StatTxExcessDef		0x29c
#define	StatTxRetryErr		0x2a0
#define	StatRxFrameErr		0x2a4
#define	StatRxExtraByte		0x2a8
#define	StatRxLateCol		0x2ac
#define	StatRxRunt		0x2b0
#define	StatRxFrameTooLong	0x2b4
#define	StatRxOverflow		0x2b8
#define	StatRxFCSErr		0x2bc
#define	StatRxFrameAlignErr	0x2c0
#define	StatRxLenErr		0x2c4
#define	StatRxUnicast		0x2c8
#define	StatRxMulticast		0x2cc
#define	StatRxBroadcast		0x2d0
#define	StatTxDef		0x2d4
#define	StatTxFrame		0x2d8
#define	StatRxCnt		0x2dc
#define	StatTxPause		0x2e0
#define	StatRxPause		0x2e4
#define	StatRxDropFrame		0x2e8
E 4
#define	VLANCTRL		0x300
I 4
#define	MSIXMAP0		0x3e0
#define	MSIXMAP1		0x3e4
#define	MSIXISR			0x3f0
#define	PWRSTAT2		0x600
E 4

D 3
/*
 * Interrupt Status reigsteer offset 0
 */
E 3
I 3
D 7
/* Interrupt Status reigsteer, offset 0 */
E 3
D 2
#define INTR_TXDESC		0x0100
#define INTR_TXERR1		0x0080
#define INTR_LSC		0x0040
#define INTR_TIMER		0x0020
#define INTR_TXOK		0x0010
#define INTR_TXERR2		0x0008
#define INTR_RDU		0x0004
#define INTR_RXOK		0x0002
#define INTR_RXERR		0x0001
E 2
I 2
D 4
#define INTR_TXDESC		0x0100	/* tx descriptor unavail */
#define INTR_TXERR1		0x0080	/* tx failed */
E 4
I 4
D 6
#define INTR_RXERR_FATAL	0x8000	/* rx fatal error */
#define INTR_TXDESC		0x0100	/* tx forced intr */
#define INTR_RXDESC		0x0080	/* rx forced intr */
E 4
#define INTR_LSC		0x0040	/* link status changed */
#define INTR_TIMER		0x0020	/* interval timer */
#define INTR_TXOK		0x0010	/* tx ok */
D 4
#define INTR_TXERR2		0x0008	/* tx failed */
E 4
I 4
#define INTR_TXERR		0x0008	/* tx failed */
E 4
#define INTR_RDU		0x0004	/* rx descriptor unavail */
#define INTR_RXOK		0x0002	/* rx ok */
#define INTR_RXERR		0x0001	/* rx failed */
E 6
I 6
#define INTR_RXERR_FATAL	0x8000U	/* rx fatal error */
#define INTR_TXDESC		0x0100U	/* tx forced intr */
#define INTR_RXDESC		0x0080U	/* rx forced intr */
#define INTR_LSC		0x0040U	/* link status changed */
#define INTR_TIMER		0x0020U	/* interval timer */
#define INTR_TXOK		0x0010U	/* tx ok */
#define INTR_TXERR		0x0008U	/* tx failed */
#define INTR_RDU		0x0004U	/* rx descriptor unavail */
#define INTR_RXOK		0x0002U	/* rx ok */
#define INTR_RXERR		0x0001U	/* rx failed */
E 7
I 7
/* Interrupt Status register, offset 0 */
#define	INTR_RXERR_FATAL	0x8000U	/* rx fatal error */
#define	INTR_TXDESC		0x0100U	/* tx forced intr */
#define	INTR_RXDESC		0x0080U	/* rx forced intr */
#define	INTR_LSC		0x0040U	/* link status changed */
#define	INTR_TIMER		0x0020U	/* interval timer */
#define	INTR_TXOK		0x0010U	/* tx ok */
#define	INTR_TXERR		0x0008U	/* tx failed */
#define	INTR_RDU		0x0004U	/* rx descriptor unavail */
#define	INTR_RXOK		0x0002U	/* rx ok */
#define	INTR_RXERR		0x0001U	/* rx failed */
E 7
E 6
E 2

D 4
#define INTR_ALL		0x01ff
E 4
I 4
D 6
#define INTR_ALL		0x81ff
E 6
I 6
D 7
#define INTR_ALL		0x81ffU
E 7
I 7
#define	INTR_ALL		0x81ffU
E 7
E 6
E 4

#define	INTR_BITS	\
	"\020"	\
I 4
	"\020RxErrFatal"	\
E 4
	"\011TXDESC"	\
D 4
	"\010TXERR1"	\
E 4
I 4
	"\010RXDESC"	\
E 4
D 2
	"\007LINK"	\
E 2
I 2
	"\007LSC"	\
E 2
	"\006TIMER"	\
	"\005TXOK"	\
D 4
	"\004TXERR2"	\
E 4
I 4
	"\004TXERR"	\
E 4
	"\003RDU"	\
	"\002RXOK"	\
	"\001RXERR"

D 3
#define UNKSETUP6_VAL		3	/* X */
E 3
I 3
D 7
/* MISC register, offset 0x80 */
D 6
#define MISC_HD			0x00000002	/* half duplex */
I 4
#define MISC_TxPAUSE		0x00000001	/* tx pause: 1:en 0:dis */
E 4
#define MISC_CONST		0x003b0f3c	/* initial value */
E 6
I 6
#define MISC_HD			0x00000002U	/* half duplex */
#define MISC_TxPAUSE		0x00000001U	/* tx pause: 1:en 0:dis */
#define MISC_CONST		0x003b0f3cU	/* initial value */
E 7
I 7
/* TxCFG register, offset 0x80 */
#define	TxCFG_JAM_SEQ		0x01000000U
#define	TxCFG_UDF_MASK		0x00200000U
#define	TxCFG_OWC_MASK		0x00100000U
#define	TxCFG_CRS_MASK		0x00080000U
#define	TxCFG_DEF_MASK		0x00040000U
#define	TxCFG_ABORT_MASK	0x00020000U
#define	TxCFG_RETRYE_MASK	0x00010000U
#define	TxCFG_BURST_EN		0x00001000U
#define	TxCFG_MAXRETRY		0x00000f00U
#define	TxCFG_TWO_DEF_EN	0x00000020U
#define	TxCFG_FCS_EN		0x00000010U
#define	TxCFG_PAD_EN		0x00000008U
#define	TxCFG_RETRY_EN		0x00000004U
#define	TxCFG_HD		0x00000002U	/* half duplex (legacy) */
#define	TxCFG_TxPAUSE		0x00000001U	/* tx pause: 1:en 0:dis */
E 7
E 6
E 3

I 7
#define	TxCFG_DEFAULT		0x003b0f3cU	/* initial value */

E 7
D 3
/*
 * MISC register, offset 0x80
 */
D 2
#define MISC_HD		0x00000002
#define MISC_FORCE	0x003b0f3c
E 2
I 2
#define MISC_HD		0x00000002	/* half duplex */
#define MISC_CONST	0x003b0f3c	/* initial value */
E 3
I 3
/* Tx Control register, offset 0x084 */
D 4
#define TxCTRL_START		0x00000001
E 4
I 4
D 6
#define	TxCTRL_MGMT_ST		0x40000000
#define	TxCTRL_TxPATH		0x01000000
#define	TxCTRL_MSYNC		0x000f0000
#define		TxCTRL_MSYNC_SHIFT	16
#define		TxCTRL_MSYNC_NOTREADY	(0 << TxCTRL_MSYNC_SHIFT)
#define		TxCTRL_MSYNC_PHYINIT	(4 << TxCTRL_MSYNC_SHIFT)
#define	TxCTRL_HSEMA		0x0000f000
#define		TxCTRL_HSEMA_SHIFT	12
#define		TxCTRL_HSEMA_LOADED	(4 << TxCTRL_HSEMA_SHIFT)
#define		TxCTRL_HSEMA_ACQ	(15 << TxCTRL_HSEMA_SHIFT)
#define	TxCTRL_MSEMA		0x00000f00
#define		TxCTRL_MSEMA_SHIFT	8
#define		TxCTRL_MSEMA_FREE	(0 << TxCTRL_HSEMA_SHIFT)
#define	TxCTRL_START		0x00000001
E 6
I 6
#define	TxCTRL_MGMT_ST		0x40000000U
#define	TxCTRL_TxPATH		0x01000000U
D 8
#define	TxCTRL_MSYNC		0x000f0000U
#define		TxCTRL_MSYNC_SHIFT	16U
#define		TxCTRL_MSYNC_NOTREADY	(0U << TxCTRL_MSYNC_SHIFT)
#define		TxCTRL_MSYNC_PHYINIT	(4U << TxCTRL_MSYNC_SHIFT)
E 8
I 8
#define	TxCTRL_SYNC		0x000f0000U
#define		TxCTRL_SYNC_SHIFT	16U
#define		TxCTRL_SYNC_NOTREADY	(0U << TxCTRL_SYNC_SHIFT)
#define		TxCTRL_SYNC_PHYINIT	(4U << TxCTRL_SYNC_SHIFT)
E 8
#define	TxCTRL_HSEMA		0x0000f000U
#define		TxCTRL_HSEMA_SHIFT	12U
#define		TxCTRL_HSEMA_LOADED	(4U << TxCTRL_HSEMA_SHIFT)
#define		TxCTRL_HSEMA_ACQ	(15U << TxCTRL_HSEMA_SHIFT)
#define	TxCTRL_MSEMA		0x00000f00U
#define		TxCTRL_MSEMA_SHIFT	8U
#define		TxCTRL_MSEMA_FREE	(0U << TxCTRL_HSEMA_SHIFT)
#define	TxCTRL_START		0x00000001U
E 6
E 4
E 3
E 2

I 4
#define	TxCTRL_BITS	\
	"\020"	\
	"\037MGMT_ST"	\
	"\031TxPATH"	\
	"\001START"

E 4
D 3
/*
 * Tx Control register, offset 0x084
 */
#define TxCTRL_START	0x00000001
E 3
I 3
/* Tx Status register, offset 0x088 */
D 5
#define TxSTAT_RUNNING		0x00000001
E 5
I 5
D 7
#define TxSTAT_RUNNING		0x00000001U
E 7
I 7
#define	TxSTAT_RUNNING		0x00000001U
E 7
E 5
E 3

D 3
/*
 * Tx Status register, offset 0x088
 */
#define TxSTAT_RUNNING	0x00000001

/*
 * Rx Packet Filter register, offset 0x08c
 */
E 3
I 3
/* Rx Packet Filter register, offset 0x08c */
E 3
D 2
#define RxPF_MBO		0x007f0008
E 2
I 2
D 4
#define RxPF_MBO		0x007f0008	/* constant */
E 4
I 4
D 5
#define RxPF_MBO		0x007f0000	/* constant */
E 4
E 2
#define RxPF_PROMISC		0x00000080	/* accept all physical */
#define RxPF_UNICAST		0x00000020	/* accept my phisical */
I 4
#define RxPF_LOOPBACK		0x00000010	/* loopback mode 1:en, 0:dis */
#define RxPF_RxPAUSE		0x00000008	/* 1:enable, 0:disable */
E 5
I 5
D 7
#define RxPF_MBO		0x007f0000U	/* constant */
#define RxPF_PROMISC		0x00000080U	/* accept all physical */
#define RxPF_UNICAST		0x00000020U	/* accept my phisical */
#define RxPF_LOOPBACK		0x00000010U	/* loopback mode 1:en, 0:dis */
#define RxPF_RxPAUSE		0x00000008U	/* 1:enable, 0:disable */
E 7
I 7
#define	RxPF_MBO		0x007f0000U	/* constant */
#define	RxPF_PROMISC		0x00000080U	/* accept all physical */
#define	RxPF_UNICAST		0x00000020U	/* accept my phisical */
#define	RxPF_LOOPBACK		0x00000010U	/* loopback mode 1:en, 0:dis */
#define	RxPF_RxPAUSE		0x00000008U	/* 1:enable, 0:disable */
E 7
E 5
E 4

D 3
/*
 * Receiver Control register, offset 0x094
 */
E 3
I 3
/* Receiver Control register, offset 0x094 */
I 4
D 5
#define RxCTRL_RxPATH		0x01000000
E 4
E 3
#define RxCTRL_START		0x00000001
E 5
I 5
D 7
#define RxCTRL_RxPATH		0x01000000U
#define RxCTRL_START		0x00000001U
E 7
I 7
#define	RxCTRL_RxPATH		0x01000000U
#define	RxCTRL_START		0x00000001U
E 7
E 5

D 3
/*
 * Receiver Status register, offset 0x098
 */
E 3
I 3
/* Receiver Status register, offset 0x098 */
E 3
D 5
#define RxSTAT_RUNNING		0x00000001
E 5
I 5
D 7
#define RxSTAT_RUNNING		0x00000001U
E 7
I 7
#define	RxSTAT_RUNNING		0x00000001U
E 7
E 5

D 3
/*
 * Random control register, offset 0x09c
 */
E 3
I 3
D 7
/* Random control register, offset 0x09c */
E 3
D 5
#define RNDCTRL_SPEED		0x0003ff00
#define		RNDCTRL_SPEED_SHIFT		8
D 3
#define		RNDCTRL_SPEED_1G		(0x7f << RNDCTRL_SPEED_SHIFT)
#define		RNDCTRL_SPEED_100M		(0x2d << RNDCTRL_SPEED_SHIFT)
E 3
#define		RNDCTRL_SPEED_10M		(0x74 << RNDCTRL_SPEED_SHIFT)
I 3
#define		RNDCTRL_SPEED_100M		(0x2d << RNDCTRL_SPEED_SHIFT)
#define		RNDCTRL_SPEED_1G		(0x7f << RNDCTRL_SPEED_SHIFT)
E 3
#define RNDCTRL_SEED		0x000000ff
E 5
I 5
#define RNDCTRL_SPEED		0x0003ff00U
#define		RNDCTRL_SPEED_SHIFT	8U
#define		RNDCTRL_SPEED_10M	(0x74U << RNDCTRL_SPEED_SHIFT)
#define		RNDCTRL_SPEED_100M	(0x2dU << RNDCTRL_SPEED_SHIFT)
#define		RNDCTRL_SPEED_1G	(0x7fU << RNDCTRL_SPEED_SHIFT)
#define RNDCTRL_SEED		0x000000ffU
E 7
I 7
/* Backoff control register, offset 0x09c */
#define	BACKOFF_SPEED		0x0003ff00U
#define		BACKOFF_SPEED_SHIFT	8U
#define		BACKOFF_SPEED_10M	(0x74U << BACKOFF_SPEED_SHIFT)
#define		BACKOFF_SPEED_100M	(0x2dU << BACKOFF_SPEED_SHIFT)
#define		BACKOFF_SPEED_1G	(0x7fU << BACKOFF_SPEED_SHIFT)
#define		BACKOFF_SPEED_MII	(0x7fU << BACKOFF_SPEED_SHIFT)
#define	BACKOFF_SEED		0x000000ffU
E 7
E 5

I 7
/* Tx defferral timing register, offset 0x0a0 */
#define	TD_IFDEF		0x00ff0000U
#define		TD_IFG_SHIFT	16
#define		TD_IFG_MII		(21 << TD_IFG_SHIFT)
#define		TD_IFG_RGMII_1G_FD	(20 << TD_IFG_SHIFT)
#define		TD_IFG_RGMII_OTHER	(22 << TD_IFG_SHIFT)
#define	TD_IFG2			0x0000ff00U
#define		TD_IFG2_SHIFT	8
#define		TD_IFG2_MII		(5 << TD_IFG2_SHIFT)
#define		TD_IFG2_RGMII_10_100	(7 << TD_IFG2_SHIFT)
#define		TD_IFG2_RGMII_1000	(5 << TD_IFG2_SHIFT)
#define		TD_IFG2_DEFAULT		(0 << TD_IFG2_SHIFT)
#define	TD_IFG1			0x000000ffU
#define		TD_IFG1_SHIFT	0
#define		TD_IFG1_DEFAULT		(15 << TD_IFG1_SHIFT)

E 7
D 3
/*
D 2
 * Multicast Addres register, offset 0x0b0
E 2
I 2
 * PHY interface register, offset 0x0c0
E 2
 */
E 3
I 3
/* PHY interface register, offset 0x0c0 */
E 3
D 2
#define MCASTADDRA_FORCE	0x00000001

/*
 * Phy Interface register, offset 0x0c0
 */
#define PHYIF_RGMII		0x10000000
#define PHYIF_100		0x00000001
#define PHYIF_1000		0x00000002
#define PHYIF_HALF		0x00000100
E 2
I 2
D 5
#define PHYIF_RGMII		0x10000000	/* 1:RGMII, 0:MII (r-) */
#define PHYIF_SPEED		0x00000003	/* speed select */
#define		PHYIF_SPEED_SHIFT	0
#define		PHYIF_SPEED_10M		(0 << PHYIF_SPEED_SHIFT)
#define		PHYIF_SPEED_100M	(1 << PHYIF_SPEED_SHIFT)
#define		PHYIF_SPEED_1G		(2 << PHYIF_SPEED_SHIFT)
#define PHYIF_HALF		0x00000100	/* duplex 1:half 0:full */
E 5
I 5
D 7
#define PHYIF_RGMII		0x10000000U	/* 1:RGMII, 0:MII (r-) */
#define PHYIF_SPEED		0x00000003U	/* speed select */
E 7
I 7
#define	PHYIF_RGMII		0x10000000U	/* 1:RGMII, 0:MII */
#define	PHYIF_SPEED		0x00000003U	/* speed select */
E 7
#define		PHYIF_SPEED_SHIFT	0U
#define		PHYIF_SPEED_10M		(0U << PHYIF_SPEED_SHIFT)
#define		PHYIF_SPEED_100M	(1U << PHYIF_SPEED_SHIFT)
#define		PHYIF_SPEED_1G		(2U << PHYIF_SPEED_SHIFT)
D 7
#define PHYIF_HALF		0x00000100U	/* duplex 1:half 0:full */
E 5
E 2
	
D 3
/*
 * Ring Sizes regiseter, offset 0x108
 */
E 3
I 3
/* Ring Sizes regiseter, offset 0x108 */
E 7
I 7
#define	PHYIF_HALF		0x00000100U	/* duplex 1:half 0:full */

/* Ring Sizes register, offset 0x108 */
E 7
E 3
D 2
#define RINGCFG_RX		0xffff0000
#define RINGCFG_RX_SHIFT	16
#define RINGCFG_TX		0x0000ffff
#define RINGCFG_TX_SHIFT	0
E 2
I 2
D 5
#define	RINGCFG_RX		0xffff0000
E 5
I 5
#define	RINGCFG_RX		0x03ff0000U
E 5
#define		RINGCFG_RX_SHIFT	16
D 5
#define	RINGCFG_TX		0x0000ffff
E 5
I 5
#define	RINGCFG_TX		0x000003ffU
E 5
#define		RINGCFG_TX_SHIFT	0
I 5
#define	RINGSIZE_MAX	0x400
E 5
E 2

I 4
D 7
/* Transmit poll register, offset 0x108 */
E 7
I 7
/* Transmit poll register, offset 0x10c */
E 7
D 5
#define	TxPOLL_MACADDR_REV	0x00008000
E 5
I 5
#define	TxPOLL_MACADDR_REV	0x00008000U
E 5

E 4
D 3
/*
 * Clock control register, offset
 */
E 3
I 3
D 7
/* Clock control register, offset */
E 3
D 2
#define CLKCTRL_EN		0x00010000
#define	CLKCTRL_DIV		0x00000fff	/* clock devider */
#define	CLKCTRL_DIV_SHIFT	0
#define	CLKCTRL_DIV_10M		(1000 << CLKCTRL_DIV_SHIFT)
#define	CLKCTRL_DIV_100M	(100 << CLKCTRL_DIV_SHIFT)
#define	CLKCTRL_DIV_1G		(50 << CLKCTRL_DIV_SHIFT)
E 2
I 2
D 5
#define CLKCTRL_FIXED		0x00010000
#define	CLKCTRL_DIV		0x00000fff	/* clock divider */
#define		CLKCTRL_DIV_SHIFT	0
#define		CLKCTRL_DIV_10M		(1000 << CLKCTRL_DIV_SHIFT)
#define		CLKCTRL_DIV_100M	(100 << CLKCTRL_DIV_SHIFT)
#define		CLKCTRL_DIV_1G		(50 << CLKCTRL_DIV_SHIFT)
E 5
I 5
#define CLKCTRL_FIXED		0x00010000U
#define	CLKCTRL_DIV		0x00000fffU	/* clock divider */
#define		CLKCTRL_DIV_SHIFT	0U
#define		CLKCTRL_DIV_10M		(1000U << CLKCTRL_DIV_SHIFT)
#define		CLKCTRL_DIV_100M	(100U << CLKCTRL_DIV_SHIFT)
#define		CLKCTRL_DIV_1G		(50U << CLKCTRL_DIV_SHIFT)
E 7
I 7
/* Receive poll register, offset 0x110 */
#define	RxPOLL_EN		0x00010000U
#define	RxPOLL_ITV		0x00000fffU	/* interval */
#define		RxPOLL_ITV_SHIFT	0U
#define		RxPOLL_ITV_10M		(1000U << RxPOLL_ITV_SHIFT)
#define		RxPOLL_ITV_100M		(100U << RxPOLL_ITV_SHIFT)
D 8
#define		RxPOLL_ITV_1G		(10U << RxPOLL_ITV_SHIFT)
E 8
I 8
#define		RxPOLL_ITV_1G		(50U << RxPOLL_ITV_SHIFT)
E 8
E 7
E 5
E 2

D 3
/*
 * DMA status register, offset 130
 */
E 3
I 3
D 7
/* DMA status register, offset 130 */
E 3
D 6
#define DMASTAT_RUNNING		0x80000000
E 6
I 6
#define DMASTAT_RUNNING		0x80000000U
E 7
I 7
/* Rx DMA status register, offset 130 */
#define	RxDMASTAT_RUNNING	0x80000000U
E 7
E 6

D 3
/*
D 2
 * DMA configuration register, offset 13c
 */
#define DMACFG_DEFAULT		0x00200010

/*
E 2
 *  DMA control register, offset 0x144
 */
E 3
I 3
/* DMA control register, offset 0x144 */
E 3
D 5
#define	DMACTRL_EXFMT_EN	0x00002000
#define	DMACTRL_RXCHECK		0x00000400
#define	DMACTRL_EXFMT		0x00000300
#define		DMACTRL_EXFMT_SHIFT	8
#define		DMACTRL_EXFMT_2		(1 << DMACTRL_EXFMT_SHIFT)
#define		DMACTRL_EXFMT_3		(2 << DMACTRL_EXFMT_SHIFT)
#define	DMACTRL_VLANINS		0x00000080
#define	DMACTRL_VLANSTRIP	0x00000040
#define	DMACTRL_RESET_ON	0x00000010
#define	DMACTRL_IDLE		0x00000008
D 2
#define	DMACTRL_RESET_VALID	0x00000004	/* W */
#define	DMACTRL_START		0x00000002	/* W */
#define	DMACTRL_TxPOLL		0x00000001
E 2
I 2
#define	DMACTRL_RESET_VALID	0x00000004	/* -w */
#define	DMACTRL_START		0x00000002	/* -w */
#define	DMACTRL_TxPOLL		0x00000001	/* -w */
E 5
I 5
#define	DMACTRL_TxRCMP_EN	0x00002000U
#define	DMACTRL_RXCHECK		0x00000400U
#define	DMACTRL_DFMT		0x00000300U
#define		DMACTRL_DFMT_SHIFT	8U
#define		DMACTRL_DFMT_1		(0U << DMACTRL_DFMT_SHIFT)
#define		DMACTRL_DFMT_2		(1U << DMACTRL_DFMT_SHIFT)
#define		DMACTRL_DFMT_3		(2U << DMACTRL_DFMT_SHIFT)
#define	DMACTRL_VLANINS		0x00000080U
#define	DMACTRL_VLANSTRIP	0x00000040U
#define	DMACTRL_RESET		0x00000010U
#define	DMACTRL_IDLE		0x00000008U
#define	DMACTRL_STOP		0x00000004U	/* -w */
D 7
#define	DMACTRL_START		0x00000002U	/* -w */
E 7
I 7
#define	DMACTRL_RxPOLL		0x00000002U	/* -w */
E 7
#define	DMACTRL_TxPOLL		0x00000001U	/* -w */
E 5
E 2

D 5
#define	DMACTRL_RESET		(DMACTRL_RESET_VALID | DMACTRL_RESET_ON)
#define	DMACTRL_UNRESET		(DMACTRL_RESET_VALID)

E 5
D 4
#define	DMACTRL_DESC_1		0x00000000
#define	DMACTRL_DESC_2		(DMACTRL_EXFMT_EN | DMACTRL_EXFMT_2)
#define	DMACTRL_DESC_3		(DMACTRL_EXFMT_EN | DMACTRL_EXFMT_3)

E 4
#define	DMACTRL_BITS	\
	"\020"	\
	"\016DescEx"	\
	"\013RXCHECK"	\
D 7
	"\012FMT3"	\
	"\011FMT2"	\
E 7
	"\010VLANINS"	\
	"\007VLANSTRIP"	\
D 5
	"\005RESET_ON"	\
E 5
I 5
	"\005RESET"	\
E 5
	"\004IDLE"	\
D 5
	"\003RESET_VALID"	\
E 5
I 5
	"\003STOP"	\
E 5
D 7
	"\002START"	\
E 7
I 7
	"\002RxPOLL"	\
E 7
	"\001TxPOLL"

D 3
/*
 * MII Status register, offset 180
 */
E 3
I 3
D 4
/* MII Status register, offset 180 */
E 3
D 2
#define MIISTAT_MASK		0x0000000f
#define MIISTAT_LINKCHANGE	0x00000008
#define MIISTAT_DONE		0x00000004
#define MIISTAT_ERROR		0x00000001
E 2
I 2
#define MIISTAT_LSC		0x00000008	/* link status changed */
#define MIISTAT_DONE		0x00000004	/* MII read/write done */
#define MIISTAT_ERROR		0x00000001	/* MII read/write error */
E 4
I 4
/* tx pause control register, offset 170 */
D 5
#define	TXPAUSE_DIS	0x1ff0080
#define	TXPAUSE_EN	0x0c00030
E 5
I 5
D 8
#define	TXPAUSE_DIS	0x1ff0080U
#define	TXPAUSE_EN	0x0c00030U
E 8
I 8
#define	TXPAUSE_DIS	0x0fff0080U
#define	TXPAUSE_EN1	0x01800010U
#define	TXPAUSE_EN2	0x056003f0U
#define	TXPAUSE_EN3	0x09f00880U
E 8
E 5
E 4
E 2

D 4
#define	MIISTAT_BITS	\
E 4
I 4
/* MII interrupt status register, offset 180 */
/* MII interrupt mask register, offset 184 */
D 5
#define MIIISR_LSC		0x00000008	/* link status changed */
#define MIIISR_DONE		0x00000004	/* MII read/write done */
#define MIIISR_ERROR		0x00000001	/* MII read/write error */
E 5
I 5
D 7
#define MIIISR_LSC		0x00000008U	/* link status changed */
#define MIIISR_DONE		0x00000004U	/* MII read/write done */
#define MIIISR_ERROR		0x00000001U	/* MII read/write error */
E 7
I 7
#define	MIIISR_LSC		0x00000008U	/* link status changed */
#define	MIIISR_DONE		0x00000004U	/* MII read/write done */
#define	MIIISR_ERROR		0x00000001U	/* MII read/write error */
E 7
E 5

D 7
#define MIIISR_ALL	(MIIISR_LSC | MIIISR_DONE | MIIISR_ERROR)
E 7
I 7
#define	MIIISR_ALL	(MIIISR_LSC | MIIISR_DONE | MIIISR_ERROR)
E 7

#define	MIIISR_BITS	\
E 4
	"\020"	\
D 2
	"\004LinkChange"	\
E 2
I 2
	"\004LSC"	\
E 2
	"\003Done"	\
	"\001Error"

D 3
/*
 * Auto MII control register, offset 188
 */
E 3
I 3
D 4
/* Auto MII control register, offset 188 */
E 4
I 4
/* MII auto sense control register, offset 188 */
E 4
E 3
D 2
#define MIIAUTO_PHY		0x1f000000
#define MIIAUTO_PHY_SHIFT	24
#define MIIAUTO_RUNNING	0x00100000
#define MIIAUTO_PHYVALID	0x00040000
#define MIIAUTO_LINKUP		0x00000004
#define MIIAUTO_START		0x00000002
E 2
I 2
D 5
#define	MIIAUTO_PHYADDR		0x1f000000
#define 	MIIAUTO_PHYADDR_SHIFT	24
#define	MIIAUTO_EN		0x00100000
#define	MIIAUTO_PHYVALID	0x00040000
#define	MIIAUTO_LINKUP		0x00000004
#define	MIIAUTO_BUSY		0x00000002
E 5
I 5
#define	MIIAUTO_PHYADDR		0x1f000000U
D 7
#define 	MIIAUTO_PHYADDR_SHIFT	24U
E 7
I 7
#define		MIIAUTO_PHYADDR_SHIFT	24U
E 7
#define	MIIAUTO_EN		0x00100000U
#define	MIIAUTO_PHYVALID	0x00040000U
#define	MIIAUTO_LINKUP		0x00000004U
#define	MIIAUTO_BUSY		0x00000002U
E 5
E 2

D 3
/*
 * MII Control register, offset 0x190
 */
E 3
I 3
/* MII Control register, offset 0x190 */
E 3
D 5
#define MIICTL_BUSY		0x00008000
D 2
#define MIICTL_WRITE		0x00000400
#define MIICTL_ADDR		0x000003e0
#define	MIICTL_ADDR_SHIFT	5
#define MIICTL_REG		0x0000001f
#define	MIICTL_REG_SHIFT	0
E 2
I 2
#define MIICTL_WRITE		0x00000400	/* 1:write, 0:read */
#define MIICTL_ADDR		0x000003e0	/* phy address */
#define		MIICTL_ADDR_SHIFT	5
#define MIICTL_REG		0x0000001f	/* register location */
#define		MIICTL_REG_SHIFT	0
E 5
I 5
D 7
#define MIICTL_BUSY		0x00008000U
#define MIICTL_WRITE		0x00000400U	/* 1:write, 0:read */
#define MIICTL_ADDR		0x000003e0U	/* phy address */
E 7
I 7
#define	MIICTL_BUSY		0x00008000U
#define	MIICTL_WRITE		0x00000400U	/* 1:write, 0:read */
#define	MIICTL_ADDR		0x000003e0U	/* phy address */
E 7
#define		MIICTL_ADDR_SHIFT	5U
D 7
#define MIICTL_REG		0x0000001fU	/* register location */
E 7
I 7
#define	MIICTL_REG		0x0000001fU	/* register location */
E 7
#define		MIICTL_REG_SHIFT	0U
E 5
E 2

D 3
/*
 * Wake up Flags register, offset 0x200
 */
E 3
I 3
/* Wake up Flags register, offset 0x200 */
E 3
D 4
#define WAKECTRL_VAL		0x7770
E 4
I 4
D 5
#define	WAKECTRL_Dx_MAGPAT(x)		(1 << ((x)*4))
#define	WAKECTRL_Dx_WAKEUPPAT(x)	(2 << ((x)*4))
#define	WAKECTRL_Dx_LSC(x)		(4 << ((x)*4))
E 5
I 5
#define	WAKECTRL_Dx_MAGPAT(x)		(1U << ((x)*4))
#define	WAKECTRL_Dx_WAKEUPPAT(x)	(2U << ((x)*4))
#define	WAKECTRL_Dx_LSC(x)		(4U << ((x)*4))
E 5
E 4
D 2
#define WAKECTRL_BUSY_SHIFT	24
#define WAKECTRL_ENABLE_SHIFT	16
#define WAKECTRL_D3_SHIFT	12
#define WAKECTRL_D2_SHIFT	8
#define WAKECTRL_D1_SHIFT	4
#define WAKECTRL_D0_SHIFT	0
#define WAKECTRL_ACCEPT_MAGPAT		0x01
#define WAKECTRL_ACCEPT_WAKEUPPAT	0x02
#define WAKECTRL_ACCEPT_LINKCHANGE	0x04
#define WAKECTRL_ENABLE		0x1111
E 2

I 2
D 3
/*
 * power control register
 */
E 3
I 3
D 4
/* power control register */
E 4
I 4
#define	WAKECTRL_ENABLE	\
	(WAKECTRL_Dx_MAGPAT(0) | WAKECTRL_Dx_MAGPAT(1) |	\
D 7
	 WAKECTRL_Dx_MAGPAT(2) | WAKECTRL_Dx_MAGPAT(3))
E 7
I 7
	WAKECTRL_Dx_MAGPAT(2) | WAKECTRL_Dx_MAGPAT(3))
E 7

/* Power control register, offset 268 */
E 4
E 3
D 5
#define	PWRCTRL_D3SUPP		0x40000000
#define	PWRCTRL_D2SUPP		0x04000000
#define	PWRCTRL_D1SUPP		0x02000000
E 5
I 5
#define	PWRCTRL_D3SUPP		0x40000000U
#define	PWRCTRL_D2SUPP		0x04000000U
#define	PWRCTRL_D1SUPP		0x02000000U
E 5
E 2

D 2
#define PWRCTRL_D3SUPP		(1<<30)
#define PWRCTRL_D2SUPP		(1<<26)
#define PWRCTRL_D1SUPP		(1<<25)

E 2
D 3
/*
 * Power State register, offset 0x26c
 */
E 3
I 3
/* Power State register, offset 0x26c */
E 3
D 2
#define PWRSTAT_POWEREDUP	0x8000
#define PWRSTAT_VALID		0x0100
#define PWRSTAT_MASK		0x0003
#define PWRSTAT_D0		0x0000
#define PWRSTAT_D1		0x0001
#define PWRSTAT_D2		0x0002
#define PWRSTAT_D3		0x0003
E 2
I 2
D 5
#define PWRSTAT_POWEREDUP	0x00008000
#define PWRSTAT_VALID		0x00000100
#define PWRSTAT_STATE		0x00000003
#define		PWRSTAT_STATE_SHIFT	0
#define		PWRSTAT_STATE_D0	(0 << PWRSTAT_STATE_SHIFT)
#define		PWRSTAT_STATE_D1	(1 << PWRSTAT_STATE_SHIFT)
#define		PWRSTAT_STATE_D2	(2 << PWRSTAT_STATE_SHIFT)
#define		PWRSTAT_STATE_D3	(3 << PWRSTAT_STATE_SHIFT)
E 5
I 5
D 7
#define PWRSTAT_POWEREDUP	0x00008000U
#define PWRSTAT_VALID		0x00000100U
#define PWRSTAT_STATE		0x00000003U
E 7
I 7
#define	PWRSTAT_POWEREDUP	0x00008000U
#define	PWRSTAT_VALID		0x00000100U
#define	PWRSTAT_STATE		0x00000003U
E 7
D 8
#define		PWRSTAT_STATE_SHIFT	0U
#define		PWRSTAT_STATE_D0	(0U << PWRSTAT_STATE_SHIFT)
#define		PWRSTAT_STATE_D1	(1U << PWRSTAT_STATE_SHIFT)
#define		PWRSTAT_STATE_D2	(2U << PWRSTAT_STATE_SHIFT)
#define		PWRSTAT_STATE_D3	(3U << PWRSTAT_STATE_SHIFT)
E 8
I 8
#define		PWRSTAT_STATE_D0	0U
#define		PWRSTAT_STATE_D1	1U
#define		PWRSTAT_STATE_D2	2U
#define		PWRSTAT_STATE_D3	3U
E 8
E 5
E 2

D 3
/*
 * VLAN control register, offset 0x300
 */
E 3
I 3
/* VLAN control register, offset 0x300 */
E 3
D 5
#define	VLANCTRL_EN		0x2000
E 5
I 5
#define	VLANCTRL_EN		0x2000U
E 5

I 4
/* Power State2 register, offset 0x600 */
E 4

I 3
/*
 * Rx and Tx descriptor formats
 */
E 3
struct rxdesc32 {
D 3
	volatile uint32_t	rxd0;
	volatile uint32_t	rxd1;
E 3
I 3
	volatile uint32_t	rxd0;	/* buffer address */
	volatile uint32_t	rxd1;	/* control, status, length */
E 3
};

struct rxdesc64 {
D 3
	volatile uint32_t	rxd0;
	volatile uint32_t	rxd1;
	volatile uint32_t	rxd2;
	volatile uint32_t	rxd3;
E 3
I 3
	volatile uint32_t	rxd0;	/* buffer address (high) */
	volatile uint32_t	rxd1;	/* buffer address (low) */
	volatile uint32_t	rxd2;	/* vtag */
	volatile uint32_t	rxd3;	/* control, status, length */
E 3
};

I 3
/* common bits in rx descriptors */
E 3
D 5
#define RX_FLAG_MASK_1		0xffff0000
#define RX_LEN_MASK_1		0x0000ffff
#define RX_FLAG_MASK_2		0xffffc000
#define RX_LEN_MASK_2		0x00003fff
E 5
I 5
D 7
#define RX_FLAG_MASK_1		0xffff0000U
#define RX_LEN_MASK_1		0x0000ffffU
#define RX_FLAG_MASK_2		0xffffc000U
#define RX_LEN_MASK_2		0x00003fffU
E 7
I 7
#define	RX_FLAG_MASK_1		0xffff0000U
#define	RX_LEN_MASK_1		0x0000ffffU
#define	RX_FLAG_MASK_2		0xffffc000U
#define	RX_LEN_MASK_2		0x00003fffU
E 7
E 5

struct txdesc32 {
D 3
	volatile uint32_t	txd0;
	volatile uint32_t	txd1;
E 3
I 3
	volatile uint32_t	txd0;	/* buffer address */
	volatile uint32_t	txd1;	/* control, status, length */
E 3
};

struct txdesc64 {
D 3
	volatile uint32_t	txd0;
	volatile uint32_t	txd1;
	volatile uint32_t	txd2;
	volatile uint32_t	txd3;
E 3
I 3
	volatile uint32_t	txd0;	/* buffer address (high) */
	volatile uint32_t	txd1;	/* buffer address (low) */
	volatile uint32_t	txd2;	/* vtag */
	volatile uint32_t	txd3;	/* control, status, length */
E 3
};

D 3
/*
 * Common tx descriptor bits
 */
E 3
I 3
/* common bits in tx descriptors */
E 3
D 5
#define TxD_OWN			0x80000000
#define TxD_LEN			0x00003fff
E 5
I 5
D 7
#define TxD_OWN			0x80000000U
#define TxD_LEN			0x00003fffU
E 7
I 7
#define	TxD_OWN			0x80000000U
D 8
#define	TxD_LEN			0x00003fffU
E 8
E 7
E 5

/*
 * Tx descriptor control and status flags for format 1.
 */
D 3
#define TxD_OWN_1		TxD_OWN		/* 0x80000000 */
#define TxD_ERR_1		0x40000000
#define TxD_UDF_1		0x20000000
#define TxD_OWC_1		0x10000000
#define TxD_CRS_1		0x08000000
#define TxD_DEF_1		0x04000000
#define TxD_INT_1		0x00800000
#define TxD_COL_1		0x00f00000
#define TxD_COL_SHIFT_1		20
#define TxD_ABORT_1		0x00080000
#define TxD_LAST_1		0x00010000
#define TxD_LEN_1		TxD_LEN
E 3
I 3
/* control bits */
#define	TxD_OWN_1		TxD_OWN		/* 0x80000000 */
D 5
#define	TxD_ERR_1		0x40000000
#define	TxD_UDF_1		0x20000000
#define	TxD_OWC_1		0x10000000
#define	TxD_CRS_1		0x08000000
#define	TxD_DEF_1		0x04000000
#define	TxD_INT_1		0x00800000
#define	TxD_COL_1		0x00f00000
#define		TxD_COL_SHIFT_1		20
#define	TxD_ABORT_1		0x00080000
#define	TxD_LAST_1		0x00010000
E 5
I 5
#define	TxD_ERR_1		0x40000000U
#define	TxD_UDF_1		0x20000000U
#define	TxD_OWC_1		0x10000000U
#define	TxD_CRS_1		0x08000000U
#define	TxD_DEF_1		0x04000000U
D 7
#define	TxD_INT_1		0x00800000U	/* XXX - original is 0x01000000 */
E 7
I 7
#define	TxD_INT_1		0x01000000U
#define	TxD_INT_1_NF4		0x00800000U
E 7
#define	TxD_COL_1		0x00f00000U
D 8
#define		TxD_COL_SHIFT_1		20U
E 8
I 8
#define		TxD_COL_SHIFT_1		20
E 8
#define	TxD_ABORT_1		0x00080000U
#define	TxD_LAST_1		0x00010000U
E 5
D 8
#define	TxD_LEN_1		TxD_LEN
E 8
I 8
#define	TxD_LEN_1		0x0000ffffU
E 8
E 3

/*
 * Tx descriptor control and status flags for format 2 and 3.
 */
D 3
/* common */
E 3
I 3
/* control bits */
E 3
D 7
#define TxD_OWN_2		TxD_OWN		/* 0x80000000 */
#define TxD_LEN_2		TxD_LEN
D 3

/* for control */
E 3
D 5
#define TxD_INT_2		0x40000000
#define TxD_LAST_2		0x20000000
#define TxD_TSO_2		0x10000000
#define TxD_CKSUM_IPv4_2	0x08000000
#define TxD_CKSUM_TCPUDP_2	0x04000000
D 3
#define TxD_TSO_SHIFT_2		14
E 3
I 3
#define		TxD_TSO_SHIFT_2		14
E 5
I 5
#define TxD_INT_2		0x40000000U
#define TxD_LAST_2		0x20000000U
#define TxD_TSO_2		0x10000000U
#define TxD_CKSUM_IPv4_2	0x08000000U
#define TxD_CKSUM_TCPUDP_2	0x04000000U
E 7
I 7
#define	TxD_OWN_2		TxD_OWN		/* 0x80000000 */
D 8
#define	TxD_LEN_2		TxD_LEN
E 8
#define	TxD_INT_2		0x40000000U
#define	TxD_LAST_2		0x20000000U
#define	TxD_TSO_2		0x10000000U
#define	TxD_CKSUM_IPv4_2	0x08000000U
#define	TxD_CKSUM_TCPUDP_2	0x04000000U
E 7
D 8
#define		TxD_TSO_SHIFT_2		14U
E 8
I 8
#define	TxD_MSS_2		0x03ffc000U
#define		TxD_MSS_SHIFT_2		14U
#define	TxD_LEN_2		0x00003fffU
E 8
E 5
E 3

D 3
/* for status */
E 3
I 3
/* status bits in txd1 or txd3 */
E 3
D 5
#define TxD_ERR_2		0x40000000
#define TxD_UDF_2		0x10000000
#define TxD_OWC_2		0x08000000
#define TxD_CRS_2		0x04000000
#define TxD_TOK_2		0x02000000
#define TxD_COL_2		0x00f00000
#define 	TxD_COL_SHIFT_2		20
#define TxD_DEF_2		0x00080000
#define TxD_ABORT_2		0x00040000
E 5
I 5
D 7
#define TxD_ERR_2		0x40000000U
#define TxD_UDF_2		0x10000000U
#define TxD_OWC_2		0x08000000U
#define TxD_CRS_2		0x04000000U
#define TxD_TOK_2		0x02000000U
#define TxD_COL_2		0x00f00000U
#define 	TxD_COL_SHIFT_2		20U
#define TxD_DEF_2		0x00080000U
#define TxD_ABORT_2		0x00040000U
E 7
I 7
#define	TxD_ERR_2		0x40000000U
#define	TxD_UDF_2		0x10000000U
#define	TxD_OWC_2		0x08000000U
#define	TxD_CRS_2		0x04000000U
#define	TxD_TOK_2		0x02000000U
#define	TxD_COL_2		0x00f00000U
D 8
#define		TxD_COL_SHIFT_2		20U
E 8
I 8
#define		TxD_COL_SHIFT_2		20
E 8
#define	TxD_DEF_2		0x00080000U
#define	TxD_ABORT_2		0x00040000U
E 7
E 5

D 3
/* txd2 */
E 3
I 3
/* vlan bits in txd2 of format 3 */
E 3
D 5
#define TxD_VLAN_EN		0x00040000
#define TxD_VTAG		0x0000ffff
E 5
I 5
D 7
#define TxD_VLAN_EN		0x00040000U
#define TxD_VTAG		0x0000ffffU
E 7
I 7
#define	TxD_VLAN_EN		0x00040000U
#define	TxD_VTAG		0x0000ffffU
E 7
E 5

D 3
/* rxd1 */
#define RxD_VLAN		0x00010000
#define RxD_VTAG		0x0000ffff

E 3
/*
D 3
 * Common rx descriptor bits
E 3
I 3
 * Rx descriptor control and status flags for format 1.
E 3
 */
I 3
/* common bits */
E 3
D 5
#define RxD_OWN			0x80000000
#define RxD_ERR			0x40000000
#define RxD_LEN			0x00003fff
E 5
I 5
D 7
#define RxD_OWN			0x80000000U
#define RxD_ERR			0x40000000U
#define RxD_LEN			0x00003fffU
E 7
I 7
#define	RxD_OWN			0x80000000U
#define	RxD_ERR			0x40000000U
#define	RxD_LEN			0x00003fffU
E 7
E 5

D 3
/*
 * Rx descriptor control and status flags for format 1.
 */
E 3
I 3
/* control and status bits */
E 3
D 7
#define RxD_OWN_1		RxD_OWN
#define RxD_ERR_1		RxD_ERR
D 5
#define RxD_FRAME_1		0x20000000
#define RxD_OVF_1		0x10000000
#define RxD_CRC_1		0x08000000
#define RxD_ERR4_1		0x04000000
#define RxD_ERR3_1		0x02000000
#define RxD_ERR2_1		0x01000000
#define RxD_ERR1_1		0x00800000
#define RxD_SUBSTRACT1_1	0x00040000
#define RxD_MISSED_1		0x00020000
#define RxD_VALID_1		0x00010000
E 5
I 5
#define RxD_FRAME_1		0x20000000U
#define RxD_OVF_1		0x10000000U
#define RxD_CRC_1		0x08000000U
#define RxD_ERR4_1		0x04000000U
#define RxD_ERR3_1		0x02000000U
#define RxD_ERR2_1		0x01000000U
#define RxD_ERR1_1		0x00800000U
#define RxD_SUBSTRACT1_1	0x00040000U
#define RxD_MISSED_1		0x00020000U
#define RxD_VALID_1		0x00010000U
E 5
#define RxD_LEN_1		RxD_LEN
E 7
I 7
#define	RxD_OWN_1		RxD_OWN
#define	RxD_ERR_1		RxD_ERR
#define	RxD_FRAME_1		0x20000000U
#define	RxD_OVF_1		0x10000000U
#define	RxD_CRC_1		0x08000000U
#define	RxD_ERR4_1		0x04000000U
#define	RxD_ERR3_1		0x02000000U
#define	RxD_ERR2_1		0x01000000U
#define	RxD_ERR1_1		0x00800000U
#define	RxD_SUBSTRACT1_1	0x00040000U
#define	RxD_MISSED_1		0x00020000U
#define	RxD_VALID_1		0x00010000U
#define	RxD_LEN_1		RxD_LEN
E 7

#define	RxD_1_BITS	\
	"\020"	\
	"\040OWN"	\
	"\037ERR"	\
	"\036FRAME"	\
	"\035OVF"	\
	"\034CRC"	\
	"\033ERR4"	\
	"\032ERR3"	\
	"\031ERR2"	\
	"\030ERR1"	\
	"\023SUBSTRACT1"	\
	"\022MISSED"	\
	"\021VALID"
D 7
	
E 7
I 7

E 7
/*
 * Rx descriptor control and status flags for format 2 and 3.
 */
I 3
/* control and status bits in rxd1 or rxd3 */
E 3
D 7
#define RxD_OWN_2		RxD_OWN
#define RxD_ERR_2		RxD_ERR
D 5
#define RxD_VALID_2		0x20000000
#define RxD_CKSUMOK_2		0x10000000
#define RxD_CKSUMP_2		0x0c000000
#define		RxD_CKSUMP_SHIFT_2	26
#define		CKSUMP_2		3
#define		CKSUMP_UDP_2		2
#define		CKSUMP_TCP_2		1
#define		CKSUMP_IP_2		0
#define RxD_SUBSTRACT1_2	0x02000000
#define RxD_FRAME_2		0x01000000
#define RxD_OVF_2		0x00800000
#define RxD_CRC_2		0x00400000
#define RxD_ERR4_2		0x00200000
#define RxD_ERR3_2		0x00100000
#define RxD_ERR2_2		0x00080000
#define RxD_ERR1_2		0x00040000
E 5
I 5
#define RxD_VALID_2		0x20000000U
#define RxD_CKSUMOK_2		0x10000000U
#define RxD_CKSUMP_2		0x0c000000U
E 7
I 7
#define	RxD_OWN_2		RxD_OWN
#define	RxD_ERR_2		RxD_ERR
#define	RxD_VALID_2		0x20000000U
#define	RxD_CKSUMP_2		0x1c000000U
E 7
#define		RxD_CKSUMP_SHIFT_2	26U
D 7
#define		CKSUMP_2		3U
#define		CKSUMP_UDP_2		2U
#define		CKSUMP_TCP_2		1U
#define		CKSUMP_IP_2		0U
#define RxD_SUBSTRACT1_2	0x02000000U
#define RxD_FRAME_2		0x01000000U
#define RxD_OVF_2		0x00800000U
#define RxD_CRC_2		0x00400000U
#define RxD_ERR4_2		0x00200000U
#define RxD_ERR3_2		0x00100000U
#define RxD_ERR2_2		0x00080000U
#define RxD_ERR1_2		0x00040000U
E 5
#define RxD_LEN_2		RxD_LEN
E 7
I 7
#define		CKSUMP_2		7U
#define		CKSUMP_UDP_2		6U
#define		CKSUMP_TCP_2		5U
#define		CKSUMP_IP_2		4U
#define		CKSUMP_IP_ERR_2		3U
#define		CKSUMP_UDP_ERR_2	2U
#define		CKSUMP_TCP_ERR_2	1U
#define		CKSUMP_NONE_2		0U
#define	RxD_SUBSTRACT1_2	0x02000000U
#define	RxD_FRAME_2		0x01000000U
#define	RxD_OVF_2		0x00800000U
#define	RxD_CRC_2		0x00400000U
#define	RxD_ERR4_2		0x00200000U
#define	RxD_ERR3_2		0x00100000U
#define	RxD_ERR2_2		0x00080000U
#define	RxD_ERR1_2		0x00040000U
#define	RxD_LEN_2		RxD_LEN
E 7

#define	RxD_2_BITS	\
	"\020"	\
	"\040OWN"	\
	"\037ERR"	\
	"\036VALID"	\
	"\035CKSUMOK"	\
	"\034CKSUMP_UDP"	\
	"\033CKSUMP_TCP"	\
	"\032SUBSTRACT1"	\
	"\031FRAME"	\
	"\030OVF"	\
	"\027CRC"	\
	"\026ERR4"	\
	"\025ERR3"	\
	"\024ERR2"	\
D 2
	"\023ERR1"	\

#define WAKEUPPATTERNS		5
#define WAKEUPMASKENTRIES	4

/* PHY defines */
#define PHY_OUI_MARVELL	0x5043
#define PHY_OUI_CICADA	0x03f1
#define PHYID1_OUI_MASK	0x03ff
#define PHYID1_OUI_SHFT	6
#define PHYID2_OUI_MASK	0xfc00
#define PHYID2_OUI_SHFT	10
#define PHY_INIT1	0x0f000
#define PHY_INIT2	0x0e00
#define PHY_INIT3	0x01000
#define PHY_INIT4	0x0200
#define PHY_INIT5	0x0004
#define PHY_INIT6	0x02000
#define PHY_GIGABIT	0x0100

#define PHY_TIMEOUT	0x1
#define PHY_ERROR	0x2

#define PHY_100		0x1
#define PHY_1000	0x2
#define PHY_HALF	0x100
E 2
I 2
	"\023ERR1"
I 3

/* vlan bits in rxd2 of format 3 */
D 5
#define RxD_VLAN		0x00010000
#define RxD_VTAG		0x0000ffff
E 5
I 5
D 7
#define RxD_VLAN		0x00010000U
#define RxD_VTAG		0x0000ffffU
E 7
I 7
#define	RxD_VLAN		0x00010000U
#define	RxD_VTAG		0x0000ffffU

#endif /* _NVENETREG_H_ */
E 7
E 5
E 3
E 2
E 1
