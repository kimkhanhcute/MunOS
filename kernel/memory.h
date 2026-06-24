#pragma once

void* memcpy(void* dst,
             const void* src,
             int size);

void* memset(void* dst,
             int value,
             int size);

int memcmp(const void* a,
           const void* b,
           int size);

void memory_init();

void* kmalloc(unsigned int size);
unsigned int heap_used();
unsigned int heap_free();
