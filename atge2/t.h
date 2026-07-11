#undef	OUTB(dp, p, v)
#undef	OUTW(dp, p, v)
#undef	OUTL(dp, p, v)
#undef	INB(dp, p)
#undef	INW(dp, p)
#undef	INL(dp, p)


#define	OUTB(dp, p, v)	\
	atge_put8((dp)->regs_handle, \
		(void *)((caddr_t)((dp)->base_addr) + (p)), v)
#define	OUTW(dp, p, v)	\
	atge_put16((dp)->regs_handle, \
		(void *)((caddr_t)((dp)->base_addr) + (p)), v)
#define	OUTL(dp, p, v)	\
	atge_put32((dp)->regs_handle, \
		(void *)((caddr_t)((dp)->base_addr) + (p)), v)
#define	INB(dp, p)	\
	atge_get8((dp)->regs_handle, \
		(void *)(((caddr_t)(dp)->base_addr) + (p)))
#define	INW(dp, p)	\
	atge_get16((dp)->regs_handle, \
		(void *)(((caddr_t)(dp)->base_addr) + (p)))
#define	INL(dp, p)	\
	atge_get32((dp)->regs_handle, \
		(void *)(((caddr_t)(dp)->base_addr) + (p)))

extern uint8_t atge_get8(ddi_acc_handle_t handle, uint8_t *dev_addr);
extern uint16_t atge_get16(ddi_acc_handle_t handle, uint16_t *dev_addr);
extern uint32_t atge_get32(ddi_acc_handle_t handle, uint32_t *dev_addr);
extern uint64_t atge_get64(ddi_acc_handle_t handle, uint64_t *dev_addr);
extern void atge_put8(ddi_acc_handle_t handle, uint8_t *dev_addr,
    uint8_t value);
extern void atge_put16(ddi_acc_handle_t handle, uint16_t *dev_addr,
    uint16_t value);
extern void atge_put32(ddi_acc_handle_t handle, uint32_t *dev_addr,
    uint32_t value);
extern void atge_put64(ddi_acc_handle_t handle, uint64_t *dev_addr,
    uint64_t value);

