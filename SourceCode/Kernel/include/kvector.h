//
// Created by XingfengYang on 2020/7/10.
//

#ifndef __KERNEL_VECTOR_H__
#define __KERNEL_VECTOR_H__

#include "list.h"
#include <stdbool.h>
#include <type.h>

#define DEFAULT_VECTOR_SIZE 12

typedef KernelStatus (*KernelVectorOperationResize)(struct KernelVector *vector, uint32_t newSize);
typedef KernelStatus (*KernelVectorOperationFree)(struct KernelVector *vector);
typedef KernelStatus (*KernelVectorOperationAdd)(struct KernelVector *vector, ListNode *node);
typedef ListNode *(*KernelVectorOperationGet)(struct KernelVector *vector, uint32_t index);
typedef KernelStatus (*KernelVectorOperationRemove)(struct KernelVector *vector, ListNode *node);
typedef KernelStatus (*KernelVectorOperationRemoveIndex)(struct KernelVector *vector, uint32_t index);
typedef uint32_t (*KernelVectorOperationSize)(struct KernelVector *vector);
typedef bool (*KernelVectorOperationIsEmpty)(struct KernelVector *vector);
typedef bool (*KernelVectorOperationIsFull)(struct KernelVector *vector);
typedef KernelStatus (*KernelVectorOperationClear)(struct KernelVector *vector);

typedef struct KernelVectorOperations {
  KernelVectorOperationResize resize;
  KernelVectorOperationFree free;
  KernelVectorOperationAdd add;
  KernelVectorOperationGet get;
  KernelVectorOperationRemove remove;
  KernelVectorOperationRemoveIndex removeIndex;
  KernelVectorOperationSize size;
  KernelVectorOperationIsEmpty isEmpty;
  KernelVectorOperationIsFull isFull;
  KernelVectorOperationClear clear;
} KernelVectorOperations;

typedef struct KernelVector {
  uint32_t size;
  ListNode **node;
  uint32_t index;
} __attribute__((packed)) KernelVector;

KernelVector *kvector_allocate();

KernelStatus kvector_resize(KernelVector *vector, uint32_t newSize);

KernelStatus kvector_free(KernelVector *vector);

KernelStatus kvector_add(KernelVector *vector, ListNode *node);

ListNode *kvector_get(KernelVector *vector, uint32_t index);

KernelStatus kvector_remove_index(KernelVector *vector, uint32_t index);

KernelStatus kvector_remove(KernelVector *vector, ListNode *index);

uint32_t kvector_size(KernelVector *vector);

bool kvector_is_empty(KernelVector *vector);

bool kvector_is_full(KernelVector *vector);

KernelStatus kvector_clear(KernelVector *vector);

#endif //__KERNEL_VECTOR_H__
