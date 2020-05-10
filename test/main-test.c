#define CTEST_MAIN

#include "../src/board.h"
#include <ctest.h>
#include <stdio.h>

struct figure white[16];
struct figure black[16];

CTEST(Field, correct_syntax_DefenitionX_check)
{
    int ans = defenitionX('a');
    ASSERT_EQUAL(0, ans);
}

CTEST(Field, Incorrect_syntax_DefenitionX_check)
{
    int ans = defenitionX('z');
    ASSERT_EQUAL(8, ans);
}

CTEST(Field, correct_syntax_DefenitionY_check)
{
    int ans = defenitionY('5');
    ASSERT_EQUAL(3, ans);
}

CTEST(Field, Incorrect_syntax_DefenitionY_check)
{
    int ans = defenitionY('9');
    ASSERT_EQUAL(8, ans);
}

CTEST(pawn, Correct_syntax_White_Pawn_check)
{
    for (int j = 0; j < 16; ++j) {
        black[j].flag = 0;
        black[j].alive = 0;
        white[j].flag = 0;
        white[j].alive = 0;
    }
    white[0].x = 4;
    white[0].y = 4;
    white[0].alive = 1;
    white[0].flag = 0;
    black[0].x = 3;
    black[0].y = 3;
    black[0].alive = 1;
    black[0].flag = 0;
    black[1].x = 5;
    black[1].y = 3;
    black[1].alive = 1;
    black[1].flag = 0;
    white[0].name = 'P';
    int ans = WPawnMoves("e4xd5 f5-f4", white, black);
    ASSERT_EQUAL(0, ans);
}

CTEST(pawn, Correct_syntax_White_Pawn_check2)
{
    for (int j = 0; j < 16; ++j) {
        black[j].flag = 0;
        black[j].alive = 0;
        white[j].flag = 0;
        white[j].alive = 0;
    }
    white[0].x = 4;
    white[0].y = 4;
    white[0].alive = 1;
    white[0].flag = 0;
    black[0].x = 3;
    black[0].y = 3;
    black[0].alive = 1;
    black[0].flag = 0;
    white[0].name = 'P';
    int ans = WPawnMoves("e4-e5 f5-f4", white, black);
    ASSERT_EQUAL(0, ans);
}

CTEST(pawn, Incorrect_syntax_White_Pawn_check)
{
    for (int j = 0; j < 16; ++j) {
        black[j].flag = 0;
        black[j].alive = 0;
        white[j].flag = 0;
        white[j].alive = 0;
    }
    white[0].x = 4;
    white[0].y = 4;
    white[0].alive = 1;
    white[0].flag = 0;
    black[0].x = 3;
    black[0].y = 3;
    black[0].alive = 1;
    black[0].flag = 0;
    white[0].name = 'P';
    int ans = WPawnMoves("e4-e7 f5-f4", white, black);
    ASSERT_EQUAL(2, ans);
}

CTEST(pawn, Correct_syntax_Black_Pawn_check)
{
    for (int j = 0; j < 16; ++j) {
        black[j].flag = 0;
        black[j].alive = 0;
        white[j].flag = 0;
        white[j].alive = 0;
    }
    white[0].x = 4;
    white[0].y = 4;
    white[0].alive = 1;
    white[0].flag = 0;
    black[0].x = 3;
    black[0].y = 3;
    black[0].alive = 1;
    black[0].flag = 0;
    white[0].name = 'P';
    int ans = BPawnMoves("e4-e5 d5-d4", white, black, 6);
    ASSERT_EQUAL(0, ans);
}

CTEST(pawn, Correct_syntax_Black_Pawn_check2)
{
    for (int j = 0; j < 16; ++j) {
        black[j].flag = 0;
        black[j].alive = 0;
        white[j].flag = 0;
        white[j].alive = 0;
    }
    white[0].x = 4;
    white[0].y = 4;
    white[0].alive = 1;
    white[0].flag = 0;
    black[0].x = 3;
    black[0].y = 3;
    black[0].alive = 1;
    black[0].flag = 0;
    white[0].name = 'P';
    int ans = BPawnMoves("e4-e4 d5xe4", white, black, 6);
    ASSERT_EQUAL(0, ans);
}

