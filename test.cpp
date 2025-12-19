#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include <vector>
#include <type_traits>
#include "stack.h"
#include "queue.h"

// ==================== TESTS FOR STACK ====================

TEST(StackTest, DefaultConstructor) {
    Stack<int> s;
    EXPECT_TRUE(s.empty());
    EXPECT_EQ(s.size(), 0);
}

TEST(StackTest, PushAndPop) {
    Stack<int> s;
    
    s.push(10);
    EXPECT_FALSE(s.empty());
    EXPECT_EQ(s.size(), 1);
    EXPECT_EQ(s.front(), 10);
    EXPECT_EQ(s.top(), 10);
    
    s.push(20);
    EXPECT_EQ(s.size(), 2);
    EXPECT_EQ(s.front(), 20);
    
    EXPECT_EQ(s.pop(), 20);
    EXPECT_EQ(s.pop(), 10);
    EXPECT_TRUE(s.empty());
}

TEST(StackTest, CopyConstructor) {
    Stack<int> s1;
    s1.push(1);
    s1.push(2);
    s1.push(3);
    
    Stack<int> s2 = s1;
    EXPECT_EQ(s1.size(), 3);
    EXPECT_EQ(s2.size(), 3);
    EXPECT_EQ(s1.front(), 3);
    EXPECT_EQ(s2.front(), 3);
    
    s1.pop();
    EXPECT_EQ(s1.size(), 2);
    EXPECT_EQ(s2.size(), 3);
}

TEST(StackTest, MoveConstructor) {
    Stack<std::string> s1;
    s1.push("Hello");
    s1.push("World");
    
    Stack<std::string> s2 = std::move(s1);
    EXPECT_TRUE(s1.empty());
    EXPECT_EQ(s1.size(), 0);
    EXPECT_EQ(s2.size(), 2);
    EXPECT_EQ(s2.front(), "World");
}

TEST(StackTest, InitializerListConstructor) {
    Stack<int> s = {1, 2, 3, 4, 5};
    EXPECT_EQ(s.size(), 5);
    EXPECT_EQ(s.front(), 5);
    
    EXPECT_EQ(s.pop(), 5);
    EXPECT_EQ(s.pop(), 4);
    EXPECT_EQ(s.pop(), 3);
    EXPECT_EQ(s.pop(), 2);
    EXPECT_EQ(s.pop(), 1);
}

TEST(StackTest, AssignmentOperator) {
    Stack<int> s1 = {1, 2, 3};
    Stack<int> s2;
    
    s2 = s1;
    EXPECT_EQ(s1.size(), 3);
    EXPECT_EQ(s2.size(), 3);
    EXPECT_EQ(s1.front(), 3);
    EXPECT_EQ(s2.front(), 3);
    
    s2 = s2;
    EXPECT_EQ(s2.size(), 3);
}

TEST(StackTest, MoveAssignment) {
    Stack<int> s1 = {1, 2, 3};
    Stack<int> s2;
    
    s2 = std::move(s1);
    EXPECT_TRUE(s1.empty());
    EXPECT_EQ(s2.size(), 3);
    EXPECT_EQ(s2.front(), 3);
}

TEST(StackTest, Clear) {
    Stack<int> s;
    s.push(1);
    s.push(2);
    s.push(3);
    
    EXPECT_EQ(s.size(), 3);
    s.clear();
    EXPECT_TRUE(s.empty());
    EXPECT_EQ(s.size(), 0);
}

TEST(StackTest, Swap) {
    Stack<int> s1 = {1, 2, 3};
    Stack<int> s2 = {4, 5, 6, 7};
    
    s1.swap(s2);
    EXPECT_EQ(s1.size(), 4);
    EXPECT_EQ(s2.size(), 3);
    EXPECT_EQ(s1.front(), 7);
    EXPECT_EQ(s2.front(), 3);
}

TEST(StackTest, Equality) {
    Stack<int> s1 = {1, 2, 3};
    Stack<int> s2 = {1, 2, 3};
    Stack<int> s3 = {1, 2};
    Stack<int> s4 = {1, 2, 4};
    
    EXPECT_TRUE(s1 == s2);
    EXPECT_FALSE(s1 == s3);
    EXPECT_FALSE(s1 == s4);
    EXPECT_TRUE(s1 != s3);
}

