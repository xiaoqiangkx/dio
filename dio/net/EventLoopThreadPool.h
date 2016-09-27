//
// Created by parallels on 9/28/16.
//

#ifndef PROJECT_EVENTLOOPTHREADPOOL_H
#define PROJECT_EVENTLOOPTHREADPOOL_H


#include <boost/core/noncopyable.hpp>
#include <vector>
#include <dio/net/EventLoopThread.h>
#include <boost/ptr_container/ptr_vector.hpp>

namespace dio {

class EventLoop;

class EventLoopThreadPool: public boost::noncopyable {
public:
    EventLoopThreadPool(EventLoop* baseLoop);
    void start();
    void setThreadNum(int num) { numThreads_ = num; }
    EventLoop* getNextLoop();

private:
    int numThreads_;
    EventLoop* baseLoop_;
    bool started_;
    boost::ptr_vector<EventLoopThread> threads_;
    std::vector<EventLoop*> loops_;
    int next_;

};
};


#endif //PROJECT_EVENTLOOPTHREADPOOL_H
