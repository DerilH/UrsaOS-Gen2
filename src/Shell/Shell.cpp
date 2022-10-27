#include "Shell.h"
#include <map>

Shell* Shell::_instance = nullptr;
Shell* Shell::CurrentShell = nullptr;

void Shell::_responseKeyboard(uint8_t scanCode, uint8_t chr)
{
    if (chr != 0)
    {
        _inputBuffer[_currentIndex] = chr;
        _currentIndex++;
        if ((!_capsPressed && !_shiftPressed) || (_capsPressed && _shiftPressed))
        {
            Print(chr);
        }
        else if ((_capsPressed && !_shiftPressed) || (_shiftPressed && !_capsPressed))
        {
            Print(chr - 32);
        }
    }
    else
    {
        if (_lastScancode == 0xE0)
        {
            switch (scanCode)
            {
            case 0x4B:
                if ((_cursorPos % _screen->GetWidth() <= 7)) return;
                _cursorPos--;
                _screen->SetCursorPos(_cursorPos);
                break;

            case 0x4D:
                _cursorPos++;
                _screen->SetCursorPos(_cursorPos);
                break;
            }
            _lastScancode = scanCode;
            return;
        }
        switch (scanCode)
        {
        case 0x0E:
            if((_cursorPos % _screen->GetWidth() <= 7)) return;
            PrintBackspace();
            _currentIndex--;
            break;
        case 0x2A:
            _shiftPressed = true;
            break;
        case 0x36:
            _shiftPressed = true;
            break;
        case 0xAA:
            _shiftPressed = false;
            break;
        case 0xB6:
            _shiftPressed = false;
            break;
        case 0xBA:
            _capsPressed = !_capsPressed;
            break;
        case 0x1C:
            _enterPressed = true;
            _inputBuffer[_currentIndex] = 0;
            _interrupt = true;
            break;
        case 0x9C:
            _enterPressed = false;
            break;
        }
    }
    _lastScancode = scanCode;
}

void Shell::Call()
{
    Print("bash > ");
    while (!_interrupt)
    {
        asm("hlt");
    }
    PrintCLRF();
    _handleCommand(_inputBuffer);
    PrintCLRF();

    _interrupt = false;
    _currentIndex = 0;
}

void Shell::_responceKeyboardS(uint8_t scanCode, uint8_t chr)
{
    _instance->_responseKeyboard(scanCode, chr);
}

Shell::Shell(Screen* screen)
{
    this->_screen = screen;
    _screen->SetCursorPos(0);
    _instance = this;
    CurrentShell = this;
    KeyboardHandler::RemoveHandler(_responceKeyboardS);
    KeyboardHandler::AddHandler(_responceKeyboardS);
}

void Shell::Print(const char* str)
{
    _cursorPos = _screen->PutString(str, _backColor, _foreColor, _cursorPos, 0);
    _screen->SetCursorPos(_cursorPos);
}
void Shell::Print(char chr) 
{
    _screen->PutChar(chr, _backColor, _foreColor, _cursorPos, 0);
    _cursorPos++;
    _screen->SetCursorPos(_cursorPos);
}

void Shell::PrintBackspace()
{
    _cursorPos--;
    _screen->PutChar(' ', _backColor, _foreColor, _cursorPos, 0);
    _screen->SetCursorPos(_cursorPos);
}

void Shell::PrintCLRF(bool CL, bool RF)
{
    if(RF) 
    {
        _cursorPos += _screen->GetWidth();
    }
    if(CL) 
    {
        _cursorPos -= _cursorPos % _screen->GetWidth();
    }
    _screen->SetCursorPos(_cursorPos);
}

void Shell::SetBackgroundColor(uint8_t color) 
{
    this->_backColor = color;
}
void Shell::SetForegroundColor(uint8_t color) 
{
    this->_foreColor = color;
}

void Shell::_handleCommand(const char* cmd) 
{
    if (cmpStrs(_inputBuffer, "date")) 
    {
        Print(RTC::GetFullDateAsString());
    }
    else if(cmpStrs(_inputBuffer, "memmap"))
    {
        PrintMemoryMap();
    }
}