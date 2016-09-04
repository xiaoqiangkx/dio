//
// Created by parallels on 9/3/16.
//

#include <dio/net/InetAddress.h>

namespace dio {
void InetAddress::initAddress(int port=0) {
    LOG_INFO << "initAddress, port: " << port;
    bzero(&addr_, sizeof addr_);

    if (port != 0) {
        addr_.sin_family = AF_INET;
        addr_.sin_addr.s_addr = INADDR_ANY;
        addr_.sin_port = htons(port);
    }
}

InetAddress::InetAddress(int port) {
    initAddress(port);
}

InetAddress::InetAddress(const InetAddress& addr) {
    int port = addr.port();
    initAddress(port);
}

InetAddress::InetAddress(struct sockaddr_in& addr) {
    initAddress(addr.sin_port);
}
};
