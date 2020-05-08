#define CTEST_MAIN

#include <stdio.h>
#include <ctest.h>
#include "../src/board.h"

CTEST(suite1, testDefenitions)
{
    int ans = defenitionX('a');
    ASSERT_EQUAL(0, ans);
}

int main(int argc, const char* argv[])
{
    return ctest_main(argc, argv);
}
