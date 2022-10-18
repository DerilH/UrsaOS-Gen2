#pragma once

#include "stdint.h"
#include "IO.h"
#include "TextModeColors.h"

extern unsigned short CursorPosition;

void SetCursorPos(unsigned short position);
unsigned short GetCursorPos();
void SetCursorPos(unsigned short x, unsigned short y);
void PutChr(uint8_t chr, uint8_t backcolor, uint8_t forecolor, int x, int y);
void PrintChr(char chr, int color = 7);
void PrintStr(const char *string, int color = 7);
void PrintEndl();
void PrintBackspace();
void ClearScreen(uint64_t ClearColor = BACKGROUND_BLACK | FOREGROUND_WHITE);
