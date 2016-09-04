cmake_minimum_required(VERSION 3.5)

FIND_PACKAGE(Boost REQUIRED)
include_directories(
/home/parallels/workspace/build/release-install/include .
)

link_directories(   # 要放在add_executable前面
/home/parallels/workspace/build/release-install/lib
)

add_subdirectory(client)
add_subdirectory(dio)
add_subdirectory(server)
add_subdirectory(test_socket)

