cmake_minimum_required(VERSION 3.20)
project(tictac)

set(CMAKE_C_STANDARD 11)

add_executable(tictac src/ai.c src/ai.h src/board.c src/board.h src/main.c src/main.h src/window.c src/window.h)

target_link_libraries(tictac ncurses)
