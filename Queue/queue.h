#ifndef __QUEUE__IMPLEMENTAION__
#define __QUEUE__IMPLEMENTAION__

#include "queue.hpp"

#include <deque>
#include <initializer_list>


template <typename T, typename Container>
queue<T, Container>::queue()
    : queue(0, value_type{})
{}

template <typename T, typename Container>
queue<T, Container>::queue(size_type size)
    : queue(size, value_type{})
{}

template <typename T, typename Container>
queue<T, Container>::queue(size_type size, value_type value)
    : object(size, value)
{}

// copy ctor
template <typename T, typename Container>
queue<T, Container>::queue(self_referenceL rhv)
{
    object.resize(rhv.size());
    object = rhv.object;
}

// move ctor
template <typename T, typename Container>
queue<T, Container>::queue(self_referenceR rhv)
{
    object.resize(rhv.size());
    object = std::move(rhv.object);
    rhv.object = nullptr;
}

template <typename T, typename Container>
queue<T, Container>::queue(std::initializer_list<T> l)
{
    object.resize(l.size());
    int i{};
    for ( auto value : l )
    {
        object[i] = value;
        ++i;
    }
}

// copy assignment
template <typename T, typename Container>
const queue<T, Container>&
queue<T, Container>::
operator=(self_referenceL rhv)
{
    if ( this != &rhv )
    {
        object.clear();
        object.resize(rhv.size());

        for ( int i = 0; i < rhv.size(); ++i )
        {
            object[i] = rhv.object[i];
        }
    }

    return *this;
}

// move assignment
template <typename T, typename Container>
const queue<T, Container>&
queue<T, Container>::
operator=(self_referenceR rhv)
{
    if ( this != &rhv )
    {
        object.resize(rhv.size());
        object = rhv.object;
        
        rhv.object.clear();
    }

    return *this;
}

template <typename T, typename Container>
T& queue<T, Container>::operator[](size_type index)
{
    return object[index];
}

template <typename T, typename Container>
const T&
queue<T, Container>::
operator[](size_type index) const
{
    return object[index];
}

template <typename T, typename Container>
T&
queue<T, Container>::
front()
{
    if ( !this->empty() )
    {
        return object[0];
    }
    throw 1;
}

template <typename T, typename Container>
T&
queue<T, Container>::
back()
{
    if ( !this->empty() )
    {
        return object[size() - 1];
    }
}

template <typename T, typename Container>
size_t queue<T, Container>::size()
{
    return object.size();
}

template <typename T, typename Container>
bool
queue<T, Container>::
empty()
{
    return !this->size();
}

template <typename T, typename Container>
void
queue<T, Container>::
push(value_type value)
{
    object.push_back(value);
}

template <typename T, typename Container>
template <typename... Args>
const queue<T, Container>&
queue<T, Container>::
emplace(Args... args)
{
    (object.push_back(args...));
}


template <typename T, typename Container>
void
queue<T, Container>::
pop()
{
    object.pop_front();
}

template <typename T, typename Container>
void
queue<T, Container>::
swap(self_referenceL other)
{
    size_type tSize = this->size();
    size_type oSize = other.size();
    size_type size = tSize > oSize ? tSize : oSize;
    object.resize(size);

    for ( int i = 0; i < size; ++i )
    {
        if ( tSize < oSize )
        {
            value_type tmp = this->object[i];
            this->object[i] = other.object[i];
            other.object[i] = tmp;
        }
        else
        {
            other.object.resize(size, 0);
            value_type tmp = this->object[i];
            this->object[i] = other.object[i];
            other.object[i] = tmp;
        }
    }
}

#endif
