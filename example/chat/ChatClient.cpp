//
// Created by parallels on 9/25/16.
//

#include "ChatClient.h"

#include <boost/bind.hpp>
#include <dio/net/TcpConnection.h>
#include <dio/net/LengthHeaderCodec.h>

namespace dio {

ChatClient::ChatClient(EventLoop *loop, const InetAddress& address):
    loop_(loop),
    tcpClient_(loop, address),
    codec_(boost::bind(&ChatClient::onMessage, this, _1, _2, _3))
{
    tcpClient_.setConnectionCallback(boost::bind(&ChatClient::onConnection, this, _1));
    tcpClient_.setMessageCallback(boost::bind(&LengthHeaderCodec::onMessage, &codec_, _1, _2, _3));
}

void ChatClient::start() {
    tcpClient_.start();
}

void ChatClient::send(const std::string& message) {
    codec_.send(connection_, message);
}

void ChatClient::onMessage(const dio::net::TcpConnectionPtr &connection, const std::string& message, Timestamp time) {
    LOG_INFO << "onMessage receive: " << message;
}

void ChatClient::onConnection(const dio::net::TcpConnectionPtr& connection) {
    if (connection->connected()) {
        connection_ = connection;
        send("test123");
    } else {

    }
}

};
