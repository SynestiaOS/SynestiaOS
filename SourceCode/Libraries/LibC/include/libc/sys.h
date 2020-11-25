//
// Created by XingfengYang on 2020/7/27.
//
#ifndef __LIBRARY_LIBC_H__
#define __LIBRARY_LIBC_H__

#include "libc/stdint.h"

#define asmlinkage __attribute__((regparm(0)))

#define _syscall5(type, name, type1, name1, type2, name2, type3, name3, type4, name4, type5, name5)              \
    type name(type1 name1, type2 name2, type3 name3, type4 name4, type5 name5) {                                 \
        uint32_t result;                                                                                         \
        __asm__ __volatile__("push {lr}\n\t"                                                                     \
                             "mov r0, #0\n\t"                                                                    \
                             "mov r1, %2\n\t"                                                                    \
                             "mov r2, %3\n\t"                                                                    \
                             "mov r3, #0\n\t"                                                                    \
                             "mov r4, %4\n\t"                                                                    \
                             "mov r5, %5\n\t"                                                                    \
                             "mov r6, %6\n\t"                                                                    \
                             "mov r7, %1\n\t"                                                                    \
                             "swi 0x0\n\t"                                                                       \
                             "mov %0, r0\n\t"                                                                    \
                             "pop {lr}\n\t"                                                                      \
                             : "=r"(result)                                                                      \
                             : "r"(__SYSCALL_##name), "r"(name1), "r"(name2), "r"(name3), "r"(name4), "r"(name5) \
                             : "r0", "r1", "r2", "r3", "r4", "r7");                                              \
        return result;                                                                                           \
    }

#define _syscall4(type, name, type1, name1, type2, name2, type3, name3, type4, name4)                \
    type name(type1 name1, type2 name2, type3 name3, type4 name4) {                                  \
        uint32_t result;                                                                             \
        __asm__ __volatile__("push {lr}\n\t"                                                         \
                             "mov r0, #0\n\t"                                                        \
                             "mov r1, %2\n\t"                                                        \
                             "mov r2, %3\n\t"                                                        \
                             "mov r3, #0\n\t"                                                        \
                             "mov r4, %4\n\t"                                                        \
                             "mov r5, %5\n\t"                                                        \
                             "mov r7, %1\n\t"                                                        \
                             "swi 0x0\n\t"                                                           \
                             "mov %0, r0\n\t"                                                        \
                             "pop {lr}\n\t"                                                          \
                             : "=r"(result)                                                          \
                             : "r"(__SYSCALL_##name), "r"(name1), "r"(name2), "r"(name3), "r"(name4) \
                             : "r0", "r1", "r2", "r3", "r4", "r7");                                  \
        return result;                                                                               \
    }

#define _syscall3(type, name, type1, name1, type2, name2, type3, name3)                  \
    type name(type1 name1, type2 name2, type3 name3) {                                   \
        uint32_t result;                                                                 \
        __asm__ __volatile__("push {lr}\n\t"                                             \
                             "mov r0, #0\n\t"                                            \
                             "mov r1, %2\n\t"                                            \
                             "mov r2, %3\n\t"                                            \
                             "mov r3, #0\n\t"                                            \
                             "mov r4, %4\n\t"                                            \
                             "mov r7, %1\n\t"                                            \
                             "swi 0x0\n\t"                                               \
                             "mov %0, r0\n\t"                                            \
                             "pop {lr}\n\t"                                              \
                             : "=r"(result)                                              \
                             : "r"(__SYSCALL_##name), "r"(name1), "r"(name2), "r"(name3) \
                             : "r0", "r1", "r2", "r3", "r4", "r7");                      \
        return result;                                                                   \
    }

#define _syscall2(type, name, type1, name1, type2, name2)                    \
    type name(type1 name1, type2 name2) {                                    \
        uint32_t result;                                                     \
        __asm__ __volatile__("push {lr}\n\t"                                 \
                             "mov r0, #0\n\t"                                \
                             "mov r1, %2\n\t"                                \
                             "mov r2, %3\n\t"                                \
                             "mov r3, #0\n\t"                                \
                             "mov r7, %1\n\t"                                \
                             "swi 0x0\n\t"                                   \
                             "mov %0, r0\n\t"                                \
                             "pop {lr}\n\t"                                  \
                             : "=r"(result)                                  \
                             : "r"(__SYSCALL_##name), "r"(name1), "r"(name2) \
                             : "r0", "r1", "r2", "r3", "r4", "r7");          \
        return result;                                                       \
    }

#define _syscall1(type, name, type1, name1)                         \
    type name(type1 name1) {                                        \
        uint32_t result;                                            \
        __asm__ __volatile__("push {lr}\n\t"                        \
                             "mov r0, #0\n\t"                       \
                             "mov r1, %2\n\t"                       \
                             "mov r3, #0\n\t"                       \
                             "mov r7, %1\n\t"                       \
                             "swi 0x0\n\t"                          \
                             "mov %0, r0\n\t"                       \
                             "pop {lr}\n\t"                         \
                             : "=r"(result)                         \
                             : "r"(__SYSCALL_##name), "r"(name1)    \
                             : "r0", "r1", "r2", "r3", "r4", "r7"); \
        return result;                                              \
    }

#define _syscall0(type, name)                                       \
    type name() {                                                   \
        uint32_t result;                                            \
        __asm__ __volatile__("push {lr}\n\t"                        \
                             "mov r0, #0\n\t"                       \
                             "mov r3, #0\n\t"                       \
                             "mov r7, %1\n\t"                       \
                             "swi 0x0\n\t"                          \
                             "mov %0, r0\n\t"                       \
                             "pop {lr}\n\t"                         \
                             : "=r"(result)                         \
                             : "r"(__SYSCALL_##name)                \
                             : "r0", "r1", "r2", "r3", "r4", "r7"); \
        return result;                                              \
    }


#define __SYSCALL_restart_syscall 0
#define __SYSCALL_exit 1
#define __SYSCALL_fork 2
#define __SYSCALL_read 3
#define __SYSCALL_write 4
#define __SYSCALL_open 5
#define __SYSCALL_close 6
#define __SYSCALL_creat 7
#define __SYSCALL_link 8
#define __SYSCALL_unlink 9
#define __SYSCALL_execve 10
#define __SYSCALL_chdir 11
#define __SYSCALL_time 12
#define __SYSCALL_mknod 13
#define __SYSCALL_chmod 14
#define __SYSCALL_lchown 15
#define __SYSCALL_lseek 16
#define __SYSCALL_getpid 17
#define __SYSCALL_mount 18
#define __SYSCALL_umount 19
#define __SYSCALL_setuid 20
#define __SYSCALL_getuid 21
#define __SYSCALL_stime 22
#define __SYSCALL_ptrace 23
#define __SYSCALL_alarm 24
#define __SYSCALL_pause 25
#define __SYSCALL_utime 26
#define __SYSCALL_access 27
#define __SYSCALL_nice 28
#define __SYSCALL_sync 29
#define __SYSCALL_kill 30
#define __SYSCALL_rename 31
#define __SYSCALL_mkdir 32
#define __SYSCALL_rmdir 33
#define __SYSCALL_dup 34
#define __SYSCALL_pipe 35
#define __SYSCALL_times 36
#define __SYSCALL_brk 37
#define __SYSCALL_setgid 38
#define __SYSCALL_getgid 39
#define __SYSCALL_geteuid 40
#define __SYSCALL_getegid 41
#define __SYSCALL_acct 42
#define __SYSCALL_umount2 43
#define __SYSCALL_ioctl 44
#define __SYSCALL_fcntl 45
#define __SYSCALL_setpgid 46
#define __SYSCALL_umask 47
#define __SYSCALL_chroot 48
#define __SYSCALL_ustat 49
#define __SYSCALL_dup2 50
#define __SYSCALL_getppid 51
#define __SYSCALL_getpgrp 52
#define __SYSCALL_setsid 53
#define __SYSCALL_sigaction 54
#define __SYSCALL_setreuid 55
#define __SYSCALL_setregid 56
#define __SYSCALL_sigsuspend 57
#define __SYSCALL_sigpending 58
#define __SYSCALL_sethostname 59
#define __SYSCALL_setrlimit 60
#define __SYSCALL_getrlimit 61
#define __SYSCALL_getrusage 62
#define __SYSCALL_gettimeofday 63
#define __SYSCALL_settimeofday 64
#define __SYSCALL_getgroups 65
#define __SYSCALL_setgroups 66
#define __SYSCALL_select 67
#define __SYSCALL_symlink 68
#define __SYSCALL_readlink 69
#define __SYSCALL_uselib 70
#define __SYSCALL_swapon 71
#define __SYSCALL_reboot 72
#define __SYSCALL_readdir 73
#define __SYSCALL_mmap 74
#define __SYSCALL_munmap 75
#define __SYSCALL_truncate 76
#define __SYSCALL_ftruncate 77
#define __SYSCALL_fchmod 78
#define __SYSCALL_fchown 79
#define __SYSCALL_getpriority 80
#define __SYSCALL_setpriority 81
#define __SYSCALL_statfs 82
#define __SYSCALL_fstatfs 83
#define __SYSCALL_socketcall 84
#define __SYSCALL_syslog 85
#define __SYSCALL_setitimer 86
#define __SYSCALL_getitimer 87
#define __SYSCALL_stat 88
#define __SYSCALL_lstat 89
#define __SYSCALL_fstat 90
#define __SYSCALL_vhangup 91
#define __SYSCALL_syscall 92
#define __SYSCALL_wait4 93
#define __SYSCALL_swapoff 94
#define __SYSCALL_sysinfo 95
#define __SYSCALL_ipc 96
#define __SYSCALL_fsync 97
#define __SYSCALL_sigreturn 98
#define __SYSCALL_clone 99
#define __SYSCALL_setdomainname 100
#define __SYSCALL_uname 101
#define __SYSCALL_adjtimex 102
#define __SYSCALL_mprotect 103
#define __SYSCALL_sigprocmask 104
#define __SYSCALL_init_module 105
#define __SYSCALL_delete_module 106
#define __SYSCALL_quotactl 107
#define __SYSCALL_getpgid 108
#define __SYSCALL_fchdir 109
#define __SYSCALL_bdflush 110
#define __SYSCALL_sysfs 111
#define __SYSCALL_personality 112
#define __SYSCALL_setfsuid 113
#define __SYSCALL_setfsgid 114
#define __SYSCALL__llseek 115
#define __SYSCALL_getdents 116
#define __SYSCALL__newselect 117
#define __SYSCALL_flock 118
#define __SYSCALL_msync 119
#define __SYSCALL_readv 120
#define __SYSCALL_writev 121
#define __SYSCALL_getsid 122
#define __SYSCALL_fdatasync 123
#define __SYSCALL__sysctl 124
#define __SYSCALL_mlock 125
#define __SYSCALL_munlock 126
#define __SYSCALL_mlockall 127
#define __SYSCALL_munlockall 128
#define __SYSCALL_sched_setparam 129
#define __SYSCALL_sched_getparam 130
#define __SYSCALL_sched_setscheduler 131
#define __SYSCALL_sched_getscheduler 132
#define __SYSCALL_sched_yield 133
#define __SYSCALL_sched_get_priority_max 134
#define __SYSCALL_sched_get_priority_min 135
#define __SYSCALL_sched_rr_get_interval 136
#define __SYSCALL_nanosleep 137
#define __SYSCALL_mremap 138
#define __SYSCALL_setresuid 139
#define __SYSCALL_getresuid 140
#define __SYSCALL_poll 141
#define __SYSCALL_nfsservctl 142
#define __SYSCALL_setresgid 143
#define __SYSCALL_getresgid 144
#define __SYSCALL_prctl 145
#define __SYSCALL_rt_sigreturn 146
#define __SYSCALL_rt_sigaction 147
#define __SYSCALL_rt_sigprocmask 148
#define __SYSCALL_rt_sigpending 149
#define __SYSCALL_rt_sigtimedwait 150
#define __SYSCALL_rt_sigqueueinfo 151
#define __SYSCALL_rt_sigsuspend 152
#define __SYSCALL_pread64 153
#define __SYSCALL_pwrite64 154
#define __SYSCALL_chown 155
#define __SYSCALL_getcwd 156
#define __SYSCALL_capget 157
#define __SYSCALL_capset 158
#define __SYSCALL_sendfile 159
#define __SYSCALL_vfork 160
#define __SYSCALL_ugetrlimit 161
#define __SYSCALL_mmap2 162
#define __SYSCALL_truncate64 163
#define __SYSCALL_ftruncate64 164
#define __SYSCALL_stat64 165
#define __SYSCALL_lstat64 166
#define __SYSCALL_fstat64 167
#define __SYSCALL_lchown32 168
#define __SYSCALL_getuid32 169
#define __SYSCALL_getgid32 170
#define __SYSCALL_geteuid32 171
#define __SYSCALL_getegid32 172
#define __SYSCALL_setreuid32 173
#define __SYSCALL_setregid32 174
#define __SYSCALL_getgroups32 175
#define __SYSCALL_setgroups32 176
#define __SYSCALL_fchown32 177
#define __SYSCALL_setresuid32 178
#define __SYSCALL_getresuid32 179
#define __SYSCALL_setresgid32 180
#define __SYSCALL_getresgid32 181
#define __SYSCALL_chown32 182
#define __SYSCALL_setuid32 183
#define __SYSCALL_setgid32 184
#define __SYSCALL_setfsuid32 185
#define __SYSCALL_setfsgid32 186
#define __SYSCALL_getdents64 187
#define __SYSCALL_pivot_root 188
#define __SYSCALL_mincore 189
#define __SYSCALL_madvise 190
#define __SYSCALL_fcntl64 191
#define __SYSCALL_gettid 192
#define __SYSCALL_readahead 193
#define __SYSCALL_setxattr 194
#define __SYSCALL_lsetxattr 195
#define __SYSCALL_fsetxattr 196
#define __SYSCALL_getxattr 197
#define __SYSCALL_lgetxattr 198
#define __SYSCALL_fgetxattr 199
#define __SYSCALL_listxattr 200
#define __SYSCALL_llistxattr 201
#define __SYSCALL_flistxattr 202
#define __SYSCALL_removexattr 203
#define __SYSCALL_lremovexattr 204
#define __SYSCALL_fremovexattr 205
#define __SYSCALL_tkill 206
#define __SYSCALL_sendfile64 207
#define __SYSCALL_futex 208
#define __SYSCALL_sched_setaffinity 209
#define __SYSCALL_sched_getaffinity 210
#define __SYSCALL_io_setup 211
#define __SYSCALL_io_destroy 212
#define __SYSCALL_io_getevents 213
#define __SYSCALL_io_submit 214
#define __SYSCALL_io_cancel 215
#define __SYSCALL_exit_group 216
#define __SYSCALL_lookup_dcookie 217
#define __SYSCALL_epoll_create 218
#define __SYSCALL_epoll_ctl 219
#define __SYSCALL_epoll_wait 220
#define __SYSCALL_remap_file_pages 221
#define __SYSCALL_set_tid_address 222
#define __SYSCALL_timer_create 223
#define __SYSCALL_timer_settime 224
#define __SYSCALL_timer_gettime 225
#define __SYSCALL_timer_getoverrun 226
#define __SYSCALL_timer_delete 227
#define __SYSCALL_clock_settime 228
#define __SYSCALL_clock_gettime 229
#define __SYSCALL_clock_getres 230
#define __SYSCALL_clock_nanosleep 231
#define __SYSCALL_statfs64 232
#define __SYSCALL_fstatfs64 233
#define __SYSCALL_tgkill 234
#define __SYSCALL_utimes 235
#define __SYSCALL_arm_fadvise64_64 236
#define __SYSCALL_pciconfig_read 237
#define __SYSCALL_pciconfig_write 238
#define __SYSCALL_mq_open 239
#define __SYSCALL_mq_unlink 240
#define __SYSCALL_mq_timedsend 241
#define __SYSCALL_mq_timedreceive 242
#define __SYSCALL_mq_notify 243
#define __SYSCALL_mq_getsetattr 244
#define __SYSCALL_waitid 245
#define __SYSCALL_socket 246
#define __SYSCALL_bind 247
#define __SYSCALL_connect 248
#define __SYSCALL_listen 249
#define __SYSCALL_accept 250
#define __SYSCALL_getsockname 251
#define __SYSCALL_getpeername 252
#define __SYSCALL_socketpair 253
#define __SYSCALL_send 254
#define __SYSCALL_sendto 255
#define __SYSCALL_recv 256
#define __SYSCALL_recvfrom 257
#define __SYSCALL_shutdown 258
#define __SYSCALL_setsockopt 259
#define __SYSCALL_getsockopt 260
#define __SYSCALL_sendmsg 261
#define __SYSCALL_recvmsg 262
#define __SYSCALL_semop 263
#define __SYSCALL_semget 264
#define __SYSCALL_semctl 265
#define __SYSCALL_msgsnd 266
#define __SYSCALL_msgrcv 267
#define __SYSCALL_msgget 268
#define __SYSCALL_msgctl 269
#define __SYSCALL_shmat 270
#define __SYSCALL_shmdt 271
#define __SYSCALL_shmget 272
#define __SYSCALL_shmctl 273
#define __SYSCALL_add_key 274
#define __SYSCALL_request_key 275
#define __SYSCALL_keyctl 276
#define __SYSCALL_semtimedop 277
#define __SYSCALL_ioprio_set 278
#define __SYSCALL_ioprio_get 279
#define __SYSCALL_inotify_init 280
#define __SYSCALL_inotify_add_watch 281
#define __SYSCALL_inotify_rm_watch 282
#define __SYSCALL_mbind 283
#define __SYSCALL_get_mempolicy 284
#define __SYSCALL_set_mempolicy 285
#define __SYSCALL_openat 286
#define __SYSCALL_mkdirat 287
#define __SYSCALL_mknodat 288
#define __SYSCALL_fchownat 289
#define __SYSCALL_futimesat 290
#define __SYSCALL_fstatat64 291
#define __SYSCALL_unlinkat 292
#define __SYSCALL_renameat 293
#define __SYSCALL_linkat 294
#define __SYSCALL_symlinkat 295
#define __SYSCALL_readlinkat 296
#define __SYSCALL_fchmodat 297
#define __SYSCALL_faccessat 298
#define __SYSCALL_pselect6 299
#define __SYSCALL_ppoll 300
#define __SYSCALL_unshare 301
#define __SYSCALL_set_robust_list 302
#define __SYSCALL_get_robust_list 303
#define __SYSCALL_splice 304
#define __SYSCALL_sync_file_range2 305
#define __SYSCALL_tee 306
#define __SYSCALL_vmsplice 307
#define __SYSCALL_move_pages 308
#define __SYSCALL_getcpu 309
#define __SYSCALL_epoll_pwait 310
#define __SYSCALL_kexec_load 311
#define __SYSCALL_utimensat 312
#define __SYSCALL_signalfd 313
#define __SYSCALL_timerfd_create 314
#define __SYSCALL_eventfd 315
#define __SYSCALL_fallocate 316
#define __SYSCALL_timeruint32_ttime 317
#define __SYSCALL_timerfd_gettime 318
#define __SYSCALL_signalfd4 319
#define __SYSCALL_eventfd2 320
#define __SYSCALL_epoll_create1 321
#define __SYSCALL_dup3 322
#define __SYSCALL_pipe2 323
#define __SYSCALL_inotify_init1 324
#define __SYSCALL_preadv 325
#define __SYSCALL_pwritev 326
#define __SYSCALL_rt_tgsigqueueinfo 327
#define __SYSCALL_perf_event_open 328
#define __SYSCALL_recvmmsg 329
#define __SYSCALL_accept4 330
#define __SYSCALL_fanotify_init 331
#define __SYSCALL_fanotify_mark 332
#define __SYSCALL_prlimit64 333
#define __SYSCALL_name_to_handle_at 334
#define __SYSCALL_open_by_handle_at 335
#define __SYSCALL_clock_adjtime 336
#define __SYSCALL_syncfs 337
#define __SYSCALL_sendmmsg 338
#define __SYSCALL_setns 339
#define __SYSCALL_process_vm_readv 340
#define __SYSCALL_process_vm_writev 341

int restart_syscall();

int exit(int error_code);

int fork();

int read(uint32_t fd, char *buf, uint32_t count);

int write(uint32_t fd, const char *buf, uint32_t count);

int open(const char *filename, int flags, uint32_t mode);

int close(uint32_t fd);

int creat(const char *pathname, uint32_t mode);

int link(const char *oldname, const char *newname);

int unlink(const char *pathname);

int execve(const char *filenamei, const char *argv, const char *envp);

int chdir(const char *filename);

int time(uint32_t *tloc);

int mknod(const char *filename, uint32_t mode, unsigned int dev);

int chmod(const char *filename, uint32_t mode);

int lchown(const char *filename, uint32_t user, uint32_t group);

int lseek(uint32_t fd, uint32_t offset, uint32_t origin);

int getpid();

int mount(char *dev_name, char *dir_name, char *type, unsigned long flags, void *data);

int umount(char *name, int flags);

int setuid(uint32_t uid);

int getuid();

int stime(uint32_t *tptr);

int ptrace(long request, long pid, unsigned long addr, unsigned long data);

int alarm(uint32_t seconds);

int pause();

int utime(char *filename, uint32_t *times);

int access(const char *filename, int mode);

int nice(int increment);

int sync();

int kill(uint32_t pid, int sig);

int rename(const char *oldname, const char *newname);

int mkdir(const char *pathname, uint32_t mode);

int rmdir(const char *pathname);

int dup(uint32_t fildes);

int pipe(int *fildes);

int times(uint32_t *tbuf);

int brk(unsigned long brk);

int setgid(uint32_t gid);

int getgid();

int geteuid();

int getegid();

int acct(const char *name);

int umount2(char *name, int flags);

int ioctl(uint32_t fd, uint32_t cmd, unsigned long arg);

int fcntl(uint32_t fd, uint32_t cmd, unsigned long arg);

int setpgid(uint32_t pid, uint32_t pgid);

int umask(int mask);

int chroot(const char *filename);

int ustat(unsigned int dev, uint32_t *ubuf);

int dup2(uint32_t oldfd, uint32_t newfd);

int getppid();

int getpgrp();

int setsid();

int sigaction(int sig, const uint32_t *act, uint32_t *oact);

int setreuid(uint32_t ruid, uint32_t euid);

int setregid(uint32_t rgid, uint32_t egid);

int sigsuspend(int restart, unsigned long oldmask, uint32_t mask);

int sigpending(uint32_t *set);

int sethostname(char *name, int len);

int setrlimit(uint32_t resource, uint32_t *rlim);

int getrlimit(uint32_t resource, uint32_t *rlim);

int getrusage(int who, uint32_t *ru);

int gettimeofday(uint32_t *tv, uint32_t *tz);

int settimeofday(uint32_t *tv, uint32_t *tz);

int getgroups(int gidsetsize, uint32_t *grouplist);

int setgroups(int gidsetsize, uint32_t *grouplist);

int select(int n, uint32_t *inp, uint32_t *outp, uint32_t *exp, uint32_t *tvp);

int symlink(const char *oldname, const char *newname);

int readlink(const char *path, char *buf, int bufsiz);

int uselib(const char *library);

int swapon(const char *specialfile, int swap_flags);

int reboot(int magic1, int magic2, uint32_t cmd, void *arg);

int readdir(uint32_t fd, uint32_t *dirent, uint32_t count);

int mmap(uint32_t *arg);

int munmap(unsigned long addr, uint32_t len);

int truncate(const char *path, long length);

int ftruncate(uint32_t fd, unsigned long length);

int fchmod(uint32_t fd, uint32_t mode);

int fchown(uint32_t fd, uint32_t user);

int getpriority(int which, int who);

int setpriority(int which, int who, int niceval);

int statfs(const char *pathname, uint32_t *buf);

int fstatfs(uint32_t fd, uint32_t *buf);

int socketcall(int call, unsigned long *args);

int syslog(int type, char *buf, int len);

int setitimer(int which, uint32_t *value, uint32_t *ovalue);

int getitimer(int which, uint32_t *value);

int stat(const char *filename, uint32_t *statbuf);

int lstat(const char *filename, uint32_t *statbuf);

int fstat(uint32_t fd, uint32_t *statbuf);

int vhangup();

int syscall();

int wait4(uint32_t upid, int *stat_addr, int options, uint32_t *ru);

int swapoff(const char *specialfile);

int sysinfo(uint32_t *info);

int ipc(uint32_t call, int first, unsigned long second, unsigned long third, void *ptr, long fifth);

int fsync(uint32_t fd);

int sigreturn();

int clone(unsigned long clone_flags, unsigned long newsp, int *parent_tidptr, int tls_val, int *child_tidptr);

int setdomainname(char *name, int len);

int uname(uint32_t *name);

int adjtimex(uint32_t *txc_p);

int mprotect(unsigned long start, uint32_t len, unsigned long prot);

int sigprocmask(int how, uint32_t *nset, uint32_t *oset);

int init_module(void *umod, unsigned long len, const char *uargs);

int delete_module(const char *name_user, uint32_t flags);

int quotactl(uint32_t cmd);

int getpgid(uint32_t pid);

int fchdir(uint32_t fd);

int bdflush(int func, long data);

int sysfs(int option, unsigned long arg1, unsigned long arg2);

int personality(uint32_t personality);

int setfsuid(uint32_t uid);

int setfsgid(uint32_t gid);

int _llseek(uint32_t fd, unsigned long offset_high, unsigned long offset_low,
            int *result, uint32_t origin);

int getdents(uint32_t fd, uint32_t *dirent, uint32_t count);

int _newselect(int n, uint32_t *inp, uint32_t *outp, uint32_t *exp, uint32_t *tvp);

int flock(uint32_t fd, uint32_t cmd);

int msync(unsigned long start, uint32_t len, int flags);

int readv(unsigned long fd, const uint32_t *vec, unsigned long vlen);

int writev(unsigned long fd, const uint32_t *vec, unsigned long vlen);

int getsid(uint32_t pid);

int fdatasync(uint32_t fd);

int _sysctl(uint32_t *args);

int mlock(unsigned long start, uint32_t len);

int munlock(unsigned long start, uint32_t len);

int mlockall(int flags);

int munlockall();

int sched_setparam(uint32_t pid, uint32_t *param);

int sched_getparam(uint32_t pid, uint32_t *param);

int sched_setscheduler(uint32_t pid, int policy, uint32_t *param);

int sched_getscheduler(uint32_t pid);

int sched_yield();

int sched_get_priority_max(int policy);

int sched_get_priority_min(int policy);

int sched_rr_get_interval(uint32_t pid, uint32_t *interval);

int nanosleep(uint32_t *rqtp, uint32_t *rmtp);

int mremap(unsigned long addr, unsigned long old_len, unsigned long new_len, unsigned long flags,
           unsigned long new_addr);

int setresuid(uint32_t ruid, uint32_t euid, uint32_t suid);

int getresuid(uint32_t *ruidp, uint32_t *euidp, uint32_t *suidp);

int poll(uint32_t *ufds, uint32_t nfds, int timeout_msecs);

int nfsservctl();

int setresgid(uint32_t rgid, uint32_t egid, uint32_t sgid32_t);

int getresgid(uint32_t *rgidp, uint32_t *egidp, uint32_t *sgidp);

int prctl(int option, unsigned long arg2, unsigned long arg3, unsigned long arg4, unsigned long arg5);

int rt_sigreturn();

int rt_sigaction(int sig, const uint32_t *act, uint32_t *oact, uint32_t sigsetsize);

int rt_sigprocmask(int how, uint32_t *nset, uint32_t *oset, uint32_t sigsetsize);

int rt_sigpending(uint32_t *set, uint32_t sigsetsize);

int rt_sigtimedwait(const uint32_t *uthese, uint32_t *uinfo, const uint32_t *uts,
                    int sigsetsize);

int rt_sigqueueinfo(uint32_t pid, int sig, uint32_t *uinfo);

int rt_sigsuspend(uint32_t *unewset, uint32_t sigsetsize);

int pread64(char *buf, uint32_t count, uint32_t pos);

int pwrite64(const char *buf, uint32_t count, uint32_t pos);

int chown(const char *filename, uint32_t user, uint32_t group);

int getcwd(char *buf, unsigned long size);

int capget(uint32_t header, uint32_t dataptr);

int capset(uint32_t header, const uint32_t data);

int sendfile(int out_fd, int in_fd, uint32_t *offset, uint32_t count);

int vfork();

int ugetrlimit(uint32_t resource, uint32_t *rlim);

int mmap2(unsigned long addr, unsigned long len, unsigned long prot, unsigned long flags, unsigned long fd,
          unsigned long pgoff);

int truncate64(uint32_t length);

int ftruncate64(uint32_t length);

int stat64(const char *filename, uint32_t *statbuf);

int lstat64(const char *filename, uint32_t *statbuf);

int fstat64(unsigned long fd, uint32_t *statbuf);

int lchown32(const char *filename, uint32_t user, uint32_t group);

int getuid32();

int getgid32();

int geteuid32();

int getegid32();

int setreuid32(uint32_t rui, uint32_t euid);

int setregid32(uint32_t rgid, uint32_t egid);

int getgroups32(int gidsetsize, uint32_t *grouplist);

int setgroups32(int gidsetsize, uint32_t *grouplist);

int fchown32(uint32_t fd, uint32_t user, uint32_t group);

int setresuid32(uint32_t ruid, uint32_t euid, uint32_t suid);

int getresuid32(uint32_t *ruidp, uint32_t *euidp, uint32_t *suidp);

int setresgid32(uint32_t rgid, uint32_t egid, uint32_t sgid);

int getresgid32(uint32_t *rgidp, uint32_t *egidp, uint32_t *sgidp);

int chown32(const char *filename, uint32_t user, uint32_t group);

int setuid32(uint32_t uid);

int setgid32(uint32_t gid);

int setfsuid32(uint32_t uid);

int setfsgid32(uint32_t gid);

int getdents64(uint32_t fd, uint32_t *dirent, uint32_t count);

int pivot_root(const char *new_root, const char *put_old);

int mincore(unsigned long start, uint32_t len, unsigned char *vec);

int madvise(unsigned long start, uint32_t len_in, int behavior);

int fcntl64(uint32_t fd, uint32_t cmd, unsigned long arg);

int gettid();

int readahead(uint32_t offset, uint32_t count);

int setxattr(const char *pathname, const char *name, const void *value, uint32_t size, int flags);

int lsetxattr(const char *pathname, const char *name, const void *value, uint32_t size, int flags);

int fsetxattr(int fd, const char *name, const void *value, uint32_t size, int flags);

int getxattr(const char *pathname, const char *name, void *value, uint32_t size);

int lgetxattr(const char *pathname, const char *name, void *value, uint32_t size);

int fgetxattr(int fd, const char *name, void *value, uint32_t size);

int listxattr(const char *pathname, char *list, uint32_t size);

int llistxattr(const char *pathname, char *list, uint32_t size);

int flistxattr(int fd, char *list, uint32_t size);

int removexattr(const char *pathname, const char *name);

int lremovexattr(const char *pathname, const char *name);

int fremovexattr(int fd, const char *name);

int tkill(uint32_t pid, int sig);

int sendfile64(int out_fd, int in_fd, uint32_t *offset, uint32_t count);

int futex(uint32_t *uaddr, int op, uint32_t val, uint32_t *utime, uint32_t *uaddr2, uint32_t val3);

int sched_setaffinity(uint32_t pid, uint32_t len, unsigned long *user_mask_ptr);

int sched_getaffinity(uint32_t pid, uint32_t len, unsigned long *user_mask_ptr);

int io_setup(unsigned int nr_events, uint32_t *ctxp);

int io_destroy(uint32_t ctx);

int io_getevents(uint32_t ctx_id, long min_nr, long nr, uint32_t *events, uint32_t *timeout);

int io_submit(uint32_t ctx_id, long nr, uint32_t **iocbpp);

int io_cancel(uint32_t ctx_id, uint32_t *iocb, uint32_t *result);

int exit_group(int error_code);

int lookup_dcookie(char *buf, uint32_t len);

int epoll_create(int size);

int epoll_ctl(int epfd, int op, int fd, uint32_t *event);

int epoll_wait(int epfd, uint32_t *events, int maxevents, int timeout);

int remap_file_pages(unsigned long start, unsigned long size, unsigned long prot, unsigned long pgoff,
                     unsigned long flags);

int set_tid_address(int *tidptr);

int timer_create(const uint32_t which_clock, uint32_t *timer_event_spec, uint32_t *created_timer_id);

int timer_settime(uint32_t timer_id, int flags, const uint32_t *new_setting,
                  uint32_t *old_setting);

int timer_gettime(uint32_t timer_id, uint32_t *setting);

int timer_getoverrun(uint32_t timer_id);

int timer_delete(uint32_t timer_id);

int clock_settime(const uint32_t which_clock, const uint32_t *tp);

int clock_gettime(const uint32_t which_clock, uint32_t *tp);

int clock_getres(const uint32_t which_clock, uint32_t *tp);

int clock_nanosleep(const uint32_t which_clock, int flags, const uint32_t *rqtp, uint32_t *rmtp);

int statfs64(const char *pathname, uint32_t sz, uint32_t *buf);

int fstatfs64(uint32_t fd, uint32_t sz, uint32_t *buf);

int tgkill(uint32_t tgid, uint32_t pid, int sig);

int utimes(char *filename, uint32_t *utimes);

int arm_fadvise64_64(int fd, int advice, uint32_t offset, uint32_t len);


int pciconfig_read(unsigned long bus, unsigned long dfn, unsigned long off, unsigned long len, void *buf);

int pciconfig_write(long bus, unsigned long dfn, unsigned long off, unsigned long len, void *buf);

int mq_open(unsigned long bus, unsigned long dfn, unsigned long off, unsigned long len, void *buf);

int mq_unlink(const char *u_name, int oflag, uint32_t mode, uint32_t *u_attr);

int mq_timedsend(const char *u_name);

int mq_timedreceive(uint32_t mqdes, const char *u_msg_ptr, uint32_t msg_len, uint32_t msg_prio,
                    const uint32_t *u_abs_timeout);

int mq_notify(uint32_t mqdes, char *u_msg_ptr, uint32_t msg_len, uint32_t *u_msg_prio,
              const uint32_t *u_abs_timeout);

int mq_getsetattr(uint32_t mqdes, const uint32_t *u_notification);

int waitid(uint32_t mqdes, const uint32_t *u_mqstat, uint32_t *u_omqstat);

int socket(int which, uint32_t upid, uint32_t *infop, int options, uint32_t *ru);

int bind(int family, int type, int protocol);

int connect(int fd, uint32_t *umyaddr, int addrlen);

int listen(int fd, uint32_t *uservaddr, int addrlen);

int accept(int fd, int backlog);

int getsockname(int fd, uint32_t *upeer_sockaddr, int *upeer_addrlen);

int getpeername(int fd, uint32_t *usockaddr, int *usockaddr_len);

int socketpair(int fd, uint32_t *usockaddr, int *usockaddr_len);

int send(int family, int type, int protocol, int *usockvec);

int sendto(int fd, void *buff, uint32_t len, uint32_t flags, uint32_t *addr, int addr_len);

int recv(int fd, void *buff, uint32_t len, uint32_t flags);

int recvfrom(int fd, void *ubuf, uint32_t size, uint32_t flags, uint32_t *addr, int *addr_len);

int shutdown(int fd, void *ubuf, uint32_t size, uint32_t flags);

int setsockopt(int fd, int how);

int getsockopt(int fd, int level, int optname, char *optval, int optlen);

int sendmsg(int fd, int level, int optname, char *optval, int *optlen);

int recvmsg(int fd, uint32_t *msg, uint32_t flags);

int semop(int fd, uint32_t *msg, uint32_t flags);

int semget(int semid, uint32_t *tsops, unsigned nsops);

int semctl(uint32_t key, int nsems, int semflg);

int msgsnd(int semnum, int cmd, uint32_t arg);

int msgrcv(int msqid, uint32_t *msgp, uint32_t msgsz, int msgflg);

int msgget(int msqid, uint32_t *msgp, uint32_t msgsz, long msgtyp, int msgflg);

int msgctl(uint32_t key, int msgflg);

int shmat(int msqid, int cmd, uint32_t *buf);

int shmdt(int shmid, char *shmaddr, int shmflg);

int shmget(char *shmaddr);

int shmctl(uint32_t key, uint32_t size, int shmflg);

int add_key(int shmid, int cmd, uint32_t *buf);

int request_key(const char *_type, const char *_description, const void *_payload, uint32_t plen, uint32_t ringid);

int keyctl(const char *_type, const char *_description, const char *_callout_info, uint32_t destringid);

int semtimedop(int option, unsigned long arg2, unsigned long arg3, unsigned long arg4, unsigned long arg5);

int ioprio_set(int which, int who, int ioprio);

int ioprio_get(int which, int who);

int inotify_init(int which, int who, int ioprio);

int inotify_add_watch(int which, int who);

int inotify_rm_watch();

int mbind(unsigned long start, unsigned long len, unsigned long mode, unsigned long *nmask, unsigned long maxnode,
          unsigned flags);

int get_mempolicy(int fd, const char *pathname, uint32_t mask);

int set_mempolicy(int fd, int32_t wd);

int openat(int *policy, unsigned long *nmask, unsigned long maxnode, unsigned long addr, unsigned long flags);

int mkdirat(int mode, unsigned long *nmask, unsigned long maxnode);

int mknodat(int dfd, const char *filename, int flags, uint32_t mode);

int fchownat(int dfd, const char *pathname, uint32_t mode);

int futimesat(int dfd, const char *filename, uint32_t mode, unsigned dev);

int fstatat64(int dfd, const char *filename, uint32_t user, uint32_t group, int flag);

int unlinkat(int dfd, const char *filename, uint32_t *utimes);

int renameat(int dfd, const char *filename, uint32_t *statbuf, int flag);

int linkat(int dfd, const char *pathname, int flag);

int symlinkat(int olddfd, const char *oldname, int newdfd, const char *newname);

int readlinkat(int olddfd, const char *oldname, int newdfd, const char *newname, int flags);

int fchmodat(const char *oldname, int newdfd, const char *newname);

int faccessat(int dfd, const char *pathname, char *buf, int bufsiz);

int pselect6(int n, uint32_t *inp, uint32_t *outp, uint32_t *exp, uint32_t *tsp, void *sig);

int ppoll(int dfd, const char *filename, uint32_t mode);

int unshare(int dfd, const char *filename, int mode);

int set_robust_list(uint32_t *ufds, uint32_t nfds, uint32_t *tsp, const uint32_t *sigmask,
                    uint32_t sigsetsize);

int get_robust_list(unsigned long unshare_flags);

int splice(int fd_in, uint32_t *off_in, int fd_out, uint32_t *off_out, uint32_t len, uint32_t flags);

int sync_file_range2(uint32_t *head, uint32_t len);

int tee(int pid, uint32_t **head_ptr, uint32_t *len_ptr);

int vmsplice(uint32_t flags, uint32_t offset, uint32_t nbytes);

int move_pages(uint32_t pid, unsigned long nr_pages, const void **pages,
               const int *nodes, int *status, int flags);

int getcpu(int fdin, int fdout, uint32_t len, uint32_t flags);

int epoll_pwait(int epfd, uint32_t *events, int maxevents, int timeout, const uint32_t *sigmask,
                int sigsetsize);

int kexec_load(int fd, const uint32_t *iov, unsigned long nr_segs, uint32_t flags);

int utimensat(unsigned *cpup, unsigned *nodep, uint32_t *unused);

int signalfd(unsigned long entry, unsigned long nr_segments,
             uint32_t *segments, unsigned long flags);

int timerfd_create(int clockid, int flags);

int eventfd(uint32_t count);

int fallocate(int dfd, const char *filename, uint32_t *utimes, int flags);

int timeruint32_ttime(int ufd, uint32_t *user_mask, uint32_t sizemask);

int timerfd_gettime(int mode, uint32_t offset, uint32_t len);

int signalfd4(int ufd, int flags, const uint32_t *utmr, uint32_t *otmr);

int eventfd2(int ufd, uint32_t *otmr);

int epoll_create1(int flags);

int dup3(uint32_t oldfd, uint32_t newfd, int flags);

int pipe2(int *fildes, int flags);

int inotify_init1(int flags);

int preadv(unsigned long fd, const uint32_t *vec, unsigned long vlen, unsigned long pos_l, unsigned long pos_h);

int pwritev(unsigned long fd, const uint32_t *vec, unsigned long vlen, unsigned long pos_l, unsigned long pos_h);

int rt_tgsigqueueinfo(uint32_t tgid, uint32_t pid, int sig, uint32_t *uinfo);

int perf_event_open(uint32_t *attr_uptr, uint32_t pid, int cpu, int group_fd, unsigned long flags);

int recvmmsg(int fd, uint32_t *mmsg, uint32_t vlen, uint32_t flags, uint32_t *timeout);

int accept4(int fd, uint32_t *upeer_sockaddr, int *upeer_addrlen, int flags);

int fanotify_init(uint32_t flags, uint32_t event_f_flags);

int fanotify_mark(uint32_t flags, uint64_t mask, int dfd, const char *pathname);

int prlimit64(uint32_t pid, uint32_t resource, const uint32_t *new_rlim, uint32_t *old_rlim);

int name_to_handle_at(int dfd, const char *name, uint32_t *handle, int *mnt_id, int flag);

int open_by_handle_at(int mountdirfd, uint32_t *handle, int flags);

int clock_adjtime(const uint32_t which_clock, uint32_t *utx);

int syncfs(int fd);

int sendmmsg(int fd, uint32_t *mmsg, uint32_t vlen, uint32_t flags);

int setns(int fd, int nstype);

int process_vm_readv(uint32_t pid, const uint32_t *lvec, unsigned long liovcnt, const uint32_t *rvec, unsigned long riovcnt,
                     unsigned long flags);

int process_vm_writev(uint32_t pid, const uint32_t *lvec, unsigned long liovcnt, const uint32_t *rvec,
                      unsigned long riovcnt, unsigned long flags);


#endif// __LIBRARY_LIBC_H__
