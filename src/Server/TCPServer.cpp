#include "TCPServer.h"

TCPServer::TCPServer(short port, size_t max_clients)
        : acceptor_(io_context_, tcp::endpoint(tcp::v4(), port)),
          max_clients_(max_clients),  repository_(std::make_shared<Repository>()) {
    spdlog::info("Port is {}", acceptor_.local_endpoint().port());
    DoAccept();
    io_context_.run();
}

TCPServer::TCPServer(short port, size_t max_clients, const std::string& file_name_to_start)
        : acceptor_(io_context_, tcp::endpoint(tcp::v4(), port)),
          max_clients_(max_clients),  repository_(std::make_shared<Repository>(file_name_to_start)) {
    spdlog::info("Port is {}", acceptor_.local_endpoint().port());
    DoAccept();
    io_context_.run();
}

void TCPServer::DoAccept() {
    if (current_clients_ < max_clients_) {
        acceptor_.async_accept(
                [this](boost::system::error_code ec, tcp::socket socket) {
                    if (!ec) {
                        spdlog::info("Client connected: {}", socket.remote_endpoint().address().to_string());
                        current_clients_++;

                        auto session = std::make_shared<TCPSession>(std::move(socket), current_clients_, repository_);
                        session->Start();
                    } else {
                        spdlog::error("Error when accepting connection: {}", ec.message());
                    }

                    DoAccept();
                });
    } else {
        spdlog::info("Max clients limit reached. Waiting for a slot to become available");
    }
}