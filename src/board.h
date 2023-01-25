#ifndef TICTAC_BOARD_H
#define TICTAC_BOARD_H

#include <stdbool.h>

#include "ai.h"
#include "window.h"

#define BOARD_DATA {\
{'a', 'b', 'c', 'd'},\
{'e', 'f', 'g', 'h'},\
{'i', 'j', 'k', 'l'},\
{'m', 'n', 'o', 'p'}\
}

enum State {
    Preparing,
    Ingame,
    Ended,
};

enum Player {
    FirstPlayer,
    SecondPlayer,
    ComputerPlayer,
    NonePlayer
};

void board_render();

enum State board_state();
void board_state_set(enum State new);

enum Color board_color();
void board_color_set(enum Color new);

enum Player board_player();
void board_player_switch();
void board_player_set(enum Player new);

char board_character(enum Player target);

bool board_ai();
void board_ai_set(bool state);

char board_cell_name(int row, int col);

bool board_check_win();
bool board_check_draw();

bool board_play(int row, int col);
bool board_play_cell(char cell);
void board_play_ai();

bool _board_cell_captured(char board[4][4], int row, int col);
bool _board_check_win(char board[4][4], enum Player target);
bool _board_check_draw(char board[4][4]);

bool _board_play(char board[4][4], int row, int col, enum Player target);
bool _board_play_cell(char board[4][4], char cell, enum Player target);

#endif //TICTAC_BOARD_H
