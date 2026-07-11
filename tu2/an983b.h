/*
 * an983b.h: %W% %E%
 * ADMtek AN983B register definitions
 * Based on AN983B data sheet by ADMtek
 * Coded by Masayuki Murayama (KHF04453@nifty.com)
 */

/* register offsets */
#define	PAR	0x00	/* PCI Access register */
#define	TDR	0x08	/* Transmit Demand register */
#define	RDR	0x10	/* Receive Demand register */
#define	RDB	0x18	/* Receive Descriptor Base */
#define	TDB	0x20	/* Transmit Descriptor Base */
#define	SR	0x28	/* Status register */
#define	NAR	0x30	/* Network Access register */
#define	IER	0x38	/* Interrupt Enable register */
#define	LPC	0x40	/* Lost Packet counter */
#define	SPR	0x48	/* Serial Port register */
#define	TMR	0x58	/* General purpose timer */
#define	WCSR	0x68	/* Wake-up control/status register */
#define	WPDR	0x70	/* Wakeup Pattern Data register */
#define	WTMR	0x78	/* Watch dog timer */
#define	SR2	0x80	/* ACSR5 - Assistant CSR5 (status register 2) */
#define	IER2	0x84	/* Interrupt Enable register 2 */
#define	CR	0x88	/* Command Register */
#define	PCIC	0x8c	/* PCI bus performance counter */
#define	PMCSR	0x90	/* Power management command and status */
#define	WTDP	0x94	/* Current working tranmit descriptor pointer */
#define	WRDP	0x98	/* Current working receive descriptor pointer */
#define	TXBR	0x9c	/* Transmit burst count/time-out */
#define	FROM	0xa0	/* Flash ROM register */
#define	PAR0	0xa4	/* physical address register 0 */
#define	PAR1	0xa8	/* PAR1 - physical address register 1 */
#define	MAR0	0xac	/* Multicast address register 0 */
#define	MAR1	0xb0	/* Multicast address register 1 */
#define	OPM	0xfc	/* Operational mode register */

/* CSR0 (offset=0x00) PAR PCI Access Register */
#define	PAR_ONNOWE	0x04000000	/* Enable OnNow registers */
#define	PAR_MWIE	0x01000000	/* Memory Write and Invalid Enable */
#define	PAR_MRLE	0x00800000	/* Memory Read Line Enable */
#define	PAR_MRME	0x00200000	/* Memory Read Multiple Enable */
#define	PAR_DBO		0x00100000	/* Descriptor byte ordering */
#define	PAR_TAP		0x00060000	/* Transmit auto-polling */
#define		PAR_TAP_SHIFT	17
#define	PAR_CAL		0x0000c000	/* Cache alignment */
#define		PAR_CAL_SHIFT	12
#define		PAR_CAL_32DW	(3 << PAR_CAL_SHIFT)
#define		PAR_CAL_16DW	(2 << PAR_CAL_SHIFT)
#define		PAR_CAL_8DW	(1 << PAR_CAL_SHIFT)
#define	PAR_PBL		0x00003f00	/* Programmable burst length */
#define		PAR_PBL_SHIFT	8
#define		PAR_PBL_32DW	(32 << PAR_PBL_SHIFT)
#define		PAR_PBL_16DW	(16 << PAR_PBL_SHIFT)
#define		PAR_PBL_8DW	(8 << PAR_PBL_SHIFT)
#define		PAR_PBL_4DW	(4 << PAR_PBL_SHIFT)
#define		PAR_PBL_2DW	(2 << PAR_PBL_SHIFT)
#define		PAR_PBL_1DW	(1 << PAR_PBL_SHIFT)
#define		PAR_PBL_UNLIMIT	(0 << PAR_PBL_SHIFT)
#define	PAR_BLE		0x00000080	/* big endian for data buffer */
#define	PAR_DSL		0x00000078	/* Descriptor Skip Length */
#define		PAR_DSL_SHIFT	3
#define	PAR_BAR		0x00000002	/* Bus arbitration 1:tx higher */
#define	PAR_SWR		0x00000001	/* Software reset */

