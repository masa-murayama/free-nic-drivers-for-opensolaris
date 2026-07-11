h29122
s 00181/00040/01227
d D 1.6 11/07/10 22:11:03 mrym 6 5
c 2.6.8 
e
s 00368/00069/00899
d D 1.5 10/09/08 17:51:39 mrym 5 4
c 2.6.6
e
s 00016/00011/00952
d D 1.4 09/05/17 21:28:42 mrym 4 3
c 2.6.4, many fixed for L1E
e
s 00465/00112/00498
d D 1.3 05/01/01 01:22:43 mrym 3 2
c 2.6.3
e
s 00062/00015/00548
d D 1.2 08/10/05 17:01:29 mrym 2 1
c 2.6.1
e
s 00563/00000/00000
d D 1.1 08/08/18 00:17:29 mrym 1 0
c date and time created 08/08/18 00:17:29 by mrym
e
u
U
f e 0
t
T
I 1
/*
 * atl1reg.h
 * Macro definitions for Attansic L1 register definition
 * This file is public domain. Coded by Masa Murayama
 */

#pragma ident   "%W% %E%"

#ifndef __ATL1REG_H__
#define	__ATL1REG_H__

/*
 * Register offset
 */
I 2
D 3
#define	PM_CTRLSTAT	0x0044
E 2
#define	PCIE_CAP_LIST	0x0058
I 2
#define	PCIE_DEVCTRL	0x0060
E 2
#define	VPDCAP		0x006c
#define	VPDDATA		0x0070
E 3
I 3
#define	PM_CTRLSTAT	0x0044	/* L1 L2 */
#define	PCIE_CAP_LIST	0x0058	/* L1 L2 */
#define	PCIE_DEVCTRL	0x0060	/* L1 */
#define	VPDCAP		0x006c	/* L1 L2 */
#define	VPDDATA		0x0070	/* L1 L2 */
E 3
I 2

E 2
#define	FLASHCTL	0x0200
I 6
#define	PCIE_PHYMISC	0x1000	/* L*C, L*D */
#define	PCIE_PHYMISC2	0x1004	/* L*C, L*D */
E 6
D 3
#define	MSTC		0x1400	/* D: master control register */
#define	SOFTTIMER_INIT	0x1404
#define	INTRDELAY_INIT	0x1408
#define	GPHYC		0x140c	/* W: GPHY control register */
#define	ISMDISDMA_TIMER	0x140e
#define	IDLE		0x1410	/* D: idle status  */
#define	MIIC		0x1414	/* D: mdio control */
#define	PHYSTAT		0x1418
#define	MACCTL		0x1480	/* D: mac control */
#define	GAPC		0x1484
#define	MACADDR		0x1488
#define	MHASH		0x1490
#define	HDCTL		0x1498
#define	MTU		0x149c
I 2
#define	WOLCTL		0x14a0
E 3
I 3
#define	PCIE_DLLTXCTRL1	0x1104	/* L2 */
I 5
#define	EEPROMCTL	0x12c0	/* L1C */
#define	EEPROM_DATA	0x12c4	/* L1C */
#define	OTPCTL		0x12f0	/* L1C */
I 6
#define	PM_CTRL		0x12f8	/* L*C, L*D */
E 6
E 5
#define	LTSSM_TEST_MODE	0x12fc	/* L1 L2 */
I 6
#define	LTSSM_ID_CTRL	0x12fc	/* L*C, L*D */
E 6

#define	MSTC		0x1400	/* D: master control register L1 L2 */
#define	SOFTTIMER_INIT	0x1404	/* L1 L2 */
#define	INTRDELAY_INIT	0x1408	/* W: interrupt delay timer L1 L2 */
#define	INTRDELAY2_INIT	0x140a	/* W: L1E */
#define	GPHYC		0x140c	/* W: GPHY control register L1 L2 LE */
D 5
#define	INTRCLR_TIMER	0x140e	/* W: L1 L1E */
E 5
I 5
#define	INTRCLR_TIMER	0x140e	/* W: except L1C */
E 5
#define	IDLE		0x1410	/* D: idle status L1 L2 LE */
#define	MIIC		0x1414	/* D: mdio control L1 L2 */
#define	PHYSTAT		0x1418	/* L1E */
D 6
#define	SERDES_LOCK	0x1424	/* L2 */
E 6
I 6
#define	SERDES_LOCK	0x1424	/* L2 L2C */
E 6
#define	MACCTL		0x1480	/* D: mac control L1 L2 Le */
#define	GAPC		0x1484	/* D: L1 L2 Le */
D 5
#define	MACADDR		0x1488	/* D: L1 LE L2 */
E 5
I 5
#define	MACADDR		0x1488	/* D: L1 LE L2 L1C */
E 5
#define	MHASH		0x1490	/* D: L1 LE L2 */
#define	HDCTL		0x1498	/* D: L1 L2 LE */
#define	MTU		0x149c	/* D: L1 L2 LE */
#define	WOLCTL		0x14a0	/* D: L1 L2 LE */
E 3
#define	WOLPAT		0x14a4	/* D*2: */
E 2
D 3
#define	RAM_RBD_BASE	0x1500
#define	RAM_RBD_SIZE	0x1504
#define	RAM_RSD_BASE	0x1508
#define	RAM_RSD_SIZE	0x150c
#define	RAM_TBD_BASE	0x1510
#define	RAM_TBD_SIZE	0x1514
#define	RAM_TRD_BASE	0x1518
#define	RAM_TRD_SIZE	0x151c
#define	RAM_RXF_BASE	0x1520
#define	RAM_RXF_SIZE	0x1524
#define	RAM_TXF_BASE	0x1528
#define	RAM_TXF_SIZE	0x152c
#define	RAM_TCPH_PATH	0x1530
#define	DESCEN		0x1534
#define	DESCBASE	0x1540
#define	RBDADDR		0x1544
#define	RSDADDR		0x1548
#define	TBDADDR		0x154c
#define	ISMADDR		0x1550
#define	SMADDR		0x1554
#define	RBD_RSD_CNT	0x1558
#define	TBD_CNT		0x155c
#define	TXQCTL		0x1580
#define	TXJCFG		0x1584
#define	RXQCTL		0x15a0
#define	RXJCFG		0x15a4
#define	RXFFC		0x15a8
#define	RSDFC		0x15ac
#define	DMAC		0x15c0
#define	ISMCTL		0x15d0
#define	ISMTHRESH	0x15d4
#define	ISMDELAY	0x15d8
#define	ISM_RX_PKT_CNT	0x15dc
#define	ISM_TX_PKT_CNT	0x15e0
#define	SMDELAY		0x15e4
#define	MBOX		0x15f0
E 3
I 3

/*
 * chip family depend section
 */
/* L1 */
#define	RAM_RBD_BASE_1	0x1500
#define	RAM_RBD_SIZE_1	0x1504
#define	RAM_RSD_BASE_1	0x1508
#define	RAM_RSD_SIZE_1	0x150c
#define	RAM_TBD_BASE_1	0x1510
#define	RAM_TBD_SIZE_1	0x1514
#define	RAM_TRD_BASE_1	0x1518
#define	RAM_TRD_SIZE_1	0x151c
#define	RAM_RXF_BASE_1	0x1520
#define	RAM_RXF_SIZE_1	0x1524
#define	RAM_TXF_BASE_1	0x1528
#define	RAM_TXF_SIZE_1	0x152c
#define	RAM_TCPH_PATH_1	0x1530
#define	DESCEN_1	0x1534
#define	DESCBASE_1	0x1540	/* D: */
#define	RBDADDR_1	0x1544	/* D: */
#define	RSDADDR_1	0x1548	/* D: */
#define	TBDADDR_1	0x154c	/* D: */
#define	ISMADDR_1	0x1550
#define	SMADDR_1	0x1554
#define	RBD_RSD_CNT_1	0x1558
#define	TBD_CNT_1	0x155c
#define	TXQCTL_1		0x1580
#define	TXJCFG_1		0x1584
#define	RXQCTL_1		0x15a0
#define	RXJCFG_1		0x15a4
#define	RXFFC_1			0x15a8
#define	RSDFC_1			0x15ac
#define	DMAC_1			0x15c0
#define	ISMCTL_1		0x15d0	/* L1 */
#define	ISMTHRESH_1		0x15d4	/* L1 */
#define	ISMDELAY_1		0x15d8	/* L1 */
#define	ISM_RX_PKT_CNT_1	0x15dc	/* L1 */
#define	ISM_TX_PKT_CNT_1	0x15e0	/* L1 */
#define	SMDELAY_1		0x15e4	/* L1 */
#define	MBOX_1			0x15f0

/* L1E */
#define	IDT_TABLE4_1e		0x14e0
#define	IDT_TABLE5_1e		0x14e4
#define	IDT_TABLE6_1e		0x14e8
#define	IDT_TABLE7_1e		0x14ec
#define	RAM_TRD_BASE_1e		0x1518
#define	RAM_TRD_SIZE_1e		0x151c
#define	RAM_RXF_BASE_1e		0x1520
#define	RAM_RXF_SIZE_1e		0x1524
#define	RAM_TXF_BASE_1e		0x1528
#define	RAM_TXF_SIZE_1e		0x152c
#define	RAM_TCPH_PKTH_1e	0x1530
#define	DESCEN_1e		0x1534
#define	RXF3_RING_BASE_HI_1e	0x153c
#define	DESCBASE_1e		0x1540
#define	RXF0_RING_BASE_1e	0x1544	/* D*2: L1E */
#define	TBDADDR_1e		0x154c
#define	RXF1_RING_BASE_HI_1e	0x1550
#define	RXF2_RING_BASE_HI_1e	0x1554
#define	RXF_RING_HIWAT_1e	0x1558
#define	TBD_CNT_1e		0x155c
#define	IDT_TABLE0_1e		0x1560
#define	IDT_TABLE1_1e		0x1564
#define	IDT_TABLE2_1e		0x1568
#define	IDT_TABLE3_1e		0x156c
#define	RSS_HASH_VAL_1e		0x1570
#define	RSS_HASH_FLAG_1e	0x1574
#define	BASE_CPU_NUM_1e		0x157c
#define	TXQCTL_1e		0x1580
#define	TXJCFG_1e		0x1584
#define	RXQCTL_1e		0x15a0
#define	RXJCFG_1e		0x15a4
#define	RXFFC_1e		0x15a8
#define	RSDFC_1e		0x15ac
#define	DMAC_1e			0x15c0
#define	SM_TIMER_1e		0x15c4
#define	TX_COALSC_PKT_1e	0x15c8	/* W: L1E */
#define	RX_COALSC_PKT_1e	0x15ca	/* W: L1E */
#define	TX_COALSC_TO_1e		0x15cc	/* W: L1E */
#define	RX_COALSC_TO_1e		0x15ce	/* W: L1E */
#define	RXF1_RING_BASE_1e	0x15d0	/* D*2: L1E */
#define	RXF2_RING_BASE_1e	0x15d8	/* D*2: L1E */
#define	RXF3_RING_BASE_1e	0x15e0	/* D*2: L1E */
#define	MBOX_1e			0x15f0
#define	RXF_RING_VALID_1e	0x15f4	/* B*2*4: L1E */

