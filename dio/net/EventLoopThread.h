//
// Created by parallels on 9/28/16.
//

#ifndef PROJECT_EVENTLOOPTHREAD_H
#define PROJECT_EVENTLOOPTHREAD_H


#include <boost/core/noncopyable.hpp>
#include <dio/base/Thread.h>
#include <dio/base/Condition.h>
#include <dio/base/Mutex.h>

namespace dio {

class EventLoop;

class EventLoopThread: public boost::noncopyable {
public:
    EventLoopThread();
    ~EventLoopThread();
    EventLoop* startLoop();
    void threadFunc();


private:
    EventLoop* loop_;
    Thread thread_;
    Condition cond_;
    MutexLock mutex_;
    bool existing_;
};

};


#endif //PROJECT_EVENTLOOPTHREAD_H
