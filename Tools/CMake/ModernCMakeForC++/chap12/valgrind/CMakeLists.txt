cmake_minimum_required(VERSION 3.28.0)
project(Valgrind CXX)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/cmake)

include(CTest)
add_subdirectory(src bin)
add_subdirectory(test)
