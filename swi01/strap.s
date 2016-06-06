
.globl _start
_start:
    ldr pc,reset_handler
    ldr pc,undefined_handler
    ldr pc,swi_handler
    ldr pc,prefetch_handler
    ldr pc,data_handler
    ldr pc,unused_handler
    ldr pc,irq_handler
    ldr pc,fiq_handler
reset_handler:      .word reset
undefined_handler:  .word hang
swi_handler:        .word swi
prefetch_handler:   .word hang
data_handler:       .word hang
unused_handler:     .word hang
irq_handler:        .word hang
fiq_handler:        .word hang

reset:
    mov r0,#0x10000
    mov r1,#0x00000
    ldmia r0!,{r2,r3,r4,r5,r6,r7,r8,r9}
    stmia r1!,{r2,r3,r4,r5,r6,r7,r8,r9}
    ldmia r0!,{r2,r3,r4,r5,r6,r7,r8,r9}
    stmia r1!,{r2,r3,r4,r5,r6,r7,r8,r9}

    ;@ FIQ 110 10001
    msr cpsr_c,#0xD1
    mov sp,#0x1000

    ;@ IRQ 110 10010
    msr cpsr_c,#0xD2
    mov sp,#0x2000

    ;@ SVC 110 10011
    msr cpsr_c,#0xD3
    mov sp,#0x3000

    ;@ ABT 110 10111
    msr cpsr_c,#0xD7
    mov sp,#0x4000

    ;@ UND 110 11011
    msr cpsr_c,#0xDB
    mov sp,#0x5000

    ;@ SYS 110 11111
    msr cpsr_c,#0xDF
    mov sp,#0x6000



    ;@ SVC 110 10011
    msr cpsr_c,#0xD3


    bl notmain
hang:
    b hang

swi:
    push {r4-r12,lr}
    bl swi_main
    pop {r4-r12,lr}
    movs pc,lr

.globl DO_SWI
DO_SWI:
    push {lr}
    svc 0
    pop {lr}
    bx lr

.globl GO_USER
GO_USER:
    ;@ USER 110 10000
    msr cpsr_c,#0xD0
    bl gouser
    b .
gouser:
    bx r0

.globl GETMODE
GETMODE:
    mrs r0,cpsr
    bx lr

.globl GETPC
GETPC:
    mov r0,pc
    bx lr

.globl GETSP
GETSP:
    mov r0,sp
    bx lr

.globl PUT32
PUT32:
    str r1,[r0]
    bx lr

.globl PUT16
PUT16:
    strh r1,[r0]
    bx lr

.globl PUT8
PUT8:
    strb r1,[r0]
    bx lr

.globl GET32
GET32:
    ldr r0,[r0]
    bx lr

.globl GET16
GET16:
    ldrh r0,[r0]
    bx lr

.globl GET8
GET8:
    ldrb r0,[r0]
    bx lr
