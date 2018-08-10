#include "z80_instructions.h"
#include "z80_logic.h"

// Main instruction opcode mapping
const Z80_Instruction MainInstructions[256] = {
    // 0x00
    { 0x00, "NOP",          OP_NONE,    4,      &NOP },
    { 0x01, "LD BC,**",     OP_WORD,    10,     &LD_BC_nn },
    { 0x02, "LD (BC),A",    OP_NONE,    7,      &LD_BCm_A },
    { 0x03, "INC BC",       OP_NONE,    6,      &INC_BC },
    { 0x04, "INC B",        OP_NONE,    4,      &INC_B },
    { 0x05, "DEC B",        OP_NONE,    4,      &DEC_B },
    { 0x06, "LD B,*",       OP_BYTE,    7,      &LD_B_n },
    { 0x07, "RLCA",         OP_NONE,    4,      &RLCA },
    { 0x08, "EX AF,AF'",    OP_NONE,    4,      &EX_AF_AFp },
    { 0x09, "ADD HL,BC",    OP_NONE,    11,     &ADD_HL_BC },
    { 0x0A, "LD A,(BC)",    OP_NONE,    7,      &LD_A_BCm },
    { 0x0B, "DEC BC",       OP_NONE,    6,      &DEC_BC },
    { 0x0C, "INC C",        OP_NONE,    4,      &INC_C },
    { 0x0D, "DEC C",        OP_NONE,    4,      &DEC_C },
    { 0x0E, "LD C,*",       OP_BYTE,    7,      &LD_C_n },
    { 0x0F, "RRCA",         OP_NONE,    4,      &RRCA },
    // 0x10
    { 0x10, "DJNZ *",       OP_BYTE,    13,     &DJNZ_n },     // TODO: 13 or 8 clock cycles
    { 0x11, "LD DE,**",     OP_WORD,    10,     &LD_DE_nn },
    { 0x12, "LD (DE),A",    OP_NONE,    7,      &LD_DEm_A },
    { 0x13, "INC DE",       OP_NONE,    6,      &INC_DE },
    { 0x14, "INC D",        OP_NONE,    4,      &INC_D },
    { 0x15, "DEC D",        OP_NONE,    4,      &DEC_D },
    { 0x16, "LD D,*",       OP_BYTE,    7,      &LD_D_n },
    { 0x17, "RLA",          OP_NONE,    4,      &RLA },
    { 0x18, "JR *",         OP_BYTE,    12,     &JR_n },
    { 0x19, "ADD HL,DE",    OP_NONE,    11,     &ADD_HL_DE },
    { 0x1A, "LD A,(DE)",    OP_NONE,    7,      &LD_A_DEm },
    { 0x1B, "DEC DE",       OP_NONE,    6,      &DEC_DE },
    { 0x1C, "INC E",        OP_NONE,    4,      &INC_E },
    { 0x1D, "DEC E",        OP_NONE,    4,      &DEC_E },
    { 0x1E, "LD E,*",       OP_BYTE,    7,      &LD_E_n },
    { 0x1F, "RRA",          OP_NONE,    4,      &RRA },
    // 0x20
    { 0x20, "JR NZ,*",      OP_BYTE,    12,      &JR_NZ_n },    // TODO: 12 or 7 clock cycles
    { 0x21, "LD HL,**",     OP_WORD,    10,      &LD_HL_nn },
    { 0x22, "LD (**),HL",   OP_WORD,    16,      &LD_nnm_HL },
    { 0x23, "INC HL",       OP_NONE,    6,      &INC_HL },
    { 0x24, "INC H",        OP_NONE,    4,      &INC_H },
    { 0x25, "DEC H",        OP_NONE,    4,      &DEC_H },
    { 0x26, "LD H,*",       OP_BYTE,    7,      &LD_H_nn },
    { 0x27, "DAA",          OP_NONE,    4,      &DAA },
    { 0x28, "JR Z,*",       OP_BYTE,    12,      &JR_Z_n },     // TODO: 12 or 7 clock cycles
    { 0x29, "ADD HL,HL",    OP_NONE,    11,      &ADD_HL_HL },
    { 0x2A, "LD HL,(**)",   OP_WORD,    16,      &LD_HL_nnm },
    { 0x2B, "DEC HL",       OP_NONE,    6,      &DEC_HL },
    { 0x2C, "INC L",        OP_NONE,    4,      &INC_L },
    { 0x2D, "DEC L",        OP_NONE,    4,      &DEC_L },
    { 0x2E, "LD L,*",       OP_BYTE,    7,      &LD_L_n },
    { 0x2F, "CPL",          OP_NONE,    4,      &CPL },
    // 0x30
    { 0x30, "JR NC,*",      OP_NONE,    2,      &JR_NC_n },
    { 0x31, "LD SP,**",     OP_NONE,    3,      &LD_SP_nn },
    { 0x32, "LD (**),A",    OP_NONE,    3,      &LD_nnm_A },
    { 0x33, "INC SP",       OP_NONE,    1,      &INC_SP },
    { 0x34, "INC (HL)",     OP_NONE,    1,      &INC_HLm },
    { 0x35, "DEC (HL)",     OP_NONE,    1,      &DEC_HLm },
    { 0x36, "LD (HL),*",    OP_NONE,    2,      &LD_HLm_n },
    { 0x37, "SCF",          OP_NONE,    1,      &SCF },
    { 0x38, "JR C,*",       OP_NONE,    2,      &JR_C_n },
    { 0x39, "ADD HL,SP",    OP_NONE,    1,      &ADD_HL_SP },
    { 0x3A, "LD A,(**)",    OP_NONE,    3,      &LD_A_nnm },
    { 0x3B, "DEC SP",       OP_NONE,    1,      &DEC_SP },
    { 0x3C, "INC A",        OP_NONE,    1,      &INC_A },
    { 0x3D, "DEC A",        OP_NONE,    1,      &DEC_A },
    { 0x3E, "LD A,*",       OP_NONE,    2,      &LD_A_n },
    { 0x3F, "CCF",          OP_NONE,    1,      &CCF },
    // 0x40
    { 0x40, "LD B,B",       OP_NONE,    4,      &LD_B_B },
    { 0x41, "LD B,C",       OP_NONE,    4,      &LD_B_C },
    { 0x42, "LD B,D",       OP_NONE,    4,      &LD_B_D },
    { 0x43, "LD B,E",       OP_NONE,    4,      &LD_B_E },
    { 0x44, "LD B,H",       OP_NONE,    4,      &LD_B_H },
    { 0x45, "LD B,L",       OP_NONE,    4,      &LD_B_L },
    { 0x46, "LD B,(HL)",    OP_NONE,    7,      &LD_B_HLm },
    { 0x47, "LD B,A",       OP_NONE,    4,      &LD_B_A },
    { 0x48, "LD C,B",       OP_NONE,    4,      &LD_C_B },
    { 0x49, "LD C,C",       OP_NONE,    4,      &LD_C_C },
    { 0x4A, "LD C,D",       OP_NONE,    4,      &LD_C_D },
    { 0x4B, "LD C,E",       OP_NONE,    4,      &LD_C_E },
    { 0x4C, "LD C,H",       OP_NONE,    4,      &LD_C_H },
    { 0x4D, "LD C,L",       OP_NONE,    4,      &LD_C_L },
    { 0x4E, "LD C,(HL)",    OP_NONE,    7,      &LD_C_HLm },
    { 0x4F, "LD C,A",       OP_NONE,    4,      &LD_C_A },
    // 0x50
    { 0x50, "",          OP_NONE,    0,      &NOP },
    { 0x51, "",          OP_NONE,    0,      &NOP },
    { 0x52, "",          OP_NONE,    0,      &NOP },
    { 0x53, "",          OP_NONE,    0,      &NOP },
    { 0x54, "",          OP_NONE,    0,      &NOP },
    { 0x55, "",          OP_NONE,    0,      &NOP },
    { 0x56, "",          OP_NONE,    0,      &NOP },
    { 0x57, "",          OP_NONE,    0,      &NOP },
    { 0x58, "",          OP_NONE,    0,      &NOP },
    { 0x59, "",          OP_NONE,    0,      &NOP },
    { 0x5A, "",          OP_NONE,    0,      &NOP },
    { 0x5B, "",          OP_NONE,    0,      &NOP },
    { 0x5C, "",          OP_NONE,    0,      &NOP },
    { 0x5D, "",          OP_NONE,    0,      &NOP },
    { 0x5E, "",          OP_NONE,    0,      &NOP },
    { 0x5F, "",          OP_NONE,    0,      &NOP },
    // 0x60
    { 0x60, "",          OP_NONE,    0,      &NOP },
    { 0x61, "",          OP_NONE,    0,      &NOP },
    { 0x62, "",          OP_NONE,    0,      &NOP },
    { 0x63, "",          OP_NONE,    0,      &NOP },
    { 0x64, "",          OP_NONE,    0,      &NOP },
    { 0x65, "",          OP_NONE,    0,      &NOP },
    { 0x66, "",          OP_NONE,    0,      &NOP },
    { 0x67, "",          OP_NONE,    0,      &NOP },
    { 0x68, "",          OP_NONE,    0,      &NOP },
    { 0x69, "",          OP_NONE,    0,      &NOP },
    { 0x6A, "",          OP_NONE,    0,      &NOP },
    { 0x6B, "",          OP_NONE,    0,      &NOP },
    { 0x6C, "",          OP_NONE,    0,      &NOP },
    { 0x6D, "",          OP_NONE,    0,      &NOP },
    { 0x6E, "",          OP_NONE,    0,      &NOP },
    { 0x6F, "",          OP_NONE,    0,      &NOP },
    // 0x70
    { 0x70, "",          OP_NONE,    0,      &NOP },
    { 0x71, "",          OP_NONE,    0,      &NOP },
    { 0x72, "",          OP_NONE,    0,      &NOP },
    { 0x73, "",          OP_NONE,    0,      &NOP },
    { 0x74, "",          OP_NONE,    0,      &NOP },
    { 0x75, "",          OP_NONE,    0,      &NOP },
    { 0x76, "",          OP_NONE,    0,      &NOP },
    { 0x77, "",          OP_NONE,    0,      &NOP },
    { 0x78, "",          OP_NONE,    0,      &NOP },
    { 0x79, "",          OP_NONE,    0,      &NOP },
    { 0x7A, "",          OP_NONE,    0,      &NOP },
    { 0x7B, "",          OP_NONE,    0,      &NOP },
    { 0x7C, "",          OP_NONE,    0,      &NOP },
    { 0x7D, "",          OP_NONE,    0,      &NOP },
    { 0x7E, "",          OP_NONE,    0,      &NOP },
    { 0x7F, "",          OP_NONE,    0,      &NOP },
    // 0x80
    { 0x80, "",          OP_NONE,    0,      &NOP },
    { 0x81, "",          OP_NONE,    0,      &NOP },
    { 0x82, "",          OP_NONE,    0,      &NOP },
    { 0x83, "",          OP_NONE,    0,      &NOP },
    { 0x84, "",          OP_NONE,    0,      &NOP },
    { 0x85, "",          OP_NONE,    0,      &NOP },
    { 0x86, "",          OP_NONE,    0,      &NOP },
    { 0x87, "",          OP_NONE,    0,      &NOP },
    { 0x88, "",          OP_NONE,    0,      &NOP },
    { 0x89, "",          OP_NONE,    0,      &NOP },
    { 0x8A, "",          OP_NONE,    0,      &NOP },
    { 0x8B, "",          OP_NONE,    0,      &NOP },
    { 0x8C, "",          OP_NONE,    0,      &NOP },
    { 0x8D, "",          OP_NONE,    0,      &NOP },
    { 0x8E, "",          OP_NONE,    0,      &NOP },
    { 0x8F, "",          OP_NONE,    0,      &NOP },
    // 0x90
    { 0x90, "",          OP_NONE,    0,      &NOP },
    { 0x91, "",          OP_NONE,    0,      &NOP },
    { 0x92, "",          OP_NONE,    0,      &NOP },
    { 0x93, "",          OP_NONE,    0,      &NOP },
    { 0x94, "",          OP_NONE,    0,      &NOP },
    { 0x95, "",          OP_NONE,    0,      &NOP },
    { 0x96, "",          OP_NONE,    0,      &NOP },
    { 0x97, "",          OP_NONE,    0,      &NOP },
    { 0x98, "",          OP_NONE,    0,      &NOP },
    { 0x99, "",          OP_NONE,    0,      &NOP },
    { 0x9A, "",          OP_NONE,    0,      &NOP },
    { 0x9B, "",          OP_NONE,    0,      &NOP },
    { 0x9C, "",          OP_NONE,    0,      &NOP },
    { 0x9D, "",          OP_NONE,    0,      &NOP },
    { 0x9E, "",          OP_NONE,    0,      &NOP },
    { 0x9F, "",          OP_NONE,    0,      &NOP },
    // 0xA0
    { 0xA0, "",          OP_NONE,    0,      &NOP },
    { 0xA1, "",          OP_NONE,    0,      &NOP },
    { 0xA2, "",          OP_NONE,    0,      &NOP },
    { 0xA3, "",          OP_NONE,    0,      &NOP },
    { 0xA4, "",          OP_NONE,    0,      &NOP },
    { 0xA5, "",          OP_NONE,    0,      &NOP },
    { 0xA6, "",          OP_NONE,    0,      &NOP },
    { 0xA7, "",          OP_NONE,    0,      &NOP },
    { 0xA8, "",          OP_NONE,    0,      &NOP },
    { 0xA9, "",          OP_NONE,    0,      &NOP },
    { 0xAA, "",          OP_NONE,    0,      &NOP },
    { 0xAB, "",          OP_NONE,    0,      &NOP },
    { 0xAC, "",          OP_NONE,    0,      &NOP },
    { 0xAD, "",          OP_NONE,    0,      &NOP },
    { 0xAE, "",          OP_NONE,    0,      &NOP },
    { 0xAF, "",          OP_NONE,    0,      &NOP },
    // 0xB0
    { 0xB0, "",          OP_NONE,    0,      &NOP },
    { 0xB1, "",          OP_NONE,    0,      &NOP },
    { 0xB2, "",          OP_NONE,    0,      &NOP },
    { 0xB3, "",          OP_NONE,    0,      &NOP },
    { 0xB4, "",          OP_NONE,    0,      &NOP },
    { 0xB5, "",          OP_NONE,    0,      &NOP },
    { 0xB6, "",          OP_NONE,    0,      &NOP },
    { 0xB7, "",          OP_NONE,    0,      &NOP },
    { 0xB8, "",          OP_NONE,    0,      &NOP },
    { 0xB9, "",          OP_NONE,    0,      &NOP },
    { 0xBA, "",          OP_NONE,    0,      &NOP },
    { 0xBB, "",          OP_NONE,    0,      &NOP },
    { 0xBC, "",          OP_NONE,    0,      &NOP },
    { 0xBD, "",          OP_NONE,    0,      &NOP },
    { 0xBE, "",          OP_NONE,    0,      &NOP },
    { 0xBF, "",          OP_NONE,    0,      &NOP },
    // 0xC0
    { 0xC0, "",          OP_NONE,    0,      &NOP },
    { 0xC1, "",          OP_NONE,    0,      &NOP },
    { 0xC2, "",          OP_NONE,    0,      &NOP },
    { 0xC3, "",          OP_NONE,    0,      &NOP },
    { 0xC4, "",          OP_NONE,    0,      &NOP },
    { 0xC5, "",          OP_NONE,    0,      &NOP },
    { 0xC6, "",          OP_NONE,    0,      &NOP },
    { 0xC7, "",          OP_NONE,    0,      &NOP },
    { 0xC8, "",          OP_NONE,    0,      &NOP },
    { 0xC9, "",          OP_NONE,    0,      &NOP },
    { 0xCA, "",          OP_NONE,    0,      &NOP },
    { 0xCB, "",          OP_NONE,    0,      &NOP },
    { 0xCC, "",          OP_NONE,    0,      &NOP },
    { 0xCD, "",          OP_NONE,    0,      &NOP },
    { 0xCE, "",          OP_NONE,    0,      &NOP },
    { 0xCF, "",          OP_NONE,    0,      &NOP },
    // 0xD0
    { 0xD0, "",          OP_NONE,    0,      &NOP },
    { 0xD1, "",          OP_NONE,    0,      &NOP },
    { 0xD2, "",          OP_NONE,    0,      &NOP },
    { 0xD3, "",          OP_NONE,    0,      &NOP },
    { 0xD4, "",          OP_NONE,    0,      &NOP },
    { 0xD5, "",          OP_NONE,    0,      &NOP },
    { 0xD6, "",          OP_NONE,    0,      &NOP },
    { 0xD7, "",          OP_NONE,    0,      &NOP },
    { 0xD8, "",          OP_NONE,    0,      &NOP },
    { 0xD9, "",          OP_NONE,    0,      &NOP },
    { 0xDA, "",          OP_NONE,    0,      &NOP },
    { 0xDB, "",          OP_NONE,    0,      &NOP },
    { 0xDC, "",          OP_NONE,    0,      &NOP },
    { 0xDD, "",          OP_NONE,    0,      &NOP },
    { 0xDE, "",          OP_NONE,    0,      &NOP },
    { 0xDF, "",          OP_NONE,    0,      &NOP },
    // 0xE0
    { 0xE0, "",          OP_NONE,    0,      &NOP },
    { 0xE1, "",          OP_NONE,    0,      &NOP },
    { 0xE2, "",          OP_NONE,    0,      &NOP },
    { 0xE3, "",          OP_NONE,    0,      &NOP },
    { 0xE4, "",          OP_NONE,    0,      &NOP },
    { 0xE5, "",          OP_NONE,    0,      &NOP },
    { 0xE6, "",          OP_NONE,    0,      &NOP },
    { 0xE7, "",          OP_NONE,    0,      &NOP },
    { 0xE8, "",          OP_NONE,    0,      &NOP },
    { 0xE9, "",          OP_NONE,    0,      &NOP },
    { 0xEA, "",          OP_NONE,    0,      &NOP },
    { 0xEB, "",          OP_NONE,    0,      &NOP },
    { 0xEC, "",          OP_NONE,    0,      &NOP },
    { 0xED, "",          OP_NONE,    0,      &NOP },
    { 0xEE, "",          OP_NONE,    0,      &NOP },
    { 0xEF, "",          OP_NONE,    0,      &NOP },
    // 0xF0
    { 0xF0, "",          OP_NONE,    0,      &NOP },
    { 0xF1, "",          OP_NONE,    0,      &NOP },
    { 0xF2, "",          OP_NONE,    0,      &NOP },
    { 0xF3, "",          OP_NONE,    0,      &NOP },
    { 0xF4, "",          OP_NONE,    0,      &NOP },
    { 0xF5, "",          OP_NONE,    0,      &NOP },
    { 0xF6, "",          OP_NONE,    0,      &NOP },
    { 0xF7, "",          OP_NONE,    0,      &NOP },
    { 0xF8, "",          OP_NONE,    0,      &NOP },
    { 0xF9, "",          OP_NONE,    0,      &NOP },
    { 0xFA, "",          OP_NONE,    0,      &NOP },
    { 0xFB, "",          OP_NONE,    0,      &NOP },
    { 0xFC, "",          OP_NONE,    0,      &NOP },
    { 0xFD, "",          OP_NONE,    0,      &NOP },
    { 0xFE, "",          OP_NONE,    0,      &NOP },
    { 0xFF, "",          OP_NONE,    0,      &NOP }
};

