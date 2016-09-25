//
// Created by parallels on 9/25/16.
//

#ifndef PROJECT_CHATSERVER_H
#define PROJECT_CHATSERVER_H


#include <boost/core/noncopyable.hpp>
#include <dio/net/TcpServer.h>
#include <dio/net/LengthHeaderCodec.h>

namespace dio {

class EventLoop;

class ChatServer: public boost::noncopyable {
public:
    ChatServer(EventLoop *loop, InetAddress address);
    void start();
private:
    typedef std::set<dio::net::TcpConnectionPtr> ConnectionList;
    EventLoop* loop_;
    TcpServer tcpServer_;
    LengthHeaderCodec codec_;
    ConnectionList connectionList_;

    void onConnection(const dio::net::TcpConnectionPtr&);
    void onStringMessage(const dio::net::TcpConnectionPtr&, const std::string&, Timestamp);
};

};


#endif //PROJECT_CHATSERVER_H
