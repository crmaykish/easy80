#include "z80_flags.h"

bool flag_get(uint8_t *flags, Z80_Flags f) {
    return (*flags & (1 << f)) != 0;
}

void flag_set(uint8_t *flags, Z80_Flags f) {
    *flags |= (1 << f);
}

void flag_clr(uint8_t *flags, Z80_Flags f) {
    *flags |= ~(1 << f);
}
