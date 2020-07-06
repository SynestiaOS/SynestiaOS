//
// Created by XingfengYang on 2020/7/6.
//

#include <kheap_test.h>
#include <tests_lib.h>
#include <stdbool.h>
#include <kheap.h>


void should_kheap_init() {
    KernelStatus heapInitStatus = kheap_init();

    ASSERT_EQ(heapInitStatus,OK)
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
    //todo:
    ASSERT_TRUE(false)
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
