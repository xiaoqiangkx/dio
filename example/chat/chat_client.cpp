//
// Created by parallels on 9/25/16.
//

#include "ChatClient.h"

#include <dio/net/TcpConnection.h>
#include <dio/base/Thread.h>
#include <dio/net/EventLoop.h>


int main() {
    LOG_INFO <<"hello chatClient";
    dio::EventLoop eventLoop;

    dio::InetAddress remoteAddress(1998);
    dio::ChatClient chatClient(&eventLoop, remoteAddress);

    chatClient.start();
    eventLoop.loop();
    return 0;
}
