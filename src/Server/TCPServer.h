#pragma once

#include "TCPSession.h"

class TCPServer {
public:
    TCPServer(short port, size_t max_clients);
    TCPServer(short port, size_t max_clients, const std::string& file_name_to_start);

private:
    boost::asio::io_context io_context_;
    tcp::acceptor acceptor_;
    std::shared_ptr<IRepository> repository_;
    std::atomic<size_t> current_clients_{0};
    const size_t max_clients_;

    void DoAccept();
};
