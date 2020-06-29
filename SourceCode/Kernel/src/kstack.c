//
// Created by XingfengYang on 2020/6/26.
//
#include <kstack.h>

KernelStatus vmm_allocate_kernel_stack(KernelStack *stack){
    // todo : allocate kernel stack

    // 1. allocate stack memory block from virtual memory (heap), and align.
    return 0;
}

KernelStatus vmm_free_kernel_stack(KernelStack *stack){
    // todo : free kernel stack
    return 0;
}
