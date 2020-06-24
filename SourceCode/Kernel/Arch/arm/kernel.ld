ENTRY(__text_start)

SECTIONS
{
    . = 0x8000;
    __text_start = .;
    .text :
    {
        KEEP(*(.interrupt_vector_table))
        KEEP(*(.text.boot))
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

    . = 0x8000 + __bss_end;
    __svc_stack = .;

    . = 0x8000 + __svc_stack;
    __irq_stack = .;

    . = 0x8000 + __irq_stack;
    __fiq_stack = .;

    . = 0x8000 + __fiq_stack;
    __sys_stack = .;

    __end_stack = .;

    __PAGE_TABLE = .;
    . = 0x804000 + __PAGE_TABLE;

    __heap_begin = .;
}
