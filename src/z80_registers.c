#include "z80_registers.h"
#include <stdlib.h>
#include <stdint.h>

typedef union reg {
    uint16_t reg_word;
    struct {
        uint8_t low;
        uint8_t high;
    } reg_bytes;
} reg_internal;

struct Z80_Registers {
    reg_internal AF_reg;
    reg_internal BC_reg;
    reg_internal DE_reg;
    reg_internal HL_reg;
    reg_internal AFp_reg;
    reg_internal BCp_reg;
    reg_internal DEp_reg;
    reg_internal HLp_reg;
};

Z80_Registers* Z80_Registers_Create() {
    Z80_Registers *reg = (Z80_Registers*) calloc(1, sizeof(Z80_Registers));
}

void Z80_Registers_Destroy(Z80_Registers *reg) {
    free(reg);
}

uint16_t* AF(Z80_Registers *reg) { return &reg->AF_reg.reg_word; }
uint16_t* BC(Z80_Registers *reg) { return &reg->BC_reg.reg_word; }
uint16_t* DE(Z80_Registers *reg) { return &reg->DE_reg.reg_word; }
uint16_t* HL(Z80_Registers *reg) { return &reg->HL_reg.reg_word; }

uint8_t* A(Z80_Registers *reg) { return &reg->AF_reg.reg_bytes.high; }
uint8_t* B(Z80_Registers *reg) { return &reg->BC_reg.reg_bytes.high; }
uint8_t* C(Z80_Registers *reg) { return &reg->BC_reg.reg_bytes.low; }
uint8_t* D(Z80_Registers *reg) { return &reg->DE_reg.reg_bytes.high; }
uint8_t* E(Z80_Registers *reg) { return &reg->DE_reg.reg_bytes.low; }
uint8_t* F(Z80_Registers *reg) { return &reg->AF_reg.reg_bytes.low; }
uint8_t* H(Z80_Registers *reg) { return &reg->HL_reg.reg_bytes.high; }
uint8_t* L(Z80_Registers *reg) { return &reg->HL_reg.reg_bytes.low; }

uint16_t* AFp(Z80_Registers *reg) { return &reg->AFp_reg.reg_word; }
uint16_t* BCp(Z80_Registers *reg) { return &reg->BCp_reg.reg_word; }
uint16_t* DEp(Z80_Registers *reg) { return &reg->DEp_reg.reg_word; }
uint16_t* HLp(Z80_Registers *reg) { return &reg->HLp_reg.reg_word; }

uint8_t* Ap(Z80_Registers *reg) { return &reg->AFp_reg.reg_bytes.high; }
uint8_t* Bp(Z80_Registers *reg) { return &reg->BCp_reg.reg_bytes.high; }
uint8_t* Cp(Z80_Registers *reg) { return &reg->BCp_reg.reg_bytes.low; }
uint8_t* Dp(Z80_Registers *reg) { return &reg->DEp_reg.reg_bytes.high; }
uint8_t* Ep(Z80_Registers *reg) { return &reg->DEp_reg.reg_bytes.low; }
uint8_t* Fp(Z80_Registers *reg) { return &reg->AFp_reg.reg_bytes.low; }
uint8_t* Hp(Z80_Registers *reg) { return &reg->HLp_reg.reg_bytes.high; }
uint8_t* Lp(Z80_Registers *reg) { return &reg->HLp_reg.reg_bytes.low; }