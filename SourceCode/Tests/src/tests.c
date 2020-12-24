//
// Created by XingfengYang on 2020/7/5.
//

#include "kernel/kheap.h"
#include "arm/cpu.h"

#include "tests/tests_lib.h"

#include "tests/kheap_test.h"
#include "tests/klist_test.h"
#include "tests/kstack_test.h"
#include "tests/kvector_test.h"

#include "tests/atomic_test.h"
#include "tests/libmath_test.h"

extern uint32_t __HEAP_BEGIN;
extern Heap testHeap;

void kernel_main_tests() {
    if (read_cpuid() == 0) {
        heap_create(&testHeap, __HEAP_BEGIN, 64 * MB);

        TEST_CASE("should_klist_insert", should_klist_insert);
        TEST_CASE("should_klist_append", should_klist_append);
        TEST_CASE("should_klist_remove_node", should_klist_remove_node);
        TEST_CASE("should_klist_return_size", should_klist_return_size);

        TEST_CASE("should_kstack_create", should_kstack_create);
        TEST_CASE("should_kstack_push_value", should_kstack_push_value);
        TEST_CASE("should_kstack_pop_value", should_kstack_pop_value);
        TEST_CASE("should_kstack_peek_value", should_kstack_peek_value);
        TEST_CASE("should_kstack_return_true_when_empty", should_kstack_return_true_when_empty);
        TEST_CASE("should_kstack_return_true_when_full", should_kstack_return_true_when_full);

        TEST_CASE("should_kheap_init", should_kheap_init);
        TEST_CASE("should_kheap_alloc", should_kheap_alloc);
        TEST_CASE("should_kheap_calloc", should_kheap_calloc);
        TEST_CASE("should_kheap_realloc", should_kheap_realloc);
        TEST_CASE("should_kheap_free", should_kheap_free);

        TEST_CASE("should_kvector_create", should_kvector_create);
        TEST_CASE("should_kvector_resize", should_kvector_resize);
        TEST_CASE("should_kvector_free", should_kvector_free);
        TEST_CASE("should_kvector_add", should_kvector_add);
        TEST_CASE("should_kvector_get", should_kvector_get);
        TEST_CASE("should_kvector_remove_index", should_kvector_remove_index);
        TEST_CASE("should_kvector_remove", should_kvector_remove);
        TEST_CASE("should_kvector_is_empty", should_kvector_is_empty);
        TEST_CASE("should_kvector_is_full", should_kvector_is_full);
        TEST_CASE("should_kvector_clear", should_kvector_clear);

        TEST_CASE("should_atomic_create", should_atomic_create);
        TEST_CASE("should_atomic_set", should_atomic_set);
        TEST_CASE("should_atomic_get", should_atomic_get);
        TEST_CASE("should_atomic_inc", should_atomic_inc);
        TEST_CASE("should_atomic_dec", should_atomic_dec);
        TEST_CASE("should_atomic_sub", should_atomic_sub);
        TEST_CASE("should_atomic_add", should_atomic_add);

        TEST_CASE("should_math_sinf", should_math_sinf);
        TEST_CASE("should_math_cosf", should_math_cosf);
        TEST_CASE("should_math_fmod", should_math_fmod);
        TEST_CASE("should_math_powf", should_math_powf);
    }
}
