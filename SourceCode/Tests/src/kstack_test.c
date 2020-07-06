//
// Created by XingfengYang on 2020/7/6.
//
#include <kstack_test.h>
#include <kstack.h>
#include <tests_lib.h>
#include <stdbool.h>

void should_kstack_create() {
    KernelStack *stack = nullptr;
    KernelStatus kernelStatus = kstack_allocate(stack);
    ASSERT_EQ(kernelStatus, OK)
    ASSERT_EQ(stack->size, DEFAULT_KERNEL_STACK_SIZE)
    ASSERT_EQ(stack->base, stack + sizeof(KernelStack))
    ASSERT_EQ(stack->top, stack->base)
}

void should_kstack_push_value() {
    // todo;
    ASSERT_EQ(true, false)
}

void should_kstack_pop_value() {
    // todo;
    ASSERT_EQ(true, false)
}

void should_kstack_peek_value() {
    // todo;
    ASSERT_EQ(true, false)
}

void should_kstack_return_true_when_empty() {
    // todo;
    ASSERT_EQ(true, false)
}

void should_kstack_return_true_when_full() {
    // todo;
    ASSERT_EQ(true, false)
}
