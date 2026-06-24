#include "memory.h"
#include <stdint.h>

static uint32_t heap_start = 0x200000;
static uint32_t heap_current = 0x200000;

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
void memory_init()
{
    heap_current = heap_start;
}

void* kmalloc(unsigned int size)
{
    void* ptr = (void*)heap_current;

    heap_current += size;

    return ptr;
}
unsigned int heap_used()
{
    return heap_current - heap_start;
}
unsigned int heap_free()
{
    return 1024 * 1024 -
           (heap_current - heap_start);
}
