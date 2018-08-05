cmake_minimum_required(VERSION 3.10.2)
project(easy80)

include_directories(include)

set(CMAKE_CXX_STANDARD 17)

add_executable(easy80
        src/z80_registers.c
        src/z80_cpu.c
        src/main.c)
