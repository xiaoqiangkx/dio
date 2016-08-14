add_executable(echo main.cpp)

#target_link_libraries(
#    echo PUBLIC muduo
#)

target_compile_options(echo PUBLIC -DMUDUO_STD_STRING -std=c++11 -Wall)
