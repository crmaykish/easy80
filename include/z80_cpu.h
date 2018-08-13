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

#define MAX_RAM_ADDRESS 65536

typedef enum cpu_state { RUNNING, STOPPED } Z80_CPUState;

typedef union reg {
    uint16_t reg_word;
    struct {
        uint8_t low;
        uint8_t high;
    } reg_byte;
} reg_internal;

typedef struct Z80_Registers {
    reg_internal AF_reg;
    reg_internal BC_reg;
    reg_internal DE_reg;
    reg_internal HL_reg;
    reg_internal AFp_reg;
    reg_internal BCp_reg;
    reg_internal DEp_reg;
    reg_internal HLp_reg;
} Z80_Registers;

typedef struct Z80_CPU {
    Z80_Registers Registers;

    uint16_t *AF;
    uint16_t *BC;
    uint16_t *DE;
    uint16_t *HL;

    uint8_t *A, *F;
    uint8_t *B, *C;
    uint8_t *D, *E;
    uint8_t *H, *L;

    uint8_t I, R;                       /*!< 8-bit registers */
    uint16_t IX, IY, SP, PC;            /*!< 16-bit registers */
    uint8_t Memory[MAX_RAM_ADDRESS];    /*!< Combined ROM and RAM for the CPU */
    Z80_CPUState State;                 /*!< State of the CPU: running, halted, etc. */
    bool Interrupts;                    /*!< Interrupts enabled */
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

/**
 * @brief Return the value stored in memory address XY
 * 
 * @param z Z80 CPU object
 * @param X most signficant byte of memory address
 * @param Y least significant byte of memory address
 * @return uint8_t value stored in (XY)
 */
uint8_t mem_nn(Z80_CPU *z, uint8_t X, uint8_t Y);

/**
 * @brief Return the value at the memory address stored in HL
 * 
 * @param z Z80 CPU object
 * @return uint8_t value stored in (HL)
 */
uint8_t mem_HL(Z80_CPU *z);

/**
 * @brief Return the operands after the PC
 * 
 * @param z Z80 CPU object
 * @param offset Byte offset from the PC to return, 0 is the PC, 1 is the first, 2 is the second, etc.
 * @return uint8_t offset from the PC
 */
uint8_t op(Z80_CPU *z, uint8_t offset);

#endif