/* ADMtek: dont have ONNOWE bit */

/* CSR1 (offset=0x08) TDR - Transmit demand register */
/* CSR2 (offset=0x10) RDR - Receive demand register */
/* CSR3 (offset=0x18) RBD - Receive descriptor base address */
/* CSR4 (offset=0x20) TBD - Transmit descriptor base address */
/* CSR5 (offset=0x28) SR  - Status register */
#define	SR_LC	0x08000000	/* Link changed (21) */
#define	SR_GP	0x08000000	/* General purpose port intr (21) */
#define	SR_BET	0x03800000	/* Bus Eror Type */
#define	SR_BET_SHIFT	23
#define		BET_PARITY_ERROR	0
#define		BET_MASTER_ABORT	1
#define		BET_TARGET_ABORT	2
#define	SR_TS	0x00700000	/* Tx state */
#define	SR_TS_SHIFT	20
#define		TS_STOP		0
#define		TS_READ_DESC	1
#define		TS_TXING	2
#define		TS_FIFO_FULL	3
#define		TS_SETUP_PKT	5
#define		TS_SUSPENDED	6
#define		TS_WRITE_DESC	7

#define	SR_RS	0x000e0000	/* Rx state */
#define	SR_RS_SHIFT	17
#define		RS_STOP		0
#define		RS_READ_DESC	1
#define		RS_CHECK_PKT	2	
#define		RS_WAIT		3
#define		RS_SUSPENDED	4
#define		RS_WRITE_DESC	5
#define		RS_FLUSH_FIFO	6
#define		RS_FIFO_DRAIN	7

#define	SR_NISS	0x00010000	/* Normal interrupt status summary */
#define	SR_AISS	0x00008000	/* Abnormal interrupt status summary */
#define	SR_ERI	0x00004000	/* Early Rx interrupt */
#define	SR_FBE	0x00002000	/* Fatal Bus Error */
#define	SR_LNF	0x00001000	/* Link Fail */
#define	SR_GPTT	0x00000800	/* General purpose timer time-out */
#define	SR_ETI	0x00000400	/* Early Tx interrupt */
#define	SR_RWT	0x00000200	/* Receive watch dog timeout */
#define	SR_RPS	0x00000100	/* Receive process stopped */
#define	SR_RDU	0x00000080	/* Receive descriptor unavailable */
#define	SR_RCI	0x00000040	/* Receive completed interrupt */
#define	SR_TUF	0x00000020	/* Transmit under-flow */
#define	SR_LNP	0x00000010	/* Link Pass, Autonego done */
#define	SR_TJT	0x00000008	/* Transmit jabber timer time-out */
#define	SR_TDU	0x00000004	/* Tranmit descriptor unavailable */
#define	SR_TPS	0x00000002	/* Transmit process stopped */
#define	SR_TCI	0x00000001	/* Transmit completed interrupt */

#define	SR_BITS	\
	"\020"	\
	"\021NISS"	\
	"\020AISS"	\
	"\017ERI"	\
	"\016FBE"	\
	"\015LNF"	\
	"\014GPTT"	\
	"\013ETI"	\
	"\012RWT"	\
	"\011RPS"	\
	"\010RDU"	\
	"\007RCI"	\
	"\006TUF"	\
	"\005LNP"	\
	"\004TJT"	\
	"\003TDU"	\
	"\002TPS"	\
	"\001TCI"