/* L2 */
D 5
#define	RAMTXTAIL_2	0x1500	/* W: */
#define	RAMRXTAIL_2	0x1502	/* W: */
#define	DESCBASE_2	0x1540	/* D: */
#define	TBDADDR_2	0x1544	/* D: 4byte align */
#define	TBDLEN_2	0x1548	/* D: max 256KB */
#define	TSDADDR_2	0x154c	/* D: 4byte align */
#define	TSDCNT_2	0x1550	/* D: in 4 byte */
#define	RBDADDR_2	0x1554	/* D: 4byte align */
#define	RBDCNT_2	0x1558	/* D: in 1536 byte */
#define	DMAR_2		0x1580	/* W: */
#define	TXTHRESH_2	0x1590	/* D: in 2 byte */
#define	DMAW_2		0x15a0	/* W: */
#define	RXHIWAT_2	0x15a8	/* W: */
#define	RXLOWAT_2	0x15aa	/* W: */
#define	TBDTAIL_2	0x15f0	/* D: */
#define	RBDTAIL_2	0x15f4	/* D: */
E 5
I 5
#define	RAMTXTAIL_2		0x1500	/* W: */
#define	RAMRXTAIL_2		0x1502	/* W: */
#define	DESCBASE_2		0x1540	/* D: */
#define	TBDADDR_2		0x1544	/* D: 4byte align */
#define	TBDLEN_2		0x1548	/* D: max 256KB */
#define	TSDADDR_2		0x154c	/* D: 4byte align */
#define	TSDCNT_2		0x1550	/* D: in 4 byte */
#define	RBDADDR_2		0x1554	/* D: 4byte align */
#define	RBDCNT_2		0x1558	/* D: in 1536 byte */
#define	DMAR_2			0x1580	/* W: */
#define	TXTHRESH_2		0x1590	/* D: in 2 byte */
#define	DMAW_2			0x15a0	/* W: */
#define	RXHIWAT_2		0x15a8	/* W: */
#define	RXLOWAT_2		0x15aa	/* W: */
#define	TBDTAIL_2		0x15f0	/* D: */
#define	RBDTAIL_2		0x15f4	/* D: */
E 5

I 5
/* L1C */
I 6
#define	IDT_TABLE0_1c		0x14e0
E 6
#define	SRAM_RFD0_INFO_1c	0x1500
#define	SRAM_RFD1_INFO_1c	0x1504
#define	SRAM_RFD2_INFO_1c	0x1508
#define	SRAM_RFD3_INFO_1c	0x150c

#define	RFD_NIC_LEN_1c		0x1510	/* Dx2 */

#define	SRAM_TRD_ADDR_1c	0x1518
#define	SRAM_TRD_LEN_1c		0x151c

#define	SRAM_RXF_ADDR_1c	0x1520
#define	SRAM_RXF_LEN_1c		0x1524
#define	SRAM_TXF_ADDR_1c	0x1528
#define	SRAM_TXF_LEN_1c		0x152C
#define	SRAM_TCPH_ADDR_1c	0x1530
#define	SRAM_PKTH_ADDR_1c	0x1532

#define	DESCEN_1c		0x1534	/* D: load pointer */
#define	RX_BASE_HI_1c		0x1540
#define	TX_BASE_HI_1c		0x1544
#define	SMB_BASE_HI_1c		0x1548
#define	SMB_BASE_LO_1c		0x154C
#define	RFD_HEAD_LO_1c		0x1550
#define	RFD_RING_SIZE_1c	0x1560
#define	RX_BUF_SIZE_1c		0x1564
#define	RRD_HEAD_LO_1c		0x1568
#define	RRD_RING_SIZE_1c	0x1578
#define	HTPD_HEAD_LO_1c		0x157C
#define	NTPD_HEAD_LO_1c		0x1580
#define	TPD_RING_SIZE_1c	0x1584
#define	CMB_BASE_LO_1c		0x1588

#define	TXQCTL_1c		0x1590
#define	TSO_THRESH_1c		0x1594
I 6
#define	TXF_WATER_MARK_1c	0x1598
E 6
#define	RXQCTL_1c		0x15a0
I 6
#define	RXQ_RXF_PAUSE_THRSH_1c	0x15a8
#define	RXD_DMAC_1c		0x15ac
E 6

I 6
#define	BASE_CPU_NUM_1c		0x15b8

E 6
#define	DMAC_1c			0x15c0
#define	SM_CTL_1c		0x15c4

#define	MB_RFD_PROD_IDX		0x15e0
#define	MB_PRIO_PROD_IDX	0x15f0
#define	MB_NORMAL_PROD_IDX	0x15f2
#define	MB_PRIO_CONS_IDX	0x15f4
#define	MB_NORMAL_CONS_IDX	0x15f6

#define	MB_RFD01_CONS_IDX	0x15f8
#define	MB_RFD23_CONS_IDX	0x15fc

#define	HDS_CTL_1c		0x160c
#define	INTRCLR_TIMER_lc	0x1608

E 5
/* common registers */
E 3
#define	ISR		0x1600	/* D: interrupt status */
#define	IMR		0x1604	/* D: interrupt mask */
D 3
#define	CURR_RBD_RSD	0x1800
#define	CURR_TBD	0x1804
E 3

I 4
/* statistic counters */
/* L1E */
#define	MAC_STATS_BASE	0x1700

E 4
I 3
/* L1 */
#define	CURR_RBD_RSD_1	0x1800
#define	CURR_TBD_1	0x1804
E 3

I 3
/* L1E */
#define	RXF0_BASE_1e	0x1800	/* L1E: not used */
#define	TBDHEAD_1e	0x1804	/* W: */
#define	RXF1_BASE_1e	0x1808	/* L1E: not used */
#define	RXF2_BASE_1e	0x180c	/* L1E: not used */
#define	RXF3_BASE_1e	0x1810	/* L1E: not used */
#define	RXF_RING_MB_1e	0x1820	/* D*2*4: dma address for rx head */
#define	TBD_TAIL_PTR_1e	0x1840
#define	SMB_ADDR_1e	0x1844

I 6
/* L1C */
#define	CLK_GATING_1c	0x1814
E 6

I 6

E 6
E 3
/*
I 3
 * Vendor specific MII PHY registers
 */
I 6
#define	MII_IER		0x12
E 6
#define	MII_DBG_ADDR	0x1d
#define	MII_DBG_DATA	0x1e
I 6
#define MII_ANA_CTRL_0	0
#define MII_ANA_CTRL_4	4
#define MII_ANA_CTRL_5	5
#define MII_ANA_CTRL_11	11
#define MII_ANA_CTRL_18	18
#define MII_ANA_CTRL_41	41
#define MII_ANA_CTRL_54	54
E 6

/*
E 3
 * Register difinitions
 */
#define	VPDCAP_FLAG		0x80000000U
#define	VPDCAP_ADDR		0x7fff0000U
#define		VPDCAP_ADDR_SHIFT	16

/* flash control regster */
#define	FLASHCTL_WAIT_READY	0x10000000	/* X */
#define	FLASHCTL_EROM_PGSZ	0x0c000000	/* X */
#define		FLASHCTL_EROM_PGSZ_SHIFT	26	/* X */
#define	FLASHCTL_CS_SETUP	0x03000000	/* X */
#define		FLASHCTL_CS_SETUP_SHIFT	24	/* X */
#define	FLASHCTL_CLK_HI		0x00c00000	/* X */
#define		FLASHCTL_CLK_HI_SHIFT	22	/* X */
#define	FLASHCTL_CLK_LO		0x00300000	/* X */
#define		FLASHCTL_CLK_LO_SHIFT	20	/* X */
#define	FLASHCTL_CS_HOLD	0x000c0000	/* X */
#define		FLASHCTL_CS_HOLD_SHIFT	18	/* X */
#define	FLASHCTL_CS_HI		0x00030000	/* X */
#define		FLASHCTL_CS_HI_SHIFT	16	/* X */
#define	FLASHCTL_LDSTART	0x00008000	/* X */
#define	FLASHCTL_VPD_EN		0x00002000	/* X */
#define	FLASHCTL_START		0x00000800	/* X */
#define	FLASHCTL_INS		0x00000700	/* X */
#define		FLASHCTL_INS_SHIFT	8	/* X */
#define	FLASHCTL_STS_WPEN	0x00000080	/* X */
#define	FLASHCTL_STS		0x000000ff	/* X */
#define	FLASHCTL_STS_NON_RDY	0x00000001
#define	FLASHCTL_STS_WEN	0x00000002

I 6
/* PCIE_PHYMISC */
#define PCIE_PHYMISC_FORCE_RCV_DET	0x0004U

/* PCIE_PHYMISC2 */
#define PCIE_PHYMISC2_SERDES_CDR	0x00030000U
#define		PCIE_PHYMISC2_SERDES_CDR_SHIFT	16
#define PCIE_PHYMISC2_SERDES_TH		0x000c0000U
#define		PCIE_PHYMISC2_SERDES_TH_SHIFT	18

E 6
I 5
/* EEPROMCTL: eeprom control register, offset 12c0, L1C */
#define EEC_RW			0x80000000
#define EEC_ACK			0x40000000
#define	EEC_ADDR		0x03ff0000
#define		EEC_ADDR_SHIFT		16
#define		EEC_ADDR_MASK		0x3ff
#define EEC_DATA_HI		0x0000ffff
#define		EEC_DATA_HI_SHIFT	0

/* OTPCTL: offset 12f0, L1C */
#define	OTPCTL_CLK_EN		0x00000002

I 6
/* PM_CTRL: offset 12f8, L*C,L*D */
#define PM_CTRL_SDES_EN			0x00000001U
#define PM_CTRL_RBER_EN			0x00000002U
#define PM_CTRL_CLK_REQ_EN		0x00000004U
#define PM_CTRL_ASPM_L1_EN		0x00000008U
#define PM_CTRL_SERDES_L1_EN		0x00000010U
#define PM_CTRL_SERDES_PLL_L1_EN	0x00000020U
#define PM_CTRL_SERDES_PD_EX_L1		0x00000040U
#define PM_CTRL_SERDES_BUDS_RX_L1_EN	0x00000080U
#define PM_CTRL_L0S_ENTRY_TIMER		0x00000F00U
#define		PM_CTRL_L0S_ENTRY_TIMER_SHIFT	8
#define PM_CTRL_ASPM_L0S_EN		0x00001000U
#define PM_CTRL_CLK_SWH_L1		0x00002000U
#define PM_CTRL_CLK_PWM_VER1_1		0x00004000U
#define PM_CTRL_RCVR_WT_TIMER		0x00008000U
#define PM_CTRL_L1_ENTRY_TIMER		0x000f0000U
#define		PM_CTRL_L1_ENTRY_TIMER_SHIFT	16
#define PM_CTRL_PM_REQ_TIMER		0x00f00000U
#define		PM_CTRL_PM_REQ_TIMER_SHIFT	20
#define PM_CTRL_LCKDET_TIMER		0x0f000000U
#define		PM_CTRL_LCKDET_TIMER_SHIFT	24
#define PM_CTRL_EN_BUFS_RX_L0S		0x10000000U
#define PM_CTRL_SA_DLY_EN		0x20000000U
#define PM_CTRL_MAC_ASPM_CHK		0x40000000U
#define PM_CTRL_HOTRST			0x80000000U

E 6
E 5
D 3
/* MSTC: Master control register */
E 3
I 3
/* MSTC: Master control register, offset 0x1400, L1/L2 */
E 3
#define	MSTC_DID		0xff000000U	/* device id */
#define		MSTC_DID_SHIFT	24U
#define		MSTC_DID_MASK	0xffU
#define	MSTC_REV		0x00ff0000U	/* chip revision */
#define		MSTC_REV_SHIFT	16U
#define		MSTCL_REV_MASK	0xffU
I 3
D 5
#define	MSTC_LEDMODE		0x00000200U	/* L1E */
#define	MSTC_INT_CLR		0x00000040U	/* L1E */
#define	MSTC_ITIMER2		0x00000020U	/* L1E */
E 5
E 3
#define	MSTC_SINT		0x00000008U	/* software interrupt */
#define	MSTC_ITIMER		0x00000004U	/* enable itimer */
#define	MSTC_MTIMER		0x00000002U	/* enable mtimer */
#define	MSTC_SRST		0x00000001U	/* software reset */

