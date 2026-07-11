h65533
s 00103/00044/00479
d D 1.9 10/04/07 22:32:15 mrym 9 8
c 2.6.6 
e
s 00007/00000/00516
d D 1.8 09/01/30 01:30:06 mrym 8 7
c 
e
s 00233/00201/00283
d D 1.7 08/12/31 23:49:42 mrym 7 6
c 2.6.
e
s 00003/00002/00481
d D 1.6 07/05/19 21:04:32 mrym 6 5
c for supporting 8100
e
s 00001/00000/00482
d D 1.5 06/04/30 03:03:43 mrym 5 4
c 8169sc added
e
s 00085/00064/00397
d D 1.4 05/12/18 17:44:05 mrym 4 3
c 2.0.0 rtl8168 supported
e
s 00008/00008/00453
d D 1.3 05/04/04 01:08:05 mrym 3 2
c volatile removed for ddi_put/get routines
e
s 00077/00009/00384
d D 1.2 05/01/10 23:23:02 mrym 2 1
c fix for flow control
e
s 00393/00000/00000
d D 1.1 04/05/24 22:10:55 mrym 1 0
c date and time created 04/05/24 22:10:55 by mrym
e
u
U
f e 0
t
T
I 1
/*
 * %W% %E%
D 4
 * Macro definitions for Realtek 8169 giga ethernet controler
 * based on Realtek RTL8169 data sheet
E 4
I 4
 * Macro definitions for Realtek RTL8169/RTL8168 giga bit ethernet controler
 * based on Realtek RTL8169/RTL8168 data sheet
E 4
 * This file is public domain. Coded by M.Murayama (KHF04453@nifty.com)
 */
I 9
#ifndef	_RTL8169REG_H_
#define	_RTL8169REG_H_
E 9

/*
 * Register offset
 */
#define	IDR		0x00	/* Base of ID registers */
#define	MAR		0x08	/* Base of multicast registers */
D 2
#define	DTCCR		0x10	/* Dump Tally Counter */
E 2
I 2
D 4
#define	DTCCRL		0x10	/* Dump Tally Counter (low) */
#define	DTCCRH		0x14	/* Dump Tally Counter (high) */
E 4
I 4
#define	DTCCR		0x10	/* Dump Tally Counter */
#define	DTCCRL		0x10	/* low 32-bit of DTCCR */
#define	DTCCRH		0x14	/* high 32-bit of DTCCR */
E 4
E 2
#define	TNPDS		0x20	/* Transmit Normal Priority Descriptors */
#define	TNPDSL		0x20	/* low 32-bit of TNPDS */
#define	TNPDSH		0x24	/* high 32-bit of TNPDS */
#define	THPDS		0x28	/* Transmit High Priority Descriptors */
#define	THPDSL		0x28	/* low 32-bit of THPDS */
D 4
#define	THPDSH		0x2c	/* low 32-bit of THPDS */
#define	FLASH		0x30	/* FLASH memory read/write register */
#define	ERBCR		0x34	/* Eealy Receive Byte Count register */
#define	ERSR		0x36	/* Early Rx Status register */
E 4
I 4
#define	THPDSH		0x2c	/* high 32-bit of THPDS */
#define	FLASH		0x30	/* FLASH memory read/write register (8169) */
#define	ERBCR		0x34	/* Eealy Receive Byte Count register (8169) */
#define	ERSR		0x36	/* Early Rx Status register (8169) */
E 4
#define	CR		0x37	/* Command register */
#define	TPPoll		0x38	/* Transmit Priority Polling register*/
#define	IMR		0x3c	/* Interrupt Mask register */
#define	ISR		0x3e	/* Interrupt Status register */
#define	TCR		0x40	/* Transmit Configuration register */
#define	RCR		0x44	/* Receive Configuration register */
#define	TCTR		0x48	/* Timer CounT register */
D 4
#define	MPC		0x4c	/* Missed packet counter */
E 4
I 4
#define	MPC		0x4c	/* Missed packet counter (8169) */
E 4
#define	CR9346		0x50	/* 93C46 command register */
#define	CFG0		0x51	/* Configration register 0 */
#define	CFG1		0x52	/* Configration register 1 */
#define	CFG2		0x53	/* Configration register 2 */
#define	CFG3		0x54	/* Configration register 3 */
#define	CFG4		0x55	/* Configration register 4 */
I 4
#define	CFG5		0x56	/* Configration register 5 (8169) */
E 4
#define	TimerInt	0x58	/* Timer Interrupt register */
D 4
#define	MULINT		0x5c	/* Multiple Interrupt select */
E 4
I 4
#define	MULINT		0x5c	/* Multiple Interrupt select (8169) */
E 4
#define	PHYAR		0x60	/* PHY Access Register */
D 4
#define	TBICSR		0x64	/* TBI Control and Status regiser 0 */
E 4
I 4
#define	TBICSR		0x64	/* TBI Control and Status regiser (8169) */
E 4
#define	TBIANAR		0x68	/* TBI Auto Negotiation Advertisement register*/
#define	TBILPAR		0x6a	/* TBI Auto Negotiation Link Partner register */
#define	PHYS		0x6c	/* PHY status */
I 9
#define	GPIO		0x6e	/* 8168 */
#define	PMCH		0x6f	/* 8168 */
#define	ERIDR		0x70	/* 8168 */
#define	ERIAR		0x74	/* 8168 */
#define	EPHY_RXER_NUM	0x7c	/* 8168 */
E 9
I 7
#define	EPHYAR		0x80	/* PCI-E PHY Access Register */
E 7
#define	Wakeup0		0x84	/* Power Management Wakeup register 0 */
#define	Wakeup1		0x8c	/* Power Management Wakeup register 1 */
D 4
#define	Wakeup2LD	0x94	/* Power Management Wakeup register 1 */
#define	Wakeup2HD	0x9C	/* Power Management Wakeup register 1 */
#define	Wakeup3LD	0xa4	/* Power Management Wakeup register 1 */
#define	Wakeup3HD	0xaC	/* Power Management Wakeup register 1 */
#define	Wakeup4LD	0xb4	/* Power Management Wakeup register 1 */
#define	Wakeup4HD	0xbC	/* Power Management Wakeup register 1 */
E 4
I 4
#define	Wakeup2LD	0x94	/* Power Management Wakeup register 2 */
#define	Wakeup2HD	0x9C	/* Power Management Wakeup register 2 */
#define	Wakeup3LD	0xa4	/* Power Management Wakeup register 3 */
#define	Wakeup3HD	0xaC	/* Power Management Wakeup register 3 */
#define	Wakeup4LD	0xb4	/* Power Management Wakeup register 4 */
#define	Wakeup4HD	0xbC	/* Power Management Wakeup register 4 */
I 9
#define	OCPDR		0xb0	/* (8168) */
#define	OCPAR		0xb4	/* (8168) */
E 9
E 4
#define	CRC0		0xc4	/* 16bit CRC of wakeup */
#define	CRC1		0xc6	/* 16bit CRC of wakeup */
#define	CRC2		0xc8	/* 16bit CRC of wakeup */
#define	CRC3		0xca	/* 16bit CRC of wakeup */
#define	CRC4		0xcc	/* 16bit CRC of wakeup */
#define	RMS		0xda	/* Rx packet Maximum Size */
I 9
#define	EFUSEAR		0xdc	/* E-FUSE access register */
E 9
#define	CpCR		0xe0	/* C+ Command register */
I 8
#define	INTRMOD		0xe2	/* interrupt moderation */
E 8
#define	RDSAR		0xe4	/* Receive Descriptor Start Address */
#define	RDSARL		0xe4	/* low 32-bit of RDSAR */
#define	RDSARH		0xe8	/* high 32-bit of RDSAR */
D 4
#define	ETThR		0xec	/* Early Transnit threshold register */
#define	FER		0xf0	/* Function Event register */
#define	FEMR		0xf4	/* Function Event Mask register */
#define	FFEMR		0xf8	/* Function forcs evet register */
E 4
I 4
#define	ETThR		0xec	/* Early Transnit threshold register (8169) */
#define	MTPS		ETThR	/* Max Tx packet Size registger (8168) */
#define	FER		0xf0	/* Function Event register (8169) */
#define	FEMR		0xf4	/* Function Event Mask register (8169) */
#define	FFEMR		0xf8	/* Function forcs evet register (8169) */
E 4

