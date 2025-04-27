cmake_minimum_required(VERSION 3.20.0)
project(SharedLibGenerator)

add_executable(SharedLibGenerator main.cpp)
target_link_libraries(SharedLibGenerator SharedLib StaticLib)

add_library(StaticLib STATIC static_lib.cpp)
target_include_directories(StaticLib PUBLIC ${CMAKE_CURRENT_LIST_DIR})

add_library(SharedLib SHARED shared_lib.cpp)
target_include_directories(SharedLib PUBLIC ${CMAKE_CURRENT_LIST_DIR})

file(GENERATE OUTPUT ${CMAKE_BINARY_DIR}/generator_output.txt
    CONTENT "Shared lib so file path: $<TARGET_SONAME_FILE:SharedLib>
    Shared lib so file name: $<TARGET_SONAME_FILE_NAME:SharedLib>
    Shared lib so file dir: $<TARGET_SONAME_FILE_DIR:SharedLib>


    Executable runtime dll file: $<TARGET_RUNTIME_DLLS:SharedLibGenerator>
    Shared lib runtime dll file: $<TARGET_RUNTIME_DLLS:SharedLib>")
