//
// Created by XingfengYang on 2020/7/27.
//
#include "libc/sys.h"


_syscall0(int, restart_syscall);

_syscall1(int, exit, int, error_code);

_syscall0(int, fork);

_syscall3(int, read, uint32_t, fd, char *, buf, uint32_t, count);

_syscall3(int, write, uint32_t, fd, const char *, buf, uint32_t, count);

_syscall3(int, open, const char *, filename, int, flags, uint32_t, mode);

_syscall1(int, close, uint32_t, fd);

_syscall3(int, execve, const char *, filenamei, const char *, argv, const char *, envp);

_syscall1(int, chdir, const char *, filename);

_syscall1(int, time, uint32_t *, tloc);

_syscall0(int, getpid);

_syscall5(int, mount, char *, dev_name, char *, dir_name, char *, type, unsigned long, flags, void *, data);

_syscall2(int, umount, char *, name, int, flags);

_syscall2(int, kill, uint32_t, pid, int, sig);

_syscall2(int, rename, const char *, oldname, const char *, newname);

_syscall2(int, mkdir, const char *, pathname, uint32_t, mode);

_syscall1(int, rmdir, const char *, pathname);
