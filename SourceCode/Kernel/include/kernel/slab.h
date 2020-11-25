//
// Created by XingfengYang on 2020/11/22.
//

#ifndef __SYNESTIAOS_SLAB_H__
#define __SYNESTIAOS_SLAB_H__

#include <kernel/kobject.h>
#include <kernel/type.h>
#include <libc/stdint.h>

#define SLAB_ARRAY_COUNT 64

typedef void (*SlabAllocCallback)(struct Slab *slab, KernelObjectType type, void *ptr);

typedef void (*SlabFreeCallback)(struct Slab *slab, KernelObjectType type, void *ptr);

typedef void *(*SlabOperationAlloc)(struct Slab *slab, KernelObjectType type);

typedef KernelStatus (*SlabOperationFree)(struct Slab *slab, void *ptr);

typedef void (*SlabOperationSetAllocCallback)(struct Slab *slab, SlabAllocCallback callback);

typedef void (*SlabOperationSetFreeCallback)(struct Slab *slab, SlabFreeCallback callback);

typedef struct SlabStatistics {
    int used[SLAB_ARRAY_COUNT];
    int free[SLAB_ARRAY_COUNT];
} SlabStatistics;

typedef struct SlabOperations {
    SlabOperationAlloc alloc;
    SlabOperationFree free;
    SlabOperationSetAllocCallback setAllocCallback;
    SlabOperationSetFreeCallback setFreeCallback;
} SlabOperations;


/**
 * kernelObjects struct:
 *
 * [ThreadObject,   Mutex,    Semaphore   ...64]
 *     |              |           |
 *   thread1       mutex1     semaphore1
 *     |              |           |
 *   thread2       mutex2     semaphore2
 *     |              |           |
 *    ...            ...         ...
 *
 *  We can use LRU here to cache our kernel Objects.
 *  Put the most recently released kernel object at the front of the corresponding linked list
 */
typedef struct Slab {
    uint32_t address;
    uint32_t maxSizeLimit;

    struct KernelObject kernelObjects[SLAB_ARRAY_COUNT];

    SlabAllocCallback allocCallback;
    SlabFreeCallback freeCallback;

    SlabOperations operations;
    SlabStatistics statistics;
} Slab;

KernelStatus slab_create(Slab *slab, uint32_t addr, uint32_t size);

#endif//__SYNESTIAOS_SLAB_H__
