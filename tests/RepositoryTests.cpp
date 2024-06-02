#include <gtest/gtest.h>
#include "src/Repository/Repository.h"

TEST(RepositoryTest, EmptyGetTest) {
    Repository repository;

    ASSERT_FALSE(repository.Get("key").has_value());
}

TEST(RepositoryTest, PutTest) {
    Repository repository;
    repository.Put("key", "value");

    ASSERT_TRUE(repository.Get("key").has_value());
    ASSERT_EQ("value", repository.Get("key").value());
}

TEST(RepositoryTest, PutAndOverwrite) {
    Repository repository;
    repository.Put("key1", "value1");

    auto old_value = repository.Put("key1", "value2");
    ASSERT_TRUE(old_value.has_value());
    ASSERT_EQ("value1", old_value.value());

    auto new_value = repository.Get("key1");
    ASSERT_TRUE(new_value.has_value());
    ASSERT_EQ("value2", new_value.value());
}

TEST(RepositoryTest, Count) {
    Repository repository;
    ASSERT_EQ(0, repository.Count());

    repository.Put("key1", "value1");
    ASSERT_EQ(1, repository.Count());

    repository.Put("key2", "value2");
    ASSERT_EQ(2, repository.Count());
}

TEST(RepositoryTest, Delete) {
    Repository repository;
    repository.Put("key", "value");

    ASSERT_TRUE(repository.Delete("key"));
    ASSERT_FALSE(repository.Get("key").has_value());
}

TEST(RepositoryTest, DeleteNonExistentKey) {
    Repository repository;
    ASSERT_FALSE(repository.Delete("key"));
}