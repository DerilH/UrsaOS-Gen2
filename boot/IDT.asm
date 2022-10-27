[extern _idt]
idtDescriptor:
  dw 4095
  dq _idt

  %macro PUSHALL 0
  	push rax
  	push rcx
  	push rdx
  	push r8
  	push r9
  	push r10
  	push r11
  %endmacro

  %macro POPALL 0
  	pop r11
  	pop r10
  	pop r9
  	pop r8
  	pop rdx
  	pop rcx
  	pop rax

  %endmacro

[extern KeyboardINT_Handler]
KeyboardISR:
    PUSHALL
    call KeyboardINT_Handler
    POPALL
    iretq
    GLOBAL KeyboardISR
    
[extern DivideByZeroEX]
ZeroDivideISR:
    PUSHALL
    call DivideByZeroEX
    POPALL
    iretq
    GLOBAL ZeroDivideISR

[extern PageFaultEX]
PageFaultISR:
    PUSHALL
    call PageFaultEX
    POPALL
    iretq
    GLOBAL PageFaultISR

[extern PITINT_Handler]
pitISR:
    PUSHALL
    call PITINT_Handler
    POPALL
    iretq
    GLOBAL pitISR;

[extern DoubleFaultEX]
DoubleFaultISR:
    PUSHALL
    call DoubleFaultEX
    POPALL
    iretq
    GLOBAL DoubleFaultISR

[extern GeneralProtectionFaultEX]
GeneralProtectionFaultISR:
    PUSHALL
    call GeneralProtectionFaultEX
    POPALL
    iretq
    GLOBAL GeneralProtectionFaultISR

LoadIDT:
  lidt[idtDescriptor]
  sti
  ret
  GLOBAL LoadIDT