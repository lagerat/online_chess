#include "board.h"
#include "board_print.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int status;
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
        return 10;
    }
    char board[8][8];
    int p = 0;
    status = 0;
    char str[20] = "\0";
    int countFile = 0;
    char notan[7] = "\0";
    while (feof(notation) == 0) {
        fgets(str, 19, notation);
        p = 0;
        if ((str[p] == 'K') || (str[p] == 'Q') || (str[p] == 'R')
            || (str[p] == 'N') || (str[p] == 'B') || (str[p] == 'k')
            || (str[p] == 'q') || (str[p] == 'r') || (str[p] == 'n')) {
            figureType(str, white, black, p);
            if (status != 0)
                return status;
        } else {
            status = WPawnMoves(str, white, black);
            if (status != 0)
                return status;
        }
        for (int i = 0; str[i] != ' '; ++i) {
            notan[i] = str[i];
        }
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
        if (boardPrint(board, countFile++, notan) == 1)
            return 10;
        p = 0;
        while (str[p] != ' ')
            p++;
        p++;
        if ((str[p] == 'K') || (str[p] == 'Q') || (str[p] == 'R')
            || (str[p] == 'N') || (str[p] == 'B') || (str[p] == 'k')
            || (str[p] == 'q') || (str[p] == 'r') || (str[p] == 'n')
            || (str[p] == 'b')) {
            figureType(str, white, black, p);
            if (status != 0)
                return status;
        } else {
            status = BPawnMoves(str, white, black, p);
            if (status != 0)
                return status;
        }
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
        int counter = 0;
        for (int i = p; (str[i] != '\n') && (str[i] != '\0'); ++i) {
            notan[counter++] = str[i];
        }
        notan[counter] = '\0';
        if (boardPrint(board, countFile++, notan) == 1)
            return 10;
    }
    return 0;
}

