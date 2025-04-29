cmake_minimum_required(VERSION 3.26.0)
project(PackageProtobuf CXX)

find_package(Protobuf REQUIRED)
message("Protobuf lib found? - ${Protobuf_FOUND}")
protobuf_generate_cpp(GENERATED_SRC GENERATED_HEADER message.proto)

add_executable(PackageProtobuf main.cpp ${GENERATED_SRC} ${GENERATED_HEADER})

# Traditional way: use variables defined in the Find module.
# target_link_libraries(PackageProtobuf PRIVATE ${Protobuf_LIBRARIES})
# target_include_directories(PackageProtobuf PRIVATE ${Protobuf_INCLUDE_DIRS} ${CMAKE_CURRENT_BINARY_DIR})

# Modern CMake way: use IMPORTED target, which passes include dirs/lib path automatically.
target_link_libraries(PackageProtobuf PRIVATE protobuf::libprotobuf)
target_include_directories(PackageProtobuf PRIVATE ${CMAKE_CURRENT_BINARY_DIR})
