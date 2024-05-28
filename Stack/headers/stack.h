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
        using size_type = std::size_t;
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
        stack(const_self_reference rhv);
        stack(self_referenceR rhv);
        template <typename InputIt>
        stack(InputIt first, InputIt last);
        ~stack();

    public:
        // Operators
        const_self_reference operator=(const_self_reference rhv);
        const_self_reference operator=(self_referenceR rhv);
        reference operator[](size_type index);
        const_reference operator[](size_type index) const;

    public:
        // Methods
        bool empty() const;
        size_type size() const;
        reference top();
        void push(const_reference val);
        void emplace(const_reference data);
        void pop();
        void swap(self_referenceL obj);

    public:
        bool operator==(const_self_reference other) const;
        bool operator!=(const_self_reference other) const;
        bool operator<(const_self_reference other) const;
        bool operator<=(const_self_reference other) const;
        bool operator>(const_self_reference other) const;
        bool operator>=(const_self_reference other) const;
};

#include "./stack.hpp"

#endif