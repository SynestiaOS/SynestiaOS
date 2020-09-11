//
// Created by XingfengYang on 2020/6/15.
//

#include <cache.h>
#include <kernel_vmm.h>
#include <log.h>
#include <page.h>
#include <stdlib.h>
#include <type.h>

extern int __PAGE_TABLE;
extern PhysicalPageAllocator kernelPageAllocator;

Level1PageTable* kernelVMML1PT;
Level2PageTable* kernelVMML2PT;
PageTable* kernelVMMPT;

void map_kernel_l1pt(uint64_t l1ptPhysicalAddress, uint64_t l2ptPhysicalAddress)
{
    kernelVMML1PT = (Level1PageTable*)l1ptPhysicalAddress;
    kernelVMML1PT->pte[0].valid = 1;
    kernelVMML1PT->pte[0].table = 1;
    kernelVMML1PT->pte[0].af = 1;
    kernelVMML1PT->pte[0].base = (uint32_t)l2ptPhysicalAddress >> VA_OFFSET;

    kernelVMML1PT->pte[1].valid = 1;
    kernelVMML1PT->pte[1].table = 1;
    kernelVMML1PT->pte[1].af = 1;
    kernelVMML1PT->pte[1].base = (uint32_t)((l2ptPhysicalAddress + 4 * KB) >> VA_OFFSET);
}

void map_kernel_l2pt(uint64_t l2ptPhysicalAddress, uint64_t ptPhysicalAddress)
{
    kernelVMML2PT = (Level2PageTable*)l2ptPhysicalAddress;
    for (uint32_t i = 0; i < KERNEL_PTE_NUMBER; i++) {
        kernelVMML2PT->pte[i].valid = 1;
        kernelVMML2PT->pte[i].table = 1;
        kernelVMML2PT->pte[i].af = 1;
        kernelVMML2PT->pte[i].base = (uint64_t)(ptPhysicalAddress + i * KERNEL_PTE_NUMBER * sizeof(PageTableEntry)) >> VA_OFFSET;
    }
    // Peripheral 16MB 0x3F000000
    for (uint32_t i = 0; i < 8; i++) {
        kernelVMML2PT->pte[504 + i].valid = 1;
        kernelVMML2PT->pte[504 + i].table = 0;
        kernelVMML2PT->pte[504 + i].af = 1;
        uint64_t physicalPageNumber = kernelPageAllocator.operations.allocHugeAt(
            &kernelPageAllocator, USAGE_PERIPHERAL, (0x3F000000 | (i * 2 * MB)) >> VA_OFFSET, 2 * MB);
        kernelVMML2PT->pte[504 + i].base = ((KERNEL_PHYSICAL_START + physicalPageNumber * PAGE_SIZE) & 0x000FFFFF000) >> VA_OFFSET;
    }

    // VideoBuffer 8M 0x3C100000
    for (uint32_t i = 0; i < 4; i++) {
        kernelVMML2PT->pte[480 + i].valid = 1;
        kernelVMML2PT->pte[480 + i].table = 0;
        kernelVMML2PT->pte[480 + i].af = 1;
        uint64_t physicalPageNumber = kernelPageAllocator.operations.allocHugeAt(
            &kernelPageAllocator, USAGE_FRAMEBUFFER, (0x3C000000 | (i * 2 * MB)) >> VA_OFFSET, 2 * MB);
        kernelVMML2PT->pte[480 + i].base = ((KERNEL_PHYSICAL_START + physicalPageNumber * PAGE_SIZE) & 0x000FFFFF000) >> VA_OFFSET;
    }

    // 2 level page table for second first page table
    Level2PageTable* secondL2PT = (Level2PageTable*)(l2ptPhysicalAddress + 4 * KB);
    secondL2PT->pte[0].valid = 1;
    secondL2PT->pte[0].table = 0;
    secondL2PT->pte[0].af = 1;
    uint64_t physicalPageNumber = kernelPageAllocator.operations.allocHugeAt(&kernelPageAllocator, USAGE_PAGE_TABLE,
        0x40000000 >> VA_OFFSET, 2 * MB);
    secondL2PT->pte[0].base = ((KERNEL_PHYSICAL_START + physicalPageNumber * PAGE_SIZE) & 0x000FFFFF000) >> VA_OFFSET;
}

void (*processHockFunc)(uint32_t process);

void kernel_vmm_add_map_hook(void (*func)(uint32_t process)) { processHockFunc = func; }

void map_kernel_pt(uint64_t ptPhysicalAddress)
{
    kernelVMMPT = (PageTable*)ptPhysicalAddress;
    uint32_t index = 0;
    for (uint32_t i = 0; i < KERNEL_L2PT_NUMBER; i++) {
        for (uint32_t j = 0; j < KERNEL_PTE_NUMBER; j++) {
            uint64_t physicalPageNumber = kernelPageAllocator.operations.allocPage4K(&kernelPageAllocator, USAGE_KERNEL);
            kernelVMMPT->pte[index].valid = 1;
            kernelVMMPT->pte[index].table = 1;
            kernelVMMPT->pte[index].af = 1;
            kernelVMMPT->pte[index].base = ((KERNEL_PHYSICAL_START + physicalPageNumber * PAGE_SIZE) & 0x000FFFFF000) >> VA_OFFSET;
            index++;
        }
        processHockFunc((i * 100) / KERNEL_L2PT_NUMBER);
    }
}

