//
// Created by XingfengYang on 2020/7/17.
//
#include "kernel/sched.h"
#include "kernel/sys_call.h"
#include "kernel/vfs.h"

extern VFS *vfs;

uint32_t sys_restart_syscall() {}

uint32_t sys_exit(int error_code) {}

uint32_t sys_fork() {}

uint32_t sys_read(uint32_t fd, char *buf, uint32_t count) {
    return vfs->operations.read(vfs, fd, buf, 0, count);
}

uint32_t sys_write(uint32_t fd, const char *buf, uint32_t count) {
    return vfs->operations.write(vfs, fd, buf, 0, count);
}

uint32_t sys_open(const char *filename, int flags, uint32_t mode) { return vfs->operations.open(vfs, filename, mode); }

uint32_t sys_close(uint32_t fd) { return vfs->operations.close(vfs, fd); }

uint32_t sys_creat(const char *pathname, uint32_t mode) {}

uint32_t sys_link(const char *oldname, const char *newname) {}

uint32_t sys_unlink(const char *pathname) {}

uint32_t sys_execve(const char *filenamei, const char *argv, const char *envp) {
}

uint32_t sys_chdir(const char *filename) {}

uint32_t sys_time(uint32_t *tloc) {}

uint32_t sys_mknod(const char *filename, uint32_t mode, unsigned int dev) {}

uint32_t sys_chmod(const char *filename, uint32_t mode) {}

uint32_t sys_lchown(const char *filename, uint32_t user, uint32_t group) {}

uint32_t sys_lseek(uint32_t fd, uint32_t offset, uint32_t origin) {}

uint32_t sys_getpid() { return schd_getpid(); }

uint32_t sys_mount(char *dev_name, char *dir_name, char *type, unsigned long flags, void *data) {}

uint32_t sys_umount(char *name, int flags) {}

uint32_t sys_setuid(uint32_t uid) {}

uint32_t sys_getuid() {}

uint32_t sys_stime(uint32_t *tptr) {}

uint32_t sys_ptrace(long request, long pid, unsigned long addr, unsigned long data) {}

uint32_t sys_alarm(uint32_t seconds) {}

uint32_t sys_pause() {}

uint32_t sys_utime(char *filename, uint32_t *times) {}

uint32_t sys_access(const char *filename, int mode) {}

uint32_t sys_nice(int increment) {}

uint32_t sys_sync() {}

uint32_t sys_kill(uint32_t pid, int sig) {}

uint32_t sys_rename(const char *oldname, const char *newname) {}

uint32_t sys_mkdir(const char *pathname, uint32_t mode) {}

uint32_t sys_rmdir(const char *pathname) {}

uint32_t sys_dup(uint32_t fildes) {}

uint32_t sys_pipe(int *fildes) {}

uint32_t sys_times(uint32_t *tbuf) {}

uint32_t sys_brk(unsigned long brk) {}

uint32_t sys_setgid(uint32_t gid) {}

uint32_t sys_getgid() {}

uint32_t sys_geteuid() {}

uint32_t sys_getegid() {}

uint32_t sys_acct(const char *name) {}

uint32_t sys_umount2(char *name, int flags) {}

uint32_t sys_ioctl(uint32_t fd, uint32_t cmd, unsigned long arg) {}

uint32_t sys_fcntl(uint32_t fd, uint32_t cmd, unsigned long arg) {}

uint32_t sys_setpgid(uint32_t pid, uint32_t pgid) {}

uint32_t sys_umask(int mask) {}

uint32_t sys_chroot(const char *filename) {}

uint32_t sys_ustat(unsigned int dev, uint32_t *ubuf) {}

uint32_t sys_dup2(uint32_t oldfd, uint32_t newfd) {}

uint32_t sys_getppid() {}

uint32_t sys_getpgrp() {}

uint32_t sys_setsid() {}

uint32_t sys_sigaction(int sig, const uint32_t *act, uint32_t *oact) {}

