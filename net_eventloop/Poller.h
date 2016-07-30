//
// Created by coolman on 16/7/25.
//

#ifndef DIO_POLLER_H
#define DIO_POLLER_H

#include <map>
#include <vector>
#include "EventLoop.h"
#include <muduo/base/Timestamp.h>

struct pollfd;  // 为什么无法#include<pool.h>

namespace dio {

class Channel;

class Poller {
public:
    typedef std::vector<Channel*> ChannelList;

    muduo::Timestamp poll(int timeoutMs, ChannelList* activeChannels);

    Poller(EventLoop* loop);
    ~Poller();

    void updateChannel(Channel* channel);

    void assertInLoopThread() { ownerLoop_->assertInLoopThread(); }
private:
    void fillActiveChannels(int numEvents, ChannelList* activeChannels) const;

    typedef std::vector<struct pollfd> PollFdList;
    typedef std::map<int, Channel*> ChannelMap;

    PollFdList pollfds_;
    ChannelMap channels_;
    EventLoop* ownerLoop_;
};
}


#endif //DIO_POLLER_H
