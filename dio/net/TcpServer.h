//
// Created by parallels on 8/14/16.
//

#ifndef DIO_TCPSERVER_H
#define DIO_TCPSERVER_H

#include <map>
#include <string>
#include <boost/noncopyable.hpp>

#include <dio/net/EventLoop.h>
#include <dio/net/Acceptor.h>
#include <dio/base/Callbacks.h>
#include <dio/net/EventLoopThreadPool.h>

namespace dio {

class TcpServer: public boost::noncopyable {
public:
    TcpServer(EventLoop *loop, const InetAddress &listenAddr);

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

    void setThreadNum(int num) {
        threadPool_->setThreadNum(num);
    }

private:
    typedef std::map<std::string, dio::net::TcpConnectionPtr> connectionMap;
    EventLoop *loop_;
    boost::shared_ptr<Acceptor> acceptorPtr_;
    dio::net::MessageCallback messageCallback_;
    dio::net::ConnectionCallback connectionCallback_;
    dio::net::WriteCompleteCallback writeCompleteCallback_;
    connectionMap connMaps_;
    bool started_;
    int nextConnId_;
    std::string name_;
    boost::scoped_ptr<EventLoopThreadPool> threadPool_;

    void newConnection(int connfd, const InetAddress& listenAddr);
    void removeConnection(const dio::net::TcpConnectionPtr& tcpConnection);
    void removeConnectionInLoop(const dio::net::TcpConnectionPtr& tcpConnection);
};

};


#endif //DIO_TCPSERVER_H
