//
// Created by XingfengYang on 2020/7/6.
//
#include <kstack_test.h>
#include <kstack.h>
#include <tests_lib.h>

void should_kstack_create() {
    KernelStack *stack = kstack_allocate();
    ASSERT_NEQ(stack, nullptr)

    ASSERT_EQ(stack->size, 0)

    VirtualAddress base = (VirtualAddress) (stack + sizeof(KernelStack) + DEFAULT_KERNEL_STACK_SIZE);
    ASSERT_EQ(stack->base, base)

    VirtualAddress top = stack->base;
    ASSERT_EQ(stack->top, top)

    ASSERT_EQ(kstack_free(stack), OK)
}

void should_kstack_push_value() {
    KernelStack *stack = kstack_allocate();
    ASSERT_NEQ(stack, nullptr)

    ASSERT_EQ(stack->size, 0)

    VirtualAddress base = (VirtualAddress) (stack + sizeof(KernelStack) + DEFAULT_KERNEL_STACK_SIZE);
    ASSERT_EQ(stack->base, base)

    VirtualAddress top = stack->base;
    ASSERT_EQ(stack->top, top)

    KernelStatus pushStatus = kstack_push(stack, 32);
    ASSERT_EQ(pushStatus, OK)
    ASSERT_EQ(kstack_peek(stack), 32)
    ASSERT_EQ(stack->size, 1)
    ASSERT_EQ(stack->top, stack->base - sizeof(uint32_t))

    ASSERT_EQ(kstack_free(stack), OK)
}

void should_kstack_pop_value() {
    KernelStack *stack = kstack_allocate();
    ASSERT_NEQ(stack, nullptr)

    ASSERT_EQ(stack->size, 0)

    VirtualAddress base = (VirtualAddress) (stack + sizeof(KernelStack) + DEFAULT_KERNEL_STACK_SIZE);
    ASSERT_EQ(stack->base, base)

    VirtualAddress top = stack->base;
    ASSERT_EQ(stack->top, top)

    KernelStatus pushStatus = kstack_push(stack, 32);
    ASSERT_EQ(pushStatus, OK)
    ASSERT_EQ(kstack_peek(stack), 32)
    ASSERT_EQ(stack->size, 1)
    ASSERT_EQ(stack->top, stack->base - sizeof(uint32_t))

    ASSERT_EQ(kstack_pop(stack), 32)
    ASSERT_EQ(stack->size, 0)
    ASSERT_EQ(stack->top, stack->base)

    ASSERT_EQ(kstack_free(stack), OK)
}

void should_kstack_peek_value() {
    KernelStack *stack = kstack_allocate();
    ASSERT_NEQ(stack, nullptr)

    ASSERT_EQ(stack->size, 0)

    VirtualAddress base = (VirtualAddress) (stack + sizeof(KernelStack) + DEFAULT_KERNEL_STACK_SIZE);
    ASSERT_EQ(stack->base, base)

    VirtualAddress top = stack->base;
    ASSERT_EQ(stack->top, top)

    KernelStatus pushStatus = kstack_push(stack, 32);
    ASSERT_EQ(pushStatus, OK)
    ASSERT_EQ(kstack_peek(stack), 32)
    ASSERT_EQ(stack->size, 1)
    ASSERT_EQ(stack->top, stack->base - sizeof(uint32_t))

    ASSERT_EQ(kstack_free(stack), OK)
}

void should_kstack_return_true_when_empty() {
    KernelStack *stack = kstack_allocate();
    ASSERT_NEQ(stack, nullptr)

    ASSERT_EQ(stack->size, 0)

    VirtualAddress base = (VirtualAddress) (stack + sizeof(KernelStack) + DEFAULT_KERNEL_STACK_SIZE);
    ASSERT_EQ(stack->base, base)

    VirtualAddress top = stack->base;
    ASSERT_EQ(stack->top, top)

    ASSERT_TRUE(kstack_is_empty(stack))

    ASSERT_EQ(kstack_free(stack), OK)
}

void should_kstack_return_true_when_full() {
    KernelStack *stack = kstack_allocate();
    ASSERT_NEQ(stack, nullptr)

    ASSERT_EQ(stack->size, 0)

    VirtualAddress base = (VirtualAddress) (stack + sizeof(KernelStack) + DEFAULT_KERNEL_STACK_SIZE);
    ASSERT_EQ(stack->base, base)

    VirtualAddress top = stack->base;
    ASSERT_EQ(stack->top, top)

    for (uint32_t i = 0; i < DEFAULT_KERNEL_STACK_SIZE / 4; i++) {
        kstack_push(stack, i);
    }

    ASSERT_EQ(stack->size, DEFAULT_KERNEL_STACK_SIZE / 4)

    ASSERT_TRUE(kstack_is_full(stack))

    ASSERT_EQ(kstack_free(stack), OK)
}
