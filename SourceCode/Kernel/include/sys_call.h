//
// Created by XingfengYang on 2020/7/13.
//
#ifndef __KERNEL_SYSCALL_H__
#define __KERNEL_SYSCALL_H__

#define asmlinkage __attribute__((regparm(0)))

#define SYSCALL_DEFINE0(name) asmlinkage long sys_##name##(void)

// SYSCALL_DEFINE0(get_pid){
//         return 0;
// }
#endif // __KERNEL_SYSCALL_H__
