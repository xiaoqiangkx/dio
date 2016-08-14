//
// Created by coolman on 16/8/9.
//

#ifndef DIO_ACCEPTOR_H
#define DIO_ACCEPTOR_H

#include <boost/noncopyable.hpp>
#include <muduo/net/InetAddress.h>
#include "Channel.h"
#include "Socket.h"
#include "SocketsOps.h"


namespace dio {

class EventLoop;

class Acceptor: public boost::noncopyable {
public:

    typedef boost::function<void (int, const muduo::net::InetAddress&)> NewConnectionCallback;
    Acceptor(EventLoop*, const muduo::net::InetAddress&);

    void setNewConnectionCallback(const NewConnectionCallback& cb) {
        newConnectionCallback_ = cb;
    }

    void listnen();
private:
    EventLoop* loop_;
    muduo::net::Socket serverSocket_;
    Channel acceptChannel_;
    bool listening_;
    NewConnectionCallback newConnectionCallback_;

    void handleRead();
};

}


#endif //DIO_ACCEPTOR_H
