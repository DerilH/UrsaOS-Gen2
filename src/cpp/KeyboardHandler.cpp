#include "../headers/KeyboardHandler.h"

bool ShiftPressed = false;
bool CapsPressed = false;
bool EnterPressed = false;
uint8_t lastScancode = 0;
char inputBuffer[128];
int bufferIndex = 0;

void KeyboardHandler(uint8_t scanCode, uint8_t chr)
{
    if(chr != 0)
    {
        inputBuffer[bufferIndex] = chr;
        bufferIndex++;
        if((!CapsPressed && !ShiftPressed) ||  (CapsPressed && ShiftPressed))
        {
            PrintChr(chr);
        } else if((CapsPressed && !ShiftPressed) || (ShiftPressed && !CapsPressed))
        {
            PrintChr(chr - 32);
        }
    }
    else
    {
        if(lastScancode == 0xE0)
        {
            switch (scanCode)
            {
                case 0x4B:
                    CursorPosition--;
                    SetCursorPos(CursorPosition);
                break;

                case 0x4D:
                    CursorPosition++;
                    SetCursorPos(CursorPosition);
                break;
            }
            lastScancode = scanCode;
            return;
        }
        switch (scanCode)
        {
            case 0x0E:
                PrintBackspace();
            break;
            case 0x2A:
                ShiftPressed = true;
            break;
            case 0x36:
                ShiftPressed = true;
            break;
            case 0xAA:
                ShiftPressed = false;
            break;
            case 0xB6:
                ShiftPressed = false;
            break;
            case 0xBA:
                CapsPressed= !CapsPressed;
            break;
            case 0x1C:
                EnterPressed = true;
                inputBuffer[bufferIndex] = 0;
                bufferIndex = 0;
            break;
            case 0x9C:
                EnterPressed = false;                
            break;
        }
    }
    lastScancode = scanCode;
}
