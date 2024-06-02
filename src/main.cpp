#include <iostream>
#include "Repository/Repository.h"
#include "Server/TCPServer.h"

int main(int argc, char* argv[]) {
    spdlog::info("Start");

    short port = k_port;
    size_t max_clients = k_max_clients;
    std::string path_to_file_to_start = k_path_to_file_to_start;

    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg == "-p" && i + 1 < argc) {
            port = static_cast<short>(std::stoi(argv[++i]));
        } else if (arg == "-f" && i + 1 < argc) {
            path_to_file_to_start = argv[++i];
        } else if (arg == "-m" && i + 1 < argc) {
            max_clients = std::stoi(argv[++i]);
        } else {
            spdlog::critical("Unknown or incomplete argument: {}", arg);
            exit(EXIT_FAILURE);
        }
    }

    try {
        if (path_to_file_to_start.empty()) {
            TCPServer server(port, max_clients);
        } else {
            TCPServer server(port, max_clients, path_to_file_to_start);
        }
    } catch (std::exception& e) {
        spdlog::critical("Error: {}", e.what());
    }

    spdlog::info("End");
}