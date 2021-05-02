//
// Created by XingfengYang on 2021/5/2.
//

#include "kernel/module.h"
#include "kernel/log.h"
#include "libc/stdint.h"

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
#include "libgui/gui_animation.h"
#include "libgui/gui_label.h"
#include "libgui/gui_window.h"
#include "raspi2/gpu.h"
#include "raspi2/synestia_os_hal.h"
#include "libgfx/gfx2d.h"
#include "raspi2/led.h"
#include "kernel/ktimer.h"
#include "kernel/module.h"


extern Heap kernelHeap;
extern Scheduler cfsScheduler;
extern VFS vfs;
GfxSurface mainSurface;

extern uint32_t *gpu_flush(int args);
extern uint32_t GFX2D_BUFFER[1024 * 768];

extern void test_threads_init();

_Noreturn uint32_t *GPU_FLUSH(int args) {
    while (1) {
        gpu_flush(0);
    }
}

uint32_t module_desktop_init(void* data){
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

    LogInfo("[Module]: module desktop inited.\n");
    return 1;
}
module_init(module_desktop_init);