//
// Created by XingfengYang on 2020/7/13.
//

#include <log.h>
#include <sched.h>
#include <sys_call.h>
#include <vfs.h>

extern VFS *vfs;

uint32_t sys_getpid(void) { return schd_getpid(); }

uint32_t sys_open(const char *name, uint32_t flags, uint32_t mode) { return vfs->operations.open(vfs, name, mode); }

uint32_t sys_read(uint32_t fd, char *buf, uint32_t count) { return vfs->operations.read(vfs, fd, buf, 0, count); }

uint32_t sys_close(uint32_t fd) { return vfs->operations.close(vfs, fd); }
