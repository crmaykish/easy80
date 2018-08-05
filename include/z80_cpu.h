#ifndef Z80_CPU_H
#define Z80_CPU_H

#include "z80_registers.h"

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

#endif