#include <time.h>
#include "window.h"

void window_init() {
    initscr();
    cbreak();
    noecho();

    start_color();

    init_pair(1, COLOR_GREEN, COLOR_BLACK);
    init_pair(2, COLOR_CYAN, COLOR_BLACK);
    init_pair(3, COLOR_RED, COLOR_BLACK);
    init_pair(4, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(5, COLOR_YELLOW, COLOR_BLACK);
    init_pair(6, COLOR_WHITE, COLOR_BLACK);
}

void window_writef(short x, short y, char* format, ...) {
    char buffer[128];
    window_move(x, y);
    va_list args;
    va_start(args, format);
    vsprintf(buffer, format, args);
    va_end(args);
    printw("%s", buffer);
    window_move(0, 0);
}

void window_write(short x, short y, char* message) {
    window_move(x, y);
    printw("%s", message);
    window_move(0, 0);
}

void window_color(enum Color color) {
    attron(COLOR_PAIR(color + 1));
}

void window_move(short x, short y) {
    move(y, x);
}

void window_draw_border() {
    border('#', '#', '#', '#','#', '#', '#', '#');
}

void window_clear() {
    clear();
    resize_term(30, 50);
}

char window_char() {
    return (char) getch();
}
