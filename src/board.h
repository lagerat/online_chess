#ifndef CHESS_BOARD_H
#define CHESS_BOARD_H

typedef struct figure {
    char name;
    int x, y;
    char flag;
    char alive;
} figure;

int figureType(char str[20], figure* white, figure* black, int p);
int RookMove(char str[20], figure* white, figure* black, int p);
int QueenMove(char str[20], figure* white, figure* black, int p);
int BishopMove(char str[20], figure* white, figure* black, int p);
int KingMove(char str[20], figure* white, figure* black, int p);
int kNightMove(char str[20], figure* white, figure* black, int p);
int WPawnMoves(char str[20], figure* white, figure* black);
int BPawnMoves(char str[20], figure* white, figure* black, int p);
int defenitionX(char symbol);
int defenitionY(char symbol);
int board();

#endif // CHESS_BOARD_H


