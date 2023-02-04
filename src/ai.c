#include "ai.h"
#include "board.h"

void ai_play(char cells[4][4]) {
    int best_value = -1000;
    int row = -1;
    int col = -1;

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (_board_cell_captured(cells, i, j)) continue;

            cells[i][j] = board_character(SecondPlayer);
            int move_value = ai_minimax(cells, 0, -1000, 1000, false);
            cells[i][j] = board_cell_name(i, j);

            if (move_value > best_value) {
                row = i;
                col = j;
                best_value = move_value;
            }
        }
    }

    board_play(row, col);
}

int ai_minimax(char cells[4][4], int depth, int alpha, int beta, bool isMax) {
    bool result1 = _board_check_win(cells, FirstPlayer);
    bool result2 = _board_check_win(cells, SecondPlayer);

    if (result1) return depth-10;
    if (result2) return depth+10;

    if (depth == 5) return 0;
    if (_board_check_draw(cells)) return 0;

    if (isMax) {
        int best = -1000;

        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                if (_board_cell_captured(cells, i, j)) continue;

                cells[i][j] = board_character(SecondPlayer);
                best = max(best, ai_minimax(cells, depth+1, alpha, beta, !isMax));
                cells[i][j] = board_cell_name(i, j);
                alpha = max(alpha, best);
                if (beta <= alpha) break;
            }
        }
        return best;
    } else {
        int best = 1000;

        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                if (_board_cell_captured(cells, i, j)) continue;

                cells[i][j] = board_character(FirstPlayer);
                best = min(best, ai_minimax(cells, depth+1, alpha, beta, !isMax));
                cells[i][j] = board_cell_name(i, j);
                beta = min(beta, best);
                if (beta <= alpha) break;
            }
        }
        return best;
    }
}