int QueenMove(char str[20], figure* white, figure* black, int p)
{
    p++;
    char symbol = str[p++];
    int x = defenitionX(symbol);
    symbol = str[p++];
    int y = defenitionY(symbol);
    symbol = str[p++];
    if (symbol == '-') {
        symbol = str[p++];
        int xNew = defenitionX(symbol);
        symbol = str[p++];
        int yNew = defenitionY(symbol);
        if (x == 8 || y == 8 || xNew == 8 || yNew == 8) {
            status = 8;
            return 8;
        }
        if ((abs((y - yNew)) == abs((x - xNew))) || (x == xNew && y != yNew)
            || (y == yNew && x != xNew)) {
            int c = 100;
            for (int i = 0; i < 16; ++i) {
                if (p < 7) {
                    if (white[i].x == x && white[i].y == y
                        && white[i].alive == 1) {
                        c = i;
                    }
                    if ((white[i].x == xNew && white[i].y == yNew
                         && white[i].alive == 1)
                        || (black[i].x == xNew && black[i].y == yNew)) {
                        status = 11;
                        return 11;
                    }
                } else if (p >= 7) {
                    if (black[i].x == x && black[i].y == y
                        && black[i].alive == 1) {
                        c = i;
                    }
                    if ((white[i].x == xNew && white[i].y == yNew
                         && white[i].alive == 1)
                        || (black[i].x == xNew && black[i].y == yNew
                            && black[i].alive == 1)) {
                        status = 11;
                        return 11;
                    }
                }
            }
            if (c == 100) {
                status = 6;
                return 6;
            }
            if (x == xNew && y > yNew) {
                for (int yCheck = y - 1; yCheck > yNew; yCheck--) {
                    for (int j = 0; j < 16; ++j) {
                        if ((black[j].x == x && black[j].y == yCheck
                             && black[j].alive == 1)
                            || (white[j].x == x && white[j].y == yCheck
                                && white[j].alive == 1)) {
                            status = 7;
                            return 7;
                        }
                    }
                }
            }
            if (x == xNew && y < yNew) {
                for (int yCheck = y + 1; yCheck < yNew; yCheck++) {
                    for (int j = 0; j < 16; ++j) {
                        if ((black[j].x == x && black[j].y == yCheck
                             && black[j].alive == 1)
                            || (white[j].x == x && white[j].y == yCheck
                                && white[j].alive == 1)) {
                            status = 7;
                            return 7;
                        }
                    }
                }
            }
            if (y == yNew && x > xNew) {
                for (int xCheck = x - 1; xCheck > xNew; xCheck--) {
                    for (int j = 0; j < 16; ++j) {
                        if ((black[j].x == xCheck && black[j].y == y
                             && black[j].alive == 1)
                            || (white[j].x == xCheck && white[j].y == y
                                && white[j].alive == 1)) {
                            status = 7;
                            return 7;
                        }
                    }
                }
            }
            if (y == yNew && x < xNew) {
                for (int xCheck = x + 1; xCheck < xNew; xCheck++) {
                    for (int j = 0; j < 16; ++j) {
                        if ((black[j].x == xCheck && black[j].y == y
                             && black[j].alive == 1)
                            || (white[j].x == xCheck && white[j].y == y
                                && white[j].alive == 1)) {
                            status = 7;
                            return 7;
                        }
                    }
                }
            }
            if ((xNew - x > 0) && (y - yNew > 0)) {
                int xCheck = x + 1;
                for (int yCheck = y - 1; yCheck > yNew; yCheck--) {
                    for (int j = 0; j < 16; ++j) {
                        if ((black[j].x == xCheck && black[j].y == yCheck
                             && black[j].alive == 1)
                            || (white[j].x == xCheck && white[j].y == yCheck
                                && white[j].alive == 1)) {
                            status = 7;
                            return 7;
                        }
                    }
                    xCheck++;
                }
            }
            if ((xNew - x < 0) && (y - yNew < 0)) {
                int xCheck = x - 1;
                for (int yCheck = y + 1; yCheck < yNew; yCheck++) {
                    for (int j = 0; j < 16; ++j) {
                        if ((black[j].x == xCheck && black[j].y == yCheck
                             && black[j].alive == 1)
                            || (white[j].x == xCheck && white[j].y == yCheck
                                && white[j].alive == 1)) {
                            status = 7;
                            return 7;
                        }
                    }
                    xCheck--;
                }
            }
            if ((xNew - x < 0) && (y - yNew > 0)) {
                int yCheck = y - 1;
                for (int xCheck = x - 1; xCheck > xNew; xCheck--) {
                    for (int j = 0; j < 16; ++j) {
                        if ((black[j].x == xCheck && black[j].y == yCheck
                             && black[j].alive == 1)
                            || (white[j].x == xCheck && white[j].y == yCheck
                                && white[j].alive == 1)) {
                            status = 7;
                            return 7;
                        }
                    }
                    yCheck--;
                }
            }

            if ((xNew - x > 0) && (y - yNew < 0)) {
                int yCheck = y + 1;
                for (int xCheck = x + 1; xCheck < xNew; xCheck++) {
                    for (int j = 0; j < 16; ++j) {
                        if ((black[j].x == xCheck && black[j].y == yCheck
                             && black[j].alive == 1)
                            || (white[j].x == xCheck && white[j].y == yCheck
                                && white[j].alive == 1)) {
                            status = 7;
                            return 7;
                        }
                    }
                    yCheck++;
                }
            }
            if (p < 7) {
                if (white[c].name != 'Q' && white[c].name != 'q') {
                    status = 12;
                    return 12;
                }
                white[c].y = yNew;
                white[c].x = xNew;
            } else if (p >= 7) {
                if (black[c].name != 'Q' && black[c].name != 'q') {
                    status = 12;
                    return 12;
                }
                black[c].y = yNew;
                black[c].x = xNew;
            }
        } else {
            status = 13;
            return 13;
        }
    } else if (symbol == 'x') {
        symbol = str[p++];
        int xNew = defenitionX(symbol);
        symbol = str[p++];
        int yNew = defenitionY(symbol);
        if ((abs((y - yNew)) == abs((x - xNew))) || (x == xNew && y != yNew)
            || (y == yNew && x != xNew)) {
            int c = 100, o = 100;
            for (int i = 0; i < 16; ++i) {
                if (p < 7) {
                    if (white[i].x == x && white[i].y == y
                        && white[i].alive == 1) {
                        c = i;
                    }
                    if (white[i].x == xNew && white[i].y == yNew
                        && white[i].alive == 1) {
                        status = 14;
                        return 14;
                    }
                    if (black[i].x == xNew && black[i].y == yNew
                        && black[i].alive == 1) {
                        o = i;
                    }
                } else if (p >= 7) {
                    if (black[i].x == x && black[i].y == y
                        && black[i].alive == 1) {
                        c = i;
                    }
                    if (white[i].x == xNew && white[i].y == yNew
                        && white[i].alive == 1) {
                        o = i;
                    }
                    if (black[i].x == xNew && black[i].y == yNew
                        && black[i].alive == 1) {
                        status = 14;
                        return 14;
                    }
                }
            }
            if (c == 100 || o == 100) {
                status = 6;
                return 6;
            }
            if (x == xNew && y > yNew) {
                for (int yCheck = y - 1; yCheck > yNew; yCheck--) {
                    for (int j = 0; j < 16; ++j) {
                        if ((black[j].x == x && black[j].y == yCheck
                             && black[j].alive == 1)
                            || (white[j].x == x && white[j].y == yCheck
                                && white[j].alive == 1)) {
                            status = 7;
                            return 7;
                        }
                    }
                }
            } else if (x == xNew && y < yNew) {
                for (int yCheck = y + 1; yCheck < yNew; yCheck++) {
                    for (int j = 0; j < 16; ++j) {
                        if ((black[j].x == x && black[j].y == yCheck
                             && black[j].alive == 1)
                            || (white[j].x == x && white[j].y == yCheck
                                && white[j].alive == 1)) {
                            status = 7;
                            return 7;
                        }
                    }
                }
            } else if (y == yNew && x > xNew) {
                for (int xCheck = x - 1; xCheck > xNew; xCheck--) {
                    for (int j = 0; j < 16; ++j) {
                        if ((black[j].x == xCheck && black[j].y == y
                             && black[j].alive == 1)
                            || (white[j].x == xCheck && white[j].y == y
                                && white[j].alive == 1)) {
                            status = 7;
                            return 7;
                        }
                    }
                }
            } else if (y == yNew && x < xNew) {
                for (int xCheck = x + 1; xCheck < xNew; xCheck++) {
                    for (int j = 0; j < 16; ++j) {
                        if ((black[j].x == xCheck && black[j].y == y
                             && black[j].alive == 1)
                            || (white[j].x == xCheck && white[j].y == y
                                && white[j].alive == 1)) {
                            status = 7;
                            return 7;
                        }
                    }
                }
            } else if ((xNew - x > 0) && (y - yNew > 0)) {
                int xCheck = x + 1;
                for (int yCheck = y - 1; yCheck > yNew; yCheck--) {
                    for (int j = 0; j < 16; ++j) {
                        if ((black[j].x == xCheck && black[j].y == yCheck
                             && black[j].alive == 1)
                            || (white[j].x == xCheck && white[j].y == yCheck
                                && white[j].alive == 1)) {
                            status = 7;
                            return 7;
                        }
                    }
                    xCheck++;
                }
            } else if ((xNew - x < 0) && (y - yNew < 0)) {
                int xCheck = x - 1;
                for (int yCheck = y + 1; yCheck < yNew; yCheck++) {
                    for (int j = 0; j < 16; ++j) {
                        if ((black[j].x == xCheck && black[j].y == yCheck
                             && black[j].alive == 1)
                            || (white[j].x == xCheck && white[j].y == yCheck
                                && white[j].alive == 1)) {
                            status = 7;
                            return 7;
                        }
                    }
                    xCheck--;
                }
            } else if ((xNew - x < 0) && (y - yNew > 0)) {
                int yCheck = y - 1;
                for (int xCheck = x - 1; xCheck > xNew; xCheck--) {
                    for (int j = 0; j < 16; ++j) {
                        if ((black[j].x == xCheck && black[j].y == yCheck
                             && black[j].alive == 1)
                            || (white[j].x == xCheck && white[j].y == yCheck
                                && white[j].alive == 1)) {
                            status = 7;
                            return 7;
                        }
                    }
                    yCheck--;
                }
            } else if ((xNew - x > 0) && (y - yNew < 0)) {
                int yCheck = y + 1;
                for (int xCheck = x + 1; xCheck < xNew; xCheck++) {
                    for (int j = 0; j < 16; ++j) {
                        if ((black[j].x == xCheck && black[j].y == yCheck
                             && black[j].alive == 1)
                            || (white[j].x == xCheck && white[j].y == yCheck
                                && white[j].alive == 1)) {
                            status = 7;
                            return 7;
                        }
                    }
                    yCheck++;
                }
            }
            if (p < 7) {
                if (white[c].name != 'Q' && white[c].name != 'q') {
                    status = 12;
                    return 12;
                }
                white[c].y = yNew;
                white[c].x = xNew;
                black[o].alive = 0;
            } else if (p >= 7) {
                if (black[c].name != 'Q' && black[c].name != 'q') {
                    status = 12;
                    return 12;
                }
                black[c].y = yNew;
                black[c].x = xNew;
                white[c].alive = 0;
            }
        } else {
            status = 13;
            return 13;
        }
    } else {
        status = 5;
        return 5;
    }
    return 0;
}