Z80_Instruction Z80_FetchInstruction(Z80_CPU *z) {
    return MainInstructions[z->Memory[z->PC]];
}

// 0x00
void NOP(Z80_CPU *z) {}
void LD_BC_nn(Z80_CPU *z) {  }
void LD_BCm_A(Z80_CPU *z) {  }
void INC_BC(Z80_CPU *z) {  }
void INC_B(Z80_CPU *z) {  }
void DEC_B(Z80_CPU *z) {  }
void LD_B_n(Z80_CPU *z) {  }
void RLCA(Z80_CPU *z) {  }
void EX_AF_AFp(Z80_CPU *z) {  }
void ADD_HL_BC(Z80_CPU *z) {  }
void LD_A_BCm(Z80_CPU *z) {  }
void DEC_BC(Z80_CPU *z) {  }
void INC_C(Z80_CPU *z) {  }
void DEC_C(Z80_CPU *z) {  }
void LD_C_n(Z80_CPU *z) {  }
void RRCA(Z80_CPU *z) {  }

// 0x10
void DJNZ_n(Z80_CPU *z) {  }
void LD_DE_nn(Z80_CPU *z) {  }
void LD_DEm_A(Z80_CPU *z) {  }
void INC_DE(Z80_CPU *z) {  }
void INC_D(Z80_CPU *z) {  }
void DEC_D(Z80_CPU *z) {  }
void LD_D_n(Z80_CPU *z) {  }
void RLA(Z80_CPU *z) {  }
void JR_n(Z80_CPU *z) {  }
void ADD_HL_DE(Z80_CPU *z) {  }
void LD_A_DEm(Z80_CPU *z) {  }
void DEC_DE(Z80_CPU *z) {  }
void INC_E(Z80_CPU *z) {  }
void DEC_E(Z80_CPU *z) {  }
void LD_E_n(Z80_CPU *z) {  }
void RRA(Z80_CPU *z) {  }

