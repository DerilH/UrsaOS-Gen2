#include <stdint.h>
#include "../headers/Print.h"
#include "../headers/string.h"
#include "../headers/TextModeColors.h"
#include "../headers/IDT.h"
#include "../headers/Memory/MemoryMap.h"
#include "../headers/Memory/MemoryManagment.h"
#include "../headers/Shell.h"

bool waiting = false;

static Shell shell(inputBuffer, 128);

void kernel_main() 
{
    while(true)
    {
        shell.Call();
    }
}

extern "C" void kernel_early_main() 
{
    SetCursorPos(0);
    ClearScreen();

    KeyboardHandle = KeyboardHandler;

    InitializeIDT();

    PrintStr("IDT init succes\n\r");

    GetUsableMemRegs();
    PrintStr("Memory map loaded \n\r");

    InitHeap(0x100000, 0x100000);

    kernel_main();
}

