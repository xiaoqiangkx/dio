//
// Created by parallels on 9/28/16.
//

#include <dio/net/EventLoopThread.h>
#include <dio/net/EventLoop.h>
#include <boost/bind.hpp>

namespace dio {

EventLoopThread::EventLoopThread():
        thread_(boost::bind(&EventLoopThread::threadFunc, this)),
        mutex_(),
        cond_(mutex_),
        existing_(false)
{

}

EventLoopThread::~EventLoopThread() {
    existing_ = true;
    if (loop_ != NULL) {
        loop_->quit();
        thread_.join();
    }
}

EventLoop* EventLoopThread::startLoop()
{
    assert(!thread_.started());
    thread_.start();

    MutexLockGuard lock(mutex_);
    while (loop_ != NULL)
    {
        cond_.wait();
    }

    return loop_;
}

void EventLoopThread::threadFunc()
{
    EventLoop loop;
    {
        MutexLockGuard lock(mutex_);
        loop_ = &loop;
        cond_.notify();
    }

    loop_->loop();
    loop_ = NULL;
}
};
