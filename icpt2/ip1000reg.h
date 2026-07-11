/*
 * %W% %E%
 * Macro definition of IC Plus IP1000A Gigabit Ethernet MAC.
 * Based on TC9020 GbE Ethernet MAC Data sheet
 * This file is public domain. Coded by M.Murayama (KHF04453@nifty.com)
 */

#ifndef _IP1000REG_H_
#define _IP1000REG_H_

/*
 * Known PCI vendor-ids and device-ids for the device
 */
#define	PCI_VID_DLINK		0x1186U
#define	PCI_DID_DL2000		0x2000U

#define	PCI_VID_SUNDANCE	0x13f0U
#define	PCI_DID_TC9020		0x2020U
#define	PCI_DID_IP1000A		0x1023U

/*
 * TC2020 register definitions
 */
/* Offsets to the device registers. */
#define	DMACtrl			0x00	/* DW */
#define	TFDListPtr		0x10	/* QW */
#define	TxDMABurstThresh	0x18	/* B */
#define	TxDMAUrgentThresh	0x19	/* B */
#define	TxDMAPollPeriod		0x1a	/* B */
#define	RFDListPtr		0x1c	/* QW */

#define	RxDMABurstThresh	0x24	/* B */
#define	RxDMAUrgentThresh	0x25	/* B */
#define	RxDMAPollPeriod		0x26	/* B */
#define	RxDMAIntCtrl		0x28	/* DW */
#define	DebugCtrl		0x2c	/* W */

#define	AsicCtrl		0x30	/* DW */
#define	FIFOCtrl		0x38	/* W */
#define	RxEarlyThresh		0x3a	/* W */
#define	FlowOffThresh		0x3c	/* W */
#define	FlowOnThresh		0x3e	/* W */

#define	TxStartThresh		0x44	/* W */
#define	EepromData		0x48	/* W */
#define	EepromCtrl		0x4a	/* W */
#define	ExpRomAddr		0x4c	/* DW */

#define	ExpRomData		0x50	/* B */
#define	WakeEvent		0x51	/* B */
#define	Countdown		0x54	/* DW */
#define	IntStatusAck		0x5a	/* W */
#define	IntEnable		0x5c	/* W */
#define	IntStatus		0x5e	/* W */

#define	TxStatus		0x60	/* DW */
#define	MACCtrl			0x6c	/* DW */

#define	VLANTag			0x70	/* DW */
#define	PhyCtrl			0x76	/* B */
#define	StationAddress		0x78	/* B*6 */

#define	VLANId			0x80	/* DW */
#define	MaxFrameSize		0x86	/* W */
#define	ReceiveMode		0x88	/* W */
#define	VLANHashTable		0x8a	/* W */
#define	HashTable		0x8c	/* DW*2 */

#define	RMONStatisticsMask	0x98	/* DW */
#define	StatisticsMask		0x9c	/* DW */


/* Ethernet MIB Statistics registers */
#define	OctetRcvdOk		0xa8	/* DW */
#define	McstOctetRcvdOk		0xac	/* DW */
#define	BcstOctetRcvdOk		0xb0	/* DW */
#define	FramesRcvdOk		0xb4	/* DW */
#define	McstFramesRcvdOk	0xb8	/* DW */
#define	RxJumboFrames		0xbc	/* W */
#define	BcstFramesRcvdOk	0xbe	/* W */
#define	TCPCheckSumErrors	0xc0	/* W */
#define	IPCheckSumErrors	0xc2	/* W */
#define	UDPCheckSumErrors	0xc4	/* W */

#define	MacControlFramesRcvd	0xc6	/* W */
#define	FrameTooLongErrors	0xc8	/* W */
#define	InRangeLengthErrors	0xca	/* W */
#define	FramesCheckSeqErrors	0xcc	/* W */
#define	FramesLostRxErrors	0xce	/* W */

