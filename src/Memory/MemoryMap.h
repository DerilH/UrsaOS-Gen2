#pragma once
#include <stdint.h>
#include "../Stdlib/string.h"
#include "../Shell/Shell.h"

#define USABLE_MEMREG 1
#define RESERVED_MEMREG 2
#define ACPI_RECLAIMED_MEMREG 3
#define ACPI_NVS_MEMREG 4
#define BAD_MEMREG 5

struct MemoryMapEntry
{
    uint64_t address;
    uint64_t size;
    uint32_t type;
    uint32_t attributes;
};

MemoryMapEntry** GetUsableMemRegs();
void PrintMemoryMap();

extern const char* MemoryRegTypes[];
