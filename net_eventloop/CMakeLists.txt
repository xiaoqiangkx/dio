add_executable(net_eventloop main.cpp EventLoop.cpp EventLoop.h Channel.cpp Channel.h Poller.cpp Poller.h TimerFd.cpp TimerFd.h base.h TimerId.h Timer.h Timer.cpp TimerQueue.cpp TimerQueue.h EventFd.cpp EventFd.h Acceptor.cpp Acceptor.h Socket.h SocketsOps.h)

target_link_libraries(
net_eventloop PUBLIC muduo_net muduo_base pthread
)

target_compile_options(net_eventloop PUBLIC -DMUDUO_STD_STRING -std=c++11 -Wall)
