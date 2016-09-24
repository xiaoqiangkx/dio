//
// Created by coolman on 16/7/23.
//

#ifndef DIO_EVENTLOOP_H
#define DIO_EVENTLOOP_H

#include <boost/scoped_ptr.hpp>
#include <boost/noncopyable.hpp>
#include <dio/base/CurrentThread.h>
#include <vector>
#include <dio/base/Timestamp.h>
#include <dio/base/Callbacks.h>
#include <dio/base/Mutex.h>

#include <dio/net/TimerQueue.h>
#include <dio/net/Channel.h>
#include <dio/net/TimerId.h>


namespace dio {

class Poller;

class EventLoop: boost::noncopyable {
public:
    typedef std::vector<Channel*> ChannelList;
    typedef boost::function<void()> Functor;

    EventLoop();
    ~EventLoop();
    void loop();

    void assertInLoopThread() {
        if (!isInLoopThread()) {
            abortNotInLoopThread();
        }
    }

    void quit();
    void updateChannel(Channel* channel);
    void removeChannel(Channel* channel);

    void QueueInLoop(const Functor& cb);

    void RunInLoop(const Functor& cb);

    void doPendingFunctors();

    TimerId runAt(dio::Timestamp timestamp, const dio::net::TimerCallback &cb);
    TimerId runAfter(double delay, const dio::net::TimerCallback &cb);
    TimerId runEvery(double interval, const dio::net::TimerCallback &cb);

    static EventLoop* getEventLoopOfCurrentThread();

    bool isInLoopThread() const {
        return dio::CurrentThread::tid() == threadId_;
    }

private:
    bool looping_;
    const pid_t threadId_;  // ensure assign once
    bool quit_;
    boost::scoped_ptr<Poller> poller_;
    ChannelList activeChannles;
    TimerQueue timerQueue_;
    std::vector<Functor> pendingFunctors_;

    boost::scoped_ptr<Channel> wakeupChannel_;
    int wakeupFd_[2];

    dio::MutexLock mutex_;
    bool callingPendingFunctor_;

    static const int kPollerTimeMs;

    void abortNotInLoopThread();
    void handleRead();
    void wakeup();
};

};

#endif //DIO_EVENTLOOP_H