I 7
/* 8168 and 810x */
#define	CSIDR		0x64
#define	CSIAR		0x68
#define	DBGREG		0xd1
I 9
#define	PHYIO		0xf8
E 9

E 7
I 2
/* Tally Counter Command register */
#define	DTCCR_ADDR	0xffffffc0	/* low 32 bit of base address */
#define	DTCCR_CMD	0x00000008

/* Tally counter offsets */
#define	TC_TxOK_8	0	/* 8byte */
#define	TC_RxOK_8	8	/* 8byte */
#define	TC_TxEr_8	16	/* 8byte */
#define	TC_RxEr_4	24	/* 4byte */
#define	TC_MissPkt_2	28	/* 2byte */
#define	TC_FAE_2	30	/* 2byte */
#define	TC_Tx1Col_4	32	/* 4byte */
#define	TC_TxMCol_4	36	/* 4byte */
#define	TC_RxOkPhy_8	40	/* 8byte */
#define	TC_RxOkBrd_8	48	/* 8byte */
#define	TC_RxOkMu_4	56	/* 4byte */
#define	TC_TxAbt_2	60	/* 2byte */
#define	TC_TxUndrn_2	62	/* 2byte */

struct rtl8169_tally_counters {
	uint64_t	tc_txok;	/* 8byte */

	uint64_t	tc_rxok;	/* 8byte */

	uint64_t	tc_txer;	/* 8byte */

	uint32_t	tc_rxer;	/* 4byte */
	uint16_t	tc_misspkt;	/* 2byte */
	uint16_t	tc_fae;		/* 2byte */

	uint32_t	tc_tx1col;	/* 4byte */
	uint32_t	tc_txmcol;	/* 4byte */

	uint64_t	tc_rxokphy;	/* 8byte */

	uint64_t	tc_rxokbrd;	/* 8byte */

	uint32_t	tc_rxokmu;	/* 4byte */
	uint16_t	tc_txabt;	/* 2byte */
	uint16_t	tc_txundrn;	/* 2byte */
};

#define	TC_SIZE		64	/* 64 bit aligned */

E 2
D 4
/* ERSR Early Rx Status, offset 0x36 */
E 4
I 4
/* ERSR Early Rx Status, offset 0x36 (8169only) */
E 4
D 7
#define	ERSR_ERGood	0x08		/* Early Rx Good packet */
#define	ERSR_ERBad	0x04		/* Early Rx Bad packet */
#define	ERSR_EROVW	0x02		/* Early Rx OverWrite */
#define	ERSR_EROK	0x01		/* Early Rx OK */
E 7
I 7
#define	ERSR_ERGood	0x08U		/* Early Rx Good packet */
#define	ERSR_ERBad	0x04U		/* Early Rx Bad packet */
#define	ERSR_EROVW	0x02U		/* Early Rx OverWrite */
#define	ERSR_EROK	0x01U		/* Early Rx OK */
E 7

/* CR : Command register,  offset 0x37  */
D 7
#define	CR_RST		0x10		/* Reset */
#define	CR_RE		0x08		/* Receiver enable */
#define	CR_TE		0x04		/* Transmitter enable */
E 7
I 7
#define	CR_STOP		0x80U		/* Stop request (8168C/CP) */
#define	CR_RST		0x10U		/* Reset */
#define	CR_RE		0x08U		/* Receiver enable */
#define	CR_TE		0x04U		/* Transmitter enable */
E 7

#define	CR_BITS	"\020\005RST\004RE\003TE"

/* TPPoll: Transmit Priority Polling,  offset 0x38 */
D 7
#define	TPPoll_HPQ	0x80		/* High priority queue polling */
#define	TPPoll_NPQ	0x40		/* Normal priority queue polling */
#define	TPPoll_FSWInt	0x01		/* Forced software interrupt */
E 7
I 7
#define	TPPoll_HPQ	0x80U		/* High priority queue polling */
#define	TPPoll_NPQ	0x40U		/* Normal priority queue polling */
#define	TPPoll_FSWInt	0x01U		/* Forced software interrupt */
E 7

/* IMR  & ISR */
D 4
#define	INTR_SERR	0x8000		/* System Error Interrupt */
E 4
I 4
D 7
#define	INTR_SERR	0x8000		/* System Error Interrupt (8169) */
E 4
#define	INTR_TimeOut	0x4000		/* Time out interrupt */
#define	INTR_SWInt	0x0100		/* Software Interrupt */
#define	INTR_TDU	0x0080		/* Tx Descriptor Unavailable */
#define	INTR_FOVW	0x0040		/* Rx FIFO overflow */
D 4
#define	INTR_PUN	0x0020		/* Packet Underrun/Link change */
E 4
I 4
#define	INTR_PUN	0x0020		/* Packet Underrun/Link change (8169)*/
E 7
I 7
#define	INTR_SERR	0x8000U		/* System Error Interrupt (8169) */
#define	INTR_TimeOut	0x4000U		/* Time out interrupt */
#define	INTR_SWInt	0x0100U		/* Software Interrupt */
#define	INTR_TDU	0x0080U		/* Tx Descriptor Unavailable */
#define	INTR_FOVW	0x0040U		/* Rx FIFO overflow */
#define	INTR_PUN	0x0020U		/* Packet Underrun/Link change (8169)*/
E 7
#define	INTR_LinkChg	INTR_PUN	/* Link change (8168)*/
E 4
D 7
#define	INTR_RDU	0x0010		/* Rx Descriptor Unavailable */
#define	INTR_TER	0x0008		/* Transmit Error */
#define	INTR_TOK	0x0004		/* Transmit OK */
#define	INTR_RER	0x0002		/* Receive Error */
#define	INTR_ROK	0x0001		/* Receive OK */
E 7
I 7
#define	INTR_RDU	0x0010U		/* Rx Descriptor Unavailable */
#define	INTR_TER	0x0008U		/* Transmit Error */
#define	INTR_TOK	0x0004U		/* Transmit OK */
#define	INTR_RER	0x0002U		/* Receive Error */
#define	INTR_ROK	0x0001U		/* Receive OK */
E 7

#define	INTR_BITS	\
	"\020"	\
	"\020SERR"	\
	"\017TimeOut"	\
	"\011SWInt"	\
	"\010TDU"	\
	"\007FOVW"	\
	"\006PUN"	\
	"\005RDU"	\
	"\004TER"	\
	"\003TOK"	\
	"\002RER"	\
	"\001ROK"

