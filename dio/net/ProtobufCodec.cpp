//
// Created by parallels on 9/25/16.
//

#include <dio/net/ProtobufCodec.h>
#include <dio/net/Buffer.h>
#include <dio/net/TcpConnection.h>
#include <google/protobuf/descriptor.h>

namespace dio {

ProtobufCodec::ProtobufCodec(const MessageCallback &cb):
    messageCallback_(cb)
{

}

void ProtobufCodec::onMessage(const net::TcpConnectionPtr tcpConnection, net::Buffer *buffer, Timestamp time) {
    // retrieve protobuf data from message
    while (buffer->readableBytes() >= kProtobufDataLength) {
        int32_t protobufLength = buffer->peekInt32();
        if (protobufLength <= 0 || buffer->readableBytes() < kProtobufDataLength + protobufLength) {
            LOG_ERROR << "protobufLength is not valid: " << protobufLength;
            tcpConnection->shutdown();
        } else {
            LOG_INFO << "ProtobufCodec::onMessage";
            buffer->retrieve(kProtobufDataLength);
            int32_t typeNameLength = buffer->readInt32();
            std::string typeName = buffer->retrieveAsString(typeNameLength);
            std::string protobufData = buffer->retrieveAsString(protobufLength - kTypeNameLength - typeNameLength);

            const ::google::protobuf::Descriptor* descriptor = ::google::protobuf::DescriptorPool::generated_pool()->FindMessageTypeByName(typeName);
            const ::google::protobuf::Message* prototype = ::google::protobuf::MessageFactory::generated_factory()->GetPrototype(descriptor);
            boost::shared_ptr<::google::protobuf::Message> newMessage(prototype->New());

            LOG_INFO << "recevice data";
            newMessage->ParseFromString(protobufData);
            if (messageCallback_) {
                messageCallback_(tcpConnection, newMessage, time);
            }
        }
    }
}

void ProtobufCodec::send(const dio::net::TcpConnectionPtr &tcpConnection, const ::google::protobuf::Message &message, const std::string &full_name) {
    std::string serialData = message.SerializeAsString();
    dio::net::Buffer buffer;
    size_t protobufDataLength = serialData.length() + full_name.length() + kTypeNameLength;
    buffer.prependInt32(full_name.length());
    buffer.prependInt32(protobufDataLength);
    buffer.append(full_name.data(), full_name.length());
    buffer.append(serialData.data(), serialData.length());
    LOG_INFO << "buffer lENGTH: " << buffer.readableBytes() << " full_name: " << full_name.length() << " serialData.length: " << serialData.length();
    tcpConnection->send(buffer.retrieveAllAsString());
}

void ProtobufCodec::sendAnswer(const dio::net::TcpConnectionPtr &tcpConnection, const dio::Answer &answer) {
    send(tcpConnection, answer, answer.descriptor()->full_name());
}

void ProtobufCodec::sendQuery(const dio::net::TcpConnectionPtr &tcpConnection, const dio::Query &query) {
    send(tcpConnection, query, query.descriptor()->full_name());
}
};
