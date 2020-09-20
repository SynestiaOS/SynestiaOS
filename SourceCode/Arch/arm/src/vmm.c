//
// Created by XingfengYang on 2020/6/15.
//

#include "vmm.h"
#include "kernel_vmm.h"
#include "mmu.h"
#include "page.h"
#include <log.h>
#include <sched.h>
#include <stdlib.h>
#include <type.h>

void virtual_memory_default_allocate_page(VirtualMemory* virtualMemory, uint32_t virtualAddress)
{
    uint32_t l1Offset = (virtualAddress >> 30) & 0b11;
    uint32_t l2Offset = (virtualAddress >> 21) & 0b111111111;
    uint32_t l3Offset = (virtualAddress >> 12) & 0b111111111;
    uint32_t pageOffset = virtualAddress & 0xFFF;

    LogError("[vmm]:usr l1Offset: %d .\n", l1Offset);
    LogError("[vmm]:usr l2Offset: %d .\n", l2Offset);
    LogError("[vmm]:usr l3Offset: %d .\n", l3Offset);
    LogError("[vmm]:usr pageOffset: %d .\n", pageOffset);

    PageTableEntry* level1PageTable = virtualMemory->pageTable;
    PageTableEntry level1PageTableEntry = level1PageTable[l1Offset];
    if (level1PageTableEntry.valid == 0) {
        // level 1 page table entry not set.
        uint64_t l2ptPage = virtualMemory->physicalPageAllocator->operations.allocPage4K(
            virtualMemory->physicalPageAllocator, USAGE_PAGE_TABLE);

        level1PageTableEntry.valid = 1;
        level1PageTableEntry.table = 1;
        level1PageTableEntry.af = 1;
        level1PageTableEntry.base = l2ptPage;

        uint64_t ptPage = virtualMemory->physicalPageAllocator->operations.allocPage4K(
            virtualMemory->physicalPageAllocator,
            USAGE_PAGE_TABLE);

        PageTableEntry* l2pt = (PageTableEntry*)virtualMemory->physicalPageAllocator->base + l2ptPage * PAGE_SIZE;

        l2pt[0].valid = 1;
        l2pt[0].table = 1;
        l2pt[0].af = 1;
        l2pt[0].base = ptPage;

        PageTableEntry* pt = (PageTableEntry*)virtualMemory->physicalPageAllocator->base + ptPage * PAGE_SIZE;

        pt[0].valid = 1;
        pt[0].table = 1;
        pt[0].af = 1;
        pt[0].base = (uint64_t)(virtualMemory->physicalPageAllocator->operations.allocPage4K(
            virtualMemory->physicalPageAllocator, USAGE_NORMAL));

    } else {
        PageTableEntry* level2PageTable = (PageTableEntry*)(level1PageTableEntry.base >> VA_OFFSET);
        PageTableEntry level2PageTableEntry = level2PageTable[l2Offset];
        if (level2PageTableEntry.valid == 0) {
            //   level 2 page table entry not set.
            uint64_t ptPage = virtualMemory->physicalPageAllocator->operations.allocPage4K(
                virtualMemory->physicalPageAllocator, USAGE_PAGE_TABLE);

            level2PageTableEntry.valid = 1;
            level2PageTableEntry.table = 1;
            level2PageTableEntry.af = 1;
            level2PageTableEntry.base = ptPage;

            PageTableEntry* pt = (PageTableEntry*)virtualMemory->physicalPageAllocator->base + ptPage * PAGE_SIZE;

            pt[0].valid = 1;
            pt[0].table = 1;
            pt[0].af = 1;
            pt[0].base = (uint64_t)(virtualMemory->physicalPageAllocator->operations.allocPage4K(
                virtualMemory->physicalPageAllocator, USAGE_NORMAL));
        } else {
            PageTableEntry* pageTable = (PageTableEntry*)(level2PageTable->base >> VA_OFFSET);
            PageTableEntry pageTableEntry = pageTable[l3Offset];
            if (pageTableEntry.valid == 0) {
                // page table entry not set
                pageTableEntry.valid = 1;
                pageTableEntry.table = 1;
                pageTableEntry.af = 1;
                pageTableEntry.base = (uint64_t)(virtualMemory->physicalPageAllocator->operations.allocPage4K(
                    virtualMemory->physicalPageAllocator, USAGE_NORMAL));

            } else {
                // should not be there, if goto there, means it not a page fault exception
            }
        }
    }
}

void virtual_memory_default_mapping_page(VirtualMemory* virtualMemory, uint32_t virtualAddress,
    uint32_t physicalAddress)
{
    // TODO:
}

void virtual_memory_default_enable(VirtualMemory* virtualMemory)
{
    write_ttbcr(CONFIG_ARM_LPAE << 31);
    LogInfo("[vmm]: ttbcr writed\n");

    write_ttbr0((uint32_t)virtualMemory->pageTable);
    LogInfo("[vmm]: ttbr0 writed\n");

    write_dacr(0x55555555);
    LogInfo("[vmm]: dacr writed\n");

    mmu_enable();
    LogInfo("[vmm]: vmm enabled\n");
}

