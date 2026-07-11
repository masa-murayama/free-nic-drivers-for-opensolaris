
/******************************************************************************/
/* Local functions. */
/******************************************************************************/

LM_STATUS b44_LM_Abort(PLM_DEVICE_BLOCK pDevice);
LM_STATUS b44_LM_QueueRxPackets(PLM_DEVICE_BLOCK pDevice);
LM_STATUS b44_LM_SetFlowControl(PLM_DEVICE_BLOCK pDevice,
    uint32_t LocalPhyAd, uint32_t RemotePhyAd);
static uint32_t b44_GetPhyAdFlowCntrlSettings(PLM_DEVICE_BLOCK pDevice);

STATIC LM_STATUS b44_LM_ResetChip(PLM_DEVICE_BLOCK pDevice);
STATIC LM_STATUS b44_LM_DisableChip(PLM_DEVICE_BLOCK pDevice);
void b44_LM_ClearStats(LM_DEVICE_BLOCK *pDevice);
void b44_LM_WriteCam(LM_DEVICE_BLOCK *pDevice, LM_UINT8 *ea,
    uint32_t camindex);

uint32_t b44_LM_getsbaddr(LM_DEVICE_BLOCK *pDevice, uint32_t id,
    uint32_t coreunit);
void b44_LM_sb_core_disable(LM_DEVICE_BLOCK *pDevice);
uint32_t b44_LM_sb_pci_setup(LM_DEVICE_BLOCK *pDevice, uint32_t cores);
uint32_t b44_LM_sb_coreunit(LM_DEVICE_BLOCK *pDevice);
void b44_LM_sb_core_reset(LM_DEVICE_BLOCK *pDevice);
uint32_t b44_LM_sb_coreid(LM_DEVICE_BLOCK *pDevice);
uint32_t b44_LM_sb_corerev(LM_DEVICE_BLOCK *pDevice);
uint32_t b44_LM_sb_iscoreup(LM_DEVICE_BLOCK *pDevice);

#define BCM4710_PCI_DMA		0x40000000	/* Client Mode PCI memory access space (1 GB) */
#define BCM4710_ENUM		0x18000000	/* Beginning of core enumeration space */

struct sbmap bcm4402[] = {
	{SBID_PCI_DMA,		0,	BCM4710_PCI_DMA},
	{SBID_ENUM,		0,	BCM4710_ENUM},
	{SBID_REG_EMAC,		0,	0x18000000},
	{SBID_REG_CODEC,	0,	0x18001000},
	{SBID_REG_PCI,		0,	0x18002000}
};

/******************************************************************************/
/* Description:                                                               */
/*                                                                            */
/* Return:                                                                    */
/******************************************************************************/

