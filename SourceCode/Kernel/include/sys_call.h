//
// Created by XingfengYang on 2020/7/13.
//
#ifndef __KERNEL_SYSCALL_H__
#define __KERNEL_SYSCALL_H__
#include <stdint.h>
#include <type.h>


// Below would move to libC
void swi(uint32_t num);

#define asmlinkage __attribute__((regparm(0)))

#define __SYS_write 4

#define _syscall0(type,name)  \
asmlinkage type name(void){     \
    __asm__ __volatile__("push {lr}\n\t"    \
                       "mov r0, %0\n\t"     \
                       "swi 0x0\n\t"        \
                       "pop {pc}\n\t" ::"r"(__SYSCALL_##name));  \
}

#define __SYSCALL_setup 0
#define __SYSCALL_exit 1
#define __SYSCALL_fork 2
#define __SYSCALL_read 3
#define __SYSCALL_write 4

_syscall0(int,setup)
_syscall0(int,exit)
_syscall0(int,fork)
_syscall0(int,read)
_syscall0(int,write)

// Below in kernel
int sys_setup(void);
int sys_exit(void);
int sys_fork(void);
int sys_read(void);
int sys_write(void);

funcPtr sys_call_table[]={
    sys_setup,
    sys_exit,
    sys_fork,
    sys_read,
    sys_write,
};

#endif // __KERNEL_SYSCALL_H__
