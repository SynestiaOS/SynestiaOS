//
// Created by XingfengYang on 2020/8/17.
//

#ifndef __LIBRARY_LIBELF_ELF_H__
#define __LIBRARY_LIBELF_ELF_H__

#include <libc/stdint.h>
#include <kernel/type.h>

typedef enum ObjectFileType {
    ET_NONE = 0x00,
    ET_REL = 0x01,
    ET_EXEC = 0x02,
    ET_DYN = 0x03,
    ET_CORE = 0x04,
    ET_LOOS = 0xfe00,
    ET_HIOS = 0xfeff,
    ET_LOPROC = 0xff00,
    ET_HIPROC = 0xffff,
} ObjectFileType;

typedef enum InstructionSet {
    ARCH_Unknown = 0x00,
    ARCH_AT_T_WE_32100 = 0x01,
    ARCH_SPARC = 0x02,
    ARCH_x86 = 0x03,
    ARCH_Motorola_68000_M68k = 0x04,
    ARCH_Motorola_88000_M88k = 0x05,
    ARCH_Intel_MCU = 0x06,
    ARCH_Intel_80860 = 0x07,
    ARCH_MIPS = 0x08,
    ARCH_IBM_System_370 = 0x09,
    ARCH_MIPS_RS3000_Little_endian = 0x0A,
    ARCH_Hewlett_Packard_PA_RISC = 0x0E,
    ARCH_Reserved = 0x0F,
    ARCH_Intel_80960 = 0x13,
    ARCH_PowerPC = 0x14,
    ARCH_PowerPC_64 = 0x15,
    ARCH_S390x = 0x16,
    ARCH_ARM_32 = 0x28,
    ARCH_SuperH = 0x2A,
    ARCH_IA_64 = 0x32,
    ARCH_amd64 = 0x3E,
    ARCH_TMS320C6000 = 0x8C,
    ARCH_ARM_64 = 0xB7,
    ARCH_RISC_V = 0xF3,
} InstructionSet;

typedef struct ElfFileHeader {
    uint8_t magic[4];// .elf
    uint8_t arch;    // This byte is set to either 1 or 2 to signify 32- or 64-bit format, respectively.
    uint8_t endian;  // This byte is set to either 1 or 2 to signify little or big endianness, respectively. This affects
    // interpretation of multi-byte fields starting with offset 0x10.
    uint8_t currentVersion;// Set to 1 for the original and current version of ELF.
    uint8_t osABI;         // Identifies the target operating system ABI.
    uint8_t abiVersion;    // Further specifies the ABI version. Its interpretation depends on the target ABI. Linux kernel
    // (after at least 2.6) has no definition of it[5], so it is ignored for statically-linked
    // executables. In that case, offset and size of EI_PAD are 8.
    uint8_t pad;             // currently unused, should be filled with zeros.
    uint16_t type;           // Identifies object file type.
    uint16_t machine;        // Specifies target instruction set architecture.
    uint32_t originalVersion;// Set to 1 for the original version of ELF.
    uint32_t entry;          // This is the memory address of the entry point from where the process starts executing. This field
    // is either 32 or 64 bits long depending on the format defined earlier.
    uint32_t programHeaderTableOffset;// Points to the start of the program header table. It usually follows the file
    // header immediately, making the offset 0x34 or 0x40 for 32- and 64-bit ELF
    // executables, respectively.
    uint32_t sectionHeaderTableOffset;     // Points to the start of the section header table.
    uint32_t flags;                        // Interpretation of this field depends on the target architecture.
    uint16_t headerSize;                   // 64 for 64 bits machine, 54 for 32 bits machine;
    uint16_t programHeaderEntryTableSize;  // Contains the size of a program header table entry.
    uint16_t entryNumsInProgramHeaderTable;// Contains the number of entries in the program header table.
    uint16_t sectionHeaderEntryTableSize;  // Contains the size of a section header table entry.
    uint16_t entryNumsInSectionHeaderTable;// Contains the number of entries in the section header table.
    uint16_t
            indexOfSectionHeaderTable;// Contains index of the section header table entry that contains the section names.

} ElfFileHeader;

