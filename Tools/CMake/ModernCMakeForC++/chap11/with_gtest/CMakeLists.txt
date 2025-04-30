cmake_minimum_required(VERSION 3.28.0)
project(WithGoogleTest CXX)

include(CTest)
add_subdirectory(src bin)
add_subdirectory(test)
