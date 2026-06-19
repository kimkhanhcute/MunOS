BITS 32

section .multiboot
align 8

MAGIC equ 0xe85250d6
ARCH  equ 0

dd MAGIC
dd ARCH
dd header_end - header_start
dd -(MAGIC + ARCH + (header_end - header_start))

dw 0
dw 0
dd 8

header_start:
header_end:

section .text
global _start
extern kernel_main

_start:
    call kernel_main

.hang:
    cli
    hlt
    jmp .hang
