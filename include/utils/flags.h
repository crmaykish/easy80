/**
 * @brief Control Z80 CPU flags
 * 
 * @file flags.h
 * @author crmaykish
 * @date 2018-08-06
 */

#ifndef FLAGS_H
#define FLAGS_H

#include <stdint.h>
#include <stdbool.h>

#define FLAG_C      0     // Carry
#define FLAG_N      1     // Add/Subtract
#define FLAG_PV     2     // Parity/Overflow
#define FLAG_H      4     // Half Carry
#define FLAG_Z      6     // Zero
#define FLAG_S      7     // Sign

/**
 * @brief Returns the given flag bit from the target byte
 * 
 * e.g. To get the H flag from the register F, use flag_get(F, FLAG_H);
 * 
 * @param target Register from which to get the flag
 * @param flag The flag bit to return
 * @return true if the flag bit is high
 * @return false if the flag bit is low
 */
bool flag_get(uint8_t *target, uint8_t flag);

/**
 * @brief Set the given flag bit to the given value in the target byte
 * 
 * @param target Register in which to set the flag
 * @param flag The flag bit to set
 * @param val Set the flag high or low
 */
void flag_set(uint8_t *target, uint8_t flag, bool val);

#endif