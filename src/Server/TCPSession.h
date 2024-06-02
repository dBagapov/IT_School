#pragma once

#include <boost/asio.hpp>
#include <iostream>
#include <memory>
#include "spdlog/spdlog.h"
#include <string>

#include "../Settings.h"
#include "../Repository/Repository.h"
#include "../Handlers/Handlers.h"

using tcp = boost::asio::ip::tcp;

class TCPSession : public std::enable_shared_from_this<TCPSession> {
public:
    explicit TCPSession(tcp::socket socket, std::atomic<size_t>& current_client, std::shared_ptr<IRepository>& repository);
    ~TCPSession();

    void Start();

private:
    tcp::socket socket_;
    std::atomic<size_t>& current_client_;
    std::shared_ptr<IRepository>& repository_;
    std::shared_ptr<CommandHandler> command_handler_;
    std::array<char, k_max_data_size> read_data_{};

    void DoRead();
    void DoWrite(const std::string& response);
};