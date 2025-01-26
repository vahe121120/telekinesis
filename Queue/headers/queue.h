#ifndef __Queue__HEADER__
#define __Queue__HEADER__

#include <deque>
#include <initializer_list>

template <typename T, typename Container = std::deque<T>>
class Queue
{
    private:
        Container object;

    public: 
        using value_type = T;
        using reference = value_type&;
        using pointer = value_type*;
        using const_reference = const value_type&;
        using size_type = std::size_t;
        using const_pointer = const value_type*;
        using self_referenceL = Queue<T, Container>&;
        using self_referenceR = Queue<T, Container>&&;
        using const_self_referenceL = const Queue<T, Container>&;

    public:
        Queue();
        template <typename InputIt>
        Queue(InputIt first, InputIt last);
        Queue(self_referenceL rhv);     // copy ctor
        Queue(self_referenceR rhv);     // move ctor
        Queue(std::initializer_list<T> l);

    public:
        const_self_referenceL operator=(const_self_referenceL rhv);
        const_self_referenceL operator=(self_referenceR rhv);

        // for printing values
        reference operator[](size_type index);

    public:
        reference front();
        const_reference front() const;
        reference back();
        const_reference back() const;
        size_type size() const;
        bool empty() const;
        void push(const_reference value);

    public:
        template <typename... Args>
        void push_range(Args... args);
        template <typename... Args>
        const_self_referenceL emplace(Args... args);
        void pop();
        void swap(self_referenceL other);

    public:
        bool operator==(const_self_referenceL other) const;
        bool operator!=(const_self_referenceL other) const;
        bool operator<(const_self_referenceL other) const;
        bool operator<=(const_self_referenceL other) const;
        bool operator>(const_self_referenceL other) const;
        bool operator>=(const_self_referenceL other) const;
};

#include "queue.hpp"

#endif