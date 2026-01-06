; C0H0S1
; 调用0x10号BIOS中断，清屏
mov al, 0x03
mov ah, 0x00
int 0x10 

; LBA28模式，逻辑扇区号28位，从0x0000000到0xFFFFFFF
; 设置读取扇区的数量
mov dx, 0x01f2
mov al, 2 ; 读取连续的几个扇区，每读取一个al就会减1
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
mov cx, 512 ; 一共要读的字节除以2（表示次数，因为每次会读2字节所以要除以2）
mov dx, 0x01f0
mov ax, 0x0800
mov ds, ax
xor bx, bx ; [ds:bx] = 0x08000
read:
in ax, dx ; 16位端口，所以要用16位寄存器
mov [bx], ax
add bx, 2 ; 因为ax是16位，所以一次会写2字节
loop read

jmp 0x0800:0x0000 ; 这里写成0x0000:0x8000也OK，只是CS和IP的值会不同，但CS:IP是相同的

times 510-($-$$) db 0 ; MBR剩余部分用0填充
dw 0xaa55
