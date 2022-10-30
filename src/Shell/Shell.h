#pragma once
#include <stdint.h>
#include "../Stdlib/string.h"
#include "../Devices/KeyboardHandler.h"
#include "../Devices/Screen.h"
#include "../Stdlib/TextModeColors.h"
#include "../Time/Time.h"
#include "../Memory/MemoryMap.h"
#include "../Memory/Memory.h"
#include "../Memory/Paging/PageFrameAllocator.h"

#define INPUT_BUFFER_SIZE 128


class Shell
{
private:
    char _inputBuffer[INPUT_BUFFER_SIZE];

    Screen* _screen;
    bool _enterPressed = false;
    bool _shiftPressed = false;
    bool _interrupt = false;
    bool _capsPressed = false;
    uint8_t _lastScancode = 0;
    uint16_t _currentIndex = 0;
    uint32_t _cursorPos;

    uint8_t* _buffer;
    uint32_t _currentLine = 0;

    uint8_t _backColor = BACKGROUND_BLACK; 
    uint8_t _foreColor = FOREGROUND_LIGHTGRAY;

    static Shell* _instance;

    void _responseKeyboard(uint8_t scanCode, uint8_t chr);
    void _handleCommand(const char* cmd);
    static void _responceKeyboardS(uint8_t scanCode, uint8_t chr);
public:
    static Shell* CurrentShell;
    Shell(Screen* screen);
    void Print(const char* str);
    void Print(char chr);
    void PrintLine(const char* str);
    void PrintBackspace();
    void PrintCLRF(bool CL = true, bool RF = true);
    void SetBackgroundColor(uint8_t color);
    void SetForegroundColor(uint8_t color);
    void Update();
    void Call();
};