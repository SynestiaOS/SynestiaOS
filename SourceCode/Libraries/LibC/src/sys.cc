//
// Created by XingfengYang on 2020/7/27.
//
#include <sys.h>


_syscall0(int, restart_syscall)

_syscall1(int, exit, int, error_code)

_syscall0(int, fork)

_syscall3(int, read, uint32_t, fd, char *, buf, uint32_t, count)

_syscall3(int, write, uint32_t, fd, const char *, buf, uint32_t, count)

_syscall3(int, open, const char *, filename, int, flags, uint32_t, mode)

_syscall1(int, close, uint32_t, fd)

_syscall2(int, creat, const char *, pathname, uint32_t, mode)

_syscall2(int, link, const char *, oldname, const char *, newname)

_syscall1(int, unlink, const char *, pathname)

_syscall3(int, execve, const char *, filenamei, const char *, argv, const char *, envp)

_syscall1(int, chdir, const char *, filename)

_syscall1(int, time, uint32_t*, tloc)

_syscall3(int, mknod, const char *, filename, uint32_t, mode, unsigned int, dev)

_syscall2(int, chmod, const char *, filename, uint32_t, mode)

_syscall3(int, lchown, const char *, filename, uint32_t, user, uint32_t, group)

_syscall3(int, lseek, uint32_t, fd, uint32_t, offset, uint32_t, origin)

_syscall0(int, getpid)

_syscall5(int, mount, char *, dev_name, char *, dir_name, char *, type, unsigned long, flags, void *, data)

_syscall2(int, umount, char *, name, int, flags)

_syscall1(int, setuid, uint32_t, uid)

_syscall0(int, getuid)

_syscall1(int, stime, uint32_t *, tptr)

_syscall4(int, ptrace, long, request, long, pid, unsigned long, addr, unsigned long, data)

_syscall1(int, alarm, uint32_t, seconds)

_syscall0(int, pause)

_syscall2(int, utime, char *, filename, uint32_t *, times)

_syscall2(int, access, const char *, filename, int, mode)

_syscall1(int, nice, int, increment)

_syscall0(int, sync)

_syscall2(int, kill, uint32_t, pid, int, sig)

_syscall2(int, rename, const char *, oldname, const char *, newname)

_syscall2(int, mkdir, const char *, pathname, uint32_t, mode)

_syscall1(int, rmdir, const char *, pathname)

_syscall1(int, dup, uint32_t, fildes)

_syscall1(int, pipe, int, *fildes)

_syscall1(int, times, uint32_t *, tbuf)

_syscall1(int, brk, unsigned long, brk)

_syscall1(int, setgid, uint32_t, gid)

_syscall0(int, getgid)

_syscall0(int, geteuid)

_syscall0(int, getegid)

_syscall1(int, acct, const char *, name)

_syscall2(int, umount2, char *, name, int, flags)

_syscall3(int, ioctl, uint32_t, fd, uint32_t, cmd, unsigned long, arg)

_syscall3(int, fcntl, uint32_t, fd, uint32_t, cmd, unsigned long, arg)

_syscall2(int, setpgid, uint32_t, pid, uint32_t, pgid)

_syscall1(int, umask, int, mask)

_syscall1(int, chroot, const char *, filename)

_syscall2(int, ustat, unsigned int, dev, uint32_t *, ubuf)

_syscall2(int, dup2, uint32_t, oldfd, uint32_t, newfd)

_syscall0(int, getppid)

_syscall0(int, getpgrp)

_syscall0(int, setsid)

_syscall3(int, sigaction, int, sig, const uint32_t *, act, uint32_t *, oact)

_syscall2(int, setreuid, uint32_t, ruid, uint32_t, euid)

_syscall2(int, setregid, uint32_t, rgid, uint32_t, egid)

_syscall3(int, sigsuspend, int, restart, unsigned long, oldmask, uint32_t, mask)

_syscall1(int, sigpending, uint32_t *, set)

