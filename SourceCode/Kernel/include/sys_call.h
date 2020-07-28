//
// Created by XingfengYang on 2020/7/13.
//
#ifndef __KERNEL_SYSCALL_H__
#define __KERNEL_SYSCALL_H__
#include <stdint.h>
#include <type.h>

uint32_t sys_getpid(void);

SysCall sys_call_table[]={
    sys_getpid
};

#endif // __KERNEL_SYSCALL_H__
