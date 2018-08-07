#ifndef Z80_FLAGS_H
#define Z80_FLAGS_H

#include <stdint.h>
#include <stdbool.h>

typedef enum {
    FLAG_C = 0,
    FLAG_N = 1,
    FLAG_PV = 2,
    FLAG_H = 4,
    FLAG_Z = 6,
    FLAG_S = 7
} Z80_Flags;

bool flag_get(uint8_t *flags, Z80_Flags f);

void flag_set(uint8_t *flags, Z80_Flags f);

void flag_clr(uint8_t *flags, Z80_Flags f);

#endif