_syscall2(int, sethostname, char *, name, int, len)

_syscall2(int, setrlimit, uint32_t, resource, uint32_t *, rlim)

_syscall2(int, getrlimit, uint32_t, resource, uint32_t *, rlim)

_syscall2(int, getrusage, int, who, uint32_t *, ru)

_syscall2(int, gettimeofday, uint32_t *, tv, uint32_t *, tz)

_syscall2(int, settimeofday, uint32_t *, tv, uint32_t *, tz)

_syscall2(int, getgroups, int, gidsetsize, uint32_t *, grouplist)

_syscall2(int, setgroups, int, gidsetsize, uint32_t *, grouplist)

_syscall5(int, select, int, n, uint32_t *, inp, uint32_t *, outp, uint32_t *, exp, uint32_t *, tvp)

_syscall2(int, symlink, const char *, oldname, const char *, newname)

_syscall3(int, readlink, const char *, path, char *, buf, int, bufsiz)

_syscall1(int, uselib, const char *, library)

_syscall2(int, swapon, const char *, specialfile, int, swap_flags)

_syscall4(int, reboot, int, magic1, int, magic2, uint32_t, cmd, void *, arg)

_syscall3(int, readdir, uint32_t, fd, uint32_t *, dirent, uint32_t, count)

_syscall1(int, mmap, uint32_t*, arg)

_syscall2(int, munmap, unsigned long, addr, uint32_t, len)

_syscall2(int, truncate, const char *, path, long, length)

_syscall2(int, ftruncate, uint32_t, fd, unsigned long, length)

_syscall2(int, fchmod, uint32_t, fd, uint32_t, mode)

_syscall2(int, fchown, uint32_t, fd, uint32_t, user)

_syscall2(int, getpriority, int, which, int, who)

_syscall3(int, setpriority, int, which, int, who, int, niceval)

_syscall2(int, statfs, const char *, pathname, uint32_t *, buf)

_syscall2(int, fstatfs, uint32_t, fd, uint32_t *, buf)

_syscall2(int, socketcall, int, call, unsigned long *, args)

_syscall3(int, syslog, int, type, char *, buf, int, len)

_syscall3(int, setitimer, int, which, uint32_t *, value, uint32_t *, ovalue)

_syscall2(int, getitimer, int, which, uint32_t *, value)

_syscall2(int, stat, const char *, filename, uint32_t *, statbuf)

_syscall2(int, lstat, const char *, filename, uint32_t *, statbuf)

_syscall2(int, fstat, uint32_t, fd, uint32_t *, statbuf)

_syscall0(int, vhangup)

_syscall0(int, syscall)

_syscall4(int, wait4, uint32_t, upid, int *, stat_addr, int, options, uint32_t *, ru)

_syscall1(int, swapoff, const char *, specialfile)

_syscall1(int, sysinfo, uint32_t *, info)

//_syscall5(int,ipc,uint32_t, call, int ,first, unsigned long ,second, unsigned long ,third, void *,ptr, long, fifth)

_syscall1(int, fsync, uint32_t, fd)

_syscall0(int, sigreturn)

_syscall5(int, clone, unsigned long, clone_flags, unsigned long, newsp, int *, parent_tidptr, int, tls_val, int *,
          child_tidptr)

_syscall2(int, setdomainname, char *, name, int, len)

_syscall1(int, uname, uint32_t *, name)

_syscall1(int, adjtimex, uint32_t *, txc_p)

_syscall3(int, mprotect, unsigned long, start, uint32_t, len, unsigned long, prot)

_syscall3(int, sigprocmask, int, how, uint32_t *, nset, uint32_t *, oset)

_syscall3(int, init_module, void *, umod, unsigned long, len, const char *, uargs)

_syscall2(int, delete_module, const char *, name_user, uint32_t, flags)

_syscall1(int, quotactl, uint32_t, cmd)

_syscall1(int, getpgid, uint32_t, pid)