#define	OctetXmtOk		0xd0	/* DW */
#define	McstOctetXmtOk		0xd4	/* DW */
#define	BcstOctetXmtOk		0xd8	/* DW */
#define	FramesXmtdOk		0xdc	/* DW */
#define	McstFramesXmtdOk	0xe0	/* DW */
#define	FramesWDeferredXmt	0xe4	/* DW */
#define	LateCollisions		0xe8	/* DW */
#define	MultiColFrames		0xec	/* DW */
#define	SingleColFrames		0xf0	/* DW */
#define	BcstFramesXmtdOk	0xf6	/* W */
#define	CarrierSenseErrors	0xf8	/* W */
#define	MacControlFramesXmtd	0xfa	/* W */
#define	FramesAbortXSColls	0xfc	/* W */
#define	FramesWEXDeferral	0xfe	/* W */

/* statistic masks */
#define	SM_OctetRcvdOk_FramesRcvdOk		0x00000001U
#define	SM_McstOctetRcvdOk_McstFramesRcvdOk	0x00000002U
#define	SM_BcstOctetRcvdOk_BcstFramesRcvdOk	0x00000004U

#define	SM_RxJumboFrames			0x00000008U
#define	SM_TCPCheckSumErrors			0x00000010U
#define	SM_IPCheckSumErrors			0x00000020U
#define	SM_UDPCheckSumErrors			0x00000040U

#define	SM_MacControlFramesRcvd			0x00000080U
#define	SM_FramesTooLongErrors			0x00000100U
#define	SM_InRangeLengthErrors			0x00000200U
#define	SM_FrameCheckSeqErrors			0x00000400U
#define	SM_FramesLostRxErrors			0x00000800U
#define	SM_OctetXmtOk_FramesXmtOk		0x00001000U
#define	SM_McstOctetXmtOk_McstFramesXmtdOk	0x00002000U
#define	SM_BcstOctetXmtOk_BcstFramesXmtdOk	0x00004000U
#define	SM_FramesWDeferredXmt			0x00008000U
#define	SM_LateCollisions			0x00010000U
#define	SM_MultiColFrames			0x00020000U
#define	SM_SingleColFrames			0x00040000U

#define	SM_TxJumboFrames			0x00080000U
#define	SM_CarrierSenseErrors			0x00100000U
#define	SM_MacControlFramesXmtd			0x00200000U
#define	SM_FramesAbortXScolls			0x00400000U
#define	SM_FramesWEXDeferal			0x00800000U

/* RMON Statistics */
#define	ESCollisions			0x100
#define	ESOctetsTransmit		0x104
#define	ESPktsTransmit			0x108
#define	ESPkts64OctetsTransmit		0x10c
#define	ESPkts65to127OctetsTransmit	0x110
#define	ESPkts128to255OctetsTransmit	0x114
#define	ESPkts256to511OctetsTransmit	0x118
#define	ESPkts512to1023ctetsTransmit	0x11c
#define	ESPkts1024to1518ctetsTransmit	0x120
#define	ESCRCAlignErrors		0x124
#define	ESUndersizePkts			0x128
#define	ESFragments			0x12c
#define	ESJabbers			0x130
#define	ESOctets			0x134
#define	ESPkts				0x138
#define	ESPkts64Octets			0x13c
#define	ESPkts65to127Octets		0x140
#define	ESPkts128to255Octets		0x144
#define	ESPkts256to511Octets		0x148
#define	ESPkts512to1023ctets		0x14c
#define	ESPkts1024to1518ctets		0x150

/* Rx Fragment descriptor */
/* offset 0 : 39..0 RxDMANextPtr */
/* offset 0 : 63..40 reserved */

