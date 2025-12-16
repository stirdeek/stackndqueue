#ifndef QUEUE_H
#define QUEUE_H

#include "fwd_container.h"
#include "node.h"
#include <cstddef>

template<typename T>
class Queue : public fwd_container<T> {
private:
    Node<T>* head_;
    Node<T>* tail_;
    size_t size_;

public:
    using iterator = typename fwd_container<T>::iterator;
    using const_iterator = typename fwd_container<T>::const_iterator;

    Queue();
    Queue(const Queue& other);
    Queue(Queue&& other) noexcept;
    ~Queue();

    Queue& operator=(const Queue& other);
    Queue& operator=(Queue&& other) noexcept;

    void push(const T& value) override;
    void push(T&& value) override;
    void pop() override;
    T& get_front() override;
    const T& get_front() const override;
    bool is_empty() const override;
    size_t size() const override;

    iterator begin() override;
    iterator end() override;
    const_iterator cbegin() const override;
    const_iterator cend() const override;

private:
    void clear();
    void copy_from(const Queue& other);

    class QueueIterator : public fwd_container<T>::iterator_base {
    private:
        Node<T>* current_;

    public:
        explicit QueueIterator(Node<T>* node);
        void* get_node() override;
        const void* get_node() const override;
        T& deref() override;
        void increment() override;
        typename fwd_container<T>::iterator_base* clone() const override;
        bool equals(const typename fwd_container<T>::iterator_base* other) const override;
    };

    class ConstQueueIterator : public fwd_container<T>::const_iterator_base {
    private:
        const Node<T>* current_;

    public:
        explicit ConstQueueIterator(const Node<T>* node);
        const void* get_node() const override;
        const T& deref() const override;
        void increment() override;
        typename fwd_container<T>::const_iterator_base* clone() const override;
        bool equals(const typename fwd_container<T>::const_iterator_base* other) const override;
    };
};

#include "Queue.hpp"
#endif
