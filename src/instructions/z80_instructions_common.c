#include <stdlib.h>
#include <stdio.h>
#include "z80_instructions_common.h"
#include "z80_instructions_main.h"
#include "z80_instructions_extended.h"
#include "z80_instructions_bit.h"
#include "z80_instructions_ix.h"
#include "z80_instructions_iy.h"
#include "flags.h"
#include "bitmath.h"

Z80_Instruction Z80_FetchInstruction(Z80_CPU *z) {
    Z80_Instruction instruction;

    uint8_t op0 = op(z, 0);
    uint8_t op1 = op(z, 1);
    uint8_t op2 = op(z, 2);

    switch (op0) {
        case PREF_EXTD:
            // Extended instruction set
            instruction = FetchExtendedInstruction(op1);
            break;
        case PREF_BIT:
            // Bit instruction set
            instruction = FetchBitInstruction(op1);
            break;
        case PREF_IX:
            if (op1 == PREF_BIT) {
                printf("IX BIT instructions not implemented.\n");
                exit(1);
            }
            else {
                instruction = FetchIXInstruction(op1);
            }
            break;
        case PREF_IY:
            // IY instruction set
            if (op1 == PREF_BIT) {
                printf("IY BIT instructions not implemented.\n");
                exit(1);
            }
            else {
                instruction = FetchIYInstruction(op1);
            }
            break;
        default:
            // Main instruction set
            instruction = FetchMainInstruction(op0);
            break;
    }

    return instruction;
}

void BAD(Z80_CPU *z) {
    printf("INVALID OPCODE: %02X %02X\n", op(z, 0), op(z, 1));
    exit(1);
}

// https://stackoverflow.com/questions/21617970/how-to-check-if-value-has-even-parity-of-bits-or-odd
bool even_parity(uint8_t n) {
    n ^= n >> 4;
    n ^= n >> 2;
    n ^= n >> 1;
    return ((~n) & 1) == 1;
}

// LD operations
void ld_byte(Z80_CPU *cpu, uint8_t *dest, uint8_t src) {
    *dest = src;
}

void ld_word(Z80_CPU *cpu, uint16_t *dest, uint16_t src) {
    *dest = src;
}

// ADD operations
static void add_internal(Z80_CPU *cpu, uint8_t val, bool use_carry) {
    // TODO: Double check the use of the carry flag in the flag logic...
    uint8_t carry_flag = (use_carry && (cpu->F, FLAG_C)) ? 1 : 0;
    uint8_t c_val = val + carry_flag;

    // Set CARRY flag high if 9th bit in sum is high
    flag_set(cpu->F, FLAG_C, ((*cpu->A + c_val) > 0xFF));

    // Always clear ADD/SUB flag
    flag_set(cpu->F, FLAG_N, false);
    
    // If signs are the same and result sign changes, overflow
    if (bit_get(*cpu->A, 7) == bit_get(c_val, 7) && bit_get(*cpu->A + c_val, 7) != bit_get(*cpu->A, 7)) {
        flag_set(cpu->F, FLAG_PV, true);
    }
    // If signs of inputs are different, clear overflow
    else {
        flag_set(cpu->F, FLAG_PV, false);
    }

    // Set HALF-CARRY bit if bit 3 of A and src are both high
    flag_set(cpu->F, FLAG_H, (bit_get(*cpu->A, 3) && bit_get(c_val, 3)));

    // Set ZERO flag if result is 0
    flag_set(cpu->F, FLAG_Z, (((*cpu->A + c_val) & 0xFF) == 0));

    // Set sign flag if bit 7 of the result is 1, indicating a negative number
    flag_set(cpu->F, FLAG_S, bit_get(*cpu->A + c_val, 7));

    // Add source value to A
    *cpu->A += c_val;
}

void add_byte(Z80_CPU *cpu, uint8_t val) {
    add_internal(cpu, val, false);
}

void adc_byte(Z80_CPU *cpu, uint8_t val) {
    add_internal(cpu, val, true);
}

void add_word(Z80_CPU *cpu, uint16_t *target, uint16_t val) {

    // TODO: flags

    (*target) += val;
}

void adc_word(Z80_CPU *cpu, uint16_t *target, uint16_t val) {
    
    // TODO: flags

    (*target) += val;
}

