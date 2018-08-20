/**
 * @brief IX instruction definitions for the Z80 CPU core
 * 
 * @file z80_instructions_ix.h
 * @author crmaykish
 * @date 2018-08-19
 */
#ifndef Z80_INSTRUCTIONS_IX_H
#define Z80_INSTRUCTIONS_IX_H

#include "z80_instructions_common.h"

Z80_Instruction FetchIXInstruction(uint8_t opcode);

#endif