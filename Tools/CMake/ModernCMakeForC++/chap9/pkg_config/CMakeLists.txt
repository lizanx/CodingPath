cmake_minimum_required(VERSION 3.26.0)
project(FindPkgConfig CXX)

find_package(PkgConfig REQUIRED)
pkg_check_modules(PQXX REQUIRED IMPORTED_TARGET libpqxx)
message("PQXX found: ${PQXX_FOUND}")

add_executable(main main.cpp)
target_link_libraries(main PRIVATE PkgConfig::PQXX)
