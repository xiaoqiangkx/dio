//
// Created by parallels on 9/25/16.
//

#include <dio/net/LengthHeaderCodec.h>
#include <dio/net/Buffer.h>
#include <dio/net/TcpConnection.h>

namespace dio {
LengthHeaderCodec::LengthHeaderCodec(const StringMessageCallback& cb):
        stringMessageCallback_(cb) {
}

void LengthHeaderCodec::onMessage(const net::TcpConnectionPtr connection, net::Buffer* buffer, Timestamp time) {
    // receive data and call stringMessageCallback_ when message come
    while (buffer->readableBytes() >= kHeaderLength) {
        int32_t len = buffer->peekInt32();
        if (len <= 0 || len > 65536) {
            LOG_ERROR << "invalid length: " << len;
            connection->shutdown();
            break;
        } else if (buffer->readableBytes() >= kHeaderLength + len) {
            buffer->retrieve(kHeaderLength);
            std::string message = buffer->retrieveAsString(len);
            if (stringMessageCallback_) {
                stringMessageCallback_(connection, message, time);
            }
        } else {
            break;
        }
    }
}

void LengthHeaderCodec::send(const dio::net::TcpConnectionPtr& connection, const std::string& message) {
    int32_t len = message.length();
    dio::net::Buffer buffer;
    buffer.append(message.data(), message.length());
    buffer.prependInt32(len);
    connection->send(buffer.retrieveAllAsString());
}
};
