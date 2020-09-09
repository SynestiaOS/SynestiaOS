//
// Created by XingfengYang on 2020/7/17.
//
#include <atomic.h>

void atomic_create(Atomic* atomic) { atomic_set(atomic, 0); }

/**
 * Because reading and writing directly to the memory address does not go through the register,
 * it is also atomic to directly manipulate the memory address.
 * So you can also use (((atoimc)->counter) = (i))
 */
void atomic_set(Atomic* atomic, uint32_t val)
{
    volatile uint32_t tmp;
    __asm__ __volatile__("@ atomic_set\n\t"
                         "1:  ldrex    %0, [%1]\n\t" // ldrex : arm的
                         "    strex    %0, %2, [%1]\n\t" // strex
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
uint32_t atomic_get(Atomic* atomic)
{
    volatile uint32_t result;
    __asm__ __volatile__("@ atomic_get\n\t"
                         "	ldrex	%0, [%1]"
                         : "=&r"(result)
                         : "r"(&atomic->counter));
    return result;
}

uint32_t atomic_inc(Atomic* atomic) { return atomic_add(atomic, 1); }

uint32_t atomic_dec(Atomic* atomic) { return atomic_sub(atomic, 1); }

uint32_t atomic_add(Atomic* atomic, uint32_t val)
{
    volatile uint32_t tmp;
    uint32_t result;
    __asm__ __volatile__("@ atomic_add\n\t"
                         "1:  ldrex    %0, [%2]\n\t"
                         "    add      %1, %0, %3\n\t"
                         "    strex    %0, %1, [%2]\n\t"
                         "    teq      %0, #0\n\t"
                         "    bne      1b"
                         : "=&r"(tmp), "=&r"(result)
                         : "r"(&atomic->counter), "r"(val)
                         : "cc");
    return result;
}

uint32_t atomic_sub(Atomic* atomic, uint32_t val)
{
    volatile uint32_t tmp;
    uint32_t result;
    __asm__ __volatile__("@ atomic_sub\n\t"
                         "1:  ldrex    %0, [%2]\n\t"
                         "    sub      %1, %0, %3\n\t"
                         "    strex    %0, %1, [%2]\n\t"
                         "    teq      %0, #0\n\t"
                         "    bne      1b"
                         : "=&r"(tmp), "=&r"(result)
                         : "r"(&atomic->counter), "r"(val)
                         : "cc");
    return result;
}