/**
 * @brief Z80 Instruction declarations
 * 
 * @file z80_instructions.h
 * @author crmaykish
 * @date 2018-08-09
 */

#ifndef Z80_INSTRUCTIONS_H
#define Z80_INSTRUCTIONS_H

#include "z80_cpu.h"

#define PREF_EXTD   0xED
#define PREF_BIT    0xCB
#define PREF_IX     0xDD
#define PREF_IY     0xFD

typedef enum operands { OP_NONE = 1, OP_BYTE = 2, OP_WORD = 3, OP_EXTD, OP_JUMP,  } Z80_Operands;

typedef struct Z80_Instruction {
    uint8_t OpCode;
    char *Name;
    Z80_Operands Operands;
    uint8_t Cycles;
    void (*Handler)(Z80_CPU*);
} Z80_Instruction;

// Function prototypes
Z80_Instruction Z80_FetchInstruction(Z80_CPU *z);

#endif