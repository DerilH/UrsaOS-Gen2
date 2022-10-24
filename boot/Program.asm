[bits 16]

call DetectMemory

cli 
lgdt [GDT_Descriptor]
mov eax, cr0
or eax, 1
mov cr0, eax

jmp CODE_SEG:start_protected_mode

%include "boot/GDT.asm"
%include "boot/DetectMemory.asm"
[bits 32]

%include "boot/DetectCPUID.asm"
%include "boot/Paging.asm"

start_protected_mode:

    mov ax, DATA_SEG
    mov ds, ax
    mov ss, ax
    mov es, ax
    mov fs, ax
    mov gs, ax


    call DetectCPUID
    call DetectLongMode
    call SetupIndentityPaging
    call EditGDT
    
    jmp CODE_SEG:start_long_mode
jmp $

[bits 64]
[extern kernel_early_main]
%include "boot/IDT.asm"
start_long_mode:
    call ActivateSSE

    call kernel_early_main
    jmp $


ActivateSSE:
    mov rax, cr0
    and ax, 0b11111101
    or ax,  0b00000001
    mov cr0, rax

    mov rax, cr4
    or ax, 0b1100000000
    mov cr4, rax
ret
times 3072-($-$$) db 0