uint32_t sys_setreuid(uint32_t ruid, uint32_t euid) {}

uint32_t sys_setregid(uint32_t rgid, uint32_t egid) {}

uint32_t sys_sigsuspend(int restart, unsigned long oldmask, uint32_t mask) {}

uint32_t sys_sigpending(uint32_t *set) {}

uint32_t sys_sethostname(char *name, int len) {}

uint32_t sys_setrlimit(uint32_t resource, uint32_t *rlim) {}

uint32_t sys_getrlimit(uint32_t resource, uint32_t *rlim) {}

uint32_t sys_getrusage(int who, uint32_t *ru) {}

uint32_t sys_gettimeofday(uint32_t *tv, uint32_t *tz) {}

uint32_t sys_settimeofday(uint32_t *tv, uint32_t *tz) {}

uint32_t sys_getgroups(int gidsetsize, uint32_t *grouplist) {}

uint32_t sys_setgroups(int gidsetsize, uint32_t *grouplist) {}

uint32_t sys_select(int n, uint32_t *inp, uint32_t *outp, uint32_t *exp, uint32_t *tvp) {}

uint32_t sys_symlink(const char *oldname, const char *newname) {}

uint32_t sys_readlink(const char *path, char *buf, int bufsiz) {}

uint32_t sys_uselib(const char *library) {}

uint32_t sys_swapon(const char *specialfile, int swap_flags) {}

uint32_t sys_reboot(int magic1, int magic2, uint32_t cmd, void *arg) {}

uint32_t sys_readdir(uint32_t fd, uint32_t *dirent, uint32_t count) {}

uint32_t sys_mmap(uint32_t *arg) {}

uint32_t sys_munmap(unsigned long addr, uint32_t len) {}

uint32_t sys_truncate(const char *path, long length) {}

uint32_t sys_ftruncate(uint32_t fd, unsigned long length) {}

uint32_t sys_fchmod(uint32_t fd, uint32_t mode) {}

uint32_t sys_fchown(uint32_t fd, uint32_t user) {}

uint32_t sys_getpriority(int which, int who) {}

uint32_t sys_setpriority(int which, int who, int niceval) {}

uint32_t sys_statfs(const char *pathname, uint32_t *buf) {}

uint32_t sys_fstatfs(uint32_t fd, uint32_t *buf) {}

uint32_t sys_socketcall(int call, unsigned long *args) {}

uint32_t sys_syslog(int type, char *buf, int len) {}

uint32_t sys_setitimer(int which, uint32_t *value, uint32_t *ovalue) {}

uint32_t sys_getitimer(int which, uint32_t *value) {}

uint32_t sys_stat(const char *filename, uint32_t *statbuf) {}

uint32_t sys_lstat(const char *filename, uint32_t *statbuf) {}

uint32_t sys_fstat(uint32_t fd, uint32_t *statbuf) {}

uint32_t sys_vhangup() {}

uint32_t sys_syscall() {}

uint32_t sys_wait4(uint32_t upid, int *stat_addr, int options, uint32_t *ru) {}

uint32_t sys_swapoff(const char *specialfile) {}

uint32_t sys_sysinfo(uint32_t *info) {}

uint32_t sys_ipc(uint32_t call, int first, unsigned long second, unsigned long third, void *ptr, long fifth) {}

uint32_t sys_fsync(uint32_t fd) {}

uint32_t sys_sigreturn() {}

uint32_t
sys_clone(unsigned long clone_flags, unsigned long newsp, int *parent_tidptr, int tls_val, int *child_tidptr) {}

uint32_t sys_setdomainname(char *name, int len) {}

uint32_t sys_uname(uint32_t *name) {}

uint32_t sys_adjtimex(uint32_t *txc_p) {}

uint32_t sys_mprotect(unsigned long start, uint32_t len, unsigned long prot) {}

