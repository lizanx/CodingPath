add_library(calc STATIC calc.cpp ext_calc.cpp)
target_include_directories(calc PUBLIC ${CMAKE_CURRENT_LIST_DIR}/include)

add_executable(main main.cpp)
target_link_libraries(main PRIVATE calc)
