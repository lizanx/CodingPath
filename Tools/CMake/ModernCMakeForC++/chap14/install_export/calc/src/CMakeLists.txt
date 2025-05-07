include(GNUInstallDirs)

add_library(calc STATIC calc.cpp)
target_include_directories(calc
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)

# Add file set for installation
target_sources(calc
    PUBLIC FILE_SET calc_headers
    TYPE HEADERS
    BASE_DIRS include
    FILES
        include/calc.hpp)

add_executable(main main.cpp)
target_link_libraries(main PRIVATE calc)

# Install and define export target
install(TARGETS calc
    EXPORT CalcTarget
    ARCHIVE
    FILE_SET calc_headers)
# Install the exported target
install(EXPORT CalcTarget
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/calc/cmake
    NAMESPACE Calc::)
