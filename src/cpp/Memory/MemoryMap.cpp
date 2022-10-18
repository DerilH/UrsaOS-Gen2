#include "../../headers/Memory/MemoryMap.h"

extern uint8_t MemoryRegCount;
uint8_t UsableMemRegsCount = 0;

MemoryMapEntry* MemoryMap = (MemoryMapEntry*)0x5000;
MemoryMapEntry* UsableMemoryRegions[20];

void GetUsableMemRegs()
{
    for(int i = 0; i < MemoryRegCount; i++) 
    {
        if((&MemoryMap[i])->type == USABLE_MEMREG) 
        {
            UsableMemoryRegions[i] = (&MemoryMap[i]);
            UsableMemRegsCount++;
        }
    }
}

void PrintMemoryMap() 
{
    PrintStr("Loaded ");
    PrintStr(to_string(MemoryRegCount));
    PrintStr(" memory regions \n\r");

    for (int i = 1; i < MemoryRegCount; i++)
    {
        PrintStr("Address - ");
        PrintStr(hextos(MemoryMap[i].address));
        PrintStr(":\n\r");

        PrintStr("Type - ");
        PrintStr(MemoryRegTypes[MemoryMap[i].type]);
        PrintStr("\n\r");

        PrintStr("Size - ");
        PrintStr(to_string(MemoryMap[i].size));
        PrintStr("\n\r");
            
        PrintStr("Attributes - ");
        PrintStr(hextos(MemoryMap[i].attributes));
        PrintStr("\n\r");
    }
}