I 5
/* l1e */
#define	MSTC_LEDMODE_1e		0x00000200U
#define	MSTC_INT_RD_CLR_1e	0x00000040U
#define	MSTC_ITIMER_RX_1e	0x00000020U
#define	MSTC_ITIMER_TX_1e	0x00000004U

/* l1c */
D 6
#define	MSTC_OTP_SEL		0x80000000U
#define	MSTC_DEV_ID		0x7f000000U
#define		MSTC_DEV_ID_SHIFT	24
#define	MSTC_REV_NUM		0x00ff0000U
#define		MSTC_REV_NUM_SHIFT	16
#define	MSTC_INT_RDCLR		0x00004000U
#define	MSTC_CLK_SWH_MODE	0x00002000U
#define	MSTC_CLK_SEL_DIS	0x00001000U
#define	MSTC_RX_ITIMER_EN	0x00000800U
#define	MSTC_TX_ITIMER_EN	0x00000400U
#define	MSTC_MANUAL_INT		0x00000200U
#define	MSTC_MTIMER_EN		0x00000100U
#define	MSTC_BERT_START		0x00000010U
#define	MSTC_TESTMODE		0x0000000cU	/* test mode */
#define		MSTC_TESTMODE_SHIFT	2
E 6
I 6
#define	MSTC_OTP_SEL_1c		0x80000000U
#define	MSTC_DEV_ID_1c		0x7f000000U
#define		MSTC_DEV_ID_SHIFT_1c	24
#define	MSTC_REV_NUM_1c		0x00ff0000U
#define		MSTC_REV_NUM_SHIFT_1c	16
#define	MSTC_INT_RDCLR_1c	0x00004000U
#define	MSTC_CLK_SWH_MODE_1c	0x00002000U
#define	MSTC_CLK_SEL_DIS_1c	0x00001000U
#define	MSTC_RX_ITIMER_EN_1c	0x00000800U
#define	MSTC_TX_ITIMER_EN_1c	0x00000400U
#define	MSTC_MANUAL_INT_1c	0x00000200U
#define	MSTC_MTIMER_EN_1c	0x00000100U
#define	MSTC_SA_TIMER_EN_1c	0x00000080U
#define	MSTC_OOB_DIS_OFF_1c	0x00000040U
#define	MSTC_BERT_START_1c	0x00000010U
#define	MSTC_TESTMODE_1c	0x0000000cU	/* test mode */
#define		MSTC_TESTMODE_SHIFT_1c	2
E 6

E 5
D 3
/* GPHYC: GPHY control register */
E 3
I 3
/* GPHYC: GPHY control register, offset 0x140c */
D 5
#define	GPHYC_PWDOWN_HW		0x4000	/* L1E */
#define	GPHYC_PHY_PLL_ON        0x2000	/* L1E */
#define	GPHYC_SEL_ANA_RST       0x1000	/* L1E */
#define	GPHYC_HIB_PULSE         0x0800	/* L1E */
#define	GPHYC_HIB_EN            0x0400	/* L1E */
#define	GPHYC_PCLK_SEL_DIS      0x0200	/* L1E */
#define	GPHYC_PHY_IDDQ_DIS      0x0100	/* L1E */
#define	GPHYC_PHY_IDDQ          0x0080	/* L1E */
#define	GPHYC_LPW_EXIT          0x0040	/* L1E */
#define	GPHYC_GATE_25M_EN       0x0020	/* L1E */
#define	GPHYC_BERT_START        0x0010	/* L1E */
#define	GPHYC_TESTMODE		0x000c	/* L1E */
#define		GPHYC_TESTMODE_SHIFT	2	/* L1E */
E 5
I 5
#define	GPHYC_PHY_PLL_BYPASS	0x8000	/* L1C */
#define	GPHYC_PWDOWN_HW		0x4000	/* L1E L1C */
#define	GPHYC_PHY_PLL_ON	0x2000	/* L1E L1C */
#define	GPHYC_SEL_ANA_RST	0x1000	/* L1E L1C */
#define	GPHYC_HIB_PULSE		0x0800	/* L1E L1C */
#define	GPHYC_HIB_EN		0x0400	/* L1E L1C */
#define	GPHYC_PCLK_SEL_DIS	0x0200	/* L1E */
#define	GPHYC_GIGA_DIS		0x0200	/* L1C */
#define	GPHYC_PHY_IDDQ_DIS	0x0100	/* L1E L1C */
#define	GPHYC_PHY_IDDQ		0x0080	/* L1E L1C */
#define	GPHYC_LPW_EXIT		0x0040	/* L1E L1C */
#define	GPHYC_GATE_25M_EN	0x0020	/* L1E L1C */
#define	GPHYC_BERT_START_1e	0x0010	/* L1E */
#define	GPHYC_REV_ANEG_1c	0x0010	/* L1C */
#define	GPHYC_TESTMODE_1e	0x000c	/* L1E */
#define		GPHYC_TESTMODE_SHIFT_1e	2	/* L1E */
#define	GPHYC_ANEG_NOW_1c	0x0008	/* L1C */
#define	GPHYC_LED_MODE_1c	0x0004	/* L1C */
E 5
#define	GPHYC_PIPEMOD		0x0002	/* L1E */
E 3
D 5
#define	GPHYC_ENABLE		0x0001
E 5
I 5
#define	GPHYC_RTL_MODE_1c		0x0002	/* L1C */
#define	GPHYC_ENABLE		0x0001	/* L2 L1E */
#define	GPHYC_EXT_RESET_1c	0x0001	/* L1C */
E 5

I 3
#define	GPHYC_DEFAULT_1e	\
	(GPHYC_PHY_PLL_ON | GPHYC_SEL_ANA_RST | \
	GPHYC_HIB_PULSE | GPHYC_HIB_EN)

I 5
#define GPHYC_DEFAULT_1c	\
	(GPHYC_SEL_ANA_RST | GPHYC_HIB_PULSE | GPHYC_HIB_EN)
E 5

I 5
#define GPHYC_PW_WOL_DIS_1c \
	(GPHYC_SEL_ANA_RST | GPHYC_HIB_PULSE |	\
	GPHYC_HIB_EN | GPHYC_PWDOWN_HW | GPHYC_PHY_IDDQ)


E 5
E 3
/* IDLE: idle status register */
#define	IDLE_ISM		0x00000080U	/* coaliscq */
#define	IDLE_SM			0x00000040U	/* statistics */
#define	IDLE_DMAW		0x00000020U	/* dma write */
#define	IDLE_DMAR		0x00000010U	/* dma read */
#define	IDLE_TXQ		0x00000008U	/* transmit queue */
#define	IDLE_RXQ		0x00000004U	/* recive queue */
#define	IDLE_TXMAC		0x00000002U	/* transmit side of mac */
#define	IDLE_RXMAC		0x00000001U	/* receive side of mac */

I 6
#define	IDLE_ALL	\
	(IDLE_ISM | IDLE_SM | IDLE_DMAW | IDLE_DMAR |	\
	IDLE_TXQ | IDLE_RXQ | IDLE_TXMAC | IDLE_RXMAC)

E 6
#define	IDLE_BITS	\
	"\020"	\
	"\010ISM"	\
	"\007SM"	\
	"\006DMAW"	\
	"\005DMAR"	\
	"\004TXQ"	\
	"\003RXQ"	\
	"\002TXMAC"

/* MII control Register */
#define	MIIC_BUSY		0x08000000U	/* MII opration in progress */
#define	MIIC_CLK		0x07000000U
#define		MIIC_CLK_SHIFT	24
#define		MIIC_CLK_4	(0U << MIIC_CLK_SHIFT)
#define		MIIC_CLK_6	(2U << MIIC_CLK_SHIFT)
#define		MIIC_CLK_8	(3U << MIIC_CLK_SHIFT)
#define		MIIC_CLK_10	(4U << MIIC_CLK_SHIFT)
#define		MIIC_CLK_14	(5U << MIIC_CLK_SHIFT)
#define		MIIC_CLK_20	(6U << MIIC_CLK_SHIFT)
#define		MIIC_CLK_28	(7U << MIIC_CLK_SHIFT)
#define	MIIC_GO			0x00800000U
#define	MIIC_SUPR		0x00400000U	/* supress preamble */
#define	MIIC_READ		0x00200000U
#define	MIIC_ADDR		0x001f0000U
#define		MIIC_ADDR_SHIFT	16
#define	MIIC_DATA		0x0000ffffU

I 3
/* PHY STATUS register, offset 0x1418 */
#define	PHYSTAT_100M	0x20000

I 6
/* SERDES LOCK */
#define	SERDES_MAC_CLK_SLOWDOWN	0x00020000U
#define	SERDES_PYH_CLK_SLOWDOWN	0x00040000U

E 6
E 3
/* MACCTL: MAC Control Register */
I 3
D 5
#define	MACCTL_HALFLEFTBUF	0xf0000000U
E 5
I 5
#define	MACCTL_HALFLEFTBUF	0xf0000000U	/* 1/1E/2/2E */
E 5
#define		MACCTL_HALFLEFTBUF_SHIFT	28
I 5
#define	MACCTL_SPEED_MODE_SW	0x40000000U	/* 1D/2C_B2 */
#define	MACCTL_HASH_ALG_CRC32	0x20000000U	/* 1D/2C_B2 */
#define	MACCTL_SINGLE_PAUSE	0x10000000U	/* 1C or later */
E 5
E 3
#define	MACCTL_DEBUG		0x08000000U
#define	MACCTL_AB		0x04000000U	/* accept broadcast */
#define	MACCTL_AAM		0x02000000U	/* accept all multicast */
#define	MACCTL_RCKSUM		0x01000000U	/* enable rx checksum */
#define	MACCTL_TXJUMBO		0x00800000U	/* enable tx jumbo packets */
#define	MACCTL_DBG_TX_BKPRESURE	0x00400000U	/* X */
#define	MACCTL_SPEED		0x00300000U	/* media speed */
#define		MACCTL_SPEED_SHIFT	20
#define		MACCTL_SPEED_1000	(2U << MACCTL_SPEED_SHIFT)
#define		MACCTL_SPEED_10_100	(1U << MACCTL_SPEED_SHIFT)
#define	MACCTL_TX_SIMURST	0x00080000U	/* X */
#define	MACCTL_SRST_TX		0x00040000U	/* X */
#define	MACCTL_SCNT		0x00020000U	/* X */
#define	MACCTL_TXPAUSE		0x00010000U	/* enable transmit pause */
#define	MACCTL_PROMISC		0x00008000U	/* promiscious mode */
#define	MACCTL_RXVTAG		0x00004000U	/* extract rx vtag */
#define	MACCTL_PRMLEN		0x00003c00U	/* preamble length */
#define		MACCTL_PRMLEN_SHIFT	10
#define	MACCTL_JUMBO		0x00000200U	/* allow jumbo packets */
#define	MACCTL_LENCHK		0x00000100U	/* X */
#define	MACCTL_AUTOPAD		0x00000080U	/* enable tx auto padding */
#define	MACCTL_CRCEN		0x00000040U	/* enable crc */
#define	MACCTL_FD		0x00000020U	/* full duplex */
#define	MACCTL_LBK		0x00000010U	/* loopback */
#define	MACCTL_RXFC		0x00000008U	/* enable rx flow control */
#define	MACCTL_TXFC		0x00000004U	/* enable tx flow control */
#define	MACCTL_RX		0x00000002U	/* enable rx */
#define	MACCTL_TX		0x00000001U	/* enable tx */

