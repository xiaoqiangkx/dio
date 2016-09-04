//
// Created by coolman on 16/7/23.
//



#include <muduo/net/InetAddress.h>

#include <muduo/net/EventLoop.h>
#include <muduo/net/TcpClient.h>

#include "Connector.h"

void newConnectionCallback(int sockfd) {
    std::cout << "test_socket:" << sockfd;
}


int main() {
    std::cout << "hello" << std::endl;
    muduo::net::EventLoop eventLoop;

    muduo::net::InetAddress clientAddr(1998);
    muduo::net::ConnectorPtr connector(new muduo::net::Connector(&eventLoop, clientAddr));
    connector->setNewConnectionCallback(newConnectionCallback);
    connector->start();
    eventLoop.loop();
    return 0;
}

