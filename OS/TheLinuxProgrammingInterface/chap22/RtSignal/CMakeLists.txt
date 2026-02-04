cmake_minimum_required(VERSION 3.28)
project(program LANGUAGES C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

set(CMAKE_C_COMPILER gcc)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -Wall -W -Wmissing-prototypes -Wno-sign-compare -Wimplicit-fallthrough -Wno-unused-parameter")

add_executable(catch_rtsigs src/catch_rtsigs.c)
add_executable(t_sigqueue src/t_sigqueue.c)

# Include dir
target_include_directories(catch_rtsigs PRIVATE "${CMAKE_SOURCE_DIR}/../../include")
target_include_directories(t_sigqueue PRIVATE "${CMAKE_SOURCE_DIR}/../../include")

# Libs
target_link_libraries(catch_rtsigs PRIVATE "${CMAKE_SOURCE_DIR}/../../lib/libtlpi.a")
target_link_libraries(t_sigqueue PRIVATE "${CMAKE_SOURCE_DIR}/../../lib/libtlpi.a")
