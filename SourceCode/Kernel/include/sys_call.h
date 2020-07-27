//
// Created by XingfengYang on 2020/7/13.
//
#ifndef __KERNEL_SYSCALL_H__
#define __KERNEL_SYSCALL_H__
#include <stdint.h>
#include <type.h>

int sys_setup(void);
int sys_exit(void);
int sys_fork(void);
int sys_read(void);
int sys_write(void);
int sys_test1(int arg1);
int sys_test2(int arg1,int arg2);
int sys_test3(int arg1,int arg2,int arg3);
int sys_test4(int arg1,int arg2,int arg3,int arg4);
int sys_test5(int arg1,int arg2,int arg3,int arg4,int arg5);

SysCall sys_call_table[]={
    sys_setup,
    sys_exit,
    sys_fork,
    sys_read,
    sys_write,
    sys_test1,
    sys_test2,
    sys_test3,
    sys_test4,
    sys_test5
};

#endif // __KERNEL_SYSCALL_H__
