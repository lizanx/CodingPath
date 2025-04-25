cmake_minimum_required(VERSION 3.20.0)
project(ToolchainConfig)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Set config to Debug" FORCE)
endif()

add_executable(ToolChainConfig main.cpp)
target_compile_definitions(ToolChainConfig PRIVATE
    $<IF:$<PLATFORM_ID:Windows>,PLATFORM_WIN,>
    $<IF:$<PLATFORM_ID:Linux>,PLATFORM_LINUX,>
    $<IF:$<CXX_COMPILER_ID:GNU>,COMPILER_GCC,>
    $<IF:$<CXX_COMPILER_ID:Clang,AppleClang>,COMPILER_CLANG,>
    $<IF:$<CONFIG:Debug>,CONFIG_DEBUG,>
    $<IF:$<CONFIG:Release>,CONFIG_RELEASE,>
    )

# Output generator output to file for debug.
file(GENERATE OUTPUT "${CMAKE_BINARY_DIR}/generator_output.txt"
    CONTENT "Config: $<CONFIG>\n")

# Add customized command to show generator output.
add_custom_command(TARGET ToolChainConfig POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E echo "Platform: $<PLATFORM_ID>, Compiler: $<CXX_COMPILER_ID>, Config: $<CONFIG>")
