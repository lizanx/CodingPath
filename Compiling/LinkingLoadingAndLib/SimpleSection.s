	.file	"SimpleSection.c"
	.text
	.globl	func1                           # -- Begin function func1
	.p2align	4
	.type	func1,@function
func1:                                  # @func1
	.cfi_startproc
# %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	subq	$16, %rsp
	movl	%edi, -4(%rbp)
	movl	-4(%rbp), %esi
	movabsq	$.L.str, %rdi
	movb	$0, %al
	callq	printf
	addq	$16, %rsp
	popq	%rbp
	.cfi_def_cfa %rsp, 8
	retq
.Lfunc_end0:
	.size	func1, .Lfunc_end0-func1
	.cfi_endproc
                                        # -- End function
	.globl	main                            # -- Begin function main
	.p2align	4
	.type	main,@function
main:                                   # @main
	.cfi_startproc
# %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	subq	$16, %rsp
	movl	$0, -4(%rbp)
	movl	$1, -8(%rbp)
	movl	main.static_var, %edi
	addl	main.static_var2, %edi
	addl	-8(%rbp), %edi
	addl	-12(%rbp), %edi
	callq	func1
	movl	-8(%rbp), %eax
	addq	$16, %rsp
	popq	%rbp
	.cfi_def_cfa %rsp, 8
	retq
.Lfunc_end1:
	.size	main, .Lfunc_end1-main
	.cfi_endproc
                                        # -- End function
	.type	global_init_var,@object         # @global_init_var
	.data
	.globl	global_init_var
	.p2align	2, 0x0
global_init_var:
	.long	84                              # 0x54
	.size	global_init_var, 4

	.type	.L.str,@object                  # @.str
	.section	.rodata.str1.1,"aMS",@progbits,1
.L.str:
	.asciz	"%d\n"
	.size	.L.str, 4

	.type	main.static_var,@object         # @main.static_var
	.data
	.p2align	2, 0x0
main.static_var:
	.long	85                              # 0x55
	.size	main.static_var, 4

	.type	main.static_var2,@object        # @main.static_var2
	.local	main.static_var2
	.comm	main.static_var2,4,4
	.type	global_uninit_var,@object       # @global_uninit_var
	.bss
	.globl	global_uninit_var
	.p2align	2, 0x0
global_uninit_var:
	.long	0                               # 0x0
	.size	global_uninit_var, 4

	.ident	"clang version 20.1.6 (Fedora 20.1.6-1.fc42)"
	.section	".note.GNU-stack","",@progbits
	.addrsig
	.addrsig_sym func1
	.addrsig_sym printf
	.addrsig_sym main.static_var
	.addrsig_sym main.static_var2
