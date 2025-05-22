add_executable(MakeTable MakeTable.cxx)
target_link_libraries(MakeTable PRIVATE tutorial_compiler_flags)

add_custom_command(OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/Table.h
    COMMAND MakeTable ${CMAKE_CURRENT_BINARY_DIR}/Table.h
    DEPENDS MakeTable)
