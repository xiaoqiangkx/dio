//
// Created by parallels on 9/20/16.
//

#ifndef PROJECT_TCPCLIENT_H
#define PROJECT_TCPCLIENT_H


#include <boost/core/noncopyable.hpp>
#include <boost/shared_ptr.hpp>
#include <dio/net/Connector.h>

namespace dio {

class EventLoop;

class TcpClient : public boost::noncopyable {
public:
    TcpClient(EventLoop* loop, const InetAddress &remoteAddress);

    void setNewConnectionCallback(const Connector::NewConnectionCallback& cb) {
        newConnectionCallback_ = cb;
    }

    void start();
    void stop();
private:
    EventLoop *loop_;
    boost::shared_ptr<Connector> connector_;
    Connector::NewConnectionCallback newConnectionCallback_;

    void onNewConnectionCallback(int sockfd);

};

};


#endif //PROJECT_TCPCLIENT_H