/* TCR: Transmit Configuration register */
D 4
#define	TCR_MACVER	0x7c800000	/* MAC version */		
D 2
#define	TCR_MACVER_B	0x00000000
#define	TCR_MACVER_D	0x00800000
#define	TCR_MACVER_E	0x04000000
E 2
I 2
#define		TCR_MACVER_B	0x00000000
#define		TCR_MACVER_D	0x00800000
#define		TCR_MACVER_E	0x04000000
#define		TCR_MACVER_F	0x10000000
E 4
I 4
D 7
#define	TCR_HWVERID	0x7c800000	/* MAC version */		
#define		TCR_HWVERID_8169	0x00000000
#define		TCR_HWVERID_8169S_D	0x00800000	/* 8269S rev.D */
#define		TCR_HWVERID_8169S_E	0x04000000	/* 8269S rev.E */
#define		TCR_HWVERID_8169SB	0x10000000	/* 8169S rev.F */
I 5
D 6
#define		TCR_HWVERID_8169SC	0x18000000
E 6
I 6
#define		TCR_HWVERID_8110SC	0x18000000
E 6
E 5
#define		TCR_HWVERID_8168	0x20000000
#define		TCR_HWVERID_8168B_B	0x30000000	/* 8168B rev.B */
#define		TCR_HWVERID_8168B_C	0x38000000	/* 8168B rev.C */
D 6
#define		TCR_HWVERID_8100E	0x30800000
E 6
#define		TCR_HWVERID_8101E	0x34000000
I 6
#define		TCR_HWVERID_8100E_A	0x30800000
#define		TCR_HWVERID_8100E_B	0x38800000
E 6
E 4
E 2
#define	TCR_IFG		0x03080000	/* Interframe Gap */
#define	TCR_IFG_802_3	0x03000000	/* 802.3 standard */
#define	TCR_LBK		0x00060000	/* Loopback test */
E 7
I 7
#define	TCR_IFG		0x03080000U	/* Interframe Gap */
D 9
#define	TCR_IFG_802_3	0x03000000U	/* 802.3 standard */
E 9
I 9
#define		TCR_IFG_802_3		0x03000000U	/* 802.3 standard */
#define		TCR_IFG_HALF_8169	0x02000000U
E 9
#define	TCR_LBK		0x00060000U	/* Loopback test */
E 7
D 9
#define	TCR_LBK_SHIFT		17
D 7
#define	TCR_LBK_NORMAL		(0 << TCR_LBK_SHIFT)
#define	TCR_LBK_DLBK		(1 << TCR_LBK_SHIFT)
#define	TCR_CRC		0x00010000	/* Inhibit Appending CRC */
#define	TCR_MXDMA	0x00000700
E 7
I 7
#define	TCR_LBK_NORMAL		(0U << TCR_LBK_SHIFT)
#define	TCR_LBK_DLBK		(1U << TCR_LBK_SHIFT)
E 9
I 9
#define		TCR_LBK_SHIFT		17
#define		TCR_LBK_NORMAL		(0U << TCR_LBK_SHIFT)
#define		TCR_LBK_DLBK		(1U << TCR_LBK_SHIFT)
E 9
#define	TCR_CRC		0x00010000U	/* Inhibit Appending CRC */
#define	TCR_MXDMA	0x00000700U
E 7
D 2
#define	TCR_MXDMA_SHIFT		8
E 2
I 2
D 9
#define	TCR_MXDMA_SHIFT	8
E 2
#define	TCR_MXDMA_BASE		16
D 7
#define	TCR_MXDMA_16		(0 << TCR_MXDMA_SHIFT)
#define	TCR_MXDMA_32		(1 << TCR_MXDMA_SHIFT)
#define	TCR_MXDMA_64		(2 << TCR_MXDMA_SHIFT)
#define	TCR_MXDMA_128		(3 << TCR_MXDMA_SHIFT)
#define	TCR_MXDMA_256		(4 << TCR_MXDMA_SHIFT)
#define	TCR_MXDMA_512		(5 << TCR_MXDMA_SHIFT)
#define	TCR_MXDMA_1024		(6 << TCR_MXDMA_SHIFT)
D 2
#define	TCR_MXDMA_UNLIMIT	(7 << TCR_MXDMA_SHIFT)
E 2
I 2
#define	TCR_MXDMA_UNLIMITED	(7 << TCR_MXDMA_SHIFT)
E 7
I 7
#define	TCR_MXDMA_16		(0U << TCR_MXDMA_SHIFT)
#define	TCR_MXDMA_32		(1U << TCR_MXDMA_SHIFT)
#define	TCR_MXDMA_64		(2U << TCR_MXDMA_SHIFT)
#define	TCR_MXDMA_128		(3U << TCR_MXDMA_SHIFT)
#define	TCR_MXDMA_256		(4U << TCR_MXDMA_SHIFT)
#define	TCR_MXDMA_512		(5U << TCR_MXDMA_SHIFT)
#define	TCR_MXDMA_1024		(6U << TCR_MXDMA_SHIFT)
#define	TCR_MXDMA_UNLIMITED	(7U << TCR_MXDMA_SHIFT)
E 9
I 9
#define		TCR_MXDMA_SHIFT		8
#define		TCR_MXDMA_BASE		16
#define		TCR_MXDMA_16		(0U << TCR_MXDMA_SHIFT)
#define		TCR_MXDMA_32		(1U << TCR_MXDMA_SHIFT)
#define		TCR_MXDMA_64		(2U << TCR_MXDMA_SHIFT)
#define		TCR_MXDMA_128		(3U << TCR_MXDMA_SHIFT)
#define		TCR_MXDMA_256		(4U << TCR_MXDMA_SHIFT)
#define		TCR_MXDMA_512		(5U << TCR_MXDMA_SHIFT)
#define		TCR_MXDMA_1024		(6U << TCR_MXDMA_SHIFT)
#define		TCR_MXDMA_UNLIMITED	(7U << TCR_MXDMA_SHIFT)
E 9
E 7
E 2

/* RCR: Receive Configuration register */

/* rx_mode_bits */
D 2
#define	RCR_MulERINT	0x01000000
E 2
I 2
D 4
#define	RCR_MulERINT	0x00100000
E 4
I 4
D 7
#define	RCR_MulERINT	0x00100000	/* 8169only */
E 7
I 7
D 9
#define	RCR_MulERINT	0x00100000U	/* 8169only */
E 9
I 9
#define	RCR_MulERINT	0x00800000U	/* 8169only */
E 9
E 7
E 4
E 2

D 7
#define	RCR_RER8	0x00010000
#define	RCR_RXFTH	0x0000e000	/* Receive FIFO threshold */
E 7
I 7
#define	RCR_RER8	0x00010000U
I 8
D 9
#define	RCR_128_INT	0x00008000U	/* 8168 */
#define	RCR_FET_MULTI	0x00004000U	/* 8168 */
#define	RCR_HALF_REFET	0x00002000U	/* 8168 */
E 9
I 9
#define	RCR_128_INT	0x00008000U
#define	RCR_FET_MULTI	0x00004000U
#define	RCR_HALF_REFET	0x00002000U
E 9
E 8
#define	RCR_RXFTH	0x0000e000U	/* Receive FIFO threshold */
E 7
D 9
#define	RCR_RXFTH_SHIFT	13	
D 7
#define	RCR_RXFTH_64		(2 << RCR_RXFTH_SHIFT)
#define	RCR_RXFTH_128		(3 << RCR_RXFTH_SHIFT)
#define	RCR_RXFTH_256		(4 << RCR_RXFTH_SHIFT)
#define	RCR_RXFTH_512		(5 << RCR_RXFTH_SHIFT)
#define	RCR_RXFTH_1024		(6 << RCR_RXFTH_SHIFT)
D 4
#define	RCR_RXFTH_NONE		(7 << RCR_RXFTH_SHIFT)
E 4
I 4
#define	RCR_RXFTH_SF		(7 << RCR_RXFTH_SHIFT)
E 7
I 7
#define	RCR_RXFTH_64		(2U << RCR_RXFTH_SHIFT)
#define	RCR_RXFTH_128		(3U << RCR_RXFTH_SHIFT)
#define	RCR_RXFTH_256		(4U << RCR_RXFTH_SHIFT)
#define	RCR_RXFTH_512		(5U << RCR_RXFTH_SHIFT)
#define	RCR_RXFTH_1024		(6U << RCR_RXFTH_SHIFT)
#define	RCR_RXFTH_SF		(7U << RCR_RXFTH_SHIFT)
E 9
I 9
#define		RCR_RXFTH_SHIFT		13	
#define		RCR_RXFTH_64		(2U << RCR_RXFTH_SHIFT)
#define		RCR_RXFTH_128		(3U << RCR_RXFTH_SHIFT)
#define		RCR_RXFTH_256		(4U << RCR_RXFTH_SHIFT)
#define		RCR_RXFTH_512		(5U << RCR_RXFTH_SHIFT)
#define		RCR_RXFTH_1024		(6U << RCR_RXFTH_SHIFT)
#define		RCR_RXFTH_SF		(7U << RCR_RXFTH_SHIFT)
E 9
E 7
E 4

