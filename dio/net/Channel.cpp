//
// Created by coolman on 16/7/25.
//

#include <dio/net/Channel.h>
#include <dio/net/EventLoop.h>

#include <poll.h>
#include <dio/base/Logging.h>


namespace dio {

    const int Channel::kNoneEvent = 0;
    const int Channel::kReadEvent = POLLIN | POLLPRI;
    const int Channel::kWriteEvent = POLLOUT;

    Channel::Channel(EventLoop *loop, int fd):
        index_(-1),
        events_(0),
        revents_(0),
        loop_(loop),
        fd_(fd),
        eventHandling_(false)
    {

    }

    Channel::~Channel() {
        assert(!eventHandling_);
    }

    void Channel::update()
    {
        loop_->updateChannel(this);
    }

    void Channel::remove() {
        loop_->removeChannel(this);
    }


    void Channel::handleEvent(dio::Timestamp timestamp) {

        eventHandling_ = true;
        if (events_ & POLLNVAL) {
            LOG_WARN << "Channel::handleEvent POLLNVAL";
        }

        if ((events_ & POLLHUP) && !(events_ & POLLIN)) {
            if (closeCallback_) closeCallback_();
        }

        if (events_ & (POLLERR | POLLNVAL)) {
            if (errorCallback_) errorCallback_();
        }

        // TODO 此处需要处理哪些POLL事件??
        if (events_ & (POLLIN | POLLPRI)) {
            if (readCallback_) readCallback_(timestamp);
        }

        if (events_ & POLLOUT) {
            if (writeCallback_) writeCallback_();
        }

        eventHandling_ = false;
    }
}