CTEST(pawn, Incorrect_syntax_Black_Pawn_check)
{
    for (int j = 0; j < 16; ++j) {
        black[j].flag = 0;
        black[j].alive = 0;
        white[j].flag = 0;
        white[j].alive = 0;
    }
    white[0].x = 4;
    white[0].y = 4;
    white[0].alive = 1;
    white[0].flag = 0;
    black[0].x = 3;
    black[0].y = 3;
    black[0].alive = 1;
    black[0].flag = 0;
    white[0].name = 'P';
    int ans = BPawnMoves("e4-e7 d5-d1", white, black, 6);
    ASSERT_EQUAL(2, ans);
}

CTEST(pawn, PresenceFigure)
{
    for (int j = 0; j < 16; ++j) {
        black[j].flag = 0;
        black[j].alive = 0;
        white[j].flag = 0;
        white[j].alive = 0;
    }
    white[0].x = 4;
    white[0].y = 4;
    white[0].alive = 1;
    white[0].flag = 0;
    black[0].x = 3;
    black[0].y = 3;
    black[0].alive = 1;
    black[0].flag = 0;
    white[0].name = 'P';
    int ans = BPawnMoves("e4-e7 f5-f1", white, black, 6);
    ASSERT_EQUAL(6, ans);
}

CTEST(king, Correct_syntax_king_check)
{
    for (int j = 0; j < 16; ++j) {
        black[j].flag = 0;
        black[j].alive = 0;
        white[j].flag = 0;
        white[j].alive = 0;
    }
    white[0].x = 4;
    white[0].y = 4;
    white[0].alive = 1;
    white[0].flag = 0;
    black[0].x = 3;
    black[0].y = 3;
    black[0].alive = 1;
    black[0].flag = 0;
    white[0].name = 'K';
    int ans = KingMove("Ke4xd5 f5-f1", white, black, 0);
    ASSERT_EQUAL(0, ans);
}

CTEST(king, Correct_syntax_king_check2)
{
    for (int j = 0; j < 16; ++j) {
        black[j].flag = 0;
        black[j].alive = 0;
        white[j].flag = 0;
        white[j].alive = 0;
    }
    white[0].x = 4;
    white[0].y = 4;
    white[0].alive = 1;
    white[0].flag = 0;
    black[0].x = 3;
    black[0].y = 3;
    black[0].alive = 1;
    black[0].flag = 0;
    white[0].name = 'K';
    int ans = KingMove("Ke4-e5 f5-f1", white, black, 0);
    ASSERT_EQUAL(0, ans);
}

CTEST(king, Incorrect_syntax_king_check)
{
    for (int j = 0; j < 16; ++j) {
        black[j].flag = 0;
        black[j].alive = 0;
        white[j].flag = 0;
        white[j].alive = 0;
    }
    white[0].x = 4;
    white[0].y = 4;
    white[0].alive = 1;
    white[0].flag = 0;
    black[0].x = 3;
    black[0].y = 3;
    black[0].alive = 1;
    black[0].flag = 0;
    white[0].name = 'K';
    int ans = KingMove("Ke4-a1 f5-f1", white, black, 0);
    ASSERT_EQUAL(13, ans);
}

CTEST(kNight, Correct_syntax_kNight_check)
{
    for (int j = 0; j < 16; ++j) {
        black[j].flag = 0;
        black[j].alive = 0;
        white[j].flag = 0;
        white[j].alive = 0;
    }
    white[0].x = 4;
    white[0].y = 4;
    white[0].alive = 1;
    white[0].flag = 0;
    black[0].x = 2;
    black[0].y = 3;
    black[0].alive = 1;
    black[0].flag = 0;
    white[0].name = 'N';
    int ans = kNightMove("Ne4xc5 f5-f1", white, black, 0);
    ASSERT_EQUAL(0, ans);
}

