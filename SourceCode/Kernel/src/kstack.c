//
// Created by XingfengYang on 2020/6/26.
//
#include <kstack.h>
#include <kheap.h>

KernelStatus kstack_allocate(KernelStack *stack) {
    // 1. allocate stack memory block from virtual memory (heap), and align.
    stack = (KernelStack *) kheap_alloc(DEFAULT_KERNEL_STACK_SIZE + sizeof(KernelStack));
    stack->size = DEFAULT_KERNEL_STACK_SIZE;
    return OK;
}

KernelStatus kstack_free(KernelStack *stack) {
    stack->size = 0;
    stack->base = 0;
    stack->top = 0;
    return kheap_free(stack);
}
