//
// Created by coolman on 16/7/23.
//


#include <dio/net/EventLoop.h>
#include <dio/net/Acceptor.h>
#include <dio/net/TcpServer.h>
#include <dio/net/TcpConnection.h>
#include <dio/base/Thread.h>


void newConnection(const dio::net::TcpConnectionPtr& connection)
{
    LOG_INFO << "hello world";
}

void messageCallback(const dio::net::TcpConnectionPtr &conn, dio::net::Buffer* buf, dio::Timestamp timestamp) {
    std::string data = buf->retrieveAllAsString();
    LOG_INFO << "new message: " << data;
    conn->send(data);
}

void writeCompleteCallback(const dio::net::TcpConnectionPtr& connection) {
    LOG_INFO << "write_complete_callback";
}

int main() {
    LOG_INFO <<"hello eventloop";
    dio::EventLoop eventLoop;

    dio::InetAddress listenAddress(1998);
    dio::TcpServer tcpServer(&eventLoop, listenAddress);
    tcpServer.setConnectionCallback(newConnection);
    tcpServer.setMessageCallback(messageCallback);
    tcpServer.setWriteCompleteCallback(writeCompleteCallback);

    tcpServer.start();
    eventLoop.loop();
    return 0;
}

