#ifndef __STACK_HEADER__
#define __STACK_HEADER__

#include <vector>
#include <initializer_list>

template <typename T, typename Container = std::vector<T>>
class stack
{
    private:
        Container object;

    public:
        using value_type = T;
        using reference = T&;
        using size_type = size_t;
        using const_reference = const T&;
        using self_referenceL = stack<value_type>&;
        using const_self_reference = const stack<value_type>&;
        using self_referenceR = stack<value_type>&&;

    public:
        // Constructors and Destructor
        stack();
        stack(size_type s);
        stack(size_type s, const_reference val);
        stack(std::initializer_list<value_type> l);
        stack(self_referenceL rhv);
        stack(self_referenceR rhv);
        ~stack();

    public:
        // Operators
        self_referenceL operator=(self_referenceL rhv);
        self_referenceL operator=(self_referenceR rhv);
        reference operator[](const value_type index);

    public:
        // Methods
        bool empty();
        size_type size();
        reference top();
        void push(const_reference val);
        void emplace(const_reference data);
        void pop();
        void swap(self_referenceL obj);
};

// template <typename T>
// bool operator==(stack<T>)

#include "stack.h"

#endif