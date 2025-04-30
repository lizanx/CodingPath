function(Format target dir)
    find_program(CLANG-FORMAT_PATH clang-format REQUIRED)
    set(EXPRESSION h hh hpp c cpp cc cxx)
    list(TRANSFORM EXPRESSION PREPEND "${dir}/*.")
    file(GLOB_RECURSE SOURCE_FILES FOLLOW_SYMLINKS
        LIST_DIRECTORIES false ${EXPRESSION})
    add_custom_command(TARGET ${target} PRE_BUILD
        COMMAND ${CLANG-FORMAT_PATH} -i --style=file ${SOURCE_FILES}
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})
endfunction()
