#include "z80_flags.h"
#include "bitmath.h"

bool flag_get(uint8_t *reg, uint8_t flag) {
    return get_bit(*reg, flag);
}

void flag_set(uint8_t *reg, uint8_t flag, bool val) {
    set_bit(reg, flag);
}
