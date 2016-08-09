//
// Created by coolman on 16/7/31.
//

#include "TimerQueue.h"
#include "Timer.h"
#include "EventLoop.h"
#include "TimerId.h"
#include <boost/bind.hpp>
#include <stdint.h>
#include <algorithm>
#include <muduo/base/Logging.h>

namespace dio {
    TimerQueue::TimerQueue(EventLoop *loop):
    ownerLoop_(loop),
    timerFd_(),
    eventFd_(),
    timerFdChannel_(loop, timerFd_.getFd()),
    wakeChannel_(loop, eventFd_.getReadFd())
    {
        // TODO: 初始化所有的channel, 此处的timerFd如何更新数据
        timerFdChannel_.setReadCallback(boost::bind(&TimerQueue::handleRead, this));
        timerFdChannel_.enableReading();
        ownerLoop_->updateChannel(&timerFdChannel_);

        wakeChannel_.setReadCallback(boost::bind(&TimerQueue::handleWakeup, this));
        wakeChannel_.enableReading();
        ownerLoop_->updateChannel(&wakeChannel_);
    }

    TimerQueue::~TimerQueue() {

    }

    void TimerQueue::handleRead()
    {

        // 根据当前的时间,找出所有过期的Timer,并且处理其中的事件
        muduo::Timestamp nowTimer(muduo::Timestamp::now().secondsSinceEpoch() * 1000 * 1000);
//        LOG_INFO << "Timer" << nowTimer.secondsSinceEpoch();
        std::vector<Entry> expired = getExpired(nowTimer);
//        LOG_INFO << "handle_event...read:" << expired.size();
        for (std::vector<Entry>::const_iterator it = expired.begin(); it != expired.end(); ++it) {
            Timer* timer = it->second;
            timer->run();
        }
    }

    void TimerQueue::handleWakeup() {
        LOG_INFO << "handle wakeup";
    }

    void TimerQueue::resetTimerFd() {
        // TODO
        LOG_INFO << "resetTimerFd";
        timerFd_.cancelTime();  // 中断前一次Timer
        assert(timerList_.size() != 0);
        muduo::Timestamp currentExpireTime = timerList_.begin()->first;
        int leftTimer = currentExpireTime.secondsSinceEpoch() - muduo::Timestamp::now().secondsSinceEpoch();
        LOG_INFO << "leftTimer:" << leftTimer << "currentExpireTime:" << currentExpireTime.microSecondsSinceEpoch() <<
                    "nowTimer:" << muduo::Timestamp::now().secondsSinceEpoch();
        timerFd_.setTime(leftTimer * 1000);
    }

    bool TimerQueue::insert(Timer *newTimer) {
        muduo::Timestamp expireTime = newTimer->expiration();

        Entry newEntry(expireTime, newTimer);
        if (timerList_.size() == 0) {
            timerList_.insert(newEntry);
            return true;
        }

        muduo::Timestamp currentExpireTime = timerList_.begin()->first;
        timerList_.insert(newEntry);
        if (expireTime < currentExpireTime) {
            return true;
        } else {
            return false;
        }

        return false;
    }

    TimerId TimerQueue::addTimer(const muduo::net::TimerCallback& cb, muduo::Timestamp when, double interval) {
        ownerLoop_->assertInLoopThread();
        Timer *newTimer = new Timer(cb, when, interval);

        bool earliestChanged = insert(newTimer);

        if (earliestChanged) {
            resetTimerFd();
        }

        return TimerId(newTimer);
    }

    void TimerQueue::cancelTimer(TimerId timerId) {
        // TODO: reset
        Timer* newTimer = timerId.timer_;
        muduo::Timestamp expire_timer = newTimer->expiration();
        TimerList::const_iterator it = timerList_.find(std::make_pair(expire_timer, newTimer));
        assert(it != timerList_.end());
        std::pair<muduo::Timestamp, Timer*> targetItem(expire_timer, newTimer);
        timerList_.erase(targetItem);
    }

    std::vector<TimerQueue::Entry> TimerQueue::getExpired(muduo::Timestamp now) {
        std::vector<Entry> expired;
        Entry sentry(now, reinterpret_cast<Timer*>(UINTPTR_MAX));
        TimerList::const_iterator it = timerList_.find(sentry);
        assert(it == timerList_.end() || now < it->first);

        std::copy(timerList_.begin(), it, std::back_inserter(expired));
        timerList_.erase(timerList_.begin(), it);

        return expired;
    }

};
