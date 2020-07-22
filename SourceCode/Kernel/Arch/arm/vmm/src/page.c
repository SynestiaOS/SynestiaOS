//
// Created by XingfengYang on 2020/7/15.
//
#include <page.h>
#include <type.h>
#include <log.h>

#define PHYSICAL_PAGE_NUMBERS (1 << 20)

PhysicalPage physicalPages[PHYSICAL_PAGE_NUMBERS] = {'\0'};
uint32_t physicalPagesUsedBitMap[PHYSICAL_PAGE_NUMBERS / BITS_IN_UINT32]  = {'\0'};

uint64_t page_alloc(PhysicalPageUsage usage) {
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

void page_mark_as_free(uint64_t pageIndex) {
  uint32_t index = pageIndex / BITS_IN_UINT32;
  uint8_t bitIndex = pageIndex % BITS_IN_UINT32;

  physicalPagesUsedBitMap[index] ^= (uint32_t)0x1 << bitIndex;
}

void page_mark_as_used(uint64_t pageIndex) {
  uint32_t index = pageIndex / BITS_IN_UINT32;
  uint8_t bitIndex = pageIndex % BITS_IN_UINT32;

  physicalPagesUsedBitMap[index] |= (uint32_t)0x1 << bitIndex;
}

uint64_t page_free(uint64_t pageIndex) {
  if (physicalPages[pageIndex].ref_count > 0) {
    physicalPages[pageIndex].ref_count -= 1;

    page_mark_as_free(pageIndex);

    return pageIndex;
  }
}

uint64_t page_alloc_huge_at(PhysicalPageUsage usage, uint64_t page, uint64_t size) {
  for (uint32_t pageOffset = 0; pageOffset < size / (4 * KB); pageOffset++) {
    uint64_t pageIndex = page + pageOffset;
    physicalPages[pageIndex].ref_count += 1;
    physicalPages[pageIndex].type = PAGE_2M;
    physicalPages[pageIndex].usage = usage;

    page_mark_as_used(pageIndex);
  }
  return page;
}

uint64_t page_free_huge(uint64_t page, uint64_t size) {
  for (uint32_t pageOffset = 0; pageOffset < size / (4 * KB); pageOffset++) {
    uint64_t pageIndex = page + pageOffset;
    page_free(pageIndex);
  }
  return page;
}
