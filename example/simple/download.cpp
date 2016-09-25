//
// Created by parallels on 9/25/16.
//

#include <dio/base/Logging.h>
#include <dio/net/TcpServer.h>
#include <dio/net/Buffer.h>
#include <dio/net/TcpConnection.h>
#include <boost/shared_ptr.hpp>

using namespace dio;

const char* g_file = "/home/parallels/workspace/dio/example/simple/test.txt";
typedef boost::shared_ptr<FILE> FilePtr;


int send_data(const net::TcpConnectionPtr connection) {
    char buf[64];
    FilePtr ctx = boost::any_cast<FilePtr>(connection->getContext());
    size_t n = ::fread(buf, 1, sizeof buf, ctx.get());

    if (n > 0) {
        std::string data(buf, buf + n);
        connection->send(data);
    }

    return n;
}

void newConnectionCallback(const net::TcpConnectionPtr tcpConnection) {
    LOG_INFO << "DayTimeServer - " << tcpConnection->peerAddr().toIpPort() << " -> " << tcpConnection->localAddr().toIpPort()
             << " is " << (tcpConnection->connected() ? "up" : "down");
    if (tcpConnection->connected()) {
        FILE* fp = ::fopen(g_file, "rb");
        if (!fp) {
            LOG_ERROR << "failed to open data";
            tcpConnection->shutdown();
            return;
        }
        FilePtr ctx(fp, ::fclose);
        tcpConnection->setContext(ctx);

        int n = send_data(tcpConnection);
        if (n <= 0) {
            tcpConnection->shutdown();
        }
    }
}

void writeMessageCompleteCallback(const net::TcpConnectionPtr connection) {
    if (connection->connected()) {
        int n = send_data(connection);
        if (n <= 0) {
            connection->shutdown();
        }
    } else {
        LOG_ERROR << "download-server: connection is closed unexpected";
    }
}

int main() {
    LOG_INFO << "Testcase: daytime: start server";
    EventLoop eventLoop;
    InetAddress inetAddress(1998);
    TcpServer tcpServer(&eventLoop, inetAddress);
    tcpServer.setConnectionCallback(newConnectionCallback);
    tcpServer.setWriteCompleteCallback(writeMessageCompleteCallback);

    tcpServer.start();
    eventLoop.loop();
    return 0;
}