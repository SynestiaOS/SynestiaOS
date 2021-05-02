#include "kernel/assert.h"
#include "kernel/log.h"
#include "arm/register.h"
#include "arm/kernel_vmm.h"
#include "arm/page.h"
#include "kernel/ext2.h"
#include "kernel/interrupt.h"
#include "kernel/kheap.h"
#include "kernel/percpu.h"
#include "kernel/scheduler.h"
#include "kernel/slab.h"
#include "kernel/vfs.h"
#include "libc/stdlib.h"
#include "raspi2/synestia_os_hal.h"
#include "kernel/ktimer.h"
#include "kernel/module.h"

extern uint32_t __text_start;
extern uint32_t __vector_table_start;
extern uint32_t __vector_table_end;
extern uint32_t __module_init_start;
extern uint32_t __module_init_end;
extern uint32_t __text_end;
extern uint32_t __rodata_start;
extern uint32_t __rodata_end;
extern uint32_t __data_start;
extern uint32_t __data_end;
extern uint32_t __bss_start;
extern uint32_t __bss_end;
extern uint32_t __sys_stack;
extern uint32_t __irq_stack;
extern uint32_t __fiq_stack;
extern uint32_t __svc_stack;
extern uint32_t __abort_stack;
extern uint32_t __undefined_stack;
extern uint32_t __end_stack;
extern uint32_t __PAGE_TABLE;
extern uint32_t __KERNEL_END;

extern uint32_t __KERNEL_END;
extern char _binary_initrd_img_start[];
extern char _binary_initrd_img_end[];
extern char _binary_initrd_img_size[];
uint32_t EXT2_ADDRESS = (uint32_t) _binary_initrd_img_start;

InterruptManager genericInterruptManager;
PhysicalPageAllocator kernelPageAllocator;
PhysicalPageAllocator userspacePageAllocator;
Heap kernelHeap;
Slab kernelObjectSlab;
Scheduler cfsScheduler;
KernelTimerManager kernelTimerManager;
VFS vfs;

void print_splash() {
    printf("   _____                       _   _       \n");
    printf("  / ____|                     | | (_)      \n");
    printf(" | (___  _   _ _ __   ___  ___| |_ _  __ _ \n");
    printf("  \\___ \\| | | | '_ \\ / _ \\/ __| __| |/ _` |\n");
    printf("  ____) | |_| | | | |  __/\\__ \\ |_| | (_| |\n");
    printf(" |_____/ \\__, |_| |_|\\___||___/\\__|_|\\__,_|\n");
    printf("          __/ |                            \n");
    printf("         |___/                          \n");
}

void print_memory_map() {
    LogInfo("[MemMap]: __text_start         = 0x%x \n", (uint32_t) &__text_start);
    LogInfo("[MemMap]: __vector_table_start = 0x%x \n", (uint32_t) &__vector_table_start);
    LogInfo("[MemMap]: __vector_table_end   = 0x%x \n", (uint32_t) &__vector_table_end);
    LogInfo("[MemMap]: __module_init_start  = 0x%x \n", (uint32_t) &__module_init_start);
    LogInfo("[MemMap]: __module_init_end  = 0x%x \n", (uint32_t) &__module_init_end);
    LogInfo("[MemMap]: __text_end           = 0x%x \n", (uint32_t) &__text_end);
    LogInfo("[MemMap]: __rodata_start       = 0x%x \n", (uint32_t) &__rodata_start);
    LogInfo("[MemMap]: __rodata_end         = 0x%x \n", (uint32_t) &__rodata_end);
    LogInfo("[MemMap]: __data_start         = 0x%x \n", (uint32_t) &__data_start);
    LogInfo("[MemMap]: __data_end           = 0x%x \n", (uint32_t) &__data_end);
    LogInfo("[MemMap]: __bss_start          = 0x%x \n", (uint32_t) &__bss_start);
    LogInfo("[MemMap]: __bss_end            = 0x%x \n", (uint32_t) &__bss_end);
    LogInfo("[MemMap]: __sys_stack          = 0x%x \n", (uint32_t) &__sys_stack);
    LogInfo("[MemMap]: __irq_stack          = 0x%x \n", (uint32_t) &__irq_stack);
    LogInfo("[MemMap]: __fiq_stack          = 0x%x \n", (uint32_t) &__fiq_stack);
    LogInfo("[MemMap]: __svc_stack          = 0x%x \n", (uint32_t) &__svc_stack);
    LogInfo("[MemMap]: __abort_stack        = 0x%x \n", (uint32_t) &__abort_stack);
    LogInfo("[MemMap]: __undefined_stack    = 0x%x \n", (uint32_t) &__undefined_stack);
    LogInfo("[MemMap]: __end_stack          = 0x%x \n", (uint32_t) &__end_stack);
    LogInfo("[MemMap]: __PAGE_TABLE         = 0x%x \n", (uint32_t) &__PAGE_TABLE);
    LogInfo("[MemMap]: __KERNEL_END         = 0x%x \n", (uint32_t) &__KERNEL_END);

    LogInfo("[RamFS]: start at              : 0x%x \n", &_binary_initrd_img_start);
    LogInfo("[RamFS]: end at                : 0x%x \n", &_binary_initrd_img_end);
}

