# Easy-80
Emulator for the Z80 CPU

## About
The goal for this project is to create an emulator module of the Z80 CPU core and instruction set.

This project does not aim to emulate a particularly Z80-based computer. Instead, the plan is to create
a reusable module that provides the basic CPU functionality without any other dependencies.

I would like to use this core as a base for future projects involving the Z80, including full computer
emulators and hardware projects.

## Status
Under active development... not yet fully functional

Development plan:
- [x] Model the internal state of the CPU (registers, memory access, etc.)
- [x] Implement some core opcodes to test the speed and accuracy of the model
- [x] Create a test program to load real machine code and debug the emulation
- [x] Implement main instruction set (Intel 8080-compatible instructions)
- [ ] Test main instruction set for accuracy against 8080 software
- [ ] Implement extended instruction set - EXTD, BITS, IX, IY
- [ ] Test extended instruction set for accuracy against real Z80 software (maybe a BASIC rom?)
- [ ] Create hardware interface layer (IN and OUT instructions)
- [ ] Make emulator timing CPU cycle accurate instead of just instruction accurate

## Dependencies
This project has no runtime dependencies. It is a standalone C module intended to be included in other projects with minimal overhead

Note: to run unit tests, the Unity source code is required. See `./tools/libs.sh`

Note: to build Doxygen documentation, `doxygen`, `dot`, and `graphviz` packages must be installed.

## Building and Testing
This project uses CMake (minimum version v3.10.2).

To build the code:

1. Install libraries: `./tools/libs.sh`
2. Build everything: `./tools/build.sh`
3. Run unit tests: `./tools/test.sh`
4. Build documentation: `./tools/docs.sh` (docs available at `easy80/docs/html/index.html`)
5. Clean: `./tools/clean.sh` (deletes build and docs directories)