D 7
#define	RCR_MXDMA	0x00000700	/* */
E 7
I 7
#define	RCR_MXDMA	0x00000700U	/* */
E 7
D 9
#define	RCR_MXDMA_SHIFT	8
D 7
#define	RCR_MXDMA_64		(2 << RCR_MXDMA_SHIFT)
#define	RCR_MXDMA_128		(3 << RCR_MXDMA_SHIFT)
#define	RCR_MXDMA_256		(4 << RCR_MXDMA_SHIFT)
#define	RCR_MXDMA_512		(5 << RCR_MXDMA_SHIFT)
#define	RCR_MXDMA_1024		(6 << RCR_MXDMA_SHIFT)
D 2
#define	RCR_MXDMA_UNLIMIT	(7 << RCR_MXDMA_SHIFT)
E 2
I 2
#define	RCR_MXDMA_UNLIMITED	(7 << RCR_MXDMA_SHIFT)
E 2
#define	RCR_9356SEL	0x00000040	/* EEPROM is 9356 */
#define	RCR_AER		0x00000020	/* Accept Error packet */
#define	RCR_AR		0x00000010	/* Accept runt */
#define	RCR_AB		0x00000008	/* Accept broadcast */
#define	RCR_AM		0x00000004	/* Accept Multicast */
#define	RCR_APM		0x00000002	/* Accept physical match */
#define	RCR_AAP		0x00000001	/* Accept all physical */
E 7
I 7
#define	RCR_MXDMA_64		(2U << RCR_MXDMA_SHIFT)
#define	RCR_MXDMA_128		(3U << RCR_MXDMA_SHIFT)
#define	RCR_MXDMA_256		(4U << RCR_MXDMA_SHIFT)
#define	RCR_MXDMA_512		(5U << RCR_MXDMA_SHIFT)
#define	RCR_MXDMA_1024		(6U << RCR_MXDMA_SHIFT)
#define	RCR_MXDMA_UNLIMITED	(7U << RCR_MXDMA_SHIFT)
E 9
I 9
#define		RCR_MXDMA_SHIFT		8
#define		RCR_MXDMA_64		(2U << RCR_MXDMA_SHIFT)
#define		RCR_MXDMA_128		(3U << RCR_MXDMA_SHIFT)
#define		RCR_MXDMA_256		(4U << RCR_MXDMA_SHIFT)
#define		RCR_MXDMA_512		(5U << RCR_MXDMA_SHIFT)
#define		RCR_MXDMA_1024		(6U << RCR_MXDMA_SHIFT)
#define		RCR_MXDMA_UNLIMITED	(7U << RCR_MXDMA_SHIFT)
E 9
#define	RCR_9356SEL	0x00000040U	/* EEPROM is 9356 */
#define	RCR_AER		0x00000020U	/* Accept Error packet */
#define	RCR_AR		0x00000010U	/* Accept runt */
#define	RCR_AB		0x00000008U	/* Accept broadcast */
#define	RCR_AM		0x00000004U	/* Accept Multicast */
#define	RCR_APM		0x00000002U	/* Accept physical match */
#define	RCR_AAP		0x00000001U	/* Accept all physical */
E 7

#define	RCR_ACCEPT_MODE		\
	(RCR_AER | RCR_AR | RCR_AB | RCR_AM | RCR_APM | RCR_AAP)

I 2
D 9
#define	RCR_MASK	\
	(RCR_MulERINT | RCR_RER8 | RCR_RXFTH | RCR_MXDMA | \
	 RCR_9356SEL | RCR_ACCEPT_MODE)
E 9
I 9
#define RCR_MASK \
	(RCR_MulERINT | RCR_RER8 | \
	RCR_128_INT | RCR_FET_MULTI | RCR_HALF_REFET | \
	RCR_RXFTH | RCR_MXDMA | \
	RCR_9356SEL | RCR_ACCEPT_MODE)
E 9

D 9

E 9
E 2
#define	RCR_BITS	\
D 9
  "\020\031MulInt\021RER8\0079356SEL\006AER\005AR\004AB\003AM\002APM\001AAP"
E 9
I 9
	"\020"	\
	"\030MulERInt"	\
	"\021RER8"	\
	"\020128INT"	\
	"\017FET_MULTI"	\
	"\016HALF_REFET"	\
	"\0079356SEL"	\
	"\006AER"	\
	"\005AR"	\
	"\004AB"	\
	"\003AM"	\
	"\002APM"	\
	"\001AAP"
E 9

/* CR9346 : 0x50 */
D 7
#define	CR9346_EEM	0xc0
#define	CR9346_EEM_SHIFT	6	
#define		CR9346_EEM_NORMAL	(0 << CR9346_EEM_SHIFT)
#define		CR9346_EEM_AUTOLD	(1 << CR9346_EEM_SHIFT)
#define		CR9346_EEM_PROGRAM	(2 << CR9346_EEM_SHIFT)
#define		CR9346_EEM_WE		(3 << CR9346_EEM_SHIFT)
#define	CR9346_EECS	0x08
#define	CR9346_EESK	0x04
#define	CR9346_EEDI	0x02
E 7
I 7
#define	CR9346_EEM	0xc0U
D 9
#define	CR9346_EEM_SHIFT	6
E 9
I 9
#define		CR9346_EEM_SHIFT	6
E 9
#define		CR9346_EEM_NORMAL	(0U << CR9346_EEM_SHIFT)
#define		CR9346_EEM_AUTOLD	(1U << CR9346_EEM_SHIFT)
#define		CR9346_EEM_PROGRAM	(2U << CR9346_EEM_SHIFT)
#define		CR9346_EEM_WE		(3U << CR9346_EEM_SHIFT)
#define	CR9346_EECS	0x08U
#define	CR9346_EESK	0x04U
#define	CR9346_EEDI	0x02U
E 7
D 9
#define	CR9346_EEDI_SHIFT	1
E 9
I 9
#define		CR9346_EEDI_SHIFT	1
E 9
D 7
#define	CR9346_EEDO	0x01
E 7
I 7
#define	CR9346_EEDO	0x01U
E 7
D 9
#define	CR9346_EEDO_SHIFT	0
E 9
I 9
#define		CR9346_EEDO_SHIFT	0
E 9

/* Config 0  offset 0x51 */

