//
// Created by XingfengYang on 2020/7/5.
//
#include <tests_lib.h>
#include <tests.h>
#include <kstack_test.h>

void __run_tests() {
    TEST_SUIT("should_kstack_create", should_kstack_create)
    TEST_SUIT("should_kstack_push_value", should_kstack_push_value)
    TEST_SUIT("should_kstack_pop_value", should_kstack_pop_value)
    TEST_SUIT("should_kstack_peek_value", should_kstack_peek_value)
    TEST_SUIT("should_kstack_return_true_when_empty", should_kstack_return_true_when_empty)
    TEST_SUIT("should_kstack_return_true_when_full", should_kstack_return_true_when_full)
}
