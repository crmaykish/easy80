#include <stdio.h>
#include <string.h>
#include "z80_cpu.h"

/*
LD A,4
INC A
INC A
LD B,10
ADD B
LD (&100),A
RET
*/
uint8_t rom[] = {0x3E, 0x04, 0x3C, 0x3C, 0x06, 0x0A, 0x80, 0x32, 0x00, 0x01, 0xC9};

int main(int argc, char const *argv[])
{
    // printf("%s\n", "Hello Z80!");

    for (int i = 0; i < 256; i++) {
        printf("case 0x%X:  // \n    printf(\"%X : Not Implemented!\\n\");\n    exit(1);\n    break;\n", i, i);
    }

    // Z80_CPU cpu;

    // Z80_CPU_Init(&cpu);

    // Z80_CPU_SetMemory(&cpu, rom, sizeof(rom), 0);

    // while(cpu.Registers.PC < 0xF) {
    //     Z80_CPU_Cycle(&cpu);
    //     Z80_CPU_PrintRegisters(&cpu);
    // }

    return 0;
}
