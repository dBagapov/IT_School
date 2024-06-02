#include "Repository.h"
#include "spdlog/spdlog.h"

#include <shared_mutex>
#include <mutex>
#include <fstream>
#include <sstream>
#include <string>

Repository::Repository(const std::string& file_name) {
    std::unique_lock<std::shared_mutex> lock(mutex_);
    std::ifstream file(file_name);

    if (!file.is_open()) {
        spdlog::error("Incorrect file name: {}", file_name);
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::size_t pos = line.find(' ');
        if (pos != std::string::npos) {
            std::string key = line.substr(0, pos);
            std::string value = line.substr(pos + 1);
            store_[key] = value;
        }
    }
}

std::optional<std::string> Repository::Get(const std::string& key) const {
    std::shared_lock<std::shared_mutex> lock(mutex_);

    auto it = store_.find(key);
    if (it != store_.end()) {
        return it->second;
    }

    return std::nullopt;
}

std::optional<std::string> Repository::Put(const std::string& key, const std::string& value) {
    std::unique_lock<std::shared_mutex> lock(mutex_);
    std::string prev_value;

    auto it = store_.find(key);
    if (it != store_.end()) {
        prev_value = store_[key];
        store_[key] = value;

        return prev_value;
    }
    store_[key] = value;

    return std::nullopt;
}

bool Repository::Delete(const std::string& key) {
    std::unique_lock<std::shared_mutex> lock(mutex_);

    auto it = store_.find(key);
    if (it != store_.end()) {
        store_.erase(it);
        return true;
    }

    return false;
}

bool Repository::Dump(const std::string& file_name) const {
    std::shared_lock<std::shared_mutex> lock(mutex_);

    std::ofstream file(file_name);

    if (!file.is_open()) {
        return false;
    }

    for (const auto& pair : store_) {
        file << pair.first << " " << pair.second << "\n";
    }

    return true;
}

size_t Repository::Count() const {
    std::shared_lock<std::shared_mutex> lock(mutex_);

    return store_.size();
}