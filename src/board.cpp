#include "board.h"
#include "board_print.h"

typedef struct figure {
    char name[2];
    int x,y;
    char flag;
} figure;
