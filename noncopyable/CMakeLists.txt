add_executable(noncopyable main.cpp)

#target_link_libraries(
#    echo PUBLIC muduo
#)

target_compile_options(noncopyable PUBLIC -DMUDUO_STD_STRING -std=c++11 -Wall -Wfloat-conversion)