typedef enum SegmentType {
    PT_NULL = 0x00000000,   //		Program header table entry unused
    PT_LOAD = 0x00000001,   //		Loadable segment
    PT_DYNAMIC = 0x00000002,//		Dynamic linking information
    PT_INTERP = 0x00000003, //		Interpreter information
    PT_NOTE = 0x00000004,   //		Auxiliary information
    PT_SHLIB = 0x00000005,  //		reserved
    PT_PHDR = 0x00000006,   //		segment containing program header table itself
    PT_TLS = 0x00000007,    //		Thread-Local Storage template
    PT_LOOS = 0x60000000,   //		see below
    PT_HIOS = 0x6FFFFFFF,   //
    PT_LOPROC = 0x70000000, //
    PT_HIPROC = 0x7FFFFFFF, //
} SegmentType;
typedef struct ElfProgramHeader {
    uint32_t type;                 // Identifies the type of the segment.
    uint32_t segmentOffset;        // Offset of the segment in the file image.
    uint32_t segmentVirtualAddress;// Virtual address of the segment in memory.
    uint32_t
            segmentPhysicalAddress;// On systems where physical address is relevant, reserved for segment's physical address.
    uint32_t segmentSizeInImage;   // Size in bytes of the segment in the file image. May be 0.
    uint32_t segmentSizeInMemory;  // Size in bytes of the segment in memory. May be 0.
    uint32_t flags;                // Segment-dependent flags (position for 32-bit structure).
    uint32_t alignment;            // 0 and 1 specify no alignment. Otherwise should be a positive, integral power of 2, with p_vaddr
    // equating p_offset modulus p_align.
} ElfProgramHeader;

typedef enum HeaderType {
    SHT_NULL = 0x0,          //		Section header table entry unused
    SHT_PROGBITS = 0x1,      //		Program data
    SHT_SYMTAB = 0x2,        //		Symbol table
    SHT_STRTAB = 0x3,        //		String table
    SHT_RELA = 0x4,          //		Relocation entries with addends
    SHT_HASH = 0x5,          //		Symbol hash table
    SHT_DYNAMIC = 0x6,       //		Dynamic linking information
    SHT_NOTE = 0x7,          //		Notes
    SHT_NOBITS = 0x8,        //		Program space with no data (bss)
    SHT_REL = 0x9,           //		Relocation entries, no addends
    SHT_SHLIB = 0x0A,        //		Reserved
    SHT_DYNSYM = 0x0B,       //		Dynamic linker symbol table
    SHT_INIT_ARRAY = 0x0E,   //		Array of constructors
    SHT_FINI_ARRAY = 0x0F,   //		Array of destructors
    SHT_PREINIT_ARRAY = 0x10,//		Array of pre-constructors
    SHT_GROUP = 0x11,        //		Section group
    SHT_SYMTAB_SHNDX = 0x12, //		Extended section indices
    SHT_NUM = 0x13,          //		Number of defined types.
    SHT_LOOS = 0x60000000,   //		Start OS-specific.
} HeaderType;

typedef enum HeaderAttribute {
    SHF_WRITE = 0x1,             //		Writable
    SHF_ALLOC = 0x2,             //		Occupies memory during execution
    SHF_EXECINSTR = 0x4,         //		Executable
    SHF_MERGE = 0x10,            //		Might be merged
    SHF_STRINGS = 0x20,          //		Contains null-terminated strings
    SHF_INFO_LINK = 0x40,        //		'sh_info' contains SHT index
    SHF_LINK_ORDER = 0x80,       //		Preserve order after combining
    SHF_OS_NONCONFORMING = 0x100,//		Non-standard OS specific handling required
    SHF_GROUP = 0x200,           //		Section is member of a group
    SHF_TLS = 0x400,             //		Section hold thread-local data
    SHF_MASKOS = 0x0ff00000,     //		OS-specific
    SHF_MASKPROC = 0xf0000000,   //		Processor-specific
    SHF_ORDERED = 0x4000000,     //		Special ordering requirement (Solaris)
    SHF_EXCLUDE = 0x8000000,     //		Section is excluded unless referenced or allocated (Solaris)
} HeaderAttribute;

typedef struct ElfSectionHeader {
    uint32_t name;          // An offset to a string in the .shstrtab section that represents the name of this section.
    uint32_t type;          // Identifies the type of this header.
    uint32_t attributes;    // Identifies the attributes of the section.
    uint32_t virtualAddress;// Virtual address of the section in memory, for sections that are loaded.
    uint32_t offset;        // Offset of the section in the file image.
    uint32_t size;          // Size in bytes of the section in the file image. May be 0.
    uint32_t link;          // Contains the section index of an associated section. This field is used for several purposes,
    // depending on the type of section.
    uint32_t info;// Contains extra information about the section. This field is used for several purposes, depending on
    // the type of section
    uint32_t addressAlignment;// Contains the required alignment of the section. This field must be a power of two.
    uint32_t entrySize;       // Contains the size, in bytes, of each entry, for sections that contain fixed-size entries.
    // Otherwise, this field contains zero.
} ElfSectionHeader;

typedef void (*ElfOperationParse)(struct Elf *elf);

typedef struct ElfOperations {
    ElfOperationParse parse;
} ElfOperations;

typedef struct Elf {
    char *data;
    uint32_t size;
    ElfFileHeader fileHeader;
    ElfProgramHeader programHeader;
    ElfSectionHeader sectionHeader;

    ElfOperations operations;
} Elf;

KernelStatus elf_init(Elf *elf, char *data);

#endif// __LIBRARY_LIBELF_ELF_H__
