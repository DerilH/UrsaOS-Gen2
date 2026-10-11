# UrsaOS-Gen2

This is my old barebones attempt at creating an operating system from scratch. It features minimal functionality and a simple mini-terminal (shell).

## Features
- **64-bit Kernel**: Written in C++ and Assembly.
- **Custom Bootloader**: Minimal boot sequence.
- **Memory Management**: Basic Paging and Page Frame Allocator.
- **Interrupt Handling**: IDT and keyboard support.
- **Mini-Terminal (Shell)**: A basic command-line interface.
- **Text Mode Graphics**: Simple screen driver for text output.

## Mini-Terminal Commands
Once booted, you can use the following commands in the shell:
- `date`: Displays the current date and time.
- `memmap`: Prints the memory map.
- `getmem`: Shows memory usage statistics (Total, Free, Reserved, Used) in bytes.
- `getmemkb`: Shows memory usage statistics in KB.
- `bitmap`: Prints the status of the page frame allocator's bitmap.

## How to Build and Run

### Prerequisites
- `nasm`: For assembling bootloader and assembly routines.
- `gcc`: For compiling C++ code.
- `ld`: For linking the kernel.
- `qemu-system-x86_64`: To run the OS in an emulator.
- `make`: For building the project.

### Building
To build the project and create the floppy image (`kernel.flp`), run:
```bash
make
```

### Running
To run the OS using QEMU:
```bash
./run
```
Or manually:
```bash
qemu-system-x86_64 kernel.flp -m 100M
```

## Disclaimer
This is a "barebones" educational project and is not intended for any practical use. It was a learning exercise in understanding low-level x86_64 architecture and kernel development.
