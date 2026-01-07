[bits 32]
section .text 

global SetVMem ; 告诉链接器下面这个标签是外部可用的
SetVMem:
    ; 现场记录
    push ebp
    mov ebp, esp
    ; 过程中用到的寄存器都要先记录
    push ebx
    push ecx
    push edx

    mov bx, es ; 用bx记录原本的es，用于后续恢复现场（这里是因为寄存器还够用，如果不够用的话就还是要压栈）
    ; 把es配成显存段
    mov dx, 00010_00_0b
    mov es, dx
    ; 通过参数找到addr和data
    mov edx, [ebp+8]  ; addr
    mov ecx, [ebp+12] ; data
    ; 通过es加偏移地址来操作显存
    mov [es:edx], cl  ; 由于data是1字节的，所以其实只有cl是有效数据

    ; 现场还原
    mov es, bx
    pop edx
    pop ecx
    pop ebx
    mov esp, ebp
    pop ebp
    ; 回跳
    ret
