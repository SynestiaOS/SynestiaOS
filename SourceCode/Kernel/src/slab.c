//
// Created by XingfengYang on 2020/11/23.
//
#include "arm/page.h"
#include "kernel/slab.h"
#include "kernel/log.h"

extern PhysicalPageAllocator kernelPageAllocator;

void slab_default_alloc_callback(struct Slab *slab, KernelObjectType type, void *ptr) {
}

void slab_default_free_callback(struct Slab *slab, KernelObjectType type, void *ptr) {
}

void *slab_default_alloc(struct Slab *slab, KernelObjectType type) {

}

KernelStatus slab_default_free(struct Slab *slab, void *ptr) {
}

void slab_default_set_alloc_callback(struct Slab *slab, SlabAllocCallback callback) {
}

void slab_default_set_free_callback(struct Slab *slab, SlabFreeCallback callback) {
}

KernelStatus slab_create(Slab *slab, uint32_t addr, uint32_t size) {
    slab->allocCallback = slab_default_alloc_callback;
    slab->freeCallback = slab_default_free_callback;

    slab->address = addr;
    LogInfo("[KSlab] at: %d. \n", slab->address);

    PhysicalPageAllocator *physicalPageAllocator = &kernelPageAllocator;

    // allocate physical page for slab
    uint32_t slabPhysicalPage = (uint32_t) physicalPageAllocator->operations.allocHugeAt(
            physicalPageAllocator, USAGE_KERNEL_HEAP, (slab->address | 4 * KB) >> VA_OFFSET, size - slab->address);
    LogInfo("[KSlab] alloc slab page: %d. \n", (uint32_t) slabPhysicalPage);

    slab->address = KERNEL_PHYSICAL_START + slabPhysicalPage * PAGE_SIZE;
    LogInfo("[KHeap] kheap at: %d. \n", slab->address);


    slab->operations.setFreeCallback = slab_default_set_free_callback;
    slab->operations.setAllocCallback = slab_default_set_alloc_callback;

    slab->operations.alloc = slab_default_alloc;
    slab->operations.free = slab_default_free;


    LogInfo("[KSlab] kslab created. \n");
    return OK;
}
