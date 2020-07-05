//
// Created by XingfengYang on 2020/7/5.
//

#ifndef __LIBRARY_LIBC_ASSERT_H__
#define __LIBRARY_LIBC_ASSERT_H__

void __assert_func(const char *file, int line, const char *func, const char *failedexpr) {
    printf("    \033[31mAssertion \"%s\" failed \033[0m\n", failedexpr);
    printf("    \033[32mFile: \"%s\" \033[0m\n", file);
    printf("    \033[32mLine: %d \033[0m\n", line);
    printf("    \033[32mFunction: %s \033[0m\n", func);
}

# define assert(__e) \
    ((__e) \
        ? (void)0 \
        : __assert_func( \
            __FILE__, \
            __LINE__, \
            __PRETTY_FUNCTION__, \
            #__e) \
    )

#endif //__LIBRARY_LIBC_ASSERT_H__