/******************************************************************************/
/* Description:                                                               */
/*    This routine initializes default parameters and reads the PCI           */
/*    configurations.                                                         */
/*                                                                            */
/* Return:                                                                    */
/*    LM_STATUS_SUCCESS                                                       */
/******************************************************************************/
LM_STATUS
b44_LM_GetAdapterInfo(
PLM_DEVICE_BLOCK pDevice)
{
    LM_UINT8 eprom[128];
    LM_STATUS Status;
    uint32_t Value32;

    /* Get Device Id and Vendor Id */
    Status = b44_MM_ReadConfig32(pDevice, PCI_VENDOR_ID_REG, &Value32);
    if(Status != LM_STATUS_SUCCESS)
    {
        return Status;
    }
    pDevice->PciVendorId = (LM_UINT16) Value32;
    pDevice->PciDeviceId = (LM_UINT16) (Value32 >> 16);

    Status = b44_MM_ReadConfig32(pDevice, PCI_REV_ID_REG, &Value32);
    if(Status != LM_STATUS_SUCCESS)
    {
        return Status;
    }
    pDevice->PciRevId = (LM_UINT8) Value32;

    /* Get subsystem vendor. */
    Status = b44_MM_ReadConfig32(pDevice, PCI_SUBSYSTEM_VENDOR_ID_REG, &Value32);
    if(Status != LM_STATUS_SUCCESS)
    {
        return Status;
    }
    pDevice->PciSubvendorId = (LM_UINT16) Value32;

    /* Get PCI subsystem id. */
    pDevice->PciSubsystemId = (LM_UINT16) (Value32 >> 16);

    Status = b44_MM_MapMemBase(pDevice);
    if(Status != LM_STATUS_SUCCESS)
    {
        return Status;
    }
    /* Initialize the memory view pointer. */
    pDevice->pMemView = (bcmenetregs_t *) pDevice->pMappedMemBase;

    b44_LM_EepromReadBlock(pDevice, 0, (LM_UINT16 *) eprom, sizeof(eprom));
    if (eprom[126] != 1)
        return LM_STATUS_FAILURE;

    pDevice->PermanentNodeAddress[0] = eprom[79];
    pDevice->PermanentNodeAddress[1] = eprom[78];
    pDevice->PermanentNodeAddress[2] = eprom[81];
    pDevice->PermanentNodeAddress[3] = eprom[80];
    pDevice->PermanentNodeAddress[4] = eprom[83];
    pDevice->PermanentNodeAddress[5] = eprom[82];

    memcpy(pDevice->NodeAddress, pDevice->PermanentNodeAddress, 6);

    pDevice->PhyAddr = eprom[90] & 0x1f;
    pDevice->MdcPort = (eprom[90] >> 14) & 0x1;

    /* Initialize the default values. */
    pDevice->TxPacketDescCnt = DEFAULT_TX_PACKET_DESC_COUNT;
    pDevice->RxPacketDescCnt = DEFAULT_RX_PACKET_DESC_COUNT;
    pDevice->MaxRxPacketDescCnt = DMAMAXRINGSZ / sizeof(dmadd_t);
    pDevice->rxoffset = 30;
    pDevice->lazyrxfc = 1;
    pDevice->lazyrxmult = 0;
    pDevice->lazytxfc = 0;
    pDevice->lazytxmult = 0;
    pDevice->intmask = DEF_INTMASK;
    pDevice->LinkStatus = LM_STATUS_LINK_DOWN;

    /* Change driver parameters. */
    Status = b44_MM_GetConfig(pDevice);
    if(Status != LM_STATUS_SUCCESS)
    {
        return Status;
    }
    return LM_STATUS_SUCCESS;
} /* LM_GetAdapterInfo */


