//
// Created by parallels on 9/20/16.
//

#include <dio/net/Connector.h>
#include <boost/bind.hpp>
#include <dio/net/EventLoop.h>
#include <dio/net/SocketOps.h>

namespace dio {

Connector::Connector(EventLoop *eventLoop, InetAddress inetAddress):
    serverAddr_(inetAddress),
    loop_(eventLoop),
    connect_(false),
    state_(kDisconnected),
    retryDelayMs_(kInitRetryMs)
{
}

void Connector::startInLoop() {
    assert(state_ == kDisconnected);

    loop_->assertInLoopThread();
    clientSocket_ = Socket();
    int ret = clientSocket_.connect(serverAddr_);
    int savedErrno = (ret == 0) ? 0 : errno;

    int sockfd = clientSocket_.fd();
    switch (savedErrno) {
        case 0:
        case EINPROGRESS:
        case EINTR:
        case EISCONN:
            connecting(sockfd);
            break;

        case EAGAIN:
        case EADDRINUSE:
        case EADDRNOTAVAIL:
        case ECONNREFUSED:
        case ENETUNREACH:
            retry(sockfd);
            break;

        case EACCES:
        case EPERM:
        case EAFNOSUPPORT:
        case EALREADY:
        case EBADF:
        case EFAULT:
        case ENOTSOCK:
            LOG_SYSERR << "connect error in Connector::startInLoop " << savedErrno;
            sockets::close(sockfd);
            break;

        default:
            LOG_SYSERR << "Unexpected error in Connector::startInLoop " << savedErrno;
            sockets::close(sockfd);
            // connectErrorCallback_();
            break;
    }
}

void Connector::start() {
    connect_ = true;
    loop_->RunInLoop(boost::bind(&Connector::startInLoop, this));
}

void Connector::stop() {
    connect_ = false;
    loop_->RunInLoop(boost::bind(&Connector::stopInLoop, this));
}

void Connector::stopInLoop() {
    loop_->assertInLoopThread();

    if (state_ == kConnected) {
        setState(kDisconnected);
        int sockfd = removeAndResetChannel();
        retry(sockfd);
    }
}

int Connector::removeAndResetChannel() {
    channelPtr_->disableAll();
    channelPtr_->remove();

    int sockfd = channelPtr_->fd();
    loop_->QueueInLoop(boost::bind(&Connector::resetChannel, this));    // avoid to deconstructor Channel in handleEvent
    return sockfd;
}

void Connector::resetChannel()
{
    channelPtr_.reset();
}

void Connector::handleWrite() {
    if (state_ == kConnecting) {
        int sockfd = removeAndResetChannel();
        int err = sockets::getSocketError(sockfd);
        if (err) {
            LOG_WARN << "Connector::handleWrite - SO_ERROR = "
                     << err << " " << strerror_tl(err);
            retry(sockfd);
        }
        else if (sockets::isSelfConnect(sockfd)) {
            LOG_WARN << "Connector::handleWrite - Self connect";
            retry(sockfd);
        }
        else {
            setState(kConnected);
            if (connect_) {
                newConnectionCallback_(sockfd);
            }
            else {
                sockets::close(sockfd);
            }
        }
    } else {
        assert(state_ == kDisconnected);
    }
}

void Connector::handleError() {

}

void Connector::retry(int sockfd) {
    setState(kDisconnected);
    sockets::close(sockfd);
    if (connect_) {
        loop_->runAfter(retryDelayMs_ / 1000.0, boost::bind(&Connector::startInLoop, this));
        retryDelayMs_ = std::min(retryDelayMs_ * 2, kMaxRetryMs);
    } else {
        LOG_ERROR << "Connector is already closed";
    }
}

void Connector::connecting(int sockfd) {
    setState(kConnecting);
    assert(!channelPtr_);
    connect_ = true;
    channelPtr_.reset(new Channel(loop_, sockfd));
    channelPtr_->setWriteCallback(boost::bind(&Connector::handleWrite, this));
    channelPtr_->setErrorCallback(boost::bind(&Connector::handleError, this));
    channelPtr_->enableWriting();
}

};
