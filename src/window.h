#ifndef TICTAC_WINDOW_H
#define TICTAC_WINDOW_H

#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>

enum Color {
    Green,
    Blue,
    Red,
    Purple,
    Yellow,
    White
};

void window_init();
void window_writef(short x, short y, char* format, ...);
void window_write(short x, short y, char* message);
void window_color(enum Color color);
void window_move(short x, short y);
void window_draw_border();
void window_clear();
char window_char();

#endif //TICTAC_WINDOW_H
