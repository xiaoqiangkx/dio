//
// Created by coolman on 16/7/31.
//

#ifndef DIO_TIMER_H
#define DIO_TIMER_H

#include <dio/base/Timestamp.h>
#include <dio/base/Callbacks.h>
#include <boost/function.hpp>
#include <boost/noncopyable.hpp>


namespace dio {
class Timer: boost::noncopyable {
public:
    Timer(const dio::net::TimerCallback cb, dio::Timestamp when, double interval);

    void run() {
        timerCallback_();
    }

    dio::Timestamp expiration() const  { return expiration_; }
    bool repeat() const { return repeat_; }

    void restart(dio::Timestamp now);

private:
    const dio::net::TimerCallback timerCallback_;
    dio::Timestamp expiration_;
    const double interval_;
    const bool repeat_;
};
};

#endif //DIO_TIMER_H
