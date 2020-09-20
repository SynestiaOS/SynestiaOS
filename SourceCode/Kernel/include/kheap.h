//
// Created by XingfengYang on 2020/6/12.
//

#ifndef __KERNEL_KHEAP_H__
#define __KERNEL_KHEAP_H__

#include <list.h>
#include <stdint.h>
#include <type.h>

typedef void (*HeapAllocCallback)(struct Heap *heap, void *ptr, uint32_t size);

typedef void (*HeapFreeCallback)(struct Heap *heap, void *ptr);

typedef void *(*HeapOperationAlloc)(struct Heap *heap, uint32_t size);

typedef void *(*HeapOperationAllocAligned)(struct Heap *heap, uint32_t size, uint32_t alignment);

typedef void *(*HeapOperationCountAlloc)(struct Heap *heap, uint32_t count, uint32_t size);

typedef void *(*HeapOperationReAlloc)(struct Heap *heap, void *ptr, uint32_t size);

typedef KernelStatus (*HeapOperationFree)(struct Heap *heap, void *ptr);

typedef void (*HeapOperationSetAllocCallback)(struct Heap *heap, HeapAllocCallback callback);

typedef void (*HeapOperationSetFreeCallback)(struct Heap *heap, HeapFreeCallback callback);

typedef struct HeapOperations {
    HeapOperationAlloc alloc;
    HeapOperationAllocAligned allocAligned;
    HeapOperationCountAlloc calloc;
    HeapOperationReAlloc realloc;
    HeapOperationFree free;
    HeapOperationSetAllocCallback setAllocCallback;
    HeapOperationSetFreeCallback setFreeCallback;
} HeapOperations;

typedef struct HeapArea {
    uint32_t size;
    ListNode list;
} __attribute__((packed)) HeapArea;

typedef struct HeapStatistics {
    uint32_t allocatedBlockCount;
    uint32_t allocatedSize;
    uint32_t mergeCounts;
} HeapStatistics;

typedef struct Heap {
    uint32_t address;
    uint32_t maxSizeLimit;
    HeapArea *usingListHead;
    HeapArea *freeListHead;
    HeapAllocCallback allocCallback;
    HeapFreeCallback freeCallback;
    HeapOperations operations;

    HeapStatistics statistics;
} Heap;

KernelStatus heap_create(Heap *heap, uint32_t addr, uint32_t size);

#endif //__KERNEL_KHEAP_H__
