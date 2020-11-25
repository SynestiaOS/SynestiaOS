//
// Created by XingfengYang on 2020/11/23.
//
#include <kernel/slab.h>

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
}
