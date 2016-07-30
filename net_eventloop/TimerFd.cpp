//
// Created by coolman on 16/7/30.
//

#include "TimerFd.h"

#include <poll.h>
#include <muduo/base/Logging.h>
#include <thread>
#include <boost/bind.hpp>


namespace dio {

//TimerFd.cpp
TimerFd::TimerFd()
        : isTiming_(false) {
    if (::pipe(pipeFd_) == -1) {
        LOG_FATAL << "TimerFd not available.";
    }
}

TimerFd::~TimerFd() {
    ::close(pipeFd_[1]);
    ::close(pipeFd_[0]);
}

int TimerFd::getFd() const {
    return pipeFd_[0];
}

void TimerFd::timerFunc(int timeoutMs) {
    ::poll(nullptr, 0, timeoutMs);
    ::write(pipeFd_[1], "a", 1);
    isTiming_ = false;
}

void TimerFd::setTime(int timeout) {
    if (isTiming_) {
        LOG_ERROR << "Timer is running.";
        return;
    }

    isTiming_ = true;
    std::thread timer(boost::bind(&TimerFd::timerFunc, this, timeout));
    timer.detach();

}

};