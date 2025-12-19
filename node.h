#ifndef NODE_H
#define NODE_H

#include <utility>

template<typename T>
struct Node {
    T data;
    Node* next;

    explicit Node(const T& value) noexcept : data(value), next(nullptr) {}
    explicit Node(T&& value) noexcept : data(std::move(value)), next(nullptr) {}
    
    template<typename... Args>
    explicit Node(Args&&... args) noexcept 
        : data(std::forward<Args>(args)...), next(nullptr) {}

    Node(const Node&) = delete;
    Node& operator=(const Node&) = delete;
    Node(Node&&) = delete;
    Node& operator=(Node&&) = delete;
};

#endif // NODE_H