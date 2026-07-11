h34835
s 00338/00317/00362
d D 1.5 08/03/04 14:53:00 mrym 5 4
c 2.6.0
e
s 00002/00002/00677
d D 1.4 06/03/24 00:51:18 mrym 4 3
c 2.0.2
e
s 00018/00015/00661
d D 1.3 06/03/15 00:41:42 mrym 3 2
c 2.0.1
e
s 00021/00020/00655
d D 1.2 05/04/22 23:58:18 mrym 2 1
c amke
e
s 00675/00000/00000
d D 1.1 05/02/08 22:47:24 mrym 1 0
c date and time created 05/02/08 22:47:24 by mrym
e
u
U
f e 0
t
T
I 1
/*
 * vt612xreg.h : Macro definitions for VIA VT612x ethernet mac chips.
 * Coded by Masayuki Murayama (KHF04453@nifty.ne.jp)
 * this file is public domain.
 */

D 5
#pragma	ident	"%W% %E%"
E 5
I 5
#pragma	ident	"%Z%%M% %I%     %E%"
E 5

I 5
#ifndef _VT612XREG_H_
#define	_VT612XREG_H_

E 5
/*
 * Known PCI vendor-id/device-id for rhine chips
 */
#define	VID_VIA		0x1106
#define	DID_VT6122	0x3119

/*
 * VIA Velocity series Register definitions
 */
#define	NUM_TX_QUEUES	4

#define	MAX_HW_MIB_COUNTER	32
#define	VELOCITY_MIN_MTU	1500
#define	VELOCITY_MAX_MTU	9000

/* Offsets to the device registers. */
#define	PAR		0x00	/* B*6: Physical addr */
#define	RCR		0x06	/* B: Rx Config */
#define	TCR		0x07	/* B: Tx Config */
#define	CR_SET		0x08	/* L: Command Reg for set operation */
#define	CR_CLR		0x0c	/* L: Command Reg for clear operation */
#define	MAR		0x10	/* B*8: Multicast Addr hash */
#define	CAM		0x10	/* B*8: Multicast Addr */
#define	ISRCTL		0x20	/* W: */
#define	TXESR		0x22	/* B: tx error status */
#define	RXESR		0x23	/* B: rx error status */
#define	ISR		0x24	/* L: Interrupt Status */
#define	IMR		0x28	/* L: Interrupt Mask */
#define	TDCSR_SET	0x30	/* W: */
#define	RDCSR_SET	0x32	/* W: */
#define	TDCSR_CLR	0x34	/* W: */
#define	RDCSR_CLR	0x36	/* W: */
#define	RDBASE_LO	0x38	/* L: Base addr of Rx descriptor */
D 5
#define	RDINDEX		0x3C	/* L: */
E 5
I 5
#define	RDINDEX		0x3c	/* W: */
#define	TQETMR		0x3e	/* W: */
E 5
#define	TDBASE_LO	0x40	/* L*4: Base addr of Tx descriptor */
#define	RDCSIZE		0x50	/* W: number of rx descriptors */
#define	TDCSIZE		0x52	/* W: number of tx descriptors */
#define	TDINDEX		0x54	/* W*4: */
#define	PAUSE_TIMER	0x5c	/* W:  */
#define	RBRDU		0x5e	/* W:  */

#define	CAMADDR		0x68	/* B: CAM address */
#define	CAMCR		0x69	/* B: CAM control */

#define	MIICFG		0x6c	/* B: MII Configuration */
#define	MIISR		0x6d	/* B: MII status */

#define	PHYSR0		0x6e	/* B: PHY status */
#define	PHYSR1		0x6f	/* B: PHY status */

#define	MIICR		0x70	/* B: MII control */
#define	MIIADR		0x71	/* B: MII address  */
#define	MIIDATA		0x72	/* W: MII data */

D 2
#define	SOFT_TIMER0	0x74	/* W: soft timer 0 (one short) */
#define	SOFT_TIMER1	0x76	/* W: soft timer 1 (periodic) */
E 2
I 2
#define	SOFT_TMR0	0x74	/* W: soft timer 0 (one short) */
#define	SOFT_TMR1	0x76	/* W: soft timer 1 (periodic) */
E 2

#define	CFGA		0x78	/* B: configuration A register */
#define	CFGB		0x79	/* B: configuration B register */
#define	CFGC		0x7a	/* B: configuration C register */
#define	CFGD		0x7b	/* B: configuration D register */
#define	DCFG		0x7c	/* W: DMA configuration register */
#define	MCFG0		0x7e	/* B: misc configuration register */
#define	MCFG1		0x7f	/* B: misc configuration register */

#define	TBIST		0x80	/* B: tx built-in test register */
#define	RBIST		0x81	/* B: rx built-in test register */
#define	PMCC		0x82	/* B */
#define	STICKHW		0x83	/* B */
#define	MIBCR		0x84	/* B */
#define	EERSV		0x85	/* B */
#define	REVID		0x86	/* B */
#define	MIBREAD		0x88	/* L */
#define	BPMA		0x8c	/* W */
#define	EEWR_DATA	0x8c	/* W */
#define	BPMA_WR		0x8f	/* L */
#define	BPCMD		0x90	/* B */
#define	BPCMD_RD	0x91	/* B */
#define	EECHKSUM	0x92	/* B */
#define	EECSR		0x93	/* B */
#define	EERD_DATA	0x94	/* W */
#define	EADDR		0x96	/* B */
#define	EMBCMD		0x97	/* B */
#define	JMPSR0		0x98	/* B */
#define	JMPSR1		0x99	/* B */
#define	JMPSR2		0x9a	/* B */
#define	JMPSR3		0x9b	/* B */
#define	GMSR		0x9c	/* B */
#define	TESTCFG		0x9d	/* B */
#define	DEBUG_REG	0x9e	/* B */
#define	GMCR		0x9f	/* B */

D 5
#define	WOLCR_SET	0xa0	/* B: Wake On Lan command register */ 
E 5
I 5
#define	WOLCR_SET	0xa0	/* B: Wake On Lan command register */
E 5
#define	PWCFG_SET	0xa1	/* B */
#define	TSTREG_SET	0xa2	/* B */
#define	WOLCFG_SET	0xa3	/* B */
#define	WOLCR_CLR	0xa4	/* B */
#define	PWCFG_CLR	0xa5	/* B */
#define	TSTREG_CLR	0xa6	/* B */
#define	WOLCFG_CLR	0xa7	/* B */
#define	PWRCSR_SET	0xa8	/* B */
#define	PWRCSR1_SET	0xa9	/* B */
#define	PWRCSR_CLR	0xac	/* B */
#define	PWRCSR1_CLR	0xad	/* B */
#define	PATRN_CRC	0xb0	/* L */
#define	BYTEMSK0	0xc0	/* L */
#define	BYTEMSK1	0xd0	/* L */
#define	BYTEMSK2	0xe0	/* L */
#define	BYTEMSK3	0xf0	/* L */

#define	MULTICAST_CAM_SIZE	64
#define	VLANTAG_CAM_SIZE	64

/* offset 0x00-0x05  Ethernet Address 0x00-0x05 */
/* No bit field */

/* RCR (offset 0x06, RW) Receive Control register */
D 4
#define	RCR_AS		0x80	/* */
#define	RCR_AP		0x40	/* */
E 4
I 4
D 5
#define	RCR_AS		0x80	/* accept symbol error packets */
#define	RCR_AP		0x40	/* accept CAM filtered packets */
E 4
#define	RCR_AL		0x20	/* accecpt long packets */
#define	RCR_PRO		0x10	/* promiscous, accept all physical packets */
#define	RCR_AB		0x08	/* accept broadcast packets */
#define	RCR_AM		0x04	/* accept multicast packets */
#define	RCR_AR		0x02	/* accept small (runt) packets */
#define	RCR_SEP		0x01	/* accept error packets */
E 5
I 5
#define	RCR_AS		0x80U	/* accept symbol error packets */
#define	RCR_AP		0x40U	/* accept CAM filtered packets */
#define	RCR_AL		0x20U	/* accecpt long packets */
#define	RCR_PRO		0x10U	/* promiscous, accept all physical packets */
#define	RCR_AB		0x08U	/* accept broadcast packets */
#define	RCR_AM		0x04U	/* accept multicast packets */
#define	RCR_AR		0x02U	/* accept small (runt) packets */
#define	RCR_SEP		0x01U	/* accept error packets */
E 5

