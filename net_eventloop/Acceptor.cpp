//
// Created by coolman on 16/8/9.
//

#include "Acceptor.h"
#include <boost/bind.hpp>
#include "EventLoop.h"
#include <muduo/base/Logging.h>


namespace dio {

    Acceptor::Acceptor(EventLoop *loop, const muduo::net::InetAddress &address):
        loop_(loop),
        serverSocket_(muduo::net::sockets::createNonblockingOrDie(AF_INET)),
        acceptChannel_(loop, serverSocket_.fd()),
        listening_(false)
    {
        serverSocket_.setReuseAddr(true);   // What's the purpose
        serverSocket_.bindAddress(address);
        acceptChannel_.setReadCallback(boost::bind(&Acceptor::handleRead, this));
    }

    void Acceptor::handleRead() {
        loop_->assertInLoopThread();
        muduo::net::InetAddress peerAddresss(0);
        int conn_fd = serverSocket_.accept(&peerAddresss);
        if (conn_fd >= 0) {
            if (newConnectionCallback_) {
                newConnectionCallback_(conn_fd, peerAddresss);
            } else {
                muduo::net::sockets::close(conn_fd);
            }
        } else {
            LOG_ERROR << "failed to handleRead without address";
        }
    }

    void Acceptor::listnen() {
        loop_->assertInLoopThread();
        listening_ = true;
        serverSocket_.listen();
        acceptChannel_.enableReading();
    }
};
