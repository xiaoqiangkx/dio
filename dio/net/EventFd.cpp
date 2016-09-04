//
// Created by coolman on 16/8/1.
//

#include <dio/net/EventFd.h>
#include <dio/base/Logging.h>

namespace dio {
    EventFd::EventFd()
    : isEventing_(false){
        if (::pipe(pipeFd_) == -1) {
            LOG_FATAL << "EventFd not available.";
        }

    }

    EventFd::~EventFd() {
        ::close(pipeFd_[0]);
        ::close(pipeFd_[1]);
    }

    void EventFd::writeEvent() {
        // TODO: 未进行同步,所以可能会写多次,不过基本无危害
        if (isEventing_) {
            return;
        }

        isEventing_ = true;
        ::write(pipeFd_[1], " ", 1);
        isEventing_ = false;
    }

    int EventFd::getReadFd() const {
        return pipeFd_[0];
    }

    int EventFd::getWriteFd() const {
        return pipeFd_[1];
    }
};