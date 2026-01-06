[bits 32]

begin:

mov ax, 00011_00_0b ; 选择3号段，数据段
mov ss, ax
mov es, ax      ; es也置为3号段
mov eax, 0x1000
mov esp, eax    ; 设置初始栈顶
mov ebp, eax    ; ebp也记录初始栈顶

mov ax, 00010_00_0b ; 选择2号段，显存段
mov ds, ax

; 初始化光标信息
mov [es:0x2000], dword 0 ; 初始化为0

; 32位环境下，入栈只能32位，所以先组一下数据
mov al, byte 'H'  ; 字符'H'
mov ah, byte 0x0f ; 黑底白色
push eax          ; 整个32位都入栈（用的时候只解析低16位）
call print

; 再打印一个字符
mov al, byte 'i'  ; 字符'i'
mov ah, byte 0x0f ; 黑底白色
push eax          
call print

; 再打印一个字符
mov al, byte '!'  ; 字符'!'
mov ah, byte 0x0f ; 黑底白色
push eax          
call print

hlt

print: 
; 现场记录
push ebp ; 栈顶记录（上一个调用栈的栈顶）
mov ebp, esp ; 用ebp记录现在的栈顶
; 通用寄存器的记录
push eax
push edx
; 下面是实际逻辑
mov edx, [ss:ebp+8] ; 现在再寻找参数时，就用ebp来计算了，ebp前有一个记录的上一个栈顶，以及一个回跳地址，所以固定偏移2个32位就是参数位置，不会随着入栈而跑偏
; 获取光标信息作为偏移地址
mov eax, [es:0x2000]
sal eax, 1       ; 左移一位，相当于乘以2，算出实际的内存偏移量
mov [eax], dx    ; 取低16位写入显存
; 改变光标信息
inc dword [es:0x2000]  ; 自增
; 现场还原
pop edx
pop eax
pop ebp ; 还原到之前调用栈的栈顶
ret ; 回跳


times 1024-($-begin) db 0 ; 补满2个扇区
