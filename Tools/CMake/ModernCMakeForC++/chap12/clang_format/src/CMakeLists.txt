add_library(calc calc.cpp)
target_include_directories(calc PUBLIC ${CMAKE_CURRENT_LIST_DIR})

add_executable(main main.cpp)
target_link_libraries(main PRIVATE calc)

include(Format)
Format(main ${CMAKE_CURRENT_LIST_DIR})
