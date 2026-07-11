static uint16_t ee_905b[] =
{
#if 0
	0xffff,	/* 00 */
	0x7671,	/* 01 */
	0x1313,	/* 02 */
	0x9055,	/* 03 */
	0x02a9,	/* 04 */
	0x0048,	/* 05 */
	0x514d,	/* 06 */
	0x6d50,	/* 07 */
	0x2979,	/* 08 or 0x2970 for 40-0502-0x asic */
	0x0000,	/* 09 */
	0x0004,	/* 0a */
	0x7671,	/* 0b */
	0x1313,	/* 0c */
	0x0010,	/* 0d */
	0x0000,	/* 0e */
	0x002a,	/* 0f */
	0x32a2,	/* 10 */
	0x0000,	/* 11 */
	0x0000,	/* 12 */
	0x0180,	/* 13 */
	0x0000,	/* 14 */
	0x0000,	/* 15 */
	0x0000,	/* 16 */
	0x10b7,	/* 17 */
	0x9055,	/* 18 */
	0x000a,	/* 19 */
	0x0000,	/* 1a */
	0x0000,	/* 1b */
	0x0000,	/* 1c */
	0x0000,	/* 1d */
	0x0000,	/* 1e */
	0x0000,	/* 1f */
	0x0000,	/* 20 */
#else
 0xffff,0x7671,0x1315,0x9055,
 0x02a9,0x0048,0x514d,0x6d50,
 0x2979,0x0000,0x0004,0x7671,
 0x1315,0x0010,0x0000,0x002a,
 0x32a2,0x0000,0x0000,0x0180,
 0x0000,0x0000,0x0000,0x10b7,
 0x9055,0x000a,0x0000,0x0000,
 0x0000,0x0000,0x0000,0x0000,
 0x0014,0x0000,0x0000,0x0000,
 0x0000,
#endif
};

static int
tcfe_exec_eeprom_cmd(struct gem_dev *dp,
		uint16_t cmd, uint16_t offset, uint16_t val)
{
	int		i;
	int		addrbits;
	int		timeo;
	struct tcfe_dev	*lp = (struct tcfe_dev *)dp->private;

	switch (cmd) {
	case EE_WriteDisable:
	case EE_WriteEnable:
		timeo = 60;
		break;

	case EE_WriteAll:
	case EE_EraseAll:
	case EE_WriteRegister:
	case EE_EraseRegister:
		timeo = 11*1000;
		break;

	case EE_ReadRegister:
		timeo = 162;
		break;

	default:
		cmn_err(CE_WARN, "!%s: %s: unknown eeprom cmd (%d)",
			dp->name, __func__, cmd);
		return (GEM_FAILURE);
	}

	addrbits = (lp->chip->flags & EEADDRSIZE_8) ? 8 : 6;
	cmd = (cmd << (addrbits - 2)) | offset;

	/* issue eeprom command */
	REG_LOCK(lp);
	SET_WIN(dp, 0);
	OUTW(dp, W0EepromData, val);

	OUTW(dp, W0EepromCommand, cmd);
	drv_usecwait(timeo);

	timeo = timeo / 10;
	for (i = 0; (INW(dp, W0EepromCommand) & EC_eepromBusy) != 0; i++) {
		if (i > timeo) {
			cmn_err(CE_WARN, "!%s: %s: timeout",
				dp->name, __func__);
			return (GEM_FAILURE);
		}
		drv_usecwait(10);
	}

	REG_UNLOCK(lp);
	return (GEM_SUCCESS);
}

static void
tcfe_fix_eeprom905b(struct gem_dev *dp)
{
	int	i;
	uint8_t	cksum = 0;

	tcfe_exec_eeprom_cmd(dp, EE_WriteEnable, 0, 0);

	for (i = 0; i < 0x20; i++) {
		cksum ^= (ee_905b[i] >> 8) ^ ee_905b[i];
		tcfe_exec_eeprom_cmd(dp, EE_EraseRegister, i, 0);
		tcfe_exec_eeprom_cmd(dp, EE_WriteRegister, i, ee_905b[i]);
		DPRINTF(0, (CE_CONT, "!%s: %x: sum:%x", __func__, i, cksum));
	}

	cksum = 0x14;
	tcfe_exec_eeprom_cmd(dp, EE_EraseRegister, 0x20, 0);
	tcfe_exec_eeprom_cmd(dp, EE_WriteRegister, 0x20, cksum);

	tcfe_exec_eeprom_cmd(dp, EE_WriteDisable, 0, 0);

	DPRINTF(10, (CE_CONT, "!%s: cksum:%x", __func__, cksum));
}
