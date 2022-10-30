kernel:
	nasm -f bin boot/boot.asm -o bin/boot.bin
	nasm -f elf64 boot/Program.asm -o obj/Program.o

	gcc -Ttext 0x8000 -ffreestanding -mgeneral-regs-only -mno-red-zone -c "src/Interrupts/Interrupts.cpp" -o "obj/Interrupts.o"

	gcc -Ttext 0x8000 -nostdlib -nodefaultlibs -ffreestanding -mno-red-zone -m64 -c "src/kernel/kernel.cpp" -o "obj/kernel.o" -no-pie
	gcc -Ttext 0x8000 -nostdlib -nodefaultlibs -ffreestanding -mno-red-zone -m64 -c "src/kernel/Panic.cpp" -o "obj/Panic.o" -no-pie

	gcc -Ttext 0x8000 -nostdlib -nodefaultlibs -ffreestanding -mno-red-zone -m64 -c "src/Interrupts/IDT.cpp" -o "obj/IDT.o" -no-pie
	gcc -Ttext 0x8000 -nostdlib -nodefaultlibs -ffreestanding -mno-red-zone -m64 -c "src/Interrupts/IO.cpp" -o "obj/IO.o" -no-pie

	gcc -Ttext 0x8000 -nostdlib -nodefaultlibs -ffreestanding -mno-red-zone -m64 -c "src/Devices/KeyboardHandler.cpp" -o "obj/KeyboardHandler.o" -no-pie
	gcc -Ttext 0x8000 -nostdlib -nodefaultlibs -ffreestanding -mno-red-zone -m64 -c "src/Devices/Screen.cpp" -o "obj/Screen.o" -no-pie

	gcc -Ttext 0x8000 -nostdlib -nodefaultlibs -ffreestanding -mno-red-zone -m64 -c "src/Stdlib/string.cpp" -o "obj/string.o" -no-pie
	gcc -Ttext 0x8000 -nostdlib -nodefaultlibs -ffreestanding -mno-red-zone -m64 -c "src/Stdlib/Constructors.cpp" -o "obj/Constructors.o" -no-pie
	gcc -Ttext 0x8000 -nostdlib -nodefaultlibs -ffreestanding -mno-red-zone -m64 -c "src/Stdlib/Bitmap.cpp" -o "obj/Bitmap.o" -no-pie
	
	gcc -Ttext 0x8000 -nostdlib -nodefaultlibs -ffreestanding -mno-red-zone -m64 -c "src/Memory/MemoryMap.cpp" -o "obj/MemoryMap.o" -no-pie
	gcc -Ttext 0x8000 -nostdlib -nodefaultlibs -ffreestanding -mno-red-zone -m64 -c "src/Memory/Memory.cpp" -o "obj/Memory.o" -no-pie

	gcc -Ttext 0x8000 -nostdlib -nodefaultlibs -ffreestanding -mno-red-zone -m64 -c "src/Memory/Paging/Paging.cpp" -o "obj/Paging.o" -no-pie
	gcc -Ttext 0x8000 -nostdlib -nodefaultlibs -ffreestanding -mno-red-zone -m64 -c "src/Memory/Paging/PageFrameAllocator.cpp" -o "obj/PageFrameAllocator.o" -no-pie
	gcc -Ttext 0x8000 -nostdlib -nodefaultlibs -ffreestanding -mno-red-zone -m64 -c "src/Memory/Paging/PageMapIndexer.cpp" -o "obj/PageMapIndexer.o" -no-pie
	gcc -Ttext 0x8000 -nostdlib -nodefaultlibs -ffreestanding -mno-red-zone -m64 -c "src/Memory/Paging/PageTableManager.cpp" -o "obj/PageTableManager.o" -no-pie

	gcc -Ttext 0x8000 -nostdlib -nodefaultlibs -ffreestanding -mno-red-zone -m64 -c "src/Time/Time.cpp" -o "obj/Time.o" -no-pie
	gcc -Ttext 0x8000 -nostdlib -nodefaultlibs -ffreestanding -mno-red-zone -m64 -c "src/Time/Pit.cpp" -o "obj/Pit.o" -no-pie

	gcc -Ttext 0x8000 -nostdlib -nodefaultlibs -ffreestanding -mno-red-zone -m64 -c "src/Shell/Shell.cpp" -o "obj/Shell.o" -no-pie

	ld -T"link.ld"
	cat bin/boot.bin bin/kernel.bin > kernel.flp

