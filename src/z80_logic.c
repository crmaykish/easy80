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
void add(Z80_CPU *cpu, uint8_t val) {
    // Set CARRY flag high if 9th bit in sum is high
    flag_set(&cpu->F, FLAG_C, ((cpu->A + val) > 0xFF));

    // Always clear ADD/SUB flag
    flag_set(&cpu->F, FLAG_N, false);
    
    // If signs are the same and result sign changes, overflow
    if (bit_get(cpu->A, 7) == bit_get(val, 7) && bit_get(cpu->A + val, 7) != bit_get(cpu->A, 7)) {
        flag_set(&cpu->F, FLAG_PV, true);
    }
    // If signs of inputs are different, clear overflow
    else {
        flag_set(&cpu->F, FLAG_PV, false);
    }

    // Set HALF-CARRY bit if bit 3 of A and src are both high
    flag_set(&cpu->F, FLAG_H, (bit_get(cpu->A, 3) && bit_get(val, 3)));

    // Set ZERO flag if result is 0
    flag_set(&cpu->F, FLAG_Z, (((cpu->A + val) & 0xFF) == 0));

    // Set sign flag if bit 7 of the result is 1, indicating a negative number
    flag_set(&cpu->F, FLAG_S, bit_get(cpu->A + val, 7));

    // Add source value to A
    cpu->A += val;
    
    // All ADD,r operations are a single opcode
    cpu->PC++;
}

// SUB operations
void sub(Z80_CPU *cpu, uint8_t val) {
    // Set CARRY flag high if A < val
    flag_set(&cpu->F, FLAG_C, (cpu->A < val));

    // Always set ADD/SUB flag
    flag_set(&cpu->F, FLAG_N, true);
    
    // If signs are different and result signs changes, overflow
    if (bit_get(cpu->A, 7) != bit_get(val, 7) && bit_get(cpu->A - val, 7) != bit_get(cpu->A, 7)) {
        flag_set(&cpu->F, FLAG_PV, true);
    }
    // If signs of inputs are the same, clear overflow
    else {
        flag_set(&cpu->F, FLAG_PV, false);
    }

    // Set HALF-CARRY bit if lower nibble of A is less than lower nibble of val
    flag_set(&cpu->F, FLAG_H, ((cpu->A & 0x0F) < (val & 0x0F)));

    // Set ZERO flag if result is 0
    flag_set(&cpu->F, FLAG_Z, (((cpu->A - val) & 0xFF) == 0));

    // Set sign flag if bit 7 of the result is 1, indicating a negative number
    flag_set(&cpu->F, FLAG_S, bit_get(cpu->A - val, 7));

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