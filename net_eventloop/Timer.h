//
// Created by coolman on 16/7/31.
//

#ifndef DIO_TIMER_H
#define DIO_TIMER_H

#include <muduo/base/Timestamp.h>
#include <muduo/net/Callbacks.h>
#include <boost/function.hpp>
#include <boost/noncopyable.hpp>


namespace dio {
class Timer: boost::noncopyable {
public:
    Timer(const muduo::net::TimerCallback cb, muduo::Timestamp when, double interval);

    void run() {
        timerCallback_();
    }

    muduo::Timestamp expiration() const  { return expiration_; }
    bool repeat() const { return repeat_; }

    void restart(muduo::Timestamp now);

private:
    const muduo::net::TimerCallback timerCallback_;
    muduo::Timestamp expiration_;
    const double interval_;
    const bool repeat_;
};
};

#endif //DIO_TIMER_H