// 0x20
void JR_NZ_n(Z80_CPU *z) {  }
void LD_HL_nn(Z80_CPU *z) {  }
void LD_nnm_HL(Z80_CPU *z) {  }
void INC_HL(Z80_CPU *z) {  }
void INC_H(Z80_CPU *z) {  }
void DEC_H(Z80_CPU *z) {  }
void LD_H_nn(Z80_CPU *z) {  }
void DAA(Z80_CPU *z) {  }
void JR_Z_n(Z80_CPU *z) {  }
void ADD_HL_HL(Z80_CPU *z) {  }
void LD_HL_nnm(Z80_CPU *z) {  }
void DEC_HL(Z80_CPU *z) {  }
void INC_L(Z80_CPU *z) {  }
void DEC_L(Z80_CPU *z) {  }
void LD_L_n(Z80_CPU *z) {  }
void CPL(Z80_CPU *z) {  }

// 0x30
void JR_NC_n(Z80_CPU *z) {  }
void LD_SP_nn(Z80_CPU *z) {  }
void LD_nnm_A(Z80_CPU *z) {  }
void INC_SP(Z80_CPU *z) {  }
void INC_HLm(Z80_CPU *z) {  }
void DEC_HLm(Z80_CPU *z) {  }
void LD_HLm_n(Z80_CPU *z) {  }
void SCF(Z80_CPU *z) {  }
void JR_C_n(Z80_CPU *z) {  }
void ADD_HL_SP(Z80_CPU *z) {  }
void LD_A_nnm(Z80_CPU *z) {  }
void DEC_SP(Z80_CPU *z) {  }
void INC_A(Z80_CPU *z) {  }
void DEC_A(Z80_CPU *z) {  }
void LD_A_n(Z80_CPU *z) {  }
void CCF(Z80_CPU *z) {  }

