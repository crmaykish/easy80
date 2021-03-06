#include "z80_instructions_main.h"
#include "z80_instructions_common.h"
#include "flags.h"
#include "bitmath.h"

// 0x00
void NOP(Z80_CPU *z) { /* do nothing */ }
void LD_BC_nn(Z80_CPU *z) { ld_word(z, z->BC, op_nn(z)); }
void LD_BCm_A(Z80_CPU *z) { SetMemVal(z, *z->BC, *z->A); }
void INC_BC(Z80_CPU *z) { inc_word(z, z->BC); }
void INC_B(Z80_CPU *z) { inc_byte(z, z->B); }
void DEC_B(Z80_CPU *z) { dec_byte(z, z->B); }
void LD_B_n(Z80_CPU *z) { ld_byte(z, z->B, Op(z, 1)); }
void RLCA(Z80_CPU *z) { rlca(z); }
void EX_AF_AFp(Z80_CPU *z) { ex(z->AF, z->AFp); }
void ADD_HL_BC(Z80_CPU *z) { add_word(z, z->HL, *z->BC); }
void LD_A_BCm(Z80_CPU *z) { ld_byte(z, z->A, GetMemVal(z, *z->BC)); }
void DEC_BC(Z80_CPU *z) { dec_word(z, z->BC); }
void INC_C(Z80_CPU *z) { inc_byte(z, z->C); }
void DEC_C(Z80_CPU *z) { dec_byte(z, z->C); }
void LD_C_n(Z80_CPU *z) { ld_byte(z, z->C, Op(z, 1)); }
void RRCA(Z80_CPU *z) { rrca(z); }

// 0x10
void DJNZ_n(Z80_CPU *z) { *z->B--; z->PC += (*z->B != 0 ? (int8_t) Op(z, 1) + OP_BYTE : 1); } // op1 is a signed value
void LD_DE_nn(Z80_CPU *z) { ld_word(z, z->DE, op_nn(z)); }
void LD_DEm_A(Z80_CPU *z) { SetMemVal(z, *z->DE, *z->A); }
void INC_DE(Z80_CPU *z) { inc_word(z, z->DE); }
void INC_D(Z80_CPU *z) { inc_byte(z, z->D); }
void DEC_D(Z80_CPU *z) { dec_byte(z, z->D); }
void LD_D_n(Z80_CPU *z) { ld_byte(z, z->D, Op(z, 1)); }
void RLA(Z80_CPU *z) { rla(z); }
void JR_n(Z80_CPU *z) { z->PC += ((int8_t) Op(z, 1) + OP_BYTE); }      // op1 is a signed value
void ADD_HL_DE(Z80_CPU *z) { add_word(z, z->HL, *z->DE); }
void LD_A_DEm(Z80_CPU *z) { ld_byte(z, z->A, GetMemVal(z, *z->DE)); }
void DEC_DE(Z80_CPU *z) { dec_word(z, z->DE); }
void INC_E(Z80_CPU *z) { inc_byte(z, z->E); }
void DEC_E(Z80_CPU *z) { dec_byte(z, z->E); }
void LD_E_n(Z80_CPU *z) { ld_byte(z, z->E, Op(z, 1)); }
void RRA(Z80_CPU *z) { rra(z); }

// 0x20
void JR_NZ_n(Z80_CPU *z) { z->PC += OP_BYTE; if (!flag_get(z->F, FLAG_Z)) { z->PC += (int8_t) Op(z, 1); } }
void LD_HL_nn(Z80_CPU *z) { ld_word(z, z->HL, op_nn(z)); }
void LD_nnm_HL(Z80_CPU *z) { SetMemVal(z, op_nn(z), *z->L); SetMemVal(z, op_nn(z) + 1, *z->H); }
void INC_HL(Z80_CPU *z) { inc_word(z, z->HL); }
void INC_H(Z80_CPU *z) { inc_byte(z, z->H); }
void DEC_H(Z80_CPU *z) { dec_byte(z, z->H); }
void LD_H_n(Z80_CPU *z) { ld_byte(z, z->H, Op(z, 1)); }
void DAA(Z80_CPU *z) { daa(z); }
void JR_Z_n(Z80_CPU *z) { z->PC += OP_BYTE; if (flag_get(z->F, FLAG_Z)) { z->PC += (int8_t) Op(z, 1); } }
void ADD_HL_HL(Z80_CPU *z) { add_word(z, z->HL, *z->HL); }
void LD_HL_nnm(Z80_CPU *z) { ld_word(z, z->HL, GetMemVal(z, op_nn(z))); }
void DEC_HL(Z80_CPU *z) { dec_word(z, z->HL); }
void INC_L(Z80_CPU *z) { inc_byte(z, z->L); }
void DEC_L(Z80_CPU *z) { dec_byte(z, z->L); }
void LD_L_n(Z80_CPU *z) { ld_byte(z, z->L, Op(z, 1)); }
void CPL(Z80_CPU *z) { flag_set(z->F, FLAG_H, true); flag_set(z->F, FLAG_N, true); *z->A ^= 0xFF; }

