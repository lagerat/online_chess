#include "board.h"
#include <stdio.h>
#include <string.h>

int boardPrint(char a[][8], int count,char notation[7])
{
    FILE* boardField;
    if (count == 0) {
        if ((boardField = fopen("..//bin//board.txt", "w")) == NULL) {
            printf("Cannot create file.\n");
            return 1;
        }
        int numbers = 8;
        fputs(notation,boardField);
        fprintf(boardField, "\n");
        for (int i = 0; i < 8; ++i) {
            fprintf(boardField, "%d", numbers--);
            for (int j = 0; j < 8; ++j) {
                fprintf(boardField, " %c", a[i][j]);
            }
            fprintf(boardField, "\n");
        }
        fputs("  A B C D E F G H", boardField);
        fprintf(boardField, "\n\n");

    } else if ((boardField = fopen("..//bin//board.txt", "at")) != NULL) {
        fputs(notation,boardField);
        fprintf(boardField, "\n");
        int numbers = 8;
        for (int i = 0; i < 8; ++i) {
            fprintf(boardField, "%d", numbers--);
            for (int j = 0; j < 8; ++j) {
                fprintf(boardField, " %c", a[i][j]);
            }
            fprintf(boardField, "\n");
        }
        fputs("  A B C D E F G H", boardField);
        fprintf(boardField, "\n\n");
    }


    fclose(boardField);
    return 0;
}