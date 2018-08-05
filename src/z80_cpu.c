#include "z80_cpu.h"
#include "string.h"

void Z80_CPU_Init(Z80_CPU *cpu) {
    // CPU to stopped
    cpu->State = STOPPED;

    // Wipe memory
    memset(&cpu->Memory, 0, sizeof(uint8_t) * MAX_ADDRESS);

    // Zero out registers
    Z80_Registers_Init(&cpu->Registers);
}