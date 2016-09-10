//
// Created by coolman on 16/7/25.
//

#include <dio/net/Channel.h>
#include <dio/net/Poller.h>

#include <poll.h>
#include <dio/base/Logging.h>


namespace dio {

    Poller::Poller(EventLoop *loop) : ownerLoop_(loop) { }

    Poller::~Poller() { }

    dio::Timestamp Poller::poll(int timeoutMs, ChannelList *activeChannels) {

        int numEvents = ::poll(&*pollfds_.begin(), pollfds_.size(), timeoutMs);
        dio::Timestamp now(dio::Timestamp::now());
        if (numEvents > 0) {
            fillActiveChannels(numEvents, activeChannels);
        } else if (numEvents == 0) {
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
            assert(pfd.fd == channel->fd() || pfd.fd == -channel->fd() - 1);
            pfd.events = channel->events();
            pfd.revents = 0;
            if (channel->isNoneEvents()) {
                pfd.fd = -channel->fd() - 1;
            }
        }
    }

    void Poller::removeChannel(Channel *channel) {
        // change the position of channel and the last channel
        assertInLoopThread();
        assert(channels_.find(channel->fd()) != channels_.end());
        assert(channels_[channel->fd()] == channel);
        assert(channel->isNoneEvents());
        int idx = channel->get_index();
        int pollfd_size = static_cast<int>(pollfds_.size());
        assert (idx >= 0 && idx < pollfd_size);
        assert(channels_[idx] == channel);

        if (idx == pollfd_size - 1) {
            channels_.erase(channel->fd());
            pollfds_.pop_back();
        } else {
            std::iter_swap(pollfds_.end() - 1, pollfds_.begin() + idx);
            int realFd = pollfds_.back().fd;
            if (realFd < 0) {
                realFd = - realFd - 1;
            }
            channels_[realFd]->set_index(idx);
            pollfds_.pop_back();
        }
    }
};