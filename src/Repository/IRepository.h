#pragma once

#include <string>
#include <optional>

class IRepository {
public:
    virtual ~IRepository() = default;

    [[nodiscard]] virtual std::optional<std::string> Get(const std::string& key) const = 0;
    virtual std::optional<std::string> Put(const std::string& key, const std::string& value) = 0;
    [[nodiscard]] virtual size_t Count() const = 0;
    [[nodiscard]] virtual bool Dump(const std::string& file_name) const = 0;
    virtual bool Delete(const std::string& key) = 0;
};