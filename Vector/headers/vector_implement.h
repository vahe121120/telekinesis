#ifndef __VECTOR_IMPLEMENTATION__
#define __VECTOR_IMPLEMENTATION__

#include "Vector.hpp"
#include <initializer_list>
#include <iostream>

using std::cout;
using std::endl;

// Default constructor

template <typename T>
vector<T>::vector()
	: vector<value_type>::vector(0, value_type{})
{}


// Assignment constructor

template <typename T>
vector<T>::vector(size_type s)
	: vector<T>::vector(s, value_type{})
{}


// Parametric constructor

template <typename T>
vector<T>::vector(size_type s, const_value_type val)
	: len{s}
	, cap{s}
	, arr{nullptr}
{
	if ( s )
	{
		arr = new value_type [cap];
		for (int i = 0; i < s; ++i)
		{
			arr[i] = val;
		}
	}
}


// dynamic initializing vector <=> constructor

template <typename T>
vector<T>::vector(std::initializer_list<value_type> l)
{
	this->len = l.size();
	this->arr = new value_type [this->len];

	int i{};
	for ( auto value : l )
	{
		arr[i] = value;
		i++;
	}
}


// Copy constructor

template <typename T>
vector<T>::vector(self_referenceL rhv)
{
	this->len = rhv.size();
	this->cap = rhv.capacity();

	arr = new value_type [cap];

	for (int i = 0; i < this->len; ++i)
	{
		this->arr[i] = rhv[i];
	}
}


// Move constructor

template <typename T>
vector<T>::vector(self_referenceR rhv)	
	: len{rhv.len}
	, cap{rhv.cap}
	, arr{rhv.arr}
{		
	rhv.arr = nullptr;
}


// Destructor

template <typename T>
vector<T>::~vector()
{
	vector<value_type>::clear();
}


// Copy assignment ( Deep copy )

template <typename T>
const vector<T>& vector<T>::operator=(const_self_reference rhv)
{
    if ( this != &rhv )
    {
		if ( arr )
        {
			this->clear();
        }
        arr = new value_type [this->cap];

        this->len = rhv.len;
        this->cap = rhv.cap;

        for (int i = 0; i < this->len; ++i)
        {
            this->arr[i] = rhv.arr[i];
        }
	} 

    return *this;
}


// Move assignment

template <typename T>
const vector<T>& vector<T>::operator=(self_referenceR rhv)
{
	if ( this != &rhv )
	{
		this->len = rhv.len;
		this->cap = rhv.cap;
		this->arr = rhv.arr;

		rhv.arr;
	}

	return *this;
}


// Subscript operator

template <typename T>
T& vector<T>::operator[](size_type index)
{
	return arr[index];
}


// Const subscript operator

template <typename T>
T& vector<T>::operator[](size_type index) const
{
	return arr[index];
}


// at method

template <typename T>
T& vector<T>::at(const size_type index)
{
	if ( index >= this->len ) throw;
	return arr[index];
}


// resize method

template <typename T>
void vector<T>::resize(const size_type s)
{
	resize(s, value_type{});
}


// resize method

template <typename T>
void vector<T>::resize(const size_type s, const_value_type val)
{
	if ( s == this->len ) return;

	if ( s > this->len )
	{
		if ( s <= this->cap )
		{
			for ( int i = this->len; i < s; ++i )
			{
				arr[i] = val;
			}

			this->len = s;
		}
		else
		{
			vector<T>::recap();
			value_type* ptr = new value_type [this->cap];

			for (int i = 0; i < this->len; ++i)
			{
				ptr[i] = this->arr[i];
			}

			this->arr = ptr;
			delete [] ptr;
			this->len = s;
		}
	}
	else
	{
		this->len = s;
	}
}


// front method

template <typename T>
T& vector<T>::front()
{
	if ( this->len )
		return arr[0];
	throw;
}


// back method

template <typename T>
T& vector<T>::back()
{
	if ( this->len )
		return arr[len - 1];
	throw;
}


// insert method

template <typename T>
const T& vector<T>::insert(const size_type index, const_value_type val)
{
	if ( index >= this->len )
		throw;

	this->len++;

	if ( this->len >= this->cap )
		vector<value_type>::recap();

	value_type* ptr = new T [this->len];

	for (int i = 0, j = 0; i < this->len; ++i, ++j)
	{
		if ( i == index )
		{
			ptr[i] = val;
			--j;
			continue;
		}

		ptr[i] = arr[j];
	}

	delete [] arr;
	arr = ptr;
	delete [] ptr;
}


// remove method

