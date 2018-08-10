#include <stdio.h>
#include "unity.h"
#include "z80_logic.h"

void test_z80_logic_ld_byte() {
    Z80_CPU cpu;
    Z80_CPU_Init(&cpu);

    ld_byte(&cpu, &cpu.A, 0xEF);
    TEST_ASSERT_EQUAL(0xEF, cpu.A);

    ld_byte(&cpu, &cpu.H, 0xAB);
    TEST_ASSERT_EQUAL(0xAB, cpu.H);
}

void test_z80_logic_ld_word() {

}

void test_z80_logic_add() {
    Z80_CPU cpu;
    
    // Test 0 + 1
    Z80_CPU_Init(&cpu);
    add(&cpu, 0x01);
    TEST_ASSERT_EQUAL(0x01, cpu.A);
    TEST_ASSERT_BIT_LOW(FLAG_C, cpu.F);
    TEST_ASSERT_BIT_LOW(FLAG_N, cpu.F);
    TEST_ASSERT_BIT_LOW(FLAG_PV, cpu.F);
    TEST_ASSERT_BIT_LOW(FLAG_H, cpu.F);
    TEST_ASSERT_BIT_LOW(FLAG_Z, cpu.F);
    TEST_ASSERT_BIT_LOW(FLAG_S, cpu.F);

    // Test 0xFF + 0x01
    Z80_CPU_Init(&cpu);
    cpu.A = 0xFF;
    add(&cpu, 0x01);
    TEST_ASSERT_EQUAL(0x00, cpu.A);
    TEST_ASSERT_BIT_HIGH(FLAG_C, cpu.F);
    TEST_ASSERT_BIT_LOW(FLAG_N, cpu.F);
    TEST_ASSERT_BIT_LOW(FLAG_PV, cpu.F);
    TEST_ASSERT_BIT_LOW(FLAG_H, cpu.F);
    TEST_ASSERT_BIT_HIGH(FLAG_Z, cpu.F);
    TEST_ASSERT_BIT_LOW(FLAG_S, cpu.F);

    // Test 0b00001000 + 0b00001000
    Z80_CPU_Init(&cpu);
    cpu.A = 0b00001000;
    add(&cpu, 0b00001000);
    TEST_ASSERT_EQUAL(0b00010000, cpu.A);
    TEST_ASSERT_BIT_LOW(FLAG_C, cpu.F);
    TEST_ASSERT_BIT_LOW(FLAG_N, cpu.F);
    TEST_ASSERT_BIT_LOW(FLAG_PV, cpu.F);
    TEST_ASSERT_BIT_HIGH(FLAG_H, cpu.F);
    TEST_ASSERT_BIT_LOW(FLAG_Z, cpu.F);
    TEST_ASSERT_BIT_LOW(FLAG_S, cpu.F);

    // Test 120 + 105 = 225 (-95 if signed)
    Z80_CPU_Init(&cpu);
    cpu.A = 120;
    add(&cpu, 105);
    TEST_ASSERT_EQUAL(225, cpu.A);
    TEST_ASSERT_BIT_LOW(FLAG_C, cpu.F);
    TEST_ASSERT_BIT_LOW(FLAG_N, cpu.F);
    TEST_ASSERT_BIT_HIGH(FLAG_PV, cpu.F);
    TEST_ASSERT_BIT_HIGH(FLAG_H, cpu.F);
    TEST_ASSERT_BIT_LOW(FLAG_Z, cpu.F);
    TEST_ASSERT_BIT_HIGH(FLAG_S, cpu.F);
}

void test_z80_logic_sub() {
    Z80_CPU cpu;
    
    // Test 0 - 1
    Z80_CPU_Init(&cpu);
    cpu.A = 0;
    sub(&cpu, 0x01);
    TEST_ASSERT_EQUAL(0xFF, cpu.A);
    TEST_ASSERT_BIT_HIGH(FLAG_C, cpu.F);
    TEST_ASSERT_BIT_HIGH(FLAG_N, cpu.F);
    TEST_ASSERT_BIT_LOW(FLAG_PV, cpu.F);
    TEST_ASSERT_BIT_HIGH(FLAG_H, cpu.F);
    TEST_ASSERT_BIT_LOW(FLAG_Z, cpu.F);
    TEST_ASSERT_BIT_HIGH(FLAG_S, cpu.F);

    // Test 127 - (-64)
    Z80_CPU_Init(&cpu);
    cpu.A = 127;
    sub(&cpu, 0b11000000);
    TEST_ASSERT_EQUAL(191, cpu.A);
    TEST_ASSERT_BIT_HIGH(FLAG_C, cpu.F);
    TEST_ASSERT_BIT_HIGH(FLAG_N, cpu.F);
    TEST_ASSERT_BIT_HIGH(FLAG_PV, cpu.F);
    TEST_ASSERT_BIT_LOW(FLAG_H, cpu.F);
    TEST_ASSERT_BIT_LOW(FLAG_Z, cpu.F);
    TEST_ASSERT_BIT_HIGH(FLAG_S, cpu.F);

    // Test 0b01000000 - 0b00000001
    Z80_CPU_Init(&cpu);
    cpu.A = 0b01000000;
    sub(&cpu, 00000001);
    TEST_ASSERT_EQUAL(63, cpu.A);
    TEST_ASSERT_BIT_LOW(FLAG_C, cpu.F);
    TEST_ASSERT_BIT_HIGH(FLAG_N, cpu.F);
    TEST_ASSERT_BIT_LOW(FLAG_PV, cpu.F);
    TEST_ASSERT_BIT_HIGH(FLAG_H, cpu.F);
    TEST_ASSERT_BIT_LOW(FLAG_Z, cpu.F);
    TEST_ASSERT_BIT_LOW(FLAG_S, cpu.F);

    // Test 0xFF - 0xFF
    Z80_CPU_Init(&cpu);
    cpu.A = 0xFF;
    sub(&cpu, 0xFF);
    TEST_ASSERT_EQUAL(0, cpu.A);
    TEST_ASSERT_BIT_LOW(FLAG_C, cpu.F);
    TEST_ASSERT_BIT_HIGH(FLAG_N, cpu.F);
    TEST_ASSERT_BIT_LOW(FLAG_PV, cpu.F);
    TEST_ASSERT_BIT_LOW(FLAG_H, cpu.F);
    TEST_ASSERT_BIT_HIGH(FLAG_Z, cpu.F);
    TEST_ASSERT_BIT_LOW(FLAG_S, cpu.F);
}

void test_z80_logic_and() {
    // TODO
}

void test_z80_logic_or() {
    // TODO
}

void test_z80_logic_xor() {
    // TODO
}

void test_z80_logic_cp() {
    // TODO
}

int main(int argc, char const *argv[])
{
    UNITY_BEGIN();

    // Run tests
    RUN_TEST(test_z80_logic_ld_byte);
    RUN_TEST(test_z80_logic_ld_word);
    RUN_TEST(test_z80_logic_add);
    RUN_TEST(test_z80_logic_sub);
    RUN_TEST(test_z80_logic_and);
    RUN_TEST(test_z80_logic_or);
    RUN_TEST(test_z80_logic_xor);
    RUN_TEST(test_z80_logic_cp);

    return UNITY_END();
}
