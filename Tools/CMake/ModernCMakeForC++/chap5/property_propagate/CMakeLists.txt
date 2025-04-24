cmake_minimum_required(VERSION 3.20.0)
project(PropertyPropagate CXX)


add_library(src_lib1 empty.cpp)
set_target_properties(src_lib1 PROPERTIES INTERFACE_LIB_VERSION 4)
# Add the customized property to interface properties check list
set_property(TARGET src_lib1 APPEND PROPERTY COMPATIBLE_INTERFACE_STRING LIB_VERSION)

add_library(src_lib2 empty.cpp)
set_target_properties(src_lib2 PROPERTIES INTERFACE_LIB_VERSION 4) # change this version, then cmake fails.
set_property(TARGET src_lib2 APPEND PROPERTY COMPATIBLE_INTERFACE_STRING LIB_VERSION)

add_library(dst_lib empty.cpp)
target_link_libraries(dst_lib src_lib1 src_lib2)
