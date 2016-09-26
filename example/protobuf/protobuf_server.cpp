//
// Created by parallels on 9/26/16.
//

#include "ProtobufServer.h"

#include <dio/net/TcpConnection.h>
#include <dio/base/Thread.h>


int main() {
    LOG_INFO <<"hello chatServer";
    dio::EventLoop eventLoop;

    dio::InetAddress listenAddress(1998);
    dio::ProtobufServer chatServer(&eventLoop, listenAddress);

    chatServer.start();
    eventLoop.loop();
    return 0;
}
