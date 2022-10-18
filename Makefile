kernel:
	nasm -f bin boot/boot.asm -o bin/boot.bin
	nasm -f elf64 boot/Program.asm -o obj/Program.o
	
	gcc -Ttext 0x8000 -ffreestanding -mno-red-zone -m64 -c "src/cpp/kernel.cpp" -o "obj/kernel.o"
	gcc -Ttext 0x8000 -ffreestanding -mno-red-zone -m64 -c "src/cpp/IDT.cpp" -o "obj/IDT.o"
	gcc -Ttext 0x8000 -ffreestanding -mno-red-zone -m64 -c "src/cpp/IO.cpp" -o "obj/IO.o"
	gcc -Ttext 0x8000 -ffreestanding -mno-red-zone -m64 -c "src/cpp/KeyboardHandler.cpp" -o "obj/KeyboardHandler.o"
	gcc -Ttext 0x8000 -ffreestanding -mno-red-zone -m64 -c "src/cpp/Print.cpp" -o "obj/Print.o"
	gcc -Ttext 0x8000 -ffreestanding -mno-red-zone -m64 -c "src/cpp/string.cpp" -o "obj/string.o"
	gcc -Ttext 0x8000 -ffreestanding -mno-red-zone -m64 -c "src/cpp/Memory/MemoryMap.cpp" -o "obj/MemoryMap.o"
	gcc -Ttext 0x8000 -ffreestanding -mno-red-zone -m64 -c "src/cpp/Memory/MemoryMapEntry.cpp" -o "obj/MemoryMapEntry.o"
	gcc -Ttext 0x8000 -ffreestanding -mno-red-zone -m64 -c "src/cpp/Memory/MemoryManagment.cpp" -o "obj/MemoryManagment.o"

	ld -T"link.ld"
	cat bin/boot.bin bin/kernel.bin > kernel.flp