// 0x30
void JR_NC_n(Z80_CPU *z) { z->PC += OP_BYTE; if (!flag_get(z->F, FLAG_C)) { z->PC += (int8_t) Op(z, 1); } }
void LD_SP_nn(Z80_CPU *z) { ld_word(z, &z->SP, op_nn(z)); }
void LD_nnm_A(Z80_CPU *z) { SetMemVal(z, op_nn(z), *z->A); }
void INC_SP(Z80_CPU *z) { inc_word(z, &z->SP); }
void INC_HLm(Z80_CPU *z) { SetMemVal(z, *z->HL, GetMemVal(z, *z->HL) + 1); }
void DEC_HLm(Z80_CPU *z) { dec_byte(z, &z->Memory[*z->HL]); }
void LD_HLm_n(Z80_CPU *z) { SetMemVal(z, *z->HL, Op(z, 1)); }
void SCF(Z80_CPU *z) { flag_set(z->F, FLAG_C, true); flag_set(z->F, FLAG_N, false); flag_set(z->F, FLAG_H, false); }
void JR_C_n(Z80_CPU *z) { z->PC += OP_BYTE; if (flag_get(z->F, FLAG_C)) { z->PC += (int8_t) Op(z, 1); } }
void ADD_HL_SP(Z80_CPU *z) { add_word(z, z->HL, z->SP); }
void LD_A_nnm(Z80_CPU *z) { ld_byte(z, z->A, GetMemVal(z, combine(Op(z, 2), Op(z, 1)))); }
void DEC_SP(Z80_CPU *z) { dec_word(z, &z->SP); }
void INC_A(Z80_CPU *z) { inc_byte(z, z->A); }
void DEC_A(Z80_CPU *z) { dec_byte(z, z->A); }
void LD_A_n(Z80_CPU *z) { ld_byte(z, z->A, Op(z, 1)); }
void CCF(Z80_CPU *z) { flag_set(z->F, FLAG_H, flag_get(z->F, FLAG_C)); flag_set(z->F, FLAG_C, !flag_get(z->F, FLAG_C)); }

// 0x40
void LD_B_B(Z80_CPU *z) { ld_byte(z, z->B, *z->B); }
void LD_B_C(Z80_CPU *z) { ld_byte(z, z->B, *z->C); }
void LD_B_D(Z80_CPU *z) { ld_byte(z, z->B, *z->D); }
void LD_B_E(Z80_CPU *z) { ld_byte(z, z->B, *z->E); }
void LD_B_H(Z80_CPU *z) { ld_byte(z, z->B, *z->H); }
void LD_B_L(Z80_CPU *z) { ld_byte(z, z->B, *z->L); }
void LD_B_HLm(Z80_CPU *z) { ld_byte(z, z->B, GetMemVal(z, *z->HL)); }
void LD_B_A(Z80_CPU *z) { ld_byte(z, z->B, *z->A); }
void LD_C_B(Z80_CPU *z) { ld_byte(z, z->C, *z->B); }
void LD_C_C(Z80_CPU *z) { ld_byte(z, z->C, *z->C); }
void LD_C_D(Z80_CPU *z) { ld_byte(z, z->C, *z->D); }
void LD_C_E(Z80_CPU *z) { ld_byte(z, z->C, *z->E); }
void LD_C_H(Z80_CPU *z) { ld_byte(z, z->C, *z->H); }
void LD_C_L(Z80_CPU *z) { ld_byte(z, z->C, *z->L); }
void LD_C_HLm(Z80_CPU *z) { ld_byte(z, z->C, GetMemVal(z, *z->HL)); }
void LD_C_A(Z80_CPU *z) { ld_byte(z, z->C, *z->A); }

// 0x50
void LD_D_B(Z80_CPU *z) { ld_byte(z, z->D, *z->B); }
void LD_D_C(Z80_CPU *z) { ld_byte(z, z->D, *z->C); }
void LD_D_D(Z80_CPU *z) { ld_byte(z, z->D, *z->D); }
void LD_D_E(Z80_CPU *z) { ld_byte(z, z->D, *z->E); }
void LD_D_H(Z80_CPU *z) { ld_byte(z, z->D, *z->H); }
void LD_D_L(Z80_CPU *z) { ld_byte(z, z->D, *z->L); }
void LD_D_HLm(Z80_CPU *z) { ld_byte(z, z->D, GetMemVal(z, *z->HL)); }
void LD_D_A(Z80_CPU *z) { ld_byte(z, z->D, *z->A); }
void LD_E_B(Z80_CPU *z) { ld_byte(z, z->E, *z->B); }
void LD_E_C(Z80_CPU *z) { ld_byte(z, z->E, *z->C); }
void LD_E_D(Z80_CPU *z) { ld_byte(z, z->E, *z->D); }
void LD_E_E(Z80_CPU *z) { ld_byte(z, z->E, *z->E); }
void LD_E_H(Z80_CPU *z) { ld_byte(z, z->E, *z->H); }
void LD_E_L(Z80_CPU *z) { ld_byte(z, z->E, *z->L); }
void LD_E_HLm(Z80_CPU *z) { ld_byte(z, z->E, GetMemVal(z, *z->HL)); }
void LD_E_A(Z80_CPU *z) { ld_byte(z, z->E, *z->A); }

// 0x60
void LD_H_B(Z80_CPU *z) { ld_byte(z, z->H, *z->B); }
void LD_H_C(Z80_CPU *z) { ld_byte(z, z->H, *z->C); }
void LD_H_D(Z80_CPU *z) { ld_byte(z, z->H, *z->D); }
void LD_H_E(Z80_CPU *z) { ld_byte(z, z->H, *z->E); }
void LD_H_H(Z80_CPU *z) { ld_byte(z, z->H, *z->H); }
void LD_H_L(Z80_CPU *z) { ld_byte(z, z->H, *z->L); }
void LD_H_HLm(Z80_CPU *z) { ld_byte(z, z->H, GetMemVal(z, *z->HL)); }
void LD_H_A(Z80_CPU *z) { ld_byte(z, z->H, *z->A); }
void LD_L_B(Z80_CPU *z) { ld_byte(z, z->L, *z->B); }
void LD_L_C(Z80_CPU *z) { ld_byte(z, z->L, *z->C); }
void LD_L_D(Z80_CPU *z) { ld_byte(z, z->L, *z->D); }
void LD_L_E(Z80_CPU *z) { ld_byte(z, z->L, *z->E); }
void LD_L_H(Z80_CPU *z) { ld_byte(z, z->L, *z->H); }
void LD_L_L(Z80_CPU *z) { ld_byte(z, z->L, *z->L); }
void LD_L_HLm(Z80_CPU *z) { ld_byte(z, z->L, GetMemVal(z, *z->HL)); }
void LD_L_A(Z80_CPU *z) { ld_byte(z, z->L, *z->A); }

