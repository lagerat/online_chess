#define CTEST_MAIN

#include "../src/board.h"
#include <ctest.h>
#include <stdio.h>

struct figure white[16];
struct figure black[16];

CTEST(suite1, testDefenitionX1)
{
    int ans = defenitionX('a');
    ASSERT_EQUAL(0, ans);
}

CTEST(suite1, testDefenitionX2)
{
    int ans = defenitionX('z');
    ASSERT_EQUAL(8, ans);
}

CTEST(suite1, testDefenitionY1)
{
    int ans = defenitionY('5');
    ASSERT_EQUAL(3, ans);
}

CTEST(suite1, testDefenitionY2)
{
    int ans = defenitionY('9');
    ASSERT_EQUAL(8, ans);
}

CTEST(suite2, WPawnMove1)
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

CTEST(suite2, WPawnMove2)
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

CTEST(suite2, WPawnMove3)
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

CTEST(suite2, BPawnMove1)
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

CTEST(suite2, BPawnMove2)
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

CTEST(suite2, BPawnMove3)
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
    int ans = WPawnMoves("e4-e7 f5-f1", white, black);
    ASSERT_EQUAL(2, ans);
}

int main(int argc, const char* argv[])
{
    return ctest_main(argc, argv);
}
