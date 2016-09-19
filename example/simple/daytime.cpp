//
// Created by parallels on 9/14/16.
//

#include <dio/base/Logging.h>
#include <dio/net/TcpServer.h>
#include <dio/net/Buffer.h>
#include <dio/net/TcpConnection.h>

using namespace dio;

void newConnectionCallback(const net::TcpConnectionPtr tcpConnection) {
    LOG_INFO << "DayTimeServer - " << tcpConnection->peerAddr().toIpPort() << " -> " << tcpConnection->localAddr().toIpPort()
            << " is " << (tcpConnection->connected() ? "up" : "down");
    if (tcpConnection->connected()) {
        LOG_INFO << "close";
        tcpConnection->send(Timestamp::now().toFormattedString());
        tcpConnection->shutdown();
    }
}

int main() {
    LOG_INFO << "Testcase: daytime: start server";
    EventLoop eventLoop;
    InetAddress inetAddress(1999);
    TcpServer tcpServer(&eventLoop, inetAddress);
    tcpServer.setConnectionCallback(newConnectionCallback);

    tcpServer.start();
    eventLoop.loop();
    return 0;
}
