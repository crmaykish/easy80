#include "z80_cpu.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

uint16_t combine(uint8_t x, uint8_t y) {
    return (x << 8) | y;
}

uint8_t split_1(uint16_t r) {
    return (r & 0xFF00) >> 8;
}

uint8_t split_2(uint16_t r) {
    return r & 0x00FF;
}

// Load operations

void ld_byte(Z80_CPU *cpu, uint8_t *dest, uint8_t src, uint8_t inc) {
    *dest = src;
    cpu->PC += inc;
}

void ld_word(Z80_CPU *cpu, uint16_t *dest, uint16_t src, uint8_t inc) {
    *dest = src;
    cpu->PC += inc;
}

void Z80_CPU_Init(Z80_CPU *cpu) {
    // Set CPU to stopped
    cpu->State = STOPPED;

    // Wipe memory
    memset(&cpu->Memory, 0, sizeof(uint8_t) * MAX_ADDRESS);

    // Zero out registers
    cpu->A = 0;
    cpu->B = 0;
    cpu->C = 0;
    cpu->D = 0;
    cpu->E = 0;
    cpu->F = 0;

    cpu->Ap = 0;
    cpu->Bp = 0;
    cpu->Cp = 0;
    cpu->Dp = 0;
    cpu->Ep = 0;
    cpu->Fp = 0;

    cpu->IX = 0;
    cpu->IY = 0;

    cpu->SP = MAX_ADDRESS - 1;

    cpu->I = 0;

    cpu->R = 0;

    cpu->PC = 0;
}

void Z80_CPU_SetMemory(Z80_CPU *cpu, uint8_t data[], size_t size, uint16_t offset) {
    // TODO: bounds checking on Memory array
    memcpy(&cpu->Memory[offset], data, size);
}

