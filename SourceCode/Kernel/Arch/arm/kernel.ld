ENTRY(__text_start)

__SIZE__ = 0x02000000;

MEMORY
{
    ram : ORIGIN = 0x0000, LENGTH = __SIZE__
}

SECTIONS
{
    . = 0x18000000;
    __text_start = .;
    .text :
    {
        KEEP(*(.interrupt_vector_table))
        KEEP(*(.text.boot))
        *(.text)
    } > ram
    . = ALIGN(4096);
    __text_end = .;

    __rodata_start = .;
    .rodata :
    {
        *(.rodata)
    } > ram
    . = ALIGN(4096);
    __rodata_end = .;

    __data_start = .;
    .data :
    {
        *(.data)
    } > ram
    . = ALIGN(4096);
    __data_end = .;

    __bss_start = .;
    .bss :
    {
        bss = .;
        *(.bss)
    } > ram
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
    . = 0x400000 + __PAGE_TABLE;

    __heap_begin = .;

    .usercode __SIZE__ : {
        *(.usercode*)
    }
}