/* offset 8 : RxFrameStatus */
#define	RFS_TCI			0xffff000000000000ULL
#define		RFS_TCIShift		48
#define	RFS_RxFrameLen		0x0000ffffULL
#define	RFS_RxFIFOOverrun	0x00010000ULL
#define	RFS_RxRuntFrame		0x00020000ULL
#define	RFS_RxAlignmentError	0x00040000ULL
#define	RFS_RxFCSError		0x00080000ULL
#define	RFS_RxOversizedFrame	0x00100000ULL
#define	RFS_RxLengthError	0x00200000ULL
#define	RFS_VLANDetected	0x00400000ULL
#define	RFS_TCPDetected		0x00800000ULL
#define	RFS_TCPError		0x01000000ULL
#define	RFS_UDPDetected		0x02000000ULL
#define	RFS_UDPError		0x04000000ULL
#define	RFS_IPDetected		0x08000000ULL
#define	RFS_IPError		0x10000000ULL
#define	RFS_FrameStart		0x20000000ULL
#define	RFS_FrameEnd		0x40000000ULL
#define	RFS_RFDDone		0x80000000ULL

#define	RFS_BITS	\
	"\020"	\
	"\021RxFIFOOverrun"	\
	"\022RxRuntFrame"	\
	"\023RxAlignmentError"	\
	"\024RxFCSError"	\
	"\025RxOversizedFrame"	\
	"\026RxLengthError"	\
	"\027VLAN_detected"	\
	"\030TCP_detected"	\
	"\031TCP_error"		\
	"\032UDP_detected"	\
	"\033UDP_error"		\
	"\034IP_detected"	\
	"\035IP_error"		\
	"\036FrameStart"	\
	"\037FrameEnd"		\
	"\040RFDDone"

/* offset 0x10 : FragInfo */
#define	RFI_FragLen		0xffff000000000000ULL
#define		RFI_FragLenShift	48
#define	RFI_FragAddr		0x000000ffffffffffULL

/* TFD */
/* offset 0 : 39..0 TxDMANextPtr */
/* offset 0 : 63..40 reserved */

/* offset 8 : TxDMAFragControl */

#define	TFC_UserPri		0x0000e00000000000ULL
#define		TFC_UserPriShift	45
#define	TFC_CFI			0x0000100000000000ULL
#define	TFC_VID			0x00000fff00000000ULL
#define		TFC_VIDShift		32
#define	TFC_VTAG		(TFC_UserPri | TFC_CFI | TFC_VID)
#define		TFC_VTAGShift		TFC_VIDShift

#define	TFC_TFDDone		0x0000000080000000ULL
#define	TFC_VLANTagInsert	0x0000000010000000ULL
#define	TFC_FragCount		0x000000000f000000ULL
#define		TFC_FragCountShift	24
#define	TFC_TxDMAIndicate	0x0000000000800000ULL
#define	TFC_TxIndicate		0x0000000000400000ULL
#define	TFC_FcsAppendDisable	0x0000000000200000ULL
#define	TFC_IPCksumEn		0x0000000000100000ULL
#define		TFC_IPCksumEnShift	20
#define	TFC_UDPCksumEn		0x0000000000080000ULL
#define		TFC_UDPCksumEnShift	19
#define	TFC_TCPCksumEn		0x0000000000040000ULL
#define		TFC_TCPCksumEnShift	18

#define	TFC_WordAlign		0x0000000000030000ULL
#define		TFC_WordAlignShift	16
#define		TFC_WordAlignDword	(0U << TFC_WordAlignShift)
#define		TFC_WordAlignWord	(2U << TFC_WordAlignShift)
#define		TFC_WordAlignDisable	(1U << TFC_WordAlignShift)

#define	TFC_FrameId		0x000000000000ffffULL

#define	TFC_BITS	\
	"\020"	\
	"\040TFDDone"	\
	"\035VLANTagInsert"	\
	"\030TxDMAIndicate"	\
	"\027TxIndicate"	\
	"\026FcsAppendDisable"	\
	"\025IP_En"	\
	"\024UDP_En"	\
	"\023TCP_En"

/* offset n*8+0 : FragInfo */
#define	TFI_FragLen		0xffff000000000000ULL
#define	TFI_FragLenShift	48
#define	TFI_FragAddr		0x000000ffffffffffULL

