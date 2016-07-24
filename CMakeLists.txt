cmake_minimum_required(VERSION 3.5)
project(dio C CXX)

include_directories(
    /Users/coolman/workspace/server/build/debug-install/include
)

link_directories(   # 要放在add_executable前面
    /Users/coolman/workspace/server/build/debug-install/lib
)

add_subdirectory(echo)
add_subdirectory(noncopyable)
add_subdirectory(net_eventloop)