/* CSR6 (offset=0x30) NAR - Network Access register */
#define	NAR_SC	0x80000000	/* Special capture effect enable */
#define	NAR_RA	0x40000000	/* Receive All */
#define	NAR_ID	0x04000000	/* Ignore Destination address MSB */
#define	NAR_MBO	0x02000000	/* Must be 1 */
#define	NAR_SCR	0x01000000	/* Scrambler mode */
#define	NAR_PCS	0x00800000	/* PCS function */
#define	NAR_TTM	0x00400000	/* Tx Threshold Mode */
#define	NAR_SF	0x00200000	/* Store and forward for tx */
#define	NAR_SQE	0x00080000	/* SQE(Heart beat) disable (1: disable) */
#define	NAR_PS	0x00040000	/* Port Sellect (0: AUI/10T, 1:MII/SYM) */
#define	NAR_CA	0x00020000	/* Capure Effect Enable */
#define	NAR_TR	0x0000c000	/* Transmit threshold control */
#define	NAR_TR_SHIFT	14
#define		TR_MASK	3
#define		TR_128	0
#define		TR_256	1
#define		TR_512	2
#define		TR_1024	3
#define	NAR_ST	0x00002000	/* Start/Stop Transmit (1: start) */
#define	NAR_FC	0x00001000	/* Force collision for tx test */
#define	NAR_OM	0x00000c00	/* Operating mode */
#define	NAR_OM_SHIFT	10
#define		OM_MASK		3
#define		OM_NORMAL	0
#define		OM_LOOPBACK	1
#define	NAR_FD	0x00000200	/* Full Duplex mode */
#define	NAR_MM	0x00000080	/* Receive all multicast packet */
#define	NAR_PR	0x00000040	/* Promiscuous mode */
#define	NAR_SBC	0x00000020	/* Stop backoff counter */
#define	NAR_IF	0x00000010	/* Inverse filtering (RO) */
#define	NAR_PB	0x00000008	/* Pass bad packet */
#define	NAR_HO	0x00000004	/* Hash Only Rx filter mode (RO) */
#define	NAR_SR	0x00000002	/* Start/Stop receive (1: start) */
#define	NAR_HP	0x00000001	/* Hash/Perfect Rx filter mode (RO) */

/* CSR7 (offset=0x38) IER - Interrupt enable register */
/* same bit assignment with SR */

/* CSR8 (offset=0x40) LPC - Lost Packet counter */
#define	LPC_OCO		0x10000000	/* FIFO Overflow counter overflow */
#define	LPC_FOC		0x0ffe0000	/* FIFO Overflow counter */
#define	LPC_FOC_SHIFT	17
#define	LPC_FOC_MASK	0x000003ff
#define	LPC_LPCO	0x00010000	/* Lost packet counter overflow */
#define	LPC_LPC		0x0000ffff	/* Lost packet counter */
#define	LPC_LPC_MASK	0x0001ffff

/* CSR9 (offset=0x48) SPR - Serial Port register */
#define	SPR_MDI		0x00080000	/* MII management data input */
#define		SPR_MDI_SHIFT	19
#define	SPR_MMC		0x00040000	/* MII management Control */
#define	SPR_MDO		0x00020000	/* MII management data output */
#define		SPR_MDO_SHIFT	17
#define	SPR_MDC		0x00010000	/* MII management Clock */
#define	SPR_SRC		0x00004000	/* Serial EEPROM Read control */
#define	SPR_SWC		0x00002000	/* Serial EEPROM Write control */
#define	SPR_SRS		0x00000800	/* Serial EEPROM select */
#define	SPR_SDO		0x00000008	/* Serial EEPROM data out */
#define		SPR_SDO_SHIFT	3
#define	SPR_SDI		0x00000004	/* Serial EEPROM data in */
#define		SPR_SDI_SHIFT	2
#define	SPR_SCLK	0x00000002	/* Serial EEPROM clock */
#define	SPR_SCS		0x00000001	/* Serial EEPROM chip select */

/* CSR11 (offset=0x58) TMR - General purpose timer */
#define	TMR_COM	0x00010000	/* Continuous Operation mode */
#define	TMR_GTV	0x0000ffff	/* General purpose timer value */

