#include <stdio.h>
#include <string.h>
#include "z80_cpu.h"
#include "bitmath.h"

int main(int argc, char const *argv[])
{
    // printf("%s\n", "Hello Z80!");

    for (int i = 0; i <= 0xFF; i++) {
        if (i % 16 == 0) {
            printf("    // 0x%X\n", i);
        }
        printf("    { 0x%X, \"\",          OP_NONE,    0,      &NOP },\n", i);
    }

    // FILE *f;

    // f = fopen(argv[1], "rb");

    // uint8_t rom_data[8192];

    // fread(rom_data, sizeof(rom_data), 1, f);

    // Z80_CPU cpu;

    // Z80_CPU_Init(&cpu);

    // Z80_CPU_SetMemory(&cpu, rom_data, sizeof(rom_data), 0);

    // cpu.State = RUNNING;

    // while(cpu.State == RUNNING) {
    //     Z80_CPU_Cycle(&cpu);
    //     Z80_CPU_PrintRegisters(&cpu);
    // }

    return 0;
}
