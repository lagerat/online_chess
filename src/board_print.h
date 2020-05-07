#ifndef CHESS_BOARD_PRINT_H
#define CHESS_BOARD_PRINT_H

#include "board.h"

typedef struct figure {
    char name;
    int x, y;
    char flag;
    char alive;
} figure;

int boardPrint(char a[][8],int count, char notation[7]);
#endif // CHESS_BOARD_PRINT_H