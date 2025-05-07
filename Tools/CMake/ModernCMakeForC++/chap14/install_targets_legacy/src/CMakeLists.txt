add_library(calc STATIC calc.cpp)
target_include_directories(calc PUBLIC ${CMAKE_CURRENT_LIST_DIR}/include)
# Set public header property for usage in installation
set_target_properties(calc PROPERTIES PUBLIC_HEADER ${CMAKE_CURRENT_SOURCE_DIR}/include/calc.hpp)

add_executable(main main.cpp)
target_link_libraries(main PRIVATE calc)
