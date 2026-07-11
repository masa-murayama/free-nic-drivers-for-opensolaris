#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

main()
{
	int	hash;
	int	hash2;
	int	hash3;
	
	for (hash = 0; hash < 512; hash++) {
		/* linux */
		if (hash < 384) {
			hash2 = hash + ((hash >> 4) << 4) +
				((hash >> 5) << 5);
		} else {
			hash2 = hash - 384;
			hash2 = 64 + hash2 + (hash2 >> 4) * 80;
		}
		hash2 += 8*12*4;

		/* bsd */
		if ((hash & 0x180) == 0x180) {
			hash3 = ((hash & 0x0F) + (hash & 0x70) * 3 + (14 << 4));
		} else {
			hash3 = ((hash & 0x1F) + ((hash >> 1) & 0xF0) * 3 +
			    (12 << 4));
		}

		hash3 = 2*(hash3 & ~0xf) + (hash3 & 0xf);

		printf("%d: (%d %d),  (%d %d)\n",
			hash, hash2/8, hash2%8, hash3/8, hash3%8);
	}
}
