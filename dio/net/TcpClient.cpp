//
// Created by parallels on 9/20/16.
//

#include <dio/net/TcpClient.h>
#include <dio/net/EventLoop.h>
#include <boost/bind.hpp>
#include <dio/net/SocketOps.h>
#include <dio/net/TcpConnection.h>


namespace dio {

    TcpClient::TcpClient(EventLoop* loop, const InetAddress &remoteAddress):
        loop_(loop),
        connector_(new Connector(loop, remoteAddress))
    {

    }

    void TcpClient::start() {
        connector_->setNewConnectionCallback(boost::bind(&TcpClient::newConnection, this, _1));
        connector_->start();
    }

    void TcpClient::stop() {
        connector_->stop();
    }

    void TcpClient::removeConnection(const dio::net::TcpConnectionPtr &tcpConnection) {
        loop_->assertInLoopThread();
        LOG_INFO << "TcpServer::removeConnection [ " << name_ << "] Connection " <<
                 tcpConnection->name_;

        connection_.reset();

        loop_->QueueInLoop(
                boost::bind(&TcpConnection::connectDestroyed, tcpConnection)
        );
    }

    void TcpClient::newConnection(int connfd) {
        // create an new TcpConnection and insert into connectionMap
        loop_->assertInLoopThread();

        char buf[32];

        snprintf(buf, sizeof buf, "#%d", connfd);
        std::string connName = name_ + buf;

        struct sockaddr_in local_addr = sockets::getLocalAddr(connfd);
        InetAddress localAddr(local_addr);

        struct sockaddr_in peer_addr = sockets::getPeerAddr(connfd);
        InetAddress peerAddr(peer_addr);

        connection_.reset(new TcpConnection(loop_, connName, connfd, localAddr, peer_addr));


        connection_->setConnectionCallback(connectionCallback_);
        connection_->setMessageCallback(messageCallback_);
        connection_->setCloseCallback(
                boost::bind(&TcpClient::removeConnection, this, _1)
        );
        connection_->connectEstablished();
    }

};
