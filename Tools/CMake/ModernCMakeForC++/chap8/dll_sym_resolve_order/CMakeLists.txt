cmake_minimum_required(VERSION 3.20.0)
project(DynamicLinkedLibSymbolResolveOrder)

add_library(SharedLib1 SHARED shared_lib_1.cpp)
add_library(SharedLib2 SHARED shared_lib_2.cpp)

# The symbol "void FuncDuplicated()" exists in both shared lib 1 and 2,
# thus linker will choose the symbol linked first.
# Namely, link order determines whether "SharedLib1-FuncDuplicated" or 
# "SharedLib2-FuncDuplicated" is used.
# This is considered bad practice, use distinct namespaces in each shared lib for clarity.
add_executable(DynamicLinkedLibSymbolResolveOrder_1 main.cpp)
target_link_libraries(DynamicLinkedLibSymbolResolveOrder_1 SharedLib1 SharedLib2) # link lib1 then lib2

add_executable(DynamicLinkedLibSymbolResolveOrder_2 main.cpp)
target_link_libraries(DynamicLinkedLibSymbolResolveOrder_2 SharedLib2 SharedLib1) # link lib2 then lib1
