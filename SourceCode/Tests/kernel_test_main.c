#if 1

#undef abort
//#undef fflush

#define abort(x)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//#define GREATEST_STDOUT
#define GREATEST_USE_LONGJMP 0
#define GREATEST_USE_TIME 0
//#define fprintf(file, fmt, ...) printf(fmt, ##__VA_ARGS__)
//#define fflush (File)
#define EXIT_FAILURE 1
#define EXIT_SUCCESS 0
#include <greatest.h>
#include <string.h>

/* A test runs various assertions, then calls PASS(), FAIL(), or SKIP(). */
TEST x_should_equal(void) {
  int x = 1;
  /* Compare, with an automatic "1 != x" failure message */
  ASSERT_EQ(1, x);

  /* Compare, with a custom failure message */
  ASSERT_EQm("Yikes, x doesn't equal 1", 1, x);

  /* Compare, and if they differ, print both values,
   * formatted like `printf("Expected: %d\nGot: %d\n", 1, x);` */
  ASSERT_EQ_FMT(1, x, "%d");
  PASS();
}

/* Suites can group multiple tests with common setup. */
SUITE(the_suite) { RUN_TEST(x_should_equal); }
/* Add definitions that need to be in the test runner's main file. */
GREATEST_MAIN_DEFS();

void kernel_main(void) {
  print("runing unit test\n\n");

  printf("len %d\n", strlen("123123123"));

  printf("is print %d", isprint(1));

  RUN_SUITE(the_suite);
}

#endif