/* Config 1  offset 0x52 */
D 7
#define	CFG1_LEDS	0xc0
D 4
#define	CFG1_DVRLOAD	0x20
#define	CFG1_LWACT	0x10
E 4
I 4
#define	CFG1_DVRLOAD	0x20	/* 8169only /
#define	CFG1_LWACT	0x10	/* 8169only /
E 4
#define	CFG1_MEMMAP	0x08
#define	CFG1_IOMAP	0x04
#define	CFG1_VPD	0x02
#define	CFG1_PMEn	0x01
E 7
I 7
#define	CFG1_LEDS	0xc0U
#define	CFG1_LEDS1	0x80U
#define	CFG1_LEDS0	0x40U
#define	CFG1_DVRLOAD	0x20U	/* 8169 */
#define	CFG1_LWACT	0x10U	/* 8169 */
#define	CFG1_SPEEDDOWN	0x10U	/* 8168 */
#define	CFG1_MEMMAP	0x08U
#define	CFG1_IOMAP	0x04U
#define	CFG1_VPD	0x02U
#define	CFG1_PMEn	0x01U
E 7

/* Config 2  offset 0x53 */
D 7
#define	CFG2_AuxStatus		0x10
D 4
#define	CFG2_PCIBusWidth	0x08	/* 1:64bit 0:32bit */
#define	CFG2_PCICLKF		0x07
E 4
I 4
#define	CFG2_PCIBusWidth	0x08	/* 1:64bit 0:32bit (8169) */
#define	CFG2_PCICLKF		0x07	/* 8169 */
E 4
#define	CFG2_PCICLKF_33		0x00
#define	CFG2_PCICLKF_66		0x01
E 7
I 7
#define	CFG2_AuxStatus		0x10U
#define	CFG2_PCIBusWidth	0x08U	/* 1:64bit 0:32bit (8169) */
#define	CFG2_PCICLKF		0x07U	/* 8169 */
#define	CFG2_PCICLKF_33		0x00U
#define	CFG2_PCICLKF_66		0x01U	/* unreliable */
E 7

I 2
#define	CFG2_BITS	\
	"\020"		\
	"\005AuxStatus"	\
	"\004PCI64bit"

E 2
/* Config 3  offset 0x54 */
D 7
#define	CFG3_GNTSel	0x80	/* Gnt Select 0:No delay 1:delay one clock R */
#define	CFG3_MAGIC	0x20	/* Magic packet */
#define	CFG3_LINKUP	0x10
D 4
#define	CFG3_CARDB_EN	0x08	/* CardBus Enable (RO) */
#define	CFG3_CLKRUN_EN	0x04	/* CLK RUN Enable (RO) */
#define	CFG3_FUNCREGEN	0x02
#define	CFG3_FBTBEN	0x01
E 4
I 4
#define	CFG3_CARDB_EN	0x08	/* CardBus Enable (RO) (8169) */
#define	CFG3_CLKRUN_EN	0x04	/* CLK RUN Enable (RO) (8169) */
#define	CFG3_FUNCREGEN	0x02	/* 8169 */
#define	CFG3_FBTBEN	0x01	/* 8169 */
#define	CFG3_BEACON_EN	0x01	/* 8168 */
E 7
I 7
#define	CFG3_GNTSel	0x80U	/* Gnt Select 0:No delay 1:delay one clock R */
#define	CFG3_MAGIC	0x20U	/* Magic packet */
#define	CFG3_LINKUP	0x10U
#define	CFG3_CARDB_EN	0x08U	/* CardBus Enable (RO) (8169) */
#define	CFG3_CLKRUN_EN	0x04U	/* CLK RUN Enable (RO) (8169) */
#define	CFG3_JUMBO	0x04U	/* enable jumbo frame (8168) */
#define	CFG3_FUNCREGEN	0x02U	/* (8169) */
#define	CFG3_FBTBEN	0x01U	/* (8169) */
#define	CFG3_BEACON_EN	0x01U	/* (8168) */
E 7
E 4

/* Configration register 4  offset 0x55 */
D 4
#define	CFG4_LWPMT	0x10
#define	CFG4_LWPTN	0x04	/* */
E 4
I 4
D 7
#define	CFG4_LWPMT	0x10	/* 8169 */
#define	CFG4_LWPTN	0x04	/* 8169 */
E 7
I 7
#define	CFG4_LWPMT	0x10U	/* (8169) */
#define	CFG4_LWPTN	0x04U	/* (8169) */
#define	CFG4_JUMBO	0x02U	/* enable jumbo frame (8168) */
E 7
E 4

/* Configration register 5  offset 0x56 */
D 7
#define	CFG5_BWF	0x40	/* Broadcast Wakeup Frame */
#define	CFG5_MWF	0x20	/* Multicast Wakeup Frame */
#define	CFG5_UWF	0x10	/* Unicast Wakeup Frame */
D 4
#define	CFG5_LANWAKE	0x02	/* LANWake Signal 1:Enable 0:Disable */
#define	CFG5_PME_STS	0x01	/* PME status bit */
E 4
I 4
#define	CFG5_LANWAKE	0x02	/* LANWake Signal 1:Enable 0:Disable (8169) */
#define	CFG5_PME_STS	0x01	/* PME status bit (8169) */
E 7
I 7
#define	CFG5_BWF	0x40U	/* Broadcast Wakeup Frame */
#define	CFG5_MWF	0x20U	/* Multicast Wakeup Frame */
#define	CFG5_UWF	0x10U	/* Unicast Wakeup Frame */
#define	CFG5_LANWAKE	0x02U	/* LANWake Signal 1:Enable 0:Disable (8169) */
#define	CFG5_PME_STS	0x01U	/* PME status bit (8169) */
E 7
E 4

/* Basic mode status register */
/* Auto-negotiation Advertisement register */
/* Auto-negotiation Link Partner Ability register */
/* Auto-negotiation Expansion register */
/* Config5 */

/* PHYAR: PHY  Accress Register: offset 0x60 */
D 7
#define	PHYAR_FLAG	0x80000000
#define	PHYAR_REGADDR	0x001f0000
E 7
I 7
#define	PHYAR_FLAG	0x80000000U
#define	PHYAR_REGADDR	0x001f0000U
E 7
D 9
#define	PHYAR_REGADDR_SHIFT	16
E 9
I 9
#define		PHYAR_REGADDR_SHIFT	16
E 9
D 7
#define	PHYAR_DATA	0x0000ffff
E 7
I 7
#define	PHYAR_DATA	0x0000ffffU
E 7

D 4
/* TBICSR: Ten Bit Interface Control and Status Register: offset 0x64 */
E 4
I 4
/* TBICSR: Ten Bit Interface Control and Status Register: offset 0x64 (8169) */
E 4
D 7
#define	TBICSR_Reset	0x80000000	/* TBI reset */
#define	TBICSR_LoopBack	0x40000000
#define	TBICSR_NWEn	0x20000000	/* TBI auto negotiation enable */
#define	TBICSR_ReNW	0x10000000	/* TBI Restart auto negotiation */
#define	TBICSR_LinkOk	0x02000000	/* TBI Link OK (RO)*/
#define	TBICSR_NWcomp	0x01000000	/* TBI Nway complete (RO)*/
E 7
I 7
#define	TBICSR_Reset	0x80000000U	/* TBI reset */
#define	TBICSR_LoopBack	0x40000000U
#define	TBICSR_NWEn	0x20000000U	/* TBI auto negotiation enable */
#define	TBICSR_ReNW	0x10000000U	/* TBI Restart auto negotiation */
#define	TBICSR_LinkOk	0x02000000U	/* TBI Link OK (RO)*/
#define	TBICSR_NWcomp	0x01000000U	/* TBI Nway complete (RO)*/
E 7

