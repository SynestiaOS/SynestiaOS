//
// Created by XingfengYang on 2020/6/22.
//

#ifndef __KERNEL_CACHE_H__
#define __KERNEL_CACHE_H__


/**
 * transaction table register 0
 * @param val
 */
static inline void write_ttbr0(uint32_t val) {
    asm volatile ("mcrr p15, 0, %[val], %[zero], c2" : : [val] "r"(val), [zero] "r"(0));
}


/**
 * transaction table base control register
 * @return
 */
static inline uint32_t read_ttbcr(void) {
    uint32_t val = 0;
    asm volatile ("mrc p15, 0, %0, c2, c0, 2" : "=r" (val));
    return val;
}

/**
 * transaction table base control register
 * @param val
 */
static inline void write_ttbcr(uint32_t val) {
    asm volatile ("mcr p15, 0, %0, c2, c0, 2" : : "r" (val) : "memory");
}

#endif //__KERNEL_CACHE_H__
