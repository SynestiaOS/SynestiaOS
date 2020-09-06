//
// Created by XingfengYang on 2020/6/15.
//

#include <cache.h>
#include <log.h>
#include <page.h>
#include <stdlib.h>
#include <type.h>
#include <vmm.h>

void virtual_memory_default_allocate_page(VirtualMemory *virtualMemory, uint32_t virtualAddress) {
  // TODO:
}

void virtual_memory_default_mapping_page(VirtualMemory *virtualMemory, uint32_t virtualAddress,
                                         uint32_t physicalAddress) {
  // TODO:
}

void virtual_memory_default_enable(VirtualMemory *virtualMemory) {
  write_ttbcr(CONFIG_ARM_LPAE << 31);
  LogInfo("[vmm]: ttbcr writed\n");

  write_ttbr0((uint32_t)virtualMemory->pageTable);
  LogInfo("[vmm]: ttbr0 writed\n");

  write_dacr(0x55555555);
  LogInfo("[vmm]: dacr writed\n");

  mmu_enable();
  LogInfo("[vmm]: vmm enabled\n");
}

void virtual_memory_default_disable(VirtualMemory *virtualMemory) { mmu_disable(); }

void virtual_memory_default_release(VirtualMemory *virtualMemory) {
  // TODO: release physical pages for page table when thread was fucking killed.
}

void virtual_memory_default_context_switch(VirtualMemory *old, VirtualMemory *new) {
  // TODO: switch page table when thread switch
}

void *virtual_memory_default_copy_to_kernel(struct VirtualMemory *virtualMemory, char *buffer, uint32_t size) {
  // calculate the physical address of buffer
  uint32_t l1Offset = (uint32_t)buffer >> 30 & 0b11;
  uint32_t l2Offset = (uint32_t)buffer >> 21 & 0b111111111;
  uint32_t l3Offset = (uint32_t)buffer >> 12 & 0b111111111;
  uint32_t pageOffset = (uint32_t)buffer & 0xFFF;

  PageTableEntry l1pte = virtualMemory->pageTable[l1Offset];
  PageTableEntry *level2PageTable = (PageTableEntry *)(l1pte.base << VA_OFFSET);
  PageTableEntry l2pte = level2PageTable[l2Offset];
  PageTableEntry *pageTable = (PageTableEntry *)(l2pte.base << VA_OFFSET);
  PageTableEntry pageTableEntry = pageTable[l3Offset];

  uint32_t physicalPageAddress = pageTableEntry.base;

  // TODO: copy buffer from user space vmm to kernel space
}

KernelStatus vmm_create(VirtualMemory *virtualMemory, PhysicalPageAllocator *physicalPageAllocator) {
  virtualMemory->operations.mappingPage = virtual_memory_default_mapping_page;
  virtualMemory->operations.contextSwitch = virtual_memory_default_context_switch;
  virtualMemory->operations.allocatePage = virtual_memory_default_allocate_page;
  virtualMemory->operations.release = virtual_memory_default_release;
  virtualMemory->operations.enable = virtual_memory_default_enable;
  virtualMemory->operations.disable = virtual_memory_default_disable;
  virtualMemory->operations.copyToKernel = virtual_memory_default_copy_to_kernel;

  virtualMemory->physicalPageAllocator = physicalPageAllocator;

  /**
   * if lpaeSupport = 5, means LPAE is supported
   */
  uint32_t lpaeSupport = (read_mmfr0() & 0xF);
  LogWarn("[LPAE]: mmfr0: %d\n", lpaeSupport);

  uint64_t l1ptPage = virtualMemory->physicalPageAllocator->operations.allocPage4K(virtualMemory->physicalPageAllocator,
                                                                                   USAGE_PAGE_TABLE);
  PageTableEntry *l1pt = (PageTableEntry *)virtualMemory->physicalPageAllocator->base + l1ptPage * PAGE_SIZE;

  uint64_t l2ptPage = virtualMemory->physicalPageAllocator->operations.allocPage4K(virtualMemory->physicalPageAllocator,
                                                                                   USAGE_PAGE_TABLE);
  PageTableEntry *l2pt = (PageTableEntry *)virtualMemory->physicalPageAllocator->base + l2ptPage * PAGE_SIZE;

  uint64_t ptPage = virtualMemory->physicalPageAllocator->operations.allocPage4K(virtualMemory->physicalPageAllocator,
                                                                                 USAGE_PAGE_TABLE);
  PageTableEntry *pt = (PageTableEntry *)virtualMemory->physicalPageAllocator->base + ptPage * PAGE_SIZE;

  pt[0].valid = 1;
  pt[0].table = 1;
  pt[0].af = 1;
  pt[0].base = (uint64_t)(
      virtualMemory->physicalPageAllocator->operations.allocPage4K(virtualMemory->physicalPageAllocator, USAGE_NORMAL));

  l2pt[0].valid = 1;
  l2pt[0].table = 1;
  l2pt[0].af = 1;
  l2pt[0].base = ptPage;

  l1pt[0].valid = 1;
  l1pt[0].table = 1;
  l1pt[0].af = 1;
  l1pt[0].base = l2ptPage;

  virtualMemory->pageTable = l1pt;

  return OK;
}

void do_page_fault(uint32_t address) {
  LogError("[vmm]: page fault at: %d .\n", address);

  uint32_t l1Offset = address >> 30 & 0b11;
  uint32_t l2Offset = address >> 21 & 0b111111111;
  uint32_t l3Offset = address >> 12 & 0b111111111;
  uint32_t pageOffset = address & 0xFFF;

  // check is thread not map vm
  LogError("[vmm]: l1Offset: %d .\n", l1Offset);
  LogError("[vmm]: l2Offset: %d .\n", l2Offset);
  LogError("[vmm]: l3Offset: %d .\n", l3Offset);
  LogError("[vmm]: pageOffset: %d .\n", pageOffset);

  // alloc physical for page table and map the address
}
