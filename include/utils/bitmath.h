/**
 * @brief Utility code relating to bit and byte manipulation
 * 
 * @file bitmath.h
 * @author crmaykish
 * @date 2018-08-06
 */

#ifndef BITMATH_H
#define BITMATH_H

#include <stdint.h>
#include <stdbool.h>

bool bit_get(uint8_t target, uint8_t bit);

void bit_set(uint8_t *target, uint8_t bit);

void bit_clear(uint8_t *target, uint8_t bit);

uint16_t combine(uint8_t x, uint8_t y);

uint8_t split_1(uint16_t r);

uint8_t split_2(uint16_t r);

void binary_string(char *buffer, uint8_t n);

#endif