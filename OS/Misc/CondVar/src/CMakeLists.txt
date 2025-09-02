cmake_minimum_required(VERSION 3.28)

project(PosixConditionalVariable)

add_executable(program main.c)

target_compile_options(program PRIVATE -pthread)
