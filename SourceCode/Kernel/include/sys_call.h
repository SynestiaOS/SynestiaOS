//
// Created by XingfengYang on 2020/7/13.
//
#ifndef __KERNEL_SYSCALL_H__
#define __KERNEL_SYSCALL_H__

#include <stdint.h>
#include <type.h>

uint32_t sys_getpid(void);

uint32_t sys_open(const char *name, uint32_t flags, uint32_t mode);

uint32_t sys_read(uint32_t fd, char *buf, uint32_t count);

uint32_t sys_close(uint32_t fd);

uint32_t sys_fork(void);

SysCall sys_call_table[] = {
        sys_getpid,
        sys_open,
        sys_read,
        sys_close,
        sys_fork,
};

#endif// __KERNEL_SYSCALL_H__
