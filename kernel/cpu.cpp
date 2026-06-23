#include "cpu.h"

void cpu_get_vendor(char* vendor)
{
    unsigned int ebx;
    unsigned int edx;
    unsigned int ecx;

    asm volatile(
        "cpuid"
        : "=b"(ebx), "=d"(edx), "=c"(ecx)
        : "a"(0)
    );

    ((unsigned int*)vendor)[0] = ebx;
    ((unsigned int*)vendor)[1] = edx;
    ((unsigned int*)vendor)[2] = ecx;

    vendor[12] = '\0';
}
void cpu_get_brand(char* brand)
{
    unsigned int data[12];

    for(int i = 0; i < 3; i++)
    {
        asm volatile(
            "cpuid"
            : "=a"(data[i * 4]),
              "=b"(data[i * 4 + 1]),
              "=c"(data[i * 4 + 2]),
              "=d"(data[i * 4 + 3])
            : "a"(0x80000002 + i)
        );
    }

    char* ptr = (char*)data;

    for(int i = 0; i < 48; i++)
    {
        brand[i] = ptr[i];
    }

    brand[48] = 0;
}
