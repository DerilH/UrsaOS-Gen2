#include "../headers/IDT.h"

extern IDT _idt[256];
extern uint64_t isr1;
extern "C" void LoadIDT();

void (*KeyboardHandle)(uint8_t scanCode, uint8_t chr);

void InitializeIDT() 
{
    
	_idt[1].re_zero = 0;
	_idt[1].offset_low = (uint16_t)(((uint64_t)&isr1 & 0x000000000000ffff));
	_idt[1].offset_mid = (uint16_t)(((uint64_t)&isr1 & 0x00000000ffff0000) >> 16);
	_idt[1].offset_high = (uint32_t)(((uint64_t)&isr1 & 0xffffffff00000000) >> 32);
	_idt[1].ist = 0;
	_idt[1].selector = 0x08;
	_idt[1].types_attr = 0x8e;

    RemapPic();

    outb(0x21, 0xfd);
    outb(0xa1, 0xff);
    LoadIDT();
}

extern "C" void isr1_handler()
{
    uint8_t scanCode = inb(0x60);
    uint8_t chr = 0;
    if(scanCode < 0x3a)
    {
        chr = KBSet1::ScanCodeLookupTable[scanCode];
    }
    KeyboardHandler(scanCode, chr);
	outb(0x20, 0x20);
	outb(0xa0, 0x20);
}