#include <gtest/gtest.h>

#include "../src/Handlers/Handlers.h"
#include "MockRepository.h"

class HandlersTest : public ::testing::Test {
protected:
    void SetUp() override {
        command_handler = std::make_shared<PutHandler>();
        command_handler->SetNext(std::make_shared<GetHandler>())
                ->SetNext(std::make_shared<DeleteHandler>())
                ->SetNext(std::make_shared<CountHandler>())
                ->SetNext(std::make_shared<DumpHandler>())
                ->SetNext(std::make_shared<UnknownCommandHandler>());
    }

    std::shared_ptr<CommandHandler> command_handler;
};

TEST_F(HandlersTest, PutRequest) {
    std::shared_ptr<MockRepository> mock_repo = std::make_shared<MockRepository>();
    EXPECT_CALL(*mock_repo, Put("key", "value")).WillOnce(testing::Return(std::nullopt));

    std::string request = "PUT key value\n";
    std::string response;

    std::shared_ptr<IRepository> repo = std::dynamic_pointer_cast<IRepository>(mock_repo);
    command_handler->Handle(request, repo, response);

    ASSERT_EQ("OK\n", response);
}

TEST_F(HandlersTest, GetRequest) {
    std::shared_ptr<MockRepository> mock_repo = std::make_shared<MockRepository>();
    EXPECT_CALL(*mock_repo, Get("key")).WillOnce(testing::Return("value"));

    std::string request = "GET key\n";
    std::string response;

    std::shared_ptr<IRepository> repo = std::dynamic_pointer_cast<IRepository>(mock_repo);
    command_handler->Handle(request, repo, response);

    ASSERT_EQ("OK value\n", response);
}

TEST_F(HandlersTest, DeleteRequest) {
    std::shared_ptr<MockRepository> mock_repo = std::make_shared<MockRepository>();
    EXPECT_CALL(*mock_repo, Delete("key")).WillOnce(testing::Return(true));

    std::string request = "DEL key\n";
    std::string response;

    std::shared_ptr<IRepository> repo = std::dynamic_pointer_cast<IRepository>(mock_repo);
    command_handler->Handle(request, repo, response);

    ASSERT_EQ("OK\n", response);
}

TEST_F(HandlersTest, CountRequest) {
    std::shared_ptr<MockRepository> mock_repo = std::make_shared<MockRepository>();
    EXPECT_CALL(*mock_repo, Count()).WillOnce(testing::Return(1));

    std::string request = "COUNT\n";
    std::string response;

    std::shared_ptr<IRepository> repo = std::dynamic_pointer_cast<IRepository>(mock_repo);
    command_handler->Handle(request, repo, response);

    ASSERT_EQ("OK 1\n", response);
}

TEST_F(HandlersTest, DumpRequest) {
    std::shared_ptr<MockRepository> mock_repo = std::make_shared<MockRepository>();
    EXPECT_CALL(*mock_repo, Dump("file_name")).WillOnce(testing::Return(true));

    std::string request = "DUMP file_name\n";
    std::string response;

    std::shared_ptr<IRepository> repo = std::dynamic_pointer_cast<IRepository>(mock_repo);
    command_handler->Handle(request, repo, response);

    ASSERT_EQ("OK\n", response);
}





