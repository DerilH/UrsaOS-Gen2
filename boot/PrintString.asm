
;Place string ptr to bx register
PrintString:
    mov ah, 0x0e
        .loop:
            mov cx, [bx]
            cmp cl, 0
            je .end
            mov al, [bx]
            inc bx
            int 10h
            jmp .loop
        .end:
ret