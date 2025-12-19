#ifndef QUEUE_H
#define QUEUE_H

#include "fwd_container.h"
#include "node.h"
#include "excaption.h"
#include <cstddef>
#include <initializer_list>
#include <iostream>
#include <iterator>

template<typename T>
class Queue : public fwd_container<T> {
private:
    Node<T>* head_;
    Node<T>* tail_;
    size_t size_;

    // Вложенные классы итераторов
    class QueueIterator : public fwd_container<T>::iterator_base {
    private:
        Node<T>* current_;
        
    public:
        QueueIterator() : current_(nullptr) {}
        explicit QueueIterator(Node<T>* node) : current_(node) {}
        
        T& operator*() const { return current_->data; }
        T* operator->() const { return &current_->data; }
        
        QueueIterator& operator++() {
            if (current_) {
                current_ = current_->next;
            }
            return *this;
        }
        
        QueueIterator operator++(int) {
            QueueIterator temp = *this;
            ++(*this);
            return temp;
        }
        
        bool operator==(const QueueIterator& other) const { 
            return current_ == other.current_; 
        }
        
        bool operator!=(const QueueIterator& other) const { 
            return current_ != other.current_; 
        }
    };
    
    class ConstQueueIterator : public fwd_container<T>::const_iterator_base {
    private:
        const Node<T>* current_;
        
    public:
        ConstQueueIterator() : current_(nullptr) {}
        explicit ConstQueueIterator(const Node<T>* node) : current_(node) {}
        
        const T& operator*() const { return current_->data; }
        const T* operator->() const { return &current_->data; }
        
        ConstQueueIterator& operator++() {
            if (current_) {
                current_ = current_->next;
            }
            return *this;
        }
        
        ConstQueueIterator operator++(int) {
            ConstQueueIterator temp = *this;
            ++(*this);
            return temp;
        }
        
        bool operator==(const ConstQueueIterator& other) const { 
            return current_ == other.current_; 
        }
        
        bool operator!=(const ConstQueueIterator& other) const { 
            return current_ != other.current_; 
        }
    };

public:
    using iterator = QueueIterator;
    using const_iterator = ConstQueueIterator;

    Queue();
    explicit Queue(size_t capacity);
    Queue(const Queue& other);
    Queue(Queue&& other) noexcept;
    Queue(std::initializer_list<T> init);
    ~Queue();

    Queue& operator=(const Queue& other);
    Queue& operator=(Queue&& other) noexcept;
    Queue& operator=(std::initializer_list<T> init);

    void push(const T& value) override;
    void push(T&& value) override;
    
    template<typename... Args>
    void emplace(Args&&... args);
    
    T pop() override;
    T& front() override;
    const T& front() const override;
    
    T& back();
    const T& back() const;
    
    bool empty() const override;
    size_t size() const override;
    void clear() override;

    iterator begin();
    iterator end();
    const_iterator begin() const;
    const_iterator end() const;
    const_iterator cbegin() const;
    const_iterator cend() const;

    void swap(Queue& other) noexcept;
    bool operator==(const Queue& other) const;
    bool operator!=(const Queue& other) const;
    
    template<typename U>
    friend void swap(Queue<U>& a, Queue<U>& b) noexcept;
    
    template<typename U>
    friend std::ostream& operator<<(std::ostream& os, const Queue<U>& queue);
    
    template<typename U>
    friend std::istream& operator>>(std::istream& is, Queue<U>& queue);

private:
    void copy_from(const Queue& other);
};

#include "queue.hxx"

#endif // QUEUE_H