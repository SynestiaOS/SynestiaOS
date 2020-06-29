//
// Created by XingfengYang on 2020/6/12.
//

#include <kheap.h>
#include <stdlib.h>

static heap_alloc_func heapAllocFunc = nullptr;
static heap_free_func heapFreeFunc = nullptr;

static HeapArea *usingListHead;
static HeapArea *freeListHead;

void default_heap_alloc_func(void *ptr, uint32_t size) {
    printf("[Heap] alloc %d bytes at %d\n", size, (uint32_t) ptr);
}

void default_heap_free_func(void *ptr) {
    HeapArea *heap = (HeapArea *) (ptr - sizeof(HeapArea));
    printf("[Heap] free %d bytes at %d\n", heap->size, (uint32_t) ptr);
}

void kernel_heap_set_alloc_callback(heap_alloc_func callback) {
    heapAllocFunc = callback;
}

void kernel_heap_set_free_callback(heap_free_func callback) {
    heapFreeFunc = callback;
}

void kernel_heap_init() {
    uint32_t heap_address = &__heap_begin;
    freeListHead = (HeapArea *) heap_address;
    freeListHead->size = 0;
    freeListHead->list.prev = nullptr;

    HeapArea *freeArea = heap_address + sizeof(HeapArea);
    freeArea->size = (0xFFFFFFFF - (uint32_t) (char *) heap_address - 2 * sizeof(HeapArea)); // all memory
    freeListHead->list.next = &freeArea->list;
    freeArea->list.next = nullptr;
    freeArea->list.prev = &freeListHead->list;

    usingListHead = nullptr;
}

void *kernel_heap_alloc(uint32_t size) {
    uint32_t allocSize = size + sizeof(HeapArea);

    HeapArea *currentFreeArea = freeListHead;
    while (currentFreeArea != nullptr) {
        // if the size of the free block can contain the request size and a rest HeapArea, then just use it, and split a new block
        if (currentFreeArea->size >= allocSize) {
            // 1. split a rest free HeapArea
            uint32_t newFreeHeapAreaAddress = (uint32_t) (void *) currentFreeArea + sizeof(HeapArea) + size;
            uint32_t restSize = currentFreeArea->size - allocSize;

            HeapArea *newFreeArea = newFreeHeapAreaAddress;
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
            HeapArea *usingArea = usingListHead;
            if (usingArea == nullptr) {
                usingListHead = currentFreeArea;
            } else {
                while (usingArea->list.next != nullptr) {
                    usingArea = getNode(usingArea->list.next, HeapArea, list);
                }
                usingArea->list.next = &currentFreeArea->list;
                currentFreeArea->list.prev = &usingArea->list;
            }

            // 4. return the ptr of the using block
            void *ptr = (void *) currentFreeArea + sizeof(HeapArea);
            if (heapFreeFunc == nullptr) {
                default_heap_alloc_func(ptr, size);
                return ptr;
            }
            heapAllocFunc(ptr, size);
            return ptr;
        }
        currentFreeArea = getNode(currentFreeArea->list.next, HeapArea, list);
        // no free block found ,it's means we must do some memory defragmentation
        // todo: defragmentation
    }
    return nullptr;
}

void *kernel_heap_calloc(uint32_t num, uint32_t size) {
    return kernel_heap_alloc(num * size);
}

void *kernel_heap_realloc(void *ptr, uint32_t size) {
    // 1. alloc new heap area
    void *newHeapArea = heap_alloc(size);

    // 2. copy the data from old heap area to new heap area
    HeapArea *oldHeapArea = ptr - sizeof(HeapArea);
    uint32_t dataSize = oldHeapArea->size;
    memcpy(newHeapArea, ptr, dataSize);

    // 3. free old heap area
    kernel_heap_free(ptr);
    return newHeapArea + sizeof(HeapArea);
}

void kernel_heap_free(void *ptr) {
    // 1. get HeapArea address
    uint32_t address = ptr - sizeof(HeapArea);
    HeapArea *currentArea = address;

    // 2. unlink from using list
    if (currentArea->list.prev != nullptr) {
        currentArea->list.prev->next = currentArea->list.next;
    }
    if (currentArea->list.next != nullptr) {
        currentArea->list.next->prev = currentArea->list.prev;
    }

    // 3. link this to free list
    HeapArea *freeArea = freeListHead;
    while (freeArea->list.next != nullptr) {
        freeArea = getNode(freeArea->list.next, HeapArea, list);
    }
    currentArea->list.prev = &freeArea->list;
    currentArea->list.next = freeArea->list.next;
    freeArea->list.next = &currentArea->list;
    if (heapFreeFunc == nullptr) {
        default_heap_free_func(ptr);
        return;
    }

    // do some merge stuff, between two adjacent free heap area
    HeapArea *firstFreeArea = freeListHead;
    while (firstFreeArea->list.next != nullptr) {
        firstFreeArea = getNode(firstFreeArea->list.next, HeapArea, list);
        HeapArea *secondFreeArea = firstFreeArea;
        while (secondFreeArea->list.next != nullptr) {
            secondFreeArea = getNode(secondFreeArea->list.next, HeapArea, list);

            // check is adjacent free heap area
            if(firstFreeArea+sizeof(HeapArea)+firstFreeArea->size == secondFreeArea){

                // resize the first heap area
                firstFreeArea->size = firstFreeArea->size+sizeof(HeapArea)+secondFreeArea->size;
                firstFreeArea->list.next = secondFreeArea->list.next;
                secondFreeArea->list.next->prev->next = &firstFreeArea->list;

                // delink the second heap area
                secondFreeArea->list.prev = nullptr;
                secondFreeArea->list.next = nullptr;
                secondFreeArea->size = 0;
            }
        }
    }

    heapFreeFunc(ptr);
}
