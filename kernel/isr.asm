[BITS 32]

global idt_load
global isr0
global irq0

extern isr0_handler
extern irq0_handler

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

irq0:
    pushad

    call irq0_handler

    popad

    mov al, 0x20
    out 0x20, al

    iret
