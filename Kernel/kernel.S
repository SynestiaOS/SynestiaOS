
kernel:	file format ELF32-arm-little

Disassembly of section .text:
exception_vector_table:
; ldr pc, _reset_addr
    8000:	18 f0 9f e5 	ldr	pc, [pc, #24]
; ldr pc, _undefined_instruction_addr
    8004:	18 f0 9f e5 	ldr	pc, [pc, #24]
; ldr pc, _software_interrupt_addr
    8008:	18 f0 9f e5 	ldr	pc, [pc, #24]
; ldr pc, _prefetch_abort_addr
    800c:	18 f0 9f e5 	ldr	pc, [pc, #24]
; ldr pc, _data_abort_addr
    8010:	18 f0 9f e5 	ldr	pc, [pc, #24]
; ldr pc, _unused_addr
    8014:	18 f0 9f e5 	ldr	pc, [pc, #24]
; ldr pc, _interrupt_addr
    8018:	18 f0 9f e5 	ldr	pc, [pc, #24]
; ldr pc, _fast_interrupt_addr
    801c:	18 f0 9f e5 	ldr	pc, [pc, #24]

_reset_addr:
    8020:	94 80 00 00 	.word	0x00008094

_undefined_instruction_addr:
    8024:	a8 85 00 00 	andeq	r8, r0, r8, lsr #11

_software_interrupt_addr:
    8028:	ac 85 00 00 	andeq	r8, r0, r12, lsr #11

_prefetch_abort_addr:
    802c:	b8 85 00 00 	strheq	r8, [r0], -r8

_data_abort_addr:
    8030:	bc 85 00 00 	strheq	r8, [r0], -r12

_unused_addr:
    8034:	c0 85 00 00 	andeq	r8, r0, r0, asr #11

_interrupt_addr:
    8038:	c4 85 00 00 	andeq	r8, r0, r4, asr #11

_fast_interrupt_addr:
    803c:	c8 85 00 00 	andeq	r8, r0, r8, asr #11

init_stack:
; mrs r0, cpsr
    8040:	00 00 0f e1 	mrs	r0, apsr
; bic r0,     #0x1F
    8044:	1f 00 c0 e3 	bic	r0, r0, #31
; orr r0,     #0x13
    8048:	13 00 80 e3 	orr	r0, r0, #19
; msr cpsr_c, r0
    804c:	00 f0 21 e1 	msr	CPSR_c, r0
; ldr r1,=__svc_stack
    8050:	60 10 9f e5 	ldr	r1, [pc, #96]
; bic sp, r1, #0x7
    8054:	07 d0 c1 e3 	bic	sp, r1, #7
; bic r0,     #0x1F
    8058:	1f 00 c0 e3 	bic	r0, r0, #31
; orr r0,     #0x12
    805c:	12 00 80 e3 	orr	r0, r0, #18
; msr cpsr_c, r0
    8060:	00 f0 21 e1 	msr	CPSR_c, r0
; ldr r1,=__irq_stack
    8064:	50 10 9f e5 	ldr	r1, [pc, #80]
; bic sp, r1, #0x7
    8068:	07 d0 c1 e3 	bic	sp, r1, #7
; bic r0,     #0x1F
    806c:	1f 00 c0 e3 	bic	r0, r0, #31
; orr r0,     #0x11
    8070:	11 00 80 e3 	orr	r0, r0, #17
; msr cpsr_c, r0
    8074:	00 f0 21 e1 	msr	CPSR_c, r0
; ldr r1,=__fiq_stack
    8078:	40 10 9f e5 	ldr	r1, [pc, #64]
; bic sp, r1, #0x7
    807c:	07 d0 c1 e3 	bic	sp, r1, #7
; bic r0,     #0x1F
    8080:	1f 00 c0 e3 	bic	r0, r0, #31
; orr r0,     #0x10
    8084:	10 00 80 e3 	orr	r0, r0, #16
; msr cpsr_c, r0
    8088:	00 f0 21 e1 	msr	CPSR_c, r0
; ldr r1,=__sys_stack
    808c:	30 10 9f e5 	ldr	r1, [pc, #48]
; bic sp, r1, #0x7
    8090:	07 d0 c1 e3 	bic	sp, r1, #7

reset_handler:
; push    {r4, r5, r6, r7, r8, r9}
    8094:	f0 03 2d e9 	push	{r4, r5, r6, r7, r8, r9}
; ldr     r0, =exception_vector_table
    8098:	28 00 9f e5 	ldr	r0, [pc, #40]
; mov     r1, #0x0000
    809c:	00 10 a0 e3 	mov	r1, #0
; ldmia   r0!,{r2, r3, r4, r5, r6, r7, r8, r9}
    80a0:	fc 03 b0 e8 	ldm	r0!, {r2, r3, r4, r5, r6, r7, r8, r9}
; stmia   r1!,{r2, r3, r4, r5, r6, r7, r8, r9}
    80a4:	fc 03 a1 e8 	stm	r1!, {r2, r3, r4, r5, r6, r7, r8, r9}
; ldmia   r0!,{r2, r3, r4, r5, r6, r7, r8}
    80a8:	fc 01 b0 e8 	ldm	r0!, {r2, r3, r4, r5, r6, r7, r8}
; stmia   r1!,{r2, r3, r4, r5, r6, r7, r8}
    80ac:	fc 01 a1 e8 	stm	r1!, {r2, r3, r4, r5, r6, r7, r8}
; pop     {r4, r5, r6, r7, r8, r9}
    80b0:	f0 03 bd e8 	pop	{r4, r5, r6, r7, r8, r9}
; blx     lr
    80b4:	3e ff 2f e1 	blx	lr

$d:
    80b8:	00 30 01 00 	.word	0x00013000
    80bc:	00 b0 01 00 	.word	0x0001b000
    80c0:	00 30 02 00 	.word	0x00023000
    80c4:	00 b0 02 00 	.word	0x0002b000
    80c8:	00 80 00 00 	.word	0x00008000

_start:
; mrc p15, #0, r1, c0, c0, #5
    80cc:	b0 1f 10 ee 	mrc	p15, #0, r1, c0, c0, #5
; and r1, r1, #3
    80d0:	03 10 01 e2 	and	r1, r1, #3
; cmp r1, #0
    80d4:	00 00 51 e3 	cmp	r1, #0
; bne _halt_smp
    80d8:	04 00 00 1a 	bne	#16 <_halt_smp>
; ldr sp, =__sys_stack
    80dc:	14 d0 9f e5 	ldr	sp, [pc, #20]
; ldr r0, =__bss_start
    80e0:	14 00 9f e5 	ldr	r0, [pc, #20]
; ldr r1, =__bss_end
    80e4:	14 10 9f e5 	ldr	r1, [pc, #20]
; bl clean_bss
    80e8:	37 01 00 eb 	bl	#1244 <clean_bss>
; bl kernel_main
    80ec:	41 01 00 eb 	bl	#1284 <kernel_main>

_halt_smp:
; wfi // wait for interrup coming
    80f0:	03 f0 20 e3 	wfi
; b _halt_smp
    80f4:	fd ff ff ea 	b	#-12 <_halt_smp>

$d:
    80f8:	00 b0 02 00 	.word	0x0002b000
    80fc:	00 a0 00 00 	.word	0x0000a000
    8100:	00 b0 00 00 	.word	0x0000b000

uart_init:
; void uart_init(void) {
    8104:	10 40 2d e9 	push	{r4, lr}
; io_writel(0, (void *) (UART0_BASE + UART_CR_OFFSET));
    8108:	30 40 01 e3 	movw	r4, #4144
    810c:	20 4f 43 e3 	movt	r4, #16160
    8110:	00 00 a0 e3 	mov	r0, #0
    8114:	04 10 a0 e1 	mov	r1, r4
    8118:	fa 00 00 eb 	bl	#1000 <io_writel>
; io_writel(0x7ff, (void *) (UART0_BASE + UART_ICR_OFFSET));
    811c:	44 10 01 e3 	movw	r1, #4164
    8120:	ff 07 00 e3 	movw	r0, #2047
    8124:	20 1f 43 e3 	movt	r1, #16160
    8128:	f6 00 00 eb 	bl	#984 <io_writel>
; io_writel(1, (void *) (UART0_BASE + UART_IBRD_OFFSET));
    812c:	24 10 01 e3 	movw	r1, #4132
    8130:	01 00 a0 e3 	mov	r0, #1
    8134:	20 1f 43 e3 	movt	r1, #16160
    8138:	f2 00 00 eb 	bl	#968 <io_writel>
; io_writel(40, (void *) (UART0_BASE + UART_FBRD_OFFSET));
    813c:	28 10 01 e3 	movw	r1, #4136
    8140:	28 00 a0 e3 	mov	r0, #40
    8144:	20 1f 43 e3 	movt	r1, #16160
    8148:	ee 00 00 eb 	bl	#952 <io_writel>
; io_writel((1 << 4) | (1 << 5) | (1 << 6), (void *) (UART0_BASE + UART_LCRH_OFFSET));
    814c:	2c 10 01 e3 	movw	r1, #4140
    8150:	70 00 a0 e3 	mov	r0, #112
    8154:	20 1f 43 e3 	movt	r1, #16160
    8158:	ea 00 00 eb 	bl	#936 <io_writel>
; io_writel((1 << 1) | (1 << 4) | (1 << 5) | (1 << 6) | (1 << 7) | (1 << 8) | (1 << 9) | (1 << 10),
    815c:	38 10 01 e3 	movw	r1, #4152
    8160:	f2 07 00 e3 	movw	r0, #2034
    8164:	20 1f 43 e3 	movt	r1, #16160
    8168:	e6 00 00 eb 	bl	#920 <io_writel>
; io_writel((1 << 0) | (1 << 8) | (1 << 9), (void *) (UART0_BASE + UART_CR_OFFSET));
    816c:	04 10 a0 e1 	mov	r1, r4
    8170:	01 03 00 e3 	movw	r0, #769
; }
    8174:	10 40 bd e8 	pop	{r4, lr}
; io_writel((1 << 0) | (1 << 8) | (1 << 9), (void *) (UART0_BASE + UART_CR_OFFSET));
    8178:	e2 00 00 ea 	b	#904 <io_writel>

uart_putc:
; void uart_putc(uint8_t ch) {
    817c:	70 40 2d e9 	push	{r4, r5, r6, lr}
; while (io_readl((void *) (UART0_BASE + UART_FR_OFFSET)) & (1 << 5));
    8180:	18 40 01 e3 	movw	r4, #4120
    8184:	20 4f 43 e3 	movt	r4, #16160
; void uart_putc(uint8_t ch) {
    8188:	00 50 a0 e1 	mov	r5, r0
; while (io_readl((void *) (UART0_BASE + UART_FR_OFFSET)) & (1 << 5));
    818c:	04 00 a0 e1 	mov	r0, r4
    8190:	e2 00 00 eb 	bl	#904 <io_readl>
    8194:	20 00 10 e3 	tst	r0, #32
    8198:	fb ff ff 1a 	bne	#-20 <uart_putc+0x10>
; io_writel(ch, (void *) (UART0_BASE + UART_DR_OFFSET));
    819c:	01 1a a0 e3 	mov	r1, #4096
    81a0:	05 00 a0 e1 	mov	r0, r5
    81a4:	20 1f 43 e3 	movt	r1, #16160
; }
    81a8:	70 40 bd e8 	pop	{r4, r5, r6, lr}
; io_writel(ch, (void *) (UART0_BASE + UART_DR_OFFSET));
    81ac:	d5 00 00 ea 	b	#852 <io_writel>

memcpy:
; void memcpy(void *dest, const void *src, int bytes) {
    81b0:	00 00 52 e3 	cmp	r2, #0
; char *d = dest;
    81b4:	1e ff 2f 01 	bxeq	lr
; while (bytes--) {
    81b8:	02 20 81 e0 	add	r2, r1, r2
    81bc:	01 00 40 e2 	sub	r0, r0, #1
; *d++ = *s++;
    81c0:	01 30 d1 e4 	ldrb	r3, [r1], #1
; while (bytes--) {
    81c4:	02 00 51 e1 	cmp	r1, r2
; *d++ = *s++;
    81c8:	01 30 e0 e5 	strb	r3, [r0, #1]!
; while (bytes--) {
    81cc:	fb ff ff 1a 	bne	#-20 <memcpy+0x10>
    81d0:	1e ff 2f e1 	bx	lr

memset:
; void memset(void *dest, uint8_t c, int bytes) {
    81d4:	00 00 52 e3 	cmp	r2, #0
; uint8_t *d = dest;
    81d8:	1e ff 2f 01 	bxeq	lr
; while (bytes--) {
    81dc:	02 20 80 e0 	add	r2, r0, r2
; *d++ = c;
    81e0:	01 10 c0 e4 	strb	r1, [r0], #1
; while (bytes--) {
    81e4:	00 00 52 e1 	cmp	r2, r0
    81e8:	fc ff ff 1a 	bne	#-16 <memset+0xc>
    81ec:	1e ff 2f e1 	bx	lr

bzero:
; void bzero(void *dest, int bytes) {
    81f0:	01 20 a0 e1 	mov	r2, r1
; memset(dest, 0, bytes);
    81f4:	00 10 a0 e3 	mov	r1, #0
    81f8:	f5 ff ff ea 	b	#-44 <memset>

itoa:
    81fc:	00 00 50 e3 	cmp	r0, #0
; char *itoa(int num, int base) {
    8200:	04 e0 2d e5 	str	lr, [sp, #-4]!
; if (num == 0) {
    8204:	27 00 00 0a 	beq	#156 <itoa+0xac>
; char *itoa(int num, int base) {
    8208:	a0 0f a0 e1 	lsr	r0, r0, #31
; if (base == 10 && num < 0) {
    820c:	0a 00 51 e3 	cmp	r1, #10
    8210:	00 30 a0 13 	movne	r3, #0
    8214:	01 30 00 02 	andeq	r3, r0, #1
    8218:	00 00 53 e3 	cmp	r3, #0
    821c:	1c 00 00 1a 	bne	#112 <itoa+0x98>
; if (base == 16) {
    8220:	10 00 51 e3 	cmp	r1, #16
    8224:	24 00 00 1a 	bne	#144 <itoa+0xc0>
; intbuf[j++] = 'x';
    8228:	e4 30 9f e5 	ldr	r3, [pc, #228]
    822c:	78 c0 a0 e3 	mov	r12, #120
    8230:	78 20 03 e3 	movw	r2, #12408
    8234:	03 30 8f e0 	add	r3, pc, r3
    8238:	b0 20 c3 e1 	strh	r2, [r3]
; intbuf[j] = '\0';
    823c:	d4 30 9f e5 	ldr	r3, [pc, #212]
    8240:	30 00 a0 e3 	mov	r0, #48
; j--;
    8244:	01 e0 a0 e3 	mov	lr, #1
; intbuf[j] = '\0';
    8248:	00 20 a0 e3 	mov	r2, #0
    824c:	03 30 8f e0 	add	r3, pc, r3
    8250:	02 20 c3 e5 	strb	r2, [r3, #2]
; j--;
    8254:	c0 20 9f e5 	ldr	r2, [pc, #192]
; intbuf[j] = '\0';
    8258:	0e 30 a0 e1 	mov	r3, lr
    825c:	02 20 8f e0 	add	r2, pc, r2
    8260:	0e 10 82 e0 	add	r1, r2, lr
    8264:	01 00 00 ea 	b	#4 <itoa+0x74>
    8268:	00 c0 d2 e5 	ldrb	r12, [r2]
    826c:	00 00 d1 e5 	ldrb	r0, [r1]
; isneg = intbuf[i];
    8270:	01 00 c2 e4 	strb	r0, [r2], #1
; intbuf[j] = isneg;
    8274:	01 30 43 e2 	sub	r3, r3, #1
; while (i < j) {
    8278:	03 00 4e e0 	sub	r0, lr, r3
    827c:	03 00 50 e1 	cmp	r0, r3
; intbuf[j] = isneg;
    8280:	01 c0 41 e4 	strb	r12, [r1], #-1
; i++;
    8284:	f7 ff ff 3a 	blo	#-36 <itoa+0x6c>
; while (i < j) {
    8288:	90 00 9f e5 	ldr	r0, [pc, #144]
    828c:	00 00 8f e0 	add	r0, pc, r0
; }
    8290:	04 f0 9d e4 	ldr	pc, [sp], #4
; isneg = 1;
    8294:	88 30 9f e5 	ldr	r3, [pc, #136]
; intbuf[j++] = '-';
    8298:	2d 20 a0 e3 	mov	r2, #45
    829c:	03 30 8f e0 	add	r3, pc, r3
    82a0:	b0 20 c3 e1 	strh	r2, [r3]
; j--;
    82a4:	f7 ff ff ea 	b	#-36 <itoa+0x8c>
; while (i < j) {
    82a8:	78 30 9f e5 	ldr	r3, [pc, #120]
; intbuf[0] = '0';
    82ac:	30 20 a0 e3 	mov	r2, #48
    82b0:	03 30 8f e0 	add	r3, pc, r3
    82b4:	b0 20 c3 e1 	strh	r2, [r3]
; return intbuf;
    82b8:	f2 ff ff ea 	b	#-56 <itoa+0x8c>
; } else if (base == 8) {
    82bc:	08 00 51 e3 	cmp	r1, #8
    82c0:	04 00 00 1a 	bne	#16 <itoa+0xdc>
; intbuf[j++] = '0';
    82c4:	60 30 9f e5 	ldr	r3, [pc, #96]
    82c8:	30 20 a0 e3 	mov	r2, #48
    82cc:	03 30 8f e0 	add	r3, pc, r3
    82d0:	b0 20 c3 e1 	strh	r2, [r3]
; j--;
    82d4:	eb ff ff ea 	b	#-84 <itoa+0x8c>
; } else if (base == 2) {
    82d8:	02 00 51 e3 	cmp	r1, #2
    82dc:	05 00 00 1a 	bne	#20 <itoa+0xfc>
; intbuf[j++] = 'b';
    82e0:	48 30 9f e5 	ldr	r3, [pc, #72]
    82e4:	62 20 03 e3 	movw	r2, #12386
    82e8:	62 c0 a0 e3 	mov	r12, #98
    82ec:	03 30 8f e0 	add	r3, pc, r3
    82f0:	b0 20 c3 e1 	strh	r2, [r3]
    82f4:	d0 ff ff ea 	b	#-192 <itoa+0x40>
; intbuf[j] = '\0';
    82f8:	34 20 9f e5 	ldr	r2, [pc, #52]
    82fc:	03 c0 a0 e1 	mov	r12, r3
    8300:	00 e0 e0 e3 	mvn	lr, #0
    8304:	02 20 8f e0 	add	r2, pc, r2
    8308:	01 00 52 e5 	ldrb	r0, [r2, #-1]
    830c:	00 30 c2 e5 	strb	r3, [r2]
; j--;
    8310:	cf ff ff ea 	b	#-196 <itoa+0x58>

$d:
    8314:	c4 1d 00 00 	.word	0x00001dc4
    8318:	ac 1d 00 00 	.word	0x00001dac
    831c:	9c 1d 00 00 	.word	0x00001d9c
    8320:	6c 1d 00 00 	.word	0x00001d6c
    8324:	5c 1d 00 00 	.word	0x00001d5c
    8328:	48 1d 00 00 	.word	0x00001d48
    832c:	2c 1d 00 00 	.word	0x00001d2c
    8330:	0c 1d 00 00 	.word	0x00001d0c
    8334:	f4 1c 00 00 	.word	0x00001cf4

atoi:
; int atoi(char *num) {
    8338:	70 40 2d e9 	push	{r4, r5, r6, lr}
; while (*num >= '0' && *num <= '9') {
    833c:	00 30 d0 e5 	ldrb	r3, [r0]
    8340:	30 30 43 e2 	sub	r3, r3, #48
    8344:	09 00 53 e3 	cmp	r3, #9
    8348:	1a 00 00 8a 	bhi	#104 <atoi+0x80>
    834c:	00 20 a0 e1 	mov	r2, r0
; num++;
    8350:	02 50 a0 e1 	mov	r5, r2
; while (*num >= '0' && *num <= '9') {
    8354:	01 30 f2 e5 	ldrb	r3, [r2, #1]!
    8358:	30 30 43 e2 	sub	r3, r3, #48
    835c:	09 00 53 e3 	cmp	r3, #9
    8360:	fa ff ff 9a 	bls	#-24 <atoi+0x18>
; num--;
    8364:	05 00 50 e1 	cmp	r0, r5
; while (num != start) {
    8368:	16 00 00 0a 	beq	#88 <atoi+0x90>
; digit = *num - '0';
    836c:	01 10 52 e5 	ldrb	r1, [r2, #-1]
; int res = 0, power = 0, digit, i;
    8370:	00 40 a0 e3 	mov	r4, #0
    8374:	00 60 45 e0 	sub	r6, r5, r0
; digit *= 10;
    8378:	0a e0 a0 e3 	mov	lr, #10
; digit = *num - '0';
    837c:	30 10 41 e2 	sub	r1, r1, #48
; for (i = 0; i < power; i++) {
    8380:	04 00 a0 e1 	mov	r0, r4
; res += digit;
    8384:	01 00 80 e0 	add	r0, r0, r1
; power++;
    8388:	04 c0 a0 e1 	mov	r12, r4
    838c:	01 40 84 e2 	add	r4, r4, #1
; num--;
    8390:	06 00 54 e1 	cmp	r4, r6
; while (num != start) {
    8394:	70 80 bd 08 	popeq	{r4, r5, r6, pc}
; digit = *num - '0';
    8398:	01 10 75 e5 	ldrb	r1, [r5, #-1]!
; for (i = 0; i < power; i++) {
    839c:	00 20 a0 e3 	mov	r2, #0
; digit = *num - '0';
    83a0:	30 10 41 e2 	sub	r1, r1, #48
; for (i = 0; i < power; i++) {
    83a4:	02 00 5c e1 	cmp	r12, r2
    83a8:	01 20 82 e2 	add	r2, r2, #1
; digit *= 10;
    83ac:	9e 01 01 e0 	mul	r1, lr, r1
; for (i = 0; i < power; i++) {
    83b0:	fb ff ff 1a 	bne	#-20 <atoi+0x6c>
    83b4:	f2 ff ff ea 	b	#-56 <atoi+0x4c>
    83b8:	01 50 40 e2 	sub	r5, r0, #1
; while (*num >= '0' && *num <= '9') {
    83bc:	00 20 a0 e1 	mov	r2, r0
; num--;
    83c0:	05 00 50 e1 	cmp	r0, r5
; while (num != start) {
    83c4:	e8 ff ff 1a 	bne	#-96 <atoi+0x34>
; int res = 0, power = 0, digit, i;
    83c8:	00 00 a0 e3 	mov	r0, #0
    83cc:	70 80 bd e8 	pop	{r4, r5, r6, pc}

putc:
; void putc(char c) {
    83d0:	69 ff ff ea 	b	#-604 <uart_putc>

puts:
; uart_putc(c);
    83d4:	10 40 2d e9 	push	{r4, lr}
; void puts(const char *str) {
    83d8:	00 40 a0 e1 	mov	r4, r0
; for (i = 0; str[i] != '\0'; i++) {
    83dc:	00 00 d0 e5 	ldrb	r0, [r0]
    83e0:	00 00 50 e3 	cmp	r0, #0
    83e4:	10 80 bd 08 	popeq	{r4, pc}
; putc(str[i]);
    83e8:	f8 ff ff eb 	bl	#-32 <putc>
; for (i = 0; str[i] != '\0'; i++) {
    83ec:	01 00 f4 e5 	ldrb	r0, [r4, #1]!
    83f0:	00 00 50 e3 	cmp	r0, #0
    83f4:	fb ff ff 1a 	bne	#-20 <puts+0x14>
    83f8:	10 80 bd e8 	pop	{r4, pc}

print:
; void print(const char *str) {
    83fc:	10 40 2d e9 	push	{r4, lr}
    8400:	00 40 a0 e1 	mov	r4, r0
; while (*str) {
    8404:	00 00 d0 e5 	ldrb	r0, [r0]
    8408:	00 00 50 e3 	cmp	r0, #0
    840c:	10 80 bd 08 	popeq	{r4, pc}
; putc(*str);
    8410:	ee ff ff eb 	bl	#-72 <putc>
; str++;
    8414:	01 00 f4 e5 	ldrb	r0, [r4, #1]!
; while (*str) {
    8418:	00 00 50 e3 	cmp	r0, #0
    841c:	fb ff ff 1a 	bne	#-20 <print+0x14>
    8420:	10 80 bd e8 	pop	{r4, pc}

printf:
; void printf(const char *fmt, ...) {
    8424:	0f 00 2d e9 	push	{r0, r1, r2, r3}
    8428:	10 40 2d e9 	push	{r4, lr}
    842c:	08 d0 4d e2 	sub	sp, sp, #8
; va_start(args, fmt);
    8430:	14 30 8d e2 	add	r3, sp, #20
; void printf(const char *fmt, ...) {
    8434:	10 40 9d e5 	ldr	r4, [sp, #16]
; va_start(args, fmt);
    8438:	04 30 8d e5 	str	r3, [sp, #4]
; for (; *fmt != '\0'; fmt++) {
    843c:	00 00 d4 e5 	ldrb	r0, [r4]
    8440:	00 00 50 e3 	cmp	r0, #0
    8444:	14 00 00 1a 	bne	#80 <printf+0x78>
    8448:	1a 00 00 ea 	b	#104 <printf+0x94>
; switch (*(++fmt)) {
    844c:	01 30 d4 e5 	ldrb	r3, [r4, #1]
    8450:	01 40 84 e2 	add	r4, r4, #1
    8454:	73 00 53 e3 	cmp	r3, #115
    8458:	1f 00 00 0a 	beq	#124 <printf+0xb8>
    845c:	19 00 00 8a 	bhi	#100 <printf+0xa4>
    8460:	25 00 53 e3 	cmp	r3, #37
    8464:	0e 00 00 0a 	beq	#56 <printf+0x80>
; puts(itoa(va_arg(args,
    8468:	64 00 53 e3 	cmp	r3, #100
    846c:	0a 10 a0 03 	moveq	r1, #10
    8470:	04 30 9d 05 	ldreq	r3, [sp, #4]
; switch (*(++fmt)) {
    8474:	04 00 00 1a 	bne	#16 <printf+0x68>
; puts(itoa(va_arg(args,
    8478:	00 00 93 e5 	ldr	r0, [r3]
    847c:	04 30 83 e2 	add	r3, r3, #4
    8480:	04 30 8d e5 	str	r3, [sp, #4]
    8484:	5c ff ff eb 	bl	#-656 <itoa>
    8488:	d1 ff ff eb 	bl	#-188 <puts>
; break;
    848c:	01 00 d4 e5 	ldrb	r0, [r4, #1]
; for (; *fmt != '\0'; fmt++) {
    8490:	01 40 84 e2 	add	r4, r4, #1
    8494:	00 00 50 e3 	cmp	r0, #0
    8498:	06 00 00 0a 	beq	#24 <printf+0x94>
; if (*fmt == '%') {
    849c:	25 00 50 e3 	cmp	r0, #37
    84a0:	e9 ff ff 0a 	beq	#-92 <printf+0x28>
; } else putc(*fmt);
    84a4:	01 40 84 e2 	add	r4, r4, #1
    84a8:	c8 ff ff eb 	bl	#-224 <putc>
; for (; *fmt != '\0'; fmt++) {
    84ac:	00 00 d4 e5 	ldrb	r0, [r4]
    84b0:	00 00 50 e3 	cmp	r0, #0
    84b4:	f8 ff ff 1a 	bne	#-32 <printf+0x78>
; }
    84b8:	08 d0 8d e2 	add	sp, sp, #8
    84bc:	10 40 bd e8 	pop	{r4, lr}
    84c0:	10 d0 8d e2 	add	sp, sp, #16
    84c4:	1e ff 2f e1 	bx	lr
; puts(itoa(va_arg(args,
    84c8:	78 00 53 e3 	cmp	r3, #120
    84cc:	10 10 a0 03 	moveq	r1, #16
    84d0:	04 30 9d 05 	ldreq	r3, [sp, #4]
; switch (*(++fmt)) {
    84d4:	e7 ff ff 0a 	beq	#-100 <printf+0x54>
    84d8:	eb ff ff ea 	b	#-84 <printf+0x68>
; puts(va_arg(args,
    84dc:	04 30 9d e5 	ldr	r3, [sp, #4]
    84e0:	00 00 93 e5 	ldr	r0, [r3]
    84e4:	04 30 83 e2 	add	r3, r3, #4
    84e8:	04 30 8d e5 	str	r3, [sp, #4]
    84ec:	b8 ff ff eb 	bl	#-288 <puts>
; break;
    84f0:	e5 ff ff ea 	b	#-108 <printf+0x68>

init_bsp:
; void init_bsp(void){
    84f4:	02 ff ff ea 	b	#-1016 <uart_init>

io_writeb:
; void io_writeb(uint8_t val, void *addr) { *(uint8_t *)addr = val; }
    84f8:	00 00 c1 e5 	strb	r0, [r1]
    84fc:	1e ff 2f e1 	bx	lr

io_writew:
; void io_writew(uint16_t val, void *addr) { *(uint16_t *)addr = val; }
    8500:	b0 00 c1 e1 	strh	r0, [r1]
    8504:	1e ff 2f e1 	bx	lr

io_writel:
; void io_writel(uint32_t val, void *addr) { *(uint32_t *)addr = val; }
    8508:	00 00 81 e5 	str	r0, [r1]
    850c:	1e ff 2f e1 	bx	lr

io_readb:
; uint8_t io_readb(void *addr) { return *(uint8_t *)addr; }
    8510:	00 00 d0 e5 	ldrb	r0, [r0]
    8514:	1e ff 2f e1 	bx	lr

io_readw:
; uint16_t io_readw(void *addr) { return *(uint16_t *)addr; }
    8518:	b0 00 d0 e1 	ldrh	r0, [r0]
    851c:	1e ff 2f e1 	bx	lr

io_readl:
; uint32_t io_readl(void *addr) { return *(uint32_t *)addr; }
    8520:	00 00 90 e5 	ldr	r0, [r0]
    8524:	1e ff 2f e1 	bx	lr

enable_interrupt:
; void enable_interrupt(){
    8528:	80 00 08 f1 	cpsie	i
; }
    852c:	1e ff 2f e1 	bx	lr

init_interrupt:
; void init_interrupt() {
    8530:	fc ff ff ea 	b	#-16 <enable_interrupt>

disable_interrupt:
; void disable_interrupt(){
    8534:	80 00 0c f1 	cpsid	i
; }
    8538:	1e ff 2f e1 	bx	lr

swi:
; void swi(uint32_t num){
    853c:	00 00 a0 e1 	mov	r0, r0
; __asm__ __volatile__("swi 0x0");
    8540:	00 00 00 ef 	svc	#0
; }
    8544:	1e ff 2f e1 	bx	lr

getIRQController:
; rpi_irq_controller_t* getIRQController(void){
    8548:	b2 0c a0 e3 	mov	r0, #45568
; }
    854c:	00 0e 47 e3 	movt	r0, #32256
    8550:	1e ff 2f e1 	bx	lr

helloswi:
; void helloswi() {
    8554:	30 40 2d e9 	push	{r4, r5, lr}
    8558:	14 d0 4d e2 	sub	sp, sp, #20
    855c:	0f 50 8d e2 	add	r5, sp, #15
; disable_interrupt();
    8560:	f3 ff ff eb 	bl	#-52 <disable_interrupt>
; const char str[] = "hello swi\n\0";
    8564:	38 30 9f e5 	ldr	r3, [pc, #56]
    8568:	04 c0 8d e2 	add	r12, sp, #4
    856c:	0c 40 a0 e1 	mov	r4, r12
    8570:	03 30 8f e0 	add	r3, pc, r3
    8574:	07 00 93 e8 	ldm	r3, {r0, r1, r2}
    8578:	68 30 a0 e3 	mov	r3, #104
    857c:	07 00 8c e8 	stm	r12, {r0, r1, r2}
; uint32_t i;
    8580:	00 00 00 ea 	b	#0 <helloswi+0x34>
; for (i = 0; i < sizeof(str); i++) {
    8584:	01 30 f4 e5 	ldrb	r3, [r4, #1]!
; uart_putc(str[i]);
    8588:	03 00 a0 e1 	mov	r0, r3
    858c:	fa fe ff eb 	bl	#-1048 <uart_putc>
; for (i = 0; i < sizeof(str); i++) {
    8590:	05 00 54 e1 	cmp	r4, r5
    8594:	fa ff ff 1a 	bne	#-24 <helloswi+0x30>
; enable_interrupt();
    8598:	14 d0 8d e2 	add	sp, sp, #20
; }
    859c:	30 40 bd e8 	pop	{r4, r5, lr}
; enable_interrupt();
    85a0:	e0 ff ff ea 	b	#-128 <enable_interrupt>

$d:
    85a4:	88 0a 00 00 	.word	0x00000a88

undefined_instruction_handler:
; void __attribute__((interrupt("UNDEF"))) undefined_instruction_handler(void){
    85a8:	0e f0 b0 e1 	movs	pc, lr

software_interrupt_handler:
; void __attribute__((interrupt("SWI"))) software_interrupt_handler(void){
    85ac:	0f 50 2d e9 	push	{r0, r1, r2, r3, r12, lr}
; helloswi();
    85b0:	e7 ff ff eb 	bl	#-100 <helloswi>
; }
    85b4:	0f 90 fd e8 	ldm	sp!, {r0, r1, r2, r3, r12, pc} ^

prefetch_abort_handler.localalias:
; void __attribute__((interrupt("ABORT"))) prefetch_abort_handler(void){
    85b8:	04 f0 5e e2 	subs	pc, lr, #4

data_abort_handler:
; }
    85bc:	04 f0 5e e2 	subs	pc, lr, #4

unused_handler:
; void unused_handler(void){
    85c0:	1e ff 2f e1 	bx	lr

interrupt_handler:
; void __attribute__((interrupt("IRQ"))) interrupt_handler(void){
    85c4:	04 f0 5e e2 	subs	pc, lr, #4

fast_interrupt_handler:
; void __attribute__((interrupt("FIQ"))) fast_interrupt_handler(void){
    85c8:	04 f0 5e e2 	subs	pc, lr, #4

clean_bss:
; void clean_bss(uint8_t *start, uint8_t *end) {
    85cc:	01 00 50 e1 	cmp	r0, r1
; for (i = 0; start + i < end; i++) {
    85d0:	1e ff 2f 21 	bxhs	lr
; *(start + i) = '\0';
    85d4:	00 30 a0 e3 	mov	r3, #0
    85d8:	01 30 c0 e4 	strb	r3, [r0], #1
; for (i = 0; start + i < end; i++) {
    85dc:	01 00 50 e1 	cmp	r0, r1
    85e0:	fc ff ff 1a 	bne	#-16 <clean_bss+0xc>
    85e4:	1e ff 2f e1 	bx	lr

print_splash:
; void print_splash() {
    85e8:	04 00 9f e5 	ldr	r0, [pc, #4]
; print(str);
    85ec:	00 00 8f e0 	add	r0, pc, r0
    85f0:	81 ff ff ea 	b	#-508 <print>

$d:
    85f4:	18 0a 00 00 	.word	0x00000a18

kernel_main:
; void kernel_main(void) {
    85f8:	10 40 2d e9 	push	{r4, lr}
; init_bsp();
    85fc:	bc ff ff eb 	bl	#-272 <init_bsp>
; init_stack();
    8600:	8e fe ff eb 	bl	#-1480 <init_stack>
; print_splash();
    8604:	f7 ff ff eb 	bl	#-36 <print_splash>
; init_interrupt();
    8608:	c8 ff ff eb 	bl	#-224 <init_interrupt>
; swi(1);
    860c:	10 40 bd e8 	pop	{r4, lr}
    8610:	01 00 a0 e3 	mov	r0, #1
    8614:	c8 ff ff ea 	b	#-224 <swi>
