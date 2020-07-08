//
// Created by XingfengYang on 2020/7/5.
//

#include <tests_lib.h>

#include <kheap_test.h>
#include <klist_test.h>
#include <kstack_test.h>

void kernel_main_tests() {
    kheap_init();

    TEST_SUIT("should_klist_insert", should_klist_insert)
    TEST_SUIT("should_klist_append", should_klist_append)
    TEST_SUIT("should_klist_remove_node", should_klist_remove_node)
    TEST_SUIT("should_klist_return_size", should_klist_return_size)

    TEST_SUIT("should_kstack_create", should_kstack_create)
    TEST_SUIT("should_kstack_push_value", should_kstack_push_value)
    TEST_SUIT("should_kstack_pop_value", should_kstack_pop_value)
    TEST_SUIT("should_kstack_peek_value", should_kstack_peek_value)
    TEST_SUIT("should_kstack_return_true_when_empty", should_kstack_return_true_when_empty)
    TEST_SUIT("should_kstack_return_true_when_full", should_kstack_return_true_when_full)

    TEST_SUIT("should_kheap_init", should_kheap_init)
    TEST_SUIT("should_kheap_alloc", should_kheap_alloc)
    TEST_SUIT("should_kheap_calloc", should_kheap_calloc)
    TEST_SUIT("should_kheap_realloc", should_kheap_realloc)
    TEST_SUIT("should_kheap_free", should_kheap_free)
}
