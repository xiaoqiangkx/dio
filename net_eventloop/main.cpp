//
// Created by coolman on 16/7/23.
//


#include "EventLoop.h"
#include "Channel.h"
#include "TimerFd.h"

#include <muduo/base/Thread.h>
#include <muduo/base/CurrentThread.h>
#include <boost/bind.hpp>
#include <boost/function.hpp>
#include <muduo/base/Logging.h>


dio::EventLoop* g_loop;

void timeout() {
    LOG_INFO << "catch timeout event";
}

int main() {

    printf("hello eventloop\n");
    dio::EventLoop eventLoop;
    g_loop = &eventLoop;

    dio::TimerFd timerFd;
    timerFd.setTime(5000);
    dio::Channel channel(&eventLoop, timerFd.getFd());
    channel.setReadCallback(boost::bind(&timeout));
    channel.enableReading();

    eventLoop.updateChannel(&channel);

    eventLoop.loop();

    pthread_exit(NULL);
}