int BishopMove(char str[20], figure* white, figure* black, int p)
{
    p++;
    char symbol = str[p++];
    int x = defenitionX(symbol);
    symbol = str[p++];
    int y = defenitionY(symbol);
    symbol = str[p++];
    if (symbol == '-') {
        symbol = str[p++];
        int xNew = defenitionX(symbol);
        symbol = str[p++];
        int yNew = defenitionY(symbol);
        if (x == 8 || y == 8 || xNew == 8 || yNew == 8) {
            status = 8;
            return 8;
        }
        if (abs((y - yNew)) == abs((x - xNew))) {
            int c = 100;
            for (int i = 0; i < 16; ++i) {
                if (p < 7) {
                    if (white[i].x == x && white[i].y == y
                        && white[i].alive == 1) {
                        c = i;
                    }
                    if ((white[i].x == xNew && white[i].y == yNew
                         && white[i].alive == 1)
                        || (black[i].x == xNew && black[i].y == yNew)) {
                        status = 11;
                        return 11;
                    }
                } else if (p >= 7) {
                    if (black[i].x == x && black[i].y == y
                        && black[i].alive == 1) {
                        c = i;
                    }
                    if ((white[i].x == xNew && white[i].y == yNew
                         && white[i].alive == 1)
                        || (black[i].x == xNew && black[i].y == yNew
                            && black[i].alive == 1)) {
                        status = 11;
                        return 11;
                    }
                }
            }
            if (c == 100) {
                status = 6;
                return 6;
            }
            if ((xNew - x > 0) && (y - yNew > 0)) {
                int xCheck = x + 1;
                for (int yCheck = y - 1; yCheck > yNew; yCheck--) {
                    for (int j = 0; j < 16; ++j) {
                        if ((black[j].x == xCheck && black[j].y == yCheck
                             && black[j].alive == 1)
                            || (white[j].x == xCheck && white[j].y == yCheck
                                && white[j].alive == 1)) {
                            status = 7;
                            return 7;
                        }
                    }
                    xCheck++;
                }
            }
            if ((xNew - x < 0) && (y - yNew < 0)) {
                int xCheck = x - 1;
                for (int yCheck = y + 1; yCheck < yNew; yCheck++) {
                    for (int j = 0; j < 16; ++j) {
                        if ((black[j].x == xCheck && black[j].y == yCheck
                             && black[j].alive == 1)
                            || (white[j].x == xCheck && white[j].y == yCheck
                                && white[j].alive == 1)) {
                            status = 7;
                            return 7;
                        }
                    }
                    xCheck--;
                }
            }
            if ((xNew - x < 0) && (y - yNew > 0)) {
                int yCheck = y - 1;
                for (int xCheck = x - 1; xCheck > xNew; xCheck--) {
                    for (int j = 0; j < 16; ++j) {
                        if ((black[j].x == xCheck && black[j].y == yCheck
                             && black[j].alive == 1)
                            || (white[j].x == xCheck && white[j].y == yCheck
                                && white[j].alive == 1)) {
                            status = 7;
                            return 7;
                        }
                    }
                    yCheck--;
                }
            }

            if ((xNew - x > 0) && (y - yNew < 0)) {
                int yCheck = y + 1;
                for (int xCheck = x + 1; xCheck < xNew; xCheck++) {
                    for (int j = 0; j < 16; ++j) {
                        if ((black[j].x == xCheck && black[j].y == yCheck
                             && black[j].alive == 1)
                            || (white[j].x == xCheck && white[j].y == yCheck
                                && white[j].alive == 1)) {
                            status = 7;
                            return 7;
                        }
                    }
                    yCheck++;
                }
            }
            if (p < 7) {
                if (white[c].name != 'B' && white[c].name != 'b') {
                    status = 12;
                    return 12;
                }
                white[c].y = yNew;
                white[c].x = xNew;
            } else if (p >= 7) {
                if (black[c].name != 'B' && black[c].name != 'b') {
                    status = 12;
                    return 12;
                }
                black[c].y = yNew;
                black[c].x = xNew;
            }
        } else {
            status = 13;
            return 13;
        }
    } else if (symbol == 'x') {
        symbol = str[p++];
        int xNew = defenitionX(symbol);
        symbol = str[p++];
        int yNew = defenitionY(symbol);
        if (abs((y - yNew)) == abs((x - xNew))) {
            int c = 100, o = 100;
            for (int i = 0; i < 16; ++i) {
                if (p < 7) {
                    if (white[i].x == x && white[i].y == y
                        && white[i].alive == 1) {
                        c = i;
                    }
                    if (white[i].x == xNew && white[i].y == yNew
                        && white[i].alive == 1) {
                        status = 11;
                        return 11;
                    }
                    if (black[i].x == xNew && black[i].y == yNew
                        && black[i].alive == 1) {
                        o = i;
                    }
                } else if (p >= 7) {
                    if (black[i].x == x && black[i].y == y
                        && black[i].alive == 1) {
                        c = i;
                    }
                    if (white[i].x == xNew && white[i].y == yNew
                        && white[i].alive == 1) {
                        o = i;
                    }
                    if (black[i].x == xNew && black[i].y == yNew
                        && black[i].alive == 1) {
                        status = 11;
                        return 11;
                    }
                }
            }
            if (c == 100 || o == 100) {
                status = 6;
                return 6;
            }
            if ((xNew - x > 0) && (y - yNew > 0)) {
                int xCheck = x + 1;
                for (int yCheck = y - 1; yCheck > yNew; yCheck--) {
                    for (int j = 0; j < 16; ++j) {
                        if ((black[j].x == xCheck && black[j].y == yCheck
                             && black[j].alive == 1)
                            || (white[j].x == xCheck && white[j].y == yCheck
                                && white[j].alive == 1)) {
                            status = 7;
                            return 7;
                        }
                    }
                    xCheck++;
                }
            }
            if ((xNew - x < 0) && (y - yNew < 0)) {
                int xCheck = x - 1;
                for (int yCheck = y + 1; yCheck < yNew; yCheck++) {
                    for (int j = 0; j < 16; ++j) {
                        if ((black[j].x == xCheck && black[j].y == yCheck
                             && black[j].alive == 1)
                            || (white[j].x == xCheck && white[j].y == yCheck
                                && white[j].alive == 1)) {
                            status = 7;
                            return 7;
                        }
                    }
                    xCheck--;
                }
            }
            if ((xNew - x < 0) && (y - yNew > 0)) {
                int yCheck = y - 1;
                for (int xCheck = x - 1; xCheck > xNew; xCheck--) {
                    for (int j = 0; j < 16; ++j) {
                        if ((black[j].x == xCheck && black[j].y == yCheck
                             && black[j].alive == 1)
                            || (white[j].x == xCheck && white[j].y == yCheck
                                && white[j].alive == 1)) {
                            status = 7;
                            return 7;
                        }
                    }
                    yCheck--;
                }
            }

            if ((xNew - x > 0) && (y - yNew > 0)) {
                int yCheck = y + 1;
                for (int xCheck = x + 1; xCheck < xNew; xCheck++) {
                    for (int j = 0; j < 16; ++j) {
                        if ((black[j].x == xCheck && black[j].y == yCheck
                             && black[j].alive == 1)
                            || (white[j].x == xCheck && white[j].y == yCheck
                                && white[j].alive == 1)) {
                            status = 7;
                            return 7;
                        }
                    }
                    yCheck++;
                }
            }
            if (p < 7) {
                if (white[c].name != 'B' && white[c].name != 'b') {
                    status = 12;
                    return 12;
                }
                white[c].y = yNew;
                white[c].x = xNew;
                black[o].alive = 0;
            } else if (p >= 7) {
                if (black[c].name != 'B' && black[c].name != 'b') {
                    status = 12;
                    return 12;
                }
                black[c].y = yNew;
                black[c].x = xNew;
                white[c].alive = 0;
            }
        } else {
            status = 13;
            return 13;
        }
    } else {
        status = 5;
        return 5;
    }
    return 0;
}