/******************************************************************************/
/* Description:                                                               */
/*    This routine sets up receive/transmit buffer descriptions queues.       */
/*                                                                            */
/* Return:                                                                    */
/*    LM_STATUS_SUCCESS                                                       */
/******************************************************************************/
LM_STATUS
b44_LM_InitializeAdapter(PLM_DEVICE_BLOCK pDevice)
{
    LM_PHYSICAL_ADDRESS MemPhy, MemBasePhy;
    LM_UINT8 *pMemVirt, *pMemBase;
    PLM_PACKET pPacket;
    LM_STATUS Status;
    uint32_t Size;
    uint32_t align, j;

    /* Intialize the queues. */
    QQ_InitQueue(&pDevice->RxPacketReceivedQ.Container, 
        MAX_RX_PACKET_DESC_COUNT);
    QQ_InitQueue(&pDevice->RxPacketFreeQ.Container,
        MAX_RX_PACKET_DESC_COUNT);

    QQ_InitQueue(&pDevice->TxPacketFreeQ.Container,MAX_TX_PACKET_DESC_COUNT);
    QQ_InitQueue(&pDevice->TxPacketActiveQ.Container,MAX_TX_PACKET_DESC_COUNT);
    QQ_InitQueue(&pDevice->TxPacketXmittedQ.Container,MAX_TX_PACKET_DESC_COUNT);

    /* Allocate memory for packet descriptors. */
    Size = (pDevice->RxPacketDescCnt + 
        pDevice->TxPacketDescCnt) * B44_MM_PACKET_DESC_SIZE;
    Status = b44_MM_AllocateMemory(pDevice, Size, (PLM_VOID *) &pPacket);
    if(Status != LM_STATUS_SUCCESS)
    {
        return Status;
    }

    for(j = 0; j < pDevice->TxPacketDescCnt; j++)
    {
        QQ_PushTail(&pDevice->TxPacketFreeQ.Container, pPacket);

        pPacket = (PLM_PACKET) ((PLM_UINT8) pPacket + B44_MM_PACKET_DESC_SIZE);
    } /* for(j.. */

    for(j = 0; j < pDevice->RxPacketDescCnt; j++)
    {
        /* Receive buffer size. */
        pPacket->u.Rx.RxBufferSize = 1522 + pDevice->rxoffset;

        /* Add the descriptor to RxPacketFreeQ. */
        QQ_PushTail(&pDevice->RxPacketFreeQ.Container, pPacket);

        pPacket = (PLM_PACKET) ((PLM_UINT8) pPacket + B44_MM_PACKET_DESC_SIZE);
    } /* for */

    /* Initialize the rest of the packet descriptors. */
    Status = b44_MM_InitializeUmPackets(pDevice);
    if(Status != LM_STATUS_SUCCESS)
    {
        return Status;
    } /* if */

    Size = (pDevice->MaxRxPacketDescCnt + pDevice->TxPacketDescCnt) *
        sizeof(dmadd_t) + DMARINGALIGN;

    Status = b44_MM_AllocateSharedMemory(pDevice, Size, (PLM_VOID) &pMemBase, &MemBasePhy);
    if(Status != LM_STATUS_SUCCESS)
    {
        return Status;
    }

    MemPhy = (MemBasePhy + (DMARINGALIGN - 1)) & ~(DMARINGALIGN - 1);
    align = MemPhy - MemBasePhy;
    pMemVirt = pMemBase + align;

    pDevice->pRxDesc = (dmadd_t *) pMemVirt;
    pDevice->RxDescPhy = MemPhy;

    pMemVirt += pDevice->MaxRxPacketDescCnt * sizeof(dmadd_t);
    MemPhy += pDevice->MaxRxPacketDescCnt * sizeof(dmadd_t);

    pDevice->pTxDesc = (dmadd_t *) pMemVirt;
    pDevice->TxDescPhy = MemPhy;

    pMemVirt += pDevice->TxPacketDescCnt * sizeof(dmadd_t);
    MemPhy += pDevice->MaxRxPacketDescCnt * sizeof(dmadd_t);

    /* Initialize the hardware. */
    Status = b44_LM_ResetAdapter(pDevice);
    if(Status != LM_STATUS_SUCCESS)
    {
        return Status;
    }

    /* We are done with initialization. */
    pDevice->InitDone = TRUE;

    return LM_STATUS_SUCCESS;
} /* LM_InitializeAdapter */


LM_STATUS
b44_LM_DisableChip(PLM_DEVICE_BLOCK pDevice)
{
    return LM_STATUS_SUCCESS;
}

