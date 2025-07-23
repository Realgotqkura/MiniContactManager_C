cmake_minimum_required(VERSION 3.31)
project(Mini_Contact_Manager C)

set(CMAKE_C_STANDARD 11)

add_executable(Mini_Contact_Manager main.c
        utilities.c
        utilities.h)
