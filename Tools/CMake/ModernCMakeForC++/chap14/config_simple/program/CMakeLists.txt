cmake_minimum_required(VERSION 3.26.0)
project(SimpleConfigProgram)

include(GNUInstallDirs)

find_package(Calc REQUIRED)
include(CMakePrintHelpers)
cmake_print_properties(TARGETS "Calc::calc"
    PROPERTIES IMPORTED_CONFIGURATIONS INTERFACE_INCLUDE_DIRECTORIES)

add_executable(main main.cpp)
target_link_libraries(main PRIVATE Calc::calc)
