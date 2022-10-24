#include "KeyboardHandler.h"
#define MAX_HANDLERS 32

const char ScanCodeLookupTable[] = {
    0, 0, '1', '2',
    '3', '4', '5', '6',
    '7', '8', '9', '0',
    '-', '=', 0, 0,
    'q', 'w', 'e', 'r',
    't', 'y', 'u', 'i',
    'o', 'p', '[', ']',
    0, 0, 'a', 's',
    'd', 'f', 'g', 'h',
    'j', 'k', 'l', ';',
    '\'', '`', 0, '\\',
    'z', 'x', 'c', 'v',
    'b', 'n', 'm', ',',
    '.', '/', 0, '*',
    0, ' '};
void (*handler)(uint8_t scanCode, uint8_t chr);

bool KeyboardHandler::_initialized = false;

void (*KeyboardHandler::_handlers[MAX_HANDLERS])(uint8_t scanCode, uint8_t chr);
uint8_t KeyboardHandler::_currentHandlers = 0;

void KeyboardHandler::CallHandlers(uint8_t scanCode, uint8_t chr)
{
    if(!_initialized) return;
    for(int i = 0; i < MAX_HANDLERS; i++) 
    {
        if(_handlers[i] == nullptr) continue;
        _handlers[i](scanCode, chr);
    }
}

void KeyboardHandler::Init() 
{
    if(_initialized) return;
    _initialized = true;

    handler = KeyboardHandler::CallHandlers;
    for(int i = 0; i < MAX_HANDLERS; i++) 
    {
        _handlers[i] = nullptr;
    }
}

void KeyboardHandler::AddHandler(void (*handlerPtr)(uint8_t scanCode, uint8_t chr))
{
    if(_currentHandlers == MAX_HANDLERS) return;
    for(int i = 0; i < MAX_HANDLERS; i++) 
    {
        if(_handlers[i] != nullptr) continue;
        _handlers[i] = handlerPtr;
        break;
    }
    _currentHandlers++;
}

void KeyboardHandler::RemoveHandler(void (*handlerPtr)(uint8_t scanCode, uint8_t chr))
{
    if(_currentHandlers == 0) return;

    for(int i = 0; i < MAX_HANDLERS; i++) 
    {
        if(_handlers[i] != handlerPtr) continue;;
        _handlers[i] = nullptr;
        break;
    } 
    _currentHandlers--;
}

