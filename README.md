# Easy-80
Emulator for the Z80 CPU

## About
The goal for this project is to create an emulator module of the Z80 CPU core and instruction set.

This project does not aim to emulate a particularly Z80-based computer. Instead, the plan is to create
a reusable module that provides the basic CPU functionality without any other dependencies.

I would like to use this core as a base for future projects involving the Z80, including full computer
emulators and hardware projects.

## Status
Pre-development: nothing implemented yet.

Development plan:
- [ ] Model the internal state of the CPU (registers, memory access, etc.)
- [ ] Implement some core opcodes to test the speed and accuracy of the model
- [ ] Add some unit tests to verify CPU functionality
- [ ] Implement remaining opcodes
- [ ] Create a test program to load real machine code and debug the emulation

## Dependencies
This project has no compile-time or runtime dependencies. It is a standalone C++ library.

## Building and Testing
This project uses CMake (minimum version v3.10.2). To build the code, you can run the included bash script: `build.sh`

`run.sh` will start the test app.