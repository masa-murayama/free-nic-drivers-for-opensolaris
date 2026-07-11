/*
 * Register definitins
 */
#define	B0_RAP		0x0000	/* B: register address port */
#define	CSR		0x0004	/* W: control/status register */
/* #define	B0_LED		0x0006	/* B: led control register */
#define	B0_ISR		0x0008	/* D: interrupt status */
#define	B0_IMR		0x000c	/* D: interrupt mask */
#define	B0_HWE_ISR	0x0010	/* D: hardware interrupt status */
#define	B0_HWE_IMR	0x0014	/* D: hardware interrupt mask */
#define	B0_SP_ISR	0x0018	/* D: special interrupt status */
#define	B0_ISR2		0x001c	/* D: interrupt status 2 (y2)*/
#define	B0_ISR3		0x0020	/* D: interrupt status 3 (y2)*/
#define	B0_EISR		0x0024	/* D: enter interrupt status (y2)*/
#define	B0_LISR		0x0028	/* D: leave interrupt status (y2)*/
#define	B0_ICR		0x002c	/* D: interrupt control register (y2)*/
#define	B0_R1_CSR	0x0060	/* D: BMU csr Rx Q1 */
#define	B0_R2_CSR	0x0064	/* D: BMU csr Rx Q2 */
#define	B0_XS1_CSR	0x0068	/* D: BMU csr sync  Tx Q1 */
#define	B0_XA1_CSR	0x006c	/* D: BMU csr async Tx Q1 */
#define	B0_XS2_CSR	0x0070	/* D: BMU csr sync  Tx Q2 */
#define	B0_XA2_CSR	0x0074	/* D: BMU csr async Tx Q2 */

#define	B2_MAC_1	0x0100	/* B8: physical mac address */
#define	B2_MAC_2	0x0108	/* B8: logical mac address for port 0 */
#define	B2_MAC_3	0x0110	/* B8: logical mac address for port 1 */

#define	B2_MAC_CFG	0x011a	/* B: */
#define	B2_CHIP_ID	0x011b	/* B: chip id */

#define	B2_TI_INI	0x0130	/* D: HW Timer init value register */
#define	B2_TI_CTRL	0x0134	/* D: HW Timer value register */
#define	B2_TI_CTRL	0x0138	/* B: HW Timer contror register */
#define	B2_TI_TEST	0x0139	/* B: HW Timer test register */

#define	B2_I2C_CTRL	0x0160	/* D: i2c hw register */
#define	B2_I2C_DATA	0x0164	/* D: i2c hw register */
#define	B2_I2C_IRQ	0x0168	/* D: i2c hw register */
#define	B2_I2C_SW	0x016c	/* D: i2c hw register */


#define	B8_Q_REGS	0x400		/* queue registes base */
#define	R1_Q		0x400

/* control status register, offset 0x04 */
/* #define	CSR_CMAIN	0x20000	/* r- */
/* #define	CSR_VAUX	0x10000	/* r- */
#define	CSR_WOL_SET	0x8000	/* -w */
#define	CSR_WOL_CLR	0x4000	/* -w */
#define	CSR_ASF_SET	0x2000	/* -w */
#define	CSR_ASF_CLR	0x1000	/* -w */
#define	CSR_CLKRUN_SET	0x0800	/* -w */
#define	CSR_CLKRUN_CLR	0x0400	/* -w */
#define	CSR_STATLED_SET	0x0200	/* -w */
#define	CSR_STATLED_CLR	0x0100	/* -w */
#define	CSR_SWIRQ_SET	0x0080	/* -w */
#define	CSR_SWIRQ_CLR	0x0040	/* -w */
#define	CSR_STOPPED	0x0020	/* r- */
#define	CSR_STOP_MASTER	0x0010	/* -w */
#define	CSR_MRST_CLR	0x0008	/* -w */
#define	CSR_MRST_SET	0x0004	/* -w */
#define	CSR_RST_CLR	0x0002	/* -w */
#define	CSR_RST_SET	0x0001	/* -w */

