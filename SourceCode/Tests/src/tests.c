//
// Created by XingfengYang on 2020/7/5.
//
#include <tests_lib.h>
#include <tests.h>


void should_not_equal() {
    ASSERT_EQ(1, 2)
}

void should_equal() {
    ASSERT_EQ(1, 1)
}

void __run_tests() {
    TEST_SUIT("should_not_equal", should_not_equal)
    TEST_SUIT("should_equal", should_equal)
}
