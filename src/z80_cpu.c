#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "z80_cpu.h"
#include "z80_flags.h"
#include "z80_instructions.h"
#include "bitmath.h"

uint8_t mem_nn(Z80_CPU *z, uint8_t X, uint8_t Y) {
    return z->Memory[combine(X, Y)];
}

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
    
    printf("%X : %s\n", op.OpCode, op.Name);

    op.Handler(cpu);

    if (op.Operands != OP_JUMP) {
        cpu->PC += op.Operands;
    }
}

void print_binary(uint8_t n) {
    for (int i = 0; i < 8; i++) {
        printf("%d", bit_get(n, i));
    }
    printf("\n");
}

void Z80_CPU_PrintRegisters(Z80_CPU *cpu) {
    printf(
        "PC: %X | AF: %X | BC: %X | DE: %X | HL: %X | F: ",
        cpu->PC,
        combine(cpu->A, cpu->F),
        combine(cpu->B, cpu->C),
        combine(cpu->D, cpu->E),
        combine(cpu->H, cpu->L)
    );
    print_binary(cpu->F);
}