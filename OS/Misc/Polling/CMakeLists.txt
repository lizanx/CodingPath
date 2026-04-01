cmake_minimum_required(VERSION 3.28)
project(program LANGUAGES C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

set(CMAKE_C_COMPILER gcc)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -Wall -W -Wmissing-prototypes -Wno-sign-compare -Wimplicit-fallthrough -Wno-unused-parameter")

file(GLOB_RECURSE SOURCES
    CONFIGURE_DEPENDS
    src/*.c
)

add_executable(${PROJECT_NAME} ${SOURCES})
