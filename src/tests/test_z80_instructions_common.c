#include "z80_instructions_common.h"
#include "flags.h"
#include "unity.h"

#define EASY80_TEST(test_name) Before(); RUN_TEST(test_name); After();

static Z80_CPU z;

void Before() {
    Z80_CPU_Init(&z);
}

void After() {
    Z80_CPU_Destroy(&z);
}

void test_even_parity() {
    TEST_ASSERT_TRUE(even_parity(0b10101010));
    TEST_ASSERT_FALSE(even_parity(0b10010001));
}

void test_ld_byte() {
    ld_byte(&z, z.A, 0x99);
    TEST_ASSERT_EQUAL(0x99, *z.A);
}

void test_ld_word() {
    ld_word(&z, z.BC, 0xABCD);
    TEST_ASSERT_EQUAL(0xABCD, *z.BC);
}

void test_add_byte() {
    add_byte(&z, 0x01);
    TEST_ASSERT_EQUAL(0x01, *z.A);
    TEST_ASSERT_BIT_LOW(FLAG_C, *z.F);
    TEST_ASSERT_BIT_LOW(FLAG_N, *z.F);
    TEST_ASSERT_BIT_LOW(FLAG_PV, *z.F);
    TEST_ASSERT_BIT_LOW(FLAG_H, *z.F);
    TEST_ASSERT_BIT_LOW(FLAG_Z, *z.F);
    TEST_ASSERT_BIT_LOW(FLAG_S, *z.F);

    add_byte(&z, 0xFF);
    TEST_ASSERT_EQUAL(0x00, *z.A);
    TEST_ASSERT_BIT_HIGH(FLAG_C, *z.F);
    TEST_ASSERT_BIT_LOW(FLAG_N, *z.F);
    TEST_ASSERT_BIT_LOW(FLAG_PV, *z.F);
    TEST_ASSERT_BIT_LOW(FLAG_H, *z.F);
    TEST_ASSERT_BIT_HIGH(FLAG_Z, *z.F);
    TEST_ASSERT_BIT_LOW(FLAG_S, *z.F);
}

int main() {
    UNITY_BEGIN();

    EASY80_TEST(test_even_parity);
    EASY80_TEST(test_ld_byte);
    EASY80_TEST(test_ld_word);
    EASY80_TEST(test_add_byte);

    return UNITY_END();
}