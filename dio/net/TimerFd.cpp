//
// Created by coolman on 16/7/30.
//

#include <dio/net/TimerFd.h>

#include <poll.h>
#include <dio/base/Logging.h>
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
//    ::poll(nullptr, 0, timeoutMs);
//    ::write(pipeFd_[1], "a", 1);
//    isTiming_ = false;
}

void TimerFd::setTime(int timeout) {
//    if (isTiming_) {
//        LOG_ERROR << "Timer is running.";
//        return;
//    }

//    std::thread timer_ = std::thread(boost::bind(&TimerFd::timerFunc, this, timeout));
//    timer_.detach();
}

void TimerFd::cancelTime() {
//    if (!isTiming_) {
//        LOG_ERROR << "Timer is not running.";
//        return;
//    }

//    isTiming_ = false;
}

};