//#include "config.h"

//#include <setjmp.h>
//#include <stdarg.h>
//#include <stddef.h>
//#include <stdint.h>

//#include "cmocka.h"

#include "../../Kernel/include/io.h"
#include "../../Libraries/LibC/include/stdint.h"
#include "../../Libraries/LibC/include/stdlib.h"

static void int_test_success(void **state __attribute__((unused))) {
  int x = 0;
  io_writeb(1, &x);
  //  assert_int_equal(x, 1);
}

void clean_bss(uint8_t *start, uint8_t *end) {
  uint32_t i;
  for (i = 0; start + i < end; i++) {
    *(start + i) = '\0';
  }
}

int os_test_main(void) {
  int_test_success(0);
  //  const struct CMUnitTest tests[] = {
  //      cmocka_unit_test(int_test_success),
  //  };
  //
  //  return cmocka_run_group_tests(tests, NULL, NULL);
  return 0;
}