#define	RCR_BITS	"\020\5Promisc\4ABroad\3AMulti\2ARunt\1SEP"

/* TCR (offset 0x07, RW) Transmit Control Register */
D 5
#define	TCR_TB2BDIS	0x80
#define	TCR_COLTMC	0x0c
E 5
I 5
#define	TCR_TB2BDIS	0x80U
#define	TCR_COLTMC	0x0cU
E 5
#define		TCR_COLTMC_MASK	0x3
#define		TCR_COLTMC_SHIFT	2
D 5
#define	TCR_LB		0x03
E 5
I 5
#define	TCR_LB		0x03U
E 5
#define		TCR_LB_SHIFT		0
D 5
#define		TCR_LB_NORMAL		(0 << TCR_LB_SHIFT)
#define		TCR_LB_LOOPBACK		(1 << TCR_LB_SHIFT)
#define		TCR_LB_MIILOOPBACK	(2 << TCR_LB_SHIFT)
#define		TCR_LB_233LOOPBACK	(3 << TCR_LB_SHIFT)
E 5
I 5
#define		TCR_LB_NORMAL		(0U << TCR_LB_SHIFT)
#define		TCR_LB_LOOPBACK		(1U << TCR_LB_SHIFT)
#define		TCR_LB_MIILOOPBACK	(2U << TCR_LB_SHIFT)
#define		TCR_LB_233LOOPBACK	(3U << TCR_LB_SHIFT)
E 5


/* CR(offset 0x08-0x0b, RW) Command register */
D 5
#define	CR_GSPRST	0x80000000
#define	CR_FORSRST	0x40000000	/* force to reset nic */
#define	CR_FPHYRST	0x20000000	/* assert phy reset */
#define	CR_DIAG		0x10000000	/* enable diagnostic mode */
#define	CR_INTPCTL	0x04000000	/* enable interrupt pace control */
#define	CR_GINTMSK1	0x02000000	/* enable all masks */
#define	CR_GINTMSK0	0x01000000
E 5
I 5
#define	CR_GSPRST	0x80000000U
#define	CR_FORSRST	0x40000000U	/* force to reset nic */
#define	CR_FPHYRST	0x20000000U	/* assert phy reset */
#define	CR_DIAG		0x10000000U	/* enable diagnostic mode */
#define	CR_INTPCTL	0x04000000U	/* enable interrupt pace control */
#define	CR_GINTMSK1	0x02000000U	/* enable all masks */
#define	CR_GINTMSK0	0x01000000U
E 5

D 5
#define CR_XONEN	0x00800000	/* enable 802.3x xon/off flow control */
#define CR_FDXTFCEN	0x00400000	/* enable full-duplex TX flow control */
#define CR_FDXRFCEN	0x00200000	/* enable full-duplex RX flow control */
#define CR_HDXFCEN	0x00100000	/* enable half-duplex flow control */
#define CR_TXHIWAT	0x000c0000	/* TX XON high threshold */
E 5
I 5
#define	CR_XONEN	0x00800000U	/* enable 802.3x xon/off flow control */
#define	CR_FDXTFCEN	0x00400000U	/* enable full-duplex TX flow control */
#define	CR_FDXRFCEN	0x00200000U	/* enable full-duplex RX flow control */
#define	CR_HDXFCEN	0x00100000U	/* enable half-duplex flow control */
#define	CR_TXHIWAT	0x000c0000U	/* TX XON high threshold */
E 5
#define		CR_TXHIWAT_SHIFT	18
D 5
#define		CR_TXHIWAT_24	(0 << CR_TXHIWAT_SHIFT)
#define		CR_TXHIWAT_32	(1 << CR_TXHIWAT_SHIFT)
#define		CR_TXHIWAT_48	(2 << CR_TXHIWAT_SHIFT)
#define		CR_TXHIWAT_64	(3 << CR_TXHIWAT_SHIFT)
E 5
I 5
#define		CR_TXHIWAT_24	(0U << CR_TXHIWAT_SHIFT)
#define		CR_TXHIWAT_32	(1U << CR_TXHIWAT_SHIFT)
#define		CR_TXHIWAT_48	(2U << CR_TXHIWAT_SHIFT)
#define		CR_TXHIWAT_64	(3U << CR_TXHIWAT_SHIFT)
E 5
#define		CR_TXHIWAT_MASK	(CR_TXHIWAT >> CR_TXHIWAT_SHIFT)
D 5
#define CR_TXLOWAT	0x00030000	/* TX pause frame low threshold */
#define		CR_TXLOWAT_MASK	0x3
E 5
I 5
#define	CR_TXLOWAT	0x00030000U	/* TX pause frame low threshold */
#define		CR_TXLOWAT_MASK	0x3U
E 5
#define		CR_TXLOWAT_SHIFT	16
D 5
#define		CR_TXLOWAT_4	(0 << CR_TXLOWAT_SHIFT)
#define		CR_TXLOWAT_8	(1 << CR_TXLOWAT_SHIFT)
#define		CR_TXLOWAT_16	(2 << CR_TXLOWAT_SHIFT)
#define		CR_TXLOWAT_24	(3 << CR_TXLOWAT_SHIFT)
E 5
I 5
#define		CR_TXLOWAT_4	(0U << CR_TXLOWAT_SHIFT)
#define		CR_TXLOWAT_8	(1U << CR_TXLOWAT_SHIFT)
#define		CR_TXLOWAT_16	(2U << CR_TXLOWAT_SHIFT)
#define		CR_TXLOWAT_24	(3U << CR_TXLOWAT_SHIFT)
E 5

D 5
#define	CR_SRST		0x00008000	/* software reset */
D 2
#define	CR_TM1EN	0x00004000	/* enable timer1 (periodic) */
#define	CR_TM0EN	0x00002000	/* enable timer1 (one shot) */
E 2
I 2
#define	CR_TMR1EN	0x00004000	/* enable timer1 (periodic) */
#define	CR_TMR0EN	0x00002000	/* enable timer0 (one shot) */
E 2
#define	CR_DPOLL	0x00000800	/* disable TD/RD auto polling */
#define	CR_DISAU	0x00000100	/* disable unicast reception */
E 5
I 5
#define	CR_SRST		0x00008000U	/* software reset */
#define	CR_TMR1EN	0x00004000U	/* enable timer1 (periodic) */
#define	CR_TMR0EN	0x00002000U	/* enable timer0 (one shot) */
#define	CR_DPOLL	0x00000800U	/* disable TD/RD auto polling */
#define	CR_DISAU	0x00000100U	/* disable unicast reception */
E 5

D 5
#define	CR_TXON		0x00000008	/* turn on transmit DMA state */
#define	CR_RXON		0x00000004	/* turn on receive DMA state */
#define	CR_STOP		0x00000002	/* stop NIC */
#define	CR_STRT		0x00000001	/* start NIC */
E 5
I 5
#define	CR_TXON		0x00000008U	/* turn on transmit DMA state */
#define	CR_RXON		0x00000004U	/* turn on receive DMA state */
#define	CR_STOP		0x00000002U	/* stop NIC */
#define	CR_STRT		0x00000001U	/* start NIC */
E 5

/* TXESR (offset 0x22) */
D 5
#define	TXESR_TFDBS	0x08
#define	TXESR_TDWBS	0x04
#define	TXESR_TDRBS	0x02
#define	TXESR_TDSTR	0x01
E 5
I 5
#define	TXESR_TFDBS	0x08U
#define	TXESR_TDWBS	0x04U
#define	TXESR_TDRBS	0x02U
#define	TXESR_TDSTR	0x01U
E 5

