OUTPUT_FORMAT(binary)

ENTRY (kernel_early_main)

INPUT
(
    obj/Program.o
    obj/Interrupts.o
    obj/Kernel.o
    obj/IDT.o
    obj/IO.o
    obj/Shell.o
    obj/Screen.o
    obj/KeyboardHandler.o
    obj/MemoryMap.o
    obj/Memory.o
    obj/PageFrameAllocator.o
    obj/string.o
    obj/Constructors.o
    obj/Time.o
    obj/Panic.o
    obj/Pit.o
    obj/Bitmap.o
    obj/PageTableManager.o
    obj/PageMapIndexer.o
    obj/Paging.o
)

OUTPUT
(
    bin/Kernel.bin
)

SECTIONS
{
 	

     . = 0x8000;
     _KernelStart = .;
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
          start_ctors = .;
         KEEP(*( .init_array ));
         KEEP(*(SORT_BY_INIT_PRIORITY( .init_array.* )));
         end_ctors = .;
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
     _KernelEnd = .;
}