//
// Created by XingfengYang on 2021/1/21.
//
#include "arm/kernel_vmm.h"
#include "raspi2/led.h"
#include "raspi2/gpu.h"
#include "libgui/gui_label.h"
#include "libc/stdlib.h"
#include "libc/stdint.h"
#include "raspi2/synestia_os_hal.h"
#include "kernel/kernel.h"
#include "kernel/bus.h"
#include "arm/page.h"
#include "kernel/ext2.h"
#include "kernel/interrupt.h"
#include "kernel/kheap.h"
#include "kernel/scheduler.h"
#include "kernel/slab.h"
#include "kernel/vfs.h"
#include "libgui/gui_window.h"
#include "libgfx/gfx2d.h"

extern uint32_t __HEAP_BEGIN;
extern char _binary_initrd_img_start[];
uint32_t EXT2_ADDRESS = (uint32_t) _binary_initrd_img_start;
extern uint32_t GFX2D_BUFFER[1024 * 768];

extern uint32_t *gpu_flush(int args);

extern DaVinciKernel kernel;

_Noreturn uint32_t *GPU_FLUSH(int args) {
    while (1) {
        kernel.genericInterruptManager.operation.disableInterrupt(&kernel.genericInterruptManager);
        gpu_flush(0);
        kernel.genericInterruptManager.operation.enableInterrupt(&kernel.genericInterruptManager);
    }
}

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

void daVinci_kernel_default_init(struct DaVinciKernel *kernel) {
    led_init();
    print_splash();
    synestia_init_bsp();

    // create interrupt manager and init generic interrupt
    interrupt_manager_create(&kernel->genericInterruptManager);

    synestia_init_timer();

    // create kernel physical page allocator
    page_allocator_create(&kernel->kernelPageAllocator, KERNEL_PHYSICAL_START, KERNEL_PHYSICAL_SIZE);

    // init kernel virtual memory mapping
    kernel_vmm_init();

    // init kernel timer manager
    kernel_timer_manager_create(&kernel->kernelTimerManager);
    kernel->kernelTimerManager.operation.init(&kernel->kernelTimerManager);
    scheduler_create(&kernel->cfsScheduler);

    // create kernel heap
    heap_create(&kernel->kernelHeap, (uint32_t) &__HEAP_BEGIN, KERNEL_PHYSICAL_SIZE - (uint32_t) (&__HEAP_BEGIN));
    slab_create(&kernel->kernelObjectSlab, 0, 0);

    // create userspace physical page allocator
    page_allocator_create(&kernel->userspacePageAllocator, USER_PHYSICAL_START, USER_PHYSICAL_SIZE);

    kernel->genericInterruptManager.operation.init(&kernel->genericInterruptManager);

    vfs_create(&kernel->vfs);
    kernel->vfs.operations.mount(&kernel->vfs, "root", FILESYSTEM_EXT2, (void *) EXT2_ADDRESS);

    service_bus_create(&kernel->testBus, "test BUS");

    gpu_init();
    gfx2d_create_surface(&kernel->mainSurface, 1024, 768, GFX2D_BUFFER);
    uint32_t *background = (uint32_t *) kernel->kernelHeap.operations.alloc(&kernel->kernelHeap, 768 * 1024 * 4);
    vfs_kernel_read(&kernel->vfs, "/initrd/init/bg1024_768.dat", (char *) background, 768 * 1024 * 4);
    kernel->mainSurface.operations.drawBitmap(&kernel->mainSurface, 0, 0, 1024, 768, background);
    kernel->kernelHeap.operations.free(&kernel->kernelHeap, background);

    kernel->mainSurface.operations.fillRect(&kernel->mainSurface, 0, 0, 1024, 64, FLUENT_PRIMARY_COLOR);
    GUILabel logo;
    logo.component.foreground = ColorRGB(0xFF, 0xFF, 0xFF);
    logo.component.colorMode = TRANSPARENT;
    gui_label_create(&logo);
    gui_label_init(&logo, 480, 28, "SynestiaOS (alpha 0.1.3)");
    gui_label_draw(&logo);

    kernel->cfsScheduler.operation.init(&kernel->cfsScheduler);

    Thread *gpuProcess = thread_create("gpu", (ThreadStartRoutine) &GPU_FLUSH, 0, 0, sysModeCPSR());
    gpuProcess->cpuAffinity = cpu_number_to_mask(0);
    kernel->cfsScheduler.operation.addThread(&kernel->cfsScheduler, gpuProcess, 1);
}

void daVinci_kernel_default_start(struct DaVinciKernel *kernel) {
    kernel->cfsScheduler.operation.schedule(&kernel->cfsScheduler);
}

DaVinciKernel *daVinci_create(DaVinciKernel *daVinciKernel) {

    daVinciKernel->operation.init = (DaVinciKernelOperationInit) daVinci_kernel_default_init;
    daVinciKernel->operation.start = (DaVinciKernelOperationStart) daVinci_kernel_default_start;

    return daVinciKernel;
}
