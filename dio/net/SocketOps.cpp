//
// Created by parallels on 9/3/16.
//

#include <dio/net/SocketOps.h>
#include <cerrno>
#include <arpa/inet.h>

namespace dio {

namespace sockets {

int getSocketError(int sockfd) {
    int optval;
    socklen_t optlen = static_cast<socklen_t>(sizeof optval);

    if (::getsockopt(sockfd, SOL_SOCKET, SO_ERROR, &optval, &optlen) < 0) {
        return errno;
    }
    else {
        return optval;
    }
}

struct sockaddr_in getLocalAddr(int sockfd) {
    struct sockaddr_in localAddr;
    bzero(&localAddr, sizeof localAddr);
    socklen_t addrlen = static_cast<socklen_t>(sizeof localAddr);
    if (::getsockname(sockfd, (struct sockaddr *) &localAddr, &addrlen) < 0) {
        LOG_SYSERR << "sockets::getLocalAddr";
    }
    return localAddr;
}


struct sockaddr_in getPeerAddr(int sockfd) {
    struct sockaddr_in peerAddr;
    bzero(&peerAddr, sizeof peerAddr);
    socklen_t addrlen = static_cast<socklen_t>(sizeof peerAddr);
    if (::getpeername(sockfd, (struct sockaddr *) &peerAddr, &addrlen) < 0) {
        LOG_SYSERR << "sockets::getPeerAddr";
    }
    return peerAddr;
}

void close(int fd) {
    if (::close(fd) < 0)
    {
        LOG_SYSERR << "sockets::close";
    }
}

ssize_t read(int sockfd, void *buf, size_t count)
{
    return ::read(sockfd, buf, count);
}

ssize_t readv(int sockfd, const struct iovec *iov, int iovcnt)
{
    return ::readv(sockfd, iov, iovcnt);
}

ssize_t write(int sockfd, const void *buf, size_t count)
{
    return ::write(sockfd, buf, count);
}

int connect(int sockfd, const struct sockaddr_in& addr)
{
    return ::connect(sockfd, (struct sockaddr *)(&addr), static_cast<socklen_t>(sizeof addr));
}

void shutdownWrite(int sockfd)
{
    LOG_INFO << "Sockets::shutdown Write sockfd:" << sockfd;
    if (::shutdown(sockfd, SHUT_WR) < 0)
    {
        LOG_SYSERR << "sockets::shutdownWrite";
    }
}

bool isSelfConnect(int sockfd)
{
    struct sockaddr_in localaddr = getLocalAddr(sockfd);
    struct sockaddr_in peeraddr = getPeerAddr(sockfd);

    return localaddr.sin_port == peeraddr.sin_port
           && localaddr.sin_addr.s_addr == peeraddr.sin_addr.s_addr;
}

};
};