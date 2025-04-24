cmake_minimum_required(VERSION 3.20.0)
project(ForbidInSrcBuild)

if(PROJECT_SOURCE_DIR STREQUAL PROJECT_BINARY_DIR)
    message(FATAL_ERROR "Src dir and build dir cannot be the same!")
else()
    message("Src dir: ${PROJECT_SOURCE_DIR}")
    message("Build dir: ${PROJECT_BINARY_DIR}")
endif()

add_executable(ForbidInSrcBuild main.cpp)
