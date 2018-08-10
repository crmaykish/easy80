#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "z80_cpu.h"
#include "z80_instructions.h"
#include "bitmath.h"

void Z80_CPU_Init(Z80_CPU *cpu) {
    // Zero all registers
    cpu->A = cpu->B = cpu->C = cpu->D = cpu->E = cpu->F = 0;
    cpu->Ap = cpu->Bp = cpu->Cp = cpu->Dp = cpu->Ep = cpu->Fp = 0;
    cpu->IX = cpu->IY = 0;
    cpu->I = cpu->R = 0;
    cpu->PC = 0;
    cpu->SP = 0;

    // Clear memory
    memset(&cpu->Memory, 0, sizeof(uint8_t) * MAX_RAM_ADDRESS);

    // CPU is not yet running
    cpu->State = STOPPED;
}

void Z80_CPU_SetMemory(Z80_CPU *cpu, uint8_t data[], size_t size, uint16_t offset) {
    // TODO: bounds checking on Memory array
    memcpy(&cpu->Memory[offset], data, size);
}

void Z80_CPU_Cycle(Z80_CPU *cpu) {
    Z80_Instruction op = Z80_FetchInstruction(cpu);
    
    printf("Fetched: %X : %s\n", op.OpCode, op.Name);

    op.Handler(cpu);

    if (op.Operands != OP_JUMP) {
        cpu->PC += op.Operands;
    }
}

void Z80_CPU_PrintRegisters(Z80_CPU *cpu) {
    char flags[9];
    binary_string(flags, cpu->F);
    printf(
        "PC: %02X | AF: %02X | BC: %02X | DE: %02X | HL: %02X | F: %s\n",
        cpu->PC,
        combine(cpu->A, cpu->F),
        combine(cpu->B, cpu->C),
        combine(cpu->D, cpu->E),
        combine(cpu->H, cpu->L),
        flags
    );
}

uint8_t mem_nn(Z80_CPU *z, uint8_t X, uint8_t Y) {
    return z->Memory[combine(X, Y)];
}

uint8_t mem_HL(Z80_CPU *z) {
    return mem_nn(z, z->H, z->L);
}

uint8_t op(Z80_CPU *z, uint8_t offset) {
    return z->Memory[z->PC + offset];
}