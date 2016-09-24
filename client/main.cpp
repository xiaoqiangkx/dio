//
// Created by coolman on 16/7/23.
//
#include <dio/net/EventLoop.h>
#include <dio/net/TcpClient.h>
#include <boost/bind.hpp>
#include <vector>

void newConnectionCallback(int sockfd) {
    LOG_INFO << "new Connection: " << sockfd;
}


int main() {
    dio::EventLoop eventLoop;
    dio::InetAddress address(1998);

//    int num = 10000;
//    std::vector<boost::shared_ptr<dio::Connector>> connectorVec(num);
//
//    for (int i = 0; i < num; ++i) {
//        boost::shared_ptr<dio::Connector> connector(new dio::Connector(&eventLoop, address));
//        connectorVec.push_back(connector);
//        connector->setNewConnectionCallback(boost::bind(&newConnectionCallback, _1));
//        connector->start();
//    }

    dio::TcpClient tcpClient(&eventLoop, address);
    tcpClient.setNewConnectionCallback(boost::bind(&newConnectionCallback, _1));
    tcpClient.start();
    eventLoop.loop();

    return 0;
}

