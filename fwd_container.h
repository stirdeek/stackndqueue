#ifndef FWD_CONTAINER_H
#define FWD_CONTAINER_H

#include <iostream>

template<typename T>
class fwd_container {
public:
    virtual ~fwd_container() = default;

    virtual void push(const T& value) = 0;
    virtual void push(T&& value) = 0;
    virtual T pop() = 0;
    virtual T& front() = 0;
    virtual const T& front() const = 0;
    virtual bool empty() const = 0;
    virtual size_t size() const = 0;
    virtual void clear() = 0;
    
    // Итераторы как вложенные классы
    class iterator_base {
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = T*;
        using reference = T&;
        
        iterator_base() : ptr(nullptr) {}
        explicit iterator_base(T* p) : ptr(p) {}
        
        reference operator*() const { return *ptr; }
        pointer operator->() const { return ptr; }
        
        iterator_base& operator++() {
            ++ptr;
            return *this;
        }
        
        iterator_base operator++(int) {
            iterator_base tmp = *this;
            ++ptr;
            return tmp;
        }
        
        bool operator==(const iterator_base& other) const { return ptr == other.ptr; }
        bool operator!=(const iterator_base& other) const { return ptr != other.ptr; }
        
    protected:
        T* ptr;
    };
    
    class const_iterator_base {
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = const T*;
        using reference = const T&;
        
        const_iterator_base() : ptr(nullptr) {}
        explicit const_iterator_base(const T* p) : ptr(p) {}
        
        reference operator*() const { return *ptr; }
        pointer operator->() const { return ptr; }
        
        const_iterator_base& operator++() {
            ++ptr;
            return *this;
        }
        
        const_iterator_base operator++(int) {
            const_iterator_base tmp = *this;
            ++ptr;
            return tmp;
        }
        
        bool operator==(const const_iterator_base& other) const { return ptr == other.ptr; }
        bool operator!=(const const_iterator_base& other) const { return ptr != other.ptr; }
        
    protected:
        const T* ptr;
    };
};

template<typename T>
std::ostream& operator<<(std::ostream& os, const fwd_container<T>& container) {
    return os;
}

template<typename T>
std::istream& operator>>(std::istream& is, fwd_container<T>& container) {
    T value;
    while (is >> value) {
        container.push(value);
    }
    return is;
}

#endif // FWD_CONTAINER_H