	.file	"ManualNameMangling.cpp"
	.text
#APP
	.globl _ZSt21ios_base_library_initv
#NO_APP
	.globl	_ZN6myname3varE
	.data
	.align 4
	.type	_ZN6myname3varE, @object
	.size	_ZN6myname3varE, 4
_ZN6myname3varE:
	.long	42
	.section	.rodata
.LC0:
	.string	"var = "
.LC1:
	.string	"\n"
	.text
	.globl	main
	.type	main, @function
main:
.LFB1984:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movl	%edi, -4(%rbp)
	movq	%rsi, -16(%rbp)
	movl	$.LC0, %esi
	movl	$_ZSt4cout, %edi
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc
	movq	%rax, %rdx
	movl	_ZN6myname3varE(%rip), %eax
	movl	%eax, %esi
	movq	%rdx, %rdi
	call	_ZNSolsEi
	movl	$.LC1, %esi
	movq	%rax, %rdi
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc
	movl	$0, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE1984:
	.size	main, .-main
	.ident	"GCC: (GNU) 15.1.1 20250521 (Red Hat 15.1.1-2)"
	.section	.note.GNU-stack,"",@progbits
