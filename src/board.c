#include "board.h"

const char characters[4] = {'X', 'O', 'O', '?'};

char cells[4][4] = BOARD_DATA;
char names[4][4] = BOARD_DATA;

enum Player player;
enum State state;
enum Color color;

bool ai_enabled;

void board_render() {
    window_write(13, 10, "     |     |     |     ");
    window_writef(13, 11, "  %c  |  %c  |  %c  |  %c  ", cells[0][0], cells[0][1], cells[0][2], cells[0][3]);
    window_write(13, 12, "_____|_____|_____|_____");
    window_write(13, 13, "     |     |     |     ");
    window_writef(13, 14, "  %c  |  %c  |  %c  |  %c  ", cells[1][0], cells[1][1], cells[1][2], cells[1][3]);
    window_write(13, 15, "_____|_____|_____|_____");
    window_write(13, 16, "     |     |     |     ");
    window_writef(13, 17, "  %c  |  %c  |  %c  |  %c  ", cells[2][0], cells[2][1], cells[2][2], cells[2][3]);
    window_write(13, 18, "_____|_____|_____|_____");
    window_write(13, 19, "     |     |     |     ");
    window_writef(13, 20,  "  %c  |  %c  |  %c  |  %c  ", cells[3][0], cells[3][1], cells[3][2], cells[3][3]);
    window_write(13, 21, "     |     |     |     ");
}

enum State board_state() {
    return state;
}

void board_state_set(enum State new) {
    state = new;
}

enum Color board_color() {
    return color;
}

void board_color_set(enum Color new) {
    color = new;
}

enum Player board_player() {
    return player;
}

void board_player_switch() {
    player = board_player() == FirstPlayer ?
            (board_ai() ?
                ComputerPlayer :
                SecondPlayer
            ) : FirstPlayer;
}

void board_player_set(enum Player new) {
    player = new;
}

char board_character(enum Player target) {
    return characters[target];
}

bool board_ai() {
    return ai_enabled;
}

void board_ai_set(bool new) {
    ai_enabled = new;
}

char board_cell_name(int row, int col) {
    return names[row][col];
}

bool board_check_win() {
    return _board_check_win(cells, board_player());
}
bool board_check_draw() {
    return _board_check_draw(cells);
}

bool board_play(int row, int col) {
    return _board_play(cells, row, col, board_player());
}

bool board_play_cell(char cell) {
    return _board_play_cell(cells, cell, board_player());
}

void board_play_ai() {
    ai_play(cells);
}

bool _board_cell_captured(char board[4][4], int row, int col) {
    return board[row][col] != names[row][col];
}

bool _board_check_win(char board[4][4], enum Player target) {
    char sign = board_character(target);

    for (int i = 0; i < 4; i++) {
        if (board[i][0] == sign && board[i][1] == sign && board[i][2] == sign && board[i][3] == sign) {
            return true;
        }
    }

    for (int j = 0; j < 4; j++) {
        if (board[0][j] == sign && board[1][j] == sign && board[2][j] == sign && board[3][j] == sign) {
            return true;
        }
    }

    if (board[0][0] == sign && board[1][1] == sign && board[2][2] == sign && board[3][3] == sign) {
        return true;
    }
    if (board[3][0] == sign && board[2][1] == sign && board[1][2] == sign && board[0][3] == sign) {
        return true;
    }

    return false;
}

bool _board_check_draw(char board[4][4]) {
    for (int x = 0; x < 4; x++) {
        for (int y = 0; y < 4; y++) {
            if (!_board_cell_captured(board, x, y)) return false;
        }
    }
    return true;
}

bool _board_play(char board[4][4], int row, int col, enum Player target) {
    if (_board_cell_captured(board, row, col)) return false;
    board[row][col] = board_character(target);
    return true;
}

bool _board_play_cell(char board[4][4], char cell, enum Player target) {
    int row, col = -1;

    for (int x = 0; x < 4; x++) {
        for (int y = 0; y < 4; y++) {
            if (names[x][y] == cell) {
                row = x;
                col = y;
                break;
            }
        }
    }

    if (col == -1) return false;
    return _board_play(board, row, col, target);
}
