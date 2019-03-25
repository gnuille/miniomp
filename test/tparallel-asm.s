	.file	"tparallel.c"
	.text
	.section	.rodata.str1.8,"aMS",@progbits,1
	.align 8
.LC0:
	.string	"Thread %d finished the execution of foo\n"
	.text
	.type	foo._omp_fn.3, @function
foo._omp_fn.3:
.LFB17:
	.cfi_startproc
	subq	$8, %rsp
	.cfi_def_cfa_offset 16
	call	omp_get_thread_num@PLT
	movl	%eax, %esi
	leaq	.LC0(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	addq	$8, %rsp
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE17:
	.size	foo._omp_fn.3, .-foo._omp_fn.3
	.type	foo._omp_fn.2, @function
foo._omp_fn.2:
.LFB16:
	.cfi_startproc
	movl	first(%rip), %eax
	addl	$16, %eax
	lock addl	%eax, second(%rip)
	ret
	.cfi_endproc
.LFE16:
	.size	foo._omp_fn.2, .-foo._omp_fn.2
	.type	foo._omp_fn.1, @function
foo._omp_fn.1:
.LFB15:
	.cfi_startproc
	movl	(%rdi), %eax
	incl	%eax
	lock addl	%eax, first(%rip)
	ret
	.cfi_endproc
.LFE15:
	.size	foo._omp_fn.1, .-foo._omp_fn.1
	.type	foo._omp_fn.0, @function
foo._omp_fn.0:
.LFB14:
	.cfi_startproc
	movl	(%rdi), %eax
	incl	%eax
	lock addl	%eax, first(%rip)
	ret
	.cfi_endproc
.LFE14:
	.size	foo._omp_fn.0, .-foo._omp_fn.0
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC1:
	.string	"First parallel region"
.LC2:
	.string	"Second parallel region"
.LC3:
	.string	"Third parallel region"
.LC4:
	.string	"Fourth parallel region"
.LC5:
	.string	"End of function"
	.text
	.globl	foo
	.type	foo, @function
foo:
.LFB12:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	pushq	%rbx
	.cfi_def_cfa_offset 24
	.cfi_offset 3, -24
	subq	$24, %rsp
	.cfi_def_cfa_offset 48
	movl	$40, %ebx
	movq	%fs:(%rbx), %rax
	movq	%rax, 8(%rsp)
	xorl	%eax, %eax
	leaq	.LC1(%rip), %rdi
	call	puts@PLT
	movl	$1023, 4(%rsp)
	leaq	4(%rsp), %rbp
	movl	$0, %ecx
	movl	$2, %edx
	movq	%rbp, %rsi
	leaq	foo._omp_fn.0(%rip), %rdi
	call	GOMP_parallel@PLT
	leaq	.LC2(%rip), %rdi
	call	puts@PLT
	movl	$1023, 4(%rsp)
	movl	$0, %ecx
	movl	$1, %edx
	movq	%rbp, %rsi
	leaq	foo._omp_fn.1(%rip), %rdi
	call	GOMP_parallel@PLT
	leaq	.LC3(%rip), %rdi
	call	puts@PLT
	movl	$0, %ecx
	movl	$0, %edx
	movl	$0, %esi
	leaq	foo._omp_fn.2(%rip), %rdi
	call	GOMP_parallel@PLT
	movl	$6, %edi
	call	omp_set_num_threads@PLT
	leaq	.LC4(%rip), %rdi
	call	puts@PLT
	movl	$0, %ecx
	movl	$0, %edx
	movl	$0, %esi
	leaq	foo._omp_fn.3(%rip), %rdi
	call	GOMP_parallel@PLT
	leaq	.LC5(%rip), %rdi
	call	puts@PLT
	movq	8(%rsp), %rdx
	xorq	%fs:(%rbx), %rdx
	jne	.L9
	movl	$1023, %eax
	addq	$24, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 24
	popq	%rbx
	.cfi_def_cfa_offset 16
	popq	%rbp
	.cfi_def_cfa_offset 8
	ret
.L9:
	.cfi_restore_state
	call	__stack_chk_fail@PLT
	.cfi_endproc
.LFE12:
	.size	foo, .-foo
	.section	.rodata.str1.8
	.align 8
.LC6:
	.string	"first = %d, second = %d, x = %d\n"
	.text
	.globl	main
	.type	main, @function
main:
.LFB13:
	.cfi_startproc
	subq	$8, %rsp
	.cfi_def_cfa_offset 16
	movl	$0, %eax
	call	foo
	movl	%eax, %ecx
	movl	second(%rip), %edx
	movl	first(%rip), %esi
	leaq	.LC6(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	$0, %eax
	addq	$8, %rsp
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE13:
	.size	main, .-main
	.globl	second
	.bss
	.align 4
	.type	second, @object
	.size	second, 4
second:
	.zero	4
	.globl	first
	.align 4
	.type	first, @object
	.size	first, 4
first:
	.zero	4
	.ident	"GCC: (GNU) 8.2.1 20181127"
	.section	.note.GNU-stack,"",@progbits
