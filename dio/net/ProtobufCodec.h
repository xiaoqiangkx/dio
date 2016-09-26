//
// Created by parallels on 9/25/16.
//

#ifndef PROJECT_PROTOBUFCODEC_H
#define PROJECT_PROTOBUFCODEC_H


#include <boost/core/noncopyable.hpp>
#include <dio/base/Timestamp.h>
#include <dio/base/Callbacks.h>
#include <google/protobuf/message.h>
#include <dio/protobuf/query.pb.h>

namespace dio {

class ProtobufCodec : public boost::noncopyable {
public:
    typedef boost::function<void(const dio::net::TcpConnectionPtr &, const boost::shared_ptr< ::google::protobuf::Message> &,
                                 Timestamp)> MessageCallback;

    explicit ProtobufCodec(const MessageCallback &cb);

    void onMessage(const net::TcpConnectionPtr tcpConnection, net::Buffer *buffer, Timestamp time);

    void sendQuery(const dio::net::TcpConnectionPtr &, const dio::Query &);
    void sendAnswer(const dio::net::TcpConnectionPtr &, const dio::Answer &);

private:
    void send(const dio::net::TcpConnectionPtr &, const ::google::protobuf::Message &, const std::string &);
    const static int kTypeNameLength = 4;
    const static int kProtobufDataLength = 4;      // include typeName and typeLength
    MessageCallback messageCallback_;

};
};


#endif //PROJECT_PROTOBUFCODEC_H
