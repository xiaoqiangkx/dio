//
// Created by coolman on 16/7/23.
//

#include <dio/net/EventLoop.h>
#include <dio/net/Poller.h>
#include <signal.h>
#include <sys/socket.h>
#include <sys/types.h>

#include <dio/base/Logging.h>
#include <boost/bind.hpp>
#include <dio/net/SocketOps.h>


namespace dio {

    class IgnoreSigPipe {
    public:
        IgnoreSigPipe()
        {
            ::signal(SIGPIPE, SIG_IGN);
        }
    };
    IgnoreSigPipe initObj;

    __thread EventLoop* t_loopInThisThread = 0;

    const int EventLoop::kPollerTimeMs = 1000;

    EventLoop::EventLoop():
    looping_(false),
    threadId_(dio::CurrentThread::tid()),
    quit_(false),
    poller_(new Poller(this)),
    timerQueue_(this),
    callingPendingFunctor_(false)
    {
        if (socketpair(AF_UNIX, SOCK_STREAM, 0, wakeupFd_) < 0) {
          LOG_SYSFATAL << "Failed to init wakeup channel";
        }

        wakeupChannel_.reset(new Channel(this, wakeupFd_[0]));

        if (t_loopInThisThread)
        {
          LOG_FATAL << "Current thread already has an event loop "
                    << threadId_;
        }
        else
        {

          t_loopInThisThread = this;
        }

//        wakeupChannel_->setReadCallback(boost::bind(&EventLoop::handleRead, this));
//        wakeupChannel_->enableReading();
    }

    void EventLoop::handleRead() {
        uint64_t one = 1;
        ssize_t n = sockets::read(wakeupFd_[0], &one, sizeof one);
        if (n != sizeof one)
        {
            LOG_ERROR << "EventLoop::handleRead() reads " << n << " bytes instead of 8";
        }
    }

    void EventLoop::wakeup() {
        uint64_t one = 1;
        ssize_t n = sockets::write(wakeupFd_[1], &one, sizeof one);
        if (n != sizeof one)
        {
            LOG_ERROR << "EventLoop::wakeup() writes " << n << " bytes instead of 8";
        }
    }

    EventLoop::~EventLoop()
    {
        assert(!looping_);
        wakeupChannel_->disableAll();
        wakeupChannel_->remove();
        ::close(wakeupFd_[0]);
        ::close(wakeupFd_[1]);
        t_loopInThisThread = NULL;
    }

    void EventLoop::loop()
    {
        assert(!looping_);
        assertInLoopThread();

        looping_ = true;
        quit_ = false;

        LOG_INFO << "is looping";
        while (!quit_) {
            sleep(1);
            poller_->poll(kPollerTimeMs, &activeChannles);
            dio::Timestamp now = dio::Timestamp::now();
            for (ChannelList::const_iterator ch = activeChannles.begin(); ch != activeChannles.end(); ++ch) {
                (*ch)->handleEvent(now);
            }
            activeChannles.clear();
        }

        doPendingFunctors();
        LOG_INFO << "stop looping";
        looping_ = false;
    }

    EventLoop* EventLoop::getEventLoopOfCurrentThread()
    {
        return t_loopInThisThread;
    }

    void EventLoop::abortNotInLoopThread()
    {
        LOG_FATAL << "dio::abortNotInLoopThread - dio "
            << this << " was created in threadId_ = " << threadId_
            << ", current thread id = " <<  dio::CurrentThread::tid();
    }

    void EventLoop::quit()
    {
        quit_ = true;
        if (!isInLoopThread()) {
            wakeup();    // 直接唤醒EventLoop来切换
        }
    }

    void EventLoop::updateChannel(Channel* channel)
    {
        assert(channel->ownerLoop() == this);
        assertInLoopThread();
        poller_->updateChannel(channel);
    }

    void EventLoop::removeChannel(Channel *channel) {
        assert(channel->ownerLoop() == this);
        assertInLoopThread();
        poller_->removeChannel(channel);
    }

    TimerId EventLoop::addTimer(dio::Timestamp timestamp, const dio::net::TimerCallback &cb) {
        return timerQueue_.addTimer(cb, timestamp, 0.0);
    }

    void EventLoop::QueueInLoop(const Functor& cb) {
        {
            dio::MutexLockGuard lock(mutex_);
            pendingFunctors_.push_back(cb);
        }

        if (!isInLoopThread() || callingPendingFunctor_) {
            wakeup();
        }
    }

    void EventLoop::RunInLoop(const Functor& cb) {
        if (isInLoopThread()) {
            cb();
        } else {
            QueueInLoop(cb);
        }
    }

    void EventLoop::doPendingFunctors() {
        std::vector<Functor> functors;
        callingPendingFunctor_ = true;

        {
            dio::MutexLockGuard lock(mutex_);
            std::swap(functors, pendingFunctors_);
        }

        for (size_t i = 0; i < functors.size(); ++i) {
            pendingFunctors_[i]();
        }

        callingPendingFunctor_ = false;
    }

};
