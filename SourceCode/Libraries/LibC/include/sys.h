//
// Created by XingfengYang on 2020/7/27.
//
#ifndef __LIBRARY_LIBC_SYS_H__
#define __LIBRARY_LIBC_SYS_H__
#include <stdint.h>

#define asmlinkage __attribute__((regparm(0)))

#define _syscall5(type, name, type1, name1, type2, name2, type3, name3, type4, name4, type5, name5)                    \
  type name(type1 name1, type2 name2, type3 name3, type4 name4, type5 name5) {                                         \
    volatile uint32_t result;                                                                                          \
    __asm__ __volatile__("push {lr}\n\t"                                                                               \
                         "mov r0, #0\n\t"                                                                              \
                         "mov r1, %2\n\t"                                                                              \
                         "mov r2, %3\n\t"                                                                              \
                         "mov r3, #0\n\t"                                                                              \
                         "mov r4, %4\n\t"                                                                              \
                         "mov r5, %5\n\t"                                                                              \
                         "mov r6, %6\n\t"                                                                              \
                         "mov r7, %1\n\t"                                                                              \
                         "swi 0x0\n\t"                                                                                 \
                         "mov %0, r0\n\t"                                                                              \
                         "pop {lr}\n\t"                                                                                \
                         : "=r"(result)                                                                                \
                         : "r"(__SYSCALL_##name), "r"(name1), "r"(name2), "r"(name3), "r"(name4), "r"(name5)           \
                         : "r0", "r1", "r2", "r3", "r4", "r7");                                                        \
    return result;                                                                                                     \
  }

#define _syscall4(type, name, type1, name1, type2, name2, type3, name3, type4, name4)                                  \
  _syscall5(type, name, type1, name1, type2, name2, type3, name3, type4, name4, int, arg5)

#define _syscall3(type, name, type1, name1, type2, name2, type3, name3)                                                \
  _syscall4(type, name, type1, name1, type2, name2, type3, name3, int, arg4)

#define _syscall2(type, name, type1, name1, type2, name2) _syscall3(type, name, type1, name1, type2, name2, int, arg3)

#define _syscall1(type, name, type1, name1) _syscall2(type, name, type1, name1, int, arg2)

#define _syscall0(type, name) _syscall1(type, name, int, arg1)

#define __SYSCALL_getpid 0
_syscall0(int, getpid)

#define __SYSCALL_open 1
    _syscall3(int, open, const char *, name, uint32_t, flags, uint32_t, mode);

#define __SYSCALL_read 2
_syscall3(int, read, uint32_t, fd, char *, buf, uint32_t, count);

#define __SYSCALL_close 3
_syscall1(int, close, uint32_t, fd);

#endif // __LIBRARY_LIBC_SYS_H__