/* B2 MACCFG register */
#define	MACCFG_REV	0x00f0	/* chip revision */
#define		MACCFG_REV_SHIFT	4
#define	MACCFG_2CLK_D	0x0002	/* disable clock for 2nd mac */
#define	MACCFG_2MAC_D	0x0001	/* disable 2nd mac */

/* B2 CHIPID register */
#define	CHIPID_GENESIS		0x0a
#define	CHIPID_YUKON		0xb0
#define	CHIPID_YUKON_LITE	0xb1
#define	CHIPID_YUKON_LP		0xb2
#define	CHIPID_YUKON_XL		0xb3
#define	CHIPID_YUKON_EC_U	0xb4
#define	CHIPID_YUKON_EC		0xb6
#define	CHIPID_YUKON_FE		0xb7

/* B2 timer control register, offset 138  */
#define	TI_CTRL_START		0x04
#define	TI_CTRL_STOP		0x02
#define	TI_CTRL_CLRINT		0x01

/* B2 I2C_CTRL register, offset 164 */
#define	I2C_CTRL_START		0x80000000
#define	I2C_CTRL_REG		0x7fff0000
#define		I2C_CTRL_REG_SHIFT	16
#define	I2C_CTRL_DEV		0x0000fe00
#define		I2C_CTRL_DEV_SHIFT	9
#define	I2C_CTRL_BURST		0x00000010
#define		I2C_CTRL_BURST_SHIFT	4
#define	I2C_CTRL_SIZE		0x0000000e
#define		I2C_CTRL_SIZE_SHIFT	1
#define	I2C_CTRL_STOP		0x00000001

/* B2 I2C_IRQ register, offset 168 */
#define	I2C_IRQ_CLR		0x0001

/* GMAC section */
#define	GMAC_BASE0	0x2800
#define	GMAC_BASE1	0x3800
#define	GMAC_BASE(port)	((port) == 0 ? GMAC_BASE0 : GMAC_BASE1)

/* GMAC registers offset from GMAC base */
#define	GPSTAT		0x0000	/* W: general purpose status register */
#define	GPCTL		0x0004	/* W: general purpose control register */
#define	TXCTL		0x0008	/* W: tx control register */
#define	RXCTL		0x000c	/* W: rx control register */
#define	TXFC		0x0010	/* W: tx flow control register */
#define	TXPARAM		0x0014	/* W: tx parameter register */
#define	SMOD		0x0018	/* W: serial mode register */
#define	PAR0		0x001c	/* W6: pause frame src address */
#define	PAR1		0x0028	/* W6: physcal address */
#define	MCHASH		0x0034	/* D4: multicast hash filter */

#define	ISRTX		0x0044	/* W: */
#define	ISRRX		0x0048	/* W: */
#define	ISRTR		0x004c	/* W: */
#define	IMRTX		0x0050	/* W: */
#define	IMRRX		0x0054	/* W: */
#define	IMRTR		0x0058	/* W: */

#define	SMI_CR		0x0080
#define	SMI_DATA	0x0084
#define	PHY_ADDR	0x0088
#define	MIB_COUNTER	0x0100

/*
 * every registers below exist 2 set for 2channel in offset 0x80
 */

