include(FetchContent)
FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2
    GIT_TAG v3.8.0
)
FetchContent_MakeAvailable(Catch2)

add_executable(unit_test program_test.cpp calc_test.cpp)
target_link_libraries(unit_test PRIVATE program Catch2::Catch2WithMain)

list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/extras)
include(Catch)
catch_discover_tests(unit_test)