uint32_t sys_sigprocmask(int how, uint32_t *nset, uint32_t *oset) {}

uint32_t sys_init_module(void *umod, unsigned long len, const char *uargs) {}

uint32_t sys_delete_module(const char *name_user, uint32_t flags) {}

uint32_t sys_quotactl(uint32_t cmd) {}

uint32_t sys_getpgid(uint32_t pid) {}

uint32_t sys_fchdir(uint32_t fd) {}

uint32_t sys_bdflush(int func, long data) {}

uint32_t sys_sysfs(int option, unsigned long arg1, unsigned long arg2) {}

uint32_t sys_personality(uint32_t personality) {}

uint32_t sys_setfsuid(uint32_t uid) {}

uint32_t sys_setfsgid(uint32_t gid) {}

uint32_t
sys__llseek(uint32_t fd, unsigned long offset_high, unsigned long offset_low, uint32_t *result, uint32_t origin) {}

uint32_t sys_getdents(uint32_t fd, uint32_t *dirent, uint32_t count) {}

uint32_t sys__newselect(int n, uint32_t *inp, uint32_t *outp, uint32_t *exp, uint32_t *tvp) {}

uint32_t sys_flock(uint32_t fd, uint32_t cmd) {}

uint32_t sys_msync(unsigned long start, uint32_t len, int flags) {}

uint32_t sys_readv(unsigned long fd, const uint32_t *vec, unsigned long vlen) {}

uint32_t sys_writev(unsigned long fd, const uint32_t *vec, unsigned long vlen) {}

uint32_t sys_getsid(uint32_t pid) {}

uint32_t sys_fdatasync(uint32_t fd) {}

uint32_t sys__sysctl(uint32_t *args) {}

uint32_t sys_mlock(unsigned long start, uint32_t len) {}

uint32_t sys_munlock(unsigned long start, uint32_t len) {}

uint32_t sys_mlockall(int flags) {}

uint32_t sys_munlockall() {}

uint32_t sys_sched_setparam(uint32_t pid, uint32_t *param) {}

uint32_t sys_sched_getparam(uint32_t pid, uint32_t *param) {}

uint32_t sys_sched_setscheduler(uint32_t pid, int policy, uint32_t *param) {}

uint32_t sys_sched_getscheduler(uint32_t pid) {}

uint32_t sys_sched_yield() {}

uint32_t sys_sched_get_priority_max(int policy) {}

uint32_t sys_sched_get_priority_min(int policy) {}

uint32_t sys_sched_rr_get_interval(uint32_t pid, uint32_t *interval) {}

uint32_t sys_nanosleep(uint32_t *rqtp, uint32_t *rmtp) {}

uint32_t sys_mremap(unsigned long addr, unsigned long old_len, unsigned long new_len, unsigned long flags,
                    unsigned long new_addr) {}

uint32_t sys_setresuid(uint32_t ruid, uint32_t euid, uint32_t suid) {}

uint32_t sys_getresuid(uint32_t *ruidp, uint32_t *euidp, uint32_t *suidp) {}

uint32_t sys_poll(uint32_t *ufds, uint32_t nfds, int timeout_msecs) {}

uint32_t sys_nfsservctl() {}

uint32_t sys_setresgid(uint32_t rgid, uint32_t egid, uint32_t sgid32_t) {}

uint32_t sys_getresgid(uint32_t *rgidp, uint32_t *egidp, uint32_t *sgidp) {}

uint32_t sys_prctl(int option, unsigned long arg2, unsigned long arg3, unsigned long arg4, unsigned long arg5) {}

uint32_t sys_rt_sigreturn() {}

uint32_t sys_rt_sigaction(int sig, const uint32_t *act, uint32_t *oact, uint32_t sigsetsize) {}

uint32_t sys_rt_sigprocmask(int how, uint32_t *nset, uint32_t *oset, uint32_t sigsetsize) {}

uint32_t sys_rt_sigpending(uint32_t *set, uint32_t sigsetsize) {}

