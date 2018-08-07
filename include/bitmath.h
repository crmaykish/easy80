#ifndef BITMATH_H
#define BITMATH_H

#include <stdint.h>

uint16_t combine(uint8_t x, uint8_t y);

uint8_t split_1(uint16_t r);

uint8_t split_2(uint16_t r);

#endif