#define	LNK_SYNC_INI0	0x0c30	/* D: Link Sync Cnt Init Value */
#define	LNK_SYNC_VAL0	0x0c34	/* D: Link Sync Cnt Current Value */
#define	LNK_SYNC_CTRL0	0x0c38	/* B: Link Sync Cnt Control Register */
#define	LNK_SYNC_TST0	0x0c39	/* B: Link Sync Cnt Test Register */
#define	LNK_LED_REG0	0x0c3c	/* B: Link LED Register */
#define	RX_GMF_EA0	0x0c40	/* D: Rx GMAC FIFO End Address */
#define	RX_GMF_AF_THR0	0x0c44	/* D: Rx GMAC FIFO Almost Full Thresh. */
#define	RX_GMF_CTRL_T0	0x0c48	/* D: Rx GMAC FIFO Control/Test */
#define	RX_GMF_FL_MSK0	0x0c4c	/* D: Rx GMAC FIFO Flush Mask */
#define	RX_GMF_FL_THR0	0x0c50	/* D: Rx GMAC FIFO Flush Threshold */
#define	RX_GMF_TR_THR0	0x0c54	/* D: Rx Truncation Threshold (Yukon-2) */
#define	RX_GMF_UP_THR0	0x0c58	/* B: Rx Upper Pause Thr (Yukon-EC_U) */
#define	RX_GMF_LP_THR0	0x0c5a	/* D: Rx Lower Pause Thr (Yukon-EC_U) */
#define	RX_GMF_VLAN0	0x0c5c	/* D: Rx VLAN Type Register (Yukon-2) */
#define	RX_GMF_WP0	0x0c60	/* D: Rx GMAC FIFO Write Pointer */
#define	RX_GMF_WLEV0	0x0c68	/* D: Rx GMAC FIFO Write Level */
#define	RX_GMF_RP0	0x0c70	/* D: Rx GMAC FIFO Read Pointer */
#define	RX_GMF_RLEV0	0x0c78	/* D: Rx GMAC FIFO Read Level */

#define	LNK_SYNC_INI1	0x0cb0	/* D: Link Sync Cnt Init Value */
#define	LNK_SYNC_VAL1	0x0cb4	/* D: Link Sync Cnt Current Value */
#define	LNK_SYNC_CTRL1	0x0cb8	/* B: Link Sync Cnt Control Register */
#define	LNK_SYNC_TST1	0x0cb9	/* B: Link Sync Cnt Test Register */
#define	LNK_LED_REG1	0x0cbc	/* B: Link LED Register */
#define	RX_GMF_EA1	0x0cc0	/* D: Rx GMAC FIFO End Address */
#define	RX_GMF_AF_THR1	0x0cc4	/* D: Rx GMAC FIFO Almost Full Thresh. */
#define	RX_GMF_CTRL_T1	0x0cc8	/* D: Rx GMAC FIFO Control/Test */
#define	RX_GMF_FL_MSK1	0x0ccc	/* D: Rx GMAC FIFO Flush Mask */
#define	RX_GMF_FL_THR1	0x0cd0	/* D: Rx GMAC FIFO Flush Threshold */
#define	RX_GMF_TR_THR1	0x0cd4	/* D: Rx Truncation Threshold (Yukon-2) */
#define	RX_GMF_UP_THR1	0x0cd8	/* B: Rx Upper Pause Thr (Yukon-EC_U) */
#define	RX_GMF_LP_THR1	0x0cda	/* D: Rx Lower Pause Thr (Yukon-EC_U) */
#define	RX_GMF_VLAN1	0x0cdc	/* D: Rx VLAN Type Register (Yukon-2) */
#define	RX_GMF_WP1	0x0ce0	/* D: Rx GMAC FIFO Write Pointer */
#define	RX_GMF_WLEV1	0x0ce8	/* D: Rx GMAC FIFO Write Level */
#define	RX_GMF_RP1	0x0ce0	/* D: Rx GMAC FIFO Read Pointer */
#define	RX_GMF_RLEV1	0x0ce8	/* D: Rx GMAC FIFO Read Level */

#define	GMAC_CTRL0	0x0f00	/* D: GMAC Control Reg */
#define	GPHY_CTRL0	0x0f04	/* D: GPHY Control Reg */
#define	GMAC_IRQ_SRC0	0x0f08	/* B: GMAC Interrupt Source Reg */
#define	GMAC_IRQ_MSK0	0x0f0c	/* B: GMAC Interrupt Mask Reg */
#define	GMAC_LINK_CTRL0	0x0f10	/* W: Link Control Reg */

#define	GMAC_CTRL1	0x0f80	/* D: GMAC Control Reg */
#define	GPHY_CTRL1	0x0f84	/* D: GPHY Control Reg */
#define	GMAC_IRQ_SRC1	0x0f88	/* B: GMAC Interrupt Source Reg */
#define	GMAC_IRQ_MSK1	0x0f8c	/* B: GMAC Interrupt Mask Reg */
#define	GMAC_LINK_CTRL1	0x0f90	/* W: Link Control Reg */