D 4
/* TBIANAR: TBI Auto-Negotiation Ability register, offset 0x68 */
E 4
I 4
/* TBIANAR: TBI Auto-Negotiation Ability register, offset 0x68 (8169) */
E 4
D 7
#define	TBIANAR_RF	0x3000
E 7
I 7
#define	TBIANAR_RF	0x3000U
E 7
#define		TBIANAR_RF_SHIFT	12
D 7
#define		TBIANAR_RF_NoError	(0 << TBIANAR_RF_SHIFT)
#define		TBIANAR_RF_Offline	(1 << TBIANAR_RF_SHIFT)
#define		TBIANAR_RF_LinkFailure	(2 << TBIANAR_RF_SHIFT)
#define		TBIANAR_RF_ANError	(3 << TBIANAR_RF_SHIFT)
#define	TBIANAR_PAUSE	0x0100
#define	TBIANAR_ASM_DIR	0x0080
E 7
I 7
#define		TBIANAR_RF_NoError	(0U << TBIANAR_RF_SHIFT)
#define		TBIANAR_RF_Offline	(1U << TBIANAR_RF_SHIFT)
#define		TBIANAR_RF_LinkFailure	(2U << TBIANAR_RF_SHIFT)
#define		TBIANAR_RF_ANError	(3U << TBIANAR_RF_SHIFT)
#define	TBIANAR_PAUSE	0x0100U
#define	TBIANAR_ASM_DIR	0x0080U
E 7
#define	TBIANAR_PS	(TBIANAR_ASM_DIR | TBIANAR_PAUSE)
#define		TBIANAR_PS_SHIFT	7
D 7
#define		TBIANAR_PS_NoPause	(0 << TBIANAR_PS_SHIFT)
#define		TBIANAR_PS_AsymPause	(1 << TBIANAR_PS_SHIFT)
#define		TBIANAR_PS_SymPause	(2 << TBIANAR_PS_SHIFT)
#define		TBIANAR_PS_Both		(3 << TBIANAR_PS_SHIFT)
E 7
I 7
#define		TBIANAR_PS_NoPause	(0U << TBIANAR_PS_SHIFT)
#define		TBIANAR_PS_AsymPause	(1U << TBIANAR_PS_SHIFT)
#define		TBIANAR_PS_SymPause	(2U << TBIANAR_PS_SHIFT)
#define		TBIANAR_PS_Both		(3U << TBIANAR_PS_SHIFT)
E 7
#define	TBIANAR_FullDup	0x0020	/* Full Duplex ability */

D 4
/* TBILPAR: TBI Auto-Negotiation Link Partnar Ability register, offset 0x68 */
E 4
I 4
/* TBILPAR: TBI Auto-Negotiation Link Partnar Ability reg, offset 0x68 (8169)*/
E 4
D 7
#define	TBILPAR_NextPage 0x8000	/* the Link partnar has a next page */
#define	TBILPAR_Ack	0x4000	/* */
#define	TBILPAR_RF	0x3000	/* Remote fault */
E 7
I 7
#define	TBILPAR_NextPage 0x8000U	/* the Link partnar has a next page */
#define	TBILPAR_Ack	0x4000U	/* */
#define	TBILPAR_RF	0x3000U	/* Remote fault */
E 7
#define		TBILPAR_RF_SHIFT	12
D 7
#define		TBILPAR_RF_NoError	(0 << TBIANAR_RF_SHIFT)
#define		TBILPAR_RF_Offline	(1 << TBIANAR_RF_SHIFT)
#define		TBILPAR_RF_LinkFailure	(2 << TBIANAR_RF_SHIFT)
#define		TBILPAR_RF_ANError	(3 << TBIANAR_RF_SHIFT)
#define	TBILPAR_HalfDup	0x0400	/* the link partnar supports half duplex */
#define	TBILPAR_FullDup	0x0200	/* the link partnar supports half duplex */
E 7
I 7
#define		TBILPAR_RF_NoError	(0U << TBIANAR_RF_SHIFT)
#define		TBILPAR_RF_Offline	(1U << TBIANAR_RF_SHIFT)
#define		TBILPAR_RF_LinkFailure	(2U << TBIANAR_RF_SHIFT)
#define		TBILPAR_RF_ANError	(3U << TBIANAR_RF_SHIFT)
#define	TBILPAR_HalfDup	0x0400U	/* link partnar supports half duplex */
#define	TBILPAR_FullDup	0x0200U	/* link partnar supports full duplex */
E 7

D 2
/* PHYS: PHY(GMII or TBI) stuta register, offset 0x6c */
E 2
I 2
/* PHYS: PHY(GMII or TBI) stutas register, offset 0x6c */
E 2
D 4
#define	PHYS_EnTBI	0x80	/* 1: TBI mode, 0:GMII mode */
E 4
I 4
D 7
#define	PHYS_EnTBI	0x80	/* 1: TBI mode, 0:GMII mode (8169) */
E 4
#define	PHYS_TxFlow	0x40	/* Tx Flow control 1:enabeled */
#define	PHYS_RxFlow	0x20	/* Rx Flow control 1:enabeled */
#define	PHYS_1000MF	0x10	/* GMII only */
#define	PHYS_100M	0x08	/* GMII or MII only */
#define	PHYS_10M	0x04	/* GMII or MII only */
#define	PHYS_LinkSts	0x02	/* 1:ok, 0:no link */
D 4
#define	PHYS_FullDup	0x01	/* 1: Full duplex */
E 4
I 4
#define	PHYS_FullDup	0x01	/* 1: full duplex, 0: half duplex */
E 7
I 7
#define	PHYS_EnTBI	0x80U	/* 1: TBI mode, 0:GMII mode (8169) */
#define	PHYS_TxFlow	0x40U	/* Tx Flow control 1:enabeled */
#define	PHYS_RxFlow	0x20U	/* Rx Flow control 1:enabeled */
#define	PHYS_1000MF	0x10U	/* GMII only */
#define	PHYS_100M	0x08U	/* GMII or MII only */
#define	PHYS_10M	0x04U	/* GMII or MII only */
#define	PHYS_LinkSts	0x02U	/* 1:ok, 0:no link */
#define	PHYS_FullDup	0x01U	/* 1: full duplex, 0: half duplex */
E 7
E 4

I 2
#define	PHYS_BITS	\
	"\020"	\
	"\010EnTBI"	\
	"\007TxFlow"	\
	"\006RxFlow"	\
	"\0051000MF"	\
	"\004100M"	\
	"\00310M"	\
	"\002LinkSts"	\
	"\001FullDup"
D 7
	
E 7

I 7
/* EPHYAR: EPHY Accress Register: offset 0x60 */
#define	EPHYAR_FLAG	0x80000000U
#define	EPHYAR_REGADDR	0x001f0000U
D 9
#define	EPHYAR_REGADDR_SHIFT	16
E 9
I 9
#define		EPHYAR_REGADDR_SHIFT	16
E 9
#define	EPHYAR_DATA	0x0000ffffU

/* CSIAR: CSI Accress Register: offset 0x68 */
#define	CSIAR_FLAG	0x80000000U
D 9
#define	CSIAR_ByteEn	0x0000000fU
#define		CSIAR_ByteEn_SHIFT	12
E 9
I 9
#define	CSIAR_ByteEn	0x0000f000U
#define		CSIAR_ByteEn_SHIFT	16
E 9
#define	CSIAR_ADDR	0x00000fffU

I 9
/* OCPDR: offset 0xb0 (8168) */
#define	OCPDR_WRITE	0x80000000U
#define	OCPDR_READ	0x00000000U
#define	OCPDR_REG	0x00ff0000U,
#define		OCPDR_GPHY_REG_SHIFT	16
/* #define		OCPDR_REG_MASK	0xFF */
#define	OCPDR_DATA	0x0000ffffU

/* OCPAR: offset 0xb4 (8168) */
#define	OCPAR_FLAG		0x80000000U
#define	OCPAR_GPHY_WRITE	0x8000f060U
#define	OCPAR_GPHY_READ		0x0000f060U

