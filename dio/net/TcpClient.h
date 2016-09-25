//
// Created by parallels on 9/20/16.
//

#ifndef PROJECT_TCPCLIENT_H
#define PROJECT_TCPCLIENT_H


#include <boost/core/noncopyable.hpp>
#include <boost/shared_ptr.hpp>
#include <dio/net/Connector.h>
#include <dio/base/Callbacks.h>


namespace dio {

class EventLoop;

class TcpClient : public boost::noncopyable {
public:
    TcpClient(EventLoop* loop, const InetAddress &remoteAddress);

    void setMessageCallback(const dio::net::MessageCallback& cb) {
        messageCallback_ = cb;
    }

    void setConnectionCallback(const dio::net::ConnectionCallback& cb) {
        connectionCallback_ = cb;
    }

    void setWriteCompleteCallback(const dio::net::WriteCompleteCallback& cb) {
        writeCompleteCallback_ = cb;
    }

    void start();
    void stop();
private:
    EventLoop *loop_;
    boost::shared_ptr<Connector> connector_;
    std::string name_;
    dio::net::TcpConnectionPtr connection_;
    dio::net::MessageCallback messageCallback_;
    dio::net::ConnectionCallback connectionCallback_;
    dio::net::WriteCompleteCallback writeCompleteCallback_;
    Connector::NewConnectionCallback newConnectionCallback_;

    void removeConnection(const dio::net::TcpConnectionPtr &tcpConnection);
    void newConnection(int connfd);

};

};


#endif //PROJECT_TCPCLIENT_H
