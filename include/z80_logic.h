/**
 * @brief General logic used by the Z80 by various individual instructions
 * 
 * @file z80_logic.h
 * @author crmaykish
 * @date 2018-08-07
 */

#ifndef Z80_LOGIC_H
#define Z80_LOGIC_H

#include "z80_cpu.h"
#include "z80_flags.h"

bool even_parity(uint8_t n);

// LD operations
void ld_byte(Z80_CPU *cpu, uint8_t *dest, uint8_t src);
void ld_word(Z80_CPU *cpu, uint16_t *dest, uint16_t src);

// ADD operations
void add_byte(Z80_CPU *cpu, uint8_t val);
void add_word(Z80_CPU *cpu, uint16_t *target, uint16_t val);
void adc_byte(Z80_CPU *cpu, uint8_t val);
void adc_word(Z80_CPU *cpu, uint16_t *target, uint16_t val);

// SUB operations
void sub(Z80_CPU *cpu, uint8_t val);
void sbc(Z80_CPU *cpu, uint8_t val);

// AND operations
void and(Z80_CPU *cpu, uint8_t val);

// OR operations
void or(Z80_CPU *cpu, uint8_t val);

// XOR operations
void xor(Z80_CPU *cpu, uint8_t val);

// DEC operations
void dec_byte(Z80_CPU *cpu, uint8_t *target);
void dec_word(Z80_CPU *cpu, uint16_t *target);

// INC operations
void inc_byte(Z80_CPU *cpu, uint8_t *target);
void inc_word(Z80_CPU *cpu, uint16_t *target);

// ROTATE operations
void rlca(Z80_CPU *cpu);
void rrca(Z80_CPU *cpu);
void rla(Z80_CPU *cpu);
void rra(Z80_CPU *cpu);

// CP operations
void cp(Z80_CPU *cpu, uint8_t val);

// DAA operations
void daa(Z80_CPU *z);

void ldir(Z80_CPU *z);

#endif