// SUB operations
static void sub_internal(Z80_CPU *cpu, uint8_t val, bool use_carry, bool cp) {
    // TODO: Double check the use of the carry flag in the flag logic...
    uint8_t carry_flag = (use_carry && (cpu->F, FLAG_C)) ? 1 : 0;
    uint8_t c_val = val + carry_flag;

    // Set CARRY flag high if A < val
    flag_set(cpu->F, FLAG_C, (*cpu->A < c_val));

    // Always set ADD/SUB flag
    flag_set(cpu->F, FLAG_N, true);
    
    // If signs are different and result signs changes, overflow
    if (bit_get(*cpu->A, 7) != bit_get(c_val, 7) && bit_get(*cpu->A - c_val, 7) != bit_get(*cpu->A, 7)) {
        flag_set(cpu->F, FLAG_PV, true);
    }
    // If signs of inputs are the same, clear overflow
    else {
        flag_set(cpu->F, FLAG_PV, false);
    }

    // Set HALF-CARRY bit if lower nibble of A is less than lower nibble of val
    flag_set(cpu->F, FLAG_H, ((*cpu->A & 0x0F) < (c_val & 0x0F)));

    // Set ZERO flag if result is 0
    flag_set(cpu->F, FLAG_Z, (((*cpu->A - c_val) & 0xFF) == 0));

    // Set sign flag if bit 7 of the result is 1, indicating a negative number
    flag_set(cpu->F, FLAG_S, bit_get(*cpu->A - c_val, 7));

    if (!cp) {
        // Subtract source from A
        *cpu->A -= c_val;
    }
}

void sub(Z80_CPU *cpu, uint8_t val) {
    sub_internal(cpu, val, false, false);
}

void sbc(Z80_CPU *cpu, uint8_t val) {
    sub_internal(cpu, val, true, false);
}

// AND operations
void and(Z80_CPU *cpu, uint8_t val) {
    flag_set(cpu->F, FLAG_C, false);
    flag_set(cpu->F, FLAG_N, false);
    flag_set(cpu->F, FLAG_H, true);

    // Overflow parity flag is set HIGH if even parity and LOW if odd
    flag_set(cpu->F, FLAG_PV, even_parity(*cpu->A & val));

    // Set ZERO flag if result is 0
    flag_set(cpu->F, FLAG_Z, ((*cpu->A & val) == 0));

    // Set sign flag if bit 7 of the result is 1, indicating a negative number
    flag_set(cpu->F, FLAG_S, bit_get(*cpu->A & val, 7));

    *cpu->A &= val;
}

// OR operations
void or(Z80_CPU *cpu, uint8_t val) {
    flag_set(cpu->F, FLAG_C, false);
    flag_set(cpu->F, FLAG_N, false);
    flag_set(cpu->F, FLAG_H, false);

    // Overflow parity flag is set HIGH if even parity and LOW if odd
    flag_set(cpu->F, FLAG_PV, even_parity(*cpu->A | val));

    // Set ZERO flag if result is 0
    flag_set(cpu->F, FLAG_Z, ((*cpu->A | val) == 0));

    // Set sign flag if bit 7 of the result is 1, indicating a negative number
    flag_set(cpu->F, FLAG_S, bit_get(*cpu->A | val, 7));

    *cpu->A |= val;
}

void xor(Z80_CPU *cpu, uint8_t val) {
    flag_set(cpu->F, FLAG_C, false);
    flag_set(cpu->F, FLAG_N, false);
    flag_set(cpu->F, FLAG_H, false);

    // Overflow parity flag is set HIGH if even parity and LOW if odd
    flag_set(cpu->F, FLAG_PV, even_parity(*cpu->A ^ val));

    // Set ZERO flag if result is 0
    flag_set(cpu->F, FLAG_Z, ((*cpu->A ^ val) == 0));

    // Set sign flag if bit 7 of the result is 1, indicating a negative number
    flag_set(cpu->F, FLAG_S, bit_get(*cpu->A ^ val, 7));

    *cpu->A ^= val;
}

void dec_byte(Z80_CPU *cpu, uint8_t *target) {
    flag_set(cpu->F, FLAG_N, true);
    flag_set(cpu->F, FLAG_PV, false);  // TODO: PV is set if m was 80h before operation; otherwise, reset
    
    // Set HALF-CARRY bit if lower nibble of result is less than lower nibble of starting value
    flag_set(cpu->F, FLAG_H, ((*target & 0x0F) < ((*target - 1) & 0x0F)));     // TODO: check this logic

    // Set ZERO flag if result is 0
    flag_set(cpu->F, FLAG_Z, ((*target - 1) == 0));

    // Set sign flag if bit 7 of the result is 1, indicating a negative number
    flag_set(cpu->F, FLAG_S, bit_get(*target - 1, 7));

    (*target)--;
}

void dec_word(Z80_CPU *cpu, uint16_t *target) {
    (*target)--;
}

