#include <stdio.h>
#include <string.h>
#include "z80_cpu.h"

uint8_t rom1[] = {0x3E, 0xA9, 0x06, 0xBF, 0x48, 0x57, 0x76};

int main(int argc, char const *argv[])
{
    printf("%s\n", "Hello Z80!");

    Z80_CPU cpu;

    Z80_CPU_Init(&cpu);

    Z80_CPU_SetMemory(&cpu, rom1, sizeof(rom1), 0);

    cpu.State = RUNNING;

    while(cpu.State == RUNNING) {
        Z80_CPU_Cycle(&cpu);
        Z80_CPU_PrintRegisters(&cpu);
    }

    return 0;
}
