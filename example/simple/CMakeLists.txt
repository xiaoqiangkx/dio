cmake_minimum_required(VERSION 3.5)

PROJECT(simple)

add_executable(simple discard.cpp)

target_link_libraries(
simple PUBLIC pthread dio
)