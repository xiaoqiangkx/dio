cmake_minimum_required(VERSION 3.5)

PROJECT(protobuf_exe)

add_executable(protobuf_exe main.cpp query.pb.cc query.pb.h)
add_executable(protobuf_client ProtobufClient.cpp ProtobufClient.h protobuf_client.cpp)
add_executable(protobuf_server ProtobufServer.cpp ProtobufServer.h  protobuf_server.cpp)

target_link_libraries(
protobuf_exe PUBLIC protobuf
)

target_link_libraries(
protobuf_client PUBLIC protobuf dio
)

target_link_libraries(
protobuf_server PUBLIC protobuf dio
)