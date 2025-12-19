#ifndef STACK_HXX
#define STACK_HXX

#include "stack.h"
#include <algorithm>
#include <initializer_list>
#include <stdexcept>
#include <utility>

template<typename T>
Stack<T>::Stack() : top_(nullptr), size_(0) {}

template<typename T>
Stack<T>::Stack(size_t /*capacity*/) : top_(nullptr), size_(0) {}

template<typename T>
Stack<T>::Stack(const Stack& other) : top_(nullptr), size_(0) {
    copy_from(other);
}

template<typename T>
Stack<T>::Stack(Stack&& other) noexcept 
    : top_(other.top_), size_(other.size_) {
    other.top_ = nullptr;
    other.size_ = 0;
}

template<typename T>
Stack<T>::Stack(std::initializer_list<T> init) : top_(nullptr), size_(0) {
    for (auto it = init.begin(); it != init.end(); ++it) {
        push(*it);
    }
}

template<typename T>
Stack<T>::~Stack() {
    clear();
}

template<typename T>
Stack<T>& Stack<T>::operator=(const Stack& other) {
    if (this != &other) {
        clear();
        copy_from(other);
    }
    return *this;
}

template<typename T>
Stack<T>& Stack<T>::operator=(Stack&& other) noexcept {
    if (this != &other) {
        clear();
        top_ = other.top_;
        size_ = other.size_;
        
        other.top_ = nullptr;
        other.size_ = 0;
    }
    return *this;
}

template<typename T>
Stack<T>& Stack<T>::operator=(std::initializer_list<T> init) {
    clear();
    for (const auto& item : init) {
        push(item);
    }
    return *this;
}

// Базовый интерфейс
template<typename T>
void Stack<T>::push(const T& value) {
    Node<T>* new_node = new Node<T>(value);
    new_node->next = top_;
    top_ = new_node;
    ++size_;
}

template<typename T>
void Stack<T>::push(T&& value) {
    Node<T>* new_node = new Node<T>(std::move(value));
    new_node->next = top_;
    top_ = new_node;
    ++size_;
}

template<typename T>
template<typename... Args>
void Stack<T>::emplace(Args&&... args) {
    Node<T>* new_node = new Node<T>(std::forward<Args>(args)...);
    new_node->next = top_;
    top_ = new_node;
    ++size_;
}

template<typename T>
T Stack<T>::pop() {
    if (!top_) throw ContainerException("pop from empty stack");
    
    T value = std::move(top_->data);
    Node<T>* temp = top_;
    top_ = top_->next;
    delete temp;
    --size_;
    
    return value;
}

template<typename T>
T& Stack<T>::front() {
    if (!top_) throw ContainerException("front from empty stack");
    return top_->data;
}

template<typename T>
const T& Stack<T>::front() const {
    if (!top_) throw ContainerException("front from empty stack");
    return top_->data;
}

template<typename T>
bool Stack<T>::empty() const {
    return top_ == nullptr;
}

template<typename T>
size_t Stack<T>::size() const {
    return size_;
}

template<typename T>
void Stack<T>::clear() {
    while (top_) {
        Node<T>* temp = top_;
        top_ = top_->next;
        delete temp;
    }
    size_ = 0;
}

// Итераторы
template<typename T>
typename Stack<T>::iterator Stack<T>::begin() {
    return iterator(top_);
}

template<typename T>
typename Stack<T>::iterator Stack<T>::end() {
    return iterator(nullptr);
}

template<typename T>
typename Stack<T>::const_iterator Stack<T>::begin() const {
    return const_iterator(top_);
}

template<typename T>
typename Stack<T>::const_iterator Stack<T>::end() const {
    return const_iterator(nullptr);
}

template<typename T>
typename Stack<T>::const_iterator Stack<T>::cbegin() const {
    return const_iterator(top_);
}

template<typename T>
typename Stack<T>::const_iterator Stack<T>::cend() const {
    return const_iterator(nullptr);
}

template<typename T>
void Stack<T>::swap(Stack& other) noexcept {
    std::swap(top_, other.top_);
    std::swap(size_, other.size_);
}

template<typename T>
bool Stack<T>::operator==(const Stack& other) const {
    if (size_ != other.size_) return false;
    
    Node<T>* curr1 = top_;
    Node<T>* curr2 = other.top_;
    
    while (curr1 && curr2) {
        if (curr1->data != curr2->data) return false;
        curr1 = curr1->next;
        curr2 = curr2->next;
    }
    
    return true;
}

template<typename T>
bool Stack<T>::operator!=(const Stack& other) const {
    return !(*this == other);
}

template<typename T>
void Stack<T>::copy_from(const Stack& other) {
    if (!other.top_) return;
    
    Node<T>* curr = other.top_;
    Stack<T> temp;
    while (curr) {
        temp.push(curr->data);
        curr = curr->next;
    }
    
    while (!temp.empty()) {
        push(temp.pop());
    }
}

template<typename T>
void swap(Stack<T>& a, Stack<T>& b) noexcept {
    a.swap(b);
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const Stack<T>& stack) {
    Node<T>* curr = stack.top_;
    bool first = true;
    while (curr) {
        if (!first) os << " ";
        os << curr->data;
        first = false;
        curr = curr->next;
    }
    return os;
}

template<typename T>
std::istream& operator>>(std::istream& is, Stack<T>& stack) {
    T value;
    while (is >> value) {
        stack.push(value);
    }
    return is;
}

#endif // STACK_HXX