#include "speaker.h"
#include "io.h"

void speaker_beep()
{
    unsigned char tmp;

    outb(0x43, 0xB6);

    unsigned short divisor = 1193180 / 1000;

    outb(0x42, divisor & 0xFF);
    outb(0x42, (divisor >> 8) & 0xFF);

    tmp = inb(0x61);

    if((tmp & 3) != 3)
    {
        outb(0x61, tmp | 3);
    }

    for(volatile int i = 0; i < 500000; i++);

    outb(0x61, inb(0x61) & 0xFC);
}
