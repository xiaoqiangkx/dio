//
// Created by parallels on 9/3/16.
//

#ifndef PROJECT_SOCKETOPS_H
#define PROJECT_SOCKETOPS_H

#include <dio/base/Logging.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

namespace dio {

class Socket;
namespace sockets {
    void close(int fd);
    ssize_t read(int sockfd, void *buf, size_t count);
    ssize_t readv(int sockfd, const struct iovec *iov, int iovcnt);
    ssize_t write(int sockfd, const void *buf, size_t count);
    int connect(int sockfd, const struct sockaddr_in& addr);
    void shutdownWrite(int sockfd);
    bool isSelfConnect(int sockfd);

    int getSocketError(int sockfd);
    struct sockaddr_in getLocalAddr(int sockfd);
    struct sockaddr_in getPeerAddr(int sockfd);
};
};

#endif //PROJECT_SOCKETOPS_H