void virtual_memory_default_disable(VirtualMemory* virtualMemory) { mmu_disable(); }

void virtual_memory_default_release(VirtualMemory* virtualMemory)
{
    // TODO: release physical pages for page table when thread was fucking killed.
}

void virtual_memory_default_context_switch(VirtualMemory* old, VirtualMemory* new)
{
    // TODO: switch page table when thread switch
}

uint32_t virtual_memory_default_translate_to_physical(struct VirtualMemory* virtualMemory, uint32_t address)
{
    // calculate the physical address of buffer
    uint32_t l1Offset = address >> 30 & 0b11;
    uint32_t l2Offset = address >> 21 & 0b111111111;
    uint32_t l3Offset = address >> 12 & 0b111111111;
    uint32_t pageOffset = address & 0xFFF;

    PageTableEntry l1pte = virtualMemory->pageTable[l1Offset];
    PageTableEntry* level2PageTable = (PageTableEntry*)(l1pte.base << VA_OFFSET);
    PageTableEntry l2pte = level2PageTable[l2Offset];
    PageTableEntry* pageTable = (PageTableEntry*)(l2pte.base << VA_OFFSET);
    PageTableEntry pageTableEntry = pageTable[l3Offset];

    uint32_t physicalPageAddress = pageTableEntry.base;

    return physicalPageAddress + pageOffset;
}

uint32_t virtual_memory_default_get_user_str_len(struct VirtualMemory* virtualMemory, void* str)
{
    uint32_t len = 0;
    uint32_t userAddress = (uint32_t)str;
    while (*(char*)(virtualMemory->operations.translateToPhysical(virtualMemory, userAddress)) != '\0') {
        len++;
        userAddress++;
    }
    return len;
}

void* virtual_memory_default_copy_to_kernel(struct VirtualMemory* virtualMemory, char* src, char* dest, uint32_t size)
{

    // TODO: copy buffer from user space vmm to kernel space
    for (uint32_t i = 0; i < size; i++) {
        dest[i] = *(char*)(virtualMemory->operations.translateToPhysical(virtualMemory, (uint32_t)src + i));
    }
}

KernelStatus vmm_create(VirtualMemory* virtualMemory, PhysicalPageAllocator* physicalPageAllocator)
{
    virtualMemory->operations.mappingPage = virtual_memory_default_mapping_page;
    virtualMemory->operations.contextSwitch = virtual_memory_default_context_switch;
    virtualMemory->operations.allocatePage = virtual_memory_default_allocate_page;
    virtualMemory->operations.release = virtual_memory_default_release;
    virtualMemory->operations.enable = virtual_memory_default_enable;
    virtualMemory->operations.disable = virtual_memory_default_disable;
    virtualMemory->operations.copyToKernel = virtual_memory_default_copy_to_kernel;
    virtualMemory->operations.translateToPhysical = virtual_memory_default_translate_to_physical;
    virtualMemory->operations.getUserStrLen = virtual_memory_default_get_user_str_len;

    virtualMemory->physicalPageAllocator = physicalPageAllocator;

    /**
   * if lpaeSupport = 5, means LPAE is supported
   */
    uint32_t lpaeSupport = (read_mmfr0() & 0xF);
    LogWarn("[LPAE]: mmfr0: %d\n", lpaeSupport);

    uint64_t l1ptPage = virtualMemory->physicalPageAllocator->operations.allocPage4K(
        virtualMemory->physicalPageAllocator,
        USAGE_PAGE_TABLE);
    PageTableEntry* l1pt = (PageTableEntry*)virtualMemory->physicalPageAllocator->base + l1ptPage * PAGE_SIZE;

    uint64_t l2ptPage = virtualMemory->physicalPageAllocator->operations.allocPage4K(
        virtualMemory->physicalPageAllocator,
        USAGE_PAGE_TABLE);
    PageTableEntry* l2pt = (PageTableEntry*)virtualMemory->physicalPageAllocator->base + l2ptPage * PAGE_SIZE;

    uint64_t ptPage = virtualMemory->physicalPageAllocator->operations.allocPage4K(virtualMemory->physicalPageAllocator,
        USAGE_PAGE_TABLE);
    PageTableEntry* pt = (PageTableEntry*)virtualMemory->physicalPageAllocator->base + ptPage * PAGE_SIZE;

    pt[0].valid = 1;
    pt[0].table = 1;
    pt[0].af = 1;
    pt[0].base = (uint64_t)(
        virtualMemory->physicalPageAllocator->operations.allocPage4K(virtualMemory->physicalPageAllocator,
            USAGE_NORMAL));

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

void do_page_fault(uint32_t address)
{
    LogError("[vmm]: page fault at: %d .\n", address);
    // check is there is a thread running, if it was, then map for thread's vmm:
    // TODO: it not good, may be make some mistake when thread is running and kernel triggered this.
    Thread* currThread = schd_get_current_thread();
    if (currThread != nullptr) {
        // may be user triggered this
        VirtualMemory virtualMemory = currThread->memoryStruct.virtualMemory;
        virtualMemory.operations.allocatePage(&virtualMemory, address);
    } else {
        // kernel triggered this
        kernel_vmm_map(address);
    }
}
