//
// Created by XingfengYang on 2020/7/17.
//
#include <atomic.h>

void atomic_create(Atomic *atomic) { atomic_set(atomic, 0); }

void atomic_set(Atomic *atomic, uint32_t val) {
  uint32_t tmp;
  __asm__ __volatile__("@ atomic_set/n"
                       "1:  ldrex    %0, [%1]/n"
                       "    strex    %0, %2, [%1]/n"
                       "    teq      %0, #0/n"
                       "    bne      1b"
                       : "=&r"(tmp)
                       : "r"(&atomic->counter), "r"(val)
                       : "cc");
}

uint32_t atomic_get(Atomic *atomic) {
  uint32_t result;
  __asm__ __volatile__("@ atomic_get\n"
                       "	ldrex	%0, [%1]"
                       : "=&r"(result)
                       : "r"(&atomic->counter));
  return result;
}