//
// Created by XingfengYang on 2020/6/12.
//

#include "kernel/kheap.h"
#include "arm/page.h"
#include "kernel/log.h"
#include "kernel/scheduler.h"
#include "libc/stdlib.h"
#include "libc/string.h"

extern PhysicalPageAllocator kernelPageAllocator;
extern Scheduler cfsScheduler;

void heap_default_alloc_callback(struct Heap *heap, void *ptr, uint32_t size) {
    heap->statistics.allocatedSize += size;
    heap->statistics.allocatedBlockCount += 1;
    LogInfo("[Heap]: alloc 0x%x bytes at 0x%x.\n", size, (uint32_t) ptr);
}

void heap_default_free_callback(struct Heap *heap, void *ptr) {
    HeapArea *heapArea = (HeapArea *) (ptr - sizeof(HeapArea));
    if (heap->statistics.allocatedSize >= heapArea->size) {
        heap->statistics.allocatedSize -= heapArea->size;
    }

    if (heap->statistics.allocatedBlockCount > 0) {
        heap->statistics.allocatedBlockCount -= 1;
    }
    LogInfo("[Heap]: free 0x%x bytes at 0x%x.\n", heapArea->size, (uint32_t) ptr);
}

void *heap_default_alloc(struct Heap *heap, uint32_t size) {
    uint32_t allocSize = size + sizeof(HeapArea);
    uint32_t offset = sizeof(void *) - (size % sizeof(void *));

    if (heap->freeListHead == nullptr) {
        LogError("[KHeap]: failed to get freeListHead.\n");
        return nullptr;
    }

    HeapArea *currentFreeArea = heap->freeListHead;
    while (currentFreeArea != nullptr) {
        // if the size of the free block can contain the request size and a rest HeapArea,
        // then just use it, and split a new block
        if (currentFreeArea->size >= (allocSize + offset)) {
            // 1. split a rest free HeapArea
            uint32_t newFreeHeapAreaAddress = (uint32_t) (void *) currentFreeArea + sizeof(HeapArea) + size + offset;
            uint32_t restSize = currentFreeArea->size - allocSize - offset;

            HeapArea *newFreeArea = (HeapArea *) newFreeHeapAreaAddress;
            newFreeArea->size = restSize;

            // 2.link new free heap area to free list
            newFreeArea->list.prev = currentFreeArea->list.prev;
            newFreeArea->list.next = currentFreeArea->list.next;
            currentFreeArea->list.prev->next = &newFreeArea->list;
            if (currentFreeArea->list.next != nullptr) {
                currentFreeArea->list.next->prev = &newFreeArea->list;
            }

            // 3. link this to using list
            currentFreeArea->list.prev = nullptr;
            currentFreeArea->list.next = nullptr;
            currentFreeArea->size = size;
            HeapArea *usingArea = heap->usingListHead;
            if (usingArea == nullptr) {
                heap->usingListHead = currentFreeArea;
            } else {
                while (usingArea->list.next != nullptr) {
                    usingArea = getNode(usingArea->list.next, HeapArea, list);
                }
                usingArea->list.next = &currentFreeArea->list;
                currentFreeArea->list.prev = &usingArea->list;
            }

            // 4. return the ptr of the using block
            void *ptr = (void *) currentFreeArea + sizeof(HeapArea);
            heap->allocCallback(heap, ptr, size);
            return ptr;
        }
        currentFreeArea = getNode(currentFreeArea->list.next, HeapArea, list);
        // no free block found ,it's means we must do some memory defragmentation
        // TODO: defragmentation
    }
    return nullptr;
}

void *heap_default_alloc_aligned(struct Heap *heap, uint32_t size, uint32_t alignment) {
    uint32_t offset = alignment - 1 + alignment;
    void *p1 = heap_default_alloc(heap, size + offset);
    if (p1 == nullptr) {
        return nullptr;
    }
    void **p2 = (void **) (((uint32_t) p1 + offset) & ~(alignment - 1));
    p2[-1] = p1;
    return p2;
}

void *heap_default_count_alloc(struct Heap *heap, uint32_t count, uint32_t size) {
    return heap->operations.alloc(heap, count * size);
}

void *heap_default_realloc(struct Heap *heap, void *ptr, uint32_t size) {
    // 1. alloc new heap area
    void *newHeapArea = heap->operations.alloc(heap, size);
    if (newHeapArea == nullptr) {
        LogError("[heap] alloc mem failed when realloc.\n");
        return nullptr;
    }

    // 2. copy the data from old heap area to new heap area
    HeapArea *oldHeapArea = ptr - sizeof(HeapArea);
    uint32_t dataSize = oldHeapArea->size;
    memcpy(newHeapArea, ptr, dataSize);

    // 3. free old heap area
    KernelStatus freeStatus = heap->operations.free(heap, ptr);
    if (freeStatus != OK) {
        LogError("[heap] free old mem failed when realloc.\n");
    }
    return newHeapArea;
}