// 0x70
void LD_HLm_B(Z80_CPU *z) { SetMemVal(z, *z->HL, *z->B); }
void LD_HLm_C(Z80_CPU *z) { SetMemVal(z, *z->HL, *z->C); }
void LD_HLm_D(Z80_CPU *z) { SetMemVal(z, *z->HL, *z->D); }
void LD_HLm_E(Z80_CPU *z) { SetMemVal(z, *z->HL, *z->E); }
void LD_HLm_H(Z80_CPU *z) { SetMemVal(z, *z->HL, *z->H); }
void LD_HLm_L(Z80_CPU *z) { SetMemVal(z, *z->HL, *z->L); }
void HALT(Z80_CPU *z) { z->State = STOPPED; }
void LD_HLm_A(Z80_CPU *z) { SetMemVal(z, *z->HL, *z->A); }
void LD_A_B(Z80_CPU *z) { ld_byte(z, z->A, *z->B); }
void LD_A_C(Z80_CPU *z) { ld_byte(z, z->A, *z->C); }
void LD_A_D(Z80_CPU *z) { ld_byte(z, z->A, *z->D); }
void LD_A_E(Z80_CPU *z) { ld_byte(z, z->A, *z->E); }
void LD_A_H(Z80_CPU *z) { ld_byte(z, z->A, *z->H); }
void LD_A_L(Z80_CPU *z) { ld_byte(z, z->A, *z->L); }
void LD_A_HLm(Z80_CPU *z) { ld_byte(z, z->A, GetMemVal(z, *z->HL)); }
void LD_A_A(Z80_CPU *z) { ld_byte(z, z->A, *z->A); }

// 0x80
void ADD_A_B(Z80_CPU *z) { add_byte(z, *z->B); }
void ADD_A_C(Z80_CPU *z) { add_byte(z, *z->C); }
void ADD_A_D(Z80_CPU *z) { add_byte(z, *z->D); }
void ADD_A_E(Z80_CPU *z) { add_byte(z, *z->E); }
void ADD_A_H(Z80_CPU *z) { add_byte(z, *z->H); }
void ADD_A_L(Z80_CPU *z) { add_byte(z, *z->L); }
void ADD_A_HLm(Z80_CPU *z) { add_byte(z, GetMemVal(z, *z->HL)); }
void ADD_A_A(Z80_CPU *z) { add_byte(z, *z->A); }
void ADC_A_B(Z80_CPU *z) { adc_byte(z, *z->B); }
void ADC_A_C(Z80_CPU *z) { adc_byte(z, *z->C); }
void ADC_A_D(Z80_CPU *z) { adc_byte(z, *z->D); }
void ADC_A_E(Z80_CPU *z) { adc_byte(z, *z->E); }
void ADC_A_H(Z80_CPU *z) { adc_byte(z, *z->H); }
void ADC_A_L(Z80_CPU *z) { adc_byte(z, *z->L); }
void ADC_A_HLm(Z80_CPU *z) { adc_byte(z, GetMemVal(z, *z->HL)); }
void ADC_A_A(Z80_CPU *z) { adc_byte(z, *z->A); }

// 0x90
void SUB_B(Z80_CPU *z) { sub(z, *z->B); }
void SUB_C(Z80_CPU *z) { sub(z, *z->C); }
void SUB_D(Z80_CPU *z) { sub(z, *z->D); }
void SUB_E(Z80_CPU *z) { sub(z, *z->E); }
void SUB_H(Z80_CPU *z) { sub(z, *z->H); }
void SUB_L(Z80_CPU *z) { sub(z, *z->L); }
void SUB_HLm(Z80_CPU *z) { sub(z, GetMemVal(z, *z->HL)); }
void SUB_A(Z80_CPU *z) { sub(z, *z->A); }
void SBC_A_B(Z80_CPU *z) { sbc(z, *z->B); }
void SBC_A_C(Z80_CPU *z) { sbc(z, *z->C); }
void SBC_A_D(Z80_CPU *z) { sbc(z, *z->D); }
void SBC_A_E(Z80_CPU *z) { sbc(z, *z->E); }
void SBC_A_H(Z80_CPU *z) { sbc(z, *z->H); }
void SBC_A_L(Z80_CPU *z) { sbc(z, *z->L); }
void SBC_A_HLm(Z80_CPU *z) { sbc(z, GetMemVal(z, *z->HL)); }
void SBC_A_A(Z80_CPU *z) { sbc(z, *z->A); }

// 0xA0
void AND_B(Z80_CPU *z) { and(z, *z->B); }
void AND_C(Z80_CPU *z) { and(z, *z->C); }
void AND_D(Z80_CPU *z) { and(z, *z->D); }
void AND_E(Z80_CPU *z) { and(z, *z->E); }
void AND_H(Z80_CPU *z) { and(z, *z->H); }
void AND_L(Z80_CPU *z) { and(z, *z->L); }
void AND_HLm(Z80_CPU *z) { and(z, GetMemVal(z, *z->HL)); }
void AND_A(Z80_CPU *z) { and(z, *z->A); }
void XOR_B(Z80_CPU *z) { xor(z, *z->B); }
void XOR_C(Z80_CPU *z) { xor(z, *z->C); }
void XOR_D(Z80_CPU *z) { xor(z, *z->D); }
void XOR_E(Z80_CPU *z) { xor(z, *z->E); }
void XOR_H(Z80_CPU *z) { xor(z, *z->H); }
void XOR_L(Z80_CPU *z) { xor(z, *z->L); }
void XOR_HLm(Z80_CPU *z) { xor(z, GetMemVal(z, *z->HL)); }
void XOR_A(Z80_CPU *z) { xor(z, *z->A); }

