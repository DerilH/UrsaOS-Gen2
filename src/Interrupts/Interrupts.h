#pragma once 
#include <stdint.h>
#include "IO.h"
#include "../Devices/KeyboardHandler.h"

#define PIC1_COMMAND 0x20
#define PIC1_DATA 0x21
#define PIC2_COMMAND 0xA0
#define PIC2_DATA 0xA1
#define PIC_EOI 0x20

#define ICW1_INIT 0x10
#define ICW1_ICW4 0x01
#define ICW4_8086 0x01

#define IRQ_OFFSET 0x20

extern uint64_t KeyboardISR;
extern uint64_t ZeroDivideISR;
extern uint64_t PageFaultISR;
extern uint64_t pitISR;
extern uint64_t DoubleFaultISR;
extern uint64_t GeneralProtectionFaultISR;
extern uint64_t DefaultISR;

void RemapPIC();
void PIC_EndMaster();
void PIC_EndSlave();

