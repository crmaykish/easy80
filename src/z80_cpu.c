#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "z80_cpu.h"
#include "z80_instructions.h"
#include "bitmath.h"

void Z80_CPU_Init(Z80_CPU *cpu) {
    cpu->Registers = Z80_Registers_Create();

    cpu->A = A(cpu->Registers);
    cpu->B = B(cpu->Registers);
    cpu->C = C(cpu->Registers);
    cpu->D = D(cpu->Registers);
    cpu->E = E(cpu->Registers);
    cpu->F = F(cpu->Registers);
    cpu->H = H(cpu->Registers);
    cpu->L = L(cpu->Registers);

    cpu->AF = AF(cpu->Registers);
    cpu->BC = BC(cpu->Registers);
    cpu->DE = DE(cpu->Registers);
    cpu->HL = HL(cpu->Registers);

    cpu->Ap = Ap(cpu->Registers);
    cpu->Bp = Bp(cpu->Registers);
    cpu->Cp = Cp(cpu->Registers);
    cpu->Dp = Dp(cpu->Registers);
    cpu->Ep = Ep(cpu->Registers);
    cpu->Fp = Fp(cpu->Registers);
    cpu->Hp = Hp(cpu->Registers);
    cpu->Lp = Lp(cpu->Registers);

    cpu->AFp = AFp(cpu->Registers);
    cpu->BCp = BCp(cpu->Registers);
    cpu->DEp = DEp(cpu->Registers);
    cpu->HLp = HLp(cpu->Registers);

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
    
    #if DEBUG
    printf("%02X : %s ", inst.OpCode, inst.Name);

    for(int i = 0; i < (12 - strlen(inst.Name)); i++) {
        printf(" ");
    }

    printf("%02X, %02X ", op(cpu, 1), op(cpu, 2));
    #endif

    inst.Handler(cpu);

    if (inst.Type != OP_JUMP) {
        cpu->PC += inst.Type;
    }
}

void Z80_CPU_PrintRegisters(Z80_CPU *cpu) {
    char flags[9];
    binary_string(flags, *cpu->AF);
    printf(
        "  -->   PC: %04X | AF: %04X | BC: %04X | DE: %04X | HL: %04X | F: %s | SP: %04X\n",
        cpu->PC,
        *cpu->AF,
        *cpu->BC,
        *cpu->DE,
        *cpu->HL,
        flags,
        cpu->SP
    );
}

uint8_t mem_nn(Z80_CPU *z, uint8_t X, uint8_t Y) {
    return z->Memory[combine(X, Y)];
}

uint8_t mem_HL(Z80_CPU *z) {
    return z->Memory[*z->HL];
}

uint8_t op(Z80_CPU *z, uint8_t offset) {
    return z->Memory[z->PC + offset];
}

uint16_t op_nn(Z80_CPU *z) {
    return combine(op(z, 2), op(z, 1));
}

uint8_t mem_val(Z80_CPU *z, uint16_t address) {
    return z->Memory[address];
}

void mem_val_set(Z80_CPU *z, uint16_t address, uint8_t val) {
    z->Memory[address] = val;
}

uint16_t pop(Z80_CPU *z) {
    uint16_t p = combine(mem_val(z, z->SP), mem_val(z, z->SP + 1));
    z->SP += 2;
    return p;
}

void push(Z80_CPU *z, uint16_t val) {
    z->SP -= 2;
    mem_val_set(z, z->SP, split_1(val));
    mem_val_set(z, z->SP + 1, split_2(val));
}

void ret(Z80_CPU *z, bool condition) {
    if (condition) {
        z->PC = pop(z);
    }
    else {
        z->PC += OP_NONE;
    }
}

void call(Z80_CPU *z, uint16_t val, bool condition) {
    if (condition) {
        push(z, z->PC + OP_WORD);
        z->PC = val;
    }
    else {
        z->PC += OP_WORD;
    }
}

void rst(Z80_CPU *z, uint8_t val) {
    push(z, z->PC + OP_NONE);
    z->PC = val;
}

void ex(uint16_t *a, uint16_t *b) {
    uint16_t t = *a;
    *a = *b;
    *b = t;
}

