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
# Export target file
install(EXPORT CalcTarget
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/calc/cmake
    NAMESPACE Calc::)

# Generate Config file
include(CMakePackageConfigHelpers)
set(LIB_INSTALL_DIR ${CMAKE_INSTALL_LIBDIR}/calc)
configure_package_config_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/CalcConfig.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/CalcConfig.cmake
    INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/calc/cmake
    PATH_VARS LIB_INSTALL_DIR
)

# Install config file
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/CalcConfig.cmake
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/calc/cmake)

# Generate version file
write_basic_package_version_file(
    ${CMAKE_CURRENT_BINARY_DIR}/CalcConfigVersion.cmake
    VERSION 1.2.3
    COMPATIBILITY AnyNewerVersion
)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/CalcConfigVersion.cmake
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/calc/cmake)