#define	MACCTL_BITS	\
	"\020"	\
I 5
	"\035SINGLE_PAUSE"	\
E 5
	"\034DEBUG"	\
	"\033AB"	\
	"\032AAM"	\
	"\031RXCKSUM"	\
	"\030TX_JUMBO"	\
	"\027DBG_TX_BKPRESURE"	\
	"\024TX_SIMURST"	\
	"\023SRST_TX"	\
	"\022SCNT"	\
	"\021TXPAUSE"	\
	"\020PROMISC"	\
	"\017RXVTAG"	\
	"\012JUMBO"	\
	"\011LENCHK"	\
	"\010AUTOPAD"	\
	"\007CRCEN"	\
	"\006FD"	\
	"\005LBK"	\
	"\004RXFC"	\
	"\003TXFC"	\
	"\002RX"	\
	"\001TX"

/* GAP: inter-frame/inter-packet gap control register */
#define	GAPC_IPGR2		0x7f000000U
#define		GAPC_IPGR2_SHIFT	24
#define	GAPC_IPGR1		0x007f0000U
#define		GAPC_IPGR1_SHIFT	16
#define	GAPC_MIFG		0x0000ff00U
#define		GAPC_MIFG_SHIFT		8
#define	GAPC_IPGT		0x0000007fU
#define		GAPC_IPGT_SHIFT		0

#define	GAPC_STD		0x60405060U	/* standard configuration */

/* HDCTL: half duplex control register */
#define	HDCTRL_JAMIPG		0x0f000000U
#define		HDCTL_JAMIPG_SHIFT	24
D 3
#define	HDCTL_ABEBE		0x00080000U
E 3
I 3
#define	HDCTL_ABEBT		0x00f00000U
E 3
#define		HDCTL_ABEBT_SHIFT	20
I 3
#define	HDCTL_ABEBE		0x00080000U
E 3
#define	HDCTL_NO_BACK_P		0x00040000U
#define	HDCTL_NO_BACK_C		0x00020000U
#define	HDCTL_EXC_DEF		0x00010000U
#define	HDCTL_RETRY		0x0000f000U
#define		HDCTL_RETRY_SHIFT	12
#define	HDCTL_LCOL		0x000003ffU
#define		HDCTL_LCOL_SHIFT	0

#define	HDCTL_STD		0x07a1f037U	/* standard configuration */

I 2
/* WOL control */
D 3
#define	WOLCTL_PAT_EN		0x00000001
#define	WOLCTL_PAT_PME_EN	0x00000002
#define	WOLCTL_MGC_EN		0x00000004
#define	WOLCTL_MGC_PME_EN	0x00000008
#define	WOLCTL_LCHG_EN		0x00000010
#define	WOLCTL_LCHG_PME_EN	0x00000020
#define	WOLCTL_PAT_ST		0x00000100
#define	WOLCTL_MGC_ST		0x00000200
#define	WOLCTL_LCHN_ST		0x00000400
#define	WOLCTL_CLK_EN		0x00008000
#define	WOLCTL_PAT0_EN		0x00010000
#define	WOLCTL_PAT1_EN		0x00020000
#define	WOLCTL_PAT2_EN		0x00040000
#define	WOLCTL_PAT3_EN		0x00080000
#define	WOLCTL_PAT4_EN		0x00100000
#define	WOLCTL_PAT5_EN		0x00200000
#define	WOLCTL_PAT6_EN		0x00400000
E 3
I 3
D 5
#define	WOLCTL_PAT_EN		0x00000001	/* L1 L2 */
#define	WOLCTL_PAT_PME_EN	0x00000002	/* L1 L2 */
#define	WOLCTL_MGC_EN		0x00000004	/* L1 L2 */
#define	WOLCTL_MGC_PME_EN	0x00000008	/* L1 L2 */
#define	WOLCTL_LCHG_EN		0x00000010	/* L1 L2 */
#define	WOLCTL_LCHG_PME_EN	0x00000020	/* L1 L2 */
#define	WOLCTL_PAT_ST		0x00000100	/* L1 L2 */
#define	WOLCTL_MGC_ST		0x00000200	/* L1 L2 */
#define	WOLCTL_LCHN_ST		0x00000400	/* L1 L2 */
#define	WOLCTL_CLK_EN		0x00008000	/* L1 L2 */
#define	WOLCTL_PAT0_EN		0x00010000	/* L1 L2 */
#define	WOLCTL_PAT1_EN		0x00020000	/* L1 L2 */
#define	WOLCTL_PAT2_EN		0x00040000	/* L1 L2 */
#define	WOLCTL_PAT3_EN		0x00080000	/* L1 L2 */
#define	WOLCTL_PAT4_EN		0x00100000	/* L1 L2 */
#define	WOLCTL_PAT5_EN		0x00200000	/* L1 */
#define	WOLCTL_PAT6_EN		0x00400000	/* L1 */
E 5
I 5
#define	WOLCTL_PAT4_MATCH	0x10000000U	/* L2 */
#define	WOLCTL_PAT3_MATCH	0x08000000U	/* L2 */
#define	WOLCTL_PAT2_MATCH	0x04000000U	/* L2 */
#define	WOLCTL_PAT1_MATCH	0x02000000U	/* L2 */
#define	WOLCTL_PAT0_MATCH	0x01000000U	/* L2 */
E 5
E 3

I 3
D 5
#define	WOLCTL_PAT0_MATCH	0x01000000	/* L2 */
#define	WOLCTL_PAT1_MATCH	0x02000000	/* L2 */
#define	WOLCTL_PAT2_MATCH	0x04000000	/* L2 */
#define	WOLCTL_PAT3_MATCH	0x08000000	/* L2 */
#define	WOLCTL_PAT4_MATCH	0x10000000	/* L2 */
E 5
I 5
#define	WOLCTL_PAT6_EN		0x00400000U	/* L1 */
#define	WOLCTL_PAT5_EN		0x00200000U	/* L1 */
#define	WOLCTL_PAT4_EN		0x00100000U	/* L1 L2 */
#define	WOLCTL_PAT3_EN		0x00080000U	/* L1 L2 */
#define	WOLCTL_PAT2_EN		0x00040000U	/* L1 L2 */
#define	WOLCTL_PAT1_EN		0x00020000U	/* L1 L2 */
#define	WOLCTL_PAT0_EN		0x00010000U	/* L1 L2 */
#define	WOLCTL_CLK_EN		0x00008000U	/* L1 L2 */
#define	WOLCTL_LCHN_ST		0x00000400U	/* L1 L2 */
#define	WOLCTL_MGC_ST		0x00000200U	/* L1 L2 */
#define	WOLCTL_PAT_ST		0x00000100U	/* L1 L2 */
#define	WOLCTL_LCHG_PME_EN	0x00000020U	/* L1 L2 */
#define	WOLCTL_LCHG_EN		0x00000010U	/* L1 L2 */
#define	WOLCTL_MGC_PME_EN	0x00000008U	/* L1 L2 */
#define	WOLCTL_MGC_EN		0x00000004U	/* L1 L2 */
#define	WOLCTL_PAT_PME_EN	0x00000002U	/* L1 L2 */
#define	WOLCTL_PAT_EN		0x00000001U	/* L1 L2 */
E 5

I 5

E 5
E 3
/* WOL pattern */
D 5
#define	WOLPAT0_PAT3		0x7f000000
E 5
I 5
#define	WOLPAT0_PAT3		0x7f000000U
E 5
#define		WOLPAT0_PAT3_SHIFT	24
D 5
#define	WOLPAT0_PAT2		0x007f0000
E 5
I 5
#define	WOLPAT0_PAT2		0x007f0000U
E 5
#define		WOLPAT0_PAT2_SHIFT	16
D 5
#define	WOLPAT0_PAT1		0x00007f00
E 5
I 5
#define	WOLPAT0_PAT1		0x00007f00U
E 5
#define		WOLPAT0_PAT1_SHIFT	8
D 5
#define	WOLPAT0_PAT0		0x0000007f
E 5
I 5
#define	WOLPAT0_PAT0		0x0000007fU
E 5
#define		WOLPAT0_PAT0_SHIFT	0

D 5
#define	WOLPAT1_PAT6		0x007f0000
E 5
I 5
#define	WOLPAT1_PAT6		0x007f0000U
E 5
#define		WOLPAT1_PAT6_SHIFT	16
D 5
#define	WOLPAT1_PAT5		0x00007f00
E 5
I 5
#define	WOLPAT1_PAT5		0x00007f00U
E 5
#define		WOLPAT1_PAT5_SHIFT	8
D 5
#define	WOLPAT1_PAT4		0x0000007f
E 5
I 5
#define	WOLPAT1_PAT4		0x0000007fU
E 5
#define		WOLPAT1_PAT4_SHIFT	0

E 2
/* Internal SRAM Partition Register */
#define	SRAM_PATH_ADDR		0x0fff0000U	/* X */
#define		SRAM_PATH_ADDR_SHIFT	16	/* X */
#define	SRAM_TCPH_ADDR		0x00000fffU	/* X */
#define		SRAM_TCPH_ADDR_SHIFT	0	/* X */

/* TXQCTL: TxQ control register */
#define	TXQCTL_TXF_BURST_NUM	0xffff0000U
#define		TXQCTL_TXF_BURST_NUM_SHIFT	16
#define	TXQCTL_TBD_FETCH_TH	0x00003f00U
#define		TXQCTL_TBD_FETCH_TH_SHIFT	8
#define	TXQCTL_ENH_MODE		0x00000040U
#define	TXQCTL_EN		0x00000020U
#define	TXQCTL_TBD_BURST_NUM	0x0000001fU
#define		TXQCTL_TBD_BURST_NUM_SHIFT	0

I 5
/* L1C */
#define	TXQCTL_LS_8023_EN	0x00000080U
#define	TXQCTL_IP_OPTION_EN	0x00000010U
#define	TXQCTL_NUM_TPD_BURST	0x0000000fU
#define		TXQCTL_NUM_TPD_BURST_SHIFT	0

E 5
/* TX jumbo packet configuration */
#define	TXJCFG_TBDIPG		0x001f0000U
#define		TXJCFG_TBDIPG_SHIFT	16
#define	TXJCFG_THRESH	0x000007ffU
#define		TXJCFG_THRESH_SHIFT	0

/* RXQCTL: RxQ control register */
#define	RXQCTL_EN		0x80000000U
#define	RXQCTL_CUT_THRU_EN	0x40000000U
#define	RXQCTL_RBD_PREF_MIN_IPG	0x001f0000U
#define		RXQCTL_RBD_PREF_MIN_IPG_SHIFT	16
#define	RXQCTL_RSD_BURST_THRESH	0x0000ff00U
#define		RXQCTL_RSD_BURST_THRESH_SHIFT	8
#define	RXQCTL_RBD_BURST_NUM	0x000000ffU
#define		RXQCTL_RBD_BURST_NUM_SHIFT	0

