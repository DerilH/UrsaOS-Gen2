#include <stdint.h>
#include "../Stdlib/string.h"
#include "../Stdlib/TextModeColors.h"
#include "../Stdlib/Constructors.h"
#include "../Memory/MemoryMap.h"
#include "../Memory/MemoryManagment.h"
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
    
    Time::Update();
    const char * str = Time::GetFullDateAsString();

    shell.Print(str);
    shell.PrintCLRF();

    //PitInit();

    while(true)
    {
       //Screen::CurrentScreen->PutString(Time::GetFullDateAsString(), BACKGROUND_BLACK, FOREGROUND_LIGHTGRAY, 0, 1);
       shell.Call();
    }
}

extern "C" void kernel_early_main() 
{

    InitHeap(0x100000, 0x100000);
    Interrupts::Init();
    KeyboardHandler::Init();

    callConstructors();

    //outb(PIC1_DATA, 0b11111000);
    //outb(PIC2_DATA, 0b11101111);

    kernel_main();
}

