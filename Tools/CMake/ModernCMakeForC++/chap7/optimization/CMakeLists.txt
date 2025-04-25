cmake_minimum_required(VERSION "3.20.0")
project(Optimization)

add_executable(Optimization main.cpp)

message("C++ DEBUG flag: " ${CMAKE_CXX_FLAGS_DEBUG})
message("C++ RELEASE flag: " ${CMAKE_CXX_FLAGS_RELEASE})
message("C DEBUG flag: " ${CMAKE_C_FLAGS_DEBUG})
message("C RELEASE flag: " ${CMAKE_C_FLAGS_RELEASE})
# message("Fortran DEBUG flag: " ${CMAKE_FORTRAN_FLAGS_DEBUG})
# message("Fortran RELEASE flag: " ${CMAKE_FORTRAN_FLAGS_RELEASE})
