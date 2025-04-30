add_library(random_mt19937 STATIC rng_mt19937.cpp)
target_include_directories(random_mt19937 PUBLIC ${CMAKE_CURRENT_LIST_DIR})

add_library(calc STATIC calc.cpp)
target_include_directories(calc PUBLIC ${CMAKE_CURRENT_LIST_DIR})

add_library(program STATIC start_program.cpp)
target_link_libraries(program PUBLIC calc random_mt19937)

# Add coverage
if(${CMAKE_BUILD_TYPE} STREQUAL Debug)
    target_compile_options(random_mt19937 PRIVATE --coverage)
    target_link_options(random_mt19937 PUBLIC --coverage)
    target_compile_options(calc PRIVATE --coverage)
    target_link_options(calc PUBLIC --coverage)
    target_compile_options(program PRIVATE --coverage)
    target_link_options(program PUBLIC --coverage)
    add_custom_command(TARGET program PRE_BUILD # remove outdated generated coverage info
        COMMAND find ${CMAKE_BINARY_DIR} -type f -name "*.gcda" -exec rm {} +)
endif()

add_executable(main main.cpp)
target_link_libraries(main PRIVATE program)
