#include "idt.h"

IDTEntry idt[256];
IDTPointer idt_ptr;

extern "C" void idt_load(uint32_t);

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

    idt_load((uint32_t)&idt_ptr);
}
