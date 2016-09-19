//
// Created by coolman on 16/8/9.
//

#include <dio/net/Acceptor.h>
#include <boost/bind.hpp>

#include <dio/net/EventLoop.h>
#include <dio/net/SocketOps.h>
#include <cerrno>


namespace dio {

    Acceptor::Acceptor(EventLoop *loop, const InetAddress &address):
        loop_(loop),
        serverSocket_(address),
        acceptChannel_(loop, serverSocket_.fd()),
        listening_(false)
    {
        serverSocket_.bindAddress();
        serverSocket_.setReusePort(true);
        acceptChannel_.setReadCallback(boost::bind(&Acceptor::handleRead, this));
    }

    void Acceptor::handleRead() {
        loop_->assertInLoopThread();
        InetAddress peerAddresss;
        int conn_fd = serverSocket_.accept(&peerAddresss);
        if (conn_fd >= 0) {
            if (newConnectionCallback_) {
                newConnectionCallback_(conn_fd, peerAddresss);
            } else {
                sockets::close(conn_fd);
            }
        } else {
            LOG_ERROR << "failed to handleRead without address: " << errno;
        }
    }

    void Acceptor::listen() {
        loop_->assertInLoopThread();
        listening_ = true;
        serverSocket_.listen();
        acceptChannel_.enableReading();
    }
};
