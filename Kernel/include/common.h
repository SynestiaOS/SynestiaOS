#ifndef _COMMON_H_
#define _COMMON_H_
#include <stdint.h>

#if defined(RASPI2) || defined(RASPI3) 
#include <raspi3.h>
#endif

// Todo, put to arm/arm64 dir and rewrite with asm
static inline void io_writeb(uint8_t val, void *addr)
{
    *(uint8_t *)addr = val;
}

static inline void io_writew(uint16_t val, void *addr)
{
    *(uint16_t *)addr = val;
}

static inline void io_writel(uint32_t val, void *addr)
{
    *(uint32_t *)addr = val;
}

static inline uint8_t io_readb(void *addr)
{
    return *(uint8_t *)addr;
}

static inline uint16_t io_readw(void *addr)
{
    return *(uint16_t *)addr;
}

static inline uint32_t io_readl(void *addr)
{
    return *(uint32_t *)addr;
}

#endif