#include "Handlers.h"
#include "spdlog/spdlog.h"

#include <sstream>

void GetHandler::Handle(const std::string& message, std::shared_ptr<IRepository>& repository, std::string& response)  {
    std::istringstream iss(message);
    std::string command;
    iss >> command;

    if (command == "GET") {
        std::string key;
        iss >> key;
        auto value = repository->Get(key);

        if (value) {
            spdlog::info("GET request for key '{}'", key);
            response = "OK " + *value + "\n";
        } else {
            spdlog::warn("Key not found: {}", key);
            response = "NE\n";
        }
    } else {
        next_handler_->Handle(message, repository, response);
    }
}