uint32_t sys_rt_sigtimedwait(const uint32_t *uthese, uint32_t *uinfo, const uint32_t *uts,
                             uint32_t sigsetsize) {}

uint32_t sys_rt_sigqueueinfo(uint32_t pid, int sig, uint32_t *uinfo) {}

uint32_t sys_rt_sigsuspend(uint32_t *unewset, uint32_t sigsetsize) {}

uint32_t sys_pread64(char *buf, uint32_t count, uint32_t pos) {}

uint32_t sys_pwrite64(const char *buf, uint32_t count, uint32_t pos) {}

uint32_t sys_chown(const char *filename, uint32_t user, uint32_t group) {}

uint32_t sys_getcwd(char *buf, unsigned long size) {}

uint32_t sys_capget(uint32_t header, uint32_t dataptr) {}

uint32_t sys_capset(uint32_t header, const uint32_t data) {}

uint32_t sys_sigaltstack() {}

uint32_t sys_sendfile(int out_fd, int in_fd, uint32_t *offset, uint32_t count) {}

uint32_t sys_vfork() {}

uint32_t sys_ugetrlimit(uint32_t resource, uint32_t *rlim) {}

uint32_t sys_mmap2(unsigned long addr, unsigned long len, unsigned long prot, unsigned long flags, unsigned long fd,
                   unsigned long pgoff) {}

uint32_t sys_truncate64(uint32_t length) {}

uint32_t sys_ftruncate64(uint32_t length) {}

uint32_t sys_stat64(const char *filename, uint32_t *statbuf) {}

uint32_t sys_lstat64(const char *filename, uint32_t *statbuf) {}

uint32_t sys_fstat64(unsigned long fd, uint32_t *statbuf) {}

uint32_t sys_lchown32(const char *filename, uint32_t user, uint32_t group) {}

uint32_t sys_getuid32() {}

uint32_t sys_getgid32() {}

uint32_t sys_geteuid32() {}

uint32_t sys_getegid32() {}

uint32_t sys_setreuid32(uint32_t rui, uint32_t euid) {}

uint32_t sys_setregid32(uint32_t rgid, uint32_t egid) {}

uint32_t sys_getgroups32(int gidsetsize, uint32_t *grouplist) {}

uint32_t sys_setgroups32(int gidsetsize, uint32_t *grouplist) {}

uint32_t sys_fchown32(uint32_t fd, uint32_t user, uint32_t group) {}

uint32_t sys_setresuid32(uint32_t ruid, uint32_t euid, uint32_t suid) {}

uint32_t sys_getresuid32(uint32_t *ruidp, uint32_t *euidp, uint32_t *suidp) {}

uint32_t sys_setresgid32(uint32_t rgid, uint32_t egid, uint32_t sgid) {}

uint32_t sys_getresgid32(uint32_t *rgidp, uint32_t *egidp, uint32_t *sgidp) {}

uint32_t sys_chown32(const char *filename, uint32_t user, uint32_t group) {}

uint32_t sys_setuid32(uint32_t uid) {}

uint32_t sys_setgid32(uint32_t gid) {}

uint32_t sys_setfsuid32(uint32_t uid) {}

uint32_t sys_setfsgid32(uint32_t gid) {}

uint32_t sys_getdents64(uint32_t fd, uint32_t *dirent, uint32_t count) {}

uint32_t sys_pivot_root(const char *new_root, const char *put_old) {}

uint32_t sys_mincore(unsigned long start, uint32_t len, unsigned char *vec) {}

uint32_t sys_madvise(unsigned long start, uint32_t len_in, int behavior) {}

uint32_t sys_fcntl64(uint32_t fd, uint32_t cmd, unsigned long arg) {}

uint32_t sys_gettid() {}

uint32_t sys_readahead(uint32_t offset, uint32_t count) {}

