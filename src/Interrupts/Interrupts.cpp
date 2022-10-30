#include "Interrupts.h"
#include "../kernel/Panic.h"
#include "../Time/Pit.h"

extern uint64_t KeyboardISR;
extern uint64_t pitISR;
extern uint64_t ZeroDivideISR;
extern uint64_t PageFaultISR;
extern uint64_t DoubleFaultISR;
extern uint64_t GeneralProtectionFaultISR;
extern uint64_t DefaultISR;

void PIC_EndMaster() {
	outb(PIC1_COMMAND, PIC_EOI);
}

void PIC_EndSlave() {
	outb(PIC2_COMMAND, PIC_EOI);
	outb(PIC1_COMMAND, PIC_EOI);
}

void RemapPIC() {
	uint8_t a1, a2;

	a1 = inb(PIC1_DATA);
	a2 = inb(PIC2_DATA);

	outb(PIC1_COMMAND, ICW1_INIT | ICW1_ICW4);
	outb(PIC2_COMMAND, ICW1_INIT | ICW1_ICW4);
	outb(PIC1_DATA, IRQ_OFFSET);
	outb(PIC2_DATA, IRQ_OFFSET + 8);
	outb(PIC1_DATA, 4);
	outb(PIC2_DATA, 2);
	outb(PIC1_DATA, ICW4_8086);
	outb(PIC2_DATA, ICW4_8086);

	outb(PIC1_DATA, a1);
	outb(PIC2_DATA, a2);

}

extern "C" void KeyboardINT_Handler()
{
	uint8_t scanCode = inb(0x60);
	uint8_t chr = 0;
	if (scanCode < 0x3a)
	{
		chr = ScanCodeLookupTable[scanCode];
	}
	handler(scanCode, chr);
	PIC_EndMaster();
}

extern "C" void DivideByZeroEX()
{
	Panic::Invoke("Zero divide");
}

extern "C" void PITINT_Handler()
{
	PIT::Tick();
	PIC_EndMaster();
}

extern "C" void PageFaultEX()
{
	Panic::Invoke("Page fault");
}

extern "C" void DoubleFaultEX() 
{
	Panic::Invoke("Double fault");
}

extern "C" void GeneralProtectionFaultEX()
{
	Panic::Invoke("General protection fault");
}

extern "C" void DefaultEX() 
{
	Panic::Invoke("Fault");
}