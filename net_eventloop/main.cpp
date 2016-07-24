//
// Created by coolman on 16/7/23.
//


#include "EventLoop.h"
#include <muduo/base/Thread.h>
#include <muduo/base/CurrentThread.h>
#include <stdio.h>
#include <boost/bind.hpp>
#include <boost/function.hpp>


void threadFunc() {
    printf("start thread pid: %d, tid: %d \n", getpid(), muduo::CurrentThread::tid());

    dio::EventLoop eventLoop;
    eventLoop.loop();
}

int main() {

    printf("hello eventloop\n");
    dio::EventLoop eventLoop;
    eventLoop.loop();

    boost::function<void ()> f = boost::bind(&threadFunc);
    muduo::Thread thread(f);
    thread.start();
    pthread_exit(NULL);
}