/* RXESR (offset 0x23) */
D 5
#define	RXESR_RFDBS	0x08
#define	RXESR_RDWBS	0x04
#define	RXESR_RDRBS	0x02
#define	RXESR_RDSTR	0x01
E 5
I 5
#define	RXESR_RFDBS	0x08U
#define	RXESR_RDWBS	0x04U
#define	RXESR_RDRBS	0x02U
#define	RXESR_RDSTR	0x01U
E 5

/* ISR (offset 0x24) */
D 5
#define	ISR_ISR3	0x80000000
#define	ISR_ISR2	0x40000000
#define	ISR_ISR1	0x20000000
#define	ISR_ISR0	0x10000000
#define	ISR_TXSTL	0x02000000	/* tx dma stall */
#define	ISR_RXSTL	0x01000000	/* rx dma stall */
#define	ISR_HFLD	0x00800000
#define	ISR_UDP		0x00400000	/* software int */
#define	ISR_MIBF	0x00200000	/* mib counter overflow */
#define	ISR_SHDN	0x00100000	/* software shutdown completed */
#define	ISR_PHY		0x00080000	/* phy status changed */
#define	ISR_PWE		0x00040000	/* wake up power event */
#define	ISR_TMR1	0x00020000	/* timer1 (periodic) expired */
#define	ISR_TMR0	0x00010000	/* timer0 (one shot) expired */
#define	ISR_SRC		0x00008000	/* link status changed */
#define	ISR_LSTPE	0x00004000	/* running out of rx descs */
#define	ISR_LSTE	0x00002000	/* no rx descs */
#define	ISR_OVF		0x00001000	/* rx fifo overflow */
#define	ISR_FLON	0x00000800	/* pause frame received */
#define	ISR_RACE	0x00000400
#define	ISR_TXWB1	0x00000200
#define	ISR_TXWB0	0x00000100
#define	ISR_PTX3	0x00000080	/* tx done on tx queue3 */
#define	ISR_PTX2	0x00000040	/* tx done on tx queue2 */
#define	ISR_PTX1	0x00000020	/* tx done on tx queue1 */
#define	ISR_PTX0	0x00000010	/* tx done on tx queue0 */
#define	ISR_PTX		0x00000008	/* tx done */
#define	ISR_PRX		0x00000004	/* rx done */
#define	ISR_PPTX	0x00000002	/* priority tx done */
#define	ISR_PPRX	0x00000001	/* priority rx done */
E 5
I 5
#define	ISR_ISR3	0x80000000U
#define	ISR_ISR2	0x40000000U
#define	ISR_ISR1	0x20000000U
#define	ISR_ISR0	0x10000000U
#define	ISR_TXSTL	0x02000000U	/* tx dma stall */
#define	ISR_RXSTL	0x01000000U	/* rx dma stall */
#define	ISR_HFLD	0x00800000U
#define	ISR_UDP		0x00400000U	/* software int */
#define	ISR_MIBF	0x00200000U	/* mib counter overflow */
#define	ISR_SHDN	0x00100000U	/* software shutdown completed */
#define	ISR_PHY		0x00080000U	/* phy status changed */
#define	ISR_PWE		0x00040000U	/* wake up power event */
#define	ISR_TMR1	0x00020000U	/* timer1 (periodic) expired */
#define	ISR_TMR0	0x00010000U	/* timer0 (one shot) expired */
#define	ISR_SRC		0x00008000U	/* link status changed */
#define	ISR_LSTPE	0x00004000U	/* running out of rx descs */
#define	ISR_LSTE	0x00002000U	/* no rx descs */
#define	ISR_OVF		0x00001000U	/* rx fifo overflow */
#define	ISR_FLON	0x00000800U	/* pause frame received */
#define	ISR_RACE	0x00000400U
#define	ISR_TXWB1	0x00000200U
#define	ISR_TXWB0	0x00000100U
#define	ISR_PTX3	0x00000080U	/* tx done on tx queue3 */
#define	ISR_PTX2	0x00000040U	/* tx done on tx queue2 */
#define	ISR_PTX1	0x00000020U	/* tx done on tx queue1 */
#define	ISR_PTX0	0x00000010U	/* tx done on tx queue0 */
#define	ISR_PTX		0x00000008U	/* tx done */
#define	ISR_PRX		0x00000004U	/* rx done */
#define	ISR_PPTX	0x00000002U	/* priority tx done */
#define	ISR_PPRX	0x00000001U	/* priority rx done */
E 5

#define	ISR_BITS	\
	"\020"	\
	"\040ISR3"	\
	"\037ISR2"	\
	"\036ISR1"	\
	"\035ISR0"	\
	"\032TXSTL"	\
	"\031RXSTL"	\
	"\030HFLD"	\
	"\027UDP"	\
	"\026MIBF"	\
	"\025SHDN"	\
	"\024PHY"	\
	"\023PWE"	\
	"\022TMR1"	\
	"\021TMR0"	\
	"\020SRC"	\
	"\017LSTPE"	\
	"\016LSTE"	\
	"\015OVF"	\
	"\014FLON"	\
	"\013RACE"	\
	"\012TXWB1"	\
	"\011TXWB0"	\
	"\010PTX3"	\
	"\007PTX2"	\
	"\006PTX1"	\
	"\005PTX0"	\
	"\004PTX"	\
	"\003PRX"	\
	"\002PPTX"	\
	"\001PPRX"

/* IMR (offset 0x0e-0x0f) Interrupt mask register */
/* same as above */

/* MAR (offset 0x10-0x17) Multicast mask register */

/* RDCSR */
D 5
#define RDCSR_DEAD	0x8
#define RDCSR_WAK	0x4
#define RDCSR_ACT	0x2
#define RDCSR_RUN	0x1
E 5
I 5
#define	RDCSR_DEAD	0x8U
#define	RDCSR_WAK	0x4U
#define	RDCSR_ACT	0x2U
#define	RDCSR_RUN	0x1U
E 5

/* TDCSR */
#define	TDCSR_BIT_WIDTH	4
D 5
#define TDCSR_DEAD(x)	(0x8 << ((x) * TDCSR_BIT_WIDTH))
#define TDCSR_WAK(x)	(0x4 << ((x) * TDCSR_BIT_WIDTH))
#define TDCSR_ACT(x)	(0x2 << ((x) * TDCSR_BIT_WIDTH))
#define TDCSR_RUN(x)	(0x1 << ((x) * TDCSR_BIT_WIDTH))
E 5
I 5
#define	TDCSR_DEAD(x)	(0x8U << ((x) * TDCSR_BIT_WIDTH))
#define	TDCSR_WAK(x)	(0x4U << ((x) * TDCSR_BIT_WIDTH))
#define	TDCSR_ACT(x)	(0x2U << ((x) * TDCSR_BIT_WIDTH))
#define	TDCSR_RUN(x)	(0x1U << ((x) * TDCSR_BIT_WIDTH))
E 5

/* CAMADDR (offset 0x68) */
D 5
#define	CAMADDR_EN	0x80	/* enable cam address register */
#define	CAMADDR_VCAMSL	0x40	/* base address for vlan */
#define	CAMADDR_INDEX	0x3f	/* cam index */
E 5
I 5
#define	CAMADDR_EN	0x80U	/* enable cam address register */
#define	CAMADDR_VCAMSL	0x40U	/* base address for vlan */
#define	CAMADDR_INDEX	0x3fU	/* cam index */
E 5

/* CAMCR (offset 0x69)  */
D 5
#define	CAMCR_SEL	0xc0	/* contents selector */
E 5
I 5
#define	CAMCR_SEL	0xc0U	/* contents selector */
E 5
#define		CAMCR_SEL_SHIFT	6
D 5
#define		CAMCR_SEL_MAR	(0 << CAMCR_SEL_SHIFT)
#define		CAMCR_SEL_MASK	(1 << CAMCR_SEL_SHIFT)
#define		CAMCR_SEL_DATA	(2 << CAMCR_SEL_SHIFT)
#define	CAMCR_AITRPKT	0x20	/* */
#define	CAMCR_AITR16	0x10	/* */
#define	CAMCR_RD	0x08	/* cam read command */
#define	CAMCR_WR	0x04	/* cam write command */
E 5
I 5
#define		CAMCR_SEL_MAR	(0U << CAMCR_SEL_SHIFT)
#define		CAMCR_SEL_MASK	(1U << CAMCR_SEL_SHIFT)
#define		CAMCR_SEL_DATA	(2U << CAMCR_SEL_SHIFT)
#define	CAMCR_AITRPKT	0x20U	/* */
#define	CAMCR_AITR16	0x10U	/* */
#define	CAMCR_RD	0x08U	/* cam read command */
#define	CAMCR_WR	0x04U	/* cam write command */
E 5

