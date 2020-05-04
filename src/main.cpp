#include "board.h"
#include "board_print.h"
#include <stdio.h>

int main()
{
    int status = board();
    switch (status) {
    case 1:
        printf("undefined error\n");
        break;
    case 2:
        printf("error during the pawn\n");
        break;
    case 4:
        printf("wrong pawn capture\n");
        break;
    case 3:
        printf("A pawn is trying to go on a testice which is occupide be "
               "anither figure\n");
        break;
    case 5:
        printf("unknow type of move\n");
        break;
    case 6:
        printf("There is no figure on the testicle that you are trying to "
               "take\n");
        break;
    case 7:
        printf("attempt to jump over a figure\n");
        break;
    case 8:
        printf("out of bounds\n");
        break;
    case 0:
        printf("All good\n");
        break;
    }
    return 0;
}
