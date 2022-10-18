#include "../headers/Print.h"

#define VIDEO_MEMORY (uint8_t*)0xb8000
#define VGA_WIDTH 80

unsigned short CursorPosition;

void SetCursorPos(unsigned short position) 
{
    outb(0x3D4, 0x0F);
    outb(0x3D5, (unsigned char)(position & 0xFF));
    outb(0x3D4, 0x0E);
    outb(0x3D5, (unsigned char)((position >> 8) & 0xFF));
    CursorPosition = position;
}
unsigned short GetCursorPos() 
{
    return CursorPosition;
}
void SetCursorPos(unsigned short x, unsigned short y) 
{
    SetCursorPos(x + y * VGA_WIDTH);
}

void PutChr(uint8_t chr, uint8_t backcolor, uint8_t forecolor, int x, int y) 
{
    uint16_t attrib = (backcolor << 4) | (forecolor & 0x0F);
    volatile uint16_t * where;
    where = (volatile uint16_t *)0xB8000 + (y * VGA_WIDTH + x) ;
    *where = chr | (attrib << 8);
}

void PrintChr(char chr, int color)
{
    PutChr(chr, 0, color, CursorPosition, 0);
    CursorPosition++;
    SetCursorPos(CursorPosition);
}

void PrintStr(const char *string, int color) 
{
    uint8_t* charPtr = (uint8_t*)string;
    while(*charPtr != 0) 
    {
        if(*charPtr == '\n') 
        {
            CursorPosition += VGA_WIDTH;
            charPtr++;
            continue;
        }
        if(*charPtr == '\r') 
        {
            CursorPosition -= CursorPosition % 80;
            charPtr++;
            continue;
        }

        PutChr(*charPtr, 0, color, CursorPosition, 0);
        charPtr++;
        CursorPosition++;
    }
    SetCursorPos(CursorPosition);
}

void PrintEndl()
{
    CursorPosition += VGA_WIDTH;
    CursorPosition -= CursorPosition % 80;
}


void PrintBackspace()
{
    CursorPosition--;
    PutChr(' ', 0, 7, CursorPosition, 0);
    SetCursorPos(CursorPosition);
}

void ClearScreen(uint64_t ClearColor)
{
    uint64_t value = 0;
    value += ClearColor << 8;
    value += ClearColor << 24;
    value += ClearColor << 40;
    value += ClearColor << 56;
    for(uint64_t* i = (uint64_t*)VIDEO_MEMORY; i < (uint64_t*)(VIDEO_MEMORY + 4000); i++)
    {
        *i = value;
    }
}