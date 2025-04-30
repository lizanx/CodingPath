cmake_minimum_required(VERSION 3.26.0)
project(ClangFormat)

enable_testing()
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/cmake)
add_subdirectory(src bin)
