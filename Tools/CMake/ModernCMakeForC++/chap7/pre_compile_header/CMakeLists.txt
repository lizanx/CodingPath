cmake_minimum_required(VERSION 3.20.0)
project(PrecompileHeader)

add_executable(PrecompileHeader main.cpp)
target_precompile_headers(PrecompileHeader PRIVATE <iostream>)
