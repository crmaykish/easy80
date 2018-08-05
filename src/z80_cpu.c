#include "z80_cpu.h"
#include "stdio.h"
#include "string.h"


void Z80_CPU_Init(Z80_CPU *cpu) {
    // CPU to stopped
    cpu->State = STOPPED;

    // Wipe memory
    memset(&cpu->Memory, 0, sizeof(uint8_t) * MAX_ADDRESS);

    // Zero out registers
    Z80_Registers_Init(&cpu->Registers);
}

void Z80_CPU_SetMemory(Z80_CPU *cpu, uint8_t data[], size_t size, uint16_t offset) {
    // TODO: bounds checking on Memory array
    memcpy(&cpu->Memory[offset], data, size);
}

void Z80_CPU_Cycle(Z80_CPU *cpu) {
    // Fetch current opcode
    uint8_t op0 = cpu->Memory[cpu->Registers.PC];
    // Fetch next two bytes for operations
    // TODO: this won't work if at the end of Memory
    uint8_t op1 = cpu->Memory[cpu->Registers.PC + 1];
    uint8_t op2 = cpu->Memory[cpu->Registers.PC + 2];

    // TODO: No overflow or flag checking here yet

    switch (op0) {
        case 0x00:  // NOP          (1 byte)
            cpu->Registers.PC++;
            break;
        case 0x06:  // LD B,*       (2 bytes)
            cpu->Registers.B = op1;
            cpu->Registers.PC+=2;
            break;
        case 0x32:  // LD (**),A    (3 bytes)
            cpu->Memory[combine(op2, op1)] = cpu->Registers.A;
            cpu->Registers.PC+=3;
            break;
        case 0x3C:  // INC A        (1 byte)
            cpu->Registers.A++;
            cpu->Registers.PC++;
            break;
        case 0x3E:  // LD A,*       (2 bytes)
            cpu->Registers.A = op1;
            cpu->Registers.PC+=2;
            break;
        case 0x80:  // ADD A,B      (1 byte)
            cpu->Registers.A += cpu->Registers.B;
            cpu->Registers.PC++;
            break;
        case 0xC9:
            cpu->Registers.PC++;
            break;  // RET          (1 byte)
        default:
            printf("%X | %s\n", op0, "Opcode not implemented!");
            break;
    }
}

void Z80_CPU_PrintRegisters(Z80_CPU *cpu) {
    printf("PC: %X | AF: %X | BC: %X | DE: %X | HL: %X\n",
        cpu->Registers.PC,
        AF(&cpu->Registers),
        BC(&cpu->Registers),
        DE(&cpu->Registers),
        HL(&cpu->Registers)
    );
}