cmake_minimum_required(VERSION 3.19)
project(online_chess)

set(CMAKE_CXX_STANDARD 17)

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)

add_executable(online_chess src/main.cpp src/board.cpp src/board.h src/figure.cpp src/figure.h)

target_link_libraries(online_chess sfml-graphics sfml-audio)

