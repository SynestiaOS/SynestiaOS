//
// Created by XingfengYang on 2020/7/17.
//
#include "kernel/kernel.h"
#include "kernel/sys_call.h"
#include "kernel/scheduler.h"
#include "kernel/vfs.h"

extern DaVinciKernel kernel;

uint32_t sys_restart_syscall() { return 0; }

uint32_t sys_exit(int error_code) { return 0; }

uint32_t sys_fork() { return 0; }

uint32_t sys_read(uint32_t fd, char *buf, uint32_t count) {
    return kernel.vfs.operations.read(&kernel.vfs, fd, buf, 0, count);
}

uint32_t sys_write(uint32_t fd, const char *buf, uint32_t count) {
    return kernel.vfs.operations.write(&kernel.vfs, fd, buf, 0, count);
}

uint32_t sys_open(const char *filename, int flags, uint32_t mode) { return kernel.vfs.operations.open(&kernel.vfs, filename, mode); }

uint32_t sys_close(uint32_t fd) { return kernel.vfs.operations.close(&kernel.vfs, fd); }

uint32_t sys_execve(const char *filename, const char *argv, const char *envp) {
}

uint32_t sys_chdir(const char *filename) { return 0; }

uint32_t sys_time(uint32_t *tloc) { return 0; }

uint32_t sys_getpid() { return kernel.cfsScheduler.operation.getCurrentPid(&kernel.cfsScheduler); }

uint32_t sys_mount(char *dev_name, char *dir_name, char *type, unsigned long flags, void *data) { return 0; }

uint32_t sys_umount(char *name, int flags) { return 0; }

uint32_t sys_kill(uint32_t pid, int sig) { return 0; }

uint32_t sys_rename(const char *oldname, const char *newname) { return 0; }

uint32_t sys_mkdir(const char *pathname, uint32_t mode) { return 0; }

uint32_t sys_rmdir(const char *pathname) { return 0; }
