cmake_minimum_required(VERSION 3.26.0)

project(logger_interface
    DESCRIPTION "A logger interface design to demo dependency inversion in C"
    LANGUAGES C)

if (!CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug")
endif()

add_subdirectory(src)
