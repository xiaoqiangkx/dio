//
// Created by parallels on 8/14/16.
//

#ifndef DIO_TCPSERVER_H
#define DIO_TCPSERVER_H

#include <map>
#include <string>
#include <boost/noncopyable.hpp>

#include "EventLoop.h"
#include "Acceptor.h"
#include "Callbacks.h"

namespace dio {

class TcpServer: public boost::noncopyable {
public:
    TcpServer(EventLoop *loop, const muduo::net::InetAddress &listenAddr);

    void setMessageCallback(const MessageCallback& cb) {
        messageCallback_ = cb;
    }

    void setConnectionCallback(const ConnectionCallback& cb) {
        connectionCallback_ = cb;
    }

    void start();

private:
    typedef std::map<std::string, TcpConnectionPtr> connectionMap;
    EventLoop *loop_;
    boost::shared_ptr<Acceptor> acceptorPtr_;
    MessageCallback messageCallback_;
    ConnectionCallback connectionCallback_;
    connectionMap connMaps_;
    bool started_;
    int nextConnId_;
    std::string connName_;

    void newConnection(int connfd, const muduo::net::InetAddress& listenAddr);
};

};


#endif //DIO_TCPSERVER_H