_syscall1(int, fchdir, uint32_t, fd)

_syscall2(int, bdflush, int, func, long, data)

_syscall3(int, sysfs, int, option, unsigned long, arg1, unsigned long, arg2)

_syscall1(int, personality, uint32_t, personality)

_syscall1(int, setfsuid, uint32_t, uid)

_syscall1(int, setfsgid, uint32_t, gid)

//_syscall5(int,_llseek,uint32_t, fd, unsigned long ,offset_high, unsigned long, offset_low,uint32_t *,result, uint32_t ,origin)

_syscall3(int, getdents, uint32_t, fd, uint32_t *, dirent, uint32_t, count)

_syscall5(int, _newselect, int, n, uint32_t *, inp, uint32_t *, outp, uint32_t *, exp, uint32_t *, tvp)

_syscall2(int, flock, uint32_t, fd, uint32_t, cmd)

_syscall3(int, msync, unsigned long, start, uint32_t, len, int, flags)

_syscall3(int, readv, unsigned long, fd, const uint32_t *, vec, unsigned long, vlen)

_syscall3(int, writev, unsigned long, fd, const uint32_t *, vec, unsigned long, vlen)

_syscall1(int, getsid, uint32_t, pid)

_syscall1(int, fdatasync, uint32_t, fd)

_syscall1(int, _sysctl, uint32_t *, args)

_syscall2(int, mlock, unsigned long, start, uint32_t, len)

_syscall2(int, munlock, unsigned long, start, uint32_t, len)

_syscall1(int, mlockall, int, flags)

_syscall0(int, munlockall)

_syscall2(int, sched_setparam, uint32_t, pid, uint32_t *, param)

_syscall2(int, sched_getparam, uint32_t, pid, uint32_t *, param)

_syscall3(int, sched_setscheduler, uint32_t, pid, int, policy, uint32_t *, param)

_syscall1(int, sched_getscheduler, uint32_t, pid)

_syscall0(int, sched_yield)

_syscall1(int, sched_get_priority_max, int, policy)

_syscall1(int, sched_get_priority_min, int, policy)

_syscall2(int, sched_rr_get_interval, uint32_t, pid, uint32_t *, interval)

_syscall2(int, nanosleep, uint32_t *, rqtp, uint32_t *, rmtp)

_syscall5(int, mremap, unsigned long, addr, unsigned long, old_len, unsigned long, new_len, unsigned long, flags,
          unsigned long, new_addr)

_syscall3(int, setresuid, uint32_t, ruid, uint32_t, euid, uint32_t, suid)

_syscall3(int, getresuid, uint32_t *, ruidp, uint32_t *, euidp, uint32_t *, suidp)

_syscall3(int, poll, uint32_t *, ufds, uint32_t, nfds, int, timeout_msecs)

_syscall0(int, nfsservctl)

_syscall3(int, setresgid, uint32_t, rgid, uint32_t, egid, uint32_t, sgid32_t)

_syscall3(int, getresgid, uint32_t *, rgidp, uint32_t *, egidp, uint32_t *, sgidp)

_syscall5(int, prctl, int, option, unsigned long, arg2, unsigned long, arg3, unsigned long, arg4, unsigned long, arg5)

_syscall0(int, rt_sigreturn)

_syscall4(int, rt_sigaction, int, sig, const uint32_t *, act, uint32_t *, oact, uint32_t, sigsetsize)

_syscall4(int, rt_sigprocmask, int, how, uint32_t *, nset, uint32_t *, oset, uint32_t, sigsetsize)

_syscall2(int, rt_sigpending, uint32_t *, set, uint32_t, sigsetsize)

//_syscall5(int,rt_sigtimedwait,const uint32_t *,uthese, uint32_t *,uinfo, const uint32_t *,uts,uint32_t ,sigsetsize)

_syscall3(int, rt_sigqueueinfo, uint32_t, pid, int, sig, uint32_t *, uinfo)

