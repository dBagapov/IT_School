#include "Handlers.h"
#include "spdlog/spdlog.h"

#include <sstream>

void DumpHandler::Handle(const std::string& message, std::shared_ptr<IRepository>& repository, std::string& response) {
    std::istringstream iss(message);
    std::string command;
    iss >> command;

    if (command == "DUMP") {
        std::string file_name;
        iss >> file_name;
        bool is_dump = repository->Dump(file_name);

        if (is_dump) {
            spdlog::info("Store saved in : {}", file_name);
            response = "OK\n";
        } else {
            spdlog::warn("File not found: {}", file_name);
            response = "NE\n";
        }
    } else {
        next_handler_->Handle(message, repository, response);
    }
}