#ifndef Z80_REGISTERS_H
#define Z80_REGISTERS_H

#include <stdint.h>

typedef struct Z80_Registers Z80_Registers;

Z80_Registers* Z80_Registers_Create();
void Z80_Registers_Destroy(Z80_Registers *reg);

uint16_t* AF(Z80_Registers *reg);
uint16_t* BC(Z80_Registers *reg);
uint16_t* DE(Z80_Registers *reg);
uint16_t* HL(Z80_Registers *reg);

uint8_t* A(Z80_Registers *reg);
uint8_t* B(Z80_Registers *reg);
uint8_t* C(Z80_Registers *reg);
uint8_t* D(Z80_Registers *reg);
uint8_t* E(Z80_Registers *reg);
uint8_t* F(Z80_Registers *reg);
uint8_t* H(Z80_Registers *reg);
uint8_t* L(Z80_Registers *reg);

uint16_t* AFp(Z80_Registers *reg);
uint16_t* BCp(Z80_Registers *reg);
uint16_t* DEp(Z80_Registers *reg);
uint16_t* HLp(Z80_Registers *reg);

uint8_t* Ap(Z80_Registers *reg);
uint8_t* Bp(Z80_Registers *reg);
uint8_t* Cp(Z80_Registers *reg);
uint8_t* Dp(Z80_Registers *reg);
uint8_t* Ep(Z80_Registers *reg);
uint8_t* Fp(Z80_Registers *reg);
uint8_t* Hp(Z80_Registers *reg);
uint8_t* Lp(Z80_Registers *reg);

#endif