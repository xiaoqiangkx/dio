//
// Created by parallels on 9/26/16.
//

#ifndef PROJECT_PROTOBUFSERVER_H
#define PROJECT_PROTOBUFSERVER_H


#include <boost/core/noncopyable.hpp>
#include <dio/net/TcpServer.h>
#include <dio/net/ProtobufCodec.h>

namespace dio {

    class EventLoop;

    class ProtobufServer: public boost::noncopyable {
    public:
        ProtobufServer(EventLoop *loop, InetAddress address);
        void start();
    private:
        typedef std::set<dio::net::TcpConnectionPtr> ConnectionList;
        EventLoop* loop_;
        TcpServer tcpServer_;
        ProtobufCodec codec_;
        ConnectionList connectionList_;

        void onConnection(const dio::net::TcpConnectionPtr&);
        void onStringMessage(const dio::net::TcpConnectionPtr&, const boost::shared_ptr< ::google::protobuf::Message>&, Timestamp);
    };

};


#endif //PROJECT_PROTOBUFSERVER_H