void map_kernel_mm()
{
    uint64_t pageTablePhysicalAddress = (uint64_t)&__PAGE_TABLE;

    uint64_t l1ptPhysicalAddress = pageTablePhysicalAddress;
    uint64_t l2ptPhysicalAddress = pageTablePhysicalAddress + 4 * KB;
    uint64_t ptPhysicalAddress = (l2ptPhysicalAddress + KERNEL_PTE_NUMBER * 4 * KB);

    map_kernel_l1pt(l1ptPhysicalAddress, l2ptPhysicalAddress);
    LogInfo("[vmm]: level 1 page table done\n");
    map_kernel_l2pt(l2ptPhysicalAddress, ptPhysicalAddress);
    LogInfo("[vmm]: level 2 page table done\n");
    map_kernel_pt(ptPhysicalAddress);
    LogInfo("[vmm]: page table done\n");
}

void kernel_vmm_init()
{
    mmu_disable();
    map_kernel_mm();

    /**
   * if lpaeSupport = 5, means LPAE is supported
   */
    uint32_t lpaeSupport = (read_mmfr0() & 0xF);
    LogWarn("[LPAE]: mmfr0: %d\n", lpaeSupport);

    kernel_vmm_enable();
}

void kernel_vmm_enable()
{
    write_ttbcr(CONFIG_ARM_LPAE << 31);
    LogInfo("[vmm]: ttbcr writed\n");

    write_ttbr0((uint32_t)kernelVMML1PT);
    LogInfo("[vmm]: ttbr0 writed\n");

    write_dacr(0x55555555);
    LogInfo("[vmm]: dacr writed\n");

    mmu_enable();
    LogInfo("[vmm]: vmm enabled\n");
}

PageTableEntry* kernel_vmm_get_page_table() { return (PageTableEntry*)kernelVMML1PT; }

void kernel_vmm_map(uint32_t virtualAddress)
{
    uint32_t l1Offset = virtualAddress >> 30 & 0b11;
    uint32_t l2Offset = virtualAddress >> 21 & 0b111111111;
    uint32_t l3Offset = virtualAddress >> 12 & 0b111111111;
    uint32_t pageOffset = virtualAddress & 0xFFF;

    LogError("[vmm]:kernel l1Offset: %d .\n", l1Offset);
    LogError("[vmm]:kernel l2Offset: %d .\n", l2Offset);
    LogError("[vmm]:kernel l3Offset: %d .\n", l3Offset);
    LogError("[vmm]:kernel pageOffset: %d .\n", pageOffset);

    if (kernelVMML1PT->pte[l1Offset].valid == 0) {
        uint64_t l2ptPage = kernelPageAllocator.operations.allocPage4KAt(
            &kernelPageAllocator,
            USAGE_PAGE_TABLE,
            ((uint32_t)kernelVMML2PT + l1Offset * 4 * KB + l2Offset * sizeof(struct PageTableEntry)) >> VA_OFFSET);

        kernelVMML1PT->pte[l1Offset].valid = 1;
        kernelVMML1PT->pte[l1Offset].table = 1;
        kernelVMML1PT->pte[l1Offset].af = 1;
        kernelVMML1PT->pte[l1Offset].base = l2ptPage;

        uint64_t ptPage = kernelPageAllocator.operations.allocPage4KAt(
            &kernelPageAllocator, USAGE_PAGE_TABLE,
            ((uint32_t)kernelVMMPT + l2Offset * 4 * KB + l3Offset * sizeof(struct PageTableEntry)) >> VA_OFFSET);

        PageTableEntry* l2pt = (PageTableEntry*)kernelPageAllocator.base + l2ptPage * PAGE_SIZE;

        // TODO: may cause page fault here.
        l2pt[0].valid = 1;
        l2pt[0].table = 1;
        l2pt[0].af = 1;
        l2pt[0].base = ptPage;

        PageTableEntry* pt = (PageTableEntry*)kernelPageAllocator.base + ptPage * PAGE_SIZE;

        pt[0].valid = 1;
        pt[0].table = 1;
        pt[0].af = 1;
        pt[0].base = (uint64_t)(kernelPageAllocator.operations.allocPage4KAt(
            &kernelPageAllocator, USAGE_NORMAL, virtualAddress >> VA_OFFSET));
    } else {
        if (kernelVMML2PT->pte[l2Offset].valid == 0) {
            uint64_t ptPage = kernelPageAllocator.operations.allocPage4KAt(
                &kernelPageAllocator, USAGE_PAGE_TABLE,
                ((uint32_t)kernelVMMPT + l2Offset * 4 * KB + l3Offset * sizeof(struct PageTableEntry)) >> VA_OFFSET);

            kernelVMML2PT->pte[l2Offset].valid = 1;
            kernelVMML2PT->pte[l2Offset].table = 1;
            kernelVMML2PT->pte[l2Offset].af = 1;
            kernelVMML2PT->pte[l2Offset].base = ptPage;

            PageTableEntry* pt = (PageTableEntry*)kernelPageAllocator.base + ptPage * PAGE_SIZE;

            pt[0].valid = 1;
            pt[0].table = 1;
            pt[0].af = 1;
            pt[0].base = (uint64_t)(kernelPageAllocator.operations.allocPage4KAt(
                &kernelPageAllocator, USAGE_NORMAL, virtualAddress >> VA_OFFSET));
        } else {
            if (kernelVMMPT->pte[l3Offset].valid == 0) {
                kernelVMMPT->pte[l3Offset].valid = 1;
                kernelVMMPT->pte[l3Offset].table = 1;
                kernelVMMPT->pte[l3Offset].af = 1;
                kernelVMMPT->pte[l3Offset].base = (uint64_t)(kernelPageAllocator.operations.allocPage4KAt(
                    &kernelPageAllocator, USAGE_NORMAL, virtualAddress >> VA_OFFSET));
            } else {
                // not be there, if goes there, means it's not a page fault
            }
        }
    }
}
