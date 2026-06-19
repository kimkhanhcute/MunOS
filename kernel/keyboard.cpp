#include "keyboard.h"
#include "io.h"

static char scancode_table[128] =
{
    0,
    27,
    '1','2','3','4','5','6','7','8','9','0',
    '-','=',
    '\b',
    '\t',

    'q','w','e','r','t','y','u','i','o','p',
    '[',']',

    '\n',

    0,

    'a','s','d','f','g','h','j','k','l',
    ';','\'','`',

    0,

    '\\',

    'z','x','c','v','b','n','m',
    ',', '.', '/',

    0,
    '*',
    0,
    ' '
};

char keyboard_getchar()
{
    while(true)
    {
        // Chờ tới khi có dữ liệu mới từ bàn phím
        while(!(inb(0x64) & 1))
        {
        }

        unsigned char scancode = inb(0x60);

        // Bỏ qua key release
        if(scancode & 0x80)
        {
            continue;
        }

        if(scancode < 128)
        {
            char c = scancode_table[scancode];

            if(c)
            {
                return c;
            }
        }
    }
}
