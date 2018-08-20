# generate a struct array for Z80_Instructions
for i in range(0, 256):
    print("{{ 0x{:0>2X}, \"\",          OP_NONE,    0,      &NOP }},".format(i))