[org 0x7c00]



mov bp, 0x7c00
mov sp, bp

mov [BOOT_DISK], dl

call ReadDisk



jmp KERNEL_SPACE

%include "boot/ReadDisk.asm"
%include "boot/PrintString.asm"

times 510 - ($-$$) db 0
dw 0xaa55


