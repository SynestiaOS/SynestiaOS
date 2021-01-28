#include "libc/string.h"
#include "kernel/bus.h"
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
#include "libgui/gui_animation.h"
#include "libgui/gui_label.h"
#include "libgui/gui_window.h"
#include "raspi2/gpu.h"
#include "raspi2/synestia_os_hal.h"
#include "libgfx/gfx2d.h"
#include "raspi2/led.h"
#include "kernel/ktimer.h"

extern uint32_t __HEAP_BEGIN;
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
GfxSurface mainSurface;


extern void test_threads_init(void);

extern uint32_t *gpu_flush(int args);

extern uint32_t GFX2D_BUFFER[1024 * 768];

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

_Noreturn uint32_t *GPU_FLUSH(int args) {
    while (1) {
        genericInterruptManager.operation.disableInterrupt(&genericInterruptManager);
        gpu_flush(0);
        genericInterruptManager.operation.enableInterrupt(&genericInterruptManager);
    }
}

void kernel_main(void) {
    if (read_cpuid() == 0) {
        led_init();
        print_splash();
        synestia_init_bsp();

        // create interrupt manager and init generic interrupt
        interrupt_manager_create(&genericInterruptManager);

        // init kernel timer manager
        kernel_timer_manager_create(&kernelTimerManager);
        kernelTimerManager.operation.init(&kernelTimerManager);

        synestia_init_timer();

        // create kernel physical page allocator
        page_allocator_create(&kernelPageAllocator, __HEAP_BEGIN, KERNEL_PHYSICAL_SIZE - __HEAP_BEGIN);

        // init kernel virtual memory mapping
//        kernel_vmm_init();

        scheduler_create(&cfsScheduler);

        // create kernel heap
        heap_create(&kernelHeap, (uint32_t) &__HEAP_BEGIN, KERNEL_PHYSICAL_SIZE - __HEAP_BEGIN);
        slab_create(&kernelObjectSlab, 0, 0);

        // create userspace physical page allocator
        page_allocator_create(&userspacePageAllocator, USER_PHYSICAL_START, USER_PHYSICAL_SIZE);

        genericInterruptManager.operation.init(&genericInterruptManager);

        vfs_create(&vfs);
        vfs.operations.mount(&vfs, "root", FILESYSTEM_EXT2, (void *) EXT2_ADDRESS);

        gpu_init();
        gfx2d_create_surface(&mainSurface, 1024, 768, GFX2D_BUFFER);
        uint32_t *background = (uint32_t *) kernelHeap.operations.alloc(&kernelHeap, 768 * 1024 * 4);
        vfs_kernel_read(&vfs, "/initrd/init/bg1024_768.dat", (char *) background, 768 * 1024 * 4);
        mainSurface.operations.drawBitmap(&mainSurface, 0, 0, 1024, 768, background);
        kernelHeap.operations.free(&kernelHeap, background);

        mainSurface.operations.fillRect(&mainSurface, 0, 0, 1024, 64, FLUENT_PRIMARY_COLOR);
        GUILabel logo;
        logo.component.foreground = ColorRGB(0xFF, 0xFF, 0xFF);
        logo.component.colorMode = TRANSPARENT;
        gui_label_create(&logo);
        gui_label_init(&logo, 480, 28, "SynestiaOS (alpha 0.1.3)");
        gui_label_draw(&logo);

        cfsScheduler.operation.init(&cfsScheduler);

        Thread *gpuProcess = thread_create("gpu", (ThreadStartRoutine) &GPU_FLUSH, 0, 0, sysModeCPSR());
        gpuProcess->cpuAffinity = cpu_number_to_mask(0);
        cfsScheduler.operation.addThread(&cfsScheduler, gpuProcess, 1);

        test_threads_init();

        cfsScheduler.operation.schedule(&cfsScheduler);
    }

    // schd_switch_next();
}