uint32_t sys_setxattr(const char *pathname, const char *name, const void *value, uint32_t size, int flags) {}

uint32_t sys_lsetxattr(const char *pathname, const char *name, const void *value, uint32_t size, int flags) {}

uint32_t sys_fsetxattr(int fd, const char *name, const void *value, uint32_t size, int flags) {}

uint32_t sys_getxattr(const char *pathname, const char *name, void *value, uint32_t size) {}

uint32_t sys_lgetxattr(const char *pathname, const char *name, void *value, uint32_t size) {}

uint32_t sys_fgetxattr(int fd, const char *name, void *value, uint32_t size) {}

uint32_t sys_listxattr(const char *pathname, char *list, uint32_t size) {}

uint32_t sys_llistxattr(const char *pathname, char *list, uint32_t size) {}

uint32_t sys_flistxattr(int fd, char *list, uint32_t size) {}

uint32_t sys_removexattr(const char *pathname, const char *name) {}

uint32_t sys_lremovexattr(const char *pathname, const char *name) {}

uint32_t sys_fremovexattr(int fd, const char *name) {}

uint32_t sys_tkill(uint32_t pid, int sig) {}

uint32_t sys_sendfile64(int out_fd, int in_fd, uint32_t *offset, uint32_t count) {}

uint32_t sys_futex(uint32_t *uaddr, int op, uint32_t val, uint32_t *utime, uint32_t *uaddr2, uint32_t val3) {}

uint32_t sys_sched_setaffinity(uint32_t pid, uint32_t len, unsigned long *user_mask_ptr) {}

uint32_t sys_sched_getaffinity(uint32_t pid, uint32_t len, unsigned long *user_mask_ptr) {}

uint32_t sys_io_setup(unsigned int nr_events, uint32_t *ctxp) {}

uint32_t sys_io_destroy(uint32_t ctx) {}

uint32_t sys_io_getevents(uint32_t ctx_id, long min_nr, long nr, uint32_t *events, uint32_t *timeout) {}

uint32_t sys_io_submit(uint32_t ctx_id, long nr, uint32_t **iocbpp) {}

uint32_t sys_io_cancel(uint32_t ctx_id, uint32_t *iocb, uint32_t *result) {}

uint32_t sys_exit_group(int error_code) {}

uint32_t sys_lookup_dcookie(char *buf, uint32_t len) {}

uint32_t sys_epoll_create(int size) {}

uint32_t sys_epoll_ctl(int epfd, int op, int fd, uint32_t *event) {}

uint32_t sys_epoll_wait(int epfd, uint32_t *events, int maxevents, int timeout) {}

uint32_t sys_remap_file_pages(unsigned long start, unsigned long size, unsigned long prot, unsigned long pgoff,
                              unsigned long flags) {}

uint32_t sys_set_tid_address(int *tidptr) {}

uint32_t sys_timer_create(const uint32_t which_clock, uint32_t *timer_event_spec, uint32_t *created_timer_id) {}

uint32_t sys_timer_settime(uint32_t timer_id, int flags, const uint32_t *new_setting,
                           uint32_t *old_setting) {}

uint32_t sys_timer_gettime(uint32_t timer_id, uint32_t *setting) {}

uint32_t sys_timer_getoverrun(uint32_t timer_id) {}

uint32_t sys_timer_delete(uint32_t timer_id) {}

uint32_t sys_clock_settime(const uint32_t which_clock, const uint32_t *tp) {}

uint32_t sys_clock_gettime(const uint32_t which_clock, uint32_t *tp) {}

uint32_t sys_clock_getres(const uint32_t which_clock, uint32_t *tp) {}

uint32_t
sys_clock_nanosleep(const uint32_t which_clock, int flags, const uint32_t *rqtp, uint32_t *rmtp) {}

uint32_t sys_statfs64(const char *pathname, uint32_t sz, uint32_t *buf) {}

uint32_t sys_fstatfs64(uint32_t fd, uint32_t sz, uint32_t *buf) {}