void kernel_main(void) {
    if (read_cpuid() == 0) {
        print_splash();

        print_memory_map();

        synestia_init_bsp();

        kernel_module_level_0_init();

        // create interrupt manager and init generic interrupt
        interrupt_manager_create(&genericInterruptManager);

        // init kernel timer manager
        kernel_timer_manager_create(&kernelTimerManager);
        kernelTimerManager.operation.init(&kernelTimerManager);

        synestia_init_timer();
        kernel_module_level_1_init();

        // create kernel physical page allocator
        page_allocator_create(&kernelPageAllocator, (uint32_t) &__KERNEL_END + PAGE_SIZE,
                              KERNEL_PHYSICAL_SIZE - (uint32_t) &__KERNEL_END);

        // init kernel virtual memory mapping
        kernel_vmm_init();

        scheduler_create(&cfsScheduler);

        // create kernel heap
        heap_create(&kernelHeap, (uint32_t) &__KERNEL_END + PAGE_SIZE,
                    KERNEL_PHYSICAL_SIZE - (uint32_t) &__KERNEL_END);
        DEBUG_ASSERT((uint32_t) kernelHeap.address >= (uint32_t) &_binary_initrd_img_end);
        slab_create(&kernelObjectSlab, 0, 0);

        // create userspace physical page allocator
        page_allocator_create(&userspacePageAllocator, USER_PHYSICAL_START, USER_PHYSICAL_SIZE);

        genericInterruptManager.operation.init(&genericInterruptManager);

        vfs_create(&vfs);
        vfs.operations.mount(&vfs, "root", FILESYSTEM_EXT2, (void *) EXT2_ADDRESS);

        LogInfo("[Ext2Verify]: check start.\n");
        uint32_t *ext2VerifyFile = (uint32_t *) kernelHeap.operations.alloc(&kernelHeap, 1024 * 32768);
        vfs_kernel_read(&vfs, "/initrd/sbin/ext2verify.bin", (char *) ext2VerifyFile, 1024 * 32768);
        uint32_t *tmp = ext2VerifyFile;
        for (uint32_t i = 0; i < 8 * MB; i++) {
            if (*tmp != i) {
                LogError("[Ext2Verify]: check failed at %d \n", i);
                LogError("[Ext2Verify]: check failed with %d \n", *tmp);
                goto halt;
            }
            tmp++;
        }
        LogInfo("[Ext2Verify]: check success. \n", *ext2VerifyFile);
        kernelHeap.operations.free(&kernelHeap, ext2VerifyFile);

        kernel_module_level_2_init();

        cfsScheduler.operation.schedule(&cfsScheduler);
    }
    halt:
    {};


    // schd_switch_next();
}
