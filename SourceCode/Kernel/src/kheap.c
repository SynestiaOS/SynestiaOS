//
// Created by XingfengYang on 2020/6/12.
//

#include <kheap.h>

static heap_alloc_func heapAllocFunc;
static heap_free_func heapFreeFunc;

static HeapArea *usingListHead;
static HeapArea *freeListHead;

void heap_set_alloc_callback(heap_alloc_func callback) {
    heapAllocFunc = callback;
}

void heap_set_free_callback(heap_free_func callback) {
    heapFreeFunc = callback;
}

void heap_init() {
    freeListHead = heap_begin;
    freeListHead->size = 0;
    freeListHead->list.prev = nullptr;

    HeapArea *freeArea = heap_begin+sizeof(HeapArea);
    freeArea->size = (0xFFFFFFFF - (uint32_t) (char *) heap_begin - 2*sizeof(HeapArea)); // all memory
    freeListHead->list.next = &freeArea->list;
    freeArea->list.next = nullptr;
    freeArea->list.prev = &freeListHead->list;

    usingListHead = nullptr;
}

void *heap_alloc(uint32_t size) {
    uint32_t allocSize = size + sizeof(HeapArea);

    HeapArea *currentFreeArea = freeListHead;
    while (currentFreeArea != nullptr) {
        // if the size of the free block can contain the request size and a rest HeapArea, then just use it, and split a new block
        if (currentFreeArea->size >= allocSize) {
            // 1. split a rest free HeapArea
            uint32_t newFreeHeapAreaAddress = (uint32_t)(void*)currentFreeArea + sizeof(HeapArea)+size;
            uint32_t restSize = currentFreeArea->size - allocSize;

            HeapArea *newFreeArea = newFreeHeapAreaAddress;
            newFreeArea->size = restSize;


            // 2.link new free heap area to free list
            newFreeArea->list.prev = currentFreeArea->list.prev;
            newFreeArea->list.next = currentFreeArea->list.next;
            currentFreeArea->list.prev->next = &newFreeArea->list;
            if(currentFreeArea->list.next!=nullptr){
                currentFreeArea->list.next->prev = &newFreeArea->list;
            }

            // 3. link this to using list
            currentFreeArea->list.prev = nullptr;
            currentFreeArea->list.next = nullptr;
            currentFreeArea->size = size;
            HeapArea *usingArea = usingListHead;
            if(usingArea==nullptr){
                usingListHead = currentFreeArea;
            }else{
                while(usingArea->list.next!=nullptr){
                    usingArea = getNode(usingArea->list.next,HeapArea,list);
                }
                usingArea->list.next = &currentFreeArea->list;
                currentFreeArea->list.prev = &usingArea->list;
            }

            // 4. return the ptr of the using block
            void *ptr = (void *)currentFreeArea+sizeof(HeapArea);
            heapAllocFunc(ptr,size);
            return ptr;
        }
        currentFreeArea = getNode(currentFreeArea->list.next,HeapArea ,list);
        // no free block found ,it's means we must do some memory defragmentation
        // todo: defragmentation
    }


}

void *heap_calloc(uint32_t num, uint32_t size) {
    return heap_alloc(num*size);
}

void *heap_realloc(void *ptr, uint32_t size) {
    //todo : a bit complex
}

void heap_free(void *ptr) {
    // 1. get HeapArea address
    uint32_t  address = ptr-sizeof(HeapArea);
    HeapArea *currentArea = address;

    // 2. unlink from using list
    if(currentArea->list.prev!=nullptr) {
        currentArea->list.prev->next = currentArea->list.next;
    }
    if(currentArea->list.next!=nullptr){
        currentArea->list.next->prev = currentArea->list.prev;
    }

    // 3. link this to free list
    HeapArea *freeArea = freeListHead;
    while (freeArea->list.next != nullptr) {
        freeArea = getNode(freeArea->list.next,HeapArea ,list);
    }
    currentArea->list.prev = &freeArea->list;
    currentArea->list.next = freeArea->list.next;
    freeArea->list.next = &currentArea->list;

    heapFreeFunc(ptr);
}