// 0x40
void LD_B_B(Z80_CPU *z) { ld_byte(z, &z->B, z->B); }
void LD_B_C(Z80_CPU *z) { ld_byte(z, &z->B, z->C); }
void LD_B_D(Z80_CPU *z) { ld_byte(z, &z->B, z->D); }
void LD_B_E(Z80_CPU *z) { ld_byte(z, &z->B, z->E); }
void LD_B_H(Z80_CPU *z) { ld_byte(z, &z->B, z->H); }
void LD_B_L(Z80_CPU *z) { ld_byte(z, &z->B, z->L); }
void LD_B_HLm(Z80_CPU *z) { ld_byte(z, &z->B, mem_HL(z)); }
void LD_B_A(Z80_CPU *z) { ld_byte(z, &z->B, z->A); }
void LD_C_B(Z80_CPU *z) { ld_byte(z, &z->C, z->B); }
void LD_C_C(Z80_CPU *z) { ld_byte(z, &z->C, z->C); }
void LD_C_D(Z80_CPU *z) { ld_byte(z, &z->C, z->D); }
void LD_C_E(Z80_CPU *z) { ld_byte(z, &z->C, z->E); }
void LD_C_H(Z80_CPU *z) { ld_byte(z, &z->C, z->H); }
void LD_C_L(Z80_CPU *z) { ld_byte(z, &z->C, z->L); }
void LD_C_HLm(Z80_CPU *z) { ld_byte(z, &z->C, mem_HL(z)); }
void LD_C_A(Z80_CPU *z) { ld_byte(z, &z->C, z->A); }

