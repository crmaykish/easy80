#ifndef Z80_CPU_H
#define Z80_CPU_H

#include "z80_registers.h"
#include "stddef.h"

#define MAX_ADDRESS 65536

typedef enum {RUNNING, STOPPED} Z80_CPUState;

typedef struct Z80_CPU {
    Z80_Registers Registers;
    Z80_CPUState State;
    uint8_t Memory[MAX_ADDRESS];
} Z80_CPU;

/**
 * @brief Zero out the state of the CPU
 * 
 * @param cpu Pointer to CPU object
 */
void Z80_CPU_Init(Z80_CPU *cpu);

/**
 * @brief Store binary data in a block of Z80 memory starting at offset
 * 
 * @param cpu Pointer to CPU object
 * @param data Byte array to store in memory
 * @param size Number of bytes to store
 * @param offset Starting point in memory to copy data, use 0 for the beginning of memory
 */
void Z80_CPU_SetMemory(Z80_CPU *cpu, uint8_t data[], size_t size, uint16_t offset);

/**
 * @brief Perform single step of the CPU
 * 
 * This is not a clock cycle, but a single opcode
 * 
 * @param cpu Pointer to CPU object
 */
void Z80_CPU_Cycle(Z80_CPU *cpu);

void Z80_CPU_PrintRegisters(Z80_CPU *cpu);

#endif