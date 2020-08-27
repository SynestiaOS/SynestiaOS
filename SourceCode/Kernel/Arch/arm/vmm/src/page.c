//
// Created by XingfengYang on 2020/7/15.
//
#include <log.h>
#include <page.h>
#include <string.h>
#include <type.h>

PhysicalPage physicalPages[PHYSICAL_PAGE_NUMBERS] = {'\0'};
uint32_t physicalPagesUsedBitMap[PHYSICAL_PAGE_NUMBERS / BITS_IN_UINT32] = {'\0'};

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

////////////////////////
uint64_t physical_page_allocator_default_alloc_page_4k(PhysicalPageAllocator *pageAllocator, PhysicalPageUsage usage) {
  for (uint32_t i = 0; i < PHYSICAL_PAGE_NUMBERS / BITS_IN_UINT32; i++) {
    if (pageAllocator->physicalPagesUsedBitMap[i] != MAX_UINT_32) {
      for (uint8_t j = 0; j < BITS_IN_UINT32; j++) {
        if ((pageAllocator->physicalPagesUsedBitMap[i] & ((uint32_t)0x1 << j)) == 0) {
          pageAllocator->physicalPages[i * BITS_IN_UINT32 + j].ref_count += 1;
          pageAllocator->physicalPages[i * BITS_IN_UINT32 + j].type = PAGE_4K;
          pageAllocator->physicalPages[i * BITS_IN_UINT32 + j].usage = usage;
          pageAllocator->physicalPagesUsedBitMap[i] |= (uint32_t)0x1 << j;
          return i * BITS_IN_UINT32 + j;
        }
      }
    }
  }
}

uint64_t physical_page_allocator_default_free_page_4k(PhysicalPageAllocator *pageAllocator, uint64_t page) {
  if (pageAllocator->physicalPages[page].ref_count > 0) {
    pageAllocator->physicalPages[page].ref_count -= 1;

    page_mark_as_free(page);

    return page;
  }
}

uint64_t physical_page_allocator_default_alloc_page_4k_at(PhysicalPageAllocator *pageAllocator, PhysicalPageUsage usage,
                                                          uint64_t address) {

  uint32_t index = address / BITS_IN_UINT32;
  uint8_t bitIndex = address % BITS_IN_UINT32;
  if ((pageAllocator->physicalPagesUsedBitMap[index] & ((uint32_t)0x1 << bitIndex)) == 0) {
    pageAllocator->physicalPages[index * BITS_IN_UINT32 + bitIndex].ref_count += 1;
    pageAllocator->physicalPages[index * BITS_IN_UINT32 + bitIndex].type = PAGE_4K;
    pageAllocator->physicalPages[index * BITS_IN_UINT32 + bitIndex].usage = usage;
    pageAllocator->physicalPagesUsedBitMap[index] |= (uint32_t)0x1 << bitIndex;
    return index * BITS_IN_UINT32 + bitIndex;
  }
}

uint64_t physical_page_allocator_default_alloc_page_4k_mark_as_used(PhysicalPageAllocator *pageAllocator,
                                                                    uint64_t page) {
  uint32_t index = page / BITS_IN_UINT32;
  uint8_t bitIndex = page % BITS_IN_UINT32;

  pageAllocator->physicalPagesUsedBitMap[index] |= (uint32_t)0x1 << bitIndex;
}

uint64_t physical_page_allocator_default_alloc_page_4k_mark_as_free(PhysicalPageAllocator *pageAllocator,
                                                                    uint64_t page) {
  uint32_t index = page / BITS_IN_UINT32;
  uint8_t bitIndex = page % BITS_IN_UINT32;

  pageAllocator->physicalPagesUsedBitMap[index] ^= (uint32_t)0x1 << bitIndex;
}

uint64_t physical_page_allocator_default_alloc_page_2m(PhysicalPageAllocator *pageAllocator, PhysicalPageUsage usage) {}

uint64_t physical_page_allocator_default_free_page_2m(PhysicalPageAllocator *pageAllocator, uint64_t page) {}

uint64_t physical_page_allocator_default_alloc_page_2m_at(PhysicalPageAllocator *pageAllocator, PhysicalPageUsage usage,
                                                          uint64_t page) {}

void page_allocator_create(PhysicalPageAllocator *pageAllocator, uint32_t base, uint32_t size) {
  pageAllocator->size = size;
  pageAllocator->base = base;

  pageAllocator->operations.allocPage4K = physical_page_allocator_default_alloc_page_4k;
  pageAllocator->operations.allocPage2M = physical_page_allocator_default_alloc_page_2m;
  pageAllocator->operations.freePage4K = physical_page_allocator_default_free_page_4k;
  pageAllocator->operations.freePage2M = physical_page_allocator_default_free_page_2m;
  pageAllocator->operations.allocPage4KAt = physical_page_allocator_default_alloc_page_4k_at;
  pageAllocator->operations.allocPage2MAt = physical_page_allocator_default_alloc_page_2m_at;
  pageAllocator->operations.page4KMarkAsFree = physical_page_allocator_default_alloc_page_4k_mark_as_free;
  pageAllocator->operations.page4KMarkAsUsed = physical_page_allocator_default_alloc_page_4k_mark_as_used;

  memset(pageAllocator->physicalPages, 0, PHYSICAL_PAGE_NUMBERS * sizeof(uint32_t));
  memset(pageAllocator->physicalPagesUsedBitMap, 0, (PHYSICAL_PAGE_NUMBERS / BITS_IN_UINT32) * sizeof(uint32_t));
}
