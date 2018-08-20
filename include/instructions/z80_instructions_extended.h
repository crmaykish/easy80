/**
 * @brief Extended instruction definitions for the Z80 CPU core
 * 
 * @file z80_instructions_extended.h
 * @author crmaykish
 * @date 2018-08-19
 */
#ifndef Z80_INSTRUCTIONS_EXTENDED_H
#define Z80_INSTRUCTIONS_EXTENDED_H

#include "z80_instructions_common.h"

Z80_Instruction FetchExtendedInstruction(uint8_t opcode);

#endif