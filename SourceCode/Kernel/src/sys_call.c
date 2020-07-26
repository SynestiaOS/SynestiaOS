//
// Created by XingfengYang on 2020/7/13.
//

#include <log.h>
#include <sys_call.h>

int sys_setup(void) {
  LogWarnning("[SysCall] syscall setup invoked.\n");
  return 0;
}

int sys_exit(void) {
  LogWarnning("[SysCall] syscall exit invoked.\n");
  return 0;
}

int sys_fork(void) {
  LogWarnning("[SysCall] syscall fork invoked.\n");
  return 0;
}

int sys_read(void) {
  LogWarnning("[SysCall] syscall read invoked.\n");
  return 0;
}

int sys_write(void) {
  LogWarnning("[SysCall] syscall write invoked.\n");
  return 0;
}

int sys_test1(int arg1){
  LogWarnning("[SysCall] syscall test1 invoked. arg1: %d \n",arg1);
  return 0;
}

int sys_test2(int arg1,int arg2){
  LogWarnning("[SysCall] syscall test2 invoked. arg1: %d \n",arg1);
  LogWarnning("[SysCall] syscall test2 invoked. arg2: %d \n",arg2);
  return 0;
}

int sys_test3(int arg1,int arg2,int arg3){
  LogWarnning("[SysCall] syscall test3 invoked. arg1: %d \n",arg1);
  LogWarnning("[SysCall] syscall test3 invoked. arg2: %d \n",arg2);
  LogWarnning("[SysCall] syscall test3 invoked. arg3: %d \n",arg3);
  return 0;
}

int sys_test4(int arg1,int arg2,int arg3,int arg4){
  LogWarnning("[SysCall] syscall test4 invoked. arg1: %d \n",arg1);
  LogWarnning("[SysCall] syscall test4 invoked. arg2: %d \n",arg2);
  LogWarnning("[SysCall] syscall test4 invoked. arg3: %d \n",arg3);
  LogWarnning("[SysCall] syscall test4 invoked. arg4: %d \n",arg4);
  return 0;
}

int sys_test5(int arg1,int arg2,int arg3,int arg4,int arg5){
  LogWarnning("[SysCall] syscall test5 invoked. arg1: %d \n",arg1);
  LogWarnning("[SysCall] syscall test5 invoked. arg2: %d \n",arg2);
  LogWarnning("[SysCall] syscall test5 invoked. arg3: %d \n",arg3);
  LogWarnning("[SysCall] syscall test5 invoked. arg4: %d \n",arg4);
  LogWarnning("[SysCall] syscall test5 invoked. arg5: %d \n",arg5);
  return 0;
}

void swi(uint32_t num) {
  __asm__ __volatile__("push {lr}\n\t"
                       "mov r0, %0\n\t"
                       "swi 0x0\n\t"
                       "pop {pc}\n\t" ::"r"(num));
}