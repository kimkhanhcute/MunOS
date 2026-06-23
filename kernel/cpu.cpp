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
