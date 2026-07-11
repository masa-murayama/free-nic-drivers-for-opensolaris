static uint16_t
rf_write_eeprom(struct gem_dev *dp, int addr, uint16_t val)
{
	int		i;
	int		addr_bits;
	uint32_t	cmd;
	uint8_t		chip_select;
	uint8_t		di;
	uint16_t	ret;
	struct rf_dev	*lp = (struct rf_dev *)dp->private;

	if (lp->chip->type == CHIP_8139B || lp->chip->type == CHIP_8139C ||
	    lp->chip->type == CHIP_8139CP) {
		/*
		 * eeprom 93C46 or 93C56: 8139B, 8139C, 8139CP
		 */
		addr_bits = ((INL(dp, RCR) & RCR_9356SEL) != 0) ? 8 : 6;
	}
	else {
		/*
		 * eeprom 93C46 : 8129, 8130, 8100, 8100B/8139D, 8101
		 */
		addr_bits = 6;
	}

	DPRINTF(2, (CE_CONT, "!%s: rf_read_eeprom: called: addr_bits:%d",
			dp->name, addr_bits));

	/* make command bits */
	cmd = (((5 << addr_bits) | addr) << 16) | val;

	/* enable eeprom interface register */
	chip_select = CR9346_EEM_PROGRAM;
	OUTB(dp, CR9346, chip_select);

	chip_select |= CR9346_EECS;
	OUTB(dp, CR9346, chip_select);
	rf_eeprom_delay(dp);

	/* output eeprom command */
	for (i = (3 + addr_bits + 16) -1 ; i >= 0; i--) {
		di = ((cmd >> i) & 1) << CR9346_EEDI_SHIFT;
		OUTB(dp, CR9346, chip_select | di);
		rf_eeprom_delay(dp);

		OUTB(dp, CR9346, chip_select | di | CR9346_EESK);
		rf_eeprom_delay(dp);
	}

	/* release clock but keep chip_select asserted */
	OUTB(dp, CR9346, chip_select);
	rf_eeprom_delay(dp);

	/* Terminate the EEPROM access. */
	OUTB(dp, CR9346, CR9346_EEM_PROGRAM);
	rf_eeprom_delay(dp);

	OUTB(dp, CR9346, chip_select);
	drv_usecwait(10);

	/*
	 * Ensure EEPROM busy
	 */
	i = 1500;
	while ((INB(dp, CR9346) & CR9346_EEDO) != 0) {
		drv_usecwait(10);
		i--;
		if (i < 0) {
			cmn_err(CE_CONT, "rf_write_eeprom: doesn't become busy");
		}
		return;
	}

	/* wait eeprom ready */
	i = 15000;
	while ((INB(dp, CR9346) & CR9346_EEDO) == 0) {
		drv_usecwait(10);
		i--;
		if (i < 0) {
			cmn_err(CE_CONT, "rf_write_eeprom: doesn't become ready");
		}
		return;
	}

	/* Terminate the EEPROM access. */
	OUTB(dp, CR9346, CR9346_EEM_PROGRAM);
	rf_eeprom_delay(dp);

	DPRINTF(2, (CE_CONT, "!rf_read_eeprom: returned 0x%x", ret));

	return ret;
}

