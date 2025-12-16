#ifndef NODE_H_INCLUDED
#define NODE_H_INCLUDED

#include <utility>

template<typename T>
class Node {
public:
    T data;
    Node* next;

    explicit Node(const T& value);
    explicit Node(T&& value);
    Node(const Node&) = delete;
    Node& operator=(const Node&) = delete;
    ~Node() = default;
    Node(Node&&) = delete;
    Node& operator=(Node&&) = delete;
};

#include "node.hpp"
#endif // NODE_H_INCLUDED
