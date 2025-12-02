cmake_minimum_required(VERSION 3.28)
project(TryFcntl LANGUAGES C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

set(CMAKE_C_COMPILER gcc)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -Wall -W -Wmissing-prototypes -Wno-sign-compare -Wimplicit-fallthrough -Wno-unused-parameter")

file(GLOB_RECURSE SOURCES
    CONFIGURE_DEPENDS
    src/*.c
)

add_executable(${PROJECT_NAME} ${SOURCES})

# Include dir
target_include_directories(${PROJECT_NAME} PRIVATE "${CMAKE_SOURCE_DIR}/../../include")

# Libs
target_link_libraries(${PROJECT_NAME} PRIVATE "${CMAKE_SOURCE_DIR}/../../lib/libtlpi.a")
