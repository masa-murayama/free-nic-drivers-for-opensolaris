#define TU_EEPROM_DELAY(dp)   {INL(dp, SPR); INL(dp, SPR);}

static uint8_t dm9102_eeprom[128] = {
	0x91, 0x02,
	0x12, 0x82,
	0x00, 0x00, 0x00, 0x00,
	0x00,
	0x00,
	0x82, 0x12,
	0x02, 0x91,
	0x00,
	0x00,
	0x00,
	0x00,

	0x03,
	0x01,

	0x02, 0x10, 0x20, 0x30, 0x40, 0x50,
	0x00,
	0x1e, 0x00,
	0x00,

	0x00, 0x08,
	0x80,
	0x06,

	0x8e,
	0x01,
	0x01,
	0x00,
	0x02,
	0x80, 0x00,
	0x00, 0x78,
	0xe0, 0x01,
	0x00, 0x50,
	0x00, 0x18,

	0x85,
	0x80,
	0x00, 0x20, 0x00, 0x40,

	0x85,
	0x00,
	0x00,
	0x00,
	0x87, 0x00,

	0x85,
	0x00,
	0x01,
	0x00,
	0x87, 0x00,

	0x85,
	0x00,
	0x04,
	0x00,
	0x87, 0x00,

	0x85,
	0x00,
	0x05,
	0x00,
	0x87, 0x00,
};

static uint16_t
tu_write_eeprom(struct gem_dev *dp, int addr, uint16_t val)
{
	int		i;
	int		addr_bits;
	uint32_t	cmd;
	uint32_t	chip_select;
	uint32_t	di;
	uint32_t	ret;
	struct tu_dev	*lp = (struct tu_dev *)dp->private;

	addr_bits = 6;

	DPRINTF(2, (CE_CONT, "!%s: %s: called: addr:%x, val:%04x",
			dp->name, __func__, addr, val));

	/* make command bits */
	cmd = (((5 << addr_bits) | addr) << 16) | val;

	/* enable eeprom interface register */
	chip_select = SPR_SRC | SPR_SRS;
	OUTL(dp, SPR, chip_select);

	chip_select |= SPR_SCS;
	OUTL(dp, SPR, chip_select);
	TU_EEPROM_DELAY(dp);

	/* output eeprom command */
	for (i = (3 + addr_bits + 16) -1; i >= 0; i--) {
		di = ((cmd >> i) & 1) << SPR_SDI_SHIFT;
		OUTL(dp, SPR, chip_select | di);
		TU_EEPROM_DELAY(dp);

		OUTL(dp, SPR, chip_select | di | SPR_SCLK);
		TU_EEPROM_DELAY(dp);
	}

	/* release clock but keep chip_select asserted */
	OUTL(dp, SPR, chip_select);
	TU_EEPROM_DELAY(dp);

	/* Terminate the EEPROM access. */
	OUTL(dp, SPR, SPR_SRC | SPR_SRS);
	TU_EEPROM_DELAY(dp);

	OUTL(dp, SPR, chip_select);
	drv_usecwait(10);

	/*
	 * Ensure EEPROM busy
	 */
	i = 1500;
	while ((INL(dp, SPR) & SPR_SDO) != 0) {
		drv_usecwait(10);
		i--;
		if (i < 0) {
			cmn_err(CE_CONT, "!%s: %s: doesn't become busy",
				dp->name, __func__);

		}
		return;
	}

	/* wait eeprom ready */
	i = 15000;
	while ((INL(dp, SPR) & SPR_SDO) == 0) {
		drv_usecwait(10);
		i--;
		if (i < 0) {
			cmn_err(CE_CONT, "!%s: %s: doesn't become ready",
				dp->name, __func__);
		}
		return;
	}

	/* Terminate the EEPROM access. */
	OUTL(dp, SPR, 0);
	TU_EEPROM_DELAY(dp);

	DPRINTF(2, (CE_CONT, "!%s: %s: returned 0x%x",
		dp->name, __func__, ret));

	return ret;
}

