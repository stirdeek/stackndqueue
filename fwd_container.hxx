#ifndef FWD_CONTAINER_HXX_INCLUDED
#define FWD_CONTAINER_HXX_INCLUDED

#include "fwd_container.h"

// Вложенные классы итераторов
template<typename T>
class fwd_container<T>::iterator {
public:
    using iterator_category = std::forward_iterator_tag;
    using value_type = T;
    using difference_type = std::ptrdiff_t;
    using pointer = T*;
    using reference = T&;

    iterator() : ptr(nullptr) {}
    explicit iterator(T* p) : ptr(p) {}

    reference operator*() const { return *ptr; }
    pointer operator->() const { return ptr; }

    iterator& operator++() {
        ++ptr;
        return *this;
    }

    iterator operator++(int) {
        iterator tmp = *this;
        ++ptr;
        return tmp;
    }

    bool operator==(const iterator& other) const { return ptr == other.ptr; }
    bool operator!=(const iterator& other) const { return ptr != other.ptr; }

private:
    T* ptr;
};

template<typename T>
class fwd_container<T>::const_iterator {
public:
    using iterator_category = std::forward_iterator_tag;
    using value_type = T;
    using difference_type = std::ptrdiff_t;
    using pointer = const T*;
    using reference = const T&;

    const_iterator() : ptr(nullptr) {}
    explicit const_iterator(const T* p) : ptr(p) {}

    reference operator*() const { return *ptr; }
    pointer operator->() const { return ptr; }

    const_iterator& operator++() {
        ++ptr;
        return *this;
    }

    const_iterator operator++(int) {
        const_iterator tmp = *this;
        ++ptr;
        return tmp;
    }

    bool operator==(const const_iterator& other) const { return ptr == other.ptr; }
    bool operator!=(const const_iterator& other) const { return ptr != other.ptr; }

private:
    const T* ptr;
};

template<typename T>
std::ostream& operator<<(std::ostream& os, const fwd_container<T>& container) {
    for (const auto& item : container) {
        os << item << " ";
    }
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

#endif // FWD_CONTAINER_HXX_INCLUDED