/******************************************************************************/
/* Description:                                                               */
/*    This function reinitializes the adapter.                                */
/*                                                                            */
/* Return:                                                                    */
/*    LM_STATUS_SUCCESS                                                       */
/******************************************************************************/
LM_STATUS
b44_LM_ResetAdapter(
PLM_DEVICE_BLOCK pDevice)
{

    /* Disable interrupt. */
    b44_LM_DisableInterrupt(pDevice);

    /* Disable transmit and receive DMA engines.  Abort all pending requests. */
    if(pDevice->InitDone)
    {
        b44_LM_Abort(pDevice);
    }

    pDevice->ShuttingDown = FALSE;

    ASSERT(b44_LM_sb_coreid(pDevice) == SB_ENET);

    pDevice->corerev = b44_LM_sb_corerev(pDevice);

    pDevice->sbmap = bcm4402;

    pDevice->coreunit = b44_LM_sb_coreunit(pDevice);

    /* enable pci interrupts, bursts, and prefetch */
    ASSERT((pDevice->coreunit == 0) || (pDevice->coreunit == 1));
    pDevice->pcirev = b44_LM_sb_pci_setup(pDevice,
        ((pDevice->coreunit == 0)? SBIV_ENET0: SBIV_ENET1));

    pDevice->ddoffset = pDevice->dataoffset =
        b44_LM_getsbaddr(pDevice, SBID_PCI_DMA, 0);

    b44_LM_ResetChip(pDevice);

#if 1
    if (pDevice->InitDone != TRUE) {
        if (pDevice->MdcPort == pDevice->coreunit) {
            b44_LM_ResetPhy(pDevice);
            b44_LM_SetupPhy(pDevice);
        }
    }
#endif

    b44_LM_SetMacAddress(pDevice, pDevice->NodeAddress);

    /* enable crc32 generation */
    REG_OR(pDevice, emaccontrol, EMC_CG);

    REG_WR(pDevice, intrecvlazy, (pDevice->lazyrxfc << IRL_FC_SHIFT));
    if (pDevice->lazyrxfc > 1)
    {
        REG_OR(pDevice, intrecvlazy, (pDevice->lazyrxmult * pDevice->lazyrxfc));
    }

    /* enable 802.3x tx flow control (honor received PAUSE frames) */
//    REG_WR(pDevice, rxconfig, ERC_FE | ERC_UF);

    b44_LM_SetReceiveMask(pDevice, pDevice->ReceiveMask);

    /* set max frame lengths - account for possible vlan tag */
    REG_WR(pDevice, rxmaxlength, MAX_ETHERNET_PACKET_SIZE + 32);
    REG_WR(pDevice, txmaxlength, MAX_ETHERNET_PACKET_SIZE + 32);

    /* set tx watermark */
    REG_WR(pDevice, txwatermark, 56);

    /* initialize the tx and rx dma channels */
    /* clear tx descriptor ring */
    memset((void*)pDevice->pTxDesc, 0, (pDevice->TxPacketDescCnt *
        sizeof(dmadd_t)));

    REG_WR(pDevice, dmaregs.xmtcontrol, XC_XE);
    REG_WR(pDevice, dmaregs.xmtaddr, (pDevice->TxDescPhy +
        pDevice->ddoffset));

    /* clear rx descriptor ring */
    memset((void*)pDevice->pRxDesc, 0, (pDevice->MaxRxPacketDescCnt *
        sizeof(dmadd_t)));

    REG_WR(pDevice, dmaregs.rcvcontrol, ((pDevice->rxoffset <<
        RC_RO_SHIFT) | RC_RE));

    REG_WR(pDevice, dmaregs.rcvaddr, (pDevice->RxDescPhy +
        pDevice->ddoffset));

    /* Queue Rx packet buffers. */
    b44_LM_QueueRxPackets(pDevice);

    /* turn on the emac */
    REG_OR(pDevice, enetcontrol, EC_EE);

    return LM_STATUS_SUCCESS;
} /* LM_ResetAdapter */





/******************************************************************************/
/* Description:                                                               */
/*    Disable the interrupt and put the transmitter and receiver engines in   */
/*    an idle state.  Also aborts all pending send requests and receive       */
/*    buffers.                                                                */
/*                                                                            */
/* Return:                                                                    */
/*    LM_STATUS_SUCCESS                                                       */
/******************************************************************************/
LM_STATUS
b44_LM_Abort(
PLM_DEVICE_BLOCK pDevice)
{
    PLM_PACKET pPacket;
    uint32_t rxin;

    b44_LM_DisableInterrupt(pDevice);

    b44_LM_DisableChip(pDevice);

    /* Abort packets that have already queued to go out. */
    pPacket = (PLM_PACKET) QQ_PopHead(&pDevice->TxPacketActiveQ.Container);
    while(pPacket)
    {

        pPacket->PacketStatus = LM_STATUS_TRANSMIT_ABORTED;

        atomic_add(pPacket->u.Tx.FragCount, &pDevice->SendDescLeft);

        QQ_PushTail(&pDevice->TxPacketXmittedQ.Container, pPacket);

        pPacket = (PLM_PACKET) 
            QQ_PopHead(&pDevice->TxPacketActiveQ.Container);
    }

    if(!pDevice->ShuttingDown)
    {
        /* Indicate packets to the protocol. */
        b44_MM_IndicateTxPackets(pDevice);

        /* Indicate received packets to the protocols. */
        b44_MM_IndicateRxPackets(pDevice);
    }
    else
    {
        /* Move the receive packet descriptors in the ReceivedQ to the */
        /* free queue. */
        for(; ;)
        {
            pPacket = (PLM_PACKET) QQ_PopHead(
                &pDevice->RxPacketReceivedQ.Container);
            if(pPacket == NULL)
            {
                break;
            }
            QQ_PushTail(&pDevice->RxPacketFreeQ.Container, pPacket);
        }
    }

    /* Clean up the Receive desc ring. */

    rxin = pDevice->rxin;
    while(rxin != pDevice->rxout) {
        pPacket = pDevice->RxPacketArr[rxin];

        QQ_PushTail(&pDevice->RxPacketFreeQ.Container, pPacket);

        rxin = (rxin + 1) & (pDevice->MaxRxPacketDescCnt - 1);
    } /* while */

    pDevice->rxin = rxin;
    return LM_STATUS_SUCCESS;
} /* LM_Abort */



