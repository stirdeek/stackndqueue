#ifndef STACK_HPP_INCLUDED
#define STACK_HPP_INCLUDED

#include "stack.h"

template<typename T>
Stack<T>::Stack() : top_(nullptr), size_(0) {}

template<typename T>
void Stack<T>::copy_from(const Stack& other) {
    if (!other.top_) {
        top_ = nullptr;
        size_ = 0;
        return;
    }

    Stack<T> temp;
    Node<T>* current = other.top_;
    while (current) {
        temp.push(current->data);
        current = current->next;
    }

    current = temp.top_;
    while (current) {
        this->push(current->data);
        current = current->next;
    }
}

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
Stack<T>::~Stack() {
    clear();
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
void Stack<T>::pop() {
    if (!top_) throw ContainerException("pop from empty stack");
    Node<T>* temp = top_;
    top_ = top_->next;
    delete temp;
    --size_;
}

template<typename T>
T& Stack<T>::get_front() {
    if (!top_) throw ContainerException("front from empty stack");
    return top_->data;
}

template<typename T>
const T& Stack<T>::get_front() const {
    if (!top_) throw ContainerException("front from empty stack");
    return top_->data;
}

template<typename T>
bool Stack<T>::is_empty() const {
    return top_ == nullptr;
}

template<typename T>
size_t Stack<T>::size() const {
    return size_;
}

template<typename T>
typename Stack<T>::iterator Stack<T>::begin() {
    return iterator(new StackIterator(top_));
}

template<typename T>
typename Stack<T>::iterator Stack<T>::end() {
    return iterator(new StackIterator(nullptr));
}

template<typename T>
typename Stack<T>::const_iterator Stack<T>::cbegin() const {
    return const_iterator(new ConstStackIterator(top_));
}

template<typename T>
typename Stack<T>::const_iterator Stack<T>::cend() const {
    return const_iterator(new ConstStackIterator(nullptr));
}
//Вот здесь я вставила
template<typename T>
typename Stack<T>::const_iterator Stack<T>::begin() const {
    return cbegin();
}

template<typename T>
typename Stack<T>::const_iterator Stack<T>::end() const {
    return cend();
}


template<typename T>
Stack<T>::StackIterator::StackIterator(Node<T>* node) : current_(node) {}

template<typename T>
void* Stack<T>::StackIterator::get_node() {
    return static_cast<void*>(current_);
}

template<typename T>
const void* Stack<T>::StackIterator::get_node() const {
    return static_cast<const void*>(current_);
}

template<typename T>
T& Stack<T>::StackIterator::deref() {
    return current_->data;
}

template<typename T>
void Stack<T>::StackIterator::increment() {
    if (current_) {
        current_ = current_->next;
    }
}

template<typename T>
typename fwd_container<T>::iterator_base* Stack<T>::StackIterator::clone() const {
    return new StackIterator(current_);
}

template<typename T>
bool Stack<T>::StackIterator::equals(const typename fwd_container<T>::iterator_base* other) const {
    return this->get_node() == other->get_node();
}

template<typename T>
Stack<T>::ConstStackIterator::ConstStackIterator(const Node<T>* node) : current_(node) {}

template<typename T>
const void* Stack<T>::ConstStackIterator::get_node() const {
    return static_cast<const void*>(current_);
}

template<typename T>
const T& Stack<T>::ConstStackIterator::deref() const {
    return current_->data;
}

template<typename T>
void Stack<T>::ConstStackIterator::increment() {
    if (current_) {
        current_ = current_->next;
    }
}

template<typename T>
typename fwd_container<T>::const_iterator_base* Stack<T>::ConstStackIterator::clone() const {
    return new ConstStackIterator(current_);
}

template<typename T>
bool Stack<T>::ConstStackIterator::equals(const typename fwd_container<T>::const_iterator_base* other) const {
    return this->get_node() == other->get_node();
}

#endif // STACK_HPP_INCLUDED