/* general purpose status register, offset 0x00 */
#define	GPSTAT_100M	0x8000	/* port speed is 100M */
#define	GPSTAT_FDX	0x4000	/* duplex mode */
#define	GPSTAT_TXFLOW_D	0x2000	/* tx flow control disabled */
#define	GPSTAT_LINKUP	0x1000	/* link up */
#define	GPSTAT_PAUSED	0x0800	/* link up */
#define	GPSTAT_TXBUSY	0x0400	/* tx busy */
#define	GPSTAT_EXC	0x0200	/* excessive collision */
#define	GPSTAT_OWC	0x0100	/* out of window collision */
#define	GPSTAT_PSH	0x0020	/* PHY status changed */
#define	GPSTAT_1G	0x0010	/* port speed is 1G */
#define	GPSTAT_PART	0x0008	/* partition mode */
#define	GPSTAT_RXFLOW_D	0x0004	/* rx flow control disabled */
#define	GPSTAT_PROMISC	0x0002	/* promiscuous mode */

/* general purpose control register, offset 0x00 */
#define	GPCTL_PROMISC	0x4000	/* enable promisc mode */
#define	GPCTL_TXFLOW_D	0x2000	/* disable tx flow control */
#define	GPCTL_TX	0x1000	/* enable tx */
#define	GPCTL_RX	0x0800	/* enable rx */
#define	GPCTL_BURST	0x0400	/* enable burst mode */
#define	GPCTL_LOOP	0x0200	/* enable mac loopback mode */
#define	GPCTL_PART	0x0100	/* enable partition mode */
#define	GPCTL_SPEED	0x0088	/* speed */
#define		GPCTL_SPEED_1G		0x0088
#define		GPCTL_SPEED_100M	0x0008
#define		GPCTL_SPEED_10M		0x0000
#define	GPCTL_FORCELINK	0x0040	/* force link pass */
#define	GPCTL_FDX	0x0020	/* full duplex */
#define	GPCTL_RXFLOW_D	0x0010	/* disable rx flow control */
#define	GPCTL_AU_DUP_D	0x0004	/* disable auto-update duplex */
#define	GPCTL_AU_FC_D	0x0002	/* disable auto-update flow control */
#define	GPCTL_AU_SPD_D	0x0001	/* disable auto-update speed */

/* tx control register, offset 0x10 */
#define	TXCTL_FORCEJUM	0x8000
#define	TXCTL_CRC_DIS	0x4000
#define	TXCTL_PAD_DIS	0x2000
#define	TXCTL_COLTHRESH	0x1c00
#define		TXCTL_COLTHRESH_SHIFT	10
#define		TXCTL_COLTHRESH_STD	(4 << TXCTL_COLTHRESH_SHIFT)

/* rx control register, offset 0x10 */
#define	RXCTL_PPA	0x8000	/* pass unicast address */
#define	RXCTL_PMA	0x4000	/* pass multicast address */
#define	RXCTL_NOCRC	0x2000	/* remove crc */
#define	RXCTL_PFC	0x1000	/* pass flow control packets */

/* tx param register, offset 0x10 */
#define	TXPARAM_JAMLEN	0xc000	/* jum length */
#define		TXPARAM_JUMLEN_SHIFT	14
#define		TXPARAM_JUMLEN_STD	(3 << TXPARAM_JUMLEN_SHIFT)
#define	TXPARAM_JAMIPG	0x3e00	/* jum ipg */
#define		TXPARAM_JUMIPG_SHIFT	9
#define		TXPARAM_JUMIPG_STD	(0xb << TXPARAM_JUMIPG_SHIFT)
#define	TXPARAM_JAMDATA	0x01f0	/* ipg jum to data */
#define		TXPARAM_JAMDATA_SHIFT	4
#define		TXPARAM_JAMDATA_STD	(0x1c << TXPARAM_JAMDATA_SHIFT)
#define	TXPARAM_BACKOFF	0x000f	/* ipg jum to data */
#define		TXPARAM_BACKOFF_STD	0x0004

