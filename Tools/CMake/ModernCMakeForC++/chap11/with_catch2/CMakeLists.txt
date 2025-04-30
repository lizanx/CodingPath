cmake_minimum_required(VERSION 3.28.0)
project(WithCatch2 CXX)

include(CTest)
add_subdirectory(src bin)
add_subdirectory(test)
