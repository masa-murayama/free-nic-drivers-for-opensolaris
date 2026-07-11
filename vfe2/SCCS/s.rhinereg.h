h46217
s 00051/00046/00458
d D 1.16 07/12/02 22:55:16 mrym 16 15
c clean up for putback
e
s 00275/00271/00229
d D 1.15 07/08/18 19:22:20 mrym 15 14
c 2.6
e
s 00001/00001/00499
d D 1.14 07/03/29 23:28:06 mrym 14 13
c misc fixes
e
s 00004/00004/00496
d D 1.13 06/11/04 04:20:07 mrym 13 12
c typo fixed
e
s 00008/00008/00492
d D 1.12 06/05/21 15:54:22 mrym 12 11
c 
e
s 00003/00001/00497
d D 1.11 05/06/06 22:01:51 mrym 11 10
c 1.0.21
e
s 00012/00010/00486
d D 1.10 05/04/08 01:30:15 mrym 10 9
c volatile removed
e
s 00037/00025/00459
d D 1.9 05/01/10 23:25:28 mrym 9 8
c fix for flowcontrol
e
s 00002/00001/00482
d D 1.8 04/12/23 07:58:50 mrym 8 7
c mmio support
e
s 00040/00024/00443
d D 1.7 04/04/29 13:36:00 mrym 7 6
c datasheet bug fixed
e
s 00015/00027/00452
d D 1.6 04/03/29 23:34:29 mrym 6 5
c rhine1 data sheet bug fixed
e
s 00016/00004/00463
d D 1.5 03/04/27 22:30:34 mrym 5 4
c 0.9.4
e
s 00037/00018/00430
d D 1.4 02/11/23 09:35:56 mrym 4 3
c pre 0.9.0
e
s 00002/00000/00446
d D 1.3 02/08/08 03:28:01 mrym 3 2
c 0.8.5
e
s 00116/00142/00330
d D 1.2 02/06/02 21:11:19 mrym 2 1
c release 0.8.2
e
s 00472/00000/00000
d D 1.1 02/05/18 21:08:13 mrym 1 0
c date and time created 02/05/18 21:08:13 by mrym
e
u
U
f e 0
t
T
I 1
/*
D 4
 * rhinereg.h %W% %E%
 * Based on VIA VT86C100A data sheet and VT6102 data sheet.
E 4
I 4
D 5
 * rhinereg.h
E 5
I 5
 * rhinereg.h : Macro definitions for VIA rhine ethernet mac chips.
E 5
D 6
 * Based on VIA VT86C100A and VT6102, VT6105LOM, VT6105M data sheet.
E 6
I 6
 * Based on VIA VT86C100A and VT6102, VT6105LOM, VT6105M data sheets.
E 6
 * Coded by Masayuki Murayama (KHF04453@nifty.ne.jp)
 * This file is public domain.
E 4
 */
I 16
#ifndef _RHINEREG_H_
#define	_RHINEREG_H_
E 16

I 4
D 16
#pragma	ident	"%W% %E%"
E 16
I 16
#pragma	ident	"%Z%%M% %I%     %E%"
E 16

E 4
/*
 * Known PCI vendor-id/device-id for rhine chips
 */
D 7

E 7
D 15
#define	VID_VIA		0x1106
#define	DID_VT86C100A	0x6100
#define	DID_VT3043	0x3043
#define	DID_VT6102	0x3065
#define	DID_VT6105	0x3106
I 4
#define	DID_VT6105M	0x3053
E 15
I 15
#define	VID_VIA		0x1106U
#define	DID_VT86C100A	0x6100U
#define	DID_VT3043	0x3043U
#define	DID_VT6102	0x3065U
#define	DID_VT6105	0x3106U
#define	DID_VT6105M	0x3053U
E 15
E 4

/*
D 7
 * VIA  Rhine seris Register definitions
E 7
I 7
 * VIA Rhine series Register definitions
E 7
 */
D 7

E 7
/* Offsets to the device registers. */
#define	PAR		0x00	/* B: Physical addr */
#define	RCR		0x06	/* B: Rx Config */
#define	TCR		0x07	/* B: Tx Config */
#define	CR		0x08	/* W: Command Reg */
I 4
#define	TXQW		0x0a	/* B: Transmit Queue Wake */
E 4
#define	ISR		0x0c	/* W: Interrupt Status */
#define	IMR		0x0e	/* W: Interrupt Mask */
#define	MAR		0x10	/* B: Multicast Addr */
D 16
#define	CRDA		0x18	/* L: Current Rx Desc Addr*/
#define	CTDA		0x1c	/* L: Current Tx Desc Addr*/
E 16
I 16
#define	CRDA		0x18	/* L: Current Rx Desc Addr */
#define	CTDA		0x1c	/* L: Current Tx Desc Addr */
E 16
#define	MPHY		0x6c	/* B: PHY addr */
#define	MIISR		0x6d	/* B */
#define	BCR		0x6e	/* W */
#define	MIICR		0x70	/* B */
#define	MIIADR		0x71	/* B */
#define	MIIDATA		0x72	/* W */
#define	EECSR		0x74	/* B */
#define	CFGA		0x78	/* B */
#define	CFGB		0x79	/* B */
#define	CFGC		0x7a	/* B */
#define	CFGD		0x7b	/* B */
#define	MPAC		0x7c	/* W */
#define	CRCC		0x7e	/* W */
#define	MISC		0x80	/* W */
I 6
#define	MISR		0x84	/* B */
#define	MIMR		0x86	/* B */
E 6
I 5
D 9
#define	CAMMASK		0x88	/* L */
#define	CAMCTRL		0x92	/* B */
#define	CAMADDR		0x93	/* B */
E 5
I 4
#define	FCR0		0x98	/* B */
#define	FCR1		0x99	/* B */
#define	PAUSE_TIMER	0x9a	/* W: for rhine III */
E 9
I 9
#define	CAMMASK		0x88	/* L: for rhine III */
#define	CAMCTRL		0x92	/* B: for rhine III */
#define	CAMADDR		0x93	/* B: for rhine III */
#define	FCR0		0x98	/* B: flow control (rhine III) */
#define	FCR1		0x99	/* B: flow control (rhine III) */
#define	PAUSE_TIMER	0x9a	/* W: sending pause value (rhine III) */
E 9
E 4
#define	STICKHW		0x83	/* B */
I 10
#define	SOFT_TMR0	0x9c
#define	SOFT_TMR1	0x9e
E 10
D 9
#define	WOLCR_SET	0xa0	/* B   Wake On Lan command register */ 
E 9
I 9
D 16
#define	WOLCR_SET	0xa0	/* B:  Wake On Lan command register */ 
E 16
I 16
#define	WOLCR_SET	0xa0	/* B:  Wake On Lan command register */
E 16
E 9
I 7
#define	PWCFG_SET	0xa1	/* B */
#define	TSTREG_SET	0xa2	/* B */
#define	WOLCG_SET	0xa3	/* B */
E 7
#define	WOLCR_CLR	0xa4	/* B */
I 7
#define	PWCFG_CLR	0xa5	/* B */
#define	TSTREG_CLR	0xa6	/* B */
E 7
#define	WOLCG_CLR	0xa7	/* B */
I 7
#define	PWRCSR_SET	0xa8	/* B */
#define	PWRCSR1_SET	0xa9	/* B */
E 7
#define	PWRCSR_CLR	0xac	/* B */
I 7
#define	PWRCSR1_CLR	0xad	/* B */
#define	PATRN_CRC	0xb0	/* L */
#define	BYTEMSK0	0xc0	/* L */
#define	BYTEMSK1	0xd0	/* L */
#define	BYTEMSK2	0xe0	/* L */
#define	BYTEMSK3	0xf0	/* L */
E 7

I 5
#define	MULTICAST_CAM_SIZE	32
#define	VLANTAG_CAM_SIZE	32
E 5

/* offset 0x00-0x05  Ethernet Address 0x00-0x05 */
/* No bit field */

/* RCR (offset 0x06, RW) Receive Control register */
D 15
#define	RCR_RRFT	0xe0	/* Receive FIFO threshold */
D 2
#define	RCR_RRFT_SHIFT	5
#define	RCR_RRFT_64	(0 << RCR_RRFT_SHIFT)	/* Manual bug ? */
#define	RCR_RRFT_32	(1 << RCR_RRFT_SHIFT)	/* Manual bug ? */
#define	RCR_RRFT_128	(2 << RCR_RRFT_SHIFT)
#define	RCR_RRFT_256	(3 << RCR_RRFT_SHIFT)
#define	RCR_RRFT_512	(4 << RCR_RRFT_SHIFT)
#define	RCR_RRFT_768	(5 << RCR_RRFT_SHIFT)
#define	RCR_RRFT_1024	(6 << RCR_RRFT_SHIFT)
#define	RCR_RRFT_SF	(7 << RCR_RRFT_SHIFT)
E 2
I 2
#define		RCR_RRFT_SHIFT	5
D 7
#define		RCR_RRFT_MASK	(0x7 << RCR_RRFT_SHIFT)
E 7
I 7
#define		RRFT_MASK	7
E 7
D 5
#define		RRFT_64		0	/* Manual bug ? */
#define		RRFT_32		1	/* Manual bug ? */
E 5
I 5
#define		RRFT_64		0
#define		RRFT_32		1
E 5
#define		RRFT_128	2
#define		RRFT_256	3
#define		RRFT_512	4
#define		RRFT_768	5
#define		RRFT_1024	6
#define		RRFT_SF		7
E 2
#define	RCR_PRO		0x10	/* Promiscous, all phiscal packet accepted */
#define	RCR_AB		0x08	/* Broadcast packets accepted */
#define	RCR_AM		0x04	/* Multicast packets accepted */
#define	RCR_AR		0x02	/* Small (runt) packets accepted */
#define	RCR_SEP		0x01	/* Error packets accepted */
E 15
I 15
#define	RCR_RRFT	0xe0U	/* Receive FIFO threshold */
#define		RCR_RRFT_SHIFT	5U
#define		RRFT_MASK	7U
#define		RRFT_64		0U
#define		RRFT_32		1U
#define		RRFT_128	2U
#define		RRFT_256	3U
#define		RRFT_512	4U
#define		RRFT_768	5U
#define		RRFT_1024	6U
#define		RRFT_SF		7U
#define	RCR_PRO		0x10U	/* Promiscous, all phiscal packet accepted */
#define	RCR_AB		0x08U	/* Broadcast packets accepted */
#define	RCR_AM		0x04U	/* Multicast packets accepted */
#define	RCR_AR		0x02U	/* Small (runt) packets accepted */
#define	RCR_SEP		0x01U	/* Error packets accepted */
E 15