TEST(StackTest, Iterators) {
    Stack<int> s = {1, 2, 3, 4, 5};
    
    int sum = 0;
    for (auto it = s.begin(); it != s.end(); ++it) {
        sum += *it;
    }
    EXPECT_EQ(sum, 15); // 5 + 4 + 3 + 2 + 1 = 15
    const Stack<int>& cs = s;
    sum = 0;
    for (auto it = cs.begin(); it != cs.end(); ++it) {
        sum += *it;
    }
    EXPECT_EQ(sum, 15);
}

TEST(StackTest, RangeBasedForLoop) {
    Stack<int> s = {1, 2, 3};
    
    std::vector<int> result;
    for (const auto& item : s) {
        result.push_back(item);
    }
    EXPECT_EQ(result.size(), 3);
    EXPECT_EQ(result[0], 3);
    EXPECT_EQ(result[1], 2);
    EXPECT_EQ(result[2], 1);
}

TEST(StackTest, Emplace) {
    Stack<std::pair<int, std::string>> s;
    s.emplace(1, "Hello");
    s.emplace(2, "World");
    
    EXPECT_EQ(s.size(), 2);
    auto item = s.pop();
    EXPECT_EQ(item.first, 2);
    EXPECT_EQ(item.second, "World");
}

TEST(StackTest, StreamOutput) {
    Stack<int> s = {1, 2, 3};
    std::ostringstream oss;
    oss << s;
    EXPECT_EQ(oss.str(), "3 2 1");
}

TEST(StackTest, StreamInput) {
    Stack<int> s;
    std::istringstream iss("10 20 30");
    iss >> s;
    
    EXPECT_EQ(s.size(), 3);
    EXPECT_EQ(s.pop(), 30);
    EXPECT_EQ(s.pop(), 20);
    EXPECT_EQ(s.pop(), 10);
}

TEST(StackTest, ExceptionOnEmptyPop) {
    Stack<int> s;
    EXPECT_THROW(s.pop(), ContainerException);
}

TEST(StackTest, ExceptionOnEmptyFront) {
    Stack<int> s;
    EXPECT_THROW(s.front(), ContainerException);
}

TEST(StackTest, LargeStack) {
    Stack<int> s;
    const int N = 1000;
    
    for (int i = 0; i < N; ++i) {
        s.push(i);
    }
    
    EXPECT_EQ(s.size(), N);
    
    for (int i = N - 1; i >= 0; --i) {
        EXPECT_EQ(s.pop(), i);
    }
    
    EXPECT_TRUE(s.empty());
}

TEST(StackTest, DifferentTypes) {
    Stack<double> s;
    s.push(3.14);
    s.push(2.71);
    EXPECT_DOUBLE_EQ(s.pop(), 2.71);
    EXPECT_DOUBLE_EQ(s.pop(), 3.14);
}

// ==================== TESTS FOR QUEUE ====================

TEST(QueueTest, DefaultConstructor) {
    Queue<int> q;
    EXPECT_TRUE(q.empty());
    EXPECT_EQ(q.size(), 0);
}

TEST(QueueTest, PushAndPop) {
    Queue<int> q;
    
    q.push(10);
    EXPECT_FALSE(q.empty());
    EXPECT_EQ(q.size(), 1);
    EXPECT_EQ(q.front(), 10);
    
    q.push(20);
    EXPECT_EQ(q.size(), 2);
    EXPECT_EQ(q.front(), 10);
    
    EXPECT_EQ(q.pop(), 10);
    EXPECT_EQ(q.front(), 20);
    EXPECT_EQ(q.pop(), 20);
    EXPECT_TRUE(q.empty());
}

TEST(QueueTest, Back) {
    Queue<int> q;
    q.push(10);
    EXPECT_EQ(q.back(), 10);
    
    q.push(20);
    EXPECT_EQ(q.back(), 20);
    
    q.push(30);
    EXPECT_EQ(q.back(), 30);
}

