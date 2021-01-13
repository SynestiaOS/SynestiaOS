//
// Created by XingfengYang on 2020/8/17.
//

#include "libelf/elf.h"
#include "kernel/log.h"
#include "libc/stdlib.h"

const char *object_file_type_to_string(uint32_t type) {
    switch (type) {
        case ET_NONE:
            return "None";
        case ET_REL:
            return "Relocatable";
        case ET_EXEC:
            return "Executable";
        case ET_DYN:
            return "Shared object";
        case ET_CORE:
            return "Core";
        case ET_LOOS:
            return "ET_LOOS";
        case ET_HIOS:
            return "ET_HIOS";
        case ET_LOPROC:
            return "ET_LOPROC";
        case ET_HIPROC:
            return "ET_HIPROC";
        default:
            return "UnKnown";
    }
}

const char *elf_get_target_machine_name(InstructionSet instructionSet) {
    switch (instructionSet) {
        case ARCH_Unknown: {
            return "No specific instruction set";
        }
        case ARCH_AT_T_WE_32100: {
            return "AT&T WE 32100";
        }
        case ARCH_SPARC: {
            return "SPARC";
        }
        case ARCH_x86: {
            return "x86";
        }
        case ARCH_Motorola_68000_M68k: {
            return "Motorola 68000 (M68k)";
        }
        case ARCH_Motorola_88000_M88k: {
            return "Motorola 88000 (M88k)";
        }
        case ARCH_Intel_MCU: {
            return "Intel MCU";
        }
        case ARCH_Intel_80860: {
            return "Intel 80860";
        }
        case ARCH_MIPS: {
            return "MIPS";
        }
        case ARCH_IBM_System_370: {
            return "IBM_System/370";
        }
        case ARCH_MIPS_RS3000_Little_endian: {
            return "MIPS RS3000 Little-endian";
        }
        case ARCH_Hewlett_Packard_PA_RISC: {
            return "Hewlett-Packard PA-RISC";
        }
        case ARCH_Reserved: {
            return "Hewlett-Packard PA-RISC";
        }
        case ARCH_Intel_80960: {
            return "Intel 80960";
        }
        case ARCH_PowerPC: {
            return "PowerPC";
        }
        case ARCH_PowerPC_64: {
            return "PowerPC (64-bit)";
        }
        case ARCH_S390x: {
            return "S390, including S390x";
        }
        case ARCH_ARM_32: {
            return "ARM (up to ARMv7/Aarch32)";
        }
        case ARCH_SuperH: {
            return "SuperH";
        }
        case ARCH_IA_64: {
            return "IA-64";
        }
        case ARCH_amd64: {
            return "amd64";
        }
        case ARCH_TMS320C6000: {
            return "TMS320C6000 Family";
        }
        case ARCH_ARM_64: {
            return "ARM 64-bits (ARMv8/Aarch64)";
        }
        case ARCH_RISC_V: {
            return "RISC-V";
        }
        default:
            return "unknown";
    }
}

KernelStatus elf_default_parse(Elf *elf) {
    // because we are in 32 bits mode, so the header is 54 byte
    elf->fileHeader = *(ElfFileHeader *) (elf->data);
    if (elf->fileHeader.magic[0] != 0x7F || elf->fileHeader.magic[1] != 0x45 || elf->fileHeader.magic[2] != 0x4c ||
        elf->fileHeader.magic[3] != 0x46) {
        elf->valid = false;
        LogError("[Elf]: not an elf file.\n");
        return ERROR;
    }

    if (elf->fileHeader.arch != 1) {
        LogError("[Elf]: just support 32-bit.\n");
        return ERROR;
    }

    if (elf->fileHeader.machine != ARCH_ARM_32) {
        LogError("[Elf]: just support arm-32, your target is %s \n",
                 elf_get_target_machine_name(elf->fileHeader.machine));
        return ERROR;
    }
}

