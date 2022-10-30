#include "Screen.h"

Screen* Screen::CurrentScreen = nullptr;


Screen::Screen(int width, int height)
{
    this->_width = width;
    this->_height = height;
}

void Screen::PutChar(uint8_t chr, uint8_t backcolor, uint8_t forecolor, int x, int y)
{
    uint16_t attrib = (backcolor << 4) | (forecolor & 0x0F);
    volatile uint16_t *where;
    where = (volatile uint16_t *)0xB8000 + (y * _width + x);
    *where = chr | (attrib << 8);
}

int Screen::PutString(const char* str, uint8_t backcolor, uint8_t forecolor, int x, int y) 
{
    uint16_t posBackup = _cursorPos;
    uint8_t* charPtr = (uint8_t*)str;
    int relatedPos;
    _cursorPos = x + y * _width;
    while(*charPtr != 0) 
    {
        if(*charPtr == '\n') 
        {
            _cursorPos += _width;
            charPtr++;
            continue;
        }
        if(*charPtr == '\r') 
        {
            _cursorPos -= _cursorPos % 80;
            charPtr++;
            continue;
        }

        PutChar(*charPtr, backcolor, forecolor, _cursorPos, 0);
        charPtr++;
        _cursorPos++;
    }
    relatedPos = _cursorPos;
    _cursorPos = posBackup;
    return relatedPos;
}

void Screen::Clear(uint64_t color)
{
    uint64_t value = 0;
    value += color << 8;
    value += color << 24;
    value += color << 40;
    value += color << 56;
    for (uint64_t *i = (uint64_t *)VIDEO_MEMORY; i < (uint64_t *)(VIDEO_MEMORY + 4000); i++)
    {
        *i = value;
    }
}
void Screen::SetCursorPos(uint16_t position)
{
    outb(0x3D4, 0x0F);
    outb(0x3D5, (unsigned char)(position & 0xFF));
    outb(0x3D4, 0x0E);
    outb(0x3D5, (unsigned char)((position >> 8) & 0xFF));
    _cursorPos = position;
}
void Screen::SetCursorPos(uint16_t x, uint16_t y)
{
    SetCursorPos(x + y * _width);
}
uint16_t Screen::GetCusorPos()
{
    return _cursorPos;
}

int Screen::GetWidth() 
{
    return _width;
}
int Screen::GetHeight() 
{
    return _height;
}