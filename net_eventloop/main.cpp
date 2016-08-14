//
// Created by coolman on 16/7/23.
//


#include "EventLoop.h"
#include "Channel.h"
#include "TimerFd.h"
#include "Acceptor.h"
#include "TcpServer.h"
#include "TcpConnection.h"

#include <muduo/base/Thread.h>
#include <muduo/base/CurrentThread.h>
#include <boost/bind.hpp>
#include <muduo/base/Logging.h>
#include <muduo/base/Timestamp.h>
#include <muduo/net/InetAddress.h>


dio::EventLoop* g_loop;

void timeout() {
    LOG_INFO << "catch timeout event";
}

void newConnection(const dio::TcpConnectionPtr& connection)
{
    LOG_INFO << "hello world";
}

int main() {

    LOG_INFO <<"hello eventloop";
    dio::EventLoop eventLoop;
    g_loop = &eventLoop;

//    muduo::Timestamp nowTime = muduo::Timestamp::now();
//    muduo::Timestamp theTimer((nowTime.secondsSinceEpoch() + 5) * 1000 * 1000);   // 5s后触发事件
//    LOG_INFO << "THE tIME" << theTimer.secondsSinceEpoch();
//    eventLoop.addTimer(theTimer, boost::bind(timeout));

    muduo::net::InetAddress listenAddress(1998);
//    dio::Acceptor acceptor(&eventLoop, listenAddress);
//    acceptor.setNewConnectionCallback(newConnection);
//    acceptor.listnen();
    dio::TcpServer tcpServer(&eventLoop, listenAddress);
    tcpServer.setConnectionCallback(newConnection);
    tcpServer.start();

    eventLoop.loop();

    pthread_exit(NULL);
}

