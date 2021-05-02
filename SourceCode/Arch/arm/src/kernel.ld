ENTRY(__text_start)

SECTIONS
{
    . = 0x8000;
    __text_start = .;
    .text :
    {
        __vector_table_start = .;
        KEEP(*(.interrupt_vector_table))
        __vector_table_end = .;
        KEEP(*(.text.boot))
        __module_init_start = .;
        __module_init_lv0_start = .;
        KEEP(*(.module_lv0.init))
        __module_init_lv0_end = .;
        __module_init_lv1_start = .;
        KEEP(*(.module_lv1.init))
        __module_init_lv1_end = .;
        __module_init_lv2_start = .;
        KEEP(*(.module_lv2.init))
        __module_init_lv2_end = .;
        __module_init_lv3_start = .;
        KEEP(*(.module_lv3.init))
        __module_init_lv3_end = .;
        __module_init_lv4_start = .;
        KEEP(*(.module_lv4.init))
        __module_init_lv4_end = .;
        __module_init_lv5_start = .;
        KEEP(*(.module_lv5.init))
        __module_init_lv5_end = .;
        __module_init_end  = .;
        *(.text)
    }
    . = ALIGN(4096);
    __text_end = .;

    __rodata_start = .;
    .rodata :
    {
        *(.rodata)
    }
    . = ALIGN(4096);
    __rodata_end = .;

    __data_start = .;
    .data :
    {
        *(.data)
    }
    . = ALIGN(4096);
    __data_end = .;

    __bss_start = .;
    .bss :
    {
        bss = .;
        *(.bss)
    }
    . = ALIGN(4096);
    __bss_end = .;

    . = 0x20000 + __bss_end;
    __sys_stack = .;

    . = 0x20000 + __sys_stack;
    __irq_stack = .;

    . = 0x20000 + __irq_stack;
    __fiq_stack = .;

    . = 0x20000 + __fiq_stack;
    __svc_stack = .;

    . = 0x20000 + __svc_stack;
    __abort_stack = .;

    . = 0x20000 + __abort_stack;
    __undefined_stack = .;

    __end_stack = .;
    . = ALIGN(4096);

    __PAGE_TABLE = .;
    . = 0x805000 + __PAGE_TABLE;

    __KERNEL_END = .;
}