/* CSR13 (offset=0x68) */
/* ADMtek WCSR - Wake-up control/status register */
#define	WCSR_CRTC	0x40000000	/* CRC-16 type */
#define	WCSR_WP1E	0x20000000	/* wake-up pattern one patched */
#define	WCSR_WP2E	0x10000000	/* wake-up pattern two matched */
#define	WCSR_WP3E	0x08000000	/* wake-up pattern three matched */
#define	WCSR_WP4E	0x04000000	/* wake-up pattern four patched */
#define	WCSR_WP5E	0x02000000	/* wake-up pattern five matched */
#define	WCSR_LINKOFF	0x00020000	/* Link off detect enable */
#define	WCSR_LINKON	0x00010000	/* Link on detect enable */
#define	WCSR_WFRE	0x00000400	/* Wake-up Frame receive enable */
#define	WCSR_MPRE	0x00000200	/* Magic packet receive enable */
#define	WCSR_LSCE	0x00000100	/* Link status changed enable */
#define	WCSR_WFR	0x00000004	/* Wake-up frame received */
#define	WCSR_MPR	0x00000002	/* Magic packet received */
#define	WCSR_LSC	0x00000001	/* Link status changed */

/* CSR14 (offset=0x70) */
/* ADMtek WPDR - Wakeup Pattern Data register */

/* CSR15 (offset=0x78) WTMR - Watch dog timer */
#define	WTMR_RWR	0x00000020	/* Receive watch dog release */
#define	WTMR_RWD	0x00000010	/* Receive watch dog disable */
#define	WTMR_ABM	0x00000008	/* AUI/BNC mode */
#define	WTMR_JCLK	0x00000004	/* Jabber clock */
#define	WTMR_NJ		0x00000002	/* Non-jabber */
#define	WTMR_JBD	0x00000001	/* Jabberdisable */

/* ADMtek */
#define	WTMR_MRXCK_AN	0x10000000	/* MII Rx clock reverse */

/* DAVICOM DM9102 */
#define	WTMR_TXPM_DM	0x00008000	/* Transmit pause packet control */
#define	WTMR_TXP0_DM	0x00004000	/* Transmit pause packet (0x0000) */
#define	WTMR_TXPF_DM	0x00002000	/* Transmit pause packet (0xffff) */
#define	WTMR_FLCE_DM	0x00000400	/* Flow control enable */
#define	WTMR_VLAN_DM	0x00000040	/* VLAN length capability enable */

/* CSR16 (offset=0x80) ACSR5 - Assistant CSR5 (status register 2) */
#define	SR2_TEIS	0x80000000	/* Tx early interrupt status */
#define	SR2_REIS	0x40000000	/* Rx early interrupt status */
#define	SR2_LCS		0x20000000	/* Status of Link change */
#define	SR2_TDIS	0x10000000	/* Tx deferred interrupt status */
#define	SR2_PFR		0x04000000	/* Pause frame Rx status */
#define	SR2_ANISS	0x00010000	/* Added normal interrupt status sammary */
#define	SR2_AAISS	0x00008000	/* Added Abnormal interrupt status summary */


/*
 * ADMtek Specific registers
 */
/* CSR17 (offset=0x84) ACSR7 - Interrupt Enable register 2 */
#define	IER2_TEIE	0x80000000	/* Tx early interrupt enable */
#define	IER2_REIE	0x40000000	/* Rx early interrupt enabel */
#define	IER2_LCIE	0x20000000	/* Link status change interrupt */
#define	IER2_TDIE	0x10000000	/* Tx deferred */
#define	IER2_PFRIE	0x04000000	/* Pause frame rx */
#define	IER2_ANISE	0x00010000	/* Added normal interrupt status */
#define	IER2_AAIE	0x00008000	/* Added abnormal interrupst status */