E 9
/* DBGREG: debug register, offset 0xd1 */
#define	DBGREG_FIX_NAK_1	0x10U
#define	DBGREG_FIX_NAK_2	0x08U
#define	DBGREG_PIN_E2		0x01U

E 7
E 2
/* RMS: Receive Packet Maximum Size, offset 0xda */
D 7
#define	RMS_MASK	0x3fff
E 7
I 7
#define	RMS_MASK	0x3fffU
E 7

/* C+CR; C+Command, offset 0xe0 */
D 4
#define	CpCR_ENDIAN	0x0200	/* 1: Big Endian 0:Little endian*/
#define	CpCR_RxVLAN	0x0040	/* Rx VLAN de-tagging enabe */
E 4
I 4
D 7
#define	CpCR_ENDIAN	0x0200	/* 1: Big Endian 0:Little endian (8169) */
#define	CpCR_RxVLAN	0x0040	/* Rx VLAN de-tagging enable */
E 4
#define	CpCR_RxChkSum	0x0020	/* Rx Checksum offload enable */
D 4
#define	CpCR_DAC	0x0010	/* PCI dual cycle access enable */
#define	CpCR_MulRW	0x0008	/* PCI multiple read/write enable */
E 4
I 4
#define	CpCR_DAC	0x0010	/* PCI dual cycle access enable (8169) */
#define	CpCR_MulRW	0x0008	/* PCI multiple read/write enable (8169) */
E 7
I 7
#define	CpCR_ENDIAN	0x0200U	/* 1: Big Endian 0:Little endian (8169) */
#define	CpCR_BIST	0x8000U
#define	CpCR_Macdbgo_oe	0x4000U
#define	CpCR_EnAnaPLL	0x4000U	/* 8169 */
#define	CpCR_NORMAL	0x2000U
#define	CpCR_HALFDUP	0x1000U	/* force half duplex */
#define	CpCR_RXFLOW	0x0800U	/* force to enable rx flow control */
#define	CpCR_TXFLOW	0x0400U	/* force to enable tx flow control */
#define	CpCR_CXPL	0x0200U
#define	CpCR_ASF	0x0100U
#define	CpCR_StatDis	0x0080U
#define	CpCR_RxVLAN	0x0040U	/* Rx VLAN de-tagging enable */
#define	CpCR_RxChkSum	0x0020U	/* Rx Checksum offload enable */
#define	CpCR_DAC	0x0010U	/* PCI dual cycle access enable (8169) */
#define	CpCR_MulRW	0x0008U	/* PCI multiple read/write enable (8169) */
#define	CpCR_Macdbgo_sel	0x001cU
#define	CpCR_INTT_3	0x0003U
#define	CpCR_INTT_2	0x0002U
#define	CpCR_INTT_1	0x0001U
#define	CpCR_INTT_0	0x0000U
E 7
E 4

I 9
/* EFUSEAR: E-FUSE accress register, 0ffset 0xdc (8168) */
#define	EFUSE_WRITE	0x80000000U
#define	EFUSE_WRITE_OK	0x00000000U
#define	EFUSE_READ	0x00000000U
#define	EFUSE_READ_OK	0x80000000U
#define	EFUSE_REG	0x0003ff00U
#define		EFUSE_REG_SHIFT	8
#define		EFUSE_REG_MASK	(EFUSE_REG >> EFUSE_REG_SHIFT)
#define	EFUSE_DATA		0x000000ffU

E 9
D 4
/* ETThR: Early Transmit Threshold register, 0ffset 0xec */
E 4
I 4
/* ETThR: Early Transmit Threshold register, 0ffset 0xec (8169) */
E 4
D 7
#define	ETThR_MASK	0x3f
#define	ETThR_UNIT	32
E 7
I 7
#define	ETThR_MASK	0x3fU
#define	ETThR_UNIT	32U
E 7

I 4
/* MTPS: Max Transmit Packet Size register, 0ffset 0xec (8168) */
D 7
#define	MTPS_MASK	0x3f
#define	MTPS_UNIT	128
E 7
I 7
#define	MTPS_MASK	0x3fU
#define	MTPS_UNIT	128U
E 7

E 4
D 7
#define	FER_INTR	0x00008000
#define	FER_GWAKE	0x00000010
E 7
I 7
#define	FER_INTR	0x00008000U
#define	FER_GWAKE	0x00000010U
E 7

D 7
#define	FEMR_INTR	0x00008000
#define	FEMR_WKUP	0x00004000
#define	FEMR_GWAKE	0x00000010
E 7
I 7
#define	FEMR_INTR	0x00008000U
#define	FEMR_WKUP	0x00004000U
#define	FEMR_GWAKE	0x00000010U
E 7

I 9
/* PHYIO at 0xf8 */
#define	PHYIO_FLAG	0x80000000U
#define	PHYIO_WRITE	0x80000000U
#define	PHYIO_READ	0x00000000U
#define	PHYIO_REG	0x001f0000U
#define		PHYIO_REG_MASK	0x001f0000U
#define		PHYIO_REG_SHIFT	16
#define	PHYIO_DATA	0xffffU

E 9
/*
 * Offset to EPROM contents
 */
#define	EPROM_EthernetID	0x0e

struct tx_desc {
D 3
	volatile uint32_t	txd0;
E 3
I 3
D 4
	uint32_t	txd0;
E 4
I 4
	volatile uint32_t	txd0;
E 4
E 3
D 7
#define	TXD0_OWN	0x80000000	/* 1: the descriptor owned by the nic */
#define	TXD0_EOR	0x40000000	/* End of Descriptor Ring */
#define	TXD0_FS		0x20000000	/* First Segment Descriptor */
#define	TXD0_LS		0x10000000	/* Last Segment Descriptor */
#define	TXD0_LGSEN	0x08000000	/* Large Send */
#define	TXD0_LGSMSS	0x07ff0000
#define	TXD0_IPCS	0x00040000	/* IP checksum offload enable */
#define	TXD0_UDPCS	0x00020000	/* UDP checksum offload enable */
#define	TXD0_TCPCS	0x00010000	/* TCP checksum offload enable */
#define	TXD0_FRAMELEN	0x0000ffff
E 7
I 7
#define	TXD0_OWN	0x80000000U	/* 1: the descriptor owned by the nic */
#define	TXD0_EOR	0x40000000U	/* End of Descriptor Ring */
#define	TXD0_FS		0x20000000U	/* First Segment Descriptor */
#define	TXD0_LS		0x10000000U	/* Last Segment Descriptor */
#define	TXD0_LGSEN	0x08000000U	/* Large Send */
#define	TXD0_LGSMSS	0x07ff0000U
#define		TXD0_LGSMSS_SHIFT	16
#define	TXD0_IPCS	0x00040000U	/* IP checksum offload enable */
#define	TXD0_UDPCS	0x00020000U	/* UDP checksum offload enable */
#define	TXD0_TCPCS	0x00010000U	/* TCP checksum offload enable */
#define	TXD0_FRAMELEN	0x0000ffffU
E 7

D 3
	volatile uint32_t	txd1;
E 3
I 3
D 4
	uint32_t	txd1;
E 4
I 4
	volatile uint32_t	txd1;
I 8
#define	TXD1_UDPCS	0x80000000U	/* UDP checksum offload enable */
#define	TXD1_TCPCS	0x40000000U	/* TCP checksum offload enable */
#define	TXD1_IPCS	0x20000000U	/* IP checksum offload enable */
E 8
E 4
E 3
D 7
#define	TXD1_TAGC	0x00020000	/* VLAN tag control 1:enable */
D 4
#define	TXD1_VLANTAG	0x0000ffff
E 4
I 4
#define	TXD1_VLAN	0x0000ffff	/* VLAN tagid + pri + cfi */
#define	TXD1_VID(x)	((((x) >> 8) & 0x0f) | (((x) << 8) & 0xff00))
#define	TXD1_PRI	0x000000e0	/* VLAN priority */
E 7
I 7
#define	TXD1_TAGC	0x00020000U	/* VLAN tag control 1:enable */
#define	TXD1_VLAN	0x0000ffffU	/* VLAN tagid + pri + cfi */
#define	TXD1_VID(x)	((((x) >> 8) & 0x0fU) | (((x) << 8) & 0xff00U))
#define	TXD1_PRI	0x000000e0U	/* VLAN priority */
E 7
#define		TXD1_PRI_SHIFT	5
D 7
#define	TXD1_CFI	0x00000010	/* VLAN CFI bit */
E 7
I 7
#define	TXD1_CFI	0x00000010U	/* VLAN CFI bit */
E 7
#define		TXD1_CFI_SHIFT	4
E 4

D 3
	volatile uint32_t	txd2;	/* Low 32-bit address of Tx buffer */
	volatile uint32_t	txd3;	/* High 32-bit address of Tx buffer */
E 3
I 3
D 4
	uint32_t	txd2;	/* Low 32-bit address of Tx buffer */
	uint32_t	txd3;	/* High 32-bit address of Tx buffer */
E 4
I 4
D 7
#define	TXD1_VTAG(x)	((((x) >> 8) & 0xff) | (((x) << 8) & 0xff00))
E 7
I 7
#define	TXD1_VTAG(x)	((((x) >> 8) & 0xffU) | (((x) << 8) & 0xff00U))
E 7

