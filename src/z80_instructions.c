#include "z80_instructions.h"
#include "z80_logic.h"

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
void LD_B_HLm(Z80_CPU *z) { ld_byte(z, &z->B, mem_nn(z, z->H, z->L)); }
void LD_B_A(Z80_CPU *z) { ld_byte(z, &z->B, z->A); }
void LD_C_B(Z80_CPU *z) { ld_byte(z, &z->C, z->B); }
void LD_C_C(Z80_CPU *z) { ld_byte(z, &z->C, z->C); }
void LD_C_D(Z80_CPU *z) { ld_byte(z, &z->C, z->D); }
void LD_C_E(Z80_CPU *z) { ld_byte(z, &z->C, z->E); }
void LD_C_H(Z80_CPU *z) { ld_byte(z, &z->C, z->H); }
void LD_C_L(Z80_CPU *z) { ld_byte(z, &z->C, z->L); }
void LD_C_HLm(Z80_CPU *z) { ld_byte(z, &z->C, mem_nn(z, z->H, z->L)); }
void LD_C_A(Z80_CPU *z) { ld_byte(z, &z->C, z->A); }

// 0x50
void LD_D_B(Z80_CPU *z) {  }
void LD_D_C(Z80_CPU *z) {  }
void LD_D_D(Z80_CPU *z) {  }
void LD_D_E(Z80_CPU *z) {  }
void LD_D_H(Z80_CPU *z) {  }
void LD_D_L(Z80_CPU *z) {  }
void LD_D_HLm(Z80_CPU *z) {  }
void LD_D_A(Z80_CPU *z) {  }
void LD_E_B(Z80_CPU *z) {  }
void LD_E_C(Z80_CPU *z) {  }
void LD_E_D(Z80_CPU *z) {  }
void LD_E_E(Z80_CPU *z) {  }
void LD_E_H(Z80_CPU *z) {  }
void LD_E_L(Z80_CPU *z) {  }
void LD_E_HLm(Z80_CPU *z) {  }
void LD_E_A(Z80_CPU *z) {  }

// 0x60
void LD_H_B(Z80_CPU *z) {  }
void LD_H_C(Z80_CPU *z) {  }
void LD_H_D(Z80_CPU *z) {  }
void LD_H_E(Z80_CPU *z) {  }
void LD_H_H(Z80_CPU *z) {  }
void LD_H_L(Z80_CPU *z) {  }
void LD_H_HLm(Z80_CPU *z) {  }
void LD_H_A(Z80_CPU *z) {  }
void LD_L_B(Z80_CPU *z) {  }
void LD_L_C(Z80_CPU *z) {  }
void LD_L_D(Z80_CPU *z) {  }
void LD_L_E(Z80_CPU *z) {  }
void LD_L_H(Z80_CPU *z) {  }
void LD_L_L(Z80_CPU *z) {  }
void LD_L_HLm(Z80_CPU *z) {  }
void LD_L_A(Z80_CPU *z) {  }

// 0x70
void LD_HLm_B(Z80_CPU *z) {  }
void LD_HLm_C(Z80_CPU *z) {  }
void LD_HLm_D(Z80_CPU *z) {  }
void LD_HLm_E(Z80_CPU *z) {  }
void LD_HLm_H(Z80_CPU *z) {  }
void LD_HLm_L(Z80_CPU *z) {  }
void HALT(Z80_CPU *z) {  }
void LD_HLm_A(Z80_CPU *z) {  }
void LD_A_B(Z80_CPU *z) {  }
void LD_A_C(Z80_CPU *z) {  }
void LD_A_D(Z80_CPU *z) {  }
void LD_A_E(Z80_CPU *z) {  }
void LD_A_H(Z80_CPU *z) {  }
void LD_A_L(Z80_CPU *z) {  }
void LD_A_HLm(Z80_CPU *z) {  }
void LD_A_A(Z80_CPU *z) {  }

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
