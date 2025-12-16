#ifndef NODE_HPP_INCLUDED
#define NODE_HPP_INCLUDED

#include "node.h"

template<typename T>
Node<T>::Node(const T& value)
    : data(value), next(nullptr) {}

template<typename T>
Node<T>::Node(T&& value)
    : data(std::move(value)), next(nullptr) {}


#endif // NODE_HPP_INCLUDED
