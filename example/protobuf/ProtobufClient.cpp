//
// Created by parallels on 9/26/16.
//

#include "ProtobufClient.h"

#include <boost/bind.hpp>
#include <dio/net/TcpConnection.h>
#include <dio/net/ProtobufCodec.h>

namespace dio {

    ProtobufClient::ProtobufClient(EventLoop *loop, const InetAddress& address):
            loop_(loop),
            tcpClient_(loop, address),
            codec_(boost::bind(&ProtobufClient::onMessage, this, _1, _2, _3))
    {
        tcpClient_.setConnectionCallback(boost::bind(&ProtobufClient::onConnection, this, _1));
        tcpClient_.setMessageCallback(boost::bind(&ProtobufCodec::onMessage, &codec_, _1, _2, _3));
    }

    void ProtobufClient::start() {
        tcpClient_.start();
    }

    void ProtobufClient::send(const dio::Query& query) {
        codec_.sendQuery(connection_, query);
    }

    void ProtobufClient::onMessage(const dio::net::TcpConnectionPtr &connection, const boost::shared_ptr<::google::protobuf::Message>& message, Timestamp time) {
        dio::Answer *answer = dynamic_cast<dio::Answer*>(message.get());
        LOG_INFO << "data";

        LOG_INFO << "onMessage receive: " << answer->solution(0);
    }

    void ProtobufClient::onConnection(const dio::net::TcpConnectionPtr& connection) {
        if (connection->connected()) {
            LOG_INFO << "ProtobufClient::onConnection";
            connection_ = connection;
            dio::Query query;
            query.set_questionid(12);
            query.set_question("test Hello World");
            query.set_questioner("Client");
            send(query);
        } else {

        }
    }

};