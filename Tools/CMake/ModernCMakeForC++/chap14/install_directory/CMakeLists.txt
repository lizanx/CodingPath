cmake_minimum_required(VERSION 3.26.0)
project(InstallDirectory)

add_subdirectory(src bin)

include(GNUInstallDirs)

install(DIRECTORY data/ DESTINATION ${CMAKE_INSTALL_DATADIR}/calc)

install(DIRECTORY src/include/calc
    TYPE INCLUDE
    PATTERN "ignored" EXCLUDE
    PATTERN "ext_calc.hpp" EXCLUDE)

install(DIRECTORY etc/
    TYPE SYSCONF
    DIRECTORY_PERMISSIONS
        OWNER_READ OWNER_WRITE OWNER_EXECUTE
    PATTERN "calc.conf"
        PERMISSIONS OWNER_READ OWNER_WRITE)