/******************************************************************************/
/* Description:                                                               */
/*    Disable the interrupt and put the transmitter and receiver engines in   */
/*    an idle state.  Aborts all pending send requests and receive buffers.   */
/*    Also free all the receive buffers.                                      */
/*                                                                            */
/* Return:                                                                    */
/*    LM_STATUS_SUCCESS                                                       */
/******************************************************************************/
LM_STATUS
b44_LM_Halt(PLM_DEVICE_BLOCK pDevice)
{
    PLM_PACKET pPacket;
    uint32_t EntryCnt;

    b44_LM_Abort(pDevice);

    /* Get the number of entries in the queue. */
    EntryCnt = QQ_GetEntryCnt(&pDevice->RxPacketFreeQ.Container);

    /* Make sure all the packets have been accounted for. */
    for(EntryCnt = 0; EntryCnt < pDevice->RxPacketDescCnt; EntryCnt++)
    {
        pPacket = (PLM_PACKET) QQ_PopHead(&pDevice->RxPacketFreeQ.Container);
        if (pPacket == 0)
            break;

        b44_MM_FreeRxBuffer(pDevice, pPacket);

        QQ_PushTail(&pDevice->RxPacketFreeQ.Container, pPacket);
    }

    b44_LM_ResetChip(pDevice);

    /* Reprogram the MAC address. */
    b44_LM_SetMacAddress(pDevice, pDevice->NodeAddress);

    return LM_STATUS_SUCCESS;
} /* LM_Halt */


STATIC LM_STATUS
b44_LM_ResetChip(LM_DEVICE_BLOCK *pDevice)
{
	if (!b44_LM_sb_iscoreup(pDevice)) {
		b44_LM_sb_pci_setup(pDevice, 
			((pDevice->coreunit == 0)? SBIV_ENET0: SBIV_ENET1));	
		/* power on reset: reset the enet core */
		b44_LM_sb_core_reset(pDevice);
		goto chipinreset;
	}

	/* read counters before resetting the chip */
	if (pDevice->mibgood)
		b44_LM_StatsUpdate(pDevice);

	REG_WR(pDevice, intrecvlazy, 0);

	/* disable emac */
	REG_WR(pDevice, enetcontrol, EC_ED);
	SPINWAIT((REG_RD(pDevice, enetcontrol) & EC_ED), 100);

	/* reset the dma engines */
	REG_WR(pDevice, dmaregs.xmtcontrol, 0);
	pDevice->txin = pDevice->txout = 0;
	atomic_set(&pDevice->SendDescLeft, pDevice->TxPacketDescCnt - 1);

	if (REG_RD(pDevice, dmaregs.rcvstatus) & RS_RE_MASK) {
		/* wait until channel is idle or stopped */
		SPINWAIT(!(REG_RD(pDevice, dmaregs.rcvstatus) & RS_RS_IDLE),
			100);
	}

	REG_WR(pDevice, dmaregs.rcvcontrol, 0);
	pDevice->rxin = pDevice->rxout = 0;

	b44_LM_sb_core_reset(pDevice);

chipinreset:
	b44_LM_ClearStats(pDevice);

	/*
	 * We want the phy registers to be accessible even when
	 * the driver is "downed" so initialize MDC preamble, frequency,
	 * and whether internal or external phy here.
	 */
		/* 4402 has 62.5Mhz SB clock and internal phy */
	REG_WR(pDevice, mdiocontrol, 0x8d);

	/* some chips have internal phy, some don't */
	if (!(REG_RD(pDevice, devcontrol) & DC_IP)) {
		REG_WR(pDevice, enetcontrol, EC_EP);
	} else if (REG_RD(pDevice, devcontrol) & DC_ER) {
		REG_AND(pDevice, devcontrol, ~DC_ER);

		b44_MM_Wait(100);

	}

	/* clear persistent sw intstatus */
	pDevice->intstatus = 0;
	return LM_STATUS_SUCCESS;
}



