cmake_minimum_required(VERSION 3.28.0) # This version officially supports C++ modules
# set(CMAKE_CXX_COMPILER "clang++")
project(CXXModules CXX)

# Libc++ has no support compiler extensions for modules.
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(math)
target_sources(math PUBLIC FILE_SET CXX_MODULES FILES math.cppm)
target_compile_features(math PUBLIC cxx_std_20)
set_target_properties(math PROPERTIES CXX_EXTENSIONS OFF)

add_executable(main main.cpp)
target_link_libraries(main PRIVATE math)
