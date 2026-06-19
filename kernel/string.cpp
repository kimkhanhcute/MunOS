#include "string.h"

bool strcmp(const char* a, const char* b)
{
    int i = 0;

    while(a[i] && b[i])
    {
        if(a[i] != b[i])
            return false;

        i++;
    }

    return a[i] == b[i];
}

int strlen(const char* str)
{
    int len = 0;

    while(str[len])
    {
        len++;
    }

    return len;
}

bool starts_with(
    const char* str,
    const char* prefix
)
{
    int i = 0;

    while(prefix[i])
    {
        if(str[i] != prefix[i])
            return false;

        i++;
    }

    return true;
}
void int_to_string(
    int value,
    char* buffer
)
{
    if(value == 0)
    {
        buffer[0] = '0';
        buffer[1] = 0;
        return;
    }

    char temp[16];
    int pos = 0;

    while(value > 0)
    {
        temp[pos++] =
            '0' + (value % 10);

        value /= 10;
    }

    int i;

    for(i = 0; i < pos; i++)
    {
        buffer[i] =
            temp[pos - i - 1];
    }

    buffer[i] = 0;
}
