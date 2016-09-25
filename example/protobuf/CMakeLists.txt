cmake_minimum_required(VERSION 3.5)

PROJECT(protobuf_exe)

add_executable(protobuf_exe main.cpp query.pb.cc query.pb.h)

target_link_libraries(
protobuf_exe PUBLIC protobuf
)