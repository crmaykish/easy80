#include <stdio.h>
#include <string.h>
#include "z80_cpu.h"

int main(int argc, char const *argv[])
{
    printf("%s\n", "Hello Z80!");

    Z80_CPU cpu;

    Z80_CPU_Init(&cpu);

    return 0;
}
