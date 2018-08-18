cmake_minimum_required(VERSION 3.10.2)
project(easy80)

FIND_PACKAGE(PkgConfig REQUIRED)
PKG_CHECK_MODULES(GTK3 REQUIRED gtk+-3.0)

include_directories(include)
include_directories(libs/Unity/src)

INCLUDE_DIRECTORIES(${GTK3_INCLUDE_DIRS})
LINK_DIRECTORIES(${GTK3_LIBRARY_DIRS})

LINK_DIRECTORIES(${GTK3_LIBRARY_DIRS})


set(CMAKE_CXX_STANDARD 17)

add_executable(easy80
        src/bitmath.c
        src/z80_flags.c
        src/z80_logic.c
        src/z80_instructions.c
        src/z80_registers.c
        src/z80_cpu.c
        src/easy80_debugger_app_win.c
        src/easy80_debugger_app.c
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

TARGET_LINK_LIBRARIES(easy80 ${GTK3_LIBRARIES})