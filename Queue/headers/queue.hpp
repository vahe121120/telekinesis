#ifndef __Queue_HPP__
#define __Queue_HPP__

#include "queue.h"

#include <deque>
#include <initializer_list>


template <typename T, typename Container>
Queue<T, Container>::Queue() = default;

template <typename T, typename Container>
template <typename InputIt>
Queue<T, Container>::Queue(InputIt first, InputIt second)
{
    object.insert(object.cbegin(), first, second);
}

// copy ctor
template <typename T, typename Container>
Queue<T, Container>::Queue(self_referenceL rhv)
{
    object.resize(rhv.size());
    object = rhv.object;
}

// move ctor
template <typename T, typename Container>
Queue<T, Container>::Queue(self_referenceR rhv)
{
    object.resize(rhv.size());
    object = std::move(rhv.object);
    rhv.object = nullptr;
}

template <typename T, typename Container>
Queue<T, Container>::Queue(std::initializer_list<T> l)
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
const Queue<T, Container>&
Queue<T, Container>::
operator=(const_self_referenceL rhv)
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
const Queue<T, Container>&
Queue<T, Container>::
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
T& Queue<T, Container>::operator[](size_type index)
{
    return object[index];
}


template <typename T, typename Container>
T&
Queue<T, Container>::
front()
{
    if ( !this->empty() )
    {
        return object[0];
    }
    throw 1;
}

template <typename T, typename Container>
const T&
Queue<T, Container>::
front() const
{
    if ( !this->empty() )
    {
        return object[0];
    }
    throw 1;
}

template <typename T, typename Container>
T&
Queue<T, Container>::
back()
{
    if ( !this->empty() )
    {
        return object[size() - 1];
    }
}

template <typename T, typename Container>
const T&
Queue<T, Container>::
back() const
{
    if ( !this->empty() )
    {
        return object[size() - 1];
    }
}

template <typename T, typename Container>
std::size_t Queue<T, Container>::size() const
{
    return (static_cast<size_type>(object.size()));
}

template <typename T, typename Container>
bool
Queue<T, Container>::
empty() const
{
    return !this->size();
}

template <typename T, typename Container>
void
Queue<T, Container>::
push(const_reference value)
{
    object.push_back(value);
}

template <typename T, typename Container>
template <typename... Args>
void
Queue<T, Container>::
push_range(Args... args)
{
    ( (object.push_back(args)), ... );
}


template <typename T, typename Container>
template <typename... Args>
const Queue<T, Container>&
Queue<T, Container>::
emplace(Args... args)
{
    ( (object.push_back(args)), ...);
}


template <typename T, typename Container>
void
Queue<T, Container>::
pop()
{
    object.pop_front();
}

template <typename T, typename Container>
void
Queue<T, Container>::
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

template <typename T, typename Container>
bool Queue<T, Container>::operator==(const_self_referenceL other) const
{
    return ( object == other.object );
}

template <typename T, typename Container>
bool Queue<T, Container>::operator!=(const_self_referenceL other) const
{
    return ( object != other.object );
}

template <typename T, typename Container>
bool Queue<T, Container>::operator<(const_self_referenceL other) const
{
    return ( object < other.object );
}

template <typename T, typename Container>
bool Queue<T, Container>::operator<=(const_self_referenceL other) const
{
    return ( object <= other.object );
}

template <typename T, typename Container>
bool Queue<T, Container>::operator>(const_self_referenceL other) const
{
    return ( object > other.object );
}

template <typename T, typename Container>
bool Queue<T, Container>::operator>=(const_self_referenceL other) const
{
    return ( object >= other.object );
}

#endif  // __Queue_HPP__