/* offset 0x00 : DMACtrl DW */
#define	DC_RxDMAComplete	0x00000008U	/* R/- */
#define	DC_RxDMAPollNow		0x00000010U	/* -/W */
#define	DC_TxDMAComplete	0x00000800U	/* R/- */
#define	DC_TxDMAPollNow		0x00001000U	/* -/W */
#define	DC_TxDMAInProg		0x00008000U	/* R/- */
#define	DC_MWIDisable		0x00040000U	/* R/W */
#define	DC_TxWriteBackDisable	0x00080000U	/* R/W */
#define	DC_TxBurstLimit		0x00700000U	/* R/W */
#define		DC_TxBurstLimitShift	20U
#define		DC_TxBurstLimitMax	(5U << DC_TxBurstLimitShift)
#define	DC_TargetAbort		0x40000000U	/* R/- */
#define	DC_MasterAbort		0x80000000U	/* R/- */

#define	DC_BITS	\
	"\020"	\
	"\004RxDMAComplete"	\
	"\005RxDMAPollNow"	\
	"\014TxDMAComplete"	\
	"\015TxDMAPollNow"	\
	"\020TxDMAInProg"	\
	"\023MWIDisable"	\
	"\024TxWriteBackDis"	\
	"\037TargetAbort"	\
	"\040MasterAbort"

/* offset 0x10 : TFDListPtr DW*2 */

/* offset 0x18 : TxDMABurstThresh B */
#define	TxDMABurstThreshUnit	32U
#define	TxDMABurstThreshMin	8U		/* 256 byte */
#define	TxDMABurstThreshMax	0xffU		/* 8160 byte */

/* offset 0x19 : TxDMAUrgentThresh byte */
#define	TxDMAUrgentThreshUnit	32U
#define	TxDMAUrgentThreshMin	4U		/* 128 byte */
#define	TxDMAUrgentThreshMax	0xffU		/* 8160 byte */

/* offset 0x1a : TxDMAPollPeriod byte */
#define	TxDMAPollPeriodUnit	320U		/* in nano second */
#define	TxDMAPollPeriodMin	1U
#define	TxDMAPollPeriodMax	0xffU

/* offset 0x1c : RFDListPtr DW*2 */

/* offset 0x24 : RxDMABurstThresh B */
#define	RxDMABurstThreshUnit	32U
#define	RxDMABurstThreshMin	8U		/* 256 byte */
#define	RxDMABurstThreshMax	0xffU		/* 8160 byte */

/* offset 0x25 : RxDMAUrgentThresh byte */
#define	RxDMAUrgentThreshUnit	32U
#define	RxDMAUrgentThreshMin	4U		/* 128 byte */
#define	RxDMAUrgentThreshMax	0xffU		/* 8160 byte */

/* offset 0x26 : RxDMAPollPeriod byte */
#define	RxDMAPollPeriodUnit	320U		/* in nano second */
#define	RxDMAPollPeriodMin	1U
#define	RxDMAPollPeriodMax	0xffU		/* 81.92 uS */

/* offset 0x28 : RxDMAIntCtrl DW */
#define	RIC_RxFrameCount	0x000000ffU
#define	RIC_PriorityThresh	0x00001c00U
#define		RIC_PriorityThreshShift	10
#define		RIC_PriorityThreshMax	RIC_PriorityThresh
#define	RIC_RxDMAWaitTime	0xffff0000U
#define		RIC_RxDMAWaitTimeShift	16
#define	RxDMAWaitTimeTick	67U		/* in nS */

/* offset 0x2c : DebugCntl W */
#define	DBG_GPIO0Ctrl		0x0001U
#define	DBG_GPIO1Ctrl		0x0002U
#define	DBG_GPIO0		0x0004U
#define	DBG_GPIO1		0x0008U
#define	DBG_dbDisableDnHalt	0x0010U
#define	DBG_dbDisableUpHalt	0x0020U
#define	DBG_dbWrSameFSH		0x0040U
#define	DBG_dbNearEmpty		0x0080U
#define	DBG_dbSyncContrDone	0x0100U
#define	DBG_dbFrCurDoneAck	0x0200U
#define	DBG_dbFrcSpd1000	0x0400U

