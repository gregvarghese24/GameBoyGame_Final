	.cpu arm7tdmi
	.eabi_attribute 20, 1
	.eabi_attribute 21, 1
	.eabi_attribute 23, 3
	.eabi_attribute 24, 1
	.eabi_attribute 25, 1
	.eabi_attribute 26, 1
	.eabi_attribute 30, 2
	.eabi_attribute 34, 0
	.eabi_attribute 18, 4
	.file	"startop.c"
	.text
	.align	2
	.global	initStart
	.syntax unified
	.arm
	.fpu softvfp
	.type	initStart, %function
initStart:
	@ Function supports interworking.
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	mov	r3, #0
	mov	r2, #1
	mov	r1, #16
	mov	ip, #90
	mov	r0, #5
	str	lr, [sp, #-4]!
	ldr	lr, .L4
	str	r3, [lr]
	ldr	lr, .L4+4
	str	r3, [lr]
	ldr	lr, .L4+8
	str	r3, [lr]
	ldr	r3, .L4+12
	ldr	lr, .L4+16
	str	r2, [r3, #8]
	str	r2, [lr]
	str	r2, [r3, #12]
	str	ip, [r3]
	str	r0, [r3, #4]
	str	r1, [r3, #16]
	str	r1, [r3, #20]
	ldr	lr, [sp], #4
	bx	lr
.L5:
	.align	2
.L4:
	.word	option
	.word	hOff
	.word	vOff
	.word	selector
	.word	win
	.size	initStart, .-initStart
	.align	2
	.global	initSelector
	.syntax unified
	.arm
	.fpu softvfp
	.type	initSelector, %function
initSelector:
	@ Function supports interworking.
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	mov	r1, #16
	mov	r2, #1
	mov	ip, #90
	mov	r0, #5
	ldr	r3, .L7
	str	r1, [r3, #16]
	str	r1, [r3, #20]
	str	ip, [r3]
	stmib	r3, {r0, r2}
	str	r2, [r3, #12]
	bx	lr
.L8:
	.align	2
.L7:
	.word	selector
	.size	initSelector, .-initSelector
	.align	2
	.global	updateSelector
	.syntax unified
	.arm
	.fpu softvfp
	.type	updateSelector, %function
updateSelector:
	@ Function supports interworking.
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	ldr	r3, .L18
	ldrh	r3, [r3]
	tst	r3, #32
	beq	.L10
	ldr	r2, .L18+4
	ldrh	r2, [r2]
	tst	r2, #32
	bne	.L10
	ldr	r2, .L18+8
	ldr	r1, [r2, #4]
	ldr	r0, [r2, #12]
	cmp	r1, r0
	blt	.L10
	ldr	r0, .L18+12
	ldr	r3, [r0]
	cmp	r3, #0
	subgt	r1, r1, #40
	subgt	r3, r3, #1
	strgt	r1, [r2, #4]
	strgt	r3, [r0]
	bx	lr
.L10:
	tst	r3, #16
	bxeq	lr
	ldr	r3, .L18+4
	ldrh	r3, [r3]
	tst	r3, #16
	bxne	lr
	ldr	r3, .L18+8
	ldr	r0, [r3, #4]
	ldr	r1, [r3, #16]
	ldr	r2, [r3, #12]
	add	r1, r0, r1
	rsb	r2, r2, #240
	cmp	r1, r2
	bxgt	lr
	ldr	r1, .L18+12
	ldr	r2, [r1]
	cmp	r2, #4
	addle	r0, r0, #40
	addle	r2, r2, #1
	strle	r0, [r3, #4]
	strle	r2, [r1]
	bx	lr
.L19:
	.align	2
.L18:
	.word	oldButtons
	.word	buttons
	.word	selector
	.word	option
	.size	updateSelector, .-updateSelector
	.align	2
	.global	updateStart
	.syntax unified
	.arm
	.fpu softvfp
	.type	updateStart, %function
updateStart:
	@ Function supports interworking.
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	b	updateSelector
	.size	updateStart, .-updateStart
	.align	2
	.global	drawSelector
	.syntax unified
	.arm
	.fpu softvfp
	.type	drawSelector, %function
drawSelector:
	@ Function supports interworking.
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	ldr	r2, .L26
	ldr	r1, .L26+4
	ldr	r3, [r2, #4]
	ldrh	r0, [r1, #48]
	orr	r3, r3, #16384
	lsl	r3, r3, #16
	tst	r0, #32
	lsr	r3, r3, #16
	ldrh	r2, [r2]
	beq	.L25
	ldrh	r1, [r1, #48]
	tst	r1, #16
	beq	.L25
	mov	r0, #0
	ldr	r1, .L26+8
	strh	r0, [r1, #4]	@ movhi
	strh	r2, [r1]	@ movhi
	strh	r3, [r1, #2]	@ movhi
	bx	lr
.L25:
	mov	r0, #64
	ldr	r1, .L26+8
	strh	r0, [r1, #4]	@ movhi
	strh	r2, [r1]	@ movhi
	strh	r3, [r1, #2]	@ movhi
	bx	lr
.L27:
	.align	2
.L26:
	.word	selector
	.word	67109120
	.word	shadowOAM
	.size	drawSelector, .-drawSelector
	.align	2
	.global	drawStart
	.syntax unified
	.arm
	.fpu softvfp
	.type	drawStart, %function
drawStart:
	@ Function supports interworking.
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, lr}
	bl	drawSelector
	ldr	r4, .L30
	mov	r3, #512
	mov	r2, #117440512
	ldr	r1, .L30+4
	mov	r0, #3
	mov	lr, pc
	bx	r4
	pop	{r4, lr}
	bx	lr
.L31:
	.align	2
.L30:
	.word	DMANow
	.word	shadowOAM
	.size	drawStart, .-drawStart
	.comm	vOff,4,4
	.comm	win,4,4
	.comm	hOff,4,4
	.comm	option,4,4
	.comm	selector,52,4
	.ident	"GCC: (devkitARM release 47) 7.1.0"
