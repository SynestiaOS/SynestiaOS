//
// Created by XingfengYang on 2020/11/18.
//

#ifndef KERNEL_REGISTER_H
#define KERNEL_REGISTER_H

#include "libc/stdint.h"

static inline uint32_t read_cpuid(void) {
    uint32_t cpuid = 0;
    asm volatile("mrc p15, #0, r0, c0, c0, #5\n\t"
                 "and r0, r0, #0xFF\n\t"
                 "mov %0, r0"
                 : "=r"(cpuid));
    return cpuid;
}


typedef struct RegisterCPSR {
    union {
        struct {
            uint32_t M: 5;
            uint32_t T: 1;
            uint32_t F: 1;
            uint32_t I: 1;
            uint32_t A: 1;
            uint32_t E: 1;
            uint32_t RESERVED2: 6;
            uint32_t GE: 4;
            uint32_t RESERVED1: 4;
            uint32_t J: 1;
            uint32_t Res: 2;
            uint32_t Q: 1;
            uint32_t V: 1;
            uint32_t C: 1;
            uint32_t Z: 1;
            uint32_t N: 1;
        };
        uint32_t val;
    };
} __attribute__((packed)) RegisterCPSR;


static inline RegisterCPSR svcModeCPSR() {
    RegisterCPSR cpsr = {0};
    cpsr.Z = 1;
    cpsr.C = 1;
    cpsr.A = 1;
    cpsr.I = 1;
    cpsr.F = 1;
    cpsr.M = 0b10011;
    return cpsr;
}

static inline RegisterCPSR userModeCPSR() {
    RegisterCPSR cpsr = {0};
    cpsr.Z = 1;
    cpsr.C = 1;
    cpsr.A = 1;
    cpsr.I = 1;
    cpsr.F = 1;
    cpsr.M = 0b10000;
    return cpsr;
}

static inline RegisterCPSR fiqModeCPSR() {
    RegisterCPSR cpsr = {0};
    cpsr.Z = 1;
    cpsr.C = 1;
    cpsr.A = 1;
    cpsr.I = 1;
    cpsr.F = 1;
    cpsr.M = 0b10001;
    return cpsr;
}

static inline RegisterCPSR irqModeCPSR() {
    RegisterCPSR cpsr = {0};
    cpsr.Z = 1;
    cpsr.C = 1;
    cpsr.A = 1;
    cpsr.I = 1;
    cpsr.F = 1;
    cpsr.M = 0b10010;
    return cpsr;
}

static inline RegisterCPSR sysModeCPSR() {
    RegisterCPSR cpsr = {0};
    cpsr.Z = 1;
    cpsr.C = 1;
    cpsr.A = 1;
    cpsr.I = 1;
    cpsr.F = 1;
    cpsr.M = 0b11111;
    return cpsr;
}



#endif//KERNEL_REGISTER_H
