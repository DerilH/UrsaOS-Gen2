#pragma once 
#include <stdint.h>
#include "../Stdlib/TextModeColors.h"
#include "../Interrupts/IO.h"
#define VIDEO_MEMORY (uint8_t*)0xb8000

class Screen 
{
private:
    int _width = 0;
    int _height = 0;
    int _mode = 0;
    uint16_t _cursorPos = 0;
public:
    static Screen* CurrentScreen;
    
    Screen(int width, int height);
    void PutChar(uint8_t chr, uint8_t backcolor, uint8_t forecolor, int x, int y);
    int PutString(const char* chr, uint8_t backcolor, uint8_t forecolor, int x, int y);
    void Clear(uint64_t color =  BACKGROUND_BLACK | FOREGROUND_WHITE);
    void SetCursorPos(uint16_t position);
    void SetCursorPos(uint16_t x, uint16_t y);
    int GetWidth();
    int GetHeight();
    uint16_t GetCusorPos();
};