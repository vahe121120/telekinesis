#ifndef __QUEUE__HEADER__
#define __QUEUE__HEADER__

#include <deque>
#include <initializer_list>

template <typename T, typename Container = std::deque<T>>
class queue
{
    private:
        Container object;

    public: 
        using value_type = T;
        using reference = value_type&;
        using pointer = value_type*;
        using const_reference = const value_type&;
        using size_type = size_t;
        using const_pointer = const value_type*;
        using self_referenceL = queue<T, Container>&;
        using self_referenceR = queue<T, Container>&&;
        using const_self_referenceL = const queue<T, Container>&;

    public:
        queue();
        queue(size_type size);
        queue(size_type size, value_type value);
        queue(self_referenceL rhv);     // copy ctor
        queue(self_referenceR rhv);     // move ctor
        queue(std::initializer_list<T> l);

    public:
        const_self_referenceL operator=(self_referenceL rhv);
        const_self_referenceL operator=(self_referenceR rhv);
        reference operator[](size_type index);
        const_reference operator[](size_type index) const;

    public:
        reference front();
        reference back();
        size_type size();
        bool empty();
        void push(value_type value);

    public:
        template <typename... Args>
        const_self_referenceL emplace(Args... args);
        void pop();
        void swap(self_referenceL other);
};

#include "queue.h"

#endif
