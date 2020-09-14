.section ".text.boot"


///////////////////////////////////////////////////////////////////
/**
 * macro, used to debug print, like printf("msg %d", 123)
 */
.macro __macro_debug_print1 message, parameter1
    ldr  x0, =\message
    mov  x1, \parameter1
    //bl   printf_
.endm

/**
 * macro, used to get current cpu core id
 */
.macro __macro_get_current_core
    mrs  x0, mpidr_el1 /* Multiprocessor Affinity Register */
    and  x0, x0, #0xFFFF /* get processor id */
.endm

/**
 * mocro, use to get current exception level
 */
.macro __macro_get_current_el
    mrs x0, CurrentEL
    lsr x0, x0, #2
.endm

/**
 * macro, used to print current exception level
 */
.macro __macro_print_current_el
    __macro_get_current_el
    mov  x1, x0
    __macro_debug_print1 __message_current_el, x1
.endm
///////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////
.globl _start
_start:
    __macro_get_current_core
    cbz  x0, _init_core0 /* hang for all non-primary cpu core */
    b    _hang_core

_hang_core:
    wfi /* wait for interrupt */
    b    _hang_core

_init_core0:
    /* TODO: (which value should sp be) */
    ldr  x0, =0x80000
    mov  sp, x0

    /* TODO: check where we are now in el3 ot not. In this case, we assume we are in el3, because qemu raspi3 boot into el3 */
    /* try drop from el3 to el1 secure */
    __macro_print_current_el /* NOTE: before we can use bl instruction, sp must be set */

    /*=============================================================*/
    /*      Enable FP/SIMD at EL1                                  */
    /*=============================================================*/
    /* IMPORTANT, el1 FP/SIMD should be enabled, because we will use fp somewhere */
    mov x0, #(0b11 << 20) /* FPEN, bits [21:20] */
    msr cpacr_el1, x0 /* Architectural Feature Access Control Register, Enable FP/SIMD at EL1 */

    /*=============================================================*/
    /*      Initialize sctlr_el1                                   */
    /*=============================================================*/
    /* Bits 29,28,23,22,20,11 should be 1 (res1 on documentation) */
    #define __SCTLR_RESERVED (3 << 28) | (3 << 22) | (1 << 20) | (1 << 11)
    /* Endianness of data accesses at EL1, 0->little-endian, 1->big-endian */
    #define __SCTLR_EE_LITTLE_ENDIAN (0 << 25)
    /* Stage 1 instruction access Cacheability control, for accesses at EL0 and EL1. 0->disable I cache */
    #define __SCTLR_I_CACHE_DISABLED (0 << 12)
    /* Stage 1 Cacheability control, for data accesses. 0->disable D cache */
    #define __SCTLR_D_CACHE_DISABLED (0 << 2)
    /* MMU enable for EL1&0 stage 1 address translation. 0->disable MMU */
    #define __SCTLR_MMU_DISABLED (0 << 0)
    // todo: i,d cache enable; mmu enable
    #define __SCTLR_VALUE (__SCTLR_RESERVED | __SCTLR_EE_LITTLE_ENDIAN | __SCTLR_I_CACHE_DISABLED | __SCTLR_D_CACHE_DISABLED | __SCTLR_MMU_DISABLED)

    mov x0, xzr /* clear x0 */
    ldr x0, =__SCTLR_VALUE
    msr sctlr_el1, x0 /* System Control Register (EL1) */

    mrs x1, sctlr_el1
    ldr x0, =__message_sctlr_el1_value
    //bl printf_

    /*=============================================================*/
    /*      Initialize scr_el3                                     */
    /*=============================================================*/
    mrs x0, scr_el3
    orr x0, x0, #(1<<10)        /* Lower EL is 64bits */
    msr scr_el3, x0 /* Secure Configuration Register */

    /*=============================================================*/
    /*      Initialize spsr_el3                                    */
    /*=============================================================*/
    mov x0, xzr
    mov x0, #0b00101            /* AArch64 Exception level and selected Stack Pointer. 0b0101->EL1h */
    orr x0, x0, #(1 << 8)       /* Enable SError and External Abort. */
    orr x0, x0, #(1 << 7)       /* IRQ interrupt Process state mask. */
    orr x0, x0, #(1 << 6)       /* FIQ interrupt Process state mask. */
    msr spsr_el3, x0 /* Saved Program Status Register (EL3) */

    /*=============================================================*/
    /*      Initialize elr_el3                                     */
    /*=============================================================*/
    adr x0, _goto_kernel_main
    msr elr_el3, x0 /* Exception Link Register (EL3) */

    /* Returns from an exception. It restores the processor state based on SPSR_ELn and branches to ELR_ELn, where n is the current exception level */
    eret

_goto_kernel_main:
    /* TODO: which value shoule sp be */
    ldr  x0, =0x80000
    mov  sp, x0

    //bl   print_mem_stack
//    bl   bss_clean

    __macro_print_current_el
#ifndef ENV_KERNEL_UNIT_TESTS
    bl   kernel_main
#else
    bl   kernel_main_tests
#endif
    __macro_get_current_core
    mov  x1, x0
    ldr  x0, =__message_core_hung
    //bl   printf_
    b    _hang_core /* kernel_main should never come here */
///////////////////////////////////////////////////////////////////

// todo: tbd
kernel_main:
    b    _hang_core /* kernel_main should never come here */

///////////////////////////////////////////////////////////////////
__message_current_el:
    .asciz "[DEBUG] current el is: %d\n"

__message_core_hung:
    .asciz "[DEBUG] core %d hung\n"

__message_sctlr_el1_value:
    .asciz "[DEBUG] sctlr_el1 is: 0x%x\n"
///////////////////////////////////////////////////////////////////
