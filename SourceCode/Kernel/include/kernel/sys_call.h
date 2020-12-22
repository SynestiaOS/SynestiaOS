//
// Created by XingfengYang on 2020/7/13.
//
#ifndef __KERNEL_SYSCALL_H__
#define __KERNEL_SYSCALL_H__

#include "kernel/type.h"
#include "libc/stdint.h"

uint32_t sys_restart_syscall();

uint32_t sys_exit(int error_code);

uint32_t sys_fork();

uint32_t sys_read(uint32_t fd, char *buf, uint32_t count);

uint32_t sys_write(uint32_t fd, const char *buf, uint32_t count);

uint32_t sys_open(const char *filename, int flags, uint32_t mode);

uint32_t sys_close(uint32_t fd);

uint32_t sys_execve(const char *filenamei, const char *argv, const char *envp);

uint32_t sys_chdir(const char *filename);

uint32_t sys_time(uint32_t *tloc);

uint32_t sys_getpid();

uint32_t sys_mount(char *dev_name, char *dir_name, char *type, unsigned long flags, void *data);

uint32_t sys_umount(char *name, int flags);

uint32_t sys_kill(uint32_t pid, int sig);

uint32_t sys_rename(const char *oldname, const char *newname);

uint32_t sys_mkdir(const char *pathname, uint32_t mode);

uint32_t sys_rmdir(const char *pathname);

SysCall sys_call_table[] = {
        sys_restart_syscall,
        sys_exit,
        sys_fork,
        sys_read,
        sys_write,
        sys_open,
        sys_close,
        sys_execve,
        sys_chdir,
        sys_time,
        sys_getpid,
        sys_mount,
        sys_umount,
        sys_kill,
        sys_rename,
        sys_mkdir,
        sys_rmdir,
};

#endif// __KERNEL_SYSCALL_H__