// 0x50
void LD_D_B(Z80_CPU *z) { ld_byte(z, &z->D, z->B); }
void LD_D_C(Z80_CPU *z) { ld_byte(z, &z->D, z->C); }
void LD_D_D(Z80_CPU *z) { ld_byte(z, &z->D, z->D); }
void LD_D_E(Z80_CPU *z) { ld_byte(z, &z->D, z->E); }
void LD_D_H(Z80_CPU *z) { ld_byte(z, &z->D, z->H); }
void LD_D_L(Z80_CPU *z) { ld_byte(z, &z->D, z->L); }
void LD_D_HLm(Z80_CPU *z) { ld_byte(z, &z->D, mem_HL(z)); }
void LD_D_A(Z80_CPU *z) { ld_byte(z, &z->D, z->A); }
void LD_E_B(Z80_CPU *z) { ld_byte(z, &z->E, z->B); }
void LD_E_C(Z80_CPU *z) { ld_byte(z, &z->E, z->C); }
void LD_E_D(Z80_CPU *z) { ld_byte(z, &z->E, z->D); }
void LD_E_E(Z80_CPU *z) { ld_byte(z, &z->E, z->E); }
void LD_E_H(Z80_CPU *z) { ld_byte(z, &z->E, z->H); }
void LD_E_L(Z80_CPU *z) { ld_byte(z, &z->E, z->L); }
void LD_E_HLm(Z80_CPU *z) { ld_byte(z, &z->E, mem_HL(z)); }
void LD_E_A(Z80_CPU *z) { ld_byte(z, &z->E, z->A); }

