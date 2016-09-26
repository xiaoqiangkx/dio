//
// Created by parallels on 9/26/16.
//

#ifndef PROJECT_PROTOBUFCLIENT_H
#define PROJECT_PROTOBUFCLIENT_H


#include <boost/core/noncopyable.hpp>
#include <dio/net/ProtobufCodec.h>
#include <dio/net/TcpClient.h>
#include <dio/net/InetAddress.h>
#include <dio/base/Callbacks.h>
#include <dio/protobuf/query.pb.h>

namespace dio {

    class EventLoop;

    class ProtobufClient : public boost::noncopyable {
    public:
        ProtobufClient(EventLoop *loop, const InetAddress& address);
        void start();
        void send(const dio::Query&);

    private:
        EventLoop *loop_;
        TcpClient tcpClient_;
        ProtobufCodec codec_;
        dio::net::TcpConnectionPtr connection_;

        void onConnection(const dio::net::TcpConnectionPtr&);
        void onMessage(const dio::net::TcpConnectionPtr&, const boost::shared_ptr<::google::protobuf::Message>&, Timestamp);
    };
};


#endif //PROJECT_PROTOBUFCLIENT_H
