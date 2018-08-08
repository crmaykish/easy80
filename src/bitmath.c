#include "bitmath.h"

bool bit_get(uint8_t target, uint8_t bit) {
    return (target & (1 << bit)) != 0;
}

void bit_set(uint8_t *target, uint8_t bit) {
    *target |= (1 << bit);
}

void bit_clear(uint8_t *target, uint8_t bit) {
    *target &= ~(1 << bit);
}

uint16_t combine(uint8_t x, uint8_t y) {
    return (x << 8) | y;
}

uint8_t split_1(uint16_t r) {
    return (r & 0xFF00) >> 8;
}

uint8_t split_2(uint16_t r) {
    return r & 0x00FF;
}