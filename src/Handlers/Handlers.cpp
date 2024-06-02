#include "Handlers.h"

#include "spdlog/spdlog.h"
#include <utility>
#include <sstream>

std::shared_ptr<CommandHandler> CommandHandler::SetNext(std::shared_ptr<CommandHandler> next_handler) {
    next_handler_ = std::move(next_handler);
    return next_handler_;
}

void UnknownCommandHandler::Handle(const std::string& message, std::shared_ptr<IRepository>& repository, std::string& response) {
    spdlog::warn("Command not found: {}", message);
    response = "NE\n";
}