//
// Created by coolman on 16/7/25.
//

#include "Channel.h"
#include "EventLoop.h"

#include <poll.h>
#include <muduo/base/Logging.h>


namespace dio {

    const int Channel::kNoneEvent = 0;
    const int Channel::kReadEvent = POLLIN | POLLPRI;
    const int Channel::kWriteEvent = POLLOUT;

    Channel::Channel(EventLoop *loop, int fd):
        index_(-1),
        revents_(0),
        events_(0),
        loop_(loop),
        fd_(fd)
    {

    }

    Channel::~Channel() { }

    void Channel::update()
    {
        loop_->updateChannel(this);
    }

    void Channel::handleEvent() {
        if (events_ & POLLNVAL) {
            LOG_WARN << "Channel::handleEvent POLLNVAL";
        }

        if (events_ & (POLLERR | POLLNVAL)) {
            if (errorCallback_) errorCallback_();
        }

        // TODO 此处需要处理哪些POLL事件??
        if (events_ & (POLLIN | POLLPRI)) {
            if (readCallback_) readCallback_();
        }

        if (events_ & POLLOUT) {
            if (writeCallback_) writeCallback_();
        }
    }
}
