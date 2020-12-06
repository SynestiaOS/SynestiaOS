//
// Created by XingfengYang on 2020/6/15.
//

#include "arm/kernel_vmm.h"
#include "arm/mmu.h"
#include "arm/page.h"
#include "kernel/log.h"
#include "kernel/type.h"
#include "libc/stdlib.h"

extern int __PAGE_TABLE;
extern PhysicalPageAllocator kernelPageAllocator;

Level1PageTable *kernelVMML1PT;

void map_kernel_pt(uint64_t pageTablePhysicalAddress) {
    kernelVMML1PT = (Level1PageTable *) pageTablePhysicalAddress;
    kernelVMML1PT->pte[0].valid = 1;
    kernelVMML1PT->pte[0].table = 0;
    kernelVMML1PT->pte[0].af = 1;
    kernelVMML1PT->pte[0].base = (uint32_t) 0 >> VA_OFFSET;

    kernelVMML1PT->pte[1].valid = 1;
    kernelVMML1PT->pte[1].table = 0;
    kernelVMML1PT->pte[1].af = 1;
    kernelVMML1PT->pte[1].base = (uint32_t)((1*GB) >> VA_OFFSET);

    kernelVMML1PT->pte[2].valid = 1;
    kernelVMML1PT->pte[2].table = 0;
    kernelVMML1PT->pte[2].af = 1;
    kernelVMML1PT->pte[2].base = (uint32_t)((2*GB) >> VA_OFFSET);

    kernelVMML1PT->pte[3].valid = 1;
    kernelVMML1PT->pte[3].table = 0;
    kernelVMML1PT->pte[3].af = 1;
    kernelVMML1PT->pte[3].base = (uint32_t)((3*GB) >> VA_OFFSET);
}

void map_kernel_mm() {
    uint64_t pageTablePhysicalAddress = (uint64_t) &__PAGE_TABLE;

    map_kernel_pt(pageTablePhysicalAddress);
    LogInfo("[vmm]: page table done\n");
}

void kernel_vmm_init() {
    mmu_disable();
    map_kernel_mm();

    /**
   * if lpaeSupport = 5, means LPAE is supported
   */
    uint32_t lpaeSupport = (read_mmfr0() & 0xF);
    LogWarn("[LPAE]: mmfr0: %d\n", lpaeSupport);

    kernel_vmm_enable();
}

void kernel_vmm_enable() {
    write_ttbcr(CONFIG_ARM_LPAE << 31);
    LogInfo("[vmm]: ttbcr writed\n");

    write_ttbr0((uint32_t) kernelVMML1PT);
    LogInfo("[vmm]: ttbr0 writed\n");

    write_dacr(0x55555555);
    LogInfo("[vmm]: dacr writed\n");

    mmu_enable();
    LogInfo("[vmm]: vmm enabled\n");
}

PageTableEntry *kernel_vmm_get_page_table() { return (PageTableEntry *) kernelVMML1PT; }

void kernel_vmm_map(uint32_t virtualAddress) {
    LogError("[vmm]: ooops, memory fault at %d .\n", virtualAddress);
}
