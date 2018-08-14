#include "z80_logic.h"
#include "z80_flags.h"
#include "bitmath.h"

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
static void sub_internal(Z80_CPU *cpu, uint8_t val, bool use_carry) {
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

    // Subtract source from A
    *cpu->A -= c_val;
}

void sub(Z80_CPU *cpu, uint8_t val) {
    sub_internal(cpu, val, false);
}

void sbc(Z80_CPU *cpu, uint8_t val) {
    sub_internal(cpu, val, true);
}

// AND operations
void and(Z80_CPU *cpu, uint8_t val) {
    flag_set(cpu->F, FLAG_C, false);
    flag_set(cpu->F, FLAG_C, false);
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
    flag_set(cpu->F, FLAG_C, false);
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
    flag_set(cpu->F, FLAG_C, false);
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

}

void rra(Z80_CPU *cpu) {

}