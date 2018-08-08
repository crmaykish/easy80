#include "z80_logic.h"
#include "z80_flags.h"
#include "bitmath.h"

// LD operations
void ld_byte(Z80_CPU *cpu, uint8_t *dest, uint8_t src, uint8_t inc) {
    *dest = src;
    cpu->PC += inc;
}

void ld_word(Z80_CPU *cpu, uint16_t *dest, uint16_t src, uint8_t inc) {
    *dest = src;
    cpu->PC += inc;
}

// ADD operations
void add_r(Z80_CPU *cpu, uint8_t val) {
    // Set CARRY flag high if 9th bit in sum is high
    flag_set(&cpu->F, FLAG_C, ((cpu->A + val) > 0xFF));

    // Always clear ADD/SUB flag
    flag_set(&cpu->F, FLAG_N, false);

    // TODO: Overflow flag

    // Set HALF-CARRY bit if A and src bits 3 are both high
    flag_set(&cpu->F, FLAG_H, (bit_get(cpu->A, 3) && bit_get(val, 3)));

    // Set ZERO flag if result is 0
    flag_set(&cpu->F, FLAG_Z, (cpu->A == 0));

    // TODO: Sign flag

    // Add source value to A
    cpu->A += val;
    
    // All ADD,r operations are a single opcode
    cpu->PC++;
}

// SUB operations
void sub(Z80_CPU *cpu, uint8_t val) {
    // TODO: Set flags

    // Subtract source from A
    cpu->A -= val;

    // All SUB,r operations are a single opcode
    cpu->PC++;
}

// AND operations
void and(Z80_CPU *cpu, uint8_t val) {
    // TODO: Set flags

    cpu->A &= val;

    // All AND,r operations are a single opcode
    cpu->PC++;
}