/* MIICFG (offset 0x6c) MII configration register */
D 5
#define	MIICFG_MPO	0xc0		/* MII polling timer interval (def 0)*/
#define		MIICFG_MPO_MASK		0x3
E 5
I 5
#define	MIICFG_MPO	0xc0U		/* MII polling timer interval (def 0) */
#define		MIICFG_MPO_MASK		0x3U
E 5
#define		MIICFG_MPO_SHIFT	6
D 5
#define		MIICFG_MPO_1024	(0 << MIICFG_MPO_SHIFT)
#define		MIICFG_MPO_512	(1 << MIICFG_MPO_SHIFT)
#define		MIICFG_MPO_128	(2 << MIICFG_MPO_SHIFT)
#define		MIICFG_MPO_64	(3 << MIICFG_MPO_SHIFT)
#define	MIICFG_MFDC	0x20		/* Accelerate MDC sleep 4times */
E 5
I 5
#define		MIICFG_MPO_1024	(0U << MIICFG_MPO_SHIFT)
#define		MIICFG_MPO_512	(1U << MIICFG_MPO_SHIFT)
#define		MIICFG_MPO_128	(2U << MIICFG_MPO_SHIFT)
#define		MIICFG_MPO_64	(3U << MIICFG_MPO_SHIFT)
#define	MIICFG_MFDC	0x20U		/* Accelerate MDC sleep 4times */
E 5

/* MIISR (offset 0x6d) MII status register */
D 5
#define	MIISR_MIDLE	0x80	/* MII polling is idle */
E 5
I 5
#define	MIISR_MIDLE	0x80U	/* MII polling is idle */
E 5

/* PHYSR0 (offset 0x6e) */
D 5
#define	PHYSR_PHYRST	0x80	/* Phy reset, by software driven */
#define	PHYSR_LINKGD	0x40	/* */
#define	PHYSR_FDPX	0x10	/* full duplex */
#define	PHYSR_SPDG	0x08	/* */
#define	PHYSR_SPD10	0x04	/* Phy Speed 1:100M, 0:10M */
#define	PHYSR_RXFLC	0x02	/* Rx flow control */
#define	PHYSR_TXFLC	0x01	/* Tx flow control */
E 5
I 5
#define	PHYSR_PHYRST	0x80U	/* Phy reset, by software driven */
#define	PHYSR_LINKGD	0x40U	/* */
#define	PHYSR_FDPX	0x10U	/* full duplex */
#define	PHYSR_SPDG	0x08U	/* */
#define	PHYSR_SPD10	0x04U	/* Phy Speed 1:100M, 0:10M */
#define	PHYSR_RXFLC	0x02U	/* Rx flow control */
#define	PHYSR_TXFLC	0x01U	/* Tx flow control */
E 5

/* PHYSR1 (offset 0x6f) */
D 5
#define	PHYSR_PHYTBI	0x01	/* TBI PHY */
E 5
I 5
#define	PHYSR_PHYTBI	0x01U	/* TBI PHY */
E 5

/* MIICR (0x70) MII interface control registger */
D 5
#define	MIICR_MAUTO	0x80	/* MII management auto port polling disable */
#define	MIICR_RCMD	0x40	/* Read enable, reset when read complete */
#define	MIICR_WCMD	0x20	/* Write enable, reset when write complete */
#define	MIICR_MDPM	0x10	/* Direct PHY programming mode enable */
#define	MIICR_MDOUT	0x08	/* Direct programming out put enable indicator*/
#define	MIICR_MDO	0x04	/* Direct programming status as management port data out */
#define	MIICR_MDI	0x02	/* Direct programming input while PHY status */
#define	MIICR_MDC	0x01	/* Direct programming status as management port clock */
E 5
I 5
#define	MIICR_MAUTO	0x80U	/* MII management auto port polling disable */
#define	MIICR_RCMD	0x40U	/* Read enable, reset when read complete */
#define	MIICR_WCMD	0x20U	/* Write enable, reset when write complete */
#define	MIICR_MDPM	0x10U	/* DP mode enable */
#define	MIICR_MDOUT	0x08U	/* DP out put enable indicator */
#define	MIICR_MDO	0x04U	/* DP status as management port data out */
#define	MIICR_MDI	0x02U	/* DP input while PHY status */
#define	MIICR_MDC	0x01U	/* DP status as management port clock */
E 5

/* MIIADR (0x71) MII address registger */
D 5
#define	MIIADR_SWMPL	0x80	/* */
#define	MIIADR_PHYAD	0x1f	/* phy addrss mask */
E 5
I 5
#define	MIIADR_SWMPL	0x80U	/* */
#define	MIIADR_PHYAD	0x1fU	/* phy addrss mask */
E 5

/* MIIDATA(0x72-73) MII data register  */

D 2
/* SOFT TIMER0 (offset 0x74) software timer register */
/* SOFT TIMER1 (offset 0x76) software timer register */
E 2
I 2
/* SOFT TMR0 (offset 0x74) software timer register */
/* SOFT TMR1 (offset 0x76) software timer register */
E 2

/* CFGA (offset 0x78 ) configration A register */
D 5
#define	CFGA_PMHCTG	0x08
#define	CFGA_GPIO1PD	0x04	/* GPIO pin enable */
#define	CFGA_ABSHDN	0x02	/* abnormal shutdown */
#define	CFGA_PACPI	0x01	/* preACPI wakeup */
E 5
I 5
#define	CFGA_PMHCTG	0x08U
#define	CFGA_GPIO1PD	0x04U	/* GPIO pin enable */
#define	CFGA_ABSHDN	0x02U	/* abnormal shutdown */
#define	CFGA_PACPI	0x01U	/* preACPI wakeup */
E 5

/* CFGB (offset 0x79 ) configration B register */
D 5
#define	CFGB_GTCPOPT	0x80	/* ? */
#define	CFGB_MIIOPT	0x40	/* 0: w/o extension clk, 1: w/ extension clk */
#define	CFGB_CRSEOPT	0x20	/* ? */
#define	CFGB_OFSET	0x10	/* ? */
#define	CFGB_CRANDOM	0x08	/* Backoff algorithm random */
#define	CFGB_CAP	0x04	/* Capture effect solusion : DEC solusion */
#define	CFGB_MBA	0x02	/* Capture effect solusion : AMD solusion */
D 2
#define	CFGB_BAKOPT	0x01	/* Backoff algorithm 0: disable, 1: enable */
E 2
I 2
#define	CFGB_BAKOPT	0x01	/* Backoff algorithm (0: disable, 1: enable) */
E 5
I 5
#define	CFGB_GTCPOPT	0x80U	/* ? */
#define	CFGB_MIIOPT	0x40U	/* 0: w/o extension clk, 1: w/ extension clk */
#define	CFGB_CRSEOPT	0x20U	/* ? */
#define	CFGB_OFSET	0x10U	/* ? */
#define	CFGB_CRANDOM	0x08U	/* Backoff algorithm random */
#define	CFGB_CAP	0x04U	/* Capture effect solusion : DEC solusion */
#define	CFGB_MBA	0x02U	/* Capture effect solusion : AMD solusion */
#define	CFGB_BAKOPT	0x01U	/* Backoff algorithm (0: disable, 1: enable) */
E 5
E 2

