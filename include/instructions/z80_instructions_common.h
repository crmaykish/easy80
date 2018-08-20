/**
 * @brief Z80 Instruction declarations
 * 
 * @file z80_instructions_common.h
 * @author crmaykish
 * @date 2018-08-09
 */
#ifndef Z80_INSTRUCTIONS_COMMON_H
#define Z80_INSTRUCTIONS_COMMON_H

#include "z80_cpu.h"

#define PREF_EXTD   0xED    /*!< Extended instruction set */
#define PREF_BIT    0xCB    /*!< BIT instruction set */
#define PREF_IX     0xDD    /*!< IX instruction set */
#define PREF_IY     0xFD    /*!< IY instruction set */

/**
 * @brief Defines the length of the different opcode types and how they effect the Program Counter
 */
typedef enum {
    OP_NONE = 1,    /*!< Opcode with no operands */
    OP_BYTE = 2,    /*!< Opcode with a single operand */
    OP_WORD = 3,    /*!< Opcode with two operands or a single 16-bit operand */
    OP_LONG = 4,    /*!< Opcode that takes up 4 bytes */    // TODO: bad name
    OP_JUMP         /*!< Instruction will manage the PC on its own */
} Z80_OpCodeType;

/**
 * @brief Defines a type of Z80 CPU instruction and its behavior
 */
typedef struct Z80_Instruction {
    uint8_t OpCode;                 /*!< Opcode of the instruction, for extended instructions, this does not include the prefix */
    char *Name;                     /*!< Assembly language name of the instruction, e.g. `LD A,n` or `POP BC` */
    Z80_OpCodeType Type;            /*!< Type of opcode - effecting PC behavior */
    uint8_t Cycles;                 /*!< How many CPU cycles this opcode takes to complete */
    void (*Handler)(Z80_CPU*);      /*!< Function pointer to the handler of this opcode */
} Z80_Instruction;

/**
 * @brief Return the Z80 instruction at the memory location pointed to by the Program Counter
 * 
 * @param z Z80 CPU object
 * @return Z80_Instruction Current instruction in the memory location pointed to by the Program Counter
 */
Z80_Instruction Z80_FetchInstruction(Z80_CPU *z);

void BAD(Z80_CPU *z);

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

uint16_t pop(Z80_CPU *z);

void push(Z80_CPU *z, uint16_t val);

void ret(Z80_CPU *z, bool condition);

void call(Z80_CPU *z, uint16_t val, bool condition);

void rst(Z80_CPU *z, uint8_t val);

void ex(uint16_t *a, uint16_t *b);

#endif