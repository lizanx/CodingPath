cmake_minimum_required(VERSION 3.28)
project(CoroutineWithC LANGUAGES C ASM)
enable_language(ASM)

set(CMAKE_C_COMPILER gcc)
set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -g")

add_subdirectory(src)
