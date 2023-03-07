cmake_minimum_required(VERSION 3.17)
project(os4 C)

set(CMAKE_C_STANDARD 99)

add_executable(os4 main.c)
add_executable(child child.c)