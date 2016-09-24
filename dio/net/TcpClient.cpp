//
// Created by parallels on 9/20/16.
//

#include <dio/net/TcpClient.h>
#include <dio/net/EventLoop.h>
#include <boost/bind.hpp>


namespace dio {

    TcpClient::TcpClient(EventLoop* loop, const InetAddress &remoteAddress):
        loop_(loop),
        connector_(new Connector(loop, remoteAddress))
    {

    }

    void TcpClient::start() {
        connector_->setNewConnectionCallback(boost::bind(&TcpClient::onNewConnectionCallback, this, _1));
        connector_->start();
    }

    void TcpClient::stop() {
        connector_->stop();
    }

    void TcpClient::onNewConnectionCallback(int sockfd) {
        LOG_INFO << "onNewConnection: " << sockfd;
    }

};
