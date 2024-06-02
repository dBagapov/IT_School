#include "TCPSession.h"

TCPSession::TCPSession(tcp::socket socket, std::atomic<size_t>& current_client, std::shared_ptr<IRepository>& repository)
        : socket_(std::move(socket)), current_client_(current_client), repository_(repository) {
    command_handler_ = std::make_shared<PutHandler>();

    command_handler_->SetNext(std::make_shared<GetHandler>())
            ->SetNext(std::make_shared<DeleteHandler>())
            ->SetNext(std::make_shared<CountHandler>())
            ->SetNext(std::make_shared<DumpHandler>())
            ->SetNext(std::make_shared<UnknownCommandHandler>());

}

TCPSession::~TCPSession() {
    current_client_--;
}

void TCPSession::Start() {
    DoRead();
}

void TCPSession::DoRead() {
    auto self(shared_from_this());
    socket_.async_read_some(boost::asio::buffer(read_data_),
                            [this, self](boost::system::error_code ec, size_t length) {
                                if (!ec) {
                                    spdlog::debug("Message received: {}");

                                    std::string message(read_data_.data(), length);
                                    std::string response;
                                    command_handler_->Handle(message, repository_, response);
                                    DoWrite(response);
                                } else if(ec == boost::asio::error::eof) {
                                    spdlog::info("Connection closed by peer");
                                } else {
                                    spdlog::error("Read error: {}", ec.message());
                                }

                            });
}

void TCPSession::DoWrite(const std::string& response) {
    auto self(shared_from_this());
    boost::asio::async_write(socket_, boost::asio::buffer(response),
                             [response, this, self](boost::system::error_code ec, size_t) {
                                 if (!ec) {
                                     spdlog::debug("Sent message: {}", response);
                                     DoRead();
                                 } else {
                                     spdlog::error("Write error: {}", ec.message());
                                 }
                             });
}
