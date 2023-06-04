cmake_minimum_required(VERSION 3.24)
project(GET_NEXT_LINE C)

set(CMAKE_C_STANDARD 11)

add_executable(GET_NEXT_LINE main.c get_next_line.c get_next_line.h get_next_line_utils.c get_next_line_utils.c)
