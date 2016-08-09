//
// Created by coolman on 16/7/25.
//

#include "Channel.h"
#include "Poller.h"

#include <poll.h>
#include <muduo/base/Logging.h>
#include <muduo/base/Timestamp.h>


namespace dio {

    Poller::Poller(EventLoop *loop) : ownerLoop_(loop) { }

    Poller::~Poller() { }

    muduo::Timestamp Poller::poll(int timeoutMs, ChannelList *activeChannels) {
        int numEvents = ::poll(&*pollfds_.begin(), pollfds_.size(), timeoutMs);
        muduo::Timestamp now(muduo::Timestamp::now());
        if (numEvents > 0) {
//            LOG_INFO << numEvents << " evnents happend";
            fillActiveChannels(numEvents, activeChannels);
        } else if (numEvents == 0) {
            LOG_INFO << "Nothing happened";
        } else {
            LOG_INFO << "Poller::poll()";
        }

        return now;
    }

    void Poller::fillActiveChannels(int numEvents, ChannelList *activeChannels) const {
        for (PollFdList::const_iterator pfd = pollfds_.begin(); pfd != pollfds_.end() &&
                                                                numEvents > 0; ++pfd) {
            if (pfd->revents > 0) {
                --numEvents;
                ChannelMap::const_iterator ch = channels_.find(pfd->fd);
                assert(ch != channels_.end());
                Channel *channel = ch->second;
                assert(channel->fd() == pfd->fd);
                channel->set_revents(pfd->revents);
                activeChannels->push_back(channel);
            }
        }
    }

    void Poller::updateChannel(Channel *channel) {
        assertInLoopThread();
        if (channel->get_index() < 0) {
            // a new channel
            assert(channels_.find(channel->fd()) == channels_.end());
            struct pollfd pfd;
            pfd.fd = channel->fd();
            pfd.events = static_cast<short>(channel->events());
            pfd.revents = 0;
            pollfds_.push_back(pfd);
            channels_[pfd.fd] = channel;

            int index = static_cast<int>(pollfds_.size()) - 1;
            channel->set_index(index);

        } else {
            // an old channel
            assert(channels_.find(channel->fd()) != channels_.end());
            assert(channels_[channel->fd()] == channel);
            int idx = channel->get_index();
            assert(idx >= 0 && idx < static_cast<int>(pollfds_.size()));
            struct pollfd &pfd = pollfds_[idx];
            assert(pfd.fd == channel->fd() || pfd.fd == -1);
            pfd.events = channel->events();
            pfd.revents = 0;
            if (channel->isNoneEvents()) {
                pfd.fd = -1;
            }
        }
    }
};