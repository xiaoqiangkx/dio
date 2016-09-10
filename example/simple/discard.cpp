//
// Created by parallels on 9/10/16.
//

#include <dio/base/Logging.h>
#include <dio/net/TcpServer.h>
#include <dio/net/Buffer.h>

using namespace dio;

void newMessageCallback(const net::TcpConnectionPtr tcpConnection, net::Buffer* buffer, Timestamp now) {
    string data = buffer->retrieveAllAsString();
    LOG_INFO << "new message come: " << data;
}

int main() {
    LOG_INFO << "start main";
    EventLoop eventLoop;
    InetAddress inetAddress(1998);
    TcpServer tcpServer(&eventLoop, inetAddress);
    tcpServer.setMessageCallback(newMessageCallback);

    LOG_INFO << "start server";
    tcpServer.start();
    eventLoop.loop();
    return 0;
}

