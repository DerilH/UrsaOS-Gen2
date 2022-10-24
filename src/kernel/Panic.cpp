#include "Panic.h"

void Panic::Invoke(const char* message) 
{
	Screen::CurrentScreen->Clear(BACKGROUND_BLACK);
	Screen::CurrentScreen->PutString(message, BACKGROUND_BLACK, FOREGROUND_LIGHTRED, 0, 0);
	Screen::CurrentScreen->SetCursorPos(10000);
	asm("cli");
	asm("hlt");
}
