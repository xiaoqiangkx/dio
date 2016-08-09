//
// Created by coolman on 16/8/9.
//

#ifndef DIO_ACCEPTOR_H
#define DIO_ACCEPTOR_H

#include <boost/core/noncopyable.hpp>
#include <muduo/net/InetAddress.h>
#include <muduo/net/Socket.h>


namespace dio {

class EventLoop;

class Acceptor: public boost::noncopyable {
private:
    EventLoop* loop_;
    Socket acceptSocket_;
};

}


#endif //DIO_ACCEPTOR_H