int RookMove(char str[20], figure* white, figure* black, int p)
{
    p++;
    char symbol = str[p++];
    int x = defenitionX(symbol);
    symbol = str[p++];
    int y = defenitionY(symbol);
    symbol = str[p++];
    if (symbol == '-') {
        symbol = str[p++];
        int xNew = defenitionX(symbol);
        symbol = str[p++];
        int yNew = defenitionY(symbol);
        if (x == 8 || y == 8 || xNew == 8 || yNew == 8) {
            status = 8;
            return 8;
        }
        if ((x == xNew && y != yNew) || (y == yNew && x != xNew)) {
            int c = 100;
            for (int i = 0; i < 16; ++i) {
                if (p < 7) {
                    if (white[i].x == x && white[i].y == y
                        && white[i].alive == 1) {
                        c = i;
                    }
                    if ((white[i].x == xNew && white[i].y == yNew
                         && white[i].alive == 1)
                        || (black[i].x == xNew && black[i].y == yNew)) {
                        status = 11;
                        return 11;
                    }
                } else if (p >= 7) {
                    if (black[i].x == x && black[i].y == y
                        && black[i].alive == 1) {
                        c = i;
                    }
                    if ((white[i].x == xNew && white[i].y == yNew
                         && white[i].alive == 1)
                        || (black[i].x == xNew && black[i].y == yNew
                            && black[i].alive == 1)) {
                        status = 11;
                        return 11;
                    }
                }
            }
            if (c == 100) {
                status = 6;
                return 6;
            }
            if (x == xNew && y > yNew) {
                for (int yCheck = y - 1; yCheck > yNew; yCheck--) {
                    for (int j = 0; j < 16; ++j) {
                        if ((black[j].x == x && black[j].y == yCheck
                             && black[j].alive == 1)
                            || (white[j].x == x && white[j].y == yCheck
                                && white[j].alive == 1)) {
                            status = 7;
                            return 7;
                        }
                    }
                }
            }
            if (x == xNew && y < yNew) {
                for (int yCheck = y + 1; yCheck < yNew; yCheck++) {
                    for (int j = 0; j < 16; ++j) {
                        if ((black[j].x == x && black[j].y == yCheck
                             && black[j].alive == 1)
                            || (white[j].x == x && white[j].y == yCheck
                                && white[j].alive == 1)) {
                            status = 7;
                            return 7;
                        }
                    }
                }
            }
            if (y == yNew && x > xNew) {
                for (int xCheck = x - 1; xCheck > xNew; xCheck--) {
                    for (int j = 0; j < 16; ++j) {
                        if ((black[j].x == xCheck && black[j].y == y
                             && black[j].alive == 1)
                            || (white[j].x == xCheck && white[j].y == y
                                && white[j].alive == 1)) {
                            status = 7;
                            return 7;
                        }
                    }
                }
            }
            if (y == yNew && x < xNew) {
                for (int xCheck = x + 1; xCheck < xNew; xCheck++) {
                    for (int j = 0; j < 16; ++j) {
                        if ((black[j].x == xCheck && black[j].y == y
                             && black[j].alive == 1)
                            || (white[j].x == xCheck && white[j].y == y
                                && white[j].alive == 1)) {
                            status = 7;
                            return 7;
                        }
                    }
                }
            }
            if (p < 7) {
                if (white[c].name != 'R' && white[c].name != 'r') {
                    status = 12;
                    return 12;
                }
                white[c].y = yNew;
                white[c].x = xNew;
            } else if (p >= 7) {
                if (black[c].name != 'R' && black[c].name != 'r') {
                    status = 12;
                    return 12;
                }
                black[c].y = yNew;
                black[c].x = xNew;
            }
        } else {
            status = 13;
            return 13;
        }
    } else if (symbol == 'x') {
        symbol = str[p++];
        int xNew = defenitionX(symbol);
        symbol = str[p++];
        int yNew = defenitionY(symbol);
        if ((x == xNew && y != yNew) || (y = yNew && x != xNew)) {
            int c = 100, o = 100;
            for (int i = 0; i < 16; ++i) {
                if (p < 7) {
                    if (white[i].x == x && white[i].y == y
                        && white[i].alive == 1) {
                        c = i;
                    }
                    if (white[i].x == xNew && white[i].y == yNew
                        && white[i].alive == 1) {
                        status = 11;
                        return 11;
                    }
                    if (black[i].x == xNew && black[i].y == yNew
                        && black[i].alive == 1) {
                        o = i;
                    }
                } else if (p >= 7) {
                    if (black[i].x == x && black[i].y == y
                        && black[i].alive == 1) {
                        c = i;
                    }
                    if (white[i].x == xNew && white[i].y == yNew
                        && white[i].alive == 1) {
                        o = i;
                    }
                    if (black[i].x == xNew && black[i].y == yNew
                        && black[i].alive == 1) {
                        status = 11;
                        return 11;
                    }
                }
            }
            if (x == xNew && y > yNew) {
                for (int yCheck = y - 1; yCheck > yNew + 1; yCheck--) {
                    for (int j = 0; j < 16; ++j) {
                        if ((black[j].x == x && black[j].y == yCheck
                             && black[j].alive == 1)
                            || (white[j].x == x && white[j].y == yCheck
                                && white[j].alive == 1)) {
                            status = 7;
                            return 7;
                        }
                    }
                }
            }
            if (x == xNew && y < yNew) {
                for (int yCheck = y + 1; yCheck < yNew - 1; yCheck++) {
                    for (int j = 0; j < 16; ++j) {
                        if ((black[j].x == x && black[j].y == yCheck
                             && black[j].alive == 1)
                            || (white[j].x == x && white[j].y == yCheck
                                && white[j].alive == 1)) {
                            status = 7;
                            return 7;
                        }
                    }
                }
            }
            if (y == yNew && x > xNew) {
                for (int xCheck = x - 1; xCheck > xNew + 1; xCheck--) {
                    for (int j = 0; j < 16; ++j) {
                        if ((black[j].x == xCheck && black[j].y == y
                             && black[j].alive == 1)
                            || (white[j].x == xCheck && white[j].y == y
                                && white[j].alive == 1)) {
                            status = 7;
                            return 7;
                        }
                    }
                }
            }
            if (y == yNew && x < xNew) {
                for (int xCheck = x + 1; xCheck < xNew - 1; xCheck++) {
                    for (int j = 0; j < 16; ++j) {
                        if ((black[j].x == xCheck && black[j].y == y
                             && black[j].alive == 1)
                            || (white[j].x == xCheck && white[j].y == y
                                && white[j].alive == 1)) {
                            status = 7;
                            return 7;
                        }
                    }
                }
            }
            if (c == 100 || o == 100) {
                status = 6;
                return 6;
            }
            if (p < 7) {
                if (white[c].name != 'R' && white[c].name != 'r') {
                    status = 12;
                    return 12;
                }
                white[c].y = yNew;
                white[c].x = xNew;
                black[o].alive = 0;
            } else if (p >= 7) {
                if (black[c].name != 'R' && black[c].name != 'r') {
                    status = 12;
                    return 12;
                }
                black[c].y = yNew;
                black[c].x = xNew;
                white[c].alive = 0;
            }
        } else {
            status = 13;
            return 13;
        }
    } else {
        status = 5;
        return 5;
    }
    return 0;
}

