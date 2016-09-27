//
// Created by parallels on 9/28/16.
//

#include <dio/net/EventLoopThreadPool.h>
#include <dio/net/EventLoop.h>

namespace dio {
    EventLoopThreadPool::EventLoopThreadPool(EventLoop* baseLoop):
            baseLoop_(baseLoop),
            next_(0),
            started_(false)
    {

    }

    void EventLoopThreadPool::start() {
        assert(!started_);
        baseLoop_->assertInLoopThread();

        started_ = true;

        for (int i = 0; i < numThreads_; ++i) {
            EventLoopThread *t = new EventLoopThread();
            EventLoop *loop = t->startLoop();
            loops_.push_back(loop);
        }
    }

    EventLoop* EventLoopThreadPool::getNextLoop() {
        baseLoop_->assertInLoopThread();
        assert(started_);
        EventLoop* loop = baseLoop_;

        if (!loops_.empty())
        {
            // round-robin
            loop = loops_[next_];
            ++next_;
            if (implicit_cast<size_t>(next_) >= loops_.size())
            {
                next_ = 0;
            }
        }
        return loop;
    }
};