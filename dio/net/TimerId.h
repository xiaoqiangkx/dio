//
// Created by coolman on 16/7/31.
//

#include <dio/base/copyable.h>
#include <stdint.h>

#ifndef DIO_TIMERID_H
#define DIO_TIMERID_H

namespace dio {
class Timer;
class TimerQueue;

class TimerId: public dio::copyable {
public:
    TimerId(Timer* timer)
            :timer_(timer)
    {

    }
private:
    friend class TimerQueue;

    Timer* timer_;
};

};

#endif //DIO_TIMERID_H