#define	RCR_BITS	"\020\5Promisc\4ABroad\3AMulti\2ARunt\1SEP"


/* TCR (offset 0x07, RW) Transmit Control Register */
D 7
#define	TCR_RTSF	0xe0	/* Transmit FIFO threshold, multiple of 128 */
D 2
#define		TCR_RTSF_MASK	0x7
E 2
#define		TCR_RTSF_SHIFT	5
D 2
#define		TCR_RTSF_64		(0 << TCR_RTSF_SHIFT)
#define		TCR_RTSF_32		(1 << TCR_RTSF_SHIFT)
#define		TCR_RTSF_128		(2 << TCR_RTSF_SHIFT)
#define		TCR_RTSF_256		(3 << TCR_RTSF_SHIFT)
#define		TCR_RTST_512		(4 << TCR_RTSF_SHIFT)
#define		TCR_RTSF_768		(5 << TCR_RTSF_SHIFT)
#define		TCR_RTSF_1024		(6 << TCR_RTSF_SHIFT)
#define		TCR_RTSF_SF		(7 << TCR_RTSF_SHIFT)
#define		TCR_RTSF_128_6102	(0 << TCR_RTSF_SHIFT) 	/* for VT6102 */
#define		TCR_RTSF_256_6102	(1 << TCR_RTSF_SHIFT)
#define		TCR_RTSF_512_6102	(2 << TCR_RTSF_SHIFT)
#define		TCR_RTSF_1024_6102	(3 << TCR_RTSF_SHIFT)
#define		TCR_RTSF_SF_6102	(4 << TCR_RTSF_SHIFT)
E 2
I 2
#define		TCR_RTSF_MASK	(0x7 << TCR_RTSF_SHIFT)
D 6
#define		RTSF_64		0
#define		RTSF_32		1
#define		RTSF_128	2
#define		RTSF_256	3
#define		RTST_512	4
#define		RTSF_768	5
#define		RTSF_1024	6
#define		RTSF_SF		7
D 4
#define		RTSF_128_610x	0 	/* for VT6102 */
E 4
I 4
#define		RTSF_128_610x	0 	/* for VT6102 or later chips */
E 4
#define		RTSF_256_610x	1
#define		RTSF_512_610x	2
#define		RTSF_1024_610x	3
#define		RTSF_SF_610x	4
E 6
I 6
#define		RTSF_128	0 	/* for VT6102 or later chips */
#define		RTSF_256	1
#define		RTSF_512	2
#define		RTSF_1024	3
#define		RTSF_SF		4
E 7
I 7
D 15
#define	TCR_RTFT	0xe0	/* Transmit FIFO threshold, multiple of 128 */
#define		TCR_RTFT_SHIFT	5
#define		RTFT_MASK	7
#define		RTFT_128	0
#define		RTFT_256	1
#define		RTFT_512	2
#define		RTFT_1024	3
#define		RTFT_SF		4
E 7
E 6
E 2
#define	TCR_OFSET	0x08	/* 0: VIA private spec, 1(default): std */
#define	TCR_LB		0x06
I 9
#define		TCR_LB_MASK		0x3
E 9
D 7
#define		TCR_LB_MASK	0x03
E 7
#define		TCR_LB_SHIFT		1
#define		TCR_LB_NORMAL		(0 << TCR_LB_SHIFT)
#define		TCR_LB_LOOPBACK		(1 << TCR_LB_SHIFT)
#define		TCR_LB_MIILOOPBACK	(2 << TCR_LB_SHIFT)
#define		TCR_LB_233LOOPBACK	(3 << TCR_LB_SHIFT)
E 15
I 15
#define	TCR_RTFT	0xe0U	/* Transmit FIFO threshold, multiple of 128 */
#define		TCR_RTFT_SHIFT	5U
#define		RTFT_MASK	7U
#define		RTFT_128	0U
#define		RTFT_256	1U
#define		RTFT_512	2U
#define		RTFT_1024	3U
#define		RTFT_SF		4U
#define	TCR_RxTAG	0x10U	/* hardware rx tag filter enable (6105M) */
#define	TCR_OFSET	0x08U	/* 0: VIA private spec, 1(default): std */
#define	TCR_LB		0x06U
#define		TCR_LB_MASK		0x3U
#define		TCR_LB_SHIFT		1U
#define		TCR_LB_NORMAL		(0U << TCR_LB_SHIFT)
#define		TCR_LB_LOOPBACK		(1U << TCR_LB_SHIFT)
#define		TCR_LB_MIILOOPBACK	(2U << TCR_LB_SHIFT)
#define		TCR_LB_233LOOPBACK	(3U << TCR_LB_SHIFT)
#define	TCR_TxTAG	0x01U	/* hardware tx tagging enable (6105M) */
E 15


/* CR(offset 0x08-0x09, RW) Command register */

D 15
#define	CR_SRST		0x8000	/* Software reset	*/
I 6
#define	CR_RDMD1	0x4000	/* Poll the RD once	*/
#define	CR_TDMD1	0x2000	/* Poll the TD once	*/
E 6
#define	CR_DPOLL	0x0800	/* Disable TD/RD auto polling */
#define	CR_FDX		0x0400	/* Full duplex		*/
#define	CR_ETEN		0x0200	/* was EarlyTX		*/
#define	CR_EREN		0x0100	/* Enable early receive mode */
D 6
#define	CR_RDMD		0x0040	/* Poll the RD once (manual bug?) */
E 6
I 6
#define	CR_RDMD		0x0040	/* Poll the RD once	*/
E 6
#define	CR_TDMD		0x0020	/* Poll the TD once	*/
#define	CR_TXON		0x0010	/* Turn on transmit DMA state */
#define	CR_RXON		0x0008	/* Turn on receive DMA state */
#define	CR_STOP		0x0004	/* Stop NIC		*/
#define	CR_STRT		0x0002	/* Start NIC		*/
#define	CR_INIT		0x0001	/* Init process begin	*/
E 15
I 15
#define	CR_SRST		0x8000U	/* Software reset	*/
#define	CR_RDMD1	0x4000U	/* Poll the RD once	*/
#define	CR_TDMD1	0x2000U	/* Poll the TD once	*/
#define	CR_DPOLL	0x0800U	/* Disable TD/RD auto polling */
#define	CR_FDX		0x0400U	/* Full duplex		*/
#define	CR_ETEN		0x0200U	/* was EarlyTX		*/
#define	CR_EREN		0x0100U	/* Enable early receive mode */
#define	CR_RDMD		0x0040U	/* Poll the RD once	*/
#define	CR_TDMD		0x0020U	/* Poll the TD once	*/
#define	CR_TXON		0x0010U	/* Turn on transmit DMA state */
#define	CR_RXON		0x0008U	/* Turn on receive DMA state */
#define	CR_STOP		0x0004U	/* Stop NIC		*/
#define	CR_STRT		0x0002U	/* Start NIC		*/
#define	CR_INIT		0x0001U	/* Init process begin	*/
E 15

#define	CR_BITS	\
	"\020"	\
	"\20SRst\14DPoll\13Fdx\12ETEn\11EREn"	\
	"\7RxDmd\6TxDmd\5TxOn\4RxOn\3Stop\2Strt\1Init"

/* offset 0x0c-0x0d ISR: Interrupt status register */

D 15
#define	ISR_KEYI	0x8000	/* General purpose 6102 / Rx wake up */
#define	ISR_SRCI	0x4000	/* link changed */
#define	ISR_ABTI	0x2000
#define	ISR_NORBF	0x1000
#define	ISR_PKRACE	0x0800
#define	ISR_OVFI	0x0400
#define	ISR_ETI		0x0200	/* TX FIFO underrun 6102 / PHY status chage */
#define	ISR_ERI		0x0100	/* early receive interrupt */
E 15
I 15
D 16
#define	ISR_KEYI	0x8000U	/* General purpose 6102 / Rx wake up */
E 16
I 16
#define	ISR_KEYI	0x8000U	/* General purpose (II) / Rx wake up */
E 16
#define	ISR_SRCI	0x4000U	/* link changed */
#define	ISR_ABTI	0x2000U
#define	ISR_NORBF	0x1000U
#define	ISR_PKRACE	0x0800U
#define	ISR_OVFI	0x0400U
D 16
#define	ISR_ETI		0x0200U	/* TX FIFO underrun 6102 / PHY status chage */
E 16
I 16
#define	ISR_ETI		0x0200U	/* TX FIFO underrun (II) / PHY status chage */
E 16
#define	ISR_ERI		0x0100U	/* early receive interrupt */
E 15

