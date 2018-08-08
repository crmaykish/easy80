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

    return UNITY_END();
}
