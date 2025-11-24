set(INC_DIR "${CMAKE_CURRENT_LIST_DIR}/include")
add_library(coroutine STATIC coroutine.c co_swap.S ${INC_DIR}/coroutine.h)
target_include_directories(coroutine PUBLIC ${INC_DIR})
