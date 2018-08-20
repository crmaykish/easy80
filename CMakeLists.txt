cmake_minimum_required(VERSION 3.10.2)
project(easy80)

include_directories(include)
include_directories(include/instructions)
include_directories(include/utils)
include_directories(libs/Unity/src)

set(CMAKE_CXX_STANDARD 17)

add_executable(easy80
        src/instructions/z80_instructions_common.c
        src/instructions/z80_instructions_main.c
        src/instructions/z80_instructions_extended.c
        src/instructions/z80_instructions_bit.c
        src/instructions/z80_instructions_ix.c
        src/instructions/z80_instructions_iy.c
        src/utils/bitmath.c
        src/utils/flags.c
        src/z80_registers.c
        src/z80_cpu.c
        src/main.c
)