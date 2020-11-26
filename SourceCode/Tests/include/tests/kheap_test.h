//
// Created by XingfengYang on 2020/7/6.
//

#ifndef __KERNEL_KHEAP_TEST_H__
#define __KERNEL_KHEAP_TEST_H__

#include "kernel/kheap.h"

extern uint32_t __HEAP_BEGIN;
Heap testHeap;

void should_kheap_init() {
    KernelStatus heapInitStatus = heap_create(&testHeap, __HEAP_BEGIN, 64 * MB);

    ASSERT_EQ(heapInitStatus, OK);
}

void should_kheap_alloc() {
    KernelStatus heapInitStatus = heap_create(&testHeap, __HEAP_BEGIN, 64 * MB);
    ASSERT_EQ(heapInitStatus, OK);

    uint32_t *values1 = (uint32_t *) testHeap.operations.alloc(&testHeap, 5 * sizeof(uint32_t));
    values1[0] = 10;
    values1[1] = 11;
    values1[2] = 12;
    values1[3] = 13;
    values1[4] = 14;

    uint32_t *values2 = (uint32_t *) testHeap.operations.alloc(&testHeap, 5 * sizeof(uint32_t));
    values2[0] = 20;
    values2[1] = 21;
    values2[2] = 22;
    values2[3] = 23;
    values2[4] = 24;

    ASSERT_EQ(values1[0], 10);
    ASSERT_EQ(values1[1], 11);
    ASSERT_EQ(values1[2], 12);
    ASSERT_EQ(values1[3], 13);
    ASSERT_EQ(values1[4], 14);

    ASSERT_EQ(values2[0], 20);
    ASSERT_EQ(values2[1], 21);
    ASSERT_EQ(values2[2], 22);
    ASSERT_EQ(values2[3], 23);
    ASSERT_EQ(values2[4], 24);
}

void should_kheap_calloc() {
    KernelStatus heapInitStatus = heap_create(&testHeap, __HEAP_BEGIN, 64 * MB);
    ASSERT_EQ(heapInitStatus, OK);

    uint32_t *values1 = (uint32_t *) testHeap.operations.calloc(&testHeap, 5, sizeof(uint32_t));
    values1[0] = 10;
    values1[1] = 11;
    values1[2] = 12;
    values1[3] = 13;
    values1[4] = 14;

    uint32_t *values2 = (uint32_t *) testHeap.operations.calloc(&testHeap, 5, sizeof(uint32_t));
    values2[0] = 20;
    values2[1] = 21;
    values2[2] = 22;
    values2[3] = 23;
    values2[4] = 24;

    ASSERT_EQ(values1[0], 10);
    ASSERT_EQ(values1[1], 11);
    ASSERT_EQ(values1[2], 12);
    ASSERT_EQ(values1[3], 13);
    ASSERT_EQ(values1[4], 14);

    ASSERT_EQ(values2[0], 20);
    ASSERT_EQ(values2[1], 21);
    ASSERT_EQ(values2[2], 22);
    ASSERT_EQ(values2[3], 23);
    ASSERT_EQ(values2[4], 24);
}

void should_kheap_realloc() {
    KernelStatus heapInitStatus = heap_create(&testHeap, __HEAP_BEGIN, 64 * MB);
    ASSERT_EQ(heapInitStatus, OK);

    uint32_t *values1 = (uint32_t *) testHeap.operations.calloc(&testHeap, 5, sizeof(uint32_t));
    values1[0] = 10;
    values1[1] = 11;
    values1[2] = 12;
    values1[3] = 13;
    values1[4] = 14;
    ASSERT_EQ(values1[0], 10);
    ASSERT_EQ(values1[1], 11);
    ASSERT_EQ(values1[2], 12);
    ASSERT_EQ(values1[3], 13);
    ASSERT_EQ(values1[4], 14);

    values1 = (uint32_t *) testHeap.operations.realloc(&testHeap, values1, 6);
    values1[5] = 15;
    ASSERT_EQ(values1[5], 15);

    ASSERT_EQ(heapInitStatus, OK);
}

void should_kheap_free() {
    KernelStatus heapInitStatus = heap_create(&testHeap, __HEAP_BEGIN, 64 * MB);
    ASSERT_EQ(heapInitStatus, OK);

    uint32_t *values1 = (uint32_t *) testHeap.operations.calloc(&testHeap, 1, sizeof(uint32_t));
    values1[0] = 10;
    ASSERT_EQ(values1[0], 10);

    KernelStatus heapFreeStatus = testHeap.operations.free(&testHeap, values1);
    ASSERT_EQ(heapFreeStatus, OK);
}

#endif//__KERNEL_KHEAP_TEST_H__
