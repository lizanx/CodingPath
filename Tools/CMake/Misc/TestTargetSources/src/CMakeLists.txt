add_subdirectory(calc)

add_executable(app main.cpp)

target_link_libraries(app calc)
