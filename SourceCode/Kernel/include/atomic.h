//
// Created by XingfengYang on 2020/7/17.
//

#ifndef __KERNEL_ATOMIC_H__
#define __KERNEL_ATOMIC_H__
#include <stdint.h>

typedef struct Atomic {
    volatile uint32_t counter;
} Atomic;

void atomic_create(Atomic* atomic);

void atomic_set(Atomic* atomic, uint32_t val);

uint32_t atomic_get(Atomic* atomic);

uint32_t atomic_inc(Atomic* atomic);

uint32_t atomic_dec(Atomic* atomic);

uint32_t atomic_add(Atomic* atomic, uint32_t val);

uint32_t atomic_sub(Atomic* atomic, uint32_t val);

#endif // __KERNEL_ATOMIC_H__