TEST(QueueTest, CopyConstructor) {
    Queue<int> q1;
    q1.push(1);
    q1.push(2);
    q1.push(3);
    
    Queue<int> q2 = q1;
    EXPECT_EQ(q1.size(), 3);
    EXPECT_EQ(q2.size(), 3);
    EXPECT_EQ(q1.front(), 1);
    EXPECT_EQ(q2.front(), 1);
    
    // Изменение оригинала не должно влиять на копию
    q1.pop();
    EXPECT_EQ(q1.size(), 2);
    EXPECT_EQ(q2.size(), 3);
}

TEST(QueueTest, MoveConstructor) {
    Queue<std::string> q1;
    q1.push("Hello");
    q1.push("World");
    
    Queue<std::string> q2 = std::move(q1);
    EXPECT_TRUE(q1.empty());
    EXPECT_EQ(q1.size(), 0);
    EXPECT_EQ(q2.size(), 2);
    EXPECT_EQ(q2.front(), "Hello");
}

TEST(QueueTest, InitializerListConstructor) {
    Queue<int> q = {1, 2, 3, 4, 5};
    EXPECT_EQ(q.size(), 5);
    EXPECT_EQ(q.front(), 1);
    EXPECT_EQ(q.back(), 5);
}

TEST(QueueTest, AssignmentOperator) {
    Queue<int> q1 = {1, 2, 3};
    Queue<int> q2;
    
    q2 = q1;
    EXPECT_EQ(q1.size(), 3);
    EXPECT_EQ(q2.size(), 3);
    EXPECT_EQ(q1.front(), 1);
    EXPECT_EQ(q2.front(), 1);
}

TEST(QueueTest, MoveAssignment) {
    Queue<int> q1 = {1, 2, 3};
    Queue<int> q2;
    
    q2 = std::move(q1);
    EXPECT_TRUE(q1.empty());
    EXPECT_EQ(q2.size(), 3);
    EXPECT_EQ(q2.front(), 1);
}

TEST(QueueTest, Clear) {
    Queue<int> q;
    q.push(1);
    q.push(2);
    q.push(3);
    
    EXPECT_EQ(q.size(), 3);
    q.clear();
    EXPECT_TRUE(q.empty());
    EXPECT_EQ(q.size(), 0);
}

TEST(QueueTest, Swap) {
    Queue<int> q1 = {1, 2, 3};
    Queue<int> q2 = {4, 5, 6, 7};
    
    q1.swap(q2);
    EXPECT_EQ(q1.size(), 4);
    EXPECT_EQ(q2.size(), 3);
    EXPECT_EQ(q1.front(), 4);
    EXPECT_EQ(q2.front(), 1);
}

TEST(QueueTest, Equality) {
    Queue<int> q1 = {1, 2, 3};
    Queue<int> q2 = {1, 2, 3};
    Queue<int> q3 = {1, 2};
    Queue<int> q4 = {1, 2, 4};
    
    EXPECT_TRUE(q1 == q2);
    EXPECT_FALSE(q1 == q3);
    EXPECT_FALSE(q1 == q4);
    EXPECT_TRUE(q1 != q3);
}

TEST(QueueTest, StreamOutput) {
    Queue<int> q = {1, 2, 3};
    std::ostringstream oss;
    oss << q;
    EXPECT_EQ(oss.str(), "1 2 3");
}

TEST(QueueTest, StreamInput) {
    Queue<int> q;
    std::istringstream iss("10 20 30");
    iss >> q;
    
    EXPECT_EQ(q.size(), 3);
    EXPECT_EQ(q.pop(), 10);
    EXPECT_EQ(q.pop(), 20);
    EXPECT_EQ(q.pop(), 30);
}

TEST(QueueTest, Iterators) {
    Queue<int> q = {1, 2, 3, 4, 5};
    
    int sum = 0;
    for (auto it = q.begin(); it != q.end(); ++it) {
        sum += *it;
    }
    EXPECT_EQ(sum, 15);
}

TEST(QueueTest, RangeBasedForLoop) {
    Queue<int> q = {1, 2, 3};
    
    std::vector<int> result;
    for (const auto& item : q) {
        result.push_back(item);
    }
    
    std::vector<int> expected = {1, 2, 3};
    EXPECT_EQ(result, expected);
}

