//
// Created by XingfengYang on 2020/7/10.
//
#include <kheap.h>
#include <kvector.h>
#include <stdlib.h>

KernelVector *kvector_allocate() {
  // 1. allocate vector memory block from virtual memory (heap), and align.
  KernelVector *vector = (KernelVector *)kheap_alloc(DEFAULT_VECTOR_SIZE * sizeof(ListNode *) + sizeof(KernelVector));
  if (vector == nullptr) {
    printf("[KVector] kVector allocate failed.\n");
    return nullptr;
  }
  vector->size = DEFAULT_VECTOR_SIZE;
  vector->index = 0;
  vector->node = (ListNode **)(vector + sizeof(KernelVector));
  return vector;
}

KernelStatus kvector_resize(KernelVector *vector, uint32_t newSize) {
  kheap_realloc(vector, newSize);
  vector->size = newSize;
  return OK;
}

KernelStatus kvector_free(KernelVector *vector) {
  kheap_free(vector);
  return OK;
}

KernelStatus kvector_add(KernelVector *vector, ListNode *node) {
  vector->node[vector->index] = node;
  vector->index++;
  return OK;
}

ListNode *kvector_get(KernelVector *vector, uint32_t index) { return vector->node[index]; }

KernelStatus kvector_remove_index(KernelVector *vector, uint32_t index) {}

KernelStatus kvector_remove(KernelVector *vector, ListNode *index) {}

bool kvector_is_empty(KernelVector *vector) { return vector->index == 0; }

bool kvector_is_full(KernelVector *vector) { return vector->index == vector->size; }

KernelStatus kvector_clear(KernelVector *vector) {
  vector->index = 0;
  for (uint32_t i = 0; i < vector->size; i++) {
    vector->node = nullptr;
  }
  return OK;
}