static uint16_t
rf_erase_eeprom(struct gem_dev *dp, int addr)
{
	int		i;
	int		addr_bits;
	uint32_t	cmd;
	uint8_t		chip_select;
	uint8_t		di;
	uint16_t	ret;
	struct rf_dev	*lp = (struct rf_dev *)dp->private;

	if (lp->chip->type == CHIP_8139B || lp->chip->type == CHIP_8139C ||
	    lp->chip->type == CHIP_8139CP) {
		/*
		 * eeprom 93C46 or 93C56: 8139B, 8139C, 8139CP
		 */
		addr_bits = ((INL(dp, RCR) & RCR_9356SEL) != 0) ? 8 : 6;
	}
	else {
		/*
		 * eeprom 93C46 : 8129, 8130, 8100, 8100B/8139D, 8101
		 */
		addr_bits = 6;
	}

	DPRINTF(2, (CE_CONT, "!%s: rf_read_eeprom: called: addr_bits:%d",
			dp->name, addr_bits));

	/* make command bits */
	cmd = (7 << addr_bits) | addr;

	/* enable eeprom interface register */
	chip_select = CR9346_EEM_PROGRAM;
	OUTB(dp, CR9346, chip_select);

	chip_select |= CR9346_EECS;
	OUTB(dp, CR9346, chip_select);
	rf_eeprom_delay(dp);

	/* output eeprom command */
	for (i = (3 + addr_bits) -1 ; i >= 0; i--) {
		di = ((cmd >> i) & 1) << CR9346_EEDI_SHIFT;
		OUTB(dp, CR9346, chip_select | di);
		rf_eeprom_delay(dp);

		OUTB(dp, CR9346, chip_select | di | CR9346_EESK);
		rf_eeprom_delay(dp);
	}

	/* release clock but keep chip_select asserted */
	OUTB(dp, CR9346, chip_select);
	rf_eeprom_delay(dp);

	/* Terminate the EEPROM access. */
	OUTB(dp, CR9346, CR9346_EEM_PROGRAM);
	rf_eeprom_delay(dp);

	OUTB(dp, CR9346, chip_select);
	drv_usecwait(10);

	/*
	 * Ensure EEPROM busy
	 */
	i = 1500;
	while ((INB(dp, CR9346) & CR9346_EEDO) != 0) {
		drv_usecwait(10);
		i--;
		if (i < 0) {
			cmn_err(CE_CONT, "rf_write_eeprom: doesn't become busy");
		}
		return;
	}

	/* wait eeprom ready */
	i = 15000;
	while ((INB(dp, CR9346) & CR9346_EEDO) == 0) {
		drv_usecwait(10);
		i--;
		if (i < 0) {
			cmn_err(CE_CONT, "rf_write_eeprom: doesn't become ready");
		}
		return;
	}

	/* Terminate the EEPROM access. */
	OUTB(dp, CR9346, CR9346_EEM_PROGRAM);
	rf_eeprom_delay(dp);

	DPRINTF(2, (CE_CONT, "!rf_read_eeprom: returned 0x%x", ret));

	return ret;
}

#define	WDS	0x00
#define	WEN	0x30

static void
rf_control_eeprom(struct gem_dev *dp, uint_t cmd)
{
	int		i;
	int		addr_bits;
	uint8_t		chip_select;
	uint8_t		di;
	uint16_t	ret;
	struct rf_dev	*lp = (struct rf_dev *)dp->private;
#ifdef notdef
	if (lp->chip->type == CHIP_8139B || lp->chip->type == CHIP_8139C ||
	    lp->chip->type == CHIP_8139CP) {
		/*
		 * eeprom 93C46 or 93C56: 8139B, 8139C, 8139CP
		 */
		addr_bits = ((INL(dp, RCR) & RCR_9356SEL) != 0) ? 8 : 6;
	}
	else
#endif
	{
		/*
		 * eeprom 93C46 : 8129, 8130, 8100, 8100B/8139D, 8101
		 */
		addr_bits = 6;
	}
	DPRINTF(2, (CE_CONT, "!%s: rf_write_enable_eeprom: called: addr_bits:%d",
			dp->name, addr_bits));

	/* make command bits */
	cmd = (4 << addr_bits) | cmd;

	/* enable eeprom interface register */
	chip_select = CR9346_EEM_PROGRAM;
	OUTB(dp, CR9346, chip_select);

	chip_select |= CR9346_EECS;
	OUTB(dp, CR9346, chip_select);
	rf_eeprom_delay(dp);

	/* output eeprom command */
	for (i = (3 + addr_bits)-1; i >= 0; i--) {
		di = ((cmd >> i) & 1) << CR9346_EEDI_SHIFT;
		OUTB(dp, CR9346, chip_select | di);
		rf_eeprom_delay(dp);

		OUTB(dp, CR9346, chip_select | di | CR9346_EESK);
		rf_eeprom_delay(dp);
	}

	/* release clock but keep chip_select asserted */
	OUTB(dp, CR9346, chip_select);
	rf_eeprom_delay(dp);

	/* Terminate the EEPROM access. */
	OUTB(dp, CR9346, CR9346_EEM_PROGRAM);
	OUTB(dp, CR9346, CR9346_EEM_NORMAL);
	rf_eeprom_delay(dp);

	DPRINTF(2, (CE_CONT, "!rf_write_enable_eeprom: returned"));

	return;
}

