#ifndef CHESS_BOARD_PRINT_H
#define CHESS_BOARD_PRINT_H

#endif // CHESS_BOARD_PRINT_H
#include "board.h"

typedef struct figure {
    char name;
    int x, y;
    char flag;
} figure;


int boardPrint(char a[][8]);