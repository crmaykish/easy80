#ifndef Z80_CPU_H
#define Z80_CPU_H

#include "stddef.h"
#include "stdint.h"

#define MAX_ADDRESS 65536

#define FLAG_C      (0)         // Carry
#define FLAG_N      (1)    // Add/Subtract
#define FLAG_PV     (2)    // Parity/Overflow
#define FLAG_H      (4)    // Half Carry
#define FLAG_Z      (6)    // Zero
#define FLAG_S      (7)    // Sign

typedef enum {RUNNING, STOPPED} Z80_CPUState;

typedef struct Z80_CPU {
    // Main registers
    uint8_t A, B, C, D, E, F, H, L;

    // Alternate registers
    uint8_t Ap, Bp, Cp, Dp, Ep, Fp, Hp, Lp;

    // Index registers
    uint16_t IX;
    uint16_t IY;

    // Stack pointer
    uint16_t SP;

    // Interrupt vector register
    uint8_t I;

    // DRAM refresh counter
    uint8_t R;

    // Program counter
    uint16_t PC;

    uint8_t Memory[MAX_ADDRESS];

    // Running / Stopped
    Z80_CPUState State;
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

/**
 * @brief Debug output of the CPU registers
 */
void Z80_CPU_PrintRegisters(Z80_CPU *cpu);

#endif