static uint16_t rtl8139b_eeprom[] = {
/*0x00:*/ 0x8129,	/* signature, must be 0x8129 */
/*0x02:*/ 0x10ec,	/* VID */
/*0x04:*/ 0x8139,	/* DID */
/*0x06:*/ 0x10ec,	/* SVID */
/*0x08:*/ 0x8139,	/* SDID */
/*0x0a:*/ 0x4020,	/* MXLAT, MNGNT */
/*0x0c:*/ 0xe112,	/* CONFIG3, MSRBMCR */
/*0x0e:*/ 0xe000,	/* ethernet ID 01:00 */
/*0x10:*/ 0x7129,	/* ethernet ID 03:02 */
/*0x12:*/ 0xeb1e,	/* ethernet ID 05:04 */
/*0x14:*/ 0x4d10,	/* CONFIG1, CONFIG0 */
/*0x16:*/ 0xf7c2,	/* PMC */
/*0x18:*/ 0x8801,	/* CONFIG4, PMCCSR */
/*0x1a:*/ 0x8388,	/* PHY1_PARM  (0x78-0x7a) */
/*0x1c:*/ 0x78fa,
/*0x1e:*/ 0x271a,	/* DELAY-XXX , PHY2_PARM (0x80) */
/*0x20:*/ 0xde43,	/* TW1_PARM (0x7c-0x7f) XXX */
/*0x22:*/ 0xcb38,
/*0x24:*/ 0xde43,	/* TW2_PARM (0x7c-0x7f) XXX */
/*0x26:*/ 0xcb38,
/*0x28:*/ 0xde43,	/* TW3_PARM (0x7c-0x7f) XXX */
/*0x2a:*/ 0xcb38,
/*0x2c:*/ 0xde43,	/* TW4_PARM (0x7c-0x7f) XXX */
/*0x2e:*/ 0xcb38,
/*0x30:*/ 0x0000,	/* CIS pointer */
/*0x32:*/ 0x0000,	/* check sum */
/*0x34:*/ 0x0000,	/* reserved */
/*0x36:*/ 0x0000,	/* reserved */
/*0x38:*/ 0x0000,	/* reserved */
/*0x3a:*/ 0x0000,	/* reserved */
/*0x3c:*/ 0x0000,	/* reserved */
/*0x3e:*/ 0x0000,	/* PXE para, reserved */
/*0x40:*/ 0x0000, 0x0000, 0x0000, 0x0000,
/*0x48:*/ 0x0000, 0x0000, 0x0000, 0x0000,
/*0x50:*/ 0x0000, 0x0000, 0x0000, 0x0000,
/*0x58:*/ 0x0000, 0x0000, 0x0000, 0x0000,
/*0x60:*/ 0x0000, 0x0000, 0x0000, 0x0000,
/*0x68:*/ 0x0000, 0x0000, 0x0000, 0x0000,
/*0x70:*/ 0x0000, 0x0000, 0x0000, 0x0000,
/*0x68:*/ 0x0000, 0x0000, 0x0000, 0x0000,
};

static uint16_t rtl8139c_eeprom[] = {
/*0x00:*/ 0x8129, 0x10ec, 0x8139, 0x1259,
/*0x04:*/ 0xa11c, 0x4020, 0xe112, 0x9000,
/*0x08:*/ 0x7d99, 0x4e29, 0x4d10, 0xf7c2,
/*0x0c:*/ 0x8801, 0x43b9, 0xb0f2, 0x071a,
/*0x10:*/ 0xdf43, 0x8a36, 0xdf43, 0x8a36,
/*0x14:*/ 0x43b9, 0xb0f2, 0x1111, 0x1111,
/*0x18:*/ 0x0000, 0x0000, 0x0000, 0x0000,
/*0x1c:*/ 0x0000, 0x0000, 0x0000, 0x0000,
/*0x20:*/ 0x0000, 0x0000, 0x0000, 0x0000,
/*0x24:*/ 0x0000, 0x0000, 0x0000, 0x0000,
/*0x28:*/ 0x0000, 0x0000, 0x0000, 0x0000,
/*0x2c:*/ 0x0000, 0x0000, 0x0000, 0x0000,
/*0x30:*/ 0x0000, 0x0000, 0x0000, 0x0000,
/*0x34:*/ 0x0000, 0x0000, 0x0000, 0x0000,
/*0x38:*/ 0x0000, 0x0000, 0x0000, 0x0000,
/*0x3c:*/ 0x0000, 0x0000, 0x0000, 0x0000,
};
