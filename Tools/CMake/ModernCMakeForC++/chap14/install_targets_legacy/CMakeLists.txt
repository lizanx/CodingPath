cmake_minimum_required(VERSION 3.26.0)
project(InstallTargetsLegacy)

add_subdirectory(src bin)

# Install commands for libcalc
include(GNUInstallDirs) # this module will correctly set install paths according to OS
message("Lib install dir: ${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_LIBDIR}")
message("Bin install dir: ${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_BINDIR}")
message("Include install dir: ${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_INCLUDEDIR}")
install(TARGETS calc
    ARCHIVE
    PUBLIC_HEADER
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/calc)
