//
// Created by XingfengYang on 2020/8/17.
//

#ifndef __LIBRARY_LIBELF_ELF_H__
#define __LIBRARY_LIBELF_ELF_H__

#include <stdint.h>
#include <type.h>

typedef struct ElfFileHeader{

} ElfFileHeader;

typedef struct ElfProgramHeader{

} ElfProgramHeader;

typedef struct ElfSectionHeader{

} ElfSectionHeader;


typedef void (*ElfOperationParse)(struct Elf* elf);
typedef struct ElfOperations{
    ElfOperationParse parse;
} ElfOperations;

typedef struct Elf{
    char *data;
    uint32_t size;
    ElfFileHeader fileHeader;
    ElfProgramHeader programHeader;
    ElfSectionHeader sectionHeader;

    ElfOperations operations;
} Elf;

KernelStatus elf_init(Elf* elf, char* data);


#endif // __LIBRARY_LIBELF_ELF_H__
