//
// Created by XingfengYang on 2020/7/6.
//

#ifndef __KERNEL_KSTACK_TEST_H__
#define __KERNEL_KSTACK_TEST_H__

#include "kernel/kstack.h"

void should_kstack_create() {
    struct KernelStack kernelStack;
    KernelStack *stack = kstack_allocate(&kernelStack);
    ASSERT_NEQ(stack, nullptr);

    ASSERT_EQ(stack->size, 0);

    VirtualAddress base = (VirtualAddress) (stack + sizeof(KernelStack) + DEFAULT_KERNEL_STACK_SIZE);
    ASSERT_EQ(stack->base, base);

    VirtualAddress top = stack->base;
    ASSERT_EQ(stack->top, top);

    ASSERT_EQ(stack->operations.free(stack), OK);
}

void should_kstack_push_value() {
    struct KernelStack kernelStack;
    KernelStack *stack = kstack_allocate(&kernelStack);
    ASSERT_NEQ(stack, nullptr);

    ASSERT_EQ(stack->size, 0);

    VirtualAddress base = (VirtualAddress) (stack + sizeof(KernelStack) + DEFAULT_KERNEL_STACK_SIZE);
    ASSERT_EQ(stack->base, base);

    VirtualAddress top = stack->base;
    ASSERT_EQ(stack->top, top);

    KernelStatus pushStatus = stack->operations.push(stack, 32);
    ASSERT_EQ(pushStatus, OK);
    ASSERT_EQ(stack->operations.peek(stack), 32);
    ASSERT_EQ(stack->size, 1);
    ASSERT_EQ(stack->top, stack->base - sizeof(uint32_t));

    ASSERT_EQ(stack->operations.free(stack), OK);
}

void should_kstack_pop_value() {
    struct KernelStack kernelStack;
    KernelStack *stack = kstack_allocate(&kernelStack);
    ASSERT_NEQ(stack, nullptr);

    ASSERT_EQ(stack->size, 0);

    VirtualAddress base = (VirtualAddress) (stack + sizeof(KernelStack) + DEFAULT_KERNEL_STACK_SIZE);
    ASSERT_EQ(stack->base, base);

    VirtualAddress top = stack->base;
    ASSERT_EQ(stack->top, top);

    KernelStatus pushStatus = stack->operations.push(stack, 32);
    ASSERT_EQ(pushStatus, OK);
    ASSERT_EQ(stack->operations.peek(stack), 32);
    ASSERT_EQ(stack->size, 1);
    ASSERT_EQ(stack->top, stack->base - sizeof(uint32_t));

    ASSERT_EQ(stack->operations.pop(stack), 32);
    ASSERT_EQ(stack->size, 0);
    ASSERT_EQ(stack->top, stack->base);

    ASSERT_EQ(stack->operations.free(stack), OK);
}

void should_kstack_peek_value() {
    struct KernelStack kernelStack;
    KernelStack *stack = kstack_allocate(&kernelStack);
    ASSERT_NEQ(stack, nullptr);

    ASSERT_EQ(stack->size, 0);

    VirtualAddress base = (VirtualAddress) (stack + sizeof(KernelStack) + DEFAULT_KERNEL_STACK_SIZE);
    ASSERT_EQ(stack->base, base);

    VirtualAddress top = stack->base;
    ASSERT_EQ(stack->top, top);

    KernelStatus pushStatus = stack->operations.push(stack, 32);
    ASSERT_EQ(pushStatus, OK);
    ASSERT_EQ(stack->operations.peek(stack), 32);
    ASSERT_EQ(stack->size, 1);
    ASSERT_EQ(stack->top, stack->base - sizeof(uint32_t));

    ASSERT_EQ(stack->operations.free(stack), OK);
}

void should_kstack_return_true_when_empty() {
    struct KernelStack kernelStack;
    KernelStack *stack = kstack_allocate(&kernelStack);
    ASSERT_NEQ(stack, nullptr);

    ASSERT_EQ(stack->size, 0);

    VirtualAddress base = (VirtualAddress) (stack + sizeof(KernelStack) + DEFAULT_KERNEL_STACK_SIZE);
    ASSERT_EQ(stack->base, base);

    VirtualAddress top = stack->base;
    ASSERT_EQ(stack->top, top);

    ASSERT_TRUE(stack->operations.isEmpty(stack));

    ASSERT_EQ(stack->operations.free(stack), OK);
}

void should_kstack_return_true_when_full() {
    struct KernelStack kernelStack;
    KernelStack *stack = kstack_allocate(&kernelStack);
    ASSERT_NEQ(stack, nullptr);

    ASSERT_EQ(stack->size, 0);

    VirtualAddress base = (VirtualAddress) (stack + sizeof(KernelStack) + DEFAULT_KERNEL_STACK_SIZE);
    ASSERT_EQ(stack->base, base);

    VirtualAddress top = stack->base;
    ASSERT_EQ(stack->top, top);

    for (uint32_t i = 0; i < DEFAULT_KERNEL_STACK_SIZE / 4; i++) {
        stack->operations.push(stack, i);
    }

    ASSERT_EQ(stack->size, DEFAULT_KERNEL_STACK_SIZE / 4);

    ASSERT_TRUE(stack->operations.isFull(stack));

    ASSERT_EQ(stack->operations.free(stack), OK);
}

#endif//__KERNEL_KSTACK_TEST_H__
