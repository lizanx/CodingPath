cmake_minimum_required(VERSION 3.26.0)
project(Calculator)

add_library(calc STATIC calc.cpp)
target_include_directories(calc PUBLIC ${CMAKE_CURRENT_LIST_DIR}/include)

add_executable(main main.cpp)
target_link_libraries(main PRIVATE calc)

# Export this project
set(EXPORT_DIR ${CMAKE_CURRENT_BINARY_DIR}/cmake)
export(TARGETS calc
    FILE "${EXPORT_DIR}/Calc.cmake"
    NAMESPACE Calc::)
