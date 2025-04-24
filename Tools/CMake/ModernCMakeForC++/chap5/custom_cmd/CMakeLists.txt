cmake_minimum_required(VERSION 3.20.0)
project(CustomizedCommands)

# Executable depends on file generated in below customized command,
# which implicitly makes this target depend on the customized command.
add_executable(CustomizedCommands main.cpp)

# Customized command 1: generate main.cpp
add_custom_command(OUTPUT main.cpp
    COMMAND "cp" ARGS "${CMAKE_SOURCE_DIR}/code.txt" "main.cpp"
)

# Customized command 2: hook triggered after compiling
add_custom_command(TARGET CustomizedCommands
    POST_BUILD
    COMMAND "echo" ARGS "Contents of main.cpp:\n"
    COMMAND "cat" ARGS "main.cpp"
)
