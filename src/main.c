#include <stdio.h>
#include <string.h>
#include "z80_cpu.h"
#include "bitmath.h"

int main(int argc, char const *argv[])
{
    printf("%s\n", "Hello Z80!");

    FILE *f;

    f = fopen(argv[1], "rb");

    uint8_t rom_data[8192];

    fread(rom_data, sizeof(rom_data), 1, f);

    Z80_CPU cpu;

    Z80_CPU_Init(&cpu);

    Z80_CPU_SetMemory(&cpu, rom_data, sizeof(rom_data), 0);

    cpu.State = RUNNING;

    for(int i = 0; i < 10; i++) {
        Z80_CPU_Cycle(&cpu);
        Z80_CPU_PrintRegisters(&cpu);
    }

    return 0;
}
