#ifndef TICTAC_AI_H
#define TICTAC_AI_H

#include <stdbool.h>
#include <string.h>

#include "window.h"

void ai_play(char cells[4][4]);
int ai_minimax(char cells[4][4], int depth, int alpha, int beta, bool isMax);

#define max(a,b) (((a) > (b)) ? (a) : (b))
#define min(a,b) (((a) > (b)) ? (b) : (a))

#endif //TICTAC_AI_H