KernelStatus heap_default_free(struct Heap *heap, void *ptr) {
    LogInfo("[KHeap] want free: 0x%x. \n", ptr);

    // 1. get HeapArea address
    uint32_t address = (uint32_t) (ptr - sizeof(HeapArea));
    HeapArea *currentArea = (HeapArea *) address;

    // 2. unlink from using list
    if (currentArea->list.prev != nullptr) {
        currentArea->list.prev->next = currentArea->list.next;
    } else {
        // if this block is the head of using list, then make using list point to next block.
        if (currentArea->list.next != nullptr) {
            heap->usingListHead = getNode(currentArea->list.next, HeapArea, list);
            currentArea->list.next->prev = nullptr;
        } else {
            heap->usingListHead = nullptr;
        }
    }

    if (currentArea->list.next != nullptr && currentArea->list.prev != nullptr) {
        currentArea->list.next->prev = currentArea->list.prev;
    }

    // 3. link this to free list
    HeapArea *freeArea = heap->freeListHead;
    while (freeArea->list.next != nullptr) {
        freeArea = getNode(freeArea->list.next, HeapArea, list);
    }
    currentArea->list.prev = &freeArea->list;
    currentArea->list.next = freeArea->list.next;
    freeArea->list.next = &currentArea->list;

    // do some merge stuff between two adjacent free heap area
    HeapArea *firstFreeArea = heap->freeListHead;
    while (firstFreeArea->list.next != nullptr) {
        firstFreeArea = getNode(firstFreeArea->list.next, HeapArea, list);
        HeapArea *secondFreeArea = firstFreeArea;
        while (secondFreeArea->list.next != nullptr) {
            secondFreeArea = getNode(secondFreeArea->list.next, HeapArea, list);

            // check is adjacent free heap area
            if (firstFreeArea + sizeof(HeapArea) + firstFreeArea->size == secondFreeArea) {

                // resize the first heap area
                firstFreeArea->size = firstFreeArea->size + sizeof(HeapArea) + secondFreeArea->size;
                firstFreeArea->list.next = secondFreeArea->list.next;
                secondFreeArea->list.next->prev->next = &firstFreeArea->list;

                // delink the second heap area
                secondFreeArea->list.prev = nullptr;
                secondFreeArea->list.next = nullptr;
                secondFreeArea->size = 0;

                heap->statistics.mergeCounts++;
            }
        }
    }
    heap->freeCallback(heap, ptr);
    memset(ptr, 0, currentArea->size);
    ptr = nullptr;

    return OK;
}

void heap_default_set_alloc_callback(struct Heap *heap, HeapAllocCallback callback) { heap->allocCallback = callback; }

void heap_default_set_free_callback(struct Heap *heap, HeapFreeCallback callback) { heap->freeCallback = callback; }

KernelStatus heap_create(Heap *heap, uint32_t addr, uint32_t size) {
    heap->address = addr;
    LogInfo("[KHeap] at: %d. \n", heap->address);

    PhysicalPageAllocator *physicalPageAllocator;
    Thread *currThread = cfsScheduler.operation.getCurrentThread(&cfsScheduler);
    if (currThread == nullptr) {
        physicalPageAllocator = &kernelPageAllocator;
    } else {
        physicalPageAllocator = currThread->memoryStruct.virtualMemory.physicalPageAllocator;
    }
    // allocate physical page for kernel heap
    uint32_t heapPhysicalPage = (uint32_t) physicalPageAllocator->operations.allocHugeAt(
            physicalPageAllocator, USAGE_KERNEL_HEAP, heap->address >> VA_OFFSET, size - heap->address);
    LogInfo("[KHeap] alloc heap page: %d. \n", (uint32_t) heapPhysicalPage);

    heap->address = KERNEL_PHYSICAL_START + heapPhysicalPage * PAGE_SIZE;
    LogInfo("[KHeap] kheap at: %d. \n", heap->address);

    HeapArea *freeHead = (HeapArea *) heap->address;
    freeHead->size = 0;
    freeHead->list.prev = nullptr;

    HeapArea *freeArea = (HeapArea *) (heap->address + sizeof(HeapArea));
    freeArea->size = (size - (uint32_t) (char *) heap->address -
                      2 * sizeof(HeapArea));// all memory
    freeHead->list.next = &freeArea->list;
    freeArea->list.next = nullptr;
    freeArea->list.prev = &freeHead->list;

    HeapArea *usingHead = nullptr;

    heap->freeListHead = freeHead;
    heap->usingListHead = usingHead;

    heap->maxSizeLimit = size;
    heap->operations.setFreeCallback = (HeapOperationSetFreeCallback) heap_default_set_free_callback;
    heap->operations.setAllocCallback = (HeapOperationSetAllocCallback) heap_default_set_alloc_callback;

    heap->allocCallback = (HeapAllocCallback) heap_default_alloc_callback;
    heap->freeCallback = (HeapFreeCallback) heap_default_free_callback;

    heap->operations.alloc = (HeapOperationAlloc) heap_default_alloc;
    heap->operations.allocAligned = (HeapOperationAllocAligned) heap_default_alloc_aligned;
    heap->operations.calloc = (HeapOperationCountAlloc) heap_default_count_alloc;
    heap->operations.realloc = (HeapOperationReAlloc) heap_default_realloc;
    heap->operations.free = (HeapOperationFree) heap_default_free;

    heap->statistics.allocatedBlockCount = 0;
    heap->statistics.allocatedSize = 0;
    heap->statistics.mergeCounts = 0;

    LogInfo("[KHeap] kheap created. \n");
    return OK;
}