_syscall2(int, rt_sigsuspend, uint32_t *, unewset, uint32_t, sigsetsize)

_syscall3(int, pread64, char *, buf, uint32_t, count, uint32_t, pos)

_syscall3(int, pwrite64, const char *, buf, uint32_t, count, uint32_t, pos)

_syscall3(int, chown, const char *, filename, uint32_t, user, uint32_t, group)

_syscall2(int, getcwd, char *, buf, unsigned long, size)

_syscall2(int, capget, uint32_t, header, uint32_t, dataptr)

_syscall2(int, capset, uint32_t, header, const uint32_t, data)

_syscall4(int, sendfile, int, out_fd, int, in_fd, uint32_t *, offset, uint32_t, count)

_syscall0(int, vfork)

_syscall2(int, ugetrlimit, uint32_t, resource, uint32_t *, rlim)

//_syscall5(int,mmap2,unsigned long ,addr, unsigned long, len, unsigned long, prot, unsigned long, flags, unsigned long, fd,unsigned long, pgoff)

_syscall1(int, truncate64, uint32_t, length)

_syscall1(int, ftruncate64, uint32_t, length)

_syscall2(int, stat64, const char *, filename, uint32_t *, statbuf)

_syscall2(int, lstat64, const char *, filename, uint32_t *, statbuf)

_syscall2(int, fstat64, unsigned long, fd, uint32_t *, statbuf)

_syscall3(int, lchown32, const char *, filename, uint32_t, user, uint32_t, group)

_syscall0(int, getuid32)

_syscall0(int, getgid32)

_syscall0(int, geteuid32)

_syscall0(int, getegid32)

_syscall2(int, setreuid32, uint32_t, rui, uint32_t, euid)

_syscall2(int, setregid32, uint32_t, rgid, uint32_t, egid)

_syscall2(int, getgroups32, int, gidsetsize, uint32_t *, grouplist)

_syscall2(int, setgroups32, int, gidsetsize, uint32_t *, grouplist)

_syscall3(int, fchown32, uint32_t, fd, uint32_t, user, uint32_t, group)

_syscall3(int, setresuid32, uint32_t, ruid, uint32_t, euid, uint32_t, suid)

_syscall3(int, getresuid32, uint32_t *, ruidp, uint32_t *, euidp, uint32_t *, suidp)

_syscall3(int, setresgid32, uint32_t, rgid, uint32_t, egid, uint32_t, sgid)

_syscall3(int, getresgid32, uint32_t *, rgidp, uint32_t *, egidp, uint32_t *, sgidp)

_syscall3(int, chown32, const char *, filename, uint32_t, user, uint32_t, group)

_syscall1(int, setuid32, uint32_t, uid)

_syscall1(int, setgid32, uint32_t, gid)

_syscall1(int, setfsuid32, uint32_t, uid)

_syscall1(int, setfsgid32, uint32_t, gid)

_syscall3(int, getdents64, uint32_t, fd, uint32_t *, dirent, uint32_t, count)

_syscall2(int, pivot_root, const char *, new_root, const char *, put_old)

_syscall3(int, mincore, unsigned long, start, uint32_t, len, unsigned char *, vec)

_syscall3(int, madvise, unsigned long, start, uint32_t, len_in, int, behavior)

_syscall3(int, fcntl64, uint32_t, fd, uint32_t, cmd, unsigned long, arg)

_syscall0(int, gettid)

_syscall2(int, readahead, uint32_t, offset, uint32_t, count)

_syscall5(int, setxattr, const char *, pathname, const char *, name, const void *, value, uint32_t, size, int, flags)

_syscall5(int, lsetxattr, const char *, pathname, const char *, name, const void *, value, uint32_t, size, int, flags)

_syscall5(int, fsetxattr, int, fd, const char *, name, const void *, value, uint32_t, size, int, flags)

_syscall4(int, getxattr, const char *, pathname, const char *, name, void *, value, uint32_t, size)

