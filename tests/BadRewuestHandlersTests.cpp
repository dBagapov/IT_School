#include <gtest/gtest.h>
#include "MockRepository.h"
#include "src/Handlers/Handlers.h"
#include "spdlog/sinks/ostream_sink.h"
#include "spdlog/logger.h"
#include "spdlog/spdlog.h"

class BadRequestHandlersTest : public ::testing::Test {
protected:
    void SetUp() override {
        command_handler = std::make_shared<PutHandler>();
        command_handler->SetNext(std::make_shared<GetHandler>())
                ->SetNext(std::make_shared<DeleteHandler>())
                ->SetNext(std::make_shared<CountHandler>())
                ->SetNext(std::make_shared<DumpHandler>())
                ->SetNext(std::make_shared<UnknownCommandHandler>());

        log_stream = std::make_shared<std::ostringstream>();
        auto ostream_sink = std::make_shared<spdlog::sinks::ostream_sink_mt>(*log_stream);
        logger = std::make_shared<spdlog::logger>("test_logger", ostream_sink);
        spdlog::set_default_logger(logger);
    }

    std::shared_ptr<CommandHandler> command_handler;
    std::shared_ptr<std::ostringstream> log_stream;
    std::shared_ptr<spdlog::logger> logger;
};

TEST_F(BadRequestHandlersTest, IncorrectKeyPutRequest) {
    std::shared_ptr<MockRepository> mock_repo = std::make_shared<MockRepository>();
    std::string request = "PUT ke?!+ value\n";
    std::string response;

    std::shared_ptr<IRepository> repo = std::dynamic_pointer_cast<IRepository>(mock_repo);
    command_handler->Handle(request, repo, response);

    std::string logs = log_stream->str();

    ASSERT_EQ("NE\n", response);
    ASSERT_TRUE(logs.find("Incorrect key:"));
}

TEST_F(BadRequestHandlersTest, EmptyPutRequest) {
    std::shared_ptr<MockRepository> mock_repo = std::make_shared<MockRepository>();
    std::string request = "PUT key\n";
    std::string response;

    std::shared_ptr<IRepository> repo = std::dynamic_pointer_cast<IRepository>(mock_repo);
    command_handler->Handle(request, repo, response);

    std::string logs = log_stream->str();

    ASSERT_EQ("NE\n", response);
    ASSERT_TRUE(logs.find("Empty value not allowed for key"));
}

TEST_F(BadRequestHandlersTest, GetRequest) {
    std::shared_ptr<MockRepository> mock_repo = std::make_shared<MockRepository>();
    EXPECT_CALL(*mock_repo, Get("key")).WillOnce(testing::Return(std::nullopt));

    std::string request = "GET key\n";
    std::string response;

    std::shared_ptr<IRepository> repo = std::dynamic_pointer_cast<IRepository>(mock_repo);
    command_handler->Handle(request, repo, response);

    std::string logs = log_stream->str();

    ASSERT_EQ("NE\n", response);
    ASSERT_TRUE(logs.find("Key not found"));
}

TEST_F(BadRequestHandlersTest, DeleteRequest) {
    std::shared_ptr<MockRepository> mock_repo = std::make_shared<MockRepository>();
    EXPECT_CALL(*mock_repo, Delete("key")).WillOnce(testing::Return(false));

    std::string request = "DEL key\n";
    std::string response;

    std::shared_ptr<IRepository> repo = std::dynamic_pointer_cast<IRepository>(mock_repo);
    command_handler->Handle(request, repo, response);

    std::string logs = log_stream->str();

    ASSERT_EQ("NE\n", response);
    ASSERT_TRUE(logs.find("Key not found"));
}

TEST_F(BadRequestHandlersTest, CountRequest) {
    std::shared_ptr<MockRepository> mock_repo = std::make_shared<MockRepository>();
    EXPECT_CALL(*mock_repo, Count()).WillOnce(testing::Return(0));

    std::string request = "COUNT\n";
    std::string response;

    std::shared_ptr<IRepository> repo = std::dynamic_pointer_cast<IRepository>(mock_repo);
    command_handler->Handle(request, repo, response);

    std::string logs = log_stream->str();

    ASSERT_EQ("NE\n", response);
    ASSERT_TRUE(logs.find("Store is empty"));
}

TEST_F(BadRequestHandlersTest, DumpRequest) {
    std::shared_ptr<MockRepository> mock_repo = std::make_shared<MockRepository>();
    EXPECT_CALL(*mock_repo, Dump("file_name")).WillOnce(testing::Return(false));

    std::string request = "DUMP file_name\n";
    std::string response;

    std::shared_ptr<IRepository> repo = std::dynamic_pointer_cast<IRepository>(mock_repo);
    command_handler->Handle(request, repo, response);

    std::string logs = log_stream->str();

    ASSERT_EQ("NE\n", response);
    ASSERT_TRUE(logs.find("File not found"));
}

TEST_F(BadRequestHandlersTest, IncorrectCommandRequest) {
    std::shared_ptr<MockRepository> mock_repo = std::make_shared<MockRepository>();

    std::string request = "command key\n";
    std::string response;

    std::shared_ptr<IRepository> repo = std::dynamic_pointer_cast<IRepository>(mock_repo);
    command_handler->Handle(request, repo, response);

    std::string logs = log_stream->str();

    ASSERT_EQ("NE\n", response);
    ASSERT_TRUE(logs.find("Command not found"));
}