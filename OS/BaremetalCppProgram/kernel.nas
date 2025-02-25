begin:
mov ax, 0xb800
mov ds, ax
mov [0x0000], byte 'H'
mov [0x0001], byte 0x0f
mov [0x0002], byte 'e'
mov [0x0003], byte 0x0f
mov [0x0004], byte 'l'
mov [0x0005], byte 0x0f
mov [0x0006], byte 'l'
mov [0x0007], byte 0x0f
mov [0x0008], byte 'o'
mov [0x0009], byte 0x0f
hlt
times 1024-($-$$) db 0 ; 由于begin已经在此文件中定投了，所以这里改成了$$