#include <iostream>
using namespace std;


class Uncopyable {
protected:
    Uncopyable() {}
    ~Uncopyable() {}
private:
    Uncopyable(const Uncopyable&);
    Uncopyable operator=(const Uncopyable&);
};


class EventLoopCopyable {

};

class EventLoop: private Uncopyable {

};



int main() {
    EventLoopCopyable event_loop_copyable;
    EventLoopCopyable event_one_copyable = event_loop_copyable;
    EventLoopCopyable event_two_copyable(event_loop_copyable);

    // 通过继承基类来避免实现被复制。
    EventLoop event_loop;
//    net_eventloop copy_one = event_loop;
//    net_eventloop copy_two(event_loop);
    return 0;
}