I 3
/* for L1E */
#define	RXQCTL_HASH_EN		0x20000000U
#define	RXQCTL_NIP_QUEUE_SEL_TBL 0x10000000U
#define	RXQCTL_RSSMODE		0x0c000000U
#define		RXQCTL_RSSMODE_SHIFT	26U
#define		RXQCTL_RSSMODE_NONE	(0U << RXQCTL_RSS_MODE_SHIFT)
#define		RXQCTL_RSSMODE_SQSINT	(1U << RXQCTL_RSS_MODE_SHIFT)
#define		RXQCTL_RSSMODE_MQUESINT	(2U << RXQCTL_RSS_MODE_SHIFT)
#define		RXQCTL_RSSMODE_MQUEMINT	(3U << RXQCTL_RSS_MODE_SHIFT)
#define	RXQCTL_HTYPE_IPV6_TCP	0x00080000
#define	RXQCTL_HTYPE_IPV6	0x00040000
#define	RXQCTL_HTYPE_IPV4_TCP	0x00020000
#define	RXQCTL_HTYPE_IPV4	0x00010000 
#define	RXQCTL_HASH_TLEN	0x0000ff00
#define		RXQCTL_HASH_TLEN_SHIFT	8U
#define	RXQCTL_IPV6_CKSUM_EN	0x00000080
#define	RXQCTL_Q3_EN		0x00000040
#define	RXQCTL_Q2_EN		0x00000020
#define	RXQCTL_Q1_EN		0x00000010
#define	RXQCTL_PBA_ALIGN	0x00000003
#define		RXQCTL_PBA_ALIGN_32		0
#define		RXQCTL_PBA_ALIGN_64		1
#define		RXQCTL_PBA_ALIGN_128		2
#define		RXQCTL_PBA_ALIGN_256		3

I 5
/* for L1C */
#define	RXQCTL_RFD_BURST_NUM	0x03f00000U
#define		RXQCTL_RFD_BURST_NUM_SHIFT	20
#define	RXQCTL_ASPM_LMT	0x00000003
#define		RXQCTL_ASPM_LMT_NO		0
#define		RXQCTL_ASPM_LMT_1M		1
#define		RXQCTL_ASPM_LMT_10M		2
#define		RXQCTL_ASPM_LMT_100M		3

E 5
E 3
/* RX jumbo packet configuration */
D 3
#define	RXJCFG_RSDTIMER		0xffff0000U
#define		RXJCFG_RSDTIMER_SHIFT	16
E 3
I 3
#define	RXJCFG_RSDTIMER		0xffff0000U	/* L1 */
#define		RXJCFG_RSDTIMER_SHIFT	16	/* L1 */
E 3
#define	RXJCFG_LKAH		0x00007800U
#define		RXJCFG_LKAH_SHIFT	11
#define	RXJCFG_THRESH		0x000007ffU
#define		RXJCFG_THRESH_SHIFT	0

/* RBD/RxFIFO flow control register */
#define	RXFFC_HIWAT		0x0fff0000U
#define		RXFFC_HIWAT_SHIFT	16
#define	RXFFC_LOWAT		0x00000fffU

/* RSD flow control register */
#define	RSDFC_LOWAT		0x0fff0000U
#define		RSDFC_LOWAT_SHIFT	16
#define	RSDFC_HIWAT		0x00000fffU

/* DMAC: dma control register */
I 5
#define	DMAC_SMB_NOW_1c		0x80000000U	/* L1C */
#define	DMAC_SMB_DIS_1c		0x01000000U	/* L1C */
#define	DMAC_CMB_NOW_1c		0x00400000U	/* L1C */

E 5
D 3
#define	DMAC_DMAW_EN		0x00000800U
#define	DMAC_DMAR_EN		0x00000400U
E 3
I 3
#define	DMAC_RXCMB_1e		0x00200000U	/* L1E */
#define	DMAC_TXCMB_1e		0x00100000U	/* L1E */
D 5
#define	DMAC_DMAW_DLY_CNT_1e	0x000f0000U	/* L1E */
#define		DMAC_DMAW_DLY_CNT_SHIFT	16U	/* L1E */
#define	DMAC_DMAR_DLY_CNT_1e	0x0000f800U	/* L1E */
E 5
I 5
#define	DMAC_SMB_EN_1c		0x00200000U	/* L1C */
#define	DMAC_CMB_EN_1c		0x00100000U	/* L1C */

D 6
#define	DMAC_DMAW_DLY_CNT	0x000f0000U	/* L1E, L1C */
#define		DMAC_DMAW_DLY_CNT_SHIFT	16U	/* L1E, L1C */
E 6
I 6
#define	DMAC_DMAW_DLY_CNT	0x000f0000U	/* L1E L1C */
#define		DMAC_DMAW_DLY_CNT_SHIFT	16U	/* L1E L1C */
E 6
#define	DMAC_DMAR_DLY_CNT	0x0000f800U	/* L1E */
E 5
#define		DMAC_DMAR_DLY_CNT_SHIFT	11U	/* L1E */
#define	DMAC_DMAW_EN_1		0x00000800U	/* L1 */
#define	DMAC_DMAR_EN_1		0x00000400U	/* L1 */
D 6
#define	DMAC_DMAR_REQ_PRI_1e	0x00000400U	/* L1E */
I 5
#define	DMAC_DMAR_REQ_PRI_1c	0x00000400U	/* L1C */
E 6
I 6
#define	DMAC_DMAR_REQ_PRI	0x00000400U	/* L1E L1C */
E 6
E 5
E 3
#define	DMAC_DMAW_MAXDMA	0x00000380U
I 2
#define		MAXDMA_128	0U
#define		MAXDMA_256	1U
#define		MAXDMA_512	2U
#define		MAXDMA_1024	3U
#define		MAXDMA_2048	4U
#define		MAXDMA_4096	5U
E 2
#define		DMAC_DMAW_MAXDMA_SHIFT	7
D 2
#define		DMAC_DMAW_MAXDMA_128	(0U << DMAC_DMAW_MAXDMA_SHIFT)
#define		DMAC_DMAW_MAXDMA_256	(1U << DMAC_DMAW_MAXDMA_SHIFT)
#define		DMAC_DMAW_MAXDMA_512	(2U << DMAC_DMAW_MAXDMA_SHIFT)
#define		DMAC_DMAW_MAXDMA_1024	(3U << DMAC_DMAW_MAXDMA_SHIFT)
#define		DMAC_DMAW_MAXDMA_2048	(4U << DMAC_DMAW_MAXDMA_SHIFT)
#define		DMAC_DMAW_MAXDMA_4096	(5U << DMAC_DMAW_MAXDMA_SHIFT)
E 2
I 2
#define		DMAC_DMAW_MAXDMA_128	(MAXDMA_128 << DMAC_DMAW_MAXDMA_SHIFT)
#define		DMAC_DMAW_MAXDMA_256	(MAXDMA_256 << DMAC_DMAW_MAXDMA_SHIFT)
#define		DMAC_DMAW_MAXDMA_512	(MAXDMA_512 << DMAC_DMAW_MAXDMA_SHIFT)
#define		DMAC_DMAW_MAXDMA_1024	(MAXDMA_1024 << DMAC_DMAW_MAXDMA_SHIFT)
#define		DMAC_DMAW_MAXDMA_2048	(MAXDMA_2048 << DMAC_DMAW_MAXDMA_SHIFT)
#define		DMAC_DMAW_MAXDMA_4096	(MAXDMA_4096 << DMAC_DMAW_MAXDMA_SHIFT)
E 2
#define	DMAC_DMAR_MAXDMA	0x00000070U
#define		DMAC_DMAR_MAXDMA_SHIFT	4
D 2
#define		DMAC_DMAR_MAXDMA_128	(0U << DMAC_DMAR_MAXDMA_SHIFT)
#define		DMAC_DMAR_MAXDMA_256	(1U << DMAC_DMAR_MAXDMA_SHIFT)
#define		DMAC_DMAR_MAXDMA_512	(2U << DMAC_DMAR_MAXDMA_SHIFT)
#define		DMAC_DMAR_MAXDMA_1024	(3U << DMAC_DMAR_MAXDMA_SHIFT)
#define		DMAC_DMAR_MAXDMA_2048	(4U << DMAC_DMAR_MAXDMA_SHIFT)
#define		DMAC_DMAR_MAXDMA_4096	(5U << DMAC_DMAR_MAXDMA_SHIFT)
E 2
I 2
#define		DMAC_DMAR_MAXDMA_128	(MAXDMA_128 << DMAC_DMAR_MAXDMA_SHIFT)
#define		DMAC_DMAR_MAXDMA_256	(MAXDMA_256 << DMAC_DMAR_MAXDMA_SHIFT)
#define		DMAC_DMAR_MAXDMA_512	(MAXDMA_512 << DMAC_DMAR_MAXDMA_SHIFT)
#define		DMAC_DMAR_MAXDMA_1024	(MAXDMA_1924 << DMAC_DMAR_MAXDMA_SHIFT)
#define		DMAC_DMAR_MAXDMA_2048	(MAXDMA_2048 << DMAC_DMAR_MAXDMA_SHIFT)
#define		DMAC_DMAR_MAXDMA_4096	(MAXDMA_4096 << DMAC_DMAR_MAXDMA_SHIFT)
E 2
#define	DMAC_RCB_128		0x00000008U	/* 0:64, 1:128 */
#define	DMAC_DMAR_OUT_ORDER	0x00000004U
#define	DMAC_DMAR_ENH_ORDER	0x00000002U
#define	DMAC_DMAR_IN_ORDER	0x00000001U

/* ISMCTL: interrupt status message and statistics message */
#define	ISMCTL_SM_EN		0x00000008U
#define	ISMCTL_ISM_EN		0x00000004U
#define	ISMCTL_UPDATE_SM	0x00000002U
#define	ISMCTL_UPDATE_ISM	0x00000001U

/* ISMTHRESH: ISM DMA Write Threshold Register */
#define	ISMTHRESH_TBD		0x07ff0000U
#define		ISMTHRESH_TBD_SHIFT	16
#define	ISMTHRESH_RSD		0x000007ffU

/* ISMDELAY */
#define	ISMDELAY_TBD		0xffff0000U	/* in 2uS */
#define		ISMDELAY_TBD_SHIFT		16
#define	ISMDELAY_RSD		0x0000ffffU	/* in 2uS */

/* MBOX: mailbox register */
#define	MBOX_TBD_TAIL		0xffc00000U
#define		MBOX_TBD_TAIL_SHIFT	22
#define	MBOX_RSD_HEAD		0x003ff800U
#define		MBOX_RSD_HEAD_SHIFT	11
#define	MBOX_RBD_TAIL		0x000007ffU
#define		MBOX_RBD_TAIL_SHIFT	0

