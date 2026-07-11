static uint16_t mtd803_eeprom[] = {
	0x7310, 0x0083, 0x0000, 0x0000,
	0x4020, 0x1516, 0x0803, 0x0000,
#ifdef notdef
	0x0200, 0xb02a, 0x9927, 0x0000,
	0x0200, 0xb02a, 0x9927, 0x0000,
#else
	0x1202, 0x5634, 0x9a78, 0x0000,
	0x1202, 0x5634, 0x9a78, 0x0000,
#endif
	0x00f2, 0x0000, 0xffff, 0xffff,
	0xffff, 0xffff, 0xffff, 0xffff,
	0xffff, 0xffff, 0xffff, 0xffff,
	0xffff, 0xffff, 0xffff, 0xffff,

	0xffff, 0xffff, 0xffff, 0xffff,
	0xffff, 0xffff, 0xffff, 0xffff,
	0xffff, 0xffff, 0xffff, 0xffff,
	0xffff, 0xffff, 0xffff, 0xffff,

	0xffff, 0xffff, 0xffff, 0xffff,
	0xffff, 0xffff, 0xffff, 0xffff,
	0xffff, 0xffff, 0xffff, 0xffff,
	0xffff, 0xffff, 0xffff, 0xffff,
};

static uint16_t
mtd_write_eeprom(struct gem_dev *dp, int addr, uint16_t val)
{
	int		i;
	int		addr_bits;
	uint32_t	cmd;
	uint32_t	chip_select;
	uint32_t	di;
	uint32_t	ret;
	struct mtd_dev	*lp = (struct mtd_dev *)dp->private;

	addr_bits = 6;

	DPRINTF(2, (CE_CONT, "!%s: %s: called: addr:%x, val:%04x",
			dp->name, __func__, addr, val));

	/* make command bits */
	cmd = (((5 << addr_bits) | addr) << 16) | val;

	/* enable eeprom interface register */
	chip_select = SROM_DPM;
	OUTB(dp, SROM_CR, chip_select);

	chip_select |= SROM_ECS;
	OUTB(dp, SROM_CR, chip_select);
	MTD_EEPROM_DELAY(dp);

	/* output eeprom command */
	for (i = (3 + addr_bits + 16) -1; i >= 0; i--) {
		di = ((cmd >> i) & 1) << SROM_EDI_SHIFT;
		OUTB(dp, SROM_CR, chip_select | di);
		MTD_EEPROM_DELAY(dp);

		OUTB(dp, SROM_CR, chip_select | di | SROM_ECK);
		MTD_EEPROM_DELAY(dp);
	}

	/* release clock but keep chip_select asserted */
	OUTB(dp, SROM_CR, chip_select);
	MTD_EEPROM_DELAY(dp);

	/* Terminate the EEPROM access. */
	OUTB(dp, SROM_CR, SROM_DPM);
	MTD_EEPROM_DELAY(dp);

	OUTB(dp, SROM_CR, chip_select);
	drv_usecwait(10);

	/*
	 * Ensure EEPROM busy
	 */
	i = 1500;
	while ((INL(dp, SROM_CR) & SROM_EDO) != 0) {
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
	while ((INL(dp, SROM_CR) & SROM_EDO) == 0) {
		drv_usecwait(10);
		i--;
		if (i < 0) {
			cmn_err(CE_CONT, "!%s: %s: doesn't become ready",
				dp->name, __func__);
		}
		return;
	}

	/* Terminate the EEPROM access. */
	OUTB(dp, SROM_CR, 0);
	MTD_EEPROM_DELAY(dp);

	DPRINTF(2, (CE_CONT, "!%s: %s: returned 0x%x",
		dp->name, __func__, ret));

	return ret;
}

static uint16_t
mtd_erase_eeprom(struct gem_dev *dp, int addr)
{
	int		i;
	int		addr_bits;
	uint32_t	cmd;
	uint32_t	chip_select;
	uint32_t	di;
	uint32_t	ret;
	struct mtd_dev	*lp = (struct mtd_dev *)dp->private;

	addr_bits = 6;

	DPRINTF(2, (CE_CONT, "!%s: %s: called: addr:%x",
			dp->name, __func__, addr));

	/* make command bits for erase */
	cmd = (7 << addr_bits) | addr;

	/* enable eeprom intemtdace register */
	chip_select = SROM_DPM;
	OUTB(dp, SROM_CR, chip_select);

	chip_select |= SROM_ECS;
	OUTB(dp, SROM_CR, chip_select);
	MTD_EEPROM_DELAY(dp);

	/* output eeprom command */
	for (i = (3 + addr_bits) -1; i >= 0; i--) {
		di = ((cmd >> i) & 1) << SROM_EDI_SHIFT;
		OUTB(dp, SROM_CR, chip_select | di);
		MTD_EEPROM_DELAY(dp);

		OUTB(dp, SROM_CR, chip_select | di | SROM_ECK);
		MTD_EEPROM_DELAY(dp);
	}

	/* release clock but keep chip_select asserted */
	OUTB(dp, SROM_CR, chip_select);
	MTD_EEPROM_DELAY(dp);

	/* Terminate the EEPROM access. */
	OUTB(dp, SROM_CR, SROM_DPM);
	MTD_EEPROM_DELAY(dp);

	OUTB(dp, SROM_CR, chip_select);
	drv_usecwait(10);

	/*
	 * Ensure EEPROM busy
	 */
	i = 1500;
	while ((INL(dp, SROM_CR) & SROM_EDO) != 0) {
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
	while ((INL(dp, SROM_CR) & SROM_EDO) == 0) {
		drv_usecwait(10);
		i--;
		if (i < 0) {
			cmn_err(CE_CONT, "!%s: %s: doesn't become ready",
				dp->name, __func__);
		}
		return;
	}

	/* Terminate the EEPROM access. */
	OUTB(dp, SROM_CR, SROM_DPM);
	MTD_EEPROM_DELAY(dp);

	OUTB(dp, SROM_CR, 0);
	MTD_EEPROM_DELAY(dp);

	DPRINTF(2, (CE_CONT, "!mtd_read_eeprom: returned 0x%x", ret));

	return ret;
}

#define	WDS	0x00
#define	WEN	0x30

static void
mtd_control_eeprom(struct gem_dev *dp, uint_t cmd)
{
	int		i;
	int		addr_bits;
	uint32_t	chip_select;
	uint32_t	di;
	uint32_t	ret;
	struct mtd_dev	*lp = (struct mtd_dev *)dp->private;

	addr_bits = 6;

	DPRINTF(2, (CE_CONT, "!%s: %s: called: addr_bits:%d",
			dp->name, __func__, addr_bits));

	/* make command bits */
	cmd = (4 << addr_bits) | cmd;

	/* enable eeprom interface register */
	chip_select = SROM_DPM;
	OUTB(dp, SROM_CR, chip_select);

	chip_select |= SROM_ECS;
	OUTB(dp, SROM_CR, chip_select);
	MTD_EEPROM_DELAY(dp);

	/* output eeprom command */
	for (i = (3 + addr_bits)-1; i >= 0; i--) {
		di = ((cmd >> i) & 1) << SROM_EDI_SHIFT;
		OUTB(dp, SROM_CR, chip_select | di);
		MTD_EEPROM_DELAY(dp);

		OUTB(dp, SROM_CR, chip_select | di | SROM_ECK);
		MTD_EEPROM_DELAY(dp);
	}

	/* release clock but keep chip_select asserted */
	OUTB(dp, SROM_CR, chip_select);
	MTD_EEPROM_DELAY(dp);

	/* Terminate the EEPROM access. */
	OUTB(dp, SROM_CR, 0);
	OUTB(dp, SROM_CR, 0);
	MTD_EEPROM_DELAY(dp);

	DPRINTF(0, (CE_CONT, "!%s: %s: returned", dp->name, __func__));

	return;
}

