//
// Created by coolman on 16/7/23.
//

#include "EventLoop.h"
#include "Poller.h"

#include <muduo/base/Logging.h>


namespace dio {

    __thread EventLoop* t_loopInThisThread = 0;

    const int EventLoop::kPollerTimeMs = 1000;

    EventLoop::EventLoop():
    looping_(false),
    threadId_(muduo::CurrentThread::tid()),
    quit_(false),
    poller_(new Poller(this))
    {
      if (t_loopInThisThread)
      {
          LOG_FATAL << "Current thread already has an event loop "
                    << threadId_;
      }
      else
      {
          t_loopInThisThread = this;
      }
    }

    EventLoop::~EventLoop()
    {
        assert(!looping_);
        t_loopInThisThread = NULL;
    }

    void EventLoop::loop()
    {
        assert(!looping_);
        assertInLoopThread();

        looping_ = true;
        quit_ = false;

        LOG_TRACE << "is looping";
        while (!quit_) {
            poller_->poll(kPollerTimeMs, &activeChannles);
            for (ChannelList::const_iterator ch = activeChannles.begin(); ch != activeChannles.end(); ++ch) {
                (*ch)->handleEvent();
            }
        }

        LOG_TRACE << "stop looping";
        looping_ = false;
    }

    EventLoop* EventLoop::getEventLoopOfCurrentThread()
    {
        return t_loopInThisThread;
    }

    void EventLoop::abortNotInLoopThread()
    {
        LOG_FATAL << "net_eventloop::abortNotInLoopThread - net_eventloop "
            << this << " was created in threadId_ = " << threadId_
            << ", current thread id = " <<  muduo::CurrentThread::tid();
    }

    void EventLoop::quit()
    {
        quit_ = true;
        // wakeup();    # 直接唤醒EventLoop来切换
    }

    void EventLoop::updateChannel(Channel* channel)
    {
        // TODO 是否需要判断channel为空
        assert(channel->ownerLoop() == this);
        assertInLoopThread();
        poller_->updateChannel(channel);
    }

};
