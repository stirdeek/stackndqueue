#ifndef QUEUE_H_INCLUDED
#define QUEUE_H_INCLUDED

#include "fwd_container.h"
#include <deque>
#include <stdexcept>

template<typename T>
class queue : public fwd_container<T> {
private:
    std::deque<T> data;

    // Класс итератора для queue
    class queue_iterator : public fwd_container<T>::iterator_base {
    private:
        typename std::deque<T>::iterator current;
        typename std::deque<T>::iterator end;

    public:
        queue_iterator(typename std::deque<T>::iterator start,
                      typename std::deque<T>::iterator end_pos)
            : current(start), end(end_pos) {}

        T& operator*() override {
            return *current;
        }

        T* operator->() override {
            return &(*current);
        }

        typename fwd_container<T>::iterator_base& operator++() override {
            ++current;
            return *this;
        }

        bool operator==(const typename fwd_container<T>::iterator_base& other) const override {
            const queue_iterator* derived = dynamic_cast<const queue_iterator*>(&other);
            if (!derived) return false;
            return current == derived->current;
        }

        bool operator!=(const typename fwd_container<T>::iterator_base& other) const override {
            return !(*this == other);
        }

    protected:
        typename fwd_container<T>::iterator_base* clone() const override {
            return new queue_iterator(*this);
        }
    };

    class queue_const_iterator : public fwd_container<T>::const_iterator_base {
    private:
        typename std::deque<T>::const_iterator current;
        typename std::deque<T>::const_iterator end;

    public:
        queue_const_iterator(typename std::deque<T>::const_iterator start,
                           typename std::deque<T>::const_iterator end_pos)
            : current(start), end(end_pos) {}

        const T& operator*() const override {
            return *current;
        }

        const T* operator->() const override {
            return &(*current);
        }

        typename fwd_container<T>::const_iterator_base& operator++() override {
            ++current;
            return *this;
        }

        bool operator==(const typename fwd_container<T>::const_iterator_base& other) const override {
            const queue_const_iterator* derived = dynamic_cast<const queue_const_iterator*>(&other);
            if (!derived) return false;
            return current == derived->current;
        }

        bool operator!=(const typename fwd_container<T>::const_iterator_base& other) const override {
            return !(*this == other);
        }

    protected:
        typename fwd_container<T>::const_iterator_base* clone() const override {
            return new queue_const_iterator(*this);
        }
    };

public:
    using iterator = typename fwd_container<T>::iterator;
    using const_iterator = typename fwd_container<T>::const_iterator;

    // Реализация методов fwd_container
    void push(const T& value) override {
        data.push_back(value);
    }

    void push(T&& value) override {
        data.push_back(std::move(value));
    }

    T pop() override {
        if (data.empty()) {
            throw std::runtime_error("Queue is empty");
        }
        T value = std::move(data.front());
        data.pop_front();
        return value;
    }

    T& get_front() override {
        if (data.empty()) {
            throw std::runtime_error("Queue is empty");
        }
        return data.front();
    }

    const T& get_front() const override {
        if (data.empty()) {
            throw std::runtime_error("Queue is empty");
        }
        return data.front();
    }

    bool is_empty() const override {
        return data.empty();
    }

    size_t size() const override {
        return data.size();
    }

    iterator begin() override {
        return iterator(new queue_iterator(data.begin(), data.end()));
    }

    iterator end() override {
        return iterator(new queue_iterator(data.end(), data.end()));
    }

    const_iterator begin() const override {
        return const_iterator(new queue_const_iterator(data.begin(), data.end()));
    }

    const_iterator end() const override {
        return const_iterator(new queue_const_iterator(data.end(), data.end()));
    }

    const_iterator cbegin() const override {
        return const_iterator(new queue_const_iterator(data.begin(), data.end()));
    }

    const_iterator cend() const override {
        return const_iterator(new queue_const_iterator(data.end(), data.end()));
    }
};

#endif // QUEUE_H_INCLUDED
