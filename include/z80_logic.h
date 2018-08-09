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

// LD operations
void ld_byte(Z80_CPU *cpu, uint8_t *dest, uint8_t src, uint8_t inc);
void ld_word(Z80_CPU *cpu, uint16_t *dest, uint16_t src, uint8_t inc);

// ADD operations
void add(Z80_CPU *cpu, uint8_t val);

// SUB operations
void sub(Z80_CPU *cpu, uint8_t val);

// AND operations
void and(Z80_CPU *cpu, uint8_t val);

#endif