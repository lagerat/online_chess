cmake_minimum_required(VERSION 3.19)
project(chessviz)

set(CMAKE_CXX_STANDARD 14)

add_executable(chessviz src/main.c src/board.c src/board_print.c src/board.h src/board_print.h )
