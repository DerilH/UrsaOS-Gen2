#include "IDT.h"

extern IDTEntry _idt[256];
extern "C" void LoadIDT();

void (*KeyboardHandle)(uint8_t scanCode, uint8_t chr);

#define IRQ_BASE                        0x20

#define IRQ_TIMER                       0x00
#define IRQ_KEYBOARD                    0x21
#define IRQ_COM2                        0x03
#define IRQ_COM1                        0x04
#define IRQ_FLOPPY                      0x06
#define IRQ_ATA0                        0x0e
#define IRQ_ATA1                        0x0f

#define INT_TIMER                       0x20
#define INT_SPURIOUS                    0xff


#define ZERO_DIVIDE_FAULT				0x00

#define DOUBLE_FAULT					0x08
#define GENERAL_PROTECTON_FAULT			0x0D
#define PAGE_FAULT_FAULT				0x0E

IDTEntry* Interrupts::_IDT = nullptr;
bool Interrupts::_initialized = false;

void Interrupts::_setHandler(uint64_t* handler, IDTEntry* entry) 
{
	entry->offset_low = (uint16_t)(((uint64_t)handler & 0x000000000000ffff));
	entry->offset_mid = (uint16_t)(((uint64_t)handler & 0x00000000ffff0000) >> 16);
	entry->offset_high = (uint32_t)(((uint64_t)handler & 0xffffffff00000000) >> 32);
}

Interrupts::Interrupts() {}

void Interrupts::Init() 
{
	if (_initialized) Panic::Invoke("Trying to reinit IDT");
	_initialized = true;

	AddInterrupt(&KeyboardISR, 0, 0x08, 0x8e, IRQ_KEYBOARD);
	AddInterrupt(&pitISR, 0, 0x08, 0x8e, INT_TIMER);

	for (int i = 0; i <= 30; i++) 
	{
		if (i == 22)
			i = 28;
		AddInterrupt(&DefaultISR, 0, 0x08, 0x8e, i);
	}

	AddInterrupt(&ZeroDivideISR, 0, 0x08, 0x8e, ZERO_DIVIDE_FAULT);
	AddInterrupt(&PageFaultISR, 0, 0x08, 0x8e, PAGE_FAULT_FAULT);

	AddInterrupt(&GeneralProtectionFaultISR, 0, 0x08, 0x8e, GENERAL_PROTECTON_FAULT);
	AddInterrupt(&DoubleFaultISR, 0, 0x08, 0x8e, DOUBLE_FAULT);

	

	LoadIDT();
	RemapPIC();

	outb(0x21, 0b11111000);
	outb(0xa1, 0xff);
}
void Interrupts::AddInterrupt(IDTEntry entry, uint8_t number) 
{
	if (!_initialized) Panic::Invoke("Trying to add interrupt before initialization");

	_IDT[number] = entry;
}
void Interrupts::AddInterrupt(uint64_t* handler, uint8_t ist, uint16_t selector, uint8_t types_attr, uint8_t number)
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