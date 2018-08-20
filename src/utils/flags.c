#include "flags.h"
#include "bitmath.h"

bool flag_get(uint8_t *reg, uint8_t flag) {
    return bit_get(*reg, flag);
}

void flag_set(uint8_t *reg, uint8_t flag, bool val) {
    if (val) {
        bit_set(reg, flag);
    }
    else {
        bit_clear(reg, flag);
    }
}
