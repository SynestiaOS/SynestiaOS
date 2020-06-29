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
    VirtualAddress base;
    uint32_t size;
    VirtualAddress top;
    void *virtualMemoryAddress;
} __attribute__((packed)) KernelStack;


KernelStatus vmm_allocate_kernel_stack(KernelStack *stack);

KernelStatus vmm_free_kernel_stack(KernelStack *stack);

#endif //__KERNEL_KSTACK_H__