int kNightMove(char str[20], figure* white, figure* black, int p)
{
    p++;
    char symbol = str[p++];
    int x = defenitionX(symbol);
    symbol = str[p++];
    int y = defenitionY(symbol);
    symbol = str[p++];
    if (symbol == '-') {
        symbol = str[p++];
        int xNew = defenitionX(symbol);
        symbol = str[p++];
        int yNew = defenitionY(symbol);
        if (x == 8 || y == 8 || xNew == 8 || yNew == 8) {
            status = 8;
            return 8;
        }
        if (((xNew - x == 1) && (y - yNew == 2))
            || ((x - xNew == 1) && (y - yNew == 2))
            || ((x - xNew == 2) && (y - yNew == 1))
            || ((xNew - x == 2) && (y - yNew == 1))
            || ((xNew - x == 2) && (yNew - y == 1))
            || ((x - xNew == 2) && (yNew - y == 1))
            || ((x - xNew == 1) && (yNew - y == 2))
            || ((xNew - x == 1) && (yNew - y == 2))) {
            int c = 100;
            for (int i = 0; i < 16; ++i) {
                if (p < 7) {
                    if (white[i].x == x && white[i].y == y
                        && white[i].alive == 1) {
                        c = i;
                    }
                    if ((white[i].x == xNew && white[i].y == yNew
                         && white[i].alive == 1)
                        || (black[i].x == xNew && black[i].y == yNew
                            && black[i].alive == 1)) {
                        status = 11;
                        return 11;
                    }
                } else if (p >= 7) {
                    if (black[i].x == x && black[i].y == y) {
                        c = i;
                    }
                    if ((white[i].x == xNew && white[i].y == yNew
                         && white[i].alive == 1)
                        || (black[i].x == xNew && black[i].y == yNew
                            && white[i].alive == 1)) {
                        status = 11;
                        return 11;
                    }
                }
            }
            if (c == 100) {
                status = 6;
                return 6;
            }
            if (p < 7) {
                if (white[c].name != 'N' && white[c].name != 'n') {
                    status = 12;
                    return 12;
                }
                white[c].y = yNew;
                white[c].x = xNew;
            } else if (p >= 7) {
                if (black[c].name != 'N' && black[c].name != 'n') {
                    status = 12;
                    return 12;
                }
                black[c].y = yNew;
                black[c].x = xNew;
            }
        } else {
            status = 13;
            return 13;
        }

    } else if (symbol == 'x') {
        symbol = str[p++];
        int xNew = defenitionX(symbol);
        symbol = str[p++];
        int yNew = defenitionY(symbol);
        if (x == 8 || y == 8 || xNew == 8 || yNew == 8) {
            status = 8;
            return 8;
        }
        if (((xNew - x == 1) && (y - yNew == 2))
            || ((x - xNew == 1) && (y - yNew == 2))
            || ((x - xNew == 2) && (y - yNew == 1))
            || ((xNew - x == 2) && (y - yNew == 1))
            || ((xNew - x == 2) && (yNew - y == 1))
            || ((x - xNew == 2) && (yNew - y == 1))
            || ((x - xNew == 1) && (yNew - y == 2))
            || ((xNew - x == 1) && (yNew - y == 2))) {
            int c = 100, o = 100;
            for (int i = 0; i < 16; ++i) {
                if (p < 7) {
                    if (white[i].x == x && white[i].y == y
                        && white[i].alive == 1) {
                        c = i;
                    }
                    if (white[i].x == xNew && white[i].y == yNew
                        && white[i].alive == 1) {
                        status = 14;
                        return 14;
                    }
                    if (black[i].x == xNew && black[i].y == yNew
                        && black[i].alive == 1) {
                        o = i;
                    }
                } else if (p >= 7) {
                    if (black[i].x == x && black[i].y == y
                        && black[i].alive == 1) {
                        c = i;
                    }
                    if (white[i].x == xNew && white[i].y == yNew
                        && white[i].alive == 1) {
                        o = i;
                    }
                    if (black[i].x == xNew && black[i].y == yNew
                        && black[i].alive == 1) {
                        status = 14;
                        return 14;
                    }
                }
            }
            if (c == 100 || o == 100) {
                status = 6;
                return 6;
            }
            if (p < 7) {
                if (white[c].name != 'N' && white[c].name != 'n') {
                    status = 12;
                    return 12;
                }
                white[c].y = yNew;
                white[c].x = xNew;
                black[o].alive = 0;
            } else if (p >= 7) {
                if (black[c].name != 'N' && black[c].name != 'n') {
                    status = 12;
                    return 12;
                }
                black[c].y = yNew;
                black[c].x = xNew;
                white[c].alive = 0;
            }
        } else {
            status = 13;
            return 13;
        }
    } else {
        status = 5;
        return 5;
    }
    return 0;
}

