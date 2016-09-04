//
// Created by coolman on 16/7/30.
//

#ifndef DIO_TIMERFD_H
#define DIO_TIMERFD_H


// 作者：Cat-Cat
// 链接：https://www.zhihu.com/question/48014224/answer/108773757
// 来源：知乎
// 著作权归作者所有，转载请联系作者获得授权。

#include <boost/noncopyable.hpp>


namespace dio {

class TimerFd: public boost::noncopyable
{
private:
    int pipeFd_[2];
    bool isTiming_;
public:
    TimerFd();
    ~TimerFd();

    int getFd() const;
    void setTime(int timeout);
    void cancelTime();
    void timerFunc(int timeoutMs);
};
};


#endif //DIO_TIMERFD_H
