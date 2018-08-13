#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "z80_cpu.h"
#include "z80_instructions.h"
#include "bitmath.h"

void Z80_CPU_Init(Z80_CPU *cpu) {
    // Zero all registers
    cpu->AF.w = 0x0000;
    cpu->BC.w = 0x0000;
    cpu->DE.w = 0x0000;
    cpu->HL.w = 0x0000;
    cpu->AFp.w = 0x0000;
    cpu->BCp.w = 0x0000;
    cpu->DEp.w = 0x0000;
    cpu->HLp.w = 0x0000;
    cpu->IX = 0;
    cpu->IY = 0;
    cpu->I = 0;
    cpu->R = 0;
    cpu->PC = 0;
    cpu->SP = 0;

    cpu->AF = &cpu->Registers.AF_reg.w;

    cpu->A = &cpu->AF.b.high;
    cpu->F = &cpu->AF.b.low;

    cpu->B = &cpu->BC.b.high;
    cpu->C = &cpu->BC.b.low;

    cpu->D = &cpu->DE.b.high;
    cpu->E = &cpu->DE.b.low;

    cpu->H = &cpu->HL.b.high;
    cpu->L = &cpu->HL.b.low;

    // Clear memory
    memset(&cpu->Memory, 0, sizeof(uint8_t) * MAX_RAM_ADDRESS);

    // CPU is not yet running
    cpu->State = STOPPED;

    // Interrupts are disabled
    cpu->Interrupts = false;
}

void Z80_CPU_SetMemory(Z80_CPU *cpu, uint8_t data[], size_t size, uint16_t offset) {
    // TODO: bounds checking on Memory array
    memcpy(&cpu->Memory[offset], data, size);
}

void Z80_CPU_Cycle(Z80_CPU *cpu) {
    Z80_Instruction inst = Z80_FetchInstruction(cpu);
    
    printf("%02X : %s ", inst.OpCode, inst.Name);

    for(int i = 0; i < (12 - strlen(inst.Name)); i++) {
        printf(" ");
    }

    printf("%02X, %02X ", op(cpu, 1), op(cpu, 2));

    inst.Handler(cpu);

    if (inst.Operands != OP_JUMP) {
        cpu->PC += inst.Operands;
    }
}

void Z80_CPU_PrintRegisters(Z80_CPU *cpu) {
    char flags[9];
    binary_string(flags, cpu->AF.b.high);
    printf(
        "  -->   PC: %04X | AF: %04X | BC: %04X | DE: %04X | HL: %04X | F: %s\n",
        cpu->PC,
        cpu->AF.w,
        cpu->BC.w,
        cpu->DE.w,
        cpu->HL.w,
        flags
    );
}

uint8_t mem_nn(Z80_CPU *z, uint8_t X, uint8_t Y) {
    return z->Memory[combine(X, Y)];
}

uint8_t mem_HL(Z80_CPU *z) {
    return z->Memory[z->HL.w];
}

uint8_t op(Z80_CPU *z, uint8_t offset) {
    return z->Memory[z->PC + offset];
}