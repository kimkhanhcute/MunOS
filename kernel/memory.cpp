#include "memory.h"

void* memcpy(void* dst,
             const void* src,
             int size)
{
    unsigned char* d =
        (unsigned char*)dst;

    const unsigned char* s =
        (const unsigned char*)src;

    for(int i = 0; i < size; i++)
    {
        d[i] = s[i];
    }

    return dst;
}

void* memset(void* dst,
             int value,
             int size)
{
    unsigned char* d =
        (unsigned char*)dst;

    for(int i = 0; i < size; i++)
    {
        d[i] = (unsigned char)value;
    }

    return dst;
}

int memcmp(const void* a,
           const void* b,
           int size)
{
    const unsigned char* x =
        (const unsigned char*)a;

    const unsigned char* y =
        (const unsigned char*)b;

    for(int i = 0; i < size; i++)
    {
        if(x[i] != y[i])
        {
            return x[i] - y[i];
        }
    }

    return 0;
}