_syscall4(int, lgetxattr, const char *, pathname, const char *, name, void *, value, uint32_t, size)

_syscall4(int, fgetxattr, int, fd, const char *, name, void *, value, uint32_t, size)

_syscall3(int, listxattr, const char *, pathname, char *, list, uint32_t, size)

_syscall3(int, llistxattr, const char *, pathname, char *, list, uint32_t, size)

_syscall3(int, flistxattr, int, fd, char *, list, uint32_t, size)

_syscall2(int, removexattr, const char *, pathname, const char *, name)

_syscall2(int, lremovexattr, const char *, pathname, const char *, name)

_syscall2(int, fremovexattr, int, fd, const char *, name)

_syscall2(int, tkill, uint32_t, pid, int, sig)

_syscall4(int, sendfile64, int, out_fd, int, in_fd, uint32_t *, offset, uint32_t, count)

//_syscall6(int,futex,uint32_t *,uaddr, int, op, uint32_t ,val, uint32_t *,utime, uint32_t *,uaddr2, uint32_t ,val3)

_syscall3(int, sched_setaffinity, uint32_t, pid, uint32_t, len, unsigned long *, user_mask_ptr)

_syscall3(int, sched_getaffinity, uint32_t, pid, uint32_t, len, unsigned long *, user_mask_ptr)

_syscall2(int, io_setup, unsigned int, nr_events, uint32_t *, ctxp)

_syscall1(int, io_destroy, uint32_t, ctx)

_syscall5(int, io_getevents, uint32_t, ctx_id, long, min_nr, long, nr, uint32_t *, events, uint32_t *,timeout)

_syscall3(int, io_submit, uint32_t, ctx_id, long, nr, uint32_t **, iocbpp)

_syscall3(int, io_cancel, uint32_t, ctx_id, uint32_t *, iocb, uint32_t *, res)

_syscall1(int, exit_group, int, error_code)

_syscall2(int, lookup_dcookie, char *, buf, uint32_t, len)

_syscall1(int, epoll_create, int, size)

_syscall4(int, epoll_ctl, int, epfd, int, op, int, fd, uint32_t *, event)

_syscall4(int, epoll_wait, int, epfd, uint32_t *, events, int, maxevents, int, timeout)

_syscall5(int, remap_file_pages, unsigned long, start, unsigned long, size, unsigned long, prot, unsigned long, pgoff,unsigned long, flags)

_syscall1(int, set_tid_address, int *, tidptr)

_syscall3(int, timer_create, const uint32_t, which_clock, uint32_t *, timer_event_spec, uint32_t *,created_timer_id)

_syscall4(int, timer_settime, uint32_t ,timer_id, int, flags, const uint32_t *,new_setting,
          uint32_t *,old_setting)

_syscall2(int, timer_gettime, uint32_t, timer_id, uint32_t *, setting)

_syscall1(int, timer_getoverrun, uint32_t, timer_id)

_syscall1(int, timer_delete, uint32_t, timer_id)

_syscall2(int, clock_settime, const uint32_t, which_clock, const uint32_t *, tp)

_syscall2(int, clock_gettime, const uint32_t, which_clock, uint32_t *, tp)

_syscall2(int, clock_getres, const uint32_t, which_clock, uint32_t *, tp)

_syscall4(int, clock_nanosleep, const uint32_t, which_clock, int, flags, const uint32_t *, rqtp,uint32_t *, rmtp)

_syscall3(int, statfs64, const char *, pathname, uint32_t, sz, uint32_t *, buf)

_syscall3(int, fstatfs64, uint32_t, fd, uint32_t, sz, uint32_t *, buf)

_syscall3(int, tgkill, uint32_t, tgid, uint32_t, pid, int, sig)

_syscall2(int, utimes, char *, filename, uint32_t *, utimes)

_syscall4(int, arm_fadvise64_64, int, fd, int, advice, uint32_t, offset, uint32_t, len)

