include(FetchContent)
FetchContent_Declare(
    GoogleTest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.14.0
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(GoogleTest)

add_executable(unit_test program_test.cpp calc_test.cpp)
target_link_libraries(unit_test PRIVATE program gtest_main gmock)

# Add coverage
include(Coverage)
AddCoverage(unit_test)

include(GoogleTest)
gtest_discover_tests(unit_test)