int KingMove(char str[20], figure* white, figure* black, int p)
{
    p++;
    char symbol = str[p++];
    int x = defenitionX(symbol);
    symbol = str[p++];
    int y = defenitionY(symbol);
    symbol = str[p++];
    if (symbol == '-') {
        symbol = str[p++];
        int xNew = defenitionX(symbol);
        symbol = str[p++];
        int yNew = defenitionY(symbol);
        if (x == 8 || y == 8 || xNew == 8 || yNew == 8) {
            status = 8;
            return 8;
        }
        if (((x - xNew == 1) && (y - yNew == 1))
            || ((yNew - y == 0) && (x - xNew == 1))
            || ((x - xNew == 1) && (yNew - y == 1))
            || ((x - xNew == 0) && (yNew - y == 1))
            || ((xNew - x == 1) && (yNew - y == 1))
            || ((xNew - x == 1) && (y - yNew == 0))
            || ((xNew - x == 1) && (y - yNew == 1))
            || ((x - xNew == 0) && (y - yNew == 1))) {
            int c = 100;
            for (int i = 0; i < 16; ++i) {
                if (p < 7) {
                    if (white[i].x == x && white[i].y == y
                        && white[i].alive == 1) {
                        c = i;
                    }
                    if ((white[i].x == xNew && white[i].y == yNew
                         && white[i].alive == 1)
                        || (black[i].x == xNew && black[i].y == yNew
                            && black[i].alive == 1)) {
                        status = 11;
                        return 11;
                    }
                } else if (p >= 7) {
                    if (black[i].x == x && black[i].y == y) {
                        c = i;
                    }
                    if ((white[i].x == xNew && white[i].y == yNew
                         && white[i].alive == 1)
                        || (black[i].x == xNew && black[i].y == yNew
                            && black[i].alive == 1)) {
                        status = 11;
                        return 11;
                    }
                }
            }
            if (c == 100) {
                status = 6;
                return 6;
            }
            if (p < 7) {
                if (white[c].name != 'k' && white[c].name != 'K') {
                    status = 12;
                    return 12;
                }
                white[c].y = yNew;
                white[c].x = xNew;
            } else if (p >= 7) {
                if (black[c].name != 'k' && black[c].name != 'K') {
                    status = 12;
                    return 12;
                }
                black[c].y = yNew;
                black[c].x = xNew;
            }
        } else {
            status = 13;
            return 13;
        }
    } else if (symbol == 'x') {
        symbol = str[p++];
        int xNew = defenitionX(symbol);
        symbol = str[p++];
        int yNew = defenitionY(symbol);
        if (((x - xNew == 1) && (y - yNew == 1))
            || ((yNew - y == 0) && (x - xNew == 1))
            || ((x - xNew == 1) && (yNew - y == 1))
            || ((x - xNew == 0) && (yNew - y == 1))
            || ((xNew - x == 1) && (yNew - y == 1))
            || ((xNew - x == 1) && (y - yNew == 0))
            || ((xNew - x == 1) && (y - yNew == 1))
            || ((x - xNew == 0) && (y - yNew == 1))) {
            int c = 100, o = 100;
            for (int i = 0; i < 16; ++i) {
                if (p < 7) {
                    if (white[i].x == x && white[i].y == y
                        && white[i].alive == 1) {
                        c = i;
                    }
                    if (white[i].x == xNew && white[i].y == yNew
                        && white[i].alive == 1) {
                        status = 14;
                        return 14;
                    }
                    if (black[i].x == xNew && black[i].y == yNew
                        && black[i].alive == 1) {
                        o = i;
                    }
                } else if (p >= 7) {
                    if (black[i].x == x && black[i].y == y
                        && black[i].alive == 1) {
                        c = i;
                    }
                    if (white[i].x == xNew && white[i].y == yNew
                        && white[i].alive == 1) {
                        o = i;
                    }
                    if (black[i].x == xNew && black[i].y == yNew
                        && black[i].alive == 1) {
                        status = 14;
                        return 14;
                    }
                }
            }
            if (c == 100 || o == 100) {
                status = 6;
                return 6;
            }
            if (p < 7) {
                if (white[c].name != 'k' && white[c].name != 'K') {
                    status = 12;
                    return 12;
                }
                white[c].y = yNew;
                white[c].x = xNew;
                black[o].alive = 0;
            } else if (p >= 7) {
                if (black[c].name != 'k' && black[c].name != 'K') {
                    status = 12;
                    return 12;
                }
                black[c].y = yNew;
                black[c].x = xNew;
                white[c].alive = 0;
            }
        } else {
            status = 13;
            return 13;
        }
    } else {
        status = 5;
        return 5;
    }
    return 0;
}