D 15
#define	ISR_CNT		0x0080	/* statstics count max */
#define	ISR_BE		0x0040	/* bus error */
#define	ISR_RU		0x0020	/* receive underrun */
#define	ISR_TU		0x0010	/* transmit underrun */
#define	ISR_TXE		0x0008	/* transmit error */
#define	ISR_RXE		0x0004	/* receive error */
#define	ISR_PTX		0x0002	/* packet transmitted */
#define	ISR_PRX		0x0001	/* packet received */
E 15
I 15
#define	ISR_CNT		0x0080U	/* statstics count max */
#define	ISR_BE		0x0040U	/* bus error */
#define	ISR_RU		0x0020U	/* receive underrun */
#define	ISR_TU		0x0010U	/* transmit underrun */
#define	ISR_TXE		0x0008U	/* transmit error */
#define	ISR_RXE		0x0004U	/* receive error */
#define	ISR_PTX		0x0002U	/* packet transmitted */
#define	ISR_PRX		0x0001U	/* packet received */
E 15

D 2
#define	IntrNormalSummary	0x0003
#define	IntrAbnormalSummary	0xC260

E 2
#define	ISR_BITS	\
	"\020"	\
	"\020KEYI\017SRCI\016ABTI\015NORBF"	\
	"\014PKRACE\013OVFlI\012ETI_MIIChange\011ERI"	\
	"\010Cnt\007BE\006RU\005TU"	\
	"\004TxE\003RxE\002PTx\001PRx"

D 2
#define	OUR_INTR_BITS	\
	(ISR_ABTI | ISR_NORBF | ISR_PKRACE | ISR_OVFI |	\
	 ISR_CNT | ISR_BE | ISR_RU | ISR_TU |	\
	 ISR_RXE |ISR_TXE | 	\
	 ISR_PTX | ISR_PRX)

E 2
/* IMR (offset 0x0e-0x0f) Interrupt mask register */
/* same as above */

/* MAR (offset 0x10-0x17) Multicast mask register */

/* Curr_RX (offset 0x18-0x1b, doulbe word RW) current RX descriptor address */
/* Curr_TX (offset 0x1c-0x1f, doulbe word RW) current TX descriptor address */

/* RDESC0-3 (offset 0x20-0x2f) Rx Descriptor */

/* The Rx buffer descriptor. */
struct rx_desc {
D 4
	uint32_t	rd_status;
	uint32_t	rd_length;
	uint32_t	rd_addr;
	uint32_t	rd_next;
E 4
I 4
D 10
	volatile uint32_t	rd_status;
	volatile uint32_t	rd_length;
	volatile uint32_t	rd_addr;
	volatile uint32_t	rd_next;
E 10
I 10
D 12
	uint32_t	rd_status;
	uint32_t	rd_length;
	uint32_t	rd_addr;
	uint32_t	rd_next;
E 12
I 12
	volatile uint32_t	rd_status;
	volatile uint32_t	rd_length;
	volatile uint32_t	rd_addr;
	volatile uint32_t	rd_next;
E 12
E 10
E 4
};


/* Receive status field in RDES0 */
D 15
#define	RSR_RXOK	0x8000	/* Received a good packet */
#define	RSR_MAR		0x2000	/* Multicast address received */
#define	RSR_BAR		0x1000	/* Broadcast address received */
#define	RSR_PHY		0x0800	/* Physical address received */
#define	RSR_CHN		0x0400
#define	RSR_STP		0x0200	/* Start of packet */
#define	RSR_EDP		0x0100	/* End of packet */
#define	RSR_BUFF	0x0080	/* Receive buffer error */
#define	RSR_SERR	0x0040	/* System bus error */
#define	RSR_RUNT	0x0020	/* Runt Packet received */
#define	RSR_LONG	0x0010	/* Long packet received */
#define	RSR_FOV		0x0008	/* FIFO overflow */
#define	RSR_FAE		0x0004	/* Frame Alignment error */
#define	RSR_CRC		0x0002	/* CRC Error error */
#define	RSR_RERR	0x0001	/* Receive error */
E 15
I 15
#define	RSR_RXOK	0x8000U	/* Received a good packet */
#define	RSR_MAR		0x2000U	/* Multicast address received */
#define	RSR_BAR		0x1000U	/* Broadcast address received */
#define	RSR_PHY		0x0800U	/* Physical address received */
#define	RSR_CHN		0x0400U
#define	RSR_STP		0x0200U	/* Start of packet */
#define	RSR_EDP		0x0100U	/* End of packet */
#define	RSR_BUFF	0x0080U	/* Receive buffer error */
#define	RSR_SERR	0x0040U	/* System bus error */
#define	RSR_RUNT	0x0020U	/* Runt Packet received */
#define	RSR_LONG	0x0010U	/* Long packet received */
#define	RSR_FOV		0x0008U	/* FIFO overflow */
#define	RSR_FAE		0x0004U	/* Frame Alignment error */
#define	RSR_CRC		0x0002U	/* CRC Error error */
#define	RSR_RERR	0x0001U	/* Receive error */
E 15

/* useful macros for RSR bits */
D 16
#define	RSR_ERRORS	(RSR_BUFF|RSR_SERR|RSR_RUNT|RSR_LONG| \
			 RSR_FOV|RSR_FAE|RSR_CRC|RSR_RERR)
E 16
I 16
#define	RSR_ERRORS	\
	(RSR_BUFF|RSR_SERR|RSR_RUNT|RSR_LONG| \
	RSR_FOV|RSR_FAE|RSR_CRC|RSR_RERR)
E 16

#define	RSR_BITS	\
	"\020"	\
D 4
	"\20RxOK\16Mar\15Bar\14Phy\13Chn\12Stp\11Edp"	\
	"\10Buff\7SErr\6Runt\5Long\4Fov\3Fae\2Crc\1RErr"
E 4
I 4
	"\20RXOK\16MAR\15BAR\14PHY\13CHN\12STP\11EDP"	\
	"\10BUFF\7SERR\6RUNT\5LONG\4FOV\3FAE\2CRC\1RERR"
E 4

D 15
#define	RDES0_OWN	0x80000000
#define	RDES0_LEN_SHIFT	16
#define	RDES0_LEN_MASK	0x7fff
E 15
I 15
#define	RDES0_OWN	0x80000000U
#define	RDES0_LEN_SHIFT	16U
#define	RDES0_LEN_MASK	0x7fffU
E 15

D 15
#define	RDES1_RBS	0x000007ff	/* Receive buffer size */
#define	RDES1_C		0x00008000	/* Chain buffer */
E 15
I 15
#define	RDES1_RBS	0x000007ffU	/* Receive buffer size */
#define	RDES1_C		0x00008000U	/* Chain buffer */
E 15

/* TDES0-3 (offset 0x40-0x4f) Tx Descriptor */
struct tx_desc {
D 4
	uint32_t	td_csr;
	uint32_t	td_length;
	uint32_t	td_addr;
	uint32_t	td_next;
E 4
I 4
D 10
	volatile uint32_t	td_csr;
	volatile uint32_t	td_length;
	volatile uint32_t	td_addr;
	volatile uint32_t	td_next;
E 10
I 10
D 12
	uint32_t	td_csr;
	uint32_t	td_length;
	uint32_t	td_addr;
	uint32_t	td_next;
E 12
I 12
	volatile uint32_t	td_csr;
	volatile uint32_t	td_length;
	volatile uint32_t	td_addr;
	volatile uint32_t	td_next;
E 12
E 10
E 4
};

D 15
#define	TDES0_OWN	0x80000000
#define	TDES0_TSR	0x0000ffff
E 15
I 15
#define	TDES0_OWN	0x80000000U
#define	TDES0_TSR	0x0000ffffU
E 15

/* TX status bits in TDSE0.  */
D 15
#define	TSR_TXERR	0x8000	/* underflow/abort/late collision/CRS */
#define	TSR_JAB		0x4000	/* Jabber (undefined for VT6102)*/
#define	TSR_SERR	0x2000	/* master abort/target abort/parity error */
D 2
#define	TSR_TBUFF_6102	0x1000	/* invalid TD format or TD underflow */
#define	TSR_UDF_6102	0x0800	/* TX Underflow */
E 2
I 2
D 6
#define	TSR_TBUFF_610x	0x1000	/* invalid TD format or TD underflow */
#define	TSR_UDF_610x	0x0800	/* TX Underflow */
E 6
I 6
#define	TSR_TBUFF	0x1000	/* invalid TD format or TD underflow */
#define	TSR_UDF		0x0800	/* TX Underflow */
E 6
E 2
#define	TSR_CRS		0x0400	/* carrier sense lost */
#define	TSR_OWC		0x0200	/* late collision */
#define	TSR_ABT		0x0100	/* exceed max collision */
#define	TSR_CDH		0x0080	/* CD Heart beat */
D 6
#define	TSR_NCR		0x0078	/* Collision retry count */
#define		TSR_NCR_MASK	0xf
#define		TSR_NCR_SHIFT	3
#define	TSR_UDF		0x0002	/* FIFO under-flow (undefined for VT6102) */
#define	TSR_DFR		0x0001	/* Deferred (undefined for VT6012)*/
E 6
I 6
#define	TSR_COLS	0x0010	/* Experience collision on trasnmit event */
#define	TSR_NCR		0x000f	/* Collision retry count */
E 15
I 15
#define	TSR_TXERR	0x8000U	/* underflow/abort/late collision/CRS */
D 16
#define	TSR_JAB		0x4000U	/* Jabber (undefined for VT6102)*/
E 16
I 16
#define	TSR_JAB		0x4000U	/* Jabber (undefined for II) */
E 16
#define	TSR_SERR	0x2000U	/* master abort/target abort/parity error */
#define	TSR_TBUFF	0x1000U	/* invalid TD format or TD underflow */
#define	TSR_UDF		0x0800U	/* TX Underflow */
#define	TSR_CRS		0x0400U	/* carrier sense lost */
#define	TSR_OWC		0x0200U	/* late collision */
#define	TSR_ABT		0x0100U	/* exceed max collision */
#define	TSR_CDH		0x0080U	/* CD Heart beat */
#define	TSR_COLS	0x0010U	/* Experience collision on trasnmit event */
#define	TSR_NCR		0x000fU	/* Collision retry count */
E 15
E 6

