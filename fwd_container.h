#ifndef FWD_CONTAINER_H
#define FWD_CONTAINER_H

#include <iterator>
#include <memory>
#include <iostream>

template<typename T>
class fwd_container {
public:
    virtual ~fwd_container() = default;

    // Абстрактные методы контейнера
    virtual void push(const T& value) = 0;
    virtual void push(T&& value) = 0;
    virtual T pop() = 0;
    virtual T& get_front() = 0;
    virtual const T& get_front() const = 0;
    virtual bool is_empty() const = 0;
    virtual size_t size() const = 0;

    // Предварительные объявления
protected:
    class iterator_base;
    class const_iterator_base;

public:
    class const_iterator;  // Предварительное объявление
    class iterator;        // Предварительное объявление

    // Базовые классы итераторов
protected:
    class iterator_base {
    public:
        virtual ~iterator_base() = default;
        virtual T& operator*() = 0;
        virtual T* operator->() = 0;
        virtual iterator_base& operator++() = 0;
        virtual bool operator==(const iterator_base& other) const = 0;
        virtual bool operator!=(const iterator_base& other) const = 0;

    protected:
        virtual iterator_base* clone() const = 0;

        friend class iterator;
        friend class const_iterator;
    };

    class const_iterator_base {
    public:
        virtual ~const_iterator_base() = default;
        virtual const T& operator*() const = 0;
        virtual const T* operator->() const = 0;
        virtual const_iterator_base& operator++() = 0;
        virtual bool operator==(const const_iterator_base& other) const = 0;
        virtual bool operator!=(const const_iterator_base& other) const = 0;

    protected:
        virtual const_iterator_base* clone() const = 0;

        friend class iterator;
        friend class const_iterator;
    };

public:
    // Класс const_iterator должен быть объявлен перед iterator
    class const_iterator {
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = const T*;
        using reference = const T&;

        const_iterator() : base(nullptr) {}
        ~const_iterator() { delete base; }

        // Конструктор копирования
        const_iterator(const const_iterator& other) : base(other.base ? other.base->clone() : nullptr) {}

        // Конструктор перемещения
        const_iterator(const_iterator&& other) noexcept : base(other.base) {
            other.base = nullptr;
        }

        // Присваивание копированием
        const_iterator& operator=(const const_iterator& other) {
            if (this != &other) {
                delete base;
                base = other.base ? other.base->clone() : nullptr;
            }
            return *this;
        }

        // Присваивание перемещением
        const_iterator& operator=(const_iterator&& other) noexcept {
            if (this != &other) {
                delete base;
                base = other.base;
                other.base = nullptr;
            }
            return *this;
        }

        // Операторы доступа
        const T& operator*() const { return base->operator*(); }
        const T* operator->() const { return base->operator->(); }

        // Префиксный инкремент
        const_iterator& operator++() {
            base->operator++();
            return *this;
        }

        // Постфиксный инкремент
        const_iterator operator++(int) {
            const_iterator temp = *this;
            base->operator++();
            return temp;
        }

        // Сравнение
        bool operator==(const const_iterator& other) const {
            if (!base && !other.base) return true;
            if (!base || !other.base) return false;
            return base->operator==(*other.base);
        }

        bool operator!=(const const_iterator& other) const {
            return !(*this == other);
        }

    private:
        const_iterator_base* base;
        friend class iterator;
        friend class fwd_container<T>;  // Делаем fwd_container другом

        const_iterator(const_iterator_base* base_ptr) : base(base_ptr) {}
    };

    // Теперь класс iterator
    class iterator {
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = T*;
        using reference = T&;

        iterator() : base(nullptr) {}
        ~iterator() { delete base; }

        // Конструктор копирования
        iterator(const iterator& other) : base(other.base ? other.base->clone() : nullptr) {}

        // Конструктор перемещения
        iterator(iterator&& other) noexcept : base(other.base) {
            other.base = nullptr;
        }

        // Конструктор из const_iterator
        iterator(const const_iterator& other) : base(other.base ? other.base->clone() : nullptr) {}

        // Присваивание копированием
        iterator& operator=(const iterator& other) {
            if (this != &other) {
                delete base;
                base = other.base ? other.base->clone() : nullptr;
            }
            return *this;
        }

        // Присваивание перемещением
        iterator& operator=(iterator&& other) noexcept {
            if (this != &other) {
                delete base;
                base = other.base;
                other.base = nullptr;
            }
            return *this;
        }

        // Операторы доступа
        T& operator*() { return base->operator*(); }
        T* operator->() { return base->operator->(); }

        // Префиксный инкремент
        iterator& operator++() {
            base->operator++();
            return *this;
        }

        // Постфиксный инкремент
        iterator operator++(int) {
            iterator temp = *this;
            base->operator++();
            return temp;
        }

        // Сравнение
        bool operator==(const iterator& other) const {
            if (!base && !other.base) return true;
            if (!base || !other.base) return false;
            return base->operator==(*other.base);
        }

        bool operator!=(const iterator& other) const {
            return !(*this == other);
        }

        bool operator==(const const_iterator& other) const {
            if (!base && !other.base) return true;
            if (!base || !other.base) return false;
            return base->operator==(*other.base);
        }

        bool operator!=(const const_iterator& other) const {
            return !(*this == other);
        }

    private:
        iterator_base* base;
        friend class const_iterator;
        friend class fwd_container<T>;  // Делаем fwd_container другом

        iterator(iterator_base* base_ptr) : base(base_ptr) {}
    };

    // Абстрактные методы для итераторов
    virtual iterator begin() = 0;
    virtual iterator end() = 0;
    virtual const_iterator begin() const = 0;
    virtual const_iterator end() const = 0;
    virtual const_iterator cbegin() const = 0;
    virtual const_iterator cend() const = 0;

    // Потоковый ввод
    friend std::istream& operator>>(std::istream& is, fwd_container& container) {
        T value;
        while (is >> value) {
            container.push(value);
        }
        return is;
    }

    // Потоковый вывод
    friend std::ostream& operator<<(std::ostream& os, const fwd_container& container) {
        for (const auto& item : container) {
            os << item << " ";
        }
        return os;
    }
};

#endif // FWD_CONTAINER_H
