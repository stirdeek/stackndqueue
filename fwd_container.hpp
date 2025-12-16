#ifndef FWD_CONTAINER_H
#define FWD_CONTAINER_H

#include <iostream>
#include <iterator>
#include <memory>
#include <stdexcept>

template<typename T>
class fwd_container {
public:
    class iterator_base {
    public:
        virtual ~iterator_base() = default;
        virtual void* get_node() = 0;
        virtual const void* get_node() const = 0;
        virtual T& deref() = 0;
        virtual void increment() = 0;
        virtual iterator_base* clone() const = 0;
        virtual bool equals(const iterator_base* other) const = 0;
    };

    class const_iterator_base {
    public:
        virtual ~const_iterator_base() = default;
        virtual const void* get_node() const = 0;
        virtual const T& deref() const = 0;
        virtual void increment() = 0;
        virtual const_iterator_base* clone() const = 0;
        virtual bool equals(const const_iterator_base* other) const = 0;
    };

    // Предварительные объявления
    class iterator;
    class const_iterator;

    // Виртуальный деструктор
    virtual ~fwd_container() = default;

    // Контейнерный интерфейс
    virtual void push(const T& value) = 0;
    virtual void push(T&& value) = 0;
    virtual T pop() = 0;
    virtual T& front() = 0;
    virtual const T& front() const = 0;
    virtual bool empty() const = 0;
    virtual size_t size() const = 0;
    virtual void clear() = 0;

    // Итераторы
    virtual iterator begin() = 0;
    virtual iterator end() = 0;
    virtual const_iterator begin() const = 0;
    virtual const_iterator end() const = 0;
    virtual const_iterator cbegin() const = 0;
    virtual const_iterator cend() const = 0;

    // Удобные методы
    const_iterator begin() const { return cbegin(); }
    const_iterator end() const { return cend(); }

    // Виртуальное сравнение
    virtual bool operator==(const fwd_container& other) const = 0;
    virtual bool operator!=(const fwd_container& other) const = 0;

    // Виртуальный swap
    virtual void swap(fwd_container& other) noexcept = 0;

    // Дружественные операторы (объявления)
    template<typename U>
    friend std::ostream& operator<<(std::ostream& os, const fwd_container<U>& container);

    template<typename U>
    friend std::istream& operator>>(std::istream& is, fwd_container<U>& container);

    // Дружественная функция swap
    template<typename U>
    friend void swap(fwd_container<U>& a, fwd_container<U>& b) noexcept;
};

// Предварительные объявления внешних операторов
template<typename T>
std::ostream& operator<<(std::ostream& os, const fwd_container<T>& container);

template<typename T>
std::istream& operator>>(std::istream& is, fwd_container<T>& container);

template<typename T>
void swap(fwd_container<T>& a, fwd_container<T>& b) noexcept;

#include "fwd_container.hpp"

#endif