/* CFGC (offset 0x7a) */
D 5
#define	CFGC_EELOAD	0x80	/* Enable EEPROM embedded and direct programming */
#define	CFGC_BROPT	0x40	/* Tie the unused bootrom address MA to high */
#define	CFGC_DLYEN	0x20	/* turn on delay transaction while memory read bootrprom */
#define	CFGC_BTSEL	0x08	/* BOOTPROM timing select */
#define	CFGC_BPS	0x07	/* BOOTPROM size select */
#define		CFGC_BPS_NONE	0x00	/*    NO BOOTPROM */
#define		CFGC_BPS_8K	0x01	/*    8K size */
#define		CFGC_BPS_16K	0x02	/*    16K size */
#define		CFGC_BPS_32K	0x03	/*    32K size */
#define		CFGC_BPS_64K	0x04	/*    64K size */
E 5
I 5
#define	CFGC_EELOAD	0x80U	/* Enable EEPROM embedded and DP */
#define	CFGC_BROPT	0x40U	/* Tie the unused bootrom address MA to high */
#define	CFGC_DLYEN	0x20U	/* delay transaction for MEMRD bootrprom */
#define	CFGC_BTSEL	0x08U	/* BOOTPROM timing select */
#define	CFGC_BPS	0x07U	/* BOOTPROM size select */
#define		CFGC_BPS_NONE	0x00U	/*    NO BOOTPROM */
#define		CFGC_BPS_8K	0x01U	/*    8K size */
#define		CFGC_BPS_16K	0x02U	/*    16K size */
#define		CFGC_BPS_32K	0x03U	/*    32K size */
#define		CFGC_BPS_64K	0x04U	/*    64K size */
E 5

/* CFGD (offset 0x7b) */
D 5
#define	CFGD_IODIS	0x80	/* disable IO access */
#define	CFGD_MSLVDACEN	0x40	/* */
#define	CFGD_CFGDACEN	0x20	/* enable dual access cycle (DAC) */
#define	CFGD_PCI64EN	0x10	/* */
#define	CFGD_HTMRL4	0x08	/* */
E 5
I 5
#define	CFGD_IODIS	0x80U	/* disable IO access */
#define	CFGD_MSLVDACEN	0x40U	/* */
#define	CFGD_CFGDACEN	0x20U	/* enable dual access cycle (DAC) */
#define	CFGD_PCI64EN	0x10U	/* */
#define	CFGD_HTMRL4	0x08U	/* */
E 5

/* DCFG (offset 0x7c) DMA configuration register */
D 5
#define DCFG_XMWI	0x8000
#define DCFG_XMRM	0x4000
#define DCFG_XMRL	0x2000
#define DCFG_PERDIS	0x1000	/* disable parity error detection */
I 2
#define DCFG_MRM	0x0800	/* use memory read multiple */
E 2
#define DCFG_MRWAIT	0x0400
#define DCFG_MWWAIT	0x0200
#define DCFG_LATMEN	0x0100	/* enable latency timer */
#define	DCFG_DMA	0x0007	/* DMA length */
E 5
I 5
#define	DCFG_XMWI	0x8000U
#define	DCFG_XMRM	0x4000U
#define	DCFG_XMRL	0x2000U
#define	DCFG_PERDIS	0x1000U	/* disable parity error detection */
#define	DCFG_MRM	0x0800U	/* use memory read multiple */
#define	DCFG_MRWAIT	0x0400U
#define	DCFG_MWWAIT	0x0200U
#define	DCFG_LATMEN	0x0100U	/* enable latency timer */
#define	DCFG_DMA	0x0007U	/* DMA length */
E 5
#define		DCFG_DMA_SHIFT	0
D 5
#define		DMA_32		0
#define		DMA_64		1
#define		DMA_128		2
#define		DMA_256		3
#define		DMA_512		4
#define		DMA_1024	5
#define		DMA_NOLIMIT	6
E 5
I 5
#define		DMA_32		0U
#define		DMA_64		1U
#define		DMA_128		2U
#define		DMA_256		3U
#define		DMA_512		4U
#define		DMA_1024	5U
#define		DMA_NOLIMIT	6U
E 5

#define	DCFG_BITS	\
	"\020"		\
	"\020XMWI"	\
	"\017XMRM"	\
	"\016XMRL"	\
	"\015PERDIS"	\
	"\013MRWAIT"	\
	"\012MWWAIT"	\
	"\011LATMEN"

/* MCFG (offset 0x7e) Misc configuration register  */
D 5
#define	MCFG_TXARB	0x8000
#define	MCFG_TXQBK1	0x0800
#define	MCFG_TXQBK0	0x0400
#define	MCFG_TXQNOBK	0x0200
#define	MCFG_SNAPOPT	0x0100
#define	MCFG_RXARB	0x0080
#define	MCFG_RFT	0x0030	/* Rx fifo threashold */
E 5
I 5
#define	MCFG_TXARB	0x8000U
#define	MCFG_TXQBK	0x0c00U
#define		MCFG_TXQBK_SHIFT	8
#define		MCFG_TXQBK_64	(0U << MCFG_TXQBK_SHIFT)
#define		MCFG_TXQBK_32	(1U << MCFG_TXQBK_SHIFT)
#define		MCFG_TXQBK_128	(2U << MCFG_TXQBK_SHIFT)
#define		MCFG_TXQBK_8	(3U << MCFG_TXQBK_SHIFT)
#define	MCFG_TXQNOBK	0x0200U
#define	MCFG_SNAPOPT	0x0100U	/* tag offset: 1:13th 0:21st */
#define	MCFG_RXARB	0x0080U
#define	MCFG_RFT	0x0030U	/* Rx fifo threashold */
E 5
#define		MCFG_RFT_SHIFT	4
D 5
#define		RFT_128		0
#define		RFT_512		1
#define		RFT_1024	2
#define		RFT_SF		3
#define	MCFG_LOWTHOPT	0x0008
#define	MCFG_PQEN	0x0004
#define	MCFG_RTGOPT	0x0002
#define	MCFG_VIDFR	0x0001
E 5
I 5
#define		RFT_128		0U
#define		RFT_512		1U
#define		RFT_1024	2U
#define		RFT_SF		3U
#define	MCFG_LOWTHOPT	0x0008U
#define	MCFG_VTAG	0x0006U
#define		MCFG_VTAG_SHIFT	1
#define		VTAG_OPT0	0U	/* tx no tag, rx all w/o ext */
#define		VTAG_OPT1	1U	/* tx no tag, rx only tagged, no-ex */
#define		VTAG_OPT2	2U	/* tx tag enable, rx all w/ extract */
#define		VTAG_OPT3	3U	/* tx tag enable, rx only tagged */
#define		MCFG_PQEN	0x0004U
#define		MCFG_RTGOPT	0x0002U
#define	MCFG_VIDFR	0x0001U
E 5

I 5
#define	MCFG_BITS	"\020"	\
	"\020TXARB"	\
	"\012TXQNOBK"	\
	"\011SNAPOPT"	\
	"\010RXARB"	\
	"\004LOWTHOPT"	\
	"\001VIDFR"

E 5
/* STICKHW (offset 0x83) */
D 5
#define	STICKHW_SWPTAG	0x10	/* */
#define	STICKHW_WOLSR	0x08	/* Legacy WOL status */
#define	STICKHW_WOLEN	0x04	/* Legacy WOL enable */
#define	STICKHW_DS1	0x02	/* Sticky DS0_shadow, R/W by software */
#define	STICKHW_DS0	0x01	/* Sticky DS0_shadow, suspend well DS write port */
E 5
I 5
#define	STICKHW_SWPTAG	0x10U	/* */
#define	STICKHW_WOLSR	0x08U	/* Legacy WOL status */
#define	STICKHW_WOLEN	0x04U	/* Legacy WOL enable */
#define	STICKHW_DS1	0x02U	/* Sticky DS0_shadow, R/W by software */
#define	STICKHW_DS0	0x01U	/* Sticky DS0_shadow, suspend well DS write */
E 5

/* MIBCR (offset 0x84) */
/* EERSV (offset 0x85) */

/* REVID (offset 0x86) */
D 5
#define	REVID_VT3119_A0	0x00
#define	REVID_VT3119_A1	0x01
#define	REVID_VT3216_A0	0x10
E 5
I 5
#define	REVID_VT3119_A0	0x00U
#define	REVID_VT3119_A1	0x01U
#define	REVID_VT3216_A0	0x10U
E 5

