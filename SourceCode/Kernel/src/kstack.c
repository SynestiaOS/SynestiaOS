//
// Created by XingfengYang on 2020/6/26.
//
#include "kernel/kstack.h"
#include "kernel/kheap.h"
#include "kernel/log.h"
#include "libc/stdlib.h"

extern Heap kernelHeap;

KernelStatus stack_default_free(struct KernelStack *stack) {
    stack->size = 0;
    stack->base = 0;
    stack->top = 0;
    KernelStatus freeStatus = kernelHeap.operations.free(&kernelHeap, stack);
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

KernelStack *kstack_allocate() {
    // 1. allocate stack memory block from virtual memory (heap), and align.
    KernelStack *stack = (KernelStack *) kernelHeap.operations.allocAligned(
            &kernelHeap, DEFAULT_KERNEL_STACK_SIZE + sizeof(KernelStack), 16);
    if (stack == nullptr) {
        LogError("[KStack] kStack allocate failed.\n");
        return nullptr;
    }
    LogInfo("[KStack] kStack allocated.\n");
    stack->virtualMemoryAddress = (uint32_t *) (stack + sizeof(KernelStack) + DEFAULT_KERNEL_STACK_SIZE);
    stack->size = 0;
    stack->base = stack->virtualMemoryAddress;
    stack->top = stack->base;

    stack->operations.free = stack_default_free;
    stack->operations.push = stack_default_push;
    stack->operations.pop = stack_default_pop;
    stack->operations.peek = stack_default_peek;
    stack->operations.isFull = stack_default_is_full;
    stack->operations.isEmpty = stack_default_is_empty;
    stack->operations.clear = stack_default_clear;

    return stack;
}
