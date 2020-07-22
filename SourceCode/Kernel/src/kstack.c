//
// Created by XingfengYang on 2020/6/26.
//
#include <kheap.h>
#include <kstack.h>
#include <stdbool.h>
#include <stdlib.h>
#include <log.h>

KernelStack *kstack_allocate() {
  // 1. allocate stack memory block from virtual memory (heap), and align.
  KernelStack *stack = (KernelStack *)kheap_alloc_aligned(DEFAULT_KERNEL_STACK_SIZE + sizeof(KernelStack), 16);
  if (stack == nullptr) {
    LogError("[KStack] kStack allocate failed.\n");
    return nullptr;
  }
  stack->virtualMemoryAddress = (uint32_t *)(stack + sizeof(KernelStack) + DEFAULT_KERNEL_STACK_SIZE);
  stack->size = 0;
  stack->base = stack->virtualMemoryAddress;
  stack->top = stack->base;
  return stack;
}

KernelStatus kstack_free(KernelStack *stack) {
  stack->size = 0;
  stack->base = 0;
  stack->top = 0;
  return kheap_free(stack);
}

KernelStatus kstack_push(KernelStack *stack, uint32_t data) {
  if (kstack_is_full(stack)) {
    return ERROR;
  }
  stack->top = stack->top - sizeof(uint32_t);
  *(uint32_t *)(stack->top) = data;
  stack->size += 1;
  return OK;
}

uint32_t kstack_pop(KernelStack *stack) {
  if (kstack_is_empty(stack)) {
    return ERROR;
  }
  uint32_t val = *(uint32_t *)(stack->top);
  stack->top = stack->top + sizeof(uint32_t);
  stack->size -= 1;
  return val;
}

uint32_t kstack_peek(KernelStack *stack) { return *(uint32_t *)(stack->top); }

bool kstack_is_empty(KernelStack *stack) { return stack->top == stack->base; }

bool kstack_is_full(KernelStack *stack) { return stack->top == stack->base - DEFAULT_KERNEL_STACK_SIZE; }

KernelStatus kstack_clear(KernelStack *stack) {
  stack->size = 0;
  stack->top = stack->base;
  return OK;
}
