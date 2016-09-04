//
// Created by parallels on 9/3/16.
//

#include <dio/net/SocketOps.h>
#include <cerrno>

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

void shutdownWrite(int sockfd)
{
    if (::shutdown(sockfd, SHUT_WR) < 0)
    {
        LOG_SYSERR << "sockets::shutdownWrite";
    }
}
};
};