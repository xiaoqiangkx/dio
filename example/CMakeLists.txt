cmake_minimum_required(VERSION 3.5)

PROJECT(example)

add_subdirectory(simple)
add_subdirectory(chat)
add_subdirectory(protobuf)
add_subdirectory(client)
add_subdirectory(server)

target_compile_options(dio PUBLIC -std=c++11 -g)
