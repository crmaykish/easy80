#ifndef Z80_REGISTERS_H
#define Z80_REGISTERS_H

#include <stdint.h>

typedef struct Z80_Registers {
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
} Z80_Registers;

/**
 * @brief Zero out all the individual registers
 * 
 * @param r Pointer to the register object
 */
void Z80_Registers_Init(Z80_Registers *r);

uint16_t combine(uint8_t x, uint8_t y);
uint8_t split_1(uint16_t r);
uint8_t split_2(uint16_t r);

// Probably won't actually need these functions...

// Access A and F as one 16-bit register
uint16_t AF(Z80_Registers *r);
void sAF(Z80_Registers *r, uint16_t af);

// Access B and C as one 16-bit register
uint16_t BC(Z80_Registers *r);
void sBC(Z80_Registers *r, uint16_t bc);

// Access D and E as one 16-bit register
uint16_t DE(Z80_Registers *r);
void sDE(Z80_Registers *r, uint16_t de);

// Access H and L as one 16-bit register
uint16_t HL(Z80_Registers *r);
void sHL(Z80_Registers *r, uint16_t hl);

// Access Ap and Fp as one 16-bit register
uint16_t AFp(Z80_Registers *r);
void sAFp(Z80_Registers *r, uint16_t afp);

// Access Bp and Cp as one 16-bit register
uint16_t BCp(Z80_Registers *r);
void sBCp(Z80_Registers *r, uint16_t bcp);

// Access Dp and Ep as one 16-bit register
uint16_t DEp(Z80_Registers *r);
void sDEp(Z80_Registers *r, uint16_t dep);

// Access Hp and Lp as one 16-bit register
uint16_t HLp(Z80_Registers *r);
void sHLp(Z80_Registers *r, uint16_t hlp);

#endif
