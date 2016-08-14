cmake_minimum_required(VERSION 3.5)
project(dio C CXX)

FIND_PACKAGE(Boost REQUIRED)
include_directories(
        /home/parallels/workspace/build/release-install/include
)

link_directories(   # 要放在add_executable前面
        /home/parallels/workspace/build/release-install/lib
)

add_subdirectory(echo)
add_subdirectory(noncopyable)
add_subdirectory(net_eventloop)
