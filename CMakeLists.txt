cmake_minimum_required(VERSION 3.26)
project(2MP3Assignment C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(2MP3Assignment
        functions.c
        functions.h
        GA.c
        OF.c)
