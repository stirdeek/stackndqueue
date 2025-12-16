#ifndef QUEUE_HPP_INCLUDED
#define QUEUE_HPP_INCLUDED

#include "Queue.h"

template<typename T>
Queue<T>::Queue() : head_(nullptr), tail_(nullptr), size_(0) {}

template<typename T>
void Queue<T>::copy_from(const Queue& other) {
    if (!other.head_) {
        head_ = tail_ = nullptr;
        size_ = 0;
        return;
    }

    Node<T>* current = other.head_;
    while (current) {
        this->push(current->data);
        current = current->next;
    }
}

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
Queue<T>::~Queue() {
    clear();
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
void Queue<T>::pop() {
    if (!head_) throw ContainerException("pop from empty queue");
    Node<T>* temp = head_;
    head_ = head_->next;
    if (!head_) {
        tail_ = nullptr;
    }
    delete temp;
    --size_;
}

template<typename T>
T& Queue<T>::get_front() {
    if (!head_) throw ContainerException("front from empty queue");
    return head_->data;
}

template<typename T>
const T& Queue<T>::get_front() const {
    if (!head_) throw ContainerException("front from empty queue");
    return head_->data;
}

template<typename T>
bool Queue<T>::is_empty() const {
    return head_ == nullptr;
}

template<typename T>
size_t Queue<T>::size() const {
    return size_;
}

template<typename T>
typename Queue<T>::iterator Queue<T>::begin() {
    return iterator(new QueueIterator(head_));
}

template<typename T>
typename Queue<T>::iterator Queue<T>::end() {
    return iterator(new QueueIterator(nullptr));
}

template<typename T>
typename Queue<T>::const_iterator Queue<T>::cbegin() const {
    return const_iterator(new ConstQueueIterator(head_));
}

template<typename T>
typename Queue<T>::const_iterator Queue<T>::cend() const {
    return const_iterator(new ConstQueueIterator(nullptr));
}

template<typename T>
Queue<T>::QueueIterator::QueueIterator(Node<T>* node) : current_(node) {}

template<typename T>
void* Queue<T>::QueueIterator::get_node() {
    return static_cast<void*>(current_);
}

template<typename T>
const void* Queue<T>::QueueIterator::get_node() const {
    return static_cast<const void*>(current_);
}

template<typename T>
T& Queue<T>::QueueIterator::deref() {
    return current_->data;
}

template<typename T>
void Queue<T>::QueueIterator::increment() {
    if (current_) {
        current_ = current_->next;
    }
}

template<typename T>
typename fwd_container<T>::iterator_base* Queue<T>::QueueIterator::clone() const {
    return new QueueIterator(current_);
}

template<typename T>
bool Queue<T>::QueueIterator::equals(const typename fwd_container<T>::iterator_base* other) const {
    return this->get_node() == other->get_node();
}

template<typename T>
Queue<T>::ConstQueueIterator::ConstQueueIterator(const Node<T>* node) : current_(node) {}

template<typename T>
const void* Queue<T>::ConstQueueIterator::get_node() const {
    return static_cast<const void*>(current_);
}

template<typename T>
const T& Queue<T>::ConstQueueIterator::deref() const {
    return current_->data;
}

template<typename T>
void Queue<T>::ConstQueueIterator::increment() {
    if (current_) {
        current_ = current_->next;
    }
}

template<typename T>
typename fwd_container<T>::const_iterator_base* Queue<T>::ConstQueueIterator::clone() const {
    return new ConstQueueIterator(current_);
}

template<typename T>
bool Queue<T>::ConstQueueIterator::equals(const typename fwd_container<T>::const_iterator_base* other) const {
    return this->get_node() == other->get_node();
}

#endif // QUEUE_HPP_INCLUDED
