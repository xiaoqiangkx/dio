//
// Created by parallels on 9/3/16.
//

#include <dio/net/Socket.h>
#include <dio/net/SocketOps.h>
#include <cerrno>

namespace dio {
Socket::Socket(const InetAddress& addr):
        localAddr_(addr.address())
{
    int sockfd = ::socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK | SOCK_CLOEXEC, IPPROTO_TCP);
    if (sockfd < 0) {
        LOG_ERROR << "Failed to create sockfd";
    }
    sockfd_ = sockfd;
}

Socket::Socket() {
    int sockfd = ::socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK | SOCK_CLOEXEC, IPPROTO_TCP);
    if (sockfd < 0) {
        LOG_ERROR << "Failed to create sockfd";
    }
    sockfd_ = sockfd;
}

Socket::Socket(int sockfd):
sockfd_(sockfd)
{

}

void Socket::setReuseAddr(bool resuseAddrFlag) {
    int optval = resuseAddrFlag ? 1 : 0;
    ::setsockopt(sockfd_, SOL_SOCKET, SO_REUSEADDR,
                 &optval, static_cast<socklen_t>(sizeof optval));
    // FIXME CHECK
}

void Socket::setReusePort(bool resusePortFlag) {
    int optval = resusePortFlag ? 1 : 0;
    int ret = ::setsockopt(sockfd_, SOL_SOCKET, SO_REUSEPORT,
                       &optval, static_cast<socklen_t>(sizeof optval));
    if (ret < 0)
    {
        LOG_SYSERR << "SO_REUSEPORT failed.";
    }
}

void Socket::bindAddress() {
    int ret = ::bind(sockfd_, (struct sockaddr *) &localAddr_, sizeof(localAddr_));
    if (ret < 0) {
        LOG_SYSERR << "failed to bind";
    }
}

int Socket::accept(InetAddress* address) {
    struct sockaddr_in addr;
    bzero(&addr, sizeof addr);
    int addrlen = sizeof(struct sockaddr_in);
    int connfd = ::accept4(sockfd_, (struct sockaddr*)&addr, (socklen_t*)&addrlen, SOCK_NONBLOCK | SOCK_CLOEXEC);
    if (connfd > 0) {
        LOG_INFO << "success";
    } else {
        LOG_ERROR << "Socket::accept error: " << errno;
    }

    return connfd;
}

int Socket::connect(InetAddress addr) {

    int ret = sockets::connect(sockfd_, addr.address());
    return ret;
}

void Socket::listen() {
    int ret = ::listen(sockfd_, SOMAXCONN);
    if (ret < 0) {
        LOG_ERROR << "Failed to listen address";
    }
}

void Socket::shutdownWrite() {
    sockets::shutdownWrite(sockfd_);
}

};