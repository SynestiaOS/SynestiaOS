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
    freeList->size = 0;
    freeList->list.prev = nullptr;
    freeList->list.next = nullptr;
    freeList->ptr = nullptr;
    usingList = nullptr;
}

void *heap_alloc(uint32_t size) {
    uint32_t allocSize = size + sizeof(HeapArea);

    List *begin = freeList->list.next;
    while (begin != nullptr) {
        begin = begin->next;
    }

}

void *heap_calloc(uint32_t num, uint32_t size) {

}

void *heap_realloc(void *ptr, uint32_t size) {

}

void heap_free(void *ptr) {

}
