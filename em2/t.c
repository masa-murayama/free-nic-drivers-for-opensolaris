#define	B	0x00
#define	A(x)	C_##x
#define	C_B	0x01

main()
{
	printf("%x\n", 0x01410c23 >> 10);
}
