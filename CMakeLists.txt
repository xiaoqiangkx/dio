cmake_minimum_required(VERSION 3.5)

FIND_PACKAGE(Boost REQUIRED)
include_directories(
.
)

add_subdirectory(client)
add_subdirectory(dio)
add_subdirectory(server)
add_subdirectory(test_socket)
add_subdirectory(example)

