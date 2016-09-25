//
// Created by coolman on 16/7/23.
//
#include <dio/net/EventLoop.h>
#include <dio/net/TcpClient.h>
#include <dio/base/Callbacks.h>
#include <boost/bind.hpp>
#include <dio/net/TcpConnection.h>
#include <vector>

void newConnectionCallback(const dio::net::TcpConnectionPtr &connection) {
    LOG_INFO << "new Connection: ";
    if (connection->connected()) {
        connection->send("123");
    }
}


void newMessageCallback(const dio::net::TcpConnectionPtr &connection, dio::net::Buffer *buf, dio::Timestamp timestamp) {
    std::string data = buf->retrieveAllAsString();
    LOG_INFO << "newMessageCallback: " << data;
}


void WriteCompleteCallback(const dio::net::TcpConnectionPtr& connection) {
    LOG_INFO << "write complete callback";
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
    tcpClient.setConnectionCallback(boost::bind(&newConnectionCallback, _1));
    tcpClient.setMessageCallback(boost::bind(&newMessageCallback, _1, _2, _3));
    tcpClient.setWriteCompleteCallback(boost::bind(&WriteCompleteCallback, _1));
    tcpClient.start();
    eventLoop.loop();

    return 0;
}

