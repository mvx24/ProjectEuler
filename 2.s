//gcc -arch i386 2.s
.text
	.globl _main

FORMAT: .ascii "%d\12\0"

_main:
	# setup the stack frame
	pushl	%ebp
	movl	%esp, %ebp
	subl	$24, %esp		//int sum(8), printf function args (4),(0)

	movl	$0, 8(%esp)		//sum = 0
	movl	$0, %edi		//prev = 0
	movl	$1, %esi		//current = 1
loop:
	//if current % 2 == 0
	movl	%esi, %eax
	movl	$0, %edx
	movl	$2, %ecx
	divl	%ecx
	cmpl	$0, %edx
	jne		notmod2
	//add current to sum
	addl	%esi, 8(%esp)
notmod2:
	//temp = prev
	movl	%edi, %eax
	//prev = current
	movl	%esi, %edi
	//current += temp
	addl	%eax, %esi

	addl	$1, 12(%esp)
	cmpl	$4000000, %esi
	jl		loop
	
	//print the sum
	movl	$FORMAT, (%esp)
	movl	8(%esp), %eax
	movl	%eax, 4(%esp)
	call	_printf
	movl	$0, %eax
	leave
	ret