static uint16_t
tu_erase_eeprom(struct gem_dev *dp, int addr)
{
	int		i;
	int		addr_bits;
	uint32_t	cmd;
	uint32_t	chip_select;
	uint32_t	di;
	uint32_t	ret;
	struct tu_dev	*lp = (struct tu_dev *)dp->private;

	addr_bits = 6;

	DPRINTF(2, (CE_CONT, "!%s: %s: called: addr:%x",
			dp->name, __func__, addr));

	/* make command bits for erase */
	cmd = (7 << addr_bits) | addr;

	/* enable eeprom intetuace register */
	chip_select = SPR_SRC | SPR_SRS;
	OUTL(dp, SPR, chip_select);

	chip_select |= SPR_SCS;
	OUTL(dp, SPR, chip_select);
	TU_EEPROM_DELAY(dp);

	/* output eeprom command */
	for (i = (3 + addr_bits) -1; i >= 0; i--) {
		di = ((cmd >> i) & 1) << SPR_SDI_SHIFT;
		OUTL(dp, SPR, chip_select | di);
		TU_EEPROM_DELAY(dp);

		OUTL(dp, SPR, chip_select | di | SPR_SCLK);
		TU_EEPROM_DELAY(dp);
	}

	/* release clock but keep chip_select asserted */
	OUTL(dp, SPR, chip_select);
	TU_EEPROM_DELAY(dp);

	/* Terminate the EEPROM access. */
	OUTL(dp, SPR, SPR_SRC | SPR_SRS);
	TU_EEPROM_DELAY(dp);

	OUTL(dp, SPR, chip_select);
	drv_usecwait(10);

	/*
	 * Ensure EEPROM busy
	 */
	i = 1500;
	while ((INL(dp, SPR) & SPR_SDO) != 0) {
		drv_usecwait(10);
		i--;
		if (i < 0) {
			cmn_err(CE_CONT, "%s: %s: doesn't become busy",
				dp->name, __func__);
		}
		return;
	}

	/* wait eeprom ready */
	i = 15000;
	while ((INL(dp, SPR) & SPR_SDO) == 0) {
		drv_usecwait(10);
		i--;
		if (i < 0) {
			cmn_err(CE_CONT, "!%s: %s: doesn't become ready",
				dp->name, __func__);
		}
		return;
	}

	/* Terminate the EEPROM access. */
	OUTL(dp, SPR, SPR_SRC | SPR_SRS);
	TU_EEPROM_DELAY(dp);

	OUTL(dp, SPR, 0);
	TU_EEPROM_DELAY(dp);

	DPRINTF(2, (CE_CONT, "!tu_read_eeprom: returned 0x%x", ret));

	return ret;
}

#define	WDS	0x00
#define	WEN	0x30

static void
tu_control_eeprom(struct gem_dev *dp, uint_t cmd)
{
	int		i;
	int		addr_bits;
	uint32_t	chip_select;
	uint32_t	di;
	uint32_t	ret;
	struct tu_dev	*lp = (struct tu_dev *)dp->private;

	addr_bits = 6;

	DPRINTF(2, (CE_CONT, "!%s: %s: called: addr_bits:%d",
			dp->name, __func__, addr_bits));

	/* make command bits */
	cmd = (4 << addr_bits) | cmd;

	/* enable eeprom interface register */
	chip_select = SPR_SRC | SPR_SRS;
	OUTL(dp, SPR, chip_select);

	chip_select |= SPR_SCS;
	OUTL(dp, SPR, chip_select);
	TU_EEPROM_DELAY(dp);

	/* output eeprom command */
	for (i = (3 + addr_bits)-1; i >= 0; i--) {
		di = ((cmd >> i) & 1) << SPR_SDI_SHIFT;
		OUTL(dp, SPR, chip_select | di);
		TU_EEPROM_DELAY(dp);

		OUTL(dp, SPR, chip_select | di | SPR_SCLK);
		TU_EEPROM_DELAY(dp);
	}

	/* release clock but keep chip_select asserted */
	OUTL(dp, SPR, chip_select);
	TU_EEPROM_DELAY(dp);

	/* Terminate the EEPROM access. */
	OUTL(dp, SPR, 0);
	OUTL(dp, SPR, 0);
	TU_EEPROM_DELAY(dp);

	DPRINTF(0, (CE_CONT, "!%s: %s: returned", dp->name, __func__));

	return;
}

