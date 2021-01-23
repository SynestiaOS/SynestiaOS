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
    __asm__ __volatile__("mrc p15, 0, %0, c0, c1, 4"
                 : "=r"(mmfr));
    return mmfr;
}

/**
 * write translation table base register 0 (TTBR0)
 * @param val
 */
static inline void write_ttbr0(uint32_t val) {
    __asm__ __volatile__("mcr p15, 0, %0, c2, c0, 0"
                 :
                 : "r"(val)
                 : "memory");
    __asm__ __volatile__("dmb");
}

/**
 * read translation table base control register (TTBCR)
 * @return
 */
static inline uint32_t read_ttbcr(void) {
    uint32_t val = 0;
    __asm__ __volatile__("mrc p15, 0, %0, c2, c0, 2"
                 : "=r"(val));
    return val;
}

/**
 * write translation table base control register (TTBCR)
 * @param val
 */
static inline void write_ttbcr(uint32_t val) {
    __asm__ __volatile__("mcr p15, 0, %0, c2, c0, 2"
                 :
                 : "r"(val)
                 : "memory");
}

static inline void mmu_enable() {
    volatile uint32_t val;
    __asm__ __volatile__("mrc p15, 0, %0, c1, c0, 0"
                 : "=r"(val));
    __asm__ __volatile__("orr %0, %1, #0x1"
                 : "=r"(val)
                 : "r"(val));
    __asm__ __volatile__("mcr p15, 0, %0, c1, c0, 0" ::"r"(val)
                 : "memory");
    __asm__ __volatile__("isb");
}

static inline void mmu_disable() {
    volatile uint32_t val;
    __asm__ __volatile__("mrc p15, 0, %0, c1, c0, 0"
                 : "=r"(val));
    __asm__ __volatile__("bic %0, %1, #0x1"
                 : "=r"(val)
                 : "r"(val));
    __asm__ __volatile__("mcr p15, 0, %0, c1, c0, 0" ::"r"(val)
                 : "memory");
    __asm__ __volatile__("isb");
}

/**
 * write data access control register (DACR)
 * @param val
 */
static inline void write_dacr(uint32_t val) {
    __asm__ __volatile__("mcr p15, 0, %0, c3, c0, 0"
                 :
                 : "r"(val));
}

#endif//__KERNEL_MMU_H__
