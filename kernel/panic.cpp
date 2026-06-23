#include "panic.h"
#include "vga.h"

void panic(const char* message)
{
    clear();

    print("=== KERNEL PANIC ===\n\n");
    print(message);
    print("\n");

    while(true)
    {
        asm volatile("cli");
        asm volatile("hlt");
    }
}
