//
// Created by parallels on 9/26/16.
//

#include "ProtobufServer.h"

#include <dio/net/EventLoop.h>
#include <boost/bind.hpp>
#include <dio/net/TcpConnection.h>
#include <dio/net/ProtobufCodec.h>
#include <dio/base/Callbacks.h>

namespace  dio {

    ProtobufServer::ProtobufServer(EventLoop *loop, InetAddress address):
            loop_(loop),
            tcpServer_(loop, address),
            codec_(boost::bind(&ProtobufServer::onStringMessage, this, _1, _2, _3))
    {
        tcpServer_.setConnectionCallback(boost::bind(&ProtobufServer::onConnection, this, _1));
        tcpServer_.setMessageCallback(boost::bind(&ProtobufCodec::onMessage, &codec_, _1, _2, _3));
    }

    void ProtobufServer::start() {
        tcpServer_.start();
    }

    void ProtobufServer::onStringMessage(const dio::net::TcpConnectionPtr& connection, const boost::shared_ptr< ::google::protobuf::Message>& message, Timestamp timestamp) {
        dio::Query* query = dynamic_cast<dio::Query*>(message.get());
        std::string questionStr = query->question();
        LOG_INFO << "receive question: " << questionStr;

        dio::Answer answer;
        answer.set_questioner(query->questioner());
        answer.set_answerer("server");
        answer.set_questionid(123);
        answer.add_solution("Hello World from server");
        for (ConnectionList::iterator it = connectionList_.begin(); it != connectionList_.end(); ++it) {
            codec_.sendAnswer(*it, answer);
        }
    }

    void ProtobufServer::onConnection(const dio::net::TcpConnectionPtr& connection) {
        if (connection->connected()) {
            connectionList_.insert(connection);
        } else {
            connectionList_.erase(connection);
        }
    }
};
