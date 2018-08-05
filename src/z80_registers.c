#include "z80_registers.h"
#include "stdio.h"

void Z80_Registers_Init(Z80_Registers *r) {
    r->A = 0;
    r->B = 0;
    r->C = 0;
    r->D = 0;
    r->E = 0;
    r->F = 0;

    r->Ap = 0;
    r->Bp = 0;
    r->Cp = 0;
    r->Dp = 0;
    r->Ep = 0;
    r->Fp = 0;

    r->IX = 0;
    r->IY = 0;

    r->SP = 0;

    r->I = 0;

    r->R = 0;

    r->PC = 0;
}

uint16_t combine(uint8_t x, uint8_t y) {
    return (x << 8) | y;
}

uint8_t split_1(uint16_t r) {
    return (r & 0xFF00) >> 8;
}

uint8_t split_2(uint16_t r) {
    return r & 0x00FF;
}

// All combined registers have a getter (no prefix) and a setter (prefixed with s)

// AF
uint16_t AF(Z80_Registers *r) {
    return combine(r->A, r->F);
}

void sAF(Z80_Registers *r, uint16_t af) {
    r->A = split_1(af);
    r->F = split_2(af);
}

// BC
uint16_t BC(Z80_Registers *r) {
    return combine(r->B, r->C);
}

void sBC(Z80_Registers *r, uint16_t bc) {
    r->B = split_1(bc);
    r->C = split_2(bc);
}

// DE
uint16_t DE(Z80_Registers *r) {
    return combine(r->D, r->E);
}

void sDE(Z80_Registers *r, uint16_t de) {
    r->D = split_1(de);
    r->E = split_2(de);
}

// HL
uint16_t HL(Z80_Registers *r) {
    return combine(r->H, r->L);
}

void sHL(Z80_Registers *r, uint16_t hl) {
    r->H = split_1(hl);
    r->L = split_2(hl);
}

// AF'
uint16_t AFp(Z80_Registers *r) {
    return combine(r->Ap, r->Fp);
}

void sAFp(Z80_Registers *r, uint16_t afp) {
    r->Ap = split_1(afp);
    r->Fp = split_2(afp);
}

// BC'
uint16_t BCp(Z80_Registers *r) {
    return combine(r->Bp, r->Cp);
}

void sBCp(Z80_Registers *r, uint16_t bcp) {
    r->Bp = split_1(bcp);
    r->Cp = split_2(bcp);
}

// DE'
uint16_t DEp(Z80_Registers *r) {
    return combine(r->Dp, r->Ep);
}

void sDEp(Z80_Registers *r, uint16_t dep) {
    r->Dp = split_1(dep);
    r->Ep = split_2(dep);
}

// HL'
uint16_t HLp(Z80_Registers *r) {
    return combine(r->Hp, r->Lp);
}

void sHLp(Z80_Registers *r, uint16_t hlp) {
    r->Hp = split_1(hlp);
    r->Lp = split_2(hlp);
}
