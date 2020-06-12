//
// Created by XingfengYang on 2020/6/12.
//

#include <kheap.h>

static heap_alloc_func heapAllocFunc;
static heap_free_func heapFreeFunc;

static HeapArea *usingList;
static HeapArea *freeList;

void heap_set_alloc_callback(heap_alloc_func callback) {
    heapAllocFunc = callback;
}

void heap_set_free_callback(heap_free_func callback) {
    heapFreeFunc = callback;
}

void heap_init() {
    freeList = heap_begin;
    freeList->size = (0xFFFFFFFF - (uint32_t) (char *) heap_begin - sizeof(HeapArea)); // all memory
    freeList->list.prev = nullptr;
    freeList->list.next = nullptr;

    usingList = nullptr;
}

void *heap_alloc(uint32_t size) {
    uint32_t allocSize = size + sizeof(HeapArea);

    List *begin = freeList->list.next;
    while (begin != nullptr) {
        // if the size of the free block can contain the request size and a rest HeapArea, then just use it, and split a new block
        if (getNode(begin, HeapArea, list)->size - size >= sizeof(HeapArea)) {
            // 1. split a rest free HeapArea

            // 2. link this to using list

            // 3. link this rest free HeapArea to free list

            // 4. return the ptr of the using block
            break;
        }
        begin = begin->next;
        // no free block found ,let's fucking build a new
    }


}

void *heap_calloc(uint32_t num, uint32_t size) {

}

void *heap_realloc(void *ptr, uint32_t size) {

}

void heap_free(void *ptr) {

}
