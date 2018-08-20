/**
 * @brief Main instruction for the Z80 CPU core
 * 
 * @file z80_instructions_main.h
 * @author crmaykish
 * @date 2018-08-19
 */

#ifndef Z80_INSTRUCTIONS_MAIN_H
#define Z80_INSTRUCTIONS_MAIN_H

#include "z80_instructions_common.h"

Z80_Instruction FetchMainInstruction(uint8_t opcode);

#endif