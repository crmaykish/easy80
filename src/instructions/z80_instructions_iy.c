#include "z80_instructions_iy.h"
#include "bitmath.h"

// 0xE0
void POP_IY(Z80_CPU *z) { z->IY = combine(GetMemVal(z, z->SP + 1), GetMemVal(z, z->SP)); z->SP += 2; }

Z80_Instruction IYInstructions[256] = {
    { 0x00, "",          OP_BYTE,    0,      &BAD },
    { 0x01, "",          OP_BYTE,    0,      &BAD },
    { 0x02, "",          OP_BYTE,    0,      &BAD },
    { 0x03, "",          OP_BYTE,    0,      &BAD },
    { 0x04, "",          OP_BYTE,    0,      &BAD },
    { 0x05, "",          OP_BYTE,    0,      &BAD },
    { 0x06, "",          OP_BYTE,    0,      &BAD },
    { 0x07, "",          OP_BYTE,    0,      &BAD },
    { 0x08, "",          OP_BYTE,    0,      &BAD },
    { 0x09, "",          OP_BYTE,    0,      &BAD },
    { 0x0A, "",          OP_BYTE,    0,      &BAD },
    { 0x0B, "",          OP_BYTE,    0,      &BAD },
    { 0x0C, "",          OP_BYTE,    0,      &BAD },
    { 0x0D, "",          OP_BYTE,    0,      &BAD },
    { 0x0E, "",          OP_BYTE,    0,      &BAD },
    { 0x0F, "",          OP_BYTE,    0,      &BAD },
    { 0x10, "",          OP_BYTE,    0,      &BAD },
    { 0x11, "",          OP_BYTE,    0,      &BAD },
    { 0x12, "",          OP_BYTE,    0,      &BAD },
    { 0x13, "",          OP_BYTE,    0,      &BAD },
    { 0x14, "",          OP_BYTE,    0,      &BAD },
    { 0x15, "",          OP_BYTE,    0,      &BAD },
    { 0x16, "",          OP_BYTE,    0,      &BAD },
    { 0x17, "",          OP_BYTE,    0,      &BAD },
    { 0x18, "",          OP_BYTE,    0,      &BAD },
    { 0x19, "",          OP_BYTE,    0,      &BAD },
    { 0x1A, "",          OP_BYTE,    0,      &BAD },
    { 0x1B, "",          OP_BYTE,    0,      &BAD },
    { 0x1C, "",          OP_BYTE,    0,      &BAD },
    { 0x1D, "",          OP_BYTE,    0,      &BAD },
    { 0x1E, "",          OP_BYTE,    0,      &BAD },
    { 0x1F, "",          OP_BYTE,    0,      &BAD },
    { 0x20, "",          OP_BYTE,    0,      &BAD },
    { 0x21, "",          OP_BYTE,    0,      &BAD },
    { 0x22, "",          OP_BYTE,    0,      &BAD },
    { 0x23, "",          OP_BYTE,    0,      &BAD },
    { 0x24, "",          OP_BYTE,    0,      &BAD },
    { 0x25, "",          OP_BYTE,    0,      &BAD },
    { 0x26, "",          OP_BYTE,    0,      &BAD },
    { 0x27, "",          OP_BYTE,    0,      &BAD },
    { 0x28, "",          OP_BYTE,    0,      &BAD },
    { 0x29, "",          OP_BYTE,    0,      &BAD },
    { 0x2A, "",          OP_BYTE,    0,      &BAD },
    { 0x2B, "",          OP_BYTE,    0,      &BAD },
    { 0x2C, "",          OP_BYTE,    0,      &BAD },
    { 0x2D, "",          OP_BYTE,    0,      &BAD },
    { 0x2E, "",          OP_BYTE,    0,      &BAD },
    { 0x2F, "",          OP_BYTE,    0,      &BAD },
    { 0x30, "",          OP_BYTE,    0,      &BAD },
    { 0x31, "",          OP_BYTE,    0,      &BAD },
    { 0x32, "",          OP_BYTE,    0,      &BAD },
    { 0x33, "",          OP_BYTE,    0,      &BAD },
    { 0x34, "",          OP_BYTE,    0,      &BAD },
    { 0x35, "",          OP_BYTE,    0,      &BAD },
    { 0x36, "",          OP_BYTE,    0,      &BAD },
    { 0x37, "",          OP_BYTE,    0,      &BAD },
    { 0x38, "",          OP_BYTE,    0,      &BAD },
    { 0x39, "",          OP_BYTE,    0,      &BAD },
    { 0x3A, "",          OP_BYTE,    0,      &BAD },
    { 0x3B, "",          OP_BYTE,    0,      &BAD },
    { 0x3C, "",          OP_BYTE,    0,      &BAD },
    { 0x3D, "",          OP_BYTE,    0,      &BAD },
    { 0x3E, "",          OP_BYTE,    0,      &BAD },
    { 0x3F, "",          OP_BYTE,    0,      &BAD },
    { 0x40, "",          OP_BYTE,    0,      &BAD },
    { 0x41, "",          OP_BYTE,    0,      &BAD },
    { 0x42, "",          OP_BYTE,    0,      &BAD },
    { 0x43, "",          OP_BYTE,    0,      &BAD },
    { 0x44, "",          OP_BYTE,    0,      &BAD },
    { 0x45, "",          OP_BYTE,    0,      &BAD },
    { 0x46, "",          OP_BYTE,    0,      &BAD },
    { 0x47, "",          OP_BYTE,    0,      &BAD },
    { 0x48, "",          OP_BYTE,    0,      &BAD },
    { 0x49, "",          OP_BYTE,    0,      &BAD },
    { 0x4A, "",          OP_BYTE,    0,      &BAD },
    { 0x4B, "",          OP_BYTE,    0,      &BAD },
    { 0x4C, "",          OP_BYTE,    0,      &BAD },
    { 0x4D, "",          OP_BYTE,    0,      &BAD },
    { 0x4E, "",          OP_BYTE,    0,      &BAD },
    { 0x4F, "",          OP_BYTE,    0,      &BAD },
    { 0x50, "",          OP_BYTE,    0,      &BAD },
    { 0x51, "",          OP_BYTE,    0,      &BAD },
    { 0x52, "",          OP_BYTE,    0,      &BAD },
    { 0x53, "",          OP_BYTE,    0,      &BAD },
    { 0x54, "",          OP_BYTE,    0,      &BAD },
    { 0x55, "",          OP_BYTE,    0,      &BAD },
    { 0x56, "",          OP_BYTE,    0,      &BAD },
    { 0x57, "",          OP_BYTE,    0,      &BAD },
    { 0x58, "",          OP_BYTE,    0,      &BAD },
    { 0x59, "",          OP_BYTE,    0,      &BAD },
    { 0x5A, "",          OP_BYTE,    0,      &BAD },
    { 0x5B, "",          OP_BYTE,    0,      &BAD },
    { 0x5C, "",          OP_BYTE,    0,      &BAD },
    { 0x5D, "",          OP_BYTE,    0,      &BAD },
    { 0x5E, "",          OP_BYTE,    0,      &BAD },
    { 0x5F, "",          OP_BYTE,    0,      &BAD },
    { 0x60, "",          OP_BYTE,    0,      &BAD },
    { 0x61, "",          OP_BYTE,    0,      &BAD },
    { 0x62, "",          OP_BYTE,    0,      &BAD },
    { 0x63, "",          OP_BYTE,    0,      &BAD },
    { 0x64, "",          OP_BYTE,    0,      &BAD },
    { 0x65, "",          OP_BYTE,    0,      &BAD },
    { 0x66, "",          OP_BYTE,    0,      &BAD },
    { 0x67, "",          OP_BYTE,    0,      &BAD },
    { 0x68, "",          OP_BYTE,    0,      &BAD },
    { 0x69, "",          OP_BYTE,    0,      &BAD },
    { 0x6A, "",          OP_BYTE,    0,      &BAD },
    { 0x6B, "",          OP_BYTE,    0,      &BAD },
    { 0x6C, "",          OP_BYTE,    0,      &BAD },
    { 0x6D, "",          OP_BYTE,    0,      &BAD },
    { 0x6E, "",          OP_BYTE,    0,      &BAD },
    { 0x6F, "",          OP_BYTE,    0,      &BAD },
    { 0x70, "",          OP_BYTE,    0,      &BAD },
    { 0x71, "",          OP_BYTE,    0,      &BAD },
    { 0x72, "",          OP_BYTE,    0,      &BAD },
    { 0x73, "",          OP_BYTE,    0,      &BAD },
    { 0x74, "",          OP_BYTE,    0,      &BAD },
    { 0x75, "",          OP_BYTE,    0,      &BAD },
    { 0x76, "",          OP_BYTE,    0,      &BAD },
    { 0x77, "",          OP_BYTE,    0,      &BAD },
    { 0x78, "",          OP_BYTE,    0,      &BAD },
    { 0x79, "",          OP_BYTE,    0,      &BAD },
    { 0x7A, "",          OP_BYTE,    0,      &BAD },
    { 0x7B, "",          OP_BYTE,    0,      &BAD },
    { 0x7C, "",          OP_BYTE,    0,      &BAD },
    { 0x7D, "",          OP_BYTE,    0,      &BAD },
    { 0x7E, "",          OP_BYTE,    0,      &BAD },
    { 0x7F, "",          OP_BYTE,    0,      &BAD },
    { 0x80, "",          OP_BYTE,    0,      &BAD },
    { 0x81, "",          OP_BYTE,    0,      &BAD },
    { 0x82, "",          OP_BYTE,    0,      &BAD },
    { 0x83, "",          OP_BYTE,    0,      &BAD },
    { 0x84, "",          OP_BYTE,    0,      &BAD },
    { 0x85, "",          OP_BYTE,    0,      &BAD },
    { 0x86, "",          OP_BYTE,    0,      &BAD },
    { 0x87, "",          OP_BYTE,    0,      &BAD },
    { 0x88, "",          OP_BYTE,    0,      &BAD },
    { 0x89, "",          OP_BYTE,    0,      &BAD },
    { 0x8A, "",          OP_BYTE,    0,      &BAD },
    { 0x8B, "",          OP_BYTE,    0,      &BAD },
    { 0x8C, "",          OP_BYTE,    0,      &BAD },
    { 0x8D, "",          OP_BYTE,    0,      &BAD },
    { 0x8E, "",          OP_BYTE,    0,      &BAD },
    { 0x8F, "",          OP_BYTE,    0,      &BAD },
    { 0x90, "",          OP_BYTE,    0,      &BAD },
    { 0x91, "",          OP_BYTE,    0,      &BAD },
    { 0x92, "",          OP_BYTE,    0,      &BAD },
    { 0x93, "",          OP_BYTE,    0,      &BAD },
    { 0x94, "",          OP_BYTE,    0,      &BAD },
    { 0x95, "",          OP_BYTE,    0,      &BAD },
    { 0x96, "",          OP_BYTE,    0,      &BAD },
    { 0x97, "",          OP_BYTE,    0,      &BAD },
    { 0x98, "",          OP_BYTE,    0,      &BAD },
    { 0x99, "",          OP_BYTE,    0,      &BAD },
    { 0x9A, "",          OP_BYTE,    0,      &BAD },
    { 0x9B, "",          OP_BYTE,    0,      &BAD },
    { 0x9C, "",          OP_BYTE,    0,      &BAD },
    { 0x9D, "",          OP_BYTE,    0,      &BAD },
    { 0x9E, "",          OP_BYTE,    0,      &BAD },
    { 0x9F, "",          OP_BYTE,    0,      &BAD },
    { 0xA0, "",          OP_BYTE,    0,      &BAD },
    { 0xA1, "",          OP_BYTE,    0,      &BAD },
    { 0xA2, "",          OP_BYTE,    0,      &BAD },
    { 0xA3, "",          OP_BYTE,    0,      &BAD },
    { 0xA4, "",          OP_BYTE,    0,      &BAD },
    { 0xA5, "",          OP_BYTE,    0,      &BAD },
    { 0xA6, "",          OP_BYTE,    0,      &BAD },
    { 0xA7, "",          OP_BYTE,    0,      &BAD },
    { 0xA8, "",          OP_BYTE,    0,      &BAD },
    { 0xA9, "",          OP_BYTE,    0,      &BAD },
    { 0xAA, "",          OP_BYTE,    0,      &BAD },
    { 0xAB, "",          OP_BYTE,    0,      &BAD },
    { 0xAC, "",          OP_BYTE,    0,      &BAD },
    { 0xAD, "",          OP_BYTE,    0,      &BAD },
    { 0xAE, "",          OP_BYTE,    0,      &BAD },
    { 0xAF, "",          OP_BYTE,    0,      &BAD },
    { 0xB0, "",          OP_BYTE,    0,      &BAD },
    { 0xB1, "",          OP_BYTE,    0,      &BAD },
    { 0xB2, "",          OP_BYTE,    0,      &BAD },
    { 0xB3, "",          OP_BYTE,    0,      &BAD },
    { 0xB4, "",          OP_BYTE,    0,      &BAD },
    { 0xB5, "",          OP_BYTE,    0,      &BAD },
    { 0xB6, "",          OP_BYTE,    0,      &BAD },
    { 0xB7, "",          OP_BYTE,    0,      &BAD },
    { 0xB8, "",          OP_BYTE,    0,      &BAD },
    { 0xB9, "",          OP_BYTE,    0,      &BAD },
    { 0xBA, "",          OP_BYTE,    0,      &BAD },
    { 0xBB, "",          OP_BYTE,    0,      &BAD },
    { 0xBC, "",          OP_BYTE,    0,      &BAD },
    { 0xBD, "",          OP_BYTE,    0,      &BAD },
    { 0xBE, "",          OP_BYTE,    0,      &BAD },
    { 0xBF, "",          OP_BYTE,    0,      &BAD },
    { 0xC0, "",          OP_BYTE,    0,      &BAD },
    { 0xC1, "",          OP_BYTE,    0,      &BAD },
    { 0xC2, "",          OP_BYTE,    0,      &BAD },
    { 0xC3, "",          OP_BYTE,    0,      &BAD },
    { 0xC4, "",          OP_BYTE,    0,      &BAD },
    { 0xC5, "",          OP_BYTE,    0,      &BAD },
    { 0xC6, "",          OP_BYTE,    0,      &BAD },
    { 0xC7, "",          OP_BYTE,    0,      &BAD },
    { 0xC8, "",          OP_BYTE,    0,      &BAD },
    { 0xC9, "",          OP_BYTE,    0,      &BAD },
    { 0xCA, "",          OP_BYTE,    0,      &BAD },
    { 0xCB, "",          OP_BYTE,    0,      &BAD },
    { 0xCC, "",          OP_BYTE,    0,      &BAD },
    { 0xCD, "",          OP_BYTE,    0,      &BAD },
    { 0xCE, "",          OP_BYTE,    0,      &BAD },
    { 0xCF, "",          OP_BYTE,    0,      &BAD },
    { 0xD0, "",          OP_BYTE,    0,      &BAD },
    { 0xD1, "",          OP_BYTE,    0,      &BAD },
    { 0xD2, "",          OP_BYTE,    0,      &BAD },
    { 0xD3, "",          OP_BYTE,    0,      &BAD },
    { 0xD4, "",          OP_BYTE,    0,      &BAD },
    { 0xD5, "",          OP_BYTE,    0,      &BAD },
    { 0xD6, "",          OP_BYTE,    0,      &BAD },
    { 0xD7, "",          OP_BYTE,    0,      &BAD },
    { 0xD8, "",          OP_BYTE,    0,      &BAD },
    { 0xD9, "",          OP_BYTE,    0,      &BAD },
    { 0xDA, "",          OP_BYTE,    0,      &BAD },
    { 0xDB, "",          OP_BYTE,    0,      &BAD },
    { 0xDC, "",          OP_BYTE,    0,      &BAD },
    { 0xDD, "",          OP_BYTE,    0,      &BAD },
    { 0xDE, "",          OP_BYTE,    0,      &BAD },
    { 0xDF, "",          OP_BYTE,    0,      &BAD },
    { 0xE0, "",          OP_BYTE,    0,      &BAD },
    { 0xE1, "POP IY",          OP_BYTE,    14,      &POP_IY},
    { 0xE2, "",          OP_BYTE,    0,      &BAD },
    { 0xE3, "",          OP_BYTE,    0,      &BAD },
    { 0xE4, "",          OP_BYTE,    0,      &BAD },
    { 0xE5, "",          OP_BYTE,    0,      &BAD },
    { 0xE6, "",          OP_BYTE,    0,      &BAD },
    { 0xE7, "",          OP_BYTE,    0,      &BAD },
    { 0xE8, "",          OP_BYTE,    0,      &BAD },
    { 0xE9, "",          OP_BYTE,    0,      &BAD },
    { 0xEA, "",          OP_BYTE,    0,      &BAD },
    { 0xEB, "",          OP_BYTE,    0,      &BAD },
    { 0xEC, "",          OP_BYTE,    0,      &BAD },
    { 0xED, "",          OP_BYTE,    0,      &BAD },
    { 0xEE, "",          OP_BYTE,    0,      &BAD },
    { 0xEF, "",          OP_BYTE,    0,      &BAD },
    { 0xF0, "",          OP_BYTE,    0,      &BAD },
    { 0xF1, "",          OP_BYTE,    0,      &BAD },
    { 0xF2, "",          OP_BYTE,    0,      &BAD },
    { 0xF3, "",          OP_BYTE,    0,      &BAD },
    { 0xF4, "",          OP_BYTE,    0,      &BAD },
    { 0xF5, "",          OP_BYTE,    0,      &BAD },
    { 0xF6, "",          OP_BYTE,    0,      &BAD },
    { 0xF7, "",          OP_BYTE,    0,      &BAD },
    { 0xF8, "",          OP_BYTE,    0,      &BAD },
    { 0xF9, "",          OP_BYTE,    0,      &BAD },
    { 0xFA, "",          OP_BYTE,    0,      &BAD },
    { 0xFB, "",          OP_BYTE,    0,      &BAD },
    { 0xFC, "",          OP_BYTE,    0,      &BAD },
    { 0xFD, "",          OP_BYTE,    0,      &BAD },
    { 0xFE, "",          OP_BYTE,    0,      &BAD },
    { 0xFF, "",          OP_BYTE,    0,      &BAD }
};

Z80_Instruction FetchIYInstruction(uint8_t opcode) {
    return IYInstructions[opcode];
}