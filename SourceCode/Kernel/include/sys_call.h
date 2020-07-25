//
// Created by XingfengYang on 2020/7/13.
//
#ifndef __KERNEL_SYSCALL_H__
#define __KERNEL_SYSCALL_H__
#include <interrupt.h>

/**
 * trigger a software interrupt
 * @param num
 */
void swi(uint32_t num);

#define asmlinkage __attribute__((regparm(0)))

#define __SYS_write 4

#define SYSCALL_DEFINE0(type,name)  \
asmlinkage type sys_##name(void){     \
    swi(__SYS_##name);   \
}

#define __SYS_setup 0
SYSCALL_DEFINE0(int,setup)

#define __SYS_exit 1
SYSCALL_DEFINE0(int,exit)

#define __SYS_fork 2
SYSCALL_DEFINE0(int,fork)

#define __SYS_read 3
SYSCALL_DEFINE0(int,read)

#define __SYS_write 4
SYSCALL_DEFINE0(int,write)

typedef int (*funcPtr)(void);

funcPtr sys_call_table[]={
    sys_setup,
    sys_exit,
    sys_fork,
    sys_read,
    sys_write,
};

#endif // __KERNEL_SYSCALL_H__
