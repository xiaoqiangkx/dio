//
// Created by coolman on 16/7/23.
//

#include <sys/socket.h>
#include <iostream>
#include <vector>
#include <unistd.h>

#include <string.h>
#include <netinet/in.h>
#include <sys/poll.h>

int main() {
    std::cout << "start test_server" << std::endl;
    struct sockaddr_in bind_addr;
    int port = 5001;

    bzero(&bind_addr, sizeof bind_addr);
    bind_addr.sin_family = AF_INET;
    bind_addr.sin_addr.s_addr = INADDR_ANY;
    bind_addr.sin_port = htons(port);

    int sockfd = ::socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK | SOCK_CLOEXEC, IPPROTO_TCP);
    if (sockfd < 0) {
        std::cout << "Failed to create sockfd" << std::endl;
        exit(1);
    }

    ::bind(sockfd, (struct sockaddr *) &bind_addr, sizeof(bind_addr));
    int ret = ::listen(sockfd, SOMAXCONN);
    if (ret < 0) {
        std::cout << "Failed to listen address" << std::endl;
        exit(1);
    }

    std::vector<struct pollfd> pollfds;
    struct pollfd pfd;
    pfd.fd = sockfd;
    pfd.events = POLLIN | POLLPRI | POLLOUT;
    pollfds.push_back(pfd);

    while (true) {
        sleep(1);
        int numEvents = ::poll(&*pollfds.begin(), pollfds.size(), 1000);
        if (numEvents > 0) {
            std::cout << "Happened " << numEvents << std::endl;
            struct sockaddr_in addr;
            bzero(&addr, sizeof addr);
            int addrlen = sizeof(struct sockaddr_in);
            int connfd = ::accept4(sockfd, (struct sockaddr*)&addr, (socklen_t*)&addrlen, SOCK_NONBLOCK | SOCK_CLOEXEC);
            if (connfd > 0) {

                std::cout << "success" << std::endl;
            } else {
                std::cout << "error" << errno << std::endl;
            }
        } else if (numEvents == 0){
            std::cout << "Nothing happened" << std::endl;
        } else {
            std::cout << "poll encounter some error" << std::endl;
        }

    }
    return 0;
}