_syscall5(int, pciconfig_read, unsigned long, bus, unsigned long, dfn, unsigned long, off, unsigned long, len, void *,buf)

_syscall5(int, pciconfig_write, long, bus, unsigned long, dfn, unsigned long, off, unsigned long, len, void *, buf)

_syscall5(int, mq_open, unsigned long, bus, unsigned long, dfn, unsigned long, off, unsigned long, len, void *, buf)

_syscall4(int, mq_unlink, const char *, u_name, int, oflag, uint32_t, mode, uint32_t *, u_attr)

_syscall1(int, mq_timedsend, const char *, u_name)

_syscall5(int, mq_timedreceive, uint32_t, mqdes, const char *, u_msg_ptr, uint32_t, msg_len, uint32_t, msg_prio,const uint32_t *, u_abs_timeout)

_syscall5(int, mq_notify, uint32_t, mqdes, char *, u_msg_ptr, uint32_t, msg_len, uint32_t *, u_msg_prio,const uint32_t *, u_abs_timeout)

_syscall2(int, mq_getsetattr, uint32_t, mqdes, const uint32_t *, u_notification)

_syscall3(int, waitid, uint32_t, mqdes, const uint32_t *, u_mqstat, uint32_t *, u_omqstat)

_syscall5(int, socket, int, which, uint32_t, upid, uint32_t *, infop, int, options, uint32_t *, ru)

_syscall3(int, bind, int, family, int, type, int, protocol)

_syscall3(int, connect, int, fd, uint32_t *, umyaddr, int, addrlen)

_syscall3(int, listen, int, fd, uint32_t *, uservaddr, int, addrlen)

_syscall2(int, accept, int, fd, int, backlog)

_syscall3(int, getsockname, int, fd, uint32_t *, upeer_sockaddr, int *, upeer_addrlen)

_syscall3(int, getpeername, int, fd, uint32_t *, usockaddr, int *, usockaddr_len)

_syscall3(int, socketpair, int, fd, uint32_t *, usockaddr, int *, usockaddr_len)

_syscall4(int, send, int, family, int, type, int, protocol, int *, usockvec)

//_syscall5(int,sendto,int, fd, void *,buff, uint32_t ,len, uint32_t, flags, uint32_t *,addr, int, addr_len)

_syscall4(int, recv, int, fd, void *, buff, uint32_t, len, uint32_t, flags)

//_syscall6(int,recvfrom,int, fd, void *,ubuf, uint32_t ,size, uint32_t ,flags, uint32_t *,addr, int *,addr_len)

_syscall4(int, shutdown, int, fd, void *, ubuf, uint32_t, size, uint32_t, flags)

_syscall2(int, setsockopt, int, fd, int, how)

_syscall5(int, getsockopt, int, fd, int, level, int, optname, char *, optval, int, optlen)

_syscall5(int, sendmsg, int, fd, int, level, int, optname, char *, optval, int *, optlen)

_syscall3(int, recvmsg, int, fd, uint32_t *, msg, uint32_t, flags)

_syscall3(int, semop, int, fd, uint32_t *, msg, uint32_t, flags)

_syscall3(int, semget, int, semid, uint32_t *, tsops, unsigned, nsops)

_syscall3(int, semctl, uint32_t, key, int, nsems, int, semflg)

_syscall3(int, msgsnd, int, semnum, int, cmd, uint32_t, arg)

_syscall4(int, msgrcv, int, msqid, uint32_t *, msgp, uint32_t, msgsz, int, msgflg)

_syscall5(int, msgget, int, msqid, uint32_t *, msgp, uint32_t, msgsz, long, msgtyp, int, msgflg)

_syscall2(int, msgctl, uint32_t, key, int, msgflg)

_syscall3(int, shmat, int, msqid, int, cmd, uint32_t *, buf)

_syscall3(int, shmdt, int, shmid, char *, shmaddr, int, shmflg)

