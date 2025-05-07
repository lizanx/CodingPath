add_library(calc STATIC calc.cpp ext_calc.cpp)
target_include_directories(calc PUBLIC ${CMAKE_CURRENT_LIST_DIR}/include)

add_executable(main main.cpp)
target_link_libraries(main PRIVATE calc)

# this module will correctly set install paths according to OS
include(GNUInstallDirs)
message("Lib install dir: ${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_LIBDIR}")
message("Bin install dir: ${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_BINDIR}")
message("Include install dir: ${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_INCLUDEDIR}")

# Files installation will only install declared files.
# (no target lib/executable will be installed, unless explicitly declared)
install(
    FILES # file installation won't retain original directory structure
        include/calc.hpp
        include/extended/ext_calc.hpp
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/calc
    )
