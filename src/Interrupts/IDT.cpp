#include "IDT.h"

extern IDTEntry _idt[256];
extern "C" void LoadIDT();

void (*KeyboardHandle)(uint8_t scanCode, uint8_t chr);

#define IRQ_BASE                        0x20

#define IRQ_TIMER                       0x00
#define IRQ_KEYBOARD                    0x01
#define IRQ_COM2                        0x03
#define IRQ_COM1                        0x04
#define IRQ_FLOPPY                      0x06
#define IRQ_ATA0                        0x0e
#define IRQ_ATA1                        0x0f

#define INT_TIMER                       0x20
#define INT_SPURIOUS                    0xff


IDTEntry* Interrupts::_IDT = nullptr;
bool Interrupts::_initialized = false;

void Interrupts::_setHandler(uint64_t handler, IDTEntry* entry) 
{
	//entry->offset_low = (uint16_t)(((uint64_t)&handler & 0x000000000000ffff));
	//entry->offset_mid = (uint16_t)(((uint64_t)&handler & 0x00000000ffff0000) >> 16);
	//entry->offset_high = (uint32_t)(((uint64_t)&handler & 0xffffffff00000000) >> 32);

	entry->offset_low = (uint16_t)(handler & 0x000000000000ffff);
	entry->offset_mid = (uint16_t)((handler & 0x00000000ffff0000) >> 16);
	entry->offset_high = (uint32_t)((handler & 0xffffffff00000000) >> 32);
}

Interrupts::Interrupts() {}

void Interrupts::Init() 
{
	if (_initialized) Panic::Invoke("Trying to reinit IDT");
	_initialized = true;


	AddInterrupt((uint64_t)((uint64_t*)KeyboardINT_Handler), 0, 0x08, 0x8e, 0x21);
	//AddInterrupt(&isr0, 0, 0x08, 0x8e, 0);
	//AddInterrupt(&isr20, 0, 0x08, 0x8e, INT_TIMER);
	
	//000000000000af4a
	//0xaf4a
	LoadIDT();

	RemapPIC();

	outb(0x21, 0xfd);
	outb(0xa1, 0xff);
}
void Interrupts::AddInterrupt(IDTEntry entry, uint8_t number) 
{
	if (!_initialized) Panic::Invoke("Trying to add interrupt before initialization");

	_IDT[number] = entry;
}
void Interrupts::AddInterrupt(uint64_t handler, uint8_t ist, uint16_t selector, uint8_t types_attr, uint8_t number)
{
	if (!_initialized) Panic::Invoke("Trying to add interrupt before initialization");
	
	_setHandler(handler, &_idt[number]);
	_idt[number].ist = ist;
	_idt[number].re_zero = 0;
	_idt[number].selector = selector;
	_idt[number].types_attr = types_attr;
}
void Interrupts::RemoveInterrupt(IDTEntry* entry) 
{
	if (!_initialized) Panic::Invoke("Trying to remove interrupt before initialization");

	entry->ist = 0;
	entry->offset_high = 0;
	entry->offset_mid = 0;
	entry->offset_low = 0;
	entry->re_zero = 0;
	entry->selector = 0;
	entry->types_attr = 0;
}

void Interrupts::RemoveInterrupt(uint8_t number)
{
	if (!_initialized) Panic::Invoke("Trying to remove interrupt before initialization");

	_idt[number].ist = 0;
	_idt[number].offset_high = 0;
	_idt[number].offset_mid = 0;
	_idt[number].offset_low = 0;
	_idt[number].re_zero = 0;
	_idt[number].selector = 0;
	_idt[number].types_attr = 0;
}

void Interrupts::DisableInterrupts()
{
	asm("cli");
}
void Interrupts::EnableInterrupts() 
{
	asm("sti");
}