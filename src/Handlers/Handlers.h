#pragma once

#include <string>
#include "memory"
#include "../Repository/Repository.h"


class CommandHandler {
public:
    virtual ~CommandHandler() = default;
    virtual void Handle(const std::string& message, std::shared_ptr<IRepository>& repository, std::string& response) = 0;
    std::shared_ptr<CommandHandler> SetNext(std::shared_ptr<CommandHandler> next_handler);

protected:
    std::shared_ptr<CommandHandler> next_handler_;
};

class PutHandler : public CommandHandler {
public:
    void Handle(const std::string& message, std::shared_ptr<IRepository>& repository, std::string& response) override;
};

class GetHandler : public CommandHandler {
public:
    void Handle(const std::string& message, std::shared_ptr<IRepository>& repository, std::string& response) override;
};

class DeleteHandler : public CommandHandler {
public:
    void Handle(const std::string& message, std::shared_ptr<IRepository>& repository, std::string& response) override;
};

class CountHandler : public CommandHandler {
public:
    void Handle(const std::string& message, std::shared_ptr<IRepository>& repository, std::string& response) override;
};

class DumpHandler : public CommandHandler {
public:
    void Handle(const std::string& message, std::shared_ptr<IRepository>& repository, std::string& response) override;
};

class UnknownCommandHandler : public CommandHandler {
public:
    void Handle(const std::string& message, std::shared_ptr<IRepository>& repository, std::string& response) override;
};



