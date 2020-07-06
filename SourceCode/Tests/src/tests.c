//
// Created by XingfengYang on 2020/7/5.
//
#include <tests_lib.h>
#include <tests.h>
#include <kstack_test.h>


void should_kheap_init();

void should_kheap_set_alloc_callback();

void should_kheap_set_free_callback();

void should_kheap_alloc();

void should_kheap_calloc();

void should_kheap_realloc();

void should_kheap_free();

void __run_tests() {
    TEST_SUIT("should_kstack_create", should_kstack_create)
    TEST_SUIT("should_kstack_push_value", should_kstack_push_value)
    TEST_SUIT("should_kstack_pop_value", should_kstack_pop_value)
    TEST_SUIT("should_kstack_peek_value", should_kstack_peek_value)
    TEST_SUIT("should_kstack_return_true_when_empty", should_kstack_return_true_when_empty)
    TEST_SUIT("should_kstack_return_true_when_full", should_kstack_return_true_when_full)

    TEST_SUIT("should_kheap_init", should_kheap_init)
    TEST_SUIT("should_kheap_set_alloc_callback", should_kheap_set_alloc_callback)
    TEST_SUIT("should_kheap_set_free_callback", should_kheap_set_free_callback)
    TEST_SUIT("should_kheap_alloc", should_kheap_alloc)
    TEST_SUIT("should_kheap_calloc", should_kheap_calloc)
    TEST_SUIT("should_kheap_realloc", should_kheap_realloc)
    TEST_SUIT("should_kheap_free", should_kheap_free)
}
