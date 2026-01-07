[bits 32]
section .text 

begin:
	mov ax, 00011_00_0b ; 选择3号段，数据段
	mov ss, ax
	; ds要跟ss一致
	mov ds, ax
	; es也初始化为数据段（防止后续出问题，先初始化）
	mov es, ax

	; 初始化栈
	mov eax, 0x1000
	mov esp, eax    ; 设置初始栈顶
	mov ebp, eax    ; ebp也记录初始栈顶

	extern Entry
	call Entry

	hlt
