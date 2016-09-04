//
// Created by coolman on 16/7/31.
//

#include <dio/net/Timer.h>

namespace dio {
    Timer::Timer(const dio::net::TimerCallback cb, dio::Timestamp when, double interval):
    timerCallback_(cb),
    expiration_(when),
    interval_(interval),
    repeat_(interval > 0.0)
    {

    }

    void Timer::restart(dio::Timestamp now) {
        if (repeat_) {
            expiration_ = dio::addTime(now, interval_);
        } else {
            expiration_ = dio::Timestamp::invalid();
        }
    }
};