int figureType(char str[20], figure* white, figure* black, int p)
{
    switch (str[p]) {
    case 'K':
    case 'k':
        KingMove(str, white, black, p);
        break;
    case 'N':
    case 'n':
        kNightMove(str, white, black, p);
        break;
    case 'r':
    case 'R':
        RookMove(str, white, black, p);
        break;
    case 'B':
        BishopMove(str, white, black, p);
        break;
    case 'q':
    case 'Q':
        QueenMove(str, white, black, p);
        break;
    default:
        return 9;
    }
    return 0;
}

int WPawnMoves(char str[20], figure* white, figure* black)
{
    int k = 0;
    char symbol = str[k++];
    int x, y;
    x = defenitionX(symbol);
    symbol = str[k++];
    y = defenitionY(symbol);
    symbol = str[k++];
    int xNew, yNew;
    if (symbol == '-') {
        symbol = str[k++];
        xNew = defenitionX(symbol);
        symbol = str[k++];
        yNew = defenitionY(symbol);
        if (xNew == 8 || yNew == 8 || y == 8 || x == 8)
            return 8;
        int c = 100;
        for (int i = 0; i < 16; ++i) {
            if (white[i].x == x && white[i].y == y && white[i].alive == 1)
                c = i;
            if ((black[i].x == xNew && black[i].y == yNew
                 && black[i].alive == 1)
                || (white[i].x == xNew && white[i].y == yNew
                    && white[i].alive == 1))
                return 3;
        }
        if (c == 100)
            return 6;
        if ((x - xNew != 0) || ((white[c].flag != 0) && (y - yNew > 1))
            || (y - yNew > 2))
            return 2;
        if (y - yNew == 2) {
            int between = y - 1;
            for (int i = 0; i < 16; ++i) {
                if (white[i].x == x && white[i].y == between
                    && white[i].alive == 1)
                    return 7;
                if (black[i].x == x && black[i].y == between
                    && black[i].alive == 1)
                    return 7;
            }
        }
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
            if (white[i].x == x && white[i].y == y && white[i].alive == 1)
                c = i;
            if (white[i].x == xNew && white[i].y == yNew && white[i].alive == 1)
                return 3;
            if ((black[i].x == xNew && black[i].y == yNew
                 && black[i].alive == 1))
                p = i;
        }
        if (p == 100 || c == 100)
            return 6;
        white[c].x = xNew;
        white[c].y = yNew;
        white[c].flag = 1;
        black[p].alive = 0;
    } else
        return 5;
    return 0;
}

