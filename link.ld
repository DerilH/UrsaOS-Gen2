OUTPUT_FORMAT(binary)

ENTRY (kernel_early_main)

INPUT
(
    obj/Program.o
    obj/Kernel.o
    obj/IDT.o
    obj/IO.o
    obj/KeyboardHandler.o
    obj/MemoryMap.o
    obj/MemoryManagment.o
    obj/MemoryMapEntry.o
    obj/Print.o
    obj/string.o
)

OUTPUT
(
    bin/Kernel.bin
)

SECTIONS
{
    . = 0x8000;

    .text : ALIGN(0x1000)
    {
        *(.text)
    }
    
    .idt BLOCK(0x1000) : ALIGN(0x1000) 
    {
        _idt = .;
        . = . + 0x1000;
    }

    .data : ALIGN(0x1000)
    {
        *(.data)
    }
    
    .rodata : ALIGN(0x1000)
    {
        *(.rodata)
    }
    
    .bss : ALIGN(0x1000)
    {
        *(COMMON)
        *(.bss)
    }
}