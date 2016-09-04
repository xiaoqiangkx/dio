cmake_minimum_required(VERSION 3.5)

include_directories(${CMAKE_SOURCE_DIR})

project(test_socket)


add_executable(test_socket main.cpp)

target_compile_options(test_socket PUBLIC -std=c++11 -Wall)