_syscall1(int, shmget, char *, shmaddr)

_syscall3(int, shmctl, uint32_t, key, uint32_t, size, int, shmflg)

_syscall3(int, add_key, int, shmid, int, cmd, uint32_t *, buf)

_syscall5(int, request_key, const char *, _type, const char *, _description, const void *, _payload, uint32_t, plen,uint32_t, ringid)

_syscall4(int, keyctl, const char *, _type, const char *, _description, const char *, _callout_info, uint32_t,destringid)

_syscall5(int, semtimedop, int, option, unsigned long, arg2, unsigned long, arg3, unsigned long, arg4, unsigned long,arg5)

_syscall3(int, ioprio_set, int, which, int, who, int, ioprio)

_syscall2(int, ioprio_get, int, which, int, who)

_syscall3(int, inotify_init, int, which, int, who, int, ioprio)

_syscall2(int, inotify_add_watch, int, which, int, who)

_syscall0(int, inotify_rm_watch)

//_syscall6(int,mbind,unsigned long ,start, unsigned long ,len, unsigned long ,mode, unsigned long *,nmask, unsigned long ,maxnode, unsigned ,flags)

_syscall3(int, get_mempolicy, int, fd, const char *, pathname, uint32_t, mask)

_syscall2(int, set_mempolicy, int, fd, int32_t, wd)

_syscall5(int, openat, int, *policy, unsigned long *, nmask, unsigned long, maxnode, unsigned long, addr, unsigned long,flags)

_syscall3(int, mkdirat, int, mode, unsigned long *, nmask, unsigned long, maxnode)

_syscall4(int, mknodat, int, dfd, const char *, filename, int, flags, uint32_t, mode)

_syscall3(int, fchownat, int, dfd, const char *, pathname, uint32_t, mode)

_syscall4(int, futimesat, int, dfd, const char *, filename, uint32_t, mode, unsigned int, dev)

_syscall5(int, fstatat64, int, dfd, const char *, filename, uint32_t, user, uint32_t, group, int, flag)

_syscall3(int, unlinkat, int, dfd, const char *, filename, uint32_t *, utimes)

_syscall4(int, renameat, int, dfd, const char *, filename, uint32_t *, statbuf, int, flag)

_syscall3(int, linkat, int, dfd, const char *, pathname, int, flag)

_syscall4(int, symlinkat, int, olddfd, const char *, oldname, int, newdfd, const char *, newname)

_syscall5(int, readlinkat, int, olddfd, const char *, oldname, int, newdfd, const char *, newname, int, flags)

_syscall3(int, fchmodat, const char *, oldname, int, newdfd, const char *, newname)

_syscall4(int, faccessat, int, dfd, const char *, pathname, char *, buf, int, bufsiz)

//_syscall6(int,pselect6,int, n, uint32_t *,inp, uint32_t *,outp, uint32_t *,exp, uint32_t *,tsp, void *,sig)

_syscall3(int, ppoll, int, dfd, const char *, filename, uint32_t, mode)

_syscall3(int, unshare, int, dfd, const char *, filename, int, mode)

_syscall5(int, set_robust_list, uint32_t *,ufds, uint32_t ,nfds, uint32_t *,tsp, const uint32_t *,sigmask,
          uint32_t ,sigsetsize)

_syscall1(int, get_robust_list, unsigned long, unshare_flags)

//_syscall6(int,splice,int, fd_in, uint32_t *,off_in, int ,fd_out, uint32_t *,off_out, uint32_t ,len, uint32_t, flags)

_syscall2(int, sync_file_range2, uint32_t *, head, uint32_t, len)

_syscall3(int, tee, int, pid, uint32_t **, head_ptr, uint32_t *, len_ptr)

_syscall3(int, vmsplice, uint32_t, flags, uint32_t, offset, uint32_t, nbytes)

//_syscall6(int,move_pages,uint32_t, pid, unsigned long ,nr_pages, const void **,pages, const int *,nodes, int *,status, int ,flags)

