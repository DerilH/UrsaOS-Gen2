MemoryRegCount: db 0
GLOBAL MemoryRegCount

DetectMemory:
    mov ax, 0
    mov es, ax
    mov di, 0x5000
    mov edx, 0x534D4150
    xor ebx, ebx

    .repeat:
        mov eax, 0xE820
        mov ecx, 24
        int 0x15

        cmp ebx, 0
        je .end

        add di, 24
        inc byte [MemoryRegCount]
        jmp .repeat
    .end:
ret