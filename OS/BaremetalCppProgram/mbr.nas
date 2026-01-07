; 调用0x10号BIOS中断，清屏
mov al, 0x03
mov ah, 0x00
int 0x10 

; LBA28模式，逻辑扇区号28位，从0x0000000到0xFFFFFFF
; 设置读取扇区的数量
mov dx, 0x01f2
; mov al, 2 ; 读取连续的几个扇区，每读取一个al就会减1
mov al, 9 ; 读取连续的几个扇区，每读取一个al就会减1
out dx, al
; 设置起始扇区号，28位需要拆开
mov dx, 0x01f3
mov al, 0x02 ; 从第2个扇区开始读（1起始，0留空），扇区号0~7位
out dx, al
mov dx, 0x01f4 ; 扇区号8~15位
mov al, 0
out dx, al
mov dx, 0x01f5 ; 扇区号16~23位
mov al, 0
out dx, al
mov dx, 0x01f6
mov al, 111_0_0000b ; 低4位是扇区号24~27位，第4位是主从盘（0主1从），高3位表示磁盘模式（111表示LBA）
; 配置命令
mov dx, 0x01f7
mov al, 0x20 ; 0x20命令表示读盘
out dx, al

wait_finish:
; 检测状态，是否读取完毕
mov dx, 0x01f7
in al, dx ; 通过该端口读取状态数据
and al, 1000_1000b ; 保留第7位和第3位
cmp al, 0000_1000b ; 要检测第7位为0（表示不在忙碌状态）和第3位是否是1（表示已经读取完毕）
jne wait_finish ; 如果不满足则循环等待

; 从端口加载数据到内存
; mov cx, 512 ; 一共要读的字节除以2（表示次数，因为每次会读2字节所以要除以2）
mov cx, 2304 ; 一共要读的字节除以2（表示次数，因为每次会读2字节所以要除以2）
mov dx, 0x01f0
mov ax, 0x0800
mov ds, ax
xor bx, bx ; [ds:bx] = 0x08000
read:
in ax, dx ; 16位端口，所以要用16位寄存器
mov [bx], ax
add bx, 2 ; 因为ax是16位，所以一次会写2字节
loop read

; 下面配置GDT
mov ax, 0x07e0
mov es, ax

; 空白段
mov [es:0x00], dword 0
mov [es:0x04], dword 0

; 1号段
; 基址0x8000，大小8KB
mov [es:0x08], word 0x1fff ; Limit=0x001fff，这是低8位
mov [es:0x0a], word 0x8000 ; Base=0x00008000，这是低16位
mov [es:0x0c], byte 0      ; 这是Base的16~23位
mov [es:0x0d], byte 1_00_1_100_0b ; P=1, DPL=0, S=1, Type=100b, A=0
mov [es:0x0e], byte 0_1_00_0000b  ; G=0, D/B=1, AVL=00, Limit的高4位是0000
mov [es:0x0f], byte 0      ; 这是Base的高8位

; 2号段
; 基址0xb8000，上限0xb8f9f，覆盖所有显存
mov [es:0x10], word 0x0f9f ; Limit=0x000f9f，这是低16位
mov [es:0x12], word 0x8000 ; Base=0x0b8000，这是低16位
mov [es:0x14], byte 0x0b   ; 这是Base的高8位
mov [es:0x15], byte 1_00_1_001_0b ; P=1, DPL=0, S=1, Type=001b, A=0
mov [es:0x16], byte 0_1_00_0000b  ; G=0, D/B=1, AVL=00, Limit的高4位是0000
mov [es:0x17], byte 0      ; 这是Base的高8位

; 3号段-数据段（要包含和对其代码段）
; 基址0x8000，大小4MB
mov [es:0x18], word 0x03ff ; Limit=0x400，这是低8位
mov [es:0x1a], word 0x8000 ; Base=0x00008000，这是低16位
mov [es:0x1c], byte 0x0000 ; 这是Base的16~23位
mov [es:0x1d], byte 1_00_1_001_0b ; P=1, DPL=0, S=1, Type=001b, A=0
mov [es:0x1e], byte 1_1_00_0000b  ; G=1, D/B=1, AVL=00, Limit的高4位是0000
mov [es:0x1f], byte 0x00   ; 这是Base的高8位

; 下面是gdt信息的配置（暂且放在0x07f00的位置）
mov ax, 0x07f0
mov es, ax
mov [es:0x00], word 31      ; 因为目前配了4个段，长度为32，所以limit为31
mov [es:0x02], dword 0x7e00 ; GDT配置表的首地址
; 把gdt配置进gdtr
lgdt [es:0x00]

mov eax, cr0
or eax, 0x01 ; PE位置1，启动保护模式
mov cr0, eax

jmp 00001_00_0b:0 ; 远跳指令可以刷新cs，使用1号段，正好跳转至kernel的加载位置（0x8000）

times 510-($-$$) db 0 ; MBR剩余部分用0填充
dw 0xaa55
