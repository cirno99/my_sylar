#include "http/http_connection.hh"
#include "log.hh"
#include "iomanager.hh"
#include "address.hh"

sylar::Logger::ptr g_logger = SYLAR_LOG_ROOT();

void test() {
    sylar::IPAddress::ptr addr(sylar::IPv4Address::Create("127.0.0.1", 90));
    sylar::Socket::ptr sock(sylar::Socket::CreateTCP(addr));
    sylar::http::HttpConnection::ptr http_conn(new sylar::http::HttpConnection(sock, false));
    sylar::http::HttpRequest::ptr req(new sylar::http::HttpRequest);
    req->setPath("/path/to/");
    req->setHeader("Host", "127.0.0.1");
    SYLAR_LOG_DEBUG(g_logger) << "Request: " << req->toString();
    sock->connect(addr);

    http_conn->sendRequest(req);
    auto resp = http_conn->recvResponse();
    SYLAR_LOG_DEBUG(g_logger) << "Response: " << resp->toString();
}

int main() {
    sylar::IOManager iom(2, false, "io");
    iom.schedule(test);
    iom.stop();
    return 0;
}