#pragma once
#include <stdint.h>
#include "../Interrupts/IO.h"

extern void (*handler)(uint8_t scanCode, uint8_t chr);
extern const char ScanCodeLookupTable[];

class KeyboardHandler
{
private:
    static bool _initialized;

    static bool _shiftPressed;
    static bool _capsPressed;
    static bool _enterPressed;
    static uint8_t _lastScancode;
    static void (*_handlers[])(uint8_t scanCode, uint8_t chr);
    static uint8_t _currentHandlers;
public:

    static void Init();
    static void CallHandlers(uint8_t scanCode, uint8_t chr);
    static void AddHandler(void (*handlerPtr)(uint8_t scanCode, uint8_t chr));
    static void RemoveHandler(void (*handlerPtr)(uint8_t scanCode, uint8_t chr));
};

