
.globl _start
_start:
    b reset
    b hang
    b hang
    b hang

    b hang
    b hang
    b hang
    b hang

    b hang
    b hang
    b hang
    b hang

    b hang
    b hang
    b hang
    b hang

reset:
    mov sp,#0x20000
    bl notmain
hang:
    b hang

.globl GETPC
GETPC:
    mov r0,pc
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
