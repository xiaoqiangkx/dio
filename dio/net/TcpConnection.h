//
// Created by parallels on 8/14/16.
//

#ifndef DIO_TCPCONNECTION_H
#define DIO_TCPCONNECTION_H

#include <boost/noncopyable.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/scoped_ptr.hpp>
#include <dio/net/Socket.h>
#include <dio/base/Callbacks.h>
#include <dio/net/Buffer.h>
#include <dio/net/InetAddress.h>

#include <string>


namespace dio {

class EventLoop;
class Channel;

class TcpConnection: public boost::noncopyable, public boost::enable_shared_from_this<TcpConnection> {
public:
    TcpConnection(EventLoop* loop, std::string name, int sockfd, const InetAddress& localAddr, const InetAddress& peerAddr);

    void setMessageCallback(const dio::net::MessageCallback& cb) {
        messageCallback_ = cb;
    }

    void setConnectionCallback(const dio::net::ConnectionCallback& cb) {
        connectionCallback_ = cb;
    }

    void setCloseCallback(const dio::net::CloseCallback& cb) {
        closeCallback_ = cb;
    }

    InetAddress localAddr() const { return localAddr_; }
    InetAddress peerAddr() const { return peerAddr_; }

    void connectEstablished();
    void connectDestroyed();

    bool connected() const { return state_ == kConnected; }

    void send(const std::string &message);
    void shutdown();

    std::string name() const { return name_; }

    std::string name_;
private:
    enum StateE {kConnecting, kConnected, kDisconneting, kDisconnected};
    void setState(StateE s) { state_ = s; }
    void handleRead(dio::Timestamp receiveTimestamp);
    void handleWrite();
    void handleClose();
    void handleError();

    void sendInLoop(const std::string &message);
    void shutdownInLoop();

    EventLoop* loop_;

    boost::scoped_ptr<Socket> socket_;
    boost::scoped_ptr<Channel> channel_;
    InetAddress localAddr_;
    InetAddress peerAddr_;
    enum StateE state_;
    dio::net::MessageCallback messageCallback_;
    dio::net::ConnectionCallback connectionCallback_;
    dio::net::CloseCallback closeCallback_;
    dio::net::Buffer inputBuffer_;
    dio::net::Buffer outputBuffer_;
};
};


#endif //DIO_TCPCONNECTION_H
