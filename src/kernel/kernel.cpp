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
#include "Panic.h"
static Screen screen(80, 25);
static Shell shell(&screen);

void kernel_main() 
{
    Screen::CurrentScreen = &screen;

    screen.Clear();
    
    shell.SetForegroundColor(FOREGROUND_LIGHTRED);
    shell.Print("Kernel loaded");
    shell.PrintCLRF();
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
    kernel_main();
}