/* MIBREAD (offset 0x88) */
/* BPMA (offset 0x8c-08d) */
/* BPMD (offset 0x8f) */
/* BPCMD (offset 0x90) */
D 5
#define BPCMD_EBPWR	0x02	/* BOOTROM embedded write command */
#define BPCMD_EBPRD	0x01	/* BOOTROM embedded read command */
E 5
I 5
#define	BPCMD_EBPWR	0x02U	/* BOOTROM embedded write command */
#define	BPCMD_EBPRD	0x01U	/* BOOTROM embedded read command */
E 5

/* EE_CHKSUM (offset 0x92) */

/* EECSR (offset 0x93) Direct program EEPROM interface */
D 5
#define	EECSR_EMBP	0x40	/* EEPROM embedded programming enable */
#define	EECSR_AUTOLD	0x20	/* Dynamic reload EEPROM content */
#define	EECSR_DPM	0x10	/* EEPROM mode */
#define	EECSR_ECS	0x08	/* chip select status */
#define	EECSR_ECK	0x04	/* clock status */
#define	EECSR_EDI	0x02	/* data in status */
E 5
I 5
#define	EECSR_EMBP	0x40U	/* EEPROM embedded programming enable */
#define	EECSR_AUTOLD	0x20U	/* Dynamic reload EEPROM content */
#define	EECSR_DPM	0x10U	/* EEPROM mode */
#define	EECSR_ECS	0x08U	/* chip select status */
#define	EECSR_ECK	0x04U	/* clock status */
#define	EECSR_EDI	0x02U	/* data in status */
E 5
#define		EECSR_EDI_SHIFT	1
D 5
#define	EECSR_EDO	0x01	/* data out status */
E 5
I 5
#define	EECSR_EDO	0x01U	/* data out status */
E 5
#define		EECSR_EDO_SHIFT	0

/* TESTCFG (offset 0x9d) */
D 5
#define	TESTCFG_HBDIS	0x80	/* disable heatbeat */
E 5
I 5
#define	TESTCFG_HBDIS	0x80U	/* disable heatbeat */
E 5

/* GMCR (offset 0x9f) */
D 5
#define	GMCR_FCGMII	0x80	/* select phy  (0: 10/100M PHY, 1:1G PHY) */
#define	GMCR_FCFDX	0x40	/* select duplex (0: half, 1:full) */
#define	GMCR_FCRESV	0x20
#define	GMCR_FCMODE	0x10	/* media detection (0:auto, 1:forced) */
#define	GMCR_LPSOPT	0x08
D 2
#define	GMCR_TM1US	0x04
#define	GMCR_TM0US	0x02
E 2
I 2
#define	GMCR_TMR1US	0x04	/* timer1 resolution (0:1mS, 1:1uS) */
#define	GMCR_TMR0US	0x02	/* timer0 resolution (0:1mS, 1:1uS) */
E 2
#define	GMCR_PHYINTEN	0x01
E 5
I 5
#define	GMCR_FCGMII	0x80U	/* select phy  (0: 10/100M PHY, 1:1G PHY) */
#define	GMCR_FCFDX	0x40U	/* select duplex (0: half, 1:full) */
#define	GMCR_FCRESV	0x20U
#define	GMCR_FCMODE	0x10U	/* media detection (0:auto, 1:forced) */
#define	GMCR_LPSOPT	0x08U
#define	GMCR_TMR1US	0x04U	/* timer1 resolution (0:1mS, 1:1uS) */
#define	GMCR_TMR0US	0x02U	/* timer0 resolution (0:1mS, 1:1uS) */
#define	GMCR_PHYINTEN	0x01U
E 5

#define	GMCR_BITS	\
	"\020"	\
	"\010FCGMII"	\
	"\007FCFDX"	\
	"\006FCRESV"	\
	"\005FCMODE"	\
	"\004LPSOPT"	\
D 2
	"\003TM1US"	\
	"\002TM0US"	\
E 2
I 2
	"\003TMR1US"	\
	"\002TMR0US"	\
E 2
	"\001PHYINTEN"

/* WOLCR.SET WOLCR.CLR (offset 0xa0, 0xa4 RWC) Wake On Lan command register */
D 5
#define	WOLCR_LinkOFF	0x0800	/* enable link of detected */
#define	WOLCR_LinkON	0x0400	/* enable link on detected */
#define	WOLCR_MAGICEN	0x0200	/* enable Magic packet filter */
#define	WOLCR_UNICAST	0x0100	/* enable UNICAST filter */
#define	WOLCR_MSWOLEN7	0x0080
#define	WOLCR_MSWOLEN6	0x0040
#define	WOLCR_MSWOLEN5	0x0020
#define	WOLCR_MSWOLEN4	0x0010
#define	WOLCR_MSWOLEN3	0x0008
#define	WOLCR_MSWOLEN2	0x0004
#define	WOLCR_MSWOLEN1	0x0002
#define	WOLCR_MSWOLEN0	0x0001
#define	WOLCR_ARP_EN	0x0001
E 5
I 5
#define	WOLCR_LinkOFF	0x0800U	/* enable link of detected */
#define	WOLCR_LinkON	0x0400U	/* enable link on detected */
#define	WOLCR_MAGICEN	0x0200U	/* enable Magic packet filter */
#define	WOLCR_UNICAST	0x0100U	/* enable UNICAST filter */
#define	WOLCR_MSWOLEN7	0x0080U
#define	WOLCR_MSWOLEN6	0x0040U
#define	WOLCR_MSWOLEN5	0x0020U
#define	WOLCR_MSWOLEN4	0x0010U
#define	WOLCR_MSWOLEN3	0x0008U
#define	WOLCR_MSWOLEN2	0x0004U
#define	WOLCR_MSWOLEN1	0x0002U
#define	WOLCR_MSWOLEN0	0x0001U
#define	WOLCR_ARP_EN	0x0001U
E 5

/* PWCFG.SET PWCFG.CLR (offset 0xa2, 0xa6 RWC) */
D 5
#define	PWCFG_SMIITIME	0x80	/* Internal MII interface timing */
#define	PWCFG_PCISTICK	0x40	/* PCI stick enable */
#define	PWCFG_WOLTYPE	0x20	/* Drive WOL output by 1:pulse or 0:button */
#define	PWCFG_LEGCYWOL	0x10	/* Enale legacy wake on lan */
#define	PWCFG_PMCSR_PME_SR 0x08	/* */
#define	PWCFG_PMCSR_PME_EN 0x04	/* */
#define	PWCFG_WOLSR	0x02	/* Legacy WOL_SR shadow */
#define	PWCFG_WOLEN	0x01	/* Legacy WOL_EN shadow */
E 5
I 5
#define	PWCFG_SMIITIME	0x80U	/* Internal MII interface timing */
#define	PWCFG_PCISTICK	0x40U	/* PCI stick enable */
#define	PWCFG_WOLTYPE	0x20U	/* Drive WOL output by 1:pulse or 0:button */
#define	PWCFG_LEGCYWOL	0x10U	/* Enale legacy wake on lan */
#define	PWCFG_PMCSR_PME_SR 0x08U	/* */
#define	PWCFG_PMCSR_PME_EN 0x04U	/* */
#define	PWCFG_WOLSR	0x02U	/* Legacy WOL_SR shadow */
#define	PWCFG_WOLEN	0x01U	/* Legacy WOL_EN shadow */
E 5

/* TESTREG.SET TESTREG.CLR (offset 0xa2, 0xa6 RWC) */
D 5
#define	TESTREG_SNORM	0x01	/* All power state capable while PHYTEST=0 */
E 5
I 5
#define	TESTREG_SNORM	0x01U	/* All power state capable while PHYTEST=0 */
E 5