/* offset 0x30 : AsicCtrl DW */
#define	AC_ExpRomSize		0x00000002U	/* R/W 0=32kB 1=64kB */
#define	AC_PhySpeed10		0x00000010U	/* R/- */
#define	AC_PhySpeed100		0x00000020U	/* R/- */
#define	AC_PhySpeed1000		0x00000040U	/* R/- */
#define	AC_PhyMedia		0x00000080U	/* R/- 0:twisted pair, 1:fibre*/
#define	AC_ForcedConfig		0x00000700U	/* R/W */
#define		AC_ForcedConfigShift	8
#define		AC_ForcedConfigNone	(0U << AC_ForcedConfigShift)
#define		AC_ForcedConfigMode1	(1U << AC_ForcedConfigShift)
#define	AC_D3ResetDisable	0x00000800U	/* R/W */
#define	AC_SpeedupMode		0x00002000U	/* R/W */
#define	AC_LEDMode		0x00004000U	/* R/W */
#define	AC_RstOutPolarity	0x00008000U	/* R/W */
#define	AC_GlobalReset		0x00010000U	/* -/Wsc */
#define	AC_RxReset		0x00020000U	/* -/Wsc */
#define	AC_TxReset		0x00040000U	/* -/Wsc */
#define	AC_DMA			0x00080000U	/* -/Wsc */
#define	AC_FIFO			0x00100000U	/* -/Wsc */
#define	AC_Network		0x00200000U	/* -/Wsc */
#define	AC_Host			0x00400000U	/* -/Wsc */
#define	AC_AutoInit		0x00800000U	/* -/Wsc */
#define	AC_RstOut		0x01000000U	/* -/Wsc */
#define	AC_InterruptRequest	0x02000000U	/* -/Wsc */
#define	AC_ResetBusy		0x04000000U	/* R/W */
#define	AC_LEDSpeed		0x08000000U	/* R/W */
#define	AC_LEDMode1		0x20000000U	/* R/W */

#define	AC_BITS	\
	"\020"	\
	"\002ExpRomSize"	\
	"\005PhySpeed10"	\
	"\006PhySpeed100"	\
	"\007PhySpeed1000"	\
	"\010PhyMedia"	\
	"\011ForcedConfig1"	\
	"\014D3ResetDisable"	\
	"\016SpeedupMode"	\
	"\017LEDMode"	\
	"\020RstOutPolarity"	\
	"\033ResetBusy"

/* offset 0x38 : FIFOCtrl W */
#define	FC_RAMTestMode		0x0001U	/* R/W */
#define	FC_Transmitting		0x4000U	/* R/- */
#define	FC_Receiving		0x8000U	/* R/- */

/* offset 0x3a : RxEarlyThresh W */
#define	RxEarlyThreshMax		0x7ffU

/* offset 0x3c : FlowOffThresh W */
/* offset 0x3e : FlowOnThresh W */
#define	FlowThreshUnit	16

/* offset 0x44 : TxStartThresh W */
#define	TxStartThreshUnit	2U	/* datasheet says 4, but it seems 2 */
#define	TxStartThreshMax	0x0fffU

/* offset 0x48 : EepromData W */
/* offset 0x4a : EepromCtrl W */
#define	EEC_Address		0x00ffU
#define	EEC_Opcode		0x0300U
#define		EEC_OpcodeShift	8
#define		EEC_OpcodeWr		(1U << EEC_OpcodeShift)
#define		EEC_OpcodeRd		(2U << EEC_OpcodeShift)
#define		EEC_OpcodeEr		(3U << EEC_OpcodeShift)
#define	EEC_SubOpcode		0x00c0U
#define		EEC_SubOpcodeShift	6
#define		EEC_OpcodeWrDis		(0U << EEC_SubOpcodeShift)
#define		EEC_OpcodeWrAll		(1U << EEC_SubOpcodeShift)
#define		EEC_OpcodeErAll		(2U << EEC_SubOpcodeShift)
#define		EEC_OpcodeWrEn		(3U << EEC_SubOpcodeShift)
#define	EEC_Busy		0x8000U

