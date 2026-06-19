#include "idt.h"

IDTEntry idt[256];
IDTPointer idt_ptr;

extern "C" void idt_load(uint32_t);
extern "C" void isr0();

void idt_set_gate(
    int num,
    uint32_t base,
    uint16_t sel,
    uint8_t flags)
{
    idt[num].offset_low = base & 0xFFFF;
    idt[num].selector = sel;
    idt[num].zero = 0;
    idt[num].type_attr = flags;
    idt[num].offset_high = (base >> 16) & 0xFFFF;
}

void idt_init()
{
    idt_ptr.limit = sizeof(IDTEntry) * 256 - 1;
    idt_ptr.base = (uint32_t)&idt;

    for(int i = 0; i < 256; i++)
    {
        idt[i].offset_low = 0;
        idt[i].selector = 0x08;
        idt[i].zero = 0;
        idt[i].type_attr = 0x8E;
        idt[i].offset_high = 0;
    }

    idt_set_gate(
        0,
        (uint32_t)isr0,
        0x08,
        0x8E);

    idt_load((uint32_t)&idt_ptr);
}
