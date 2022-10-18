#include <stdint.h>
#include "../headers/Print.h"
#include "../headers/string.h"
#include "../headers/TextModeColors.h"
#include "../cpp/IDT.cpp"
#include "../headers/Memory/MemoryMap.h"
#include "../headers/Memory/MemoryManagment.h"

void kernel_main() 
{
    
    PrintStr("bash > ");
    while(true);    
}

extern "C" void kernel_early_main() 
{
    SetCursorPos(0);
    ClearScreen();

    KeyboardHandle = KeyboardHandler;

    InitializeIDT();

    PrintStr("IDT init succes\n\r");

    //GetUsableMemRegs();
    PrintStr("Memory map loaded \n\r");

    //InitHeap(0x100000, 0x100000);

    //kernel_main();
}

