//
// Created by coolman on 16/7/31.
//

#include "Timer.h"

namespace dio {
    Timer::Timer(const muduo::net::TimerCallback cb, muduo::Timestamp when, double interval):
    timerCallback_(cb),
    expiration_(when),
    interval_(interval),
    repeat_(interval > 0.0)
    {

    }

    void Timer::restart(muduo::Timestamp now) {
        if (repeat_) {
            expiration_ = muduo::addTime(now, interval_);
        } else {
            expiration_ = muduo::Timestamp::invalid();
        }
    }
};