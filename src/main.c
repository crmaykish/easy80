#include <stdio.h>
#include <string.h>
#include "z80_cpu.h"
#include "bitmath.h"

// only for exit()
#include <stdlib.h>

int main(int argc, char const *argv[])
{
    FILE *f;
    f = fopen("/home/colin/Downloads/CPM/zexdoc.com", "rb");

    uint8_t rom_data[8192];

    fread(rom_data, sizeof(rom_data), 1, f);

    Z80_CPU cpu;

    Z80_CPU_Init(&cpu);

    // Start the program at 0x100
    Z80_CPU_SetMemory(&cpu, rom_data, sizeof(rom_data), 0x100);

    // Set stack pointer out of range of the zexdoc code
    cpu.SP = 0xF000;

    // Set PC to start at the zexdoc code
    cpu.PC = 0x0100;

    

    printf("Hit <ENTER> to single-step through the ROM. Ctrl-C to exit.\n");

    cpu.State = RUNNING;

    while(cpu.State == RUNNING) {
        getchar();
        Z80_CPU_Cycle(&cpu);
        Z80_CPU_PrintRegisters(&cpu);


        if (cpu.PC == 0x05){
            // CP/M function call
            if (*cpu.C == 0x02) {
                // output the value in E as ASCII code
                printf("CP/M: %c", *cpu.E);
            }
            else if (*cpu.C == 0x09) {
                // read bytes starting at address DE until '$' and then output them as ASCII
                printf("CP/M: ");

                char c = '\0';
                int i = 0;
                while (c != '$') {
                    printf("%c", c);
                    c = mem_val(&cpu, *cpu.DE + i);
                    i++;
                }

            }
            else {
                printf("Unknown CP/M function. Abort!\n");
                exit(1);
            }

            // return to zexdoc code
            cpu.PC = pop(&cpu);
        }

    }

    return 0;
}
