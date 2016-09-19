//
// Created by parallels on 9/10/16.
//

#include <dio/base/Logging.h>
#include <dio/net/TcpServer.h>
#include <dio/net/Buffer.h>
#include <dio/net/TcpConnection.h>

using namespace dio;

void newMessageCallback(const net::TcpConnectionPtr tcpConnection, net::Buffer* buffer, Timestamp time) {
    string msg = buffer->retrieveAllAsString();
    LOG_INFO << tcpConnection->name() << " discard " << msg.size() << " bytes data at " << time.toString();
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

