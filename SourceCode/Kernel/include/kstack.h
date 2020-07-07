//
// Created by XingfengYang on 2020/6/26.
//

#ifndef __KERNEL_KSTACK_H__
#define __KERNEL_KSTACK_H__

#include <stdint.h>
#include "type.h"

#define DEFAULT_KERNEL_STACK_SIZE 32*KB

typedef uint32_t VirtualAddress;

typedef struct KernelStack {
    uint32_t size;
    VirtualAddress base;
    VirtualAddress top;
    VirtualAddress *virtualMemoryAddress;
} __attribute__((packed)) KernelStack;


KernelStack *kstack_allocate();

KernelStatus kstack_free(KernelStack *stack);

KernelStatus kstack_push(KernelStack *stack, uint32_t data);

uint32_t kstack_pop(KernelStack *stack);

uint32_t kstack_peek(KernelStack *stack);

bool kstack_is_empty(KernelStack *stack);

bool kstack_is_full(KernelStack *stack);

KernelStatus kstack_clear(KernelStack *stack);

#endif //__KERNEL_KSTACK_H__
