//
// Created by coolman on 16/7/31.
//

#ifndef DIO_TIMERQUEUE_H
#define DIO_TIMERQUEUE_H

#include <set>
#include <vector>
#include <muduo/base/Timestamp.h>
#include <muduo/net/Callbacks.h>
#include "TimerFd.h"
#include "EventFd.h"
#include "Channel.h"


namespace dio {

class EventLoop;
class Timer;
class TimerId;

class TimerQueue {

public:
    TimerQueue(EventLoop*);
    ~TimerQueue();

    EventLoop* ownerLoop() { return ownerLoop_; }

    TimerId addTimer(const muduo::net::TimerCallback& cb, muduo::Timestamp when, double interval);
    void cancelTimer(TimerId);

    void handleRead();
    void handleWakeup();

private:
    typedef std::pair<muduo::Timestamp, Timer*> Entry;
    typedef std::set<Entry> TimerList;

    TimerList timerList_;
    EventLoop* ownerLoop_;
    TimerFd timerFd_;
    EventFd eventFd_;
    Channel timerFdChannel_;
    Channel wakeChannel_;

    void resetTimerFd();
    bool insert(Timer*);

    std::vector<Entry> getExpired(muduo::Timestamp now);
};

};


#endif //DIO_TIMERQUEUE_H
