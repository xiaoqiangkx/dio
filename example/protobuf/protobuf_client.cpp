//
// Created by parallels on 9/26/16.
//

#include "ProtobufClient.h"

#include <dio/net/TcpConnection.h>
#include <dio/base/Thread.h>
#include <dio/net/EventLoop.h>


int main() {
    LOG_INFO <<"hello chatClient";
    dio::EventLoop eventLoop;

    dio::InetAddress remoteAddress(1998);
    dio::ProtobufClient chatClient(&eventLoop, remoteAddress);

    chatClient.start();
    eventLoop.loop();
    return 0;
}