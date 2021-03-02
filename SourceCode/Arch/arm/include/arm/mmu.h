//
// Created by XingfengYang on 2020/6/22.
//

#ifndef __KERNEL_MMU_H__
#define __KERNEL_MMU_H__

#define CONFIG_ARM_LPAE 1

#include "libc/stdint.h"

/**
 * read memory model feature register 0 (MMFR0)
 **/
static inline uint32_t read_mmfr0(void) {
    uint32_t mmfr;
    asm volatile("mrc p15, 0, %0, c0, c1, 4"
                 : "=r"(mmfr));
    return mmfr;
}

/**
 * write Primary Remap Register
 * @param val
 */
static inline void write_primapr(uint32_t val) {
    asm("MCR P15, 0, %0, C10, C2, 0 " : : "r" (val));
}

/**
 * write translation table base register 0 (TTBR0)
 * @param val
 */
static inline void write_ttbr0(uint32_t val) {
    asm("MCRR P15, 0, %0, %1, C2" : : "r"(val), "r"(0));
}

/**
 * read translation table base control register (TTBCR)
 * @return
 */
static inline uint32_t read_ttbcr(void) {
    uint32_t val = 0;
    asm volatile("mrc p15, 0, %0, c2, c0, 2"
                 : "=r"(val));
    return val;
}

/**
 * write translation table base control register (TTBCR)
 * @param val
 */
static inline void write_ttbcr(uint32_t val) {
    asm volatile("mcr p15, 0, %0, c2, c0, 2"
                 :
                 : "r"(val)
                 : "memory");
}

static inline void mmu_enable() {
    volatile uint32_t val;
    asm volatile("mrc p15, 0, %0, c1, c0, 0"
                 : "=r"(val));
    asm volatile("orr %0, %1, #0x1"
                 : "=r"(val)
                 : "r"(val));
    asm volatile("mcr p15, 0, %0, c1, c0, 0" ::"r"(val)
                 : "memory");
    asm volatile("isb");
}

static inline void mmu_disable() {
    volatile uint32_t val;
    asm volatile("mrc p15, 0, %0, c1, c0, 0"
                 : "=r"(val));
    asm volatile("bic %0, %1, #0x1"
                 : "=r"(val)
                 : "r"(val));
    asm volatile("mcr p15, 0, %0, c1, c0, 0" ::"r"(val)
                 : "memory");
    asm volatile("isb");
}

/**
 * write data access control register (DACR)
 * @param val
 */
static inline void write_dacr(uint32_t val) {
    asm volatile("mcr p15, 0, %0, c3, c0, 0"
                 :
                 : "r"(val));
}

#endif//__KERNEL_MMU_H__
