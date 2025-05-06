add_library(calc STATIC calc.cpp)
target_include_directories(calc PUBLIC ${CMAKE_CURRENT_LIST_DIR})

add_library(program STATIC start_program.cpp)
target_link_libraries(program PUBLIC calc)

add_executable(main main.cpp)
target_link_libraries(main PRIVATE program)

include(ClangTidy)
AddClangTidy(program)
