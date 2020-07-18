//
// Created by XingfengYang on 2020/7/17.
//
#include <atomic.h>

void atomic_create(Atomic *atomic) { atomic_set(atomic, 0); }

/**
 * Because reading and writing directly to the memory address does not go through the register,
 * it is also atomic to directly manipulate the memory address.
 * So you can also use (((atoimc)->counter) = (i))
 */
void atomic_set(Atomic *atomic, uint32_t val) {
  volatile uint32_t tmp;
  __asm__ __volatile__("@ atomic_set\n\t"
                       "1:  ldrex    %0, [%1]\n\t"
                       "    strex    %0, %2, [%1]\n\t"
                       "    teq      %0, #0\n\t"
                       "    bne      1b"
                       : "=&r"(tmp)
                       : "r"(&atomic->counter), "r"(val)
                       : "cc");
}

/**
 * Because reading and writing directly to the memory address does not go through the register,
 * it is also atomic to directly manipulate the memory address.
 * So you can also use (*(volatile int *)&(atomic)->counter)
 */
uint32_t atomic_get(Atomic *atomic) {
  volatile uint32_t result;
  __asm__ __volatile__("@ atomic_get\n\t"
                       "	ldrex	%0, [%1]"
                       : "=&r"(result)
                       : "r"(&atomic->counter));
  return result;
}