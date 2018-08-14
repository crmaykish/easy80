cmake_minimum_required(VERSION 3.10.2)
project(easy80)

include_directories(include)
include_directories(libs/Unity/src)

set(CMAKE_CXX_STANDARD 17)

add_executable(easy80
        src/bitmath.c
        src/z80_flags.c
        src/z80_logic.c
        src/z80_instructions.c
        src/z80_registers.c
        src/z80_cpu.c
        src/main.c
)

add_executable(test_bitmath
        test/test_bitmath.c
        src/bitmath.c
        libs/Unity/src/unity.c
)

add_executable(test_z80_flags
        test/test_z80_flags.c
        src/z80_flags.c
        src/bitmath.c
        libs/Unity/src/unity.c
)

add_executable(test_z80_cpu
        test/test_z80_cpu.c
        src/z80_cpu.c
        src/z80_instructions.c
        src/z80_logic.c
        src/z80_flags.c
        src/z80_registers.c
        src/bitmath.c
        libs/Unity/src/unity.c
)

add_executable(test_z80_logic
        test/test_z80_logic.c
        src/z80_cpu.c
        src/z80_instructions.c
        src/z80_logic.c
        src/z80_flags.c
        src/z80_registers.c
        src/bitmath.c
        libs/Unity/src/unity.c
)