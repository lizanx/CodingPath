cmake_minimum_required(VERSION 3.20.0)
project(FakeTargets)

add_library(final_lib empty.cpp)

# Alias target
add_library(lib1 empty.cpp)
add_library(lib1_alias ALIAS lib1)
target_link_libraries(final_lib lib1_alias)

# Interface target
add_library(warning_properties INTERFACE)
target_compile_options(warning_properties INTERFACE -Wall -Wextra -Wpedantic)
target_link_libraries(final_lib warning_properties)

# Object target
add_library(lib2 OBJECT empty.cpp)
target_link_libraries(final_lib lib2)