// 0x60
void LD_H_B(Z80_CPU *z) { ld_byte(z, &z->H, z->B); }
void LD_H_C(Z80_CPU *z) { ld_byte(z, &z->H, z->C); }
void LD_H_D(Z80_CPU *z) { ld_byte(z, &z->H, z->D); }
void LD_H_E(Z80_CPU *z) { ld_byte(z, &z->H, z->E); }
void LD_H_H(Z80_CPU *z) { ld_byte(z, &z->H, z->H); }
void LD_H_L(Z80_CPU *z) { ld_byte(z, &z->H, z->L); }
void LD_H_HLm(Z80_CPU *z) { ld_byte(z, &z->H, mem_HL(z)); }
void LD_H_A(Z80_CPU *z) { ld_byte(z, &z->H, z->A); }
void LD_L_B(Z80_CPU *z) { ld_byte(z, &z->L, z->B); }
void LD_L_C(Z80_CPU *z) { ld_byte(z, &z->L, z->C); }
void LD_L_D(Z80_CPU *z) { ld_byte(z, &z->L, z->D); }
void LD_L_E(Z80_CPU *z) { ld_byte(z, &z->L, z->E); }
void LD_L_H(Z80_CPU *z) { ld_byte(z, &z->L, z->H); }
void LD_L_L(Z80_CPU *z) { ld_byte(z, &z->L, z->L); }
void LD_L_HLm(Z80_CPU *z) { ld_byte(z, &z->L, mem_HL(z)); }
void LD_L_A(Z80_CPU *z) { ld_byte(z, &z->L, z->A); }

