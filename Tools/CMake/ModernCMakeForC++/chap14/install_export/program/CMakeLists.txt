cmake_minimum_required(VERSION 3.26.0)
project(InstallExportProgram)

include(GNUInstallDirs)

add_executable(main main.cpp)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_LIBDIR}/calc/cmake)
include(CalcTarget)
target_link_libraries(main PRIVATE Calc::calc)
