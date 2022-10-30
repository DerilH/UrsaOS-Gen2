#include <stdint.h>
#include "../Stdlib/string.h"
#include "../Stdlib/TextModeColors.h"
#include "../Stdlib/Constructors.h"
#include "../Memory/MemoryMap.h"
#include "../Memory/Memory.h"
#include "../Shell/Shell.h"
#include "../Time/Time.h"
#include "../Time/Pit.h"
#include "../Devices/Screen.h"
#include "../Interrupts/IDT.h"
#include "../Memory/Paging/PageFrameAllocator.h"
#include "../Memory/Paging/PageTableManager.h"
#include "../Memory/Paging/Paging.h"
#include "Panic.h"

static Screen screen(80, 25);
static Shell shell(&screen);

extern uint64_t _KernelStart;
extern uint64_t _KernelEnd;
const uint64_t KernelSize = (uint64_t)&_KernelEnd - (uint64_t)&_KernelStart;

PageTableManager pageTableManager = 0;

extern "C" void DisablePaging();
extern "C" void EnablePaging();

void kernel_main() 
{
    Screen::CurrentScreen = &screen;

    screen.Clear();
    
    shell.SetForegroundColor(FOREGROUND_LIGHTRED);
    shell.PrintLine("Kernel loaded");
    shell.SetForegroundColor(FOREGROUND_LIGHTGRAY);
    shell.PrintCLRF();

    while(true)
    {
       shell.Call();
    }
}

extern "C" void kernel_early_main() 
{
    InitHeap(0x100000, 0x100000);
    Interrupts::Init();
    KeyboardHandler::Init();
    PIT::SetDivisor(65535);

    Timer timer(995);
    timer.SetCallback([]()
        {
            Screen::CurrentScreen->PutString(RTC::GetFullDateAsString(), BACKGROUND_BLACK, FOREGROUND_LIGHTGRAY, 61, 0);
        });
    timer.Start();
    timer.Cycled = true;

    callConstructors();

    PageFrameAllocator::Init(MemoryMap, MemoryRegCount);
    PageFrameAllocator::LockPages(&_KernelStart, KernelSize / 4096 + 1);
    PageFrameAllocator::LockPages((void*)0, 8);

    //Paging
    PageTable* PML4 = (PageTable*)PageFrameAllocator::RequestPage();
    memset(PML4, 0, 0x1000);

    pageTableManager = PageTableManager(PML4);

    
    //Shell::CurrentShell->PrintLine(to_string(PageFrameAllocator::GetFullMemorySize()));

    for (uint64_t t = 0x0000; t < PageFrameAllocator::GetFullMemorySize() - 0x500000; t += 0x1000) {
        pageTableManager.MapMemory((void*)t, (void*)t);
        Screen::CurrentScreen->PutString(to_string(t), BACKGROUND_BLACK, FOREGROUND_LIGHTRED, 0, 0);
    }
    
    asm("mov %0, %%cr3" : : "r" (PML4));
    kernel_main();
}

