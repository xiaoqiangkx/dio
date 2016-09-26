//
// Created by parallels on 9/3/16.
//

#ifndef PROJECT_INETADDRESS_H
#define PROJECT_INETADDRESS_H

#include <sys/socket.h>
#include <netinet/in.h>
#include <dio/base/Logging.h>
#include <arpa/inet.h>
#include <stdio.h>


namespace dio {
class InetAddress {
public:
    InetAddress(int port=0);
    InetAddress(const InetAddress& addr);
    InetAddress(struct sockaddr_in& addr);
    int port() const { return htons(addr_.sin_port); }
    struct sockaddr_in address() const { return addr_; }
    string toIpPort() {
        char *ip = inet_ntoa(addr_.sin_addr);
        char port_data[4];
        sprintf(port_data, ":%d", port());
        string ip_port(ip);
        ip_port.append(port_data);
        return ip_port;
    }
private:
    void initAddress(int port);
    struct sockaddr_in addr_;
};
};


#endif //PROJECT_INETADDRESS_H