/* CSR18 (offset=0x88) CR - Command Register */
#define	CR_D3CS		0x80000000	/* D3cold support */
#define	CR_AUXCL	0x70000000	/* Aux current */
#define	CR_PMEP		0x08000000	/* active type select */
#define	CR_PMEPEN	0x04000000	/* PMEP pin enable */
#define	CR_PCI_PAD	0x02000000	/* No effect in PCI mode */
#define	CR_PMES_STICKY	0x01000000	/* pmez sticky */
#define	CR_4_3LED	0x00800000	/* 3 LED mode select */
#define	CR_RFS		0x00600000	/* Receive FIFO size */
#define	CR_CRD		0x00100000	/* Clock run disable */
#define	CR_PM		0x00080000	/* power management */
#define	CR_APM		0x00040000	/* APM mode */
#define	CR_LWS		0x00020000	/* Should be 0 */
#define	CR_D3_APM	0x00000080	/* D3_cold */
#define	CR_RWP		0x00000040	/* Reset Wake-up Pattern data */
#define	CR_PAUSE	0x00000020	/* PAUSE function enable */
#define	CR_RTE		0x00000010	/* Rx threshold enable */
#define	CR_DRT		0x0000000c	/* Drain Rx threshold */
#define	CR_SINT		0x00000002	/* Software interrupt */
#define	CR_ATUR		0x00000001	/* enabla automatically Tx underrun recovery */

/* CSR19 (offset=0x8c) PCIC - PCI bus performance counter */
#define	PCIC_CLKCNT	0xffff0000
#define	PCIC_DWCNT	0x000000ff

/* CSR20 (offset=0x90) PMCSR - Power management command and status */
#define	PMCSR_PMES	0x00008000	/* PME_status */
#define	PMCSR_DSCAL	0x00006000	/* Data scale */
#define	PMCSR_DSEL	0x00001e00	/* Data_select */
#define	PMCSR_PME_EN	0x00000003	/* Power status */

/* CSR21 (offset=0x94) WTDP - current working tranmit descriptor pointer */
/* CSR22 (offset=0x98) WRDP - current working receive descriptor pointer */
/* CSR23 (offset=0x9c) TXBR - Transmit burst count /time-out */
#define	TXBR_TBCNT	0x000f0000	/* Transmit burst count */
#define	TXBR_TTO	0x00000fff	/* Transmit time-out */

/* CSR24 (offset=0xa0) FROM */
/* CSR25 (offset=0xa4 PAR0 - physical address register 0 */
/* CSR26 (offset=0xa8) PAR1 - physical address register 1 */
/* CSR27 (offset=0xac) MAR0 - Multicast address register 0 */
/* CSR28 (offset=0xb0) MAR1 - Multicast address register 1 */
/* Operation mode register (memory base offset 0x0fc ) */

#define	OPM_SPEED	0x80000000	/* speed (100M) */
#define	OPM_FD		0x40000000	/* Full duplex */
#define	OPM_LINK	0x20000000	/* network llink status */
#define	OPM_EERLOD	0x04000000	/* Reload data from eerom */
#define	OPM_OPMODE	0x00000007	/* Operation mode */
#define	OPM_SNGLE	0x00000007	/* single chip mode */
#define	OPM_MAC		0x00000004	/* MAC only */

/* Receive descriptor */
#define	RDES0_OWN	0x80000000
#define	RDES0_AUN	0x40000000	/* Address unmatch (DM9102) */
#define	RDES0_FL	0x3fff0000	/* frame length including crc */
#define		RDES0_FL_SHIFT	16
#define	RDES0_ES	0x00008000	/* Error summary */
#define	RDES0_DE	0x00004000	/* descriptor error */
#define	RDES0_DT	0x00003000	/* Data type */
#define		RDES0_DT_SHIFT	12
#define		DT_NORMAL	0	/* normal */
#define		DT_MAC_LB	1	/* mac loopback */
#define		DT_TX_LB	2	/* tx loopback */
#define		DT_REMOTE_LB	3	/* remote loopback */
#define	RDES0_RF	0x00000800	/* Runt frame */
#define	RDES0_MF	0x00000400	/* Multicast frame */
#define	RDES0_FS	0x00000200	/* First descriptor */
#define	RDES0_LS	0x00000100	/* Last descriptor */
#define	RDES0_TL	0x00000080	/* Too long packet */
#define	RDES0_CS	0x00000040	/* Late collision */
#define	RDES0_FT	0x00000020	/* Frame type */
#define	RDES0_RW	0x00000010	/* Receive watchdog */
#define	RDES0_DB	0x00000004	/* Dibble bit */
#define	RDES0_CE	0x00000002	/* CRC error */
#define	RDES0_OF	0x00000001	/* Overflow */	

