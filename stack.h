#ifndef STACK_H
#define STACK_H

#include "fwd_container.h"
#include "node.h"
#include "excaption.h"
#include <cstddef>
#include <initializer_list>
#include <iostream>
#include <iterator>

template<typename T>
class Stack : public fwd_container<T> {
private:
    Node<T>* top_;
    size_t size_;

    // Вложенные классы итераторов
    class StackIterator : public fwd_container<T>::iterator_base {
    private:
        Node<T>* current_;
        
    public:
        StackIterator() : current_(nullptr) {}
        explicit StackIterator(Node<T>* node) : current_(node) {}
        
        T& operator*() const { return current_->data; }
        T* operator->() const { return &current_->data; }
        
        StackIterator& operator++() {
            if (current_) {
                current_ = current_->next;
            }
            return *this;
        }
        
        StackIterator operator++(int) {
            StackIterator temp = *this;
            ++(*this);
            return temp;
        }
        
        bool operator==(const StackIterator& other) const { 
            return current_ == other.current_; 
        }
        
        bool operator!=(const StackIterator& other) const { 
            return current_ != other.current_; 
        }
    };
    
    class ConstStackIterator : public fwd_container<T>::const_iterator_base {
    private:
        const Node<T>* current_;
        
    public:
        ConstStackIterator() : current_(nullptr) {}
        explicit ConstStackIterator(const Node<T>* node) : current_(node) {}
        
        const T& operator*() const { return current_->data; }
        const T* operator->() const { return &current_->data; }
        
        ConstStackIterator& operator++() {
            if (current_) {
                current_ = current_->next;
            }
            return *this;
        }
        
        ConstStackIterator operator++(int) {
            ConstStackIterator temp = *this;
            ++(*this);
            return temp;
        }
        
        bool operator==(const ConstStackIterator& other) const { 
            return current_ == other.current_; 
        }
        
        bool operator!=(const ConstStackIterator& other) const { 
            return current_ != other.current_; 
        }
    };

public:
    using iterator = StackIterator;
    using const_iterator = ConstStackIterator;

    Stack();
    explicit Stack(size_t capacity);
    Stack(const Stack& other);
    Stack(Stack&& other) noexcept;
    Stack(std::initializer_list<T> init);
    ~Stack();

    Stack& operator=(const Stack& other);
    Stack& operator=(Stack&& other) noexcept;
    Stack& operator=(std::initializer_list<T> init);

    void push(const T& value) override;
    void push(T&& value) override;
    
    template<typename... Args>
    void emplace(Args&&... args);
    
    T pop() override;
    T& front() override;
    const T& front() const override;
    bool empty() const override;
    size_t size() const override;
    void clear() override;

    iterator begin();
    iterator end();
    const_iterator begin() const;
    const_iterator end() const;
    const_iterator cbegin() const;
    const_iterator cend() const;

    void swap(Stack& other) noexcept;
    bool operator==(const Stack& other) const;
    bool operator!=(const Stack& other) const;
    T& top() { return front(); }
    const T& top() const { return front(); }
    
    template<typename U>
    friend void swap(Stack<U>& a, Stack<U>& b) noexcept;
    
    template<typename U>
    friend std::ostream& operator<<(std::ostream& os, const Stack<U>& stack);
    
    template<typename U>
    friend std::istream& operator>>(std::istream& is, Stack<U>& stack);

private:
    void copy_from(const Stack& other);
};

#include "stack.hxx"

#endif // STACK_H