cmake_minimum_required(VERSION 3.19)
project(chessSFMLboard)

set(CMAKE_CXX_STANDARD 14)

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)

add_executable(chessSFMLboard src/main.cpp src/board.cpp src/board.h src/figure.cpp src/figure.h)

target_link_libraries(chessSFMLboard sfml-graphics sfml-audio)