uint32_t sys_tgkill(uint32_t tgid, uint32_t pid, int sig) {}

uint32_t sys_utimes(char *filename, uint32_t *utimes) {}

uint32_t sys_arm_fadvise64_64(int fd, int advice, uint32_t offset, uint32_t len) {}

uint32_t sys_pciconfig_read(unsigned long bus, unsigned long dfn, unsigned long off, unsigned long len, void *buf) {}

uint32_t sys_pciconfig_write(long bus, unsigned long dfn, unsigned long off, unsigned long len, void *buf) {}

uint32_t sys_mq_open(unsigned long bus, unsigned long dfn, unsigned long off, unsigned long len, void *buf) {}

uint32_t sys_mq_unlink(const char *u_name, int oflag, uint32_t mode, uint32_t *u_attr) {}

uint32_t sys_mq_timedsend(const char *u_name) {}

uint32_t sys_mq_timedreceive(uint32_t mqdes, const char *u_msg_ptr, uint32_t msg_len, uint32_t msg_prio,
                             const uint32_t *u_abs_timeout) {}

uint32_t sys_mq_notify(uint32_t mqdes, char *u_msg_ptr, uint32_t msg_len, uint32_t *u_msg_prio,
                       const uint32_t *u_abs_timeout) {}

uint32_t sys_mq_getsetattr(uint32_t mqdes, const uint32_t *u_notification) {}

uint32_t sys_waitid(uint32_t mqdes, const uint32_t *u_mqstat, uint32_t *u_omqstat) {}

uint32_t sys_socket(int which, uint32_t upid, uint32_t *infop, int options, uint32_t *ru) {}

uint32_t sys_bind(int family, int type, int protocol) {}

uint32_t sys_connect(int fd, uint32_t *umyaddr, int addrlen) {}

uint32_t sys_listen(int fd, uint32_t *uservaddr, int addrlen) {}

uint32_t sys_accept(int fd, int backlog) {}

uint32_t sys_getsockname(int fd, uint32_t *upeer_sockaddr, int *upeer_addrlen) {}

uint32_t sys_getpeername(int fd, uint32_t *usockaddr, int *usockaddr_len) {}

uint32_t sys_socketpair(int fd, uint32_t *usockaddr, int *usockaddr_len) {}

uint32_t sys_send(int family, int type, int protocol, int *usockvec) {}

uint32_t sys_sendto(int fd, void *buff, uint32_t len, uint32_t flags, uint32_t *addr, int addr_len) {}

uint32_t sys_recv(int fd, void *buff, uint32_t len, uint32_t flags) {}

uint32_t sys_recvfrom(int fd, void *ubuf, uint32_t size, uint32_t flags, uint32_t *addr, int *addr_len) {}

uint32_t sys_shutdown(int fd, void *ubuf, uint32_t size, uint32_t flags) {}

uint32_t sys_setsockopt(int fd, int how) {}

uint32_t sys_getsockopt(int fd, int level, int optname, char *optval, int optlen) {}

uint32_t sys_sendmsg(int fd, int level, int optname, char *optval, int *optlen) {}

uint32_t sys_recvmsg(int fd, uint32_t *msg, uint32_t flags) {}

uint32_t sys_semop(int fd, uint32_t *msg, uint32_t flags) {}

uint32_t sys_semget(int semid, uint32_t *tsops, unsigned nsops) {}

uint32_t sys_semctl(uint32_t key, int nsems, int semflg) {}

uint32_t sys_msgsnd(int semnum, int cmd, uint32_t arg) {}

uint32_t sys_msgrcv(int msqid, uint32_t *msgp, uint32_t msgsz, int msgflg) {}

uint32_t sys_msgget(int msqid, uint32_t *msgp, uint32_t msgsz, long msgtyp, int msgflg) {}

uint32_t sys_msgctl(uint32_t key, int msgflg) {}