/* WOLCFG.SET WOLCFG.CLR (offset 0xa3, 0xa7 RWC) */
D 5
#define	WOLCFG_PMEOVR	0x80	/* Force PMEEN always over PME_EN (legacy) */
#define	WOLCFG_SAM	0x20	/* Accept multicast in suspend well */
#define	WOLCFG_SAB	0x10	/* Accept broadcast in suspend well */
#define	WOLCFG_SMIIACC	0x08	/* MDC acceleration */
#define	WOLCFG_SMIIOPT	0x04	/* MIIOPT to extend clock in suspend well */
#define	WOLCFG_PHYINTEN	0x01	/* Internal PHY enable */
E 5
I 5
#define	WOLCFG_PMEOVR	0x80U	/* Force PMEEN always over PME_EN (legacy) */
#define	WOLCFG_SAM	0x20U	/* Accept multicast in suspend well */
#define	WOLCFG_SAB	0x10U	/* Accept broadcast in suspend well */
#define	WOLCFG_SMIIACC	0x08U	/* MDC acceleration */
#define	WOLCFG_SMIIOPT	0x04U	/* MIIOPT to extend clock in suspend well */
#define	WOLCFG_PHYINTEN	0x01U	/* Internal PHY enable */
E 5

/* PWRCSR.SET PSWCSR.CLR (offset 0xa8, 0xac RWC) undocumented */

/* PATTERN CRC0-3 (offset 0xb0-0xbf, RW) */
/* BYTEMASK0-3 CRC0-3 (offset 0xc0-0xff, RW) */
/* RDESC0-3 (offset 0x20-0x2f) Rx Descriptor */

/* The Rx buffer descriptor. */
struct rx_desc {
D 2
	volatile uint32_t	rdes0;
	volatile uint32_t	rdes1;
	volatile uint32_t	rdes2;
	volatile uint32_t	rdes3;
E 2
I 2
D 3
	uint32_t	rdes0;
	uint32_t	rdes1;
	uint32_t	rdes2;
	uint32_t	rdes3;
E 3
I 3
	volatile uint32_t	rdes0;
	volatile uint32_t	rdes1;
	volatile uint32_t	rdes2;
	volatile uint32_t	rdes3;
E 3
E 2
};

/* Receive status field in RDES0 */
D 5
#define	RSR_RXOK	0x8000	/* Received a good packet */
#define	RSR_PFT		0x4000	/* Perfect filtering match */
#define	RSR_MAR		0x2000	/* Multicast address received */
#define	RSR_BAR		0x1000	/* Broadcast address received */
#define	RSR_PHY		0x0800	/* Physical address received */
#define	RSR_VTAG	0x0400	/* VLAN tagged packet received */
#define	RSR_STP		0x0200	/* Start of packet */
#define	RSR_EDP		0x0100	/* End of packet */
E 5
I 5
#define	RSR_RXOK	0x8000U	/* Received a good packet */
#define	RSR_PFT		0x4000U	/* Perfect filtering match */
#define	RSR_MAR		0x2000U	/* Multicast address received */
#define	RSR_BAR		0x1000U	/* Broadcast address received */
#define	RSR_PHY		0x0800U	/* Physical address received */
#define	RSR_VTAG	0x0400U	/* VLAN tagged packet received */
#define	RSR_STP		0x0200U	/* Start of packet */
#define	RSR_EDP		0x0100U	/* End of packet */
E 5

D 5
#define	RSR_DETAG	0x0080	/* VLAN tag extracted */
#define	RSR_SNTAG	0x0040	/* tagged snap packet */
#define	RSR_RXER	0x0020	/* symbol error */
#define	RSR_LONG	0x0010	/* Long packet received */
#define	RSR_CE		0x0008	/* TCP/IP checksum error */
#define	RSR_FAE		0x0004	/* Frame Alignment error */
#define	RSR_CRC		0x0002	/* CRC Error error */
#define	RSR_VIDM	0x0001	/* VLAN tag filter miss */
E 5
I 5
#define	RSR_DETAG	0x0080U	/* VLAN tag extracted */
#define	RSR_SNTAG	0x0040U	/* tagged snap packet */
#define	RSR_RXER	0x0020U	/* symbol error */
#define	RSR_LONG	0x0010U	/* Long packet received */
#define	RSR_CE		0x0008U	/* TCP/IP checksum error */
#define	RSR_FAE		0x0004U	/* Frame Alignment error */
#define	RSR_CRC		0x0002U	/* CRC Error error */
#define	RSR_VIDM	0x0001U	/* VLAN tag filter miss */
E 5

D 3
#define	CSM_IPOK	0x40	/* IP Checkusm validatiaon ok */
#define	CSM_TUPOK	0x20	/* TCP/UDP Checkusm validatiaon ok */
#define	CSM_FRAG	0x10	/* Fragment IP datagram */
#define	CSM_IPKT	0x04	/* Received an IP packet */
#define	CSM_TCPKT	0x02	/* Received a TCP packet */
#define	CSM_UDPKT	0x01	/* Received a UDP packet */
E 3
I 3
D 5
#define	RDES1_IPOK	0x00400000	/* IP Checkusm validatiaon ok */
#define	RDES1_TUPOK	0x00200000	/* TCP/UDP Checkusm validatiaon ok */
#define	RDES1_FRAG	0x00100000	/* Fragment IP datagram */
#define	RDES1_IPKT	0x00040000	/* Received an IP packet */
#define	RDES1_TCPKT	0x00020000	/* Received a TCP packet */
#define	RDES1_UDPKT	0x00010000	/* Received a UDP packet */
E 5
I 5
#define	RDES1_IPOK	0x00400000U	/* IP Checkusm validatiaon ok */
#define	RDES1_TUPOK	0x00200000U	/* TCP/UDP Checkusm validatiaon ok */
#define	RDES1_FRAG	0x00100000U	/* Fragment IP datagram */
#define	RDES1_IPKT	0x00040000U	/* Received an IP packet */
#define	RDES1_TCPKT	0x00020000U	/* Received a TCP packet */
#define	RDES1_UDPKT	0x00010000U	/* Received a UDP packet */
#define	RDES1_VTAG	0x0000ffffU	/* extracted vtag */
E 5
E 3

/* useful macros for RSR bits */
#define	RSR_BITS	\
	"\020"	\
	"\020RXOK"	\
	"\017PFT"	\
	"\016MAR"	\
	"\015BAR"	\
	"\014PHY"	\
	"\013VTAG"	\
	"\012STP"	\
	"\011EDP"	\
	"\010DETAG"	\
	"\007SNTAG"	\
	"\006RXER"	\
	"\005LONG"	\
	"\004CE"	\
	"\003FAE"	\
	"\002CRC"	\
	"\001VIDM"

D 5
#define	RDES0_OWN	0x80000000
#define	RDES0_LEN	0x3fff0000
E 5
I 5
#define	RDES0_OWN	0x80000000U
#define	RDES0_LEN	0x3fff0000U
E 5
#define		RDES0_LEN_SHIFT	16
D 5
#define		RDES0_LEN_MASK	0x3fff
E 5
I 5
#define		RDES0_LEN_MASK	0x3fffU
E 5

D 5
#define	RDES3_INTR	0x80000000	/* Inter request */
#define	RDES3_RBS	0x3fff0000	/* Receive buffer size */
E 5
I 5
#define	RDES3_INTR	0x80000000U	/* Inter request */
#define	RDES3_RBS	0x3fff0000U	/* Receive buffer size */
E 5
#define		RDES3_RBS_SHIFT	16
D 5
#define	RDES3_ADDRHI	0x0000ffff	/* bit[47-16] of rx buffer address */
E 5
I 5
#define	RDES3_ADDRHI	0x0000ffffU	/* bit[47-16] of rx buffer address */
E 5

D 5
/* TDES0-1 Tx Descriptor */
struct td_buf {
D 2
	volatile uint32_t	tbdes0;	/* low address */
	volatile uint32_t	tbdes1;	/* high address, length and controles */
E 2
I 2
D 3
	uint32_t	tbdes0;	/* low address */
	uint32_t	tbdes1;	/* high address, length and controles */
E 3
I 3
	volatile uint32_t	tbdes0;	/* low address */
	volatile uint32_t	tbdes1;	/* high address, length and controles */
E 3
E 2
};
E 5
I 5
/* tx descriptor */
#define	TBDES_QUEUE	0x8000000000000000ULL	/* next descriptor is valid */
#define	TBDES_LEN	0x3fff000000000000ULL	/* fragment length */
#define		TBDES_LEN_SHIFT	48ull
#define	TBDES_ADDR	0x0000ffffffffffffULL	/* bit[47-0] of buf address */
E 5