// 0xB0
void OR_B(Z80_CPU *z) { or(z, *z->B); }
void OR_C(Z80_CPU *z) { or(z, *z->C); }
void OR_D(Z80_CPU *z) { or(z, *z->D); }
void OR_E(Z80_CPU *z) { or(z, *z->E); }
void OR_H(Z80_CPU *z) { or(z, *z->H); }
void OR_L(Z80_CPU *z) { or(z, *z->L); }
void OR_HLm(Z80_CPU *z) { or(z, GetMemVal(z, *z->HL)); }
void OR_A(Z80_CPU *z) { or(z, *z->A); }
void CP_B(Z80_CPU *z) { cp(z, *z->B); }
void CP_C(Z80_CPU *z) { cp(z, *z->C); }
void CP_D(Z80_CPU *z) { cp(z, *z->D); }
void CP_E(Z80_CPU *z) { cp(z, *z->E); }
void CP_H(Z80_CPU *z) { cp(z, *z->H); }
void CP_L(Z80_CPU *z) { cp(z, *z->L); }
void CP_HLm(Z80_CPU *z) { cp(z, GetMemVal(z, *z->HL)); }
void CP_A(Z80_CPU *z) { cp(z, *z->A); }

// 0xC0
void RET_NZ(Z80_CPU *z) { ret(z, !flag_get(z->F, FLAG_Z)); }
void POP_BC(Z80_CPU *z) { *z->BC = pop(z); }
void JP_NZ_nn(Z80_CPU *z) { z->PC = !flag_get(z->F, FLAG_Z) ? op_nn(z) : (z->PC + OP_WORD); }
void JP_nn(Z80_CPU *z) { z->PC = op_nn(z); }
void CALL_NZ_nn(Z80_CPU *z) { call(z, op_nn(z), !flag_get(z->F, FLAG_Z)); }
void PUSH_BC(Z80_CPU *z) { push(z, *z->BC); }
void ADD_A_n(Z80_CPU *z) { add_byte(z, Op(z, 1)); }
void RST_00h(Z80_CPU *z) { rst(z, 0x00); }
void RET_Z(Z80_CPU *z) { ret(z, flag_get(z->F, FLAG_Z)); }
void RET(Z80_CPU *z) { ret(z, true); }
void JP_Z_nn(Z80_CPU *z) { z->PC = flag_get(z->F, FLAG_Z) ? op_nn(z) : (z->PC + OP_WORD); }
void BITS(Z80_CPU *z) { /* BITS INSTRUCTION SET */ }
void CALL_Z_nn(Z80_CPU *z) { call(z, op_nn(z), flag_get(z->F, FLAG_Z)); }
void CALL_nn(Z80_CPU *z) { call(z, op_nn(z), true); }
void ADC_A_n(Z80_CPU *z) { adc_byte(z, Op(z, 1)); }
void RST_08h(Z80_CPU *z) { rst(z, 0x08); }

// 0xD0
void RET_NC(Z80_CPU *z) { ret(z, !flag_get(z->F, FLAG_C)); }
void POP_DE(Z80_CPU *z) { *z->DE = pop(z); }
void JP_NC_nn(Z80_CPU *z) { z->PC = !flag_get(z->F, FLAG_C) ? op_nn(z) : (z->PC + OP_WORD); }
void OUT_nm_a(Z80_CPU *z) { /* TODO: OUT */ }
void CALL_NC_nn(Z80_CPU *z) { call(z, op_nn(z), !flag_get(z->F, FLAG_C)); }
void PUSH_DE(Z80_CPU *z) { push(z, *z->DE); }
void SUB_n(Z80_CPU *z) { sub(z, Op(z, 1)); }
void RST_10h(Z80_CPU *z) { rst(z, 0x10); }
void RET_C(Z80_CPU *z) { ret(z, flag_get(z->F, FLAG_C)); }
void EXX(Z80_CPU *z) { ex(z->BC, z->BCp); ex(z->DE, z->DEp); ex(z->HL, z->HLp); }
void JP_C_nn(Z80_CPU *z) { z->PC = flag_get(z->F, FLAG_C) ? op_nn(z) : (z->PC + OP_WORD); }
void IN_A_nm(Z80_CPU *z) { /* TODO: IN */ }
void CALL_C_nn(Z80_CPU *z) { call(z, op_nn(z), flag_get(z->F, FLAG_C)); }
void IX(Z80_CPU *z) { /* IX INSTRUCTION SET */ }
void SBC_A_n(Z80_CPU *z) { sbc(z, Op(z, 1)); }
void RST_18h(Z80_CPU *z) { rst(z, 0x18); }

