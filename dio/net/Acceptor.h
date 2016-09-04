//
// Created by coolman on 16/8/9.
//

#ifndef DIO_ACCEPTOR_H
#define DIO_ACCEPTOR_H

#include <boost/noncopyable.hpp>
#include <dio/net/InetAddress.h>
#include <dio/net/Channel.h>
#include <dio/net/Socket.h>


namespace dio {

class EventLoop;

class Acceptor: public boost::noncopyable {
public:

    typedef boost::function<void (int, const InetAddress&)> NewConnectionCallback;
    Acceptor(EventLoop*, const InetAddress&);

    void setNewConnectionCallback(const NewConnectionCallback& cb) {
        newConnectionCallback_ = cb;
    }

    void listen();
private:
    EventLoop* loop_;
    Socket serverSocket_;
    Channel acceptChannel_;
    bool listening_;
    NewConnectionCallback newConnectionCallback_;

    void handleRead();
};

}


#endif //DIO_ACCEPTOR_H
