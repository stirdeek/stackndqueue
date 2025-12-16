#ifndef STACK_H
#define STACK_H

#include "fwd_container.h"
#include "node.h"
#include <cstddef>

template<typename T>
class Stack : public fwd_container<T> {
private:
    Node<T>* top_;
    size_t size_;

public:
    using iterator = typename fwd_container<T>::iterator;
    using const_iterator = typename fwd_container<T>::const_iterator;

    Stack();
    Stack(const Stack& other);
    Stack(Stack&& other) noexcept;
    ~Stack();

    Stack& operator=(const Stack& other);
    Stack& operator=(Stack&& other) noexcept;

    void push(const T& value) override;
    void push(T&& value) override;
    void pop() override;
    T& get_front() override;
    const T& get_front() const override;
    bool is_empty() const override;
    size_t size() const override;

    iterator begin() override;
    iterator end() override;
    const_iterator begin() const;
    const_iterator end() const;
    const_iterator cbegin() const override;
    const_iterator cend() const override;

private:
    void clear();
    void copy_from(const Stack& other);

    class StackIterator : public fwd_container<T>::iterator_base {
    private:
        Node<T>* current_;

    public:
        explicit StackIterator(Node<T>* node);
        void* get_node() override;
        const void* get_node() const override;
        T& deref() override;
        void increment() override;
        typename fwd_container<T>::iterator_base* clone() const override;
        bool equals(const typename fwd_container<T>::iterator_base* other) const override;
    };

    class ConstStackIterator : public fwd_container<T>::const_iterator_base {
    private:
        const Node<T>* current_;

    public:
        explicit ConstStackIterator(const Node<T>* node);
        const void* get_node() const override;
        const T& deref() const override;
        void increment() override;
        typename fwd_container<T>::const_iterator_base* clone() const override;
        bool equals(const typename fwd_container<T>::const_iterator_base* other) const override;
    };
};

#include "Stack.hpp"
#endif // STACK_H