// 0x70
void LD_HLm_B(Z80_CPU *z) {  }
void LD_HLm_C(Z80_CPU *z) {  }
void LD_HLm_D(Z80_CPU *z) {  }
void LD_HLm_E(Z80_CPU *z) {  }
void LD_HLm_H(Z80_CPU *z) {  }
void LD_HLm_L(Z80_CPU *z) {  }
void HALT(Z80_CPU *z) { z->State = STOPPED; }
void LD_HLm_A(Z80_CPU *z) {  }
void LD_A_B(Z80_CPU *z) { ld_byte(z, &z->A, z->B); }
void LD_A_C(Z80_CPU *z) { ld_byte(z, &z->A, z->C); }
void LD_A_D(Z80_CPU *z) { ld_byte(z, &z->A, z->D); }
void LD_A_E(Z80_CPU *z) { ld_byte(z, &z->A, z->E); }
void LD_A_H(Z80_CPU *z) { ld_byte(z, &z->A, z->H); }
void LD_A_L(Z80_CPU *z) { ld_byte(z, &z->A, z->L); }
void LD_A_HLm(Z80_CPU *z) { ld_byte(z, &z->A, mem_HL(z)); }
void LD_A_A(Z80_CPU *z) { ld_byte(z, &z->A, z->A); }

// 0x80
void ADD_A_B(Z80_CPU *z) {  }
void ADD_A_C(Z80_CPU *z) {  }
void ADD_A_D(Z80_CPU *z) {  }
void ADD_A_E(Z80_CPU *z) {  }
void ADD_A_H(Z80_CPU *z) {  }
void ADD_A_L(Z80_CPU *z) {  }
void ADD_A_HLm(Z80_CPU *z) {  }
void ADD_A_A(Z80_CPU *z) {  }
void ADC_A_B(Z80_CPU *z) {  }
void ADC_A_C(Z80_CPU *z) {  }
void ADC_A_D(Z80_CPU *z) {  }
void ADC_A_E(Z80_CPU *z) {  }
void ADC_A_H(Z80_CPU *z) {  }
void ADC_A_L(Z80_CPU *z) {  }
void ADC_A_HLm(Z80_CPU *z) {  }
void ADC_A_A(Z80_CPU *z) {  }

// 0x90
void SUB_B(Z80_CPU *z) {  }
void SUB_C(Z80_CPU *z) {  }
void SUB_D(Z80_CPU *z) {  }
void SUB_E(Z80_CPU *z) {  }
void SUB_H(Z80_CPU *z) {  }
void SUB_L(Z80_CPU *z) {  }
void SUB_HLm(Z80_CPU *z) {  }
void SUB_A(Z80_CPU *z) {  }
void SBC_A_B(Z80_CPU *z) {  }
void SBC_A_C(Z80_CPU *z) {  }
void SBC_A_D(Z80_CPU *z) {  }
void SBC_A_E(Z80_CPU *z) {  }
void SBC_A_H(Z80_CPU *z) {  }
void SBC_A_L(Z80_CPU *z) {  }
void SBC_A_HLm(Z80_CPU *z) {  }
void SBC_A_A(Z80_CPU *z) {  }

// 0xA0
void AND_B(Z80_CPU *z) {  }
void AND_C(Z80_CPU *z) {  }
void AND_D(Z80_CPU *z) {  }
void AND_E(Z80_CPU *z) {  }
void AND_H(Z80_CPU *z) {  }
void AND_L(Z80_CPU *z) {  }
void AND_HLm(Z80_CPU *z) {  }
void AND_A(Z80_CPU *z) {  }
void XOR_B(Z80_CPU *z) {  }
void XOR_C(Z80_CPU *z) {  }
void XOR_D(Z80_CPU *z) {  }
void XOR_E(Z80_CPU *z) {  }
void XOR_H(Z80_CPU *z) {  }
void XOR_L(Z80_CPU *z) {  }
void XOR_HLm(Z80_CPU *z) {  }
void XOR_A(Z80_CPU *z) {  }

