//
// Created by coolman on 16/7/31.
//

#ifndef DIO_TIMERQUEUE_H
#define DIO_TIMERQUEUE_H

#include <set>
#include <vector>
#include <dio/base/Timestamp.h>
#include <dio/base/Callbacks.h>
#include <dio/net/TimerFd.h>
#include <dio/net/EventFd.h>
#include <dio/net/Channel.h>


namespace dio {

class EventLoop;
class Timer;
class TimerId;

class TimerQueue {

public:
    TimerQueue(EventLoop*);
    ~TimerQueue();

    EventLoop* ownerLoop() { return ownerLoop_; }

    TimerId addTimer(const dio::net::TimerCallback& cb, dio::Timestamp when, double interval);
    void cancelTimer(TimerId);

    void handleRead();
    void handleWakeup();

private:
    typedef std::pair<dio::Timestamp, Timer*> Entry;
    typedef std::set<Entry> TimerList;

    TimerList timerList_;
    EventLoop* ownerLoop_;
    TimerFd timerFd_;
    EventFd eventFd_;
    Channel timerFdChannel_;
    Channel wakeChannel_;

    void resetTimerFd();
    bool insert(Timer*);

    std::vector<Entry> getExpired(dio::Timestamp now);
};

};


#endif //DIO_TIMERQUEUE_H
