//
// Created by parallels on 9/20/16.
//

#ifndef PROJECT_CONNECTOR_H
#define PROJECT_CONNECTOR_H

#include <dio/net/InetAddress.h>
#include <dio/net/Channel.h>
#include <dio/net/Socket.h>
#include <boost/shared_ptr.hpp>

namespace dio {

class EventLoop;

class Connector : public boost::noncopyable {

public:
    typedef boost::function<void (int sockfd)> NewConnectionCallback;
    Connector(EventLoop *eventLoop, InetAddress inetAddress);
    void start();
    void stop();

    void setNewConnectionCallback(const NewConnectionCallback& cb) {
        newConnectionCallback_ = cb;
    }

private:
    enum StateE {kConnecting, kConnected, kDisconneting, kDisconnected};
    const int kInitRetryMs = 500;
    const int kMaxRetryMs = 30 * 1000;        // retry to connecting interval
    InetAddress serverAddr_;
    EventLoop *loop_;
    Socket clientSocket_;
    boost::shared_ptr<Channel> channelPtr_;     // loose it when establish a connection
    bool connect_;
    StateE state_;
    int retryDelayMs_;

    NewConnectionCallback newConnectionCallback_;

    void handleWrite();
    void handleError();
    void connecting(int sockfd);
    void retry(int sockfd);
    int removeAndResetChannel();
    void resetChannel();
    void setState(StateE state) {
        state_ = state;
    }
    void startInLoop();
    void stopInLoop();

};

}

#endif //PROJECT_CONNECTOR_H
