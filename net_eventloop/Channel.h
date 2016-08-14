//
// Created by coolman on 16/7/25.
//

#ifndef DIO_CHANNEL_H
#define DIO_CHANNEL_H


#include <boost/noncopyable.hpp>
#include <boost/function.hpp>


namespace dio {

class EventLoop;

class Channel: boost::noncopyable {
public:
    typedef boost::function<void()> EventCallback;

    Channel(EventLoop* loop, int fd);
    ~Channel();

    void handleEvent();
    void setReadCallback(const EventCallback& cb) {
        readCallback_ = cb;
    }
    void setWriteCallback(const EventCallback& cb) {
        writeCallback_ = cb;
    }
    void setErrorCallback(const EventCallback& cb) {
        errorCallback_ = cb;
    }

    void enableReading() { events_ |= kReadEvent; update(); }
    void enableWriting() { events_ |= kWriteEvent; update(); }
    void disableWriting() { events_ &= ~kWriteEvent; update(); }
    void disableAll() { events_ = kNoneEvent; update(); }

    EventLoop* ownerLoop() { return loop_; }


    int get_index() const { return index_; }
    void set_index(int idx) { index_ = idx; }

    int fd() const { return fd_; }

    void set_revents(int rvet) { revents_ = rvet; }
    int events() const { return events_; }
    bool isNoneEvents() { return events_ == kNoneEvent; }

private:
    int events_;
    EventLoop* loop_;
    int index_;
    const int fd_;
    int revents_;
    EventCallback readCallback_;
    EventCallback writeCallback_;
    EventCallback errorCallback_;

    static const int kNoneEvent;
    static const int kReadEvent;
    static const int kWriteEvent;

    void update();

};
}


#endif //DIO_CHANNEL_H
