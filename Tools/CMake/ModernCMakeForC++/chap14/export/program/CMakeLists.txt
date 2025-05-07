cmake_minimum_required(VERSION 3.26.0)
project(MainProgram)

add_executable(main main.cpp)

set(CALC_CMAKE_MODULE "../calculator/build/cmake/Calc.cmake")
include(${CALC_CMAKE_MODULE})
target_link_libraries(main PRIVATE Calc::calc)

include(CMakePrintHelpers)
cmake_print_properties(TARGETS "Calc::calc"
    PROPERTIES IMPORTED_CONFIGURATIONS INTERFACE_INCLUDE_DIRECTORIES)