/* ISR: Interrupt Status Register, offset 0x1600 */
D 3
#define	ISR_DIS_INT		0x80000000U	/* X */
#define	ISR_DIS_DMA		0x40000000U	/* X */
#define	ISR_DIS_SM		0x20000000U	/* X */
#define	ISR_PCIE_ERR		0x10000000U
#define	ISR_CERR		0x08000000U
#define	ISR_NFER		0x04000000U
#define	ISR_FER			0x02000000U
#define	ISR_UR			0x01000000U
#define	ISR_MAC_TX		0x00800000U	/* X */
#define	ISR_MAC_RX		0x00400000U	/* X */
#define	ISR_ISM_TX		0x00200000U
#define	ISR_ISM_RX		0x00100000U
#define	ISR_RX_DMA		0x00080000U	/* X */
#define	ISR_TX_DMA		0x00040000U	/* X */
#define	ISR_TX_PKT		0x00020000U	/* X */
#define	ISR_RX_PKT		0x00010000U	/* X */
#define	ISR_GPHY		0x00001000U	/* X */
#define	ISR_DMAW_TO_RST		0x00000800U	/* X */
#define	ISR_DMAR_TO_RST		0x00000400U	/* X */
#define	ISR_HOST_RSD_OVF	0x00000200U	/* X */
#define	ISR_HOST_RBD_UNRUN	0x00000100U	/* X */
#define	ISR_LINK		0x00000080U	/* X */
#define	ISR_TXF_UNRUN		0x00000040U	/* X */
#define	ISR_RSD_OVF		0x00000020U	/* X */
#define	ISR_RBD_UNRUN		0x00000010U	/* X */
#define	ISR_RXF_OVF		0x00000008U	/* X */
#define	ISR_MANUAL		0x00000004U	/* X */
#define	ISR_TIMER		0x00000002U	/* X */
#define	ISR_SM			0x00000001U
E 3
I 3
/* ISR bits for L1 chipset */
#define	ISR_DIS_INT_1		0x80000000U	/* X */
#define	ISR_DIS_DMA_1		0x40000000U	/* X */
#define	ISR_DIS_SM_1		0x20000000U	/* X */
#define	ISR_PCIE_ERR_1		0x10000000U
#define	ISR_CERR_1		0x08000000U
#define	ISR_NFER_1		0x04000000U
D 4
#define	ISR_FER_1			0x02000000U
#define	ISR_UR_1			0x01000000U
E 4
I 4
#define	ISR_FER_1		0x02000000U
#define	ISR_UR_1		0x01000000U
E 4
#define	ISR_MAC_TX_1		0x00800000U	/* X */
#define	ISR_MAC_RX_1		0x00400000U	/* X */
#define	ISR_ISM_TX_1		0x00200000U
#define	ISR_ISM_RX_1		0x00100000U
#define	ISR_RX_DMA_1		0x00080000U	/* X */
#define	ISR_TX_DMA_1		0x00040000U	/* X */
#define	ISR_TX_PKT_1		0x00020000U	/* X */
#define	ISR_RX_PKT_1		0x00010000U	/* X */
D 4
#define	ISR_GPHY_LOWPWR_1		0x00004000U	/* X */
E 4
I 4
#define	ISR_GPHY_LOWPWR_1	0x00004000U	/* X */
E 4
#define	ISR_TX_CREGIT_1		0x00002000U	/* X */
#define	ISR_GPHY_1		0x00001000U	/* X */
D 4
#define	ISR_DMAW_TO_RST_1		0x00000800U	/* X */
#define	ISR_DMAR_TO_RST_1		0x00000400U	/* X */
E 4
I 4
#define	ISR_DMAW_TO_RST_1	0x00000800U	/* X */
#define	ISR_DMAR_TO_RST_1	0x00000400U	/* X */
E 4
#define	ISR_HOST_RSD_OVF_1	0x00000200U	/* X */
#define	ISR_HOST_RBD_UNRUN_1	0x00000100U	/* X */
#define	ISR_LINK_1		0x00000080U	/* X */
#define	ISR_TXF_UNRUN_1		0x00000040U	/* X */
#define	ISR_RSD_OVF_1		0x00000020U	/* X */
#define	ISR_RBD_UNRUN_1		0x00000010U	/* X */
#define	ISR_RXF_OVF_1		0x00000008U	/* X */
#define	ISR_MANUAL_1		0x00000004U	/* X */
#define	ISR_TIMER_1		0x00000002U	/* X */
D 4
#define	ISR_SM_1			0x00000001U
E 4
I 4
#define	ISR_SM_1		0x00000001U
E 4
E 3

D 3
#define	ISR_BITS	\
E 3
I 3
#define	ISR_BITS_1	\
E 3
	"\020"	\
	"\040DIS_INT"	\
	"\037DIS_DMA"	\
	"\036DIS_SM"	\
	"\035PCIE_ERR"	\
	"\034CERR"	\
	"\033NFERR"	\
	"\032FERR"	\
	"\031UR"	\
	"\030MAC_TX"	\
	"\027MAC_RX"	\
	"\026ISM_TX"	\
	"\025ISM_RX"	\
	"\024RX_DMA"	\
	"\023TX_DMA"	\
	"\022TX_PKT"	\
	"\021RX_PKT"	\
	"\015GPHY"	\
	"\014DMAW_TO_RST"	\
	"\013DMAR_TO_RST"	\
	"\012HOST_RSD_OV"	\
	"\011HOST_RBD_UNRUN"	\
	"\010LINK"	\
	"\007TXF_UNRUN"	\
	"\006RSD_OV"	\
	"\005RBD_UNRUN"	\
	"\004RXF_OV"	\
	"\003MANUAL"	\
	"\002TIMER"	\
	"\001SM"

I 3
/* ISR bits in L1E chipset */
#define	ISR_DIS_INT_1e		0x80000000U
#define	ISR_PCIE_ERR_1e		0x10000000U
#define	ISR_CERR_1e		0x08000000U
#define	ISR_NFER_1e		0x04000000U
#define	ISR_FER_1e		0x02000000U
#define	ISR_UR_1e		0x01000000U
#define	ISR_MAC_TX_1e		0x00800000U
#define	ISR_MAC_RX_1e		0x00400000U
#define	ISR_RX_PKT3_1e		0x00200000U
#define	ISR_RX_PKT2_1e		0x00100000U
#define	ISR_RX_PKT1_1e		0x00080000U
#define	ISR_TX_DMA_1e		0x00040000U
#define	ISR_TX_PKT_1e		0x00020000U
#define	ISR_RX_PKT_1e		0x00010000U
#define	ISR_GPHY_LOWPWR_1e	0x00004000U
D 4
#define	ISR_TX_CREGIT_1e	0x00002000U
E 4
I 4
#define	ISR_TX_CREDIT_1e	0x00002000U
E 4
#define	ISR_GPHY_1e		0x00001000U
#define	ISR_DMAW_TO_RST_1e	0x00000800U
#define	ISR_DMAR_TO_RST_1e	0x00000400U
#define	ISR_RX0_PAGE_FULL_1e	0x00000200U
#define	ISR_TXF_UNRUN_1e	0x00000100U
#define	ISR_RXF3_OV_1e		0x00000080U
#define	ISR_RXF2_OV_1e		0x00000040U
#define	ISR_RXF1_OV_1e		0x00000020U
#define	ISR_RXF0_OV_1e		0x00000010U
#define	ISR_RXF_OVF_1e		0x00000008U
#define	ISR_MANUAL_1e		0x00000004U
#define	ISR_TIMER_1e		0x00000002U
#define	ISR_SM_1e		0x00000001U

#define	ISR_BITS_1e	\
	"\020"	\
	"\040DIS_INT"	\
	"\035PCIE_ERR"	\
	"\034CERR"	\
	"\033NFERR"	\
	"\032FERR"	\
	"\031UR"	\
	"\030MAC_TX"	\
	"\027MAC_RX"	\
	"\026RX_PKT3"	\
	"\025RX_PKT2"	\
	"\024RX_PKT1"	\
	"\023TX_DMA"	\
	"\022TX_PKT"	\
	"\021RX_PKT"	\
I 4
	"\017GPHY_LPW"	\
	"\016TX_CREDIT"	\
E 4
	"\015GPHY"	\
	"\014DMAW_TO_RST"	\
	"\013DMAR_TO_RST"	\
	"\012RX0_PAGE_FULL"	\
	"\011TXF_UNRUN"	\
	"\010RX3_OV"	\
	"\007RX2_OV"	\
	"\006RX1_OV"	\
	"\005RX0_OV"	\
	"\004RXF_OVF"	\
	"\003MANUAL"	\
	"\002TIMER"	\
	"\001SM"

/* ISR bits for L2 chipset */
#define	ISR_DIS_INT_2		0x80000000U
#define	ISR_PCIE_ERR_2		0x10000000U
#define	ISR_CERR_2		0x08000000U
#define	ISR_NFER_2		0x04000000U
#define	ISR_FER_2		0x02000000U
#define	ISR_UR_2		0x01000000U
#define	ISR_TX_EARLY_2		0x00040000U
#define	ISR_RX_UPDATE_2		0x00020000U
#define	ISR_TX_UPDATE_2		0x00010000U
D 4
#define	ISR_GPHY_2		0x00000800U
E 4
I 4
#define	ISR_PHY_2		0x00000800U
E 4
#define	ISR_DMAW_TO_RST_2	0x00000400U
#define	ISR_DMAR_TO_RST_2	0x00000200U
#define	ISR_RXD_OV_2		0x00000100U
#define	ISR_TXD_UR_2		0x00000080U
#define	ISR_LINKCHG_2		0x00000040U
#define	ISR_RXS_OV_2		0x00000020U
#define	ISR_TXS_OV_2		0x00000010U
#define	ISR_TXF_UR_2		0x00000008U
#define	ISR_RXF_OVF_2		0x00000004U
#define	ISR_MANUAL_2		0x00000002U
#define	ISR_TIMER_2		0x00000001U

#define	ISR_BITS_2	\
	"\020"	\
	"\040DIS_INT"	\
	"\034PCIE_ERR"	\
	"\033CERR"	\
	"\032NFER"	\
	"\032FER"	\
	"\031UR"	\
	"\023TX_EARLY"	\
	"\022RX_UPDATE"	\
	"\021TX_UPDATE"	\
D 4
	"\014GPHY"	\
E 4
I 4
	"\014PHY"	\
E 4
	"\013DMAW_TO_RST"	\
	"\012DMAR_TO_RST"	\
	"\011RXD_OV"	\
	"\010TXD_UR"	\
	"\007LINKCHG"	\
	"\006RXS_OV"	\
	"\005TXS_OV"	\
	"\004TXF_UR"	\
	"\003RXF_OVF"	\
	"\002MANUAL"	\
	"\001TIMER"


I 5
#define	ISR_DIS_INT_1c		0x80000000U	/* X */
#define	ISR_PHY_LINKDOWN_1c	0x04000000U	/* X */
#define	ISR_CERR_1c		0x02000000U	/* X */
#define	ISR_NFER_1c		0x01000000U	/* X */
#define	ISR_FER_1c		0x00800000U	/* X */
#define	ISR_UR_1c		0x00400000U	/* X */
#define	ISR_MAC_TX_1c		0x00200000U	/* X */
#define	ISR_MAC_RX_1c		0x00100000U	/* X */
D 6
#define	ISR_RX_PKT3_1c		0x00080000U	/* X */	/* X */
E 6
I 6
#define	ISR_RX_PKT3_1c		0x00080000U	/* X */
E 6
#define	ISR_RX_PKT2_1c		0x00040000U	/* X */
#define	ISR_RX_PKT1_1c		0x00020000U	/* X */
#define	ISR_RX_PKT0_1c		0x00010000U	/* X */
#define	ISR_TX_PKT_1c		0x00008000U	/* X */
#define	ISR_TXQ_TO_RST_1c	0x00004000U	/* X */
#define	ISR_GPHY_LOWPWR_1c	0x00002000U	/* X */
#define	ISR_GPHY_1c		0x00001000U	/* X */
#define	ISR_TX_CREDIT_1c	0x00000800U	/* X */
#define	ISR_DMAW_TO_RST_1c	0x00000400U	/* X */
#define	ISR_DMAR_TO_RST_1c	0x00000200U	/* X */
#define	ISR_TXF_UR_1c		0x00000100U	/* X */
#define	ISR_RFD3_UR_1c		0x00000080U	/* X */
#define	ISR_RFD2_UR_1c		0x00000040U	/* X */
#define	ISR_RFD1_UR_1c		0x00000020U	/* X */
#define	ISR_RFD0_UR_1c		0x00000010U	/* X */
#define	ISR_HW_RXF_OV_1c	0x00000008U	/* X */
#define	ISR_MANUAL_1c		0x00000004U	/* X */
#define	ISR_TIMER_1c		0x00000002U	/* X */
#define	ISR_SMB_1c		0x00000001U	/* X */

