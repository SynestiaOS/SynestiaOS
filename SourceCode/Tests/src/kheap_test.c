//
// Created by XingfengYang on 2020/7/6.
//

#include <kheap_test.h>
#include <tests_lib.h>
#include <kheap.h>


void should_kheap_init() {
    KernelStatus heapInitStatus = kheap_init();

    ASSERT_EQ(heapInitStatus, OK)
}

static uint32_t test_heap_alloc_size = 0;
static uint32_t test_heap_free_size = 0;

void test_heap_alloc_func(void *ptr, uint32_t size) {
    test_heap_alloc_size += size;
}

void test_heap_free_func(void *ptr) {
    HeapArea *heap = (HeapArea *) (ptr - sizeof(HeapArea));
    test_heap_alloc_size -= heap->size;
}

void should_kheap_set_alloc_callback() {
    KernelStatus heapInitStatus = kheap_init();
    ASSERT_EQ(heapInitStatus, OK)

    test_heap_alloc_size = 0;
    kheap_set_alloc_callback(test_heap_alloc_func);
    void *pVoid = kheap_alloc(5);
    ASSERT_NEQ(pVoid, nullptr)

    // todo: it's incorrect
    // ASSERT_EQ(test_heap_alloc_size, 5)
}

void should_kheap_set_free_callback() {
    KernelStatus heapInitStatus = kheap_init();
    ASSERT_EQ(heapInitStatus, OK)

    test_heap_free_size = 0;
    kheap_set_free_callback(test_heap_free_func);
    kheap_free(kheap_alloc(2));

    // todo: it's incorrect
    // ASSERT_EQ(test_heap_free_size, 2)
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
    KernelStatus heapInitStatus = kheap_init();
    ASSERT_EQ(heapInitStatus, OK)


    uint32_t *values1 = (uint32_t *) kheap_calloc(5, sizeof(uint32_t));
    values1[0] = 10;
    values1[1] = 11;
    values1[2] = 12;
    values1[3] = 13;
    values1[4] = 14;


    uint32_t *values2 = (uint32_t *) kheap_calloc(5, sizeof(uint32_t));
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

void should_kheap_realloc() {
    KernelStatus heapInitStatus = kheap_init();
    ASSERT_EQ(heapInitStatus, OK)


    uint32_t *values1 = (uint32_t *) kheap_calloc(5, sizeof(uint32_t));
    values1[0] = 10;
    values1[1] = 11;
    values1[2] = 12;
    values1[3] = 13;
    values1[4] = 14;
    ASSERT_EQ(values1[0], 10)
    ASSERT_EQ(values1[1], 11)
    ASSERT_EQ(values1[2], 12)
    ASSERT_EQ(values1[3], 13)
    ASSERT_EQ(values1[4], 14)


    values1 = (uint32_t *) kheap_realloc(values1, 6);
    values1[5] = 15;
    ASSERT_EQ(values1[5], 15)

    ASSERT_EQ(heapInitStatus, OK)

}

void should_kheap_free() {
    KernelStatus heapInitStatus = kheap_init();
    ASSERT_EQ(heapInitStatus, OK)


    uint32_t *values1 = (uint32_t *) kheap_calloc(1, sizeof(uint32_t));
    values1[0] = 10;
    ASSERT_EQ(values1[0], 10)

    KernelStatus heapFreeStatus = kheap_free(values1);
    ASSERT_EQ(heapFreeStatus, OK)
}
