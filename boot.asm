[org 0x7c00]

%macro SetWriteMode 0
    mov ah, 0x0e
%endmacro

%macro PrintChar 1
    SetWriteMode
    mov al, %1
    int 0x10
%endmacro

%macro PrintCLRF 0
    push ax
    SetWriteMode
    mov al, 10
    int 10h 
    mov al, 13 
    int 10h
    pop ax
%endmacro

;Prints null-terminated string
%macro PrintString 1
    push ax
    push bx
    push cx
    SetWriteMode
    mov bx, %1
    %%loop:
        mov cx, [bx]
        cmp cl, 0
        je %%end
        mov al, [bx]
        inc bx
        int 10h
        jmp %%loop
    %%end:
    pop cx
    pop bx
    pop ax
%endmacro 

%macro ReadChar 0
    mov ah, 0
    int 0x16
%endmacro

;First arg: buffer pointer
;Second arf: number of chars to read
%macro ReadString 2
    push bx
    push cx
    push ax
    mov cx, 0
    mov bx, %1
    %%loop:
        ReadChar
        ;Check for Backspace
        cmp al, 8
        jne %%nb
        cmp cx, 0    
        je %%loop
        cmp [bx - 1], byte '>'
        je %%loop

        dec bx
        dec cx
        PrintChar 8
        jmp %%loop
        %%nb:
        ;Check for Enter
        cmp al, 13
        je %%end
        ;Check for buffer end
        cmp cx, %2
        je %%end

        mov [bx], al
        inc cx
        inc bx
        PrintChar al
        jmp %%loop
    %%end:
    inc bx
    mov [bx], word 0
    PrintCLRF
    pop ax
    pop cx
    pop bx
%endmacro

;First arg: buffer pointer
;Second arg: buffer size
%macro ClearBuffer 2
    push bx
    push cx

    mov bx, %1
    mov cx, 0

    %%loop:
        mov [bx], byte 0
        cmp cx, %2
        je %%end
        
        inc bx 
        inc cx

    jmp %%loop

    %%end:

    pop cx
    pop bx
%endmacro

;Fisrt and Second args: null-terminated string buffer pointers
;Returns true or false to al register
%macro CompareStrings 2

    push bx ; stack bx
    push cx ; stack cx
    push dx ; stack dx

    mov bx, %1 ; set pointer to bx
    mov cx, %2 ; set pointer to cx

    cmp bx, cx ; compare bx, cx pointers
    je %%true ; return true

    %%loop:
        mov ax, [bx]

        push bx
        mov bx, cx
        mov dx, [bx] ; swap bx in stack and read from cx
        pop bx

        cmp ax, dx  
        jne %%false ; if "A" = "A" cotinue
        
        cmp ah, 0 
        je %%true ; if end of string return true

        inc bx
        inc cx
        
        jmp %%loop
    %%true:
        mov ax, 1
        jmp %%end
    %%false:
        mov ax, 0
    %%end:

    pop dx
    pop cx
    pop bx
%endmacro

;First arg: number
;Second arg: string buffer pointer
;Returns number as string to buffer  
%macro NumberToString 2
    pusha
    mov ax, %1
    mov bx, %2
    mov si, 0
    mov cx, 0 

    %%loop:
        mov dl, 10
        div dl

        add ah, 48
        mov [bx], byte ah
        inc bx
        mov ah, 0

        inc si

        cmp al, 0
        je %%end1
    jmp %%loop
   
    %%end1:

    sub bx, si
    %%puloop:
        mov ax, [bx]
        push ax
        inc bx
        inc cx

        cmp si, cx
        je %%end2
    jmp %%puloop
    %%end2:

    sub bx, si
    mov cx, 0
    %%poloop:
        cmp si, cx
        je %%end
        
        pop ax
        mov [bx], al

        inc bx
        inc cx

    jmp %%poloop
    %%end:
    mov [bx], byte 0
    popa
%endmacro

mov ax, 0
ILoop:

    PrintString baseInputMessage
    ReadString inputBuffer, 256

    .end:
    ClearBuffer inputBuffer, 128 ; Clear input buffer
jmp ILoop


;Data

baseInputMessage: db "bash > ", 0
inputBuffer:
 times 32 db 0
testBuff: db "NumberToString", 0
times 510 - ($-$$) db 0
dw 0xaa55