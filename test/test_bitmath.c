#include <stdio.h>
#include "unity.h"
#include "bitmath.h"

void test_bitmath_bit_get() {
    TEST_ASSERT_TRUE(bit_get(0b11110000, 6));
    TEST_ASSERT_FALSE(bit_get(0b11110000, 1));
}

void test_bitmath_bit_set() {
    uint8_t t = 0b00000000;

    bit_set(&t, 0);
    bit_set(&t, 4);
    bit_set(&t, 6);

    TEST_ASSERT_BIT_HIGH(0, t);
    TEST_ASSERT_BIT_HIGH(4, t);
    TEST_ASSERT_BIT_HIGH(6, t);
}

void test_bitmath_bit_clear() {
    uint8_t t = 0b11111111;

    bit_clear(&t, 0);
    bit_clear(&t, 4);
    bit_clear(&t, 6);

    TEST_ASSERT_BIT_LOW(0, t);
    TEST_ASSERT_BIT_LOW(4, t);
    TEST_ASSERT_BIT_LOW(6, t);
}

int main(int argc, char const *argv[])
{
    UNITY_BEGIN();

    // Run tests
    RUN_TEST(test_bitmath_bit_get);
    RUN_TEST(test_bitmath_bit_set);
    RUN_TEST(test_bitmath_bit_clear);

    return UNITY_END();
}
