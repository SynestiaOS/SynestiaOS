#include <kernel/io.h>

void io_writeb(uint8_t val, void *addr) { *(uint8_t *) addr = val; }

void io_writew(uint16_t val, void *addr) { *(uint16_t *) addr = val; }

void io_writel(uint32_t val, void *addr) { *(uint32_t *) addr = val; }

uint8_t io_readb(void *addr) { return *(uint8_t *) addr; }

uint16_t io_readw(void *addr) { return *(uint16_t *) addr; }

uint32_t io_readl(void *addr) { return *(uint32_t *) addr; }
