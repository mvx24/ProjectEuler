//gcc -arch i386 1.s
.text
	.globl _main

FORMAT: .ascii "%d\12\0"

_main:
	# setup the stack frame
	pushl	%ebp
	movl	%esp, %ebp
	subl	$24, %esp		//int i, int sum, printf function args

	movl	$0, 8(%esp)
	movl	$0, 12(%esp)
loop:
	//if i % 5 == 0
	movl	12(%esp), %eax
	movl	$0, %edx
	movl	$5, %ecx
	divl	%ecx
	cmpl	$0, %edx
	jne		notmod5
	//add i to sum
	movl	12(%esp), %eax
	addl	%eax, 8(%esp)
	jmp		endloop
notmod5:
	//if i % 3 == 0
	movl	12(%esp), %eax
	cltd
	movl	$3, %ecx
	divl	%ecx
	cmpl	$0, %edx
	jne		endloop
	//add i to sum
	movl	12(%esp), %eax
	addl	%eax, 8(%esp)

endloop:
	addl	$1, 12(%esp)
	cmpl	$1000, 12(%esp)
	jl		loop
	
	//print the sum
	movl	$FORMAT, (%esp)
	movl	8(%esp), %eax
	movl	%eax, 4(%esp)
	call	_printf
	movl	$0, %eax
	leave
	ret
