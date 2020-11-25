//
// Created by XingfengYang on 2020/11/18.
//

#ifndef KERNEL_CPU_H
#define KERNEL_CPU_H

#include <stdint.h>

static inline uint32_t read_cpuid(void) {
    uint32_t cpuid = 0;
    asm volatile("mrc p15, #0, r0, c0, c0, #5\n\t"
                 "and r0, r0, #0xFF\n\t"
                 "mov %0, r0"
                 : "=r"(cpuid));
    return cpuid;
}


#endif//KERNEL_CPU_H