/* offset 0x4c : ExpRomAddr DW */
/* offset 0x50 : ExpRomData B */
/* offset 0x51 : WakeEvent B */
#define	WE_WakePktEnable	0x01U	/* R/W */
#define	WE_MagicPktEnable	0x02U	/* R/W */
#define	WE_LinkEventEnable	0x04U	/* R/W */
#define	WE_WakePolarity		0x08U	/* R/W */
#define	WE_WakePktEvent		0x10U	/* R/- */
#define	WE_MagicPktEvent	0x20U	/* R/- */
#define	WE_LinkEvent		0x40U	/* R/- */
#define	WE_WakeOnLanEnable	0x80U	/* R/W */

/* offset 0x54 : Countdown DW */
#define	CD_Count		0x0000ffffU
#define	CD_CountdownSpeed	0x01000000U	/* 0:3200nS 1:320nS when 1Gbps*/
#define	CD_CountdownMode	0x02000000U	/* 0:now, 1: after TxDMAcomp */
#define	CD_CountdownIntEnabled	0x04000000U

/* offset 0x5a : IntStatusAck W */
/* offset 0x5c : IntEnable W */
/* offset 0x5e : IntStatus W */
#define	INT_InterruptStatus	0x0001U
#define	INT_HostError		0x0002U
#define	INT_TxComplete		0x0004U
#define	INT_MACControlFrame	0x0008U
#define	INT_RxComplete		0x0010U
#define	INT_RxEARLY		0x0020U
#define	INT_IntRequested	0x0040U
#define	INT_UpdateStats		0x0080U
#define	INT_LinkEvent		0x0100U
#define	INT_TxDMAComplete	0x0200U
#define	INT_RxDMAComplete	0x0400U
#define	INT_RFDListEnd		0x0800U
#define	INT_RxDMAPriority	0x1000U

#define	INT_BITS	\
	"\020"	\
	"\001InterruptStatus"	\
	"\002HostError"	\
	"\003TxComplete"	\
	"\004MACControlFrame"	\
	"\005RxComplete"	\
	"\006RxEarly"		\
	"\007IntRequested"	\
	"\010UpdateStats"	\
	"\011LinkEvent"	\
	"\012TxDMAComplete"	\
	"\013RxDMAComplete"	\
	"\014RFDListEnd"	\
	"\015RxDMAPriority"

/* offset 0x60 : TxStatus DW */
#define	TS_TxError		0x00000001U
#define	TS_LateCollision	0x00000004U
#define	TS_MaxCollisions	0x00000008U
#define	TS_TxUnderrun		0x00000010U
#define	TS_TxIndicateReqd	0x00000040U
#define	TS_TxComplete		0x00000080U
#define	TS_TxFrameId		0xffff0000U
#define		TS_TxFrameIdShift	16

#define	TS_BITS	\
	"\020"	\
	"\001TxError"	\
	"\003LateCollision"	\
	"\004MaxCollisions"	\
	"\005TxUnderrun"	\
	"\007TxIndicateReqd"	\
	"\010TxComplete"

