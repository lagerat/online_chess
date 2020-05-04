#include "board.h"
#include "board_print.h"
#include <stdio.h>

int main()
{
    int status = board();
    switch (status) {
    case 1:
        printf("undefined error");
        break;
    case 2:
        printf("error during the pawn");
        break;
    case 4:
        printf("wrong pawn capture");
        break;
    case 3:
        printf("A pawn is trying to go on a testice which is occupide be "
               "anither figure");
        break;
    case 5:
        printf("unknow type of move");
        break;
    case 6:
        printf("There is no figure on the testicle that you are trying to "
               "take");
        break;
    case 8:
        printf("out of bounds");
        break;
    case 0:
        printf("All good");
        break;
    }
    return 0;
}
