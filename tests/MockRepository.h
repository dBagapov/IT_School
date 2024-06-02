#pragma once

#include <gmock/gmock.h>
#include "../src/Repository/IRepository.h"

class MockRepository : public IRepository {
public:
    MOCK_METHOD(std::optional<std::string>, Get, (const std::string& key), (const, override));
    MOCK_METHOD(std::optional<std::string>, Put, (const std::string& key, const std::string& value), (override));
    MOCK_METHOD(size_t, Count, (), (const, override));
    MOCK_METHOD(bool, Delete, (const std::string& key), (override));
    MOCK_METHOD(bool, Dump, (const std::string& file_name), (const, override));
};