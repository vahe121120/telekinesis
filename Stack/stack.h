#ifndef __STACK_IMPLEMENTATION__
#define __STACK_IMPLEMENTATION__

#include <vector>
#include <initializer_list>
#include "stack.hpp"

// Constructors

// Default constructor
template <typename T, typename Container>
stack<T, Container>::stack()
{
    Container object;
}

// Assignment constructor
template <typename T, typename Container>
stack<T, Container>::stack(size_type s)
{
    value_type val{};
    stack<T, Container>::stack(s, val);
}

// Parametric constructor
template <typename T, typename Container>
stack<T, Container>::stack(size_type s, const_reference val)
{
    object.resize(s, val);
}

// initializer_list constructor
template <typename T, typename Container>
stack<T, Container>::stack(std::initializer_list<value_type> l)
{
    object.resize(l.size());

    int i{};
    for ( auto value : l )
    {
        object[i] = value;
        ++i;
    }
}

// Copy constructor
template <typename T, typename Container>
stack<T, Container>::stack(self_referenceL rhv)
{
    size_type size = rhv.size();
    object.resize(size);
    
    for ( int i = 0; i < size; ++i )
    {
        object[i] = rhv[i];
    }
}

// Move constructor
template <typename T, typename Container>
stack<T, Container>::stack(self_referenceR rhv)
{
    size_type size = rhv.size();
    object.resize(size);

    for ( int i = 0; i < size; ++i )
    {
        object[i] = rhv[i];
    }
    rhv.clear();
}

// Destructor
template <typename T, typename Container>
stack<T, Container>::~stack()
{
    object.clear();
}


// Operators

// operator = copy
template <typename T, typename Container>
stack<T>& stack<T, Container>::operator=(self_referenceL rhv)
{
    if ( this != &rhv )
    {
        object.clear();

        size_type size = rhv.size();
        object.resize(size);

        for ( int i = 0; i < size; ++i )
        {
            object[i] = rhv[i];
        }
    }

    return *this;
}

// operator = move
template <typename T, typename Container>
stack<T>& stack<T, Container>::operator=(self_referenceR rhv)
{
    if ( this != &rhv )
    {
        size_type size = rhv.size();
        object.resize(size);
        
        for ( int i = 0; i < size; ++i )
        {
            object[i] = rhv[i];
        }
    }

    return *this;
}

template <typename T, typename Container>
T& stack<T, Container>::operator[](const value_type index)
{
    return object[index];
}


// Methods
template <typename T, typename Container>
bool stack<T, Container>::empty()
{
    return !object.size();
}

template <typename T, typename Container>
size_t stack<T, Container>::size()
{
    return object.size();
}

template <typename T, typename Container>
T& stack<T, Container>::top()
{
    return object.back();
}

template <typename T, typename Container>
void stack<T, Container>::push(const_reference val)
{
    object.push_back(val);
}

template <typename T, typename Container>
void stack<T, Container>::emplace(const_reference data)
{
    object.push_back(data);
}

template <typename T, typename Container>
void stack<T, Container>::pop()
{
    object.pop_back();
}

template <typename T, typename Container>
void stack<T, Container>::swap(self_referenceL obj)
{
    int size = (object.size() > obj.size()) ? obj.size() : object.size();
    T tmp{};

    for ( int i = 0; i < size; ++i )
    {
        tmp = obj[i];
        obj[i] = object[i];
        object[i] = tmp;
    }
}


#endif