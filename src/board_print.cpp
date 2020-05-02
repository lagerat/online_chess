#include "board_print.h"
#include "board.h"
#include <stdio.h>
#include <string.h>

int boardPrint(char a[][8])
{
    FILE* boardField;
    if ((boardField = fopen("..//bin//board.txt", "w")) == NULL) {
        printf("Cannot create file.\n");
        return 1;
    }
    for (int i = 0; i < 8; ++i) {
        fprintf(boardField, "%d", i + 1);
        for (int j = 0; j < 8; ++j) {
            fprintf(boardField," %c",a[i][j]);
        }
        fprintf(boardField, "\n");
    }
    fputs("  A B C D E F G H", boardField);

    fclose(boardField);
}