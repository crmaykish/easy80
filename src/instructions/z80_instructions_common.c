#include <stdlib.h>
#include <stdio.h>
#include "z80_instructions_common.h"
#include "z80_instructions_main.h"
#include "z80_instructions_extended.h"
#include "z80_instructions_bit.h"
#include "z80_instructions_ix.h"
#include "z80_instructions_iy.h"
#include "z80_logic.h"

void BAD(Z80_CPU *z) { printf("INVALID OPCODE: %02X %02X\n", op(z, 0), op(z, 1)); exit(1); }

Z80_Instruction Z80_FetchInstruction(Z80_CPU *z) {
    Z80_Instruction instruction;

    uint8_t op0 = op(z, 0);
    uint8_t op1 = op(z, 1);
    uint8_t op2 = op(z, 2);

    switch (op0) {
        case PREF_EXTD:
            // Extended instruction set
            instruction = FetchExtendedInstruction(op1);
            break;
        case PREF_BIT:
            // Bit instruction set
            instruction = FetchBitInstruction(op1);
            break;
        case PREF_IX:
            if (op1 == PREF_BIT) {
                printf("IX BIT instructions not implemented.\n");
                exit(1);
            }
            else {
                instruction = FetchIXInstruction(op1);
            }
            break;
        case PREF_IY:
            // IY instruction set
            if (op1 == PREF_BIT) {
                printf("IY BIT instructions not implemented.\n");
                exit(1);
            }
            else {
                instruction = FetchIYInstruction(op1);
            }
            break;
        default:
            // Main instruction set
            instruction = FetchMainInstruction(op0);
            break;
    }

    return instruction;
}