#define	ISR_BITS_1c	\
	"\020"	\
	"\040DIS_INT"	\
	"\033PHY_LINKDOWN"	\
	"\032CERR"	\
	"\031NFER"	\
	"\030FER"	\
	"\027UR"	\
	"\026MAC_TX"	\
	"\025MAC_RX"	\
	"\024RX_PKT3"	\
	"\023RX_PKT2"	\
	"\022RX_PKT1"	\
	"\021RX_PKT0"	\
	"\020TX_PKT"	\
	"\017TXQ_TO_RST"	\
	"\016GPHY_LOWPWR"	\
	"\015GPHY"	\
	"\014TX_CREDIT"	\
	"\013DMAW_TO_RST"	\
	"\012DMAR_TO_RST"	\
	"\011TXF_UR"	\
	"\010RFD3_UR"	\
	"\007RFD2_UR"	\
	"\006RFD1_UR"	\
	"\005RFD0_UR"	\
	"\004HW_RXF_OV"	\
	"\003MANUAL"	\
	"\002TIMER"	\
	"\001SMB"

E 5
E 3
/* statistics information */
#define	STAT_RxOK		0
#define	STAT_RxBCAST		1
#define	STAT_RxMCAST		2
#define	STAT_RxPAUSE		3
#define	STAT_RxCTRL		4
D 2
#define	STAT_RxFCS		5
E 2
I 2
#define	STAT_RxCRC		5
E 2
#define	STAT_RxLEN		6
#define	STAT_RxBYTE		7
#define	STAT_RxRUNT		8
#define	STAT_RxFRAG		9
#define	STAT_Rx64		10
#define	STAT_Rx65_127		11
#define	STAT_RX128_255		12
#define	STAT_Rx256_511		13
#define	STAT_Rx512_1023		14
#define	STAT_Rx1024_1518	15
#define	STAT_Rx1519_MAX		16
D 2
#define	STAT_RxOVF		17
E 2
I 2
#define	STAT_RxLONG		17
E 2
#define	STAT_RxFIFO		18
D 2
#define	STAT_RxRRD_OVF		19
E 2
I 2
#define	STAT_RxNORRD		19
E 2
#define	STAT_RxALIGN		20
#define	STAT_RxBCAST_BYTE	21
#define	STAT_RxMCAST_BYTE	22
#define	STAT_RxADDR		23
#define	STAT_TxOK		24
#define	STAT_TxBCAST		25
#define	STAT_TxMCAST		26
#define	STAT_TxPAUSE		27
#define	STAT_TxEXCDEFER		28
#define	STAT_TxCTRL		29
#define	STAT_TxDEFER		30
#define	STAT_TxBYTE		31
#define	STAT_Tx64		32
#define	STAT_Tx65_127		33
#define	STAT_Tx128_255		34
#define	STAT_Tx256_511		35
#define	STAT_Tx512_1023		36
#define	STAT_Tx1024_1518	37
#define	STAT_Tx1519_MAX		38
#define	STAT_Tx1COL		39
#define	STAT_TxMCOL		40
#define	STAT_TxLATE_COL		41
#define	STAT_TxABORT		42
#define	STAT_TxUNDERRUN		43
#define	STAT_TxRD_EOP		44
#define	STAT_TxLEN		45
#define	STAT_TxTRUNC		46
#define	STAT_TxBCAST_BYTE	47
#define	STAT_TxMCAST_BYTE	48
D 4
#define	STAT_SM_VALID		49
#define	STAT_MAX		50
E 4
I 4
#define	STAT_MAX		49
E 4

/* Interrupt Status Message */
struct intr_status_msg {
	volatile uint32_t	ism_isr;	/* copy of ISR */
	volatile uint16_t	ism_rsd;	/* current rx status desc */
	volatile uint16_t	ism_rbd;	/* current rx buffer desc */
	volatile uint16_t	ism_unused;
	volatile uint16_t	ism_tbd;	/* current tx buffer desc */
};

/* rx status descriptor */
struct rx_status_desc {
	volatile uint64_t	rsd0;
	volatile uint64_t	rsd1;
};

I 3
#define	RSD0_CPU_1e	0xc000000000000000ULL
#define		RSD0_CPU_SHIFT_1e	62
E 3
#define	RSD0_LEN	0xffff000000000000ULL
I 3
#define	RSD0_LEN_1e	0x3fff000000000000ULL
E 3
#define		RSD0_LEN_SHIFT		48
#define	RSD0_CKSUM	0x0000ffff00000000ULL
#define		RSD0_CKSUM_SHIFT	32
#define	RSD0_INDEX	0x00000000ffff0000ULL
#define		RSD0_INDEX_SHIFT	16
#define	RSD0_NUM	0x00000000000000ffULL
I 3
#define	RSD0_SEQNUM	0x000000000000ffffULL
E 3

#define	RSD0_OWN	(RSD0_LEN | RSD0_CKSUM)

#define	RSD1_VTAG	0xffff000000000000ULL
#define		RSD0_VTAG_SHIFT		48
#define	RSD1_FLAGS	0x00000000ffffffffULL
#define		RSD1_E_DES_ADDR	0x02000000U	/*  */
#define		RSD1_E_LEN	0x01000000U	/* length error */
#define		RSD1_E_L4CHKSUM	0x00800000U	/* TCP/UDP cksum error */
#define		RSD1_E_IPCHKSUM	0x00400000U	/* IP cksum error */
#define		RSD1_E_TRUNC	0x00200000U	/* trancated */
#define		RSD1_E_OVF	0x00100000U	/* overflow */
#define		RSD1_E_RUNT	0x00080000U	/* too short */
#define		RSD1_E_DRIBBLE	0x00040000U	/* dribble error */
#define		RSD1_E_CODE	0x00020000U	/*  */
#define		RSD1_E_CRC	0x00010000U	/* crc error */
#define		RSD1_PAUSE	0x00008000U	/* pause packet */
#define		RSD1_MCAST	0x00004000U	/* multicast */
#define		RSD1_BCAST	0x00002000U	/* broadcast */
#define		RSD1_TCP	0x00001000U	/* tcp */
#define		RSD1_UDP	0x00000800U	/* udp */
#define		RSD1_IPv4	0x00000400U	/* ipv4 */
#define		RSD1_ERR	0x00000200U	/* error */
#define		RSD1_VLAN_INS	0x00000100U	/* vlan tag is inserted */
#define		RSD1_ETH_TYPE	0x00000080U	/* snap  */
I 3
#define		RSD1_IPv4_DF	0x00000040U	/* ipv4 */
#define		RSD1_IPv4_MF	0x00000020U	/* ipv4 */
D 5
#define		RSD1_IPv6_MF	0x00000010U	/* ipv6 */
E 5
I 5
#define		RSD1_IPv6	0x00000010U	/* ipv6 */
E 5
#define		RSD1_RSS_IP6TCP	0x00000008U	/* ipv6 TCP */
#define		RSD1_RSS_IP6	0x00000004U	/* ipv6 */
#define		RSD1_RSS_IP4TCP	0x00000002U	/* ipv4 TCP */
#define		RSD1_RSS_IP4	0x00000001U	/* ipv4 */
E 3

#define	RSD1_BITS	\
	"\020"	\
	"\032E_DES_ADDR"	\
	"\031E_LEN"	\
	"\030E_L4_CHKSUM"	\
	"\027E_IP_CHKSUM"	\
	"\026E_TRUNC"	\
	"\025E_OV"	\
	"\024E_RUNT"	\
	"\023E_DRIBBLE"	\
	"\022E_CODE"	\
	"\021E_CRC"	\
	"\020PAUSE"	\
	"\017MCAST"	\
	"\016BCAST"	\
	"\015TCP"	\
	"\014UDP"	\
	"\013IPv4"	\
	"\012ERR"	\
	"\011VLAN_INS"	\
	"\010ETH_TYPE"

I 5
/* for L1C */
#define	RRS0_HASH	0xffffffff00000000ULL
#define		RRS0_HASH_SHIFT		32
#define	RRS0_INDEX	0x00000000fff00000ULL
#define		RRS0_INDEX_SHIFT	20
#define	RRS0_CNT	0x00000000000f0000ULL
#define		RRS0_CNT_SHIFT		16
#define	RRS0_CSUM	0x000000000000ffffULL
#define		RRS0_CSUM_SHIFT		0

#define	RRS1_UPDATED	0x8000000000000000ULL
#define	RRS1_LEN_ERR	0x4000000000000000ULL	/* length error */
#define	RRS1_FIFO_FULL	0x2000000000000000ULL
#define	RRS1_TYPE	0x1000000000000000ULL
#define		RRS1_TYPE_SHIFT	60
#define		RRS1_TYPE_802_3	(1ULL << RRS1_TYPE_SHIFT)
#define		RRS1_TYPE_ETH	(0ULL << RRS1_TYPE_SHIFT)
#define	RRS1_MCAST	0x0800000000000000ULL	/* multicast */
#define	RRS1_BCAST	0x0400000000000000ULL	/* broadcast */
#define	RRS1_E_ICMP	0x0200000000000000ULL
#define	RRS1_E_RUNT	0x0100000000000000ULL	/* too short */
#define	RRS1_E_TRUNC	0x0080000000000000ULL	/* trancated */
#define	RRS1_E_FAE	0x0040000000000000ULL	/* crc error */
#define	RRS1_E_CRC	0x0020000000000000ULL	/* crc error */
#define	RRS1_E_SUM	0x0010000000000000ULL

#define	RRS1_PROT_ID	0x000e000000000000ULL
#define		RRS1_PROT_ID_SHIFT	49
#define	RRS1_VLAN_INS	0x0001000000000000ULL	/* vlan tag inserted */
#define	RRS1_E_IP_CSUM	0x0000800000000000ULL
#define	RRS1_E_L4_CSUM	0x0000400000000000ULL
#define	RRS1_PKT_SIZE	0x00003fff00000000ULL
#define		RRS1_PKT_SIZE_SHIFT	32

#define	RRS1_HASH_FLG	0x00000000f0000000ULL
#define		RSD0_HASH_FLG_SHIFT	28
#define	RRS1_CPU_NUM	0x000000000c000000ULL
#define		RSD0_CPU_NUM_SHIFT	26
#define	RRS1_HDS_TYPE	0x0000000003000000ULL
#define		RRS1_HDS_TYPE_SHIFT	24
#define		RRS1_HDS_TYPE_HEAD	1
#define		RRS1_HDS_TYPE_DATA	2
#define	RRS1_HEAD_LEN	0x0000000000ff0000ULL
#define		RSD0_HEAD_LEN_SHIFT	16
#define	RRS1_VTAG	0x000000000000ffffULL
#define		RRS0_VTAG_SHIFT		0

#define RRS_IS_NO_HDS_TYPE(rss) \
	((((rss) & RRS1_HDS_TYPE) >> RRS1_HDS_TYPE_SHIFT) == 0)

#define RRS_IS_HDS_HEAD(rss) \
        ((((rss) & RRS1_HDS_TYPE) >> RRS1_HDS_TYPE_SHIFT) == \
	RRS_HDS_TYPE_HEAD)

