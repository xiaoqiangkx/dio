//
// Created by parallels on 8/14/16.
//

#include <dio/net/TcpConnection.h>
#include <dio/net/EventLoop.h>
#include <boost/bind.hpp>
#include <boost/implicit_cast.hpp>
#include <cerrno>


namespace dio {
    TcpConnection::TcpConnection(EventLoop* loop, std::string name, int sockfd, const InetAddress& localAddr, const InetAddress& peerAddr):
        name_(name),
        loop_(loop),
        socket_(new Socket(sockfd)),
        channel_(new Channel(loop_, sockfd)),
        localAddr_(localAddr),
        peerAddr_(peerAddr),
        state_(kConnecting)
    {
        channel_->enableReading();
        channel_->setReadCallback(boost::bind(&TcpConnection::handleRead, this, _1));
        channel_->setWriteCallback(boost::bind(&TcpConnection::handleWrite, this));
        channel_->setCloseCallback(boost::bind(&TcpConnection::handleClose, this));
        channel_->setErrorCallback(boost::bind(&TcpConnection::handleError, this));
    }

    void TcpConnection::handleRead(dio::Timestamp receiveTimestamp) {
        int savedErrno = 0;
        ssize_t n = inputBuffer_.readFd(channel_->fd(), &savedErrno);
        if (n > 0) {
            messageCallback_(shared_from_this(), &inputBuffer_, receiveTimestamp);
        } else if (n == 0) {
            handleClose();
        } else {
            errno = savedErrno;

            if (errno == EAGAIN) {
                return;
            }

            LOG_SYSERR << "TcpConnection::handleRead()";
            handleError();
        }
    }

    void TcpConnection::handleWrite() {
        loop_->assertInLoopThread();
        if (channel_->isWriting() && outputBuffer_.readableBytes() > 0) {
            ssize_t n = ::write(channel_->fd(), outputBuffer_.peek(), outputBuffer_.readableBytes());
            if (n > 0) {
                outputBuffer_.retrieve(n);
                if (outputBuffer_.readableBytes() == 0) {
                    channel_->disableWriting();
                    if (state_ == kDisconneting) {
                        shutdownInLoop();
                    }
                } else {
                    LOG_INFO << "There is more data";
                }
            } else {
                LOG_SYSERR << "TcpConnection::handleWrite";
            }
        } else {
            LOG_INFO << "There is nothing to send";
        }
    }

    void TcpConnection::handleClose() {
        loop_->assertInLoopThread();
        assert(state_ == kDisconneting);

        channel_->disableAll();
        closeCallback_(shared_from_this());
    }

    void TcpConnection::handleError() {
        int err = sockets::getSocketError(channel_->fd());
        LOG_ERROR << "TcpConncetion:handleError [" << name_ << "] SO_ERROR = " <<
                err << " " << strerror(err);
    }

    void TcpConnection::connectEstablished() {
        assert(state_ == kConnecting);
        setState(kConnected);
    }

    void TcpConnection::connectDestroyed() {
        loop_->assertInLoopThread();
        assert(state_ == kDisconneting);
        setState(kDisconnected);

        channel_->disableAll();
        connectionCallback_(shared_from_this());
        loop_->removeChannel(get_pointer(channel_));
    }

    void TcpConnection::shutdown() {
        if (state_ == kConnected) {
            setState(kDisconneting);
            loop_->RunInLoop(boost::bind(&TcpConnection::shutdownInLoop, this));
        }
    }

    void TcpConnection::shutdownInLoop() {
        loop_->assertInLoopThread();
        if (!channel_->isWriting()) {
            socket_->shutdownWrite();
        }
    }

    void TcpConnection::send(const std::string &message) {
        if (state_ == kConnected) {
            if (loop_->isInLoopThread()) {
                sendInLoop(message);
            } else {
                loop_->RunInLoop(boost::bind(&TcpConnection::sendInLoop, this, message));
            }
        }
    }

    void TcpConnection::sendInLoop(const std::string &message) {
        loop_->assertInLoopThread();
        ssize_t nWrote;
        if (message.size() > 0 && outputBuffer_.readableBytes() == 0) {
            nWrote = ::write(channel_->fd(), message.data(), message.size());
            if (nWrote >= 0) {
                if (boost::implicit_cast<size_t>(nWrote) < message.size()) {
                    LOG_INFO << "there is more data to send";
                }
            } else {
                nWrote = 0;
                if (errno != EWOULDBLOCK) {
                    LOG_SYSERR << "TcpConnection::sendInLoop";
                }
            }
        }

        assert(nWrote >= 0);
        if (boost::implicit_cast<size_t>(nWrote) < message.size()) {
            outputBuffer_.append(message.data() + nWrote, message.size() - nWrote);

            if (!channel_->isWriting()) {
                channel_->enableWriting();
            }
        }
    }
};