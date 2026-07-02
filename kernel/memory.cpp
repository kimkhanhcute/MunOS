#include "memory.h"
#include "vga.h"
#include <stdint.h>

static uint32_t heap_start = 0x200000;
static uint32_t heap_current = 0x200000;
static MemoryBlock* heap_head = 0;
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
    heap_head = 0;
}

void* kmalloc(unsigned int size)
{
    if(size == 0)
        return 0;

    // Tìm block đã free đủ lớn
    MemoryBlock* cur = heap_head;

    while(cur)
    {
        if(cur->free && cur->size >= size)
        {
            cur->free = false;

            print("[kmalloc] Reuse block\n");

            return (void*)(cur + 1);
        }

        cur = cur->next;
    }

    // Không có block phù hợp -> tạo block mới
    MemoryBlock* block = (MemoryBlock*)heap_current;

    block->size = size;
    block->free = false;
    block->next = 0;

    heap_current += sizeof(MemoryBlock);
    heap_current += size;

    if(heap_head == 0)
    {
        heap_head = block;
    }
    else
    {
        cur = heap_head;

        while(cur->next)
            cur = cur->next;

        cur->next = block;
    }

    print("[kmalloc] New block\n");

    return (void*)(block + 1);
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
void kfree(void* ptr)
{
    if(ptr == 0)
        return;

    MemoryBlock* block = ((MemoryBlock*)ptr) - 1;

    block->free = true;

    print("[kfree] Free block\n");
}