// 0xE0
void RET_PO(Z80_CPU *z) { ret(z, !flag_get(z->F, FLAG_PV)); }
void POP_HL(Z80_CPU *z) { *z->HL = pop(z); }
void JP_PO_nn(Z80_CPU *z) { z->PC = !flag_get(z->F, FLAG_PV) ? op_nn(z) : (z->PC + OP_WORD); }
void EX_SPm_HL(Z80_CPU *z) { uint16_t temp = GetMemVal(z, z->SP); SetMemVal(z, z->SP, *z->HL); *z->HL = temp; }
void CALL_PO_nn(Z80_CPU *z) { call(z, op_nn(z), !flag_get(z->F, FLAG_PV)); }
void PUSH_HL(Z80_CPU *z) { push(z, *z->HL); }
void AND_n(Z80_CPU *z) { and(z, Op(z, 1)); }
void RST_20h(Z80_CPU *z) { rst(z, 0x20); }
void RET_PE(Z80_CPU *z) { ret(z, flag_get(z->F, FLAG_PV)); }
void JP_HLm(Z80_CPU *z) { z->PC = GetMemVal(z, *z->HL); }
void JP_PE_nn(Z80_CPU *z) { z->PC = flag_get(z->F, FLAG_PV) ? op_nn(z) : (z->PC + OP_WORD); }
void EX_DE_HL(Z80_CPU *z) { ex(z->DE, z->HL); }
void CALL_PE_nn(Z80_CPU *z) { call(z, op_nn(z), flag_get(z->F, FLAG_PV)); }
void EXTD(Z80_CPU *z) { /* EXTD INSTRUCTION SET */ }
void XOR_n(Z80_CPU *z) { xor(z, Op(z, 1)); }
void RST_28h(Z80_CPU *z) { rst(z, 0x28); }

// 0xF0
void RET_P(Z80_CPU *z) { ret(z, !flag_get(z->F, FLAG_S)); }
void POP_AF(Z80_CPU *z) { *z->AF = pop(z); }
void JP_P_nn(Z80_CPU *z) { z->PC = !flag_get(z->F, FLAG_S) ? op_nn(z) : (z->PC + OP_WORD); }
void DI(Z80_CPU *z) { z->Interrupts = false; }
void CALL_P_nn(Z80_CPU *z) { call(z, op_nn(z), !flag_get(z->F, FLAG_S)); }
void PUSH_AF(Z80_CPU *z) { push(z, *z->AF); }
void OR_n(Z80_CPU *z) { or(z, Op(z, 1)); }
void RST_30h(Z80_CPU *z) { rst(z, 0x30); }
void RET_M(Z80_CPU *z) { ret(z, flag_get(z->F, FLAG_S)); }
void LD_SP_HL(Z80_CPU *z) { ld_word(z, &z->SP, *z->HL); }
void JP_M_nn(Z80_CPU *z) { z->PC = flag_get(z->F, FLAG_S) ? op_nn(z) : (z->PC + OP_WORD); }
void EI(Z80_CPU *z) { z->Interrupts = true; }
void CALL_M_nn(Z80_CPU *z) { call(z, op_nn(z), flag_get(z->F, FLAG_S)); }
void IY(Z80_CPU *z) { /* IY */ }
void CP_n(Z80_CPU *z) { cp(z, Op(z, 1)); }
void RST_38h(Z80_CPU *z) { rst(z, 0x38); }