D 2
#define	TSR_COLS_6102	0x0010	/* Experience collision on trasnmit event */
#define	TSR_NCR_6102	0x000f	/* Collision retry count for VT6102*/
#define	TSR_NCR_MASK	0xf
#define TSR_NCR_SHIFT_6102	0
E 2
I 2
D 6
#define	TSR_COLS_610x	0x0010	/* Experience collision on trasnmit event */
#define	TSR_NCR_610x	0x000f	/* Collision retry count for VT6102/6105 */
D 4
#define	TSR_NCR_MASK_610x	0xf
#define TSR_NCR_SHIFT_610x	0
E 4
E 2

E 6
#define	TSR_BITS	\
D 4
	"\020\20TxErr\17Jab\16SErr\13Crs\12Owc\11Abt\10Cdh\2Udf\1Dfr"
E 4
I 4
D 6
	"\020\20TXERR\17JAB\16SERR\13CRS\12OWC\11ABT\10CDH\2UDF\1DFR"
#define	TSR_BITS_610x	\
E 6
	"\020\20TXERR\16SERR\15TBUFF\14UDF\13CRS\12OWC\11ABT\10CDH"
E 4

D 15
#define	TDES1_IC	0x00800000	/* assert interrupt immidiately */
#define	TDES1_EDP	0x00400000	/* End of transmit packet */
#define	TDES1_STP	0x00200000	/* Start of transmit packet */
E 15
I 15
#define	TDES1_IC	0x00800000U	/* assert interrupt immidiately */
#define	TDES1_EDP	0x00400000U	/* End of transmit packet */
#define	TDES1_STP	0x00200000U	/* Start of transmit packet */
E 15

D 15
#define	TDES1_CRC	0x00010000	/* Disable CRC generation */
#define	TDES1_C		0x00008000	/* Chained */
#define	TDES1_TLNG	0x000007ff	/* Transmit buffer size */
E 15
I 15
#define	TDES1_CRC	0x00010000U	/* Disable CRC generation */
#define	TDES1_C		0x00008000U	/* Chained */
#define	TDES1_TLNG	0x000007ffU	/* Transmit buffer size */
E 15

D 4
#define	TXDESC1_BITS	"\020\030IC\027EDP\026STP\021CRC_DIS\020C"
E 4
I 4
#define	TDES1_BITS	"\020\030IC\027EDP\026STP\021CRC_DIS\020C"
E 4

I 4
D 15
#define	TDES3_TDCTL	0x00000001	/* surpress interrupt */
I 5
#define	TDES3_NEXT	0xfffffff0	/* surpress interrupt */
E 15
I 15
#define	TDES3_TDCTL	0x00000001U	/* surpress interrupt */
#define	TDES3_NEXT	0xfffffff0U	/* surpress interrupt */
E 15
E 5
E 4

D 14
/* PHY_ADR (offset 0x6c) Phy address register */
E 14
I 14
/* MPHY (offset 0x6c) Phy address register */
E 14

D 15
#define	PHYADR_MPO	0xc0		/* MII polling timer interval (def 0)*/
#define	PHYADR_MFDC	0x20		/* Accelerate MDC sleep 4times */
#define		PHYADR_MPO_MASK		0x3
#define		PHYADR_MPO_SHIFT	6
#define		PHYADR_MPO_1024	(0 << PHYADR_MPO_SHIFT)
#define		PHYADR_MPO_512	(1 << PHYADR_MPO_SHIFT)
#define		PHYADR_MPO_128	(2 << PHYADR_MPO_SHIFT)
#define		PHYADR_MPO_64	(3 << PHYADR_MPO_SHIFT)
#define	PHYADR_PHYAD	0x1f		/* phy addrss mask (def 0x01) */
E 15
I 15
D 16
#define	PHYADR_MPO	0xc0U		/* MII polling timer interval (def 0)*/
E 16
I 16
#define	PHYADR_MPO	0xc0U		/* MII polling interval (def 0) */
E 16
#define	PHYADR_MFDC	0x20U		/* Accelerate MDC sleep 4times */
#define		PHYADR_MPO_MASK		0x3U
#define		PHYADR_MPO_SHIFT	6U
#define		PHYADR_MPO_1024	(0U << PHYADR_MPO_SHIFT)
#define		PHYADR_MPO_512	(1U << PHYADR_MPO_SHIFT)
#define		PHYADR_MPO_128	(2U << PHYADR_MPO_SHIFT)
#define		PHYADR_MPO_64	(3U << PHYADR_MPO_SHIFT)
#define	PHYADR_PHYAD	0x1fU		/* phy addrss mask (def 0x01) */
E 15


/* MIISR (offset 0x6d) */

D 15
#define	MIISR_PHYRST	0x80	/* Phy reset, by software driven */
#define	MIISR_GPIO1POL	0x80	/* Phy reset, by software driven */
#define	MIISR_MFDC	0x10	/* use default ext'l PHY device address as 1 */
#define	MIISR_PHYOPT	0x10	/* use default ext'l PHY device address as 1 */
#define	MIISR_MIIERR	0x08	/* Phy device received error */
#define	MIISR_MRERR	0x04	/* Phy device received error */
#define	MIISR_LNKFL	0x02	/* Link Fail */
#define	MIISR_SPD10	0x01	/* Phy Speed 1:100M, 0:10M */
E 15
I 15
#define	MIISR_PHYRST	0x80U	/* Phy reset, by software driven */
#define	MIISR_GPIO1POL	0x80U	/* Phy reset, by software driven */
#define	MIISR_MFDC	0x10U	/* use default ext'l PHY device address as 1 */
#define	MIISR_PHYOPT	0x10U	/* use default ext'l PHY device address as 1 */
#define	MIISR_MIIERR	0x08U	/* Phy device received error */
#define	MIISR_MRERR	0x04U	/* Phy device received error */
#define	MIISR_LNKFL	0x02U	/* Link Fail */
#define	MIISR_SPD10	0x01U	/* Phy Speed 1:100M, 0:10M */
E 15


/* BCR (offset 0x6e-0x6f) Bus Config register */
D 2

#define	BCR_DMA_MASK		0x0007	/* DMA length */
E 2
I 2
D 15
#define	BCR_MED_FDX	0x8000			/* fixed FDX mode (RHINE II) */
#define	BCR_MED_SPD100	0x4000			/* fixed 100M mode (RHINE II) */
#define	BCR_CTFT	0x3800			/* RX FIFO threshold */
#define		BCR_CTFT_USE_TDES	0	/* use tx descriptor */
#define		BCR_CTFT_MASK		0x7
#define		BCR_CTFT_SHIFT		11
#define	BCR_POT		0x0700			/* Polling timer interval */
#define		BCR_POT_MASK		0x7
#define		BCR_POT_SHIFT		8
#define	BCR_MED2	0x0080			/* Medium select control */
#define	BCR_EXTLED	0x0040			/* Extra LED control */
#define	BCR_CRFT	0x0038			/* RX FIFO threshold */
#define		BCR_CRFT_USE_RDES	0	/* use rx descriptor */
#define		BCR_CRFT_MASK		0x7
#define		BCR_CRFT_SHIFT		3
#define		BCR_CRFT_EXTLED		0x0040	/* Extra LED support control */
#define		BCR_CRFT_MED2		0x0080	/* Medium select control */
#define	BCR_DMA_MASK	0x0007			/* DMA length */
E 2
#define		BCR_DMA_32		0
#define		BCR_DMA_64		1
#define		BCR_DMA_128		2
#define		BCR_DMA_256		3
#define		BCR_DMA_512		4
#define		BCR_DMA_1024		5
#define		BCR_DMA_NOLIMIT		6
E 15
I 15
D 16
#define	BCR_VIDFLTR	0x8000U			/* VLAN ID filter (6105M) */
#define	BCR_HTQBLK	0x4000U			/* Higher tx queue blocks lower (6105M) */
#define	BCR_MED_FDX	0x8000U			/* fixed FDX mode (6102 II) */
#define	BCR_MED_SPD100	0x4000U			/* fixed 100M mode (6102 II) */
#define	BCR_CTFT	0x3800U			/* TX FIFO threshold */
E 16
I 16
#define	BCR_VIDFLTR	0x8000U		/* VLAN ID filter (IIIM) */
#define	BCR_HTQBLK	0x4000U		/* Higher tx queue blocks lower(IIIM) */
#define	BCR_MED_FDX	0x8000U		/* fixed FDX mode (II) */
#define	BCR_MED_SPD100	0x4000U		/* fixed 100M mode (II) */
#define	BCR_CTFT	0x3800U		/* TX FIFO threshold */
E 16
#define		BCR_CTFT_USE_TDES	0U	/* use tx descriptor */
#define		BCR_CTFT_MASK		0x7U
#define		BCR_CTFT_SHIFT		11U
#define	BCR_POT		0x0700U			/* Polling timer interval */
#define		BCR_POT_MASK		0x7U
#define		BCR_POT_SHIFT		8U
#define	BCR_MED2	0x0080U			/* Medium select control */
#define	BCR_EXTLED	0x0040U			/* Extra LED control */
#define	BCR_CRFT	0x0038U			/* RX FIFO threshold */
#define		BCR_CRFT_USE_RDES	0U	/* use rx descriptor */
#define		BCR_CRFT_MASK		0x7U
#define		BCR_CRFT_SHIFT		3U
#define		BCR_CRFT_EXTLED		0x0040U	/* Extra LED support control */
#define		BCR_CRFT_MED2		0x0080U	/* Medium select control */
#define	BCR_DMA_MASK	0x0007U			/* DMA length */
#define		BCR_DMA_32		0U
#define		BCR_DMA_64		1U
#define		BCR_DMA_128		2U
#define		BCR_DMA_256		3U
#define		BCR_DMA_512		4U
#define		BCR_DMA_1024		5U
#define		BCR_DMA_NOLIMIT		6U
E 15

