#include <stdio.h>
#include "unity.h"
#include "z80_logic.h"

void test_z80_logic_ld_byte() {
    Z80_CPU cpu;
    Z80_CPU_Init(&cpu);

    ld_byte(&cpu, &cpu.A, 0xEF, 2);
    TEST_ASSERT_EQUAL(0xEF, cpu.A);
    TEST_ASSERT_EQUAL(0x02, cpu.PC);

    ld_byte(&cpu, &cpu.H, 0xAB, 1);
    TEST_ASSERT_EQUAL(0xAB, cpu.H);
    TEST_ASSERT_EQUAL(0x03, cpu.PC);
}

void test_z80_logic_ld_word() {

}

void test_z80_logic_add_r() {
    Z80_CPU cpu;
    
    // Test 0 + 1 - expect no flags
    Z80_CPU_Init(&cpu);
    add_r(&cpu, 0x01);
    TEST_ASSERT_EQUAL(0x01, cpu.A);
    TEST_ASSERT_BIT_LOW(FLAG_C, cpu.F);
    TEST_ASSERT_BIT_LOW(FLAG_N, cpu.F);
    TEST_ASSERT_BIT_LOW(FLAG_PV, cpu.F);
    TEST_ASSERT_BIT_LOW(FLAG_H, cpu.F);
    TEST_ASSERT_BIT_LOW(FLAG_Z, cpu.F);
    TEST_ASSERT_BIT_LOW(FLAG_S, cpu.F);

    // Test 0xFF + 0x01 - expect overflow, zero flags set
    Z80_CPU_Init(&cpu);
    cpu.A = 0xFF;
    add_r(&cpu, 0x01);
    TEST_ASSERT_EQUAL(0x00, cpu.A);
    TEST_ASSERT_BIT_HIGH(FLAG_C, cpu.F);
    TEST_ASSERT_BIT_LOW(FLAG_N, cpu.F);
    TEST_ASSERT_BIT_LOW(FLAG_PV, cpu.F);
    TEST_ASSERT_BIT_LOW(FLAG_H, cpu.F);
    TEST_ASSERT_BIT_HIGH(FLAG_Z, cpu.F);
    TEST_ASSERT_BIT_LOW(FLAG_S, cpu.F);

    // Test 0b00001000 + 0b00001000, expect half-carry flag set
    Z80_CPU_Init(&cpu);
    cpu.A = 0b00001000;
    add_r(&cpu, 0b00001000);
    TEST_ASSERT_EQUAL(0b00010000, cpu.A);
    TEST_ASSERT_BIT_LOW(FLAG_C, cpu.F);
    TEST_ASSERT_BIT_LOW(FLAG_N, cpu.F);
    TEST_ASSERT_BIT_LOW(FLAG_PV, cpu.F);
    TEST_ASSERT_BIT_HIGH(FLAG_H, cpu.F);
    TEST_ASSERT_BIT_LOW(FLAG_Z, cpu.F);
    TEST_ASSERT_BIT_LOW(FLAG_S, cpu.F);

    // Test 120 + 105 = 225 (-95 if signed), expect overflow, half-carry, and sign flags to be set
    Z80_CPU_Init(&cpu);
    cpu.A = 120;
    add_r(&cpu, 105);
    TEST_ASSERT_EQUAL(225, cpu.A);
    TEST_ASSERT_BIT_LOW(FLAG_C, cpu.F);
    TEST_ASSERT_BIT_LOW(FLAG_N, cpu.F);
    TEST_ASSERT_BIT_HIGH(FLAG_PV, cpu.F);
    TEST_ASSERT_BIT_HIGH(FLAG_H, cpu.F);
    TEST_ASSERT_BIT_LOW(FLAG_Z, cpu.F);
    TEST_ASSERT_BIT_HIGH(FLAG_S, cpu.F);
}

void test_z80_logic_sub() {
    
}

void test_z80_logic_and() {
    
}

int main(int argc, char const *argv[])
{
    UNITY_BEGIN();

    // Run tests
    RUN_TEST(test_z80_logic_ld_byte);
    RUN_TEST(test_z80_logic_ld_word);
    RUN_TEST(test_z80_logic_add_r);

    return UNITY_END();
}
