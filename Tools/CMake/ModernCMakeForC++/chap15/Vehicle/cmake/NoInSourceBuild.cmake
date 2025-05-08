if(${PROJECT_SOURCE_DIR} STREQUAL ${PROJECT_BINARY_DIR})
message(FATAL_ERROR
    "\n"
    "In-source build not allowed!\n"
    "Source dir: ${PROJECT_SOURCE_DIR}\n"
    "Build dir: ${PROJECT_BINARY_DIR}\n"
    "Use 'cmake -B <temporary-build-dir>' for out-of-tree build.\n"
    "To remove cmake files you accidentally created,\n"
    "execute 'rm -rf ./CMakeFiles ./CMakeCache.txt'\n")
endif()