uint32_t sys_shmat(int msqid, int cmd, uint32_t *buf) {}

uint32_t sys_shmdt(int shmid, char *shmaddr, int shmflg) {}

uint32_t sys_shmget(char *shmaddr) {}

uint32_t sys_shmctl(uint32_t key, uint32_t size, int shmflg) {}

uint32_t sys_add_key(int shmid, int cmd, uint32_t *buf) {}

uint32_t sys_request_key(const char *_type, const char *_description, const void *_payload, uint32_t plen,
                         uint32_t ringid) {}

uint32_t sys_keyctl(const char *_type, const char *_description, const char *_callout_info, uint32_t destringid) {}

uint32_t sys_semtimedop(int option, unsigned long arg2, unsigned long arg3, unsigned long arg4, unsigned long arg5) {}


uint32_t sys_ioprio_set(int which, int who, int ioprio) {}

uint32_t sys_ioprio_get(int which, int who) {}

uint32_t sys_inotify_init(int which, int who, int ioprio) {}

uint32_t sys_inotify_add_watch(int which, int who) {}

uint32_t sys_inotify_rm_watch() {}

uint32_t
sys_mbind(unsigned long start, unsigned long len, unsigned long mode, unsigned long *nmask, unsigned long maxnode,
          unsigned flags) {}

uint32_t sys_get_mempolicy(int fd, const char *pathname, uint32_t mask) {}

uint32_t sys_set_mempolicy(int fd, int32_t wd) {}

uint32_t
sys_openat(int *policy, unsigned long *nmask, unsigned long maxnode, unsigned long addr, unsigned long flags) {}

uint32_t sys_mkdirat(int mode, unsigned long *nmask, unsigned long maxnode) {}

uint32_t sys_mknodat(int dfd, const char *filename, int flags, uint32_t mode) {}

uint32_t sys_fchownat(int dfd, const char *pathname, uint32_t mode) {}

uint32_t sys_futimesat(int dfd, const char *filename, uint32_t mode, unsigned dev) {}

uint32_t sys_fstatat64(int dfd, const char *filename, uint32_t user, uint32_t group, int flag) {}

uint32_t sys_unlinkat(int dfd, const char *filename, uint32_t *utimes) {}

uint32_t sys_renameat(int dfd, const char *filename, uint32_t *statbuf, int flag) {}

uint32_t sys_linkat(int dfd, const char *pathname, int flag) {}

uint32_t sys_symlinkat(int olddfd, const char *oldname, int newdfd, const char *newname) {}

uint32_t sys_readlinkat(int olddfd, const char *oldname, int newdfd, const char *newname, int flags) {}

uint32_t sys_fchmodat(const char *oldname, int newdfd, const char *newname) {}

uint32_t sys_faccessat(int dfd, const char *pathname, char *buf, int bufsiz) {}

uint32_t sys_pselect6(int n, uint32_t *inp, uint32_t *outp, uint32_t *exp, uint32_t *tsp, void *sig) {}

uint32_t sys_ppoll(int dfd, const char *filename, uint32_t mode) {}

uint32_t sys_unshare(int dfd, const char *filename, int mode) {}

uint32_t sys_set_robust_list(uint32_t *ufds, uint32_t nfds, uint32_t *tsp, const uint32_t *sigmask,
                             uint32_t sigsetsize) {}

uint32_t sys_get_robust_list(unsigned long unshare_flags) {}

uint32_t sys_splice(int fd_in, uint32_t *off_in, int fd_out, uint32_t *off_out, uint32_t len, uint32_t flags) {}

uint32_t sys_sync_file_range2(uint32_t *head, uint32_t len) {}

uint32_t sys_tee(int pid, uint32_t **head_ptr, uint32_t *len_ptr) {}

uint32_t sys_vmsplice(uint32_t flags, uint32_t offset, uint32_t nbytes) {}