// 0xB0
void OR_B(Z80_CPU *z) {  }
void OR_C(Z80_CPU *z) {  }
void OR_D(Z80_CPU *z) {  }
void OR_E(Z80_CPU *z) {  }
void OR_H(Z80_CPU *z) {  }
void OR_L(Z80_CPU *z) {  }
void OR_HLm(Z80_CPU *z) {  }
void OR_A(Z80_CPU *z) {  }
void CP_B(Z80_CPU *z) {  }
void CP_C(Z80_CPU *z) {  }
void CP_D(Z80_CPU *z) {  }
void CP_E(Z80_CPU *z) {  }
void CP_H(Z80_CPU *z) {  }
void CP_L(Z80_CPU *z) {  }
void CP_HLm(Z80_CPU *z) {  }
void CP_A(Z80_CPU *z) {  }

// 0xC0
void RET_NZ(Z80_CPU *z) {  }
void POP_BC(Z80_CPU *z) {  }
void JP_NZ_nn(Z80_CPU *z) {  }
void JP_nn(Z80_CPU *z) {  }
void CALL_NZ_nn(Z80_CPU *z) {  }
void PUSH_BC(Z80_CPU *z) {  }
void ADD_A_n(Z80_CPU *z) {  }
void RST_00h(Z80_CPU *z) {  }
void RET_Z(Z80_CPU *z) {  }
void RET(Z80_CPU *z) {  }
void JP_Z_nn(Z80_CPU *z) {  }
void BITS(Z80_CPU *z) {  }
void CALL_Z_nn(Z80_CPU *z) {  }
void CALL_nn(Z80_CPU *z) {  }
void ADC_A_n(Z80_CPU *z) {  }
void RST_08h(Z80_CPU *z) {  }

// 0xD0
void RET_NC(Z80_CPU *z) {  }
void POP_DE(Z80_CPU *z) {  }
void JP_NC_nn(Z80_CPU *z) {  }
void OUT_nm_a(Z80_CPU *z) {  }
void CALL_NC_nn(Z80_CPU *z) {  }
void PUSH_DE(Z80_CPU *z) {  }
void SUB_n(Z80_CPU *z) {  }
void RST_10h(Z80_CPU *z) {  }
void RET_C(Z80_CPU *z) {  }
void EXX(Z80_CPU *z) {  }
void JP_C_nn(Z80_CPU *z) {  }
void IN_A_nm(Z80_CPU *z) {  }
void CALL_C_nn(Z80_CPU *z) {  }
void IX(Z80_CPU *z) {  }
void SBC_A_n(Z80_CPU *z) {  }
void RST_18h(Z80_CPU *z) {  }

// 0xE0
void RET_PO(Z80_CPU *z) {  }
void POP_HL(Z80_CPU *z) {  }
void JP_PO_nn(Z80_CPU *z) {  }
void EX_SPm_HL(Z80_CPU *z) {  }
void CALL_PO_nn(Z80_CPU *z) {  }
void PUSH_HL(Z80_CPU *z) {  }
void AND_n(Z80_CPU *z) {  }
void RST_20h(Z80_CPU *z) {  }
void RET_PE(Z80_CPU *z) {  }
void JP_HLm(Z80_CPU *z) {  }
void JP_PE_nn(Z80_CPU *z) {  }
void EX_DE_HL(Z80_CPU *z) {  }
void CALL_PE_nn(Z80_CPU *z) {  }
void EXTD(Z80_CPU *z) {  }
void XOR_n(Z80_CPU *z) {  }
void RST_28h(Z80_CPU *z) {  }

// 0xF0
void RET_P(Z80_CPU *z) {  }
void POP_AF(Z80_CPU *z) {  }
void JP_P_nn(Z80_CPU *z) {  }
void DI(Z80_CPU *z) {  }
void CALL_P_nn(Z80_CPU *z) {  }
void PUSH_AF(Z80_CPU *z) {  }
void OR_n(Z80_CPU *z) {  }
void RST_30h(Z80_CPU *z) {  }
void RET_M(Z80_CPU *z) {  }
void LD_SP_HL(Z80_CPU *z) {  }
void JP_M_nn(Z80_CPU *z) {  }
void EI(Z80_CPU *z) {  }
void CALL_M_nn(Z80_CPU *z) {  }
void IY(Z80_CPU *z) {  }
void CP_n(Z80_CPU *z) {  }
void RST_38h(Z80_CPU *z) {  }
