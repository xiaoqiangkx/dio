//
// Created by parallels on 8/14/16.
//

#include "TcpServer.h"
#include <dio/net/TcpConnection.h>
#include <dio/net/SocketOps.h>
#include <cstdio>

#include <boost/bind.hpp>


namespace dio {

    TcpServer::TcpServer(EventLoop *loop, const InetAddress &listenAddr):
        loop_(loop),
        acceptorPtr_(new Acceptor(loop, listenAddr)),
        started_(false),
        nextConnId_(1),
        name_("conn_")
    {
        acceptorPtr_->setNewConnectionCallback(boost::bind(&TcpServer::newConnection, this, _1, _2));
    }

    void TcpServer::start() {
        loop_->assertInLoopThread();
        acceptorPtr_->listen();
    }

    void TcpServer::removeConnection(const dio::net::TcpConnectionPtr &tcpConnection) {
        loop_->assertInLoopThread();
        LOG_INFO << "TcpServer::removeConnection [ " << name_ << "] Connection " <<
             tcpConnection->name_;

        connMaps_.erase(tcpConnection->name_);
        loop_->QueueInLoop(
                boost::bind(&TcpConnection::connectDestroyed, tcpConnection)
        );
    }

    void TcpServer::newConnection(int connfd, const InetAddress& listenAddr) {
        // create an new TcpConnection and insert into connectionMap
        loop_->assertInLoopThread();

        char buf[32];

        snprintf(buf, sizeof buf, "#%d", connfd);
        std::string connName = name_ + buf;

        struct sockaddr_in local_addr = sockets::getLocalAddr(connfd);
        InetAddress localAddr(local_addr);

        struct sockaddr_in peer_addr = sockets::getPeerAddr(connfd);
        InetAddress peerAddr(peer_addr);

        dio::net::TcpConnectionPtr newConnPtr(new TcpConnection(loop_, connName, connfd, localAddr, peer_addr));
        connMaps_[connName] = newConnPtr;

        newConnPtr->setConnectionCallback(connectionCallback_);
        newConnPtr->setMessageCallback(messageCallback_);
        newConnPtr->setCloseCallback(
               boost::bind(&TcpServer::removeConnection, this, _1)
        );
        newConnPtr->connectEstablished();
    }
};