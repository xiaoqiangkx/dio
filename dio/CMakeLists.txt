cmake_minimum_required(VERSION 3.5)

project(dio)

add_subdirectory(net/tests)

AUX_SOURCE_DIRECTORY(. DIR_DIO_SRCS)
AUX_SOURCE_DIRECTORY(./base DIO_BASE_SRCS)
AUX_SOURCE_DIRECTORY(./net DIO_NET_SRCS)
AUX_SOURCE_DIRECTORY(./protobuf DIO_PROTOBUF_SRCS)
ADD_LIBRARY(dio STATIC ${DIR_DIO_SRCS} ${DIO_BASE_SRCS} ${DIO_NET_SRCS} ${DIO_PROTOBUF_SRCS} net/tests/test_unittest.cpp net/TcpClient.cpp net/TcpClient.h net/Connector.cpp net/Connector.h net/LengthHeaderCodec.cpp net/LengthHeaderCodec.h net/ProtobufCodec.cpp net/ProtobufCodec.h net/EventLoopThread.cpp net/EventLoopThread.h net/EventLoopThreadPool.cpp net/EventLoopThreadPool.h)

target_link_libraries(
dio PUBLIC pthread
)

target_compile_options(dio PUBLIC -std=c++11 -g)