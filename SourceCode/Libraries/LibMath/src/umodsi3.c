//
// Created by Shifu Wu  on 2021/1/24.
//

#if ARCH_arm

typedef union { unsigned int i; float f; } fu;
unsigned int __umodsi3 (unsigned int a, unsigned int b);
unsigned int
__umodsi3 (unsigned int a, unsigned int b)
{
    unsigned int d, t, s0, s1, s2, r0, r1;
    fu u0, u1, u2,  u1b, u2b;
    if (b > a)
        return a;
    /* Compute difference in number of bits in S0.  */
    u0.i = 0x40000000;
    u1b.i = u2b.i = u0.i;
    u1.i = a;
    u2.i = b;
    u1.i = a | u0.i;
    t = 0x4b800000 | ((a >> 23) & 0xffff);
    if (a >> 23)
    {
        u1.i = t;
        u1b.i = 0x4b800000;
    }
    u2.i = b | u0.i;
    t = 0x4b800000 | ((b >> 23) & 0xffff);
    if (b >> 23)
    {
        u2.i = t;
        u2b.i = 0x4b800000;
    }
    u1.f = u1.f - u1b.f;
    u2.f = u2.f - u2b.f;
    s1 = u1.i >> 23;
    s2 = u2.i >> 23;
    s0 = s1 - s2;
#define STEP(n) case n: d = b << n; t = a - d; if (t <= a) a = t;
    switch (s0)
    {
        STEP (31)
        STEP (30)
        STEP (29)
        STEP (28)
        STEP (27)
        STEP (26)
        STEP (25)
        STEP (24)
        STEP (23)
        STEP (22)
        STEP (21)
        STEP (20)
        STEP (19)
        STEP (18)
        STEP (17)
        STEP (16)
        STEP (15)
        STEP (14)
        STEP (13)
        STEP (12)
        STEP (11)
        STEP (10)
        STEP (9)
        STEP (8)
        STEP (7)
        STEP (6)
        STEP (5)
        STEP (4)
        STEP (3)
        STEP (2)
        STEP (1)
        STEP (0)
    }
    return a;
}

#endif
