#include "MemoryMap.h"

const char* MemoryRegTypes[] =
{
    "Nothing",
    "USABLE_MEMREG",
    "RESERVED_MEMREG",
    "ACPI_RECLAIMED_MEMREG",
    "ACPI_NVS_MEMREG",
    "BAD_MEMREG"
};

extern uint8_t MemoryRegCount;
uint8_t UsableMemRegsCount = 0;

MemoryMapEntry* MemoryMap = (MemoryMapEntry*)0x5000;

void PrintMemoryMap() 
{
    Shell::CurrentShell->Print("Loaded ");
    Shell::CurrentShell->Print(to_string(MemoryRegCount));
    Shell::CurrentShell->Print(" memory regions \n\r");

    for (int i = 1; i < MemoryRegCount; i++)
    {
        Shell::CurrentShell->Print("Address - ");
        Shell::CurrentShell->Print(hextos(MemoryMap[i].address));
        Shell::CurrentShell->Print(":\n\r");

        Shell::CurrentShell->Print("Type - ");
        Shell::CurrentShell->Print(MemoryRegTypes[MemoryMap[i].type]);
        Shell::CurrentShell->Print("\n\r");

        Shell::CurrentShell->Print("Size - ");
        Shell::CurrentShell->Print(to_string(MemoryMap[i].size));
        Shell::CurrentShell->Print("\n\r");
            
        Shell::CurrentShell->Print("Attributes - ");
        Shell::CurrentShell->Print(hextos(MemoryMap[i].attributes));
        Shell::CurrentShell->Print("\n\r");
    }
}