// Main instruction opcode mapping
const Z80_Instruction MainInstructions[256] = {
    // 0x00 NAME            SIZE        CYCLES  HANDLER
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
    // 0x10 NAME            SIZE        CYCLES  HANDLER
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
    // 0x20 NAME            SIZE        CYCLES  HANDLER
    { 0x20, "JR NZ,*",      OP_BYTE,    12,     &JR_NZ_n },    // TODO: 12 or 7 clock cycles
    { 0x21, "LD HL,**",     OP_WORD,    10,     &LD_HL_nn },
    { 0x22, "LD (**),HL",   OP_WORD,    16,     &LD_nnm_HL },
    { 0x23, "INC HL",       OP_NONE,    6,      &INC_HL },
    { 0x24, "INC H",        OP_NONE,    4,      &INC_H },
    { 0x25, "DEC H",        OP_NONE,    4,      &DEC_H },
    { 0x26, "LD H,*",       OP_BYTE,    7,      &LD_H_n },
    { 0x27, "DAA",          OP_NONE,    4,      &DAA },
    { 0x28, "JR Z,*",       OP_BYTE,    12,     &JR_Z_n },     // TODO: 12 or 7 clock cycles
    { 0x29, "ADD HL,HL",    OP_NONE,    11,     &ADD_HL_HL },
    { 0x2A, "LD HL,(**)",   OP_WORD,    16,     &LD_HL_nnm },
    { 0x2B, "DEC HL",       OP_NONE,    6,      &DEC_HL },
    { 0x2C, "INC L",        OP_NONE,    4,      &INC_L },
    { 0x2D, "DEC L",        OP_NONE,    4,      &DEC_L },
    { 0x2E, "LD L,*",       OP_BYTE,    7,      &LD_L_n },
    { 0x2F, "CPL",          OP_NONE,    4,      &CPL },
    // 0x30 NAME            SIZE        CYCLES  HANDLER
    { 0x30, "JR NC,*",      OP_BYTE,    2,      &JR_NC_n },
    { 0x31, "LD SP,**",     OP_WORD,    3,      &LD_SP_nn },
    { 0x32, "LD (**),A",    OP_WORD,    3,      &LD_nnm_A },
    { 0x33, "INC SP",       OP_NONE,    1,      &INC_SP },
    { 0x34, "INC (HL)",     OP_NONE,    1,      &INC_HLm },
    { 0x35, "DEC (HL)",     OP_NONE,    1,      &DEC_HLm },
    { 0x36, "LD (HL),*",    OP_BYTE,    2,      &LD_HLm_n },
    { 0x37, "SCF",          OP_NONE,    1,      &SCF },
    { 0x38, "JR C,*",       OP_BYTE,    2,      &JR_C_n },
    { 0x39, "ADD HL,SP",    OP_NONE,    1,      &ADD_HL_SP },
    { 0x3A, "LD A,(**)",    OP_WORD,    3,      &LD_A_nnm },
    { 0x3B, "DEC SP",       OP_NONE,    1,      &DEC_SP },
    { 0x3C, "INC A",        OP_NONE,    1,      &INC_A },
    { 0x3D, "DEC A",        OP_NONE,    1,      &DEC_A },
    { 0x3E, "LD A,*",       OP_BYTE,    2,      &LD_A_n },
    { 0x3F, "CCF",          OP_NONE,    1,      &CCF },
    // 0x40 NAME            SIZE        CYCLES  HANDLER
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
    // 0x50 NAME            SIZE        CYCLES  HANDLER
    { 0x50, "LD D,B",       OP_NONE,    4,      &LD_D_B },
    { 0x51, "LD D,C",       OP_NONE,    4,      &LD_D_C },
    { 0x52, "LD D,D",       OP_NONE,    4,      &LD_D_D },
    { 0x53, "LD D,E",       OP_NONE,    4,      &LD_D_E },
    { 0x54, "LD D,H",       OP_NONE,    4,      &LD_D_H },
    { 0x55, "LD D,L",       OP_NONE,    4,      &LD_D_L },
    { 0x56, "LD D,(HL)",    OP_NONE,    7,      &LD_D_HLm },
    { 0x57, "LD D,A",       OP_NONE,    4,      &LD_D_A },
    { 0x58, "LD E,B",       OP_NONE,    4,      &LD_E_B },
    { 0x59, "LD E,C",       OP_NONE,    4,      &LD_E_C },
    { 0x5A, "LD E,D",       OP_NONE,    4,      &LD_E_D },
    { 0x5B, "LD E,E",       OP_NONE,    4,      &LD_E_E },
    { 0x5C, "LD E,H",       OP_NONE,    4,      &LD_E_H },
    { 0x5D, "LD E,L",       OP_NONE,    4,      &LD_E_L },
    { 0x5E, "LD E,(HL)",    OP_NONE,    7,      &LD_E_HLm },
    { 0x5F, "LD E,A",       OP_NONE,    4,      &LD_E_A },
    // 0x60 NAME            SIZE        CYCLES  HANDLER
    { 0x60, "LD H,B",       OP_NONE,    4,      &LD_H_B },
    { 0x61, "LD H,C",       OP_NONE,    4,      &LD_H_C },
    { 0x62, "LD H,D",       OP_NONE,    4,      &LD_H_D },
    { 0x63, "LD H,E",       OP_NONE,    4,      &LD_H_E },
    { 0x64, "LD H,H",       OP_NONE,    4,      &LD_H_H },
    { 0x65, "LD H,L",       OP_NONE,    4,      &LD_H_L },
    { 0x66, "LD H,(HL)",    OP_NONE,    7,      &LD_H_HLm },
    { 0x67, "LD H,A",       OP_NONE,    4,      &LD_H_A },
    { 0x68, "LD L,B",       OP_NONE,    4,      &LD_L_B },
    { 0x69, "LD L,C",       OP_NONE,    4,      &LD_L_C },
    { 0x6A, "LD L,D",       OP_NONE,    4,      &LD_L_D },
    { 0x6B, "LD L,E",       OP_NONE,    4,      &LD_L_E },
    { 0x6C, "LD L,H",       OP_NONE,    4,      &LD_L_H },
    { 0x6D, "LD L,L",       OP_NONE,    4,      &LD_L_L },
    { 0x6E, "LD L,(HL)",    OP_NONE,    7,      &LD_L_HLm },
    { 0x6F, "LD L,A",       OP_NONE,    4,      &LD_L_A },
    // 0x70 NAME            SIZE        CYCLES  HANDLER
    { 0x70, "LD (HL),B",    OP_NONE,    7,      &LD_HLm_B },
    { 0x71, "LD (HL),C",    OP_NONE,    7,      &LD_HLm_C },
    { 0x72, "LD (HL),D",    OP_NONE,    7,      &LD_HLm_D },
    { 0x73, "LD (HL),E",    OP_NONE,    7,      &LD_HLm_E },
    { 0x74, "LD (HL),H",    OP_NONE,    7,      &LD_HLm_H },
    { 0x75, "LD (HL),L",    OP_NONE,    7,      &LD_HLm_L },
    { 0x76, "HALT",         OP_NONE,    4,      &HALT },
    { 0x77, "LD (HL),A",    OP_NONE,    7,      &LD_HLm_A },
    { 0x78, "LD A,B",       OP_NONE,    4,      &LD_A_B },
    { 0x79, "LD A,C",       OP_NONE,    4,      &LD_A_C },
    { 0x7A, "LD A,D",       OP_NONE,    4,      &LD_A_D },
    { 0x7B, "LD A,E",       OP_NONE,    4,      &LD_A_E },
    { 0x7C, "LD A,H",       OP_NONE,    4,      &LD_A_H },
    { 0x7D, "LD A,L",       OP_NONE,    4,      &LD_A_L },
    { 0x7E, "LD A,(HL)",    OP_NONE,    7,      &LD_A_HLm },
    { 0x7F, "LD A,A",       OP_NONE,    4,      &LD_A_A },
    // 0x80 NAME            SIZE        CYCLES  HANDLER
    { 0x80, "ADD A,B",      OP_NONE,    4,      &ADD_A_B },
    { 0x81, "ADD A,C",      OP_NONE,    4,      &ADD_A_C },
    { 0x82, "ADD A,D",      OP_NONE,    4,      &ADD_A_D },
    { 0x83, "ADD A,E",      OP_NONE,    4,      &ADD_A_E },
    { 0x84, "ADD A,H",      OP_NONE,    4,      &ADD_A_H },
    { 0x85, "ADD A,L",      OP_NONE,    4,      &ADD_A_L },
    { 0x86, "ADD A,(HL)",   OP_NONE,    7,      &ADD_A_HLm },
    { 0x87, "ADD A,A",      OP_NONE,    4,      &ADD_A_A },
    { 0x88, "ADC A,B",      OP_NONE,    4,      &ADC_A_B },
    { 0x89, "ADC A,C",      OP_NONE,    4,      &ADC_A_C },
    { 0x8A, "ADC A,D",      OP_NONE,    4,      &ADC_A_D },
    { 0x8B, "ADC A,E",      OP_NONE,    4,      &ADC_A_E },
    { 0x8C, "ADC A,H",      OP_NONE,    4,      &ADC_A_H },
    { 0x8D, "ADC A,L",      OP_NONE,    4,      &ADC_A_L },
    { 0x8E, "ADC A,(HL)",   OP_NONE,    7,      &ADC_A_HLm },
    { 0x8F, "ADC A,A",      OP_NONE,    4,      &ADC_A_A },
    // 0x90 NAME            SIZE        CYCLES  HANDLER
    { 0x90, "SUB B",        OP_NONE,    4,      &SUB_B },
    { 0x91, "SUB C",        OP_NONE,    4,      &SUB_C },
    { 0x92, "SUB D",        OP_NONE,    4,      &SUB_D },
    { 0x93, "SUB E",        OP_NONE,    4,      &SUB_E },
    { 0x94, "SUB H",        OP_NONE,    4,      &SUB_H },
    { 0x95, "SUB L",        OP_NONE,    4,      &SUB_L },
    { 0x96, "SUB (HL)",     OP_NONE,    7,      &SUB_HLm },
    { 0x97, "SUB A",        OP_NONE,    4,      &SUB_A },
    { 0x98, "SBC A,B",      OP_NONE,    4,      &SBC_A_B },
    { 0x99, "SBC A,C",      OP_NONE,    4,      &SBC_A_C },
    { 0x9A, "SBC A,D",      OP_NONE,    4,      &SBC_A_D },
    { 0x9B, "SBC A,E",      OP_NONE,    4,      &SBC_A_E },
    { 0x9C, "SBC A,H",      OP_NONE,    4,      &SBC_A_H },
    { 0x9D, "SBC A,L",      OP_NONE,    4,      &SBC_A_L },
    { 0x9E, "SBC A,(HL)",   OP_NONE,    7,      &SBC_A_HLm },
    { 0x9F, "SBC A,A",      OP_NONE,    4,      &SBC_A_A },
    // 0xA0 NAME            SIZE        CYCLES  HANDLER
    { 0xA0, "AND B",        OP_NONE,    4,      &AND_B },
    { 0xA1, "AND C",        OP_NONE,    4,      &AND_C },
    { 0xA2, "AND D",        OP_NONE,    4,      &AND_D },
    { 0xA3, "AND E",        OP_NONE,    4,      &AND_E },
    { 0xA4, "AND H",        OP_NONE,    4,      &AND_H },
    { 0xA5, "AND L",        OP_NONE,    4,      &AND_L },
    { 0xA6, "AND (HL)",     OP_NONE,    7,      &AND_HLm },
    { 0xA7, "AND A",        OP_NONE,    4,      &AND_A },
    { 0xA8, "XOR B",        OP_NONE,    4,      &XOR_B },
    { 0xA9, "XOR C",        OP_NONE,    4,      &XOR_C },
    { 0xAA, "XOR D",        OP_NONE,    4,      &XOR_D },
    { 0xAB, "XOR E",        OP_NONE,    4,      &XOR_E },
    { 0xAC, "XOR H",        OP_NONE,    4,      &XOR_H },
    { 0xAD, "XOR L",        OP_NONE,    4,      &XOR_L },
    { 0xAE, "XOR (HL)",     OP_NONE,    7,      &XOR_HLm },
    { 0xAF, "XOR A",        OP_NONE,    4,      &XOR_A },
    // 0xB0 NAME            SIZE        CYCLES  HANDLER
    { 0xB0, "OR B",         OP_NONE,    4,      &OR_B },
    { 0xB1, "OR C",         OP_NONE,    4,      &OR_C },
    { 0xB2, "OR D",         OP_NONE,    4,      &OR_D },
    { 0xB3, "OR E",         OP_NONE,    4,      &OR_E },
    { 0xB4, "OR H",         OP_NONE,    4,      &OR_H },
    { 0xB5, "OR L",         OP_NONE,    4,      &OR_L },
    { 0xB6, "OR (HL)",      OP_NONE,    7,      &OR_HLm },
    { 0xB7, "OR A",         OP_NONE,    4,      &OR_A },
    { 0xB8, "CP B",         OP_NONE,    4,      &CP_B },
    { 0xB9, "CP C",         OP_NONE,    4,      &CP_C },
    { 0xBA, "CP D",         OP_NONE,    4,      &CP_D },
    { 0xBB, "CP E",         OP_NONE,    4,      &CP_E },
    { 0xBC, "CP H",         OP_NONE,    4,      &CP_H },
    { 0xBD, "CP L",         OP_NONE,    4,      &CP_L },
    { 0xBE, "CP (HL)",      OP_NONE,    7,      &CP_HLm },
    { 0xBF, "CP A",         OP_NONE,    4,      &CP_A },
    // 0xC0 NAME            SIZE        CYCLES  HANDLER
    { 0xC0, "RET NZ",       OP_JUMP,    11,     &RET_NZ },    //: TODO 11 or 5 clock cycles
    { 0xC1, "POP BC",       OP_NONE,    10,     &POP_BC },
    { 0xC2, "JP NZ,**",     OP_JUMP,    10,     &JP_NZ_nn },
    { 0xC3, "JP **",        OP_JUMP,    10,     &JP_nn },
    { 0xC4, "CALL NZ,**",   OP_JUMP,    17,     &CALL_NZ_nn },    //: TODO 17 or 10 clock cycles
    { 0xC5, "PUSH BC",      OP_NONE,    11,     &PUSH_BC },
    { 0xC6, "ADD A,*",      OP_BYTE,    7,      &ADD_A_n },
    { 0xC7, "RST 00h",      OP_NONE,    11,     &RST_00h },
    { 0xC8, "RET Z",        OP_JUMP,    11,     &RET_Z },    //: TODO 11 or 5 clock cycles
    { 0xC9, "RET",          OP_JUMP,    10,     &RET },
    { 0xCA, "JP Z,**",      OP_JUMP,    10,     &JP_Z_nn },
    { 0xCB, "BITS",         OP_NONE,    0,      &BITS },
    { 0xCC, "CALL Z,**",    OP_JUMP,    17,     &CALL_Z_nn },    //: TODO 17 or 10 clock cycles
    { 0xCD, "CALL **",      OP_JUMP,    17,     &CALL_nn },
    { 0xCE, "ADC A,*",      OP_BYTE,    7,      &ADC_A_n },
    { 0xCF, "RST 08h",      OP_NONE,    11,     &RST_08h },
    // 0xD0 NAME            SIZE        CYCLES  HANDLER
    { 0xD0, "RET NC",       OP_JUMP,    11,     &RET_NC },     // 11/5
    { 0xD1, "POP DE",       OP_NONE,    10,     &POP_DE },
    { 0xD2, "JP NC,**",     OP_WORD,    10,     &JP_NC_nn },
    { 0xD3, "OUT (*),A",    OP_BYTE,    11,     &OUT_nm_a },
    { 0xD4, "CALL NC,**",   OP_JUMP,    17,     &CALL_NC_nn },     // 17/10
    { 0xD5, "PUSH DE",      OP_NONE,    11,     &PUSH_DE },
    { 0xD6, "SUB *",        OP_BYTE,    7,      &SUB_n },
    { 0xD7, "RST 10h",      OP_NONE,    11,     &RST_10h },    
    { 0xD8, "RET C",        OP_JUMP,    11,     &RET_C },    // 11/5
    { 0xD9, "EXX",          OP_NONE,    4,      &EXX },
    { 0xDA, "JP C,**",      OP_WORD,    10,     &JP_C_nn },
    { 0xDB, "IN A,(*)",     OP_BYTE,    11,     &IN_A_nm },
    { 0xDC, "CALL C,**",    OP_JUMP,    17,     &CALL_C_nn },    // 17/10
    { 0xDD, "IX",           OP_NONE,    0,      &IX },
    { 0xDE, "SBC A,*",      OP_WORD,    7,      &SBC_A_n },
    { 0xDF, "RST 18h",      OP_NONE,    11,     &RST_18h },
    // 0xE0 NAME            SIZE        CYCLES  HANDLER
    { 0xE0, "RET PO",       OP_JUMP,    11,     &RET_PO },     // 11/5
    { 0xE1, "POP HL",       OP_NONE,    10,     &POP_HL },
    { 0xE2, "JP PO,**",     OP_WORD,    10,     &JP_PO_nn },
    { 0xE3, "EX (SP),HL",   OP_NONE,    19,     &EX_SPm_HL },
    { 0xE4, "CALL PO,**",   OP_JUMP,    17,     &CALL_PO_nn },    // 17/10
    { 0xE5, "PUSH HL",      OP_NONE,    11,     &PUSH_HL },
    { 0xE6, "AND *",        OP_BYTE,    7,      &AND_n },
    { 0xE7, "RST 20h",      OP_NONE,    11,     &RST_20h },
    { 0xE8, "RET PE",       OP_JUMP,    11,     &RET_PE },     // 11/5
    { 0xE9, "JP (HL)",      OP_NONE,    4,      &JP_HLm },
    { 0xEA, "JP PE,**",     OP_WORD,    10,     &JP_PE_nn },
    { 0xEB, "EX DE,HL",     OP_NONE,    4,      &EX_DE_HL },
    { 0xEC, "CALL PE,**",   OP_JUMP,    17,     &CALL_PE_nn },     // 17/10
    { 0xED, "EXTD",         OP_NONE,    0,      &EXTD },
    { 0xEE, "XOR *",        OP_WORD,    7,      &XOR_n },
    { 0xEF, "RST 28h",      OP_NONE,    11,     &RST_28h },
    // 0xF0 NAME            SIZE        CYCLES  HANDLER
    { 0xF0, "RET P",        OP_JUMP,    11,     &RET_P },     // 11/5
    { 0xF1, "POP AF",       OP_NONE,    10,     &POP_AF },
    { 0xF2, "JP P,**",      OP_WORD,    10,     &JP_P_nn },
    { 0xF3, "DI",           OP_NONE,    4,      &DI },
    { 0xF4, "CALL P,**",    OP_JUMP,    17,     &CALL_P_nn },    // 17/10
    { 0xF5, "PUSH AF",      OP_NONE,    11,     &PUSH_AF },
    { 0xF6, "OR *",         OP_BYTE,    7,      &OR_n },
    { 0xF7, "RST 30h",      OP_NONE,    11,     &RST_30h },
    { 0xF8, "RET M",        OP_JUMP,    11,     &RET_M },    // 11/5
    { 0xF9, "LD SP,HL",     OP_NONE,    6,      &LD_SP_HL },
    { 0xFA, "JP M,**",      OP_WORD,    10,     &JP_M_nn },
    { 0xFB, "EI",           OP_NONE,    4,      &EI },
    { 0xFC, "CALL M,**",    OP_JUMP,    17,     &CALL_M_nn },     // 17/10
    { 0xFD, "IY",           OP_NONE,    0,      &IY },
    { 0xFE, "CP *",         OP_BYTE,    7,      &CP_n },
    { 0xFF, "RST 38h",      OP_NONE,    11,     &RST_38h }
};

Z80_Instruction FetchMainInstruction(uint8_t opcode) {
    return MainInstructions[opcode];
}