cmake_minimum_required(VERSION 3.20.0)
project(try_run)

try_run(
    RunResultVar
    CompileResultVar
    ${CMAKE_CURRENT_LIST_DIR}/build
    ${CMAKE_CURRENT_LIST_DIR}/main.cpp
    RUN_OUTPUT_VARIABLE RunOutputVar
)

message("Run result: ${RunResultVar}")
message("Compile result: ${CompileResultVar}")
message("Program std output: ${RunOutputVar}")