uint32_t
sys_move_pages(uint32_t pid, unsigned long nr_pages, const void **pages, const int *nodes, int *status, int flags) {}

uint32_t sys_getcpu(int fdin, int fdout, uint32_t len, uint32_t flags) {}

uint32_t sys_epoll_pwait(int epfd, uint32_t *events, int maxevents, int timeout, const uint32_t *sigmask,
                         uint32_t sigsetsize) {}

uint32_t sys_kexec_load(int fd, const uint32_t *iov, unsigned long nr_segs, uint32_t flags) {}

uint32_t sys_utimensat(unsigned *cpup, unsigned *nodep, uint32_t *unused) {}

uint32_t
sys_signalfd(unsigned long entry, unsigned long nr_segments, uint32_t *segments, unsigned long flags) {}

uint32_t sys_timerfd_create(int clockid, int flags) {}

uint32_t sys_eventfd(uint32_t count) {}

uint32_t sys_fallocate(int dfd, const char *filename, uint32_t *utimes, int flags) {}

uint32_t sys_timeruint32_ttime(int ufd, uint32_t *user_mask, uint32_t sizemask) {}

uint32_t sys_timerfd_gettime(int mode, uint32_t offset, uint32_t len) {}

uint32_t sys_signalfd4(int ufd, int flags, const uint32_t *utmr, uint32_t *otmr) {}

uint32_t sys_eventfd2(int ufd, uint32_t *otmr) {}

uint32_t sys_epoll_create1(int flags) {}

uint32_t sys_dup3(uint32_t oldfd, uint32_t newfd, int flags) {}

uint32_t sys_pipe2(int *fildes, int flags) {}

uint32_t sys_inotify_init1(int flags) {}

uint32_t
sys_preadv(unsigned long fd, const uint32_t *vec, unsigned long vlen, unsigned long pos_l, unsigned long pos_h) {}

uint32_t
sys_pwritev(unsigned long fd, const uint32_t *vec, unsigned long vlen, unsigned long pos_l, unsigned long pos_h) {}

uint32_t sys_rt_tgsigqueueinfo(uint32_t tgid, uint32_t pid, int sig, uint32_t *uinfo) {}

uint32_t
sys_perf_event_open(uint32_t *attr_uptr, uint32_t pid, int cpu, int group_fd, unsigned long flags) {}

uint32_t sys_recvmmsg(int fd, uint32_t *mmsg, uint32_t vlen, uint32_t flags, uint32_t *timeout) {}

uint32_t sys_accept4(int fd, uint32_t *upeer_sockaddr, int *upeer_addrlen, int flags) {}

uint32_t sys_fanotify_init(uint32_t flags, uint32_t event_f_flags) {}

uint32_t sys_fanotify_mark(uint32_t flags, uint64_t mask, int dfd, const char *pathname) {}

uint32_t sys_prlimit64(uint32_t pid, uint32_t resource, const uint32_t *new_rlim, uint32_t *old_rlim) {}

uint32_t sys_name_to_handle_at(int dfd, const char *name, uint32_t *handle, int *mnt_id, int flag) {}

uint32_t sys_open_by_handle_at(int mountdirfd, uint32_t *handle, int flags) {}

uint32_t sys_clock_adjtime(const uint32_t which_clock, uint32_t *utx) {}

uint32_t sys_syncfs(int fd) {}

uint32_t sys_sendmmsg(int fd, uint32_t *mmsg, uint32_t vlen, uint32_t flags) {}

uint32_t sys_setns(int fd, int nstype) {}

uint32_t sys_process_vm_readv(uint32_t pid, const uint32_t *lvec, unsigned long liovcnt, const uint32_t *rvec,
                              unsigned long riovcnt, unsigned long flags) {}

uint32_t sys_process_vm_writev(uint32_t pid, const uint32_t *lvec, unsigned long liovcnt, const uint32_t *rvec,
                               unsigned long riovcnt, unsigned long flags) {}
