#include "io.h"

unsigned char inb(unsigned short port)
{
    unsigned char result;

    asm volatile(
        "inb %1, %0"
        : "=a"(result)
        : "Nd"(port)
    );

    return result;
}

void outb(
    unsigned short port,
    unsigned char value
)
{
    asm volatile(
        "outb %0, %1"
        :
        : "a"(value),
          "Nd"(port)
    );
}

unsigned short inw(unsigned short port)
{
    unsigned short result;

    asm volatile(
        "inw %1, %0"
        : "=a"(result)
        : "Nd"(port)
    );

    return result;
}

void outw(
    unsigned short port,
    unsigned short value
)
{
    asm volatile(
        "outw %0, %1"
        :
        : "a"(value),
          "Nd"(port)
    );
}
