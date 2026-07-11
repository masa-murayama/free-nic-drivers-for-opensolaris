#include "b44reg.h"

#define	RD_REG(dp, x)	INL(dp, (int)(intptr_t)&((bcmenetregs_t *)NULL)->x)
#define	RD_SBREG(dp, x)	INL(dp, (int)(intptr_t)&((sbpciregs_t *)NULL)->x)
#define	RD_SBREG16(dp, x)	INW(dp, (int)(intptr_t)&((sbpciregs_t *)NULL)->x)

static void
bfe_dump_regs(struct gem_dev *dp)
{
	cmn_err(CE_CONT, "%s: %x\n", "devcontrol", RD_REG(dp, devcontrol));
	cmn_err(CE_CONT, "%s: %x\n", "biststatus", RD_REG(dp, biststatus));
	cmn_err(CE_CONT, "%s: %x\n", "wakeuplength", RD_REG(dp, wakeuplength));
	cmn_err(CE_CONT, "%s: %x\n", "intstatus", RD_REG(dp, intstatus));
	cmn_err(CE_CONT, "%s: %x\n", "intmask", RD_REG(dp, intmask));
	cmn_err(CE_CONT, "%s: %x\n", "gptimer", RD_REG(dp, gptimer));
	cmn_err(CE_CONT, "%s: %x\n", "enetftaddr", RD_REG(dp, enetftaddr));
	cmn_err(CE_CONT, "%s: %x\n", "enetftdata", RD_REG(dp, enetftdata));
	cmn_err(CE_CONT, "%s: %x\n", "emactxmaxburstlen", RD_REG(dp, emactxmaxburstlen));
	cmn_err(CE_CONT, "%s: %x\n", "emacrxmaxburstlen", RD_REG(dp, emacrxmaxburstlen));
	cmn_err(CE_CONT, "%s: %x\n", "emaccontrol", RD_REG(dp, emaccontrol));
	cmn_err(CE_CONT, "%s: %x\n", "emacflowcontrol", RD_REG(dp, emacflowcontrol));
	cmn_err(CE_CONT, "%s: %x\n", "intrecvlazy", RD_REG(dp, intrecvlazy));
	cmn_err(CE_CONT, "%s: %x\n", "dmaregs.xmtcontrol", RD_REG(dp, dmaregs.xmtcontrol));
	cmn_err(CE_CONT, "%s: %x\n", "dmaregs.xmtaddr", RD_REG(dp, dmaregs.xmtaddr));
	cmn_err(CE_CONT, "%s: %x\n", "dmaregs.xmtptr", RD_REG(dp, dmaregs.xmtptr));
	cmn_err(CE_CONT, "%s: %x\n", "dmaregs.xmtstatus", RD_REG(dp, dmaregs.xmtstatus));
	cmn_err(CE_CONT, "%s: %x\n", "dmaregs.rcvcontrol", RD_REG(dp, dmaregs.rcvcontrol));
	cmn_err(CE_CONT, "%s: %x\n", "dmaregs.rcvaddr", RD_REG(dp, dmaregs.rcvaddr));
	cmn_err(CE_CONT, "%s: %x\n", "dmaregs.rcvptr", RD_REG(dp, dmaregs.rcvptr));
	cmn_err(CE_CONT, "%s: %x\n", "dmaregs.rcvstatus", RD_REG(dp, dmaregs.rcvstatus));
	cmn_err(CE_CONT, "%s: %x\n", "dmaregs.fifoaddr", RD_REG(dp, dmaregs.fifoaddr));
	cmn_err(CE_CONT, "%s: %x\n", "dmaregs.fifodatalow", RD_REG(dp, dmaregs.fifodatalow));
	cmn_err(CE_CONT, "%s: %x\n", "dmaregs.fifodatahigh", RD_REG(dp, dmaregs.fifodatahigh));
	cmn_err(CE_CONT, "%s: %x\n", "rxconfig", RD_REG(dp, rxconfig));
	cmn_err(CE_CONT, "%s: %x\n", "rxmaxlength", RD_REG(dp, rxmaxlength));
	cmn_err(CE_CONT, "%s: %x\n", "txmaxlength", RD_REG(dp, txmaxlength));
	cmn_err(CE_CONT, "%s: %x\n", "mdiocontrol", RD_REG(dp, mdiocontrol));
	cmn_err(CE_CONT, "%s: %x\n", "mdiodata", RD_REG(dp, mdiodata));
	cmn_err(CE_CONT, "%s: %x\n", "emacintmask", RD_REG(dp, emacintmask));
	cmn_err(CE_CONT, "%s: %x\n", "emacintstatus", RD_REG(dp, emacintstatus));
	cmn_err(CE_CONT, "%s: %x\n", "camdatalo", RD_REG(dp, camdatalo));
	cmn_err(CE_CONT, "%s: %x\n", "camdatahi", RD_REG(dp, camdatahi));
	cmn_err(CE_CONT, "%s: %x\n", "camcontrol", RD_REG(dp, camcontrol));
	cmn_err(CE_CONT, "%s: %x\n", "enetcontrol", RD_REG(dp, enetcontrol));
	cmn_err(CE_CONT, "%s: %x\n", "txcontrol", RD_REG(dp, txcontrol));
	cmn_err(CE_CONT, "%s: %x\n", "txwatermark", RD_REG(dp, txwatermark));
	cmn_err(CE_CONT, "%s: %x\n", "sbconfig.sbipsflag", RD_REG(dp, sbconfig.sbipsflag));
	cmn_err(CE_CONT, "%s: %x\n", "sbconfig.sbtpsflag", RD_REG(dp, sbconfig.sbtpsflag));
	cmn_err(CE_CONT, "%s: %x\n", "sbconfig.sbadmatch3", RD_REG(dp, sbconfig.sbadmatch3));
	cmn_err(CE_CONT, "%s: %x\n", "sbconfig.sbadmatch2", RD_REG(dp, sbconfig.sbadmatch2));
	cmn_err(CE_CONT, "%s: %x\n", "sbconfig.sbadmatch1", RD_REG(dp, sbconfig.sbadmatch1));
	cmn_err(CE_CONT, "%s: %x\n", "sbconfig.sbimstate", RD_REG(dp, sbconfig.sbimstate));
	cmn_err(CE_CONT, "%s: %x\n", "sbconfig.sbintvec", RD_REG(dp, sbconfig.sbintvec));
	cmn_err(CE_CONT, "%s: %x\n", "sbconfig.sbtmstatelow", RD_REG(dp, sbconfig.sbtmstatelow));
	cmn_err(CE_CONT, "%s: %x\n", "sbconfig.sbtmstatehigh", RD_REG(dp, sbconfig.sbtmstatehigh));
	cmn_err(CE_CONT, "%s: %x\n", "sbconfig.sbbwa0", RD_REG(dp, sbconfig.sbbwa0));
	cmn_err(CE_CONT, "%s: %x\n", "sbconfig.sbimconfiglow", RD_REG(dp, sbconfig.sbimconfiglow));
	cmn_err(CE_CONT, "%s: %x\n", "sbconfig.sbimconfighigh", RD_REG(dp, sbconfig.sbimconfighigh));
	cmn_err(CE_CONT, "%s: %x\n", "sbconfig.sbadmatch0", RD_REG(dp, sbconfig.sbadmatch0));
	cmn_err(CE_CONT, "%s: %x\n", "sbconfig.sbtmconfiglow", RD_REG(dp, sbconfig.sbtmconfiglow));
	cmn_err(CE_CONT, "%s: %x\n", "sbconfig.sbtmconfighigh", RD_REG(dp, sbconfig.sbtmconfighigh));
	cmn_err(CE_CONT, "%s: %x\n", "sbconfig.sbbconfig", RD_REG(dp, sbconfig.sbbconfig));
	cmn_err(CE_CONT, "%s: %x\n", "sbconfig.sbbstate", RD_REG(dp, sbconfig.sbbstate));
	cmn_err(CE_CONT, "%s: %x\n", "sbconfig.sbactcnfg", RD_REG(dp, sbconfig.sbactcnfg));
	cmn_err(CE_CONT, "%s: %x\n", "sbconfig.sbflagst", RD_REG(dp, sbconfig.sbflagst));
	cmn_err(CE_CONT, "%s: %x\n", "sbconfig.sbidlow", RD_REG(dp, sbconfig.sbidlow));
	cmn_err(CE_CONT, "%s: %x\n", "sbconfig.sbidhigh", RD_REG(dp, sbconfig.sbidhigh));
}

