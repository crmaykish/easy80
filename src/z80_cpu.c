#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "z80_cpu.h"
#include "z80_instructions_common.h"
#include "bitmath.h"

void Z80_CPU_Init(Z80_CPU *z) {
    z->Registers = Z80_Registers_Create();

    z->A = A(z->Registers);
    z->B = B(z->Registers);
    z->C = C(z->Registers);
    z->D = D(z->Registers);
    z->E = E(z->Registers);
    z->F = F(z->Registers);
    z->H = H(z->Registers);
    z->L = L(z->Registers);

    z->AF = AF(z->Registers);
    z->BC = BC(z->Registers);
    z->DE = DE(z->Registers);
    z->HL = HL(z->Registers);

    z->Ap = Ap(z->Registers);
    z->Bp = Bp(z->Registers);
    z->Cp = Cp(z->Registers);
    z->Dp = Dp(z->Registers);
    z->Ep = Ep(z->Registers);
    z->Fp = Fp(z->Registers);
    z->Hp = Hp(z->Registers);
    z->Lp = Lp(z->Registers);

    z->AFp = AFp(z->Registers);
    z->BCp = BCp(z->Registers);
    z->DEp = DEp(z->Registers);
    z->HLp = HLp(z->Registers);

    // Clear memory
    memset(&z->Memory, 0, sizeof(uint8_t) * MAX_RAM_ADDRESS);

    // CPU is not yet running
    z->State = STOPPED;

    // Interrupts are disabled
    z->Interrupts = false;
}

void Z80_CPU_Destroy(Z80_CPU *z) {
    Z80_Registers_Destroy(z->Registers);
}

void Z80_CPU_SetMemory(Z80_CPU *z, uint8_t data[], size_t size, uint16_t offset) {
    // TODO: bounds checking on Memory array
    memcpy(&z->Memory[offset], data, size);
}

void Z80_CPU_Cycle(Z80_CPU *z) {
    Z80_Instruction inst = Z80_FetchInstruction(z);
    
    printf("%02X : %s ", inst.OpCode, inst.Name);

    for(int i = 0; i < (12 - strlen(inst.Name)); i++) {
        printf(" ");
    }

    printf("%02X, %02X ", Op(z, 1), Op(z, 2));

    inst.Handler(z);

    if (inst.Type != OP_JUMP) {
        // JUMP instructions handle the program counter on their own
        // Everything else increases the PC by the opcode size
        z->PC += inst.Type;
    }
}

void Z80_CPU_PrintRegisters(Z80_CPU *z) {
    char flags[9];
    binary_string(flags, *z->AF);
    printf(
        "  -->   PC: %04X | AF: %04X | BC: %04X | DE: %04X | HL: %04X | F: %s | SP: %04X\n",
        z->PC,
        *z->AF,
        *z->BC,
        *z->DE,
        *z->HL,
        flags,
        z->SP
    );
}

uint8_t Op(Z80_CPU *z, uint8_t offset) {
    return GetMemVal(z, z->PC + offset);
}

uint16_t op_nn(Z80_CPU *z) {
    return combine(Op(z, 2), Op(z, 1));
}

uint8_t GetMemVal(Z80_CPU *z, uint16_t address) {
    return z->Memory[address];
}

void SetMemVal(Z80_CPU *z, uint16_t address, uint8_t val) {
    z->Memory[address] = val;
}