#pragma once

#include "IRepository.h"
#include <unordered_map>
#include <shared_mutex>
#include <optional>

class Repository : public IRepository {
    std::unordered_map<std::string, std::string> store_;
    mutable std::shared_mutex mutex_;
public:
    Repository() = default;
    explicit Repository(const std::string& file_name);

    Repository(const Repository& other) = delete;
    Repository& operator=(const Repository& other) = delete;

    std::optional<std::string> Get(const std::string& key) const override;
    std::optional<std::string> Put(const std::string& key, const std::string& value) override;
    size_t Count() const override;
    bool Delete(const std::string& key) override;
    bool Dump(const std::string& file_name) const override;
};