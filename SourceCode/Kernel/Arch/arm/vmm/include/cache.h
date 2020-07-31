//
// Created by XingfengYang on 2020/6/22.
//

#ifndef __KERNEL_CACHE_H__
#define __KERNEL_CACHE_H__

#define CONFIG_ARM_LPAE 1
#include <stdint.h>

/**
 * read memory model feature register 0 (MMFR0)
 **/
static inline uint32_t read_mmfr0(void) {
  uint32_t mmfr;
  asm volatile("mrc p15, 0, %0, c0, c1, 4" : "=r"(mmfr));
  return mmfr;
}

static inline uint32_t read_cpuid(void) {
  uint32_t cpuid = 0;
  asm volatile("mrc p15, #0, r0, c0, c0, #5\n\t"
               "and r0, r0, #0xFF\n\t"
               "mov %0, r0"
               : "=r"(cpuid));
  return cpuid;
}

/**
 * write translation table base register 0 (TTBR0)
 * @param val
 */
static inline void write_ttbr0(uint32_t val) {
  asm volatile("mcr p15, 0, %0, c2, c0, 0" : : "r"(val) : "memory");
  asm volatile("dmb");
}

/**
 * read translation table base control register (TTBCR)
 * @return
 */
static inline uint32_t read_ttbcr(void) {
  uint32_t val = 0;
  asm volatile("mrc p15, 0, %0, c2, c0, 2" : "=r"(val));
  return val;
}

/**
 * write translation table base control register (TTBCR)
 * @param val
 */
static inline void write_ttbcr(uint32_t val) { asm volatile("mcr p15, 0, %0, c2, c0, 2" : : "r"(val) : "memory"); }

static inline void mmu_enable() {
  asm volatile("mrc p15, 0, r12, c1, c0, 0");
  asm volatile("orr r12, r12, #0x1");
  asm volatile("mcr p15, 0, r12, c1, c0, 0");
  asm volatile("dsb");
}

static inline void mmu_disable() {
  asm volatile("mrc p15, 0, r12, c1, c0, 0");
  asm volatile("bic r12, r12, #0x1");
  asm volatile("mcr p15, 0, r12, c1, c0, 0");
  asm volatile("dsb");
}

/**
 * write data access control register (DACR)
 * @param val
 */
static inline void write_dacr(uint32_t val) { asm volatile("mcr p15, 0, %0, c3, c0, 0" : : "r"(val)); }

#endif //__KERNEL_CACHE_H__
