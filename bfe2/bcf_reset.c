#include <sys/types.h>
#include <sys/conf.h>
#include <sys/debug.h>
#include <sys/stropts.h>
#include <sys/stream.h>
#include <sys/strlog.h>
#include <sys/kmem.h>
#include <sys/stat.h>
#include <sys/kstat.h>
#include <sys/vtrace.h>
#include <sys/dlpi.h>
#include <sys/strsun.h>
#include <sys/ethernet.h>
#include <sys/modctl.h>
#include <sys/errno.h>
#include <sys/ddi.h>
#include <sys/sunddi.h>
#include <sys/ddi_impldefs.h>

#include <sys/pci.h>
#include "mii.h"
#include "gem.h"
#include "bcm4400reg.h"

#define	FLUSH(dp, reg)	(void)INL(dp, reg)

#define	SBBASE_PCIDMA	0x40000000
#define	SBBASE_ENUM	0x18000000
#define	SBBASE_EMAC	0x18000000
#define	SBBASE_CODEC	0x18001000
#define	SBBASE_PCI	0x18002000

int
bcf_reset_core(struct gem_dev *dp)
{
	uint32_t val;

	/*
	 * Must do the disable sequence first to work for arbitrary
	 * current core state.
	 */
	if ((INL(dp, SBTMSTATELOW) & SBTML_RESET) == 0) {
		
		/* set the reject bit */
		OUTL(dp, SBTMSTATELOW, (SBTML_CLK | SBTML_REJ));

		/* spin until reject is set */
		while ((INL(dp, SBTMSTATELOW) & SBTML_REJ) == 0) {
			drv_usecwait(1);
		}

		/* spin until sbtmstatehigh.busy is clear */
		while (INL(dp, SBTMSTATEHIGH) & SBTMH_BUSY) {
			drv_usecwait(1);
		}

		/* set reset and reject while enabling the clocks */
		OUTL(dp, SBTMSTATELOW,
			(SBTML_FGC | SBTML_CLK | SBTML_REJ | SBTML_RESET));

		FLUSH(dp, SBTMSTATELOW);
		drv_usecwait(10);

		/* leave reset and reject asserted */
		OUTL(dp, SBTMSTATELOW, (SBTML_REJ | SBTML_RESET));
		drv_usecwait(1);
	}

	/*
	 * Now do the initialization sequence.
	 */

	/*
	 * set reset while enabling the clock and forcing them
	 * on throughout the core
	 */
	OUTL(dp, SBTMSTATELOW, (SBTML_FGC | SBTML_CLK | SBTML_RESET));
	FLUSH(dp, SBTMSTATELOW);
	drv_usecwait(1);

	/* PR3158 workaround - not fixed in any chip yet */
	if (INL(dp, SBTMSTATEHIGH) & SBTMH_SERR) {
		OUTL(dp, SBTMSTATEHIGH, 0);
		cmn_err(CE_WARN, "SBTMH_SERR; clearing...");
		return -1;
	}
	if ((val = INL(dp, SBIMSTATE)) & (SBIM_IBE | SBIM_TO)) {

		OUTL(dp, SBIMSTATE, val & ~(SBIM_IBE | SBIM_TO));
		cmn_err(CE_WARN, "sbimstate is not clear");
		return -1;
	}

	/* clear reset and allow it to propagate throughout the core */
	OUTL(dp, SBTMSTATELOW, (SBTML_FGC | SBTML_CLK));
	FLUSH(dp, SBTMSTATELOW);
	drv_usecwait(1);

	/* leave clock enabled */
	OUTL(dp, SBTMSTATELOW, SBTML_CLK);
	FLUSH(dp, SBTMSTATELOW);
	drv_usecwait(1);

	return 0;
}

int
bcf_init_pci(struct gem_dev *dp, uint32_t intrmask)
{
	uint32_t		bar0win;
	uint32_t		rev;
	ddi_acc_handle_t	conf_handle;

#ifdef TEST_POWERONRESET
	if ((INL(dp, SBTMSTATELOW) &
		(SBTML_RESET | SBTML_REJ | SBTML_CLK)) == SBTML_CLK) {
		/* do nothing as the core is up */
		cmn_err(CE_CONT, "sb_pci_setup: the core is up");
		return 0;
	}
#endif
	if (pci_config_setup(dp->dip, &conf_handle) != DDI_SUCCESS) {
		cmn_err(CE_WARN, "%s: sb_pci_setup: pci_config_setup failed",
			dp->name);
		return -1;
	}

	bar0win = pci_config_get32(conf_handle, PCI_BAR0_WIN);

	/* point bar0 at pci core registers */
	pci_config_put32(conf_handle, PCI_BAR0_WIN, SBBASE_PCI);

	if (SB_PCI != ((INL(dp, SBIDHIGH)&SBIDH_CC_MASK)>>SBIDH_CC_SHIFT)) {
		cmn_err(CE_WARN, "bcf_init_pci: core id is wrong");
	}

	/* enable sb->pci interrupts */
	OUTL(dp, SBINTVEC, INL(dp, SBINTVEC) | intrmask);

	/* enable prefetch and bursts for sonics-to-pci translation 2 */
#ifdef notdef
	((sbpciregs_t *)REG(dp))->sbtopci2 |= SBTOPCI_PREF | SBTOPCI_BURST;
	cmn_err(CE_CONT, "sbtopci2 is 0x%x", &((sbpciregs_t *)NULL)->sbtopci2);
#else
	OUTL(dp, SBTOPCI2, INL(dp, SBTOPCI2) | SBTOPCI_PREF | SBTOPCI_BURST);
#endif

	pci_config_put32(conf_handle, PCI_BAR0_WIN, bar0win);

	pci_config_teardown(&conf_handle);

	return;
}