/* serial mode register, offset 0x10 */
#define	SERMOD_DATABL	0xf800	/* data blinder (ro)*/
#define		SERMOD_DATABL_SHIFT	11
#define		SERMOD_DATABL_STD	(4 << SERMOD_DATABL_SHIFT)
#define	SERMOD_RTRY4	0x0400	/* retry tx 4 times */
#define	SERMOD_VLAN	0x0200	/* vlan 1:enable 0:disable */
#define	SERMOD_JUMBO	0x0100	/* jumbo frame 1:enable 0:disable */
#define	SERMOD_IPG	0x00ff	/* ipg */
#define		SERMOD_IPG_STD	0x001e

/* SMI control register, offset 0x80 */
#define	SMI_CR_PHY	0xf800		/* phy address */
#define		SMI_CR_PHY_SHIFT	11
#define	SMI_CR_REG	0x07c0		/* register location */
#define		SMI_CR_REG_SHIFT	6
#define	SMI_CR_READ	0x0020		/* 1:read , 0: write */
#define	SMI_CR_VALID	0x0010		/* read data valid */
#define	SMI_CR_BUSY	0x0008		/* command in progress */

/* SMI data register, offset 0x84 */

/* PHY_ADDR register, offset 0x88 */
#define	PHY_ADDR_CLR	0x0020		/* clear MIB counter on read */
#define	PHY_ADDR_TST	0x0010		/* load MIC counters (for diag) */

/* MIB counter, offse 0x0100 to 0x025c */
#define	NUM_MIB_COUNTER	(0x160/4)

/* GMAC_CTRL register, offset */
#define	GMC_H_BURST_ON	0x00000080	/* Half Duplex Burst Mode On */
#define	GMC_H_BURST_OFF	0x00000040	/* Half Duplex Burst Mode Off */
#define	GMC_F_LOOPB_ON	0x00000020	/* FIFO Loopback On */
#define	GMC_F_LOOPB_OFF	0x00000010	/* FIFO Loopback Off */
#define	GMC_PAUSE_ON	0x00000008	/* Pause On */
#define	GMC_PAUSE_OFF	0x00000004	/* Pause Off */
#define	GMC_RST_CLR	0x00000002	/* Clear GMAC Reset */
#define	GMC_RST_SET	0x00000001	/* Set GMAC Reset */

/* GPHY_CTRL register, offset */
#define	GPC_SEL_BDT	0x10000000	/* Select Bi-Dir.Transfer for MDC/MDIO*/
#define	GPC_INT_POL_HI	0x08000000	/* IRQ Polarity is Active HIGH */
#define	GPC_75_OHM	0x04000000	/* Use 75Ohm Termination instead of 50*/
#define	GPC_DIS_FC	0x02000000	/* Disable Automatic Fiber/Copper Detection */
#define	GPC_DIS_SLEEP	0x01000000	/* Disable Energy Detect */
#define	GPC_HWCFG_M	0x00f00000	/* HWCFG_MODE */
#define		GPC_HWCFG_M_SHIFT	20
#define	GPC_ANEG_0	0x00080000	/* ANEG[0] */
#define	GPC_ENA_XC	0x00040000	/* Enable MDI crossover */
#define	GPC_DIS_125	0x00020000	/* Disable 125 MHz clock */
#define	GPC_ANEG_3	0x00010000	/* ANEG[3] */
#define	GPC_ANEG_2	0x00008000	/* ANEG[2] */
#define	GPC_ANEG_1	0x00004000	/* ANEG[1] */
#define	GPC_ENA_PAUSE	0x00002000	/* Enable Pause (SYM_OR_REM) */
#define	GPC_PHYADDR	0x00001f00	/* Phy Addr */
#define		GPC_PHYADDR_SHIFT	8
#define	GPC_RST_CLR	0x00000002	/* Clear GPHY Reset */
#define	GPC_RST_SET	0x00000001	/* Set   GPHY Reset */