template <typename T>
void vector<T>::remove(size_type index)
{
	if ( index >= this->len ) throw;

	value_type* ptr = new value_type [this->len - 1];

	for (int i = 0, j = 0; i < this->len; ++i, ++j)
	{	
		if ( j == index )
		{
			--i;
			continue;
		}
		ptr[i] = arr[j];
	}

	this->len--;

	delete [] arr;
	arr = ptr;
	delete [] ptr;
}


// push_back method

template <typename T>
void vector<T>::push_back(const_value_type val)
{
	if ( !arr )
	{
		this->cap = 5;
		this->len = 1;
		arr = new value_type [cap];
		arr[0] = val;
	}
	else
	{
		this->len++;
		if ( this->len >= this->cap )
			vector<value_type>::recap();
		this->arr[len - 1] = val;
	}
}


// pop_back method

template <typename T>
void vector<T>::pop_back()
{
	if ( !this->empty() )
	{
		this->len--;
	}
}


// data method

template <typename T>
T* vector<T>::data()
{
	return (arr + 0);
}


// recap method

template <typename T>
void vector<T>::recap()
{
	while ( this->cap < this->len )
	{
		this->cap *= 2;
	}
}


// clear method

template <typename T>
void vector<T>::clear()
{
	if ( arr )
	{
		for (int i = this->len; i >= 0; --i)
		{
			this->arr[i] = 0;
		}

		delete [] arr;
		arr = nullptr;

		this->len = 0;
		this->cap = 0;
	}
}


// empty method

template <typename T>
bool vector<T>::empty()
{
	return !this->len;
}


// size method

template <typename T>
size_t vector<T>::size()
{
	return this->len;
}


// capacity method

template <typename T>
size_t vector<T>::capacity()
{
	return this->cap;
}


// Arithmetic operators <=> object with object

template <typename T>
const vector<T>
vector<T>::operator+(const_self_reference other)
{
	size_t size = (other.len > this->len) ? other.len : this->len;
	vector<value_type> ob(size);

	for ( int i = 0; i < size; ++i )
	{
		ob[i] = arr[i] + other[i];
	}

	return ob;
}

template <typename T>
const vector<T>
vector<T>::operator-(const_self_reference other)
{
	size_t size = (other.len > this->len) ? other.len : this->len;
	vector<value_type> ob(size);

	for ( int i = 0; i < size; ++i )
	{
		ob[i] = arr[i] - other[i];
	}

	return ob;
}

template <typename T>
const vector<T>
vector<T>::operator*(const_self_reference other)
{
	size_t size = (other.len > this->len) ? other.len : this->len;
	vector<value_type> ob(size);

	for ( int i = 0; i < size; ++i )
	{
		ob[i] = arr[i] * other[i];
	}

	return ob;
}

template <typename T>
const vector<T>
vector<T>::operator/(const_self_reference other)
{
	size_t size = (other.len > this->len) ? other.len : this->len;
	vector<value_type> ob(size);

	for ( int i = 0; i < size; ++i )
	{
		ob[i] = arr[i] / other[i];
	}

	return ob;
}

template <typename T>
const vector<T>
vector<T>::operator%(const_self_reference other)
{
	size_t size = (other.len > this->len) ? other.len : this->len;
	vector<value_type> ob(size);

	for ( int i = 0; i < size; ++i )
	{
		ob[i] = arr[i] % other[i];
	}

	return ob;
}


// Arithmetic operators <=> object with T

template <typename T>
const vector<T> operator+(T val1, vector<T>& val2)
{
	size_t size = val2.size();
	vector<T> tmp(size);
	for ( int i = 0; i < size; ++i )
	{
		tmp[i] = val2[i] + val1;
	}

	return tmp;
}

template <typename T>
const vector<T> operator-(T val1, vector<T>& val2)
{
	size_t size = val2.size();
	vector<T> tmp(size);
	for ( int i = 0; i < size; ++i )
	{
		tmp[i] = val2[i] - val1;
	}

	return tmp;
}

template <typename T>
const vector<T> operator*(T val1, vector<T>& val2)
{
	size_t size = val2.size();
	vector<T> tmp(size);
	for ( int i = 0; i < size; ++i )
	{
		tmp[i] = val2[i] * val1;
	}

	return tmp;
}

template <typename T>
const vector<T> operator/(T val1, vector<T>& val2)
{
	size_t size = val2.size();
	vector<T> tmp(size);
	for ( int i = 0; i < size; ++i )
	{
		tmp[i] = val2[i] / val1;
	}

	return tmp;
}

template <typename T>
const vector<T> operator%(T val1, vector<T>& val2)
{
	size_t size = val2.size();
	vector<T> tmp(size);
	for ( int i = 0; i < size; ++i )
	{
		tmp[i] = val2[i] % val1;
	}

	return tmp;
}


#endif