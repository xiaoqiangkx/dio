//
// Created by parallels on 8/14/16.
//

#include "TcpServer.h"
#include "TcpConnection.h"

#include <boost/bind.hpp>


namespace dio {

    TcpServer::TcpServer(EventLoop *loop, const muduo::net::InetAddress &listenAddr):
        loop_(loop),
        acceptorPtr_(new Acceptor(loop, listenAddr)),
        started_(false),
        nextConnId_(1),
        connName_("conn_")
    {
        acceptorPtr_->setNewConnectionCallback(boost::bind(&TcpServer::newConnection, this, _1, _2));
    }

    void TcpServer::start() {
        loop_->assertInLoopThread();
        acceptorPtr_->listnen();
    }

    void TcpServer::newConnection(int connfd, const muduo::net::InetAddress& listenAddr) {
        // create an new TcpConnection and insert into connectionMap
        loop_->assertInLoopThread();

        char buf[32];

        snprintf(buf, sizeof buf, "#%d", connfd);
        ++connfd;
        std::string connName = connName_ + buf;

        TcpConnectionPtr newConnPtr(new TcpConnection());
        connMaps_[connName] = newConnPtr;

        if (connectionCallback_) {
            connectionCallback_(newConnPtr);
        }
    }
};