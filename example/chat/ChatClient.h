//
// Created by parallels on 9/25/16.
//

#ifndef PROJECT_CHATCLIENT_H
#define PROJECT_CHATCLIENT_H


#include <boost/core/noncopyable.hpp>
#include <dio/net/LengthHeaderCodec.h>
#include <dio/net/TcpClient.h>
#include <dio/net/InetAddress.h>
#include <dio/base/Callbacks.h>

namespace dio {

class EventLoop;

class ChatClient : public boost::noncopyable {
public:
    ChatClient(EventLoop *loop, const InetAddress& address);
    void start();
    void send(const std::string&);

private:
    EventLoop *loop_;
    TcpClient tcpClient_;
    LengthHeaderCodec codec_;
    dio::net::TcpConnectionPtr connection_;

    void onConnection(const dio::net::TcpConnectionPtr&);
    void onMessage(const dio::net::TcpConnectionPtr&, const std::string&, Timestamp);
};
};


#endif //PROJECT_CHATCLIENT_H
