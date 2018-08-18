#include <stdio.h>
#include <ncurses.h>
#include "z80_cpu.h"

int main(int argc, char const *argv[])
{
    initscr();
    printw("Z80 Debugger");
    refresh();
    getch();
    endwin();
}
