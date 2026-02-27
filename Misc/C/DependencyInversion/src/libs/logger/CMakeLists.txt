add_library(logger STATIC file_logger.c stdout_logger.c)
target_include_directories(logger PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
