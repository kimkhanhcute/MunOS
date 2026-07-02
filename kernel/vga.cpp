#include "vga.h"

static volatile unsigned short* VGA =
    (unsigned short*)0xB8000;

static int row = 0;
static int col = 0;

static const unsigned char color = 0x0F;

void scroll()
{
    for(int y = 1; y < 25; y++)
    {
        for(int x = 0; x < 80; x++)
        {
            VGA[(y - 1) * 80 + x] =
                VGA[y * 80 + x];
        }
    }

    for(int x = 0; x < 80; x++)
    {
        VGA[24 * 80 + x] =
            (color << 8) | ' ';
    }

    row = 24;
}

void clear()
{
    for(int y = 0; y < 25; y++)
    {
        for(int x = 0; x < 80; x++)
        {
            VGA[y * 80 + x] =
                (color << 8) | ' ';
        }
    }

    row = 0;
    col = 0;
}

void putchar(char c)
{
    if(c == '\n')
    {
        row++;
        col = 0;

        if(row >= 25)
        {
            scroll();
        }

        return;
    }

    if(c == '\b')
    {
        if(col > 0)
        {
            col--;

            VGA[row * 80 + col] =
                (color << 8) | ' ';
        }

        return;
    }

    VGA[row * 80 + col] =
        (color << 8) | c;

    col++;

    if(col >= 80)
    {
        col = 0;
        row++;

        if(row >= 25)
        {
            scroll();
        }
    }
}

void print(const char* str)
{
    while(*str)
    {
        putchar(*str++);
    }
}

void print_char(char c)
{
    putchar(c);
}
void print_hex(unsigned int value)
{
    const char* hex = "0123456789ABCDEF";

    print("0x");

    for(int i = 28; i >= 0; i -= 4)
    {
        print_char(hex[(value >> i) & 0xF]);
    }
}
