//
// Created by XingfengYang on 2020/7/13.
//

#ifndef __KERNEL_SYSCALL_H__
#define __KERNEL_SYSCALL_H__

#define SYSCALL_DEFINE0(name)   \
    asmlinkage long sys_##name##(void){ \
            \
    }       \


#endif // __KERNEL_SYSCALL_H__
