//
// Created by XingfengYang on 2020/7/6.
//

#ifndef __KERNEL_KHEAP_TEST_H__
#define __KERNEL_KHEAP_TEST_H__

#include <kheap.h>

void should_kheap_init() {
  KernelStatus heapInitStatus = kheap_init();

  ASSERT_EQ(heapInitStatus, OK);
}

void should_kheap_alloc() {
  KernelStatus heapInitStatus = kheap_init();
  ASSERT_EQ(heapInitStatus, OK);

  uint32_t *values1 = (uint32_t *)kheap_alloc(5 * sizeof(uint32_t));
  values1[0] = 10;
  values1[1] = 11;
  values1[2] = 12;
  values1[3] = 13;
  values1[4] = 14;

  uint32_t *values2 = (uint32_t *)kheap_alloc(5 * sizeof(uint32_t));
  values2[0] = 20;
  values2[1] = 21;
  values2[2] = 22;
  values2[3] = 23;
  values2[4] = 24;

  ASSERT_EQ(values1[0], 10);
  ASSERT_EQ(values1[1], 11);
  ASSERT_EQ(values1[2], 12);
  ASSERT_EQ(values1[3], 13);
  ASSERT_EQ(values1[4], 14);

  ASSERT_EQ(values2[0], 20);
  ASSERT_EQ(values2[1], 21);
  ASSERT_EQ(values2[2], 22);
  ASSERT_EQ(values2[3], 23);
  ASSERT_EQ(values2[4], 24);
}

void should_kheap_calloc() {
  KernelStatus heapInitStatus = kheap_init();
  ASSERT_EQ(heapInitStatus, OK);

  uint32_t *values1 = (uint32_t *)kheap_calloc(5, sizeof(uint32_t));
  values1[0] = 10;
  values1[1] = 11;
  values1[2] = 12;
  values1[3] = 13;
  values1[4] = 14;

  uint32_t *values2 = (uint32_t *)kheap_calloc(5, sizeof(uint32_t));
  values2[0] = 20;
  values2[1] = 21;
  values2[2] = 22;
  values2[3] = 23;
  values2[4] = 24;

  ASSERT_EQ(values1[0], 10);
  ASSERT_EQ(values1[1], 11);
  ASSERT_EQ(values1[2], 12);
  ASSERT_EQ(values1[3], 13);
  ASSERT_EQ(values1[4], 14);

  ASSERT_EQ(values2[0], 20);
  ASSERT_EQ(values2[1], 21);
  ASSERT_EQ(values2[2], 22);
  ASSERT_EQ(values2[3], 23);
  ASSERT_EQ(values2[4], 24);
}

void should_kheap_realloc() {
  KernelStatus heapInitStatus = kheap_init();
  ASSERT_EQ(heapInitStatus, OK);

  uint32_t *values1 = (uint32_t *)kheap_calloc(5, sizeof(uint32_t));
  values1[0] = 10;
  values1[1] = 11;
  values1[2] = 12;
  values1[3] = 13;
  values1[4] = 14;
  ASSERT_EQ(values1[0], 10);
  ASSERT_EQ(values1[1], 11);
  ASSERT_EQ(values1[2], 12);
  ASSERT_EQ(values1[3], 13);
  ASSERT_EQ(values1[4], 14);

  values1 = (uint32_t *)kheap_realloc(values1, 6);
  values1[5] = 15;
  ASSERT_EQ(values1[5], 15);

  ASSERT_EQ(heapInitStatus, OK);
}

void should_kheap_free() {
  KernelStatus heapInitStatus = kheap_init();
  ASSERT_EQ(heapInitStatus, OK);

  uint32_t *values1 = (uint32_t *)kheap_calloc(1, sizeof(uint32_t));
  values1[0] = 10;
  ASSERT_EQ(values1[0], 10);

  KernelStatus heapFreeStatus = kheap_free(values1);
  ASSERT_EQ(heapFreeStatus, OK);
}

#endif //__KERNEL_KHEAP_TEST_H__
