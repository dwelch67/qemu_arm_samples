
.global _start
_start:
    mov sp,#0x8000
    bl notmain
    wfi
    b .

.thumb
.thumb_func
.globl PUT32
PUT32:
    str r1,[r0]
    bx lr

.thumb_func
.globl GETPC
GETPC:
    mov r0,pc
    bx lr
    
