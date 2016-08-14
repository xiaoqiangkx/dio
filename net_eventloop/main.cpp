//
// Created by coolman on 16/7/23.
//


#include "EventLoop.h"
#include "Channel.h"
#include "TimerFd.h"
#include "Acceptor.h"

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

void newConnection(int fd, const muduo::net::InetAddress &address)
{
    LOG_INFO << "newConnection Build from address" << address.toIpPort();
    ::write(fd, "hello world\n", 12);
    muduo::net::sockets::close(fd);
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
    dio::Acceptor acceptor(&eventLoop, listenAddress);
    acceptor.setNewConnectionCallback(newConnection);
    acceptor.listnen();

    eventLoop.loop();

    pthread_exit(NULL);
}