CTEST(kNight, Correct_syntax_kNight_check2)
{
    for (int j = 0; j < 16; ++j) {
        black[j].flag = 0;
        black[j].alive = 0;
        white[j].flag = 0;
        white[j].alive = 0;
    }
    white[0].x = 4;
    white[0].y = 4;
    white[0].alive = 1;
    white[0].flag = 0;
    black[0].x = 2;
    black[0].y = 3;
    black[0].alive = 1;
    black[0].flag = 0;
    white[0].name = 'N';
    int ans = kNightMove("Ne4-f6 f5-f1", white, black, 0);
    ASSERT_EQUAL(0, ans);
}

CTEST(kNight, Incorrect_syntax_kNight_check)
{
    for (int j = 0; j < 16; ++j) {
        black[j].flag = 0;
        black[j].alive = 0;
        white[j].flag = 0;
        white[j].alive = 0;
    }
    white[0].x = 4;
    white[0].y = 4;
    white[0].alive = 1;
    white[0].flag = 0;
    black[0].x = 2;
    black[0].y = 3;
    black[0].alive = 1;
    black[0].flag = 0;
    white[0].name = 'N';
    int ans = RookMove("Ne4-a1 f5-f1", white, black, 0);
    ASSERT_EQUAL(13, ans);
}

CTEST(Rook, Correct_syntax_Rook_check)
{
    for (int j = 0; j < 16; ++j) {
        black[j].flag = 0;
        black[j].alive = 0;
        white[j].flag = 0;
        white[j].alive = 0;
    }
    white[0].x = 4;
    white[0].y = 4;
    white[0].alive = 1;
    white[0].flag = 0;
    black[0].x = 4;
    black[0].y = 1;
    black[0].alive = 1;
    black[0].flag = 0;
    white[0].name = 'R';
    int ans = RookMove("Re4xe7 f5-f1", white, black, 0);
    ASSERT_EQUAL(0, ans);
}

CTEST(Rook, Correct_syntax_Rook_check2)
{
    for (int j = 0; j < 16; ++j) {
        black[j].flag = 0;
        black[j].alive = 0;
        white[j].flag = 0;
        white[j].alive = 0;
    }
    white[0].x = 4;
    white[0].y = 4;
    white[0].alive = 1;
    white[0].flag = 0;
    black[0].x = 3;
    black[0].y = 1;
    black[0].alive = 1;
    black[0].flag = 0;
    white[0].name = 'R';
    int ans = RookMove("Re4-b4 f5-f1", white, black, 0);
    ASSERT_EQUAL(0, ans);
}

CTEST(Rook, Incorrect_syntax_Rook_check)
{
    for (int j = 0; j < 16; ++j) {
        black[j].flag = 0;
        black[j].alive = 0;
        white[j].flag = 0;
        white[j].alive = 0;
    }
    white[0].x = 4;
    white[0].y = 4;
    white[0].alive = 1;
    white[0].flag = 0;
    black[0].x = 4;
    black[0].y = 1;
    black[0].alive = 1;
    black[0].flag = 0;
    white[0].name = 'R';
    int ans = RookMove("Re4-e8 f5-f1", white, black, 0);
    ASSERT_EQUAL(7, ans);
}

CTEST(Bishop, Correct_syntax_Bishop_check)
{
    for (int j = 0; j < 16; ++j) {
        black[j].flag = 0;
        black[j].alive = 0;
        white[j].flag = 0;
        white[j].alive = 0;
    }
    white[0].x = 4;
    white[0].y = 4;
    white[0].alive = 1;
    white[0].flag = 0;
    black[0].x = 2;
    black[0].y = 6;
    black[0].alive = 1;
    black[0].flag = 0;
    white[0].name = 'B';
    int ans = BishopMove("Be4xc2 f5-f1", white, black, 0);
    ASSERT_EQUAL(0, ans);
}

