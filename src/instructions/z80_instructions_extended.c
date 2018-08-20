#include "z80_instructions_extended.h"
#include "z80_instructions_common.h"
#include "bitmath.h"

// Extended instruction set implementation

// 0x40

// 0x50

// 0x60

// 0x70
void LD_nnm_SP(Z80_CPU *z) { 
    // TODO: backwards operands?
    SetMemVal(z, split_1(z->SP), Op(z, 3));
    SetMemVal(z, split_2(z->SP), Op(z, 2));
}
void LD_SP_nnm(Z80_CPU *z) { ld_word(z, &z->SP, GetMemVal(z, combine(Op(z, 3), Op(z, 2)))); }
// 0xA0

// 0xB0
void LDIR(Z80_CPU *z) { ldir(z); }
void CPIR(Z80_CPU *z) {  }
void INIR(Z80_CPU *z) {  }
void OTIR(Z80_CPU *z) {  }
void LDDR(Z80_CPU *z) {  }
void CPDR(Z80_CPU *z) {  }
void INDR(Z80_CPU *z) {  }
void OTDR(Z80_CPU *z) {  }

// Extended instruction set only includes 0x40, 0x50, 0x60, 0x70, 0xA0, 0xB0
// Access the array with an offset of 0x40, but skips 0x80 and 0x90
const Z80_Instruction ExtendedInstructions[96] = {
    // 0x40
    { 0x40, "IN B,(C)",     OP_NONE,    0,      &BAD },
    { 0x41, "OUT (C),B",    OP_NONE,    0,      &BAD },
    { 0x42, "SBC HL,BC",    OP_NONE,    0,      &BAD },
    { 0x43, "LD (**),BC",   OP_NONE,    0,      &BAD },
    { 0x44, "NEG",          OP_NONE,    0,      &BAD },
    { 0x45, "RETN",         OP_NONE,    0,      &BAD },
    { 0x46, "IM 0",         OP_NONE,    0,      &BAD },
    { 0x47, "LD I,A",       OP_NONE,    0,      &BAD },
    { 0x48, "IN C,(C)",     OP_NONE,    0,      &BAD },
    { 0x49, "OUT (C),C",    OP_NONE,    0,      &BAD },
    { 0x4A, "ADC HL,BC",    OP_NONE,    0,      &BAD },
    { 0x4B, "LD BC,(**)",   OP_NONE,    0,      &BAD },
    { 0x4C, "NEG",          OP_NONE,    0,      &BAD },
    { 0x4D, "RETI",         OP_NONE,    0,      &BAD },
    { 0x4E, "IM 0/1",       OP_NONE,    0,      &BAD },
    { 0x4F, "LD R,A",       OP_NONE,    0,      &BAD },
    // 0x50
    { 0x50, "",          OP_NONE,    0,      &BAD },
    { 0x51, "",          OP_NONE,    0,      &BAD },
    { 0x52, "",          OP_NONE,    0,      &BAD },
    { 0x53, "",          OP_NONE,    0,      &BAD },
    { 0x54, "",          OP_NONE,    0,      &BAD },
    { 0x55, "",          OP_NONE,    0,      &BAD },
    { 0x56, "",          OP_NONE,    0,      &BAD },
    { 0x57, "",          OP_NONE,    0,      &BAD },
    { 0x58, "",          OP_NONE,    0,      &BAD },
    { 0x59, "",          OP_NONE,    0,      &BAD },
    { 0x5A, "",          OP_NONE,    0,      &BAD },
    { 0x5B, "",          OP_NONE,    0,      &BAD },
    { 0x5C, "",          OP_NONE,    0,      &BAD },
    { 0x5D, "",          OP_NONE,    0,      &BAD },
    { 0x5E, "",          OP_NONE,    0,      &BAD },
    { 0x5F, "",          OP_NONE,    0,      &BAD },
    // 0x60
    { 0x60, "",          OP_NONE,    0,      &BAD },
    { 0x61, "",          OP_NONE,    0,      &BAD },
    { 0x62, "",          OP_NONE,    0,      &BAD },
    { 0x63, "",          OP_NONE,    0,      &BAD },
    { 0x64, "",          OP_NONE,    0,      &BAD },
    { 0x65, "",          OP_NONE,    0,      &BAD },
    { 0x66, "",          OP_NONE,    0,      &BAD },
    { 0x67, "",          OP_NONE,    0,      &BAD },
    { 0x68, "",          OP_NONE,    0,      &BAD },
    { 0x69, "",          OP_NONE,    0,      &BAD },
    { 0x6A, "",          OP_NONE,    0,      &BAD },
    { 0x6B, "",          OP_NONE,    0,      &BAD },
    { 0x6C, "",          OP_NONE,    0,      &BAD },
    { 0x6D, "",          OP_NONE,    0,      &BAD },
    { 0x6E, "",          OP_NONE,    0,      &BAD },
    { 0x6F, "",          OP_NONE,    0,      &BAD },
    // 0x70
    { 0x70, "",          OP_NONE,    0,      &BAD },
    { 0x71, "",          OP_NONE,    0,      &BAD },
    { 0x72, "",          OP_NONE,    0,      &BAD },
    { 0x73, "LD (**),SP",   OP_LONG,    20,     &LD_nnm_SP },
    { 0x74, "",          OP_NONE,    0,      &BAD },
    { 0x75, "",          OP_NONE,    0,      &BAD },
    { 0x76, "",          OP_NONE,    0,      &BAD },
    { 0x77, "",          OP_NONE,    0,      &BAD },
    { 0x78, "",          OP_NONE,    0,      &BAD },
    { 0x79, "",          OP_NONE,    0,      &BAD },
    { 0x7A, "",          OP_NONE,    0,      &BAD },
    { 0x7B, "LD SP,(**)",   OP_LONG,    20,     &LD_SP_nnm },
    { 0x7C, "",          OP_NONE,    0,      &BAD },
    { 0x7D, "",          OP_NONE,    0,      &BAD },
    { 0x7E, "",          OP_NONE,    0,      &BAD },
    { 0x7F, "",          OP_NONE,    0,      &BAD },
    // 0xA0
    { 0xA0, "",          OP_NONE,    0,      &BAD },
    { 0xA1, "",          OP_NONE,    0,      &BAD },
    { 0xA2, "",          OP_NONE,    0,      &BAD },
    { 0xA3, "",          OP_NONE,    0,      &BAD },
    { 0xA4, "",          OP_NONE,    0,      &BAD },
    { 0xA5, "",          OP_NONE,    0,      &BAD },
    { 0xA6, "",          OP_NONE,    0,      &BAD },
    { 0xA7, "",          OP_NONE,    0,      &BAD },
    { 0xA8, "",          OP_NONE,    0,      &BAD },
    { 0xA9, "",          OP_NONE,    0,      &BAD },
    { 0xAA, "",          OP_NONE,    0,      &BAD },
    { 0xAB, "",          OP_NONE,    0,      &BAD },
    { 0xAC, "",          OP_NONE,    0,      &BAD },
    { 0xAD, "",          OP_NONE,    0,      &BAD },
    { 0xAE, "",          OP_NONE,    0,      &BAD },
    { 0xAF, "",          OP_NONE,    0,      &BAD },
    //0xB0
    { 0xB0, "LDIR",      OP_BYTE,    21,     &LDIR },    // 21/16
    { 0xB1, "",          OP_NONE,    0,      &BAD },
    { 0xB2, "",          OP_NONE,    0,      &BAD },
    { 0xB3, "",          OP_NONE,    0,      &BAD },
    { 0xB4, "",          OP_NONE,    0,      &BAD },
    { 0xB5, "",          OP_NONE,    0,      &BAD },
    { 0xB6, "",          OP_NONE,    0,      &BAD },
    { 0xB7, "",          OP_NONE,    0,      &BAD },
    { 0xB8, "",          OP_NONE,    0,      &BAD },
    { 0xB9, "",          OP_NONE,    0,      &BAD },
    { 0xBA, "",          OP_NONE,    0,      &BAD },
    { 0xBB, "",          OP_NONE,    0,      &BAD },
    { 0xBC, "",          OP_NONE,    0,      &BAD },
    { 0xBD, "",          OP_NONE,    0,      &BAD },
    { 0xBE, "",          OP_NONE,    0,      &BAD },
    { 0xBF, "",          OP_NONE,    0,      &BAD },
};

Z80_Instruction FetchExtendedInstruction(uint8_t opcode) {
    return (opcode >= 0xA0) ? ExtendedInstructions[opcode - 0x60] : ExtendedInstructions[opcode - 0x40];
}