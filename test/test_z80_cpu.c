#include <stdio.h>
#include "unity.h"
#include "z80_cpu.h"

void test_z80_cpu_init() {
    Z80_CPU cpu;
    Z80_CPU_Init(&cpu);

    TEST_ASSERT_EQUAL(0, cpu.PC);
    TEST_ASSERT_EQUAL(0, cpu.A);
    TEST_ASSERT_EQUAL(STOPPED, cpu.State);
    
    TEST_ASSERT_EQUAL(0, cpu.Memory[0]);
    TEST_ASSERT_EQUAL(0, cpu.Memory[MAX_RAM_ADDRESS]);
    TEST_ASSERT_EQUAL(0, cpu.Memory[MAX_RAM_ADDRESS / 2]);
}

void test_z80_set_memory() {
    Z80_CPU cpu;
    Z80_CPU_Init(&cpu);
    
    uint8_t data[] = {0xAB, 0xBC, 0xDE, 0xFF};

    Z80_CPU_SetMemory(&cpu, data, 4, 0xFF);

    TEST_ASSERT_EQUAL(0xAB, cpu.Memory[0xFF]);
    TEST_ASSERT_EQUAL(0xBC, cpu.Memory[0x100]);
    TEST_ASSERT_EQUAL(0xDE, cpu.Memory[0x101]);
    TEST_ASSERT_EQUAL(0xFF, cpu.Memory[0x102]);
}

int main(int argc, char const *argv[])
{
    UNITY_BEGIN();

    // Run tests
    RUN_TEST(test_z80_cpu_init);
    RUN_TEST(test_z80_set_memory);

    return UNITY_END();
}