CTEST(Bishop, Correct_syntax_Bishop_check2)
{
    for (int j = 0; j < 16; ++j) {
        black[j].flag = 0;
        black[j].alive = 0;
        white[j].flag = 0;
        white[j].alive = 0;
    }
    white[0].x = 4;
    white[0].y = 4;
    white[0].alive = 1;
    white[0].flag = 0;
    black[0].x = 2;
    black[0].y = 6;
    black[0].alive = 1;
    black[0].flag = 0;
    white[0].name = 'B';
    int ans = BishopMove("Be4-c6 f5-f1", white, black, 0);
    ASSERT_EQUAL(0, ans);
}

CTEST(Bishop, Incorrect_syntax_Bishop_check)
{
    for (int j = 0; j < 16; ++j) {
        black[j].flag = 0;
        black[j].alive = 0;
        white[j].flag = 0;
        white[j].alive = 0;
    }
    white[0].x = 4;
    white[0].y = 4;
    white[0].alive = 1;
    white[0].flag = 0;
    black[0].x = 3;
    black[0].y = 3;
    black[0].alive = 1;
    black[0].flag = 0;
    white[0].name = 'B';
    int ans = BishopMove("Be4-c6 f5-f1", white, black, 0);
    ASSERT_EQUAL(7, ans);
}

CTEST(Queen, Correct_syntax_Queen_check)
{
    for (int j = 0; j < 16; ++j) {
        black[j].flag = 0;
        black[j].alive = 0;
        white[j].flag = 0;
        white[j].alive = 0;
    }
    white[0].x = 4;
    white[0].y = 4;
    white[0].alive = 1;
    white[0].flag = 0;
    black[0].x = 3;
    black[0].y = 3;
    black[0].alive = 1;
    black[0].flag = 0;
    white[0].name = 'Q';
    int ans = QueenMove("Qe4xd5 f5-f1", white, black, 0);
    ASSERT_EQUAL(0, ans);
}

CTEST(Queen, Correct_syntax_Queen_check2)
{
    for (int j = 0; j < 16; ++j) {
        black[j].flag = 0;
        black[j].alive = 0;
        white[j].flag = 0;
        white[j].alive = 0;
    }
    white[0].x = 4;
    white[0].y = 4;
    white[0].alive = 1;
    white[0].flag = 0;
    black[0].x = 4;
    black[0].y = 2;
    black[0].alive = 1;
    black[0].flag = 0;
    white[0].name = 'Q';
    int ans = QueenMove("Qe4xe6 f5-f1", white, black, 0);
    ASSERT_EQUAL(0, ans);
}

CTEST(Queen, Incorrect_syntax_Queen_check)
{
    for (int j = 0; j < 16; ++j) {
        black[j].flag = 0;
        black[j].alive = 0;
        white[j].flag = 0;
        white[j].alive = 0;
    }
    white[0].x = 4;
    white[0].y = 4;
    white[0].alive = 1;
    white[0].flag = 0;
    black[0].x = 4;
    black[0].y = 2;
    black[0].alive = 1;
    black[0].flag = 0;
    white[0].name = 'Q';
    int ans = QueenMove("Qe4-e7 f5-f1", white, black, 0);
    ASSERT_EQUAL(7, ans);
}

CTEST(Queen, Incorrect_syntax_Queen_check2)
{
    for (int j = 0; j < 16; ++j) {
        black[j].flag = 0;
        black[j].alive = 0;
        white[j].flag = 0;
        white[j].alive = 0;
    }
    white[0].x = 4;
    white[0].y = 4;
    white[0].alive = 1;
    white[0].flag = 0;
    black[0].x = 4;
    black[0].y = 2;
    black[0].alive = 1;
    black[0].flag = 0;
    white[0].name = 'Q';
    int ans = QueenMove("Qe4-c3 f5-f1", white, black, 0);
    ASSERT_EQUAL(13, ans);
}

int main(int argc, const char* argv[])
{
    return ctest_main(argc, argv);
}
