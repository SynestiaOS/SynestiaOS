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
        KEEP(*(.moduleinit))
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
