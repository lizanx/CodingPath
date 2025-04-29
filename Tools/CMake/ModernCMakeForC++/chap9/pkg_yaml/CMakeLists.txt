cmake_minimum_required(VERSION 3.5.0)
project(FetchContentYamlCpp CXX)

configure_file(config.yaml config.yaml COPYONLY)

include(FetchContent)
FetchContent_Declare(external-yaml-cpp
    GIT_REPOSITORY https://github.com/jbeder/yaml-cpp.git
    GIT_TAG 0.8.0
    FIND_PACKAGE_ARGS NAMES yaml-cpp)
FetchContent_MakeAvailable(external-yaml-cpp)

add_executable(main main.cpp)
target_link_libraries(main PRIVATE yaml-cpp::yaml-cpp)

include(CMakePrintHelpers)
cmake_print_properties(TARGETS yaml-cpp::yaml-cpp
    PROPERTIES TYPE SOURCE_DIR INTERFACE_INCLUDE_DIRS)
