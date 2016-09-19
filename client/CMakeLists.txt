add_executable(client main.cpp Connector.h ../example/simple/discard.cpp)

project(client)

target_link_libraries(client PUBLIC muduo_net muduo_base pthread)