#include "board.h"
#include "board_print.h"
#include <stdio.h>
#include <stdlib.h>

int WPawnMoves(char str[20], figure* white, figure* black);
int defenitionX(char symbol);
int defenitionY(char symbol);
int board()
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
            black[k].alive = 1;
            black[k].name = namesBlack[count];
            if (count < 8)
                count++;
            k++;
        }
    }
    k = 0, count = 0;
    for (int i = 7; i > 5; i--) {
        for (int j = 0; j < 8; ++j) {
            white[k].y = i;
            white[k].x = j;
            white[k].flag = 0;
            white[k].alive = 1;
            white[k].name = namesWhite[count];
            if (count < 8)
                count++;
            k++;
        }
    }

    FILE* notation;
    if ((notation = fopen("..//bin//notation.txt", "r+")) == NULL) {
        printf("Cannot open notation file.\n");
        return 1;
    }
    char str[20] = "\0";
    while (feof(notation) == 0) {
        fgets(str, 19, notation);
        if ((str[0] == 'K') || (str[0] == 'Q') || (str[0] == 'R')
            || (str[0] == 'N') || (str[0] == 'B') || (str[0] == 'k')
            || (str[0] == 'q') || (str[0] == 'r') || (str[0] == 'n')
            || (str[0] == 'b'))
            printf("figure\n");
        else
            WPawnMoves(str, white, black);
    }
    char board[8][8];
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            board[i][j] = ' ';
        }
    }
    for (int i = 0; i < 16; ++i) {
        if (black[i].alive)
            board[black[i].y][black[i].x] = black[i].name;
        if (white[i].alive)
            board[white[i].y][white[i].x] = white[i].name;
    }
    boardPrint(board);
}

int WPawnMoves(char str[20], figure* white, figure* black)
{
    int k = 0;
    char symbol = str[k++];
    int x, y;
    x = defenitionX(symbol);
    symbol = str[k++];
    y = defenitionY(symbol);
    int xNew, yNew;
    if (str[k++] == '-') {
        symbol = str[k++];
        xNew = defenitionX(symbol);
        symbol = str[k++];
        yNew = defenitionY(symbol);
        int c = 100;
        for (int i = 0; i < 16; ++i) {
            if (white[i].x == x && white[i].y == y)
                c = i;
            if ((black[i].x == xNew && black[i].y == yNew)
                || (white[i].x == xNew && white[i].y == yNew))
                return 3;
        }
        if (c == 100)
            return 6;
        if ((x - xNew != 0) || ((white[c].flag != 0) && (y - yNew > 1)))
            return 1;
        if (((y - yNew == 2) && (white[c].flag == 0)) || (y - yNew == 1)) {
            white[c].flag = 1;
            white[c].y = yNew;
            white[c].x = xNew;
        }

    } else if (str[k - 1] == 'x') {
        symbol = str[k++];
        xNew = defenitionX(symbol);
        symbol = str[k++];
        yNew = defenitionY(symbol);
        int c = 100, p = 100;
        if ((abs(x - xNew) != 1) || (y - yNew != 1))
            return 4;
        for (int i = 0; i < 16; ++i) {
            if (white[i].x == x && white[i].y == y)
                c = i;
            if (white[i].x == xNew && white[i].y == yNew)
                return 3;
            if ((black[i].x == xNew && black[i].y == yNew))
                p = i;
        }
        if (p == 100 || c == 100)
            return 6;
        white[c].x = xNew;
        white[c].y = yNew;
        white[c].flag = 1;
        black[c].alive = 0;
    } else
        return 5;
}

int defenitionX(char symbol)
{
    int x;
    switch (symbol) {
    case 'a':
        x = 0;
        break;
    case 'b':
        x = 1;
        break;
    case 'c':
        x = 2;
        break;
    case 'd':
        x = 3;
        break;
    case 'e':
        x = 4;
        break;
    case 'f':
        x = 5;
        break;
    case 'g':
        x = 6;
        break;
    case 'h':
        x = 7;
        break;
    default:
        return 8;
    }
    return x;
}

int defenitionY(char symbol)
{
    int y;
    switch (symbol) {
    case '1':
        y = 7;
        break;
    case '2':
        y = 6;
        break;
    case '3':
        y = 5;
        break;
    case '4':
        y = 4;
        break;
    case '5':
        y = 3;
        break;
    case '6':
        y = 2;
        break;
    case '7':
        y = 1;
        break;
    case '8':
        y = 0;
        break;
    default:
        return 8;
    }
    return y;
}