D 2
#define	BCR_CRFT		0x0038	/* RX FIFO threshold */
#define		BCR_CRFT_USE_RDES	0	/* use rx descriptor */
#define		BCR_CRFT_MASK		0x7
#define		BCR_CRFT_SHIFT		3
#define		BCR_CRFT_EXTLED		0x0040	/* Extra LED support control */
#define		BCR_CRFT_MED2		0x0080	/* Medium select control */

#define	BCR_EXTLED		0x0040	/* Extra LED control */
#define	BCR_MED2		0x0080	/* Medium select control */

#define	BCR_POT			0x0700	/* Polling timer interval */
#define		BCR_POT_MASK		0x7
#define		BCR_POT_SHIFT		8
#define	BCR_CTFT		0x3800	/* RX FIFO threshold */
#define		BCR_CTFT_USE_TDES	0	/* use tx descriptor */
#define		BCR_CTFT_MASK		0x7
#define		BCR_CTFT_SHIFT		11

E 2
/* MIICR (0x70) MII interface control registger */
I 2
D 15
#define	MIICR_MAUTO	0x80	/* MII management auto port polling disable */
#define	MIICR_RCMD	0x40	/* Read enable, reset when read complete */
#define	MIICR_WCMD	0x20	/* Write enable, reset when write complete */
#define	MIICR_MDPM	0x10	/* Direct PHY programming mode enable */
#define	MIICR_MDOUT	0x08	/* Direct programming out put enable indicator*/
#define	MIICR_MDO	0x04	/* Direct programming status as management port data out */
E 2
#define	MIICR_MDC	0x01	/* Direct programming status as management port clock */
#define	MIICR_MDI	0x02	/* Direct programming input while PHY status */
E 15
I 15
#define	MIICR_MAUTO	0x80U	/* MII management auto port polling disable */
#define	MIICR_RCMD	0x40U	/* Read enable, reset when read complete */
#define	MIICR_WCMD	0x20U	/* Write enable, reset when write complete */
#define	MIICR_MDPM	0x10U	/* Direct PHY programming mode enable */
D 16
#define	MIICR_MDOUT	0x08U	/* Direct programming out put enable indicator*/
#define	MIICR_MDO	0x04U	/* Direct programming status as management port data out */
#define	MIICR_MDC	0x01U	/* Direct programming status as management port clock */
#define	MIICR_MDI	0x02U	/* Direct programming input while PHY status */
E 16
I 16
#define	MIICR_MDOUT	0x08U	/* DP output enable indicator */
#define	MIICR_MDO	0x04U	/* DP management port data out */
#define	MIICR_MDC	0x01U	/* DP management port clock */
#define	MIICR_MDI	0x02U	/* DP input while PHY status */
E 16
E 15
D 2
#define	MIICR_MDO	0x04	/* Direct programming status as management port data out */
#define	MIICR_MDOUT	0x08	/* Direct programming out put enable indicator*/
#define	MIICR_MDPM	0x10	/* Direct PHY programming mode enable */
#define	MIICR_WCMD	0x20	/* Write enable, reset when write complete */
#define	MIICR_RCMD	0x40	/* Read enable, reset when read complete */
#define	MIICR_MAUTO	0x80	/* MII management auto port polling disable */
E 2

/* MIIADR (0x71) MII CSR Offset address registger */
D 2
#define	MIIADR_MAD	0x1f	/* MII management port address */
#define	MIIADR_MDONE	0x20	/* MDIO auto polling data ready */
#define	MIIADR_MSRCEN	0x40	/* close the poll function of MDONE */
E 2
D 4
#define	MIIADR_MIDLE	0x80	/* not at polling cycle (VT6102 only) */
E 4
I 4
D 7
#define	MIIADR_MIDLE	0x80	/* not at polling cycle (VT6102 or later) */
E 7
I 7
D 15
#define	MIIADR_MIDLE	0x80	/* not in polling cycle (VT6102 or later) */
E 7
E 4
I 2
#define	MIIADR_MSRCEN	0x40	/* close the poll function of MDONE */
#define	MIIADR_MDONE	0x20	/* MDIO auto polling data ready */
#define	MIIADR_MAD	0x1f	/* MII management port address */
E 15
I 15
D 16
#define	MIIADR_MIDLE	0x80U	/* not in polling cycle (VT6102 or later) */
E 16
I 16
#define	MIIADR_MIDLE	0x80U	/* not in polling cycle (II or later) */
E 16
#define	MIIADR_MSRCEN	0x40U	/* close the poll function of MDONE */
#define	MIIADR_MDONE	0x20U	/* MDIO auto polling data ready */
#define	MIIADR_MAD	0x1fU	/* MII management port address */
E 15
E 2

/* MIIDATA(0x72-73) MII data register  */

/* EECSR (0x74) Direct program EEPROM interface */
D 9
#define	EECSR_EDO	0x01	/* data out status */
I 3
#define	EECSR_EDO_SHIFT	0	/* data out status */
E 3
#define	EECSR_EDI	0x02	/* data in status */
I 3
#define	EECSR_EDI_SHIFT	1	/* data in status */
E 3
#define	EECSR_ECK	0x04	/* clock status */
#define	EECSR_ECS	0x08	/* chip select status */
#define	EECSR_DPM	0x10	/* EEPROM mode */
#define	EECSR_AUTOLD	0x20	/* Dynamic reload EEPROM content */
#define	EECSR_EMBP	0x40	/* EEPROM embedded programming enable */
E 9
D 15
#define	EECSR_EEPR	0x80	/* EEPROM programmed status */
I 9
#define	EECSR_EMBP	0x40	/* EEPROM embedded programming enable */
#define	EECSR_AUTOLD	0x20	/* Dynamic reload EEPROM content */
#define	EECSR_DPM	0x10	/* EEPROM mode */
#define	EECSR_ECS	0x08	/* chip select status */
#define	EECSR_ECK	0x04	/* clock status */
#define	EECSR_EDI	0x02	/* data in status */
#define		EECSR_EDI_SHIFT	1	/* data in status */
E 15
I 15
#define	EECSR_EEPR	0x80U	/* EEPROM programmed status */
#define	EECSR_EMBP	0x40U	/* EEPROM embedded programming enable */
#define	EECSR_AUTOLD	0x20U	/* Dynamic reload EEPROM content */
#define	EECSR_DPM	0x10U	/* EEPROM mode */
#define	EECSR_ECS	0x08U	/* chip select status */
#define	EECSR_ECK	0x04U	/* clock status */
#define	EECSR_EDI	0x02U	/* data in status */
#define		EECSR_EDI_SHIFT	1U	/* data in status */
E 15
#define	EECSR_EDO	0x01	/* data out status */
D 15
#define		EECSR_EDO_SHIFT	0	/* data out status */
E 15
I 15
#define		EECSR_EDO_SHIFT	0U	/* data out status */
E 15
E 9

D 16
/* TEST (offset 0x75)*/
/* DEGUG0 (offset 0x76)*/
/* DEGUG1 (offset 0x77)*/
E 16
I 16
/* TEST (offset 0x75) */
/* DEGUG0 (offset 0x76) */
/* DEGUG1 (offset 0x77) */
E 16

/* CFGA (offset 0x78 ) configration A register */
D 8
#define	CFGA_MIIOPT	0x40	/* 0: w/o extension clk, 1: w/ extension clk */
E 8
D 7
#define	CFGA_EELOAD	0x80	/* Enable EEPROM embedded and directprograminng */
E 7
I 7
D 15
#define	CFGA_EELOAD	0x80	/* Enable EEPROM embedded and direct programming */
I 8
#define	CFGA_MIIOPT	0x40	/* 0: w/o extension clk, 1: w/ extension clk */
#define	CFGA_MMIOEN	0x20	/* enable memory mapped I/O (VT86C100A) */
E 15
I 15
D 16
#define	CFGA_EELOAD	0x80U	/* Enable EEPROM embedded and direct programming */
E 16
I 16
#define	CFGA_EELOAD	0x80U	/* Enable EEPROM and direct programming */
E 16
#define	CFGA_MIIOPT	0x40U	/* 0: w/o extension clk, 1: w/ extension clk */
#define	CFGA_MMIOEN	0x20U	/* enable memory mapped I/O (VT86C100A) */
E 15
E 8
E 7