/* reset and re-enable a core */
void
b44_LM_sb_core_reset(LM_DEVICE_BLOCK *pDevice)
{
	volatile uint32_t dummy;

	/*
	 * Must do the disable sequence first to work for arbitrary current core state.
	 */
	b44_LM_sb_core_disable(pDevice);

	/*
	 * Now do the initialization sequence.
	 */

	/* set reset while enabling the clock and forcing them on throughout the core */
	REG_WR(pDevice, sbconfig.sbtmstatelow,
		(SBTML_FGC | SBTML_CLK | SBTML_RESET));

	dummy = REG_RD(pDevice, sbconfig.sbtmstatelow);
	b44_MM_Wait(1);

	/* PR3158 workaround - not fixed in any chip yet */
	if (REG_RD(pDevice, sbconfig.sbtmstatehigh) & SBTMH_SERR) {
		printf("SBTMH_SERR; clearing...\n");
		REG_WR(pDevice, sbconfig.sbtmstatehigh, 0);
		ASSERT(0);
	}
	if ((dummy = REG_RD(pDevice, sbconfig.sbimstate)) &
		(SBIM_IBE | SBIM_TO)) {

		REG_AND(pDevice, sbconfig.sbimstate, ~(SBIM_IBE | SBIM_TO));
		ASSERT(0);
	}

	/* clear reset and allow it to propagate throughout the core */
	REG_WR(pDevice, sbconfig.sbtmstatelow, (SBTML_FGC | SBTML_CLK));
	dummy = REG_RD(pDevice, sbconfig.sbtmstatelow);
	b44_MM_Wait(1);

	/* leave clock enabled */
	REG_WR(pDevice, sbconfig.sbtmstatelow, SBTML_CLK);
	dummy = REG_RD(pDevice, sbconfig.sbtmstatelow);
	b44_MM_Wait(1);
}

void
b44_LM_sb_core_disable(LM_DEVICE_BLOCK *pDevice)
{
	volatile uint32_t dummy;

	/* must return if core is already in reset */
	if (REG_RD(pDevice, sbconfig.sbtmstatelow) & SBTML_RESET)
		return;
	
	/* set the reject bit */
	REG_WR(pDevice, sbconfig.sbtmstatelow, (SBTML_CLK | SBTML_REJ));

	/* spin until reject is set */
	while ((REG_RD(pDevice, sbconfig.sbtmstatelow) & SBTML_REJ) == 0)
		b44_MM_Wait(1);

	/* spin until sbtmstatehigh.busy is clear */
	while (REG_RD(pDevice, sbconfig.sbtmstatehigh) & SBTMH_BUSY)
		b44_MM_Wait(1);

	/* set reset and reject while enabling the clocks */
	REG_WR(pDevice, sbconfig.sbtmstatelow,
		(SBTML_FGC | SBTML_CLK | SBTML_REJ | SBTML_RESET));

	dummy = REG_RD(pDevice, sbconfig.sbtmstatelow);
	b44_MM_Wait(10);

	/* leave reset and reject asserted */
	REG_WR(pDevice, sbconfig.sbtmstatelow, (SBTML_REJ | SBTML_RESET));
	b44_MM_Wait(1);
}

/*
 * Configure the pci core for pci client (NIC) action
 * and return the pci core revision.
 */
uint32_t
b44_LM_sb_pci_setup(LM_DEVICE_BLOCK *pDevice, uint32_t cores)
{
	uint32_t bar0window;
	sbpciregs_t *pciregs;
	uint32_t pcirev;

	pciregs = (sbpciregs_t *) pDevice->pMemView;

	/* save bar0window */
	b44_MM_ReadConfig32(pDevice, PCI_BAR0_WIN, &bar0window);
	/* point bar0 at pci core registers */
	b44_MM_WriteConfig32(pDevice, PCI_BAR0_WIN, b44_LM_getsbaddr(pDevice,
		SBID_REG_PCI, 0));

	ASSERT(b44_LM_sb_coreid(pDevice) == SB_PCI);

	pcirev = b44_LM_sb_corerev(pDevice);

	/* enable sb->pci interrupts */
	REG_OR(pDevice, sbconfig.sbintvec, cores);

	/* enable prefetch and bursts for sonics-to-pci translation 2 */
	REG_WR_OFFSET(pDevice, OFFSETOF(sbpciregs_t, sbtopci2),
		REG_RD_OFFSET(pDevice, OFFSETOF(sbpciregs_t, sbtopci2)) |
		(SBTOPCI_PREF|SBTOPCI_BURST));

	/* restore bar0window */
	b44_MM_WriteConfig32(pDevice, PCI_BAR0_WIN, bar0window);

	return (pcirev);
}