/* offset 0x6c : MACCtrl DW */
#define	MC_IFSSelect		0x00000003U	/* R/W */
#define		MC_IFSSelectShift	0
#define		MC_IFSSelect96		(0U << MC_IFSSelectShift)
#define		MC_IFSSelect1024	(1U << MC_IFSSelectShift)
#define		MC_IFSSelect1792	(2U << MC_IFSSelectShift)
#define		MC_IFSSelect4352	(3U << MC_IFSSelectShift)
#define		MC_IFSSelect802_3	MC_IFSSelect96	/* standard */
#define	MC_DuplexSelect		0x00000020U	/* R/W 0:half, 1:full*/
#define	MC_RcvLargeFrames	0x00000040U	/* R/W */	/* reserved */
#define	MC_TxFlowControlEnable	0x00000080U	/* R/W */
#define	MC_RxFlowControlEnable	0x00000100U	/* R/W */
#define	MC_RcvFCS		0x00000200U	/* R/W */
#define	MC_FIFOLoopback		0x00000400U	/* R/W */
#define	MC_MACLoopback		0x00000800U	/* R/W */
#define	MC_AutoVLANtagging	0x00001000U	/* R/W */
#define	MC_AutoVLANuntagging	0x00002000U	/* R/W */
#define	MC_CollisionDetect	0x00010000U	/* R/- */
#define	MC_CarrierSense		0x00020000U	/* R/- */
#define	MC_StatisticsEnable	0x00200000U	/* -/Wsc */
#define	MC_StatisticsDisable	0x00400000U	/* -/Wsc */
#define	MC_StatisticsEnabled	0x00800000U	/* R/- */
#define	MC_TxEnable		0x01000000U	/* -/Wsc */
#define	MC_TxDisable		0x02000000U	/* -/Wsc */
#define	MC_TxEnabled		0x04000000U	/* R/- */
#define	MC_RxEnable		0x08000000U	/* -/Wsc */
#define	MC_RxDisable		0x10000000U	/* -/Wsc */
#define	MC_RxEnabled		0x20000000U	/* R/- */
#define	MC_Paused		0x40000000U	/* R/- */

#define	MC_BITS	\
	"\020"			\
	"\006DuplexSelect"	\
	"\007RcvLargeFrames"	\
	"\010TxFlowControlEnable"	\
	"\011RxFlowControlEnable"	\
	"\012RcvFCS"		\
	"\013FIFOLoopback"	\
	"\014MACLoopback"	\
	"\015AutoVLANtagging"	\
	"\016AutoVLANuntagging"	\
	"\021CollisionDetect"	\
	"\022CarrierSense"	\
	"\030StatisticsEnabled"	\
	"\033TxEnabled"		\
	"\036RxEnabled"		\
	"\037Paused"

/* offset 0x76 : PhyCtrl B */
#define	PC_MgmtClk		0x01U	/* -/W */
#define	PC_MgmtData		0x02U	/* R/W */
#define		PC_MgmtDataShift	1
#define	PC_MgmtDir		0x04U	/* -/W */
#define	PC_PhyDuplexPolarity	0x08U	/* R/W */
#define	PC_PhyDuplexStatus	0x10U	/* R/- */
#define	PC_PhyLnkPolarity	0x20U	/* R/W */
#define	PC_LinkSpeed		0xc0U	/* R/- */
#define		PC_LinkSpeedShift	6
#define		PC_LinkSpeed_down	(0U << PC_LinkSpeedShift)
#define		PC_LinkSpeed_10		(1U << PC_LinkSpeedShift)
#define		PC_LinkSpeed_100	(2U << PC_LinkSpeedShift)
#define		PC_LinkSpeed_1000	(3U << PC_LinkSpeedShift)

/* offset 0x78-0x7d : StationAddress W*3 */

/* offset 0x86 : MaxFrameSize W */

/* offset 0x88 : ReceiveMode W */
#define	RM_ReceiveUnicast	0x0001U	/* R/W */
#define	RM_ReceiveMulticast	0x0002U	/* R/W */
#define	RM_ReceiveBroadcast	0x0004U	/* R/W */
#define	RM_ReceiveAllFrames	0x0008U	/* R/W */
#define	RM_ReceiveMulticastHash	0x0010U	/* R/W */
#define	RM_ReceiveIPMulticast	0x0020U	/* R/W */
#define	RM_ReceiveVLANMatch	0x0100U	/* R/W */
#define	RM_ReceiveVLANHash	0x0200U	/* R/W */

#define	RM_BITS	\
	"\020"			\
	"\001RxUnicast"		\
	"\002RxMulticast"	\
	"\003RxBroadcast"	\
	"\004RxAllFrames"	\
	"\005RxMulticastHash"	\
	"\006RxIPMulticast"	\
	"\011RxVLANMatch"	\
	"\012RxVLANHash"

/* offset 0x8c-0x93 : Hashtable DW*2 */

#endif /* _IP1000REG_H_ */