void Z80_CPU_Cycle(Z80_CPU *cpu) {
    // Fetch current opcode
    uint8_t op0 = cpu->Memory[cpu->PC];
    // Fetch next two bytes for operations
    // TODO: this won't work if at the end of Memory
    uint8_t op1 = cpu->Memory[cpu->PC + 1];
    uint8_t op2 = cpu->Memory[cpu->PC + 2];

    printf("OP: %X\n", op0);

    switch (op0) {
        case 0x0:  // NOP
            cpu->PC++;
            break;
        case 0x01:  // LD BC,**
            ld_byte(cpu, &cpu->B, op2, 0);
            ld_byte(cpu, &cpu->C, op1, 3);
            break;
        case 0x02:  // LD (BC),A
            cpu->Memory[combine(cpu->B, cpu->C)] = cpu->A;
            cpu->PC += 3;
            break;
        case 0x03:  // INC BC
            cpu->B = split_1(combine(cpu->B, cpu->C) + 1);
            cpu->C = split_2(combine(cpu->B, cpu->C) + 1);
            cpu->PC++;
            break;
        case 0x04:  // INC B
            printf("4 : Flags not set!\n");
            cpu->B++;
            cpu->PC++;
            break;
        case 0x05:  // DEC B
            printf("5 : Flags not set!\n");
            cpu->B--;
            cpu->PC++;
            break;
        case 0x06:  // LD B,*
            ld_byte(cpu, &cpu->B, op1, 2);
            break;
        case 0x07:  // 
            printf("7 : Not Implemented!\n");
            exit(1);
            break;
        case 0x08:  // 
            printf("8 : Not Implemented!\n");
            exit(1);
            break;
        case 0x09:  // 
            printf("9 : Not Implemented!\n");
            exit(1);
            break;
        case 0x0A:  // 
            printf("A : Not Implemented!\n");
            exit(1);
            break;
        case 0x0B:  // 
            printf("B : Not Implemented!\n");
            exit(1);
            break;
        case 0x0C:  // INC C
            printf("C : Flags not set!\n");
            cpu->C++;
            cpu->PC++;
            break;
        case 0x0D:  // DEC C
            printf("D : Flags not set!\n");
            cpu->C--;
            cpu->PC++;
            break;
        case 0x0E:  // LD C,*
            ld_byte(cpu, &cpu->C, op1, 2);
            break;
        case 0x0F:  // 
            printf("F : Not Implemented!\n");
            exit(1);
            break;
        case 0x10:  // 
            printf("10 : Not Implemented!\n");
            exit(1);
            break;
        case 0x11:  // LD DE,**
            ld_byte(cpu, &cpu->D, op2, 0);
            ld_byte(cpu, &cpu->E, op1, 3);
            break;
        case 0x12:  // 
            printf("12 : Not Implemented!\n");
            exit(1);
            break;
        case 0x13:  // 
            printf("13 : Not Implemented!\n");
            exit(1);
            break;
        case 0x14:  // 
            printf("14 : Not Implemented!\n");
            exit(1);
            break;
        case 0x15:  // 
            printf("15 : Not Implemented!\n");
            exit(1);
            break;
        case 0x16:  // 
            printf("16 : Not Implemented!\n");
            exit(1);
            break;
        case 0x17:  // 
            printf("17 : Not Implemented!\n");
            exit(1);
            break;
        case 0x18:  // 
            printf("18 : Not Implemented!\n");
            exit(1);
            break;
        case 0x19:  // 
            printf("19 : Not Implemented!\n");
            exit(1);
            break;
        case 0x1A:  // 
            printf("1A : Not Implemented!\n");
            exit(1);
            break;
        case 0x1B:  // 
            printf("1B : Not Implemented!\n");
            exit(1);
            break;
        case 0x1C:  // 
            printf("1C : Not Implemented!\n");
            exit(1);
            break;
        case 0x1D:  // 
            printf("1D : Not Implemented!\n");
            exit(1);
            break;
        case 0x1E:  // 
            printf("1E : Not Implemented!\n");
            exit(1);
            break;
        case 0x1F:  // 
            printf("1F : Not Implemented!\n");
            exit(1);
            break;
        case 0x20:  // 
            printf("20 : Not Implemented!\n");
            exit(1);
            break;
        case 0x21:  // 
            printf("21 : Not Implemented!\n");
            exit(1);
            break;
        case 0x22:  // 
            printf("22 : Not Implemented!\n");
            exit(1);
            break;
        case 0x23:  // 
            printf("23 : Not Implemented!\n");
            exit(1);
            break;
        case 0x24:  // 
            printf("24 : Not Implemented!\n");
            exit(1);
            break;
        case 0x25:  // 
            printf("25 : Not Implemented!\n");
            exit(1);
            break;
        case 0x26:  // 
            printf("26 : Not Implemented!\n");
            exit(1);
            break;
        case 0x27:  // 
            printf("27 : Not Implemented!\n");
            exit(1);
            break;
        case 0x28:  // 
            printf("28 : Not Implemented!\n");
            exit(1);
            break;
        case 0x29:  // 
            printf("29 : Not Implemented!\n");
            exit(1);
            break;
        case 0x2A:  // 
            printf("2A : Not Implemented!\n");
            exit(1);
            break;
        case 0x2B:  // 
            printf("2B : Not Implemented!\n");
            exit(1);
            break;
        case 0x2C:  // 
            printf("2C : Not Implemented!\n");
            exit(1);
            break;
        case 0x2D:  // 
            printf("2D : Not Implemented!\n");
            exit(1);
            break;
        case 0x2E:  // 
            printf("2E : Not Implemented!\n");
            exit(1);
            break;
        case 0x2F:  // 
            printf("2F : Not Implemented!\n");
            exit(1);
            break;
        case 0x30:  // 
            printf("30 : Not Implemented!\n");
            exit(1);
            break;
        case 0x31:  // LD SP,**
            ld_word(cpu, &cpu->SP, combine(op2, op1), 3);
            break;
        case 0x32:  // LD (**),A
            ld_byte(cpu, &cpu->Memory[combine(op2, op1)], cpu->A, 3);
            break;
        case 0x33:  // INC SP
            cpu->SP++;
            cpu->PC++;
            break;
        case 0x34:  // 
            printf("34 : Not Implemented!\n");
            exit(1);
            break;
        case 0x35:  // 
            printf("35 : Not Implemented!\n");
            exit(1);
            break;
        case 0x36:  // 
            printf("36 : Not Implemented!\n");
            exit(1);
            break;
        case 0x37:  // 
            printf("37 : Not Implemented!\n");
            exit(1);
            break;
        case 0x38:  // 
            printf("38 : Not Implemented!\n");
            exit(1);
            break;
        case 0x39:  // 
            printf("39 : Not Implemented!\n");
            exit(1);
            break;
        case 0x3A:  // LD A,(**)
            ld_byte(cpu, &cpu->A, cpu->Memory[combine(op2, op1)], 3);
            break;
        case 0x3B:  // DEC SP
            cpu->SP--;
            cpu->PC++;
            break;
        case 0x3C:  // INC A
            printf("3C : Flags not set!\n");
            cpu->A++;
            cpu->PC++;
            break;
        case 0x3D:  // 
            printf("3D : Not Implemented!\n");
            exit(1);
            break;
        case 0x3E:  // LD A,*
            ld_byte(cpu, &cpu->A, op1, 2);
            break;
        case 0x3F:  // 
            printf("3F : Not Implemented!\n");
            exit(1);
            break;
        case 0x40:  // LD B,B
            ld_byte(cpu, &cpu->B, cpu->B, 1);
            break;
        case 0x41:  // LD B,C
            ld_byte(cpu, &cpu->B, cpu->C, 1);
            break;
        case 0x42:  // LD B,D
            ld_byte(cpu, &cpu->B, cpu->D, 1);
            break;
        case 0x43:  // LD B,E
            ld_byte(cpu, &cpu->B, cpu->E, 1);
            break;
        case 0x44:  // LD B,H
            ld_byte(cpu, &cpu->B, cpu->H, 1);
            break;
        case 0x45:  // LD B,L
            ld_byte(cpu, &cpu->B, cpu->L, 1);
            break;
        case 0x46:  // 
            printf("46 : Not Implemented!\n");
            exit(1);
            break;
        case 0x47:  // LD B,A
            ld_byte(cpu, &cpu->B, cpu->A, 1);
            break;
        case 0x48:  // LD C,B
            ld_byte(cpu, &cpu->C, cpu->B, 1);
            break;
        case 0x49:  // LD C,C
            ld_byte(cpu, &cpu->C, cpu->C, 1);
            break;
        case 0x4A:  // LD C,D
            ld_byte(cpu, &cpu->C, cpu->D, 1);
            break;
        case 0x4B:  // LD C,E
            ld_byte(cpu, &cpu->C, cpu->E, 1);
            break;
        case 0x4C:  // LD C,H
            ld_byte(cpu, &cpu->C, cpu->H, 1);
            break;
        case 0x4D:  // LD C,L
            ld_byte(cpu, &cpu->C, cpu->L, 1);
            break;
        case 0x4E:  // 
            printf("4E : Not Implemented!\n");
            exit(1);
            break;
        case 0x4F:  // LD C,A
            ld_byte(cpu, &cpu->C, cpu->A, 1);
            break;
        case 0x50:  // LD D,B
            ld_byte(cpu, &cpu->D, cpu->B, 1);
            break;
        case 0x51:  // LD D,C
            ld_byte(cpu, &cpu->D, cpu->C, 1);
            break;
        case 0x52:  // LD D,D
            ld_byte(cpu, &cpu->D, cpu->D, 1);
            break;
        case 0x53:  // LD D,E
            ld_byte(cpu, &cpu->D, cpu->E, 1);
            break;
        case 0x54:  // LD D,H
            ld_byte(cpu, &cpu->D, cpu->H, 1);
            break;
        case 0x55:  // LD D,L
            ld_byte(cpu, &cpu->D, cpu->L, 1);
            break;
        case 0x56:  // 
            printf("56 : Not Implemented!\n");
            exit(1);
            break;
        case 0x57:  // LD D,A
            ld_byte(cpu, &cpu->D, cpu->A, 1);
            break;
        case 0x58:  // LD E,B
            ld_byte(cpu, &cpu->E, cpu->B, 1);
            break;
        case 0x59:  // LD E,C
            ld_byte(cpu, &cpu->E, cpu->C, 1);
            break;
        case 0x5A:  // LD E,D
            ld_byte(cpu, &cpu->E, cpu->D, 1);
            break;
        case 0x5B:  // LD E,E
            ld_byte(cpu, &cpu->E, cpu->E, 1);
            break;
        case 0x5C:  // LD E,H
            ld_byte(cpu, &cpu->E, cpu->H, 1);
            break;
        case 0x5D:  // LD E,L
            ld_byte(cpu, &cpu->E, cpu->L, 1);
            break;
        case 0x5E:  // 
            printf("5E : Not Implemented!\n");
            exit(1);
            break;
        case 0x5F:  // LD E,A
            ld_byte(cpu, &cpu->E, cpu->A, 1);
            break;
        case 0x60:  // LD H,B
            ld_byte(cpu, &cpu->H, cpu->B, 1);
            break;
        case 0x61:  // LD H,C
            ld_byte(cpu, &cpu->H, cpu->C, 1);
            break;
        case 0x62:  // LD H,D
            ld_byte(cpu, &cpu->H, cpu->D, 1);
            break;
        case 0x63:  // LD H,E
            ld_byte(cpu, &cpu->H, cpu->E, 1);
            break;
        case 0x64:  // LD H,H
            ld_byte(cpu, &cpu->H, cpu->H, 1);
            break;
        case 0x65:  // LD H,L
            ld_byte(cpu, &cpu->H, cpu->L, 1);
            break;
        case 0x66:  // 
            printf("66 : Not Implemented!\n");
            exit(1);
            break;
        case 0x67:  // LD H,A
            ld_byte(cpu, &cpu->H, cpu->A, 1);
            break;
        case 0x68:  // LD L,B
            ld_byte(cpu, &cpu->L, cpu->B, 1);
            break;
        case 0x69:  // LD L,C
            ld_byte(cpu, &cpu->L, cpu->C, 1);
            break;
        case 0x6A:  // LD L,D
            ld_byte(cpu, &cpu->L, cpu->D, 1);
            break;
        case 0x6B:  // LD L,E
            ld_byte(cpu, &cpu->L, cpu->E, 1);
            break;
        case 0x6C:  // LD L,H
            ld_byte(cpu, &cpu->L, cpu->H, 1);
            break;
        case 0x6D:  // LD L,L
            ld_byte(cpu, &cpu->L, cpu->L, 1);
            break;
        case 0x6E:  // 
            printf("6E : Not Implemented!\n");
            exit(1);
            break;
        case 0x6F:  // LD L,A
            ld_byte(cpu, &cpu->L, cpu->A, 1);
            break;
        case 0x70:  // 
            printf("70 : Not Implemented!\n");
            exit(1);
            break;
        case 0x71:  // 
            printf("71 : Not Implemented!\n");
            exit(1);
            break;
        case 0x72:  // 
            printf("72 : Not Implemented!\n");
            exit(1);
            break;
        case 0x73:  // 
            printf("73 : Not Implemented!\n");
            exit(1);
            break;
        case 0x74:  // 
            printf("74 : Not Implemented!\n");
            exit(1);
            break;
        case 0x75:  // 
            printf("75 : Not Implemented!\n");
            exit(1);
            break;
        case 0x76:  // HALT
            cpu->State = STOPPED;
            cpu->PC++;
            break;
        case 0x77:  // 
            printf("77 : Not Implemented!\n");
            exit(1);
            break;
        case 0x78:  // LD A,B
            ld_byte(cpu, &cpu->A, cpu->B, 1);
            break;
        case 0x79:  // LD A,C
            ld_byte(cpu, &cpu->A, cpu->B, 1);
            break;
        case 0x7A:  // LD A,D
            ld_byte(cpu, &cpu->A, cpu->B, 1);
            break;
        case 0x7B:  // LD A,E
            ld_byte(cpu, &cpu->A, cpu->B, 1);
            break;
        case 0x7C:  // LD A,H
            ld_byte(cpu, &cpu->A, cpu->B, 1);
            break;
        case 0x7D:  // LD A,L
            ld_byte(cpu, &cpu->A, cpu->B, 1);
            break;
        case 0x7E:  // 
            printf("7E : Not Implemented!\n");
            exit(1);
            break;
        case 0x7F:  // LD A,A
            ld_byte(cpu, &cpu->A, cpu->A, 1);
            break;
        case 0x80:  // ADD A,B
            printf("80 : Flags not set!\n");
            cpu->A += cpu->B;
            cpu->PC++;
            break;
        case 0x81:  // 
            printf("81 : Not Implemented!\n");
            exit(1);
            break;
        case 0x82:  // 
            printf("82 : Not Implemented!\n");
            exit(1);
            break;
        case 0x83:  // 
            printf("83 : Not Implemented!\n");
            exit(1);
            break;
        case 0x84:  // 
            printf("84 : Not Implemented!\n");
            exit(1);
            break;
        case 0x85:  // 
            printf("85 : Not Implemented!\n");
            exit(1);
            break;
        case 0x86:  // 
            printf("86 : Not Implemented!\n");
            exit(1);
            break;
        case 0x87:  // 
            printf("87 : Not Implemented!\n");
            exit(1);
            break;
        case 0x88:  // 
            printf("88 : Not Implemented!\n");
            exit(1);
            break;
        case 0x89:  // 
            printf("89 : Not Implemented!\n");
            exit(1);
            break;
        case 0x8A:  // 
            printf("8A : Not Implemented!\n");
            exit(1);
            break;
        case 0x8B:  // 
            printf("8B : Not Implemented!\n");
            exit(1);
            break;
        case 0x8C:  // 
            printf("8C : Not Implemented!\n");
            exit(1);
            break;
        case 0x8D:  // 
            printf("8D : Not Implemented!\n");
            exit(1);
            break;
        case 0x8E:  // 
            printf("8E : Not Implemented!\n");
            exit(1);
            break;
        case 0x8F:  // 
            printf("8F : Not Implemented!\n");
            exit(1);
            break;
        case 0x90:  // 
            printf("90 : Not Implemented!\n");
            exit(1);
            break;
        case 0x91:  // 
            printf("91 : Not Implemented!\n");
            exit(1);
            break;
        case 0x92:  // 
            printf("92 : Not Implemented!\n");
            exit(1);
            break;
        case 0x93:  // 
            printf("93 : Not Implemented!\n");
            exit(1);
            break;
        case 0x94:  // 
            printf("94 : Not Implemented!\n");
            exit(1);
            break;
        case 0x95:  // 
            printf("95 : Not Implemented!\n");
            exit(1);
            break;
        case 0x96:  // 
            printf("96 : Not Implemented!\n");
            exit(1);
            break;
        case 0x97:  // 
            printf("97 : Not Implemented!\n");
            exit(1);
            break;
        case 0x98:  // 
            printf("98 : Not Implemented!\n");
            exit(1);
            break;
        case 0x99:  // 
            printf("99 : Not Implemented!\n");
            exit(1);
            break;
        case 0x9A:  // 
            printf("9A : Not Implemented!\n");
            exit(1);
            break;
        case 0x9B:  // 
            printf("9B : Not Implemented!\n");
            exit(1);
            break;
        case 0x9C:  // 
            printf("9C : Not Implemented!\n");
            exit(1);
            break;
        case 0x9D:  // 
            printf("9D : Not Implemented!\n");
            exit(1);
            break;
        case 0x9E:  // 
            printf("9E : Not Implemented!\n");
            exit(1);
            break;
        case 0x9F:  // 
            printf("9F : Not Implemented!\n");
            exit(1);
            break;
        case 0xA0:  // 
            printf("A0 : Not Implemented!\n");
            exit(1);
            break;
        case 0xA1:  // 
            printf("A1 : Not Implemented!\n");
            exit(1);
            break;
        case 0xA2:  // 
            printf("A2 : Not Implemented!\n");
            exit(1);
            break;
        case 0xA3:  // 
            printf("A3 : Not Implemented!\n");
            exit(1);
            break;
        case 0xA4:  // 
            printf("A4 : Not Implemented!\n");
            exit(1);
            break;
        case 0xA5:  // 
            printf("A5 : Not Implemented!\n");
            exit(1);
            break;
        case 0xA6:  // 
            printf("A6 : Not Implemented!\n");
            exit(1);
            break;
        case 0xA7:  // 
            printf("A7 : Not Implemented!\n");
            exit(1);
            break;
        case 0xA8:  // 
            printf("A8 : Not Implemented!\n");
            exit(1);
            break;
        case 0xA9:  // 
            printf("A9 : Not Implemented!\n");
            exit(1);
            break;
        case 0xAA:  // 
            printf("AA : Not Implemented!\n");
            exit(1);
            break;
        case 0xAB:  // 
            printf("AB : Not Implemented!\n");
            exit(1);
            break;
        case 0xAC:  // 
            printf("AC : Not Implemented!\n");
            exit(1);
            break;
        case 0xAD:  // 
            printf("AD : Not Implemented!\n");
            exit(1);
            break;
        case 0xAE:  // 
            printf("AE : Not Implemented!\n");
            exit(1);
            break;
        case 0xAF:  // 
            printf("AF : Not Implemented!\n");
            exit(1);
            break;
        case 0xB0:  // 
            printf("B0 : Not Implemented!\n");
            exit(1);
            break;
        case 0xB1:  // 
            printf("B1 : Not Implemented!\n");
            exit(1);
            break;
        case 0xB2:  // 
            printf("B2 : Not Implemented!\n");
            exit(1);
            break;
        case 0xB3:  // 
            printf("B3 : Not Implemented!\n");
            exit(1);
            break;
        case 0xB4:  // 
            printf("B4 : Not Implemented!\n");
            exit(1);
            break;
        case 0xB5:  // 
            printf("B5 : Not Implemented!\n");
            exit(1);
            break;
        case 0xB6:  // 
            printf("B6 : Not Implemented!\n");
            exit(1);
            break;
        case 0xB7:  // 
            printf("B7 : Not Implemented!\n");
            exit(1);
            break;
        case 0xB8:  // 
            printf("B8 : Not Implemented!\n");
            exit(1);
            break;
        case 0xB9:  // 
            printf("B9 : Not Implemented!\n");
            exit(1);
            break;
        case 0xBA:  // 
            printf("BA : Not Implemented!\n");
            exit(1);
            break;
        case 0xBB:  // 
            printf("BB : Not Implemented!\n");
            exit(1);
            break;
        case 0xBC:  // 
            printf("BC : Not Implemented!\n");
            exit(1);
            break;
        case 0xBD:  // 
            printf("BD : Not Implemented!\n");
            exit(1);
            break;
        case 0xBE:  // 
            printf("BE : Not Implemented!\n");
            exit(1);
            break;
        case 0xBF:  // 
            printf("BF : Not Implemented!\n");
            exit(1);
            break;
        case 0xC0:  // 
            printf("C0 : Not Implemented!\n");
            exit(1);
            break;
        case 0xC1:  // 
            printf("C1 : Not Implemented!\n");
            exit(1);
            break;
        case 0xC2:  // 
            printf("C2 : Not Implemented!\n");
            exit(1);
            break;
        case 0xC3:  // JP **
            cpu->PC = op1;
            break;
        case 0xC4:  // 
            printf("C4 : Not Implemented!\n");
            exit(1);
            break;
        case 0xC5:  // 
            printf("C5 : Not Implemented!\n");
            exit(1);
            break;
        case 0xC6:  // 
            printf("C6 : Not Implemented!\n");
            exit(1);
            break;
        case 0xC7:  // 
            printf("C7 : Not Implemented!\n");
            exit(1);
            break;
        case 0xC8:  // 
            printf("C8 : Not Implemented!\n");
            exit(1);
            break;
        case 0xC9:  // 
            printf("C9 : Not Implemented!\n");
            exit(1);
            break;
        case 0xCA:  // 
            printf("CA : Not Implemented!\n");
            exit(1);
            break;
        case 0xCB:  // 
            printf("CB : Not Implemented!\n");
            exit(1);
            break;
        case 0xCC:  // 
            printf("CC : Not Implemented!\n");
            exit(1);
            break;
        case 0xCD:  // 
            printf("CD : Not Implemented!\n");
            exit(1);
            break;
        case 0xCE:  // 
            printf("CE : Not Implemented!\n");
            exit(1);
            break;
        case 0xCF:  // 
            printf("CF : Not Implemented!\n");
            exit(1);
            break;
        case 0xD0:  // 
            printf("D0 : Not Implemented!\n");
            exit(1);
            break;
        case 0xD1:  // 
            printf("D1 : Not Implemented!\n");
            exit(1);
            break;
        case 0xD2:  // 
            printf("D2 : Not Implemented!\n");
            exit(1);
            break;
        case 0xD3:  // 
            printf("D3 : Not Implemented!\n");
            exit(1);
            break;
        case 0xD4:  // 
            printf("D4 : Not Implemented!\n");
            exit(1);
            break;
        case 0xD5:  // 
            printf("D5 : Not Implemented!\n");
            exit(1);
            break;
        case 0xD6:  // 
            printf("D6 : Not Implemented!\n");
            exit(1);
            break;
        case 0xD7:  // 
            printf("D7 : Not Implemented!\n");
            exit(1);
            break;
        case 0xD8:  // 
            printf("D8 : Not Implemented!\n");
            exit(1);
            break;
        case 0xD9:  // 
            printf("D9 : Not Implemented!\n");
            exit(1);
            break;
        case 0xDA:  // 
            printf("DA : Not Implemented!\n");
            exit(1);
            break;
        case 0xDB:  // 
            printf("DB : Not Implemented!\n");
            exit(1);
            break;
        case 0xDC:  // 
            printf("DC : Not Implemented!\n");
            exit(1);
            break;
        case 0xDD:  // 
            printf("DD : Not Implemented!\n");
            exit(1);
            break;
        case 0xDE:  // 
            printf("DE : Not Implemented!\n");
            exit(1);
            break;
        case 0xDF:  // 
            printf("DF : Not Implemented!\n");
            exit(1);
            break;
        case 0xE0:  // 
            printf("E0 : Not Implemented!\n");
            exit(1);
            break;
        case 0xE1:  // 
            printf("E1 : Not Implemented!\n");
            exit(1);
            break;
        case 0xE2:  // 
            printf("E2 : Not Implemented!\n");
            exit(1);
            break;
        case 0xE3:  // 
            printf("E3 : Not Implemented!\n");
            exit(1);
            break;
        case 0xE4:  // 
            printf("E4 : Not Implemented!\n");
            exit(1);
            break;
        case 0xE5:  // 
            printf("E5 : Not Implemented!\n");
            exit(1);
            break;
        case 0xE6:  // 
            printf("E6 : Not Implemented!\n");
            exit(1);
            break;
        case 0xE7:  // 
            printf("E7 : Not Implemented!\n");
            exit(1);
            break;
        case 0xE8:  // 
            printf("E8 : Not Implemented!\n");
            exit(1);
            break;
        case 0xE9:  // 
            printf("E9 : Not Implemented!\n");
            exit(1);
            break;
        case 0xEA:  // 
            printf("EA : Not Implemented!\n");
            exit(1);
            break;
        case 0xEB:  // 
            printf("EB : Not Implemented!\n");
            exit(1);
            break;
        case 0xEC:  // 
            printf("EC : Not Implemented!\n");
            exit(1);
            break;
        case 0xED:  // 
            printf("ED : Not Implemented!\n");
            exit(1);
            break;
        case 0xEE:  // 
            printf("EE : Not Implemented!\n");
            exit(1);
            break;
        case 0xEF:  // 
            printf("EF : Not Implemented!\n");
            exit(1);
            break;
        case 0xF0:  // 
            printf("F0 : Not Implemented!\n");
            exit(1);
            break;
        case 0xF1:  // 
            printf("F1 : Not Implemented!\n");
            exit(1);
            break;
        case 0xF2:  // 
            printf("F2 : Not Implemented!\n");
            exit(1);
            break;
        case 0xF3:  // 
            printf("F3 : Not Implemented!\n");
            exit(1);
            break;
        case 0xF4:  // 
            printf("F4 : Not Implemented!\n");
            exit(1);
            break;
        case 0xF5:  // 
            printf("F5 : Not Implemented!\n");
            exit(1);
            break;
        case 0xF6:  // 
            printf("F6 : Not Implemented!\n");
            exit(1);
            break;
        case 0xF7:  // 
            printf("F7 : Not Implemented!\n");
            exit(1);
            break;
        case 0xF8:  // 
            printf("F8 : Not Implemented!\n");
            exit(1);
            break;
        case 0xF9:  // 
            printf("F9 : Not Implemented!\n");
            exit(1);
            break;
        case 0xFA:  // 
            printf("FA : Not Implemented!\n");
            exit(1);
            break;
        case 0xFB:  // 
            printf("FB : Not Implemented!\n");
            exit(1);
            break;
        case 0xFC:  // 
            printf("FC : Not Implemented!\n");
            exit(1);
            break;
        case 0xFD:  // 
            printf("FD : Not Implemented!\n");
            exit(1);
            break;
        case 0xFE:  // 
            printf("FE : Not Implemented!\n");
            exit(1);
            break;
        case 0xFF:  // 
            printf("FF : Not Implemented!\n");
            exit(1);
            break;

    }
}

void Z80_CPU_PrintRegisters(Z80_CPU *cpu) {
    printf(
        "PC: %X | AF: %X | BC: %X | DE: %X | HL: %X\n",
        cpu->PC,
        combine(cpu->A, cpu->F),
        combine(cpu->B, cpu->C),
        combine(cpu->D, cpu->E),
        combine(cpu->H, cpu->L)
    );
}