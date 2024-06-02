#include "Handlers.h"
#include "spdlog/spdlog.h"

#include <sstream>

void CountHandler::Handle(const std::string& message, std::shared_ptr<IRepository>& repository, std::string& response) {
    std::istringstream iss(message);
    std::string command;
    iss >> command;

    if (command == "COUNT") {
        size_t count = repository->Count();

        if (count != 0) {
            spdlog::info("COUNT request processed. Total count: {}", count);
            response = "OK " + std::to_string(count) + "\n";
        } else {
            response = "NE\n";
            spdlog::warn("Store is empty");
        }
    } else {
        next_handler_->Handle(message, repository, response);
    }
}
