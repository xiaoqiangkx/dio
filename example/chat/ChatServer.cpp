//
// Created by parallels on 9/25/16.
//

#include "ChatServer.h"

#include <dio/net/EventLoop.h>
#include <boost/bind.hpp>
#include <dio/net/TcpConnection.h>
#include <dio/net/LengthHeaderCodec.h>
#include <dio/base/Callbacks.h>

namespace  dio {

ChatServer::ChatServer(EventLoop *loop, InetAddress address):
    loop_(loop),
    tcpServer_(loop, address),
    codec_(boost::bind(&ChatServer::onStringMessage, this, _1, _2, _3))
{
    tcpServer_.setConnectionCallback(boost::bind(&ChatServer::onConnection, this, _1));
    tcpServer_.setMessageCallback(boost::bind(&LengthHeaderCodec::onMessage, &codec_, _1, _2, _3));
}

void ChatServer::start() {
    tcpServer_.start();
}

void ChatServer::onStringMessage(const dio::net::TcpConnectionPtr& connection, const std::string& message, Timestamp timestamp) {
    for (ConnectionList::iterator it = connectionList_.begin(); it != connectionList_.end(); ++it) {
        codec_.send(*it, message);
    }
}

void ChatServer::onConnection(const dio::net::TcpConnectionPtr& connection) {
    if (connection->connected()) {
        connectionList_.insert(connection);
    } else {
        connectionList_.erase(connection);
    }
}
};
