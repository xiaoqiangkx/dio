//
// Created by coolman on 16/8/1.
//

#ifndef DIO_EVENTFD_H
#define DIO_EVENTFD_H


#include <boost/core/noncopyable.hpp>

namespace dio {

class EventFd: public boost::noncopyable {
private:
    int pipeFd_[2];
    bool isEventing_;

public:
    EventFd();
    ~EventFd();

    int getReadFd() const;
    int getWriteFd() const;

    void writeEvent();
};

};


#endif //DIO_EVENTFD_H
