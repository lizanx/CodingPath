; C0H0S1
; 调用0x10号BIOS中断，清屏
mov al, 0x03
mov ah, 0x00
int 0x10 
; 加载一个扇区到0x08000的位置
mov ax, 0x0800
mov es, ax
mov bx, 0 ; 软盘中的内容会加载到es:bx的位置
mov ah, 2 ; ah=2, 使用读盘功能
mov al, 2 ; ah表示需要读取连续的几个扇区（读2个就是1KB的大小）
mov ch, 0 ; ch表示第几柱面
mov dh, 0 ; dh表示第几磁头
mov cl, 2 ; cl表示第几扇区
mov dl, 0 ; dl表示驱动器号，软盘会在0x00~0x7F，硬盘会在0x80~0xFF
int 0x13  ; 执行0x13号中断的2号功能（读盘功能）

jmp 0x0800:0x0000 ; 这里写成0x0000:0x8000也OK，只是CS和IP的值会不同，但CS:IP是相同的

times 510-($-$$) db 0 ; MBR剩余部分用0填充
dw 0xaa55

; 现在已经是C0H0S2的内容了
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

times 1024-($-begin) db 0 ; 补满2个扇区