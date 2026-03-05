cmake_minimum_required(VERSION 3.26.0)

project(OpaqueEnumDeclaration DESCRIPTION "A demo program to show opaque enum declaration mechanism")

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (!CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug")
endif()

add_subdirectory(src)
