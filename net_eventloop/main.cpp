//
// Created by coolman on 16/7/23.
//


#include "EventLoop.h"
#include "Channel.h"
#include "TimerFd.h"

#include <muduo/base/Thread.h>
#include <muduo/base/CurrentThread.h>
#include <boost/bind.hpp>
#include <muduo/base/Logging.h>
#include <muduo/base/Timestamp.h>


dio::EventLoop* g_loop;

void timeout() {
    LOG_INFO << "catch timeout event";
}

int main() {

    printf("hello eventloop\n");
    dio::EventLoop eventLoop;
    g_loop = &eventLoop;

    muduo::Timestamp nowTime = muduo::Timestamp::now();
    muduo::Timestamp theTimer((nowTime.secondsSinceEpoch() + 5) * 1000 * 1000);   // 5s后触发事件
    LOG_INFO << "THE tIME" << theTimer.secondsSinceEpoch();
    eventLoop.addTimer(theTimer, boost::bind(timeout));

    eventLoop.loop();

    pthread_exit(NULL);
}

