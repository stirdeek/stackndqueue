#include <gtest/gtest.h>
#include "stack.h"
#include "queue.h"
#include <sstream>
#include <string>

// Тесты для stack с int
TEST(StackIntTest, BasicOperations) {
    stack<int> s;
    EXPECT_TRUE(s.is_empty());
    EXPECT_EQ(s.size(), 0);

    s.push(1);
    s.push(2);
    s.push(3);

    EXPECT_FALSE(s.is_empty());
    EXPECT_EQ(s.size(), 3);
    EXPECT_EQ(s.get_front(), 3);

    EXPECT_EQ(s.pop(), 3);
    EXPECT_EQ(s.pop(), 2);
    EXPECT_EQ(s.pop(), 1);
    EXPECT_TRUE(s.is_empty());
}

TEST(StackIntTest, MoveOperations) {
    stack<std::string> s;
    std::string str = "hello";
    s.push(std::move(str));
    EXPECT_TRUE(str.empty());
    EXPECT_EQ(s.get_front(), "hello");
}

TEST(StackIntTest, IteratorTest) {
    stack<int> s;
    s.push(1);
    s.push(2);
    s.push(3);

    auto it = s.begin();
    EXPECT_EQ(*it, 1);
    ++it;
    EXPECT_EQ(*it, 2);
    ++it;
    EXPECT_EQ(*it, 3);
    ++it;
    EXPECT_EQ(it, s.end());
}

TEST(StackIntTest, ConstIteratorTest) {
    stack<int> s;
    s.push(1);
    s.push(2);
    s.push(3);

    const auto& cs = s;
    auto it = cs.begin();
    EXPECT_EQ(*it, 1);
    ++it;
    EXPECT_EQ(*it, 2);
}

TEST(StackIntTest, StreamOperations) {
    stack<int> s;
    std::istringstream iss("1 2 3 4 5");
    iss >> s;

    EXPECT_EQ(s.size(), 5);
    EXPECT_EQ(s.pop(), 5);
    EXPECT_EQ(s.pop(), 4);

    std::ostringstream oss;
    oss << s;
    EXPECT_FALSE(oss.str().empty());
}

// Тесты для queue с int
TEST(QueueIntTest, BasicOperations) {
    queue<int> q;
    EXPECT_TRUE(q.is_empty());
    EXPECT_EQ(q.size(), 0);

    q.push(1);
    q.push(2);
    q.push(3);

    EXPECT_FALSE(q.is_empty());
    EXPECT_EQ(q.size(), 3);
    EXPECT_EQ(q.get_front(), 1);

    EXPECT_EQ(q.pop(), 1);
    EXPECT_EQ(q.pop(), 2);
    EXPECT_EQ(q.pop(), 3);
    EXPECT_TRUE(q.is_empty());
}

TEST(QueueIntTest, MoveOperations) {
    queue<std::string> q;
    std::string str = "hello";
    q.push(std::move(str));
    EXPECT_TRUE(str.empty());
    EXPECT_EQ(q.get_front(), "hello");
}

TEST(QueueIntTest, IteratorTest) {
    queue<int> q;
    q.push(1);
    q.push(2);
    q.push(3);

    auto it = q.begin();
    EXPECT_EQ(*it, 1);
    ++it;
    EXPECT_EQ(*it, 2);
    ++it;
    EXPECT_EQ(*it, 3);
    ++it;
    EXPECT_EQ(it, q.end());
}

TEST(QueueIntTest, ConstIteratorTest) {
    queue<int> q;
    q.push(1);
    q.push(2);
    q.push(3);

    const auto& cq = q;
    auto it = cq.begin();
    EXPECT_EQ(*it, 1);
    ++it;
    EXPECT_EQ(*it, 2);
}

TEST(QueueIntTest, StreamOperations) {
    queue<int> q;
    std::istringstream iss("1 2 3 4 5");
    iss >> q;

    EXPECT_EQ(q.size(), 5);
    EXPECT_EQ(q.pop(), 1);
    EXPECT_EQ(q.pop(), 2);

    std::ostringstream oss;
    oss << q;
    EXPECT_FALSE(oss.str().empty());
}

// Тесты для stack с double
TEST(StackDoubleTest, BasicOperations) {
    stack<double> s;
    EXPECT_TRUE(s.is_empty());
    EXPECT_EQ(s.size(), 0);

    s.push(1.1);
    s.push(2.2);
    s.push(3.3);

    EXPECT_FALSE(s.is_empty());
    EXPECT_EQ(s.size(), 3);
    EXPECT_DOUBLE_EQ(s.get_front(), 3.3);

    EXPECT_DOUBLE_EQ(s.pop(), 3.3);
    EXPECT_DOUBLE_EQ(s.pop(), 2.2);
    EXPECT_DOUBLE_EQ(s.pop(), 1.1);
    EXPECT_TRUE(s.is_empty());
}

TEST(StackDoubleTest, IteratorTest) {
    stack<double> s;
    s.push(1.1);
    s.push(2.2);
    s.push(3.3);

    auto it = s.begin();
    EXPECT_DOUBLE_EQ(*it, 1.1);
    ++it;
    EXPECT_DOUBLE_EQ(*it, 2.2);
    ++it;
    EXPECT_DOUBLE_EQ(*it, 3.3);
}

// Тесты для queue с double
TEST(QueueDoubleTest, BasicOperations) {
    queue<double> q;
    EXPECT_TRUE(q.is_empty());
    EXPECT_EQ(q.size(), 0);

    q.push(1.1);
    q.push(2.2);
    q.push(3.3);

    EXPECT_FALSE(q.is_empty());
    EXPECT_EQ(q.size(), 3);
    EXPECT_DOUBLE_EQ(q.get_front(), 1.1);

    EXPECT_DOUBLE_EQ(q.pop(), 1.1);
    EXPECT_DOUBLE_EQ(q.pop(), 2.2);
    EXPECT_DOUBLE_EQ(q.pop(), 3.3);
    EXPECT_TRUE(q.is_empty());
}

TEST(QueueDoubleTest, IteratorTest) {
    queue<double> q;
    q.push(1.1);
    q.push(2.2);
    q.push(3.3);

    auto it = q.begin();
    EXPECT_DOUBLE_EQ(*it, 1.1);
    ++it;
    EXPECT_DOUBLE_EQ(*it, 2.2);
    ++it;
    EXPECT_DOUBLE_EQ(*it, 3.3);
}

// Тесты для stack с std::string
TEST(StackStringTest, BasicOperations) {
    stack<std::string> s;
    s.push("hello");
    s.push("world");
    s.push("test");

    EXPECT_EQ(s.pop(), "test");
    EXPECT_EQ(s.pop(), "world");
    EXPECT_EQ(s.pop(), "hello");
}

// Тесты для queue с std::string
TEST(QueueStringTest, BasicOperations) {
    queue<std::string> q;
    q.push("hello");
    q.push("world");
    q.push("test");

    EXPECT_EQ(q.pop(), "hello");
    EXPECT_EQ(q.pop(), "world");
    EXPECT_EQ(q.pop(), "test");
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
