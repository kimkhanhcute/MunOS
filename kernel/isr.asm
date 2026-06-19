[BITS 32]

global idt_load
global isr0

extern isr0_handler

idt_load:
    mov eax, [esp + 4]
    lidt [eax]
    ret

isr0:
    cli
    call isr0_handler

.hang:
    hlt
    jmp .hang
