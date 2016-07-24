//
// Created by coolman on 16/7/23.
//

#include "EventLoop.h"
#include <muduo/base/Logging.h>
#include <poll.h>
#include <stdio.h>

using namespace muduo;


namespace dio {
    __thread EventLoop* t_loopInThisThread = 0;

    EventLoop::EventLoop():
    looping_(false), threadId_(muduo::CurrentThread::tid())
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

        printf("is looping\n");
        ::poll(NULL, 0, 5 * 1000);

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

};