/*
 * Return the SB address corresponding to core <id> instance <coreunit>.
 * Provide a layer of indirection between SB address map elements
 * and the individual chip maps.
 */
uint32_t
b44_LM_getsbaddr(LM_DEVICE_BLOCK *pDevice, uint32_t id, uint32_t coreunit)
{
	struct sbmap *sbmap;
	int i;

	sbmap = pDevice->sbmap;
	ASSERT(sbmap);

	for (i = 0; i < SBID_MAX; i++)
		if ((id == sbmap[i].id) && (coreunit == sbmap[i].coreunit))
			return (sbmap[i].sbaddr);

	ASSERT(0);
	return (0xdeadbeef);
}

uint32_t
b44_LM_sb_base(uint32_t admatch)
{
	uint32_t base;
	uint32_t type;

	type = admatch & SBAM_TYPE_MASK;
	ASSERT(type < 3);

	base = 0;

	if (type == 0) {
		base = admatch & SBAM_BASE0_MASK;
	} else if (type == 1) {
		ASSERT(admatch & SBAM_ADEN);
		ASSERT(!(admatch & SBAM_ADNEG));	/* neg not supported */
		base = admatch & SBAM_BASE1_MASK;
	} else if (type == 2) {
		ASSERT(admatch & SBAM_ADEN);
		ASSERT(!(admatch & SBAM_ADNEG));	/* neg not supported */
		base = admatch & SBAM_BASE2_MASK;
	}

	return (base);
}

uint32_t
b44_LM_sb_size(uint32_t admatch)
{
	uint32_t size;
	uint32_t type;

	type = admatch & SBAM_TYPE_MASK;
	ASSERT(type < 3);

	size = 0;

	if (type == 0) {
		size = 1 << (((admatch & SBAM_ADINT0_MASK) >> SBAM_ADINT0_SHIFT) + 1);
	} else if (type == 1) {
		ASSERT(admatch & SBAM_ADEN);
		ASSERT(!(admatch & SBAM_ADNEG));	/* neg not supported */
		size = 1 << (((admatch & SBAM_ADINT1_MASK) >> SBAM_ADINT1_SHIFT) + 1);
	} else if (type == 2) {
		ASSERT(admatch & SBAM_ADEN);
		ASSERT(!(admatch & SBAM_ADNEG));	/* neg not supported */
		size = 1 << (((admatch & SBAM_ADINT2_MASK) >> SBAM_ADINT2_SHIFT) + 1);
	}

	return (size);
}

/* return the core instance number of this core */
uint32_t
b44_LM_sb_coreunit(LM_DEVICE_BLOCK *pDevice)
{
	struct sbmap *sbmap;
	uint32_t base;
	int i;

	sbmap = pDevice->sbmap;
	ASSERT(sbmap);

	base = b44_LM_sb_base(REG_RD(pDevice, sbconfig.sbadmatch0));

	for (i = 0; i < SBID_MAX; i++)
		if (base == sbmap[i].sbaddr)
			return (sbmap[i].coreunit);

	ASSERT(0);
	return (0xdeadbeef);
}


uint32_t
b44_LM_sb_clock(LM_DEVICE_BLOCK *pDevice, uint32_t extifva)
{
	ASSERT(0);	/* XXX TBD */
	return (0);
}

uint32_t
b44_LM_sb_coreid(LM_DEVICE_BLOCK *pDevice)
{
	return ((REG_RD(pDevice, sbconfig.sbidhigh) &
		SBIDH_CC_MASK) >> SBIDH_CC_SHIFT);
}

uint32_t
b44_LM_sb_corerev(LM_DEVICE_BLOCK *pDevice)
{
	return (REG_RD(pDevice, sbconfig.sbidhigh) & SBIDH_RC_MASK);
}

uint32_t
b44_LM_sb_iscoreup(LM_DEVICE_BLOCK *pDevice)
{
	return ((REG_RD(pDevice, sbconfig.sbtmstatelow) &
		(SBTML_RESET | SBTML_REJ | SBTML_CLK)) == SBTML_CLK);
}