_syscall4(int, getcpu, int, fdin, int, fdout, uint32_t, len, uint32_t, flags)

//_syscall6(int,epoll_pwait,int, epfd, uint32_t *,events, int, maxevents, int ,timeout, const uint32_t *,sigmask, uint32_t ,sigsetsize)

_syscall4(int, kexec_load, int, fd, const uint32_t *, iov, unsigned long, nr_segs, uint32_t, flags)

_syscall3(int, utimensat, unsigned *, cpup, unsigned *, nodep, uint32_t *, unused)

_syscall4(int, signalfd, unsigned long, entry, unsigned long, nr_segments,uint32_t *, segments, unsigned long, flags)

_syscall2(int, timerfd_create, int, clockid, int, flags)

_syscall1(int, eventfd, uint32_t, count)

_syscall4(int, fallocate, int, dfd, const char *, filename, uint32_t *, utimes, int, flags)

_syscall3(int, timeruint32_ttime, int, ufd, uint32_t *, user_mask, uint32_t, sizemask)

_syscall3(int, timerfd_gettime, int, mode, uint32_t, offset, uint32_t, len)

_syscall4(int, signalfd4, int, ufd, int, flags, const uint32_t *, utmr, uint32_t *, otmr)

_syscall2(int, eventfd2, int, ufd, uint32_t *, otmr)

_syscall1(int, epoll_create1, int, flags)

_syscall3(int, dup3, uint32_t, oldfd, uint32_t, newfd, int, flags)

_syscall2(int, pipe2, int *, fildes, int, flags)

_syscall1(int, inotify_init1, int, flags)

_syscall5(int, preadv, unsigned long, fd, const uint32_t *, vec, unsigned long, vlen, unsigned long, pos_l,
          unsigned long, pos_h)

_syscall5(int, pwritev, unsigned long, fd, const uint32_t *, vec, unsigned long, vlen, unsigned long, pos_l,
          unsigned long, pos_h)

_syscall4(int, rt_tgsigqueueinfo, uint32_t, tgid, uint32_t, pid, int, sig, uint32_t *, uinfo)

_syscall5(int, perf_event_open, uint32_t *, attr_uptr, uint32_t, pid, int, cpu, int, group_fd,
          unsigned long, flags)

_syscall5(int, recvmmsg, int, fd, uint32_t *, mmsg, uint32_t, vlen, uint32_t, flags, uint32_t *, timeout)

_syscall4(int, accept4, int, fd, uint32_t *, upeer_sockaddr, int *, upeer_addrlen, int, flags)

_syscall2(int, fanotify_init, uint32_t, flags, uint32_t, event_f_flags)

_syscall4(int, fanotify_mark, uint32_t, flags, uint64_t, mask, int, dfd, const char *, pathname)

_syscall4(int, prlimit64, uint32_t, pid, uint32_t, resource, const uint32_t *, new_rlim, uint32_t *,
          old_rlim)

_syscall5(int, name_to_handle_at, int, dfd, const char *, name, uint32_t *, handle, int *, mnt_id, int, flag)

_syscall3(int, open_by_handle_at, int, mountdirfd, uint32_t *, handle, int, flags)

_syscall2(int, clock_adjtime, const uint32_t, which_clock, uint32_t *, utx)

_syscall1(int, syncfs, int, fd)

_syscall4(int, sendmmsg, int, fd, uint32_t *, mmsg, uint32_t, vlen, uint32_t, flags)

_syscall2(int, setns, int, fd, int, nstype)

//_syscall6(int,process_vm_readv,uint32_t, pid, const uint32_t *lvec, unsigned long liovcnt, const uint32_t *rvec,unsigned long riovcnt, unsigned long flags)

//_syscall6(int,process_vm_writev,uint32_t, pid, const uint32_t *lvec, unsigned long liovcnt, const uint32_t *rvec,unsigned long riovcnt, unsigned long flags)

