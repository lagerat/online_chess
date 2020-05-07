#include "board.h"
#include "board_print.h"
#include <stdio.h>

int main()
{
    int status = board();
    switch (status) {
    case 1:
        printf("undefined error\n");
        return 1;
    case 2:
        printf("error during the pawn\n");
        return 2;
    case 4:
        printf("wrong pawn capture\n");
        return 4;
    case 3:
        printf("A pawn is trying to go on a testice which is occupide be "
               "anither figure\n");
        return 3;
    case 5:
        printf("unknow type of move\n");
        return 5;
    case 6:
        printf("There is no figure on the testicle that you are trying to "
               "take\n");
        return 6;
    case 7:
        printf("attempt to jump over a figure\n");
        return 7;
    case 8:
        printf("out of bounds\n");
        return 8;
    case 9:
        printf("unknow type of figure\n");
        return 9;
    case 10:
        printf("wrong king Move");
        return 10;
    case 11:
        printf("Figure is trying to go to a cell that is occupide by another figure");
        return 11;
    case 12:
        printf("On the indicated cell is not the figure that you indicated");
        return 12;
    case 13:
        printf("Knight is trying to go a cell that is occipide by another figure");
        return 13;
    case 14:
        printf("wrong knight move");
        return 14;
    case 15:
        printf("wrong bishop move");
        return 15;
    case 0:
        printf("All good\n");
        break;
    }
    return 0;
}
