//
// Created by XingfengYang on 2020/7/6.
//

#include <kheap_test.h>
#include <tests_lib.h>
#include <stdbool.h>
#include <kheap.h>


void should_kheap_init() {
    KernelStatus heapInitStatus = kheap_init();

    ASSERT_EQ(heapInitStatus, OK)
}

void should_kheap_set_alloc_callback() {
    //todo:
    ASSERT_TRUE(false)
}

void should_kheap_set_free_callback() {
    //todo:
    ASSERT_TRUE(false)
}

void should_kheap_alloc() {
    KernelStatus heapInitStatus = kheap_init();
    ASSERT_EQ(heapInitStatus, OK)


    uint32_t *values1 = (uint32_t *) kheap_alloc(5 * sizeof(uint32_t));
    values1[0] = 10;
    values1[1] = 11;
    values1[2] = 12;
    values1[3] = 13;
    values1[4] = 14;


    uint32_t *values2 = (uint32_t *) kheap_alloc(5 * sizeof(uint32_t));
    values2[0] = 20;
    values2[1] = 21;
    values2[2] = 22;
    values2[3] = 23;
    values2[4] = 24;


    ASSERT_EQ(values1[0], 10)
    ASSERT_EQ(values1[1], 11)
    ASSERT_EQ(values1[2], 12)
    ASSERT_EQ(values1[3], 13)
    ASSERT_EQ(values1[4], 14)

    ASSERT_EQ(values2[0], 20)
    ASSERT_EQ(values2[1], 21)
    ASSERT_EQ(values2[2], 22)
    ASSERT_EQ(values2[3], 23)
    ASSERT_EQ(values2[4], 24)
}

void should_kheap_calloc() {
    //todo:
    ASSERT_TRUE(false)
}

void should_kheap_realloc() {
    //todo:
    ASSERT_TRUE(false)
}

void should_kheap_free() {
    //todo:
    ASSERT_TRUE(false)
}
