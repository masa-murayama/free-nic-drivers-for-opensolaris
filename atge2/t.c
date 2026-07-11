uint8_t
atge_get8(ddi_acc_handle_t handle, uint8_t *dev_addr)
{
	return (ddi_get8(handle, dev_addr));
}

uint16_t
atge_get16(ddi_acc_handle_t handle, uint16_t *dev_addr)
{
	return (ddi_get16(handle, dev_addr));
}

uint32_t
atge_get32(ddi_acc_handle_t handle, uint32_t *dev_addr)
{
	return (ddi_get32(handle, dev_addr));
}

uint64_t
atge_get64(ddi_acc_handle_t handle, uint64_t *dev_addr)
{
	return (ddi_get64(handle, dev_addr));
}

void
atge_put8(ddi_acc_handle_t handle, uint8_t *dev_addr, uint8_t value)
{
	ddi_put8(handle, dev_addr, value);
}

void
atge_put16(ddi_acc_handle_t handle, uint16_t *dev_addr, uint16_t value)
{
	ddi_put16(handle, dev_addr, value);
}

void
atge_put32(ddi_acc_handle_t handle, uint32_t *dev_addr, uint32_t value)
{
	ddi_put32(handle, dev_addr, value);
}

void
atge_put64(ddi_acc_handle_t handle, uint64_t *dev_addr, uint64_t value)
{
	ddi_put64(handle, dev_addr, value);
}

