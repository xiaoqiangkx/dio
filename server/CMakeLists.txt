cmake_minimum_required(VERSION 3.5)

include_directories(${CMAKE_SOURCE_DIR})

project(server)


add_executable(server main.cpp)

target_link_libraries(
server PUBLIC pthread dio
)

target_compile_options(dio PUBLIC -std=c++11)
