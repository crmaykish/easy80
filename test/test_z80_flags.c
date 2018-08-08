#include <stdio.h>
#include "unity.h"
#include "z80_flags.h"

void test_z80_flags_flag_get() {
    uint8_t t = 0b00001111;
    
    TEST_ASSERT_TRUE(flag_get(&t, FLAG_C));
    TEST_ASSERT_FALSE(flag_get(&t, FLAG_Z));
}

void test_z80_flags_flag_set() {
    uint8_t t = 0b11110000;

    flag_set(&t, FLAG_C, true);
    flag_set(&t, FLAG_S, false);

    TEST_ASSERT_BIT_HIGH(FLAG_C, t);
    TEST_ASSERT_BIT_LOW(FLAG_S, t);
}

int main(int argc, char const *argv[])
{
    UNITY_BEGIN();

    // Run tests
    RUN_TEST(test_z80_flags_flag_get);
    RUN_TEST(test_z80_flags_flag_set);

    return UNITY_END();
}