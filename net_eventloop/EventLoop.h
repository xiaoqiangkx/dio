//
// Created by coolman on 16/7/23.
//

#ifndef DIO_EVENTLOOP_H
#define DIO_EVENTLOOP_H

#include <boost/core/noncopyable.hpp>
#include <boost/scoped_ptr.hpp>
#include <muduo/base/CurrentThread.h>
#include <vector>
#include <muduo/base/Timestamp.h>
#include <muduo/net/Callbacks.h>

#include "TimerQueue.h"
#include "Channel.h"
#include "TimerId.h"


namespace dio {

class Poller;

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

    void quit();
    void updateChannel(Channel* channel);

    TimerId addTimer(muduo::Timestamp timestamp, const muduo::net::TimerCallback &cb);

    static EventLoop* getEventLoopOfCurrentThread();

    typedef std::vector<Channel*> ChannelList;
private:
    bool looping_;
    const pid_t threadId_;  // ensure assign once
    bool quit_;
    boost::scoped_ptr<Poller> poller_;
    ChannelList activeChannles;
    TimerQueue timerQueue_;

    static const int kPollerTimeMs;

    bool isInLoopThread() const {
        return muduo::CurrentThread::tid() == threadId_;
    }

    void abortNotInLoopThread();
};

};

#endif //DIO_EVENTLOOP_H
