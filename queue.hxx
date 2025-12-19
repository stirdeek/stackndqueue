#ifndef QUEUE_HXX
#define QUEUE_HXX

#include "queue.h"
#include <algorithm>
#include <initializer_list>
#include <stdexcept>
#include <utility>

template<typename T>
Queue<T>::Queue() : head_(nullptr), tail_(nullptr), size_(0) {}

template<typename T>
Queue<T>::Queue(size_t /*capacity*/) : head_(nullptr), tail_(nullptr), size_(0) {}

template<typename T>
Queue<T>::Queue(const Queue& other) : head_(nullptr), tail_(nullptr), size_(0) {
    copy_from(other);
}

template<typename T>
Queue<T>::Queue(Queue&& other) noexcept 
    : head_(other.head_), tail_(other.tail_), size_(other.size_) {
    other.head_ = other.tail_ = nullptr;
    other.size_ = 0;
}

template<typename T>
Queue<T>::Queue(std::initializer_list<T> init) 
    : head_(nullptr), tail_(nullptr), size_(0) {
    for (const auto& item : init) {
        push(item);
    }
}

template<typename T>
Queue<T>::~Queue() {
    clear();
}

template<typename T>
Queue<T>& Queue<T>::operator=(const Queue& other) {
    if (this != &other) {
        clear();
        copy_from(other);
    }
    return *this;
}

template<typename T>
Queue<T>& Queue<T>::operator=(Queue&& other) noexcept {
    if (this != &other) {
        clear();
        head_ = other.head_;
        tail_ = other.tail_;
        size_ = other.size_;
        
        other.head_ = other.tail_ = nullptr;
        other.size_ = 0;
    }
    return *this;
}

template<typename T>
Queue<T>& Queue<T>::operator=(std::initializer_list<T> init) {
    clear();
    for (const auto& item : init) {
        push(item);
    }
    return *this;
}

template<typename T>
void Queue<T>::push(const T& value) {
    Node<T>* new_node = new Node<T>(value);
    if (!tail_) {
        head_ = tail_ = new_node;
    } else {
        tail_->next = new_node;
        tail_ = new_node;
    }
    ++size_;
}

template<typename T>
void Queue<T>::push(T&& value) {
    Node<T>* new_node = new Node<T>(std::move(value));
    if (!tail_) {
        head_ = tail_ = new_node;
    } else {
        tail_->next = new_node;
        tail_ = new_node;
    }
    ++size_;
}

template<typename T>
template<typename... Args>
void Queue<T>::emplace(Args&&... args) {
    Node<T>* new_node = new Node<T>(std::forward<Args>(args)...);
    if (!tail_) {
        head_ = tail_ = new_node;
    } else {
        tail_->next = new_node;
        tail_ = new_node;
    }
    ++size_;
}

template<typename T>
T Queue<T>::pop() {
    if (!head_) throw ContainerException("pop from empty queue");
    
    T value = std::move(head_->data);
    Node<T>* temp = head_;
    head_ = head_->next;
    
    if (!head_) {
        tail_ = nullptr;
    }
    
    delete temp;
    --size_;
    
    return value;
}

template<typename T>
T& Queue<T>::front() {
    if (!head_) throw ContainerException("front from empty queue");
    return head_->data;
}

template<typename T>
const T& Queue<T>::front() const {
    if (!head_) throw ContainerException("front from empty queue");
    return head_->data;
}

template<typename T>
T& Queue<T>::back() {
    if (!tail_) throw ContainerException("back from empty queue");
    return tail_->data;
}

template<typename T>
const T& Queue<T>::back() const {
    if (!tail_) throw ContainerException("back from empty queue");
    return tail_->data;
}

template<typename T>
bool Queue<T>::empty() const {
    return head_ == nullptr;
}

template<typename T>
size_t Queue<T>::size() const {
    return size_;
}

template<typename T>
void Queue<T>::clear() {
    while (head_) {
        Node<T>* temp = head_;
        head_ = head_->next;
        delete temp;
    }
    tail_ = nullptr;
    size_ = 0;
}

// Итераторы
template<typename T>
typename Queue<T>::iterator Queue<T>::begin() {
    return iterator(head_);
}

template<typename T>
typename Queue<T>::iterator Queue<T>::end() {
    return iterator(nullptr);
}

template<typename T>
typename Queue<T>::const_iterator Queue<T>::begin() const {
    return const_iterator(head_);
}

template<typename T>
typename Queue<T>::const_iterator Queue<T>::end() const {
    return const_iterator(nullptr);
}

template<typename T>
typename Queue<T>::const_iterator Queue<T>::cbegin() const {
    return const_iterator(head_);
}

template<typename T>
typename Queue<T>::const_iterator Queue<T>::cend() const {
    return const_iterator(nullptr);
}

template<typename T>
void Queue<T>::swap(Queue& other) noexcept {
    std::swap(head_, other.head_);
    std::swap(tail_, other.tail_);
    std::swap(size_, other.size_);
}

template<typename T>
bool Queue<T>::operator==(const Queue& other) const {
    if (size_ != other.size_) return false;
    
    Node<T>* curr1 = head_;
    Node<T>* curr2 = other.head_;
    
    while (curr1 && curr2) {
        if (curr1->data != curr2->data) return false;
        curr1 = curr1->next;
        curr2 = curr2->next;
    }
    
    return true;
}

template<typename T>
bool Queue<T>::operator!=(const Queue& other) const {
    return !(*this == other);
}

// Вспомогательные методы
template<typename T>
void Queue<T>::copy_from(const Queue& other) {
    if (!other.head_) return;
    
    Node<T>* curr = other.head_;
    while (curr) {
        push(curr->data);
        curr = curr->next;
    }
}

template<typename T>
void swap(Queue<T>& a, Queue<T>& b) noexcept {
    a.swap(b);
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const Queue<T>& queue) {
    Node<T>* curr = queue.head_;
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
std::istream& operator>>(std::istream& is, Queue<T>& queue) {
    T value;
    while (is >> value) {
        queue.push(value);
    }
    return is;
}

#endif // QUEUE_HXX