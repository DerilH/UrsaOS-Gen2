CODE_SEG equ code_descriptor - GDT_Start
DATA_SEG equ data_descriptor - GDT_Start

GDT_Start:
    null_descriptor:
        dd 0h
        dd 0h
    code_descriptor:
        dw 0xffff ; Limit
        dw 0h ; Base
        db 0h ; Base
        db 10011010b ; PPT, Type flags
        db 11001111b ; Other + limit
        db 0h ; Base
    data_descriptor:
        dw 0xffff ; Limit
        dw 0h ; Base
        db 0h ; Base
        db 10010010b ; PPT, Type flags
        db 11001111b ; Other + limit
        db 0h ; Base
GDT_End:
GDT_Descriptor:
    dw GDT_End - GDT_Start - 1
    dd GDT_Start

[bits 32]
EditGDT:
    mov [code_descriptor + 6], byte 10101111b
    mov [data_descriptor + 6], byte 10101111b
ret
[bits 16]