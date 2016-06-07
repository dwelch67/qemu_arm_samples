

.code 32

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

    bl reset2
    b hang
reset2:
    ldr r0,=notmain
    bx r0

hang:
    b hang

swi:
    push {r4-r12,lr}
    bl swi2
    pop {r4-r12,lr}
    movs pc,lr
swi2:
    ldr r4,=swi_main
    bx r4

gouser:
    ;@ USER 110 10000
    msr cpsr_c,#0xD0
    bl gouser2
    b .
gouser2:    
    bx r0

getmode:
    mrs r0,cpsr
    bx lr


;@ -------------------------------------------------------------------
;@  ARM above THUMB below
;@ -------------------------------------------------------------------

.thumb

;@ assume all addresses branch linked to from thumb code are thumb mode.

.thumb_func
.globl GO_USER
GO_USER:
    ldr r1,=gouser
    bx r1

.thumb_func
.globl GETMODE
GETMODE:
    ldr r0,=getmode
    bx r0

.thumb_func
.globl DO_SWI
DO_SWI:
    push {r4,lr}
    svc 0
    pop {r4,pc}

.thumb_func
.globl GETPC
GETPC:
    mov r0,pc
    bx lr

.thumb_func
.globl GETSP
GETSP:
    mov r0,sp
    bx lr

.thumb_func
.globl PUT32
PUT32:
    str r1,[r0]
    bx lr

.thumb_func
.globl PUT16
PUT16:
    strh r1,[r0]
    bx lr

.thumb_func
.globl PUT8
PUT8:
    strb r1,[r0]
    bx lr

.thumb_func
.globl GET32
GET32:
    ldr r0,[r0]
    bx lr

.thumb_func
.globl GET16
GET16:
    ldrh r0,[r0]
    bx lr

.thumb_func
.globl GET8
GET8:
    ldrb r0,[r0]
    bx lr