void elf_default_dump(Elf *elf) {
    LogInfo("ELF (%d) {{", elf);
    LogInfo("    is_valid: %d}", elf->operations.isValid(elf));

    if (!elf->operations.isValid(elf)) {
        LogInfo("}}");
        return;
    }

    LogInfo("    type:    %s", object_file_type_to_string(elf->fileHeader.type));
    LogInfo("    machine: %s", elf_get_target_machine_name(elf->fileHeader.machine));
    LogInfo("    entry:   %d", elf->fileHeader.entry);
    LogInfo("    shoff:   %d", elf->fileHeader.sectionHeaderTableOffset);
    LogInfo("    shnum:   %d", elf->fileHeader.entryNumsInProgramHeaderTable);
    LogInfo("    phoff:   %d", elf->fileHeader.programHeaderTableOffset);
    LogInfo("    phnum:   %d", elf->fileHeader.entryNumsInSectionHeaderTable);
    LogInfo(" shstrndx:   %d", elf->fileHeader.indexOfSectionHeaderTable);

    ElfProgramHeader *programHeader = (ElfProgramHeader *) (elf->data + elf->fileHeader.programHeaderTableOffset);
    for (uint32_t i = 0; i < elf->fileHeader.entryNumsInProgramHeaderTable; i++) {
        LogInfo("    Program Header %d: {{", i);
        LogInfo("        type: %d", programHeader->type);
        LogInfo("      offset: %d", programHeader->segmentOffset);
        LogInfo("       flags: %d", programHeader->flags);
        LogInfo("    }}\n");
        programHeader += sizeof(struct ElfProgramHeader);
    }


    for (uint32_t i = 0; i < elf->fileHeader.entryNumsInSectionHeaderTable; i++) {
        ElfSectionHeader *sectionHeader = (struct ElfSectionHeader *) (elf->data +
                                                                       elf->fileHeader.sectionHeaderTableOffset +
                                                                       i * sizeof(ElfSectionHeader));
        LogInfo("    Section %d: {{", i);
        LogInfo("        name: %d", sectionHeader->name);
        LogInfo("        type: %d", sectionHeader->type);
        LogInfo("      offset: %d", sectionHeader->offset);
        LogInfo("        size: %d", sectionHeader->size);
        LogInfo("        ");
        LogInfo("    }}\n");

        if (sectionHeader->type == SHT_SYMTAB) {
            elf->symbolTableSectionIndex = i;
        }
    }

    ElfSectionHeader *symbolSectionHeader = (ElfSectionHeader *) (elf->data + sizeof(ElfSectionHeader) *
                                                                              elf->symbolTableSectionIndex);
    LogInfo("Symbol count: %d (table is %d)", symbolSectionHeader->entrySize, elf->symbolTableSectionIndex);

    for (uint32_t i = 0; i < symbolSectionHeader->entrySize; i++) {
        Elf32Symbol *symbol = (Elf32Symbol *) (elf->data + symbolSectionHeader->offset + i * (sizeof(Elf32Symbol)));
        LogInfo("Symbol %d:", i);
        LogInfo("    Name: %s", symbol->name);
        LogInfo("    In section: %d", elf->symbolTableSectionIndex);
        LogInfo("    Value: %d", symbol->value);
        LogInfo("    Size: %d", symbol->size);
    }

    LogInfo("}} \n");
}

bool elf_default_is_valid(Elf *elf) {
    return elf->valid;
}

KernelStatus elf_init(Elf *elf, char *data) {
    elf->operations.parse = (ElfOperationParse) elf_default_parse;
    elf->operations.dump = (ElfOperationDump) elf_default_dump;
    elf->operations.isValid = (ElfOperationIsValid) elf_default_is_valid;
    elf->valid = true;
    if (data[0] == 0x7F && data[1] == 0x45 && data[2] == 0x4c && data[3] == 0x46) {
        elf->data = data;
        return OK;
    }
    elf->valid = false;
    return ERROR;
}