#define RRS_IS_HDS_DATA(rss) \
	((((rss) & RRS1_HDS_TYPE) >> RRS1_HDS_TYPE_SHIFT) == \
	RRS_HDS_TYPE_DATA)

#define	RRS1_BITS	\
	"\020"	\
D 6
	"\032E_DES_ADDR"	\
	"\031E_LEN"	\
	"\030E_L4_CHKSUM"	\
	"\027E_IP_CHKSUM"	\
	"\026E_TRUNC"	\
	"\025E_OV"	\
	"\024E_RUNT"	\
	"\023E_DRIBBLE"	\
	"\022E_CODE"	\
	"\021E_CRC"	\
	"\020PAUSE"	\
	"\017MCAST"	\
	"\016BCAST"	\
	"\015TCP"	\
	"\014UDP"	\
	"\013IPv4"	\
	"\012ERR"	\
	"\011VLAN_INS"	\
	"\010ETH_TYPE"
E 6
I 6
	"\040UPDATE"	\
	"\037MLEN_ERR"	\
	"\036MFIFO_FULL"	\
	"\035MTYPE"	\
	"\034MCAST"	\
	"\033BCAST"	\
	"\032E_ICMP"	\
	"\031E_RUNT"	\
	"\030E_TRUNC"	\
	"\027E_FAE"	\
	"\026E_CRC"	\
	"\025E_SUM"	\
	"\021VLAN_INS"	\
	"\020E_IP_CHKSUM"	\
	"\017E_L4_CHKSUM"
E 6

E 5
struct rx_buffer_desc {
	volatile uint32_t	rb_addr;
	volatile uint32_t	rb_haddr;
	volatile uint32_t	rb_flags;
};

I 5
/* for 1c */
struct rx_free_desc {
	volatile uint64_t	rf_addr;
};

E 5
struct tx_buffer_desc {
	volatile uint64_t	tb_addr;
I 5
#define	tpd_flags	tb_addr
E 5
	volatile uint64_t	tb_flags;
I 5
#define	tpd_addr	tb_flags
E 5
};

#define	TBF_CKSUMOFF	0xff00000000000000ULL	/* cksum */
#define		TBF_CKSUMOFF_SHIFT	56
#define	TBF_PAYLDOFF	0x00ff000000000000ULL	/* cksum */
#define		TBF_PAYLDOFF_SHIFT	48
#define	TBF_MSS		0xfff8000000000000ULL	/* tso */
#define		TBF_MSS_SHIFT	51
#define	TBF_HDRFLG	0x0004000000000000ULL	/* tso */
#define	TBF_TCPHL	0x0003c00000000000ULL	/* tso */
#define		TBF_TCPHL_SHIFT	46
#define	TBF_IPHL	0x00003c0000000000ULL	/* tso */
#define		TBF_IPHL_SHIFT	42
#define	TBF_ETHTYPE	0x0000020000000000ULL	/* soft vlan tagged */
#define	TBF_VTAGGED	0x0000010000000000ULL
#define	TBF_UDPC	0x0000008000000000ULL
#define	TBF_TCPC	0x0000004000000000ULL
#define	TBF_IPC		0x0000002000000000ULL
#define	TBF_SEGMENT	0x0000001000000000ULL
#define	TBF_CKSUM	0x0000000800000000ULL
#define	TBF_INSVTAG	0x0000000400000000ULL
#define	TBF_COALESE	0x0000000200000000ULL
#define	TBF_EOP		0x0000000100000000ULL
#define	TBF_VTAG	0x00000000ffff0000ULL
#define		TBF_VTAG_SHIFT	16
#define	TBF_PKTINT	0x0000000000008000ULL
#define	TBF_DMAINT	0x0000000000004000ULL
#define	TBF_BUFLEN	0x0000000000003fffULL	/* 14bit */

I 3
/* tx header for L2 */
#define	TH_PKTSIZE	0x000007ffU
#define	TH_INSVTAG	0x00008000U
#define	TH_VTAG		0xffff0000U
#define	TH_VTAG_SHIFT		16U

I 5
/* tx header for L1C */
#define	TPD_EOP		0x8000000000000000ULL
#define	TPD_MSS		0x7ffc000000000000ULL	/* tso */
#define		TPD_MSS_SHIFT	50
#define	TPD_CCSUM_EPAD	0x4000000000000000ULL
#define	TPD_CCSUM_OFF	0x003c000000000000ULL
#define		TPD_CCSUM_OFF_SHIFT	50
#define	TPD_ETHTYPE	0x0002000000000000ULL	/* 0:802.3, 1: ether */
#define	TPD_LSO_IPv4	0x0001000000000000ULL
#define	TPD_INSVTAG	0x0000800000000000ULL
#define	TPD_CONVTAG	0x0000400000000000ULL
#define	TPD_LSO_IPv6	0x0000200000000000ULL
#define	TPD_LSO		0x0000100000000000ULL
#define	TPD_UDP		0x0000080000000000ULL
#define	TPD_TCP		0x0000040000000000ULL
#define	TPD_IP		0x0000020000000000ULL
#define	TPD_CCSUM	0x0000010000000000ULL
#define	TPD_CKOFF	0x000000ff00000000ULL
#define		TPD_CKOFF_SHIFT	32
#define	TPD_VTAG	0x00000000ffff0000ULL
#define		TPD_VTAG_SHIFT	16
#define	TPD_BUFLEN	0x000000000000ffffULL

E 5
/* rx status for L2 */
#define	RS_UPDATE	0x80000000U
#define	RS_VLAN		0x08000000U
#define	RS_ALIGN	0x04000000U
#define	RS_TRUNC	0x02000000U
#define	RS_FRAG		0x01000000U
#define	RS_RUNT		0x00800000U
#define	RS_CODE		0x00400000U
#define	RS_CRC		0x00200000U
#define	RS_CTRL		0x00100000U
#define	RS_PAUSE	0x00080000U
#define	RS_MCAST	0x00040000U
#define	RS_BCAST	0x00020000U
#define	RS_OK		0x00010000U
#define	RS_PKTSIZE	0x000007ffU

#define	RS_BITS	\
	"\020"	\
	"\040UPDATE"	\
	"\034VLAN"	\
	"\033ALIGN"	\
	"\032TRUNC"	\
	"\031FRAG"	\
	"\030RUNT"	\
	"\027CODE"	\
	"\026CRC"	\
	"\025CTRL"	\
	"\024PAUSE"	\
	"\023MCAST"	\
	"\022BCAST"	\
	"\021OK"	

/* tx status for L2 */
#define	TS_UPDATE	0x80000000U
#define	TS_URUN		0x08000000U
#define	TS_ABORT	0x04000000U
#define	TS_LATE		0x02000000U
#define	TS_MCOL		0x01000000U
#define	TS_SCOL		0x00800000U
#define	TS_EXC		0x00400000U
#define	TS_DEFER	0x00200000U
#define	TS_CTRL		0x00100000U
#define	TS_PAUSE	0x00080000U
#define	TS_MCAST	0x00040000U
#define	TS_BCAST	0x00020000U
#define	TS_OK		0x00010000U
#define	TS_PKTSIZE	0x000007ffU

#define	TS_BITS	\
	"\020"	\
	"\040UPDATE"	\
	"\034URUN"	\
	"\033ABORT"	\
	"\032LATE"	\
	"\031MCOL"	\
	"\030SCOL"	\
	"\027EXC"	\
	"\026DEFER"	\
	"\025CTRL"	\
	"\024PAUSE"	\
	"\023MCAST"	\
	"\022BCAST"	\
	"\021OK"

I 6
/*
 * Vendor specific MII PHY registers
 */

/* MII_IER register */
#define	MII_IER_LINKUP			0x0400U
#define	MII_IER_LINKDOWN		0x0800U

/* MII_ANA_CTRL_0 */
#define ANA_RESTART_CAL			0x0001U
#define ANA_MANUL_SWICH_ON		0x001eU
#define		ANA_MANUL_SWICH_ON_SHIFT	0x1
#define ANA_MAN_ENABLE			0x0020U
#define ANA_SEL_HSP			0x0040U
#define ANA_EN_HB			0x0080U
#define ANA_EN_HBIAS			0x0100U
#define ANA_OEN_125M			0x0200U
#define ANA_EN_LCKDT			0x0400U
#define ANA_LCKDT_PHY			0x0800U
#define ANA_AFE_MODE			0x1000U
#define ANA_VCO_SLOW			0x2000U
#define ANA_VCO_FAST			0x4000U
#define ANA_SEL_CLK125M_DSP		0x8000U

/* MII_ANA_CTRL_4 */
#define ANA_IECHO_ADJ_3			0x000fU
#define		ANA_IECHO_ADJ_3_SHIFT		0
#define ANA_IECHO_ADJ_2			0x00f0U
#define		ANA_IECHO_ADJ_2_SHIFT		4
#define ANA_IECHO_ADJ_1			0x0f00U
#define		ANA_IECHO_ADJ_1_SHIFT		8
#define ANA_IECHO_ADJ_0			0xf000U
#define		ANA_IECHO_ADJ_0_SHIFT		12

/* MII_ANA_CTRL_5 */
#define ANA_SERDES_CDR_BW		0x0003U
#define		ANA_SERDES_CDR_BW_SHIFT		0
#define ANA_MS_PAD_DBG			0x0004U
#define ANA_SPEEDUP_DBG			0x0008U
#define ANA_SERDES_TH_LOS		0x0030U
#define		 ANA_SERDES_TH_LOS_SHIFT	4
#define ANA_SERDES_EN_DEEM		0x0040U
#define ANA_SERDES_TXELECIDLE		0x0080U
#define ANA_SERDES_BEACON		0x0100U
#define ANA_SERDES_HALFTXDR		0x0200U
#define ANA_SERDES_SEL_HSP		0x0400U
#define ANA_SERDES_EN_PLL		0x0800U
#define ANA_SERDES_EN			0x1000U
#define ANA_SERDES_EN_LCKDT		0x2000U

/* MII_ANA_CTRL_11 */
#define ANA_PS_HIB_EN			0x8000U

/* MII_ANA_CTRL_18 */
#define ANA_TEST_MODE_10BT_01		0x0003U
#define		ANA_TEST_MODE_10BT_01SHIFT	0
#define ANA_LOOP_SEL_10BT		0x0004U
#define ANA_RGMII_MODE_SW		0x0008U
#define ANA_EN_LONGECABLE		0x0010U
#define ANA_TEST_MODE_10BT_2		0x0020U
#define ANA_EN_10BT_IDLE		0x0400U
#define ANA_EN_MASK_TB			0x0800U
#define ANA_TRIGGER_SEL_TIMER		0x3000U
#define		ANA_TRIGGER_SEL_TIMER_SHIFT	12
#define ANA_INTERVAL_SEL_TIMER		0xc000U
#define		ANA_INTERVAL_SEL_TIMER_SHIFT	14

/* MII_ANA_CTRL_41 */
#define ANA_TOP_PS_EN			0x8000U

/* MII_ANA_CTRL_54 */
#define ANA_LONG_CABLE_TH_100		0x003fU
#define		ANA_LONG_CABLE_TH_100_SHIFT	0
#define ANA_DESERVED			0x0040U
#define ANA_EN_LIT_CH			0x0080U
#define	ANA_SHORT_CABLE_TH_100		0x3f00U
#define		ANA_SHORT_CABLE_TH_100_SHIFT	8
#define ANA_BP_BAD_LINK_ACCUM		0x4000U
#define ANA_BP_SMALL_BW			0x8000U

E 6
E 3
#endif /* __ATL1REG_H__ */
E 1
