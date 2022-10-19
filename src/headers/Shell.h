#pragma once
#include <stdint.h>
#include "string.h"
#include "KeyboardHandler.h"

class Shell
{
private:
    //char* inputBuffer;
    int bufferLenght;

public:
    Shell(char* inputBuffer, int bufferLenght) 
    {
        //this->inputBuffer = inputBuffer;
        this->bufferLenght = bufferLenght;
    }

    void Call() 
    {
        PrintStr("bash > ");
        while (!EnterPressed )
        {
            asm("hlt");
        }
        PrintEndl();
        if(cmpStrs(inputBuffer, "test")) 
        {
            PrintStr("echo");
        }
        PrintEndl();
        EnterPressed = false;
    }
};