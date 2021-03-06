/**
 * @brief Z80 object and state machine manipulation
 * 
 * @file z80_cpu.h
 * @author crmaykish
 * @date 2018-08-04
 */

#ifndef Z80_CPU_H
#define Z80_CPU_H

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include "z80_registers.h"

#define MAX_RAM_ADDRESS 65536

typedef enum cpu_state { RUNNING, STOPPED } Z80_CPUState;

typedef struct Z80_CPU {
    Z80_Registers *Registers;

    // TODO: possible to make these pointers constant so they are never accidentally changed after creation

    // Main registers pointers
    uint16_t *AF;
    uint16_t *BC;
    uint16_t *DE;
    uint16_t *HL;
    uint8_t *A;
    uint8_t *F;
    uint8_t *B;
    uint8_t *C;
    uint8_t *D;
    uint8_t *E;
    uint8_t *H;
    uint8_t *L;

    // Alternate registers pointers
    uint16_t *AFp;
    uint16_t *BCp;
    uint16_t *DEp;
    uint16_t *HLp;
    uint8_t *Ap;
    uint8_t *Fp;
    uint8_t *Bp;
    uint8_t *Cp;
    uint8_t *Dp;
    uint8_t *Ep;
    uint8_t *Hp;
    uint8_t *Lp;

    // TODO: Convert these pseudo-registers to Z80_Registers for a unified interface
    uint8_t I, R;                       /*!< 8-bit registers */
    uint16_t IX, IY, SP, PC;            /*!< 16-bit registers */
    
    uint8_t Memory[MAX_RAM_ADDRESS];    /*!< Combined ROM and RAM for the CPU */
    Z80_CPUState State;                 /*!< State of the CPU: running, halted, etc. */
    bool Interrupts;                    /*!< Interrupts enabled */
} Z80_CPU;

/**
 * @brief Zero out the state of the CPU
 * 
 * @param z Pointer to CPU object
 */
void Z80_CPU_Init(Z80_CPU *z);

/**
 * @brief Cleanup the Z80_CPU object
 * 
 * @param z pointer to CPU object
 */
void Z80_CPU_Destroy(Z80_CPU *z);

/**
 * @brief Store binary data in a block of Z80 memory starting at offset
 * 
 * @param z Pointer to CPU object
 * @param data Byte array to store in memory
 * @param size Number of bytes to store
 * @param offset Starting point in memory to copy data, use 0 for the beginning of memory
 */
void Z80_CPU_SetMemory(Z80_CPU *z, uint8_t data[], size_t size, uint16_t offset);

/**
 * @brief Perform single step of the CPU
 * 
 * This is not a clock cycle, but a single opcode
 * 
 * @param z Pointer to CPU object
 */
void Z80_CPU_Cycle(Z80_CPU *z);

/**
 * @brief Debug output of the CPU registers
 */
void Z80_CPU_PrintRegisters(Z80_CPU *z);

/**
 * @brief Get the value in memory at the given address
 * 
 * @param z CPU object
 * @param address memory address (16-bit value)
 * @return uint8_t value in memory address
 */
uint8_t GetMemVal(Z80_CPU *z, uint16_t address);

/**
 * @brief Set the memory value at the given address to the given value
 * 
 * @param z CPU object
 * @param address memory address (16-bit)
 * @param val value to store in memory
 */
void SetMemVal(Z80_CPU *z, uint16_t address, uint8_t val);

/**
 * @brief Return the operand at offset from the PC
 * 
 * @param z Z80 CPU object
 * @param offset Byte offset from the PC to return, 0 is the PC, 1 is the first, 2 is the second, etc.
 * @return uint8_t offset from the PC
 */
uint8_t Op(Z80_CPU *z, uint8_t offset);

/**
 * @brief Return the two bytes after PC as a single word
 * 
 * @param z CPU object
 * @return uint16_t two bytes after the opcode as a word
 */
uint16_t op_nn(Z80_CPU *z);

#endif