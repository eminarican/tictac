#include "main.h"

int main() {
    board_state_set(Preparing);
    board_color_set(Yellow);
    window_init();

    window_clear();

    while (true) {
        window_color(board_color());
        window_clear();

        window_draw_border();

        switch(board_state()) {
            case Preparing:
                preparing();
                break;
            case Ingame:
                ingame();
                break;
            case Ended:
                ended();
                exit(0);
        }
    }
}

void preparing() {
    window_write(9, 9, "welcome to the tic tac toe game");
    window_write(9, 10, "set your setting and press enter");

    if(board_ai()) {
        window_write(9, 12, "selected game mode: pvc");
    } else {
        window_write(9, 12, "selected game mode: pvp");
    }

    window_write(9, 14, "1: play with using ai");
    window_write(9, 15, "2: play without using ai");

    window_write(9, 17, "a: change color to yellow");
    window_write(9, 18, "b: change color to green");
    window_write(9, 19, "c: change color to blue");

    window_write(9, 21, "(press a button above or enter)");

    switch(window_char()) {
        case '1':
            board_ai_set(true);
            break;
        case '2':
            board_ai_set(false);
            break;
        case 'a':
            board_color_set(Yellow);
            break;
        case 'b':
            board_color_set(Green);
            break;
        case 'c':
            board_color_set(Blue);
            break;
        case '\n':
            board_state_set(Ingame);
            break;
        case 27:
            exit(0);
    }
}

void ingame() {
    window_write(22, 6, "X O X");

    if (board_ai()) {
        window_write(11, 8, "Player 1 (X) - Computer (O)");
    } else {
        window_write(11, 8, "Player 1 (X) - Player 2 (O)");
    }

    board_render();

    switch(board_player()) {
        case FirstPlayer:
            window_write(13, 23, "Player 1 select a cell");
            while (!board_play_cell(window_char()));
            break;
        case SecondPlayer:
            window_write(13, 23, "Player 2 select a cell");
            while (!board_play_cell(window_char()));
            break;
        case ComputerPlayer:
            window_write(12, 23, "Computer selecting a cell");
            board_play_ai();
            break;
        case NonePlayer:
            board_state_set(Ended);
            board_color_set(Purple);
            return;
    }

    if (board_check_win()) {
        board_state_set(Ended);
        board_color_set(Purple);
    } else if(board_check_draw()) {
        board_player_set(NonePlayer);
        board_color_set(Purple);
        board_state_set(Ended);
    } else {
        board_player_switch();
    }
}

void ended() {
    switch(board_player()) {
        case FirstPlayer:
            window_write(13, 23, "!Player 1 won the game!");
            break;
        case SecondPlayer:
            window_write(13, 23, "!Player 2 won the game!");
            break;
        case ComputerPlayer:
            window_write(13, 23, "!Computer won the game!");
            break;
        case NonePlayer:
            window_write(14, 23, "!No one won the game!");
            break;
    }

    window_char();
}