D 5
#define	TBDES1_QUEUE		0x80000000	/* next descriptor is valid */
#define	TBDES1_LEN		0x3fff0000	/* fragment length */
#define		TBDES1_LEN_SHIFT	16
#define	TBDES1_ADDRHI		0x0000ffff	/* bit[47-16] of buf address */
E 5
I 5
#define	TBDES_BITS	"\020\100QUEUE"
E 5

D 5
#define	TBDES1_BITS	"\020\040QUEUE"

E 5
D 3
#define	NTDBUFS	7
E 3
I 3
#define	NTDBUFS	7				/* must be 7 */
E 3
struct tx_desc {
D 2
	volatile uint32_t	tdes0;
	volatile uint32_t	tdes1;
	struct td_buf		td_bufs[NTDBUFS];
E 2
I 2
D 3
	uint32_t	tdes0;
	uint32_t	tdes1;
E 3
I 3
	volatile uint32_t	tdes0;
	volatile uint32_t	tdes1;
E 3
D 5
	struct td_buf	td_bufs[NTDBUFS];
E 5
I 5
	volatile uint64_t	tbdes[NTDBUFS];
E 5
E 2
};

D 5
#define	TDES0_OWN	0x80000000	/* owned by nic */
#define	TDES0_LEN	0x3fff0000	/* total transmit length */
E 5
I 5
#define	TDES0_OWN	0x80000000U	/* owned by nic */
#define	TDES0_LEN	0x3fff0000U	/* total transmit length */
E 5
#define		TDES0_LEN_SHIFT	16
D 5
#define	TDES0_TSR	0x0000ffff	/* transmit status */
E 5
I 5
#define	TDES0_TSR	0x0000ffffU	/* transmit status */
E 5

D 5
#define	TSR_TXERR	0x8000		/* underflow/abort/late collision/CRS */
#define	TSR_FDX		0x4000		/* full duplex mode */
#define	TSR_GMII	0x2000		/* GMII mode */
#define	TSR_LNKFL	0x1000		/* packet serviced while link down */
#define	TSR_SHDN	0x0400		/* shutdown case */
#define	TSR_CRS		0x0200		/* carrier sense lost */
#define	TSR_CDH		0x0100		/* AQH test fail (CD heartbeat) */
#define	TSR_ABT		0x0080		/* TX abort */
#define	TSR_OWT		0x0040		/* Jumbo frame tx abort */
#define	TSR_OWC		0x0020		/* Out of window */
#define	TSR_COLS	0x0010		/* experience of collision */
#define	TSR_NCR		0x000f		/* Collision retry count */
E 5
I 5
#define	TSR_TXERR	0x8000U		/* underflow/abort/late collision/CRS */
#define	TSR_FDX		0x4000U		/* full duplex mode */
#define	TSR_GMII	0x2000U		/* GMII mode */
#define	TSR_LNKFL	0x1000U		/* packet serviced while link down */
#define	TSR_SHDN	0x0400U		/* shutdown case */
#define	TSR_CRS		0x0200U		/* carrier sense lost */
#define	TSR_CDH		0x0100U		/* AQH test fail (CD heartbeat) */
#define	TSR_ABT		0x0080U		/* TX abort */
#define	TSR_OWT		0x0040U		/* Jumbo frame tx abort */
#define	TSR_OWC		0x0020U		/* Out of window */
#define	TSR_COLS	0x0010U		/* experience of collision */
#define	TSR_NCR		0x000fU		/* Collision retry count */
E 5

#define	TDES0_BITS	\
	"\020"	\
	"\040OWN"	\
	"\020TXERR"	\
	"\017FDX"	\
	"\016GMII"	\
	"\015LNKFL"	\
	"\013SHDN"	\
	"\012CRS"	\
	"\011CDH"	\
	"\010ABT"	\
	"\007OWT"	\
	"\006OWC"	\
	"\005COLS"	\

D 5
#define	TDES1_CMDZ	0xf0000000	/* number of fragments + 1 */
E 5
I 5
#define	TDES1_CMDZ	0xf0000000U	/* number of fragments + 1 */
E 5
#define		TDES1_CMDZ_SHIFT	28
D 5
#define	TDES1_TCPLS	0x03000000
E 5
I 5
#define	TDES1_TCPLS	0x03000000U
E 5
#define		TDES1_TCPLS_SHIFT	24
D 5
#define		TDES1_TCPLS_NORMAL	(3 << TDES1_TCPLS_SHIFT)
#define		TDES1_TCPLS_START	(2 << TDES1_TCPLS_SHIFT)
#define		TDES1_TCPLS_END		(1 << TDES1_TCPLS_SHIFT)
#define		TDES1_TCPLS_MED		(0 << TDES1_TCPLS_SHIFT)
#define	TDES1_TCR	0x00ff0000
#define	TDES1_TCR_TIC	0x00800000	/* assert interrupt immediately */
#define	TDES1_TCR_PIC	0x00400000	/* priority interrupt request */
#define	TDES1_TCR_VETAG	0x00200000	/* enable VLAN tag */
#define	TDES1_TCR_IPCK	0x00100000	/* request IP  checksum calculation */
E 5
I 5
#define		TDES1_TCPLS_NORMAL	(3U << TDES1_TCPLS_SHIFT)
#define		TDES1_TCPLS_START	(2U << TDES1_TCPLS_SHIFT)
#define		TDES1_TCPLS_END		(1U << TDES1_TCPLS_SHIFT)
#define		TDES1_TCPLS_MED		(0U << TDES1_TCPLS_SHIFT)
#define	TDES1_TCR	0x00ff0000U
#define	TDES1_TCR_TIC	0x00800000U	/* assert interrupt immediately */
#define	TDES1_TCR_PIC	0x00400000U	/* priority interrupt request */
#define	TDES1_TCR_VETAG	0x00200000U	/* enable VLAN tag */
#define	TDES1_TCR_IPCK	0x00100000U	/* request IP  checksum calculation */
E 5
I 3
#define		TDES1_TCR_IPCK_SHIFT	20
E 3
D 5
#define	TDES1_TCR_UDPCK	0x00080000	/* request UDP checksum calculation */
E 5
I 5
#define	TDES1_TCR_UDPCK	0x00080000U	/* request UDP checksum calculation */
E 5
I 3
#define		TDES1_TCR_UDPCK_SHIFT	19
E 3
D 5
#define	TDES1_TCR_TCPCK	0x00040000	/* request TCP checksum calculation */
E 5
I 5
#define	TDES1_TCR_TCPCK	0x00040000U	/* request TCP checksum calculation */
E 5
I 3
#define		TDES1_TCR_TCPCK_SHIFT	18
E 3
D 5
#define	TDES1_TCR_JUMBO	0x00020000	/* indicate a big packet in GMAC side */
#define	TDES1_TCR_NOCRC	0x00010000	/* disable CRC generation */
#define	TDES1_PRI	0x0000e000	/* VLAN priority bits */
E 5
I 5
#define	TDES1_TCR_JUMBO	0x00020000U	/* indicate a big packet in GMAC side */
#define	TDES1_TCR_NOCRC	0x00010000U	/* disable CRC generation */
#define	TDES1_PRI	0x0000e000U	/* VLAN priority bits */
E 5
#define		TDES1_PRI_SHIFT	13
D 5
#define	TDES1_CFI	0x00001000	/* VLAN CFI bit */
#define	TDES1_VID	0x00000fff	/* VLAN ID */
E 5
I 5
#define	TDES1_CFI	0x00001000U	/* VLAN CFI bit */
#define	TDES1_VID	0x00000fffU	/* VLAN ID */
E 5

#define	TDES1_BITS	\
	"\020"		\
	"\030TIC"	\
	"\027PIC"	\
	"\026VETAG"	\
	"\025IPCK"	\
	"\024UDPCK"	\
	"\023TCPCK"	\
	"\022JMBO"	\
	"\021NOCRC"	\
	"\015CFI"
I 5


#endif	/* _VT612XREG_H_ */
E 5
E 1
