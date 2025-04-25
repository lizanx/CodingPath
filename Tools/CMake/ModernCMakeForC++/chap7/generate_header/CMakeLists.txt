cmake_minimum_required(VERSION 3.20.0)
project(GenerateHeader)

add_executable(GenerateHeader main.cpp)

# Defined variables used for header generation
set(DEF_VAR_1 ON)
set(DEF_VAR_2 "Hello, world")
set(DEF_VAR_3 "CMake is very powerful")
# set(DEF_VAR_4 "...")

# Use config file to generate header.
configure_file(configure.hpp.in generated_header/configure.hpp)
target_include_directories(GenerateHeader PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/generated_header)
