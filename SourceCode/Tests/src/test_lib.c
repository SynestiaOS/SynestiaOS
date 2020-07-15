//
// Created by XingfengYang on 2020/7/6.
//

#include <tests_lib.h>

void __assert_func_failed(const char *file, int line, const char *func, const char *failedexpr) {
  __test_all_asserts++;
  __test_failed_asserts++;
  if (__test_all_asserts > 1) {
    printf("├──\033[31mAssertion \"%s\" false \033[0m\n", failedexpr);
    printf("│    ├──\033[31mFile: %s, Line: %d \033[0m\n", file, line);
    printf("│    └──\033[31mFunction: %s \033[0m\n", func);
  } else {
    printf("└──\033[31mAssertion \"%s\" false \033[0m\n", failedexpr);
    printf("     ├──\033[31mFile: %s, Line: %d \033[0m\n", file, line);
    printf("     └──\033[31mFunction: %s \033[0m\n", func);
  }
}

void __assert_func_success(const char *file, int line, const char *func, const char *failedexpr) {
  __test_all_asserts++;
  if (__test_all_asserts > 1) {
    printf("├──\033[32mAssertion \"%s\" true \033[0m\n", failedexpr);
  } else {
    printf("└──\033[32mAssertion \"%s\" true \033[0m\n", failedexpr);
  }
}
