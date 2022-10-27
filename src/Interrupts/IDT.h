#pragma once
#include <stdint.h>
#include "../Stdlib/string.h"
#include "../kernel/Panic.h"
#include "Interrupts.h"
#include "IO.h"

extern void (*KeyboardHandle)(uint8_t scanCode, uint8_t chr);

struct IDTEntry
{
    uint16_t offset_low;
    uint16_t selector;
    uint8_t ist;
    uint8_t types_attr;
    uint16_t offset_mid;
    uint32_t offset_high;
    uint32_t re_zero;
};

class Interrupts 
{
private:
    Interrupts();

    static bool _initialized;
    static void _setHandler(uint64_t* handler, IDTEntry* entry);
    static IDTEntry* _IDT;
public:
    static void Init();
    static void AddInterrupt(IDTEntry entry, uint8_t number);
    static void AddInterrupt(uint64_t* handler, uint8_t ist, uint16_t selector, uint8_t types_attr, uint8_t number);
    static void RemoveInterrupt(IDTEntry* entry);
    static void RemoveInterrupt(uint8_t number);
    static void DisableInterrupts();
    static void EnableInterrupts();
};

void InitializeIDT();
