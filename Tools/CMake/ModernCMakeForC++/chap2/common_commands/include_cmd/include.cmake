message("Current script: ${CMAKE_CURRENT_LIST_FILE}")
message("Calling my_func...")
include("${CMAKE_CURRENT_LIST_DIR}/my_func.cmake")
my_func(1 2 3 4)
