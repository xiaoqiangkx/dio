//
// Created by parallels on 9/3/16.
//

#ifndef PROJECT_SOCKET_H
#define PROJECT_SOCKET_H

#include <dio/net/InetAddress.h>

namespace dio {

class Socket {
public:
    Socket();
    Socket(const InetAddress& addr);
    Socket(int sockfd);
    bool isValid() const { return sockfd_ > 0; }
    int fd() const { return sockfd_; }
    void setReuseAddr(bool resuseAddrFlag);
    void setReusePort(bool resusePortFlag);
    void bindAddress();

    int accept(InetAddress* address);
    int connect(InetAddress address);
    void shutdownWrite();
    void listen();
private:
    int sockfd_;
    struct sockaddr_in peerAddr_;
    struct sockaddr_in localAddr_;
};
};


#endif //PROJECT_SOCKET_H

