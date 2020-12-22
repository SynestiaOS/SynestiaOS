//
// Created by XingfengYang on 2020/7/27.
//
#ifndef __LIBRARY_LIBC_H__
#define __LIBRARY_LIBC_H__

#include "libc/stdint.h"

#define asmlinkage __attribute__((regparm(0)))

#define _syscall5(type, name, type1, name1, type2, name2, type3, name3, type4, name4, type5, name5)              \
    type name(type1 name1, type2 name2, type3 name3, type4 name4, type5 name5) {                                 \
        uint32_t result;                                                                                         \
        __asm__ __volatile__("push {lr}\n\t"                                                                     \
                             "mov r0, #0\n\t"                                                                    \
                             "mov r1, %2\n\t"                                                                    \
                             "mov r2, %3\n\t"                                                                    \
                             "mov r3, #0\n\t"                                                                    \
                             "mov r4, %4\n\t"                                                                    \
                             "mov r5, %5\n\t"                                                                    \
                             "mov r6, %6\n\t"                                                                    \
                             "mov r7, %1\n\t"                                                                    \
                             "swi 0x0\n\t"                                                                       \
                             "mov %0, r0\n\t"                                                                    \
                             "pop {lr}\n\t"                                                                      \
                             : "=r"(result)                                                                      \
                             : "r"(__SYSCALL_##name), "r"(name1), "r"(name2), "r"(name3), "r"(name4), "r"(name5) \
                             : "r0", "r1", "r2", "r3", "r4", "r7");                                              \
        return result;                                                                                           \
    }

#define _syscall4(type, name, type1, name1, type2, name2, type3, name3, type4, name4)                \
    type name(type1 name1, type2 name2, type3 name3, type4 name4) {                                  \
        uint32_t result;                                                                             \
        __asm__ __volatile__("push {lr}\n\t"                                                         \
                             "mov r0, #0\n\t"                                                        \
                             "mov r1, %2\n\t"                                                        \
                             "mov r2, %3\n\t"                                                        \
                             "mov r3, #0\n\t"                                                        \
                             "mov r4, %4\n\t"                                                        \
                             "mov r5, %5\n\t"                                                        \
                             "mov r7, %1\n\t"                                                        \
                             "swi 0x0\n\t"                                                           \
                             "mov %0, r0\n\t"                                                        \
                             "pop {lr}\n\t"                                                          \
                             : "=r"(result)                                                          \
                             : "r"(__SYSCALL_##name), "r"(name1), "r"(name2), "r"(name3), "r"(name4) \
                             : "r0", "r1", "r2", "r3", "r4", "r7");                                  \
        return result;                                                                               \
    }

#define _syscall3(type, name, type1, name1, type2, name2, type3, name3)                  \
    type name(type1 name1, type2 name2, type3 name3) {                                   \
        uint32_t result;                                                                 \
        __asm__ __volatile__("push {lr}\n\t"                                             \
                             "mov r0, #0\n\t"                                            \
                             "mov r1, %2\n\t"                                            \
                             "mov r2, %3\n\t"                                            \
                             "mov r3, #0\n\t"                                            \
                             "mov r4, %4\n\t"                                            \
                             "mov r7, %1\n\t"                                            \
                             "swi 0x0\n\t"                                               \
                             "mov %0, r0\n\t"                                            \
                             "pop {lr}\n\t"                                              \
                             : "=r"(result)                                              \
                             : "r"(__SYSCALL_##name), "r"(name1), "r"(name2), "r"(name3) \
                             : "r0", "r1", "r2", "r3", "r4", "r7");                      \
        return result;                                                                   \
    }

#define _syscall2(type, name, type1, name1, type2, name2)                    \
    type name(type1 name1, type2 name2) {                                    \
        uint32_t result;                                                     \
        __asm__ __volatile__("push {lr}\n\t"                                 \
                             "mov r0, #0\n\t"                                \
                             "mov r1, %2\n\t"                                \
                             "mov r2, %3\n\t"                                \
                             "mov r3, #0\n\t"                                \
                             "mov r7, %1\n\t"                                \
                             "swi 0x0\n\t"                                   \
                             "mov %0, r0\n\t"                                \
                             "pop {lr}\n\t"                                  \
                             : "=r"(result)                                  \
                             : "r"(__SYSCALL_##name), "r"(name1), "r"(name2) \
                             : "r0", "r1", "r2", "r3", "r4", "r7");          \
        return result;                                                       \
    }

#define _syscall1(type, name, type1, name1)                         \
    type name(type1 name1) {                                        \
        uint32_t result;                                            \
        __asm__ __volatile__("push {lr}\n\t"                        \
                             "mov r0, #0\n\t"                       \
                             "mov r1, %2\n\t"                       \
                             "mov r3, #0\n\t"                       \
                             "mov r7, %1\n\t"                       \
                             "swi 0x0\n\t"                          \
                             "mov %0, r0\n\t"                       \
                             "pop {lr}\n\t"                         \
                             : "=r"(result)                         \
                             : "r"(__SYSCALL_##name), "r"(name1)    \
                             : "r0", "r1", "r2", "r3", "r4", "r7"); \
        return result;                                              \
    }

#define _syscall0(type, name)                                       \
    type name() {                                                   \
        uint32_t result;                                            \
        __asm__ __volatile__("push {lr}\n\t"                        \
                             "mov r0, #0\n\t"                       \
                             "mov r3, #0\n\t"                       \
                             "mov r7, %1\n\t"                       \
                             "swi 0x0\n\t"                          \
                             "mov %0, r0\n\t"                       \
                             "pop {lr}\n\t"                         \
                             : "=r"(result)                         \
                             : "r"(__SYSCALL_##name)                \
                             : "r0", "r1", "r2", "r3", "r4", "r7"); \
        return result;                                              \
    }

#define __SYSCALL_restart_syscall 0
#define __SYSCALL_exit 1
#define __SYSCALL_fork 2
#define __SYSCALL_read 3
#define __SYSCALL_write 4
#define __SYSCALL_open 5
#define __SYSCALL_close 6
#define __SYSCALL_execve 7
#define __SYSCALL_chdir 8
#define __SYSCALL_time 9
#define __SYSCALL_getpid 10
#define __SYSCALL_mount 11
#define __SYSCALL_umount 12
#define __SYSCALL_kill 13
#define __SYSCALL_rename 14
#define __SYSCALL_mkdir 15
#define __SYSCALL_rmdir 16

int restart_syscall();

int exit(int error_code);

int fork();

int read(uint32_t fd, char *buf, uint32_t count);

int write(uint32_t fd, const char *buf, uint32_t count);

int open(const char *filename, int flags, uint32_t mode);

int close(uint32_t fd);

int execve(const char *filenamei, const char *argv, const char *envp);

int chdir(const char *filename);

int time(uint32_t *tloc);

int getpid();

int mount(char *dev_name, char *dir_name, char *type, unsigned long flags, void *data);

int umount(char *name, int flags);

int kill(uint32_t pid, int sig);

int rename(const char *oldname, const char *newname);

int mkdir(const char *pathname, uint32_t mode);

int rmdir(const char *pathname);
#endif// __LIBRARY_LIBC_H__
