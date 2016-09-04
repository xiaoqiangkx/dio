//
// Created by coolman on 16/7/31.
//

#include <dio/net/TimerQueue.h>
#include <dio/net/Timer.h>
#include <dio/net/EventLoop.h>
#include <boost/bind.hpp>
#include <dio/base/Logging.h>

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
        dio::Timestamp nowTimer(dio::Timestamp::now().secondsSinceEpoch() * 1000 * 1000);
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
        dio::Timestamp currentExpireTime = timerList_.begin()->first;
        int leftTimer = currentExpireTime.secondsSinceEpoch() - dio::Timestamp::now().secondsSinceEpoch();
        LOG_INFO << "leftTimer:" << leftTimer << "currentExpireTime:" << currentExpireTime.microSecondsSinceEpoch() <<
                    "nowTimer:" << dio::Timestamp::now().secondsSinceEpoch();
        timerFd_.setTime(leftTimer * 1000);
    }

    bool TimerQueue::insert(Timer *newTimer) {
        dio::Timestamp expireTime = newTimer->expiration();

        Entry newEntry(expireTime, newTimer);
        if (timerList_.size() == 0) {
            timerList_.insert(newEntry);
            return true;
        }

        dio::Timestamp currentExpireTime = timerList_.begin()->first;
        timerList_.insert(newEntry);
        if (expireTime < currentExpireTime) {
            return true;
        } else {
            return false;
        }

        return false;
    }

    TimerId TimerQueue::addTimer(const dio::net::TimerCallback& cb, dio::Timestamp when, double interval) {
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
        dio::Timestamp expire_timer = newTimer->expiration();
        TimerList::const_iterator it = timerList_.find(std::make_pair(expire_timer, newTimer));
        assert(it != timerList_.end());
        std::pair<dio::Timestamp, Timer*> targetItem(expire_timer, newTimer);
        timerList_.erase(targetItem);
    }

    std::vector<TimerQueue::Entry> TimerQueue::getExpired(dio::Timestamp now) {
        std::vector<Entry> expired;
        Entry sentry(now, reinterpret_cast<Timer*>(UINTPTR_MAX));
        TimerList::const_iterator it = timerList_.find(sentry);
        assert(it == timerList_.end() || now < it->first);

        std::copy(timerList_.begin(), it, std::back_inserter(expired));
        timerList_.erase(timerList_.begin(), it);

        return expired;
    }

};