/* CFGB (offset 0x79 ) configration B register */
D 2
#define	CFGB_LATMEN	0x01	/* latency timer */
#define	CFGB_MWAIT	0x02	/* Master write insert one wait state 2-2-2-2 */
#define	CFGB_MRWAIT	0x04	/* Master read insert one wait state 2-2-2-2 */
#define	CFGB_RXARBIT	0x08	/* Arbitration priority */
#define	CFGB_TXARBIT	0x10	/* Arbitration priority */
#define	CFGB_MRLDIS	0x20	/* Memory read line support 0:enable 1:disable*/
E 2
I 2
D 15
#define	CFGB_QPKTDIS	0x80	/* Disable transmit frame queuing */
E 2
#define	CFGB_PERRDIS	0x40	/* Disable data parity generation (6102) */
#define	CFGB_TXPACE	0x40	/* TX descriptor paceing algorithm (100) */
D 2
#define	CFGB_QPKTDIS	0x80	/* Disable transmit frame queuing */
E 2
I 2
#define	CFGB_MRLDIS	0x20	/* Memory read line support 0:enable 1:disable*/
#define	CFGB_TXARBIT	0x10	/* Arbitration priority */
#define	CFGB_RXARBIT	0x08	/* Arbitration priority */
#define	CFGB_MRWAIT	0x04	/* Master read insert one wait state 2-2-2-2 */
#define	CFGB_MWAIT	0x02	/* Master write insert one wait state 2-2-2-2 */
#define	CFGB_LATMEN	0x01	/* latency timer */
E 15
I 15
#define	CFGB_QPKTDIS	0x80U	/* Disable transmit frame queuing */
D 16
#define	CFGB_PERRDIS	0x40U	/* Disable data parity generation (6102) */
E 16
I 16
#define	CFGB_PERRDIS	0x40U	/* Disable data parity generation (II) */
E 16
#define	CFGB_TXPACE	0x40U	/* TX descriptor paceing algorithm (100) */
D 16
#define	CFGB_MRLDIS	0x20U	/* Memory read line support 0:enable 1:disable*/
E 16
I 16
#define	CFGB_MRLDIS	0x20U	/* Memory read line 0:enable 1:disable */
E 16
#define	CFGB_TXARBIT	0x10U	/* Arbitration priority */
#define	CFGB_RXARBIT	0x08U	/* Arbitration priority */
#define	CFGB_MRWAIT	0x04U	/* Master read insert one wait state 2-2-2-2 */
#define	CFGB_MWAIT	0x02U	/* Master write insert one wait state 2-2-2-2 */
#define	CFGB_LATMEN	0x01U	/* latency timer */
E 15
E 2

/* CFGC (offset 0x7a) */
D 2
#define	CFGC_BPS	0x07	/* BOOTPROM size select */
#define	CFGC_BPS_NONE	0x00	/*    NO BOOTPROM */
#define	CFGC_BPS_8K	0x01	/*    8K size */
#define	CFGC_BPS_16K	0x02	/*    16K size */
#define	CFGC_BPS_32K	0x03	/*    32K size */
#define	CFGC_BPS_64K	0x04	/*    64K size */
#define	CFGC_BTSEL	0x08	/* BOOTPROM timing select */
#define	CFGC_DLYEN	0x20	/* turn on delay transaction while memory read bootrprom */
#define	CFGC_BROPT	0x40	/* Tie the unused bootrom address MA to high */
E 2
D 15
#define	CFGC_MED3	0x80	/* Medium select control (VT6102) */
I 2
#define	CFGC_BROPT	0x40	/* Tie the unused bootrom address MA to high */
#define	CFGC_DLYEN	0x20	/* turn on delay transaction while memory read bootrprom */
#define	CFGC_BTSEL	0x08	/* BOOTPROM timing select */
#define	CFGC_BPS	0x07	/* BOOTPROM size select */
#define		CFGC_BPS_NONE	0x00	/*    NO BOOTPROM */
#define		CFGC_BPS_8K	0x01	/*    8K size */
#define		CFGC_BPS_16K	0x02	/*    16K size */
#define		CFGC_BPS_32K	0x03	/*    32K size */
#define		CFGC_BPS_64K	0x04	/*    64K size */
E 15
I 15
D 16
#define	CFGC_MED3	0x80U	/* Medium select control (VT6102) */
E 16
I 16
#define	CFGC_MED3	0x80U	/* Medium select control (II) */
E 16
#define	CFGC_BROPT	0x40U	/* Tie the unused bootrom address MA to high */
D 16
#define	CFGC_DLYEN	0x20U	/* turn on delay transaction while memory read bootrprom */
E 16
I 16
#define	CFGC_DLYEN	0x20U	/* turn on delay in reading bootrprom */
E 16
#define	CFGC_BTSEL	0x08U	/* BOOTPROM timing select */
#define	CFGC_BPS	0x07U	/* BOOTPROM size select */
#define		CFGC_BPS_NONE	0x00U	/*    NO BOOTPROM */
#define		CFGC_BPS_8K	0x01U	/*    8K size */
#define		CFGC_BPS_16K	0x02U	/*    16K size */
#define		CFGC_BPS_32K	0x03U	/*    32K size */
#define		CFGC_BPS_64K	0x04U	/*    64K size */
E 15
E 2

/* CFGD (offset 0x7b) */
D 2
#define	CFGD_BAKOPT	0x01	/* Backoff algorithm 0: disable, 1: enable */
#define	CFGD_MBA	0x02	/* Capture effect solusion : AMD solusion */
#define	CFGD_CAP	0x04	/* Capture effect solusion : DEC solusion */
#define	CFGD_CRANDOM	0x08	/* Backoff algorithm random */
#define	CFGD_PMCDIG	0x10	/* PMCC(0x82) setting mode (6102) */
#define	CFGD_MAGICKEY	0x10	/* Magic key enable(100) */
#define	CFGD_MRLEN	0x20	/* PCI memory read line capable 0:no, 1:yes */
#define	CFGD_DIAG	0x40	/* Diagnostic mode 0:disable, 1:enable */
E 2
D 15
#define	CFGD_MMIOEN	0x80	/* Memory mapped I/O access enable (6102) */
D 2
#define	CFGD_GPIO2	0x80	/* GPIO2 Input status change monitor(100) */*/
E 2
I 2
#define	CFGD_GPIOEN	0x80	/* GPIO2 Input status change monitor(100) */
#define	CFGD_DIAG	0x40	/* Diagnostic mode 0:disable, 1:enable */
#define	CFGD_MRLEN	0x20	/* PCI memory read line capable 0:no, 1:yes */
#define	CFGD_MAGICKEY	0x10	/* Magic key enable(100) */
#define	CFGD_PMCDIG	0x10	/* PMCC(0x82) setting mode (6102) */
D 13
#define	CFGD_CRANDOM	0x08	/* Backoff algorithm random */
#define	CFGD_CAP	0x04	/* Capture effect solusion : DEC solusion */
#define	CFGD_MBA	0x02	/* Capture effect solusion : AMD solusion */
E 13
I 13
#define	CFGD_CRANDOM	0x08	/* Backoff algorithm : random */
#define	CFGD_CAP	0x04	/* Capture effect solution : DEC solusion */
#define	CFGD_MBA	0x02	/* Capture effect solution : AMD solusion */
E 13
#define	CFGD_BAKOPT	0x01	/* Backoff algorithm 0: disable, 1: enable */
E 15
I 15
D 16
#define	CFGD_MMIOEN	0x80U	/* Memory mapped I/O access enable (6102) */
E 16
I 16
#define	CFGD_MMIOEN	0x80U	/* Memory mapped I/O access enable (II) */
E 16
#define	CFGD_GPIOEN	0x80U	/* GPIO2 Input status change monitor(100) */
#define	CFGD_DIAG	0x40U	/* Diagnostic mode 0:disable, 1:enable */
#define	CFGD_MRLEN	0x20U	/* PCI memory read line capable 0:no, 1:yes */
#define	CFGD_MAGICKEY	0x10U	/* Magic key enable(100) */
D 16
#define	CFGD_PMCDIG	0x10U	/* PMCC(0x82) setting mode (6102) */
E 16
I 16
#define	CFGD_PMCDIG	0x10U	/* PMCC(0x82) setting mode (II) */
E 16
#define	CFGD_CRANDOM	0x08U	/* Backoff algorithm : random */
#define	CFGD_CAP	0x04U	/* Capture effect solution : DEC solusion */
#define	CFGD_MBA	0x02U	/* Capture effect solution : AMD solusion */
#define	CFGD_BAKOPT	0x01U	/* Backoff algorithm 0: disable, 1: enable */
E 15
E 2

/* MISC (offset 0x80-0x81) */
D 2
#define	MISC_Tm0EN	0x0001	/* Enable software timer 0 */
#define	MISC_Tm0Susp	0x0002	/* 1 when Soft timer0 timeout */
#define	MISC_HDXFEN	0x0004	/* Half duplex flow control enable */
#define	MISC_FDXRFEN	0x0008	/* Full duplex flow control enable */
#define	MISC_Tm1EN	0x0100	/* Enable software timer 1 to count */
#define	MISC_VAXJMP	0x2000	/* There is a AUX power outside, for sofr ref.*/
E 2
D 15
#define	MISC_FORSRST	0x4000	/* Force software reset */
I 2
#define	MISC_VAXJMP	0x2000	/* There is a AUX power outside, for sofr ref.*/
#define	MISC_Tm1EN	0x0100	/* Enable software timer 1 to count */
D 11
#define	MISC_FDXRFEN	0x0008	/* Full duplex flow control enable */
E 11
I 11
#define	MISC_Tm0US	0x0020	/* timer 0 micro second mode */
#define	MISC_FDXTFEN	0x0010	/* Full duplex flow tx control enable */
#define	MISC_FDXRFEN	0x0008	/* Full duplex flow rx control enable */
E 11
#define	MISC_HDXFEN	0x0004	/* Half duplex flow control enable */
#define	MISC_Tm0Susp	0x0002	/* 1 when Soft timer0 timeout */
#define	MISC_Tm0EN	0x0001	/* Enable software timer 0 */
E 15
I 15
#define	MISC_FORSRST	0x4000U	/* Force software reset */
D 16
#define	MISC_VAXJMP	0x2000U	/* There is a AUX power outside, for sofr ref.*/
E 16
I 16
#define	MISC_VAXJMP	0x2000U	/* There is a AUX power outside, for soft ref */
E 16
#define	MISC_Tm1EN	0x0100U	/* Enable software timer 1 to count */
#define	MISC_Tm0US	0x0020U	/* timer 0 micro second mode */
#define	MISC_FDXTFEN	0x0010U	/* Full duplex flow tx control enable */
#define	MISC_FDXRFEN	0x0008U	/* Full duplex flow rx control enable */
#define	MISC_HDXFEN	0x0004U	/* Half duplex flow control enable */
#define	MISC_Tm0Susp	0x0002U	/* 1 when Soft timer0 timeout */
#define	MISC_Tm0EN	0x0001U	/* Enable software timer 0 */
E 15
E 2

