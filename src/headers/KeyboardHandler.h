#pragma once
#include <stdint.h>
#include "KBScanCodeSet1.h"
#include "Print.h"

extern bool EnterPressed;
void KeyboardHandler(uint8_t scanCode, uint8_t chr);
extern char inputBuffer[128];