TEST(QueueTest, Emplace) {
    Queue<std::pair<int, std::string>> q;
    q.emplace(1, "Hello");
    q.emplace(2, "World");
    
    EXPECT_EQ(q.size(), 2);
    auto item = q.pop();
    EXPECT_EQ(item.first, 1);
    EXPECT_EQ(item.second, "Hello");
}

TEST(QueueTest, ExceptionOnEmptyPop) {
    Queue<int> q;
    EXPECT_THROW(q.pop(), ContainerException);
}

TEST(QueueTest, ExceptionOnEmptyFront) {
    Queue<int> q;
    EXPECT_THROW(q.front(), ContainerException);
}

TEST(QueueTest, ExceptionOnEmptyBack) {
    Queue<int> q;
    EXPECT_THROW(q.back(), ContainerException);
}

TEST(QueueTest, LargeQueue) {
    Queue<int> q;
    const int N = 1000;
    
    for (int i = 0; i < N; ++i) {
        q.push(i);
    }
    
    EXPECT_EQ(q.size(), N);
    
    for (int i = 0; i < N; ++i) {
        EXPECT_EQ(q.pop(), i);
    }
    
    EXPECT_TRUE(q.empty());
}

TEST(QueueTest, DifferentTypes) {
    Queue<double> q;
    q.push(3.14);
    q.push(2.71);
    EXPECT_DOUBLE_EQ(q.pop(), 3.14);
    EXPECT_DOUBLE_EQ(q.pop(), 2.71);
}

// ==================== COMPARATIVE TESTS ====================

TEST(ComparativeTest, StackVsQueueBehavior) {
    Stack<int> s;
    Queue<int> q;
    
    s.push(1); s.push(2); s.push(3);
    q.push(1); q.push(2); q.push(3);
    
    EXPECT_EQ(s.pop(), 3);  // LIFO
    EXPECT_EQ(q.pop(), 1);  // FIFO
}

TEST(ComparativeTest, StressTest) {
    const int N = 10000;
    
    Stack<int> s;
    Queue<int> q;
    
    for (int i = 0; i < N; ++i) {
        s.push(i);
        q.push(i);
    }
    
    EXPECT_EQ(s.size(), N);
    EXPECT_EQ(q.size(), N);
    
    for (int i = N - 1; i >= 0; --i) {
        EXPECT_EQ(s.pop(), i);
    }
    
    for (int i = 0; i < N; ++i) {
        EXPECT_EQ(q.pop(), i);
    }
}

// ==================== EDGE CASES ====================

TEST(EdgeCaseTest, EmptyContainers) {
    Stack<int> s1, s2;
    EXPECT_TRUE(s1 == s2);
    EXPECT_FALSE(s1 != s2);
    
    Queue<int> q1, q2;
    EXPECT_TRUE(q1 == q2);
    EXPECT_FALSE(q1 != q2);
}

TEST(EdgeCaseTest, SingleElement) {
    Stack<int> s;
    s.push(42);
    EXPECT_EQ(s.size(), 1);
    EXPECT_EQ(s.front(), 42);
    EXPECT_EQ(s.pop(), 42);
    EXPECT_TRUE(s.empty());
    
    Queue<int> q;
    q.push(42);
    EXPECT_EQ(q.size(), 1);
    EXPECT_EQ(q.front(), 42);
    EXPECT_EQ(q.back(), 42);
    EXPECT_EQ(q.pop(), 42);
    EXPECT_TRUE(q.empty());
}

TEST(EdgeCaseTest, SelfSwap) {
    Stack<int> s = {1, 2, 3};
    s.swap(s);
    EXPECT_EQ(s.size(), 3);
    EXPECT_EQ(s.front(), 3);
    
    Queue<int> q = {1, 2, 3};
    q.swap(q);
    EXPECT_EQ(q.size(), 3);
    EXPECT_EQ(q.front(), 1);
}

TEST(EdgeCaseTest, IteratorValidity) {
    Stack<int> s = {1, 2, 3};
    auto it = s.begin();
    EXPECT_EQ(*it, 3);

    s.push(4);
    EXPECT_EQ(*it, 3);
    
    auto it2 = s.begin();
    EXPECT_EQ(*it2, 4);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}