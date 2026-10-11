CC = gcc
ASM = nasm

# Основные флаги компиляции для ядра (включая защиту от переполнения стека -fno-stack-protector)
CFLAGS = -Ttext 0x8000 -nostdlib -nodefaultlibs -ffreestanding -mno-red-zone -m64 -fno-stack-protector -no-pie

# Специальные флаги для Interrupts.cpp (с сохранением -mgeneral-regs-only)
CFLAGS_INTERRUPTS = -Ttext 0x8000 -ffreestanding -mgeneral-regs-only -mno-red-zone -fno-stack-protector

kernel:
	mkdir -p bin
	mkdir -p obj
	$(ASM) -f bin boot/boot.asm -o bin/boot.bin
	$(ASM) -f elf64 boot/Program.asm -o obj/Program.o

	$(CC) $(CFLAGS_INTERRUPTS) -c "src/Interrupts/Interrupts.cpp" -o "obj/Interrupts.o"

	$(CC) $(CFLAGS) -c "src/kernel/kernel.cpp" -o "obj/kernel.o"
	$(CC) $(CFLAGS) -c "src/kernel/Panic.cpp" -o "obj/Panic.o"

	$(CC) $(CFLAGS) -c "src/Interrupts/IDT.cpp" -o "obj/IDT.o"
	$(CC) $(CFLAGS) -c "src/Interrupts/IO.cpp" -o "obj/IO.o"

	$(CC) $(CFLAGS) -c "src/Devices/KeyboardHandler.cpp" -o "obj/KeyboardHandler.o"
	$(CC) $(CFLAGS) -c "src/Devices/Screen.cpp" -o "obj/Screen.o"

	$(CC) $(CFLAGS) -c "src/Stdlib/string.cpp" -o "obj/string.o"
	$(CC) $(CFLAGS) -c "src/Stdlib/Constructors.cpp" -o "obj/Constructors.o"
	$(CC) $(CFLAGS) -c "src/Stdlib/Bitmap.cpp" -o "obj/Bitmap.o"
	
	$(CC) $(CFLAGS) -c "src/Memory/MemoryMap.cpp" -o "obj/MemoryMap.o"
	$(CC) $(CFLAGS) -c "src/Memory/Memory.cpp" -o "obj/Memory.o"

	$(CC) $(CFLAGS) -c "src/Memory/Paging/Paging.cpp" -o "obj/Paging.o"
	$(CC) $(CFLAGS) -c "src/Memory/Paging/PageFrameAllocator.cpp" -o "obj/PageFrameAllocator.o"
	$(CC) $(CFLAGS) -c "src/Memory/Paging/PageMapIndexer.cpp" -o "obj/PageMapIndexer.o"
	$(CC) $(CFLAGS) -c "src/Memory/Paging/PageTableManager.cpp" -o "obj/PageTableManager.o"

	$(CC) $(CFLAGS) -c "src/Time/Time.cpp" -o "obj/Time.o"
	$(CC) $(CFLAGS) -c "src/Time/Pit.cpp" -o "obj/Pit.o"

	$(CC) $(CFLAGS) -c "src/Shell/Shell.cpp" -o "obj/Shell.o"

	ld -T"link.ld"
	cat ./bin/boot.bin ./bin/kernel.bin > kernel.flp