void inc_byte(Z80_CPU *cpu, uint8_t *target) {
    flag_set(cpu->F, FLAG_N, false);
    flag_set(cpu->F, FLAG_PV, false);  // TODO: PV is set if m was 7Fh before operation; otherwise, reset
    
    // Set HALF-CARRY bit if lower nibble of result is less than lower nibble of starting value
    flag_set(cpu->F, FLAG_H, ((*target & 0x0F) < ((*target + 1) & 0x0F)));     // TODO: check this logic

    // Set ZERO flag if result is 0
    flag_set(cpu->F, FLAG_Z, ((*target + 1) == 0));

    // Set sign flag if bit 7 of the result is 1, indicating a negative number
    flag_set(cpu->F, FLAG_S, bit_get(*target + 1, 7));

    (*target)++;
}

void inc_word(Z80_CPU *cpu, uint16_t *target) {
    (*target)++;
}

void rlca(Z80_CPU *cpu) {
    uint8_t bit7 = (*cpu->A & 0b10000000) >> 7;
    
    flag_set(cpu->F, FLAG_N, false);
    flag_set(cpu->F, FLAG_H, false);
    
    flag_set(cpu->F, FLAG_C, (bit7 == 1));

    *cpu->A << 1;
    *cpu->A += bit7;
}

void rrca(Z80_CPU *cpu) {
    uint8_t bit0 = *cpu->A & 0b00000001;
    
    flag_set(cpu->F, FLAG_N, false);
    flag_set(cpu->F, FLAG_H, false);
    
    flag_set(cpu->F, FLAG_C, (bit0 == 1));

    *cpu->A >> 1;
    *cpu->A += (bit0 << 7);
}

void rla(Z80_CPU *cpu) {
    // Reset H and N flags
    flag_set(cpu->F, FLAG_N, false);
    flag_set(cpu->F, FLAG_H, false);

    // Current value of the carry flag
    uint8_t old_carry = flag_get(cpu->F, FLAG_C);

    // Set carry flag to the current 7th bit of A
    flag_set(cpu->F, FLAG_C, ((*cpu->A & 0b10000000) >> 7) == 1);

    *cpu->A << 1;

    *cpu->A |= (old_carry & 0x1);
}

void rra(Z80_CPU *cpu) {
    // Reset H and N flags
    flag_set(cpu->F, FLAG_N, false);
    flag_set(cpu->F, FLAG_H, false);

    // Current value of the carry flag
    uint8_t old_carry = flag_get(cpu->F, FLAG_C);

    // Set carry flag to the current 0th bit of A
    flag_set(cpu->F, FLAG_C, (*cpu->A & 0b1) == 1);

    *cpu->A >> 1;

    *cpu->A |= ((old_carry & 0b10000000) << 7);
}

void cp(Z80_CPU *cpu, uint8_t val) {
    sub_internal(cpu, val, false, true);
}

void daa(Z80_CPU *z) {
    // If the lower 4 bits contain non-BCD number or if H flag is set, add 0x06
    if ((*z->A & 0xF) > 9 || flag_get(z->F, FLAG_H)) {
        *z->A += 0x06;
    }

    // If the upper 4 bits contain non-BCD number, then 0x60 is added
    if (((*z->A & 0xF0) >> 4) > 9 || flag_get(z->F, FLAG_C)) {
        *z->A += 0x60;
        // If this second addition is needed, set the carry flag
        flag_set(z->F, FLAG_C, true);
    }
    else {
        // If the second addition was not needed, reset the carry flag
        flag_set(z->F, FLAG_C, false);
    }

    // Overflow parity flag is set HIGH if even parity and LOW if odd
    flag_set(z->F, FLAG_PV, even_parity(*z->A));

    // Set ZERO flag if result is 0
    flag_set(z->F, FLAG_Z, ((*z->A) == 0));

    // Set sign flag if bit 7 of the result is 1, indicating a negative number
    flag_set(z->F, FLAG_S, bit_get(*z->A, 7));

    // TODO: H flag?
    // TODO: do SBC, DEC, and NEG instructions require different behavior here?
}

void ldir(Z80_CPU *z) {
    // TODO: interrupts can fire during this process
    
    flag_set(z->F, FLAG_N, false);
    flag_set(z->F, FLAG_PV, false);
    flag_set(z->F, FLAG_H, false);

    while (*z->BC != 0) {
        // (HL) -> (DE)
        mem_val_set(z, *z->DE, mem_HL(z));

        *z->HL++;
        *z->DE++;
        *z->BC--;
    }
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
