cmake_minimum_required(VERSION 3.20.0)
project(StaticLibDependencyResolve)

# Lib1 depends on Lib2(you must link Lib1 before Lib2, otherwise there'll be missing symbols)
add_library(StaticLib1 STATIC static_lib_1.cpp)
add_library(StaticLib2 STATIC static_lib_2.cpp)

add_executable(StaticLibDependencyResolve main.cpp)
# target_link_libraries(StaticLibDependencyResolve StaticLib1 StaticLib2) # OK
target_link_libraries(StaticLibDependencyResolve StaticLib2 StaticLib1) # Fail
