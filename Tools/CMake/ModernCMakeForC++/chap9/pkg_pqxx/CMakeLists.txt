cmake_minimum_required(VERSION 3.26.0)
project(PackagePqxx CXX)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/module")
find_package(PQXX REQUIRED)

add_executable(PackagePqxx main.cpp)
target_link_libraries(PackagePqxx PRIVATE PQXX::PQXX)