#include <stdio.h>

int
main(int argc, char *argv)
{
#if AAA > 0
	printf("aaa>0\n");
#else
	printf("aaa<=0\n");
#endif
}
