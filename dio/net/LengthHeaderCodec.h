//
// Created by parallels on 9/25/16.
//

#ifndef PROJECT_LENGTHHEADERCODEC_H
#define PROJECT_LENGTHHEADERCODEC_H

#include <boost/core/noncopyable.hpp>
#include <string>
#include <dio/base/Timestamp.h>
#include <dio/base/Callbacks.h>

namespace dio {

class LengthHeaderCodec: public boost::noncopyable {
public:
    typedef boost::function<void(const dio::net::TcpConnectionPtr&, const std::string&, Timestamp)> StringMessageCallback;
    explicit LengthHeaderCodec(const StringMessageCallback& cb);
    void onMessage(const net::TcpConnectionPtr tcpConnection, net::Buffer* buffer, Timestamp time);
    void send(const dio::net::TcpConnectionPtr&, const std::string&);
private:
    const static int kHeaderLength = 4;
    StringMessageCallback stringMessageCallback_;
};

};


#endif //PROJECT_LENGTHHEADERCODEC_H
