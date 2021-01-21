//
// Created by XingfengYang on 2020/6/26.
//
#include "kernel/kernel.h"
#include "kernel/kstack.h"
#include "kernel/kheap.h"
#include "kernel/log.h"
#include "libc/stdlib.h"

extern DaVinciKernel kernel;

KernelStatus stack_default_free(struct KernelStack *stack) {
    stack->size = 0;
    stack->base = 0;
    stack->top = 0;
    KernelStatus freeStatus = kernel.kernelHeap.operations.free(&kernel.kernelHeap, stack->virtualMemoryAddress);
    if (freeStatus != OK) {
        LogError("[KStack] kStack free failed.\n");
        return freeStatus;
    }
    LogInfo("[KStack] kStack freed.\n");
    return OK;
}

KernelStatus stack_default_push(struct KernelStack *stack, uint32_t data) {
    if (stack->operations.isFull(stack)) {
        LogError("[KStack] kStack push failed, stack full.\n");
        return ERROR;
    }
    stack->top = stack->top - sizeof(uint32_t);
    *(uint32_t *) (stack->top) = data;
    stack->size += 1;
    return OK;
}

uint32_t stack_default_pop(struct KernelStack *stack) {
    if (stack->operations.isEmpty(stack)) {
        LogError("[KStack] kStack pop failed, stack empty.\n");
        return ERROR;
    }
    uint32_t val = *(uint32_t *) (stack->top);
    stack->top = stack->top + sizeof(uint32_t);
    stack->size -= 1;
    return val;
}

uint32_t stack_default_peek(struct KernelStack *stack) { return *(uint32_t *) (stack->top); }

bool stack_default_is_full(struct KernelStack *stack) { return stack->top == stack->base - DEFAULT_KERNEL_STACK_SIZE; }

bool stack_default_is_empty(struct KernelStack *stack) { return stack->top == stack->base; }

KernelStatus stack_default_clear(struct KernelStack *stack) {
    stack->size = 0;
    stack->top = stack->base;
    return OK;
}

KernelStack *kstack_allocate(struct KernelStack *kernelStack) {
    // 1. allocate stack memory block from virtual memory (heap), and align.
    KernelStack *stack = (KernelStack *) kernel.kernelHeap.operations.allocAligned(&kernel.kernelHeap, DEFAULT_KERNEL_STACK_SIZE, 16);
    if (stack == nullptr) {
        LogError("[KStack] kStack allocate failed.\n");
        return nullptr;
    }
    LogInfo("[KStack] kStack allocated.\n");
    kernelStack->virtualMemoryAddress = (VirtualAddress *) stack;
    kernelStack->size = 0;
    kernelStack->base = (VirtualAddress) (stack + DEFAULT_KERNEL_STACK_SIZE);
    kernelStack->top = kernelStack->base;

    kernelStack->operations.free = (StackOperationFree) stack_default_free;
    kernelStack->operations.push = (StackOperationPush) stack_default_push;
    kernelStack->operations.pop = (StackOperationPop) stack_default_pop;
    kernelStack->operations.peek = (StackOperationPeek) stack_default_peek;
    kernelStack->operations.isFull = (StackOperationIsFull) stack_default_is_full;
    kernelStack->operations.isEmpty = (StackOperationIsEmpty) stack_default_is_empty;
    kernelStack->operations.clear = (StackOperationClear) stack_default_clear;

    return kernelStack;
}
