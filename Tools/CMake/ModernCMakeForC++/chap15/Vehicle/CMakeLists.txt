cmake_minimum_required(VERSION 3.26.0)
project(Vehicle VERSION 1.3.4 LANGUAGES CXX)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/cmake)

include(NoInSourceBuild)

include(CTest)

add_subdirectory(src bin)
add_subdirectory(test)

include(Packaging)