#define	RSR_BITS	\
	"\020"		\
	"\040OWN"	\
	"\020ES"	\
	"\017DE"	\
	"\014RF"	\
	"\013MF"	\
	"\012FS"	\
	"\011LS"	\
	"\010TL"	\
	"\007CS"	\
	"\006FT"	\
	"\005RW"	\
	"\003DB"	\
	"\002CE"	\
	"\001OF"

#define	RDES1_RER	0x02000000	/* Receive End of ring */
#define	RDES1_RCH	0x01000000	/* Second address chain */
#define	RDES1_RBS2	0x003ff800	/* buffer 2 size */
#define	RDES1_RBS2_SHIFT	11	
#define	RDES1_RBS1	0x000007ff	/* buffer 1 size */
#define	RDES1_RBS1_SHIFT	0

#define	RCR_BITS	"\020\032RER\031RCH"

struct rx_desc {
	volatile uint32_t	rd_status;
	volatile uint32_t	rd_control;
	volatile uint32_t	rd_baddr1;
	volatile uint32_t	rd_baddr2;
};

#define	TDES0_OWN	0x80000000	/* Own */
#define	TDES0_UR	0x00c00000	/* Under-run */
#define	TDES0_ES	0x00008000	/* Error summary */
#define	TDES0_TO	0x00004000	/* Transmit jabber timeout */
#define	TDES0_LO	0x00000800	/* Loss carrier */
#define	TDES0_NC	0x00000400	/* No carrier */
#define	TDES0_LC	0x00000200	/* Late collision */
#define	TDES0_EC	0x00000100	/* Excessive collision */
#define	TDES0_HF	0x00000080	/* Heart beat fail */
#define	TDES0_CC	0x00000078	/* Collision count */
#define		TDES0_CC_SHIFT	3
#define		CC_MASK		0xf
#define	TDES0_UF	0x00000002	/* Under-run */
#define	TDES0_DE	0x00000001	/* deferred */

#define	TSR_BITS	\
	"\020"		\
	"\040OWN"	\
	"\014ES"	\
	"\013TO"	\
	"\010LO"	\
	"\007NC"	\
	"\006LC"	\
	"\005EC"	\
	"\004HF"	\
	"\002UF"	\
	"\001DE"

#define	TDES1_IC	0x80000000	/* Interrupt completed */
#define	TDES1_LS	0x40000000	/* Last descriptor */
#define	TDES1_FS	0x20000000	/* First descriptor */
#define	TDES1_FMB1	0x10000000	/* Filtering mode bit1 */
#define	TDES1_SETF	0x08000000	/* Setup frame*/
#define	TDES1_AC	0x04000000	/* Disable add CRC function */
#define	TDES1_TER	0x02000000	/* End of ring */
#define	TDES1_TCH	0x01000000	/* 2nd address chain */
#define	TDES1_DPD	0x00800000	/* Disable add padding function */
#define	TDES1_FMB0	0x00400000	/* Filtering mode bit0 */
#define	TDES1_TBS2	0x003ff800	/* buffer 2 size */
#define	TDES1_TBS2_SHIFT	11
#define		TBS2_MASK	0x7ff
#define	TDES1_TBS1	0x000007ff	/* buffer 1 size */
#define	TDES1_TBS1_SHIFT	0
#define		TBS1_MASK	0x7ff

#define	TCR_BITS	\
	"\020"		\
	"\040IC"	\
	"\037LS"	\
	"\036FS"	\
	"\035FMB1"	\
	"\034SETF"	\
	"\033AC"	\
	"\032TER"	\
	"\031TCH"	\
	"\030DPD"	\
	"\027FMB0"

struct tx_desc {
	volatile uint32_t	td_status;
	volatile uint32_t	td_control;
	volatile uint32_t	td_baddr1;
	volatile uint32_t	td_baddr2;
};