int BPawnMoves(char str[20], figure* white, figure* black, int p)
{
    char symbol = str[p++];
    int x, y;
    x = defenitionX(symbol);
    symbol = str[p++];
    y = defenitionY(symbol);
    symbol = str[p++];
    int xNew, yNew;
    if (symbol == '-') {
        symbol = str[p++];
        xNew = defenitionX(symbol);
        symbol = str[p++];
        yNew = defenitionY(symbol);
        if (xNew == 8 || yNew == 8 || y == 8 || x == 8)
            return 8;
        int c = 100;
        for (int i = 0; i < 16; ++i) {
            if (black[i].x == x && black[i].y == y && black[i].alive == 1)
                c = i;
            if ((white[i].x == xNew && white[i].y == yNew
                 && white[i].alive == 1)
                || (black[i].x == xNew && black[i].y == yNew
                    && black[i].alive == 1))
                return 3;
        }
        if (c == 100)
            return 6;
        if ((x - xNew != 0) || ((black[c].flag != 0) && (yNew - y > 1))
            || (yNew - y > 2))
            return 2;
        if (yNew - y == 2) {
            int between = yNew - 1;
            for (int i = 0; i < 16; ++i) {
                if (white[i].x == x && white[i].y == between
                    && white[i].alive == 1)
                    return 7;
                if (black[i].x == x && black[i].y == between
                    && black[i].alive == 1)
                    return 7;
            }
        }
        if (((yNew - y == 2) && (black[c].flag == 0)) || (yNew - y == 1)) {
            black[c].flag = 1;
            black[c].y = yNew;
            black[c].x = xNew;
        }

    } else if (str[p - 1] == 'x') {
        symbol = str[p++];
        xNew = defenitionX(symbol);
        symbol = str[p++];
        yNew = defenitionY(symbol);
        int c = 100, l = 100;
        if ((abs(x - xNew) != 1) || (yNew - y != 1))
            return 4;
        for (int i = 0; i < 16; ++i) {
            if (black[i].x == x && black[i].y == y && black[i].alive == 1)
                c = i;
            if (black[i].x == xNew && black[i].y == yNew && black[i].alive == 1)
                return 3;
            if ((white[i].x == xNew && white[i].y == yNew
                 && white[i].alive == 1))
                l = i;
        }
        if (l == 100 || c == 100)
            return 6;
        black[c].x = xNew;
        black[c].y = yNew;
        black[c].flag = 1;
        white[l].alive = 0;
    } else
        return 5;
    return 0;
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