add_executable(client main.cpp)

project(client)

target_link_libraries(client PUBLIC dio pthread)