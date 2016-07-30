add_executable(net_eventloop main.cpp EventLoop.cpp EventLoop.h Channel.cpp Channel.h Poller.cpp Poller.h TimerFd.cpp TimerFd.h base.h)

target_link_libraries(
net_eventloop PUBLIC muduo_net muduo_base
)

target_compile_options(net_eventloop PUBLIC -DMUDUO_STD_STRING -std=c++11 -Wall -Wfloat-conversion)