/* STICKHW (offset 0x83) */
D 2
#define	STICKHW_DS0	0x01	/* Sticky DS0_shadow, suspend well DS write port */
#define	STICKHW_DS1	0x02	/* Sticky DS0_shadow, R/W by software */
#define	STICKHW_WOLEN	0x04	/* Legacy WOL enable */
#define	STICKHW_WOLSR	0x08	/* Legacy WOL status */
E 2
D 16
#define	STICKHW_LGWOL	0x80	/* Legacy WOL enable, status for software reference from jumper strapping MD5 */
E 16
I 16
#define	STICKHW_LGWOL	0x80	/* Legacy WOL enable, jumper strapping MD5 */
E 16
I 2
D 15
#define	STICKHW_WOLSR	0x08	/* Legacy WOL status */
#define	STICKHW_WOLEN	0x04	/* Legacy WOL enable */
#define	STICKHW_DS1	0x02	/* Sticky DS0_shadow, R/W by software */
#define	STICKHW_DS0	0x01	/* Sticky DS0_shadow, suspend well DS write port */
E 15
I 15
#define	STICKHW_WOLSR	0x08U	/* Legacy WOL status */
#define	STICKHW_WOLEN	0x04U	/* Legacy WOL enable */
D 16
#define	STICKHW_DS1	0x02U	/* Sticky DS0_shadow, R/W by software */
#define	STICKHW_DS0	0x01U	/* Sticky DS0_shadow, suspend well DS write port */
E 16
I 16
#define	STICKHW_DS1	0x02U	/* Sticky DS1_shadow, R/W by software */
#define	STICKHW_DS0	0x01U	/* Sticky DS0_shadow, suspend well write port */
E 16
E 15
E 2

/* MISR (offset 0x84) */
D 2
#define	MISR_TIM0I	0x01	/* Software timer 0 interrupt */
#define	MISR_TIM1I	0x02	/* Software timer 1 interrupt */
#define	MISR_TDWBI	0x08	/* TD WB queue race, will cause when TX shotdown*/
#define	MISR_SSRCI	0x10	/* */
E 2
I 2
D 15
#define	MISR_PMEI	0x80	/* Power event report in test mode */
E 2
D 7
#define	MISR_UDPIS	0x40	/* User defined, host driven interrupt */
#define	MISR_UDPI	0x40	/* User defined, host driven interrupt */
D 2
#define	MISR_PMEI	0x80	/* Power event report in test mode */
E 2
I 2
#define	MISR_SSRCI	0x10	/* */
E 7
I 7
#define	MISR_UDPICLR	0x40	/* User defined, host driven interrupt */
#define	MISR_UDPISET	0x20	/* User defined, host driven interrupt */
#define	MISR_SSRCI	0x10	/* suspend well status changed */
E 7
#define	MISR_TDWBI	0x08	/* TD WB queue race, will cause when TX shotdown*/
I 7
#define	MISR_PHYI	0x04	/* PHY status changed */
E 7
#define	MISR_TIM1I	0x02	/* Software timer 1 interrupt */
#define	MISR_TIM0I	0x01	/* Software timer 0 interrupt */
E 15
I 15
#define	MISR_PMEI	0x80U	/* Power event report in test mode */
#define	MISR_UDPICLR	0x40U	/* User defined, host driven interrupt */
#define	MISR_UDPISET	0x20U	/* User defined, host driven interrupt */
#define	MISR_SSRCI	0x10U	/* suspend well status changed */
D 16
#define	MISR_TDWBI	0x08U	/* TD WB queue race, will cause when TX shotdown*/
E 16
I 16
#define	MISR_TDWBI	0x08U	/* TD WB queue race interrupt */
E 16
#define	MISR_PHYI	0x04U	/* PHY status changed */
#define	MISR_TIM1I	0x02U	/* Software timer 1 interrupt */
#define	MISR_TIM0I	0x01U	/* Software timer 0 interrupt */
E 15
E 2

I 7
#define	MISR_BITS	\
	"\020\010PMEI\007UDPI_CLR\007UDPICLR\006UDPISET\005SSRCI"	\
	"\004TDWBI\003PHYI\002TIM1I\001TIM0I"

E 7
/* MIMR (offset 0x86) */
D 2
#define	MIMR_TIM0IM	0x01	/* Software timer 0 interrupt mask */
#define	MIMR_TIM1IM	0x02	/* Software timer 1 interrupt mask */
#define	MIMR_TDWBIM	0x08	/* TD WB queue race, will cause when TX shotdown mask*/
#define	MIMR_SSRCIM	0x10	/* */
#define	MIMR_UDPIM	0x40	/* User defined, host driven interrupt mask*/
E 2
D 15
#define	MIMR_PMEIM	0x80	/* Power event report in test mode mask */
I 7
#define	MIMR_UDPI	0x40	/* User defined, host driven interrupt mask*/
E 7
I 2
#define	MIMR_UDPIM	0x40	/* User defined, host driven interrupt mask*/
#define	MIMR_SSRCIM	0x10	/* */
#define	MIMR_TDWBIM	0x08	/* TD WB queue race, will cause when TX shotdown mask*/
#define	MIMR_TIM1IM	0x02	/* Software timer 1 interrupt mask */
#define	MIMR_TIM0IM	0x01	/* Software timer 0 interrupt mask */
E 15
I 15
#define	MIMR_PMEIM	0x80U	/* Power event report in test mode mask */
D 16
#define	MIMR_UDPI	0x40U	/* User defined, host driven interrupt mask*/
#define	MIMR_UDPIM	0x40U	/* User defined, host driven interrupt mask*/
E 16
I 16
#define	MIMR_UDPI	0x40U	/* User defined, host driven interrupt mask */
#define	MIMR_UDPIM	0x40U	/* User defined, host driven interrupt mask */
E 16
#define	MIMR_SSRCIM	0x10U	/* */
D 16
#define	MIMR_TDWBIM	0x08U	/* TD WB queue race, will cause when TX shotdown mask*/
E 16
I 16
#define	MIMR_TDWBIM	0x08U	/* TD WB queue race interrupt mask */
E 16
#define	MIMR_TIM1IM	0x02U	/* Software timer 1 interrupt mask */
#define	MIMR_TIM0IM	0x01U	/* Software timer 0 interrupt mask */
E 15
E 2
D 5

E 5
/* BPMA (offset 0x8c-0c8d) */
/* BPMD (offset 0x8f) */
/* BPCMD (offset 0x90) */
D 2
#define BPCMD_EBPRD	0x01	/* BOOTROM embedded read command */
E 2
D 15
#define BPCMD_EBPWR	0x02	/* BOOTROM embedded write command */
I 2
#define BPCMD_EBPRD	0x01	/* BOOTROM embedded read command */
E 15
I 15
D 16
#define BPCMD_EBPWR	0x02U	/* BOOTROM embedded write command */
#define BPCMD_EBPRD	0x01U	/* BOOTROM embedded read command */
E 16
I 16
#define	BPCMD_EBPWR	0x02U	/* BOOTROM embedded write command */
#define	BPCMD_EBPRD	0x01U	/* BOOTROM embedded read command */
E 16
E 15
E 2

/* BPIN_DATA (offset 0x91) */
I 5

/* CAMCTRL (offset 0x92) 6105M only */
D 15
#define	CAMCTRL_RD	0x08	/* cam read command */
#define	CAMCTRL_WR	0x04	/* cam write command */
D 13
#define	CAMCTRL_VLAN	0x02	/* cam select (1: VLAN 0: multicast)*/
E 13
I 13
#define	CAMCTRL_VLAN	0x02	/* cam select (1:VLAN, 0:multicast) */
E 13
#define	CAMCTRL_EN	0x01	/* enable cam access */
E 15
I 15
#define	CAMCTRL_RD	0x08U	/* cam read command */
#define	CAMCTRL_WR	0x04U	/* cam write command */
#define	CAMCTRL_VLAN	0x02U	/* cam select (1:VLAN, 0:multicast) */
#define	CAMCTRL_EN	0x01U	/* enable cam access */
E 15