/* queue registers offset */
#define	Q_D		0x00	/* currect descriptor */
#define	Q_DA		0x20	/* D*2: current descriptor address */
#define	Q_DONE		0x24	/* W: done index (y2) */
#define	Q_AC		0x28	/* D*2: current address counter */
#define	Q_BC		0x30	/* D: current byte counter */
#define	Q_CSR		0x34	/* D: BMU control & status register */
#define	Q_F		0x38	/* D: flags *
#define	Q_T1		0x3c	/* D: test register 1 */
#define	Q_WM		0x40	/* W: fifo water mark */
#define	Q_AL		0x42	/* W: fifo alignment */

#define	Q_RX_RSP	0x44	/* W: fifo read shadow pointer */
#define	Q_RX_RSL	0x46	/* W: fifo read shadow level */
#define	Q_RX_RP		0x48	/* W: fifo read pointer */
#define	Q_RX_RL		0x4a	/* W: fifo read level */
#define	Q_RX_WP		0x4c	/* B: fifo write pointer */
#define	Q_RX_WSP	0x4d	/* B: fifo write shadow pointer */
#define	Q_RX_WL		0x4e	/* B: fifo write level */
#define	Q_RX_WSL	0x4f	/* B: fifo write shadow level */

#define	Q_TX_RSP	0x44	/* W: fifo write shadow pointer */
#define	Q_TX_RSL	0x46	/* B: fifo write shadow level */
#define	Q_TX_RP		0x48	/* B: fifo write pointer */
#define	Q_TX_RL		0x4a	/* B: fifo write level */
#define	Q_TX_WP		0x4c	/* B: fifo read pointer */
#define	Q_TX_WL		0x4e	/* B: fifo read level */

/* prefetch unit registers offset */
#define	P_CTRL		0x50	/* D: prefetch unit control register */
#define	P_LAST_IDX	0x54	/* D: last index regsister */
#define	P_ADDR_LO	0x58	/* D: list start address (low) */
#define	P_ADDR_HI	0x5c	/* D: list start address (high) */
#define	P_GET_IDX	0x60	/* W: get index regsister */
#define	P_PUT_IDX	0x64	/* W: put index regsister */
#define	P_FIFO_WP	0x70	/* B: fifo write pointer */
#define	P_FIFO_RP	0x74	/* B: fifo read pointer */
#define	P_FIFO_WM	0x78	/* B: fifo watermark */
#define	P_FIFO_LVL	0x7c	/* B: fifo level */


/*
 * descriptor commands
 */
#define	CMD_TCPWRITE	0x11
#define	CMD_TCPSTART	0x12
#define	CMD_TCPINIT	0x14
#define	CMD_TCPLCK	0x18
#define	CMD_TCPCKSUM	0x12
#define	CMD_TCPIS	0x16
#define	CMD_TCPLW	0x19
#define	CMD_TCPLSW	0x1b
#define	CMD_TCPLISW	0x1f

#define	CMD_ADDR64	0x21
#define	CMD_VLAN	0x22
#define	CMD_ADDR64VLAN	0x23
#define	CMD_LRGLEN	0x24
#define	CMD_LRGLENVLAN	0x26

#define	CMD_BUFFER	0x40
#define	CMD_PACKET	0x41
#define	CMD_LARGESEND	0x43

/*
 * status commands
 */
#define	CMD_RXSTART	0x60
#define	CMD_RXTIMESTAMP	0x61
#define	CMD_RXVLAN	0x62
#define	CMD_RXCHKS	0x64
#define	CMD_RXCHKSVLAN	0x66
#define	CMD_RXTIMEVLAN	0x63
#define	CMD_RSS_HASH	0x65
#define	CMD_TXINDEXLE	0x68

#define	CMD_PUTIDX	0x70

/*
 * yukon2 descriptor definition
 */
struct tx_desc {
	uint32_t	arg;
	uint32_t	cmd;

#define	TXDESC_CMD_SHIFT	24
};
