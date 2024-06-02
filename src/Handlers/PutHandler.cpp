#include "Handlers.h"
#include "spdlog/spdlog.h"

#include <sstream>

inline bool isKeyCorrect(const std::string& key) {
    return std::all_of(key.begin(), key.end(), [](unsigned char c) { return std::isalnum(c); });
}

void PutHandler::Handle(const std::string& message, std::shared_ptr<IRepository>& repository, std::string& response)  {
    std::istringstream iss(message);
    std::string command;
    iss >> command;

    if (command == "PUT") {
        std::string key;
        std::string value;
        iss >> key >> value;

        if (!isKeyCorrect(key)) {
            spdlog::warn("Incorrect key: {}", key);
            response = "NE\n";
        } else if (value.empty()) {
            spdlog::warn("Empty value not allowed for key: {}", key);
            response = "NE\n";
        } else {
            spdlog::info("PUT request for key '{}' with value '{}'", key, value);
            auto prev_value = repository->Put(key, value);
            response = prev_value ? "OK " + *prev_value + "\n" : "OK\n";
        }
    } else {
        next_handler_->Handle(message, repository, response);
    }
}