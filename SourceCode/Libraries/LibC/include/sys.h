//
// Created by XingfengYang on 2020/7/27.
//
#ifndef __LIBRARY_LIBC_SYS_H__
#define __LIBRARY_LIBC_SYS_H__

#define asmlinkage __attribute__((regparm(0)))

#define _syscall5(type,name,type1,name1,type2,name2,type3,name3,type4,name4,type5,name5)  \
type name(type1 name1, type2 name2, type3 name3, type4 name4,type5 name5){     \
 __asm__ __volatile__("push {lr}\n\t"    \
                       "mov r0, #0\n\t"     \
                       "mov r1, %1\n\t"     \
                       "mov r2, %2\n\t"     \
                       "mov r3, #0\n\t"     \
                       "mov r4, %3\n\t"     \
                       "mov r5, %4\n\t"     \
                       "mov r6, %5\n\t"     \
                       "mov r7, %0\n\t"     \
                       "swi 0x0\n\t"        \
                       "pop {lr}\n\t"       \
                       :                    \
                       :"r"(__SYSCALL_##name),"r"(name1),"r"(name2),"r"(name3),"r"(name4),"r"(name5)  \
                       :"r0","r1","r2","r3","r4","r7"); \
}

#define _syscall4(type,name,type1,name1,type2,name2,type3,name3,type4,name4)  \
   _syscall5(type,name,type1,name1,type2,name2,type3,name3,type4,name4,int,arg5)

#define _syscall3(type,name,type1,name1,type2,name2,type3,name3)  \
    _syscall4(type,name,type1,name1,type2,name2,type3,name3,int,arg4)

#define _syscall2(type,name,type1,name1,type2,name2)  \
   _syscall3(type,name,type1,name1,type2,name2,int,arg3)

#define _syscall1(type,name,type1,name1)  \
    _syscall2(type,name,type1,name1,int,arg2)

#define _syscall0(type,name)  \
    _syscall1(type,name,int,arg1)



#define __SYSCALL_setup 0
#define __SYSCALL_exit 1
#define __SYSCALL_fork 2
#define __SYSCALL_read 3
#define __SYSCALL_write 4

_syscall0(int,setup)
_syscall0(int,exit)
_syscall0(int,fork)
_syscall0(int,read)
_syscall0(int,write)

#define __SYSCALL_test1 5
_syscall1(int,test1,int,arg1)

#define __SYSCALL_test2 6
_syscall2(int,test2,int,arg1,int,arg2)

#define __SYSCALL_test3 7
_syscall3(int,test3,int,arg1,int,arg2,int,arg3)

#define __SYSCALL_test4 8
_syscall4(int,test4,int,arg1,int,arg2,int,arg3,int,arg4)

#define __SYSCALL_test5 9
_syscall5(int,test5,int,arg1,int,arg2,int,arg3,int,arg4,int,arg5)

#endif // __LIBRARY_LIBC_SYS_H__
