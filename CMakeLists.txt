cmake_minimum_required(VERSION 3.16)
project(X_Tetris_first C)

set(CMAKE_C_STANDARD 90)
add_executable(X_Tetris_first main.c tetralib.h)
target_link_libraries(X_Tetris_first PRIVATE m)
