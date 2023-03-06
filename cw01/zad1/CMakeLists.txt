cmake_minimum_required(VERSION 3.24)
project(zad1 C)

set(CMAKE_C_STANDARD 17)

add_executable(zad1
        library.c
        zad1lib.c
        zad1lib.h
        main.c)
