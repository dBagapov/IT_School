#include "Handlers.h"
#include "spdlog/spdlog.h"

#include <sstream>

void DeleteHandler::Handle(const std::string& message, std::shared_ptr<IRepository>& repository, std::string& response) {
    std::istringstream iss(message);
    std::string command;
    iss >> command;

    if (command == "DEL") {
        std::string key;
        iss >> key;
        bool is_delete = repository->Delete(key);

        if (is_delete) {
            spdlog::info("Key deleted: {}", key);
            response = "OK\n";
        } else {
            spdlog::warn("Key not found: {}", key);
            response = "NE\n";
        }
    } else {
        next_handler_->Handle(message, repository, response);
    }
}