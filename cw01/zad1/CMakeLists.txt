cmake_minimum_required(VERSION 3.24)
project(zad1 C)

set(CMAKE_C_STANDARD 17)

add_library(library.h)

add_executable(zad1
        main.c)

find_library(/home/endrew/Github/Operating_systems/cw01/zad1/library.h)


