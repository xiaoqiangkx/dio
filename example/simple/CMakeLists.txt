cmake_minimum_required(VERSION 3.5)

PROJECT(simple)

add_executable(discard discard.cpp)
add_executable(daytime daytime.cpp)
add_executable(download download.cpp)

target_link_libraries(
discard PUBLIC pthread dio
)

target_link_libraries(
daytime PUBLIC pthread dio
)

target_link_libraries(
download PUBLIC pthread dio
)