#include <sys/types.h>

uint16_t srom_21140[] = {
/*0x000:*/0x1282, 0x9100, 0x0000, 0x0000,
/*0x008:*/0x0000, 0x0000, 0x0000, 0x0000,
/*0x010:*/0x00cb, 0x0101, 0xc000, 0xff26,
/*0x018:*/0x1301, 0x1e00, 0x0000, 0x0800,
/*0x020:*/0x0480, 0x0000, 0x001d, 0x0003,
/*0x028:*/0x008d, 0x0004, 0x001b, 0x0005,
/*0x030:*/0x008b, 0x0000, 0x0000, 0x0000,
/*0x038:*/0x0000, 0x0000, 0x0000, 0x0000,
/*0x040:*/0x0000, 0x0000, 0x0000, 0x0000,
/*0x048:*/0x0000, 0x0000, 0x0000, 0x0000,
/*0x050:*/0x0000, 0x0000, 0x0000, 0x0000,
/*0x058:*/0x0000, 0x0000, 0x0000, 0x0000,
/*0x060:*/0x0000, 0x0000, 0x0000, 0x0000,
/*0x068:*/0x0000, 0x0000, 0x0000, 0x0000,
/*0x070:*/0x0000, 0x0000, 0x0000, 0x0000,
/*0x078:*/0x0000, 0x0000, 0x0000, 0xeeee,
};

uint16_t srom_21143[] = {
/*0x000:*/ 0x0000, 0x0000, 0x0000, 0x0000,
/*0x008:*/ 0x0000, 0x0000, 0x0000, 0x0000,
/*0x010:*/ 0x0000, 0x0103, 0x4000, 0x3526,
/*0x018:*/ 0x1c37, 0x1e00, 0x0000, 0x0800,
/*0x020:*/ 0x8604, 0x0002, 0x08a1, 0x00a0,
/*0x028:*/ 0x0286, 0xa104, 0xa008, 0x8800,
/*0x030:*/ 0x0304, 0x08a1, 0x00a0, 0x8061,
/*0x038:*/ 0x0488, 0xa105, 0xa008, 0x6100,
/*0x040:*/ 0x0080, 0x0000, 0x0000, 0x0000,
/*0x048:*/ 0x0000, 0x0000, 0x0000, 0x0000,
/*0x050:*/ 0x0000, 0x0000, 0x0000, 0x0000,
/*0x058:*/ 0x0000, 0x0000, 0x0000, 0x0000,
/*0x060:*/ 0x0000, 0x0000, 0x0000, 0x0000,
/*0x068:*/ 0x0000, 0x0000, 0x0000, 0x0000,
/*0x070:*/ 0x0000, 0x0000, 0x0000, 0x0000,
/*0x078:*/ 0x0000, 0x0000, 0x0000, 0xdbba,
};

uint8_t *
media_block(uint8_t *cp)
{
	uint_t	type;
	uint_t	length;
	uint_t	ext;
	uint_t	f;
	uint_t	media_code;
	uint_t	gp_data;

	f = cp[0] >> 7;
	if (f == 0) {
		length = 3;
		media_code = cp[0] & 0x3f;
		gp_data    = cp[1];
		printf("type: 21140 Compact Format\n");
		printf("media code:%x\n", media_code);
		printf("gp data 0x%02x\n", gp_data);
		printf("cmd 0x%04x\n", (cp[3] << 8) | cp[2]);
		printf("\n");
		return cp + length + 1;
	}

	length = cp[0] & 0x7f;
	type = cp[1];
	ext = (cp[2] & 0x40) != 0;
	media_code =  cp[2] & 0x1f;

	printf("F:%d length:%d\n", f, length);
	printf("type: 0x%x\n", type);
	printf("ext: %d  Media Code:0x%x\n", f);

	switch (type) {
	case 2:
		printf("media code:%x\n", media_code);
		if (ext == 0) {
			printf("gp ctrl 0x%04x\n", (cp[4] << 8) | cp[3]);
			printf("gp data 0x%04x\n", (cp[6] << 8) | cp[5]);
		} else {
			printf("csr13 0x%04x\n", (cp[4] << 8) | cp[3]);
			printf("csr14 0x%04x\n", (cp[6] << 8) | cp[5]);
			printf("csr15 0x%04x\n", (cp[8] << 8) | cp[7]);
			printf("gp ctrl 0x%04x\n", (cp[10] << 8) | cp[9]);
			printf("gp data 0x%04x\n", (cp[12] << 8) | cp[11]);
		}
		break;
	case 4:
		printf("media code: 0x%02x\n", cp[2] & 0x1f);
		printf("gp ctrl 0x%04x\n", (cp[4] << 8) | cp[3]);
		printf("gp data 0x%04x\n", (cp[6] << 8) | cp[5]);
		printf("cmd 0x%04x\n", (cp[8] << 8) | cp[7]);
		break;
	}

	return cp + (cp[0] & 0x7f) + 1;
}

/* 21143 */
uint8_t *
info_leaf(uint8_t *cp, int chip_21143)
{
	int	i, k;

	printf("selected connection type:%04x\n",
		(cp[1] << 8) | cp[0]);

	if (chip_21143) {
		k = cp[2];
		printf("block count :%02x\n", cp[2]);

		cp += 3;
	} else {
		k = cp[3];
		printf("general purpose :%02x\n", cp[2]);
		printf("block count :%02x\n", cp[3]);

		cp += 4;
	}

	for (i = 0; i < k; i++) {
		cp = media_block(cp);
	}
}

main()
{
	uint8_t	*cp;
	uint16_t	svid;
	uint16_t	sdid;
	uint16_t	offset;
#ifdef notdef
	cp = (uint8_t *)srom_21140;
#else
	cp = (uint8_t *)srom_21140;
#endif
	/* parse ID block */
	svid = cp[1] << 8 | cp[0];

	sdid = cp[3] << 8 | cp[2];

	printf("svid: %04x\n", svid);
	printf("sdid: %04x\n", sdid);
	printf("func1 hwopt: %02x\n", cp[14]);
	printf("misc hwopt: %02x\n", cp[15]);
	printf("func0 hwopt: %02x\n", cp[17]);

	cp += 18;

	printf("srom format version: %02x\n", cp[0]);
	printf("num controler: %02x\n", cp[1]);

	cp += 2;
	printf("mac address: %02x:%02x:%02x:%02x:%02x:%02x\n",
		cp[0], cp[1], cp[2], cp[3], cp[4], cp[5]);

	cp += 6;
	printf("device number: %02x\n", cp[0]);

	cp += 1;
	offset = (cp[1] << 8) | cp[0];
#ifdef notdef
	cp = ((uint8_t *)srom_21140) + offset;
#else
	cp = ((uint8_t *)srom_21140) + offset;
#endif
	cp = info_leaf(cp, 0);
}
