add_library(calc SHARED calc.cpp)
target_include_directories(calc PUBLIC ${CMAKE_CURRENT_LIST_DIR}/include)
# Add file set for installation
target_sources(calc PUBLIC
    FILE_SET calc_headers
    TYPE HEADERS
    BASE_DIRS include
    FILES
        include/calc.hpp)

add_executable(main main.cpp)
target_link_libraries(main PRIVATE calc)

# Install commands for libcalc
include(GNUInstallDirs) # this module will correctly set install paths according to OS
message("Lib install dir: ${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_LIBDIR}")
message("Bin install dir: ${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_BINDIR}")
message("Include install dir: ${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_INCLUDEDIR}")
install(TARGETS calc LIBRARY FILE_SET calc_headers)
# Call "ldconfig" on Unix to update ld cache.
if(UNIX)
    message("Unix system, update ld cache.")
    install(CODE "execute_process(COMMAND ldconfig)")
endif()
