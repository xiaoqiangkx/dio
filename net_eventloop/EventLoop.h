//
// Created by coolman on 16/7/23.
//

#ifndef MUDUO_RECIPE_EVENTLOOP_H
#define MUDUO_RECIPE_EVENTLOOP_H

#include <boost/core/noncopyable.hpp>
#include <muduo/base/CurrentThread.h>


namespace dio {

class EventLoop: boost::noncopyable {
public:
    EventLoop();
    ~EventLoop();
    void loop();

    void assertInLoopThread() {
        if (!isInLoopThread()) {
            abortNotInLoopThread();
        }
    }

    static EventLoop* getEventLoopOfCurrentThread();
private:
    bool looping_;
    const pid_t threadId_;  // ensure assign once

    bool isInLoopThread() const {
        return muduo::CurrentThread::tid() == threadId_;
    }

    void abortNotInLoopThread();
};

};

#endif //MUDUO_RECIPE_EVENTLOOP_H
