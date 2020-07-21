//
// Created by XingfengYang on 2020/7/15.
//
#include <page.h>
#include <type.h>

#define PHYSICAL_PAGE_NUMBERS (1 << 20)

PhysicalPage physicalPages[PHYSICAL_PAGE_NUMBERS];
uint32_t physicalPagesUsedBitMap[PHYSICAL_PAGE_NUMBERS / BITS_IN_UINT32];

uint64_t vmm_alloc_page(PhysicalPageUsage usage) {
  for (uint32_t i = 0; i < PHYSICAL_PAGE_NUMBERS / BITS_IN_UINT32; i++) {
    if (physicalPagesUsedBitMap[i] != MAX_UINT_32) {
      for (uint8_t j = 0; j < BITS_IN_UINT32; j++) {
        if ((physicalPagesUsedBitMap[i] & ((uint32_t)0x1 << j)) == 0) {
          physicalPages[i * BITS_IN_UINT32 + j].ref_count += 1;
          physicalPages[i * BITS_IN_UINT32 + j].type = PAGE_4K;
          physicalPages[i * BITS_IN_UINT32 + j].usage = usage;
          physicalPagesUsedBitMap[i] |= (uint32_t)0x1 << j;
          return i * BITS_IN_UINT32 + j;
        }
      }
    }
  }
}

uint64_t vmm_free_page(uint64_t pageIndex) {
  if (physicalPages[pageIndex].ref_count > 0) {
    physicalPages[pageIndex].ref_count -= 1;

    uint32_t index = pageIndex / BITS_IN_UINT32;
    uint8_t bitIndex = pageIndex % BITS_IN_UINT32;

    physicalPagesUsedBitMap[index] ^= (uint32_t)0x1 << bitIndex;
    return pageIndex;
  }
}

uint64_t vmm_alloc_huge_page_at(PhysicalPageUsage usage, uint64_t page, uint64_t size) {
  for (uint32_t pageOffset = 0; pageOffset < size / (4 * KB); pageOffset++) {
    physicalPages[page + pageOffset].ref_count += 1;
    physicalPages[page + pageOffset].type = PAGE_2M;
    physicalPages[page + pageOffset].usage = usage;

    uint32_t index = (page + pageOffset) / BITS_IN_UINT32;
    uint8_t bitIndex = (page + pageOffset) % BITS_IN_UINT32;

    physicalPagesUsedBitMap[index] |= (uint32_t)0x1 << bitIndex;
  }
  return page;
}

uint64_t vmm_free_huge_page(uint64_t page, uint64_t size) {
  for (uint32_t pageOffset = 0; pageOffset < size / (4 * KB); pageOffset++) {
    vmm_free_page(page + pageOffset);
  }
  return page;
}