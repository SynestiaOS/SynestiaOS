//
// Created by XingfengYang on 2020/6/12.
//

#include <kheap.h>
#include <log.h>
#include <page.h>
#include <stdlib.h>

static heap_alloc_func heapAllocFunc = nullptr;
static heap_free_func heapFreeFunc = nullptr;

HeapArea *usingListHead;
HeapArea *freeListHead;

#define ALL_PHYSICAL_MEM_SIZE 0xFFFFFFFF
#define ALL_KERNEL_HEAP_MEM_SIZE 96*MB

void default_heap_alloc_func(void *ptr, uint32_t size) {
  LogInfo("[Heap]: alloc %d bytes at %d.\n", size, (uint32_t)ptr);
}

void default_heap_free_func(void *ptr) {
  HeapArea *heap = (HeapArea *)(ptr - sizeof(HeapArea));
  LogInfo("[Heap]: free %d bytes at %d.\n", heap->size, (uint32_t)ptr);
}

void kheap_set_alloc_callback(heap_alloc_func callback) { heapAllocFunc = callback; }

void kheap_set_free_callback(heap_free_func callback) { heapFreeFunc = callback; }

KernelStatus kheap_init() {
  kheap_set_alloc_callback(default_heap_alloc_func);
  kheap_set_free_callback(default_heap_free_func);

  uint32_t heapAddress = (uint32_t)&__HEAP_BEGIN;
  LogInfo("[KHeap] end bss at: %d. \n", heapAddress);

  uint32_t heapPhysicalPage =
      (uint32_t)page_alloc_huge_at(USAGE_KERNEL_HEAP, (heapAddress | 4 * KB) >> VA_OFFSET, 128 * MB - heapAddress);
  LogInfo("[KHeap] alloc heap page: %d. \n", (uint32_t)heapPhysicalPage);

  heapAddress = KERNEL_PHYSICAL_START + heapPhysicalPage * PAGE_SIZE;
  LogInfo("[KHeap] kheap at: %d. \n", heapAddress);

  freeListHead = (HeapArea *)heapAddress;
  freeListHead->size = 0;
  freeListHead->list.prev = nullptr;

  HeapArea *freeArea = (HeapArea *)(heapAddress + sizeof(HeapArea));
  freeArea->size = (ALL_KERNEL_HEAP_MEM_SIZE - (uint32_t)(char *)heapAddress - 2 * sizeof(HeapArea)); // all memory
  freeListHead->list.next = &freeArea->list;
  freeArea->list.next = nullptr;
  freeArea->list.prev = &freeListHead->list;

  usingListHead = nullptr;

  return OK;
}

void *kheap_alloc(uint32_t size) {
  uint32_t allocSize = size + sizeof(HeapArea);

  if (freeListHead == nullptr) {
    LogError("[KHeap]: failed to get freeListHead.\n");
    return nullptr;
  }

  HeapArea *currentFreeArea = freeListHead;
  while (currentFreeArea != nullptr) {
    // if the size of the free block can contain the request size and a rest HeapArea,
    // then just use it, and split a new block
    if (currentFreeArea->size >= allocSize) {
      // 1. split a rest free HeapArea
      uint32_t newFreeHeapAreaAddress = (uint32_t)(void *)currentFreeArea + sizeof(HeapArea) + size;
      uint32_t restSize = currentFreeArea->size - allocSize;

      HeapArea *newFreeArea = (HeapArea *)newFreeHeapAreaAddress;
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
      void *ptr = (void *)currentFreeArea + sizeof(HeapArea);
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

void *kheap_alloc_aligned(uint32_t size, uint32_t alignment) {
  uint32_t offset = alignment - 1 + sizeof(void *);
  void *p1 = kheap_alloc(size + offset);
  if (p1 == nullptr) {
    return nullptr;
  }
  void **p2 = (void **)(((uint32_t)p1 + offset) & ~(alignment - 1));
  p2[-1] = p1;
  return p2;
}

void *kheap_calloc(uint32_t num, uint32_t size) { return kheap_alloc(num * size); }

void *kheap_realloc(void *ptr, uint32_t size) {
  // 1. alloc new heap area
  void *newHeapArea = kheap_alloc(size);
  if (newHeapArea == nullptr) {
    LogError("[heap] alloc mem failed when realloc.\n");
    return;
  }

  // 2. copy the data from old heap area to new heap area
  HeapArea *oldHeapArea = ptr - sizeof(HeapArea);
  uint32_t dataSize = oldHeapArea->size;
  memcpy(newHeapArea, ptr, dataSize);

  // 3. free old heap area
  KernelStatus freeStatus = kheap_free(ptr);
  if (freeStatus != OK) {
    LogError("[heap] free old mem failed when realloc.\n");
  }
  return newHeapArea;
}

KernelStatus kheap_free(void *ptr) {
  // 1. get HeapArea address
  uint32_t address = (uint32_t)(ptr - sizeof(HeapArea));
  HeapArea *currentArea = (HeapArea *)address;

  // 2. unlink from using list
  if (currentArea->list.prev != nullptr) {
    currentArea->list.prev->next = currentArea->list.next;
  }

  if (currentArea->list.next != nullptr && currentArea->list.prev != nullptr) {
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

  // do some merge stuff, between two adjacent free heap area
  HeapArea *firstFreeArea = freeListHead;
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
      }
    }
  }

  if (heapFreeFunc == nullptr) {
    default_heap_free_func(ptr);
    ptr = nullptr;
    return OK;
  }

  heapFreeFunc(ptr);
  ptr = nullptr;
  return OK;
}
