add_subdirectory(libcoroutine)

add_executable(co_test main.c)
target_link_libraries(co_test coroutine)
