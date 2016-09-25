cmake_minimum_required(VERSION 3.5)

PROJECT(chat)

add_executable(chat_server chat_server.cpp ChatServer.h ChatServer.cpp)
add_executable(chat_client chat_client.cpp ChatClient.cpp ChatClient.h ../protobuf/main.cpp)

target_link_libraries(
chat_server PUBLIC pthread dio
)

target_link_libraries(
chat_client PUBLIC pthread dio
)