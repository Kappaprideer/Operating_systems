cmake_minimum_required(VERSION 3.24)
project(zad2 C)

set(CMAKE_C_STANDARD 17)

add_executable(zad2
        main.c
        ../zad1/library.h
        ../zad1/library.c)