E 5
/* EE_CHKSUM (offset 0x93) */
/* SUSPEND_MII_AD (offset 0x94-95) */
/* SU_PHYID (offset 0x96) */
D 9
/* PAUSE_TIMER (offset 0x98-0x99) */
I 4
/* FCR1 (offset 0x99) rhine3 */
E 9
I 9
/* FCR0 (offset 0x98) rhine3 only */
/* FCR1 (offset 0x99) rhine3 only */
E 9
D 16
#define FCR1_TXLOWAT	0xc0
E 16
I 16
#define	FCR1_TXLOWAT	0xc0
E 16
D 9
#define FCR1_TXLOWAT_SHIFT	6
E 9
I 9
D 15
#define		FCR1_TXLOWAT_MASK	0x3
#define		FCR1_TXLOWAT_SHIFT	6
#define		FCR1_TXLOWAT_4	(0 << FCR1_TXLOWAT_SHIFT)
#define		FCR1_TXLOWAT_8	(1 << FCR1_TXLOWAT_SHIFT)
#define		FCR1_TXLOWAT_16	(2 << FCR1_TXLOWAT_SHIFT)
#define		FCR1_TXLOWAT_24	(3 << FCR1_TXLOWAT_SHIFT)
E 15
I 15
#define		FCR1_TXLOWAT_MASK	0x3U
#define		FCR1_TXLOWAT_SHIFT	6U
#define		FCR1_TXLOWAT_4	(0U << FCR1_TXLOWAT_SHIFT)
#define		FCR1_TXLOWAT_8	(1U << FCR1_TXLOWAT_SHIFT)
#define		FCR1_TXLOWAT_16	(2U << FCR1_TXLOWAT_SHIFT)
#define		FCR1_TXLOWAT_24	(3U << FCR1_TXLOWAT_SHIFT)
E 15
E 9
D 16
#define FCR1_TXHIWAT	0x30
E 16
I 16
#define	FCR1_TXHIWAT	0x30
E 16
D 9
#define FCR1_TXHIWAT_SHIFT	4
#define FCR1_XONOFF_EN	0x08
#define FCR1_FDFCTX_EN	0x04
#define FCR1_FDFCRX_EN	0x02
#define FCR1_HDFC_EN	0x01
E 4
/* PAUSE_SR (offset 0x9a-0x9b) */
E 9
I 9
D 15
#define		FCR1_TXHIWAT_MASK	0x3
#define		FCR1_TXHIWAT_SHIFT	4
#define		FCR1_TXHIWAT_24	(0 << FCR1_TXHIWAT_SHIFT)
#define		FCR1_TXHIWAT_32	(1 << FCR1_TXHIWAT_SHIFT)
#define		FCR1_TXHIWAT_48	(2 << FCR1_TXHIWAT_SHIFT)
#define		FCR1_TXHIWAT_64	(3 << FCR1_TXHIWAT_SHIFT)
#define FCR1_XONOFF_EN	0x08	/* enable sending xoff pause frame */
#define FCR1_FDFCTX_EN	0x04	/* enable sending pause frame */
#define FCR1_FDFCRX_EN	0x02	/* enable receiving pause frame */
#define FCR1_HDFC_EN	0x01	/* enable half duplex flow control */
E 15
I 15
#define		FCR1_TXHIWAT_MASK	0x3U
#define		FCR1_TXHIWAT_SHIFT	4U
#define		FCR1_TXHIWAT_24	(0U << FCR1_TXHIWAT_SHIFT)
#define		FCR1_TXHIWAT_32	(1U << FCR1_TXHIWAT_SHIFT)
#define		FCR1_TXHIWAT_48	(2U << FCR1_TXHIWAT_SHIFT)
#define		FCR1_TXHIWAT_64	(3U << FCR1_TXHIWAT_SHIFT)
D 16
#define FCR1_XONOFF_EN	0x08U	/* enable sending xoff pause frame */
#define FCR1_FDFCTX_EN	0x04U	/* enable sending pause frame */
#define FCR1_FDFCRX_EN	0x02U	/* enable receiving pause frame */
#define FCR1_HDFC_EN	0x01U	/* enable half duplex flow control */
E 16
I 16
#define	FCR1_XONOFF_EN	0x08U	/* enable sending xoff pause frame */
#define	FCR1_FDFCTX_EN	0x04U	/* enable sending pause frame */
#define	FCR1_FDFCRX_EN	0x02U	/* enable receiving pause frame */
#define	FCR1_HDFC_EN	0x01U	/* enable half duplex flow control */
E 16
E 15

/* PAUSE_TIMER (offset 0x9a-0x9b) pause timer value to send */
E 9
D 10
/* SOFT_TIMER0 (offset 0x9c-0x9d) */
/* SOFT_TIMER1 (offset 0x9e-0x9f) */
E 10
I 10
/* SOFT_TMR0 (offset 0x9c-0x9d) */
/* SOFT_TMR1 (offset 0x9e-0x9f) */
E 10

D 7
/* WOLCR.SET WOLCR.CLR (offset 0xa0, 0xa4 RW) Wake On Lan command register */
D 2
#define	WOLCR_PTNMH	0x0f	/* enable pattern match filtering */
#define	WOLCR_UNICAST	0x10	/* enable UNICAST filter */
#define	WOLCR_MAGICEN	0x20	/* enable Magic packet filter */
#define	WOLCR_LinkON	0x40	/* enable link on detected */
E 2
#define	WOLCR_LinkOFF	0x80	/* enable link oof detected */
E 7
I 7
/* WOLCR.SET WOLCR.CLR (offset 0xa0, 0xa4 RWC) Wake On Lan command register */
D 15
#define	WOLCR_LinkOFF	0x80	/* enable link of detected */
E 7
I 2
#define	WOLCR_LinkON	0x40	/* enable link on detected */
#define	WOLCR_MAGICEN	0x20	/* enable Magic packet filter */
#define	WOLCR_UNICAST	0x10	/* enable UNICAST filter */
#define	WOLCR_PTNMH	0x0f	/* enable pattern match filtering */
E 15
I 15
#define	WOLCR_LinkOFF	0x80U	/* enable link of detected */
#define	WOLCR_LinkON	0x40U	/* enable link on detected */
#define	WOLCR_MAGICEN	0x20U	/* enable Magic packet filter */
#define	WOLCR_UNICAST	0x10U	/* enable UNICAST filter */
#define	WOLCR_PTNMH	0x0fU	/* enable pattern match filtering */
E 15
E 2

D 7
/* PWCFG.SET PWCFG.CLR (offset 0xa1, 0xa5 RW) */
E 7
I 7
/* PWCFG.SET PWCFG.CLR (offset 0xa1, 0xa5 RWC) */
E 7
D 2
#define	PWCFG_WOLEN	0x01	/* Legacy WOL_EN shadow */
#define	PWCFG_WOLSR	0x02	/* Legacy WOL_SR shadow */
#define	PWCFG_LEGCYWOL	0x10	/* Enale legacy wake on lan */
#define	PWCFG_WOLTYPE	0x20	/* Drive WOL output by 1:pulse or 0:button */
E 2
D 15
#define	PWCFG_SMIITIME	0x80	/* Internal MII interface timing */
I 2
#define	PWCFG_WOLTYPE	0x20	/* Drive WOL output by 1:pulse or 0:button */
#define	PWCFG_LEGCYWOL	0x10	/* Enale legacy wake on lan */
#define	PWCFG_WOLSR	0x02	/* Legacy WOL_SR shadow */
#define	PWCFG_WOLEN	0x01	/* Legacy WOL_EN shadow */
E 15
I 15
#define	PWCFG_SMIITIME	0x80U	/* Internal MII interface timing */
#define	PWCFG_WOLTYPE	0x20U	/* Drive WOL output by 1:pulse or 0:button */
#define	PWCFG_LEGCYWOL	0x10U	/* Enale legacy wake on lan */
#define	PWCFG_WOLSR	0x02U	/* Legacy WOL_SR shadow */
#define	PWCFG_WOLEN	0x01U	/* Legacy WOL_EN shadow */
E 15
E 2

D 7
/* TESTREG.SET TESTREG.CLR (offset 0xa2, 0xa6 RW) */
E 7
I 7
/* TESTREG.SET TESTREG.CLR (offset 0xa2, 0xa6 RWC) */
E 7
D 15
#define	TESTREG_SNORM	0x01	/* All power state capable while PHYTEST=0 */
E 15
I 15
#define	TESTREG_SNORM	0x01U	/* All power state capable while PHYTEST=0 */
E 15

D 7
/* WOLCG.SET WOLCG.CLR (offset 0xa3, 0xa7 RW) */
E 7
I 7
/* WOLCG.SET WOLCG.CLR (offset 0xa3, 0xa7 RWC) */
E 7
D 2
#define	WOLCG_SMIIOPT	0x04	/* MIIOPT to extend clock in suspend well */
#define	WOLCG_SMIIACC	0x08	/* MDC acceleration */
#define	WOLCG_SAB	0x10	/* Accept broadcast in suspend well */
#define	WOLCG_SAM	0x20	/* Accept multicast in suspend well */
#define	WOLCG_SFDX	0x40	/* Full duplex in suspend well */
E 2
D 15
#define	WOLCG_PMEOVR	0x80	/* Force PMEEN always over PME_EN (legacy) */
I 2
#define	WOLCG_SFDX	0x40	/* Full duplex in suspend well */
#define	WOLCG_SAM	0x20	/* Accept multicast in suspend well */
#define	WOLCG_SAB	0x10	/* Accept broadcast in suspend well */
#define	WOLCG_SMIIACC	0x08	/* MDC acceleration */
#define	WOLCG_SMIIOPT	0x04	/* MIIOPT to extend clock in suspend well */
E 15
I 15
#define	WOLCG_PMEOVR	0x80U	/* Force PMEEN always over PME_EN (legacy) */
#define	WOLCG_SFDX	0x40U	/* Full duplex in suspend well */
#define	WOLCG_SAM	0x20U	/* Accept multicast in suspend well */
#define	WOLCG_SAB	0x10U	/* Accept broadcast in suspend well */
#define	WOLCG_SMIIACC	0x08U	/* MDC acceleration */
#define	WOLCG_SMIIOPT	0x04U	/* MIIOPT to extend clock in suspend well */
E 15
E 2

D 7
/* PWRCSR.SET PSWCSR.CLR (offset 0xa8, 0xac) undocumented */
E 7
I 7
/* PWRCSR.SET PSWCSR.CLR (offset 0xa8, 0xac RWC) undocumented */
E 7

/* PATTERN CRC0-3 (offset 0xb0-0xbf, RW) */
/* BYTEMASK0-3 CRC0-3 (offset 0xc0-0xff, RW) */
I 16

#endif	/* _RHINEREG_H_ */
E 16
D 2

/*
 * MII interface, status flags.
 * Not to be confused with the MIIStatus register ...
 */
enum mii_status_bits {
	MIICap100T4		= 0x8000,
	MIICap10100HdFd		= 0x7800,
	MIIPreambleSupr		= 0x0040,
	MIIAutoNegCompleted	= 0x0020,
	MIIRemoteFault		= 0x0010,
	MIICapAutoNeg		= 0x0008,
	MIILink			= 0x0004,
	MIIJabber		= 0x0002,
	MIIExtended		= 0x0001,
};
E 2
E 1