static void
bfe_dump_miiregs(struct gem_dev *dp)
{
	int	i;
	int	save;

	save = dp->mii_phy_addr;
	dp->mii_phy_addr = 1;

	for (i = 0; i < 28; i++) {
		cmn_err(CE_CONT, "miireg%d: %04x", i, bfe_mii_read(dp, i));
	}

	dp->mii_phy_addr = save;
}

static void
bfe_dump_sbregs(struct gem_dev *dp)
{
	ddi_acc_handle_t	conf_handle;
	int			i;
	uint32_t		bar0win;

	/* the core isn't up now */
	if (pci_config_setup(dp->dip, &conf_handle) != DDI_SUCCESS) {
		cmn_err(CE_WARN,
		"!%s: %s: pci_config_setup failed",
			dp->name, __func__);
		return;
	}

	/*
	 * Change bar0window to map sbtopci registers
	 */
	bar0win = pci_config_get32(conf_handle, PCI_BAR0_WIN);
	DPRINTF(2, (CE_CONT, "!%s: bfe_reset_chip: bar0win:0x%x",
		dp->name, bar0win));
	pci_config_put32(conf_handle, PCI_BAR0_WIN, SB_PCI_BASE);


	cmn_err(CE_CONT, "%s: %x\n", "control", RD_SBREG(dp, control));
	cmn_err(CE_CONT, "%s: %x\n", "arbcontrol", RD_SBREG(dp, arbcontrol));
	cmn_err(CE_CONT, "%s: %x\n", "intstatus", RD_SBREG(dp, intstatus));
	cmn_err(CE_CONT, "%s: %x\n", "intmask", RD_SBREG(dp, intmask));
	cmn_err(CE_CONT, "%s: %x\n", "sbtopcimailbox", RD_SBREG(dp, sbtopcimailbox));
	cmn_err(CE_CONT, "%s: %x\n", "bcastaddr", RD_SBREG(dp, bcastaddr));
	cmn_err(CE_CONT, "%s: %x\n", "bcastdata", RD_SBREG(dp, bcastdata));
	cmn_err(CE_CONT, "%s: %x\n", "sbtopci0", RD_SBREG(dp, sbtopci0));
	cmn_err(CE_CONT, "%s: %x\n", "sbtopci1", RD_SBREG(dp, sbtopci1));
	cmn_err(CE_CONT, "%s: %x\n", "sbtopci2", RD_SBREG(dp, sbtopci2));
	cmn_err(CE_CONT, "%s:\n", "sprom[]");

	for (i = 0; i < 36; i++) {
		cmn_err(CE_CONT, "%x\n", RD_SBREG16(dp, sprom[i]));
	}

	cmn_err(CE_CONT, "%s: %x\n", "sbconfig.sbipsflag", RD_REG(dp, sbconfig.sbipsflag));
	cmn_err(CE_CONT, "%s: %x\n", "sbconfig.sbtpsflag", RD_REG(dp, sbconfig.sbtpsflag));
	cmn_err(CE_CONT, "%s: %x\n", "sbconfig.sbadmatch3", RD_REG(dp, sbconfig.sbadmatch3));
	cmn_err(CE_CONT, "%s: %x\n", "sbconfig.sbadmatch2", RD_REG(dp, sbconfig.sbadmatch2));
	cmn_err(CE_CONT, "%s: %x\n", "sbconfig.sbadmatch1", RD_REG(dp, sbconfig.sbadmatch1));
	cmn_err(CE_CONT, "%s: %x\n", "sbconfig.sbimstate", RD_REG(dp, sbconfig.sbimstate));
	cmn_err(CE_CONT, "%s: %x\n", "sbconfig.sbintvec", RD_REG(dp, sbconfig.sbintvec));
	cmn_err(CE_CONT, "%s: %x\n", "sbconfig.sbtmstatelow", RD_REG(dp, sbconfig.sbtmstatelow));
	cmn_err(CE_CONT, "%s: %x\n", "sbconfig.sbtmstatehigh", RD_REG(dp, sbconfig.sbtmstatehigh));
	cmn_err(CE_CONT, "%s: %x\n", "sbconfig.sbbwa0", RD_REG(dp, sbconfig.sbbwa0));
	cmn_err(CE_CONT, "%s: %x\n", "sbconfig.sbimconfiglow", RD_REG(dp, sbconfig.sbimconfiglow));
	cmn_err(CE_CONT, "%s: %x\n", "sbconfig.sbimconfighigh", RD_REG(dp, sbconfig.sbimconfighigh));
	cmn_err(CE_CONT, "%s: %x\n", "sbconfig.sbadmatch0", RD_REG(dp, sbconfig.sbadmatch0));
	cmn_err(CE_CONT, "%s: %x\n", "sbconfig.sbtmconfiglow", RD_REG(dp, sbconfig.sbtmconfiglow));
	cmn_err(CE_CONT, "%s: %x\n", "sbconfig.sbtmconfighigh", RD_REG(dp, sbconfig.sbtmconfighigh));
	cmn_err(CE_CONT, "%s: %x\n", "sbconfig.sbbconfig", RD_REG(dp, sbconfig.sbbconfig));
	cmn_err(CE_CONT, "%s: %x\n", "sbconfig.sbbstate", RD_REG(dp, sbconfig.sbbstate));
	cmn_err(CE_CONT, "%s: %x\n", "sbconfig.sbactcnfg", RD_REG(dp, sbconfig.sbactcnfg));
	cmn_err(CE_CONT, "%s: %x\n", "sbconfig.sbflagst", RD_REG(dp, sbconfig.sbflagst));
	cmn_err(CE_CONT, "%s: %x\n", "sbconfig.sbidlow", RD_REG(dp, sbconfig.sbidlow));
	cmn_err(CE_CONT, "%s: %x\n", "sbconfig.sbidhigh", RD_REG(dp, sbconfig.sbidhigh));

	/* restore bar0window mapping */
	pci_config_put32(conf_handle, PCI_BAR0_WIN, bar0win);

	pci_config_teardown(&conf_handle);
}

static void
bfe_dump_allregs(struct gem_dev *dp, char *title)
{
	cmn_err(CE_CONT, "%s: register dump: %s", dp->name, title);
	bfe_dump_regs(dp);
	bfe_dump_sbregs(dp);
	bfe_dump_miiregs(dp);
}

