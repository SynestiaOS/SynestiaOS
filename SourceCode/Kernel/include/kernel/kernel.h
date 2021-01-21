//
// Created by XingfengYang on 2021/1/21.
//

#ifndef SYNESTIAOS_KERNEL_H
#define SYNESTIAOS_KERNEL_H

#include "kernel/ktimer.h"
#include "libgfx/gfx2d.h"
#include "arm/page.h"
#include "kernel/bus.h"
#include "kernel/ext2.h"
#include "kernel/interrupt.h"
#include "kernel/kheap.h"
#include "kernel/percpu.h"
#include "kernel/scheduler.h"
#include "kernel/slab.h"
#include "kernel/vfs.h"

typedef void (*DaVinciKernelOperationInit)(struct DaVinciKernel *kernel);

typedef void (*DaVinciKernelOperationStart)(struct DaVinciKernel *kernel);

typedef struct DaVinciKernelOperation {
    DaVinciKernelOperationInit init;
    DaVinciKernelOperationStart start;
} DaVinciKernelOperation;

typedef struct DaVinciKernel {
    struct InterruptManager genericInterruptManager;
    struct PhysicalPageAllocator kernelPageAllocator;
    struct PhysicalPageAllocator userspacePageAllocator;
    struct Heap kernelHeap;
    struct Slab kernelObjectSlab;
    struct Scheduler cfsScheduler;
    struct KernelTimerManager kernelTimerManager;
    struct VFS vfs;
    struct GfxSurface mainSurface;
    struct ServiceBus testBus;
    DaVinciKernelOperation operation;
} DaVinciKernel;

struct DaVinciKernel *daVinci_create(struct DaVinciKernel *daVinciKernel);


#endif //SYNESTIAOS_KERNEL_H
