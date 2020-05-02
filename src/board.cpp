#include "board.h"
#include "board_print.h"
#include <stdio.h>



void board()
{
    char namesBlack[] = {'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r', 'p', '\0'};
    char namesWhite[] = {'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R', 'P', '\0'};
    figure white[16];
    figure black[16];
    int count = 0;
    int k = 0;
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 8; ++j) {
            black[k].y = i;
            black[k].x = j;
            black[k].flag = 0;
            black[k].name = namesBlack[count];
            if (count < 8)
                count++;
            k++;
        }
    }
    k = 0,count = 0;
    for (int i = 7; i > 5; i--) {
        for (int j = 0; j < 8; ++j) {
            white[k].y = i;
            white[k].x = j;
            white[k].flag = 0;
            white[k].name = namesWhite[count];
            if (count < 8)
                count++;
            k++;
        }
    }
    char board[8][8];
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            board[i][j] = ' ';
        }
    }
    for (int i = 0; i < 16; ++i) {
        board[black[i].y][black[i].x] = black[i].name;
        board[white[i].y][white[i].x] = white[i].name;
    }
    boardPrint(board);

}