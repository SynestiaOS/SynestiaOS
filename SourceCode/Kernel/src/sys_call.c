//
// Created by XingfengYang on 2020/7/13.
//

#include <sys_call.h>


void swi(uint32_t num) {
  __asm__ __volatile__("push {lr}\n\t"
                       "mov r0, %0\n\t"
                       "swi 0x0\n\t"
                       "pop {pc}\n\t" ::"r"(num));
}