	volatile uint32_t	txd2;	/* Low 32-bit address of Tx buffer */
	volatile uint32_t	txd3;	/* High 32-bit address of Tx buffer */
E 4
E 3
};

#define	TXD0_BITS	\
	"\020"		\
	"\040OWN"	\
	"\037EOR"	\
	"\036FS"	\
	"\035LS"	\
	"\034LGSEN"	\
	"\023IPCS"	\
	"\022UDPCS"	\
	"\021TCPCS"

struct rx_desc {
D 3
	volatile uint32_t	rxd0;
E 3
I 3
D 4
	uint32_t	rxd0;
E 4
I 4
	volatile uint32_t	rxd0;
E 4
E 3
D 7
#define	RXD0_OWN	0x80000000	/* 1: descriptor owned by nic */
#define	RXD0_EOR	0x40000000	/* End of Rx descriptor */
#define	RXD0_FS		0x20000000	/* First Segment descriptor */
#define	RXD0_LS		0x10000000	/* Last Segment descriptor */
#define	RXD0_MAR	0x08000000	/* Multicast address Packet received */
#define	RXD0_PAM	0x04000000	/* Physical address Matched */
#define	RXD0_BAR	0x02000000	/* Broadcast address Packet received */
D 4
#define	RXD0_BOVF	0x01000000	/* Buffer overflow */
#define	RXD0_FOVF	0x00800000	/* FIFO overflow */
E 4
I 4
#define	RXD0_BOVF	0x01000000	/* Buffer overflow (8169) */
#define	RXD0_FOVF	0x00800000	/* FIFO overflow (8169) */
E 4
#define	RXD0_RWT	0x00400000	/* Receive Watchdog Timer Expired */
#define	RXD0_RES	0x00200000	/* Receive Error Summary */
#define	RXD0_RUNT	0x00100000	/* Runt Packet */
#define	RXD0_CRC	0x00080000	/* CRC Error */
#define	RXD0_PID	0x00060000	/* Protocol ID */
E 7
I 7
#define	RXD0_OWN	0x80000000U	/* 1: descriptor owned by nic */
#define	RXD0_EOR	0x40000000U	/* End of Rx descriptor */
#define	RXD0_FS		0x20000000U	/* First Segment descriptor */
#define	RXD0_LS		0x10000000U	/* Last Segment descriptor */
#define	RXD0_MAR	0x08000000U	/* Multicast address Packet received */
#define	RXD0_PAM	0x04000000U	/* Physical address Matched */
#define	RXD0_BAR	0x02000000U	/* Broadcast address Packet received */
#define	RXD0_BOVF	0x01000000U	/* Buffer overflow (8169) */
#define	RXD0_FOVF	0x00800000U	/* FIFO overflow (8169) */
#define	RXD0_RWT	0x00400000U	/* Receive Watchdog Timer Expired */
#define	RXD0_RES	0x00200000U	/* Receive Error Summary */
#define	RXD0_RUNT	0x00100000U	/* Runt Packet */
#define	RXD0_CRC	0x00080000U	/* CRC Error */
#define	RXD0_PID	0x00060000U	/* Protocol ID */
E 7
#define		RXD0_PID_SHIFT	17
D 7
#define		RXD0_PID_NONIP	(0 << RXD0_PID_SHIFT)
#define		RXD0_PID_TCP	(1 << RXD0_PID_SHIFT)
#define		RXD0_PID_UDP	(2 << RXD0_PID_SHIFT)
#define		RXD0_PID_IP	(3 << RXD0_PID_SHIFT)
#define	RXD0_IPF	0x00010000	/* IP checksum failure */
#define	RXD0_UDPF	0x00008000	/* UDP checksum failure */
#define	RXD0_TCPF	0x00004000	/* TCP checksum failure */
#define	RXD0_FRAMELEN	0x00003fff
E 7
I 7
#define		RXD0_PID_NONIP	(0U << RXD0_PID_SHIFT)
#define		RXD0_PID_TCP	(1U << RXD0_PID_SHIFT)
#define		RXD0_PID_UDP	(2U << RXD0_PID_SHIFT)
#define		RXD0_PID_IP	(3U << RXD0_PID_SHIFT)
#define	RXD0_IPF	0x00010000U	/* IP checksum failure */
#define	RXD0_UDPF	0x00008000U	/* UDP checksum failure */
#define	RXD0_TCPF	0x00004000U	/* TCP checksum failure */
#define	RXD0_FRAMELEN	0x00003fffU
E 7

D 3
	volatile uint32_t	rxd1;
E 3
I 3
D 4
	uint32_t	rxd1;
E 4
I 4
	volatile uint32_t	rxd1;
E 4
E 3
D 7
#define	RXD1_TAVA	0x00010000	/* Tan Available */
#define	RXD1_VLANTAG	0x0000ffff	/* VLAN Tag */
E 7
I 7
#define	RXD1_TAVA	0x00010000U	/* Tan Available */
#define	RXD1_VLANTAG	0x0000ffffU	/* VLAN Tag */
E 7

D 3
	volatile uint32_t	rxd2;	/* Low 32-bit Address of Rx buffer */
	volatile uint32_t	rxd3;	/* High 32-bit Addres of Rx buffer */
E 3
I 3
D 4
	uint32_t	rxd2;	/* Low 32-bit Address of Rx buffer */
	uint32_t	rxd3;	/* High 32-bit Addres of Rx buffer */
E 4
I 4
	volatile uint32_t	rxd2;	/* Low 32-bit Address of Rx buffer */
	volatile uint32_t	rxd3;	/* High 32-bit Addres of Rx buffer */
E 4
E 3
};

#define	RXD0_BITS	\
	"\020"		\
	"\040OWN"	\
	"\037EOR"	\
	"\036FS"	\
	"\035LS"	\
	"\034MAR"	\
	"\033PAM"	\
	"\032BAR"	\
	"\031BOVF"	\
	"\030FOVF"	\
	"\027RWT"	\
	"\026RES"	\
	"\025RUNT"	\
	"\024CRC"	\
	"\021IPF"	\
	"\020UDPF"	\
	"\017TCPF"
I 9

#endif	/* _RTL8169REG_H_ */
E 9
E 1
