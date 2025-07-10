	.cpu cortex-m3
	.arch armv7-m
	.fpu softvfp
	.eabi_attribute 20, 1
	.eabi_attribute 21, 1
	.eabi_attribute 23, 3
	.eabi_attribute 24, 1
	.eabi_attribute 25, 1
	.eabi_attribute 26, 1
	.eabi_attribute 30, 6
	.eabi_attribute 34, 1
	.eabi_attribute 18, 4
	.file	"main.c"
	.text
	.global	vector_table
	.section	.isr_vector,"a"// tells assembler that .isr_vector is 'allocatable'
	.align	2 //aligns the next label (v_t) to 2^n (2^2 = 4) making .size 8
	.type	vector_table, %object
	.size	vector_table, 8
vector_table:
	.word	_stack_top
	.word	Reset_Handler
	.text
	.align	1
	.global	Reset_Handler //makes r_h visibale to the linker
	.syntax unified
	.thumb
	.thumb_func
	.type	Reset_Handler, %function
Reset_Handler:
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	push	{r7, lr}
	sub	sp, sp, #8
	add	r7, sp, #0
	ldr	r3, .L6
	ldr	r3, [r3]
	str	r3, [r7, #4]
	ldr	r3, .L6+4
	ldr	r3, [r3]
	str	r3, [r7]
	b	.L2
.L3:
	ldr	r2, [r7, #4]
	adds	r3, r2, #4
	str	r3, [r7, #4]
	ldr	r3, [r7]
	adds	r1, r3, #4
	str	r1, [r7]
	ldr	r2, [r2]
	str	r2, [r3]
.L2:
	ldr	r3, .L6+8
	ldr	r3, [r3]
	ldr	r2, [r7]
	cmp	r2, r3
	bcc	.L3
	ldr	r3, .L6+12
	ldr	r3, [r3]
	str	r3, [r7]
	b	.L4
.L5:
	ldr	r3, [r7]
	adds	r2, r3, #4
	str	r2, [r7]
	movs	r2, #0
	str	r2, [r3]
.L4:
	ldr	r3, .L6+16
	ldr	r3, [r3]
	ldr	r2, [r7]
	cmp	r2, r3
	bcc	.L5
	bl	main
	nop
	adds	r7, r7, #8
	mov	sp, r7
	@ sp needed
	pop	{r7, pc}
.L7:
	.align	2
.L6:
	.word	_data_load_start
	.word	_data_start
	.word	_data_end
	.word	_bss_start
	.word	_bss_end
	.size	Reset_Handler, .-Reset_Handler
	.ident	"GCC: (GNU) 15.1.0"
